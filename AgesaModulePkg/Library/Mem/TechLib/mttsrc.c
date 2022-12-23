/* $NoKeywords:$ */
/**
 * @file
 *
 * mttsrc.c
 *
 * Technology Software based DQS receiver enable training
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mt.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_TECHLIB_MTTSRC_FILECODE
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
MemTDqsTrainRcvrEnSw (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function executes first pass of receiver enable training for all dies
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTTrainRcvrEnSwPass1 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return MemTDqsTrainRcvrEnSw (TechPtr, 1);
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function executes receiver enable training for a specific die
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]  Pass - Pass of the receiver training
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
STATIC
MemTDqsTrainRcvrEnSw (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  )
{
  _16BYTE_ALIGN  UINT8  PatternBuffer[3 * 64];
  UINT8  TestBuffer[120];
  UINT8  *PatternBufPtr[4];
  UINT8  *TempPtr;
  UINT32 TestAddrRJ16[4];
  UINT32 TempAddrRJ16;
  UINT32 RealAddr;
  UINT16 CurTest[4];
  UINT8 Dct;
  UINT8 Receiver;
  UINT8 i;
  UINT8 TimesFail;
  UINT8 TimesRetrain;
  UINT16 RcvrEnDly;
  UINT16 MaxRcvrEnDly;
  UINT16 RcvrEnDlyLimit;
  UINT16 MaxDelayCha;
  BOOLEAN S0En;
  BOOLEAN S1En;
  UINT8 MaxFilterDly;

  MEM_DATA_STRUCT *MemPtr;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  MEM_NB_BLOCK  *NBPtr;

  NBPtr = TechPtr->NBPtr;
  MemPtr = NBPtr->MemPtr;
  MCTPtr = NBPtr->MCTPtr;
  TechPtr->TrainingType = TRN_RCVR_ENABLE;

  TempAddrRJ16 = 0;
  TempPtr = NULL;
  MaxDelayCha = 0;
  MaxFilterDly = TechPtr->MaxFilterDly;
  RcvrEnDlyLimit = NBPtr->RcvrEnDlyLimit;
  TimesRetrain = DEFAULT_TRAINING_TIMES;
  IDS_OPTION_HOOK (IDS_MEM_RETRAIN_TIMES, &TimesRetrain, &MemPtr->StdHeader);

  IDS_HDT_CONSOLE (MEM_STATUS, "\nStart SW RxEn training\n");
  // Set environment settings before training
  MemTBeginTraining (TechPtr);

  PatternBufPtr[0] = PatternBufPtr[2] = PatternBuffer;
  MemUFillTrainPattern (TestPattern0, PatternBufPtr[0], 64);
  PatternBufPtr[1] = PatternBufPtr[3] = PatternBufPtr[0] + 128;
  MemUFillTrainPattern (TestPattern1, PatternBufPtr[1], 64);

  // Begin receiver enable training
  AGESA_TESTPOINT (TpProcMemReceiverEnableTraining, &(MemPtr->StdHeader));
  MaxRcvrEnDly = 0;
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    IDS_HDT_CONSOLE (MEM_STATUS, "\tDct %d\n", Dct);
    NBPtr->SwitchDCT (NBPtr, Dct);
    DCTPtr = NBPtr->DCTPtr;

    // Set training bit
    NBPtr->SetBitField (NBPtr, BFDqsRcvEnTrain, 1);

    // Relax Max Latency before training
    NBPtr->SetMaxLatency (NBPtr, 0xFFFF);

    if (Pass == FIRST_PASS) {
      TechPtr->InitDQSPos4RcvrEn (TechPtr);
    }

    // there are four receiver pairs, loosely associated with chipselects.
    Receiver = DCTPtr->Timings.CsEnabled ? 0 : 8;
    for (; Receiver < 8; Receiver += 2) {
      TechPtr->DqsRcvEnSaved = 0;
      RcvrEnDly = RcvrEnDlyLimit;
      S0En = NBPtr->GetSysAddr (NBPtr, Receiver, &TestAddrRJ16[0]);
      S1En = NBPtr->GetSysAddr (NBPtr, Receiver + 1, &TestAddrRJ16[2]);
      if (S0En) {
        TestAddrRJ16[1] = TestAddrRJ16[0] + BIGPAGE_X8_RJ16;
      }
      if (S1En) {
        TestAddrRJ16[3] = TestAddrRJ16[2] + BIGPAGE_X8_RJ16;
      }

      if (S0En || S1En) {
        IDS_HDT_CONSOLE (MEM_STATUS, "\t\tCS %d\n", Receiver);

        // Write the test patterns
        AGESA_TESTPOINT (TpProcMemRcvrWritePattern, &(MemPtr->StdHeader));
        IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tWrite to addresses: ");
        for (i = (S0En ? 0 : 2); i < (S1En ? 4 : 2); i++) {
          RealAddr = MemUSetUpperFSbase (TestAddrRJ16[i], MemPtr);
          MemUWriteCachelines (RealAddr, PatternBufPtr[i], 1);
          IDS_HDT_CONSOLE (MEM_FLOW, " %04x0000 ", TestAddrRJ16[i]);
        }
        IDS_HDT_CONSOLE (MEM_FLOW, "\n");

        // Initialize RcvrEnDly value and other DCT stored values
        //                MCTPtr->DqsRcvEnPass = Pass ? 0xFF : 0;

        // Sweep receiver enable delays
        AGESA_TESTPOINT (TpProcMemRcvrStartSweep, &(MemPtr->StdHeader));
        TimesFail = 0;
        ERROR_HANDLE_RETRAIN_BEGIN (TimesFail, TimesRetrain)
        {
          for (RcvrEnDly = 0; RcvrEnDly < RcvrEnDlyLimit; RcvrEnDly++) {
            AGESA_TESTPOINT (TpProcMemRcvrSetDelay, &(MemPtr->StdHeader));
            TechPtr->SetRcvrEnDly (TechPtr, Receiver, RcvrEnDly);
            IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tDly %3x", RcvrEnDly);

            // Read and compare the first beat of data
            for (i = (S0En ? 0 : 2); i < (S1En ? 4 : 2); i++) {
              AGESA_TESTPOINT (TpProcMemRcvrReadPattern, &(MemPtr->StdHeader));
              RealAddr = MemUSetUpperFSbase (TestAddrRJ16[i], MemPtr);
              MemUReadCachelines (TestBuffer, RealAddr, 1);
              AGESA_TESTPOINT (TpProcMemRcvrTestPattern, &(MemPtr->StdHeader));
              CurTest[i] = TechPtr->Compare1ClPattern (TechPtr, TestBuffer, PatternBufPtr[i]);
              // Due to speculative execution during MemUReadCachelines, we must
              //  flush one more cache line than we read.
              MemUProcIOClFlush (TestAddrRJ16[i], 2, MemPtr);
              TechPtr->ResetDCTWrPtr (TechPtr, Receiver);

              //
              // Swap the test pointers such that even and odd steps alternate.
              //
              if ((i % 2) == 0) {
                TempPtr = PatternBufPtr[i];
                PatternBufPtr[i] = PatternBufPtr[i + 1];

                TempAddrRJ16 = TestAddrRJ16[i];
                TestAddrRJ16[i] = TestAddrRJ16[i + 1];
              } else {
                PatternBufPtr[i] = TempPtr;
                TestAddrRJ16[i] = TempAddrRJ16;
              }
            }

            if (TechPtr->SaveRcvrEnDly (TechPtr, Receiver, RcvrEnDly, S0En ? (CurTest[0] & CurTest[1]) : 0xFFFF, S1En ? (CurTest[2] & CurTest[3]) : 0xFFFF)) {
              // if all bytelanes pass
              if (MaxRcvrEnDly < (RcvrEnDly - MaxFilterDly)) {
                MaxRcvrEnDly = RcvrEnDly - MaxFilterDly;
              }
              break;
            }
          } // End of delay sweep
          ERROR_HANDLE_RETRAIN_END ((RcvrEnDly > (RcvrEnDlyLimit - 1)), TimesFail)
        }

        if (RcvrEnDly == RcvrEnDlyLimit) {
          // no passing window
          PutEventLog (AGESA_ERROR, MEM_ERROR_RCVR_EN_NO_PASSING_WINDOW_EQUAL_LIMIT, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
          SetMemError (AGESA_ERROR, MCTPtr);
        }

        if (RcvrEnDly > (RcvrEnDlyLimit - 1)) {
        // passing window too narrow, too far delayed
          PutEventLog (AGESA_ERROR, MEM_ERROR_RCVR_EN_VALUE_TOO_LARGE_LIMIT_LESS_ONE, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
          SetMemError (AGESA_ERROR, MCTPtr);
          DCTPtr->Timings.CsTrainFail |= DCTPtr->Timings.CsPresent & (UINT16) (3 << Receiver);
          MCTPtr->ChannelTrainFail |= (UINT32)1 << Dct;
          if (!NBPtr->MemPtr->ErrorHandling (MCTPtr, NBPtr->Dct, DCTPtr->Timings.CsTrainFail, &NBPtr->MemPtr->StdHeader)) {
            ASSERT (FALSE);
            return FALSE;
          }
        }
      }

      TechPtr->LoadRcvrEnDly (TechPtr, Receiver);     // set final delays
    }   // End while Receiver < 8

    // Clear training bit when done
    NBPtr->SetBitField (NBPtr, BFDqsRcvEnTrain, 0);

    // Set Max Latency for both channels
    MaxRcvrEnDly += 0x20;  // @attention -
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tMaxRcvrEnDly: %03x\n", MaxRcvrEnDly);
    if (MCTPtr->GangedMode) {
      if (Dct == 0) {
        MaxDelayCha = MaxRcvrEnDly;
      } else if (MaxRcvrEnDly > MaxDelayCha) {
        NBPtr->SwitchDCT (NBPtr, 0);
        NBPtr->SetMaxLatency (NBPtr, MaxRcvrEnDly);
      }
    } else {
      NBPtr->SetMaxLatency (NBPtr, MaxRcvrEnDly);
    }
    TechPtr->ResetDCTWrPtr (TechPtr, 6);
  }

  // Restore environment settings after training
  MemTEndTraining (TechPtr);
  IDS_HDT_CONSOLE (MEM_FLOW, "End SW RxEn training\n\n");
  return (BOOLEAN) (MCTPtr->ErrCode < AGESA_FATAL);
}


