/* $NoKeywords:$ */
/**
 * @file
 *
 * mfmemclr.c
 *
 * Feature function for memory clear operation
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/Memclr)
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




#include "AGESA.h"
#include "mm.h"
#include "mn.h"
#include "mfmemclr.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATMEMCLRLIB_MFMEMCLR_FILECODE

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

/*
 *-----------------------------------------------------------------------------
 *                                EXPORTED FUNCTIONS
 *
 *-----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   Initiates memory clear operation on one node with Dram on it.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

BOOLEAN
MemFMctMemClr_Init (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  AGESA_TESTPOINT (TpProcMemMemClr, &NBPtr->MemPtr->StdHeader);
  IDS_PERF_TIMESTAMP (TP_BEGINMEMFMCTMEMCLR_INIT, &(NBPtr->MemPtr->StdHeader));
  if (NBPtr->RefPtr->EnableMemClr == TRUE) {
    if (NBPtr->MCTPtr->NodeMemSize != 0) {
      if (!NBPtr->MemCleared) {
        NBPtr->PollBitField (NBPtr, BFMemClrBusy, 0, SPECIAL_PCI_ACCESS_TIMEOUT, FALSE);
        if (NBPtr->GetBitField (NBPtr, BFDramEnabled) == 1) {
          NBPtr->FamilySpecificHook[BeforeMemClr] (NBPtr, NBPtr);
          NBPtr->SetBitField (NBPtr, BFDramBaseAddr, 0);
          NBPtr->SetBitField (NBPtr, BFMemClrInit, 1);
        }
      }
    }
  }
  IDS_PERF_TIMESTAMP (TP_ENDNMEMFMCTMEMCLR_INIT, &(NBPtr->MemPtr->StdHeader));
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   Ensures memory clear operation has completed on one node with Dram on it.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

BOOLEAN
MemFMctMemClr_Sync (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 MicroSecondToWait;

  MicroSecondToWait = 0;
  if (NBPtr->RefPtr->EnableMemClr == TRUE) {
    if (NBPtr->MCTPtr->NodeMemSize != 0) {
      // Calculate Timeout value:
      // Timeout (in microsecond) = Memory Size * 1.5 ns / 8 Byte * 4 (Margin) * 1000 (change millisecond to us)
      // NodeMemSize is system address right shifted by 16, so shift it 4 bits to right to convert it to MB.
      // 1.5 / 8 * 4 * 1000 = 750
      MicroSecondToWait = (NBPtr->MCTPtr->NodeMemSize >> 4) * 750;

      if (!NBPtr->MemCleared) {
        NBPtr->PollBitField (NBPtr, BFMemClrBusy, 0, MicroSecondToWait, FALSE);
        NBPtr->PollBitField (NBPtr, BFMemCleared, 1, MicroSecondToWait, FALSE);
        NBPtr->SetBitField (NBPtr, BFDramBaseAddr, NBPtr->MCTPtr->NodeSysBase >> (27 - 16));
        NBPtr->MemCleared = TRUE;
      }
    }
  }
  return TRUE;
}


