/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe init tables.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313364 $   @e \$Date: 2015-02-21 04:31:07 +0800 (Sat, 21 Feb 2015) $
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
#include  "GnbRegistersCZ.h"

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
 *           T A B L E S
 *----------------------------------------------------------------------------------------
 */


STATIC PCIE_HOST_REGISTER_ENTRY ROMDATA CoreInitTable [] = {
  {
    D0F0xE4_CORE_0020_ADDRESS,
    D0F0xE4_CORE_0020_CiRcOrderingDis_MASK,
    (0x1 << D0F0xE4_CORE_0020_CiRcOrderingDis_OFFSET)
  },
  {
    D0F0xE4_CORE_0010_ADDRESS,
    D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_MASK,
    (0x4 << D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_OFFSET)
  },
  {
    D0F0xE4_CORE_001C_ADDRESS,
    D0F0xE4_CORE_001C_TxArbRoundRobinEn_MASK |
    D0F0xE4_CORE_001C_TxArbSlvLimit_MASK |
    D0F0xE4_CORE_001C_TxArbMstLimit_MASK,
    (0x1 << D0F0xE4_CORE_001C_TxArbRoundRobinEn_OFFSET) |
    (0x4 << D0F0xE4_CORE_001C_TxArbSlvLimit_OFFSET) |
    (0x4 << D0F0xE4_CORE_001C_TxArbMstLimit_OFFSET)
  },
  {
    D0F0xE4_CORE_001C_ADDRESS,
    D0F0xE4_CORE_001C_SlvMemLsEn_MASK |
    D0F0xE4_CORE_001C_MstMemLsEn_MASK |
    D0F0xE4_CORE_001C_ReplayMemLsEn_MASK,
    (0x1 << D0F0xE4_CORE_001C_SlvMemLsEn_OFFSET) |
    (0x1 << D0F0xE4_CORE_001C_MstMemLsEn_OFFSET) |
    (0x1 << D0F0xE4_CORE_001C_ReplayMemLsEn_OFFSET)
  },
  {
    D0F0xE4_CORE_0040_ADDRESS,
    D0F0xE4_CORE_0040_PElecIdleMode_MASK,
    (0x1 << D0F0xE4_CORE_0040_PElecIdleMode_OFFSET)
  },
  {
    D0F0xE4_CORE_0002_ADDRESS,
    D0F0xE4_CORE_0002_HwDebug_0__MASK,
    (0x1 << D0F0xE4_CORE_0002_HwDebug_0__OFFSET)
  },
  {
    D0F0xE4_CORE_00C1_ADDRESS,
    D0F0xE4_CORE_00C1_StrapLinkBwNotificationCapEn_MASK |
    D0F0xE4_CORE_00C1_StrapGen2Compliance_MASK |
    D0F0xE4_CORE_00C1_StrapGen3Compliance_MASK,
    (0x1 << D0F0xE4_CORE_00C1_StrapLinkBwNotificationCapEn_OFFSET) |
    (0x1 << D0F0xE4_CORE_00C1_StrapGen2Compliance_OFFSET) |
    (0x1 << D0F0xE4_CORE_00C1_StrapGen3Compliance_OFFSET)
  },
  {
    D0F0xE4_CORE_00B0_ADDRESS,
    D0F0xE4_CORE_00B0_StrapF0MsiEn_MASK |
    D0F0xE4_CORE_00B0_StrapF0AerEn_MASK,
    (0x1 << D0F0xE4_CORE_00B0_StrapF0MsiEn_OFFSET)
  },
  {
    D0F0xE4_CORE_00B1_ADDRESS,
    D0F0xE4_CORE_00B1_StrapF1MsiEn_MASK |
    D0F0xE4_CORE_00B1_StrapF1AerEn_MASK,
    (0x1 << D0F0xE4_CORE_00B1_StrapF1MsiEn_OFFSET) | (0x1 << D0F0xE4_CORE_00B1_StrapF1AerEn_OFFSET)
  },
  {
    D0F0xE4_CORE_00B2_ADDRESS,
    D0F0xE4_CORE_00B2_StrapF2MsiEn_MASK |
    D0F0xE4_CORE_00B2_StrapF2AerEn_MASK,
    (0x1 << D0F0xE4_CORE_00B2_StrapF2MsiEn_OFFSET) | (0x1 << D0F0xE4_CORE_00B2_StrapF2AerEn_OFFSET)
  }
};

CONST PCIE_HOST_REGISTER_TABLE_HEADER ROMDATA CoreInitTableCZ  = {
  &CoreInitTable[0],
  sizeof (CoreInitTable) / sizeof (PCIE_HOST_REGISTER_ENTRY)
};


STATIC PCIE_HOST_REGISTER_ENTRY ROMDATA PhyLaneInitEarlyTable [] = {
  {
    D0F0xE4_PHY_000A_ADDRESS,
    D0F0xE4_PHY_000A_adapt_cfg_mode_MASK,
    (0x163ul << D0F0xE4_PHY_000A_adapt_cfg_mode_OFFSET)
  }
};

CONST PCIE_HOST_REGISTER_TABLE_HEADER ROMDATA PhyLaneInitEarlyTableCZ  = {
  &PhyLaneInitEarlyTable[0],
  sizeof (PhyLaneInitEarlyTable) / sizeof (PCIE_HOST_REGISTER_ENTRY)
};


STATIC PCIE_HOST_REGISTER_ENTRY ROMDATA PhyWrapperInitEarlyTable [] = {
  {
    D0F0xE4_PHY_620A_ADDRESS,
    D0F0xE4_PHY_620A_adapt_cfg_fom_ber_MASK |
    D0F0xE4_PHY_620A_adapt_cfg_oc_time_MASK |
    D0F0xE4_PHY_620A_adapt_cfg_cdr_time_MASK |
    D0F0xE4_PHY_620A_adapt_cfg_leq_time_MASK |
    D0F0xE4_PHY_620A_adapt_cfg_dfe_time_MASK |
    D0F0xE4_PHY_620A_adapt_cfg_fom_time_MASK,
    (0x3ul << D0F0xE4_PHY_620A_adapt_cfg_fom_ber_OFFSET) |
    (0xcul << D0F0xE4_PHY_620A_adapt_cfg_oc_time_OFFSET) |
    (0x3ul << D0F0xE4_PHY_620A_adapt_cfg_cdr_time_OFFSET) |
    (0x7ul << D0F0xE4_PHY_620A_adapt_cfg_leq_time_OFFSET) |
    (0x9ul << D0F0xE4_PHY_620A_adapt_cfg_dfe_time_OFFSET) |
    (0xcul << D0F0xE4_PHY_620A_adapt_cfg_fom_time_OFFSET)
  },
  {
    D0F0xE4_PHY_620B_ADDRESS,
    D0F0xE4_PHY_620B_adapt_cfg_leq_loop_gain_MASK |
    D0F0xE4_PHY_620B_adapt_cfg_ofc_loop_gain_MASK |
    D0F0xE4_PHY_620B_adapt_cfg_fom_loop_gain_MASK |
    D0F0xE4_PHY_620B_adapt_cfg_dfe_ref_loop_gain_MASK |
    D0F0xE4_PHY_620B_adapt_cfg_dfe_tap_loop_gain_MASK |
    D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_rt_MASK |
    D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_lt_MASK,
    (0x3ul << D0F0xE4_PHY_620B_adapt_cfg_leq_loop_gain_OFFSET) |
    (0xcul << D0F0xE4_PHY_620B_adapt_cfg_ofc_loop_gain_OFFSET) |
    (0xcul << D0F0xE4_PHY_620B_adapt_cfg_fom_loop_gain_OFFSET) |
    (0xcul << D0F0xE4_PHY_620B_adapt_cfg_dfe_ref_loop_gain_OFFSET) |
    (0xcul << D0F0xE4_PHY_620B_adapt_cfg_dfe_tap_loop_gain_OFFSET) |
    (0x4ul << D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_rt_OFFSET) |
    (0x4ul << D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_lt_OFFSET)
  }
};

CONST PCIE_HOST_REGISTER_TABLE_HEADER ROMDATA PhyWrapperInitEarlyTableCZ  = {
  &PhyWrapperInitEarlyTable[0],
  sizeof (PhyWrapperInitEarlyTable) / sizeof (PCIE_HOST_REGISTER_ENTRY)
};

STATIC PCIE_PORT_REGISTER_ENTRY ROMDATA PortInitEarlyTable [] = {
  {
    DxFxxE4_x70_ADDRESS,
    DxFxxE4_x70_RxRcbCplTimeoutMode_MASK,
    (0x1 << DxFxxE4_x70_RxRcbCplTimeoutMode_OFFSET)
  },
  {
    DxFxxE4_xA0_ADDRESS,
    DxFxxE4_xA0_Lc16xClearTxPipe_MASK | DxFxxE4_xA0_LcL1ImmediateAck_MASK | DxFxxE4_xA0_LcL0sInactivity_MASK,
    (0x3 << DxFxxE4_xA0_Lc16xClearTxPipe_OFFSET) |
    (0x1 << DxFxxE4_xA0_LcL1ImmediateAck_OFFSET) |
    (0x6 << DxFxxE4_xA0_LcL0sInactivity_OFFSET)
  },
  {
    DxFxxE4_xA1_ADDRESS,
    DxFxxE4_xA1_LcDontGotoL0sifL1Armed_MASK,
    (0x1 << DxFxxE4_xA1_LcDontGotoL0sifL1Armed_OFFSET)
  },
  {
    DxFxxE4_xA2_ADDRESS,
    DxFxxE4_xA2_LcRenegotiateEn_MASK |
    DxFxxE4_xA2_LcUpconfigureSupport_MASK |
    DxFxxE4_xA2_LcDynLanesPwrState_MASK,
    (0x1 << DxFxxE4_xA2_LcRenegotiateEn_OFFSET) |
    (0x1 << DxFxxE4_xA2_LcUpconfigureSupport_OFFSET) |
    (0x3 << DxFxxE4_xA2_LcDynLanesPwrState_OFFSET)
  },
  {
    DxFxxE4_xA3_ADDRESS,
    DxFxxE4_xA3_LcXmitNFts_MASK,
    (0x36 << DxFxxE4_xA3_LcXmitNFts_OFFSET)
  },
  {
    DxFxxE4_xA3_ADDRESS,
    DxFxxE4_xA3_LcXmitNFtsOverrideEn_MASK,
    (0x1 << DxFxxE4_xA3_LcXmitNFtsOverrideEn_OFFSET)
  },
  {
    DxFxxE4_xB5_ADDRESS,
    DxFxxE4_xB5_LcGoToRecovery_MASK,
    0x1 << DxFxxE4_xB5_LcGoToRecovery_OFFSET
  },
  {
    DxFxxE4_xB1_ADDRESS,
    DxFxxE4_xB1_LcDeassertRxEnInL0s_MASK | DxFxxE4_xB1_LcBlockElIdleinL0_MASK | DxFxxE4_xB1_LcElecIdleMode_MASK,
    (0x1 << DxFxxE4_xB1_LcDeassertRxEnInL0s_OFFSET) |
    (0x1 << DxFxxE4_xB1_LcBlockElIdleinL0_OFFSET) |
    (0x1 << DxFxxE4_xB1_LcElecIdleMode_OFFSET)
  },
  {
    DxFxxE4_xB6_ADDRESS,
    DxFxxE4_xB6_LcEqSearchMode_MASK,
    (0x1 << DxFxxE4_xB6_LcEqSearchMode_OFFSET)
  },
  {
    DxFxxE4_xC0_ADDRESS,
    DxFxxE4_xC0_StrapLaneNegotiation_MASK,
    (0x1 << DxFxxE4_xC0_StrapLaneNegotiation_OFFSET)
  },
  {
    DxFxxE4_xDA_ADDRESS,
    DxFxxE4_xDA_RegHpgiPresenceDetectStateChangeEn_MASK,
    (0x1 << DxFxxE4_xDA_RegHpgiPresenceDetectStateChangeEn_OFFSET)
  }
};

CONST PCIE_PORT_REGISTER_TABLE_HEADER ROMDATA PortInitEarlyTableCZ  = {
  &PortInitEarlyTable[0],
  sizeof (PortInitEarlyTable) / sizeof (PCIE_PORT_REGISTER_ENTRY)
};


STATIC PCIE_PORT_REGISTER_ENTRY ROMDATA PortInitMidTable [] = {
  {
    DxFxxE4_xC0_ADDRESS,
    DxFxxE4_xC0_StrapAutoRcSpeedNegotiationDis_MASK,
    (0x1 << DxFxxE4_xC0_StrapAutoRcSpeedNegotiationDis_OFFSET)
  }
};

CONST PCIE_PORT_REGISTER_TABLE_HEADER ROMDATA PortInitMidTableCZ  = {
  &PortInitMidTable[0],
  sizeof (PortInitMidTable) / sizeof (PCIE_PORT_REGISTER_ENTRY)
};

