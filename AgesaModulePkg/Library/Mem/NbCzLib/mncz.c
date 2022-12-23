/* $NoKeywords:$ */
/**
 * @file
 *
 * mncz.c
 *
 * Common Northbridge  functions for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 320611 $ @e \$Date: 2015-06-12 15:21:43 +0800 (Fri, 12 Jun 2015) $
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mp.h"
#include "mncz.h"
#include "AmdSoc.h"
#include "mu.h"
#include "PlatformMemoryConfiguration.h"
#include "S3.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_NBCZLIB_MNCZ_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define MEM_PSC_FLOW_DEFTRUE (BOOLEAN (*) (MEM_NB_BLOCK*, MEM_PSC_TABLE_BLOCK *)) memDefTrue

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

extern PSO_ENTRY DefaultPlatformMemoryConfiguration[];
extern MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[];
extern MEM_PSC_FLOW MemPGetMaxFreqSupported;
extern OPTION_MEM_FEATURE_NB MemNInitEarlySampleSupportCZ;

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes the northbridge block
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *MemPtr  - Pointer to the MEM_DATA_STRUCT
 *     @param[in]        *FeatPtr  - Pointer to the MEM_FEAT_BLOCK_NB
 *     @param[in]        *SharedPtr - Pointer to the MEM_SHARED_DATA
 *     @param[in]        NodeID  - UINT8 indicating node ID of the NB object.
 *
 *     @return     Boolean indicating that this is the correct memory
 *                 controller type for the node number that was passed in.
 */

BOOLEAN
MemConstructNBBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       MEM_FEAT_BLOCK_NB *FeatPtr,
  IN       MEM_SHARED_DATA *SharedPtr,
  IN       UINT8 NodeID
  )
{
  UINT8 Dct;
  UINT8 Channel;
  UINT8 SpdSocketIndex;
  UINT8 SpdChannelIndex;
  DIE_STRUCT *MCTPtr;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;

  GetLogicalIdOfSocket (MemPtr->DiesPerSystem->SocketId, &(MemPtr->DiesPerSystem->LogicalCpuid), &(MemPtr->StdHeader));

  NBPtr->MemPtr = MemPtr;
  NBPtr->RefPtr = MemPtr->ParameterListPtr;
  NBPtr->SharedPtr = SharedPtr;

  MCTPtr = MemPtr->DiesPerSystem;
  NBPtr->MCTPtr = MCTPtr;
  NBPtr->MCTPtr->NodeId = NodeID;
  NBPtr->PciAddr.AddressValue = MCTPtr->PciAddr.AddressValue;
  NBPtr->VarMtrrHiMsk = GetVarMtrrHiMsk (&(MemPtr->DiesPerSystem->LogicalCpuid), &(MemPtr->StdHeader));

  //
  // Allocate buffer for DCT_STRUCTs and CH_DEF_STRUCTs
  //
  AllocHeapParams.RequestedBufferSize = MAX_DCTS_PER_NODE_CZ * (
                                          sizeof (DCT_STRUCT) + (
                                            MAX_CHANNELS_PER_DCT_CZ * (sizeof (CH_DEF_STRUCT) + sizeof (MEM_PS_BLOCK) + sizeof (CH_TIMING_STRUCT))
                                          )
                                        );
  AllocHeapParams.BufferHandle = GENERATE_MEM_HANDLE (ALLOC_DCT_STRUCT_HANDLE, NodeID, 0, 0);
  AllocHeapParams.Persist = HEAP_LOCAL_CACHE;
  if (HeapAllocateBuffer (&AllocHeapParams, &MemPtr->StdHeader) != AGESA_SUCCESS) {
    PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_DCT_STRUCT_AND_CH_DEF_STRUCTs, NBPtr->Node, 0, 0, 0, &MemPtr->StdHeader);
    SetMemError (AGESA_FATAL, MCTPtr);
    ASSERT(FALSE); // Could not allocate buffer for DCT_STRUCTs and CH_DEF_STRUCTs
    return FALSE;
  }

  MCTPtr->DctCount = MAX_DCTS_PER_NODE_CZ;
  MCTPtr->DctData = (DCT_STRUCT *) AllocHeapParams.BufferPtr;
  AllocHeapParams.BufferPtr += MAX_DCTS_PER_NODE_CZ * sizeof (DCT_STRUCT);
  for (Dct = 0; Dct < MAX_DCTS_PER_NODE_CZ; Dct++) {
    MCTPtr->DctData[Dct].Dct = Dct;
    MCTPtr->DctData[Dct].ChannelCount = MAX_CHANNELS_PER_DCT_CZ;
    MCTPtr->DctData[Dct].ChData = (CH_DEF_STRUCT *) AllocHeapParams.BufferPtr;
    MCTPtr->DctData[Dct].ChData[0].Dct = Dct;
    AllocHeapParams.BufferPtr += MAX_CHANNELS_PER_DCT_CZ * sizeof (CH_DEF_STRUCT);
    MCTPtr->DctData[Dct].TimingsMemPs1 = (CH_TIMING_STRUCT *) AllocHeapParams.BufferPtr;
    AllocHeapParams.BufferPtr += MAX_CHANNELS_PER_DCT_CZ * sizeof (CH_TIMING_STRUCT);
  }
  NBPtr->PSBlock = (MEM_PS_BLOCK *) AllocHeapParams.BufferPtr;

  //
  // Initialize Socket List
  //
  for (Dct = 0; Dct < MAX_DCTS_PER_NODE_CZ; Dct++) {
    MemPtr->SocketList[MCTPtr->SocketId].ChannelPtr[(MCTPtr->DieId * 2) + Dct] = &(MCTPtr->DctData[Dct].ChData[0]);
    MemPtr->SocketList[MCTPtr->SocketId].TimingsPtr[(MCTPtr->DieId * 2) + Dct] = &(MCTPtr->DctData[Dct].Timings);
    MCTPtr->DctData[Dct].ChData[0].ChannelID = (MCTPtr->DieId * 2) + Dct;
  }
  MemNInitNBDataCZ (NBPtr);

  //FeatPtr->InitEarlySampleSupport (NBPtr);
  MemNInitEarlySampleSupportCZ (NBPtr);

  NBPtr->FeatPtr = FeatPtr;

  //
  // Calculate SPD Offsets per channel and assign pointers to the data.  At this point, we calculate the Node-Dct-Channel
  // centric offsets and store the pointers to the first DIMM of each channel in the Channel Definition struct for that
  // channel.  This pointer is then used later to calculate the offsets to be used for each logical dimm once the
  // dimm types(QR or not) are known. This is done in the Technology block constructor.
  //
  // Calculate the SpdSocketIndex separately from the SpdChannelIndex.
  // This will facilitate modifications due to some processors that might
  // map the DCT-CHANNEL differently.
  //
  SpdSocketIndex = GetSpdSocketIndex (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr->MCTPtr->SocketId, &MemPtr->StdHeader);
  //
  // Traverse the Dct/Channel structures
  //
  for (Dct = 0; Dct < MAX_DCTS_PER_NODE_CZ; Dct++) {
    for (Channel = 0; Channel < MAX_CHANNELS_PER_DCT_CZ; Channel++) {

      NBPtr->MCTPtr->DctData[Dct].ChData[Channel].ColumnCount = MAX_DELAYS;

      //
      // Calculate the number of Dimms on this channel using the
      //   die/dct/channel to Socket/channel conversion.
      //
      SpdChannelIndex = GetSpdChannelIndex (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                            NBPtr->MCTPtr->SocketId,
                                            MemNGetSocketRelativeChannelNb (NBPtr, Dct & 1, Channel),
                                            &MemPtr->StdHeader);
      NBPtr->MCTPtr->DctData[Dct].ChData[Channel].SpdPtr = &(MemPtr->SpdDataStructure[SpdSocketIndex + SpdChannelIndex]);
    }
  }

  //
  // Initialize Dct and DctCfgSel bit
  //
  MemNSetBitFieldNb (NBPtr, BFDctCfgSel, 0);
  MemNSwitchDCTNb (NBPtr, 0);

  return TRUE;
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
MemNInitNBDataCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;

  NBPtr->DctCachePtr = NBPtr->DctCache;
  NBPtr->PsPtr = NBPtr->PSBlock;
  MemNInitNBRegTableCZ (NBPtr, NBPtr->NBRegTable);
  NBPtr->Node = ((UINT8) NBPtr->PciAddr.Address.Device) - 24;
  NBPtr->Dct = 0;
  NBPtr->Channel = 0;
  NBPtr->DctCount = MAX_DCTS_PER_NODE_CZ;
  NBPtr->ChannelCount = MAX_CHANNELS_PER_DCT_CZ;
  NBPtr->NodeCount = MAX_NODES_SUPPORTED_CZ;

  NBPtr->MemCleared = FALSE;
  NBPtr->StartupSpeed = DDR667_FREQUENCY;
  NBPtr->M1Speed = NBPtr->StartupSpeed;
  NBPtr->DefDctSelIntLvAddr = 4;
  NBPtr->NbFreqChgState = 0;
  NBPtr->NbPsCtlReg = 0;
  NBPtr->CsRegMsk = 0x7FF8FFE0;
  NBPtr->MemPstate = MEMORY_PSTATE0;
  NBPtr->MemPstateStage = MEMORY_PSTATE_1ST_STAGE;
  NBPtr->CsPerChannel = MAX_CS_PER_CHANNEL_CZ;

  //PerRankTimingEn is always set to 0 which force CsPerDelay = 2.
  NBPtr->CsPerDelay = 2;

  // Legacy settings, can probably be removed
  NBPtr->Ganged = FALSE;
  NBPtr->PosTrnPattern = POS_PATTERN_256B;
  NBPtr->RdDqsDlyRetrnStat = RDDQSDLY_RTN_NEEDED;
  NBPtr->RcvrEnDlyLimit = 0x1FF;
  NBPtr->FreqChangeParam = NULL;
  NBPtr->MaxRxEnSeedTotal = 0x1FF;
  NBPtr->MinRxEnSeedGross = 0;

  LibAmdMemFill (NBPtr->DctCache, 0, sizeof (NBPtr->DctCache), &NBPtr->MemPtr->StdHeader);
  MemNInitNBDataNb (NBPtr);

  // ---------------------------------------------------------------------------
  // Common functions
  // ---------------------------------------------------------------------------
  NBPtr->MemNCmnGetSetFieldNb = MemNCmnGetSetFieldCZ;
  NBPtr->SetEccSymbolSize = MemNSetEccSymbolSizeNb;
  NBPtr->PollBitField = MemNPollBitFieldNb;
  NBPtr->BrdcstCheck = MemNBrdcstCheckNb;
  NBPtr->BrdcstSet = MemNBrdcstSetNb;
  NBPtr->GetTrainDly = MemNGetTrainDlyNb;
  NBPtr->SetTrainDly = MemNSetTrainDlyNb;
  NBPtr->MemNcmnGetSetTrainDly = MemNcmnGetSetTrainDlyCZ;
  NBPtr->StitchMemory = MemNStitchMemoryNb;
  NBPtr->DisableDCT = MemNDisableDctCZ;
  NBPtr->HtMemMapInit = MemNHtMemMapCZ;
  NBPtr->SyncAddrMapToAllNodes = (VOID (*) (MEM_NB_BLOCK *)) memDefRet;
  NBPtr->CpuMemTyping = MemNCPUMemTypingNb;

  // ---------------------------------------------------------------------------
  // Misc functions
  // ---------------------------------------------------------------------------
  NBPtr->GetSocketRelativeChannel = MemNGetSocketRelativeChannelNb;
  NBPtr->MemNPlatformSpecificFormFactorInitNb = (BOOLEAN (*) (MEM_NB_BLOCK *)) memDefRet;

  NBPtr->SyncTargetSpeed = MemNSyncTargetSpeedNb;
  NBPtr->MemNCapSpeedBatteryLife = MemNCapSpeedBatteryLifeCZ;
  NBPtr->ProgramCycTimings = (VOID (*) (struct _MEM_NB_BLOCK *NBPtr)) memDefaultUndefined;  // Must be redefined per technology.

  NBPtr->PlatformSpec = (BOOLEAN (*) (MEM_NB_BLOCK *)) memDefRet;

  NBPtr->GetMemClkFreqInCurrentContext = MemNGetMemClkFreqInCurrentContextCZ;
  NBPtr->ProgramNbPsDependentRegs = MemNProgramNbPstateDependentRegistersCZ;

  NBPtr->GetUmaSize = MemNGetUmaSizeCZ;
  NBPtr->UMAMemTyping = MemNUMAMemTypingNb;

  NBPtr->MemNDisableScrubber = MemNDisableScrubberCZ;
  NBPtr->MemNRestoreScrubber = MemNRestoreScrubberCZ;
  NBPtr->MemNSetEccExclusionRange = MemNSetEccExclusionRangeUnb;
  NBPtr->MemNDisableMemClk = MemNDisableMemClkUnb;
  NBPtr->MemNTristateUnusedChipSelects = MemNTristateUnusedChipSelectsNb;
  NBPtr->MemS3PspDetect = MemS3PspDetectionCZ;
  NBPtr->MemS3PspPlatformSecureBootEn = MemS3PspPlatformSecureBootEnCZ;
  NBPtr->MemRunningOnPsp = MemRunningOnPspCZ;
  NBPtr->GetCSIntLvAddr = (VOID (*) (struct _MEM_NB_BLOCK *NBPtr, UINT8 BankAddrMap, UINT8 *LowBit, UINT8 *HiBit)) memDefaultUndefined;  // Must be redefined per technology.

  // ---------------------------------------------------------------------------
  // Training functions
  // ---------------------------------------------------------------------------
  NBPtr->WritePattern = MemNContWritePatternUnb;
  NBPtr->ReadPattern = MemNContReadPatternUnb;
  NBPtr->FlushPattern = (VOID (*) (MEM_NB_BLOCK *, UINT32, UINT16)) memDefRet;
  NBPtr->TrainingPatternInit = (AGESA_STATUS (*) (MEM_NB_BLOCK *)) memDefRetSuccess;
  NBPtr->TrainingPatternFinalize = (AGESA_STATUS (*) (MEM_NB_BLOCK *)) memDefRetSuccess;
  NBPtr->CompareTestPattern = MemNCompareTestPatternUnb;
  NBPtr->GetSysAddr = (BOOLEAN (*) (MEM_NB_BLOCK *, UINT8, UINT32 *)) memDefTrue;
  NBPtr->getMaxLatParams = MemNGetMaxLatParamsCZ;
  NBPtr->WaitXMemClks = MemNWaitXMemClksNb;

  NBPtr->MemNGetMemoryWidth = MemNGetMemoryWidthUnb;

  // ---------------------------------------------------------------------------
  // Family specific flags
  // ---------------------------------------------------------------------------
  NBPtr->IsSupported[CheckFindPSOverideWithSocket] = TRUE;
  NBPtr->IsSupported[EccByteTraining] = TRUE;
  NBPtr->IsSupported[DqsRoutingTypeDependence] = TRUE;

  // ---------------------------------------------------------------------------
  // Family specific hooks
  // ---------------------------------------------------------------------------
  NBPtr->FamilySpecificHook[DCTSelectSwitch] = MemNDctCfgSelectCZ;
  NBPtr->FamilySpecificHook[SetupHwTrainingEngine] = MemNSetupHwTrainingEngineUnb;
  NBPtr->FamilySpecificHook[ReleaseNbPstate] = MemNReleaseNbPstateCZ;
  NBPtr->FamilySpecificHook[FixupUmaInfo] = MemNFixupUmaInfoCZ;

  NBPtr->FamilySpecificHook[DisableMemHoleMapping] = MemNDisableMemHoleMappingCZ;
  NBPtr->FamilySpecificHook[RestoreMemHoleMapping] = MemNRestoreMemHoleMappingCZ;
  NBPtr->FamilySpecificHook[DramScrubErratum792] = MemNDramScrubErratum792CZ;
  NBPtr->FamilySpecificHook[GetDdrMaxRate] = MemNGetDdrMaxRateCZ;
  // ---------------------------------------------------------------------------
  // Initialize PS block's functions
  // ---------------------------------------------------------------------------
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->PSBlock[Dct].MemPGetPORFreqLimit = MemNGetPORFreqLimitTblDrvNb;
    NBPtr->PSBlock[Dct].MemPDoPs = (BOOLEAN (*) (MEM_NB_BLOCK *)) memDefRet;
    MemNSwitchDCTNb (NBPtr, Dct);
    NBPtr->DCTPtr->Timings.MaxRdLat0 = 0x3FF;
    NBPtr->DCTPtr->Timings.MaxRdLat1 = 0x3FF;
    NBPtr->DCTPtr->Timings.MaxRdLat2 = 0x3FF;
    NBPtr->DCTPtr->Timings.MaxRdLat3 = 0x3FF;
  }
  // ---------------------------------------------------------------------------
  // Default DQS routing type set for backward compatibility
  // ---------------------------------------------------------------------------
  if (MemNGetPackageTypeCZ (NBPtr) == CZ_FP4 || MemNGetPackageTypeCZ (NBPtr) == CZ_FM2r2) {
    NBPtr->DqsRoutingType = DQS_ROUTING_TREE;
  } else {
    NBPtr->DqsRoutingType = DQS_ROUTING_DAISY_CHAIN;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes the default values in the MEM_DATA_STRUCT
 *
 *   NOTE: This function must first verify the NB Family.
 *
 *     @param[in,out]   *MemPtr  - Pointer to the MEM_DATA_STRUCT
 *
 */
VOID
MemNInitDefaultsCZ (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  //CPU_LOGICAL_ID LogicalId;
  ASSERT (MemPtr != NULL);

  // Only initialize on CZ processors, otherwise exit.
  // No longer needed
  //CommonServices->GetLogicalIdOfCurrentCore (&LogicalId, &(MemPtr->StdHeader));
  //if (!((LogicalId.Revision & AMD_F15_CZ_ALL) != 0)) {
  //  return;
  //}

  //
  // DllPDBypassMode
  //
  MemPtr->ParameterListPtr->EnableDllPDBypassMode = FALSE;

  //
  // AMP
  //
  MemPtr->ParameterListPtr->AmpEnable = FALSE;
  MemPtr->ParameterListPtr->AmpWarningMsgEnable = FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Get Carrizo package type.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          The package type
 *
 */

CZ_PACKAGE_TYPE
MemNGetPackageTypeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CPUID_DATA CpuId;
  UINT8 RegValue;
  CZ_PACKAGE_TYPE PkgType;

  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  RegValue = (UINT8) (CpuId.EBX_Reg >> 28) & 0xF; // bit 31:28
  ///@todo - update the PkgType once it is reflected in BKDG
  if (RegValue == 0) {
    PkgType = CZ_FP4;
  } else if (RegValue == 2) {
    PkgType = CZ_AM4;
  } else if (RegValue == 3) {
    PkgType = CZ_FM2r2;
  } else {
    PkgType = UNKNOWN;
  }

  return PkgType;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Clock and power gate unused DCTs
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNClockAndPowerGateUnusedDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MemNSetBitFieldNb (NBPtr, BFDctClkGateEn, 0);
  MemNSetBitFieldNb (NBPtr, BFDctPwrGateEn, 0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Exclude DIMM failed PMU training.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNDimmExcludesCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;
  BOOLEAN ErrorRecovery;

  ErrorRecovery = TRUE;

  IDS_OPTION_HOOK (IDS_MEM_ERROR_RECOVERY, &ErrorRecovery, &NBPtr->MemPtr->StdHeader);

  if (ErrorRecovery && (NBPtr->MCTPtr->ChannelTrainFail != 0)) {
    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      MemNSwitchDCTNb (NBPtr, Dct);

      // Disable the channel when CS fails PMU training.
      if (NBPtr->DCTPtr->Timings.CsTrainFail != 0) {
        IDS_HDT_CONSOLE (MEM_FLOW, "\tDct %d excluded due to PMU training failure on CS: %x\n", Dct, NBPtr->DCTPtr->Timings.CsTrainFail);
        NBPtr->DCTPtr->Timings.CsTestFail = NBPtr->DCTPtr->Timings.CsPresent;
        MemNDisableDctCZ (NBPtr);
      }

      MemNStitchMemoryNb (NBPtr);
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This is function gets the erratum 792 for CZ to disable ScrubRate and ScrubRedir
 *
 *     @param[in,out]   *NBPtr      - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *OptParam   - Pointer to Optional Parameter
 *
 */
BOOLEAN
MemNDramScrubErratum792CZ (
  IN OUT   MEM_NB_BLOCK  *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  MemNSetBitFieldNb (NBPtr, BFDramScrub, 0);
  MemNSetBitFieldNb (NBPtr, BFScrubReDirEn, 0);
  return TRUE;
}

