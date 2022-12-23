//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file BotPeim.c
    This file belongs to "Framework".
    This file is modified by AMI to include copyright message,
    appropriate header and integration code.
    This file contains generic routines needed for USB recovery
    Mass Storage BOT PEIM

**/

/*++
   This file contains a 'Sample Driver' and is licensed as such
   under the terms of your license agreement with Intel or your
   vendor.  This file may be modified by the user, subject to
   the additional terms of the license agreement
--*/

/**
BOT Transportation implementation.

Copyright (c) 2006, Intel Corporation. All rights reserved.<BR>
  
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
#include <Library/DebugLib.h>

STATIC
EFI_STATUS BotRecoveryReset (
    IN EFI_PEI_SERVICES **PeiServices,
    IN PEI_BOT_DEVICE   *PeiBotDev )
{
    EFI_USB_DEVICE_REQUEST DevReq;
    UINT32 Timeout;
    PEI_USB_IO_PPI         *UsbIoPpi;
    UINT8      EndpointAddr;
    EFI_STATUS Status;
    UINT32      UsbStatus;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    if (UsbIoPpi == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    (**PeiServices).SetMem((VOID*)&DevReq, sizeof(EFI_USB_DEVICE_REQUEST), 0);

    DevReq.RequestType = 0x21;
    DevReq.Request = 0xff;
    DevReq.Value = 0;
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

    //
    // clear bulk in endpoint stall feature
    //
    EndpointAddr = (PeiBotDev->BulkInEndpoint)->EndpointAddress;
    PeiUsbClearEndpointHalt( PeiServices, UsbIoPpi, EndpointAddr );

    //
    // clear bulk out endpoint stall feature
    //
    EndpointAddr = (PeiBotDev->BulkOutEndpoint)->EndpointAddress;
    PeiUsbClearEndpointHalt( PeiServices, UsbIoPpi, EndpointAddr );

    return Status;
}


STATIC
EFI_STATUS BotCommandPhase (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_BOT_DEVICE         *PeiBotDev,
    IN VOID                   *Command,
    IN UINT8                  CommandSize,
    IN UINT32                 DataTransferLength,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT16                 Timeout )
{
    CBW             Cbw;
    EFI_STATUS      Status;
    PEI_USB_IO_PPI  *UsbIoPpi;
    UINTN           DataSize;
    UINT32          UsbStatus;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    (**PeiServices).SetMem((VOID*)&Cbw, sizeof(CBW), 0);

    //
    // Fill the command block, detailed see BOT spec
    //
    Cbw.CbwSignature = CBWSIG;
    Cbw.CbwTag = 0x01;
    Cbw.CbwDataTransferLength = DataTransferLength;
    Cbw.CbwFlags = (Direction == EfiUsbDataIn)? 0x80 : 0;
    Cbw.CbwLUN = PeiBotDev->Lun;       
    Cbw.CbwCBLength = CommandSize;

    PeiCopyMem( Cbw.CbwCB, Command, CommandSize );

    DataSize = sizeof(CBW);

    Status = UsbIoPpi->UsbBulkTransfer(
        PeiServices,
        UsbIoPpi,
        (PeiBotDev->BulkOutEndpoint)->EndpointAddress,
        (UINT8 *) &Cbw,
        &DataSize,
        Timeout,
        &UsbStatus
             );
    if ( EFI_ERROR( Status ) ) {
        //
        // Command phase fail, we need to recovery reset this device
        //
        BotRecoveryReset( PeiServices, PeiBotDev );
        return EFI_DEVICE_ERROR;
    }

    return EFI_SUCCESS;
}


STATIC
EFI_STATUS BotDataPhase (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_BOT_DEVICE         *PeiBotDev,
    IN UINT32                 *DataSize,
    IN OUT VOID               *DataBuffer,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT16                 Timeout )
{
    EFI_STATUS      Status;
    PEI_USB_IO_PPI  *UsbIoPpi;
    UINT8           EndpointAddr;
    UINTN           Remain;
    UINTN           Increment;
    UINT32          MaxPacketLen;
    UINT8           *BufferPtr;
    UINTN           TransferredSize;
	UINTN           TransferSize;
    UINT32          UsbStatus;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    Remain = *DataSize;
    BufferPtr = (UINT8 *) DataBuffer;
    TransferredSize = 0;

    //
    // retrieve the the max packet length of the given endpoint
    //
    if (Direction == EfiUsbDataIn) {
        MaxPacketLen = (PeiBotDev->BulkInEndpoint)->MaxPacketSize;
        EndpointAddr = (PeiBotDev->BulkInEndpoint)->EndpointAddress;
    }
    else {
        MaxPacketLen = (PeiBotDev->BulkOutEndpoint)->MaxPacketSize;
        EndpointAddr = (PeiBotDev->BulkOutEndpoint)->EndpointAddress;
    }

    while (Remain > 0) {
        //
        // Using 15 packets to avoid Bitstuff error
        //
        if (Remain > 16 * MaxPacketLen) {
            TransferSize = 16 * MaxPacketLen;
        }
        else {
            TransferSize = Remain;
        }

		Increment = TransferSize;
	
        Status = UsbIoPpi->UsbBulkTransfer(
            PeiServices,
            UsbIoPpi,
            EndpointAddr,
            BufferPtr,
            &Increment,
            Timeout,
            &UsbStatus
                 );

        TransferredSize += Increment;

        if (EFI_ERROR(Status)) {
            if (UsbStatus & EFI_USB_ERR_STALL) {
                PeiUsbClearEndpointHalt( PeiServices, UsbIoPpi, EndpointAddr );
            }
            return Status;
        }
	
		if (Increment < TransferSize) {
			break;
		}
		
        BufferPtr += Increment;
        Remain -= Increment;
    }

    *DataSize = (UINT32) TransferredSize;

    return EFI_SUCCESS;
}

EFI_STATUS
BotStatusPhase (
    IN  EFI_PEI_SERVICES    **PeiServices,
    IN  PEI_BOT_DEVICE      *PeiBotDev,
    OUT UINT8               *TransferStatus,
    IN  UINT16              Timeout
)
{
    CSW             Csw;
    EFI_STATUS      Status;
    PEI_USB_IO_PPI  *UsbIoPpi;
    UINT8           EndpointAddr;
    UINTN           DataSize;
    UINT32          UsbStatus;

    UsbIoPpi = PeiBotDev->UsbIoPpi;

    (**PeiServices).SetMem((VOID*)&Csw, sizeof(CSW), 0);

    EndpointAddr = (PeiBotDev->BulkInEndpoint)->EndpointAddress;

    //  DataSize = sizeof(CSW);
    DataSize = 0x0D;

    //
    // Get the status field from bulk transfer
    //
    Status = UsbIoPpi->UsbBulkTransfer(
        PeiServices,
        UsbIoPpi,
        EndpointAddr,
        &Csw,
        &DataSize,
        Timeout,
        &UsbStatus
             );

    if (EFI_ERROR(Status)) {
        if (UsbStatus & EFI_USB_ERR_STALL) {
            // The host shall clear the Bulk-in pipe.
            PeiUsbClearEndpointHalt(PeiServices, UsbIoPpi, EndpointAddr);
        }

        // The host shall again attempt to receive the CSW.
        DataSize = 0x0D;
        UsbStatus = 0;
        
        Status = UsbIoPpi->UsbBulkTransfer(
            PeiServices,
            UsbIoPpi,
            EndpointAddr,
            &Csw,
            &DataSize,
            Timeout,
            &UsbStatus
                 );
        if (EFI_ERROR(Status)) {
            if (UsbStatus & EFI_USB_ERR_STALL) {
                BotRecoveryReset(PeiServices, PeiBotDev);
            }
            return Status;
        }
    }

    //
    // Check for valid CSW
    //
    if ((DataSize != 0x0D) || (Csw.CswSignature != CSWSIG) || (Csw.CswTag != 0x01)) {
        return EFI_DEVICE_ERROR;
    }   

    *TransferStatus = Csw.CswStatus;

    return EFI_SUCCESS;
}


EFI_STATUS
PeiAtapiCommand (
    IN EFI_PEI_SERVICES       **PeiServices,
    IN PEI_BOT_DEVICE         *PeiBotDev,
    IN VOID                   *Command,
    IN UINT8                  CommandSize,
    IN VOID                   *DataBuffer,
    IN UINT32                 BufferLength,
    IN EFI_USB_DATA_DIRECTION Direction,
    IN UINT16                 TimeOutInMilliSeconds
)

/*++

   Routine Description:
    Send ATAPI command using BOT protocol.

   Arguments:
    This                  - Protocol instance pointer.
    Command               - Command buffer
    CommandSize           - Size of Command Buffer
    DataBuffer            - Data buffer
    BufferLength          - Length of Data buffer
    Direction             - Data direction of this command
    TimeoutInMilliseconds - Timeout value in ms

   Returns:
    EFI_SUCCES          - Command succeeded.
    EFI_DEVICE_ERROR    - Command failed.

   --*/
{
    EFI_STATUS  Status;
    EFI_STATUS  BotDataStatus   =   EFI_SUCCESS;
    UINT8       TransferStatus;
    UINT32      BufferSize;
    UINT8       *Tmp;
    UINT32      Temp;

    Tmp = (UINT8 *)Command;
    Temp = Tmp[0];
    
    DEBUG((DEBUG_INFO, "Executing ScsiCmd(%x)\n", Temp));
    //
    // First send ATAPI command through Bot
    //
    Status = BotCommandPhase(
        PeiServices,
        PeiBotDev,
        Command,
        CommandSize,
        BufferLength,
        Direction,
        TimeOutInMilliSeconds
             );

    if ( EFI_ERROR( Status ) ) {
        return EFI_DEVICE_ERROR;
    }

    //
    // Send/Get Data if there is a Data Stage
    //
    switch (Direction) {
        case EfiUsbDataIn:
        case EfiUsbDataOut:
            BufferSize = BufferLength;

            BotDataStatus = BotDataPhase(
                PeiServices,
                PeiBotDev,
                &BufferSize,
                DataBuffer,
                Direction,
                TimeOutInMilliSeconds
                            );
            break;

        case EfiUsbNoData:
            break;
    }

    //
    // Status Phase
    //

    Status = BotStatusPhase(
        PeiServices,
        PeiBotDev,
        &TransferStatus,
        TimeOutInMilliSeconds
             );
    
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }

    if (TransferStatus) {
        if (TransferStatus > 0x01) {
            // The host shall perform a Reset Recovery if CSWStatus is 0x02.
            BotRecoveryReset(PeiServices, PeiBotDev);
        }
        return EFI_DEVICE_ERROR;
    }

    return BotDataStatus;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
