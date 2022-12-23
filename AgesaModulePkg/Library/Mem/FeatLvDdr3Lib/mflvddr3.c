/* $NoKeywords:$ */
/**
 * @file
 *
 * lvddr3.c
 *
 * Voltage change for DDR3 DIMMs.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/LVDDR3)
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
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATLVDDR3LIB_MFLVDDR3_FILECODE

/* features */
#include "Library/AmdMemFeatLvDdr3Lib.h"


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

/*-----------------------------------------------------------------------------*/
/**
 *
 *   This function calculate the common lowest voltage supported by all DDR3
 *   DIMMs in the system. This function only needs to be called on BSP.
 *
 *   @param[in, out]    *NBPtr - Pointer to NB block
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */

BOOLEAN
MemFLvDdr3 (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  CH_DEF_STRUCT *ChannelPtr;
  MEM_TECH_BLOCK  *TechPtr;
  MEM_SHARED_DATA *mmSharedPtr;
  UINT8 Dct;
  UINT8 Channel;
  UINT8 Dimm;
  UINT8 *SpdBufferPtr;
  UINT8 VDDByte;
  UINT8 VoltageMap;

  mmSharedPtr = NBPtr->SharedPtr;
  TechPtr = NBPtr->TechPtr;
  VoltageMap = 0xFF;

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->SwitchDCT (NBPtr, Dct);
    for (Channel = 0; Channel < NBPtr->ChannelCount; Channel++) {
      NBPtr->SwitchChannel (NBPtr, Channel);
      ChannelPtr = NBPtr->ChannelPtr;
      for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
        if (TechPtr->GetDimmSpdBuffer (TechPtr, &SpdBufferPtr, Dimm)) {
          // SPD byte 6: Module Nominal Voltage, VDD
          // 1.5v - bit 0
          // 1.35v - bit 1
          // 1.2v - bit 2
          VDDByte = SpdBufferPtr[MNVVDD];
          IDS_HDT_CONSOLE (MEM_FLOW, "Node%d DCT%d Channel%d Dimm%d VDD Byte: 0x%02x\n", NBPtr->Node, Dct, Channel, Dimm, VDDByte);

          // Reverse the 1.5V operable bit. So its encoding can be consistent
          // with that of 1.35V and 1.25V operable bit.
          VDDByte ^= 1;
          ASSERT (VDDByte != 0);

          if (mmSharedPtr->VoltageMap != 0) {
            // Get the common supported voltage map
            VoltageMap &= VDDByte;
          } else {
            // This is the second execution of all the loop as no common voltage is found
            if (VDDByte == (1 << VOLT1_5_ENCODED_VAL)) {
              // Always exclude 1.5V dimm if no common voltage is found
              ChannelPtr->DimmExclude |= (UINT16) 1 << Dimm;
            }
          }
        }
      }
      if (mmSharedPtr->VoltageMap == 0) {
        NBPtr->DCTPtr->Timings.DimmExclude |= ChannelPtr->DimmExclude;
      }
    }
  }

  if (mmSharedPtr->VoltageMap != 0) {
    mmSharedPtr->VoltageMap &= VoltageMap;
  }

  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

