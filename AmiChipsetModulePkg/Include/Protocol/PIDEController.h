//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file PIDEController.h
    The protocol for IDE controller.

**/
//**********************************************************************

#ifndef _PIDEController_
#define _PIDEController_

#ifdef __cplusplus
extern "C" {
#endif

#define IDE_CONTROLLER_PROTOCOL_GUID \
        { 0x20E28787, 0xDF32, 0x4BDA, 0xB7, 0xE7, 0xCB, 0xBD, 0xA3, 0x37, 0x1E, 0xF8 }

#define SATA_CONTROLLER_PROTOCOL_GUID \
        { 0x2acb6627, 0xdf02, 0x4e23, 0xb4, 0xf9, 0x6a, 0x93, 0xfa, 0x6e, 0x9d, 0xa6 }

// Forward reference for pure ANSI compatability
typedef struct _IDE_CONTROLLER_PROTOCOL IDE_CONTROLLER_PROTOCOL;
typedef struct _IDENTIFY_DATA IDENTIFY_DATA;
typedef struct _IDE_DEVICE_INTERFACE IDE_DEVICE_INTERFACE;
typedef struct _IDE_BUS_PROTOCOL IDE_BUS_PROTOCOL;

#pragma pack(1)

typedef struct {
    UINT8   Register;
    UINT8   And_Mask;
    UINT8   Or_Mask;
} IDE_CONTROLLER_INIT_DATA;

//  Equates used for Flag
#define     Acoustic_Support_Enable             0x01
#define     S3_RESUME_UNLOCK_HDD_PASSWORD       0x02            // Set bit 1 in Flags only if HDD loses power in S3 state.

typedef struct {
    UINT8   PrimaryChannel;
    UINT8   PrimaryMasterDevice;
    UINT8   PrimarySlaveDevice;
    UINT8   SecondaryChannel;
    UINT8   SecondaryMasterDevice;
    UINT8   SecondarySlaveDevice;
    UINT8   BusMasterEnable;
    UINT8   HPMask;
    UINT8   Flags;
    UINT8   Acoustic_Management_Level;
} CONTROLLER_INFO;


typedef EFI_STATUS (*EFI_IDE_CONTROLLER_SET_PIO_TIMING) (
    IDE_DEVICE_INTERFACE        *IdeDevice
);

typedef
EFI_STATUS
(*EFI_IDE_CONTROLLER_SET_DMA_TIMING) (
    IDE_DEVICE_INTERFACE        *IdeDevice
);

typedef
EFI_STATUS
(*EFI_IDE_CONTROLLER_GET_MODE) (
    IDE_DEVICE_INTERFACE        *IdeDevice
);

typedef
EFI_STATUS
(*EFI_IDE_CONTROLLER_GET_CONTROLLER_INFO) (
    IN EFI_HANDLE               Controller,
    IN OUT CONTROLLER_INFO      *ControllerInfo
);

typedef
EFI_STATUS
(*EFI_IDE_HP_DEVICE_CHANGE) (
    EFI_PCI_IO_PROTOCOL         *PciIO,
    UINT8                       HPMask,
    UINT8                       *CurrentStatus
);


typedef
EFI_STATUS
(*EFI_IDE_DISABLE_ENABLE_CHANNEL) (
    EFI_PCI_IO_PROTOCOL         *PciIO,
    UINT8                       Channel,
    UINT8                       Device,
    BOOLEAN                     DisableEnable
);

typedef struct _IDE_CONTROLLER_PROTOCOL {
    UINT8                               Max_Channel;
    EFI_PCI_IO_PROTOCOL                 *PciIO;
    EFI_HANDLE                          ControllerHandle;
    EFI_IDE_CONTROLLER_GET_CONTROLLER_INFO IdeGetControllerInfo;
    EFI_IDE_CONTROLLER_SET_PIO_TIMING   IdeSetPioMode;
    EFI_IDE_CONTROLLER_SET_DMA_TIMING   IdeSetDmaMode;
    EFI_IDE_CONTROLLER_GET_MODE         GetbestPioDmaMode;
    EFI_IDE_HP_DEVICE_CHANGE            HPCheckForDeviceChange;
    EFI_IDE_DISABLE_ENABLE_CHANNEL      HPDisableEnableChannel;
    CHAR16 *                            Controllername;
}IDE_CONTROLLER_PROTOCOL;

#pragma pack()



/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
