/* $NoKeywords:$ */
/**
 * @file
 *
 * mnidendimmcz.c
 *
 * CZ northbridge constructor for dimm identification translator.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/HY)
 * @e \$Revision$ @e \$Date$
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
#include "mm.h"
#include "mn.h"
#include "OptionMemory.h"       // need def for MEM_FEAT_BLOCK_NB
#include "mncz.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_NULL_NBCZLIBNULL_MNIDENDIMMCZ_FILECODE

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
NormalizedToBankAddrMapCZ (
  IN       UINT64  ChannelAddr,
  IN       UINT64  CSMask,
  IN       UINT8   DimmAddrMap,
  IN       UINT8   RankDef,
  IN       BOOLEAN BankSwap,
  IN       BOOLEAN DctSelBankSwap,
  IN       BOOLEAN BankSwizzleMode,
      OUT  UINT8   *Bank,
      OUT  UINT32  *Row,
      OUT  UINT16  *Col
  );

UINT64
STATIC
BankSwapAddrCZ (
  IN       BOOLEAN BankSwap,
  IN       UINT64 addr,
  IN       BOOLEAN DctSelBankSwap
  );

UINT8
STATIC
AddrToBankSwizzleCZ (
  IN       BOOLEAN swizzle,
  IN       UINT64 addr,
  IN       UINT8 bankbit,
  IN       UINT8 offset
  );

UINT64
STATIC
CSInterleavingBitSwapCZ (
  IN       UINT64 addr,
  IN       UINT64 CSMask,
  IN       UINT8 hiBit,
  IN       UINT8 lowBit
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
BOOLEAN
MemNIdentifyDimmConstructorCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  );

AGESA_STATUS
MemFTransSysAddrToCsCZ (
  IN OUT   AMD_IDENTIFY_DIMM *AmdDimmIdentify,
  IN       MEM_MAIN_DATA_BLOCK *mmPtr
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function initializes the northbridge block for dimm identification translator
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]   *MemPtr  - Pointer to the MEM_DATA_STRUCT
 *     @param[in,out]   NodeID   - ID of current node to construct
 *     @return          TRUE     - This is the correct constructor for the targeted node.
 *     @return          FALSE    - This isn't the correct constructor for the targeted node.
 */

BOOLEAN
MemNIdentifyDimmConstructorCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   MEM_DATA_STRUCT *MemPtr,
  IN       UINT8 NodeID
  )
{
  return TRUE;
}

/*-----------------------------------------------------------------------------*/
/**
*
*   This function translates the given physical system address to
*   a node, channel select, chip select, bank, row, and column address.
*
*   @param[in, out]   *AmdDimmIdentify - Pointer to the parameter structure AMD_IDENTIFY_DIMM
*   @param[in, out]   *mmPtr - Pointer to the MEM_MAIN_DATA_BLOCK
*
*   @retval           AGESA_SUCCESS - The chip select address is found
*   @retval           AGESA_BOUNDS_CHK - Targeted address is out of bound.
*
*/
AGESA_STATUS
MemFTransSysAddrToCsCZ (
  IN OUT   AMD_IDENTIFY_DIMM *AmdDimmIdentify,
  IN       MEM_MAIN_DATA_BLOCK *mmPtr
  )
{
  return AGESA_SUCCESS;
}

/*-----------------------------------------------------------------------------*/
/**
*
*   This function returns a Bank, Row, and Col as seen on the DRAM Command/Addr bus
*
*   @param[in]    ChannelAddr - Memory address within the channel
*   @param[in]    CSMask - Chip select mask
*   @param[in]    DimmAddrMap - DIMM configuration information of address mapping
*   @param[in]    RankDef - Rank definition
*   @param[in]    BankSwap - Bank swap mode
*   @param[in]    DctSelBankSwap - DCT Select Bank swap mode
*   @param[in]    BankSwizzleMode - Bank swizzle mode
*   @param[out]   Bank - Pointer to the bank number
*   @param[out]   Row - Pointer to the row number
*   @param[out]   Col - Pointer to the column number
*
*/
VOID
STATIC
NormalizedToBankAddrMapCZ (
  IN       UINT64  ChannelAddr,
  IN       UINT64  CSMask,
  IN       UINT8   DimmAddrMap,
  IN       UINT8   RankDef,
  IN       BOOLEAN BankSwap,
  IN       BOOLEAN DctSelBankSwap,
  IN       BOOLEAN BankSwizzleMode,
     OUT   UINT8   *Bank,
     OUT   UINT32  *Row,
     OUT   UINT16  *Col
  )
{

}

/*-----------------------------------------------------------------------------*/
/**
*
*   Function returns a normalized address after remapping by bank swaping. See D18F2xA8[BankSwap].
*
*   @param[in]    BankSwap - Bank swap mode
*   @param[in]    addr - memory address within channel
*   @param[in]    DctSelBankSwap - DCT select bank swap mode
*
*   @retval       Normalized address after remapping by bank swaping.
*
*/
UINT64
STATIC
BankSwapAddrCZ (
  IN       BOOLEAN BankSwap,
  IN       UINT64 addr,
  IN       BOOLEAN DctSelBankSwap
  )
{
  return 0;
}

/*-----------------------------------------------------------------------------*/
/**
*
*   Function returns a DRAM device bank address after adjusting for possible
*   remapping by bank swizzling. See D18F2x94[BankSwizzleMode].
*
*   @param[in]    swizzle - Bank swizzle mode
*   @param[in]    addr - memory address within channel
*   @param[in]    bankbit - Bank bit to be swapped
*   @param[in]    offset - Offset to the bank bit to be swapped
*
*   @retval       DRAM device bank address after adjusting for possible remapping by bank swizzling
*
*/
UINT8
STATIC
AddrToBankSwizzleCZ (
  IN       BOOLEAN swizzle,
  IN       UINT64 addr,
  IN       UINT8 bankbit,
  IN       UINT8 offset
  )
{

}

/*-----------------------------------------------------------------------------*/
/**
*
*   Function returns a normalized address after adjusting for possible bit swapping
*   by CS Interleaving.
*
*   @param[in]    addr - memory address within channel
*   @param[in]    CSMask - Chip select mask
*   @param[in]    hiBit - LSB at the start of the range of bits that take part in the swap
*   @param[in]    lowBit - LSB at the start of the range of bits that take part in the swap
*
*   @retval      Normalized address after adjusting for possible bit swapping by CS Interleaving
*
*/
UINT64
STATIC
CSInterleavingBitSwapCZ (
  IN       UINT64 addr,
  IN       UINT64 CSMask,
  IN       UINT8 hiBit,
  IN       UINT8 lowBit
  )
{
  return 0;
}

