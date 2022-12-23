/* $NoKeywords:$ */
/**
 * @file
 *
 * mnphycz.c
 *
 * Northbridge Phy support for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 317293 $ @e \$Date: 2015-04-22 08:44:09 +0800 (Wed, 22 Apr 2015) $
 *
 **/
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
*
*/


/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */


#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "cpuRegisters.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mnreg.h"
#include "OptionMemory.h"       // need def for MEM_FEAT_BLOCK_NB
#include "mncz.h"
#include "PlatformMemoryConfiguration.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNPHYCZ_FILECODE
/* features */
#include "mftds.h"
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

typedef struct {
  UINT8 BankAddr :4;
  UINT8 Addr13 :1;
  UINT8 Addr14 :1;
  UINT8 Addr15 :1;
  UINT8 Reserved :1;
} BANK_ADDR_MAP;
/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

VOID
MemNTriStateUnusedPadCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function programs DDR mode for each Phy
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNSetPhyDdrModeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tSet MajorMode=%d\n", Mode);
  // According to the type of DRAM attached, program the following phy mode
  // D18F2x9C_x00F0_000E_dct[1:0][D4_Mode]
  MemNSetBitFieldNb (NBPtr, BFD4ModeAbyte, (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x1);
  // D18F2x9C_x00[F,8:0]1_000E_dct[1:0][D4_Mode]
  MemNSetBitFieldNb (NBPtr, BFD4ModeDbyte, (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x1);
  // D18F2x9C_x0002_000E_dct[1:0][D4_Mode]
  MemNSetBitFieldNb (NBPtr, BFD4ModeMByte, (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x1);
  // D18F2x9C_x00[F,3:0]0_[F,B:0]04A_dct[1:0][MajorMode]
  MemNSetBitFieldNb (NBPtr, BFMajorModeAbyte, (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x3);
  // D18F2x9C_x0[3,1:0][F,8:0]1_[F,B:0]043_dct[1:0][MajorMode]
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFMajorModeDbyte), (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x3);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFMajorModeDbyte), (Mode == DRAM_TYPE_DDR3_CZ) ? 0x4 : 0x3);
  // D18F2x9C_x0[3,1:0][F,8:0]1_[F,B:0]043_dct[1:0][ExtVrefRange]
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFExtVrefRange), (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x1);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFExtVrefRange), (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0 : 0x1);
  // D18F2x9C_x0004_00F0_dct[1:0][AcsmDdrMode(1=DDR4, 0=DDR3)] (ACSM)
  MemNSetBitFieldNb (NBPtr, BFAcsmDdrMode, (Mode == DRAM_TYPE_DDR3_CZ) ? 0x1 : 0x0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs general Phy configuration registers
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPhyGenCfgCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT64 RODT;
  UINT64 WODT;
  UINT8  Cs;
  UINT8  PerCsFunction;
  UINT32 X4Dimm;
  CPUID_DATA CpuId;
  UINT8 RegValue;
  DCT_STRUCT *DCTPtr;

  DCTPtr = NBPtr->DCTPtr;

  X4Dimm = 0;
  PerCsFunction = 1;

  // Program D18F2x9C_x00[F,3:0]0_0009_dct[1:0][HiAddrMode].
  MemNSetBitFieldNb (NBPtr, RegHighAddrMode, 0);

  // Program D18F2x9C_x0[3,1:0][F,8:0]1_0010_dct[1:0][X4Dimm]
  if (MemNGetBitFieldNb (NBPtr, BFPerRankTimingEn) == 0) {
    PerCsFunction = 2;
  }
  for (Cs = 0; Cs < MAX_CS_PER_CHANNEL; Cs++) {
    X4Dimm |= (((DCTPtr->Timings.Dimmx4Present >> (Cs / 2)) & 1) << (Cs / PerCsFunction));
  }
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, RegDByteCtrl1), X4Dimm);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, RegDByteCtrl1), X4Dimm);

  // Program D18F2x9C_x00F4_00E[7:0]_dct[1:0][OdtRdPatCs, OdtWrPatCs] per 2.10.10.3.1 [DRAM ODT Pin Control].
  RODT = (LShiftU64 ((UINT64) NBPtr->ChannelPtr->PhyRODTCSHigh, 32)) | NBPtr->ChannelPtr->PhyRODTCSLow;
  WODT = (LShiftU64 ((UINT64) NBPtr->ChannelPtr->PhyWODTCSHigh, 32)) | NBPtr->ChannelPtr->PhyWODTCSLow;
  for (Cs = 0; Cs < MAX_CS_PER_CHANNEL; Cs++) {
    MemNSetBitFieldNb (NBPtr, RegAcsmOdtCtrl0 + Cs, (UINT32) (LShiftU64 (((RShiftU64 (RODT, (Cs * 8))) & 0xF), 4) | ((RShiftU64 (WODT, (Cs * 8))) & 0xF)));
  }

  // Program D18F2x9C_x00[F,8:0]1_0016_dct[1:0][POdtWidthDq, POdtWidthDqs, POdtStartDelayDq, POdtStartDelayDqs, ProcOdtOff, ProcOdtOn].
  MemNSetBitFieldNb (NBPtr, RegProcOdtTmg, 0x1244);

  // Program D18F2x9C_x00F0_0015_dct[3:0][VrefFilt]
  MemNSetBitFieldNb (NBPtr, RegVrefByteAbyte, 0);

  // Program D18F2x9C_x0002_0098_dct[1:0][CalD4D3] = 0
  MemNSetBitFieldNb (NBPtr, BFCalD4D3, 0);

  // Programs the following for maximum power savings prior to training:
  MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegTxControlDq), 0x0000);
  MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegTxControlDq2), 0x8000);
  MemNSetBitFieldNb (NBPtr, RegCadByteDbgCtrl, 0x0022);
  MemNSetBitFieldNb (NBPtr, RegDataByteDbgCtrl, 0x0033);
  MemNSetBitFieldNb (NBPtr, RegMasterByteDbgCtrl, 0x0001);
  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  RegValue = (UINT8) (CpuId.EBX_Reg >> 28) & 0xF; // bit 31:28
  if (RegValue == 0) {
    // FP4 package
    MemNSetBitFieldNb (NBPtr, RegMasterD3MerrRcvrCntrl, 0x0000);
  }
  MemNSetBitFieldNb (NBPtr, RegMasterD3EvntMerr, 0x0000);
  MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDataDqDqsRcvCntrl3), 0x0052);

  if (X4Dimm == 0) {
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhyDllPowerdown0), 0x800);
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhyDllPowerdown2), 0x1000);
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhyDllPowerdown2), 0x1001);
  }

  // Program static value for Abyte/DByte DllPumpCount and MaxDurDllNoLock, BIOS:0
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFCadDllPumpCount), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFCadMaxDurDllNoLock), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFDataDllPumpCount), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFDataMaxDurDllNoLock), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFCadDllPumpCount), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFCadMaxDurDllNoLock), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFDataDllPumpCount), 0);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFDataMaxDurDllNoLock), 0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the phy registers according to the desired phy VDDIO voltage level
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNPhyVoltageLevelCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{
  UINT8 Voltage;
  UINT32 Value8;

  switch (NBPtr->RefPtr->DDRVoltage) {
  case VOLT1_5:
    Voltage = 3;
    break;
  case VOLT1_35:
    Voltage = 2;
    break;
  case VOLT1_25:
  case VOLT1_2:
    Voltage = 1;
    break;
  default:
    Voltage = 3;
    break;
  }

  // Program D18F2x9C_x00[F,3:0]0_[F,B:0]04A_dct[1:0][AVoltageLevel].
  MemNSetBitFieldNb (NBPtr, BFAVoltageLevel, Voltage);
  // Program D18F2x9C_x00[F,8:0]1_[F,B:0]04A_dct[1:0][VoltageLevel].
  MemNSetBitFieldNb (NBPtr, BFVoltageLevel, Voltage);
  // Program D18F2x9C_x0002_009B_dct[1:0]= If Ddr4Mode Then EA02h Else E024h
  MemNSetBitFieldNb (NBPtr, RegCalVRefs, 0xE024);
  if ((Mode == DRAM_TYPE_DDR4_CZ) && (NBPtr->ChannelPtr->Dimms > 1)) {
    Value8 = 0x5F;
  } else {
    Value8 = 0x40;
  }
  IDS_HDT_CONSOLE(MEM_FLOW, "RegVrefHSpeed = %02x\n", Value8);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS ((Mode == DRAM_TYPE_DDR4_CZ) ? ALL_MEM_PS : 1, RegVrefHSpeed), Value8);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, RegVrefLpower), 0x40);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs DRAM channel frequency
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNProgramChannelFreqCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{
  UINT16 Freq;
  UINT16 PllMultDiv;
  UINT16 PMUClkDiv;

  // 1. Program D18F2x9C_x0002_0093_dct[1:0][PllRegWaitTime] = 4Bh.
  MemNSetBitFieldNb (NBPtr, RegPllRegWaitTime, 0x4B);

  // 2. Program D18F2x9C_x0002_0089_dct[1:0][PllLockTime] = C8h. Restore the default PLL lock time.
  MemNSetBitFieldNb (NBPtr, RegPllLockTime, 0xC8);

  // 3. Program D18F2x9C_x0002_0000_dct[1:0][PllMultDiv]. PMU Reset must be high.
  Freq = NBPtr->DCTPtr->Timings.TargetSpeed * 2;
  PllMultDiv = ((Freq / 100) * 0x100) + ((Freq % 100) / 20);
  MemNSetBitFieldNb (NBPtr, RegPllMemPs0, PllMultDiv);

  // 4. Program D18F2x9C_x0002_0080_dct[1:0][PMUClkDiv].
  // PMU must operate no faster than 533MHz
  PMUClkDiv = CEIL_DIV (((CEIL_DIV (Freq, 533) < 1) ? 0 : CEIL_DIV (Freq, 533)), 2);
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (0, BFPMUClkDiv),  PMUClkDiv);

  // 5. Program D18F2x9C_x0002_0001_dct[1:0][PllMultDiv] = If Ddr4ModeThen '1333 MT/s' else '667 MT/s'.
  MemNSetBitFieldNb (NBPtr, RegPllMemPs1, (Mode == DRAM_TYPE_DDR3_CZ) ? 0x0603 : 0x0D01);

  // 6. IF (Ddr3Mode) program D18F2x9C_x0102_0080_dct[1:0][PMUClkDiv].
  MemNSetBitFieldNb (NBPtr, PER_MEM_PS (1, BFPMUClkDiv), 1);
}



/* -----------------------------------------------------------------------------*/
/**
 *
 *    DRAM Phy Power Savings, tri-state unused pads, and DLLs.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Mode     - DDR3/DDR4
 *
 */

VOID
MemNDramPhyPowerSavingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8  Mode
  )
{
  CONST UINT8 DLL_RESET_RELOCK_SHIFT = 7;

  IDS_SKIP_HOOK (IDS_MEM_PHY_POWER_SAVING, NBPtr, &NBPtr->MemPtr->StdHeader) {
    // 1. Program DctPhyA41 as follows to disable unused pads.
    // DrvStrenP = DrvStrenP = 0.
    // See 2.10.4. Software does this for each unconnected pad in the package or each pad
    // connected to unused pins
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tTri-state unused pads\n");
    MemNTriStateUnusedPadCZ (NBPtr);

    // 2. Program D18F2x9C_x0[3,1:0][F,3:0]0_0014_dct[1:0][MaxDurDllNoLock] = 0.
    // DctPhyA78[DllResetRelock] must be set to 1 prior to writing this register
    // and then DctPhyA78[DllResetRelock] must be cleared after the register
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tCAD DLL standby\n");
    MemNSetBitFieldNb (NBPtr, RegDctPhyA78DllControl, (1 << DLL_RESET_RELOCK_SHIFT));
    MemNSetBitFieldNb (NBPtr, BFCadMaxDurDllNoLock, 0);
    MemNSetBitFieldNb (NBPtr, RegDctPhyA78DllControl, 0);

    if (NBPtr->MemPstate == 1 && Mode == DRAM_TYPE_DDR3_CZ) {
      // 3. Program D18F2x9C_x0[3,1:0][F,8:0]1_[F,B:0]04D_dct[1:0] as follows:
      // For M1 context program ODTStrenN = ODTStrenP = 0
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ALL_BYTES, RegDataRxImpedance), 0);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS, ALL_BYTES, RegDataRxImpedance), 0);
    }
  }
  // Restore cold reset default values over a warm reset so that a change from "ECC disabled"
  // to "ECC enabled" does not affect the PMU training environment
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, BFPowerDownRcvrDbyte), 0);
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS, ECC_BYTE, BFPowerDownRcvrDbyte), 0);
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD00910F77), 0);
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD00910000), 0);
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD00910F77), 0);
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD0091F04E), 0x1300);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Additional DRAM Phy Power Savings
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNAddlDramPhyPowerSavingsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

  IDS_SKIP_HOOK (IDS_MEM_PHY_POWER_SAVING, NBPtr, &NBPtr->MemPtr->StdHeader) {
    // 4. Program D18F2x9C_x00[F,3:0]0_[F,B:0]04A_dct[1:0][PowerDownRcvr] = 1.
    MemNSetBitFieldNb (NBPtr, BFPowerDownRcvrAbyte, 1);

    // 6. Disable unused DLL components in ABYTE as follows:
    // Program D18F2x9C_x0020_0077_dct[] = 07C0h. Disable Tx DLL in Abyte 2.
    // Program D18F2x9C_x0030_0077_dct[] = 07C0h. Disable Tx DLL in Abyte 3.
    // Program D18F2x9C_x0000_0077_dct[] = 07C4h.
    // Program D18F2x9C_x0010_0077_dct[] = 07C4h.
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhy0x00200077), 0x0);
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhy0x00300077), 0x0);
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhy0x00000077), 0x4);
    if (MemNGetBitFieldNb (NBPtr, BFParEn) != 0) {
      MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhy0x00100077), 0x0);
    } else {
      MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhy0x00100077), 0x8);
    }

    // 7. If ECC memory is not connected or is disabled, or the package does not support ECC,
    // then power down data chiplet 8 with the following:
    // Write to all memory P-state instances if available.
    // Program D18F2x9C_x00[F,8:0]1_[F,B:0]04A_dct[1:0][PowerDownRcvr]=1
    // Program D18F2x9C_x00[F,8:0]1_0[F,2:0]77_dct[1:0] = 07CFh.  Turn off all DLLs
    // Program D18F2x9C_x00[F,8:0]1_0000_dct[1:0][DByteEnable]=1. Actually "disables"
    // Program D18F2x9C_x00[F,8:0]1_0[F,2:0]77_dct[1:0] = 07DFh.  Turn off XCLK
    // Program D18F2x9C_x0[3,1:0][F,8:0]1_[F,B:0]04D_dct[1:0] = 0000h.  Disable Odt
    // Program D18F2x9C_x0[3,1:0][F,8:0]1_[F,B:0]041_dct[1:0] = 0000h.  Disable output driver impedance
    // Program D18F2x9C_x00[F,8:0]1_[F,B:0]04E_dct[1:0]= 0000h
    if (MemNGetBitFieldNb (NBPtr, BFDimmEccEn) == 0) {
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, BFPowerDownRcvrDbyte), 1);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS, ECC_BYTE, BFPowerDownRcvrDbyte), 1);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD00910F77), 0x07CF);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD00910000), 0x0004);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD00910F77), 0x07DF);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD0391F04D), 0x0000);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD0391F041), 0x0000);
      MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDctPhyD0091F04E), 0x0000);
    }

    // 8. Power down unused receivers in data chips as follows:
    // Program D18F2x9C_x00F1_904A_dct[1:0][PowerDownRcvr]=1. DBI.
    // If x4 DIMMs are not present then program D18F2x9C_x00F1_B04A_dct[1:0][PowerDownRcvr]=1.
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhyD00F1904A), 0x0100);
    if (MemNGetBitFieldNb (NBPtr, BFX4Dimm) == 0) {
      MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegDctPhyD00F1B04A), 0x0100);
    }

    // 10. Power down the PMU
    MemNDisablePmuCZ (NBPtr);

    // D18F2x9C_x0002_005D_dct[1:0][ForceHClk] = 0.
    MemNSetBitFieldNb (NBPtr, PER_INSTANCE (RegMisc5), 0);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Enable DDR3 PHY calibrating
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNEnablePhyCalibrationCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNSetBitFieldNb (NBPtr, BFCalOnce, 1);
  MemNSetBitFieldNb (NBPtr, RegCalRate, 0xA3);
  MemNSetBitFieldNb (NBPtr, BFCalRun, 1);
  MemNSetBitFieldNb (NBPtr, RegCalRate, 0xB3);
  MemNSetBitFieldNb (NBPtr, BFCalRun, 0);
  MemNSetBitFieldNb (NBPtr, BFCalOnce, 0);
  MemNSetBitFieldNb (NBPtr, RegCalRate, 0x83);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Waits for PHY calibrating to complete
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPendOnPhyCalibrateCompletionCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  // read CalBusy and discard result - this is needed to latch the
  // initial 'busy' status
  MemNGetBitFieldNb (NBPtr, RegCalBusy);

  // Wait until D18F2x9C_x20097 == 0.
  MemNPollBitFieldNb (NBPtr, RegCalBusy, 0, PCI_ACCESS_TIMEOUT, FALSE);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Set the rate for PHY calibrate
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNRateOfPhyCalibrateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNSetBitFieldNb (NBPtr, BFCalInitMode, 0);
  MemNSetBitFieldNb (NBPtr, RegCalRate, 0x03);
  MemNSetBitFieldNb (NBPtr, BFCalRun, 1);
  MemNSetBitFieldNb (NBPtr, RegCalRate, 0x13);
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function tri-state unused pads.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNTriStateUnusedPadCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CONST UINT8           PinType[4]  = {PSO_MEMCLK_DIS, PSO_CKE_TRI, PSO_ODT_TRI, PSO_CS_TRI};
  CONST UINT8           TabSize[4]  = {             4,           4,           4,          8};
  CONST UINT8           PadName[4]  = {       PAD_CLK,     PAD_CKE,     PAD_ODT,     PAD_CS};
  UINT8  *TabPtr;
  UINT8  i;
  UINT8  k;
  UINT8  Value;
  UINT8  PadNumber;
  BOOLEAN MemoryAllClocks;
  BOOLEAN MemoryAllCke;
  BOOLEAN MemoryAllCs;
  MEM_PARAMETER_STRUCT *RefPtr;

  TabPtr = NULL;
  RefPtr = NBPtr->MemPtr->ParameterListPtr;

  //===================================================================
  // Tristate DATA[8] if ECC is not supported
  //===================================================================
  if (MemNGetBitFieldNb (NBPtr, BFDimmEccEn) == 0) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tTri-state ECC Pad\n");
    MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ECC_BYTE, RegDataTxImpedance), 0);
    MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS, ECC_BYTE, RegDataTxImpedance), 0);
  }

  MemoryAllClocks = RefPtr->MemoryAllClocksOn;
  IDS_OPTION_HOOK (IDS_ALL_MEMORY_CLOCK, &MemoryAllClocks, &(NBPtr->MemPtr->StdHeader));
  MemoryAllCke = FALSE;
  IDS_OPTION_HOOK (IDS_ALL_MEMORY_CKE, &MemoryAllCke, &(NBPtr->MemPtr->StdHeader));
  MemoryAllCs = FALSE;
  IDS_OPTION_HOOK (IDS_ALL_MEMORY_CS, &MemoryAllCs, &(NBPtr->MemPtr->StdHeader));

  //===================================================================
  // Tristate unused MEMCLK, CKE, ODT and CS to save power
  //===================================================================
  //
  for (k = 0; k < GET_SIZE_OF (PinType); k++) {
    if (NBPtr->IsSupported[CheckFindPSOverideWithSocket]) {
      TabPtr = FindPSOverrideEntry (RefPtr->PlatformMemoryConfiguration, PinType[k], NBPtr->MCTPtr->SocketId, MemNGetSocketRelativeChannelNb (NBPtr, NBPtr->Dct, 0), 0,
                                    &(NBPtr->MCTPtr->LogicalCpuid), &(NBPtr->MemPtr->StdHeader));
    }

    if (TabPtr != NULL) {
      Value = 0;
      for (i = 0; i < TabSize[k]; i++) {
        if ((NBPtr->DCTPtr->Timings.CsPresent & TabPtr[i]) == 0) {
          Value |= (UINT8) (1 << i);
        }
      }

      // CAD/Pad numbers need tri-state
      while (Value != 0) {
        PadNumber = (UINT8)LowBitSet32 (Value);
        Value &= ~ (1 << PadNumber);

        if (PadName[k] == PAD_CLK) {
          if (!MemoryAllClocks) {
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tTri-state MEMCLK %d\n", PadNumber);
            MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCadTxImpedance), 0);
            MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCalTxImpedance), 0);
          }
        } else if (PadName[k] == PAD_CKE) {
          if (!MemoryAllCke) {
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tTri-state CKE %d\n", PadNumber);

            MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCadTxImpedance), 0);
            MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCalTxImpedance), 0);
          }
        } else if (PadName[k] == PAD_CS) {
          if (!MemoryAllCs) {
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tTri-state CS %d\n", PadNumber);

            MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCadTxImpedance), 0);
            MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCalTxImpedance), 0);
          }
        } else {
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tTri-state %s %d\n", ((PadName[k] == PAD_ODT) ? "MEMODT"  : "UnKnown"), PadNumber);

          MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCadTxImpedance), 0);
          MemNSetBitFieldNb (NBPtr, PER_CAD_PAD (PadName[k], PadNumber, RegCalTxImpedance), 0);
        }
      }
    }
  }
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Determine slow OPN mode is true if any valid NB-Pstates not tied
 *     to M1 has NCLK=800MHZ/M0=667MHZ or NCLK=800MHZ/M0=1333MHZ
 *
 *     @param[in,out]   *NBPtr    - Pointer to the MEM_NB_BLOCK
 *
 *     @return         TRUE  - slow_OPN mode, otherwise False
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
STATIC
MemNSlowOpnModeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8  NbPs;
  UINT32 NbClkFreqMhz;
  UINT16 Speed;

  for (NbPs = 0; NbPs < 4; NbPs++) {
    if (MemNGetBitFieldNb (NBPtr, BFMemPstate0 + NbPs) != 1) {
      NbClkFreqMhz = MemNGetNbClkFreqByPstateUnb (NBPtr, NbPs);
      Speed = NBPtr->DCTPtr->Timings.TargetSpeed;
      if ((NbClkFreqMhz == 800) && ((Speed == DDR667_FREQUENCY) || (Speed == DDR1333_FREQUENCY))) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets or set DQS timing during training.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   TrnDly - type of delay to be set
 *     @param[in]   DrbnVar - encoding of Dimm-Rank-Byte-Nibble to be accessed
 *                  (use either DIMM_BYTE_ACCESS(dimm,byte) or CS_NBBL_ACCESS(cs,nibble) to use this encoding
 *     @param[in]   Field - Value to be programmed
 *     @param[in]   IsSet - Indicates if the function will set or get
 *
 *     @return      value read, if the function is used as a "get"
 */

UINT32
MemNcmnGetSetTrainDlyCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 IsSet,
  IN       TRN_DLY_TYPE TrnDly,
  IN       DRBN DrbnVar,
  IN       UINT16 Field
  )
{
  UINT32 Value;
  UINT8 Dimm;
  UINT8 Rank;
  UINT8 Byte;
  UINT8 Nibble;
  BIT_FIELD_NAME BitField;

  BitField = 0;
  Dimm = DRBN_DIMM (DrbnVar);
  Rank = DRBN_RANK (DrbnVar);
  Byte = DRBN_BYTE (DrbnVar);
  Nibble = DRBN_NBBL (DrbnVar);

  ASSERT (Dimm < (NBPtr->CsPerChannel / NBPtr->CsPerDelay));
  ASSERT (Byte <= ECC_DLY);
  if ((Byte == ECC_DLY) && (!NBPtr->MCTPtr->Status[SbEccDimms] || !NBPtr->IsSupported[EccByteTraining])) {
    // When ECC is not enabled
    if (IsSet) {
      // On write, ignore
      return 0;
    } else {
      // On read, redirect to byte 0 to correct fence averaging
      Byte = 0;
    }
  }

  switch (TrnDly) {
  case AccessRcvEnDly:
    BitField = PER_DATA_BYTE (PAD_DQS, Byte, RegDataRxDly);
    break;
  case AccessWrDqsDly:
    BitField = PER_DATA_BYTE (PAD_DQS, Byte, RegDataTxDly);
    break;
  case AccessWrDatDly:
    BitField = PER_DATA_BYTE (((Nibble == 0) ? PAD_DQ_L : PAD_DQ_H), Byte, RegDataTxDly);
    break;
  case AccessRdDqsDly:
    BitField = PER_DATA_BYTE (((Nibble == 0) ? PAD_DQ_L : PAD_DQ_H), Byte, RegDataRxDly);
    break;
  case AccessRdDqs2dDly:
    BitField = PER_DATA_BYTE (((Nibble == 0) ? PAD_DQ_L : PAD_DQ_H), Byte, RegDataRxDly);
    break;
  case AccessWrDat2dDly:
    BitField = PER_DATA_BYTE (((Nibble == 0) ? PAD_DQ_L : PAD_DQ_H), Byte, RegDataTxDly);
    break;
  default:
    IDS_ERROR_TRAP;
  }
  BitField = PER_DIMM (Dimm, BitField);
  Value = MemNGetBitFieldNb (NBPtr, BitField);

  if (IsSet) {
    MemNSetBitFieldNb (NBPtr, BitField, Field);
  }
  return Value;
}


