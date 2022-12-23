/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH DXE
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH DXE
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */

#ifndef _FCH_INIT_PROTOCOL_H_
#define _FCH_INIT_PROTOCOL_H_


extern EFI_GUID gFchInitProtocolGuid;

typedef struct _FCH_INIT_PROTOCOL FCH_INIT_PROTOCOL;
/// FCH USB Over Current Data Block
typedef struct {
  UINT32       ChipType;                           ///< Bitfield: Applied chip types
  UINT8        Usb1OcPinMap[5];       ///< USB1 over current pin mapping
  UINT8        Usb2OcPinMap[5];       ///< USB2 over current pin mapping
  UINT8        Usb3OcPinMap[4];       ///< USB3 over current pin mapping
  UINT8        Usb4OcPinMap[2];       ///< USB4 over current pin mapping
  UINT8        Xhci0OcPinMap[2];      ///< XHCI0 over current pin mapping
  UINT8        Xhci1OcPinMap[2];      ///< XHCI1 over current pin mapping
} USB_OC;


//
// Protocol prototypes
//
typedef
VOID
(EFIAPI *FP_FCH_USB_OC) (
  USB_OC      *UsbOc
  );

//
// Rev2 for USB OC mapping after ZP
//
typedef EFI_STATUS (EFIAPI *FP_FCH_USB_OC2) (
  IN       CONST FCH_INIT_PROTOCOL   *This,              ///< FCH INIT Protocol
  IN       UINT8                     Socket,             ///< CPU/Socket number in system
  IN       UINT8                     Port,               ///< Bitmap (Bit0 - Port0, Bit1 - Port1, etc.) to disable USB3 ports
  IN       UINT8                     OCPin               ///< Bitmap (Bit0 - Port0, Bit1 - Port1, etc.) to disable USB2 ports
);

//
// USB port disable function
//
typedef EFI_STATUS (EFIAPI *FP_FCH_USB_PORT_DISABLE2) (
  IN       CONST FCH_INIT_PROTOCOL   *This,              ///< FCH INIT Protocol
  IN       UINT8                     Socket,             ///< CPU/Socket number in system
  IN       UINT32                    USB3DisableMap,     ///< Bitmap (Bit0 - Port0, Bit1 - Port1, etc.) to disable USB3 ports
  IN       UINT32                    USB2DisableMap      ///< Bitmap (Bit0 - Port0, Bit1 - Port1, etc.) to disable USB2 ports
);


/// FCH INIT Protocol
typedef struct _FCH_INIT_PROTOCOL {
  UINTN                     Revision;                 ///< Protocol Revision
  UINTN                     FchRev;                   ///< FCH Revision
  VOID                      *FchPolicy;               ///< Fch Config Data Block
  VOID                      *FchPtPolicy;             ///< PT Data Block
  FP_FCH_USB_OC             FpUsbOverCurrent;         ///< Service: USB Over Current
  FP_FCH_USB_OC2            FpUsbOverCurrent2;        ///< Service: USB Over Current2
  FP_FCH_USB_PORT_DISABLE2  FpUsbPortDisable2;        ///< Service: USB Port Disable2
} FCH_INIT_PROTOCOL;

// current PPI revision
#define FCH_INIT_REV  0x01

#endif // _FCH_INIT_PROTOCOL_H_

