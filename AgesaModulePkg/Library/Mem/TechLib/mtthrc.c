/* $NoKeywords:$ */
/**
 * @file
 *
 * mtthrc.c
 *
 * Phy assisted DQS receiver enable training
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech)
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
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_TECHLIB_MTTHRC_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define TpProcMemRcvrSetSeed TpProcMemRcvrSetDelay
#define TpProcMemRcvrInitPRE TpProcMemRcvrStartSweep
#define TpProcMemRcvrBackToBackRead TpProcMemRcvrTestPattern

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

VOID
STATIC
MemTProgramRcvrEnDly (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 ChipSel,
  IN       UINT8 Pass
  );

BOOLEAN
STATIC
MemTDqsTrainRcvrEnHw (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
extern UINT16 T1minToFreq[];

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function executes first pass of Phy assisted receiver enable training
 *      for current node at DDR800 and below.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @pre   Auto refresh and ZQCL must be disabled
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemTDqsTrainRcvrEnHwPass1 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return MemTDqsTrainRcvrEnHw (TechPtr, 1);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function executes second pass of Phy assisted receiver enable training
 *      for current node at DDR1066 and above.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @pre   Auto refresh and ZQCL must be disabled
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemTDqsTrainRcvrEnHwPass2 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  // If current speed is higher than start-up speed, do second pass of WL
  if (TechPtr->NBPtr->DCTPtr->Timings.Speed > TechPtr->NBPtr->StartupSpeed) {
    return MemTDqsTrainRcvrEnHw (TechPtr, 2);
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
 *      This function executes Phy assisted receiver enable training for current node.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]  Pass - Pass of the receiver training
 *
 *     @pre   Auto refresh and ZQCL must be disabled
 *
 */
BOOLEAN
STATIC
MemTDqsTrainRcvrEnHw (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  )
{
  MEM_NB_BLOCK  *NBPtr;
  UINT32 TestAddrRJ16;
  UINT8  Dct;
  UINT8  ChipSel;
  NBPtr = TechPtr->NBPtr;

  TechPtr->TrainingType = TRN_RCVR_ENABLE;

  AGESA_TESTPOINT (TpProcMemReceiverEnableTraining , &(NBPtr->MemPtr->StdHeader));
  IDS_HDT_CONSOLE (MEM_STATUS, "\nStart HW RxEn training\n");

  // Set environment settings before training
  MemTBeginTraining (TechPtr);
  //
  // Setup hardware training engine (if applicable)
  //
  NBPtr->FamilySpecificHook[SetupHwTrainingEngine] (NBPtr, &TechPtr->TrainingType);

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);
    NBPtr->SwitchDCT (NBPtr, Dct);
    //training for each rank
    for (ChipSel = 0; ChipSel < MAX_CS_PER_CHANNEL; (NBPtr->MCTPtr->Status[SbLrdimms])? ChipSel += 2: ChipSel++) {
      if (NBPtr->GetSysAddr (NBPtr, ChipSel, &TestAddrRJ16)) {
        if (!(NBPtr->MCTPtr->Status[SbLrdimms]) || ((NBPtr->ChannelPtr->LrDimmPresent & ((UINT8) 1 << (ChipSel >> 1))) != 0)) {
          // 1.Prepare the DIMMs for training
          NBPtr->SetBitField (NBPtr, BFTrDimmSel, ChipSel / NBPtr->CsPerDelay);

          TechPtr->ChipSel = ChipSel;
          TechPtr->Pass = Pass;
          NBPtr->FamilySpecificHook[InitPerNibbleTrn] (NBPtr, NULL);
          for (TechPtr->TrnNibble = NIBBLE_0; TechPtr->TrnNibble <= (NBPtr->FamilySpecificHook[TrainRxEnPerNibble] (NBPtr, &ChipSel)? NIBBLE_0 : NIBBLE_1); TechPtr->TrnNibble++) {
            // 2.Prepare the phy for DQS receiver enable training.
            IDS_HDT_CONSOLE (MEM_STATUS, "\t\tCS %d\n", ChipSel);
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\tTestAddr %x0000\n", TestAddrRJ16);
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t     Byte:  00  01  02  03  04  05  06  07  ECC\n");

            AGESA_TESTPOINT (TpProcMemRcvrSetSeed, &(NBPtr->MemPtr->StdHeader));
            NBPtr->MemNPrepareRcvrEnDlySeed (NBPtr);

            NBPtr->FamilySpecificHook[SetMaxRdLatBasedOnSeededRxEnDly] (NBPtr, NULL);

            AGESA_TESTPOINT (TpProcMemRcvrInitPRE, &(NBPtr->MemPtr->StdHeader));
            // 3.BIOS initiates the phy assisted receiver enable training
            NBPtr->SetBitField (NBPtr, BFDqsRcvTrEn, 1);

            // 4.BIOS begins sending out of back-to-back reads to create
            //   a continuous stream of DQS edges on the DDR interface
            AGESA_TESTPOINT (TpProcMemRcvrBackToBackRead, &(NBPtr->MemPtr->StdHeader));
            NBPtr->GenHwRcvEnReads (NBPtr, TestAddrRJ16);

            // 7.Program [DqsRcvTrEn]=0 to stop the DQS receive enable training.
            NBPtr->SetBitField (NBPtr, BFDqsRcvTrEn, 0);

            // 8.Get the gross and fine delay values.
            // 9.Calculate the corresponding final delay values
            MemTProgramRcvrEnDly (TechPtr, ChipSel, Pass);
          }
        }
      }
    }
  }
  // Restore environment settings after training
  MemTEndTraining (TechPtr);
  IDS_HDT_CONSOLE (MEM_FLOW, "End HW RxEn training\n\n");

  return (BOOLEAN) (NBPtr->MCTPtr->ErrCode < AGESA_FATAL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function calculates final RcvrEnDly for each rank
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]  ChipSel - Rank to be trained
 *     @param[in]  Pass - Pass of the receiver training
 *
 */
VOID
STATIC
MemTProgramRcvrEnDly (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 ChipSel,
  IN       UINT8 Pass
  )
{
  MEM_NB_BLOCK  *NBPtr;
  CH_DEF_STRUCT *ChannelPtr;
  UINT8  ByteLane;
  UINT16 RcvEnDly;
  UINT16 CsPairRcvEnDly;
  UINT16 RankRcvEnDly[9];
  NBPtr = TechPtr->NBPtr;
  ChannelPtr = TechPtr->NBPtr->ChannelPtr;
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t      PRE: ");
  for (ByteLane = 0; ByteLane < (NBPtr->MCTPtr->Status[SbEccDimms] ? 9 : 8) ; ByteLane++) {
    RcvEnDly = (UINT8) NBPtr->GetTrainDly (NBPtr, AccessPhRecDly, DIMM_BYTE_ACCESS (ChipSel / NBPtr->CsPerDelay, ByteLane));
    IDS_HDT_CONSOLE (MEM_FLOW, "%03x ", RcvEnDly);

    RcvEnDly = RcvEnDly + TechPtr->DiffSeedGrossSeedPreGross[ByteLane];

    // Add 1 UI to get to the midpoint of preamble
    RcvEnDly += 0x20;
    TechPtr->Bytelane = ByteLane;
    RankRcvEnDly[ByteLane] = RcvEnDly;
    if (NBPtr->FamilySpecificHook[TrainRxEnAdjustDlyPerNibble] (NBPtr, &RcvEnDly)) {
      if (((ChipSel & 1) == 1) && (NBPtr->CsPerDelay == 2)) {
        // For each rank pair on a dual-rank DIMM, compute the average value of the total delays saved during the
        //  training of each rank and program the result in D18F2x[1,0]9C_x0000_00[24:10][DqsRcvEnGrossDelay,
        //  DqsRcvEnFineDelay].
        CsPairRcvEnDly = ChannelPtr->RcvEnDlys[(ChipSel >> 1) * TechPtr->DlyTableWidth () + ByteLane];
        RcvEnDly = (CsPairRcvEnDly + RcvEnDly + 1) / 2;
      }
    }
    ChannelPtr->RcvEnDlys[(ChipSel / NBPtr->CsPerDelay) * TechPtr->DlyTableWidth () + ByteLane] = RcvEnDly;
    NBPtr->SetTrainDly (NBPtr, AccessRcvEnDly, DIMM_BYTE_ACCESS ((ChipSel / NBPtr->CsPerDelay), ByteLane), RcvEnDly);
  }

  IDS_HDT_CONSOLE_DEBUG_CODE (
    IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\t\t     RxEn: ");
    for (ByteLane = 0; ByteLane < (NBPtr->MCTPtr->Status[SbEccDimms] ? 9 : 8); ByteLane++) {
      IDS_HDT_CONSOLE (MEM_FLOW, "%03x ", RankRcvEnDly[ByteLane]);
    }
    if (NBPtr->FamilySpecificHook[TrainRxEnGetAvgDlyPerNibble] (NBPtr, NULL)) {
      if (((ChipSel & 1) == 1) && (NBPtr->CsPerDelay == 2)) {
        IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\t\t      Avg: ");
        for (ByteLane = 0; ByteLane < (NBPtr->MCTPtr->Status[SbEccDimms] ? 9 : 8); ByteLane++) {
          IDS_HDT_CONSOLE (MEM_FLOW, "%03x ", ChannelPtr->RcvEnDlys[(ChipSel / NBPtr->CsPerDelay) * TechPtr->DlyTableWidth () + ByteLane]);
        }
      }
    }
    IDS_HDT_CONSOLE (MEM_FLOW, "\n\n");
  )
}

