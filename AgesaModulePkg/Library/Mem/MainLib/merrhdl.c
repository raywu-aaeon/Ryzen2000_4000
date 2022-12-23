/* $NoKeywords:$ */
/**
 * @file
 *
 * merrhdl.c
 *
 * Memory error handling
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

#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Library/AmdHeapLib.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_MAINLIB_MERRHDL_FILECODE

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

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function handle errors occur in memory code.
 *
 *
 *     @param[in,out]   *MCTPtr - pointer to DIE_STRUCT.
 *     @param[in,out]   DCT - DCT that needs to be handled.
 *     @param[in,out]   ChipSelMask - Chip select mask that needs to be handled
 *     @param[in,out]   *StdHeader - pointer to AMD_CONFIG_PARAMS
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemErrHandle (
  IN       DIE_STRUCT *MCTPtr,
  IN       UINT8  DCT,
  IN       UINT16  ChipSelMask,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  BOOLEAN ErrorRecovery;
  BOOLEAN IgnoreErr;
  DCT_STRUCT *DCTPtr;
  UINT8 CurrentDCT;
  LOCATE_HEAP_PTR LocHeap;
  MEM_NB_BLOCK *NBPtr;
  MEM_MAIN_DATA_BLOCK mmData;

  DCTPtr = MCTPtr->DctData;
  ErrorRecovery = TRUE;
  IgnoreErr = FALSE;
  IDS_OPTION_HOOK (IDS_MEM_ERROR_RECOVERY, &ErrorRecovery, StdHeader);

  if (ErrorRecovery) {
    if (DCT == EXCLUDE_ALL_DCT) {
      // Exclude all DCTs on a node
      for (CurrentDCT = 0; CurrentDCT < MCTPtr->DctCount; CurrentDCT++) {
        DCTPtr[CurrentDCT].Timings.CsTestFail = DCTPtr[CurrentDCT].Timings.CsPresent;
      }
    } else if (ChipSelMask == EXCLUDE_ALL_CHIPSEL) {
      // Exclude the specified DCT
      DCTPtr[DCT].Timings.CsTestFail = DCTPtr[DCT].Timings.CsPresent;
    } else {
      // Exclude the chip select that has been marked out
      DCTPtr[DCT].Timings.CsTestFail |= ChipSelMask & DCTPtr[DCT].Timings.CsPresent;
      IDS_OPTION_HOOK (IDS_LOADCARD_ERROR_RECOVERY, &DCTPtr[DCT], StdHeader);
    }

    // Exclude the failed dimm to recovery from error
    if (MCTPtr->NodeMemSize != 0) {
      LocHeap.BufferHandle = AMD_MEM_AUTO_HANDLE;
      if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
        // NB block has already been constructed by main block.
        // No need to construct it here.
        NBPtr = (MEM_NB_BLOCK *)LocHeap.BufferPtr;
        if (!NBPtr->SharedPtr->NodeMap[MCTPtr->NodeId].IsValid) {
          // Memory map has not been calculated, no need to remap memory across node here.
          // Only need to remap memory within the node.
          NBPtr = &NBPtr[MCTPtr->NodeId];
          NBPtr->FeatPtr->ExcludeDIMM (NBPtr);
        } else {
          // Need to remap memory across the whole system.
          mmData.MemPtr = NBPtr->MemPtr;
          mmData.mmSharedPtr = NBPtr->SharedPtr;
          mmData.NBPtr = NBPtr;
          mmData.TechPtr = (MEM_TECH_BLOCK *) (&NBPtr[NBPtr->MemPtr->DieCount]);
          mmData.DieCount = NBPtr->MemPtr->DieCount;
          if (!((MEM_OPTION_INSTALL_STRUCT *)NBPtr->MemPtr->OptionMemoryInstallPtr)->MemFeatMain.ExcludeDIMM (&mmData)) {
            return FALSE;
          }
        }
      }
      // If allocation fails, that means the code is not running at BSP.
      // Parallel training is in process.
      // Remap for parallel training will be done when control returns to BSP.
    }
    return TRUE;
  } else {
    IDS_OPTION_HOOK (IDS_MEM_IGNORE_ERROR, &IgnoreErr, StdHeader);
    if (IgnoreErr) {
      return TRUE;
    }
    SetMemError (AGESA_FATAL, MCTPtr);
    // ErrorRecovery is FALSE
    return FALSE;
  }
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */


