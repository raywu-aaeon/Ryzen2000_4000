/* $NoKeywords:$ */
/**
 * @file
 *
 * DxioInitRV - Initialize DXIO subsystem
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
#include <Library/PcieMiscCommLib.h>
//From AgesaPkg
#include <AmdPcieComplex.h>
#include <Ppi/NbioPcieComplexPpi.h>
#include <Ppi/AmdMemoryInfoHobPpi.h>
//Dependent on AgesaPkg
#include <Library/DxioLibV1.h>
#include <IdsHookId.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioAzaliaLib.h>
#include <Library/FabricResourceManagerLib.h>
#include <Library/GnbPciAccLib.h>
#include <Library/GnbLib.h>
#include <Library/SmnAccessLib.h>

#define FILECODE        NBIO_PCIE_AMDNBIOPCIERVPEI_DXIOINITRV_FILECODE
//<Embedded_Override_Start>
#define NBIF0_DCE_AZ_STRAP2_ADDRESS                          (NBIF0_DCE_AZ_STRAP0_ADDRESS + 8)
//<Embedded_Override_End>

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */
#define NBIF1RCCFG_COMMAND_ADDRESS                              0x10100004UL   //Nbif1 B:D:F. 0 8 1
#define NBIF1RCCFG_SUB_BUS_ADDRESS                              0x10100018UL
#define NBIF1RCCFG_BASELIMIT_ADDRESS                            0x10100020UL
#define NBIF1EPF6CFG_VENDOR_ID_ADDRESS                          0x10146000UL    // B:D:F. A 0 6
#define NBIF1EPF6CFG_COMMAND_ADDRESS                            0x10146004UL
#define NBIF1EPF6CFG_BASE_ADDR_1_ADDRESS                        0x10146010UL
#define NBIF1EPF6CFG_ADAPTER_ID_ADDRESS                         0x1014604CUL

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
VOID
KpnpResetWorkaround (
  IN CONST  EFI_PEI_SERVICES   **PeiServices,
  IN        GNB_HANDLE         *GnbHandle
  );

VOID
A0ParallelTrainingWorkaround (
  IN CONST  EFI_PEI_SERVICES         **PeiServices,
  IN        GNB_HANDLE               *GnbHandle,
  IN OUT    DXIO_COMPLEX_DESCRIPTOR  *PcieTopologyData
  );


/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */

STATIC PEI_AMD_NBIO_PCIE_TRAINING_DONE_PPI mNbioPcieTrainingDonePpi = {
  AMD_TRAINING_DONE_STATUS          /// Status
};

STATIC EFI_PEI_PPI_DESCRIPTOR mNbioPcieTrainingDonePpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdNbioPcieTrainingDonePpiGuid,
  &mNbioPcieTrainingDonePpi
};

#define DxioInputParsetGetNextDescriptor(Descriptor) (Descriptor != NULL ? ((((Descriptor->Flags & DESCRIPTOR_TERMINATE_LIST) != 0) ? NULL : (++Descriptor))) : NULL)


/*---------------------------------------------------------------------------------------*/
/**
 * Check RV OPN number
 *
 * @retval    TRUE    This is RV2 B4 part
 *            FALSE   This is not RV2 B4 part
 *
 */
BOOLEAN
CheckRv2OpnB4 (
  )
{
  UINT32              RegisterData;
  UINT32              TempData32;

  SmnRegisterRead (0, SMUFUSEx000005C0_ADDRESS, &RegisterData);
  TempData32 = (RegisterData >> 30) & 0x3;
  if (TempData32 == 3) {
    return TRUE;
  }
  return FALSE;
}
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
/*---------------------------------------------------------------------------------------*/
/**
 * Rv2S3SataWorkaroundr
 *
 * @param[in]       GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
VOID
Rv2S3SataWorkaround (
  IN        GNB_HANDLE         *GnbHandle
  )
{
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    SATA_GLOBAL_OPTION_ADDRESS,
    (UINT32)~(PCS_PHY_global_SW_Reset_Mask),
    0x1 << PCS_PHY_global_SW_Reset_OFFSET,
    0
    );
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    SATA_GLOBAL_OPTION_ADDRESS,
    (UINT32)~(PCS_PHY_global_SW_Reset_Mask),
    0x0 << PCS_PHY_global_SW_Reset_OFFSET,
    0
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enumerate all Pcie connectors for register setting.
 *
 *
 * @param[in]       GnbHandle      Pointer to the Silicon Descriptor for this node
 * @param[in]       Engine         Pointer to engine config descriptor
 * @param[in, out]  Buffer         Not used
 */
VOID
STATIC
PcieIntegratedInterfaceCallback (
  IN       GNB_HANDLE            *GnbHandle,
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  UINT32                            Address;
  UINT8                             MappingPortID;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieIntegratedInterfaceCallback Enter\n");

  MappingPortID = (Engine->Type.Port.PortId) % 8;

  Address = GPP0_TX_CNTL_ADDRESS;
  Address += (MappingPortID * 0x1000);
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32) ~(PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_MASK),
    0 << PCIE_TX_CNTL_TX_FLUSH_TLP_DIS_OFFSET,
    0
    );

  //
  // DynamicLanesPowerState
  // Dynamic Power Down Unused Lanes in Link Width Change needs to be enabled by default, with the aggressive setting of P2
  //
  Address = PCIE0_LC_LINK_WIDTH_CNTL_ADDRESS;
  Address += (MappingPortID * 0x1000);
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(PCIE_LC_LINK_WIDTH_CNTL_LC_DYN_LANES_PWR_STATE_MASK),
    (3 << PCIE_LC_LINK_WIDTH_CNTL_LC_DYN_LANES_PWR_STATE_OFFSET),
    0
    );

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieIntegratedInterfaceCallback Exit\n");

}

/*----------------------------------------------------------------------------------------*/
/**
 * After Pcie Training Enumerate all Pcie connectors for register setting.
 *
 *
 *
 * @param[in]     Engine  Engine configuration info
 * @param[in,out] Buffer  Buffer pointer
 * @param[in]     Pcie    PCIe configuration info
 */
VOID
STATIC
PcieAfterTrainingDoneCallback (
  IN       GNB_HANDLE            *GnbHandle,
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer
  )
{
  PCIe_WRAPPER_CONFIG               *Wrapper;
  UINT32                            Address;
  UINT8                             MappingPortID;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAfterTrainingDoneCallback Enter\n");

  Address = Engine->Type.Port.Address.AddressValue;
  if (Address != 0) {
    // Set slot_implemented
    GnbLibPciRMW (
      Engine->Type.Port.Address.AddressValue | DxF0x58_ADDRESS,
      AccessWidth32,
      0xffffffff,
      1 << DxF0x58_SlotImplemented_OFFSET,
      (AMD_CONFIG_PARAMS *) NULL
      );
  }

  Wrapper = PcieConfigGetParentWrapper (Engine);
  MappingPortID = (Engine->Type.Port.PortId) % 8;

  //
  // L1ImmediateACK
  //
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of L1ImmediateACK  = 0x%x\n",Engine->Type.Port.L1ImmediateACK);
  Address = SMN_0x11140280_ADDRESS;
  Address += (MappingPortID * 0x1000);
  IDS_HDT_CONSOLE (GNB_TRACE, "Address L1ImmediateACK  = 0x%x\n",Address);
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(SMN_0x11140280_LC_L1_IMMEDIATE_ACK_MASK),
    (Engine->Type.Port.L1ImmediateACK << SMN_0x11140280_LC_L1_IMMEDIATE_ACK_OFFSET),
    0
    );

  //
  // EqSearchMode (00) Gradient Search  - Not support on ZP, keep it as inactive
  //              (01) Exhaustive Search
  //              (02) Exhaustive Search + 3x3 - Not support on ZP, keep it as inactive
  //              (03) Preset Search
  // DisGen3EQPhase
  // BypassGen3EQ
  //
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of EqSearchMode  = 0x%x\n",Engine->Type.Port.EqSearchMode);
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of DisGen3EQPhase  = 0x%x\n",Engine->Type.Port.DisGen3EQPhase);
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of EqSearchMode  = 0x%x\n",Engine->Type.Port.BypassGen3EQ);

  Address = SMN_0x111402d8_ADDRESS;
  Address += (MappingPortID * 0x1000);
  IDS_HDT_CONSOLE (GNB_TRACE, "Address EqSearchMode  = 0x%x\n", Address);

  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(SMN_0x111402d8_LC_EQ_SEARCH_MODE_MASK |
    SMN_0x111402d8_LC_BYPASS_EQ_MASK |
    SMN_0x111402d8_LC_BYPASS_EQ_REQ_PHASE_MASK),
    (Engine->Type.Port.EqSearchMode << SMN_0x111402d8_LC_EQ_SEARCH_MODE_OFFSET) |
    (Engine->Type.Port.DisGen3EQPhase << SMN_0x111402d8_LC_BYPASS_EQ_OFFSET) |
    (Engine->Type.Port.BypassGen3EQ << SMN_0x111402d8_LC_BYPASS_EQ_REQ_PHASE_OFFSET),
    0
    );

  //
  // EnableSafeSearch
  // LcFomTime (00) 300us
  //           (01) 200us
  //           (02) 100us
  //           (03) Less than 100us
  //
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of LcFomTime  = 0x%x\n",Engine->Type.Port.LcFomTime);
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of EnableSafeSearch  = 0x%x\n",Engine->Type.Port.EnableSafeSearch);

  Address = SMN_0x111402f0_ADDRESS;
  Address += (MappingPortID * 0x1000);
  IDS_HDT_CONSOLE (GNB_TRACE, "Address of LcFomTime  = 0x%x\n", Address);

  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(SMN_0x111402f0_LC_FOM_TIME_MASK |
    SMN_0x111402f0_LC_SAFE_EQ_SEARCH_MASK),
    (Engine->Type.Port.LcFomTime << SMN_0x111402f0_LC_FOM_TIME_OFFSET) |
    (Engine->Type.Port.EnableSafeSearch << SMN_0x111402f0_LC_SAFE_EQ_SEARCH_OFFSET),
    0
    );

  //
  // Enable3x3Search
  //
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of Enable3x3Search  = 0x%x\n",Engine->Type.Port.Enable3x3Search);
  Address = SMN_0x111402e0_ADDRESS;
  Address += (MappingPortID * 0x1000);
  IDS_HDT_CONSOLE (GNB_TRACE, "Address of Enable3x3Search  = 0x%x\n",Address);

  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(SMN_0x111402e0_LC_3X3_COEFF_SEARCH_EN_MASK),
    (Engine->Type.Port.Enable3x3Search << SMN_0x111402e0_LC_3X3_COEFF_SEARCH_EN_OFFSET),
    0
    );

  //
  // (Implementation notes: due to known bug, we may not support 1SYM on ZP A0, please set 2SYM as default for all 3speeds until further confirmation)
  // SpcMode.SpcGen1 - (REGS_LC_SPC_MODE_2P5GT = 1 as defalut)
  // SpcMode.SpcGen2 - (REGS_LC_SPC_MODE_5GT = 1 as defalut)
  // SpcMode.SpcGen3 - (REGS_LC_SPC_MODE_8GT = 1 as defalut)
  //
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of SpcGen1  = 0x%x\n",Engine->Type.Port.SpcMode.SpcGen1);
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of SpcGen2  = 0x%x\n",Engine->Type.Port.SpcMode.SpcGen2);
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of SpcGen3  = 0x%x\n",Engine->Type.Port.SpcMode.SpcGen3);

  Address = SMN_0x111402ec_ADDRESS;
  Address += (MappingPortID * 0x1000);
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(SMN_0x111402ec_LC_SPC_MODE_2P5GT_MASK |
    SMN_0x111402ec_LC_SPC_MODE_5GT_MASK |
    SMN_0x111402ec_LC_SPC_MODE_8GT_MASK),
    (Engine->Type.Port.SpcMode.SpcGen1 << SMN_0x111402ec_LC_SPC_MODE_2P5GT_OFFSET) |
    (Engine->Type.Port.SpcMode.SpcGen2 << SMN_0x111402ec_LC_SPC_MODE_5GT_OFFSET) |
    (Engine->Type.Port.SpcMode.SpcGen3 << SMN_0x111402ec_LC_SPC_MODE_8GT_OFFSET),
    0
    );

  //
  /// @todo : PortReversal
  //
  //
  // TXDeEmphasis (RSMU  0x4A348)
  //

  //
  // TXMargin
  //

  //
  // ScramblerCntl
  //

  //
  // PowerOff Unused Phy Lanes and PLL L1
  //
  IDS_HDT_CONSOLE (GNB_TRACE, "Value of PowerOffPhyLanesPllL1 = 0x%x\n",Engine->Type.Port.PowerOffPhyLanesPllL1);
  Address = PCIE0_LC_CNTL6_ADDRESS;
  Address += (MappingPortID * 0x1000);
  IDS_HDT_CONSOLE (GNB_TRACE, "Address of PowerOffPhyLanesPllL1= 0x%x\n",Address);
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    Address,
    (UINT32)~(PCIE_LC_CNTL6_LC_L1_POWERDOWN_MASK),
    (Engine->Type.Port.PowerOffPhyLanesPllL1 << PCIE_LC_CNTL6_LC_L1_POWERDOWN_OFFSET),
    0
    );

  //
  // Native_PME
  //
  if (Engine->Type.Port.PortData.LinkHotplug == HotplugEnhanced) {
    Address = Native_PME_ADDRESS;
    Address += (MappingPortID * 0x1000);
    IDS_HDT_CONSOLE (GNB_TRACE, "Address of Native_PME = 0x%x\n", Address);
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      Address,
      (UINT32)~(BIT3),
      (0x1 << 3),
      0
      );
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAfterTrainingDoneCallback Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get number of PCIe engines in given complex
 *
 *
 *
 * @param[in] PortList    Complex configuration
 * @retval                Number of Engines
 */
UINTN
DxioInputParserGetNumberOfEngines (
  IN      DXIO_PORT_DESCRIPTOR       *PortList
  )
{
  UINTN                 Result;
  DXIO_PORT_DESCRIPTOR  *PciePortList;
  Result = 0;
  PciePortList = PortList;
  while (PciePortList != NULL) {
    Result++;
    PciePortList = DxioInputParsetGetNextDescriptor (PciePortList);
  }
  return Result;
}

/*----------------------------------------------------------------------------------------*/
/**
 * To Hook Dxio Interface initialize Setting
 *
 *
 * @param[in]  EngineDescriptor   Pointer to engine descriptor
 */
VOID
DxioInterfaceInitSettingHook (
  IN      DXIO_PORT_DESCRIPTOR      *EngineDescriptor
  )
{

  if (EngineDescriptor->EngineData.EngineType == PciePortEngine) {
    switch (PcdGet8 (PcdPsppPolicy)) {
    case 1:  // Performance
      break;
    case 2:  // Balanced
      break;
    case 3:  // Power Saving
      break;
    default:
      break;
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "Engine->Port.LinkSpeedCapability: %x\n", EngineDescriptor->Port.LinkSpeedCapability);

}


/*----------------------------------------------------------------------------------------*/
/**
 * Helper function to dump input configuration to user engine descriptor
 *
 *
 * @param[in]  EngineDescriptor   Pointer to engine descriptor
 */
VOID
DxioUserDescriptorConfigDump (
  IN      DXIO_PORT_DESCRIPTOR      *EngineDescriptor
  )
{

  IDS_HDT_CONSOLE (PCIE_MISC, "  Engine Type - %a\n",
    (EngineDescriptor->EngineData.EngineType == DxioPcieEngine) ? "PCIe Port" : (
    (EngineDescriptor->EngineData.EngineType == DxioSATAEngine) ? "SATA Port" : (
    (EngineDescriptor->EngineData.EngineType == DxioUSBEngine) ? "USB Port" : (
    (EngineDescriptor->EngineData.EngineType == DxioDPEngine) ? "Display Port" : (
    (EngineDescriptor->EngineData.EngineType == DxioEthernetEngine) ? "Ethernet Port" : (
    (EngineDescriptor->EngineData.EngineType == DxioGOPEngine) ? "GOP Port" : (
    (EngineDescriptor->EngineData.EngineType == DxioUnusedEngine) ? "Unused" : "Invalid"))))))
    );
  IDS_HDT_CONSOLE (PCIE_MISC, "    Start Phy Lane - %d\n    End   Phy Lane - %d\n",
    EngineDescriptor->EngineData.StartLane,
    EngineDescriptor->EngineData.EndLane
  );
  IDS_HDT_CONSOLE (PCIE_MISC, "    Hotplug - %d\n", EngineDescriptor->EngineData.HotPluggable);
  IDS_HDT_CONSOLE (PCIE_MISC, "    GpioGroupId - %d\n", EngineDescriptor->EngineData.GpioGroupId);
  if (EngineDescriptor->EngineData.EngineType == PciePortEngine) {
    IDS_HDT_CONSOLE (PCIE_MISC, "    PortPresent - %d\n    DeviceNumber - %d\n    FunctionNumber - %d\n    LinkSpeedCapability - %d\n    LinkAspm - %d\n    LinkHotplug - %d\n    SB link - %d\n    MiscControls - 0x%02x\n" ,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.PortPresent,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.DeviceNumber,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.FunctionNumber,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.LinkSpeedCapability,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.LinkAspm,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.LinkHotplug,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.MiscControls.SbLink,
      ((DXIO_PORT_DESCRIPTOR *) EngineDescriptor)->Port.MiscControls
    );
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Helper function to dump input configuration to debug out
 *
 *
 * @param[in]  ComplexDescriptor   Pointer to user defined complex descriptor
 */
VOID
DxioUserConfigConfigDump (
  IN      DXIO_COMPLEX_DESCRIPTOR     *ComplexDescriptor
  )
{
  DXIO_PORT_DESCRIPTOR      *EngineDescriptor;
  UINTN                     Index;
  UINTN                     NumberOfEngines;

  IDS_HDT_CONSOLE (PCIE_MISC, "<---------- PCIe User Config Start------------->\n");
  EngineDescriptor = ComplexDescriptor->PciePortList;
  NumberOfEngines = DxioInputParserGetNumberOfEngines (EngineDescriptor);
  IDS_HDT_CONSOLE (PCIE_MISC, "NumberOfEngines - %d\n", NumberOfEngines);

  for (Index = 0; Index < NumberOfEngines; Index++) {
    DxioInterfaceInitSettingHook (EngineDescriptor);
    DxioUserDescriptorConfigDump (EngineDescriptor);
    EngineDescriptor++;
  }
  IDS_HDT_CONSOLE (PCIE_MISC, "<---------- PCIe User Config End-------------->\n");
}

/**----------------------------------------------------------------------------------------*/
/**
 * PCIE interface to configure register setting
 *
 *
 *
 * @param[in]  ComplexDescriptor   Pointer to user defined complex descriptor
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/

VOID
SataChannelTypeSetting (
  IN      DXIO_COMPLEX_DESCRIPTOR     *ComplexDescriptor
  )
{
  UINT8                   SataChannelType;
  DXIO_PORT_DESCRIPTOR    *EngineDescriptor;

  IDS_HDT_CONSOLE (GNB_TRACE, "SataChannelTypeSetting Enter\n");
  SataChannelType = PcdGet8 (PcdCfgSataPhyTuning);
  if (SataChannelType != 0) {
    while (ComplexDescriptor != NULL) {
      EngineDescriptor = ComplexDescriptor->PciePortList;
      while (EngineDescriptor != NULL) {
        if (EngineDescriptor->EngineData.EngineType == DxioSATAEngine) {
          EngineDescriptor->Port.MiscControls.ChannelType = SataChannelType;
          IDS_HDT_CONSOLE (GNB_TRACE, "SataChannelTypeSetting(ChannelType=%x)\n", SataChannelType);
        }
        EngineDescriptor = DxioInputParsetGetNextDescriptor (EngineDescriptor);
      }
      ComplexDescriptor = DxioInputParsetGetNextDescriptor (ComplexDescriptor);
    }
  }
  return;
}

/**----------------------------------------------------------------------------------------*/
/**
 * PCIE interface to configure register setting
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/

VOID
PcieInterfaceInitSetting (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG   *PcieEngine;
  PCIe_WRAPPER_CONFIG  *PcieWrapper;
  PCI_ADDR             NbifAddress;
  UINT32               Index;
  UINT32               Value;
  UINT32               PortIndex;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieInterfaceInitSetting Enter\n");
  //
  // DMA workaround
  //
  NbifAddress.AddressValue = 0;
  NbifAddress.Address.Device = 8;
  NbifAddress.Address.Function = 1;
  NbifAddress.Address.Register = 4;
  NbioRegisterRMW (GnbHandle, TYPE_D0F0, NbifAddress.AddressValue, 0xFF, 0x04, 0);
  NbifAddress.Address.Function = 2;
  NbioRegisterRMW (GnbHandle, TYPE_D0F0, NbifAddress.AddressValue, 0xFF, 0x04, 0);

  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      PcieIntegratedInterfaceCallback (GnbHandle, PcieEngine, NULL );
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    if (PcdGetBool (PcdCfgACSEnable)) {
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_AER_EN_offset, 1);
      Index = 0xFFFE0002;
      NbioRegisterWrite (GnbHandle,
                         TYPE_SMN,
                         PCIE0_STRAP_INDEX_ADDRESS,
                         &Index,
                         0
                         );
      Value = 1;
      NbioRegisterWrite (GnbHandle,
                         TYPE_SMN,
                         PCIE0_STRAP_DATA_ADDRESS,
                         &Value,
                         0
                         );
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_SOURCE_VALIDATION_offset, 1);
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_TRANSLATION_BLOCKING_offset, 1);
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_DIRECT_TRANSLATED_P2P_offset, 1);
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_P2P_COMPLETION_REDIRECT_offset, 1);
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_P2P_REQUEST_REDIRECT_offset, 1);
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_UPSTREAM_FORWARDING_offset, 1);
      //dxio_fw_mp1_pcie_strapBif_write( pcieMapData->pcieCoreId, dxio_fw_e_STRAP_BIF_ACS_EN_offset, 1);
      for (Index = 0xFFFE0069; Index <= 0xFFFE006E; Index++) {
        NbioRegisterWrite (GnbHandle,
                           TYPE_SMN,
                           PCIE0_STRAP_INDEX_ADDRESS,
                           &Index,
                           0
                           );
        Value = 1;
        NbioRegisterWrite (GnbHandle,
                           TYPE_SMN,
                           PCIE0_STRAP_DATA_ADDRESS,
                           &Value,
                           0
                           );
      }
      Index = 0xFFFE0068;
      NbioRegisterWrite (GnbHandle,
                         TYPE_SMN,
                         PCIE0_STRAP_INDEX_ADDRESS,
                         &Index,
                         0
                         );
      Value = 1;
      NbioRegisterWrite (GnbHandle,
                         TYPE_SMN,
                         PCIE0_STRAP_DATA_ADDRESS,
                         &Value,
                         0
                         );

      NbioRegisterRMW (GnbHandle,           // set Dev1 Port
                       TYPE_SMN,
                       SMN_RCC_DEV1_PORT_STRAP0_ADDRESS ,
                       (UINT32) ~(STRAP_AER_EN_DN_DEV0_MASK |
                       STRAP_ACS_EN_DN_DEV0_MASK |
                       STRAP_CPL_ABORT_ERR_EN_DN_DEV0_MASK),
                       ((0x1 << STRAP_AER_EN_DN_DEV0_OFFSET) |
                       (0x1 << STRAP_ACS_EN_DN_DEV0_OFFSET) |
                       (0x1 << STRAP_CPL_ABORT_ERR_EN_DN_DEV0_OFFSET)),
                       0
                       );

       for (Index = 0; Index < 3; Index++) {     // Handle Dev1 Fcns 0..2
         NbioRegisterRMW (GnbHandle,
                          TYPE_SMN,
                          NBIF1_SATA_STRAP2_ADDRESS | (Index * 0x200),
                          (UINT32) ~(RCC_BIF_STRAP2_AER_EN_DEV0_F0_MASK |
                          RCC_BIF_STRAP2_ACS_EN_DEV0_F0_MASK |
                          RCC_BIF_STRAP2_CPL_ABORT_ERR_EN_DEV0_F0_MASK),
                          ((0x1 << RCC_BIF_STRAP2_AER_EN_DEV0_F0_OFFSET) |
                          (0x1 << RCC_BIF_STRAP2_ACS_EN_DEV0_F0_OFFSET) |
                          (0x1 << RCC_BIF_STRAP2_CPL_ABORT_ERR_EN_DEV0_F0_OFFSET)),
                          0
                          );
       }
//<Embedded_Override_Start>

      if (PcdGet8 (PcdCfgIgpuContorl) != 0) {
        NbioRegisterRMW (GnbHandle,
                         TYPE_SMN,
                         DEV0_PORT_STRAP0_ADDRESS,
                         (UINT32) ~(STRAP_ACS_EN_DN_DEV0_MASK),
                         (1 << STRAP_ACS_EN_DN_DEV0_OFFSET),
                         0
                         );

        NbioRegisterRMW (GnbHandle,
                         TYPE_SMN,
                         RCC_BIF_STRAP2_ADDRESS,
                         (UINT32) ~(RCC_BIF_STRAP2_ACS_EN_DEV0_F0_MASK),
                         (1 << RCC_BIF_STRAP2_ACS_EN_DEV0_F0_OFFSET),
                         0
                         );
      }
        //<Embedded_Override_Start>
        for (Index = 0; Index < 7; Index++) {     // Handle Dev0 Fcns 1..7
          NbioRegisterRMW (GnbHandle,
                          TYPE_SMN,
                          (NBIF0_DCE_AZ_STRAP2_ADDRESS + (Index * 0x200)),
                          (UINT32) ~(RCC_BIF_STRAP2_ACS_EN_DEV0_F0_MASK),
                         (1 << RCC_BIF_STRAP2_ACS_EN_DEV0_F0_OFFSET),
                          0
                          );
        }
        //<Embedded_Override_End>
    }

//<Embedded_Override_End>
    //STRAP_BIF_L0S_EXIT_LATENCY_A to G
    for (PortIndex = 0; PortIndex < 7; PortIndex++) {
      //<Embedded_Override_Start>
      //STRAP_BIF_L0S_EXIT_LATENCY_A offset values are different for RV1 and RV2.Update the strap index value accordingly
      if(CheckRvOpn()) {
        Index = ( FUSE_ACCESS_LOCATION + STRAP_BIF_L0S_EXIT_LATENCY_A_OFFSET_RV1 ) + (PortIndex * 0x51);
      } else {
        Index = ( FUSE_ACCESS_LOCATION + STRAP_BIF_L0S_EXIT_LATENCY_A_OFFSET_RV2 ) + (PcieEngine->Type.Port.PortId * 0x51);
      }
      //<Embedded_Override_End>
      NbioRegisterWrite (GnbHandle,
                         TYPE_SMN,
                         PCIE0_STRAP_INDEX_ADDRESS,
                         &Index,
                         0
                         );
      Value = 0x7;
      NbioRegisterWrite (GnbHandle,
                         TYPE_SMN,
                         PCIE0_STRAP_DATA_ADDRESS,
                         &Value,
                         0
                         );
    }

    // MasterPLL statically on Lane4
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      PCS_PCIEX16_C10_GLOBAL_CONTROL1_ADDRESS,
      (UINT32)~(MasterPLL_Mask),
      (0x4 << MasterPLL_OFFSET),
      0
      );
    IDS_HDT_CONSOLE (GNB_TRACE, "PCS_PCIEX16_C10_GLOBAL_CONTROL1\n");

    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieInterfaceInitSetting Exit\n");
}

/**----------------------------------------------------------------------------------------*/
/**
 * PCIE interface to configure register setting after Dxio init done
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/

VOID
PcieInterfaceAfterDxioDoneSetting (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG   *PcieEngine;
  PCIe_WRAPPER_CONFIG  *PcieWrapper;
  UINT32               Value;
  UINT32               Address;
  UINT32               PortIndex;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieInterfaceAfterDxioDoneSetting Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      PcieAfterTrainingDoneCallback (GnbHandle, PcieEngine, NULL );
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    Value = (UINT32) PcdGet8 (PcdGfxAtomicOps);
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_STRAP_F0_ADDRESS,
                     (UINT32) ~(PCIE_STRAP_F0_STRAP_F0_ATOMIC_EN_MASK),
                     Value << PCIE_STRAP_F0_STRAP_F0_ATOMIC_EN_OFFSET,
                     0
                     );
    if (PcdGetBool (PcdPcieEcrcEnablement)) {
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       PCIE0_STRAP_F0_ADDRESS,
                       (UINT32) ~(PCIE_STRAP_F0_STRAP_F0_ECRC_CHECK_EN_MASK | PCIE_STRAP_F0_STRAP_F0_ECRC_GEN_EN_MASK),
                       (1 << PCIE_STRAP_F0_STRAP_F0_ECRC_CHECK_EN_OFFSET) | (1 << PCIE_STRAP_F0_STRAP_F0_ECRC_GEN_EN_OFFSET),
                       0
                       );
    }
    Address = PCIEP_STRAP_MISC_instPCIE0_link_ADDRESS;
    for (PortIndex = 0; PortIndex < 7; PortIndex++) {
      NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     Address | (PortIndex << 12),
                     (UINT32) ~(PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_MASK | PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_MASK),
                     (1 << PCIEP_STRAP_MISC_STRAP_EXTENDED_FMT_SUPPORTED_OFFSET) | (1 << PCIEP_STRAP_MISC_STRAP_E2E_PREFIX_EN_OFFSET),
                     0
                     );
      NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_SLOT_APERTURE | DEVICE_CNTL2_ADDRESS | (PortIndex << 12),
                     (UINT32) ~(DEVICE_CNTL2_CPL_TIMEOUT_VALUE_MASK),
                     (0x6 << DEVICE_CNTL2_CPL_TIMEOUT_VALUE_OFFSET),
                     0
                     );
      NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     SMN_0x11140280_ADDRESS | (PortIndex << 12),
                     (UINT32) ~(SMN_0x11140280_LC_L1_IMMEDIATE_ACK_MASK),
                     (0x1 << SMN_0x11140280_LC_L1_IMMEDIATE_ACK_OFFSET),
                     0
                     );
      NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_LC_LINK_WIDTH_CNTL_ADDRESS | (PortIndex << 12),
                     (UINT32) ~(PCIE_LC_LINK_WIDTH_CNTL_LC_DUAL_END_RECONFIG_EN_MASK),
                     (0x1 << PCIE_LC_LINK_WIDTH_CNTL_LC_DUAL_END_RECONFIG_EN_OFFSET),
                     0
                     );
      NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_PCIE_LC_CNTL2_ADDRESS | (PortIndex << 12),
                     (UINT32) ~(PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_MASK),
                     (0x1 << PCIE_LC_CNTL2_LC_ELEC_IDLE_MODE_OFFSET),
                     0
                     );
      NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_PCIEP_HW_DEBUG_ADDRESS | (PortIndex << 12),
                     (UINT32) ~(PCIEP_HW_DEBUG_HW_15_DEBUG_MASK),
                     (0x1 << PCIEP_HW_DEBUG_HW_15_DEBUG_OFFSET),
                     0
                     );
    }

    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_CNTL_ADDRESS,
                     (UINT32) ~(PCIE_CNTL_RX_RCB_INVALID_SIZE_DIS_MASK),
                     0x0 << PCIE_CNTL_RX_RCB_INVALID_SIZE_DIS_OFFSET,
                     0
                     );

    if (PcdGetBool (PcdAmdNbioReportEdbErrors)) {
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       PCIE0_P_CNTL_ADDRESS ,
                       (UINT32) ~(PCIE_P_CNTL_P_IGNORE_EDB_ERR_MASK),
                       0x0 << PCIE_P_CNTL_P_IGNORE_EDB_ERR_OFFSET,
                       0
                       );
    } else {
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       PCIE0_P_CNTL_ADDRESS,
                       (UINT32) ~(PCIE_P_CNTL_P_IGNORE_EDB_ERR_MASK),
                       0x1 << PCIE_P_CNTL_P_IGNORE_EDB_ERR_OFFSET,
                       0
                       );
    }

    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE0_P_CNTL_ADDRESS,
                     (UINT32) ~(PCIE_P_CNTL_P_ELEC_IDLE_MODE_MASK),
                     0x1 << PCIE_P_CNTL_P_ELEC_IDLE_MODE_OFFSET,
                     0
                     );

    if (PcdGetBool (PcdCfgPCIeAEREnable)) {
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       PCIE0_STRAP_F0_ADDRESS,
                       (UINT32) ~(PCIE_STRAP_F0_STRAP_F0_AER_EN_MASK),
                       (0x1 << PCIE_STRAP_F0_STRAP_F0_AER_EN_OFFSET),
                       0
                       );
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieInterfaceAfterDxioDoneSetting Exit\n");
}

/**----------------------------------------------------------------------------------------*/
/**
 * PCIE interface to configure register setting after Dxio init done
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 * @retval    AGESA_STATUS
 */
 /*----------------------------------------------------------------------------------------*/

VOID
SubsystemIdSetting (
  IN       GNB_HANDLE       *GnbHandle
  )
{
  UINT32      Value;
  UINT32      Index;
  UINT32      SubsystemDeviceId;
  UINT32      SubsystemVendorId;

  IDS_HDT_CONSOLE (GNB_TRACE, "SubsystemIdSetting Entry\n");

  // IOMMU
  Value = PcdGet32 (PcdCfgIommuSsid);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdCfgIommuSsid = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_IOMMU_SSID_ADDRESS, &Value, 0);
  }
  // GFX
  Value = PcdGet32 (PcdAmdCfgGnbIGPUSSID);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdAmdCfgGnbIGPUSSID = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0EPF0_GFX_SSID_ADDRESS, &Value, 0);
  }

  // GFX Audio SSID
  Value = PcdGet32 (PcdAmdCfgGnbIGPUAudioSSID);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdAmdCfgGnbIGPUAudioSSID = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0EPF1_GFX_Audio_SSID_ADDRESS, &Value, 0);
  }

  // PSPCCP
  Value = PcdGet32 (PcdCfgPspccpSsid);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdCfgPspccpSsid = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0EPF2_PSP_SSID_ADDRESS, &Value, 0);
  }

  // HDAudio
  Value = PcdGet32 (PcdAmdCfgGnbHDAudioSSID);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdAmdCfgGnbHDAudioSSID = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0EPF6_HDAudio_SSID_ADDRESS, &Value, 0);
  }

  // XGBE
  Value = PcdGet32 (PcdCfgXgbeSsid);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdCfgXgbeSsid = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0EPF9_GBE0_SSID_ADDRESS, &Value, 0);
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0EPF10_GBE1_SSID_ADDRESS, &Value, 0);
  }

  // NBIF Root Bridge Functions
  Value = PcdGet32 (PcdCfgNbifRCSsid);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdCfgNbifRCSsid = %x\n", Value);
  if (Value != 0) {
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF0RC_SSID_ADDRESS, &Value, 0);
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCICFG_NBIF1RC_SSID_ADDRESS, &Value, 0);
  }

  // PCIE
  SubsystemDeviceId = (UINT32) PcdGet16 (PcdAmdPcieSubsystemDeviceID);
  if (SubsystemDeviceId != 0) {
    //STRAP_BIF_SUBSYS_ID offset values are different for RV1 and RV2.Update the strap index value accordingly
    //<Embedded_Override_Start>
    if(CheckRvOpn()) {
      Index = FUSE_ACCESS_LOCATION + STRAP_BIF_SUBSYS_ID_OFFSET_RV1;
    } else {
      Index = FUSE_ACCESS_LOCATION + STRAP_BIF_SUBSYS_ID_OFFSET_RV2;
    }
    //<Embedded_Override_End>
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCIE0_STRAP_INDEX_ADDRESS, &Index, 0);
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCIE0_STRAP_DATA_ADDRESS, &SubsystemDeviceId, 0);
  }
  SubsystemVendorId = (UINT32) PcdGet16 (PcdAmdPcieSubsystemVendorID);
  if (SubsystemVendorId != 0) {
    //STRAP_BIF_SUBSYS_VEN_ID offset values are different for RV1 and RV2.Update the strap index value accordingly
    //<Embedded_Override_Start>
    if(CheckRvOpn()) {
      Index = FUSE_ACCESS_LOCATION + STRAP_BIF_SUBSYS_VEN_ID_OFFSET_RV1;
    } else {
      Index = FUSE_ACCESS_LOCATION + STRAP_BIF_SUBSYS_VEN_ID_OFFSET_RV2;
    }
    //<Embedded_Override_End>
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCIE0_STRAP_INDEX_ADDRESS, &Index, 0);
    NbioRegisterWrite (GnbHandle, TYPE_SMN, PCIE0_STRAP_DATA_ADDRESS, &SubsystemVendorId, 0);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "SubsystemIdSetting Exit\n");
  return;
}

/**----------------------------------------------------------------------------------------*/
/**
 * configure HDAudio verb table
 *
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/

VOID
HDAudioVerbTableSetting (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  EFI_STATUS            Status;
  FABRIC_TARGET         MmioTarget;
  FABRIC_MMIO_ATTRIBUTE MmioAttr;
  UINT64                HDAudioMmioBase;
  UINT64                HDAudioMmioSize;
  UINT64                VerbTableAddress;
  UINT32                Value;
  UINT32                MmioBase;
  UINT64                Align;

  IDS_HDT_CONSOLE (GNB_TRACE, "NBIO HDAudio Config\n");
  NbioRegisterRead (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_VENDOR_ID_ADDRESS, &Value, 0);
  if (Value != 0xFFFFFFFF) {
    IDS_HDT_CONSOLE (GNB_TRACE, "HDAudio ID = 0x%x\n", Value);
    MmioBase = 0xFFFFFFFF;
    NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_BASE_ADDR_1_ADDRESS, &MmioBase, 0);
    NbioRegisterRead (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_BASE_ADDR_1_ADDRESS, &MmioBase, 0);
    IDS_HDT_CONSOLE (GNB_TRACE, "   MmioBase read from BAR10 %x\n", MmioBase);

    MmioTarget.TgtType = TARGET_RB;
    MmioTarget.SocketNum = 0;
    MmioTarget.RbNum = 0;
    MmioAttr.ReadEnable = 1;
    MmioAttr.WriteEnable = 1;
    MmioAttr.NonPosted = 0;
    MmioAttr.MmioType = NON_PCI_DEVICE_BELOW_4G;
    HDAudioMmioSize = 0xFFFFFFFF - MmioBase + 1;
    Align = ~MmioBase;

    Status = FabricAllocateMmio (&HDAudioMmioBase, &HDAudioMmioSize, Align, MmioTarget, &MmioAttr);
    IDS_HDT_CONSOLE (GNB_TRACE, "   HDAudioMmioBase = %x,HDAudioMmioSize = %x\n", (UINT32)HDAudioMmioBase, (UINT32)HDAudioMmioSize);
    if (Status == EFI_SUCCESS) {
      MmioBase = (UINT32) HDAudioMmioBase;
      NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_BASE_ADDR_1_ADDRESS, &MmioBase, 0);
      Value = (MmioBase & 0xFFF00000) | ((MmioBase & 0xFFF00000) >> 16);
      NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1RCCFG_BASELIMIT_ADDRESS, &Value, 0);
      NbioRegisterRead (GnbHandle, TYPE_SMN, NBIF1RCCFG_SUB_BUS_ADDRESS, &Value, 0);
      NbioRegisterRMW (GnbHandle, TYPE_SMN, NBIF1RCCFG_SUB_BUS_ADDRESS, 0xFF000FF, 0x0a0a00, 0);
      NbioRegisterRMW (GnbHandle, TYPE_SMN, NBIF1RCCFG_COMMAND_ADDRESS, (UINT32) ~(BIT1 | BIT2), (BIT1 | BIT2), 0);
      NbioRegisterRMW (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_COMMAND_ADDRESS, (UINT32) ~(BIT1 | BIT2), (BIT1 | BIT2), 0);
      VerbTableAddress = (UINT64) PcdGet32 (PcdCfgAzaliaCodecVerbTable);
      NbioConfigureVerbTable (MmioBase, VerbTableAddress);
      MmioBase = 0;
      NbioRegisterRMW (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_COMMAND_ADDRESS, (UINT32) ~(BIT1 | BIT2), 0, 0);
      NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_BASE_ADDR_1_ADDRESS, &MmioBase, 0);
      NbioRegisterRMW (GnbHandle, TYPE_SMN, NBIF1RCCFG_COMMAND_ADDRESS, (UINT32) ~(BIT1 | BIT2), 0, 0);
      NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1RCCFG_SUB_BUS_ADDRESS, &Value, 0);
      NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1RCCFG_BASELIMIT_ADDRESS, &MmioBase, 0);
    }

    Value = PcdGet32 (PcdCfgAzaliaSsid);
    if (Value != 0) {
      NbioRegisterWrite (GnbHandle, TYPE_SMN, NBIF1EPF6CFG_ADAPTER_ID_ADDRESS, &Value, 0);
      IDS_HDT_CONSOLE (GNB_TRACE, "NBIO HDAudio SSID=%x\n", Value);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set the operating link speed for Promontory based on topology config.
 * Initial training is Gen1.
 *
 *
 * @param[in]  ComplexDescriptor   Pointer to user defined complex descriptor
 */
VOID
DxioSetPtGenSpeed (
  IN      DXIO_COMPLEX_DESCRIPTOR     *ComplexDescriptor
  )
{
  DXIO_PORT_DESCRIPTOR      *EngineDescriptor;
  DXIO_COMPLEX_DESCRIPTOR   *LocalComplex;

  IDS_HDT_CONSOLE (PCIE_MISC, "DxioSetPtGenSpeed Enter\n");
  LocalComplex = ComplexDescriptor;
  while (LocalComplex != NULL) {
    EngineDescriptor = LocalComplex->PciePortList;
    while (EngineDescriptor != NULL) {
      if (EngineDescriptor->Port.MiscControls.SbLink == 1) {
        IDS_HDT_CONSOLE (PCIE_MISC, "  Setting PT to Gen%d\n",EngineDescriptor->Port.LinkSpeedCapability);
        if (EngineDescriptor->Port.LinkSpeedCapability == DxioGenMaxSupported) {
          PcdSet8(PcdPTTargetSpeed, DxioGen3);
          IDS_HDT_CONSOLE (PCIE_MISC, "  Setting PT to Gen3\n");
        } else {
          PcdSet8(PcdPTTargetSpeed, EngineDescriptor->Port.LinkSpeedCapability);
          IDS_HDT_CONSOLE (PCIE_MISC, "  Setting PT to Gen%d\n",EngineDescriptor->Port.LinkSpeedCapability);
        }
      }
      EngineDescriptor = DxioInputParsetGetNextDescriptor (EngineDescriptor);
    }
    LocalComplex = DxioInputParsetGetNextDescriptor (LocalComplex);
  }
  IDS_HDT_CONSOLE (PCIE_MISC, "DxioSetPtGenSpeed Exit\n");
}


/*----------------------------------------------------------------------------------------*/
/**
 * The Sequence to disable ACP before Hidden ACP controller.
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 */
VOID
DisableAcpSequence (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  UINT32 Value;

  Value = 0;
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    ACP_PGFSM_CTRL_ADDRESS,
    (UINT32)~(ACP_PGFSM_CTRL_Mask),
    0x1 << ACP_PGFSM_CTRL_OFFSET,
    0
    );

  while (TRUE) {
    NbioRegisterRead (GnbHandle, TYPE_SMN, ACP_PGFSM_STATUS_ADDRESS, &Value, 0);
    if (Value == 0x0) {
      break;
    }
  }

  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    ACP_CONTROL_ADDRESS,
    (UINT32)~(ClkEn_Mask),
    0x1 << ClkEn_OFFSET,
    0
    );


  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    ACP_SOFT_RESET_ADDRESS,
    (UINT32)~(SoftResetAud_Mask),
    0x1 << SoftResetAud_OFFSET,
    0
    );

  while (TRUE) {
    NbioRegisterRead (GnbHandle, TYPE_SMN, ACP_SOFT_RESET_ADDRESS, &Value, 0);
    if (Value & (SoftResetAud_Mask | SoftResetAudDone_Mask))     //0x00010001
     break;
  }

  Value = 0;
  NbioRegisterWrite (GnbHandle, TYPE_SMN, ACP_SOFT_RESET_ADDRESS, &Value, 0);
  while (TRUE) {
    NbioRegisterRead (GnbHandle, TYPE_SMN, ACP_SOFT_RESET_ADDRESS, &Value, 0);
    if(Value == 0) {
      break;
    }
  }

  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    ACP_DYNAMIC_CG_MASTER_CONTROL_ADDRESS,
    (UINT32)~(ACP_DYNAMIC_CG_Disable_Mask),
    0x1FF << ACP_DYNAMIC_CG_Disable_OFFSET,
    0
    );

  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    ACP_PGMEM_CTRL_ADDRESS,
    (UINT32)~(ACP_PGMEM_SHUT_DOWN_Mask),
    0xFFF << ACP_PGMEM_SHUT_DOWN_OFFSET,
    0
    );

  while (TRUE) {
    NbioRegisterRead (GnbHandle, TYPE_SMN, ACP_MEM_PG_STS_ADDRESS, &Value, 0);
    if(Value == 0) {
      break;
    }
  }
  Value = 0;
  NbioRegisterWrite (GnbHandle, TYPE_SMN, ACP_DYNAMIC_CG_MASTER_CONTROL_ADDRESS, &Value, 0);
  NbioRegisterWrite (GnbHandle, TYPE_SMN, ACP_CONTROL_ADDRESS, &Value, 0);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback for NbioSmuServicesPpi installation
 *
 *
 *
 * @param[in]  PeiServices       Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  NotifyDescriptor  NotifyDescriptor pointer
 * @param[in]  Ppi               Ppi pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
DxioInitializationCallbackPpi (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                        Status;
  GNB_HANDLE                        *GnbHandle;
  GNB_HANDLE                        *NextHandle;
  UINT32                            SmuArg[6];
  UINT32                            PackageType;
  SOC_LOGICAL_ID                    LogicalId;
  PCIe_PLATFORM_CONFIG              *Pcie;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI    *PcieServicesPpi;
  PEI_AMD_NBIO_SMU_SERVICES_PPI     *SmuServicesPpi;
  AMD_MEMORY_INFO_HOB_PPI           *AmdMemoryInfoHob;
  GNB_PCIE_INFORMATION_DATA_HOB     *PciePlatformConfigHob;
  DXIO_COMPLEX_DESCRIPTOR           *PcieTopologyData;
  PEI_AMD_NBIO_PCIE_COMPLEX_PPI     *NbioPcieComplexPpi;
  AMD_PEI_SOC_LOGICAL_ID_PPI        *SocLogicalIdPpi;
  DXIO_ANCILLARYPORTDATA_PSPP       PsppParams;
  EFI_BOOT_MODE                     BootMode;
  BOOLEAN                           IsRv2;

  Status = PeiServicesGetBootMode (&BootMode);

  SetMem ((VOID *)(&LogicalId), sizeof (LogicalId), 0);
  AGESA_TESTPOINT (TpDxioInitializationCallbackPpiEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "DxioInitializationCallbackPpi Entry\n");
  Status = (*PeiServices)->LocatePpi (PeiServices, &gAmdMemoryInfoHobPpiGuid, 0, NULL, &AmdMemoryInfoHob);
  if (!EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "AmdMemoryInfoHobPpiGuid is installed\n");
    Status = (*PeiServices)->LocatePpi (PeiServices, &gAmdNbioSmuServicesPpiGuid, 0, NULL, &SmuServicesPpi);
    if (!EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE (GNB_TRACE, "gAmdNbioSmuServicesPpiGuid is installed\n");
      Status = (*PeiServices)->LocatePpi (PeiServices, &gAmdNbioPcieComplexPpiGuid, 0, NULL, &NbioPcieComplexPpi);
      if (!EFI_ERROR (Status)) {
        IDS_HDT_CONSOLE (GNB_TRACE, "gAmdNbioPcieComplexPpiGuid is installed\n");
        NbioPcieComplexPpi->PcieGetComplex (NbioPcieComplexPpi, &PcieTopologyData);
        PcieTopologyData->BmcLinkLocation = 0xFF;
        DxioUserConfigConfigDump (PcieTopologyData);

        // Get package type
        Status = (*PeiServices)->LocatePpi (
                                 PeiServices,
                                 &gAmdSocLogicalIdPpiGuid,
                                 0,
                                 NULL,
                                 &SocLogicalIdPpi
                                 );
        if (!EFI_ERROR (Status)) {
          Status = SocLogicalIdPpi->GetLogicalIdOnCurrentCore (&LogicalId);
        }
        PackageType = LibAmdGetPackageType ((AMD_CONFIG_PARAMS *) NULL);

        // Need topology structure to get GnbHandle
        Status = (*PeiServices)->LocatePpi (
                                   PeiServices,
                                   &gAmdNbioPcieServicesPpiGuid,
                                   0,
                                   NULL,
                                   (VOID **)&PcieServicesPpi
                                   );
        PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
        Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);
        Pcie->PsppPolicy = PcdGet8 (PcdPsppPolicy);
        // How to define default thresholds?
        PsppParams.Field.lowBWThreshold = PsppThreshold100Percent;
        PsppParams.Field.HighBWThreshold = PsppThreshold90Percent;
        PsppParams.Field.lowBWThresholdG2 =  PsppThreshold95Percent;
        PsppParams.Field.HighBWThresholdG2 = PsppThreshold90Percent;
        PsppParams.Field.lowBWThresholdG3 = PsppThreshold95Percent;
        PsppParams.Field.HighBWThresholdG3 = PsppThreshold0Percent;
        PsppParams.Field.BWHintCount = 3;
        Pcie->PsppTuningParams = PsppParams.Value;
        IDS_HOOK (IDS_HOOK_NBIO_PSPP_TUNING, (VOID *)NULL, (VOID *)Pcie);

        LibAmdMemFill (SmuArg, 0x00, 24, (AMD_CONFIG_PARAMS *) NULL);
        SmuArg[0] = 0xAA55AA55;
        SmuServicesPpi->SmuServiceRequest (SmuServicesPpi, 0, 1, SmuArg, SmuArg);

        GnbHandle = NbioGetHandle (Pcie);

        NextHandle = GnbGetNextHandle (GnbHandle);
        if (NextHandle == NULL) {
          // Temporary enable for AM4 only
          if (PcdGet8 (PcdAmdNbioAudioSelect) != Soundwire) {
            if (PcdGetBool (PcdCfgHdAudioEnable)) {
              NbioEnableNbifDevice (GnbHandle, DxioHDaudioEngine, 0);
              HDAudioVerbTableSetting (GnbHandle);
            } else {
              NbioDisableNbifDevice (GnbHandle, DxioHDaudioEngine, 0);
            }
          }
        }

        while (GnbHandle != NULL) {
          IDS_HOOK (IDS_HOOK_NBIO_PCIE_USER_CONFIG, (VOID *)GnbHandle, (VOID *)PcieTopologyData);
          // Skip KPNP workaround on B0 Silicon
          if ((LogicalId.Family & AMD_FAMILY_17_RV) && (LogicalId.Revision & AMD_REV_F17_RV_A0) == TRUE) {
            KpnpResetWorkaround (PeiServices, GnbHandle);
            A0ParallelTrainingWorkaround (PeiServices, GnbHandle, PcieTopologyData);
          }
          PcieInterfaceInitSetting (GnbHandle);
          if (!PcdGetBool (PcdAcpController)){
            DisableAcpSequence (GnbHandle);
            NbioDisableNbifDevice (GnbHandle, DxioACPEngine, 0);
          }
          if (!PcdGetBool (PcdCfgSensorFusionHubEnable)) {
            NbioDisableNbifDevice (GnbHandle, DxioMP2Engine, 0);
          }
          GnbHandle = GnbGetNextHandle (GnbHandle);
        }
        DxioSetPtGenSpeed (PcieTopologyData);
        SataChannelTypeSetting  (PcieTopologyData);
        // At this point we know the NBIO topology and SMU services are available
        // We can now use SMU to initialize DXIO
        Status = DxioEarlyInitV1 (PeiServices, SmuServicesPpi, Pcie, PcieTopologyData);
        PcieConfigDebugDump (Pcie);

        GnbHandle = NbioGetHandle (Pcie);
        while (GnbHandle != NULL) {
          // IDS_HOOK (IDS_HOOK_NBIO_PCIE_TOPOLOGY, (VOID *)GnbHandle, (VOID *)Pcie);
          PciePortsVisibilityControlRV (HidePorts, GnbHandle);

          IsRv2 = CheckRv2OpnB4 ();
          if ((LogicalId.Family & AMD_FAMILY_RV2) != 0) {
            IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 Single Source \n");
            IsRv2 = TRUE;
          }
          if ((BootMode == BOOT_ON_S3_RESUME) && (IsRv2 == TRUE)) {
            Rv2S3SataWorkaround (GnbHandle);
          }
          PcieInterfaceAfterDxioDoneSetting (GnbHandle);
          SubsystemIdSetting (GnbHandle);
          GnbHandle = GnbGetNextHandle (GnbHandle);
        }
        PcieConfigureHotplugPortsRV (Pcie);

        // Initialize ARI
        GnbHandle = NbioGetHandle (Pcie);
        while (GnbHandle != NULL) {
          if (TRUE == PcdGetBool (PcdCfgPcieAriSupport)) {
            NbioRegisterRMW (
              GnbHandle,
              TYPE_SMN,
              IOC_FEATURE_CNTL_ADDRESS,
              (UINT32)~(NBMISC_0118_IOC_ARI_SUPPORTED_MASK),
              1 << NBMISC_0118_IOC_ARI_SUPPORTED_OFFSET,
              0
              );
            PcieAriInit (GnbHandle);
          }
          GnbHandle = GnbGetNextHandle (GnbHandle);
        }

        // Install PPI to notify other drivers that PCIe training is complete
        Status = (**PeiServices).InstallPpi (PeiServices, &mNbioPcieTrainingDonePpiList);
      }
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "DxioInitializationCallbackPpi Exit\n");
  AGESA_TESTPOINT (TpDxioInitializationCallbackPpiExit, NULL);
  return EFI_SUCCESS;
}



