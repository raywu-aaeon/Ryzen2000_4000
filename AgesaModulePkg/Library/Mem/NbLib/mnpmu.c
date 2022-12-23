/* $NoKeywords:$ */
/**
 * @file
 *
 * mnpmu.c
 *
 * Common Northbridge function for PMU initialization
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "merrhdl.h"
#include "cpuRegisters.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NBLIB_MNPMU_FILECODE

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
 *      This function resets the PMU
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPmuResetNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  // 1. Program D18F2x9C_x0002_0099_dct[3:0][PmuReset,PmuStall] = 1,1.
  MemNSetBitFieldNb (NBPtr, BFPmuReset, 1);
  MemNSetBitFieldNb (NBPtr, BFPmuStall, 1);

  // 2. Program D18F2x9C_x0002_000E_dct[3:0][PhyDisable]=0.
  MemNSetBitFieldNb (NBPtr, BFPhyDisable, 0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function commands PMU to start DRAM initialization and/or DRAM training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNStartPmuNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\tStart PMU on image%d...\n", NBPtr->PmuFirmwareImage);
  // Initialize the protocol bit prior use.
  MemNSetBitFieldNb (NBPtr, BFRdy, 1);
  MemNSetBitFieldNb (NBPtr, BFRdy2, 1);

  // Clear PmuStall to start PMU
  MemNSetBitFieldNb (NBPtr, BFPmuStall, 0);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function waits for PMU to complete
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - PMU completes
 *     @return          FALSE - PMU fails
 */

BOOLEAN
MemNPendOnPmuCompletionNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 UsMsg;
  UINT16 Us2Msg;
  INT16 Us2MsgIndex;
  INT16 Count;

  UsMsg = 0;
  Us2Msg = 0;
  Count = 0;

  while (UsMsg != USMSG_PMUQEMPTY) {
    // 1. Wait until D18F2x9C_x0002_0004_dct[3:0][UsRdy]==0.
    MemNPollBitFieldNb (NBPtr, BFUsRdy, 0, PCI_ACCESS_TIMEOUT, FALSE);

    // 2. Read D18F2x9C_x0002_0032_dct[3:0][Message]
    UsMsg = (UINT16) MemNGetBitFieldNb (NBPtr, BFUsMessage);
    IDS_HDT_CONSOLE (MEM_PMU, "\t\t\tUsMsg: %x\n", UsMsg);

    Us2MsgIndex = 0;

    // Print out debug data if available
    if (UsMsg == USMSG_US2MSGRDY) {
      IDS_HDT_CONSOLE (MEM_PMU, "\t\t\t\tStream message through US mailbox 2\n");
      do {
        // 1. Wait until D18F2x9C_x0002_0004_dct[3:0][Us2Rdy]==0.
        MemNPollBitFieldNb (NBPtr, BFUs2Rdy, 0, PCI_ACCESS_TIMEOUT, FALSE);

        // 2. Read D18F2x9C_x0002_0034_dct[3:0][Message]
        Us2Msg = (UINT16) MemNGetBitFieldNb (NBPtr, BFUs2Message);
        IDS_HDT_CONSOLE (MEM_PMU, "\t\t\t\tUs2Msg : %x\n", Us2Msg);

        if (Us2MsgIndex == 0) {
          // The first item received is the COUNT.
          Count = (INT16)Us2Msg;
          IDS_HDT_CONSOLE (MEM_PMU, "\t\t\t\tUs2Msg COUNT: %x\n", Count);
        }

        Us2MsgIndex++;

        // 3. Program D18F2x9C_x0002_0035_dct[3:0][Rdy] = 1.
        MemNSetBitFieldNb (NBPtr, BFRdy2, 1);

        // 4. Decrement COUNT and loop to step 1 until COUNT == -1.
      } while (--Count >= 0);
    }

    // 3. Program D18F2x9C_x0002_0033_dct[3:0][Rdy] = 1.
    MemNSetBitFieldNb (NBPtr, BFRdy, 1);

    if (UsMsg == USMSG_FAIL) {
      return FALSE;
    }
  }

  return TRUE;
}

