/* $NoKeywords:$ */
/**
 * @file
 *
 *  PCIe link training
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312796 $   @e \$Date: 2015-02-11 18:56:00 +0800 (Wed, 11 Feb 2015) $
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
#include  "GnbCommonLib.h"
#include  "GnbTimerLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieInitLib.h"
#include  "GnbPcieTrainingV2.h"
#include  "GnbRegistersCommonV2.h"
#include  <Library/OemPcieResetControlLib.h>

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIETRAININGV2_PCIETRAININGV2_FILECODE
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

VOID
STATIC
PcieTrainingDebugDumpPortState (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  );

VOID
STATIC
PcieSetResetStateOnEnginesV2 (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  );

VOID
STATIC
PcieTrainingCheckResetDurationV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  );

VOID
STATIC
PcieTrainingDeassertResetV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  );

VOID
STATIC
PcieTrainingBrokenLineV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  );

VOID
STATIC
PcieTrainingGen2FailV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Set link State
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  State               State to set
 * @param[in]  UpdateTimeStamp     Update time stamp
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
PcieTrainingSetPortStateV2 (
  IN      PCIe_ENGINE_CONFIG        *CurrentEngine,
  IN      PCIE_LINK_TRAINING_STATE  State,
  IN      BOOLEAN                   UpdateTimeStamp,
  IN      PCIe_PLATFORM_CONFIG      *Pcie
  )
{
  UINT32 TimeStamp;
  CurrentEngine->Type.Port.State = (UINT8) State;
  if (UpdateTimeStamp) {
    TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));
    CurrentEngine->Type.Port.TimeStamp = TimeStamp;
  }
  GNB_DEBUG_CODE (
    PcieTrainingDebugDumpPortState (CurrentEngine, Pcie)
    );
}


/*----------------------------------------------------------------------------------------*/
/**
 * Set state for all engines connected to same reset ID
 *
 *
 *
 * @param[in]       Engine              Pointer to engine config descriptor
 * @param[in, out]  Buffer              Pointer to Reset Id
 * @param[in]       Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieSetResetStateOnEnginesV2 (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8 ResetId;
  ResetId = *(UINT8 *)Buffer;
  if (Engine->Type.Port.PortData.ResetId == ResetId && !PcieConfigIsSbPcieEngine (Engine)) {
    PcieTrainingSetPortStateV2 (Engine, LinkStateResetDuration, TRUE, Pcie);
    GnbLibPciRMW (
      Engine->Type.Port.Address.AddressValue | DxFxx68_ADDRESS,
      AccessWidth32,
      (UINT32) ~DxFxx68_LinkDis_MASK,
      1 << DxFxx68_LinkDis_OFFSET,
      GnbLibGetHeader (Pcie)
      );
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Assert GPIO port reset.
 *
 *  Transition to LinkStateResetDuration state
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingAssertReset (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_SLOT_RESET_INFO ResetInfo;
  ResetInfo.ResetControl = AssertSlotReset;
  ResetInfo.ResetId = CurrentEngine->Type.Port.PortData.ResetId;
  LibAmdMemCopy (&ResetInfo.StdHeader, GnbLibGetHeader (Pcie), sizeof (AMD_CONFIG_PARAMS), GnbLibGetHeader (Pcie));
  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PcieSetResetStateOnEnginesV2,
    (VOID *)&CurrentEngine->Type.Port.PortData.ResetId,
    Pcie
    );
  AgesaPcieSlotResetControl (0, &ResetInfo);
}


/*----------------------------------------------------------------------------------------*/
/**
 * Check for reset duration
 *
 *  Transition to LinkStateResetDuration state
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingCheckResetDurationV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32 TimeStamp;
  TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));
  if (TIMESTAMPS_DELTA (TimeStamp, CurrentEngine->Type.Port.TimeStamp) >= Pcie->LinkGpioResetAssertionTime) {
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateResetExit, FALSE, Pcie);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Deassert GPIO port reset.
 *
 *  Transition to LinkStateResetDuration state
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Platform configuration
 *
 */
VOID
STATIC
PcieTrainingDeassertResetV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_SLOT_RESET_INFO ResetInfo;
  ResetInfo.ResetControl = DeassertSlotReset;
  ResetInfo.ResetId = CurrentEngine->Type.Port.PortData.ResetId;
  LibAmdMemCopy (&ResetInfo.StdHeader, GnbLibGetHeader (Pcie), sizeof (AMD_CONFIG_PARAMS), GnbLibGetHeader (Pcie));
  AgesaPcieSlotResetControl (0, &ResetInfo);
  GnbLibPciRMW (
    CurrentEngine->Type.Port.Address.AddressValue | DxFxx68_ADDRESS,
    AccessWidth32,
    (UINT32) ~DxFxx68_LinkDis_MASK,
    0 << DxFxx68_LinkDis_OFFSET,
    GnbLibGetHeader (Pcie)
    );
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkTrainingResetTimeout, TRUE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Check for after reset deassertion timeout
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingCheckResetTimeout (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32 TimeStamp;
  TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));
  if (TIMESTAMPS_DELTA (TimeStamp, CurrentEngine->Type.Port.TimeStamp) >= Pcie->LinkResetToTrainingTime) {
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateReleaseTraining, FALSE, Pcie);
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Release training
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingRelease (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8                   LinkTrainingState;
  GNB_HANDLE              *GnbHandle;
  UINT32                  Address;

  GnbHandle = GnbGetHandle (GnbLibGetHeader (Pcie));
  Address = WRAP_SPACE2 (PcieConfigGetParentWrapper (CurrentEngine)->WrapId, D0F0xE4_WRAP_0800_ADDRESS + 0x100 * CurrentEngine->Type.Port.PortId);

  PcieRegisterWriteField (
    PcieConfigGetParentWrapper (CurrentEngine),
    Address,
    D0F0xE4_WRAP_0800_HoldTraining_OFFSET,
    D0F0xE4_WRAP_0800_HoldTraining_WIDTH,
    0,
    FALSE,
    Pcie
    );
  if (CurrentEngine->Type.Port.PortData.MiscControls.LinkComplianceMode == 0x1) {
    LinkTrainingState = LinkStateCompliance;
  } else {
    LinkTrainingState = LinkStateDetectPresence;
  }
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkTrainingState, TRUE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Detect presence of any EP on the link
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieTrainingDetectPresence (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8   LinkHwStateHistory[4];
  UINT32  TimeStamp;
  PcieUtilGetLinkHwStateHistory (CurrentEngine, &LinkHwStateHistory[0], 4, Pcie);
  if (LinkHwStateHistory[0] > 4) {
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateDetecting, TRUE, Pcie);
    return;
  }
  TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));
  if (TIMESTAMPS_DELTA (TimeStamp, CurrentEngine->Type.Port.TimeStamp) >= Pcie->LinkReceiverDetectionPooling) {
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateDeviceNotPresent, FALSE, Pcie);
  }
}



/*----------------------------------------------------------------------------------------*/
/**
 * Detect Link State
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieTrainingDetectLinkState (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8   LinkHwStateHistory[16];
  UINT32  TimeStamp;
  UINT8   LinkTrainingState;
  UINT8 FailPattern1 [] = {0x2a, 0x6};
  UINT8 FailPattern2 [] = {0x2a, 0x9};
  UINT8 FailPattern3 [] = {0x2a, 0xb};

  PcieUtilGetLinkHwStateHistory (CurrentEngine, &LinkHwStateHistory[0], 4, Pcie);
  if (LinkHwStateHistory[0] == 0x10) {
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateL0, FALSE, Pcie);
    return;
  };
  TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));
  if (TIMESTAMPS_DELTA (TimeStamp, CurrentEngine->Type.Port.TimeStamp) >= Pcie->LinkL0Pooling) {
    LinkTrainingState = LinkStateTrainingFail;
    PcieUtilGetLinkHwStateHistory (CurrentEngine, &LinkHwStateHistory[0], 16, Pcie);
    if (LinkHwStateHistory[0] == 0x7) {
      LinkTrainingState = LinkStateCompliance;
    } else if (PcieUtilSearchArray (LinkHwStateHistory, sizeof (LinkHwStateHistory), FailPattern1, sizeof (FailPattern1))) {
      LinkTrainingState = LinkStateBrokenLane;
    } else if (PcieUtilSearchArray (LinkHwStateHistory, sizeof (LinkHwStateHistory), FailPattern2, sizeof (FailPattern2))) {
      LinkTrainingState = LinkStateGen2Fail;
    } else if (PcieUtilSearchArray (LinkHwStateHistory, sizeof (LinkHwStateHistory), FailPattern3, sizeof (FailPattern3))) {
      LinkTrainingState = LinkStateGen2Fail;
    }
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkTrainingState, FALSE, Pcie);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Lanes enable/disable control
 *
 * @param[in]   Control             Lane control action
 * @param[in]   LaneBitMap          Core lanes bitmap
 * @param[in]   Wrapper             Pointer to Wrapper config descriptor
 * @param[in]   Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyLaneControlV5 (
  IN      LANE_CONTROL          Control,
  IN      UINT32                LaneBitMap,
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
    )
{
  D0F0xE4_WRAP_8029_STRUCT  D0F0xE4_WRAP_8029;
  D0F0xE4_WRAP_8029.Value = PcieRegisterRead (
                            Wrapper,
                            WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8029_ADDRESS),
                            Pcie
                            );

  if (Control == EnableLanes) {
    D0F0xE4_WRAP_8029.Value |= LaneBitMap;
  } else if (Control == DisableLanes) {
    D0F0xE4_WRAP_8029.Value &= (~LaneBitMap);
  }
  D0F0xE4_WRAP_8029.Value &= ((1 << Wrapper->NumberOfLanes) - 1);
  PcieRegisterWrite (
    Wrapper,
    WRAP_SPACE (Wrapper->WrapId, D0F0xE4_WRAP_8029_ADDRESS),
    D0F0xE4_WRAP_8029.Value,
    TRUE,
    Pcie
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Reduce link width
 *
 *
 * @param[in]  LinkWidth           Link width
 * @param[in]  Engine              Pointer to Engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 */
VOID
PcieTopologyReduceLinkWidthV5 (
  IN      UINT8                 LinkWidth,
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_WRAPPER_CONFIG       *Wrapper;
  UINT32                    LinkReversed;
  UINT8                     DeltaLinkWidthBitmap;
  UINT32                    LanesToDisable;
  Wrapper = PcieConfigGetParentWrapper (Engine);
  LinkReversed = PcieUtilIsLinkReversed (TRUE, Engine, Pcie);

  DeltaLinkWidthBitmap = (1 << (PcieConfigGetNumberOfCoreLane (Engine) - LinkWidth)) - 1;
  LanesToDisable = (DeltaLinkWidthBitmap << ((LinkReversed == 1) ? Engine->Type.Port.StartCoreLane : (Engine->Type.Port.StartCoreLane +  LinkWidth)));

  PcieTopologyLaneControlV5 (
    DisableLanes,
    LanesToDisable,
    Wrapper,
    Pcie
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Broken Lane
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieTrainingBrokenLineV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8 CurrentLinkWidth;
  UINT8 LinkTrainingState;
  CurrentLinkWidth = PcieUtilGetLinkWidth (CurrentEngine, Pcie);
  if ((CurrentLinkWidth < PcieConfigGetNumberOfPhyLane (CurrentEngine)) &&
      (CurrentLinkWidth > 0) &&
      ((CurrentEngine->InitStatus & INIT_STATUS_PCIE_PORT_BROKEN_LANE_X1) == 0)) {
    CurrentEngine->InitStatus |= INIT_STATUS_PCIE_PORT_BROKEN_LANE_RECOVERY;
    if (CurrentLinkWidth == 1) {
      CurrentEngine->InitStatus |= INIT_STATUS_PCIE_PORT_BROKEN_LANE_X1;
    }
    PcieTopologyReduceLinkWidthV5 (CurrentLinkWidth, CurrentEngine, Pcie);
    LinkTrainingState = LinkStateResetAssert;
// todo: remove temporary
//    PutEventLog (
//      AGESA_WARNING,
//      GNB_EVENT_BROKEN_LANE_RECOVERY,
//      CurrentEngine->Type.Port.Address.AddressValue,
//      0,
//      0,
//      0,
//      GnbLibGetHeader (Pcie)
//      );
  } else {
    LinkTrainingState = LinkStateGen2Fail;
  }
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkTrainingState, FALSE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Check if link fail because device does not support Gen2
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingGen2FailV2 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8 LinkTrainingState;
  if (CurrentEngine->Type.Port.PortData.MiscControls.LinkSafeMode != PcieGen1) {
    PcieConfigUpdatePortStatus (CurrentEngine, INIT_STATUS_PCIE_PORT_GEN2_RECOVERY, 0);
    CurrentEngine->Type.Port.PortData.MiscControls.LinkSafeMode = PcieGen1;
    PcieLinkSafeMode (CurrentEngine, Pcie);
    LinkTrainingState = LinkStateResetAssert;
// todo: remove temporary
//    PutEventLog (
//      AGESA_WARNING,
//      GNB_EVENT_BROKEN_LANE_RECOVERY,
//      CurrentEngine->Type.Port.Address.AddressValue,
//      0,
//      0,
//      0,
//      GnbLibGetHeader (Pcie)
//      );
  } else {
    LinkTrainingState = LinkStateTrainingFail;
  }
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkTrainingState, FALSE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Link in L0
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieCheckLinkL0 (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateVcoNegotiation, TRUE, Pcie);
}
/*----------------------------------------------------------------------------------------*/
/**
 * Check if link fail because device does not support Gen X
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingCheckVcoNegotiation (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32          TimeStamp;
  DxFxx128_STRUCT DxFxx128;
  TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));
  GnbLibPciRead (CurrentEngine->Type.Port.Address.AddressValue | DxFxx128_ADDRESS, AccessWidth32, &DxFxx128, GnbLibGetHeader (Pcie));
  if (DxFxx128.Field.VcNegotiationPending == 0) {
    UINT16  NumberOfPhyLane;
    NumberOfPhyLane = PcieConfigGetNumberOfPhyLane (CurrentEngine);
    if (Pcie->GfxCardWorkaround == GfxWorkaroundEnable && NumberOfPhyLane >= 8) {
      // Limit exposure of workaround to x8 and x16 port.
      PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateGfxWorkaround, TRUE, Pcie);
    } else {
      PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingSuccess, FALSE, Pcie);
    }
    return;
  }
  if (TIMESTAMPS_DELTA (TimeStamp, CurrentEngine->Type.Port.TimeStamp) >= 1000 * 1000) {
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateRetrain, FALSE, Pcie);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Check if for GFX workaround condition
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingGfxWorkaround (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32                TimeStamp;
  GFX_WORKAROUND_STATUS GfxWorkaroundStatus;
  TimeStamp = GnbFmTimeStamp (GnbLibGetHeader (Pcie));

  GfxWorkaroundStatus = PcieGfxCardWorkaroundV2 (CurrentEngine->Type.Port.Address, GnbLibGetHeader (Pcie));
  switch (GfxWorkaroundStatus) {
  case GFX_WORKAROUND_DEVICE_NOT_READY:
    if (TIMESTAMPS_DELTA (TimeStamp, CurrentEngine->Type.Port.TimeStamp) >= (3 * 1000000)) {
      PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingFail, TRUE, Pcie);
    }
    break;
  case GFX_WORKAROUND_SUCCESS:
    PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingSuccess, FALSE, Pcie);
    break;
  case GFX_WORKAROUND_RESET_DEVICE:
    if (CurrentEngine->Type.Port.GfxWrkRetryCount < 5) {
      CurrentEngine->Type.Port.GfxWrkRetryCount++;
      PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateResetAssert, TRUE, Pcie);
    } else {
      PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingFail, TRUE, Pcie);
    }
    break;
  default:
    ASSERT (FALSE);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Retrain link
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingRetrainLink (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  GnbLibPciRMW (
    CurrentEngine->Type.Port.Address.AddressValue | DxFxx68_ADDRESS,
    AccessWidth32,
    (UINT32) ~DxFxx68_RetrainLink_MASK,
    1 << DxFxx68_RetrainLink_OFFSET,
    GnbLibGetHeader (Pcie)
    );
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateDetecting, TRUE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Training fail on this port
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingFail (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieConfigUpdatePortStatus (CurrentEngine, INIT_STATUS_PCIE_PORT_TRAINING_FAIL, 0);
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateDeviceNotPresent, FALSE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Links training success
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieTrainingSuccess (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieConfigUpdatePortStatus (CurrentEngine, INIT_STATUS_PCIE_TRAINING_SUCCESS, 0);
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingCompleted, FALSE, Pcie);
  GnbLibPciRMW (
    CurrentEngine->Type.Port.Address.AddressValue | DxFxx68_ADDRESS,
    AccessWidth32,
    (UINT32) ~DxFxx68_LinkBWManagementStatus_MASK,
    1 << DxFxx68_LinkBWManagementStatus_OFFSET,
    GnbLibGetHeader (Pcie)
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Links in compliance
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingCompliance (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieConfigUpdatePortStatus (CurrentEngine,  INIT_STATUS_PCIE_PORT_IN_COMPLIANCE, 0);
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingCompleted, FALSE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCie EP not present
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingNotPresent (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  GNB_HANDLE              *GnbHandle;
  UINT32                  Address;

  GnbHandle = GnbGetHandle (GnbLibGetHeader (Pcie));
  Address = WRAP_SPACE2 (PcieConfigGetParentWrapper (CurrentEngine)->WrapId, D0F0xE4_WRAP_0800_ADDRESS + 0x100 * CurrentEngine->Type.Port.PortId);

  if ((CurrentEngine->Type.Port.PortData.LinkHotplug == HotplugEnhanced) || (CurrentEngine->Type.Port.PortData.LinkHotplug == HotplugServer)) {
  } else {
    PcieRegisterWriteField (
      PcieConfigGetParentWrapper (CurrentEngine),
      Address,
      D0F0xE4_WRAP_0800_HoldTraining_OFFSET,
      D0F0xE4_WRAP_0800_HoldTraining_WIDTH,
      1,
      FALSE,
      Pcie
      );
  }
  PcieTrainingSetPortStateV2 (CurrentEngine, LinkStateTrainingCompleted, FALSE, Pcie);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Final state. Port training completed.
 *
 * Initialization status recorded in PCIe_ENGINE_CONFIG.InitStatus
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */
VOID
STATIC
PcieTrainingCompleted (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
}

/*----------------------------------------------------------------------------------------*/
/**
 * Training state handling
 *
 *
 *
 * @param[in]       Engine              Pointer to engine config descriptor
 * @param[in, out]  Buffer              Indicate if engine in non final state
 * @param[in]       Pcie                Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieTrainingPortCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  BOOLEAN *TrainingComplete;
  TrainingComplete = (BOOLEAN *) Buffer;
  if (Engine->Type.Port.State < Pcie->TrainingExitState) {
    *TrainingComplete = FALSE;
  } else {
    return;
  }
  switch (Engine->Type.Port.State) {
  case LinkStateResetAssert:
    PcieTrainingAssertReset (Engine, Pcie);
    break;
  case LinkStateResetDuration:
    PcieTrainingCheckResetDurationV2 (Engine, Pcie);
    break;
  case LinkStateResetExit:
    PcieTrainingDeassertResetV2 (Engine, Pcie);
    break;
  case LinkTrainingResetTimeout:
    PcieTrainingCheckResetTimeout (Engine, Pcie);
    break;
  case LinkStateReleaseTraining:
    PcieTrainingRelease (Engine, Pcie);
    break;
  case LinkStateDetectPresence:
    PcieTrainingDetectPresence (Engine, Pcie);
    break;
  case LinkStateDetecting:
    PcieTrainingDetectLinkState (Engine, Pcie);
    break;
  case LinkStateBrokenLane:
    PcieTrainingBrokenLineV2 (Engine, Pcie);
    break;
  case LinkStateGen2Fail:
    PcieTrainingGen2FailV2 (Engine, Pcie);
    break;
  case LinkStateL0:
    PcieCheckLinkL0 (Engine, Pcie);
    break;
  case LinkStateVcoNegotiation:
    PcieTrainingCheckVcoNegotiation (Engine, Pcie);
    break;
  case LinkStateRetrain:
    PcieTrainingRetrainLink (Engine, Pcie);
    break;
  case LinkStateTrainingFail:
    PcieTrainingFail (Engine, Pcie);
    break;
  case LinkStateGfxWorkaround:
    PcieTrainingGfxWorkaround (Engine, Pcie);
    break;
  case LinkStateTrainingSuccess:
    PcieTrainingSuccess (Engine, Pcie);
    break;
  case LinkStateCompliance:
    PcieTrainingCompliance (Engine, Pcie);
    break;
  case LinkStateDeviceNotPresent:
    PcieTrainingNotPresent (Engine, Pcie);
    break;
  case LinkStateTrainingCompleted:
    PcieTrainingCompleted (Engine, Pcie);
    break;
  default:
    break;
  }

}


/*----------------------------------------------------------------------------------------*/
/**
 * Main link training procedure
 *
 *  Port end up in three possible state  LinkStateTrainingNotPresent/LinkStateCompliance/
 *                                       LinkStateTrainingSuccess
 *
 * @param[in]   Pcie                Pointer to global PCIe configuration
 * @retval      AGESA_STATUS
 *
 */

AGESA_STATUS
PcieTrainingV2 (
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS  Status;
  BOOLEAN       TrainingComplete;

  IDS_PERF_TIMESTAMP (TP_BEGINGNBPCIETRAINING, GnbLibGetHeader (Pcie));
  Status = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTrainingV2 Enter\n");
  do {
    TrainingComplete = TRUE;
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
      PcieTrainingPortCallback,
      &TrainingComplete,
      Pcie
      );
  } while (!TrainingComplete);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTrainingV2 Exit [%x]\n", Status);
  IDS_PERF_TIMESTAMP (TP_ENDGNBPCIETRAINING, GnbLibGetHeader (Pcie));
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Helper function to dump port state on state transition
 *
 *
 * @param[in]  CurrentEngine       Pointer to engine config descriptor
 * @param[in]  Pcie                Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieTrainingDebugDumpPortState (
  IN      PCIe_ENGINE_CONFIG    *CurrentEngine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  IDS_HDT_CONSOLE (PCIE_MISC, "  Port %d:%d:%d State [%s] Time Stamp [%d]\n",
    CurrentEngine->Type.Port.Address.Address.Bus,
    CurrentEngine->Type.Port.Address.Address.Device,
    CurrentEngine->Type.Port.Address.Address.Function,
    (CurrentEngine->Type.Port.State == LinkStateTrainingFail) ? "LinkStateTrainingFail    " : (
    (CurrentEngine->Type.Port.State == LinkStateTrainingSuccess) ? "LinkStateTrainingSuccess " : (
    (CurrentEngine->Type.Port.State == LinkStateCompliance) ? "LinkStateCompliance      " : (
    (CurrentEngine->Type.Port.State == LinkStateDeviceNotPresent) ? "LinkStateDeviceNotPresent" :  (
    (CurrentEngine->Type.Port.State == LinkStateResetAssert) ? "LinkStateResetAssert     " :  (
    (CurrentEngine->Type.Port.State == LinkStateResetDuration) ? "LinkStateResetDuration   " :  (
    (CurrentEngine->Type.Port.State == LinkTrainingResetTimeout) ? "LinkTrainingResetTimeout " :  (
    (CurrentEngine->Type.Port.State == LinkStateReleaseTraining) ? "LinkStateReleaseTraining " :  (
    (CurrentEngine->Type.Port.State == LinkStateDetectPresence) ? "LinkStateDetectPresence  " :  (
    (CurrentEngine->Type.Port.State == LinkStateDetecting) ? "LinkStateDetecting       " :  (
    (CurrentEngine->Type.Port.State == LinkStateBrokenLane) ? "LinkStateBrokenLane      " :  (
    (CurrentEngine->Type.Port.State == LinkStateGen2Fail) ? "LinkStateGen2Fail        " :  (
    (CurrentEngine->Type.Port.State == LinkStateL0) ? "LinkStateL0              " :  (
    (CurrentEngine->Type.Port.State == LinkStateVcoNegotiation) ? "LinkStateVcoNegotiation  " :  (
    (CurrentEngine->Type.Port.State == LinkStateGfxWorkaround) ? "LinkStateGfxWorkaround   " : (
    (CurrentEngine->Type.Port.State == LinkStateTrainingCompleted) ? "LinkStateTrainingComplete" : (
    (CurrentEngine->Type.Port.State == LinkStateRetrain) ? "LinkStateRetrain         " : (
    (CurrentEngine->Type.Port.State == LinkStateResetExit) ? "LinkStateResetExit       " : "Unknown"))))))))))))))))),
    CurrentEngine->Type.Port.TimeStamp
    );
}

