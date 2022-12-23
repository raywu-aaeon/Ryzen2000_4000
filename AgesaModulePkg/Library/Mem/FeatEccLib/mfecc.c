/* $NoKeywords:$ */
/**
 * @file
 *
 * mfecc.c
 *
 * Feature ECC initialization functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/ECC)
 * @e \$Revision: 313790 $ @e \$Date: 2015-02-27 13:31:28 +0800 (Fri, 27 Feb 2015) $
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
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "Library/AmdMemFeatEccLib.h"
#include "Filecode.h"
#include "mfmemclr.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATECCLIB_MFECC_FILECODE
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
InitECCOverriedeStruct (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   ECC_OVERRIDE_STRUCT *pecc_override_struct
  );

BOOLEAN
MemFCheckECC (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

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
 *      This function checks to see if ECC can be enabled on all nodes
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */

BOOLEAN
MemFCheckECC (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  DIE_STRUCT *MCTPtr;
  MEM_SHARED_DATA *SharedPtr;
  BOOLEAN ErrorRecovery;
  UINT32   EccCapable;

  ASSERT (NBPtr != NULL);

  MCTPtr = NBPtr->MCTPtr;
  SharedPtr = NBPtr->SharedPtr;

  ErrorRecovery = TRUE;
  IDS_OPTION_HOOK (IDS_MEM_ERROR_RECOVERY, &ErrorRecovery, &NBPtr->MemPtr->StdHeader);

  //
  // Check if respective silicon supports Ecc by querying F3xE8[Ecc].
  //
  EccCapable = NBPtr->GetBitField (NBPtr, BFEccCapable);
  IDS_HDT_CONSOLE (MEM_FLOW, "ECC Capable: %d\n", EccCapable);

  if (MCTPtr->NodeMemSize != 0) {
    if (SharedPtr->AllECC && MCTPtr->Status[SbEccDimms] && (ErrorRecovery || (MCTPtr->ErrCode < AGESA_ERROR) && EccCapable)) {
      // Clear all MCA reports before using scrubber
      // to initialize ECC check bits
      //
      NBPtr->McaNbCtlReg = NBPtr->GetBitField (NBPtr, BFMcaNbCtlReg);
      NBPtr->SetBitField (NBPtr, BFMcaNbCtlReg, 0);
      NBPtr->SetBitField (NBPtr, BFSyncOnUcEccEn, 0);
      // In unganged mode, set DctDctIntlv
      if (!NBPtr->Ganged) {
        NBPtr->SetBitField (NBPtr, BFDctDatIntLv, 1);
      }
      //
      // Set Ecc Symbol Size
      //
      NBPtr->SetEccSymbolSize (NBPtr);
      // If ECC can be enabled on this node,
      // set the master ECCen bit (according to setup)
      //
      NBPtr->SetBitField (NBPtr, BFDramEccEn, 1);
      // With ECC enabled MemClr must be performed
      NBPtr->RefPtr->EnableMemClr = TRUE;
      // Do mem clear on current node
      MemFMctMemClr_Init (NBPtr);
      return TRUE;
    } else {
      if (SharedPtr->AllECC) {
        SharedPtr->AllECC = FALSE;
      }
      // ECC requested but cannot be enabled
      MCTPtr->Status[SbEccDimms] = FALSE;
      MCTPtr->ErrStatus[EsbDramECCDis] = TRUE;
      PutEventLog (AGESA_WARNING, MEM_WARNING_ECC_DIS, NBPtr->Node, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_WARNING, MCTPtr);
    }
  }
  return FALSE;
}

  /* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initializes the ECC on all nodes
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */

BOOLEAN
MemFInitECC (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT8 Node;
  UINT32 ScrubAddrRJ16;
  DIE_STRUCT *MCTPtr;
  MEM_SHARED_DATA *SharedPtr;
  ECC_OVERRIDE_STRUCT  ecc_override_struct;
  BOOLEAN Flag;

  InitECCOverriedeStruct (NBPtr, &ecc_override_struct);
  IDS_OPTION_HOOK (IDS_ECC, &ecc_override_struct, &(NBPtr->MemPtr->StdHeader));

  ASSERT (NBPtr != NULL);

  MCTPtr = NBPtr->MCTPtr;
  Node = MCTPtr->NodeId;
  SharedPtr = NBPtr->SharedPtr;
  Flag = TRUE;

  NBPtr->FamilySpecificHook[ScrubberErratum] (NBPtr, (VOID *) &Flag);

  if ((MCTPtr->Status[SbEccDimms]) && (SharedPtr->AllECC)) {
    // Check if the input dram scrub rate is supported or not
    ASSERT (ecc_override_struct.CfgScrubDramRate <= 0x16);
    if (ecc_override_struct.CfgScrubDramRate != 0) {
    // Program scrub address,
    // let the scrub Addr be the Base of this Node
    // Only enable Dram scrubber when there is memory on current node
    //
      NBPtr->SetBitField (NBPtr, BFScrubReDirEn, 0);
      ScrubAddrRJ16 = (NBPtr->GetBitField (NBPtr, BFDramBaseReg0 + Node) & 0xFFFF0000) >> 8;
      ScrubAddrRJ16 |= NBPtr->GetBitField (NBPtr, BFDramBaseHiReg0 + Node) << 24;
      NBPtr->SetBitField (NBPtr, BFScrubAddrLoReg, ScrubAddrRJ16 << 16);
      NBPtr->SetBitField (NBPtr, BFScrubAddrHiReg, ScrubAddrRJ16 >> 16);
      NBPtr->BrdcstSet (NBPtr, BFDramScrub, ecc_override_struct.CfgScrubDramRate);
      NBPtr->IsSupported[ScrubberEn] = TRUE;
    }
  }
  // Scrub CTL for Dcache, L2, L3
  // Check if the input L2 scrub rate is supported or not
  ASSERT (ecc_override_struct.CfgScrubL2Rate <= 0x16);
  NBPtr->SetBitField (NBPtr, BFL2Scrub, ecc_override_struct.CfgScrubL2Rate);
  // Check if the input Dcache scrub rate is supported or not
  ASSERT (ecc_override_struct.CfgScrubDcRate <= 0x16);
  NBPtr->SetBitField (NBPtr, BFDcacheScrub, ecc_override_struct.CfgScrubDcRate);
  // Do not enable L3 Scrub if F3xE8[L3Capable] is 0 or F3x188[DisableL3] is 1
  if ((NBPtr->GetBitField (NBPtr, BFL3Capable) == 1) && (NBPtr->GetBitField (NBPtr, BFDisableL3) == 0)) {
    // Check if input L3 scrub rate is supported or not
    ASSERT (ecc_override_struct.CfgScrubL3Rate <= 0x16);
    NBPtr->SetBitField (NBPtr, BFL3Scrub, ecc_override_struct.CfgScrubL3Rate);
  }

  // Check if Dcache scrubber or L2 scrubber is enabled
  if ((ecc_override_struct.CfgScrubL2Rate != 0) || (ecc_override_struct.CfgScrubDcRate!= 0)) {
    // If ClkDivisor is deeper than divide-by-16
    if (NBPtr->GetBitField (NBPtr, BFC1ClkDivisor) > 4) {
      // Set it to divide-by-16
      NBPtr->SetBitField (NBPtr, BFC1ClkDivisor, 4);
    }
  }

  NBPtr->SetBitField (NBPtr, BFScrubReDirEn, ecc_override_struct.CfgEccRedirection);
  NBPtr->SetBitField (NBPtr, BFSyncOnUcEccEn, ecc_override_struct.CfgEccSyncFlood);
  // Restore MCA reports after scrubber is done
  // with initializing ECC check bits
  NBPtr->SetBitField (NBPtr, BFMcaNbCtlReg, NBPtr->McaNbCtlReg);

  Flag = FALSE;
  NBPtr->FamilySpecificHook[ScrubberErratum] (NBPtr, (VOID *) &Flag);

  NBPtr->FamilySpecificHook[DramScrubErratum792] (NBPtr, NULL);
  return TRUE;
}

VOID
STATIC
InitECCOverriedeStruct (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   ECC_OVERRIDE_STRUCT *pecc_override_struct
  )
{
  MEM_PARAMETER_STRUCT *RefPtr;

  RefPtr = NBPtr->RefPtr;
  //
  // If (D18F3x44[DramEccEn]==1) THEN 1 ELSE 0 ENDIF
  //
  if (NBPtr->GetBitField (NBPtr, BFDramEccEn) == 1) {
    pecc_override_struct->CfgEccRedirection = 1;
  } else {
    pecc_override_struct->CfgEccRedirection = 0;
  }

  pecc_override_struct->CfgEccSyncFlood = RefPtr->EccSyncFlood;
  pecc_override_struct->CfgScrubDcRate = RefPtr->ScrubDcRate;

  if (RefPtr->ScrubDramRate != 0xFF) {
    pecc_override_struct->CfgScrubDramRate = RefPtr->ScrubDramRate;
  } else {
    if (NBPtr->MCTPtr->NodeMemSize <= 0x4000) {
      pecc_override_struct->CfgScrubDramRate = 0x12; // 1 ~ 1 GB
    } else if (NBPtr->MCTPtr->NodeMemSize <= 0x8000) {
      pecc_override_struct->CfgScrubDramRate = 0x11; // 1 GB + 1 ~ 2 GB
    } else if (NBPtr->MCTPtr->NodeMemSize <= 0x10000) {
      pecc_override_struct->CfgScrubDramRate = 0x10; // 2 GB + 1 ~ 4 GB
    } else if (NBPtr->MCTPtr->NodeMemSize <= 0x20000) {
      pecc_override_struct->CfgScrubDramRate = 0x0F; // 4 GB + 1 ~ 8 GB
    } else if (NBPtr->MCTPtr->NodeMemSize <= 0x40000) {
      pecc_override_struct->CfgScrubDramRate = 0x0E; // 8 GB + 1 ~ 16 GB
    } else {
      pecc_override_struct->CfgScrubDramRate = 0x0D; //16 GB + 1 above
    }
  }

  pecc_override_struct->CfgScrubL2Rate = RefPtr->ScrubL2Rate;
  pecc_override_struct->CfgScrubL3Rate = RefPtr->ScrubL3Rate;
}

