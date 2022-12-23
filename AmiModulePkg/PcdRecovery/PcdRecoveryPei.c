//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  PCD Recovery PEIM.
**/
#include <PiPei.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Ppi/BootInRecoveryMode.h>
#include <Fid.h>
#include <Token.h>
#include "PcdRecovery.h"

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

static EFI_GUID gFidFileName = FID_FFS_FILE_NAME_GUID;

//---------------------------------------------------------------------------
// Local prototypes
//---------------------------------------------------------------------------
EFI_STATUS
EFIAPI
InitializePcdRecoveryInfo(
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                      *InvokePpi
);

//---------------------------------------------------------------------------
// PPIs notifications to be installed
//---------------------------------------------------------------------------
static EFI_PEI_NOTIFY_DESCRIPTOR  gNotifyPcdBootInRecovery[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
        &gEfiPeiBootInRecoveryModePpiGuid,
        InitializePcdRecoveryInfo
    }
};

#pragma pack(push)
#pragma pack(1)


// Structure that defines the layout of FW_VERSION
typedef struct _AMI_FW_VERSION_SECTION {
    EFI_FFS_FILE_HEADER               FfsFileHeader;    //< The FFS file header
    EFI_FREEFORM_SUBTYPE_GUID_SECTION GuidedSection;    //< The Guided Section of the FFS file
    FW_VERSION                        FwVersionData;
} AMI_FW_VERSION_SECTION;

#pragma pack(pop)


/**
  This function returns current FID descriptor

  @param  PeiServices   Pointer to the Pointer to the Pei Services Table
  @param  Fid           Pointer where to store FID descriptor

  @retval EFI_SUCCESS   Layout returned successfully
  @retval Other         There is no FID descriptor in buffer

**/
EFI_STATUS
PcdPeiGetFid (
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    OUT VOID                   *Fid
)
{
    EFI_STATUS                    Status;
    EFI_PEI_FV_HANDLE             FvHandle;
    EFI_PEI_FILE_HANDLE           FileHandle;
    UINTN                         FvNum = 0;
    AMI_FW_VERSION_SECTION        *FwVersionSectionData = NULL;

    while ( TRUE )
    {
        FvHandle = NULL;
        Status = (*PeiServices)->FfsFindNextVolume( PeiServices, FvNum, &FvHandle );
        if ( EFI_ERROR( Status ) )
        {
            DEBUG((DEBUG_ERROR,"[PcdRecoveryPei]FfsFindNextVolume Status =%r, FvNum= %d\n", Status, FvNum));
            return Status;
        }

        FileHandle = NULL;
        // Find file
        Status = (*PeiServices)->FfsFindFileByName (&gFidFileName, FvHandle, &FileHandle);
        if ( !EFI_ERROR (Status))
        {
            DEBUG((DEBUG_VERBOSE,"[PcdRecoveryPei]FfsFindFileByName FileHandle->Name =%g, FvNum= %d\n",
                              &(((EFI_FFS_FILE_HEADER*)FileHandle)->Name), FvNum));
            break;
        }

        FvNum++;
    }

    FwVersionSectionData = (AMI_FW_VERSION_SECTION*)FileHandle;

    CopyMem(Fid, &FwVersionSectionData->FwVersionData, sizeof(FW_VERSION));

    return Status;
}

/**
  Initialize PcdRecovery Info when boot in Recovery

  @param       PeiServices      - Pointer to the PEI services table
  @param       NotifyDescriptor - Pointer to the descriptor for the
                                  notification event.
  @param       InvokePpi        - Pointer to the PPI that was installed

  @param       EFI_STATUS
**/

EFI_STATUS
EFIAPI
InitializePcdRecoveryInfo(
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
    IN VOID                      *InvokePpi
)
{
    EFI_STATUS           Status;
    FW_VERSION           Fid;
    AMI_PCD_RECOVERY_HOB *AmiPcdRecoveryHob = NULL;

    AmiPcdRecoveryHob = GetFirstGuidHob(&gAmiPcdRecoveryHobGuid);
    if (AmiPcdRecoveryHob == NULL)
    {
        DEBUG ((DEBUG_ERROR, "[PcdRecoveryPei] Get AmiPcdRecoveryHob fail.\n"));
        return EFI_SUCCESS;
    }

    AmiPcdRecoveryHob->IsRecovery = 1;

    Status = PcdPeiGetFid((CONST EFI_PEI_SERVICES**)PeiServices, &Fid);
    if ( EFI_ERROR(Status) )
    {
        DEBUG ((DEBUG_ERROR, "PcdPeiGetFid fails: %r\n", Status));
        return Status;
    }

    CopyMem(&AmiPcdRecoveryHob->FwVersionData, &Fid, sizeof(FW_VERSION));

    return EFI_SUCCESS;
}

/**
  Entry point of the PcdRecovery PEIM.

  @param  FileHandle  Handle of the file being invoked.
  @param  PeiServices Describes the list of possible PEI Services.

  @retval EFI_SUCESS  The entry point of AmiPcdRecovery PEIM executes successfully.
  @retval Others      Some error occurs during the execution of this function.
**/
EFI_STATUS
PcdRecoveryPeiEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS           Status;
    EFI_BOOT_MODE        BootMode;
    FW_VERSION           Fid;
    AMI_PCD_RECOVERY_HOB *AmiPcdRecoveryHob = NULL;
    UINTN                SkuId;

    // Determine boot mode
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);

    Status = (*PeiServices)->CreateHob( PeiServices,
                                        EFI_HOB_TYPE_GUID_EXTENSION,
                                        sizeof(AMI_PCD_RECOVERY_HOB),
                                        (VOID **) &AmiPcdRecoveryHob);
    if ( EFI_ERROR(Status) )
    {
        DEBUG ((DEBUG_ERROR, "[PcdRecoveryPei] CreateHob fails for AmiPcdRecoveryHob %r\n", Status));
        return Status;
    }

    AmiPcdRecoveryHob->EfiHobGuidType.Name = gAmiPcdRecoveryHobGuid;
    AmiPcdRecoveryHob->IsRecovery = 0;

    //Set IsRecovery flag if boot in recovery
    Status = (*PeiServices)->NotifyPpi( PeiServices, gNotifyPcdBootInRecovery);
    if ( EFI_ERROR(Status) )
    {
        return Status;
    }

    if(BootMode == BOOT_ON_FLASH_UPDATE && PcdGetBool(PcdUseNewImageOnFlashUpdate))
    {
        Status = PcdPeiGetFid(PeiServices, &Fid);
        if ( EFI_ERROR(Status) )
        {
            DEBUG ((DEBUG_ERROR, "PcdPeiGetFid fails: %r\n", Status));
            return Status;
        }

        CopyMem(&AmiPcdRecoveryHob->FwVersionData, &Fid, sizeof(FW_VERSION));
    }
	SkuId = LibPcdGetSku();
	CopyMem(&AmiPcdRecoveryHob->SkuId, &SkuId, sizeof(UINTN));

    return Status;
}
