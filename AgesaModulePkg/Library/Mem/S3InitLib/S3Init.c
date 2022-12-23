/* $NoKeywords:$ */
/**
 * @file
 *
 *
 * S3 Initialization routines
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Common
 * @e \$Revision: 331559 $   @e \$Date: 2015-11-23 14:44:23 +0800 (Mon, 23 Nov 2015) $
 *
 */
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
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/FabricPstatesLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_S3INITLIB_S3INIT_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
/// Heap Node Header
typedef struct _BUFFER_NODE {
  UINT32        BufferHandle;                     ///< An unique ID of buffer.
  UINT32        BufferSize;                       ///< Size of buffer.
  UINT8         Persist;                          ///< A flag. If marked, to be stored and passed to AmdInitLate.
} BUFFER_NODE;
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
CONST UINT32 ROMDATA S3LateHeapTable[] =
{
  EVENT_LOG_BUFFER_HANDLE,
  SOCKET_DIE_MAP_HANDLE,
  NODE_ID_MAP_HANDLE,
  IDS_CONTROL_HANDLE,
  AMD_S3_SCRIPT_SAVE_TABLE_HANDLE,
  AMD_PCIE_COMPLEX_DATA_HANDLE
};

#define S3LATE_TABLE_SIZE (sizeof (S3LateHeapTable) / sizeof (UINT32))


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

AGESA_STATUS
S3InitConstructor (
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN OUT   S3_DATA_BLOCK     *S3DataBlock
  );

AGESA_STATUS
S3InitDestructor (
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN OUT   S3_DATA_BLOCK     *S3DataBlock
  );


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This routine is responsible for saving silicon component registers to the
 * SMM save area in preparation of entering system suspend-to-RAM mode.
 *
 * @param[in,out] AmdRtbParams      Required input parameters for the S3Init routine.
 *
 * @return        Aggregated status across all internal AMD S3 save calls invoked.
 *
 */
AGESA_STATUS
S3Init (
  IN OUT   AMD_RTB_PARAMS *AmdRtbParams
  )
{
  UINTN  i;
  UINT32 EarlyBufferSize;
  UINT32 LateBufferSize;
  UINT32 LateContextSize;
  UINT32 HeapSize;
  UINT8  *BufferPointer;
  UINT8  *HeapBuffer;
  LOCATE_HEAP_PTR LocateHeap;
  BUFFER_NODE *HeapNode;
  ALLOCATE_HEAP_PARAMS AllocParams;
  DEVICE_BLOCK_HEADER *MemoryRelatedDeviceList;
  DEVICE_BLOCK_HEADER *NonMemoryRelatedDeviceList;
  AGESA_STATUS ReturnStatus;
  VOID   *HeapPtrs[S3LATE_TABLE_SIZE];
  UINT32 HeapSizes[S3LATE_TABLE_SIZE];
  UINT32 HeapBuffersPresent;
  VOID *MemDataPointer;

  AGESA_TESTPOINT (TpProcS3Init, &AmdRtbParams->StdHeader);

  ASSERT (AmdRtbParams != NULL);

  ReturnStatus = AGESA_SUCCESS;

  IDS_SKIP_HOOK (IDS_BEFORE_S3_SAVE, AmdRtbParams, &AmdRtbParams->StdHeader) {
    HeapBuffersPresent = 0;
    EarlyBufferSize = 0;
    LateBufferSize = 0;
    LateContextSize = 0;
    HeapSize = 0;
    NonMemoryRelatedDeviceList = NULL;
    MemoryRelatedDeviceList = NULL;
    MemDataPointer = NULL;

    LocateHeap.BufferHandle = AMD_SKIP_MEM_S3_SAVE;
    if (HeapLocateBuffer (&LocateHeap, &AmdRtbParams->StdHeader) == AGESA_SUCCESS) {
      EarlyBufferSize = 0;
    } else {
      // Get memory device list
      MemFS3GetDeviceList (&MemoryRelatedDeviceList, AmdRtbParams->OptionMemoryInstallPtr, &AmdRtbParams->StdHeader);
      LocateHeap.BufferHandle = AMD_MEM_S3_SAVE_HANDLE;
      if (HeapLocateBuffer (&LocateHeap, &AmdRtbParams->StdHeader) == AGESA_SUCCESS) {
        // Memory data has been saved and stored in the heap.
        // Just copy data from heap.
        // First 4 bytes in the heap store the size of the saved memory data.
        EarlyBufferSize = *(UINT32 *) LocateHeap.BufferPtr;
        MemDataPointer = LocateHeap.BufferPtr + 4;
      } else {
        if (MemoryRelatedDeviceList != NULL) {
          // Determine size needed
          EarlyBufferSize = GetWorstCaseContextSize (MemoryRelatedDeviceList, INIT_RESUME, &AmdRtbParams->StdHeader);
        }
      }
    }

    for (i = 0; i < S3LATE_TABLE_SIZE; i++) {
      LocateHeap.BufferHandle = S3LateHeapTable[i];
      if (HeapLocateBuffer (&LocateHeap, &AmdRtbParams->StdHeader) == AGESA_SUCCESS) {
        HeapBuffersPresent++;
        HeapSize += LocateHeap.BufferSize;
        HeapPtrs[i] = LocateHeap.BufferPtr;
        HeapSizes[i] = LocateHeap.BufferSize;
      } else {
        HeapPtrs[i] = NULL;
        HeapSizes[i] = 0;
      }
    }

    // Determine heap data size requirements
    if (HeapBuffersPresent != 0) {
      HeapSize += (HeapBuffersPresent * sizeof (BUFFER_NODE));
    }

    // Get non memory device list
    GetNonMemoryRelatedDeviceList (&NonMemoryRelatedDeviceList, &AmdRtbParams->StdHeader);

    if (NonMemoryRelatedDeviceList != NULL) {
      // Determine size needed
      LateContextSize = GetWorstCaseContextSize (NonMemoryRelatedDeviceList, S3_LATE_RESTORE, &AmdRtbParams->StdHeader);
    }
    LateBufferSize = HeapSize + LateContextSize;
    if (LateBufferSize != 0) {
      LateBufferSize += sizeof (S3_VOLATILE_STORAGE_HEADER);
    }

    if ((EarlyBufferSize != 0) || (LateBufferSize != 0)) {
      //
      // Allocate a buffer
      //
      AllocParams.RequestedBufferSize = EarlyBufferSize + LateBufferSize;
      AllocParams.BufferHandle = AMD_S3_INFO_BUFFER_HANDLE;
      AllocParams.Persist = HEAP_SYSTEM_MEM;
      AGESA_TESTPOINT (TpIfBeforeAllocateS3SaveBuffer, &AmdRtbParams->StdHeader);
      if (HeapAllocateBuffer (&AllocParams, &AmdRtbParams->StdHeader) != AGESA_SUCCESS) {
        if (AGESA_ERROR > ReturnStatus) {
          ReturnStatus = AGESA_ERROR;
        }
      }
      AGESA_TESTPOINT (TpIfAfterAllocateS3SaveBuffer, &AmdRtbParams->StdHeader);
      if (EarlyBufferSize != 0) {
        AmdRtbParams->S3DataBlock.NvStorage = AllocParams.BufferPtr;
        if (MemDataPointer != NULL) {
          LibAmdMemCopy (AmdRtbParams->S3DataBlock.NvStorage,
                         MemDataPointer,
                         EarlyBufferSize,
                         &AmdRtbParams->StdHeader);
          SaveDeviceListContext (NULL,
                                 AmdRtbParams->S3DataBlock.NvStorage,
                                 PSP_INIT_RESUME,
                                 &EarlyBufferSize,
                                 &AmdRtbParams->StdHeader);
        } else {
          SaveDeviceListContext (MemoryRelatedDeviceList,
                                 AmdRtbParams->S3DataBlock.NvStorage,
                                 INIT_RESUME,
                                 &EarlyBufferSize,
                                 &AmdRtbParams->StdHeader);
        }
      }
      AmdRtbParams->S3DataBlock.NvStorageSize = EarlyBufferSize;

      if (LateBufferSize != 0) {
        BufferPointer = AllocParams.BufferPtr;
        AmdRtbParams->S3DataBlock.VolatileStorage = &(BufferPointer[EarlyBufferSize]);

        ((S3_VOLATILE_STORAGE_HEADER *) AmdRtbParams->S3DataBlock.VolatileStorage)->HeapOffset = NULL;
        ((S3_VOLATILE_STORAGE_HEADER *) AmdRtbParams->S3DataBlock.VolatileStorage)->HeapSize = HeapSize;
        ((S3_VOLATILE_STORAGE_HEADER *) AmdRtbParams->S3DataBlock.VolatileStorage)->RegisterDataOffset = NULL;
        ((S3_VOLATILE_STORAGE_HEADER *) AmdRtbParams->S3DataBlock.VolatileStorage)->RegisterDataSize = LateContextSize;

        if (HeapSize != 0) {
          // Transfer heap contents
          ((S3_VOLATILE_STORAGE_HEADER *) AmdRtbParams->S3DataBlock.VolatileStorage)->HeapOffset = sizeof (S3_VOLATILE_STORAGE_HEADER);

          HeapBuffer = &BufferPointer[EarlyBufferSize + sizeof (S3_VOLATILE_STORAGE_HEADER)];
          for (i = 0; i < S3LATE_TABLE_SIZE; i++) {
            if (HeapPtrs[i] != NULL) {
              HeapNode = (BUFFER_NODE *) HeapBuffer;
              HeapNode->BufferSize = HeapSizes[i]; // S3LateHeapTable[i].BufferLength;
              HeapNode->BufferHandle = S3LateHeapTable[i];
              HeapBuffer += sizeof (HeapNode);
              LibAmdMemCopy ((VOID *) HeapBuffer, HeapPtrs[i], HeapSizes[i], &AmdRtbParams->StdHeader);
              HeapBuffer += HeapSizes[i];
            }
          }
        }

        if (LateContextSize != 0) {

          ((S3_VOLATILE_STORAGE_HEADER *) AmdRtbParams->S3DataBlock.VolatileStorage)->RegisterDataOffset = HeapSize + sizeof (S3_VOLATILE_STORAGE_HEADER);

          SaveDeviceListContext (NonMemoryRelatedDeviceList,
                                 &(BufferPointer[EarlyBufferSize + HeapSize + sizeof (S3_VOLATILE_STORAGE_HEADER)]),
                                 S3_LATE_RESTORE,
                                 &LateContextSize,
                                 &AmdRtbParams->StdHeader);
        }
        AmdRtbParams->S3DataBlock.VolatileStorageSize = HeapSize + LateContextSize + sizeof (S3_VOLATILE_STORAGE_HEADER);
      }
    }
  }
  return  ReturnStatus;
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This routine is responsible for setting default values for the input parameters
 * needed by the S3Init routine
 *
 * @param[in]     StdHeader      The standard header.
 * @param[in,out] S3DataBlock    Required input parameters for the S3Init routine.
 *
 * @retval        AGESA_SUCCESS  Always Succeeds.
 *
 */
AGESA_STATUS
S3InitConstructor (
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN OUT   S3_DATA_BLOCK     *S3DataBlock
  )
{
  S3DataBlockInitializer (S3DataBlock);
  return AGESA_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This routine is responsible for deallocation of heap space allocated during
 * S3Init routine
 *
 * @param[in]     StdHeader       The standard header.
 * @param[in,out] S3DataBlock     Required input parameters for the S3Init routine.
 *
 * @retval        AGESA_STATUS
 *
 */
AGESA_STATUS
S3InitDestructor (
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN OUT   S3_DATA_BLOCK     *S3DataBlock
  )
{
  AGESA_STATUS ReturnStatus;
  AGESA_STATUS RetVal;
  LOCATE_HEAP_PTR LocateHeap;

  ASSERT (StdHeader != NULL);

  ReturnStatus = AGESA_SUCCESS;

  // Deallocate heap space allocated during memory S3 save
  LocateHeap.BufferHandle = AMD_MEM_S3_SAVE_HANDLE;
  if (HeapLocateBuffer (&LocateHeap, StdHeader) == AGESA_SUCCESS) {
    RetVal = HeapDeallocateBuffer (AMD_MEM_S3_SAVE_HANDLE, StdHeader);
  } else {
    RetVal = MemS3Deallocate (StdHeader);
  }
  if (RetVal > ReturnStatus) {
    ReturnStatus = RetVal;
  }

  RetVal = HeapDeallocateBuffer (AMD_S3_NB_INFO_BUFFER_HANDLE, StdHeader);
  if (RetVal > ReturnStatus) {
    ReturnStatus = RetVal;
  }

  RetVal = HeapDeallocateBuffer (AMD_S3_INFO_BUFFER_HANDLE, StdHeader);
  if (RetVal > ReturnStatus) {
    ReturnStatus = RetVal;
  }

  return ReturnStatus;
}

