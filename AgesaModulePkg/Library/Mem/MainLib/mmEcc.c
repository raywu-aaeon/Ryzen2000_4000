/* $NoKeywords:$ */
/**
 * @file
 *
 * mmEcc.c
 *
 * Main Memory Feature implementation file for ECC Initialization
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


#include "Porting.h"
#include "AGESA.h"
#include "Ids.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "ma.h"
#include "mfmemclr.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_MAINLIB_MMECC_FILECODE
/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

BOOLEAN
MemMEcc (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  );

/*-----------------------------------------------------------------------------
*                                EXPORTED FUNCTIONS
*
*-----------------------------------------------------------------------------
*/
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *
 *
 *     @param[in,out]   *mmPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMEcc (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  )
{
  UINT8 Die;
  MEM_SHARED_DATA *SharedPtr;
  MEM_PARAMETER_STRUCT *RefPtr;
  BOOLEAN RetVal;

  RetVal = TRUE;
  RefPtr = mmPtr->MemPtr->ParameterListPtr;
  SharedPtr = mmPtr->mmSharedPtr;

  //
  // Run Northbridge-specific ECC initialization feature for each die.
  //
  SharedPtr->AllECC = FALSE;
  if (RefPtr->EnableEccFeature) {
    SharedPtr->AllECC = TRUE;
    AGESA_TESTPOINT (TpProcMemEccInitialization, &(mmPtr->MemPtr->StdHeader));

    for (Die = 0 ; Die < mmPtr->DieCount ; Die ++ ) {
      mmPtr->NBPtr[Die].FeatPtr->CheckEcc (&(mmPtr->NBPtr[Die]));
      RetVal &= (BOOLEAN) (mmPtr->NBPtr[Die].MCTPtr->ErrCode < AGESA_FATAL);
    }
    if (SharedPtr->AllECC == TRUE) {
      RefPtr->GStatus[GsbAllECCDimms] = TRUE;
      // Sync mem clear before setting scrub rate.
      for (Die = 0; Die < mmPtr->DieCount; Die++) {
        MemFMctMemClr_Sync (&(mmPtr->NBPtr[Die]));
      }
    }
  }
  // Scrubber control
  for (Die = 0 ; Die < mmPtr->DieCount ; Die ++ ) {
    mmPtr->NBPtr[Die].FeatPtr->InitEcc (&(mmPtr->NBPtr[Die]));
  }
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function disable DRAM scrubber
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
VOID
MemMDisableScrubber (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8 Node;
  MEM_SHARED_DATA *SharedPtr;
  MEM_NB_BLOCK  *NBArray;

  SharedPtr = MemMainPtr->mmSharedPtr;
  NBArray = MemMainPtr->NBPtr;
  if (SharedPtr->AllECC == TRUE) {
    for (Node = 0; Node < MemMainPtr->DieCount; Node ++) {
      NBArray[Node].MemNDisableScrubber (&NBArray[Node]);
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function restore the settings of DRAM scrubber
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
VOID
MemMRestoreScrubber (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8 Node;
  MEM_SHARED_DATA *SharedPtr;
  MEM_NB_BLOCK  *NBArray;

  SharedPtr = MemMainPtr->mmSharedPtr;
  NBArray = MemMainPtr->NBPtr;
  if (SharedPtr->AllECC == TRUE) {
    for (Node = 0; Node < MemMainPtr->DieCount; Node ++) {
      NBArray[Node].MemNRestoreScrubber (&NBArray[Node]);
    }
  }
}

