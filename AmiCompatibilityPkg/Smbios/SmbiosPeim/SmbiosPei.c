//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SmbiosPei.c
    This file provides function to update "Wake-up Type"
    data field in Smbios Type 1 structure

**/

#include <AmiPeiLib.h>
#include <Library/DebugLib.h>
#include <Library/LockBoxLib.h>
#include <Library/PeiServicesLib.h>
#include <Protocol/AmiSmbios.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Ppi/MemoryDiscovered.h>
#include <Ppi/SmmCommunication.h>

//extern VOID		OemRuntimeShadowRamWrite(IN BOOLEAN Enable);
extern UINT8	getWakeupTypeForSmbios(VOID);
extern VOID     NbRuntimeShadowRamWrite(IN BOOLEAN Enable);
EFI_STATUS
EFIAPI
NotifyOnSmmCommunication (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

static
EFI_PEI_NOTIFY_DESCRIPTOR NotifyList[] = {
    {
        EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,    
        &gEfiPeiSmmCommunicationPpiGuid,
        NotifyOnSmmCommunication
    }
};

EFI_GUID    gSmbiosWakeupTypeUpdateGuid = SMBIOS_WAKEUPTYPE_GUID;

/**
    Driver entry point for SmbiosPei
    
    Detect and update SMBIOS Type 1 structure "Wake-up Type"
    data field

    @param PeiServices

    @retval VOID Updated SMBIOS Type 1 "Wake-up Type"
    @param FfsHeader
    @param PeiServices

    @retval EFI_STATUS Status

**/
EFI_STATUS
EFIAPI
SmbiosPeiEntryPoint(
    IN       EFI_PEI_FILE_HANDLE    FileHandle,
    IN CONST EFI_PEI_SERVICES       **PeiServices
)
{
    EFI_STATUS      Status;
    EFI_BOOT_MODE   BootMode;
    
    // Determine boot mode
    Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    if (EFI_ERROR(Status)) {
        DEBUG((DEBUG_ERROR, "Failed to get BootMode\n"));
        return Status;
    }

    if (BootMode == BOOT_ON_S3_RESUME) {
        Status = (**PeiServices).NotifyPpi(
                                    (const EFI_PEI_SERVICES **)PeiServices, 
                                    (const EFI_PEI_NOTIFY_DESCRIPTOR *)NotifyList);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    return EFI_SUCCESS;
}

/**
   @internal
   
    This routine is called when gEfiPeiSmmCommunicationPpiGuid
    is available.

    @param PeiServices      Pointer to PEI Services
    @param NotifyDesc       Pointer to notify descriptor
    @param InvokePpi        Pointer to Invoke PPI.

    @retval EFI_SUCCESS
    
   @endinternal
**/

EFI_STATUS
EFIAPI
NotifyOnSmmCommunication (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_STATUS      Status;
    UINT64          WakeupTypePtr;
    UINTN           SmbiosLockBoxSize; 
    
    // First get LockBox data size
    SmbiosLockBoxSize = sizeof (WakeupTypePtr);
    Status = RestoreLockBox (
                        &gSmbiosWakeupTypeUpdateGuid, 
                        &WakeupTypePtr, 
                        &SmbiosLockBoxSize);        
    if (Status == EFI_SUCCESS) {
        if (WakeupTypePtr > 0xf0000) {
            *(UINT8 *)(UINTN)WakeupTypePtr = getWakeupTypeForSmbios();
        } else {
            //OemRuntimeShadowRamWrite(TRUE);
            NbRuntimeShadowRamWrite(TRUE);
            *(UINT8 *)(UINTN)WakeupTypePtr = getWakeupTypeForSmbios();
            //OemRuntimeShadowRamWrite(FALSE);
            NbRuntimeShadowRamWrite(FALSE);
        }
    }
    
    return EFI_SUCCESS;
}
