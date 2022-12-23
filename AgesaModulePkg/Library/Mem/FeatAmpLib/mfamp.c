/* $NoKeywords:$ */
/**
 * @file
 *
 * mfamp.c
 *
 * Feature function for AMD Memory Profile (overclocking)
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/AMP)
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
#include "AGESA.h"
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "Library/AmdMemFeatAmpLib.h"
#include "mt.h"
#include "mt3.h"
#include "Library/IdsLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Ids.h"
#include "mtspd3.h"
#include "merrhdl.h"
#include "mu.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATAMPLIB_MFAMP_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define SPD_OVRCLK_VAL 3

// AMP SPD bytes offset
#define AMP_SPD_PF         80
#define AMP_SPD_Volt       81
#define AMP_SPD_TCK        82
#define AMP_SPD_TCK_FTB    83
#define AMP_SPD_CASLO      84
#define AMP_SPD_CASHI      85
#define AMP_SPD_TAA        86
#define AMP_SPD_TAA_FTB    87
#define AMP_SPD_TRCD       88
#define AMP_SPD_TRCD_FTB   89
#define AMP_SPD_TRP        90
#define AMP_SPD_TRP_FTB    91
#define AMP_SPD_UPPER_TRC  92
#define AMP_SPD_TRAS       93
#define AMP_SPD_TRC        94
#define AMP_SPD_TRC_FTB    95
#define AMP_SPD_TWR        96
#define AMP_SPD_TWTR       97
#define AMP_SPD_TRTP       98
#define AMP_SPD_TRFC_LO    99
#define AMP_SPD_TRFC_HI    100
#define AMP_SPD_UPPER_TFAW 101
#define AMP_SPD_TFAW       102
#define AMP_SPD_TRRD       103

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

/*
 *-----------------------------------------------------------------------------
 *                                EXPORTED FUNCTIONS
 *
 *-----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   Enable overclocking functionality on current node if it is requested.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE
 */

BOOLEAN
MemFAMP (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  STATIC CONST UINT8 SpdOffsetToCopy[] = {
    AMP_SPD_TCK,        SPD_TCK,
    AMP_SPD_TCK_FTB,    SPD_TCK_FTB,
    AMP_SPD_CASLO,      SPD_CASLO,
    AMP_SPD_CASHI,      SPD_CASHI,
    AMP_SPD_TAA,        SPD_TAA,
    AMP_SPD_TAA_FTB,    SPD_TAA_FTB,
    AMP_SPD_TRCD,       SPD_TRCD,
    AMP_SPD_TRCD_FTB,   SPD_TRCD_FTB,
    AMP_SPD_TRP,        SPD_TRP,
    AMP_SPD_TRP_FTB,    SPD_TRP_FTB,
    // SPD_UPPER_TRC = SPD_UPPER_TRAS = B21
    AMP_SPD_UPPER_TRC,  SPD_UPPER_TRC,
    AMP_SPD_TRAS,       SPD_TRAS,
    AMP_SPD_TRC,        SPD_TRC,
    AMP_SPD_TRC_FTB,    SPD_TRC_FTB,
    AMP_SPD_TWR,        SPD_TWR,
    AMP_SPD_TWTR,       SPD_TWTR,
    AMP_SPD_TRTP,       SPD_TRTP,
    AMP_SPD_TRFC_LO,    SPD_TRFC_LO,
    AMP_SPD_TRFC_HI,    SPD_TRFC_HI,
    AMP_SPD_UPPER_TFAW, SPD_UPPER_TFAW,
    AMP_SPD_TFAW,       SPD_TFAW,
    AMP_SPD_TRRD,       SPD_TRRD
  };

  UINT8 i;
  UINT8 j;
  UINT8 Dct;
  UINT8 NumDimmslots;
  AMP_DIMM_VOLTAGE Volt;
  UINT8 *SpdBufferPtr;
  BOOLEAN OverClockFlag;

  i = 0;
  j = 0;
  Dct = 0;
  NumDimmslots = 0;
  SpdBufferPtr = NULL;
  OverClockFlag = FALSE;
  Volt = AMP_VOLT_RSVD;

  // Initialize output parameters
  NBPtr->RefPtr->AmpStatus.AmpVoltageValid = FALSE;
  NBPtr->RefPtr->AmpStatus.AmpSupportDetectedButNotEnabled = FALSE;
  NBPtr->RefPtr->AmpStatus.AmpSelectedButNotEnabled = FALSE;


  if (NBPtr->RefPtr->AmpEnable) {
    IDS_HDT_CONSOLE (MEM_FLOW, "AMP Support Enabled !\n");
    //
    // Check Profile across Dcts as well as DIMM modules
    //
    OverClockFlag = TRUE;
    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      MemNSwitchDCTNb (NBPtr, Dct);
      NumDimmslots = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                            NBPtr->MCTPtr->SocketId,
                                            NBPtr->ChannelPtr->ChannelID);

      for (i = 0; i < NumDimmslots; i++) {
        //
        // Locate SPD data buffer of the DIMM module
        //
        if (MemTGetDimmSpdBuffer3 (NBPtr->TechPtr, &SpdBufferPtr, i)) {
          //
          // Profile check
          //
          if (((SpdBufferPtr[AMP_SPD_PF] >> 6) & 3) != SPD_OVRCLK_VAL) {
            OverClockFlag = FALSE;
            Dct = NBPtr->DctCount;
            break;
          }
          //
          // Profile rev. and voltage support check
          //
          if ((((SpdBufferPtr[AMP_SPD_PF] >> 3) & 7) < 1) || ((SpdBufferPtr[AMP_SPD_Volt] & 0xF) != 4)) {
            OverClockFlag = FALSE;
            Dct = NBPtr->DctCount;
            break;
          }
        }
      }
    }

    //
    // Copy upper SPD data to corresponding SPD data fields if OverClockFlag is TRUE
    //
    if (OverClockFlag) {
      IDS_HDT_CONSOLE (MEM_FLOW, "Copy upper SPD data ...\n");
      for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
        IDS_HDT_CONSOLE (MEM_FLOW, "Dct%d\n", Dct);
        MemNSwitchDCTNb (NBPtr, Dct);
        NumDimmslots = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                              NBPtr->MCTPtr->SocketId,
                                              NBPtr->ChannelPtr->ChannelID);

        for (i = 0; i < NumDimmslots; i++) {
          if (MemTGetDimmSpdBuffer3 (NBPtr->TechPtr, &SpdBufferPtr, i)) {
            IDS_HDT_CONSOLE (MEM_FLOW, "\tDimm%d\n", i);
            for (j = 0; j < GET_SIZE_OF (SpdOffsetToCopy); j += 2) {
              IDS_HDT_CONSOLE (MEM_FLOW, "\t\tByte %2d = %2x  ->  ", SpdOffsetToCopy[j + 1], SpdBufferPtr[SpdOffsetToCopy[j + 1]]);
              SpdBufferPtr[SpdOffsetToCopy[j + 1]] = SpdBufferPtr[SpdOffsetToCopy[j]];
              IDS_HDT_CONSOLE (MEM_FLOW, "%x\n", SpdBufferPtr[SpdOffsetToCopy[j + 1]]);
            }

            // Look for the lowest voltage
            // Byte 81 definition :
            //    0x01 to 0x09, the smaller value, the lower voltage it is
            //    0x10 to 0x60, the greater value, the lower voltage it is
            ASSERT (((SpdBufferPtr[AMP_SPD_Volt] >= AMP_VOLT1_5) && (SpdBufferPtr[AMP_SPD_Volt] <= AMP_VOLT1_9)) || ((SpdBufferPtr[AMP_SPD_Volt] >= AMP_VOLT1_45) && (SpdBufferPtr[AMP_SPD_Volt] <= AMP_VOLT1_2)))
            if (Volt == AMP_VOLT_RSVD) {
              Volt = SpdBufferPtr[AMP_SPD_Volt];
            } else if ((Volt >= AMP_VOLT1_45)) {
              if (SpdBufferPtr[AMP_SPD_Volt] <= AMP_VOLT1_45) {
                Volt = SpdBufferPtr[AMP_SPD_Volt];
              } else {
                if (Volt < SpdBufferPtr[AMP_SPD_Volt]) {
                  Volt = SpdBufferPtr[AMP_SPD_Volt];
                }
              }
            } else {
              if (SpdBufferPtr[AMP_SPD_Volt] <= AMP_VOLT1_45) {
                if (Volt > SpdBufferPtr[AMP_SPD_Volt]) {
                  Volt = SpdBufferPtr[AMP_SPD_Volt];
                }
              } else {
                Volt = SpdBufferPtr[AMP_SPD_Volt];
              }
            }
          }
        }
      }

      // Save determined voltage
      NBPtr->RefPtr->AmpVoltage = Volt;

      // Set up Family Specific Hook for AMP voltage display
      NBPtr->FamilySpecificHook[AmpVoltageDisp] = MemNAmpVoltageDispUnb;

      // Set flag to tell that AMP is exactly enabled internally
      NBPtr->IsSupported[AMPIsEnabled] = TRUE;

      // Tell that AMP voltage is valid
      NBPtr->RefPtr->AmpStatus.AmpVoltageValid = TRUE;

    } else {
      // AMP selected but not enabled
      IDS_HDT_CONSOLE (MEM_FLOW, "Warning : AMP selected but not enabled !\n");
      if (NBPtr->RefPtr->AmpWarningMsgEnable) {
        IDS_HDT_CONSOLE (MEM_FLOW, "Put warning event log of AMP ...\n");
        PutEventLog (AGESA_WARNING, MEM_WARNING_AMP_SELECTED_BUT_NOT_ENABLED, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
        SetMemError (AGESA_WARNING, NBPtr->MCTPtr);

        NBPtr->RefPtr->AmpStatus.AmpSelectedButNotEnabled = TRUE;
      }
    }
  } else {
    // AMP support detected but not enabled
    IDS_HDT_CONSOLE (MEM_FLOW, "Warning : AMP support detected but not enabled !\n");
    if (NBPtr->RefPtr->AmpWarningMsgEnable) {
      IDS_HDT_CONSOLE (MEM_FLOW, "Put warning event log of AMP ...\n");
      PutEventLog (AGESA_WARNING, MEM_WARNING_AMP_SUPPORT_DETECTED_BUT_NOT_ENABLED, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_WARNING, NBPtr->MCTPtr);

      NBPtr->RefPtr->AmpStatus.AmpSupportDetectedButNotEnabled = TRUE;
    }
  }

  return TRUE;
}


