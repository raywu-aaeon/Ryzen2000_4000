/* $NoKeywords:$ */
/**
 * @file
 *
 * mndctD4cz.c
 *
 * Northbridge DCT support for CZ with DDR4
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 325428 $ @e \$Date: 2015-08-27 20:08:24 +0800 (Thu, 27 Aug 2015) $
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


#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mp.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "mncz.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mftds.h"
#include "merrhdl.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNDCTD4CZ_FILECODE

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
///< DQ Mapping Register Fields
typedef struct _DQ_MAPPING_REGISTER {
  UINT8 Byte0; ///< Byte0 value
  UINT8 Byte1; ///< Byte1 value
  UINT8 Byte2; ///< Byte2 value
  UINT8 Byte3; ///< Byte3 value
  UINT8 Byte4; ///< Byte4 value
} DQ_MAPPING_REGISTER;

typedef struct _D4_TCWL_ENTRY {
  UINT16 Speed;
  UINT8 Tcwl;
} D4_TCWL_ENTRY;

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function uses calculated values from DCT.Timings structure to
 *      program its registers for CZ
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramCycTimingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CONST CTENTRY TmgAdjTab[] = {
    // BitField,      Min, Max, Bias, Ratio_x2
    {  BFTcl,           5,  19,    0,    2   },
    {  BFTrcd,          5,  26,    0,    2   },
    {  BFTrp,           5,  26,    0,    2   },
    {  BFTrtp,          4,  14,    0,    2   },
    {  BFTras,          8,  54,    0,    2   },
    {  BFTrc,          10,  78,    0,    2   },
    {  BFTwr,           5,  26,    0,    2   },
    {  BFTrrd,          1,  13,    0,    2   },
    {  BFTwtr,          2,  14,    0,    2   },
    {  BFFourActWindow, 6,  50,    0,    2   },
    {  BFTrrdL,         1,  13,    0,    2   },
    {  BFTwtrL,         2,  14,    0,    2   },
  };

  CONST D4_TCWL_ENTRY DDR4TCWLTable[] = {
    { DDR1333_FREQUENCY, 9 },
    { DDR1600_FREQUENCY, 9 },
    { DDR1866_FREQUENCY, 10 },
    { DDR2133_FREQUENCY, 11 },
    { DDR2400_FREQUENCY, 12 },
  };

  DCT_STRUCT *DCTPtr;
  UINT8  *MiniMaxTmg;
  UINT16 *MiniMaxTrfc;
  UINT16 TrfcMax;
  UINT8  Value8;
  UINT8  ValFAW;
  UINT8  ValTrrd;
  UINT8  j;
  UINT8  i;
  UINT8  Tcwl;
  UINT8 RdOdtTrnOnDly;
  BIT_FIELD_NAME BitField;
  MEM_PARAMETER_STRUCT *RefPtr;
  UINT32 ValTwtr;
  UINT32 ValTwtrL;
  UINT32 tDllk;

  DCTPtr = NBPtr->DCTPtr;
  RefPtr = NBPtr->RefPtr;

  ValFAW = 0;
  ValTrrd = 0;
  TrfcMax = 0;
  ValTwtr = 0;
  ValTwtrL = 0;

  //======================================================================
  // Program DRAM Timing values
  //======================================================================
  //
  MiniMaxTmg = &DCTPtr->Timings.CasL;
  for (j = 0; j < GET_SIZE_OF (TmgAdjTab); j++) {
    BitField = TmgAdjTab[j].BitField;

    if (BitField == BFTrp) {
      if (NBPtr->IsSupported[AdjustTrp]) {
        MiniMaxTmg[j] ++;
        if (MiniMaxTmg[j] < 5) {
          MiniMaxTmg[j] = 5;
        }
      }
    }

    if (MiniMaxTmg[j] < TmgAdjTab[j].Min) {
      MiniMaxTmg[j] = TmgAdjTab[j].Min;
    } else if (MiniMaxTmg[j] > TmgAdjTab[j].Max) {
      MiniMaxTmg[j] = TmgAdjTab[j].Max;
    }

    Value8 = (UINT8) MiniMaxTmg[j];
    if (BitField == BFTwtr) {
      //
      // Twtr
      //
      ValTwtr = Value8;
    } else if (BitField == BFTwtrL) {
      //
      // TwtrL
      //
      ValTwtrL = Value8;
    } else if (BitField == BFTrrd) {
      //
      // Trrd
      //
      ValTrrd = Value8;
    } else if (BitField == BFFourActWindow) {
      //
      // tFAW
      //
      ValFAW = Value8;
    }
    MemNSetBitFieldNb (NBPtr, BitField, Value8);
  }
  //
  // UBTS-5557897
  // Twtr = MAX(TwtrL, Twtr)
  //
  if (ValTwtr > ValTwtrL) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\tIncreasing TwtrL to match Twtr\n");
    MemNSetBitFieldNb (NBPtr, BFTwtrL, ValTwtr);
  } else if ( ValTwtrL > ValTwtr) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\tIncreasing Twtr to match TwtrL\n");
    MemNSetBitFieldNb (NBPtr, BFTwtr, ValTwtrL);
  }

  MiniMaxTrfc = &DCTPtr->Timings.Trfc0;
  for (j = 0; j < 4; j++) {
    if ((NBPtr->DCTPtr->Timings.DctDimmValid & (1 << j)) != 0) {
      if (MiniMaxTrfc[j] > TrfcMax) {
        TrfcMax = MiniMaxTrfc[j];
      }
      MemNSetBitFieldNb (NBPtr, BFTrfc0 + j, MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, MiniMaxTrfc[j]));
    }
  }
  //
  // Program tCWL
  //
  Tcwl = 0;
  for (i = 0; i < GET_SIZE_OF (DDR4TCWLTable); i++) {
    if (DDR4TCWLTable[i].Speed == DCTPtr->Timings.Speed) {
      Tcwl = DDR4TCWLTable[i].Tcwl;
      break;
    }
  }
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tTcwl = %d\n",Tcwl);
  ASSERT (i < GET_SIZE_OF (DDR4TCWLTable));
  ASSERT (Tcwl > 0);
  MemNSetBitFieldNb (NBPtr, BFTcwl, Tcwl);

  if (RefPtr->DramDoubleRefreshRateEn) {
    MemNSetBitFieldNb (NBPtr, BFTref, MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, 3900));      // 3.9 us
    MemNSetBitFieldNb (NBPtr, BFODTSDoubleRefreshRate, 0);
  } else {
    MemNSetBitFieldNb (NBPtr, BFTref, MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, 7800));      // 7.8 us
    MemNSetBitFieldNb (NBPtr, BFODTSDoubleRefreshRate, 1);
  }

  MemNSetBitFieldNb (NBPtr, BFTrcpage, NBPtr->DCTPtr->Timings.Trcpage);
  //
  // Txs = SelfRefreshAbort ? tXS_Abort : tXS
  //                          tXS_Abort = tRFC4(min) + 10ns
  //                          tXS = tRFC(min) + 10ns
  //
  MemNSetBitFieldNb (NBPtr, BFTxs, NBPtr->SelfRefreshAbort ?
                     MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, DCTPtr->Timings.Trfc4 + 10) :
                     MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, TrfcMax + 10));

  RdOdtTrnOnDly = (DCTPtr->Timings.CasL > Tcwl) ? (DCTPtr->Timings.CasL - Tcwl) : 0;
  MemNSetBitFieldNb (NBPtr, BFRdOdtTrnOnDly, RdOdtTrnOnDly);
  NBPtr->FamilySpecificHook[ProgOdtControl] (NBPtr, NULL);
  //
  // Program Tstag
  //
  // Tstag = BIOS: MAX(D18F2x204_dct[1:0]_mp[1:0][Trrd], CEIL(D18F2x204_dct[1:0]_mp[1:0][FourActWindow]/4))
  if (NBPtr->MemPstate == 0) {
    for (j = 0; j < 4; j++) {
      MemNSetBitFieldNb (NBPtr, BFTstag0 + j, MAX (ValTrrd,  (ValFAW + 3) / 4));
    }
  }
  //
  // Program Tmod = MAX (15nS, 24nCK)
  //
  MemNSetBitFieldNb (NBPtr, BFTmod, MAX (24, MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, 15)));
  //
  // Program Tvrefdq = 150ns
  //
  MemNSetBitFieldNb (NBPtr, BFTvrefdq, MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, 150));
  //
  // Program Tzqcs and Tzqoper
  //
  // Tzqcs = 128nCK
  MemNSetBitFieldNb (NBPtr, BFTzqcs, (128 / 16));
  // Tzqoper = 512 nCK
  MemNSetBitFieldNb (NBPtr, BFTzqoper, (512 / 32));
  //
  // Tdllk
  //
  tDllk = (( NBPtr->DCTPtr->Timings.Speed <= DDR1866_FREQUENCY ) ? 597 :    // Data rate <= 1866
          (( NBPtr->DCTPtr->Timings.Speed <= DDR2400_FREQUENCY ) ? 768 :    // 1866 < Data rate <= 2400
                                                                  1024 )) ; // Data rate > 2400
  MemNSetBitFieldNb (NBPtr, BFTdllk, tDllk);

  // Program power management timing
  MemNDramPowerMngTimingCZ (NBPtr);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs Mem Pstate registers for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       MemPstate - Mem Pstate
 *
 */

VOID
MemNProgramMemPstateRegD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 MemPstate
  )
{
  UINT8 TxpVal;

  if (MemPstate == 0) {
    MemNSetBitFieldNb (NBPtr, BFMemClkFreq, MEMCLK_FREQ_TO_ID (NBPtr->DCTPtr->Timings.Speed));
    MemNSetBitFieldNb (NBPtr, BFMemClkFreqVal, 1);
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMPState 0 Frequency = %d MHz\n", (UINT16) MEMCLK_ID_TO_FREQ (MemNGetBitFieldNb (NBPtr, BFMemClkFreq)));
  } else {
    MemNSetBitFieldNb (NBPtr, BFM1MemClkFreq, MEMCLK_FREQ_TO_ID (NBPtr->M1Speed));
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMPState 1 Frequency = %d MHz\n", (UINT16) MEMCLK_ID_TO_FREQ (MemNGetBitFieldNb (NBPtr, BFM1MemClkFreq)));
  }

  //
  // Non-SPD Timings
  //
  MemNSetBitFieldNb (NBPtr, BFTrwtWB, 0x1C);
  MemNSetBitFieldNb (NBPtr, BFTrwtTO, 0x1B);
  MemNSetBitFieldNb (NBPtr, BFTwrrd, 0xB );

  MemNSetBitFieldNb (NBPtr, BFTrdrdBan, 0x2);
  MemNSetBitFieldNb (NBPtr, BFTrdrdSdSc, 0x1);
  MemNSetBitFieldNb (NBPtr, BFTrdrdSdScL, 0x1);
  MemNSetBitFieldNb (NBPtr, BFTrdrdSdDc, 0xB);
  MemNSetBitFieldNb (NBPtr, BFTrdrdDd, 0xB);

  MemNSetBitFieldNb (NBPtr, BFTwrwrSdSc, 0x1);
  MemNSetBitFieldNb (NBPtr, BFTwrwrSdScL, 0x1);
  MemNSetBitFieldNb (NBPtr, BFTwrwrSdDc, 0xB);
  MemNSetBitFieldNb (NBPtr, BFTwrwrDd, 0xB);

  if (NBPtr->ChannelPtr->DimmSRPresent != 0 && NBPtr->ChannelPtr->DimmDrPresent != 0 &&
    (NBPtr->DCTPtr->Timings.Speed == DDR1600_FREQUENCY || NBPtr->DCTPtr->Timings.Speed == DDR1866_FREQUENCY)) {
    NBPtr->DCTPtr->Timings.RdOdtOnDuration = DEFAULT_RD_ODT_CZ + 1;
    NBPtr->DCTPtr->Timings.WrOdtOnDuration = DEFAULT_WR_ODT_CZ + 1;
  } else {
    NBPtr->DCTPtr->Timings.RdOdtOnDuration = DEFAULT_RD_ODT_CZ;
    NBPtr->DCTPtr->Timings.WrOdtOnDuration = DEFAULT_WR_ODT_CZ;
  }
  MemNSetBitFieldNb (NBPtr, BFWrOdtOnDuration, NBPtr->DCTPtr->Timings.WrOdtOnDuration);
  MemNSetBitFieldNb (NBPtr, BFRdOdtOnDuration, NBPtr->DCTPtr->Timings.RdOdtOnDuration);
  MemNSetBitFieldNb (NBPtr, BFWrOdtTrnOnDly, DEFAULT_RD_ODT_TRNONDLY_CZ);

  MemNSetBitFieldNb (NBPtr, BFTmrd, 8);
  MemNSetBitFieldNb (NBPtr, BFEffArbDis, 0);
  MemNSetBitFieldNb (NBPtr, BFAggrPDDelay, 0x20);
  //
  // Txp = MAX (4nCK, 6nS)
  //
  TxpVal = MAX ( 4, (UINT8) (0xFF & (MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, 6))));
  MemNSetBitFieldNb (NBPtr, BFTxp, TxpVal);

  if (NBPtr->RefPtr->EnablePowerDown) {
    MemNSetBitFieldNb (NBPtr, BFPchgPDEnDelay, 0x20);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the memory controller for training for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNConfigureDctForTrainingD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNSetBitFieldNb (NBPtr, BFGsyncDis, 0x0);
  MemNSetBitFieldNb (NBPtr, BFAddrCmdTriEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFDisAutoRefresh, 0x1);
  MemNSetBitFieldNb (NBPtr, BFForceAutoPchg, 0x0);
  MemNSetBitFieldNb (NBPtr, BFDynPageCloseEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFBankSwizzleMode, 0x0);
  MemNSetBitFieldNb (NBPtr, BFDcqBypassMax, 0x0);
  MemNSetBitFieldNb (NBPtr, BFPowerDownEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFZqcsInterval, 0x0);
  MemNSetBitFieldNb (NBPtr, BFCmdThrottleMode, 0x0);
  MemNSetBitFieldNb (NBPtr, BFODTSEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFBwCapEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFBankSwap, 0x0);
  MemNSetBitFieldNb (NBPtr, BFTraceModeEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFDramScrub, 0);
  MemNSetBitFieldNb (NBPtr, BFScrubReDirEn, 0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the memory controller for mission mode for DDR4
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNConfigureDctNormalD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNSetBitFieldNb (NBPtr, BFAddrCmdTriEn, 0x1);
  MemNSetBitFieldNb (NBPtr, BFDisAutoRefresh, 0x0);
  MemNSetBitFieldNb (NBPtr, BFForceAutoPchg, 0x0);
  MemNSetBitFieldNb (NBPtr, BFDynPageCloseEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFDcqBypassMax, 0x1F);
  MemNSetBitFieldNb (NBPtr, BFZqcsInterval, 0x2);
  MemNSetBitFieldNb (NBPtr, BFTraceModeEn, 0x0);
  MemNSetBitFieldNb (NBPtr, BFAggrPDEn, 1);
  MemNSetBitFieldNb (NBPtr, BFDataScrambleEn, 1);

  //
  // Power Down Enable
  //
  if (NBPtr->RefPtr->EnablePowerDown) {
    MemNSetBitFieldNb (NBPtr, BFPowerDownEn, 0x1);
  }

  IEM_SKIP_CODE (IEM_LATE_DCT_CONFIG) {
    MemNSetBitFieldNb (NBPtr, BFBankSwap, 0x1);
    MemNSetBitFieldNb (NBPtr, BFBankSwapAddr8En, 0x1);
    MemNSetBitFieldNb (NBPtr, BFBankGroupSwap, 0x0);

    if (NBPtr->RefPtr->EnableBankSwizzle) {
      MemNSetBitFieldNb (NBPtr, BFBankSwizzleMode, 1);
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function returns the High and Low Bit Masks to be swapped
 *      to enable CS interleaving for CZ with DDR4
 *
 *     @param[in,out]  *NBPtr      - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  BankAddrMap - Bank Address Mapping Nibble for the current CS
 *     @param[in,out]  *LowBit     - Pointer to Low bit
 *     @param[in,out]  *HiBit      - Pointer to High bit
 *
 */
VOID
MemNGetCSIntLvAddrD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 BankAddrMap,
  OUT   UINT8 *LowBit,
  OUT   UINT8 *HiBit
  )
{
  //                                               DIMM Address Map
  //                                0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
  CONST UINT8 AddrSwapHi[]  = { 0, 30, 31, 31, 32, 32, 33, 33, 34,  0, 35 };
  CONST UINT8 AddrSwapLo1[] = { 0, 16, 17, 16, 17, 16, 17, 16, 17,  0, 17 };
  CONST UINT8 AddrSwapLo2[] = { 0, 11, 12, 11, 12, 11, 12, 11, 12,  0, 12 };
  CONST UINT8 AddrSwapLo3[] = { 0, 12, 13, 12, 13, 12, 13, 12, 13,  0, 13 };
  UINT8 DctSelIntLvAddr;
  UINT8 BankSwapAddr8En;

  ASSERT (BankAddrMap < GET_SIZE_OF (AddrSwapHi));
  ASSERT (BankAddrMap < GET_SIZE_OF (AddrSwapLo1));
  ASSERT (BankAddrMap < GET_SIZE_OF (AddrSwapLo2));
  ASSERT (BankAddrMap < GET_SIZE_OF (AddrSwapLo3));

  DctSelIntLvAddr = (UINT8) MemNGetBitFieldNb (NBPtr, BFDctSelIntLvAddr);
  BankSwapAddr8En = (UINT8) MemNGetBitFieldNb (NBPtr, BFBankSwapAddr8En);
  //
  // Select Apropriate Swap Table based on the configuration
  //
  *HiBit = AddrSwapHi[BankAddrMap];
  //
  // Select Low bit table based on Bank Address Swap Bits
  //
  if (MemNGetBitFieldNb (NBPtr, BFBankSwap) == 1) {
    if (((NBPtr->MCTPtr->LogicalCpuid.Revision & AMD_REV_F15_CZ_ALL) != 0 && NBPtr->MemPtr->ParameterListPtr->EnableBankSwapOnly != BANK_SWAP_ONLY_ENABLED) ||
        ((NBPtr->MCTPtr->LogicalCpuid.Revision & AMD_REV_F15_BR_ALL) != 0 && NBPtr->MemPtr->ParameterListPtr->EnableBankSwapOnly == BANK_SWAP_ONLY_DISABLED)) {
      if ((BankSwapAddr8En == 1) && (DctSelIntLvAddr == 4)) {
        *LowBit = AddrSwapLo2[BankAddrMap];
      } else {
        *LowBit = AddrSwapLo3[BankAddrMap];
      }
    } else {
      *LowBit = AddrSwapLo1[BankAddrMap];
    }
  } else {
    *LowBit = AddrSwapLo1[BankAddrMap];
  }
  ASSERT (*HiBit != 0);
  ASSERT (*LowBit != 0);
  //
  // Convert Normalized Physical Address Bits from Table to register bit field
  // D18F2x[5C:40]_dct[1:0] [DRAM CS Base Address] and D18F2x[6C:60]_dct[1:0] [DRAM CS Mask]
  //
  // Address Bits [39:27] = Bit field [31:19]
  // Address Bits [21:11] = Bit field [15:5]
  //
  *(UINT8 *) LowBit -= (11 - 5);
  *(UINT8 *) HiBit -= (27 - 19);
  return;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs DDR4 turnaround timings for each DCT
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramTurnaroundTimingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
  UINT32 TrdrdSdSc;
  UINT32 TrdrdSdScL;
  UINT32 TrdrdSdDc;
  UINT32 TrdrdDd;
  UINT32 TrdrdBan;
  UINT32 TwrwrSdSc;
  UINT32 TwrwrSdScL;
  UINT32 TwrwrSdDc;
  UINT32 TwrwrDd;
  UINT32 Twrrd;
  UINT32 TrwtTO;
  UINT32 TrwtWB;
  UINT8  tCCD_L;
  UINT32 LD;
  UINT32 ROD;
  UINT32 WOD;

  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ*)NBPtr->PsPtr->PmuSramMsgBlockPtr;
  ASSERT (PmuSramMsgBlockPtr != NULL);

  // DDR Turnaround Parameters
  LD = MemNGetBitFieldNb (NBPtr, BFTcl) - MemNGetBitFieldNb (NBPtr, BFTcwl);
  ROD = MAX (0, MemNGetBitFieldNb (NBPtr, BFRdOdtOnDuration) - 6) + MAX (0, MemNGetBitFieldNb (NBPtr, BFRdOdtTrnOnDly) - LD);
  WOD = MAX (0, MemNGetBitFieldNb (NBPtr, BFWrOdtOnDuration) - 6);

  tCCD_L = NBPtr->DCTPtr->Timings.TccdL;
  TrdrdSdSc  = 1;
  TrdrdSdScL = tCCD_L - 3;
  TwrwrSdSc = 1;
  TwrwrSdScL = tCCD_L - 3;
  TrdrdBan = 1;
  if (NBPtr->MemPstate == 0) {
    TrdrdSdDc = PmuSramMsgBlockPtr->M0_CD_R_R_SD;
    TrdrdDd = MAX (PmuSramMsgBlockPtr->M0_CD_R_R, ROD + 3);
    TwrwrSdDc = MAX (PmuSramMsgBlockPtr->M0_CD_W_W_SD, WOD + 3);
    TwrwrDd = MAX (PmuSramMsgBlockPtr->M0_CD_W_W, WOD + 3);
    Twrrd = MAX (PmuSramMsgBlockPtr->M0_CD_W_R, WOD + 3 - MAX (0, LD));
    TrwtTO = MAX (PmuSramMsgBlockPtr->M0_CD_R_W, ROD + 3 + LD);
  } else {
    TrdrdSdDc = PmuSramMsgBlockPtr->Annex.D4u.M1_CD_R_R_SD;
    TrdrdDd = MAX (PmuSramMsgBlockPtr->Annex.D4u.M1_CD_R_R, ROD + 3);
    TwrwrSdDc = MAX (PmuSramMsgBlockPtr->Annex.D4u.M1_CD_W_W_SD, WOD + 3);
    TwrwrDd = MAX (PmuSramMsgBlockPtr->Annex.D4u.M1_CD_W_W, WOD + 3);
    Twrrd = MAX (PmuSramMsgBlockPtr->Annex.D4u.M1_CD_W_R, WOD + 3 - MAX (0, LD));
    TrwtTO = MAX (PmuSramMsgBlockPtr->Annex.D4u.M1_CD_R_W, ROD + 3 + LD);
  }
  TrwtWB = TrwtTO + 1;

  MemNSetBitFieldNb (NBPtr, BFTrdrdSdSc, TrdrdSdSc);
  MemNSetBitFieldNb (NBPtr, BFTrdrdSdScL, TrdrdSdScL);
  MemNSetBitFieldNb (NBPtr, BFTrdrdSdDc, TrdrdSdDc);
  MemNSetBitFieldNb (NBPtr, BFTrdrdDd, TrdrdDd);
  MemNSetBitFieldNb (NBPtr, BFTrdrdBan, TrdrdBan);
  MemNSetBitFieldNb (NBPtr, BFTwrwrSdSc, TwrwrSdSc);
  MemNSetBitFieldNb (NBPtr, BFTwrwrSdScL, TwrwrSdScL);
  MemNSetBitFieldNb (NBPtr, BFTwrwrSdDc, TwrwrSdDc);
  MemNSetBitFieldNb (NBPtr, BFTwrwrDd, TwrwrDd);
  MemNSetBitFieldNb (NBPtr, BFTwrrd, Twrrd);
  MemNSetBitFieldNb (NBPtr, BFTrwtTO, TrwtTO);
  MemNSetBitFieldNb (NBPtr, BFTrwtWB, TrwtWB);

  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tTurnaround Timings\n");
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tTrdrdSdSc  : %x\t\t TwrwrSdSc  : %x\n", TrdrdSdSc, TwrwrSdSc);
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tTrdrdSdScL : %x\t\t TwrwrSdScL : %x\n", TrdrdSdScL, TwrwrSdScL);
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tTrdrdDd    : %x\t\t TwrwrDd    : %x\n", TrdrdDd, TwrwrDd);
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tTrdrdBan   : %x\t\t Twrrd      : %x\n", TrdrdBan, Twrrd);
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tTrwtTO     : %x\t\t TrwtWB     : %x\n\n", TrwtTO, TrwtWB);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Mode Register initialization for DDR4.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNModeRegisterInitializationD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 Mr0;
  UINT32 Mr1;
  UINT32 Mr2;
  UINT32 Mr3;
  UINT32 Mr4;
  UINT32 Mr5;
  UINT32 Mr6;

  Mr0 = MemNCalcD4MR0 (NBPtr);
  Mr1 = MemNCalcD4MR1 (NBPtr, 0);
  Mr2 = MemNCalcD4MR2 (NBPtr, 0);
  Mr3 = MemNCalcD4MR3 (NBPtr);
  Mr4 = MemNCalcD4MR4 (NBPtr);
  Mr5 = MemNCalcD4MR5 (NBPtr, 0);
  Mr6 = MemNCalcD4MR6 (NBPtr);

  MemNSetBitFieldNb (NBPtr, BFMxMr0, Mr0);
  MemNSetBitFieldNb (NBPtr, BFMxMr1, Mr1);
  MemNSetBitFieldNb (NBPtr, BFMxMr2, Mr2);
  MemNSetBitFieldNb (NBPtr, BFMxMr4, Mr4);
  MemNSetBitFieldNb (NBPtr, BFMxMr5, Mr5);
  MemNSetBitFieldNb (NBPtr, BFMxMr6, Mr6);
  //
  // Enable MxMr0-6
  //
  MemNSetBitFieldNb (NBPtr, BFMxMrsEn, 0x7F);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function uses calculated values from DCT.Timings structure to
 *      program its registers for CZ
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramDqMappingsD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CONST DQ_MAPPING_REGISTER DqMappings[] = {
    //   5:0      11:6      17:12    23:18      29:24
    {   DQ_0_3,   DQ_4_7,  DQ_8_11, DQ_12_15, DQ_16_19 },
    { DQ_20_23, DQ_24_27, DQ_28_31, DQ_32_35, DQ_36_39 },
    { DQ_40_43, DQ_44_47, DQ_48_51, DQ_52_55, DQ_56_59 },
    { DQ_60_63, DQ_64_67, DQ_68_71,     0xFF,     0xFF }
  };
  CONST BIT_FIELD_NAME DQMapBitfieldTbl[] = {
    BFDQMappingDimm0Reg0, BFDQMappingDimm0Reg1, BFDQMappingDimm0Reg2, BFDQMappingDimm0Reg3,
    BFDQMappingDimm1Reg0, BFDQMappingDimm1Reg1, BFDQMappingDimm1Reg2, BFDQMappingDimm1Reg3,
    BFDQMappingDimm2Reg0, BFDQMappingDimm2Reg1, BFDQMappingDimm2Reg2, BFDQMappingDimm2Reg3,
    BFDQMappingDimm3Reg0, BFDQMappingDimm3Reg1, BFDQMappingDimm3Reg2, BFDQMappingDimm3Reg3
  };
  UINT8 *SpdBufferPtr;
  UINT8 Dimm;
  UINT8  Reg;
  UINT32  DqMapVal;
  BIT_FIELD_NAME BitField;
  //
  // Program DQ Mapping Bitfield for each valid DIMM
  //
  for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDimm %d\n", Dimm);
    if ((NBPtr->ChannelPtr->ChDimmValid & ((UINT8)1 << Dimm)) != 0) {
      NBPtr->TechPtr->GetDimmSpdBuffer (NBPtr->TechPtr, &SpdBufferPtr, Dimm);
      for (Reg = 0; Reg < 4; Reg++) {
        //
        /// @todo: DDR4 Need to Check for Package Rank Mapping(Not supported on CZ)
        ///   and Disable Write CRC if DIMMs use it.
        //
        BitField = DQMapBitfieldTbl[Dimm * 4] + Reg;
        DqMapVal = SpdBufferPtr[MemTGetDQMappingByte (DqMappings[Reg].Byte0)] & 0x3F;
        DqMapVal |= (SpdBufferPtr[MemTGetDQMappingByte (DqMappings[Reg].Byte1)] & 0x3F) << 6;
        DqMapVal |= (SpdBufferPtr[MemTGetDQMappingByte (DqMappings[Reg].Byte2)] & 0x3F) << 12;
        if (Reg < 3) {
          DqMapVal |= (SpdBufferPtr[MemTGetDQMappingByte (DqMappings[Reg].Byte3)] & 0x3F) << 18;
          DqMapVal |= (SpdBufferPtr[MemTGetDQMappingByte (DqMappings[Reg].Byte4)] & 0x3F) << 24;
        }
        MemNSetBitFieldNb (NBPtr, BitField, DqMapVal);
        IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDQ Mapping Reg 1%x%x: %08x\n", (Dimm + 4), (Reg * 4), DqMapVal);
      }; // Reg
    }; // DimmValid
  }; // Dimm
}
