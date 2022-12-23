/* $NoKeywords:$ */
/**
 * @file
 *
 * mftds.c
 *
 * Northbridge table drive support file for DR
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat/TABLE)
 * @e \$Revision: 324073 $ @e \$Date: 2015-08-11 09:45:24 +0800 (Tue, 11 Aug 2015) $
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mftds.h"
#include "OptionMemory.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_NULL_FEATTABLELIBNULL_MFTDS_FILECODE

/*----------------------------------------------------------------------------
 *   Mixed (DEFINITIONS AND MACROS / TYPEDEFS, STRUCTURES, ENUMS)
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 *                         DEFINITIONS AND MACROS
 *
 *-----------------------------------------------------------------------------
 */
#define MAX_BYTELANES_PER_CHANNEL   (8 + 1)  ///< Max Bytelanes per channel

/*----------------------------------------------------------------------------
 *                         TYPEDEFS, STRUCTURES, ENUMS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           FUNCTIONS PROTOTYPE
 *
 *----------------------------------------------------------------------------
 */

VOID
SetTableValues (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_TABLE_ALIAS MTPtr
  );

BOOLEAN
SetTableValuesLoop (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_TABLE_ALIAS *MTPtr,
  IN       UINT8     time
  );

/*-----------------------------------------------------------------------------
 *
 *   This function initializes bit field translation table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_TABLE_ALIAS structure
 *     @param[in]       time     - Indicate the timing for the register which is written.
 *
 *     @return          None
 * ----------------------------------------------------------------------------
 */
VOID
MemFInitTableDrive (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8     time
  )
{

}

/*-----------------------------------------------------------------------------
 *
 *   This function initializes bit field translation table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *MTPtr   - Pointer to the MEM_TABLE_ALIAS structure
 *     @param[in]       time     - Indicate the timing for the register which is written.
 *
 *     @return          BOOLEAN  - TRUE:  Values were set
 *                                 FALSE: No values were set
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
SetTableValuesLoop (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_TABLE_ALIAS *MTPtr,
  IN       UINT8     time
  )
{
  return TRUE;
}

/*-----------------------------------------------------------------------------
 *
 *   Engine for setting Table Value.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       MTPtr    - Pointer to the MEM_TABLE_ALIAS structure
 *
 *     @return      None
 * ----------------------------------------------------------------------------
 */
VOID
SetTableValues (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_TABLE_ALIAS MTPtr
  )
{

}







