/* $NoKeywords:$ */
/**
 * @file
 *
 * mttEdgeDetect.c
 *
 * DQS R/W position training utilizing Data Eye Edge Detection for optimization
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
#include "mttEdgeDetect.h"
#include "OptionMemory.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_TECHLIBNULL_MTTEDGEDETECT_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */


#define LAST_DELAY    (-128)
#define INC_DELAY     1
#define DEC_DELAY     0



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

/**
 * Sweep Table For Byte Training without insertion delay
 *
*/
DQS_POS_SWEEP_TABLE SweepTableByte[] =
{
  //     Begin  End   Inc/Dec  Step  EndResult Edge
  {      0x00,  0x1F, INC_DELAY,  4, 0xFFFF,   LEFT_EDGE},  /// For Left Edge, start from 0 and Increment to 0x1F by 4 until all PASS
  { LAST_DELAY, 0x00, DEC_DELAY, -1, 0xFE00,   LEFT_EDGE},  ///  Then go back down to 0x00 by 1 until all FAIL
  {      0x1F,  0x00, DEC_DELAY, -4, 0xFFFF,   RIGHT_EDGE}, /// For Right Edge, start from 0x1F down to 0 until all PASS.
  { LAST_DELAY, 0x1F, INC_DELAY,  1, 0xFE00,   RIGHT_EDGE}  ///  Then go back up by 1 until all FAIL.
};
/**
 * Sweep Table For Byte Training with insertion delay
 *
*/
DQS_POS_SWEEP_TABLE InsSweepTableByte[] =
{
  //     Begin  End   Inc/Dec  Step  EndResult Edge
  {      0x00, -0x20, DEC_DELAY, -4, 0xFE00, LEFT_EDGE},  /// For Left Edge, start from 0 and Decrement to -0x20 by -4 until all FAIL
  { LAST_DELAY, 0x1F, INC_DELAY,  1, 0xFFFF, LEFT_EDGE},  ///  Then go back up to 0x1F by 1 until all PASS
  {      0x1F,  0x00, DEC_DELAY, -4, 0xFFFF, RIGHT_EDGE}, /// For Right Edge, start from 0x1F down to 0 until all PASS.
  { LAST_DELAY, 0x1F, INC_DELAY,  1, 0xFE00, RIGHT_EDGE}  ///  Then go back up by 1 until all FAIL.
};

BOOLEAN
STATIC
MemTTrainDQSRdWrEdgeDetect (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

BOOLEAN
STATIC
MemTInitTestPatternAddress (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr
  );

BOOLEAN
STATIC
MemTContinueSweep (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr
  );

BOOLEAN
STATIC
MemTSetNextDelay (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr
  );

UINT8
STATIC
MemTScaleDelayVal (
  IN OUT MEM_TECH_BLOCK *TechPtr,
  IN INT8 Delay
  );

BOOLEAN
STATIC
MemTDataEyeSave (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr,
  IN       UINT8 ByteLane
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
extern MEM_FEAT_TRAIN_SEQ memTrainSequenceDDR3[];
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function executes DQS position training for all a Memory channel using
 *     the Edge Detection algorithm.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */

BOOLEAN
MemTTrainDQSEdgeDetectSw (
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
 *      This Executes Read DQS and Write Data Position training on a chip select pair
 *  using the Edge Detection algorithm.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - No Errors occurred
 *     @return  FALSE - Errors occurred

 */

BOOLEAN
STATIC
MemTTrainDQSRdWrEdgeDetect (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function executes DQS position training for both read and write, using
 *     the Edge Detection Algorithm.  This method searches for the beginning and end
 *     of the Data Eye with out scanning every DSQ delay value. The following is a
 *     detailed description of the algorithm:
 *
 *     Four-Stage Data Eye Sweep
 *
 *     -Search starts at Delay value of 0.
 *     -Search left in steps of 4/32UI looking for all Byte lanes Passing. Left from zero rolls over to a negative value.
 *     -Negative values are translated to the high end of the delay range, but using Insertion delay comparison.
 *     -For each passing byte lane, freeze delay at first passing value, but set mask so next steps will not compare for byte lanes that previously passed
 *     -Switch to search right in steps of 1/32UI looking for fail.
 *     -For each lane, starting delay for 1/32 sweep right is first passing delay from 4/32 sweep left.
 *     -For each failing byte lane, freeze delay at first failing value, but set mask so next steps will not compare for byte lanes that previously failed
 *     -Search right until all byte lanes have failed
 *     -For each lane, right edge used by BIOS will be first failing delay value minus 1/32

 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - All bytelanes pass
 *     @return  FALSE - Some bytelanes fail
*/
BOOLEAN
MemTTrainDQSEdgeDetect (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Initialize the Test Pattern Address for two chip selects and, if this
 *     is a Write Data Eye, write the initial test pattern.
 *
 *     Test Address is stored in the Sweep info struct.  If Memory is not present
 *     then return with False.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   *SweepPtr -  Pointer to SWEEP_INFO structure.
 *
 *     @return  BOOLEAN
 *              TRUE  - Memory is present
 *              FALSE - No memory present on this Chip Select pair.
 *
**
 */
BOOLEAN
STATIC
MemTInitTestPatternAddress (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *     Test Conditions for exiting the training loop, set the next delay value,
 *     and return status
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   *SweepPtr -  Pointer to SWEEP_INFO structure.
 *
 *     @return  BOOLEAN
 *              TRUE  - Continue to test with next delay setting
 *              FALSE - Exit training loop.  Either the result has been found or
 *                      end of delay range has been reached.
*/
BOOLEAN
STATIC
MemTContinueSweep (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function sets the next delay value for each bytelane that needs to
 *      be advanced.  It checks the bounds of the delay to see if we are at the
 *      end of the range.  If we are to close to advance a whole step value, but
 *      not at the boundary, then we set the delay to the boundary.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   *SweepPtr -  Pointer to SWEEP_INFO structure.
 *
 */

BOOLEAN
STATIC
MemTSetNextDelay (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function accepts a delay value in 32nd of a UI and converts it to an
 *     actual register value, taking into consideration NB type, rd/wr,
 *     and frequency.
 *
 *     Delay = (Min + (Delay * ( (Max - Min) / TRN_DELAY_MAX) )) & Mask
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       *Delay     - INT8 of delay value;
 *
 *     @return  UINT8 of the adjusted delay value
*/
UINT8
STATIC
MemTScaleDelayVal (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       INT8 Delay
  )
{
  return 0;
}





/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function calculates the Center of the Data eye for the specified byte lane
 *       and stores its DQS Delay value for reference.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   *SweepPtr -  Pointer to SWEEP_INFO structure.
 *     @param[in]       ByteLane  -  Bytelane number being targeted
 *
 */
BOOLEAN
STATIC
MemTDataEyeSave (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   SWEEP_INFO *SweepPtr,
  IN       UINT8 ByteLane
  )
{
  return TRUE;
}


