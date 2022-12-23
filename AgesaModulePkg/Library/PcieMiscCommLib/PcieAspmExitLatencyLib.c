/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to calculate PCIe topology segment maximum exit latency
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
#include  <Library/IdsLib.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/PcieMiscCommLib.h>

#define FILECODE LIBRARY_PCIEMISCCOMMLIB_PCIEASPMEXITLATENCYLIB_FILECODE

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
  PCIe_ASPM_LATENCY_INFO  *AspmLatencyInfo;
  PCI_ADDR                DownstreamPort;
  UINT8                   LinkCount;
} PCIE_EXIT_LATENCY_DATA;

typedef struct {
  GNB_PCI_SCAN_DATA ScanData;
  PCI_ADDR          DownstreamPort;
  UINT16            L1ExitLatency;
  BOOLEAN           BlackList;
} PCIE_L1_EXIT_LATENCY_DATA;
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
UINT16  DeviceTableL1ExitLatency[] = {
 //VID   DID     5 - L1 exit latency 16us~32us
 0x1022, 0x43C6, 5,
 0x1022, 0x43C7, 5,
 0x1022, 0x43C8, 5,
 0x1022, 0x43D0, 5,
 0x1022, 0x43D1, 5,
 0x1022, 0x43D2, 5,
 0x1022, 0x43D3, 5,
 0x1022, 0x43D4, 5,
 0x1022, 0x43D5, 5,
 0x1022, 0x43D6, 5,
 0x1022, 0x43D7, 5,
 0x1022, 0x43D8, 5,
 0x1022, 0x43D9, 5,
 0x1022, 0x43DA, 5,
 0x1022, 0x43DB, 5,
 0x1022, 0x43DC, 5,
 0x1022, 0x43DD, 5,
 0x1022, 0x43DE, 5,
 0x1022, 0x43DF, 5,
 0x1022, 0x43EC, 5,
 0x1022, 0x43EE, 5,
 0x1022, 0x43EF, 5,
};

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie L1ExitLatency Black List
 *
 *
 *
 * @param[in] LinkL1ExitLatency   L1ExitLatency black list
 */

VOID
PcieL1ExitLatencyBlackListFeature (
  IN       PCIE_L1_EXIT_LATENCY_DATA *LinkL1ExitLatency
  )
{
  UINT32  i;
  UINT32  DeviceId;
  UINT32  VendorId;
  UINT32  DownstreamDeviceId;

  GnbLibPciRead (LinkL1ExitLatency->DownstreamPort.AddressValue, AccessWidth32, &DownstreamDeviceId, NULL);
  for (i = 0; i < (sizeof (DeviceTableL1ExitLatency) / sizeof (UINT16)); i = i + 3) {
    VendorId = DeviceTableL1ExitLatency[i];
    DeviceId = DeviceTableL1ExitLatency[i + 1];
    if ((VendorId == (UINT16)DownstreamDeviceId) && (DeviceId == (DownstreamDeviceId >> 16))) {
      LinkL1ExitLatency->BlackList = TRUE;
      LinkL1ExitLatency->L1ExitLatency = DeviceTableL1ExitLatency[i + 2];
      IDS_HDT_CONSOLE (GNB_TRACE, "  - Vid(0x%x) Did(0x%x) L1ExitLatency = %d\n",
        (UINT16)DownstreamDeviceId,
        (UINT16)(DownstreamDeviceId >> 16),
        LinkL1ExitLatency->L1ExitLatency
        );
      break;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get maximum exit latency for device
 *
 *
 *
 * @param[in]     Device          PCI Address
 * @param[in,out] ScanData        Scan configuration data
 * @retval                        Scan Status of 0
 */

SCAN_STATUS
PcieAspmGetMaxExitLatencyCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  PCIE_EXIT_LATENCY_DATA  *PcieExitLatencyData;
  PCIE_DEVICE_TYPE        DeviceType;
  UINT32                  Value;
  UINT8                   PcieCapPtr;
  UINT8                   L1AcceptableLatency;

  PcieExitLatencyData = (PCIE_EXIT_LATENCY_DATA*) ScanData;
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieAspmGetMaxExitLatencyCallback for Device = %d:%d:%d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function
    );
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    PcieExitLatencyData->DownstreamPort = Device;
    PcieExitLatencyData->LinkCount++;
    GnbLibPciScanSecondaryBus (Device, &PcieExitLatencyData->ScanData);
    PcieExitLatencyData->LinkCount--;
    break;
  case  PcieDeviceUpstreamPort:
    GnbLibPciScanSecondaryBus (Device, &PcieExitLatencyData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, ScanData->StdHeader);
    ASSERT (PcieCapPtr != 0);
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER),
      AccessWidth32,
      &Value,
      ScanData->StdHeader
      );
    if ((Value & PCIE_ASPM_L1_SUPPORT_CAP) != 0) {
      GnbLibPciRead (
        Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER),
        AccessWidth32,
        &Value,
        ScanData->StdHeader
        );
      L1AcceptableLatency = (UINT8) (1 << ((Value >> 9) & 0x7));
      if (PcieExitLatencyData->LinkCount > 1) {
        L1AcceptableLatency = L1AcceptableLatency + PcieExitLatencyData->LinkCount;
      }
      if (PcieExitLatencyData->AspmLatencyInfo->MaxL1ExitLatency <  L1AcceptableLatency) {
        PcieExitLatencyData->AspmLatencyInfo->MaxL1ExitLatency = L1AcceptableLatency;
      }
      IDS_HDT_CONSOLE (PCIE_MISC, "  Device max exit latency  L1 - %d us\n",
        L1AcceptableLatency
        );
    }
    break;
  default:
    break;
  }
  return SCAN_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Determine ASPM L-state maximum exit latency for PCIe segment
 *
 *  Scan through all link in segment to determine maxim exit latency requirement by EPs.
 *
 * @param[in]   DownstreamPort    PCI address of PCIe port
 * @param[out]  AspmLatencyInfo   Latency info
 * @param[in]   StdHeader         Standard configuration header
 *
 */

VOID
PcieAspmGetMaxExitLatency (
  IN       PCI_ADDR                DownstreamPort,
     OUT   PCIe_ASPM_LATENCY_INFO  *AspmLatencyInfo,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  PCIE_EXIT_LATENCY_DATA  PcieExitLatencyData;
  PcieExitLatencyData.AspmLatencyInfo = AspmLatencyInfo;
  PcieExitLatencyData.ScanData.StdHeader = StdHeader;
  PcieExitLatencyData.LinkCount = 0;
  PcieExitLatencyData.ScanData.GnbScanCallback = PcieAspmGetMaxExitLatencyCallback;
  GnbLibPciScan (DownstreamPort, DownstreamPort, &PcieExitLatencyData.ScanData);
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
PcieL1ExitLatencyWACallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS                ScanStatus;
  PCIE_L1_EXIT_LATENCY_DATA  *PcielinkData;
  PCIE_DEVICE_TYPE           DeviceType;
  ScanStatus = SCAN_SUCCESS;
  PcielinkData = (PCIE_L1_EXIT_LATENCY_DATA *) ScanData;
  PcielinkData->DownstreamPort = Device;
  PcieL1ExitLatencyBlackListFeature(PcielinkData);
  if (PcielinkData->BlackList) {
    return ScanStatus;
  }
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    GnbLibPciScanSecondaryBus (Device, &PcielinkData->ScanData);
    break;
  case  PcieDeviceUpstreamPort:
    GnbLibPciScanSecondaryBus (Device, &PcielinkData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    break;
  default:
    break;
  }
  return ScanStatus;
}
/*----------------------------------------------------------------------------------------*/
/**
 * L1 Exit Latency
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  L1ExitLatency   L1 Exit Latency Value
 * @retval                          FALSE or TRUE
 */
BOOLEAN
PcieLinkL1ExitLatencyWA (
  IN       PCIe_ENGINE_CONFIG      *Engine,
  IN OUT   UINT16                  *L1ExitLatency
  )
{
  PCIE_L1_EXIT_LATENCY_DATA PcieL1ExitLatencyData;
  PcieL1ExitLatencyData.ScanData.StdHeader = NULL;
  PcieL1ExitLatencyData.ScanData.GnbScanCallback = PcieL1ExitLatencyWACallback;
  PcieL1ExitLatencyData.L1ExitLatency = 0xFFFF;
  PcieL1ExitLatencyData.DownstreamPort = Engine->Type.Port.Address;
  PcieL1ExitLatencyData.BlackList = FALSE;
  GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieL1ExitLatencyData.ScanData);
  *L1ExitLatency = PcieL1ExitLatencyData.L1ExitLatency;
  return PcieL1ExitLatencyData.BlackList;
}
