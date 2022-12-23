/* $NoKeywords:$ */
/**
 * @file
 *
 * mttdimmbt.c
 *
 * Technology Dimm Based Training
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
#include "mm.h"
#include "mn.h"
#include "mnreg.h"
#include "mt.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_TECHLIBNULL_MTTDIMBT_FILECODE

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
MemTInitDqsPos4RcvrEnByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

VOID
STATIC
MemTSetRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly
  );

VOID
STATIC
MemTLoadRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  );

BOOLEAN
STATIC
MemTSaveRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly,
  IN       UINT16 CmpResultRank0,
  IN       UINT16 CmpResultRank1
  );

VOID
STATIC
MemTResetDctWrPtrByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  );

UINT16
STATIC
MemTCompare1ClPatternByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Buffer[],
  IN       UINT8 Pattern[]
  );

VOID
STATIC
MemTSkipChipSelPass1Byte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *ChipSelPtr
  );

VOID
STATIC
MemTSkipChipSelPass2Byte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *ChipSelPtr
  );

UINT8
STATIC
MemTMaxByteLanesByte ( VOID );

UINT8
STATIC
MemTDlyTableWidthByte ( VOID );

VOID
STATIC
MemTSetDqsDelayCsrByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 ByteLane,
  IN       UINT8 Dly
  );

VOID
STATIC
MemTDqsWindowSaveByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 ByteLane,
  IN       UINT8 DlyMin,
  IN       UINT8 DlyMax
  );

BOOLEAN
STATIC
MemTFindMaxRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
     OUT   UINT8 *ChipSel
  );

UINT16
STATIC
MemTCompare1ClPatternOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Buffer[],
  IN       UINT8 Pattern[],
  IN       UINT8 Side,
  IN       UINT8 Receiver,
  IN       BOOLEAN Side1En
  );

VOID
STATIC
MemTLoadRcvrEnDlyOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  );

VOID
STATIC
MemTSetRcvrEnDlyOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly
  );

VOID
STATIC
MemTLoadInitialRcvEnDlyOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  );

UINT8
STATIC
MemTFindMinMaxGrossDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       TRN_DLY_TYPE TrnDlyType,
  IN       BOOLEAN IfMax
  );
/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */


/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function enables byte based training if called
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */

VOID
MemTDimmByteTrainInit (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{

}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function initializes the DQS Positions in preparation for Receiver Enable Training.
 *  Write Position is no delay, Read Position is 1/2 Memclock delay
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 */

VOID
STATIC
MemTInitDqsPos4RcvrEnByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function programs DqsRcvEnDly to additional index for DQS receiver enabled training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 *     @param[in]       RcvEnDly  - receiver enable delay to be saved
 */

VOID
STATIC
MemTSetRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function loads the DqsRcvEnDly from saved data and program to additional index
 *  for DQS receiver enabled training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 *
 */

VOID
STATIC
MemTLoadRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function saves passing DqsRcvEnDly values to the stack
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 *     @param[in]       RcvEnDly  - receiver enable delay to be saved
 *     @param[in]       CmpResultRank0 - compare result for Rank 0
 *     @param[in]       CmpResultRank1 - compare result for Rank 1
 *
 *     @return  TRUE - All bytelanes pass
 *     @return  FALSE - Some bytelanes fail
 */

BOOLEAN
STATIC
MemTSaveRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly,
  IN       UINT16 CmpResultRank0,
  IN       UINT16 CmpResultRank1
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function performs a filtering functionality and saves passing DqsRcvEnDly
 *  values to the stack
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 *     @param[in]       RcvEnDly  - receiver enable delay to be saved
 *     @param[in]       CmpResultRank0 - compare result for Rank 0
 *     @param[in]       CmpResultRank1 - compare result for Rank 1
 *
 *     @return  TRUE - All bytelanes pass
 *     @return  FALSE - Some bytelanes fail
 */

BOOLEAN
MemTSaveRcvrEnDlyByteFilter (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly,
  IN       UINT16 CmpResultRank0,
  IN       UINT16 CmpResultRank1
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function compares test pattern with data in buffer and return a pass/fail bitmap
 *       for 8 Bytes
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Buffer[]  -  Buffer data from DRAM (Measured data from DRAM) to compare
 *     @param[in]       Pattern[]  - Pattern (Expected data in ROM/CACHE) to compare against
 *
 *     @return  PASS - Bit map of results of comparison
 */

UINT16
STATIC
MemTCompare1ClPatternByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Buffer[],
  IN       UINT8 Pattern[]
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       The function resets the DCT input buffer write pointer.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver - Chip select
 *
 */

VOID
STATIC
MemTResetDctWrPtrByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function skips odd chip select if training at 800MT or above.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       *ChipSelPtr - Pointer to variable contains Chip select index
 *
 */

VOID
STATIC
MemTSkipChipSelPass1Byte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *ChipSelPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  MemTSkipChipSelPass2Byte:
 *
 *       This function skips odd chip select if training at 800MT or above.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   *ChipSelPtr - Pointer to variable contains Chip select index
 *
 */

VOID
STATIC
MemTSkipChipSelPass2Byte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT8 *ChipSelPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function determines the maximum number of byte lanes
 *
 *     @return  Max number of Bytelanes
 */

UINT8
STATIC
MemTMaxByteLanesByte ( VOID )
{
  return MAX_BYTELANES;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function determines the width of the delay tables (eg. RcvEnDlys, WrDqsDlys,...)
 *
 *     @return  Delay table width in bytes
 */

UINT8
STATIC
MemTDlyTableWidthByte ( VOID )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function writes the Delay value to a certain byte lane
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       ByteLane  -  Bytelane number being targeted
 *     @param[in]       Dly - Delay value
 *
 */

VOID
STATIC
MemTSetDqsDelayCsrByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 ByteLane,
  IN       UINT8 Dly
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function programs the trained DQS delay for the specified byte lane
 *       and stores its DQS window for reference.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       ByteLane  -  Bytelane number being targeted
 *     @param[in]       DlyMin - Minimum delay value
 *     @param[in]       DlyMax- Maximum delay value
 *
 */

VOID
STATIC
MemTDqsWindowSaveByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 ByteLane,
  IN       UINT8 DlyMin,
  IN       UINT8 DlyMax
  )
{

}


/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function finds the DIMM that has the largest receiver enable delay.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[out]      *ChipSel   - Pointer to the Chip select that has the largest receiver enable delay.
 *
 *     @return   TRUE - A chip select can be found.
 *     @return   FALSE - A chip select cannot be found.
 */

BOOLEAN
STATIC
MemTFindMaxRcvrEnDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
     OUT   UINT8 *ChipSel
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function finds the DIMM that has the largest receiver enable delay + Read DQS Delay.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[out]      *ChipSel   - Pointer to the Chip select that has the largest receiver enable delay
 *                                   + Read DQS Delay.
 *
 *     @return   TRUE - A chip select can be found.
 *     @return   FALSE - A chip select cannot be found.
 */

BOOLEAN
MemTFindMaxRcvrEnDlyRdDqsDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
     OUT   UINT8 *ChipSel
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function finds the DIMM that has the largest receiver enable delay + Read DQS Delay for UNB
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[out]      *ChipSel   - Pointer to the Chip select that has the largest receiver enable delay
 *                                   + Read DQS Delay.
 *
 *     @return   TRUE - A chip select can be found.
 *     @return   FALSE - A chip select cannot be found.
 */

BOOLEAN
MemTFindMaxRcvrEnDlyRdDqsDlyByteUnb (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
     OUT   UINT8 *ChipSel
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function finds the minimum or maximum gross dly among all the bytes.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       TrnDlyType - Target Dly type
 *     @param[in]       IfMax - If this is for maximum value or minimum
 *
 *     @return   minimum gross dly
 */
UINT8
STATIC
MemTFindMinMaxGrossDlyByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       TRN_DLY_TYPE TrnDlyType,
  IN       BOOLEAN IfMax
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *       This function compares test pattern with data in buffer and return a pass/fail bitmap
 *       for 8 Bytes for optimized receiver enable training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Buffer[]  -  Buffer data from DRAM (Measured data from DRAM) to compare
 *     @param[in]       Pattern[]  - Pattern (Expected data in ROM/CACHE) to compare against
 *     @param[in]       Side - current side being targeted
 *     @param[in]       Receiver - Current receiver value
 *     @param[in]       Side1En - Indicates if the second side of the DIMM is being used
 *     @return  PASS - Bit map of results of comparison
 */

UINT16
STATIC
MemTCompare1ClPatternOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Buffer[],
  IN       UINT8 Pattern[],
  IN       UINT8 Side,
  IN       UINT8 Receiver,
  IN       BOOLEAN  Side1En
  )
{
  return 0;
}
/*-----------------------------------------------------------------------------
 *
 *  This function initializes variables for optimized training.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemTInitializeVariablesOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function loads the DqsRcvEnDly from saved data and program to additional index
 *  for optimized DQS receiver enabled training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 *
 */

VOID
STATIC
MemTLoadRcvrEnDlyOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function programs DqsRcvEnDly to additional index for DQS receiver enabled training
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 *     @param[in]       RcvEnDly  - receiver enable delay to be saved
 */

VOID
STATIC
MemTSetRcvrEnDlyOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT16 RcvEnDly
  )
{

}
/*-----------------------------------------------------------------------------
 *
 *  This sets any Errors generated from Dly sweep
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]   DCT   - current DCT
 *     @param[in]   Receiver   - current receiver
 *
 *     @return     FALSE - Fatal error occurs.
 *     @return     TRUE  - No fatal error occurs.
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemTSetSweepErrorOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver,
  IN       UINT8 Dct,
  IN       BOOLEAN ErrorCheck
  )
{
  return TRUE;
}

/*-----------------------------------------------------------------------------
 *
 *  This function determines the maximum receiver delay value
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @retval  MaxRcvrValue - Maximum receiver delay value for all bytelanes
 * ----------------------------------------------------------------------------
 */

UINT16
MemTGetMaxValueOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return 0;
}
/*-----------------------------------------------------------------------------
 *
 *  This function determines if the sweep loop should complete.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @retval  TRUE - All bytelanes pass
 *              FALSE - Some bytelanes fail
 * ----------------------------------------------------------------------------
 */

BOOLEAN
MemTCheckRcvrEnDlyLimitOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  This function load the result of write levelization training into RcvrEnDlyOpt,
 *  using it as the initial value for Receiver DQS training.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Receiver  - Current Chip select value
 */
VOID
STATIC
MemTLoadInitialRcvEnDlyOptByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Receiver
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function finds the DIMM that has the largest receiver enable delay that are trained by PMU
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[out]      *ChipSel   - Pointer to the Chip select that has the largest receiver enable delay
 *                                   + Read DQS Delay.
 *
 *     @return   TRUE - A chip select can be found.
 *     @return   FALSE - A chip select cannot be found.
 */

BOOLEAN
MemTFindMaxRcvrEnDlyTrainedByPmuByte (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
     OUT   UINT8 *ChipSel
  )
{
  return TRUE;
}

