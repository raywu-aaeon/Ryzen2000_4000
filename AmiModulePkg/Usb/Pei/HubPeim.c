//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file HubPeim.c
    This file belongs to "Framework".
    This file is modified by AMI to include copyright message,
    appropriate header and integration code.
    This file contains generic routines needed for USB recovery
    PEIM

**/
/**
Usb Hub Request Support In PEI Phase

Copyright (c) 2006 - 2014, Intel Corporation. All rights reserved.<BR>
  
This program and the accompanying materials
are licensed and made available under the terms and conditions
of the BSD License which accompanies this distribution.  The
full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
//#include "HubPeim.h"
#include "UsbPei.h"
//#include "PeiUsbLib.h"

#include "Ppi/Stall.h"
#include <Ppi/IoMmu.h>
#include <Library/DebugLib.h>

extern EFI_PEI_STALL_PPI *gUsbPeiStall;
extern EDKII_IOMMU_PPI *gEdk2IoMmuPpi;
UINT32    *gHubPortStatusPtr = NULL;
UINT32    *gHubStatus = NULL;

typedef struct {
    UINT32	HubPortStatus;
    UINT32	EfiPortStatus;
} EFI_USB_PORT_STATUS_MAP;

EFI_USB_PORT_STATUS_MAP  HubPortStatusMap[] = {
    // Port status bits
    {HUB_PORT_CONNECTION, USB_PORT_STAT_CONNECTION},
    {HUB_PORT_ENABLE, USB_PORT_STAT_ENABLE},
    {HUB_PORT_SUSPEND, USB_PORT_STAT_SUSPEND},
    {HUB_PORT_OVER_CURRENT, USB_PORT_STAT_OVERCURRENT},
    {HUB_PORT_RESET, USB_PORT_STAT_RESET},
    {HUB_PORT_POWER, USB_PORT_STAT_POWER},
    {HUB_PORT_LOW_SPEED, USB_PORT_STAT_LOW_SPEED},
    {HUB_PORT_HIGH_SPEED, USB_PORT_STAT_HIGH_SPEED},
    // Port status change bits
    {HUB_C_PORT_CONNECTION << 16, USB_PORT_STAT_C_CONNECTION << 16},
    {HUB_C_PORT_ENABLE << 16, USB_PORT_STAT_C_ENABLE << 16},
    {HUB_C_PORT_SUSPEND << 16, USB_PORT_STAT_C_SUSPEND << 16},
    {HUB_C_PORT_OVER_CURRENT << 16, USB_PORT_STAT_C_OVERCURRENT << 16},
    {HUB_C_PORT_RESET << 16, USB_PORT_STAT_C_RESET << 16}
};

EFI_USB_PORT_STATUS_MAP  SsHubPortStatusMap[] = {
    // Port status bits
    {SS_HUB_PORT_CONNECTION, USB_PORT_STAT_CONNECTION | USB_PORT_STAT_SUPER_SPEED},
    {SS_HUB_PORT_ENABLE, USB_PORT_STAT_ENABLE},
    {SS_HUB_PORT_OVER_CURRENT, USB_PORT_STAT_OVERCURRENT},
    {SS_HUB_PORT_RESET, USB_PORT_STAT_RESET},
    {SS_HUB_PORT_POWER, USB_PORT_STAT_POWER},
    // Port status change bits
    {SS_HUB_C_PORT_CONNECTION << 16, USB_PORT_STAT_C_CONNECTION << 16},
    {SS_HUB_C_PORT_ENABLE << 16, USB_PORT_STAT_C_ENABLE << 16},
    {SS_HUB_C_PORT_SUSPEND << 16, USB_PORT_STAT_C_SUSPEND << 16},
    {SS_HUB_C_PORT_OVER_CURRENT << 16, USB_PORT_STAT_C_OVERCURRENT << 16},
    {SS_HUB_C_PORT_RESET << 16, USB_PORT_STAT_C_RESET << 16}
};

/**
    This function uses a device's PEI_USB_IO_PPI interface to execute a 
    control transfer on the default control pipe to issue a Hub 
    Class-specific request to obtain the port status and port status
    change bits.

        
    @param PeiServices 
        --  PEI Sevices table pointer
    @param UsbIoPpi 
        --  PEI_USB_IO_PPI interface pointer for the device
        that is being accessed
    @param Port 
        --  This value is the hub port number for which the
        status is to be returned.
    @param PortStatus 
        --  This output value is the USB Specification 
        (Revision 2.0) Hub Port Status field (upper word)
        and Change Status field (lower word) values as 
        returned by the Get Port Status Hub Class device 
        standard request.

    @retval 
        EFI_STATUS (Return Value)
        = EFI_SUCCESS on successful completion
        or valid EFI error code

**/

EFI_STATUS PeiHubGetPortStatus (
    IN  EFI_PEI_SERVICES    **PeiServices,
    IN  PEI_USB_IO_PPI      *UsbIoPpi,
    IN  UINT8               Port,
    OUT UINT32              *PortStatus )
{
    EFI_USB_DEVICE_REQUEST  DevReq;
    PEI_USB_DEVICE          *PeiUsbDev;
    UINT32                  HubPortStatus = 0;
    UINT32                  Timeout;
    EFI_USB_PORT_STATUS_MAP *PortStatusMap;
    UINT8                   Index;
    UINT8                   Count;
    UINT32                  UsbStatus;
    EFI_STATUS              Status;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);
    if (gEdk2IoMmuPpi) {
        if (gHubPortStatusPtr == NULL) {
            Status = gEdk2IoMmuPpi->AllocateBuffer (
                                        gEdk2IoMmuPpi,
                                        EfiBootServicesData,
                                        1,
                                        (VOID**)&gHubPortStatusPtr,
                                        EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                        );
            if (EFI_ERROR(Status)) {
                return EFI_OUT_OF_RESOURCES;
            }
        }
        (*PeiServices)->SetMem(gHubPortStatusPtr, sizeof(UINT32), 0);
    } else {
        gHubPortStatusPtr = &HubPortStatus;
    }

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_GET_PORT_STATUS_REQ_TYPE;
    DevReq.Request = HUB_GET_PORT_STATUS;
    DevReq.Value = 0;
    DevReq.Index = Port;
    DevReq.Length = sizeof(UINT32);

    Timeout = 3000;

    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbDataIn,
                         Timeout,
                         gHubPortStatusPtr,
                         sizeof(UINT32),
                         &UsbStatus
                         );

    if ((PeiUsbDev->DeviceSpeed != USB_SUPER_SPEED_DEVICE) && 
        (PeiUsbDev->DeviceSpeed != USB_SUPER_SPEED_PLUS_DEVICE)) {
        PortStatusMap = HubPortStatusMap;
        Count = sizeof(HubPortStatusMap) / sizeof(EFI_USB_PORT_STATUS_MAP);
    } else {
        PortStatusMap = SsHubPortStatusMap;
        Count = sizeof(SsHubPortStatusMap) / sizeof(EFI_USB_PORT_STATUS_MAP);
    }

    for (*PortStatus = 0, Index = 0; Index < Count; Index++) {
        if ((*gHubPortStatusPtr) & PortStatusMap[Index].HubPortStatus) {
            *PortStatus |= PortStatusMap[Index].EfiPortStatus;
        }
    }

    return Status;
}


EFI_STATUS PeiHubSetPortFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    IN UINT8            Value )

/*++

   Routine Description:
    Set specified feature to a give hub port

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Port            -   Usb hub port number (starting from 1).
    Value           -   New feature value.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT
    EFI_INVALID_PARAMETER

   --*/

{
    EFI_USB_DEVICE_REQUEST      DevReq;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_SET_PORT_FEATURE_REQ_TYPE;
    DevReq.Request = HUB_SET_PORT_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = Port;
    DevReq.Length = 0;

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbNoData,
                         Timeout,
                         NULL,
                         0,
                         &UsbStatus
                         );

    return Status;
}


EFI_STATUS PeiHubClearPortFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Port,
    IN UINT8            Value )

/*++

   Routine Description:
    Clear a specified feature of a given hub port

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Port            -   Usb hub port number (starting from 1).
    Value           -   Feature value that will be cleared from
                        that hub port.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT
    EFI_INVALID_PARAMETER

   --*/
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_CLEAR_FEATURE_PORT_REQ_TYPE;
    DevReq.Request = HUB_CLEAR_FEATURE_PORT;
    DevReq.Value = Value;
    DevReq.Index = Port;
    DevReq.Length = 0;

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbNoData,
                         Timeout,
                         NULL,
                         0,
                         &UsbStatus
                         );

    return Status;
}


EFI_STATUS PeiHubGetHubStatus (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    OUT UINT32          *HubStatus )

/*++

   Routine Description:
    Get Hub Status

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    HubStatus       -   Current Hub status and change status.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_GET_HUB_STATUS_REQ_TYPE;
    DevReq.Request = HUB_GET_HUB_STATUS;
    DevReq.Value = 0;
    DevReq.Index = 0;
    DevReq.Length = sizeof(UINT32);

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbDataIn,
                         Timeout,
                         HubStatus,
                         sizeof(UINT32),
                         &UsbStatus
                         );

    return Status;
}


EFI_STATUS PeiHubSetHubFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Value )

/*++

   Routine Description:
    Set a specified feature to the hub

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Value           -   Feature value that will be set to the hub.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_SET_HUB_FEATURE_REQ_TYPE;
    DevReq.Request = HUB_SET_HUB_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbNoData,
                         Timeout,
                         NULL,
                         0,
                         &UsbStatus
                         );

    return Status;
}


EFI_STATUS PeiHubClearHubFeature (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    IN UINT8            Value )

/*++

   Routine Description:
    Set a specified feature to the hub

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    Value           -   Feature value that will be cleared from the hub.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_CLEAR_FEATURE_REQ_TYPE;
    DevReq.Request = HUB_CLEAR_FEATURE;
    DevReq.Value = Value;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbNoData,
                         Timeout,
                         NULL,
                         0,
                         &UsbStatus
                         );

    return Status;

}

EFI_STATUS PeiSetHubDepth (
    IN EFI_PEI_SERVICES        **PeiServices,
	IN PEI_USB_IO_PPI          *UsbIoPpi,
	IN UINT16                  HubDepth)
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    PEI_USB_DEVICE              *PeiUsbDev;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );
    if ((PeiUsbDev->DeviceSpeed != USB_SUPER_SPEED_DEVICE) && 
            (PeiUsbDev->DeviceSpeed != USB_SUPER_SPEED_PLUS_DEVICE)) {
        return EFI_SUCCESS;
    }

    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = HUB_SET_HUB_DEPTH_REQ_TYPE;
    DevReq.Request = HUB_SET_HUB_DEPTH;
    DevReq.Value = HubDepth;
    DevReq.Index = 0;
    DevReq.Length = 0;

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbNoData,
                         Timeout,
                         NULL,
                         0,
                         &UsbStatus
                         );
    return Status;
}

EFI_STATUS PeiGetHubDescriptor (
    IN EFI_PEI_SERVICES        **PeiServices,
    IN PEI_USB_IO_PPI          *UsbIoPpi,
    IN UINTN                   DescriptorSize,
    OUT EFI_USB_HUB_DESCRIPTOR *HubDescriptor )

/*++

   Routine Description:
    Get the hub descriptor

   Arguments:
    UsbIoPpi           -   EFI_USB_IO_PROTOCOL instance
    DescriptorSize  -   The length of Hub Descriptor buffer.
    HubDescriptor   -   Caller allocated buffer to store the hub descriptor
                        if successfully returned.

   Returns:
    EFI_SUCCESS
    EFI_DEVICE
    EFI_TIME_OUT

   --*/
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    PEI_USB_DEVICE              *PeiUsbDev;
    EFI_STATUS                  Status;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

	PeiUsbDev = PEI_USB_DEVICE_FROM_THIS( UsbIoPpi );
    //ZeroMem( &DevReq, sizeof(EFI_USB_DEVICE_REQUEST) );
    (*PeiServices)->SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = USB_RT_HUB | 0x80;
    DevReq.Request = HUB_GET_DESCRIPTOR;
    if ((PeiUsbDev->DeviceSpeed == USB_SUPER_SPEED_DEVICE) ||
            (PeiUsbDev->DeviceSpeed == USB_SUPER_SPEED_PLUS_DEVICE)) {
        DevReq.Value = USB_DT_SS_HUB << 8;
    } else {
        DevReq.Value = USB_DT_HUB << 8;
    }

    DevReq.Index = 0;
    DevReq.Length = (UINT16) DescriptorSize;

    Timeout = 3000;
    Status = UsbIoPpi->UsbControlTransfer(
                         PeiServices,
                         UsbIoPpi,
                         &DevReq,
                         EfiUsbDataIn,
                         Timeout,
                         HubDescriptor,
                         (UINT16) DescriptorSize,
                         &UsbStatus
                         );

    return Status;

}


EFI_STATUS PeiDoHubConfig (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_DEVICE   *PeiUsbDevice )

/*++

   Routine Description:
    Configure the hub

   Arguments:
    PeiUsbDevice         -   Indicating the hub controller device that
                              will be configured

   Returns:
    EFI_SUCCESS
    EFI_DEVICE_ERROR

   --*/
{
    EFI_USB_HUB_DESCRIPTOR  HubDescriptor;
    EFI_STATUS              Status;
    EFI_USB_HUB_STATUS      HubStatusPtr;
    EFI_USB_HUB_STATUS      *HubStatus;
    UINTN                   Index;
    UINT32                  PortStatus;
    PEI_USB_IO_PPI          *UsbIoPpi;
    EFI_USB_HUB_DESCRIPTOR  *HubDescriptorPtr = NULL;
    UINTN                   Size = 0;
    VOID                    *Mapping = NULL;
    UINT64                  HubMappedBaseAddr = 0;
    UINT64                  HubStatusMappedBaseAddr = 0;
    VOID                    *HubStatusMapping = NULL;

    (*PeiServices)->SetMem(&HubDescriptor, sizeof(HubDescriptor), 0);
    UsbIoPpi = &PeiUsbDevice->UsbIoPpi;
    Status = PeiSetHubDepth(
               PeiServices,
               UsbIoPpi,
               PeiUsbDevice->HubDepth
               );
    
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    if (gEdk2IoMmuPpi) {
            Status = gEdk2IoMmuPpi->AllocateBuffer (
                                        gEdk2IoMmuPpi,
                                        EfiBootServicesData,
                                        1,
                                        (VOID**)&HubDescriptorPtr,
                                        EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                        );
            if (EFI_ERROR(Status)) {
                return EFI_OUT_OF_RESOURCES;
            }
        (*PeiServices)->SetMem(HubDescriptorPtr, sizeof(EFI_USB_HUB_DESCRIPTOR), 0);
        Size   = sizeof(EFI_USB_HUB_DESCRIPTOR);
        Status = gEdk2IoMmuPpi->Map (
                     gEdk2IoMmuPpi,
                     EdkiiIoMmuOperationBusMasterCommonBuffer,
                     HubDescriptorPtr,
                     &Size,
                     (EFI_PHYSICAL_ADDRESS*)&HubMappedBaseAddr,
                     &Mapping
                     );
        HubDescriptorPtr = (EFI_USB_HUB_DESCRIPTOR*)(UINTN)HubMappedBaseAddr;
        DEBUG((DEBUG_INFO, "Iommu HubDescriptorPtr %x \n"));
    } else {
        HubDescriptorPtr = &HubDescriptor;
    }
    //
    // First get the whole descriptor, then
    // get the number of hub ports
    //
    Status = PeiGetHubDescriptor(
                 PeiServices,
                 UsbIoPpi,
                 sizeof(EFI_USB_HUB_DESCRIPTOR),
                 HubDescriptorPtr
                 );
    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }
    PeiUsbDevice->DownStreamPortNo = HubDescriptorPtr->NbrPorts;

    if (gEdk2IoMmuPpi) {
            Status = gEdk2IoMmuPpi->AllocateBuffer (
                                        gEdk2IoMmuPpi,
                                        EfiBootServicesData,
                                        1,
                                        (VOID**)&gHubStatus,
                                        EDKII_IOMMU_ATTRIBUTE_MEMORY_WRITE_COMBINE
                                        );
            if (EFI_ERROR(Status)) {
                return EFI_OUT_OF_RESOURCES;
            }
        (*PeiServices)->SetMem(gHubStatus, sizeof(UINT32), 0);
        Size   = sizeof(UINT32);
        Status = gEdk2IoMmuPpi->Map (
                     gEdk2IoMmuPpi,
                     EdkiiIoMmuOperationBusMasterCommonBuffer,
                     gHubStatus,
                     &Size,
                     (EFI_PHYSICAL_ADDRESS*)&HubStatusMappedBaseAddr,
                     &HubStatusMapping
                     );
        HubStatus = (EFI_USB_HUB_STATUS *)(UINTN)HubStatusMappedBaseAddr;
        DEBUG((DEBUG_INFO, "Iommu HubStatus %x \n"));
    } else {
        HubStatus = (EFI_USB_HUB_STATUS *)&HubStatusPtr;
    }
    
    Status = PeiHubGetHubStatus( 
               PeiServices,
               UsbIoPpi,
               (UINT32 *) HubStatus
               );

    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }
    //
    //  Get all hub ports status
    //
    for (Index = 0; Index < PeiUsbDevice->DownStreamPortNo; Index++) {
        Status = PeiHubGetPortStatus( PeiServices,
                     UsbIoPpi,
                     (UINT8)(Index + 1),
                     &PortStatus
                     );
        if ( EFI_ERROR( Status ) ) {
            continue;
        }
    }

    //
    //  Power all the hub ports
    //
    for (Index = 0; Index < PeiUsbDevice->DownStreamPortNo; Index++) {
        Status = PeiHubSetPortFeature( PeiServices,
                     UsbIoPpi,
                     (UINT8)(Index + 1),
                     EfiUsbPortPower
                     );
        if ( EFI_ERROR( Status ) ) {
            continue;
        }
    }
    //
    // Clear Hub Status Change
    //
    Status = PeiHubGetHubStatus( PeiServices,
        UsbIoPpi,
        (UINT32 *) HubStatus
             );
    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    } else {
        
        //
        // Hub power supply change happens
        //
        if (HubStatus->HubChange & HUB_CHANGE_LOCAL_POWER) {
            PeiHubClearHubFeature( 
              PeiServices,
              UsbIoPpi,
              C_HUB_LOCAL_POWER
              );
        }

        //
        // Hub change overcurrent happens
        //
        if (HubStatus->HubChange & HUB_CHANGE_OVERCURRENT) {
            
            PeiHubClearHubFeature( 
                PeiServices,
                UsbIoPpi,
                C_HUB_OVER_CURRENT
            );
        }
    }
    
    if (gUsbPeiStall!=NULL)
        gUsbPeiStall->Stall(
                        (CONST EFI_PEI_SERVICES**)PeiServices, 
                        gUsbPeiStall, 
                        (HubDescriptorPtr->PwrOn2PwrGood << 1) *1000
                        );
    
    if (gEdk2IoMmuPpi) {
        if(Mapping != NULL){
            gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, Mapping);
        }
        if(HubStatusMapping != NULL){
            gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, HubStatusMapping);
        }
        gEdk2IoMmuPpi->FreeBuffer (
                           gEdk2IoMmuPpi,
                           1,
                           (VOID*)HubDescriptorPtr
                           );
                           
        gEdk2IoMmuPpi->FreeBuffer (
                           gEdk2IoMmuPpi,
                           1,
                           (VOID*)gHubStatus
                           );
    }
    return EFI_SUCCESS;

}


//
// Send reset signal over the given root hub port
//
VOID PeiResetHubPort (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi,
    UINT8               PortNum )
{
    UINT8               Retry;
    EFI_USB_PORT_STATUS HubPortStatus;
    //
    // reset root port
    //
    PeiHubSetPortFeature(
        PeiServices,
        UsbIoPpi,
        PortNum,
        EfiUsbPortReset
    );

    Retry = 20;
    do {
        
        PeiHubGetPortStatus(
          PeiServices,
          UsbIoPpi,
          PortNum,
          (UINT32 *)&HubPortStatus
          );
        if (gUsbPeiStall!=NULL)
            gUsbPeiStall->Stall(
                            (CONST EFI_PEI_SERVICES**)PeiServices,
                            gUsbPeiStall,
                            PEI_USB_RESET_PORT_DELAY_MS * 100
                            );
        Retry -= 1;
    } while ( (HubPortStatus.PortChangeStatus &
               USB_PORT_STAT_C_RESET) == 0 && Retry > 0 );

    // The USB System Software guarantees a minimum of 10 ms for reset recovery.
    if (gUsbPeiStall!=NULL)
        gUsbPeiStall->Stall(
                        (CONST EFI_PEI_SERVICES**)PeiServices, 
                        gUsbPeiStall, 
                        PEI_USB_RESET_PORT_DELAY_MS * 1000
                        );
    
    //
    // Clear any change status
    //
    PeiHubClearPortFeature(
        PeiServices,
        UsbIoPpi,
        PortNum,
        EfiUsbPortResetChange
    );

    return;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
