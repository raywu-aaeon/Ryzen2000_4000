/* $NoKeywords:$ */
/**
 * @file
 *
 * mttecc.c
 *
 * Technology ECC byte support
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_TECHLIB_MTTECC_FILECODE
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

VOID
STATIC
MemTCalcDQSEccTmg (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm,
  IN       UINT8 Type,
  IN OUT   VOID  *DlyArray
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function sets the DQS ECC timings
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTSetDQSEccTmgs (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  UINT8 Dct;
  UINT8 Dimm;
  UINT8 i;

  MEM_NB_BLOCK *NBPtr;
  CH_DEF_STRUCT *ChannelPtr;

  NBPtr = TechPtr->NBPtr;
  if (NBPtr->MCTPtr->NodeMemSize) {
    for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
      NBPtr->SwitchDCT (NBPtr, Dct);
      if (NBPtr->DCTPtr->Timings.DctMemSize != 0) {
        ChannelPtr = NBPtr->ChannelPtr;
        for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
          if (NBPtr->DCTPtr->Timings.CsEnabled & ((UINT16)1 << (Dimm * 2))) {
            i = Dimm * TechPtr->DlyTableWidth ();
            MemTCalcDQSEccTmg (TechPtr, Dimm, AccessRcvEnDly, &ChannelPtr->RcvEnDlys[i]);
            MemTCalcDQSEccTmg (TechPtr, Dimm, AccessRdDqsDly, &ChannelPtr->RdDqsDlys[i]);
            MemTCalcDQSEccTmg (TechPtr, Dimm, AccessWrDatDly, &ChannelPtr->WrDatDlys[i]);
          }
        }
      }
    }
  }
  return (BOOLEAN) (NBPtr->MCTPtr->ErrCode < AGESA_FATAL);
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function calculates the DQS ECC timings
 *
 *     @param[in,out]   *TechPtr - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Dimm - Dimm number
 *     @param[in]       Type - Type of DQS timing
 *     @param[in,out]   *DlyArray - Pointer to the array of delays per this Dimm
 *
 */

VOID
STATIC
MemTCalcDQSEccTmg (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm,
  IN       UINT8 Type,
  IN OUT   VOID  *DlyArray
  )
{
  UINT8 i;
  UINT8 j;
  UINT8 Scale;
  UINT8 EccByte;
  UINT16 ByteiDly;
  UINT16 BytejDly;
  UINT16 EccDly;
  UINT8 *WrDqsDly;
  MEM_NB_BLOCK *NBPtr;
  CH_DEF_STRUCT *ChannelPtr;

  NBPtr = TechPtr->NBPtr;
  ChannelPtr = NBPtr->ChannelPtr;

  EccByte = TechPtr->MaxByteLanes ();
  i = (UINT8) (ChannelPtr->DctEccDqsLike & 0xFF);
  j = (UINT8) (ChannelPtr->DctEccDqsLike >> 8);
  Scale = ChannelPtr->DctEccDqsScale;
  WrDqsDly = &ChannelPtr->WrDqsDlys[Dimm * TechPtr->DlyTableWidth ()];

  if (Type == AccessRcvEnDly) {
    ByteiDly = ((UINT16 *) DlyArray)[i];
    BytejDly = ((UINT16 *) DlyArray)[j];
  } else {
    ByteiDly = ((UINT8 *) DlyArray)[i];
    BytejDly = ((UINT8 *) DlyArray)[j];
  }

  //
  // For WrDatDly, Subtract TxDqs Delay to get
  //  TxDq-TxDqs Delta, which is what should be averaged.
  //
  if (Type == AccessWrDatDly) {
    ByteiDly = ByteiDly - WrDqsDly[i];
    BytejDly = BytejDly - WrDqsDly[j];
  }

  if (BytejDly > ByteiDly) {
    EccDly = ByteiDly + (UINT8) (((UINT16) (BytejDly - ByteiDly) * Scale + 0x77) / 0xFF);
    //                                                            Round up --^
  } else {
    EccDly = BytejDly + (UINT8) (((UINT16) (ByteiDly - BytejDly) * (0xFF - Scale) + 0x77) / 0xFF);
    //                                                                     Round up --^
  }

  if (Type == AccessRcvEnDly) {
    ((UINT16 *) DlyArray)[EccByte] = EccDly;
  } else {
    ((UINT8 *) DlyArray)[EccByte] = (UINT8) EccDly;
  }

  //
  // For WrDatDly, Add back the TxDqs value for ECC bytelane
  //
  if (Type == AccessWrDatDly) {
    EccDly = EccDly + WrDqsDly[EccByte];
  }

  NBPtr->SetTrainDly (NBPtr, Type, DIMM_BYTE_ACCESS (Dimm, EccByte), EccDly);
}

