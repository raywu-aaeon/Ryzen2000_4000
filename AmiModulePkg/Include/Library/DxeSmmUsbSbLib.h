//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file DxeSmmUsbSbLib.h
    Defines the DxeSmmUsbSblib library functions.
**/

#ifndef _DXE_SMM_USB_SB_LIB_H
#define _DXE_SMM_USB_SB_LIB_H

#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmGpiDispatch2.h>
#include <Protocol/UsbPolicy.h>
#include <Protocol/AmiUsbHid.h>

#define USB_HANDLE   0xFF555342       //'U''S''B'

EFI_STATUS EFIAPI USBSB_InstallXhciHwSmiHandler(VOID);
EFI_STATUS EFIAPI USBSB_InstallUsbIntTimerHandler(VOID);
EFI_STATUS EFIAPI USBSB_UninstallTimerHandlers(VOID);
EFI_STATUS EFIAPI USBSB_InstallSmiEventHandlers(VOID);
#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
