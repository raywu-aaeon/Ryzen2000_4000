/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific PCIe complex initialization services
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
#include  "GnbRegistersCommon.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIEINITLIB_PCIESILICONSERVICES_FILECODE
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

/*----------------------------------------------------------------------------------------*/
/**
 * Hide/Unhide all ports
 *
 *
 * @param[in]  Control             Control Hide/Unhide ports
 * @param[in]  Silicon             Pointer to silicon configuration descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */

VOID
STATIC
PcieSiliconControlPorts (
  IN      PCIE_PORT_VISIBILITY    Control,
  IN      PCIe_SILICON_CONFIG     *Silicon,
  IN      PCIe_PLATFORM_CONFIG    *Pcie
  )
{
  PCIe_ENGINE_CONFIG  *EngineList;
  UINT32              Value;
  Value = (Control == HidePorts) ? ((1 << D0F0xCC_x01_BridgeDis_OFFSET) | (1 << D0F0xCC_x01_CfgDis_OFFSET)) : 0;
  Value |= (1 << D0F0xCC_x01_CsrEnable_OFFSET) | (1 << D0F0xCC_x01_SetPowEn_OFFSET);
  EngineList = PcieConfigGetChildEngine (Silicon);
  while (EngineList != NULL) {
    if (PcieConfigIsPcieEngine (EngineList)) {
      GnbLibPciIndirectRMW (
        Silicon->Address.AddressValue | D0F0xC8_ADDRESS,
        D0F0xCC_x01_ADDRESS | ((EngineList->Type.Port.NativeDevNumber << 3 | EngineList->Type.Port.NativeFunNumber) << D0F0xC8_NB_DEV_IND_SEL_OFFSET),
        AccessS3SaveWidth32,
        (UINT32)~(D0F0xCC_x01_BridgeDis_MASK | D0F0xCC_x01_CfgDis_MASK | D0F0xCC_x01_CsrEnable_MASK | D0F0xCC_x01_SetPowEn_MASK),
        Value,
        GnbLibGetHeader (Pcie)
        );
    }
    EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetNextTopologyDescriptor (EngineList, DESCRIPTOR_TERMINATE_GNB);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Hide unused ports
 *
 *
 *
 * @param[in]  Silicon             Pointer to silicon configuration data area
 * @param[in]  Pcie                Pointer to data area up to 256 byte
 */

VOID
STATIC
PcieSiliconEnablePorts (
  IN      PCIe_SILICON_CONFIG   *Silicon,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_ENGINE_CONFIG  *EngineList;
  EngineList = PcieConfigGetChildEngine (Silicon);
  while (EngineList != NULL) {
    if (PcieConfigIsPcieEngine (EngineList)) {
      if (!PcieConfigIsSbPcieEngine (EngineList) &&
        (PcieConfigCheckPortStatus (EngineList, INIT_STATUS_PCIE_TRAINING_SUCCESS) ||
        ((EngineList->Type.Port.PortData.LinkHotplug != HotplugDisabled) &&
        (EngineList->Type.Port.PortData.LinkHotplug != HotplugInboard)))) {
        GnbLibPciIndirectRMW (
          Silicon->Address.AddressValue | D0F0xC8_ADDRESS,
          D0F0xCC_x01_ADDRESS | ((EngineList->Type.Port.PortData.DeviceNumber << 3 | EngineList->Type.Port.PortData.FunctionNumber)  << D0F0xC8_NB_DEV_IND_SEL_OFFSET),
          AccessS3SaveWidth32,
          (UINT32)~(D0F0xCC_x01_BridgeDis_MASK | D0F0xCC_x01_CfgDis_MASK | D0F0xCC_x01_CsrEnable_MASK | D0F0xCC_x01_SetPowEn_MASK),
          ((1 << D0F0xCC_x01_CsrEnable_OFFSET) | (1 << D0F0xCC_x01_SetPowEn_OFFSET)),
          GnbLibGetHeader (Pcie)
        );
      }
    }
    EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetNextTopologyDescriptor (EngineList, DESCRIPTOR_TERMINATE_GNB);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Control port visibility in PCI config space
 *
 *
 * @param[in]  Control         Control Hide/Unhide ports
 * @param[in]  Pcie            Pointer to global PCIe configuration
 */
VOID
PciePortsVisibilityControl (
  IN      PCIE_PORT_VISIBILITY    Control,
  IN      PCIe_PLATFORM_CONFIG    *Pcie
  )
{
  PCIe_SILICON_CONFIG *SiliconList;
  SiliconList = (PCIe_SILICON_CONFIG *) PcieConfigGetChild (DESCRIPTOR_SILICON, &Pcie->Header);
  while (SiliconList != NULL) {
    switch (Control) {
    case UnhidePorts:
      PcieSiliconControlPorts (UnhidePorts, SiliconList, Pcie);
      break;
    case HidePorts:
      PcieSiliconControlPorts (HidePorts, SiliconList, Pcie);
      PcieSiliconEnablePorts (SiliconList, Pcie);
      break;
    default:
      ASSERT (FALSE);
    }
    SiliconList = (PCIe_SILICON_CONFIG *) PcieConfigGetNextTopologyDescriptor (SiliconList, DESCRIPTOR_TERMINATE_TOPOLOGY);
  }
}

