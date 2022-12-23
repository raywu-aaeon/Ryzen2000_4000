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
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdHeapLib.h>


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


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
  return AGESA_UNSUPPORTED;
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
  return AGESA_UNSUPPORTED;
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
  return AGESA_UNSUPPORTED;
}

