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

#ifndef _IDS_NV_INT_DEF_SSP_H_
#define _IDS_NV_INT_DEF_SSP_H_

///L3 way locking
///Number of ways allocated to trace data in the L3M.
typedef enum {
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_TWO = 0,///<Two
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_SIX = 1,///<Six
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_TEN = 2,///<Ten
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_FOURTEEN = 3,///<Fourteen
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK;

///L3 way locking CCD bitmap
///bitmap to select which CCD should apply to. Bit[0] - logical CCD0, Bit[1] - logical CCD1
#define IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_CCD_BITMAP_MIN 0 ///< Min of L3 way locking CCD bitmap
#define IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_CCD_BITMAP_MAX 0xff ///< Max of L3 way locking CCD bitmap

///L3 Range Lock Enable
///L3 Range Lock Enable
typedef enum {
  IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN;

///CacheLock Disable
///Control LS_CFG[LsCfgDisCacheLock]
typedef enum {
  IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS;

///SpecLockMap Disable
///Control LS_CFG[LsCfgDisSpecLockMap]. Note: if the 'Enable IBS' option is Enabled, SpecLockMap will be disabled and setting this option to 'Enable' will have no effect on the bit field.
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS;

///Locks to only schedule non-spec
///Control LS_CFG[LsCfgScnLockNs]
typedef enum {
  IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS;

///ResyncOoOLdOnL1Evict
///Control LS_CFG[LsCfgResyncOoOLdOnL1Evict]
typedef enum {
  IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT;

///MemFile2EGS Disable
///Control LS_CFG[LsCfgDisMemfile2EGS]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS;

///SpecWcReq Disable
///Control LS_CFG[LsCfgDisSpecWcReq]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS;

///ForceAllSbex
///Control LS_CFG[LsCfgForceAllSbex]
typedef enum {
  IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX;

///OC_BUILD_CNT_MAX
///Control IC_CFG[IcCfgOcBuildCntMax]
#define IDSOPT_DBG_CPU_GEN_OC_BLD_CNT_MAX_MIN 0 ///< Min of OC_BUILD_CNT_MAX
#define IDSOPT_DBG_CPU_GEN_OC_BLD_CNT_MAX_MAX 0x1f ///< Max of OC_BUILD_CNT_MAX

///OC Token Bypass Disable
///Control IC_CFG[IcCfgDisOcTokenBypass]
typedef enum {
  IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS;

///Disable Spec TLB Reload
///Control DC_CFG[DisSpecTlbRld]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS;

///Disable L1 Region HW Prefetcher
///Control DC_CFG[DisRegionHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS;

///Disable L1 Stride HW Prefetcher
///Control DC_CFG[DisStrideHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS;

///Disable L1 HW Prefetcher
///Control DC_CFG[DisHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS;

///TW_CFG: CohMemTypesOnly
///Control TW_CFG[TwCfgCohMemTypesOnly]
typedef enum {
  IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY;

///FP_CFG: RET_DISACCF
///Control FP_CFG[RET_DISACCF]
typedef enum {
  IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F;

///FP_CFG: RET_ADVTOK_RET
///Control FP_CFG[RET_ADVTOK_RET]
#define IDSOPT_DBG_CPU_GEN_RET_ADV_TOK_RET_MIN 0 ///< Min of FP_CFG: RET_ADVTOK_RET
#define IDSOPT_DBG_CPU_GEN_RET_ADV_TOK_RET_MAX 0x7 ///< Max of FP_CFG: RET_ADVTOK_RET

///FP_CFG: SCE_THROTTLE_X87
///Control FP_CFG[SCE_THROTTLE_X87]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_THR_X87_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_THR_X87_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_THR_X87_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_THR_X87;

///FP_CFG: SCE_ENABLE_RRT
///Control FP_CFG[SCE_ENABLE_RRT]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_EN_RRT_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_EN_RRT_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_EN_RRT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_EN_RRT;

///FP_CFG: SCE_ALWAYS_THROTTLE
///Control FP_CFG[SCE_ALWAYS_THROTTLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_08 = 0,///<0/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_18 = 1,///<1/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_28 = 2,///<2/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_48 = 3,///<4/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR;

///FP_CFG: SCE_LIVELOCK_THRESH
///Control FP_CFG[SCE_LIVELOCK_THRESH]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_16 = 0,///<16
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_32 = 1,///<32
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_64 = 2,///<64
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH;

///FP_CFG: SCE_DIDT_TH_ENABLE
///Control FP_CFG[SCE_DIDT_TH_ENABLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN;

///FP_CFG: SCE_DIDT_INJ_R_ENABLE
///Control FP_CFG[SCE_DIDT_INJ_R_ENABLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN;

///FP_CFG: SCE_DIDT_INJ_F_ENABLE
///Control FP_CFG[SCE_DIDT_INJ_F_ENABLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN;

///FP_CFG: SCE_DIDT_TH_SCHEME
///Control FP_CFG[SCE_DIDT_TH_SCHEME]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME_REACT = 0,///<React
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME_PRESET = 1,///<Preset
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME;

///FP_CFG: SCE_DIDT_TIMECONST
///Control FP_CFG[SCE_DIDT_TIMECONST]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_2 = 0,///<2
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_4 = 1,///<4
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_8 = 2,///<8
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST;

///FP_CFG: SCE_DIDT_TH_THRESH
///Control FP_CFG[SCE_DIDT_TH_THRESH]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH_REGULAR = 0,///<Regular
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH_LOW = 1,///<Low
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH;

///FP_CFG: SCE_DIDT_INJ_THRESH
///Control FP_CFG[SCE_DIDT_INJ_THRESH]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_LOW = 0,///<Low
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_MEDLOW = 1,///<Med Low
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_MEDHIGH = 2,///<Med High
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_HIGH = 3,///<High
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH;

///Stack Engine Disable
///Control DE_CFG[DecfgStackEngineDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS;

///Mem File Disable
///Control DE_CFG[DecfgMemfileDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS;

///Disable MemRenaming
///Control DE_CFG[DecfgMemRenameDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS;

///Branch Fusion
///Control DE_CFG[DecfgBranchFusionDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_BRANCH_FUSION_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BRANCH_FUSION_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_BRANCH_FUSION_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_BRANCH_FUSION;

///DisableAllEarlyVbTokenRet
///Control L2_CFG[DisableAllEarlyVbTokenRet]
typedef enum {
  IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS;

///L2EvictForceDcBackprobe
///Control L2_CFG[L2EvictForceDcBackprobe]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB;

///L2WcbXrqSerializeTidAgnostic
///Control L2_CFG[L2WcbXrqSerializeTidAgnostic]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN;

///TdPickThrottleEnable
///Control L2_CFG[TdPickThrottleEnable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN;

///Disable L2 Pf Low Arb Pri
///Control L2_CFG[DisableL2PfLowArbPriority]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS;

///DisableLsReqPfPromotion
///Control L2_CFG[DisableLsReqPfPromotion]
typedef enum {
  IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS;

///L2 Max Stream Distance
///Control L2_PFCFG[MaxStreamDist]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_31LINES = 0,///<31 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_24LINES = 1,///<24 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_16LINES = 2,///<16 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_8LINES = 3,///<8 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST;

///L2 Page Pf Distance
///Control L2_PFCFG[PagePfDist]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_16LINES = 0,///<16 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_8LINES = 1,///<8 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_20LINES = 2,///<20 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_28LINES = 3,///<28 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST;

///Stream Throttle Control
///Control L2_PFCFG[StreamThrottleControl]
typedef enum {
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_OFF = 0,///<Off
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_ON = 1,///<On
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_UPDATEIMM = 2,///<Update Imm
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_UPDATE128RSP = 3,///<Update 128 rsp
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL;

///L2 Stride Prefetcher
///Control L2_PFCFG[EnableStridePf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF;

///L2 Max Stride Distance
///Control L2_PFCFG[MaxStrideDist]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_20STRIDES = 0,///<20 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_16STRIDES = 1,///<16 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_12STRIDES = 2,///<12 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_8STRIDES = 3,///<8 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST;

///Page Pf Hint Dis
///Control L2_PFCFG[DisablePagePfHint]
typedef enum {
  IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS;

///L2 Stream Throttle Disable
///Control L2_PFCFG[L2StreamThrottleDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS;

///L2 Up Down Prefetcher
///Control L2_PFCFG[EnableUpDownPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF;

///EX_CFG: FORCE_EXSCBUSY_GATER
///Control EX_CFG[FORCE_EXSCBUSY_GATER]
typedef enum {
  IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER;

///DisLiveLockIgnMabIdxBlk
///Control LS_CFG2[DisLiveLockIgnMabIdxBlk]
typedef enum {
  IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS;

///DisStIgnMabIdxBlk
///Control LS_CFG2[DisStIgnMabIdxBlk]
typedef enum {
  IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS;

///DisDcTagPaDcVFatalErr
///Control LS_CFG2[DisDcTagPaDcVFatalErr]
typedef enum {
  IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS;

///Disable Recent
///Control BP_CFG[DIS_RECENT]
typedef enum {
  IDSOPT_DBG_CPU_GEN_RECENT_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RECENT_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_RECENT_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_RECENT_DIS;

///BP Prefetch Disable
///Control BP_CFG[BpCfgDisPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_BP_PF_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BP_PF_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_BP_PF_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_BP_PF_DIS;

///BP Disable
///Control BP_CFG[DIS_L1BTB]
typedef enum {
  IDSOPT_DBG_CPU_GEN_BP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_BP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_BP_DIS;

///L2 Range Lock Enable
///L2 Range Lock Enable
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN;

///Report Responsible Victim
///Control ChL3Cfg0[ReportResponsibleVic]
typedef enum {
  IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC;

///Report Shared Victim
///Control ChL3Cfg0[ReportSharedVic]
typedef enum {
  IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC;

///Mesh Gate Level
///Control ChL3Cfg0[MeshGateLvl]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_OFF = 0,///<Off
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_REQUEST = 1,///<Request
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_MEMORY = 2,///<Memory
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_DATAFLOW = 3,///<Dataflow
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL;

///DelayedWakeEn
///Control ChL3Cfg0[DelayedWakeEn]
typedef enum {
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN;

///Delayed Wake Count
///Control ChL3Cfg0[DelayedWakeCount]
typedef enum {
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_64VICTIMS = 0,///<64 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_128VICTIMS = 1,///<128 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_256VICTIMS = 2,///<256 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_512VICTIMS = 3,///<512 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_1024VICTIMS = 4,///<1024 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_2048VICTIMS = 5,///<2048 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_4096VICTIMS = 6,///<4096 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_UNLIMITED = 7,///<Unlimited
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT;

///WrSzLkUpDis
///Control ChL3Cfg0[WrSzLkUpDis]
typedef enum {
  IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS;

///Spec DRAM Rd Dis
///Control ChL3Cfg1[SpecDramRdDis]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS;

///Mesh Gate Hold
///Control ChL3Cfg1[MeshGateHold]
#define IDSOPT_DBG_CPU_GEN_MESH_GATE_HOLD_MIN 0 ///< Min of Mesh Gate Hold
#define IDSOPT_DBG_CPU_GEN_MESH_GATE_HOLD_MAX 0x3 ///< Max of Mesh Gate Hold

///Vmg16TB
typedef enum {
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG16_TB_0 = 0,///<0
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG16_TB_1 = 1,///<1
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG16_TB_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG16_TB;

///VmgRemapDis
typedef enum {
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_REMAP_DIS_0 = 0,///<0
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_REMAP_DIS_1 = 1,///<1
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_REMAP_DIS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_REMAP_DIS;

///VmgKeyReclaimThresh
typedef enum {
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_0 = 0,///<0
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_1 = 1,///<1
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_2 = 2,///<2
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_3 = 3,///<3
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_4 = 4,///<4
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_5 = 5,///<5
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_6 = 6,///<6
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_7 = 7,///<7
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_THRESH;

///VmgKeyReclaimNum
typedef enum {
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_0 = 0,///<0
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_1 = 1,///<1
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_2 = 2,///<2
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_3 = 3,///<3
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_4 = 4,///<4
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_5 = 5,///<5
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_6 = 6,///<6
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_7 = 7,///<7
  IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_CACHE_L3_CRB428_VMG_KEY_RECLAIM_NUM;

///Enable Redirect Shutdown to HDT
typedef enum {
  IDSOPT_DBG_CPU_GEN_REDIRECT_SHUTDOWN_TO_HDT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_REDIRECT_SHUTDOWN_TO_HDT_AUTO = 0,///<Auto
} IDSOPT_DBG_CPU_GEN_REDIRECT_SHUTDOWN_TO_HDT;

///Enable Redirect int1 int3 to HDT
///redirect debug exceptions and breakpoints to HDT
typedef enum {
  IDSOPT_DBG_CPU_GEN_REDIRECT_EXCEPTIONS_TO_HDT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_REDIRECT_EXCEPTIONS_TO_HDT_AUTO = 0,///<Auto
} IDSOPT_DBG_CPU_GEN_REDIRECT_EXCEPTIONS_TO_HDT;

///Exception Breakpoint Control
///Enable:\n  Set MSRC001_1018[8]=0x1\n  Set MSRC001_100A[17]=1\nDisable:\n  Set MSRC001_1018[8]=0x0\n  Set MSRC001_100A[17]=0
typedef enum {
  IDSOPT_DBG_CPU_EXCP_BP_CTRL_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_CPU_EXCP_BP_CTRL_ENABLE = 0x1,///<Enable
} IDSOPT_DBG_CPU_EXCP_BP_CTRL;

///Exception Vector
///Specifies an exception vector
#define IDSOPT_DBG_CPU_EXCP_VEC_MIN 0 ///< Min of Exception Vector
#define IDSOPT_DBG_CPU_EXCP_VEC_MAX 0xff ///< Max of Exception Vector

///LBR
///1=Enable last branch record.
typedef enum {
  IDSOPT_DBG_CPU_GEN_LBR_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_LBR_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_LBR_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LBR;

///HDT OUT
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDTOUT_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDTOUT_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDTOUT;

///ABL BreakPoint
///Enable : Enable Break Point Function for ABL\nDisable : Disable Break Point Function for ABL\nAuto : Keep default behavior
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_BP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_ABL_BP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_ABL_BP_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ABL_BP;

///ABL HDTOUT
///ABL HdtOut is require additional HDT perl script\nEnable : Enable HdtOut Function for ABL\nDisable : Disable HdtOut Function for ABL
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT;

///ABL HDTOUT Die Control
///AUTO, Select Die 0 for SCM, and Socket 0 Die 1 for MCM\nManual, Specified the Enabled Die by ABL HDTOUT Die bitmask option
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_CTRL_AUTO = 0,///<AUTO
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_CTRL_MANUAL = 1,///<Manual
} IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_CTRL;

///ABL HDTOUT Die Bitmask
///Specified the ABLOUT enabled die through bit mask, each bit is corresponding to a die,  max support 2 sockets 4 dies. e.g. 0x16 enable Socket 0 Die 1 & Die 2, Socket 1 Die 0
#define IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_BIT_MASK_MIN 0 ///< Min of ABL HDTOUT Die Bitmask
#define IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_BIT_MASK_MAX 0xff ///< Max of ABL HDTOUT Die Bitmask

///HDT Breakpoint 1 (x86 AGESA start)
///Setting this option to enabled will cause the BIOS to force the system into HDT mode just before DRAM init, right after the backend code for the memory timing options is run and immediately before the DRAM enable bit is set. All of the registers for DCT init will be programmed, but the DRAM Init bit will not have been set yet.
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT1_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDT_BRKPT1;

///HDT Breakpoint 3 (Before OS)
///Setting this option to enabled will cause the BIOS to force the system into HDT mode very late in POST.
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT3_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT3_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDT_BRKPT3;

///HDT Breakpoint 2 (Before PCI init)
///Setting this option to enabled will cause the BIOS to force the system into HDT mode just before PCI initialization.
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT2_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDT_BRKPT2;

///Stall for unlock
///If enabled, BIOS will stall execution just prior to OS hand-off at the end of the POST process.  To proceed, set <TBD> to a non-zero value.
typedef enum {
  IDSOPT_DBG_CPU_GEN_STALL_FOR_UNLOCK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_STALL_FOR_UNLOCK_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_STALL_FOR_UNLOCK;

///SVM Lock
typedef enum {
  IDSOPT_DBG_CPU_GEN_SVM_LOCK_ENABLE = 0,///<Enable
  IDSOPT_DBG_CPU_GEN_SVM_LOCK_DISABLE = 1,///<Disable
} IDSOPT_DBG_CPU_GEN_SVM_LOCK;

///Core MSR Access Disable
///This control enables/disables the MSR Access in the Core.\n 0 = Core MSR Access ENABLED (DPM_CFG[MsrAccessDisable] = 0)\n 1 = Core MSR Access DISABLED (DPM_CFG[MsrAccessDisable] = 1)
typedef enum {
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_0 = 0,///<0
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_1 = 1,///<1
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS;

///uCode Patching
///Enable or disable microcode patching. If disabled, no microcode patches will be loaded. If enabled, only patches that apply to the installed processor will be loaded.
typedef enum {
  IDSOPT_DBG_CPU_GEN_U_CODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_U_CODE_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_GEN_U_CODE;

///Sync Flood on MCA
///Enable or disable BIOS Sync Flood on MCA.
typedef enum {
  IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA;

///ACPI WHEA
///Controls activation of CPU Machine Check Setting
typedef enum {
  IDSOPT_DBG_CPU_GEN_WHEA_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_WHEA_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_WHEA_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_WHEA;

///RdRand
///Disable RdRand instruction
typedef enum {
  IDSOPT_DBG_CPU_GEN_RD_RAND_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_RD_RAND_DISABLE = 1,///<Disable
} IDSOPT_DBG_CPU_GEN_RD_RAND;

///RdSeed
///Disable RdSeed instruction
typedef enum {
  IDSOPT_DBG_CPU_GEN_RD_SEED_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RD_SEED_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_GEN_RD_SEED;

///SMEE
///Control secure memory encryption enable
typedef enum {
  IDSOPT_DBG_CPU_GEN_SMEE_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SMEE_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SMEE_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SMEE;

///SmmLock Control
///Disabling this feature forces SmmLock to be cleared.
typedef enum {
  IDSOPT_DBG_CPU_SMM_LOCK_CONTROL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_SMM_LOCK_CONTROL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_SMM_LOCK_CONTROL;

///ACPI _PSS
///Enable / disable the P-state object declaration to the OS.
typedef enum {
  IDSOPT_DBG_CPU_PM_CTL_PSS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_PM_CTL_PSS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_PM_CTL_PSS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_PM_CTL_PSS;

///MCG_CTL Control
///Manual allows for overriding MCG_CTL for bank 22.
typedef enum {
  IDSOPT_DBG_CPU_MCG_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCG_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCG_CTL_CTRL;

///MCG_CTL Value
///Value to program the MCG_CTL MSR.
#define IDSOPT_DBG_CPU_MCG_CTL_VALUE_MIN 0 ///< Min of MCG_CTL Value
#define IDSOPT_DBG_CPU_MCG_CTL_VALUE_MAX 0xffffffffffffffff ///< Max of MCG_CTL Value

///CR4.MCE Control
///Set / clear CR4.MCE bit.
typedef enum {
  IDSOPT_DBG_CPU_CR4_MCE_CTRL_CLEAR = 0,///<Clear
  IDSOPT_DBG_CPU_CR4_MCE_CTRL_SET = 1,///<Set
  IDSOPT_DBG_CPU_CR4_MCE_CTRL_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_CR4_MCE_CTRL;

///Lock Threshold Counters
///Set MCAi_MISC[Locked] = 0/1
typedef enum {
  IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS_0 = 0,///<0
  IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS_1 = 1,///<1
  IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS;

///MCA0_CTL Control
///Manual allows for overriding MCA_CTL for bank 0.
typedef enum {
  IDSOPT_DBG_CPU_MCA0_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA0_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA0_CTL_CTRL;

///MCA0_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_LOW_MIN 0 ///< Min of MCA0_CTL_LOW
#define IDSOPT_DBG_CPU_MCA0_CTL_LOW_MAX 0xffffffff ///< Max of MCA0_CTL_LOW

///MCA0_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_HIGH_MIN 0 ///< Min of MCA0_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA0_CTL_HIGH_MAX 0xffffffff ///< Max of MCA0_CTL_HIGH

///MCA0_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 0.
typedef enum {
  IDSOPT_DBG_CPU_MCA0_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA0_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA0_CTL_MASK_CTRL;

///MCA0_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_LOW_MIN 0 ///< Min of MCA0_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA0_CTL_MASK_LOW

///MCA0_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_HIGH_MIN 0 ///< Min of MCA0_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA0_CTL_MASK_HIGH

///MCA1_CTL Control
///Manual allows for overriding MCA_CTL for bank 1.
typedef enum {
  IDSOPT_DBG_CPU_MCA1_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA1_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA1_CTL_CTRL;

///MCA1_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_LOW_MIN 0 ///< Min of MCA1_CTL_LOW
#define IDSOPT_DBG_CPU_MCA1_CTL_LOW_MAX 0xffffffff ///< Max of MCA1_CTL_LOW

///MCA1_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_HIGH_MIN 0 ///< Min of MCA1_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA1_CTL_HIGH_MAX 0xffffffff ///< Max of MCA1_CTL_HIGH

///MCA1_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 1.
typedef enum {
  IDSOPT_DBG_CPU_MCA1_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA1_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA1_CTL_MASK_CTRL;

///MCA1_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_LOW_MIN 0 ///< Min of MCA1_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA1_CTL_MASK_LOW

///MCA1_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_HIGH_MIN 0 ///< Min of MCA1_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA1_CTL_MASK_HIGH

///MCA2_CTL Control
///Manual allows for overriding MCA_CTL for bank 2.
typedef enum {
  IDSOPT_DBG_CPU_MCA2_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA2_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA2_CTL_CTRL;

///MCA2_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_LOW_MIN 0 ///< Min of MCA2_CTL_LOW
#define IDSOPT_DBG_CPU_MCA2_CTL_LOW_MAX 0xffffffff ///< Max of MCA2_CTL_LOW

///MCA2_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_HIGH_MIN 0 ///< Min of MCA2_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA2_CTL_HIGH_MAX 0xffffffff ///< Max of MCA2_CTL_HIGH

///MCA2_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 2.
typedef enum {
  IDSOPT_DBG_CPU_MCA2_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA2_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA2_CTL_MASK_CTRL;

///MCA2_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_LOW_MIN 0 ///< Min of MCA2_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA2_CTL_MASK_LOW

///MCA2_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_HIGH_MIN 0 ///< Min of MCA2_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA2_CTL_MASK_HIGH

///MCA3_CTL Control
///Manual allows for overriding MCA_CTL for bank 3.
typedef enum {
  IDSOPT_DBG_CPU_MCA3_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA3_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA3_CTL_CTRL;

///MCA3_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_LOW_MIN 0 ///< Min of MCA3_CTL_LOW
#define IDSOPT_DBG_CPU_MCA3_CTL_LOW_MAX 0xffffffff ///< Max of MCA3_CTL_LOW

///MCA3_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_HIGH_MIN 0 ///< Min of MCA3_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA3_CTL_HIGH_MAX 0xffffffff ///< Max of MCA3_CTL_HIGH

///MCA3_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 3.
typedef enum {
  IDSOPT_DBG_CPU_MCA3_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA3_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA3_CTL_MASK_CTRL;

///MCA3_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_LOW_MIN 0 ///< Min of MCA3_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA3_CTL_MASK_LOW

///MCA3_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_HIGH_MIN 0 ///< Min of MCA3_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA3_CTL_MASK_HIGH

///MCA4_CTL Control
///Manual allows for overriding MCA_CTL for bank 4.
typedef enum {
  IDSOPT_DBG_CPU_MCA4_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA4_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA4_CTL_CTRL;

///MCA4_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_LOW_MIN 0 ///< Min of MCA4_CTL_LOW
#define IDSOPT_DBG_CPU_MCA4_CTL_LOW_MAX 0xffffffff ///< Max of MCA4_CTL_LOW

///MCA4_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_HIGH_MIN 0 ///< Min of MCA4_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA4_CTL_HIGH_MAX 0xffffffff ///< Max of MCA4_CTL_HIGH

///MCA4_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 4.
typedef enum {
  IDSOPT_DBG_CPU_MCA4_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA4_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA4_CTL_MASK_CTRL;

///MCA4_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_LOW_MIN 0 ///< Min of MCA4_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA4_CTL_MASK_LOW

///MCA4_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_HIGH_MIN 0 ///< Min of MCA4_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA4_CTL_MASK_HIGH

///MCA5_CTL Control
///Manual allows for overriding MCA_CTL for bank 5.
typedef enum {
  IDSOPT_DBG_CPU_MCA5_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA5_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA5_CTL_CTRL;

///MCA5_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_LOW_MIN 0 ///< Min of MCA5_CTL_LOW
#define IDSOPT_DBG_CPU_MCA5_CTL_LOW_MAX 0xffffffff ///< Max of MCA5_CTL_LOW

///MCA5_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_HIGH_MIN 0 ///< Min of MCA5_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA5_CTL_HIGH_MAX 0xffffffff ///< Max of MCA5_CTL_HIGH

///MCA5_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 5.
typedef enum {
  IDSOPT_DBG_CPU_MCA5_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA5_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA5_CTL_MASK_CTRL;

///MCA5_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_LOW_MIN 0 ///< Min of MCA5_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA5_CTL_MASK_LOW

///MCA5_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_HIGH_MIN 0 ///< Min of MCA5_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA5_CTL_MASK_HIGH

///MCA6_CTL Control
///Manual allows for overriding MCA_CTL for bank 6.
typedef enum {
  IDSOPT_DBG_CPU_MCA6_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA6_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA6_CTL_CTRL;

///MCA6_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_LOW_MIN 0 ///< Min of MCA6_CTL_LOW
#define IDSOPT_DBG_CPU_MCA6_CTL_LOW_MAX 0xffffffff ///< Max of MCA6_CTL_LOW

///MCA6_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_HIGH_MIN 0 ///< Min of MCA6_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA6_CTL_HIGH_MAX 0xffffffff ///< Max of MCA6_CTL_HIGH

///MCA6_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 6.
typedef enum {
  IDSOPT_DBG_CPU_MCA6_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA6_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA6_CTL_MASK_CTRL;

///MCA6_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_LOW_MIN 0 ///< Min of MCA6_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA6_CTL_MASK_LOW

///MCA6_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_HIGH_MIN 0 ///< Min of MCA6_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA6_CTL_MASK_HIGH

///MCA7_CTL Control
///Manual allows for overriding MCA_CTL for bank 7.
typedef enum {
  IDSOPT_DBG_CPU_MCA7_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA7_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA7_CTL_CTRL;

///MCA7_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_LOW_MIN 0 ///< Min of MCA7_CTL_LOW
#define IDSOPT_DBG_CPU_MCA7_CTL_LOW_MAX 0xffffffff ///< Max of MCA7_CTL_LOW

///MCA7_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_HIGH_MIN 0 ///< Min of MCA7_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA7_CTL_HIGH_MAX 0xffffffff ///< Max of MCA7_CTL_HIGH

///MCA7_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 7.
typedef enum {
  IDSOPT_DBG_CPU_MCA7_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA7_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA7_CTL_MASK_CTRL;

///MCA7_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_LOW_MIN 0 ///< Min of MCA7_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA7_CTL_MASK_LOW

///MCA7_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_HIGH_MIN 0 ///< Min of MCA7_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA7_CTL_MASK_HIGH

///MCA8_CTL Control
///Manual allows for overriding MCA_CTL for bank 8.
typedef enum {
  IDSOPT_DBG_CPU_MCA8_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA8_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA8_CTL_CTRL;

///MCA8_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_LOW_MIN 0 ///< Min of MCA8_CTL_LOW
#define IDSOPT_DBG_CPU_MCA8_CTL_LOW_MAX 0xffffffff ///< Max of MCA8_CTL_LOW

///MCA8_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_HIGH_MIN 0 ///< Min of MCA8_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA8_CTL_HIGH_MAX 0xffffffff ///< Max of MCA8_CTL_HIGH

///MCA8_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 8.
typedef enum {
  IDSOPT_DBG_CPU_MCA8_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA8_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA8_CTL_MASK_CTRL;

///MCA8_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_LOW_MIN 0 ///< Min of MCA8_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA8_CTL_MASK_LOW

///MCA8_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_HIGH_MIN 0 ///< Min of MCA8_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA8_CTL_MASK_HIGH

///MCA9_CTL Control
///Manual allows for overriding MCA_CTL for bank 9.
typedef enum {
  IDSOPT_DBG_CPU_MCA9_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA9_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA9_CTL_CTRL;

///MCA9_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_LOW_MIN 0 ///< Min of MCA9_CTL_LOW
#define IDSOPT_DBG_CPU_MCA9_CTL_LOW_MAX 0xffffffff ///< Max of MCA9_CTL_LOW

///MCA9_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_HIGH_MIN 0 ///< Min of MCA9_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA9_CTL_HIGH_MAX 0xffffffff ///< Max of MCA9_CTL_HIGH

///MCA9_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 9.
typedef enum {
  IDSOPT_DBG_CPU_MCA9_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA9_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA9_CTL_MASK_CTRL;

///MCA9_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_LOW_MIN 0 ///< Min of MCA9_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA9_CTL_MASK_LOW

///MCA9_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_HIGH_MIN 0 ///< Min of MCA9_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA9_CTL_MASK_HIGH

///MCA10_CTL Control
///Manual allows for overriding MCA_CTL for bank 10.
typedef enum {
  IDSOPT_DBG_CPU_MCA10_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA10_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA10_CTL_CTRL;

///MCA10_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_LOW_MIN 0 ///< Min of MCA10_CTL_LOW
#define IDSOPT_DBG_CPU_MCA10_CTL_LOW_MAX 0xffffffff ///< Max of MCA10_CTL_LOW

///MCA10_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_HIGH_MIN 0 ///< Min of MCA10_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA10_CTL_HIGH_MAX 0xffffffff ///< Max of MCA10_CTL_HIGH

///MCA10_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 10.
typedef enum {
  IDSOPT_DBG_CPU_MCA10_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA10_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA10_CTL_MASK_CTRL;

///MCA10_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_LOW_MIN 0 ///< Min of MCA10_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA10_CTL_MASK_LOW

///MCA10_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_HIGH_MIN 0 ///< Min of MCA10_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA10_CTL_MASK_HIGH

///MCA11_CTL Control
///Manual allows for overriding MCA_CTL for bank 11.
typedef enum {
  IDSOPT_DBG_CPU_MCA11_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA11_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA11_CTL_CTRL;

///MCA11_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_LOW_MIN 0 ///< Min of MCA11_CTL_LOW
#define IDSOPT_DBG_CPU_MCA11_CTL_LOW_MAX 0xffffffff ///< Max of MCA11_CTL_LOW

///MCA11_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_HIGH_MIN 0 ///< Min of MCA11_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA11_CTL_HIGH_MAX 0xffffffff ///< Max of MCA11_CTL_HIGH

///MCA11_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 11.
typedef enum {
  IDSOPT_DBG_CPU_MCA11_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA11_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA11_CTL_MASK_CTRL;

///MCA11_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_LOW_MIN 0 ///< Min of MCA11_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA11_CTL_MASK_LOW

///MCA11_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_HIGH_MIN 0 ///< Min of MCA11_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA11_CTL_MASK_HIGH

///MCA12_CTL Control
///Manual allows for overriding MCA_CTL for bank 12.
typedef enum {
  IDSOPT_DBG_CPU_MCA12_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA12_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA12_CTL_CTRL;

///MCA12_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_LOW_MIN 0 ///< Min of MCA12_CTL_LOW
#define IDSOPT_DBG_CPU_MCA12_CTL_LOW_MAX 0xffffffff ///< Max of MCA12_CTL_LOW

///MCA12_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_HIGH_MIN 0 ///< Min of MCA12_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA12_CTL_HIGH_MAX 0xffffffff ///< Max of MCA12_CTL_HIGH

///MCA12_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_LOW_MIN 0 ///< Min of MCA12_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA12_CTL_MASK_LOW

///MCA12_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 12.
typedef enum {
  IDSOPT_DBG_CPU_MCA12_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA12_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA12_CTL_MASK_CTRL;

///MCA12_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_HIGH_MIN 0 ///< Min of MCA12_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA12_CTL_MASK_HIGH

///MCA13_CTL Control
///Manual allows for overriding MCA_CTL for bank 13.
typedef enum {
  IDSOPT_DBG_CPU_MCA13_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA13_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA13_CTL_CTRL;

///MCA13_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_LOW_MIN 0 ///< Min of MCA13_CTL_LOW
#define IDSOPT_DBG_CPU_MCA13_CTL_LOW_MAX 0xffffffff ///< Max of MCA13_CTL_LOW

///MCA13_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_HIGH_MIN 0 ///< Min of MCA13_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA13_CTL_HIGH_MAX 0xffffffff ///< Max of MCA13_CTL_HIGH

///MCA13_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 13.
typedef enum {
  IDSOPT_DBG_CPU_MCA13_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA13_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA13_CTL_MASK_CTRL;

///MCA13_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_LOW_MIN 0 ///< Min of MCA13_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA13_CTL_MASK_LOW

///MCA13_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_HIGH_MIN 0 ///< Min of MCA13_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA13_CTL_MASK_HIGH

///MCA14_CTL Control
///Manual allows for overriding MCA_CTL for bank 14.
typedef enum {
  IDSOPT_DBG_CPU_MCA14_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA14_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA14_CTL_CTRL;

///MCA14_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_LOW_MIN 0 ///< Min of MCA14_CTL_LOW
#define IDSOPT_DBG_CPU_MCA14_CTL_LOW_MAX 0xffffffff ///< Max of MCA14_CTL_LOW

///MCA14_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_HIGH_MIN 0 ///< Min of MCA14_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA14_CTL_HIGH_MAX 0xffffffff ///< Max of MCA14_CTL_HIGH

///MCA14_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 14.
typedef enum {
  IDSOPT_DBG_CPU_MCA14_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA14_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA14_CTL_MASK_CTRL;

///MCA14_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_LOW_MIN 0 ///< Min of MCA14_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA14_CTL_MASK_LOW

///MCA14_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_HIGH_MIN 0 ///< Min of MCA14_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA14_CTL_MASK_HIGH

///MCA15_CTL Control
///Manual allows for overriding MCA_CTL for bank 15.
typedef enum {
  IDSOPT_DBG_CPU_MCA15_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA15_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA15_CTL_CTRL;

///MCA15_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_LOW_MIN 0 ///< Min of MCA15_CTL_LOW
#define IDSOPT_DBG_CPU_MCA15_CTL_LOW_MAX 0xffffffff ///< Max of MCA15_CTL_LOW

///MCA15_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_HIGH_MIN 0 ///< Min of MCA15_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA15_CTL_HIGH_MAX 0xffffffff ///< Max of MCA15_CTL_HIGH

///MCA15_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 15.
typedef enum {
  IDSOPT_DBG_CPU_MCA15_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA15_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA15_CTL_MASK_CTRL;

///MCA15_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_LOW_MIN 0 ///< Min of MCA15_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA15_CTL_MASK_LOW

///MCA15_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_HIGH_MIN 0 ///< Min of MCA15_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA15_CTL_MASK_HIGH

///MCA16_CTL Control
///Manual allows for overriding MCA_CTL for bank 16.
typedef enum {
  IDSOPT_DBG_CPU_MCA16_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA16_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA16_CTL_CTRL;

///MCA16_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_LOW_MIN 0 ///< Min of MCA16_CTL_LOW
#define IDSOPT_DBG_CPU_MCA16_CTL_LOW_MAX 0xffffffff ///< Max of MCA16_CTL_LOW

///MCA16_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_HIGH_MIN 0 ///< Min of MCA16_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA16_CTL_HIGH_MAX 0xffffffff ///< Max of MCA16_CTL_HIGH

///MCA16_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 16.
typedef enum {
  IDSOPT_DBG_CPU_MCA16_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA16_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA16_CTL_MASK_CTRL;

///MCA16_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_LOW_MIN 0 ///< Min of MCA16_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA16_CTL_MASK_LOW

///MCA16_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_HIGH_MIN 0 ///< Min of MCA16_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA16_CTL_MASK_HIGH

///MCA17_CTL Control
///Manual allows for overriding MCA_CTL for bank 17.
typedef enum {
  IDSOPT_DBG_CPU_MCA17_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA17_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA17_CTL_CTRL;

///MCA17_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_LOW_MIN 0 ///< Min of MCA17_CTL_LOW
#define IDSOPT_DBG_CPU_MCA17_CTL_LOW_MAX 0xffffffff ///< Max of MCA17_CTL_LOW

///MCA17_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_HIGH_MIN 0 ///< Min of MCA17_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA17_CTL_HIGH_MAX 0xffffffff ///< Max of MCA17_CTL_HIGH

///MCA17_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 17.
typedef enum {
  IDSOPT_DBG_CPU_MCA17_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA17_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA17_CTL_MASK_CTRL;

///MCA17_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_LOW_MIN 0 ///< Min of MCA17_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA17_CTL_MASK_LOW

///MCA17_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_HIGH_MIN 0 ///< Min of MCA17_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA17_CTL_MASK_HIGH

///MCA18_CTL Control
///Manual allows for overriding MCA_CTL for bank 18.
typedef enum {
  IDSOPT_DBG_CPU_MCA18_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA18_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA18_CTL_CTRL;

///MCA18_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_LOW_MIN 0 ///< Min of MCA18_CTL_LOW
#define IDSOPT_DBG_CPU_MCA18_CTL_LOW_MAX 0xffffffff ///< Max of MCA18_CTL_LOW

///MCA18_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_HIGH_MIN 0 ///< Min of MCA18_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA18_CTL_HIGH_MAX 0xffffffff ///< Max of MCA18_CTL_HIGH

///MCA18_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 18.
typedef enum {
  IDSOPT_DBG_CPU_MCA18_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA18_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA18_CTL_MASK_CTRL;

///MCA18_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_LOW_MIN 0 ///< Min of MCA18_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA18_CTL_MASK_LOW

///MCA18_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_HIGH_MIN 0 ///< Min of MCA18_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA18_CTL_MASK_HIGH

///MCA19_CTL Control
///Manual allows for overriding MCA_CTL for bank 19.
typedef enum {
  IDSOPT_DBG_CPU_MCA19_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA19_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA19_CTL_CTRL;

///MCA19_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_LOW_MIN 0 ///< Min of MCA19_CTL_LOW
#define IDSOPT_DBG_CPU_MCA19_CTL_LOW_MAX 0xffffffff ///< Max of MCA19_CTL_LOW

///MCA19_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_HIGH_MIN 0 ///< Min of MCA19_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA19_CTL_HIGH_MAX 0xffffffff ///< Max of MCA19_CTL_HIGH

///MCA19_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 19.
typedef enum {
  IDSOPT_DBG_CPU_MCA19_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA19_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA19_CTL_MASK_CTRL;

///MCA19_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_LOW_MIN 0 ///< Min of MCA19_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA19_CTL_MASK_LOW

///MCA19_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_HIGH_MIN 0 ///< Min of MCA19_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA19_CTL_MASK_HIGH

///MCA20_CTL Control
///Manual allows for overriding MCA_CTL for bank 20.
typedef enum {
  IDSOPT_DBG_CPU_MCA20_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA20_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA20_CTL_CTRL;

///MCA20_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_LOW_MIN 0 ///< Min of MCA20_CTL_LOW
#define IDSOPT_DBG_CPU_MCA20_CTL_LOW_MAX 0xffffffff ///< Max of MCA20_CTL_LOW

///MCA20_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_HIGH_MIN 0 ///< Min of MCA20_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA20_CTL_HIGH_MAX 0xffffffff ///< Max of MCA20_CTL_HIGH

///MCA20_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 20.
typedef enum {
  IDSOPT_DBG_CPU_MCA20_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA20_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA20_CTL_MASK_CTRL;

///MCA20_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_LOW_MIN 0 ///< Min of MCA20_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA20_CTL_MASK_LOW

///MCA20_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_HIGH_MIN 0 ///< Min of MCA20_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA20_CTL_MASK_HIGH

///MCA21_CTL Control
///Manual allows for overriding MCA_CTL for bank 21.
typedef enum {
  IDSOPT_DBG_CPU_MCA21_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA21_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA21_CTL_CTRL;

///MCA21_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_LOW_MIN 0 ///< Min of MCA21_CTL_LOW
#define IDSOPT_DBG_CPU_MCA21_CTL_LOW_MAX 0xffffffff ///< Max of MCA21_CTL_LOW

///MCA21_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_HIGH_MIN 0 ///< Min of MCA21_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA21_CTL_HIGH_MAX 0xffffffff ///< Max of MCA21_CTL_HIGH

///MCA21_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 21.
typedef enum {
  IDSOPT_DBG_CPU_MCA21_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA21_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA21_CTL_MASK_CTRL;

///MCA21_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_LOW_MIN 0 ///< Min of MCA21_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA21_CTL_MASK_LOW

///MCA21_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_HIGH_MIN 0 ///< Min of MCA21_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA21_CTL_MASK_HIGH

///MCA22_CTL Control
///Manual allows for overriding MCA_CTL for bank 22.
typedef enum {
  IDSOPT_DBG_CPU_MCA22_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA22_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA22_CTL_CTRL;

///MCA22_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_LOW_MIN 0 ///< Min of MCA22_CTL_LOW
#define IDSOPT_DBG_CPU_MCA22_CTL_LOW_MAX 0xffffffff ///< Max of MCA22_CTL_LOW

///MCA22_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_HIGH_MIN 0 ///< Min of MCA22_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA22_CTL_HIGH_MAX 0xffffffff ///< Max of MCA22_CTL_HIGH

///MCA22_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 22.
typedef enum {
  IDSOPT_DBG_CPU_MCA22_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA22_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA22_CTL_MASK_CTRL;

///MCA22_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_LOW_MIN 0 ///< Min of MCA22_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA22_CTL_MASK_LOW

///MCA22_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_HIGH_MIN 0 ///< Min of MCA22_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA22_CTL_MASK_HIGH

///MCA23_CTL Control
///Manual allows for overriding MCA_CTL for bank 23.
typedef enum {
  IDSOPT_DBG_CPU_MCA23_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA23_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA23_CTL_CTRL;

///MCA23_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 23.
#define IDSOPT_DBG_CPU_MCA23_CTL_LOW_MIN 0 ///< Min of MCA23_CTL_LOW
#define IDSOPT_DBG_CPU_MCA23_CTL_LOW_MAX 0xffffffff ///< Max of MCA23_CTL_LOW

///MCA23_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 23.
#define IDSOPT_DBG_CPU_MCA23_CTL_HIGH_MIN 0 ///< Min of MCA23_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA23_CTL_HIGH_MAX 0xffffffff ///< Max of MCA23_CTL_HIGH

///MCA23_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 23.
typedef enum {
  IDSOPT_DBG_CPU_MCA23_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA23_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA23_CTL_MASK_CTRL;

///MCA23_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 23.
#define IDSOPT_DBG_CPU_MCA23_CTL_MASK_LOW_MIN 0 ///< Min of MCA23_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA23_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA23_CTL_MASK_LOW

///MCA23_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 23.
#define IDSOPT_DBG_CPU_MCA23_CTL_MASK_HIGH_MIN 0 ///< Min of MCA23_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA23_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA23_CTL_MASK_HIGH

///MCA24_CTL Control
///Manual allows for overriding MCA_CTL for bank 24.
typedef enum {
  IDSOPT_DBG_CPU_MCA24_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA24_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA24_CTL_CTRL;

///MCA24_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 24.
#define IDSOPT_DBG_CPU_MCA24_CTL_LOW_MIN 0 ///< Min of MCA24_CTL_LOW
#define IDSOPT_DBG_CPU_MCA24_CTL_LOW_MAX 0xffffffff ///< Max of MCA24_CTL_LOW

///MCA24_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 24.
#define IDSOPT_DBG_CPU_MCA24_CTL_HIGH_MIN 0 ///< Min of MCA24_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA24_CTL_HIGH_MAX 0xffffffff ///< Max of MCA24_CTL_HIGH

///MCA24_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 24.
typedef enum {
  IDSOPT_DBG_CPU_MCA24_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA24_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA24_CTL_MASK_CTRL;

///MCA24_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 24.
#define IDSOPT_DBG_CPU_MCA24_CTL_MASK_LOW_MIN 0 ///< Min of MCA24_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA24_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA24_CTL_MASK_LOW

///MCA24_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 24.
#define IDSOPT_DBG_CPU_MCA24_CTL_MASK_HIGH_MIN 0 ///< Min of MCA24_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA24_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA24_CTL_MASK_HIGH

///MCA25_CTL Control
///Manual allows for overriding MCA_CTL for bank 25.
typedef enum {
  IDSOPT_DBG_CPU_MCA25_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA25_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA25_CTL_CTRL;

///MCA25_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 25.
#define IDSOPT_DBG_CPU_MCA25_CTL_LOW_MIN 0 ///< Min of MCA25_CTL_LOW
#define IDSOPT_DBG_CPU_MCA25_CTL_LOW_MAX 0xffffffff ///< Max of MCA25_CTL_LOW

///MCA25_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 25.
#define IDSOPT_DBG_CPU_MCA25_CTL_HIGH_MIN 0 ///< Min of MCA25_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA25_CTL_HIGH_MAX 0xffffffff ///< Max of MCA25_CTL_HIGH

///MCA25_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 25.
typedef enum {
  IDSOPT_DBG_CPU_MCA25_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA25_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA25_CTL_MASK_CTRL;

///MCA25_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 25.
#define IDSOPT_DBG_CPU_MCA25_CTL_MASK_LOW_MIN 0 ///< Min of MCA25_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA25_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA25_CTL_MASK_LOW

///MCA25_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 25.
#define IDSOPT_DBG_CPU_MCA25_CTL_MASK_HIGH_MIN 0 ///< Min of MCA25_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA25_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA25_CTL_MASK_HIGH

///MCA26_CTL Control
///Manual allows for overriding MCA_CTL for bank 26.
typedef enum {
  IDSOPT_DBG_CPU_MCA26_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA26_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA26_CTL_CTRL;

///MCA26_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 26.
#define IDSOPT_DBG_CPU_MCA26_CTL_LOW_MIN 0 ///< Min of MCA26_CTL_LOW
#define IDSOPT_DBG_CPU_MCA26_CTL_LOW_MAX 0xffffffff ///< Max of MCA26_CTL_LOW

///MCA26_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 26.
#define IDSOPT_DBG_CPU_MCA26_CTL_HIGH_MIN 0 ///< Min of MCA26_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA26_CTL_HIGH_MAX 0xffffffff ///< Max of MCA26_CTL_HIGH

///MCA26_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 26.
typedef enum {
  IDSOPT_DBG_CPU_MCA26_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA26_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA26_CTL_MASK_CTRL;

///MCA26_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 26.
#define IDSOPT_DBG_CPU_MCA26_CTL_MASK_LOW_MIN 0 ///< Min of MCA26_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA26_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA26_CTL_MASK_LOW

///MCA26_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 26.
#define IDSOPT_DBG_CPU_MCA26_CTL_MASK_HIGH_MIN 0 ///< Min of MCA26_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA26_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA26_CTL_MASK_HIGH

///MCA27_CTL Control
///Manual allows for overriding MCA_CTL for bank 27.
typedef enum {
  IDSOPT_DBG_CPU_MCA27_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA27_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA27_CTL_CTRL;

///MCA27_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 27.
#define IDSOPT_DBG_CPU_MCA27_CTL_LOW_MIN 0 ///< Min of MCA27_CTL_LOW
#define IDSOPT_DBG_CPU_MCA27_CTL_LOW_MAX 0xffffffff ///< Max of MCA27_CTL_LOW

///MCA27_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 27.
#define IDSOPT_DBG_CPU_MCA27_CTL_HIGH_MIN 0 ///< Min of MCA27_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA27_CTL_HIGH_MAX 0xffffffff ///< Max of MCA27_CTL_HIGH

///MCA27_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 27.
typedef enum {
  IDSOPT_DBG_CPU_MCA27_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA27_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA27_CTL_MASK_CTRL;

///MCA27_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 27.
#define IDSOPT_DBG_CPU_MCA27_CTL_MASK_LOW_MIN 0 ///< Min of MCA27_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA27_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA27_CTL_MASK_LOW

///MCA27_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 27.
#define IDSOPT_DBG_CPU_MCA27_CTL_MASK_HIGH_MIN 0 ///< Min of MCA27_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA27_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA27_CTL_MASK_HIGH

///Memory Holes at 2G and 5G (512MB)
///Allocate 512MB memory holes at 2G and 5G
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G;

///SMM handler size per thread
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_FOR_SMM_PER_THREAD_MIN 0 ///< Min of SMM handler size per thread
#define IDSOPT_DBG_CPU_MEM_HOLE_FOR_SMM_PER_THREAD_MAX 4294967295 ///< Max of SMM handler size per thread

///Memory Hole on Socket 0
///in MB. This hole should be in local memory.
#define IDSOPT_DBG_CPU_MEM_HOLE_SKT0_MIN 0 ///< Min of Memory Hole on Socket 0
#define IDSOPT_DBG_CPU_MEM_HOLE_SKT0_MAX 4294967295 ///< Max of Memory Hole on Socket 0

///Memory Hole on Socket 1
///in MB. This hole should be in local memory.
#define IDSOPT_DBG_CPU_MEM_HOLE_SKT1_MIN 0 ///< Min of Memory Hole on Socket 1
#define IDSOPT_DBG_CPU_MEM_HOLE_SKT1_MAX 4294967295 ///< Max of Memory Hole on Socket 1

///BTHB Core 0 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0;

///BTHB Core 1 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_8MB = 4,///< 8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1;

///BTHB Core 2 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_8MB = 4,///< 8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2;

///BTHB Core 3 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3;

///BTHB Core 4 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4;

///BTHB Core 5 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5;

///BTHB Core 6 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6;

///BTHB Core 7 Hole Size
///in MB. Try to assign local memory first, if can't, use memory on other socket
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7;

///Medium grain clock gating
///Controls the MGCG feature.
typedef enum {
  IDSOPT_DF_DBG_MGCG_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLEDNOHYST = 1,///<Enabled - no hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED1FCLKHYST = 2,///<Enabled - 1FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED2FCLKHYST = 3,///<Enabled - 2FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED3FCLKHYST = 4,///<Enabled - 3FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED4FCLKHYST = 5,///<Enabled - 4FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED5FCLKHYST = 6,///<Enabled - 5FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED6FCLKHYST = 7,///<Enabled - 6FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED7FCLKHYST = 8,///<Enabled - 7FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED8FLCKHYST = 9,///<Enabled - 8FLCK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED9FCLKHYST = 10,///<Enabled - 9FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED10FCLKHYST = 11,///<Enabled - 10FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED11FCLKHYST = 12,///<Enabled - 11FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED15FCLKHYST = 13,///<Enabled - 15FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED31FCLKHYST = 14,///<Enabled - 31FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED63FCLKHYST = 15,///<Enabled - 63FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_AUTO = 31,///<Auto
} IDSOPT_DF_DBG_MGCG_CTRL;

///DF Watchdog Timer Control
///Controls DF watchdog timers (DF::DfGlobalCtrl[WDTBaseSel])
typedef enum {
  IDSOPT_DF_DBG_WDT_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_WDT_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_WDT_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_WDT_CTRL;

///Mask DF WDT errors from causing MCA
///This keeps the WDT enabled and will show up in scans, but won't let them cause a MCA.\n\nAUTO/Disabled (unmasked) doesn't touch the HWA errors.\nEnabled (masked) will set the following bits:\n  - DF::HardwareAssertMaskLow[4] in all CCM instances\n  - DF::HardwareAssertMaskLow[5] in all CCM instances\n  - DF::HardwareAssertMaskHigh[3] in all IOM instances
typedef enum {
  IDSOPT_DF_DBG_MASK_WDT_FROM_CAUSING_MCA_ENABLED = 0,///<Enabled
  IDSOPT_DF_DBG_MASK_WDT_FROM_CAUSING_MCA_DISABLED = 1,///<Disabled
  IDSOPT_DF_DBG_MASK_WDT_FROM_CAUSING_MCA_AUTO = 0xF,///<Auto
} IDSOPT_DF_DBG_MASK_WDT_FROM_CAUSING_MCA;

///Core master request ordering
///Can be used to force TgtStart/TgtDone ordering on all ReqBlockLevel 2 read or write sized requests.
typedef enum {
  IDSOPT_DF_DBG_CORE_MSTR_REQ_ORDERING_ALWAYSORDERED = 0,///<Always Ordered
  IDSOPT_DF_DBG_CORE_MSTR_REQ_ORDERING_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CORE_MSTR_REQ_ORDERING;

///Disable MemCancel
///Controls DF::CCMConfig1[DisAllMemCancel]
typedef enum {
  IDSOPT_DF_DBG_MEM_CANCEL_DIS_FORCEOFF = 0,///<Force off
  IDSOPT_DF_DBG_MEM_CANCEL_DIS_FORCEON = 1,///<Force on
  IDSOPT_DF_DBG_MEM_CANCEL_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_MEM_CANCEL_DIS;

///CCM LL thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LLElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LL_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LL_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LL_THRESH_CTRL;

///CCM LL thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LLElvPriReqThr]
#define IDSOPT_DF_DBG_CCM_LL_THRESH_MIN 0 ///< Min of CCM LL thresh
#define IDSOPT_DF_DBG_CCM_LL_THRESH_MAX 0xf ///< Max of CCM LL thresh

///CCM LL cumulative thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LLCumElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_CTRL;

///CCM LL cumulative thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LLCumElvPriReqThr].
#define IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_MIN 0 ///< Min of CCM LL cumulative thresh
#define IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_MAX 0x1f ///< Max of CCM LL cumulative thresh

///CCM LP thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LPElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LP_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LP_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LP_THRESH_CTRL;

///CCM LP thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LPElvPriReqThr]
#define IDSOPT_DF_DBG_CCM_LP_THRESH_MIN 0 ///< Min of CCM LP thresh
#define IDSOPT_DF_DBG_CCM_LP_THRESH_MAX 0x7 ///< Max of CCM LP thresh

///CCM LP cumulative thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LPCumElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_CTRL;

///CCM LP cumulative thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LPCumElvPriReqThr].
#define IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_MIN 0 ///< Min of CCM LP cumulative thresh
#define IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_MAX 0x1f ///< Max of CCM LP cumulative thresh

///CCM bypass control
///Controls DF::CCMConfig[DisPrbReqByp, DisPrbRspByp, DisCcmReqQByp, DisCcmRspDQByp, DisCcmRspDataByp]
typedef enum {
  IDSOPT_DF_DBG_CCM_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CCM_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CCM_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CCM_BYPASS_CTRL;

///I/O master request ordering
///Can be used to disable the Target Start shortcut.
typedef enum {
  IDSOPT_DF_DBG_IO_MSTR_REQ_ORDERING_ALWAYSORDERED = 0,///<Always Ordered
  IDSOPT_DF_DBG_IO_MSTR_REQ_ORDERING_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_IO_MSTR_REQ_ORDERING;

///I/O request bus lock control
///Can be used to force bus locks on all IO non-posted requests, not just atomics (DF::IOMConfig[EnReqBusLock])
typedef enum {
  IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL;

///IOM PerfMon Ctrl - PrbRsp
///Controls DF:IOMConfig[LatMonFtiPrbRsp]
typedef enum {
  IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP_TGTDONE = 0,///<TgtDone
  IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP_PRBRSP = 1,///<PrbRsp
  IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP;

///IOM PerfMon Ctrl - TgtSel
///Controls DF:IOMConfig[LatMonTgtSel]
typedef enum {
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_DRAM = 0,///<DRAM
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_IO = 1,///<I/O
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_INTERRUPTS = 2,///<Interrupts
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_SYSMGMT = 3,///<Sys mgmt
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_FENCE = 4,///<Fence
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_FLUSH = 5,///<Flush
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_IOSRSP = 6,///<IOS rsp
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_OTHERS = 7,///<Others
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_AUTO = 15,///<Auto
} IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL;

///Limit maximum I/O requests
///Limit the number of non-posted I/O requests from masters.  Select the master to limit.
typedef enum {
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_IOM = 0,///<IOM
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_CCM = 1,///<CCM
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_BOTH = 2,///<Both
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER;

///Max I/O request limit
///Specify the number of non-posted I/O requests from the masters specified above.  The value specified will be applied directly to DF::MasterRequestControl[MstIoNpActReqLmt].  Note that '0' means that no limit is imposed.
#define IDSOPT_DF_DBG_LMT_MAX_IO_REQ_LIMIT_MIN 0 ///< Min of Max I/O request limit
#define IDSOPT_DF_DBG_LMT_MAX_IO_REQ_LIMIT_MAX 0x3f ///< Max of Max I/O request limit

///IOS resp bypass control
///Controls DF::IOMConfig[DisIosRspBypass]
typedef enum {
  IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL;

///Disable migratory probes
///Controls DF::CoherentSlaveConfigA1[DisPrbMig]
typedef enum {
  IDSOPT_DF_DBG_MIG_PRB_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_MIG_PRB_DIS_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_MIG_PRB_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_MIG_PRB_DIS;

///Stop on SPF error detect
///Controls DF::SpfModeControl0[StopOnProtErrDet]
typedef enum {
  IDSOPT_DF_DBG_STOP_ON_SPF_ERROR_STOP = 0,///<Stop
  IDSOPT_DF_DBG_STOP_ON_SPF_ERROR_CONTINUE = 1,///<Continue
  IDSOPT_DF_DBG_STOP_ON_SPF_ERROR_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_STOP_ON_SPF_ERROR;

///SPF ways control
typedef enum {
  IDSOPT_DF_DBG_SPF_WAY_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_SPF_WAY_CTRL_AUTO = 0xF,///<Auto
} IDSOPT_DF_DBG_SPF_WAY_CTRL;

///Disable SPF ways
///SPF is comprised of LPF and PPF, each with 16 ways. These ways should be disabled/enabled by choosing the bits as below;\nBits[31:16][LPFWayDis]\nBits[15:0][PPFWayDis]\n\nEg. say we want to disable LPF ways 5,11\nD18F2x208 [SPF Way Disable] = 0000_1000_0010_0000_0000_0000_0000_0000  = 0x08200000\n\nEg. say we want to disable PPF ways 3,10\nD18F2x208 [SPF Way Disable] = 0000_0000_0000_0000_0000_0100_0000_1000  = 0x00000408\n\nEg. say we want to disable LPF ways 5,11 and PPF ways 3,10\nD18F2x208 [SPF Way Disable] = 0000_1000_0020_0000_0000_0100_0000_1000  = 0x82000408\n
#define IDSOPT_DF_DBG_SPF_WAY_DIS_MIN 0 ///< Min of Disable SPF ways
#define IDSOPT_DF_DBG_SPF_WAY_DIS_MAX 0xffffffff ///< Max of Disable SPF ways

///CS bypass control
///Controls DF::CoherentSlaveConfigA1[DisRspByp, DisReqByp]
typedef enum {
  IDSOPT_DF_DBG_CS_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CS_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CS_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CS_BYPASS_CTRL;

///TgtStart control
///Controls whether or not the coherent slave sends a TgtStart packet (DF::CoherentSlaveConfigA1[DisTgtStrt])
typedef enum {
  IDSOPT_DF_DBG_TGT_START_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_TGT_START_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_TGT_START_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_TGT_START_CTRL;

///CPU Masters receive probe responses
typedef enum {
  IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP_ENABLE = 1,///<Enable
  IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP;

///I/O Masters receive probe responses
typedef enum {
  IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP_ENABLE = 1,///<Enable
  IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP;

///Disable TCDX bypasses
///Controls TCDX bypasses DF::TCDXConfig[BypassEnable]\nDisabled - D18F7x11C=0\nEnabled - D18F7x11C=reset value
typedef enum {
  IDSOPT_DF_DBG_TCDX_BYPASS_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_TCDX_BYPASS_DIS_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_TCDX_BYPASS_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_TCDX_BYPASS_DIS;

///Reduce credits - request
///Reduce request credits
typedef enum {
  IDSOPT_DF_DBG_REDUCE_CREDITS_REQ_REDUCECREDITS = 0,///<Reduce credits
  IDSOPT_DF_DBG_REDUCE_CREDITS_REQ_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_REDUCE_CREDITS_REQ;

///Reduce credits - probe
///Reduce probe credits
typedef enum {
  IDSOPT_DF_DBG_REDUCE_CREDITS_PRB_REDUCECREDITS = 0,///<Reduce credits
  IDSOPT_DF_DBG_REDUCE_CREDITS_PRB_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_REDUCE_CREDITS_PRB;

///Reduce credits - response
///Reduce response credits
typedef enum {
  IDSOPT_DF_DBG_REDUCE_CREDITS_RSP_REDUCECREDITS = 0,///<Reduce credits
  IDSOPT_DF_DBG_REDUCE_CREDITS_RSP_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_REDUCE_CREDITS_RSP;

///CAKE req & addr compression
///Controls request / address compression on links (DF::CakeCompCntlReq[CntlRdBlkEn,CntlRdSzFEn,CntlRdSzHEn,CntlWrSzFEn,CntlWrSzHEn])
typedef enum {
  IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION;

///CAKE data compression
///Controls data compression on links (DF::CakeCompCntlReq[CntlDatCompPatEn])
typedef enum {
  IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION;

///CAKE IO addr compression bit
///Controls which address bit is used for I/O compression index (DF::CakeCompCntlReq[CntlCompZIomAddrBit])
typedef enum {
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT20 = 0,///<Bit 20
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT21 = 1,///<Bit 21
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT22 = 2,///<Bit 22
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT23 = 3,///<Bit 23
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_AUTO = 7,///<Auto
} IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT;

///CAKE resp command packing
///Controls response command packing on links (DF::CakeCntlRsp[CntlSrcDnEn,CntlTgtStEn,CntlTgtDnDEn,CntlTgtDnEn,CntlTknEn])
typedef enum {
  IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING;

///CAKE probe combining
///Controls probe combining on links (DF::CakePrbCmbCntl[CntlPrbCmbSrcDis, CntlPrbCmbTgtDis])
typedef enum {
  IDSOPT_DF_DBG_CAKE_PRB_COMBINING_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_PRB_COMBINING_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_PRB_COMBINING_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_PRB_COMBINING;

///CAKE token thresholding
///Control CAKE token thresholding on ZP-Bx
typedef enum {
  IDSOPT_DF_DBG_CAKE_TKN_THRESH_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_TKN_THRESH_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_TKN_THRESH_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_TKN_THRESH;

///Optimize Cake data latency
///Enable disable CAKE data latency optimization on ZP-Bx
typedef enum {
  IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT;

///CAKE bypass control
///Controls DF::CakeSysConfig[FtiToGmiDatBypEn, GmiToFtiGmiDatBypEn]
typedef enum {
  IDSOPT_DF_DBG_CAKE_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_BYPASS_CTRL;

///PIE PRQ broadcast limit
///Controls DF::PIEConfig[PrqBcstWRspLmt]
typedef enum {
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_NOLIMIT = 0,///<No limit
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_1 = 1,///<1
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_2 = 2,///<2
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_3 = 3,///<3
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_4 = 4,///<4
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_5 = 5,///<5
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_6 = 6,///<6
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_7 = 7,///<7
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_AUTO = 15,///<Auto
} IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT;

///Disable I/O bus lock involvement
///Controls whether IOM participates (is locked by) bus locks (DF::PIEConfig[DisIOMLock])
typedef enum {
  IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS;

///DF picker load step control
///Controls DF::PwrMgtCfg0[PickLoadStepCstateEn]
typedef enum {
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL;

///NVDIMM indicator to DF
///Controls DF::PstateS3Control [NvdimmSelfRefrEn]
typedef enum {
  IDSOPT_DF_DBG_NVDIMM_PRESENT_NVDIMMSPRESENT = 1,///<NVDIMMs present
  IDSOPT_DF_DBG_NVDIMM_PRESENT_NVDIMMSNOTPRESENT = 0,///<NVDIMMs not present
  IDSOPT_DF_DBG_NVDIMM_PRESENT_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_NVDIMM_PRESENT;

///DF Pstate change quiesce ctrl
///Controls DF::PstateS3Control[DfPstateChgDisableQuiesce]
typedef enum {
  IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL_DISABLED = 1,///<Disabled
  IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL_ENABLED = 0,///<Enabled
  IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL;

///Load step hysteresis control
///Set F5x358 Load Step Hysteresis Control
typedef enum {
  IDSOPT_DF_DBG_LOAD_STEP_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_LOAD_STEP_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_LOAD_STEP_CTRL;

///Load step hysteresis value
///Set F5x358 Load Step Hysteresis Control
#define IDSOPT_DF_DBG_LOAD_STEP_VALUE_MIN 0 ///< Min of Load step hysteresis value
#define IDSOPT_DF_DBG_LOAD_STEP_VALUE_MAX 0xFFFFFFFF ///< Max of Load step hysteresis value

///xGMI Link Configuration
///Configures the number of xGMI2 links used on a multi-socket system.
typedef enum {
  IDSOPT_DF_DBG_XGMI_LINK_CFG_AUTO = 3,///<Auto
  IDSOPT_DF_DBG_XGMI_LINK_CFG_3XGMILINKS = 1,///<3 xGMI Links
  IDSOPT_DF_DBG_XGMI_LINK_CFG_4XGMILINKS = 2,///<4 xGMI Links
} IDSOPT_DF_DBG_XGMI_LINK_CFG;

///GMI / xGMI link error injection
///Inject GMI / xGMI link errors periodically.  Check the hardware config for which options are valid.  In the single link options, 'S' is socket and 'D' is internal die.
typedef enum {
  IDSOPT_DF_DBG_LINK_ERR_INJ_ALLGMILINKS = 0,///<All GMI links
  IDSOPT_DF_DBG_LINK_ERR_INJ_ALLXGMILINKS = 1,///<All xGMI links
  IDSOPT_DF_DBG_LINK_ERR_INJ_ALLLINKSGMIXGMI = 2,///<All links (GMI + xGMI)
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0D1 = 3,///<S0: D0-D1
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0D2 = 4,///<S0: D0-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0D3 = 5,///<S0: D0-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D1D2 = 6,///<S0: D1-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D1D3 = 7,///<S0: D1-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D2D3 = 8,///<S0: D2-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D0D1 = 9,///<S1: D0-D1
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D0D2 = 10,///<S1: D0-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D0D3 = 11,///<S1: D0-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D1D2 = 12,///<S1: D1-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D1D3 = 13,///<S1: D1-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D2D3 = 14,///<S1: D2-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0XGMI = 15,///<S0: D0 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D1XGMI = 16,///<S0: D1 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D2XGMI = 17,///<S0: D2 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D3XGMI = 18,///<S0: D3 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_AUTO = 31,///<Auto
} IDSOPT_DF_DBG_LINK_ERR_INJ;

///Allocate tokens for VC8 tracing
///Allocates tokens for VC8 tracing
typedef enum {
  IDSOPT_DF_DBG_VC8_TRACING_TOK_ALLOC_ALLOCATE = 0,///<Allocate
  IDSOPT_DF_DBG_VC8_TRACING_TOK_ALLOC_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_VC8_TRACING_TOK_ALLOC;

///REQ_CS
///Number of request credits to allocate in TCDX for CS tracing.  REQ_CS and REQ_IOMS should be a max of 3 if CS && IOMS tracing is on, else max of 5
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_CS_MIN 0 ///< Min of REQ_CS
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_CS_MAX 5 ///< Max of REQ_CS

///REQ_IOMS
///Number of request credits to allocate in TCDX for IOMS tracing.  REQ_CS and REQ_IOMS should be a max of 3 if CS && IOMS tracing is on, else max of 5
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_IOMS_MIN 0 ///< Min of REQ_IOMS
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_IOMS_MAX 5 ///< Max of REQ_IOMS

///CSQ
///Number of CSQ entries to allocate.  Must not be 0 if either REQ_CS > 0 || REQ_IOMS > 0
#define IDSOPT_DF_DBG_VC8_TRACING_CSQ_MIN 0 ///< Min of CSQ
#define IDSOPT_DF_DBG_VC8_TRACING_CSQ_MAX 32 ///< Max of CSQ

///RSP_IOMS
///Number of response credits to allocate in IOMS for responses.  Must not be 0 if REQ_IOMS > 0
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_IOMS_MIN 0 ///< Min of RSP_IOMS
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_IOMS_MAX 5 ///< Max of RSP_IOMS

///RSP_TCDX
///Number of response credits to allocate in TCDX for responses.  Must not be 0 if either REQ_CS > 0 || REQ_IOMS > 0
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_TCDX_MIN 0 ///< Min of RSP_TCDX
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_TCDX_MAX 5 ///< Max of RSP_TCDX

///DBGU_DF trace to DRAM
///Control DBGU DF tracing to DRAM. Use local memory first. if no local memory, use remote memory
typedef enum {
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM;

///DF TCB IOMS0 trace to DRAM
///Control DF TCB IOMS trace to DRAM. Use local memory first. if no local memory, use remote memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOMS0_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOMS0_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS0_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS0_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOMS0_TRC_TO_DRAM;

///DF TCB IOMS1 trace to DRAM
///Control DF TCB IOMS trace to DRAM. Use local memory first. if no local memory, use remote memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOMS1_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOMS1_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS1_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS1_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOMS1_TRC_TO_DRAM;

///DF TCB IOMS2 trace to DRAM
///Control DF TCB IOMS trace to DRAM. Use local memory first. if no local memory, use remote memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOMS2_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOMS2_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS2_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS2_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOMS2_TRC_TO_DRAM;

///DF TCB IOMS3 trace to DRAM
///Control DF TCB IOMS trace to DRAM. Use local memory first. if no local memory, use remote memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOMS3_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOMS3_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS3_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS3_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOMS3_TRC_TO_DRAM;

///DF TCB CS UMC0 trace to DRAM
///Control DF TCB CS UMC0 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC0_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC0_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC0_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC0_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC0_TRC_TO_DRAM;

///DF TCB CS UMC1 trace to DRAM
///Control DF TCB CS UMC1 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC1_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC1_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC1_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC1_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC1_TRC_TO_DRAM;

///DF TCB CS UMC2 trace to DRAM
///Control DF TCB CS UMC2 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC2_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC2_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC2_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC2_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC2_TRC_TO_DRAM;

///DF TCB CS UMC3 trace to DRAM
///Control DF TCB CS UMC3 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC3_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC3_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC3_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC3_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC3_TRC_TO_DRAM;

///DF TCB CS UMC4 trace to DRAM
///Control DF TCB CS UMC4 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC4_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC4_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC4_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC4_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC4_TRC_TO_DRAM;

///DF TCB CS UMC5 trace to DRAM
///Control DF TCB CS UMC5 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC5_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC5_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC5_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC5_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC5_TRC_TO_DRAM;

///DF TCB CS UMC6 trace to DRAM
///Control DF TCB CS UMC6 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC6_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC6_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC6_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC6_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC6_TRC_TO_DRAM;

///DF TCB CS UMC7 trace to DRAM
///Control DF TCB CS UMC7 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_UMC7_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_UMC7_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC7_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_UMC7_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_UMC7_TRC_TO_DRAM;

///DF TCB CS CCIX0 trace to DRAM
///Control DF TCB CS CCIX0 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX0_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX0_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX0_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX0_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_CCIX0_TRC_TO_DRAM;

///DF TCB CS CCIX1 trace to DRAM
///Control DF TCB CS CCIX1 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX1_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX1_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX1_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX1_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_CCIX1_TRC_TO_DRAM;

///DF TCB CS CCIX2 trace to DRAM
///Control DF TCB CS CCIX2 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX2_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX2_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX2_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX2_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_CCIX2_TRC_TO_DRAM;

///DF TCB CS CCIX3 trace to DRAM
///Control DF TCB CS CCIX3 trace to DRAM. Must be in local memory
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX3_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX3_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX3_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_CS_CCIX3_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_CS_CCIX3_TRC_TO_DRAM;

///Clean Victim vs Probe Interlock Control
///For Rev Ax, Auto == Method 1. Otherwise, Auto == Method 2.\nMethod 1\nF2x224[30] = 0; F3x10C[21] = 1; F3x10C[25:24] = 0\nMethod 2\nF2x224[30] = 1; F3x10C[21] = 0; F3x10C[25:24] = 2
typedef enum {
  IDSOPT_DF_DBG_CLN_VIC_PRB_INTERLOCK_CTRL_AUTO = 0xFF,///<Auto
  IDSOPT_DF_DBG_CLN_VIC_PRB_INTERLOCK_CTRL_METHOD1 = 0,///<Method 1
  IDSOPT_DF_DBG_CLN_VIC_PRB_INTERLOCK_CTRL_METHOD2 = 1,///<Method 2
} IDSOPT_DF_DBG_CLN_VIC_PRB_INTERLOCK_CTRL;

///Enforce supported frequency
///If this option is disable, and the target board does not support a certain VDDIO, then picking up a specific VDDIO through the CMOS option menu is required.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4;

///DRAM Timing User Controls
///DRAM Timing User Controls
typedef enum {
  IDSOPT_DBG_MEM_TIMING_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_CTL_DDR4;

///UclkDiv1M0
///UclkDiv1 option, relative to FCLK.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4;

///UclkDiv1M1
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4;

///UclkDiv1M2
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4;

///UclkDiv1M3
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4;

///Trtp
///Specifies the read CAS# to precharge time.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_5CLK = 0x5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_6CLK = 0x6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_7CLK = 0x7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_DBG_MEM_TIMING_TRTP_DDR4;

///TrrdL
///Specify the row-to-row delay.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4;

///TrrdS
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_0CHCLK = 0xC,///<0Ch Clk
} IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4;

///Trc Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRC_CTL_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRC_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TRC_CTL_DDR4;

///Trc
///Specify the RAS# active to RAS# active time.
#define IDSOPT_DBG_MEM_TIMING_TRC_DDR4_MIN 29 ///< Min of Trc
#define IDSOPT_DBG_MEM_TIMING_TRC_DDR4_MAX 135 ///< Max of Trc

///Trdwr
///This sets the tWRTTO time.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1DHCLK = 0x1D,///<1Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1EHCLK = 0x1E,///<1Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1FHCLK = 0x1F,///<1Fh Clk
} IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4;

///Twrrd
///Specify the write to read delay when accessing different DIMMs.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0CH = 0xC,///<0Ch
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0DH = 0xD,///<0Dh
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0EH = 0xE,///<0Eh
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0FH = 0xF,///<0Fh
} IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4;

///TwtrL
///Specify the write to read delay when accessing the same DIMM.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_2CLK = 2,///<2 Clk
} IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4;

///TwtrS
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4;

///Tcwl
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_16HCLK = 0x16,///<16h Clk
} IDSOPT_DBG_MEM_TIMING_TCWL_DDR4;

///TwrwrSc
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4;

///TwrwrSd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4;

///TwrwrDd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4;

///TrdrdSc
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4;

///TrdrdSd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4;

///TrdrdDd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4;

///Tref Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TREF_CTL_DDR4_MANUAL = 0x1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TREF_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TREF_CTL_DDR4;

///Tref
///Specify the tRef time.
#define IDSOPT_DBG_MEM_TIMING_TREF_DDR4_MIN 0 ///< Min of Tref
#define IDSOPT_DBG_MEM_TIMING_TREF_DDR4_MAX 0xffff ///< Max of Tref

///TrwtWB
///Specify the Trwtwb time.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4;

///Trfc0 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRFC0_CTL_DDR4_MANUAL = 0x1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TRFC0_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRFC0_CTL_DDR4;

///Trfc0
///Specify the Trfcx time. D18F2x2A0_[10:0]
#define IDSOPT_DBG_MEM_TIMING_TRFC0_DDR4_MIN 0x1 ///< Min of Trfc0
#define IDSOPT_DBG_MEM_TIMING_TRFC0_DDR4_MAX 0x7ff ///< Max of Trfc0

///Trfc1 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRFC1_CTL_DDR4_MANUAL = 0x1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TRFC1_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRFC1_CTL_DDR4;

///Trfc1
///Specify the Trfcx time. D18F2x2A0_[26:16]
#define IDSOPT_DBG_MEM_TIMING_TRFC1_DDR4_MIN 0x1 ///< Min of Trfc1
#define IDSOPT_DBG_MEM_TIMING_TRFC1_DDR4_MAX 0x7ff ///< Max of Trfc1

///Tcksrx Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TCKSRX_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TCKSRX_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TCKSRX_CTL_DDR4;

///Tcksrx
#define IDSOPT_DBG_MEM_TIMING_TCKSRX_DDR4_MIN 0 ///< Min of Tcksrx
#define IDSOPT_DBG_MEM_TIMING_TCKSRX_DDR4_MAX 0x3fff ///< Max of Tcksrx

///Tcksre Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TCKSRE_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TCKSRE_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TCKSRE_CTL_DDR4;

///Tcksre
#define IDSOPT_DBG_MEM_TIMING_TCKSRE_DDR4_MIN 0 ///< Min of Tcksre
#define IDSOPT_DBG_MEM_TIMING_TCKSRE_DDR4_MAX 0xff ///< Max of Tcksre

///Tpd Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TPD_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TPD_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TPD_CTL_DDR4;

///Tpd
#define IDSOPT_DBG_MEM_TIMING_TPD_DDR4_MIN 0x1 ///< Min of Tpd
#define IDSOPT_DBG_MEM_TIMING_TPD_DDR4_MAX 0xf ///< Max of Tpd

///Trddata_en Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDDATAEN_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDDATAEN_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TRDDATAEN_CTL_DDR4;

///Trddata_en
#define IDSOPT_DBG_MEM_TIMING_TRDDATAEN_DDR4_MIN 0 ///< Min of Trddata_en
#define IDSOPT_DBG_MEM_TIMING_TRDDATAEN_DDR4_MAX 0x7f ///< Max of Trddata_en

///Tphy_wrlat Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_CTL_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_CTL_DDR4;

///Tphy_wrlat
#define IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_DDR4_MIN 0 ///< Min of Tphy_wrlat
#define IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_DDR4_MAX 0x1f ///< Max of Tphy_wrlat

///Tphy_wrdata Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_CTL_DDR4;

///Tphy_wrdata
#define IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_DDR4_MIN 0 ///< Min of Tphy_wrdata
#define IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_DDR4_MAX 0x7 ///< Max of Tphy_wrdata

///WrOdtOnDur
typedef enum {
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4;

///WrOdtTrnOnDly
typedef enum {
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_1 = 1,///<1
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_2 = 2,///<2
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4;

///RdOdtOnDur
typedef enum {
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4;

///RdOdtTrnOnDly
typedef enum {
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_1 = 1,///<1
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_2 = 2,///<2
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4;

///POdtStartDelayDqs Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_CTL_DDR4;

///POdtStartDelayDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_DDR4_MIN 0 ///< Min of POdtStartDelayDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_DDR4_MAX 3 ///< Max of POdtStartDelayDqs

///POdtStartDelayDq Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_CTL_DDR4;

///POdtStartDelayDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_DDR4_MIN 0 ///< Min of POdtStartDelayDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_DDR4_MAX 0xf ///< Max of POdtStartDelayDq

///POdtTailWidthDqs Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_CTL_DDR4;

///POdtTailWidthDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_DDR4_MIN 0 ///< Min of POdtTailWidthDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_DDR4_MAX 3 ///< Max of POdtTailWidthDqs

///POdtTailWidthDq Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_CTL_DDR4;

///POdtTailWidthDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_DDR4_MIN 0 ///< Min of POdtTailWidthDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_DDR4_MAX 0xf ///< Max of POdtTailWidthDq

///Address Command Tristate Enable
///1=Tristate the address, command, and bank buses when a Deselect command is issued.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4_DISABLED = 1,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4;

///Cmd2T
///Select between 1T and 2T mode on ADDR/CMD
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4_1T = 0,///<1T
  IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4_2T = 1,///<2T
  IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4;

///On DIMM Temperature Sensor Enable
///Enables the monitoring of the EVENT_L pin and indicates whether the on DIMM temperature sensors of the DIMMs on a channel are enabled.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4;

///CmdThrottleMode Control
///Control command throttle mode.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4;

///CmdThrottleMode
///Control command throttle mode.
#define IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_DDR4_MIN 8 ///< Min of CmdThrottleMode
#define IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_DDR4_MAX 255 ///< Max of CmdThrottleMode

///Gear Down Mode
typedef enum {
  IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4;

///DRAM Hardware History Mechanism
///Disable DRAM Hardware History Mechanism: UMC_CH::EccCtrl[EccHardwareHistoryEn]. Default should be to set this to 1 if EccCtrl[EccSymbolSize]==x8
typedef enum {
  IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4_DISABLE = 16,///<Disable
  IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4;

///DRAM Parity
typedef enum {
  IDSOPT_DBG_MEM_DRAM_PARITY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DRAM_PARITY_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_DRAM_PARITY_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_DRAM_PARITY_DDR4;

///DBI
typedef enum {
  IDSOPT_DBG_MEM_DBI_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DBI_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_DBI_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_DBI_DDR4;

///AddrTweakEn Control
/// SMNx00050144 [Data Control] (DataCtrl)31:16 AddrTweakEn. Read-write. Reset: 0. Per key field that controls if encryption algorithm uses the physical address or not. Simple AES versus AES+Locality
typedef enum {
  IDSOPT_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4;

///AddrTweakEn
#define IDSOPT_DBG_MEM_ADDR_TWEAK_EN_DDR4_MIN 0 ///< Min of AddrTweakEn
#define IDSOPT_DBG_MEM_ADDR_TWEAK_EN_DDR4_MAX 0xffff ///< Max of AddrTweakEn

///Data Encryption
///8 DataEncrEn. Read-write. Reset: 0. 0=Disable. 1=Enable. Enables data encryption. -  SMNx00050144 [Data Control] (DataCtrl) Bit 8
typedef enum {
  IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4;

///Force Encryption
/// SMNx00050144 [Data Control] (DataCtrl) Bit 11 11 ForceEncrEn. Read-write. Reset: 0. 0=Disable. 1=Enable. Force region 0 data encryption for all requests.
typedef enum {
  IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4;

///UMC Key 0
typedef enum {
  IDSOPT_DBG_MEM_UMC_KEY0_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_UMC_KEY0_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_UMC_KEY0_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_UMC_KEY0_DDR4;

///DRAM Fine Granularity Refresh
typedef enum {
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_FIXED1X = 0,///<Fixed 1X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_FIXED2X = 1,///<Fixed 2X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_FIXED4X = 2,///<Fixed 4X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_OTF2X = 5,///<OTF 2X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_OTF4X = 6,///<OTF 4X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4;

///DRAM Temperature Controlled Refresh Mode
typedef enum {
  IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4;

///Data Mask
typedef enum {
  IDSOPT_DBG_MEM_DATA_MASK_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DATA_MASK_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_DATA_MASK_DDR4_DISABLED = 0,///<Disabled`
} IDSOPT_DBG_MEM_DATA_MASK_DDR4;

///RdPreamble Critical Speed
typedef enum {
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_AUTO = 0xFFFF,///<Auto
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1600 = 800,///<DDR1600
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1866 = 933,///<DDR1866
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2133 = 1067,///<DDR2133
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2400 = 1200,///<DDR2400
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2667 = 1333,///<DDR2667
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2933 = 1467,///<DDR2933
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR3200 = 1600,///<DDR3200
} IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4;

///RdPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_RD_PREAMBLE_MSTATE_BITMAP_DDR4_MIN 0 ///< Min of RdPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_RD_PREAMBLE_MSTATE_BITMAP_DDR4_MAX 0xf ///< Max of RdPreamble M-state Bitmap

///WrPreamble Critical Speed
typedef enum {
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_AUTO = 0xFFFF,///<Auto
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1600 = 800,///<DDR1600
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1866 = 933,///<DDR1866
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2133 = 1067,///<DDR2133
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2400 = 1200,///<DDR2400
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2667 = 1333,///<DDR2667
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2933 = 1467,///<DDR2933
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR3200 = 1600,///<DDR3200
} IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4;

///WrPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_WR_PREAMBLE_MSTATE_BITMAP_DDR4_MIN 0 ///< Min of WrPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_WR_PREAMBLE_MSTATE_BITMAP_DDR4_MAX 0xf ///< Max of WrPreamble M-state Bitmap

///ProcOdtAlwaysOn
typedef enum {
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4_1 = 1,///<1
} IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4;

///ProcOdtAlwaysOff
typedef enum {
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4_1 = 1,///<1
} IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4;

///Early Page Activate
typedef enum {
  IDSOPT_DBG_MEM_EARLY_PAGE_ACTIVATE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_EARLY_PAGE_ACTIVATE_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_EARLY_PAGE_ACTIVATE_DDR4;

///Power Down Enable
///Enable or disable DDR power down mode, D18F2x94_dct[1:0][15]
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4;

///Power Down Mode
///Set the DDR power down mode
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4_CHANNEL = 0,///<Channel
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4_CHIPSELECT = 1,///<Chip Select
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4;

///Power Down Delay Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4;

///Power Down Delay
#define IDSOPT_DBG_MEM_CTRLLER_PD_DLY_DDR4_MIN 0 ///< Min of Power Down Delay
#define IDSOPT_DBG_MEM_CTRLLER_PD_DLY_DDR4_MAX 0xff ///< Max of Power Down Delay

///Aggressive Power Down Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4;

///Aggressive Power Down Delay Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4;

///Aggressive Power Down Delay
///Specifies a hysteresis count from the last DRAM activity for the DCT to close pages prior to precharge power down.
#define IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_DDR4_MIN 0x1 ///< Min of Aggressive Power Down Delay
#define IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_DDR4_MAX 0x3f ///< Max of Aggressive Power Down Delay

///Phy Power Saving
///Enable or disable DRAM Phy power savings.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4;

///Power Down Phy Power Save Disable
///1= Disable phy clock gating during precharge power down. 0=Enable phy clock gating during precharge power down to save power.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4_1 = 1,///<1
  IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4;

///All Memory Clks Enable
///This allows selection of all memory clocks enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4;

///All CKE Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4;

///All CS Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4;

///Inject TX Command Parity Errors
/// DF is requesting a UMC CBS option for injecting TX command parity errors as this will generate RETRANSMIT commands. The following webpage describes the recipe: http://twiki.amd.com/twiki/bin/view/DFArch/UmcRetransmitRecipe
typedef enum {
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4;

///Data Bus Configuration User Controls
///Specify the mode for drive strength to Auto or Manual
typedef enum {
  IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4;

///Data Drive Strength
///Specifies the Data Drive Strength
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_480OHM = 1,///<480 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_240OHM = 2,///<240 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_160OHM = 3,///<160 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_120OHM = 6,///<120 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_96OHM = 7,///<96 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_80OHM = 0xA,///<80 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_68OHM = 0xB,///<68 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_60OHM = 0xE,///<60 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_533OHM = 0xF,///<53.3 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_48OHM = 0x1A,///<48 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_436OHM = 0x1B,///<43.6 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_40OHM = 0x1E,///<40 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_369OHM = 0x1F,///<36.9 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_343OHM = 0x3A,///<34.3 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_32OHM = 0x3B,///<32 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_30OHM = 0x3E,///<30 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_282OHM = 0x3F,///<28.2 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_HIZ = 0,///<HiZ
} IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4;

///RttNom
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RTT_NOMDISABLE = 0,///<Rtt_Nom Disable
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ4 = 1,///<RZQ/4
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ2 = 2,///<RZQ/2
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ6 = 3,///<RZQ/6
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ1 = 4,///<RZQ/1
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ5 = 5,///<RZQ/5
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ3 = 6,///<RZQ/3
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ7 = 7,///<RZQ/7
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4;

///RttWr
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_DYNAMICODTOFF = 0,///<Dynamic ODT Off
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_RZQ2 = 1,///<RZQ/2
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_RZQ1 = 2,///<RZQ/1
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_HIZ = 3,///<Hi-Z
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_RZQ3 = 4,///<RZQ/3
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4;

///RttPark
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RTT_PARKDISABLE = 0,///<Rtt_PARK Disable
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ4 = 1,///<RZQ/4
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ2 = 2,///<RZQ/2
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ6 = 3,///<RZQ/6
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ1 = 4,///<RZQ/1
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ5 = 5,///<RZQ/5
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ3 = 6,///<RZQ/3
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ7 = 7,///<RZQ/7
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4;

///DRAM Output Driver Impedance
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4_RZQ7 = 0,///<RZQ/7
  IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4_RZQ5 = 1,///<RZQ/5
} IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4;

///ARdPtrInitValMP0 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4;

///ARdPtrInitValMP0
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_DDR4_MIN 0 ///< Min of ARdPtrInitValMP0
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_DDR4_MAX 15 ///< Max of ARdPtrInitValMP0

///ARdPtrInitValMP1 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4;

///ARdPtrInitValMP1
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_DDR4_MIN 0 ///< Min of ARdPtrInitValMP1
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_DDR4_MAX 127 ///< Max of ARdPtrInitValMP1

///DFI MRL Margin Control
typedef enum {
  IDSOPT_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4;

///DFI MRL Margin
#define IDSOPT_DBG_MEM_DFI_MRL_MARGIN_DDR4_MIN 0 ///< Min of DFI MRL Margin
#define IDSOPT_DBG_MEM_DFI_MRL_MARGIN_DDR4_MAX 31 ///< Max of DFI MRL Margin

///Per Rank Training
typedef enum {
  IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4;

///PMU Training Mode
///Use this option to select various PMU Training Mode. 1D Training is always performed for Reads and Writes. 2D may be performed for Reads, Writes or both.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DONLYTRAINING = 0,///<1D Only Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DAND2DREADTRAINING = 1,///<1D and 2D Read Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DAND2DWRITETRAINING = 2,///<1D and 2D Write Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DAND2DREADANDWRITETRAINING = 3,///<1D and 2D Read and Write Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4;

///MR6VrefDQ Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4;

///MR6VrefDQ
#define IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_DDR4_MIN 0 ///< Min of MR6VrefDQ
#define IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_DDR4_MAX 0x7f ///< Max of MR6VrefDQ

///DRAM Vref Range
typedef enum {
  IDSOPT_DBG_MEM_VREF_RANGE_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_VREF_RANGE_DDR4_RANGE1 = 1,///<Range 1
  IDSOPT_DBG_MEM_VREF_RANGE_DDR4_RANGE2 = 2,///<Range 2
} IDSOPT_DBG_MEM_VREF_RANGE_DDR4;

///DFE Read Training
///Perform 2D Read Training with DFE on.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4;

///FFE Write Training
///Perform 2D WriteTraining with FFE on.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4;

///RxEnDly Override Op
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_PLUS = 0,///<Plus
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_MINUS = 1,///<Minus
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_OVERRIDE = 2,///<Override
} IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP;

///RxEnDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_VALUE_MIN 0 ///< Min of RxEnDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_VALUE_MAX 0xffff ///< Max of RxEnDly Override Value

///Delay Weight2D Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_CTRL_DDR4;

///Delay Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_DDR4_MIN 0 ///< Min of Delay Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_DDR4_MAX 255 ///< Max of Delay Weight2D

///Voltage Weight2D Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_CTRL_DDR4;

///Voltage Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_DDR4_MIN 0 ///< Min of Voltage Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_DDR4_MAX 255 ///< Max of Voltage Weight2D

///Bits Per Point Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_CTRL_DDR4;

///Bits Per Point
#define IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_DDR4_MIN 0 ///< Min of Bits Per Point
#define IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_DDR4_MAX 255 ///< Max of Bits Per Point

///CPU Vref Training Seed Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4;

///CPU Vref Training Seed
#define IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_DDR4_MIN 0 ///< Min of CPU Vref Training Seed
#define IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_DDR4_MAX 0xff ///< Max of CPU Vref Training Seed

///Custom 1D Message Control 1
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1;

///1D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET1_MIN 0 ///< Min of 1D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET1_MAX 0xffff ///< Max of 1D Message Offset 1

///1D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA1_MIN 0 ///< Min of 1D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA1_MAX 0xff ///< Max of 1D Message Data 1

///Custom 1D Message Control 2
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2;

///1D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET2_MIN 0 ///< Min of 1D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET2_MAX 0xffff ///< Max of 1D Message Offset 2

///1D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA2_MIN 0 ///< Min of 1D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA2_MAX 0xff ///< Max of 1D Message Data 2

///Custom 2D message Control 1
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1;

///2D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET1_MIN 0 ///< Min of 2D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET1_MAX 0xffff ///< Max of 2D Message Offset 1

///2D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA1_MIN 0 ///< Min of 2D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA1_MAX 0xff ///< Max of 2D Message Data 1

///Custom 2D Message Control 2
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2;

///2D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET2_MIN 0 ///< Min of 2D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET2_MAX 0xffff ///< Max of 2D Message Offset 2

///2D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA2_MIN 0 ///< Min of 2D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA2_MAX 0xff ///< Max of 2D Message Data 2

///DBGU_NBIO Port 80 Tracing
///Control DBGU_NBIO Diagnostic Port 80 Write Tracing
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TRACING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TRACING_ENABLED = 1,///<Enabled
} IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TRACING;

///DBGU_NBIO Port 80 Destination
///Selects the destination for Port 80 tracing
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_DESTINATION_TRACETODRB = 0,///<Trace to DRB
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_DESTINATION_TRACETODRAM = 1,///<Trace to DRAM
} IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_DESTINATION;

///DBGU_NBIO Port 80 Timestamps
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP_ENABLED = 1,///<Enabled
} IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP;

///IVRS Options
///IVRS table
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IVRS_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_DBGU_IVRS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_IVRS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBGU_IVRS;

///USB MSI-X CAP
///enable/disable USB MSI-X CAP
typedef enum {
  IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN;

///SATA PHY Tuning
typedef enum {
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_NONE = 0,///<None
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_SHORTERTRACELENGTH = 1,///<Shorter Trace Length
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_LONGERTRACELENGTH = 2,///<Longer Trace Length
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING;

///DXIO PHY Programming
///Selects whether PHY programming runs from ROM or SRAM
typedef enum {
  IDSOPT_DBG_DXIO_PHY_PROGRAMMING_RUNFROMROM = 0,///<Run from ROM
  IDSOPT_DBG_DXIO_PHY_PROGRAMMING_RUNFROMSRAM = 1,///<Run from SRAM
} IDSOPT_DBG_DXIO_PHY_PROGRAMMING;

///Maximum Read Request size
///the maximum Read Request size for the Function as a Requester
typedef enum {
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_128BYTES = 0,///<128 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_256BYTES = 1,///<256 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_512BYTES = 2,///<512 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_1024BYTES = 3,///<1024 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_2048BYTES = 4,///<2048 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_4096BYTES = 5,///<4096 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE;

///LC_MULT_UPSTREAM_AUTO_SPD_CHNG_EN
///Defines the setting of this feature for all PCIe devices.  "Auto" uses the DXIO default setting of 0 for Gen1 and 1 for Gen2/3
typedef enum {
  IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO_DISABLED = 0,///<Disabled
  IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO_ENABLED = 1,///<Enabled
  IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO_AUTO = 0xF,///<Auto
} IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO;

///Report EDB Errors
///Defines the setting of this feature for all PCIe devices.
typedef enum {
  IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS;

///PCIe Topology Control
typedef enum {
  IDSOPT_PCIE_TOPOLOGY_CONTROL_AUTO = 0,///<Auto
  IDSOPT_PCIE_TOPOLOGY_CONTROL_MANUAL = 1,///<Manual
} IDSOPT_PCIE_TOPOLOGY_CONTROL;

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY0_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY0_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY0_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY0_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY0_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY0_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY0_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY0_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY0_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY0_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY0_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY0_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY0_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY0_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY0_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY0_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY1_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY1_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY1_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY1_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY1_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY1_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY1_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY1_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY1_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY1_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY1_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY1_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY1_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY1_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY1_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY1_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY2_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY2_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY2_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY2_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY2_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY2_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY2_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY2_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY2_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY2_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY2_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY2_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY2_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY2_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY2_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY2_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY3_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY3_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY3_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY3_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY3_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY3_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY3_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY3_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY3_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY3_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY3_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY3_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY3_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY3_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY3_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY3_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY4_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY4_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY4_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY4_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY4_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY4_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY4_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY4_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY4_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY4_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY4_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY4_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY4_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY4_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY4_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY4_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY5_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY5_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY5_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY5_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY5_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY5_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY5_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY5_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY5_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY5_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY5_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY5_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY5_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY5_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY5_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY5_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY6_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY6_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY6_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY6_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY6_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY6_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY6_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY6_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY6_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY6_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY6_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY6_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY6_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY6_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY6_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY6_SOCKET_MAX 1 ///< Max of Socket

///Engine Type
///The PCIe Engine Type.
typedef enum {
  IDSOPT_PC_IE_TOPOLOGY7_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_PC_IE_TOPOLOGY7_ENGINE_TYPE_PCIE = 1,///<PCIe
  IDSOPT_PC_IE_TOPOLOGY7_ENGINE_TYPE_SATA = 2,///<SATA
} IDSOPT_PC_IE_TOPOLOGY7_ENGINE_TYPE;

///Start Lane
///The Start Lane Number, must be less than the End Lane number.
#define IDSOPT_PC_IE_TOPOLOGY7_START_LANE_MIN 0 ///< Min of Start Lane
#define IDSOPT_PC_IE_TOPOLOGY7_START_LANE_MAX 129 ///< Max of Start Lane

///End Lane
///The End Lane Number, must be greater than the Start Lane number.
#define IDSOPT_PC_IE_TOPOLOGY7_END_LANE_MIN 0 ///< Min of End Lane
#define IDSOPT_PC_IE_TOPOLOGY7_END_LANE_MAX 129 ///< Max of End Lane

///Reset ID
///Reset ID associated with chosen group of ports.
#define IDSOPT_PC_IE_TOPOLOGY7_RESET_ID_MIN 0 ///< Min of Reset ID
#define IDSOPT_PC_IE_TOPOLOGY7_RESET_ID_MAX 0xff ///< Max of Reset ID

///Device
///PCIe device number.
#define IDSOPT_PC_IE_TOPOLOGY7_DEVICE_MIN 0 ///< Min of Device
#define IDSOPT_PC_IE_TOPOLOGY7_DEVICE_MAX 5 ///< Max of Device

///Function
///PCIe function number.
#define IDSOPT_PC_IE_TOPOLOGY7_FUNCTION_MIN 0 ///< Min of Function
#define IDSOPT_PC_IE_TOPOLOGY7_FUNCTION_MAX 7 ///< Max of Function

///Socket
#define IDSOPT_PC_IE_TOPOLOGY7_SOCKET_MIN 0 ///< Min of Socket
#define IDSOPT_PC_IE_TOPOLOGY7_SOCKET_MAX 1 ///< Max of Socket

///PCIe Port Settings
///These settings will be applied to all active PCIe ports unless overriden on a per port basis.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL;

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT_ALL_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT_ALL_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT_ALL_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT_ALL_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT_ALL_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT_ALL_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT_ALL_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT_ALL_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT_ALL_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT_ALL_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT_ALL_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT_ALL_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT_ALL_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_ALL_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN3_4SYM = 2,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_ALL_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN3_4SYM = 2,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL1_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN3_4SYM = 16,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL2_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN3_4SYM = 2,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL3_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN3_4SYM = 2,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL4_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN3_4SYM = 2,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL5_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN3_4SYM = 2,///<4 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL6_SPC_GEN3;

///PCIe Port Settings
///These settings will be applied to the specified PCIe Port if set to Enabled.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CUSTOM = 1,///<Custom
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Port Training
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TRAINING;

///Hotplug Support
///Set Hotplug
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_HOTPLUG;

///Speed Mode
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE_GEN4 = 4,///<GEN4
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPEED_MODE;

///Compliance Mode
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_COMPLIANCE_MODE;

///Link ASPM
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W
///Slot Power Limit in Watt
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W

///L1 Immediate ACK
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_L1_IMM_ACK;

///TX De-emphasis
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_DEEMPHASIS;

///TX Margin
///TX Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_TX_MARGIN;

///Scrambler control
///Scrambler control
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCRAMBLER_CNTL;

///Equalization Search Mode (Gen3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE;

///Equalization Search Mode (Gen4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GEN4_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GEN4_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GEN4_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_EQUAL_SEARCH_MODE_GEN4;

///Disable Gen3 EQ Phase2/3
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD;

///Disable Gen4 EQ Phase2/3
///Disable Gen4 EQ Phase2/3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_GEN4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_GEN4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_USC_EQ_NOT_REQD_GEN4;

///LC FOM TIME
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_LC_FOM_TIME;

///Port Reversal
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PORT_REVERSAL;

///Downstream Tx Preset (Gen3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET;

///Downstream Tx Preset (Gen4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_TX_PRESET_GEN4;

///Upstream Tx Preset (Gen3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET;

///Upstream Tx Preset (Gen4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P8 = 8,///<P8
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P9 = 9,///<P9
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_P10 = 0xA,///<P10
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_TX_PRESET_GEN4;

///Downstream Rx Preset Hint
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CFG_US_RX_HINT;

///Bypass Gen3 EQ
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN3_EQ;

///Bypass Gen4 EQ
///Bypass Gen4 EQ
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN4_EQ_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN4_EQ_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN4_EQ_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_BYPASS_GEN4_EQ;

///Enable 3x3 Search
///Enable 3x3 Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE3X3_SEARCH;

///Enable Safe Search
///Enable Safe Search
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_ENABLE_SAFE_SEARCH;

///SRIS_SRNS
///SRIS_SRNS
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_SRNS;

///SRIS_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_EN;

///SRIS_AUTODETECT_EN
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT
///SRIS_EN
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_MAX_PAYLOAD_SIZE;

///RX Timing Margin
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_RX_TIMING_MARGIN_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_RX_TIMING_MARGIN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_RX_TIMING_MARGIN_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_RX_TIMING_MARGIN;

///Data Link Feature Cap
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DATA_LINK_FEATURE_CAP_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DATA_LINK_FEATURE_CAP_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DATA_LINK_FEATURE_CAP_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_DATA_LINK_FEATURE_CAP;

///Scalable Flow Control
///Enabled forces Data Link Feature Cap to True
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCALABLE_FLOW_CONTROL_AUTO = 0,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCALABLE_FLOW_CONTROL_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCALABLE_FLOW_CONTROL_DISABLE = 2,///<Disable
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SCALABLE_FLOW_CONTROL;

///Flow Control Credits Control
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_NPH_CREDITS_MIN 0 ///< Min of NP-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR

///NP-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_NPD_CREDITS_MIN 0 ///< Min of NP-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA

///P-HDR
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PH_CREDITS_MIN 0 ///< Min of P-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PH_CREDITS_MAX 0xff ///< Max of P-HDR

///P-DATA
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PD_CREDITS_MIN 0 ///< Min of P-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_PD_CREDITS_MAX 0xff ///< Max of P-DATA

///CPL-HDR
///Completion Header Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR

///CPL-DATA
///Completion Data Flow Control Credits
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA
#define IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA

///Gen1
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN1;

///Gen2
///SPC
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN2;

///Gen3
typedef enum {
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN3_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN3_3SYM = 2,///<3 sym
} IDSOPT_DBG_NBIO_PCIE_PORT_SPECIAL7_SPC_GEN3;

///LCLK Gating(GFX)
///Enable LCLK clock gating
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING;

///Clock Gating (TxClk or RefClk branches)(GFX)
///Enable Clock gating (TXCLK, REFCLK)
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING;

///Master PLL Selection(GFX)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GFX_MASTER_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_MASTER_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_MASTER_PLL_CTL;

///MasterPLL
///MasterPLL
#define IDSOPT_DBG_GNB_GFX_MASTER_PLL_MIN 0 ///< Min of MasterPLL
#define IDSOPT_DBG_GNB_GFX_MASTER_PLL_MAX 0xff ///< Max of MasterPLL

///Force PLL PWR On when link in lower power mode(GFX)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GFX_FORCE_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_FORCE_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_FORCE_PLL_CTL;

///AllowPLLinPS4
///AllowPLLinPS4
typedef enum {
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4;

///AllowPLLabovePS4
///AllowPLLabovePS4
typedef enum {
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4;

///Force mplla on(GFX)
///Force mplla on
typedef enum {
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON;

///Force mpllb on(GFX)
///Force mpllb on
typedef enum {
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON;

///PCIe AtomicOps Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_GFX_ATOMIC_OPS;

///LCLK Gating(GPP)
///Enable LCLK clock gating
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING;

///Clock Gating (TxClk or RefClk branches)(GPP)
///Enable Clock gating (TXCLK, REFCLK)
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING;

///Master PLL Selection(GPP)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GPP_MASTER_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GPP_MASTER_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GPP_MASTER_PLL_CTL;

///MasterPLL
///MasterPLL
#define IDSOPT_DBG_GNB_GPP_MASTER_PLL_MIN 0 ///< Min of MasterPLL
#define IDSOPT_DBG_GNB_GPP_MASTER_PLL_MAX 0xff ///< Max of MasterPLL

///Force PLL PWR On when link in lower power mode(GPP)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GPP_FORCE_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GPP_FORCE_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GPP_FORCE_PLL_CTL;

///AllowPLLinPS4
///AllowPLLinPS4
typedef enum {
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4;

///AllowPLLabovePS4
///AllowPLLabovePS4
typedef enum {
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4;

///Force mplla on(GPP)
///Force mplla on
typedef enum {
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON;

///Force mpllb on(GPP)
///Force mpllb on
typedef enum {
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON;

///PCIe AtomicOps Support
///Enables AtomicOps on this PCIe controller
typedef enum {
  IDSOPT_DBG_GNB_GPP_ATOMIC_OPS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GPP_ATOMIC_OPS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_ATOMIC_OPS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_GPP_ATOMIC_OPS;

///AER Settings for All Ports
///AER Settings for all PCIe ports, unless overriden by per port settings.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL;

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_ALL_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 1
///AER Per port settings, Group 1
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL1_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 2
///AER Per port settings, Group 2
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL2_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 3
///AER Per port settings, Group 3
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL3_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 4
///AER Per port settings, Group 4
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL4_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 5
///AER Per port settings, Group 5
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL5_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 6
///AER Per port settings, Group 6
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL6_ACS_VIOLATION_SEVERITY;

///AER Settings Per-Port Group 7
///AER Per port settings, Group 7
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7;

///Socket
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_SOCKET_SOCKET0 = 0x0,///<Socket 0
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_SOCKET_SOCKET1 = 1,///<Socket 1
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_SOCKET;

///Port Identification Method
///Method to identify which Device/Function, Port Number or Lane Number settings should be applied to.
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ID_METHOD_DEVICEANDFUNCTION = 0,///<Device and  Function
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ID_METHOD_PORTNUMBER = 1,///<Port Number
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ID_METHOD_LANENUMBER = 2,///<Lane Number
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ID_METHOD;

///PCI Device
///The PCIe device number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DEVICE_MIN 0x1 ///< Min of PCI Device
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DEVICE_MAX 0x4 ///< Max of PCI Device

///PCI Function
///The PCIe function number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_FUNCTION_MIN 0x1 ///< Min of PCI Function
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_FUNCTION_MAX 0x7 ///< Max of PCI Function

///NBIO Number
///The NBIO number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_NBIO_NUMBER_MIN 0 ///< Min of NBIO Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_NBIO_NUMBER_MAX 0x3 ///< Max of NBIO Number

///Port Number
///The PCIe port number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_PORT_NUMBER_MIN 0 ///< Min of Port Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_PORT_NUMBER_MAX 0xf ///< Max of Port Number

///Lane Number
///The PCIe lane number to apply settings to.
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_LANE_NUMBER_MIN 0 ///< Min of Lane Number
#define IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_LANE_NUMBER_MAX 0x81 ///< Max of Lane Number

///Bad TLP
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_TLP;

///Bad DLLP Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_BAD_DLLP_STATUS;

///Replay Number Rollover Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_MASK;

///Acs Violation Severity
typedef enum {
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_PORT_SPECIAL7_ACS_VIOLATION_SEVERITY;

///NBIO Global CG Override
typedef enum {
  IDSOPT_DBG_NBIO_GLOBAL_CG_OVERRIDE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_GLOBAL_CG_OVERRIDE_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_GLOBAL_CG_OVERRIDE;

///IOHC LCLK Clock Gating
///LCLK Gating (IOC)
typedef enum {
  IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING;

///IOMMU L1 Clock Gating
///IOMMU L1 LCLK Gating
typedef enum {
  IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING;

///IOMMU L2 Clock Gating
///IOMMU L2 LCLK Gating
typedef enum {
  IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING;

///SST clock gating
///SST clock gating
typedef enum {
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING;

///NBIF MGCG
///nBIF MCGC
typedef enum {
  IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_DISABLED = 0,///<Disabled
  IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_ENABLED = 1,///<Enabled
  IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_AUTO = 0xf,///<Auto
} IDSOPT_CBS_DBG_NBIO_NBIF_MGCG;

///NBIF MGCG Hysteresis
#define IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_HYSTERESIS_MIN 0 ///< Min of NBIF MGCG Hysteresis
#define IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_HYSTERESIS_MAX 0xff ///< Max of NBIF MGCG Hysteresis

///SHUB MGCG
///SHUB (NGDC) MGCG
typedef enum {
  IDSOPT_DBG_NBIO_SHUB_MGCG_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_SHUB_MGCG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_SHUB_MGCG_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_SHUB_MGCG;

///SHUB MGCG Hysteresis
#define IDSOPT_DBG_NBIO_SHUB_MGCG_HYSTERESIS_MIN 0 ///< Min of SHUB MGCG Hysteresis
#define IDSOPT_DBG_NBIO_SHUB_MGCG_HYSTERESIS_MAX 0xff ///< Max of SHUB MGCG Hysteresis

///IOHC Global CG Control
typedef enum {
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_AUTO = 0xf,///<Auto
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_DISABLED = 0,///<Disabled
} IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL;

///IOHC CG Hysteresis
#define IDSOPT_DBG_NBIO_IOHC_CG_HYSTERESIS_MIN 0 ///< Min of IOHC CG Hysteresis
#define IDSOPT_DBG_NBIO_IOHC_CG_HYSTERESIS_MAX 0xff ///< Max of IOHC CG Hysteresis

///IOHC CG CTRL0 CLK0
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK0_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK0_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK0;

///IOHC CG CTRL0 CLK1
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK1_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK1_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK1;

///IOHC CG CTRL0 CLK2
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK2_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK2_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK2;

///IOHC CG CTRL0 CLK3
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK3_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK3_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK3;

///IOHC CG CTRL0 CLK4
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK4_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK4;

///IOHC CG CTRL0 CLK5
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK5_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK5_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK5;

///IOHC CG CTRL0 CLK6
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK6_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK6_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK6;

///IOHC CG CTRL0 CLK7
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK7_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK7_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK7;

///IOHC CG CTRL0 CLK8
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK8_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK8_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK8;

///IOHC CG CTRL0 CLK9
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK9_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK9_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK9;

///IOHC CG CTRL1 CLK0
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK0_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK0_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK0;

///IOHC CG CTRL1 CLK1
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK1_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK1_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK1;

///IOHC CG CTRL1 CLK2
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK2_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK2_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK2;

///IOHC CG CTRL1 CLK3
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK3_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK3_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK3;

///IOHC CG CTRL1 CLK4
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK4_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK4;

///IOHC CG CTRL1 CLK5
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK5_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK5_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK5;

///IOHC CG CTRL1 CLK6
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK6_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK6_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK6;

///IOHC CG CTRL1 CLK7
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK7_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK7_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK7;

///IOHC CG CTRL1 CLK8
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK8_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK8_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK8;

///IOHC CG CTRL1 CLK9
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK9_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK9_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK9;

///IOHC CG CTRL2 CLK0
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK0_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK0_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK0;

///IOHC CG CTRL2 CLK1
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK1_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK1_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK1;

///IOHC CG CTRL2 CLK2
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK2_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK2_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK2;

///IOHC CG CTRL2 CLK3
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK3_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK3_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK3;

///IOHC CG CTRL2 CLK4
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK4_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK4;

///IOHC CG CTRL2 CLK5
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK5_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK5_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK5;

///IOHC CG CTRL2 CLK6
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK6_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK6_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK6;

///IOHC CG CTRL2 CLK7
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK7_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK7_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK7;

///IOHC CG CTRL2 CLK8
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK8_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK8_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK8;

///IOHC CG CTRL2 CLK9
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK9_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK9_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK9;

///NTB Clock Gating
///Enable/Disable NTB Clock Gating
typedef enum {
  IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE;

///VF_BAR Allocation Control
///Configure non pci device bar for IOMMU VF
typedef enum {
  IDSOPT_DBG_GNB_VF_BAR_ALLOCATION_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_VF_BAR_ALLOCATION_CONTROL_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_VF_BAR_ALLOCATION_CONTROL;

///VFCNTL_BAR Allocation Control
///Configure non pci device bar for IOMMU VF Control
typedef enum {
  IDSOPT_DBG_GNB_VFCNTL_BAR_ALLOCATION_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_VFCNTL_BAR_ALLOCATION_CONTROL_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_VFCNTL_BAR_ALLOCATION_CONTROL;

///VF*_BAR Enable Bit
///Hit the enable bit on any allocated VF Bars for IOMMU
typedef enum {
  IDSOPT_DBG_GNB_VF_BA_RS_ENABLE_BIT_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_VF_BA_RS_ENABLE_BIT_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_VF_BA_RS_ENABLE_BIT;

///Overclocking Enable
///Disable Overclocking.  "Auto" will not force overclocking disabled
typedef enum {
  IDSOPT_DBG_OVERCLOCKING_ENABLE_AUTO = 0xF,///<Auto
  IDSOPT_DBG_OVERCLOCKING_ENABLE_DISABLE = 1,///<Disable
  IDSOPT_DBG_OVERCLOCKING_ENABLE_ENABLE = 0,///<Enable
} IDSOPT_DBG_OVERCLOCKING_ENABLE;

///Overclocking Frequency Limit
///Value in MHz selects the maximum frequency setting allowed for overclocking support.
#define IDSOPT_DBG_OVERCLOCKING_FREQUENCY_LIMIT_MIN 0 ///< Min of Overclocking Frequency Limit
#define IDSOPT_DBG_OVERCLOCKING_FREQUENCY_LIMIT_MAX 8000 ///< Max of Overclocking Frequency Limit

///Overclocking Voltage Limit
///Value in VID selects the maximum voltage setting allowed for overclocking support.
#define IDSOPT_DBG_OVERCLOCKING_VOLTAGE_LIMIT_MIN 0 ///< Min of Overclocking Voltage Limit
#define IDSOPT_DBG_OVERCLOCKING_VOLTAGE_LIMIT_MAX 0xFF ///< Max of Overclocking Voltage Limit

///DBGU_NBIO trace to DRAM Control
///Control DBGU NBIO trac to DRAM
typedef enum {
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_CTRL_AUTO = 0,///<Auto
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_CTRL_MANUAL = 1,///<Manual
} IDSOPT_DBG_DBGU_NBIO_TO_DRAM_CTRL;

///Sockets(DBGU_NBIO)
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_SOCKET_SOCKET0 = 0,///<Socket 0
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_SOCKET_SOCKET1 = 1,///<Socket 1
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_SOCKET_ALLSOCKETS = 0xf,///<All Sockets
} IDSOPT_DBG_DBGU_NBIO_TO_DRAM_SOCKET;

///Instances(DBGU_NBIO)
///These settings will be applied to the specified Instance number.
typedef enum {
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_INSTANCE_INSTANCE0 = 0,///<Instance 0
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_INSTANCE_INSTANCE1 = 1,///<Instance 1
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_INSTANCE_INSTANCE2 = 2,///<Instance 2
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_INSTANCE_INSTANCE3 = 3,///<Instance 3
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_INSTANCE_ALLINSTANCE = 0xf,///<All Instance
} IDSOPT_DBG_DBGU_NBIO_TO_DRAM_INSTANCE;

///Buffer Size(DBGU_NBIO)
///setting DBGU_NBIO trace to DRAM Buffer Size
typedef enum {
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_BUFFER_SIZE_1MB = 1,///<1 MB
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_BUFFER_SIZE_4MB = 2,///<4 MB
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_BUFFER_SIZE_16MB = 3,///<16 MB
  IDSOPT_DBG_DBGU_NBIO_TO_DRAM_BUFFER_SIZE_64MB = 4,///<64 MB
} IDSOPT_DBG_DBGU_NBIO_TO_DRAM_BUFFER_SIZE;

///DBGU_IO trace to DRAM Control
///Control DBGU NBIO trac to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_CTRL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_CTRL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_CTRL;

///Sockets(DBGU_IO)
///These settings will be applied to the specified socket number.
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_SOCKET_SOCKET0 = 0,///<Socket 0
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_SOCKET_SOCKET1 = 1,///<Socket 1
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_SOCKET_ALLSOCKETS = 0xf,///<All Sockets
} IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_SOCKET;

///Instances(DBGU_IO)
///These settings will be applied to the specified Instance number.
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_INSTANCE_INSTANCE0 = 0,///<Instance 0
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_INSTANCE_INSTANCE1 = 1,///<Instance 1
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_INSTANCE_INSTANCE2 = 2,///<Instance 2
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_INSTANCE_INSTANCE3 = 3,///<Instance 3
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_INSTANCE_ALLINSTANCE = 0xf,///<All Instance
} IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_INSTANCE;

///Buffer Size(DBGU_IO)
///setting DBGU_IO trace to DRAM Buffer Size
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_BUFFER_SIZE_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_BUFFER_SIZE_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_BUFFER_SIZE_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_BUFFER_SIZE_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_BUFFER_SIZE;

///AB Clock Gating
///Enable or disable AB clock gating
typedef enum {
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING;

///SDP Memory Power Saving
///Enable/disable SDP Memory Power Saving
typedef enum {
  IDSOPT_SBG_MEMORY_POWER_SAVING_ENABLED = 1,///<Enabled
  IDSOPT_SBG_MEMORY_POWER_SAVING_DISABLED = 0,///<Disabled
} IDSOPT_SBG_MEMORY_POWER_SAVING;

///SDP Clock Gating
///Enable/disable SDP Clock Gating
typedef enum {
  IDSOPT_SBG_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_SBG_CLOCK_GATING_DISABLED = 0,///<Disabled
} IDSOPT_SBG_CLOCK_GATING;

///XDMA DMA write 16-byte mode
///Enable/disable XDMA DMA Write 16 Byte Mode
typedef enum {
  IDSOPT_XDMA_DMA_WRITE16_BYTE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_XDMA_DMA_WRITE16_BYTE_MODE_DISABLED = 0,///<Disabled
} IDSOPT_XDMA_DMA_WRITE16_BYTE_MODE;

///XDMA Memory Power Saving
///Enable/disable XDMA Memory Power Saving
typedef enum {
  IDSOPT_XDMA_MEMORY_POWER_SAVING_ENABLED = 1,///<Enabled
  IDSOPT_XDMA_MEMORY_POWER_SAVING_DISABLED = 0,///<Disabled
} IDSOPT_XDMA_MEMORY_POWER_SAVING;

///XDMA PENDING NPR THRESHOLD
///XDMA PENDING NPR THRESHOLD
typedef enum {
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_32PENDINGNPR = 0,///<32 Pending NPR
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_1PENDINGNPR = 1,///<1 Pending NPR
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_4PENDINGNPR = 2,///<4 Pending NPR
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_28PENDINGNPR = 3,///<28 Pending NPR
} IDSOPT_XDMA_PENDING_NPR_THRESHOLD;

///XDMA DNCPL ORDER DIS
///XDMA DNCPL ORDER DIS
typedef enum {
  IDSOPT_XDMA_DNCPL_ORDER_DIS_ENABLED = 0,///<Enabled
  IDSOPT_XDMA_DNCPL_ORDER_DIS_DISABLED = 1,///<Disabled
} IDSOPT_XDMA_DNCPL_ORDER_DIS;

///SDPHOST_BYPASS_DATA_PACK
typedef enum {
  IDSOPT_SDPHOST_BYPASS_DATA_PACK_DISABLE = 0,///<Disable
  IDSOPT_SDPHOST_BYPASS_DATA_PACK_ENABLE = 1,///<Enable
} IDSOPT_SDPHOST_BYPASS_DATA_PACK;

///SDPHOST_DIS_NPMWR_PROTECT
typedef enum {
  IDSOPT_SDPHOST_DIS_NPMWR_PROTECT_DISABLE = 0,///<Disable
  IDSOPT_SDPHOST_DIS_NPMWR_PROTECT_ENABLE = 1,///<Enable
} IDSOPT_SDPHOST_DIS_NPMWR_PROTECT;

///SATA Set MaxGen2 Capability
///Select whether or not Enable SATA MaxGen2 Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2;

///Aggressive Link PM Capability
///Select Enable or Disable Aggressive Link PM Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP;

///Port Multiplier Capability
///Select Enable or Disable Port Multiplier Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP;

///Partial State Capability
///Select Enable or Disable Partial State Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_PSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_PSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_PSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PSC_CAP;

///Slumber State Capability
///Select Enable or Disable Slumber State Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_SSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SSC_CAP;

///Unused SATA Port Auto Shut Down
///Select Unused SATA Port Auto Shut Down or not
typedef enum {
  IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF;

///Options for FIS-based Switching Support
///Select Enable or Disable FIS-based Switching Support
typedef enum {
  IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING;

///Command Completion Coalescing Support
///Select Enable or Disable Command Completion Coalescing Support
typedef enum {
  IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT;

///SATA MSI Capability
///Select Enable or Disable SATA MSI Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY;

///SATA Target Support 8 Devices
///Enable/disable SATA 8-device target support
typedef enum {
  IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE;

///Generic Mode
///Enable/disable SATA generic mode
typedef enum {
  IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE_ENABLED = 0,///<Enabled
  IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE_DISABLED = 1,///<Disabled
  IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE;

///SATA AHCI Enclosure
///Enable/disable SATA AHCI enclosure management
typedef enum {
  IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT;

///Sata0 Enable
///Enable or Disable Sata0.\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA0_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA0_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA0_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA0_ENABLE;

///Sata1 Enable
///Enable or Disable Sata1.\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA1_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA1_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA1_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA1_ENABLE;

///Sata2 Enable
///Enable or Disable Sata2.\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA2_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA2_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA2_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA2_ENABLE;

///Sata3 Enable
///Enable or Disable Sata3.\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA3_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA3_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA3_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA3_ENABLE;

///Sata4 (Socket1) Enable
///Enable or Disable Sata4 on Socket 1 (IOD1)..\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA4_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA4_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA4_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA4_ENABLE;

///Sata5 (Socket1) Enable
///Enable or Disable Sata5 on Socket 1 (IOD1)..\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA5_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA5_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA5_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA5_ENABLE;

///Sata6 (Socket1) Enable
///Enable or Disable Sata6 on Socket 1 (IOD1)..\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA6_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA6_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA6_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA6_ENABLE;

///Sata7 (Socket1) Enable
///Enable or Disable Sata7 on Socket 1 (IOD1)..\nEach IOD has 4 Sata Controllers.
typedef enum {
  IDSOPT_DBG_FCH_SATA7_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA7_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA7_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA7_ENABLE;

///Sata0 eSATA Port0
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT0;

///Sata0 eSATA Port1
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT1;

///Sata0 eSATA Port2
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT2_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT2_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT2;

///Sata0 eSATA Port3
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT3_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT3_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT3;

///Sata0 eSATA Port4
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT4_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT4_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT4;

///Sata0 eSATA Port5
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT5_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT5_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT5;

///Sata0 eSATA Port6
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT6_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT6_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT6;

///Sata0 eSATA Port7
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT7_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT7_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT7;

///Sata1 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0;

///Sata1 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1;

///Sata1 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2;

///Sata1 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3;

///Sata1 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4;

///Sata1 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5;

///Sata1 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6;

///Sata1 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7;

///Sata2 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0;

///Sata2 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1;

///Sata2 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2;

///Sata2 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3;

///Sata2 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4;

///Sata2 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5;

///Sata2 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6;

///Sata2 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7_AUTO = 2,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7;

///Sata3 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0;

///Sata3 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1;

///Sata3 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2;

///Sata3 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3;

///Sata3 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4;

///Sata3 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5;

///Sata3 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6;

///Sata3 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7;

///Sata4 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0;

///Sata4 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1;

///Sata4 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2;

///Sata4 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3;

///Sata4 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4;

///Sata4 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5;

///Sata4 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6;

///Sata4 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7;

///Sata5 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0;

///Sata5 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1;

///Sata5 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2;

///Sata5 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3;

///Sata5 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4;

///Sata5 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5;

///Sata5 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6;

///Sata5 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7;

///Sata6 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0;

///Sata6 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1;

///Sata6 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2;

///Sata6 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3;

///Sata6 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4;

///Sata6 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5;

///Sata6 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6;

///Sata6 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7;

///Sata7 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0;

///Sata7 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1;

///Sata7 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2;

///Sata7 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3;

///Sata7 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4;

///Sata7 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5;

///Sata7 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6;

///Sata7 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7;

///Socket1 DevSlp0 Enable
///Only Sata0 on each IOD/socket support DevSlp.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0;

///DevSleep0 Port Number
///Only Sata0 on each IOD/socket support DevSlp.
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Socket1 DevSlp1 Enable
///Only Sata0 on each IOD/socket support DevSlp.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1;

///DevSleep1 Port Number
///Only Sata0 on each IOD/socket support DevSlp.
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Sata0 SGPIO
///Eable Sata0 SGPIO feature
typedef enum {
  IDSOPT_DBG_FCH_SATA_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SGPIO0;

///Sata1 SGPIO
///Enable or Disable SataSgpio on Sata1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0;

///Sata2 SGPIO
///Enable or Disable SataSgpio on Sata2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0;

///Sata3 SGPIO
///Enable or Disable SataSgpio on Sata3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0;

///Sata4 SGPIO
///Enable or Disable SataSgpio on Sata4 (Socket1)
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0;

///Sata5 SGPIO
///Enable or Disable SataSgpio on Sata5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0;

///Sata6 SGPIO
///Enable or Disable SataSgpio on Sata6 (Socket1)
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0;

///Sata7 SGPIO
///Enable or Disable SataSgpio on Sata7 (Socket7)
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0;

///Timer Tick Tracking
///Enable/disable timer tick tracking
typedef enum {
  IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK;

///Clock Interrupt Tag
///Enable/disable tag on clock interrupt
typedef enum {
  IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG;

///SPI Read Mode
///Select SPI read mode
typedef enum {
  IDSOPT_DBG_FCH_SPI_MODE_DEFAULT = 0,///<Default
  IDSOPT_DBG_FCH_SPI_MODE_DUALIO112 = 2,///<Dual IO 1-1-2
  IDSOPT_DBG_FCH_SPI_MODE_QUALIO114 = 3,///<Qual IO 1-1-4
  IDSOPT_DBG_FCH_SPI_MODE_DUALIO122 = 4,///<Dual IO 1-2-2
  IDSOPT_DBG_FCH_SPI_MODE_QUALIO144 = 5,///<Qual IO 1-4-4
  IDSOPT_DBG_FCH_SPI_MODE_NORMAL = 6,///<Normal
  IDSOPT_DBG_FCH_SPI_MODE_FASTREAD = 7,///<Fast Read
  IDSOPT_DBG_FCH_SPI_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SPI_MODE;

///SPI Normal Speed
///Select SPI Normal speed
typedef enum {
  IDSOPT_DBG_FCH_SPI_SPEED_DEFAULT = 0,///<Default
  IDSOPT_DBG_FCH_SPI_SPEED_66MHZ = 1,///<66MHz
  IDSOPT_DBG_FCH_SPI_SPEED_33MHZ = 2,///<33MHz
  IDSOPT_DBG_FCH_SPI_SPEED_22MHZ = 3,///<22MHz
  IDSOPT_DBG_FCH_SPI_SPEED_165MHZ = 4,///<16.5MHz
  IDSOPT_DBG_FCH_SPI_SPEED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_FCH_SPI_SPEED_800KHZ = 5,///<800kHz
} IDSOPT_DBG_FCH_SPI_SPEED;

///SPI Fast Read Speed
///Select SPI fast read speed
typedef enum {
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_66MHZ = 1,///<66MHz
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_33MHZ = 2,///<33MHz
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_22MHZ = 3,///<22MHz
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_165MHZ = 4,///<16.5MHz
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_100MHZ = 5,///<100MHz
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_FCH_SPI_FAST_SPEED_800KHZ = 6,///<800kHz
} IDSOPT_DBG_FCH_SPI_FAST_SPEED;

///SDB
///Select whether or not set FCH debug function
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE;

///HPET in FCH
///Select whether or not Enable HPET in FCH
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE;

///Wathdog Timer (WDT) in FCH
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE;

///FCH Spread Spectrum
///Select whether or not Enable the Spread Spectrum Feature
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM;

///Not Clear ThermalTrip Status
///Select whether or not Clear the ThermalTrip Status bit
typedef enum {
  IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP;

///A Link Clock Gate Off
///A Link Clock Gate Off
typedef enum {
  IDSOPT_A_LINK_CLK_GATE_OFF_ENABLED = 1,///<Enabled
  IDSOPT_A_LINK_CLK_GATE_OFF_DISABLED = 0,///<Disabled
} IDSOPT_A_LINK_CLK_GATE_OFF;

///B Link Clock Gate Off
///B Link Clock Gate Off
typedef enum {
  IDSOPT_B_LINK_CLK_GATE_OFF_ENABLED = 1,///<Enabled
  IDSOPT_B_LINK_CLK_GATE_OFF_DISABLED = 0,///<Disabled
} IDSOPT_B_LINK_CLK_GATE_OFF;

///USB DBGCLK Enable
typedef enum {
  IDSOPT_DBG_USBDBGCLK_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_USBDBGCLK_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_USBDBGCLK_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_USBDBGCLK_ENABLE;

///Stress Reset Mode
///Select stress reset mode
typedef enum {
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_IO_WRITE_64_FE = 1,///<IO_WRITE_64_FE
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_IO_WRITE_CF9_06 = 2,///<IO_WRITE_CF9_06
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_IO_WRITE_CF9_0E = 3,///<IO_WRITE_CF9_0E
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_STRESS_RESET_MODE;

///Long Timer SMI
///Whether to register long timer SMI in POST. Short Timer and Long Timer SMIs can be enabled exclusively, if both are enabled, only Long timer SMI will take effect
typedef enum {
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI;

///Long Timer SMI StartNow
///Whether to start the SMI immediately during registration
typedef enum {
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW;

///Long Timer CycleDuration
///Actual cycle duration = CycleDuration + 1 (ms), eg: CycleDuration = 999, then SMI frequency=1Hz
#define IDSOPT_DBG_FCH_SMI_LONG_TIMER_CYCLE_DURATION_MIN 0 ///< Min of Long Timer CycleDuration
#define IDSOPT_DBG_FCH_SMI_LONG_TIMER_CYCLE_DURATION_MAX 0x7fff ///< Max of Long Timer CycleDuration

///Short Timer SMI
///Whether to register short timer SMI in POST
typedef enum {
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI;

///Short Timer SMI StartNow
///Whether to start the SMI immediately during registration
typedef enum {
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW;

///Short Timer CycleDuration
///Actual cycle duration = CycleDuration + 1 (us), eg: CycleDuration = 999, then SMI frequency=1000Hz
#define IDSOPT_DBG_FCH_SMI_SHORT_TIMER_CYCLE_DURATION_MIN 0 ///< Min of Short Timer CycleDuration
#define IDSOPT_DBG_FCH_SMI_SHORT_TIMER_CYCLE_DURATION_MAX 0x7fff ///< Max of Short Timer CycleDuration

///LPC_CLK1
typedef enum {
  IDSOPT_DBG_FCH_LPC_CL_K1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_LPC_CL_K1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_LPC_CL_K1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_LPC_CL_K1;

///Enable ForceGen1
///Enable User input to limit USB3 port speed for Gen2 vs. Gen1.
typedef enum {
  IDSOPT_DBG_FCH_USB_FORCE_GEN1_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_USB_FORCE_GEN1_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_USB_FORCE_GEN1_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_USB_FORCE_GEN1_EN;

///Port Force Gen1
///Set 1 to force Usb3 port to gen1 speed.\nbit[1:0] Socket0 Controller0 port0-1.\nbit[3:2] Socket0 Controller1 port0-1.\nbit[5:4] Socket0 Controller0 port0-1.\nbit[7:6] Socket0 Controller1 port0-1.
#define IDSOPT_FCH_DEBUG_USB_PORT_FORCE_GEN1_MIN 0 ///< Min of Port Force Gen1
#define IDSOPT_FCH_DEBUG_USB_PORT_FORCE_GEN1_MAX 0xFF ///< Max of Port Force Gen1

///PT Aggressive Link PM Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP;

///PT Partial State Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_PSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_PSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_PSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_PSC_CAP;

///PT Slumber State Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_SSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_SSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_SSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_SSC_CAP;

///PT SATA MSI Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_MSI_CAPABILITY_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_MSI_CAPABILITY_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_MSI_CAPABILITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_MSI_CAPABILITY;

///PT Sata mode for Port0
///PT SATA port mode for port 0
typedef enum {
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_GEN1 = 1,///<Gen1
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_GEN2 = 2,///<Gen2
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_GEN3 = 3,///<Gen3
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_PORT_MD_PORT0;

///PT Sata mode for Port1
///PT SATA port mode for port 1
typedef enum {
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_GEN1 = 1,///<Gen1
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_GEN2 = 2,///<Gen2
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_GEN3 = 3,///<Gen3
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_PORT_MD_PORT1;

///PT Sata Hot Plug Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_HOT_PLUG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_HOT_PLUG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_HOT_PLUG_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_SATA_HOT_PLUG;

///PT AOAC
///AOAC
typedef enum {
  IDSOPT_DBG_PTAOAC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PTAOAC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PTAOAC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PTAOAC;

///PT HW LPM
typedef enum {
  IDSOPT_DBG_PTHW_LPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PTHW_LPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PTHW_LPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PTHW_LPM;

///PT DbC
typedef enum {
  IDSOPT_DBG_PT_DB_C_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_DB_C_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_DB_C_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_DB_C;

///PT XHC PME
///PT XHC PME
typedef enum {
  IDSOPT_DBG_PTXHC_PME_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PTXHC_PME_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PTXHC_PME_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PTXHC_PME;

///Data Calculation
///FEATURE_DATA_CALCULATION_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_DATA_CALCULATION_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_DATA_CALCULATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_DATA_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_DATA_CALCULATION;

///PPT
///FEATURE_PPT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPPT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPPT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPPT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPPT;

///TDC
///FEATURE_TDC_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUTDC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUTDC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUTDC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUTDC;

///EDC
///FEATURE_EDC_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUEDC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUEDC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUEDC_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMUEDC;

///Thermal Controller
///FEATURE_THERMAL_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER;

///Reliability Controller
///FEATURE_FIT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER;

///PROCHOT
///FEATURE_PROCHOT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPROCHOT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPROCHOT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPROCHOT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPROCHOT;

///LCLK Deep Sleep
///FEATURE_LCLK_DEEP_SLEEP_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMULCLK_DEEP_SLEEP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMULCLK_DEEP_SLEEP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMULCLK_DEEP_SLEEP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMULCLK_DEEP_SLEEP;

///SOCCLK Deep Sleep
///FEATURE_SOCCLK_DEEP_SLEEP
typedef enum {
  IDSOPT_DBG_GNB_SMUSOCCLK_DEEP_SLEEP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUSOCCLK_DEEP_SLEEP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUSOCCLK_DEEP_SLEEP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUSOCCLK_DEEP_SLEEP;

///SHUBCLK Deep Sleep
///FEATURE_SHUBCLK_DEEP_SLEEP_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUSHUBCLK_DEEP_SLEEP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUSHUBCLK_DEEP_SLEEP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUSHUBCLK_DEEP_SLEEP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUSHUBCLK_DEEP_SLEEP;

///CC6
///FEATURE_CC6_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUC_C6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUC_C6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUC_C6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUC_C6;

///PC6
///FEATURE_PC6_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUP_C6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUP_C6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUP_C6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUP_C6;

///SMU Clock Gating
///FEATURE_CLOCK_GATING_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUSMU_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUSMU_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUSMU_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUSMU_CLOCK_GATING;

///CCLK DPM
///FEATURE_CCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUCCLKDPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUCCLKDPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUCCLKDPM_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMUCCLKDPM;

///LCLK DPM
///FEATURE_LCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMULCLKDPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMULCLKDPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMULCLKDPM_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMULCLKDPM;

///FCLK/UCLK/MEMCLK DPM
///FEATURE_FCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUFCLKUCLKMEMCLKDPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUFCLKUCLKMEMCLKDPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUFCLKUCLKMEMCLKDPM_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMUFCLKUCLKMEMCLKDPM;

///DLWM
///FEATURE_DLWM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDLWM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDLWM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDLWM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDLWM;

///PCIe Hotplug
///FEATURE_PCIE_HOTPLUG_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG;

///Fan Controller
///FEATURE_FAN_CONTROLLER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER;

///Cstate Boost
///FEATURE_CSTATE_BOOST_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_CSTATE_BOOST_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_CSTATE_BOOST_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_CSTATE_BOOST_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_CSTATE_BOOST;

///DLDO
///FEATURE_DLDO_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDLDO_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDLDO_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDLDO_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMUDLDO;

///CPPC
///FEATURE_CPPC_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUCPPC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUCPPC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUCPPC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUCPPC;

///DF PState Mode Select
///Selects the DF Pstate Mode
typedef enum {
  IDSOPT_DBG_DF_PSTATE_MODE_SEL_NORMAL = 0,///<Normal
  IDSOPT_DBG_DF_PSTATE_MODE_SEL_DFPSTATEREMAPUSEDFPSTATE0ONLY = 1,///<DfPstate Remap, use DfPstate[0] only
  IDSOPT_DBG_DF_PSTATE_MODE_SEL_DFPSTATEREMAPUSEALLDFPSTATES = 2,///<DfPstate Remap, use all DfPstates
  IDSOPT_DBG_DF_PSTATE_MODE_SEL_FORCEDFPSTATEINDEX = 3,///<Force DfPstateIndex
  IDSOPT_DBG_DF_PSTATE_MODE_SEL_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_DF_PSTATE_MODE_SEL;

///DF PState Override
///Selects the fixed PState when DF PState Mode Select is Override
#define IDSOPT_DBG_DF_PSTATE_OVERRIDE_MIN 0 ///< Min of DF PState Override
#define IDSOPT_DBG_DF_PSTATE_OVERRIDE_MAX 48 ///< Max of DF PState Override

///TDC Control
///Auto = Use the fused VDDCR_CPU TDC limit\nManual = User can set customized VDDCR_CPU TDC limit
typedef enum {
  IDSOPT_DBG_TDC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_TDC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_TDC_CTL;

///TDC
///VDDCR_CPU TDC Limit [A]
#define IDSOPT_DBG_TDC_LIMIT_MIN 0 ///< Min of TDC
#define IDSOPT_DBG_TDC_LIMIT_MAX 0xffffffff ///< Max of TDC

///EDC Control
///Auto = Use the fused VDDCR_CPU EDC limit\nManual = User can set customized VDDCR_CPU EDC limit
typedef enum {
  IDSOPT_DBG_EDC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_EDC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_EDC_CTL;

///EDC
///VDDCR_CPU EDC Limit [A]
#define IDSOPT_DBG_EDC_LIMIT_MIN 0 ///< Min of EDC
#define IDSOPT_DBG_EDC_LIMIT_MAX 0xffffffff ///< Max of EDC

///TjMax Control
///Auto = Auto = Use the fused TjMax\nManual = User can set customized TjMax
typedef enum {
  IDSOPT_DBG_TJ_MAX_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_TJ_MAX_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_TJ_MAX_CTL;

///TjMax
///TjMax [C] (Used for thermal throttling limit)
#define IDSOPT_DBG_TJ_MAX_MIN 0 ///< Min of TjMax
#define IDSOPT_DBG_TJ_MAX_MAX 0xffffffff ///< Max of TjMax

///Platform Infrastructure Limits
///Auto = Use the default platform infrastructure limits\nManual = User can set customized platform infrastructure limits
typedef enum {
  IDSOPT_DBG_PLATFORM_INFRASTRUCTURE_LIMITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_PLATFORM_INFRASTRUCTURE_LIMITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_PLATFORM_INFRASTRUCTURE_LIMITS_CTL;

///TDP Platform Limit
///TDP Platform Limit [W]
#define IDSOPT_DBG_TDP_PLATFORM_LIMIT_MIN 0 ///< Min of TDP Platform Limit
#define IDSOPT_DBG_TDP_PLATFORM_LIMIT_MAX 0xffffffff ///< Max of TDP Platform Limit

///PPT Platform Limit
///PPT Platform Limit [W]
#define IDSOPT_DBG_PPT_PLATFORM_LIMIT_MIN 0 ///< Min of PPT Platform Limit
#define IDSOPT_DBG_PPT_PLATFORM_LIMIT_MAX 0xffffffff ///< Max of PPT Platform Limit

///TDC Platform Limit
///TDC Platform Limit [W]
#define IDSOPT_DBG_TDC_PLATFORM_LIMIT_MIN 0 ///< Min of TDC Platform Limit
#define IDSOPT_DBG_TDC_PLATFORM_LIMIT_MAX 0xffffffff ///< Max of TDC Platform Limit

///EDC Platform Limit
///EDC Platform Limit [W]
#define IDSOPT_DBG_EDC_PLATFORM_LIMIT_MIN 0 ///< Min of EDC Platform Limit
#define IDSOPT_DBG_EDC_PLATFORM_LIMIT_MAX 0xffffffff ///< Max of EDC Platform Limit

///DLDO PSM Margin Control
///Auto = Default configuration\nManual = User can set custom DLDO PSM Margin
typedef enum {
  IDSOPT_DBG_DLDO_PSM_MARGIN_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_DLDO_PSM_MARGIN_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_DLDO_PSM_MARGIN_CTL;

///DLDO PSM Margin Sign
///Positive = DLDO PSM Margin value is positive\nNegitive = DLDO PSM Margin value is negitive
typedef enum {
  IDSOPT_DBG_DLDO_PSM_MARGIN_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_DLDO_PSM_MARGIN_SIGN_NEGITIVE = 0,///<Negitive
} IDSOPT_DBG_DLDO_PSM_MARGIN_SIGN;

///DLDO PSM Margin
///Specify the PSM offset to apply to the DLDOs -- signed integer\nThis offset is applied to all cores in the system
#define IDSOPT_DBG_DLDO_PSM_MARGIN_MIN 0 ///< Min of DLDO PSM Margin
#define IDSOPT_DBG_DLDO_PSM_MARGIN_MAX 0xffffffff ///< Max of DLDO PSM Margin

///SVI2 Voltage Control
///Auto = Use default VDDCR_CPU voltage control\nManual = User can set custom VDDCR_CPU voltage control settings
typedef enum {
  IDSOPT_DBG_VDDCR_VOLTAGE_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_VDDCR_VOLTAGE_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_VDDCR_VOLTAGE_CTL;

///VDDCR_CPU Voltage Offset Sign
///Positive = VDDCR_CPU Voltage Offset value is positive\nNegitive = VDDCR_CPU Voltage Offset value is negitive
typedef enum {
  IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_SIGN_NEGITIVE = 0,///<Negitive
} IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_SIGN;

///VDDCR_CPU Voltage Offset
///Specify the voltage offset to apply to VDDCR_CPU -- signed integer [mV]
#define IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_MIN 0 ///< Min of VDDCR_CPU Voltage Offset
#define IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_MAX 0xffffffff ///< Max of VDDCR_CPU Voltage Offset

///VDDCR_CPU Voltage
///Specify the voltage to apply to VDDCR_CPU -- integer [mV]
#define IDSOPT_DBG_VDDCR_CPU_VOLTAGE_MIN 0 ///< Min of VDDCR_CPU Voltage
#define IDSOPT_DBG_VDDCR_CPU_VOLTAGE_MAX 0xffffffff ///< Max of VDDCR_CPU Voltage

///VDDCR_SOC Voltage Offset Sign
///Positive = VDDCR_SOC Voltage Offset value is positive\nNegitive = VDDCR_SOC Voltage Offset value is negitive
typedef enum {
  IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_SIGN_NEGITIVE = 0,///<Negitive
} IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_SIGN;

///VDDCR_SOC Voltage Offset
///Specify the voltage offset to apply to VDDCR_SOC -- signed integer [mV]
#define IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_MIN 0 ///< Min of VDDCR_SOC Voltage Offset
#define IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_MAX 0xffffffff ///< Max of VDDCR_SOC Voltage Offset

///VDDCR_SOC Voltage
///Specify the voltage to apply to VDDCR_SOC -- integer [mV]
#define IDSOPT_DBG_VDDCR_SOC_VOLTAGE_MIN 0 ///< Min of VDDCR_SOC Voltage
#define IDSOPT_DBG_VDDCR_SOC_VOLTAGE_MAX 0xffffffff ///< Max of VDDCR_SOC Voltage

///AllocateDramBuffer Control
///Auto = No not allocate a DRAM buffer/n Menual = Allocate DRAM buffer
typedef enum {
  IDSOPT_DBG_DRAM_ALLOCATION_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_DRAM_ALLOCATION_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_DRAM_ALLOCATION_CTL;

///AllocateDramBuffer
///0 = No not allocate a DRAM buffer\nany non-zero value = Allocate DRAM buffer to size in MB defined in the setting
#define IDSOPT_DBG_ALLOCATE_DRAM_BUFFER_MIN 0 ///< Min of AllocateDramBuffer
#define IDSOPT_DBG_ALLOCATE_DRAM_BUFFER_MAX 0xffffffff ///< Max of AllocateDramBuffer

///Determinism Control
///Auto = Use default performance determinism settings\nManual = User can set custom performance determinism settings
typedef enum {
  IDSOPT_DBG_DETERMINISM_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_DETERMINISM_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_DETERMINISM_CTL;

///Determinism Slider Percentage
///Specify the performance determinism slider percentage [%]
#define IDSOPT_DBG_DETERMINISM_SLIDER_PERCENTAGE_MIN 0 ///< Min of Determinism Slider Percentage
#define IDSOPT_DBG_DETERMINISM_SLIDER_PERCENTAGE_MAX 0x64 ///< Max of Determinism Slider Percentage

///DC BTC
///0 = Do not run DC BTC\n1 = Run DC BTC\nAuto = Use default DC BTC settings
typedef enum {
  IDSOPT_DBG_DC_BTC_0 = 0,///<0
  IDSOPT_DBG_DC_BTC_1 = 1,///<1
  IDSOPT_DBG_DC_BTC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_DC_BTC;

///DC BTC VID
#define IDSOPT_DBG_DC_BTC_VID_MIN 0x00 ///< Min of DC BTC VID
#define IDSOPT_DBG_DC_BTC_VID_MAX 0xFF ///< Max of DC BTC VID

///DC BTC Error Offset Voltage/Margin
#define IDSOPT_DBG_DC_BTC_OFFSET_VOLTAGE_MARGIN_MIN 0x00 ///< Min of DC BTC Error Offset Voltage/Margin
#define IDSOPT_DBG_DC_BTC_OFFSET_VOLTAGE_MARGIN_MAX 0xFF ///< Max of DC BTC Error Offset Voltage/Margin

///DF Cstate Control
///Auto = Use default DF Cstate settings\nManual = User can set custom DF Cstate settings
typedef enum {
  IDSOPT_DBG_DF_CSTATE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_DF_CSTATE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_DF_CSTATE_CTL;

///DfCstateClkPwrDnEn
///0 = clear DfCstateClkPwrDnEn\n1 = set DfCstateClkPwrDnEn
typedef enum {
  IDSOPT_DBG_DF_CSTATE_CLK_PWR_DN_EN_CTL_0 = 0,///<0
  IDSOPT_DBG_DF_CSTATE_CLK_PWR_DN_EN_CTL_1 = 1,///<1
} IDSOPT_DBG_DF_CSTATE_CLK_PWR_DN_EN_CTL;

///DfCstateSelfRefrEn
///0 = clear DfCstateSelfRefrEn\n1 = set DfCstateSelfRefrEn
typedef enum {
  IDSOPT_DBG_DF_CSTATE_SELF_REFR_EN_CTL_0 = 0,///<0
  IDSOPT_DBG_DF_CSTATE_SELF_REFR_EN_CTL_1 = 1,///<1
} IDSOPT_DBG_DF_CSTATE_SELF_REFR_EN_CTL;

///DfCstateGmiPwrDnEn
///0 = clear DfCstateGmiPwrDnEn\n1 = set DfCstateGmiPwrDnEn
typedef enum {
  IDSOPT_DBG_DF_CSTATE_GMI_PWR_DN_EN_CTL_0 = 0,///<0
  IDSOPT_DBG_DF_CSTATE_GMI_PWR_DN_EN_CTL_1 = 1,///<1
} IDSOPT_DBG_DF_CSTATE_GMI_PWR_DN_EN_CTL;

///DfCstateGopPwrDnEn
///0 = clear DfCstateGopPwrDnEn\n1 = set DfCstateGopPwrDnEn
typedef enum {
  IDSOPT_DBG_DF_CSTATE_GOP_PWR_DN_EN_CTL_0 = 0,///<0
  IDSOPT_DBG_DF_CSTATE_GOP_PWR_DN_EN_CTL_1 = 1,///<1
} IDSOPT_DBG_DF_CSTATE_GOP_PWR_DN_EN_CTL;

///PowerManagementMode Override
///Auto = Use fused MP1_PowerManagementMode\nManual = User can set custom PowerManagementMode ***SUPPORTED ON UNSECURE PARTS ONLY***
typedef enum {
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_OVERRIDE_MANUAL = 1,///<Manual
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_OVERRIDE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_POWER_MANAGEMENT_MODE_OVERRIDE;

///CCX VDCI3 Async Control
///0 = predictive mode\n1 = async mode
typedef enum {
  IDSOPT_DBG_CCX_VDCI3_ASYNC_CONTROL_0 = 0,///<0
  IDSOPT_DBG_CCX_VDCI3_ASYNC_CONTROL_1 = 1,///<1
  IDSOPT_DBG_CCX_VDCI3_ASYNC_CONTROL_AUTO = 2,///<Auto
} IDSOPT_DBG_CCX_VDCI3_ASYNC_CONTROL;

///PowerManagementMode
///0 = Telemetry\n1 = Per Part Calculations\n2 = Force 100% determinism\n3 = Default 100% Determinism\n4 = Default 0% Determinism
typedef enum {
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_0 = 0,///<0
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_1 = 1,///<1
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_2 = 2,///<2
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_3 = 3,///<3
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_4 = 4,///<4
  IDSOPT_DBG_POWER_MANAGEMENT_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_POWER_MANAGEMENT_MODE;

///CC1Dis
///0=Use the default\n1=Disable CC1 for debug purposes
typedef enum {
  IDSOPT_DBG_GNB_SMUC_C1_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_SMUC_C1_AUTO = 0x0,///<Auto
} IDSOPT_DBG_GNB_SMUC_C1;

///Fmax Override
///Fmax override in MHz; 0 means no override.
#define IDSOPT_DBG_GNB_SMU_FMAX_OVERRIDE_MIN 0 ///< Min of Fmax Override
#define IDSOPT_DBG_GNB_SMU_FMAX_OVERRIDE_MAX 65535 ///< Max of Fmax Override

///CCLK Frequency Control
///CCLK Frequency Control in Mhz; 0 means no force.
#define IDSOPT_DBG_GNB_SMU_CCLK_FREQ_CNTL_MIN 0 ///< Min of CCLK Frequency Control
#define IDSOPT_DBG_GNB_SMU_CCLK_FREQ_CNTL_MAX 65535 ///< Max of CCLK Frequency Control

///GRA Group 1
///Enable or disable GRA Group 1
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A1_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A1_USR_CTL;

///GRA1 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A1_REG_TYPE;

///GRA1 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A1_TIME_POINT;

///GRA1 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A1_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A1_GEN_REG_NODE;

///GRA1 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A1_BUS_MIN 0 ///< Min of GRA1 Bus
#define IDSOPT_DBG_MISC_GR_A1_BUS_MAX 255 ///< Max of GRA1 Bus

///GRA1 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A1_DEV_MIN 0 ///< Min of GRA1 Device
#define IDSOPT_DBG_MISC_GR_A1_DEV_MAX 31 ///< Max of GRA1 Device

///GRA1 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A1_FUN_MIN 0 ///< Min of GRA1 Function
#define IDSOPT_DBG_MISC_GR_A1_FUN_MAX 7 ///< Max of GRA1 Function

///GRA1 Offset
///If type=PCIIndirectReg, this offset specify the dataport. e.g. F0x64_12, x64 is the dataport
#define IDSOPT_DBG_MISC_GR_A1_OFFSET_MIN 0 ///< Min of GRA1 Offset
#define IDSOPT_DBG_MISC_GR_A1_OFFSET_MAX 0xfff ///< Max of GRA1 Offset

///GRA1 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A1_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A1_CORES;

///GRA1 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A1_NODE_MIN 0 ///< Min of GRA1 Node
#define IDSOPT_DBG_MISC_GR_A1_NODE_MAX 255 ///< Max of GRA1 Node

///GRA1 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A1_CORE_MIN 0 ///< Min of GRA1 Core
#define IDSOPT_DBG_MISC_GR_A1_CORE_MAX 127 ///< Max of GRA1 Core

///GRA1 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_MSR_HIGH_MIN 0 ///< Min of GRA1 MSR Address High
#define IDSOPT_DBG_MISC_GR_A1_MSR_HIGH_MAX 0xffff ///< Max of GRA1 MSR Address High

///GRA1 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_MSR_LOW_MIN 0 ///< Min of GRA1 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A1_MSR_LOW_MAX 0xffff ///< Max of GRA1 MSR Address Low

///GRA1 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A1_MMIO_HIGH_MIN 0 ///< Min of GRA1 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A1_MMIO_HIGH_MAX 0xffff ///< Max of GRA1 MMIO Address High

///GRA1 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A1_MMIO_LOW_MIN 0 ///< Min of GRA1 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A1_MMIO_LOW_MAX 0xffff ///< Max of GRA1 MMIO Address Low

///GRA1 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA1 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA1 PCI Indirect Register Offset[31:16]

///GRA1 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA1 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA1 PCI Indirect Register Offset[15:0]

///GRA1 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT;

///GRA1 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA1 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA1 GMMX Offset[31:16]

///GRA1 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_LOW_MIN 0 ///< Min of GRA1 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA1 GMMX Offset[15:0]

///GRA1 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_SMN_HIGH_MIN 0 ///< Min of GRA1 SMN Address High
#define IDSOPT_DBG_MISC_GR_A1_SMN_HIGH_MAX 0xffff ///< Max of GRA1 SMN Address High

///GRA1 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_SMN_LOW_MIN 0 ///< Min of GRA1 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A1_SMN_LOW_MAX 0xffff ///< Max of GRA1 SMN Address Low

///GRA1 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A1_DF_INSTANCE_MIN 0 ///< Min of GRA1 DF Instance
#define IDSOPT_DBG_MISC_GR_A1_DF_INSTANCE_MAX 0xff ///< Max of GRA1 DF Instance

///GRA1 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHEST_MIN 0 ///< Min of GRA1 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHEST_MAX 0xffff ///< Max of GRA1 Mask Value [63:48]

///GRA1 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHER_MIN 0 ///< Min of GRA1 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHER_MAX 0xffff ///< Max of GRA1 Mask Value [47:32]

///GRA1 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWER_MIN 0 ///< Min of GRA1 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWER_MAX 0xffff ///< Max of GRA1 Mask Value [31:16]

///GRA1 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWEST_MIN 0 ///< Min of GRA1 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWEST_MAX 0xffff ///< Max of GRA1 Mask Value [15:0]

///GRA1 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHEST_MIN 0 ///< Min of GRA1 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHEST_MAX 0xffff ///< Max of GRA1 Or Value [63:48]

///GRA1 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHER_MIN 0 ///< Min of GRA1 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHER_MAX 0xffff ///< Max of GRA1 Or Value [47:32]

///GRA1 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWER_MIN 0 ///< Min of GRA1 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWER_MAX 0xffff ///< Max of GRA1 Or Value [31:16]

///GRA1 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWEST_MIN 0 ///< Min of GRA1 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWEST_MAX 0xffff ///< Max of GRA1 Or Value [15:0]

///GRA Group 2
///Enable or disable GRA Group 2
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A2_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A2_USR_CTL;

///GRA2 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A2_REG_TYPE;

///GRA2 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A2_TIME_POINT;

///GRA2 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A2_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A2_GEN_REG_NODE;

///GRA2 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A2_BUS_MIN 0 ///< Min of GRA2 Bus
#define IDSOPT_DBG_MISC_GR_A2_BUS_MAX 255 ///< Max of GRA2 Bus

///GRA2 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A2_DEV_MIN 0 ///< Min of GRA2 Device
#define IDSOPT_DBG_MISC_GR_A2_DEV_MAX 31 ///< Max of GRA2 Device

///GRA2 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A2_FUN_MIN 0 ///< Min of GRA2 Function
#define IDSOPT_DBG_MISC_GR_A2_FUN_MAX 7 ///< Max of GRA2 Function

///GRA2 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A2_OFFSET_MIN 0 ///< Min of GRA2 Offset
#define IDSOPT_DBG_MISC_GR_A2_OFFSET_MAX 0xfff ///< Max of GRA2 Offset

///GRA2 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A2_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A2_CORES;

///GRA2 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A2_NODE_MIN 0 ///< Min of GRA2 Node
#define IDSOPT_DBG_MISC_GR_A2_NODE_MAX 255 ///< Max of GRA2 Node

///GRA2 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A2_CORE_MIN 0 ///< Min of GRA2 Core
#define IDSOPT_DBG_MISC_GR_A2_CORE_MAX 127 ///< Max of GRA2 Core

///GRA2 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_MSR_HIGH_MIN 0 ///< Min of GRA2 MSR Address High
#define IDSOPT_DBG_MISC_GR_A2_MSR_HIGH_MAX 0xffff ///< Max of GRA2 MSR Address High

///GRA2 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_MSR_LOW_MIN 0 ///< Min of GRA2 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A2_MSR_LOW_MAX 0xffff ///< Max of GRA2 MSR Address Low

///GRA2 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A2_MMIO_HIGH_MIN 0 ///< Min of GRA2 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A2_MMIO_HIGH_MAX 0xffff ///< Max of GRA2 MMIO Address High

///GRA2 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A2_MMIO_LOW_MIN 0 ///< Min of GRA2 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A2_MMIO_LOW_MAX 0xffff ///< Max of GRA2 MMIO Address Low

///GRA2 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA2 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA2 PCI Indirect Register Offset[31:16]

///GRA2 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA2 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA2 PCI Indirect Register Offset[15:0]

///GRA2 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT;

///GRA2 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA2 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA2 GMMX Offset[31:16]

///GRA2 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_LOW_MIN 0 ///< Min of GRA2 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA2 GMMX Offset[15:0]

///GRA2 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_SMN_HIGH_MIN 0 ///< Min of GRA2 SMN Address High
#define IDSOPT_DBG_MISC_GR_A2_SMN_HIGH_MAX 0xffff ///< Max of GRA2 SMN Address High

///GRA2 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_SMN_LOW_MIN 0 ///< Min of GRA2 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A2_SMN_LOW_MAX 0xffff ///< Max of GRA2 SMN Address Low

///GRA2 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A2_DF_INSTANCE_MIN 0 ///< Min of GRA2 DF Instance
#define IDSOPT_DBG_MISC_GR_A2_DF_INSTANCE_MAX 0xff ///< Max of GRA2 DF Instance

///GRA2 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHEST_MIN 0 ///< Min of GRA2 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHEST_MAX 0xffff ///< Max of GRA2 Mask Value [63:48]

///GRA2 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHER_MIN 0 ///< Min of GRA2 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHER_MAX 0xffff ///< Max of GRA2 Mask Value [47:32]

///GRA2 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWER_MIN 0 ///< Min of GRA2 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWER_MAX 0xffff ///< Max of GRA2 Mask Value [31:16]

///GRA2 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWEST_MIN 0 ///< Min of GRA2 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWEST_MAX 0xffff ///< Max of GRA2 Mask Value [15:0]

///GRA2 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHEST_MIN 0 ///< Min of GRA2 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHEST_MAX 0xffff ///< Max of GRA2 Or Value [63:48]

///GRA2 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHER_MIN 0 ///< Min of GRA2 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHER_MAX 0xffff ///< Max of GRA2 Or Value [47:32]

///GRA2 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWER_MIN 0 ///< Min of GRA2 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWER_MAX 0xffff ///< Max of GRA2 Or Value [31:16]

///GRA2 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWEST_MIN 0 ///< Min of GRA2 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWEST_MAX 0xffff ///< Max of GRA2 Or Value [15:0]

///GRA Group 3
///Enable or disable GRA Group 3
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A3_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A3_USR_CTL;

///GRA3 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A3_REG_TYPE;

///GRA3 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A3_TIME_POINT;

///GRA3 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A3_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A3_GEN_REG_NODE;

///GRA3 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A3_BUS_MIN 0 ///< Min of GRA3 Bus
#define IDSOPT_DBG_MISC_GR_A3_BUS_MAX 255 ///< Max of GRA3 Bus

///GRA3 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A3_DEV_MIN 0 ///< Min of GRA3 Device
#define IDSOPT_DBG_MISC_GR_A3_DEV_MAX 31 ///< Max of GRA3 Device

///GRA3 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A3_FUN_MIN 0 ///< Min of GRA3 Function
#define IDSOPT_DBG_MISC_GR_A3_FUN_MAX 7 ///< Max of GRA3 Function

///GRA3 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A3_OFFSET_MIN 0 ///< Min of GRA3 Offset
#define IDSOPT_DBG_MISC_GR_A3_OFFSET_MAX 0xfff ///< Max of GRA3 Offset

///GRA3 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A3_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A3_CORES;

///GRA3 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A3_NODE_MIN 0 ///< Min of GRA3 Node
#define IDSOPT_DBG_MISC_GR_A3_NODE_MAX 255 ///< Max of GRA3 Node

///GRA3 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A3_CORE_MIN 0 ///< Min of GRA3 Core
#define IDSOPT_DBG_MISC_GR_A3_CORE_MAX 127 ///< Max of GRA3 Core

///GRA3 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_MSR_HIGH_MIN 0 ///< Min of GRA3 MSR Address High
#define IDSOPT_DBG_MISC_GR_A3_MSR_HIGH_MAX 0xffff ///< Max of GRA3 MSR Address High

///GRA3 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_MSR_LOW_MIN 0 ///< Min of GRA3 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A3_MSR_LOW_MAX 0xffff ///< Max of GRA3 MSR Address Low

///GRA3 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A3_MMIO_HIGH_MIN 0 ///< Min of GRA3 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A3_MMIO_HIGH_MAX 0xffff ///< Max of GRA3 MMIO Address High

///GRA3 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A3_MMIO_LOW_MIN 0 ///< Min of GRA3 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A3_MMIO_LOW_MAX 0xffff ///< Max of GRA3 MMIO Address Low

///GRA3 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA3 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA3 PCI Indirect Register Offset[31:16]

///GRA3 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA3 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA3 PCI Indirect Register Offset[15:0]

///GRA3 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT;

///GRA3 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA3 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA3 GMMX Offset[31:16]

///GRA3 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_LOW_MIN 0 ///< Min of GRA3 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA3 GMMX Offset[15:0]

///GRA3 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_SMN_HIGH_MIN 0 ///< Min of GRA3 SMN Address High
#define IDSOPT_DBG_MISC_GR_A3_SMN_HIGH_MAX 0xffff ///< Max of GRA3 SMN Address High

///GRA3 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_SMN_LOW_MIN 0 ///< Min of GRA3 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A3_SMN_LOW_MAX 0xffff ///< Max of GRA3 SMN Address Low

///GRA3 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A3_DF_INSTANCE_MIN 0 ///< Min of GRA3 DF Instance
#define IDSOPT_DBG_MISC_GR_A3_DF_INSTANCE_MAX 0xff ///< Max of GRA3 DF Instance

///GRA3 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHEST_MIN 0 ///< Min of GRA3 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHEST_MAX 0xffff ///< Max of GRA3 Mask Value [63:48]

///GRA3 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHER_MIN 0 ///< Min of GRA3 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHER_MAX 0xffff ///< Max of GRA3 Mask Value [47:32]

///GRA3 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWER_MIN 0 ///< Min of GRA3 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWER_MAX 0xffff ///< Max of GRA3 Mask Value [31:16]

///GRA3 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWEST_MIN 0 ///< Min of GRA3 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWEST_MAX 0xffff ///< Max of GRA3 Mask Value [15:0]

///GRA3 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHEST_MIN 0 ///< Min of GRA3 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHEST_MAX 0xffff ///< Max of GRA3 Or Value [63:48]

///GRA3 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHER_MIN 0 ///< Min of GRA3 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHER_MAX 0xffff ///< Max of GRA3 Or Value [47:32]

///GRA3 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWER_MIN 0 ///< Min of GRA3 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWER_MAX 0xffff ///< Max of GRA3 Or Value [31:16]

///GRA3 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWEST_MIN 0 ///< Min of GRA3 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWEST_MAX 0xffff ///< Max of GRA3 Or Value [15:0]

///GRA Group 4
///Enable or disable GRA Group 4
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A4_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A4_USR_CTL;

///GRA4 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A4_REG_TYPE;

///GRA4 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A4_TIME_POINT;

///GRA4 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A4_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A4_GEN_REG_NODE;

///GRA4 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A4_BUS_MIN 0 ///< Min of GRA4 Bus
#define IDSOPT_DBG_MISC_GR_A4_BUS_MAX 255 ///< Max of GRA4 Bus

///GRA4 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A4_DEV_MIN 0 ///< Min of GRA4 Device
#define IDSOPT_DBG_MISC_GR_A4_DEV_MAX 31 ///< Max of GRA4 Device

///GRA4 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A4_FUN_MIN 0 ///< Min of GRA4 Function
#define IDSOPT_DBG_MISC_GR_A4_FUN_MAX 7 ///< Max of GRA4 Function

///GRA4 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A4_OFFSET_MIN 0 ///< Min of GRA4 Offset
#define IDSOPT_DBG_MISC_GR_A4_OFFSET_MAX 0xfff ///< Max of GRA4 Offset

///GRA4 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A4_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A4_CORES;

///GRA4 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A4_NODE_MIN 0 ///< Min of GRA4 Node
#define IDSOPT_DBG_MISC_GR_A4_NODE_MAX 255 ///< Max of GRA4 Node

///GRA4 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A4_CORE_MIN 0 ///< Min of GRA4 Core
#define IDSOPT_DBG_MISC_GR_A4_CORE_MAX 127 ///< Max of GRA4 Core

///GRA4 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_MSR_HIGH_MIN 0 ///< Min of GRA4 MSR Address High
#define IDSOPT_DBG_MISC_GR_A4_MSR_HIGH_MAX 0xffff ///< Max of GRA4 MSR Address High

///GRA4 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_MSR_LOW_MIN 0 ///< Min of GRA4 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A4_MSR_LOW_MAX 0xffff ///< Max of GRA4 MSR Address Low

///GRA4 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A4_MMIO_HIGH_MIN 0 ///< Min of GRA4 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A4_MMIO_HIGH_MAX 0xffff ///< Max of GRA4 MMIO Address High

///GRA4 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A4_MMIO_LOW_MIN 0 ///< Min of GRA4 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A4_MMIO_LOW_MAX 0xffff ///< Max of GRA4 MMIO Address Low

///GRA4 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA4 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA4 PCI Indirect Register Offset[31:16]

///GRA4 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA4 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA4 PCI Indirect Register Offset[15:0]

///GRA4 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT;

///GRA4 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA4 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA4 GMMX Offset[31:16]

///GRA4 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_LOW_MIN 0 ///< Min of GRA4 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA4 GMMX Offset[15:0]

///GRA4 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_SMN_HIGH_MIN 0 ///< Min of GRA4 SMN Address High
#define IDSOPT_DBG_MISC_GR_A4_SMN_HIGH_MAX 0xffff ///< Max of GRA4 SMN Address High

///GRA4 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_SMN_LOW_MIN 0 ///< Min of GRA4 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A4_SMN_LOW_MAX 0xffff ///< Max of GRA4 SMN Address Low

///GRA4 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A4_DF_INSTANCE_MIN 0 ///< Min of GRA4 DF Instance
#define IDSOPT_DBG_MISC_GR_A4_DF_INSTANCE_MAX 0xff ///< Max of GRA4 DF Instance

///GRA4 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHEST_MIN 0 ///< Min of GRA4 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHEST_MAX 0xffff ///< Max of GRA4 Mask Value [63:48]

///GRA4 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHER_MIN 0 ///< Min of GRA4 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHER_MAX 0xffff ///< Max of GRA4 Mask Value [47:32]

///GRA4 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWER_MIN 0 ///< Min of GRA4 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWER_MAX 0xffff ///< Max of GRA4 Mask Value [31:16]

///GRA4 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWEST_MIN 0 ///< Min of GRA4 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWEST_MAX 0xffff ///< Max of GRA4 Mask Value [15:0]

///GRA4 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHEST_MIN 0 ///< Min of GRA4 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHEST_MAX 0xffff ///< Max of GRA4 Or Value [63:48]

///GRA4 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHER_MIN 0 ///< Min of GRA4 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHER_MAX 0xffff ///< Max of GRA4 Or Value [47:32]

///GRA4 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWER_MIN 0 ///< Min of GRA4 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWER_MAX 0xffff ///< Max of GRA4 Or Value [31:16]

///GRA4 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWEST_MIN 0 ///< Min of GRA4 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWEST_MAX 0xffff ///< Max of GRA4 Or Value [15:0]

///GRA Group 5
///Enable or disable GRA Group 5
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A5_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A5_USR_CTL;

///GRA5 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A5_REG_TYPE;

///GRA5 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A5_TIME_POINT;

///GRA5 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A5_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A5_GEN_REG_NODE;

///GRA5 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A5_BUS_MIN 0 ///< Min of GRA5 Bus
#define IDSOPT_DBG_MISC_GR_A5_BUS_MAX 255 ///< Max of GRA5 Bus

///GRA5 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A5_DEV_MIN 0 ///< Min of GRA5 Device
#define IDSOPT_DBG_MISC_GR_A5_DEV_MAX 31 ///< Max of GRA5 Device

///GRA5 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A5_FUN_MIN 0 ///< Min of GRA5 Function
#define IDSOPT_DBG_MISC_GR_A5_FUN_MAX 7 ///< Max of GRA5 Function

///GRA5 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A5_OFFSET_MIN 0 ///< Min of GRA5 Offset
#define IDSOPT_DBG_MISC_GR_A5_OFFSET_MAX 0xfff ///< Max of GRA5 Offset

///GRA5 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A5_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A5_CORES;

///GRA5 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A5_NODE_MIN 0 ///< Min of GRA5 Node
#define IDSOPT_DBG_MISC_GR_A5_NODE_MAX 255 ///< Max of GRA5 Node

///GRA5 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A5_CORE_MIN 0 ///< Min of GRA5 Core
#define IDSOPT_DBG_MISC_GR_A5_CORE_MAX 127 ///< Max of GRA5 Core

///GRA5 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_MSR_HIGH_MIN 0 ///< Min of GRA5 MSR Address High
#define IDSOPT_DBG_MISC_GR_A5_MSR_HIGH_MAX 0xffff ///< Max of GRA5 MSR Address High

///GRA5 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_MSR_LOW_MIN 0 ///< Min of GRA5 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A5_MSR_LOW_MAX 0xffff ///< Max of GRA5 MSR Address Low

///GRA5 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A5_MMIO_HIGH_MIN 0 ///< Min of GRA5 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A5_MMIO_HIGH_MAX 0xffff ///< Max of GRA5 MMIO Address High

///GRA5 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A5_MMIO_LOW_MIN 0 ///< Min of GRA5 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A5_MMIO_LOW_MAX 0xffff ///< Max of GRA5 MMIO Address Low

///GRA5 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA5 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA5 PCI Indirect Register Offset[31:16]

///GRA5 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA5 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA5 PCI Indirect Register Offset[15:0]

///GRA5 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT;

///GRA5 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA5 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA5 GMMX Offset[31:16]

///GRA5 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_LOW_MIN 0 ///< Min of GRA5 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA5 GMMX Offset[15:0]

///GRA5 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_SMN_HIGH_MIN 0 ///< Min of GRA5 SMN Address High
#define IDSOPT_DBG_MISC_GR_A5_SMN_HIGH_MAX 0xffff ///< Max of GRA5 SMN Address High

///GRA5 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_SMN_LOW_MIN 0 ///< Min of GRA5 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A5_SMN_LOW_MAX 0xffff ///< Max of GRA5 SMN Address Low

///GRA5 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A5_DF_INSTANCE_MIN 0 ///< Min of GRA5 DF Instance
#define IDSOPT_DBG_MISC_GR_A5_DF_INSTANCE_MAX 0xff ///< Max of GRA5 DF Instance

///GRA5 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHEST_MIN 0 ///< Min of GRA5 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHEST_MAX 0xffff ///< Max of GRA5 Mask Value [63:48]

///GRA5 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHER_MIN 0 ///< Min of GRA5 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHER_MAX 0xffff ///< Max of GRA5 Mask Value [47:32]

///GRA5 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWER_MIN 0 ///< Min of GRA5 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWER_MAX 0xffff ///< Max of GRA5 Mask Value [31:16]

///GRA5 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWEST_MIN 0 ///< Min of GRA5 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWEST_MAX 0xffff ///< Max of GRA5 Mask Value [15:0]

///GRA5 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHEST_MIN 0 ///< Min of GRA5 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHEST_MAX 0xffff ///< Max of GRA5 Or Value [63:48]

///GRA5 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHER_MIN 0 ///< Min of GRA5 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHER_MAX 0xffff ///< Max of GRA5 Or Value [47:32]

///GRA5 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWER_MIN 0 ///< Min of GRA5 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWER_MAX 0xffff ///< Max of GRA5 Or Value [31:16]

///GRA5 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWEST_MIN 0 ///< Min of GRA5 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWEST_MAX 0xffff ///< Max of GRA5 Or Value [15:0]

///GRA Group 6
///Enable or disable GRA Group 6
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A6_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A6_USR_CTL;

///GRA6 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A6_REG_TYPE;

///GRA6 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A6_TIME_POINT;

///GRA6 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A6_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A6_GEN_REG_NODE;

///GRA6 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A6_BUS_MIN 0 ///< Min of GRA6 Bus
#define IDSOPT_DBG_MISC_GR_A6_BUS_MAX 255 ///< Max of GRA6 Bus

///GRA6 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A6_DEV_MIN 0 ///< Min of GRA6 Device
#define IDSOPT_DBG_MISC_GR_A6_DEV_MAX 31 ///< Max of GRA6 Device

///GRA6 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A6_FUN_MIN 0 ///< Min of GRA6 Function
#define IDSOPT_DBG_MISC_GR_A6_FUN_MAX 7 ///< Max of GRA6 Function

///GRA6 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A6_OFFSET_MIN 0 ///< Min of GRA6 Offset
#define IDSOPT_DBG_MISC_GR_A6_OFFSET_MAX 0xfff ///< Max of GRA6 Offset

///GRA6 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A6_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A6_CORES;

///GRA6 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A6_NODE_MIN 0 ///< Min of GRA6 Node
#define IDSOPT_DBG_MISC_GR_A6_NODE_MAX 255 ///< Max of GRA6 Node

///GRA6 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A6_CORE_MIN 0 ///< Min of GRA6 Core
#define IDSOPT_DBG_MISC_GR_A6_CORE_MAX 127 ///< Max of GRA6 Core

///GRA6 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_MSR_HIGH_MIN 0 ///< Min of GRA6 MSR Address High
#define IDSOPT_DBG_MISC_GR_A6_MSR_HIGH_MAX 0xffff ///< Max of GRA6 MSR Address High

///GRA6 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_MSR_LOW_MIN 0 ///< Min of GRA6 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A6_MSR_LOW_MAX 0xffff ///< Max of GRA6 MSR Address Low

///GRA6 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A6_MMIO_HIGH_MIN 0 ///< Min of GRA6 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A6_MMIO_HIGH_MAX 0xffff ///< Max of GRA6 MMIO Address High

///GRA6 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A6_MMIO_LOW_MIN 0 ///< Min of GRA6 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A6_MMIO_LOW_MAX 0xffff ///< Max of GRA6 MMIO Address Low

///GRA6 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA6 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA6 PCI Indirect Register Offset[31:16]

///GRA6 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA6 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA6 PCI Indirect Register Offset[15:0]

///GRA6 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT;

///GRA6 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA6 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA6 GMMX Offset[31:16]

///GRA6 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_LOW_MIN 0 ///< Min of GRA6 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA6 GMMX Offset[15:0]

///GRA6 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_SMN_HIGH_MIN 0 ///< Min of GRA6 SMN Address High
#define IDSOPT_DBG_MISC_GR_A6_SMN_HIGH_MAX 0xffff ///< Max of GRA6 SMN Address High

///GRA6 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_SMN_LOW_MIN 0 ///< Min of GRA6 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A6_SMN_LOW_MAX 0xffff ///< Max of GRA6 SMN Address Low

///GRA6 DF Instance
#define IDSOPT_DBG_MISC_GR_A6_DF_INSTANCE_MIN 0 ///< Min of GRA6 DF Instance
#define IDSOPT_DBG_MISC_GR_A6_DF_INSTANCE_MAX 0xff ///< Max of GRA6 DF Instance

///GRA6 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHEST_MIN 0 ///< Min of GRA6 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHEST_MAX 0xffff ///< Max of GRA6 Mask Value [63:48]

///GRA6 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHER_MIN 0 ///< Min of GRA6 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHER_MAX 0xffff ///< Max of GRA6 Mask Value [47:32]

///GRA6 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWER_MIN 0 ///< Min of GRA6 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWER_MAX 0xffff ///< Max of GRA6 Mask Value [31:16]

///GRA6 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWEST_MIN 0 ///< Min of GRA6 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWEST_MAX 0xffff ///< Max of GRA6 Mask Value [15:0]

///GRA6 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHEST_MIN 0 ///< Min of GRA6 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHEST_MAX 0xffff ///< Max of GRA6 Or Value [63:48]

///GRA6 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHER_MIN 0 ///< Min of GRA6 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHER_MAX 0xffff ///< Max of GRA6 Or Value [47:32]

///GRA6 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWER_MIN 0 ///< Min of GRA6 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWER_MAX 0xffff ///< Max of GRA6 Or Value [31:16]

///GRA6 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWEST_MIN 0 ///< Min of GRA6 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWEST_MAX 0xffff ///< Max of GRA6 Or Value [15:0]


#endif //_IDS_NV_INT_DEF_SSP_H_
