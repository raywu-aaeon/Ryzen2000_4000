/* $NoKeywords:$ */
/**
 * @file
 *
 * mtrci3.c
 *
 * Technology Control word initialization for DDR3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR3)
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mt.h"
#include "mt3.h"
#include "mtrci3.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_TECHDDR3LIB_MTRCI3_FILECODE
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
 *   This function sends control words
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */

VOID
MemTDramControlRegInit3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 ChipSel;
  UINT8 i;
  UINT8 RawCard;
  UINT8 Data;
  UINT16 CsPresent;

  MEM_DATA_STRUCT *MemPtr;
  MEM_NB_BLOCK  *NBPtr;

  NBPtr = TechPtr->NBPtr;
  MemPtr = NBPtr->MemPtr;
  CsPresent = NBPtr->DCTPtr->Timings.CsPresent;

  MemUWait10ns (800, MemPtr);   // wait 8us TACT must be changed to optimize to 8 MEM CLKs

  // Set EnDramInit to start DRAM initialization

  MemUWait10ns (600, MemPtr);   // wait 6us for PLL LOCK

  for (ChipSel = 0; ChipSel < MAX_CS_PER_CHANNEL; ChipSel += 2) {
    //
    // If chip select present
    //
    if ((CsPresent & ((UINT16)3 << ChipSel)) != 0) {
      NBPtr->SetBitField (NBPtr, BFMrsChipSel, ChipSel);

      // 2. Program F2x[1, 0]A8[CtrlWordCS]=bit mask for target chip selects.
      NBPtr->SetBitField (NBPtr, BFCtrlWordCS, 3 << (ChipSel & 0xFE));

      RawCard = NBPtr->ChannelPtr->RefRawCard[ChipSel >> 1];

      for (i = 0; i <= 15; i++) {
        // wait 8us for TMRD, must be changed to optimize to 8 MEM CLKs
        MemUWait10ns (800, MemPtr);
        if ((i != 6) && (i != 7)) {
          Data = MemTGetCtlWord3 (TechPtr, i, RawCard, ChipSel);
          MemTSendCtlWord3 (TechPtr, i, Data);
        }
      }
    }
  }
  MemUWait10ns (600, MemPtr);   // wait 6us for TSTAB
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function calculates the ControlRC value
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]     CtrlWordNum  -  control Word number.
 *     @param[in]     RawCard  -  Raw Card
 *     @param[in]     ChipSel  - Target Chip Select
 *     @return  Control Word value
 */

UINT8
MemTGetCtlWord3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 CtrlWordNum,
  IN       UINT8 RawCard,
  IN       UINT8 ChipSel
  )
{
  UINT8  Data;
  UINT8  PowerDownMode;
  DCT_STRUCT *DCTPtr;
  CH_DEF_STRUCT *ChannelPtr;
  MEM_PARAMETER_STRUCT *RefPtr;

  DCTPtr = TechPtr->NBPtr->DCTPtr;
  ChannelPtr = TechPtr->NBPtr->ChannelPtr;
  RefPtr = TechPtr->NBPtr->MemPtr->ParameterListPtr;

  Data = 0;  //Default value for all control words is 0
  switch (CtrlWordNum) {
  case 0:
    Data = 0x02;  // DA4=1
    break;
  case 1:
    if (DCTPtr->Timings.DimmSRPresent & ((UINT16) 1 << (ChipSel >> 1))) {
      Data = 0x0C;  // if single rank, set DBA1 and DBA0
    }
    break;
  case 2:
    Data = ChannelPtr->CtrlWrd02[ChipSel >> 1];
    break;
  case 3:
    Data = ChannelPtr->CtrlWrd03[ChipSel >> 1];
    break;
  case 4:
    Data = ChannelPtr->CtrlWrd04[ChipSel >> 1];
    break;
  case 5:
    Data = ChannelPtr->CtrlWrd05[ChipSel >> 1];
    break;
  case 8:
    Data = ChannelPtr->CtrlWrd08[ChipSel >> 1];
    break;
  case 9:
    // RC9 = 0xD except when partial powerdown mode is enabled and mix SR/DR or SR/QR configurations,
    // RC9 should be 0x9 for SR and and 0xD for DR or QR RDIMMs.
    PowerDownMode = (UINT8) RefPtr->PowerDownMode;
    PowerDownMode = (!TechPtr->NBPtr->IsSupported[ChannelPDMode]) ? PowerDownMode : 0;
    IDS_OPTION_HOOK (IDS_POWERDOWN_MODE, &PowerDownMode, &(TechPtr->NBPtr->MemPtr->StdHeader));
    if ((PowerDownMode == 1) &&
        (DCTPtr->Timings.DimmSRPresent & ((UINT16) 1 << (ChipSel >> 1))) &&
        ((DCTPtr->Timings.DimmDrPresent != 0) || (DCTPtr->Timings.DimmQrPresent != 0))) {
      Data = 0x09;
    } else {
      Data = 0x0D;
    }
    break;
  case 11:
    Data = CONVERT_VDDIO_TO_ENCODED (TechPtr->RefPtr->DDRVoltage, ChannelPtr->TechType);
    break;
  default:;
  }

  return (Data & 0x0F);
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function sends control word command
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]     CmdNum  -  control number.
 *     @param[in]     Value  -  value to send
 *
 */

VOID
MemTSendCtlWord3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 CmdNum,
  IN       UINT8 Value
  )
{
  MEM_NB_BLOCK  *NBPtr;

  NBPtr = TechPtr->NBPtr;

  // 1. Program MrsBank and MrsAddress.
  //    n = [BA2, A2, A1, A0].
  //    data = [BA1, BA0, A4, A3].
  //    Set all other bits in MrsAddress to zero.
  //
  NBPtr->SetBitField (NBPtr, BFMrsBank, ((CmdNum & 8) >> 1) | (Value >> 2));
  NBPtr->SetBitField (NBPtr, BFMrsAddress, ((Value & 3) << 3) | (CmdNum & 7));
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tCS%d RC%02d %04x\n", (MemNGetBitFieldNb (NBPtr, BFMrsChipSel) & 7), CmdNum, Value);

  // 2.Set SendCtrlWord=1
  NBPtr->SetBitField (NBPtr, BFSendCtrlWord, 1);
  // 3.Wait for BFSendCtrlWord=0
  NBPtr->PollBitField (NBPtr, BFSendCtrlWord, 0, PCI_ACCESS_TIMEOUT, FALSE);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function sends specific control words commands before frequency change for certain DRAM buffers.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */

VOID
FreqChgCtrlWrd3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 ChipSel;
  UINT16 Speed;
  UINT16 CsPresent;

  MEM_DATA_STRUCT *MemPtr;
  MEM_NB_BLOCK  *NBPtr;

  NBPtr = TechPtr->NBPtr;
  MemPtr = NBPtr->MemPtr;
  Speed = NBPtr->DCTPtr->Timings.Speed;
  CsPresent = NBPtr->DCTPtr->Timings.CsPresent;


  for (ChipSel = 0; ChipSel < MAX_CS_PER_CHANNEL; ChipSel += 2) {
    //
    // If chip select present.
    //
    if ((CsPresent & ((UINT16)3 << ChipSel)) != 0) {

      NBPtr->SetBitField (NBPtr, BFMrsChipSel, ChipSel);
      // program F2x[1, 0]A8[CtrlWordCS]=bit mask for target chip selects.
      NBPtr->SetBitField (NBPtr, BFCtrlWordCS, 3 << (ChipSel & 0xFE));

      //wait 8us for TMRD, must be changed to optimize to 8 MEM CLKs
      MemUWait10ns (800, MemPtr);
      if (Speed == DDR800_FREQUENCY) {
        MemTSendCtlWord3 (TechPtr, 0x0A, 0);
      } else if (Speed == DDR1066_FREQUENCY) {
        MemTSendCtlWord3 (TechPtr, 0x0A, 1);
      } else if (Speed == DDR1333_FREQUENCY) {
        MemTSendCtlWord3 (TechPtr, 0x0A, 2);
      } else if (Speed == DDR1600_FREQUENCY) {
        MemTSendCtlWord3 (TechPtr, 0x0A, 3);
      } else if (Speed == DDR1866_FREQUENCY) {
        MemTSendCtlWord3 (TechPtr, 0x0A, 4);
      } else {
        ASSERT (FALSE);
      }
    }
  }
}


