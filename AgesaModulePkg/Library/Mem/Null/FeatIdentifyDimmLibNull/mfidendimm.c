/* $NoKeywords:$ */
/**
 * @file
 *
 * mfidendimm.c
 *
 * Translate physical system address to dimm identification.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Feat)
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
#include "cpuRegisters.h"
#include "OptionMemory.h"
#include "Library/AmdHeapLib.h"
#include "Library/AmdMemFeatIdentifyDimmLib.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_NULL_FEATIDENTIFYDIMMLIBNULL_MFIDENDIMM_FILECODE

extern MEM_NB_SUPPORT memNBInstalled[];

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define MAX_DCTS_PER_DIE        2   ///< Max DCTs per die
#define MAX_CHLS_PER_DCT        1   ///< Max Channels per DCT

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
/*-----------------------------------------------------------------------------*/
/**
*
*   This function identifies the dimm on which the given memory address locates.
*
*   @param[in, out]   *AmdDimmIdentify - Pointer to the parameter structure AMD_IDENTIFY_DIMM
*
*   @retval           AGESA_SUCCESS - Successfully translate physical system address
*                                     to dimm identification.
*                     AGESA_BOUNDS_CHK - Targeted address is out of bound.
*
*/

AGESA_STATUS
AmdIdentifyDimm (
  IN OUT   AMD_IDENTIFY_DIMM *AmdDimmIdentify
  )
{
  return AGESA_SUCCESS;
}


/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------*/
/**
*
*   This function is the interface to call the PCI register access function
*   defined in NB block.
*
*   @param[in]   *NBPtr - Pointer to the parameter structure MEM_NB_BLOCK
*   @param[in]   NodeID - Node ID number of the target Northbridge
*   @param[in]   DctNum - DCT number if applicable, otherwise, put 0
*   @param[in]   BitFieldName - targeted bitfield
*
*   @retval      UINT32 - 32 bits PCI register value
*
*/
UINT32
MemFGetPCI (
  IN   MEM_NB_BLOCK *NBPtr,
  IN   UINT8 NodeID,
  IN   UINT8 DctNum,
  IN   BIT_FIELD_NAME BitFieldName
  )
{
  return 0;
}

/*-----------------------------------------------------------------------------*/
/**
*
*   This function returns an even parity bit (making the total # of 1's even)
*   {0, 1} = number of set bits in argument is {even, odd}.
*
*   @param[in]   address - the address on which the parity bit will be calculated
*
*   @retval      UINT8 - parity bit
*
*/

UINT8
MemFUnaryXOR (
  IN   UINT32 address
  )
{
  return 0;
}

