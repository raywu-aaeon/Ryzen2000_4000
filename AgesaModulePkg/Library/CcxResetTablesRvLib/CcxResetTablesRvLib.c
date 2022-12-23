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
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 */
/*++
Module Name:

  CcxResetTablesRvLib.c
  Apply register table settings

Abstract:
--*/

#include <AGESA.h>
#include <Library/AmdTableLib.h>
#include <SocLogicalId.h>
#include <Filecode.h>

#define FILECODE LIBRARY_CCXRESETTABLESZPLIB_CCXRESETTABLESZPLIB_FILECODE

CONST UINT8 ROMDATA CcxRvAllCoreRegistersAfterApLaunch[] = {
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

// Reserved (0xC00110DC)
// bit[17]    Reserved = 0
// bit[15]    Reserved = 0
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV2, AMD_REV_F17_RV2_A1, 0xC00110DC, 0x0000000000000000, 0x0000000000028000),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_B1, 0xC00110DC, 0x0000000000000000, 0x0000000000028000),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

STATIC CONST UINT8 ROMDATA CcxRvComputeUnitRegistersAfterApLaunch[] =
{
//  M S R    T a b l e s
// ----------------------

// CpuWdtCfg (0xC0010074)
// bits[6:3]   CpuWdtCountSel  = 1
// bit[0]      CpuWdtEn = 1
  MAKE_MSR_ENTRY (0xC0010074, 0x0000000000000009, 0x0000000000000079),

// MC0_CONFIG (0xC0002004)
// bits[38:37] DeferredIntType      = 1
// bit[34]     LogDeferredInMcaStat = 1
// bit[33]     TransparentErrorLoggingEnable = 0
// bit[32]     McaXEnable           = 1
  MAKE_MSR_ENTRY (0xC0002004, 0x0000002500000000, 0x0000006700000000),

// MC1_CONFIG (0xC0002014)
// bits[38:37] DeferredIntType = 1
// bit[34]     LogDeferredInMcaStat = 1
// bit[33]     TransparentErrorLoggingEnable = 0
// bit[32]     McaXEnable      = 1
  MAKE_MSR_ENTRY (0xC0002014, 0x0000002500000000, 0x0000006700000000),

// MC2_CONFIG (0xC0002024)
// bits[38:37] DeferredIntType = 1
// bit[34]     LogDeferredInMcaStat = 1
// bit[33]     TransparentErrorLoggingEnable = 0
// bit[32]     McaXEnable      = 1
  MAKE_MSR_ENTRY (0xC0002024, 0x0000002500000000, 0x0000006700000000),

// MC3_CONFIG (0xC0002034)
// bits[38:37] DeferredIntType = 1
// bit[34]     LogDeferredInMcaStat = 1
// bit[33]     TransparentErrorLoggingEnable = 0
// bit[32]     McaXEnable      = 1
  MAKE_MSR_ENTRY (0xC0002034, 0x0000002500000000, 0x0000006700000000),

// MC5_CONFIG (0xC0002054)
// bits[38:37] DeferredIntType = 1
// bit[34]     LogDeferredInMcaStat = 1
// bit[33]     TransparentErrorLoggingEnable = 0
// bit[32]     McaXEnable      = 1
  MAKE_MSR_ENTRY (0xC0002054, 0x0000002500000000, 0x0000006700000000),

// MC6_CONFIG (0xC0002064)
// bits[38:37] DeferredIntType = 1
// bit[34]     LogDeferredInMcaStat = 1
// bit[33]     TransparentErrorLoggingEnable = 0
// bit[32]     McaXEnable      = 1
  MAKE_MSR_ENTRY (0xC0002064, 0x0000002500000000, 0x0000006700000000),

// MCA_CTL_MASK_IF (0xC0010401)
// bit [13]    SystemReadDataError = 1
  MAKE_MSR_ENTRY (0xC0010401, 0x0000000000002000, 0x0000000000002000),

// MCA_CTL_MASK_FP (0xC0010406)
// bit [6]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010406, 0x0000000000000040, 0x0000000000000040),

// MCA_CTL_MASK_L2 (0xC0010402)
// bit [3]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010402, 0x0000000000000008, 0x0000000000000008),

// MCA_CTL_MASK_L3 (0xC0010407)
// bit [7]     Hwa = 1
  MAKE_MSR_ENTRY (0xC0010407, 0x0000000000000080, 0x0000000000000080),

// Reserved (0xC0011020)
// bit [4]    Reserved = 1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_A0, 0xC0011020, 0x0000000000000010, 0x0000000000000010),
// bit [8]   Reserved = 1, for Revs B0
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_B0, 0xC0011020, 0x0000000000000100, 0x0000000000000100),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV2, AMD_REV_F17_RV2_A0, 0xC0011020, 0x0000000000000100, 0x0000000000000100),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_B0, 0xC0011020, 0x0000000000000100, 0x0000000000000100),
// bit [57]   Reserved = 1, for Revs B0
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_B0, 0xC0011020, 0x0200000000000000, 0x0200000000000000),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_GTE_B0, 0xC0011020, 0x0200000000000000, 0x0200000000000000),
// bit [57]   Reserved = 1, for Revs A1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV2, AMD_REV_F17_RV2_A1, 0xC0011020, 0x0200000000000000, 0x0200000000000000),

// Reserved (0xC001102D)
// bit[34]    Reserved = 1, for Revs B0
// bit [5]    Reserved = 1, for Revs B0
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_B0, 0xC001102D, 0x0000000400000020, 0x0000000400000020),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_GTE_B0, 0xC001102D, 0x0000000400000020, 0x0000000400000020),
// bit[34]    Reserved = 1, for Revs A1
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV2, AMD_REV_F17_RV2_A1, 0xC001102D, 0x0000000400000000, 0x0000000400000000),


// TW_CFG (0xC0011023)
// bit[45]     Reserved = 1
  MAKE_MSR_ENTRY (0xC0011023, 0x0000200000000000, 0x0000200000000000),

// Reserved (0xC0011028)
// bit[4]      Reserved = 1
// bit[2]      Reserved = 1
  MAKE_MSR_ENTRY (0xC0011028, 0x0000000000000014, 0x0000000000000014),

// Reserved (0xC0011029)
// bit[17]      Reserved = 1
// bit[14]      Reserved = 1
// bit[13]      Reserved = 1
  MAKE_MSR_ENTRY (0xC0011029, 0x0000000000026000, 0x0000000000026000),

// Reserved (0xC0011029)
// bit[28]    Reserved = 1, for Revs B0 and later
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_GTE_B0, 0xC0011029, 0x0000000010000000, 0x0000000010000000),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_GTE_B0, 0xC0011029, 0x0000000010000000, 0x0000000010000000),

// Reserved (0xC001102A)
// bit[57]     Reserved = 1
// bit[55]     Reserved = 1
// bit[15]     Reserved = 1
// bit[7]      Reserved = 1
  MAKE_MSR_ENTRY (0xC001102A, 0x0280000000008080, 0x0280000000008080),

// Reserved (0xC001102A)
// bit[58]       Reserved = 1, for B0 and later
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_GTE_B0, 0xC001102A, 0x0400000000000000, 0x0400000000000000),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_GTE_B0, 0xC001102A, 0x0400000000000000, 0x0400000000000000),

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
// bit[60]     Reserved = 1
// bit[32]     Reserved = 1
  MAKE_MSR_ENTRY (0xC001102D, 0x1000000100000000, 0x1000000100000000),

// Reserved (0xC001102E)
// bit[0]      Reserved = 1, for Rev B0 and later
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV, AMD_REV_F17_RV_GTE_B0, 0xC001102E, 0x0000000000000001, 0x0000000000000001),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_RV2, AMD_REV_F17_RV2_ALL, 0xC001102E, 0x0000000000000001, 0x0000000000000001),
  MAKE_MSR_CPU_REV_ENTRY (AMD_FAMILY_17_PIC, AMD_REV_F17_PIC_GTE_B0, 0xC001102E, 0x0000000000000001, 0x0000000000000001),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

CONST UINT8 ROMDATA CcxRvComplexRegistersAfterApLaunch[] = {
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
// bit[0]      Reserved = 1
  MAKE_MSR_ENTRY (0xC0011093, 0x0000000000480063, 0x00000000005D9FFF),

// Reserved (0xC0011097)
// bit[11:9]   Reserved = 7
// bit[8:6]    Reserved = 7
// bit[5:3]    Reserved = 6
// bit[2:1]    Reserved = 3
  MAKE_MSR_ENTRY (0xC0011097, 0x0000000000000FF6, 0x0000000000000FFE),

// Table Terminator
  MAKE_TABLE_TERMINATOR
};

CONST REGISTER_TABLE ROMDATA CcxRvComplexRegTableAfterApLaunch = {
  ComplexPrimary,
  CcxRvComplexRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA CcxRvCURegTableAfterApLaunch = {
  ComputeUnitPrimary,
  CcxRvComputeUnitRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA CcxRvAllCoreRegTableAfterApLaunch = {
  AllCores,
  CcxRvAllCoreRegistersAfterApLaunch,
};

CONST REGISTER_TABLE ROMDATA *CcxRvRegisterTablesAfterApLaunch[] = {
  &CcxRvAllCoreRegTableAfterApLaunch,
  &CcxRvCURegTableAfterApLaunch,
  &CcxRvComplexRegTableAfterApLaunch,
  NULL
};

CONST REGISTER_TABLE ROMDATA *CcxRvRegisterTablesAfterApLaunchSecureS3[] = {
  NULL
};

CONST REGISTER_TABLE_AT_GIVEN_TP ROMDATA CcxRvRegTableListAtGivenTP[] = {
  {AmdRegisterTableTpAfterApLaunch, CcxRvRegisterTablesAfterApLaunch},
  {AmdRegisterTableTpAfterApLaunchSecureS3, CcxRvRegisterTablesAfterApLaunchSecureS3},
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
    SetRegistersFromTablesAtGivenTimePoint ((REGISTER_TABLE_AT_GIVEN_TP *) &CcxRvRegTableListAtGivenTP[0], AmdRegisterTableTpAfterApLaunchSecureS3, StdHeader);
  } else {
    SetRegistersFromTablesAtGivenTimePoint ((REGISTER_TABLE_AT_GIVEN_TP *) &CcxRvRegTableListAtGivenTP[0], AmdRegisterTableTpAfterApLaunch, StdHeader);
  }
}


