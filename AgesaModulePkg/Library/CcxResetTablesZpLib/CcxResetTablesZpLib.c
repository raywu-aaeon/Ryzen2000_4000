/* $NoKeywords:$ */
/**
 * @file
 *
 * CCX Reset Tables Library - ZP
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

  CcxResetTablesZpLib.c
  Apply register table settings

Abstract:
--*/

#include <AGESA.h>
#include <Library/AmdTableLib.h>
#include <SocLogicalId.h>
#include <Filecode.h>

#define FILECODE LIBRARY_CCXRESETTABLESZPLIB_CCXRESETTABLESZPLIB_FILECODE

CONST UINT8 ROMDATA CcxZpAllCoreRegistersAfterApLaunch[] = {
// APIC_BAR (0x0000001B)
// bit[11]     ApicEn = 1
  MAKE_MSR_ENTRY (0x0000001B, 0x0000000000000800, 0x0000000000000800),

// HWCR (0xC0010015)
// bit[27]     EffFreqReadOnlyLock = 1
  MAKE_MSR_ENTRY (0xC0010015, 0x0000000008000000, 0x0000000008000000),

// CPUIDExt0xC0011005
// bit [48] FMA4 = 0
// bit [42] IBS = 0
  MAKE_MSR_ENTRY (0xC0011005, 0x0000000000000000, 0x0001040000000000),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

STATIC CONST UINT8 ROMDATA CcxZpComputeUnitRegistersAfterApLaunch[] =
{
//  M S R    T a b l e s
// ----------------------
// MCA_CTL_MASK_IF (0xC0010401)
// bit [13]    SystemReadDataError = 1
  MAKE_MSR_ENTRY (0xC0010401, 0x0000000000002000, 0x0000000000002000),

// MCA_CTL_MASK_L2 (0xC0010402)
// bit [3]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010402, 0x0000000000000008, 0x0000000000000008),

// MCA_CTL_MASK_FP (0xC0010406)
// bit [6]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010406, 0x0000000000000040, 0x0000000000000040),

// Reserved (0xC0011020)
// bit [57]   Reserved = 1, for Revs >= B1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B1, 0xC0011020, 0x0200000000000000, 0x0200000000000000),

// Reserved (0xC001102D)
// bit [5]    Reserved = 1, for Revs >=B2
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B2, 0xC001102D, 0x0000000000000020, 0x0000000000000020),
// bit[34]    Reserved = 1, for Revs >= B1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B1, 0xC001102D, 0x0000000400000000, 0x0000000400000000),

// TW_CFG (0xC0011023)
// bit[45]     Reserved = 1 if AM4
  MAKE_MSR_PLATFORM_FEAT_ENTRY (AMD_PF_AM4, 0xC0011023, 0x0000200000000000, 0x0000200000000000),

// Reserved (0xC0011020)
// bit[4]        Reserved = 0, for PR_Bx
// bit[57]       Reserved = 1, for PR_Bx
// bit[8]        Reserved = 1, for ZP_PR_ALL
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_PR_Bx, 0xC0011020, 0x0200000000000000, 0x0200000000000010),
  MAKE_MSR_CPU_REV_PLATFORM_FEAT_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_ALL, AMD_PF_AM4, 0xC0011020, 0x0000000000000100, 0x0000000000000100),

// TW_CFG (0xC0011023)
// bit[8]     Reserved = 1 if B1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_B1, 0xC0011023, 0x0000000000000100, 0x0000000000000100),

// Reserved (0xC0011028)
// bit[43]     Reserved = 1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_A0, 0xC0011028, 0x0000080000000000, 0x0000080000000000),

// Reserved (0xC0011028)
// bit[4]      Reserved = 1
// bit[2]      Reserved = 1
  MAKE_MSR_ENTRY (0xC0011028, 0x0000000000000014, 0x0000000000000014),

// Reserved (0xC0011029)
// bit[14]        Reserved = 1
// bit[10]        Reserved = 1. for Rev A0
  MAKE_MSR_ENTRY (0xC0011029, 0x0000000000004000, 0x0000000000004000),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_A0, 0xC0011029, 0x0000000000000400, 0x0000000000000400),
// Reserved (0xC0011029)
// bit[17]      Reserved = 1
// bit[13]      Reserved = 1
  MAKE_MSR_ENTRY (0xC0011029, 0x0000000000022000, 0x0000000000022000),

// Reserved (0xC0011029)
// bit[28]    Reserved = 1, for Revs >= B2
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B2, 0xC0011029, 0x0000000010000000, 0x0000000010000000),

// Reserved (0xC001102A)
// bit[5]        Reserved = 1, for A0 only
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_A0, 0xC001102A, 0x0000000000000020, 0x0000000000000020),

// Reserved (0xC001102A)
// bit[57]       Reserved = 1, for Bx only
// bit[55]       Reserved = 1, for Bx only
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_Bx, 0xC001102A, 0x0280000000000000, 0x0280000000000000),

// Reserved (0xC001102A)
// bit[58]       Reserved = 1, for >= B2
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B2, 0xC001102A, 0x0400000000000000, 0x0400000000000000),

// Reserved (0xC001102A)
// bit[15]     Reserved = 1
// bit[7]      Reserved = 1
  MAKE_MSR_ENTRY (0xC001102A, 0x0000000000008080, 0x0000000000008080),

// Reserved (0xC001102C)
// bit[56]     Reserved = 1
// bit[54]     Reserved = 1
// bit[53]     Reserved = 1
// bit[51]     Reserved = 1
  MAKE_MSR_ENTRY (0xC001102C, 0x0168000000000000, 0x0168000000000000),

// Reserved (0xC001102B)
// bit[19]     Reserved = 1
  MAKE_MSR_ENTRY (0xC001102B, 0x0000000000080000, 0x0000000000080000),

// Reserved (0xC001102D)
// bit[34]        Reserved = 1, for A0 & PR_Bx only
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, (AMD_REV_F17_ZP_A0 | AMD_REV_F17_PR_Bx), 0xC001102D, 0x0000000400000000, 0x0000000400000000),

// Reserved (0xC001102D)
// bit[60]     Reserved = 1
// bit[32]     Reserved = 1
  MAKE_MSR_ENTRY (0xC001102D, 0x1000000100000000, 0x1000000100000000),

// Reserved (0xC001102E)
// bit[28]     Reserved = 1, for A0 and B0 only.
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, (AMD_REV_F17_ZP_A0 | AMD_REV_F17_ZP_B0), 0xC001102E, 0x0000000010000000, 0x0000000010000000),

// Reserved (0xC001102E)
// bit[0]      Reserved = 1, for Rev >= B2
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B2, 0xC001102E, 0x0000000000000001, 0x0000000000000001),

// Reserved (0xC0011074)
// bit[60]     Reserved = 0
  MAKE_MSR_ENTRY (0xC0011074, 0x0000000000000000, 0x1000000000000000),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

CONST UINT8 ROMDATA CcxZpComplexRegistersAfterApLaunch[] = {
// Reserved (0xC0011093)
// bit[22]     Reserved = 1
// bit[20:19]  Reserved = 1
// bit[18]     Reserved = 0
// bit[16]     Reserved = 0
// bit[15]     Reserved = 0
// bit[12:10]  Reserved = 0
// bit[9:7]    Reserved = 0
// bit[6:4]    Reserved = 6
// bit[3:1]    Reserved = 1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_LT_B1, 0xC0011093, 0x0000000000480062, 0x00000000005D9FFE),

// Reserved (0xC0011093)
// for Revs >= B1
// bit[22]     Reserved = 1
// bit[20:19]  Reserved = 1
// bit[18]     Reserved = 0
// bit[16]     Reserved = 0
// bit[15]     Reserved = 0
// bit[12:10]  Reserved = 0
// bit[9:8]    Reserved = 0
// bit[6:4]    Reserved = 6
// bit[3:2]    Reserved = 0
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_ZP, AMD_REV_F17_ZP_PR_GTE_B1, 0xC0011093, 0x0000000000480060, 0x00000000005D9F7C),

// Reserved (0xC0011097)
// bit[11:9]   Reserved = 7
// bit[8:6]    Reserved = 7
// bit[5:3]    Reserved = 6
// bit[2:1]    Reserved = 3
  MAKE_MSR_ENTRY (0xC0011097, 0x0000000000000FF6, 0x0000000000000FFE),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

CONST REGISTER_TABLE ROMDATA CcxZpComplexRegTableAfterApLaunch = {
  ComplexPrimary,
  CcxZpComplexRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA CcxZpCURegTableAfterApLaunch = {
  ComputeUnitPrimary,
  CcxZpComputeUnitRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA CcxZpAllCoreRegTableAfterApLaunch = {
  AllCores,
  CcxZpAllCoreRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA *CcxZpRegisterTablesAfterApLaunch[] = {
  &CcxZpAllCoreRegTableAfterApLaunch,
  &CcxZpCURegTableAfterApLaunch,
  &CcxZpComplexRegTableAfterApLaunch,
  NULL
};

CONST REGISTER_TABLE ROMDATA *CcxZpRegisterTablesAfterApLaunchSecureS3[] = {
  NULL
};

CONST REGISTER_TABLE_AT_GIVEN_TP ROMDATA CcxZpRegTableListAtGivenTP[] = {
  {AmdRegisterTableTpAfterApLaunch, CcxZpRegisterTablesAfterApLaunch},
  {AmdRegisterTableTpAfterApLaunchSecureS3, CcxZpRegisterTablesAfterApLaunchSecureS3},
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
    SetRegistersFromTablesAtGivenTimePoint ((REGISTER_TABLE_AT_GIVEN_TP *) &CcxZpRegTableListAtGivenTP[0], AmdRegisterTableTpAfterApLaunchSecureS3, StdHeader);
  } else {
    SetRegistersFromTablesAtGivenTimePoint ((REGISTER_TABLE_AT_GIVEN_TP *) &CcxZpRegTableListAtGivenTP[0], AmdRegisterTableTpAfterApLaunch, StdHeader);
  }
}


