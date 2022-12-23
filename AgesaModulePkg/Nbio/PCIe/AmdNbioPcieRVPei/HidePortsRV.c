/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe ports visibility control.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 276746 $   @e \$Date: 2014-10-28 12:22:52 -0600 (Mon, 28 Oct 2013) $
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
#include <AMD.h>
#include <Gnb.h>
#include <Filecode.h>
#include <GnbRegistersRV.h>
#include <GnbDxio.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/TimerLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcieConfigLib.h>

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVPEI_HIDEPORTSRV_FILECODE

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


/*----------------------------------------------------------------------------------------
 *                     L O C A L   D A T A   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
STATIC
PcieControlPortsZP (
  IN      PCIE_PORT_VISIBILITY    Control,
  IN      GNB_HANDLE              *GnbHandle
  );

VOID
STATIC
PcieEnablePortsZP (
  IN      GNB_HANDLE              *GnbHandle
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Control port visibility in PCI config space
 *
 *
 * @param[in]  Control         Control Hide/Unhide ports
 * @param[in]  GnbHandle       Pointer to GNB_HANDLE
 */
VOID
PciePortsVisibilityControlRV (
  IN      PCIE_PORT_VISIBILITY    Control,
  IN      GNB_HANDLE              *GnbHandle
  )
{
  switch (Control) {
  case UnhidePorts:
    IDS_HDT_CONSOLE (GNB_TRACE, "Unhide Ports\n");
    PcieControlPortsZP (UnhidePorts, GnbHandle);
    break;
  case HidePorts:
    IDS_HDT_CONSOLE (GNB_TRACE, "Hide Ports\n");
    PcieControlPortsZP (HidePorts, GnbHandle);
    PcieEnablePortsZP (GnbHandle);
    break;
  default:
    ASSERT (FALSE);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Hide/Unhide all ports
 *
 *
 * @param[in]  Control             Control Hide/Unhide ports
 * @param[in]  GnbHandle           Pointer to the Silicon Descriptor for this node
 */

VOID
STATIC
PcieControlPortsZP (
  IN      PCIE_PORT_VISIBILITY    Control,
  IN      GNB_HANDLE              *GnbHandle
  )
{
  UINT32              Value;
  UINT32              Index;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieControlPortsRV Entry \n");
  Value = (Control == HidePorts) ? ((1 << SMN_0x13B31004_BridgeDis_OFFSET) | (1 << SMN_0x13B31004_CfgDis_OFFSET)) : 0;
  Value |= (1 << SMN_0x13B31004_CrsEnable_OFFSET);

  for (Index = 0; Index < 7; Index++) {    ///@todo magic number 7
   NbioRegisterRMW (GnbHandle,
                    TYPE_SMN,
                    SMN_0x13B31004_ADDRESS + (Index << 10),
                    (UINT32)~(SMN_0x13B31004_BridgeDis_MASK | SMN_0x13B31004_CfgDis_MASK | SMN_0x13B31004_CrsEnable_MASK),
                    Value,
                    0   // Change to flags if used in DXE
                    );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieControlPortsRV Exit\n");
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Hide unused ports
 *
 *
 *
 * @param[in]  GnbHandle           Pointer to the Silicon Descriptor for this node
 */

VOID
STATIC
PcieEnablePortsZP (
  IN      GNB_HANDLE              *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG  *EngineList;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieEnablePortsRV Entry \n");
  EngineList = PcieConfigGetChildEngine (GnbHandle);
  while (EngineList != NULL) {
    if ((EngineList->InitStatus == INIT_STATUS_PCIE_TRAINING_SUCCESS) ||
       ((EngineList->Type.Port.PortData.LinkHotplug != HotplugDisabled) &&
        (EngineList->Type.Port.PortData.LinkHotplug != HotplugInboard))) {
      IDS_HDT_CONSOLE (GNB_TRACE, "PcieEnablePortsRV Enabling %d\n", EngineList->Type.Port.LogicalBridgeId);
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       SMN_0x13B31004_ADDRESS + (EngineList->Type.Port.LogicalBridgeId << 10),
                       (UINT32)~(SMN_0x13B31004_BridgeDis_MASK | SMN_0x13B31004_CfgDis_MASK | SMN_0x13B31004_CrsEnable_MASK),
                       (1 << SMN_0x13B31004_CrsEnable_OFFSET),
                       0   // Change to flags if used in DXE
                       );
    }
    EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetNextTopologyDescriptor (EngineList, DESCRIPTOR_TERMINATE_GNB);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieEnablePortsRV Exit \n");
  return;
}



