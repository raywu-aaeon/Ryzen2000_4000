/* $NoKeywords:$ */
/**
 * @file
 *
 * Configure Max Payload
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
#include  <Library/AmdBaseLib.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/GnbPcieConfigLib.h>
#include  <Library/PcieMiscCommLib.h>
#include  <Library/PcdLib.h>
#include  <OptionGnb.h>

#define FILECODE LIBRARY_PCIEMISCCOMMLIB_PCIEMAXPAYLOADLIB_FILECODE

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
  UINT8                   MaxPayload;
  BOOLEAN                 Extend_Tag;
} PCIE_MAX_PAYLOAD_DATA;


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


SCAN_STATUS
PcieGetMaxPayloadCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  );

SCAN_STATUS
PcieSetMaxPayloadCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  );

AGESA_STATUS
PciePayloadBlackListFeature (
  IN       PCI_ADDR               Device,
  IN       UINT8                  *MaxPayload,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Determine maximum payload size for PCIe segment
 *
 *  Scan through all link in segment to determine maximum payload by EPs.
 *
 * @param[in]   DownstreamPort    PCI address of PCIe port
 * @param[in]   EngineMaxPayload  MaxPayload supported by the engine
 * @param[in]   StdHeader         Standard configuration header
 *
 */

VOID
PcieSetMaxPayload (
  IN       PCI_ADDR                DownstreamPort,
  IN       UINT8                   EngineMaxPayload,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  PCIE_MAX_PAYLOAD_DATA  PcieMaxPayloadData;

  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieSetMaxPayload for Device = %d:%d:%d\n",
    DownstreamPort.Address.Bus,
    DownstreamPort.Address.Device,
    DownstreamPort.Address.Function
    );
  PcieMaxPayloadData.MaxPayload = EngineMaxPayload;
  PcieMaxPayloadData.Extend_Tag = TRUE;
  PcieMaxPayloadData.ScanData.StdHeader = StdHeader;
  PcieMaxPayloadData.ScanData.GnbScanCallback = PcieGetMaxPayloadCallback;
  GnbLibPciScan (DownstreamPort, DownstreamPort, &PcieMaxPayloadData.ScanData);
  PcieMaxPayloadData.ScanData.GnbScanCallback = PcieSetMaxPayloadCallback;
  GnbLibPciScan (DownstreamPort, DownstreamPort, &PcieMaxPayloadData.ScanData);
  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieSetMaxPayloadExit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Evaluate device Max Payload - save SMALLEST Max Payload for PCIe Segment
 *
 *
 *
 * @param[in]     Device          PCI Address
 * @param[in,out] ScanData        Scan configuration data
 * @retval                        Scan Status of 0
 */

SCAN_STATUS
PcieGetMaxPayloadCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  PCIE_MAX_PAYLOAD_DATA   *PcieMaxPayloadData;
  PCIE_DEVICE_TYPE        DeviceType;
  UINT32                  Value;
  UINT8                   PcieCapPtr;
  UINT8                   DeviceMaxPayload;

  PcieMaxPayloadData = (PCIE_MAX_PAYLOAD_DATA*) ScanData;
  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieGetMaxPayloadCallback for Device = %d:%d:%d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function
    );
  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, ScanData->StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER),
      AccessWidth32,
      &Value,
      ScanData->StdHeader
    );
    DeviceMaxPayload = (UINT8) (Value & 0x7);
    if ((Value & BIT5) == 0) {
      PcieMaxPayloadData->Extend_Tag = FALSE;
    }
    PciePayloadBlackListFeature (Device, &DeviceMaxPayload, ScanData->StdHeader);
    IDS_HDT_CONSOLE (GNB_TRACE, "  Found DeviceMaxPayload as %d (Value = 0x%x)\n", DeviceMaxPayload, Value);
    if (DeviceMaxPayload < PcieMaxPayloadData->MaxPayload) {
      PcieMaxPayloadData->MaxPayload = DeviceMaxPayload;
    }
  }
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
  case  PcieDeviceUpstreamPort:
    GnbLibPciScanSecondaryBus (Device, &PcieMaxPayloadData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    break;
  default:
    break;
  }
  return SCAN_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Configure the Max Payload setting to all devices in the PCIe Segment
 *
 *
 *
 * @param[in]     Device          PCI Address
 * @param[in,out] ScanData        Scan configuration data
 * @retval                        Scan Status of 0
 */

SCAN_STATUS
PcieSetMaxPayloadCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  PCIE_MAX_PAYLOAD_DATA   *PcieMaxPayloadData;
  PCIE_DEVICE_TYPE        DeviceType;
  UINT8                   PcieCapPtr;
  UINT32                  Value;

  PcieMaxPayloadData = (PCIE_MAX_PAYLOAD_DATA*) ScanData;
  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieSetMaxPayloadCallback for Device = %d:%d:%d to %d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function,
    PcieMaxPayloadData->MaxPayload
    );
  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, ScanData->StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CTRL_REGISTER),
      AccessWidth32,
      &Value,
      ScanData->StdHeader
    );
    Value = (Value & 0xFFFFFF1F) | (PcieMaxPayloadData->MaxPayload << 5);
    if (PcieMaxPayloadData->Extend_Tag) {
      Value |= BIT8;
      IDS_HDT_CONSOLE (GNB_TRACE, "EXTEND_TAG_EN PCIE_DEVICE_CTRL=%08x\n", Value);
    }
    GnbLibPciWrite (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CTRL_REGISTER),
      AccessS3SaveWidth32,
      &Value,
      ScanData->StdHeader
      );
  }

  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
  case  PcieDeviceUpstreamPort:
    GnbLibPciScanSecondaryBus (Device, &PcieMaxPayloadData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    break;
  default:
    break;
  }
  return SCAN_SUCCESS;
}

UINT16  PayloadBlacklistDeviceTable[] = {
  0x1969, 0x1083, (UINT16) MAX_PAYLOAD_128
};

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie Max_Payload_Size Black List
 *
 *
 *
 * @param[in] Device              PCI_ADDR of PCIe Device to evaluate
 * @param[in] MaxPayload          Pointer to Max_Payload_Size value
 * @param[in] StdHeader           Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
PciePayloadBlackListFeature (
  IN       PCI_ADDR               Device,
  IN       UINT8                  *MaxPayload,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  UINT32  TargetDeviceId;
  UINTN   i;
  UINT32  DeviceId;
  UINT32  VendorId;

  GnbLibPciRead (Device.AddressValue, AccessWidth32, &TargetDeviceId, StdHeader);
  for (i = 0; i < (sizeof (PayloadBlacklistDeviceTable) / sizeof (UINT16)); i = i + 3) {
    VendorId = PayloadBlacklistDeviceTable[i];
    DeviceId = PayloadBlacklistDeviceTable[i + 1];
    if (VendorId == (UINT16)TargetDeviceId) {
      if (DeviceId == 0xFFFF || DeviceId == (TargetDeviceId >> 16)) {
        *MaxPayload = (UINT8) PayloadBlacklistDeviceTable[i + 2];
      }
    }
  }
  return AGESA_SUCCESS;
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
PcieMaxPayloadInitCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  UINT8                     EngineMaxPayload;
  UINT16                    linkwidth;

  if ((PcdGetBool (PcdCfgMaxPayloadEnable)) &&
      (!PcieConfigIsSbPcieEngine (Engine)) &&
      (PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS))) {
    EngineMaxPayload =  Engine->Type.Port.MaxPayloadSize;
    if (Engine->EngineData.EndLane >= Engine->EngineData.StartLane) {
      linkwidth = Engine->EngineData.EndLane - Engine->EngineData.StartLane + 1;
    } else {
      linkwidth = Engine->EngineData.StartLane - Engine->EngineData.EndLane + 1;
    }
    if (linkwidth >= 4) {
      if (EngineMaxPayload > MAX_PAYLOAD_512) {
        EngineMaxPayload =  MAX_PAYLOAD_512;
      }
    } else if (linkwidth == 2) {
      if (EngineMaxPayload > MAX_PAYLOAD_256) {
        EngineMaxPayload =  MAX_PAYLOAD_256;
      }
    } else if (linkwidth == 1) {
      if (EngineMaxPayload > MAX_PAYLOAD_128) {
        EngineMaxPayload =  MAX_PAYLOAD_128;
      }
    }

    IDS_HDT_CONSOLE (GNB_TRACE, "%dX Device = %d:%d:%d MaxPayload = %x\n", linkwidth, Engine->Type.Port.Address.Address.Bus, Engine->Type.Port.Address.Address.Device, Engine->Type.Port.Address.Address.Function, EngineMaxPayload);
    PcieSetMaxPayload (Engine->Type.Port.Address, EngineMaxPayload, NULL);
  }
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to configure MaxPayloadSize on PCIE interface
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/

VOID
PcieMaxPayloadInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG             *PcieEngine;
  PCIe_WRAPPER_CONFIG            *PcieWrapper;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMaxPayloadInterface Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        PcieMaxPayloadInitCallback (PcieEngine, NULL);
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMaxPayloadInterface Exit\n");
}


