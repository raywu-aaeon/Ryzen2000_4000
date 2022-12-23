/* $NoKeywords:$ */
/**
 * @file
 *
 * CCX Reset Tables Library - VH
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

  CcxResetTablesVhLib.c
  Apply register table settings

Abstract:
--*/

#include <AGESA.h>
#include <Library/AmdTableLib.h>
#include <SocLogicalId.h>
#include <Filecode.h>

#define FILECODE LIBRARY_CCXRESETTABLESVHLIB_CCXRESETTABLESVHLIB_FILECODE

CONST UINT8 ROMDATA CcxVhAllCoreRegistersAfterApLaunch[] = {
// To enable x2APIC mode, we have to set ApicEn first then set x2ApicEn
// Transition from disabled mode to x2APIC mode is illegal per x2APIC spec

// APIC_BAR (0x0000001B)
// bit[11]     ApicEn = 1
  MAKE_MSR_ENTRY (0x0000001B, 0x0000000000000800, 0x0000000000000800),

// APIC_BAR (0x0000001B)
// bit[10]     x2ApicEn = 1
  MAKE_MSR_PLATFORM_FEAT_ENTRY (AMD_PF_X2APIC, 0x0000001B, 0x0000000000000400, 0x0000000000000400),

// CPUID_FEATURES (0xC0011004)
// bit[53]     X2APIC = 0
  MAKE_MSR_PLATFORM_FEAT_ENTRY (AMD_PF_APIC, 0xC0011004, 0, BIT53),

// BU workaround
// HDT_CFG (0xC001100A)
// bit[20]     SHTDWNDBG = 1
  MAKE_MSR_ENTRY (0xC001100A, 0x0000000000100000, 0x0000000000100000),

// HWCR (0xC0010015)
// bit[27]     EffFreqReadOnlyLock = 1
  MAKE_MSR_ENTRY (0xC0010015, 0x0000000008000000, 0x0000000008000000),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

STATIC CONST UINT8 ROMDATA CcxVhComputeUnitRegistersAfterApLaunch[] =
{
//  M S R    T a b l e s
// ----------------------
// MCA_CTL_MASK_LS (0xC0010400)
// bit[10]     SystemReadDataErrorT1 = 0
// bit[9]      SystemReadDataErrorT0 = 0
  MAKE_MSR_ENTRY (0xC0010400, 0x0000000000000000, 0x0000000000000600),

// MCA_CTL_MASK_IF (0xC0010401)
// bit[13]     SystemReadDataError = 0
// bit[11]     L2BtbMultiHit = 1
// bit[10]     L1BtbMultiHit = 1
  MAKE_MSR_ENTRY (0xC0010401, 0x0000000000000C00, 0x0000000000002C00),

// MCA_CTL_MASK_L2 (0xC0010402)
// bit [3]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010402, 0x0000000000000008, 0x0000000000000008),

// MCA_CTL_MASK_FP (0xC0010406)
// bit [6]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010406, 0x0000000000000040, 0x0000000000000040),

// Reserved (0xC0011020)
// bit[48:47] Reserved = 0
// bit[46]    Reserved = 1
// bit[39]    Reserved = 0
// bit[38]    Reserved = 1
  MAKE_MSR_ENTRY (0xC0011020, 0x0000404000000000, 0x0001C0C000000000),

// Reserved (0xC0011028)
// bit[4]     Reserved = 1
// bit[2]     Reserved = 1 WA for Ax
  MAKE_MSR_ENTRY (0xC0011028, 0x0000000000000010, 0x0000000000000010),
  MAKE_MSR_CORE_REV_ENTRY (AMD_CORE_FAMILY_17_VH, AMD_CORE_F17_VH_Ax, 0xC0011028, 0x0000000000000004, 0x0000000000000004),

// Reserved (0xC0011029)
// bit[49]    Reserved = 1
// bit[48]    Reserved = 1
// bit[33]    Reserved = 1
// bit[32]    Reserved = 1
// bit[28]    Reserved = 1
  MAKE_MSR_ENTRY (0xC0011029, 0x0003000310000000, 0x0003000310000000),

// Reserved (0xC001102A)
// bit[16]    Reserved = 1
// bit[15]    Reserved = 1
// bit[7]     Reserved = 1
  MAKE_MSR_ENTRY (0xC001102A, 0x0000000000018080, 0x0000000000018080),

// Reserved (0xC001102C)
// bits[57:56] Reserved = 0x3
// bit[51]     Reserved = 1
  MAKE_MSR_ENTRY (0xC001102C, 0x0308000000000000, 0x0308000000000000),

// Reserved (0xC001102D)
// bit[34]    Reserved = 1
// bit[4]     Reserved = 1 GTE_B0
  MAKE_MSR_ENTRY (0xC001102D, 0x0000000400000000, 0x0000000400000000),
  MAKE_MSR_CORE_REV_ENTRY (AMD_CORE_FAMILY_17_VH, AMD_CORE_F17_VH_GTE_B0, 0xC001102D, 0x0000000000000010, 0x0000000000000010),

// Reserved (0xC001102E)
// bit[41]   Reserved = 1
// bit[33]   Reserved = 1 WA for Ax
// bit[17]   Reserved = 1 WA for Ax
// bit[5]    Reserved = 1 WA for Ax
  MAKE_MSR_ENTRY (0xC001102E, 0x0000020000000000, 0x0000020000000000),
  MAKE_MSR_CORE_REV_ENTRY (AMD_CORE_FAMILY_17_VH, AMD_CORE_F17_VH_Ax, 0xC001102E, 0x0000000200020020, 0x0000000200020020),


// Reserved (0xC00110E2)
// bit[47:45] Reserved = 1
// bit[44:42] Reserved = 2
// bit[41]    Reserved = 1
// bit[39]    Reserved = 1
// bit[38]    Reserved = 1
// bit[37]    Reserved = 1
// bit[36]    Reserved = 1
// bit[35]    Reserved = 1
// bit[33]    Reserved = 1
// bit[32]    Reserved = 1
// bit[19]    Reserved = 1
// bit[4]     Reserved = 1
// bit[3]     Reserved = 1
  MAKE_MSR_ENTRY (0xC00110E2, 0x00002AFB00080018, 0x0000FEFB00080018),

// Reserved (0xC0011074)
// bit[60]     Reserved = 0
  MAKE_MSR_ENTRY (0xC0011074, 0x0000000000000000, 0x1000000000000000),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

CONST UINT8 ROMDATA CcxVhComplexRegistersAfterApLaunch[] = {

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

CONST REGISTER_TABLE ROMDATA CcxVhComplexRegTableAfterApLaunch = {
  ComplexPrimary,
  CcxVhComplexRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA CcxVhCURegTableAfterApLaunch = {
  ComputeUnitPrimary,
  CcxVhComputeUnitRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA CcxVhAllCoreRegTableAfterApLaunch = {
  AllCores,
  CcxVhAllCoreRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA *CcxVhRegisterTablesAfterApLaunch[] = {
  &CcxVhAllCoreRegTableAfterApLaunch,
  &CcxVhCURegTableAfterApLaunch,
  &CcxVhComplexRegTableAfterApLaunch,
  NULL
};

CONST REGISTER_TABLE ROMDATA *CcxVhRegisterTablesAfterApLaunchSecureS3[] = {
  NULL
};

CONST REGISTER_TABLE_AT_GIVEN_TP ROMDATA CcxVhRegTableListAtGivenTP[] = {
  {AmdRegisterTableTpAfterApLaunch, CcxVhRegisterTablesAfterApLaunch},
  {AmdRegisterTableTpAfterApLaunchSecureS3, CcxVhRegisterTablesAfterApLaunchSecureS3},
  {MaxAmdRegisterTableTps, NULL}
};


/*++

Routine Description:

  Zen - Zeppelin Register table programming

Arguments:
  SleepType
  AMD_CONFIG_PARAMS *

Returns:

--*/
VOID
CcxProgramTablesAtReset (
  IN       UINT8               SleepType,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  )
{
  if (SleepType == 0x03) {
    SetRegistersFromTablesAtGivenTimePoint ((REGISTER_TABLE_AT_GIVEN_TP *) &CcxVhRegTableListAtGivenTP[0], AmdRegisterTableTpAfterApLaunchSecureS3, StdHeader);
  } else {
    SetRegistersFromTablesAtGivenTimePoint ((REGISTER_TABLE_AT_GIVEN_TP *) &CcxVhRegTableListAtGivenTP[0], AmdRegisterTableTpAfterApLaunch, StdHeader);
  }
}


