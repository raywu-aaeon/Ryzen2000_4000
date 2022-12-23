/* $NoKeywords:$ */
/**
 * @file
 *
 * mttwl3.c
 *
 * Technology Phy assisted write levelization for DDR3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Tech/DDR3)
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
#include "mu.h"
#include "mt.h"
#include "mp.h"
#include "mtsdi3.h"
#include "mtlrdimm3.h"
#include "merrhdl.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_TECHDDR3LIBNULL_MTTWL3_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
extern MEM_PSC_FLOW_BLOCK* memPlatSpecFlowArray[];

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
MemTWriteLevelizationHw3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  );

VOID
STATIC
MemTWLPerDimmHw3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm,
  IN       UINT8 Pass
  );

VOID
STATIC
MemTPrepareDIMMs3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 TargetDIMM,
  IN       BOOLEAN Wl
  );

VOID
STATIC
MemTProcConfig3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm,
  IN       UINT8 Pass
  );

VOID
STATIC
MemTBeginWLTrain3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */


/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function executes first pass of Phy assisted write levelization
 *      for a specific node (DDR800).
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTWriteLevelizationHw3Pass1 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function executes second pass of Phy assisted write levelization
 *      for a specific node (DDR1066 and above).
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTWriteLevelizationHw3Pass2 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function prepares for Phy assisted training.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTPreparePhyAssistedTraining (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function revert to normal settings when exiting from Phy assisted training.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTExitPhyAssistedTraining (
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
 *      This function executed hardware based write levelization for a specific die
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in] Pass - Pass number (1 (400Mhz) or 2 (>400Mhz))
 *
 *     @pre   Auto refresh and ZQCL must be disabled
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
STATIC
MemTWriteLevelizationHw3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Pass
  )
{
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function initializes per DIMM write levelization
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in] Dimm - DIMM to be trained
 *     @param[in] Pass - Pass number (1 (400Mhz) or 2 (>400Mhz))
 *
 */

VOID
STATIC
MemTWLPerDimmHw3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm,
  IN       UINT8 Pass
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function prepares the DIMMS for Write Levelization
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in] TargetDIMM - DIMM to be trained
 *     @param[in] Wl - Indicates if WL mode should be enabled
 *
 */

VOID
STATIC
MemTPrepareDIMMs3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 TargetDIMM,
  IN       BOOLEAN Wl
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function programs seed values for Write Levelization
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in] Dimm - DIMM to be trained
 *     @param[in] Pass - Pass for WL training (1 - 400Mhz or 2 - >400Mhz)
 *
 */

VOID
STATIC
MemTProcConfig3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm,
  IN       UINT8 Pass
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function begins WL training for a specific DIMM
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in] Dimm - DIMM to be trained
 *
 */

VOID
STATIC
MemTBeginWLTrain3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN       UINT8 Dimm
  )
{

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *      This function programs register after Phy assisted training is finish.
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return          TRUE -  No fatal error occurs.
 *     @return          FALSE - Fatal error occurs.
 */

BOOLEAN
MemTExitPhyAssistedTrainingClient3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

