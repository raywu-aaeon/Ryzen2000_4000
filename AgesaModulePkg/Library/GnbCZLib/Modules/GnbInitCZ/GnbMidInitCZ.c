/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB mid post initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-26 11:00:43 +0800 (Thu, 26 Feb 2015) $
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
#include  "GnbFuseTable.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbCommonLib.h"
#include  "GnbNbInitLib.h"
#include  "GnbTable.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GnbFamServices.h"
#include  "OptionGnb.h"
#include  "GnbSmuInitLibV8.h"
#include  "GnbPcieInitLib.h"
#include  "Library/AmdHeapLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GNBMIDINITCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern GNB_TABLE ROMDATA      GnbMidInitTableCZ[];

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

AGESA_STATUS
GnbMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * ORB TX/RX Memory power gating
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
STATIC
GnbOrbMidMemoryPowerGating (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS              Status;
  GNB_HANDLE                *GnbHandle;
  GNB_BUILD_OPTIONS_CZ      *GnbBuildOptionData;
  D0F0x98_x02_STRUCT        D0F0x98_x02;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbOrbMidMemoryPowerGating Enter\n");
  Status = AGESA_SUCCESS;

  GnbHandle = GnbGetHandle (StdHeader);

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  GnbRegisterReadCZ (GnbHandle, D0F0x98_x02_TYPE, D0F0x98_x02_ADDRESS, &D0F0x98_x02.Value, 0, StdHeader);

  if (GnbBuildOptionData->CfgOrbTxMemPowerGating != OrbMemPowerGatingDisabled) {
    D0F0x98_x02.Field.OrbTxPgmemEn = 1;
    if (GnbBuildOptionData->CfgOrbTxMemPowerGating == OrbMemPowerGatingSD) {
      D0F0x98_x02.Field.TxPgmemStEn = 4;
    } else if (GnbBuildOptionData->CfgOrbTxMemPowerGating == OrbMemPowerGatingDS) {
      D0F0x98_x02.Field.TxPgmemStEn = 2;
    } else {
      D0F0x98_x02.Field.TxPgmemStEn = 1;
    }
  }

  if (GnbBuildOptionData->CfgOrbRxMemPowerGating != OrbMemPowerGatingDisabled) {
    D0F0x98_x02.Field.OrbRxPgmemEn = 1;
    if (GnbBuildOptionData->CfgOrbRxMemPowerGating == OrbMemPowerGatingSD) {
      D0F0x98_x02.Field.RxPgmemStEn = 4;
    } else if (GnbBuildOptionData->CfgOrbRxMemPowerGating == OrbMemPowerGatingDS) {
      D0F0x98_x02.Field.RxPgmemStEn = 2;
    } else {
      D0F0x98_x02.Field.RxPgmemStEn = 1;
    }
  }

  D0F0x98_x02.Field.PgmemHysteresis = 0x3F;

  GnbRegisterWriteCZ (GnbHandle, D0F0x98_x02_TYPE, D0F0x98_x02_ADDRESS, &D0F0x98_x02.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbOrbMidMemoryPowerGating Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * SPG ACGAZ Memory power gating
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
STATIC
GnbSPGACGAZMidMemoryPowerGating (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS              Status;
  GNB_HANDLE                *GnbHandle;
  GNB_BUILD_OPTIONS_CZ      *GnbBuildOptionData;
  UINT32                    D9F2xEC_x50;
  UINT32                    D8F0xEC_x50;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSPGACGAZMidMemoryPowerGating Enter\n");
  Status = AGESA_SUCCESS;

  GnbHandle = GnbGetHandle (StdHeader);

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  GnbRegisterReadCZ (GnbHandle, D9F2xEC_x50_TYPE, D9F2xEC_x50_ADDRESS, &D9F2xEC_x50, 0, StdHeader);
  GnbRegisterReadCZ (GnbHandle, D8F0xEC_x50_TYPE, D8F0xEC_x50_ADDRESS, &D8F0xEC_x50, 0, StdHeader);

  D9F2xEC_x50 &= 0xFFFFFFFC;
  D8F0xEC_x50 &= 0xFFFFFFFC;
  D9F2xEC_x50 |= (GnbBuildOptionData->CfgSpgMemPowerGatingEnable & 0x3);
  D8F0xEC_x50 |= (GnbBuildOptionData->CfgAcgAzMemPowerGatingEnable & 0x3);

  GnbRegisterWriteCZ (GnbHandle, D9F2xEC_x50_TYPE, D9F2xEC_x50_ADDRESS, &D9F2xEC_x50, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  GnbRegisterWriteCZ (GnbHandle, D8F0xEC_x50_TYPE, D8F0xEC_x50_ADDRESS, &D8F0xEC_x50, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbSPGACGAZMidMemoryPowerGating Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Program IOMMU MMIO registers
 *
 *
 *
 * @param[in]  GnbHandle           Pointer to GNB_HANDLE
 * @param[in]  StdHeader  Standard configuration header
 */

VOID
STATIC
GnbIommuMidInitProgramMmRegCZ (
  IN       GNB_HANDLE            *GnbHandle,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT16                  CapabilityOffset;
  UINT64                  BaseAddress;
  UINT32                  Value;
  PCI_ADDR                GnbIommuPciAddress;
  UINT8                   i;
  UINT32                  SupData;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitProgramMmRegCZ Enter\n");

  GnbIommuPciAddress = GnbGetIommuPciAddress (GnbHandle, StdHeader);
  CapabilityOffset = GnbLibFindPciCapability (GnbIommuPciAddress.AddressValue, IOMMU_CAP_ID, StdHeader);

  GnbLibPciRead (GnbIommuPciAddress.AddressValue | (CapabilityOffset + 0x8), AccessWidth32, &Value, StdHeader);
  BaseAddress = (UINT64) Value << 32;
  GnbLibPciRead (GnbIommuPciAddress.AddressValue | (CapabilityOffset + 0x4), AccessWidth32, &Value, StdHeader);
  BaseAddress |= Value;
  BaseAddress &= 0xfffffffffffffffe;
  IDS_HDT_CONSOLE (GNB_TRACE, "IOMMU base address %x\n", BaseAddress);
  // ISOC
  GnbLibMemRMW (BaseAddress + 0x18, AccessS3SaveWidth32, 0xFFFFF7FF, 0x800, StdHeader);
  // NXSUP
  SupData = 0;
  GnbLibMemRead (BaseAddress + 0x30, AccessWidth32, &Value, StdHeader);
  if ((Value & BIT3) != 0) {
    SupData |= BIT2;
  }
  // USSUP
  GnbLibMemRead (BaseAddress + 0x34, AccessWidth32, &Value, StdHeader);
  if ((Value & BIT5) != 0) {
    SupData |= BIT1;
  }
  for (i = 0; i < 4; i++) {
    GnbRegisterReadCZ (
      GnbHandle,
      D0F2xFC_x27_L1_TYPE,
      D0F2xFC_x27_L1_ADDRESS (i),
      &Value,
      0,
      StdHeader
      );
    Value |= SupData;
    GnbRegisterWriteCZ (
      GnbHandle,
      D0F2xFC_x27_L1_TYPE,
      D0F2xFC_x27_L1_ADDRESS (i),
      &Value,
      GNB_REG_ACC_FLAG_S3SAVE,
      StdHeader
      );
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitProgramMmRegCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Override IOMMU PCIE Strap
 *
 *
 *
 * @param[in]  GnbHandle           Pointer to GNB_HANDLE
 */

VOID
STATIC
GnbIommuMidInitPcieStrapOverrideCZ (
  IN       GNB_HANDLE            *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG     *EngineList;
  AMD_CONFIG_PARAMS      *StdHeader;
  PCIe_PLATFORM_CONFIG   *Pcie;
  AGESA_STATUS           AgesaStatus;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitPcieStrapOverrideCZ Enter\n");

  StdHeader = PcieConfigGetStdHeader (GnbHandle);
  AgesaStatus = PcieLocateConfigurationData (StdHeader, &Pcie);
  if (AgesaStatus != AGESA_SUCCESS) {
    return;
  }

  EngineList = PcieConfigGetChildEngine (GnbHandle);
  while (EngineList != NULL) {
    if (PcieConfigIsPcieEngine (EngineList)) {

      if (PcieConfigCheckPortStatus (EngineList, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
        PciePortRegisterRMW (
          EngineList,
          DxFxxE4_xC1_ADDRESS,
          DxFxxE4_xC1_StrapE2EPrefixEn_MASK | DxFxxE4_xC1_StrapExtendedFmtSupported_MASK,
          (1 << DxFxxE4_xC1_StrapE2EPrefixEn_OFFSET) | (1 << DxFxxE4_xC1_StrapExtendedFmtSupported_OFFSET),
          TRUE,
          Pcie
          );
      }
    }
    EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetNextTopologyDescriptor (EngineList, DESCRIPTOR_TERMINATE_GNB);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitPcieStrapOverrideCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Registers needs to be set if no GFX PCIe ports being us
 *
 *
 *
 * @param[in]  GnbHandle           Pointer to GNB_HANDLE
 */

VOID
STATIC
GnbIommuMidInitPcieCoreUsageCZ (
  IN       GNB_HANDLE            *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG    *EngineList;
  D0F2xF4_x57_STRUCT    D0F2xF4_x57;
  UINT32                CoreDisMask;
  AMD_CONFIG_PARAMS     *StdHeader;
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitPcieCoreUsageCZ Enter\n");
  //
  // Initial asusmption that no wrapper/cores are booting used
  //
  CoreDisMask = 0x3;

  EngineList = PcieConfigGetChildEngine (GnbHandle);
  while (EngineList != NULL) {
    if (PcieConfigIsPcieEngine (EngineList)) {
      if (PcieConfigCheckPortStatus (EngineList, INIT_STATUS_PCIE_TRAINING_SUCCESS) ||
        ((EngineList->Type.Port.PortData.LinkHotplug != HotplugDisabled) && (EngineList->Type.Port.PortData.LinkHotplug != HotplugInboard))) {
          //Wrap ID correspoing to bit in D0F2xF4_x57
        CoreDisMask &= (~(1 << PcieConfigGetParentWrapper (EngineList)->WrapId));
      }
    }
    EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetNextTopologyDescriptor (EngineList, DESCRIPTOR_TERMINATE_GNB);
  }
  StdHeader = PcieConfigGetStdHeader (GnbHandle);
  GnbRegisterReadCZ (GnbHandle, D0F2xF4_x57_TYPE, D0F2xF4_x57_ADDRESS, &D0F2xF4_x57.Value, 0, StdHeader);
  D0F2xF4_x57.Value = (D0F2xF4_x57.Value & (~0x3)) | CoreDisMask;
  GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x57_TYPE, D0F2xF4_x57_ADDRESS, &D0F2xF4_x57.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitPcieCoreUsageCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to for each PCIe port
 *
 *
 *
 *
 * @param[in]       CoreId        CoreId
 *
 */

UINT8
STATIC
GnbIommuCoreIdToL1SelCZ (
  IN       UINT8                 CoreId
  )
{
  UINT8 Sel;
  Sel = 0;
  switch (CoreId) {
  // GPP
  case 0x0:
    Sel = L1_SEL_PPx40;
    break;
  // GFX
  case 0x1:
    Sel = L1_SEL_PPx41;
    break;

  default:
    ASSERT (FALSE);
  }
  return Sel;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to for each PCIe port
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
GnbIommuMidInitOnPortCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  GNB_TOPOLOGY_INFO       TopologyInfo;
  GNB_HANDLE              *GnbHandle;
  D0F2xFC_x07_L1_STRUCT   D0F2xFC_x07_L1;
  D0F2xFC_x0D_L1_STRUCT   D0F2xFC_x0D_L1;

  TopologyInfo.PhantomFunction = FALSE;
  TopologyInfo.PcieToPciexBridge = FALSE;
  GnbHandle = (GNB_HANDLE *) PcieConfigGetParentSilicon (Engine);
  if (Engine->Type.Port.PortData.LinkHotplug != HotplugDisabled) {
    TopologyInfo.PhantomFunction = TRUE;
    TopologyInfo.PcieToPciexBridge = TRUE;
  } else {
    if (PcieConfigIsSbPcieEngine (Engine)) {
      PCI_ADDR  StartSbPcieDev;
      PCI_ADDR  EndSbPcieDev;
      StartSbPcieDev.AddressValue = MAKE_SBDFO (0, 0, 0x15, 0, 0);
      EndSbPcieDev.AddressValue = MAKE_SBDFO (0, 0, 0x15, 7, 0);
      GnbGetTopologyInfo (StartSbPcieDev, EndSbPcieDev, &TopologyInfo, GnbLibGetHeader (Pcie));
    } else {
      GnbGetTopologyInfo (Engine->Type.Port.Address, Engine->Type.Port.Address, &TopologyInfo, GnbLibGetHeader (Pcie));
    }
  }
  if (TopologyInfo.PhantomFunction) {
    GnbRegisterReadCZ (
      GnbHandle,
      D0F2xFC_x07_L1_TYPE,
      D0F2xFC_x07_L1_ADDRESS (GnbIommuCoreIdToL1SelCZ (Engine->Type.Port.CoreId)),
      &D0F2xFC_x07_L1.Value,
      0,
      GnbLibGetHeader (Pcie)
      );
    D0F2xFC_x07_L1.Value |= BIT0;
    GnbRegisterWriteCZ (
      GnbHandle,
      D0F2xFC_x07_L1_TYPE,
      D0F2xFC_x07_L1_ADDRESS (GnbIommuCoreIdToL1SelCZ (Engine->Type.Port.CoreId)),
      &D0F2xFC_x07_L1.Value,
      GNB_REG_ACC_FLAG_S3SAVE,
      GnbLibGetHeader (Pcie)
      );
  }
  if (TopologyInfo.PcieToPciexBridge) {
    GnbRegisterReadCZ (
      GnbHandle,
      D0F2xFC_x0D_L1_TYPE,
      D0F2xFC_x0D_L1_ADDRESS (GnbIommuCoreIdToL1SelCZ (Engine->Type.Port.CoreId)),
      &D0F2xFC_x0D_L1.Value,
      0,
      GnbLibGetHeader (Pcie)
      );
    D0F2xFC_x0D_L1.Field.VOQPortBits = 0x7;
    GnbRegisterWriteCZ (
      GnbHandle,
      D0F2xFC_x0D_L1_TYPE,
      D0F2xFC_x0D_L1_ADDRESS (GnbIommuCoreIdToL1SelCZ (Engine->Type.Port.CoreId)),
      &D0F2xFC_x0D_L1.Value,
      GNB_REG_ACC_FLAG_S3SAVE,
      GnbLibGetHeader (Pcie)
      );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * IOMMU Mid Init
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
STATIC
GnbIommuMidInitCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS          Status;
  PCIe_PLATFORM_CONFIG  *Pcie;
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitCZ Enter\n");
  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  if (Status == AGESA_SUCCESS) {
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
      GnbIommuMidInitOnPortCallbackCZ,
      NULL,
      Pcie
      );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitCZ Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Mid Post Init
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
GnbMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS      Status;
  UINT32            Property;
  AGESA_STATUS      AgesaStatus;
  GNB_HANDLE        *GnbHandle;
  GNB_BUILD_OPTIONS_CZ      *GnbBuildOptionData;

  AgesaStatus = AGESA_SUCCESS;
  AGESA_TESTPOINT (TpGnbMidInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbMidInterfaceCZ Enter\n");

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  Status = GnbIommuMidInitCZ (StdHeader);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  Property = TABLE_PROPERTY_DEFAULT;
  Property |= GnbBuildOptionData->GnbCommonOptions.CfgOrbClockGatingEnable ? TABLE_PROPERTY_ORB_CLK_GATING : 0;
  Property |= GnbBuildOptionData->GnbCommonOptions.CfgIocLclkClockGatingEnable ? TABLE_PROPERTY_IOC_LCLK_CLOCK_GATING : 0;
  Property |= GnbBuildOptionData->CfgSpgClockGatingEnable ? TABLE_PROPERTY_SPG_CLOCK_GATING : 0;
  Property |= GnbBuildOptionData->CfgAcgAzClockGatingEnable ? TABLE_PROPERTY_ACG_AZ_CLOCK_GATING : 0;

  GnbHandle = GnbGetHandle (StdHeader);
  if (GnbFmCheckIommuPresent (GnbHandle, StdHeader)) {
    Status = GnbEnableIommuMmio (GnbHandle, StdHeader);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    if (Status == AGESA_SUCCESS) {
      GnbIommuMidInitProgramMmRegCZ (GnbHandle, StdHeader);
    }
    GnbIommuMidInitPcieCoreUsageCZ (GnbHandle);
  }

  Status = GnbProcessTable (
             GnbHandle,
             GnbMidInitTableCZ,
             Property,
             GNB_TABLE_FLAGS_FORCE_S3_SAVE,
             StdHeader
             );
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  Status = GnbOrbMidMemoryPowerGating (StdHeader);
  Status = GnbSPGACGAZMidMemoryPowerGating (StdHeader);

  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbMidInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpGnbMidInterfaceCZExit, NULL);
  return  AgesaStatus;
}

