/* $NoKeywords:$ */
/**
 * @file
 *
 * mnmctcz.c
 *
 * Northbridge CZ MCT supporting functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 312808 $ @e \$Date: 2015-02-11 19:22:11 +0800 (Wed, 11 Feb 2015) $
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
#include "Library/AmdHeapLib.h"
#include "mport.h"
#include "Gnb.h"
#include "mm.h"
#include "mn.h"
#include "mnreg.h"
#include "OptionMemory.h"
#include "mncz.h"
#include "merrhdl.h"
//#include "cpuFeatures.h"
#include "Filecode.h"
#include "mftds.h"
#include "mu.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNMCTCZ_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define DCT_ADDR_VAL      0
#define LGCY_MMIO_HOLE_EN 1
#define DCT_SEL           4
#define ACP_ENGINE_SIZE_4MB_RJ16  0x0040

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

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function switches memory pstate for CZ
 *
 *     @param[in,out]   *NBPtr    - Pointer to the MEM_NB_BLOCK
 *     @param[in]       MemPstate - Mem Pstate
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNSwitchMemPstateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 MemPstate
  )
{
  ASSERT (MemPstate < 2);   // Only support 2 memory pstates
  IDS_HDT_CONSOLE (MEM_FLOW, "MemPsSel = %d\n", MemPstate);
  NBPtr->MemPstate = MemPstate;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function create the HT memory map
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return  TRUE  - indicates that a FATAL error has not occurred
 *     @return  FALSE - indicates that a FATAL error has occurred
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemNHtMemMapCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8  Dct;
  UINT8  DctIndex;
  UINT8  Range;
  UINT8  WeReMask;
  UINT32 BottomIo;
  UINT32 NodeMemSize;
  UINT32 NodeSysBase;
  UINT32 NodeSysLimit;
  UINT32 DctSysBase;
  UINT32 DctSysLimit;
  UINT32 DctBaseReg;
  UINT32 DctLimitReg;
  UINT32 HoleOffset;
  MEM_PARAMETER_STRUCT *RefPtr;
  DIE_STRUCT *MCTPtr;

  RefPtr = NBPtr->RefPtr;
  MCTPtr = NBPtr->MCTPtr;
  //
  // Physical addresses in this function are right adjusted by 16 bits ([47:16])
  // They are BottomIO, HoleOffset, DctSelBaseAddr, NodeSysBase, NodeSysLimit.
  //

  // Enforce bottom of IO to be 128MB aligned
  BottomIo = (RefPtr->BottomIo & 0xF8) << 8;

  NodeMemSize = 0;
  NodeSysBase = 0;
  NodeSysLimit = 0;
  DctSysBase = 0;
  DctSysLimit = 0;
  Range = 0;
  HoleOffset = 0;
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    DctIndex = NBPtr->DctCount - 1 - Dct;
    IDS_SKIP_HOOK (IDS_BEFORE_HT_MEM_MAP, NBPtr, &(NBPtr->MemPtr->StdHeader)) {
      DctIndex = NBPtr->DctCount - 1 - DctIndex;
    }
    MemNSwitchDCTNb (NBPtr, DctIndex);

    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      NodeMemSize += NBPtr->DCTPtr->Timings.DctMemSize;
      DctSysLimit = DctSysBase + NBPtr->DCTPtr->Timings.DctMemSize - 1;

      DctBaseReg = (DctSysBase & 0xFFFFF800) | (DctIndex << DCT_SEL) | (1 << DCT_ADDR_VAL);
      DctLimitReg = (DctSysLimit & 0xFFFFF800);

      if ((DctSysBase <= BottomIo) && (DctSysLimit >= BottomIo)) {
        // HW Dram Remap
        MCTPtr->Status[SbHWHole] = TRUE;
        RefPtr->GStatus[GsbHWHole] = TRUE;
        MCTPtr->NodeHoleBase = BottomIo;
        RefPtr->HoleBase = BottomIo;

        if (DctSysBase != BottomIo) {
          HoleOffset = (_4GB_RJ16 - BottomIo) + DctSysBase;
          DctBaseReg |= (1 << LGCY_MMIO_HOLE_EN);
        } else {
          DctBaseReg += _4GB_RJ16 - BottomIo;
        }

        NodeSysLimit = _4GB_RJ16 - BottomIo;

        DctLimitReg += _4GB_RJ16 - BottomIo;
        DctSysLimit += _4GB_RJ16 - BottomIo;

        MemNSetBitFieldNb (NBPtr, BFDramHoleBase, BottomIo >> 8);
        MemNSetBitFieldNb (NBPtr, BFDramHoleOffset, HoleOffset >> 7);
        MemNSetBitFieldNb (NBPtr, BFDramMemHoistValid, 1);
        MemNSetBitFieldNb (NBPtr, BFDramHoleValid, 1);
      }

      MemNSetBitFieldNb (NBPtr, BFDctBaseReg0 + Range, DctBaseReg);
      MemNSetBitFieldNb (NBPtr, BFDctLimitReg0 + Range, DctLimitReg);
      Range++;

      DctSysBase = (DctSysLimit + 1) & 0xFFFFFFF0;
    }
  }

  NodeSysLimit += NodeMemSize - 1;

  MCTPtr->NodeSysBase = NodeSysBase;
  MCTPtr->NodeSysLimit = NodeSysLimit;
  RefPtr->SysLimit = MCTPtr->NodeSysLimit;

  WeReMask = 3;
  // Set the Dram base and set the WE and RE flags in the base.
  MemNSetBitFieldNb (NBPtr, BFDramBaseReg0, (NodeSysBase << 8) | WeReMask);
  MemNSetBitFieldNb (NBPtr, BFDramBaseHiReg0, NodeSysBase >> 24);
  // Set the Dram limit and set DstNode.
  MemNSetBitFieldNb (NBPtr, BFDramLimitReg0, ((NodeSysLimit << 8) & 0xFFFF0000));
  MemNSetBitFieldNb (NBPtr, BFDramLimitHiReg0, NodeSysLimit >> 24);

  MemNSetBitFieldNb (NBPtr, BFDramBaseAddr, NodeSysBase >> (27 - 16));
  MemNSetBitFieldNb (NBPtr, BFDramLimitAddr, NodeSysLimit >> (27 - 16));

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function does synchronous channel initialization
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSyncChannelInitCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);

    // Synchronous channel initialization.
    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      MemNSetBitFieldNb (NBPtr, BFPtrInitReq, 1);
      MemNPollBitFieldNb (NBPtr, BFPtrInitReq, 0, PCI_ACCESS_TIMEOUT, FALSE);
    }
  }

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);

    // Program D18F2x90_dct[1:0][ExitSelfRef]=1. Wait for D18F2x90_dct[1:0][ExitSelfRef]=0. Wait Tref*2
    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      MemNSetBitFieldNb (NBPtr, BFExitSelfRef, 1);
      MemNPollBitFieldNb (NBPtr, BFExitSelfRef, 0, PCI_ACCESS_TIMEOUT, FALSE);
      MemUWait10ns ((7800 * 2) / 10, NBPtr->MemPtr);  // wait Tref * 2
      MemNSetBitFieldNb (NBPtr, BFChanVal, 1);
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function obtains the memory frequency in the current context
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
UINT16
MemNGetMemClkFreqInCurrentContextCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;
  UINT16 MemClkSpeed;
  CONST BIT_FIELD_NAME MemPstateBF[4] = {BFMemPstate0, BFMemPstate1, BFMemPstate2, BFMemPstate3};

  for (Dct = 0; Dct < MAX_DCTS_PER_NODE_CZ; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      break;
    }
  }

  if (MemNGetBitFieldNb (NBPtr, MemPstateBF[NBPtr->NbPstate]) == 0) {
    MemClkSpeed = NBPtr->DCTPtr->Timings.Speed;
  } else {
    MemClkSpeed = MemNGetMemClkFreqUnb (NBPtr, (UINT8) MemNGetBitFieldNb (NBPtr, BFM1MemClkFreq));
  }
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMemclk Freq: %d\n", MemClkSpeed);

  return MemClkSpeed;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function calculates and programs NB P-state dependent registers for CZ
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNProgramNbPstateDependentRegistersCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;

  NBPtr->GetMemClkFreqInCurrentContext (NBPtr);

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);

    if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
      MemNSetBitFieldNb (NBPtr, BFDataTxFifoWrDly0 + NBPtr->NbPstate, 0);
    }
  }

  MemFInitTableDrive (NBPtr, MTAfterNbPstateChange);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function releases the NB P-state force for CZ
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   OptParam - Optional parameter
 *
 *     @return    TRUE
 */
BOOLEAN
MemNReleaseNbPstateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  // Switch to NBPstateLo before restoring NBPstateHi
  //   SwNbPstateLoDis = NbPstateDisOnP0 = NbPstateThreshold = 0.
  MemNSetBitFieldNb (NBPtr, BFNbPstateCtlReg, MemNGetBitFieldNb (NBPtr, BFNbPstateCtlReg) & 0xFFFF81FF);
  MemNPollBitFieldNb (NBPtr, BFCurNbPstateLo, 1, PCI_ACCESS_TIMEOUT, FALSE);
  MemNPollBitFieldNb (NBPtr, BFNbPstateReqBusy, 0, PCI_ACCESS_TIMEOUT, FALSE);

  // 7. Restore the initial D18F5x170[NbPstateThreshold, NbPstateHi] values.
  MemNSetBitFieldNb (NBPtr, BFNbPstateCtlReg, (MemNGetBitFieldNb (NBPtr, BFNbPstateCtlReg) & 0xFFFFE13F) | (NBPtr->NbPsCtlReg & 0x1EC0));

  // Switch to NbPstateHi before restoring NbPstateLo
  MemNSetBitFieldNb (NBPtr, BFSwNbPstateLoDis, 1);
  MemNPollBitFieldNb (NBPtr, BFCurNbPstateLo, 0, PCI_ACCESS_TIMEOUT, FALSE);
  MemNPollBitFieldNb (NBPtr, BFNbPstateReqBusy, 0, PCI_ACCESS_TIMEOUT, FALSE);

  // 8. Restore the initial D18F5x170[NbPstateLo] values.
  MemNSetBitFieldNb (NBPtr, BFNbPstateLo, (NBPtr->NbPsCtlReg >> 3) & 3);

  // 6. Restore the initial D18F5x170[SwNbPstateLoDis, NbPstateDisOnP0] values.
  MemNSetBitFieldNb (NBPtr, BFNbPstateCtlReg, (MemNGetBitFieldNb (NBPtr, BFNbPstateCtlReg) & 0xFFFF9FFF) | (NBPtr->NbPsCtlReg & 0x6000));

  // Clear NbPsSel to 0
  NBPtr->NbPstate = 0;
  NBPtr->NbPsCtlReg = 0;

  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     Report the Uma size that is going to be allocated.
 *     Total system memory   UMASize
 *     >= 6G                   1G
 *     >= 4G                 512M
 *     >= 2G                 256M
 *     < 2G                  256M
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          Uma size [31:0] = Addr [47:16]
 */
UINT32
MemNGetUmaSizeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 SysMemSize;
  UINT32 SizeOfUma;

  SysMemSize = NBPtr->RefPtr->SysLimit + 1;
  SysMemSize = (SysMemSize + 0x100) & 0xFFFFFF00;   // Ignore 16MB allocated for C6 when finding UMA size

  if (NBPtr->RefPtr->UmaVersion == UMA_LEGACY) {
    if (SysMemSize > 0x10000) {
      //
      // If SysLimit is > 4GB then calculate the SysMemSize by Adjusting the BottomIo
      //
      SysMemSize = (SysMemSize - 0x10000) + (NBPtr->RefPtr->BottomIo << 8);
      if (SysMemSize >= 0x10000 && SysMemSize < 0x18000) {
        SizeOfUma = 512 << (20 - 16);       // If SystemMemSize is >= 4GB but < 6 GB
      } else {
        SizeOfUma = 1024 << (20 - 16);      // If SystemMemSize is >= 6 GB
      }
    } else if (SysMemSize >= 0x8000  && SysMemSize < 0x10000) {
      SizeOfUma = 256 << (20 - 16);         // If SystemMemSize is >= 2 GB but < 4GB
    } else {
      SizeOfUma = 256 << (20 - 16);         // If SystemMemSize is < 2 GB
    }
  } else {
    if (SysMemSize > 0x10000) {
      //
      // If SysLimit is > 4GB then calculate the SysMemSize by Adjusting the BottomIo
      //
      SysMemSize = (SysMemSize - 0x10000) + (NBPtr->RefPtr->BottomIo << 8);
    }
    if (SysMemSize >= 0x20000) {
      //
      // If SystemMemSize is >= 8 GB
      //
      SizeOfUma = 512 << (20 - 16);
    } else if (SysMemSize >= 0x18000 && SysMemSize < 0x20000) {
      //
      // If SystemMemSize is >= 6 GB but < 8GB
      //
      SizeOfUma = 384 << (20 - 16);
    } else if (SysMemSize >= 0x10000 && SysMemSize < 0x18000) {
      //
      // If SystemMemSize is >= 4 GB but < 6GB
      //
      SizeOfUma = 80 << (20 - 16);
    } else if (SysMemSize >= 0x8000 && SysMemSize < 0x10000) {
      //
      // If SystemMemSize is >= 2 GB but < 4GB
      //
      switch (NBPtr->RefPtr->GnbResolution) {
      case DISPLAY_1920x1080_And_Below:
        SizeOfUma = 32 << (20 - 16);
        break;
      case DISPLAY_2560x1600:
        SizeOfUma = 48 << (20 - 16);
        break;
      case DISPLAY_3840x2160:
        SizeOfUma = 80 << (20 - 16);
        break;
      default:
        SizeOfUma = 80 << (20 - 16);
      }
    } else {
      //
      // If SystemMemSize is < 2 GB
      //
      SizeOfUma = 32 << (20 - 16);
    }
  }

  return SizeOfUma;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function allocates memory storage for C6 and ACP Engine when
 *     it is requested to be enabled
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNAllocateC6AndAcpEngineStorageCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 SysLimit;
  UINT32 DramLimitReg;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  ACP_ENGINE_T *AcpEnginePtr;
  UINT32 AcpEngineBaseRJ16;
  UINT32 AcpEngineSizeRJ16;
  BOOLEAN AcpEngineFeature;

  AcpEngineFeature = FALSE;
  AcpEngineSizeRJ16 = 0;

  if (NBPtr->RefPtr->GnbAcpSize != NO_ACP_SIZE) {
    AcpEngineFeature = TRUE;

    // AcpSize is Right Justify by 16.
    AcpEngineSizeRJ16 = NBPtr->RefPtr->GnbAcpSize;
  }

  // SysLimit is Right Justify by 16.
  SysLimit = NBPtr->RefPtr->SysLimit;

  // Both CC6 and ACP Engine are enabled.
  if ((NBPtr->RefPtr->CStateMode != CStateModeDisabled || MemPspDetectionMechanismCZ (NBPtr)) && AcpEngineFeature) {
    // Senity check on ACP Engine size.
    ASSERT (AcpEngineSizeRJ16 <= ACP_ENGINE_SIZE_4MB_RJ16);

    if (!NBPtr->SharedPtr->C6Enabled && !NBPtr->SharedPtr->AcpEngineEnabled) {
      // System memory available is reduced by 32MB.
      // CC6 is 16MB and ACP Engine is 2MB or 4MB.  Since we use one
      // MTRR, it need to set to 32MB because of the power of 2.
      // Pretty much memory wasted up to 14MB.
      SysLimit -= _32MB_RJ16;

      NBPtr->MCTPtr->NodeSysLimit = SysLimit;
      NBPtr->RefPtr->SysLimit = SysLimit;
      NBPtr->SharedPtr->AcpEngineEnabled = TRUE;
      NBPtr->SharedPtr->C6Enabled = TRUE;

      // Set TOPMEM and MTRRs (only need to be done once for BSC)
      MemNC6AndGnbAcpEngineAdjustMSRs (NBPtr);

      // Allocate heap for ACP Engine
      AllocHeapParams.RequestedBufferSize = sizeof (ACP_ENGINE_T);
      AllocHeapParams.BufferHandle = AMD_GNB_ACP_ENGINE_HANDLE;
      AllocHeapParams.Persist = HEAP_SYSTEM_MEM;

      if (AGESA_SUCCESS != HeapAllocateBuffer (&AllocHeapParams, &(NBPtr->MemPtr->StdHeader))) {
        ASSERT(FALSE); // Could not allocate heap for ACP Engine.
      }

      AcpEnginePtr = (ACP_ENGINE_T *) AllocHeapParams.BufferPtr;

      // ACP Engine sit above the CC6 and CC6 is 16MB storage.
      AcpEngineBaseRJ16 = SysLimit + 1 + _16MB_RJ16;
      AcpEnginePtr->AcpEngineBase = (UINT64) ((UINT64) AcpEngineBaseRJ16 << 16);
      AcpEnginePtr->AcpEngineSize = AcpEngineSizeRJ16 << 16;
    }

    // Set BFCC6SaveEn
    MemNSetBitFieldNb (NBPtr, BFCC6SaveEn, 1);
    // LockDramCfg will be set in FinalizeMCT
  // Only CC6 is enabled.
  } else if (NBPtr->RefPtr->CStateMode != CStateModeDisabled || MemPspDetectionMechanismCZ (NBPtr))  {
    // Calculate new SysLimit
    if (!NBPtr->SharedPtr->C6Enabled) {
      // System memory available is reduced by 16MB.
      SysLimit -= _16MB_RJ16;

      NBPtr->MCTPtr->NodeSysLimit = SysLimit;
      NBPtr->RefPtr->SysLimit = SysLimit;
      NBPtr->SharedPtr->C6Enabled = TRUE;

      // Set TOPMEM and MTRRs (only need to be done once for BSC)
      MemNC6AdjustMSRs (NBPtr);
    }

    // Set BFCC6SaveEn
    MemNSetBitFieldNb (NBPtr, BFCC6SaveEn, 1);
    // LockDramCfg will be set in FinalizeMCT
  // Only ACP Engine is enabled.
  } else if (AcpEngineFeature) {
    // Senity check on ACP Engine size.
    ASSERT (AcpEngineSizeRJ16 <= ACP_ENGINE_SIZE_4MB_RJ16);

    // Calculate new SysLimit
    if (!NBPtr->SharedPtr->AcpEngineEnabled) {
      // System memory available is reduced by 16MB.
      SysLimit -= _16MB_RJ16;

      NBPtr->MCTPtr->NodeSysLimit = SysLimit;
      NBPtr->RefPtr->SysLimit = SysLimit;
      NBPtr->SharedPtr->AcpEngineEnabled = TRUE;

      // Set TOPMEM and MTRRs (only need to be done once for BSC)
      MemNC6AdjustMSRs (NBPtr);

      // Allocate heap for ACP Engine
      AllocHeapParams.RequestedBufferSize = sizeof (ACP_ENGINE_T);
      AllocHeapParams.BufferHandle = AMD_GNB_ACP_ENGINE_HANDLE;
      AllocHeapParams.Persist = HEAP_SYSTEM_MEM;

      if (AGESA_SUCCESS != HeapAllocateBuffer (&AllocHeapParams, &(NBPtr->MemPtr->StdHeader))) {
        ASSERT(FALSE); // Could not allocate heap for ACP Engine.
      }

      AcpEnginePtr = (ACP_ENGINE_T *) AllocHeapParams.BufferPtr;
      // ACP Engine sit above TOM.
      AcpEngineBaseRJ16 = SysLimit + 1;
      AcpEnginePtr->AcpEngineBase = (UINT64) ((UINT64) AcpEngineBaseRJ16 << 16);
      AcpEnginePtr->AcpEngineSize = AcpEngineSizeRJ16 << 16;
    }
  }

  if (NBPtr->SharedPtr->C6Enabled || NBPtr->SharedPtr->AcpEngineEnabled) {
    // Set Dram Limit
    DramLimitReg = MemNGetBitFieldNb (NBPtr, BFDramLimitReg0) & 0x0000FFFF;
    MemNSetBitFieldNb (NBPtr, BFDramLimitReg0, ((SysLimit << 8) & 0xFFFF0000) | DramLimitReg);
    MemNSetBitFieldNb (NBPtr, BFDramLimitHiReg0, SysLimit >> 24);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function fixes up UMA info
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   OptParam - Optional parameter
 *
 *     @return    TRUE
 */
BOOLEAN
MemNFixupUmaInfoCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  UMA_INFO *UmaInfoPtr;
  UINT64   Limit;
  UINT8    IntlvEn;
  UINT8    DctSel;
  UINT8    Range;

  UmaInfoPtr = (UMA_INFO *) OptParam;

  UmaInfoPtr->MemType = NBPtr->ChannelPtr->TechType;  // Both Channels the same type

  for (Range = 0; Range < 4; Range++) {
    Limit = MemNGetBitFieldNb (NBPtr, BFDctLimitReg0 + Range);
    IntlvEn = (UINT8) (Limit & 0xF);
    Limit = ((Limit | 0x7FF) << (27 - 11));

    if (UmaInfoPtr->UmaBase < Limit) {
      if (IntlvEn != 0) {
        // Interleave is enabled
        if (NBPtr->DctCount == 2) {
          UmaInfoPtr->UmaAttributes = UMA_ATTRIBUTE_INTERLEAVE | UMA_ATTRIBUTE_ON_DCT0 | UMA_ATTRIBUTE_ON_DCT1;
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\tUMA is in interleaved region of DCT0 and DCT1\n");
        }
      } else {
        // No interleave, select DCT that UMA is on
        DctSel = (UINT8) (MemNGetBitFieldNb (NBPtr, BFDctBaseReg0 + Range) >> 4) & 7;
        UmaInfoPtr->UmaAttributes = (UINT32) 1 << (3 - DctSel + 27);
        IDS_HDT_CONSOLE (MEM_FLOW, "\t\tUMA is in DCT%d region\n", DctSel);
      }
      break;
    }
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets final values for specific registers.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemNFinalizeMctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 Speed;
  UINT32 Value32;
  UINT8 DcqBwThrotWm1;
  UINT8 DcqBwThrotWm2;

  Speed = NBPtr->DCTPtr->Timings.Speed;

  MemNBrdcstSetNb (NBPtr, BFOppWrEnhDis, 1);

  // F2x118
  MemNSetBitFieldNb (NBPtr, RegMctCfgLo, (MemNGetBitFieldNb (NBPtr, RegMctCfgLo) & 0x77FFFFF) | 0x10000000);

  // F2x11C
  MemNSetBitFieldNb (NBPtr, RegMctCfgHi, (MemNGetBitFieldNb (NBPtr, RegMctCfgHi) & 0x0003C000) | 0x0CE00ED1);

  // F2x1B0
  MemNSetBitFieldNb (NBPtr, RegExtMctCfgLo, (MemNGetBitFieldNb (NBPtr, RegExtMctCfgLo) & 0x003FE8C0) | 0x0FC01001);

  // F2x1B4
  if (Speed == DDR667_FREQUENCY) {
    DcqBwThrotWm1 = 3;
    DcqBwThrotWm2 = 4;
  } else if (Speed == DDR800_FREQUENCY) {
    DcqBwThrotWm1 = 3;
    DcqBwThrotWm2 = 5;
  } else if (Speed == DDR1066_FREQUENCY) {
    DcqBwThrotWm1 = 4;
    DcqBwThrotWm2 = 6;
  } else if (Speed == DDR1333_FREQUENCY) {
    DcqBwThrotWm1 = 5;
    DcqBwThrotWm2 = 8;
  } else if  (Speed == DDR1600_FREQUENCY) {
    DcqBwThrotWm1 = 6;
    DcqBwThrotWm2 = 9;
  } else if  (Speed == DDR1866_FREQUENCY) {
    DcqBwThrotWm1 = 7;
    DcqBwThrotWm2 = 10;
  } else {
    DcqBwThrotWm1 = 8;
    DcqBwThrotWm2 = 12;
  }

  Value32 = MemNGetBitFieldNb (NBPtr, RegExtMctCfgHi);
  Value32 &= 0xFFFFFC00;
  Value32 |= (((UINT32) DcqBwThrotWm2 << 5) | (UINT32) DcqBwThrotWm1);
  MemNSetBitFieldNb (NBPtr, RegExtMctCfgHi, Value32);

  MemNSetBitFieldNb (NBPtr, BFFreeOpbdDcqStallThresh, 3);
  MemNSetBitFieldNb (NBPtr, BFDisMctHldRegSkidBuffer, 1);

  // Set LockDramCfg
  if (NBPtr->RefPtr->CStateMode != CStateModeDisabled || MemPspDetectionMechanismCZ (NBPtr)) {
    IDS_SKIP_HOOK (IDS_LOCK_DRAM_CFG, NBPtr, &NBPtr->MemPtr->StdHeader) {
      MemNSetBitFieldNb (NBPtr, BFLockDramCfg, 1);
      MemNBrdcstSetNb (NBPtr, BFDramSprLock, 1);
    }
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function force the ECC symbol size
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *Size    - ECC symbol size
 *                               FALSE = x4
 *                               TRUE  = x8
 *
 *     @return    TRUE
 */

BOOLEAN
MemNForceEccSymbolSizeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *Size
  )
{
  *(BOOLEAN *)Size = TRUE;

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   Set DRAM Controller select channel interleave address bit.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNInitChannelIntlvAddressBitCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  // Set DctSelIntLvAddr = D18F2x114[DctSelIntLvAddr[2]], D18F2x110[DctSelIntLvAddr[1:0]] = 100b
  // regardless channel interleave is enable or not.
  NBPtr->DefDctSelIntLvAddr = 4;
  NBPtr->SetBitField (NBPtr, BFDctSelIntLvAddr, NBPtr->DefDctSelIntLvAddr);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function disables scrubber temporarily for write access to
 *     DCT additional address space
 *
 *     @param[in,out]   *NBPtr            - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNDisableScrubberCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  NBPtr->DisDramScrub = NBPtr->GetBitField (NBPtr, BFDisDramScrub);
  NBPtr->SetBitField (NBPtr, BFDisDramScrub, 1);
  NBPtr->GetBitField (NBPtr, BFDisDramScrub);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function restores scrubber settings
 *
 *     @param[in,out]   *NBPtr            - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNRestoreScrubberCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  NBPtr->SetBitField (NBPtr, BFDisDramScrub, NBPtr->DisDramScrub);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function disable memory hole mappings
 *
 *     @param[in,out]   *NBPtr             - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *OptParam          - Optional parameter
 *
 *     @return    TRUE
 */

BOOLEAN
MemNDisableMemHoleMappingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  UINT8 Range;
  CONST BIT_FIELD_NAME LgcyMmioHoleEnBF[] = {BFLgcyMmioHoleEn0, BFLgcyMmioHoleEn1};
  CONST BIT_FIELD_NAME DctIntLvEnBF[] = {BFDctIntLvEn0, BFDctIntLvEn1};

  for (Range = 0; Range < sizeof (LgcyMmioHoleEnBF) / sizeof (BIT_FIELD_NAME); Range++) {
    NBPtr->LgcyMmioHoleEnMap &= ~(1 << Range);
    NBPtr->LgcyMmioHoleEnMap |= (NBPtr->GetBitField (NBPtr, LgcyMmioHoleEnBF[Range]) << Range);
    NBPtr->SetBitField (NBPtr, LgcyMmioHoleEnBF[Range], 0);
  }

  // Work around for UBTS-418496
  for (Range = 0; Range < sizeof (DctIntLvEnBF) / sizeof (BIT_FIELD_NAME); Range++) {
    NBPtr->DctIntLvEnMap &= ~(0xF << (Range * 4));
    NBPtr->DctIntLvEnMap |= (NBPtr->GetBitField (NBPtr, DctIntLvEnBF[Range]) << (Range * 4));
    NBPtr->SetBitField (NBPtr, DctIntLvEnBF[Range], 0);
  }

  // Save and disable PrefIoDis[13] and PrefCpuDis[12]
  NBPtr->MctPrefecherDisMap &= ~(0x3 << 12);
  NBPtr->MctPrefecherDisMap |= (NBPtr->GetBitField (NBPtr, BFPrefCpuDis) << 12);
  NBPtr->SetBitField (NBPtr, BFPrefCpuDis, 1);
  NBPtr->MctPrefecherDisMap |= (NBPtr->GetBitField (NBPtr, BFPrefIoDis) << 13);
  NBPtr->SetBitField (NBPtr, BFPrefIoDis, 1);

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function restore memory hole mappings
 *
 *     @param[in,out]   *NBPtr             - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *OptParam          - Optional parameter
 *
 *     @return    TRUE
 */

BOOLEAN
MemNRestoreMemHoleMappingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  UINT8 Range;
  CONST BIT_FIELD_NAME LgcyMmioHoleEnBF[] = {BFLgcyMmioHoleEn0, BFLgcyMmioHoleEn1};
  CONST BIT_FIELD_NAME DctIntLvEnBF[] = {BFDctIntLvEn0, BFDctIntLvEn1};

  for (Range = 0; Range < sizeof (LgcyMmioHoleEnBF) / sizeof (BIT_FIELD_NAME); Range++) {
    NBPtr->SetBitField (NBPtr, LgcyMmioHoleEnBF[Range], (NBPtr->LgcyMmioHoleEnMap >> Range) & 1);
  }

  for (Range = 0; Range < sizeof (DctIntLvEnBF) / sizeof (BIT_FIELD_NAME); Range++) {
    NBPtr->SetBitField (NBPtr, DctIntLvEnBF[Range], (NBPtr->DctIntLvEnMap >> (Range * 4)) & 0xF);
  }

  NBPtr->SetBitField (NBPtr, BFPrefCpuDis, (NBPtr->MctPrefecherDisMap >> 12) & 0x1);
  NBPtr->SetBitField (NBPtr, BFPrefIoDis, (NBPtr->MctPrefecherDisMap >> 13) & 0x1);

  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

