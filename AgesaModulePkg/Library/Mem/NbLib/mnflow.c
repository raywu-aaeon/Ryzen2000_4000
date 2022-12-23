/* $NoKeywords:$ */
/**
 * @file
 *
 * mnflow.c
 *
 * Common Northbridge initializer flow for MCT and DCT
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



#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/AmdCalloutLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NBLIB_MNFLOW_FILECODE
/* features */
#include "mftds.h"

extern MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[];
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
STATIC
MemNInitDCTNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

VOID
STATIC
MemNCleanupDctRegsNb (
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
 *
 *      This function programs the MCT with initial values
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - AGESA_FATAL error did not occur (it is possible to have an Error that is not AGESA_SUCCESS)
 *     @return          FALSE - AGESA_FATAL error occurred
 */

BOOLEAN
MemNInitMCTNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MEM_TECH_BLOCK *TechPtr;
  UINT8 Dct;
  BOOLEAN Flag;
  ID_INFO CallOutIdInfo;

  TechPtr = NBPtr->TechPtr;
  // Switch Tech functions for Nb
  NBPtr->TechBlockSwitch (NBPtr);
  // Start Memory controller initialization sequence
  Flag = FALSE;
  if (TechPtr->DimmPresence (TechPtr)) {
    AGESA_TESTPOINT (TpProcMemPlatformSpecificInit, &(NBPtr->MemPtr->StdHeader));
    if (NBPtr->MemNPlatformSpecificFormFactorInitNb (NBPtr)) {
      AGESA_TESTPOINT (TpProcMemSpdTiming, &(NBPtr->MemPtr->StdHeader));
      if (TechPtr->SpdCalcWidth (TechPtr)) {
        AGESA_TESTPOINT (TpProcMemSpeedTclConfig, &(NBPtr->MemPtr->StdHeader));
        if (TechPtr->SpdGetTargetSpeed (TechPtr)) {
          for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
            NBPtr->SwitchDCT (NBPtr, Dct);

            Flag |= MemNInitDCTNb (NBPtr);
          }

          if (Flag && !NBPtr->IsSupported[TwoStageDramInit] && (NBPtr->MCTPtr->ErrCode != AGESA_FATAL)) {
            MemFInitTableDrive (NBPtr, MTBeforeDInit);
            AGESA_TESTPOINT (TpProcMemBeforeAgesaHookBeforeDramInit, &(NBPtr->MemPtr->StdHeader));
            IDS_PERF_TIMESTAMP (TP_BEGINAGESAHOOKBEFOREDRAMINIT, &(NBPtr->MemPtr->StdHeader));
            CallOutIdInfo.IdField.SocketId = NBPtr->MCTPtr->SocketId;
            CallOutIdInfo.IdField.ModuleId = NBPtr->MCTPtr->DieId;
            IDS_HDT_CONSOLE (MEM_FLOW, "\nCalling out to Platform BIOS on Socket %d Module %d...\n", CallOutIdInfo.IdField.SocketId, CallOutIdInfo.IdField.ModuleId);
            AgesaHookBeforeDramInit ((UINTN) CallOutIdInfo.IdInformation, NBPtr->MemPtr);
            IDS_HDT_CONSOLE (MEM_FLOW, "\nVDDIO = 1.%dV\n", (NBPtr->RefPtr->DDRVoltage == VOLT1_5) ? 5 :
                                                  (NBPtr->RefPtr->DDRVoltage == VOLT1_35) ? 35 :
                                                  (NBPtr->RefPtr->DDRVoltage == VOLT1_25) ? 25 : 999);
            AGESA_TESTPOINT (TpProcMemAfterAgesaHookBeforeDramInit, &(NBPtr->MemPtr->StdHeader));
            IDS_PERF_TIMESTAMP (TP_ENDAGESAHOOKBEFOREDRAMINIT, &(NBPtr->MemPtr->StdHeader));
            IDS_OPTION_HOOK (IDS_BEFORE_DRAM_INIT, NBPtr, &(NBPtr->MemPtr->StdHeader));
            NBPtr->InitMCT (NBPtr);
            NBPtr->StartupDCT (NBPtr);
          }
        }
      }
    }
  }
  return (BOOLEAN) (NBPtr->MCTPtr->ErrCode != AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initializes the platform specific block for families that support
 *      table driven form factor
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - AGESA_SUCCESS
 */

BOOLEAN
MemNPlatformSpecificFormFactorInitTblDrvNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Dct;

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->SwitchDCT (NBPtr, Dct);
    NBPtr->PsPtr->MemPDoPs = MemPPSCFlow;
    NBPtr->PsPtr->MemPGetPORFreqLimit = MemNGetPORFreqLimitTblDrvNb;
    NBPtr->PsPtr->MemPGetPass1Seeds = MemPGetPSCPass1Seed;
  }

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
 *
 *      This function programs the DCT with initial values
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - Error did not occur
 *     @return          FALSE - Error occurred
 */

BOOLEAN
STATIC
MemNInitDCTNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MEM_TECH_BLOCK *TechPtr;
  TechPtr = NBPtr->TechPtr;
  TechPtr->SetDramMode (TechPtr);

  if (!NBPtr->MCTPtr->GangedMode || (NBPtr->MCTPtr->Dct == 0)) {
    if (NBPtr->DCTPtr->Timings.DctDimmValid == 0) {
      NBPtr->DisableDCT (NBPtr);
    } else {
      MemNCleanupDctRegsNb (NBPtr);
      if (TechPtr->AutoCycTiming (TechPtr)) {
        if (TechPtr->SpdSetBanks (TechPtr)) {
          if (NBPtr->StitchMemory (NBPtr)) {
            // if all dimms on a DCT are disabled, the DCT needs to be disabled.
            if (NBPtr->DCTPtr->Timings.CsEnabled != 0) {
              if (NBPtr->AutoConfig (NBPtr)) {
                if (NBPtr->PlatformSpec (NBPtr)) {
                  return TRUE;
                }
              }
            } else {
              NBPtr->DisableDCT (NBPtr);
            }
          }
        }
      }
    }
  }
  return FALSE;
}

/*-----------------------------------------------------------------------------*/
/**
 *
 *      This function clears DCT registers
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
STATIC
MemNCleanupDctRegsNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  BIT_FIELD_NAME BitField;

  for (BitField = BFCSBaseAddr0Reg; BitField <= BFCSBaseAddr7Reg; BitField++) {
    MemNSetBitFieldNb (NBPtr, BitField, 0);
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This is function gets the POR speed limit for families supports table driven form factor
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNGetPORFreqLimitTblDrvNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 i;

  i = 0;
  while (memPlatSpecFlowArray[i] != NULL) {
    if ((memPlatSpecFlowArray[i])->MaxFrequency (NBPtr, (memPlatSpecFlowArray[i])->EntryOfTables)) {
      break;
    }
    i++;
  }
  // Check if there is no table found across CPU families. If so, disable channels.
  if (memPlatSpecFlowArray[i] == NULL) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nDCT %d: No MaxFreq table. This channel will be disabled.\n", NBPtr->Dct);
    NBPtr->DCTPtr->Timings.DimmExclude |= NBPtr->DCTPtr->Timings.DctDimmValid;
    PutEventLog (AGESA_ERROR, MEM_ERROR_UNSUPPORTED_DIMM_CONFIG, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
    SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
    // Change target speed to highest value so it won't affect other channels when leveling frequency across the node.
    NBPtr->DCTPtr->Timings.TargetSpeed = UNSUPPORTED_DDR_FREQUENCY;
  }
}

