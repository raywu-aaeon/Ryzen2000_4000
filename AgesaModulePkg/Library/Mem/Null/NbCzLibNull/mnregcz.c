/* $NoKeywords:$ */
/**
 * @file
 *
 * mnregcz.c
 *
 * Common Northbridge register related functions for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 325208 $ @e \$Date: 2015-08-26 10:05:40 +0800 (Wed, 26 Aug 2015) $
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
//#include "AdvancedApi.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mncz.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mport.h"
#include "merrhdl.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNREGCZ_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define BC_FIELDS   4

#define PMU_SMB_MEM_PS0_START   0x23
#define PMU_SMB_MEM_PS1_START   0x37

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

// Pad name, Pad instance, Chiplet number, Group number, Pad number
STATIC CONST DDR_CHIP_TO_PAD_ENTRY ROMDATA ChipToPadTableCZ[] = {
  {MEMCKE0, 2, 0, 0, 3},
  {MEMCKE0, 3, 0, 0, 2},
  {MEMCKE0, 0, 0, 0, 1},
  {MEMCKE0, 1, 0, 0, 0},
  {MEMADD0, 14, 0, 2, 11},
  {MEMADD0, 15, 0, 2, 10},
  {MEMADD0, 12, 0, 2, 9},
  {MEMBANK0, 2, 0, 2, 8},
  {MEMADD0, 8, 0, 2, 7},
  {MEMADD0, 7, 0, 2, 6},
  {MEMADD0, 11, 0, 2, 5},
  {MEMADD0, 9, 0, 2, 4},
  {MEMCLK0_L, 2, 1, 0, 3},
  {MEMCLK0_H, 2, 1, 0, 2},
  {MEMCLK0_L, 0, 1, 0, 1},
  {MEMCLK0_H, 0, 1, 0, 0},
  {MEMADD0, 5, 1, 1, 9},
  {MEMADD0, 6, 1, 1, 8},
  {MEMADD0, 2, 1, 1, 7},
  {MEMADD0, 1, 1, 1, 6},
  {MEMADD0, 3, 1, 1, 5},
  {MEMADD0, 4, 1, 1, 4},
  {MEMCLK0_L, 3, 2, 0, 3},
  {MEMCLK0_H, 3, 2, 0, 2},
  {MEMCLK0_L, 1, 2, 0, 1},
  {MEMCLK0_H, 1, 2, 0, 0},
  {MEMADD0, 10, 2, 1, 7},
  {MEMBANK0, 0, 2, 1, 6},
  {MEMADD0, 0, 2, 1, 5},
  {MEMBANK0, 1, 2, 1, 4},
  {MEMCS0_L, 6, 2, 2, 11},
  {MEMCS0_L, 4, 2, 2, 10},
  {MEMCS0_L, 2, 2, 2, 9},
  {MEMCS0_L, 0, 2, 2, 8},
  {MEMADD0, 13, 3, 0, 3},
  {MEMCAS0_L, 0, 3, 0, 2},
  {MEMWE0_L, 0, 3, 0, 1},
  {MEMRAS0_L, 0, 3, 0, 0},
  {MEMODT0, 3, 3, 1, 7},
  {MEMODT0, 1, 3, 1, 6},
  {MEMODT0, 0, 3, 1, 5},
  {MEMODT0, 2, 3, 1, 4},
  {MEMCS0_L, 7, 3, 2, 11},
  {MEMCS0_L, 5, 3, 2, 10},
  {MEMCS0_L, 3, 3, 2, 9},
  {MEMCS0_L, 1, 3, 2, 8},
  {MEMDQ, 7, 0, 1, 7},
  {MEMDQ, 6, 0, 1, 6},
  {MEMDQ, 5, 0, 1, 5},
  {MEMDQ, 4, 0, 1, 4},
  {MEMDQ, 3, 0, 0, 3},
  {MEMDQ, 2, 0, 0, 2},
  {MEMDQ, 1, 0, 0, 1},
  {MEMDQ, 0, 0, 0, 0},
  {MEMDQS, 0, 0, 2, 10},
  {MEMDQS, 0, 0, 2, 8},
  {MEMDQS, 0, 0, 2, 11},
  {MEMDQS, 0, 0, 3, 9},
  {MEMDQ_L, 0, 0, 0, 0},
  {MEMDQ_H, 0, 0, 1, 4},
  {MEMDQS_L, 0, 0, 2, 11},
  {MEMDQS_H, 0, 0, 2, 8},
  {MEMADD_A14, 14, 0, 2, 11},
  {MEMADD_A15, 15, 0, 2, 10},
  {MEMADD_A13, 13, 3, 0, 3},
  {MEMADD_UNUSED, 0, 1, 1, 11},
  {MEMADD_UNUSED, 0, 1, 1, 10}
};

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*-----------------------------------------------------------------------------*/
/**
 *      This function matches the SOC_LOGICAL_ID with certain criteria to
 *      determine if it is supported by this NBBlock.
 *
 *     @param[in]       *LogicalIdPtr - Pointer to the SOC_LOGICAL_ID
 *
 *     @return          TRUE -  This node is a CZ.
 *     @return          FALSE - This node is not a CZ.
 *
 */
BOOLEAN
MemNIsIdSupportedCZ (
  IN       SOC_LOGICAL_ID *LogicalIdPtr
  )
{
  return TRUE;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------*/

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function gets or sets a value to a bit field in a PCI register.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field to be programmed
 *     @param[in]   InputValue - Value to be programmed
 *     @param[in]   IsSet - Indicates if the function will set or get
 *
 *     @return      value read, if the function is used as a "get"
 */

UINT32
MemNCmnGetSetFieldCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 IsSet,
  IN       UINTN FieldName,
  IN       UINT32 InputValue
  )
{
  return 0;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function is used by families that use a separate DctCfgSel bit to
 *     select the current DCT which will be accessed by function 2.
 *     NOTE:  This function must be called BEFORE the NBPtr->Dct variable is
 *     updated.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Dct     - Pointer to ID of the target DCT
 *
 */

BOOLEAN
MemNDctCfgSelectCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function sets the current DCT to work on.
 *   Should be called before accessing a certain DCT
 *   All data structures will be updated to point to the current DCT
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   Dct - ID of the target DCT
 *
 */

VOID
MemNSwitchDctCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes bit field translation table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   NBRegTable[]  - Pointer to the bit field data structure
 *
 */

VOID
MemNInitNBRegTableCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   TSEFO NBRegTable[]
  )
{

}


