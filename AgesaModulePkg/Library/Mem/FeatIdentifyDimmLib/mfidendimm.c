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
#include "Library/AmdMemBaseV5Lib.h"
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

#define FILECODE LIBRARY_MEM_FEATIDENTIFYDIMMLIB_MFIDENDIMM_FILECODE

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
  UINT8 i;
  AGESA_STATUS RetVal;
  MEM_MAIN_DATA_BLOCK mmData;             // Main Data block
  MEM_NB_BLOCK *NBPtr;
  MEM_DATA_STRUCT MemData;
  LOCATE_HEAP_PTR LocHeap;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  UINT8 Node;
  UINT8 Dct;
  UINT8 Die;
  UINT8 DieCount;
  MEM_OPTION_INSTALL_STRUCT *OptionMemoryInstallPtr;

  LibAmdMemCopy (&(MemData.StdHeader), &(AmdDimmIdentify->StdHeader), sizeof (AMD_CONFIG_PARAMS), &(AmdDimmIdentify->StdHeader));
  mmData.MemPtr = &MemData;
  RetVal = MemSocketScan (&mmData);
  if (RetVal == AGESA_FATAL) {
    return RetVal;
  }
  DieCount = mmData.DieCount;
  ///@todo
  //
  OptionMemoryInstallPtr = (MEM_OPTION_INSTALL_STRUCT *) (MemData.OptionMemoryInstallPtr);

  // Search for AMD_MEM_AUTO_HANDLE on the heap first.
  // Only apply for space on the heap if cannot find AMD_MEM_AUTO_HANDLE on the heap.
  LocHeap.BufferHandle = AMD_MEM_AUTO_HANDLE;
  if (HeapLocateBuffer (&LocHeap, &AmdDimmIdentify->StdHeader) == AGESA_SUCCESS) {
    // NB block has already been constructed by main block.
    // No need to construct it here.
    NBPtr = (MEM_NB_BLOCK *)LocHeap.BufferPtr;
    mmData.NBPtr = NBPtr;
  } else {
    AllocHeapParams.RequestedBufferSize = (DieCount * (sizeof (MEM_NB_BLOCK)));
    AllocHeapParams.BufferHandle = AMD_MEM_AUTO_HANDLE;
    AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
    if (HeapAllocateBuffer (&AllocHeapParams, &AmdDimmIdentify->StdHeader) != AGESA_SUCCESS) {
      PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_IDENTIFY_DIMM_MEM_NB_BLOCK, 0, 0, 0, 0, &AmdDimmIdentify->StdHeader);
      ASSERT(FALSE); // Could not allocate heap space for NB block for Identify DIMM
      return AGESA_FATAL;
    }
    NBPtr = (MEM_NB_BLOCK *)AllocHeapParams.BufferPtr;
    mmData.NBPtr = NBPtr;
    // Construct each die.
    for (Die = 0; Die < DieCount; Die ++) {
      i = 0;
      while (OptionMemoryInstallPtr->memNBInstalled.MemIdentifyDimmConstruct != 0) {
        if (OptionMemoryInstallPtr->memNBInstalled.MemIdentifyDimmConstruct (&NBPtr[Die], &MemData, Die)) {
          break;
        }
        i++;
      };
      if (OptionMemoryInstallPtr->memNBInstalled.MemIdentifyDimmConstruct == 0) {
        PutEventLog (AGESA_FATAL, MEM_ERROR_NO_CONSTRUCTOR_FOR_IDENTIFY_DIMM, Die, 0, 0, 0, &AmdDimmIdentify->StdHeader);
        ASSERT(FALSE); // No Identify DIMM constructor found
        return AGESA_FATAL;
      }
    }
  }

  i = 0;
  while (OptionMemoryInstallPtr->memNBInstalled.MemIdentifyDimmConstruct != 0) {
    if ((RetVal = OptionMemoryInstallPtr->memNBInstalled.MemTransSysAddrToCs (AmdDimmIdentify, &mmData)) == AGESA_SUCCESS) {
      // Translate Node, DCT and Chip select number to Socket, Channel and Dimm number.
      Node = AmdDimmIdentify->SocketId;
      Dct = AmdDimmIdentify->MemChannelId;
      AmdDimmIdentify->SocketId = MemData.DiesPerSystem[Node].SocketId;
      AmdDimmIdentify->MemChannelId = NBPtr[Node].GetSocketRelativeChannel (&NBPtr[Node], Dct, 0);
      AmdDimmIdentify->DimmId = AmdDimmIdentify->ChipSelect / 2;
      AmdDimmIdentify->ChipSelect %= 2;
      break;
    }
    i++;
  };

  return RetVal;
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
  MEM_NB_BLOCK *LocalNBPtr;
  UINT8 Die;

  // Find NBBlock that associates with node NodeID
  for (Die = 0; (Die < MAX_NODES_SUPPORTED) && (NBPtr[Die].Node != NodeID); Die ++);
  ASSERT (Die < MAX_NODES_SUPPORTED);

  // Get the northbridge pointer for the targeted node.
  LocalNBPtr = &NBPtr[Die];
  LocalNBPtr->FamilySpecificHook[DCTSelectSwitch] (LocalNBPtr, &DctNum);
  LocalNBPtr->Dct = DctNum;
  // The caller of this function will take care of the ganged/unganged situation.
  // So Ganged is set to be false here, and do PCI read on the DCT specified by DctNum.
  return LocalNBPtr->GetBitField (LocalNBPtr, BitFieldName);
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
  UINT8 parity;
  UINT8 index;
  parity = 0;
  for (index = 0; index < 32; ++ index) {
    parity = (UINT8) (parity ^ (address & 0x1));
    address = address >> 1;
  }
  return parity;
}

