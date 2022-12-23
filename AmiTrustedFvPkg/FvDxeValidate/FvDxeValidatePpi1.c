//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
 Verify signed DXE FVs (PEI after memory, DXE2 & BDS FVs)
 Locate FvDxeSig FFS in FV_DATA FV, if found - verify the signature of signed FV ranges
 by comparing decrypted hash against a hash value constructed using the ROM map layout
 and stored inside the FV_DATA FvDxeSig Certificate header
 Copy all signed FV Dxe ranges to RAM before performing hash calculation.
 Install a PPI to notify TCG module the good DXE Hash is ready to be extended to PCR
**/

#include <Token.h>
#include <AmiPeiLib.h>
#include <Ppi/AmiFvDxeValidate.h>

#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <CryptLib.h>
#include "AmiCertificate.h"
#include <Library/AmiRomLayoutLib.h>

#include <Library/DebugLib.h>
#include <Library/PerformanceLib.h>

//------------------------------------------------------------------------
// Definitions
//------------------------------------------------------------------------
/// The GUID of the HOB containing Hash address list.
// cf96ae83-7ce7-4e3f-903f-b0f431cb5746
#define AMI_FV_DIGEST_HOB_GUID \
    {0xcf96ae83, 0x7ce7, 0x4e3f, { 0x90, 0x3f, 0xb0, 0xf4, 0x31, 0xcb, 0x57, 0x46} }
static EFI_GUID gAddrListHobGuid = AMI_FV_DIGEST_HOB_GUID;

/// AMI FvDxe signature hashed address list HOB
typedef struct _AMI_FV_DIGEST_INFO_HOB {
    EFI_HOB_GUID_TYPE    Header;
    AMI_FV_DIGEST_PPI    FvDigestPpi;
    UINTN                LenListOffs;
//    UINTN               AddrList[]; // List of mem ranges used to calculate final FvHash digest
//    UINTN               LenList[];  // List of mem ranges used to calculate final FvHash digest
//    UINTN               HashList[]; // List of pointers to the hashes of memory ranges within a HashTbl
//    UINT8               *HashTbl1;   // The buffer with the list of hashes calculated over mem ranges
} AMI_FV_DIGEST_INFO_HOB;

#define  MAX_FV_STORE_HEADER_SIZE 0x100
#ifndef AMI_FFS_COMMON_SECTION_HEADER
typedef struct _AMI_FFS_COMMON_SECTION_HEADER {
    EFI_FFS_FILE_HEADER FfsHdr;                         //< The FFS file header
    EFI_FREEFORM_SUBTYPE_GUID_SECTION GuidedSection;    //< The Guided Section of the FFS file
    APTIO_FW_CAPSULE_HEADER   pFvSigHeader[0];
} AMI_FFS_COMMON_SECTION_HEADER;
#endif
//------------------------------------------------------------------------
// External function prototypes
//------------------------------------------------------------------------
VOID ExecuteActionOnFailureToValidateFv(IN CONST EFI_PEI_SERVICES **PeiServices);

//------------------------------------------------------------------------
// Local prototypes
//------------------------------------------------------------------------
EFI_STATUS HashFwRomMapImage (
    IN AMI_FV_DXE_VALIDATE_PPI  *ThisPpi,
    IN CONST EFI_PEI_SERVICES   **PeiServices,
    IN APTIO_FW_CAPSULE_HEADER  *FvSigHeader
);

EFI_STATUS EFIAPI VerifyFvDxe(
    IN AMI_FV_DXE_VALIDATE_PPI  *ThisPpi,
    IN CONST EFI_PEI_SERVICES   **PeiServices,
    IN OUT AMI_ROM_AREA         *AmiRomArea
);

EFI_STATUS LaunchFvDxeVerifyPpi(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN AMI_FV_DXE_VALIDATE_PPI *FvDxeValidatePpi,
    IN AMI_ROM_AREA            *Area
);

EFI_STATUS EFIAPI InstallFvDxeVerifyPpi(
    IN EFI_PEI_SERVICES         **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                      *NullPpi
);

EFI_STATUS InstallFvDigestPpi(
    IN CONST EFI_PEI_SERVICES   **PeiServices,
    IN AMI_FV_DIGEST_PPI        *pFvDigestPpi
);

EFI_STATUS EFIAPI InstallFvDigestAfterMem(
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID *Ppi
);

//------------------------------------------------------------------------
// Notify, Install PPI
//------------------------------------------------------------------------
//static EFI_PEI_NOTIFY_DESCRIPTOR mReadyToInstallFvDxeVerify[] =
//{
//    {
//        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
//        &gEfiPeiMemoryDiscoveredPpiGuid,
//        (EFI_PEIM_NOTIFY_ENTRY_POINT)InstallFvDxeVerifyPpi
//    },
//};
static EFI_PEI_NOTIFY_DESCRIPTOR mReadyToInstallFvDigestAfterMem[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gEfiPeiMemoryDiscoveredPpiGuid,
        (EFI_PEIM_NOTIFY_ENTRY_POINT)InstallFvDigestAfterMem
    },
};
static EFI_PEI_NOTIFY_DESCRIPTOR mReadyToLaunchFvDxeVerify[] =
{
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gAmiPublishFvDxeValidatePpiGuid,
        (EFI_PEIM_NOTIFY_ENTRY_POINT)InstallFvDxeVerifyPpi
    },
};

//------------------------------------------------------------------------
// Verify FvSig
//------------------------------------------------------------------------

/**
Determine if the Rom Area attributes indicate the FV is measured

@param    Attributes

@retval   TRUE if FV is Measured
**/
BOOLEAN
IsFvMeasured (
  UINT32 Attributes
){
    return ( ((Attributes & AMI_ROM_AREA_MEASURED) == AMI_ROM_AREA_MEASURED)
           ||
           // or predict measured ranges: one of DXE/DXE2/BDS || PEI_AFTER_MEM && not FV_BB
           ((Attributes & AMI_ROM_AREA_FV_ACCESS_ATTRIBUTES) != 0
            &&
            // not FV_BB
            (Attributes & (AMI_ROM_AREA_FV_PEI | AMI_ROM_AREA_VITAL)) != (AMI_ROM_AREA_FV_PEI | AMI_ROM_AREA_VITAL)
           )
   );
}
/**
Determine if the Rom Area attributes indicate the FV PEI AFTER MEM

@param    Attributes

@retval   TRUE if FV is PEI MEM
**/
BOOLEAN
IsFvPeiAfterMem (
  UINT32 Attributes
){
    return (//((Attributes & AMI_ROM_AREA_FV_PEI_MEM) == AMI_ROM_AREA_FV_PEI_MEM)
           //|| // +VITAL
           (Attributes & (AMI_ROM_AREA_FV_PEI_MEM | AMI_ROM_AREA_VITAL)) == (AMI_ROM_AREA_FV_PEI_MEM | AMI_ROM_AREA_VITAL)
    );
}

// ----------------------------------------------------------------------------------------
// CryptoPPI replacement functions
// ----------------------------------------------------------------------------------------
// SDL defined Public Exponent E of RSA Key.
//
// Const defined in AmiCryptoPkg SDL
const UINT8  KeyE[] = {E_CONST}; // 0x10001
const UINTN  LenE = sizeof(KeyE);
//    PKCS_1 PSS Signature constant. Size of the Salt (random data) field in PSS signature.
const INT32  PssSaltlen = PSS_SIG_SALTLEN; // 0 - saltlen matches the size of hash

typedef struct{
    EFI_GUID   AlgGuid;
    UINT32     BlobSize;
    UINT8      *Blob;
} PEI_CRYPT_HANDLE;

/**
  The function locates a FwKey Hob pointing to a
  Platform Signing Key (PK) inside FV_BB ffs

  @param[out]  pFwKeyHob Pointer to pFwKeyHob

  @retval     Status
    EFI_SUCCESS               The Key Hob was found
    EFI_NOT_FOUND             The Key Hob not found
**/

EFI_STATUS
CryptoGetFwKeyHob (
    IN OUT FW_KEY_HOB **pFwKeyHob
){
    EFI_STATUS       Status = EFI_NOT_FOUND;
    CONST EFI_PEI_SERVICES **PeiServices;
    VOID            *FirstHob;

    PeiServices = GetPeiServicesTablePointer ();
    if (*PeiServices == NULL) ASSERT_EFI_ERROR (EFI_NOT_FOUND);
    (*PeiServices)->GetHobList(PeiServices, &FirstHob);
    if (!FirstHob) {ASSERT_EFI_ERROR (EFI_NOT_FOUND);return EFI_NOT_FOUND;}

    while ( !EFI_ERROR(Status = FindNextHobByType(EFI_HOB_TYPE_GUID_EXTENSION, &FirstHob)) ) {
     if ( CompareGuid(&((EFI_HOB_GUID_TYPE*)FirstHob)->Name, &gPRKeyGuid) ) {
         break;
     }
    }
    if (!EFI_ERROR(Status)) 
        *pFwKeyHob = (FW_KEY_HOB *)FirstHob;

    return Status;
}

/**
  Function returns Ptr to a Platform Signing Key (PK) Ffs inside Recovery FV (FV_BB or similar)

  @param[in]   KeyAlgorithm Points to the EFI_GUID which identifies the PKpub algorithm to use.
  @param[out]  PublicKey    Handle to a key used to return a ptr to a Key. This handle must be identifying a public key.

  @retval     Status
    EFI_SUCCESS               The Key is successfully returned.
    EFI_NOT_FOUND             The Key not found
    EFI_ACCESS_DENIED         The key could not be used in signature operation.
    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
                              of the underlying signature algorithm.
**/
EFI_STATUS
GetKey (
  IN CONST EFI_GUID          *KeyAlgorithm, // reserved to PKPUB_KEY_GUID
  IN OUT PEI_CRYPT_HANDLE        *PublicKey
  )
{
    EFI_STATUS      Status;
    FW_KEY_HOB *pFwKeyHob;

    if(PublicKey == NULL /*|| KeyAlgorithm == NULL*/)
        return EFI_INVALID_PARAMETER;

    // now only supporting PKpub key comparison
//    if(CompareGuid((EFI_GUID*)KeyAlgorithm, &gPRKeyGuid)==0)
//        return EFI_INVALID_PARAMETER;

    // Acquire FwKey hob
    pFwKeyHob = NULL;
    Status = CryptoGetFwKeyHob(&pFwKeyHob);
    if (!EFI_ERROR(Status)) {
//        PublicKey->AlgGuid = pFwKeyHob->KeyGuid;
        CopyGuid (&PublicKey->AlgGuid, &pFwKeyHob->KeyGuid);
        if(pFwKeyHob->Header.Header.HobLength > sizeof(FW_KEY_HOB))
            PublicKey->Blob = (UINT8*)((UINTN)pFwKeyHob+sizeof(FW_KEY_HOB));
        else
            PublicKey->Blob = (UINT8*)(UINTN)(pFwKeyHob->KeyAddress);

        PublicKey->BlobSize = pFwKeyHob->KeySize;
    } 
    return Status;
}
/**
  Function verifies that the specified signature matches the specified hash. 
  Verifies the RSA-SSA signature with EMSA-PKCS1-v1_5 encoding scheme defined in
  RSA PKCS#1.
  This function decrypts the signature with the provided key and then compares 
  the decrypted value to the specified hash value

  @param[in]  PublicKey     Handle to a key used for verifying signatures. This handle must be identifying a public key.
  @param[in]  Hash          Handle of the hash object to verify.
  @param[in]  Signature     Pointer to the signature data to be verified.
  @param[in]  SignatureSize The size, in bytes, of the signature data.
  @param[in]  Flags        Specifies additional flags to further customize the signing/verifying behavior.

  @retval     Status
    EFI_SUCCESS               The signature is successfully verified.
    EFI_SECURITY_VIOLATION    The signature does not match the given message.
    EFI_ACCESS_DENIED         The key could not be used in signature operation.
    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
                              of the underlying signature algorithm.
**/
EFI_STATUS
VerifySig
(
  IN PEI_CRYPT_HANDLE            *PublicKey,
  IN PEI_CRYPT_HANDLE            *Hash,
  IN VOID                        *Signature,
  IN UINTN                       SignatureSize,
  IN UINT32                      Flags
  )
{
    EFI_STATUS      Status;
    INTN            err;
    struct          crypto_rsa_key *key = NULL;
    size_t         *sig_len=(size_t*)&SignatureSize;
    INT32           pss_modulus_bitlen;
    INT32           pss_saltlen;
    UINT32          HashLen;
    UINT8           DecriptedSig[DEFAULT_RSA_SIG_LEN];

// Only supporting RSASSA_PKCS1V15 signature types
    if(!((Flags & EFI_CRYPT_RSASSA_PKCS1V15) || 
         (Flags & EFI_CRYPT_RSASSA_PSS)) )
            return EFI_INVALID_PARAMETER;

    ResetCRmm();

// check Key handle if requested PubKey is a Platform FW Key
// In this case use the FW key from ffs image
// validity of the Key must be verified prior to calling VerifySig
// Guid must match one of the valid keys we can use in PEI Sig verification.
// For now Public Key is supported in 2 formats: RAW 256 bytes and ASN.1 Integer
// shall be extended to gPBkey_x509_Guid
    if(CompareGuid(&PublicKey->AlgGuid, &gEfiCertRsa2048Guid)==0)
        return EFI_INVALID_PARAMETER;

    key = crypto_import_rsa2048_public_key(PublicKey->Blob, PublicKey->BlobSize, (UINT8*)&KeyE, LenE);

    if(key == NULL )
        err = -1;
    else
        err = crypto_rsa_exptmod((const UINT8*)Signature, (size_t)SignatureSize, (UINT8*)&DecriptedSig, sig_len, key, 0);
// locate Hash inside the decrypted signature body and compare it with given Hash;
// Should be extended to handle sha1, sha256 hashes. use Hash->AlgGuid to determine the Hash type
    if(!err) 
    {
        HashLen = SHA256_DIGEST_SIZE;
        if(Flags & EFI_CRYPT_RSASSA_PKCS1V15)
        {
            // Validate PKCS#1v1.5 Padding
            err = pkcs_1_v1_5_decode((const UINT8 *)Hash->Blob, HashLen, (const UINT8 *)&DecriptedSig, (unsigned long)*sig_len);
        } else { //(Flags & EFI_CRYPT_RSASSA_PSS))
            // Validate PKCS#1 PSS Signature: padding & hash
            pss_saltlen = (PssSaltlen!=0)?(INT32)PssSaltlen:HashLen;
            pss_modulus_bitlen = DEFAULT_RSA_SIG_LEN << 3;
            err = pkcs_1_pss_decode(
                    Hash->Blob, HashLen, 
                    (const unsigned char *)&DecriptedSig, (unsigned long)*sig_len, 
                    pss_saltlen,  pss_modulus_bitlen);
        }
    }

    Status = !err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION;

    // clear memory heap on exit
    ResetCRmm();

    return Status;
}
/**
  Function compares the input PublicKey against Platform Signing Key (PK) image in the flash.

  @param[in]   KeyAlgorithm    Points to the EFI_GUID which identifies the PKpub algorithm to use.
  @param[in]   PublicKey       Handle to a key used for verifying signatures.  This handle must be identifying a public key.

  @retval     Status
    EFI_SUCCESS               The Key is successfully verified.
    EFI_SECURITY_VIOLATION    The Key does not match current FW key.
    EFI_ACCESS_DENIED         The key could not be used in signature operation.
    EFI_INVALID_PARAMETER     The size of input message or signature does not meet the criteria 
                              of the underlying signature algorithm.
**/
EFI_STATUS
VerifyKey
(
  IN CONST EFI_GUID          *KeyAlgorithm, // reserved to PKPUB_KEY_GUID
  IN PEI_CRYPT_HANDLE        *PublicKey
  )
{
    EFI_STATUS    Status;
    int           err;
    PEI_CRYPT_HANDLE KeyHndl;
    UINT8         Hash[SHA256_DIGEST_SIZE] = {0};
    UINT8         *KeyBuf, *PKpubBuffer=NULL;
    size_t        KeyLen;

    if(PublicKey == NULL || KeyAlgorithm == NULL || PublicKey->Blob == NULL)
        return EFI_INVALID_PARAMETER;

// check Key handle if requested PubKey is a Platform Key PKpub.
// In this case use PKpub key from ffs image
//    if(CompareGuid((EFI_GUID*)KeyAlgorithm, &gPRKeyGuid)==0)
//        return EFI_INVALID_PARAMETER;
    
    Status = GetKey(KeyAlgorithm, &KeyHndl);
    if(EFI_ERROR(Status))
        return Status;

    PKpubBuffer = KeyHndl.Blob;
    KeyLen = (size_t)KeyHndl.BlobSize; // always 256
    KeyBuf = PublicKey->Blob;
//  FWKey : hash
    if(CompareGuid(&KeyHndl.AlgGuid, &gEfiCertSha256Guid)==0){
        return EFI_SECURITY_VIOLATION;
    }
    KeyBuf = Hash;
    //    pubkey : Rsa2048 - hash it
//        if(CompareGuid(&PublicKey->AlgGuid, &gEfiCertRsa2048Guid) ){
    // SHA256 Hash of RSA Key
        KeyLen = (size_t)PublicKey->BlobSize;
        sha256_vector(1, (const UINT8**)&PublicKey->Blob, (const size_t*)&KeyLen, KeyBuf);
//        } 

//    KeyLen = SHA256_DIGEST_SIZE;
    err = MemCmp(PKpubBuffer, KeyBuf, SHA256_DIGEST_SIZE);

    return (!err ? EFI_SUCCESS:EFI_SECURITY_VIOLATION);
}

/**
The Rom image hash is calculated according to Rom Area map

 @param[in]   ThisPpi - pointer to a FvDxeValidatePpi struct
 @param[in]   FvSigHeader - pointer to a FW Capsule Hdr

 @retval      Status 
              EFI_SUCCESS            Your hash is in the output buffer
              EFI_SECURITY_VIOLATION Something went wrong
**/
EFI_STATUS HashFwRomMapImage (
    IN AMI_FV_DXE_VALIDATE_PPI  *ThisPpi,
    IN CONST EFI_PEI_SERVICES   **PeiServices,
    IN APTIO_FW_CAPSULE_HEADER  *FvSigHeader
){
    EFI_STATUS  Status;
    ROM_AREA    *RomAreaTbl;
    UINTN        RomSize = FLASH_SIZE;
    UINTN        i,ii,max_num_elem, num_elem;
    FwHashManifestHdr *MfstHdr;
    UINT8       *HashTbl, *HashTbl1;
    UINTN        DigestLen;

    UINTN *AddrList;
    UINTN *LenList;
    UINTN *HashList;
    UINT8 *Addr;
    UINTN Size;

    UINTN  HobSize;
    AMI_FV_DIGEST_INFO_HOB *pHob;
    AMI_FV_DIGEST_PPI       *pFvDigestPpi;

    MfstHdr = (FwHashManifestHdr*)((UINTN)FvSigHeader+FvSigHeader->RomLayoutOffset);
    RomAreaTbl = (ROM_AREA*)((UINTN)MfstHdr + MfstHdr->HeaderSize);
    HashTbl = (UINT8*)((UINTN)MfstHdr + MfstHdr->HashAreaOffset);
    DigestLen = SHA256_DIGEST_SIZE;

    if(AMI_TDXE_SHA256 != (int)MfstHdr->HashType ||
       DigestLen != MfstHdr->HashSize)
        return EFI_UNSUPPORTED;

    max_num_elem = MfstHdr->NumberOfDescriptors;
    // at least one signed range must be included
    if(max_num_elem == 0) return EFI_UNSUPPORTED;
    ii = (max_num_elem+1)*sizeof(UINTN); // add a NULL terminator
    //ii*3=AddrLis+LenList+HashList + HashTbl=max_num_elem*DigestLen
    HobSize = sizeof(AMI_FV_DIGEST_INFO_HOB)+(ii*3)+(max_num_elem*DigestLen);
    if (*PeiServices == NULL) {ASSERT_EFI_ERROR (EFI_INVALID_PARAMETER); return EFI_INVALID_PARAMETER;}
    Status = (*PeiServices)->CreateHob( PeiServices,EFI_HOB_TYPE_GUID_EXTENSION,(UINT16)HobSize,(void**)&pHob);
    //AMI_FV_DIGEST_PPI + ii*3=AddrLis+LenList+HashList + HashTbl=max_num_elem*DigestLen
    DEBUG ((DEBUG_INFO, "AddrList Hob %X [sz %X, LenOffs %X]...%r\n", pHob, HobSize, ii, Status));
    if (EFI_ERROR(Status))  return Status;
    CopyGuid (&(pHob->Header.Name), &gAddrListHobGuid);
    pHob->LenListOffs = ii;
    AddrList = (UINTN*)((UINTN)pHob + sizeof(AMI_FV_DIGEST_INFO_HOB));
    LenList  = (UINTN*)((UINTN)AddrList+ ii);
    HashList = (UINTN*)((UINTN)LenList + ii);
    HashTbl1 = (UINT8*)((UINTN)HashList + ii);
    MemSet(AddrList, HobSize-sizeof(AMI_FV_DIGEST_INFO_HOB), 0);
    pFvDigestPpi = (AMI_FV_DIGEST_PPI*)&pHob->FvDigestPpi.HashElemCnt;
    pFvDigestPpi->AddrList  = AddrList;
    pFvDigestPpi->LenList   = LenList;
    pFvDigestPpi->HashList  = HashList;
    pFvDigestPpi->HashElemCnt = 0;
    pFvDigestPpi->HashSize  = DigestLen;
    pFvDigestPpi->HashAlgId = AMI_TDXE_SHA256;

    num_elem = 0;
    Status = EFI_SUCCESS;
    PERF_START (NULL, "Hash", NULL, 0);
    for(i=0; i < max_num_elem && RomAreaTbl[i].Size != 0 && (UINTN)HashTbl+(i*DigestLen) <= (UINTN)FvSigHeader+FvSigHeader->RomImageOffset; i++)
    {
        if(!IsFvMeasured(RomAreaTbl[i].Attributes) ||
           !(RomAreaTbl[i].Attributes & AMI_ROM_AREA_SIGNED))
            continue;

        // sanity check for buffer overruns
        if(RomAreaTbl[i].Offset > RomSize ||
           ((UINT64)RomAreaTbl[i].Offset + RomAreaTbl[i].Size) > RomSize ) {
            Status = EFI_SECURITY_VIOLATION;
            break;
        }
        Addr = (UINT8*)(UINTN)RomAreaTbl[i].Address;
        Size = RomAreaTbl[i].Size;
        HashList[num_elem] = (UINTN)HashTbl1+(num_elem*DigestLen);
        sha256_vector(1, (const UINT8**)&Addr, (const size_t*)&Size, (UINT8*)(UINTN)(HashList[num_elem]));
        if(0 != MemCmp((VOID*)((UINTN)HashList[num_elem]), (VOID*)((UINTN)HashTbl+(i*DigestLen)), DigestLen) ){
            DEBUG_CODE (
                    DEBUG ((DEBUG_INFO, "\n%02d:Hashed Range: %8lX-%X Attr %X\n", i+1, RomAreaTbl[i].Address, RomAreaTbl[i].Size, RomAreaTbl[i].Attributes ));
                    for (ii=0; ii<4; ii++) DEBUG ((DEBUG_INFO,"%02X ", *(UINT8*)(UINTN)(HashList[num_elem]+ii) ));
                    DEBUG ((DEBUG_INFO, "...\nFAIL!!!\n"));
            );
            Status = EFI_SECURITY_VIOLATION;
            if(IsFvPeiAfterMem(RomAreaTbl[i].Attributes)) {
                ThisPpi->bFvDxeFvPeiMemValid = FALSE;
                break;
            }
            continue;
        }
        AddrList[num_elem] = (UINTN)Addr;
        LenList[num_elem] = Size;
        num_elem++;
    }
    PERF_END (NULL, "Hash", NULL, 0);
    DEBUG ((DEBUG_INFO, "\nHash Mfst(%r),Hash size %d, Valid ranges %d(%d)\n", Status,DigestLen,num_elem,i));
    // at least one signed range must be included
    if(num_elem == 0 || num_elem > max_num_elem) return EFI_SECURITY_VIOLATION;;
    pFvDigestPpi->HashElemCnt = num_elem;
    if(EFI_ERROR(Status)) return Status;

    // for backward compatibility with TCG
    CopyMem((VOID *)&pFvDigestPpi->FvHash, (VOID *)HashList[0], DigestLen);
    //-----------------------------------------------------------------------------------
    // Install FvDigestPPI
    //-----------------------------------------------------------------------------------
    Status = InstallFvDigestPpi(PeiServices, pFvDigestPpi);
    ASSERT_EFI_ERROR(Status);

    return Status;
}

/**
This code verifies the signature for the measured FV DXE regions, 
 and performs following checks on the image:
  1. Signing certificate is signed with trusted Root Platform key
  2. Integrity check. Image Signature verification
Validate  Root Certificate 
   -Compare PubKey in Root Certificate Hdr with local FW Platform Key
   -Hash SignCert.PubKey 
   -VerifySig for RootCert.Signature and compare with SignCert.Key hash
 Validate  Sign Certificate 
   -Hash the ROM image inside the FW Capsule
   -VerifySig for SignCert.Signature and compare with calculated hash

@param[in]   ThisPpi - pointer to a FvDxeValidatePpi struct
@param[in]   FvSigHeader - pointer to a FW Capsule Hdr

 @retval     Status
             EFI_SUCCESS               The signature is successfully verified.
             EFI_SECURITY_VIOLATION    The signature does not match the given message.
**/
EFI_STATUS VerifyFwCertRsa2048Sha256 (
    IN AMI_FV_DXE_VALIDATE_PPI  *ThisPpi,
    IN APTIO_FW_CAPSULE_HEADER  *FvSigHeader
){
    EFI_STATUS              Status;
    PEI_CRYPT_HANDLE        PubKeyHndl;
    PEI_CRYPT_HANDLE        HashHndl;
    UINT8                   *pSig;
    UINT32                  Flags;
    UINT8                   *Addr;
    UINTN                   Size;
    EFI_CERT_BLOCK_RSA_2048_SHA256* pRootCert;
    FwHashManifestHdr       *MfstHdr;
    UINT8 HashDB[SHA256_DIGEST_SIZE];

    if(CompareGuid((EFI_GUID*)&FvSigHeader->FWCert.SignCert.Hdr.CertType, &gEfiCertTypeRsa2048Sha256Guid)==0) {
        DEBUG((DEBUG_ERROR,"Invalid Certificate type %g\n",(EFI_GUID*)&FvSigHeader->FWCert.SignCert.Hdr.CertType));
        return EFI_UNSUPPORTED;
    }

    Flags = (FvSigHeader->CapHdr.Flags & CAPSULE_FLAGS_RSA_PSS_PADDING_SCHEME)?EFI_CRYPT_RSASSA_PSS:EFI_CRYPT_RSASSA_PKCS1V15;

    HashHndl.AlgGuid  = gEfiHashAlgorithmSha256Guid;
    HashHndl.BlobSize = SHA256_DIGEST_SIZE;
    HashHndl.Blob = &HashDB[0];
//
// 1. Compare Capsule's Sign Cert key with Platform Root Key
//
    PubKeyHndl.BlobSize =  DEFAULT_RSA_KEY_MODULUS_LEN;
    PubKeyHndl.AlgGuid = gEfiCertRsa2048Guid;
    PubKeyHndl.Blob = (UINT8*)FvSigHeader->FWCert.SignCert.CertData.PublicKey;
    Status = VerifyKey(&gPRKeyGuid, &PubKeyHndl);
    DEBUG ((DEBUG_INFO, "Compare Platform and SignCert Keys : %r\n", Status));
    //  Skip the RootCert key checking if SignCert Key and PR Key are matching
    if(EFI_ERROR(Status)) {
    //
    // 1.1 Verify Signed Certificate key chain to a Platform Root key
    //
        for (pRootCert = &FvSigHeader->FWCert.RootCert; 
             (UINTN)pRootCert < ((UINT64)(UINTN)&FvSigHeader->FWCert+FvSigHeader->FWCert.SignCert.Hdr.Hdr.dwLength) &&
                 pRootCert->PublicKey[0]!=0;
             pRootCert++) 
        {
            PubKeyHndl.Blob = (UINT8*)pRootCert->PublicKey;
            Status = VerifyKey(&gPRKeyGuid, &PubKeyHndl); 
            DEBUG ((DEBUG_INFO, "Compare Platform and RootCert Keys : %r\n", Status));
            if (EFI_ERROR(Status)) continue;
            //
            // 2. Verify RootCert.Signature
            //
            // 2.1  Compute FWCert.SignCert.PublicKey Hash
            // 
            if(FvSigHeader->CapHdr.Flags & CAPSULE_FLAGS_SIGNKEY_IN_ROOTCERT)
            {
                Addr = (UINT8*)FvSigHeader->FWCert.SignCert.CertData.PublicKey;
                Size = DEFAULT_RSA_KEY_MODULUS_LEN;
            } else
            // 2.2  Compute FWCert.SignCert Hash
            {
                Addr = (UINT8*)&FvSigHeader->FWCert.SignCert;
                Size = sizeof(AMI_CERTIFICATE_RSA2048_SHA256);
            }
            sha256_vector(1, (const UINT8**)&Addr, (const size_t*)&Size, HashHndl.Blob);

            pSig = (void*)pRootCert->Signature; 
            Status = VerifySig(&PubKeyHndl, &HashHndl, pSig, DEFAULT_RSA_SIG_LEN, Flags ); 
            DEBUG ((DEBUG_INFO, "Verify Root Cert : %r\n", Status));
            break;
        }
    }
    if (EFI_ERROR(Status)) return EFI_SECURITY_VIOLATION;
//
// 3. Verify Signing Cert
//
// 3.1 Calculate the hash of the Rom Table Manifest
//
    MfstHdr = (FwHashManifestHdr*)((UINTN)FvSigHeader+FvSigHeader->RomLayoutOffset);
    if (AMI_TDXE_SHA256 != (int)MfstHdr->HashType) 
        return EFI_SECURITY_VIOLATION;

    Addr = (UINT8*)(UINTN)MfstHdr;
    Size = MfstHdr->TableSize;
    sha256_vector(1, (const UINT8**)&Addr, (const size_t*)&Size, HashHndl.Blob);

    pSig = (void*)FvSigHeader->FWCert.SignCert.CertData.Signature; 
    PubKeyHndl.Blob = (UINT8*)FvSigHeader->FWCert.SignCert.CertData.PublicKey;

    PERF_START (NULL, "Pkcs1", NULL, 0);
    Status = VerifySig(&PubKeyHndl, &HashHndl, pSig, DEFAULT_RSA_SIG_LEN, Flags);
    PERF_END (NULL, "Pkcs1", NULL, 0);
    return Status;
}

/**
 Return size of FV header, including ExtHeader

 @param[in] Address - Address of FV to search in

 @retval    Fv Hdr size
**/
UINT32 GetFvHeaderSize(
    VOID *Address
){
    EFI_FIRMWARE_VOLUME_HEADER *FwVolHeader;
    EFI_FIRMWARE_VOLUME_EXT_HEADER *FwVolExtHeader;

    FwVolHeader = (EFI_FIRMWARE_VOLUME_HEADER *)Address;
    if (   FwVolHeader->Signature!=EFI_FVH_SIGNATURE//FV_SIGNATURE
        || FwVolHeader->HeaderLength != (UINT16)(sizeof(EFI_FIRMWARE_VOLUME_HEADER)+sizeof(EFI_FV_BLOCK_MAP_ENTRY))
    ) return 0;
    if (FwVolHeader->ExtHeaderOffset == 0){
        return (UINT32)FwVolHeader->HeaderLength;
    }else {
        UINT32 HeaderSize;
        UINT32 MaxOffset =  MAX_FV_STORE_HEADER_SIZE - sizeof(EFI_FFS_FILE_HEADER) - sizeof(EFI_FIRMWARE_VOLUME_EXT_HEADER);
        UINT32 MaxSize;

        if (   FwVolHeader->ExtHeaderOffset < FwVolHeader->HeaderLength
            || FwVolHeader->ExtHeaderOffset > MaxOffset
        ) return 0;

        MaxSize =   MAX_FV_STORE_HEADER_SIZE - sizeof(EFI_FFS_FILE_HEADER) - sizeof(EFI_FIRMWARE_VOLUME_HEADER) - sizeof(EFI_FV_BLOCK_MAP_ENTRY);
        FwVolExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *) ((UINT8*)FwVolHeader + FwVolHeader->ExtHeaderOffset);
        if (   FwVolExtHeader->ExtHeaderSize < sizeof(EFI_FIRMWARE_VOLUME_EXT_HEADER)
            || FwVolExtHeader->ExtHeaderSize > MaxSize
        ) return 0;
        HeaderSize = FwVolHeader->ExtHeaderOffset + FwVolExtHeader->ExtHeaderSize;
        return ALIGN_VALUE(HeaderSize,8);
    }
}
/**
 This service will discover firmware files of FREEFORM type by a 
 File GUID and a Section GUID.


 @param[in] FvAddress - Address of FV to search in
 @param[in] FvSize - Size of FV to search in

 @param[out] Ffs - returns a pointer to FFs Hdr

 @retval     Status
**/
EFI_FFS_FILE_HEADER *
GetFvMfstSigFfs (
    IN UINT64    FvAddress,
    IN UINT32    FvSize
)
{
  EFI_FFS_FILE_HEADER  *ppFile;
  UINT32                FvHdrSize;
  UINTN                 Index;
//FvDxe ffs
  static EFI_GUID  gFvMfstFFSGuid   = {0x68d1fed0, 0x143e, 0x479c, {0xbf, 0x39, 0x45, 0x6e, 0x98, 0xb4, 0xfa, 0xc5}};
  static EFI_GUID gFvMfstFfsSecGuid = {0x72a45c4b, 0xf348, 0x408f, {0xb9, 0x13, 0xf7, 0x83, 0x9f, 0x24, 0x7c, 0xe2}};
// FwCap ffs
//  static EFI_GUID    gFvMfstFFSGuid = {0x414D94AD,0x998D,0x47D2,{0xBF,0xCD,0x4E,0x88,0x22,0x41,0xDE,0x32}};
//  static EFI_GUID gFvMfstFfsSecGuid = {0x5A88641B,0xBBB9,0x4AA6,{0x80,0xF7,0x49,0x8A,0xE4,0x07,0xC3,0x1F}};

  if (!FvSize || !FvAddress)
    return NULL;

  FvHdrSize = GetFvHeaderSize((VOID*)(UINTN)FvAddress);
  ppFile = (EFI_FFS_FILE_HEADER*)((UINTN)FvAddress + FvHdrSize);
  Index = 0;
  while(((UINT64)(UINTN)ppFile > FvAddress) && 
        ((UINT64)(UINTN)ppFile < (FvAddress+FvSize))
        )
  {
      Index++;
      if(ppFile->Type == EFI_FV_FILETYPE_FREEFORM &&
         CompareGuid(&gFvMfstFFSGuid, &(ppFile->Name)) &&
         CompareGuid(&gFvMfstFfsSecGuid, &(((AMI_FFS_COMMON_SECTION_HEADER*)ppFile)->GuidedSection.SubTypeGuid))
      ){
          DEBUG ((DEBUG_INFO, "%d:Ffs %8X(%X)=%g, Type %2X\n", Index, (UINTN)ppFile, ((*(UINT32 *)ppFile->Size) & 0xffffff), &gFvMfstFFSGuid, ppFile->Type));
          DEBUG ((DEBUG_INFO, "===>FvMfstSig Ffs found\n"));
          return ppFile;
      }
      FvHdrSize = ALIGN_VALUE(((*(UINT32 *)ppFile->Size) & 0xffffff), 8);
      ppFile = (EFI_FFS_FILE_HEADER*)((UINT8*)ppFile+FvHdrSize);
  }
  return NULL;
}

/**
This function finds the FvSig Header inside FV, by traversing each Ffs within FV

 @param FvAddress     FV address
 @param Size          Size of the FV
 @param FvSigHeader   FvSig Header pointer

 @retval EFI_SUCCESS  Found guided encrypted section.
**/
EFI_STATUS
LocateFvMfstSigHeader(
  UINT64                     FvAddress,
  UINT32                     Size,
  APTIO_FW_CAPSULE_HEADER  **FvSigHeader
) {
  APTIO_FW_CAPSULE_HEADER   *pFvSigHeader;
  AMI_FFS_COMMON_SECTION_HEADER *FvSigFfs;
  FwHashManifestHdr *MfstHdr;

  FvSigFfs = (AMI_FFS_COMMON_SECTION_HEADER *)GetFvMfstSigFfs(FvAddress, Size);
  if( FvSigFfs ){
      pFvSigHeader = (APTIO_FW_CAPSULE_HEADER*)(FvSigFfs->pFvSigHeader);
      // just a sanity check - Cap Size must match the Section size
      if( (((*(UINT32 *)FvSigFfs->FfsHdr.Size) & 0xffffff) == 
             pFvSigHeader->CapHdr.HeaderSize + sizeof(AMI_FFS_COMMON_SECTION_HEADER)) &&
             CompareGuid((EFI_GUID*)&pFvSigHeader->CapHdr.CapsuleGuid, &gFWCapsuleGuid) && 
            (pFvSigHeader->CapHdr.Flags & CAPSULE_FLAGS_EXT_ROM_LAYOUT_TABLE)
      ){
          MfstHdr = (FwHashManifestHdr*)((UINTN)pFvSigHeader+pFvSigHeader->RomLayoutOffset);
          // More Hdr fields sanity checks for buffer overruns
          // Signed Aptio Capsule only supports WIN_CERT_TYPE_EFI_GUID 
          if(pFvSigHeader->FWCert.SignCert.Hdr.Hdr.wCertificateType != WIN_CERT_TYPE_EFI_GUID ||
             pFvSigHeader->RomLayoutOffset< (UINT64)pFvSigHeader->FWCert.SignCert.Hdr.Hdr.dwLength + offsetof(APTIO_FW_CAPSULE_HEADER, FWCert) ||
// check MFST
             MfstHdr->Signature != AMI_HASH_MANIFEST_SIGNATURE || //0x4C4D4F52;
             MfstHdr->Version != 2 || 
             MfstHdr->DesriptorSize != sizeof(ROM_AREA) ||
             (UINT64)pFvSigHeader->RomLayoutOffset + MfstHdr->TableSize > pFvSigHeader->CapHdr.HeaderSize ||
             (UINT64)pFvSigHeader->RomLayoutOffset + sizeof(FwHashManifestHdr)+2*sizeof(ROM_AREA) + 2*sizeof(SHA256_DIGEST_SIZE) > pFvSigHeader->CapHdr.HeaderSize
          ) {
              DEBUG ((DEBUG_ERROR, "FvDxeSig Hdr invalid\n"));
              return EFI_SECURITY_VIOLATION;
          }
          DEBUG ((DEBUG_INFO, "===>FvDxeSig Hdr found at %8X\n", (UINTN)pFvSigHeader));
          *FvSigHeader = pFvSigHeader;
          return EFI_SUCCESS;
      }
  }
  // header ffs is not found
  return EFI_NOT_FOUND;
}
/**
Verifies FVs with Measured attribute i.e., DXE, DXE2, BDS, PEI_MEM
Relocates FVs to RAM before verification

 @param[in] ThisPpi Pointer to the Ppi data structure.
 @param[in] PeiServices Pointer to the Pointer to the Pei Services Table.
 @param[in] AmiRomArea Pointer to the AMI_ROM_AREA with an address of FV to be validated
 @param[out] AmiRomArea->Address to be updated with an address in memory the FV is relocated to

 @retval EFI_STATUS  Volume should be published
**/
EFI_STATUS EFIAPI
VerifyFvDxe (
    IN AMI_FV_DXE_VALIDATE_PPI  *ThisPpi,
    IN CONST EFI_PEI_SERVICES   **PeiServices,
    IN OUT AMI_ROM_AREA         *AmiRomArea
) {
    EFI_STATUS    Status;
    IN APTIO_FW_CAPSULE_HEADER  *FvSigHeader;
    AMI_ROM_AREA *Area;
    BOOLEAN      bRangeValid;
    ROM_AREA     *Area1, *RomAreaTbl;
    FwHashManifestHdr *MfstHdr;

    if(PeiServices == NULL || ThisPpi == NULL)
        return EFI_NOT_READY;

    // Skip full function re-run if previous FV test was successful
    if(ThisPpi->bFvDxeProcessed) {
        Status = (ThisPpi->bFvDxeSigStatus && ThisPpi->bFvDxeMfstStatus)?EFI_SUCCESS:EFI_SECURITY_VIOLATION;
        DEBUG((DEBUG_INFO, "VerifyFvDxe : %r\n", Status));
        return Status;
    }
/*
 * TBD
 * Each FV can be signed individually and have FvDxeSig.ffs for the single FV range
 * If input "Area" parameter is NULL -> verify all FVs in a loop, else 
 *  verify each FV area individually.
 * Common flow: if FV Measured attrib. -> relocate(PCD policy), locate FvDxesig.ffs, VerifySig, InstallDigestPPI 
 * 
 * for(Area0 = AmiGetFirstRomArea(); Area0 != NULL; Area0 = AmiGetNextRomArea(Area0)) {
 *  
 *  Search for FvDxesig.ffs in Area 
 *    If Found -> 
 *     update RomRanges in FvSig rom map with addresses in MEM 
 *     1. run validation
 *     2. set ThisPpi->bFvDxeSigStatus to TRUE/FALSE
 * 
 *   Continue to next Area to search for signed FvDxeSig
 *  }
 *  Pros: Allow to sign each FV individually by ODM, OEM IBV etc., so they can be replaced in the BIOS image individually
 *        TCG must locate all instances of FvDigestPPI to extend each measured FV digest to the PCR0
 */
    PERF_START (NULL, "T-Dxe", NULL, 0);
    FvSigHeader = NULL;
    for(Area = AmiGetFirstRomArea(); Area != NULL; Area = AmiGetNextRomArea(Area)) {
        DEBUG ((DEBUG_INFO, "FV %8lX(%8X), Attr %4X\n", Area->Address, Area->Size, Area->Attributes));
        if(!IsFvMeasured(Area->Attributes) )
            continue;
        if(FvSigHeader == NULL) {
            if(!EFI_ERROR(LocateFvMfstSigHeader(Area->Address, Area->Size, &FvSigHeader)))
                break;
        }
    }

    ThisPpi->bFvDxeProcessed = TRUE;
    ThisPpi->bFvDxeSigStatus = FALSE;
    ThisPpi->bFvDxeMfstStatus = FALSE;
    ThisPpi->bFvDxeFvPeiMemValid = TRUE;

    if(FvSigHeader != NULL) {
        // Validate HashManifest
        Status = VerifyFwCertRsa2048Sha256(ThisPpi, FvSigHeader);
        DEBUG((DEBUG_INFO, "Verify FvDxe Signature: %r\n", Status));
    } else {
        DEBUG((DEBUG_ERROR,"FvDxeSig Hdr not found\n"));
        Status = EFI_NOT_FOUND; // go straight to recovery
    }
    if(EFI_ERROR(Status)) {
        PERF_END (NULL, "T-Dxe", NULL, 0);
        return Status;
    }
    ThisPpi->bFvDxeSigStatus = TRUE;
    /*
     * Validate FvSigHdr RomArea ranges exist for each measured area in the global RomLoayout
     * The check is needed to catch invalid FvDxe RomMap with empty or fixed range(s)
     *
     * Loop till Area1->Offset == Area->Offset
     *   in all entries with Area1->Offset >= Area->Offset && 
     *                       Area1->Offset <  Area->Offset+Area->Size
     */
    MfstHdr = (FwHashManifestHdr*)((UINTN)FvSigHeader+FvSigHeader->RomLayoutOffset);
    RomAreaTbl = (ROM_AREA*)((UINTN)MfstHdr + MfstHdr->HeaderSize);
    for(Area = AmiGetFirstRomArea(); Area != NULL; Area = AmiGetNextRomArea(Area)) {
        if(!IsFvMeasured(Area->Attributes) )
            continue;
        bRangeValid = FALSE;
        for(Area1 = RomAreaTbl; Area1->Size != 0; Area1++) {
            if(!IsFvMeasured(Area1->Attributes) || !(Area1->Attributes & AMI_ROM_AREA_SIGNED))
                continue;
            if(Area1->Offset >= Area->Offset && ((Area1->Offset + Area1->Size) <= (Area->Offset + Area->Size)) ) {
                bRangeValid = TRUE;
                DEBUG((DEBUG_INFO, "--->TstRange: %8lX-%X\n", Area1->Address, Area1->Size));
            }
        }
        if(bRangeValid == FALSE) {
            DEBUG((DEBUG_ERROR,"Invalid FvDxe Hdr RomMap\n"));
            PERF_END (NULL, "T-Dxe", NULL, 0);
            return EFI_NOT_FOUND; // go straight to recovery
        }
    }
    // Verify Mftst Hash ranges
    Status = HashFwRomMapImage(ThisPpi, PeiServices, FvSigHeader);
    DEBUG((DEBUG_INFO, "FV Hash Mfst %r\n", Status ));
    if(!EFI_ERROR(Status)) {
        ThisPpi->bFvDxeMfstStatus = TRUE; // All FvDxe Mfst Hashes are Valid
    }
    PERF_END (NULL, "T-Dxe", NULL, 0);

    return Status;
}
//---------------------------------------------------------------------------------------------------
// End PPI
//---------------------------------------------------------------------------------------------------

/* pre-mem
 * Direct call to InstallFvDxeVerifyPpi()
 * Install FvDxeValidate Ppi(once in pre-mem)
 * Launch FvDxe Verify (Area = NULL)
 *    Create hash Hob, Install FvDigestppi if hash Mfst is valid
 * 
 * after-mem
 * Callback on MemInstalled:
 *   Locate hashHob - 
 *   Update FvDigestPpi fields
 * Callback On PublishFv:
 *   Locate FvDxeValidatePpi
     call FvDxePpi->FvDxeValidate(Area)
 */

/**
 This function will launch FvDxeVerify

 @param PeiServices Pointer to the Pointer to the Pei Services Table.
 @param NotifyDescriptor The notification descriptor for this notification event.
 @param NotifyPpi Pointer to a ppi.

 @retval EFI_SUCCESS If PPI is successfully installed.
*/
EFI_STATUS
LaunchFvDxeVerifyPpi(
    IN EFI_PEI_SERVICES    **PeiServices,
    IN AMI_FV_DXE_VALIDATE_PPI *FvDxeValidatePpi,
    IN AMI_ROM_AREA            *Area
) {
    EFI_STATUS               Status;

    if(FvDxeValidatePpi == NULL) {
        ASSERT_EFI_ERROR(EFI_INVALID_PARAMETER);
        return EFI_INVALID_PARAMETER;
    }

    DEBUG ((DEBUG_INFO, "FvDxeValidatePpi %X... Area %8lX-%X\n", FvDxeValidatePpi, (Area==NULL)?0:Area->Address,(Area==NULL)?0:Area->Size));
    Status = FvDxeValidatePpi->FvDxeValidate(FvDxeValidatePpi, (CONST EFI_PEI_SERVICES **)PeiServices, Area);
    if(Area) {
        if(EFI_ERROR(Status) && 
           FvDxeValidatePpi->bFvDxeProcessed && FvDxeValidatePpi->bFvDxeSigStatus && !FvDxeValidatePpi->bFvDxeMfstStatus ){
            // Can be a Vital PEI_AFTER_MEM containing Recovery PPIs
            // only relevant when recovery is enabled and its Ppis are in FV_BB_AFTER_MEM
            if (PcdGet32(AmiPcdTdxeFailedRecoveryPolicy) == 0 && // 0 - Invoke BIOS recovery process
                IsFvPeiAfterMem(Area->Attributes) && FvDxeValidatePpi->bFvDxeFvPeiMemValid ){
                    Status = EFI_SUCCESS;
            }
            DEBUG((DEBUG_INFO, "Verify (%r), Hash Mfst %a, FV_BB_AFTER_MEM %X(%a)\n",  Status, (FvDxeValidatePpi->bFvDxeMfstStatus)?"Pass":"Fail", IsFvPeiAfterMem(Area->Attributes),(FvDxeValidatePpi->bFvDxeFvPeiMemValid)?"Valid":"Fail"));
        }
        if(!EFI_ERROR(Status)) {
            Status = AmiPublishFvArea(Area);
            DEBUG((DEBUG_INFO, "Publish FV %8lX %r\n", Area->Address, Status));
            ASSERT_EFI_ERROR(Status);
        }
    }
    // on Failure to validate FV DXE -> execute recovery action according to a TDXE Policy
    if (EFI_ERROR(Status)){

        ExecuteActionOnFailureToValidateFv((CONST EFI_PEI_SERVICES**)PeiServices);
    }
    return Status;
}

/**
 The function will publish a FvDigestPpi PPI after successful FV Dxe verification.

 @param pFvDigestPpi Pointer to the AMI_FV_DIGEST_PPI data structure

 @retval EFI_SUCCESS If FV_MAIN is successfully verified.
*/
EFI_STATUS
InstallFvDigestPpi(
    IN CONST EFI_PEI_SERVICES **PeiServices,
    IN AMI_FV_DIGEST_PPI        *pFvDigestPpi
) {
    
    EFI_STATUS              Status;
    EFI_PEI_PPI_DESCRIPTOR *pPpiDesc;
    //--------------------------------------------------------------------------
    //   Allocate dynamic placeholder for Descriptor PPI
    //--------------------------------------------------------------------------
    pPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *)AllocateZeroPool(sizeof(EFI_PEI_PPI_DESCRIPTOR));
    ASSERT (pPpiDesc != NULL);
    if(pPpiDesc == NULL) return EFI_OUT_OF_RESOURCES;

    pPpiDesc->Ppi = (VOID*)pFvDigestPpi;
    pPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    pPpiDesc->Guid = &gAmiFvDigestPpiGuid;
    //------------------------------------------------------------------------
    // Install FvDxeValidatePpi
    //------------------------------------------------------------------------
    Status = (*PeiServices)->InstallPpi (PeiServices, pPpiDesc);
    DEBUG((DEBUG_INFO, "Install FvDigestPpi %X: %r\n", pPpiDesc->Ppi, Status));
    ASSERT_EFI_ERROR(Status);

    return Status;
}

/**
 This callback function will publish a FvDxeValidate PPI
 Execute FvDxeValidate PPI on gAmiPublishFvDxeValidatePpiGuid signal event
 
 @param PeiServices Pointer to the Pointer to the Pei Services Table.
 @param NotifyDescriptor The notification descriptor for this notification event.
 @param NotifyPpi Pointer to a ppi.

 @retval EFI_SUCCESS If PPI is successfully installed.
*/
EFI_STATUS EFIAPI
InstallFvDxeVerifyPpi(
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                      *NotifyPpi
) {
    EFI_STATUS               Status;
    AMI_FV_DXE_VALIDATE_PPI *FvDxeValidatePpi = NULL;
    EFI_PEI_PPI_DESCRIPTOR  *pPpiDesc;
    AMI_PUBLISH_FV_DXE_PPI  *PublishFvDxePpi;
    AMI_ROM_AREA            *Area;

    Status = (*PeiServices)->LocatePpi((CONST EFI_PEI_SERVICES**)PeiServices, &gAmiFvDxeValidatePpiGuid, 0, NULL, (void**)&FvDxeValidatePpi);
    DEBUG((DEBUG_INFO, "NotifyPpi (%X), FvDxeValidatePpi(%X) %r\n", NotifyPpi, FvDxeValidatePpi, Status));
    if(EFI_ERROR(Status)) {

        //------------------------------------------------------------------------
        //    Create PPI with ptr to FvDxe RomMap with the re-mapped addresses
        //    Use PPI inside PublishFV hook and update the Area->Address to RAM
        //------------------------------------------------------------------------
        FvDxeValidatePpi = (AMI_FV_DXE_VALIDATE_PPI *)AllocateZeroPool(sizeof(AMI_FV_DXE_VALIDATE_PPI));
        ASSERT (FvDxeValidatePpi != NULL);    
        if(FvDxeValidatePpi == NULL) return EFI_OUT_OF_RESOURCES;

        FvDxeValidatePpi->FvDxeValidate = VerifyFvDxe;
        //--------------------------------------------------------------------------
        //   Allocate dynamic placeholder for Descriptor PPI
        //--------------------------------------------------------------------------
        pPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *)AllocateZeroPool(sizeof(EFI_PEI_PPI_DESCRIPTOR));
        ASSERT (pPpiDesc != NULL);    
        if(pPpiDesc == NULL) return EFI_OUT_OF_RESOURCES;

        pPpiDesc->Ppi = (VOID*) FvDxeValidatePpi;
        pPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
        pPpiDesc->Guid = &gAmiFvDxeValidatePpiGuid;
        //------------------------------------------------------------------------
        // Install FvDxeValidatePpi
        //------------------------------------------------------------------------
        Status = (*PeiServices)->InstallPpi ((CONST EFI_PEI_SERVICES**)PeiServices, pPpiDesc);
        DEBUG((DEBUG_INFO, "Install FvDxeValidatePpi(%X) PeiServices(%X): %r\n", FvDxeValidatePpi, PeiServices, Status));
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) return Status;
    }
    // Run FvDxeValidate if PublishFvDxePpi is pending or if launched from a PEI entry point...
    PublishFvDxePpi = (AMI_PUBLISH_FV_DXE_PPI *)NotifyPpi;
    DEBUG ((DEBUG_INFO, "PublishFvDxePpi(%X), Area %X(%l8X)\n", PublishFvDxePpi, (PublishFvDxePpi==NULL)?0:&PublishFvDxePpi->Area, (PublishFvDxePpi==NULL)?0:PublishFvDxePpi->Area.Address));
    Area = NULL;
    if(PublishFvDxePpi)
        Area = &PublishFvDxePpi->Area;

    Status = LaunchFvDxeVerifyPpi(PeiServices,FvDxeValidatePpi,Area);

    return Status;
}

/**
 The function will be called on MemoryInstalled callback:
 Update FvDigestPpi with fixed up addresses from AddrList Hob

 @param PeiServices Pointer to the Pointer to the Pei Services Table.
 @param NotifyDescriptor The notification descriptor for this notification event.
 @param NotifyPpi Pointer to a ppi.

 @retval EFI_SUCCESS If PPI is successfully installed.
*/
EFI_STATUS EFIAPI
InstallFvDigestAfterMem(
    IN EFI_PEI_SERVICES    **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID *Ppi
) {
    EFI_STATUS              Status;
    AMI_FV_DIGEST_PPI       *pFvDigestPpi = NULL;
    AMI_FV_DIGEST_INFO_HOB  *AddrListHob;
    UINTN                   *HashTbl;
    int                     i;

    Status = (*PeiServices)->LocatePpi((CONST EFI_PEI_SERVICES**)PeiServices, &gAmiFvDigestPpiGuid, 0, NULL, (VOID**)&pFvDigestPpi);
    DEBUG((DEBUG_INFO, "InstallFvDigestAfterMem: FvDigestPpi(%X) %r\n", pFvDigestPpi, Status));
    if(EFI_ERROR(Status)) return Status;
    // update address to AddrList/LenList in RAM
    // Locate Hob
    (*PeiServices)->GetHobList((CONST EFI_PEI_SERVICES **)PeiServices, (VOID**)&AddrListHob);
    if (!AddrListHob ) {ASSERT_EFI_ERROR (EFI_NOT_FOUND);return EFI_NOT_FOUND;}
    Status = FindNextHobByGuid (&gAddrListHobGuid, (VOID**)&AddrListHob);
//        DEBUG ((DEBUG_INFO, "Hob %X: %r\n", AddrListHob, Status));
//        DEBUG ((DEBUG_INFO, "AddrList %X, LenList %X (OffsFromAddrList %X), HashElemCnt %X\n", ((UINTN)AddrListHob + sizeof(AMI_FV_DIGEST_INFO_HOB)), ((UINTN)AddrListHob + sizeof(AMI_FV_DIGEST_INFO_HOB)+ AddrListHob->LenListOffs), AddrListHob->LenListOffs, AddrListHob->FvDigestPpi.HashElemCnt));
    if (!EFI_ERROR(Status)) {
//        DEBUG((DEBUG_INFO, "Before:AddrList %X, LenList %X, HashElemCnt %d, HashSize %X\n", pFvDigestPpi->AddrList, pFvDigestPpi->LenList, pFvDigestPpi->HashElemCnt, pFvDigestPpi->HashSize));
        pFvDigestPpi->AddrList = (UINTN*)((UINTN)AddrListHob + sizeof(AMI_FV_DIGEST_INFO_HOB));
        pFvDigestPpi->LenList  = (UINTN*)((UINTN)pFvDigestPpi->AddrList + AddrListHob->LenListOffs);
        pFvDigestPpi->HashList = (UINTN*)((UINTN)pFvDigestPpi->LenList + AddrListHob->LenListOffs);
        HashTbl = (UINTN*)((UINTN)pFvDigestPpi->HashList + AddrListHob->LenListOffs);
        for(i=0; i<(int)pFvDigestPpi->HashElemCnt; i++) {
            pFvDigestPpi->HashList[i]=(UINTN)HashTbl+(i*pFvDigestPpi->HashSize);
//            DEBUG ((DEBUG_INFO, "%2d: Addr %X, Hash %X...\n\n", i,pFvDigestPpi->AddrList[i], *(UINT32*)(UINTN)pFvDigestPpi->HashList[i]));
        }
//        DEBUG ((DEBUG_INFO, "After :AddrList %X, LenList %X, HashList %X, FvHash %X, HashElemCnt %d\n", pFvDigestPpi->AddrList, pFvDigestPpi->LenList, pFvDigestPpi->HashList, pFvDigestPpi->FvHash, pFvDigestPpi->HashElemCnt));
//        DEBUG_CODE ( 
//            for(i=0; i<16; i++) DEBUG ((DEBUG_INFO,"%02X ", *(UINT8*)((UINTN)pFvDigestPpi->HashList[0]+i) )); DEBUG((DEBUG_INFO, "\n"));
//            for(i=0; i<16; i++) DEBUG ((DEBUG_INFO,"%02X ", pFvDigestPpi->FvHash[i]));DEBUG((DEBUG_INFO, "\n"));
//        );
    }
    return Status;
}

/**
  Entry point to ValidatetFvDxeEntry PEIM.
  
  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval Status EFI_STATUS code
**/
EFI_STATUS
EFIAPI
ValidateFvDxeEntry(
    IN       EFI_PEI_FILE_HANDLE    FileHandle,
    IN CONST EFI_PEI_SERVICES       **PeiServices
) {
    // Verify before memory installed
    InstallFvDxeVerifyPpi((EFI_PEI_SERVICES **)PeiServices,NULL,NULL);

    // Launch on memory install or END_OF_PEI notify
    (*PeiServices)->NotifyPpi(PeiServices, mReadyToInstallFvDigestAfterMem);
    // Launch on gAmiPublishFvDxeValidatePpiGuid
    (*PeiServices)->NotifyPpi(PeiServices, mReadyToLaunchFvDxeVerify);

    return EFI_SUCCESS;
}
