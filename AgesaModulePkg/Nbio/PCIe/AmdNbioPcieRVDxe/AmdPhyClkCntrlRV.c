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
#include <GnbRegistersRV.h>
#include <GnbDxio.h>
#include <Library/PcieConfigLib.h>
//#include <Guid/GnbPcieInfoHob.h>
#include <Library/NbioHandleLib.h>
#include <Library/SmnAccessLib.h>
#include <Library/BaseLib.h>

#define FILECODE        NBIO_PCIE_AMDNBIOSPCIERVDXE_AMDPHYCLKCNTRLRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define NUMBER_OF_CLKREQB   7

//
// Register Name SATA_AHCI_GHC_PRT_CFG
// Description : This register is Resevred
// Reset condtion: PGFSM_IP_hardreset. This register is writeable only when Global Option Register bit [0] is set. Implementation Note: Project-dependent default will be evaluated to this equation {$FCH_ARCH_SATA_PORT_TOTAL{1?b1}}, that is, since these fields are bit-significant, the number of bits being set will depend on the total number of ports supported in the SATA controller. This variable $FCH_ARCH_SATA_PORT_TOTAL is an architectural define in RTL, and shall be larger than or equal to NP (number of ports), but should be distinguished from NP. For example, in Erie, there are total of 6 ports, so PxCMD.FBSCP will have a value of 3Fh. Each field is dedicated to the theoretical maximum number of ports, presumably 8, on each project variants. For projects that have number of ports less than 8, the remaining bits will be treated as don?t care, yet still read/write-able.
//

// Address
#define SMN_SATA_AHCI_GHC_PRT_CFG_ADDRESS                      0x31010f8UL

/// Bitfield Description : Reserved.
///  Read & Write & bit-significant.
/// Each bit controls PxCMD.HPCP(bit 18 of ABAR+ portoffset + 18h):
/// If set to 1, this port's signal and power connector is externally accessible via a joint signal and power connector for blindmate device hot plug.
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_HPCP_OFFSET            0
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_HPCP_WIDTH             8
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_HPCP_MASK              0xff

/// Bitfield Description : Reserved.
///  Read & Write & bit-significant.
/// Each bit controls PxCMD.MPSP(bit 19 of ABAR+ portoffset + 18h):
/// If set to 1, the platform supports a mechanical presence switch attached to this port.
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_MPSP_OFFSET            8
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_MPSP_WIDTH             8
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_MPSP_MASK              0xff00

/// Bitfield Description : Reserved.
///  Read & Write & bit-significant.
/// Each bit controls PxCMD.ESP(bit 21 of ABAR+ portoffset + 18h):
/// If set to 1, this port?s signal connector is externally accessible on a signal only connector
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_ESP_OFFSET             16
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_ESP_WIDTH              8
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_ESP_MASK               0xff0000

/// Bitfield Description : Reserved.
///  Read & Write & bit-significant.
/// Each bit controls PxCMD.FBSCP (bit 22 of ABAR + portoffset + 18h):
/// When set to 1, indicates that this port supports Port Multiplier FIS-based-switching (FBS).
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_FBSCP_OFFSET           24
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_FBSCP_WIDTH            8
#define SATA_AHCI_GHC_PRT_CFG_GHC_PxCMD_FBSCP_MASK             0xff000000L

/// SATAAHCI_000000F8
typedef union {
  struct {
    UINT32                                          GHC_PxCMD_HPCP:8 ; ///<
    UINT32                                          GHC_PxCMD_MPSP:8 ; ///<
    UINT32                                           GHC_PxCMD_ESP:8 ; ///<
    UINT32                                         GHC_PxCMD_FBSCP:8 ; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SATA_AHCI_GHC_PRT_CFG_STRUCT;

//
// Register Name SATA_AHCI_P_SSTS
// Description : Reserved.
//

// Address
#define SMN_SATA0_AHCI_P_SSTS_ADDRESS                           0x3101128UL
#define SMN_SATA1_AHCI_P_SSTS_ADDRESS                           0x31011a8UL


/// Bitfield Description : Indicates the interface device detection and Phy state.
#define SATA_AHCI_P_SSTS_P_SSTS_DET_OFFSET                     0
#define SATA_AHCI_P_SSTS_P_SSTS_DET_WIDTH                      4
#define SATA_AHCI_P_SSTS_P_SSTS_DET_MASK                       0xf

/// Bitfield Description : Indicates the negotiated interface communication speed.
#define SATA_AHCI_P_SSTS_P_SSTS_SPD_OFFSET                     4
#define SATA_AHCI_P_SSTS_P_SSTS_SPD_WIDTH                      4
#define SATA_AHCI_P_SSTS_P_SSTS_SPD_MASK                       0xf0

/// Bitfield Description : Indicates the current interface state.
#define SATA_AHCI_P_SSTS_P_SSTS_IPM_OFFSET                     8
#define SATA_AHCI_P_SSTS_P_SSTS_IPM_WIDTH                      4
#define SATA_AHCI_P_SSTS_P_SSTS_IPM_MASK                       0xf00

/// Bitfield Description : Reserved.
#define SATA_AHCI_P_SSTS_P_SSTS_Reserved_OFFSET                12
#define SATA_AHCI_P_SSTS_P_SSTS_Reserved_WIDTH                 20
#define SATA_AHCI_P_SSTS_P_SSTS_Reserved_MASK                  0xfffff000L

/// SATAPORT0SMN_00000028
typedef union {
  struct {
    UINT32                                              P_SSTS_DET:4 ; ///<
    UINT32                                              P_SSTS_SPD:4 ; ///<
    UINT32                                              P_SSTS_IPM:4 ; ///<
    UINT32                                         P_SSTS_Reserved:20; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SATA_AHCI_P_SSTS_STRUCT;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/// PHY Usage Structure
typedef struct {
  BOOLEAN         PHY_A0_PCIe;                          ///< PHY A0, LANES 2/3
  BOOLEAN         PHY_A1_SATA;                          ///< PHY A1, LANES 0/1
  BOOLEAN         PHY_A2_PCIe;                          ///< PHY A2, LANES 4/7
  BOOLEAN         PHY_A3_4_PCIe;                        ///< PHY A3/4, LANES 8/15
  UINT8           PHY_A0_PCIe_Mask;                     ///< CLKREQb mask for PHY_A0_PCIe
  UINT8           PHY_A1_SATA_Mask;                     ///< CLKREQb mask for PHY_A1_SATA
  UINT8           PHY_A2_PCIe_Mask;                     ///< CLKREQb mask for PHY_A2_PCIe
  UINT8           PHY_A3_4_PCIe_Mask;                   ///< CLKREQb mask for PHY_A3_4_PCIe
} PCIE_PHY_USAGE_STRUCT;


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
AmdPhyControlCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIE_PHY_USAGE_STRUCT         *Usage;
  UINT32                        LaneNumber;

  Usage = (PCIE_PHY_USAGE_STRUCT *) Buffer;

  if ((Engine->InitStatus == INIT_STATUS_PCIE_TRAINING_SUCCESS) ||
     ((Engine->Type.Port.PortData.LinkHotplug != HotplugDisabled) &&
      (Engine->Type.Port.PortData.LinkHotplug != HotplugInboard))) {
      for (LaneNumber = Engine->EngineData.StartLane; LaneNumber <= Engine->EngineData.EndLane; LaneNumber++) {
      switch (LaneNumber) {
      case 0:
      case 1:
        Usage->PHY_A0_PCIe = TRUE;
        if ((Engine->Type.Port.ClkReq != 0) && (Engine->Type.Port.ClkReq <= NUMBER_OF_CLKREQB)) {
          Usage->PHY_A0_PCIe_Mask |= (1 << (Engine->Type.Port.ClkReq - 1));
        }
        break;
      case 2:
      case 3:
        Usage->PHY_A1_SATA = TRUE;
        if ((Engine->Type.Port.ClkReq != 0) && (Engine->Type.Port.ClkReq <= NUMBER_OF_CLKREQB)) {
          Usage->PHY_A1_SATA_Mask |= (1 << (Engine->Type.Port.ClkReq - 1));
        }
        break;
      case 4:
      case 5:
      case 6:
      case 7:
        Usage->PHY_A2_PCIe = TRUE;
        if ((Engine->Type.Port.ClkReq != 0) && (Engine->Type.Port.ClkReq <= NUMBER_OF_CLKREQB)) {
          Usage->PHY_A2_PCIe_Mask |= (1 << (Engine->Type.Port.ClkReq - 1));
        }
        break;
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
        Usage->PHY_A3_4_PCIe = TRUE;
        if ((Engine->Type.Port.ClkReq != 0) && (Engine->Type.Port.ClkReq <= NUMBER_OF_CLKREQB)) {
          Usage->PHY_A3_4_PCIe_Mask |= (1 << (Engine->Type.Port.ClkReq - 1));
        }
        break;
      }
    }
  }
  return;
}


/**
 *---------------------------------------------------------------------------------------
 *  AmdPciePhyClkCntrl
 *
 *  Description:
 *     Configure PHY Clock Control
 *  Parameters:
 *    @param[in]     Pcie   PCIe_PLATFORM_CONFIG pointer
 *
 *    @retval         VOID
 *
 *---------------------------------------------------------------------------------------
 **/

VOID
AmdPciePhyClkCntrl (
  IN       PCIe_PLATFORM_CONFIG       *Pcie
  )

{
  GNB_HANDLE                    *GnbHandle;
  PCIE_PHY_USAGE_STRUCT         Usage;
  BOOLEAN                       EnableDynamicControl;
  BOOLEAN                       SataDrivePresent;
  NBIFSTRAP0_STRUCT             Strap0;
  SATA_AHCI_GHC_PRT_CFG_STRUCT  GhcPrtCfg;
  SATA_AHCI_P_SSTS_STRUCT       PSsts;

    IDS_HDT_CONSOLE (GNB_TRACE, "AmdPciePhyClkCntrl Entry\n");

  Usage.PHY_A0_PCIe = FALSE;
  Usage.PHY_A1_SATA = FALSE;
  Usage.PHY_A2_PCIe = FALSE;
  Usage.PHY_A3_4_PCIe = FALSE;
  PcieConfigRunProcForAllEngines (
    DESCRIPTOR_ALLOCATED | DESCRIPTOR_PCIE_ENGINE,
    AmdPhyControlCallback,
    (VOID *) &Usage,
    Pcie
    );

  if (Usage.PHY_A0_PCIe == FALSE) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A0 FALSE\n");
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A0 TRUE\n");
  }
  if (Usage.PHY_A1_SATA == FALSE) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A1 FALSE\n");
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A1 TRUE\n");
  }
  if (Usage.PHY_A2_PCIe == FALSE) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A2 FALSE\n");
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A2 TRUE\n");
  }
  if (Usage.PHY_A3_4_PCIe == FALSE) {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A3_4 FALSE\n");
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A3_4 TRUE\n");
  }

  GnbHandle = NbioGetHandle (Pcie);
  EnableDynamicControl = FALSE;
  // PHY_A0
  if ((PcdGet8 (PcdPhyA0DynamicControl) == 1) && (Usage.PHY_A0_PCIe == FALSE)) {
    // else-if (PHY_A0 PCIe is unused)
    // Program xB0[9]=1 (static turn off)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A0 Unused\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg5_ADDRESS,
                    ~(CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Static_Disable_MASK),
                    (1 << CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Static_Disable_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  } else {
    // else (PHY_A0 PCIe free running enable)
    // Program xB0[8]=0, x4C[24]=0 (default)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A0 PCIe Free Running Enabled\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg5_ADDRESS,
                    ~(CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Dynamic_EnB_MASK),
                    (0 << CGPLLCntrlReg5_CLKGEN_PHY_A0_Refclk_Dynamic_EnB_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }


  SataDrivePresent = FALSE;
  SmnRegisterRead (GnbHandle->Address.Address.Bus,
                   NBIF1_SATA_STRAP0_ADDRESS,
                   &Strap0
                   );
  if (Strap0.Field.STRAP_FUNC_EN_DEV0_F0 == 1) {
    SmnRegisterRead (GnbHandle->Address.Address.Bus,
                     SMN_SATA0_AHCI_P_SSTS_ADDRESS,
                     &PSsts.Value
                     );
    if (PSsts.Field.P_SSTS_DET == 3) {
      SataDrivePresent = TRUE;
    }
    SmnRegisterRead(GnbHandle->Address.Address.Bus,
                     SMN_SATA1_AHCI_P_SSTS_ADDRESS,
                     &PSsts.Value
                     );
    if (PSsts.Field.P_SSTS_DET == 3) {
      SataDrivePresent = TRUE;
    }
    SmnRegisterRead (GnbHandle->Address.Address.Bus,
                     SMN_SATA_AHCI_GHC_PRT_CFG_ADDRESS,
                     &GhcPrtCfg.Value
                     );
    if (GhcPrtCfg.Field.GHC_PxCMD_ESP != 0) {
      SataDrivePresent = TRUE;
    }
  }

  // PHY_A1
  if ((PcdGet8 (PcdPhyA1DynamicControl) == 1) && (Usage.PHY_A1_SATA == FALSE)) {
    if (TRUE == SataDrivePresent) {
        // PHY_A1, if the PHY is assigned to SATA, please program MISC_B0[16] & MISC_B0[24]
        IDS_HDT_CONSOLE (GNB_TRACE, "PHY A1 SATA\n");
        EnableDynamicControl = TRUE;
        SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                        SMN_CGPLLCntrlReg5_ADDRESS,
                        ~(CGPLLCntrlReg5_CLKGEN_PHY_A1_SataMac_En_MASK |
                          CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_MASK),
                        ((1 << CGPLLCntrlReg5_CLKGEN_PHY_A1_SataMac_En_OFFSET) |
                         (1 << CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_OFFSET)),
                        GNB_REG_ACC_FLAG_S3SAVE
                        );
    } else {
      // Program xB0[25]=1 (static turn off)
      IDS_HDT_CONSOLE (GNB_TRACE, "PHY A1 Unused\n");
      SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                      SMN_CGPLLCntrlReg5_ADDRESS,
                      ~(CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Static_Disable_MASK),
                      (1 << CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Static_Disable_OFFSET),
                      GNB_REG_ACC_FLAG_S3SAVE
                      );
    }
  }
  else {
    // else (PHY_A1 SATA free running enable)
    // Program xB0[24]=0, x4C[24]=0 (default)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A1 PCIe Free Running Enabled\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg5_ADDRESS,
                    ~(CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_MASK),
                    (0 << CGPLLCntrlReg5_CLKGEN_PHY_A1_Refclk_Dynamic_EnB_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }

  // PHY_A2
  if ((PcdGet8 (PcdPhyA2DynamicControl) == 1) && (Usage.PHY_A2_PCIe == FALSE)) {
    // else-if (PHY_A2 PCIe is unused)
    // Program xB4[9]=1 (static turn off)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A2 Unused\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg6_ADDRESS,
                    ~(CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Static_Disable_MASK),
                    (1 << CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Static_Disable_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }
  else {
    // else (PHY_A2 PCIe free running enable)
    // Program xB4[8]=0, x4C[24]=0 (default)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A2 PCIe Free Running Enabled\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg6_ADDRESS,
                    ~(CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Dynamic_EnB_MASK),
                    (0 << CGPLLCntrlReg6_CLKGEN_PHY_A2_Refclk_Dynamic_EnB_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }

  // PHY_A3_4
  if ((PcdGet8 (PcdPhyA34DynamicControl) == 1) && (Usage.PHY_A0_PCIe == FALSE) &&
      (Usage.PHY_A1_SATA == FALSE) && (Usage.PHY_A2_PCIe == FALSE) && (Usage.PHY_A3_4_PCIe == FALSE)) {
    // else-if (PHY_A3_4 PCIe is unused)
    // Program xB4[25]=1 (static turn off)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A3_4 Unused\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg6_ADDRESS,
                    ~(CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Static_Disable_MASK),
                    (1 << CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Static_Disable_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }
  else {
    // else (PHY_A3_4 PCIe free running enable)
    // Program xB4[24]=0, x4C[24]=0 (default)
    IDS_HDT_CONSOLE (GNB_TRACE, "PHY A3_4 PCIe Free Running Enabled\n");
    SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    SMN_CGPLLCntrlReg6_ADDRESS,
                    ~(CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Dynamic_EnB_MASK),
                    (0 << CGPLLCntrlReg6_CLKGEN_PHY_A3_4_Refclk_Dynamic_EnB_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }

  // BIOS will program x2C[24]=1 when resume if any PHY_Ax dynamic turn off control has been enabled.
  if (EnableDynamicControl == TRUE) {
    IDS_HDT_CONSOLE (GNB_TRACE, "Enable Dynamic Control\n");
    SmnRegisterRMW(GnbHandle->Address.Address.Bus,
                    SMN_MiscClkCntl4_ADDRESS,
                    ~(MiscClkCntl4_PCIe_PHY_A_Refclk_Global_Dynamic_EnB_MASK),
                    (1 << MiscClkCntl4_PCIe_PHY_A_Refclk_Global_Dynamic_EnB_OFFSET),
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
  }

  IDS_HDT_CONSOLE(GNB_TRACE, "AmdPciePhyClkCntrl Exit\n");
  return;
}




