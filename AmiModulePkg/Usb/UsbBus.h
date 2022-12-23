//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file UsbBus.h
    AMI USB bus driver header file

**/

#ifndef _USBBUS_INC_
#define _USBBUS_INC_

#include "Tree.h"
#include <AmiDef.h>
#include <UsbDef.h>
#include <Protocol/UsbHc.h>
#include <Protocol/UsbIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/AmiUsbIad.h>


#define USB_MAXLANID          16
#define USB_MAXCHILDREN       8
#define USB_MAXCONTROLLERS    4
#define USB_NAME_STRING_128   128

#define USB_US_LAND_ID        0x0409

#pragma pack(push, 1)

typedef struct {
  UINT8  Length;
  UINT8  DescriptorType;
} USB_DESCRIPTOR_T;

typedef struct {
  UINT8  Len;
  UINT8  Desctype;
  UINT16 LangId[1];
} LANG_TABLE_T;

#pragma pack(pop)

enum node_type_enum { NodeHC, NodeDevice, NodeGroup };




typedef struct _USBBUS_HC_T USBBUS_HC_T;
struct _USBBUS_HC_T{
    UINT8                               Type;
    EFI_HANDLE                          Handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *Dp;
    EFI_USB2_HC_PROTOCOL                *Hc;     // USB_HC_ installed on controller
    HC_STRUC                            *HcStruc;
    TREENODE_T                          Node;
};

#define COMPRESS_EP_ADR(a)              ( a & 0xF )

typedef struct _USBIAD_DATA_T USBIAD_DATA_T;
struct _USBIAD_DATA_T{
    EFI_HANDLE  Handle;
    UINTN       DataSize;
};

typedef struct _IAD_DETAILS IAD_DETAILS;
struct _IAD_DETAILS{
    UINT8                                       ConfigIndex;
    AMI_USB_INTERFACE_ASSOCIATION_DESCRIPTOR    *Descriptor;
    EFI_HANDLE                                  IadHandle;
    AMI_USB_IAD_PROTOCOL                        Iad;
    USBIAD_DATA_T                               *Data;
};

typedef struct _DEVGROUP_T DEVGROUP_T;
struct _DEVGROUP_T{
    UINT8                               Type;
    EFI_HANDLE                          handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *Dp;
    EFI_USB2_HC_PROTOCOL                *Hc;    //  USB_HC_ that the controller is attached to
    DEV_INFO                            *DevInfo;
    HC_STRUC                            *HcStruc;
    LANG_TABLE_T                        *LangTable;
    EFI_USB_STRING_DESCRIPTOR           *ManufacturerStrDesc;
    EFI_USB_STRING_DESCRIPTOR           *ProductStrDesc;
    EFI_USB_STRING_DESCRIPTOR           *SerialNumberStrDesc;
    EFI_USB_DEVICE_DESCRIPTOR           DevDesc;
    EFI_USB_CONFIG_DESCRIPTOR           **ConfigDesc;
    EFI_USB_ENDPOINT_DESCRIPTOR         *Endpoints[0x20];
    EFI_USB_ENDPOINT_DESCRIPTOR         *A2Endpoint[0x20];
    UINT8                               EndpointCount;

    INT32                               ActiveConfig; // index in configs
    UINT8                               ConfigCount;
    BOOLEAN                             DevDescPresent;
    TREENODE_T                          Node;
    UINT8                               IadCount;
    IAD_DETAILS                         *IadDetails;
};

#define USB_MAX_ALT_IF 16

typedef struct _USBDEV_T USBDEV_T;
struct _USBDEV_T{
    UINT8                               Type;
    EFI_HANDLE                          Handle; // handle of the controller
    EFI_DEVICE_PATH_PROTOCOL            *Dp;
    EFI_USB2_HC_PROTOCOL                *Hc; //USB_HC_ that the controller is attached to
    DEV_INFO                            *DevInfo;
    HC_STRUC                            *HcStruc;
    CHAR16                              *Name;
    BOOLEAN                             ConnectCompleted; //was ConnectControllers successful?
    UINT8                               FirstEndpoint[USB_MAX_ALT_IF];
    UINT8                               EndEndpoint[USB_MAX_ALT_IF];
    EFI_USB_INTERFACE_DESCRIPTOR        *InterfaceDesc[USB_MAX_ALT_IF];
    UINT32                              LoadedAltIfMap;
    UINT8                               Speed;
    EFI_USB_IO_PROTOCOL                 Io;
    TREENODE_T                          Node;
    UINT8                               AsyncEndpoint;
};

EFI_STATUS 
EFIAPI
UsbBusSupported (
  EFI_DRIVER_BINDING_PROTOCOL     *This,
  EFI_HANDLE                      controller,
  EFI_DEVICE_PATH_PROTOCOL        *DevicePathProtocol
  );

EFI_STATUS
EFIAPI
UsbBusStart (
  EFI_DRIVER_BINDING_PROTOCOL     *This,
  EFI_HANDLE                      controller,
  EFI_DEVICE_PATH_PROTOCOL        *DevicePathProtocol
  );

EFI_STATUS
EFIAPI
UsbBusStop (
  EFI_DRIVER_BINDING_PROTOCOL     *This,
  EFI_HANDLE                      controller,
  UINTN                           NumberOfChildren,
  EFI_HANDLE                      *ChildHandleBuffer
  );

//EFI_STATUS UsbBusInit(EFI_HANDLE  ImageHandle,EFI_HANDLE  ServiceHandle);

USBDEV_T    *UsbIo2Dev(EFI_USB_IO_PROTOCOL  *p);
DEVGROUP_T  *UsbDevGetGroup(USBDEV_T  *Dev);
DEV_INFO    *FindDevStruc(EFI_HANDLE Controller);

UINT8*
UsbSmiGetDescriptor(
    HC_STRUC  *Hc,
    DEV_INFO  *Dev,
    UINT8     *Buf,
    UINT16    Len,
    UINT8     DescType,
    UINT8     DescIndex
);

UINT16
UsbSmiControlTransfer (
    HC_STRUC    *HCStruc,
    DEV_INFO    *DevInfo,
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length
);

UINT32
UsbSmiIsocTransfer(
    HC_STRUC    *HcStruc,
    DEV_INFO    *DevInfo,
    UINT8       XferDir,
    UINT8       *Buffer,
    UINT32      Length,
    UINT8       *Async
);

UINT8
UsbResetAndReconfigDev(
    HC_STRUC    *HostController,
    DEV_INFO    *Device
);

UINT8
UsbDevDriverDisconnect(
    HC_STRUC    *HostController,
    DEV_INFO    *Device
);

UINT8
UsbSmiActivatePolling (
    HC_STRUC    *HostController,
    DEV_INFO    *DevInfo
);

UINT8
UsbSmiDeactivatePolling (
    HC_STRUC    *HostController,
    DEV_INFO    *DevInfo
);

#define GETBIT(Bitarray, Value, Bit) \
    ((Value) = (UINT8)(((Bitarray) & (1 << (Bit))) >> (Bit)))\

#define SETBIT(Bitarray, Value, Bit) \
    (Bitarray) = (((Bitarray) & ~(1 << (Bit))) | (((Value) & 1) << (Bit)) )\

#define IsSlow(Dev) Dev->Speed
#define GetSpeed(Dev) Dev->Speed

VOID InstallDevice(DEV_INFO* DevInfo);
BOOLEAN eUninstallDevice(VOID* Node, VOID* Context);
EFI_STATUS RemoveDevInfo(DEV_INFO* DevInfo);


#endif //_USBBUS_INC_

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************