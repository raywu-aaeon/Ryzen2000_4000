/* $NoKeywords:$ */
/**
 * @file
 *
 * CZ specific PCIe services
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 311774 $   @e \$Date: 2015-01-27 07:47:17 +0800 (Tue, 27 Jan 2015) $
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
#include  "Library/AmdHeapLib.h"
#include  "GnbPcie.h"
#include  "GnbSbLib.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieInitLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieTrainingV2.h"
#include  "GnbNbInitLib.h"
#include  "PcieComplexDataCZ.h"
#include  "PcieLibCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbFuseTable.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_PCIELIBCZ_FILECODE
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
 * Request boot up voltage
 *
 *
 *
 * @param[in]  LinkCap             Global GEN capability
 * @param[in]  Pcie                Pointer to PCIe configuration data area
 */
VOID
PcieSetVoltageCZ (
  IN      PCIE_LINK_SPEED_CAP   LinkCap,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8                      TargetVid;
  UINT8                      MinVidIndex;
  UINT8                      VddNbVid[8];
  UINT8                      Index;
  PP_FUSE_ARRAY_V2           *PpFuseArray;
  UINT32                     Millivolt[6];
  D0F0xBC_xC0014004_STRUCT   D0F0xBC_xC0014004;
  D0F0xBC_xC0014007_STRUCT   D0F0xBC_xC0014007;
  D0F0xBC_xC0014008_STRUCT   D0F0xBC_xC0014008;
  D0F0xBC_xC00160C4_STRUCT   D0F0xBC_xC00160C4;
  D0F0xBC_xC00160C7_STRUCT   D0F0xBC_xC00160C7;
  D0F0xBC_xC00160C8_STRUCT   D0F0xBC_xC00160C8;
  D0F0xBC_xC001706C_STRUCT   D0F0xBC_xC001706C;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieSetVoltageCZ Enter\n");
  Index = 0;

  PpFuseArray = GnbLocateHeapBuffer (AMD_PP_FUSE_TABLE_HANDLE, GnbLibGetHeader (Pcie));
  if (PpFuseArray == NULL) {
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC0014004_TYPE, D0F0xBC_xC0014004_ADDRESS, &D0F0xBC_xC0014004, 0, GnbLibGetHeader (Pcie));
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC0014007_TYPE, D0F0xBC_xC0014007_ADDRESS, &D0F0xBC_xC0014007, 0, GnbLibGetHeader (Pcie));
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC0014008_TYPE, D0F0xBC_xC0014008_ADDRESS, &D0F0xBC_xC0014008, 0, GnbLibGetHeader (Pcie));
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC00160C4_TYPE, D0F0xBC_xC00160C4_ADDRESS, &D0F0xBC_xC00160C4, 0, GnbLibGetHeader (Pcie));
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC00160C7_TYPE, D0F0xBC_xC00160C7_ADDRESS, &D0F0xBC_xC00160C7, 0, GnbLibGetHeader (Pcie));
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC00160C8_TYPE, D0F0xBC_xC00160C8_ADDRESS, &D0F0xBC_xC00160C8, 0, GnbLibGetHeader (Pcie));
    GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), D0F0xBC_xC001706C_TYPE, D0F0xBC_xC001706C_ADDRESS, &D0F0xBC_xC001706C, 0, GnbLibGetHeader (Pcie));
    VddNbVid[0] = (UINT8) D0F0xBC_xC0014004.Field.GnbVid0;
    VddNbVid[1] = (UINT8) D0F0xBC_xC0014004.Field.GnbVid1;
    VddNbVid[2] = (UINT8) D0F0xBC_xC0014007.Field.GnbVid2;
    VddNbVid[3] = (UINT8) D0F0xBC_xC0014008.Field.GnbVid3;
    VddNbVid[4] = (UINT8) D0F0xBC_xC0014008.Field.GnbVid4;
    VddNbVid[5] = (UINT8) D0F0xBC_xC00160C4.Field.GnbVid5;
    VddNbVid[6] = (UINT8) D0F0xBC_xC00160C7.Field.GnbVid6;
    VddNbVid[7] = (UINT8) D0F0xBC_xC00160C8.Field.GnbVid7;
    if (LinkCap <= PcieGen2) {
      Index = (UINT8) D0F0xBC_xC001706C.Field.PcieGen2Vid;
    } else if (LinkCap >= PcieGen3) {
      Index = (UINT8) D0F0xBC_xC001706C.Field.PcieGen3Vid;
    }
  } else {
    VddNbVid[0] = PpFuseArray->VddNbVid[0];
    VddNbVid[1] = PpFuseArray->VddNbVid[1];
    VddNbVid[2] = PpFuseArray->VddNbVid[2];
    VddNbVid[3] = PpFuseArray->VddNbVid[3];
    VddNbVid[4] = PpFuseArray->VddNbVid[4];
    VddNbVid[5] = PpFuseArray->VddNbVid[5];
    VddNbVid[6] = PpFuseArray->VddNbVid[6];
    VddNbVid[7] = PpFuseArray->VddNbVid[7];
    if (LinkCap <= PcieGen2) {
      Index = PpFuseArray->PcieGen2Vid;
    } else if (LinkCap >= PcieGen3) {
      Index = PpFuseArray->PcieGen3Vid;
    }
  }

  if (LinkCap > PcieGen1) {

    ASSERT (VddNbVid[Index] != 0);
    TargetVid = VddNbVid[Index];

  } else {

    MinVidIndex = 0;
    for (Index = 0; Index < (sizeof (VddNbVid) / sizeof (VddNbVid[0])); Index++) {
      IDS_HDT_CONSOLE (PCIE_MISC, "  VddNbVid[%d] %x\n", Index, VddNbVid[Index]);
      if (VddNbVid[Index] > VddNbVid[MinVidIndex]) {
        MinVidIndex = (UINT8) Index;
      }
    }
    //ASSERT (VddNbVid[MinVidIndex] != 0);
    TargetVid = VddNbVid[MinVidIndex];

  }

  Millivolt[0] = GnbTranslateVidCodeToMillivolt (TargetVid, GnbLibGetHeader (Pcie)) * 4 / 100;
  IDS_HDT_CONSOLE (PCIE_MISC, "  Set Voltage for Gen %d, Vid code %d, Millivolt with 2 fraction = %d\n", LinkCap, TargetVid, Millivolt[0]);

  Millivolt[1] = 0;
  Millivolt[2] = 0;
  Millivolt[3] = 0;
  Millivolt[4] = 0;
  Millivolt[5] = 0;

  if (TargetVid != 0) {
    GnbRegisterWriteCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), TYPE_SMU_MSG, SMC_MSG_VddNbRequest, Millivolt, 0, GnbLibGetHeader (Pcie));
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieSetVoltageCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * PLL power up latency
 *
 *
 * @param[in]  Wrapper     Pointer to Wrapper config descriptor
 * @param[in]  Pcie        Pointer to PICe configuration data area
 * @retval                 Pll wake up latency in us
 */
UINT8
PciePifGetPllPowerUpLatencyCZ (
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  return 35;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Get max link speed capability supported by this port
 *
 *
 *
 * @param[in]  Flags              See Flags PCIE_PORT_GEN_CAP_BOOT / PCIE_PORT_GEN_CAP_MAX
 * @param[in]  Engine             Pointer to engine config descriptor
 * @retval     PcieGen1/PcieGen2  Max supported link gen capability
 */
PCIE_LINK_SPEED_CAP
PcieGetLinkSpeedCapCZ (
  IN       UINT32                Flags,
  IN       PCIe_ENGINE_CONFIG    *Engine
  )
{
  PCIE_LINK_SPEED_CAP   LinkSpeedCapability;
  PCIe_WRAPPER_CONFIG   *Wrapper;
  PCIe_PLATFORM_CONFIG  *Pcie;

  Wrapper = PcieConfigGetParentWrapper (Engine);
  Pcie = PcieConfigGetPlatform (Wrapper);

  LinkSpeedCapability = PcieGen3;
  IDS_HDT_CONSOLE (GNB_TRACE, "Init LinkSpeedCapability = %x\n", LinkSpeedCapability);

  if (Engine->Type.Port.PortData.LinkSpeedCapability == PcieGenMaxSupported) {
    Engine->Type.Port.PortData.LinkSpeedCapability = (UINT8) LinkSpeedCapability;
    IDS_HDT_CONSOLE (GNB_TRACE, "  Change to PcieGenMaxSupported = %x\n", LinkSpeedCapability);
  }
  if (Pcie->PsppPolicy == PsppPowerSaving) {
    LinkSpeedCapability = PcieGen1;
    IDS_HDT_CONSOLE (GNB_TRACE, "  Change to PsppPowerSaving Gen1\n");
  }
  if (Engine->Type.Port.PortData.LinkSpeedCapability < LinkSpeedCapability) {
    LinkSpeedCapability = Engine->Type.Port.PortData.LinkSpeedCapability;
    IDS_HDT_CONSOLE (GNB_TRACE, "  Change to LinkSpeedCapability = %x\n", LinkSpeedCapability);
  }
  if ((Flags & PCIE_PORT_GEN_CAP_BOOT) != 0) {
    if ((Pcie->PsppPolicy == PsppBalanceLow || Engine->Type.Port.PortData.MiscControls.LinkSafeMode == PcieGen1) && !PcieConfigIsSbPcieEngine (Engine)) {
      LinkSpeedCapability = PcieGen1;
      IDS_HDT_CONSOLE (GNB_TRACE, "  Change to PCIE_PORT_GEN_CAP_BOOT with Gen1\n");
    }
  }
  return LinkSpeedCapability;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Get timestamp
 *
 *
 *
 * @param[in]  StdHeader             Standard header
 * @retval     TimeStamp             Count
 */

UINT32
GnbTimeStampCZ (
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  UINT32 TimeStamp;

  TimeStamp = 0;

  GnbLibPciIndirectRead (
    MAKE_SBDFO (0, 0, 0, 0, 0xE0),
    0x13080F0,
    AccessWidth32,
    &TimeStamp,
    StdHeader
    );

  if (TimeStamp == 0) {
    GnbLibPciIndirectRead (
      MAKE_SBDFO (0, 0, 0, 0, 0xE0),
      0x13180F0,
      AccessWidth32,
      &TimeStamp,
      StdHeader
      );
  }

  return TimeStamp;

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
PcieTopologyLaneControlCZ (
  IN      LANE_CONTROL          Control,
  IN      UINT32                LaneBitMap,
  IN      PCIe_WRAPPER_CONFIG   *Wrapper,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
    )
{
  D0F0xE4_CORE_0129_STRUCT  D0F0xE4_CORE_0129;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologyLaneControlCZ Enter\n");
  D0F0xE4_CORE_0129.Value = PcieRegisterRead (
                            Wrapper,
                            CORE_SPACE (Wrapper->StartPcieCoreId, D0F0xE4_CORE_0129_ADDRESS),
                            Pcie
                            );

  if (Control == EnableLanes) {
    D0F0xE4_CORE_0129.Value |= LaneBitMap;
  } else if (Control == DisableLanes) {
    D0F0xE4_CORE_0129.Value &= (~LaneBitMap);
  }
  D0F0xE4_CORE_0129.Value &= ((1 << Wrapper->NumberOfLanes) - 1);
  PcieRegisterWrite (
    Wrapper,
    CORE_SPACE (Wrapper->StartPcieCoreId, D0F0xE4_CORE_0129_ADDRESS),
    D0F0xE4_CORE_0129.Value,
    TRUE,
    Pcie
    );
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieTopologyLaneControlCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Power down unused lanes and plls
 *
 *
 * @param[in]  Wrapper         Pointer to wrapper config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 */

VOID
PciePwrPowerDownUnusedLanesCZ (
  IN       PCIe_WRAPPER_CONFIG    *Wrapper,
  IN       PCIe_PLATFORM_CONFIG   *Pcie
  )
{
  UINT32              UnusedLanes;
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePwrPowerDownUnusedLanesCZ Enter\n");
  if (Wrapper->Features.PowerOffUnusedLanes != 0) {
    UnusedLanes = PcieUtilGetWrapperLaneBitMap (LANE_TYPE_CORE_ALL, LANE_TYPE_PCIE_CORE_ALLOC_ACTIVE, Wrapper);
    PcieTopologyLaneControlCZ (
      DisableLanes,
      UnusedLanes,
      Wrapper,
      Pcie
      );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePwrPowerDownUnusedLanesCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init various features on all active ports
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
DdiEdpPortDetectCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS             Status;
  BOOLEAN                  *EdpPresent;

  Status = AGESA_SUCCESS;

  IDS_HDT_CONSOLE (GNB_TRACE, "DdiEdpPortDetectCallbackCZ Enter\n");
  if ((Engine->Type.Ddi.DdiData.ConnectorType == ConnectorTypeEDP) ||
      (Engine->Type.Ddi.DdiData.ConnectorType == ConnectorTypeDpToLvds) ||
      (Engine->Type.Ddi.DdiData.ConnectorType == ConnectorTypeEDPToLvds) ||
      (Engine->Type.Ddi.DdiData.ConnectorType == ConnectorTypeEDPToLvdsSwInit)) {

    IDS_HDT_CONSOLE (GNB_TRACE, "Found eDP/LVDS Connector\n");
    EdpPresent = (BOOLEAN *) Buffer;
    *EdpPresent = TRUE;
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "DdiEdpPortDetectCallbackCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe eDP port detection and poower down
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
PcieEdpPortPowerCheckCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  GMMx1206C_STRUCT      GMMx1206C;
  BOOLEAN               EdpPresent;
  AGESA_STATUS          Status;
  AGESA_STATUS          AgesaStatus;
  PCIe_PLATFORM_CONFIG  *Pcie;
  AgesaStatus = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieEdpPortPowerCheckCZ Enter\n");
  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    EdpPresent = FALSE;
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_ALLOCATED | DESCRIPTOR_DDI_ENGINE | DESCRIPTOR_VIRTUAL,
      DdiEdpPortDetectCallbackCZ,
      (VOID *)&EdpPresent,
      Pcie
      );
    if (EdpPresent == FALSE) {
      // Power off
      GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), GMMx1206C_TYPE, GMMx1206C_ADDRESS, &GMMx1206C.Value, 0, GnbLibGetHeader (Pcie));
      GMMx1206C.Field.LVTMA_PWRSEQ_EN = 0;
      GMMx1206C.Field.LVTMA_PWRSEQ_TARGET_STATE = 0;
      GMMx1206C.Field.LVTMA_BLON_OVRD = 0;
      GnbRegisterWriteCZ (GnbGetHandle (GnbLibGetHeader (Pcie)), GMMx1206C_TYPE, GMMx1206C_ADDRESS, &GMMx1206C.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Pcie));
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidBeforeGfxInitCZ Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}



