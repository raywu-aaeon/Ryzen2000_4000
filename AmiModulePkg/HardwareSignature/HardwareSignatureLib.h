//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file  HardwareSignatureLib.h

  The header file for Hardware Signature Library. 

**/

#ifndef _HARDWARE_SIGNATURE_LIB_H_
#define _HARDWARE_SIGNATURE_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif
///----------------------------------------------------------------------
/// Include Files
///----------------------------------------------------------------------
#include <Token.h>
#include <Protocol/PciIo.h>
#include <Protocol/UsbIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/EdidDiscovered.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/BlockIo.h>
#include <IndustryStandard/AmiAtaAtapi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>

#define HARDWARE_CONFIG_DATA_VARIABLE L"HardwareConfigData"

#define FIRMWARE_UPDATE_COUNT_VARIABLE L"FirmwareUpdateCountVar"

#define IsRestoreMemoryType(MemoryType) \
    ((MemoryType) == EfiACPIReclaimMemory || \
    (MemoryType) == EfiACPIMemoryNVS || \
    (MemoryType) == EfiRuntimeServicesCode || \
    (MemoryType) == EfiRuntimeServicesData || \
    (MemoryType) == EfiReservedMemoryType )

#define VESA_BIOS_EXTENSIONS_EDID_BLOCK_SIZE 128

#if HARDWARE_SIGNATURE_PS2_CHANGE
/**
 *  Hardware Signature PS/2 Present Status Structure
 */ 
typedef struct  {
    
    BOOLEAN     Keyboard;                      ///< The present state of PS2 Keyboard in SIO_DEV_STATUS.
    BOOLEAN     Mouse;                         ///< The present state of PS2 Mouse in SIO_DEV_STATUS.  
    
} AMI_HARDWARE_SIGNATURE_PS2_DATA;
#endif

/**
 *  Identify LBA Format Data Structure, NVM Command Set Specific
 *  Figure 93 NVM Express 1.2 Spec
 */ 
typedef struct {
    
    UINT16      Ms;                             ///< Bits 15:0      Metadata Size
    UINT8       Lbads;                          ///< Bits 23:16     LBA Data Size
    UINT8       Rp : 2;                         ///< Bits 25:24     Relative Performance
    UINT8       Reserved1 :6;                   ///< Bits 31:26     Reserved
    
} NVME_LBA_FORMAT_DATA;

/**
 *  Identify Namespace Data Structure, NVM Command Set Specific
 *  Figure 92 NVM Express 1.2 Spec
 */ 
typedef struct {
    
    UINT64                  Nsize;              ///< Offset 7:0      Namespace Size
    UINT64                  Ncap;               ///< Offset 15:8     Namespace Capacity
    UINT64                  Nuse;               ///< Offset 23:16    Namespace Utilization
    UINT8                   Nsfeat;             ///< Offset 24       Namespace Features
    UINT8                   Nlbaf;              ///< Offset 25       Number of LBA Formats
    UINT8                   Flbas;              ///< Offset 26       Formatted LBA Size
    UINT8                   Mc;                 ///< Offset 27       Metadata Capabilities
    UINT8                   Dpc;                ///< Offset 28       End-to-end Data Protection Capabilities
    UINT8                   Dps;                ///< Offset 29       End-to-end Data Protection Type Settings
    UINT8                   Nmic;               ///< Offset 30       Namespace Multi-path I/O and Namespace Sharing Capabilities
    UINT8                   Rescap;             ///< Offset 31       Reservation Capabilities
    UINT8                   Fpi;                ///< Offset 32       Format Progress Indicator
    UINT8                   Reserved1;          ///< Offset 33       Reserved
    UINT16                  Nawun;              ///< Offset 35:34    Namespace Atomic Write Unit Normal
    UINT16                  Nawupf;             ///< Offset 37:36    Namespace Atomic Write Unit Power Fail
    UINT16                  Nacwu;              ///< Offset 39:38    Namespace Atomic Compare & Write Unit
    UINT16                  Nabsn;              ///< Offset 41:40    Namespace Atomic Boundary Size Normal
    UINT16                  Nabo;               ///< Offset 43:42    Namespace Atomic Boundary Offset
    UINT16                  Nabspf;             ///< Offset 45:44    Namespace Atomic Boundary Size Power Fail
    UINT8                   Reserved2[2];       ///< Offset 46:47    Reserved
    UINT8                   Nvmcap[16];         ///< Offset 63:48    NVM Capacity
    UINT8                   Reserved3[40];      ///< Offset 103:64   Reserved
    UINT8                   Nguid[16];          ///< Offset 119:104  Namespace Globally Unique Identifier
    UINT64                  Eui64;              ///< Offset 127:120  IEEE Extended Unique Identifier
    NVME_LBA_FORMAT_DATA    Lbaf[16];           ///< Offset 191:128  LBA Format 
    UINT8                   Reserved4[192];     ///< Offset 383:192  Reserved
    UINT8                   Vs[3712];           ///< Offset 4095:384 Vendor Specific   
} NVME_IDENTIFY_NAMESPACE_DATA;

/**
 *  ATA/ATAPI-6
 * 
 */ 
#define ATA_SERIAL_NUMBER_LENGTH  20 ///< Serial number (20 ASCII characters)

#define HARDWARE_SIGNATURE_FACS_ADDRESS_NUMBER 3

/**
 *  ---------------------------------------------------------------------------
 *  
 *  Function Definitions
 *  
 *  ---------------------------------------------------------------------------
 */ 
EFI_STATUS 
SetHardwareConfigDataToNvram (
    IN AMI_HARDWARE_SIGNATURE_CONFIG_DATA *HardwareConfigData );

BOOLEAN 
IsDifferentMemorySize(
    IN UINT32 CurMemorySizeMb, 
    IN UINT32 PreMemorySizeMb);

EFI_STATUS 
GetMemMapData(
    IN OUT AMI_HARDWARE_SIGNATURE_MEMORY_MAP_DATA *MemMapConfigData);

EFI_STATUS 
GetPciDeviceData(
    IN OUT AMI_HARDWARE_SIGNATURE_PCI_DATA *HardwarePciData);

EFI_STATUS 
GetUsbDeviceData(
    IN OUT AMI_HARDWARE_SIGNATURE_USB_DATA *HardwareUsbData);
        
EFI_STATUS 
GetDiskInfoData(
    OUT AMI_HARDWARE_SIGNATURE_DISK_DATA *HardwareDiskData);

EFI_STATUS 
GetVideoData(
    OUT AMI_HARDWARE_SIGNATURE_VIDEO_DATA *HardwareVideoData);
/**
 *  ---------------------------------------------------------------------------
 *  
 *  Functions to detect and set Hardware configurations
 *  
 *  ---------------------------------------------------------------------------
 */ 
#if HARDWARE_SIGNATURE_PS2_CHANGE
EFI_STATUS 
DetectPs2KeyboardMouseState(
    IN OUT AMI_HARDWARE_SIGNATURE_PS2_DATA *Present);

EFI_STATUS 
DetectAndSetPs2Config(
    IN UINTN BufferSize, 
    IN VOID *Buffer);
#endif

EFI_STATUS 
DetectAndSetMemorySizeConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

EFI_STATUS 
DetectAndSetMemoryMapConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

EFI_STATUS 
DetectAndSetPciConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);

#if HARDWARE_SIGNATURE_USB_CHANGE
EFI_STATUS 
DetectAndSetUsbConfig(
    IN UINTN BufferSize, 
    IN VOID *Buffer);
#endif

EFI_STATUS 
DetectAndSetVideoConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer );

EFI_STATUS 
DetectAndSetDiskConfig (
    IN UINTN BufferSize,
    IN VOID  *Buffer );


EFI_STATUS 
EFIAPI
UpdateHardwareSignatureData(
    IN EFI_EVENT Event, 
    IN VOID *Context);

VOID 
QuickSort(
    IN OUT UINT32 *ChecksumData, 
    IN     UINT32 LChecksumPosition, 
    IN     UINT32 RChecksumPosition);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************



