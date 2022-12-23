/* $NoKeywords:$ */
/**
 * @file
 *
 * DxioCfgPointsRV - Configuration entry points for the DXIO subsystem
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioBaseRVPei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
 */
/*****************************************************************************
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
 */
#include <AMD.h>
#include <Gnb.h>
#include <PiPei.h>
#include <Filecode.h>
#include <GnbDxio.h>
#include <GnbRegistersRV.h>

//From AgesaPkg
#include <AmdPcieComplex.h>
#include <Ppi/NbioPcieComplexPpi.h>


#include "AmdNbioPcieRVPei.h"

#include <Guid/GnbPcieInfoHob.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Ppi/NbioPcieTrainingPpi.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/SocLogicalIdPpi.h>
#include <Library/PeiServicesLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/NbioHandleLib.h>
//Dependent on AgesaPkg
#include <Library/DxioLibV1.h>
#include <IdsHookId.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioAzaliaLib.h>
#include <Library/GnbPciAccLib.h>
#include <Library/GnbLib.h>
#include <CcxRegistersRV.h>

#define FILECODE        NBIO_PCIE_AMDNBIOPCIERVPEI_DXIOCFGPOINTSRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

// Comment this line to enable extended debug output if tracing is enabled
#undef GNB_TRACE_ENABLE

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
BOOLEAN CheckRvOpn(VOID);

//=========================================================================================
// Timepoint after port mapping and before reconfig
//=========================================================================================

/*----------------------------------------------------------------------------------------*/
/**
 * Per-Engine Callback for
 *
 *
 *
 * @param[in]     Engine  Engine configuration info
 * @param[in,out] Buffer  Buffer pointer
 * @param[in]     Pcie    PCIe configuration info
 */
VOID
STATIC
DxioCfgBeforeReconfigCallback (
  IN       GNB_HANDLE            *GnbHandle,
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "DxioCfgBeforeReconfigCallback Enter\n");
  return;
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to configure DXIO/PCIe ports after ports are mapped and before reconfig
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/

VOID
DxioCfgBeforeReconfig (
  IN       GNB_HANDLE       *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG        *PcieEngine;
  PCIe_WRAPPER_CONFIG       *PcieWrapper;

  IDS_HDT_CONSOLE (GNB_TRACE, "DxioCfgBeforeReconfig Enter\n");
  IDS_HOOK (IDS_HOOK_NBIO_PCIE_TOPOLOGY, (VOID *) GnbHandle, (VOID *) NULL);

  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      DxioCfgBeforeReconfigCallback (GnbHandle, PcieEngine, NULL );
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  return;
}


//=========================================================================================
// Timepoint after reconfig and before port training
//=========================================================================================

/*----------------------------------------------------------------------------------------*/
/**
 * Per-Engine Callback for
 *
 *
 *
 * @param[in]     Engine  Engine configuration info
 * @param[in,out] Buffer  Buffer pointer
 * @param[in]     Pcie    PCIe configuration info
 */
VOID
STATIC
DxioCfgAfterReconfigCallback (
  IN       GNB_HANDLE            *GnbHandle,
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  PCI_ADDR                            PciAddress;
  UINT16                              Index;
  PCIE_LANE_EQUALIZATION_CNTL_STRUCT  LaneEq;
  UINT32                              Value32;

  if (PcieLibIsEngineAllocated(Engine)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "DxioCfgAfterReconfigCallback Enter\n");
    IDS_HDT_CONSOLE (GNB_TRACE, "DsTxPreset = 0x%x\n", Engine->Type.Port.LaneEqualizationCntl.DsTxPreset);
    IDS_HDT_CONSOLE (GNB_TRACE, "DsRxPresetHint = 0x%x\n", Engine->Type.Port.LaneEqualizationCntl.DsRxPresetHint);
    IDS_HDT_CONSOLE (GNB_TRACE, "UsTxPreset = 0x%x\n", Engine->Type.Port.LaneEqualizationCntl.UsTxPreset);
    IDS_HDT_CONSOLE (GNB_TRACE, "UsRxPresetHint = 0x%x\n", Engine->Type.Port.LaneEqualizationCntl.UsRxPresetHint);

    PciAddress.AddressValue = Engine->Type.Port.Address.AddressValue;
    PciAddress.Address.Register = 0x27C;

    if ((Engine->Type.Port.LaneEqualizationCntl.DsTxPreset != 0) &&
       (Engine->Type.Port.LaneEqualizationCntl.DsRxPresetHint != 0) &&
       (Engine->Type.Port.LaneEqualizationCntl.UsTxPreset != 0) &&
       (Engine->Type.Port.LaneEqualizationCntl.UsRxPresetHint != 0)) {
       // CBS override, no need to initial registers
    } else {
      if ((Engine->Type.Port.PortData.LinkSpeedCapability == PcieGen3) ||
        (Engine->Type.Port.PortData.LinkSpeedCapability == PcieGenMaxSupported)) {
        // Gen3 cap enabled
        Engine->Type.Port.LaneEqualizationCntl.DsTxPreset = 7;
        Engine->Type.Port.LaneEqualizationCntl.DsRxPresetHint = 3;
        Engine->Type.Port.LaneEqualizationCntl.UsTxPreset = 7;
        Engine->Type.Port.LaneEqualizationCntl.UsRxPresetHint = 3;
      }
    }
    GnbLibPciRead(PciAddress.AddressValue, AccessWidth16, &LaneEq.Value, NULL);
    LaneEq.Field.DOWNSTREAM_PORT_TX_PRESET = Engine->Type.Port.LaneEqualizationCntl.DsTxPreset;
    LaneEq.Field.DOWNSTREAM_PORT_RX_PRESET_HINT = Engine->Type.Port.LaneEqualizationCntl.DsRxPresetHint;
    LaneEq.Field.UPSTREAM_PORT_TX_PRESET = Engine->Type.Port.LaneEqualizationCntl.UsTxPreset;
    LaneEq.Field.UPSTREAM_PORT_RX_PRESET_HINT = Engine->Type.Port.LaneEqualizationCntl.UsRxPresetHint;
    Value32 = (UINT32) LaneEq.Value + ((UINT32) LaneEq.Value << 16);
    for (Index = 0; Index < 8; Index++) {
      IDS_HDT_CONSOLE (GNB_TRACE, "Writing Address = 0x%x\n", PciAddress.AddressValue);
      GnbLibPciWrite(PciAddress.AddressValue, AccessWidth32, &Value32, NULL);
      PciAddress.Address.Register += 4;
    }

    //
    //Update the STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT , STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT
    //STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET & STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET strap index offset values for RV1 an RV2.
    //
    //<Embedded_Override_Start>
    if(CheckRvOpn()) {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV1;
    } else {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV2;
    }
    //<Embedded_Override_End>
    NbioRegisterWrite (GnbHandle,
                    TYPE_SMN,
                    PCIE0_STRAP_INDEX_ADDRESS,
                    &Value32,
                    0
                    );
    Value32 = Engine->Type.Port.LaneEqualizationCntl.DsRxPresetHint;
    NbioRegisterWrite (GnbHandle,
                    TYPE_SMN,
                    PCIE0_STRAP_DATA_ADDRESS,
                    &Value32,
                    0
                    );

    //<Embedded_Override_Start>
    if(CheckRvOpn()) {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV1;
    } else {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_RX_PRESET_HINT_OFFSET_RV2;
    }
    //<Embedded_Override_End>
    NbioRegisterWrite (GnbHandle,
                      TYPE_SMN,
                      PCIE0_STRAP_INDEX_ADDRESS,
                      &Value32,
                      0
                      );
    Value32 = Engine->Type.Port.LaneEqualizationCntl.UsRxPresetHint;
    NbioRegisterWrite (GnbHandle,
                      TYPE_SMN,
                      PCIE0_STRAP_DATA_ADDRESS,
                      &Value32,
                      0
                      );

    //<Embedded_Override_Start>
    if(CheckRvOpn()) {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_OFFSET_RV1;
    } else {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_DOWNSTREAM_PORT_TX_PRESET_OFFSET_RV2;
    }
    //<Embedded_Override_End>
    NbioRegisterWrite (GnbHandle,
                      TYPE_SMN,
                      PCIE0_STRAP_INDEX_ADDRESS,
                      &Value32,
                      0
                      );
    Value32 = Engine->Type.Port.LaneEqualizationCntl.DsTxPreset;
    NbioRegisterWrite (GnbHandle,
                      TYPE_SMN,
                      PCIE0_STRAP_DATA_ADDRESS,
                      &Value32,
                      0
                      );

    //<Embedded_Override_Start>
    if(CheckRvOpn()) {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_OFFSET_RV1;
    } else {
      Value32 = FUSE_ACCESS_LOCATION + STRAP_BIF_PCIE_LANE_EQUALIZATION_CNTL_UPSTREAM_PORT_TX_PRESET_OFFSET_RV2;
    }
    //<Embedded_Override_End>
    NbioRegisterWrite (GnbHandle,
                      TYPE_SMN,
                      PCIE0_STRAP_INDEX_ADDRESS,
                      &Value32,
                      0
                      );
    Value32 = Engine->Type.Port.LaneEqualizationCntl.UsTxPreset;
    NbioRegisterWrite (GnbHandle,
                      TYPE_SMN,
                      PCIE0_STRAP_DATA_ADDRESS,
                      &Value32,
                      0
                      );
    }
  return;
}

/**----------------------------------------------------------------------------------------*/
/**
 * Interface to configure DXIO/PCIe ports after reconfig and before training
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/

VOID
DxioCfgAfterReconfig (
  IN       GNB_HANDLE       *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG        *PcieEngine;
  PCIe_WRAPPER_CONFIG       *PcieWrapper;
  IDS_HDT_CONSOLE (GNB_TRACE, "DxioCfgAfterReconfig Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      DxioCfgAfterReconfigCallback (GnbHandle, PcieEngine, NULL );
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  return;
}


