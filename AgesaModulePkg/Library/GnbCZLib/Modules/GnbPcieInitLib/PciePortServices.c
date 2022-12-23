/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe port initialization service procedure
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 322247 $   @e \$Date: 2015-07-09 15:18:54 +0800 (Thu, 09 Jul 2015) $
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
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "GnbSbLib.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieInitLib.h"
#include  "GnbRegistersCommon.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIEINITLIB_PCIEPORTSERVICES_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
UINT8 L1State = 0x1b;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Set completion timeout
 *
 *
 *
 * @param[in]  Engine          Pointer to engine config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 *
 */

VOID
PcieCompletionTimeout (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  GnbLibPciRMW (
    Engine->Type.Port.Address.AddressValue | DxF0x80_ADDRESS,
    AccessWidth32,
    0xffffffff,
    0x6 << DxF0x80_CplTimeoutValue_OFFSET,
    GnbLibGetHeader (Pcie)
    );
  if (Engine->Type.Port.PortData.LinkHotplug != HotplugDisabled) {
    PciePortRegisterWriteField (
      Engine,
      DxF0xE4_x20_ADDRESS,
      DxF0xE4_x20_TxFlushTlpDis_OFFSET,
      DxF0xE4_x20_TxFlushTlpDis_WIDTH,
      0x0,
      TRUE,
      Pcie
      );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set misc slot capability
 *
 *
 *
 * @param[in]  Engine          Pointer to engine config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 *
 */

VOID
PcieLinkSetSlotCap (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  GnbLibPciRMW (
    Engine->Type.Port.Address.AddressValue | DxF0x58_ADDRESS,
    AccessWidth32,
    0xffffffff,
    1 << DxF0x58_SlotImplemented_OFFSET,
    GnbLibGetHeader (Pcie)
    );
  GnbLibPciRMW (
    Engine->Type.Port.Address.AddressValue | DxF0x3C_ADDRESS,
    AccessWidth32,
    0xffffffff,
    1 << DxF0x3C_IntPin_OFFSET,
    GnbLibGetHeader (Pcie)
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Safe mode to force link advertize Gen1 only capability in TS
 *
 *
 *
 * @param[in]  Engine          Pointer to engine config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 *
 */

VOID
PcieLinkSafeMode (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieFmSetLinkSpeedCap (PcieGen1, Engine, Pcie);
  PciePortRegisterRMW (
    Engine,
    DxF0xE4_xA2_ADDRESS,
    DxF0xE4_xA2_LcUpconfigureDis_MASK,
    (1 << DxF0xE4_xA2_LcUpconfigureDis_OFFSET),
    FALSE,
    Pcie
    );
}


/*----------------------------------------------------------------------------------------*/
/**
 * Set current link speed
 *
 *
 * @param[in]  Engine               Pointer to engine configuration descriptor
 * @param[in]  Pcie                 Pointer to global PCIe configuration
 *
 */
VOID
PcieSetLinkWidthCap (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PciePortRegisterRMW (
    Engine,
    DxF0xE4_xA2_ADDRESS,
    DxF0xE4_xA2_LcUpconfigureDis_MASK,
    0,
    FALSE,
    Pcie
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Force compliance
 *
 *
 *
 * @param[in]  Engine          Pointer to engine config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 *
 */

VOID
PcieForceCompliance (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  if (Engine->Type.Port.PortData.LinkSpeedCapability >= PcieGen2) {
    GnbLibPciRMW (
      Engine->Type.Port.Address.AddressValue | DxF0x88_ADDRESS,
      AccessWidth32,
      0xffffffff,
      0x1 << DxF0x88_EnterCompliance_OFFSET,
      GnbLibGetHeader (Pcie)
      );
  } else if (Engine->Type.Port.PortData.LinkSpeedCapability == PcieGen1) {
    PciePortRegisterWriteField (
      Engine,
      DxF0xE4_xC0_ADDRESS,
      DxF0xE4_xC0_StrapForceCompliance_OFFSET,
      DxF0xE4_xC0_StrapForceCompliance_WIDTH,
      0x1,
      FALSE,
      Pcie
      );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enable ASPM on SB link
 *
 *
 *
 * @param[in]  Engine          Pointer to engine config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 *
 */

VOID
PcieEnableAspm (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  if (Engine->Type.Port.PortData.LinkAspm != AspmDisabled) {
    if (PcieConfigIsSbPcieEngine (Engine)) {
      SbPcieLinkAspmControl (Engine, Pcie);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set current link speed
 *
 *
 * @param[in]  LinkSpeedCapability  Link Speed Capability
 * @param[in]  Engine               Pointer to engine configuration descriptor
 * @param[in]  Pcie                 Pointer to global PCIe configuration
 *
 */
VOID
PcieSetLinkSpeedCapV4 (
  IN      PCIE_LINK_SPEED_CAP   LinkSpeedCapability,
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  DxF0xE4_xA4_STRUCT  DxF0xE4_xA4;
  DxF0xE4_xC0_STRUCT  DxF0xE4_xC0;
  DxF0x88_STRUCT      DxF0x88;
  GnbLibPciRead (
    Engine->Type.Port.Address.AddressValue | DxF0x88_ADDRESS,
    AccessWidth32,
    &DxF0x88.Value,
    GnbLibGetHeader (Pcie)
   );
  DxF0xE4_xA4.Value = PciePortRegisterRead (
                        Engine,
                        DxF0xE4_xA4_ADDRESS,
                        Pcie
                        );
  DxF0xE4_xC0.Value = PciePortRegisterRead (
                        Engine,
                        DxF0xE4_xC0_ADDRESS,
                        Pcie
                        );

  switch (LinkSpeedCapability) {
  case PcieGen3:
    DxF0xE4_xA4.Field.LcGen2EnStrap = 0x1;
    DxF0xE4_xA4.Field.LcGen3EnStrap = 0x1;
    DxF0xE4_xA4.Field.LcMultUpstreamAutoSpdChngEn = 0x1;
    DxF0x88.Field.TargetLinkSpeed = 0x3;
    DxF0x88.Field.HwAutonomousSpeedDisable = 0x0;
    break;
  case PcieGen2:
    DxF0xE4_xA4.Field.LcGen2EnStrap = 0x1;
    DxF0xE4_xA4.Field.LcGen3EnStrap = 0x0;
    DxF0xE4_xA4.Field.LcMultUpstreamAutoSpdChngEn = 0x1;
    DxF0x88.Field.TargetLinkSpeed = 0x2;
    DxF0x88.Field.HwAutonomousSpeedDisable = 0x0;
    break;
  case PcieGen1:
    DxF0xE4_xA4.Field.LcGen2EnStrap = 0x0;
    DxF0xE4_xA4.Field.LcGen3EnStrap = 0x0;
    DxF0xE4_xA4.Field.LcMultUpstreamAutoSpdChngEn = 0x0;
    DxF0x88.Field.TargetLinkSpeed = 0x1;
    DxF0x88.Field.HwAutonomousSpeedDisable = 0x1;
    PcieRegisterWriteField (
      PcieConfigGetParentWrapper (Engine),
      WRAP_SPACE (PcieConfigGetParentWrapper (Engine)->WrapId, D0F0xE4_WRAP_0803_ADDRESS + 0x100 * Engine->Type.Port.PortId),
      D0F0xE4_WRAP_0803_StrapBifDeemphasisSel_OFFSET,
      D0F0xE4_WRAP_0803_StrapBifDeemphasisSel_WIDTH,
      0,
      FALSE,
      Pcie
      );
    break;
  default:
    ASSERT (FALSE);
    break;
  }

  if ((Pcie->PsppPolicy == PsppDisabled) || (PcieConfigIsSbPcieEngine (Engine))) {
    DxF0xE4_xC0.Field.StrapAutoRcSpeedNegotiationDis = 0x0;
  } else {
    DxF0xE4_xC0.Field.StrapAutoRcSpeedNegotiationDis = 0x1;
  }

  PciePortRegisterWrite (
    Engine,
    DxF0xE4_xA4_ADDRESS,
    DxF0xE4_xA4.Value,
    FALSE,
    Pcie
    );
  PciePortRegisterWrite (
    Engine,
    DxF0xE4_xC0_ADDRESS,
    DxF0xE4_xC0.Value,
    FALSE,
    Pcie
    );
  GnbLibPciWrite (
    Engine->Type.Port.Address.AddressValue | DxF0x88_ADDRESS,
    AccessWidth32,
    &DxF0x88.Value,
    GnbLibGetHeader (Pcie)
   );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set slot power limit
 *
 *
 *
 * @param[in]  Engine              Pointer to engine configuration
 * @param[in]  Pcie                Pointer to PCIe configuration
 */


VOID
PcieEnableSlotPowerLimitV5 (
  IN      PCIe_ENGINE_CONFIG     *Engine,
  IN      PCIe_PLATFORM_CONFIG   *Pcie
  )
{
  PCIe_SILICON_CONFIG   *Silicon;
  if (PcieLibIsEngineAllocated (Engine) && Engine->Type.Port.PortData.PortPresent != PortDisabled && !PcieConfigIsSbPcieEngine (Engine)) {
    IDS_HDT_CONSOLE (PCIE_MISC, "   Enable Slot Power Limit for Port % d\n", Engine->Type.Port.Address.Address.Device);
    Silicon = PcieConfigGetParentSilicon (Engine);
    GnbLibPciIndirectRMW (
      Silicon->Address.AddressValue | D0F0xC8_ADDRESS,
      D0F0xCC_x01_ADDRESS | ((Engine->Type.Port.PortData.DeviceNumber << 3 | Engine->Type.Port.PortData.FunctionNumber)  << D0F0xC8_NB_DEV_IND_SEL_OFFSET),
      AccessS3SaveWidth32,
      0xffffffff,
      1 << D0F0xCC_x01_SetPowEn_OFFSET,
      GnbLibGetHeader (Pcie)
    );
  }
}

