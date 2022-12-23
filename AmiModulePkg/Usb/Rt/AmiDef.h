//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiDef.h
    AMI USB driver definitions, framework specific

**/
#ifndef     __AMI_DEF_H
#define     __AMI_DEF_H

#include <Protocol/AmiUsbController.h>
#include <Token.h>
#include <IndustryStandard/Pci.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DxeSmmUsbSbLib.h>
#define USB_DRIVER_VERSION  USB_DRIVER_MAJOR_VER
#define _FAR_

extern USB_GLOBAL_DATA     *gUsbData;
//
//Define the Generic USB cable support for USB debugger
//
#ifndef GENERIC_USB_CABLE_SUPPORT
#define GENERIC_USB_CABLE_SUPPORT 0
#endif
#if GENERIC_USB_CABLE_SUPPORT
#undef USB_DEBUG
#define USB_DEBUG
#endif

// 
// Define USB Debug
//
#ifndef USB_DEBUG
#define USB_DEBUG(UsbErrorLevel, ...) \
    if ((gUsbData == NULL) || ((gUsbData->UsbFeature2 & USB_DEBUG_SWITCH) &&((UsbErrorLevel) & (gUsbData->UsbDbgMaskMap)))){\
        DEBUG(((UINTN)(-1), __VA_ARGS__));\
    }
#endif
        
//Define USB_DEBUG_MESSAGES_BITMAP
#define DEBUG_HC_POLL       BIT0
#define DEBUG_HC            BIT1
#define DEBUG_BUS           BIT2    //same as org DEBUG_LEVEL_USBBUS
#define DEBUG_DEV_INIT      BIT3    //same as org Lv3
#define DEBUG_HID           BIT4
#define DEBUG_STORAGE       BIT5
#define DEBUG_HUB           BIT6
#define DEBUG_REPORT_DESC   BIT8
#define DEBUG_KBC           BIT9
#define DEBUG_MEM           BIT10
#define DEBUG_MISC          BIT11

// 
// Common defination
//
#define MICROSECOND                 10
#define MILLISECOND                 (1000 * MICROSECOND)
#define ONESECOND                   (1000 * MILLISECOND)
#define MILLISECOND_FIXED_DELAY     1000
#define COUNTOF(x) (sizeof(x)/sizeof((x)[0]))
// 
// Define USB EBDA offset
//
#define USB_DATA_EBDA_OFFSET         0x104
#define USB_PROTOCOL_EBDA_OFFSET     0x32

//
// Define macros to build data structure signatures from characters.
//
#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

#endif      // __AMI_DEF_H

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
