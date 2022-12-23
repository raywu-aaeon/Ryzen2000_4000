/* $NoKeywords:$ */
/**
 * @file
 *
 * mnD4cz.c
 *
 * DDR4 Specific Northbridge functions for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision$ @e \$Date$
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
///@todo
//#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "OptionMemory.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mncz.h"
#include "mnD4cz.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_NBCZLIB_MND4CZ_FILECODE

extern ROMDATA PMU_FIRMWARE PmuFirmwareD4ImageTableCZ[];
extern ROMDATA UINT8 PmuFirmwareD4ImageTableSizeCZ;
extern MEM_PSC_FLOW_BLOCK memPlatSpecFlowD4CZ;
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
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function initializes member DDR4 Technology Specific functions and
 *    variables of NB block.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNInitNBDataD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  //
  // DDR4 Startup Speed and M1 Speed are both DDR1333
  //
  NBPtr->StartupSpeed = DDR1333_FREQUENCY;
  NBPtr->M1Speed = DDR1333_FREQUENCY;
  //
  // Assign DDR4 PMU FW Image Table
  //
  NBPtr->PmuFirmwareImageTable = PmuFirmwareD4ImageTableCZ;
  NBPtr->PmuFirmwareImageTableSize = PmuFirmwareD4ImageTableSizeCZ;
  //
  // Initialize Platform Specific Flow Block
  //
  NBPtr->PlatSpecFlowPtr = &memPlatSpecFlowD4CZ;
  // ---------------------------------------------------------------------------
  // Common functions
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // Misc functions
  // ---------------------------------------------------------------------------
  NBPtr->ProgramCycTimings = MemNProgramCycTimingsD4CZ;
  NBPtr->GetCSIntLvAddr = MemNGetCSIntLvAddrD4CZ;

  // ---------------------------------------------------------------------------
  // Training functions
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // Family specific flags
  // ---------------------------------------------------------------------------
  NBPtr->SelfRefreshAbort = FALSE;

  if (NBPtr->RefPtr->DramTempControlledRefreshEn && NBPtr->RefPtr->EnableExtendedTemperatureRange) {
    //
    // Force CfgDramDoubleRefreshRateEn = TRUE as it is required for DDR4 Temperature Controlled
    //  refresh in the Extended Temperature Range.
    //
    if (NBPtr->RefPtr->DramDoubleRefreshRateEn != TRUE) {
      NBPtr->RefPtr->DramDoubleRefreshRateEn = TRUE;
      ///@todo
      //PutEventLog (AGESA_ALERT, MEM_ALERT_DRAM_DOUBLE_REFRESH_RATE_ENABLED, 0, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_ALERT, NBPtr->MCTPtr);
    }
  }

  // ---------------------------------------------------------------------------
  // Family specific hooks
  // ---------------------------------------------------------------------------

  // ---------------------------------------------------------------------------
  // Initialize PS block's functions
  // ---------------------------------------------------------------------------
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function programs DDR mode to DDR4 for all DCTs
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSetDdrModeD4CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8   Dct;

  // Set DramType and disable unused DCTs
  for (Dct = 0; Dct < MAX_DCTS_PER_NODE_CZ; Dct++) {
    MemNSwitchDCTNb (NBPtr, Dct);

    MemNSetBitFieldNb (NBPtr, BFDramType, DRAM_TYPE_DDR4_CZ);
  }

  // After disable unused DCTs, change the number of DCTs to 2 for DDR4 mode
  NBPtr->DctCount = MAX_D4_DCTS_PER_NODE_CZ;
  // Program bit fields before memory init
  MemNSetBitFieldNb (NBPtr, BFEnSplitMctDatBuffers, 1);
}



