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

//**********************************************************************
//
/** @file AmiPspFtpmSmm.c
    Clear PSP Tpm Nvram

**/

#include <PiSmm.h>
#include <Library/UefiLib.h>
#include "Guid/AmiPsp.h"
#include "Token.h"
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/AmiBufferValidationLib.h>
#include <Protocol/SmmBase2.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Protocol/FlashProtocol.h>
#include <AmiPspFtpm.h>

EFI_SMM_SYSTEM_TABLE2           *Smst2 = NULL;
extern  FLASH_PROTOCOL 			AmiAgesaFlashProtocol;
extern  FLASH_PROTOCOL          *AmiPspFlash;


/**
    This function returns base address of PSP lv2 directory

  @param PspComboDirBase  The base address of PSP combo dir.
  @param PspDirBase       The base address of PSP lv2 directory

  @retval BOOLEAN         TRUE - PSP lv2 directory is found.

**/
BOOLEAN
GetPspLv2Dir (
  IN       UINT32                   PspLv1DirBase,
  IN OUT   EFI_PHYSICAL_ADDRESS     *PspLv2DirBase
  )
{
    UINT32                      i;

    for (i = 0; i < ((PSP_DIRECTORY*)PspLv1DirBase)->Header.TotalEntries; i++)
    {
        if (((PSP_DIRECTORY*)PspLv1DirBase)->PspEntry[i].Type.Field.Type == PSP_DIR_LV2)
        {
            *PspLv2DirBase = ((PSP_DIRECTORY*)PspLv1DirBase)->PspEntry[i].Location;
            return  TRUE;
        }
    }
    return FALSE;
}

/**
    This function returns base address of PSP lv1 directory

  @param PspComboDirBase  The base address of PSP combo dir.
  @param PspChipId        The chip id of CPU family.
  @param PspDirBase       The base address of PSP lv1 directory

  @retval BOOLEAN         TRUE - PSP lv1 directory is found.

**/
BOOLEAN
GetPspLv1Dir (
  IN       UINT32     PspComboDirBase,
  IN       UINT32     PspChipId,
  IN OUT   UINT32     *PspDirBase
  )
{
    PSP_COMBO_DIRECTORY         *PspComboDir;
    PSP_COMBO_DIRECTORY_ENTRY   *PspComboEntry;
    UINT32                      i;

    PspComboDir = (PSP_COMBO_DIRECTORY *) (UINTN) PspComboDirBase;
    PspComboEntry = &PspComboDir->ComboEntry[0];
    // Check the signature
    if (PspComboDir->Header.PspCookie != PSP_COMBO_DIRECTORY_HEADER_SIGNATURE)
    {
        return FALSE;
    }
    // Loop to found matched entry
    for (i = 0; i < PspComboDir->Header.TotalEntries; i++)
    {
        if (PspComboEntry[i].Id == PspChipId)
        {
            *PspDirBase = (UINT32) PspComboEntry[i].PspDirTableAddr;
            return TRUE;
        }
    }
    return FALSE;
}

/**
    This function returns base address and size of PSP NVRAM

  @param Address  The base address of PSP Nvram.
  @param NvSize   The size of PSP Nvram.

  @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
GetPspNvBaseAndSize(
  IN OUT EFI_PHYSICAL_ADDRESS   *Address,
  IN OUT UINTN                  *NvSize
)
{
    VOID                    *RomPtr;
    UINTN                   i;
    SOC_ID_STRUCT           SocId;
    SOC_ID_STRUCT           SocId2;
    SOC_ID_STRUCT           SocId3;
    UINT32                  PspChipId;
    UINT32                  PspComboDirBase;
    UINT32                  PspLv1DirBase;
    EFI_PHYSICAL_ADDRESS    PspLv2DirBase;

    RomPtr = (VOID*)((0xFFFFFFFF - FLASH_SIZE + 1) + FCH_FIRMWARE_OFFSET);
    if (((FIRMWARE_ENTRY_TABLEV2*)RomPtr)->Signature != FIRMWARE_TABLE_SIGNATURE)
        return EFI_NOT_FOUND;

    // Check Hardware Identification
    SocId.SocFamilyID = F15_BR_RAW_ID;
    SocId.PackageType = BR_PKG_AM4;
    if (SocHardwareIdentificationCheck (&SocId))
    {
        RomPtr = (VOID*)((FIRMWARE_ENTRY_TABLEV2*)RomPtr)->LegacyPspDirBase;
        DEBUG((DEBUG_INFO, "\n RomPtr = %lx\n", RomPtr));
        DEBUG((DEBUG_INFO, "\n RomPtr->Header.TotalEntries = %lx\n", ((PSP_DIRECTORY*)RomPtr)->Header.TotalEntries));
        for (i = 0; i < ((PSP_DIRECTORY*)RomPtr)->Header.TotalEntries; i++)
        {
            if (((PSP_DIRECTORY*)RomPtr)->PspEntry[i].Type.Field.Type == PSP_NV_DATA)
            {
                *Address = ((PSP_DIRECTORY*)RomPtr)->PspEntry[i].Location;
                *NvSize = ((PSP_DIRECTORY*)RomPtr)->PspEntry[i].Size;
                return  EFI_SUCCESS;
            }
        }
    }
    else
    {
        // Check Hardware Identification
        SocId.SocFamilyID = F17_RV_RAW_ID;
        SocId.PackageType = RV_FP5;

        SocId2.SocFamilyID = F17_RV2_RAW_ID;
        SocId2.PackageType = RV_FP5;

        SocId3.SocFamilyID = F17_PIC_RAW_ID;
        SocId3.PackageType = RV_FP5;
        
        if (SocHardwareIdentificationCheck (&SocId) || SocHardwareIdentificationCheck (&SocId2) || SocHardwareIdentificationCheck (&SocId3))
        {
            PspLv1DirBase = ((FIRMWARE_ENTRY_TABLEV2*)RomPtr)->PspDirBase;
            DEBUG((DEBUG_INFO, "\n PspLv1DirBase = %lx\n", PspLv1DirBase));
        }
        else
        {
            PspComboDirBase = ((FIRMWARE_ENTRY_TABLEV2*)RomPtr)->PspDirBase;
            DEBUG((DEBUG_INFO, "\n PspComboDirBase = %lx\n", PspComboDirBase));
            SocId.SocFamilyID = F17_ZP_RAW_ID;
            SocId.PackageType = ZP_PKG_AM4;
            if (SocHardwareIdentificationCheck (&SocId))
                PspChipId = ZP_PSP_CHIP_ID;
            else
                PspChipId = RV_PSP_CHIP_ID;

            GetPspLv1Dir(PspComboDirBase, PspChipId, &PspLv1DirBase);
            DEBUG((DEBUG_INFO, "\n PspLv1DirBase = %lx\n", PspLv1DirBase));
        }

        GetPspLv2Dir(PspLv1DirBase, &PspLv2DirBase);
        DEBUG((DEBUG_INFO, "\n PspLv2DirBase = %lx\n", PspLv2DirBase));

        for (i = 0; i < ((PSP_DIRECTORY*)PspLv2DirBase)->Header.TotalEntries; i++)
        {
            if (((PSP_DIRECTORY*)PspLv2DirBase)->PspEntry[i].Type.Field.Type == PSP_NV_DATA)
            {
                *Address = ((PSP_DIRECTORY*)PspLv2DirBase)->PspEntry[i].Location;
                *NvSize = ((PSP_DIRECTORY*)PspLv2DirBase)->PspEntry[i].Size;
                return  EFI_SUCCESS;
            }
        }
    }

    return  EFI_NOT_FOUND;
}

/**
    This function saves the Psp S3 data to Psp S3 Nvram.

  @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param Context         Points to an optional handler context which was specified when the
                         handler was registered.
  @param CommBuffer      A pointer to a collection of data in memory that will
                         be conveyed from a non-SMM environment into an SMM environment.
  @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
AmiPspFtpmClearNv (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *DispatchContext OPTIONAL,
    IN  OUT VOID        *CommBuffer      OPTIONAL,
    IN  OUT UINTN       *CommBufferSize  OPTIONAL
)
{
    EFI_STATUS      		Status = EFI_SUCCESS;
    EFI_PHYSICAL_ADDRESS    PspNvBase = 0;
    UINTN                   EraseSize = 0;
    UINT8                   *DataBuffer;
    UINTN                   DataSize;

    DEBUG((DEBUG_INFO, "\n AmiPspFtpmClearNv Entry\n"));

    DataBuffer = (UINT8*)CommBuffer;
    DataSize = *CommBufferSize;
    DEBUG((DEBUG_INFO, "\n DataSize = %lx\n", DataSize));
    DEBUG((DEBUG_INFO, "\n DataBuffer[0] = %x\n", *DataBuffer));

    Status = AmiValidateMemoryBuffer((VOID*)CommBuffer, *CommBufferSize);
    if (Status != EFI_SUCCESS)
        return  Status;

    if ((AmiPspFlash != NULL) && (*DataBuffer == 1))
    {
        Status = GetPspNvBaseAndSize(&PspNvBase, &EraseSize);
        if (Status != EFI_SUCCESS)
        {
            DEBUG((DEBUG_ERROR, "WARNING: Unable to get PSP nvram base\n"));
            return EFI_UNSUPPORTED;
        }

        DEBUG((DEBUG_INFO, "\n PspNvBase = %lx\n", PspNvBase));
        DEBUG((DEBUG_INFO, "\n EraseSize = %lx\n", EraseSize));

        Status = AmiAgesaFlashProtocol.Erase((VOID*)PspNvBase, EraseSize);
        DEBUG((DEBUG_INFO, "\n Flash Erase status = %r\n", Status));
    }

    Smst2->SmiHandlerUnRegister(DispatchHandle);
    DEBUG((DEBUG_INFO, "\n SmiHandlerUnRegister AmiPspFtpmClearNv status = %r\n", Status));

    return Status;
}

/**
    Initializes Psp S3 SMM Drivers.

    @param

    @retval EFI_STATUS

    @note Here is the control flow of this function:
**/

EFI_STATUS
EFIAPI
AmiPspFtpmSmmInit (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
 )
{
    EFI_STATUS              Status;
    EFI_SMM_BASE2_PROTOCOL  *SmmBase2;
    VOID                    *FirstHob;
    AMI_PSP_FTPM_HOB        *AmiPspFtpmHob;
    EFI_HANDLE              Handle;

    DEBUG ((DEBUG_INFO , "AmiPspFtpmSmmInit entry\n"));

    Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &FirstHob);
    if (EFI_ERROR(Status)) return Status;

    AmiPspFtpmHob = GetNextGuidHob(&gAmiPspFtpmHobGuid, FirstHob);
    if (!AmiPspFtpmHob) return EFI_NOT_FOUND;

    if (AmiPspFtpmHob->ClearPspNvram == PSP_FTPM_FLAG_CLEAR)
    {
        Status = gBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, (VOID**)&SmmBase2);
        if (EFI_ERROR(Status)) {
            return Status;
        }

        Status = SmmBase2->GetSmstLocation(SmmBase2, &Smst2);
        if (EFI_ERROR(Status)) {
            return EFI_UNSUPPORTED;
        }

        Status = Smst2->SmiHandlerRegister(
                        (VOID *)AmiPspFtpmClearNv,
                        &gAmiPspFtpmSmmCommunicationGuid,
                        &Handle
                        );
        if (EFI_ERROR(Status)) 
        {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
    }

    DEBUG ((DEBUG_INFO , "AmiPspFtpmSmmInit exit\n"));

    return Status;
}

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
