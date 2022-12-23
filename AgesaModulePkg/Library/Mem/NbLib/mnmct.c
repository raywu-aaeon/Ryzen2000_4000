/* $NoKeywords:$ */
/**
 * @file
 *
 * mnmct.c
 *
 * Northbridge Common MCT supporting functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
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
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
//#include "cpuFeatures.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NBLIB_MNMCT_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define NBCOF_MHZ(NbFid, NbDid) (100 * ((NbFid + 4) / (1 << NbDid)));
#define GROSS_DELAY_UNB   5
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
BOOLEAN
STATIC
MemNSetMTRRrangeNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 Base,
  IN OUT   UINT32 *LimitPtr,
  IN       UINT32 MtrrAddr,
  IN       UINT8 MtrrType
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Get max frequency from OEM platform definition, from
 *     any user override (limiting) of max frequency, and
 *     from any Si Revision Specific information.  Return
 *     the least of these three in DIE_STRUCT.Timings.TargetSpeed.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSyncTargetSpeedNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8  Dct;
  UINT8  Channel;
  UINT16 MinSpeed;
  UINT16 DdrMaxRate;
  UINT32 *ChnlTmgMod;
  UINT32 Mode[MAX_CHANNELS_PER_SOCKET];
  UINT32 MemClkFreq;
  UINT32 ProposedFreq;
  DCT_STRUCT *DCTPtr;
  MEM_PARAMETER_STRUCT *RefPtr;

  RefPtr = NBPtr->MemPtr->ParameterListPtr;

  ASSERT (NBPtr->DctCount <= sizeof (Mode));
  MinSpeed = 16000;
  DdrMaxRate = 16000;

  //
  // Check maximum DRAM data rate that the processor is designed to support.
  //
  MemNGetMaxDdrRateUnb (NBPtr, (VOID *) &DdrMaxRate);
  IDS_OPTION_HOOK (IDS_SKIP_FUSED_MAX_RATE, &DdrMaxRate, &NBPtr->MemPtr->StdHeader);

  IDS_HDT_CONSOLE(MEM_FLOW, "\tPlatform MemoryBusFrequencyLimit = %d\n", RefPtr->MemoryBusFrequencyLimit);
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);
    DCTPtr = NBPtr->DCTPtr;

    // Check if input user time mode is valid or not
    ASSERT ((NBPtr->RefPtr->UserTimingMode == TIMING_MODE_SPECIFIC) ||
        (NBPtr->RefPtr->UserTimingMode == TIMING_MODE_LIMITED) ||
        (NBPtr->RefPtr->UserTimingMode == TIMING_MODE_AUTO));
    Mode[Dct] = NBPtr->RefPtr->UserTimingMode;
    // Check if input clock value is valid or not
    ASSERT ((NBPtr->ChannelPtr->TechType == DDR3_TECHNOLOGY) ?
            (NBPtr->RefPtr->MemClockValue >= DDR667_FREQUENCY) :
           ((NBPtr->ChannelPtr->TechType == DDR4_TECHNOLOGY) ?
            (NBPtr->RefPtr->MemClockValue >= DDR1333_FREQUENCY) :
            (NBPtr->RefPtr->MemClockValue <= DDR1066_FREQUENCY)));
    MemClkFreq = NBPtr->RefPtr->MemClockValue;
    IDS_HDT_CONSOLE(MEM_FLOW, "\tDefault MemClkFreq = %d\n", MemClkFreq);
    if (DCTPtr->Timings.DctDimmValid != 0) {
      IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);

      Channel = MemNGetSocketRelativeChannelNb (NBPtr, Dct, 0);
      ChnlTmgMod = (UINT32 *) FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_BUS_SPEED, NBPtr->MCTPtr->SocketId, Channel, 0,
                                                                    &(NBPtr->MCTPtr->LogicalCpuid), &(NBPtr->MemPtr->StdHeader));
      if (ChnlTmgMod != NULL) {
        // Check if input user timing mode is valid or not
        ASSERT ((ChnlTmgMod[0] == TIMING_MODE_SPECIFIC) || (ChnlTmgMod[0] == TIMING_MODE_LIMITED) ||
          (ChnlTmgMod[0] != TIMING_MODE_AUTO));
        if (ChnlTmgMod[0] != TIMING_MODE_AUTO) {
          Mode[Dct] = ChnlTmgMod[0];
          // Check if input clock value is valid or not
          ASSERT ((NBPtr->ChannelPtr->TechType == DDR3_TECHNOLOGY) ?
            (ChnlTmgMod[1] >= DDR667_FREQUENCY) :
           ((NBPtr->ChannelPtr->TechType == DDR4_TECHNOLOGY) ?
            (ChnlTmgMod[1] >= DDR1333_FREQUENCY) :
            (ChnlTmgMod[1] <= DDR1066_FREQUENCY)));
          MemClkFreq = ChnlTmgMod[1];
        }
      }

      ProposedFreq = RefPtr->MemoryBusFrequencyLimit;
      if (Mode[Dct] == TIMING_MODE_LIMITED) {
        if (MemClkFreq < ProposedFreq) {
          ProposedFreq = MemClkFreq;
        }
      } else if (Mode[Dct] == TIMING_MODE_SPECIFIC) {
        ProposedFreq = MemClkFreq;
      }

      if (Mode[Dct] == TIMING_MODE_SPECIFIC) {
        DCTPtr->Timings.TargetSpeed = (UINT16) ProposedFreq;
      } else {
        // "limit" mode
        if (DCTPtr->Timings.TargetSpeed > ProposedFreq) {
          DCTPtr->Timings.TargetSpeed = (UINT16) ProposedFreq;
        }
      }
      IDS_HDT_CONSOLE(MEM_FLOW, "\tMemClkFreq after platform limits applied =  %d\n", DCTPtr->Timings.TargetSpeed);
      IDS_SKIP_HOOK (IDS_MEM_MCLK_ABOVE_NCLK, NBPtr, &NBPtr->MemPtr->StdHeader) {
        if (DCTPtr->Timings.TargetSpeed > DdrMaxRate) {
          if (Mode[Dct] == TIMING_MODE_SPECIFIC) {
            PutEventLog (AGESA_ALERT, MEM_ALERT_USER_TMG_MODE_OVERRULED, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
            SetMemError (AGESA_ALERT, NBPtr->MCTPtr);
          }
          DCTPtr->Timings.TargetSpeed = DdrMaxRate;
          IDS_HDT_CONSOLE(MEM_FLOW, "\tLimiting MemClkFreq to DdrMaxRate of %d\n", DdrMaxRate);
        }
      }

      IDS_SKIP_HOOK (IDS_POR_MEM_FREQ, NBPtr, &NBPtr->MemPtr->StdHeader) {
        //
        //Call Platform POR Frequency Override
        //
        if (!MemProcessConditionalOverrides (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr, PSO_ACTION_SPEEDLIMIT, ALL_DIMMS)) {
          //
          // Get the POR frequency limit
          //
          NBPtr->PsPtr->MemPGetPORFreqLimit (NBPtr);
        }
      }
      IDS_OPTION_HOOK (IDS_STRETCH_FREQUENCY_LIMIT, NBPtr, &NBPtr->MemPtr->StdHeader);
      if (MinSpeed > DCTPtr->Timings.TargetSpeed) {
        MinSpeed = DCTPtr->Timings.TargetSpeed;
      }
    }
  }

  //
  // Limit Startup Speed and M1 Speed
  //
  if (MinSpeed < NBPtr->StartupSpeed) {
    NBPtr->StartupSpeed = MinSpeed;
  }
  if (MinSpeed < NBPtr->M1Speed) {
    NBPtr->M1Speed = MinSpeed;
  }
  //
  // Sync all DCTs to the same speed
  //
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);
    NBPtr->DCTPtr->Timings.TargetSpeed = MinSpeed;
  }
  IDS_HDT_CONSOLE(MEM_FLOW, "\n\t\tLowest supported MemClkFreq for all channels: %d\n", MinSpeed);

  IDS_SKIP_HOOK (IDS_MEM_MCLK_ABOVE_NCLK, NBPtr, &NBPtr->MemPtr->StdHeader) {
    NBPtr->MemNCapSpeedBatteryLife (NBPtr);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     Program system DRAM map to this node
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSyncAddrMapToAllNodesNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Node;
  UINT32 NodeSysBase;
  UINT32 NodeSysLimit;
  UINT8  WeReMask;
  MEM_PARAMETER_STRUCT *RefPtr;

  RefPtr = NBPtr->RefPtr;
  for (Node = 0; Node < NBPtr->NodeCount; Node++) {
    NodeSysBase = NBPtr->SharedPtr->NodeMap[Node].SysBase;
    NodeSysLimit = NBPtr->SharedPtr->NodeMap[Node].SysLimit;
    if (NBPtr->SharedPtr->NodeMap[Node].IsValid) {
      WeReMask = 3;
    } else {
      WeReMask = 0;
    }
    // Set the Dram base and set the WE and RE flags in the base.
    MemNSetBitFieldNb (NBPtr, BFDramBaseReg0 + Node, (NodeSysBase << 8) | WeReMask);
    MemNSetBitFieldNb (NBPtr, BFDramBaseHiReg0 + Node, NodeSysBase >> 24);
    // Set the Dram limit and set DstNode.
    MemNSetBitFieldNb (NBPtr, BFDramLimitReg0 + Node, (NodeSysLimit << 8) | Node);
    MemNSetBitFieldNb (NBPtr, BFDramLimitHiReg0 + Node, NodeSysLimit >> 24);

    if (RefPtr->GStatus[GsbHWHole]) {
      MemNSetBitFieldNb (NBPtr, BFDramMemHoistValid, 1);
      MemNSetBitFieldNb (NBPtr, BFDramHoleBase, (RefPtr->HoleBase >> 8));
    }
  }

  NBPtr->FamilySpecificHook[InitExtMMIOAddr] (NBPtr, NULL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function calculates the critical delay difference (CDD)
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       TrnDlyType1 - Type of first Gross Delay parameter
 *     @param[in]       TrnDlyType2 - Type of second Gross Delay parameter
 *     @param[in]       SameDimm - CDD of same DIMMs
 *     @param[in]       DiffDimm - CDD of different DIMMs
 *
 *     @return          CDD term - in 1/2 MEMCLK
 */
INT16
MemNCalcCDDNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       TRN_DLY_TYPE TrnDlyType1,
  IN       TRN_DLY_TYPE TrnDlyType2,
  IN       BOOLEAN SameDimm,
  IN       BOOLEAN DiffDimm
  )
{
  INT16 CDD;
  INT16 CDDtemp;
  UINT16 TrnDly1;
  UINT16 TrnDly2;
  UINT8 i;
  UINT8 j;
  UINT8 ByteLane;
  UINT16 CsEnabled;
  BOOLEAN SameDlyType;

  SameDlyType = (BOOLEAN) (TrnDlyType1 == TrnDlyType2);
  CsEnabled = NBPtr->DCTPtr->Timings.CsEnabled;
  CDD = -127;
  // If the two delay types compared are the same type, then no need to compare the same
  // pair twice. Adjustments are made in the upper bound and lower bound of the loop to
  // handle this.
  for (i = 0; i < (SameDlyType ? (NBPtr->CsPerChannel - NBPtr->CsPerDelay) : NBPtr->CsPerChannel); i = i + NBPtr->CsPerDelay) {
    if ((CsEnabled & ((UINT16) ((NBPtr->CsPerDelay == 2) ? 3 : 1) << i)) != 0) {
      for (j = SameDlyType ? (i + NBPtr->CsPerDelay) : 0; j < NBPtr->CsPerChannel; j = j + NBPtr->CsPerDelay) {
        if (((CsEnabled & ((UINT16) ((NBPtr->CsPerDelay == 2)? 3 : 1) << j)) != 0) &&
            ((SameDimm && ((i / 2) == (j / 2))) || (DiffDimm && ((i / 2) != (j / 2))))) {
          for (ByteLane = 0; ByteLane < ((NBPtr->MCTPtr->Status[SbEccDimms] && NBPtr->IsSupported[EccByteTraining]) ? 9 : 8); ByteLane++) {
            TrnDly1 = GetTrainDlyFromHeapNb (NBPtr, TrnDlyType1, DIMM_BYTE_ACCESS (i / NBPtr->CsPerDelay, ByteLane)) >> GROSS_DELAY_UNB;  // Gross delay only
            TrnDly2 = GetTrainDlyFromHeapNb (NBPtr, TrnDlyType2, DIMM_BYTE_ACCESS (j / NBPtr->CsPerDelay, ByteLane)) >> GROSS_DELAY_UNB;  // Gross delay only

            CDDtemp = TrnDly1 - TrnDly2;
            // If the 2 delay types to be compared are the same, then keep the absolute difference
            if ((SameDlyType) && (CDDtemp < 0)) {
              CDDtemp = (-CDDtemp);
            }

            CDD = (CDD < CDDtemp) ? CDDtemp : CDD;
          }
        }
      }
    }
  }

  return CDD;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets DQS timing from data saved in heap.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   TrnDlyType - type of delay to be set
 *     @param[in]   Drbn - encoding of Dimm-Rank-Byte-Nibble to be accessed
 *                  (use either DIMM_BYTE_ACCESS(dimm,byte) or CS_NBBL_ACCESS(cs,nibble) to use this encoding
 *
 *     @return      value of the target timing.
 */
UINT16
GetTrainDlyFromHeapNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       TRN_DLY_TYPE TrnDlyType,
  IN       DRBN Drbn
  )
{
  UINT8 Dimm;
  UINT8 Byte;
  UINT16 TrainDly;
  CH_DEF_STRUCT *ChannelPtr;
  MEM_TECH_BLOCK *TechPtr;

  Dimm = DRBN_DIMM (Drbn);
  Byte = DRBN_BYTE (Drbn);
  ChannelPtr = NBPtr->ChannelPtr;
  TechPtr = NBPtr->TechPtr;

  ASSERT (Dimm < (NBPtr->CsPerChannel / NBPtr->CsPerDelay));
  ASSERT (Byte <= ECC_DLY);

  if (NBPtr->MemPstate == MEMORY_PSTATE1) {
    switch (TrnDlyType) {
    case AccessRcvEnDly:
      TrainDly = ChannelPtr->RcvEnDlysMemPs1[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    case AccessWrDqsDly:
      TrainDly = ChannelPtr->WrDqsDlysMemPs1[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    case AccessWrDatDly:
      TrainDly = ChannelPtr->WrDatDlysMemPs1[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    case AccessRdDqsDly:
      TrainDly = ChannelPtr->RdDqsDlysMemPs1[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    default:
      TrainDly = 0;
      IDS_ERROR_TRAP;
    }
  } else {
    switch (TrnDlyType) {
    case AccessRcvEnDly:
      TrainDly = ChannelPtr->RcvEnDlys[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    case AccessWrDqsDly:
      TrainDly = ChannelPtr->WrDqsDlys[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    case AccessWrDatDly:
      TrainDly = ChannelPtr->WrDatDlys[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    case AccessRdDqsDly:
      TrainDly = ChannelPtr->RdDqsDlys[Dimm * TechPtr->DlyTableWidth () + Byte];
      break;
    default:
      TrainDly = 0;
      IDS_ERROR_TRAP;
    }
  }

  return TrainDly;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets the fixed MTRRs for common legacy ranges.
 *   It sets TOP_MEM and TOM2 and some variable MTRRs with WB Uncacheable type.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - An Error value lower than AGESA_FATAL may have occurred
 *     @return          FALSE - An Error value greater than or equal to AGESA_FATAL may have occurred
 */

BOOLEAN
MemNCPUMemTypingNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 Bottom32bIO;
  UINT32 Bottom40bIO;
  UINT32 Cache32bTOP;
  S_UINT64 SMsr;

  MEM_DATA_STRUCT *MemPtr;
  MEM_PARAMETER_STRUCT *RefPtr;
  RefPtr = NBPtr->RefPtr;
  MemPtr = NBPtr->MemPtr;

  //
  //======================================================================
  // Set temporary top of memory from Node structure data.
  // Adjust temp top of memory down to accommodate 32-bit IO space.
  //======================================================================
  //Bottom40bIO=top of memory, right justified 16 bits  (defines dram versus IO space type)
  //Bottom32bIO=sub 4GB top of memory, right justified 16 bits (defines dram versus IO space type)
  //Cache32bTOP=sub 4GB top of WB cacheable memory, right justified 16 bits
  //
  if (RefPtr->HoleBase != 0) {
    Bottom32bIO = RefPtr->HoleBase;
  } else if (RefPtr->BottomIo != 0) {
    Bottom32bIO = (UINT32)RefPtr->BottomIo << (24 - 16);
  } else {
    Bottom32bIO = (UINT32)1 << (24 - 16);
  }

  Cache32bTOP = RefPtr->SysLimit + 1;
  if (Cache32bTOP < _4GB_RJ16) {
    Bottom40bIO = 0;
    if (Bottom32bIO >= Cache32bTOP) {
      Bottom32bIO = Cache32bTOP;
    }
  } else {
    Bottom40bIO = Cache32bTOP;
  }

  Cache32bTOP = Bottom32bIO;


  //
  //======================================================================
  // Set default values for CPU registers
  //======================================================================
  //
  SMsr.Value64 = AsmReadMsr64 (SYS_CFG);
  SMsr.Values32.lo |= 0x1C0000;       // turn on modification enable bit and
                                      // mtrr enable bits
  AsmWriteMsr64 (SYS_CFG, SMsr.Value64);

  SMsr.Value64 = 0x1E1E1E1E1E1E1E1E;
  AsmWriteMsr64 (0x250, SMsr.Value64);      // 0 - 512K = WB Mem
  AsmWriteMsr64 (0x258, SMsr.Value64);      // 512K - 640K = WB Mem

  //
  //======================================================================
  // Set variable MTRR values
  //======================================================================
  //
  MemNSetMTRRrangeNb (NBPtr, 0, &Cache32bTOP, 0x200, 6);

  RefPtr->Sub4GCacheTop = Cache32bTOP << 16;

  //
  //======================================================================
  // Set TOP_MEM and TOM2 CPU registers
  //======================================================================
  //
  SMsr.Values32.hi = Bottom32bIO >> (32 - 16);
  SMsr.Values32.lo = Bottom32bIO << 16;
  AsmWriteMsr64 (TOP_MEM, SMsr.Value64);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tTOP_MEM:  %08x0000\n", Bottom32bIO);

  if (Bottom40bIO) {
    SMsr.Values32.hi = Bottom40bIO >> (32 - 16);
    SMsr.Values32.lo = Bottom40bIO << 16;
  } else {
    SMsr.Values32.hi = 0;
    SMsr.Values32.lo = 0;
  }
  AsmWriteMsr64 (TOP_MEM2, SMsr.Value64);

  SMsr.Value64 = AsmReadMsr64 (SYS_CFG);
  if (Bottom40bIO) {
    RefPtr->Sub1THoleBase = Bottom40bIO;
    IDS_HDT_CONSOLE (MEM_FLOW, "\tTOP_MEM2: %08x0000\n", Bottom40bIO);
    IDS_HDT_CONSOLE (MEM_FLOW, "\tSub1THoleBase: %08x0000\n", RefPtr->Sub1THoleBase);
    // Enable TOM2
    SMsr.Values32.lo |= 0x00600000;
  } else {
    // Disable TOM2
    SMsr.Values32.lo &= ~0x00600000;
  }
  SMsr.Values32.lo &= 0xFFF7FFFF; // turn off modification enable bit
  AsmWriteMsr64 (SYS_CFG, SMsr.Value64);

  return (BOOLEAN) (NBPtr->MCTPtr->ErrCode < AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function runs on the BSP only, it sets the fixed MTRRs for common legacy ranges.
 *   It sets TOP_MEM and TOM2 and some variable MTRRs with WB Uncacheable type.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNUMAMemTypingNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 Bottom32bIO;
  UINT32 Bottom32bUMA;
  UINT32 Cache32bTOP;
  UINT32 Value32;
  UINT8 BitCount;
  UINT8 i;

  MEM_PARAMETER_STRUCT *RefPtr;
  RefPtr = NBPtr->RefPtr;
  BitCount = 0;
  //
  //======================================================================
  // Adjust temp top of memory down to accommodate UMA memory start
  //======================================================================
  // Bottom32bIO=sub 4GB top of memory, right justified 16 bits (defines dram versus IO space type)
  // Cache32bTOP=sub 4GB top of WB cacheable memory, right justified 16 bits
  //
  Bottom32bIO = RefPtr->Sub4GCacheTop >> 16;
  Bottom32bUMA = RefPtr->UmaBase;

  if (Bottom32bUMA < Bottom32bIO) {
    Cache32bTOP = Bottom32bUMA;
    RefPtr->Sub4GCacheTop = Bottom32bUMA << 16;
    //
    //======================================================================
    //Set variable MTRR values
    //======================================================================
    //
    Value32 = Cache32bTOP;
    //Pre-check the bit count of bottom Uma to see if it is potentially running out of Mtrr while typing.
    while (Value32 != 0) {
      i = (UINT8)LowBitSet32 (Value32);
      Value32 &= ~ (1 << i);
      BitCount++;
    }

    if (BitCount > 5) {
      NBPtr->RefPtr->GStatus[GsbMTRRshort] = TRUE;
      MemNSetMTRRUmaRegionUCNb (NBPtr, &Cache32bTOP, &Bottom32bIO);
    } else {
      MemNSetMTRRrangeNb (NBPtr, 0, &Cache32bTOP, 0x200, 6);
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *  Program MTRRs to describe given range as given cache type.  Use MTRR pairs
 *  starting with the given MTRRphys Base address, and use as many as is
 *  required up to (excluding) MSR 020C, which is reserved for OS.
 *
 *  "Limit" in the context of this procedure is not the numerically correct
 *  limit, but rather the Last address+1, for purposes of coding efficiency
 *  and readability.  Size of a region is then Limit-Base.
 *
 *  1. Size of each range must be a power of two
 *  2. Each range must be naturally aligned (Base is same as size)
 *
 *  There are two code paths: the ascending path and descending path (analogous
 *  to bsf and bsr), where the next limit is a function of the next set bit in
 *  a forward or backward sequence of bits (as a function of the Limit).  We
 *  start with the ascending path, to ensure that regions are naturally aligned,
 *  then we switch to the descending path to maximize MTRR usage efficiency.
 *  Base=0 is a special case where we start with the descending path.
 *  Correct Mask for region is 2comp(Size-1)-1,
 *  which is 2comp(Limit-Base-1)-1 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]     Base - Base address[47:16] of specified range.
 *     @param[in]     *LimitPtr - Limit address[47:16] of specified range.
 *     @param[in]     MtrrAddr - address of var MTRR pair to start using.
 *     @param[in]     MtrrType - Cache type for the range.
 *
 *     @return      TRUE - No failure occurred
 *     @return      FALSE - Failure occurred because run out of variable-size MTRRs before completion.
 */

BOOLEAN
STATIC
MemNSetMTRRrangeNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 Base,
  IN OUT   UINT32 *LimitPtr,
  IN       UINT32 MtrrAddr,
  IN       UINT8 MtrrType
  )
{
  S_UINT64 SMsr;
  UINT32 CurBase;
  UINT32 CurLimit;
  UINT32 CurSize;
  UINT32 CurAddr;
  UINT32 Value32;
  UINT64 vMtrrBase;
  UINT64 vMtrrMask;

  CurBase = Base;
  CurLimit = *LimitPtr;
  CurAddr = MtrrAddr;

  while ((CurAddr >= 0x200) && (CurAddr < 0x20F) && (CurBase < *LimitPtr)) {
    vMtrrBase = AsmReadMsr64 (CurAddr);
    vMtrrMask = AsmReadMsr64 (CurAddr + 1);
    if (((vMtrrBase & 7) == 5) && ((vMtrrMask & 0x800) != 0)) {
      // a valid vMTRR setting with WP memory type is ROM cache
      // don't clear this vMTRR
      CurAddr += 2;
    } else {
      CurSize = CurLimit = (UINT32)1 << LowBitSet32 (CurBase);
      CurLimit += CurBase;
      if ((CurBase == 0) || (*LimitPtr < CurLimit)) {
        CurLimit = *LimitPtr - CurBase;
        CurSize = CurLimit = (UINT32)1 << HighBitSet32 (CurLimit);
        CurLimit += CurBase;
      }

      // prog. MTRR with current region Base
      SMsr.Values32.lo = (CurBase << 16) | (UINT32)MtrrType;
      SMsr.Values32.hi = CurBase >> (32 - 16);
      AsmWriteMsr64 (CurAddr, SMsr.Value64);

      // prog. MTRR with current region Mask
      CurAddr++;                              // other half of MSR pair
      Value32 = CurSize - (UINT32)1;
      Value32 = ~Value32;
      SMsr.Values32.hi = (Value32 >> (32 - 16)) & NBPtr->VarMtrrHiMsk;
      SMsr.Values32.lo = (Value32 << 16) | ((UINT32)1 << MTRR_VALID);
      AsmWriteMsr64 (CurAddr, SMsr.Value64);

      CurBase = CurLimit;
      CurAddr++;                              // next MSR pair
    }
  }

  if (CurLimit < *LimitPtr) {
    // Announce failure
    *LimitPtr = CurLimit;
    IDS_ERROR_TRAP;
  }

  SMsr.Value64 = 0;
  while ((CurAddr >= 0x200) && (CurAddr < 0x20F)) {
    vMtrrBase = AsmReadMsr64 (CurAddr);
    vMtrrMask = AsmReadMsr64 (CurAddr + 1);
    if (((vMtrrBase & 7) == 5) && ((vMtrrMask & 0x800) != 0)) {
      // a valid vMTRR setting with WP memory type is ROM cache
      // don't clear this vMTRR
      CurAddr += 2;
    } else {
      // clear vMTRR base
      AsmWriteMsr64 (CurAddr, SMsr.Value64);
      CurAddr++;
      // clear vMTRR mask
      AsmWriteMsr64 (CurAddr, SMsr.Value64);
      CurAddr++;
    }
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     Program one MTRR to describe Uma region as UC cache type if we detect running out of
 *     Mtrr circumstance.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]     *BasePtr - Base address[47:24] of specified range.
 *     @param[in]     *LimitPtr - Limit address[47:24] of specified range.
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemNSetMTRRUmaRegionUCNb  (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 *BasePtr,
  IN OUT   UINT32 *LimitPtr
  )
{
  S_UINT64 SMsr;
  UINT32 Mtrr;
  UINT32 Size;
  UINT32 Value32;

  Size = *LimitPtr - *BasePtr;
  // Check if Size is a power of 2
  if ((Size & (Size - 1)) != 0) {
    for (Mtrr = 0x200; Mtrr < 0x20A; Mtrr += 2) {
      SMsr.Value64 = AsmReadMsr64 (Mtrr + 1);
      if ((SMsr.Values32.lo & ((UINT32) 1 << 11)) == 0) {
        MemNSetMTRRrangeNb (NBPtr, *BasePtr, LimitPtr, Mtrr, 0);
        break;
      }
    }
    if (Mtrr == 0x20A) {
      // Run out of MTRRs
      IDS_ERROR_TRAP;
    }
  } else {
    Mtrr = 0x20A; //Reserved pair of MTRR for UMA region.

    // prog. MTRR with current region Base
    SMsr.Values32.lo = *BasePtr  << 16;
    SMsr.Values32.hi = *BasePtr >> (32 - 16);
    AsmWriteMsr64 (Mtrr, SMsr.Value64);

    // prog. MTRR with current region Mask
    Mtrr++;                              // other half of MSR pair
    Value32 = Size - (UINT32)1;
    Value32 = ~Value32;
    SMsr.Values32.hi = (Value32 >> (32 - 16)) & NBPtr->VarMtrrHiMsk;
    SMsr.Values32.lo = (Value32 << 16) | ((UINT32)1 << MTRR_VALID);
    AsmWriteMsr64 (Mtrr, SMsr.Value64);
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function readjusts TOPMEM and MTRRs after allocating storage for C6
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNC6AdjustMSRs (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 SysLimit;
  UINT32 CurAddr;
  S_UINT64 SMsr;

  SysLimit = NBPtr->RefPtr->SysLimit + 1;
  SMsr.Values32.hi = SysLimit >> (32 - 16);
  SMsr.Values32.lo = SysLimit << 16;
  if (SysLimit < _4GB_RJ16) {
    AsmWriteMsr64 (TOP_MEM, SMsr.Value64);
    IDS_HDT_CONSOLE (MEM_FLOW, "TOP_MEM:  %08x0000\n", SysLimit);
    // If there is no UMA buffer, then set top of cache and MTRR.
    // Otherwise, top of cache and MTRR will be set when UMA buffer is set up.
    if (NBPtr->RefPtr->UmaMode == UMA_NONE) {
      NBPtr->RefPtr->Sub4GCacheTop = (SysLimit << 16);
      // Find unused MTRR to set C6 region to UC
      for (CurAddr = 0x200; CurAddr < 0x20C; CurAddr += 2) {
        SMsr.Value64 = AsmReadMsr64 (CurAddr + 1);
        if ((SMsr.Values32.lo & ((UINT32) 1 << 11)) == 0) {
          // Set region base as TOM
          SMsr.Values32.hi = SysLimit >> (32 - 16);
          SMsr.Values32.lo = SysLimit << 16;
          AsmWriteMsr64 (CurAddr, SMsr.Value64);

          // set region mask to 16MB
          SMsr.Values32.hi = NBPtr->VarMtrrHiMsk;
          SMsr.Values32.lo = 0xFF000800;
          AsmWriteMsr64 (CurAddr + 1, SMsr.Value64);

          break;
        }
      }
    }
  } else {
    AsmWriteMsr64 (TOP_MEM2, SMsr.Value64);
    IDS_HDT_CONSOLE (MEM_FLOW, "TOP_MEM2: %08x0000\n", SysLimit);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function readjusts TOPMEM and MTRRs after allocating storage for C6
 *     and GNB ACP Engine as 32MB.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNC6AndGnbAcpEngineAdjustMSRs (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 SysLimit;
  UINT32 CurAddr;
  S_UINT64 SMsr;

  SysLimit = NBPtr->RefPtr->SysLimit + 1;
  SMsr.Values32.hi = SysLimit >> (32 - 16);
  SMsr.Values32.lo = SysLimit << 16;
  if (SysLimit < _4GB_RJ16) {
    AsmWriteMsr64 (TOP_MEM, SMsr.Value64);
    IDS_HDT_CONSOLE (MEM_FLOW, "TOP_MEM:  %08x0000\n", SysLimit);
    // If there is no UMA buffer, then set top of cache and MTRR.
    // Otherwise, top of cache and MTRR will be set when UMA buffer is set up.
    if (NBPtr->RefPtr->UmaMode == UMA_NONE) {
      NBPtr->RefPtr->Sub4GCacheTop = (SysLimit << 16);
      // Find unused MTRR to set C6 and GNB ACP engine region to UC
      for (CurAddr = 0x200; CurAddr < 0x20C; CurAddr += 2) {
        SMsr.Value64 = AsmReadMsr64 (CurAddr + 1);
        if ((SMsr.Values32.lo & ((UINT32) 1 << 11)) == 0) {
          // Set region base as TOM
          SMsr.Values32.hi = SysLimit >> (32 - 16);
          SMsr.Values32.lo = SysLimit << 16;
          AsmWriteMsr64 (CurAddr, SMsr.Value64);

          // set region mask to 32MB.
          SMsr.Values32.hi = NBPtr->VarMtrrHiMsk;
          SMsr.Values32.lo = 0xFE000800;
          AsmWriteMsr64 (CurAddr + 1, SMsr.Value64);

          break;
        }
      }
    }
  } else {
    AsmWriteMsr64 (TOP_MEM2, SMsr.Value64);
    IDS_HDT_CONSOLE (MEM_FLOW, "TOP_MEM2: %08x0000\n", SysLimit);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Family-specific hook to override the DdrMaxRate value for families with a
 *     non-GH-compatible encoding for BFDdrMaxRate
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *DdrMaxRate - Void pointer to DdrMaxRate.  Used as INT16.
 *
 *     @return          TRUE
 *
 */
BOOLEAN
MemNGetMaxDdrRateUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *DdrMaxRate
  )
{
  UINT8 DdrMaxRateEncoded;

  DdrMaxRateEncoded = (UINT8) MemNGetBitFieldNb (NBPtr, BFDdrMaxRate);
  NBPtr->FamilySpecificHook[GetDdrMaxRate] (NBPtr, &DdrMaxRateEncoded);

  if (DdrMaxRateEncoded == 0) {
    * (UINT16 *) DdrMaxRate = UNSUPPORTED_DDR_FREQUENCY;
  } else {
    * (UINT16 *) DdrMaxRate = MemNGetMemClkFreqUnb (NBPtr, DdrMaxRateEncoded);
  }
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function performs the action after save/restore execution
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  OptParam   - Optional parameter
 *
 *     @return    TRUE
 *
 */

BOOLEAN
MemNAfterSaveRestoreUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  // Sync. up DctCfgSel value with NBPtr->Dct
  MemNSetBitFieldNb (NBPtr, BFDctCfgSel, NBPtr->Dct);

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Get NB operating frequency in Mhz of selected NB Pstate
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *NBPstate - NB Pstate
 *
 *     @return      NB operating frequency value in Mhz.
 */

UINT32
MemNGetNbClkFreqByPstateUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 NBPstate
  )
{
  return NBCOF_MHZ (MemNGetBitFieldNb (NBPtr, BFNbFid0 + NBPstate), MemNGetBitFieldNb (NBPtr, BFNbDid0 + NBPstate));
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Limited the DDR target speed with in MaxDdrRate fused.
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 *     @return    TRUE
 *
 */

VOID
MemNAdjustDdrSpeedUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;
  UINT16 DdrMaxRate;

  IDS_SKIP_HOOK (IDS_MEM_MCLK_ABOVE_NCLK, NBPtr, &NBPtr->MemPtr->StdHeader) {
    DdrMaxRate = 16000;
    MemNGetMaxDdrRateUnb (NBPtr, (VOID *) &DdrMaxRate);

    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      MemNSwitchDCTNb (NBPtr, Dct);
      if (NBPtr->DCTPtr->Timings.TargetSpeed > DdrMaxRate) {
        NBPtr->DCTPtr->Timings.TargetSpeed = DdrMaxRate;
        IDS_HDT_CONSOLE(MEM_FLOW, "\tDct %d: Limiting MemClkFreq to DdrMaxRate of %d\n", Dct, DdrMaxRate);
      }
    }
  }
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

