/**
 * @file
 *
 * PCIe link ASPM Black List
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
#include  <Filecode.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/PcieMiscCommLib.h>

#define FILECODE LIBRARY_PCIEMISCCOMMLIB_PCIEASPMBLACKLISTLIB_FILECODE
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

typedef struct {
  GNB_PCI_SCAN_DATA       ScanData;
  UINT16                  Aspm;
  PCI_ADDR                UpstreamPort;
  PCI_ADDR                DownstreamPort;
  BOOLEAN                 AspmBlackList;
} PCIE_ASPM_BLACK_LIST_DATA;

UINT16  AspmBrDeviceTable[] = {
 0x1002, 0x9441, (UINT16) ~(AspmL1 | AspmL0s),
 0x10B5, 0xFFFF, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0402, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0193, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0422, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0292, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x00F9, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0141, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0092, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D0, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D1, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D2, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D3, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D5, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D7, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01D8, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01DC, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01DE, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x01DF, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x016A, (UINT16) ~(AspmL1 | AspmL0s),
 0x10DE, 0x0392, (UINT16) ~(AspmL1 | AspmL0s),
 0x8086, 0x10D3, (UINT16) ~(AspmL1 | AspmL0s),
 0x8086, 0x0953, (UINT16) ~(AspmL1 | AspmL0s),
 0x1B4B, 0x91A3, (UINT16) ~(AspmL0s),
 0x1B4B, 0x9123, (UINT16) ~(AspmL0s),
 0x1969, 0x1083, (UINT16) ~(AspmL0s),
 0x1033, 0x0194, (UINT16) ~(AspmL0s),
 0x1180, 0xE832, (UINT16) ~(AspmL0s),
 0x1180, 0xE823, (UINT16) ~(AspmL0s)
};

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie ASPM Black List
 *
 *
 *
 * @param[in] LinkAspm            PCie ASPM black list
 * @param[in] StdHeader           Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
PcieAspmBlackListFeature (
  IN       PCIe_LINK_ASPM         *LinkAspm,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32  UpstreamDeviceId;
  UINT32  DownstreamDeviceId;
  UINTN   i;
  UINT32  DeviceId;
  UINT32  VendorId;

  GnbLibPciRead (LinkAspm->UpstreamPort.AddressValue, AccessWidth32, &UpstreamDeviceId, StdHeader);
  GnbLibPciRead (LinkAspm->DownstreamPort.AddressValue, AccessWidth32, &DownstreamDeviceId, StdHeader);
  LinkAspm->BlackList = FALSE;
  for (i = 0; i < (sizeof (AspmBrDeviceTable) / sizeof (UINT16)); i = i + 3) {
    VendorId = AspmBrDeviceTable[i];
    DeviceId = AspmBrDeviceTable[i + 1];
    if (VendorId == (UINT16)UpstreamDeviceId || VendorId == (UINT16)DownstreamDeviceId ) {
      if (DeviceId == 0xFFFF || DeviceId == (UpstreamDeviceId >> 16) || DeviceId == (DownstreamDeviceId >> 16)) {
        LinkAspm->UpstreamAspm &= AspmBrDeviceTable[i + 2];
        LinkAspm->DownstreamAspm &= AspmBrDeviceTable[i + 2];
        LinkAspm->BlackList = TRUE;
      }
    }
  }

  if (UpstreamDeviceId == 0x10831969) {
    GnbLibPciRMW (LinkAspm->UpstreamPort.AddressValue | 0x12F8, AccessS3SaveWidth32, 0xFFF7F7FF, 0, StdHeader);
  }

  if ((UpstreamDeviceId == 0x163914E4) && (LinkAspm->RequestedAspm & AspmL1)) {
    //Workaround for 5709C ASPM L1 Issue
    // Vendor ID: 0x14E4, Device ID: 0x1639
    //PCIE_LC_TRAINING_CNTL.LC_ASPM_L1_NAK_TIMER_SEL = 0x1
    GnbLibPciIndirectRMW (LinkAspm->DownstreamPort.AddressValue | 0xE0, 0xA1, AccessS3SaveWidth32, 0xFF3FFFFF, 0x400000, StdHeader);
  }

  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * ASPM Black List
 *
 *
 *
 * @param[in] Device                   PCI_ADDR of PCIe Device to evaluate
 * @param[in] PcieAspmBlackListData    Pointer to PCIE_ASPM_BLACK_LIST_DATA
 * @param[in] StdHeader                Standard configuration header
 * @retval    AGESA_STATUS
 */
AGESA_STATUS
CheckPcieAspmBlackList (
  IN       PCIE_ASPM_BLACK_LIST_DATA  *PcieAspmBlackListData,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  UINT32  UpstreamDeviceId;
  UINT32  DownstreamDeviceId;
  UINTN   i;
  UINT32  DeviceId;
  UINT32  VendorId;
  GnbLibPciRead (PcieAspmBlackListData->UpstreamPort.AddressValue, AccessWidth32, &UpstreamDeviceId, StdHeader);
  GnbLibPciRead (PcieAspmBlackListData->DownstreamPort.AddressValue, AccessWidth32, &DownstreamDeviceId, StdHeader);
  for (i = 0; i < (sizeof (AspmBrDeviceTable) / sizeof (UINT16)); i = i + 4) {
    VendorId = AspmBrDeviceTable[i];
    DeviceId = AspmBrDeviceTable[i + 1];
    if (VendorId == 0xFFFF) {
      break;
    }
    if ((VendorId == (UINT16)UpstreamDeviceId) || (VendorId == (UINT16)DownstreamDeviceId)) {
      if (DeviceId == 0xFFFF || DeviceId == (UpstreamDeviceId >> 16) || DeviceId == (DownstreamDeviceId >> 16)) {
        PcieAspmBlackListData->Aspm = AspmBrDeviceTable[i + 2];
        PcieAspmBlackListData->AspmBlackList = TRUE;
        IDS_HDT_CONSOLE (GNB_TRACE, "  ASPM Black List: US_DID=0x%x DS_DID=0x%x PM_SUPPORT=0x%x \n", UpstreamDeviceId, DownstreamDeviceId, PcieAspmBlackListData->Aspm);
      }
    }
  }
  return AGESA_SUCCESS;
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
PcieAspmBlackListCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS                ScanStatus;
  PCIE_ASPM_BLACK_LIST_DATA  *PcieAspmBlackListData;
  PCIE_DEVICE_TYPE           DeviceType;
  ScanStatus = SCAN_SUCCESS;
  PcieAspmBlackListData = (PCIE_ASPM_BLACK_LIST_DATA*) ScanData;
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    PcieAspmBlackListData->DownstreamPort = Device;
    GnbLibPciScanSecondaryBus (Device, &PcieAspmBlackListData->ScanData);
    break;
  case  PcieDeviceUpstreamPort:
    PcieAspmBlackListData->UpstreamPort = Device;
    CheckPcieAspmBlackList (PcieAspmBlackListData, NULL);
    GnbLibPciScanSecondaryBus (Device, &PcieAspmBlackListData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    PcieAspmBlackListData->UpstreamPort = Device;
    CheckPcieAspmBlackList (PcieAspmBlackListData, NULL);
    ScanStatus = SCAN_SKIP_FUNCTIONS;
    break;
  default:
    break;
  }
  return ScanStatus;
}
/*----------------------------------------------------------------------------------------*/
/**
 * Callback to Disable ASPM Capability
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 */
UINT16
PcieDisableASPMCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine
  )
{
  PCIE_ASPM_BLACK_LIST_DATA PcieAspmBlackListData;
  UINT16  AspmValue;
  AspmValue = 0xFFFF;
  PcieAspmBlackListData.Aspm = 0xFFFF;
  PcieAspmBlackListData.AspmBlackList = FALSE;
  PcieAspmBlackListData.ScanData.StdHeader = NULL;
  PcieAspmBlackListData.ScanData.GnbScanCallback = PcieAspmBlackListCallback;
  GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieAspmBlackListData.ScanData);
  if (PcieAspmBlackListData.AspmBlackList) {
    AspmValue = PcieAspmBlackListData.Aspm;
  }
  return AspmValue;
}
