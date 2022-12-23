/* $NoKeywords:$ */
/**
 * @file
 *
 * Various workarounds
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
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieTrainingV2.h"
#include  "GnbRegistersCommonV2.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBPCIETRAININGV2_PCIEWORKAROUNDSV2_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern BUILD_OPT_CFG UserOptions;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
AGESA_STATUS
PcieConfigureBridgeResourcesV2 (
  IN      PCI_ADDR             Port,
  IN      AMD_CONFIG_PARAMS    *StdHeader
  );

VOID
PcieFreeBridgeResourcesV2 (
  IN      PCI_ADDR             Port,
  IN      AMD_CONFIG_PARAMS    *StdHeader
  );

GFX_WORKAROUND_STATUS
PcieDeskewWorkaroundV2 (
  IN      PCI_ADDR            Device,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  );

GFX_WORKAROUND_STATUS
PcieNvWorkaroundV2 (
  IN      PCI_ADDR            Device,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
PcieProgramCpuMmioV2 (
  OUT    UINT32              *SaveValues,
  IN     AMD_CONFIG_PARAMS   *StdHeader
  );

VOID
PcieRestoreCpuMmioV2 (
  IN     UINT32              *RestoreValues,
  IN     AMD_CONFIG_PARAMS   *StdHeader
  );

BOOLEAN
PcieIsDeskewCardDetectedV2 (
  IN      UINT16             DeviceId
  );

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * ATI RV370/RV380 card workaround
 *
 *
 *
 * @param[in]  Port        PCI address of the port
 * @param[in]  StdHeader   Standard configuration header
 * @retval     GFX_WORKAROUND_STATUS   Return the GFX Card Workaround status
 */
GFX_WORKAROUND_STATUS
PcieGfxCardWorkaroundV2 (
  IN     PCI_ADDR               Port,
  IN     AMD_CONFIG_PARAMS      *StdHeader
  )
{
  GFX_WORKAROUND_STATUS   Status;
  UINT16                  DeviceId;
  UINT16                  VendorId;
  UINT8                   DevClassCode;
  UINT32                  SaveValueData[2];
  PCI_ADDR                Ep;

  Status = GFX_WORKAROUND_SUCCESS;

  Ep.AddressValue = MAKE_SBDFO (0, Port.Address.Bus + Port.Address.Device, 0, 0, 0);
  if (PcieConfigureBridgeResourcesV2 (Port, StdHeader) == AGESA_SUCCESS) {
    GnbLibPciRead (Ep.AddressValue | 0x00, AccessWidth16, &DeviceId, StdHeader);
    Status = GFX_WORKAROUND_DEVICE_NOT_READY;
    if (DeviceId != 0xffff) {
      GnbLibPciRead (Ep.AddressValue | 0x02, AccessWidth16, &VendorId, StdHeader);
      if (VendorId != 0xffff) {
        GnbLibPciRead (Ep.AddressValue | 0x0B, AccessWidth8, &DevClassCode, StdHeader);
        Status = GFX_WORKAROUND_SUCCESS;
        if (DevClassCode == 3) {
          PcieProgramCpuMmioV2 (SaveValueData, StdHeader);
          if (VendorId == 0x1002 && PcieIsDeskewCardDetectedV2 (DeviceId)) {
            Status = PcieDeskewWorkaroundV2 (Ep, StdHeader);
          } else if (VendorId == 0x10DE) {
            Status = PcieNvWorkaroundV2 (Ep, StdHeader);
          }
          PcieRestoreCpuMmioV2 (SaveValueData, StdHeader);
        }
      }
    }
    PcieFreeBridgeResourcesV2 (Port, StdHeader);
  }
  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * RV370/RV380 Deskew workaround
 *
 *
 *
 * @param[in] Device     Pcie Address of ATI RV370/RV380 card.
 * @param[in] StdHeader  Standard configuration header
 */
GFX_WORKAROUND_STATUS
PcieDeskewWorkaroundV2 (
  IN      PCI_ADDR              Device,
  IN      AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINTN       MmioBase;
  UINT16      MmioData1;
  UINT32      MmioData2;

  MmioBase = UserOptions.CfgTempPcieMmioBaseAddress;
  if (MmioBase == 0) {
    return GFX_WORKAROUND_SUCCESS;
  }
  GnbLibPciWrite (Device.AddressValue | 0x18, AccessWidth32, &MmioBase, StdHeader);
  GnbLibPciRMW (Device.AddressValue | 0x04, AccessWidth8 , ~(UINT32) BIT1, BIT1, StdHeader);
  GnbLibMemRMW (MmioBase + 0x120, AccessWidth16, 0, 0xb700, StdHeader);
  GnbLibMemRead (MmioBase + 0x120, AccessWidth16, &MmioData1, StdHeader);
  if (MmioData1 == 0xb700) {
    GnbLibMemRMW (MmioBase + 0x124, AccessWidth32, 0, 0x13, StdHeader);
    GnbLibMemRead (MmioBase + 0x124, AccessWidth32, &MmioData2, StdHeader);
    if (MmioData2 == 0x13) {
      GnbLibMemRead (MmioBase + 0x12C, AccessWidth32, &MmioData2, StdHeader);
      if (MmioData2 & BIT8) {
        return  GFX_WORKAROUND_RESET_DEVICE;
      }
    }
  }
  GnbLibPciRMW (Device.AddressValue | 0x04, AccessWidth8, ~(UINT32) BIT1, 0x0, StdHeader);
  GnbLibPciRMW (Device.AddressValue | 0x18, AccessWidth32, 0x0, 0x0, StdHeader);

  return GFX_WORKAROUND_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  NV43 card workaround (lost SSID)
 *
 *
 *
 * @param[in] Device     Pcie Address of NV43 card.
 * @param[in] StdHeader  Standard configuration header
 */
GFX_WORKAROUND_STATUS
PcieNvWorkaroundV2 (
  IN     PCI_ADDR              Device,
  IN     AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT32      DeviceSSID;
  UINTN       MmioBase;
  UINT32      MmioData3;

  MmioBase = UserOptions.CfgTempPcieMmioBaseAddress;
  if (MmioBase == 0) {
    return GFX_WORKAROUND_SUCCESS;
  }
  GnbLibPciRMW (Device.AddressValue | 0x30, AccessWidth32, 0x0, ((UINT32)MmioBase) | 1, StdHeader);
  GnbLibPciRMW (Device.AddressValue | 0x4, AccessWidth8, 0x0, 0x2, StdHeader);
  GnbLibPciRead (Device.AddressValue | 0x2c, AccessWidth32, &DeviceSSID, StdHeader);
  GnbLibMemRead (MmioBase + 0x54, AccessWidth32, &MmioData3, StdHeader);
  if (DeviceSSID != MmioData3) {
    GnbLibPciRMW (Device.AddressValue | 0x40, AccessWidth32, 0x0, MmioData3, StdHeader);
  }
  GnbLibPciRMW (Device.AddressValue | 0x30, AccessWidth32, 0x0, 0x0, StdHeader);
  GnbLibPciRMW (Device.AddressValue | 0x4, AccessWidth8, 0x0, 0x0, StdHeader);
  return GFX_WORKAROUND_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  Allocate temporary resources for Pcie P2P bridge
 *
 *
 *
 * @param[in] Port         Pci Address of Port to initialize.
 * @param[in] StdHeader    Standard configuration header
 */
AGESA_STATUS
PcieConfigureBridgeResourcesV2 (
  IN      PCI_ADDR              Port,
  IN      AMD_CONFIG_PARAMS     *StdHeader
  )
{
  UINT32      Value;
  UINT32      MmioBase;

  MmioBase = UserOptions.CfgTempPcieMmioBaseAddress;
  if (MmioBase == 0) {
    return AGESA_WARNING;
  }
  Value = Port.Address.Bus + ((Port.Address.Bus + Port.Address.Device) << 8) + ((Port.Address.Bus + Port.Address.Device) << 16);
  GnbLibPciWrite (Port.AddressValue | DxFxx18_ADDRESS, AccessWidth32, &Value, StdHeader);
  Value = MmioBase + (MmioBase >> 16);
  GnbLibPciWrite (Port.AddressValue | DxFxx20_ADDRESS, AccessWidth32, &Value, StdHeader);
  Value = 0x000fff0;
  GnbLibPciWrite (Port.AddressValue | DxFxx24_ADDRESS, AccessWidth32, &Value, StdHeader);
  Value = 0x2;
  GnbLibPciWrite (Port.AddressValue | D0F0x04_ADDRESS, AccessWidth8, &Value, StdHeader);
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 *  Free temporary resources for Pcie P2P bridge
 *
 *
 *
 * @param[in] Port       Pci Address of Port to clear resource allocation.
 * @param[in] StdHeader  Standard configuration header
 */
VOID
PcieFreeBridgeResourcesV2 (
  IN      PCI_ADDR            Port,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 Value;

  Value = 0;
  GnbLibPciWrite (Port.AddressValue | D0F0x04_ADDRESS, AccessWidth8,  &Value, StdHeader);
  GnbLibPciWrite (Port.AddressValue | DxFxx18_ADDRESS, AccessWidth32, &Value, StdHeader);
  GnbLibPciWrite (Port.AddressValue | DxFxx20_ADDRESS, AccessWidth32, &Value, StdHeader);
  GnbLibPciWrite (Port.AddressValue | DxFxx24_ADDRESS, AccessWidth32, &Value, StdHeader);

}


/*----------------------------------------------------------------------------------------*/
/*
 * Save CPU MMIO register
 *
 *
 *
 * @param[out] UINT32        SaveValues
 * @param[in]  StdHeader     Standard configuration header
 *
 */
VOID
PcieProgramCpuMmioV2 (
     OUT   UINT32             *SaveValues,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  //Save CPU MMIO Register
  GnbLibPciRead (MAKE_SBDFO (0, 0, 0x18, 0x1, 0xB8), AccessWidth32, SaveValues, StdHeader);
  GnbLibPciRead (MAKE_SBDFO (0, 0, 0x18, 0x1, 0xBC), AccessWidth32, SaveValues + 1, StdHeader);

  //Write Temp Pcie MMIO to CPU
  GnbLibPciRMW (MAKE_SBDFO (0, 0, 0x18, 0x1, 0xBC), AccessWidth32, 0, (UserOptions.CfgTempPcieMmioBaseAddress >> 16) << 8, StdHeader);
  GnbLibPciRMW (MAKE_SBDFO (0, 0, 0x18, 0x1, 0xB8), AccessWidth32, 0, ((UserOptions.CfgTempPcieMmioBaseAddress >> 16) << 8) | 0x3, StdHeader);

}

/*----------------------------------------------------------------------------------------*/
/*
 * Restore CPU MMIO register
 *
 *
 *
 * @param[in] PCIe_PLATFORM_CONFIG    Pcie
 * @param[in] StdHeader               Standard configuration header
 */
VOID
PcieRestoreCpuMmioV2 (
  IN      UINT32                *RestoreValues,
  IN      AMD_CONFIG_PARAMS     *StdHeader
  )
{
  //Restore CPU MMIO Register
  GnbLibPciRMW (MAKE_SBDFO (0, 0, 0x18, 0x1, 0xB8), AccessWidth32, 0, *RestoreValues, StdHeader);
  GnbLibPciRMW (MAKE_SBDFO (0, 0, 0x18, 0x1, 0xBC), AccessWidth32, 0, *(RestoreValues + 1), StdHeader);

}

/*----------------------------------------------------------------------------------------*/
/*
 * Check if card required test for deskew workaround
 *
 *
 *
 * @param[in] DeviceId    Device ID
 */

BOOLEAN
PcieIsDeskewCardDetectedV2 (
  IN      UINT16    DeviceId
  )
{
  if ((DeviceId >= 0x3150 && DeviceId <= 0x3152) || (DeviceId == 0x3154) ||
     (DeviceId == 0x3E50) || (DeviceId == 0x3E54) ||
     ((DeviceId & 0xfff8) == 0x5460) || ((DeviceId & 0xfff8)  == 0x5B60)) {
    return TRUE;
  }
  return FALSE;
}



