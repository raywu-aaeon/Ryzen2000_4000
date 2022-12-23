/* $NoKeywords:$ */
/**
 * @file
 *
 * mndctcz.c
 *
 * Northbridge DCT support for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 325428 $ @e \$Date: 2015-08-27 20:08:24 +0800 (Thu, 27 Aug 2015) $
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
#include "mport.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mu.h"
#include "mp.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "mncz.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mftds.h"
#include "merrhdl.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNDCTCZ_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define UNUSED_CLK 4
#define MAX_RD_DQS_DLY 0x1F

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */
typedef struct {
  UINT32 BitField; ///< Bit field name of the timing
  UINT8 Min;               ///< Minimum value for timing
  UINT8 Max;               ///< Maximum value for timing
} SPD_TMG;

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

extern MEM_PSC_FLOW MemPGetODTPattern;

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function disables the DCT and mem clock for CZ
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNDisableDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function programs dram power management timing related registers
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 *     @return    none
 * ----------------------------------------------------------------------------
 */
VOID
MemNDramPowerMngTimingCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function programs evaluate the conditions to program CsMux
 *
 *
 *     @param[in]   DimmAddrMap   - DimmAddrMap
 *     @param[in]   RankDef       - RankDef
 *
 *     @return          TRUE - CsMux should be set
 *     @return          FALSE - CsMux should be reset
 */

BOOLEAN
STATIC
EvaluateCsMuxCZ (
  IN       UINT8   DimmAddrMap,
  IN       UINT8   RankDef
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function programs the memory controller with configuration parameters
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - An Error value lower than AGESA_FATAL may have occurred
 *     @return          FALSE - An Error value greater than or equal to AGESA_FATAL may have occurred
 *     @return          NBPtr->MCTPtr->ErrCode - Contains detailed AGESA_STATUS value
 */

BOOLEAN
MemNAutoConfigCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function looks up platform specific config/timing values from the interface layer and
 *   programs them into DCT.
 *
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE  - No errors
 *     @return          FALSE - Found errors on a channel and disable it
 */

BOOLEAN
MemNPlatformSpecCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function retrieves the Max latency parameters
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @param[in]  *MinDlyPtr - Pointer to variable to store the Minimum Delay value
 *     @param[in]  *MaxDlyPtr - Pointer to variable to store the Maximum Delay value
 *     @param[in]  *DlyBiasPtr - Pointer to variable to store Delay Bias value
 *     @param[in]  MaxRcvEnDly - Maximum receiver enable delay value
 */

VOID
MemNGetMaxLatParamsCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT16 MaxRcvEnDly,
  IN OUT   UINT16 *MinDlyPtr,
  IN OUT   UINT16 *MaxDlyPtr,
  IN OUT   UINT16 *DlyBiasPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     The function resets Rcv Fifo
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in]       Dummy - Dummy parameter
 *
 */

VOID
MemNResetRcvFifoCZ (
  IN OUT   struct _MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dummy
  )
{
  // Carrizo does not need to reset Rcv FIFO.
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function modifies CS interleaving low address according to several conditions for CZ.
 *
 *     @param[in,out]  *NBPtr    - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  *LowBit   - Pointer to low bit
 *
 */

BOOLEAN
MemNCSIntLvLowAddrAdjCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *LowBit
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function caps speed based on battery life check.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 */
VOID
MemNCapSpeedBatteryLifeCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Configure disable DLL shutdown in self-refresh mode.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNConfigureDisDllShutdownSrCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function finds the DIMM that has the largest receiver enable delay
 *     that are trained by PMU
 *
 *     @param[in,out]   *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[out]      *ChipSel   - Pointer to the Chip select that has the
 *                                   largest Round Trip Command Delay.
 *
 *     @return   TRUE  - A chip select can be found.
 *               FALSE - A chip select cannot be found.
 */

BOOLEAN
MemNCalculateRoundTripCommandDelayCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
     OUT   UINT8 *ChipSel
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function trains Max latency for all dies
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTTrainMaxLatencyCZ (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Get the MaxDdrRate
 *
 *     @param[in,out]   *NBPtr      - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *OptParam   - Pointer to DdrMaxRate
 *
 */

BOOLEAN
MemNGetDdrMaxRateCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *OptParam
  )
{
  return TRUE;
}

