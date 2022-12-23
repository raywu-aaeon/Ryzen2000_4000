/* $NoKeywords:$ */
/**
 * @file
 *
 * mn.c
 *
 * Common Northbridge functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/)
 * @e \$Revision: 323045 $ @e \$Date: 2015-07-21 17:18:32 +0800 (Tue, 21 Jul 2015) $
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
#include <Library/BaseMemoryLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mport.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "S3.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NBLIB_MN_FILECODE

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
extern OPTION_MEM_FEATURE_NB* memNTrainFlowControl[];

extern BUILD_OPT_CFG UserOptions;
extern PSO_ENTRY DefaultPlatformMemoryConfiguration[];
extern MEM_PLATFORM_CFG* memPlatformTypeInstalled[];

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes the default values in the MEM_DATA_STRUCT
 *
 *     @param[in,out]   *MemPtr  - Pointer to the MEM_DATA_STRUCT
 *
 */
VOID
MemNCmnInitDefaultsNb (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  //UINT8 Socket;
  //UINT8 Channel;
  //MEM_PARAMETER_STRUCT *RefPtr;
  //ASSERT (MemPtr != NULL);
  //RefPtr = MemPtr->ParameterListPtr;
  //
  // Memory Map/Mgt.
  // Mask Bottom IO with 0xF8 to force hole size to have granularity of 128MB
  //RefPtr->BottomIo = 0xE0;
  //RefPtr->UmaVersion = UserOptions.CfgUmaVersion;
  //RefPtr->UmaMode = UserOptions.CfgUmaMode;
  //RefPtr->UmaSize = UserOptions.CfgUmaSize;
  //RefPtr->MemHoleRemapping = TRUE;
  //RefPtr->LimitMemoryToBelow1Tb = UserOptions.CfgLimitMemoryToBelow1Tb;
  //
  // Dram Timing
  //
  //RefPtr->UserTimingMode = UserOptions.CfgTimingModeSelect;
  //RefPtr->MemClockValue = UserOptions.CfgMemoryClockSelect;
  //RefPtr->MemoryAllClocksOn = UserOptions.CfgMemoryAllClocksOn;
  //
  // Socket Struct
  //
  //for (Socket = 0; Socket < MAX_SOCKETS_SUPPORTED; Socket++) {
  //  for (Channel = 0; Channel < MAX_CHANNELS_PER_SOCKET; Channel++) {
  //    MemPtr->SocketList[Socket].ChannelPtr[Channel] = NULL;
  //    MemPtr->SocketList[Socket].TimingsPtr[Channel] = NULL;
  //  }
  //}
  //
  // UMA options
  //
  //RefPtr->UmaSize = UserOptions.CfgUmaSize;
  //RefPtr->UmaAbove4G = UserOptions.CfgUmaAbove4G;
  //RefPtr->UmaAlignment = UserOptions.CfgUmaAlignment;
  //
  // Memory Clear
  //RefPtr->EnableMemClr = TRUE;
  //
  // TableBasedAlterations
  //
  //RefPtr->TableBasedAlterations = NULL;
  //
  // Platform config table
  //
  //RefPtr->PlatformMemoryConfiguration = DefaultPlatformMemoryConfiguration;
  //
  // Memory Restore
  //
  //RefPtr->MemRestoreCtl = FALSE;
  //RefPtr->SaveMemContextCtl = FALSE;
  //
  // Capsule support
  //
  //RefPtr->IsCapsuleMode = FALSE;
  //S3DataBlockInitializer (&RefPtr->MemContext);
  //
  // Dram Configuration
  //
  //RefPtr->EnableBankSwapOnly = UserOptions.CfgMemoryEnableBankSwapOnly;
  //RefPtr->EnableBankIntlv = UserOptions.CfgMemoryEnableBankInterleaving;
  //RefPtr->EnableNodeIntlv = UserOptions.CfgMemoryEnableNodeInterleaving;
  //RefPtr->EnableChannelIntlv = UserOptions.CfgMemoryChannelInterleaving;
  //RefPtr->EnableBankSwizzle = UserOptions.CfgBankSwizzle;
  //RefPtr->EnableParity = UserOptions.CfgMemoryParityEnable;
  //RefPtr->EnableOnLineSpareCtl = UserOptions.CfgOnlineSpare;
  //
  // Dram Power
  //
  //RefPtr->EnablePowerDown = UserOptions.CfgMemoryPowerDown;
  //
  // Dram Mac Default
  //
  //RefPtr->DramMacDefault = UserOptions.CfgMemoryMacDefault;
  //
  // Dram Extended Temperature Range
  //
  //RefPtr->EnableExtendedTemperatureRange = UserOptions.CfgMemoryExtendedTemperatureRange;
  //
  // Dram Temperature Controlled Refresh Rate Enable
  //
  //RefPtr->DramTempControlledRefreshEn = UserOptions.CfgDramTempControlledRefreshEn;
  //
  // ECC
  //
  //RefPtr->EnableDllPDBypassMode = UserOptions.CfgDdrPhyDllBypassMode;
  //
  // ECC
  //
  //RefPtr->EnableEccFeature = UserOptions.CfgEnableEccFeature;
  //
  // Vref
  //
  //RefPtr->ExternalVrefCtl = UserOptions.CfgExternalVrefCtlFeature;
  //
  //Training Mode
  //
  //RefPtr->ForceTrainMode = UserOptions.CfgForceTrainMode;
  //RefPtr->PmuTrainMode = UserOptions.CfgPmuTrainMode;
  //
  // AMP
  //
  //RefPtr->AmpEnable = FALSE;
  //RefPtr->AmpWarningMsgEnable = FALSE;
  //
  // Preferred technology type that AGESA will enable when it is mixed with other technology types.
  //
  //RefPtr->DimmTypeUsedInMixedConfig = UserOptions.CfgDimmTypeUsedInMixedConfig;
  //RefPtr->DimmTypeDddr3Capable = UserOptions.CfgDimmTypeDdr3Capable;
  //RefPtr->DimmTypeDddr4Capable = UserOptions.CfgDimmTypeDdr4Capable;

  // 2x DRAM refresh rate.
  //RefPtr->DramDoubleRefreshRate = UserOptions.CfgDramDoubleRefreshRateEn;

  //
  // Check if there is a Vddio Override through BLDCFG
  //
  //if (RefPtr->CustomVddioVoltage <= VOLT1_2) {
  //  RefPtr->CustomVddioSupport = RefPtr->CfgCustomVddioVoltage;
  //  IDS_HDT_CONSOLE (MEM_FLOW, "\nCustom VDDIO Change is initiated through BLDCFG\n");
  //  IDS_HDT_CONSOLE (MEM_FLOW, "\tWARNING!!! If CustomVddio voltage request is more than supported DDR Voltage, it could potentially damage the DIMMs\n");
  //} else {
  //  ASSERT (RefPtr->CfgCustomVddioVoltage <= VOLT1_2);
  //  RefPtr->CustomVddioSupport = VOLT_INITIAL;
  //}
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function initializes member functions and variables of NB block.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNInitNBDataNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  INT32 i;

  NBPtr->DctCachePtr = NBPtr->DctCache;
  NBPtr->PsPtr = NBPtr->PSBlock;
  NBPtr->PlatSpecFlowPtr = NULL;

  SetMem (NBPtr->DctCachePtr, sizeof (NBPtr->DctCache), 0);

  SetMem (&NBPtr->IsSupported, sizeof (NBPtr->IsSupported), 0);

  for (i = 0; i < NumberOfHooks; i++) {
    NBPtr->FamilySpecificHook[i] = MemNDefaultFamilyHookNb;
  }

  for (i = 0; i < NBPtr->DctCount; i++) {
    NBPtr->PSBlock[i].MemPGetPass1Seeds = (BOOLEAN (*) (MEM_NB_BLOCK *)) memDefTrue;
  }

  NBPtr->SwitchDCT = MemNSwitchDCTNb;
  NBPtr->SwitchChannel = MemNSwitchChannelNb;
  NBPtr->GetBitField = MemNGetBitFieldNb;
  NBPtr->SetBitField = MemNSetBitFieldNb;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   Get System address of Chipselect RJ 16 bits (Addr[47:16])
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Receiver - Chipselect to be targeted [0-7]
 *     @param[out]      AddrPtr -  Pointer to System Address [47:16]
 *
 *     @return      TRUE  - Address is valid
 *     @return      FALSE  - Address is not valid
 */

BOOLEAN
MemNGetMCTSysAddrNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Receiver,
     OUT   UINT32 *AddrPtr
  )
{
  S_UINT64 SMsr;
  UINT32 CSBase;
  UINT32 HoleBase;
  UINT32 DctSelBaseAddr;
  UINT32 BottomUma;
  DIE_STRUCT *MCTPtr;
  MEM_DATA_STRUCT *MemPtr;

  MCTPtr = NBPtr->MCTPtr;
  MemPtr = NBPtr->MemPtr;

  ASSERT (Receiver < 8);

  CSBase = MemNGetBitFieldNb (NBPtr, BFCSBaseAddr0Reg + Receiver);
  if (CSBase & 1) {
    ASSERT ((CSBase & 0xE0) == 0);   // Should not enable CS interleaving before DQS training.

    // Scale base address from [39:8] to [47:16]
    CSBase >>= 8;

    HoleBase = MCTPtr->NodeHoleBase ? MCTPtr->NodeHoleBase : 0x7FFFFFFF;

    if ((MemNGetBitFieldNb (NBPtr, BFDctSelHiRngEn) == 1) && (NBPtr->Dct == MemNGetBitFieldNb (NBPtr, BFDctSelHi))) {
      DctSelBaseAddr = MemNGetBitFieldNb (NBPtr, BFDctSelBaseAddr) << (27 - 16);
      if (DctSelBaseAddr > HoleBase) {
        DctSelBaseAddr -= _4GB_RJ16 - HoleBase;
      }
      CSBase += DctSelBaseAddr;
    } else {
      CSBase += MCTPtr->NodeSysBase;
    }

    if (CSBase >= HoleBase) {
      CSBase += _4GB_RJ16 - HoleBase;
    }

    CSBase += (UINT32)1 << (21 - 16);  // Add 2MB offset to avoid compat area.
    if ((CSBase >= (MCT_TRNG_KEEPOUT_START >> 8)) && (CSBase <= (MCT_TRNG_KEEPOUT_END >> 8))) {
      CSBase += (((MCT_TRNG_KEEPOUT_END >> 8) - CSBase) + 0x0F) & 0xFFFFFFF0;
    }

    if (MCTPtr->Status[SbHWHole]) {
      if (MCTPtr->Status[SbSWNodeHole]) {
        SMsr.Value64 = AsmReadMsr64 (TOP_MEM);

        if ((CSBase >= (SMsr.Values32.lo >> 16)) && (CSBase < _4GB_RJ16)) {
          return FALSE;
        }
      }
    }

    BottomUma = NBPtr->RefPtr->Sub4GCacheTop >> 16;
    if (BottomUma && (CSBase >= BottomUma) && (CSBase < _4GB_RJ16)) {
      return FALSE;
    }
    *AddrPtr = CSBase;
    return TRUE;
  }
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function determines if a Rank is enabled.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]    Receiver - Receiver to check
 *     @return - FALSE
 *
 */

BOOLEAN
MemNRankEnabledNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Receiver
  )
{
  UINT32 CSBase;
  CSBase = MemNGetBitFieldNb (NBPtr, BFCSBaseAddr0Reg + Receiver);
  if (CSBase & 1) {
    return  TRUE;
  } else {
    return  FALSE;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function sets the EccSymbolSize bit depending upon configurations
 *     and system override.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSetEccSymbolSizeNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 X4DimmsOnly;
  BOOLEAN Size;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  MEM_PARAMETER_STRUCT *RefPtr;

  ASSERT (NBPtr != NULL);

  MCTPtr = NBPtr->MCTPtr;
  DCTPtr = NBPtr->DCTPtr;
  RefPtr = NBPtr->RefPtr;

  // Determine if this node has only x4 DRAM parts
  X4DimmsOnly = (UINT16) ((!(DCTPtr->Timings.Dimmx8Present | DCTPtr->Timings.Dimmx16Present)) && DCTPtr->Timings.Dimmx4Present);
  //
  // Check if EccSymbolSize BKDG value is overridden
  //
  if (RefPtr->EccSymbolSize != ECCSYMBOLSIZE_USE_BKDG) {
    Size = (RefPtr->EccSymbolSize == ECCSYMBOLSIZE_FORCE_X4) ? FALSE : TRUE;
  } else {
    if (X4DimmsOnly && MCTPtr->GangedMode) {
      Size = FALSE;
    } else {
      Size = TRUE;
    }
    NBPtr->FamilySpecificHook[ForceEccSymbolSize] (NBPtr, &Size);
  }
  IDS_OPTION_HOOK (IDS_ECCSYMBOLSIZE, &Size, &(NBPtr->MemPtr->StdHeader));
  MemNSetBitFieldNb (NBPtr, BFEccSymbolSize, (UINT32) Size);
}

/*-----------------------------------------------------------------------------*/
/**
 *
 *      This function flushes the  training pattern
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in] Address - System Address [47:16]
 *     @param[in] ClCount - Number of cache lines
 *
 */

VOID
MemNFlushPatternNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 Address,
  IN       UINT16 ClCount
  )
{
  // Due to speculative execution during MemUReadCachelines, we must
  //  flush one more cache line than we read.
  MemUProcIOClFlush (Address, ClCount + 1, NBPtr->MemPtr);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function compares test pattern with data in buffer and
 *     return a pass/fail bitmap for 8 bytelanes (upper 8 bits are reserved)
 *
 *     @param[in,out]   *NBPtr    - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Buffer[]  - Buffer data from DRAM (Measured data from DRAM) to compare
 *     @param[in]       Pattern[] - Pattern (Expected data in ROM/CACHE) to compare against
 *     @param[in]       ByteCount - Byte count
 *
 *     @return  PASS - Bitmap of results of comparison
 */

UINT16
MemNCompareTestPatternNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Buffer[],
  IN       UINT8 Pattern[],
  IN       UINT16 ByteCount
  )
{
  UINT16 i;
  UINT16 Pass;
  UINT8 ColumnCount;
  UINT8 FailingBitMask[8];

  ASSERT ((ByteCount == 18 * 64) || (ByteCount == 9 * 64) || (ByteCount == 64 * 64) || (ByteCount == 32 * 64) || (ByteCount == 3 * 64));

  ColumnCount = NBPtr->ChannelPtr->ColumnCount;
  Pass = 0xFFFF;
  //
  // Clear Failing Bit Mask
  //
  for (i = 0; i < sizeof (FailingBitMask); i++) {
    FailingBitMask[i] = 0;
  }

  if (NBPtr->Ganged && (NBPtr->Dct != 0)) {
    i = 8;   // DCT 1 in ganged mode
  } else {
    i = 0;
  }

  for (; i < ByteCount; i++) {
    if (Buffer[i] != Pattern[i]) {
      // if bytelane n fails
      Pass &= ~((UINT16)1 << (i % 8));    // clear bit n
      FailingBitMask[i % NBPtr->TechPtr->MaxByteLanes ()] |= (Buffer[i] ^ Pattern[i]);
    }

    if (NBPtr->Ganged && ((i & 7) == 7)) {
      i += 8;     // if ganged, skip over other Channel's Data
    }
  }
  //
  // Accumulate Failing bit data
  //
  for (i = 0; i < sizeof (FailingBitMask); i++) {
    NBPtr->ChannelPtr->FailingBitMask[(ColumnCount * NBPtr->TechPtr->ChipSel) + i] &=
      FailingBitMask[i];
  }

  return Pass;
}

/*-----------------------------------------------------------------------------
 *
 *
 *     This function compares test pattern with data in buffer and
 *     return a pass/fail bitmap for 8 bytelanes (upper 8 bits are reserved)
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Buffer[]  - Buffer data from DRAM (Measured data from DRAM) to compare
 *     @param[in]       Pattern[] - Pattern (Expected data in ROM/CACHE) to compare against
 *     @param[in]       ByteCount - Byte count
 *
 *     @retval  PASS - Bitmap of results of comparison
 * ----------------------------------------------------------------------------
 */
UINT16
MemNInsDlyCompareTestPatternNb (
  IN       MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Buffer[],
  IN       UINT8 Pattern[],
  IN       UINT16 ByteCount
  )
{
  UINT16 i;
  UINT16 Pass;
  UINT16 BeatOffset;
  UINT16 BeatCnt;
  UINT8 ColumnCount;
  UINT8 FailingBitMask[8];

  ASSERT ((ByteCount == 18 * 64) || (ByteCount == 9 * 64) || (ByteCount == 64 * 64) || (ByteCount == 32 * 64) || (ByteCount == 3 * 64));

  ColumnCount = NBPtr->ChannelPtr->ColumnCount;
  Pass = 0xFFFF;
  //
  // Clear Failing Bit Mask
  //
  for (i = 0; i < sizeof (FailingBitMask); i++) {
    FailingBitMask[i] = 0;
  }

  if (NBPtr->Ganged && (NBPtr->Dct != 0)) {
    i = 8;   // DCT 1 in ganged mode
  } else {
    i = 0;
  }

  if (NBPtr->Ganged) {
    BeatOffset = 16;
  } else {
    BeatOffset = 8;
  }

  BeatCnt = 0;
  for (; i < ByteCount; i++) {

    if (Buffer[i] != Pattern[i + BeatOffset]) {
      // if bytelane n fails
      Pass &= ~((UINT16)1 << (i % 8));    // clear bit n
      FailingBitMask[i % NBPtr->TechPtr->MaxByteLanes ()] |= (Buffer[i] ^ Pattern[i + BeatOffset]);
    }

    if ((i & 7) == 7) {
      if (NBPtr->Ganged) {
        i += 8;     // if ganged, skip over other Channel's Data
      }
      BeatCnt++;
    }

    if ((BeatCnt & 3) == 3) {
      // Skip last data beat of a 4-beat burst.
      BeatCnt++;
      i = i + BeatOffset;
    }
  }
  //
  // Accumulate Failing bit data
  //
  for (i = 0; i < sizeof (FailingBitMask); i++) {
    NBPtr->ChannelPtr->FailingBitMask[(ColumnCount * NBPtr->TechPtr->ChipSel) + i] &=
      FailingBitMask[i];
  }

  return Pass;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function sets the training control flow for UNB
 *      The DDR3 mode bit must be set prior to calling this function
 *
 *      @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 */
BOOLEAN
MemNTrainingFlowUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  memNTrainFlowControl[DDR3_TRAIN_FLOW] (NBPtr);
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function sets the ECC exclusion range for UNB
 *
 *      @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 */
VOID
MemNSetEccExclusionRangeUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MEM_PARAMETER_STRUCT *RefPtr;
  RefPtr = NBPtr->RefPtr;

  if (RefPtr->UmaSize != 0) {
    NBPtr->SetBitField (NBPtr, BFECCExclusionBaseLow, (RefPtr->UmaBase << 16) | 1);
    NBPtr->SetBitField (NBPtr, BFECCExclusionBaseHigh, RefPtr->UmaBase >> 16);
    NBPtr->SetBitField (NBPtr, BFECCExclusionLimitLow, ((RefPtr->UmaBase + RefPtr->UmaSize) << 16) - 1);
    NBPtr->SetBitField (NBPtr, BFECCExclusionLimitHigh, (RefPtr->UmaBase + RefPtr->UmaSize - 1) >> 16);
  }
}
/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */


