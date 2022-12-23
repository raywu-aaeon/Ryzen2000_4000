/**
 * @file
 *
 * SMU Features enablement
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#ifndef _SMU_FEATURES_ENABLE_H_
#define _SMU_FEATURES_ENABLE_H_

#include <smu10.h>

#define SMU_FEATURES_ENABLE_DEFAULT (1 << FEATURE_CCLK_CONTROLLER_BIT) | \
                                    (1 << FEATURE_FAN_CONTROLLER_BIT) | \
                                    (1 << FEATURE_DATA_CALCULATION_BIT) | \
                                    (1 << FEATURE_PPT_BIT) | \
                                    (1 << FEATURE_TDC_BIT) | \
                                    (1 << FEATURE_THERMAL_BIT) | \
                                    (1 << FEATURE_FIT_BIT) | \
                                    (1 << FEATURE_EDC_BIT) | \
                                    (1 << FEATURE_PLL_POWER_DOWN_BIT) | \
                                    (1 << FEATURE_ULV_BIT) | \
                                    (1 << FEATURE_VDDOFF_BIT) | \
                                    (1 << FEATURE_VCN_DPM_BIT) | \
                                    (1 << FEATURE_ACP_DPM_BIT) | \
                                    (1 << FEATURE_ISP_DPM_BIT) | \
                                    (1 << FEATURE_FCLK_DPM_BIT) | \
                                    (1 << FEATURE_SOCCLK_DPM_BIT) | \
                                    (1 << FEATURE_MP0CLK_DPM_BIT) | \
                                    (1 << FEATURE_LCLK_DPM_BIT) | \
                                    (1 << FEATURE_SHUBCLK_DPM_BIT) | \
                                    (1 << FEATURE_DCEFCLK_DPM_BIT) | \
                                    (1 << FEATURE_GFX_DPM_BIT) | \
                                    (1 << FEATURE_DS_GFXCLK_BIT) | \
                                    (1 << FEATURE_DS_SOCCLK_BIT) | \
                                    (1 << FEATURE_DS_LCLK_BIT) | \
                                    (1 << FEATURE_DS_DCEFCLK_BIT) | \
                                    (1 << FEATURE_DS_SHUBCLK_BIT) | \
                                    (1 << FEATURE_RM_BIT) | \
                                    (0 << FEATURE_S0i2_BIT) | \
                                    (1 << FEATURE_WHISPER_MODE_BIT) | \
                                    (1 << FEATURE_DS_FCLK_BIT) | \
                                    (1 << FEATURE_DS_SMNCLK_BIT) | \
                                    (1 << FEATURE_DS_MP1CLK_BIT)

#define SMU_FEATURES_ENABLE_EXT_DEFAULT  (1 << (FEATURE_DS_MP0CLK_BIT % 32)) | \
                                         (1 << (FEATURE_MGCG_BIT % 32)) | \
                                         (1 << (FEATURE_DS_FUSE_SRAM_BIT % 32)) | \
                                         (0 << (FEATURE_GFX_CKS % 32)) | \
                                         (1 << (FEATURE_PSI0_BIT % 32)) | \
                                         (1 << (FEATURE_PROCHOT_BIT % 32)) | \
                                         (1 << (FEATURE_CPUOFF_BIT % 32)) | \
                                         (1 << (FEATURE_STAPM_BIT % 32)) | \
                                         (1 << (FEATURE_CORE_CSTATES_BIT % 32)) | \
                                         (0 << (FEATURE_GFX_DUTY_CYCLE_BIT % 32)) | \
                                         (0 << (FEATURE_AA_MODE_BIT % 32)) | \
                                         (0 << (FEATURE_S0i3_EN_BIT % 32))

#define RV2_SMU_FEATURES_ENABLE_DEFAULT (1 << FEATURE_CCLK_CONTROLLER_BIT) | \
                                        (1 << FEATURE_FAN_CONTROLLER_BIT) | \
                                        (1 << FEATURE_DATA_CALCULATION_BIT) | \
                                        (1 << FEATURE_PPT_BIT) | \
                                        (1 << FEATURE_TDC_BIT) | \
                                        (1 << FEATURE_THERMAL_BIT) | \
                                        (1 << FEATURE_FIT_BIT) | \
                                        (1 << FEATURE_EDC_BIT) | \
                                        (1 << FEATURE_PLL_POWER_DOWN_BIT) | \
                                        (1 << FEATURE_ULV_BIT) | \
                                        (1 << FEATURE_VDDOFF_BIT) | \
                                        (1 << FEATURE_VCN_DPM_BIT) | \
                                        (1 << FEATURE_ACP_DPM_BIT) | \
                                        (1 << FEATURE_ISP_DPM_BIT) | \
                                        (1 << FEATURE_FCLK_DPM_BIT) | \
                                        (1 << FEATURE_SOCCLK_DPM_BIT) | \
                                        (1 << FEATURE_MP0CLK_DPM_BIT) | \
                                        (1 << FEATURE_LCLK_DPM_BIT) | \
                                        (1 << FEATURE_SHUBCLK_DPM_BIT) | \
                                        (1 << FEATURE_DCEFCLK_DPM_BIT) | \
                                        (1 << FEATURE_GFX_DPM_BIT) | \
                                        (1 << FEATURE_DS_GFXCLK_BIT) | \
                                        (1 << FEATURE_DS_SOCCLK_BIT) | \
                                        (1 << FEATURE_DS_LCLK_BIT) | \
                                        (1 << FEATURE_DS_DCEFCLK_BIT) | \
                                        (1 << FEATURE_DS_SHUBCLK_BIT) | \
                                        (1 << FEATURE_RM_BIT) | \
                                        (0 << FEATURE_S0i2_BIT) | \
                                        (1 << FEATURE_WHISPER_MODE_BIT) | \
                                        (1 << FEATURE_DS_FCLK_BIT) | \
                                        (1 << FEATURE_DS_SMNCLK_BIT) | \
                                        (1 << FEATURE_DS_MP1CLK_BIT)

#define RV2_SMU_FEATURES_ENABLE_EXT_DEFAULT  (1 << (FEATURE_DS_MP0CLK_BIT % 32)) | \
                                             (1 << (FEATURE_MGCG_BIT % 32)) | \
                                             (1 << (FEATURE_DS_FUSE_SRAM_BIT % 32)) | \
                                             (0 << (FEATURE_GFX_CKS % 32)) | \
                                             (1 << (FEATURE_PSI0_BIT % 32)) | \
                                             (1 << (FEATURE_PROCHOT_BIT % 32)) | \
                                             (1 << (FEATURE_CPUOFF_BIT % 32)) | \
                                             (1 << (FEATURE_STAPM_BIT % 32)) | \
                                             (1 << (FEATURE_CORE_CSTATES_BIT % 32)) | \
                                             (0 << (FEATURE_GFX_DUTY_CYCLE_BIT % 32)) | \
                                             (0 << (FEATURE_AA_MODE_BIT % 32)) | \
                                             (0 << (FEATURE_LIVMIN_BIT % 32)) | \
                                             (0 << (FEATURE_RLC_PACE_BIT % 32))

#define PCO_SMU_FEATURES_ENABLE_DEFAULT (1 << FEATURE_CCLK_CONTROLLER_BIT) | \
                                        (1 << FEATURE_FAN_CONTROLLER_BIT) | \
                                        (1 << FEATURE_DATA_CALCULATION_BIT) | \
                                        (1 << FEATURE_PPT_BIT) | \
                                        (1 << FEATURE_TDC_BIT) | \
                                        (1 << FEATURE_THERMAL_BIT) | \
                                        (1 << FEATURE_FIT_BIT) | \
                                        (1 << FEATURE_EDC_BIT) | \
                                        (1 << FEATURE_PLL_POWER_DOWN_BIT) | \
                                        (1 << FEATURE_ULV_BIT) | \
                                        (1 << FEATURE_VDDOFF_BIT) | \
                                        (1 << FEATURE_VCN_DPM_BIT) | \
                                        (1 << FEATURE_ACP_DPM_BIT) | \
                                        (1 << FEATURE_ISP_DPM_BIT) | \
                                        (1 << FEATURE_FCLK_DPM_BIT) | \
                                        (1 << FEATURE_SOCCLK_DPM_BIT) | \
                                        (1 << FEATURE_MP0CLK_DPM_BIT) | \
                                        (1 << FEATURE_LCLK_DPM_BIT) | \
                                        (1 << FEATURE_SHUBCLK_DPM_BIT) | \
                                        (1 << FEATURE_DCEFCLK_DPM_BIT) | \
                                        (1 << FEATURE_GFX_DPM_BIT) | \
                                        (1 << FEATURE_DS_GFXCLK_BIT) | \
                                        (1 << FEATURE_DS_SOCCLK_BIT) | \
                                        (1 << FEATURE_DS_LCLK_BIT) | \
                                        (1 << FEATURE_DS_DCEFCLK_BIT) | \
                                        (1 << FEATURE_DS_SHUBCLK_BIT) | \
                                        (1 << FEATURE_RM_BIT) | \
                                        (0 << FEATURE_S0i2_BIT) | \
                                        (1 << FEATURE_WHISPER_MODE_BIT) | \
                                        (1 << FEATURE_DS_FCLK_BIT) | \
                                        (1 << FEATURE_DS_SMNCLK_BIT) | \
                                        (1 << FEATURE_DS_MP1CLK_BIT)

#define PCO_SMU_FEATURES_ENABLE_EXT_DEFAULT  (1 << (FEATURE_DS_MP0CLK_BIT % 32)) | \
                                             (1 << (FEATURE_MGCG_BIT % 32)) | \
                                             (1 << (FEATURE_DS_FUSE_SRAM_BIT % 32)) | \
                                             (0 << (FEATURE_GFX_CKS % 32)) | \
                                             (1 << (FEATURE_PSI0_BIT % 32)) | \
                                             (1 << (FEATURE_PROCHOT_BIT % 32)) | \
                                             (1 << (FEATURE_CPUOFF_BIT % 32)) | \
                                             (1 << (FEATURE_STAPM_BIT % 32)) | \
                                             (1 << (FEATURE_CORE_CSTATES_BIT % 32)) | \
                                             (0 << (FEATURE_GFX_DUTY_CYCLE_BIT % 32)) | \
                                             (0 << (FEATURE_AA_MODE_BIT % 32)) | \
                                             (0 << (FEATURE_S0i3_EN_BIT % 32)) | \
                                             (0 << (FEATURE_OSCSTATE_BIT % 32))

#define AM4_SMU_FEATURES_ENABLE_DEFAULT (1 << FEATURE_CCLK_CONTROLLER_BIT) | \
                                        (1 << FEATURE_FAN_CONTROLLER_BIT) | \
                                        (1 << FEATURE_DATA_CALCULATION_BIT) | \
                                        (1 << FEATURE_PPT_BIT) | \
                                        (1 << FEATURE_TDC_BIT) | \
                                        (1 << FEATURE_THERMAL_BIT) | \
                                        (1 << FEATURE_FIT_BIT) | \
                                        (1 << FEATURE_EDC_BIT) | \
                                        (1 << FEATURE_PLL_POWER_DOWN_BIT) | \
                                        (1 << FEATURE_ULV_BIT) | \
                                        (1 << FEATURE_VDDOFF_BIT) | \
                                        (1 << FEATURE_VCN_DPM_BIT) | \
                                        (1 << FEATURE_ACP_DPM_BIT) | \
                                        (1 << FEATURE_ISP_DPM_BIT) | \
                                        (1 << FEATURE_FCLK_DPM_BIT) | \
                                        (1 << FEATURE_SOCCLK_DPM_BIT) | \
                                        (1 << FEATURE_MP0CLK_DPM_BIT) | \
                                        (1 << FEATURE_LCLK_DPM_BIT) | \
                                        (1 << FEATURE_SHUBCLK_DPM_BIT) | \
                                        (1 << FEATURE_DCEFCLK_DPM_BIT) | \
                                        (1 << FEATURE_GFX_DPM_BIT) | \
                                        (1 << FEATURE_DS_GFXCLK_BIT) | \
                                        (1 << FEATURE_DS_SOCCLK_BIT) | \
                                        (1 << FEATURE_DS_LCLK_BIT) | \
                                        (1 << FEATURE_DS_DCEFCLK_BIT) | \
                                        (1 << FEATURE_DS_SHUBCLK_BIT) | \
                                        (1 << FEATURE_RM_BIT) | \
                                        (0 << FEATURE_S0i2_BIT) | \
                                        (0 << FEATURE_WHISPER_MODE_BIT) | \
                                        (1 << FEATURE_DS_FCLK_BIT) | \
                                        (1 << FEATURE_DS_SMNCLK_BIT) | \
                                        (1 << FEATURE_DS_MP1CLK_BIT)

#define AM4_SMU_FEATURES_ENABLE_EXT_DEFAULT  (1 << (FEATURE_DS_MP0CLK_BIT % 32)) | \
                                             (1 << (FEATURE_MGCG_BIT % 32)) | \
                                             (1 << (FEATURE_DS_FUSE_SRAM_BIT % 32)) | \
                                             (0 << (FEATURE_GFX_CKS % 32)) | \
                                             (1 << (FEATURE_PSI0_BIT % 32)) | \
                                             (1 << (FEATURE_PROCHOT_BIT % 32)) | \
                                             (1 << (FEATURE_CPUOFF_BIT % 32)) | \
                                             (1 << (FEATURE_STAPM_BIT % 32)) | \
                                             (1 << (FEATURE_CORE_CSTATES_BIT % 32)) | \
                                             (0 << (FEATURE_GFX_DUTY_CYCLE_BIT % 32)) | \
                                             (0 << (FEATURE_AA_MODE_BIT % 32))
#endif

