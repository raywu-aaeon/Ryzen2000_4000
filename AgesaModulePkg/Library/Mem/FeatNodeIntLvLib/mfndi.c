/* $NoKeywords:$ */
/**
 * @file
 *
 * mfndi.c
 *
 * Feature applies Node memory interleaving
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/Ndintlv)
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mport.h"
#include "Library/AmdMemFeatNodeIntLvLib.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATNODEINTLVLIB_MFNDI_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define _4GB_ (0x10000ul)

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
 *  Perform a check to see if node interleaving can be enabled on each node.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  Node interleaving can be enabled.
 *     @return          FALSE - Node interleaving cannot be enabled.
 */

BOOLEAN
MemFCheckInterleaveNodes (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  DIE_STRUCT *MCTPtr;

  ASSERT (NBPtr != NULL);

  MCTPtr = NBPtr->MCTPtr;

  if (MCTPtr->NodeMemSize != 0) {
    if (!NBPtr->SharedPtr->NodeIntlv.IsValid) {
      NBPtr->SharedPtr->NodeIntlv.NodeMemSize = MCTPtr->NodeMemSize;
      NBPtr->SharedPtr->NodeIntlv.Dct0MemSize = MCTPtr->DctData[0].Timings.DctMemSize;
      NBPtr->SharedPtr->NodeIntlv.IsValid = TRUE;
    } else {
      if ((NBPtr->SharedPtr->NodeIntlv.NodeMemSize != MCTPtr->NodeMemSize) ||
          (NBPtr->SharedPtr->NodeIntlv.Dct0MemSize != MCTPtr->DctData[0].Timings.DctMemSize)) {
        return FALSE;
      }
    }
  } else {
    // Only when all nodes have memory will node interleaving be enabled
    return FALSE;
  }
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Applies Node memory interleaving for each node.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */

BOOLEAN
MemFInterleaveNodes (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 NodeCnt;
  UINT8 BitShift;
  UINT32 MemSize;
  UINT32 Dct0MemSize;
  UINT32 NodeSysBase;
  UINT32 NodeSysLimit;
  UINT32 HoleBase;
  UINT32 HoleSize;
  UINT32 HoleOffset;
  S_UINT64 SMsr;
  MEM_PARAMETER_STRUCT *RefPtr;
  DIE_STRUCT *MCTPtr;

  ASSERT (NBPtr != NULL);

  RefPtr = NBPtr->RefPtr;
  MCTPtr = NBPtr->MCTPtr;
  if (RefPtr->GStatus[GsbSoftHole] || RefPtr->GStatus[GsbHWHole]) {
    HoleBase = RefPtr->HoleBase;
    HoleSize = _4GB_ - HoleBase;
  } else {
    HoleBase = 0;
    HoleSize = 0;
  }

  NodeCnt = NBPtr->SharedPtr->NodeIntlv.NodeCnt;
  Dct0MemSize = NBPtr->SharedPtr->NodeIntlv.Dct0MemSize;
  MemSize = NBPtr->SharedPtr->NodeIntlv.NodeMemSize;

  BitShift = LowBitSet32 (NodeCnt);
  Dct0MemSize <<= BitShift;
  if (HoleSize != 0) {
    RefPtr->GStatus[GsbHWHole] = TRUE;
    HoleOffset = HoleSize;
    if (Dct0MemSize >= HoleBase) {
      Dct0MemSize += HoleSize;
    } else {
      HoleOffset += Dct0MemSize;
    }
  } else {
    HoleOffset = 0;
  }

  MemSize = (MemSize << BitShift) + HoleSize;

  MCTPtr->NodeSysBase = 0;
  MCTPtr->NodeSysLimit = MemSize - 1;
  RefPtr->SysLimit = MemSize - 1;

  // When node interleaving is enabled with larger than 1012GB memory,
  // system memory limit will be lowered to fill in HT reserved region.
  // TOP_MEM2 was set in CpuMemTyping and needs to be updated as well.
  if (RefPtr->SysLimit >= HT_REGION_BASE_RJ16) {
    if (RefPtr->LimitMemoryToBelow1Tb) {
      SMsr.Values32.hi = HT_REGION_BASE_RJ16 >> (32 - 16);
      SMsr.Values32.lo = HT_REGION_BASE_RJ16 << 16;
    } else {
      SMsr.Values32.hi = MemSize >> (32 - 16);
      SMsr.Values32.lo = MemSize << 16;
    }
    AsmWriteMsr64 (TOP_MEM2, SMsr.Value64);
    IDS_HDT_CONSOLE (MEM_FLOW, "TOP_MEM2: %08x0000\n", MemSize);
    RefPtr->Sub1THoleBase =  HT_REGION_BASE_RJ16;
    RefPtr->SysLimit = HT_REGION_BASE_RJ16 - 1;
  } else {
    RefPtr->Sub1THoleBase =  RefPtr->SysLimit + 1;
  }

  NBPtr->SetBitField (NBPtr, BFDramIntlvSel, NBPtr->SharedPtr->NodeIntlv.NodeIntlvSel);
  NBPtr->SetBitField (NBPtr, BFDramBaseAddr, 0);
  NBPtr->SetBitField (NBPtr, BFDramIntlvEn, NodeCnt - 1);
  NBPtr->SetBitField (NBPtr, BFDramLimitAddr, (MemSize - 1) >> (27 - 16));

  if (HoleSize != 0) {
    MCTPtr->Status[SbHWHole] = TRUE;
    // DramHoleBase will be set when sync address map to other nodes.
    NBPtr->SetBitField (NBPtr, BFDramHoleOffset, HoleOffset >> (23 - 16));
    NBPtr->SetBitField (NBPtr, BFDramHoleValid, 1);
  }

  if ((MCTPtr->DctData[1].Timings.DctMemSize != 0) && (!NBPtr->Ganged)) {
    NBPtr->SetBitField (NBPtr, BFDctSelBaseAddr, Dct0MemSize >> (27 - 16));
    NBPtr->SetBitField (NBPtr, BFDctSelBaseOffset, Dct0MemSize >> (26 - 16));
  }

  NodeSysBase = NodeCnt - 1;
  NodeSysLimit = ((MemSize - 1)& 0xFFFFFF00) | NBPtr->SharedPtr->NodeIntlv.NodeIntlvSel;
  NBPtr->SharedPtr->NodeMap[NBPtr->Node].IsValid = TRUE;
  NBPtr->SharedPtr->NodeMap[NBPtr->Node].SysBase = NodeSysBase;
  NBPtr->SharedPtr->NodeMap[NBPtr->Node].SysLimit = NodeSysLimit;

  NBPtr->SharedPtr->NodeIntlv.NodeIntlvSel++;
  return TRUE;
}

