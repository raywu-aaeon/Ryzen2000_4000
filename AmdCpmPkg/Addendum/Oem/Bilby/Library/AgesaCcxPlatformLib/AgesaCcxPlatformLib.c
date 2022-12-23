/*****************************************************************************
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
#include <Library/IoLib.h>

/*--------------------------------------------------------------------------------------*/
/**
 *  Hook to store the vector that all APs should jump to out of reset to a non-volatile,
 *  shared location.
 *
 *  @param[in]     ApInitAddress     Address of the code that AP should jump to
 *  @param[in,out] ContentToRestore  The current value in the non-volatile storage
 *
 **/
/*--------------------------------------------------------------------------------------*/
VOID
SaveApInitVector (
  IN       UINT32  ApInitAddress,
  IN OUT   UINT32  *ContentToRestore
  )
{
  UINT32                  Value32;
  UINTN                   Index;

  *ContentToRestore = 0;
  //
  // !!! This is one of the suggested solutions where BSP can launch AP without
  // going through intitializing of Pei Core Services. This function saves the
  // ApInit pointer. In this process, the current content of CMOS gets saved
  // and returned to caller which will be restored once APInit is done by
  // calling RestoreContentVector
  //
  for (Index = 0xA0; Index <= 0xA3; Index++) {
    IoWrite8 (0x72, (UINT8)Index);
    Value32 = (UINT32)(IoRead8 (0x73));
    *ContentToRestore |= (Value32 << ((Index - 0xA0)*8));
    Value32 = (UINT32) (ApInitAddress & 0xff);
    IoWrite8 (0x73, (UINT8)Value32);
    ApInitAddress >>= 8;
  }
}

/*--------------------------------------------------------------------------------------*/
/**
 *  Hook to restore the initial content of the non-volatile storage location.
 *
 *  @param[in]     ContentToRestore  The value to restore
 *
 **/
/*--------------------------------------------------------------------------------------*/
VOID
RestoreContentVector (
  IN       UINT32  ContentToRestore
  )
{
  UINT32                 Value32;
  UINTN                  Index;

  Value32 = 0;
  for (Index = 0xA0; Index <= 0xA3; Index++) {
    IoWrite8 (0x72, (UINT8)Index);
    Value32 = (UINT8) ((ContentToRestore >> (Index - 0xA0)*8));
    IoWrite8 (0x73, (UINT8)Value32);
  }
}

