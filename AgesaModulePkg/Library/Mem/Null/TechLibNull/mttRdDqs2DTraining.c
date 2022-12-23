/* $NoKeywords:$ */
/**
 * @file
 *
 * mttRdDqs2DTraining.c
 *
 * RD DQS 2 dimentional training
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Library/AmdHeapLib.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mt.h"
#include "mport.h"
#include "merrhdl.h"
#include "Filecode.h"
#include "OptionMemory.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_TECHLIBNULL_MTTRDDQS2DTRAINING_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define MAX_DELAYS    9   /* 8 data bytes + 1 ECC byte */
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
MemT2DRdDQSProcessConvolution (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
  extern MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[];

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function executes 2D training for Rd DQS
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */

BOOLEAN
MemTAmdRdDqs2DTraining (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}
/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function determines the maximum number of lanes to program 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - Configuration valid
 *              FALSE - Configuration invalid
 */
BOOLEAN
MemTCheck2DTrainingPerConfig (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return FALSE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function determines the maximum number of lanes to program 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - Max Number of Lanes
 */
UINT8
MemT2DGetMaxLanes (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return 0;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs Vref to internal or external control for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */
VOID
MemT2DProgramIntExtVrefSelect (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs Vref for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Vref - Vref value
 *
 */
VOID
MemT2DProgramVref (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Vref
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs RdDQS for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       RdDQSDly -  RdDqs value
 *
 */
VOID
MemT2DPrograRdDQSDly (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 RdDQSDly
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function stores data for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *     @param[in]   *InPhaseResult[]   - Array of inphase results
 *     @param[in]   *PhaseResult180[]   - Array of Phase 180 results
 *
 *     @return  TRUE - No Errors occurred
 */
VOID
StoreResult (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data,
  IN       UINT32 InPhaseResult[],
  IN       UINT32 PhaseResult180[]
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function determines the height of data for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */
BOOLEAN
MemT2DRdDQSHeight (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function gets the width for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  width
 */
UINT8
MemGet2dRdDQSWidth (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return 0;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function gets the step height for the dimond mask for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *     @param[in]   Vref   - current Vref value
 *     @param[in]   Lane   - current Lane
 *
 *     @return  TRUE - Step found and value should be updated
 *              FALSE - Step not found and value should not be updated
 */
BOOLEAN
MemCheck2dRdDQSDiamondMaskStep (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data,
  IN       UINT8 Vref,
  IN       UINT8 Lane
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function applies a mask fo 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */
BOOLEAN
MemT2DRdDQSApplyMask (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function Examines the convolution function and determines the Max RDqs for
 *     2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */

BOOLEAN
MemT2DRdDQSProcessConvolution (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function programs the Max RDqs for 2D RdDQS training from convolution
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */
BOOLEAN
MemT2DRdDQSPrograMaxRdDQSDly (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function finds the Positive and negative Vref Margin for the current CS
 *     for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */
BOOLEAN
MemT2DRdDQSFindCsVrefMargin (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function finds the final Vref Margin for 2D RdDQS training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */
BOOLEAN
MemT2DRdDQSFinalVrefMargin (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function displays ther results of the 2D search
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *Data   - Pointer to Result data structure
 *
 *     @return
 */
VOID
MemT2DRdDqsDisplaySearch (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       MEM_2D_ENTRY *Data
  )
{

}

