/* $NoKeywords:$ */
/**
 * @file
 *
 * A Plus A Graphics Configuration
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV9Dxe
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
 */
/*****************************************************************************
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
 */
#include <PiDxe.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdNbioPcieServicesProtocol.h>
#include <Protocol/AmdCcxProtocol.h>
#include <GnbDxio.h>
#include <Guid/GnbPcieInfoHob.h>
#include <GnbRegistersRV.h>
#include <Library/GnbRegisterAccZpLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/PcieConfigLib.h>
#include <IdsHookId.h>
#include <Library/AmdIdsHookLib.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/GnbLib.h>
#include <Library/GnbPciAccLib.h>
#include "AmdPsppRV.h"
#include <Library/GnbPciLib.h>

#include <AmdPcieComplex.h>

#define FILECODE        NBIO_PCIE_AMDNBIOSPCIERVDXE_AMDPSPPRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


UINT16 DefaultSmartDeviceVendorList[] = {
  0x1002,
  0x1022,
  0x10DE,
  0xFFFF
};

VEN_DEV_ID DefaultBlacklistDeviceList[] = {
  {0x8086, 0x2526},
  {0xFFFF, 0xFFFF}
};


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 * Callback to init A+A feature to SMU
 *
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer          Not used
 * @param[in]       Pcie            Pointer to global PCIe configuration
 *
 */

UINT32
STATIC
GetPsppDeviceType (
  IN       UINT16                VendorId,
  IN       UINT16                DeviceId
  )
{
  UINT32      PsppDeviceType;
  UINT32      Index;

  PsppDeviceType = NonSmartDevice;

  Index = 0;
  while (DefaultSmartDeviceVendorList[Index] != 0xFFFF) {
    if (DefaultSmartDeviceVendorList[Index] == VendorId) {
      return SmartDevice;
    }
    Index++;
  }
  Index = 0;
  while (DefaultBlacklistDeviceList[Index].Value != 0xFFFFFFFF) {
    if ((DefaultBlacklistDeviceList[Index].Field.VendorId == VendorId) &&
       (DefaultBlacklistDeviceList[Index].Field.DeviceId == DeviceId)) {
      return DumbDevice;
    }
    Index++;
  }
  return PsppDeviceType;
}


/**
 * Callback to init A+A feature to SMU
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
AmdPsppCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32                    SecondaryAddress;
  PCI_ADDR                  DeviceAddress;
  UINT32                    VendorDeviceId;
  UINT16                    DeviceId;
  UINT16                    VendorId;
  UINT32                    DeviceType;
  GNB_HANDLE                *NbioHandle;
  UINT32                    SmuArg[6];
  UINT8                     PsppMode;
  UINT32                    PsppDeviceType;
  UINT32                    DeviceFunction;
  UINT32                    TargetSpeed;
  PCIE_LC_SPEED_CNTL_STRUCT LcSpeedCntl;
  UINT32                    PciAddress = 0;
  UINT8                     PMData8 = 0;
  UINT8                     OrgPMData8 = 0;
  UINT32                    PciAddress2 = 0;
  UINT8                     ASPMData8 = 0;
  UINT8                     OrgAspmData8 = 0;
  UINT32                    PciAddress3 = 0;
  UINT8                     CurrentLinkSpeed8 = 0;
  UINT8                     WatchDogCounter = 0;
  UINT8                     PcieCapPtr = 0;
  UINT16                    ParentCapPtr = 0;

  // DXIO PSPP modes do not match AGESA definitions.  Translate the value to DXIO values.
  switch (PcdGet8 (PcdPsppPolicy)) {
  case AgesaPsppPerformance:
    PsppMode = DxioPsppPerformance;
    break;
  case AgesaPsppBalance:
    PsppMode = DxioPsppBalanced;
    break;
  case AgesaPsppPowerSaving:
    PsppMode = DxioPsppPowerSaving;
    break;
  default:
    return;
  }

  NbioHandle = (GNB_HANDLE *) PcieConfigGetParentSilicon (Engine);

  GnbLibPciRead (Engine->Type.Port.Address.AddressValue | 0x18, AccessWidth32, &SecondaryAddress, (AMD_CONFIG_PARAMS *) NULL);
  DeviceAddress.AddressValue = 0;
  DeviceAddress.Address.Bus = (SecondaryAddress >> 8) & 0xFF;
  IDS_HDT_CONSOLE (GNB_TRACE, "Checking secondary bus 0x%x\n", SecondaryAddress);

  DeviceFunction = (Engine->Type.Port.Address.Address.Device << 3) + Engine->Type.Port.Address.Address.Function;
  if ((DeviceAddress.Address.Bus != 0xFF) && (DeviceAddress.Address.Bus != 0x0)) {
    GnbLibPciRead (DeviceAddress.AddressValue, AccessWidth32, &VendorDeviceId, (AMD_CONFIG_PARAMS *)NULL);
    GnbLibPciRead (DeviceAddress.AddressValue | 0x08, AccessWidth32, &DeviceType, (AMD_CONFIG_PARAMS *) NULL);
    VendorId = (UINT16) (VendorDeviceId & 0xFFFF);
    DeviceId = (UINT16) (VendorDeviceId >> 16);
    IDS_HDT_CONSOLE (GNB_TRACE, "  Read device info on bus %d Vendor:%x Device %x and DeviceType\n", DeviceAddress.Address.Bus, VendorId, DeviceId, DeviceType >> 24);
    PsppDeviceType = GetPsppDeviceType (VendorId, DeviceId);
    LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
    SmuArg[1] = DeviceFunction;
    SmuArg[2] = PsppDeviceType;
    SmuArg[3] = PsppMode;
    NbioDxioServiceRequestV10 (NbioHandle, DXIO_MSG_RNTM_CHANGESPEEDPERPSPPPOLICY, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);

    if (VendorId== 0x8086 && DeviceId == 0x2526) {
      WatchDogCounter = 0;

      ParentCapPtr = GnbLibFindPciCapability (DeviceAddress.AddressValue, PCIE_EXT_AER_CAP_ID, NULL);
      if (ParentCapPtr != 0) {
        PciAddress = MAKE_SBDFO (0, DeviceAddress.Address.Bus, 0, 0, ParentCapPtr + 0x4);
        GnbLibPciRead (PciAddress, AccessWidth8, &PMData8, (AMD_CONFIG_PARAMS *) NULL);
        OrgPMData8 = PMData8;
      }

      PcieCapPtr = GnbLibFindPciCapability (DeviceAddress.AddressValue, PCIE_CAP_ID, NULL);
      if (PcieCapPtr != 0) {
        PciAddress2 = MAKE_SBDFO (0, DeviceAddress.Address.Bus, 0, 0, PcieCapPtr + 0x10);
        GnbLibPciRead (PciAddress2, AccessWidth8, &ASPMData8, (AMD_CONFIG_PARAMS *) NULL);

        OrgAspmData8 = ASPMData8;
        // Disable device ASPM as 0;
        ASPMData8 = ASPMData8 & 0xFFFFFFFC;
        GnbLibPciWrite (PciAddress2, AccessWidth8, &ASPMData8, (AMD_CONFIG_PARAMS *) NULL);

        LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
        SmuArg[1] = DxioPcieEngine;
        SmuArg[2] = DxioGen2;
        SmuArg[3] = Engine->Type.Port.PcieBridgeId;
        NbioDxioServiceRequestV10 (NbioHandle, DXIO_MSG_PHYS_TARGETFREQUPDATE | (DXIO_freqUpdType_single << 10), SmuArg, GNB_REG_ACC_FLAG_S3SAVE);

        GnbLibPciWrite (PciAddress2, AccessWidth8, &OrgAspmData8, (AMD_CONFIG_PARAMS *) NULL);
        GnbLibPciWrite (PciAddress, AccessWidth8, &OrgPMData8, (AMD_CONFIG_PARAMS *) NULL);

        IDS_HDT_CONSOLE (GNB_TRACE, "  Engine->Type.Port.PcieBridgeId: %x\n", Engine->Type.Port.PcieBridgeId);

        //check current link state

        PciAddress3 = MAKE_SBDFO (0, DeviceAddress.Address.Bus, 0, 0, PcieCapPtr + 0x12);
        GnbLibPciRead (PciAddress3, AccessWidth8, &CurrentLinkSpeed8, (AMD_CONFIG_PARAMS *) NULL);

        IDS_HDT_CONSOLE (GNB_TRACE, "  PciAddress3: %x\n", PciAddress3);

        IDS_HDT_CONSOLE (GNB_TRACE, "  CurrentLinkSpeed8: %x\n", CurrentLinkSpeed8);
        IDS_HDT_CONSOLE (GNB_TRACE, "  CurrentLinkSpeed8 & (0xF): %x\n", CurrentLinkSpeed8 & (0xF));

        while ( (CurrentLinkSpeed8 & (0xF)) != 0x2) {
          // Send again
          LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
          SmuArg[1] = DxioPcieEngine;
          SmuArg[2] = DxioGen2;
          SmuArg[3] = Engine->Type.Port.PcieBridgeId;
          NbioDxioServiceRequestV10 (NbioHandle, DXIO_MSG_PHYS_TARGETFREQUPDATE | (DXIO_freqUpdType_single << 10), SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
          WatchDogCounter++;
          GnbLibPciRead (PciAddress3, AccessWidth8, &CurrentLinkSpeed8, (AMD_CONFIG_PARAMS *) NULL);

          IDS_HDT_CONSOLE (GNB_TRACE, "  CurrentLinkSpeed8: %x\n", CurrentLinkSpeed8);
          IDS_HDT_CONSOLE (GNB_TRACE, "  CurrentLinkSpeed8 & (0xF): %x\n", CurrentLinkSpeed8 & (0xF));
          if (WatchDogCounter == 10) {
            IDS_HDT_CONSOLE (GNB_TRACE, "  WatchDogCounter: %x Change Gen Speed fail \n", WatchDogCounter);
            break;
          }
        }
      }
    }

    if ((PsppDeviceType != DumbDevice) && (PsppMode == DxioPsppBalanced)) {
      TargetSpeed = Engine->Type.Port.PortData.LinkSpeedCapability;
      if (TargetSpeed == DxioGenMaxSupported) {
        TargetSpeed = DxioGen3;
      }
      NbioRegisterRead (NbioHandle, TYPE_SMN, PCIE_LC_SPEED_CNTL_ADDRESS + (Engine->Type.Port.PortId << 12), &LcSpeedCntl.Value, 0);

      if (TargetSpeed == DxioGen3) {
        if (LcSpeedCntl.Field.LC_OTHER_SIDE_SUPPORTS_GEN3 == 0) {
          IDS_HDT_CONSOLE (GNB_TRACE, "  Other side does not support Gen3\n", DeviceAddress.Address.Bus, VendorId, DeviceId, DeviceType >> 24);
          TargetSpeed = DxioGen2;
        }
      }

      if (TargetSpeed == DxioGen2) {
        if (LcSpeedCntl.Field.LC_OTHER_SIDE_SUPPORTS_GEN2 == 0) {
          IDS_HDT_CONSOLE (GNB_TRACE, "  Other side does not support Gen2\n", DeviceAddress.Address.Bus, VendorId, DeviceId, DeviceType >> 24);
          TargetSpeed = DxioGen1;
        }
      }

      if (TargetSpeed != DxioGen1) {
        LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
        SmuArg[1] = DxioPcieEngine;
        SmuArg[2] = TargetSpeed;
        SmuArg[3] = Engine->Type.Port.PcieBridgeId;
        NbioDxioServiceRequestV10 (NbioHandle, DXIO_MSG_PHYS_TARGETFREQUPDATE | (DXIO_freqUpdType_single << 10), SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
      }
    }
  }
}


/**
 *---------------------------------------------------------------------------------------
 *  APlusAConfigV10
 *
 *  Description:
 *     Configure SMU for A Plus A Graphics Config
 *  Parameters:
 *    @param[in]     Event
 *    @param[in]     *Context
 *
 *    @retval         VOID
 *
 *---------------------------------------------------------------------------------------
 **/

VOID
AmdPsppConfig (
  IN       PCIe_PLATFORM_CONFIG       *Pcie
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "AmdPsppConfig Entry\n");

  // Only need special config for Balanced Mode
  if (AgesaPsppDisabled != PcdGet8 (PcdPsppPolicy)) {
    PcieConfigRunProcForAllEngines (
        DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
        AmdPsppCallback,
        NULL,
        Pcie
        );
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "AmdPsppConfig Exit\n");
  return;
}


