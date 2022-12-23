/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe post initialization.
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
#include  "GnbPcie.h"
#include  "GnbPcieFamServices.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieTrainingV2.h"
#include  "GnbPcieInitLib.h"
#include  "PcieComplexDataCZ.h"
#include  "PcieLibCZ.h"
#include  "GnbRegistersCZ.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_PCIEPOSTINITCZ_FILECODE
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
PciePostEarlyInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
PciePostInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
PciePostS3InterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

VOID
PcieLateRestoreInitCZS3Script (
  IN      AMD_CONFIG_PARAMS               *StdHeader,
  IN      UINT16                          ContextLength,
  IN      VOID*                           Context
  );

/*----------------------------------------------------------------------------------------*/
/**
 * PHY lane RxAdaptMode Init
 *
 *
 *
 * @param[in]  Engine              Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
STATIC
PciePhyLaneRxAdaptModeCZ (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{

  IDS_HDT_CONSOLE (GNB_TRACE, "PciePhyLaneInitRxAdaptModeCZ Enter\n");
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePhyLaneInitRxAdaptModeCZ Exit\n");
}


/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init various features on all ports
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
PciePostPortInitCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIE_LINK_SPEED_CAP LinkSpeedCapability;
  ASSERT (Engine->EngineData.EngineType == PciePortEngine);
  if (Engine->Type.Port.PortData.MiscControls.LinkSafeMode == PcieGen1) {
    PcieLinkSafeMode (Engine, Pcie);
  }
//  PciePhyLaneRxAdaptModeCZ (Engine, Pcie);
  LinkSpeedCapability = PcieFmGetLinkSpeedCap (PCIE_PORT_GEN_CAP_BOOT, Engine);
  PcieSetLinkSpeedCapV4 (LinkSpeedCapability, Engine, Pcie);
  if (PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS) && (LinkSpeedCapability > PcieGen1) && !PcieConfigIsSbPcieEngine (Engine)) {
    PcieTrainingSetPortStateV2 (Engine, LinkStateRetrain, FALSE, Pcie);
    PcieConfigUpdatePortStatus (Engine, 0, INIT_STATUS_PCIE_TRAINING_SUCCESS);
  }
  if (Engine->Type.Port.PortData.MiscControls.LinkComplianceMode == 0x1) {
    PcieForceCompliance (Engine, Pcie);
    PcieTrainingSetPortStateV2 (Engine, LinkStateResetExit, FALSE, Pcie);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init various features on all ports
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
PciePostS3PortInitCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIE_LINK_SPEED_CAP       LinkSpeedCapability;
  PCIE_LINK_TRAINING_STATE  State;

  ASSERT (Engine->EngineData.EngineType == PciePortEngine);

//  PciePhyLaneRxAdaptModeCZ (Engine, Pcie);
  LinkSpeedCapability = PcieFmGetLinkSpeedCap (PCIE_PORT_GEN_CAP_BOOT, Engine);
  PcieSetLinkSpeedCapV4 (LinkSpeedCapability, Engine, Pcie);

  if (Engine->Type.Port.PortData.MiscControls.LinkSafeMode == PcieGen1) {
    PcieLinkSafeMode (Engine, Pcie);
  }

  if (!PcieConfigIsSbPcieEngine (Engine)) {
    //
    // General Port
    //
    State = LinkStateDeviceNotPresent;
    if (Engine->Type.Port.PortData.LinkHotplug == HotplugDisabled || Engine->Type.Port.PortData.LinkHotplug == HotplugInboard) {
      //
      // Non hotplug device: we only check status from previous boot
      //
      if (PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
        State = LinkStateResetExit;
      }
    } else {
      UINT32  PcieScratch;
      //
      //  Get endpoint staus from scratch
      //
      PcieScratch = PciePortRegisterRead (Engine, DxFxxE4_x01_ADDRESS, Pcie);
      //
      // Hotplug device: we check ep status if reported
      //
      if ((PcieScratch & 0x1) == 0) {
        State = LinkStateResetExit;
      }
    }
    //
    // For compliance we always leave link in enabled state
    //
    if (Engine->Type.Port.PortData.MiscControls.LinkComplianceMode) {
      State = LinkStateResetExit;
    }
    PcieConfigUpdatePortStatus (Engine, 0, INIT_STATUS_PCIE_TRAINING_SUCCESS);
  } else {
    //
    // SB port
    //
    State = LinkStateTrainingSuccess;
  }
  PcieTrainingSetPortStateV2 (Engine, State, FALSE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Master procedure to init various features on all active ports
 *
 *
 *
 *
 * @param[in]   Pcie            Pointer to global PCIe configuration
 * @retval      AGESA_STATUS
 *
 */

AGESA_STATUS
STATIC
PciePostEarlyPortInitCZ (
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS  Status;
  Status = AGESA_SUCCESS;
  // Distributed Training started at PciePortInit complete it now to get access to PCIe devices
  if (Pcie->TrainingAlgorithm == PcieTrainingDistributed) {
    Pcie->TrainingExitState = LinkStateTrainingCompleted;
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Master procedure to init various features on all active ports
 *
 *
 *
 *
 * @param[in]   Pcie            Pointer to global PCIe configuration
 * @retval      AGESA_STATUS
 *
 */

AGESA_STATUS
STATIC
PciePostPortInitCZ (
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS  Status;
  Status = AGESA_SUCCESS;
  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PciePostPortInitCallbackCZ,
    NULL,
    Pcie
    );
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Master procedure to init various features on all active ports
 *
 *
 *
 *
 * @param[in]   Pcie            Pointer to global PCIe configuration
 * @retval      AGESA_STATUS
 *
 */

AGESA_STATUS
STATIC
PciePostS3PortInitCZ (
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS  Status;
  Status = AGESA_SUCCESS;
  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PciePostS3PortInitCallbackCZ,
    NULL,
    Pcie
    );
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie Init
 *
 *
 *
 * @param[in]  Pcie                Pointer to global PCIe configuration
 * @retval     AGESA_SUCCESS       Topology successfully mapped
 * @retval     AGESA_ERROR         Topology can not be mapped
 */

AGESA_STATUS
STATIC
PciePostInitCZ (
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIE_LINK_SPEED_CAP  GlobalSpeedCap;

  GlobalSpeedCap = PcieUtilGlobalGenCapability (
                     PCIE_PORT_GEN_CAP_BOOT | PCIE_GLOBAL_GEN_CAP_TRAINED_PORTS | PCIE_GLOBAL_GEN_CAP_HOTPLUG_PORTS,
                     Pcie
                     );


  PcieSetVoltageCZ (GlobalSpeedCap, Pcie);
  return  AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Post Init before memory init
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */
AGESA_STATUS
PciePostEarlyInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS            AgesaStatus;
  AGESA_STATUS            Status;
  PCIe_PLATFORM_CONFIG    *Pcie;

  AGESA_TESTPOINT (TpPciePostEarlyInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePostInterfaceCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  IDS_OPTION_HOOK (IDS_BEFORE_GPP_TRAINING, Pcie, StdHeader);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    PciePortsVisibilityControl (UnhidePorts, Pcie);

    Status = PciePostEarlyPortInitCZ (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    Status = PcieTrainingV2 (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    PciePortsVisibilityControl (HidePorts, Pcie);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePostInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpPciePostEarlyInterfaceCZExit, NULL);
  return  AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Post Init After memory init
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */
AGESA_STATUS
PciePostInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS          AgesaStatus;
  AGESA_STATUS          Status;
  PCIe_PLATFORM_CONFIG  *Pcie;
  AGESA_TESTPOINT (TpPciePostInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePostInterfaceCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  IDS_OPTION_HOOK (IDS_BEFORE_GEN2_INIT, Pcie, StdHeader);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    PciePortsVisibilityControl (UnhidePorts, Pcie);

    Status = PciePostInitCZ (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    Status = PciePostPortInitCZ (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    IDS_OPTION_HOOK (IDS_BEFORE_GEN3_INIT, Pcie, StdHeader);
    Status = PcieTrainingV2 (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    PciePortsVisibilityControl (HidePorts, Pcie);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePostInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpPciePostInterfaceCZExit, NULL);
  return  AgesaStatus;
}


/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Post Init for S3 resume
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */
AGESA_STATUS
PciePostS3InterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS          AgesaStatus;
  AGESA_STATUS          Status;
  PCIe_PLATFORM_CONFIG  *Pcie;
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePostS3InterfaceCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    PciePortsVisibilityControl (UnhidePorts, Pcie);

    Status = PciePostInitCZ (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    if (Pcie->TrainingAlgorithm == PcieTrainingDistributed) {
      Status = PciePostS3PortInitCZ (Pcie);
    } else {
      Status = PciePostPortInitCZ (Pcie);
    }
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    Status = PcieTrainingV2 (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    PciePortsVisibilityControl (HidePorts, Pcie);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePostS3InterfaceCZ Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe S3 restore
 *
 *
 *
 * @param[in]  StdHeader      Standard configuration header
 * @param[in]  ContextLength  Context Length (not used)
 * @param[in]  Context        Context pointer (not used)
 */
VOID
PcieLateRestoreInitCZS3Script (
  IN      AMD_CONFIG_PARAMS               *StdHeader,
  IN      UINT16                          ContextLength,
  IN      VOID*                           Context
  )
{
  PciePostS3InterfaceCZ (StdHeader);
}
