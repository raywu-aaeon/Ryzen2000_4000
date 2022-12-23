/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe mid post initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312286 $   @e \$Date: 2015-02-04 14:11:11 +0800 (Wed, 04 Feb 2015) $
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
#include  "OptionGnb.h"
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieInitLib.h"
#include  "GnbFamServices.h"
#include  "GnbRegistersCZ.h"
#include  "GnbRegisterAccCZ.h"
#include  "PcieLibCZ.h"
#include  "GnbLibPciAcc.h"
#include  "PciePowerGateCZ.h"
#include  "PcieComplexDataCZ.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbRegistersCZ.h"
#include  "PcieComplexDataCZ.h"
#include  "PcieAriInitCZ.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_PCIEMIDINITCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern CONST PCIE_PORT_REGISTER_TABLE_HEADER ROMDATA PortInitMidTableCZ;

#define ABS(X) (((X) < 0) ? (-(X)) : (X))

//for SOI PHY, NB L1 existing latency is about 30us
//for TSMC PHY, NB L1 existing latency is about 35us
#define NB_L1_EXITING_LATENCY_CZ   35
#define PLL_RAMP_UP_TIME    22

#define PARITY_UNCORRECTABLE_GROUP  0
#define PARITY_CORRECTABLE_GROUP    1
#define PARITY_ECC_GROUP            2

#define Error_Injection_on_Write    1
#define Error_Injection_on_Read     2
#define Disable_Error_Reporting     4
#define Enable_Error_Reporting      5

#define Disable_ECC_Error_Detection_and_Correction  0
#define Enable_ECC_Error_Detection_and_Correction   1
#define SEC_Error_Injection                         2
#define Disable_SEC_Error_Reporting                 3
#define Enable_SEC_Error_Reporting                  4
#define DED_Error_Injection                         5
#define Disable_DED_Error_Reporting                 6
#define Enable_DED_Error_Reporting                  7
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
/// PCIe Wrapper Characterization Structure
typedef struct {
  UINT8   MinAspmL1ExitLatency;     ///< Minimum ASPM L1 Exit Latency on wrapper
  UINT8   ActualL1Latency;          ///< Actual L1 Latency value for wrapper
  BOOLEAN AnyDevFailPllpdnb;        ///< Any device on wrapper cannot support PLLPDNB
} PCIe_WRAPPER_INFO;

/// PCIe Characterization Buffer
typedef struct {
  PCIe_WRAPPER_INFO WrapperInfo[NUMBER_OF_WRAPPERS];
} PCIe_INFO_BUFFER;

typedef struct {
  IN      UINT32        GroupType;       ///< Parity Group ID
  IN      UINT32        GroupID;         ///< Group Type
  IN      UINT32        StructureID;     ///< Structure ID
  IN      UINT32        ErrGenCmd;       ///< Error command
} GNB_PARITY_TABLE;
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

AGESA_STATUS
PcieMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

VOID
STATIC
PcieMidAspmInitCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  );

GNB_PARITY_TABLE GnbParityTableCZ[] = {
    { PARITY_ECC_GROUP,0,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,0,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,0,2, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,0,3, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,0,4, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,0,5, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,1,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,1,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,1,2, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,1,3, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,1,4, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,1,5, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,2,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,2,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,3,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,3,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,4,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,4,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,5,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,6,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,6,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,7,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,7,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,7,2, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,7,3, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,7,4, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,8,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,2, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,3, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,4, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,5, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,6, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,7, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,8, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,9, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,10, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,11, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,12, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,13, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,14, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,15, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,16, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,17, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,18, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,19, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,20, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,21, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,22, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,9,23, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,0, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,1, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,2, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,3, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,4, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,5, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,6, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_ECC_GROUP,10,7, Enable_ECC_Error_Detection_and_Correction },
    { PARITY_UNCORRECTABLE_GROUP,11,0, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,11,1, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,0, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,1, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,2, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,3, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,4, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,5, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,6, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,7, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,8, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,12,9, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,13,0, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,13,1, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,0, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,1, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,2, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,3, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,4, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,5, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,6, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,7, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,8, Enable_Error_Reporting },
    { PARITY_UNCORRECTABLE_GROUP,14,9, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,11,0, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,12,0, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,13,0, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,14,0, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,0, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,1, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,2, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,3, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,4, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,5, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,6, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,7, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,8, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,9, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,10, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,11, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,12, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,13, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,14, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,15,15, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,16,0, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,16,1, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,16,2, Enable_Error_Reporting },
    { PARITY_CORRECTABLE_GROUP,16,3, Enable_Error_Reporting },
};

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
PcieMidPortInitCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{

  PciePortProgramRegisterTable (PortInitMidTableCZ.Table, PortInitMidTableCZ.Length, Engine, TRUE, Pcie);
  if (PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS) || Engine->Type.Port.PortData.LinkHotplug != HotplugDisabled) {
    PcieEnableSlotPowerLimitV5 (Engine, Pcie);
  }
  if (PcieConfigIsSbPcieEngine (Engine)) {
    // Halt BIOS Timer to save power during run-time
    PcieRegisterWriteField (
      PcieConfigGetParentWrapper (Engine),
      WRAP_SPACE (PcieConfigGetParentWrapper (Engine)->WrapId, D0F0xE4_WRAP_80F1_ADDRESS),
      D0F0xE4_WRAP_80F1_ClockRate_OFFSET,
      D0F0xE4_WRAP_80F1_ClockRate_WIDTH,
      0,
      TRUE,
      Pcie
      );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Auto-Power Down electrical Idle detector
 *
 *
 * @param[in]  Wrapper         Pointer to wrapper config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 */

VOID
STATIC
PciePwrAutoPowerDownElectricalIdleDetectorCz (
  IN       PCIe_WRAPPER_CONFIG     *Wrapper,
  IN       PCIe_PLATFORM_CONFIG    *Pcie
  )
{
  UINT8   Pif;
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePwrAutoPowerDownElectricalIdleDetectorCz Enter\n");
  for (Pif = 0; Pif < Wrapper->NumberOfPIFs; Pif++) {
    PcieRegisterWriteField (
      Wrapper,
      PIF_SPACE (Wrapper->WrapId, Pif, D0F0xE4_PIF_000B_ADDRESS),
      D0F0xE4_PIF_000B_EiDetCycleMode_OFFSET,
      D0F0xE4_PIF_000B_EiDetCycleMode_WIDTH,
      0x2,
      TRUE,
      Pcie
      );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePwrAutoPowerDownElectricalIdleDetectorCz Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Master procedure to init various features on all active ports
 *
 *
 *
 *
 * @param[in]   Pcie            Pointer to global PCIe configuration
 * @retval      AGESA_STATUS
 *
 */

AGESA_STATUS
STATIC
PcieMidPortInitCZ (
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS         Status;
  PCIE_LINK_SPEED_CAP  GlobalSpeedCap;

  Status = AGESA_SUCCESS;

  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PcieMidPortInitCallbackCZ,
    NULL,
    Pcie
    );

  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PcieMidAspmInitCallbackCZ,
    NULL,
    Pcie
    );

  GlobalSpeedCap = PcieUtilGlobalGenCapability (
                     PCIE_PORT_GEN_CAP_BOOT | PCIE_GLOBAL_GEN_CAP_TRAINED_PORTS | PCIE_GLOBAL_GEN_CAP_HOTPLUG_PORTS,
                     Pcie
                     );


  PcieSetVoltageCZ (GlobalSpeedCap, Pcie);
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Clock gating
 *
 *
 *
 * @param[in]  Wrapper         Pointer to wrapper config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 */

VOID
STATIC
PciePwrClockGatingCZ (
  IN       PCIe_WRAPPER_CONFIG    *Wrapper,
  IN       PCIe_PLATFORM_CONFIG   *Pcie
  )
{
  D0F0xE4_CORE_0118_STRUCT  D0F0xE4_CORE_0118;
  D0F0xE4_CORE_0011_STRUCT  D0F0xE4_CORE_0011;

  IDS_HDT_CONSOLE (GNB_TRACE, "PciePwrClockGatingCZ Enter\n");

  if ((Wrapper->Features.ClkGating == 0x1) || (Wrapper->Features.TxclkGatingPllPowerDown == 0x1) || (Wrapper->Features.LclkGating == 0x1)) {
    D0F0xE4_CORE_0118.Value = PcieRegisterRead (
                                Wrapper,
                                CORE_SPACE (Wrapper->StartPcieCoreId, D0F0xE4_CORE_0118_ADDRESS),
                                Pcie
                                );

    D0F0xE4_CORE_0011.Value = PcieRegisterRead (
                                Wrapper,
                                CORE_SPACE (Wrapper->StartPcieCoreId, D0F0xE4_CORE_0011_ADDRESS),
                                Pcie
                                );

    if (Wrapper->Features.ClkGating == 0x1) {
      //TXCLK_PERM gating enable
      D0F0xE4_CORE_0118.Field.TXCLK_PERM_GATE_ENABLE = 0x1;
      D0F0xE4_CORE_0118.Field.TXCLK_PERM_GATE_LATENCY = 0x1;
      D0F0xE4_CORE_0118.Field.RCVR_DET_CLK_ENABLE = 0x1;
      D0F0xE4_CORE_0011.Field.DynClkLatency = 0xf;

      //TXCLK DYN gating enable
      D0F0xE4_CORE_0118.Field.TXCLK_DYN_GATE_ENABLE = 0x1;
      D0F0xE4_CORE_0118.Field.TXCLK_DYN_GATE_LATENCY = 0x1;

      //TXCLK REGS gating enable
      D0F0xE4_CORE_0118.Field.TXCLK_REGS_GATE_ENABLE = 0x1;
      D0F0xE4_CORE_0118.Field.TXCLK_REGS_GATE_LATENCY = 0x1;

      //TXCLK PRBS gating enable
      D0F0xE4_CORE_0118.Field.TXCLK_PRBS_GATE_ENABLE = 0x1;

      //TXCLK LCNT gating enable
      D0F0xE4_CORE_0118.Field.TXCLK_LCNT_GATE_ENABLE = 0x1;

      //TXCLK PIF1X gating enable
      D0F0xE4_CORE_0118.Field.TXCLK_PIF_GATE_ENABLE = 0x1;

      //REFCLK REGS gating enable
      D0F0xE4_CORE_0118.Field.REFCLK_REGS_GATE_ENABLE = 0x1;
      D0F0xE4_CORE_0118.Field.REFCLK_REGS_GATE_LATENCY = 0x1;
    }
    if (Wrapper->Features.TxclkGatingPllPowerDown == 0x1) {
      D0F0xE4_CORE_0118.Field.TXCLK_PERM_GATE_PLL_PDN = 0x1;
    }

    if (Wrapper->Features.LclkGating == 0x1) {
      //PCIE LCLK gating enable
      D0F0xE4_CORE_0118.Field.LCLK_DYN_GATE_ENABLE = 0x1;
      D0F0xE4_CORE_0118.Field.LCLK_GATE_TXCLK_FREE = 0x0;
      D0F0xE4_CORE_0118.Field.LCLK_DYN_GATE_LATENCY = 0x1;
    }

    PcieRegisterWrite (
      Wrapper,
      CORE_SPACE (Wrapper->StartPcieCoreId, D0F0xE4_CORE_0118_ADDRESS),
      D0F0xE4_CORE_0118.Value,
      TRUE,
      Pcie
      );
    PcieRegisterWrite (
      Wrapper,
      CORE_SPACE (Wrapper->StartPcieCoreId, D0F0xE4_CORE_0011_ADDRESS),
      D0F0xE4_CORE_0011.Value,
      TRUE,
      Pcie
      );
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePwrClockGatingCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Per wrapper Pcie Mid Init.
 *
 *
 * @param[in]  Wrapper         Pointer to wrapper configuration descriptor
 * @param[in]  Buffer          Pointer buffer
 * @param[in]  Pcie            Pointer to global PCIe configuration
 */
AGESA_STATUS
STATIC
PcieMidInitCallbackCZ (
  IN       PCIe_WRAPPER_CONFIG           *Wrapper,
  IN OUT   VOID                          *Buffer,
  IN       PCIe_PLATFORM_CONFIG          *Pcie
  )
{
  PciePwrAutoPowerDownElectricalIdleDetectorCz (Wrapper, Pcie);
  PciePwrPowerDownUnusedLanesCZ (Wrapper, Pcie);
  PciePwrClockGatingCZ (Wrapper, Pcie);
  PcieLockRegisters (Wrapper, Pcie);

  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie Mid Init
 *
 *   Late PCIe initialization
 *
 * @param[in]  Pcie                Pointer to global PCIe configuration
 * @retval     AGESA_SUCCESS       Topology successfully mapped
 * @retval     AGESA_ERROR         Topology can not be mapped
 */

AGESA_STATUS
STATIC
PcieMidInitCZ (
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS          AgesaStatus;
  AGESA_STATUS          Status;
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidInitCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;

  IDS_OPTION_HOOK (IDS_BEFORE_POWER_GATING, Pcie, GnbLibGetHeader (Pcie));
  Status = PcieConfigRunProcForAllWrappers (DESCRIPTOR_ALL_WRAPPERS, PcieMidInitCallbackCZ, NULL, Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  Status = PciePowerGateCZ (Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidInitCZ Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}

VOID
STATIC
PcieAerInitCZ (
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_AER_CONFIG          AerConfig;
  PCIe_PORT_AER_CONFIG     PortAerConfigBuffer[NUMBER_OF_PORTS];
  UINT32                   RegisterValue;
  UINT8                    Index;
  UINT8                    DevIndex;
  BOOLEAN                  AerEnable;
  D0F0x64_x16_STRUCT       D0F0x64_x16;
  D0F0xE4_CORE_00B0_STRUCT D0F0xE4_CORE_00B0;
  D0F0xE4_CORE_00C0_STRUCT D0F0xE4_CORE_00C0;
  D0F0xE4_WRAP_000A_STRUCT D0F0xE4_WRAP_000A;
  D0F0xE4_WRAP_0003_STRUCT D0F0xE4_WRAP_0003;
  D0F0xE4_WRAP_0004_STRUCT D0F0xE4_WRAP_0004;
  DxFxx60_STRUCT           DxFxx60;
  DxFxx74_STRUCT           DxFxx74;
  DxFxx2A6_STRUCT          DxFxx2A6;
  DxFxx168_STRUCT          DxFxx168;
  DxFxxE4_x6A_STRUCT       DxFxxE4_x6A;
  DxFxx17C_STRUCT          DxFxx17C;
  DxFxxE4_x70_STRUCT       DxFxxE4_x70;
  UINT8                    WrapId;
  UINT8                    CoreId;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAerInitCZ Enter\n");

  AerEnable = FALSE;
  LibAmdMemFill (PortAerConfigBuffer, 0x00, sizeof (PCIe_PORT_AER_CONFIG) * NUMBER_OF_PORTS, GnbLibGetHeader (Pcie));
  AerConfig.PortAerConfig = (PCIe_PORT_AER_CONFIG *)PortAerConfigBuffer;
  AerConfig.NumberOfPorts = NUMBER_OF_PORTS;
  IDS_HDT_CONSOLE (GNB_TRACE, "Number of ports in GNB: %d\n", NUMBER_OF_PORTS);

  IDS_OPTION_CALLOUT (IDS_CALLOUT_GNB_PCIE_AER_CONFIG, &AerConfig, GnbLibGetHeader (Pcie));

  for (DevIndex = 2; DevIndex <= 3; DevIndex++) {
    for (Index = 0; Index < 5; Index++) {
      GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, 0), AccessWidth32, &RegisterValue, GnbLibGetHeader (Pcie));
      if ((AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].PortAerEnable == TRUE) && (RegisterValue != 0xFFFFFFFF)) {

        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx15C_ADDRESS), AccessWidth32, &RegisterValue, GnbLibGetHeader (Pcie));
        RegisterValue &= ~(
          DxFxx15C_DlpErrSeverity_MASK |
          DxFxx15C_PsnErrSeverity_MASK |
          DxFxx15C_CplTimeoutSeverity_MASK |
          DxFxx15C_CplAbortErrSeverity_MASK |
          DxFxx15C_UnexpCplSeverity_MASK |
          DxFxx15C_MalTlpSeverity_MASK |
          DxFxx15C_EcrcErrSeverity_MASK |
          DxFxx15C_UnsuppReqErrSeverity_MASK |
          DxFxx15C_AcsViolationSeverity_MASK
          );
        AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].UncorrectableSeverity.Value &= (
          DxFxx15C_DlpErrSeverity_MASK |
          DxFxx15C_PsnErrSeverity_MASK |
          DxFxx15C_CplTimeoutSeverity_MASK |
          DxFxx15C_CplAbortErrSeverity_MASK |
          DxFxx15C_UnexpCplSeverity_MASK |
          DxFxx15C_MalTlpSeverity_MASK |
          DxFxx15C_EcrcErrSeverity_MASK |
          DxFxx15C_UnsuppReqErrSeverity_MASK |
          DxFxx15C_AcsViolationSeverity_MASK
          );
        RegisterValue |= AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].UncorrectableSeverity.Value;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx15C_ADDRESS), AccessS3SaveWidth32, &RegisterValue, GnbLibGetHeader (Pcie));

        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx158_ADDRESS), AccessS3SaveWidth32, &RegisterValue, GnbLibGetHeader (Pcie));
        RegisterValue &= ~(
          DxFxx158_DlpErrMask_MASK |
          DxFxx158_PsnErrMask_MASK |
          DxFxx158_CplTimeoutMask_MASK |
          DxFxx158_CplAbortErrMask_MASK |
          DxFxx158_UnexpCplMask_MASK |
          DxFxx158_MalTlpMask_MASK |
          DxFxx158_EcrcErrMask_MASK |
          DxFxx158_UnsuppReqErrMask_MASK |
          DxFxx158_AcsViolationMask_MASK
          );
        AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].UncorrectableMask.Value &= (
          DxFxx158_DlpErrMask_MASK |
          DxFxx158_PsnErrMask_MASK |
          DxFxx158_CplTimeoutMask_MASK |
          DxFxx158_CplAbortErrMask_MASK |
          DxFxx158_UnexpCplMask_MASK |
          DxFxx158_MalTlpMask_MASK |
          DxFxx158_EcrcErrMask_MASK |
          DxFxx158_UnsuppReqErrMask_MASK |
          DxFxx158_AcsViolationMask_MASK
          );
        RegisterValue |= AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].UncorrectableMask.Value;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx158_ADDRESS), AccessS3SaveWidth32, &RegisterValue, GnbLibGetHeader (Pcie));

        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx164_ADDRESS), AccessS3SaveWidth32, &RegisterValue, GnbLibGetHeader (Pcie));
        RegisterValue &= ~(
          DxFxx164_BadTlpMask_MASK |
          DxFxx164_BadDllpMask_MASK |
          DxFxx164_ReplayNumRolloverMask_MASK |
          DxFxx164_ReplayTimerTimeoutMask_MASK |
          DxFxx164_AdvisoryNonfatalErrMask_MASK
          );
        AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].CorrectableMask.Value &= (
          DxFxx164_BadTlpMask_MASK |
          DxFxx164_BadDllpMask_MASK |
          DxFxx164_ReplayNumRolloverMask_MASK |
          DxFxx164_ReplayTimerTimeoutMask_MASK |
          DxFxx164_AdvisoryNonfatalErrMask_MASK
          );
        RegisterValue |= AerConfig.PortAerConfig[((DevIndex - 2) * 5) + Index].CorrectableMask.Value;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx164_ADDRESS), AccessS3SaveWidth32, &RegisterValue, GnbLibGetHeader (Pcie));

        // Enable sending of ERR messages at Port level
        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx60_ADDRESS), AccessS3SaveWidth32, &DxFxx60.Value, GnbLibGetHeader (Pcie));
        DxFxx60.Field.CorrErrEn = 0x1;
        DxFxx60.Field.NonFatalErrEn = 0x1;
        DxFxx60.Field.FatalErrEn = 0x1;
        DxFxx60.Field.UsrReportEn = 0x1;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx60_ADDRESS), AccessS3SaveWidth32, &DxFxx60.Value, GnbLibGetHeader (Pcie));

        //Enable System Error (SERR) generation on errors per port
        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx74_ADDRESS), AccessS3SaveWidth32, &DxFxx74.Value, GnbLibGetHeader (Pcie));
        DxFxx74.Field.SerrOnCorrErrEn = 0x1;
        DxFxx74.Field.SerrOnNonFatalErrEn = 0x1;
        DxFxx74.Field.SerrOnFatalErrEn = 0x1;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx74_ADDRESS), AccessS3SaveWidth32, &DxFxx74.Value, GnbLibGetHeader (Pcie));

        // Enable ACS sub-item per port
        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx2A6_ADDRESS), AccessS3SaveWidth32, &DxFxx2A6.Value, GnbLibGetHeader (Pcie));
        DxFxx2A6.Field.SourceValidationEn = 0x1;
        DxFxx2A6.Field.TranslationBlockingEn = 0x1;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx2A6_ADDRESS), AccessS3SaveWidth32, &DxFxx2A6.Value, GnbLibGetHeader (Pcie));

        // Enable ECRC checking
        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx168_ADDRESS), AccessS3SaveWidth32, &DxFxx168.Value, GnbLibGetHeader (Pcie));
        DxFxx168.Field.EcrcCheckEn = 0x1;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx168_ADDRESS), AccessS3SaveWidth32, &DxFxx168.Value, GnbLibGetHeader (Pcie));

        // Enable PSN_ADVISORY_NONFATAL and Error Log Feature per port
        GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxxE0_ADDRESS), DxFxxE4_x6A_ADDRESS, AccessS3SaveWidth32, &DxFxxE4_x6A.Value, GnbLibGetHeader (Pcie));
        DxFxxE4_x6A.Field.StrapPoisonedAdvisoryNonfatal = 0x1;
        DxFxxE4_x6A.Field.StrapFirstRcvdErrLog = 0x1;
        // Enable error reporting
        DxFxxE4_x6A.Field.ErrReportingDis = 0x0;
        GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxxE0_ADDRESS), DxFxxE4_x6A_ADDRESS, AccessS3SaveWidth32, &DxFxxE4_x6A.Value, GnbLibGetHeader (Pcie));

        // Enable interrupt generation on errors per port
        GnbLibPciRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx17C_ADDRESS), AccessS3SaveWidth32, &DxFxx17C.Value, GnbLibGetHeader (Pcie));
        DxFxx17C.Field.CorrErrRepEn = 0x1;
        DxFxx17C.Field.NonfatalErrRepEn = 0x1;
        DxFxx17C.Field.CorrErrRepEn = 0x1;
        GnbLibPciWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxx17C_ADDRESS), AccessS3SaveWidth32, &DxFxx17C.Value, GnbLibGetHeader (Pcie));

        // Disable error ignore control per port
        GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxxE0_ADDRESS), DxFxxE4_x70_ADDRESS, AccessS3SaveWidth32, &DxFxxE4_x70.Value, GnbLibGetHeader (Pcie));
        DxFxxE4_x70.Value = 0x0;
        GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, DevIndex, Index + 1, DxFxxE0_ADDRESS), DxFxxE4_x70_ADDRESS, AccessS3SaveWidth32, &DxFxxE4_x70.Value, GnbLibGetHeader (Pcie));

        AerEnable = TRUE;
      }
    }
  }

  if (AerEnable) {
    //Enable AER feature interface in IOC
    GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0x60_ADDRESS), D0F0x64_x16_ADDRESS, AccessS3SaveWidth32, &D0F0x64_x16.Value, GnbLibGetHeader (Pcie));
    D0F0x64_x16.Field.AerUrMsgEn = 0x1;
    D0F0x64_x16.Field.PCIE0AerCredits = 0x1;
    D0F0x64_x16.Field.PCIE1AerCredits = 0x1;
    GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0x60_ADDRESS), D0F0x64_x16_ADDRESS, AccessS3SaveWidth32, &D0F0x64_x16.Value, GnbLibGetHeader (Pcie));

    //Enable AER capability at Core level
    for (CoreId = 0; CoreId < 2; CoreId++) {
      GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), CORE_SPACE (CoreId, D0F0xE4_CORE_00B0_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_CORE_00B0.Value, GnbLibGetHeader (Pcie));
      D0F0xE4_CORE_00B0.Field.StrapF0AerEn = 0x1;
      D0F0xE4_CORE_00B0.Field.StrapF0AcsEn = 0x1;
      D0F0xE4_CORE_00B0.Field.StrapF0CplAbortErrEn = 0x1;
      D0F0xE4_CORE_00B0.Field.StrapF0EcrcCheckEn = 0x1;
      GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), CORE_SPACE (CoreId, D0F0xE4_CORE_00B0_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_CORE_00B0.Value, GnbLibGetHeader (Pcie));

      GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), CORE_SPACE (CoreId, D0F0xE4_CORE_00C0_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_CORE_00C0.Value, GnbLibGetHeader (Pcie));
      D0F0xE4_CORE_00C0.Field.StrapEcn1p1En = 0x1;
      GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), CORE_SPACE (CoreId, D0F0xE4_CORE_00C0_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_CORE_00C0.Value, GnbLibGetHeader (Pcie));
    }

    for (WrapId = 0; WrapId < 2; WrapId++) {
      GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), WRAP_SPACE (WrapId, D0F0xE4_WRAP_000A_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_WRAP_000A.Value, GnbLibGetHeader (Pcie));
      D0F0xE4_WRAP_000A.Field.STRAP_BIF_ACS_EN = 0x1;
      D0F0xE4_WRAP_000A.Field.STRAP_BIF_ACS_SOURCE_VALIDATION = 0x1;
      D0F0xE4_WRAP_000A.Field.STRAP_BIF_ACS_TRANSLATION_BLOCKING = 0x1;
      GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), WRAP_SPACE (WrapId, D0F0xE4_WRAP_000A_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_WRAP_000A.Value, GnbLibGetHeader (Pcie));

      GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), WRAP_SPACE (WrapId, D0F0xE4_WRAP_0003_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_WRAP_0003.Value, GnbLibGetHeader (Pcie));
      D0F0xE4_WRAP_0003.Field.STRAP_BIF_ECRC_CHECK_EN = 0x1;
      GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), WRAP_SPACE (WrapId, D0F0xE4_WRAP_0003_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_WRAP_0003.Value, GnbLibGetHeader (Pcie));

      GnbLibPciIndirectRead (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), WRAP_SPACE (WrapId, D0F0xE4_WRAP_0004_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_WRAP_0004.Value, GnbLibGetHeader (Pcie));
      D0F0xE4_WRAP_0004.Value = 0x0;
      GnbLibPciIndirectWrite (MAKE_SBDFO (0, 0, 0, 0, D0F0xE0_ADDRESS), WRAP_SPACE (WrapId, D0F0xE4_WRAP_0004_ADDRESS), AccessS3SaveWidth32, &D0F0xE4_WRAP_0004.Value, GnbLibGetHeader (Pcie));
    }
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAerInitCZ Exit\n");
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GNB PCIe Internal Parity Error Configuration
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 *
 */
 VOID
STATIC
GnbParityErrorConfig (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  GNB_HANDLE                *GnbHandle;
  UINTN                     i;
  D0F0xC4_x1_STRUCT         D0F0xC4_x1;
  GNB_BUILD_OPTIONS_CZ    *GnbBuildOptionData;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbParityErrorConfig Enter\n");

  GnbHandle = GnbGetHandle (StdHeader);

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  if (GnbBuildOptionData->CfgParityErrorConfiguration == FALSE) {
    return;
  }

  for ( i = 0; i < sizeof (GnbParityTableCZ) / sizeof (GNB_PARITY_TABLE); i++) {
    D0F0xC4_x1.Value = 0x0;
    GnbRegisterWriteCZ (GnbHandle, D0F0xC4_x1_TYPE, D0F0xC4_x1_ADDRESS, &D0F0xC4_x1.Value, AccessWidth32, StdHeader);

    do {
      GnbRegisterReadCZ (GnbHandle, D0F0xC4_x1_TYPE, D0F0xC4_x1_ADDRESS, &D0F0xC4_x1.Value, 0, StdHeader);
    } while (D0F0xC4_x1.Field.ParityErrGenInjectAllow != 0x1);

    D0F0xC4_x1.Field.ParityErrGenGroupSel = GnbParityTableCZ[i].GroupID;
    if (GnbParityTableCZ[i].GroupType != PARITY_ECC_GROUP) {
      D0F0xC4_x1.Field.ParityErrGenGroupTypeSel = GnbParityTableCZ[i].GroupType;
    }
    D0F0xC4_x1.Field.ParityErrGenIdSel = GnbParityTableCZ[i].StructureID;
    D0F0xC4_x1.Field.ParityErrGenCmd = GnbParityTableCZ[i].ErrGenCmd;

    GnbRegisterWriteCZ (GnbHandle, D0F0xC4_x1_TYPE, D0F0xC4_x1_ADDRESS, &D0F0xC4_x1.Value, AccessWidth32, StdHeader);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbParityErrorConfig Exit\n");
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to characterize all active ports / sublinks
 *
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer
 * @param[in]       Pcie            Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieMidPortCharacterizationCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_WRAPPER_INFO       *WrapperInfo;
  PCIe_ASPM_LATENCY_INFO  LinkLatencyInfo;

  WrapperInfo = &(((PCIe_INFO_BUFFER *)Buffer)->WrapperInfo[PcieConfigGetParentWrapper (Engine)->WrapId]);

  LinkLatencyInfo.MaxL1ExitLatency = 255;
  LinkLatencyInfo.MaxL0sExitLatency = 255;

  if (PcieConfigCheckPortStatus (Engine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
    // Determine minimum L1 exit latency for this engine
    PcieAspmGetMinExitLatency (Engine->Type.Port.Address, &LinkLatencyInfo, GnbLibGetHeader (Pcie));
    if (LinkLatencyInfo.MaxL1ExitLatency < WrapperInfo->MinAspmL1ExitLatency) {
      WrapperInfo->MinAspmL1ExitLatency = LinkLatencyInfo.MaxL1ExitLatency;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to characterize all wrappers
 *
 *
 *
 *
 * @param[in]       Wrapper         Pointer to wrapper config descriptor
 * @param[in, out]  Buffer
 * @param[in]       Pcie            Pointer to global PCIe configuration
 * @retval          AGESA_SUCCESS   Topology successfully mapped
 *
 */

AGESA_STATUS
STATIC
PcieMidWrapperCharacterizationCallbackCZ (
  IN       PCIe_WRAPPER_CONFIG   *Wrapper,
  IN       VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_WRAPPER_INFO       *WrapperInfo;
  UINT8                   Pif;
  D0F0xE4_PIF_0004_STRUCT D0F0xE4_PIF_0004;
  UINT32                  ActiveLaneBitmap;
  UINT8                   LinkNumber;

  LinkNumber = 0;
  WrapperInfo = &(((PCIe_INFO_BUFFER *)Buffer)->WrapperInfo[Wrapper->WrapId]);

  // calculate Actual_L1_Latency: Actual_L1_Latency = PLL Ramp-up time + (number of links in between EP and root port - 0x1) * 1us
  ActiveLaneBitmap = PcieUtilGetWrapperLaneBitMap (LANE_TYPE_PCIE_PHY_NATIVE_ACTIVE | LANE_TYPE_PCIE_PHY_NATIVE_HOTPLUG, 0, Wrapper);

  do {
    if ((ActiveLaneBitmap & BIT0) == BIT0) {
      LinkNumber++;
    }
    ActiveLaneBitmap = ActiveLaneBitmap >> 1;
  } while (ActiveLaneBitmap != 0);

  WrapperInfo->ActualL1Latency = PLL_RAMP_UP_TIME + LinkNumber;

  if (WrapperInfo->MinAspmL1ExitLatency < WrapperInfo->ActualL1Latency) {
    WrapperInfo->AnyDevFailPllpdnb = TRUE;
  }

  if ((WrapperInfo->MinAspmL1ExitLatency > NB_L1_EXITING_LATENCY_CZ) && (Wrapper->Features.PllOffInL1 != 0) && (!WrapperInfo->AnyDevFailPllpdnb)) {
    IDS_HDT_CONSOLE (GNB_TRACE, "Minimum ASPM L1 Exit Latency on wrapper %x\n", WrapperInfo->MinAspmL1ExitLatency);
    IDS_HDT_CONSOLE (GNB_TRACE, "NB_L1_EXITING_LATENCY_CZ %x\n", NB_L1_EXITING_LATENCY_CZ);
    IDS_HDT_CONSOLE (GNB_TRACE, "calculate Actual_L1_Latency %x\n", WrapperInfo->ActualL1Latency);
    IDS_HDT_CONSOLE (GNB_TRACE, "AnyDevFailPllpdnb %x\n", WrapperInfo->AnyDevFailPllpdnb);
    for (Pif = 0; Pif < Wrapper->NumberOfPIFs; Pif++) {
      D0F0xE4_PIF_0004.Value = PcieRegisterRead (
                                 Wrapper,
                                 PIF_SPACE (Wrapper->WrapId, Pif, D0F0xE4_PIF_0004_ADDRESS),
                                 Pcie
                                 );
      D0F0xE4_PIF_0004.Field.PifPllPwrdnEn = 1;
      PcieRegisterWrite (
          Wrapper,
          PIF_SPACE (Wrapper->WrapId, Pif, D0F0xE4_PIF_0004_ADDRESS),
          D0F0xE4_PIF_0004.Value,
          TRUE,
          Pcie
        );
    }
  }

  return (AGESA_SUCCESS);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Pcie Mid Characterization
 *
 *   Mid PCIe Characterization
 *
 * @param[in, out]  PcieInfoBuffer      Pointer to PCIe characterization info
 * @param[in]       Pcie                Pointer to global PCIe configuration
 * @retval          AGESA_SUCCESS       Topology successfully mapped
 * @retval          AGESA_ERROR         Topology can not be mapped
 */

AGESA_STATUS
STATIC
PcieMidCharacterizationCZ (
  IN OUT   PCIe_INFO_BUFFER      *PcieInfoBuffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS          AgesaStatus;
  AGESA_STATUS          Status;
  UINT8                 Index;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidCharacterizationCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;

  // Set initial stats for all PcieInfoBuffer fields
  for (Index = 0; Index < NUMBER_OF_WRAPPERS; Index++) {
    ((PCIe_INFO_BUFFER *) PcieInfoBuffer)->WrapperInfo[Index].MinAspmL1ExitLatency = 255;
    ((PCIe_INFO_BUFFER *) PcieInfoBuffer)->WrapperInfo[Index].AnyDevFailPllpdnb = FALSE;
  }

  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    PcieMidPortCharacterizationCallbackCZ,
    (VOID *) PcieInfoBuffer,
    Pcie
    );

  Status = PcieConfigRunProcForAllWrappers (
             DESCRIPTOR_ALL_WRAPPERS,
             PcieMidWrapperCharacterizationCallbackCZ,
             (VOID *) PcieInfoBuffer,
             Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidCharacterizationCZ Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Mid Init
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */
AGESA_STATUS
PcieMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS          AgesaStatus;
  AGESA_STATUS          Status;
  PCIe_PLATFORM_CONFIG  *Pcie;
  PCIe_INFO_BUFFER      PcieInfoBuffer;

  AGESA_TESTPOINT (TpPcieMidInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidInterfaceCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    PciePortsVisibilityControl (UnhidePorts, Pcie);

    Status = PcieMidCharacterizationCZ (&PcieInfoBuffer, Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    Status = PcieMidPortInitCZ (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    Status = PcieMidInitCZ (Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    Status = PcieAriInitCZ (StdHeader, Pcie);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    ASSERT (Status == AGESA_SUCCESS);

    PcieAerInitCZ (Pcie);

    GnbParityErrorConfig (StdHeader);

    PciePortsVisibilityControl (HidePorts, Pcie);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieMidInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpPcieMidInterfaceCZExit, NULL);
  return  AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to init ASPM on all active ports
 *
 *
 *
 *
 * @param[in]       Engine          Pointer to engine config descriptor
 * @param[in, out]  Buffer          PortCount
 * @param[in]       Pcie            Pointer to global PCIe configuration
 *
 */

VOID
STATIC
PcieMidAspmInitCallbackCZ (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PcieEnableAspm (Engine,  Pcie);
}
