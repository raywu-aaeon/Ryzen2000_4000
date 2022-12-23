/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe port remapping functions.
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
#include <GnbDxio.h>
#include <PiPei.h>
#include <Filecode.h>
#include <GnbRegistersRV.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/TimerLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcieConfigLib.h>

#include <AmdPcieComplex.h>

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVPEI_PCIEHOTPLUGRV_FILECODE

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

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init hotplug features on all hotplug ports
 *
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer          Not used
 * @param[in]       Pcie            Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieHotplugInitCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_WRAPPER_CONFIG   *Wrapper;
  GNB_HANDLE            *GnbHandle;
  UINT32                SmnAddress;
  UINT32                Value;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieHotplugInitCallback Enter\n");
  if (Engine->Type.Port.PortData.LinkHotplug != HotplugDisabled ) {
    IDS_HDT_CONSOLE (GNB_TRACE, "Found Hotplug Engine at:\n");
    IDS_HDT_CONSOLE (GNB_TRACE, "  Port.PortId = %d\n", Engine->Type.Port.PortId);
    IDS_HDT_CONSOLE (GNB_TRACE, "  Port.PcieBridgeId = %d\n", Engine->Type.Port.PcieBridgeId);
    IDS_HDT_CONSOLE (GNB_TRACE, "  Port.Address = %x\n", Engine->Type.Port.Address);
    IDS_HDT_CONSOLE (GNB_TRACE, "  Type = ");

    Wrapper = PcieConfigGetParentWrapper (Engine);
    GnbHandle = (GNB_HANDLE *) PcieConfigGetParentSilicon (Engine);

    //devCfg:NB_PCIE_SLOT_CAP.HOTPLUG_CAPABLE = 1h;
    NbioRegisterRMW (GnbHandle,
                     TYPE_PCI,
                     MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CAP_ADDRESS),
                     (UINT32) ~(SLOT_CAP_HOTPLUG_CAPABLE_MASK),
                     1 << SLOT_CAP_HOTPLUG_CAPABLE_OFFSET,
                     0
                     );

    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     L1_DEBUG_1_PCIE0_ADDRESS,
                     (UINT32) ~(L1_MISC_CNTRL_1_REG_force_OrderStreamID_func_MASK),
                     1 << L1_MISC_CNTRL_1_REG_force_OrderStreamID_func_OFFSET,
                     0
                     );

//    SmnAddress = (Wrapper->WrapId == 0) ? GPP0_RX_CNTL_ADDRESS : GFX0_RX_CNTL_ADDRESS;
//    SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
//    NbioRegisterRMW (GnbHandle,
//                     PCIE_RX_CNTL_TYPE,
//                     SmnAddress,
//                     (UINT32) ~(PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_MASK),
//                     3 << PCIE_RX_CNTL_RX_RCB_CPL_TIMEOUT_OFFSET,
//                     0
//                     );

    SmnAddress = GPP0_TX_CNTL_ADDRESS;
    SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
    NbioRegisterRMW (GnbHandle,
                     PCIE_TX_CNTL_TYPE,
                     SmnAddress,
                     (UINT32) ~(PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_MASK),
                     0 << PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_OFFSET,
                     0
                     );

    //
    // Type specific hotplug configuration
    //
    switch (Engine->Type.Port.PortData.LinkHotplug) {
    //
    // Basic Hotplug Configuration
    //
    case DxioHotplugBasic:
      IDS_HDT_CONSOLE (GNB_TRACE, "DxioHotplugBasic\n");
      NbioRegisterRMW (GnbHandle,
                       TYPE_PCI,
                       MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                       (UINT32) ~(SLOT_CNTL_HOTPLUG_INTR_EN_MASK),
                       1 << SLOT_CNTL_HOTPLUG_INTR_EN_OFFSET,
                       0
                       );

      // devCfg:PCIEIND_P: PCIEP PCIEP_PORT_CNTL.NATIVE_PME_EN = !legacyHotPlug;
      SmnAddress = GPP0_PORT_CNTL_ADDRESS;
      SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
      NbioRegisterRMW (GnbHandle,
                       PCIE_TX_CNTL_TYPE,
                       SmnAddress,
                       (UINT32) ~(PCIEP_PORT_CNTL_NATIVE_PME_EN_MASK),
                       0 << PCIEP_PORT_CNTL_NATIVE_PME_EN_OFFSET,
                       0
                       );
      break;

    //
    // Enhanced Hotplug Configuration
    //
    case DxioHotplugEnhanced:
      IDS_HDT_CONSOLE (GNB_TRACE, "DxioHotplugEnhanced\n");

      NbioRegisterRMW (GnbHandle,
                       TYPE_PCI,
                       MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                       (UINT32) ~(SLOT_CNTL_HOTPLUG_INTR_EN_MASK),
                       1 << SLOT_CNTL_HOTPLUG_INTR_EN_OFFSET,
                       0
                       );

      // devCfg:PCIEIND_P: PCIEP PCIEP_PORT_CNTL.NATIVE_PME_EN = !legacyHotPlug;
      SmnAddress = GPP0_PORT_CNTL_ADDRESS;
      SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
      NbioRegisterRMW (GnbHandle,
                       PCIE_TX_CNTL_TYPE,
                       SmnAddress,
                       (UINT32) ~(PCIEP_PORT_CNTL_NATIVE_PME_EN_MASK),
                       1 << PCIEP_PORT_CNTL_NATIVE_PME_EN_OFFSET,
                       0
                       );

      SmnAddress = GPP0_LC_CNTL3_ADDRESS;
      SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
      NbioRegisterRMW (GnbHandle,
                       PCIE_LC_CNTL3_TYPE,
                       SmnAddress,
                       (UINT32) ~(PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_MASK |
                                  PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_MASK |
                                  PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_MASK |
                                  PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_MASK),
                       ((1 << PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_OFFSET) |
                        (0 << PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_OFFSET) |
                        (3 << PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_OFFSET) |
                        (3 << PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_OFFSET)),
                       0
                       );

      NbioRegisterRead (GnbHandle,
                      TYPE_PCI,
                      MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                      &Value,
                      0);
      IDS_HDT_CONSOLE (GNB_TRACE, "Value = 0x%x\n", Value);
      SmnAddress = GPP0_LC_CNTL3_ADDRESS;
      SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
      NbioRegisterRead (GnbHandle,
                        PCIE_LC_CNTL3_TYPE,
                        SmnAddress,
                        &Value,
                        0);
      IDS_HDT_CONSOLE (GNB_TRACE, "Value = 0x%x\n", Value);

      NbioRegisterRMW (GnbHandle,
                       PCIE_CNTL_TYPE,
                       PCIE0_CNTL_ADDRESS,
                       (UINT32) ~(PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_MASK),
                       0x5 << PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_OFFSET,
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       CPM_CONTROL_TYPE,
                       PCIE0_CPM_CONTROL_ADDRESS,
                       (UINT32) ~(CPM_CONTROL_RCVR_DET_CLK_ENABLE_MASK),
                       0x1 << CPM_CONTROL_RCVR_DET_CLK_ENABLE_OFFSET,
                       0
                       );
      break;
    //
    // Inboard Hotplug Configuration
    // Inboard Hotplug is similar to Enhanced Hotplug, except that the device must be present at boot
    //
    case DxioHotplugInboard:
      IDS_HDT_CONSOLE (GNB_TRACE, "DxioHotplugInboard\n");
      if (Engine->InitStatus == INIT_STATUS_PCIE_TRAINING_SUCCESS) {
        NbioRegisterRMW (GnbHandle,
                         TYPE_PCI,
                         MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                         (UINT32) ~(SLOT_CNTL_HOTPLUG_INTR_EN_MASK),
                         1 << SLOT_CNTL_HOTPLUG_INTR_EN_OFFSET,
                         0
                         );

        // devCfg:PCIEIND_P: PCIEP PCIEP_PORT_CNTL.NATIVE_PME_EN = !legacyHotPlug;
        SmnAddress = GPP0_PORT_CNTL_ADDRESS;
        SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
        NbioRegisterRMW (GnbHandle,
                         PCIE_TX_CNTL_TYPE,
                         SmnAddress,
                         (UINT32) ~(PCIEP_PORT_CNTL_NATIVE_PME_EN_MASK),
                         1 << PCIEP_PORT_CNTL_NATIVE_PME_EN_OFFSET,
                         0
                         );

        SmnAddress = GPP0_LC_CNTL3_ADDRESS;
        SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
        NbioRegisterRMW (GnbHandle,
                         PCIE_LC_CNTL3_TYPE,
                         SmnAddress,
                         (UINT32) ~(PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_MASK |
                                    PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_MASK |
                                    PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_MASK |
                                    PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_MASK),
                         ((1 << PCIE_LC_CNTL3_LC_ENHANCED_HOT_PLUG_EN_OFFSET) |
                          (0 << PCIE_LC_CNTL3_LC_RCVR_DET_EN_OVERRIDE_OFFSET) |
                          (3 << PCIE_LC_CNTL3_LC_EHP_RX_PHY_CMD_OFFSET) |
                          (3 << PCIE_LC_CNTL3_LC_EHP_TX_PHY_CMD_OFFSET)),
                         0
                         );

        NbioRegisterRead (GnbHandle,
                        TYPE_PCI,
                        MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                        &Value,
                        0);
        IDS_HDT_CONSOLE (GNB_TRACE, "Value = 0x%x\n", Value);
        SmnAddress = GPP0_LC_CNTL3_ADDRESS;
        SmnAddress |= (Engine->Type.Port.PortId % 8) << 12;
        NbioRegisterRead (GnbHandle,
                          PCIE_LC_CNTL3_TYPE,
                          SmnAddress,
                          &Value,
                          0);
        IDS_HDT_CONSOLE (GNB_TRACE, "Value = 0x%x\n", Value);

        NbioRegisterRMW (GnbHandle,
                         PCIE_CNTL_TYPE,
                         PCIE0_CNTL_ADDRESS,
                         (UINT32) ~(PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_MASK),
                         0x5 << PCIE_CNTL_LC_HOT_PLUG_DELAY_SEL_OFFSET,
                         0
                         );
        NbioRegisterRMW (GnbHandle,
                         CPM_CONTROL_TYPE,
                         PCIE0_CPM_CONTROL_ADDRESS,
                         (UINT32) ~(CPM_CONTROL_RCVR_DET_CLK_ENABLE_MASK),
                         0x1 << CPM_CONTROL_RCVR_DET_CLK_ENABLE_OFFSET,
                         0
                         );
      }
      break;
    case DxioHotplugServerExpress:
      IDS_HDT_CONSOLE (GNB_TRACE, "DxioHotplugServerExpress\n");
      //Express Module
      NbioRegisterRMW (GnbHandle,
                       TYPE_PCI,
                       MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CAP_ADDRESS),
                       (UINT32) ~(SLOT_CAP_ATTN_BUTTON_PRESENT_MASK |
                                  SLOT_CAP_PWR_CONTROLLER_PRESENT_MASK |
                                  SLOT_CAP_MRL_SENSOR_PRESENT_MASK |
                                  SLOT_CAP_ATTN_INDICATOR_PRESENT_MASK |
                                  SLOT_CAP_PWR_INDICATOR_PRESENT_MASK |
                                  SLOT_CAP_HOTPLUG_SURPRISE_MASK |
                                  SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_MASK |
                                  SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_MASK),
                       ((1 << SLOT_CAP_ATTN_BUTTON_PRESENT_OFFSET) |
                        (1 << SLOT_CAP_PWR_CONTROLLER_PRESENT_OFFSET) |
                        (0 << SLOT_CAP_MRL_SENSOR_PRESENT_OFFSET) |
                        (1 << SLOT_CAP_ATTN_INDICATOR_PRESENT_OFFSET) |
                        (1 << SLOT_CAP_PWR_INDICATOR_PRESENT_OFFSET) |
                        (1 << SLOT_CAP_HOTPLUG_SURPRISE_OFFSET) |
                        (1 << SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_OFFSET) |
                        (0 << SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_OFFSET)),
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       TYPE_PCI,
                       MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                       (UINT32) ~(SLOT_CNTL_ATTN_BUTTON_PRESSED_MASK |
                                  SLOT_CNTL_PWR_FAULT_DETECTED_MASK |
                                  SLOT_CNTL_MRL_SENSOR_CHANGED_MASK |
                                  SLOT_CNTL_PRESENCE_DETECT_CHANGED_MASK |
                                  SLOT_CNTL_COMMAND_COMPLETED_MASK |
                                  SLOT_CNTL_DL_STATE_CHANGED_MASK),
                       ((1 << SLOT_CNTL_ATTN_BUTTON_PRESSED_OFFSET) |
                        (1 << SLOT_CNTL_PWR_FAULT_DETECTED_OFFSET) |
                        (1 << SLOT_CNTL_MRL_SENSOR_CHANGED_OFFSET) |
                        (1 << SLOT_CNTL_PRESENCE_DETECT_CHANGED_OFFSET) |
                        (1 << SLOT_CNTL_COMMAND_COMPLETED_OFFSET) |
                        (1 << SLOT_CNTL_DL_STATE_CHANGED_OFFSET)),
                       0
                       );
      break;
    case DxioHotplugServerEntSSD:
      IDS_HDT_CONSOLE (GNB_TRACE, "DxioHotplugServerEntSSD\n");
      //Enterprise SSD
      NbioRegisterRMW (GnbHandle,
                       TYPE_PCI,
                       MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CAP_ADDRESS),
                       (UINT32) ~(SLOT_CAP_ATTN_BUTTON_PRESENT_MASK |
                                  SLOT_CAP_PWR_CONTROLLER_PRESENT_MASK |
                                  SLOT_CAP_MRL_SENSOR_PRESENT_MASK |
                                  SLOT_CAP_ATTN_INDICATOR_PRESENT_MASK |
                                  SLOT_CAP_PWR_INDICATOR_PRESENT_MASK |
                                  SLOT_CAP_HOTPLUG_SURPRISE_MASK |
                                  SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_MASK |
                                  SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_MASK),
                       ((0 << SLOT_CAP_ATTN_BUTTON_PRESENT_OFFSET) |
                        (0 << SLOT_CAP_PWR_CONTROLLER_PRESENT_OFFSET) |
                        (0 << SLOT_CAP_MRL_SENSOR_PRESENT_OFFSET) |
                        (0 << SLOT_CAP_ATTN_INDICATOR_PRESENT_OFFSET) |
                        (0 << SLOT_CAP_PWR_INDICATOR_PRESENT_OFFSET) |
                        (1 << SLOT_CAP_HOTPLUG_SURPRISE_OFFSET) |
                        (0 << SLOT_CAP_ELECTROMECH_INTERLOCK_PRESENT_OFFSET) |
                        (1 << SLOT_CAP_NO_COMMAND_COMPLETED_SUPPORTED_OFFSET)),
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       TYPE_PCI,
                       MAKE_SBDFO (0, 0, Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber, SLOT_CNTL_ADDRESS),
                       (UINT32) ~(SLOT_CNTL_ATTN_BUTTON_PRESSED_MASK |
                                  SLOT_CNTL_PWR_FAULT_DETECTED_MASK |
                                  SLOT_CNTL_MRL_SENSOR_CHANGED_MASK |
                                  SLOT_CNTL_PRESENCE_DETECT_CHANGED_MASK |
                                  SLOT_CNTL_COMMAND_COMPLETED_MASK |
                                  SLOT_CNTL_DL_STATE_CHANGED_MASK),
                       ((1 << SLOT_CNTL_ATTN_BUTTON_PRESSED_OFFSET) |
                        (1 << SLOT_CNTL_PWR_FAULT_DETECTED_OFFSET) |
                        (1 << SLOT_CNTL_MRL_SENSOR_CHANGED_OFFSET) |
                        (1 << SLOT_CNTL_PRESENCE_DETECT_CHANGED_OFFSET) |
                        (1 << SLOT_CNTL_COMMAND_COMPLETED_OFFSET) |
                        (1 << SLOT_CNTL_DL_STATE_CHANGED_OFFSET)),
                       0
                       );
      break;

    default:
      IDS_HDT_CONSOLE (GNB_TRACE, "Invalid Hotplug Type\n");
      ASSERT (FALSE);
      break;
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieHotplugInitCallback Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Map engine to specific PCI device address
 *
 *
 * @param[in]  GnbHandle           Pointer to the Silicon Descriptor for this node
 * @param[in]  PortDevMap          Pointer to PortDevMap
 */

VOID
PcieConfigureHotplugPortsRV (
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieConfigureHotplugPortsRV Enter\n");
  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PcieHotplugInitCallback,
    NULL,
    Pcie
    );
}



