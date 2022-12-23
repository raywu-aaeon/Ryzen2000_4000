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
#include  <Library/BaseLib.h>
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieInitLib.h"
#include  "GnbNbInitLib.h"
#include  "GnbRegistersCommonV2.h"
#include  "GnbFuseTable.h"
#include  "OptionGnb.h"
#include  "GnbFamServices.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBNBINITLIB_GNBNBINITLIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define SMC_RAM_START_ADDR 0x10000ul

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

typedef struct {
  GNB_PCI_SCAN_DATA     ScanData;
  GNB_TOPOLOGY_INFO     *TopologyInfo;
} GNB_TOPOLOGY_INFO_DATA;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Check a PCIE device to see if it supports phantom functions
 *
 * @param[in] Device      Device pci address
 * @param[in] StdHeader   Standard configuration header
 * @return    TRUE        Current device supports phantom functions
 */
BOOLEAN
GnbCheckPhantomFuncSupport (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8   PcieCapPtr;
  UINT32  Value;
  Value = 0;

  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (Device.AddressValue | (PcieCapPtr + 4), AccessWidth32, &Value, StdHeader);
  }
  return ((Value & (BIT3 | BIT4)) != 0) ? TRUE : FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Evaluate device
 *
 *
 *
 * @param[in]     Device          PCI Address
 * @param[in,out] ScanData        Scan configuration data
 * @retval                        Scan Status
 */

SCAN_STATUS
STATIC
GnbTopologyInfoScanCallback (
  IN       PCI_ADDR                 Device,
  IN OUT   GNB_PCI_SCAN_DATA        *ScanData
  )
{
  SCAN_STATUS             ScanStatus;
  GNB_TOPOLOGY_INFO_DATA  *GnbTopologyInfo;
  PCIE_DEVICE_TYPE        DeviceType;
  ScanStatus = SCAN_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "  GnbIommuInfoScanCallback for Device = %d:%d:%d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function
    );
  GnbTopologyInfo = (GNB_TOPOLOGY_INFO_DATA *)ScanData;
  ScanStatus = SCAN_SUCCESS;
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    GnbLibPciScanSecondaryBus (Device, &GnbTopologyInfo->ScanData);
    break;
  case  PcieDeviceUpstreamPort:
    GnbLibPciScanSecondaryBus (Device, &GnbTopologyInfo->ScanData);
    ScanStatus = SCAN_SKIP_FUNCTIONS | SCAN_SKIP_DEVICES | SCAN_SKIP_BUSES;
    break;
  case  PcieDevicePcieToPcix:
    GnbTopologyInfo->TopologyInfo->PcieToPciexBridge = TRUE;
    ScanStatus = SCAN_SKIP_FUNCTIONS | SCAN_SKIP_DEVICES | SCAN_SKIP_BUSES;
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    if (GnbCheckPhantomFuncSupport (Device, ScanData->StdHeader)) {
      GnbTopologyInfo->TopologyInfo->PhantomFunction = TRUE;
    }
    ScanStatus = SCAN_SKIP_DEVICES | SCAN_SKIP_BUSES;
    break;
  default:
    break;
  }
  return ScanStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get IOMMU topology info
 *
 *
 *
 * @param[in] StartPciAddress   Start PCI address
 * @param[in] EndPciAddress     End PCI address
 * @param[in] TopologyInfo      Topology info structure
 * @param[in] StdHeader         Standard Configuration Header
 */

AGESA_STATUS
GnbGetTopologyInfo (
  IN       PCI_ADDR                  StartPciAddress,
  IN       PCI_ADDR                  EndPciAddress,
     OUT   GNB_TOPOLOGY_INFO         *TopologyInfo,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  GNB_TOPOLOGY_INFO_DATA  GnbTopologyInfo;
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbGetTopologyInfo Enter\n");
  GnbTopologyInfo.ScanData.GnbScanCallback = GnbTopologyInfoScanCallback;
  GnbTopologyInfo.ScanData.StdHeader = StdHeader;
  GnbTopologyInfo.TopologyInfo = TopologyInfo;
  GnbLibPciScan (StartPciAddress, EndPciAddress, &GnbTopologyInfo.ScanData);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbGetTopologyInfo Exit\n");
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get IOMMU PCI address
 *
 *
 * @param[in]  GnbHandle       GNB handle
 * @param[in]  StdHeader       Standard configuration header
 */

PCI_ADDR
GnbGetIommuPciAddress (
  IN       GNB_HANDLE               *GnbHandle,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  PCI_ADDR  GnbIommuPciAddress;
  GnbIommuPciAddress = GnbGetHostPciAddress (GnbHandle);
  GnbIommuPciAddress.Address.Function = 0x2;
  return  GnbIommuPciAddress;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enable IOMMU base address. (MMIO space )
 *
 *
 * @param[in]     GnbHandle       GNB handle
 * @param[in]     StdHeader       Standard Configuration Header
 * @retval        AGESA_SUCCESS
 * @retval        AGESA_ERROR
 */

AGESA_STATUS
GnbEnableIommuMmio (
  IN       GNB_HANDLE           *GnbHandle,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  AGESA_STATUS            Status;
  UINT16                  CapabilityOffset;
  UINT64                  BaseAddress;
  UINT32                  Value;
  PCI_ADDR                GnbIommuPciAddress;

  Status = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEnableIommuMmio Enter\n");

  if (GnbFmCheckIommuPresent (GnbHandle, StdHeader)) {
    GnbIommuPciAddress = GnbGetIommuPciAddress (GnbHandle, StdHeader);
    CapabilityOffset = GnbLibFindPciCapability (GnbIommuPciAddress.AddressValue, IOMMU_CAP_ID, StdHeader);

    GnbLibPciRead (GnbIommuPciAddress.AddressValue | (CapabilityOffset + 0x8), AccessWidth32, &Value, StdHeader);
    BaseAddress = (UINT64) Value << 32;
    GnbLibPciRead (GnbIommuPciAddress.AddressValue | (CapabilityOffset + 0x4), AccessWidth32, &Value, StdHeader);
    BaseAddress |= Value;

    if ((BaseAddress & 0xfffffffffffffffe) != 0x0) {
      IDS_HDT_CONSOLE (GNB_TRACE, "  Enable IOMMU MMIO at address %x for Socket %d Silicon %d\n", BaseAddress, GnbGetSocketId (GnbHandle) , GnbGetSiliconId (GnbHandle));
      GnbLibPciRMW (GnbIommuPciAddress.AddressValue | (CapabilityOffset + 0x8), AccessS3SaveWidth32, 0xFFFFFFFF, 0x0, StdHeader);
      GnbLibPciRMW (GnbIommuPciAddress.AddressValue | (CapabilityOffset + 0x4), AccessS3SaveWidth32, 0xFFFFFFFE, 0x1, StdHeader);
    } else {
      ASSERT (FALSE);
      Status = AGESA_ERROR;
    }
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEnableIommuMmio Exit\n");
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init NB set top of memory
 *
 *
 *
 * @param[in] NbPciAddress    Gnb PCI address
 * @param[in] StdHeader       Standard Configuration Header
 */

AGESA_STATUS
GnbSetTom (
  IN      PCI_ADDR            NbPciAddress,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  AGESA_STATUS  Status;
  UINT64        MsrData;
  UINT64        GnbTom2;
  UINT64        GnbTom3;
  UINT32        Value;

  Status = AGESA_SUCCESS;
  //Read memory size below 4G from MSR C001_001A
  MsrData = AsmReadMsr64 (TOP_MEM);
  //Write to NB register 0x90
  Value = (UINT32)MsrData & 0xFF800000;     //Keep bits 31:23
  GnbLibPciRMW (
    NbPciAddress.AddressValue | D0F0x90_ADDRESS,
    AccessS3SaveWidth32,
    0x007FFFFF,
    Value,
    StdHeader
    );
  if (Value == 0) {
    Status = AGESA_WARNING;
  }

  GnbTom2 = 0;
  GnbTom3 = 0;
  MsrData = AsmReadMsr64 (SYS_CFG);
  if ((MsrData & BIT21) != 0) {
    //If SYS_CFG(MtrrTom2En) then configure GNB TOM2 and TOM3
    //Read memory size above 4G from TOP_MEM2 (MSR C001_001D)
    MsrData = AsmReadMsr64 (TOP_MEM2);
    if ((MsrData & (UINT64)0x0000FFFFFFC00000) > ((UINT64)0x0000010000000000)) {
      // If TOP_MEM2 is above 1TB, enable GNB TOM2 and TOM3
      // Set TOM2 for below 1TB limit
      GnbTom2 = 0x000000FD00000000;
      // TOM3 is INCLUSIVE, so set it to TOM - 1 using bits 47:22
      GnbTom3 = (MsrData - 1) & (UINT64)0x0000FFFFFFC00000;
    } else {
      // If TOP_MEM2 is below 1TB, set TOM2 using bits 39:22
      GnbTom2 = MsrData & (UINT64)0x000000FFFFC00000;       //Keep bits 39:22
      // If TOP_MEM2 is below 1TB, disable GNB TOM3
      GnbTom3 = 0;
    }
  }

  if (GnbTom2 != 0) {
    // Write memory size[39:32] to indirect register 1A[7:0]
    Value = (UINT32) ((GnbTom2 >> 32) & 0xFF);
    GnbLibPciIndirectRMW (
      NbPciAddress.AddressValue | D0F0x60_ADDRESS,
      D0F0x64_x1A_ADDRESS,
      AccessS3SaveWidth32,
      0xFFFFFF00,
      Value,
      StdHeader
    );
    // Write memory size[31:23] to indirect register 19[31:23] and enable memory through bit 0
    Value = (UINT32)GnbTom2 & 0xFF800000;      //Keep bits 31:23
    Value |= BIT0;                            // Enable top of memory
    GnbLibPciIndirectRMW (
      NbPciAddress.AddressValue | D0F0x60_ADDRESS,
      D0F0x64_x19_ADDRESS,
      AccessS3SaveWidth32,
      0x007FFFFF,
      Value,
      StdHeader
    );
  }

  if (GnbTom3 != 0) {
    // Above 1TB addressing TOM3 if MSR TOM is above 1TB
    // Write memory size[51:22] to indirect register 4E[29:0] and enable memory through bit 31
    Value = (UINT32) (GnbTom3 >> 22);
    Value |= BIT31;
    GnbLibPciIndirectRMW (
      NbPciAddress.AddressValue | D0F0x60_ADDRESS,
      D0F0x64_x4E_ADDRESS,
      AccessS3SaveWidth32,
      0xBFFFFFFF,
      Value,
      StdHeader
    );
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get the index of highest SCLK VID
 *
 * @param[in] StdHeader       Standard configuration header
 * @retval                    NBVDD VID index
 */
UINT8
GnbLocateHighestVidIndex (
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT8             MaxVid;
  UINT8             MaxVidIndex;
  UINTN             Index;
  PP_FUSE_ARRAY_V2     *PpFuseArray;

  PpFuseArray = (PP_FUSE_ARRAY_V2 *) GnbLocateHeapBuffer (AMD_PP_FUSE_TABLE_HANDLE, StdHeader);
  ASSERT (PpFuseArray != NULL);
  if (PpFuseArray == NULL) {
    IDS_HDT_CONSOLE (GNB_TRACE, "  ERROR!!! Heap Location\n");
    return 0;
  }

  MaxVidIndex = 0;
  MaxVid = 0xff;
  for (Index = 0; Index < (sizeof (PpFuseArray->VddNbVid) / sizeof (PpFuseArray->VddNbVid[0])); Index++) {
    if (PpFuseArray->VddNbVid[Index] != 0 && PpFuseArray->VddNbVid[Index] < MaxVid) {
      MaxVid = PpFuseArray->VddNbVid[Index];
      MaxVidIndex = (UINT8) Index;
    }
  }
  ASSERT (PpFuseArray->VddNbVid[MaxVidIndex] != 0);
  return MaxVidIndex;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Translate VID code to millivolt with two fraction bits
 *
 *
 * @param[in] Vid             VID code
 * @param[in] StdHeader       Standard configuration header
 * @retval    100 millivolt with two fraction bits
 */

UINT32
GnbTranslateVidCodeToMillivolt (
  IN       UINT8                 Vid,
  IN       AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT32       Millivolt;

  // According to SVI2 spec, Vid Code 0xF7 is 6.25mv. 6.25mv is one boundary value.
  if (Vid > 0xF7) {
    Vid = 0xF7;
    ASSERT (FALSE);
  }

  // Equation: VID code increase/decrease 1, there is one 6.25mv change.
  //           6.25mv could be described using integer 625 with two fraction bits.
  Millivolt = (0xF7 - Vid + 1) * 625;

  return Millivolt;
}

/*----------------------------------------------------------------------------------------*/
/**
 * NB Dynamic Wake
 * ORB_CNB_Wake signal is used to inform the CNB NCLK controller and GNB LCLK controller
 *   that ORB is (or will soon) push data into the synchronizer FIFO (i.e. wake is high).
 *
 * @param[in] NbPciAddress    Gnb PCI address
 * @param[in] StdHeader       Standard Configuration Header
 */

VOID
GnbOrbDynamicWake (
  IN      PCI_ADDR            NbPciAddress,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{

  D0F0x98_x2C_STRUCT D0F0x98_x2C;
  GNB_BUILD_OPTIONS_COMMON  *GnbCommonOptions;

  GnbLibPciIndirectRead (
    NbPciAddress.AddressValue | D0F0x94_ADDRESS,
    D0F0x98_x2C_ADDRESS,
    AccessWidth32,
    &D0F0x98_x2C.Value,
    StdHeader
    );

  // Enable Dynamic wake
  // Wake Hysteresis timer value.  Specifies the number of SMU pulses to count.
  GnbCommonOptions = (GNB_BUILD_OPTIONS_COMMON*) GnbFmGnbBuildOptions (StdHeader);
  if (GnbCommonOptions->CfgOrbDynWakeEnable) {
    D0F0x98_x2C.Field.DynWakeEn = 1;
  } else {
    D0F0x98_x2C.Field.DynWakeEn = 0;
  }
  D0F0x98_x2C.Field.WakeHysteresis = 0x19;

  IDS_OPTION_HOOK (IDS_GNB_ORBDYNAMIC_WAKE, &D0F0x98_x2C, StdHeader);

  GnbLibPciIndirectWrite (
    NbPciAddress.AddressValue | D0F0x94_ADDRESS,
    D0F0x98_x2C_ADDRESS,
    AccessS3SaveWidth32,
    &D0F0x98_x2C.Value,
    StdHeader
    );
}
/*----------------------------------------------------------------------------------------*/
/**
 * Config GNB to prevent LPC deadlock scenario
 *
 *
 * @param[in]  GnbHandle       GNB handle
 * @param[in]  StdHeader       Standard configuration header
 */

VOID
GnbLpcDmaDeadlockPrevention (
  IN       GNB_HANDLE               *GnbHandle,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  PCIe_PLATFORM_CONFIG  *Pcie;
  PCIe_ENGINE_CONFIG    *EngineList;

  Pcie = (PCIe_PLATFORM_CONFIG *) PcieConfigGetParent (DESCRIPTOR_PLATFORM, &GnbHandle->Header);
  EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetChild (DESCRIPTOR_ALL_ENGINES, &GnbHandle->Header);
  while (EngineList != NULL) {
    if (PcieConfigIsPcieEngine (EngineList) && PcieConfigIsSbPcieEngine (EngineList)) {
      PcieRegisterRMW (
        PcieConfigGetParentWrapper (EngineList),
        CORE_SPACE (EngineList->Type.Port.CoreId, D0F0xE4_CORE_0010_ADDRESS),
        D0F0xE4_CORE_0010_UmiNpMemWrite_MASK,
        1 << D0F0xE4_CORE_0010_UmiNpMemWrite_OFFSET,
        TRUE,
        Pcie
        );
      //Enable special NP memory write protocol in ORB
      GnbLibPciIndirectRMW (
        GnbHandle->Address.AddressValue | D0F0x94_ADDRESS,
        D0F0x98_x06_ADDRESS,
        AccessS3SaveWidth32,
        0xFFFFFFFF,
        1 << D0F0x98_x06_UmiNpMemWrEn_OFFSET,
        StdHeader
        );
      break;
    }
    EngineList = (PCIe_ENGINE_CONFIG *) PcieConfigGetNextTopologyDescriptor (EngineList, DESCRIPTOR_TERMINATE_GNB);
  }
}

