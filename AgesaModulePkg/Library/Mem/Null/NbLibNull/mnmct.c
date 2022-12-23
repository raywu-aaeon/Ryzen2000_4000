/* $NoKeywords:$ */
/**
 * @file
 *
 * mnmct.c
 *
 * Northbridge Common MCT supporting functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
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
#include "mu.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
//#include "cpuFeatures.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_NBLIBNULL_MNMCT_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define NBCOF_MHZ(NbFid, NbDid) (100 * ((NbFid + 4) / (1 << NbDid)));
#define GROSS_DELAY_UNB   5
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
MemNSetMTRRrangeNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 Base,
  IN OUT   UINT32 *LimitPtr,
  IN       UINT32 MtrrAddr,
  IN       UINT8 MtrrType
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Get max frequency from OEM platform definition, from
 *     any user override (limiting) of max frequency, and
 *     from any Si Revision Specific information.  Return
 *     the least of these three in DIE_STRUCT.Timings.TargetSpeed.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSyncTargetSpeedNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     Program system DRAM map to this node
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSyncAddrMapToAllNodesNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function calculates the critical delay difference (CDD)
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       TrnDlyType1 - Type of first Gross Delay parameter
 *     @param[in]       TrnDlyType2 - Type of second Gross Delay parameter
 *     @param[in]       SameDimm - CDD of same DIMMs
 *     @param[in]       DiffDimm - CDD of different DIMMs
 *
 *     @return          CDD term - in 1/2 MEMCLK
 */
INT16
MemNCalcCDDNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       TRN_DLY_TYPE TrnDlyType1,
  IN       TRN_DLY_TYPE TrnDlyType2,
  IN       BOOLEAN SameDimm,
  IN       BOOLEAN DiffDimm
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets DQS timing from data saved in heap.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   TrnDlyType - type of delay to be set
 *     @param[in]   Drbn - encoding of Dimm-Rank-Byte-Nibble to be accessed
 *                  (use either DIMM_BYTE_ACCESS(dimm,byte) or CS_NBBL_ACCESS(cs,nibble) to use this encoding
 *
 *     @return      value of the target timing.
 */
UINT16
GetTrainDlyFromHeapNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       TRN_DLY_TYPE TrnDlyType,
  IN       DRBN Drbn
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets the fixed MTRRs for common legacy ranges.
 *   It sets TOP_MEM and TOM2 and some variable MTRRs with WB Uncacheable type.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - An Error value lower than AGESA_FATAL may have occurred
 *     @return          FALSE - An Error value greater than or equal to AGESA_FATAL may have occurred
 */

BOOLEAN
MemNCPUMemTypingNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function runs on the BSP only, it sets the fixed MTRRs for common legacy ranges.
 *   It sets TOP_MEM and TOM2 and some variable MTRRs with WB Uncacheable type.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNUMAMemTypingNb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *  Program MTRRs to describe given range as given cache type.  Use MTRR pairs
 *  starting with the given MTRRphys Base address, and use as many as is
 *  required up to (excluding) MSR 020C, which is reserved for OS.
 *
 *  "Limit" in the context of this procedure is not the numerically correct
 *  limit, but rather the Last address+1, for purposes of coding efficiency
 *  and readability.  Size of a region is then Limit-Base.
 *
 *  1. Size of each range must be a power of two
 *  2. Each range must be naturally aligned (Base is same as size)
 *
 *  There are two code paths: the ascending path and descending path (analogous
 *  to bsf and bsr), where the next limit is a function of the next set bit in
 *  a forward or backward sequence of bits (as a function of the Limit).  We
 *  start with the ascending path, to ensure that regions are naturally aligned,
 *  then we switch to the descending path to maximize MTRR usage efficiency.
 *  Base=0 is a special case where we start with the descending path.
 *  Correct Mask for region is 2comp(Size-1)-1,
 *  which is 2comp(Limit-Base-1)-1 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]     Base - Base address[47:16] of specified range.
 *     @param[in]     *LimitPtr - Limit address[47:16] of specified range.
 *     @param[in]     MtrrAddr - address of var MTRR pair to start using.
 *     @param[in]     MtrrType - Cache type for the range.
 *
 *     @return      TRUE - No failure occurred
 *     @return      FALSE - Failure occurred because run out of variable-size MTRRs before completion.
 */

BOOLEAN
STATIC
MemNSetMTRRrangeNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 Base,
  IN OUT   UINT32 *LimitPtr,
  IN       UINT32 MtrrAddr,
  IN       UINT8 MtrrType
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     Program one MTRR to describe Uma region as UC cache type if we detect running out of
 *     Mtrr circumstance.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]     *BasePtr - Base address[47:24] of specified range.
 *     @param[in]     *LimitPtr - Limit address[47:24] of specified range.
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */
BOOLEAN
MemNSetMTRRUmaRegionUCNb  (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 *BasePtr,
  IN OUT   UINT32 *LimitPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function readjusts TOPMEM and MTRRs after allocating storage for C6
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNC6AdjustMSRs (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function readjusts TOPMEM and MTRRs after allocating storage for C6
 *     and GNB ACP Engine as 32MB.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemNC6AndGnbAcpEngineAdjustMSRs (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Family-specific hook to override the DdrMaxRate value for families with a
 *     non-GH-compatible encoding for BFDdrMaxRate
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *DdrMaxRate - Void pointer to DdrMaxRate.  Used as INT16.
 *
 *     @return          TRUE
 *
 */
BOOLEAN
MemNGetMaxDdrRateUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *DdrMaxRate
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function performs the action after save/restore execution
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  OptParam   - Optional parameter
 *
 *     @return    TRUE
 *
 */

BOOLEAN
MemNAfterSaveRestoreUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Get NB operating frequency in Mhz of selected NB Pstate
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *NBPstate - NB Pstate
 *
 *     @return      NB operating frequency value in Mhz.
 */

UINT32
MemNGetNbClkFreqByPstateUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT32 NBPstate
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Limited the DDR target speed with in MaxDdrRate fused.
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *
 *     @return    TRUE
 *
 */

VOID
MemNAdjustDdrSpeedUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

