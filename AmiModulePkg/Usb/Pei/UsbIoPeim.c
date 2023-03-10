//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file UsbIoPeim.c
    This file belongs to "Framework".
    This file is modified by AMI to include copyright message,
    appropriate header and integration code.
    This file contains generic routines needed for USB recovery
    PEIM

**/
/**
The module is used to implement Usb Io PPI interfaces.

Copyright (c) 2006 - 2014, Intel Corporation. All rights reserved. <BR>
  
This program and the accompanying materials
are licensed and made available under the terms and conditions
of the BSD License which accompanies this distribution.  The
full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "UsbPei.h"
#include <Ppi/IoMmu.h>

extern EDKII_IOMMU_PPI *gEdk2IoMmuPpi;

#define PAGESIZE  4096

EFI_STATUS PeiUsbFindEndpoint(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    UINT8               Endpoint,
    UINT8               *EpDescIndex
)
{
    UINT8       EpIndx;
    EFI_USB_ENDPOINT_DESCRIPTOR *EndpointDescriptor;
    EFI_STATUS  Status;

    for (EpIndx = 0; EpIndx < MAX_ENDPOINT; EpIndx++) {
        Status = PeiUsbGetEndpointDescriptor( PeiServices,
            UsbIoPpi, EpIndx, &EndpointDescriptor );
        if (EFI_ERROR(Status)) return Status;

        if (EndpointDescriptor->EndpointAddress == Endpoint) {
            break;
        }
    }

    if (EpIndx == MAX_ENDPOINT) {
        return EFI_INVALID_PARAMETER;
    }

    *EpDescIndex = EpIndx;

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
PeiUsbControlTransfer(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN PEI_USB_IO_PPI               *This,
    IN EFI_USB_DEVICE_REQUEST       *Request,
    IN EFI_USB_DATA_DIRECTION       Direction,
    IN UINT32                       Timeout,
    IN OUT VOID                     *Data       OPTIONAL,
    IN UINTN                        DataLength  OPTIONAL,
    OUT UINT32                      *UsbStatus
)
{
    EFI_STATUS     Status;
    PEI_USB_DEVICE *PeiUsbDev;
    PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( This );
    UsbHcPpi = PeiUsbDev->UsbHcPpi;

    Status = UsbHcPpi->ControlTransfer(
                         PeiServices,
                         UsbHcPpi,
                         PeiUsbDev->DeviceAddress,
                         PeiUsbDev->DeviceSpeed,
                         (UINT8)PeiUsbDev->MaxPacketSize0,
                         PeiUsbDev->TransactionTranslator,
                         Request,
                         Direction,
                         Data,
                         &DataLength,
                         Timeout,
                         UsbStatus
                         );

    return Status;
}


EFI_STATUS
EFIAPI
PeiUsbBulkTransfer(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *This,
    IN UINT8            DeviceEndpoint,
    IN OUT VOID         *Data,
    IN OUT UINTN        *DataLength,
    IN UINTN            Timeout,
    OUT UINT32          *UsbStatus
)
{
    EFI_STATUS                  Status;
    PEI_USB_DEVICE              *PeiUsbDev;
    PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi;
    UINT16                      MaxPacketLength;
    UINT8                       DataToggle;
    UINT8                       OldToggle;
    UINT8                       EndpointIndex;
    EFI_PHYSICAL_ADDRESS        TempAddress;
    VOID                        *Mapping = NULL;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( This );
    UsbHcPpi = PeiUsbDev->UsbHcPpi;

    Status = PeiUsbFindEndpoint(PeiServices, This, DeviceEndpoint, &EndpointIndex);
    if (EFI_ERROR(Status)) return Status;

    MaxPacketLength = (PeiUsbDev->EndpointDesc[EndpointIndex]->MaxPacketSize);

    if ( ( PeiUsbDev->DataToggle & (1 << EndpointIndex) ) != 0 ) {
        DataToggle = 1;
    }
    else {
        DataToggle = 0;
    }

    OldToggle = DataToggle;

    if (gEdk2IoMmuPpi) {
        // 0 = BulkIn, 1 = BulkOut
        if (DeviceEndpoint & BIT7) {
            Status = gEdk2IoMmuPpi->Map (
                         gEdk2IoMmuPpi,
                         EdkiiIoMmuOperationBusMasterWrite,
                         Data,
                         DataLength,
                         (EFI_PHYSICAL_ADDRESS*)&TempAddress,
                         &Mapping
                         );
        } else {
            Status = gEdk2IoMmuPpi->Map (
                         gEdk2IoMmuPpi,
                         EdkiiIoMmuOperationBusMasterRead,
                         Data,
                         DataLength,
                         (EFI_PHYSICAL_ADDRESS*)&TempAddress,
                         &Mapping
                         );
        }
        if (EFI_ERROR(Status)){
            return Status;
        }

        Data = (VOID*)(UINTN)TempAddress;
    }

    Status = UsbHcPpi->BulkTransfer(
                         PeiServices,
                         UsbHcPpi,
                         PeiUsbDev->DeviceAddress,
                         DeviceEndpoint,
                         PeiUsbDev->DeviceSpeed,
                         MaxPacketLength,
                         PeiUsbDev->TransactionTranslator,
                         Data,
                         DataLength,
                         &DataToggle,
                         Timeout,
                         UsbStatus
                         );

    if (OldToggle != DataToggle) {
        PeiUsbDev->DataToggle =
            (UINT8) ( PeiUsbDev->DataToggle ^ (1 << EndpointIndex) );
    }

    if (gEdk2IoMmuPpi && Mapping) {
        gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, Mapping);
    }

    return Status;
}


EFI_STATUS
EFIAPI
PeiUsbSyncInterruptTransfer(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *This,
    IN     UINT8        DeviceEndpoint,
    IN OUT void         *Data,
    IN OUT UINTN        *DataLength,
    IN     UINTN        Timeout
)
{
    EFI_STATUS      Status;
    PEI_USB_DEVICE  *PeiUsbDev;
    PEI_USB_HOST_CONTROLLER_PPI *UsbHcPpi;
    UINT32          TransferResult;
    UINT8           DataToggle;
    UINT8           OldToggle;
    UINT8           EndpointIndex;
    UINTN           MaxPacketLength;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( This );
    UsbHcPpi = PeiUsbDev->UsbHcPpi;

    Status = PeiUsbFindEndpoint(PeiServices, This, DeviceEndpoint, &EndpointIndex);
    if (EFI_ERROR(Status)) return Status;

    MaxPacketLength = (PeiUsbDev->EndpointDesc[EndpointIndex]->MaxPacketSize);

    if ( ( PeiUsbDev->DataToggle & (1 << EndpointIndex) ) != 0 ) {
        DataToggle = 1;
    }
    else {
        DataToggle = 0;
    }

    OldToggle = DataToggle;

    Status = UsbHcPpi->SyncInterruptTransfer(
                         PeiServices,
                         UsbHcPpi,
                         PeiUsbDev->DeviceAddress,
                         DeviceEndpoint,
                         PeiUsbDev->DeviceSpeed,
                         (UINT8)MaxPacketLength,
                         PeiUsbDev->TransactionTranslator,
                         Data,
                         DataLength,
                         &DataToggle,
                         Timeout,
                         &TransferResult
                         );

    if (OldToggle != DataToggle) {
        PeiUsbDev->DataToggle =
            (UINT8) ( PeiUsbDev->DataToggle ^ (1 << EndpointIndex) );
    }

    return Status;
}


EFI_STATUS
EFIAPI
PeiUsbGetInterfaceDescriptor(
    IN EFI_PEI_SERVICES             **PeiServices,
    IN PEI_USB_IO_PPI               *This,
    IN EFI_USB_INTERFACE_DESCRIPTOR **InterfaceDescriptor
)
{
    PEI_USB_DEVICE *PeiUsbDev;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( This );

    *InterfaceDescriptor = PeiUsbDev->InterfaceDesc;

    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
PeiUsbGetEndpointDescriptor(
    IN EFI_PEI_SERVICES            **PeiServices,
    IN PEI_USB_IO_PPI              *This,
    IN UINT8                       EndpointIndex,
    IN EFI_USB_ENDPOINT_DESCRIPTOR **EndpointDescriptor
)
{
    PEI_USB_DEVICE *PeiUsbDev;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( This );

    if (EndpointIndex >= PeiUsbDev->InterfaceDesc->NumEndpoints) {
        return EFI_INVALID_PARAMETER;
    }

    *EndpointDescriptor = PeiUsbDev->EndpointDesc[EndpointIndex];

    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
PeiUsbPortReset(
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *This
)
{
    PEI_USB_DEVICE *PeiUsbDev;
    EFI_STATUS     Status;
    UINT8 Address;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( This );

    ResetRootPort(
        PeiServices,
        PeiUsbDev->UsbHcPpi,
        PeiUsbDev->DeviceAddress
        );

    //
    // Set address
    //
    Address = PeiUsbDev->DeviceAddress;
    PeiUsbDev->DeviceAddress = 0;

    Status = PeiUsbSetDeviceAddress(
               PeiServices,
               This,
               Address
               );

    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    PeiUsbDev->DeviceAddress = Address;

    //
    // Set default configuration
    //
    Status = PeiUsbSetConfiguration(
               PeiServices,
               This
               );

    return Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
