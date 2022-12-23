/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe port remapping functions.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 276746 $   @e \$Date: 2014-10-28 12:22:52 -0600 (Mon, 28 Oct 2013) $
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
#include <AMD.h>
#include <Gnb.h>
#include <PiPei.h>
#include <Filecode.h>
#include <GnbRegistersRV.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/TimerLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcieConfigLib.h>

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVPEI_PCIEREMAPRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

#define DEVFUNC(d, f) ((((UINT8) d) << 3) | ((UINT8) f))

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                     L O C A L   D A T A   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

UINT8 ROMDATA DefaultPortDevMapRV [] = {
  DEVFUNC (1, 1),
  DEVFUNC (1, 2),
  DEVFUNC (1, 3),
  DEVFUNC (1, 4),
  DEVFUNC (1, 5),
  DEVFUNC (1, 6),
  DEVFUNC (1, 7)
};

/*----------------------------------------------------------------------------------------*/
/**
 * Check if engine can be remapped to Device/function number requested by user
 * defined engine descriptor
 *
 *   Function only called if requested device/function does not much native device/function
 *
 * @param[in]  DevFunc             PCI Device(7:3) and Func(2:0)
 * @retval     TRUE                Descriptor can be mapped to engine
 * @retval     FALSE               Descriptor can NOT be mapped to engine
 */

BOOLEAN
PcieCheckPortPciDeviceMapping (
  IN      UINT8         DevFunc
  )
{
  UINT8                 Index;
  for (Index = 0; Index < (sizeof (DefaultPortDevMapRV) / sizeof (DefaultPortDevMapRV[0])); Index++) {
    if (DefaultPortDevMapRV[Index] == DevFunc) {
      return TRUE;
    }
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Map engine to specific PCI device address
 *
 *
 *
 * @param[in]  Engine              Pointer to engine configuration
 * @param[in]  PortDevMap          Pointer to PortDevMap
 * @retval     AGESA_ERROR         Fail to map PCI device address
 * @retval     AGESA_SUCCESS       Successfully allocate PCI address
 */

AGESA_STATUS
PcieMapPortPciAddress (
  IN      PCIe_ENGINE_CONFIG     *Engine,
  IN      UINT8*                 PortDevMap
  )
{
  AGESA_STATUS            Status;
  UINT8                   DevFunc;
  UINT8                   Index;
  Status = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMapPortPciAddress Enter\n");
  if (Engine->Type.Port.PortData.DeviceNumber == 0 && Engine->Type.Port.PortData.FunctionNumber == 0) {
    Engine->Type.Port.PortData.DeviceNumber = Engine->Type.Port.NativeDevNumber;
    Engine->Type.Port.PortData.FunctionNumber = Engine->Type.Port.NativeFunNumber;
  }

  DevFunc = (Engine->Type.Port.PortData.DeviceNumber << 3) | Engine->Type.Port.PortData.FunctionNumber;
  if (PcieCheckPortPciDeviceMapping (DevFunc) != TRUE) {
    Status = AGESA_ERROR;
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "    Device %x, Function %x\n", Engine->Type.Port.PortData.DeviceNumber, Engine->Type.Port.PortData.FunctionNumber);
    for (Index = 0; Index < sizeof (DefaultPortDevMapRV); ++Index) {
      if (PortDevMap[Index] == DevFunc) {
        Status = AGESA_ERROR;
        break;
      }
    }
  }
  if (Status == AGESA_SUCCESS) {
    PortDevMap[Engine->Type.Port.PortId] = DevFunc;
    IDS_HDT_CONSOLE (GNB_TRACE, "    PortDevMap DevFunc 0x%x, for PortId %d\n", DevFunc, Engine->Type.Port.PortId);
  }
  for (Index = 0; Index < sizeof (DefaultPortDevMapRV); ++Index) {
    if (DevFunc == DefaultPortDevMapRV[Index]) {
      Engine->Type.Port.LogicalBridgeId = Index;
      IDS_HDT_CONSOLE (GNB_TRACE, "    LogicalBridgeId = %x\n", Index);
      break;
    }
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMapPortPciAddress Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Map engine to specific PCI device address
 *
 *
 * @param[in]  GnbHandle           Pointer to the Silicon Descriptor for this node
 * @param[in]  PortDevMap          Pointer to PortDevMap
 */

VOID
PcieSetPortPciAddressMap (
  IN      GNB_HANDLE    *GnbHandle,
  IN      UINT8         *PortDevMap
  )
{
  UINT8                       Index;
  UINT8                       DevFuncIndex;
  UINT8                       PortDevMapLocal [sizeof (DefaultPortDevMapRV)];
  SMN_0x13B100C0_STRUCT       DeviceRemap;
  PCIE_TX_REQUESTER_ID_STRUCT TxRequester;
  UINT32                      Value;

  LibAmdMemCopy ((VOID*) PortDevMapLocal, (VOID*) DefaultPortDevMapRV, sizeof (DefaultPortDevMapRV), (AMD_CONFIG_PARAMS *) NULL);
  for (Index = 0; Index < sizeof (DefaultPortDevMapRV); ++Index) {
    if (PortDevMap[Index] != 0) {
      for (DevFuncIndex = 0; DevFuncIndex < sizeof (DefaultPortDevMapRV); ++DevFuncIndex) {
        if (PortDevMapLocal[DevFuncIndex] == PortDevMap[Index]) {
          PortDevMapLocal[DevFuncIndex] = 0;
          break;
        }
      }
    }
  }
  for (Index = 0; Index < sizeof (DefaultPortDevMapRV); ++Index) {
    if (PortDevMap[Index] == 0) {
      for (DevFuncIndex = 0; DevFuncIndex < sizeof (DefaultPortDevMapRV); ++DevFuncIndex) {
        if (PortDevMapLocal[DevFuncIndex] != 0) {
          PortDevMap[Index] = PortDevMapLocal[DevFuncIndex];
          PortDevMapLocal[DevFuncIndex] = 0;
          break;
        }
      }
    }
    NbioRegisterRead (GnbHandle, SMN_0x13B100C0_TYPE, SMN_0x13B100C0_ADDRESS + (Index << 2), &DeviceRemap.Value, 0);
    DeviceRemap.Field.DevFnMap = PortDevMap[Index];
    NbioRegisterWrite (GnbHandle, SMN_0x13B100C0_TYPE, SMN_0x13B100C0_ADDRESS + (Index << 2), &DeviceRemap.Value, 0);

    NbioRegisterRead (GnbHandle, PCIE_TX_REQUESTER_ID_TYPE, PCIE_TX_REQUESTER_ID_ADDRESS + (Index << 12), &TxRequester.Value, 0);
    TxRequester.Field.TxRequesterIdDevice = PortDevMap[Index] >> 3;
    TxRequester.Field.TxRequesterIdBus = 0;
    NbioRegisterWrite (GnbHandle, PCIE_TX_REQUESTER_ID_TYPE, PCIE_TX_REQUESTER_ID_ADDRESS + (Index << 12), &TxRequester.Value, 0);

    NbioRegisterRead (GnbHandle, PCIEP_HW_DEBUG_TYPE, PCIE0_PCIEP_HW_DEBUG_ADDRESS + (Index << 12), &Value, 0);
    Value &= ~(0x7);
    Value |= (PortDevMap[Index] & 0x7);
    DeviceRemap.Field.DevFnMap = PortDevMap[Index];
    NbioRegisterWrite (GnbHandle, PCIEP_HW_DEBUG_TYPE, PCIE0_PCIEP_HW_DEBUG_ADDRESS + (Index << 12), &Value, 0);

  }
}



