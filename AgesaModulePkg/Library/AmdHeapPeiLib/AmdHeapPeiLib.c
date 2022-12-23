/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to access heap.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: LIB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
*****************************************************************************
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Filecode.h>
#include <Library/BaseLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdHeapLib.h>

#define FILECODE LIBRARY_AMDHEAPPEILIB_AMDHEAPPEILIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
extern EFI_GUID  gAmdHeapHobGuid;

#define HEAP_BUFFER_NODE_SIGNATURE SIGNATURE_32 ('H', 'E', 'A', 'P')
/// Heap Node
typedef struct _HEAP_BUFFER_NODE {
  UINT32        Signature;                        ///< HEAP_BUFFER_NODE Signature
  UINT32        BufferHandle;                     ///< An unique ID of buffer.
  UINT32        BufferSize;                       ///< Size of buffer.
  UINT8         Persist;                          ///< A flag. If marked, to be stored and passed to AmdInitLate.
  UINT8         Valid;                            ///< PEI HOB doesn't provide a function for deallocate the HOB, this flag FALSE identify this node is invalid
//  UINT8         Data;                             ///< Heap Data
} HEAP_BUFFER_NODE;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
/**
 * Check If Persist field is valid
 *
 *
 * @param[in]  Persist               Persist field of HEAP_BUFFER_NODE structure
 *
 * @retval     TRUE                  Persist field Valid
 * @retval     FALSE                 Persist field Invalid
 */
BOOLEAN
STATIC
IsPersistValid (
  UINT8         Persist
  )
{
  //
  if ((Persist == HEAP_DO_NOT_EXIST_YET) ||
      (Persist == HEAP_LOCAL_CACHE) ||
      (Persist == HEAP_TEMP_MEM) ||
      (Persist == HEAP_SYSTEM_MEM) ||
      (Persist == HEAP_DO_NOT_EXIST_ANYMORE) ||
      (Persist == HEAP_S3_RESUME) ||
      (Persist == HEAP_BOOTTIME_SYSTEM_MEM) ||
      (Persist == HEAP_RUNTIME_SYSTEM_MEM)) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Allocates space for a new buffer in the heap
 *
 * This function will allocate new buffer by calling PEI HOB service, the allocated memory
 * will be filled with zeros
 *
 * @param[in,out]  AllocateHeapParams structure pointer containing the size of the
 *                                   desired new region, its handle, and the
 *                                   return pointer.
 * @param[in,out]  StdHeader         Config handle for library and services.
 *
 * @retval         AGESA_SUCCESS     No error
 * @retval         AGESA_BOUNDS_CHK  Handle already exists, or not enough
 *                                   free space
 * @retval         AGESA_UNSUPPORTED Input Parameter check fail
 * @retval         AGESA_ERROR       Locate Heap Fail
 *
 */
AGESA_STATUS
HeapAllocateBuffer (
  IN OUT   ALLOCATE_HEAP_PARAMS *AllocateHeapParams,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS Status;
  HEAP_BUFFER_NODE HeapBufferNode;
  LOCATE_HEAP_PTR LocateHeapPtr;
  VOID        *HobPtr;

  //Input Parameters check
  if (IsPersistValid (AllocateHeapParams->Persist) == FALSE) {
    return AGESA_UNSUPPORTED;
  }
  //Check duplicated handle
  LocateHeapPtr.BufferHandle = AllocateHeapParams->BufferHandle;
  if (HeapLocateBuffer (&LocateHeapPtr, NULL) == AGESA_SUCCESS) {
    return AGESA_BOUNDS_CHK;
  }

  //Create HEAP private information as supplement for EFI GUID HOB
  HeapBufferNode.Signature = HEAP_BUFFER_NODE_SIGNATURE;
  HeapBufferNode.BufferHandle = AllocateHeapParams->BufferHandle;
  HeapBufferNode.BufferSize = AllocateHeapParams->RequestedBufferSize;
  HeapBufferNode.Persist = AllocateHeapParams->Persist;
  HeapBufferNode.Valid = TRUE;
  //Create a Guid Hob, with request size plus the node size
  HobPtr = BuildGuidDataHob (&gAmdHeapHobGuid, &HeapBufferNode, sizeof (HEAP_BUFFER_NODE) + AllocateHeapParams->RequestedBufferSize);

  if (HobPtr != NULL) {
    AllocateHeapParams->BufferPtr = (UINT8 *) (HobPtr) + sizeof (HEAP_BUFFER_NODE);
    //Fill the allocate HEAP with INT3 machine code
    //SetMem (AllocateHeapParams->BufferPtr, AllocateHeapParams->RequestedBufferSize, 0xCC);
    SetMem (AllocateHeapParams->BufferPtr, AllocateHeapParams->RequestedBufferSize, 0);
  }

  Status = (HobPtr == NULL)? AGESA_ERROR : AGESA_SUCCESS;
  return Status;
}
/**
*  Internal routine used to find the matched HEAP Node in HOB List
*
* @param[in,out]  HeapHandle An unique ID of Heap buffer
*
  @return The matched HEAP GUID HOB among the whole HOB list, NULL if not founded
*/
VOID *
InternalGetHeapBufferNode (
  UINT32        HeapHandle
  )
{
  EFI_HOB_GUID_TYPE       *HeapGuidHob;
  HEAP_BUFFER_NODE             *HeapBufferNode;

  HeapGuidHob = GetFirstGuidHob (&gAmdHeapHobGuid);
  while (HeapGuidHob != NULL) {
    HeapBufferNode = GET_GUID_HOB_DATA (HeapGuidHob);

    //Check If node matches
    if ((HeapBufferNode->BufferHandle == HeapHandle) &&
        (HeapBufferNode->Signature == HEAP_BUFFER_NODE_SIGNATURE) &&
        (HeapBufferNode->Valid == TRUE)) {
      return GET_GUID_HOB_DATA (HeapGuidHob);
    }
    //Due GetNextGuidHob function does not skip the starting HOB pointer unconditionally: it returns HobStart back if HobStart itself meets the requirement;
    //Move to Next Hob Entry
    HeapGuidHob = GET_NEXT_HOB (HeapGuidHob);
    HeapGuidHob = GetNextGuidHob (&gAmdHeapHobGuid, HeapGuidHob);
  }
  return NULL;
}

/**
 * Deallocates a previously allocated buffer in the heap PEI HOB service
 *
 * This function will deallocate buffer by calling
 *
 * @param[in]      BufferHandle      Handle of the buffer to free.
 * @param[in]      StdHeader         Config handle for library and services.
 *
 * @retval         AGESA_SUCCESS     No error
 * @retval         AGESA_BOUNDS_CHK  Handle does not exist on the heap
 *
 */
AGESA_STATUS
HeapDeallocateBuffer (
  IN       UINT32 BufferHandle,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  HEAP_BUFFER_NODE             *HeapBufferNode;

  HeapBufferNode = (HEAP_BUFFER_NODE *) InternalGetHeapBufferNode (BufferHandle);

  if (HeapBufferNode == NULL) {
    //Can't find the specific Heap in HOB List
    return AGESA_BOUNDS_CHK;
  }
  //Invalid the Node
  HeapBufferNode->Valid = FALSE;
  return AGESA_SUCCESS;
}


/**
 * Locates a previously allocated buffer on the heap.
 *
 * This function searches the heap for a buffer with the desired handle, and
 * returns a pointer to the buffer.
 *
 * @param[in,out]  LocateHeap     Structure containing the buffer's handle,
 *                                   and the return pointer.
 * @param[in]      StdHeader         Config handle for library and services.
 *
 * @retval         AGESA_SUCCESS     No error
 * @retval         AGESA_BOUNDS_CHK  Handle does not exist on the heap
 *
 */
AGESA_STATUS
HeapLocateBuffer (
  IN OUT   LOCATE_HEAP_PTR *LocateHeap,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  HEAP_BUFFER_NODE             *HeapBufferNode;

  HeapBufferNode = (HEAP_BUFFER_NODE *) InternalGetHeapBufferNode (LocateHeap->BufferHandle);

  if (HeapBufferNode == NULL) {
    //Can't find the specific Heap in HOB List
    LocateHeap->BufferPtr = NULL;
    LocateHeap->BufferSize = 0;
    return AGESA_BOUNDS_CHK;
  }

  LocateHeap->BufferPtr = ((UINT8 *) HeapBufferNode + sizeof (HEAP_BUFFER_NODE));
  LocateHeap->BufferSize = HeapBufferNode->BufferSize;
  return AGESA_SUCCESS;
}

