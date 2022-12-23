//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file
    This file contains code for Platform Secure Boot related functionality

**/

#include "Token.h"
#include <Guid/AmiPsp.h>
#include <Library/HobLib.h>
#include <RomLayout.h>
#include <AmiPeiLib.h>
#include <Ppi/CryptoPPI.h>
#include <BaseCryptLib.h>
#include <Include/AmiCertificate.h>
#include <Protocol/Hash.h>
#include <Library/DebugLib.h>

#define ROM_LAYOUT_FFS_GUID \
    { 0x0DCA793A, 0xEA96, 0x42d8, 0xBD, 0x7B, 0xDC, 0x7F, 0x68, 0x4E, 0x38, 0xC1 }
    
extern EFI_GUID gAmiDigitalSignaturePPIGuid;    

typedef struct _ROM_LAYOUT_SECTION {
    EFI_GUID Guid;
    ROM_AREA Layout[1];
} ROM_LAYOUT_SECTION;

static EFI_GUID RomLayoutFfsGuid            = ROM_LAYOUT_FFS_GUID;
static EFI_GUID gFWkey_RSA2048_Guid         = EFI_CERT_RSA2048_GUID;
static EFI_GUID gFWkeyGuid                  = PR_KEY_GUID;
static EFI_GUID gEfiHashAlgorithmSha256Guid = EFI_HASH_ALGORITHM_SHA256_GUID;

#define FV_IN_RAM   0

#if FV_IN_RAM
    UINT8   *FvInRamStart;
    UINTN   RamOffset;
#endif

/**
    Function to read ROM_LAYOUT data from FFS file

    @param PeiServices pointer to PEI services
    @param Layout pointer to output buffer

    @retval EFI_SUCCESS if ROM layout is retrieved

**/

EFI_STATUS
GetRomLayout(
  IN    EFI_PEI_SERVICES    **PeiServices,
  OUT   ROM_AREA            **Layout
)
{
    EFI_STATUS                  Status;
    EFI_FIRMWARE_VOLUME_HEADER  *BootFv;
    EFI_FFS_FILE_HEADER         *File = NULL;
    ROM_LAYOUT_SECTION          *Section;

    Status = (*PeiServices)->FfsFindNextVolume (PeiServices, 0, &BootFv);
    if (EFI_ERROR(Status)) 
        return Status;

    do
    {
        Status = (*PeiServices)->FfsFindNextFile (PeiServices, EFI_FV_FILETYPE_FREEFORM, BootFv, &File);
        if (!EFI_ERROR(Status) && !guidcmp (&(File->Name), &RomLayoutFfsGuid))
            break;
    } while (Status == EFI_SUCCESS);

    if (EFI_ERROR (Status)) 
        return Status;

    Status = (*PeiServices)->FfsFindSectionData (PeiServices, EFI_SECTION_FREEFORM_SUBTYPE_GUID, File, &Section);
    if (EFI_ERROR (Status))
        return Status;

    *Layout = Section->Layout;
    return EFI_SUCCESS;
}

/**
    Verify DXE volume, signed at build time 

    @param PeiServices pointer to PEI services
    @param pFv pointer to Firmware volume header
    @param pFile pointer to DxeSig file header 

    @retval EFI_SUCCESS if DXE volume verified without errors

**/

EFI_STATUS
CheckDxeSign(
  IN    EFI_PEI_SERVICES            **PeiServices,
  IN    EFI_FIRMWARE_VOLUME_HEADER  *Fv,
  IN    EFI_FFS_FILE_HEADER         *File
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    AMI_CRYPT_DIGITAL_SIGNATURE_PPI *AmiSigPpi = NULL;
    VOID                            *HashCtx = NULL;
    UINTN                           CtxSize;
    UINT8                           HashDb[SHA256_DIGEST_SIZE];
    UINT8*                          CurrPosition;
    INTN                            CmpStatus;
    APTIO_FW_CAPSULE_HEADER         *AptioFwCapsHdrPtr;
    PEI_CRYPT_HANDLE                HashHndl;
    PEI_CRYPT_HANDLE                PubKeyHndl;
    UINT32                          Flags = 0;
    ROM_AREA                        *RomAreaTbl;
    VOID                            *Sig;
    UINTN                           Index;
    
    Status = (*PeiServices)->LocatePpi (PeiServices, &gAmiDigitalSignaturePPIGuid, 0, NULL, &AmiSigPpi);
    if (EFI_ERROR(Status))
        return Status;

    CtxSize = Sha256GetContextSize();
    Status = (*PeiServices)->AllocatePool (PeiServices, CtxSize, &HashCtx);
    ASSERT_PEI_ERROR (PeiServices, Status);
    if (EFI_ERROR (Status))
        return Status;

    // Adjust to section
    CurrPosition = (UINT8*)File;
    CurrPosition += sizeof (EFI_FFS_FILE_HEADER);

    // At file section
    CurrPosition += sizeof (EFI_COMMON_SECTION_HEADER);
    CmpStatus = guidcmp (CurrPosition,&gDxeSigSectionGuid);
    if (0 != CmpStatus)
        return  EFI_VOLUME_CORRUPTED;

    (UINT8*)AptioFwCapsHdrPtr = CurrPosition + sizeof (EFI_GUID);

    if (AptioFwCapsHdrPtr->RomImageOffset > FWCAPSULE_MAX_HDR_SIZE)
        return EFI_SECURITY_VIOLATION;
    
    // For now Aptio FW Capsule only supports WIN_CERT_TYPE_EFI_GUID 
    if (AptioFwCapsHdrPtr->FWCert.SignCert.Hdr.Hdr.wCertificateType != WIN_CERT_TYPE_EFI_GUID)
        return EFI_SECURITY_VIOLATION;

    // Version 010 and later supporting extended flags
    if (AptioFwCapsHdrPtr->CapHdr.Flags & CAPSULE_FLAGS_CAPHDR_IN_SIGNCERT)
    {
        if (AptioFwCapsHdrPtr->CapHdr.Flags & CAPSULE_FLAGS_RSA_PSS_PADDING_SCHEME)
            Flags = EFI_CRYPT_RSASSA_PSS;
        else
            Flags = EFI_CRYPT_RSASSA_PKCS1V15;
    }
    else
        Flags = EFI_CRYPT_RSASSA_PSS;

    HashHndl.AlgGuid  = gEfiHashAlgorithmSha256Guid;
    HashHndl.BlobSize = SHA256_DIGEST_SIZE;
    HashHndl.Blob = (UINT8*)&HashDb;

	// 1. Compare Capsule's Sign Cert key with Platform Root Key
    PubKeyHndl.BlobSize =  DEFAULT_RSA_KEY_MODULUS_LEN;
    PubKeyHndl.AlgGuid = gFWkey_RSA2048_Guid;
    PubKeyHndl.Blob = (UINT8*)AptioFwCapsHdrPtr->FWCert.SignCert.CertData.PublicKey;

    Status = AmiSigPpi->VerifyKey (AmiSigPpi, &gFWkeyGuid, &PubKeyHndl); 
    DEBUG((DEBUG_INFO, "DxeSign:Compare Platform and SignCert Keys : %r\n", Status));

	// Skip the RootCert key checking if SignCert Key and PR Key are a Match
    if (EFI_ERROR (Status))
    {
        // 1.1 Compare Capsule's Cert Root key with Platform Root
        PubKeyHndl.Blob = (UINT8*)AptioFwCapsHdrPtr->FWCert.RootCert.PublicKey;
        Status = AmiSigPpi->VerifyKey (AmiSigPpi, &gFWkeyGuid, &PubKeyHndl); 
        DEBUG((DEBUG_INFO, "DxeSign:Compare Platform and RootCert Keys : %r\n", Status));
        if (EFI_ERROR(Status))
            return Status;        

        // 2. Verify RootCert.Signature
        // 2.1  Compute FWCert.SignCert.PublicKey Hash
        Sha256Init (HashCtx);
        if (AptioFwCapsHdrPtr->CapHdr.Flags & CAPSULE_FLAGS_SIGNKEY_IN_ROOTCERT)
        {
            Sha256Update (HashCtx, (UINT8*)AptioFwCapsHdrPtr->FWCert.SignCert.CertData.PublicKey, 
             DEFAULT_RSA_KEY_MODULUS_LEN);
        }
        else
        {
            // 2.2  Compute FWCert.SignCert Hash
            Sha256Update (HashCtx, (UINT8*)&AptioFwCapsHdrPtr->FWCert.SignCert, sizeof (AMI_CERTIFICATE_RSA2048_SHA256));
        }
        if (!Sha256Final (HashCtx, HashDb))
            return EFI_SECURITY_VIOLATION;
    
        Sig = (void*)AptioFwCapsHdrPtr->FWCert.RootCert.Signature; 
        Status = AmiSigPpi->VerifySig (AmiSigPpi, &PubKeyHndl, &HashHndl, Sig,
                             DEFAULT_RSA_SIG_LEN, Flags);
        DEBUG((DEBUG_INFO, "DxeSign:Verify Root Cert : %r\n", Status));
        if (EFI_ERROR (Status))
            return Status;
    }

#if FV_IN_RAM
    Status = (*PeiServices)->AllocatePool (PeiServices, (UINTN)pFv->FvLength + 0x1000, &FvInRamStart);
    if (EFI_ERROR(Status))
        return Status;

    // Align 64 byte or 4096
    (UINTN)FvInRamStart = ((UINTN)FvInRamStart & 0xFFFFF000) + 0x1000;
//####    CopyMem_LpcDma(FvInRamStart, pFv, (UINTN)pFv->FvLength);
    MemCpy32 (FvInRamStart, pFv, (UINTN)pFv->FvLength);
    RamOffset = (UINT8*)pFv - FvInRamStart;
#endif //FV_IN_RAM

    // 3. Verify Signing Cert Signature
    // 3.1 The Rom image hash is calculated based on info from the Rom Area map

    RomAreaTbl = (ROM_AREA *)(UINTN)((UINT32)AptioFwCapsHdrPtr +
     AptioFwCapsHdrPtr->RomLayoutOffset);

    // Initialize a SHA hash context.
    Sha256Init (HashCtx);
    // number of signed elements in RomMap may not exceed max_num_elem constant. 
    // overall number of elements in the RomMap may not exceed max_num_elem x 2
    for (Index = 0; RomAreaTbl[Index].Size != 0 && 
          ((UINTN)&RomAreaTbl[Index] < (UINTN)((UINT32)AptioFwCapsHdrPtr+AptioFwCapsHdrPtr->RomImageOffset)); 
          Index++)
    {
        if (!(RomAreaTbl[Index].Attributes & ROM_AREA_FV_SIGNED)) 
            continue;
        // RomArea has offsets relative to ROM start
#if FV_IN_RAM    
        Sha256Update (HashCtx, (UINT8 *)((UINTN)(0xFFFFFFFF - FLASH_SIZE + 1) + RomAreaTbl[Index].Offset - RamOffset), RomAreaTbl[Index].Size);
#else
        Sha256Update (HashCtx, (UINT8 *)((UINTN)(0xFFFFFFFF - FLASH_SIZE + 1) + RomAreaTbl[Index].Offset), RomAreaTbl[Index].Size);
#endif  // FV_IN_RAM        
    }

	// 3.2 Hash of Capsule Hdr + FW Certificate Hdr
    if (AptioFwCapsHdrPtr->CapHdr.Flags & CAPSULE_FLAGS_CAPHDR_IN_SIGNCERT)
        Sha256Update (HashCtx, (UINT8*)AptioFwCapsHdrPtr, (UINTN)&AptioFwCapsHdrPtr->FWCert.SignCert.CertData - (UINTN)AptioFwCapsHdrPtr);

	// 3.3 Hash of the ROM_MAP table
    Sha256Update (HashCtx, (UINT8*)RomAreaTbl, ((Index + 1) * sizeof (ROM_AREA)));
    if (!Sha256Final (HashCtx, HashDb))
        return EFI_SECURITY_VIOLATION;

    Sig = (void*)AptioFwCapsHdrPtr->FWCert.SignCert.CertData.Signature; 
    PubKeyHndl.Blob = (UINT8*)AptioFwCapsHdrPtr->FWCert.SignCert.CertData.PublicKey;
    Status = AmiSigPpi->VerifySig (AmiSigPpi, &PubKeyHndl, &HashHndl, Sig, DEFAULT_RSA_SIG_LEN, Flags); 
    DEBUG((DEBUG_INFO, "DxeSign:Verify Sign Certificate Sig : %r\n", Status));

    return  Status;
}

/**
    This function is the entry point for PeiAmiPsp PEIM.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_STATUS EFI_SUCCESS
            This function will not return if EFI_STATUS != EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
PeiAmiPspEntry (
  IN        EFI_PEI_FILE_HANDLE FileHandle,
  IN CONST  EFI_PEI_SERVICES    **PeiServices
)
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_BOOT_MODE               BootMode;
    ROM_AREA                    *Area;
    EFI_FIRMWARE_VOLUME_HEADER  *Fv;
    VOID                        *File = NULL;
    INTN                        CmpStatus;

    BootMode = GetBootModeHob();
    
    if(BootMode == BOOT_IN_RECOVERY_MODE) 
	    return Status;

    Status = GetRomLayout (PeiServices, &Area);

    for(Area; Area->Size != 0; Area++) 
	{
        if (!(Area->Attributes & ROM_AREA_FV_SIGNED)) continue;
        if ((ROM_AREA_FV_PEI + ROM_AREA_FV_DXE) != (Area->Attributes & (ROM_AREA_FV_PEI + ROM_AREA_FV_DXE))) 
		    continue;
        // Find DXE FV
        if(((Area->Address - 1) + Area->Size) != 0xFFFFFFFF) 
		    break; // not FV_BB
    }

    // if not found - stop
    if((ROM_AREA_FV_PEI+ROM_AREA_FV_DXE) != (Area->Attributes & (ROM_AREA_FV_PEI+ROM_AREA_FV_DXE))) 
        goto ErrorLoop;
    
    Fv = (EFI_FIRMWARE_VOLUME_HEADER*)Area->Address;
    
    Status = (*PeiServices)->FfsFindNextFile (PeiServices,
                              EFI_FV_FILETYPE_FREEFORM, Fv, &File);
    if (EFI_ERROR(Status))
        goto ErrorLoop;    
    
    // Compare GUID - it can be capsule FFS file or other files
    CmpStatus = guidcmp (&((EFI_FFS_FILE_HEADER*)File)->Name,&gDxeSigFfsGuid);
    if (0 != CmpStatus)
    {
        while (!EFI_ERROR(Status))
        {
            Status = (*PeiServices)->FfsFindNextFile (PeiServices,
                                      EFI_FV_FILETYPE_FREEFORM, Fv, &File);
            if (EFI_ERROR (Status))
                goto ErrorLoop;    
            CmpStatus = guidcmp (&((EFI_FFS_FILE_HEADER*)File)->Name,&gDxeSigFfsGuid);
            if (!CmpStatus)
                break;
        }
        if (0 != CmpStatus)
            goto ErrorLoop;
    }

    Status = CheckDxeSign (PeiServices, Fv, File);
    if(EFI_ERROR(Status))
        goto ErrorLoop;

    return  Status;

ErrorLoop:
    while(1);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
