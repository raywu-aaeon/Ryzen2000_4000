/* $NoKeywords:$ */
/**
 * @file
 *
 * mfchi.c
 *
 * Feature Channel interleaving support
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/Chintlv)
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
#include "mm.h"
#include "mn.h"
#include "Library/AmdMemFeatChIntLvLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATCHINTLVLIB_MFCHI_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define _4GB_ (0x10000ul >> 10)

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
 *   MemFInterleaveChannels:
 *
 *  Applies DIMM channel interleaving if enabled, if not ganged mode, and
 *  there are valid dimms in both channels.  Called once per Node.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */

BOOLEAN
MemFInterleaveChannels (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 DramBase;
  UINT32 DctSelBase;
  UINT32 HoleSize;
  UINT32 HoleBase;
  UINT32 HoleOffset;
  UINT32 Dct0Size;
  UINT32 Dct1Size;
  UINT32 SmallerDct;
  UINT8 DctSelIntLvAddr;
  UINT8 DctSelHi;
  UINT8 DctSelHiRngEn;
  UINT32 HoleValid;

  MEM_PARAMETER_STRUCT *RefPtr;
  DIE_STRUCT *MCTPtr;

  ASSERT (NBPtr != NULL);

  RefPtr = NBPtr->RefPtr;

  DctSelIntLvAddr = NBPtr->DefDctSelIntLvAddr;
  if (RefPtr->EnableChannelIntlv) {
    HoleSize = 0;
    HoleBase = 0;
    if (RefPtr->GStatus[GsbSoftHole] || RefPtr->GStatus[GsbHWHole]) {
      // HoleBase scaled from [47:16] to [47:26]
      HoleBase = RefPtr->HoleBase >> 10;
      HoleSize = _4GB_ - HoleBase;
    }

    MCTPtr = NBPtr->MCTPtr;

    HoleValid = NBPtr->GetBitField (NBPtr, BFDramHoleValid);
    if ((!MCTPtr->GangedMode) &&
        (MCTPtr->DctData[0].Timings.DctMemSize != 0) &&
        (MCTPtr->DctData[1].Timings.DctMemSize != 0)) {
      // DramBase scaled [47:16] to [47:26]
      DramBase = MCTPtr->NodeSysBase >> 10;
      // Scale NodeSysLimit [47:16] to [47:26]
      Dct1Size = (MCTPtr->NodeSysLimit + 1) >> 10;
      Dct0Size = NBPtr->GetBitField (NBPtr, BFDctSelBaseOffset);
      if ((Dct0Size >= _4GB_) && (DramBase < HoleBase)) {
        Dct0Size -= HoleSize;
      }
      if ((Dct1Size >= _4GB_) && (DramBase < HoleBase)) {
        Dct1Size -= HoleSize;
      }
      Dct1Size -= Dct0Size;
      Dct0Size -= DramBase;

       // Select the bigger size DCT to put in DctSelHi
      DctSelHiRngEn = 1;
      DctSelHi = 0;
      SmallerDct = Dct1Size;
      if (Dct1Size == Dct0Size) {
        SmallerDct = 0;
        DctSelHiRngEn = 0;
      } else if (Dct1Size > Dct0Size) {
        SmallerDct = Dct0Size;
        DctSelHi = 1;
      }

      if (SmallerDct != 0) {
        DctSelBase = (SmallerDct * 2) + DramBase;
      } else {
        DctSelBase = 0;
      }
      if ((DctSelBase >= HoleBase) && (DramBase < HoleBase)) {
        DctSelBase += HoleSize;
      }
      IDS_OPTION_HOOK (IDS_CHANNEL_INTERLEAVE, &DctSelIntLvAddr, &(NBPtr->MemPtr->StdHeader));
      NBPtr->SetBitField (NBPtr, BFDctSelBaseAddr, DctSelBase >> 1);
      NBPtr->SetBitField (NBPtr, BFDctSelHiRngEn, DctSelHiRngEn);
      NBPtr->SetBitField (NBPtr, BFDctSelHi, DctSelHi);
      NBPtr->SetBitField (NBPtr, BFDctSelIntLvAddr, DctSelIntLvAddr);
      NBPtr->SetBitField (NBPtr, BFDctSelIntLvEn, 1);

       // DctSelBaseOffset = DctSelBaseAddr - Interleaved region
      NBPtr->SetBitField (NBPtr, BFDctSelBaseOffset, DctSelBase - SmallerDct);

       // Adjust DramHoleOffset
      if (HoleValid != 0) {
        HoleOffset = DramBase;
        if ((DctSelBase < HoleBase) && (DctSelBase != 0)) {
          HoleOffset += (DctSelBase - DramBase) >> 1;
        }
        HoleOffset += HoleSize;
        NBPtr->SetBitField (NBPtr, BFDramHoleOffset, HoleOffset << 3);
      }
    } else {
      //
      // Channel Interleaving is requested but cannot be enabled
      //
      PutEventLog (AGESA_WARNING, MEM_WARNING_CHANNEL_INTERLEAVING_NOT_ENABLED, NBPtr->Node, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_WARNING, MCTPtr);
    }

    return TRUE;
  } else {
    return FALSE;
  }
}

