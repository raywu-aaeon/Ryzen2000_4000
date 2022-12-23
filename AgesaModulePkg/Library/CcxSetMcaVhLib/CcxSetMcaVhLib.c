/* $NoKeywords:$ */
/**
 * @file
 *
 * CCX Set MCA Library - VH
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision$   @e \$Date$
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
/*++
Module Name:

  CcxSetMcaLib.c
  Set MCA registers

Abstract:
--*/

#include <AGESA.h>
#include <Library/BaseLib.h>
#include <Library/CcxRolesLib.h>
#include <CcxRegistersVh.h>
#include <Filecode.h>

#define FILECODE LIBRARY_CCXSETMCAVHLIB_CCXSETMCAVHLIB_FILECODE

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxSetMca
 *
 *  Description:
 *    This routine sets all MCA registers
 *
 */
VOID
CcxSetMca (
  )
{
  UINT8           McaIndex;
  UINT8           McaCount;
  MCA_CONFIG_MSR  McaCfg;

  // MSR_0000_0179[7:0][Count]
  McaCount = (AsmReadMsr64 (0x00000179) & 0xFF);
  for (McaIndex = 0; McaIndex < McaCount; McaIndex++) {
    McaCfg.Value = AsmReadMsr64 (MSR_MCA_CFG_BANK0 + 0x10 * McaIndex);

    // MCi_CONFIG[32][McaXEnable] = 1 if MGC_CAP[Count] <= 32, else 0
    McaCfg.Field.McaXEnable = (McaCount <= 32) ? 1 : 0;

    // MCi_CONFIG[33][TransparentErrorLoggingEnable] = 0 if supported
    if (McaCfg.Field.TransparentErrorLoggingSupported == 1) {
      McaCfg.Field.TransparentErrorLoggingEnable = 0;
    }

    // MCi_CONFIG[34][LogDeferredInMcaStat] = 1 if supported
    if (McaCfg.Field.DeferredErrorLoggingSupported == 1) {
      McaCfg.Field.LogDeferredInMcaStat = 1;
    }
    AsmWriteMsr64 ((MSR_MCA_CFG_BANK0 + 0x10 * McaIndex), McaCfg.Value);
  }

  // MCA_CTL_MASK_L3
  // Should be run by core 0 of every DIE
  if (CcxIsDiePrimary (NULL)) {
    for (McaIndex = 0; McaIndex < 8; McaIndex++) {
      AsmMsrOr64 ((0xC0010407 + McaIndex), BIT7);
      AsmMsrOr64 (0xC0010419, (BIT9 | BIT8 | BIT7 | BIT6));
    }
  }
}


