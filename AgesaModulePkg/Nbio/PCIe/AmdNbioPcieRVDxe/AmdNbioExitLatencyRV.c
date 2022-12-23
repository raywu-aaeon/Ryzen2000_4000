/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to Set PCIe topology segment L0s exit latency
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
* Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
*
* AMD is granting You permission to use this software and documentation (if
* any) (collectively, the "Software") pursuant to the terms and conditions of
* the Software License Agreement included with the Software. If You do not have
* a copy of the Software License Agreement, contact Your AMD representative for
* a copy.
*
* You agree that You will not reverse engineer or decompile the Software, in
* whole or in part, except as allowed by applicable law.
*
* WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
* ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
* INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
* ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
* ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
* warranties, so the above exclusion may not apply to You, but only to the
* extent required by law.
*
* LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
* APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
* LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
* CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
* OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
* ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
* INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
* LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
* FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
* INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
* PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
* You for all damages, losses, and causes of action (whether in contract, tort
* (including negligence) or otherwise) exceed the amount of $50 USD. You agree
* to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
* and their respective licensors, directors, officers, employees, affiliates or
* agents from and against any and all loss, damage, liability and other
* expenses (including reasonable attorneys' fees), resulting from Your
* possession or use of the Software or violation of the terms and conditions of
* this Agreement.
*
* U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
* Software and related documentation are "commercial items", as that term is
* defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
* software" and "commercial computer software documentation", as such terms are
* used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
* respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
* 227.7202-1 through 227.7202-4, as applicable, the commercial computer
* software and commercial computer software documentation are being licensed to
* U.S. Government end users: (a) only as commercial items, and (b) with only
* those rights as are granted to all other end users pursuant to the terms and
* conditions set forth in this Agreement. Unpublished rights are reserved under
* the copyright laws of the United States.
*
* EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
* laws and regulations, as well as the import/export control laws and
* regulations of other countries as applicable. You further agree You will not
* export, re-export, or transfer, directly or indirectly, any product,
* technical data, software or source code received from AMD under this license,
* or the direct product of such technical data or software to any country for
* which the United States or any other applicable government requires an export
* license or other governmental approval without first obtaining such licenses
* or approvals, or in violation of any applicable laws or regulations of the
* United States or the country where the technical data or software was
* obtained. You acknowledges the technical data and software received will not,
* in the absence of authorization from U.S. or local law and regulations as
* applicable, be used by or exported, re-exported or transferred to: (i) any
* sanctioned or embargoed country, or to nationals or residents of such
* countries; (ii) any restricted end-user as identified on any applicable
* government end-user list; or (iii) any party where the end-use involves
* nuclear, chemical/biological weapons, rocket systems, or unmanned air
* vehicles.  For the most current Country Group listings, or for additional
* information about the EAR or Your obligations under those regulations, please
* refer to the website of the U.S. Bureau of Industry and Security at
* http://www.bis.doc.gov/.
*******************************************************************************
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <GnbDxio.h>
#include <OptionGnb.h>
#include <Filecode.h>
#include <Library/IdsLib.h>
#include <Library/GnbPcieConfigLib.h>
#include <Library/GnbCommonLib.h>
#include <Library/NbioHandleLib.h>
#include <GnbRegistersRV.h>
#include <Library/NbioRegisterAccLib.h>

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVDXE_AMDNBIOEXITLATENCYRV_FILECODE

//<Embedded_Override_Start>
/*----------------------------------------------------------------------------------------*/
/**
 * FALSE - RV2
 * TRUE  - RV
 */
BOOLEAN
CheckRvOpn (
  )
{
  UINT32  TempData32;

  TempData32 = (PcdGet32 (PcdGetRVFamilyOPN) >> 30) & 0x3;

  if ((TempData32 == RV1_SINGLE_SOURCE) || (TempData32 == RV1_B4_DUAL_SOURCE)) {
    return TRUE;
  }
  return FALSE;
}
//<Embedded_Override_End>
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

typedef struct {
  GNB_PCI_SCAN_DATA ScanData;
  PCI_ADDR          DownstreamPort;
  UINT16            L1ExitLatency;
  BOOLEAN           BlackList;
} PCIE_EXIT_LATENCY_DATA;

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
  IN       PCIE_EXIT_LATENCY_DATA *LinkL1ExitLatency
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
      break;
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
PcieL1ExitLatencyCallback (
  IN       PCI_ADDR             Device,
  IN OUT   GNB_PCI_SCAN_DATA    *ScanData
  )
{
  SCAN_STATUS             ScanStatus;
  PCIE_EXIT_LATENCY_DATA  *PcielinkData;
  PCIE_DEVICE_TYPE        DeviceType;

  ScanStatus = SCAN_SUCCESS;
  PcielinkData = (PCIE_EXIT_LATENCY_DATA *) ScanData;
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
PcieLinkL1ExitLatency (
  IN       PCIe_ENGINE_CONFIG      *Engine,
  IN OUT   UINT16                  *L1ExitLatency
  )
{
  PCIE_EXIT_LATENCY_DATA PcieL1ExitLatencyData;

  PcieL1ExitLatencyData.ScanData.StdHeader = NULL;
  PcieL1ExitLatencyData.ScanData.GnbScanCallback = PcieL1ExitLatencyCallback;
  PcieL1ExitLatencyData.L1ExitLatency = 0xFFFF;
  PcieL1ExitLatencyData.DownstreamPort = Engine->Type.Port.Address;
  PcieL1ExitLatencyData.BlackList = FALSE;
  GnbLibPciScan (Engine->Type.Port.Address, Engine->Type.Port.Address, &PcieL1ExitLatencyData.ScanData);
  *L1ExitLatency = PcieL1ExitLatencyData.L1ExitLatency;

  return PcieL1ExitLatencyData.BlackList;
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to set L1 Exit Latency
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
PcieL1ExitLatencyInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  UINT32                 Index;
  UINT32                 Value;
  UINT16                 L1ExitLatency;
  PCIe_ENGINE_CONFIG     *PcieEngine;
  PCIe_WRAPPER_CONFIG    *PcieWrapper;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieL1ExitLatencyInterface Enter\n");
  L1ExitLatency = 0xFFFF;
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine) && PcieConfigCheckPortStatus (PcieEngine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
        if (TRUE == PcieLinkL1ExitLatency (PcieEngine, (UINT16*)&L1ExitLatency)) {
          if (L1ExitLatency != 0xFFFF) {
            IDS_HDT_CONSOLE (GNB_TRACE, "  Found Low power PT Device, set L1ExitLatency = %d to Device = %d:%d:%d\n", 
                              L1ExitLatency,
                              PcieEngine->Type.Port.Address.Address.Bus,
                              PcieEngine->Type.Port.Address.Address.Device,
                              PcieEngine->Type.Port.Address.Address.Function
                              );
            //<Embedded_Override_Start>
            //STRAP_BIF_L1_EXIT_LATENCY_A offset values are different for RV1 and RV2.Update the strap index value accordingly
            if(CheckRvOpn()) {
              Index = ( FUSE_ACCESS_LOCATION + STRAP_BIF_L1_EXIT_LATENCY_A_OFFSET_RV1 ) + (PcieEngine->Type.Port.PortId * 0x51);
            }
            else {
              Index = ( FUSE_ACCESS_LOCATION + STRAP_BIF_L1_EXIT_LATENCY_A_OFFSET_RV2 ) + (PcieEngine->Type.Port.PortId * 0x51);
            }
            //<Embedded_Override_End>
            NbioRegisterWrite (GnbHandle,
                               TYPE_SMN,
                               PCIE0_STRAP_INDEX_ADDRESS,
                               &Index,
                               0
                               );
            Value = L1ExitLatency;
            NbioRegisterWrite (GnbHandle,
                               TYPE_SMN,
                               PCIE0_STRAP_DATA_ADDRESS,
                               &Value,
                               0
                               );
          }
        }
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieL1ExitLatencyInterface Exit\n");
}

