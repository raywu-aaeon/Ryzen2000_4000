/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe Clock Power Managment
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
#include  "Gnb.h"
#include  "GnbPcieConfig.h"
#include  "GnbCommonLib.h"
#include  "PcieClkPm.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIEMISC_PCIECLKPM_FILECODE
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
 * Enable Clock Power Managment on function of the device
 *
 *
 *
 * @param[in] Function     PCI address of function.
 * @param[in] StdHeader    Standard configuration header
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
STATIC
PcieClkPmEnableOnFunction (
  IN       PCI_ADDR             Function,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8       PcieCapPtr;
  PcieCapPtr = GnbLibFindPciCapability (Function.AddressValue, PCIE_CAP_ID, StdHeader);
  if (PcieCapPtr != 0) {
    GnbLibPciRMW (
      Function.AddressValue | (PcieCapPtr + PCIE_LINK_CTRL_REGISTER),
      AccessS3SaveWidth32,
      ~(UINT32) (BIT8),
      BIT8,
      StdHeader
      );
  }
}


/**----------------------------------------------------------------------------------------*/
/**
 * check capability of entire device including its functions
 *
 *
 *
 * @param[in] Device      PCI address of downstream port
 * @param[in] StdHeader   Standard configuration header
 *
 * @retval    TRUE - Device support Clock Power Managment
 */
 /*----------------------------------------------------------------------------------------*/
BOOLEAN
STATIC
PcieClkPmCheckDeviceCapability (
  IN       PCI_ADDR                 Device,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{

  UINT8   MaxFunc;
  UINT8   CurrentFunc;
  UINT8   PcieCapPtr;
  UINT32  Value;

  MaxFunc = GnbLibPciIsMultiFunctionDevice (Device.AddressValue, StdHeader) ? 7 : 0;

  for (CurrentFunc = 0; CurrentFunc <= MaxFunc; CurrentFunc++) {
    Device.Address.Function = CurrentFunc;
    if (GnbLibPciIsDevicePresent (Device.AddressValue, StdHeader)) {
      PcieCapPtr = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, StdHeader);
      if (PcieCapPtr == 0) {
        return FALSE;
      }
      GnbLibPciRead (
        Device.AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER),
        AccessWidth32,
        &Value,
        StdHeader
        );
      if ((Value & BIT18) == 0) {
        return FALSE;
      }
    }
  }
  return TRUE;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Set Clock power managment on device
 *
 *
 *
 * @param[in] Device        PCI address of device.
 * @param[in] StdHeader     Standard configuration header
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
STATIC
PcieClkPmEnableOnDevice (
  IN       PCI_ADDR             Device,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8                   MaxFunc;
  UINT8                   CurrentFunc;
  AGESA_STATUS            AgesaStatus;
  AgesaStatus = AGESA_UNSUPPORTED;
  if (PcieClkPmCheckDeviceCapability (Device, StdHeader)) {
    MaxFunc = GnbLibPciIsMultiFunctionDevice (Device.AddressValue, StdHeader) ? 7 : 0;
    for (CurrentFunc = 0; CurrentFunc <= MaxFunc; CurrentFunc++) {
      Device.Address.Function = CurrentFunc;
      if (GnbLibPciIsDevicePresent (Device.AddressValue, StdHeader)) {
// todo:tempremove        AgesaStatus = AgesaGnbOemCallout (StdHeader, AGESA_GNB_PCIE_CLK_REQ, &Device);
// todo:tempremove        if (AgesaStatus == AGESA_SUCCESS) {
        IDS_HDT_CONSOLE (GNB_TRACE, "  Enable Clock Power Managment for Device = %d:%d:%d\n",
        Device.Address.Bus,
        Device.Address.Device,
        Device.Address.Function
        );
        PcieClkPmEnableOnFunction (Device, StdHeader);
// todo:tempremove        }
      }
    }
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
STATIC
PcieClkPmCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS             ScanStatus;
  PCIE_DEVICE_TYPE        DeviceType;
  ScanStatus = SCAN_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "  PcieClkPmCallback for Device = %d:%d:%d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function
    );
  ScanStatus = SCAN_SUCCESS;
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
    GnbLibPciRMW (Device.AddressValue | 0x18, AccessS3SaveWidth32, 0xffffffffull, 0x0, ScanData->StdHeader);
    GnbLibPciScanSecondaryBus (Device, ScanData);
    break;
  case  PcieDeviceUpstreamPort:
    PcieClkPmEnableOnDevice (Device, ScanData->StdHeader);
    GnbLibPciRMW (Device.AddressValue | 0x18, AccessS3SaveWidth32, 0xffffffffull, 0x0, ScanData->StdHeader);
    GnbLibPciScanSecondaryBus (Device, ScanData);
    ScanStatus = SCAN_SKIP_FUNCTIONS | SCAN_SKIP_DEVICES | SCAN_SKIP_BUSES;
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    PcieClkPmEnableOnDevice (Device, ScanData->StdHeader);
    ScanStatus = SCAN_SKIP_FUNCTIONS | SCAN_SKIP_DEVICES | SCAN_SKIP_BUSES;
    break;
  default:
    break;
  }
  return ScanStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Confiugure Clock Power Managment
 *
 *
 *
 *
 * @param[in]       DownstreamPort       Downstream port PCI address
 * @param[in]       StdHeader            Standard configuration header
 *
 */

VOID
STATIC
PcieClkPmPortInitConfigure (
  IN       PCI_ADDR               DownstreamPort,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  GNB_PCI_SCAN_DATA  ScanData;
  ScanData.StdHeader = StdHeader;
  ScanData.GnbScanCallback = PcieClkPmCallback;
  GnbLibPciScan (DownstreamPort, DownstreamPort, &ScanData);
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
PcieClkPmPortInitCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  if (Engine->Type.Port.PortData.MiscControls.ClkPmSupport == 0x1 &&
      !PcieConfigIsSbPcieEngine (Engine) &&
      PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
    PcieClkPmPortInitConfigure (
      Engine->Type.Port.Address,
      GnbLibGetHeader (Pcie)
      );
  }
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to enable Clock Power Managment
 *
 *
 *
 * @param[in] StdHeader   Standard configuration header
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/
AGESA_STATUS
PcieClkPmInterface (
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  AGESA_STATUS          AgesaStatus;
  PCIe_PLATFORM_CONFIG  *Pcie;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieClkPmInterface Enter\n");
  AgesaStatus = PcieLocateConfigurationData (StdHeader, &Pcie);
  if (AgesaStatus == AGESA_SUCCESS) {
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
      PcieClkPmPortInitCallback,
      NULL,
      Pcie
      );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieClkPmInterface Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}

