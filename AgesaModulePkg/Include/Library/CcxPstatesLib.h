/* $NoKeywords:$ */
/**
 * @file
 *
 * CCX base Services library prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 */
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
 *******************************************************************************
 **/
#ifndef _CCX_PSTATES_LIB_H_
#define _CCX_PSTATES_LIB_H_
#pragma pack (push, 1)

/*---------------------------------------------------------------------------------------
 *               T Y P E D E F S,   S T R U C T U R E S,    E N U M S
 *---------------------------------------------------------------------------------------
 */
/// Pstate enum
typedef enum {
  SwPstate0 = 0,       ///< Software P0
  SwPstate1,           ///< Software P1
  SwPstate2,           ///< Software P2
  SwPstate3,           ///< Software P3
  SwPstate4,           ///< Software P4
  SwPstate5,           ///< Software P5
  SwPstate6,           ///< Software P6
  SwPstate7,           ///< Software P7
  HwPstate0 = 0x80,    ///< Hardware P0
  HwPstate1,           ///< Hardware P1
  HwPstate2,           ///< Hardware P2
  HwPstate3,           ///< Hardware P3
  HwPstate4,           ///< Hardware P4
  HwPstate5,           ///< Hardware P5
  HwPstate6,           ///< Hardware P6
  HwPstate7            ///< Hardware P7
} CCX_PSTATE;

/// Switch Core Pstate
typedef struct {
  UINTN    Pstate;             ///< Target Pstate
  BOOLEAN  WaitForCompletion;  ///< Wait for Pstate transition to complete
} CCX_SWITCH_PSTATE;

#define SW_PSTATE_MAX SwPstate0
#define HW_PSTATE_MAX HwPstate0
#define HW_PSTATE_MIN HwPstate7

/*---------------------------------------------------------------------------------------
 *                        F U N C T I O N    P R O T O T Y P E
 *---------------------------------------------------------------------------------------
 */
BOOLEAN
CcxGetPstateInfo (
  IN       UINTN               Socket,
  IN       CCX_PSTATE          Pstate,
     OUT   UINTN              *Frequency,
     OUT   UINTN              *VoltageInuV,
     OUT   UINTN              *PowerInmW,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  );

VOID
CcxGetPstateNumber (
  IN       UINTN               Socket,
     OUT   UINTN              *NumberOfBoostPstate,
     OUT   UINTN              *NumberOfHwPstate,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  );

VOID
CcxSwitchPstate (
  IN       CCX_SWITCH_PSTATE *SwitchPstate
  );

UINT8
CcxGetCurrentPstate (
  );

#pragma pack (pop)
#endif // _CCX_PSTATES_LIB_H_
