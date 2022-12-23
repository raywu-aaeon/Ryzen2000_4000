/* $NoKeywords:$ */
/**
 * @file
 *
 * mfemp.c
 *
 * Feature EMP initialization functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/ECC)
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
#include "mm.h"
#include "mn.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATECCLIB_MFEMP_FILECODE
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
IsPowerOfTwo (
  IN       UINT32 TestNumber
  );

BOOLEAN
MemFInitEMP (
  IN OUT   MEM_NB_BLOCK *NBPtr
  );

/*
 *-----------------------------------------------------------------------------
 *                                EXPORTED FUNCTIONS
 *
 *-----------------------------------------------------------------------------
 */

extern BUILD_OPT_CFG UserOptions;

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initializes EMP (Enhanced Memory Protection)
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE -  This feature is enabled.
 *     @return          FALSE - This feature is not enabled.
 */

BOOLEAN
MemFInitEMP (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  MEM_PARAMETER_STRUCT *RefPtr;
  DIE_STRUCT *MCTPtr;

  ASSERT (NBPtr != NULL);

  RefPtr = NBPtr->RefPtr;
  MCTPtr = NBPtr->MCTPtr;

  if (RefPtr->EnableEccFeature) {
    if (NBPtr->GetBitField (NBPtr, BFEnhMemProtCap) == 0) {
      PutEventLog (AGESA_WARNING, MEM_WARNING_EMP_NOT_SUPPORTED, 0, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
      MCTPtr->ErrStatus[EsbEMPNotSupported] = TRUE;
    } else if (RefPtr->EnableChannelIntlv || RefPtr->EnableBankIntlv || RefPtr->EnableBankSwizzle) {
      PutEventLog (AGESA_WARNING, MEM_WARNING_EMP_CONFLICT, 0, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
      MCTPtr->ErrStatus[EsbEMPConflict] = TRUE;
    } else if ((!MCTPtr->GangedMode) &&
               (!IsPowerOfTwo (MCTPtr->DctData[0].Timings.DctMemSize) &&
                !IsPowerOfTwo (MCTPtr->DctData[1].Timings.DctMemSize))) {
      PutEventLog (AGESA_WARNING, MEM_WARNING_EMP_NOT_ENABLED, 0, 0, 0, 0, &NBPtr->MemPtr->StdHeader);
      MCTPtr->ErrStatus[EsbEMPDis] = TRUE;
    } else {
      // Reduce memory size to 7/8 of the original memory size
      ASSERT ((MCTPtr->NodeMemSize % 8) == 0);
      NBPtr->SetBitField (NBPtr, BFDramHoleValid, 0);
      MCTPtr->NodeMemSize = (MCTPtr->NodeMemSize / 8) * 7;
      NBPtr->HtMemMapInit (NBPtr);
      NBPtr->CpuMemTyping (NBPtr);

      // Enable EMP
      NBPtr->SetBitField (NBPtr, BFDramEccEn, 1);

      // Scrub CTL settings for Dcache, L2
      NBPtr->SetBitField (NBPtr, BFL2Scrub, UserOptions.CfgScrubL2Rate);
      NBPtr->SetBitField (NBPtr, BFDcacheScrub, UserOptions.CfgScrubDcRate);

      NBPtr->SetBitField (NBPtr, BFSyncOnUcEccEn, UserOptions.CfgEccSyncFlood);
      return TRUE;
    }
  }
  return FALSE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function checks to see if the input is power of two.
 *
 *     @param[in]    TestNumber  - Value to check for power of two
 *
 *     @return          TRUE     - is power of two
 *                      FALSE    - is not power of two
 */
BOOLEAN
STATIC
IsPowerOfTwo (
  IN       UINT32 TestNumber
  )
{
  return (BOOLEAN) ((TestNumber & (TestNumber - 1)) == 0);
}

