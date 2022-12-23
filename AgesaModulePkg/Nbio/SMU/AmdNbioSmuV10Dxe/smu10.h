/* $NoKeywords:$ */
/**
 * @file
 *
 * Contains the definition of the SMU10
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: Nbio/SMU
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
#ifndef SMU10_H_
#define SMU10_H_

//#include <stdint.h>
//#include <features/smu_features.h>

#pragma pack(push, 1)

#define ENABLE_DEBUG_FEATURES


// Feature Control Defines
#define FEATURE_CCLK_CONTROLLER_BIT   0
#define FEATURE_FAN_CONTROLLER_BIT    1
#define FEATURE_DATA_CALCULATION_BIT  2
#define FEATURE_PPT_BIT               3
#define FEATURE_TDC_BIT               4
#define FEATURE_THERMAL_BIT           5
#define FEATURE_FIT_BIT               6
#define FEATURE_EDC_BIT               7
#define FEATURE_PLL_POWER_DOWN_BIT    8
#define FEATURE_ULV_BIT               9
#define FEATURE_VDDOFF_BIT            10
#define FEATURE_VCN_DPM_BIT           11
#define FEATURE_ACP_DPM_BIT           12
#define FEATURE_ISP_DPM_BIT           13
#define FEATURE_FCLK_DPM_BIT          14
#define FEATURE_SOCCLK_DPM_BIT        15
#define FEATURE_MP0CLK_DPM_BIT        16
#define FEATURE_LCLK_DPM_BIT          17
#define FEATURE_SHUBCLK_DPM_BIT       18
#define FEATURE_DCEFCLK_DPM_BIT       19
#define FEATURE_GFX_DPM_BIT           20
#define FEATURE_DS_GFXCLK_BIT         21
#define FEATURE_DS_SOCCLK_BIT         22
#define FEATURE_DS_LCLK_BIT           23
#define FEATURE_DS_DCEFCLK_BIT        24
#define FEATURE_DS_SHUBCLK_BIT        25
#define FEATURE_RM_BIT                26
#define FEATURE_S0i2_BIT              27
#define FEATURE_WHISPER_MODE_BIT      28
#define FEATURE_DS_FCLK_BIT           29
#define FEATURE_DS_SMNCLK_BIT         30
#define FEATURE_DS_MP1CLK_BIT         31
#define FEATURE_DS_MP0CLK_BIT         32
#define FEATURE_MGCG_BIT              33
#define FEATURE_DS_FUSE_SRAM_BIT      34
#define FEATURE_GFX_CKS               35
#define FEATURE_PSI0_BIT              36
#define FEATURE_PROCHOT_BIT           37
#define FEATURE_CPUOFF_BIT            38
#define FEATURE_STAPM_BIT             39
#define FEATURE_CORE_CSTATES_BIT      40
#define FEATURE_GFX_DUTY_CYCLE_BIT    41
#define FEATURE_AA_MODE_BIT           42
#define FEATURE_LIVMIN_BIT            43  //RV2
#define FEATURE_RLC_PACE_BIT          44  //RV2
#define FEATURE_S0i3_EN_BIT           45  //S0i3 PICASSO
#define FEATURE_OSCSTATE_BIT          46
#define FEATURE_SPARE_47_BIT          47
#define FEATURE_SPARE_48_BIT          48
#define FEATURE_SPARE_49_BIT          49
#define FEATURE_SPARE_50_BIT          50
#define FEATURE_SPARE_51_BIT          51
#define FEATURE_SPARE_52_BIT          52
#define FEATURE_SPARE_53_BIT          53
#define FEATURE_SPARE_54_BIT          54
#define FEATURE_SPARE_55_BIT          55
#define FEATURE_SPARE_56_BIT          56
#define FEATURE_SPARE_57_BIT          57
#define FEATURE_SPARE_58_BIT          58
#define FEATURE_SPARE_59_BIT          59
#define FEATURE_SPARE_60_BIT          60
#define FEATURE_SPARE_61_BIT          61
#define FEATURE_SPARE_62_BIT          62
#define FEATURE_SPARE_63_BIT          63

#define NUM_FEATURES                  64

#define FEATURE_CCLK_CONTROLLER_MASK  (1 << FEATURE_CCLK_CONTROLLER_BIT   )
#define FEATURE_FAN_CONTROLLER_MASK   (1 << FEATURE_FAN_CONTROLLER_BIT    )
#define FEATURE_DATA_CALCULATION_MASK (1 << FEATURE_DATA_CALCULATION_BIT  )
#define FEATURE_PPT_MASK              (1 << FEATURE_PPT_BIT               )
#define FEATURE_TDC_MASK              (1 << FEATURE_TDC_BIT               )
#define FEATURE_THERMAL_MASK          (1 << FEATURE_THERMAL_BIT           )
#define FEATURE_FIT_MASK              (1 << FEATURE_FIT_BIT               )
#define FEATURE_EDC_MASK              (1 << FEATURE_EDC_BIT               )
#define FEATURE_PLL_POWER_DOWN_MASK   (1 << FEATURE_PLL_POWER_DOWN_BIT    )
#define FEATURE_ULV_MASK              (1 << FEATURE_ULV_BIT               )
#define FEATURE_VDDOFF_MASK           (1 << FEATURE_VDDOFF_BIT            )
#define FEATURE_VCN_DPM_MASK          (1 << FEATURE_VCN_DPM_BIT           )
#define FEATURE_ACP_DPM_MASK          (1 << FEATURE_ACP_DPM_BIT           )
#define FEATURE_ISP_DPM_MASK          (1 << FEATURE_ISP_DPM_BIT           )
#define FEATURE_FCLK_DPM_MASK         (1 << FEATURE_FCLK_DPM_BIT          )
#define FEATURE_SOCCLK_DPM_MASK       (1 << FEATURE_SOCCLK_DPM_BIT        )
#define FEATURE_MP0CLK_DPM_MASK       (1 << FEATURE_MP0CLK_DPM_BIT        )
#define FEATURE_LCLK_DPM_MASK         (1 << FEATURE_LCLK_DPM_BIT          )
#define FEATURE_SHUBCLK_DPM_MASK      (1 << FEATURE_SHUBCLK_DPM_BIT       )
#define FEATURE_DCEFCLK_DPM_MASK      (1 << FEATURE_DCEFCLK_DPM_BIT       )
#define FEATURE_GFX_DPM_MASK          (1 << FEATURE_GFX_DPM_BIT           )
#define FEATURE_DS_GFXCLK_MASK        (1 << FEATURE_DS_GFXCLK_BIT         )
#define FEATURE_DS_SOCCLK_MASK        (1 << FEATURE_DS_SOCCLK_BIT         )
#define FEATURE_DS_LCLK_MASK          (1 << FEATURE_DS_LCLK_BIT           )
#define FEATURE_DS_DCEFCLK_MASK       (1 << FEATURE_DS_DCEFCLK_BIT        )
#define FEATURE_DS_SHUBCLK_MASK       (1 << FEATURE_DS_SHUBCLK_BIT        )
#define FEATURE_RM_MASK               (1 << FEATURE_RM_BIT                )
#define FEATURE_DS_FCLK_MASK          (1 << FEATURE_DS_FCLK_BIT           )
#define FEATURE_DS_SMNCLK_MASK        (1 << FEATURE_DS_SMNCLK_BIT         )
#define FEATURE_DS_MP1CLK_MASK        (1 << FEATURE_DS_MP1CLK_BIT         )
#define FEATURE_DS_MP0CLK_MASK        (1 << (FEATURE_DS_MP0CLK_BIT    - 32))
#define FEATURE_MGCG_MASK             (1 << (FEATURE_MGCG_BIT         - 32))
#define FEATURE_DS_FUSE_SRAM_MASK     (1 << (FEATURE_DS_FUSE_SRAM_BIT - 32))
#define FEATURE_PSI0_MASK             (1 << (FEATURE_PSI0_BIT         - 32))
#define FEATURE_STAPM_MASK            (1 << (FEATURE_STAPM_BIT        - 32))
#define FEATURE_PROCHOT_MASK          (1 << (FEATURE_PROCHOT_BIT      - 32))
#define FEATURE_CPUOFF_MASK           (1 << (FEATURE_CPUOFF_BIT       - 32))
#define FEATURE_CORE_CSTATES_MASK     (1 << (FEATURE_CORE_CSTATES_BIT - 32))
#define FEATURE_GFX_DUTY_CYCLE_MASK   (1 << (FEATURE_GFX_DUTY_CYCLE_BIT - 32))
#define FEATURE_AA_MODE_MASK          (1 << (FEATURE_AA_MODE_BIT      - 32))
#define FEATURE_LIVMIN_MASK           (1 << (FEATURE_LIVMIN_BIT       - 32))
#define FEATURE_RLC_PACE_MASK         (1 << (FEATURE_RLC_PACE_BIT     - 32))
#define FEATURE_S0i3_EN_MASK          (1 << (FEATURE_S0i3_EN_BIT      - 32))
#define FEATURE_OSCSTATE_MASK         (1 << (FEATURE_OSCSTATE_BIT     - 32))

#define TABLE_PPTABLE            0

// Workload bits
#define WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 0
#define WORKLOAD_PPLIB_VIDEO_BIT          2
#define WORKLOAD_PPLIB_VR_BIT             3
#define WORKLOAD_PPLIB_COMPUTE_BIT        4
#define WORKLOAD_PPLIB_CUSTOM_BIT         5
#define WORKLOAD_PPLIB_COUNT              6

/// @todo Style_Analyzer: Add Doxygen comment to struct construct
struct SMU10_Firmware_Footer {
  UINT32 Signature;    ///<
};
typedef struct SMU10_Firmware_Footer SMU10_Firmware_Footer;

/// @todo Style_Analyzer: Add Doxygen comment to struct construct
typedef struct {
  UINT32  ImageVersion;  ///<
  UINT32  ImageVersion2; // This is repeated because DW0 cannot be written in SRAM due to HW bug.
  UINT32  Padding0[3];
  UINT32  SizeFWSigned;
  UINT32  Padding1[25];
  UINT32  FirmwareType;
  UINT32  Filler[32];    ///<
} SMU_Firmware_Header;

/// @todo Style_Analyzer: Add Doxygen comment to struct construct
typedef struct {
  // MP1_EXT_SCRATCH0
  UINT32 CurrLevel_ACP     : 4;                ///<
  UINT32 CurrLevel_ISP     : 4;                ///<
  UINT32 CurrLevel_VCN     : 4;                ///<
  UINT32 CurrLevel_LCLK    : 4;                ///<
  UINT32 CurrLevel_MP0CLK  : 4;                ///<
  UINT32 CurrLevel_FCLK    : 4;                ///<
  UINT32 CurrLevel_SOCCLK  : 4;                ///<
  UINT32 CurrLevel_DCEFCLK : 4;                ///<
  // MP1_EXT_SCRATCH1
  UINT32 TargLevel_ACP     : 4;                ///<
  UINT32 TargLevel_ISP     : 4;                ///<
  UINT32 TargLevel_VCN     : 4;                ///<
  UINT32 TargLevel_LCLK    : 4;                ///<
  UINT32 TargLevel_MP0CLK  : 4;                ///<
  UINT32 TargLevel_FCLK    : 4;                ///<
  UINT32 TargLevel_SOCCLK  : 4;                ///<
  UINT32 TargLevel_DCEFCLK : 4;                ///<
  // MP1_EXT_SCRATCH2
  UINT32 CurrLevel_SHUBCLK  : 4;               ///<
  UINT32 TargLevel_SHUBCLK  : 4;               ///<
  UINT32 InUlv              : 1;               ///<
  UINT32 InS0i2             : 1;               ///<
  UINT32 InWhisperMode      : 1;               ///<
  UINT32 GfxOn              : 1;               ///<
  UINT32 RsmuCalBusyDpmIndex: 8;
  UINT32 DpmHandlerId       : 8;
  UINT32 DpmTimerId         : 4;
  // MP1_EXT_SCRATCH3
  UINT32 ReadWriteSmnRegAddr: 32;
  // MP1_EXT_SCRATCH4
  UINT32 InLivMin           : 1;
  UINT32 Reserved           : 31;
  // MP1_EXT_SCRATCH5
  UINT32 FeatureStatus[NUM_FEATURES / 32];     ///<
} FwStatus_t;

#define TABLE_BIOS_IF            0 // Called by BIOS
#define TABLE_WATERMARKS         1 // Called by Driver
#define TABLE_CUSTOM_DPM         2 // Called by Driver
#define TABLE_PMSTATUSLOG        3 // Called by Tools for Agm logging
#define TABLE_DPMCLOCKS          4 // Called by Driver
#define TABLE_MOMENTARY_PM       5 // Called by Tools
#define TABLE_MODERN_STDBY       6 // Called by Tools for Modern Standby Log
#define TABLE_SMU_METRICS        7 // Called by Driver
#define TABLE_COUNT              8

#pragma pack(pop)

#endif

