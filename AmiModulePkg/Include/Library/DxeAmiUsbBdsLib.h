//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file DxeAmiUsbBdsLib.h
    Head file for AmiUsbBdsLib library
**/

#ifndef __DXE_AMI_USB_BDS_LIB_H__
#define __DXE_AMI_USB_BDS_LIB_H__

#define NOT_ON_USB_ASSIGN_ROOT_PORT 0xFF 

typedef struct _UsbPortLayerLink UsbPortLayerLink;
struct _UsbPortLayerLink{
    UINT8       TotalDviceOfLayer;
    UINT8       ParentAddress;
    UINT8       AddressOfLayer;
};

typedef struct {
  UINTN                     Bus;
  UINTN                     Device;
  UINTN                     Function;
  UINT8                     RootPort;
} USBDEVICE_HCROOTPORT;

EFI_STATUS
EFIAPI
UsbDeviceHcRootPortInformation(
        IN EFI_HANDLE                   UsbIoDeviceHandle,
        IN OUT USBDEVICE_HCROOTPORT     *UsbDeviceHcRootPort
);

EFI_STATUS
EFIAPI
UninstallUsbIo(
    IN EFI_HANDLE   UsbPciControllerHandle,
    IN UINT8        PortNumber,
    IN UINT32       UsbHostPciVidDid        OPTIONAL,
    IN UINT32       UsbDeviceVidDid         OPTIONAL,
    IN VOID         *HostControllerBridge   OPTIONAL
);

VOID
EFIAPI
UsbAddHcEvent(
);
#endif //__DXE_AMI_USB_BDS_LIB_H__

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
