/* $NoKeywords:$ */
/**
 * @file
 *
 * mmLvDdr4.c
 *
 * Main Memory Feature implementation file for low voltage DDR4 support
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
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
#include "Ids.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mmlvddr4.h"
#include "PlatformMemoryConfiguration.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_MAINLIB_MMLVDDR4_FILECODE

extern MEM_FEAT_BLOCK_MAIN MemFeatMain;
/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
*                                EXPORTED FUNCTIONS
*
*-----------------------------------------------------------------------------
*/
BOOLEAN
MemMLvDdr4 (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *  Find the common supported voltage on all nodes.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMLvDdr4 (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8   Node;
  BOOLEAN RetVal;
  BOOLEAN SecondLoop;
  MEM_NB_BLOCK  *NBPtr;
  MEM_PARAMETER_STRUCT *ParameterPtr;
  MEM_SHARED_DATA *mmSharedPtr;

  NBPtr = MemMainPtr->NBPtr;
  mmSharedPtr = MemMainPtr->mmSharedPtr;
  ParameterPtr = MemMainPtr->MemPtr->ParameterListPtr;
  mmSharedPtr->VoltageMap = 0xFF;
  SecondLoop = FALSE;
  RetVal = TRUE;

  for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
    NBPtr[Node].FeatPtr->LvDdr4 (&NBPtr[Node]);
    // Check if there is no common supported voltage
    if ((mmSharedPtr->VoltageMap == 0) && !SecondLoop) {
      // restart node loop by setting node to 0xFF
      Node = 0xFF;
      SecondLoop = TRUE;
    }
  }

  if (mmSharedPtr->VoltageMap == 0) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nNo commonly supported VDDIO is found.\n");
    PutEventLog (AGESA_WARNING, MEM_WARNING_NO_COMMONLY_SUPPORTED_VDDIO, 0, 0, 0, 0, &(NBPtr[BSP_DIE].MemPtr->StdHeader));
    SetMemError (AGESA_WARNING, NBPtr[BSP_DIE].MCTPtr);
    // When there is no commonly supported VDDIO, use 1.35V as the temporal VDDIO
    ParameterPtr->DDRVoltage = VOLT1_35;
  } else {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nCommonly supported VDDIO is: %s%s%s.\n", ((mmSharedPtr->VoltageMap & 1) != 0) ? "1.5V, " : "", ((mmSharedPtr->VoltageMap & 2) != 0) ? "1.35V, " : "", ((mmSharedPtr->VoltageMap & 4) != 0) ? "1.25V" : "");
    ParameterPtr->DDRVoltage = CONVERT_ENCODED_TO_VDDIO (HighBitSet32 (mmSharedPtr->VoltageMap), DDR4_TECHNOLOGY);
  }

  for (Node = 0; Node < MemMainPtr->DieCount; Node ++) {
    // Check if the voltage needs force to 1.5V
    NBPtr[Node].FamilySpecificHook[ForceLvDimmVoltage] (&NBPtr[Node], MemMainPtr);

    RetVal &= (BOOLEAN) (NBPtr[Node].MCTPtr->ErrCode < AGESA_FATAL);
  }

  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Find the common supported voltage on all nodes, taken into account of the
 *  user option for performance and power saving.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMLvDdr4PerformanceEnhPre (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8 Node;
  BOOLEAN RetVal;
  DIMM_VOLTAGE VDDIO;
  MEM_NB_BLOCK *NBPtr;
  MEM_PARAMETER_STRUCT *ParameterPtr;
  MEM_SHARED_DATA *mmSharedPtr;
  MEMORY_POWER_POLICY PowerPolicy;

  NBPtr = MemMainPtr->NBPtr;
  mmSharedPtr = MemMainPtr->mmSharedPtr;
  ParameterPtr = MemMainPtr->MemPtr->ParameterListPtr;
  PowerPolicy = ParameterPtr->MemoryPowerPolicy;

  IDS_OPTION_HOOK (IDS_MEMORY_POWER_POLICY, &PowerPolicy, &NBPtr->MemPtr->StdHeader);
  IDS_HDT_CONSOLE (MEM_FLOW, (PowerPolicy == Performance) ? "\nMaximize Performance\n" : "\nMaximize Battery Life\n");

  if (ParameterPtr->DDRVoltage != VOLT_INITIAL) {
    mmSharedPtr->VoltageMap = VDDIO_DETERMINED;
    PutEventLog (AGESA_WARNING, MEM_WARNING_INITIAL_DDR3VOLT_NONZERO, 0, 0, 0, 0, &(NBPtr[BSP_DIE].MemPtr->StdHeader));
    SetMemError (AGESA_WARNING, NBPtr[BSP_DIE].MCTPtr);
    IDS_HDT_CONSOLE (MEM_FLOW, "Warning: Initial Value for VDDIO has been changed.\n");
    RetVal = TRUE;
  } else {
    RetVal = MemMLvDdr4 (MemMainPtr);

    VDDIO = ParameterPtr->DDRVoltage;
    if (NBPtr->IsSupported[PerformanceOnly] || ((PowerPolicy == Performance) && (mmSharedPtr->VoltageMap != 0))) {
      // When there is no commonly supported voltage, do not optimize performance
      // For cases where we can maximize performance, do the following
      // When VDDIO is enforced, DDRVoltage(for DDR4) will be overriden by specific VDDIO
      // So cases with DDRVoltage(for DDR4) left to be VOLT_UNSUPPORTED will be open to maximizing performance.
      ParameterPtr->DDRVoltage = VOLT_UNSUPPORTED;
    }

    /// @todo DDR4 has to make a different version of this to pass the DDR4_TECHNOLOGY type
    IDS_OPTION_HOOK (IDS_ENFORCE_VDDIO, &(ParameterPtr->DDRVoltage), &NBPtr->MemPtr->StdHeader);

    if (ParameterPtr->DDRVoltage != VOLT_UNSUPPORTED) {
      // When Voltage is already determined, do not have further process to choose maximum frequency to optimize performance
      mmSharedPtr->VoltageMap = VDDIO_DETERMINED;
      IDS_HDT_CONSOLE (MEM_FLOW, "VDDIO is determined. No further optimization will be done.\n");
    } else {
      for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
        NBPtr[Node].MaxFreqVDDIO[VOLT1_5_ENCODED_VAL] = UNSUPPORTED_DDR_FREQUENCY;
        NBPtr[Node].MaxFreqVDDIO[VOLT1_35_ENCODED_VAL] = UNSUPPORTED_DDR_FREQUENCY;
        NBPtr[Node].MaxFreqVDDIO[VOLT1_25_ENCODED_VAL] = UNSUPPORTED_DDR_FREQUENCY;
      }
      // Reprogram the leveling result as temporal candidate
      ParameterPtr->DDRVoltage = VDDIO;
    }
  }

  ASSERT (ParameterPtr->DDRVoltage != VOLT_UNSUPPORTED);
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Finalize the VDDIO for the board for performance enhancement.
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemMLvDdr4PerformanceEnhFinalize (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8 Dct;
  UINT8 Node;
  UINT8 NodeCnt[VOLT1_25 + 1];
  UINT8 MaxCnt;
  MEM_NB_BLOCK *NBPtr;
  MEM_PARAMETER_STRUCT *ParameterPtr;
  MEM_SHARED_DATA *mmSharedPtr;
  UINT8 CurrentVoltage;
  DIMM_VOLTAGE Voltage;
  UINT32 HighestFreq;

  ParameterPtr = MemMainPtr->MemPtr->ParameterListPtr;
  mmSharedPtr = MemMainPtr->mmSharedPtr;
  NBPtr = MemMainPtr->NBPtr;

  LibAmdMemFill (NodeCnt, 0, VOLT1_25_ENCODED_VAL + 1, &NBPtr->MemPtr->StdHeader);
  if (mmSharedPtr->VoltageMap != VDDIO_DETERMINED) {
    Voltage = ParameterPtr->DDRVoltage;
    IDS_HDT_CONSOLE (MEM_FLOW, "\nSearching for VDDIO that can maximize frequency: \n");
    for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
      HighestFreq = 0;
      // Find out what the highest frequency that can be reached is on this node across different voltage.
      for (CurrentVoltage = VOLT1_5_ENCODED_VAL; CurrentVoltage <= VOLT1_25_ENCODED_VAL; CurrentVoltage ++) {
        if (HighestFreq < NBPtr[Node].MaxFreqVDDIO[CurrentVoltage]) {
          HighestFreq = NBPtr[Node].MaxFreqVDDIO[CurrentVoltage];
        }
      }
      IDS_HDT_CONSOLE (MEM_FLOW, "Node%d: 1.5V -> %dMHz, 1.35V -> %dMHz, 1.25V -> %dMHz\n", Node, NBPtr[Node].MaxFreqVDDIO[VOLT1_5_ENCODED_VAL], NBPtr[Node].MaxFreqVDDIO[VOLT1_35_ENCODED_VAL], NBPtr[Node].MaxFreqVDDIO[VOLT1_25_ENCODED_VAL]);
      // Figure out what voltage we can have when attaining the highest frequency.
      for (CurrentVoltage = VOLT1_5_ENCODED_VAL; CurrentVoltage <= VOLT1_25_ENCODED_VAL; CurrentVoltage ++) {
        if (NBPtr[Node].MaxFreqVDDIO[CurrentVoltage] == HighestFreq) {
          NodeCnt[CurrentVoltage] ++;
        }
      }
    }
    IDS_HDT_CONSOLE (MEM_FLOW, "Number of nodes that can run at maximize performance: 1.5V -> %d Nodes 1.35V -> %d Nodes 1.25V -> %d Nodes.\n", NodeCnt[VOLT1_5_ENCODED_VAL], NodeCnt[VOLT1_35_ENCODED_VAL], NodeCnt[VOLT1_25_ENCODED_VAL]);
    MaxCnt = 0;
    // Use the VDDIO at which most nodes can run at higher frequency
    for (CurrentVoltage = VOLT1_5_ENCODED_VAL; CurrentVoltage <= VOLT1_25_ENCODED_VAL; CurrentVoltage ++) {
      if (MaxCnt <= NodeCnt[CurrentVoltage]) {
        MaxCnt = NodeCnt[CurrentVoltage];
        ParameterPtr->DDRVoltage = CONVERT_ENCODED_TO_VDDIO (CurrentVoltage, DDR4_TECHNOLOGY);
      }
    }

    ASSERT (ParameterPtr->DDRVoltage != VOLT_UNSUPPORTED);

    mmSharedPtr->VoltageMap = VDDIO_DETERMINED;
    if (Voltage != ParameterPtr->DDRVoltage) {
      // Finalize frequency with updated finalized VDDIO
      for (Node = 0; Node < MemMainPtr->DieCount; Node++) {
        // Need to re-sync target speed and different VDDIO may cause different settings
        NBPtr[Node].TechPtr->SpdGetTargetSpeed (NBPtr[Node].TechPtr);
        for (Dct = 0; Dct < NBPtr[Node].DctCount; Dct++) {
          NBPtr[Node].SwitchDCT (&(NBPtr[Node]), Dct);
          if (NBPtr[Node].DCTPtr->Timings.CsEnabled != 0) {
            if (!NBPtr[Node].PlatformSpec (&(NBPtr[Node]))) {
              return FALSE;
            }
          }
        }
      }
    }
  }
  return TRUE;
}

