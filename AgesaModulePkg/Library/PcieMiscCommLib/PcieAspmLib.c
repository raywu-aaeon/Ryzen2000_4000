/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe link ASPM
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
#include  <GnbDxio.h>
#include  <OptionGnb.h>
#include  <Filecode.h>
#include  <Library/IdsLib.h>
#include  <Library/GnbPcieConfigLib.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/PcieMiscCommLib.h>
#include  <Library/PcdLib.h>

#define FILECODE LIBRARY_PCIEMISCCOMMLIB_PCIEASPMLIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

typedef struct {
  GNB_PCI_SCAN_DATA       ScanData;
  PCIE_ASPM_TYPE          Aspm;
  PCI_ADDR                DownstreamPort;
  BOOLEAN                 AspmL0sBlackList;
} PCIE_ASPM_DATA;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

SCAN_STATUS
PcieAspmCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  );

VOID
PcieAspmEnableOnLink (
  IN       PCI_ADDR                 Downstream,
  IN       PCI_ADDR                 Upstream,
  IN       PCIE_ASPM_TYPE           Aspm,
  IN OUT   BOOLEAN                  *AspmL0sBlackList,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

VOID
PcieAspmEnableOnDevice (
  IN       PCI_ADDR             Device,
  IN       PCIE_ASPM_TYPE       Aspm,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  );

PCIE_ASPM_TYPE
PcieAspmGetPmCapability (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

BOOLEAN
STATIC
PcieAspmOptionalCompliance (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Enable PCIE Advance state power management
 *
 *
 *
 * @param[in] DownstreamPort      PCI Address of the downstream port
 * @param[in] Aspm                ASPM type
 * @param[in] StdHeader           Standard configuration header
 * @retval     AGESA_STATUS
 */

VOID
PcieLinkAspmEnable (
  IN       PCI_ADDR                DownstreamPort,
  IN       PCIE_ASPM_TYPE          Aspm,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  PCIE_ASPM_DATA PcieAspmData;
  PcieAspmData.Aspm = Aspm;
  PcieAspmData.ScanData.StdHeader = StdHeader;
  PcieAspmData.ScanData.GnbScanCallback = PcieAspmCallback;
  PcieAspmData.AspmL0sBlackList = FALSE;
  GnbLibPciScan (DownstreamPort, DownstreamPort, &PcieAspmData.ScanData);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Evaluate device
 *
 *
 *
 * @param[in]     Device          PCI Address
 * @param[in,out] ScanData        Scan configuration data
 * @retval                        Scan Status of 0
 */

SCAN_STATUS
PcieAspmCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS             ScanStatus;
  PCIE_ASPM_DATA          *PcieAspmData;
  PCIE_DEVICE_TYPE        DeviceType;
  ScanStatus = SCAN_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieAspmCallback for Device = %d:%d:%d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function
    );
  PcieAspmData = (PCIE_ASPM_DATA *) ScanData;
  ScanStatus = SCAN_SUCCESS;
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    PcieAspmData->DownstreamPort = Device;
    GnbLibPciScanSecondaryBus (Device, &PcieAspmData->ScanData);

    //Pcie ASPM Black List for L0s with HW method change
    if ((DeviceType == PcieDeviceRootComplex) && (PcieAspmData->AspmL0sBlackList == TRUE)) {
      IDS_HDT_CONSOLE (GNB_TRACE, "  Black List L0s disabled = %d:%d:%d\n", Device.Address.Bus, Device.Address.Device, Device.Address.Function);
      GnbLibPciIndirectRMW (Device.AddressValue | 0xE0, 0xA0, AccessS3SaveWidth32, 0xfffff0ff, 0, ScanData->StdHeader);
    }
    break;
  case  PcieDeviceUpstreamPort:
    PcieAspmEnableOnLink (
      PcieAspmData->DownstreamPort,
      Device,
      PcieAspmData->Aspm,
      &PcieAspmData->AspmL0sBlackList,
      ScanData->StdHeader
      );
    GnbLibPciScanSecondaryBus (Device, &PcieAspmData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    PcieAspmEnableOnLink (
      PcieAspmData->DownstreamPort,
      Device,
      PcieAspmData->Aspm,
      &PcieAspmData->AspmL0sBlackList,
      ScanData->StdHeader
      );
    break;
  default:
    break;
  }
  return ScanStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set  ASPM State on PCIe device function
 *
 *
 *
 * @param[in] Function    PCI address of function.
 * @param[in] Aspm                Aspm capability to enable
 * @param[in] StdHeader           Standard configuration header
 *
 */
 /*----------------------------------------------------------------------------------------*/

VOID
PcieAspmEnableOnFunction (
  IN       PCI_ADDR             Function,
  IN       PCIE_ASPM_TYPE       Aspm,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8       PcieCapPtr;
  PcieCapPtr = GnbLibFindPciCapability (Function.AddressValue, PCIE_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRMW (
      Function.AddressValue | (PcieCapPtr + PCIE_LINK_CTRL_REGISTER) ,
      AccessS3SaveWidth8,
      ~(UINT32) (BIT0 | BIT1),
      Aspm,
      StdHeader
      );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set ASPM State on all function of PCI device
 *
 *
 *
 * @param[in] Device    PCI address of device.
 * @param[in] Aspm                Aspm capability to enable
 * @param[in] StdHeader           Standard configuration header
 *
 */
 /*----------------------------------------------------------------------------------------*/

VOID
PcieAspmEnableOnDevice (
  IN       PCI_ADDR             Device,
  IN       PCIE_ASPM_TYPE       Aspm,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8 MaxFunc;
  UINT8 CurrentFunc;
  MaxFunc = GnbLibPciIsMultiFunctionDevice (Device.AddressValue, StdHeader) ? 7 : 0;
  for (CurrentFunc = 0; CurrentFunc <= MaxFunc; CurrentFunc++) {
    Device.Address.Function = CurrentFunc;
    if (GnbLibPciIsDevicePresent (Device.AddressValue, StdHeader)) {
      PcieAspmEnableOnFunction (Device, Aspm, StdHeader);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 *  Enable ASPM on link
 *
 *
 *
 * @param[in]       Downstream          PCI Address of downstrteam port
 * @param[in]       Upstream            PCI Address of upstream port
 * @param[in]       Aspm                Aspm capability to enable
 * @param[in, out]  AspmL0sBlackList    AspmBlackList
 * @param[in]       StdHeader           Standard configuration header
 */

VOID
PcieAspmEnableOnLink (
  IN       PCI_ADDR                 Downstream,
  IN       PCI_ADDR                 Upstream,
  IN       PCIE_ASPM_TYPE           Aspm,
  IN OUT   BOOLEAN                  *AspmL0sBlackList,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  PCIe_LINK_ASPM  LinkAspm;
  PCIE_ASPM_TYPE  DownstreamCap;
  PCIE_ASPM_TYPE  UpstreamCap;
  BOOLEAN         UpstreamOpComp;
  BOOLEAN         AspmBlackListEnable;

  LinkAspm.DownstreamPort = Downstream;
  DownstreamCap = PcieAspmGetPmCapability (Downstream, StdHeader);
  UpstreamOpComp = PcieAspmOptionalCompliance (Upstream, StdHeader);
  LinkAspm.UpstreamPort = Upstream;
  UpstreamCap = PcieAspmGetPmCapability (Upstream, StdHeader);
  LinkAspm.DownstreamAspm = DownstreamCap & UpstreamCap & Aspm;
  LinkAspm.UpstreamAspm = LinkAspm.DownstreamAspm;
  LinkAspm.RequestedAspm = Aspm;
  if (!UpstreamOpComp) {
    LinkAspm.UpstreamAspm &= AspmL1;
    if ((UpstreamCap & Aspm & AspmL0s) != 0) {
      LinkAspm.UpstreamAspm |= AspmL0s;
    }
    LinkAspm.DownstreamAspm &= AspmL1;
    if ((DownstreamCap & Aspm & AspmL0s) != 0) {
      LinkAspm.DownstreamAspm |= AspmL0s;
    }
  }

  AspmBlackListEnable = PcdGetBool (PcdCfgPcieAspmBlackListEnableEnable);
  if (AspmBlackListEnable == TRUE) {
    PcieAspmBlackListFeature (&LinkAspm, StdHeader);
    if ((LinkAspm.DownstreamAspm & AspmL0s) == 0) {
      *AspmL0sBlackList = LinkAspm.BlackList;
    }
  }
  //AgesaPcieLinkAspm (&LinkAspm, StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "  Set ASPM [%d]  for Device = %d:%d:%d\n",
    (LinkAspm.UpstreamAspm) ,
    LinkAspm.UpstreamPort.Address.Bus,
    LinkAspm.UpstreamPort.Address.Device,
    LinkAspm.UpstreamPort.Address.Function
    );
  IDS_HDT_CONSOLE (GNB_TRACE, "  Set ASPM [%d]  for Device = %d:%d:%d\n",
    (LinkAspm.DownstreamAspm) ,
    LinkAspm.DownstreamPort.Address.Bus,
    LinkAspm.DownstreamPort.Address.Device,
    LinkAspm.DownstreamPort.Address.Function
    );
  // Disable ASPM  Downstream component
  PcieAspmEnableOnDevice (Upstream, AspmDisabled, StdHeader);
  // Enable  ASPM  Upstream component
  PcieAspmEnableOnFunction (Downstream, LinkAspm.DownstreamAspm, StdHeader);
  // Enable  ASPM  Downstream component
  PcieAspmEnableOnDevice (Upstream, LinkAspm.UpstreamAspm, StdHeader);
}

/**----------------------------------------------------------------------------------------*/
/**
 * Port/Endpoint ASPM capability
 *
 *
 *
 * @param[in] Device      PCI address of downstream port
 * @param[in] StdHeader   Standard configuration header
 *
 * @retval    PCIE_ASPM_TYPE
 */
 /*----------------------------------------------------------------------------------------*/
PCIE_ASPM_TYPE
PcieAspmGetPmCapability (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8   PcieCapPtr;
  UINT32  Value;
  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, StdHeader);
  if (PcieCapPtr == 0) {
    return 0;
  }
  GnbLibPciRead (
    Device.AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER),
    AccessWidth32,
    &Value,
    StdHeader
    );
  return (Value >> 10) & 3;
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
 *
 */

VOID
STATIC
PcieAspmPortInitCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  if (Engine->Type.Port.PortData.LinkAspm != AspmDisabled &&
      !PcieConfigIsSbPcieEngine (Engine) &&
      PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
    PcieLinkAspmEnable (
      Engine->Type.Port.Address,
      Engine->Type.Port.PortData.LinkAspm,
      NULL
      );
  }
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to enable Clock Power Managment
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
PcieAspmInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG             *PcieEngine;
  PCIe_WRAPPER_CONFIG            *PcieWrapper;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmInterface Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        PcieAspmPortInitCallback (PcieEngine, NULL);
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmInterface Exit\n");
}

/**----------------------------------------------------------------------------------------*/
/**
 * Port/Endpoint ASPM optionality compliance
 *
 *
 *
 * @param[in] Device      PCI address of downstream port
 * @param[in] StdHeader   Standard configuration header
 *
 * @retval    BOOLEAN
 */
 /*----------------------------------------------------------------------------------------*/

BOOLEAN
STATIC
PcieAspmOptionalCompliance (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8   PcieCapPtr;
  UINT32  Value;
  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, StdHeader);
  if (PcieCapPtr == 0) {
    return 0;
  }
  GnbLibPciRead (
    Device.AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER),
    AccessWidth32,
    &Value,
    StdHeader
    );
  return (BOOLEAN) ((Value >> 22) & 1);
}

