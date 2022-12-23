/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/PlatformHookLib.h>
#include <Library/DebugLib.h>

#define SIO_UNLOCK_PORT       0x2E

#define SIO_INDEX_PORT        0x2E
#define SIO_DATA_PORT         0x2F

#define R_UART_LSR            5

/**
  Performs platform specific initialization required for the CPU to access
  the hardware associated with a SerialPortLib instance.  This function does
  not intiailzie the serial port hardware itself.  Instead, it initializes 
  hardware devices that are required for the CPU to access the serial port 
  hardware.  This function may be called more than once.

  @retval RETURN_SUCCESS       The platform specific initialization succeeded.
  @retval RETURN_DEVICE_ERROR  The platform specific initialization could not be completed.
 
**/
RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (
  VOID
  )
{
  // Assume R_UART_LSR will never return 0xFF when serial port is enabled.  Use
  // that to determine if we already enabled the serial port.
  
  if (IoRead8 ((UINTN)(PcdGet64 (PcdSerialRegisterBase)) + R_UART_LSR) == 0xFF) {

    //
    // Enable LPC DMA cycle
    //
    PciOr32 (PCI_LIB_ADDRESS (0, 20, 3, 0x40), BIT2);
    //
    // Enable I/O Port 0x2E/0x2F & 0x4E/0x4F decoding to LPC
    //
    PciOr32 (PCI_LIB_ADDRESS (0, 20, 3, 0x48), BIT0+BIT1);
    //
    // Enable I/O Port 0x3F8~0x3FF & 0x2F8~0x2FF & 0x2E8~0x2EF & 0x3E8~0x3EF decoding to LPC
    //
    PciOr32 (PCI_LIB_ADDRESS (0, 20, 3, 0x44), BIT6+BIT7+BIT11+BIT13);

    //
    // enter MB PNP Mode so we can program
    //
    IoWrite8 (SIO_UNLOCK_PORT, 0x87);
    IoWrite8 (SIO_UNLOCK_PORT, 0x01);
    IoWrite8 (SIO_UNLOCK_PORT, 0x55);
    IoWrite8 (SIO_UNLOCK_PORT, 0x55);

    // Select Serial Port 1 LDN 1
    IoWrite8 (SIO_INDEX_PORT, 0x07);
    IoWrite8 (SIO_DATA_PORT, 0x01);

    // Set Serial Port 1 base address
    IoWrite8 (SIO_INDEX_PORT, 0x60);
    IoWrite8 (SIO_DATA_PORT, (UINT8)(((UINTN)PcdGet64 (PcdSerialRegisterBase) >> 8) & 0xFF));
    IoWrite8 (SIO_INDEX_PORT, 0x61);
    IoWrite8 (SIO_DATA_PORT, (UINT8)(((UINTN)PcdGet64 (PcdSerialRegisterBase)) & 0xFF));

    // Activate Serial Port 1
    IoWrite8 (SIO_INDEX_PORT, 0x30);
    IoWrite8 (SIO_DATA_PORT, 0x01);

    // exit MB PNP mode
//    IoWrite8 (SIO_INDEX_PORT, 0x02);
//    IoOr8 (SIO_DATA_PORT, 1);

  }
  return EFI_SUCCESS;
}

