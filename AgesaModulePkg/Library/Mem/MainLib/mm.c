/* $NoKeywords:$ */
/**
 * @file
 *
 * mm.c
 *
 * Main Memory Entrypoint file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
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
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_MAINLIB_MM_FILECODE
/* features */

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
 *
 *      This function deallocates heap buffers that were allocated in AmdMemAuto
 *
 *     @param[in,out]   *MemPtr   - Pointer to the MEM_DATA_STRUCT
 *
 *     @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemAmdFinalize (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  UINT8 Die;

  for (Die = 0; Die < MemPtr->DieCount; Die++ ) {
    HeapDeallocateBuffer (GENERATE_MEM_HANDLE (ALLOC_TRN_DATA_HANDLE, Die, 0, 0), &MemPtr->StdHeader);
    HeapDeallocateBuffer (GENERATE_MEM_HANDLE (ALLOC_DCT_STRUCT_HANDLE, Die, 0, 0), &MemPtr->StdHeader);
  }

  HeapDeallocateBuffer (GENERATE_MEM_HANDLE (ALLOC_DIE_STRUCT_HANDLE, 0, 0, 0), &MemPtr->StdHeader);
  HeapDeallocateBuffer (AMD_S3_SAVE_HANDLE, &MemPtr->StdHeader);
  HeapDeallocateBuffer (AMD_MEM_SPD_HANDLE, &MemPtr->StdHeader);
  HeapDeallocateBuffer (AMD_MEM_AUTO_HANDLE, &MemPtr->StdHeader);
  HeapDeallocateBuffer (AMD_MEM_DATA_HANDLE, &MemPtr->StdHeader);

  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 * MemSocketScan - Scan all nodes, recording the physical Socket number,
 * Die Number (relative to the socket), and PCI Device address of each
 * populated socket.
 *
 * This information is used by the northbridge block to map a dram
 * channel on a particular DCT, on a particular CPU Die, in a particular
 * socket to a the DRAM SPD Data for the DIMMS physically connected to
 * that channel.
 *
 * Also, the customer socket map is populated with pointers to the
 * appropriate channel structures, so that the customer can locate the
 * appropriate channel configuration data.
 *
 * This socket scan will always result in Die 0 as the BSP.
 *
 *     @param[in,out]   *mmPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
AGESA_STATUS
MemSocketScan (
  IN OUT   MEM_MAIN_DATA_BLOCK *mmPtr
  )
{
  MEM_DATA_STRUCT *MemPtr;
  UINT8 DieIndex;
  UINT8 DieCount;
  UINT32 SocketId;
  UINT32 DieId;
  UINT8 Die;
  PCI_ADDR Address;
  AGESA_STATUS AgesaStatus;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;

  ASSERT (mmPtr != NULL);
  ASSERT (mmPtr->MemPtr != NULL);
  MemPtr = mmPtr->MemPtr;

  //
  //  Count the number of dies in the system
  //
  DieCount = 0;
  for (Die = 0; Die < MAX_NODES_SUPPORTED; Die++) {
    if (GetSocketModuleOfNode ((UINT32)Die, &SocketId, &DieId, (VOID *)MemPtr)) {
      DieCount++;
    }
  }
  MemPtr->DieCount = DieCount;
  mmPtr->DieCount = DieCount;

  if (DieCount > 0) {
    //
    //  Allocate buffer for DIE_STRUCTs
    //
    AllocHeapParams.RequestedBufferSize = ((UINT16)DieCount * sizeof (DIE_STRUCT));
    AllocHeapParams.BufferHandle = GENERATE_MEM_HANDLE (ALLOC_DIE_STRUCT_HANDLE, 0, 0, 0);
    AllocHeapParams.Persist = HEAP_LOCAL_CACHE;
    if (HeapAllocateBuffer (&AllocHeapParams, &MemPtr->StdHeader) == AGESA_SUCCESS) {
      MemPtr->DiesPerSystem = (DIE_STRUCT *)AllocHeapParams.BufferPtr;
      //
      //  Find SocketId, DieId, and PCI address of each node
      //
      DieIndex = 0;
      for (Die = 0; Die < MAX_NODES_SUPPORTED; Die++) {
        if (GetSocketModuleOfNode ((UINT32)Die, &SocketId, &DieId, (VOID *)MemPtr)) {
          if (GetPciAddress ((VOID *)MemPtr, (UINT8)SocketId, (UINT8)DieId, &Address, &AgesaStatus)) {
            MemPtr->DiesPerSystem[DieIndex].SocketId = (UINT8)SocketId;
            MemPtr->DiesPerSystem[DieIndex].DieId = (UINT8)DieId;
            MemPtr->DiesPerSystem[DieIndex].PciAddr.AddressValue = Address.AddressValue;

            DieIndex++;
          }
        }
      }
      AgesaStatus = AGESA_SUCCESS;
    } else {
      ASSERT(FALSE); // Heap allocation failed for DIE_STRUCTs
      AgesaStatus = AGESA_FATAL;
    }
  } else {
    ASSERT(FALSE); // No die in the system
    AgesaStatus = AGESA_FATAL;
  }
  return AgesaStatus;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function is default function for the fultion list
 *
 *     @param[in,out]   *pMemData   - Pointer to the MEM_DATA_STRUCT
 */
VOID
AmdMemFunctionListDef (
  IN OUT   VOID *pMemData
  )
{
}

