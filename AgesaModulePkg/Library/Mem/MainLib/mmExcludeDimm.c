/* $NoKeywords:$ */
/**
 * @file
 *
 * mmExcludeDimm.c
 *
 * Main Memory Feature implementation file for RAS DIMM Exclude Feature
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_MAINLIB_MMEXCLUDEDIMM_FILECODE

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
BOOLEAN
MemMRASExcludeDIMM (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

/*-----------------------------------------------------------------------------
*                                EXPORTED FUNCTIONS
*
*-----------------------------------------------------------------------------
*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Check and disable Chip selects that fail training on all nodes.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMRASExcludeDIMM (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8   Node;
  BOOLEAN IsEnabled;
  BOOLEAN RetVal;
  BOOLEAN IsChannelIntlvEnabled[MAX_NODES_SUPPORTED];
  UINT8   FirstEnabledNode;
  UINT32  BottomIO;
  MEM_NB_BLOCK  *NBPtr;
  MEM_PARAMETER_STRUCT *RefPtr;
  S_UINT64 SMsr;

  FirstEnabledNode = 0;
  IsEnabled = FALSE;
  RetVal = TRUE;
  NBPtr = MemMainPtr->NBPtr;
  RefPtr = NBPtr[BSP_DIE].RefPtr;
  for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
    if (NBPtr[Node].FeatPtr->ExcludeDIMM (&NBPtr[Node])) {
      if (!IsEnabled) {
        // Record the first node that has exclude dimm enabled
        FirstEnabledNode = Node;
        IsEnabled = TRUE;
      }
    }
  }

  // Force memory address remap when we want to undo 1TB hoisting
  if (NBPtr->SharedPtr->UndoHoistingAbove1TB) {
    IsEnabled = TRUE;
  }

  if (IsEnabled) {
    // Check if all nodes have all dimms excluded. If yes, fatal exit
    NBPtr[BSP_DIE].SharedPtr->CurrentNodeSysBase = 0;
    BottomIO = (NBPtr[BSP_DIE].RefPtr->BottomIo & 0xF8) << 8;
    // If the first node that has excluded dimms does not have a system base smaller
    // than bottomIO, then we don't need to reset the GStatus, as we don't need to
    // remap memory hole.
    if (NBPtr[FirstEnabledNode].MCTPtr->NodeSysBase < BottomIO) {
      RefPtr->GStatus[GsbHWHole] = FALSE;
      RefPtr->GStatus[GsbSpIntRemapHole] = FALSE;
      RefPtr->GStatus[GsbSoftHole] = FALSE;
      RefPtr->HoleBase = 0;
      RefPtr->SysLimit = 0;
    }
    // If Node Interleaving has been executed before the remapping then we need to
    // start from the first node.
    // There may be a few senarios:
    // 1. Node interleaving is not enabled before the remap, and still cannot be enabled after
    //    remap
    // 2. Node interleaving cannot be enabled before the remap, but it can be enabled after
    //    remap
    // 3. Node interleaving is enabled before the remap, but it cannot be enabled after the remap
    if (NBPtr->SharedPtr->NodeIntlv.IsValid) {
      FirstEnabledNode = 0;
    }

    for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
      IsChannelIntlvEnabled [Node] = FALSE;
      // Check if node interleaving has been enabled on this node
      // if yes, disable it.
      if (NBPtr[Node].GetBitField (&NBPtr[Node], BFDramIntlvEn) != 0) {
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDramIntlvEn, 0);
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDramIntlvSel, 0);
      }
      if (Node >= FirstEnabledNode) {
        // Remap memory on nodes with node number larger than the first node that has excluded dimms.
        // If channel interleaving has already been enabled, need to disable it before remapping memory.
        if (NBPtr[Node].GetBitField (&NBPtr[Node], BFDctSelIntLvEn) != 0) {
          NBPtr[Node].SetBitField (&NBPtr[Node], BFDctSelIntLvEn, 0);
          IsChannelIntlvEnabled [Node] = TRUE;
        }
        NBPtr[Node].MCTPtr->Status[SbHWHole] = FALSE;
        NBPtr[Node].MCTPtr->Status[SbSWNodeHole] = FALSE;
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDctSelBaseAddr, 0);
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDctSelHiRngEn, 0);
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDctSelHi, 0);
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDctSelBaseOffset, 0);
        NBPtr[Node].SetBitField (&NBPtr[Node], BFDramHoleAddrReg, 0);
        NBPtr[Node].HtMemMapInit (&NBPtr[Node]);
      } else if (NBPtr[Node].MCTPtr->NodeMemSize != 0) {
        // No change is needed in the memory map of this node.
        // Need to adjust the current system base for other nodes processed later.
        NBPtr[Node].SharedPtr->CurrentNodeSysBase = (NBPtr[Node].MCTPtr->NodeSysLimit + 1) & 0xFFFFFFF0;
        RefPtr->SysLimit = NBPtr[Node].MCTPtr->NodeSysLimit;
        // If the current node does not have the memory hole, then set DramHoleAddrReg to be 0.
        // If memory hoisting is enabled later by other node, SyncAddrMapToAllNodes will set the base
        // and DramMemHoistValid.
        // Otherwise, do not change the register value, as we need to keep DramHoleOffset unchanged, as well
        // DramHoleValid.
        if (!NBPtr[Node].MCTPtr->Status[SbHWHole]) {
          NBPtr[Node].SetBitField (&NBPtr[Node], BFDramHoleAddrReg, 0);
        }
      }
    }

    for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
      NBPtr[Node].SyncAddrMapToAllNodes (&NBPtr[Node]);
    }

    SMsr.Value64 = AsmReadMsr64 (TOP_MEM);
    // Only when TOM is set can CpuMemTyping be re-run
    if ((SMsr.Values32.hi != 0) || (SMsr.Values32.lo != 0)) {
      if (RefPtr->SysLimit != 0) {
        NBPtr[BSP_DIE].CpuMemTyping (&NBPtr[BSP_DIE]);

        // When 1TB hoisting is not supported, TOP_MEM2 cannot exceed HT reserved region base.
        if ((RefPtr->SysLimit >= HT_REGION_BASE_RJ16) && (NBPtr->SharedPtr->UndoHoistingAbove1TB)) {
          SMsr.Values32.hi = HT_REGION_BASE_RJ16 >> (32 - 16);
          SMsr.Values32.lo = HT_REGION_BASE_RJ16 << 16;
          AsmWriteMsr64 (TOP_MEM2, SMsr.Value64);
          IDS_HDT_CONSOLE (MEM_FLOW, "TOP_MEM2: %08x0000\n", HT_REGION_BASE_RJ16);
          RefPtr->Sub1THoleBase = HT_REGION_BASE_RJ16;
          RefPtr->SysLimit = HT_REGION_BASE_RJ16 - 1;
        }
      }
    }

    // Re-run node interleaving if it has been exeucuted before the remap
    if (NBPtr->SharedPtr->NodeIntlv.IsValid) {
      ((MEM_OPTION_INSTALL_STRUCT *)NBPtr->MemPtr->OptionMemoryInstallPtr)->MemFeatMain.InterleaveNodes (MemMainPtr);
    }

    // Re-enable channel interleaving if it was enabled before remapping memory
    for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
      if (IsChannelIntlvEnabled [Node]) {
        NBPtr[Node].FeatPtr->InterleaveChannels (&NBPtr[Node]);
      }
    }

    // Reset UndoHoistingAbove1TB if it was previously set
    NBPtr->SharedPtr->UndoHoistingAbove1TB = FALSE;
  }

  // if all dimms on all nodes are excluded, do fatal exit
  if (RefPtr->SysLimit == 0) {
    PutEventLog (AGESA_FATAL, MEM_ERROR_NO_DIMM_FOUND_ON_SYSTEM, 0, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
    SetMemError (AGESA_FATAL, NBPtr[BSP_DIE].MCTPtr);
    ASSERT (FALSE);
  }

  for (Node = 0; Node < MemMainPtr->DieCount; Node ++) {
    RetVal &= (BOOLEAN) (NBPtr[Node].MCTPtr->ErrCode < AGESA_FATAL);
  }

  return RetVal;
}

