/* $NoKeywords:$ */
/**
 * @file
 *
 * DXIO initialization services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
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
#include <PiPei.h>
#include <AmdPcieComplex.h>
#include <GnbDxio.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Library/BaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/GnbLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/DxioLibV2.h>
#include "DxioLibLocal.h"

#define FILECODE LIBRARY_DXIOLIBV2_DXIODEBUGOUT_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Helper function to dump input configuration to user engine descriptor
 *
 *
 * @param[in]  EngineDescriptor   Pointer to engine descriptor
 */
VOID
STATIC
DxioEntryConfigDump (
  IN       DXIO_ENGINE_DESCRIPTOR    *EngineDescriptor
  )
{
  UINT8       *Buffer;

  Buffer = (UINT8*) EngineDescriptor;
  //GnbLibDebugDumpBuffer ((VOID*) EngineDescriptor, sizeof(DXIO_ENGINE_DESCRIPTOR), 1, 16);
  IDS_HDT_CONSOLE (PCIE_MISC, "\n");

  IDS_HDT_CONSOLE (PCIE_MISC, "  Engine Type - %a\n",
    (EngineDescriptor->EngineType == DxioPcieEngine) ? "PCIe Port" : (
    (EngineDescriptor->EngineType == DxioSATAEngine) ? "SATA Port" : (
    (EngineDescriptor->EngineType == DxioUnusedEngine) ? "Unused" : "Invalid"))
    );
  IDS_HDT_CONSOLE (PCIE_MISC, "    Start Phy Lane - %d\n    End   Phy Lane - %d\n",
    EngineDescriptor->StartLane,
    EngineDescriptor->EndLane
  );
  IDS_HDT_CONSOLE (PCIE_MISC, "    Hotplug - %d\n", EngineDescriptor->HotPluggable);
  IDS_HDT_CONSOLE (PCIE_MISC, "    GpioGroupId - %d\n", EngineDescriptor->GpioGroupID);
  if (EngineDescriptor->EngineType == PciePortEngine) {
    IDS_HDT_CONSOLE (PCIE_MISC, "    PortPresent - %d\n    maxLinkSpeedCap - %d\n" ,
      EngineDescriptor->LinkDesc.Pcie.Capabilities.portPresent,
      EngineDescriptor->LinkDesc.Pcie.Capabilities.maxLinkSpeedCap
    );
    IDS_HDT_CONSOLE (PCIE_MISC, "    MacPortID - %d\n", EngineDescriptor->LinkDesc.Pcie.MacPortID);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Helper function to dump the data being sent to SMU
 *
 *
 * @param[in]  PlatformDescriptor   Pointer to platform descriptor
 * @param[in]  PlatformDescSize     Size of platform descriptor
 * @param[in]  AncillaryData        Pointer to platform descriptor
 * @param[in]  AncillaryDataSize    Size of platform descriptor
 */
VOID
DxioDebugDump (
  IN       DXIO_PLATFORM_DESCRIPTOR  *PlatformDescriptor,
  IN       UINT32                    PlatformDescSize,
  IN       UINT8                     *AncillaryData,
  IN       UINT32                    AncillaryDataSize
  )
{
  DXIO_PLATFORM_DESCRIPTOR  *PlatformPointer;
  DXIO_ENGINE_DESCRIPTOR    *EnginePointer;
  UINT32                    EngineCount;
  UINT32                    Index;


  PlatformPointer = (DXIO_PLATFORM_DESCRIPTOR *) PlatformDescriptor;
  EngineCount = PlatformPointer->NumEngineDesc;
  IDS_HDT_CONSOLE (GNB_TRACE, "Number of Engines is %d\n", EngineCount);
  PlatformPointer++;
  EnginePointer = (DXIO_ENGINE_DESCRIPTOR *)PlatformPointer;
  for (Index = 0;Index < EngineCount; Index++) {
    DxioEntryConfigDump (EnginePointer);
    EnginePointer++;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "Sending this Platform Descriptor to SMU...\n");
  GnbLibDebugDumpBuffer ((VOID*) PlatformDescriptor, PlatformDescSize << 2, 1, 16);
  IDS_HDT_CONSOLE (GNB_TRACE, "\n");
  if (AncillaryDataSize != 0) {
    IDS_HDT_CONSOLE (GNB_TRACE, "Sending this Ancillary Data to SMU...\n");
    GnbLibDebugDumpBuffer ((VOID*) AncillaryData, AncillaryDataSize << 2, 3, 8);
    IDS_HDT_CONSOLE (GNB_TRACE, "\n");
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "No ancillary data to send\n");
  }
  return;
}



