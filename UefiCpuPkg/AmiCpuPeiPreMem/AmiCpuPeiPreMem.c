//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file AmiCpuPeiPreMem.c
    Main CpuPeiEarlyInit Driver File. 

**/

#include <Token.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Register/Microcode.h>
#include <Library/BaseMemoryLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>

/**
  Find the microcode address in specific firmware volume.

  @param Fv - Firmware Volume
  @param MicrocodePatchAddress - If find, return microcode patch address
  @param MicrocodePatchRegionSize - If find, return microcode patch size

  @retval EFI_SUCCESS        - Found microcode.
  @retval EFI_NOT_FOUND      - Not found.
**/

EFI_STATUS
EFIAPI
FindMicrocodeInFv (
  IN VOID *Fv,
  OUT UINT64 *MicrocodePatchAddress,
  OUT UINT64 *MicrocodePatchRegionSize
  )
{
    EFI_GUID                          MicrocodeFfsGuid = {0x17088572, 0x377F, 0x44ef, 0x8F, 0x4E, 0xB0, 0x9F, 0xFF, 0x46, 0xA0, 0x70};
    UINT8                             *pEndOfFv = (UINT8*)Fv + ((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->FvLength - 1;
    UINT8                             *pFfs = (UINT8*)Fv + ((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->HeaderLength;
    UINT32                            FfsSize;
    EFI_FIRMWARE_VOLUME_HEADER        *FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)Fv;
    EFI_FIRMWARE_VOLUME_EXT_HEADER    *ExtHdr;

    //Check for corrupt firmware volume.
    if (((EFI_FIRMWARE_VOLUME_HEADER*)Fv)->Signature != 'HVF_') return EFI_NOT_FOUND;
    if (pEndOfFv <= pFfs) return EFI_NOT_FOUND;
	//If FV extension header exist
    if (FvHeader->ExtHeaderOffset != 0) {
        // Skip extended Header if exists.
        ExtHdr = (EFI_FIRMWARE_VOLUME_EXT_HEADER *)((UINT8*)FvHeader + (FvHeader->ExtHeaderOffset));
        pFfs = (UINT8*)ExtHdr + ExtHdr->ExtHeaderSize;
    } else {
        pFfs = (UINT8*)FvHeader + FvHeader->HeaderLength;
    }
    pFfs = (UINT8*)(((UINTN)pFfs + 7)& ~7);    //Align to 8 bytes
    while(TRUE) {
      if (pFfs >= pEndOfFv) return EFI_NOT_FOUND;

      FfsSize = *(UINT32*)&((EFI_FFS_FILE_HEADER*)pFfs)->Size & 0xffffff;

      //Find Microcode file
      if (CompareGuid(&((EFI_FFS_FILE_HEADER*)pFfs)->Name, &MicrocodeFfsGuid)) {
#if MICROCODE_SPLIT_BB_UPDATE
        if ((UINTN)Fv == FV_MICROCODE_UPDATE_BASE) {
            UINT8  *pEndOfFfs;
            CPU_MICROCODE_HEADER  *pUc;
            UINT32 UcSize;
            UINT32 CpuSignature;
            UINT8  CpuFlags = (UINT8) AsmMsrBitFieldRead64 (MSR_IA32_PLATFORM_ID, 50, 52);
            UINT8  UcFlag = 1 << CpuFlags;

            pEndOfFfs = pFfs + FfsSize;
            AsmCpuid (CPUID_VERSION_INFO, &CpuSignature, NULL, NULL, NULL);

            //Find Microcode
            pUc = (CPU_MICROCODE_HEADER*)((UINTN)pFfs + sizeof(EFI_FFS_FILE_HEADER));

            while(TRUE) {
                if (pUc->HeaderVersion != 1) return EFI_NOT_FOUND;  //End of microcode or corrupt.
                UcSize = pUc->DataSize ? pUc->TotalSize : 2048;

                if ((pUc->ProcessorSignature.Uint32 == CpuSignature) && (pUc->ProcessorFlags & UcFlag)) {
                    //Find Microcode
                    *MicrocodePatchAddress = (UINT64)(UINTN)pUc;
                    *MicrocodePatchRegionSize = (UINT64)(UINTN)UcSize;
                    return EFI_SUCCESS;
                }

                if (pUc->TotalSize > (pUc->DataSize + sizeof (CPU_MICROCODE_HEADER))) {        //Extended signature count.
                    CPU_MICROCODE_EXTENDED_TABLE_HEADER *ExtendedTableHeader = (CPU_MICROCODE_EXTENDED_TABLE_HEADER*)((UINT8*)(UINTN)pUc + pUc->DataSize + 48);
                    CPU_MICROCODE_EXTENDED_TABLE        *ExtendedTable = (CPU_MICROCODE_EXTENDED_TABLE *)(ExtendedTableHeader + 1);
                    UINT32 ExtendedTableCount = ExtendedTableHeader->ExtendedSignatureCount;
                    UINT8 i;

                    if (ExtendedTableCount >= 20) return EFI_NOT_FOUND;    //Corrupt microcode.

                    for (i = 0; i < ExtendedTableCount; i++) {
                        if ((ExtendedTable->ProcessorSignature.Uint32 == CpuSignature) && ((ExtendedTable->ProcessorFlag & UcFlag))) {
                            //Find Microcode
                            *MicrocodePatchAddress = (UINT64)(UINTN)pUc;
                            *MicrocodePatchRegionSize = (UINT64)(UINTN)UcSize;
                            return EFI_SUCCESS;
                        }
                        ExtendedTable ++;
                    }
                }

#if PACK_MICROCODE
                UcSize = (UcSize + (16 - 1)) & ~(16 - 1);
#else
                UcSize = (UcSize + (MICROCODE_BLOCK_SIZE - 1)) & ~(MICROCODE_BLOCK_SIZE - 1);
#endif
                if (((UINT64)(UINTN)pUc + UcSize) >= (UINT64)(UINTN)pEndOfFfs) return EFI_NOT_FOUND;   //End of uc or corrupt

                pUc = (CPU_MICROCODE_HEADER*)((UINTN)pUc + UcSize);
            }
        }
        else {
            //Find Microcode
            *MicrocodePatchAddress = (UINT64)(UINTN)(pFfs + sizeof(EFI_FFS_FILE_HEADER));
            *MicrocodePatchRegionSize = (UINT64)(UINTN)FfsSize;
            return EFI_SUCCESS;
        }
#else
        //Find Microcode
        *MicrocodePatchAddress = (UINT64)(UINTN)(pFfs + sizeof(EFI_FFS_FILE_HEADER));
        *MicrocodePatchRegionSize = (UINT64)(UINTN)FfsSize;
        return EFI_SUCCESS;
#endif
      }
      if ((pFfs + FfsSize) <= pFfs) return EFI_NOT_FOUND; //Corruption?
      pFfs +=  FfsSize;  //Next file.
      pFfs = (UINT8*)(((UINTN)pFfs + 7) & ~7);  //Align on 8 byte boundary.
    }

    return EFI_NOT_FOUND;
}

/**
  Find the microcode address.

  @param MicrocodePatchAddress - If find, return microcode patch address
  @param MicrocodePatchRegionSize - If find, return microcode patch size

  @retval EFI_SUCCESS        - Found microcode.
  @retval EFI_NOT_FOUND      - Not found.
**/

EFI_STATUS
EFIAPI
FindMicrocode (
  OUT UINT64 *MicrocodePatchAddress,
  OUT UINT64 *MicrocodePatchRegionSize
  )
{
	EFI_STATUS  Status;
#if MICROCODE_SPLIT_BB_UPDATE
    Status =  FindMicrocodeInFv((VOID*)FV_MICROCODE_UPDATE_BASE, MicrocodePatchAddress, MicrocodePatchRegionSize);
    if (EFI_ERROR (Status)) Status = FindMicrocodeInFv((VOID*)FV_MICROCODE_BASE, MicrocodePatchAddress, MicrocodePatchRegionSize);
#else
    Status =  FindMicrocodeInFv((VOID*)FV_MICROCODE_BASE, MicrocodePatchAddress, MicrocodePatchRegionSize);
#endif
	return Status;
}

/**
    CpuPei driver entry Before memory initialize

    @param  FileHandle    Handle of the file being invoked.
    @param  PeiServices   Describes the list of possible PEI Services.

    @retval EFI_STATUS Return EFI status. 
**/

EFI_STATUS
EFIAPI
AmiCpuPeiPreMemEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
	EFI_STATUS  Status;
	UINT64                                  MicrocodePatchAddress;
	UINT64                                  MicrocodePatchRegionSize;
	
	MicrocodePatchAddress    = PcdGet64 (PcdCpuMicrocodePatchAddress);
    MicrocodePatchRegionSize = PcdGet64 (PcdCpuMicrocodePatchRegionSize);

	if (MicrocodePatchRegionSize == 0) {
	    Status = FindMicrocode(&MicrocodePatchAddress, &MicrocodePatchRegionSize);
		if (!EFI_ERROR (Status)) {
			//Change PCDs
			PcdSet64(PcdCpuMicrocodePatchAddress, MicrocodePatchAddress);
			PcdSet64(PcdCpuMicrocodePatchRegionSize, MicrocodePatchRegionSize);
		}
	}
  return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**             5555 Oakbrook Pkwy, Norcross, GA 30093               **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
