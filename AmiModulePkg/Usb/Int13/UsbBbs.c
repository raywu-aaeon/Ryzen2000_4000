//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file UsbBbs.c

**/

#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmiUsbController.h>

/**
    Create BBS table for each USB mass storage device.

**/

VOID
CollectUsbBbsDevices (
    VOID
)
{
    EFI_STATUS  Status;
    EFI_USB_PROTOCOL        *AmiUsb;

    Status = gBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, (VOID**)&AmiUsb);
    if (EFI_ERROR(Status)) {
        return;
    }

    AmiUsb->InstallUsbLegacyBootDevices();
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
