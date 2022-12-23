/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe link ASPM L1 SS
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
#include  <Library/NbioRegisterAccLib.h>

#define FILECODE LIBRARY_PCIEMISCCOMMLIB_PCIEASPML1SSLIB_FILECODE
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
  BOOLEAN                 AspmL1_1;
  BOOLEAN                 AspmL1_2;
  PCI_ADDR                DownstreamPort;
} PCIE_ASPM_L1SS_DATA;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Enable PCIE Advance state power management
 *
 *
 *
 * @param[in] Device              PCI Address of the port
 * @param[in] Data                Control Data
 * @param[in] StdHeader           Standard configuration header
 */

VOID
PcieL1SSEnable (
  IN       PCI_ADDR                Device,
  IN       UINT32                  Data,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT16  PcieCapPtr;
  UINT32  CapValue;
  UINT32  Value;

  PcieCapPtr = GnbLibFindPcieExtendedCapability (Device.AddressValue, PCIE_EXT_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER),
      AccessWidth32,
      &CapValue,
      StdHeader
      );
    if (CapValue & BIT4) {
      GnbLibPciRead (
        Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CTRL_REGISTER),
        AccessWidth32,
        &Value,
        StdHeader
        );
      Value = ((Value & 0xFFFFFFF0) | Data);
      GnbLibPciWrite (
        Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CTRL_REGISTER),
        AccessS3SaveWidth32,
        &Value,
        StdHeader
        );
      IDS_HDT_CONSOLE (GNB_TRACE, "  Enable L1SS for Device = %d:%d:%d (%08x - %08x)\n",
        Device.Address.Bus,
        Device.Address.Device,
        Device.Address.Function,
        CapValue,
        Value
        );
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get PCIe Link L1SS Capability
 *
 *
 *
 * @param[in] Device              PCI Address of the downstream port
 * @param[in,out] Value           Capability Value
 * @param[in] StdHeader           Standard configuration header
 */

BOOLEAN
PcieL1SSGetCapability (
  IN       PCI_ADDR                Device,
  IN OUT   UINT32                  *Value,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT16         PcieCapPtr;
  UINT32         CapValue;
  BOOLEAN        CapabilityStatus;

  CapValue = 0;
  CapabilityStatus = FALSE;
  PcieCapPtr = GnbLibFindPcieExtendedCapability (Device.AddressValue, PCIE_EXT_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER),
      AccessWidth32,
      &CapValue,
      StdHeader
      );
    if (CapValue & BIT4) {
      CapabilityStatus = TRUE;
    }
  }
  *Value = CapValue;

  IDS_HDT_CONSOLE (GNB_TRACE, "  Device(%d:%d:%d) L1SS Capability:%d, Value=0x%x\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function,
    CapabilityStatus,
    CapValue
    );
 return CapabilityStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enable PCIE Advance state power management
 *
 *
 *
 * @param[in] Downstream          PCI Address of the downstream port
 * @param[in] Upstream            PCI Address of the upstream port
 * @param[in] AspmL1_1            ASPM L1 SS
 * @param[in] AspmL1_2            ASPM L1 SS
 * @param[in] StdHeader           Standard configuration header
 */

VOID
PcieLinkL1SSEnable (
  IN       PCI_ADDR                Downstream,
  IN       PCI_ADDR                Upstream,
  IN       BOOLEAN                 AspmL1_1,
  IN       BOOLEAN                 AspmL1_2,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  BOOLEAN        boolDownstreamCap;
  BOOLEAN        boolUpstreamCap;
  UINT32         DownstreamCapValue;
  UINT32         UpstreamCapValue;
  UINT32         Data32;

  Data32 = 0;
  boolDownstreamCap = PcieL1SSGetCapability (Downstream, &DownstreamCapValue, StdHeader);
  boolUpstreamCap = PcieL1SSGetCapability (Upstream, &UpstreamCapValue, StdHeader);
  if (boolDownstreamCap & boolUpstreamCap) {
    if (AspmL1_1) {
      if ((DownstreamCapValue & BIT1) && (UpstreamCapValue & BIT1)) {
        Data32 |= BIT1;
      }
      if ((DownstreamCapValue & BIT3) && (UpstreamCapValue & BIT3)) {
        Data32 |= BIT3;
      }
    }
    if (AspmL1_2) {
      if (AspmL1_2) {
        if ((DownstreamCapValue & BIT0) && (UpstreamCapValue & BIT0)) {
          Data32 |= BIT0;
        }
        if ((DownstreamCapValue & BIT2) && (UpstreamCapValue & BIT2)) {
          Data32 |= BIT2;
        }
      }
    }
    PcieL1SSEnable (Downstream, Data32, StdHeader);
    PcieL1SSEnable (Upstream, Data32, StdHeader);
  }
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
SetPcieAspmL1SSCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS           ScanStatus;
  PCIE_ASPM_L1SS_DATA   *PcieAspmL1SSData;
  PCIE_DEVICE_TYPE      DeviceType;

  ScanStatus = SCAN_SUCCESS;
  PcieAspmL1SSData = (PCIE_ASPM_L1SS_DATA*) ScanData;

  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    PcieAspmL1SSData->DownstreamPort = Device;
    GnbLibPciScanSecondaryBus (Device, &PcieAspmL1SSData->ScanData);
    break;
  case  PcieDeviceUpstreamPort:
    PcieLinkL1SSEnable (
      PcieAspmL1SSData->DownstreamPort,
      Device,
      PcieAspmL1SSData->AspmL1_1,
      PcieAspmL1SSData->AspmL1_2,
      ScanData->StdHeader
      );
    GnbLibPciScanSecondaryBus (Device, &PcieAspmL1SSData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    PcieLinkL1SSEnable (
      PcieAspmL1SSData->DownstreamPort,
      Device,
      PcieAspmL1SSData->AspmL1_1,
      PcieAspmL1SSData->AspmL1_2,
      ScanData->StdHeader
      );
    ScanStatus = SCAN_SKIP_FUNCTIONS;
    break;
  default:
    break;
  }
  return ScanStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init PM L1 SS on all active ports
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer          Not used
 */

VOID
PcieAspmL1SSPortInitCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  PCIE_ASPM_L1SS_DATA PcieAspmL1SSData;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmL1SSPortInitCallback Enter\n");
  IDS_HDT_CONSOLE (GNB_TRACE, "  L1SS %d:%d:%d (L1.1=%d, L1.2=%d)\n",
    Engine->Type.Port.Address.Address.Bus,
    Engine->Type.Port.Address.Address.Device,
    Engine->Type.Port.Address.Address.Function,
    Engine->Type.Port.LinkAspmL1_1,
    Engine->Type.Port.LinkAspmL1_2
    );

  PcieAspmL1SSData.AspmL1_1 = (BOOLEAN) Engine->Type.Port.LinkAspmL1_1;
  PcieAspmL1SSData.AspmL1_2 = (BOOLEAN) Engine->Type.Port.LinkAspmL1_2;
  PcieAspmL1SSData.ScanData.StdHeader = NULL;

  PcieAspmL1SSData.ScanData.GnbScanCallback = SetPcieAspmL1SSCallback;
  GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieAspmL1SSData.ScanData);

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmL1SSPortInitCallback Exit\n");
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to enable PM L1 SS
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
PcieAspmL1SSInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG             *PcieEngine;
  PCIe_WRAPPER_CONFIG            *PcieWrapper;
  UINT32                         SmnAddress;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmL1SSInterface Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        if ((PcieEngine->Type.Port.LinkAspmL1_1 == 1) || (PcieEngine->Type.Port.LinkAspmL1_2 == 1)) {
          if (PcieConfigCheckPortStatus (PcieEngine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
            PcieAspmL1SSPortInitCallback (PcieEngine, NULL);
            if ((PcieEngine->Type.Port.LinkAspmL1_1 == 1) || (PcieEngine->Type.Port.LinkAspmL1_2 == 1)) {

              SmnAddress = (PcieWrapper->WrapId == 0) ? 0x111402ec : 0x112402ec;
              SmnAddress |= (PcieEngine->Type.Port.PortId % 8) << 12;
              NbioRegisterRMW (GnbHandle, TYPE_SMN, SmnAddress, (UINT32) ~(BIT21), BIT21, GNB_REG_ACC_FLAG_S3SAVE);

              // after enable L1 SS, then re-enable ASPM L1
              PcieEngine->Type.Port.PortData.LinkAspm = AspmL1;
            }
            if (PcieEngine->Type.Port.LinkAspmL1_2 == 1) {
              // if L1.2 is enabled, LTR has to be enabled
              if (PcieWrapper->WrapId == 0) {
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11140304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11141304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11142304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11143304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11144304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11145304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11146304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11147304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
              } else {
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11240304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11241304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11242304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11243304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11244304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11245304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11246304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
                NbioRegisterRMW (GnbHandle, TYPE_SMN, 0x11247304, (UINT32) ~(BIT5), BIT5, GNB_REG_ACC_FLAG_S3SAVE);
              }
            }
          } else if (PcieEngine->Type.Port.PortData.LinkHotplug == HotplugDisabled) {
            SmnAddress = (PcieWrapper->WrapId == 0) ? 0x11100378 : 0x11200378;
            SmnAddress |= (PcieEngine->Type.Port.PortId % 8) << 12;
            NbioRegisterRMW (GnbHandle, TYPE_SMN, SmnAddress,
                             (UINT32) ~(0xF),
                             0xF,
                             GNB_REG_ACC_FLAG_S3SAVE);

            SmnAddress = (PcieWrapper->WrapId == 0) ? 0x111402ec : 0x112402ec;
            SmnAddress |= (PcieEngine->Type.Port.PortId % 8) << 12;
            NbioRegisterRMW (GnbHandle, TYPE_SMN, SmnAddress, (UINT32) ~(BIT21), BIT21, GNB_REG_ACC_FLAG_S3SAVE);
          }
        }
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmL1SSInterface Exit\n");
}

