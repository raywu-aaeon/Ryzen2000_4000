/* $NoKeywords:$ */
/**
 * @file
 *
 * ma.c
 *
 * Initializes ARDK Block
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ardk)
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
#include "ma.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_ARDKLIB_MA_FILECODE

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

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *    This is the default return function of the ARDK block. The function always
 *    returns   AGESA_UNSUPPORTED
 *
 *     @param[in,out]   *MemData           Pointer to MEM_DATA_STRUCTURE
 *     @param[in]       SocketID        Socket number
 *     @param[in]       *CurrentChannel       Pointer to CH_DEF_STRUCT
 *
 *     @return          AGESA_UNSUPPORTED  AGESA status indicating that default is unsupported
 *
 */

AGESA_STATUS
MemAGetPsCfgDef (
  IN OUT   MEM_DATA_STRUCT *MemData,
  IN       UINT8 SocketID,
  IN OUT   CH_DEF_STRUCT *CurrentChannel
  )
{
  return AGESA_UNSUPPORTED;
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
MemAGetPsRankType (
  IN       CH_DEF_STRUCT *CurrentChannel
  )
{
  UINT8 i;
  UINT16 DIMMRankType;

  DIMMRankType = 0;
  for (i = 0; i < MAX_DIMMS_PER_CHANNEL; i++) {
    if (CurrentChannel->MCTPtr->Status[SbLrdimms]) {
      if ((CurrentChannel->LrDimmPresent & (UINT8) 1 << i) != 0) {
        DIMMRankType |= (UINT16) 1 << (i << 2);
      }
    } else {
      if ((CurrentChannel->DimmQrPresent & (UINT8) 1 << i) != 0) {
        if (i < 2) {
          DIMMRankType |= (UINT16) 4 << (i << 2);
        }
      } else if ((CurrentChannel->DimmDrPresent & (UINT8) 1 << i) != 0) {
        DIMMRankType |= (UINT16) 2 << (i << 2);
      } else if ((CurrentChannel->DimmSRPresent & (UINT8) 1 << i) != 0) {
        DIMMRankType |= (UINT16) 1 << (i << 2);
      }
    }
  }
  return DIMMRankType;
}

