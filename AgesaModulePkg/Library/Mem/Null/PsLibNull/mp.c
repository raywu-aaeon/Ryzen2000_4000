/* $NoKeywords:$ */
/**
 * @file
 *
 * mp.c
 *
 * Common platform specific configuration.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps)
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
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "mu.h"
#include "ma.h"
#include "mp.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_NULL_PSLIBNULL_MP_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define PSO_TYPE    0
#define PSO_LENGTH  1
#define PSO_DATA    2

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
MemPPSCGen (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );

BOOLEAN
STATIC
MemPCheckTblDrvOverrideConfig (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

BOOLEAN
STATIC
MemPCheckTblDrvOverrideConfigSpeedLimit (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

VOID
STATIC
MemPTblDrvOverrideSpeedLimit (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

UINT8
STATIC
MemPTblDrvOverrideODT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

VOID
STATIC
MemPTblDrvOverrideODTPattern (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

UINT8
STATIC
MemPTblDrvOverrideRC2IBT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer,
  IN       UINT8 NumOfReg
  );

BOOLEAN
STATIC
MemPTblDrvOverrideMR0WR (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

BOOLEAN
STATIC
MemPTblDrvOverrideMR0CL (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  );

BOOLEAN
STATIC
MemPTblDrvOverrideMR10OpSpeed (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
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
 *    This is the default return function of the Platform Specific block. The function always
 *    returns   AGESA_UNSUPPORTED
 *
 *     @param[in,out]   *MemPtr           Pointer to MEM_DATA_STRUCTURE
 *     @param[in]       *ChannelPtr       Pointer to CH_DEF_STRUCT
 *     @param[in]       *PsPtr            Pointer to MEM_PS_BLOCK
 *
 *     @return          AGESA_UNSUPPORTED  AGESA status indicating that default is unsupported
 *
 */

AGESA_STATUS
MemPConstructPsUDef (
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN OUT   CH_DEF_STRUCT *ChannelPtr,
  IN OUT   MEM_PS_BLOCK *PsPtr
  )
{
  return AGESA_UNSUPPORTED;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function will set the DramTerm and DramTermDyn in the structure of a channel.
 *
 *     @param[in,out]   *NBPtr           Pointer to MEM_NB_BLOCK
 *     @param[in]       ArraySize        Size of the array of DramTerm
 *     @param[in]       *DramTermPtr     Address the array of DramTerm
 *
 *     @return          TRUE - Find DramTerm and DramTermDyn for corresponding platform and dimm population.
 *     @return          FALSE - Fail to find DramTerm and DramTermDyn for corresponding platform and dimm population.
 *
 */
BOOLEAN
MemPGetDramTerm (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 ArraySize,
  IN       CONST DRAM_TERM_ENTRY *DramTermPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function gets the highest POR supported speed.
 *
 *     @param[in,out]   *NBPtr           Pointer to MEM_NB_BLOCK
 *     @param[in]       FreqLimitSize    Size of the array of Frequency Limit
 *     @param[in]       *FreqLimitPtr     Address the array of Frequency Limit
 *
 *     @return          UINT8 - frequency limit
 *
 */
UINT16
MemPGetPorFreqLimit (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 FreqLimitSize,
  IN       CONST POR_SPEED_LIMIT *FreqLimitPtr
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function is the default function for getting POR speed limit. When a
 *    package does not need to cap the speed, it should use this function to initialize
 *    the corresponding function pointer.
 *
 *     @param[in,out]   *NBPtr           Pointer to MEM_NB_BLOCK
 *
 */
VOID
MemPGetPORFreqLimitDef (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function gets the seed value of WL and HW RxEn pass 1 training.
 *
 *     @param[in,out]   *NBPtr           Pointer to MEM_NB_BLOCK
 *
 *     @return          TRUE - Entries are found
 *     @return          FALSE - Entries are not found
 *
 */
BOOLEAN
MemPGetPSCPass1Seed (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function gets platform specific configuration such as Max Freq., Slow Mode, Dram Term,
 *    and so on.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return          TRUE - Successfully execute platform specific configuration flow.
 *     @return          FALSE - Fail to execute platform specific configuration flow.
 *
 */
BOOLEAN
MemPPSCFlow (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function constructs the rank type map of Dimm0, Dimm1, Dimm2. Also it counts the number
 *     of dimm in the table.
 *
 *     @param[in]       Dimm0       Rank type of Dimm0
 *     @param[in]       Dimm1       Rank type of Dimm1
 *     @param[in]       Dimm2       Rank type of Dimm2
 *     @param[in, out]       *RankTypeInTable       Pointer to RankTypeInTable variable
 *
 *
 */
VOID
MemPConstructRankTypeMap (
  IN       UINT16 Dimm0,
  IN       UINT16 Dimm1,
  IN       UINT16 Dimm2,
  IN OUT   UINT16 *RankTypeInTable
  )
{

}

/*-----------------------------------------------------------------------------*/
/**
 *     MemPIsIdSupported
 *      This function matches the SOC_LOGICAL_ID and PackageType with certain criteria to
 *      determine if it is supported by this NB type.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       LogicalId - SOC_LOGICAL_ID
 *     @param[in]       PackageType - Package Type
 *
 *     @return          TRUE -  NB type is matched !
 *     @return          FALSE - NB type is not matched !
 *
 */
BOOLEAN
MemPIsIdSupported (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       SOC_LOGICAL_ID LogicalId,
  IN       UINT8 PackageType
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function returns the rank type map of a channel.
 *
 *     @param[in]       *CurrentChannel       Pointer to CH_DEF_STRUCT
 *
 *     @return          UINT16 - The map of rank type.
 *
 */
UINT16
MemPGetPsRankType (
  IN       CH_DEF_STRUCT *CurrentChannel
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function performs the action for the rest of platform specific configuration such as
 *    tri-state stuff
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables       Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          TRUE - No error occurred.
 *     @return          FALSE - Error occurred.
 *
 */
BOOLEAN
STATIC
MemPPSCGen (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{
  return TRUE;
}


 /* -----------------------------------------------------------------------------*/
/**
 *
 *    This function proceeds Table Driven Overriding.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in] PlatformMemoryConfiguration - Pointer to Platform config table
 *     @param[in] ProceededPSOType - Proceeded PSO type
 *
 *     @return          bit0 ~ bit7 - Overriding CS or DIMM map.
 *     @return          bit15         - Invalid entry found if set.
 *
 */
UINT16
MemPProceedTblDrvOverride (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       PSO_TABLE *PlatformMemoryConfiguration,
  IN       UINT8 ProceededPSOType
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides the speed limit.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 */
VOID
STATIC
MemPTblDrvOverrideSpeedLimit (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides the ODTs (RttNom and RttWr).
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 *     @return          Target CS overriding bit map
 *
 */
UINT8
STATIC
MemPTblDrvOverrideODT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides the ODT patterns.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 */
VOID
STATIC
MemPTblDrvOverrideODTPattern (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides the Ctrl Word 2 and 8.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *     @param[in]       NumOfReg  - Number of registers
 *
 *     @return          Target DIMM overridng bit map
 *
 */
UINT8
STATIC
MemPTblDrvOverrideRC2IBT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer,
  IN       UINT8 NumOfReg
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides MR0[WR].
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 *     @return          TRUE : Overridden
 *     @return          FALSE : Not overriden
 *
 */
BOOLEAN
STATIC
MemPTblDrvOverrideMR0WR (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides MR0[WR].
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 *     @return          TRUE : Overridden
 *     @return          FALSE : Not overriden
 *
 */
BOOLEAN
STATIC
MemPTblDrvOverrideMR0CL (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function overrides MR10[OperatingSpeed].
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 *     @return          TRUE : Overridden
 *     @return          FALSE : Not overriden
 *
 */
BOOLEAN
STATIC
MemPTblDrvOverrideMR10OpSpeed (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function checks if platform configuration is matched or not.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 *     @return          TRUE : Configuration is matched
 *     @return          FALSE : Configuration is not matched
 *
 */
BOOLEAN
STATIC
MemPCheckTblDrvOverrideConfig (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
  return FALSE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *    This function checks if platform configuration is matched or not.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Buffer  - Pointer to Platform config table
 *
 *     @return          TRUE : Configuration is matched
 *     @return          FALSE : Configuration is not matched
 *
 */
BOOLEAN
STATIC
MemPCheckTblDrvOverrideConfigSpeedLimit (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 *Buffer
  )
{
  return FALSE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Prepare PS table look-up conditions (ie. DIMM type, rank type,...)
 *
 *     @param[in,out]   *NBPtr        - Pointer to the MEM_NB_BLOCK
 *
 */
VOID
MemPPreparePsTabLookupConditions (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Select and return the pointer to the table that supports currently populated
 *     processor, DIMMs, and platform
 *
 *     @param[in,out]   *NBPtr        - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *ListOfTables - Pointer to PSC_TBL_ENTRY array of pointers
 *     @param[in]       *TableSize    - Size of the selected table
 *
 *     @return          Pointer to the selected PSC_TBL_ENTRY table
 *
 */
PSC_TBL_ENTRY *
MemPGetTableEntry (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       PSC_TBL_ENTRY *ListOfTables[],
     OUT   UINT8 *TableSize
  )
{
  return NULL;
}

