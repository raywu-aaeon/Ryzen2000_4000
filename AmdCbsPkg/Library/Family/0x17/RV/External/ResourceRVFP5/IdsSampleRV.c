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
 **/


//This file is auto generated, don't edit it manually

//RedirectForReturnDis
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_GEN_W_A05, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdRedirectForReturnDis)) {
  case IDSOPT_CMN_CPU_GEN_W_A05_AUTO:
    break;
  case IDSOPT_CMN_CPU_GEN_W_A05_1:
    break;
  case IDSOPT_CMN_CPU_GEN_W_A05_0:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//L2 TLB Associativity
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_L2_TLB_WAY_ALLOC, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC_0:
    break;
  case IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC_1:
    break;
  case IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Platform First Error Handling
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_PFEH, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_CPU_PFEH_ENABLE:
    break;
  case IDSOPT_CMN_CPU_PFEH_DISABLE:
    break;
  case IDSOPT_CMN_CPU_PFEH_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Core Performance Boost
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_CPB, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdCpbMode)) {
  case IDSOPT_CMN_CPU_CPB_DISABLED:
    break;
  case IDSOPT_CMN_CPU_CPB_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Global C-state Control
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_GLOBAL_CSTATE_CTRL, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdCStateMode)) {
  case IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL_DISABLED:
    break;
  case IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL_ENABLED:
    break;
  case IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//OC Mode
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_OC_MODE, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_CPU_OC_MODE_NORMALOPERATION:
    break;
  case IDSOPT_CMN_CPU_OC_MODE_OC1:
    break;
  case IDSOPT_CMN_CPU_OC_MODE_CUSTOMIZED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Streaming Stores Control
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_STREAMING_STORES_CTRL, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdStreamingStoresCtrl)) {
  case IDSOPT_CMN_CPU_STREAMING_STORES_CTRL_DISABLED:
    break;
  case IDSOPT_CMN_CPU_STREAMING_STORES_CTRL_ENABLED:
    break;
  case IDSOPT_CMN_CPU_STREAMING_STORES_CTRL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Enable IBS
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_EN_IBS, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_CPU_EN_IBS_DISABLED:
    break;
  case IDSOPT_CMN_CPU_EN_IBS_ENABLED:
    break;
  case IDSOPT_CMN_CPU_EN_IBS_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Custom Pstate0
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdCcxP0Setting)) {
  case IDSOPT_CPU_PST_CUSTOM_P0_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P0, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P0_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P0_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P0, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P0_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P0_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST0_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST0_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST0_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST0_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST0_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST0_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST0_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST0_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST0_VID_MIN);
}

//Custom Pstate1
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P1_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P1_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P1, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P1_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P1_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P1, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P1_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P1_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST1_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST1_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST1_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST1_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST1_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST1_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST1_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST1_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST1_VID_MIN);
}

//Custom Pstate2
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P2, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P2_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P2_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P2_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P2, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P2_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P2_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P2, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P2_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P2_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST2_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST2_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST2_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST2_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST2_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST2_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST2_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST2_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST2_VID_MIN);
}

//Custom Pstate3
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P3, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P3_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P3_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P3_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P3, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P3_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P3_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P3, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P3_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P3_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST3_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST3_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST3_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST3_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST3_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST3_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST3_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST3_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST3_VID_MIN);
}

//Custom Pstate4
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P4_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P4_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P4_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P4_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST4_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST4_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST4_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST4_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST4_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST4_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST4_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST4_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST4_VID_MIN);
}

//Custom Pstate5
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P5, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P5_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P5_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P5_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P5, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P5_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P5_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P5, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P5_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P5_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST5_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST5_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST5_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST5_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST5_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST5_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST5_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST5_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST5_VID_MIN);
}

//Custom Pstate6
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P6, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P6_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P6_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P6_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P6, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P6_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P6_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P6, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P6_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P6_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST6_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST6_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST6_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST6_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST6_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST6_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST6_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST6_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST6_VID_MIN);
}

//Custom Pstate7
IDS_NV_READ_SKIP (IDSNVID_CPU_PST_CUSTOM_P7, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_PST_CUSTOM_P7_DISABLED:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P7_CUSTOM:
    break;
  case IDSOPT_CPU_PST_CUSTOM_P7_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CPU_COF_P7, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_COF_P7_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_COF_P7_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_VOLTAGE_P7, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_VOLTAGE_P7_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_VOLTAGE_P7_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST7_FID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST7_FID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST7_FID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST7_DID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST7_DID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST7_DID_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CPU_PST7_VID, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CPU_PST7_VID_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CPU_PST7_VID_MIN);
}

//Relaxed EDC throttling
IDS_NV_READ_SKIP (IDSNVID_CPU_RELAXED_EDC_THROTTLING, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CPU_RELAXED_EDC_THROTTLING_DISABLED:
    break;
  case IDSOPT_CPU_RELAXED_EDC_THROTTLING_ENABLED:
    break;
  case IDSOPT_CPU_RELAXED_EDC_THROTTLING_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Downcore control
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_GEN_DOWNCORE_CTRL, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdDownCoreMode)) {
  case IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_ONE:
    break;
  case IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_TWO:
    break;
  case IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_THREE:
    break;
  case IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//SMTEN
IDS_NV_READ_SKIP (IDSNVID_CMN_CPU_GEN_SMT_EN, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdSmtMode)) {
  case IDSOPT_CMN_CPU_GEN_SMT_EN_DISABLE:
    break;
  case IDSOPT_CMN_CPU_GEN_SMT_EN_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//DRAM scrub time
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_DRAM_SCRUB_TIME, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdFabricDramScrubTime)) {
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_DISABLED:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_1HOUR:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_4HOURS:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_8HOURS:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_16HOURS:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_24HOURS:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_48HOURS:
    break;
  case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Redirect scrubber control
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_REDIR_SCRUB_CTRL, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_DISABLED:
    break;
  case IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_ENABLED:
    break;
  case IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Disable DF sync flood propagation
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_SYNC_FLOOD_PROP, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_SYNC_FLOOD_PROP_SYNCFLOODDISABLED:
    break;
  case IDSOPT_DF_CMN_SYNC_FLOOD_PROP_SYNCFLOODENABLED:
    break;
  case IDSOPT_DF_CMN_SYNC_FLOOD_PROP_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//GMI encryption control
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_GMI_ENCRYPTION, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_GMI_ENCRYPTION_DISABLED:
    break;
  case IDSOPT_DF_CMN_GMI_ENCRYPTION_ENABLED:
    break;
  case IDSOPT_DF_CMN_GMI_ENCRYPTION_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//xGMI encryption control
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_X_GMI_ENCRYPTION, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_X_GMI_ENCRYPTION_DISABLED:
    break;
  case IDSOPT_DF_CMN_X_GMI_ENCRYPTION_ENABLED:
    break;
  case IDSOPT_DF_CMN_X_GMI_ENCRYPTION_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//CC6 memory region encryption
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_CC6_MEM_ENCRYPTION, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION_DISABLED:
    break;
  case IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION_ENABLED:
    break;
  case IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Location of private memory regions
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_CC6_ALLOCATION_SCHEME, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME_DISTRIBUTED:
    break;
  case IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME_CONSOLIDATED:
    break;
  case IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//System probe filter
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_SYS_PROBE_FILTER, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_SYS_PROBE_FILTER_DISABLED:
    break;
  case IDSOPT_DF_CMN_SYS_PROBE_FILTER_ENABLED:
    break;
  case IDSOPT_DF_CMN_SYS_PROBE_FILTER_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Memory interleaving
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_MEM_INTLV, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_MEM_INTLV_NONE:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_CHANNEL:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_DIE:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_SOCKET:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Memory interleaving size
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_MEM_INTLV_SIZE, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_MEM_INTLV_SIZE_256BYTES:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_SIZE_512BYTES:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_SIZE_1KB:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_SIZE_2KB:
    break;
  case IDSOPT_DF_CMN_MEM_INTLV_SIZE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Channel interleaving hash
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_CHNL_INTLV_HASH, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_CHNL_INTLV_HASH_DISABLED:
    break;
  case IDSOPT_DF_CMN_CHNL_INTLV_HASH_ENABLED:
    break;
  case IDSOPT_DF_CMN_CHNL_INTLV_HASH_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//DF C-state control
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_CSTATE_CTRL, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_CSTATE_CTRL_DISABLED:
    break;
  case IDSOPT_DF_CMN_CSTATE_CTRL_ENABLED:
    break;
  case IDSOPT_DF_CMN_CSTATE_CTRL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//xGMI DLWM control
IDS_NV_READ_SKIP (IDSNVID_DF_CMNX_GMI_DLWM_CTRL, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMNX_GMI_DLWM_CTRL_DISABLED:
    break;
  case IDSOPT_DF_CMNX_GMI_DLWM_CTRL_ENABLED:
    break;
  case IDSOPT_DF_CMNX_GMI_DLWM_CTRL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Freeze DF module queues on error
IDS_NV_READ_SKIP (IDSNVID_DF_CMN_FREEZE_QUEUE_ERROR, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_DISABLED:
    break;
  case IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_ENABLED:
    break;
  case IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Overclock
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_OVERCLOCK_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_OVERCLOCK_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_OVERCLOCK_DDR4_ENABLED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Memory Clock Speed
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_SPEED_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_SPEED_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_667MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_800MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_933MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1067MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1200MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1333MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1367MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1400MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1433MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1467MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1500MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1533MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1567MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1600MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1633MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1667MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1700MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1733MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1767MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1800MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1833MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1867MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1900MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1933MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1967MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_2000MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_333MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_400MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_533MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1050MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_1066MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_2033MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_2067MHZ:
    break;
  case IDSOPT_CMN_MEM_SPEED_DDR4_2100MHZ:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Tcl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TCL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_11HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_13HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_14HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_20HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCL_DDR4_21HCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Trcdrd
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRCDRD_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_14HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_11HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_13HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_1BHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Trcdwr
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRCDWR_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XACLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XBCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XCCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XDCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XECLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XFCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_11HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_13HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_14HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_1BHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Trp
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRP_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_11HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_13HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_14HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRP_DDR4_1BHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Tras
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRAS_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_20HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_21HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_22HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_23HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_24HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_25HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_26HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_27HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_28HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_29HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_30HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_31HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_32HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_33HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_34HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_35HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_36HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_37HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_38HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_39HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_3AHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Trc Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRC_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRC_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRC_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRC_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TRC_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TRC_DDR4_MIN);
}

//TrrdS
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRRD_S_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_0CHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TrrdL
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRRD_L_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_0CHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Tfaw Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TFAW_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TFAW_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TFAW_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TFAW_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TFAW_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TFAW_DDR4_MIN);
}

//TwtrS
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWTR_S_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0EHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TwtrL
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWTR_L_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0EHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Twr Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWR_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWR_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWR_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWR_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TWR_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TWR_DDR4_MIN);
}

//Trcpage Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRCPAGE_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TRCPAGE_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TRCPAGE_DDR4_MIN);
}

//TrdrdScL Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRDRD_SC_L_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_DDR4_MIN);
}

//TwrwrScL Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWRWR_SC_L_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_DDR4_MIN);
}

//Trfc Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRFC_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRFC_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRFC_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRFC_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TRFC_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TRFC_DDR4_MIN);
}

//Trfc2 Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRFC2_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRFC2_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRFC2_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRFC2_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TRFC2_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TRFC2_DDR4_MIN);
}

//Trfc4 Ctrl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRFC4_CTRL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRFC4_CTRL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRFC4_CTRL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRFC4_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_TIMING_TRFC4_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_TIMING_TRFC4_DDR4_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_OVERCLOCK_FAIL_CNT, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_OVERCLOCK_FAIL_CNT_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_OVERCLOCK_FAIL_CNT_MIN);
}

//ProcODT
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_PROC_ODT_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_HIGHIMPEDANCE:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_480OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_240OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_160OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_120OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_96OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_80OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_686OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_60OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_533OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_48OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_436OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_40OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_369OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_343OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_32OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_30OHM:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_282OHM:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Tcwl
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TCWL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_14HCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Trtp
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRTP_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0EHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Tcke
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TCKE_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_11HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_13HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_14HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TrdrdSc
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRDRD_SC_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TrdrdSd
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRDRD_SD_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TrdrdDd
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRDRD_DD_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TwrwrSc
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWRWR_SC_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TwrwrSd
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWRWR_SD_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TwrwrDd
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWRWR_DD_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Trdwr
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TRDWR_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0FHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_10HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_11HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_12HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_13HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_14HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_15HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_16HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_17HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_18HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_19HCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1CHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1DHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1EHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1FHCLK:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Twrrd
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TIMING_TWRRD_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_1CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_2CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_3CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_4CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_5CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_6CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_7CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_8CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_9CLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0AHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0BHCLK:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0CH:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0DH:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0EH:
    break;
  case IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0FH:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Cmd2T
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER2_T_MODE_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4_1T:
    break;
  case IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4_2T:
    break;
  case IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Gear Down Mode
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_GEAR_DOWN_MODE_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Data Mask
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_DATA_MASK_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_DATA_MASK_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_DATA_MASK_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_DATA_MASK_DDR4_DISABLED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Power Down Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//CAD Bus Timing User Controls
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_ADDR_CMD_SETUP_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_ADDR_CMD_SETUP_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_ADDR_CMD_SETUP_DDR4_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CS_ODT_SETUP_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_CS_ODT_SETUP_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_CS_ODT_SETUP_DDR4_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CKE_SETUP_DDR4, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_CMN_MEM_CKE_SETUP_DDR4_MAX);
  ASSERT (IdsNvValue >= IDSOPT_CMN_MEM_CKE_SETUP_DDR4_MIN);
}

//CAD Bus Drive Strength User Controls
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//ClkDrvStren
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_1200OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_600OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_400OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_300OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_240OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_200OHM:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//AddrCmdDrvStren
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_1200OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_600OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_400OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_300OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_240OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_200OHM:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//CsOdtDrvStren
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_1200OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_600OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_400OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_300OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_240OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_200OHM:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//CkeDrvStren
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_1200OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_600OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_400OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_300OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_240OHM:
    break;
  case IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_200OHM:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Data Bus Configuration User Controls
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4_MANUAL:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//RttNom
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_RTT_NOM_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RTT_NOMDISABLE:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ4:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ2:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ6:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ1:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ5:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ3:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ7:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//RttWr
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_RTT_WR_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_DYNAMICODTOFF:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_RZQ2:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_RZQ1:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_HIZ:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_RZQ3:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//RttPark
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_RTT_PARK_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RTT_PARKDISABLE:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ4:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ2:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ6:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ1:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ5:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ3:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ7:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Data Poisoning
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_DATA_POISONING_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_DATA_POISONING_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_DATA_POISONING_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_DATA_POISONING_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//DRAM ECC Symbol Size
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4_X4:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4_X8:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//DRAM ECC Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//TSME
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_TSME_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_TSME_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_TSME_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_TSME_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Chipselect Interleaving
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//BankGroupSwap
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_APU:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_CPU:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//BankGroupSwapAlt
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Address Hash Bank
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_ADDRESS_HASH_BANK_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4_DISABLED:
    break;
  case IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Address Hash CS
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_ADDRESS_HASH_CS_DDR4, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4_AUTO:
    break;
  case IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4_ENABLED:
    break;
  case IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4_DISABLED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//MBIST Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_MBIST_EN, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_MBIST_EN_AUTO:
    break;
  case IDSOPT_CMN_MEM_MBIST_EN_DISABLED:
    break;
  case IDSOPT_CMN_MEM_MBIST_EN_ENABLED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//MBIST Test Mode
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_MBIST_SUB_TEST, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_MBIST_SUB_TEST_AUTO:
    break;
  case IDSOPT_CMN_MEM_MBIST_SUB_TEST_INTERFACEMODE:
    break;
  case IDSOPT_CMN_MEM_MBIST_SUB_TEST_DATAEYEMODE:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//MBIST Aggressors
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_MBIST_AGGRESSORS, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_MBIST_AGGRESSORS_AUTO:
    break;
  case IDSOPT_CMN_MEM_MBIST_AGGRESSORS_DISABLED:
    break;
  case IDSOPT_CMN_MEM_MBIST_AGGRESSORS_ENABLED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//MBIST Per Bit Slave Die Reporting
IDS_NV_READ_SKIP (IDSNVID_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING_AUTO:
    break;
  case IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING_DISABLED:
    break;
  case IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING_ENABLED:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//System Configuration
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_SMU_SYSTEM_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_12WPORCONFIGURATION1COMMERCIALCONSUMER:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_15WPORCONFIGURATION2COMMERCIALCONSUMER:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_25WPORCONFIGURATION3COMMERCIALCONSUMER:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_35WPORCONFIGURATION4CONSUMER:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_45WPORCONFIGURATION5CONSUMER:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_54WPORCONFIGURATION6CONSUMER:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_35WPORCONFIGURATION7EMBEDDED:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_45WPORCONFIGURATION8EMBEDDED:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_54WPORCONFIGURATION9EMBEDDED:
    break;
  case IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Audio IOs
IDS_NV_READ_SKIP (IDSNVID_DBG_GNB_AUDIO_I_OS, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdAmdNbioAudioSelect)) {
  case IDSOPT_DBG_GNB_AUDIO_I_OS_AUTO:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_MAXHDAMINSOUNDWIRE:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_MAXMHDAMINSOUNDWIRE:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_MAXSOUNDWIREMINHDA:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_MAXSOUNDWIREMINMHDA:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_I2STDM:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_DISABLEAUDIOIOS:
    break;
  case IDSOPT_DBG_GNB_AUDIO_I_OS_SOUNDWIRE:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//System Temperature Tracking
IDS_NV_READ_SKIP (IDSNVID_CMN_SYSTEM_TEMPERATURE_TRACKING, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_AUTO:
    break;
  case IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_DISABLE:
    break;
  case IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_ENABLE:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Integrated Graphics Controller
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFXI_GPU_CONTROL, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdCfgIgpuContorl)) {
  case IDSOPT_CMN_GNB_GFXI_GPU_CONTROL_DISABLED:
    break;
  case IDSOPT_CMN_GNB_GFXI_GPU_CONTROL_FORCES:
    break;
  case IDSOPT_CMN_GNB_GFXI_GPU_CONTROL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//UMA Mode
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_UMA_MODE, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_GNB_GFX_UMA_MODE_AUTO:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_MODE_UMA_SPECIFIED:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_MODE_UMA_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//UMA Version
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_UMA_VERSION, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_GNB_GFX_UMA_VERSION_LEGACY:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_VERSION_NONLEGACY:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_VERSION_HYBRIDSECURE:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_VERSION_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Display Resulotuon
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_DISPLAY_RESOLUTION, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_1920X1080ANDBELOW:
    break;
  case IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_2560X1600:
    break;
  case IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_3840X2160:
    break;
  case IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//UMA Frame buffer Size
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_AUTO:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_64M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_128M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_256M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_384M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_512M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_80M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_96M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_768M:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_1G:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_2G:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_3G:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_4G:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_8G:
    break;
  case IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_16G:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//NB Azalia
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_GFX_NB_AZALIA, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdCfgAzaliaEnable)) {
  case IDSOPT_CMN_GNB_GFX_NB_AZALIA_DISABLED:
    break;
  case IDSOPT_CMN_GNB_GFX_NB_AZALIA_ENABLED:
    break;
  case IDSOPT_CMN_GNB_GFX_NB_AZALIA_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//IOMMU
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_NB_IOMMU, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdCfgIommuSupport)) {
  case IDSOPT_CMN_GNB_NB_IOMMU_DISABLED:
    break;
  case IDSOPT_CMN_GNB_NB_IOMMU_ENABLED:
    break;
  case IDSOPT_CMN_GNB_NB_IOMMU_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PSPP Policy
IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_PCIE_PSPP_POLICY, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPsppPolicy)) {
  case IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_DISABLED:
    break;
  case IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_PERFORMANCE:
    break;
  case IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_BALANCED:
    break;
  case IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_POWERSAVING:
    break;
  case IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Fan Control
IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_CTL, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DBG_FAN_CTL_MANUAL:
    break;
  case IDSOPT_DBG_FAN_CTL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Force PWM Control
IDS_NV_READ_SKIP (IDSNVID_DBG_FORCE_PWM_CTL, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DBG_FORCE_PWM_CTL_FORCE:
    break;
  case IDSOPT_DBG_FORCE_PWM_CTL_UNFORCE:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FORCE_PWM, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FORCE_PWM_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FORCE_PWM_MIN);
}

//Fan Table Control
IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_CTL, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DBG_FAN_TABLE_CTL_MANUAL:
    break;
  case IDSOPT_DBG_FAN_TABLE_CTL_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_LOW, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_TEMP_LOW_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_TEMP_LOW_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_MED, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_TEMP_MED_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_TEMP_MED_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_HIGH, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_TEMP_HIGH_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_TEMP_HIGH_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_TEMP_CRITICAL, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_TEMP_CRITICAL_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_TEMP_CRITICAL_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_T_PWM_LOW, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_T_PWM_LOW_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_T_PWM_LOW_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_PWM_MED, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_PWM_MED_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_PWM_MED_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_PWM_HIGH, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_PWM_HIGH_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_PWM_HIGH_MIN);
}

IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_HYST, &IdsNvValue) {
  ASSERT (IdsNvValue <= IDSOPT_DBG_FAN_TABLE_HYST_MAX);
  ASSERT (IdsNvValue >= IDSOPT_DBG_FAN_TABLE_HYST_MIN);
}

//Pwm Frequency
IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_TABLE_PWM_FREQ, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DBG_FAN_TABLE_PWM_FREQ_100HZ:
    break;
  case IDSOPT_DBG_FAN_TABLE_PWM_FREQ_25KHZ:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Fan Polarity
IDS_NV_READ_SKIP (IDSNVID_DBG_FAN_POLARITY, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_DBG_FAN_POLARITY_NEGATIVE:
    break;
  case IDSOPT_DBG_FAN_POLARITY_POSITIVE:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//SATA Controller
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_SATA_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdSataEnable)) {
  case IDSOPT_CMN_FCH_SATA_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_FCH_SATA_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_FCH_SATA_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//SATA Mode
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_SATA_CLASS, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdSataClass)) {
  case IDSOPT_CMN_FCH_SATA_CLASS_AHCI:
    break;
  case IDSOPT_CMN_FCH_SATA_CLASS_AHCIASID0X7904:
    break;
  case IDSOPT_CMN_FCH_SATA_CLASS_AUTO:
    break;
  case IDSOPT_CMN_FCH_SATA_CLASS_RAID:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Sata RAS Support
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_SATA_RAS_SUPPORT, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdSataRasSupport)) {
  case IDSOPT_CMN_FCH_SATA_RAS_SUPPORT_DISABLED:
    break;
  case IDSOPT_CMN_FCH_SATA_RAS_SUPPORT_ENABLED:
    break;
  case IDSOPT_CMN_FCH_SATA_RAS_SUPPORT_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Sata Disabled AHCI Prefetch Function
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdSataAhciDisPrefetchFunction)) {
  case IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION_DISABLED:
    break;
  case IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION_ENABLED:
    break;
  case IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Aggresive SATA Device Sleep Port 0
IDS_NV_READ_SKIP (IDSNVID_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdSataDevSlpPort0)) {
  case IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0_DISABLE:
    break;
  case IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0_ENABLE:
    break;
  case IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Aggresive SATA Device Sleep Port 1
IDS_NV_READ_SKIP (IDSNVID_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdSataDevSlpPort1)) {
  case IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1_DISABLE:
    break;
  case IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1_ENABLE:
    break;
  case IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//XHCI0 controller enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_USB_XHC_I0_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdXhci0Enable)) {
  case IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//XHCI1 controller enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_USB_XHC_I1_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdXhci1Enable)) {
  case IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Ac Loss Control
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPwrFailShadow)) {
  case IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_ALWAYSOFF:
    break;
  case IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_ALWAYSON:
    break;
  case IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_RESERVED:
    break;
  case IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_PREVIOUS:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//I2C 0 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_I2_C0_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_I2_C0_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C0_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C0_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//I2C 1 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_I2_C1_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_I2_C1_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C1_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C1_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//I2C 2 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_I2_C2_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_I2_C2_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C2_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C2_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//I2C 3 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_I2_C3_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_I2_C3_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C3_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C3_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//I2C 4 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_I2_C4_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_I2_C4_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C4_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C4_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//I2C 5 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_I2_C5_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_I2_C5_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C5_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_I2_C5_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 0 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART0_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_UART0_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART0_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_UART0_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 0 Legacy Options
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART0_LEGACY_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (FchUart0LegacyEnable)) {
  case IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X2E8:
    break;
  case IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X2F8:
    break;
  case IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X3E8:
    break;
  case IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X3F8:
    break;
  case IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 1 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART1_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_UART1_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART1_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_UART1_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 1 Legacy Options
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART1_LEGACY_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (FchUart1LegacyEnable)) {
  case IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X2E8:
    break;
  case IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X2F8:
    break;
  case IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X3E8:
    break;
  case IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X3F8:
    break;
  case IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 2 Enable (no HW FC)
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART2_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_UART2_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART2_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_UART2_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 2 Legacy Options
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART2_LEGACY_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (FchUart2LegacyEnable)) {
  case IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X2E8:
    break;
  case IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X2F8:
    break;
  case IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X3E8:
    break;
  case IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X3F8:
    break;
  case IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 3 Enable (no HW FC)
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART3_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  case IDSOPT_CMN_FCH_UART3_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART3_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_UART3_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Uart 3 Legacy Options
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_UART3_LEGACY_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (FchUart3LegacyEnable)) {
  case IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X2E8:
    break;
  case IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X2F8:
    break;
  case IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X3E8:
    break;
  case IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X3F8:
    break;
  case IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//ESPI Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_ESPI_CONFIG, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdEspiEnable)) {
  case IDSOPT_CMN_FCH_ESPI_CONFIG_DISABLED:
    break;
  case IDSOPT_CMN_FCH_ESPI_CONFIG_ENABLED:
    break;
  case IDSOPT_CMN_FCH_ESPI_CONFIG_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//XGBE0 enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_XGBE0_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdXgbePort0ConfigEn)) {
  case IDSOPT_CMN_FCH_XGBE0_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_FCH_XGBE0_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_FCH_XGBE0_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//XGBE1 enable
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_XGBE1_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdXgbePort1ConfigEn)) {
  case IDSOPT_CMN_FCH_XGBE1_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_FCH_XGBE1_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_FCH_XGBE1_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//eMMC/SD Configure
IDS_NV_READ_SKIP (IDSNVID_DBG_FCH_EMMC_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdEmmcEnable)) {
  case IDSOPT_DBG_FCH_EMMC_ENABLE_DISABLED:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_SDNORMALSPEED:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_SDHIGHSPEED:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_SDUHSISDR50:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_SDUHSIDDR50:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_SDUHSISDR104:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCEMMCBACKWARDCOMPATIBILITY:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHIGHSPEEDSDR:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHIGHSPEEDDDR:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHS200:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHS400:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHS300:
    break;
  case IDSOPT_DBG_FCH_EMMC_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Driver Type
IDS_NV_READ_SKIP (IDSNVID_DBG_FCH_EMMC_DRIVER_TYPE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdEmmcDriverType)) {
  case IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_AMDEMMCDRIVER:
    break;
  case IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_MSDRIVER:
    break;
  case IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_MSEMMCDRIVER:
    break;
  case IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//D3 Cold Support
IDS_NV_READ_SKIP (IDSNVID_DBG_FCH_EMMC_D3_SUPPORT, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdEmmcD3Support)) {
  case IDSOPT_DBG_FCH_EMMC_D3_SUPPORT_DISABLED:
    break;
  case IDSOPT_DBG_FCH_EMMC_D3_SUPPORT_ENABLED:
    break;
  case IDSOPT_DBG_FCH_EMMC_D3_SUPPORT_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//eMMC Boot
IDS_NV_READ_SKIP (IDSNVID_DBG_FCH_EMMC_BOOT, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdEmmcBoot)) {
  case IDSOPT_DBG_FCH_EMMC_BOOT_DISABLED:
    break;
  case IDSOPT_DBG_FCH_EMMC_BOOT_ENABLED:
    break;
  case IDSOPT_DBG_FCH_EMMC_BOOT_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//LPC Clock Run control
IDS_NV_READ_SKIP (IDSNVID_CMN_FCH_LPC_CLOCK_RUN_EN, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdLpcClkRunEn)) {
  case IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN_DISABLED:
    break;
  case IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN_ENABLED:
    break;
  case IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//Toggle All PwrGood On Cf9
IDS_NV_READ_SKIP (IDSNVID_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGetBool (PcdToggleAllPwrGoodOnCf9)) {
  case IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9_DISABLED:
    break;
  case IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9_ENABLED:
    break;
  case IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Mode
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_CLASS, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataMode)) {
  case IDSOPT_CMN_PT_SATA_CLASS_AHCI:
    break;
  case IDSOPT_CMN_PT_SATA_CLASS_RAID:
    break;
  case IDSOPT_CMN_PT_SATA_CLASS_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT Aggresive SATA Device Sleep Port 0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataAggresiveDevSlpP0)) {
  case IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT Aggresive SATA Device Sleep Port 1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataAggresiveDevSlpP1)) {
  case IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 0 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT0_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort0Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT0_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT0_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT0_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 1 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT1_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort1Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT1_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT1_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT1_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 2 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT2_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort2Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT2_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT2_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT2_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 3 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT3_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort3Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT3_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT3_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT3_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 4 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT4_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort4Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT4_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT4_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT4_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 5 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT5_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort5Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT5_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT5_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT5_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 6 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT6_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort6Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT6_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT6_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT6_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT SATA Port 7 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_SATA_PORT7_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTSataPort7Enable)) {
  case IDSOPT_CMN_PT_SATA_PORT7_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT7_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_SATA_PORT7_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT XHCI GEN1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_XHCI_GEN1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTXhciGen1)) {
  case IDSOPT_DBG_PT_XHCI_GEN1_DISABLE:
    break;
  case IDSOPT_DBG_PT_XHCI_GEN1_ENABLE:
    break;
  case IDSOPT_DBG_PT_XHCI_GEN1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT XHCI GEN2
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_XHCI_GEN2, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTXhciGen2)) {
  case IDSOPT_DBG_PT_XHCI_GEN2_DISABLE:
    break;
  case IDSOPT_DBG_PT_XHCI_GEN2_ENABLE:
    break;
  case IDSOPT_DBG_PT_XHCI_GEN2_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB Equalization4
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB_EQUALIZATION4, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsbEqualization4)) {
  case IDSOPT_DBG_PT_USB_EQUALIZATION4_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB_EQUALIZATION4_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB_EQUALIZATION4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB Redriver
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB_REDRIVER, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsbRedriver)) {
  case IDSOPT_DBG_PT_USB_REDRIVER_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB_REDRIVER_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB_REDRIVER_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB31 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB31_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb31P0)) {
  case IDSOPT_DBG_PT_USB31_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB31_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB31_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB31 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB31_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb31P1)) {
  case IDSOPT_DBG_PT_USB31_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB31_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB31_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB30_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb30P0)) {
  case IDSOPT_DBG_PT_USB30_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB30_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb30P1)) {
  case IDSOPT_DBG_PT_USB30_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT2
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB30_P2, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb30P2)) {
  case IDSOPT_DBG_PT_USB30_P2_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P2_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P2_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT3
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB30_P3, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb30P3)) {
  case IDSOPT_DBG_PT_USB30_P3_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P3_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P3_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT4
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB30_P4, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb30P4)) {
  case IDSOPT_DBG_PT_USB30_P4_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P4_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT5
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB30_P5, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb30P5)) {
  case IDSOPT_DBG_PT_USB30_P5_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P5_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB30_P5_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB20_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb20P0)) {
  case IDSOPT_DBG_PT_USB20_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB20_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb20P1)) {
  case IDSOPT_DBG_PT_USB20_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT2
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB20_P2, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb20P2)) {
  case IDSOPT_DBG_PT_USB20_P2_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P2_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P2_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT3
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB20_P3, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb20P3)) {
  case IDSOPT_DBG_PT_USB20_P3_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P3_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P3_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT4
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB20_P4, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb20P4)) {
  case IDSOPT_DBG_PT_USB20_P4_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P4_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT5
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_USB20_P5, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTUsb20P5)) {
  case IDSOPT_DBG_PT_USB20_P5_DISABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P5_ENABLE:
    break;
  case IDSOPT_DBG_PT_USB20_P5_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB31 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB31_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb31P0)) {
  case IDSOPT_DBG_PT_PROM2_USB31_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB31_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB31_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB31 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB31_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb31P1)) {
  case IDSOPT_DBG_PT_PROM2_USB31_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB31_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB31_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB30_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb30P0)) {
  case IDSOPT_DBG_PT_PROM2_USB30_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB30_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB30_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB30_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb30P1)) {
  case IDSOPT_DBG_PT_PROM2_USB30_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB30_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB30_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB20_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb20P0)) {
  case IDSOPT_DBG_PT_PROM2_USB20_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB20_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb20P1)) {
  case IDSOPT_DBG_PT_PROM2_USB20_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT2
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB20_P2, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb20P2)) {
  case IDSOPT_DBG_PT_PROM2_USB20_P2_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P2_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P2_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT3
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB20_P3, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb20P3)) {
  case IDSOPT_DBG_PT_PROM2_USB20_P3_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P3_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P3_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT4
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB20_P4, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb20P4)) {
  case IDSOPT_DBG_PT_PROM2_USB20_P4_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P4_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT5
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM2_USB20_P5, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm2Usb20P5)) {
  case IDSOPT_DBG_PT_PROM2_USB20_P5_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P5_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM2_USB20_P5_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB31 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB31_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb31P0)) {
  case IDSOPT_DBG_PT_PROM1_USB31_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB31_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB31_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB31 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB31_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb31P1)) {
  case IDSOPT_DBG_PT_PROM1_USB31_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB31_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB31_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB30 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB30_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb30P0)) {
  case IDSOPT_DBG_PT_PROM1_USB30_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB30_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB30_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT0
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB20_P0, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb20P0)) {
  case IDSOPT_DBG_PT_PROM1_USB20_P0_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P0_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P0_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT1
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB20_P1, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb20P1)) {
  case IDSOPT_DBG_PT_PROM1_USB20_P1_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P1_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P1_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT2
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB20_P2, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb20P2)) {
  case IDSOPT_DBG_PT_PROM1_USB20_P2_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P2_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P2_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT3
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB20_P3, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb20P3)) {
  case IDSOPT_DBG_PT_PROM1_USB20_P3_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P3_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P3_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT4
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB20_P4, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb20P4)) {
  case IDSOPT_DBG_PT_PROM1_USB20_P4_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P4_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P4_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT USB20 PORT5
IDS_NV_READ_SKIP (IDSNVID_DBG_PT_PROM1_USB20_P5, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTProm1Usb20P5)) {
  case IDSOPT_DBG_PT_PROM1_USB20_P5_DISABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P5_ENABLE:
    break;
  case IDSOPT_DBG_PT_PROM1_USB20_P5_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 0 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT0_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort0Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT0_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT0_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT0_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 1 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT1_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort1Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT1_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT1_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT1_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 2 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT2_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort2Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT2_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT2_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT2_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 3 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT3_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort3Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT3_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT3_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT3_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 4 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT4_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort4Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT4_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT4_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT4_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 5 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT5_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort5Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT5_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT5_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT5_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 6 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT6_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort6Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT6_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT6_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT6_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}

//PT PCIE Port 7 Enable
IDS_NV_READ_SKIP (IDSNVID_CMN_PT_PCIE_PORT7_ENABLE, &IdsNvValue) {
  switch (IdsNvValue) {
  switch (PcdGet8 (PcdPTPciePort7Enable)) {
  case IDSOPT_CMN_PT_PCIE_PORT7_ENABLE_DISABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT7_ENABLE_ENABLED:
    break;
  case IDSOPT_CMN_PT_PCIE_PORT7_ENABLE_AUTO:
    break;
  default:
    ASSERT (FALSE);
    break;
  }
}


