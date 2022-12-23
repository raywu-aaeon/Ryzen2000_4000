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
#include  <Library/AmdBaseLib.h>
#include  <Library/GnbPcieConfigLib.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/PcieMiscCommLib.h>
#include  <GnbRegistersRV.h>
#include  <Library/NbioRegisterAccLib.h>

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVDXE_AMDNBIOPCIECLKREQRV_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
typedef struct {
  GNB_PCI_SCAN_DATA       ScanData;
  PCI_ADDR                DownstreamPort;
} PCIE_CLKREQ_PMM_DATA;

#define GPPClkCntrl_ADDRESS                      0x02D01E00UL
/// GPPClkCntrl
typedef union {
  struct {
    UINT32                  GPP_CLK0_Clock_Request_mapping:2 ; ///<
    UINT32                  GPP_CLK1_Clock_Request_mapping:2 ; ///<
    UINT32                  GPP_CLK4_Clock_Request_mapping:2 ; ///<
    UINT32                  GPP_CLK2_Clock_Request_mapping:2 ; ///<
    UINT32                  GPP_CLK3_Clock_Request_mapping:2 ; ///<
    UINT32                  GPP_CLK5_Clock_Request_mapping:2 ; ///<
    UINT32                  GPP_CLK6_Clock_Request_mapping:2 ; ///<
    UINT32                                  Reserved_31_14:18; ///<
  } Field;                                                     ///<
  UINT32 Value;                                                ///< @todo comments
} GPP_CLK_CNTRL;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
#define NUMBER_OF_CLKREQB        8
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                     L O C A L   D A T A   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

UINT8 ROMDATA DefaultClkReqMapCntlRV [NUMBER_OF_CLKREQB][2] = {
  {0xFF, 0},    // CLKREQB_0
  {0xFF, 1},    // CLKREQB_1
  {0xFF, 2},    // CLKREQB_2
  {0xFF, 3},    // CLKREQB_3
  {0xFF, 4},    // CLKREQB_4
  {0xFF, 5},    // CLKREQB_5
  {0xFF, 6},    // CLKREQB_6
  {0xFF, 7},    // CLKREQB_7
};

VOID
UpdateClkReqMapCntl ()
{
  UINT8                 Index;
  UINT8                 Index1;
  UINT8                 data0;

  for (Index = 0; Index < NUMBER_OF_CLKREQB; Index++) {
    for (Index1 = 0; Index1 < NUMBER_OF_CLKREQB; Index1++) {
      if (DefaultClkReqMapCntlRV[Index1][0] == Index) {
        data0 = DefaultClkReqMapCntlRV[Index][1];
        DefaultClkReqMapCntlRV[Index][1] = DefaultClkReqMapCntlRV[Index1][1];
        DefaultClkReqMapCntlRV[Index1][1] = data0;

        data0 = DefaultClkReqMapCntlRV[Index][0];
        DefaultClkReqMapCntlRV[Index][0] = DefaultClkReqMapCntlRV[Index1][0];
        DefaultClkReqMapCntlRV[Index1][0] = data0;

        DefaultClkReqMapCntlRV[Index][0] = 0xFF;
      }
    }
  }
  for (Index = 0; Index < NUMBER_OF_CLKREQB; Index++) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PORT_%d_CLKREQB_MAP: 0x%x - %d\n", Index, DefaultClkReqMapCntlRV[Index][0], DefaultClkReqMapCntlRV[Index][1]);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set CLOCK_POWER_MANAGEMENT_EN on PCIe device function
 *
 *
 *
 * @param[in] AddressValue    PCI address of function.
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
PcieClkReqPmmEnable (
  IN       UINT32            AddressValue
  )
{
  UINT8       PcieCapPtr;
  UINT32      Value;
  PcieCapPtr = GnbLibFindPciCapability (AddressValue, PCIE_CAP_ID, NULL);
  if (PcieCapPtr != 0) {
    GnbLibPciRead (AddressValue | (PcieCapPtr + PCIE_LINK_CAP_REGISTER), AccessWidth32, &Value, NULL);
    Value &= BIT18;
    // Check CLOCK_POWER_MANAGEMENT is Supported
    if (Value != 0) {
      // CLOCK_POWER_MANAGEMENT_EN set to Enable
      GnbLibPciRMW (
      AddressValue | (PcieCapPtr + PCIE_LINK_CTRL_REGISTER) ,
      AccessS3SaveWidth32,
      ~(UINT32)BIT8,
      BIT8,
      NULL
      );
    }
  }
}

SCAN_STATUS
SetPcieClkReqPmmEnableCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS             ScanStatus;
  PCIE_CLKREQ_PMM_DATA    *PcieClkReqPmmData;
  PCIE_DEVICE_TYPE        DeviceType;

  ScanStatus = SCAN_SUCCESS;
  PcieClkReqPmmData = (PCIE_CLKREQ_PMM_DATA *) ScanData;
  IDS_HDT_CONSOLE (GNB_TRACE, "  SetPcieClkReqPmmEnableCallback for Device = %d:%d:%d\n",
    Device.Address.Bus,
    Device.Address.Device,
    Device.Address.Function
    );
  DeviceType = GnbLibGetPcieDeviceType (Device, ScanData->StdHeader);
  switch (DeviceType) {
  case  PcieDeviceRootComplex:
  case  PcieDeviceDownstreamPort:
  case  PcieDeviceUpstreamPort:
    IDS_HDT_CONSOLE (GNB_TRACE, "  PcieDeviceRootComplex/PcieDeviceDownstreamPort/PcieDeviceUpstreamPort %d\n", DeviceType);
    GnbLibPciScanSecondaryBus (Device, &PcieClkReqPmmData->ScanData);
    break;
  case  PcieDeviceEndPoint:
  case  PcieDeviceLegacyEndPoint:
    IDS_HDT_CONSOLE (GNB_TRACE, "  PcieDeviceEndPoint %d\n", DeviceType);
    PcieClkReqPmmEnable (Device.AddressValue);
    break;
  default:
    IDS_HDT_CONSOLE (GNB_TRACE, "  Unknow DeviceType %d\n", DeviceType);
    break;
  }
  return ScanStatus;
}

VOID
PcieClkReqPmmEnableCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  PCIE_CLKREQ_PMM_DATA PcieClkReqPmmData;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieClkReqPmmEnableCallback Enter\n");
  PcieClkReqPmmData.ScanData.StdHeader = NULL;
  PcieClkReqPmmData.ScanData.GnbScanCallback = SetPcieClkReqPmmEnableCallback;
  GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieClkReqPmmData.ScanData);

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieClkReqPmmEnableCallback Exit\n");
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
PcieClkReqInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG             *PcieEngine;
  PCIe_WRAPPER_CONFIG            *PcieWrapper;
  PCIE_LC_PM_CNTL_STRUCT         NBIO_PCIE_LC_PM_CNTL;
  GPP_CLK_CNTRL                  GPP_CLK_CNTRL_MISC;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieClkReqInterface Enter\n");

  NbioRegisterRead ( GnbHandle, TYPE_SMN, GPPClkCntrl_ADDRESS, &GPP_CLK_CNTRL_MISC.Value, 0);
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if ((PcieLibIsEngineAllocated (PcieEngine)) &&
          (PcieConfigCheckPortStatus (PcieEngine, INIT_STATUS_PCIE_TRAINING_SUCCESS))) {
        if (PcieEngine->Type.Port.PortData.MiscControls.ClkPmSupport == 1) {
          PcieClkReqPmmEnableCallback (PcieEngine, NULL);
        }
        if ((PcieEngine->Type.Port.LinkAspmL1_1 == 1) || (PcieEngine->Type.Port.LinkAspmL1_2 == 1)) {
          if ((PcieEngine->Type.Port.ClkReq != 0) && (PcieEngine->Type.Port.ClkReq <= NUMBER_OF_CLKREQB)) {
            DefaultClkReqMapCntlRV[PcieEngine->Type.Port.ClkReq - 1][0] = PcieEngine->Type.Port.PortId;
            IDS_HDT_CONSOLE (GNB_TRACE, "%d:%d    PortId=%d Clkreq#=%d\n" ,
                             PcieEngine->Type.Port.PortData.DeviceNumber,
                             PcieEngine->Type.Port.PortData.FunctionNumber,
                             PcieEngine->Type.Port.PortId,
                             PcieEngine->Type.Port.ClkReq - 1);
            switch (PcieEngine->Type.Port.ClkReq) {
            case 1:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK0_Clock_Request_mapping = 1;
              break;
            case 2:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK1_Clock_Request_mapping = 1;
              break;
            case 3:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK2_Clock_Request_mapping = 1;
              break;
            case 4:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK3_Clock_Request_mapping = 1;
              break;
            case 5:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK4_Clock_Request_mapping = 1;
              break;
            case 6:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK5_Clock_Request_mapping = 1;
              break;
            case 7:
              GPP_CLK_CNTRL_MISC.Field.GPP_CLK6_Clock_Request_mapping = 1;
              break;
            default:
              break;
            }
          }
        }
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }

  UpdateClkReqMapCntl (DefaultClkReqMapCntlRV[0][0]);
  NbioRegisterRead ( GnbHandle, PCIE_LC_PM_CNTL_TYPE, PCIE_LC_PM_CNTL_ADDRESS, &NBIO_PCIE_LC_PM_CNTL, 0);
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_0_CLKREQB_MAP = DefaultClkReqMapCntlRV[0][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_1_CLKREQB_MAP = DefaultClkReqMapCntlRV[1][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_2_CLKREQB_MAP = DefaultClkReqMapCntlRV[2][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_3_CLKREQB_MAP = DefaultClkReqMapCntlRV[3][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_4_CLKREQB_MAP = DefaultClkReqMapCntlRV[4][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_5_CLKREQB_MAP = DefaultClkReqMapCntlRV[5][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_6_CLKREQB_MAP = DefaultClkReqMapCntlRV[6][1];
  NBIO_PCIE_LC_PM_CNTL.Field.LC_PORT_7_CLKREQB_MAP = DefaultClkReqMapCntlRV[7][1];
  NbioRegisterWrite (GnbHandle, PCIE_LC_PM_CNTL_TYPE, PCIE_LC_PM_CNTL_ADDRESS, &NBIO_PCIE_LC_PM_CNTL, GNB_REG_ACC_FLAG_S3SAVE);
  NbioRegisterWrite (GnbHandle, TYPE_SMN, GPPClkCntrl_ADDRESS, &GPP_CLK_CNTRL_MISC.Value, GNB_REG_ACC_FLAG_S3SAVE);

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieClkReqInterface Exit\n");
}


