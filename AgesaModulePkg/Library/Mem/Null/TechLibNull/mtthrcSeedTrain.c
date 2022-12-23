/* $NoKeywords:$ */
/**
 * @file
 *
 * mtthrcSt.c
 *
 * Phy assisted DQS receiver enable seedless training
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
#include "mt.h"
#include "mttEdgeDetect.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NULL_TECHLIBNULL_MTTHRCSEEDTRAIN_FILECODE
/*----------------------------------------------------------------------------
3 *                          DEFINITIONS AND MACROS
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
MemTRdPosRxEnSeedSetDly3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT16 RcvEnDly,
  IN OUT   UINT8 ByteLane
  );

VOID
STATIC
MemTRdPosRxEnSeedCheckRxEndly3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*-----------------------------------------------------------------------------
 *
 *
 *     This function checks each bytelane for no window error.
 *
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   OptParam   - Optional parameter
 *
 *     @return    TRUE
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemTTrackRxEnSeedlessRdWrNoWindBLError (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}
/*-----------------------------------------------------------------------------
 *
 *
 *      This function checks each bytelane for small window error.
 *
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   OptParam   - Optional parameter(Unused)
 *
 *     @return    TRUE
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemTTrackRxEnSeedlessRdWrSmallWindBLError (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function sets the RxEn delay
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *     @param[in,out]   *RcvEnDly   - Receiver Enable Delay
 *     @param[in,out]   *ByteLane   - Bytelane
 *
*/
VOID
STATIC
MemTRdPosRxEnSeedSetDly3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr,
  IN OUT   UINT16 RcvEnDly,
  IN OUT   UINT8 ByteLane
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function determines if the currert RxEn delay settings have failed
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
*/
VOID
STATIC
MemTRdPosRxEnSeedCheckRxEndly3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{

}
/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function executes RdDQS training and if fails adjusts the RxEn Gross results for
 *     each bytelane
 *
 *     @param[in,out]   *TechPtr   - Pointer to the MEM_TECH_BLOCK
 *
 *     @return  TRUE - All bytelanes pass
 *     @return  FALSE - Some bytelanes fail
*/
BOOLEAN
MemTRdPosWithRxEnDlySeeds3 (
  IN OUT   MEM_TECH_BLOCK *TechPtr
  )
{
  return TRUE;
}

