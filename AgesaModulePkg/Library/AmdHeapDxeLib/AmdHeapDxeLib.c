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
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdHeapLib.h>

#define FILECODE LIBRARY_AMDHEAPDXELIB_AMDHEAPDXELIB_FILECODE

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

/// Heap Node Header
typedef struct HEAP_BUFFER_NODE_LINKED {
  LIST_ENTRY    LinkNode;                         ///< Linked Node
  HEAP_BUFFER_NODE BufferNode;                    ///< Heap Buffer Node
} HEAP_BUFFER_NODE_LINKED;

///HEAP protocol revision 1.0
#define AMD_HEAP_PROTOCOL_REV1  0x00000001ul      ///< AMD Heap Protocol Rev 1.0
/// Heap Protocol definition
typedef struct _AMD_HEAP_PROTOCOL {
  UINT32        Rev;                              ///< Protocol Rev
  LIST_ENTRY    HeapListHead;                    ///< Linked List Header of HEAP
} AMD_HEAP_PROTOCOL;

///Used to get base address of HEAP_BUFFER_NODE_LINKED
#define HEAP_BUFFER_NODE_LINKED_FROM_THIS(a)  BASE_CR (a, HEAP_BUFFER_NODE_LINKED, LinkNode)

///Guid used to Locate Heap HOB
extern EFI_GUID  gAmdHeapHobGuid;
///Protocol used to locate the Header of HEAP LinkList
extern EFI_GUID  gAmdHeapHeaderProtocolGuid;

///Init Protocol data
AMD_HEAP_PROTOCOL mAmdHeapProtocolStruct = {
  AMD_HEAP_PROTOCOL_REV1,
  {
    NULL,
    NULL
  }
};
///Header of HEAP Linked list
LIST_ENTRY              *mHeapLinkedListHead;


/*----------------------------------------------------------------------------------------*/
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
 * Allocate memory, build HeapBufferNodeLinked node, and insert to the HEAP linked list
 * according to the HeapBufferNode
 *
 *
 * @param[in]  HeapBufferNode             Strcuture describe to be allocated heap buffer
 * @param[in, out]  HeapBufferNodeLinked  Return the pointer of allocated heap buffer node
 *
 * @retval     EFI_SUCCESS           Node successfully created
 * @retval     EFI_UNSUPPORTED       Memory allocation fail
 */
EFI_STATUS
BuildHeapBufferNodeLinked (
  HEAP_BUFFER_NODE        *HeapBufferNode,
  HEAP_BUFFER_NODE_LINKED **HeapBufferNodeLinked
  )
{
  HEAP_BUFFER_NODE_LINKED *_HeapBufferNodeLinked;

  //Allocate Memory according HEAP persist
  //For compatile still support previous Persist definition, but will keep the data through boot time for all persist type
  //And keep runtime persist for HEAP_RUNTIME_SYSTEM_MEM type.
  if (HeapBufferNode->Persist == HEAP_RUNTIME_SYSTEM_MEM) {
    _HeapBufferNodeLinked = AllocateRuntimePool (sizeof (HEAP_BUFFER_NODE_LINKED) + HeapBufferNode->BufferSize);
    ASSERT (_HeapBufferNodeLinked != NULL);
  } else {
    _HeapBufferNodeLinked = AllocatePool (sizeof (HEAP_BUFFER_NODE_LINKED) + HeapBufferNode->BufferSize);
    ASSERT (_HeapBufferNodeLinked != NULL);
  }

  if (_HeapBufferNodeLinked == NULL) {
    return EFI_UNSUPPORTED;
  }
  *HeapBufferNodeLinked = _HeapBufferNodeLinked;

  //Copy the contents to new allocated location
  CopyMem (&_HeapBufferNodeLinked->BufferNode, HeapBufferNode, sizeof (HEAP_BUFFER_NODE));
  //Insert Node to List
  InsertTailList (mHeapLinkedListHead,  &_HeapBufferNodeLinked->LinkNode);
  return EFI_SUCCESS;
}

/**
 * Create the heap linked list which used for DXE phase base on the GUID HOB
 * This function will only be called once on 1st enter of AmdHeapDxeLib, when
 * gAmdHeapHeaderProtocolGuid protocol hasn't been installed
 *
 */
VOID
EFIAPI
BuildHeapList (
  VOID
  )
{
  EFI_HOB_GUID_TYPE       *GuidHob;
  HEAP_BUFFER_NODE        *HeapBufferNodeOnHob;
  HEAP_BUFFER_NODE_LINKED *HeapBufferNodeLinked;


  HeapBufferNodeLinked = NULL;
  GuidHob = GetFirstGuidHob (&gAmdHeapHobGuid);
  //Traversal the GUID HOB to find AMD HEAP GUID HOB Node
  while (GuidHob != NULL) {
    HeapBufferNodeOnHob = GET_GUID_HOB_DATA (GuidHob);

    //Check If node matches
    if ((HeapBufferNodeOnHob->Signature == HEAP_BUFFER_NODE_SIGNATURE) &&
        (HeapBufferNodeOnHob->Valid == TRUE)) {
      BuildHeapBufferNodeLinked (HeapBufferNodeOnHob, &HeapBufferNodeLinked);
      //Copy the HOB Data contents to new allocated location
      CopyMem (HeapBufferNodeLinked + 1, HeapBufferNodeOnHob + 1, HeapBufferNodeOnHob->BufferSize);
    }
    //Due GetNextGuidHob function does not skip the starting HOB pointer unconditionally: it returns HobStart back if HobStart itself meets the requirement;
    //Move to Next Hob Entry
    GuidHob = GET_NEXT_HOB (GuidHob);
    GuidHob = GetNextGuidHob (&gAmdHeapHobGuid, GuidHob);
  }
}

/**
  The constructor function used to locate Heap List Header and Initial the Heap Data if 1st enter in DXE

  @param  ImageHandle   The firmware allocated handle for the EFI image.
  @param  SystemTable   A pointer to the EFI System Table.

  @retval EFI_SUCCESS   The constructor successfully gets Heap List Header.
  @retval Other value   The constructor can't get Heap List Header.

**/
EFI_STATUS
EFIAPI
AmdHeapDxeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS      Status;
  EFI_HANDLE      Handle;
  AMD_HEAP_PROTOCOL *AmdHeapProtocol;

  AmdHeapProtocol = NULL;
  Status = gBS->LocateProtocol (&gAmdHeapHeaderProtocolGuid, NULL, &AmdHeapProtocol);
  if (EFI_ERROR (Status)) {
    //Heap List haven't been created, rebuild Heap List by copy from HOB
    InitializeListHead (&mAmdHeapProtocolStruct.HeapListHead);
    mHeapLinkedListHead = &mAmdHeapProtocolStruct.HeapListHead;
    BuildHeapList ();

    Handle = NULL;
    Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gAmdHeapHeaderProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mAmdHeapProtocolStruct
                    );
    ASSERT (Status == EFI_SUCCESS);
    return Status;
  }
  mHeapLinkedListHead = &AmdHeapProtocol->HeapListHead;
  return EFI_SUCCESS;
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
  EFI_STATUS EfiStatus;
  HEAP_BUFFER_NODE HeapBufferNode;
  LOCATE_HEAP_PTR LocateHeapPtr;
  HEAP_BUFFER_NODE_LINKED *HeapBufferNodeLinked;

  //Input Parameters check
  if (IsPersistValid (AllocateHeapParams->Persist) == FALSE) {
    return AGESA_UNSUPPORTED;
  }
  //Check duplicated handle
  LocateHeapPtr.BufferHandle = AllocateHeapParams->BufferHandle;
  if (HeapLocateBuffer (&LocateHeapPtr, NULL) == AGESA_SUCCESS) {
    return AGESA_BOUNDS_CHK;
  }
  AllocateHeapParams->BufferPtr = NULL;

  //Create HEAP private information as supplement for EFI GUID HOB
  HeapBufferNode.Signature = HEAP_BUFFER_NODE_SIGNATURE;
  HeapBufferNode.BufferHandle = AllocateHeapParams->BufferHandle;
  HeapBufferNode.BufferSize = AllocateHeapParams->RequestedBufferSize;
  HeapBufferNode.Persist = AllocateHeapParams->Persist;
  HeapBufferNode.Valid = TRUE;
  //Create a HEAP Linked Node
  EfiStatus = BuildHeapBufferNodeLinked (&HeapBufferNode, &HeapBufferNodeLinked);
  if (!EFI_ERROR (EfiStatus)) {
    AllocateHeapParams->BufferPtr = (UINT8 *) (HeapBufferNodeLinked + 1);
    //Fill the allocate HEAP with INT3 machine code
    //SetMem (AllocateHeapParams->BufferPtr, AllocateHeapParams->RequestedBufferSize, 0xCC);
    SetMem (AllocateHeapParams->BufferPtr, AllocateHeapParams->RequestedBufferSize, 0);
  }

  Status = (EFI_ERROR (EfiStatus))? AGESA_ERROR : AGESA_SUCCESS;
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
InternalGetHeapLinkedNode (
  UINT32        HeapHandle
  )
{
  LIST_ENTRY          *CurHeapNode;
  HEAP_BUFFER_NODE_LINKED *HeapBufferNodeLinked;

  CurHeapNode = GetFirstNode (mHeapLinkedListHead);

  while (!IsNull (mHeapLinkedListHead, CurHeapNode)) {
    //Check If node matches
    HeapBufferNodeLinked = HEAP_BUFFER_NODE_LINKED_FROM_THIS (CurHeapNode);
    if ((HeapBufferNodeLinked->BufferNode.BufferHandle == HeapHandle) &&
        (HeapBufferNodeLinked->BufferNode.Signature == HEAP_BUFFER_NODE_SIGNATURE)) {
      return HeapBufferNodeLinked;
    }
    CurHeapNode = GetNextNode (mHeapLinkedListHead, CurHeapNode);
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
  HEAP_BUFFER_NODE_LINKED *HeapBufferNode;

  HeapBufferNode = (HEAP_BUFFER_NODE_LINKED *) InternalGetHeapLinkedNode (BufferHandle);

  if (HeapBufferNode == NULL) {
    //Can't find the specific Heap in HOB List
    return AGESA_BOUNDS_CHK;
  }

  //Remove from the linked list
  RemoveEntryList (&HeapBufferNode->LinkNode);
  //Free the space
  FreePool (HeapBufferNode);
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
  HEAP_BUFFER_NODE_LINKED *HeapBufferNode;

  HeapBufferNode = (HEAP_BUFFER_NODE_LINKED *) InternalGetHeapLinkedNode (LocateHeap->BufferHandle);

  if (HeapBufferNode == NULL) {
    //Can't find the specific Heap in HOB List
    LocateHeap->BufferPtr = NULL;
    LocateHeap->BufferSize = 0;
    return AGESA_BOUNDS_CHK;
  }

  LocateHeap->BufferPtr = (UINT8 *) (HeapBufferNode + 1);
  LocateHeap->BufferSize = HeapBufferNode->BufferNode.BufferSize;
  return AGESA_SUCCESS;
}

