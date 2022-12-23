/* $NoKeywords:$ */
/**
 * @file
 *
 * mttecc3.c
 *
 * Technology ECC byte support for registered DDR3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR3)
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
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_TECHDDR3LIB_MTTECC3_FILECODE
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
 *   This function sets the DQS ECC timings for registered DDR3
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTSetDQSEccTmgsRDdr3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 Dct;
  UINT8 Dimm;
  UINT8 i;
  UINT8 *WrDqsDly;
  UINT16 *RcvEnDly;
  UINT8 *RdDqsDly;
  UINT8 *WrDatDly;
  UINT8 EccByte;
  INT16 TempValue;

  MEM_NB_BLOCK *NBPtr;
  CH_DEF_STRUCT *ChannelPtr;

  EccByte = TechPtr->MaxByteLanes ();
  NBPtr = TechPtr->NBPtr;

  if (NBPtr->MCTPtr->NodeMemSize) {
    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      NBPtr->SwitchDCT (NBPtr, Dct);
      if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
        ChannelPtr = NBPtr->ChannelPtr;
        for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
          if (NBPtr->DCTPtr->Timings.CsEnabled & ((UINT16)3 << (Dimm * 2))) {
            i = Dimm * TechPtr->DlyTableWidth ();
            WrDqsDly = &ChannelPtr->WrDqsDlys[i];
            RcvEnDly = &ChannelPtr->RcvEnDlys[i];
            RdDqsDly = &ChannelPtr->RdDqsDlys[i];
            WrDatDly = &ChannelPtr->WrDatDlys[i];
            // Receiver DQS Enable:
            // Receiver DQS enable for ECC bytelane = Receiver DQS enable for bytelane 3 -
            //                                        [write DQS for bytelane 3 - write DQS for ECC]

            TempValue = (INT16) RcvEnDly[3] - (INT16) (WrDqsDly[3] - WrDqsDly[EccByte]);
            if (TempValue < 0) {
              TempValue = 0;
            }
            RcvEnDly[EccByte] = (UINT16) TempValue;

            // Read DQS:
            // Read DQS for ECC bytelane = read DQS of byte lane 3
            //
            RdDqsDly[EccByte] = RdDqsDly[3];

            // Write Data:
            // Write Data for ECC bytelane = Write DQS for ECC +
            //                               [write data for bytelane 3 - Write DQS for bytelane 3]
            TempValue = (INT16) (WrDqsDly[EccByte] + (INT8) (WrDatDly[3] - WrDqsDly[3]));
            if (TempValue < 0) {
              TempValue = 0;
            }
            WrDatDly[EccByte] = (UINT8) TempValue;

            NBPtr->SetTrainDly (NBPtr, AccessRcvEnDly, DIMM_BYTE_ACCESS (Dimm, EccByte), RcvEnDly[EccByte]);
            NBPtr->SetTrainDly (NBPtr, AccessRdDqsDly, DIMM_BYTE_ACCESS (Dimm, EccByte), RdDqsDly[EccByte]);
            NBPtr->SetTrainDly (NBPtr, AccessWrDatDly, DIMM_BYTE_ACCESS (Dimm, EccByte), WrDatDly[EccByte]);
          }
        }
      }
    }
  }
  return (BOOLEAN) (NBPtr->MCTPtr->ErrCode < AGESA_FATAL);
}
