/* $NoKeywords:$ */
/**
 * @file
 *
 * NB services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include  "Gnb.h"
#include  "GnbPcieConfig.h"
#include  "GnbCommonLib.h"
#include  "GnbFamServices.h"
#include  "GnbRegistersCommonV2.h"
#include  "Library/AmdHeapLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBIOMMUIVRS_GNBIOMMUSCRATCH_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
AGESA_STATUS
GnbIommuScratchMemoryRangeInterface (
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Set Iommu Scratch Memory Range
 * 1) code needs to be executed at Late Init
 * 2) Allocate heap using  heap type HEAP_RUNTIME_SYSTEM_MEM
 * 3) Allocate enough memory to be able to get address aligned required by register
 * 4) Assign same address to all Gnb in system
 *
 *
 * @param[in]  StdHeader       Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
GnbIommuScratchMemoryRangeInterface (
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  AGESA_STATUS          Status;
  ALLOCATE_HEAP_PARAMS  AllocHeapParams;
  UINT32                AddressLow;
  UINT32                AddressHigh;
  GNB_HANDLE            *GnbHandle;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuScratchMemoryRangeInterface Enter\n");

  AllocHeapParams.RequestedBufferSize = 128;
  AllocHeapParams.BufferHandle = AMD_GNB_IOMMU_SCRATCH_MEM_HANDLE;
  AllocHeapParams.Persist = HEAP_RUNTIME_SYSTEM_MEM;
  Status = HeapAllocateBuffer (&AllocHeapParams, StdHeader);
  if (Status != AGESA_SUCCESS) {
    IDS_HDT_CONSOLE (GNB_TRACE, "  Iommu Scratch Memory not allocated.\n");
    ASSERT (FALSE);
    return AGESA_FATAL;
  }

  AddressLow = (((UINT32) ((UINT64) AllocHeapParams.BufferPtr)) + 0x3F) & D0F0x98_x27_IOMMUUrAddr_31_6__MASK;
  AddressHigh = ((UINT32) (((UINT64) AllocHeapParams.BufferPtr) >> 32)) & D0F0x98_x26_IOMMUUrAddr_39_32__MASK;

  GnbHandle = GnbGetHandle (StdHeader);
  while (GnbHandle != NULL) {
    if (GnbFmCheckIommuPresent (GnbHandle, StdHeader)) {
      IDS_HDT_CONSOLE (GNB_TRACE, "Set Iommu Scratch Memory for Socket %d Silicon %d\n", GnbGetSocketId (GnbHandle) , GnbGetSiliconId (GnbHandle));
      GnbLibPciIndirectWrite (
        GnbHandle->Address.AddressValue | D0F0x94_ADDRESS,
        D0F0x98_x27_ADDRESS,
        AccessS3SaveWidth32,
        &AddressLow,
        StdHeader);

      GnbLibPciIndirectWrite (
        GnbHandle->Address.AddressValue | D0F0x94_ADDRESS,
        D0F0x98_x26_ADDRESS,
        AccessS3SaveWidth32,
        &AddressHigh,
        StdHeader);
    }
    GnbHandle = GnbGetNextHandle (GnbHandle);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuScratchMemoryRangeInterface Exit\n");

  return AGESA_SUCCESS;
}

