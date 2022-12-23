/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe Latency Tolerance Reporting
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
#include  <Library/BaseLib.h>


#define FILECODE LIBRARY_PCIEMISCCOMMLIB_PCIELTRLIB_FILECODE
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
  BOOLEAN                 LTREn;
  PCI_ADDR                DownstreamPort;
} PCIE_LTR_DATA;
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * set Snoop/non-snoop latency on EP
 *
 *
 *
 * @param[in] Device              PCI Address of the downstream port
 * @param[in] StdHeader           Standard configuration header
 */

VOID
SetPcieEPSnooplatency (
  IN       PCI_ADDR                Device,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT16  PcieCapPtr;
  UINT32  Value;

  PcieCapPtr = GnbLibFindPcieExtendedCapability (Device.AddressValue, PCIE_LTR_EXT_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + 0x04),
      AccessWidth32,
      &Value,
      StdHeader
      );
    Value = (Value & 0xE000E000) | 0x10011001;
    GnbLibPciWrite (
      Device.AddressValue | (PcieCapPtr + 0x04),
      AccessS3SaveWidth32,
      &Value,
      StdHeader
      );
    IDS_HDT_CONSOLE (GNB_TRACE, "  Set Snoop/non-snoop latency for Device = %d:%d:%d Value = %08x\n",
      Device.Address.Bus,
      Device.Address.Device,
      Device.Address.Function,
      Value
      );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get Port_T_POWER_ON_Scale result
 *
 *
 * @param[in] Port_T_POWER_ON_Scale            Undecoded Scale
 *
 * @retval UINT32                              Port_T_POWER_ON_Scale value.
 */
UINT32
GetScaleResult (
  IN       UINT32                Port_T_POWER_ON_Scale
  )
{

  switch (Port_T_POWER_ON_Scale) {
    case 0:
      Port_T_POWER_ON_Scale = 2;
      break;
    case 1:
      Port_T_POWER_ON_Scale = 10;
      break;
    case 2:
      Port_T_POWER_ON_Scale = 100;
      break;
    default:
      break;
   }

  return Port_T_POWER_ON_Scale;

}

/*----------------------------------------------------------------------------------------*/
/**
 * Discovery TPowerOn on RC and EP
 *
 *
 *
 * @param[in] Device              PCI Address of the downstream port
 * @param[in] PcieCapPtr          The PCIe Caps Pointer
 */
VOID
TPowerOnDiscovery (
  IN       PCI_ADDR                Device,
  IN       UINT16                  PcieCapPtr
  )
{
  UINT32                Value;
  UINT32                T_POWER_ON;
  UINT32                End_POINT_T_POWER_ON;
  UINT8                 SubBUS;
  PCI_ADDR              EndPointDevice;
  UINT16                EndPointPcieCapPtr;
  UINT32                Port_T_POWER_ON_Scale;
  UINT32                Port_T_POWER_ON_Value;
  UINT32                Port_T_POWER_ON_Result;
  UINT32                End_Port_T_POWER_ON_Result;

  Port_T_POWER_ON_Scale = 0;
  Port_T_POWER_ON_Value = 0;
  Port_T_POWER_ON_Result = 0;
  End_Port_T_POWER_ON_Result = 0;

  // Check RP first
  GnbLibPciRead (
    Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER),
    AccessWidth32,
    &Value,
    NULL
    );
  IDS_HDT_CONSOLE (GNB_TRACE, "locate %x Value = %x\n", (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER), Value);

  T_POWER_ON = (Value & 0x00FB0000);   // check bit17:16 and 23;19
  IDS_HDT_CONSOLE (GNB_TRACE, "T_POWER_ON %x\n", T_POWER_ON);

  Port_T_POWER_ON_Scale = (Value & 0x00030000);
  Port_T_POWER_ON_Scale = (UINT32) RShiftU64 ((UINT64)Port_T_POWER_ON_Scale, 16);
  Port_T_POWER_ON_Value = (Value & 0x00F80000);
  Port_T_POWER_ON_Value = (UINT32) RShiftU64 ((UINT64)Port_T_POWER_ON_Value, 19);
  Port_T_POWER_ON_Scale =GetScaleResult (Port_T_POWER_ON_Scale);
  Port_T_POWER_ON_Result = Port_T_POWER_ON_Scale * Port_T_POWER_ON_Value;
  IDS_HDT_CONSOLE (GNB_TRACE, "Port_T_POWER_ON_Result: %x\n", Port_T_POWER_ON_Result);
  // check End Device
  GnbLibPciRead (
    Device.AddressValue | (PCICFG_SPACE_SECONDARY_BUS_OFFSET),
    AccessWidth8,
    &SubBUS,
    NULL
  );

  EndPointDevice.Address.Register= 0;
  EndPointDevice.Address.Function= 0;
  EndPointDevice.Address.Device= 0;
  EndPointDevice.Address.Bus = SubBUS;
  EndPointDevice.Address.Segment= 0;

  IDS_HDT_CONSOLE (GNB_TRACE, "SubBUS: %x\n",SubBUS);

  EndPointPcieCapPtr = GnbLibFindPcieExtendedCapability (EndPointDevice.AddressValue, PCIE_EXT_CAP_ID, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "EndPointPcieCapPtr: %x\n", EndPointPcieCapPtr);

  if (EndPointPcieCapPtr != 0) {
    GnbLibPciRead (
      EndPointDevice.AddressValue | (EndPointPcieCapPtr + PCIE_DEVICE_CAP_REGISTER),
      AccessWidth32,
      &Value,
      NULL
      );

    IDS_HDT_CONSOLE (GNB_TRACE, "locate %x Value = %x\n", (PcieCapPtr + PCIE_DEVICE_CAP_REGISTER), Value);

    End_POINT_T_POWER_ON = (Value & 0x00FB0000);   // check bit17:16 and 23;19
    IDS_HDT_CONSOLE (GNB_TRACE, "End_POINT_T_POWER_ON %x\n", End_POINT_T_POWER_ON);

    Port_T_POWER_ON_Scale = (Value & 0x00030000);
    Port_T_POWER_ON_Scale = (UINT32) RShiftU64 ((UINT64)Port_T_POWER_ON_Scale, 16);
    Port_T_POWER_ON_Value = (Value & 0x00F80000);
    Port_T_POWER_ON_Value = (UINT32) RShiftU64 ((UINT64)Port_T_POWER_ON_Value, 19);
    Port_T_POWER_ON_Scale =GetScaleResult (Port_T_POWER_ON_Scale);
    End_Port_T_POWER_ON_Result = Port_T_POWER_ON_Scale * Port_T_POWER_ON_Value;
    IDS_HDT_CONSOLE (GNB_TRACE, "End_Port_T_POWER_ON_Result: %x\n", End_Port_T_POWER_ON_Result);

    // Check largest T POWER ON Scale
    if (Port_T_POWER_ON_Result < End_Port_T_POWER_ON_Result) {
      T_POWER_ON = End_POINT_T_POWER_ON;
      IDS_HDT_CONSOLE (GNB_TRACE, "Swap  T_POWER_ON\n");
    }
  }

  // Program RP
  GnbLibPciRead (
    Device.AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER),
    AccessWidth32,
    &Value,
    NULL
    );

  IDS_HDT_CONSOLE (GNB_TRACE, "  Get Root PORT for Device = %d:%d:%d Value = %08x\n",
     Device.Address.Bus,
     Device.Address.Device,
     Device.Address.Function,
     Value
     );
  Value = (Value & 0xFFFF0000); // Clear lower 16 bits
  Value = Value | (UINT32) RShiftU64 ((UINT64)T_POWER_ON, 16);

  GnbLibPciWrite (
    Device.AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER),
    AccessS3SaveWidth32,
    &Value,
    NULL
    );
   IDS_HDT_CONSOLE (GNB_TRACE, "  Set Root PORT for Device = %d:%d:%d Value = %08x\n",
      Device.Address.Bus,
      Device.Address.Device,
      Device.Address.Function,
      Value
      );

  // Program End Point
  GnbLibPciRead (
    EndPointDevice.AddressValue | (EndPointPcieCapPtr + PCIE_LINK_CAP_REGISTER),
    AccessWidth32,
    &Value,
    NULL
    );
  IDS_HDT_CONSOLE (GNB_TRACE, "  Get EndPoint PORT for Device = %d:%d:%d Value = %08x\n",
     EndPointDevice.Address.Bus,
     EndPointDevice.Address.Device,
     EndPointDevice.Address.Function,
     Value
     );

  Value = (Value & 0xFFFF0000);  // Clear lower 16 bits
  Value = Value | (UINT32) RShiftU64 ((UINT64)T_POWER_ON, 16);

  GnbLibPciWrite (
    EndPointDevice.AddressValue | (EndPointPcieCapPtr + PCIE_LINK_CAP_REGISTER),
    AccessS3SaveWidth32,
    &Value,
    NULL
    );

  IDS_HDT_CONSOLE (GNB_TRACE, "  Set EndPoint PORT for Device = %d:%d:%d Value = %08x\n",
     EndPointDevice.Address.Bus,
     EndPointDevice.Address.Device,
     EndPointDevice.Address.Function,
     Value
     );

}

/*----------------------------------------------------------------------------------------*/
/**
 * Set LC_LTR_L1_2_thresholds on RC
 *
 *
 *
 * @param[in] Device              PCI Address of the downstream port
 * @param[in] AspmL1_1            ASPM L1 SS
 * @param[in] AspmL1_2            ASPM L1 SS
 * @param[in] StdHeader           Standard configuration header
 */

VOID
SetPcieLC_LTR_L1_2_thresholds (
  IN       PCI_ADDR                Device,
  IN       AMD_CONFIG_PARAMS       *StdHeader
  )
{
  UINT16            PcieCapPtr;
  UINT32            Value;
  PCIE_DEVICE_TYPE  DeviceType;

  IDS_HDT_CONSOLE (GNB_TRACE, "Device = %x\n", Device.AddressValue);

  PcieCapPtr = GnbLibFindPcieExtendedCapability (Device.AddressValue, PCIE_EXT_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {

    DeviceType = GnbLibGetPcieDeviceType (Device, StdHeader);
    switch (DeviceType) {
    case  PcieDeviceRootComplex:
    case  PcieDeviceDownstreamPort:
    case  PcieDeviceUpstreamPort:
      TPowerOnDiscovery (Device, PcieCapPtr);
      break;
    default:
      break;
    }

    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CTRL_REGISTER),
      AccessWidth32,
      &Value,
      StdHeader
      );
    Value = (Value & 0x1C00FFFF) | 0x60010000;
    GnbLibPciWrite (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CTRL_REGISTER),
      AccessS3SaveWidth32,
      &Value,
      StdHeader
      );
    IDS_HDT_CONSOLE (GNB_TRACE, "  Set LC_LTR_L1_2_thresholds for Device = %d:%d:%d Value = %08x\n",
      Device.Address.Bus,
      Device.Address.Device,
      Device.Address.Function,
      Value
      );
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
GetPcieLTRCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS           ScanStatus;
  PCIE_LTR_DATA         *PcieLTRData;
  PCIE_DEVICE_TYPE      DeviceType;
  UINT8                 PcieCapPtr;
  UINT32                Value;

  ScanStatus = SCAN_SUCCESS;
  PcieLTRData = (PCIE_LTR_DATA*) ScanData;
  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, ScanData->StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CAP2_REGISTER),
      AccessWidth32,
      &Value,
      ScanData->StdHeader
    );
    if (Value & BIT11) {
      DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
      switch (DeviceType) {
      case  PcieDeviceRootComplex:
      case  PcieDeviceDownstreamPort:
      case  PcieDeviceUpstreamPort:
        GnbLibPciScanSecondaryBus (Device, &PcieLTRData->ScanData);
        break;
      case  PcieDeviceEndPoint:
        PcieLTRData->LTREn = TRUE;
        break;
      case  PcieDeviceLegacyEndPoint:
        break;
      default:
        break;
      }
    } else {
      PcieLTRData->LTREn = FALSE;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "  GetPcieLTRCallback for Device = %d:%d:%d  (LTR_SUPPORTED=%d)\n",
      Device.Address.Bus,
      Device.Address.Device,
      Device.Address.Function,
      PcieLTRData->LTREn
      );
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "  GetPcieLTRCallback for Device = %d:%d:%d  PCIE_CAP_ID not found.\n",
      Device.Address.Bus,
      Device.Address.Device,
      Device.Address.Function
      );
  }

  return ScanStatus;
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
SetPcieLTRCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  PCIE_LTR_DATA         *PcieLTRData;
  PCIE_DEVICE_TYPE      DeviceType;
  UINT8                 PcieCapPtr;
  UINT32                Value;

  PcieLTRData = (PCIE_LTR_DATA*) ScanData;
  IDS_HDT_CONSOLE (GNB_TRACE, "  SetPcieLTRCallback for Device = %d:%d:%d to %d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function,
    PcieLTRData->LTREn
    );

  PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, ScanData->StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CNTL2_REGISTER),
      AccessWidth32,
      &Value,
      ScanData->StdHeader
    );
    Value |= BIT10;
    GnbLibPciWrite (
      Device.AddressValue | (PcieCapPtr + PCIE_DEVICE_CNTL2_REGISTER),
      AccessS3SaveWidth32,
      &Value,
      ScanData->StdHeader
      );

    DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
    switch (DeviceType) {
    case  PcieDeviceRootComplex:
    case  PcieDeviceDownstreamPort:
    case  PcieDeviceUpstreamPort:
      SetPcieLC_LTR_L1_2_thresholds (Device, ScanData->StdHeader);
      GnbLibPciScanSecondaryBus (Device, &PcieLTRData->ScanData);
      break;
    case  PcieDeviceEndPoint:
    case  PcieDeviceLegacyEndPoint:
      SetPcieLC_LTR_L1_2_thresholds (Device, ScanData->StdHeader);
      SetPcieEPSnooplatency (Device, ScanData->StdHeader);
      break;
    default:
      break;
    }
  }
  return SCAN_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init LTR on all active ports
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer          Not used
 */

VOID
PcieLTRPortInitCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  PCIE_LTR_DATA PcieLTRData;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieLTRPortInitCallback Enter\n");
  PcieLTRData.LTREn = FALSE;
  PcieLTRData.ScanData.StdHeader = NULL;

  PcieLTRData.ScanData.GnbScanCallback = GetPcieLTRCallback;
  GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieLTRData.ScanData);

  if (PcieLTRData.LTREn) {
    PcieLTRData.ScanData.GnbScanCallback = SetPcieLTRCallback;
    GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieLTRData.ScanData);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieLTRPortInitCallback Exit\n");
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to enable Latency Tolerance Reporting
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
PcieLTRInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG             *PcieEngine;
  PCIe_WRAPPER_CONFIG            *PcieWrapper;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieLTRInterface Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        PcieLTRPortInitCallback (PcieEngine, NULL);
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieLTRInterface Exit\n");
}


