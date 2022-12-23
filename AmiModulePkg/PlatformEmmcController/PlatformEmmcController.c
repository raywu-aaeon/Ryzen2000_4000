//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

#include <Protocol/DevicePath.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/AmiSdEmmcControllerInitProtocol.h>

EFI_STATUS
EFIAPI 
GetNumberOfSlots 
(
  IN     AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *This,
  IN OUT UINT8                           *NumOfSlots
) {
    *NumOfSlots = 1;
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI 
GetSlotBaseAddress
(
  IN     AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *This,
  IN     UINT8                           SlotNum,
  IN OUT UINTN                           *SlotMmioBaseAddress
) {
    *SlotMmioBaseAddress = 0xFEDD5000;
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
GetDeviceLocation
(
  IN     AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *This,
  IN OUT CHAR16                          *DeviceName
) {
    return EFI_UNSUPPORTED;
}

EFI_STATUS PlatformEmmcEntryPoint
(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS                                 Status;
    AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *AmiSdEmmcControllerInitProtocol = NULL;
    EFI_GUID                                  AmiSdEmmcControllerInitProtocolGuid = AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL_GUID;
    EFI_HANDLE                                ControllerHandle = NULL;
    static struct {
        AMI_SD_EMMC_VENDOR_DEVICE_PATH   AmiSdEmmcVendorDp;
        EFI_DEVICE_PATH_PROTOCOL end;
    } SdEmmcVendorDp = {
            {
              {{HARDWARE_DEVICE_PATH, HW_VENDOR_DP, {sizeof(AMI_SD_EMMC_VENDOR_DEVICE_PATH), 0}},
              AMI_SD_EMMC_VENDOR_DEVICE_PATH_GUID}, // VENDOR_DEVICE_PATH
              0,
            },
            {END_DEVICE_PATH_TYPE,END_ENTIRE_DEVICE_PATH_SUBTYPE,sizeof(EFI_DEVICE_PATH_PROTOCOL)}
        };
    Status = gBS->AllocatePool (EfiBootServicesData, \
                                sizeof(AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL),
                                &AmiSdEmmcControllerInitProtocol);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    gBS->SetMem(AmiSdEmmcControllerInitProtocol, sizeof(AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL), 0);
    AmiSdEmmcControllerInitProtocol->GetSlotBaseAddress = GetSlotBaseAddress;
    AmiSdEmmcControllerInitProtocol->GetNumberOfSlots = GetNumberOfSlots;
    AmiSdEmmcControllerInitProtocol->GetDeviceName = GetDeviceLocation;
    
    Status = gBS->InstallMultipleProtocolInterfaces(&ControllerHandle,
                                                    &AmiSdEmmcControllerInitProtocolGuid, AmiSdEmmcControllerInitProtocol,
                                                    &gEfiDevicePathProtocolGuid, &SdEmmcVendorDp,
                                                    NULL
                                                    );
    DEBUG((-1,"\n InstallProtcol :%r",Status));
    ASSERT_EFI_ERROR(Status);
    
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
