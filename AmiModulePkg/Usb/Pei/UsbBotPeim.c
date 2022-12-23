//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file UsbBotPeim.c
    This file belongs to "Framework".
    This file is modified by AMI to include copyright message,
    appropriate header and integration code.
    This file contains generic routines needed for USB recovery
    PEIM

**/


/*++
   This file contains a 'Sample Driver' and is licensed as such
   under the terms of your license agreement with Intel or your
   vendor.  This file may be modified by the user, subject to
   the additional terms of the license agreement
   --*/

/**

Copyright (c) 2006 - 2015, Intel Corporation. All rights reserved.<BR>
  
This program and the accompanying materials
are licensed and made available under the terms and conditions
of the BSD License which accompanies this distribution.  The
full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include "UsbBotPeim.h"
#include "BotPeim.h"
#define PAGESIZE  4096
#include <Library/DebugLib.h>
#include <Ppi/Stall.h>
extern EFI_PEI_STALL_PPI *gUsbPeiStall;

//
// Global function
//
EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH |
    EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gAmiPeiUsbIoPpiGuid,
    NotifyOnUsbIoPpi
};

EFI_PEI_RECOVERY_BLOCK_IO_PPI mRecoveryBlkIoPpi = {
    BotGetNumberOfBlockDevices,
    BotGetMediaInfo,
    BotReadBlocks
};


EFI_PEI_PPI_DESCRIPTOR mPpiList = {
    EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiVirtualBlockIoPpiGuid,
    NULL
};

EFI_STATUS
PeiBotDetectMedia (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev );

EFI_STATUS
BotCheckDeviceReady (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev);

EFI_STATUS PeimInitializeUsbBot (
    IN EFI_PEI_SERVICES    **PeiServices )
{
    EFI_STATUS     Status;
    UINTN          UsbIoPpiInstance;
    EFI_PEI_PPI_DESCRIPTOR *TempPpiDescriptor;
    PEI_USB_IO_PPI *UsbIoPpi;

    //
    // locate all usb io PPIs
    //
    for (UsbIoPpiInstance = 0;
         UsbIoPpiInstance < PEI_FAT_MAX_USB_IO_PPI;
         UsbIoPpiInstance++) {

        Status = PeiServicesLocatePpi (&gAmiPeiUsbIoPpiGuid, UsbIoPpiInstance, &TempPpiDescriptor, (VOID **) &UsbIoPpi);
        if ( EFI_ERROR( Status ) ) {
            break;
        }
        InitUsbBot( PeiServices, UsbIoPpi );

    }

    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
NotifyOnUsbIoPpi(
    IN EFI_PEI_SERVICES          **PeiServices,
    IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN VOID                      *InvokePpi
)
{
    PEI_USB_IO_PPI *UsbIoPpi;

    UsbIoPpi = (PEI_USB_IO_PPI *)InvokePpi;

    InitUsbBot(PeiServices, UsbIoPpi);

    return EFI_SUCCESS;
}

EFI_STATUS GetMaxLun (
    IN  EFI_PEI_SERVICES    **PeiServices,
    IN  PEI_USB_IO_PPI      *UsbIoPpi,
    IN  UINT8               Port,
    OUT UINT8               *MaxLun )
{
    EFI_USB_DEVICE_REQUEST      DevReq;
    EFI_STATUS                  EfiStatus;
    UINT32                      Timeout;
    UINT32                      UsbStatus;

    (**PeiServices).SetMem(&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    //
    // Fill Device request packet
    //
    DevReq.RequestType = 0xA1;
    DevReq.Request = 0x0FE;
    DevReq.Value = 0;
    DevReq.Index = Port;
    DevReq.Length = sizeof(UINT8);

    Timeout = 3000;

    EfiStatus = UsbIoPpi->UsbControlTransfer(
                            PeiServices,
                            UsbIoPpi,
                            &DevReq,
                            EfiUsbDataIn,
                            Timeout,
                            MaxLun,
                            sizeof(UINT8),
                            &UsbStatus
                            );

    return EfiStatus;
}


EFI_STATUS InitUsbBot (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_USB_IO_PPI   *UsbIoPpi )
{
    PEI_BOT_DEVICE *PeiBotDevice;
    EFI_STATUS     Status;
    EFI_USB_INTERFACE_DESCRIPTOR *InterfaceDesc;
    UINT8                        *AllocateAddress;
    EFI_USB_ENDPOINT_DESCRIPTOR  *EndpointDesc;
    UINT8 Index;
    UINT8 MaxLun = 0;                   
    UINT8 CurrentLun;                   
    //
    // Check its interface
    //
    Status = UsbIoPpi->UsbGetInterfaceDescriptor( PeiServices,
        UsbIoPpi, &InterfaceDesc );
    if ( EFI_ERROR( Status ) ) {
        return Status;
    }

    //
    // Check if it is the BOT device we support
    //

    if ( (InterfaceDesc->InterfaceClass != BASE_CLASS_MASS_STORAGE)
        || (InterfaceDesc->InterfaceProtocol != PROTOCOL_BOT) ) {

        return EFI_NOT_FOUND;
    }

    Status = GetMaxLun(PeiServices,UsbIoPpi,InterfaceDesc->InterfaceNumber,&MaxLun);
    
    for(CurrentLun = 0; CurrentLun <= MaxLun; CurrentLun++) {

        Status = PeiServicesAllocatePool(
                sizeof(PEI_BOT_DEVICE), 
                (VOID**)&AllocateAddress
                     ); 
        if (EFI_ERROR( Status)) {
            return Status;
        }

        PeiBotDevice = (PEI_BOT_DEVICE *)AllocateAddress;
        (**PeiServices).SetMem(PeiBotDevice, sizeof(PEI_BOT_DEVICE), 0);

        PeiBotDevice->Signature = PEI_BOT_DEVICE_SIGNATURE;
        PeiBotDevice->UsbIoPpi = UsbIoPpi;
        PeiBotDevice->BotInterface = InterfaceDesc;
        PeiBotDevice->FdEmulOffset = 0; //bala
        //
        // Default value
        //
        PeiBotDevice->Media.DeviceType = UsbMassStorage;
        PeiBotDevice->Media.BlockSize = 0x200;
        PeiBotDevice->Lun = CurrentLun;
    
        //
        // Check its Bulk-in/Bulk-out endpoint
        //
        for (Index = 0; Index < 2; Index++) {
            Status = UsbIoPpi->UsbGetEndpointDescriptor( 
                                 PeiServices,
                                 UsbIoPpi, 
                                 Index, 
                                 &EndpointDesc 
                                 );
            if ( EFI_ERROR( Status ) ) {
                return Status;
            }

            if (EndpointDesc->Attributes != 2) {
                continue;
            }

            if ( (EndpointDesc->EndpointAddress & 0x80) != 0 ) {
                PeiBotDevice->BulkInEndpoint = EndpointDesc;
            }
            else {
                PeiBotDevice->BulkOutEndpoint = EndpointDesc;
            }

        }

        PeiBotDevice->BlkIoPpi = mRecoveryBlkIoPpi;
        PeiBotDevice->BlkIoPpiList = mPpiList;
        PeiBotDevice->BlkIoPpiList.Ppi = &PeiBotDevice->BlkIoPpi;

        Status = PeiUsbInquiry( PeiServices, PeiBotDevice );
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_ERROR, "Failed to get inquiry data\n"));
            return Status;
        }

        Status = PeiServicesInstallPpi (&PeiBotDevice->BlkIoPpiList); 
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BotGetNumberOfBlockDevices(
    IN EFI_PEI_SERVICES              **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                        *NumberBlockDevices
)
{
    //
    // For Usb devices, this value should be always 1
    //

    *NumberBlockDevices = 1;
    return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BotGetMediaInfo(
    IN EFI_PEI_SERVICES                     **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI        *This,
    IN UINTN                                DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA              *MediaInfo
)
{
    PEI_BOT_DEVICE      *PeiBotDev;
    EFI_STATUS          Status;

    PeiBotDev = PEI_BOT_DEVICE_FROM_THIS(This);

    Status = PeiBotDetectMedia(PeiServices, PeiBotDev);

    if (EFI_ERROR(Status)) {
        return Status;
    }

    *MediaInfo = PeiBotDev->Media;

    return EFI_SUCCESS;
}

EFI_STATUS
PeiBotDetectMedia (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev
)
{

    EFI_STATUS              Status = EFI_SUCCESS;
    UINT8                   *AllocateAddress;
    REQUEST_SENSE_DATA      *SensePtr = NULL;
    UINT8                   SenseKey;
    UINT8                   Asc;

    UINT8                   RetryCount;
    UINT8                   RetryReq = 0;


    //PeiUsbReadCapacity fills PeiBotDev structure for
    //BlockSize, LastBlock, Media Present
    for (RetryCount = 0; RetryCount < 25; RetryCount++) {
        Status = PeiUsbReadCapacity(PeiServices, PeiBotDev);

        if (!EFI_ERROR(Status)) {
            break;
        }

        //If ReadCapcity fails, then find out type of error
        if (RetryCount == 0) {
            if (PeiBotDev->SensePtr == NULL) {
                //During the first retry allocate the memory
                Status = PeiServicesAllocatePool(
                           sizeof(REQUEST_SENSE_DATA), 
                           (VOID**)&AllocateAddress
                           ); 
                if (EFI_ERROR(Status)) {
                    return Status;
                }
                PeiBotDev->SensePtr = (REQUEST_SENSE_DATA *)AllocateAddress;
            }
            SensePtr = PeiBotDev->SensePtr;
            (**PeiServices).SetMem((VOID*)SensePtr, sizeof(REQUEST_SENSE_DATA), 0);

            if (gUsbPeiStall==NULL) {
                DEBUG((DEBUG_ERROR, "Failed to Locate Pei Stall Ppi\n"));
            }
        }

        Status = PeiUsbRequestSense(PeiServices, PeiBotDev, (UINT8 *)SensePtr);
        if (EFI_ERROR(Status)) {
            //If RequestSense also fails, then there is an serious error
            //Return to the caller with appropriate error code
            //              PeiBotDev->Media.MediaPresent = FALSE;
            //              PeiBotDev->Media.BlockSize = 0;
            //              Status = EFI_DEVICE_ERROR;
            //              return EFI_DEVICE_ERROR;
        }
        //Parse the sense buffer for the error

        SenseKey = SensePtr->sense_key;
        Asc = SensePtr->addnl_sense_code;

        
        if (SenseKey == SK_NOT_READY) {
            //Logical Unit Problem
            switch (Asc) {
                case    ASC_NO_MEDIA:   // //Medium Not Present.
                    if (RetryCount >= 3) {
                        Status = BotCheckDeviceReady(PeiServices, PeiBotDev);
                        if (Status == EFI_NO_MEDIA) {
                            PeiBotDev->Media.MediaPresent = FALSE;
                            return Status;
                        }  
                    }
                    RetryReq = 1;   //Do retry
                    break;
                case    ASC_NOT_READY:           //Becoming Ready/Init Required/ Busy/ Format in Progress.
                case    ASC_MEDIA_UPSIDE_DOWN:   //No reference position found (medium may be upside down)
                case    ASC_COMM_ERR:            //Communication failure
                    RetryReq = 1;   //Do retry
                    break;
                default:
                    break;
            }
        } else if (SenseKey == SK_UNIT_ATTENTION && Asc == ASC_MEDIA_CHANGE) {
            RetryReq = 1;   //Do retry
        }

        PeiBotDev->Media.MediaPresent = FALSE;
        PeiBotDev->Media.BlockSize = 0;
        Status = EFI_DEVICE_ERROR;
        if (!RetryReq) {
            return Status;
        }
        //Wait for 100 msec
        if (gUsbPeiStall!=NULL)
            gUsbPeiStall->Stall( 
                            (CONST EFI_PEI_SERVICES**)PeiServices, 
                            gUsbPeiStall, 
                            100 * 1000 
                            ); // 100msec delay
    }
    return Status;
}

EFI_STATUS
EFIAPI
BotReadBlocks(
    IN EFI_PEI_SERVICES                     **PeiServices,
    IN EFI_PEI_RECOVERY_BLOCK_IO_PPI        *This,
    IN UINTN                                DeviceIndex,
    IN EFI_PEI_LBA                          StartLBA,
    IN UINTN                                BufferSize,
    OUT VOID                                *Buffer
)
{
    PEI_BOT_DEVICE          *PeiBotDev;
    EFI_STATUS              Status;
    UINTN                   NumberOfBlocks;
    UINT8                   *AllocateAddress;
    REQUEST_SENSE_DATA      *SensePtr = NULL;
    UINT8                   SenseKey;
    UINT8                   Asc;

    UINT8                   RetryCount;


    PeiBotDev = PEI_BOT_DEVICE_FROM_THIS(This);

    //StartLBA += PeiBotDev->FdEmulOffset;

    //
    // Check parameters
    //
    if (Buffer == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    if (BufferSize == 0) {
        return EFI_SUCCESS;
    }

    //if (BufferSize % BlockSize != 0) {
        //Status = EFI_BAD_BUFFER_SIZE;
    //}

    if (!PeiBotDev->Media.MediaPresent) {
        return EFI_NO_MEDIA;
    }

    if (StartLBA > PeiBotDev->Media.LastBlock) {
        return EFI_INVALID_PARAMETER;
    }

    NumberOfBlocks = BufferSize / (PeiBotDev->Media.BlockSize);

    for (RetryCount = 0; RetryCount < 3; RetryCount++) {
        
        Status = PeiUsbRead10(
            PeiServices,
            PeiBotDev,
            Buffer,
            StartLBA,
            NumberOfBlocks
                 );

        if (!EFI_ERROR(Status)) {
            break;
        }

        if (RetryCount == 0) {
            if (PeiBotDev->SensePtr == NULL) {

                Status = PeiServicesAllocatePool(
                        sizeof(REQUEST_SENSE_DATA), 
                        (VOID**)&AllocateAddress
                             );
                if (EFI_ERROR(Status)) {
                    return Status;
                }
                PeiBotDev->SensePtr = (REQUEST_SENSE_DATA *)AllocateAddress;
            }
            SensePtr = PeiBotDev->SensePtr;
            (**PeiServices).SetMem((VOID*)SensePtr, sizeof(REQUEST_SENSE_DATA), 0);

            if (gUsbPeiStall==NULL) {
                DEBUG((DEBUG_ERROR, "Failed to Locate Pei Stall Ppi\n"));
            }
        }

        Status = PeiUsbRequestSense(PeiServices, PeiBotDev, (UINT8 *)SensePtr);
        if (EFI_ERROR(Status)) {
            //If RequestSense also fails, then there is an serious error
            //Return to the caller with appropriate error code
            return EFI_DEVICE_ERROR;
        }
        //Parse the sense buffer for the error
        
        SenseKey = SensePtr->sense_key;
        Asc = SensePtr->addnl_sense_code;


        if ((SenseKey == 0x02) && (Asc == 0x3A)) {
            Status = BotCheckDeviceReady(PeiServices, PeiBotDev);
            if (EFI_ERROR(Status)) {
                if (Status == EFI_NO_MEDIA) {
                    PeiBotDev->Media.MediaPresent = FALSE;
                }
                    return Status;
            }
        }

        if (gUsbPeiStall!=NULL)
            gUsbPeiStall->Stall( 
                            (CONST EFI_PEI_SERVICES**)PeiServices, 
                            gUsbPeiStall, 
                            9000 
                            );
    }
    
    if (RetryCount == 3) {
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;

}

EFI_STATUS
BotCheckDeviceReady (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev
)
{
    UINT8                   RetryCount;
    UINT8                   SenseKey;
    UINT8                   Asc;

    EFI_STATUS              Status = EFI_SUCCESS;
    REQUEST_SENSE_DATA      *SensePtr;
    UINT8                   *AllocateAddress;

    if (PeiBotDev->SensePtr == NULL) {

        Status = PeiServicesAllocatePool(
                sizeof(REQUEST_SENSE_DATA), 
                (VOID**)&AllocateAddress
                     );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        PeiBotDev->SensePtr = (REQUEST_SENSE_DATA *)AllocateAddress;
    }
    SensePtr = PeiBotDev->SensePtr;
    (**PeiServices).SetMem((VOID*)SensePtr, sizeof(REQUEST_SENSE_DATA), 0);

    for (RetryCount = 0; RetryCount < 3; RetryCount++) {
        
        PeiUsbTestUnitReady(PeiServices, PeiBotDev);

        Status = PeiUsbRequestSense(PeiServices, PeiBotDev, (UINT8 *)SensePtr);
        if (EFI_ERROR(Status)) {
            //If RequestSense also fails, then there is an serious error
            //Return to the caller with appropriate error code
            return EFI_DEVICE_ERROR;
        }

        Status = EFI_DEVICE_ERROR;
        
        SenseKey = SensePtr->sense_key;
        Asc = SensePtr->addnl_sense_code;


        if (SenseKey == 0) {
            Status = EFI_SUCCESS;
            break;
        }
        if ((SenseKey == 0x28) && (Asc == 0x06)){
            Status = EFI_MEDIA_CHANGED;
            if (gUsbPeiStall!=NULL)
                gUsbPeiStall->Stall( 
                                (CONST EFI_PEI_SERVICES**)PeiServices, 
                                gUsbPeiStall, 
                                100 * 1000 
                                );
            continue;
        }
        if ((SenseKey == 0x02) && (Asc == 0x3A)){
            Status = EFI_NO_MEDIA;
            if (gUsbPeiStall!=NULL)
                gUsbPeiStall->Stall( 
                                (CONST EFI_PEI_SERVICES**)PeiServices, 
                                gUsbPeiStall, 
                                20 * 1000 
                                );
            continue;
        }

    }
    return Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
