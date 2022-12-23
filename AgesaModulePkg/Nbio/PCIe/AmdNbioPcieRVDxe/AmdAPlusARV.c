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
#include <GnbRegistersZP.h>
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

#include <AmdPcieComplex.h>

#define FILECODE        NBIO_PCIE_AMDNBIOSPCIERVDXE_AMDAPLUSARV_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

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

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
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

VOID
STATIC
AmdAPlusACallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT32                SecondaryAddress;
  PCI_ADDR              DeviceAddress;
  UINT32                VendorDeviceId;
  UINT32                DeviceId;
  UINT32                VendorId;
  UINT32                DeviceApertureLo;
  UINT32                DeviceApertureHi;
  UINT32                DeviceType;
  GNB_HANDLE            *NbioHandle;
  UINT32                SmuStatus;
  UINT32                Index;
  UINT32                SmuArg[6];

  NbioHandle = (GNB_HANDLE *) PcieConfigGetParentSilicon (Engine);

  GnbLibPciRead (Engine->Type.Port.Address.AddressValue | 0x18, AccessWidth32, &SecondaryAddress, (AMD_CONFIG_PARAMS *) NULL);
  DeviceAddress.AddressValue = 0;
  DeviceAddress.Address.Bus = (SecondaryAddress >> 8) & 0xFF;
  IDS_HDT_CONSOLE (GNB_TRACE, "Checking secondary bus %x\n", SecondaryAddress);

  if ((DeviceAddress.Address.Bus != 0xFF) && (DeviceAddress.Address.Bus != 0x0)) {
    GnbLibPciRead(DeviceAddress.AddressValue, AccessWidth32, &VendorDeviceId, (AMD_CONFIG_PARAMS *)NULL);
    GnbLibPciRead (DeviceAddress.AddressValue | 0x08, AccessWidth32, &DeviceType, (AMD_CONFIG_PARAMS *) NULL);
    VendorId = VendorDeviceId & 0xFFFF;
    DeviceId = VendorDeviceId >> 16;
    IDS_HDT_CONSOLE (GNB_TRACE, "  Read device info on bus %d Vendor:%x Device %x and DeviceType\n", DeviceAddress.Address.Bus, VendorId, DeviceId, DeviceType >> 24);
    if (((VendorId == 0x1002) || (VendorId == 0x1022)) && ((DeviceType >> 24) == 3)) {
      // We found an ATI/AMD Display Controller, so notify SMU
      IDS_HDT_CONSOLE (GNB_TRACE, "  dGPU located on bus %d Vendor:%x Device %x\n", DeviceAddress.Address.Bus, VendorId, DeviceId);
      for (Index = 0x10; Index < 0x30; Index += 4) {
        GnbLibPciRead (DeviceAddress.AddressValue | Index, AccessWidth32, &DeviceApertureLo, (AMD_CONFIG_PARAMS *)NULL);
        // Look for non-prefetchable memory BAR
        if ((DeviceApertureLo & 0x9) == 0) {
          if ((DeviceApertureLo & 0x6) == 0x4) {
            Index += 4;
            GnbLibPciRead (DeviceAddress.AddressValue | Index, AccessWidth32, &DeviceApertureHi, (AMD_CONFIG_PARAMS *)NULL);
          } else {
            DeviceApertureHi = 0;
          }
          //
          // Notify SMU of the dGPU ID and Aperture
          //
          NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
          SmuArg[0] = DeviceId;
          SmuStatus = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetGpuDeviceId, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
          if (SmuStatus == BIOSSMC_Result_OK) {
            NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
            SmuArg[0] = DeviceApertureLo & 0xFFFFFFF0;
            SmuStatus = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetGpuApertureLow, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
            NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
            SmuArg[0] = DeviceApertureHi;
            SmuStatus = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_SetGpuApertureHigh, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
            NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
            SmuArg[1] = 1 << (42 - 32);
            SmuStatus = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_EnableSmuFeatures, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
            NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
            SmuStatus = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (NbioHandle), SMC_MSG_StartGpuLink, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
          }
          break;
        } else if ((DeviceApertureLo & 0x6) == 0x4) {
          // 64 bit memory address - skip upper dword of BAR
          Index += 4;
        }
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
 *    @param[in]     Pcie   PCIe_PLATFORM_CONFIG pointer
 *
 *    @retval         VOID
 *
 *---------------------------------------------------------------------------------------
 **/

VOID
AmdAPlusAConfig (
  IN       PCIe_PLATFORM_CONFIG       *Pcie
  )

{
  IDS_HDT_CONSOLE (GNB_TRACE, "APlusAConfigV10 Entry\n");

  if (PcdGet8 (PcdCfgPeApmEnable) != 0) {
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
      AmdAPlusACallback,
      NULL,
      Pcie
      );
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "APlusAConfigV10 Exit\n");
  return;
}





