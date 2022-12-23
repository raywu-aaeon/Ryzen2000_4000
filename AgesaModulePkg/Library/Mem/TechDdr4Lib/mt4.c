/* $NoKeywords:$ */
/**
 * @file
 *
 * mt4.c
 *
 * Common Technology  functions for DDR4
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR4)
 * @e \$Revision: 311646 $ @e \$Date: 2015-01-26 17:32:59 +0800 (Mon, 26 Jan 2015) $
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
#include "mt4.h"
#include "mtspd4.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

/* features */
#define FILECODE LIBRARY_MEM_TECHDDR4LIB_MT4_FILECODE

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
 *   This function Constructs the technology block
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */

BOOLEAN
MemConstructTechBlock4 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  TECHNOLOGY_TYPE *TechTypePtr;
  UINT8 Dct;
  UINT8 Channel;
  UINT8 i;
  DIE_STRUCT *MCTPtr;
  DCT_STRUCT *DCTPtr;
  CH_DEF_STRUCT *ChannelPtr;
  UINT8 DimmSlots;


  TechTypePtr = (TECHNOLOGY_TYPE *) FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_MEM_TECH, NBPtr->MCTPtr->SocketId, 0, 0, NULL, NULL);
  if (TechTypePtr != NULL) {
    // Ensure the platform override value is valid
    ASSERT ((*TechTypePtr == DDR4_TECHNOLOGY) || (*TechTypePtr == DDR3_TECHNOLOGY) || (*TechTypePtr == DDR2_TECHNOLOGY));
    if (*TechTypePtr != DDR4_TECHNOLOGY) {
      return FALSE;
    }
  }

  TechPtr->NBPtr = NBPtr;
  TechPtr->RefPtr = NBPtr->RefPtr;
  MCTPtr = NBPtr->MCTPtr;

  TechPtr->DimmPresence = MemTDIMMPresence4;
  TechPtr->SpdCalcWidth = MemTSPDCalcWidth4;
  TechPtr->SpdGetTargetSpeed = MemTSPDGetTargetSpeed4;
  TechPtr->AutoCycTiming = MemTAutoCycTiming4;
  TechPtr->SpdSetBanks = MemTSPDSetBanks4;
  TechPtr->GetCSIntLvAddr = MemTGetCSIntLvAddr4;
  TechPtr->GetDimmSpdBuffer = MemTGetDimmSpdBuffer4;
  TechPtr->MaxFilterDly = 0;
  //
  // Map the Logical Dimms on this channel to the SPD that should be used for that logical DIMM.
  // The pointers to the DIMM SPD information is as follows (2 Dimm/Ch and 3 Dimm/Ch examples).
  //
  //    DIMM Spd Buffer                          Current Channel DimmSpdPtr[MAX_DIMMS_PER_CHANNEL] array
  //    (Number of dimms varies by platform)     (Array size is determined in AGESA.H) Dimm operations loop
  //                                              on this array only)
  //    2 DIMMS PER CHANNEL
  //
  //    Socket N  Channel N Dimm 0 SR/DR DIMM <--------------DimmSpdPtr[0]
  //                        Dimm 1 SR/DR DIMM <--------------DimmSpdPtr[1]
  //                                                         DimmSpdPtr[2]------->NULL
  //                                                         DimmSpdPtr[3]------->NULL
  //
  //    Socket N  Channel N Dimm 0 SR/DR DIMM <--------------DimmSpdPtr[0]
  //                        Dimm 1    QR DIMM <---------+----DimmSpdPtr[1]
  //                                                    |    DimmSpdPtr[2]------->NULL
  //                                                    +----DimmSpdPtr[3]
  //
  //    Socket N  Channel N Dimm 0    QR DIMM <-----+--------DimmSpdPtr[0]
  //                        Dimm 1    QR DIMM <-----|---+----DimmSpdPtr[1]
  //                                                +-- | ---DimmSpdPtr[2]
  //                                                    +----DimmSpdPtr[3]
  //
  //    3 DIMMS PER CHANNEL
  //
  //    Socket N  Channel N Dimm 0 SR/DR DIMM <--------------DimmSpdPtr[0]
  //                        Dimm 1 SR/DR DIMM <--------------DimmSpdPtr[1]
  //                        Dimm 3 SR/DR DIMM <--------------DimmSpdPtr[2]
  //                                                         DimmSpdPtr[3]------->NULL
  //
  //    Socket N  Channel N Dimm 0 SR/DR DIMM <--------------DimmSpdPtr[0]
  //                        Dimm 1    QR DIMM <---------+----DimmSpdPtr[1]
  //                        Dimm 3 SR/DR DIMM <-------- | ---DimmSpdPtr[2]
  //                                                    +----DimmSpdPtr[3]
  //
  //
  //    FOR LRDIMMS
  //
  //    This code will assign SPD pointers on the basis of Physical ranks, even though
  //    an LRDIMM may only use one or two logical ranks, that determination will have to
  //    be made from downstream code.  An LRDIMM with greater than 2 Physical ranks will have
  //    its DimmSpdPtr[] mapped as if it were a QR in the above diagrams.

  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    NBPtr->SwitchDCT (NBPtr, Dct);
    DCTPtr = NBPtr->DCTPtr;
    for (Channel = 0; Channel < NBPtr->ChannelCount; Channel++) {
      NBPtr->SwitchChannel (NBPtr, Channel);
      ChannelPtr = NBPtr->ChannelPtr;
      ChannelPtr->TechType = DDR4_TECHNOLOGY;
      ChannelPtr->MCTPtr = MCTPtr;
      ChannelPtr->DCTPtr = DCTPtr;

      DimmSlots = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                         MCTPtr->SocketId,
                                         NBPtr->GetSocketRelativeChannel (NBPtr, Dct, Channel)
                                        );
      //
      // Initialize the SPD pointers for each Dimm
      //
      for (i = 0 ; i < (sizeof (ChannelPtr->DimmSpdPtr) / sizeof (ChannelPtr->DimmSpdPtr[0])) ; i++) {
        ChannelPtr->DimmSpdPtr[i] = NULL;
      }
      for (i = 0 ; i < DimmSlots; i++) {
        ChannelPtr->DimmSpdPtr[i] = &(ChannelPtr->SpdPtr[i]);
        if ( (i + 2) < (sizeof (ChannelPtr->DimmSpdPtr) / sizeof (ChannelPtr->DimmSpdPtr[0]))) {
          if (ChannelPtr->DimmSpdPtr[i]->DimmPresent) {
            if ((((ChannelPtr->DimmSpdPtr[i]->Data[SPD_RANKS] >> RANKS_SHIFT) & RANKS_MASK) + 1) > 2) {
              ChannelPtr->DimmSpdPtr[i + 2] = &(ChannelPtr->SpdPtr[i]);
            }
          }
        }
      }
    }
  }
  // Initialize Common technology functions
  MemTCommonTechInit (TechPtr);

  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

