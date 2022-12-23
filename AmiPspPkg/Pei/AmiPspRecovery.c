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

//#include "token.h"
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Ppi/AmdPspRecoveryDetectPpi.h>
#include <Ppi/MasterBootMode.h>

EFI_STATUS
EFIAPI
AmiPspRecoveryCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

EFI_PEI_NOTIFY_DESCRIPTOR  AmiPspRecoveryNotifyList =
{
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmdPspRecoveryDetectPpiGuid,
    AmiPspRecoveryCallback
};

static EFI_PEI_PPI_DESCRIPTOR MasterBootModePpi[] =
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiMasterBootModePpiGuid,
    NULL
  };

/**
    This function is called when AmdPspRecoveryDetectPpiGuid is installed.
    It changes the boot mode to recovery mode.

    @param Pointer to PeiServices
    @param Pointer to NotifyDesc
    @param InvokePpi 

    @retval EFI_SUCCESS always success

**/
EFI_STATUS
EFIAPI
AmiPspRecoveryCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_BOOT_MODE                   	BootMode;
    EFI_STATUS                      	Status;

    BootMode = BOOT_IN_RECOVERY_MODE;
    Status = (*PeiServices)->SetBootMode(PeiServices, BootMode);
    DEBUG((DEBUG_INFO, "AmiPspRecoveryCallback SetBootMode status = %r\n", Status));
    Status = (*PeiServices)->InstallPpi(PeiServices, MasterBootModePpi);
    DEBUG((DEBUG_INFO, "AmiPspRecoveryCallback Install Master boot mode status = %r\n", Status));

    return  EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmiPspRecoveryEntry (
  IN        EFI_PEI_FILE_HANDLE FileHandle,
  IN CONST  EFI_PEI_SERVICES    **PeiServices
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_BOOT_MODE                   BootMode;
    AMD_PSP_RECOVERY_DETECT_PPI     *AmdPspRecoveryPpi;

    Status = (*PeiServices)->LocatePpi (PeiServices, &gAmdPspRecoveryDetectPpiGuid,
                              0, NULL, &AmdPspRecoveryPpi);
    if (Status != EFI_SUCCESS)
    {
        Status = (**PeiServices).NotifyPpi (PeiServices, &AmiPspRecoveryNotifyList);
        DEBUG((DEBUG_INFO, "NotifyPpi status = %r\n", Status));
        return  Status;
    }

    BootMode = BOOT_IN_RECOVERY_MODE;
    Status = (*PeiServices)->SetBootMode(PeiServices, BootMode);
    DEBUG((DEBUG_INFO, "AmiPspRecoveryEntry SetBootMode status = %r\n", Status));
    Status = (*PeiServices)->InstallPpi(PeiServices, MasterBootModePpi);
    DEBUG((DEBUG_INFO, "AmiPspRecoveryEntry Install Master boot mode status = %r\n", Status));

	return	Status;
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
