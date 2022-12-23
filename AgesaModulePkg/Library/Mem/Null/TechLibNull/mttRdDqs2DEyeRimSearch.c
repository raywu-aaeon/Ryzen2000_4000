/* $NoKeywords:$ */
/**
 * @file
 *
 * mttRdDqs2DEyeRimmSearch.c
 *
 * RD DQS 2 Dimentional Training using Eye Rim Sampling
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

#define FILECODE LIBRARY_MEM_NULL_TECHLIBNULL_MTTRDDQS2DEYERIMSEARCH_FILECODE

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
MemTInitializeEyeRimSearch (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

VOID
MemTEyeFill (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

BOOLEAN
CheckSaveResAtEdge (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN   UINT8 lane,
  IN   INT8 y,
  IN   INT8 x,
  IN   INT8 xdir
  );

UINT8
DetermineSavedState (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN   UINT8 lane,
  IN   INT8 y,
  IN   INT8 x
  );

UINT8
GetPassFailValue (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN   UINT8 lane,
  IN   INT8 y,
  IN   INT8 x
  );

VOID
SetPassFailValue (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN   UINT8 lane,
  IN   INT8 y,
  IN   INT8 x,
  IN   UINT8 result
  );

VOID
SetSavedState (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN   UINT8 lane,
  IN   INT8 y,
  IN   INT8 x,
  IN   UINT8 result
  );

INT8 MemTGet1DTrainedEyeCenter (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN UINT8 lane
  );

BOOLEAN
CheckForFail (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN   UINT8 lane,
  IN   INT8 y,
  IN   INT8 x
  );

BOOLEAN
AllocateSaveLaneStorage (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

INT8
xlateY (
  IN INT8 y
  );

BOOLEAN
ClearSampledPassResults (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Initialize Eye Rim Search
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE
 */
BOOLEAN
MemTInitializeEyeRimSearch (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *     This function collects data for Eye Rim Search
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred
 */
BOOLEAN
MemT2DRdDQSEyeRimSearch (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *     Fill the data eye
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return
 */
VOID
MemTEyeFill (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *    Get the 1D trained center
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]  lane - current lane
 *
 *     @return
 */
INT8
MemTGet1DTrainedEyeCenter (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Determine if the saved value is at or close to the edge
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *lane   - current lane
 *     @param[in]   y   -  vref value
 *     @param[in]   x   -  RdDqs value
 *     @param[in]   xdir   -  x-direction
 *
 *     @return  TRUE - close to edge, FALSE - not close to edge
 */
BOOLEAN
CheckSaveResAtEdge (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane,
  IN       INT8 y,
  IN       INT8 x,
  IN       INT8 xdir
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    determine if a BL has been saved
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   lane   - current lane
 *     @param[in]   y   -  vref value
 *     @param[in]   x   -  RdDqs value
 *
 *     @return  1 - value saved, 0 - value not saved
 */
UINT8
DetermineSavedState (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane,
  IN       INT8 y,
  IN       INT8 x
  )
{
  return 0;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *    Determine if a failure has occured
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   lane   - current lane
 *     @param[in]   y   -  vref value
 *     @param[in]   x   -  RdDqs value
 *
 *     @return  2 - Fail, 3 - Pass
 */
BOOLEAN
CheckForFail (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane,
  IN       INT8 y,
  IN       INT8 x
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *    Get pass fail state of lane
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   lane   - current lane
 *     @param[in]   y   -  vref value
 *     @param[in]   x   -  RdDqs value
 *
 *     @return  0 - Value not saved, 2 - Fail, 3 - Pass
 */
UINT8
GetPassFailValue (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane,
  IN       INT8 y,
  IN       INT8 x
  )
{
  return 0;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *    Set the Pass/Fail state of lane
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *lane   - current lane
 *     @param[in]   y   -  vref value
 *     @param[in]   x   -  RdDqs value
 *     @param[in]   result   -  result value
 *
 *     @return  Saved Value
 */
VOID
SetPassFailValue (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane,
  IN       INT8 y,
  IN       INT8 x,
  IN       UINT8 result
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *    Set the save state of lane
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   *lane   - current lane
 *     @param[in]   y   -  vref value
 *     @param[in]   x   -  RdDqs value
 *     @param[in]   result   -  result value
 *
 *     @return  Saved Value
 */
VOID
SetSavedState (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 lane,
  IN       INT8 y,
  IN       INT8 x,
  IN       UINT8 result
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *    Allocate data storage
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  FALSE - No Errors occurred
 *     @return  TRUE - Errors occurred
 */
BOOLEAN
AllocateSaveLaneStorage (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Translate Vref into a positive, linear value that can be used as an
 *      array index.
 *
 *     @param[in]   y   -  vref value
 *
 *     @return  Saved Value
 */
INT8
xlateY (
  IN INT8 y
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Re-walking the eye rim for each aggressor combination, which invalidates previous Passes
 *     in the sample array.  Previous Fails in the sample array remain valid. Knowledge of previous Fails
 *     and speeds sampling for the subsequent walks, esp. when used in conjunction w/ ParallelSampling
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE
 */
BOOLEAN
ClearSampledPassResults (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

