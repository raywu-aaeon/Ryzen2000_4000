//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SdioDriver.h
    Header file for the SIO

**/

#ifndef _AMI_SDIO_DRIVER_H_
#define _AMI_SDIO_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------

#include <Token.h>
#include <Uefi.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Protocol/DebugSupport.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <IndustryStandard/Pci.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/DevicePath.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/SdioBus.h>
#include "SdioDef.h"
#include <Protocol/AmiSdEmmcControllerInitProtocol.h>

#define  ZeroMemory(Buffer,Size) gBS->SetMem(Buffer,Size,0)

#define LANGUAGE_CODE_ENGLISH    "en-US"

#define     DEVICE_DISABLED                     0
#define     DEVICE_IN_RESET_STATE               1
#define     DEVICE_DETECTION_FAILED             2
#define     DEVICE_DETECTED_SUCCESSFULLY        3
#define     DEVICE_CONFIGURED_SUCCESSFULLY      4
#define     DEVICE_REMOVED                      5
#define     BLKIO_REVISION                      1


//-----------------------------------------------
//      ERROR CODE REPORTED TO CALLER
//-----------------------------------------------
#define SDIO_WRITE_PROTECT_ERR          0x003   // Write protect error
#define SDIO_TIME_OUT_ERR               0x080   // Command timed out error
#define SDIO_DRIVE_NOT_READY_ERR        0x0AA   // Drive not ready error
#define SDIO_DATA_CORRECTED_ERR         0x011   // Data corrected error
#define SDIO_PARAMETER_FAILED           0x007   // Bad parameter error
#define SDIO_MARK_NOT_FOUND_ERR         0x002   // Address mark not found error
#define SDIO_NO_MEDIA_ERR               0x031   // No media in drive
#define SDIO_READ_ERR                   0x004   // Read error
#define SDIO_UNCORRECTABLE_ERR          0x010   // Uncorrectable data error
#define SDIO_BAD_SECTOR_ERR             0x00A   // Bad sector error
#define SDIO_GENERAL_FAILURE            0x020   // Controller general failure

#define BAR_64_32_SUPPORT_BIT           BIT1+BIT2
#define BAR_64_BIT                      4

#define MAX_NUMBLOCK_16BIT              0xFFFF

// 8KB Memory for Transfer Buffer.
// If the device supports 64 Bit addressing, For ADMA transfer it should be 8KB aligned.
// For 32 Bit addressing 4KB aligned
#define SDIO_SIZE  8192

//
// Device Path for SD and MMC devices 
//   
#define SDIO_DEVICE_PATH_LENGTH SATA_DEVICE_PATH_LENGTH

//
//SDIO Setup fields
//
#pragma pack(1)
typedef struct{
    UINT8  SdEmul;
    UINT64 SdMmcAddress;
}SDMMC_EMULATION;

typedef struct {
    UINT8           SdioMode;
    UINT8           SdioMassDevNum;
    UINT8           IoDeviceType[8];
    SDMMC_EMULATION SdioEmu[8];
} SDIO_DEV_CONFIGURATION;
#pragma pack()
///
/// SDIO Device Path SubType.
///
#define MSG_SDIO_DP               0x1A
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///Slot Number 
  UINT8                           SlotNumber;
} SDIO_DEVICE_PATH;

// Driver Binding Protocol functions

EFI_STATUS
EFIAPI
SdioDriverSupported (
    IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_HANDLE                   Controller,
    IN  EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
);

EFI_STATUS
EFIAPI
SdioDriverStart (
    IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_HANDLE                   Controller,
    IN  EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
SdioDriverStop (
    IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_HANDLE                   Controller,
    IN  UINTN                        NumberOfChildren,
    IN  EFI_HANDLE                   *ChildHandleBuffer
);

EFI_STATUS
InstallSdioBusProtocol (
    IN  EFI_HANDLE                   Controller,
    IN  OUT AMI_SDIO_BUS_PROTOCOL    *SdioBusInterface,
    IN  VOID                         *ControllerInterface,
    IN  AMI_SD_EMMC_CONTROLLER_TYPE  ControllerType
);

EFI_STATUS
SdioInitController (
    IN  OUT AMI_SDIO_BUS_PROTOCOL    *SdioBusInterface
);

EFI_STATUS
CreateSdioDevicePath (
    IN  EFI_DRIVER_BINDING_PROTOCOL      *This,
    IN  EFI_HANDLE                       Controller,
    IN  SDIO_DEVICE_INTERFACE            *SdioDevInterface,
    IN  OUT EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
);

EFI_STATUS
InitSdioBlockIO (
    IN  SDIO_DEVICE_INTERFACE            *SdioDevInterface
);

EFI_STATUS
InitSdioDiskInfo (
    IN  SDIO_DEVICE_INTERFACE            *SdioDevInterface
);
#if defined ( MDE_PKG_VERSION ) && (MDE_PKG_VERSION > 12) 
EFI_STATUS
InitSdioBlockErase (
    IN  SDIO_DEVICE_INTERFACE            *SdioDevInterface
);
#endif
SDIO_DEVICE_INTERFACE *
GetSdioDevInterface (
    IN  AMI_SDIO_BUS_PROTOCOL            *SdioBusInterface,
    IN  UINT8                            Port
);

EFI_STATUS
DetectAndConfigureDevice (
    IN  EFI_DRIVER_BINDING_PROTOCOL      *This,
    IN  EFI_HANDLE                       Controller,
    IN  EFI_DEVICE_PATH_PROTOCOL         *RemainingDevicePath,
    IN  AMI_SDIO_BUS_PROTOCOL            *SdioBusInterface,
    IN  UINT8                            PortNo
);

EFI_STATUS
SdioDetectDeviceAndConfigure (
    IN  AMI_SDIO_BUS_PROTOCOL           *SdioBusInterface,
    IN  UINT8                           Port
);

EFI_STATUS
CheckAndConfigureSdioDevice (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
);

EFI_STATUS
SdIoSetVoltage (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
);

EFI_STATUS
EFIAPI
SdioBlkRead (
    IN  EFI_BLOCK_IO_PROTOCOL        *This,
    IN  UINT32                       MediaId,
    IN  EFI_LBA                      Lba,
    IN  UINTN                        BufferSize,
    OUT VOID                         *Buffer
);

EFI_STATUS
EFIAPI
SdioBlkWrite (
    IN  EFI_BLOCK_IO_PROTOCOL        *This,
    IN  UINT32                       MediaId,
    IN  EFI_LBA                      Lba,
    IN  UINTN                        BufferSize,
    OUT VOID                         *Buffer
);

EFI_STATUS
SdioBlkReadWrite (
    IN  EFI_BLOCK_IO_PROTOCOL       *This,
    IN  UINT32                      MediaId,
    IN  EFI_LBA                     Lba,
    IN  UINTN                       BufferSize,
    OUT VOID                        *Buffer,
    BOOLEAN                         READWRITE
);

EFI_STATUS
EFIAPI
SdioReset (
    IN  EFI_BLOCK_IO_PROTOCOL        *This,
    IN  BOOLEAN                      ExtendedVerification
);

EFI_STATUS
EFIAPI
SdioBlkFlush (
    IN  EFI_BLOCK_IO_PROTOCOL        *This
);

EFI_STATUS
SdMmcCheckDevicePresence (
    IN  SDIO_DEVICE_INTERFACE        *SdioBusInterface,
    IN  UINT8                        Port
);

EFI_STATUS
SdioReadDevice (
    IN  SDIO_DEVICE_INTERFACE        *SdioDevInterface,
    IN  UINT8                        Port,
    IN  EFI_LBA                      Lba,
    IN  UINT32                       NumBlks,
    IN  VOID                         *BufferAddress
);

EFI_STATUS
SdioWriteDevice (
    IN  SDIO_DEVICE_INTERFACE        *SdioDevInterface,
    IN  UINT8                        Port,
    IN  EFI_LBA                      Lba,
    IN  UINT32                       NumBlks,
    IN  VOID                         *BufferAddress
);

EFI_STATUS 
EFIAPI
SdioCtlDriverName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  CHAR8                         *Language,
    OUT CHAR16                        **DriverName
);

EFI_STATUS
EFIAPI
SdioCtlGetControllerName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  EFI_HANDLE                    ControllerHandle,
    IN  EFI_HANDLE                    ChildHandle        OPTIONAL,
    IN  CHAR8                         *Language,
    OUT CHAR16                        **ControllerName
);


VOID
GetSetSdioAccessMode ();

EFI_STATUS
TransferSdioDataToSmram ();


EFI_STATUS
SdioGetMassDeviceInformation (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Port
);

EFI_STATUS
SdioRead (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Port,
    IN  EFI_LBA                 Lba,
    IN  UINT32                  NumBlks,
    IN  VOID                    *BufferAddress
);

EFI_STATUS
SdioWrite (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Port,
    IN  EFI_LBA                 Lba,
    IN  UINT32                  NumBlks,
    IN  VOID                    *BufferAddress
);

EFI_STATUS 
SdMmcCheckDevicePresence (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Port
);

EFI_STATUS
SdCheckDeviceRemoval (
    IN  AMI_SDIO_BUS_PROTOCOL    *SdioBusInterface,
    IN  UINT8                    Port
);
VOID
ZeroMemorySmm (
    VOID  *Buffer,
    UINTN Size
);

UINT8
GetDevEntry (
    IN  UINT64   SdioBaseAddress
);

VOID
InitilizeSdioSetupConfiguration(
);

UINT8
SDIOGetFormatType (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT8               *SdioReadData,
    OUT UINT16              *EmuType
);

VOID
SdioMassUpdateCylinderInfo (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port 
);

UINT8 
SDIOSetDefaultGeometry ( 
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
);

UINT8
SDIOValidatePartitionTable (
    IN  UINT8       *Buffer,
    IN  UINT32      dMaxLBA,
    OUT UINT8       **ActPartAddr
);

UINT8
SDIOUpdateCHSFromBootRecord (
    IN  SDIO_DEVICE_INFO*   SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT8*              SdBootRecord
);

VOID SdioDelay(
    IN UINTN    DelayValue
);

typedef struct _SDIO_TIME_TICK{
    UINT64          Detect;
    UINT64          After_detect;
}SDIO_TIME_TICK;

EFI_STATUS 
IoCardEnableHook (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Slot
);

VOID
EFIAPI
SdioAllDriverConnectedCallback (
    EFI_EVENT    Event,
    VOID         *Context
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//**********************************************************************
