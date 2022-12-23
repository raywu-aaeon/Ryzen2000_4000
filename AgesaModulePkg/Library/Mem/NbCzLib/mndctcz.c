/* $NoKeywords:$ */
/**
 * @file
 *
 * mndctcz.c
 *
 * Northbridge DCT support for CZ
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/FabricPstatesLib.h"
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
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNDCTCZ_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define UNUSED_CLK 4
#define MAX_RD_DQS_DLY 0x1F

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */
typedef struct {
  UINT32 BitField; ///< Bit field name of the timing
  UINT8 Min;               ///< Minimum value for timing
  UINT8 Max;               ///< Maximum value for timing
} SPD_TMG;

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

extern MEM_PSC_FLOW MemPGetODTPattern;

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function disables the DCT and mem clock for CZ
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNDisableDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDisable DCT %d\n", NBPtr->Dct);

  // Clear BFDphyMemPsSelEn prior PHY accesses
  MemNSetBitFieldNb (NBPtr, BFDphyMemPsSelEn, 0);

  // Tristate Vref on unused channel
  MemNSetBitFieldNb (NBPtr, BFGlobalVrefInSel, 2);

  // Tri-state drivers
  MemNSetBitFieldNb (NBPtr, RegTxImpedance, 0);

  // Program D18F2x9C_x00FA_F04A_dct[3:03:03:0] = 0080h.  Abyte/abit bc. Pwrdn Rcvrs used only in loopback mode
  MemNSetBitFieldNb (NBPtr, RegFAF04A, 0x80);

  // Program D18F2x9C_x00[F,8:0]1_[F,B:0]04E_dct[1:0]= 0000h
  MemNSetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ, ALL_BYTES, RegDctPhyD0091F04E), 0x0000);

  // Phy LP2 state
  MemNSetBitFieldNb (NBPtr, RegPwrStateCmd, 4);

  // Ensure that D18F2x78_dct[1:0][ChanVal] = 0.
  MemNSetBitFieldNb (NBPtr, BFChanVal, 0);

  //Disable powergating the ss channel when the Dcc is powergated
  MemNSetBitFieldNb (NBPtr, BFDisDllShutdownSR, 1);

  // Disable DCT
  MemNSetBitFieldNb (NBPtr, BFDisDramInterface, 1);

  // Clear ZqToCsMap as it defaults to 0000_AA55h
  MemNSetBitFieldNb (NBPtr, RegZqToCsMap, 0);

  NBPtr->DCTPtr->Timings.DctMemSize = 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function programs dram power management timing related registers
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 *     @return    none
 * ----------------------------------------------------------------------------
 */
VOID
MemNDramPowerMngTimingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  STATIC CONST UINT8 Tcke[] = {3, 3, 3, 4, 4, 5, 6, 6, 2};
  UINT8 Tck;

  // These timings are based on DDR3 spec
  // Tcksrx BIOS: 0
  Tck = (UINT8) MAX (5, (MemUnsToMemClk (NBPtr->DCTPtr->Timings.Speed, 10)));
  MemNSetBitFieldNb (NBPtr, BFTcksrx, 0);

  // Tcksre = max(5 nCK, 10 ns)
  MemNSetBitFieldNb (NBPtr, BFTcksre, MIN (0x3F, MAX (Tck, 5)));

  // Tckesr BIOS: 2
  MemNSetBitFieldNb (NBPtr, BFTckesr, 2);

  // Tcpded : 1
  MemNSetBitFieldNb (NBPtr, BFTcpded, (MemNGetBitFieldNb (NBPtr, BFDramType) == DRAM_TYPE_DDR3_CZ
                                    && MemNGetBitFieldNb (NBPtr, BFUnBuffDimm) == 1 ? 2 : 4));
  // Tpd = tCKE(min)
  //                               tCKE(min)
  // DDR-667   7.5ns = 3nCk     max(3nCK, 7.5ns)   = 3nCK
  // DDR-800   7.5ns = 3nCk     max(3nCK, 7.5ns)   = 3nCK
  // DDR-1066  5.625ns = 3nCK   max(3nCK, 5.625ns) = 3nCK
  // DDR-1333  5.625ns = 4nCK   max(3nCK, 4nCK)    = 4nCK
  // DDR-1600  5ns = 4nCK       max(3nCK, 4nCK)    = 4nCK
  // DDR-1866  5ns = 5nCK       max(3nCK, 5nCK)    = 5nCK
  // DDR-2133  5ns = 6nCK       max(3nCK, 6nCK)    = 6nCK
  // DDR-2400  5ns = 6nCK       max(3nCK, 6nCK)    = 6nCK
  // Tpd = tCKE(min)
  MemNSetBitFieldNb (NBPtr, BFTpd, Tcke[(NBPtr->DCTPtr->Timings.Speed / 133) - 2]);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function programs evaluate the conditions to program CsMux
 *
 *
 *     @param[in]   DimmAddrMap   - DimmAddrMap
 *     @param[in]   RankDef       - RankDef
 *
 *     @return          TRUE - CsMux should be set
 *     @return          FALSE - CsMux should be reset
 */

BOOLEAN
STATIC
EvaluateCsMuxCZ (
  IN       UINT8   DimmAddrMap,
  IN       UINT8   RankDef
  )
{
  if ((DimmAddrMap == 7 || DimmAddrMap == 9) && (RankDef == 3)) {
    return TRUE;
  } else if ((DimmAddrMap == 0xA || DimmAddrMap == 0xB || DimmAddrMap == 0xC) &&
             (RankDef == 2 || RankDef == 3)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function programs the memory controller with configuration parameters
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - An Error value lower than AGESA_FATAL may have occurred
 *     @return          FALSE - An Error value greater than or equal to AGESA_FATAL may have occurred
 *     @return          NBPtr->MCTPtr->ErrCode - Contains detailed AGESA_STATUS value
 */

BOOLEAN
MemNAutoConfigCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 i;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  UINT32 PowerDownMode;
  UINT32 DramType;
  UINT8 NumDimmslots;
  UINT8 RankDef[3];
  UINT8 DimmAddrMap[3];
  UINT8 DataMaskMbType;
  UINT8 *DataMaskMbTypeOverride;

  MCTPtr = NBPtr->MCTPtr;
  DCTPtr = NBPtr->DCTPtr;

  DramType = MemNGetBitFieldNb (NBPtr, BFDramType);
  //
  //======================================================================
  // NB Config 1 Lo Register Value
  //======================================================================
  MemNSetBitFieldNb (NBPtr, BFDisDramScrub, 1);

  //
  //======================================================================
  // Build Dram Config Lo Register Value
  //======================================================================
  MemNSetBitFieldNb (NBPtr, BFUnBuffDimm, 1);
  MemNSetBitFieldNb (NBPtr, BFPendRefPaybackS3En, 1);
  MemNSetBitFieldNb (NBPtr, BFStagRefEn, 1);
  MemNSetBitFieldNb (NBPtr, BFIdleCycLimit, 8);

  // DimmEccEn
  if (NBPtr->RefPtr->EnableEccFeature && MCTPtr->Status[SbEccDimms]) {
    MemNSetBitFieldNb (NBPtr, BFDimmEccEn, 1);
  }

  // X4Dimm
  MemNSetBitFieldNb (NBPtr, BFX4Dimm, DCTPtr->Timings.Dimmx4Present);

  //
  //======================================================================
  // Build Dram Config Hi Register Value
  //======================================================================
  //
  PowerDownMode = 1;
  IDS_OPTION_HOOK (IDS_POWERDOWN_MODE, &PowerDownMode, &(NBPtr->MemPtr->StdHeader));
  MemNSetBitFieldNb (NBPtr, BFPowerDownMode, PowerDownMode);
  MemNSetBitFieldNb (NBPtr, BFOn3RdCasStallMode, 1);
  MemNSetBitFieldNb (NBPtr, BFDphyMemPsSelEn, 0);
  //
  //======================================================================
  // Build Dram MRS Register Value
  //======================================================================
  //
  MemNSetBitFieldNb (NBPtr, BFPchgPDModeSel, (DramType == DRAM_TYPE_DDR3_CZ) ? 1 : 0);
  MemNSetBitFieldNb (NBPtr, BFBurstCtrl, 1);

  //======================================================================
  // DRAM Controller Miscellaneous 2
  //======================================================================
  MemNSetBitFieldNb (NBPtr, BFPerRankTimingEn, 0);
  MemNSetBitFieldNb (NBPtr, BFFastSelfRefEntryDis, 0);
  MemNSetBitFieldNb (NBPtr, BFPrtlChPDEnhEn, 0);
  MemNSetBitFieldNb (NBPtr, BFPrtlChPDDynDly, 4);
  MemNSetBitFieldNb (NBPtr, BFPDPhyPSDis, 1);

  NumDimmslots = (UINT8) GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                                NBPtr->MCTPtr->SocketId,
                                                NBPtr->ChannelPtr->ChannelID);
  for (i = 0; i < 3; i ++) {
    RankDef[i] = (UINT8) MemNGetBitFieldNb (NBPtr, BFRankDef0 + i);
    DimmAddrMap[i] = (UINT8) ((MemNGetBitFieldNb (NBPtr, BFDramBankAddrReg) >> (i * 4)) & 0xF);
  }
  // BIOS Recommendations for D18F2xA8_dct[1:0][CsMux45]
  if (NumDimmslots == 1 || NumDimmslots == 2) {
    MemNSetBitFieldNb (NBPtr, BFCSMux45, EvaluateCsMuxCZ (DimmAddrMap[0], RankDef[0]) ? 1 : 0);
  } else {
    MemNSetBitFieldNb (NBPtr, BFCSMux45, 0);
  }

  // BIOS Recommendations for D18F2xA8_dct[1:0][CsMux67]
  if (NumDimmslots == 2) {
    MemNSetBitFieldNb (NBPtr, BFCSMux67, EvaluateCsMuxCZ (DimmAddrMap[1], RankDef[1]) ? 1 : 0);
  } else if (NumDimmslots == 3) {
    if (EvaluateCsMuxCZ (DimmAddrMap[0], RankDef[0]) ||
        EvaluateCsMuxCZ (DimmAddrMap[1], RankDef[1]) ||
        EvaluateCsMuxCZ (DimmAddrMap[2], RankDef[2])) {
      MemNSetBitFieldNb (NBPtr, BFCSMux67, 1);
    } else {
      MemNSetBitFieldNb (NBPtr, BFCSMux67, 0);
    }
  } else {
    MemNSetBitFieldNb (NBPtr, BFCSMux67, 0);
  }

  //BIOS: IF (CsMux67 == 1 || CsMux45 == 1) THEN 1 ELSE 0 ENDIF.
  if (MemNGetBitFieldNb (NBPtr, BFCSMux45) == 1 || MemNGetBitFieldNb (NBPtr, BFCSMux67) == 1) {
    MemNSetBitFieldNb (NBPtr, BFExtendedParityEn, 1);
  }

  for (i = 0; i < 4; i++) {
    MemNSetBitFieldNb (NBPtr, BFTstag0 + i, 0x14);
  }

  MemNSetBitFieldNb (NBPtr, BFFlushWrOnS3StpGnt, 1);

  MemNSetBitFieldNb (NBPtr, RegZqToCsMap, 0x00000A05 & ((NBPtr->DCTPtr->Timings.CsPresent & 0xF)
                                                     | (((NBPtr->DCTPtr->Timings.CsPresent) & 0xF) << 8)));
  if (MemNGetPackageTypeCZ (NBPtr) == CZ_FP4 || MemNGetPackageTypeCZ (NBPtr) == CZ_FM2r2) {
    MemNSetBitFieldNb (NBPtr, RegCkeToCsMap, 0x00000A05 & ((NBPtr->DCTPtr->Timings.CsPresent & 0xF)
                                                       | (((NBPtr->DCTPtr->Timings.CsPresent) & 0xF) << 8)));
  } else {
    MemNSetBitFieldNb (NBPtr, RegCkeToCsMap, 0x08040201 & ((NBPtr->DCTPtr->Timings.CsPresent & 0xF)
                                                       |  (((NBPtr->DCTPtr->Timings.CsPresent) & 0xF) << 8)
                                                       |  (((NBPtr->DCTPtr->Timings.CsPresent) & 0xF) << 16)
                                                       |  (((NBPtr->DCTPtr->Timings.CsPresent) & 0xF) << 24)));
  }

  if (NBPtr->ChannelPtr->RegDimmPresent != 0) {
    MemNSetBitFieldNb (NBPtr, BFSubMemclkRegDly, 1);
  }

  MemNSetBitFieldNb (NBPtr, BFGlobalVrefInSel, 1);

  //======================================================================
  // DisDatMsk: IF (DataMaskMbType != 1) THEN 1 ELSE 0 ENDIF
  //======================================================================
  DataMaskMbTypeOverride = FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                                PSO_DATA_MASK_MB_TYPE,
                                                NBPtr->MCTPtr->SocketId,
                                                NBPtr->ChannelPtr->ChannelID,
                                                0,
                                                NULL,
                                                NULL);
  DataMaskMbType = (DataMaskMbTypeOverride != NULL) ? *DataMaskMbTypeOverride : DATAMASK_DM_ROUTING;
  MemNSetBitFieldNb (NBPtr, BFDisDatMsk, (DataMaskMbType != DATAMASK_DM_ROUTING) ? 1 : 0);

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function looks up platform specific config/timing values from the interface layer and
 *   programs them into DCT.
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE  - No errors
 *     @return          FALSE - Found errors on a channel and disable it
 */

BOOLEAN
MemNPlatformSpecCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MEM_PSC_FLOW_BLOCK *PlatSpecFlowPtr;
  BOOLEAN Result;
  Result = FALSE;
  //
  IDS_OPTION_HOOK (IDS_BEFORE_PLAT_TABLES, NBPtr, &(NBPtr->MemPtr->StdHeader));

  // Extract recommended settings from tables
  //
  MemPPreparePsTabLookupConditions (NBPtr);

  PlatSpecFlowPtr = (MEM_PSC_FLOW_BLOCK*) NBPtr->PlatSpecFlowPtr;

  if (PlatSpecFlowPtr != NULL) {
    //
    // CAD Bus Config
    //
    if (MemPLookupCadBusCfgTabs (NBPtr, PlatSpecFlowPtr->EntryOfTables)) {
      //
      // Data Bus Config
      //
      if (PlatSpecFlowPtr->DramTerm (NBPtr, PlatSpecFlowPtr->EntryOfTables)) {
        //
        // ODT Pattern
        //
        if (MemPGetODTPattern (NBPtr, PlatSpecFlowPtr->EntryOfTables)) {
          Result = TRUE;
        }
      }
    }
  }
  //
  // Disable channel if there are errors
  //
  IDS_SKIP_HOOK (IDS_ENFORCE_PLAT_TABLES, NBPtr, &(NBPtr->MemPtr->StdHeader)) {
    if (!Result) {
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDisable DCT%d due to unsupported DIMM configuration\n", NBPtr->Dct);
      if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
        ASSERT (FALSE);
      }
      MemNDisableDctCZ (NBPtr);
    }
  }

  if (Result) {
    // Program settings
    MemNSetBitFieldNb (NBPtr, BFSlowAccessMode, (NBPtr->ChannelPtr->SlowMode) ? 1 : 0);
    MemNSetBitFieldNb (NBPtr, RegPhyRODTCSLow, NBPtr->ChannelPtr->PhyRODTCSLow);
    MemNSetBitFieldNb (NBPtr, RegPhyRODTCSHigh, NBPtr->ChannelPtr->PhyRODTCSHigh);
    MemNSetBitFieldNb (NBPtr, RegPhyWODTCSLow, NBPtr->ChannelPtr->PhyWODTCSLow);
    MemNSetBitFieldNb (NBPtr, RegPhyWODTCSHigh, NBPtr->ChannelPtr->PhyWODTCSHigh);

    // Override settings as requested
    MemProcessConditionalOverrides (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr, PSO_ACTION_ODT, ALL_DIMMS);
  }

  return Result;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function retrieves the Max latency parameters
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @param[in]  *MinDlyPtr - Pointer to variable to store the Minimum Delay value
 *     @param[in]  *MaxDlyPtr - Pointer to variable to store the Maximum Delay value
 *     @param[in]  *DlyBiasPtr - Pointer to variable to store Delay Bias value
 *     @param[in]  MaxRcvEnDly - Maximum receiver enable delay value
 */

VOID
MemNGetMaxLatParamsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT16 MaxRcvEnDly,
  IN OUT   UINT16 *MinDlyPtr,
  IN OUT   UINT16 *MaxDlyPtr,
  IN OUT   UINT16 *DlyBiasPtr
  )
{
  UINT32 N;
  UINT32 T;
  UINT32 P;
  UINT32 MemClkPeriod;

  // 1. P = N = T = 0.
  P = N = T = 0;

  // Calculate a starting MaxRdLatency delay value by converting Tcl MEMCLKs + 2 MEMCLKs + 4 NCLKs + (18 - (ABYTE RdPtrInitVal/2)) MEMCLKs to NCLKs
  P = 2 * (MemNGetBitFieldNb (NBPtr, BFTcl) + 2 + (18 - (MemNGetBitFieldNb (NBPtr, PER_NB_PS (NBPtr->NbPstate, RegRdPtrInitVal)) + 1) / 2));

  // 10. N = (P/(MemClkFreq * 2) + T) * NclkFreq; Convert from PCLKs plus time to NCLKs.
  MemClkPeriod = 1000000 / ((NBPtr->MemPstate == 0) ? NBPtr->DCTPtr->Timings.Speed : NBPtr->M1Speed);
  N = ((((P * MemClkPeriod + 1) / 2) + T) * NBPtr->NBClkFreq + 500000) / 1000000 + 4;

  // Calculate a starting MaxRdLatency delay value with steps 5, 9, and 12 excluded
  *MinDlyPtr = (UINT16) N;

  *MaxDlyPtr = 0x3FF;

  // 5. Program D18F2x1F[C:0]_dct[1:0][MaxRdLatency] = CEIL(current value + marginfactor).
  // margin factor = 1 NCLK + 3 MEMCLK + ((NBCOF/DdrRate >= 2) ? 4 MEMCLK - 4 NCLK : 0)
  N = 1;
  P = 6;

  if (NBPtr->NBClkFreq >= (UINT16) (((NBPtr->MemPstate == 0) ? NBPtr->DCTPtr->Timings.Speed : NBPtr->M1Speed) * 2)) {
    P += 8;
    N += (((P * MemClkPeriod + 1) / 2) * NBPtr->NBClkFreq + 500000) / 1000000;
    N -= 4;
  } else {
    N += (((P * MemClkPeriod + 1) / 2) * NBPtr->NBClkFreq + 500000) / 1000000;
  }
  *DlyBiasPtr = (UINT16) N;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     The function resets Rcv Fifo
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Dummy - Dummy parameter
 *
 */

VOID
MemNResetRcvFifoCZ (
  IN OUT   struct _MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dummy
  )
{
  // Carrizo does not need to reset Rcv FIFO.
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function modifies CS interleaving low address according to several conditions for CZ.
 *
 *     @param[in,out]  *NBPtr    - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  *LowBit   - Pointer to low bit
 *
 */

BOOLEAN
MemNCSIntLvLowAddrAdjCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *LowBit
  )
{
  UINT8 DctSelIntLvAddr;
  UINT8 BankSwapAddr8En;

  DctSelIntLvAddr = (UINT8) MemNGetBitFieldNb (NBPtr, BFDctSelIntLvAddr);
  BankSwapAddr8En =   (UINT8) MemNGetBitFieldNb (NBPtr, BFBankSwapAddr8En);

  //
  //D18F2x[5C:40]_dct[1:0][15:5] = BaseAddr[21:11] &&
  //D18F2x[6C:60]_dct[1:0][15:5] = AddrMask[21:11], so *LowBit needs to be added with 2.
  //
  *(UINT8 *) LowBit += 2;

  if (MemNGetBitFieldNb (NBPtr, BFBankSwap) == 1) {
    if (((NBPtr->MCTPtr->LogicalCpuid.Revision & AMD_REV_F15_CZ_ALL) != 0 && NBPtr->MemPtr->ParameterListPtr->EnableBankSwapOnly != BANK_SWAP_ONLY_ENABLED) ||
        ((NBPtr->MCTPtr->LogicalCpuid.Revision & AMD_REV_F15_BR_ALL) != 0 && NBPtr->MemPtr->ParameterListPtr->EnableBankSwapOnly == BANK_SWAP_ONLY_DISABLED)) {
      if ((BankSwapAddr8En == 1) && (DctSelIntLvAddr == 4)) {
        *(UINT8 *) LowBit = 5;
      } else {
        *(UINT8 *) LowBit = 6;
      }
    }
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function caps speed based on battery life check.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 */
VOID
MemNCapSpeedBatteryLifeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CONST UINT16 SupportedFreq[] = {
    DDR2400_FREQUENCY,
    DDR2133_FREQUENCY,
    DDR1866_FREQUENCY,
    DDR1600_FREQUENCY,
    DDR1333_FREQUENCY,
    DDR1066_FREQUENCY,
    DDR800_FREQUENCY,
    DDR667_FREQUENCY
  };

  UINT32 NBFreq;
  UINT16 DdrFreq;
  UINT16 j;
  UINT8 Dct;
  INT8   NbPs;
  UINT32 MemPstate;
  UINT8 NumOfNbPstates;
  FABRIC_PSTATE_INFO NbPstateInfo;

  //GetCpuServicesOfCurrentCore ((CONST CPU_SPECIFIC_SERVICES **) &FamilySpecificServices, &(NBPtr->MemPtr->StdHeader));
  IDS_HDT_CONSOLE(MEM_FLOW,"\t\tLimit Memory Speed for Each MState based on lowest Associated NB Frequency...\n");
  //
  // Check each NBState NCLK Frequency against the corresponding MState and limit the Memclk
  // to be equal or less than the NCLK
  //
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tNBPs     NCLK       MPs     MemClk\n");
  NBFreq = 0;
  NumOfNbPstates = (UINT8)FabricPstatesGetNumberOfPstatesOnDie (NBPtr->MCTPtr->SocketId, NBPtr->MCTPtr->DieId) - 1;
  for (NbPs = 0; NbPs < NumOfNbPstates; NbPs++) {
    //
    // Ge NBPState Info
    //
    FabricPstatesGetPstateInfo (NBPtr->MCTPtr->SocketId, NBPtr->MCTPtr->DieId, NbPs, &NbPstateInfo);
    NBFreq = (UINT32)NbPstateInfo.Frequency;
    MemPstate = (UINT32)NbPstateInfo.AssociatedMstate;
    ASSERT (MemPstate < 2);
    IDS_HDT_CONSOLE(MEM_FLOW, "\t\t %d       %s%dMHz     %d      ", NbPs, (NBFreq < 1000) ? " " : "", NBFreq, MemPstate);
    //
    // Pick Max MEMCLK that is less than or equal to NCLK
    //
    DdrFreq = DDR800_FREQUENCY;
    for (j = 0; j < GET_SIZE_OF (SupportedFreq); j++) {
      if (NBFreq >= SupportedFreq[j]) {
        DdrFreq = SupportedFreq[j];
        break;
      }
    }
    //
    // Cap MemClk frequency to lowest NCLK frequency
    //
    if (MemPstate == 0) {
      //
      // MPState 0
      //
      for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
        MemNSwitchDCTNb (NBPtr, Dct);
        IDS_HDT_CONSOLE(MEM_FLOW, "%s", (Dct > 0) ? "\n\t\t                            " : "");
        IDS_HDT_CONSOLE(MEM_FLOW, "Dct %d: %dMHz", Dct, NBPtr->DCTPtr->Timings.TargetSpeed);
        if (NBPtr->DCTPtr->Timings.TargetSpeed > DdrFreq) {
          NBPtr->DCTPtr->Timings.TargetSpeed = DdrFreq;
          IDS_HDT_CONSOLE(MEM_FLOW, " --> %dMHz", NBPtr->DCTPtr->Timings.TargetSpeed);
        }
      }
      IDS_HDT_CONSOLE(MEM_FLOW, "\n");
    } else {
      //
      // MPState 1
      //
      IDS_HDT_CONSOLE(MEM_FLOW, "%dMHz", NBPtr->M1Speed);
      if (NBPtr->M1Speed > DdrFreq) {
        NBPtr->M1Speed = DdrFreq;
        IDS_HDT_CONSOLE(MEM_FLOW, " --> %dMHz", NBPtr->M1Speed);
      }
      IDS_HDT_CONSOLE(MEM_FLOW, "\n");
    }
    //
    // Check to make sure limiting clock value is valid
    //
    ASSERT ((NBPtr->ChannelPtr->TechType == DDR3_TECHNOLOGY) ?
            (DdrFreq >= DDR667_FREQUENCY) :
            ((NBPtr->ChannelPtr->TechType == DDR4_TECHNOLOGY) ?
             (DdrFreq >= DDR1333_FREQUENCY) :
             (DdrFreq <= DDR1066_FREQUENCY)));
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Configure disable DLL shutdown in self-refresh mode.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNConfigureDisDllShutdownSrCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNBrdcstSetUnConditionalNb (NBPtr, BFDisDllShutdownSR, 0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function finds the DIMM that has the largest receiver enable delay
 *     that are trained by PMU
 *
 *     @param[in,out]   *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[out]      *ChipSel   - Pointer to the Chip select that has the
 *                                   largest Round Trip Command Delay.
 *
 *     @return   TRUE  - A chip select can be found.
 *               FALSE - A chip select cannot be found.
 */

BOOLEAN
MemNCalculateRoundTripCommandDelayCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
     OUT   UINT8 *ChipSel
  )
{
  BIT_FIELD_NAME BitField;
  UINT8   ChipSelect;
  BOOLEAN RetVal;
  UINT16  MaxDly;
  UINT16  DqAndDqsDly;
  UINT8   MaxDlyCs;
  UINT32  DqValue;
  UINT32  DqsValue;
  UINT32  RxRdPtrOffset;
  UINT8  ByteLane;
  UINT8   Dimm;

  RetVal = FALSE;
  MaxDly = 0;
  MaxDlyCs = 0;

  IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\tCalculating worst-case round trip command delay on channel %d\n", NBPtr->Dct);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t MaxRxCmdDelay = (RxRdPtrOffset * 64) + RxDly(DQS) +  MAX((RxDly(DQ_H) & 0x1F), (RxDly(DQ_L) & 0x1F))\n");

  RxRdPtrOffset = ( 0x3F & MemNGetBitFieldNb (NBPtr, RegDataRdPtrOffset));
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t RxRdPtrOffset = %02x\n", RxRdPtrOffset);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t                      ------- RxDly -------\n");
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tDimm     ByteLane     DQS     DQ_L     DQ_H     MaxRxCmdDelay\n");

  for (ChipSelect = 0; ChipSelect < NBPtr->CsPerChannel; ChipSelect = ChipSelect + NBPtr->CsPerDelay) {
    if ((NBPtr->DCTPtr->Timings.CsPresent & ((UINT16) ((NBPtr->CsPerDelay == 2)? 3 : 1) << ChipSelect)) != 0) {
      Dimm = ChipSelect >> ((NBPtr->CsPerDelay == 2)? 1 : 0);
      BitField = PER_DIMM (Dimm, RegDataRxDly);
      IDS_HDT_CONSOLE (MEM_FLOW, "\t\t  %d         ",Dimm);
      for (ByteLane = 0; ByteLane < ((NBPtr->MCTPtr->Status[SbEccDimms] && NBPtr->IsSupported[EccByteTraining]) ? 9 : 8); ByteLane++) {
        IDS_HDT_CONSOLE (MEM_FLOW, "%s%d          ", (ByteLane > 0)?"\t\t            ":"", ByteLane);
        //
        // RxDly of DQS
        //
        DqsValue = MemNGetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQS_H, ByteLane, BitField));
        //
        // RxDly of DQ_L
        //
        DqValue = (MemNGetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ_L, ByteLane, BitField)) & 0x1F);
        //
        // Chipselect has the worst round trip.
        //
        DqAndDqsDly = (UINT16) ((RxRdPtrOffset * 64) + (DqValue + DqsValue));
        IDS_HDT_CONSOLE (MEM_FLOW, "%02x      %02x%s      ",DqsValue, DqValue, (DqAndDqsDly > MaxDly)?"*":" ");
        if (DqAndDqsDly > MaxDly) {
          MaxDly = DqAndDqsDly;
          MaxDlyCs = ChipSelect;
          RetVal = TRUE;
        }
        //
        // RxDly of DQ_H
        //
        DqValue = (MemNGetBitFieldNb (NBPtr, PER_DATA_BYTE (PAD_DQ_H, ByteLane, BitField)) & 0x1F);
        //
        // Chipselect has the worst round trip.
        //
        DqAndDqsDly = (UINT16) ((RxRdPtrOffset * 64) + (DqValue + DqsValue));
        IDS_HDT_CONSOLE (MEM_FLOW, "%02x%s        ", DqValue, (DqAndDqsDly > MaxDly)?"*":" ");
        if (DqAndDqsDly > MaxDly) {
          MaxDly = DqAndDqsDly;
          MaxDlyCs = ChipSelect;
          RetVal = TRUE;
        }
        IDS_HDT_CONSOLE (MEM_FLOW, "%02x \n", MaxDly);
      } // End of ByteLane For Loop.
    }
  } // End of ChipSelect For Loop.
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMaxRxCmdDelay Value is %02x on Chipselect %d.\n\n", MaxDly, MaxDlyCs);
  NBPtr->TechPtr->MaxDlyForMaxRdLat = MaxDly;
  *ChipSel = MaxDlyCs;
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function trains Max latency for all dies
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTTrainMaxLatencyCZ (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT32 TestAddrRJ16;
  UINT8 Dct;
  UINT8 ChipSel;
  UINT8  *PatternBufPtr;
  UINT8  *TestBufferPtr;
  UINT8  CurrentNbPstate;
  UINT16 CalcMaxLatDly;
  UINT16 MaxLatDly;
  UINT16 MaxLatLimit;
  UINT16 Margin;
  UINT16 CurTest;
  UINT16 _CL_;
  UINT8 TimesFail;
  UINT8 TimesRetrain;
  UINT16 i;

  MEM_DATA_STRUCT *MemPtr;
  DIE_STRUCT *MCTPtr;
  MEM_NB_BLOCK  *NBPtr;

  NBPtr = TechPtr->NBPtr;
  MCTPtr = NBPtr->MCTPtr;
  MemPtr = NBPtr->MemPtr;
  TechPtr->TrainingType = TRN_MAX_READ_LATENCY;
  TimesRetrain = DEFAULT_TRAINING_TIMES;
  IDS_OPTION_HOOK (IDS_MEM_RETRAIN_TIMES, &TimesRetrain, &MemPtr->StdHeader);

  IDS_HDT_CONSOLE (MEM_STATUS, "\nStart MaxRdLat training\n");
  // Set environment settings before training
  AGESA_TESTPOINT (TpProcMemMaxRdLatencyTraining, &(MemPtr->StdHeader));

  MemTBeginTraining (TechPtr);
  //
  // Initialize the Training Pattern
  //
  if (AGESA_SUCCESS != NBPtr->TrainingPatternInit (NBPtr)) {
    return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
  }
  TechPtr->PatternLength = (MCTPtr->Status[Sb128bitmode]) ? 6 : 3;
  //
  // Setup hardware training engine (if applicable)
  //
  NBPtr->FamilySpecificHook[SetupHwTrainingEngine] (NBPtr, &TechPtr->TrainingType);
  //
  // Adjust RdDqsDly used for MaxRdLatency calculation
  //
  NBPtr->FamilySpecificHook[AdjustRdDqsDlyForMaxRdLat] (NBPtr, NULL);

  MaxLatDly = 0;
  _CL_ = TechPtr->PatternLength;
  PatternBufPtr = TechPtr->PatternBufPtr;
  TestBufferPtr = TechPtr->TestBufPtr;
  //
  // Begin max latency training
  //
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    if (MCTPtr->Status[Sb128bitmode] && (Dct != 0)) {
      break;
    }

    NBPtr->SwitchDCT (NBPtr, Dct);

    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);
      if (MemNCalculateRoundTripCommandDelayCZ (NBPtr, &ChipSel)) {
        TechPtr->ChipSel = ChipSel;
        if (NBPtr->GetSysAddr (NBPtr, ChipSel, &TestAddrRJ16)) {
          IDS_HDT_CONSOLE (MEM_STATUS, "\t\tCS %d\n", ChipSel);
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tWrite to address: %04x0000\n", TestAddrRJ16);

          // Write the test patterns
          AGESA_TESTPOINT (TpProcMemMaxRdLatWritePattern, &(MemPtr->StdHeader));
          NBPtr->WritePattern (NBPtr, TestAddrRJ16, PatternBufPtr, _CL_);

          // Sweep max latency delays
          NBPtr->getMaxLatParams (NBPtr, TechPtr->MaxDlyForMaxRdLat, &CalcMaxLatDly, &MaxLatLimit, &Margin);
          AGESA_TESTPOINT (TpProcMemMaxRdLatStartSweep, &(MemPtr->StdHeader));

          TimesFail = 0;
          ERROR_HANDLE_RETRAIN_BEGIN (TimesFail, TimesRetrain)
          {
            MaxLatDly = CalcMaxLatDly;
            for (i = 0; i < (MaxLatLimit - CalcMaxLatDly); i++) {
              NBPtr->SetBitField (NBPtr, BFMaxLatency0 + NBPtr->NbPstate, MaxLatDly);
              IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDly %3x", MaxLatDly);
              TechPtr->ResetDCTWrPtr (TechPtr, 6);

              AGESA_TESTPOINT (TpProcMemMaxRdLatReadPattern, &(MemPtr->StdHeader));
              NBPtr->ReadPattern (NBPtr, TestBufferPtr, TestAddrRJ16, _CL_);
              AGESA_TESTPOINT (TpProcMemMaxRdLatTestPattern, &(MemPtr->StdHeader));
              CurTest = NBPtr->CompareTestPattern (NBPtr, TestBufferPtr, PatternBufPtr, _CL_ * 64);
              NBPtr->FlushPattern (NBPtr, TestAddrRJ16, _CL_);

              if (NBPtr->IsSupported[ReverseMaxRdLatTrain]) {
                // Reverse training decrements MaxLatDly whenever the test passes
                // and uses the last passing MaxLatDly as left edge
                if (CurTest == 0xFFFF) {
                  IDS_HDT_CONSOLE (MEM_FLOW, "  P");
                  if (MaxLatDly == 0) {
                    break;
                  } else {
                    MaxLatDly--;
                  }
                }
              } else {
                // Traditional training increments MaxLatDly until the test passes
                // and uses it as left edge
                if (CurTest == 0xFFFF) {
                  IDS_HDT_CONSOLE (MEM_FLOW, "  P");
                  break;
                } else {
                  MaxLatDly++;
                }
              }
              IDS_HDT_CONSOLE (MEM_FLOW, "\n");
            } // End of delay sweep
            ERROR_HANDLE_RETRAIN_END ((MaxLatDly >= MaxLatLimit), TimesFail)
          }

          AGESA_TESTPOINT (TpProcMemMaxRdLatSetDelay, &(MemPtr->StdHeader));

          if (MaxLatDly >= MaxLatLimit) {
            PutEventLog (AGESA_ERROR, MEM_ERROR_MAX_LAT_NO_WINDOW, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
            SetMemError (AGESA_ERROR, MCTPtr);
            NBPtr->DCTPtr->Timings.CsTrainFail |= NBPtr->DCTPtr->Timings.CsPresent;
            MCTPtr->ChannelTrainFail |= (UINT32)1 << Dct;
            if (!NBPtr->MemPtr->ErrorHandling (MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
              ASSERT (FALSE);
              return FALSE;
            }
          } else {
            NBPtr->FamilySpecificHook[AddlMaxRdLatTrain] (NBPtr, &TestAddrRJ16);

            IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\tFirst Passing MRL: %03x", MaxLatDly);
            MaxLatDly = MaxLatDly + Margin;
            if (NBPtr->IsSupported[ReverseMaxRdLatTrain]) {
              MaxLatDly++;  // Add 1 to get back to the last passing value
            }
            // Set final delays
            CurrentNbPstate = (UINT8) MemNGetBitFieldNb (NBPtr, BFCurNbPstate);
            ASSERT (CurrentNbPstate <= 3);
            NBPtr->ChannelPtr->DctMaxRdLat [CurrentNbPstate] = MaxLatDly;
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tShifted MaxRdLat: %03x", MaxLatDly);
            // Pick the smallest MaxRdLatency over multiple runs
            if (MaxLatDly < (&NBPtr->DCTPtr->Timings.MaxRdLat0)[NBPtr->NbPstate]) {
              (&NBPtr->DCTPtr->Timings.MaxRdLat0)[NBPtr->NbPstate] = MaxLatDly;
            } else {
              MaxLatDly = (&NBPtr->DCTPtr->Timings.MaxRdLat0)[NBPtr->NbPstate];
            }
            NBPtr->SetBitField (NBPtr, BFMaxLatency0 + NBPtr->NbPstate, MaxLatDly);
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tFinal MaxRdLat: %03x\n", MaxLatDly);

          }
        }
      }
    }
  }

  // Restore environment settings after training
  MemTEndTraining (TechPtr);
  IDS_HDT_CONSOLE (MEM_FLOW, "\nEnd MaxRdLat training\n\n");
  //
  // Finalize the Pattern
  //
  NBPtr->TrainingPatternFinalize (NBPtr);
  return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Get the MaxDdrRate
 *
 *     @param[in,out]   *NBPtr      - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *OptParam   - Pointer to DdrMaxRate
 *
 */

BOOLEAN
MemNGetDdrMaxRateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *OptParam
  )
{
  LOCATE_HEAP_PTR LocHeap;

  LocHeap.BufferHandle = AMD_MEM_DDR_MAX_RATE_HANDLE;
  if (HeapLocateBuffer (&LocHeap, &(NBPtr->MemPtr->StdHeader)) == AGESA_SUCCESS) {
    *(UINT8 *)OptParam = *(UINT8 *)LocHeap.BufferPtr;
  }

  return TRUE;
}

