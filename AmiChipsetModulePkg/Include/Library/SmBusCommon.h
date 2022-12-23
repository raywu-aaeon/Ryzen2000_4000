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
/** @file SmBusCommon.h
    SMBus common header file, define all the SMBus specific
    equates and structures in this file for DXE/PEI phase.

**/
//**********************************************************************
#ifndef __SMBUS_COMMON__H__
#define __SMBUS_COMMON__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi/UefiBaseType.h>
#include <IndustryStandard/SmBus.h>
#include <Library/IoLib.h>

#define SMBUS_ADDRESS_ARP           0x61 // SMBus Device Default Address

#define SMBUS_DATA_PREPARE_TO_ARP   0x01
#define SMBUS_DATA_RESET_DEVICE     0x02
#define SMBUS_DATA_GET_UDID_GENERAL 0x03
#define SMBUS_DATA_ASSIGN_ADDRESS   0x04

#define SMBUS_SPEC_RESERVED_ADDRESS 21
#define GET_UDID_BUFFER_SIZE        17

#define SMBUS_LOWEST_AVAILABLE_ADDRESS  0x08
#define SMBUS_HIGHEST_AVAILABLE_ADDRESS 0x77

#define SMBUS_BUS   ((SMBUS_BUS_DEV_FUN >> 8) & 0xff)
#define SMBUS_DEV   ((SMBUS_BUS_DEV_FUN >> 3) & 0x1f)
#define SMBUS_FUN   ( SMBUS_BUS_DEV_FUN & 0x07)

#define SMBUS_REG_PCICMD        0x04    // SmBus PCI Command Register
//----------------------------------------------------------------------;
//   AMD SB700 SM Bus I/O Registers                                     ;
//----------------------------------------------------------------------;
#define SMB_IOREG_HST_STS        0x00   // Host Status Reg.
#define     HST_STS_HOST_BUSY        0x01    // RO
#define     HST_STS_INTR             0x02    // R/WC
#define     HST_STS_DEV_ERR          0x04    // R/WC
#define     HST_STS_BUS_ERR          0x08    // R/WC
#define     HST_STS_FAILED           0x10    // R/WC
#define     HST_STS_SMBALERT_STS     0x20    // R/WC
#define     HST_STS_INUSE_STS        0x40    // R/WC
#define     HST_STS_BDS              0x80    // R/WC
#define     HST_STS_ALL              0xfe    // R/WC
#define     HST_STS_ERROR            0x1c    // R/WC
#define SMB_IOREG_HST_CNT        0x02   // Host Control Reg.
#define     HST_CNT_INTRENN          0x01    // RW
#define     HST_CNT_KILL             0x02    // RW
#define     HST_CNT_SMB_CMD          0x1C    // RW
#define         SMB_CMD_BYTE             0x04
#define         SMB_CMD_BYTE_DATA        0x08
#define         SMB_CMD_WORD_DATA        0x0c
#define         SMB_CMD_BLOCK            0x14
#define     HST_CNT_LAST_BYTE        0x20    // RW
#define     HST_CNT_START            0x40    // RW
#define     HST_CNT_PEC_EN           0x80    // RW
#define SMB_IOREG_AUX_CTL        SMB_IOREG_HST_CNT   // Auxiliary Control Reg.
#define     PEC_APPEND               0x20    // R/W
#define     PEC_EN                   0x80    // R/W

#define SMB_IOREG_HST_CMD        0x03   // Host Command Reg.
#define SMB_IOREG_XMIT_SLVA      0x04   // Transmit Slave Address Reg.
#define     XMIT_SLVA_RW             0x01    // RW
#define SMB_IOREG_HST_D0         0x05   // Host Data 0
#define SMB_IOREG_HST_D1         0x06   // Host Data 1
#define SMB_IOREG_HOST_BLOCK_DB  0x07   // Host Block Data Byte Reg.

#define SMB_IOREG01         0x01        // SMBusSlaveStatus
#define SMB_IOREG08         0x08        // SMBusSlaveControl
#define SMB_IOREG09         0x09        // SMBusShadowCmd
#define SMB_IOREG15         0x15        // SMBusCounter

#define SMBUS_NUM_RESERVED      21      // Number of device addresses
                                        // that are reserved by the
                                        // SMBus spec.
#define SMBUS_DEFAULT_ARP_ADDRESS 0xC2 >> 1
#define SMBUS_DATA_PREPARE_TO_ARP 0x01
#define SMBUS_DATA_RESET_DEVICE 0x02
#define SMBUS_DATA_GET_UDID_GENERAL 0x03
#define SMBUS_DATA_ASSIGN_ADDRESS 0x04
#define SMBUS_GET_UDID_LENGTH   17      // 16 byte UDID + 1 byte address

typedef struct _SMBUS_PRIVATE SMBUS_PRIVATE;

typedef VOID (* SMBUS_WAIT ) (
    IN  SMBUS_PRIVATE   *This,
    IN  UINTN           Microseconds
    );

extern EFI_GUID SmBusIdentifierGuid;
extern UINT8 SmBusPlatformReservedAddress[];
extern UINT8 SmBusPlatformReservedAddressSize;

/**
    AMI SMBUS driver private data structure

    UINT16               	SmBusBase               SMBUS device base IO address
    SMBUS_WAIT           	SmBusWait               Pointer to Wait function
    UINT8                	MaxDevices              Maximum number of supported devices
    UINT8                	BoardReservedAddressCount                  Number of board reserved addesses
    UINT8                	*BoardReservedAddressList                  Pointer to board reserved addresses list
    ArpDeviceCount               UINT8                   Number of current devices
    EFI_SMBUS_DEVICE_MAP 	*ArpDeviceList   	Pointer to list of current devices
 
**/
typedef struct _SMBUS_PRIVATE
{
    UINT16               SmBusBase;
    SMBUS_WAIT           SmBusWait;
    UINT8                MaxDevices;
    UINT8                BoardReservedAddressCount;
    UINT8                *BoardReservedAddressList;
    UINT8                ArpDeviceCount;
    EFI_SMBUS_DEVICE_MAP *ArpDeviceList;

} SMBUS_PRIVATE;


//*******************************************************
//      Shared functions prototypes
//*******************************************************

VOID SmBusRead (
    IN   UINT16 SmBusBase,
    IN   UINT16 Offset,
    IN   UINTN  ByteCount,
    OUT  UINT8  *Buffer
);

VOID SmBusWrite (
    IN   UINT16 SmBusBase,
    IN   UINT16 Offset,
    IN   UINTN  ByteCount,
    IN   UINT8  *Buffer
);

EFI_STATUS Execute (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN     EFI_SMBUS_DEVICE_COMMAND Command,
    IN     EFI_SMBUS_OPERATION      Operation,
    IN     BOOLEAN                  PecCheck,
    IN OUT UINTN                    *Length,
    IN OUT VOID                     *Buffer
);

EFI_STATUS CheckNotify (
    IN  SMBUS_PRIVATE            *Context,
    OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress,
    OUT UINTN                    *Data
);

EFI_STATUS ArpDevice (
    IN     SMBUS_PRIVATE            *Context,
    IN     BOOLEAN                  ArpAll,
    IN     EFI_SMBUS_UDID           *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
);

EFI_STATUS GetArpMap (
    IN     SMBUS_PRIVATE        *Context,
    IN OUT UINTN                *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
);

EFI_STATUS PrepareToArp (
    IN SMBUS_PRIVATE *Context
);

EFI_STATUS ArpDeviceDirected (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_UDID           *SmbusUdid,
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress
);

EFI_STATUS ArpDeviceFull (
    IN SMBUS_PRIVATE *Context
);

EFI_STATUS AssignAddress (
    IN SMBUS_PRIVATE        *Context,
    IN EFI_SMBUS_DEVICE_MAP *DeviceMap
);

EFI_STATUS GetUdidGeneral (
    IN  SMBUS_PRIVATE        *Context,
    OUT EFI_SMBUS_DEVICE_MAP *DeviceMap
);

BOOLEAN IsAddressAvailable (
    IN SMBUS_PRIVATE *Context,
    IN UINT8         Address
);

UINT8 GetAvailableAddress (
    IN SMBUS_PRIVATE *Context
);

VOID ConvertMapToBuffer (
    IN EFI_SMBUS_DEVICE_MAP *DeviceMap,
    OUT UINT8               *Buffer
);

VOID ConvertBufferToMap (
    OUT EFI_SMBUS_DEVICE_MAP *DeviceMap,
    IN UINT8                 *Buffer
);


//*******************************************************
//      SmBusPorting.c use only functions prototypes
//*******************************************************
typedef struct _SBSMBUS_PRIVATE SBSMBUS_PRIVATE;

typedef
UINT8
(EFIAPI *SMBUS_IO_READ) (
  IN SBSMBUS_PRIVATE    *Private,
  IN UINTN              Offset
  );

typedef
VOID
(EFIAPI *SMBUS_IO_WRITE) (
  IN SBSMBUS_PRIVATE    *Private,
  IN UINTN              Offset,
  IN UINTN              Data
  );

#pragma pack(1)
typedef struct _SBSMBUS_PRIVATE{
    SMBUS_PRIVATE               *Context;
    UINTN                       SlaveAddress;
    UINTN                       Command;
    UINTN                       Operation;
    UINTN                       Length;
    UINTN                       SmbusIoBase;
    UINT8                       CurrentHostStatus;
    BOOLEAN                     PecCheck;
    SMBUS_IO_READ               SmbusIoRead;
    SMBUS_IO_WRITE              SmbusIoWrite;
};
#pragma pack()

static
EFI_STATUS
SmbusAccess(
  IN SBSMBUS_PRIVATE *Private,
  IN OUT VOID *Buffer
  );

static
UINT8
SmbusIoRead (
  IN      SBSMBUS_PRIVATE  *Private,
  IN      UINTN           Offset
  );

static
VOID
SmbusIoWrite (
  IN      SBSMBUS_PRIVATE   *Private,
  IN      UINTN             Offset,
  IN      UINTN             Data
  );

#define SMBUS_DELAY_MACRO Private->Context->SmBusWait(Private->Context, 200); // 50 uSec

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
