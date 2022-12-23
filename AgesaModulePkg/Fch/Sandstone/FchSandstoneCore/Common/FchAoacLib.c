/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH Aoac operation lib
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 312516 $   @e \$Date: 2015-02-06 17:37:45 -0800 (Fri, 06 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
#include "FchPlatform.h"
#define FILECODE PROC_FCH_COMMON_FCHAOACLIB_FILECODE


/**
 * FchAoacPowerOnDev - Power On/Off Fch Device
 *
 * @param[in] Device     - Device to be turn on or off
 * @param[in] On         - 1 to turn on, 0 to turn off
 *
 */
VOID
FchAoacPowerOnDev (
  IN  UINT8      Device,
  IN  UINT8      On
  )
{
  if (On == 1) {
    if ((ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (Device << 1)) & 3) != 0) {
      ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (Device << 1)) &= ~(UINT8) (BIT0 + BIT1);
      ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (Device << 1)) |= BIT3;
      do {
      } while ((ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x41 + (Device << 1)) & 7) != 7);
    }
  } else {
    if ((ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (Device << 1)) & 3) != 3) {
      ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (Device << 1)) &= ~(UINT8) (BIT3);
      do {
      } while ((ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x41 + (Device << 1)) & 7) != 0);
      if (Device != FCH_AOAC_ESPI) {  //PLAT-26858 
        ACPIMMIO8 (ACPI_MMIO_BASE + AOAC_BASE + 0x40 + (Device << 1)) |= BIT0 + BIT1;
      }
    }
  }
}


