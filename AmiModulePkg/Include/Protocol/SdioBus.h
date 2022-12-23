//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************

/** @file SdioBus.h
**/

#ifndef _AMI_SDIO_BUS_H
#define _AMI_SDIO_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------
#include <Protocol/PciIo.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskInfo.h>
#include <SdioController.h>

#if defined ( MDE_PKG_VERSION ) && (MDE_PKG_VERSION > 12) 
#include <Protocol/EraseBlock.h>
#endif
//----------------------------------------------------------------------

#define SETUP_GUID { 0xEC87D643, 0xEBA4, 0x4BB5,{ 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 }}

#define PCI_CL_SYSTEM_PERIPHERALS           0x08
#define PCI_CL_SYSTEM_PERIPHERALS_SCL_SD    0x05

#define  MAX_SLOTS_PER_CONTROLLER        0x06

typedef struct _SDIO_DEVICE_INTERFACE SDIO_DEVICE_INTERFACE;

typedef VOID 
(EFIAPI *EFI_SDIO_INVOKE_API) (
VOID*   fURP    
);
// Enum added to discriminate SD/EMMC controller type.
typedef enum 
{
  PciIoType,
  NonPciIoType
} AMI_SD_EMMC_CONTROLLER_TYPE;

typedef struct{
    EFI_HANDLE                      ControllerHandle;
    UINT64                          SdioBaseAddress[MAX_SLOTS_PER_CONTROLLER];
    LIST_ENTRY                      SdioDeviceList;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePathProtocol;
    VOID                            *ControllerInterface;
    EFI_SDIO_INVOKE_API             SdioInvokeApi;
    UINT64                          AdmaDescriptorAddress;
    VOID                            *AdmaDescriptorAddressUnMap;
    UINT8                           NumberOfSlotsImplemented;
    AMI_SD_EMMC_CONTROLLER_TYPE     ControllerType;
    BOOLEAN                         CardPresentState[MAX_SLOTS_PER_CONTROLLER];
} AMI_SDIO_BUS_PROTOCOL;

typedef struct { 
    EFI_DISK_INFO_PROTOCOL                DiskInfo;                // should be the first Entry
    SDIO_DEVICE_INTERFACE                *SdioDevInterface;
}SDIO_DISK_INFO;

typedef struct { 
    EFI_BLOCK_IO_PROTOCOL                BlkIo;                    // should be the first Entry
    SDIO_DEVICE_INTERFACE                *SdioDevInterface;
}SDIO_BLOCK_IO;

#if defined ( MDE_PKG_VERSION ) && (MDE_PKG_VERSION > 12) 

typedef struct { 
    EFI_ERASE_BLOCK_PROTOCOL             BlkErase;                   
    SDIO_DEVICE_INTERFACE                *SdioDevInterface;
} SDIO_BLOCK_ERASE;

#endif

struct _SDIO_DEVICE_INTERFACE{
    EFI_HANDLE                  SdioDeviceHandle;
    BOOLEAN                     MassStorageDevice;
    UINT8                       SlotNumber;
    UINT8                       DeviceState;
    CHAR16                      UnicodePNMString[27];
    SDIO_DEVICE_INFO            *SdioDevInfo;
    AMI_SDIO_BUS_PROTOCOL       *SdioBusInterface;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePathProtocol; 
    SDIO_BLOCK_IO               *SdioBlkIo;
#if defined ( MDE_PKG_VERSION ) && (MDE_PKG_VERSION > 12) 
    SDIO_BLOCK_ERASE            *SdioBlkErase;
#endif
    SDIO_DISK_INFO              *SdioDiskInfo;
    LIST_ENTRY                   SdioDeviceLink; 
};

extern EFI_GUID gSdioBusInitProtocolGuid;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif 

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**                 5555 Oakbrook Parkway, Norcross, GA 30093              **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
