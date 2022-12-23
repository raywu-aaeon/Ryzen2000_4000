/* $NoKeywords:$ */
/**
 * @file
 *
 * mfdimmexclud.c
 *
 * Feature DIMM exclude.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/EXCLUDIMM)
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
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATEXCLUDEDIMMLIB_MFDIMMEXCLUD_FILECODE

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
BOOLEAN
MemFRASExcludeDIMM (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Check and disable Chip selects that fail training for each node.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */
BOOLEAN
MemFRASExcludeDIMM (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;
  UINT8 ReserveDCT;
  UINT8 q;
  BOOLEAN Flag;
  BOOLEAN IsCSIntlvEnabled;
  UINT16 CsTestFail;
  DIE_STRUCT *MCTPtr;
  BOOLEAN RetVal;

  ASSERT (NBPtr != NULL);
  ReserveDCT = NBPtr->Dct;
  CsTestFail = 0;
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->SwitchDCT (NBPtr, Dct);
    if (NBPtr->DCTPtr->Timings.CsTestFail != 0) {
      // When there is no new failed dimm that needs to be excluded, then no need to go through the process.
      switch (NBPtr->SharedPtr->DimmExcludeFlag) {
      case NORMAL:
        // See there is new dimm that needs to be excluded
        if ((NBPtr->DCTPtr->Timings.CsTestFail & NBPtr->DCTPtr->Timings.CsEnabled) != 0) {
          CsTestFail |= NBPtr->DCTPtr->Timings.CsTestFail;
        }
        break;
      case TRAINING:
        // Do not do any dimm excluding during training
        // Dimm exclude will be done at the end of training
        break;
      case END_TRAINING:
        // Exclude all dimms that have failures during training
        if ((NBPtr->DCTPtr->Timings.CsTrainFail != 0) ||
            ((NBPtr->DCTPtr->Timings.CsTestFail & NBPtr->DCTPtr->Timings.CsEnabled) != 0)) {
          CsTestFail |= NBPtr->DCTPtr->Timings.CsTestFail;
        }
        break;
      default:
        IDS_ERROR_TRAP;
      }
    }
  }

  if (CsTestFail != 0) {
    IsCSIntlvEnabled = FALSE;
    MCTPtr = NBPtr->MCTPtr;
    MCTPtr->NodeMemSize = 0;
    NBPtr->SharedPtr->NodeMap[NBPtr->Node].IsValid = FALSE;
    NBPtr->SharedPtr->NodeMap[NBPtr->Node].SysBase = 0;
    NBPtr->SharedPtr->NodeMap[NBPtr->Node].SysLimit = 0;
    NBPtr->SetBitField (NBPtr, BFDramBaseAddr, 0);
    NBPtr->SetBitField (NBPtr, BFDramLimitAddr, 0);

    if (MCTPtr->GangedMode) {
      // if ganged mode, disable all pairs of CS that fail.
      NBPtr->DCTPtr->Timings.CsTestFail |= CsTestFail;
    }

    // if chip select interleaving has been enabled, need to undo it before remapping memory
    if (NBPtr->FeatPtr->UndoInterleaveBanks (NBPtr)) {
      IsCSIntlvEnabled = TRUE;
    }

    Flag = TRUE;
    NBPtr->FamilySpecificHook[BfAfExcludeDimm] (NBPtr, &Flag);
    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      NBPtr->SwitchDCT (NBPtr, Dct);
      if (!MCTPtr->GangedMode || (MCTPtr->Dct == 0)) {
        if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
          NBPtr->DCTPtr->Timings.DctMemSize = 0;

          NBPtr->DCTPtr->Timings.CsEnabled = 0;
          for (q = 0; q < MAX_CS_PER_CHANNEL; q++) {
            NBPtr->SetBitField (NBPtr, BFCSBaseAddr0Reg + q, 0);
          }

          // Set F2x94[DisDramInterface] = 1 if all chip selects fail training on the DCT
          if ((NBPtr->DCTPtr->Timings.CsPresent & ~NBPtr->DCTPtr->Timings.CsTestFail) == 0) {
            NBPtr->DisableDCT (NBPtr);
          }

          Flag = NBPtr->StitchMemory (NBPtr);
          ASSERT (Flag == TRUE);
        }
      }
    }
    Flag = FALSE;
    NBPtr->FamilySpecificHook[BfAfExcludeDimm] (NBPtr, &Flag);

    // Re-enable chip select interleaving when remapping is done.
    if (IsCSIntlvEnabled) {
      NBPtr->FeatPtr->InterleaveBanks (NBPtr);
    }

    RetVal = TRUE;
  } else {
    RetVal = FALSE;
  }
  NBPtr->SwitchDCT (NBPtr, ReserveDCT);
  return RetVal;
}


