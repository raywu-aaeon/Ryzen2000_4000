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

#ifndef __AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL__H__
#define __AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Protocol/DevicePath.h>

// Forward definition.

typedef struct _AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL;

#define AMI_SD_EMMC_VENDOR_DEVICE_PATH_GUID \
  { \
    0xf29fcb02, 0x029e, 0x4206, {0xbc, 0x18, 0x94, 0x2f, 0xaa, 0xba, 0xfa, 0x2a} \
  }
typedef struct {
  VENDOR_DEVICE_PATH    VendorDevicePath;
  UINT8                 UID;
} AMI_SD_EMMC_VENDOR_DEVICE_PATH;

#define AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL_GUID \
  { \
    0xbe98ba47, 0x4a2a, 0x4c12, {0xae, 0x83, 0x7, 0x22, 0xd4, 0xe0, 0xad, 0x45} \
  }
/**
  Returns Number of Slots present under this SD/eMMC controller.

  @param[in]       This           Indicates a pointer to the calling context.
  @param[in]       NumOfSlots     A pointer to memory that holds Number of Slots
                                  information.
  @retval EFI_SUCCESS             Returned Number of Slot Information Properly.
**/
typedef
EFI_STATUS
(EFIAPI *AMI_SD_EMMC_GET_NUM_OF_SLOTS) (
  IN     AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *This,
  IN OUT UINT8                                     *NumOfSlots
);
/**
  Returns Mmio Base address for the specified input SlotNum.

  @param[in]       This                 Indicates a pointer to the calling context.
  @param[in]       SlotNum              The SlotNo for which the Base address has to be returned.
  @param[in]       SlotMmioBaseAddress  The pointer to the memory that holds Slot's MMIO Base Address 

  @retval EFI_SUCCESS             MMIO base address returned properly for the 
                                  specified SlotNum input.
  @retval EFI_INVALID_PARAMETER   There is no Slot available with SlotNum input.
  @retval EFI_NOT_FOUND           There is no MMIO base address for the specified 
                                  SlotNum input.

**/
typedef
EFI_STATUS
(EFIAPI *AMI_SD_EMMC_GET_SLOT_BASE_ADDRESS) (
  IN     AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *This,
  IN     UINT8                                     SlotNum,
  IN OUT UINT64                                    *SlotMmioBaseAddress
);
/**
  Returns the device Name to show location information in Setup.It may represent about 
  controller location on this platform.

  @param[in]       This           Indicates a pointer to the calling context.
  @param[in]       DeviceName     The Device Name to show under SDIO Configuration SetUp page.
  
  @retval EFI_SUCCESS             DeviceName is returned properly.
  @retval EFI_UNSUPPORTED         There is no Specific name implemented for this
                                  SD/eMMC controller.

**/
typedef
EFI_STATUS
(EFIAPI *AMI_SD_EMMC_GET_DEVICE_NAME) (
  IN       AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *This,
  IN  OUT  CHAR16                                    *DeviceName
);

struct _AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL {
    AMI_SD_EMMC_GET_NUM_OF_SLOTS            GetNumberOfSlots;
    AMI_SD_EMMC_GET_SLOT_BASE_ADDRESS       GetSlotBaseAddress;
    AMI_SD_EMMC_GET_DEVICE_NAME             GetDeviceName;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
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
