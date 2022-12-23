/* $NoKeywords:$ */
/**
 * @file
 *
 * mmAggressor.c
 *
 * Main Memory Feature implementation file for aggressor initialization.
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
#include "OptionMemory.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "Ids.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_MAINLIB_MMAGGRESSOR_FILECODE

extern MEM_FEAT_BLOCK_MAIN MemFeatMain;

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
VOID
STATIC
MemMInitializeAggressorData (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  );

/*-----------------------------------------------------------------------------
*                                EXPORTED FUNCTIONS
*
*-----------------------------------------------------------------------------
*/
BOOLEAN
MemMAggressor (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *  Find Aggressor Chipselects on all DCTs/Nodes relative to the
 *   current node.
 *
 *     @param[in,out]   *mmPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMAggressor (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  )
{
  MemMInitializeAggressorData (mmPtr);

  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Determine Aggressor Chipselects for all DCTs on all nodes relative to the
 *   current node.
 *
 *     @param[in,out]   *mmPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
VOID
STATIC
MemMInitializeAggressorData (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  )
{
  UINT8 Die;
  UINT8 AdjacentDie;
  UINT32 AdjacentSocketNum;
  UINT32 TargetSocketNum;
  UINT32 ModuleNum;
  UINT8 Dct;
  UINT8 ChipSel;
  BOOLEAN FirstCsFound;
  UINT8 Max2Aggressors;
  UINT8 MaxAggressors;
  UINT8 MaxAggressorDie;
  UINT8 MaxAggressorDct;
  UINT8 AggressorCount;

  MaxAggressors = 0;
  Max2Aggressors = 0;
  MaxAggressorDie = 0;
  MaxAggressorDct = 0;
  //
  //  Scan all Dies for Aggressors
  //
  for (Die = 0 ; Die < mmPtr->DieCount ; Die ++ ) {
    //
    // For each Die
    //
    GetSocketModuleOfNode (Die, &TargetSocketNum, &ModuleNum, &(mmPtr->MemPtr->StdHeader));
    //
    //  Find the Adjacent Die and cound the aggressors each
    //
    MaxAggressors = 0;
    Max2Aggressors = 0;
    for (AdjacentDie = 0; AdjacentDie < mmPtr->DieCount; AdjacentDie++) {
      mmPtr->NBPtr[Die].DieEnabled[AdjacentDie] = FALSE;
      GetSocketModuleOfNode (AdjacentDie, &AdjacentSocketNum, &ModuleNum, &(mmPtr->MemPtr->StdHeader));
      //
      // If Same Socket, then its the adjacent Die
      //
      if (TargetSocketNum == AdjacentSocketNum) {
        if (AdjacentDie != Die) {
          //
          // Is same socket, different die
          //
          if (mmPtr->NBPtr[AdjacentDie].MCTPtr->NodeMemSize != 0) {
            mmPtr->NBPtr[Die].AdjacentDieNBPtr = &mmPtr->NBPtr[AdjacentDie];
            mmPtr->NBPtr[Die].DieEnabled[AdjacentDie] = TRUE;
          }
        } else {
          if (mmPtr->NBPtr[Die].MCTPtr->NodeMemSize != 0) {
            mmPtr->NBPtr[Die].DieEnabled[Die] = TRUE;
          }
        }
        //
        // Determine the initial target CS,
        // Max Dimms and max CS number for all DCTs (potential aggressors)
        //
        if (mmPtr->NBPtr[AdjacentDie].MCTPtr->NodeMemSize != 0) {
          for (Dct = 0; Dct < mmPtr->NBPtr[AdjacentDie].DctCount; Dct++) {
            FirstCsFound = FALSE;
            mmPtr->NBPtr[AdjacentDie].SwitchDCT (&mmPtr->NBPtr[AdjacentDie], Dct);
            AggressorCount = 0;
            for (ChipSel = 0; ChipSel < mmPtr->NBPtr[AdjacentDie].CsPerChannel; ChipSel = ChipSel + mmPtr->NBPtr[AdjacentDie].CsPerDelay) {
              if ((mmPtr->NBPtr[AdjacentDie].DCTPtr->Timings.CsEnabled & ((UINT16) 1 << ChipSel)) != 0) {
                if (FirstCsFound == FALSE) {
                  // Set Initial CS value for Current Aggressor CS
                  mmPtr->NBPtr[AdjacentDie].InitialAggressorCSTarget[Dct] = ChipSel;
                  mmPtr->NBPtr[AdjacentDie].CurrentAggressorCSTarget[Dct] = mmPtr->NBPtr[AdjacentDie].InitialAggressorCSTarget[Dct];
                  FirstCsFound = TRUE;
                }
                mmPtr->NBPtr[AdjacentDie].MaxAggressorCSEnabled[Dct] = ChipSel;
                AggressorCount++;
              }
            } // ChipSel
            //
            // Track Maximum Aggressors for current channel
            //
            if (AggressorCount >= MaxAggressors) {
              Max2Aggressors = MaxAggressors;
              MaxAggressors = AggressorCount;
              MaxAggressorDie = AdjacentDie;
              MaxAggressorDct = Dct;
            } else {
              //
              // Also count second maximum
              //
              if (AggressorCount > Max2Aggressors) {
                Max2Aggressors = AggressorCount;
              }
            }
          } // Dct
        } // NodeMemSize != 0
      } // Same Socket
    } // AdjacentDie
    //
    // Assign Max Aggressor Values.  For each channel in the same package, the max aggressor will
    // be the highest number out of the other three channels.  That means that the channel with the
    // most chipselects has a max aggressor count equal to the second highest CS count. For the other
    // three, it will be the highest CS count.
    //
    for (AdjacentDie = 0 ; AdjacentDie < mmPtr->DieCount ; AdjacentDie ++ ) {
      if ( mmPtr->NBPtr[Die].DieEnabled[AdjacentDie] == TRUE) {
        for (Dct = 0; Dct < mmPtr->NBPtr[AdjacentDie].DctCount; Dct++) {
          if ((AdjacentDie == MaxAggressorDie) && (Dct == MaxAggressorDct)) {
            mmPtr->NBPtr[AdjacentDie].MaxAggressorDimms[Dct] = Max2Aggressors;
          } else {
            mmPtr->NBPtr[AdjacentDie].MaxAggressorDimms[Dct] = MaxAggressors;
          }
        } // Dct
      } // Enabled
    } // AdjacentDie
  } // Die
}

