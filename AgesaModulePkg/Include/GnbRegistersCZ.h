/* $NoKeywords:$ */
/**
 * @file
 *
 * AGESA gnb file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
 ******************************************************************************
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
#ifndef _GNBREGISTERSCZ_H_
#define _GNBREGISTERSCZ_H_
#define  TYPE_D0F0                  0x1
#define  TYPE_D0F0x64               0x2
#define  TYPE_D0F0x98               0x3
#define  TYPE_D0F0xBC               0x4
#define  TYPE_D0F0xE4               0x5
#define  TYPE_DxF0                  0x6
#define  TYPE_DxF0xE4               0x7
#define  TYPE_D0F2                  0x8
#define  TYPE_D0F2xF4               0x9
#define  TYPE_D0F2xFC               0xa
#define  TYPE_D18F1                 0xb
#define  TYPE_D18F2                 0xc
#define  TYPE_D18F3                 0xd
#define  TYPE_D18F4                 0xe
#define  TYPE_D18F5                 0xf
#define  TYPE_MSR                   0x10
#define  TYPE_D1F0                  0x11
#define  TYPE_GMM                   0x12
#define  TYPE_D1F1                  0x13
#define  TYPE_D18F2_dct0            0x14
#define  TYPE_D18F2_dct1            0x15
//#define  TYPE_D18F2_dct2            0x16
//#define  TYPE_D18F2_dct3            0x17
#define  TYPE_D18F2_dct0_mp0        0x18
#define  TYPE_D18F2_dct0_mp1        0x19
#define  TYPE_D18F2_dct1_mp0        0x1a
#define  TYPE_D18F2_dct1_mp1        0x1b
//#define  TYPE_D18F2_dct2_mp0        0x1c
//#define  TYPE_D18F2_dct2_mp1        0x1d
//#define  TYPE_D18F2_dct3_mp0        0x1e
//#define  TYPE_D18F2_dct3_mp1        0x1f
#define  TYPE_CGIND                 0x20
#define  TYPE_SMU_MSG               0x21
#define  TYPE_D0F0xD4               0x22
#define  TYPE_D0F0xFC               0x23
#define  TYPE_D18F0                 0x24
#define  TYPE_D8F0xEC               0x25
#define  TYPE_D9F2                  0x26
#define  TYPE_D9F2xEC               0x27
#define  TYPE_D9F2xF4               0x28
#define  TYPE_D0F0xC4               0x29

#ifndef WRAP_SPACE1
  #define  WRAP_SPACE1(w, x)   (0x01300000 | (w << 16) | (x))
#endif
#ifndef WRAP_SPACE2
  #define  WRAP_SPACE2(w, x)   (0x01500000 | (w << 16) | (x))
#endif
#ifndef WRAP_SPACE
//0~C  45,46,50, 80,  800~805, 813, 900~905, 913, A00~A05, A13, B00~B05, B13, C00~C05, C13  8030~8036   F000~F004
#define  WRAP_SPACE(w, x)   (( (x <= 0xC) || (x == 0x45) || (x == 0x46) || (x == 0x50) || (x == 0x80) || \
                              ((x >= 0x800) && (x <= 0x805)) || (x == 0x813) || \
                              ((x >= 0x900) && (x <= 0x905)) || (x == 0x913) || \
                              ((x >= 0xA00) && (x <= 0xA05)) || (x == 0xA13) || \
                              ((x >= 0xB00) && (x <= 0xB05)) || (x == 0xB13) || \
                              ((x >= 0xC00) && (x <= 0xC05)) || (x == 0xC13) || \
                              ((x >= 0x8030) && (x <= 0x8036)) || \
                              ((x >= 0xF000) && (x <= 0xF004)) ) ? WRAP_SPACE2(w, x) : WRAP_SPACE1(w, x))
#endif
#ifndef CORE_SPACE
  #define  CORE_SPACE(c, x)   (0x01400000 | (c << 16) | (x))
#endif
#ifndef PHY_SPACE
  #define  PHY_SPACE(w, p, x) (0x00200000 | ((p + 1) << 24) | (w << 16) | (x))
#endif
#ifndef PIF_SPACE
  #define  PIF_SPACE(w, p, x) (0x00100000 | ((p + 1) << 24) | (w << 16) | (x))
#endif

#define SMU_MSG_TYPE                            TYPE_SMU_MSG

#define SMC_MSG_TEST                            0x1
#define SMC_MSG_PHY_LN_OFF                      0x2
#define SMC_MSG_PHY_LN_ON                       0x3
#define SMC_MSG_PWR_OFF_x16                     0xff//0x8
#define SMC_MSG_RECONFIGURE_SB                  0x19
#define SMC_MSG_VddNbRequest                    0x3A
#define SMC_MSG_VddGfxRequest                   0xff//0x3B
#define SMC_MSG_SetLclkSoftMin                  0xff//0x4C
#define SMC_MSG_SetLclkSoftMax                  0xff//0x4D
#define SMC_MSG_SetLclkHardMin                  0xff//0x4E
#define SMC_MSG_SetLclkHardMax                  0xff//0x4F
#define SMC_MSG_PowerDownGpu                    0x55
#define SMC_MSG_PowerUpGpu                      0xff//0x56
#define SMC_MSG_EnableAllSmuFeatures            0x5F
#define SMC_MSG_DisableAllSmuFeatures           0x60
#define SMC_MSG_PowerSourceAC                   0xff//0x61
#define SMC_MSG_PowerSourceDC                   0xff//0x62
#define SMC_MSG_LoadPort80MonitorParameters     0x65
#define SMC_MSG_LoadSystemConfigParameters      0x66
#define SMC_MSG_LoadTdcLimitParameters          0x67
#define SMC_MSG_LoadMemoryParameters            0x68
#define SMC_MSG_LoadCTdpParameters              0x69
#define SMC_MSG_LoadPkgPowerParameters          0x6A
#define SMC_MSG_LoadEdcLimitParameters          0x6B
#define SMC_MSG_LoadStapmParameters             0x6C
#define SMC_MSG_LoadBbbParameters               0x6D
#define SMC_MSG_ApplyShadowPstates              0x6E
#define SMC_MSG_ReadScs                         0x6F
#define SMC_MSG_ProgramApmMSRs                  0x70
// 0x71 to 0x72 is unused
#define SMC_MSG_GetFeatureStatus                0xff//0x73
#define SMC_MSG_MONITOR_PORT80_GetPosition      0xff//0x76
#define SMC_MSG_BC                              0x77
#define SMC_MSG_SecureSmnWrite                  0x78
#define SMC_MSG_SecureSmnRead                   0x79
#define SMC_MSG_LoadBatteryLifeParameters       0xff//0x7A
#define SMC_MSG_ChangeNumBoostStates            0xff//0x7B // Return feature status
#define SMC_MSG_LoadTjMaxParameters             0x7C
#define SMC_MSG_GetBtcGbvHi                     0x7D
#define SMC_MSG_GetBtcGbvLo                     0x7E
#define SMC_MSG_SetBtcGbvHi                     0x7F
#define SMC_MSG_SetBtcGbvLo                     0x80
#define SMC_MSG_LoadDeterminismParameters       0x81
#define SMC_MSG_LoadPsiParameters               0x82
#define SMC_MSG_UnderflowCntlSmiCmds            0x83
#define SMC_MSG_PowerUpAcp                      0x84
#define SMC_MSG_BH_CPU_ActivityMonitor_EN       0xFF//0x88


#define SMC_MSG_SetCpuVid                       0x88
#define SMC_MSG_SetPsfSigma                     0x89

//
#define BAPM_MASK               0x00000001
#define POWER_ESTIMATOR_MASK    0x00000002
#define THERMAL_CONTROLLER_MASK 0x00000004
#define TDC_LIMITING_MASK       0x00000008
#define PKG_PWR_LIMITING_MASK   0x00000010
#define LCLK_DPM_MASK           0x00000020
#define VOLTAGE_CONTROLLER_MASK 0x00000040
#define GEAPM_MASK              0x00000080
#define BBB_MASK                0x00000100
#define IBS_MASK                0x00000200
#define PSTATE_ARBITER_MASK     0x00000400
#define NB_DPM_MASK             0x00000800
#define LCLK_DEEP_SLEEP_MASK    0x00001000
#define ULV_MASK                0x00002000
#define GFX_CU_PG_MASK          0x00004000
#define AVFS_MASK               0x00008000
#define UVD_DPM_MASK            0x00010000
#define VQ_CONTROLLER_MASK      0x00020000
#define ACC_MASK                0x00040000
#define SCLK_DPM_MASK           0x00080000
#define PRE_FETCH_DATA_MASK     0x00100000
#define DFS_BYPASS_MASK         0x00200000
#define HTC_MASK                0x00400000
#define VDDGFX_MASK             0x00800000
#define LEAPM_MASK              0x01000000
#define CONN_STDBY_MASK         0x02000000
#define PORT80_MONITOR_MASK     0x04000000
#define PSPCLK_DPM_MASK         0x08000000
#define STAPM_MASK              0x10000000
#define RELIABILITY_MASK        0x20000000
#define CPU_STRETCHER_MASK      0x40000000
#define SCLK_STRETCHER_MASK     0x80000000

//
#define  L1_SEL_PPx40                         0
#define  L1_SEL_PPx41                         1
#define  L1_SEL_GBIF                          2
//IOAGR (SBG, PSP, APG and INTGEN shared one L1)
#define  L1_SEL_IOAGR                         3


// **** MSRC001_1073 Register Definition ****
// Address
#define MSRC001_1073_ADDRESS                                    0xc0011073

// Type
#define MSRC001_1073_TYPE                                       TYPE_MSR

// **** D0F0x04 Register Definition ****
// Address
#define D0F0x04_ADDRESS                                         0x4

// Type
#define D0F0x04_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x04_IoAccessEn_OFFSET                               0
#define D0F0x04_IoAccessEn_WIDTH                                1
#define D0F0x04_IoAccessEn_MASK                                 0x1
#define D0F0x04_MemAccessEn_OFFSET                              1
#define D0F0x04_MemAccessEn_WIDTH                               1
#define D0F0x04_MemAccessEn_MASK                                0x2
#define D0F0x04_BusMasterEn_OFFSET                              2
#define D0F0x04_BusMasterEn_WIDTH                               1
#define D0F0x04_BusMasterEn_MASK                                0x4
#define D0F0x04_Reserved_19_3_OFFSET                            3
#define D0F0x04_Reserved_19_3_WIDTH                             17
#define D0F0x04_Reserved_19_3_MASK                              0xffff8
#define D0F0x04_CapList_OFFSET                                  20
#define D0F0x04_CapList_WIDTH                                   1
#define D0F0x04_CapList_MASK                                    0x100000
#define D0F0x04_Reserved_31_21_OFFSET                           21
#define D0F0x04_Reserved_31_21_WIDTH                            11
#define D0F0x04_Reserved_31_21_MASK                             0xffe00000

/// D0F0x04
typedef union {
  struct {                                                              ///<
    UINT32                                               IoAccessEn:1 ; ///<
    UINT32                                              MemAccessEn:1 ; ///<
    UINT32                                              BusMasterEn:1 ; ///<
    UINT32                                            Reserved_19_3:17; ///<
    UINT32                                                  CapList:1 ; ///<
    UINT32                                           Reserved_31_21:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x04_STRUCT;

// **** D0F0x60 Register Definition ****
// Address
#define D0F0x60_ADDRESS                                         0x60

// Type
#define D0F0x60_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x60_MiscIndAddr_OFFSET                              0
#define D0F0x60_MiscIndAddr_WIDTH                               8
#define D0F0x60_MiscIndAddr_MASK                                0xff
#define D0F0x60_Reserved_31_8_OFFSET                            8
#define D0F0x60_Reserved_31_8_WIDTH                             24
#define D0F0x60_Reserved_31_8_MASK                              0xffffff00

/// D0F0x60
typedef union {
  struct {                                                              ///<
    UINT32                                              MiscIndAddr:8 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x60_STRUCT;

// **** D0F0x7C Register Definition ****
// Address
#define D0F0x7C_ADDRESS                                         0x7c

// Type
#define D0F0x7C_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x7C_ForceIntGfxDisable_OFFSET                       0
#define D0F0x7C_ForceIntGfxDisable_WIDTH                        1
#define D0F0x7C_ForceIntGfxDisable_MASK                         0x1
#define D0F0x7C_Reserved_31_1_OFFSET                            1
#define D0F0x7C_Reserved_31_1_WIDTH                             31
#define D0F0x7C_Reserved_31_1_MASK                              0xfffffffe

/// D0F0x7C
typedef union {
  struct {                                                              ///<
    UINT32                                       ForceIntGfxDisable:1 ; ///<
    UINT32                                            Reserved_31_1:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x7C_STRUCT;

// **** D0F0x94 Register Definition ****
// Address
#define D0F0x94_ADDRESS                                         0x94

// Type
#define D0F0x94_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0x94_OrbIndAddr_OFFSET                               0
#define D0F0x94_OrbIndAddr_WIDTH                                7
#define D0F0x94_OrbIndAddr_MASK                                 0x7f
#define D0F0x94_Reserved_31_7_OFFSET                            7
#define D0F0x94_Reserved_31_7_WIDTH                             25
#define D0F0x94_Reserved_31_7_MASK                              0xffffff80

/// D0F0x94
typedef union {
  struct {                                                              ///<
    UINT32                                               OrbIndAddr:7 ; ///<
    UINT32                                            Reserved_31_7:25; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x94_STRUCT;

// **** D0F0xB8 Register Definition ****
// Address
#define D0F0xB8_ADDRESS                                         0xb8

// Type
#define D0F0xB8_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xB8_NbSmuIndAddr_OFFSET                             0
#define D0F0xB8_NbSmuIndAddr_WIDTH                              32
#define D0F0xB8_NbSmuIndAddr_MASK                               0xffffffff

/// D0F0xB8
typedef union {
  struct {                                                              ///<
    UINT32                                             NbSmuIndAddr:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xB8_STRUCT;

// **** D0F0xD0 Register Definition ****
// Address
#define D0F0xD0_ADDRESS                                         0xd0

// Type
#define D0F0xD0_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xD0_NbGbifIndAddr_OFFSET                            0
#define D0F0xD0_NbGbifIndAddr_WIDTH                             32
#define D0F0xD0_NbGbifIndAddr_MASK                              0xffffffff

/// D0F0xD0
typedef union {
  struct {                                                              ///<
    UINT32                                            NbGbifIndAddr:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD0_STRUCT;

// **** D0F0xE0 Register Definition ****
// Address
#define D0F0xE0_ADDRESS                                         0xe0

// Type
#define D0F0xE0_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xE0_PcieIndxAddr_OFFSET                             0
#define D0F0xE0_PcieIndxAddr_WIDTH                              16
#define D0F0xE0_PcieIndxAddr_MASK                               0xffff
#define D0F0xE0_FrameType_OFFSET                                16
#define D0F0xE0_FrameType_WIDTH                                 8
#define D0F0xE0_FrameType_MASK                                  0xff0000
#define D0F0xE0_BlockSelect_OFFSET                              24
#define D0F0xE0_BlockSelect_WIDTH                               8
#define D0F0xE0_BlockSelect_MASK                                0xff000000

/// D0F0xE0
typedef union {
  struct {                                                              ///<
    UINT32                                             PcieIndxAddr:16; ///<
    UINT32                                                FrameType:8 ; ///<
    UINT32                                              BlockSelect:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE0_STRUCT;

// **** D0F0xF8 Register Definition ****
// Address
#define D0F0xF8_ADDRESS                                         0xf8

// Type
#define D0F0xF8_TYPE                                            TYPE_D0F0
// Field Data
#define D0F0xF8_IOAPICIndAddr_OFFSET                            0
#define D0F0xF8_IOAPICIndAddr_WIDTH                             8
#define D0F0xF8_IOAPICIndAddr_MASK                              0xff
#define D0F0xF8_Reserved_31_8_OFFSET                            8
#define D0F0xF8_Reserved_31_8_WIDTH                             24
#define D0F0xF8_Reserved_31_8_MASK                              0xffffff00

/// D0F0xF8
typedef union {
  struct {                                                              ///<
    UINT32                                            IOAPICIndAddr:8 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xF8_STRUCT;

// **** D0F0x64_x0D Register Definition ****
// Address
#define D0F0x64_x0D_ADDRESS                                     0xd

// Type
#define D0F0x64_x0D_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x0D_PciDev0Fn2RegEn_OFFSET                      0
#define D0F0x64_x0D_PciDev0Fn2RegEn_WIDTH                       1
#define D0F0x64_x0D_PciDev0Fn2RegEn_MASK                        0x1
#define D0F0x64_x0D_Reserved_30_1_OFFSET                        1
#define D0F0x64_x0D_Reserved_30_1_WIDTH                         30
#define D0F0x64_x0D_Reserved_30_1_MASK                          0x7ffffffe
#define D0F0x64_x0D_IommuDis_OFFSET                             31
#define D0F0x64_x0D_IommuDis_WIDTH                              1
#define D0F0x64_x0D_IommuDis_MASK                               0x80000000

/// D0F0x64_x0D
typedef union {
  struct {                                                              ///<
    UINT32                                          PciDev0Fn2RegEn:1 ; ///<
    UINT32                                            Reserved_30_1:30; ///<
    UINT32                                                 IommuDis:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x0D_STRUCT;

// **** D0F0x64_x16 Register Definition ****
// Address
#define D0F0x64_x16_ADDRESS                                     0x16

// Type
#define D0F0x64_x16_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x16_AerUrMsgEn_OFFSET                           0
#define D0F0x64_x16_AerUrMsgEn_WIDTH                            1
#define D0F0x64_x16_AerUrMsgEn_MASK                             0x1
#define D0F0x64_x16_Reserved_3_1_OFFSET                         1
#define D0F0x64_x16_Reserved_3_1_WIDTH                          3
#define D0F0x64_x16_Reserved_3_1_MASK                           0xe
#define D0F0x64_x16_PCIE0AerCredits_OFFSET                      4
#define D0F0x64_x16_PCIE0AerCredits_WIDTH                       3
#define D0F0x64_x16_PCIE0AerCredits_MASK                        0x70
#define D0F0x64_x16_Reserved_7_7_OFFSET                         7
#define D0F0x64_x16_Reserved_7_7_WIDTH                          1
#define D0F0x64_x16_Reserved_7_7_MASK                           0x80
#define D0F0x64_x16_PCIE1AerCredits_OFFSET                      8
#define D0F0x64_x16_PCIE1AerCredits_WIDTH                       3
#define D0F0x64_x16_PCIE1AerCredits_MASK                        0x700
#define D0F0x64_x16_Reserved_31_11_OFFSET                       11
#define D0F0x64_x16_Reserved_31_11_WIDTH                        21
#define D0F0x64_x16_Reserved_31_11_MASK                         0xfffff800

/// D0F0x64_x16
typedef union {
  struct {                                                              ///<
    UINT32                                               AerUrMsgEn:1 ; ///<
    UINT32                                             Reserved_3_1:3 ; ///<
    UINT32                                          PCIE0AerCredits:3 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                          PCIE1AerCredits:3 ; ///<
    UINT32                                           Reserved_31_11:21; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x16_STRUCT;

// **** D0F0x64_x1D Register Definition ****
// Address
#define D0F0x64_x1D_ADDRESS                                     0x1d

// Type
#define D0F0x64_x1D_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x1D_Reserved_0_0_OFFSET                         0
#define D0F0x64_x1D_Reserved_0_0_WIDTH                          1
#define D0F0x64_x1D_Reserved_0_0_MASK                           0x1
#define D0F0x64_x1D_VgaEn_OFFSET                                1
#define D0F0x64_x1D_VgaEn_WIDTH                                 1
#define D0F0x64_x1D_VgaEn_MASK                                  0x2
#define D0F0x64_x1D_Reserved_2_2_OFFSET                         2
#define D0F0x64_x1D_Reserved_2_2_WIDTH                          1
#define D0F0x64_x1D_Reserved_2_2_MASK                           0x4
#define D0F0x64_x1D_Vga16En_OFFSET                              3
#define D0F0x64_x1D_Vga16En_WIDTH                               1
#define D0F0x64_x1D_Vga16En_MASK                                0x8
#define D0F0x64_x1D_IntgfxBusMasterDis_OFFSET                   4
#define D0F0x64_x1D_IntgfxBusMasterDis_WIDTH                    1
#define D0F0x64_x1D_IntgfxBusMasterDis_MASK                     0x10
#define D0F0x64_x1D_IntgfxP2pDis_OFFSET                         5
#define D0F0x64_x1D_IntgfxP2pDis_WIDTH                          1
#define D0F0x64_x1D_IntgfxP2pDis_MASK                           0x20
#define D0F0x64_x1D_Reserved_31_6_OFFSET                        6
#define D0F0x64_x1D_Reserved_31_6_WIDTH                         26
#define D0F0x64_x1D_Reserved_31_6_MASK                          0xffffffc0

/// D0F0x64_x1D
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                                    VgaEn:1 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                                  Vga16En:1 ; ///<
    UINT32                                       IntgfxBusMasterDis:1 ; ///<
    UINT32                                             IntgfxP2pDis:1 ; ///<
    UINT32                                            Reserved_31_6:26; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x1D_STRUCT;

// **** D0F0x64_x1F Register Definition ****
// Address
#define D0F0x64_x1F_ADDRESS                                     0x1f

// Type
#define D0F0x64_x1F_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x1F_SBLocatedPort_OFFSET                        0
#define D0F0x64_x1F_SBLocatedPort_WIDTH                         16
#define D0F0x64_x1F_SBLocatedPort_MASK                          0xffff
#define D0F0x64_x1F_SBLocatedCore_OFFSET                        16
#define D0F0x64_x1F_SBLocatedCore_WIDTH                         16
#define D0F0x64_x1F_SBLocatedCore_MASK                          0xffff0000

/// D0F0x64_x1F
typedef union {
  struct {                                                              ///<
    UINT32                                            SBLocatedPort:16; ///<
    UINT32                                            SBLocatedCore:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x1F_STRUCT;

// **** D0F0x64_x22 Register Definition ****
// Address
#define D0F0x64_x22_ADDRESS                                     0x22

// Type
#define D0F0x64_x22_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x22_OnDelay_OFFSET                              0
#define D0F0x64_x22_OnDelay_WIDTH                               4
#define D0F0x64_x22_OnDelay_MASK                                0xf
#define D0F0x64_x22_OffHysteresis_OFFSET                        4
#define D0F0x64_x22_OffHysteresis_WIDTH                         8
#define D0F0x64_x22_OffHysteresis_MASK                          0xff0
#define D0F0x64_x22_DivId_OFFSET                                12
#define D0F0x64_x22_DivId_WIDTH                                 3
#define D0F0x64_x22_DivId_MASK                                  0x7000
#define D0F0x64_x22_RampDisClk6_OFFSET                          15
#define D0F0x64_x22_RampDisClk6_WIDTH                           1
#define D0F0x64_x22_RampDisClk6_MASK                            0x8000
#define D0F0x64_x22_RampDisClk5_OFFSET                          16
#define D0F0x64_x22_RampDisClk5_WIDTH                           1
#define D0F0x64_x22_RampDisClk5_MASK                            0x10000
#define D0F0x64_x22_RampDisClk4_OFFSET                          17
#define D0F0x64_x22_RampDisClk4_WIDTH                           1
#define D0F0x64_x22_RampDisClk4_MASK                            0x20000
#define D0F0x64_x22_RampDisClk3_OFFSET                          18
#define D0F0x64_x22_RampDisClk3_WIDTH                           1
#define D0F0x64_x22_RampDisClk3_MASK                            0x40000
#define D0F0x64_x22_RampDisClk2_OFFSET                          19
#define D0F0x64_x22_RampDisClk2_WIDTH                           1
#define D0F0x64_x22_RampDisClk2_MASK                            0x80000
#define D0F0x64_x22_RampDisClk1_OFFSET                          20
#define D0F0x64_x22_RampDisClk1_WIDTH                           1
#define D0F0x64_x22_RampDisClk1_MASK                            0x100000
#define D0F0x64_x22_RampDisClk0_OFFSET                          21
#define D0F0x64_x22_RampDisClk0_WIDTH                           1
#define D0F0x64_x22_RampDisClk0_MASK                            0x200000
#define D0F0x64_x22_Reserved_23_22_OFFSET                       22
#define D0F0x64_x22_Reserved_23_22_WIDTH                        2
#define D0F0x64_x22_Reserved_23_22_MASK                         0xc00000
#define D0F0x64_x22_SoftOverrideClk6_OFFSET                     24
#define D0F0x64_x22_SoftOverrideClk6_WIDTH                      1
#define D0F0x64_x22_SoftOverrideClk6_MASK                       0x1000000
#define D0F0x64_x22_Reserved_25_25_OFFSET                       25
#define D0F0x64_x22_Reserved_25_25_WIDTH                        1
#define D0F0x64_x22_Reserved_25_25_MASK                         0x2000000
#define D0F0x64_x22_SoftOverrideClk4_OFFSET                     26
#define D0F0x64_x22_SoftOverrideClk4_WIDTH                      1
#define D0F0x64_x22_SoftOverrideClk4_MASK                       0x4000000
#define D0F0x64_x22_SoftOverrideClk4_VALUE                      0x0
#define D0F0x64_x22_SoftOverrideClk3_OFFSET                     27
#define D0F0x64_x22_SoftOverrideClk3_WIDTH                      1
#define D0F0x64_x22_SoftOverrideClk3_MASK                       0x8000000
#define D0F0x64_x22_SoftOverrideClk3_VALUE                      0x0
#define D0F0x64_x22_SoftOverrideClk2_OFFSET                     28
#define D0F0x64_x22_SoftOverrideClk2_WIDTH                      1
#define D0F0x64_x22_SoftOverrideClk2_MASK                       0x10000000
#define D0F0x64_x22_SoftOverrideClk2_VALUE                      0x0
#define D0F0x64_x22_SoftOverrideClk1_OFFSET                     29
#define D0F0x64_x22_SoftOverrideClk1_WIDTH                      1
#define D0F0x64_x22_SoftOverrideClk1_MASK                       0x20000000
#define D0F0x64_x22_SoftOverrideClk1_VALUE                      0x0
#define D0F0x64_x22_SoftOverrideClk0_OFFSET                     30
#define D0F0x64_x22_SoftOverrideClk0_WIDTH                      1
#define D0F0x64_x22_SoftOverrideClk0_MASK                       0x40000000
#define D0F0x64_x22_SoftOverrideClk0_VALUE                      0x0
#define D0F0x64_x22_Reserved_31_31_OFFSET                       31
#define D0F0x64_x22_Reserved_31_31_WIDTH                        1
#define D0F0x64_x22_Reserved_31_31_MASK                         0x80000000

/// D0F0x64_x22
typedef union {
  struct {                                                              ///<
    UINT32                                                  OnDelay:4 ; ///<
    UINT32                                            OffHysteresis:8 ; ///<
    UINT32                                                    DivId:3 ; ///<
    UINT32                                              RampDisClk6:1 ; ///<
    UINT32                                              RampDisClk5:1 ; ///<
    UINT32                                              RampDisClk4:1 ; ///<
    UINT32                                              RampDisClk3:1 ; ///<
    UINT32                                              RampDisClk2:1 ; ///<
    UINT32                                              RampDisClk1:1 ; ///<
    UINT32                                              RampDisClk0:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                         SoftOverrideClk6:1 ; ///<
    UINT32                                           Reserved_25_25:1 ; ///<
    UINT32                                         SoftOverrideClk4:1 ; ///<
    UINT32                                         SoftOverrideClk3:1 ; ///<
    UINT32                                         SoftOverrideClk2:1 ; ///<
    UINT32                                         SoftOverrideClk1:1 ; ///<
    UINT32                                         SoftOverrideClk0:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x22_STRUCT;

// **** D0F0x64_x23 Register Definition ****
// Address
#define D0F0x64_x23_ADDRESS                                     0x23

// Type
#define D0F0x64_x23_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x23_OnDelay_OFFSET                              0
#define D0F0x64_x23_OnDelay_WIDTH                               4
#define D0F0x64_x23_OnDelay_MASK                                0xf
#define D0F0x64_x23_OffHysteresis_OFFSET                        4
#define D0F0x64_x23_OffHysteresis_WIDTH                         8
#define D0F0x64_x23_OffHysteresis_MASK                          0xff0
#define D0F0x64_x23_DivId_OFFSET                                12
#define D0F0x64_x23_DivId_WIDTH                                 3
#define D0F0x64_x23_DivId_MASK                                  0x7000
#define D0F0x64_x23_RampDisClk6_OFFSET                          15
#define D0F0x64_x23_RampDisClk6_WIDTH                           1
#define D0F0x64_x23_RampDisClk6_MASK                            0x8000
#define D0F0x64_x23_RampDisClk5_OFFSET                          16
#define D0F0x64_x23_RampDisClk5_WIDTH                           1
#define D0F0x64_x23_RampDisClk5_MASK                            0x10000
#define D0F0x64_x23_RampDisClk4_OFFSET                          17
#define D0F0x64_x23_RampDisClk4_WIDTH                           1
#define D0F0x64_x23_RampDisClk4_MASK                            0x20000
#define D0F0x64_x23_RampDisClk3_OFFSET                          18
#define D0F0x64_x23_RampDisClk3_WIDTH                           1
#define D0F0x64_x23_RampDisClk3_MASK                            0x40000
#define D0F0x64_x23_RampDisClk2_OFFSET                          19
#define D0F0x64_x23_RampDisClk2_WIDTH                           1
#define D0F0x64_x23_RampDisClk2_MASK                            0x80000
#define D0F0x64_x23_RampDisClk1_OFFSET                          20
#define D0F0x64_x23_RampDisClk1_WIDTH                           1
#define D0F0x64_x23_RampDisClk1_MASK                            0x100000
#define D0F0x64_x23_RampDisClk0_OFFSET                          21
#define D0F0x64_x23_RampDisClk0_WIDTH                           1
#define D0F0x64_x23_RampDisClk0_MASK                            0x200000
#define D0F0x64_x23_Reserved_23_22_OFFSET                       22
#define D0F0x64_x23_Reserved_23_22_WIDTH                        2
#define D0F0x64_x23_Reserved_23_22_MASK                         0xc00000
#define D0F0x64_x23_Reserved_25_24_OFFSET                       24
#define D0F0x64_x23_Reserved_25_24_WIDTH                        2
#define D0F0x64_x23_Reserved_25_24_MASK                         0x3000000
#define D0F0x64_x23_SoftOverrideClk4_OFFSET                     26
#define D0F0x64_x23_SoftOverrideClk4_WIDTH                      1
#define D0F0x64_x23_SoftOverrideClk4_MASK                       0x4000000
#define D0F0x64_x23_SoftOverrideClk4_VALUE                      0x0
#define D0F0x64_x23_SoftOverrideClk3_OFFSET                     27
#define D0F0x64_x23_SoftOverrideClk3_WIDTH                      1
#define D0F0x64_x23_SoftOverrideClk3_MASK                       0x8000000
#define D0F0x64_x23_SoftOverrideClk3_VALUE                      0x0
#define D0F0x64_x23_SoftOverrideClk2_OFFSET                     28
#define D0F0x64_x23_SoftOverrideClk2_WIDTH                      1
#define D0F0x64_x23_SoftOverrideClk2_MASK                       0x10000000
#define D0F0x64_x23_SoftOverrideClk2_VALUE                      0x0
#define D0F0x64_x23_SoftOverrideClk1_OFFSET                     29
#define D0F0x64_x23_SoftOverrideClk1_WIDTH                      1
#define D0F0x64_x23_SoftOverrideClk1_MASK                       0x20000000
#define D0F0x64_x23_SoftOverrideClk1_VALUE                      0x0
#define D0F0x64_x23_SoftOverrideClk0_OFFSET                     30
#define D0F0x64_x23_SoftOverrideClk0_WIDTH                      1
#define D0F0x64_x23_SoftOverrideClk0_MASK                       0x40000000
#define D0F0x64_x23_SoftOverrideClk0_VALUE                      0x0
#define D0F0x64_x23_Reserved_31_31_OFFSET                       31
#define D0F0x64_x23_Reserved_31_31_WIDTH                        1
#define D0F0x64_x23_Reserved_31_31_MASK                         0x80000000

/// D0F0x64_x23
typedef union {
  struct {                                                              ///<
    UINT32                                                  OnDelay:4 ; ///<
    UINT32                                            OffHysteresis:8 ; ///<
    UINT32                                                    DivId:3 ; ///<
    UINT32                                              RampDisClk6:1 ; ///<
    UINT32                                              RampDisClk5:1 ; ///<
    UINT32                                              RampDisClk4:1 ; ///<
    UINT32                                              RampDisClk3:1 ; ///<
    UINT32                                              RampDisClk2:1 ; ///<
    UINT32                                              RampDisClk1:1 ; ///<
    UINT32                                              RampDisClk0:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                           Reserved_25_24:2 ; ///<
    UINT32                                         SoftOverrideClk4:1 ; ///<
    UINT32                                         SoftOverrideClk3:1 ; ///<
    UINT32                                         SoftOverrideClk2:1 ; ///<
    UINT32                                         SoftOverrideClk1:1 ; ///<
    UINT32                                         SoftOverrideClk0:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x23_STRUCT;

// **** D0F0x64_x30 Register Definition ****
// Address
#define D0F0x64_x30_ADDRESS                                     0x30

// Type
#define D0F0x64_x30_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x30_PBr0_DevFnMap_OFFSET                        0
#define D0F0x64_x30_PBr0_DevFnMap_WIDTH                         8
#define D0F0x64_x30_PBr0_DevFnMap_MASK                          0xff
#define D0F0x64_x30_Reserved_OFFSET                             8
#define D0F0x64_x30_Reserved_WIDTH                              24
#define D0F0x64_x30_Reserved_MASK                               0xffffff00

/// D0F0x64_x30
typedef union {
  struct {                                                              ///<
    UINT32                                            PBr0_DevFnMap:8 ; ///<
    UINT32                                                 Reserved:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x30_STRUCT;

// **** D0F0x64_x46 Register Definition ****
// Address
#define D0F0x64_x46_ADDRESS                                     0x46

// Type
#define D0F0x64_x46_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x46_HpPmpmeDevIdEn_OFFSET                       0
#define D0F0x64_x46_HpPmpmeDevIdEn_WIDTH                        1
#define D0F0x64_x46_HpPmpmeDevIdEn_MASK                         0x1
#define D0F0x64_x46_P2PMode_OFFSET                              1
#define D0F0x64_x46_P2PMode_WIDTH                               2
#define D0F0x64_x46_P2PMode_MASK                                0x6
#define D0F0x64_x46_Reserved_4_3_OFFSET                         3
#define D0F0x64_x46_Reserved_4_3_WIDTH                          2
#define D0F0x64_x46_Reserved_4_3_MASK                           0x18
#define D0F0x64_x46_JtagEn_OFFSET                               5
#define D0F0x64_x46_JtagEn_WIDTH                                1
#define D0F0x64_x46_JtagEn_MASK                                 0x20
#define D0F0x64_x46_Reserved_8_6_OFFSET                         6
#define D0F0x64_x46_Reserved_8_6_WIDTH                          3
#define D0F0x64_x46_Reserved_8_6_MASK                           0x1C0
#define D0F0x64_x46_Reserved_10_9_OFFSET                        9
#define D0F0x64_x46_Reserved_10_9_WIDTH                         2
#define D0F0x64_x46_Reserved_10_9_MASK                          0x600
#define D0F0x64_x46_DsAlwaysBusy_OFFSET                         11
#define D0F0x64_x46_DsAlwaysBusy_WIDTH                          1
#define D0F0x64_x46_DsAlwaysBusy_MASK                           0x800
#define D0F0x64_x46_IntxLevelOnlyMode_OFFSET                    12
#define D0F0x64_x46_IntxLevelOnlyMode_WIDTH                     1
#define D0F0x64_x46_IntxLevelOnlyMode_MASK                      0x1000
#define D0F0x64_x46_Reserved_13_13_OFFSET                       13
#define D0F0x64_x46_Reserved_13_13_WIDTH                        1
#define D0F0x64_x46_Reserved_13_13_MASK                         0x2000
#define D0F0x64_x46_Reserved_14_14_OFFSET                       14
#define D0F0x64_x46_Reserved_14_14_WIDTH                        1
#define D0F0x64_x46_Reserved_14_14_MASK                         0x4000
#define D0F0x64_x46_HostClkReqIdle_OFFSET                       15
#define D0F0x64_x46_HostClkReqIdle_WIDTH                        1
#define D0F0x64_x46_HostClkReqIdle_MASK                         0x8000
#define D0F0x64_x46_CgttLclkOverride_OFFSET                     16
#define D0F0x64_x46_CgttLclkOverride_WIDTH                      1
#define D0F0x64_x46_CgttLclkOverride_MASK                       0x10000
#define D0F0x64_x46_CgttLclkOverride_VALUE                      0x0
#define D0F0x64_x46_Reserved_21_17_OFFSET                       17
#define D0F0x64_x46_Reserved_21_17_WIDTH                        5
#define D0F0x64_x46_Reserved_21_17_MASK                         0x3e0000
#define D0F0x64_x46_IocAriSupported_OFFSET                      22
#define D0F0x64_x46_IocAriSupported_WIDTH                       1
#define D0F0x64_x46_IocAriSupported_MASK                        0x400000
#define D0F0x64_x46_HostCfgErrStatMask_OFFSET                   23
#define D0F0x64_x46_HostCfgErrStatMask_WIDTH                    1
#define D0F0x64_x46_HostCfgErrStatMask_MASK                     0x800000
#define D0F0x64_x46_Reserved_27_24_OFFSET                       24
#define D0F0x64_x46_Reserved_27_24_WIDTH                        4
#define D0F0x64_x46_Reserved_27_24_MASK                         0xf000000
#define D0F0x64_x46_MiscFeatureCntl_OFFSET                      28
#define D0F0x64_x46_MiscFeatureCntl_WIDTH                       4
#define D0F0x64_x46_MiscFeatureCntl_MASK                        0xf0000000

/// D0F0x64_x46
typedef union {
  struct {                                                              ///<
    UINT32                                           HpPmpmeDevIdEn:1 ; ///<
    UINT32                                                  P2PMode:2 ; ///<
    UINT32                                             Reserved_4_3:2 ; ///<
    UINT32                                                   JtagEn:1 ; ///<
    UINT32                                             Reserved_8_6:3 ; ///<
    UINT32                                            Reserved_10_9:2 ; ///<
    UINT32                                             DsAlwaysBusy:1 ; ///<
    UINT32                                        IntxLevelOnlyMode:1 ; ///<
    UINT32                                           Reserved_13_13:1 ; ///<
    UINT32                                           Reserved_14_14:1 ; ///<
    UINT32                                           HostClkReqIdle:1 ; ///<
    UINT32                                         CgttLclkOverride:1 ; ///<
    UINT32                                           Reserved_21_17:5 ; ///<
    UINT32                                          IocAriSupported:1 ; ///<
    UINT32                                       HostCfgErrStatMask:1 ; ///<
    UINT32                                           Reserved_27_24:4 ; ///<
    UINT32                                          MiscFeatureCntl:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x46_STRUCT;

// **** D0F0x64_x50 Register Definition ****
// Address
#define D0F0x64_x50_ADDRESS                                     0x50

// Type
#define D0F0x64_x50_TYPE                                        TYPE_D0F0x64
// Field Data
#define D0F0x64_x50_ACGPortA_BusMasterDis_OFFSET                0
#define D0F0x64_x50_ACGPortA_BusMasterDis_WIDTH                 1
#define D0F0x64_x50_ACGPortA_BusMasterDis_MASK                  0x1
#define D0F0x64_x50_ACGPortA_P2pDis_OFFSET                      1
#define D0F0x64_x50_ACGPortA_P2pDis_WIDTH                       1
#define D0F0x64_x50_ACGPortA_P2pDis_MASK                        0x2
#define D0F0x64_x50_ACGPortA_CfgDis_OFFSET                      2
#define D0F0x64_x50_ACGPortA_CfgDis_WIDTH                       1
#define D0F0x64_x50_ACGPortA_CfgDis_MASK                        0x4
#define D0F0x64_x50_ACGPortA_Dis_OFFSET                         3
#define D0F0x64_x50_ACGPortA_Dis_WIDTH                          1
#define D0F0x64_x50_ACGPortA_Dis_MASK                           0x8
#define D0F0x64_x50_ACGPortB_BusMasterDis_OFFSET                4
#define D0F0x64_x50_ACGPortB_BusMasterDis_WIDTH                 1
#define D0F0x64_x50_ACGPortB_BusMasterDis_MASK                  0x10
#define D0F0x64_x50_ACGPortB_P2pDis_OFFSET                      5
#define D0F0x64_x50_ACGPortB_P2pDis_WIDTH                       1
#define D0F0x64_x50_ACGPortB_P2pDis_MASK                        0x20
#define D0F0x64_x50_ACGPortB_CfgDis_OFFSET                      6
#define D0F0x64_x50_ACGPortB_CfgDis_WIDTH                       1
#define D0F0x64_x50_ACGPortB_CfgDis_MASK                        0x40
#define D0F0x64_x50_ACGPortB_Dis_OFFSET                         7
#define D0F0x64_x50_ACGPortB_Dis_WIDTH                          1
#define D0F0x64_x50_ACGPortB_Dis_MASK                           0x80
#define D0F0x64_x50_Reserved_OFFSET                             8
#define D0F0x64_x50_Reserved_WIDTH                              24
#define D0F0x64_x50_Reserved_MASK                               0xffffff00

/// D0F0x64_x50
typedef union {
  struct {                                                              ///<
    UINT32                                    ACGPortA_BusMasterDis:1 ; ///<
    UINT32                                          ACGPortA_P2pDis:1 ; ///<
    UINT32                                          ACGPortA_CfgDis:1 ; ///<
    UINT32                                             ACGPortA_Dis:1 ; ///<
    UINT32                                    ACGPortB_BusMasterDis:1 ; ///<
    UINT32                                          ACGPortB_P2pDis:1 ; ///<
    UINT32                                          ACGPortB_CfgDis:1 ; ///<
    UINT32                                             ACGPortB_Dis:1 ; ///<
    UINT32                                                 Reserved:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x64_x50_STRUCT;

// **** D0F0x98_x02 Register Definition ****
// Address
#define D0F0x98_x02_ADDRESS                                     0x2

// Type
#define D0F0x98_x02_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x02_OrbRxPgmemEn_OFFSET                         0
#define D0F0x98_x02_OrbRxPgmemEn_WIDTH                          1
#define D0F0x98_x02_OrbRxPgmemEn_MASK                           0x1
#define D0F0x98_x02_OrbTxPgmemEn_OFFSET                         1
#define D0F0x98_x02_OrbTxPgmemEn_WIDTH                          1
#define D0F0x98_x02_OrbTxPgmemEn_MASK                           0x2
#define D0F0x98_x02_RxPgmemStEn_OFFSET                          2
#define D0F0x98_x02_RxPgmemStEn_WIDTH                           3
#define D0F0x98_x02_RxPgmemStEn_MASK                            0x1c
#define D0F0x98_x02_TxPgmemStEn_OFFSET                          5
#define D0F0x98_x02_TxPgmemStEn_WIDTH                           3
#define D0F0x98_x02_TxPgmemStEn_MASK                            0xe0
#define D0F0x98_x02_Reserved_15_8_OFFSET                        8
#define D0F0x98_x02_Reserved_15_8_WIDTH                         8
#define D0F0x98_x02_Reserved_15_8_MASK                          0xff00
#define D0F0x98_x02_PgmemHysteresis_OFFSET                      16
#define D0F0x98_x02_PgmemHysteresis_WIDTH                       16
#define D0F0x98_x02_PgmemHysteresis_MASK                        0xffff0000

/// D0F0x98_x02
typedef union {
  struct {                                                              ///<
    UINT32                                             OrbRxPgmemEn:1 ; ///<
    UINT32                                             OrbTxPgmemEn:1 ; ///<
    UINT32                                              RxPgmemStEn:3 ; ///<
    UINT32                                              TxPgmemStEn:3 ; ///<
    UINT32                                            Reserved_15_8:8 ; ///<
    UINT32                                          PgmemHysteresis:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x02_STRUCT;

// **** D0F0x98_x06 Register Definition ****
// Address
#define D0F0x98_x06_ADDRESS                                     0x6

// Type
#define D0F0x98_x06_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x06_Reserved_1_0_OFFSET                         0
#define D0F0x98_x06_Reserved_1_0_WIDTH                          2
#define D0F0x98_x06_Reserved_1_0_MASK                           0x3
#define D0F0x98_x06_HostReqPassPWMode_OFFSET                    2
#define D0F0x98_x06_HostReqPassPWMode_WIDTH                     1
#define D0F0x98_x06_HostReqPassPWMode_MASK                      0x4
#define D0F0x98_x06_HostReqPassPWMode_VALUE                     0x0
#define D0F0x98_x06_HostReqSnoopMode_OFFSET                     3
#define D0F0x98_x06_HostReqSnoopMode_WIDTH                      1
#define D0F0x98_x06_HostReqSnoopMode_MASK                       0x8
#define D0F0x98_x06_HostReqSnoopMode_VALUE                      0x0
#define D0F0x98_x06_HostRdRspPassPWMode_OFFSET                  4
#define D0F0x98_x06_HostRdRspPassPWMode_WIDTH                   1
#define D0F0x98_x06_HostRdRspPassPWMode_MASK                    0x10
#define D0F0x98_x06_HostRdRspPassPWMode_VALUE                   0x0
#define D0F0x98_x06_Reserved_10_5_OFFSET                        5
#define D0F0x98_x06_Reserved_10_5_WIDTH                         6
#define D0F0x98_x06_Reserved_10_5_MASK                          0x7e0
#define D0F0x98_x06_HtdNoErr_OFFSET                             11
#define D0F0x98_x06_HtdNoErr_WIDTH                              1
#define D0F0x98_x06_HtdNoErr_MASK                               0x800
#define D0F0x98_x06_HtdNoErr_VALUE                              0x0
#define D0F0x98_x06_Reserved_13_12_OFFSET                       12
#define D0F0x98_x06_Reserved_13_12_WIDTH                        2
#define D0F0x98_x06_Reserved_13_12_MASK                         0x3000
#define D0F0x98_x06_ReqCompatModeDis_OFFSET                     14
#define D0F0x98_x06_ReqCompatModeDis_WIDTH                      1
#define D0F0x98_x06_ReqCompatModeDis_MASK                       0x4000
#define D0F0x98_x06_ReqCompatModeDis_VALUE                      0x0
#define D0F0x98_x06_HostRdSplitEn_OFFSET                        15
#define D0F0x98_x06_HostRdSplitEn_WIDTH                         1
#define D0F0x98_x06_HostRdSplitEn_MASK                          0x8000
#define D0F0x98_x06_Reserved_25_16_OFFSET                       16
#define D0F0x98_x06_Reserved_25_16_WIDTH                        10
#define D0F0x98_x06_Reserved_25_16_MASK                         0x3ff0000
#define D0F0x98_x06_UmiNpMemWrEn_OFFSET                         26
#define D0F0x98_x06_UmiNpMemWrEn_WIDTH                          1
#define D0F0x98_x06_UmiNpMemWrEn_MASK                           0x4000000
#define D0F0x98_x06_Reserved_31_27_OFFSET                       27
#define D0F0x98_x06_Reserved_31_27_WIDTH                        5
#define D0F0x98_x06_Reserved_31_27_MASK                         0xf8000000

/// D0F0x98_x06
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_1_0:2 ; ///<
    UINT32                                        HostReqPassPWMode:1 ; ///<
    UINT32                                         HostReqSnoopMode:1 ; ///<
    UINT32                                      HostRdRspPassPWMode:1 ; ///<
    UINT32                                            Reserved_10_5:6 ; ///<
    UINT32                                                 HtdNoErr:1 ; ///<
    UINT32                                           Reserved_13_12:2 ; ///<
    UINT32                                         ReqCompatModeDis:1 ; ///<
    UINT32                                            HostRdSplitEn:1 ; ///<
    UINT32                                           Reserved_25_16:10; ///<
    UINT32                                             UmiNpMemWrEn:1 ; ///<
    UINT32                                           Reserved_31_27:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x06_STRUCT;

// **** D0F0x98_x07 Register Definition ****
// Address
#define D0F0x98_x07_ADDRESS                                     0x7

// Type
#define D0F0x98_x07_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x07_IocBwOptEn_OFFSET                           0
#define D0F0x98_x07_IocBwOptEn_WIDTH                            1
#define D0F0x98_x07_IocBwOptEn_MASK                             0x1
#define D0F0x98_x07_IocBwOptEn_VALUE                            0x1
#define D0F0x98_x07_IocWrROMapDis_OFFSET                        1
#define D0F0x98_x07_IocWrROMapDis_WIDTH                         1
#define D0F0x98_x07_IocWrROMapDis_MASK                          0x2
#define D0F0x98_x07_IocRdROMapDis_OFFSET                        2
#define D0F0x98_x07_IocRdROMapDis_WIDTH                         1
#define D0F0x98_x07_IocRdROMapDis_MASK                          0x4
#define D0F0x98_x07_Reserved_3_3_OFFSET                         3
#define D0F0x98_x07_Reserved_3_3_WIDTH                          1
#define D0F0x98_x07_Reserved_3_3_MASK                           0x8
#define D0F0x98_x07_IommuBwOptEn_OFFSET                         4
#define D0F0x98_x07_IommuBwOptEn_WIDTH                          1
#define D0F0x98_x07_IommuBwOptEn_MASK                           0x10
#define D0F0x98_x07_IommuBwOptEn_VALUE                          0x1
#define D0F0x98_x07_SpgBwOptEn_OFFSET                           5
#define D0F0x98_x07_SpgBwOptEn_WIDTH                            1
#define D0F0x98_x07_SpgBwOptEn_MASK                             0x20
#define D0F0x98_x07_DmaReqRespPassPWMode_OFFSET                 6
#define D0F0x98_x07_DmaReqRespPassPWMode_WIDTH                  1
#define D0F0x98_x07_DmaReqRespPassPWMode_MASK                   0x40
#define D0F0x98_x07_DmaReqRespPassPWMode_VALUE                  0x0
#define D0F0x98_x07_IommuIsocPassPWMode_OFFSET                  7
#define D0F0x98_x07_IommuIsocPassPWMode_WIDTH                   1
#define D0F0x98_x07_IommuIsocPassPWMode_MASK                    0x80
#define D0F0x98_x07_IommuIsocPassPWMode_VALUE                   0x1
#define D0F0x98_x07_Reserved_14_8_OFFSET                        8
#define D0F0x98_x07_Reserved_14_8_WIDTH                         7
#define D0F0x98_x07_Reserved_14_8_MASK                          0x7f00
#define D0F0x98_x07_DropZeroMaskWrEn_OFFSET                     15
#define D0F0x98_x07_DropZeroMaskWrEn_WIDTH                      1
#define D0F0x98_x07_DropZeroMaskWrEn_MASK                       0x8000
#define D0F0x98_x07_DropZeroMaskWrEn_VALUE                      0x1
#define D0F0x98_x07_SyncFloodOnParityErr_OFFSET                 16
#define D0F0x98_x07_SyncFloodOnParityErr_WIDTH                  1
#define D0F0x98_x07_SyncFloodOnParityErr_MASK                   0x10000
#define D0F0x98_x07_Reserved_30_17_OFFSET                       17
#define D0F0x98_x07_Reserved_30_17_WIDTH                        14
#define D0F0x98_x07_Reserved_30_17_MASK                         0x7ffe0000
#define D0F0x98_x07_SMUCsrIsocEn_OFFSET                         31
#define D0F0x98_x07_SMUCsrIsocEn_WIDTH                          1
#define D0F0x98_x07_SMUCsrIsocEn_MASK                           0x80000000
#define D0F0x98_x07_SMUCsrIsocEn_VALUE                          0x1

/// D0F0x98_x07
typedef union {
  struct {                                                              ///<
    UINT32                                               IocBwOptEn:1 ; ///<
    UINT32                                            IocWrROMapDis:1 ; ///<
    UINT32                                            IocRdROMapDis:1 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                             IommuBwOptEn:1 ; ///<
    UINT32                                               SpgBwOptEn:1 ; ///<
    UINT32                                     DmaReqRespPassPWMode:1 ; ///<
    UINT32                                      IommuIsocPassPWMode:1 ; ///<
    UINT32                                            Reserved_14_8:7 ; ///<
    UINT32                                         DropZeroMaskWrEn:1 ; ///<
    UINT32                                     SyncFloodOnParityErr:1 ; ///<
    UINT32                                           Reserved_30_17:14; ///<
    UINT32                                             SMUCsrIsocEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x07_STRUCT;

// **** D0F0x98_x08 Register Definition ****
// Address
#define D0F0x98_x08_ADDRESS                                     0x8

// Type
#define D0F0x98_x08_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x08_NpWrrLenA_OFFSET                            0
#define D0F0x98_x08_NpWrrLenA_WIDTH                             8
#define D0F0x98_x08_NpWrrLenA_MASK                              0xff
#define D0F0x98_x08_NpWrrLenA_VALUE                             0x8
#define D0F0x98_x08_NpWrrLenB_OFFSET                            8
#define D0F0x98_x08_NpWrrLenB_WIDTH                             8
#define D0F0x98_x08_NpWrrLenB_MASK                              0xff00
#define D0F0x98_x08_NpWrrLenB_VALUE                             0x8
#define D0F0x98_x08_NpWrrLenC_OFFSET                            16
#define D0F0x98_x08_NpWrrLenC_WIDTH                             8
#define D0F0x98_x08_NpWrrLenC_MASK                              0xff0000
#define D0F0x98_x08_NpWrrLenC_VALUE                             0x1
#define D0F0x98_x08_NpWrrLenD_OFFSET                            24
#define D0F0x98_x08_NpWrrLenD_WIDTH                             8
#define D0F0x98_x08_NpWrrLenD_MASK                              0xff000000

/// D0F0x98_x08
typedef union {
  struct {                                                              ///<
    UINT32                                                NpWrrLenA:8 ; ///<
    UINT32                                                NpWrrLenB:8 ; ///<
    UINT32                                                NpWrrLenC:8 ; ///<
    UINT32                                                NpWrrLenD:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x08_STRUCT;

// **** D0F0x98_x0C Register Definition ****
// Address
#define D0F0x98_x0C_ADDRESS                                     0xc

// Type
#define D0F0x98_x0C_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x0C_GcmWrrLenA_OFFSET                           0
#define D0F0x98_x0C_GcmWrrLenA_WIDTH                            8
#define D0F0x98_x0C_GcmWrrLenA_MASK                             0xff
#define D0F0x98_x0C_GcmWrrLenA_VALUE                            0x8
#define D0F0x98_x0C_GcmWrrLenB_OFFSET                           8
#define D0F0x98_x0C_GcmWrrLenB_WIDTH                            8
#define D0F0x98_x0C_GcmWrrLenB_MASK                             0xff00
#define D0F0x98_x0C_GcmWrrLenB_VALUE                            0x8
#define D0F0x98_x0C_Reserved_23_16_OFFSET                       16
#define D0F0x98_x0C_Reserved_23_16_WIDTH                        8
#define D0F0x98_x0C_Reserved_23_16_MASK                         0xff0000
#define D0F0x98_x0C_Reserved_31_24_OFFSET                       24
#define D0F0x98_x0C_Reserved_31_24_WIDTH                        8
#define D0F0x98_x0C_Reserved_31_24_MASK                         0xff000000

/// D0F0x98_x0C
typedef union {
  struct {                                                              ///<
    UINT32                                               GcmWrrLenA:8 ; ///<
    UINT32                                               GcmWrrLenB:8 ; ///<
    UINT32                                           Reserved_23_16:8 ; ///<
    UINT32                                           Reserved_31_24:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x0C_STRUCT;

// **** D0F0x98_x1E Register Definition ****
// Address
#define D0F0x98_x1E_ADDRESS                                     0x1e

// Type
#define D0F0x98_x1E_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x1E_DisableSyncFloodDetect_OFFSET               0
#define D0F0x98_x1E_DisableSyncFloodDetect_WIDTH                1
#define D0F0x98_x1E_DisableSyncFloodDetect_MASK                 0x1
#define D0F0x98_x1E_HiPriEn_OFFSET                              1
#define D0F0x98_x1E_HiPriEn_WIDTH                               1
#define D0F0x98_x1E_HiPriEn_MASK                                0x2
#define D0F0x98_x1E_HiPriEn_VALUE                               0x1
#define D0F0x98_x1E_Reserved_23_2_OFFSET                        2
#define D0F0x98_x1E_Reserved_23_2_WIDTH                         22
#define D0F0x98_x1E_Reserved_23_2_MASK                          0xfffffc
#define D0F0x98_x1E_RxErrStatusDelay_OFFSET                     24
#define D0F0x98_x1E_RxErrStatusDelay_WIDTH                      8
#define D0F0x98_x1E_RxErrStatusDelay_MASK                       0xff000000
#define D0F0x98_x1E_RxErrStatusDelay_VALUE                      0x48

// **** D0F0x98_x28 Register Definition ****
// Address
#define D0F0x98_x28_ADDRESS                                     0x28

// Type
#define D0F0x98_x28_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x28_Reserved_0_0_OFFSET                         0
#define D0F0x98_x28_Reserved_0_0_WIDTH                          1
#define D0F0x98_x28_Reserved_0_0_MASK                           0x1
#define D0F0x98_x28_ForceCoherentIntr_OFFSET                    1
#define D0F0x98_x28_ForceCoherentIntr_WIDTH                     1
#define D0F0x98_x28_ForceCoherentIntr_MASK                      0x2
#define D0F0x98_x28_ForceCoherentIntr_VALUE                     0x1
#define D0F0x98_x28_ForceFifoFlush_OFFSET                       2
#define D0F0x98_x28_ForceFifoFlush_WIDTH                        1
#define D0F0x98_x28_ForceFifoFlush_MASK                         0x4
#define D0F0x98_x28_ForceFifoFlush_VALUE                        0x0
#define D0F0x98_x28_Reserved_31_3_OFFSET                        3
#define D0F0x98_x28_Reserved_31_3_WIDTH                         29
#define D0F0x98_x28_Reserved_31_3_MASK                          0xfffffff8

/// D0F0x98_x28
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                        ForceCoherentIntr:1 ; ///<
    UINT32                                           ForceFifoFlush:1 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x28_STRUCT;

// **** D0F0x98_x2C Register Definition ****
// Address
#define D0F0x98_x2C_ADDRESS                                     0x2c

// Type
#define D0F0x98_x2C_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x2C_Reserved_0_0_OFFSET                         0
#define D0F0x98_x2C_Reserved_0_0_WIDTH                          1
#define D0F0x98_x2C_Reserved_0_0_MASK                           0x1
#define D0F0x98_x2C_DynWakeEn_OFFSET                            1
#define D0F0x98_x2C_DynWakeEn_WIDTH                             1
#define D0F0x98_x2C_DynWakeEn_MASK                              0x2
#define D0F0x98_x2C_DynWakeEn_VALUE                             0x1
#define D0F0x98_x2C_CgttLclkOverride_OFFSET                     2
#define D0F0x98_x2C_CgttLclkOverride_WIDTH                      1
#define D0F0x98_x2C_CgttLclkOverride_MASK                       0x4
#define D0F0x98_x2C_CgttLclkOverride_VALUE                      0x0
#define D0F0x98_x2C_Reserved_8_3_OFFSET                         3
#define D0F0x98_x2C_Reserved_8_3_WIDTH                          6
#define D0F0x98_x2C_Reserved_8_3_MASK                           0x1f8
#define D0F0x98_x2C_SBDmaActiveMask_OFFSET                      9
#define D0F0x98_x2C_SBDmaActiveMask_WIDTH                       1
#define D0F0x98_x2C_SBDmaActiveMask_MASK                        0x200
#define D0F0x98_x2C_SBDmaActiveMask_VALUE                       0x1
#define D0F0x98_x2C_SBDmaActiveMaskIntFCH_OFFSET                10
#define D0F0x98_x2C_SBDmaActiveMaskIntFCH_WIDTH                 1
#define D0F0x98_x2C_SBDmaActiveMaskIntFCH_MASK                  0x400
#define D0F0x98_x2C_Reserved_15_11_OFFSET                       11
#define D0F0x98_x2C_Reserved_15_11_WIDTH                        5
#define D0F0x98_x2C_Reserved_15_11_MASK                         0xf800
#define D0F0x98_x2C_WakeHysteresis_OFFSET                       16
#define D0F0x98_x2C_WakeHysteresis_WIDTH                        16
#define D0F0x98_x2C_WakeHysteresis_MASK                         0xffff0000
#define D0F0x98_x2C_WakeHysteresis_VALUE                        0x19

/// D0F0x98_x2C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                                DynWakeEn:1 ; ///<
    UINT32                                         CgttLclkOverride:1 ; ///<
    UINT32                                             Reserved_8_3:6 ; ///<
    UINT32                                          SBDmaActiveMask:1 ; ///<
    UINT32                                    SBDmaActiveMaskIntFCH:1 ; ///<
    UINT32                                           Reserved_15_11:5 ; ///<
    UINT32                                           WakeHysteresis:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x2C_STRUCT;

// **** D0F0x98_x3A Register Definition ****
// Address
#define D0F0x98_x3A_ADDRESS                                     0x3a

// Type
#define D0F0x98_x3A_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x3A_ClumpingEn_OFFSET                           0
#define D0F0x98_x3A_ClumpingEn_WIDTH                            32
#define D0F0x98_x3A_ClumpingEn_MASK                             0xffffffff

/// D0F0x98_x3A
typedef union {
  struct {                                                              ///<
    UINT32                                               ClumpingEn:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x3A_STRUCT;

// **** D0F0x98_x49 Register Definition ****
// Address
#define D0F0x98_x49_ADDRESS                                     0x49

// Type
#define D0F0x98_x49_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x49_OnDelay_OFFSET                              0
#define D0F0x98_x49_OnDelay_WIDTH                               4
#define D0F0x98_x49_OnDelay_MASK                                0xf
#define D0F0x98_x49_OffHysteresis_OFFSET                        4
#define D0F0x98_x49_OffHysteresis_WIDTH                         8
#define D0F0x98_x49_OffHysteresis_MASK                          0xff0
#define D0F0x98_x49_OffHysteresis_VALUE                         0x10
#define D0F0x98_x49_DivId_OFFSET                                12
#define D0F0x98_x49_DivId_WIDTH                                 3
#define D0F0x98_x49_DivId_MASK                                  0x7000
#define D0F0x98_x49_RampDisableClk6_OFFSET                      15
#define D0F0x98_x49_RampDisableClk6_WIDTH                       1
#define D0F0x98_x49_RampDisableClk6_MASK                        0x8000
#define D0F0x98_x49_RampDisableClk5_OFFSET                      16
#define D0F0x98_x49_RampDisableClk5_WIDTH                       1
#define D0F0x98_x49_RampDisableClk5_MASK                        0x10000
#define D0F0x98_x49_RampDisableClk4_OFFSET                      17
#define D0F0x98_x49_RampDisableClk4_WIDTH                       1
#define D0F0x98_x49_RampDisableClk4_MASK                        0x20000
#define D0F0x98_x49_RampDisableClk3_OFFSET                      18
#define D0F0x98_x49_RampDisableClk3_WIDTH                       1
#define D0F0x98_x49_RampDisableClk3_MASK                        0x40000
#define D0F0x98_x49_RampDisableClk2_OFFSET                      19
#define D0F0x98_x49_RampDisableClk2_WIDTH                       1
#define D0F0x98_x49_RampDisableClk2_MASK                        0x80000
#define D0F0x98_x49_RampDisableClk1_OFFSET                      20
#define D0F0x98_x49_RampDisableClk1_WIDTH                       1
#define D0F0x98_x49_RampDisableClk1_MASK                        0x100000
#define D0F0x98_x49_RampDisableClk0_OFFSET                      21
#define D0F0x98_x49_RampDisableClk0_WIDTH                       1
#define D0F0x98_x49_RampDisableClk0_MASK                        0x200000
#define D0F0x98_x49_Reserved_23_22_OFFSET                       22
#define D0F0x98_x49_Reserved_23_22_WIDTH                        2
#define D0F0x98_x49_Reserved_23_22_MASK                         0xc00000
#define D0F0x98_x49_SoftOverrideClk6_OFFSET                     24
#define D0F0x98_x49_SoftOverrideClk6_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk6_MASK                       0x1000000
#define D0F0x98_x49_SoftOverrideClk6_VALUE                      0x0
#define D0F0x98_x49_SoftOverrideClk5_OFFSET                     25
#define D0F0x98_x49_SoftOverrideClk5_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk5_MASK                       0x2000000
#define D0F0x98_x49_SoftOverrideClk5_VALUE                      0x0
#define D0F0x98_x49_SoftOverrideClk4_OFFSET                     26
#define D0F0x98_x49_SoftOverrideClk4_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk4_MASK                       0x4000000
#define D0F0x98_x49_SoftOverrideClk4_VALUE                      0x0
#define D0F0x98_x49_SoftOverrideClk3_OFFSET                     27
#define D0F0x98_x49_SoftOverrideClk3_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk3_MASK                       0x8000000
#define D0F0x98_x49_SoftOverrideClk3_VALUE                      0x0
#define D0F0x98_x49_SoftOverrideClk2_OFFSET                     28
#define D0F0x98_x49_SoftOverrideClk2_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk2_MASK                       0x10000000
#define D0F0x98_x49_SoftOverrideClk2_VALUE                      0x0
#define D0F0x98_x49_SoftOverrideClk1_OFFSET                     29
#define D0F0x98_x49_SoftOverrideClk1_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk1_MASK                       0x20000000
#define D0F0x98_x49_SoftOverrideClk1_VALUE                      0x0
#define D0F0x98_x49_SoftOverrideClk0_OFFSET                     30
#define D0F0x98_x49_SoftOverrideClk0_WIDTH                      1
#define D0F0x98_x49_SoftOverrideClk0_MASK                       0x40000000
#define D0F0x98_x49_SoftOverrideClk0_VALUE                      0x0
#define D0F0x98_x49_Reserved_31_31_OFFSET                       31
#define D0F0x98_x49_Reserved_31_31_WIDTH                        1
#define D0F0x98_x49_Reserved_31_31_MASK                         0x80000000

/// D0F0x98_x49
typedef union {
  struct {                                                              ///<
    UINT32                                                  OnDelay:4 ; ///<
    UINT32                                            OffHysteresis:8 ; ///<
    UINT32                                                    DivId:3 ; ///<
    UINT32                                          RampDisableClk6:1 ; ///<
    UINT32                                          RampDisableClk5:1 ; ///<
    UINT32                                          RampDisableClk4:1 ; ///<
    UINT32                                          RampDisableClk3:1 ; ///<
    UINT32                                          RampDisableClk2:1 ; ///<
    UINT32                                          RampDisableClk1:1 ; ///<
    UINT32                                          RampDisableClk0:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                         SoftOverrideClk6:1 ; ///<
    UINT32                                         SoftOverrideClk5:1 ; ///<
    UINT32                                         SoftOverrideClk4:1 ; ///<
    UINT32                                         SoftOverrideClk3:1 ; ///<
    UINT32                                         SoftOverrideClk2:1 ; ///<
    UINT32                                         SoftOverrideClk1:1 ; ///<
    UINT32                                         SoftOverrideClk0:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x49_STRUCT;

// **** D0F0x98_x4A Register Definition ****
// Address
#define D0F0x98_x4A_ADDRESS                                     0x4a

// Type
#define D0F0x98_x4A_TYPE                                        TYPE_D0F0x98
// Field Data
#define D0F0x98_x4A_OnDelay_OFFSET                              0
#define D0F0x98_x4A_OnDelay_WIDTH                               4
#define D0F0x98_x4A_OnDelay_MASK                                0xf
#define D0F0x98_x4A_OffHysteresis_OFFSET                        4
#define D0F0x98_x4A_OffHysteresis_WIDTH                         8
#define D0F0x98_x4A_OffHysteresis_MASK                          0xff0
#define D0F0x98_x4A_OffHysteresis_VALUE                         0x10
#define D0F0x98_x4A_DivId_OFFSET                                12
#define D0F0x98_x4A_DivId_WIDTH                                 3
#define D0F0x98_x4A_DivId_MASK                                  0x7000
#define D0F0x98_x4A_RampDisableClk6_OFFSET                      15
#define D0F0x98_x4A_RampDisableClk6_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk6_MASK                        0x8000
#define D0F0x98_x4A_RampDisableClk5_OFFSET                      16
#define D0F0x98_x4A_RampDisableClk5_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk5_MASK                        0x10000
#define D0F0x98_x4A_RampDisableClk4_OFFSET                      17
#define D0F0x98_x4A_RampDisableClk4_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk4_MASK                        0x20000
#define D0F0x98_x4A_RampDisableClk3_OFFSET                      18
#define D0F0x98_x4A_RampDisableClk3_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk3_MASK                        0x40000
#define D0F0x98_x4A_RampDisableClk2_OFFSET                      19
#define D0F0x98_x4A_RampDisableClk2_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk2_MASK                        0x80000
#define D0F0x98_x4A_RampDisableClk1_OFFSET                      20
#define D0F0x98_x4A_RampDisableClk1_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk1_MASK                        0x100000
#define D0F0x98_x4A_RampDisableClk0_OFFSET                      21
#define D0F0x98_x4A_RampDisableClk0_WIDTH                       1
#define D0F0x98_x4A_RampDisableClk0_MASK                        0x200000
#define D0F0x98_x4A_Reserved_23_22_OFFSET                       22
#define D0F0x98_x4A_Reserved_23_22_WIDTH                        2
#define D0F0x98_x4A_Reserved_23_22_MASK                         0xc00000
#define D0F0x98_x4A_SoftOverrideClk6_OFFSET                     24
#define D0F0x98_x4A_SoftOverrideClk6_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk6_MASK                       0x1000000
#define D0F0x98_x4A_SoftOverrideClk6_VALUE                      0x0
#define D0F0x98_x4A_SoftOverrideClk5_OFFSET                     25
#define D0F0x98_x4A_SoftOverrideClk5_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk5_MASK                       0x2000000
#define D0F0x98_x4A_SoftOverrideClk5_VALUE                      0x0
#define D0F0x98_x4A_SoftOverrideClk4_OFFSET                     26
#define D0F0x98_x4A_SoftOverrideClk4_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk4_MASK                       0x4000000
#define D0F0x98_x4A_SoftOverrideClk4_VALUE                      0x0
#define D0F0x98_x4A_SoftOverrideClk3_OFFSET                     27
#define D0F0x98_x4A_SoftOverrideClk3_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk3_MASK                       0x8000000
#define D0F0x98_x4A_SoftOverrideClk3_VALUE                      0x0
#define D0F0x98_x4A_SoftOverrideClk2_OFFSET                     28
#define D0F0x98_x4A_SoftOverrideClk2_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk2_MASK                       0x10000000
#define D0F0x98_x4A_SoftOverrideClk2_VALUE                      0x0
#define D0F0x98_x4A_SoftOverrideClk1_OFFSET                     29
#define D0F0x98_x4A_SoftOverrideClk1_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk1_MASK                       0x20000000
#define D0F0x98_x4A_SoftOverrideClk1_VALUE                      0x0
#define D0F0x98_x4A_SoftOverrideClk0_OFFSET                     30
#define D0F0x98_x4A_SoftOverrideClk0_WIDTH                      1
#define D0F0x98_x4A_SoftOverrideClk0_MASK                       0x40000000
#define D0F0x98_x4A_SoftOverrideClk0_VALUE                      0x0
#define D0F0x98_x4A_Reserved_31_31_OFFSET                       31
#define D0F0x98_x4A_Reserved_31_31_WIDTH                        1
#define D0F0x98_x4A_Reserved_31_31_MASK                         0x80000000

/// D0F0x98_x4A
typedef union {
  struct {                                                              ///<
    UINT32                                                  OnDelay:4 ; ///<
    UINT32                                            OffHysteresis:8 ; ///<
    UINT32                                                    DivId:3 ; ///<
    UINT32                                          RampDisableClk6:1 ; ///<
    UINT32                                          RampDisableClk5:1 ; ///<
    UINT32                                          RampDisableClk4:1 ; ///<
    UINT32                                          RampDisableClk3:1 ; ///<
    UINT32                                          RampDisableClk2:1 ; ///<
    UINT32                                          RampDisableClk1:1 ; ///<
    UINT32                                          RampDisableClk0:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                         SoftOverrideClk6:1 ; ///<
    UINT32                                         SoftOverrideClk5:1 ; ///<
    UINT32                                         SoftOverrideClk4:1 ; ///<
    UINT32                                         SoftOverrideClk3:1 ; ///<
    UINT32                                         SoftOverrideClk2:1 ; ///<
    UINT32                                         SoftOverrideClk1:1 ; ///<
    UINT32                                         SoftOverrideClk0:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0x98_x4A_STRUCT;

// **** D0F0xD4_x010914C3 Register Definition ****
// Address
#define D0F0xD4_x010914C3_ADDRESS                              0x10914c3

// Type
#define D0F0xD4_x010914C3_TYPE                                 TYPE_D0F0xD4
// Field Data
#define D0F0xD4_x010914C3_SelfRingDis_OFFSET                   0
#define D0F0xD4_x010914C3_SelfRingDis_WIDTH                    1
#define D0F0xD4_x010914C3_SelfRingDis_MASK                     0x1
#define D0F0xD4_x010914C3_TransCheckDis_OFFSET                 1
#define D0F0xD4_x010914C3_TransCheckDis_WIDTH                  1
#define D0F0xD4_x010914C3_TransCheckDis_MASK                   0x2
#define D0F0xD4_x010914C3_UntransLbackEn_OFFSET                2
#define D0F0xD4_x010914C3_UntransLbackEn_WIDTH                 1
#define D0F0xD4_x010914C3_UntransLbackEn_MASK                  0x4
#define D0F0xD4_x010914C3_NonConsecutiveBeZeroDis_OFFSET       3
#define D0F0xD4_x010914C3_NonConsecutiveBeZeroDis_WIDTH        1
#define D0F0xD4_x010914C3_NonConsecutiveBeZeroDis_MASK         0x8
#define D0F0xD4_x010914C3_Reserved_31_4_OFFSET                 4
#define D0F0xD4_x010914C3_Reserved_31_4_WIDTH                  28
#define D0F0xD4_x010914C3_Reserved_31_4_MASK                   0xfffffff0

/// D0F0xD4_x010914C3
typedef union {
  struct {                                                              ///<
    UINT32                                              SelfRingDis:1 ; ///<
    UINT32                                            TransCheckDis:1 ; ///<
    UINT32                                           UntransLbackEn:1 ; ///<
    UINT32                                  NonConsecutiveBeZeroDis:1 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD4_x010914C3_STRUCT;

// **** D0F0xD4_x010914E1 Register Definition ****
// Address
#define D0F0xD4_x010914E1_ADDRESS                              0x10914e1

// Type
#define D0F0xD4_x010914E1_TYPE                                 TYPE_D0F0xD4
// Field Data
#define D0F0xD4_x010914E1_Reserved_0_0_OFFSET                  0
#define D0F0xD4_x010914E1_Reserved_0_0_WIDTH                   1
#define D0F0xD4_x010914E1_Reserved_0_0_MASK                    0x1
#define D0F0xD4_x010914E1_StrapBifRegApSize_OFFSET             1
#define D0F0xD4_x010914E1_StrapBifRegApSize_WIDTH              2
#define D0F0xD4_x010914E1_StrapBifRegApSize_MASK               0x6
#define D0F0xD4_x010914E1_StrapBifMemApSize_OFFSET             3
#define D0F0xD4_x010914E1_StrapBifMemApSize_WIDTH              3
#define D0F0xD4_x010914E1_StrapBifMemApSize_MASK               0x38
#define D0F0xD4_x010914E1_StrapBifRomApSize_OFFSET             6
#define D0F0xD4_x010914E1_StrapBifRomApSize_WIDTH              2
#define D0F0xD4_x010914E1_StrapBifRomApSize_MASK               0xc0
#define D0F0xD4_x010914E1_StrapBifFbAlwaysOn_OFFSET            8
#define D0F0xD4_x010914E1_StrapBifFbAlwaysOn_WIDTH             1
#define D0F0xD4_x010914E1_StrapBifFbAlwaysOn_MASK              0x100
#define D0F0xD4_x010914E1_StrapBifFbCplTypeSel_OFFSET          9
#define D0F0xD4_x010914E1_StrapBifFbCplTypeSel_WIDTH           2
#define D0F0xD4_x010914E1_StrapBifFbCplTypeSel_MASK            0x600
#define D0F0xD4_x010914E1_StrapBifDebugAccess_OFFSET           11
#define D0F0xD4_x010914E1_StrapBifDebugAccess_WIDTH            1
#define D0F0xD4_x010914E1_StrapBifDebugAccess_MASK             0x800
#define D0F0xD4_x010914E1_StrapBifDoorbellBarDis_OFFSET        12
#define D0F0xD4_x010914E1_StrapBifDoorbellBarDis_WIDTH         1
#define D0F0xD4_x010914E1_StrapBifDoorbellBarDis_MASK          0x1000
#define D0F0xD4_x010914E1_StrapBifBarComplianceEn_OFFSET       13
#define D0F0xD4_x010914E1_StrapBifBarComplianceEn_WIDTH        1
#define D0F0xD4_x010914E1_StrapBifBarComplianceEn_MASK         0x2000
#define D0F0xD4_x010914E1_StrapBifBarDoorbellAperSize_OFFSET   14
#define D0F0xD4_x010914E1_StrapBifBarDoorbellAperSize_WIDTH    2
#define D0F0xD4_x010914E1_StrapBifBarDoorbellAperSize_MASK     0xc000
#define D0F0xD4_x010914E1_StrapReserved_OFFSET                 16
#define D0F0xD4_x010914E1_StrapReserved_WIDTH                  11
#define D0F0xD4_x010914E1_StrapReserved_MASK                   0x7ff0000
#define D0F0xD4_x010914E1_Reserved_31_27_OFFSET                27
#define D0F0xD4_x010914E1_Reserved_31_27_WIDTH                 5
#define D0F0xD4_x010914E1_Reserved_31_27_MASK                  0xf8000000

/// D0F0xD4_x010914E1
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                        StrapBifRegApSize:2 ; ///<
    UINT32                                        StrapBifMemApSize:3 ; ///<
    UINT32                                        StrapBifRomApSize:2 ; ///<
    UINT32                                       StrapBifFbAlwaysOn:1 ; ///<
    UINT32                                     StrapBifFbCplTypeSel:2 ; ///<
    UINT32                                      StrapBifDebugAccess:1 ; ///<
    UINT32                                   StrapBifDoorbellBarDis:1 ; ///<
    UINT32                                  StrapBifBarComplianceEn:1 ; ///<
    UINT32                              StrapBifBarDoorbellAperSize:2 ; ///<
    UINT32                                            StrapReserved:11; ///<
    UINT32                                           Reserved_31_27:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD4_x010914E1_STRUCT;

// **** D0F0xD4_x010914E2 Register Definition ****
// Address
#define D0F0xD4_x010914E2_ADDRESS                              0x10914e2

// Type
#define D0F0xD4_x010914E2_TYPE                                 TYPE_D0F0xD4
// Field Data
#define D0F0xD4_x010914E2_Reserved_0_0_OFFSET                  0
#define D0F0xD4_x010914E2_Reserved_0_0_WIDTH                   1
#define D0F0xD4_x010914E2_Reserved_0_0_MASK                    0x1
#define D0F0xD4_x010914E2_StrapBifIoBarDis_OFFSET              1
#define D0F0xD4_x010914E2_StrapBifIoBarDis_WIDTH               1
#define D0F0xD4_x010914E2_StrapBifIoBarDis_MASK                0x2
#define D0F0xD4_x010914E2_StrapBifVgaDis_OFFSET                2
#define D0F0xD4_x010914E2_StrapBifVgaDis_WIDTH                 1
#define D0F0xD4_x010914E2_StrapBifVgaDis_MASK                  0x4
#define D0F0xD4_x010914E2_StrapBifF064BarDisA_OFFSET           3
#define D0F0xD4_x010914E2_StrapBifF064BarDisA_WIDTH            1
#define D0F0xD4_x010914E2_StrapBifF064BarDisA_MASK             0x8
#define D0F0xD4_x010914E2_StrapCec64BarDis_OFFSET              4
#define D0F0xD4_x010914E2_StrapCec64BarDis_WIDTH               1
#define D0F0xD4_x010914E2_StrapCec64BarDis_MASK                0x10
#define D0F0xD4_x010914E2_StrapBifAz64BarDisA_OFFSET           5
#define D0F0xD4_x010914E2_StrapBifAz64BarDisA_WIDTH            1
#define D0F0xD4_x010914E2_StrapBifAz64BarDisA_MASK             0x20
#define D0F0xD4_x010914E2_StrapBifF0BarEn_OFFSET               6
#define D0F0xD4_x010914E2_StrapBifF0BarEn_WIDTH                1
#define D0F0xD4_x010914E2_StrapBifF0BarEn_MASK                 0x40
#define D0F0xD4_x010914E2_StrapBifRxIgnoreMsgErr_OFFSET        7
#define D0F0xD4_x010914E2_StrapBifRxIgnoreMsgErr_WIDTH         1
#define D0F0xD4_x010914E2_StrapBifRxIgnoreMsgErr_MASK          0x80
#define D0F0xD4_x010914E2_StrapBifF0LegacyDeviceTypeDis_OFFSET 8
#define D0F0xD4_x010914E2_StrapBifF0LegacyDeviceTypeDis_WIDTH  1
#define D0F0xD4_x010914E2_StrapBifF0LegacyDeviceTypeDis_MASK   0x100
#define D0F0xD4_x010914E2_StrapBifF2LegacyDeviceTypeDis_OFFSET 9
#define D0F0xD4_x010914E2_StrapBifF2LegacyDeviceTypeDis_WIDTH  1
#define D0F0xD4_x010914E2_StrapBifF2LegacyDeviceTypeDis_MASK   0x200
#define D0F0xD4_x010914E2_StrapBifAzLegacyDeviceTypeDis_OFFSET 10
#define D0F0xD4_x010914E2_StrapBifAzLegacyDeviceTypeDis_WIDTH  1
#define D0F0xD4_x010914E2_StrapBifAzLegacyDeviceTypeDis_MASK   0x400
#define D0F0xD4_x010914E2_StrapBifRxIgnoreEpErr_OFFSET         11
#define D0F0xD4_x010914E2_StrapBifRxIgnoreEpErr_WIDTH          1
#define D0F0xD4_x010914E2_StrapBifRxIgnoreEpErr_MASK           0x800
#define D0F0xD4_x010914E2_StrapCecPmeSupportComplianceDis_OFFSET 12
#define D0F0xD4_x010914E2_StrapCecPmeSupportComplianceDis_WIDTH 1
#define D0F0xD4_x010914E2_StrapCecPmeSupportComplianceDis_MASK 0x1000
#define D0F0xD4_x010914E2_StrapBifAudioEn_OFFSET               13
#define D0F0xD4_x010914E2_StrapBifAudioEn_WIDTH                1
#define D0F0xD4_x010914E2_StrapBifAudioEn_MASK                 0x2000
#define D0F0xD4_x010914E2_StrapReserved_OFFSET                 14
#define D0F0xD4_x010914E2_StrapReserved_WIDTH                  8
#define D0F0xD4_x010914E2_StrapReserved_MASK                   0x3fc000
#define D0F0xD4_x010914E2_Reserved_31_22_OFFSET                22
#define D0F0xD4_x010914E2_Reserved_31_22_WIDTH                 10
#define D0F0xD4_x010914E2_Reserved_31_22_MASK                  0xffc00000

/// D0F0xD4_x010914E2
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                         StrapBifIoBarDis:1 ; ///<
    UINT32                                           StrapBifVgaDis:1 ; ///<
    UINT32                                      StrapBifF064BarDisA:1 ; ///<
    UINT32                                         StrapCec64BarDis:1 ; ///<
    UINT32                                      StrapBifAz64BarDisA:1 ; ///<
    UINT32                                          StrapBifF0BarEn:1 ; ///<
    UINT32                                   StrapBifRxIgnoreMsgErr:1 ; ///<
    UINT32                            StrapBifF0LegacyDeviceTypeDis:1 ; ///<
    UINT32                            StrapBifF2LegacyDeviceTypeDis:1 ; ///<
    UINT32                            StrapBifAzLegacyDeviceTypeDis:1 ; ///<
    UINT32                                    StrapBifRxIgnoreEpErr:1 ; ///<
    UINT32                          StrapCecPmeSupportComplianceDis:1 ; ///<
    UINT32                                          StrapBifAudioEn:1 ; ///<
    UINT32                                            StrapReserved:8 ; ///<
    UINT32                                           Reserved_31_22:10; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD4_x010914E2_STRUCT;

// **** D0F0xD4_x01091507 Register Definition ****
// Address
#define D0F0xD4_x01091507_ADDRESS                              0x1091507

// Type
#define D0F0xD4_x01091507_TYPE                                 TYPE_D0F0xD4
// Field Data
#define D0F0xD4_x01091507_Reserved_0_0_OFFSET                  0
#define D0F0xD4_x01091507_Reserved_0_0_WIDTH                   1
#define D0F0xD4_x01091507_Reserved_0_0_MASK                    0x1
#define D0F0xD4_x01091507_StrapBifGen3EnA_OFFSET               1
#define D0F0xD4_x01091507_StrapBifGen3EnA_WIDTH                1
#define D0F0xD4_x01091507_StrapBifGen3EnA_MASK                 0x2
#define D0F0xD4_x01091507_StrapBifClkPmEn_OFFSET               2
#define D0F0xD4_x01091507_StrapBifClkPmEn_WIDTH                1
#define D0F0xD4_x01091507_StrapBifClkPmEn_MASK                 0x4
#define D0F0xD4_x01091507_StrapBifBiosRomEn_OFFSET             3
#define D0F0xD4_x01091507_StrapBifBiosRomEn_WIDTH              1
#define D0F0xD4_x01091507_StrapBifBiosRomEn_MASK               0x8
#define D0F0xD4_x01091507_StrapBifSmbusDis_OFFSET              4
#define D0F0xD4_x01091507_StrapBifSmbusDis_WIDTH               1
#define D0F0xD4_x01091507_StrapBifSmbusDis_MASK                0x10
#define D0F0xD4_x01091507_StrapBifMemApSizePin_OFFSET          5
#define D0F0xD4_x01091507_StrapBifMemApSizePin_WIDTH           3
#define D0F0xD4_x01091507_StrapBifMemApSizePin_MASK            0xe0
#define D0F0xD4_x01091507_Reserved_8_8_OFFSET                  8
#define D0F0xD4_x01091507_Reserved_8_8_WIDTH                   1
#define D0F0xD4_x01091507_Reserved_8_8_MASK                    0x100
#define D0F0xD4_x01091507_StrapBifVgaDisPin_OFFSET             9
#define D0F0xD4_x01091507_StrapBifVgaDisPin_WIDTH              1
#define D0F0xD4_x01091507_StrapBifVgaDisPin_MASK               0x200
#define D0F0xD4_x01091507_Reserved_10_10_OFFSET                10
#define D0F0xD4_x01091507_Reserved_10_10_WIDTH                 1
#define D0F0xD4_x01091507_Reserved_10_10_MASK                  0x400
#define D0F0xD4_x01091507_StrapTxCfgDrvFullSwing_OFFSET        11
#define D0F0xD4_x01091507_StrapTxCfgDrvFullSwing_WIDTH         1
#define D0F0xD4_x01091507_StrapTxCfgDrvFullSwing_MASK          0x800
#define D0F0xD4_x01091507_Reserved_15_12_OFFSET                12
#define D0F0xD4_x01091507_Reserved_15_12_WIDTH                 4
#define D0F0xD4_x01091507_Reserved_15_12_MASK                  0xf000
#define D0F0xD4_x01091507_StrapBifAudioEnPin_OFFSET            16
#define D0F0xD4_x01091507_StrapBifAudioEnPin_WIDTH             1
#define D0F0xD4_x01091507_StrapBifAudioEnPin_MASK              0x10000
#define D0F0xD4_x01091507_StrapBifCecEnPin_OFFSET              17
#define D0F0xD4_x01091507_StrapBifCecEnPin_WIDTH               1
#define D0F0xD4_x01091507_StrapBifCecEnPin_MASK                0x20000
#define D0F0xD4_x01091507_Reserved_31_18_OFFSET                18
#define D0F0xD4_x01091507_Reserved_31_18_WIDTH                 14
#define D0F0xD4_x01091507_Reserved_31_18_MASK                  0xfffc0000

/// D0F0xD4_x01091507
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                          StrapBifGen3EnA:1 ; ///<
    UINT32                                          StrapBifClkPmEn:1 ; ///<
    UINT32                                        StrapBifBiosRomEn:1 ; ///<
    UINT32                                         StrapBifSmbusDis:1 ; ///<
    UINT32                                     StrapBifMemApSizePin:3 ; ///<
    UINT32                                             Reserved_8_8:1 ; ///<
    UINT32                                        StrapBifVgaDisPin:1 ; ///<
    UINT32                                           Reserved_10_10:1 ; ///<
    UINT32                                   StrapTxCfgDrvFullSwing:1 ; ///<
    UINT32                                           Reserved_15_12:4 ; ///<
    UINT32                                       StrapBifAudioEnPin:1 ; ///<
    UINT32                                         StrapBifCecEnPin:1 ; ///<
    UINT32                                           Reserved_31_18:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD4_x01091507_STRUCT;

// **** D0F0xD4_x01091518 Register Definition ****
// Address
#define D0F0xD4_x01091518_ADDRESS                               0x1091518
// Type
#define D0F0xD4_x01091518_TYPE                                  TYPE_D0F0xD4

// Field Data
#define D0F0xD4_x01091518_LinkTrainEn_OFFSET                    0
#define D0F0xD4_x01091518_LinkTrainEn_WIDTH                     1
#define D0F0xD4_x01091518_LinkTrainEn_MASK                      0x1
#define D0F0xD4_x01091518_Reserved_31_1_OFFSET                  1
#define D0F0xD4_x01091518_Reserved_31_1_WIDTH                   31
#define D0F0xD4_x01091518_Reserved_31_1_MASK                    0xFFFFFFFE

/// D0F0xD4_x01091518
typedef union {
  struct {                                                            ///<
    UINT32                                             LinkTrainEn:1; ///<
    UINT32                                           Reserved_31_1:31; ///<

  } Field;

  UINT32 Value;
} D0F0xD4_x01091518_STRUCT;

// **** D0F0xD4_x01301486 Register Definition ****
// Address
#define D0F0xD4_x01301486_ADDRESS                               0x1301486
// Type
#define D0F0xD4_x01301486_TYPE                                  TYPE_D0F0xD4

// Field Data
#define D0F0xD4_x01301486_StrapEn_OFFSET                        0
#define D0F0xD4_x01301486_StrapEn_WIDTH                         1
#define D0F0xD4_x01301486_StrapEn_MASK                          0x1
#define D0F0xD4_x01301486_RstDone_OFFSET                        1
#define D0F0xD4_x01301486_RstDone_WIDTH                         1
#define D0F0xD4_x01301486_RstDone_MASK                          0x2
#define D0F0xD4_x01301486_LinkTrainEn_OFFSET                    2
#define D0F0xD4_x01301486_LinkTrainEn_WIDTH                     1
#define D0F0xD4_x01301486_LinkTrainEn_MASK                      0x4
#define D0F0xD4_x01301486_StrapAllValid_OFFSET                  3
#define D0F0xD4_x01301486_StrapAllValid_WIDTH                   1
#define D0F0xD4_x01301486_StrapAllValid_MASK                    0x8
#define D0F0xD4_x01301486_Reserved_7_4_OFFSET                   4
#define D0F0xD4_x01301486_Reserved_7_4_WIDTH                    4
#define D0F0xD4_x01301486_Reserved_7_4_MASK                     0xF0
#define D0F0xD4_x01301486_RecapStrapWarmrst_OFFSET              8
#define D0F0xD4_x01301486_RecapStrapWarmrst_WIDTH               1
#define D0F0xD4_x01301486_RecapStrapWarmrst_MASK                0x100
#define D0F0xD4_x01301486_Reserved_31_9_OFFSET                  9
#define D0F0xD4_x01301486_Reserved_31_9_WIDTH                   23
#define D0F0xD4_x01301486_Reserved_31_9_MASK                    0xFFFFFE00

/// D0F0xD4_x01301486
typedef union {
  struct {                                                            ///<
    UINT32                                                 StrapEn:1; ///<
    UINT32                                                 RstDone:1; ///<
    UINT32                                             LinkTrainEn:1; ///<
    UINT32                                           StrapAllValid:1; ///<
    UINT32                                            Reserved_7_4:4; ///<
    UINT32                                       RecapStrapWarmrst:1; ///<
    UINT32                                           Reserved_31_9:23; ///<

  } Field;

  UINT32 Value;
} D0F0xD4_x01301486_STRUCT;

// **** D0F0xD4_x013014AC Register Definition ****
// Address
#define D0F0xD4_x013014AC_ADDRESS                               0x13014AC
// Type
#define D0F0xD4_x013014AC_TYPE                                  TYPE_D0F0xD4

// Field Data
#define D0F0xD4_x013014AC_Reserved_0_0_OFFSET                   0
#define D0F0xD4_x013014AC_Reserved_0_0_WIDTH                    1
#define D0F0xD4_x013014AC_Reserved_0_0_MASK                     0x1
#define D0F0xD4_x013014AC_StrapBifGen3EnA_OFFSET                1
#define D0F0xD4_x013014AC_StrapBifGen3EnA_WIDTH                 1
#define D0F0xD4_x013014AC_StrapBifGen3EnA_MASK                  0x2
#define D0F0xD4_x013014AC_StrapBifClkPmEn_OFFSET                2
#define D0F0xD4_x013014AC_StrapBifClkPmEn_WIDTH                 1
#define D0F0xD4_x013014AC_StrapBifClkPmEn_MASK                  0x4
#define D0F0xD4_x013014AC_StrapBifBiosRomEn_OFFSET              3
#define D0F0xD4_x013014AC_StrapBifBiosRomEn_WIDTH               1
#define D0F0xD4_x013014AC_StrapBifBiosRomEn_MASK                0x8
#define D0F0xD4_x013014AC_StrapBifSmbusDis_OFFSET               4
#define D0F0xD4_x013014AC_StrapBifSmbusDis_WIDTH                1
#define D0F0xD4_x013014AC_StrapBifSmbusDis_MASK                 0x10
#define D0F0xD4_x013014AC_StrapBifMemApSizePin_OFFSET           5
#define D0F0xD4_x013014AC_StrapBifMemApSizePin_WIDTH            3
#define D0F0xD4_x013014AC_StrapBifMemApSizePin_MASK             0xE0
#define D0F0xD4_x013014AC_Reserved_8_8_OFFSET                   8
#define D0F0xD4_x013014AC_Reserved_8_8_WIDTH                    1
#define D0F0xD4_x013014AC_Reserved_8_8_MASK                     0x100
#define D0F0xD4_x013014AC_StrapBifVgaDisPin_OFFSET              9
#define D0F0xD4_x013014AC_StrapBifVgaDisPin_WIDTH               1
#define D0F0xD4_x013014AC_StrapBifVgaDisPin_MASK                0x200
#define D0F0xD4_x013014AC_Reserved_10_10_OFFSET                 10
#define D0F0xD4_x013014AC_Reserved_10_10_WIDTH                  1
#define D0F0xD4_x013014AC_Reserved_10_10_MASK                   0x400
#define D0F0xD4_x013014AC_StrapTxCfgDrvFullSwing_OFFSET         11
#define D0F0xD4_x013014AC_StrapTxCfgDrvFullSwing_WIDTH          1
#define D0F0xD4_x013014AC_StrapTxCfgDrvFullSwing_MASK           0x800
#define D0F0xD4_x013014AC_Reserved_15_12_OFFSET                 12
#define D0F0xD4_x013014AC_Reserved_15_12_WIDTH                  4
#define D0F0xD4_x013014AC_Reserved_15_12_MASK                   0xF000
#define D0F0xD4_x013014AC_StrapBifAudioEnPin_OFFSET             16
#define D0F0xD4_x013014AC_StrapBifAudioEnPin_WIDTH              1
#define D0F0xD4_x013014AC_StrapBifAudioEnPin_MASK               0x10000
#define D0F0xD4_x013014AC_StrapBifCecEnPin_OFFSET               17
#define D0F0xD4_x013014AC_StrapBifCecEnPin_WIDTH                1
#define D0F0xD4_x013014AC_StrapBifCecEnPin_MASK                 0x20000
#define D0F0xD4_x013014AC_Reserved_31_18_OFFSET                 18
#define D0F0xD4_x013014AC_Reserved_31_18_WIDTH                  14
#define D0F0xD4_x013014AC_Reserved_31_18_MASK                   0xFFFC0000

/// D0F0xD4_x013014AC
typedef union {
  struct {                                                            ///<
    UINT32                                            Reserved_0_0:1; ///<
    UINT32                                         StrapBifGen3EnA:1; ///<
    UINT32                                         StrapBifClkPmEn:1; ///<
    UINT32                                       StrapBifBiosRomEn:1; ///<
    UINT32                                        StrapBifSmbusDis:1; ///<
    UINT32                                    StrapBifMemApSizePin:3; ///<
    UINT32                                            Reserved_8_8:1; ///<
    UINT32                                       StrapBifVgaDisPin:1; ///<
    UINT32                                          Reserved_10_10:1; ///<
    UINT32                                  StrapTxCfgDrvFullSwing:1; ///<
    UINT32                                          Reserved_15_12:4; ///<
    UINT32                                      StrapBifAudioEnPin:1; ///<
    UINT32                                        StrapBifCecEnPin:1; ///<
    UINT32                                          Reserved_31_18:14; ///<

  } Field;

  UINT32 Value;
} D0F0xD4_x013014AC_STRUCT;

// **** D0F0xD4_x013014B6 Register Definition ****
// Address
#define D0F0xD4_x013014B6_ADDRESS                               0x13014B6
// Type
#define D0F0xD4_x013014B6_TYPE                                  TYPE_D0F0xD4

// Field Data
#define D0F0xD4_x013014B6_Reserved_0_0_OFFSET                   0
#define D0F0xD4_x013014B6_Reserved_0_0_WIDTH                    1
#define D0F0xD4_x013014B6_Reserved_0_0_MASK                     0x1
#define D0F0xD4_x013014B6_StrapBifIoBarDis_OFFSET               1
#define D0F0xD4_x013014B6_StrapBifIoBarDis_WIDTH                1
#define D0F0xD4_x013014B6_StrapBifIoBarDis_MASK                 0x2
#define D0F0xD4_x013014B6_StrapBifVgaDis_OFFSET                 2
#define D0F0xD4_x013014B6_StrapBifVgaDis_WIDTH                  1
#define D0F0xD4_x013014B6_StrapBifVgaDis_MASK                   0x4
#define D0F0xD4_x013014B6_StrapBifF064BarDisA_OFFSET            3
#define D0F0xD4_x013014B6_StrapBifF064BarDisA_WIDTH             1
#define D0F0xD4_x013014B6_StrapBifF064BarDisA_MASK              0x8
#define D0F0xD4_x013014B6_StrapCec64BarDis_OFFSET               4
#define D0F0xD4_x013014B6_StrapCec64BarDis_WIDTH                1
#define D0F0xD4_x013014B6_StrapCec64BarDis_MASK                 0x10
#define D0F0xD4_x013014B6_StrapBifAz64BarDisA_OFFSET            5
#define D0F0xD4_x013014B6_StrapBifAz64BarDisA_WIDTH             1
#define D0F0xD4_x013014B6_StrapBifAz64BarDisA_MASK              0x20
#define D0F0xD4_x013014B6_StrapBifF0BarEn_OFFSET                6
#define D0F0xD4_x013014B6_StrapBifF0BarEn_WIDTH                 1
#define D0F0xD4_x013014B6_StrapBifF0BarEn_MASK                  0x40
#define D0F0xD4_x013014B6_StrapBifRxIgnoreMsgErr_OFFSET         7
#define D0F0xD4_x013014B6_StrapBifRxIgnoreMsgErr_WIDTH          1
#define D0F0xD4_x013014B6_StrapBifRxIgnoreMsgErr_MASK           0x80
#define D0F0xD4_x013014B6_StrapBifF0LegacyDeviceTypeDis_OFFSET  8
#define D0F0xD4_x013014B6_StrapBifF0LegacyDeviceTypeDis_WIDTH   1
#define D0F0xD4_x013014B6_StrapBifF0LegacyDeviceTypeDis_MASK    0x100
#define D0F0xD4_x013014B6_StrapBifF2LegacyDeviceTypeDis_OFFSET  9
#define D0F0xD4_x013014B6_StrapBifF2LegacyDeviceTypeDis_WIDTH   1
#define D0F0xD4_x013014B6_StrapBifF2LegacyDeviceTypeDis_MASK    0x200
#define D0F0xD4_x013014B6_StrapBifAzLegacyDeviceTypeDis_OFFSET  10
#define D0F0xD4_x013014B6_StrapBifAzLegacyDeviceTypeDis_WIDTH   1
#define D0F0xD4_x013014B6_StrapBifAzLegacyDeviceTypeDis_MASK    0x400
#define D0F0xD4_x013014B6_StrapBifRxIgnoreEpErr_OFFSET          11
#define D0F0xD4_x013014B6_StrapBifRxIgnoreEpErr_WIDTH           1
#define D0F0xD4_x013014B6_StrapBifRxIgnoreEpErr_MASK            0x800
#define D0F0xD4_x013014B6_StrapCecPmeSupportComplianceDis_OFFSET 12
#define D0F0xD4_x013014B6_StrapCecPmeSupportComplianceDis_WIDTH 1
#define D0F0xD4_x013014B6_StrapCecPmeSupportComplianceDis_MASK  0x1000
#define D0F0xD4_x013014B6_StrapBifAudioEn_OFFSET                13
#define D0F0xD4_x013014B6_StrapBifAudioEn_WIDTH                 1
#define D0F0xD4_x013014B6_StrapBifAudioEn_MASK                  0x2000
#define D0F0xD4_x013014B6_StrapReserved_OFFSET                  14
#define D0F0xD4_x013014B6_StrapReserved_WIDTH                   8
#define D0F0xD4_x013014B6_StrapReserved_MASK                    0x3FC000
#define D0F0xD4_x013014B6_Reserved_31_22_OFFSET                 22
#define D0F0xD4_x013014B6_Reserved_31_22_WIDTH                  10
#define D0F0xD4_x013014B6_Reserved_31_22_MASK                   0xFFC00000

/// D0F0xD4_x013014B6
typedef union {
  struct {                                                            ///<
    UINT32                                            Reserved_0_0:1; ///<
    UINT32                                        StrapBifIoBarDis:1; ///<
    UINT32                                          StrapBifVgaDis:1; ///<
    UINT32                                     StrapBifF064BarDisA:1; ///<
    UINT32                                        StrapCec64BarDis:1; ///<
    UINT32                                     StrapBifAz64BarDisA:1; ///<
    UINT32                                         StrapBifF0BarEn:1; ///<
    UINT32                                  StrapBifRxIgnoreMsgErr:1; ///<
    UINT32                           StrapBifF0LegacyDeviceTypeDis:1; ///<
    UINT32                           StrapBifF2LegacyDeviceTypeDis:1; ///<
    UINT32                           StrapBifAzLegacyDeviceTypeDis:1; ///<
    UINT32                                   StrapBifRxIgnoreEpErr:1; ///<
    UINT32                         StrapCecPmeSupportComplianceDis:1; ///<
    UINT32                                         StrapBifAudioEn:1; ///<
    UINT32                                           StrapReserved:8; ///<
    UINT32                                          Reserved_31_22:10; ///<

  } Field;

  UINT32 Value;
} D0F0xD4_x013014B6_STRUCT;

// **** D0F0xD4_x013014B8 Register Definition ****
// Address
#define D0F0xD4_x013014B8_ADDRESS                              0x13014b8

// Type
#define D0F0xD4_x013014B8_TYPE                                 TYPE_D0F0xD4
// Field Data
#define D0F0xD4_x013014B8_Reserved_0_0_OFFSET                  0
#define D0F0xD4_x013014B8_Reserved_0_0_WIDTH                   1
#define D0F0xD4_x013014B8_Reserved_0_0_MASK                    0x1
#define D0F0xD4_x013014B8_StrapBifL1AcceptableLatency_OFFSET   1
#define D0F0xD4_x013014B8_StrapBifL1AcceptableLatency_WIDTH    3
#define D0F0xD4_x013014B8_StrapBifL1AcceptableLatency_MASK     0xe
#define D0F0xD4_x013014B8_StrapBifPmSupport_OFFSET             4
#define D0F0xD4_x013014B8_StrapBifPmSupport_WIDTH              2
#define D0F0xD4_x013014B8_StrapBifPmSupport_MASK               0x30
#define D0F0xD4_x013014B8_StrapBifInitialNFts_OFFSET           6
#define D0F0xD4_x013014B8_StrapBifInitialNFts_WIDTH            8
#define D0F0xD4_x013014B8_StrapBifInitialNFts_MASK             0x3fc0
#define D0F0xD4_x013014B8_StrapBifE2ePrefixEnA_OFFSET          14
#define D0F0xD4_x013014B8_StrapBifE2ePrefixEnA_WIDTH           1
#define D0F0xD4_x013014B8_StrapBifE2ePrefixEnA_MASK            0x4000
#define D0F0xD4_x013014B8_StrapBifExtendedFmtSupportedA_OFFSET 15
#define D0F0xD4_x013014B8_StrapBifExtendedFmtSupportedA_WIDTH  1
#define D0F0xD4_x013014B8_StrapBifExtendedFmtSupportedA_MASK   0x8000
#define D0F0xD4_x013014B8_StrapBifPasidPrefixSupported_OFFSET  16
#define D0F0xD4_x013014B8_StrapBifPasidPrefixSupported_WIDTH   1
#define D0F0xD4_x013014B8_StrapBifPasidPrefixSupported_MASK    0x10000
#define D0F0xD4_x013014B8_StrapBifMaxPasidWidth_OFFSET         17
#define D0F0xD4_x013014B8_StrapBifMaxPasidWidth_WIDTH          5
#define D0F0xD4_x013014B8_StrapBifMaxPasidWidth_MASK           0x3e0000
#define D0F0xD4_x013014B8_StrapBifF0AtsEn_OFFSET               22
#define D0F0xD4_x013014B8_StrapBifF0AtsEn_WIDTH                1
#define D0F0xD4_x013014B8_StrapBifF0AtsEn_MASK                 0x400000
#define D0F0xD4_x013014B8_Reserved_31_23_OFFSET                23
#define D0F0xD4_x013014B8_Reserved_31_23_WIDTH                 9
#define D0F0xD4_x013014B8_Reserved_31_23_MASK                  0xff800000

/// D0F0xD4_x0130_14B8
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                              StrapBifL1AcceptableLatency:3 ; ///<
    UINT32                                        StrapBifPmSupport:2 ; ///<
    UINT32                                      StrapBifInitialNFts:8 ; ///<
    UINT32                                     StrapBifE2ePrefixEnA:1 ; ///<
    UINT32                            StrapBifExtendedFmtSupportedA:1 ; ///<
    UINT32                             StrapBifPasidPrefixSupported:1 ; ///<
    UINT32                                    StrapBifMaxPasidWidth:5 ; ///<
    UINT32                                          StrapBifF0AtsEn:1 ; ///<
    UINT32                                           Reserved_31_23:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD4_x013014B8_STRUCT;

// **** D0F0xD4_x013014BE Register Definition ****
// Address
#define D0F0xD4_x013014BE_ADDRESS                                     0x013014BE

// Type
#define D0F0xD4_x013014BE_TYPE                                        TYPE_D0F0xD4
// Field Data
#define D0F0xD4_x013014BE_Reserved_19_0_OFFSET                        0
#define D0F0xD4_x013014BE_Reserved_19_0_WIDTH                         20
#define D0F0xD4_x013014BE_Reserved_19_0_MASK                          0xfffff
#define D0F0xD4_x013014BE_StrapBifSymalignHwDebug_OFFSET              20
#define D0F0xD4_x013014BE_StrapBifSymalignHwDebug_WIDTH               1
#define D0F0xD4_x013014BE_StrapBifSymalignHwDebug_MASK                0x100000
#define D0F0xD4_x013014BE_Reserved_31_21_OFFSET                       21
#define D0F0xD4_x013014BE_Reserved_31_21_WIDTH                        11
#define D0F0xD4_x013014BE_Reserved_31_21_MASK                         0xffe00000

/// D0F0xD4_x013014BE
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_19_0:20; ///<
    UINT32                                  StrapBifSymalignHwDebug:1 ; ///<
    UINT32                                           Reserved_31_21:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xD4_x013014BE_STRUCT;

// **** D0F0xBC_x13000000 Register Definition ****
// Address
#define D0F0xBC_x13000000_ADDRESS                                        0x13000000

// Type
#define D0F0xBC_x13000000_TYPE                                           TYPE_D0F0xBC
// Field Data
#define D0F0xBC_x13000000_CONTENT_OFFSET                                 0
#define D0F0xBC_x13000000_CONTENT_WIDTH                                  32
#define D0F0xBC_x13000000_CONTENT_MASK                                   0xffffffff

/// D0F0xBC_x13000000
typedef union {
  struct {                                                              ///<
    UINT32                                                  CONTENT:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_x13000000_STRUCT;

// **** D0F0xBC_x13000010 Register Definition ****
// Address
#define D0F0xBC_x13000010_ADDRESS                                        0x13000010

// Type
#define D0F0xBC_x13000010_TYPE                                           TYPE_D0F0xBC
// Field Data
#define D0F0xBC_x13000010_CONTENT_OFFSET                                 0
#define D0F0xBC_x13000010_CONTENT_WIDTH                                  32
#define D0F0xBC_x13000010_CONTENT_MASK                                   0xffffffff

/// D0F0xBC_x13000010
typedef union {
  struct {                                                              ///<
    UINT32                                                  CONTENT:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_x13000010_STRUCT;

// **** D0F0xBC_x13000020 Register Definition ****
// Address
#define D0F0xBC_x13000020_ADDRESS                                        0x13000020

// Type
#define D0F0xBC_x13000020_TYPE                                           TYPE_D0F0xBC
// Field Data
#define D0F0xBC_x13000020_CONTENT_OFFSET                                 0
#define D0F0xBC_x13000020_CONTENT_WIDTH                                  32
#define D0F0xBC_x13000020_CONTENT_MASK                                   0xffffffff

/// D0F0xBC_x13000020
typedef union {
  struct {                                                              ///<
    UINT32                                                  CONTENT:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_x13000020_STRUCT;

// **** D0F0xBC_x13000024 Register Definition ****
// Address
#define D0F0xBC_x13000024_ADDRESS                                        0x13000024

// Type
#define D0F0xBC_x13000024_TYPE                                           TYPE_D0F0xBC
// Field Data
#define D0F0xBC_x13000024_CONTENT_OFFSET                                 0
#define D0F0xBC_x13000024_CONTENT_WIDTH                                  32
#define D0F0xBC_x13000024_CONTENT_MASK                                   0xffffffff

/// D0F0xBC_x13000024
typedef union {
  struct {                                                              ///<
    UINT32                                                  CONTENT:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_x13000024_STRUCT;

// **** D0F0xBC_x13000028 Register Definition ****
// Address
#define D0F0xBC_x13000028_ADDRESS                                        0x13000028

// Type
#define D0F0xBC_x13000028_TYPE                                           TYPE_D0F0xBC
// Field Data
#define D0F0xBC_x13000028_CONTENT_OFFSET                                 0
#define D0F0xBC_x13000028_CONTENT_WIDTH                                  32
#define D0F0xBC_x13000028_CONTENT_MASK                                   0xffffffff

/// D0F0xBC_x13000028
typedef union {
  struct {                                                              ///<
    UINT32                                                  CONTENT:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_x13000028_STRUCT;

// **** D0F0xBC_x1300002C Register Definition ****
// Address
#define D0F0xBC_x1300002C_ADDRESS                                        0x1300002C

// Type
#define D0F0xBC_x1300002C_TYPE                                           TYPE_D0F0xBC
// Field Data
#define D0F0xBC_x1300002C_CONTENT_OFFSET                                 0
#define D0F0xBC_x1300002C_CONTENT_WIDTH                                  32
#define D0F0xBC_x1300002C_CONTENT_MASK                                   0xffffffff

/// D0F0xBC_x1300002C
typedef union {
  struct {                                                              ///<
    UINT32                                                  CONTENT:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_x1300002C_STRUCT;

// **** D0F0xBC_x13000030 Register Definition ****
// Address
#define D0F0xBC_x13000030_ADDRESS                                        0x13000030

// Type
#define D0F0xBC_x13000030_TYPE                                           TYPE_D0F0xBC

// **** D0F0xBC_x13000034 Register Definition ****
// Address
#define D0F0xBC_x13000034_ADDRESS                                        0x13000034

// Type
#define D0F0xBC_x13000034_TYPE                                           TYPE_D0F0xBC

// **** D0F0xE4_CORE_0002 Register Definition ****
// Address
#define D0F0xE4_CORE_0002_ADDRESS                               0x2

// Type
#define D0F0xE4_CORE_0002_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0002_HwDebug_0__OFFSET                     0
#define D0F0xE4_CORE_0002_HwDebug_0__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_0__MASK                       0x1
#define D0F0xE4_CORE_0002_HwDebug_0__VALUE                      0x1
#define D0F0xE4_CORE_0002_HwDebug_1__OFFSET                     1
#define D0F0xE4_CORE_0002_HwDebug_1__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_1__MASK                       0x2
#define D0F0xE4_CORE_0002_Reserved_2_2_OFFSET                   2
#define D0F0xE4_CORE_0002_Reserved_2_2_WIDTH                    1
#define D0F0xE4_CORE_0002_Reserved_2_2_MASK                     0x4
#define D0F0xE4_CORE_0002_HwDebug_3__OFFSET                     3
#define D0F0xE4_CORE_0002_HwDebug_3__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_3__MASK                       0x8
#define D0F0xE4_CORE_0002_HwDebug_4__OFFSET                     4
#define D0F0xE4_CORE_0002_HwDebug_4__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_4__MASK                       0x10
#define D0F0xE4_CORE_0002_HwDebug_5__OFFSET                     5
#define D0F0xE4_CORE_0002_HwDebug_5__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_5__MASK                       0x20
#define D0F0xE4_CORE_0002_HwDebug_6__OFFSET                     6
#define D0F0xE4_CORE_0002_HwDebug_6__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_6__MASK                       0x40
#define D0F0xE4_CORE_0002_HwDebug_7__OFFSET                     7
#define D0F0xE4_CORE_0002_HwDebug_7__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_7__MASK                       0x80
#define D0F0xE4_CORE_0002_HwDebug_8__OFFSET                     8
#define D0F0xE4_CORE_0002_HwDebug_8__WIDTH                      1
#define D0F0xE4_CORE_0002_HwDebug_8__MASK                       0x100
#define D0F0xE4_CORE_0002_HwDebug_11_9__OFFSET                  9
#define D0F0xE4_CORE_0002_HwDebug_11_9__WIDTH                   3
#define D0F0xE4_CORE_0002_HwDebug_11_9__MASK                    0xe00
#define D0F0xE4_CORE_0002_HwDebug_12__OFFSET                    12
#define D0F0xE4_CORE_0002_HwDebug_12__WIDTH                     1
#define D0F0xE4_CORE_0002_HwDebug_12__MASK                      0x1000
#define D0F0xE4_CORE_0002_HwDebug_14_13__OFFSET                 13
#define D0F0xE4_CORE_0002_HwDebug_14_13__WIDTH                  2
#define D0F0xE4_CORE_0002_HwDebug_14_13__MASK                   0x6000
#define D0F0xE4_CORE_0002_HwDebug_15__OFFSET                    15
#define D0F0xE4_CORE_0002_HwDebug_15__WIDTH                     1
#define D0F0xE4_CORE_0002_HwDebug_15__MASK                      0x8000
#define D0F0xE4_CORE_0002_Reserved_31_16_OFFSET                 16
#define D0F0xE4_CORE_0002_Reserved_31_16_WIDTH                  16
#define D0F0xE4_CORE_0002_Reserved_31_16_MASK                   0xffff0000

/// D0F0xE4_CORE_0002
typedef union {
  struct {                                                              ///<
    UINT32                                               HwDebug_0_:1 ; ///<
    UINT32                                               HwDebug_1_:1 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                               HwDebug_3_:1 ; ///<
    UINT32                                               HwDebug_4_:1 ; ///<
    UINT32                                               HwDebug_5_:1 ; ///<
    UINT32                                               HwDebug_6_:1 ; ///<
    UINT32                                               HwDebug_7_:1 ; ///<
    UINT32                                               HwDebug_8_:1 ; ///<
    UINT32                                            HwDebug_11_9_:3 ; ///<
    UINT32                                              HwDebug_12_:1 ; ///<
    UINT32                                           HwDebug_14_13_:2 ; ///<
    UINT32                                              HwDebug_15_:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0002_STRUCT;

// **** D0F0xE4_CORE_0010 Register Definition ****
// Address
#define D0F0xE4_CORE_0010_ADDRESS                               0x10

// Type
#define D0F0xE4_CORE_0010_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0010_HwInitWrLock_OFFSET                   0
#define D0F0xE4_CORE_0010_HwInitWrLock_WIDTH                    1
#define D0F0xE4_CORE_0010_HwInitWrLock_MASK                     0x1
#define D0F0xE4_CORE_0010_LcHotPlugDelSel_OFFSET                1
#define D0F0xE4_CORE_0010_LcHotPlugDelSel_WIDTH                 3
#define D0F0xE4_CORE_0010_LcHotPlugDelSel_MASK                  0xe
#define D0F0xE4_CORE_0010_Reserved_6_4_OFFSET                   4
#define D0F0xE4_CORE_0010_Reserved_6_4_WIDTH                    3
#define D0F0xE4_CORE_0010_Reserved_6_4_MASK                     0x70
#define D0F0xE4_CORE_0010_UrErrReportDis_OFFSET                 7
#define D0F0xE4_CORE_0010_UrErrReportDis_WIDTH                  1
#define D0F0xE4_CORE_0010_UrErrReportDis_MASK                   0x80
#define D0F0xE4_CORE_0010_PcieMalformAtomicOps_OFFSET           8
#define D0F0xE4_CORE_0010_PcieMalformAtomicOps_WIDTH            1
#define D0F0xE4_CORE_0010_PcieMalformAtomicOps_MASK             0x100
#define D0F0xE4_CORE_0010_UmiNpMemWrite_OFFSET                  9
#define D0F0xE4_CORE_0010_UmiNpMemWrite_WIDTH                   1
#define D0F0xE4_CORE_0010_UmiNpMemWrite_MASK                    0x200
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_OFFSET            10
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_WIDTH             3
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_MASK              0x1c00
#define D0F0xE4_CORE_0010_RxUmiAdjPayloadSize_VALUE             0x4
#define D0F0xE4_CORE_0010_Reserved_14_13_OFFSET                 13
#define D0F0xE4_CORE_0010_Reserved_14_13_WIDTH                  2
#define D0F0xE4_CORE_0010_Reserved_14_13_MASK                   0x6000
#define D0F0xE4_CORE_0010_RxRcbAtsUcDis_OFFSET                  15
#define D0F0xE4_CORE_0010_RxRcbAtsUcDis_WIDTH                   1
#define D0F0xE4_CORE_0010_RxRcbAtsUcDis_MASK                    0x8000
#define D0F0xE4_CORE_0010_RxRcbReorderEn_OFFSET                 16
#define D0F0xE4_CORE_0010_RxRcbReorderEn_WIDTH                  1
#define D0F0xE4_CORE_0010_RxRcbReorderEn_MASK                   0x10000
#define D0F0xE4_CORE_0010_RxRcbInvalidSizeDis_OFFSET            17
#define D0F0xE4_CORE_0010_RxRcbInvalidSizeDis_WIDTH             1
#define D0F0xE4_CORE_0010_RxRcbInvalidSizeDis_MASK              0x20000
#define D0F0xE4_CORE_0010_RxRcbUnexpCplDis_OFFSET               18
#define D0F0xE4_CORE_0010_RxRcbUnexpCplDis_WIDTH                1
#define D0F0xE4_CORE_0010_RxRcbUnexpCplDis_MASK                 0x40000
#define D0F0xE4_CORE_0010_RxRcbCplTimeoutTestMode_OFFSET        19
#define D0F0xE4_CORE_0010_RxRcbCplTimeoutTestMode_WIDTH         1
#define D0F0xE4_CORE_0010_RxRcbCplTimeoutTestMode_MASK          0x80000
#define D0F0xE4_CORE_0010_RxRcbChannelOrdering_OFFSET           20
#define D0F0xE4_CORE_0010_RxRcbChannelOrdering_WIDTH            1
#define D0F0xE4_CORE_0010_RxRcbChannelOrdering_MASK             0x100000
#define D0F0xE4_CORE_0010_RxRcbWrongAttrDis_OFFSET              21
#define D0F0xE4_CORE_0010_RxRcbWrongAttrDis_WIDTH               1
#define D0F0xE4_CORE_0010_RxRcbWrongAttrDis_MASK                0x200000
#define D0F0xE4_CORE_0010_RxRcbWrongFuncnumDis_OFFSET           22
#define D0F0xE4_CORE_0010_RxRcbWrongFuncnumDis_WIDTH            1
#define D0F0xE4_CORE_0010_RxRcbWrongFuncnumDis_MASK             0x400000
#define D0F0xE4_CORE_0010_RxAtsTranCplSplitDis_OFFSET           23
#define D0F0xE4_CORE_0010_RxAtsTranCplSplitDis_WIDTH            1
#define D0F0xE4_CORE_0010_RxAtsTranCplSplitDis_MASK             0x800000
#define D0F0xE4_CORE_0010_TxCplDebug_OFFSET                     24
#define D0F0xE4_CORE_0010_TxCplDebug_WIDTH                      6
#define D0F0xE4_CORE_0010_TxCplDebug_MASK                       0x3f000000
#define D0F0xE4_CORE_0010_RxIgnoreLtrMsgUr_OFFSET               30
#define D0F0xE4_CORE_0010_RxIgnoreLtrMsgUr_WIDTH                1
#define D0F0xE4_CORE_0010_RxIgnoreLtrMsgUr_MASK                 0x40000000
#define D0F0xE4_CORE_0010_RxCplPostedReqOrdEn_OFFSET            31
#define D0F0xE4_CORE_0010_RxCplPostedReqOrdEn_WIDTH             1
#define D0F0xE4_CORE_0010_RxCplPostedReqOrdEn_MASK              0x80000000

/// D0F0xE4_CORE_0010
typedef union {
  struct {                                                              ///<
    UINT32                                             HwInitWrLock:1 ; ///<
    UINT32                                          LcHotPlugDelSel:3 ; ///<
    UINT32                                             Reserved_6_4:3 ; ///<
    UINT32                                           UrErrReportDis:1 ; ///<
    UINT32                                     PcieMalformAtomicOps:1 ; ///<
    UINT32                                            UmiNpMemWrite:1 ; ///<
    UINT32                                      RxUmiAdjPayloadSize:3 ; ///<
    UINT32                                           Reserved_14_13:2 ; ///<
    UINT32                                            RxRcbAtsUcDis:1 ; ///<
    UINT32                                           RxRcbReorderEn:1 ; ///<
    UINT32                                      RxRcbInvalidSizeDis:1 ; ///<
    UINT32                                         RxRcbUnexpCplDis:1 ; ///<
    UINT32                                  RxRcbCplTimeoutTestMode:1 ; ///<
    UINT32                                     RxRcbChannelOrdering:1 ; ///<
    UINT32                                        RxRcbWrongAttrDis:1 ; ///<
    UINT32                                     RxRcbWrongFuncnumDis:1 ; ///<
    UINT32                                     RxAtsTranCplSplitDis:1 ; ///<
    UINT32                                               TxCplDebug:6 ; ///<
    UINT32                                         RxIgnoreLtrMsgUr:1 ; ///<
    UINT32                                      RxCplPostedReqOrdEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0010_STRUCT;

// **** D0F0xE4_CORE_0011 Register Definition ****
// Address
#define D0F0xE4_CORE_0011_ADDRESS                               0x11

// Type
#define D0F0xE4_CORE_0011_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0011_DynClkLatency_OFFSET                  0
#define D0F0xE4_CORE_0011_DynClkLatency_WIDTH                   4
#define D0F0xE4_CORE_0011_DynClkLatency_MASK                    0xf
#define D0F0xE4_CORE_0011_Reserved_15_4_OFFSET                  4
#define D0F0xE4_CORE_0011_Reserved_15_4_WIDTH                   12
#define D0F0xE4_CORE_0011_Reserved_15_4_MASK                    0xfff0
#define D0F0xE4_CORE_0011_CiMaxPayloadSizeMode_OFFSET           16
#define D0F0xE4_CORE_0011_CiMaxPayloadSizeMode_WIDTH            1
#define D0F0xE4_CORE_0011_CiMaxPayloadSizeMode_MASK             0x10000
#define D0F0xE4_CORE_0011_CiPrivMaxPayloadSize_OFFSET           17
#define D0F0xE4_CORE_0011_CiPrivMaxPayloadSize_WIDTH            3
#define D0F0xE4_CORE_0011_CiPrivMaxPayloadSize_MASK             0xe0000
#define D0F0xE4_CORE_0011_CiMaxReadRequestSizeMode_OFFSET       20
#define D0F0xE4_CORE_0011_CiMaxReadRequestSizeMode_WIDTH        1
#define D0F0xE4_CORE_0011_CiMaxReadRequestSizeMode_MASK         0x100000
#define D0F0xE4_CORE_0011_CiPrivMaxReadRequestSize_OFFSET       21
#define D0F0xE4_CORE_0011_CiPrivMaxReadRequestSize_WIDTH        3
#define D0F0xE4_CORE_0011_CiPrivMaxReadRequestSize_MASK         0xe00000
#define D0F0xE4_CORE_0011_CiMaxReadSafeMode_OFFSET              24
#define D0F0xE4_CORE_0011_CiMaxReadSafeMode_WIDTH               1
#define D0F0xE4_CORE_0011_CiMaxReadSafeMode_MASK                0x1000000
#define D0F0xE4_CORE_0011_CiExtendedTagEnOverride_OFFSET        25
#define D0F0xE4_CORE_0011_CiExtendedTagEnOverride_WIDTH         2
#define D0F0xE4_CORE_0011_CiExtendedTagEnOverride_MASK          0x6000000
#define D0F0xE4_CORE_0011_Reserved_31_27_OFFSET                 27
#define D0F0xE4_CORE_0011_Reserved_31_27_WIDTH                  5
#define D0F0xE4_CORE_0011_Reserved_31_27_MASK                   0xf8000000

/// D0F0xE4_CORE_0011
typedef union {
  struct {                                                              ///<
    UINT32                                            DynClkLatency:4 ; ///<
    UINT32                                            Reserved_15_4:12; ///<
    UINT32                                     CiMaxPayloadSizeMode:1 ; ///<
    UINT32                                     CiPrivMaxPayloadSize:3 ; ///<
    UINT32                                 CiMaxReadRequestSizeMode:1 ; ///<
    UINT32                                 CiPrivMaxReadRequestSize:3 ; ///<
    UINT32                                        CiMaxReadSafeMode:1 ; ///<
    UINT32                                  CiExtendedTagEnOverride:2 ; ///<
    UINT32                                           Reserved_31_27:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0011_STRUCT;

// **** D0F0xE4_CORE_001C Register Definition ****
// Address
#define D0F0xE4_CORE_001C_ADDRESS                               0x1c

// Type
#define D0F0xE4_CORE_001C_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_001C_TxArbRoundRobinEn_OFFSET              0
#define D0F0xE4_CORE_001C_TxArbRoundRobinEn_WIDTH               1
#define D0F0xE4_CORE_001C_TxArbRoundRobinEn_MASK                0x1
#define D0F0xE4_CORE_001C_TxArbRoundRobinEn_VALUE               0x1
#define D0F0xE4_CORE_001C_TxArbSlvLimit_OFFSET                  1
#define D0F0xE4_CORE_001C_TxArbSlvLimit_WIDTH                   5
#define D0F0xE4_CORE_001C_TxArbSlvLimit_MASK                    0x3e
#define D0F0xE4_CORE_001C_TxArbSlvLimit_VALUE                   0x4
#define D0F0xE4_CORE_001C_TxArbMstLimit_OFFSET                  6
#define D0F0xE4_CORE_001C_TxArbMstLimit_WIDTH                   5
#define D0F0xE4_CORE_001C_TxArbMstLimit_MASK                    0x7c0
#define D0F0xE4_CORE_001C_TxArbMstLimit_VALUE                   0x4
#define D0F0xE4_CORE_001C_TxBlockTlpOnPmDis_OFFSET              11
#define D0F0xE4_CORE_001C_TxBlockTlpOnPmDis_WIDTH               1
#define D0F0xE4_CORE_001C_TxBlockTlpOnPmDis_MASK                0x800
#define D0F0xE4_CORE_001C_TX_ATOMIC_OPS_DISABLE_OFFSET          13
#define D0F0xE4_CORE_001C_TX_ATOMIC_OPS_DISABLE_WIDTH           1
#define D0F0xE4_CORE_001C_TX_ATOMIC_OPS_DISABLE_MASK            0x2000
#define D0F0xE4_CORE_001C_SlvMemLsEn_OFFSET                     16
#define D0F0xE4_CORE_001C_SlvMemLsEn_WIDTH                      1
#define D0F0xE4_CORE_001C_SlvMemLsEn_MASK                       0x10000
#define D0F0xE4_CORE_001C_SlvMemAggressiveLsEn_OFFSET           17
#define D0F0xE4_CORE_001C_SlvMemAggressiveLsEn_WIDTH            1
#define D0F0xE4_CORE_001C_SlvMemAggressiveLsEn_MASK             0x20000
#define D0F0xE4_CORE_001C_MstMemLsEn_OFFSET                     18
#define D0F0xE4_CORE_001C_MstMemLsEn_WIDTH                      1
#define D0F0xE4_CORE_001C_MstMemLsEn_MASK                       0x40000
#define D0F0xE4_CORE_001C_ReplayMemLsEn_OFFSET                  19
#define D0F0xE4_CORE_001C_ReplayMemLsEn_WIDTH                   1
#define D0F0xE4_CORE_001C_ReplayMemLsEn_MASK                    0x80000
#define D0F0xE4_CORE_001C_SlvMemSdEn_OFFSET                     20
#define D0F0xE4_CORE_001C_SlvMemSdEn_WIDTH                      1
#define D0F0xE4_CORE_001C_SlvMemSdEn_MASK                       0x100000
#define D0F0xE4_CORE_001C_SlvMemAggressiveSdEn_OFFSET           21
#define D0F0xE4_CORE_001C_SlvMemAggressiveSdEn_WIDTH            1
#define D0F0xE4_CORE_001C_SlvMemAggressiveSdEn_MASK             0x200000
#define D0F0xE4_CORE_001C_MstMemSdEn_OFFSET                     22
#define D0F0xE4_CORE_001C_MstMemSdEn_WIDTH                      1
#define D0F0xE4_CORE_001C_MstMemSdEn_MASK                       0x400000
#define D0F0xE4_CORE_001C_ReplayMemSdEn_OFFSET                  23
#define D0F0xE4_CORE_001C_ReplayMemSdEn_WIDTH                   1
#define D0F0xE4_CORE_001C_ReplayMemSdEn_MASK                    0x800000
#define D0F0xE4_CORE_001C_RxNpMemWriteEncoding_OFFSET           24
#define D0F0xE4_CORE_001C_RxNpMemWriteEncoding_WIDTH            5
#define D0F0xE4_CORE_001C_RxNpMemWriteEncoding_MASK             0x1f000000
#define D0F0xE4_CORE_001C_RxNpMemWriteEncoding_VALUE            0xe
#define D0F0xE4_CORE_001C_Reserved_31_29_OFFSET                 29
#define D0F0xE4_CORE_001C_Reserved_31_29_WIDTH                  3
#define D0F0xE4_CORE_001C_Reserved_31_29_MASK                   0xe0000000

/// D0F0xE4_CORE_001C
typedef union {
  struct {                                                              ///<
    UINT32                                        TxArbRoundRobinEn:1 ; ///<
    UINT32                                            TxArbSlvLimit:5 ; ///<
    UINT32                                            TxArbMstLimit:5 ; ///<
    UINT32                                        TxBlockTlpOnPmDis:1 ; ///<
    UINT32                                           Reserved_12_12:1 ; ///<
    UINT32                                    TX_ATOMIC_OPS_DISABLE:1 ; ///<
    UINT32                                           Reserved_15_14:2 ; ///<
    UINT32                                               SlvMemLsEn:1 ; ///<
    UINT32                                     SlvMemAggressiveLsEn:1 ; ///<
    UINT32                                               MstMemLsEn:1 ; ///<
    UINT32                                            ReplayMemLsEn:1 ; ///<
    UINT32                                               SlvMemSdEn:1 ; ///<
    UINT32                                     SlvMemAggressiveSdEn:1 ; ///<
    UINT32                                               MstMemSdEn:1 ; ///<
    UINT32                                            ReplayMemSdEn:1 ; ///<
    UINT32                                     RxNpMemWriteEncoding:5 ; ///<
    UINT32                                           Reserved_31_29:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_001C_STRUCT;

// **** D0F0xE4_CORE_0020 Register Definition ****
// Address
#define D0F0xE4_CORE_0020_ADDRESS                               0x20

// Type
#define D0F0xE4_CORE_0020_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0020_Reserved_1_0_OFFSET                   0
#define D0F0xE4_CORE_0020_Reserved_1_0_WIDTH                    2
#define D0F0xE4_CORE_0020_Reserved_1_0_MASK                     0x3
#define D0F0xE4_CORE_0020_CiSlvSplitMode_OFFSET                 2
#define D0F0xE4_CORE_0020_CiSlvSplitMode_WIDTH                  1
#define D0F0xE4_CORE_0020_CiSlvSplitMode_MASK                   0x4
#define D0F0xE4_CORE_0020_CiSlvGenUsrDis_OFFSET                 3
#define D0F0xE4_CORE_0020_CiSlvGenUsrDis_WIDTH                  1
#define D0F0xE4_CORE_0020_CiSlvGenUsrDis_MASK                   0x8
#define D0F0xE4_CORE_0020_CiMstCmplDummyData_OFFSET             4
#define D0F0xE4_CORE_0020_CiMstCmplDummyData_WIDTH              1
#define D0F0xE4_CORE_0020_CiMstCmplDummyData_MASK               0x10
#define D0F0xE4_CORE_0020_Reserved_5_5_OFFSET                   5
#define D0F0xE4_CORE_0020_Reserved_5_5_WIDTH                    1
#define D0F0xE4_CORE_0020_Reserved_5_5_MASK                     0x20
#define D0F0xE4_CORE_0020_CiSlvRcRdReqSize_OFFSET               6
#define D0F0xE4_CORE_0020_CiSlvRcRdReqSize_WIDTH                2
#define D0F0xE4_CORE_0020_CiSlvRcRdReqSize_MASK                 0xc0
#define D0F0xE4_CORE_0020_CiSlvOrderingDis_OFFSET               8
#define D0F0xE4_CORE_0020_CiSlvOrderingDis_WIDTH                1
#define D0F0xE4_CORE_0020_CiSlvOrderingDis_MASK                 0x100
#define D0F0xE4_CORE_0020_CiRcOrderingDis_OFFSET                9
#define D0F0xE4_CORE_0020_CiRcOrderingDis_WIDTH                 1
#define D0F0xE4_CORE_0020_CiRcOrderingDis_MASK                  0x200
#define D0F0xE4_CORE_0020_CiSlvCplAllocDis_OFFSET               10
#define D0F0xE4_CORE_0020_CiSlvCplAllocDis_WIDTH                1
#define D0F0xE4_CORE_0020_CiSlvCplAllocDis_MASK                 0x400
#define D0F0xE4_CORE_0020_CiSlvCplAllocMode_OFFSET              11
#define D0F0xE4_CORE_0020_CiSlvCplAllocMode_WIDTH               1
#define D0F0xE4_CORE_0020_CiSlvCplAllocMode_MASK                0x800
#define D0F0xE4_CORE_0020_CiSlvCplAllocSor_OFFSET               12
#define D0F0xE4_CORE_0020_CiSlvCplAllocSor_WIDTH                1
#define D0F0xE4_CORE_0020_CiSlvCplAllocSor_MASK                 0x1000
#define D0F0xE4_CORE_0020_CiMstIgnorePageAlignedRequest_OFFSET  13
#define D0F0xE4_CORE_0020_CiMstIgnorePageAlignedRequest_WIDTH   1
#define D0F0xE4_CORE_0020_CiMstIgnorePageAlignedRequest_MASK    0x2000
#define D0F0xE4_CORE_0020_Reserved_31_14_OFFSET                 14
#define D0F0xE4_CORE_0020_Reserved_31_14_WIDTH                  18
#define D0F0xE4_CORE_0020_Reserved_31_14_MASK                   0xffffc000

/// D0F0xE4_CORE_0020
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_1_0:2 ; ///<
    UINT32                                           CiSlvSplitMode:1 ; ///<
    UINT32                                           CiSlvGenUsrDis:1 ; ///<
    UINT32                                       CiMstCmplDummyData:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                         CiSlvRcRdReqSize:2 ; ///<
    UINT32                                         CiSlvOrderingDis:1 ; ///<
    UINT32                                          CiRcOrderingDis:1 ; ///<
    UINT32                                         CiSlvCplAllocDis:1 ; ///<
    UINT32                                        CiSlvCplAllocMode:1 ; ///<
    UINT32                                         CiSlvCplAllocSor:1 ; ///<
    UINT32                            CiMstIgnorePageAlignedRequest:1 ; ///<
    UINT32                                           Reserved_31_14:18; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0020_STRUCT;

// **** D0F0xE4_CORE_003D Register Definition ****
// Address
#define D0F0xE4_CORE_003D_ADDRESS                              0x3d

// Type
#define D0F0xE4_CORE_003D_TYPE                                 TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_003D_LC_L1_POWER_GATING_EN_OFFSET         0
#define D0F0xE4_CORE_003D_LC_L1_POWER_GATING_EN_WIDTH          1
#define D0F0xE4_CORE_003D_LC_L1_POWER_GATING_EN_MASK           0x1
#define D0F0xE4_CORE_003D_Reserved_31_1_OFFSET                 1
#define D0F0xE4_CORE_003D_Reserved_31_1_WIDTH                  31
#define D0F0xE4_CORE_003D_Reserved_31_1_MASK                   0xfffffffe

/// D0F0xE4_CORE_003D
typedef union {
  struct {                                                              ///<
    UINT32                                    LC_L1_POWER_GATING_EN:1 ; ///<
    UINT32                                            Reserved_31_1:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_003D_STRUCT;

// **** D0F0xE4_CORE_0040 Register Definition ****
// Address
#define D0F0xE4_CORE_0040_ADDRESS                               0x40

// Type
#define D0F0xE4_CORE_0040_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0040_Reserved_0_0_OFFSET                   0
#define D0F0xE4_CORE_0040_Reserved_0_0_WIDTH                    1
#define D0F0xE4_CORE_0040_Reserved_0_0_MASK                     0x1
#define D0F0xE4_CORE_0040_PSymalignMode_OFFSET                  1
#define D0F0xE4_CORE_0040_PSymalignMode_WIDTH                   1
#define D0F0xE4_CORE_0040_PSymalignMode_MASK                    0x2
#define D0F0xE4_CORE_0040_PSymalignHwDebug_OFFSET               2
#define D0F0xE4_CORE_0040_PSymalignHwDebug_WIDTH                1
#define D0F0xE4_CORE_0040_PSymalignHwDebug_MASK                 0x4
#define D0F0xE4_CORE_0040_PElastDeskewHwDebug_OFFSET            3
#define D0F0xE4_CORE_0040_PElastDeskewHwDebug_WIDTH             1
#define D0F0xE4_CORE_0040_PElastDeskewHwDebug_MASK              0x8
#define D0F0xE4_CORE_0040_PIgnoreCrcErr_OFFSET                  4
#define D0F0xE4_CORE_0040_PIgnoreCrcErr_WIDTH                   1
#define D0F0xE4_CORE_0040_PIgnoreCrcErr_MASK                    0x10
#define D0F0xE4_CORE_0040_PIgnoreLenErr_OFFSET                  5
#define D0F0xE4_CORE_0040_PIgnoreLenErr_WIDTH                   1
#define D0F0xE4_CORE_0040_PIgnoreLenErr_MASK                    0x20
#define D0F0xE4_CORE_0040_PIgnoreEdbErr_OFFSET                  6
#define D0F0xE4_CORE_0040_PIgnoreEdbErr_WIDTH                   1
#define D0F0xE4_CORE_0040_PIgnoreEdbErr_MASK                    0x40
#define D0F0xE4_CORE_0040_PIgnoreIdlErr_OFFSET                  7
#define D0F0xE4_CORE_0040_PIgnoreIdlErr_WIDTH                   1
#define D0F0xE4_CORE_0040_PIgnoreIdlErr_MASK                    0x80
#define D0F0xE4_CORE_0040_PIgnoreTokErr_OFFSET                  8
#define D0F0xE4_CORE_0040_PIgnoreTokErr_WIDTH                   1
#define D0F0xE4_CORE_0040_PIgnoreTokErr_MASK                    0x100
#define D0F0xE4_CORE_0040_Reserved_11_9_OFFSET                  9
#define D0F0xE4_CORE_0040_Reserved_11_9_WIDTH                   3
#define D0F0xE4_CORE_0040_Reserved_11_9_MASK                    0xe00
#define D0F0xE4_CORE_0040_PBlkLockMode_OFFSET                   12
#define D0F0xE4_CORE_0040_PBlkLockMode_WIDTH                    1
#define D0F0xE4_CORE_0040_PBlkLockMode_MASK                     0x1000
#define D0F0xE4_CORE_0040_PAlwaysUseFastTxclk_OFFSET            13
#define D0F0xE4_CORE_0040_PAlwaysUseFastTxclk_WIDTH             1
#define D0F0xE4_CORE_0040_PAlwaysUseFastTxclk_MASK              0x2000
#define D0F0xE4_CORE_0040_PElecIdleMode_OFFSET                  14
#define D0F0xE4_CORE_0040_PElecIdleMode_WIDTH                   2
#define D0F0xE4_CORE_0040_PElecIdleMode_MASK                    0xc000
#define D0F0xE4_CORE_0040_PElecIdleMode_VALUE                   0x1
#define D0F0xE4_CORE_0040_DlpIgnoreInL1En_OFFSET                16
#define D0F0xE4_CORE_0040_DlpIgnoreInL1En_WIDTH                 1
#define D0F0xE4_CORE_0040_DlpIgnoreInL1En_MASK                  0x10000
#define D0F0xE4_CORE_0040_Reserved_31_17_OFFSET                 17
#define D0F0xE4_CORE_0040_Reserved_31_17_WIDTH                  15
#define D0F0xE4_CORE_0040_Reserved_31_17_MASK                   0xfffe0000

/// D0F0xE4_CORE_0040
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                            PSymalignMode:1 ; ///<
    UINT32                                         PSymalignHwDebug:1 ; ///<
    UINT32                                      PElastDeskewHwDebug:1 ; ///<
    UINT32                                            PIgnoreCrcErr:1 ; ///<
    UINT32                                            PIgnoreLenErr:1 ; ///<
    UINT32                                            PIgnoreEdbErr:1 ; ///<
    UINT32                                            PIgnoreIdlErr:1 ; ///<
    UINT32                                            PIgnoreTokErr:1 ; ///<
    UINT32                                            Reserved_11_9:3 ; ///<
    UINT32                                             PBlkLockMode:1 ; ///<
    UINT32                                      PAlwaysUseFastTxclk:1 ; ///<
    UINT32                                            PElecIdleMode:2 ; ///<
    UINT32                                          DlpIgnoreInL1En:1 ; ///<
    UINT32                                           Reserved_31_17:15; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0040_STRUCT;

// **** D0F0xE4_CORE_00B0 Register Definition ****
// Address
#define D0F0xE4_CORE_00B0_ADDRESS                               0xb0

// Type
#define D0F0xE4_CORE_00B0_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_00B0_StrapF0En_OFFSET                      0
#define D0F0xE4_CORE_00B0_StrapF0En_WIDTH                       1
#define D0F0xE4_CORE_00B0_StrapF0En_MASK                        0x1
#define D0F0xE4_CORE_00B0_StrapF0LegacyDeviceTypeEn_OFFSET      1
#define D0F0xE4_CORE_00B0_StrapF0LegacyDeviceTypeEn_WIDTH       1
#define D0F0xE4_CORE_00B0_StrapF0LegacyDeviceTypeEn_MASK        0x2
#define D0F0xE4_CORE_00B0_StrapF0MsiEn_OFFSET                   2
#define D0F0xE4_CORE_00B0_StrapF0MsiEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0MsiEn_MASK                     0x4
#define D0F0xE4_CORE_00B0_StrapF0MsiEn_VALUE                    0x1
#define D0F0xE4_CORE_00B0_StrapF0VcEn_OFFSET                    3
#define D0F0xE4_CORE_00B0_StrapF0VcEn_WIDTH                     1
#define D0F0xE4_CORE_00B0_StrapF0VcEn_MASK                      0x8
#define D0F0xE4_CORE_00B0_StrapF0DsnEn_OFFSET                   4
#define D0F0xE4_CORE_00B0_StrapF0DsnEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0DsnEn_MASK                     0x10
#define D0F0xE4_CORE_00B0_StrapF0AerEn_OFFSET                   5
#define D0F0xE4_CORE_00B0_StrapF0AerEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0AerEn_MASK                     0x20
#define D0F0xE4_CORE_00B0_StrapF0AerEn_VALUE                    0x1
#define D0F0xE4_CORE_00B0_StrapF0AcsEn_OFFSET                   6
#define D0F0xE4_CORE_00B0_StrapF0AcsEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0AcsEn_MASK                     0x40
#define D0F0xE4_CORE_00B0_StrapF0BarEn_OFFSET                   7
#define D0F0xE4_CORE_00B0_StrapF0BarEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0BarEn_MASK                     0x80
#define D0F0xE4_CORE_00B0_StrapF0PwrEn_OFFSET                   8
#define D0F0xE4_CORE_00B0_StrapF0PwrEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0PwrEn_MASK                     0x100
#define D0F0xE4_CORE_00B0_StrapF0DpaEn_OFFSET                   9
#define D0F0xE4_CORE_00B0_StrapF0DpaEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0DpaEn_MASK                     0x200
#define D0F0xE4_CORE_00B0_StrapF0AtsEn_OFFSET                   10
#define D0F0xE4_CORE_00B0_StrapF0AtsEn_WIDTH                    1
#define D0F0xE4_CORE_00B0_StrapF0AtsEn_MASK                     0x400
#define D0F0xE4_CORE_00B0_StrapF0PageReqEn_OFFSET               11
#define D0F0xE4_CORE_00B0_StrapF0PageReqEn_WIDTH                1
#define D0F0xE4_CORE_00B0_StrapF0PageReqEn_MASK                 0x800
#define D0F0xE4_CORE_00B0_StrapF0PasidEn_OFFSET                 12
#define D0F0xE4_CORE_00B0_StrapF0PasidEn_WIDTH                  1
#define D0F0xE4_CORE_00B0_StrapF0PasidEn_MASK                   0x1000
#define D0F0xE4_CORE_00B0_StrapF0EcrcCheckEn_OFFSET             13
#define D0F0xE4_CORE_00B0_StrapF0EcrcCheckEn_WIDTH              1
#define D0F0xE4_CORE_00B0_StrapF0EcrcCheckEn_MASK               0x2000
#define D0F0xE4_CORE_00B0_StrapF0EcrcGenEn_OFFSET               14
#define D0F0xE4_CORE_00B0_StrapF0EcrcGenEn_WIDTH                1
#define D0F0xE4_CORE_00B0_StrapF0EcrcGenEn_MASK                 0x4000
#define D0F0xE4_CORE_00B0_StrapF0CplAbortErrEn_OFFSET           15
#define D0F0xE4_CORE_00B0_StrapF0CplAbortErrEn_WIDTH            1
#define D0F0xE4_CORE_00B0_StrapF0CplAbortErrEn_MASK             0x8000
#define D0F0xE4_CORE_00B0_StrapF0PoisonedAdvisoryNonfatal_OFFSET 16
#define D0F0xE4_CORE_00B0_StrapF0PoisonedAdvisoryNonfatal_WIDTH 1
#define D0F0xE4_CORE_00B0_StrapF0PoisonedAdvisoryNonfatal_MASK  0x10000
#define D0F0xE4_CORE_00B0_StrapF0McEn_OFFSET                    17
#define D0F0xE4_CORE_00B0_StrapF0McEn_WIDTH                     1
#define D0F0xE4_CORE_00B0_StrapF0McEn_MASK                      0x20000
#define D0F0xE4_CORE_00B0_Reserved_31_18_OFFSET                 18
#define D0F0xE4_CORE_00B0_Reserved_31_18_WIDTH                  14
#define D0F0xE4_CORE_00B0_Reserved_31_18_MASK                   0xfffc0000

/// D0F0xE4_CORE_00B0
typedef union {
  struct {                                                              ///<
    UINT32                                                StrapF0En:1 ; ///<
    UINT32                                StrapF0LegacyDeviceTypeEn:1 ; ///<
    UINT32                                             StrapF0MsiEn:1 ; ///<
    UINT32                                              StrapF0VcEn:1 ; ///<
    UINT32                                             StrapF0DsnEn:1 ; ///<
    UINT32                                             StrapF0AerEn:1 ; ///<
    UINT32                                             StrapF0AcsEn:1 ; ///<
    UINT32                                             StrapF0BarEn:1 ; ///<
    UINT32                                             StrapF0PwrEn:1 ; ///<
    UINT32                                             StrapF0DpaEn:1 ; ///<
    UINT32                                             StrapF0AtsEn:1 ; ///<
    UINT32                                         StrapF0PageReqEn:1 ; ///<
    UINT32                                           StrapF0PasidEn:1 ; ///<
    UINT32                                       StrapF0EcrcCheckEn:1 ; ///<
    UINT32                                         StrapF0EcrcGenEn:1 ; ///<
    UINT32                                     StrapF0CplAbortErrEn:1 ; ///<
    UINT32                          StrapF0PoisonedAdvisoryNonfatal:1 ; ///<
    UINT32                                              StrapF0McEn:1 ; ///<
    UINT32                                           Reserved_31_18:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_00B0_STRUCT;

// **** D0F0xE4_CORE_00B1 Register Definition ****
// Address
#define D0F0xE4_CORE_00B1_ADDRESS                               0xb1

// Type
#define D0F0xE4_CORE_00B1_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_00B1_StrapF1En_OFFSET                      0
#define D0F0xE4_CORE_00B1_StrapF1En_WIDTH                       1
#define D0F0xE4_CORE_00B1_StrapF1En_MASK                        0x1
#define D0F0xE4_CORE_00B1_StrapF1LegacyDeviceTypeEn_OFFSET      1
#define D0F0xE4_CORE_00B1_StrapF1LegacyDeviceTypeEn_WIDTH       1
#define D0F0xE4_CORE_00B1_StrapF1LegacyDeviceTypeEn_MASK        0x2
#define D0F0xE4_CORE_00B1_StrapF1MsiEn_OFFSET                   2
#define D0F0xE4_CORE_00B1_StrapF1MsiEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1MsiEn_MASK                     0x4
#define D0F0xE4_CORE_00B1_StrapF1MsiEn_VALUE                    0x1
#define D0F0xE4_CORE_00B1_StrapF1VcEn_OFFSET                    3
#define D0F0xE4_CORE_00B1_StrapF1VcEn_WIDTH                     1
#define D0F0xE4_CORE_00B1_StrapF1VcEn_MASK                      0x8
#define D0F0xE4_CORE_00B1_StrapF1DsnEn_OFFSET                   4
#define D0F0xE4_CORE_00B1_StrapF1DsnEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1DsnEn_MASK                     0x10
#define D0F0xE4_CORE_00B1_StrapF1AerEn_OFFSET                   5
#define D0F0xE4_CORE_00B1_StrapF1AerEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1AerEn_MASK                     0x20
#define D0F0xE4_CORE_00B1_StrapF1AerEn_VALUE                    0x1
#define D0F0xE4_CORE_00B1_StrapF1AcsEn_OFFSET                   6
#define D0F0xE4_CORE_00B1_StrapF1AcsEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1AcsEn_MASK                     0x40
#define D0F0xE4_CORE_00B1_StrapF1BarEn_OFFSET                   7
#define D0F0xE4_CORE_00B1_StrapF1BarEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1BarEn_MASK                     0x80
#define D0F0xE4_CORE_00B1_StrapF1PwrEn_OFFSET                   8
#define D0F0xE4_CORE_00B1_StrapF1PwrEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1PwrEn_MASK                     0x100
#define D0F0xE4_CORE_00B1_StrapF1DpaEn_OFFSET                   9
#define D0F0xE4_CORE_00B1_StrapF1DpaEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1DpaEn_MASK                     0x200
#define D0F0xE4_CORE_00B1_StrapF1AtsEn_OFFSET                   10
#define D0F0xE4_CORE_00B1_StrapF1AtsEn_WIDTH                    1
#define D0F0xE4_CORE_00B1_StrapF1AtsEn_MASK                     0x400
#define D0F0xE4_CORE_00B1_StrapF1PageReqEn_OFFSET               11
#define D0F0xE4_CORE_00B1_StrapF1PageReqEn_WIDTH                1
#define D0F0xE4_CORE_00B1_StrapF1PageReqEn_MASK                 0x800
#define D0F0xE4_CORE_00B1_StrapF1PasidEn_OFFSET                 12
#define D0F0xE4_CORE_00B1_StrapF1PasidEn_WIDTH                  1
#define D0F0xE4_CORE_00B1_StrapF1PasidEn_MASK                   0x1000
#define D0F0xE4_CORE_00B1_StrapF1EcrcCheckEn_OFFSET             13
#define D0F0xE4_CORE_00B1_StrapF1EcrcCheckEn_WIDTH              1
#define D0F0xE4_CORE_00B1_StrapF1EcrcCheckEn_MASK               0x2000
#define D0F0xE4_CORE_00B1_StrapF1EcrcGenEn_OFFSET               14
#define D0F0xE4_CORE_00B1_StrapF1EcrcGenEn_WIDTH                1
#define D0F0xE4_CORE_00B1_StrapF1EcrcGenEn_MASK                 0x4000
#define D0F0xE4_CORE_00B1_StrapF1CplAbortErrEn_OFFSET           15
#define D0F0xE4_CORE_00B1_StrapF1CplAbortErrEn_WIDTH            1
#define D0F0xE4_CORE_00B1_StrapF1CplAbortErrEn_MASK             0x8000
#define D0F0xE4_CORE_00B1_StrapF1PoisonedAdvisoryNonfatal_OFFSET 16
#define D0F0xE4_CORE_00B1_StrapF1PoisonedAdvisoryNonfatal_WIDTH 1
#define D0F0xE4_CORE_00B1_StrapF1PoisonedAdvisoryNonfatal_MASK  0x10000
#define D0F0xE4_CORE_00B1_Reserved_31_17_OFFSET                 17
#define D0F0xE4_CORE_00B1_Reserved_31_17_WIDTH                  15
#define D0F0xE4_CORE_00B1_Reserved_31_17_MASK                   0xfffe0000

/// D0F0xE4_CORE_00B1
typedef union {
  struct {                                                              ///<
    UINT32                                                StrapF1En:1 ; ///<
    UINT32                                StrapF1LegacyDeviceTypeEn:1 ; ///<
    UINT32                                             StrapF1MsiEn:1 ; ///<
    UINT32                                              StrapF1VcEn:1 ; ///<
    UINT32                                             StrapF1DsnEn:1 ; ///<
    UINT32                                             StrapF1AerEn:1 ; ///<
    UINT32                                             StrapF1AcsEn:1 ; ///<
    UINT32                                             StrapF1BarEn:1 ; ///<
    UINT32                                             StrapF1PwrEn:1 ; ///<
    UINT32                                             StrapF1DpaEn:1 ; ///<
    UINT32                                             StrapF1AtsEn:1 ; ///<
    UINT32                                         StrapF1PageReqEn:1 ; ///<
    UINT32                                           StrapF1PasidEn:1 ; ///<
    UINT32                                       StrapF1EcrcCheckEn:1 ; ///<
    UINT32                                         StrapF1EcrcGenEn:1 ; ///<
    UINT32                                     StrapF1CplAbortErrEn:1 ; ///<
    UINT32                          StrapF1PoisonedAdvisoryNonfatal:1 ; ///<
    UINT32                                           Reserved_31_17:15; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_00B1_STRUCT;

// **** D0F0xE4_CORE_00B2 Register Definition ****
// Address
#define D0F0xE4_CORE_00B2_ADDRESS                               0xb2

// Type
#define D0F0xE4_CORE_00B2_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_00B2_StrapF2En_OFFSET                      0
#define D0F0xE4_CORE_00B2_StrapF2En_WIDTH                       1
#define D0F0xE4_CORE_00B2_StrapF2En_MASK                        0x1
#define D0F0xE4_CORE_00B2_StrapF2LegacyDeviceTypeEn_OFFSET      1
#define D0F0xE4_CORE_00B2_StrapF2LegacyDeviceTypeEn_WIDTH       1
#define D0F0xE4_CORE_00B2_StrapF2LegacyDeviceTypeEn_MASK        0x2
#define D0F0xE4_CORE_00B2_StrapF2MsiEn_OFFSET                   2
#define D0F0xE4_CORE_00B2_StrapF2MsiEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2MsiEn_MASK                     0x4
#define D0F0xE4_CORE_00B2_StrapF2MsiEn_VALUE                    0x1
#define D0F0xE4_CORE_00B2_StrapF2VcEn_OFFSET                    3
#define D0F0xE4_CORE_00B2_StrapF2VcEn_WIDTH                     1
#define D0F0xE4_CORE_00B2_StrapF2VcEn_MASK                      0x8
#define D0F0xE4_CORE_00B2_StrapF2DsnEn_OFFSET                   4
#define D0F0xE4_CORE_00B2_StrapF2DsnEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2DsnEn_MASK                     0x10
#define D0F0xE4_CORE_00B2_StrapF2AerEn_OFFSET                   5
#define D0F0xE4_CORE_00B2_StrapF2AerEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2AerEn_MASK                     0x20
#define D0F0xE4_CORE_00B2_StrapF2AerEn_VALUE                    0x1
#define D0F0xE4_CORE_00B2_StrapF2AcsEn_OFFSET                   6
#define D0F0xE4_CORE_00B2_StrapF2AcsEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2AcsEn_MASK                     0x40
#define D0F0xE4_CORE_00B2_StrapF2BarEn_OFFSET                   7
#define D0F0xE4_CORE_00B2_StrapF2BarEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2BarEn_MASK                     0x80
#define D0F0xE4_CORE_00B2_StrapF2PwrEn_OFFSET                   8
#define D0F0xE4_CORE_00B2_StrapF2PwrEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2PwrEn_MASK                     0x100
#define D0F0xE4_CORE_00B2_StrapF2DpaEn_OFFSET                   9
#define D0F0xE4_CORE_00B2_StrapF2DpaEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2DpaEn_MASK                     0x200
#define D0F0xE4_CORE_00B2_StrapF2AtsEn_OFFSET                   10
#define D0F0xE4_CORE_00B2_StrapF2AtsEn_WIDTH                    1
#define D0F0xE4_CORE_00B2_StrapF2AtsEn_MASK                     0x400
#define D0F0xE4_CORE_00B2_StrapF2PageReqEn_OFFSET               11
#define D0F0xE4_CORE_00B2_StrapF2PageReqEn_WIDTH                1
#define D0F0xE4_CORE_00B2_StrapF2PageReqEn_MASK                 0x800
#define D0F0xE4_CORE_00B2_StrapF2PasidEn_OFFSET                 12
#define D0F0xE4_CORE_00B2_StrapF2PasidEn_WIDTH                  1
#define D0F0xE4_CORE_00B2_StrapF2PasidEn_MASK                   0x1000
#define D0F0xE4_CORE_00B2_StrapF2EcrcCheckEn_OFFSET             13
#define D0F0xE4_CORE_00B2_StrapF2EcrcCheckEn_WIDTH              1
#define D0F0xE4_CORE_00B2_StrapF2EcrcCheckEn_MASK               0x2000
#define D0F0xE4_CORE_00B2_StrapF2EcrcGenEn_OFFSET               14
#define D0F0xE4_CORE_00B2_StrapF2EcrcGenEn_WIDTH                1
#define D0F0xE4_CORE_00B2_StrapF2EcrcGenEn_MASK                 0x4000
#define D0F0xE4_CORE_00B2_StrapF2CplAbortErrEn_OFFSET           15
#define D0F0xE4_CORE_00B2_StrapF2CplAbortErrEn_WIDTH            1
#define D0F0xE4_CORE_00B2_StrapF2CplAbortErrEn_MASK             0x8000
#define D0F0xE4_CORE_00B2_StrapF2PoisonedAdvisoryNonfatal_OFFSET 16
#define D0F0xE4_CORE_00B2_StrapF2PoisonedAdvisoryNonfatal_WIDTH 1
#define D0F0xE4_CORE_00B2_StrapF2PoisonedAdvisoryNonfatal_MASK  0x10000
#define D0F0xE4_CORE_00B2_Reserved_31_17_OFFSET                 17
#define D0F0xE4_CORE_00B2_Reserved_31_17_WIDTH                  15
#define D0F0xE4_CORE_00B2_Reserved_31_17_MASK                   0xfffe0000

/// D0F0xE4_CORE_00B2
typedef union {
  struct {                                                              ///<
    UINT32                                                StrapF2En:1 ; ///<
    UINT32                                StrapF2LegacyDeviceTypeEn:1 ; ///<
    UINT32                                             StrapF2MsiEn:1 ; ///<
    UINT32                                              StrapF2VcEn:1 ; ///<
    UINT32                                             StrapF2DsnEn:1 ; ///<
    UINT32                                             StrapF2AerEn:1 ; ///<
    UINT32                                             StrapF2AcsEn:1 ; ///<
    UINT32                                             StrapF2BarEn:1 ; ///<
    UINT32                                             StrapF2PwrEn:1 ; ///<
    UINT32                                             StrapF2DpaEn:1 ; ///<
    UINT32                                             StrapF2AtsEn:1 ; ///<
    UINT32                                         StrapF2PageReqEn:1 ; ///<
    UINT32                                           StrapF2PasidEn:1 ; ///<
    UINT32                                       StrapF2EcrcCheckEn:1 ; ///<
    UINT32                                         StrapF2EcrcGenEn:1 ; ///<
    UINT32                                     StrapF2CplAbortErrEn:1 ; ///<
    UINT32                          StrapF2PoisonedAdvisoryNonfatal:1 ; ///<
    UINT32                                           Reserved_31_17:15; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_00B2_STRUCT;

// **** D0F0xE4_CORE_00C0 Register Definition ****
// Address
#define D0F0xE4_CORE_00C0_ADDRESS                               0xc0

// Type
#define D0F0xE4_CORE_00C0_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_00C0_Reserved_3_0_OFFSET                   0
#define D0F0xE4_CORE_00C0_Reserved_3_0_WIDTH                    4
#define D0F0xE4_CORE_00C0_Reserved_3_0_MASK                     0xf
#define D0F0xE4_CORE_00C0_StrapTlAltBufEn_OFFSET                4
#define D0F0xE4_CORE_00C0_StrapTlAltBufEn_WIDTH                 1
#define D0F0xE4_CORE_00C0_StrapTlAltBufEn_MASK                  0x10
#define D0F0xE4_CORE_00C0_Reserved_5_5_OFFSET                   5
#define D0F0xE4_CORE_00C0_Reserved_5_5_WIDTH                    1
#define D0F0xE4_CORE_00C0_Reserved_5_5_MASK                     0x20
#define D0F0xE4_CORE_00C0_StrapBypassScrambler_OFFSET           6
#define D0F0xE4_CORE_00C0_StrapBypassScrambler_WIDTH            1
#define D0F0xE4_CORE_00C0_StrapBypassScrambler_MASK             0x40
#define D0F0xE4_CORE_00C0_Reserved_7_7_OFFSET                   7
#define D0F0xE4_CORE_00C0_Reserved_7_7_WIDTH                    1
#define D0F0xE4_CORE_00C0_Reserved_7_7_MASK                     0x80
#define D0F0xE4_CORE_00C0_StrapMaxPasidWidth_OFFSET             8
#define D0F0xE4_CORE_00C0_StrapMaxPasidWidth_WIDTH              5
#define D0F0xE4_CORE_00C0_StrapMaxPasidWidth_MASK               0x1f00
#define D0F0xE4_CORE_00C0_StrapPasidExePermissionSupported_OFFSET 13
#define D0F0xE4_CORE_00C0_StrapPasidExePermissionSupported_WIDTH 1
#define D0F0xE4_CORE_00C0_StrapPasidExePermissionSupported_MASK 0x2000
#define D0F0xE4_CORE_00C0_StrapPasidPrivModeSupport_OFFSET      14
#define D0F0xE4_CORE_00C0_StrapPasidPrivModeSupport_WIDTH       1
#define D0F0xE4_CORE_00C0_StrapPasidPrivModeSupport_MASK        0x4000
#define D0F0xE4_CORE_00C0_StrapPasidGlobalInvalidateSupported_OFFSET 15
#define D0F0xE4_CORE_00C0_StrapPasidGlobalInvalidateSupported_WIDTH 1
#define D0F0xE4_CORE_00C0_StrapPasidGlobalInvalidateSupported_MASK 0x8000
#define D0F0xE4_CORE_00C0_Reserved_23_16_OFFSET                 16
#define D0F0xE4_CORE_00C0_Reserved_23_16_WIDTH                  8
#define D0F0xE4_CORE_00C0_Reserved_23_16_MASK                   0xff0000
#define D0F0xE4_CORE_00C0_StrapClkPmEn_OFFSET                   24
#define D0F0xE4_CORE_00C0_StrapClkPmEn_WIDTH                    1
#define D0F0xE4_CORE_00C0_StrapClkPmEn_MASK                     0x1000000
#define D0F0xE4_CORE_00C0_StrapEcn1p1En_OFFSET                  25
#define D0F0xE4_CORE_00C0_StrapEcn1p1En_WIDTH                   1
#define D0F0xE4_CORE_00C0_StrapEcn1p1En_MASK                    0x2000000
#define D0F0xE4_CORE_00C0_StrapExtVcCount_OFFSET                26
#define D0F0xE4_CORE_00C0_StrapExtVcCount_WIDTH                 1
#define D0F0xE4_CORE_00C0_StrapExtVcCount_MASK                  0x4000000
#define D0F0xE4_CORE_00C0_Reserved_27_27_OFFSET                 27
#define D0F0xE4_CORE_00C0_Reserved_27_27_WIDTH                  1
#define D0F0xE4_CORE_00C0_Reserved_27_27_MASK                   0x8000000
#define D0F0xE4_CORE_00C0_StrapReverseAll_OFFSET                28
#define D0F0xE4_CORE_00C0_StrapReverseAll_WIDTH                 1
#define D0F0xE4_CORE_00C0_StrapReverseAll_MASK                  0x10000000
#define D0F0xE4_CORE_00C0_StrapMstAdr64En_OFFSET                29
#define D0F0xE4_CORE_00C0_StrapMstAdr64En_WIDTH                 1
#define D0F0xE4_CORE_00C0_StrapMstAdr64En_MASK                  0x20000000
#define D0F0xE4_CORE_00C0_StrapFlrEn_OFFSET                     30
#define D0F0xE4_CORE_00C0_StrapFlrEn_WIDTH                      1
#define D0F0xE4_CORE_00C0_StrapFlrEn_MASK                       0x40000000
#define D0F0xE4_CORE_00C0_StrapInternalErrEn_OFFSET             31
#define D0F0xE4_CORE_00C0_StrapInternalErrEn_WIDTH              1
#define D0F0xE4_CORE_00C0_StrapInternalErrEn_MASK               0x80000000

/// D0F0xE4_CORE_00C0
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_3_0:4 ; ///<
    UINT32                                          StrapTlAltBufEn:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                     StrapBypassScrambler:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                       StrapMaxPasidWidth:5 ; ///<
    UINT32                         StrapPasidExePermissionSupported:1 ; ///<
    UINT32                                StrapPasidPrivModeSupport:1 ; ///<
    UINT32                      StrapPasidGlobalInvalidateSupported:1 ; ///<
    UINT32                                           Reserved_23_16:8 ; ///<
    UINT32                                             StrapClkPmEn:1 ; ///<
    UINT32                                            StrapEcn1p1En:1 ; ///<
    UINT32                                          StrapExtVcCount:1 ; ///<
    UINT32                                           Reserved_27_27:1 ; ///<
    UINT32                                          StrapReverseAll:1 ; ///<
    UINT32                                          StrapMstAdr64En:1 ; ///<
    UINT32                                               StrapFlrEn:1 ; ///<
    UINT32                                       StrapInternalErrEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_00C0_STRUCT;

// **** D0F0xE4_CORE_00C1 Register Definition ****
// Address
#define D0F0xE4_CORE_00C1_ADDRESS                               0xc1

// Type
#define D0F0xE4_CORE_00C1_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_00C1_StrapLinkBwNotificationCapEn_OFFSET   0
#define D0F0xE4_CORE_00C1_StrapLinkBwNotificationCapEn_WIDTH    1
#define D0F0xE4_CORE_00C1_StrapLinkBwNotificationCapEn_MASK     0x1
#define D0F0xE4_CORE_00C1_StrapGen2Compliance_OFFSET            1
#define D0F0xE4_CORE_00C1_StrapGen2Compliance_WIDTH             1
#define D0F0xE4_CORE_00C1_StrapGen2Compliance_MASK              0x2
#define D0F0xE4_CORE_00C1_StrapMstcplTimeoutEn_OFFSET           2
#define D0F0xE4_CORE_00C1_StrapMstcplTimeoutEn_WIDTH            1
#define D0F0xE4_CORE_00C1_StrapMstcplTimeoutEn_MASK             0x4
#define D0F0xE4_CORE_00C1_StrapGen3Compliance_OFFSET            3
#define D0F0xE4_CORE_00C1_StrapGen3Compliance_WIDTH             1
#define D0F0xE4_CORE_00C1_StrapGen3Compliance_MASK              0x8
#define D0F0xE4_CORE_00C1_StrapTphSupported_OFFSET              4
#define D0F0xE4_CORE_00C1_StrapTphSupported_WIDTH               1
#define D0F0xE4_CORE_00C1_StrapTphSupported_MASK                0x10
#define D0F0xE4_CORE_00C1_Reserved_31_5_OFFSET                  5
#define D0F0xE4_CORE_00C1_Reserved_31_5_WIDTH                   27
#define D0F0xE4_CORE_00C1_Reserved_31_5_MASK                    0xffffffe0

/// D0F0xE4_CORE_00C1
typedef union {
  struct {                                                              ///<
    UINT32                             StrapLinkBwNotificationCapEn:1 ; ///<
    UINT32                                      StrapGen2Compliance:1 ; ///<
    UINT32                                     StrapMstcplTimeoutEn:1 ; ///<
    UINT32                                      StrapGen3Compliance:1 ; ///<
    UINT32                                        StrapTphSupported:1 ; ///<
    UINT32                                            Reserved_31_5:27; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_00C1_STRUCT;

// **** D0F0xE4_CORE_0100 Register Definition ****
// Address
#define D0F0xE4_CORE_0100_ADDRESS                               0x100

// Type
#define D0F0xE4_CORE_0100_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0100_RECONFIGURE_OFFSET                    0
#define D0F0xE4_CORE_0100_RECONFIGURE_WIDTH                     1
#define D0F0xE4_CORE_0100_RECONFIGURE_MASK                      0x1

/// D0F0xE4_CORE_0100
typedef union {
  struct {                                                              ///<
    UINT32                                              RECONFIGURE:1 ; ///<
    UINT32                                             Reserved1_31:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0100_STRUCT;

// **** D0F0xE4_CORE_0101 Register Definition ****
// Address
#define D0F0xE4_CORE_0101_ADDRESS                               0x101

// Type
#define D0F0xE4_CORE_0101_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0101_RECONFIGURE_EN_OFFSET                 0
#define D0F0xE4_CORE_0101_RECONFIGURE_EN_WIDTH                  1
#define D0F0xE4_CORE_0101_RECONFIGURE_EN_MASK                   0x1
#define D0F0xE4_CORE_0101_ATOMIC_RESET_EN_OFFSET                1
#define D0F0xE4_CORE_0101_ATOMIC_RESET_EN_WIDTH                 1
#define D0F0xE4_CORE_0101_ATOMIC_RESET_EN_MASK                  0x2
#define D0F0xE4_CORE_0101_RESET_PERIOD_OFFSET                   2
#define D0F0xE4_CORE_0101_RESET_PERIOD_WIDTH                    3
#define D0F0xE4_CORE_0101_RESET_PERIOD_MASK                     0x1c
#define D0F0xE4_CORE_0101_Reserved_OFFSET                       5
#define D0F0xE4_CORE_0101_Reserved_WIDTH                        3
#define D0F0xE4_CORE_0101_Reserved_MASK                         0xe0
#define D0F0xE4_CORE_0101_WAIT_LINKUP_OFFSET                    8
#define D0F0xE4_CORE_0101_WAIT_LINKUP_WIDTH                     1
#define D0F0xE4_CORE_0101_WAIT_LINKUP_MASK                      0x100
#define D0F0xE4_CORE_0101_FORCE_REGIDLE_OFFSET                  9
#define D0F0xE4_CORE_0101_FORCE_REGIDLE_WIDTH                   1
#define D0F0xE4_CORE_0101_FORCE_REGIDLE_MASK                    0x200
#define D0F0xE4_CORE_0101_BLOCK_ON_IDLE_OFFSET                  10
#define D0F0xE4_CORE_0101_BLOCK_ON_IDLE_WIDTH                   1
#define D0F0xE4_CORE_0101_BLOCK_ON_IDLE_MASK                    0x400
#define D0F0xE4_CORE_0101_Reserved11_11_OFFSET                  11
#define D0F0xE4_CORE_0101_Reserved11_11_WIDTH                   1
#define D0F0xE4_CORE_0101_Reserved11_11_MASK                    0x800
#define D0F0xE4_CORE_0101_CONFIG_XFER_MODE_OFFSET               12
#define D0F0xE4_CORE_0101_CONFIG_XFER_MODE_WIDTH                1
#define D0F0xE4_CORE_0101_CONFIG_XFER_MODE_MASK                 0x1000
#define D0F0xE4_CORE_0101_MUXSEL_XFER_MODE_OFFSET               13
#define D0F0xE4_CORE_0101_MUXSEL_XFER_MODE_WIDTH                1
#define D0F0xE4_CORE_0101_MUXSEL_XFER_MODE_MASK                 0x2000
#define D0F0xE4_CORE_0101_HLDTRAIN_XFER_MODE_OFFSET             14
#define D0F0xE4_CORE_0101_HLDTRAIN_XFER_MODE_WIDTH              1
#define D0F0xE4_CORE_0101_HLDTRAIN_XFER_MODE_MASK               0x4000
#define D0F0xE4_CORE_0101_Reserved15_15_OFFSET                  15
#define D0F0xE4_CORE_0101_Reserved15_15_WIDTH                   1
#define D0F0xE4_CORE_0101_Reserved15_15_MASK                    0x8000
#define D0F0xE4_CORE_0101_BYPASS_HOLD_OFFSET                    16
#define D0F0xE4_CORE_0101_BYPASS_HOLD_WIDTH                     1
#define D0F0xE4_CORE_0101_BYPASS_HOLD_MASK                      0x10000
#define D0F0xE4_CORE_0101_BYPASS_PIF_HOLD_OFFSET                17
#define D0F0xE4_CORE_0101_BYPASS_PIF_HOLD_WIDTH                 1
#define D0F0xE4_CORE_0101_BYPASS_PIF_HOLD_MASK                  0x20000
#define D0F0xE4_CORE_0101_Reserved18_31_OFFSET                  18
#define D0F0xE4_CORE_0101_Reserved18_31_WIDTH                   14
#define D0F0xE4_CORE_0101_Reserved18_31_MASK                    0xfffc0000

/// D0F0xE4_CORE_0101
typedef union {
  struct {                                                              ///<
    UINT32                                           RECONFIGURE_EN:1 ; ///<
    UINT32                                          ATOMIC_RESET_EN:1 ; ///<
    UINT32                                             RESET_PERIOD:3 ; ///<
    UINT32                                                 Reserved:3 ; ///<
    UINT32                                              WAIT_LINKUP:1 ; ///<
    UINT32                                            FORCE_REGIDLE:1 ; ///<
    UINT32                                            BLOCK_ON_IDLE:1 ; ///<
    UINT32                                            Reserved11_11:1 ; ///<
    UINT32                                         CONFIG_XFER_MODE:1 ; ///<
    UINT32                                         MUXSEL_XFER_MODE:1 ; ///<
    UINT32                                       HLDTRAIN_XFER_MODE:1 ; ///<
    UINT32                                            Reserved15_15:1 ; ///<
    UINT32                                              BYPASS_HOLD:1 ; ///<
    UINT32                                          BYPASS_PIF_HOLD:1 ; ///<
    UINT32                                            Reserved18_31:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0101_STRUCT;

// **** D0F0xE4_CORE_0103 Register Definition ****
// Address
#define D0F0xE4_CORE_0103_ADDRESS                               0x103

// Type
#define D0F0xE4_CORE_0103_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0103_Switchclk_OFFSET                      0
#define D0F0xE4_CORE_0103_Switchclk_WIDTH                       1
#define D0F0xE4_CORE_0103_Switchclk_MASK                        0x1
#define D0F0xE4_CORE_0103_Resetpcfg_OFFSET                      1
#define D0F0xE4_CORE_0103_Resetpcfg_WIDTH                       1
#define D0F0xE4_CORE_0103_Resetpcfg_MASK                        0x2
#define D0F0xE4_CORE_0103_Resetlanemux_OFFSET                   2
#define D0F0xE4_CORE_0103_Resetlanemux_WIDTH                    1
#define D0F0xE4_CORE_0103_Resetlanemux_MASK                     0x4
#define D0F0xE4_CORE_0103_Resetwrapregs_OFFSET                  3
#define D0F0xE4_CORE_0103_Resetwrapregs_WIDTH                   1
#define D0F0xE4_CORE_0103_Resetwrapregs_MASK                    0x8
#define D0F0xE4_CORE_0103_Resetsrbm0_OFFSET                     4
#define D0F0xE4_CORE_0103_Resetsrbm0_WIDTH                      1
#define D0F0xE4_CORE_0103_Resetsrbm0_MASK                       0x10
#define D0F0xE4_CORE_0103_Resetsrbm1_OFFSET                     5
#define D0F0xE4_CORE_0103_Resetsrbm1_WIDTH                      1
#define D0F0xE4_CORE_0103_Resetsrbm1_MASK                       0x20
#define D0F0xE4_CORE_0103_Resetlc_OFFSET                        6
#define D0F0xE4_CORE_0103_Resetlc_WIDTH                         1
#define D0F0xE4_CORE_0103_Resetlc_MASK                          0x40
#define D0F0xE4_CORE_0103_Reserved_7_7_OFFSET                   7
#define D0F0xE4_CORE_0103_Reserved_7_7_WIDTH                    1
#define D0F0xE4_CORE_0103_Reserved_7_7_MASK                     0x80
#define D0F0xE4_CORE_0103_Syncidlepif00_OFFSET                  8
#define D0F0xE4_CORE_0103_Syncidlepif00_WIDTH                   1
#define D0F0xE4_CORE_0103_Syncidlepif00_MASK                    0x100
#define D0F0xE4_CORE_0103_Syncidlepif01_OFFSET                  9
#define D0F0xE4_CORE_0103_Syncidlepif01_WIDTH                   1
#define D0F0xE4_CORE_0103_Syncidlepif01_MASK                    0x200
#define D0F0xE4_CORE_0103_Reserved_12_10_OFFSET                 10
#define D0F0xE4_CORE_0103_Reserved_12_10_WIDTH                  3
#define D0F0xE4_CORE_0103_Reserved_12_10_MASK                   0x1c00
#define D0F0xE4_CORE_0103_Resetmntr_OFFSET                      13
#define D0F0xE4_CORE_0103_Resetmntr_WIDTH                       1
#define D0F0xE4_CORE_0103_Resetmntr_MASK                        0x2000
#define D0F0xE4_CORE_0103_Resethltr_OFFSET                      14
#define D0F0xE4_CORE_0103_Resethltr_WIDTH                       1
#define D0F0xE4_CORE_0103_Resethltr_MASK                        0x4000
#define D0F0xE4_CORE_0103_Resetcpm_OFFSET                       15
#define D0F0xE4_CORE_0103_Resetcpm_WIDTH                        1
#define D0F0xE4_CORE_0103_Resetcpm_MASK                         0x8000
#define D0F0xE4_CORE_0103_Resetpif0_OFFSET                      16
#define D0F0xE4_CORE_0103_Resetpif0_WIDTH                       1
#define D0F0xE4_CORE_0103_Resetpif0_MASK                        0x10000
#define D0F0xE4_CORE_0103_Resetpif1_OFFSET                      17
#define D0F0xE4_CORE_0103_Resetpif1_WIDTH                       1
#define D0F0xE4_CORE_0103_Resetpif1_MASK                        0x20000
#define D0F0xE4_CORE_0103_Reserved_19_18_OFFSET                 18
#define D0F0xE4_CORE_0103_Reserved_19_18_WIDTH                  2
#define D0F0xE4_CORE_0103_Reserved_19_18_MASK                   0xc0000
#define D0F0xE4_CORE_0103_Resetimparb0_OFFSET                   20
#define D0F0xE4_CORE_0103_Resetimparb0_WIDTH                    1
#define D0F0xE4_CORE_0103_Resetimparb0_MASK                     0x100000
#define D0F0xE4_CORE_0103_Resetimparb1_OFFSET                   21
#define D0F0xE4_CORE_0103_Resetimparb1_WIDTH                    1
#define D0F0xE4_CORE_0103_Resetimparb1_MASK                     0x200000
#define D0F0xE4_CORE_0103_Reserved_23_22_OFFSET                 22
#define D0F0xE4_CORE_0103_Reserved_23_22_WIDTH                  2
#define D0F0xE4_CORE_0103_Reserved_23_22_MASK                   0xc00000
#define D0F0xE4_CORE_0103_Resetphy0_OFFSET                      24
#define D0F0xE4_CORE_0103_Resetphy0_WIDTH                       1
#define D0F0xE4_CORE_0103_Resetphy0_MASK                        0x1000000
#define D0F0xE4_CORE_0103_Resetphy1_OFFSET                      25
#define D0F0xE4_CORE_0103_Resetphy1_WIDTH                       1
#define D0F0xE4_CORE_0103_Resetphy1_MASK                        0x2000000
#define D0F0xE4_CORE_0103_Reserved_27_26_OFFSET                 26
#define D0F0xE4_CORE_0103_Reserved_27_26_WIDTH                  2
#define D0F0xE4_CORE_0103_Reserved_27_26_MASK                   0xc000000
#define D0F0xE4_CORE_0103_Togglestrap_OFFSET                    28
#define D0F0xE4_CORE_0103_Togglestrap_WIDTH                     1
#define D0F0xE4_CORE_0103_Togglestrap_MASK                      0x10000000
#define D0F0xE4_CORE_0103_Cmdcfgen_OFFSET                       29
#define D0F0xE4_CORE_0103_Cmdcfgen_WIDTH                        1
#define D0F0xE4_CORE_0103_Cmdcfgen_MASK                         0x20000000
#define D0F0xE4_CORE_0103_Reserved_31_30_OFFSET                 30
#define D0F0xE4_CORE_0103_Reserved_31_30_WIDTH                  2
#define D0F0xE4_CORE_0103_Reserved_31_30_MASK                   0xc0000000

/// D0F0xE4_CORE_0103
typedef union {
  struct {                                                              ///<
    UINT32                                                Switchclk:1 ; ///<
    UINT32                                                Resetpcfg:1 ; ///<
    UINT32                                             Resetlanemux:1 ; ///<
    UINT32                                            Resetwrapregs:1 ; ///<
    UINT32                                               Resetsrbm0:1 ; ///<
    UINT32                                               Resetsrbm1:1 ; ///<
    UINT32                                                  Resetlc:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                            Syncidlepif00:1 ; ///<
    UINT32                                            Syncidlepif01:1 ; ///<
    UINT32                                           Reserved_12_10:3 ; ///<
    UINT32                                                Resetmntr:1 ; ///<
    UINT32                                                Resethltr:1 ; ///<
    UINT32                                                 Resetcpm:1 ; ///<
    UINT32                                                Resetpif0:1 ; ///<
    UINT32                                                Resetpif1:1 ; ///<
    UINT32                                           Reserved_19_18:2 ; ///<
    UINT32                                             Resetimparb0:1 ; ///<
    UINT32                                             Resetimparb1:1 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                                Resetphy0:1 ; ///<
    UINT32                                                Resetphy1:1 ; ///<
    UINT32                                           Reserved_27_26:2 ; ///<
    UINT32                                              Togglestrap:1 ; ///<
    UINT32                                                 Cmdcfgen:1 ; ///<
    UINT32                                           Reserved_31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0103_STRUCT;

// **** D0F0xE4_CORE_0118 Register Definition ****
// Address
#define D0F0xE4_CORE_0118_ADDRESS                               0x118

// Type
#define D0F0xE4_CORE_0118_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0118_LCLK_DYN_GATE_ENABLE_OFFSET           0
#define D0F0xE4_CORE_0118_LCLK_DYN_GATE_ENABLE_WIDTH            1
#define D0F0xE4_CORE_0118_LCLK_DYN_GATE_ENABLE_MASK             0x1
#define D0F0xE4_CORE_0118_TXCLK_DYN_GATE_ENABLE_OFFSET          1
#define D0F0xE4_CORE_0118_TXCLK_DYN_GATE_ENABLE_WIDTH           1
#define D0F0xE4_CORE_0118_TXCLK_DYN_GATE_ENABLE_MASK            0x2
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_ENABLE_OFFSET         2
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_ENABLE_WIDTH          1
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_ENABLE_MASK           0x4
#define D0F0xE4_CORE_0118_TXCLK_PIF_GATE_ENABLE_OFFSET          3
#define D0F0xE4_CORE_0118_TXCLK_PIF_GATE_ENABLE_WIDTH           1
#define D0F0xE4_CORE_0118_TXCLK_PIF_GATE_ENABLE_MASK            0x8
#define D0F0xE4_CORE_0118_TXCLK_GSKT_GATE_ENABLE_OFFSET         4
#define D0F0xE4_CORE_0118_TXCLK_GSKT_GATE_ENABLE_WIDTH          1
#define D0F0xE4_CORE_0118_TXCLK_GSKT_GATE_ENABLE_MASK           0x10
#define D0F0xE4_CORE_0118_TXCLK_LCNT_GATE_ENABLE_OFFSET         5
#define D0F0xE4_CORE_0118_TXCLK_LCNT_GATE_ENABLE_WIDTH          1
#define D0F0xE4_CORE_0118_TXCLK_LCNT_GATE_ENABLE_MASK           0x20
#define D0F0xE4_CORE_0118_TXCLK_REGS_GATE_ENABLE_OFFSET         6
#define D0F0xE4_CORE_0118_TXCLK_REGS_GATE_ENABLE_WIDTH          1
#define D0F0xE4_CORE_0118_TXCLK_REGS_GATE_ENABLE_MASK           0x40
#define D0F0xE4_CORE_0118_TXCLK_PRBS_GATE_ENABLE_OFFSET         7
#define D0F0xE4_CORE_0118_TXCLK_PRBS_GATE_ENABLE_WIDTH          1
#define D0F0xE4_CORE_0118_TXCLK_PRBS_GATE_ENABLE_MASK           0x80
#define D0F0xE4_CORE_0118_REFCLK_REGS_GATE_ENABLE_OFFSET        8
#define D0F0xE4_CORE_0118_REFCLK_REGS_GATE_ENABLE_WIDTH         1
#define D0F0xE4_CORE_0118_REFCLK_REGS_GATE_ENABLE_MASK          0x100
#define D0F0xE4_CORE_0118_LCLK_DYN_GATE_LATENCY_OFFSET          9
#define D0F0xE4_CORE_0118_LCLK_DYN_GATE_LATENCY_WIDTH           1
#define D0F0xE4_CORE_0118_LCLK_DYN_GATE_LATENCY_MASK            0x200
#define D0F0xE4_CORE_0118_TXCLK_DYN_GATE_LATENCY_OFFSET         10
#define D0F0xE4_CORE_0118_TXCLK_DYN_GATE_LATENCY_WIDTH          1
#define D0F0xE4_CORE_0118_TXCLK_DYN_GATE_LATENCY_MASK           0x400
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_LATENCY_OFFSET        11
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_LATENCY_WIDTH         1
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_LATENCY_MASK          0x800
#define D0F0xE4_CORE_0118_TXCLK_REGS_GATE_LATENCY_OFFSET        12
#define D0F0xE4_CORE_0118_TXCLK_REGS_GATE_LATENCY_WIDTH         1
#define D0F0xE4_CORE_0118_TXCLK_REGS_GATE_LATENCY_MASK          0x1000
#define D0F0xE4_CORE_0118_REFCLK_REGS_GATE_LATENCY_OFFSET       13
#define D0F0xE4_CORE_0118_REFCLK_REGS_GATE_LATENCY_WIDTH        1
#define D0F0xE4_CORE_0118_REFCLK_REGS_GATE_LATENCY_MASK         0x2000
#define D0F0xE4_CORE_0118_LCLK_GATE_TXCLK_FREE_OFFSET           14
#define D0F0xE4_CORE_0118_LCLK_GATE_TXCLK_FREE_WIDTH            1
#define D0F0xE4_CORE_0118_LCLK_GATE_TXCLK_FREE_MASK             0x4000
#define D0F0xE4_CORE_0118_RCVR_DET_CLK_ENABLE_OFFSET            15
#define D0F0xE4_CORE_0118_RCVR_DET_CLK_ENABLE_WIDTH             1
#define D0F0xE4_CORE_0118_RCVR_DET_CLK_ENABLE_MASK              0x8000
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_PLL_PDN_OFFSET        16
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_PLL_PDN_WIDTH         1
#define D0F0xE4_CORE_0118_TXCLK_PERM_GATE_PLL_PDN_MASK          0x10000
#define D0F0xE4_CORE_0118_FAST_TXCLK_LATENCY_OFFSET             17
#define D0F0xE4_CORE_0118_FAST_TXCLK_LATENCY_WIDTH              3
#define D0F0xE4_CORE_0118_FAST_TXCLK_LATENCY_MASK               0xe0000
#define D0F0xE4_CORE_0118_MASTER_PCIE_PLL_SELECT_OFFSET         20
#define D0F0xE4_CORE_0118_MASTER_PCIE_PLL_SELECT_WIDTH          1
#define D0F0xE4_CORE_0118_MASTER_PCIE_PLL_SELECT_MASK           0x100000
#define D0F0xE4_CORE_0118_MASTER_PCIE_PLL_AUTO_OFFSET           21
#define D0F0xE4_CORE_0118_MASTER_PCIE_PLL_AUTO_WIDTH            1
#define D0F0xE4_CORE_0118_MASTER_PCIE_PLL_AUTO_MASK             0x200000
#define D0F0xE4_CORE_0118_REFCLK_XSTCLK_ENABLE_OFFSET           22
#define D0F0xE4_CORE_0118_REFCLK_XSTCLK_ENABLE_WIDTH            1
#define D0F0xE4_CORE_0118_REFCLK_XSTCLK_ENABLE_MASK             0x400000
#define D0F0xE4_CORE_0118_REFCLK_XSTCLK_LATENCY_OFFSET          23
#define D0F0xE4_CORE_0118_REFCLK_XSTCLK_LATENCY_WIDTH           1
#define D0F0xE4_CORE_0118_REFCLK_XSTCLK_LATENCY_MASK            0x800000
#define D0F0xE4_CORE_0118_SPARE_REGS_OFFSET                     24
#define D0F0xE4_CORE_0118_SPARE_REGS_WIDTH                      8
#define D0F0xE4_CORE_0118_SPARE_REGS_MASK                       0xff000000

/// D0F0xE4_CORE_0118
typedef union {
  struct {                                                              ///<
    UINT32                                     LCLK_DYN_GATE_ENABLE:1 ; ///<
    UINT32                                    TXCLK_DYN_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_PERM_GATE_ENABLE:1 ; ///<
    UINT32                                    TXCLK_PIF_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_GSKT_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_LCNT_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_REGS_GATE_ENABLE:1 ; ///<
    UINT32                                   TXCLK_PRBS_GATE_ENABLE:1 ; ///<
    UINT32                                  REFCLK_REGS_GATE_ENABLE:1 ; ///<
    UINT32                                    LCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                   TXCLK_DYN_GATE_LATENCY:1 ; ///<
    UINT32                                  TXCLK_PERM_GATE_LATENCY:1 ; ///<
    UINT32                                  TXCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                 REFCLK_REGS_GATE_LATENCY:1 ; ///<
    UINT32                                     LCLK_GATE_TXCLK_FREE:1 ; ///<
    UINT32                                      RCVR_DET_CLK_ENABLE:1 ; ///<
    UINT32                                  TXCLK_PERM_GATE_PLL_PDN:1 ; ///<
    UINT32                                       FAST_TXCLK_LATENCY:3 ; ///<
    UINT32                                   MASTER_PCIE_PLL_SELECT:1 ; ///<
    UINT32                                     MASTER_PCIE_PLL_AUTO:1 ; ///<
    UINT32                                     REFCLK_XSTCLK_ENABLE:1 ; ///<
    UINT32                                    REFCLK_XSTCLK_LATENCY:1 ; ///<
    UINT32                                               SPARE_REGS:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0118_STRUCT;

// **** D0F0xE4_CORE_0121 Register Definition ****
// Address
#define D0F0xE4_CORE_0121_ADDRESS                               0x121

// Type
#define D0F0xE4_CORE_0121_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0121_TXLANE0_OFFSET                        0
#define D0F0xE4_CORE_0121_TXLANE0_WIDTH                         8
#define D0F0xE4_CORE_0121_TXLANE0_MASK                          0xff
#define D0F0xE4_CORE_0121_TXLANE1_OFFSET                        8
#define D0F0xE4_CORE_0121_TXLANE1_WIDTH                         8
#define D0F0xE4_CORE_0121_TXLANE1_MASK                          0xff00
#define D0F0xE4_CORE_0121_TXLANE2_OFFSET                        16
#define D0F0xE4_CORE_0121_TXLANE2_WIDTH                         8
#define D0F0xE4_CORE_0121_TXLANE2_MASK                          0xff0000
#define D0F0xE4_CORE_0121_TXLANE3_OFFSET                        24
#define D0F0xE4_CORE_0121_TXLANE3_WIDTH                         8
#define D0F0xE4_CORE_0121_TXLANE3_MASK                          0xff000000

/// D0F0xE4_CORE_0121
typedef union {
  struct {                                                              ///<
    UINT32                                                  TXLANE0:8 ; ///<
    UINT32                                                  TXLANE1:8 ; ///<
    UINT32                                                  TXLANE2:8 ; ///<
    UINT32                                                  TXLANE3:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0121_STRUCT;

// **** D0F0xE4_CORE_0125 Register Definition ****
// Address
#define D0F0xE4_CORE_0125_ADDRESS                               0x125

// Type
#define D0F0xE4_CORE_0125_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0125_RXLANE0_OFFSET                        0
#define D0F0xE4_CORE_0125_RXLANE0_WIDTH                         8
#define D0F0xE4_CORE_0125_RXLANE0_MASK                          0xff
#define D0F0xE4_CORE_0125_RXLANE1_OFFSET                        8
#define D0F0xE4_CORE_0125_RXLANE1_WIDTH                         8
#define D0F0xE4_CORE_0125_RXLANE1_MASK                          0xff00
#define D0F0xE4_CORE_0125_RXLANE2_OFFSET                        16
#define D0F0xE4_CORE_0125_RXLANE2_WIDTH                         8
#define D0F0xE4_CORE_0125_RXLANE2_MASK                          0xff0000
#define D0F0xE4_CORE_0125_RXLANE3_OFFSET                        24
#define D0F0xE4_CORE_0125_RXLANE3_WIDTH                         8
#define D0F0xE4_CORE_0125_RXLANE3_MASK                          0xff000000

/// D0F0xE4_CORE_0125
typedef union {
  struct {                                                              ///<
    UINT32                                                  RXLANE0:8 ; ///<
    UINT32                                                  RXLANE1:8 ; ///<
    UINT32                                                  RXLANE2:8 ; ///<
    UINT32                                                  RXLANE3:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0125_STRUCT;

// **** D0F0xE4_CORE_0129 Register Definition ****
// Address
#define D0F0xE4_CORE_0129_ADDRESS                               0x129

// Type
#define D0F0xE4_CORE_0129_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_0129_LANE_enable_OFFSET                    0
#define D0F0xE4_CORE_0129_LANE_enable_WIDTH                     16
#define D0F0xE4_CORE_0129_LANE_enable_MASK                      0xffff
#define D0F0xE4_CORE_0129_Reserved_OFFSET                       16
#define D0F0xE4_CORE_0129_Reserved_WIDTH                        16
#define D0F0xE4_CORE_0129_Reserved_MASK                         0xffff0000

/// D0F0xE4_CORE_0129
typedef union {
  struct {                                                              ///<
    UINT32                                              LANE_enable:16; ///<
    UINT32                                                 Reserved:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_0129_STRUCT;

// **** D0F0xE4_CORE_012A Register Definition ****
// Address
#define D0F0xE4_CORE_012A_ADDRESS                               0x12a

// Type
#define D0F0xE4_CORE_012A_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_012A_PRBSPCIeSelect_OFFSET                 0
#define D0F0xE4_CORE_012A_PRBSPCIeSelect_WIDTH                  16
#define D0F0xE4_CORE_012A_PRBSPCIeSelect_MASK                   0xffff
#define D0F0xE4_CORE_012A_Reserved_OFFSET                       16
#define D0F0xE4_CORE_012A_Reserved_WIDTH                        12
#define D0F0xE4_CORE_012A_Reserved_MASK                         0xfff0000
#define D0F0xE4_CORE_012A_LMLaneDegrade0_OFFSET                 28
#define D0F0xE4_CORE_012A_LMLaneDegrade0_WIDTH                  1
#define D0F0xE4_CORE_012A_LMLaneDegrade0_MASK                   0x10000000
#define D0F0xE4_CORE_012A_LMLaneDegrade1_OFFSET                 29
#define D0F0xE4_CORE_012A_LMLaneDegrade1_WIDTH                  1
#define D0F0xE4_CORE_012A_LMLaneDegrade1_MASK                   0x20000000
#define D0F0xE4_CORE_012A_LMLaneDegrade2_OFFSET                 30
#define D0F0xE4_CORE_012A_LMLaneDegrade2_WIDTH                  1
#define D0F0xE4_CORE_012A_LMLaneDegrade2_MASK                   0x40000000
#define D0F0xE4_CORE_012A_LMLaneDegrade3_OFFSET                 31
#define D0F0xE4_CORE_012A_LMLaneDegrade3_WIDTH                  1
#define D0F0xE4_CORE_012A_LMLaneDegrade3_MASK                   0x80000000

/// D0F0xE4_CORE_012A
typedef union {
  struct {                                                              ///<
    UINT32                                           PRBSPCIeSelect:16; ///<
    UINT32                                                 Reserved:12; ///<
    UINT32                                           LMLaneDegrade0:1 ; ///<
    UINT32                                           LMLaneDegrade1:1 ; ///<
    UINT32                                           LMLaneDegrade2:1 ; ///<
    UINT32                                           LMLaneDegrade3:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_012A_STRUCT;

// **** D0F0xE4_CORE_012C Register Definition ****
// Address
#define D0F0xE4_CORE_012C_ADDRESS                               0x12c

// Type
#define D0F0xE4_CORE_012C_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_012C_LMTxEn0_OFFSET                        0
#define D0F0xE4_CORE_012C_LMTxEn0_WIDTH                         1
#define D0F0xE4_CORE_012C_LMTxEn0_MASK                          0x1
#define D0F0xE4_CORE_012C_LMTxClkEn0_OFFSET                     1
#define D0F0xE4_CORE_012C_LMTxClkEn0_WIDTH                      1
#define D0F0xE4_CORE_012C_LMTxClkEn0_MASK                       0x2
#define D0F0xE4_CORE_012C_LMTxMargin0_OFFSET                    2
#define D0F0xE4_CORE_012C_LMTxMargin0_WIDTH                     3
#define D0F0xE4_CORE_012C_LMTxMargin0_MASK                      0x1c
#define D0F0xE4_CORE_012C_LMSkipBit0_OFFSET                     5
#define D0F0xE4_CORE_012C_LMSkipBit0_WIDTH                      1
#define D0F0xE4_CORE_012C_LMSkipBit0_MASK                       0x20
#define D0F0xE4_CORE_012C_LMLaneUnused0_OFFSET                  6
#define D0F0xE4_CORE_012C_LMLaneUnused0_WIDTH                   1
#define D0F0xE4_CORE_012C_LMLaneUnused0_MASK                    0x40
#define D0F0xE4_CORE_012C_LMTxMarginEn0_OFFSET                  7
#define D0F0xE4_CORE_012C_LMTxMarginEn0_WIDTH                   1
#define D0F0xE4_CORE_012C_LMTxMarginEn0_MASK                    0x80
#define D0F0xE4_CORE_012C_LMDeemph0_OFFSET                      8
#define D0F0xE4_CORE_012C_LMDeemph0_WIDTH                       1
#define D0F0xE4_CORE_012C_LMDeemph0_MASK                        0x100
#define D0F0xE4_CORE_012C_LMTxEn1_OFFSET                        9
#define D0F0xE4_CORE_012C_LMTxEn1_WIDTH                         1
#define D0F0xE4_CORE_012C_LMTxEn1_MASK                          0x200
#define D0F0xE4_CORE_012C_LMTxClkEn1_OFFSET                     10
#define D0F0xE4_CORE_012C_LMTxClkEn1_WIDTH                      1
#define D0F0xE4_CORE_012C_LMTxClkEn1_MASK                       0x400
#define D0F0xE4_CORE_012C_LMTxMargin1_OFFSET                    11
#define D0F0xE4_CORE_012C_LMTxMargin1_WIDTH                     3
#define D0F0xE4_CORE_012C_LMTxMargin1_MASK                      0x3800
#define D0F0xE4_CORE_012C_LMSkipBit1_OFFSET                     14
#define D0F0xE4_CORE_012C_LMSkipBit1_WIDTH                      1
#define D0F0xE4_CORE_012C_LMSkipBit1_MASK                       0x4000
#define D0F0xE4_CORE_012C_LMLaneUnused1_OFFSET                  15
#define D0F0xE4_CORE_012C_LMLaneUnused1_WIDTH                   1
#define D0F0xE4_CORE_012C_LMLaneUnused1_MASK                    0x8000
#define D0F0xE4_CORE_012C_LMTxMarginEn1_OFFSET                  16
#define D0F0xE4_CORE_012C_LMTxMarginEn1_WIDTH                   1
#define D0F0xE4_CORE_012C_LMTxMarginEn1_MASK                    0x10000
#define D0F0xE4_CORE_012C_LMDeemph1_OFFSET                      17
#define D0F0xE4_CORE_012C_LMDeemph1_WIDTH                       1
#define D0F0xE4_CORE_012C_LMDeemph1_MASK                        0x20000
#define D0F0xE4_CORE_012C_LMTxEn2_OFFSET                        18
#define D0F0xE4_CORE_012C_LMTxEn2_WIDTH                         1
#define D0F0xE4_CORE_012C_LMTxEn2_MASK                          0x40000
#define D0F0xE4_CORE_012C_LMTxClkEn2_OFFSET                     19
#define D0F0xE4_CORE_012C_LMTxClkEn2_WIDTH                      1
#define D0F0xE4_CORE_012C_LMTxClkEn2_MASK                       0x80000
#define D0F0xE4_CORE_012C_LMTxMargin2_OFFSET                    20
#define D0F0xE4_CORE_012C_LMTxMargin2_WIDTH                     3
#define D0F0xE4_CORE_012C_LMTxMargin2_MASK                      0x700000
#define D0F0xE4_CORE_012C_LMSkipBit2_OFFSET                     23
#define D0F0xE4_CORE_012C_LMSkipBit2_WIDTH                      1
#define D0F0xE4_CORE_012C_LMSkipBit2_MASK                       0x800000
#define D0F0xE4_CORE_012C_LMLaneUnused2_OFFSET                  24
#define D0F0xE4_CORE_012C_LMLaneUnused2_WIDTH                   1
#define D0F0xE4_CORE_012C_LMLaneUnused2_MASK                    0x1000000
#define D0F0xE4_CORE_012C_LMTxMarginEn2_OFFSET                  25
#define D0F0xE4_CORE_012C_LMTxMarginEn2_WIDTH                   1
#define D0F0xE4_CORE_012C_LMTxMarginEn2_MASK                    0x2000000
#define D0F0xE4_CORE_012C_LMDeemph2_OFFSET                      26
#define D0F0xE4_CORE_012C_LMDeemph2_WIDTH                       1
#define D0F0xE4_CORE_012C_LMDeemph2_MASK                        0x4000000
#define D0F0xE4_CORE_012C_TxCoeffID0_OFFSET                     27
#define D0F0xE4_CORE_012C_TxCoeffID0_WIDTH                      2
#define D0F0xE4_CORE_012C_TxCoeffID0_MASK                       0x18000000
#define D0F0xE4_CORE_012C_TxCoeffID1_OFFSET                     29
#define D0F0xE4_CORE_012C_TxCoeffID1_WIDTH                      2
#define D0F0xE4_CORE_012C_TxCoeffID1_MASK                       0x60000000
#define D0F0xE4_CORE_012C_Reserved_31_31_OFFSET                 31
#define D0F0xE4_CORE_012C_Reserved_31_31_WIDTH                  1
#define D0F0xE4_CORE_012C_Reserved_31_31_MASK                   0x80000000

/// D0F0xE4_CORE_012C
typedef union {
  struct {                                                              ///<
    UINT32                                                  LMTxEn0:1 ; ///<
    UINT32                                               LMTxClkEn0:1 ; ///<
    UINT32                                              LMTxMargin0:3 ; ///<
    UINT32                                               LMSkipBit0:1 ; ///<
    UINT32                                            LMLaneUnused0:1 ; ///<
    UINT32                                            LMTxMarginEn0:1 ; ///<
    UINT32                                                LMDeemph0:1 ; ///<
    UINT32                                                  LMTxEn1:1 ; ///<
    UINT32                                               LMTxClkEn1:1 ; ///<
    UINT32                                              LMTxMargin1:3 ; ///<
    UINT32                                               LMSkipBit1:1 ; ///<
    UINT32                                            LMLaneUnused1:1 ; ///<
    UINT32                                            LMTxMarginEn1:1 ; ///<
    UINT32                                                LMDeemph1:1 ; ///<
    UINT32                                                  LMTxEn2:1 ; ///<
    UINT32                                               LMTxClkEn2:1 ; ///<
    UINT32                                              LMTxMargin2:3 ; ///<
    UINT32                                               LMSkipBit2:1 ; ///<
    UINT32                                            LMLaneUnused2:1 ; ///<
    UINT32                                            LMTxMarginEn2:1 ; ///<
    UINT32                                                LMDeemph2:1 ; ///<
    UINT32                                               TxCoeffID0:2 ; ///<
    UINT32                                               TxCoeffID1:2 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_012C_STRUCT;

// **** D0F0xE4_CORE_012D Register Definition ****
// Address
#define D0F0xE4_CORE_012D_ADDRESS                               0x12d

// Type
#define D0F0xE4_CORE_012D_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_CORE_012D_LMTxEn3_OFFSET                        0
#define D0F0xE4_CORE_012D_LMTxEn3_WIDTH                         1
#define D0F0xE4_CORE_012D_LMTxEn3_MASK                          0x1
#define D0F0xE4_CORE_012D_LMTxClkEn3_OFFSET                     1
#define D0F0xE4_CORE_012D_LMTxClkEn3_WIDTH                      1
#define D0F0xE4_CORE_012D_LMTxClkEn3_MASK                       0x2
#define D0F0xE4_CORE_012D_LMTxMargin3_OFFSET                    2
#define D0F0xE4_CORE_012D_LMTxMargin3_WIDTH                     3
#define D0F0xE4_CORE_012D_LMTxMargin3_MASK                      0x1c
#define D0F0xE4_CORE_012D_LMSkipBit3_OFFSET                     5
#define D0F0xE4_CORE_012D_LMSkipBit3_WIDTH                      1
#define D0F0xE4_CORE_012D_LMSkipBit3_MASK                       0x20
#define D0F0xE4_CORE_012D_LMLaneUnused3_OFFSET                  6
#define D0F0xE4_CORE_012D_LMLaneUnused3_WIDTH                   1
#define D0F0xE4_CORE_012D_LMLaneUnused3_MASK                    0x40
#define D0F0xE4_CORE_012D_LMTxMarginEn3_OFFSET                  7
#define D0F0xE4_CORE_012D_LMTxMarginEn3_WIDTH                   1
#define D0F0xE4_CORE_012D_LMTxMarginEn3_MASK                    0x80
#define D0F0xE4_CORE_012D_LMDeemph3_OFFSET                      8
#define D0F0xE4_CORE_012D_LMDeemph3_WIDTH                       1
#define D0F0xE4_CORE_012D_LMDeemph3_MASK                        0x100
#define D0F0xE4_CORE_012D_TxCoeffID2_OFFSET                     9
#define D0F0xE4_CORE_012D_TxCoeffID2_WIDTH                      2
#define D0F0xE4_CORE_012D_TxCoeffID2_MASK                       0x600
#define D0F0xE4_CORE_012D_TxCoeffID3_OFFSET                     11
#define D0F0xE4_CORE_012D_TxCoeffID3_WIDTH                      2
#define D0F0xE4_CORE_012D_TxCoeffID3_MASK                       0x1800
#define D0F0xE4_CORE_012D_TxCoeff0_OFFSET                       13
#define D0F0xE4_CORE_012D_TxCoeff0_WIDTH                        6
#define D0F0xE4_CORE_012D_TxCoeff0_MASK                         0x7e000
#define D0F0xE4_CORE_012D_TxCoeff1_OFFSET                       19
#define D0F0xE4_CORE_012D_TxCoeff1_WIDTH                        6
#define D0F0xE4_CORE_012D_TxCoeff1_MASK                         0x1f80000
#define D0F0xE4_CORE_012D_TxCoeff2_OFFSET                       25
#define D0F0xE4_CORE_012D_TxCoeff2_WIDTH                        6
#define D0F0xE4_CORE_012D_TxCoeff2_MASK                         0x7e000000
#define D0F0xE4_CORE_012D_Reserved_31_31_OFFSET                 31
#define D0F0xE4_CORE_012D_Reserved_31_31_WIDTH                  1
#define D0F0xE4_CORE_012D_Reserved_31_31_MASK                   0x80000000

/// D0F0xE4_CORE_012D
typedef union {
  struct {                                                              ///<
    UINT32                                                  LMTxEn3:1 ; ///<
    UINT32                                               LMTxClkEn3:1 ; ///<
    UINT32                                              LMTxMargin3:3 ; ///<
    UINT32                                               LMSkipBit3:1 ; ///<
    UINT32                                            LMLaneUnused3:1 ; ///<
    UINT32                                            LMTxMarginEn3:1 ; ///<
    UINT32                                                LMDeemph3:1 ; ///<
    UINT32                                               TxCoeffID2:2 ; ///<
    UINT32                                               TxCoeffID3:2 ; ///<
    UINT32                                                 TxCoeff0:6 ; ///<
    UINT32                                                 TxCoeff1:6 ; ///<
    UINT32                                                 TxCoeff2:6 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_CORE_012D_STRUCT;

// **** D0F0xE4_PIF_0004 Register Definition ****
// Address
#define D0F0xE4_PIF_0004_ADDRESS                                0x4

// Type
#define D0F0xE4_PIF_0004_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0004_PifPllPwrdnEn_OFFSET                   0
#define D0F0xE4_PIF_0004_PifPllPwrdnEn_WIDTH                    1
#define D0F0xE4_PIF_0004_PifPllPwrdnEn_MASK                     0x1
#define D0F0xE4_PIF_0004_DtmForceFreqdivX1_OFFSET               1
#define D0F0xE4_PIF_0004_DtmForceFreqdivX1_WIDTH                1
#define D0F0xE4_PIF_0004_DtmForceFreqdivX1_MASK                 0x2
#define D0F0xE4_PIF_0004_PifPllHndshkEarlyAbort_OFFSET          2
#define D0F0xE4_PIF_0004_PifPllHndshkEarlyAbort_WIDTH           1
#define D0F0xE4_PIF_0004_PifPllHndshkEarlyAbort_MASK            0x4
#define D0F0xE4_PIF_0004_PifPllPwrdnEarlyExit_OFFSET            3
#define D0F0xE4_PIF_0004_PifPllPwrdnEarlyExit_WIDTH             1
#define D0F0xE4_PIF_0004_PifPllPwrdnEarlyExit_MASK              0x8
#define D0F0xE4_PIF_0004_PhyRstPwrokVdd_OFFSET                  4
#define D0F0xE4_PIF_0004_PhyRstPwrokVdd_WIDTH                   1
#define D0F0xE4_PIF_0004_PhyRstPwrokVdd_MASK                    0x10
#define D0F0xE4_PIF_0004_Reserved_5_5_OFFSET                    5
#define D0F0xE4_PIF_0004_Reserved_5_5_WIDTH                     1
#define D0F0xE4_PIF_0004_Reserved_5_5_MASK                      0x20
#define D0F0xE4_PIF_0004_PifPllStatus_OFFSET                    6
#define D0F0xE4_PIF_0004_PifPllStatus_WIDTH                     2
#define D0F0xE4_PIF_0004_PifPllStatus_MASK                      0xc0
#define D0F0xE4_PIF_0004_PifPllDegradeOffVote_OFFSET            8
#define D0F0xE4_PIF_0004_PifPllDegradeOffVote_WIDTH             1
#define D0F0xE4_PIF_0004_PifPllDegradeOffVote_MASK              0x100
#define D0F0xE4_PIF_0004_PifPllUnusedOffVote_OFFSET             9
#define D0F0xE4_PIF_0004_PifPllUnusedOffVote_WIDTH              1
#define D0F0xE4_PIF_0004_PifPllUnusedOffVote_MASK               0x200
#define D0F0xE4_PIF_0004_PifPllDegradeS2Vote_OFFSET             10
#define D0F0xE4_PIF_0004_PifPllDegradeS2Vote_WIDTH              1
#define D0F0xE4_PIF_0004_PifPllDegradeS2Vote_MASK               0x400
#define D0F0xE4_PIF_0004_PifPgExitMode_OFFSET                   11
#define D0F0xE4_PIF_0004_PifPgExitMode_WIDTH                    1
#define D0F0xE4_PIF_0004_PifPgExitMode_MASK                     0x800
#define D0F0xE4_PIF_0004_PifDegradePwrPllMode_OFFSET            12
#define D0F0xE4_PIF_0004_PifDegradePwrPllMode_WIDTH             1
#define D0F0xE4_PIF_0004_PifDegradePwrPllMode_MASK              0x1000
#define D0F0xE4_PIF_0004_PifLaneunusedAffectGang_OFFSET         13
#define D0F0xE4_PIF_0004_PifLaneunusedAffectGang_WIDTH          1
#define D0F0xE4_PIF_0004_PifLaneunusedAffectGang_MASK           0x2000
#define D0F0xE4_PIF_0004_PifPgAbortDisable_OFFSET               14
#define D0F0xE4_PIF_0004_PifPgAbortDisable_WIDTH                1
#define D0F0xE4_PIF_0004_PifPgAbortDisable_MASK                 0x4000
#define D0F0xE4_PIF_0004_Reserved_31_15_OFFSET                  15
#define D0F0xE4_PIF_0004_Reserved_31_15_WIDTH                   17
#define D0F0xE4_PIF_0004_Reserved_31_15_MASK                    0xffff8000

/// D0F0xE4_PIF_0004
typedef union {
  struct {                                                              ///<
    UINT32                                            PifPllPwrdnEn:1 ; ///<
    UINT32                                        DtmForceFreqdivX1:1 ; ///<
    UINT32                                   PifPllHndshkEarlyAbort:1 ; ///<
    UINT32                                     PifPllPwrdnEarlyExit:1 ; ///<
    UINT32                                           PhyRstPwrokVdd:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                             PifPllStatus:2 ; ///<
    UINT32                                     PifPllDegradeOffVote:1 ; ///<
    UINT32                                      PifPllUnusedOffVote:1 ; ///<
    UINT32                                      PifPllDegradeS2Vote:1 ; ///<
    UINT32                                            PifPgExitMode:1 ; ///<
    UINT32                                     PifDegradePwrPllMode:1 ; ///<
    UINT32                                  PifLaneunusedAffectGang:1 ; ///<
    UINT32                                        PifPgAbortDisable:1 ; ///<
    UINT32                                           Reserved_31_15:17; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0004_STRUCT;

// **** D0F0xE4_PIF_0008 Register Definition ****
// Address
#define D0F0xE4_PIF_0008_ADDRESS                             0x8

// Type
#define D0F0xE4_PIF_0008_TYPE                                TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_0008_TxpwrInS2_OFFSET                    0
#define D0F0xE4_PIF_0008_TxpwrInS2_WIDTH                     3
#define D0F0xE4_PIF_0008_TxpwrInS2_MASK                      0x7
#define D0F0xE4_PIF_0008_TxpwrInSpdchng_OFFSET               3
#define D0F0xE4_PIF_0008_TxpwrInSpdchng_WIDTH                3
#define D0F0xE4_PIF_0008_TxpwrInSpdchng_MASK                 0x38
#define D0F0xE4_PIF_0008_TxpwrInOff_OFFSET                   6
#define D0F0xE4_PIF_0008_TxpwrInOff_WIDTH                    3
#define D0F0xE4_PIF_0008_TxpwrInOff_MASK                     0x1c0
#define D0F0xE4_PIF_0008_TxpwrInDegrade_OFFSET               9
#define D0F0xE4_PIF_0008_TxpwrInDegrade_WIDTH                3
#define D0F0xE4_PIF_0008_TxpwrInDegrade_MASK                 0xe00
#define D0F0xE4_PIF_0008_TxpwrInUnused_OFFSET                12
#define D0F0xE4_PIF_0008_TxpwrInUnused_WIDTH                 3
#define D0F0xE4_PIF_0008_TxpwrInUnused_MASK                  0x7000
#define D0F0xE4_PIF_0008_TxpwrInInit_OFFSET                  15
#define D0F0xE4_PIF_0008_TxpwrInInit_WIDTH                   3
#define D0F0xE4_PIF_0008_TxpwrInInit_MASK                    0x38000
#define D0F0xE4_PIF_0008_TxpwrInPllOff_OFFSET                18
#define D0F0xE4_PIF_0008_TxpwrInPllOff_WIDTH                 3
#define D0F0xE4_PIF_0008_TxpwrInPllOff_MASK                  0x1c0000
#define D0F0xE4_PIF_0008_TxpwrInDegradeMode_OFFSET           21
#define D0F0xE4_PIF_0008_TxpwrInDegradeMode_WIDTH            1
#define D0F0xE4_PIF_0008_TxpwrInDegradeMode_MASK             0x200000
#define D0F0xE4_PIF_0008_TxpwrInUnusedMode_OFFSET            22
#define D0F0xE4_PIF_0008_TxpwrInUnusedMode_WIDTH             1
#define D0F0xE4_PIF_0008_TxpwrInUnusedMode_MASK              0x400000
#define D0F0xE4_PIF_0008_TxpwrGatingInL1_OFFSET              23
#define D0F0xE4_PIF_0008_TxpwrGatingInL1_WIDTH               1
#define D0F0xE4_PIF_0008_TxpwrGatingInL1_MASK                0x800000
#define D0F0xE4_PIF_0008_TxpwrGatingInUnused_OFFSET          24
#define D0F0xE4_PIF_0008_TxpwrGatingInUnused_WIDTH           1
#define D0F0xE4_PIF_0008_TxpwrGatingInUnused_MASK            0x1000000
#define D0F0xE4_PIF_0008_Reserved_31_25_OFFSET               25
#define D0F0xE4_PIF_0008_Reserved_31_25_WIDTH                7
#define D0F0xE4_PIF_0008_Reserved_31_25_MASK                 0xfe000000

/// D0F0xE4_PIF_0008PIF
typedef union {
  struct {                                                              ///<
    UINT32                                                TxpwrInS2:3 ; ///<
    UINT32                                           TxpwrInSpdchng:3 ; ///<
    UINT32                                               TxpwrInOff:3 ; ///<
    UINT32                                           TxpwrInDegrade:3 ; ///<
    UINT32                                            TxpwrInUnused:3 ; ///<
    UINT32                                              TxpwrInInit:3 ; ///<
    UINT32                                            TxpwrInPllOff:3 ; ///<
    UINT32                                       TxpwrInDegradeMode:1 ; ///<
    UINT32                                        TxpwrInUnusedMode:1 ; ///<
    UINT32                                          TxpwrGatingInL1:1 ; ///<
    UINT32                                      TxpwrGatingInUnused:1 ; ///<
    UINT32                                           Reserved_31_25:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_0008_STRUCT;

// **** D0F0xE4_PIF_000A Register Definition ****
// Address
#define D0F0xE4_PIF_000A_ADDRESS                             0xA

// Type
#define D0F0xE4_PIF_000A_TYPE                                TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_000A_RxpwrInS2_OFFSET                    0
#define D0F0xE4_PIF_000A_RxpwrInS2_WIDTH                     3
#define D0F0xE4_PIF_000A_RxpwrInS2_MASK                      0x7
#define D0F0xE4_PIF_000A_RxpwrInSpdchng_OFFSET               3
#define D0F0xE4_PIF_000A_RxpwrInSpdchng_WIDTH                3
#define D0F0xE4_PIF_000A_RxpwrInSpdchng_MASK                 0x38
#define D0F0xE4_PIF_000A_RxpwrInOff_OFFSET                   6
#define D0F0xE4_PIF_000A_RxpwrInOff_WIDTH                    3
#define D0F0xE4_PIF_000A_RxpwrInOff_MASK                     0x1c0
#define D0F0xE4_PIF_000A_RxpwrInDegrade_OFFSET               9
#define D0F0xE4_PIF_000A_RxpwrInDegrade_WIDTH                3
#define D0F0xE4_PIF_000A_RxpwrInDegrade_MASK                 0xe00
#define D0F0xE4_PIF_000A_RxpwrInUnused_OFFSET                12
#define D0F0xE4_PIF_000A_RxpwrInUnused_WIDTH                 3
#define D0F0xE4_PIF_000A_RxpwrInUnused_MASK                  0x7000
#define D0F0xE4_PIF_000A_RxpwrInInit_OFFSET                  15
#define D0F0xE4_PIF_000A_RxpwrInInit_WIDTH                   3
#define D0F0xE4_PIF_000A_RxpwrInInit_MASK                    0x38000
#define D0F0xE4_PIF_000A_RxpwrInPllOff_OFFSET                18
#define D0F0xE4_PIF_000A_RxpwrInPllOff_WIDTH                 3
#define D0F0xE4_PIF_000A_RxpwrInPllOff_MASK                  0x1c0000
#define D0F0xE4_PIF_000A_RxpwrInDegradeMode_OFFSET           21
#define D0F0xE4_PIF_000A_RxpwrInDegradeMode_WIDTH            1
#define D0F0xE4_PIF_000A_RxpwrInDegradeMode_MASK             0x200000
#define D0F0xE4_PIF_000A_RxpwrInUnusedMode_OFFSET            22
#define D0F0xE4_PIF_000A_RxpwrInUnusedMode_WIDTH             1
#define D0F0xE4_PIF_000A_RxpwrInUnusedMode_MASK              0x400000
#define D0F0xE4_PIF_000A_RxpwrGatingInL1_OFFSET              23
#define D0F0xE4_PIF_000A_RxpwrGatingInL1_WIDTH               1
#define D0F0xE4_PIF_000A_RxpwrGatingInL1_MASK                0x800000
#define D0F0xE4_PIF_000A_RxpwrGatingInUnused_OFFSET          24
#define D0F0xE4_PIF_000A_RxpwrGatingInUnused_WIDTH           1
#define D0F0xE4_PIF_000A_RxpwrGatingInUnused_MASK            0x1000000
#define D0F0xE4_PIF_000A_RxHldEieCount_OFFSET                25
#define D0F0xE4_PIF_000A_RxHldEieCount_WIDTH                 1
#define D0F0xE4_PIF_000A_RxHldEieCount_MASK                  0x2000000
#define D0F0xE4_PIF_000A_RxEiDetInPs2Degrade_OFFSET          26
#define D0F0xE4_PIF_000A_RxEiDetInPs2Degrade_WIDTH           1
#define D0F0xE4_PIF_000A_RxEiDetInPs2Degrade_MASK            0x4000000
#define D0F0xE4_PIF_000A_Reserved_31_27_OFFSET               27
#define D0F0xE4_PIF_000A_Reserved_31_27_WIDTH                5
#define D0F0xE4_PIF_000A_Reserved_31_27_MASK                 0xf8000000

/// D0F0xE4_PIF_000APIF
typedef union {
  struct {                                                              ///<
    UINT32                                                RxpwrInS2:3 ; ///<
    UINT32                                           RxpwrInSpdchng:3 ; ///<
    UINT32                                               RxpwrInOff:3 ; ///<
    UINT32                                           RxpwrInDegrade:3 ; ///<
    UINT32                                            RxpwrInUnused:3 ; ///<
    UINT32                                              RxpwrInInit:3 ; ///<
    UINT32                                            RxpwrInPllOff:3 ; ///<
    UINT32                                       RxpwrInDegradeMode:1 ; ///<
    UINT32                                        RxpwrInUnusedMode:1 ; ///<
    UINT32                                          RxpwrGatingInL1:1 ; ///<
    UINT32                                      RxpwrGatingInUnused:1 ; ///<
    UINT32                                            RxHldEieCount:1 ; ///<
    UINT32                                      RxEiDetInPs2Degrade:1 ; ///<
    UINT32                                           Reserved_31_27:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PIF_000A_STRUCT;

// **** D0F0xE4_PIF_000B Register Definition ****
// Address
#define D0F0xE4_PIF_000B_ADDRESS                                0xB

// Type
#define D0F0xE4_PIF_000B_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PIF_000B_EiDetCycleMode_OFFSET                  17
#define D0F0xE4_PIF_000B_EiDetCycleMode_WIDTH                   2
#define D0F0xE4_PIF_000B_EiDetCycleMode_MASK                    0x60000

// **** D0F0xE4_PHY_000A Register Definition ****
// Address
#define D0F0xE4_PHY_000A_ADDRESS                                0xa

// Type
#define D0F0xE4_PHY_000A_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_000A_adapt_cfg_mode_OFFSET                  0
#define D0F0xE4_PHY_000A_adapt_cfg_mode_WIDTH                   10
#define D0F0xE4_PHY_000A_adapt_cfg_mode_MASK                    0x3ff
#define D0F0xE4_PHY_000A_Reserved_OFFSET                        10
#define D0F0xE4_PHY_000A_Reserved_WIDTH                         3
#define D0F0xE4_PHY_000A_Reserved_MASK                          0x1c00
#define D0F0xE4_PHY_000A_adapt_cfg_track_sel_OFFSET             13
#define D0F0xE4_PHY_000A_adapt_cfg_track_sel_WIDTH              3
#define D0F0xE4_PHY_000A_adapt_cfg_track_sel_MASK               0xe000
#define D0F0xE4_PHY_000A_Reserved16_16_OFFSET                   16
#define D0F0xE4_PHY_000A_Reserved16_16_WIDTH                    1
#define D0F0xE4_PHY_000A_Reserved16_16_MASK                     0x10000
#define D0F0xE4_PHY_000A_adapt_cfg_pwr_save_off_OFFSET          17
#define D0F0xE4_PHY_000A_adapt_cfg_pwr_save_off_WIDTH           1
#define D0F0xE4_PHY_000A_adapt_cfg_pwr_save_off_MASK            0x20000
#define D0F0xE4_PHY_000A_Reserved18_18_OFFSET                   18
#define D0F0xE4_PHY_000A_Reserved18_18_WIDTH                    1
#define D0F0xE4_PHY_000A_Reserved18_18_MASK                     0x40000
#define D0F0xE4_PHY_000A_adapt_cfg_pwr_down_time_sel_OFFSET     19
#define D0F0xE4_PHY_000A_adapt_cfg_pwr_down_time_sel_WIDTH      2
#define D0F0xE4_PHY_000A_adapt_cfg_pwr_down_time_sel_MASK       0x180000
#define D0F0xE4_PHY_000A_Reserved21_31_OFFSET                   21
#define D0F0xE4_PHY_000A_Reserved21_31_WIDTH                    11
#define D0F0xE4_PHY_000A_Reserved21_31_MASK                     0xffe00000

/// D0F0xE4_PHY_000A
typedef union {
  struct {                                                              ///<
    UINT32                                           adapt_cfg_mode:10; ///<
    UINT32                                                 Reserved:3 ; ///<
    UINT32                                      adapt_cfg_track_sel:3 ; ///<
    UINT32                                            Reserved16_16:1 ; ///<
    UINT32                                   adapt_cfg_pwr_save_off:1 ; ///<
    UINT32                                            Reserved18_18:1 ; ///<
    UINT32                              adapt_cfg_pwr_down_time_sel:2 ; ///<
    UINT32                                            Reserved21_31:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_000A_STRUCT;

// **** D0F0xE4_PHY_620A Register Definition ****
// Address
#define D0F0xE4_PHY_620A_ADDRESS                                0x620a

// Type
#define D0F0xE4_PHY_620A_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_620A_adapt_cfg_fom_ber_OFFSET               0
#define D0F0xE4_PHY_620A_adapt_cfg_fom_ber_WIDTH                3
#define D0F0xE4_PHY_620A_adapt_cfg_fom_ber_MASK                 0x7
#define D0F0xE4_PHY_620A_Reserved_OFFSET                        3
#define D0F0xE4_PHY_620A_Reserved_WIDTH                         1
#define D0F0xE4_PHY_620A_Reserved_MASK                          0x8
#define D0F0xE4_PHY_620A_adapt_cfg_oc_time_OFFSET               4
#define D0F0xE4_PHY_620A_adapt_cfg_oc_time_WIDTH                4
#define D0F0xE4_PHY_620A_adapt_cfg_oc_time_MASK                 0xf0
#define D0F0xE4_PHY_620A_Reserved8_8_OFFSET                     8
#define D0F0xE4_PHY_620A_Reserved8_8_WIDTH                      1
#define D0F0xE4_PHY_620A_Reserved8_8_MASK                       0x100
#define D0F0xE4_PHY_620A_adapt_cfg_cdr_time_OFFSET              9
#define D0F0xE4_PHY_620A_adapt_cfg_cdr_time_WIDTH               4
#define D0F0xE4_PHY_620A_adapt_cfg_cdr_time_MASK                0x1e00
#define D0F0xE4_PHY_620A_Reserved13_13_OFFSET                   13
#define D0F0xE4_PHY_620A_Reserved13_13_WIDTH                    1
#define D0F0xE4_PHY_620A_Reserved13_13_MASK                     0x2000
#define D0F0xE4_PHY_620A_adapt_cfg_leq_time_OFFSET              14
#define D0F0xE4_PHY_620A_adapt_cfg_leq_time_WIDTH               4
#define D0F0xE4_PHY_620A_adapt_cfg_leq_time_MASK                0x3c000
#define D0F0xE4_PHY_620A_Reserved18_18_OFFSET                   18
#define D0F0xE4_PHY_620A_Reserved18_18_WIDTH                    1
#define D0F0xE4_PHY_620A_Reserved18_18_MASK                     0x40000
#define D0F0xE4_PHY_620A_adapt_cfg_dfe_time_OFFSET              19
#define D0F0xE4_PHY_620A_adapt_cfg_dfe_time_WIDTH               5
#define D0F0xE4_PHY_620A_adapt_cfg_dfe_time_MASK                0xf80000
#define D0F0xE4_PHY_620A_Reserved24_24_OFFSET                   24
#define D0F0xE4_PHY_620A_Reserved24_24_WIDTH                    1
#define D0F0xE4_PHY_620A_Reserved24_24_MASK                     0x1000000
#define D0F0xE4_PHY_620A_adapt_cfg_fom_time_OFFSET              25
#define D0F0xE4_PHY_620A_adapt_cfg_fom_time_WIDTH               4
#define D0F0xE4_PHY_620A_adapt_cfg_fom_time_MASK                0x1e000000
#define D0F0xE4_PHY_620A_Reserved29_31_OFFSET                   29
#define D0F0xE4_PHY_620A_Reserved29_31_WIDTH                    3
#define D0F0xE4_PHY_620A_Reserved29_31_MASK                     0xe0000000

/// D0F0xE4_PHY_620A
typedef union {
  struct {                                                              ///<
    UINT32                                        adapt_cfg_fom_ber:3 ; ///<
    UINT32                                                 Reserved:1 ; ///<
    UINT32                                        adapt_cfg_oc_time:4 ; ///<
    UINT32                                              Reserved8_8:1 ; ///<
    UINT32                                       adapt_cfg_cdr_time:4 ; ///<
    UINT32                                            Reserved13_13:1 ; ///<
    UINT32                                       adapt_cfg_leq_time:4 ; ///<
    UINT32                                            Reserved18_18:1 ; ///<
    UINT32                                       adapt_cfg_dfe_time:5 ; ///<
    UINT32                                            Reserved24_24:1 ; ///<
    UINT32                                       adapt_cfg_fom_time:4 ; ///<
    UINT32                                            Reserved29_31:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_620A_STRUCT;

// **** D0F0xE4_PHY_620B Register Definition ****
// Address
#define D0F0xE4_PHY_620B_ADDRESS                                0x620b

// Type
#define D0F0xE4_PHY_620B_TYPE                                   TYPE_D0F0xE4
// Field Data
#define D0F0xE4_PHY_620B_adapt_cfg_leq_loop_gain_OFFSET         0
#define D0F0xE4_PHY_620B_adapt_cfg_leq_loop_gain_WIDTH          2
#define D0F0xE4_PHY_620B_adapt_cfg_leq_loop_gain_MASK           0x3
#define D0F0xE4_PHY_620B_Reserved_OFFSET                        2
#define D0F0xE4_PHY_620B_Reserved_WIDTH                         1
#define D0F0xE4_PHY_620B_Reserved_MASK                          0x4
#define D0F0xE4_PHY_620B_adapt_cfg_ofc_loop_gain_OFFSET         3
#define D0F0xE4_PHY_620B_adapt_cfg_ofc_loop_gain_WIDTH          4
#define D0F0xE4_PHY_620B_adapt_cfg_ofc_loop_gain_MASK           0x78
#define D0F0xE4_PHY_620B_Reserved7_7_OFFSET                     7
#define D0F0xE4_PHY_620B_Reserved7_7_WIDTH                      1
#define D0F0xE4_PHY_620B_Reserved7_7_MASK                       0x80
#define D0F0xE4_PHY_620B_adapt_cfg_fom_loop_gain_OFFSET         8
#define D0F0xE4_PHY_620B_adapt_cfg_fom_loop_gain_WIDTH          4
#define D0F0xE4_PHY_620B_adapt_cfg_fom_loop_gain_MASK           0xf00
#define D0F0xE4_PHY_620B_Reserved12_12_OFFSET                   12
#define D0F0xE4_PHY_620B_Reserved12_12_WIDTH                    1
#define D0F0xE4_PHY_620B_Reserved12_12_MASK                     0x1000
#define D0F0xE4_PHY_620B_adapt_cfg_dfe_ref_loop_gain_OFFSET       13
#define D0F0xE4_PHY_620B_adapt_cfg_dfe_ref_loop_gain_WIDTH        4
#define D0F0xE4_PHY_620B_adapt_cfg_dfe_ref_loop_gain_MASK         0x1e000
#define D0F0xE4_PHY_620B_adapt_cfg_dfe_tap_loop_gain_OFFSET       18
#define D0F0xE4_PHY_620B_adapt_cfg_dfe_tap_loop_gain_WIDTH        4
#define D0F0xE4_PHY_620B_adapt_cfg_dfe_tap_loop_gain_MASK         0x3c0000
#define D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_rt_OFFSET       23
#define D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_rt_WIDTH        3
#define D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_rt_MASK         0x3800000
#define D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_lt_OFFSET       27
#define D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_lt_WIDTH        3
#define D0F0xE4_PHY_620B_adapt_cfg_pi_off_range_lt_MASK         0x38000000


/// D0F0xE4_PHY_620B
typedef union {
  struct {                                                              ///<
    UINT32                                  adapt_cfg_leq_loop_gain:2 ; ///<
    UINT32                                                 Reserved:1 ; ///<
    UINT32                                  adapt_cfg_ofc_loop_gain:4 ; ///<
    UINT32                                              Reserved7_7:1 ; ///<
    UINT32                                  adapt_cfg_fom_loop_gain:4 ; ///<
    UINT32                                            Reserved12_12:1 ; ///<
    UINT32                              adapt_cfg_dfe_ref_loop_gain:4 ; ///<
    UINT32                                            Reserved17_17:1 ; ///<
    UINT32                              adapt_cfg_dfe_tap_loop_gain:4 ; ///<
    UINT32                                            Reserved22_22:1 ; ///<
    UINT32                                adapt_cfg_pi_off_range_rt:3 ; ///<
    UINT32                                            Reserved26_26:1 ; ///<
    UINT32                                adapt_cfg_pi_off_range_lt:3 ; ///<
    UINT32                                            Reserved31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_PHY_620B_STRUCT;


// **** D0F0xE4_WRAP_0000 Register Definition ****
// Address
#define D0F0xE4_WRAP_0000_ADDRESS                               0x0

// Type
#define D0F0xE4_WRAP_0000_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0000_Reserved_0_0_OFFSET                   0
#define D0F0xE4_WRAP_0000_Reserved_0_0_WIDTH                    1
#define D0F0xE4_WRAP_0000_Reserved_0_0_MASK                     0x1
#define D0F0xE4_WRAP_0000_StrapBifAerEn_OFFSET                  1
#define D0F0xE4_WRAP_0000_StrapBifAerEn_WIDTH                   1
#define D0F0xE4_WRAP_0000_StrapBifAerEn_MASK                    0x2
#define D0F0xE4_WRAP_0000_StrapBifEcn1p1En_OFFSET               2
#define D0F0xE4_WRAP_0000_StrapBifEcn1p1En_WIDTH                1
#define D0F0xE4_WRAP_0000_StrapBifEcn1p1En_MASK                 0x4
#define D0F0xE4_WRAP_0000_StrapBifGen2Compliance_OFFSET         3
#define D0F0xE4_WRAP_0000_StrapBifGen2Compliance_WIDTH          1
#define D0F0xE4_WRAP_0000_StrapBifGen2Compliance_MASK           0x8
#define D0F0xE4_WRAP_0000_Reserved_4_4_OFFSET                   4
#define D0F0xE4_WRAP_0000_Reserved_4_4_WIDTH                    1
#define D0F0xE4_WRAP_0000_Reserved_4_4_MASK                     0x10
#define D0F0xE4_WRAP_0000_StrapBifEnDecToHiddenReg_OFFSET       5
#define D0F0xE4_WRAP_0000_StrapBifEnDecToHiddenReg_WIDTH        1
#define D0F0xE4_WRAP_0000_StrapBifEnDecToHiddenReg_MASK         0x20
#define D0F0xE4_WRAP_0000_Reserved_8_6_OFFSET                   6
#define D0F0xE4_WRAP_0000_Reserved_8_6_WIDTH                    3
#define D0F0xE4_WRAP_0000_Reserved_8_6_MASK                     0x1c0
#define D0F0xE4_WRAP_0000_StrapBifMstCplTimeoutEn_OFFSET        9
#define D0F0xE4_WRAP_0000_StrapBifMstCplTimeoutEn_WIDTH         1
#define D0F0xE4_WRAP_0000_StrapBifMstCplTimeoutEn_MASK          0x200
#define D0F0xE4_WRAP_0000_Reserved_20_10_OFFSET                 10
#define D0F0xE4_WRAP_0000_Reserved_20_10_WIDTH                  11
#define D0F0xE4_WRAP_0000_Reserved_20_10_MASK                   0x1ffc00
#define D0F0xE4_WRAP_0000_StrapBif2VcEn_OFFSET                  21
#define D0F0xE4_WRAP_0000_StrapBif2VcEn_WIDTH                   1
#define D0F0xE4_WRAP_0000_StrapBif2VcEn_MASK                    0x200000
#define D0F0xE4_WRAP_0000_StrapBif2VcEn_VALUE                   0x0
#define D0F0xE4_WRAP_0000_Reserved_22_22_OFFSET                 22
#define D0F0xE4_WRAP_0000_Reserved_22_22_WIDTH                  1
#define D0F0xE4_WRAP_0000_Reserved_22_22_MASK                   0x400000
#define D0F0xE4_WRAP_0000_StrapBif2AriEn_OFFSET                 23
#define D0F0xE4_WRAP_0000_StrapBif2AriEn_WIDTH                  1
#define D0F0xE4_WRAP_0000_StrapBif2AriEn_MASK                   0x800000
#define D0F0xE4_WRAP_0000_StrapBif2AriEn_VALUE                  0x0
#define D0F0xE4_WRAP_0000_StrapBifAcsEn_OFFSET                  24
#define D0F0xE4_WRAP_0000_StrapBifAcsEn_WIDTH                   1
#define D0F0xE4_WRAP_0000_StrapBifAcsEn_MASK                    0x1000000
#define D0F0xE4_WRAP_0000_StrapBifAcsSourceValidation_OFFSET    25
#define D0F0xE4_WRAP_0000_StrapBifAcsSourceValidation_WIDTH     1
#define D0F0xE4_WRAP_0000_StrapBifAcsSourceValidation_MASK      0x2000000
#define D0F0xE4_WRAP_0000_StrapBifAcsTranslationBlocking_OFFSET 26
#define D0F0xE4_WRAP_0000_StrapBifAcsTranslationBlocking_WIDTH  1
#define D0F0xE4_WRAP_0000_StrapBifAcsTranslationBlocking_MASK   0x4000000
#define D0F0xE4_WRAP_0000_Reserved_27_27_OFFSET                 27
#define D0F0xE4_WRAP_0000_Reserved_27_27_WIDTH                  1
#define D0F0xE4_WRAP_0000_Reserved_27_27_MASK                   0x8000000
#define D0F0xE4_WRAP_0000_StrapBifTlAltBufEn_OFFSET             28
#define D0F0xE4_WRAP_0000_StrapBifTlAltBufEn_WIDTH              1
#define D0F0xE4_WRAP_0000_StrapBifTlAltBufEn_MASK               0x10000000
#define D0F0xE4_WRAP_0000_StrapBifLtrSupported_OFFSET           29
#define D0F0xE4_WRAP_0000_StrapBifLtrSupported_WIDTH            1
#define D0F0xE4_WRAP_0000_StrapBifLtrSupported_MASK             0x20000000
#define D0F0xE4_WRAP_0000_StrapBifObffSupported_OFFSET          30
#define D0F0xE4_WRAP_0000_StrapBifObffSupported_WIDTH           2
#define D0F0xE4_WRAP_0000_StrapBifObffSupported_MASK            0xc0000000

/// D0F0xE4_WRAP_0000
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                            StrapBifAerEn:1 ; ///<
    UINT32                                         StrapBifEcn1p1En:1 ; ///<
    UINT32                                   StrapBifGen2Compliance:1 ; ///<
    UINT32                                             Reserved_4_4:1 ; ///<
    UINT32                                 StrapBifEnDecToHiddenReg:1 ; ///<
    UINT32                                             Reserved_8_6:3 ; ///<
    UINT32                                  StrapBifMstCplTimeoutEn:1 ; ///<
    UINT32                                           Reserved_20_10:11; ///<
    UINT32                                            StrapBif2VcEn:1 ; ///<
    UINT32                                           Reserved_22_22:1 ; ///<
    UINT32                                           StrapBif2AriEn:1 ; ///<
    UINT32                                            StrapBifAcsEn:1 ; ///<
    UINT32                              StrapBifAcsSourceValidation:1 ; ///<
    UINT32                           StrapBifAcsTranslationBlocking:1 ; ///<
    UINT32                                           Reserved_27_27:1 ; ///<
    UINT32                                       StrapBifTlAltBufEn:1 ; ///<
    UINT32                                     StrapBifLtrSupported:1 ; ///<
    UINT32                                    StrapBifObffSupported:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0000_STRUCT;

// **** D0F0xE4_WRAP_0003 Register Definition ****
// Address
#define D0F0xE4_WRAP_0003_ADDRESS                               0x3

// Type
#define D0F0xE4_WRAP_0003_TYPE                                  TYPE_D0F0xE4
// Field Data

/// D0F0xE4_WRAP_0003
typedef union {
  struct {                                                              ///<
    UINT32                                           Reserved_13_0:14 ; ///<
    UINT32                                  STRAP_BIF_ECRC_CHECK_EN:1 ; ///<
    UINT32                                          Reserved_31_15:17 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0003_STRUCT;

// **** D0F0xE4_WRAP_0004 Register Definition ****
// Address
#define D0F0xE4_WRAP_0004_ADDRESS                               0x4

// Type
#define D0F0xE4_WRAP_0004_TYPE                                  TYPE_D0F0xE4
// Field Data

/// D0F0xE4_WRAP_0004
typedef union {
  struct {                                                              ///<
    UINT32                                           Reserved_31_0:32 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0004_STRUCT;

// **** D0F0xE4_WRAP_000A Register Definition ****
// Address
#define D0F0xE4_WRAP_000A_ADDRESS                               0xA

// Type
#define D0F0xE4_WRAP_000A_TYPE                                  TYPE_D0F0xE4
// Field Data

/// D0F0xE4_WRAP_000A
typedef union {
  struct {                                                              ///<
    UINT32                                         STRAP_BIF_ACS_EN:1 ; ///<
    UINT32                          STRAP_BIF_ACS_SOURCE_VALIDATION:1 ; ///<
    UINT32                       STRAP_BIF_ACS_TRANSLATION_BLOCKING:1 ; ///<
    UINT32                                           Reserved_31_3:29 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_000A_STRUCT;

// Type
// Address
#define D0F0xE4_WRAP_0046_ADDRESS                               0x46

// **** D0F0xE4_WRAP_0050 Register Definition ****
// Address
#define D0F0xE4_WRAP_0050_ADDRESS                               0x50

// Type
#define D0F0xE4_WRAP_0050_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlDsPortRxPresetHint_OFFSET 0
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlDsPortRxPresetHint_WIDTH 3
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlDsPortRxPresetHint_MASK 0x7
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlUsPortRxPresetHint_OFFSET 3
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlUsPortRxPresetHint_WIDTH 3
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlUsPortRxPresetHint_MASK 0x38
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlDsPortTxPreset_OFFSET 6
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlDsPortTxPreset_WIDTH 4
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlDsPortTxPreset_MASK 0x3c0
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlUsPortTxPreset_OFFSET 10
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlUsPortTxPreset_WIDTH 4
#define D0F0xE4_WRAP_0050_StrapBifPcieLaneEqCntlUsPortTxPreset_MASK 0x3c00
#define D0F0xE4_WRAP_0050_Reserved_31_14_OFFSET                 14
#define D0F0xE4_WRAP_0050_Reserved_31_14_WIDTH                  18
#define D0F0xE4_WRAP_0050_Reserved_31_14_MASK                   0xffffc000

/// D0F0xE4_WRAP_0050
typedef union {
  struct {                                                              ///<
    UINT32                 StrapBifPcieLaneEqCntlDsPortRxPresetHint:3 ; ///<
    UINT32                 StrapBifPcieLaneEqCntlUsPortRxPresetHint:3 ; ///<
    UINT32                     StrapBifPcieLaneEqCntlDsPortTxPreset:4 ; ///<
    UINT32                     StrapBifPcieLaneEqCntlUsPortTxPreset:4 ; ///<
    UINT32                                           Reserved_31_14:18; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0050_STRUCT;

// **** D0F0xE4_WRAP_0080 Register Definition ****
// Address
#define D0F0xE4_WRAP_0080_ADDRESS                               0x80

// Type
#define D0F0xE4_WRAP_0080_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0080_StrapBifLinkConfig_OFFSET             0
#define D0F0xE4_WRAP_0080_StrapBifLinkConfig_WIDTH              4
#define D0F0xE4_WRAP_0080_StrapBifLinkConfig_MASK               0xf
#define D0F0xE4_WRAP_0080_Reserved_31_4_OFFSET                  4
#define D0F0xE4_WRAP_0080_Reserved_31_4_WIDTH                   28
#define D0F0xE4_WRAP_0080_Reserved_31_4_MASK                    0xfffffff0

/// D0F0xE4_WRAP_0080
typedef union {
  struct {                                                              ///<
    UINT32                                       StrapBifLinkConfig:4 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0080_STRUCT;

// **** D0F0xE4_WRAP_0801 Register Definition ****
// Address
#define D0F0xE4_WRAP_0801_ADDRESS                               0x801

// Type
#define D0F0xE4_WRAP_0801_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_0801_Reserved_6_0_OFFSET                   0
#define D0F0xE4_WRAP_0801_Reserved_6_0_WIDTH                    7
#define D0F0xE4_WRAP_0801_Reserved_6_0_MASK                     0x7f
#define D0F0xE4_WRAP_0801_StrapBifLcBypassEq_OFFSET             7
#define D0F0xE4_WRAP_0801_StrapBifLcBypassEq_WIDTH              1
#define D0F0xE4_WRAP_0801_StrapBifLcBypassEq_MASK               0x80
#define D0F0xE4_WRAP_0801_StrapBifLcBypassEqReqPhase_OFFSET     8
#define D0F0xE4_WRAP_0801_StrapBifLcBypassEqReqPhase_WIDTH      1
#define D0F0xE4_WRAP_0801_StrapBifLcBypassEqReqPhase_MASK       0x100
#define D0F0xE4_WRAP_0801_StrapBifLcEqSearchMode_OFFSET         9
#define D0F0xE4_WRAP_0801_StrapBifLcEqSearchMode_WIDTH          2
#define D0F0xE4_WRAP_0801_StrapBifLcEqSearchMode_MASK           0x600
#define D0F0xE4_WRAP_0801_StrapBifGen3En_OFFSET                 11
#define D0F0xE4_WRAP_0801_StrapBifGen3En_WIDTH                  1
#define D0F0xE4_WRAP_0801_StrapBifGen3En_MASK                   0x800
#define D0F0xE4_WRAP_0801_StrapBifTargetLinkSpeed_OFFSET        12
#define D0F0xE4_WRAP_0801_StrapBifTargetLinkSpeed_WIDTH         2
#define D0F0xE4_WRAP_0801_StrapBifTargetLinkSpeed_MASK          0x3000
#define D0F0xE4_WRAP_0801_Reserved_15_14_OFFSET                 14
#define D0F0xE4_WRAP_0801_Reserved_15_14_WIDTH                  2
#define D0F0xE4_WRAP_0801_Reserved_15_14_MASK                   0xc000
#define D0F0xE4_WRAP_0801_StrapBifLcEqFs_OFFSET                 16
#define D0F0xE4_WRAP_0801_StrapBifLcEqFs_WIDTH                  6
#define D0F0xE4_WRAP_0801_StrapBifLcEqFs_MASK                   0x3f0000
#define D0F0xE4_WRAP_0801_Reserved_23_22_OFFSET                 22
#define D0F0xE4_WRAP_0801_Reserved_23_22_WIDTH                  2
#define D0F0xE4_WRAP_0801_Reserved_23_22_MASK                   0xc00000
#define D0F0xE4_WRAP_0801_StrapBifLcEqLf_OFFSET                 24
#define D0F0xE4_WRAP_0801_StrapBifLcEqLf_WIDTH                  6
#define D0F0xE4_WRAP_0801_StrapBifLcEqLf_MASK                   0x3f000000
#define D0F0xE4_WRAP_0801_Reserved_31_30_OFFSET                 30
#define D0F0xE4_WRAP_0801_Reserved_31_30_WIDTH                  2
#define D0F0xE4_WRAP_0801_Reserved_31_30_MASK                   0xc0000000

/// D0F0xE4_WRAP_0801
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_6_0:7 ; ///<
    UINT32                                       StrapBifLcBypassEq:1 ; ///<
    UINT32                               StrapBifLcBypassEqReqPhase:1 ; ///<
    UINT32                                   StrapBifLcEqSearchMode:2 ; ///<
    UINT32                                           StrapBifGen3En:1 ; ///<
    UINT32                                  StrapBifTargetLinkSpeed:2 ; ///<
    UINT32                                           Reserved_15_14:2 ; ///<
    UINT32                                           StrapBifLcEqFs:6 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                           StrapBifLcEqLf:6 ; ///<
    UINT32                                           Reserved_31_30:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_0801_STRUCT;

// **** D0F0xE4_WRAP_80F1 Register Definition ****
// Address
#define D0F0xE4_WRAP_80F1_ADDRESS                               0x80f1

// Type
#define D0F0xE4_WRAP_80F1_TYPE                                  TYPE_D0F0xE4
// Field Data
#define D0F0xE4_WRAP_80F1_ClockRate_OFFSET                      0
#define D0F0xE4_WRAP_80F1_ClockRate_WIDTH                       8
#define D0F0xE4_WRAP_80F1_ClockRate_MASK                        0xff
#define D0F0xE4_WRAP_80F1_Reserved_31_8_OFFSET                  8
#define D0F0xE4_WRAP_80F1_Reserved_31_8_WIDTH                   24
#define D0F0xE4_WRAP_80F1_Reserved_31_8_MASK                    0xffffff00

/// D0F0xE4_WRAP_80F1
typedef union {
  struct {                                                              ///<
    UINT32                                                ClockRate:8 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xE4_WRAP_80F1_STRUCT;

// **** D0F0xFC_x0F Register Definition ****
// Address
#define D0F0xFC_x0F_ADDRESS                                     0xf

// Type
#define D0F0xFC_x0F_TYPE                                        TYPE_D0F0xFC
// Field Data
#define D0F0xFC_x0F_GBIFExtIntrGrp_OFFSET                       0
#define D0F0xFC_x0F_GBIFExtIntrGrp_WIDTH                        3
#define D0F0xFC_x0F_GBIFExtIntrGrp_MASK                         0x7
#define D0F0xFC_x0F_Reserved_3_3_OFFSET                         3
#define D0F0xFC_x0F_Reserved_3_3_WIDTH                          1
#define D0F0xFC_x0F_Reserved_3_3_MASK                           0x8
#define D0F0xFC_x0F_GBIFExtIntrSwz_OFFSET                       4
#define D0F0xFC_x0F_GBIFExtIntrSwz_WIDTH                        2
#define D0F0xFC_x0F_GBIFExtIntrSwz_MASK                         0x30
#define D0F0xFC_x0F_Reserved_31_6_OFFSET                        6
#define D0F0xFC_x0F_Reserved_31_6_WIDTH                         26
#define D0F0xFC_x0F_Reserved_31_6_MASK                          0xffffffc0

/// D0F0xFC_x0F
typedef union {
  struct {                                                              ///<
    UINT32                                           GBIFExtIntrGrp:3 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                           GBIFExtIntrSwz:2 ; ///<
    UINT32                                            Reserved_31_6:26; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xFC_x0F_STRUCT;

// **** D0F0xFC_x2F Register Definition ****
// Address
#define D0F0xFC_x2F_ADDRESS                                     0x2f

// Type
#define D0F0xFC_x2F_TYPE                                        TYPE_D0F0xFC
// Field Data
#define D0F0xFC_x2F_ApgPortBExtIntrGrp_OFFSET                   0
#define D0F0xFC_x2F_ApgPortBExtIntrGrp_WIDTH                    3
#define D0F0xFC_x2F_ApgPortBExtIntrGrp_MASK                     0x7
#define D0F0xFC_x2F_Reserved_3_3_OFFSET                         3
#define D0F0xFC_x2F_Reserved_3_3_WIDTH                          1
#define D0F0xFC_x2F_Reserved_3_3_MASK                           0x8
#define D0F0xFC_x2F_ApgPortBExtIntrSwz_OFFSET                   4
#define D0F0xFC_x2F_ApgPortBExtIntrSwz_WIDTH                    2
#define D0F0xFC_x2F_ApgPortBExtIntrSwz_MASK                     0x30
#define D0F0xFC_x2F_Reserved_7_6_OFFSET                         6
#define D0F0xFC_x2F_Reserved_7_6_WIDTH                          2
#define D0F0xFC_x2F_Reserved_7_6_MASK                           0xc0
#define D0F0xFC_x2F_ApgPortAExtIntrGrp_OFFSET                   8
#define D0F0xFC_x2F_ApgPortAExtIntrGrp_WIDTH                    3
#define D0F0xFC_x2F_ApgPortAExtIntrGrp_MASK                     0x700
#define D0F0xFC_x2F_Reserved_11_11_OFFSET                       11
#define D0F0xFC_x2F_Reserved_11_11_WIDTH                        1
#define D0F0xFC_x2F_Reserved_11_11_MASK                         0x800
#define D0F0xFC_x2F_ApgPortAExtIntrSwz_OFFSET                   12
#define D0F0xFC_x2F_ApgPortAExtIntrSwz_WIDTH                    2
#define D0F0xFC_x2F_ApgPortAExtIntrSwz_MASK                     0x3000
#define D0F0xFC_x2F_Reserved_31_14_OFFSET                       14
#define D0F0xFC_x2F_Reserved_31_14_WIDTH                        18
#define D0F0xFC_x2F_Reserved_31_14_MASK                         0xffffc000

/// D0F0xFC_x2F
typedef union {
  struct {                                                              ///<
    UINT32                                       ApgPortBExtIntrGrp:3 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                       ApgPortBExtIntrSwz:2 ; ///<
    UINT32                                             Reserved_7_6:2 ; ///<
    UINT32                                       ApgPortAExtIntrGrp:3 ; ///<
    UINT32                                           Reserved_11_11:1 ; ///<
    UINT32                                       ApgPortAExtIntrSwz:2 ; ///<
    UINT32                                           Reserved_31_14:18; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xFC_x2F_STRUCT;

// **** D0F0xFC_x30 Register Definition ****
// Address
#define D0F0xFC_x30_ADDRESS                                     0x30

// Type
#define D0F0xFC_x30_TYPE                                        TYPE_D0F0xFC
// Field Data
#define D0F0xFC_x30_SpgExtIntrGrp_OFFSET                        0
#define D0F0xFC_x30_SpgExtIntrGrp_WIDTH                         3
#define D0F0xFC_x30_SpgExtIntrGrp_MASK                          0x7
#define D0F0xFC_x30_Reserved_3_3_OFFSET                         3
#define D0F0xFC_x30_Reserved_3_3_WIDTH                          1
#define D0F0xFC_x30_Reserved_3_3_MASK                           0x8
#define D0F0xFC_x30_SpgExtIntrSwz_OFFSET                        4
#define D0F0xFC_x30_SpgExtIntrSwz_WIDTH                         2
#define D0F0xFC_x30_SpgExtIntrSwz_MASK                          0x30
#define D0F0xFC_x30_Reserved_31_6_OFFSET                        6
#define D0F0xFC_x30_Reserved_31_6_WIDTH                         26
#define D0F0xFC_x30_Reserved_31_6_MASK                          0xffffffc0

/// D0F0xFC_x30
typedef union {
  struct {                                                              ///<
    UINT32                                            SpgExtIntrGrp:3 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                            SpgExtIntrSwz:2 ; ///<
    UINT32                                            Reserved_31_6:26; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xFC_x30_STRUCT;

// **** DxFxx60 Register Definition ****
// Address
#define DxFxx60_ADDRESS                                         0x60

// Type
#define DxFxx60_TYPE                                            TYPE_D2F1
// Field Data
#define DxFxx60_CorrErrEn_OFFSET                                0
#define DxFxx60_CorrErrEn_WIDTH                                 1
#define DxFxx60_CorrErrEn_MASK                                  0x1
#define DxFxx60_NonFatalErrEn_OFFSET                            1
#define DxFxx60_NonFatalErrEn_WIDTH                             1
#define DxFxx60_NonFatalErrEn_MASK                              0x2
#define DxFxx60_FatalErrEn_OFFSET                               2
#define DxFxx60_FatalErrEn_WIDTH                                1
#define DxFxx60_FatalErrEn_MASK                                 0x4
#define DxFxx60_UsrReportEn_OFFSET                              3
#define DxFxx60_UsrReportEn_WIDTH                               1
#define DxFxx60_UsrReportEn_MASK                                0x8
#define DxFxx60_RelaxedOrdEn_OFFSET                             4
#define DxFxx60_RelaxedOrdEn_WIDTH                              1
#define DxFxx60_RelaxedOrdEn_MASK                               0x10
#define DxFxx60_MaxPayloadSize_OFFSET                           5
#define DxFxx60_MaxPayloadSize_WIDTH                            3
#define DxFxx60_MaxPayloadSize_MASK                             0xe0
#define DxFxx60_ExtendedTagEn_OFFSET                            8
#define DxFxx60_ExtendedTagEn_WIDTH                             1
#define DxFxx60_ExtendedTagEn_MASK                              0x100
#define DxFxx60_PhantomFuncEn_OFFSET                            9
#define DxFxx60_PhantomFuncEn_WIDTH                             1
#define DxFxx60_PhantomFuncEn_MASK                              0x200
#define DxFxx60_AuxPowerPmEn_OFFSET                             10
#define DxFxx60_AuxPowerPmEn_WIDTH                              1
#define DxFxx60_AuxPowerPmEn_MASK                               0x400
#define DxFxx60_NoSnoopEnable_OFFSET                            11
#define DxFxx60_NoSnoopEnable_WIDTH                             1
#define DxFxx60_NoSnoopEnable_MASK                              0x800
#define DxFxx60_MaxRequestSize_OFFSET                           12
#define DxFxx60_MaxRequestSize_WIDTH                            3
#define DxFxx60_MaxRequestSize_MASK                             0x7000
#define DxFxx60_InitiateFlr_OFFSET                              15
#define DxFxx60_InitiateFlr_WIDTH                               1
#define DxFxx60_InitiateFlr_MASK                                0x8000
#define DxFxx60_CorrErr_OFFSET                                  16
#define DxFxx60_CorrErr_WIDTH                                   1
#define DxFxx60_CorrErr_MASK                                    0x10000
#define DxFxx60_NonFatalErr_OFFSET                              17
#define DxFxx60_NonFatalErr_WIDTH                               1
#define DxFxx60_NonFatalErr_MASK                                0x20000
#define DxFxx60_FatalErr_OFFSET                                 18
#define DxFxx60_FatalErr_WIDTH                                  1
#define DxFxx60_FatalErr_MASK                                   0x40000
#define DxFxx60_UsrDetected_OFFSET                              19
#define DxFxx60_UsrDetected_WIDTH                               1
#define DxFxx60_UsrDetected_MASK                                0x80000
#define DxFxx60_AuxPwr_OFFSET                                   20
#define DxFxx60_AuxPwr_WIDTH                                    1
#define DxFxx60_AuxPwr_MASK                                     0x100000
#define DxFxx60_TransactionsPending_OFFSET                      21
#define DxFxx60_TransactionsPending_WIDTH                       1
#define DxFxx60_TransactionsPending_MASK                        0x200000
#define DxFxx60_Reserved_31_22_OFFSET                           22
#define DxFxx60_Reserved_31_22_WIDTH                            10
#define DxFxx60_Reserved_31_22_MASK                             0xffc00000

/// DxFxx60
typedef union {
  struct {                                                              ///<
    UINT32                                                CorrErrEn:1 ; ///<
    UINT32                                            NonFatalErrEn:1 ; ///<
    UINT32                                               FatalErrEn:1 ; ///<
    UINT32                                              UsrReportEn:1 ; ///<
    UINT32                                             RelaxedOrdEn:1 ; ///<
    UINT32                                           MaxPayloadSize:3 ; ///<
    UINT32                                            ExtendedTagEn:1 ; ///<
    UINT32                                            PhantomFuncEn:1 ; ///<
    UINT32                                             AuxPowerPmEn:1 ; ///<
    UINT32                                            NoSnoopEnable:1 ; ///<
    UINT32                                           MaxRequestSize:3 ; ///<
    UINT32                                              InitiateFlr:1 ; ///<
    UINT32                                                  CorrErr:1 ; ///<
    UINT32                                              NonFatalErr:1 ; ///<
    UINT32                                                 FatalErr:1 ; ///<
    UINT32                                              UsrDetected:1 ; ///<
    UINT32                                                   AuxPwr:1 ; ///<
    UINT32                                      TransactionsPending:1 ; ///<
    UINT32                                           Reserved_31_22:10; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx60_STRUCT;

// **** DxFxx6C Register Definition ****
// Address
#define DxFxx6C_ADDRESS                                         0x6c

// Type
#define DxFxx6C_TYPE                                            TYPE_DxF0
// Field Data
#define DxFxx6C_AttnButtonPresent_OFFSET                        0
#define DxFxx6C_AttnButtonPresent_WIDTH                         1
#define DxFxx6C_AttnButtonPresent_MASK                          0x1
#define DxFxx6C_PwrControllerPresent_OFFSET                     1
#define DxFxx6C_PwrControllerPresent_WIDTH                      1
#define DxFxx6C_PwrControllerPresent_MASK                       0x2
#define DxFxx6C_MrlSensorPresent_OFFSET                         2
#define DxFxx6C_MrlSensorPresent_WIDTH                          1
#define DxFxx6C_MrlSensorPresent_MASK                           0x4
#define DxFxx6C_AttnIndicatorPresent_OFFSET                     3
#define DxFxx6C_AttnIndicatorPresent_WIDTH                      1
#define DxFxx6C_AttnIndicatorPresent_MASK                       0x8
#define DxFxx6C_PwrIndicatorPresent_OFFSET                      4
#define DxFxx6C_PwrIndicatorPresent_WIDTH                       1
#define DxFxx6C_PwrIndicatorPresent_MASK                        0x10
#define DxFxx6C_HotplugSurprise_OFFSET                          5
#define DxFxx6C_HotplugSurprise_WIDTH                           1
#define DxFxx6C_HotplugSurprise_MASK                            0x20
#define DxFxx6C_HotplugCapable_OFFSET                           6
#define DxFxx6C_HotplugCapable_WIDTH                            1
#define DxFxx6C_HotplugCapable_MASK                             0x40
#define DxFxx6C_SlotPwrLimitValue_OFFSET                        7
#define DxFxx6C_SlotPwrLimitValue_WIDTH                         8
#define DxFxx6C_SlotPwrLimitValue_MASK                          0x7f80
#define DxFxx6C_SlotPwrLimitScale_OFFSET                        15
#define DxFxx6C_SlotPwrLimitScale_WIDTH                         2
#define DxFxx6C_SlotPwrLimitScale_MASK                          0x18000
#define DxFxx6C_ElecMechIlPresent_OFFSET                        17
#define DxFxx6C_ElecMechIlPresent_WIDTH                         1
#define DxFxx6C_ElecMechIlPresent_MASK                          0x20000
#define DxFxx6C_NoCmdCplSupport_OFFSET                          18
#define DxFxx6C_NoCmdCplSupport_WIDTH                           1
#define DxFxx6C_NoCmdCplSupport_MASK                            0x40000
#define DxFxx6C_PhysicalSlotNumber_OFFSET                       19
#define DxFxx6C_PhysicalSlotNumber_WIDTH                        13
#define DxFxx6C_PhysicalSlotNumber_MASK                         0xfff80000

/// DxFxx6C
typedef union {
  struct {                                                              ///<
    UINT32                                        AttnButtonPresent:1 ; ///<
    UINT32                                     PwrControllerPresent:1 ; ///<
    UINT32                                         MrlSensorPresent:1 ; ///<
    UINT32                                     AttnIndicatorPresent:1 ; ///<
    UINT32                                      PwrIndicatorPresent:1 ; ///<
    UINT32                                          HotplugSurprise:1 ; ///<
    UINT32                                           HotplugCapable:1 ; ///<
    UINT32                                        SlotPwrLimitValue:8 ; ///<
    UINT32                                        SlotPwrLimitScale:2 ; ///<
    UINT32                                        ElecMechIlPresent:1 ; ///<
    UINT32                                          NoCmdCplSupport:1 ; ///<
    UINT32                                       PhysicalSlotNumber:13; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx6C_STRUCT;

// **** DxFxx74 Register Definition ****
// Address
#define DxFxx74_ADDRESS                                         0x74

// Type
#define DxFxx74_TYPE                                            TYPE_D2F1
// Field Data
#define DxFxx74_SerrOnCorrErrEn_OFFSET                          0
#define DxFxx74_SerrOnCorrErrEn_WIDTH                           1
#define DxFxx74_SerrOnCorrErrEn_MASK                            0x1
#define DxFxx74_SerrOnNonFatalErrEn_OFFSET                      1
#define DxFxx74_SerrOnNonFatalErrEn_WIDTH                       1
#define DxFxx74_SerrOnNonFatalErrEn_MASK                        0x2
#define DxFxx74_SerrOnFatalErrEn_OFFSET                         2
#define DxFxx74_SerrOnFatalErrEn_WIDTH                          1
#define DxFxx74_SerrOnFatalErrEn_MASK                           0x4
#define DxFxx74_PmIntEn_OFFSET                                  3
#define DxFxx74_PmIntEn_WIDTH                                   1
#define DxFxx74_PmIntEn_MASK                                    0x8
#define DxFxx74_CrsSoftVisibilityEn_OFFSET                      4
#define DxFxx74_CrsSoftVisibilityEn_WIDTH                       1
#define DxFxx74_CrsSoftVisibilityEn_MASK                        0x10
#define DxFxx74_Reserved_15_5_OFFSET                            5
#define DxFxx74_Reserved_15_5_WIDTH                             11
#define DxFxx74_Reserved_15_5_MASK                              0xffe0
#define DxFxx74_CrsSoftVisibility_OFFSET                        16
#define DxFxx74_CrsSoftVisibility_WIDTH                         1
#define DxFxx74_CrsSoftVisibility_MASK                          0x10000
#define DxFxx74_Reserved_31_17_OFFSET                           17
#define DxFxx74_Reserved_31_17_WIDTH                            15
#define DxFxx74_Reserved_31_17_MASK                             0xfffe0000

/// DxFxx74
typedef union {
  struct {                                                              ///<
    UINT32                                          SerrOnCorrErrEn:1 ; ///<
    UINT32                                      SerrOnNonFatalErrEn:1 ; ///<
    UINT32                                         SerrOnFatalErrEn:1 ; ///<
    UINT32                                                  PmIntEn:1 ; ///<
    UINT32                                      CrsSoftVisibilityEn:1 ; ///<
    UINT32                                            Reserved_15_5:11; ///<
    UINT32                                        CrsSoftVisibility:1 ; ///<
    UINT32                                           Reserved_31_17:15; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx74_STRUCT;

// **** DxFxxE0 Register Definition ****
// Address
#define DxFxxE0_ADDRESS                                         0xe0

// Type
#define DxFxxE0_TYPE                                            TYPE_D2F1

// **** DxFxx158 Register Definition ****
// Address
#define DxFxx158_ADDRESS                                        0x158

// Type
#define DxFxx158_TYPE                                           TYPE_D2F1
// Field Data
#define DxFxx158_Reserved_3_0_OFFSET                            0
#define DxFxx158_Reserved_3_0_WIDTH                             4
#define DxFxx158_Reserved_3_0_MASK                              0xf
#define DxFxx158_DlpErrMask_OFFSET                              4
#define DxFxx158_DlpErrMask_WIDTH                               1
#define DxFxx158_DlpErrMask_MASK                                0x10
#define DxFxx158_SurprdnErrMask_OFFSET                          5
#define DxFxx158_SurprdnErrMask_WIDTH                           1
#define DxFxx158_SurprdnErrMask_MASK                            0x20
#define DxFxx158_Reserved_11_6_OFFSET                           6
#define DxFxx158_Reserved_11_6_WIDTH                            6
#define DxFxx158_Reserved_11_6_MASK                             0xfc0
#define DxFxx158_PsnErrMask_OFFSET                              12
#define DxFxx158_PsnErrMask_WIDTH                               1
#define DxFxx158_PsnErrMask_MASK                                0x1000
#define DxFxx158_FcErrMask_OFFSET                               13
#define DxFxx158_FcErrMask_WIDTH                                1
#define DxFxx158_FcErrMask_MASK                                 0x2000
#define DxFxx158_CplTimeoutMask_OFFSET                          14
#define DxFxx158_CplTimeoutMask_WIDTH                           1
#define DxFxx158_CplTimeoutMask_MASK                            0x4000
#define DxFxx158_CplAbortErrMask_OFFSET                         15
#define DxFxx158_CplAbortErrMask_WIDTH                          1
#define DxFxx158_CplAbortErrMask_MASK                           0x8000
#define DxFxx158_UnexpCplMask_OFFSET                            16
#define DxFxx158_UnexpCplMask_WIDTH                             1
#define DxFxx158_UnexpCplMask_MASK                              0x10000
#define DxFxx158_RcvOvflMask_OFFSET                             17
#define DxFxx158_RcvOvflMask_WIDTH                              1
#define DxFxx158_RcvOvflMask_MASK                               0x20000
#define DxFxx158_MalTlpMask_OFFSET                              18
#define DxFxx158_MalTlpMask_WIDTH                               1
#define DxFxx158_MalTlpMask_MASK                                0x40000
#define DxFxx158_EcrcErrMask_OFFSET                             19
#define DxFxx158_EcrcErrMask_WIDTH                              1
#define DxFxx158_EcrcErrMask_MASK                               0x80000
#define DxFxx158_UnsuppReqErrMask_OFFSET                        20
#define DxFxx158_UnsuppReqErrMask_WIDTH                         1
#define DxFxx158_UnsuppReqErrMask_MASK                          0x100000
#define DxFxx158_AcsViolationMask_OFFSET                        21
#define DxFxx158_AcsViolationMask_WIDTH                         1
#define DxFxx158_AcsViolationMask_MASK                          0x200000
#define DxFxx158_UncorrInteralErrMask_OFFSET                    22
#define DxFxx158_UncorrInteralErrMask_WIDTH                     1
#define DxFxx158_UncorrInteralErrMask_MASK                      0x400000
#define DxFxx158_McBlockedTLPMask_OFFSET                        23
#define DxFxx158_McBlockedTLPMask_WIDTH                         1
#define DxFxx158_McBlockedTLPMask_MASK                          0x800000
#define DxFxx158_AtomicOpEgressBlockedTLPMask_OFFSET            24
#define DxFxx158_AtomicOpEgressBlockedTLPMask_WIDTH             1
#define DxFxx158_AtomicOpEgressBlockedTLPMask_MASK              0x1000000
#define DxFxx158_TlpPrefixMask_OFFSET                           25
#define DxFxx158_TlpPrefixMask_WIDTH                            1
#define DxFxx158_TlpPrefixMask_MASK                             0x2000000
#define DxFxx158_Reserved_31_26_OFFSET                          26
#define DxFxx158_Reserved_31_26_WIDTH                           6
#define DxFxx158_Reserved_31_26_MASK                            0xfc000000

/// DxFxx158
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_3_0:4 ; ///<
    UINT32                                               DlpErrMask:1 ; ///<
    UINT32                                           SurprdnErrMask:1 ; ///<
    UINT32                                            Reserved_11_6:6 ; ///<
    UINT32                                               PsnErrMask:1 ; ///<
    UINT32                                                FcErrMask:1 ; ///<
    UINT32                                           CplTimeoutMask:1 ; ///<
    UINT32                                          CplAbortErrMask:1 ; ///<
    UINT32                                             UnexpCplMask:1 ; ///<
    UINT32                                              RcvOvflMask:1 ; ///<
    UINT32                                               MalTlpMask:1 ; ///<
    UINT32                                              EcrcErrMask:1 ; ///<
    UINT32                                         UnsuppReqErrMask:1 ; ///<
    UINT32                                         AcsViolationMask:1 ; ///<
    UINT32                                     UncorrInteralErrMask:1 ; ///<
    UINT32                                         McBlockedTLPMask:1 ; ///<
    UINT32                             AtomicOpEgressBlockedTLPMask:1 ; ///<
    UINT32                                            TlpPrefixMask:1 ; ///<
    UINT32                                           Reserved_31_26:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx158_STRUCT;

// **** DxFxx15C Register Definition ****
// Address
#define DxFxx15C_ADDRESS                                        0x15c

// Type
#define DxFxx15C_TYPE                                           TYPE_D2F1
// Field Data
#define DxFxx15C_Reserved_3_0_OFFSET                            0
#define DxFxx15C_Reserved_3_0_WIDTH                             4
#define DxFxx15C_Reserved_3_0_MASK                              0xf
#define DxFxx15C_DlpErrSeverity_OFFSET                          4
#define DxFxx15C_DlpErrSeverity_WIDTH                           1
#define DxFxx15C_DlpErrSeverity_MASK                            0x10
#define DxFxx15C_SurprdnErrSeverity_OFFSET                      5
#define DxFxx15C_SurprdnErrSeverity_WIDTH                       1
#define DxFxx15C_SurprdnErrSeverity_MASK                        0x20
#define DxFxx15C_Reserved_11_6_OFFSET                           6
#define DxFxx15C_Reserved_11_6_WIDTH                            6
#define DxFxx15C_Reserved_11_6_MASK                             0xfc0
#define DxFxx15C_PsnErrSeverity_OFFSET                          12
#define DxFxx15C_PsnErrSeverity_WIDTH                           1
#define DxFxx15C_PsnErrSeverity_MASK                            0x1000
#define DxFxx15C_FcErrSeverity_OFFSET                           13
#define DxFxx15C_FcErrSeverity_WIDTH                            1
#define DxFxx15C_FcErrSeverity_MASK                             0x2000
#define DxFxx15C_CplTimeoutSeverity_OFFSET                      14
#define DxFxx15C_CplTimeoutSeverity_WIDTH                       1
#define DxFxx15C_CplTimeoutSeverity_MASK                        0x4000
#define DxFxx15C_CplAbortErrSeverity_OFFSET                     15
#define DxFxx15C_CplAbortErrSeverity_WIDTH                      1
#define DxFxx15C_CplAbortErrSeverity_MASK                       0x8000
#define DxFxx15C_UnexpCplSeverity_OFFSET                        16
#define DxFxx15C_UnexpCplSeverity_WIDTH                         1
#define DxFxx15C_UnexpCplSeverity_MASK                          0x10000
#define DxFxx15C_RcvOvflSeverity_OFFSET                         17
#define DxFxx15C_RcvOvflSeverity_WIDTH                          1
#define DxFxx15C_RcvOvflSeverity_MASK                           0x20000
#define DxFxx15C_MalTlpSeverity_OFFSET                          18
#define DxFxx15C_MalTlpSeverity_WIDTH                           1
#define DxFxx15C_MalTlpSeverity_MASK                            0x40000
#define DxFxx15C_EcrcErrSeverity_OFFSET                         19
#define DxFxx15C_EcrcErrSeverity_WIDTH                          1
#define DxFxx15C_EcrcErrSeverity_MASK                           0x80000
#define DxFxx15C_UnsuppReqErrSeverity_OFFSET                    20
#define DxFxx15C_UnsuppReqErrSeverity_WIDTH                     1
#define DxFxx15C_UnsuppReqErrSeverity_MASK                      0x100000
#define DxFxx15C_AcsViolationSeverity_OFFSET                    21
#define DxFxx15C_AcsViolationSeverity_WIDTH                     1
#define DxFxx15C_AcsViolationSeverity_MASK                      0x200000
#define DxFxx15C_UncorrInteralErrSeverity_OFFSET                22
#define DxFxx15C_UncorrInteralErrSeverity_WIDTH                 1
#define DxFxx15C_UncorrInteralErrSeverity_MASK                  0x400000
#define DxFxx15C_McBlockedTLPSeverity_OFFSET                    23
#define DxFxx15C_McBlockedTLPSeverity_WIDTH                     1
#define DxFxx15C_McBlockedTLPSeverity_MASK                      0x800000
#define DxFxx15C_AtomicOpEgressBlockedTLPSeverity_OFFSET        24
#define DxFxx15C_AtomicOpEgressBlockedTLPSeverity_WIDTH         1
#define DxFxx15C_AtomicOpEgressBlockedTLPSeverity_MASK          0x1000000
#define DxFxx15C_TlpPrefixSeverity_OFFSET                       25
#define DxFxx15C_TlpPrefixSeverity_WIDTH                        1
#define DxFxx15C_TlpPrefixSeverity_MASK                         0x2000000
#define DxFxx15C_Reserved_31_26_OFFSET                          26
#define DxFxx15C_Reserved_31_26_WIDTH                           6
#define DxFxx15C_Reserved_31_26_MASK                            0xfc000000

/// DxFxx15C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_3_0:4 ; ///<
    UINT32                                           DlpErrSeverity:1 ; ///<
    UINT32                                       SurprdnErrSeverity:1 ; ///<
    UINT32                                            Reserved_11_6:6 ; ///<
    UINT32                                           PsnErrSeverity:1 ; ///<
    UINT32                                            FcErrSeverity:1 ; ///<
    UINT32                                       CplTimeoutSeverity:1 ; ///<
    UINT32                                      CplAbortErrSeverity:1 ; ///<
    UINT32                                         UnexpCplSeverity:1 ; ///<
    UINT32                                          RcvOvflSeverity:1 ; ///<
    UINT32                                           MalTlpSeverity:1 ; ///<
    UINT32                                          EcrcErrSeverity:1 ; ///<
    UINT32                                     UnsuppReqErrSeverity:1 ; ///<
    UINT32                                     AcsViolationSeverity:1 ; ///<
    UINT32                                 UncorrInteralErrSeverity:1 ; ///<
    UINT32                                     McBlockedTLPSeverity:1 ; ///<
    UINT32                         AtomicOpEgressBlockedTLPSeverity:1 ; ///<
    UINT32                                        TlpPrefixSeverity:1 ; ///<
    UINT32                                           Reserved_31_26:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx15C_STRUCT;
// **** DxFxx164 Register Definition ****
// Address
#define DxFxx164_ADDRESS                                        0x164

// Type
#define DxFxx164_TYPE                                           TYPE_D2F1
// Field Data
#define DxFxx164_RcvErrMask_OFFSET                              0
#define DxFxx164_RcvErrMask_WIDTH                               1
#define DxFxx164_RcvErrMask_MASK                                0x1
#define DxFxx164_Reserved_5_1_OFFSET                            1
#define DxFxx164_Reserved_5_1_WIDTH                             5
#define DxFxx164_Reserved_5_1_MASK                              0x3e
#define DxFxx164_BadTlpMask_OFFSET                              6
#define DxFxx164_BadTlpMask_WIDTH                               1
#define DxFxx164_BadTlpMask_MASK                                0x40
#define DxFxx164_BadDllpMask_OFFSET                             7
#define DxFxx164_BadDllpMask_WIDTH                              1
#define DxFxx164_BadDllpMask_MASK                               0x80
#define DxFxx164_ReplayNumRolloverMask_OFFSET                   8
#define DxFxx164_ReplayNumRolloverMask_WIDTH                    1
#define DxFxx164_ReplayNumRolloverMask_MASK                     0x100
#define DxFxx164_Reserved_11_9_OFFSET                           9
#define DxFxx164_Reserved_11_9_WIDTH                            3
#define DxFxx164_Reserved_11_9_MASK                             0xe00
#define DxFxx164_ReplayTimerTimeoutMask_OFFSET                  12
#define DxFxx164_ReplayTimerTimeoutMask_WIDTH                   1
#define DxFxx164_ReplayTimerTimeoutMask_MASK                    0x1000
#define DxFxx164_AdvisoryNonfatalErrMask_OFFSET                 13
#define DxFxx164_AdvisoryNonfatalErrMask_WIDTH                  1
#define DxFxx164_AdvisoryNonfatalErrMask_MASK                   0x2000
#define DxFxx164_CorrIntErrMask_OFFSET                          14
#define DxFxx164_CorrIntErrMask_WIDTH                           1
#define DxFxx164_CorrIntErrMask_MASK                            0x4000
#define DxFxx164_HdrLogOvflMask_OFFSET                          15
#define DxFxx164_HdrLogOvflMask_WIDTH                           1
#define DxFxx164_HdrLogOvflMask_MASK                            0x8000
#define DxFxx164_Reserved_31_16_OFFSET                          16
#define DxFxx164_Reserved_31_16_WIDTH                           16
#define DxFxx164_Reserved_31_16_MASK                            0xffff0000

/// DxFxx164
typedef union {
  struct {                                                              ///<
    UINT32                                               RcvErrMask:1 ; ///<
    UINT32                                             Reserved_5_1:5 ; ///<
    UINT32                                               BadTlpMask:1 ; ///<
    UINT32                                              BadDllpMask:1 ; ///<
    UINT32                                    ReplayNumRolloverMask:1 ; ///<
    UINT32                                            Reserved_11_9:3 ; ///<
    UINT32                                   ReplayTimerTimeoutMask:1 ; ///<
    UINT32                                  AdvisoryNonfatalErrMask:1 ; ///<
    UINT32                                           CorrIntErrMask:1 ; ///<
    UINT32                                           HdrLogOvflMask:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx164_STRUCT;

// **** DxFxx168 Register Definition ****
// Address
#define DxFxx168_ADDRESS                                        0x168

// Type
#define DxFxx168_TYPE                                           TYPE_D2F1
// Field Data
#define DxFxx168_FirstErrPtr_OFFSET                             0
#define DxFxx168_FirstErrPtr_WIDTH                              5
#define DxFxx168_FirstErrPtr_MASK                               0x1f
#define DxFxx168_EcrcGenCap_OFFSET                              5
#define DxFxx168_EcrcGenCap_WIDTH                               1
#define DxFxx168_EcrcGenCap_MASK                                0x20
#define DxFxx168_EcrcGenEn_OFFSET                               6
#define DxFxx168_EcrcGenEn_WIDTH                                1
#define DxFxx168_EcrcGenEn_MASK                                 0x40
#define DxFxx168_EcrcCheckCap_OFFSET                            7
#define DxFxx168_EcrcCheckCap_WIDTH                             1
#define DxFxx168_EcrcCheckCap_MASK                              0x80
#define DxFxx168_EcrcCheckEn_OFFSET                             8
#define DxFxx168_EcrcCheckEn_WIDTH                              1
#define DxFxx168_EcrcCheckEn_MASK                               0x100
#define DxFxx168_MultiHdrRecdCap_OFFSET                         9
#define DxFxx168_MultiHdrRecdCap_WIDTH                          1
#define DxFxx168_MultiHdrRecdCap_MASK                           0x200
#define DxFxx168_MultiHdrRecdEn_OFFSET                          10
#define DxFxx168_MultiHdrRecdEn_WIDTH                           1
#define DxFxx168_MultiHdrRecdEn_MASK                            0x400
#define DxFxx168_TlpPrefixLogPresent_OFFSET                     11
#define DxFxx168_TlpPrefixLogPresent_WIDTH                      1
#define DxFxx168_TlpPrefixLogPresent_MASK                       0x800
#define DxFxx168_Reserved_31_12_OFFSET                          12
#define DxFxx168_Reserved_31_12_WIDTH                           20
#define DxFxx168_Reserved_31_12_MASK                            0xfffff000

/// DxFxx168
typedef union {
  struct {                                                              ///<
    UINT32                                              FirstErrPtr:5 ; ///<
    UINT32                                               EcrcGenCap:1 ; ///<
    UINT32                                                EcrcGenEn:1 ; ///<
    UINT32                                             EcrcCheckCap:1 ; ///<
    UINT32                                              EcrcCheckEn:1 ; ///<
    UINT32                                          MultiHdrRecdCap:1 ; ///<
    UINT32                                           MultiHdrRecdEn:1 ; ///<
    UINT32                                      TlpPrefixLogPresent:1 ; ///<
    UINT32                                           Reserved_31_12:20; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx168_STRUCT;

// **** DxFxx17C Register Definition ****
// Address
#define DxFxx17C_ADDRESS                                        0x17c

// Type
#define DxFxx17C_TYPE                                           TYPE_D2F1
// Field Data
#define DxFxx17C_CorrErrRepEn_OFFSET                            0
#define DxFxx17C_CorrErrRepEn_WIDTH                             1
#define DxFxx17C_CorrErrRepEn_MASK                              0x1
#define DxFxx17C_NonfatalErrRepEn_OFFSET                        1
#define DxFxx17C_NonfatalErrRepEn_WIDTH                         1
#define DxFxx17C_NonfatalErrRepEn_MASK                          0x2
#define DxFxx17C_FatalErrRepEn_OFFSET                           2
#define DxFxx17C_FatalErrRepEn_WIDTH                            1
#define DxFxx17C_FatalErrRepEn_MASK                             0x4
#define DxFxx17C_Reserved_31_3_OFFSET                           3
#define DxFxx17C_Reserved_31_3_WIDTH                            29
#define DxFxx17C_Reserved_31_3_MASK                             0xfffffff8

/// DxFxx17C
typedef union {
  struct {                                                              ///<
    UINT32                                             CorrErrRepEn:1 ; ///<
    UINT32                                         NonfatalErrRepEn:1 ; ///<
    UINT32                                            FatalErrRepEn:1 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx17C_STRUCT;

// **** DxFxx2A6 Register Definition ****
// Address
#define DxFxx2A6_ADDRESS                                        0x2a4

// Type
#define DxFxx2A6_TYPE                                           TYPE_D2F1
// Field Data
#define DxFxx2A6_Reserved_15_0_OFFSET                           0
#define DxFxx2A6_Reserved_15_0_WIDTH                            16
#define DxFxx2A6_Reserved_15_0_MASK                             0xffff
#define DxFxx2A6_SourceValidationEn_OFFSET                      16
#define DxFxx2A6_SourceValidationEn_WIDTH                       1
#define DxFxx2A6_SourceValidationEn_MASK                        0x10000
#define DxFxx2A6_TranslationBlockingEn_OFFSET                   17
#define DxFxx2A6_TranslationBlockingEn_WIDTH                    1
#define DxFxx2A6_TranslationBlockingEn_MASK                     0x20000
#define DxFxx2A6_P2pRequestRedirectEn_OFFSET                    18
#define DxFxx2A6_P2pRequestRedirectEn_WIDTH                     1
#define DxFxx2A6_P2pRequestRedirectEn_MASK                      0x40000
#define DxFxx2A6_P2pCompletionRedirectEn_OFFSET                 19
#define DxFxx2A6_P2pCompletionRedirectEn_WIDTH                  1
#define DxFxx2A6_P2pCompletionRedirectEn_MASK                   0x80000
#define DxFxx2A6_UpstreamForwardingEn_OFFSET                    20
#define DxFxx2A6_UpstreamForwardingEn_WIDTH                     1
#define DxFxx2A6_UpstreamForwardingEn_MASK                      0x100000
#define DxFxx2A6_P2pEgressControlEn_OFFSET                      21
#define DxFxx2A6_P2pEgressControlEn_WIDTH                       1
#define DxFxx2A6_P2pEgressControlEn_MASK                        0x200000
#define DxFxx2A6_DirectTranslatedP2pEn_OFFSET                   22
#define DxFxx2A6_DirectTranslatedP2pEn_WIDTH                    1
#define DxFxx2A6_DirectTranslatedP2pEn_MASK                     0x400000
#define DxFxx2A6_Reserved_31_23_OFFSET                          23
#define DxFxx2A6_Reserved_31_23_WIDTH                           9
#define DxFxx2A6_Reserved_31_23_MASK                            0xff800000

/// DxFxx2A6
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_15_0:16; ///<
    UINT32                                       SourceValidationEn:1 ; ///<
    UINT32                                    TranslationBlockingEn:1 ; ///<
    UINT32                                     P2pRequestRedirectEn:1 ; ///<
    UINT32                                  P2pCompletionRedirectEn:1 ; ///<
    UINT32                                     UpstreamForwardingEn:1 ; ///<
    UINT32                                       P2pEgressControlEn:1 ; ///<
    UINT32                                    DirectTranslatedP2pEn:1 ; ///<
    UINT32                                           Reserved_31_23:9 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxx2A6_STRUCT;

// **** DxFxxE4_x01 Register Definition ****
// Address
#define DxFxxE4_x01_ADDRESS                                     0x1
// Type
#define DxFxxE4_x01_TYPE                                        TYPE_D2F1xE4

// **** DxFxxE4_x10 Register Definition ****
// Address
#define DxFxxE4_x10_ADDRESS                                     0x10

// Type
#define DxFxxE4_x10_TYPE                                        TYPE_D2F1xE4
// Field Data

#define DxFxxE4_x10_Reserved_2_0_OFFSET                         0
#define DxFxxE4_x10_Reserved_2_0_WIDTH                          3
#define DxFxxE4_x10_Reserved_2_0_MASK                           0x7
#define DxFxxE4_x10_NativePmeEn_OFFSET                          3
#define DxFxxE4_x10_NativePmeEn_WIDTH                           1
#define DxFxxE4_x10_NativePmeEn_MASK                            0x8
#define DxFxxE4_x10_Reserved_31_4_OFFSET                        4
#define DxFxxE4_x10_Reserved_31_4_WIDTH                         28
#define DxFxxE4_x10_Reserved_31_4_MASK                          0xfffffff0

// **** DxFxxE4_x20 Register Definition ****
// Address
#define DxFxxE4_x20_ADDRESS                                     0x20

// Type
#define DxFxxE4_x20_TYPE                                        TYPE_D2F1xE4
// Field Data
#define DxFxxE4_x20_Reserved_14_0_OFFSET                        0
#define DxFxxE4_x20_Reserved_14_0_WIDTH                         15
#define DxFxxE4_x20_Reserved_14_0_MASK                          0x7fff
#define DxFxxE4_x20_TxFlushTlpDis_OFFSET                        15
#define DxFxxE4_x20_TxFlushTlpDis_WIDTH                         1
#define DxFxxE4_x20_TxFlushTlpDis_MASK                          0x8000
#define DxFxxE4_x20_Reserved_31_16_OFFSET                       16
#define DxFxxE4_x20_Reserved_31_16_WIDTH                        16
#define DxFxxE4_x20_Reserved_31_16_MASK                         0xffff0000

/// DxFxxE4_x20
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_14_0:15; ///<
    UINT32                                            TxFlushTlpDis:1 ; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_x20_STRUCT;

// **** DxFxxE4_x6A Register Definition ****
// Address
#define DxFxxE4_x6A_ADDRESS                                     0x6a

// Type
#define DxFxxE4_x6A_TYPE                                        TYPE_D2F1xE4
// Field Data
#define DxFxxE4_x6A_ErrReportingDis_OFFSET                      0
#define DxFxxE4_x6A_ErrReportingDis_WIDTH                       1
#define DxFxxE4_x6A_ErrReportingDis_MASK                        0x1
#define DxFxxE4_x6A_ErrReportingDis_VALUE                       0x0
#define DxFxxE4_x6A_StrapFirstRcvdErrLog_OFFSET                 1
#define DxFxxE4_x6A_StrapFirstRcvdErrLog_WIDTH                  1
#define DxFxxE4_x6A_StrapFirstRcvdErrLog_MASK                   0x2
#define DxFxxE4_x6A_RxDropEcrcFailures_OFFSET                   2
#define DxFxxE4_x6A_RxDropEcrcFailures_WIDTH                    1
#define DxFxxE4_x6A_RxDropEcrcFailures_MASK                     0x4
#define DxFxxE4_x6A_Reserved_3_3_OFFSET                         3
#define DxFxxE4_x6A_Reserved_3_3_WIDTH                          1
#define DxFxxE4_x6A_Reserved_3_3_MASK                           0x8
#define DxFxxE4_x6A_TxGenerateLcrcErr_OFFSET                    4
#define DxFxxE4_x6A_TxGenerateLcrcErr_WIDTH                     1
#define DxFxxE4_x6A_TxGenerateLcrcErr_MASK                      0x10
#define DxFxxE4_x6A_RxGenerateLcrcErr_OFFSET                    5
#define DxFxxE4_x6A_RxGenerateLcrcErr_WIDTH                     1
#define DxFxxE4_x6A_RxGenerateLcrcErr_MASK                      0x20
#define DxFxxE4_x6A_TxGenerateEcrcErr_OFFSET                    6
#define DxFxxE4_x6A_TxGenerateEcrcErr_WIDTH                     1
#define DxFxxE4_x6A_TxGenerateEcrcErr_MASK                      0x40
#define DxFxxE4_x6A_RxGenerateEcrcErr_OFFSET                    7
#define DxFxxE4_x6A_RxGenerateEcrcErr_WIDTH                     1
#define DxFxxE4_x6A_RxGenerateEcrcErr_MASK                      0x80
#define DxFxxE4_x6A_AerHdrLogTimeout_OFFSET                     8
#define DxFxxE4_x6A_AerHdrLogTimeout_WIDTH                      3
#define DxFxxE4_x6A_AerHdrLogTimeout_MASK                       0x700
#define DxFxxE4_x6A_AerHdrLogF0TimerExpire1_OFFSET              11
#define DxFxxE4_x6A_AerHdrLogF0TimerExpire1_WIDTH               1
#define DxFxxE4_x6A_AerHdrLogF0TimerExpire1_MASK                0x800
#define DxFxxE4_x6A_Reserved_13_12_OFFSET                       12
#define DxFxxE4_x6A_Reserved_13_12_WIDTH                        2
#define DxFxxE4_x6A_Reserved_13_12_MASK                         0x3000
#define DxFxxE4_x6A_CiPSlvBufRdHaltStatus_OFFSET                14
#define DxFxxE4_x6A_CiPSlvBufRdHaltStatus_WIDTH                 1
#define DxFxxE4_x6A_CiPSlvBufRdHaltStatus_MASK                  0x4000
#define DxFxxE4_x6A_CiNpSlvBufRdHaltStatus_OFFSET               15
#define DxFxxE4_x6A_CiNpSlvBufRdHaltStatus_WIDTH                1
#define DxFxxE4_x6A_CiNpSlvBufRdHaltStatus_MASK                 0x8000
#define DxFxxE4_x6A_CiSlvBufHaltReset_OFFSET                    16
#define DxFxxE4_x6A_CiSlvBufHaltReset_WIDTH                     1
#define DxFxxE4_x6A_CiSlvBufHaltReset_MASK                      0x10000
#define DxFxxE4_x6A_SendErrMsgImmediately_OFFSET                17
#define DxFxxE4_x6A_SendErrMsgImmediately_WIDTH                 1
#define DxFxxE4_x6A_SendErrMsgImmediately_MASK                  0x20000
#define DxFxxE4_x6A_StrapPoisonedAdvisoryNonfatal_OFFSET        18
#define DxFxxE4_x6A_StrapPoisonedAdvisoryNonfatal_WIDTH         1
#define DxFxxE4_x6A_StrapPoisonedAdvisoryNonfatal_MASK          0x40000
#define DxFxxE4_x6A_Reserved_31_19_OFFSET                       19
#define DxFxxE4_x6A_Reserved_31_19_WIDTH                        13
#define DxFxxE4_x6A_Reserved_31_19_MASK                         0xfff80000

/// DxFxxE4_x6A
typedef union {
  struct {                                                              ///<
    UINT32                                          ErrReportingDis:1 ; ///<
    UINT32                                     StrapFirstRcvdErrLog:1 ; ///<
    UINT32                                       RxDropEcrcFailures:1 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                        TxGenerateLcrcErr:1 ; ///<
    UINT32                                        RxGenerateLcrcErr:1 ; ///<
    UINT32                                        TxGenerateEcrcErr:1 ; ///<
    UINT32                                        RxGenerateEcrcErr:1 ; ///<
    UINT32                                         AerHdrLogTimeout:3 ; ///<
    UINT32                                  AerHdrLogF0TimerExpire1:1 ; ///<
    UINT32                                           Reserved_13_12:2 ; ///<
    UINT32                                    CiPSlvBufRdHaltStatus:1 ; ///<
    UINT32                                   CiNpSlvBufRdHaltStatus:1 ; ///<
    UINT32                                        CiSlvBufHaltReset:1 ; ///<
    UINT32                                    SendErrMsgImmediately:1 ; ///<
    UINT32                            StrapPoisonedAdvisoryNonfatal:1 ; ///<
    UINT32                                           Reserved_31_19:13; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_x6A_STRUCT;

// **** DxFxxE4_x70 Register Definition ****
// Address
#define DxFxxE4_x70_ADDRESS                                     0x70
// Type
#define DxFxxE4_x70_TYPE                                        TYPE_D2F1xE4

// Field Data
#define DxFxxE4_x70_Reserved_15_0_OFFSET                        0
#define DxFxxE4_x70_Reserved_15_0_WIDTH                         16
#define DxFxxE4_x70_Reserved_15_0_MASK                          0xFFFF
#define DxFxxE4_x70_RxRcbCplTimeout_OFFSET                      16
#define DxFxxE4_x70_RxRcbCplTimeout_WIDTH                       3
#define DxFxxE4_x70_RxRcbCplTimeout_MASK                        0x70000
#define DxFxxE4_x70_RxRcbCplTimeoutMode_OFFSET                  19
#define DxFxxE4_x70_RxRcbCplTimeoutMode_WIDTH                   1
#define DxFxxE4_x70_RxRcbCplTimeoutMode_MASK                    0x80000
#define DxFxxE4_x70_Reserved_31_20_OFFSET                       20
#define DxFxxE4_x70_Reserved_31_20_WIDTH                        12
#define DxFxxE4_x70_Reserved_31_20_MASK                         0xFFF00000

/// DxFxxE4_x70
typedef union {
  struct {                                                            ///<
    UINT32                                           Reserved_15_0:16; ///<
    UINT32                                         RxRcbCplTimeout:3; ///<
    UINT32                                     RxRcbCplTimeoutMode:1; ///<
    UINT32                                          Reserved_31_20:12; ///<

  } Field;

  UINT32 Value;
} DxFxxE4_x70_STRUCT;

// **** DxFxxE4_xA0 Register Definition ****
// Address
#define DxFxxE4_xA0_ADDRESS                                     0xa0

// Type
#define DxFxxE4_xA0_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xA0_Reserved_0_0_OFFSET                         0
#define DxFxxE4_xA0_Reserved_0_0_WIDTH                          1
#define DxFxxE4_xA0_Reserved_0_0_MASK                           0x1
#define DxFxxE4_xA0_LcDontEnterL23InD0_OFFSET                   1
#define DxFxxE4_xA0_LcDontEnterL23InD0_WIDTH                    1
#define DxFxxE4_xA0_LcDontEnterL23InD0_MASK                     0x2
#define DxFxxE4_xA0_LcResetlIdleCountEn_OFFSET                  2
#define DxFxxE4_xA0_LcResetlIdleCountEn_WIDTH                   1
#define DxFxxE4_xA0_LcResetlIdleCountEn_MASK                    0x4
#define DxFxxE4_xA0_LcResetLink_OFFSET                          3
#define DxFxxE4_xA0_LcResetLink_WIDTH                           1
#define DxFxxE4_xA0_LcResetLink_MASK                            0x8
#define DxFxxE4_xA0_Lc16xClearTxPipe_OFFSET                     4
#define DxFxxE4_xA0_Lc16xClearTxPipe_WIDTH                      4
#define DxFxxE4_xA0_Lc16xClearTxPipe_MASK                       0xf0
#define DxFxxE4_xA0_Lc16xClearTxPipe_VALUE                      0x3
#define DxFxxE4_xA0_LcL0sInactivity_OFFSET                      8
#define DxFxxE4_xA0_LcL0sInactivity_WIDTH                       4
#define DxFxxE4_xA0_LcL0sInactivity_MASK                        0xf00
#define DxFxxE4_xA0_LcL1Inactivity_OFFSET                       12
#define DxFxxE4_xA0_LcL1Inactivity_WIDTH                        4
#define DxFxxE4_xA0_LcL1Inactivity_MASK                         0xf000
#define DxFxxE4_xA0_LcPmiToL1Dis_OFFSET                         16
#define DxFxxE4_xA0_LcPmiToL1Dis_WIDTH                          1
#define DxFxxE4_xA0_LcPmiToL1Dis_MASK                           0x10000
#define DxFxxE4_xA0_LcIncNFtsEn_OFFSET                          17
#define DxFxxE4_xA0_LcIncNFtsEn_WIDTH                           1
#define DxFxxE4_xA0_LcIncNFtsEn_MASK                            0x20000
#define DxFxxE4_xA0_LcLookForIdleInL1L23_OFFSET                 18
#define DxFxxE4_xA0_LcLookForIdleInL1L23_WIDTH                  2
#define DxFxxE4_xA0_LcLookForIdleInL1L23_MASK                   0xc0000
#define DxFxxE4_xA0_LcFactorInExtSync_OFFSET                    20
#define DxFxxE4_xA0_LcFactorInExtSync_WIDTH                     1
#define DxFxxE4_xA0_LcFactorInExtSync_MASK                      0x100000
#define DxFxxE4_xA0_LcWaitForPmAckDis_OFFSET                    21
#define DxFxxE4_xA0_LcWaitForPmAckDis_WIDTH                     1
#define DxFxxE4_xA0_LcWaitForPmAckDis_MASK                      0x200000
#define DxFxxE4_xA0_LcWakeFromL23_OFFSET                        22
#define DxFxxE4_xA0_LcWakeFromL23_WIDTH                         1
#define DxFxxE4_xA0_LcWakeFromL23_MASK                          0x400000
#define DxFxxE4_xA0_LcL1ImmediateAck_OFFSET                     23
#define DxFxxE4_xA0_LcL1ImmediateAck_WIDTH                      1
#define DxFxxE4_xA0_LcL1ImmediateAck_MASK                       0x800000
#define DxFxxE4_xA0_LcL1ImmediateAck_VALUE                      0x1
#define DxFxxE4_xA0_LcAspmToL1Dis_OFFSET                        24
#define DxFxxE4_xA0_LcAspmToL1Dis_WIDTH                         1
#define DxFxxE4_xA0_LcAspmToL1Dis_MASK                          0x1000000
#define DxFxxE4_xA0_LcDelayCount_OFFSET                         25
#define DxFxxE4_xA0_LcDelayCount_WIDTH                          2
#define DxFxxE4_xA0_LcDelayCount_MASK                           0x6000000
#define DxFxxE4_xA0_LcDelayL0sExit_OFFSET                       27
#define DxFxxE4_xA0_LcDelayL0sExit_WIDTH                        1
#define DxFxxE4_xA0_LcDelayL0sExit_MASK                         0x8000000
#define DxFxxE4_xA0_LcDelayL1Exit_OFFSET                        28
#define DxFxxE4_xA0_LcDelayL1Exit_WIDTH                         1
#define DxFxxE4_xA0_LcDelayL1Exit_MASK                          0x10000000
#define DxFxxE4_xA0_LcExtendWaitForElIdle_OFFSET                29
#define DxFxxE4_xA0_LcExtendWaitForElIdle_WIDTH                 1
#define DxFxxE4_xA0_LcExtendWaitForElIdle_MASK                  0x20000000
#define DxFxxE4_xA0_LcEscapeL1L23En_OFFSET                      30
#define DxFxxE4_xA0_LcEscapeL1L23En_WIDTH                       1
#define DxFxxE4_xA0_LcEscapeL1L23En_MASK                        0x40000000
#define DxFxxE4_xA0_LcGateRcvrIdle_OFFSET                       31
#define DxFxxE4_xA0_LcGateRcvrIdle_WIDTH                        1
#define DxFxxE4_xA0_LcGateRcvrIdle_MASK                         0x80000000

/// DxFxxE4_xA0
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                       LcDontEnterL23InD0:1 ; ///<
    UINT32                                      LcResetlIdleCountEn:1 ; ///<
    UINT32                                              LcResetLink:1 ; ///<
    UINT32                                         Lc16xClearTxPipe:4 ; ///<
    UINT32                                          LcL0sInactivity:4 ; ///<
    UINT32                                           LcL1Inactivity:4 ; ///<
    UINT32                                             LcPmiToL1Dis:1 ; ///<
    UINT32                                              LcIncNFtsEn:1 ; ///<
    UINT32                                     LcLookForIdleInL1L23:2 ; ///<
    UINT32                                        LcFactorInExtSync:1 ; ///<
    UINT32                                        LcWaitForPmAckDis:1 ; ///<
    UINT32                                            LcWakeFromL23:1 ; ///<
    UINT32                                         LcL1ImmediateAck:1 ; ///<
    UINT32                                            LcAspmToL1Dis:1 ; ///<
    UINT32                                             LcDelayCount:2 ; ///<
    UINT32                                           LcDelayL0sExit:1 ; ///<
    UINT32                                            LcDelayL1Exit:1 ; ///<
    UINT32                                    LcExtendWaitForElIdle:1 ; ///<
    UINT32                                          LcEscapeL1L23En:1 ; ///<
    UINT32                                           LcGateRcvrIdle:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xA0_STRUCT;

// **** DxFxxE4_xA1 Register Definition ****
// Address
#define DxFxxE4_xA1_ADDRESS                                     0xA1
// Type
#define DxFxxE4_xA1_TYPE                                        TYPE_D2F1xE4

// Field Data
#define DxFxxE4_xA1_Reserved_10_0_OFFSET                        0
#define DxFxxE4_xA1_Reserved_10_0_WIDTH                         11
#define DxFxxE4_xA1_Reserved_10_0_MASK                          0x7FF
#define DxFxxE4_xA1_LcDontGotoL0sifL1Armed_OFFSET               11
#define DxFxxE4_xA1_LcDontGotoL0sifL1Armed_WIDTH                1
#define DxFxxE4_xA1_LcDontGotoL0sifL1Armed_MASK                 0x800
#define DxFxxE4_xA1_Reserved_31_12_OFFSET                       12
#define DxFxxE4_xA1_Reserved_31_12_WIDTH                        4
#define DxFxxE4_xA1_Reserved_31_12_MASK                         0xF000
#define DxFxxE4_xA1_LcExtendWaitForSkp_OFFSET                   16
#define DxFxxE4_xA1_LcExtendWaitForSkp_WIDTH                    1
#define DxFxxE4_xA1_LcExtendWaitForSkp_MASK                     0x10000
#define DxFxxE4_xA1_Reserved_31_17_OFFSET                       17
#define DxFxxE4_xA1_Reserved_31_17_WIDTH                        15
#define DxFxxE4_xA1_Reserved_31_17_MASK                         0xFFFE0000

/// DxFxxE4_xA1
typedef union {
  struct {                                                            ///<
    UINT32                                           Reserved_10_0:11; ///<
    UINT32                                  LcDontGotoL0sifL1Armed:1 ; ///<
    UINT32                                          Reserved_15_12:4 ; ///<
    UINT32                                      LcExtendWaitForSkp:1 ; ///<
    UINT32                                          Reserved_31_17:15; ///<
  } Field;

  UINT32 Value;
} DxFxxE4_xA1_STRUCT;

// **** DxFxxE4_xA2 Register Definition ****
// Address
#define DxFxxE4_xA2_ADDRESS                                     0xA2
// Type
#define DxFxxE4_xA2_TYPE                                        TYPE_D2F1xE4

// Field Data
#define DxFxxE4_xA2_LcLinkWidth_OFFSET                          0
#define DxFxxE4_xA2_LcLinkWidth_WIDTH                           3
#define DxFxxE4_xA2_LcLinkWidth_MASK                            0x7
#define DxFxxE4_xA2_Reserved_3_3_OFFSET                         3
#define DxFxxE4_xA2_Reserved_3_3_WIDTH                          1
#define DxFxxE4_xA2_Reserved_3_3_MASK                           0x8
#define DxFxxE4_xA2_LcLinkWidthRd_OFFSET                        4
#define DxFxxE4_xA2_LcLinkWidthRd_WIDTH                         3
#define DxFxxE4_xA2_LcLinkWidthRd_MASK                          0x70
#define DxFxxE4_xA2_LcReconfigArcMissingEscape_OFFSET           7
#define DxFxxE4_xA2_LcReconfigArcMissingEscape_WIDTH            1
#define DxFxxE4_xA2_LcReconfigArcMissingEscape_MASK             0x80
#define DxFxxE4_xA2_LcReconfigNow_OFFSET                        8
#define DxFxxE4_xA2_LcReconfigNow_WIDTH                         1
#define DxFxxE4_xA2_LcReconfigNow_MASK                          0x100
#define DxFxxE4_xA2_LcRenegotiationSupport_OFFSET               9
#define DxFxxE4_xA2_LcRenegotiationSupport_WIDTH                1
#define DxFxxE4_xA2_LcRenegotiationSupport_MASK                 0x200
#define DxFxxE4_xA2_LcRenegotiateEn_OFFSET                      10
#define DxFxxE4_xA2_LcRenegotiateEn_WIDTH                       1
#define DxFxxE4_xA2_LcRenegotiateEn_MASK                        0x400
#define DxFxxE4_xA2_LcShortReconfigEn_OFFSET                    11
#define DxFxxE4_xA2_LcShortReconfigEn_WIDTH                     1
#define DxFxxE4_xA2_LcShortReconfigEn_MASK                      0x800
#define DxFxxE4_xA2_LcUpconfigureSupport_OFFSET                 12
#define DxFxxE4_xA2_LcUpconfigureSupport_WIDTH                  1
#define DxFxxE4_xA2_LcUpconfigureSupport_MASK                   0x1000
#define DxFxxE4_xA2_LcUpconfigureDis_OFFSET                     13
#define DxFxxE4_xA2_LcUpconfigureDis_WIDTH                      1
#define DxFxxE4_xA2_LcUpconfigureDis_MASK                       0x2000
#define DxFxxE4_xA2_Reserved_19_14_OFFSET                       14
#define DxFxxE4_xA2_Reserved_19_14_WIDTH                        6
#define DxFxxE4_xA2_Reserved_19_14_MASK                         0xFC000
#define DxFxxE4_xA2_LcUpconfigCapable_OFFSET                    20
#define DxFxxE4_xA2_LcUpconfigCapable_WIDTH                     1
#define DxFxxE4_xA2_LcUpconfigCapable_MASK                      0x100000
#define DxFxxE4_xA2_LcDynLanesPwrState_OFFSET                   21
#define DxFxxE4_xA2_LcDynLanesPwrState_WIDTH                    2
#define DxFxxE4_xA2_LcDynLanesPwrState_MASK                     0x600000
#define DxFxxE4_xA2_Reserved_31_23_OFFSET                       23
#define DxFxxE4_xA2_Reserved_31_23_WIDTH                        9
#define DxFxxE4_xA2_Reserved_31_23_MASK                         0xFF800000

/// DxFxxE4_xA2
typedef union {
  struct {                                                            ///<
    UINT32                                             LcLinkWidth:3; ///<
    UINT32                                            Reserved_3_3:1; ///<
    UINT32                                           LcLinkWidthRd:3; ///<
    UINT32                              LcReconfigArcMissingEscape:1; ///<
    UINT32                                           LcReconfigNow:1; ///<
    UINT32                                  LcRenegotiationSupport:1; ///<
    UINT32                                         LcRenegotiateEn:1; ///<
    UINT32                                       LcShortReconfigEn:1; ///<
    UINT32                                    LcUpconfigureSupport:1; ///<
    UINT32                                        LcUpconfigureDis:1; ///<
    UINT32                                          Reserved_19_14:6; ///<
    UINT32                                       LcUpconfigCapable:1; ///<
    UINT32                                      LcDynLanesPwrState:2; ///<
    UINT32                                          Reserved_31_23:9; ///<

  } Field;

  UINT32 Value;
} DxFxxE4_xA2_STRUCT;

// **** DxFxxE4_xA3 Register Definition ****
// Address
#define DxFxxE4_xA3_ADDRESS                                     0xa3

// Type
#define DxFxxE4_xA3_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xA3_LcXmitNFts_OFFSET                           0
#define DxFxxE4_xA3_LcXmitNFts_WIDTH                            8
#define DxFxxE4_xA3_LcXmitNFts_MASK                             0xff
#define DxFxxE4_xA3_LcXmitNFtsOverrideEn_OFFSET                 8
#define DxFxxE4_xA3_LcXmitNFtsOverrideEn_WIDTH                  1
#define DxFxxE4_xA3_LcXmitNFtsOverrideEn_MASK                   0x100
#define DxFxxE4_xA3_LcXmitFtsBeforeRecovery_OFFSET              9
#define DxFxxE4_xA3_LcXmitFtsBeforeRecovery_WIDTH               1
#define DxFxxE4_xA3_LcXmitFtsBeforeRecovery_MASK                0x200
#define DxFxxE4_xA3_Reserved_15_10_OFFSET                       10
#define DxFxxE4_xA3_Reserved_15_10_WIDTH                        6
#define DxFxxE4_xA3_Reserved_15_10_MASK                         0xfc00
#define DxFxxE4_xA3_LcXmitNFtsLimit_OFFSET                      16
#define DxFxxE4_xA3_LcXmitNFtsLimit_WIDTH                       8
#define DxFxxE4_xA3_LcXmitNFtsLimit_MASK                        0xff0000
#define DxFxxE4_xA3_LcNFts_OFFSET                               24
#define DxFxxE4_xA3_LcNFts_WIDTH                                8
#define DxFxxE4_xA3_LcNFts_MASK                                 0xff000000

/// DxFxxE4_xA3
typedef union {
  struct {                                                              ///<
    UINT32                                               LcXmitNFts:8 ; ///<
    UINT32                                     LcXmitNFtsOverrideEn:1 ; ///<
    UINT32                                  LcXmitFtsBeforeRecovery:1 ; ///<
    UINT32                                           Reserved_15_10:6 ; ///<
    UINT32                                          LcXmitNFtsLimit:8 ; ///<
    UINT32                                                   LcNFts:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xA3_STRUCT;

// **** DxFxxE4_xB1 Register Definition ****
// Address
#define DxFxxE4_xB1_ADDRESS                                     0xb1

// Type
#define DxFxxE4_xB1_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xB1_LcTimedOutState_OFFSET                      0
#define DxFxxE4_xB1_LcTimedOutState_WIDTH                       6
#define DxFxxE4_xB1_LcTimedOutState_MASK                        0x3f
#define DxFxxE4_xB1_LcTimedOut_OFFSET                           6
#define DxFxxE4_xB1_LcTimedOut_WIDTH                            1
#define DxFxxE4_xB1_LcTimedOut_MASK                             0x40
#define DxFxxE4_xB1_LcLookForBwReduction_OFFSET                 7
#define DxFxxE4_xB1_LcLookForBwReduction_WIDTH                  1
#define DxFxxE4_xB1_LcLookForBwReduction_MASK                   0x80
#define DxFxxE4_xB1_LcMoreTs2En_OFFSET                          8
#define DxFxxE4_xB1_LcMoreTs2En_WIDTH                           1
#define DxFxxE4_xB1_LcMoreTs2En_MASK                            0x100
#define DxFxxE4_xB1_LcX12NegotiationDis_OFFSET                  9
#define DxFxxE4_xB1_LcX12NegotiationDis_WIDTH                   1
#define DxFxxE4_xB1_LcX12NegotiationDis_MASK                    0x200
#define DxFxxE4_xB1_LcLinkUpReversalEn_OFFSET                   10
#define DxFxxE4_xB1_LcLinkUpReversalEn_WIDTH                    1
#define DxFxxE4_xB1_LcLinkUpReversalEn_MASK                     0x400
#define DxFxxE4_xB1_LcIllegalState_OFFSET                       11
#define DxFxxE4_xB1_LcIllegalState_WIDTH                        1
#define DxFxxE4_xB1_LcIllegalState_MASK                         0x800
#define DxFxxE4_xB1_LcIllegalStateRestartEn_OFFSET              12
#define DxFxxE4_xB1_LcIllegalStateRestartEn_WIDTH               1
#define DxFxxE4_xB1_LcIllegalStateRestartEn_MASK                0x1000
#define DxFxxE4_xB1_LcWaitForOtherLanesMode_OFFSET              13
#define DxFxxE4_xB1_LcWaitForOtherLanesMode_WIDTH               1
#define DxFxxE4_xB1_LcWaitForOtherLanesMode_MASK                0x2000
#define DxFxxE4_xB1_LcElecIdleMode_OFFSET                       14
#define DxFxxE4_xB1_LcElecIdleMode_WIDTH                        2
#define DxFxxE4_xB1_LcElecIdleMode_MASK                         0xc000
#define DxFxxE4_xB1_LcDisableInferredElecIdleDetect_OFFSET      16
#define DxFxxE4_xB1_LcDisableInferredElecIdleDetect_WIDTH       1
#define DxFxxE4_xB1_LcDisableInferredElecIdleDetect_MASK        0x10000
#define DxFxxE4_xB1_Reserved_18_17_OFFSET                       17
#define DxFxxE4_xB1_Reserved_18_17_WIDTH                        2
#define DxFxxE4_xB1_Reserved_18_17_MASK                         0x60000
#define DxFxxE4_xB1_LcDeassertRxEnInL0s_OFFSET                  19
#define DxFxxE4_xB1_LcDeassertRxEnInL0s_WIDTH                   1
#define DxFxxE4_xB1_LcDeassertRxEnInL0s_MASK                    0x80000
#define DxFxxE4_xB1_LcBlockElIdleinL0_OFFSET                    20
#define DxFxxE4_xB1_LcBlockElIdleinL0_WIDTH                     1
#define DxFxxE4_xB1_LcBlockElIdleinL0_MASK                      0x100000
#define DxFxxE4_xB1_LcBlockElIdleinL0_VALUE                     0x1
#define DxFxxE4_xB1_LcRcvL0toRcvL0sDis_OFFSET                   21
#define DxFxxE4_xB1_LcRcvL0toRcvL0sDis_WIDTH                    1
#define DxFxxE4_xB1_LcRcvL0toRcvL0sDis_MASK                     0x200000
#define DxFxxE4_xB1_LcAssertInactiveDuringHold_OFFSET           22
#define DxFxxE4_xB1_LcAssertInactiveDuringHold_WIDTH            1
#define DxFxxE4_xB1_LcAssertInactiveDuringHold_MASK             0x400000
#define DxFxxE4_xB1_LcWaitForLanesInLwNeg_OFFSET                23
#define DxFxxE4_xB1_LcWaitForLanesInLwNeg_WIDTH                 2
#define DxFxxE4_xB1_LcWaitForLanesInLwNeg_MASK                  0x1800000
#define DxFxxE4_xB1_LcPwrDownNegOffLanes_OFFSET                 25
#define DxFxxE4_xB1_LcPwrDownNegOffLanes_WIDTH                  1
#define DxFxxE4_xB1_LcPwrDownNegOffLanes_MASK                   0x2000000
#define DxFxxE4_xB1_LcDisableLostSymLockArcs_OFFSET             26
#define DxFxxE4_xB1_LcDisableLostSymLockArcs_WIDTH              1
#define DxFxxE4_xB1_LcDisableLostSymLockArcs_MASK               0x4000000
#define DxFxxE4_xB1_LcLinkBwNotificationDis_OFFSET              27
#define DxFxxE4_xB1_LcLinkBwNotificationDis_WIDTH               1
#define DxFxxE4_xB1_LcLinkBwNotificationDis_MASK                0x8000000
#define DxFxxE4_xB1_Reserved_28_28_OFFSET                       28
#define DxFxxE4_xB1_Reserved_28_28_WIDTH                        1
#define DxFxxE4_xB1_Reserved_28_28_MASK                         0x10000000
#define DxFxxE4_xB1_LcTestTimerSel_OFFSET                       29
#define DxFxxE4_xB1_LcTestTimerSel_WIDTH                        2
#define DxFxxE4_xB1_LcTestTimerSel_MASK                         0x60000000
#define DxFxxE4_xB1_ElecIdleForPi_OFFSET                        31
#define DxFxxE4_xB1_ElecIdleForPi_WIDTH                         1
#define DxFxxE4_xB1_ElecIdleForPi_MASK                          0x80000000

/// DxFxxE4_xB1
typedef union {
  struct {                                                              ///<
    UINT32                                          LcTimedOutState:6 ; ///<
    UINT32                                               LcTimedOut:1 ; ///<
    UINT32                                     LcLookForBwReduction:1 ; ///<
    UINT32                                              LcMoreTs2En:1 ; ///<
    UINT32                                      LcX12NegotiationDis:1 ; ///<
    UINT32                                       LcLinkUpReversalEn:1 ; ///<
    UINT32                                           LcIllegalState:1 ; ///<
    UINT32                                  LcIllegalStateRestartEn:1 ; ///<
    UINT32                                  LcWaitForOtherLanesMode:1 ; ///<
    UINT32                                           LcElecIdleMode:2 ; ///<
    UINT32                          LcDisableInferredElecIdleDetect:1 ; ///<
    UINT32                                           Reserved_18_17:2 ; ///<
    UINT32                                      LcDeassertRxEnInL0s:1 ; ///<
    UINT32                                        LcBlockElIdleinL0:1 ; ///<
    UINT32                                       LcRcvL0toRcvL0sDis:1 ; ///<
    UINT32                               LcAssertInactiveDuringHold:1 ; ///<
    UINT32                                    LcWaitForLanesInLwNeg:2 ; ///<
    UINT32                                     LcPwrDownNegOffLanes:1 ; ///<
    UINT32                                 LcDisableLostSymLockArcs:1 ; ///<
    UINT32                                  LcLinkBwNotificationDis:1 ; ///<
    UINT32                                           Reserved_28_28:1 ; ///<
    UINT32                                           LcTestTimerSel:2 ; ///<
    UINT32                                            ElecIdleForPi:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xB1_STRUCT;

// **** DxFxxE4_xB5 Register Definition ****
// Address
#define DxFxxE4_xB5_ADDRESS                                     0xb5

// Type
#define DxFxxE4_xB5_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xB5_LcSelectDeemphasis_OFFSET                   0
#define DxFxxE4_xB5_LcSelectDeemphasis_WIDTH                    1
#define DxFxxE4_xB5_LcSelectDeemphasis_MASK                     0x1
#define DxFxxE4_xB5_LcSelectDeemphasisCntl_OFFSET               1
#define DxFxxE4_xB5_LcSelectDeemphasisCntl_WIDTH                2
#define DxFxxE4_xB5_LcSelectDeemphasisCntl_MASK                 0x6
#define DxFxxE4_xB5_LcRcvdDeemphasis_OFFSET                     3
#define DxFxxE4_xB5_LcRcvdDeemphasis_WIDTH                      1
#define DxFxxE4_xB5_LcRcvdDeemphasis_MASK                       0x8
#define DxFxxE4_xB5_LcCompToDetect_OFFSET                       4
#define DxFxxE4_xB5_LcCompToDetect_WIDTH                        1
#define DxFxxE4_xB5_LcCompToDetect_MASK                         0x10
#define DxFxxE4_xB5_LcResetTsxCntInRlockEn_OFFSET               5
#define DxFxxE4_xB5_LcResetTsxCntInRlockEn_WIDTH                1
#define DxFxxE4_xB5_LcResetTsxCntInRlockEn_MASK                 0x20
#define DxFxxE4_xB5_LcAutoSpeedChangeAttemptsAllowed_OFFSET     6
#define DxFxxE4_xB5_LcAutoSpeedChangeAttemptsAllowed_WIDTH      2
#define DxFxxE4_xB5_LcAutoSpeedChangeAttemptsAllowed_MASK       0xc0
#define DxFxxE4_xB5_LcAutoSpeedChangeAttemptFailed_OFFSET       8
#define DxFxxE4_xB5_LcAutoSpeedChangeAttemptFailed_WIDTH        1
#define DxFxxE4_xB5_LcAutoSpeedChangeAttemptFailed_MASK         0x100
#define DxFxxE4_xB5_LcClrFailedAutoSpdChangeCnt_OFFSET          9
#define DxFxxE4_xB5_LcClrFailedAutoSpdChangeCnt_WIDTH           1
#define DxFxxE4_xB5_LcClrFailedAutoSpdChangeCnt_MASK            0x200
#define DxFxxE4_xB5_LcEnhancedHotPlugEn_OFFSET                  10
#define DxFxxE4_xB5_LcEnhancedHotPlugEn_WIDTH                   1
#define DxFxxE4_xB5_LcEnhancedHotPlugEn_MASK                    0x400
#define DxFxxE4_xB5_LcRcvrDetEnOverride_OFFSET                  11
#define DxFxxE4_xB5_LcRcvrDetEnOverride_WIDTH                   1
#define DxFxxE4_xB5_LcRcvrDetEnOverride_MASK                    0x800
#define DxFxxE4_xB5_LcEhpRxPhyCmd_OFFSET                        12
#define DxFxxE4_xB5_LcEhpRxPhyCmd_WIDTH                         2
#define DxFxxE4_xB5_LcEhpRxPhyCmd_MASK                          0x3000
#define DxFxxE4_xB5_LcEhpTxPhyCmd_OFFSET                        14
#define DxFxxE4_xB5_LcEhpTxPhyCmd_WIDTH                         2
#define DxFxxE4_xB5_LcEhpTxPhyCmd_MASK                          0xc000
#define DxFxxE4_xB5_LcChipBifUsbIdleEn_OFFSET                   16
#define DxFxxE4_xB5_LcChipBifUsbIdleEn_WIDTH                    1
#define DxFxxE4_xB5_LcChipBifUsbIdleEn_MASK                     0x10000
#define DxFxxE4_xB5_LcChipBifUsbIdleEn_VALUE                    0x0
#define DxFxxE4_xB5_LcL1BlockReconfigEn_OFFSET                  17
#define DxFxxE4_xB5_LcL1BlockReconfigEn_WIDTH                   1
#define DxFxxE4_xB5_LcL1BlockReconfigEn_MASK                    0x20000
#define DxFxxE4_xB5_LcAutoDisableSpeedSupportEn_OFFSET          18
#define DxFxxE4_xB5_LcAutoDisableSpeedSupportEn_WIDTH           1
#define DxFxxE4_xB5_LcAutoDisableSpeedSupportEn_MASK            0x40000
#define DxFxxE4_xB5_LcAutoDisableSpeedSupportMaxFailSel_OFFSET  19
#define DxFxxE4_xB5_LcAutoDisableSpeedSupportMaxFailSel_WIDTH   2
#define DxFxxE4_xB5_LcAutoDisableSpeedSupportMaxFailSel_MASK    0x180000
#define DxFxxE4_xB5_LcFastL1EntryExitEn_OFFSET                  21
#define DxFxxE4_xB5_LcFastL1EntryExitEn_WIDTH                   1
#define DxFxxE4_xB5_LcFastL1EntryExitEn_MASK                    0x200000
#define DxFxxE4_xB5_LcRxPhyCmdInactiveEnMode_OFFSET             22
#define DxFxxE4_xB5_LcRxPhyCmdInactiveEnMode_WIDTH              1
#define DxFxxE4_xB5_LcRxPhyCmdInactiveEnMode_MASK               0x400000
#define DxFxxE4_xB5_LcDscDontEnterL23AfterPmeAck_OFFSET         23
#define DxFxxE4_xB5_LcDscDontEnterL23AfterPmeAck_WIDTH          1
#define DxFxxE4_xB5_LcDscDontEnterL23AfterPmeAck_MASK           0x800000
#define DxFxxE4_xB5_LcHwVoltageIfControl_OFFSET                 24
#define DxFxxE4_xB5_LcHwVoltageIfControl_WIDTH                  2
#define DxFxxE4_xB5_LcHwVoltageIfControl_MASK                   0x3000000
#define DxFxxE4_xB5_LcVoltageTimerSel_OFFSET                    26
#define DxFxxE4_xB5_LcVoltageTimerSel_WIDTH                     4
#define DxFxxE4_xB5_LcVoltageTimerSel_MASK                      0x3c000000
#define DxFxxE4_xB5_LcGoToRecovery_OFFSET                       30
#define DxFxxE4_xB5_LcGoToRecovery_WIDTH                        1
#define DxFxxE4_xB5_LcGoToRecovery_MASK                         0x40000000
#define DxFxxE4_xB5_LcNEieSel_OFFSET                            31
#define DxFxxE4_xB5_LcNEieSel_WIDTH                             1
#define DxFxxE4_xB5_LcNEieSel_MASK                              0x80000000

/// DxFxxE4_xB5
typedef union {
  struct {                                                              ///<
    UINT32                                       LcSelectDeemphasis:1 ; ///<
    UINT32                                   LcSelectDeemphasisCntl:2 ; ///<
    UINT32                                         LcRcvdDeemphasis:1 ; ///<
    UINT32                                           LcCompToDetect:1 ; ///<
    UINT32                                   LcResetTsxCntInRlockEn:1 ; ///<
    UINT32                         LcAutoSpeedChangeAttemptsAllowed:2 ; ///<
    UINT32                           LcAutoSpeedChangeAttemptFailed:1 ; ///<
    UINT32                              LcClrFailedAutoSpdChangeCnt:1 ; ///<
    UINT32                                      LcEnhancedHotPlugEn:1 ; ///<
    UINT32                                      LcRcvrDetEnOverride:1 ; ///<
    UINT32                                            LcEhpRxPhyCmd:2 ; ///<
    UINT32                                            LcEhpTxPhyCmd:2 ; ///<
    UINT32                                       LcChipBifUsbIdleEn:1 ; ///<
    UINT32                                      LcL1BlockReconfigEn:1 ; ///<
    UINT32                              LcAutoDisableSpeedSupportEn:1 ; ///<
    UINT32                      LcAutoDisableSpeedSupportMaxFailSel:2 ; ///<
    UINT32                                      LcFastL1EntryExitEn:1 ; ///<
    UINT32                                 LcRxPhyCmdInactiveEnMode:1 ; ///<
    UINT32                             LcDscDontEnterL23AfterPmeAck:1 ; ///<
    UINT32                                     LcHwVoltageIfControl:2 ; ///<
    UINT32                                        LcVoltageTimerSel:4 ; ///<
    UINT32                                           LcGoToRecovery:1 ; ///<
    UINT32                                                LcNEieSel:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xB5_STRUCT;

// **** DxFxxE4_xB6 Register Definition ****
// Address
#define DxFxxE4_xB6_ADDRESS                                     0xb6

// Type
#define DxFxxE4_xB6_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xB6_LcTxEnableBehaviour_OFFSET                  0
#define DxFxxE4_xB6_LcTxEnableBehaviour_WIDTH                   2
#define DxFxxE4_xB6_LcTxEnableBehaviour_MASK                    0x3
#define DxFxxE4_xB6_Reserved_2_2_OFFSET                         2
#define DxFxxE4_xB6_Reserved_2_2_WIDTH                          1
#define DxFxxE4_xB6_Reserved_2_2_MASK                           0x4
#define DxFxxE4_xB6_LcGatePmiL1WithSlvIdle_OFFSET               3
#define DxFxxE4_xB6_LcGatePmiL1WithSlvIdle_WIDTH                1
#define DxFxxE4_xB6_LcGatePmiL1WithSlvIdle_MASK                 0x8
#define DxFxxE4_xB6_LcBypassEq_OFFSET                           4
#define DxFxxE4_xB6_LcBypassEq_WIDTH                            1
#define DxFxxE4_xB6_LcBypassEq_MASK                             0x10
#define DxFxxE4_xB6_LcRedoEq_OFFSET                             5
#define DxFxxE4_xB6_LcRedoEq_WIDTH                              1
#define DxFxxE4_xB6_LcRedoEq_MASK                               0x20
#define DxFxxE4_xB6_LcExtendEieos_OFFSET                        6
#define DxFxxE4_xB6_LcExtendEieos_WIDTH                         1
#define DxFxxE4_xB6_LcExtendEieos_MASK                          0x40
#define DxFxxE4_xB6_LcIgnoreParity_OFFSET                       7
#define DxFxxE4_xB6_LcIgnoreParity_WIDTH                        1
#define DxFxxE4_xB6_LcIgnoreParity_MASK                         0x80
#define DxFxxE4_xB6_LcEqSearchMode_OFFSET                       8
#define DxFxxE4_xB6_LcEqSearchMode_WIDTH                        2
#define DxFxxE4_xB6_LcEqSearchMode_MASK                         0x300
#define DxFxxE4_xB6_LcDscCheckCoeffsInRlock_OFFSET              10
#define DxFxxE4_xB6_LcDscCheckCoeffsInRlock_WIDTH               1
#define DxFxxE4_xB6_LcDscCheckCoeffsInRlock_MASK                0x400
#define DxFxxE4_xB6_LcUscEqNotReqd_OFFSET                       11
#define DxFxxE4_xB6_LcUscEqNotReqd_WIDTH                        1
#define DxFxxE4_xB6_LcUscEqNotReqd_MASK                         0x800
#define DxFxxE4_xB6_LcUscGoToEq_OFFSET                          12
#define DxFxxE4_xB6_LcUscGoToEq_WIDTH                           1
#define DxFxxE4_xB6_LcUscGoToEq_MASK                            0x1000
#define DxFxxE4_xB6_LcSetQuiesce_OFFSET                         13
#define DxFxxE4_xB6_LcSetQuiesce_WIDTH                          1
#define DxFxxE4_xB6_LcSetQuiesce_MASK                           0x2000
#define DxFxxE4_xB6_LcQuiesceRcvd_OFFSET                        14
#define DxFxxE4_xB6_LcQuiesceRcvd_WIDTH                         1
#define DxFxxE4_xB6_LcQuiesceRcvd_MASK                          0x4000
#define DxFxxE4_xB6_LcUnexpectedCoeffsRcvd_OFFSET               15
#define DxFxxE4_xB6_LcUnexpectedCoeffsRcvd_WIDTH                1
#define DxFxxE4_xB6_LcUnexpectedCoeffsRcvd_MASK                 0x8000
#define DxFxxE4_xB6_LcBypassEqReqPhase_OFFSET                   16
#define DxFxxE4_xB6_LcBypassEqReqPhase_WIDTH                    1
#define DxFxxE4_xB6_LcBypassEqReqPhase_MASK                     0x10000
#define DxFxxE4_xB6_LcForcePresetInEqReqPhase_OFFSET            17
#define DxFxxE4_xB6_LcForcePresetInEqReqPhase_WIDTH             1
#define DxFxxE4_xB6_LcForcePresetInEqReqPhase_MASK              0x20000
#define DxFxxE4_xB6_LcForcePresetValue_OFFSET                   18
#define DxFxxE4_xB6_LcForcePresetValue_WIDTH                    4
#define DxFxxE4_xB6_LcForcePresetValue_MASK                     0x3c0000
#define DxFxxE4_xB6_LcUscDelayDllps_OFFSET                      22
#define DxFxxE4_xB6_LcUscDelayDllps_WIDTH                       1
#define DxFxxE4_xB6_LcUscDelayDllps_MASK                        0x400000
#define DxFxxE4_xB6_LcPcieTxFullSwing_OFFSET                    23
#define DxFxxE4_xB6_LcPcieTxFullSwing_WIDTH                     1
#define DxFxxE4_xB6_LcPcieTxFullSwing_MASK                      0x800000
#define DxFxxE4_xB6_LcEqWaitForEvalDone_OFFSET                  24
#define DxFxxE4_xB6_LcEqWaitForEvalDone_WIDTH                   1
#define DxFxxE4_xB6_LcEqWaitForEvalDone_MASK                    0x1000000
#define DxFxxE4_xB6_Lc8gtSkipOrderEn_OFFSET                     25
#define DxFxxE4_xB6_Lc8gtSkipOrderEn_WIDTH                      1
#define DxFxxE4_xB6_Lc8gtSkipOrderEn_MASK                       0x2000000
#define DxFxxE4_xB6_LcWaitForMoreTsInRlock_OFFSET               26
#define DxFxxE4_xB6_LcWaitForMoreTsInRlock_WIDTH                6
#define DxFxxE4_xB6_LcWaitForMoreTsInRlock_MASK                 0xfc000000

/// DxFxxE4_xB6
typedef union {
  struct {                                                              ///<
    UINT32                                      LcTxEnableBehaviour:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                   LcGatePmiL1WithSlvIdle:1 ; ///<
    UINT32                                               LcBypassEq:1 ; ///<
    UINT32                                                 LcRedoEq:1 ; ///<
    UINT32                                            LcExtendEieos:1 ; ///<
    UINT32                                           LcIgnoreParity:1 ; ///<
    UINT32                                           LcEqSearchMode:2 ; ///<
    UINT32                                  LcDscCheckCoeffsInRlock:1 ; ///<
    UINT32                                           LcUscEqNotReqd:1 ; ///<
    UINT32                                              LcUscGoToEq:1 ; ///<
    UINT32                                             LcSetQuiesce:1 ; ///<
    UINT32                                            LcQuiesceRcvd:1 ; ///<
    UINT32                                   LcUnexpectedCoeffsRcvd:1 ; ///<
    UINT32                                       LcBypassEqReqPhase:1 ; ///<
    UINT32                                LcForcePresetInEqReqPhase:1 ; ///<
    UINT32                                       LcForcePresetValue:4 ; ///<
    UINT32                                          LcUscDelayDllps:1 ; ///<
    UINT32                                        LcPcieTxFullSwing:1 ; ///<
    UINT32                                      LcEqWaitForEvalDone:1 ; ///<
    UINT32                                         Lc8gtSkipOrderEn:1 ; ///<
    UINT32                                   LcWaitForMoreTsInRlock:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xB6_STRUCT;

// **** DxFxxE4_xC0 Register Definition ****
// Address
#define DxFxxE4_xC0_ADDRESS                                     0xc0

// Type
#define DxFxxE4_xC0_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xC0_StrapFTSyTSxCount_OFFSET                    0
#define DxFxxE4_xC0_StrapFTSyTSxCount_WIDTH                     2
#define DxFxxE4_xC0_StrapFTSyTSxCount_MASK                      0x3
#define DxFxxE4_xC0_StrapLongyTSxCount_OFFSET                   2
#define DxFxxE4_xC0_StrapLongyTSxCount_WIDTH                    2
#define DxFxxE4_xC0_StrapLongyTSxCount_MASK                     0xc
#define DxFxxE4_xC0_StrapMedyTSxCount_OFFSET                    4
#define DxFxxE4_xC0_StrapMedyTSxCount_WIDTH                     2
#define DxFxxE4_xC0_StrapMedyTSxCount_MASK                      0x30
#define DxFxxE4_xC0_StrapShortyTSxCount_OFFSET                  6
#define DxFxxE4_xC0_StrapShortyTSxCount_WIDTH                   2
#define DxFxxE4_xC0_StrapShortyTSxCount_MASK                    0xc0
#define DxFxxE4_xC0_StrapSkipInterval_OFFSET                    8
#define DxFxxE4_xC0_StrapSkipInterval_WIDTH                     3
#define DxFxxE4_xC0_StrapSkipInterval_MASK                      0x700
#define DxFxxE4_xC0_StrapBypassRcvrDet_OFFSET                   11
#define DxFxxE4_xC0_StrapBypassRcvrDet_WIDTH                    1
#define DxFxxE4_xC0_StrapBypassRcvrDet_MASK                     0x800
#define DxFxxE4_xC0_StrapComplianceDis_OFFSET                   12
#define DxFxxE4_xC0_StrapComplianceDis_WIDTH                    1
#define DxFxxE4_xC0_StrapComplianceDis_MASK                     0x1000
#define DxFxxE4_xC0_StrapForceCompliance_OFFSET                 13
#define DxFxxE4_xC0_StrapForceCompliance_WIDTH                  1
#define DxFxxE4_xC0_StrapForceCompliance_MASK                   0x2000
#define DxFxxE4_xC0_StrapReverseLcLanes_OFFSET                  14
#define DxFxxE4_xC0_StrapReverseLcLanes_WIDTH                   1
#define DxFxxE4_xC0_StrapReverseLcLanes_MASK                    0x4000
#define DxFxxE4_xC0_StrapAutoRcSpeedNegotiationDis_OFFSET       15
#define DxFxxE4_xC0_StrapAutoRcSpeedNegotiationDis_WIDTH        1
#define DxFxxE4_xC0_StrapAutoRcSpeedNegotiationDis_MASK         0x8000
#define DxFxxE4_xC0_StrapLaneNegotiation_OFFSET                 16
#define DxFxxE4_xC0_StrapLaneNegotiation_WIDTH                  3
#define DxFxxE4_xC0_StrapLaneNegotiation_MASK                   0x70000
#define DxFxxE4_xC0_Reserved_31_19_OFFSET                       19
#define DxFxxE4_xC0_Reserved_31_19_WIDTH                        13
#define DxFxxE4_xC0_Reserved_31_19_MASK                         0xfff80000

/// DxFxxE4_xC0
typedef union {
  struct {                                                              ///<
    UINT32                                        StrapFTSyTSxCount:2 ; ///<
    UINT32                                       StrapLongyTSxCount:2 ; ///<
    UINT32                                        StrapMedyTSxCount:2 ; ///<
    UINT32                                      StrapShortyTSxCount:2 ; ///<
    UINT32                                        StrapSkipInterval:3 ; ///<
    UINT32                                       StrapBypassRcvrDet:1 ; ///<
    UINT32                                       StrapComplianceDis:1 ; ///<
    UINT32                                     StrapForceCompliance:1 ; ///<
    UINT32                                      StrapReverseLcLanes:1 ; ///<
    UINT32                           StrapAutoRcSpeedNegotiationDis:1 ; ///<
    UINT32                                     StrapLaneNegotiation:3 ; ///<
    UINT32                                           Reserved_31_19:13; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xC0_STRUCT;

// **** DxFxxE4_xC1 Register Definition ****
// Address
#define DxFxxE4_xC1_ADDRESS                                     0xc1
// Type
#define DxFxxE4_xC1_TYPE                                        TYPE_D4F1xE4
// Field Data
#define DxFxxE4_xC1_StrapE2EPrefixEn_OFFSET                     1
#define DxFxxE4_xC1_StrapE2EPrefixEn_WIDTH                      1
#define DxFxxE4_xC1_StrapE2EPrefixEn_MASK                       0x2
#define DxFxxE4_xC1_StrapExtendedFmtSupported_OFFSET            2
#define DxFxxE4_xC1_StrapExtendedFmtSupported_WIDTH             1
#define DxFxxE4_xC1_StrapExtendedFmtSupported_MASK              0x4

/// DxFxxE4_xC1
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                         StrapE2EPrefixEn:1 ; ///<
    UINT32                                StrapExtendedFmtSupported:1 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xC1_STRUCT;

// **** DxFxxE4_xDA Register Definition ****
// Address
#define DxFxxE4_xDA_ADDRESS                                     0xda

// Type
#define DxFxxE4_xDA_TYPE                                        TYPE_D2F1xE4
// Field Data
#define DxFxxE4_xDA_RegHpgiAssertToSmiEn_OFFSET                 0
#define DxFxxE4_xDA_RegHpgiAssertToSmiEn_WIDTH                  1
#define DxFxxE4_xDA_RegHpgiAssertToSmiEn_MASK                   0x1
#define DxFxxE4_xDA_RegHpgiAssertToSciEn_OFFSET                 1
#define DxFxxE4_xDA_RegHpgiAssertToSciEn_WIDTH                  1
#define DxFxxE4_xDA_RegHpgiAssertToSciEn_MASK                   0x2
#define DxFxxE4_xDA_RegHpgiDeassertToSmiEn_OFFSET               2
#define DxFxxE4_xDA_RegHpgiDeassertToSmiEn_WIDTH                1
#define DxFxxE4_xDA_RegHpgiDeassertToSmiEn_MASK                 0x4
#define DxFxxE4_xDA_RegHpgiDeassertToSciEn_OFFSET               3
#define DxFxxE4_xDA_RegHpgiDeassertToSciEn_WIDTH                1
#define DxFxxE4_xDA_RegHpgiDeassertToSciEn_MASK                 0x8
#define DxFxxE4_xDA_Reserved_6_4_OFFSET                         4
#define DxFxxE4_xDA_Reserved_6_4_WIDTH                          3
#define DxFxxE4_xDA_Reserved_6_4_MASK                           0x70
#define DxFxxE4_xDA_RegHpgiHook_OFFSET                          7
#define DxFxxE4_xDA_RegHpgiHook_WIDTH                           1
#define DxFxxE4_xDA_RegHpgiHook_MASK                            0x80
#define DxFxxE4_xDA_HpgiRegAssertToSmiStatus_OFFSET             8
#define DxFxxE4_xDA_HpgiRegAssertToSmiStatus_WIDTH              1
#define DxFxxE4_xDA_HpgiRegAssertToSmiStatus_MASK               0x100
#define DxFxxE4_xDA_HpgiRegAssertToSciStatus_OFFSET             9
#define DxFxxE4_xDA_HpgiRegAssertToSciStatus_WIDTH              1
#define DxFxxE4_xDA_HpgiRegAssertToSciStatus_MASK               0x200
#define DxFxxE4_xDA_HpgiRegDeassertToSmiStatus_OFFSET           10
#define DxFxxE4_xDA_HpgiRegDeassertToSmiStatus_WIDTH            1
#define DxFxxE4_xDA_HpgiRegDeassertToSmiStatus_MASK             0x400
#define DxFxxE4_xDA_HpgiRegDeassertToSciStatus_OFFSET           11
#define DxFxxE4_xDA_HpgiRegDeassertToSciStatus_WIDTH            1
#define DxFxxE4_xDA_HpgiRegDeassertToSciStatus_MASK             0x800
#define DxFxxE4_xDA_Reserved_14_12_OFFSET                       12
#define DxFxxE4_xDA_Reserved_14_12_WIDTH                        3
#define DxFxxE4_xDA_Reserved_14_12_MASK                         0x7000
#define DxFxxE4_xDA_HpgiRegPresenceDetectStateChangeStatus_OFFSET 15
#define DxFxxE4_xDA_HpgiRegPresenceDetectStateChangeStatus_WIDTH 1
#define DxFxxE4_xDA_HpgiRegPresenceDetectStateChangeStatus_MASK 0x8000
#define DxFxxE4_xDA_RegHpgiPresenceDetectStateChangeEn_OFFSET   16
#define DxFxxE4_xDA_RegHpgiPresenceDetectStateChangeEn_WIDTH    1
#define DxFxxE4_xDA_RegHpgiPresenceDetectStateChangeEn_MASK     0x10000
#define DxFxxE4_xDA_Reserved_31_17_OFFSET                       17
#define DxFxxE4_xDA_Reserved_31_17_WIDTH                        15
#define DxFxxE4_xDA_Reserved_31_17_MASK                         0xfffe0000

/// DxFxxE4_xDA
typedef union {
  struct {                                                              ///<
    UINT32                                     RegHpgiAssertToSmiEn:1 ; ///<
    UINT32                                     RegHpgiAssertToSciEn:1 ; ///<
    UINT32                                   RegHpgiDeassertToSmiEn:1 ; ///<
    UINT32                                   RegHpgiDeassertToSciEn:1 ; ///<
    UINT32                                             Reserved_6_4:3 ; ///<
    UINT32                                              RegHpgiHook:1 ; ///<
    UINT32                                 HpgiRegAssertToSmiStatus:1 ; ///<
    UINT32                                 HpgiRegAssertToSciStatus:1 ; ///<
    UINT32                               HpgiRegDeassertToSmiStatus:1 ; ///<
    UINT32                               HpgiRegDeassertToSciStatus:1 ; ///<
    UINT32                                           Reserved_14_12:3 ; ///<
    UINT32                   HpgiRegPresenceDetectStateChangeStatus:1 ; ///<
    UINT32                       RegHpgiPresenceDetectStateChangeEn:1 ; ///<
    UINT32                                           Reserved_31_17:15; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DxFxxE4_xDA_STRUCT;

// **** D0F2x50 Register Definition ****
// Address
#define D0F2x50_ADDRESS                                         0x50

// Type
#define D0F2x50_TYPE                                            TYPE_D0F2
// Field Data
#define D0F2x50_IommuMsiNum_OFFSET                              0
#define D0F2x50_IommuMsiNum_WIDTH                               5
#define D0F2x50_IommuMsiNum_MASK                                0x1f
#define D0F2x50_IommuGvaSize_OFFSET                             5
#define D0F2x50_IommuGvaSize_WIDTH                              3
#define D0F2x50_IommuGvaSize_MASK                               0xe0
#define D0F2x50_IommuPaSize_OFFSET                              8
#define D0F2x50_IommuPaSize_WIDTH                               7
#define D0F2x50_IommuPaSize_MASK                                0x7f00
#define D0F2x50_IommuVaSize_OFFSET                              15
#define D0F2x50_IommuVaSize_WIDTH                               7
#define D0F2x50_IommuVaSize_MASK                                0x3f8000
#define D0F2x50_IommuHtAtsResv_OFFSET                           22
#define D0F2x50_IommuHtAtsResv_WIDTH                            1
#define D0F2x50_IommuHtAtsResv_MASK                             0x400000
#define D0F2x50_Reserved_26_23_OFFSET                           23
#define D0F2x50_Reserved_26_23_WIDTH                            4
#define D0F2x50_Reserved_26_23_MASK                             0x7800000
#define D0F2x50_IommuMsiNumPpr_OFFSET                           27
#define D0F2x50_IommuMsiNumPpr_WIDTH                            5
#define D0F2x50_IommuMsiNumPpr_MASK                             0xf8000000

/// D0F2x50
typedef union {
  struct {                                                              ///<
    UINT32                                              IommuMsiNum:5 ; ///<
    UINT32                                             IommuGvaSize:3 ; ///<
    UINT32                                              IommuPaSize:7 ; ///<
    UINT32                                              IommuVaSize:7 ; ///<
    UINT32                                           IommuHtAtsResv:1 ; ///<
    UINT32                                           Reserved_26_23:4 ; ///<
    UINT32                                           IommuMsiNumPpr:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2x50_STRUCT;

// **** D0F2x7C Register Definition ****
// Address
#define D0F2x7C_ADDRESS                                         0x7c

// Type
#define D0F2x7C_TYPE                                            TYPE_D0F2
// Field Data
#define D0F2x7C_InterruptPinW_OFFSET                            0
#define D0F2x7C_InterruptPinW_WIDTH                             3
#define D0F2x7C_InterruptPinW_MASK                              0x7
#define D0F2x7C_Reserved_3_3_OFFSET                             3
#define D0F2x7C_Reserved_3_3_WIDTH                              1
#define D0F2x7C_Reserved_3_3_MASK                               0x8
#define D0F2x7C_MinorRevIdW_OFFSET                              4
#define D0F2x7C_MinorRevIdW_WIDTH                               4
#define D0F2x7C_MinorRevIdW_MASK                                0xf0
#define D0F2x7C_IoTlbsupW_OFFSET                                8
#define D0F2x7C_IoTlbsupW_WIDTH                                 1
#define D0F2x7C_IoTlbsupW_MASK                                  0x100
#define D0F2x7C_EfrSupW_OFFSET                                  9
#define D0F2x7C_EfrSupW_WIDTH                                   1
#define D0F2x7C_EfrSupW_MASK                                    0x200
#define D0F2x7C_MsiMultMessCapW_OFFSET                          10
#define D0F2x7C_MsiMultMessCapW_WIDTH                           3
#define D0F2x7C_MsiMultMessCapW_MASK                            0x1c00
#define D0F2x7C_CapExtW_OFFSET                                  13
#define D0F2x7C_CapExtW_WIDTH                                   1
#define D0F2x7C_CapExtW_MASK                                    0x2000
#define D0F2x7C_Reserved_31_14_OFFSET                           14
#define D0F2x7C_Reserved_31_14_WIDTH                            18
#define D0F2x7C_Reserved_31_14_MASK                             0xffffc000

/// D0F2x7C
typedef union {
  struct {                                                              ///<
    UINT32                                            InterruptPinW:3 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                              MinorRevIdW:4 ; ///<
    UINT32                                                IoTlbsupW:1 ; ///<
    UINT32                                                  EfrSupW:1 ; ///<
    UINT32                                          MsiMultMessCapW:3 ; ///<
    UINT32                                                  CapExtW:1 ; ///<
    UINT32                                           Reserved_31_14:18; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2x7C_STRUCT;

// **** D0F2x80 Register Definition ****
// Address
#define D0F2x80_ADDRESS                                         0x80

// Type
#define D0F2x80_TYPE                                            TYPE_D0F2
// Field Data
#define D0F2x80_PrefSupW_OFFSET                                 0
#define D0F2x80_PrefSupW_WIDTH                                  1
#define D0F2x80_PrefSupW_MASK                                   0x1
#define D0F2x80_PprSupW_OFFSET                                  1
#define D0F2x80_PprSupW_WIDTH                                   1
#define D0F2x80_PprSupW_MASK                                    0x2
#define D0F2x80_Reserved_2_2_OFFSET                             2
#define D0F2x80_Reserved_2_2_WIDTH                              1
#define D0F2x80_Reserved_2_2_MASK                               0x4
#define D0F2x80_NxSupW_OFFSET                                   3
#define D0F2x80_NxSupW_WIDTH                                    1
#define D0F2x80_NxSupW_MASK                                     0x8
#define D0F2x80_GtSupW_OFFSET                                   4
#define D0F2x80_GtSupW_WIDTH                                    1
#define D0F2x80_GtSupW_MASK                                     0x10
#define D0F2x80_Reserved_5_5_OFFSET                             5
#define D0F2x80_Reserved_5_5_WIDTH                              1
#define D0F2x80_Reserved_5_5_MASK                               0x20
#define D0F2x80_IaSupW_OFFSET                                   6
#define D0F2x80_IaSupW_WIDTH                                    1
#define D0F2x80_IaSupW_MASK                                     0x40
#define D0F2x80_GaSupW_OFFSET                                   7
#define D0F2x80_GaSupW_WIDTH                                    1
#define D0F2x80_GaSupW_MASK                                     0x80
#define D0F2x80_Reserved_8_8_OFFSET                             8
#define D0F2x80_Reserved_8_8_WIDTH                              1
#define D0F2x80_Reserved_8_8_MASK                               0x100
#define D0F2x80_PcSupW_OFFSET                                   9
#define D0F2x80_PcSupW_WIDTH                                    1
#define D0F2x80_PcSupW_MASK                                     0x200
#define D0F2x80_HatsW_OFFSET                                    10
#define D0F2x80_HatsW_WIDTH                                     2
#define D0F2x80_HatsW_MASK                                      0xc00
#define D0F2x80_Reserved_20_12_OFFSET                           12
#define D0F2x80_Reserved_20_12_WIDTH                            9
#define D0F2x80_Reserved_20_12_MASK                             0x1ff000
#define D0F2x80_GamSupW_OFFSET                                  21
#define D0F2x80_GamSupW_WIDTH                                   3
#define D0F2x80_GamSupW_MASK                                    0xe00000
#define D0F2x80_Reserved_31_24_OFFSET                           24
#define D0F2x80_Reserved_31_24_WIDTH                            8
#define D0F2x80_Reserved_31_24_MASK                             0xff000000

/// D0F2x80
typedef union {
  struct {                                                              ///<
    UINT32                                                 PrefSupW:1 ; ///<
    UINT32                                                  PprSupW:1 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                                   NxSupW:1 ; ///<
    UINT32                                                   GtSupW:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                                   IaSupW:1 ; ///<
    UINT32                                                   GaSupW:1 ; ///<
    UINT32                                             Reserved_8_8:1 ; ///<
    UINT32                                                   PcSupW:1 ; ///<
    UINT32                                                    HatsW:2 ; ///<
    UINT32                                           Reserved_20_12:9 ; ///<
    UINT32                                                  GamSupW:3 ; ///<
    UINT32                                           Reserved_31_24:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2x80_STRUCT;

// **** D0F2xF0 Register Definition ****
// Address
#define D0F2xF0_ADDRESS                                         0xf0

// Type
#define D0F2xF0_TYPE                                            TYPE_D0F2
// Field Data
#define D0F2xF0_L2cfgIndex_OFFSET                               0
#define D0F2xF0_L2cfgIndex_WIDTH                                8
#define D0F2xF0_L2cfgIndex_MASK                                 0xff
#define D0F2xF0_L2cfgWrEn_OFFSET                                8
#define D0F2xF0_L2cfgWrEn_WIDTH                                 1
#define D0F2xF0_L2cfgWrEn_MASK                                  0x100
#define D0F2xF0_Reserved_31_9_OFFSET                            9
#define D0F2xF0_Reserved_31_9_WIDTH                             23
#define D0F2xF0_Reserved_31_9_MASK                              0xfffffe00

/// D0F2xF0
typedef union {
  struct {                                                              ///<
    UINT32                                               L2cfgIndex:8 ; ///<
    UINT32                                                L2cfgWrEn:1 ; ///<
    UINT32                                            Reserved_31_9:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF0_STRUCT;

// **** D0F2xF8 Register Definition ****
// Address
#define D0F2xF8_ADDRESS                                         0xf8

// Type
#define D0F2xF8_TYPE                                            TYPE_D0F2
// Field Data
#define D0F2xF8_L1cfgIndex_OFFSET                               0
#define D0F2xF8_L1cfgIndex_WIDTH                                16
#define D0F2xF8_L1cfgIndex_MASK                                 0xffff
#define D0F2xF8_L1cfgSel_OFFSET                                 16
#define D0F2xF8_L1cfgSel_WIDTH                                  4
#define D0F2xF8_L1cfgSel_MASK                                   0xf0000
#define D0F2xF8_Reserved_30_20_OFFSET                           20
#define D0F2xF8_Reserved_30_20_WIDTH                            11
#define D0F2xF8_Reserved_30_20_MASK                             0x7ff00000
#define D0F2xF8_L1cfgEn_OFFSET                                  31
#define D0F2xF8_L1cfgEn_WIDTH                                   1
#define D0F2xF8_L1cfgEn_MASK                                    0x80000000

/// D0F2xF8
typedef union {
  struct {                                                              ///<
    UINT32                                               L1cfgIndex:16; ///<
    UINT32                                                 L1cfgSel:4 ; ///<
    UINT32                                           Reserved_30_20:11; ///<
    UINT32                                                  L1cfgEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF8_STRUCT;

// **** D0F2xF4_x10 Register Definition ****
// Address
#define D0F2xF4_x10_ADDRESS                                     0x10

// Type
#define D0F2xF4_x10_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x10_DTCReplacementSel_OFFSET                    0
#define D0F2xF4_x10_DTCReplacementSel_WIDTH                     2
#define D0F2xF4_x10_DTCReplacementSel_MASK                      0x3
#define D0F2xF4_x10_Reserved_2_2_OFFSET                         2
#define D0F2xF4_x10_Reserved_2_2_WIDTH                          1
#define D0F2xF4_x10_Reserved_2_2_MASK                           0x4
#define D0F2xF4_x10_DTCLRUUpdatePri_OFFSET                      3
#define D0F2xF4_x10_DTCLRUUpdatePri_WIDTH                       1
#define D0F2xF4_x10_DTCLRUUpdatePri_MASK                        0x8
#define D0F2xF4_x10_DTCParityEn_OFFSET                          4
#define D0F2xF4_x10_DTCParityEn_WIDTH                           1
#define D0F2xF4_x10_DTCParityEn_MASK                            0x10
#define D0F2xF4_x10_Reserved_7_5_OFFSET                         5
#define D0F2xF4_x10_Reserved_7_5_WIDTH                          3
#define D0F2xF4_x10_Reserved_7_5_MASK                           0xe0
#define D0F2xF4_x10_DTCInvalidationSel_OFFSET                   8
#define D0F2xF4_x10_DTCInvalidationSel_WIDTH                    2
#define D0F2xF4_x10_DTCInvalidationSel_MASK                     0x300
#define D0F2xF4_x10_DTCInvalidationSel_VALUE                    0x2
#define D0F2xF4_x10_DTCSoftInvalidate_OFFSET                    10
#define D0F2xF4_x10_DTCSoftInvalidate_WIDTH                     1
#define D0F2xF4_x10_DTCSoftInvalidate_MASK                      0x400
#define D0F2xF4_x10_Reserved_12_11_OFFSET                       11
#define D0F2xF4_x10_Reserved_12_11_WIDTH                        2
#define D0F2xF4_x10_Reserved_12_11_MASK                         0x1800
#define D0F2xF4_x10_DTCBypass_OFFSET                            13
#define D0F2xF4_x10_DTCBypass_WIDTH                             1
#define D0F2xF4_x10_DTCBypass_MASK                              0x2000
#define D0F2xF4_x10_Reserved_14_14_OFFSET                       14
#define D0F2xF4_x10_Reserved_14_14_WIDTH                        1
#define D0F2xF4_x10_Reserved_14_14_MASK                         0x4000
#define D0F2xF4_x10_DTCParitySupport_OFFSET                     15
#define D0F2xF4_x10_DTCParitySupport_WIDTH                      1
#define D0F2xF4_x10_DTCParitySupport_MASK                       0x8000
#define D0F2xF4_x10_DTCWays_OFFSET                              16
#define D0F2xF4_x10_DTCWays_WIDTH                               8
#define D0F2xF4_x10_DTCWays_MASK                                0xff0000
#define D0F2xF4_x10_Reserved_27_24_OFFSET                       24
#define D0F2xF4_x10_Reserved_27_24_WIDTH                        4
#define D0F2xF4_x10_Reserved_27_24_MASK                         0xf000000
#define D0F2xF4_x10_DTCEntries_OFFSET                           28
#define D0F2xF4_x10_DTCEntries_WIDTH                            4
#define D0F2xF4_x10_DTCEntries_MASK                             0xf0000000

/// D0F2xF4_x10
typedef union {
  struct {                                                              ///<
    UINT32                                        DTCReplacementSel:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                          DTCLRUUpdatePri:1 ; ///<
    UINT32                                              DTCParityEn:1 ; ///<
    UINT32                                             Reserved_7_5:3 ; ///<
    UINT32                                       DTCInvalidationSel:2 ; ///<
    UINT32                                        DTCSoftInvalidate:1 ; ///<
    UINT32                                           Reserved_12_11:2 ; ///<
    UINT32                                                DTCBypass:1 ; ///<
    UINT32                                           Reserved_14_14:1 ; ///<
    UINT32                                         DTCParitySupport:1 ; ///<
    UINT32                                                  DTCWays:8 ; ///<
    UINT32                                           Reserved_27_24:4 ; ///<
    UINT32                                               DTCEntries:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x10_STRUCT;

// **** D0F2xF4_x14 Register Definition ****
// Address
#define D0F2xF4_x14_ADDRESS                                     0x14

// Type
#define D0F2xF4_x14_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x14_ITCReplacementSel_OFFSET                    0
#define D0F2xF4_x14_ITCReplacementSel_WIDTH                     2
#define D0F2xF4_x14_ITCReplacementSel_MASK                      0x3
#define D0F2xF4_x14_Reserved_2_2_OFFSET                         2
#define D0F2xF4_x14_Reserved_2_2_WIDTH                          1
#define D0F2xF4_x14_Reserved_2_2_MASK                           0x4
#define D0F2xF4_x14_ITCLRUUpdatePri_OFFSET                      3
#define D0F2xF4_x14_ITCLRUUpdatePri_WIDTH                       1
#define D0F2xF4_x14_ITCLRUUpdatePri_MASK                        0x8
#define D0F2xF4_x14_ITCParityEn_OFFSET                          4
#define D0F2xF4_x14_ITCParityEn_WIDTH                           1
#define D0F2xF4_x14_ITCParityEn_MASK                            0x10
#define D0F2xF4_x14_Reserved_7_5_OFFSET                         5
#define D0F2xF4_x14_Reserved_7_5_WIDTH                          3
#define D0F2xF4_x14_Reserved_7_5_MASK                           0xe0
#define D0F2xF4_x14_ITCInvalidationSel_OFFSET                   8
#define D0F2xF4_x14_ITCInvalidationSel_WIDTH                    2
#define D0F2xF4_x14_ITCInvalidationSel_MASK                     0x300
#define D0F2xF4_x14_ITCSoftInvalidate_OFFSET                    10
#define D0F2xF4_x14_ITCSoftInvalidate_WIDTH                     1
#define D0F2xF4_x14_ITCSoftInvalidate_MASK                      0x400
#define D0F2xF4_x14_Reserved_12_11_OFFSET                       11
#define D0F2xF4_x14_Reserved_12_11_WIDTH                        2
#define D0F2xF4_x14_Reserved_12_11_MASK                         0x1800
#define D0F2xF4_x14_ITCBypass_OFFSET                            13
#define D0F2xF4_x14_ITCBypass_WIDTH                             1
#define D0F2xF4_x14_ITCBypass_MASK                              0x2000
#define D0F2xF4_x14_Reserved_14_14_OFFSET                       14
#define D0F2xF4_x14_Reserved_14_14_WIDTH                        1
#define D0F2xF4_x14_Reserved_14_14_MASK                         0x4000
#define D0F2xF4_x14_ITCParitySupport_OFFSET                     15
#define D0F2xF4_x14_ITCParitySupport_WIDTH                      1
#define D0F2xF4_x14_ITCParitySupport_MASK                       0x8000
#define D0F2xF4_x14_ITCWays_OFFSET                              16
#define D0F2xF4_x14_ITCWays_WIDTH                               8
#define D0F2xF4_x14_ITCWays_MASK                                0xff0000
#define D0F2xF4_x14_Reserved_27_24_OFFSET                       24
#define D0F2xF4_x14_Reserved_27_24_WIDTH                        4
#define D0F2xF4_x14_Reserved_27_24_MASK                         0xf000000
#define D0F2xF4_x14_ITCEntries_OFFSET                           28
#define D0F2xF4_x14_ITCEntries_WIDTH                            4
#define D0F2xF4_x14_ITCEntries_MASK                             0xf0000000

/// D0F2xF4_x14
typedef union {
  struct {                                                              ///<
    UINT32                                        ITCReplacementSel:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                          ITCLRUUpdatePri:1 ; ///<
    UINT32                                              ITCParityEn:1 ; ///<
    UINT32                                             Reserved_7_5:3 ; ///<
    UINT32                                       ITCInvalidationSel:2 ; ///<
    UINT32                                        ITCSoftInvalidate:1 ; ///<
    UINT32                                           Reserved_12_11:2 ; ///<
    UINT32                                                ITCBypass:1 ; ///<
    UINT32                                           Reserved_14_14:1 ; ///<
    UINT32                                         ITCParitySupport:1 ; ///<
    UINT32                                                  ITCWays:8 ; ///<
    UINT32                                           Reserved_27_24:4 ; ///<
    UINT32                                               ITCEntries:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x14_STRUCT;

// **** D0F2xF4_x18 Register Definition ****
// Address
#define D0F2xF4_x18_ADDRESS                                     0x18

// Type
#define D0F2xF4_x18_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x18_PTCAReplacementSel_OFFSET                   0
#define D0F2xF4_x18_PTCAReplacementSel_WIDTH                    2
#define D0F2xF4_x18_PTCAReplacementSel_MASK                     0x3
#define D0F2xF4_x18_Reserved_2_2_OFFSET                         2
#define D0F2xF4_x18_Reserved_2_2_WIDTH                          1
#define D0F2xF4_x18_Reserved_2_2_MASK                           0x4
#define D0F2xF4_x18_PTCALRUUpdatePri_OFFSET                     3
#define D0F2xF4_x18_PTCALRUUpdatePri_WIDTH                      1
#define D0F2xF4_x18_PTCALRUUpdatePri_MASK                       0x8
#define D0F2xF4_x18_PTCAParityEn_OFFSET                         4
#define D0F2xF4_x18_PTCAParityEn_WIDTH                          1
#define D0F2xF4_x18_PTCAParityEn_MASK                           0x10
#define D0F2xF4_x18_Reserved_7_5_OFFSET                         5
#define D0F2xF4_x18_Reserved_7_5_WIDTH                          3
#define D0F2xF4_x18_Reserved_7_5_MASK                           0xe0
#define D0F2xF4_x18_PTCAInvalidationSel_OFFSET                  8
#define D0F2xF4_x18_PTCAInvalidationSel_WIDTH                   2
#define D0F2xF4_x18_PTCAInvalidationSel_MASK                    0x300
#define D0F2xF4_x18_PTCASoftInvalidate_OFFSET                   10
#define D0F2xF4_x18_PTCASoftInvalidate_WIDTH                    1
#define D0F2xF4_x18_PTCASoftInvalidate_MASK                     0x400
#define D0F2xF4_x18_PTCA2MMode_OFFSET                           11
#define D0F2xF4_x18_PTCA2MMode_WIDTH                            1
#define D0F2xF4_x18_PTCA2MMode_MASK                             0x800
#define D0F2xF4_x18_Reserved_12_12_OFFSET                       12
#define D0F2xF4_x18_Reserved_12_12_WIDTH                        1
#define D0F2xF4_x18_Reserved_12_12_MASK                         0x1000
#define D0F2xF4_x18_PTCABypass_OFFSET                           13
#define D0F2xF4_x18_PTCABypass_WIDTH                            1
#define D0F2xF4_x18_PTCABypass_MASK                             0x2000
#define D0F2xF4_x18_Reserved_14_14_OFFSET                       14
#define D0F2xF4_x18_Reserved_14_14_WIDTH                        1
#define D0F2xF4_x18_Reserved_14_14_MASK                         0x4000
#define D0F2xF4_x18_PTCAParitySupport_OFFSET                    15
#define D0F2xF4_x18_PTCAParitySupport_WIDTH                     1
#define D0F2xF4_x18_PTCAParitySupport_MASK                      0x8000
#define D0F2xF4_x18_PTCAWays_OFFSET                             16
#define D0F2xF4_x18_PTCAWays_WIDTH                              8
#define D0F2xF4_x18_PTCAWays_MASK                               0xff0000
#define D0F2xF4_x18_Reserved_27_24_OFFSET                       24
#define D0F2xF4_x18_Reserved_27_24_WIDTH                        4
#define D0F2xF4_x18_Reserved_27_24_MASK                         0xf000000
#define D0F2xF4_x18_PTCAEntries_OFFSET                          28
#define D0F2xF4_x18_PTCAEntries_WIDTH                           4
#define D0F2xF4_x18_PTCAEntries_MASK                            0xf0000000

/// D0F2xF4_x18
typedef union {
  struct {                                                              ///<
    UINT32                                       PTCAReplacementSel:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                         PTCALRUUpdatePri:1 ; ///<
    UINT32                                             PTCAParityEn:1 ; ///<
    UINT32                                             Reserved_7_5:3 ; ///<
    UINT32                                      PTCAInvalidationSel:2 ; ///<
    UINT32                                       PTCASoftInvalidate:1 ; ///<
    UINT32                                               PTCA2MMode:1 ; ///<
    UINT32                                           Reserved_12_12:1 ; ///<
    UINT32                                               PTCABypass:1 ; ///<
    UINT32                                           Reserved_14_14:1 ; ///<
    UINT32                                        PTCAParitySupport:1 ; ///<
    UINT32                                                 PTCAWays:8 ; ///<
    UINT32                                           Reserved_27_24:4 ; ///<
    UINT32                                              PTCAEntries:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x18_STRUCT;

// **** D0F2xF4_x22 Register Definition ****
// Address
#define D0F2xF4_x22_ADDRESS                                     0x22

// Type
#define D0F2xF4_x22_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x22_L2aUpdateFilterBypass_OFFSET                0
#define D0F2xF4_x22_L2aUpdateFilterBypass_WIDTH                 1
#define D0F2xF4_x22_L2aUpdateFilterBypass_MASK                  0x1
#define D0F2xF4_x22_L2aUpdateFilterRdlatency_OFFSET             1
#define D0F2xF4_x22_L2aUpdateFilterRdlatency_WIDTH              4
#define D0F2xF4_x22_L2aUpdateFilterRdlatency_MASK               0x1e
#define D0F2xF4_x22_Reserved_31_5_OFFSET                        5
#define D0F2xF4_x22_Reserved_31_5_WIDTH                         27
#define D0F2xF4_x22_Reserved_31_5_MASK                          0xffffffe0

/// D0F2xF4_x22
typedef union {
  struct {                                                              ///<
    UINT32                                    L2aUpdateFilterBypass:1 ; ///<
    UINT32                                 L2aUpdateFilterRdlatency:4 ; ///<
    UINT32                                            Reserved_31_5:27; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x22_STRUCT;

// **** D0F2xF4_x30 Register Definition ****
// Address
#define D0F2xF4_x30_ADDRESS                                     0x30

// Type
#define D0F2xF4_x30_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x30_ERRRuleLock1_OFFSET                         0
#define D0F2xF4_x30_ERRRuleLock1_WIDTH                          1
#define D0F2xF4_x30_ERRRuleLock1_MASK                           0x1
#define D0F2xF4_x30_Reserved_3_1_OFFSET                         1
#define D0F2xF4_x30_Reserved_3_1_WIDTH                          3
#define D0F2xF4_x30_Reserved_3_1_MASK                           0xe
#define D0F2xF4_x30_ERRRuleDisable3_OFFSET                      4
#define D0F2xF4_x30_ERRRuleDisable3_WIDTH                       28
#define D0F2xF4_x30_ERRRuleDisable3_MASK                        0xfffffff0

/// D0F2xF4_x30
typedef union {
  struct {                                                              ///<
    UINT32                                             ERRRuleLock1:1 ; ///<
    UINT32                                             Reserved_3_1:3 ; ///<
    UINT32                                          ERRRuleDisable3:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x30_STRUCT;

// **** D0F2xF4_x33 Register Definition ****
// Address
#define D0F2xF4_x33_ADDRESS                                     0x33

// Type
#define D0F2xF4_x33_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x33_CKGateL2ARegsDisable_OFFSET                 0
#define D0F2xF4_x33_CKGateL2ARegsDisable_WIDTH                  1
#define D0F2xF4_x33_CKGateL2ARegsDisable_MASK                   0x1
#define D0F2xF4_x33_CKGateL2ARegsDisable_VALUE                  0x0
#define D0F2xF4_x33_CKGateL2ADynamicDisable_OFFSET              1
#define D0F2xF4_x33_CKGateL2ADynamicDisable_WIDTH               1
#define D0F2xF4_x33_CKGateL2ADynamicDisable_MASK                0x2
#define D0F2xF4_x33_CKGateL2ADynamicDisable_VALUE               0x0
#define D0F2xF4_x33_CKGateL2ACacheDisable_OFFSET                2
#define D0F2xF4_x33_CKGateL2ACacheDisable_WIDTH                 1
#define D0F2xF4_x33_CKGateL2ACacheDisable_MASK                  0x4
#define D0F2xF4_x33_CKGateL2ACacheDisable_VALUE                 0x0
#define D0F2xF4_x33_CKGateL2ASpare_OFFSET                       3
#define D0F2xF4_x33_CKGateL2ASpare_WIDTH                        1
#define D0F2xF4_x33_CKGateL2ASpare_MASK                         0x8
#define D0F2xF4_x33_CKGateL2ALength_OFFSET                      4
#define D0F2xF4_x33_CKGateL2ALength_WIDTH                       2
#define D0F2xF4_x33_CKGateL2ALength_MASK                        0x30
#define D0F2xF4_x33_CKGateL2AStop_OFFSET                        6
#define D0F2xF4_x33_CKGateL2AStop_WIDTH                         2
#define D0F2xF4_x33_CKGateL2AStop_MASK                          0xc0
#define D0F2xF4_x33_Reserved_31_8_OFFSET                        8
#define D0F2xF4_x33_Reserved_31_8_WIDTH                         24
#define D0F2xF4_x33_Reserved_31_8_MASK                          0xffffff00

/// D0F2xF4_x33
typedef union {
  struct {                                                              ///<
    UINT32                                     CKGateL2ARegsDisable:1 ; ///<
    UINT32                                  CKGateL2ADynamicDisable:1 ; ///<
    UINT32                                    CKGateL2ACacheDisable:1 ; ///<
    UINT32                                           CKGateL2ASpare:1 ; ///<
    UINT32                                          CKGateL2ALength:2 ; ///<
    UINT32                                            CKGateL2AStop:2 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x33_STRUCT;

// **** D0F2xF4_x34 Register Definition ****
// Address
#define D0F2xF4_x34_ADDRESS                                     0x34

// Type
#define D0F2xF4_x34_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x34_L2aregGstPgsize_OFFSET                      0
#define D0F2xF4_x34_L2aregGstPgsize_WIDTH                       2
#define D0F2xF4_x34_L2aregGstPgsize_MASK                        0x3
#define D0F2xF4_x34_L2aregHostPgsize_OFFSET                     2
#define D0F2xF4_x34_L2aregHostPgsize_WIDTH                      2
#define D0F2xF4_x34_L2aregHostPgsize_MASK                       0xc
#define D0F2xF4_x34_Reserved_31_4_OFFSET                        4
#define D0F2xF4_x34_Reserved_31_4_WIDTH                         28
#define D0F2xF4_x34_Reserved_31_4_MASK                          0xfffffff0

/// D0F2xF4_x34
typedef union {
  struct {                                                              ///<
    UINT32                                          L2aregGstPgsize:2 ; ///<
    UINT32                                         L2aregHostPgsize:2 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x34_STRUCT;

// **** D0F2xF4_x35 Register Definition ****
// Address
#define D0F2xF4_x35_ADDRESS                                     0x35

// Type
#define D0F2xF4_x35_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x35_L2aregLSEn_OFFSET                           0
#define D0F2xF4_x35_L2aregLSEn_WIDTH                            1
#define D0F2xF4_x35_L2aregLSEn_MASK                             0x1
#define D0F2xF4_x35_L2aregDSEn_OFFSET                           1
#define D0F2xF4_x35_L2aregDSEn_WIDTH                            1
#define D0F2xF4_x35_L2aregDSEn_MASK                             0x2
#define D0F2xF4_x35_L2aregSDEn_OFFSET                           2
#define D0F2xF4_x35_L2aregSDEn_WIDTH                            1
#define D0F2xF4_x35_L2aregSDEn_MASK                             0x4
#define D0F2xF4_x35_Reserved_31_3_OFFSET                        3
#define D0F2xF4_x35_Reserved_31_3_WIDTH                         29
#define D0F2xF4_x35_Reserved_31_3_MASK                          0xfffffff8

/// D0F2xF4_x35
typedef union {
  struct {                                                              ///<
    UINT32                                               L2aregLSEn:1 ; ///<
    UINT32                                               L2aregDSEn:1 ; ///<
    UINT32                                               L2aregSDEn:1 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x35_STRUCT;

// **** D0F2xF4_x36 Register Definition ****
// Address
#define D0F2xF4_x36_ADDRESS                                     0x36

// Type
#define D0F2xF4_x36_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x36_L2aregLSThres_OFFSET                        0
#define D0F2xF4_x36_L2aregLSThres_WIDTH                         32
#define D0F2xF4_x36_L2aregLSThres_MASK                          0xffffffff

/// D0F2xF4_x36
typedef union {
  struct {                                                              ///<
    UINT32                                            L2aregLSThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x36_STRUCT;

// **** D0F2xF4_x37 Register Definition ****
// Address
#define D0F2xF4_x37_ADDRESS                                     0x37

// Type
#define D0F2xF4_x37_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x37_L2aregDSThres_OFFSET                        0
#define D0F2xF4_x37_L2aregDSThres_WIDTH                         32
#define D0F2xF4_x37_L2aregDSThres_MASK                          0xffffffff

/// D0F2xF4_x37
typedef union {
  struct {                                                              ///<
    UINT32                                            L2aregDSThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x37_STRUCT;

// **** D0F2xF4_x3B Register Definition ****
// Address
#define D0F2xF4_x3B_ADDRESS                                     0x3b

// Type
#define D0F2xF4_x3B_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x3B_FSM_ADDR_OFFSET                             0
#define D0F2xF4_x3B_FSM_ADDR_WIDTH                              8
#define D0F2xF4_x3B_FSM_ADDR_MASK                               0xff
#define D0F2xF4_x3B_Power_Down_OFFSET                           8
#define D0F2xF4_x3B_Power_Down_WIDTH                            1
#define D0F2xF4_x3B_Power_Down_MASK                             0x100
#define D0F2xF4_x3B_Power_Up_OFFSET                             9
#define D0F2xF4_x3B_Power_Up_WIDTH                              1
#define D0F2xF4_x3B_Power_Up_MASK                               0x200
#define D0F2xF4_x3B_P1_Select_OFFSET                            10
#define D0F2xF4_x3B_P1_Select_WIDTH                             1
#define D0F2xF4_x3B_P1_Select_MASK                              0x400
#define D0F2xF4_x3B_P2_Select_OFFSET                            11
#define D0F2xF4_x3B_P2_Select_WIDTH                             1
#define D0F2xF4_x3B_P2_Select_MASK                              0x800
#define D0F2xF4_x3B_PG_Write_OFFSET                             12
#define D0F2xF4_x3B_PG_Write_WIDTH                              1
#define D0F2xF4_x3B_PG_Write_MASK                               0x1000
#define D0F2xF4_x3B_PG_Read_OFFSET                              13
#define D0F2xF4_x3B_PG_Read_WIDTH                               1
#define D0F2xF4_x3B_PG_Read_MASK                                0x2000
#define D0F2xF4_x3B_Reserved_OFFSET                             14
#define D0F2xF4_x3B_Reserved_WIDTH                              13
#define D0F2xF4_x3B_Reserved_MASK                               0x7ffc000
#define D0F2xF4_x3B_SRBM_override_OFFSET                        27
#define D0F2xF4_x3B_SRBM_override_WIDTH                         1
#define D0F2xF4_x3B_SRBM_override_MASK                          0x8000000
#define D0F2xF4_x3B_REG_ADDR_OFFSET                             28
#define D0F2xF4_x3B_REG_ADDR_WIDTH                              4
#define D0F2xF4_x3B_REG_ADDR_MASK                               0xf0000000

/// D0F2xF4_x3B
typedef union {
  struct {                                                              ///<
    UINT32                                                 FSM_ADDR:8 ; ///<
    UINT32                                               Power_Down:1 ; ///<
    UINT32                                                 Power_Up:1 ; ///<
    UINT32                                                P1_Select:1 ; ///<
    UINT32                                                P2_Select:1 ; ///<
    UINT32                                                 PG_Write:1 ; ///<
    UINT32                                                  PG_Read:1 ; ///<
    UINT32                                                 Reserved:13; ///<
    UINT32                                            SRBM_override:1 ; ///<
    UINT32                                                 REG_ADDR:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x3B_STRUCT;

// **** D0F2xF4_x3C Register Definition ****
// Address
#define D0F2xF4_x3C_ADDRESS                                     0x3c

// Type
#define D0F2xF4_x3C_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x3C_WriteValue_OFFSET                           0
#define D0F2xF4_x3C_WriteValue_WIDTH                            32
#define D0F2xF4_x3C_WriteValue_MASK                             0xffffffff

/// D0F2xF4_x3C
typedef union {
  struct {                                                              ///<
    UINT32                                               WriteValue:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x3C_STRUCT;

// **** D0F2xF4_x3D Register Definition ****
// Address
#define D0F2xF4_x3D_ADDRESS                                     0x3d

// Type
#define D0F2xF4_x3D_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x3D_ReadValue_OFFSET                            0
#define D0F2xF4_x3D_ReadValue_WIDTH                             24
#define D0F2xF4_x3D_ReadValue_MASK                              0xffffff
#define D0F2xF4_x3D_Reserved_31_24_OFFSET                       24
#define D0F2xF4_x3D_Reserved_31_24_WIDTH                        8
#define D0F2xF4_x3D_Reserved_31_24_MASK                         0xff000000

/// D0F2xF4_x3D
typedef union {
  struct {                                                              ///<
    UINT32                                                ReadValue:24; ///<
    UINT32                                           Reserved_31_24:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x3D_STRUCT;

// **** D0F2xF4_x47 Register Definition ****
// Address
#define D0F2xF4_x47_ADDRESS                                     0x47

// Type
#define D0F2xF4_x47_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x47_AtsIgnoreIWDis_OFFSET                       0
#define D0F2xF4_x47_AtsIgnoreIWDis_WIDTH                        1
#define D0F2xF4_x47_AtsIgnoreIWDis_MASK                         0x1
#define D0F2xF4_x47_TwNwEn_OFFSET                               1
#define D0F2xF4_x47_TwNwEn_WIDTH                                1
#define D0F2xF4_x47_TwNwEn_MASK                                 0x2
#define D0F2xF4_x47_TwNwEn_VALUE                                0x1
#define D0F2xF4_x47_TwAtomicFilterEn_OFFSET                     2
#define D0F2xF4_x47_TwAtomicFilterEn_WIDTH                      1
#define D0F2xF4_x47_TwAtomicFilterEn_MASK                       0x4
#define D0F2xF4_x47_TwAtomicFilterEn_VALUE                      0x1
#define D0F2xF4_x47_BlockPTEUpdateUSZeroDis_OFFSET              3
#define D0F2xF4_x47_BlockPTEUpdateUSZeroDis_WIDTH               1
#define D0F2xF4_x47_BlockPTEUpdateUSZeroDis_MASK                0x8
#define D0F2xF4_x47_Reserved_5_4_OFFSET                         4
#define D0F2xF4_x47_Reserved_5_4_WIDTH                          2
#define D0F2xF4_x47_Reserved_5_4_MASK                           0x30
#define D0F2xF4_x47_PageMode0FixDis_OFFSET                      6
#define D0F2xF4_x47_PageMode0FixDis_WIDTH                       1
#define D0F2xF4_x47_PageMode0FixDis_MASK                        0x40
#define D0F2xF4_x47_LogATSDis_OFFSET                            7
#define D0F2xF4_x47_LogATSDis_WIDTH                             1
#define D0F2xF4_x47_LogATSDis_MASK                              0x80
#define D0F2xF4_x47_PTCUpdateAddrTransReq_OFFSET                8
#define D0F2xF4_x47_PTCUpdateAddrTransReq_WIDTH                 1
#define D0F2xF4_x47_PTCUpdateAddrTransReq_MASK                  0x100
#define D0F2xF4_x47_PprBaseLoHdPtrResetDis_OFFSET               9
#define D0F2xF4_x47_PprBaseLoHdPtrResetDis_WIDTH                1
#define D0F2xF4_x47_PprBaseLoHdPtrResetDis_MASK                 0x200
#define D0F2xF4_x47_PprBaseHiHdPtrResetDis_OFFSET               10
#define D0F2xF4_x47_PprBaseHiHdPtrResetDis_WIDTH                1
#define D0F2xF4_x47_PprBaseHiHdPtrResetDis_MASK                 0x400
#define D0F2xF4_x47_PprLenHdPtrReset_OFFSET                     11
#define D0F2xF4_x47_PprLenHdPtrReset_WIDTH                      1
#define D0F2xF4_x47_PprLenHdPtrReset_MASK                       0x800
#define D0F2xF4_x47_DTEResvBitChkDis_OFFSET                     12
#define D0F2xF4_x47_DTEResvBitChkDis_WIDTH                      1
#define D0F2xF4_x47_DTEResvBitChkDis_MASK                       0x1000
#define D0F2xF4_x47_GaBaseLoHdPtrResetDis_OFFSET                13
#define D0F2xF4_x47_GaBaseLoHdPtrResetDis_WIDTH                 1
#define D0F2xF4_x47_GaBaseLoHdPtrResetDis_MASK                  0x2000
#define D0F2xF4_x47_GaBaseHiHdPtrResetDis_OFFSET                14
#define D0F2xF4_x47_GaBaseHiHdPtrResetDis_WIDTH                 1
#define D0F2xF4_x47_GaBaseHiHdPtrResetDis_MASK                  0x4000
#define D0F2xF4_x47_GaLenHdPtrReset_OFFSET                      15
#define D0F2xF4_x47_GaLenHdPtrReset_WIDTH                       1
#define D0F2xF4_x47_GaLenHdPtrReset_MASK                        0x8000
#define D0F2xF4_x47_Reserved_30_16_OFFSET                       16
#define D0F2xF4_x47_Reserved_30_16_WIDTH                        15
#define D0F2xF4_x47_Reserved_30_16_MASK                         0x7fff0000
#define D0F2xF4_x47_GpuIommuDis_OFFSET                          31
#define D0F2xF4_x47_GpuIommuDis_WIDTH                           1
#define D0F2xF4_x47_GpuIommuDis_MASK                            0x80000000

/// D0F2xF4_x47
typedef union {
  struct {                                                              ///<
    UINT32                                           AtsIgnoreIWDis:1 ; ///<
    UINT32                                                   TwNwEn:1 ; ///<
    UINT32                                         TwAtomicFilterEn:1 ; ///<
    UINT32                                  BlockPTEUpdateUSZeroDis:1 ; ///<
    UINT32                                             Reserved_5_4:2 ; ///<
    UINT32                                          PageMode0FixDis:1 ; ///<
    UINT32                                                LogATSDis:1 ; ///<
    UINT32                                    PTCUpdateAddrTransReq:1 ; ///<
    UINT32                                   PprBaseLoHdPtrResetDis:1 ; ///<
    UINT32                                   PprBaseHiHdPtrResetDis:1 ; ///<
    UINT32                                         PprLenHdPtrReset:1 ; ///<
    UINT32                                         DTEResvBitChkDis:1 ; ///<
    UINT32                                    GaBaseLoHdPtrResetDis:1 ; ///<
    UINT32                                    GaBaseHiHdPtrResetDis:1 ; ///<
    UINT32                                          GaLenHdPtrReset:1 ; ///<
    UINT32                                           Reserved_30_16:15; ///<
    UINT32                                              GpuIommuDis:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x47_STRUCT;

// **** D0F2xF4_x49 Register Definition ****
// Address
#define D0F2xF4_x49_ADDRESS                                     0x49

// Type
#define D0F2xF4_x49_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x49_SBlocated_Port_OFFSET                       0
#define D0F2xF4_x49_SBlocated_Port_WIDTH                        16
#define D0F2xF4_x49_SBlocated_Port_MASK                         0xffff
#define D0F2xF4_x49_SBlocated_Core_OFFSET                       16
#define D0F2xF4_x49_SBlocated_Core_WIDTH                        16
#define D0F2xF4_x49_SBlocated_Core_MASK                         0xffff0000

/// D0F2xF4_x49
typedef union {
  struct {                                                              ///<
    UINT32                                           SBlocated_Port:16; ///<
    UINT32                                           SBlocated_Core:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x49_STRUCT;

// **** D0F2xF4_x4C Register Definition ****
// Address
#define D0F2xF4_x4C_ADDRESS                                     0x4c

// Type
#define D0F2xF4_x4C_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x4C_QueueArbFBPri_OFFSET                        0
#define D0F2xF4_x4C_QueueArbFBPri_WIDTH                         1
#define D0F2xF4_x4C_QueueArbFBPri_MASK                          0x1
#define D0F2xF4_x4C_PTCAddrTransReqUpdate_OFFSET                1
#define D0F2xF4_x4C_PTCAddrTransReqUpdate_WIDTH                 1
#define D0F2xF4_x4C_PTCAddrTransReqUpdate_MASK                  0x2
#define D0F2xF4_x4C_FC1Dis_OFFSET                               2
#define D0F2xF4_x4C_FC1Dis_WIDTH                                1
#define D0F2xF4_x4C_FC1Dis_MASK                                 0x4
#define D0F2xF4_x4C_DTCUpdateVOneIVZero_OFFSET                  3
#define D0F2xF4_x4C_DTCUpdateVOneIVZero_WIDTH                   1
#define D0F2xF4_x4C_DTCUpdateVOneIVZero_MASK                    0x8
#define D0F2xF4_x4C_DTCUpdateVZeroIVOne_OFFSET                  4
#define D0F2xF4_x4C_DTCUpdateVZeroIVOne_WIDTH                   1
#define D0F2xF4_x4C_DTCUpdateVZeroIVOne_MASK                    0x10
#define D0F2xF4_x4C_FC2Dis_OFFSET                               5
#define D0F2xF4_x4C_FC2Dis_WIDTH                                1
#define D0F2xF4_x4C_FC2Dis_MASK                                 0x20
#define D0F2xF4_x4C_FC3Dis_OFFSET                               6
#define D0F2xF4_x4C_FC3Dis_WIDTH                                1
#define D0F2xF4_x4C_FC3Dis_MASK                                 0x40
#define D0F2xF4_x4C_FC2AltMode_OFFSET                           7
#define D0F2xF4_x4C_FC2AltMode_WIDTH                            1
#define D0F2xF4_x4C_FC2AltMode_MASK                             0x80
#define D0F2xF4_x4C_GstPartialPtcCntrl_OFFSET                   8
#define D0F2xF4_x4C_GstPartialPtcCntrl_WIDTH                    2
#define D0F2xF4_x4C_GstPartialPtcCntrl_MASK                     0x300
#define D0F2xF4_x4C_GstPartialPtcCntrl_VALUE                    0x3
#define D0F2xF4_x4C_Reserved_31_10_OFFSET                       10
#define D0F2xF4_x4C_Reserved_31_10_WIDTH                        22
#define D0F2xF4_x4C_Reserved_31_10_MASK                         0xfffffc00

/// D0F2xF4_x4C
typedef union {
  struct {                                                              ///<
    UINT32                                            QueueArbFBPri:1 ; ///<
    UINT32                                    PTCAddrTransReqUpdate:1 ; ///<
    UINT32                                                   FC1Dis:1 ; ///<
    UINT32                                      DTCUpdateVOneIVZero:1 ; ///<
    UINT32                                      DTCUpdateVZeroIVOne:1 ; ///<
    UINT32                                                   FC2Dis:1 ; ///<
    UINT32                                                   FC3Dis:1 ; ///<
    UINT32                                               FC2AltMode:1 ; ///<
    UINT32                                       GstPartialPtcCntrl:2 ; ///<
    UINT32                                           Reserved_31_10:22; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x4C_STRUCT;

// **** D0F2xF4_x50 Register Definition ****
// Address
#define D0F2xF4_x50_ADDRESS                                     0x50

// Type
#define D0F2xF4_x50_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x50_PDCReplacementSel_OFFSET                    0
#define D0F2xF4_x50_PDCReplacementSel_WIDTH                     2
#define D0F2xF4_x50_PDCReplacementSel_MASK                      0x3
#define D0F2xF4_x50_Reserved_2_2_OFFSET                         2
#define D0F2xF4_x50_Reserved_2_2_WIDTH                          1
#define D0F2xF4_x50_Reserved_2_2_MASK                           0x4
#define D0F2xF4_x50_PDCLRUUpdatePri_OFFSET                      3
#define D0F2xF4_x50_PDCLRUUpdatePri_WIDTH                       1
#define D0F2xF4_x50_PDCLRUUpdatePri_MASK                        0x8
#define D0F2xF4_x50_PDCParityEn_OFFSET                          4
#define D0F2xF4_x50_PDCParityEn_WIDTH                           1
#define D0F2xF4_x50_PDCParityEn_MASK                            0x10
#define D0F2xF4_x50_Reserved_7_5_OFFSET                         5
#define D0F2xF4_x50_Reserved_7_5_WIDTH                          3
#define D0F2xF4_x50_Reserved_7_5_MASK                           0xe0
#define D0F2xF4_x50_PDCInvalidationSel_OFFSET                   8
#define D0F2xF4_x50_PDCInvalidationSel_WIDTH                    2
#define D0F2xF4_x50_PDCInvalidationSel_MASK                     0x300
#define D0F2xF4_x50_PDCSoftInvalidate_OFFSET                    10
#define D0F2xF4_x50_PDCSoftInvalidate_WIDTH                     1
#define D0F2xF4_x50_PDCSoftInvalidate_MASK                      0x400
#define D0F2xF4_x50_Reserved_11_11_OFFSET                       11
#define D0F2xF4_x50_Reserved_11_11_WIDTH                        1
#define D0F2xF4_x50_Reserved_11_11_MASK                         0x800
#define D0F2xF4_x50_PDCSearchDirection_OFFSET                   12
#define D0F2xF4_x50_PDCSearchDirection_WIDTH                    1
#define D0F2xF4_x50_PDCSearchDirection_MASK                     0x1000
#define D0F2xF4_x50_PDCBypass_OFFSET                            13
#define D0F2xF4_x50_PDCBypass_WIDTH                             1
#define D0F2xF4_x50_PDCBypass_MASK                              0x2000
#define D0F2xF4_x50_Reserved_14_14_OFFSET                       14
#define D0F2xF4_x50_Reserved_14_14_WIDTH                        1
#define D0F2xF4_x50_Reserved_14_14_MASK                         0x4000
#define D0F2xF4_x50_PDCParitySupport_OFFSET                     15
#define D0F2xF4_x50_PDCParitySupport_WIDTH                      1
#define D0F2xF4_x50_PDCParitySupport_MASK                       0x8000
#define D0F2xF4_x50_PDCWays_OFFSET                              16
#define D0F2xF4_x50_PDCWays_WIDTH                               8
#define D0F2xF4_x50_PDCWays_MASK                                0xff0000
#define D0F2xF4_x50_Reserved_27_24_OFFSET                       24
#define D0F2xF4_x50_Reserved_27_24_WIDTH                        4
#define D0F2xF4_x50_Reserved_27_24_MASK                         0xf000000
#define D0F2xF4_x50_PDCEntries_OFFSET                           28
#define D0F2xF4_x50_PDCEntries_WIDTH                            4
#define D0F2xF4_x50_PDCEntries_MASK                             0xf0000000

/// D0F2xF4_x50
typedef union {
  struct {                                                              ///<
    UINT32                                        PDCReplacementSel:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                          PDCLRUUpdatePri:1 ; ///<
    UINT32                                              PDCParityEn:1 ; ///<
    UINT32                                             Reserved_7_5:3 ; ///<
    UINT32                                       PDCInvalidationSel:2 ; ///<
    UINT32                                        PDCSoftInvalidate:1 ; ///<
    UINT32                                           Reserved_11_11:1 ; ///<
    UINT32                                       PDCSearchDirection:1 ; ///<
    UINT32                                                PDCBypass:1 ; ///<
    UINT32                                           Reserved_14_14:1 ; ///<
    UINT32                                         PDCParitySupport:1 ; ///<
    UINT32                                                  PDCWays:8 ; ///<
    UINT32                                           Reserved_27_24:4 ; ///<
    UINT32                                               PDCEntries:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x50_STRUCT;

// **** D0F2xF4_x53 Register Definition ****
// Address
#define D0F2xF4_x53_ADDRESS                                     0x53

// Type
#define D0F2xF4_x53_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x53_L2bUpdateFilterBypass_OFFSET                0
#define D0F2xF4_x53_L2bUpdateFilterBypass_WIDTH                 1
#define D0F2xF4_x53_L2bUpdateFilterBypass_MASK                  0x1
#define D0F2xF4_x53_L2bUpdateFilterRdlatency_OFFSET             1
#define D0F2xF4_x53_L2bUpdateFilterRdlatency_WIDTH              4
#define D0F2xF4_x53_L2bUpdateFilterRdlatency_MASK               0x1e
#define D0F2xF4_x53_Reserved_31_5_OFFSET                        5
#define D0F2xF4_x53_Reserved_31_5_WIDTH                         27
#define D0F2xF4_x53_Reserved_31_5_MASK                          0xffffffe0

/// D0F2xF4_x53
typedef union {
  struct {                                                              ///<
    UINT32                                    L2bUpdateFilterBypass:1 ; ///<
    UINT32                                 L2bUpdateFilterRdlatency:4 ; ///<
    UINT32                                            Reserved_31_5:27; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x53_STRUCT;

// **** D0F2xF4_x54 Register Definition ****
// Address
#define D0F2xF4_x54_ADDRESS                                     0x54

// Type
#define D0F2xF4_x54_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x54_TWQueueLimit_OFFSET                         0
#define D0F2xF4_x54_TWQueueLimit_WIDTH                          6
#define D0F2xF4_x54_TWQueueLimit_MASK                           0x3f
#define D0F2xF4_x54_TWForceCoherent_OFFSET                      6
#define D0F2xF4_x54_TWForceCoherent_WIDTH                       1
#define D0F2xF4_x54_TWForceCoherent_MASK                        0x40
#define D0F2xF4_x54_Reserved_7_7_OFFSET                         7
#define D0F2xF4_x54_Reserved_7_7_WIDTH                          1
#define D0F2xF4_x54_Reserved_7_7_MASK                           0x80
#define D0F2xF4_x54_TWPrefetchEn_OFFSET                         8
#define D0F2xF4_x54_TWPrefetchEn_WIDTH                          1
#define D0F2xF4_x54_TWPrefetchEn_MASK                           0x100
#define D0F2xF4_x54_TWPrefetchOnly4KDis_OFFSET                  9
#define D0F2xF4_x54_TWPrefetchOnly4KDis_WIDTH                   1
#define D0F2xF4_x54_TWPrefetchOnly4KDis_MASK                    0x200
#define D0F2xF4_x54_TWPTEOnUntransExcl_OFFSET                   10
#define D0F2xF4_x54_TWPTEOnUntransExcl_WIDTH                    1
#define D0F2xF4_x54_TWPTEOnUntransExcl_MASK                     0x400
#define D0F2xF4_x54_TWPTEOnAddrTransExcl_OFFSET                 11
#define D0F2xF4_x54_TWPTEOnAddrTransExcl_WIDTH                  1
#define D0F2xF4_x54_TWPTEOnAddrTransExcl_MASK                   0x800
#define D0F2xF4_x54_TWPrefetchRange_OFFSET                      12
#define D0F2xF4_x54_TWPrefetchRange_WIDTH                       3
#define D0F2xF4_x54_TWPrefetchRange_MASK                        0x7000
#define D0F2xF4_x54_Reserved_15_15_OFFSET                       15
#define D0F2xF4_x54_Reserved_15_15_WIDTH                        1
#define D0F2xF4_x54_Reserved_15_15_MASK                         0x8000
#define D0F2xF4_x54_TwfilterDis_OFFSET                          16
#define D0F2xF4_x54_TwfilterDis_WIDTH                           1
#define D0F2xF4_x54_TwfilterDis_MASK                            0x10000
#define D0F2xF4_x54_Twfilter64bDis_OFFSET                       17
#define D0F2xF4_x54_Twfilter64bDis_WIDTH                        1
#define D0F2xF4_x54_Twfilter64bDis_MASK                         0x20000
#define D0F2xF4_x54_TwContWalkPErrDis_OFFSET                    18
#define D0F2xF4_x54_TwContWalkPErrDis_WIDTH                     1
#define D0F2xF4_x54_TwContWalkPErrDis_MASK                      0x40000
#define D0F2xF4_x54_Reserved_31_19_OFFSET                       19
#define D0F2xF4_x54_Reserved_31_19_WIDTH                        13
#define D0F2xF4_x54_Reserved_31_19_MASK                         0xfff80000

/// D0F2xF4_x54
typedef union {
  struct {                                                              ///<
    UINT32                                             TWQueueLimit:6 ; ///<
    UINT32                                          TWForceCoherent:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                             TWPrefetchEn:1 ; ///<
    UINT32                                      TWPrefetchOnly4KDis:1 ; ///<
    UINT32                                       TWPTEOnUntransExcl:1 ; ///<
    UINT32                                     TWPTEOnAddrTransExcl:1 ; ///<
    UINT32                                          TWPrefetchRange:3 ; ///<
    UINT32                                           Reserved_15_15:1 ; ///<
    UINT32                                              TwfilterDis:1 ; ///<
    UINT32                                           Twfilter64bDis:1 ; ///<
    UINT32                                        TwContWalkPErrDis:1 ; ///<
    UINT32                                           Reserved_31_19:13; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x54_STRUCT;

// **** D0F2xF4_x56 Register Definition ****
// Address
#define D0F2xF4_x56_ADDRESS                                     0x56

// Type
#define D0F2xF4_x56_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x56_CPPrefetchDis_OFFSET                        0
#define D0F2xF4_x56_CPPrefetchDis_WIDTH                         1
#define D0F2xF4_x56_CPPrefetchDis_MASK                          0x1
#define D0F2xF4_x56_CPFlushOnWait_OFFSET                        1
#define D0F2xF4_x56_CPFlushOnWait_WIDTH                         1
#define D0F2xF4_x56_CPFlushOnWait_MASK                          0x2
#define D0F2xF4_x56_CPFlushOnWait_VALUE                         0x1
#define D0F2xF4_x56_CPFlushOnInv_OFFSET                         2
#define D0F2xF4_x56_CPFlushOnInv_WIDTH                          1
#define D0F2xF4_x56_CPFlushOnInv_MASK                           0x4
#define D0F2xF4_x56_CPFlushOnInv_VALUE                          0x0
#define D0F2xF4_x56_Reserved_15_3_OFFSET                        3
#define D0F2xF4_x56_Reserved_15_3_WIDTH                         13
#define D0F2xF4_x56_Reserved_15_3_MASK                          0xfff8
#define D0F2xF4_x56_CPRdDelay_OFFSET                            16
#define D0F2xF4_x56_CPRdDelay_WIDTH                             16
#define D0F2xF4_x56_CPRdDelay_MASK                              0xffff0000

/// D0F2xF4_x56
typedef union {
  struct {                                                              ///<
    UINT32                                            CPPrefetchDis:1 ; ///<
    UINT32                                            CPFlushOnWait:1 ; ///<
    UINT32                                             CPFlushOnInv:1 ; ///<
    UINT32                                            Reserved_15_3:13; ///<
    UINT32                                                CPRdDelay:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x56_STRUCT;

// **** D0F2xF4_x57 Register Definition ****
// Address
#define D0F2xF4_x57_ADDRESS                                     0x57

// Type
#define D0F2xF4_x57_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x57_L1ImuPcieGfxDis_OFFSET                      0
#define D0F2xF4_x57_L1ImuPcieGfxDis_WIDTH                       1
#define D0F2xF4_x57_L1ImuPcieGfxDis_MASK                        0x1
#define D0F2xF4_x57_CPL1Off_1__OFFSET                           1
#define D0F2xF4_x57_CPL1Off_1__WIDTH                            1
#define D0F2xF4_x57_CPL1Off_1__MASK                             0x2
#define D0F2xF4_x57_L1ImuIntGfxDis_OFFSET                       2
#define D0F2xF4_x57_L1ImuIntGfxDis_WIDTH                        1
#define D0F2xF4_x57_L1ImuIntGfxDis_MASK                         0x4
#define D0F2xF4_x57_L1ImuIntGfxDis_VALUE                        0x0
#define D0F2xF4_x57_CPL1Off_15_3__OFFSET                        3
#define D0F2xF4_x57_CPL1Off_15_3__WIDTH                         13
#define D0F2xF4_x57_CPL1Off_15_3__MASK                          0xfff8
#define D0F2xF4_x57_Reserved_31_16_OFFSET                       16
#define D0F2xF4_x57_Reserved_31_16_WIDTH                        16
#define D0F2xF4_x57_Reserved_31_16_MASK                         0xffff0000

/// D0F2xF4_x57
typedef union {
  struct {                                                              ///<
    UINT32                                          L1ImuPcieGfxDis:1 ; ///<
    UINT32                                               CPL1Off_1_:1 ; ///<
    UINT32                                           L1ImuIntGfxDis:1 ; ///<
    UINT32                                            CPL1Off_15_3_:13; ///<
    UINT32                                           Reserved_31_16:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x57_STRUCT;

// **** D0F2xF4_x80 Register Definition ****
// Address
#define D0F2xF4_x80_ADDRESS                                     0x80

// Type
#define D0F2xF4_x80_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x80_ERRRuleLock0_OFFSET                         0
#define D0F2xF4_x80_ERRRuleLock0_WIDTH                          1
#define D0F2xF4_x80_ERRRuleLock0_MASK                           0x1
#define D0F2xF4_x80_Reserved_3_1_OFFSET                         1
#define D0F2xF4_x80_Reserved_3_1_WIDTH                          3
#define D0F2xF4_x80_Reserved_3_1_MASK                           0xe
#define D0F2xF4_x80_ERRRuleDisable0_OFFSET                      4
#define D0F2xF4_x80_ERRRuleDisable0_WIDTH                       28
#define D0F2xF4_x80_ERRRuleDisable0_MASK                        0xfffffff0

/// D0F2xF4_x80
typedef union {
  struct {                                                              ///<
    UINT32                                             ERRRuleLock0:1 ; ///<
    UINT32                                             Reserved_3_1:3 ; ///<
    UINT32                                          ERRRuleDisable0:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x80_STRUCT;

// **** D0F2xF4_x90 Register Definition ****
// Address
#define D0F2xF4_x90_ADDRESS                                     0x90

// Type
#define D0F2xF4_x90_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x90_CKGateL2BRegsDisable_OFFSET                 0
#define D0F2xF4_x90_CKGateL2BRegsDisable_WIDTH                  1
#define D0F2xF4_x90_CKGateL2BRegsDisable_MASK                   0x1
#define D0F2xF4_x90_CKGateL2BRegsDisable_VALUE                  0x0
#define D0F2xF4_x90_CKGateL2BDynamicDisable_OFFSET              1
#define D0F2xF4_x90_CKGateL2BDynamicDisable_WIDTH               1
#define D0F2xF4_x90_CKGateL2BDynamicDisable_MASK                0x2
#define D0F2xF4_x90_CKGateL2BDynamicDisable_VALUE               0x0
#define D0F2xF4_x90_CKGateL2BMiscDisable_OFFSET                 2
#define D0F2xF4_x90_CKGateL2BMiscDisable_WIDTH                  1
#define D0F2xF4_x90_CKGateL2BMiscDisable_MASK                   0x4
#define D0F2xF4_x90_CKGateL2BMiscDisable_VALUE                  0x0
#define D0F2xF4_x90_CKGateL2BCacheDisable_OFFSET                3
#define D0F2xF4_x90_CKGateL2BCacheDisable_WIDTH                 1
#define D0F2xF4_x90_CKGateL2BCacheDisable_MASK                  0x8
#define D0F2xF4_x90_CKGateL2BLength_OFFSET                      4
#define D0F2xF4_x90_CKGateL2BLength_WIDTH                       2
#define D0F2xF4_x90_CKGateL2BLength_MASK                        0x30
#define D0F2xF4_x90_CKGateL2BStop_OFFSET                        6
#define D0F2xF4_x90_CKGateL2BStop_WIDTH                         2
#define D0F2xF4_x90_CKGateL2BStop_MASK                          0xc0
#define D0F2xF4_x90_Reserved_31_8_OFFSET                        8
#define D0F2xF4_x90_Reserved_31_8_WIDTH                         24
#define D0F2xF4_x90_Reserved_31_8_MASK                          0xffffff00

/// D0F2xF4_x90
typedef union {
  struct {                                                              ///<
    UINT32                                     CKGateL2BRegsDisable:1 ; ///<
    UINT32                                  CKGateL2BDynamicDisable:1 ; ///<
    UINT32                                     CKGateL2BMiscDisable:1 ; ///<
    UINT32                                    CKGateL2BCacheDisable:1 ; ///<
    UINT32                                          CKGateL2BLength:2 ; ///<
    UINT32                                            CKGateL2BStop:2 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x90_STRUCT;

// **** D0F2xF4_x94 Register Definition ****
// Address
#define D0F2xF4_x94_ADDRESS                                     0x94

// Type
#define D0F2xF4_x94_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x94_L2bregGstPgsize_OFFSET                      0
#define D0F2xF4_x94_L2bregGstPgsize_WIDTH                       2
#define D0F2xF4_x94_L2bregGstPgsize_MASK                        0x3
#define D0F2xF4_x94_L2bregHostPgsize_OFFSET                     2
#define D0F2xF4_x94_L2bregHostPgsize_WIDTH                      2
#define D0F2xF4_x94_L2bregHostPgsize_MASK                       0xc
#define D0F2xF4_x94_Reserved_31_4_OFFSET                        4
#define D0F2xF4_x94_Reserved_31_4_WIDTH                         28
#define D0F2xF4_x94_Reserved_31_4_MASK                          0xfffffff0

/// D0F2xF4_x94
typedef union {
  struct {                                                              ///<
    UINT32                                          L2bregGstPgsize:2 ; ///<
    UINT32                                         L2bregHostPgsize:2 ; ///<
    UINT32                                            Reserved_31_4:28; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x94_STRUCT;

// **** D0F2xF4_x95 Register Definition ****
// Address
#define D0F2xF4_x95_ADDRESS                                     0x95

// Type
#define D0F2xF4_x95_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x95_L2bregLSEn_OFFSET                           0
#define D0F2xF4_x95_L2bregLSEn_WIDTH                            1
#define D0F2xF4_x95_L2bregLSEn_MASK                             0x1
#define D0F2xF4_x95_L2bregDSEn_OFFSET                           1
#define D0F2xF4_x95_L2bregDSEn_WIDTH                            1
#define D0F2xF4_x95_L2bregDSEn_MASK                             0x2
#define D0F2xF4_x95_L2bregSDEn_OFFSET                           2
#define D0F2xF4_x95_L2bregSDEn_WIDTH                            1
#define D0F2xF4_x95_L2bregSDEn_MASK                             0x4
#define D0F2xF4_x95_Reserved_31_3_OFFSET                        3
#define D0F2xF4_x95_Reserved_31_3_WIDTH                         29
#define D0F2xF4_x95_Reserved_31_3_MASK                          0xfffffff8

/// D0F2xF4_x95
typedef union {
  struct {                                                              ///<
    UINT32                                               L2bregLSEn:1 ; ///<
    UINT32                                               L2bregDSEn:1 ; ///<
    UINT32                                               L2bregSDEn:1 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x95_STRUCT;

// **** D0F2xF4_x96 Register Definition ****
// Address
#define D0F2xF4_x96_ADDRESS                                     0x96

// Type
#define D0F2xF4_x96_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x96_L2bregLSThres_OFFSET                        0
#define D0F2xF4_x96_L2bregLSThres_WIDTH                         32
#define D0F2xF4_x96_L2bregLSThres_MASK                          0xffffffff

/// D0F2xF4_x96
typedef union {
  struct {                                                              ///<
    UINT32                                            L2bregLSThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x96_STRUCT;

// **** D0F2xF4_x97 Register Definition ****
// Address
#define D0F2xF4_x97_ADDRESS                                     0x97

// Type
#define D0F2xF4_x97_TYPE                                        TYPE_D0F2xF4
// Field Data
#define D0F2xF4_x97_L2bregDSThres_OFFSET                        0
#define D0F2xF4_x97_L2bregDSThres_WIDTH                         32
#define D0F2xF4_x97_L2bregDSThres_MASK                          0xffffffff

/// D0F2xF4_x97
typedef union {
  struct {                                                              ///<
    UINT32                                            L2bregDSThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xF4_x97_STRUCT;

// **** D0F2xFC_x07_L1 Register Definition ****
// Address
#define D0F2xFC_x07_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x07)

// Type
#define D0F2xFC_x07_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x07_L1_PhantomFuncDis_OFFSET                    0
#define D0F2xFC_x07_L1_PhantomFuncDis_WIDTH                     1
#define D0F2xFC_x07_L1_PhantomFuncDis_MASK                      0x1
#define D0F2xFC_x07_L1_Reserved_10_1_OFFSET                     1
#define D0F2xFC_x07_L1_Reserved_10_1_WIDTH                      10
#define D0F2xFC_x07_L1_Reserved_10_1_MASK                       0x7fe
#define D0F2xFC_x07_L1_SpecReqFilterEn_OFFSET                   11
#define D0F2xFC_x07_L1_SpecReqFilterEn_WIDTH                    1
#define D0F2xFC_x07_L1_SpecReqFilterEn_MASK                     0x800
#define D0F2xFC_x07_L1_SpecReqFilterEn_VALUE                    0x1
#define D0F2xFC_x07_L1_AtsSeqNumEn_OFFSET                       12
#define D0F2xFC_x07_L1_AtsSeqNumEn_WIDTH                        1
#define D0F2xFC_x07_L1_AtsSeqNumEn_MASK                         0x1000
#define D0F2xFC_x07_L1_AtsSeqNumEn_VALUE                        0x1
#define D0F2xFC_x07_L1_Reserved_13_13_OFFSET                    13
#define D0F2xFC_x07_L1_Reserved_13_13_WIDTH                     1
#define D0F2xFC_x07_L1_Reserved_13_13_MASK                      0x2000
#define D0F2xFC_x07_L1_AtsPhysPageOverlapDis_OFFSET             14
#define D0F2xFC_x07_L1_AtsPhysPageOverlapDis_WIDTH              1
#define D0F2xFC_x07_L1_AtsPhysPageOverlapDis_MASK               0x4000
#define D0F2xFC_x07_L1_AtsPhysPageOverlapDis_VALUE              0x1
#define D0F2xFC_x07_L1_Reserved_16_15_OFFSET                    15
#define D0F2xFC_x07_L1_Reserved_16_15_WIDTH                     2
#define D0F2xFC_x07_L1_Reserved_16_15_MASK                      0x18000
#define D0F2xFC_x07_L1_L1NwEn_OFFSET                            17
#define D0F2xFC_x07_L1_L1NwEn_WIDTH                             1
#define D0F2xFC_x07_L1_L1NwEn_MASK                              0x20000
#define D0F2xFC_x07_L1_L1NwEn_VALUE                             0x1
#define D0F2xFC_x07_L1_Reserved_31_18_OFFSET                    18
#define D0F2xFC_x07_L1_Reserved_31_18_WIDTH                     14
#define D0F2xFC_x07_L1_Reserved_31_18_MASK                      0xfffc0000

/// D0F2xFC_x07_L1
typedef union {
  struct {                                                              ///<
    UINT32                                           PhantomFuncDis:1 ; ///<
    UINT32                                            Reserved_10_1:10; ///<
    UINT32                                          SpecReqFilterEn:1 ; ///<
    UINT32                                              AtsSeqNumEn:1 ; ///<
    UINT32                                           Reserved_13_13:1 ; ///<
    UINT32                                    AtsPhysPageOverlapDis:1 ; ///<
    UINT32                                           Reserved_16_15:2 ; ///<
    UINT32                                                   L1NwEn:1 ; ///<
    UINT32                                           Reserved_31_18:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x07_L1_STRUCT;

// **** D0F2xFC_x09_L1 Register Definition ****
// Address
#define D0F2xFC_x09_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x09)

// Type
#define D0F2xFC_x09_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x09_L1_SbLocatedPort_OFFSET                     0
#define D0F2xFC_x09_L1_SbLocatedPort_WIDTH                      16
#define D0F2xFC_x09_L1_SbLocatedPort_MASK                       0xffff
#define D0F2xFC_x09_L1_SbLocatedPort_VALUE                      0x1
#define D0F2xFC_x09_L1_SbLocatedCore_OFFSET                     16
#define D0F2xFC_x09_L1_SbLocatedCore_WIDTH                      16
#define D0F2xFC_x09_L1_SbLocatedCore_MASK                       0xffff0000

/// D0F2xFC_x09_L1
typedef union {
  struct {                                                              ///<
    UINT32                                            SbLocatedPort:16; ///<
    UINT32                                            SbLocatedCore:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x09_L1_STRUCT;

// **** D0F2xFC_x0C_L1 Register Definition ****
// Address
#define D0F2xFC_x0C_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x0C)

// Type
#define D0F2xFC_x0C_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x0C_L1_UnfilterDis_OFFSET                       0
#define D0F2xFC_x0C_L1_UnfilterDis_WIDTH                        1
#define D0F2xFC_x0C_L1_UnfilterDis_MASK                         0x1
#define D0F2xFC_x0C_L1_FragmentDis_OFFSET                       1
#define D0F2xFC_x0C_L1_FragmentDis_WIDTH                        1
#define D0F2xFC_x0C_L1_FragmentDis_MASK                         0x2
#define D0F2xFC_x0C_L1_CacheirOnly_OFFSET                       2
#define D0F2xFC_x0C_L1_CacheirOnly_WIDTH                        1
#define D0F2xFC_x0C_L1_CacheirOnly_MASK                         0x4
#define D0F2xFC_x0C_L1_CacheiwOnly_OFFSET                       3
#define D0F2xFC_x0C_L1_CacheiwOnly_WIDTH                        1
#define D0F2xFC_x0C_L1_CacheiwOnly_MASK                         0x8
#define D0F2xFC_x0C_L1_Reserved_4_4_OFFSET                      4
#define D0F2xFC_x0C_L1_Reserved_4_4_WIDTH                       1
#define D0F2xFC_x0C_L1_Reserved_4_4_MASK                        0x10
#define D0F2xFC_x0C_L1_ReplacementSel_OFFSET                    5
#define D0F2xFC_x0C_L1_ReplacementSel_WIDTH                     1
#define D0F2xFC_x0C_L1_ReplacementSel_MASK                      0x20
#define D0F2xFC_x0C_L1_Reserved_7_6_OFFSET                      6
#define D0F2xFC_x0C_L1_Reserved_7_6_WIDTH                       2
#define D0F2xFC_x0C_L1_Reserved_7_6_MASK                        0xc0
#define D0F2xFC_x0C_L1_L2Credits_OFFSET                         8
#define D0F2xFC_x0C_L1_L2Credits_WIDTH                          6
#define D0F2xFC_x0C_L1_L2Credits_MASK                           0x3f00
#define D0F2xFC_x0C_L1_Reserved_19_14_OFFSET                    14
#define D0F2xFC_x0C_L1_Reserved_19_14_WIDTH                     6
#define D0F2xFC_x0C_L1_Reserved_19_14_MASK                      0xfc000
#define D0F2xFC_x0C_L1_L1Banks_OFFSET                           20
#define D0F2xFC_x0C_L1_L1Banks_WIDTH                            2
#define D0F2xFC_x0C_L1_L1Banks_MASK                             0x300000
#define D0F2xFC_x0C_L1_Reserved_23_22_OFFSET                    22
#define D0F2xFC_x0C_L1_Reserved_23_22_WIDTH                     2
#define D0F2xFC_x0C_L1_Reserved_23_22_MASK                      0xc00000
#define D0F2xFC_x0C_L1_L1Entries_OFFSET                         24
#define D0F2xFC_x0C_L1_L1Entries_WIDTH                          4
#define D0F2xFC_x0C_L1_L1Entries_MASK                           0xf000000
#define D0F2xFC_x0C_L1_L1VirtOrderQueues_OFFSET                 28
#define D0F2xFC_x0C_L1_L1VirtOrderQueues_WIDTH                  3
#define D0F2xFC_x0C_L1_L1VirtOrderQueues_MASK                   0x70000000
#define D0F2xFC_x0C_L1_Reserved_31_31_OFFSET                    31
#define D0F2xFC_x0C_L1_Reserved_31_31_WIDTH                     1
#define D0F2xFC_x0C_L1_Reserved_31_31_MASK                      0x80000000

/// D0F2xFC_x0C_L1
typedef union {
  struct {                                                              ///<
    UINT32                                              UnfilterDis:1 ; ///<
    UINT32                                              FragmentDis:1 ; ///<
    UINT32                                              CacheirOnly:1 ; ///<
    UINT32                                              CacheiwOnly:1 ; ///<
    UINT32                                             Reserved_4_4:1 ; ///<
    UINT32                                           ReplacementSel:1 ; ///<
    UINT32                                             Reserved_7_6:2 ; ///<
    UINT32                                                L2Credits:6 ; ///<
    UINT32                                           Reserved_19_14:6 ; ///<
    UINT32                                                  L1Banks:2 ; ///<
    UINT32                                           Reserved_23_22:2 ; ///<
    UINT32                                                L1Entries:4 ; ///<
    UINT32                                        L1VirtOrderQueues:3 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x0C_L1_STRUCT;

// **** D0F2xFC_x0D_L1 Register Definition ****
// Address
#define D0F2xFC_x0D_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x0D)

// Type
#define D0F2xFC_x0D_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x0D_L1_VOQPortBits_OFFSET                       0
#define D0F2xFC_x0D_L1_VOQPortBits_WIDTH                        3
#define D0F2xFC_x0D_L1_VOQPortBits_MASK                         0x7
#define D0F2xFC_x0D_L1_Reserved_3_3_OFFSET                      3
#define D0F2xFC_x0D_L1_Reserved_3_3_WIDTH                       1
#define D0F2xFC_x0D_L1_Reserved_3_3_MASK                        0x8
#define D0F2xFC_x0D_L1_VOQFuncBits_OFFSET                       4
#define D0F2xFC_x0D_L1_VOQFuncBits_WIDTH                        3
#define D0F2xFC_x0D_L1_VOQFuncBits_MASK                         0x70
#define D0F2xFC_x0D_L1_Reserved_7_7_OFFSET                      7
#define D0F2xFC_x0D_L1_Reserved_7_7_WIDTH                       1
#define D0F2xFC_x0D_L1_Reserved_7_7_MASK                        0x80
#define D0F2xFC_x0D_L1_VOQXorMode_OFFSET                        8
#define D0F2xFC_x0D_L1_VOQXorMode_WIDTH                         1
#define D0F2xFC_x0D_L1_VOQXorMode_MASK                          0x100
#define D0F2xFC_x0D_L1_CacheByPass_OFFSET                       9
#define D0F2xFC_x0D_L1_CacheByPass_WIDTH                        1
#define D0F2xFC_x0D_L1_CacheByPass_MASK                         0x200
#define D0F2xFC_x0D_L1_L1CacheParityEn_OFFSET                   10
#define D0F2xFC_x0D_L1_L1CacheParityEn_WIDTH                    1
#define D0F2xFC_x0D_L1_L1CacheParityEn_MASK                     0x400
#define D0F2xFC_x0D_L1_L1ParityEn_OFFSET                        11
#define D0F2xFC_x0D_L1_L1ParityEn_WIDTH                         1
#define D0F2xFC_x0D_L1_L1ParityEn_MASK                          0x800
#define D0F2xFC_x0D_L1_L1DTEDis_OFFSET                          12
#define D0F2xFC_x0D_L1_L1DTEDis_WIDTH                           1
#define D0F2xFC_x0D_L1_L1DTEDis_MASK                            0x1000
#define D0F2xFC_x0D_L1_BlockL1Dis_OFFSET                        13
#define D0F2xFC_x0D_L1_BlockL1Dis_WIDTH                         1
#define D0F2xFC_x0D_L1_BlockL1Dis_MASK                          0x2000
#define D0F2xFC_x0D_L1_WqEntrydis_OFFSET                        14
#define D0F2xFC_x0D_L1_WqEntrydis_WIDTH                         5
#define D0F2xFC_x0D_L1_WqEntrydis_MASK                          0x7c000
#define D0F2xFC_x0D_L1_AtsNobufferInsert_OFFSET                 19
#define D0F2xFC_x0D_L1_AtsNobufferInsert_WIDTH                  1
#define D0F2xFC_x0D_L1_AtsNobufferInsert_MASK                   0x80000
#define D0F2xFC_x0D_L1_SndFilterDis_OFFSET                      20
#define D0F2xFC_x0D_L1_SndFilterDis_WIDTH                       1
#define D0F2xFC_x0D_L1_SndFilterDis_MASK                        0x100000
#define D0F2xFC_x0D_L1_L1orderEn_OFFSET                         21
#define D0F2xFC_x0D_L1_L1orderEn_WIDTH                          1
#define D0F2xFC_x0D_L1_L1orderEn_MASK                           0x200000
#define D0F2xFC_x0D_L1_L1CacheInvAllEn_OFFSET                   22
#define D0F2xFC_x0D_L1_L1CacheInvAllEn_WIDTH                    1
#define D0F2xFC_x0D_L1_L1CacheInvAllEn_MASK                     0x400000
#define D0F2xFC_x0D_L1_SelectTimeoutPulse_OFFSET                23
#define D0F2xFC_x0D_L1_SelectTimeoutPulse_WIDTH                 3
#define D0F2xFC_x0D_L1_SelectTimeoutPulse_MASK                  0x3800000
#define D0F2xFC_x0D_L1_L1CacheSelReqid_OFFSET                   26
#define D0F2xFC_x0D_L1_L1CacheSelReqid_WIDTH                    1
#define D0F2xFC_x0D_L1_L1CacheSelReqid_MASK                     0x4000000
#define D0F2xFC_x0D_L1_L1CacheSelInterleave_OFFSET              27
#define D0F2xFC_x0D_L1_L1CacheSelInterleave_WIDTH               1
#define D0F2xFC_x0D_L1_L1CacheSelInterleave_MASK                0x8000000
#define D0F2xFC_x0D_L1_PretransNovaFilteren_OFFSET              28
#define D0F2xFC_x0D_L1_PretransNovaFilteren_WIDTH               1
#define D0F2xFC_x0D_L1_PretransNovaFilteren_MASK                0x10000000
#define D0F2xFC_x0D_L1_Untrans2mFilteren_OFFSET                 29
#define D0F2xFC_x0D_L1_Untrans2mFilteren_WIDTH                  1
#define D0F2xFC_x0D_L1_Untrans2mFilteren_MASK                   0x20000000
#define D0F2xFC_x0D_L1_L1DebugCntrMode_OFFSET                   30
#define D0F2xFC_x0D_L1_L1DebugCntrMode_WIDTH                    1
#define D0F2xFC_x0D_L1_L1DebugCntrMode_MASK                     0x40000000
#define D0F2xFC_x0D_L1_Reserved_31_31_OFFSET                    31
#define D0F2xFC_x0D_L1_Reserved_31_31_WIDTH                     1
#define D0F2xFC_x0D_L1_Reserved_31_31_MASK                      0x80000000

/// D0F2xFC_x0D_L1
typedef union {
  struct {                                                              ///<
    UINT32                                              VOQPortBits:3 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                              VOQFuncBits:3 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                               VOQXorMode:1 ; ///<
    UINT32                                              CacheByPass:1 ; ///<
    UINT32                                          L1CacheParityEn:1 ; ///<
    UINT32                                               L1ParityEn:1 ; ///<
    UINT32                                                 L1DTEDis:1 ; ///<
    UINT32                                               BlockL1Dis:1 ; ///<
    UINT32                                               WqEntrydis:5 ; ///<
    UINT32                                        AtsNobufferInsert:1 ; ///<
    UINT32                                             SndFilterDis:1 ; ///<
    UINT32                                                L1orderEn:1 ; ///<
    UINT32                                          L1CacheInvAllEn:1 ; ///<
    UINT32                                       SelectTimeoutPulse:3 ; ///<
    UINT32                                          L1CacheSelReqid:1 ; ///<
    UINT32                                     L1CacheSelInterleave:1 ; ///<
    UINT32                                     PretransNovaFilteren:1 ; ///<
    UINT32                                        Untrans2mFilteren:1 ; ///<
    UINT32                                          L1DebugCntrMode:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x0D_L1_STRUCT;

// **** D0F2xFC_x27_L1 Register Definition ****
// Address
#define D0F2xFC_x27_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x27)

// Type
#define D0F2xFC_x27_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x27_L1_Debug_sticky_bits_OFFSET                 0
#define D0F2xFC_x27_L1_Debug_sticky_bits_WIDTH                  8
#define D0F2xFC_x27_L1_Debug_sticky_bits_MASK                   0xff
#define D0F2xFC_x27_L1_Reserved_OFFSET                          8
#define D0F2xFC_x27_L1_Reserved_WIDTH                           24
#define D0F2xFC_x27_L1_Reserved_MASK                            0xffffff00

/// D0F2xFC_x27_L1
typedef union {
  struct {                                                              ///<
    UINT32                                        Debug_sticky_bits:8 ; ///<
    UINT32                                                 Reserved:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x27_L1_STRUCT;


// **** D0F2xFC_x32_L1 Register Definition ****
// Address
#define D0F2xFC_x32_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x32)

// Type
#define D0F2xFC_x32_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x32_L1_AtsMultipleRespEn_OFFSET                 0
#define D0F2xFC_x32_L1_AtsMultipleRespEn_WIDTH                  1
#define D0F2xFC_x32_L1_AtsMultipleRespEn_MASK                   0x1
#define D0F2xFC_x32_L1_AtsMultipleL1toL2En_OFFSET               1
#define D0F2xFC_x32_L1_AtsMultipleL1toL2En_WIDTH                1
#define D0F2xFC_x32_L1_AtsMultipleL1toL2En_MASK                 0x2
#define D0F2xFC_x32_L1_TimeoutPulseExtEn_OFFSET                 2
#define D0F2xFC_x32_L1_TimeoutPulseExtEn_WIDTH                  1
#define D0F2xFC_x32_L1_TimeoutPulseExtEn_MASK                   0x4
#define D0F2xFC_x32_L1_TlpprefixerrEn_OFFSET                    3
#define D0F2xFC_x32_L1_TlpprefixerrEn_WIDTH                     1
#define D0F2xFC_x32_L1_TlpprefixerrEn_MASK                      0x8
#define D0F2xFC_x32_L1_DmaBufCredits_OFFSET                     4
#define D0F2xFC_x32_L1_DmaBufCredits_WIDTH                      6
#define D0F2xFC_x32_L1_DmaBufCredits_MASK                       0x3f0
#define D0F2xFC_x32_L1_DmaBufMaxNpCred_OFFSET                   10
#define D0F2xFC_x32_L1_DmaBufMaxNpCred_WIDTH                    6
#define D0F2xFC_x32_L1_DmaBufMaxNpCred_MASK                     0xfc00
#define D0F2xFC_x32_L1_DmaNpHaltDis_OFFSET                      16
#define D0F2xFC_x32_L1_DmaNpHaltDis_WIDTH                       1
#define D0F2xFC_x32_L1_DmaNpHaltDis_MASK                        0x10000
#define D0F2xFC_x32_L1_ForceDmaAttrLow_OFFSET                   17
#define D0F2xFC_x32_L1_ForceDmaAttrLow_WIDTH                    3
#define D0F2xFC_x32_L1_ForceDmaAttrLow_MASK                     0xe0000
#define D0F2xFC_x32_L1_Reserved_31_20_OFFSET                    20
#define D0F2xFC_x32_L1_Reserved_31_20_WIDTH                     12
#define D0F2xFC_x32_L1_Reserved_31_20_MASK                      0xfff00000

/// D0F2xFC_x32_L1
typedef union {
  struct {                                                              ///<
    UINT32                                        AtsMultipleRespEn:1 ; ///<
    UINT32                                      AtsMultipleL1toL2En:1 ; ///<
    UINT32                                        TimeoutPulseExtEn:1 ; ///<
    UINT32                                           TlpprefixerrEn:1 ; ///<
    UINT32                                            DmaBufCredits:6 ; ///<
    UINT32                                          DmaBufMaxNpCred:6 ; ///<
    UINT32                                             DmaNpHaltDis:1 ; ///<
    UINT32                                          ForceDmaAttrLow:3 ; ///<
    UINT32                                           Reserved_31_20:12; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x32_L1_STRUCT;

// **** D0F2xFC_x33_L1 Register Definition ****
// Address
#define D0F2xFC_x33_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x33)

// Type
#define D0F2xFC_x33_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x33_L1_L1ClkgateLen_OFFSET                      0
#define D0F2xFC_x33_L1_L1ClkgateLen_WIDTH                       2
#define D0F2xFC_x33_L1_L1ClkgateLen_MASK                        0x3
#define D0F2xFC_x33_L1_Reserved_3_2_OFFSET                      2
#define D0F2xFC_x33_L1_Reserved_3_2_WIDTH                       2
#define D0F2xFC_x33_L1_Reserved_3_2_MASK                        0xc
#define D0F2xFC_x33_L1_L1DmaClkgateEn_OFFSET                    4
#define D0F2xFC_x33_L1_L1DmaClkgateEn_WIDTH                     1
#define D0F2xFC_x33_L1_L1DmaClkgateEn_MASK                      0x10
#define D0F2xFC_x33_L1_L1DmaClkgateEn_VALUE                     0x1
#define D0F2xFC_x33_L1_L1CacheClkgateEn_OFFSET                  5
#define D0F2xFC_x33_L1_L1CacheClkgateEn_WIDTH                   1
#define D0F2xFC_x33_L1_L1CacheClkgateEn_MASK                    0x20
#define D0F2xFC_x33_L1_L1CacheClkgateEn_VALUE                   0x1
#define D0F2xFC_x33_L1_L1CpslvClkgateEn_OFFSET                  6
#define D0F2xFC_x33_L1_L1CpslvClkgateEn_WIDTH                   1
#define D0F2xFC_x33_L1_L1CpslvClkgateEn_MASK                    0x40
#define D0F2xFC_x33_L1_L1CpslvClkgateEn_VALUE                   0x1
#define D0F2xFC_x33_L1_L1DmaInputClkgateEn_OFFSET               7
#define D0F2xFC_x33_L1_L1DmaInputClkgateEn_WIDTH                1
#define D0F2xFC_x33_L1_L1DmaInputClkgateEn_MASK                 0x80
#define D0F2xFC_x33_L1_L1DmaInputClkgateEn_VALUE                0x1
#define D0F2xFC_x33_L1_L1PerfClkgateEn_OFFSET                   8
#define D0F2xFC_x33_L1_L1PerfClkgateEn_WIDTH                    1
#define D0F2xFC_x33_L1_L1PerfClkgateEn_MASK                     0x100
#define D0F2xFC_x33_L1_L1PerfClkgateEn_VALUE                    0x1
#define D0F2xFC_x33_L1_L1MemoryClkgateEn_OFFSET                 9
#define D0F2xFC_x33_L1_L1MemoryClkgateEn_WIDTH                  1
#define D0F2xFC_x33_L1_L1MemoryClkgateEn_MASK                   0x200
#define D0F2xFC_x33_L1_L1MemoryClkgateEn_VALUE                  0x1
#define D0F2xFC_x33_L1_L1RegClkgateEn_OFFSET                    10
#define D0F2xFC_x33_L1_L1RegClkgateEn_WIDTH                     1
#define D0F2xFC_x33_L1_L1RegClkgateEn_MASK                      0x400
#define D0F2xFC_x33_L1_L1RegClkgateEn_VALUE                     0x1
#define D0F2xFC_x33_L1_L1HostreqClkgateEn_OFFSET                11
#define D0F2xFC_x33_L1_L1HostreqClkgateEn_WIDTH                 1
#define D0F2xFC_x33_L1_L1HostreqClkgateEn_MASK                  0x800
#define D0F2xFC_x33_L1_L1HostreqClkgateEn_VALUE                 0x1
#define D0F2xFC_x33_L1_Reserved_30_12_OFFSET                    12
#define D0F2xFC_x33_L1_Reserved_30_12_WIDTH                     19
#define D0F2xFC_x33_L1_Reserved_30_12_MASK                      0x7ffff000
#define D0F2xFC_x33_L1_L1L2ClkgateEn_OFFSET                     31
#define D0F2xFC_x33_L1_L1L2ClkgateEn_WIDTH                      1
#define D0F2xFC_x33_L1_L1L2ClkgateEn_MASK                       0x80000000
#define D0F2xFC_x33_L1_L1L2ClkgateEn_VALUE                      0x1

/// D0F2xFC_x33_L1
typedef union {
  struct {                                                              ///<
    UINT32                                             L1ClkgateLen:2 ; ///<
    UINT32                                             Reserved_3_2:2 ; ///<
    UINT32                                           L1DmaClkgateEn:1 ; ///<
    UINT32                                         L1CacheClkgateEn:1 ; ///<
    UINT32                                         L1CpslvClkgateEn:1 ; ///<
    UINT32                                      L1DmaInputClkgateEn:1 ; ///<
    UINT32                                          L1PerfClkgateEn:1 ; ///<
    UINT32                                        L1MemoryClkgateEn:1 ; ///<
    UINT32                                           L1RegClkgateEn:1 ; ///<
    UINT32                                       L1HostreqClkgateEn:1 ; ///<
    UINT32                                           Reserved_30_12:19; ///<
    UINT32                                            L1L2ClkgateEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x33_L1_STRUCT;

// **** D0F2xFC_x39_L1 Register Definition ****
// Address
#define D0F2xFC_x39_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x39)

// Type
#define D0F2xFC_x39_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x39_L1_LSEn_OFFSET                              0
#define D0F2xFC_x39_L1_LSEn_WIDTH                               1
#define D0F2xFC_x39_L1_LSEn_MASK                                0x1
#define D0F2xFC_x39_L1_DSEn_OFFSET                              1
#define D0F2xFC_x39_L1_DSEn_WIDTH                               1
#define D0F2xFC_x39_L1_DSEn_MASK                                0x2
#define D0F2xFC_x39_L1_SDEn_OFFSET                              2
#define D0F2xFC_x39_L1_SDEn_WIDTH                               1
#define D0F2xFC_x39_L1_SDEn_MASK                                0x4
#define D0F2xFC_x39_L1_Reserved_31_3_OFFSET                     3
#define D0F2xFC_x39_L1_Reserved_31_3_WIDTH                      29
#define D0F2xFC_x39_L1_Reserved_31_3_MASK                       0xfffffff8

/// D0F2xFC_x39_L1
typedef union {
  struct {                                                              ///<
    UINT32                                                     LSEn:1 ; ///<
    UINT32                                                     DSEn:1 ; ///<
    UINT32                                                     SDEn:1 ; ///<
    UINT32                                            Reserved_31_3:29; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x39_L1_STRUCT;

// **** D0F2xFC_x3A_L1 Register Definition ****
// Address
#define D0F2xFC_x3A_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x3A)

// Type
#define D0F2xFC_x3A_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x3A_L1_LSThres_OFFSET                           0
#define D0F2xFC_x3A_L1_LSThres_WIDTH                            32
#define D0F2xFC_x3A_L1_LSThres_MASK                             0xffffffff

/// D0F2xFC_x3A_L1
typedef union {
  struct {                                                              ///<
    UINT32                                                  LSThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x3A_L1_STRUCT;

// **** D0F2xFC_x3B_L1 Register Definition ****
// Address
#define D0F2xFC_x3B_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x3B)

// Type
#define D0F2xFC_x3B_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x3B_L1_DSThres_OFFSET                           0
#define D0F2xFC_x3B_L1_DSThres_WIDTH                            32
#define D0F2xFC_x3B_L1_DSThres_MASK                             0xffffffff

/// D0F2xFC_x3B_L1
typedef union {
  struct {                                                              ///<
    UINT32                                                  DSThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x3B_L1_STRUCT;

// **** D0F2xFC_x3C_L1i2_L1 Register Definition ****
// Address
#define D0F2xFC_x3C_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x3C)

// Type
#define D0F2xFC_x3C_L1_TYPE                                     TYPE_D0F2xFC
// Field Data
#define D0F2xFC_x3C_L1_SDThres_OFFSET                           0
#define D0F2xFC_x3C_L1_SDThres_WIDTH                            32
#define D0F2xFC_x3C_L1_SDThres_MASK                             0xffffffff

/// D0F2xFC_x3C_L1
typedef union {
  struct {                                                              ///<
    UINT32                                                  SDThres:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F2xFC_x3C_L1_STRUCT;

// **** D0F2xFC_x3D_L1 Register Definition ****
// Address
#define D0F2xFC_x3D_L1_ADDRESS(Sel)                             ((Sel << 16) | 0x3D)

// Type
#define D0F2xFC_x3D_L1_TYPE                                     TYPE_D0F2xFC


// **** D18F0x110 Register Definition ****
// Address
#define D18F0x110_ADDRESS                                       0x110

// Type
#define D18F0x110_TYPE                                          TYPE_D18F0
// Field Data
#define D18F0x110_Reserved_0_0_OFFSET                           0
#define D18F0x110_Reserved_0_0_WIDTH                            1
#define D18F0x110_Reserved_0_0_MASK                             0x1
#define D18F0x110_ClumpEn_OFFSET                                1
#define D18F0x110_ClumpEn_WIDTH                                 31
#define D18F0x110_ClumpEn_MASK                                  0xfffffffe

/// D18F0x110
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                                  ClumpEn:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F0x110_STRUCT;

// **** D18F1x10C Register Definition ****
// Address
#define D18F1x10C_ADDRESS                                       0x10c

// Type
#define D18F1x10C_TYPE                                          TYPE_D18F1
// Field Data
#define D18F1x10C_DctCfgSel_OFFSET                              0
#define D18F1x10C_DctCfgSel_WIDTH                               3
#define D18F1x10C_DctCfgSel_MASK                                0x7
#define D18F1x10C_Unused_5_3_OFFSET                             3
#define D18F1x10C_Unused_5_3_WIDTH                              3
#define D18F1x10C_Unused_5_3_MASK                               0x38
#define D18F1x10C_Unused_6_6_OFFSET                             6
#define D18F1x10C_Unused_6_6_WIDTH                              1
#define D18F1x10C_Unused_6_6_MASK                               0x40
#define D18F1x10C_DctCfgBcEn_OFFSET                             7
#define D18F1x10C_DctCfgBcEn_WIDTH                              1
#define D18F1x10C_DctCfgBcEn_MASK                               0x80
#define D18F1x10C_Reserved_31_8_OFFSET                          8
#define D18F1x10C_Reserved_31_8_WIDTH                           24
#define D18F1x10C_Reserved_31_8_MASK                            0xffffff00

/// D18F1x10C
typedef union {
  struct {                                                              ///<
    UINT32                                                DctCfgSel:3 ; ///<
    UINT32                                               Unused_5_3:3 ; ///<
    UINT32                                               Unused_6_6:1 ; ///<
    UINT32                                               DctCfgBcEn:1 ; ///<
    UINT32                                            Reserved_31_8:24; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F1x10C_STRUCT;

// **** D18F3x64 Register Definition ****
// Address
#define D18F3x64_ADDRESS                                        0x64

// Type
#define D18F3x64_TYPE                                           TYPE_D18F3
// Field Data
#define D18F3x64_HTC_EN_OFFSET                                  0
#define D18F3x64_HTC_EN_WIDTH                                   1
#define D18F3x64_HTC_EN_MASK                                    0x1
#define D18F3x64_HTC_EN_VALUE                                   0x0
#define D18F3x64_RSVD0_OFFSET                                   1
#define D18F3x64_RSVD0_WIDTH                                    1
#define D18F3x64_RSVD0_MASK                                     0x2
#define D18F3x64_HTC_P_STATE_EN_OFFSET                          2
#define D18F3x64_HTC_P_STATE_EN_WIDTH                           1
#define D18F3x64_HTC_P_STATE_EN_MASK                            0x4
#define D18F3x64_RSVD1_OFFSET                                   3
#define D18F3x64_RSVD1_WIDTH                                    1
#define D18F3x64_RSVD1_MASK                                     0x8
#define D18F3x64_HTC_ACTIVE_OFFSET                              4
#define D18F3x64_HTC_ACTIVE_WIDTH                               1
#define D18F3x64_HTC_ACTIVE_MASK                                0x10
#define D18F3x64_HTC_ACTIVE_LOG_OFFSET                          5
#define D18F3x64_HTC_ACTIVE_LOG_WIDTH                           1
#define D18F3x64_HTC_ACTIVE_LOG_MASK                            0x20
#define D18F3x64_HTC_APIC_HI_EN_OFFSET                          6
#define D18F3x64_HTC_APIC_HI_EN_WIDTH                           1
#define D18F3x64_HTC_APIC_HI_EN_MASK                            0x40
#define D18F3x64_HTC_APIC_LO_EN_OFFSET                          7
#define D18F3x64_HTC_APIC_LO_EN_WIDTH                           1
#define D18F3x64_HTC_APIC_LO_EN_MASK                            0x80
#define D18F3x64_HTC_DIAG_OFFSET                                8
#define D18F3x64_HTC_DIAG_WIDTH                                 1
#define D18F3x64_HTC_DIAG_MASK                                  0x100
#define D18F3x64_DIS_PROCHOT_PIN_OFFSET                         9
#define D18F3x64_DIS_PROCHOT_PIN_WIDTH                          1
#define D18F3x64_DIS_PROCHOT_PIN_MASK                           0x200
#define D18F3x64_HTC_TO_GNB_EN_OFFSET                           10
#define D18F3x64_HTC_TO_GNB_EN_WIDTH                            1
#define D18F3x64_HTC_TO_GNB_EN_MASK                             0x400
#define D18F3x64_PROCHOT_TO_GNB_EN_OFFSET                       11
#define D18F3x64_PROCHOT_TO_GNB_EN_WIDTH                        1
#define D18F3x64_PROCHOT_TO_GNB_EN_MASK                         0x800
#define D18F3x64_Reserved_15_12_OFFSET                          12
#define D18F3x64_Reserved_15_12_WIDTH                           4
#define D18F3x64_Reserved_15_12_MASK                            0xf000
#define D18F3x64_HTC_TMP_LMT_OFFSET                             16
#define D18F3x64_HTC_TMP_LMT_WIDTH                              7
#define D18F3x64_HTC_TMP_LMT_MASK                               0x7f0000
#define D18F3x64_HTC_SLEW_SEL_OFFSET                            23
#define D18F3x64_HTC_SLEW_SEL_WIDTH                             1
#define D18F3x64_HTC_SLEW_SEL_MASK                              0x800000
#define D18F3x64_HTC_HYST_LMT_OFFSET                            24
#define D18F3x64_HTC_HYST_LMT_WIDTH                             4
#define D18F3x64_HTC_HYST_LMT_MASK                              0xf000000
#define D18F3x64_HTC_PSTATE_LIMIT_OFFSET                        28
#define D18F3x64_HTC_PSTATE_LIMIT_WIDTH                         3
#define D18F3x64_HTC_PSTATE_LIMIT_MASK                          0x70000000
#define D18F3x64_Reserved_31_31_OFFSET                          31
#define D18F3x64_Reserved_31_31_WIDTH                           1
#define D18F3x64_Reserved_31_31_MASK                            0x80000000

/// D18F3x64
typedef union {
  struct {                                                              ///<
    UINT32                                                   HTC_EN:1 ; ///<
    UINT32                                                    RSVD0:1 ; ///<
    UINT32                                           HTC_P_STATE_EN:1 ; ///<
    UINT32                                                    RSVD1:1 ; ///<
    UINT32                                               HTC_ACTIVE:1 ; ///<
    UINT32                                           HTC_ACTIVE_LOG:1 ; ///<
    UINT32                                           HTC_APIC_HI_EN:1 ; ///<
    UINT32                                           HTC_APIC_LO_EN:1 ; ///<
    UINT32                                                 HTC_DIAG:1 ; ///<
    UINT32                                          DIS_PROCHOT_PIN:1 ; ///<
    UINT32                                            HTC_TO_GNB_EN:1 ; ///<
    UINT32                                        PROCHOT_TO_GNB_EN:1 ; ///<
    UINT32                                           Reserved_15_12:4 ; ///<
    UINT32                                              HTC_TMP_LMT:7 ; ///<
    UINT32                                             HTC_SLEW_SEL:1 ; ///<
    UINT32                                             HTC_HYST_LMT:4 ; ///<
    UINT32                                         HTC_PSTATE_LIMIT:3 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F3x64_STRUCT;

// **** D18F3xA0 Register Definition ****
// Address
#define D18F3xA0_ADDRESS                                        0xa0

// Type
#define D18F3xA0_TYPE                                           TYPE_D18F3
// Field Data
#define D18F3xA0_Reserved_27_0_OFFSET                           0
#define D18F3xA0_Reserved_27_0_WIDTH                            28
#define D18F3xA0_Reserved_27_0_MASK                             0xfffffff
#define D18F3xA0_NbPstateForce_OFFSET                           28
#define D18F3xA0_NbPstateForce_WIDTH                            1
#define D18F3xA0_NbPstateForce_MASK                             0x10000000
#define D18F3xA0_Reserved_29_29_OFFSET                          29
#define D18F3xA0_Reserved_29_29_WIDTH                           1
#define D18F3xA0_Reserved_29_29_MASK                            0x20000000
#define D18F3xA0_DualVdd_OFFSET                                 30
#define D18F3xA0_DualVdd_WIDTH                                  1
#define D18F3xA0_DualVdd_MASK                                   0x40000000
#define D18F3xA0_Reserved_31_31_OFFSET                          31
#define D18F3xA0_Reserved_31_31_WIDTH                           1
#define D18F3xA0_Reserved_31_31_MASK                            0x80000000

/// D18F3xA0
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved_27_0:28; ///<
    UINT32                                            NbPstateForce:1 ; ///<
    UINT32                                           Reserved_29_29:1 ; ///<
    UINT32                                                  DualVdd:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F3xA0_STRUCT;

// **** D18F4x1B8 Register Definition ****
// Address
#define D18F4x1B8_ADDRESS                                       0x1b8

// Type
#define D18F4x1B8_TYPE                                          TYPE_D18F4
// Field Data
#define D18F4x1B8_ProcessorTdp_OFFSET                           0
#define D18F4x1B8_ProcessorTdp_WIDTH                            16
#define D18F4x1B8_ProcessorTdp_MASK                             0xffff
#define D18F4x1B8_BaseTdp_OFFSET                                16
#define D18F4x1B8_BaseTdp_WIDTH                                 16
#define D18F4x1B8_BaseTdp_MASK                                  0xffff0000

/// D18F4x1B8
typedef union {
  struct {                                                              ///<
    UINT32                                             ProcessorTdp:16; ///<
    UINT32                                                  BaseTdp:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F4x1B8_STRUCT;

// **** D18F5xE8 Register Definition ****
// Address
#define D18F5xE8_ADDRESS                                        0xe8

// Type
#define D18F5xE8_TYPE                                           TYPE_D18F5
// Field Data
#define D18F5xE8_Tdp2Watt_15_6__OFFSET                          0
#define D18F5xE8_Tdp2Watt_15_6__WIDTH                           10
#define D18F5xE8_Tdp2Watt_15_6__MASK                            0x3ff
#define D18F5xE8_Tdp2Watt_5_0__OFFSET                           10
#define D18F5xE8_Tdp2Watt_5_0__WIDTH                            6
#define D18F5xE8_Tdp2Watt_5_0__MASK                             0xfc00
#define D18F5xE8_ApmTdpLimit_OFFSET                             16
#define D18F5xE8_ApmTdpLimit_WIDTH                              16
#define D18F5xE8_ApmTdpLimit_MASK                               0xffff0000

/// D18F5xE8
typedef union {
  struct {                                                              ///<
    UINT32                                           Tdp2Watt_15_6_:10; ///<
    UINT32                                            Tdp2Watt_5_0_:6 ; ///<
    UINT32                                              ApmTdpLimit:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5xE8_STRUCT;

// **** D18F5x160 Register Definition ****
// Address
#define D18F5x160_ADDRESS                                       0x160

// Type
#define D18F5x160_TYPE                                          TYPE_D18F5
// Field Data
#define D18F5x160_NbPstateEn_OFFSET                             0
#define D18F5x160_NbPstateEn_WIDTH                              1
#define D18F5x160_NbPstateEn_MASK                               0x1
#define D18F5x160_NbFid_5_0__OFFSET                             1
#define D18F5x160_NbFid_5_0__WIDTH                              6
#define D18F5x160_NbFid_5_0__MASK                               0x7e
#define D18F5x160_NbDid_OFFSET                                  7
#define D18F5x160_NbDid_WIDTH                                   1
#define D18F5x160_NbDid_MASK                                    0x80
#define D18F5x160_Reserved_9_8_OFFSET                           8
#define D18F5x160_Reserved_9_8_WIDTH                            2
#define D18F5x160_Reserved_9_8_MASK                             0x300
#define D18F5x160_NbVid_6_0__OFFSET                             10
#define D18F5x160_NbVid_6_0__WIDTH                              7
#define D18F5x160_NbVid_6_0__MASK                               0x1fc00
#define D18F5x160_Reserved_17_17_OFFSET                         17
#define D18F5x160_Reserved_17_17_WIDTH                          1
#define D18F5x160_Reserved_17_17_MASK                           0x20000
#define D18F5x160_MemPstate_OFFSET                              18
#define D18F5x160_MemPstate_WIDTH                               1
#define D18F5x160_MemPstate_MASK                                0x40000
#define D18F5x160_Reserved_19_19_OFFSET                         19
#define D18F5x160_Reserved_19_19_WIDTH                          1
#define D18F5x160_Reserved_19_19_MASK                           0x80000
#define D18F5x160_NbFid_6__OFFSET                               20
#define D18F5x160_NbFid_6__WIDTH                                1
#define D18F5x160_NbFid_6__MASK                                 0x100000
#define D18F5x160_NbVid_7__OFFSET                               21
#define D18F5x160_NbVid_7__WIDTH                                1
#define D18F5x160_NbVid_7__MASK                                 0x200000
#define D18F5x160_NbIddDiv_OFFSET                               22
#define D18F5x160_NbIddDiv_WIDTH                                2
#define D18F5x160_NbIddDiv_MASK                                 0xc00000
#define D18F5x160_NbIddValue_OFFSET                             24
#define D18F5x160_NbIddValue_WIDTH                              8
#define D18F5x160_NbIddValue_MASK                               0xff000000

/// D18F5x160
typedef union {
  struct {                                                              ///<
    UINT32                                               NbPstateEn:1 ; ///<
    UINT32                                               NbFid_5_0_:6 ; ///<
    UINT32                                                    NbDid:1 ; ///<
    UINT32                                             Reserved_9_8:2 ; ///<
    UINT32                                               NbVid_6_0_:7 ; ///<
    UINT32                                           Reserved_17_17:1 ; ///<
    UINT32                                                MemPstate:1 ; ///<
    UINT32                                           Reserved_19_19:1 ; ///<
    UINT32                                                 NbFid_6_:1 ; ///<
    UINT32                                                 NbVid_7_:1 ; ///<
    UINT32                                                 NbIddDiv:2 ; ///<
    UINT32                                               NbIddValue:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5x160_STRUCT;

// **** D18F5x164 Register Definition ****
// Address
#define D18F5x164_ADDRESS                                       0x164

// Type
#define D18F5x164_TYPE                                          TYPE_D18F5
// Field Data
#define D18F5x164_NbPstateEn_OFFSET                             0
#define D18F5x164_NbPstateEn_WIDTH                              1
#define D18F5x164_NbPstateEn_MASK                               0x1
#define D18F5x164_NbFid_5_0__OFFSET                             1
#define D18F5x164_NbFid_5_0__WIDTH                              6
#define D18F5x164_NbFid_5_0__MASK                               0x7e
#define D18F5x164_NbDid_OFFSET                                  7
#define D18F5x164_NbDid_WIDTH                                   1
#define D18F5x164_NbDid_MASK                                    0x80
#define D18F5x164_Reserved_9_8_OFFSET                           8
#define D18F5x164_Reserved_9_8_WIDTH                            2
#define D18F5x164_Reserved_9_8_MASK                             0x300
#define D18F5x164_NbVid_6_0__OFFSET                             10
#define D18F5x164_NbVid_6_0__WIDTH                              7
#define D18F5x164_NbVid_6_0__MASK                               0x1fc00
#define D18F5x164_Reserved_17_17_OFFSET                         17
#define D18F5x164_Reserved_17_17_WIDTH                          1
#define D18F5x164_Reserved_17_17_MASK                           0x20000
#define D18F5x164_MemPstate_OFFSET                              18
#define D18F5x164_MemPstate_WIDTH                               1
#define D18F5x164_MemPstate_MASK                                0x40000
#define D18F5x164_Reserved_19_19_OFFSET                         19
#define D18F5x164_Reserved_19_19_WIDTH                          1
#define D18F5x164_Reserved_19_19_MASK                           0x80000
#define D18F5x164_NbFid_6__OFFSET                               20
#define D18F5x164_NbFid_6__WIDTH                                1
#define D18F5x164_NbFid_6__MASK                                 0x100000
#define D18F5x164_NbVid_7__OFFSET                               21
#define D18F5x164_NbVid_7__WIDTH                                1
#define D18F5x164_NbVid_7__MASK                                 0x200000
#define D18F5x164_NbIddDiv_OFFSET                               22
#define D18F5x164_NbIddDiv_WIDTH                                2
#define D18F5x164_NbIddDiv_MASK                                 0xc00000
#define D18F5x164_NbIddValue_OFFSET                             24
#define D18F5x164_NbIddValue_WIDTH                              8
#define D18F5x164_NbIddValue_MASK                               0xff000000

/// D18F5x164
typedef union {
  struct {                                                              ///<
    UINT32                                               NbPstateEn:1 ; ///<
    UINT32                                               NbFid_5_0_:6 ; ///<
    UINT32                                                    NbDid:1 ; ///<
    UINT32                                             Reserved_9_8:2 ; ///<
    UINT32                                               NbVid_6_0_:7 ; ///<
    UINT32                                           Reserved_17_17:1 ; ///<
    UINT32                                                MemPstate:1 ; ///<
    UINT32                                           Reserved_19_19:1 ; ///<
    UINT32                                                 NbFid_6_:1 ; ///<
    UINT32                                                 NbVid_7_:1 ; ///<
    UINT32                                                 NbIddDiv:2 ; ///<
    UINT32                                               NbIddValue:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5x164_STRUCT;

// **** D18F5x168 Register Definition ****
// Address
#define D18F5x168_ADDRESS                                       0x168

// Type
#define D18F5x168_TYPE                                          TYPE_D18F5
// Field Data
#define D18F5x168_NbPstateEn_OFFSET                             0
#define D18F5x168_NbPstateEn_WIDTH                              1
#define D18F5x168_NbPstateEn_MASK                               0x1
#define D18F5x168_NbFid_5_0__OFFSET                             1
#define D18F5x168_NbFid_5_0__WIDTH                              6
#define D18F5x168_NbFid_5_0__MASK                               0x7e
#define D18F5x168_NbDid_OFFSET                                  7
#define D18F5x168_NbDid_WIDTH                                   1
#define D18F5x168_NbDid_MASK                                    0x80
#define D18F5x168_Reserved_9_8_OFFSET                           8
#define D18F5x168_Reserved_9_8_WIDTH                            2
#define D18F5x168_Reserved_9_8_MASK                             0x300
#define D18F5x168_NbVid_6_0__OFFSET                             10
#define D18F5x168_NbVid_6_0__WIDTH                              7
#define D18F5x168_NbVid_6_0__MASK                               0x1fc00
#define D18F5x168_Reserved_17_17_OFFSET                         17
#define D18F5x168_Reserved_17_17_WIDTH                          1
#define D18F5x168_Reserved_17_17_MASK                           0x20000
#define D18F5x168_MemPstate_OFFSET                              18
#define D18F5x168_MemPstate_WIDTH                               1
#define D18F5x168_MemPstate_MASK                                0x40000
#define D18F5x168_Reserved_19_19_OFFSET                         19
#define D18F5x168_Reserved_19_19_WIDTH                          1
#define D18F5x168_Reserved_19_19_MASK                           0x80000
#define D18F5x168_NbFid_6__OFFSET                               20
#define D18F5x168_NbFid_6__WIDTH                                1
#define D18F5x168_NbFid_6__MASK                                 0x100000
#define D18F5x168_NbVid_7__OFFSET                               21
#define D18F5x168_NbVid_7__WIDTH                                1
#define D18F5x168_NbVid_7__MASK                                 0x200000
#define D18F5x168_NbIddDiv_OFFSET                               22
#define D18F5x168_NbIddDiv_WIDTH                                2
#define D18F5x168_NbIddDiv_MASK                                 0xc00000
#define D18F5x168_NbIddValue_OFFSET                             24
#define D18F5x168_NbIddValue_WIDTH                              8
#define D18F5x168_NbIddValue_MASK                               0xff000000

/// D18F5x168
typedef union {
  struct {                                                              ///<
    UINT32                                               NbPstateEn:1 ; ///<
    UINT32                                               NbFid_5_0_:6 ; ///<
    UINT32                                                    NbDid:1 ; ///<
    UINT32                                             Reserved_9_8:2 ; ///<
    UINT32                                               NbVid_6_0_:7 ; ///<
    UINT32                                           Reserved_17_17:1 ; ///<
    UINT32                                                MemPstate:1 ; ///<
    UINT32                                           Reserved_19_19:1 ; ///<
    UINT32                                                 NbFid_6_:1 ; ///<
    UINT32                                                 NbVid_7_:1 ; ///<
    UINT32                                                 NbIddDiv:2 ; ///<
    UINT32                                               NbIddValue:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5x168_STRUCT;

// **** D18F5x16C Register Definition ****
// Address
#define D18F5x16C_ADDRESS                                       0x16c

// Type
#define D18F5x16C_TYPE                                          TYPE_D18F5
// Field Data
#define D18F5x16C_NbPstateEn_OFFSET                             0
#define D18F5x16C_NbPstateEn_WIDTH                              1
#define D18F5x16C_NbPstateEn_MASK                               0x1
#define D18F5x16C_NbFid_5_0__OFFSET                             1
#define D18F5x16C_NbFid_5_0__WIDTH                              6
#define D18F5x16C_NbFid_5_0__MASK                               0x7e
#define D18F5x16C_NbDid_OFFSET                                  7
#define D18F5x16C_NbDid_WIDTH                                   1
#define D18F5x16C_NbDid_MASK                                    0x80
#define D18F5x16C_Reserved_9_8_OFFSET                           8
#define D18F5x16C_Reserved_9_8_WIDTH                            2
#define D18F5x16C_Reserved_9_8_MASK                             0x300
#define D18F5x16C_NbVid_6_0__OFFSET                             10
#define D18F5x16C_NbVid_6_0__WIDTH                              7
#define D18F5x16C_NbVid_6_0__MASK                               0x1fc00
#define D18F5x16C_Reserved_17_17_OFFSET                         17
#define D18F5x16C_Reserved_17_17_WIDTH                          1
#define D18F5x16C_Reserved_17_17_MASK                           0x20000
#define D18F5x16C_MemPstate_OFFSET                              18
#define D18F5x16C_MemPstate_WIDTH                               1
#define D18F5x16C_MemPstate_MASK                                0x40000
#define D18F5x16C_Reserved_19_19_OFFSET                         19
#define D18F5x16C_Reserved_19_19_WIDTH                          1
#define D18F5x16C_Reserved_19_19_MASK                           0x80000
#define D18F5x16C_NbFid_6__OFFSET                               20
#define D18F5x16C_NbFid_6__WIDTH                                1
#define D18F5x16C_NbFid_6__MASK                                 0x100000
#define D18F5x16C_NbVid_7__OFFSET                               21
#define D18F5x16C_NbVid_7__WIDTH                                1
#define D18F5x16C_NbVid_7__MASK                                 0x200000
#define D18F5x16C_NbIddDiv_OFFSET                               22
#define D18F5x16C_NbIddDiv_WIDTH                                2
#define D18F5x16C_NbIddDiv_MASK                                 0xc00000
#define D18F5x16C_NbIddValue_OFFSET                             24
#define D18F5x16C_NbIddValue_WIDTH                              8
#define D18F5x16C_NbIddValue_MASK                               0xff000000

/// D18F5x16C
typedef union {
  struct {                                                              ///<
    UINT32                                               NbPstateEn:1 ; ///<
    UINT32                                               NbFid_5_0_:6 ; ///<
    UINT32                                                    NbDid:1 ; ///<
    UINT32                                             Reserved_9_8:2 ; ///<
    UINT32                                               NbVid_6_0_:7 ; ///<
    UINT32                                           Reserved_17_17:1 ; ///<
    UINT32                                                MemPstate:1 ; ///<
    UINT32                                           Reserved_19_19:1 ; ///<
    UINT32                                                 NbFid_6_:1 ; ///<
    UINT32                                                 NbVid_7_:1 ; ///<
    UINT32                                                 NbIddDiv:2 ; ///<
    UINT32                                               NbIddValue:8 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5x16C_STRUCT;

// **** D18F5x170 Register Definition ****
// Address
#define D18F5x170_ADDRESS                                       0x170

// Type
#define D18F5x170_TYPE                                          TYPE_D18F5
// Field Data
#define D18F5x170_NbPstateMaxVal_OFFSET                         0
#define D18F5x170_NbPstateMaxVal_WIDTH                          2
#define D18F5x170_NbPstateMaxVal_MASK                           0x3
#define D18F5x170_Reserved_2_2_OFFSET                           2
#define D18F5x170_Reserved_2_2_WIDTH                            1
#define D18F5x170_Reserved_2_2_MASK                             0x4
#define D18F5x170_NbPstateLo_OFFSET                             3
#define D18F5x170_NbPstateLo_WIDTH                              2
#define D18F5x170_NbPstateLo_MASK                               0x18
#define D18F5x170_Reserved_5_5_OFFSET                           5
#define D18F5x170_Reserved_5_5_WIDTH                            1
#define D18F5x170_Reserved_5_5_MASK                             0x20
#define D18F5x170_NbPstateHi_OFFSET                             6
#define D18F5x170_NbPstateHi_WIDTH                              2
#define D18F5x170_NbPstateHi_MASK                               0xc0
#define D18F5x170_Reserved_8_8_OFFSET                           8
#define D18F5x170_Reserved_8_8_WIDTH                            1
#define D18F5x170_Reserved_8_8_MASK                             0x100
#define D18F5x170_NbPstateThreshold_OFFSET                      9
#define D18F5x170_NbPstateThreshold_WIDTH                       4
#define D18F5x170_NbPstateThreshold_MASK                        0x1e00
#define D18F5x170_NbPstateDisOnP0_OFFSET                        13
#define D18F5x170_NbPstateDisOnP0_WIDTH                         1
#define D18F5x170_NbPstateDisOnP0_MASK                          0x2000
#define D18F5x170_SwNbPstateLoDis_OFFSET                        14
#define D18F5x170_SwNbPstateLoDis_WIDTH                         1
#define D18F5x170_SwNbPstateLoDis_MASK                          0x4000
#define D18F5x170_Reserved_15_15_OFFSET                         15
#define D18F5x170_Reserved_15_15_WIDTH                          1
#define D18F5x170_Reserved_15_15_MASK                           0x8000
#define D18F5x170_HalfLinkWidthTime_OFFSET                      16
#define D18F5x170_HalfLinkWidthTime_WIDTH                       3
#define D18F5x170_HalfLinkWidthTime_MASK                        0x70000
#define D18F5x170_Reserved_19_19_OFFSET                         19
#define D18F5x170_Reserved_19_19_WIDTH                          1
#define D18F5x170_Reserved_19_19_MASK                           0x80000
#define D18F5x170_FullLinkWidthTime_OFFSET                      20
#define D18F5x170_FullLinkWidthTime_WIDTH                       3
#define D18F5x170_FullLinkWidthTime_MASK                        0x700000
#define D18F5x170_NbPstateGnbSlowDis_OFFSET                     23
#define D18F5x170_NbPstateGnbSlowDis_WIDTH                      1
#define D18F5x170_NbPstateGnbSlowDis_MASK                       0x800000
#define D18F5x170_NbPstateLoRes_OFFSET                          24
#define D18F5x170_NbPstateLoRes_WIDTH                           3
#define D18F5x170_NbPstateLoRes_MASK                            0x7000000
#define D18F5x170_NbPstateHiRes_OFFSET                          27
#define D18F5x170_NbPstateHiRes_WIDTH                           3
#define D18F5x170_NbPstateHiRes_MASK                            0x38000000
#define D18F5x170_NbPstateFidVidSbcEn_OFFSET                    30
#define D18F5x170_NbPstateFidVidSbcEn_WIDTH                     1
#define D18F5x170_NbPstateFidVidSbcEn_MASK                      0x40000000
#define D18F5x170_NbPstateFidVidSbcEn_VALUE                     0x1
#define D18F5x170_MemPstateDis_OFFSET                           31
#define D18F5x170_MemPstateDis_WIDTH                            1
#define D18F5x170_MemPstateDis_MASK                             0x80000000

/// D18F5x170
typedef union {
  struct {                                                              ///<
    UINT32                                           NbPstateMaxVal:2 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                               NbPstateLo:2 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                               NbPstateHi:2 ; ///<
    UINT32                                             Reserved_8_8:1 ; ///<
    UINT32                                        NbPstateThreshold:4 ; ///<
    UINT32                                          NbPstateDisOnP0:1 ; ///<
    UINT32                                          SwNbPstateLoDis:1 ; ///<
    UINT32                                           Reserved_15_15:1 ; ///<
    UINT32                                        HalfLinkWidthTime:3 ; ///<
    UINT32                                           Reserved_19_19:1 ; ///<
    UINT32                                        FullLinkWidthTime:3 ; ///<
    UINT32                                       NbPstateGnbSlowDis:1 ; ///<
    UINT32                                            NbPstateLoRes:3 ; ///<
    UINT32                                            NbPstateHiRes:3 ; ///<
    UINT32                                      NbPstateFidVidSbcEn:1 ; ///<
    UINT32                                             MemPstateDis:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5x170_STRUCT;

// **** D18F5x174 Register Definition ****
// Address
#define D18F5x174_ADDRESS                                       0x174

// Type
#define D18F5x174_TYPE                                          TYPE_D18F5
// Field Data
#define D18F5x174_NbPstateDis_OFFSET                            0
#define D18F5x174_NbPstateDis_WIDTH                             1
#define D18F5x174_NbPstateDis_MASK                              0x1
#define D18F5x174_StartupNbPstate_OFFSET                        1
#define D18F5x174_StartupNbPstate_WIDTH                         2
#define D18F5x174_StartupNbPstate_MASK                          0x6
#define D18F5x174_CurNbFid_5_0__OFFSET                          3
#define D18F5x174_CurNbFid_5_0__WIDTH                           6
#define D18F5x174_CurNbFid_5_0__MASK                            0x1f8
#define D18F5x174_CurNbDid_OFFSET                               9
#define D18F5x174_CurNbDid_WIDTH                                1
#define D18F5x174_CurNbDid_MASK                                 0x200
#define D18F5x174_Reserved_10_10_OFFSET                         10
#define D18F5x174_Reserved_10_10_WIDTH                          1
#define D18F5x174_Reserved_10_10_MASK                           0x400
#define D18F5x174_CurNbFid_6__OFFSET                            11
#define D18F5x174_CurNbFid_6__WIDTH                             1
#define D18F5x174_CurNbFid_6__MASK                              0x800
#define D18F5x174_CurNbVid_6_0__OFFSET                          12
#define D18F5x174_CurNbVid_6_0__WIDTH                           7
#define D18F5x174_CurNbVid_6_0__MASK                            0x7f000
#define D18F5x174_CurNbPstate_OFFSET                            19
#define D18F5x174_CurNbPstate_WIDTH                             2
#define D18F5x174_CurNbPstate_MASK                              0x180000
#define D18F5x174_Reserved_21_21_OFFSET                         21
#define D18F5x174_Reserved_21_21_WIDTH                          1
#define D18F5x174_Reserved_21_21_MASK                           0x200000
#define D18F5x174_CurNbPstateLo_OFFSET                          22
#define D18F5x174_CurNbPstateLo_WIDTH                           1
#define D18F5x174_CurNbPstateLo_MASK                            0x400000
#define D18F5x174_CurNbVid_7__OFFSET                            23
#define D18F5x174_CurNbVid_7__WIDTH                             1
#define D18F5x174_CurNbVid_7__MASK                              0x800000
#define D18F5x174_CurMemPstate_OFFSET                           24
#define D18F5x174_CurMemPstate_WIDTH                            1
#define D18F5x174_CurMemPstate_MASK                             0x1000000
#define D18F5x174_Reserved_25_25_OFFSET                         25
#define D18F5x174_Reserved_25_25_WIDTH                          1
#define D18F5x174_Reserved_25_25_MASK                           0x2000000
#define D18F5x174_CurNbVidPstate_OFFSET                         26
#define D18F5x174_CurNbVidPstate_WIDTH                          2
#define D18F5x174_CurNbVidPstate_MASK                           0xc000000
#define D18F5x174_Reserved_28_28_OFFSET                         28
#define D18F5x174_Reserved_28_28_WIDTH                          1
#define D18F5x174_Reserved_28_28_MASK                           0x10000000
#define D18F5x174_NbVidUseGnb_OFFSET                            29
#define D18F5x174_NbVidUseGnb_WIDTH                             1
#define D18F5x174_NbVidUseGnb_MASK                              0x20000000
#define D18F5x174_NbVidReqBusy_OFFSET                           30
#define D18F5x174_NbVidReqBusy_WIDTH                            1
#define D18F5x174_NbVidReqBusy_MASK                             0x40000000
#define D18F5x174_NbPstateReqBusy_OFFSET                        31
#define D18F5x174_NbPstateReqBusy_WIDTH                         1
#define D18F5x174_NbPstateReqBusy_MASK                          0x80000000

/// D18F5x174
typedef union {
  struct {                                                              ///<
    UINT32                                              NbPstateDis:1 ; ///<
    UINT32                                          StartupNbPstate:2 ; ///<
    UINT32                                            CurNbFid_5_0_:6 ; ///<
    UINT32                                                 CurNbDid:1 ; ///<
    UINT32                                           Reserved_10_10:1 ; ///<
    UINT32                                              CurNbFid_6_:1 ; ///<
    UINT32                                            CurNbVid_6_0_:7 ; ///<
    UINT32                                              CurNbPstate:2 ; ///<
    UINT32                                           Reserved_21_21:1 ; ///<
    UINT32                                            CurNbPstateLo:1 ; ///<
    UINT32                                              CurNbVid_7_:1 ; ///<
    UINT32                                             CurMemPstate:1 ; ///<
    UINT32                                           Reserved_25_25:1 ; ///<
    UINT32                                           CurNbVidPstate:2 ; ///<
    UINT32                                           Reserved_28_28:1 ; ///<
    UINT32                                              NbVidUseGnb:1 ; ///<
    UINT32                                             NbVidReqBusy:1 ; ///<
    UINT32                                          NbPstateReqBusy:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F5x174_STRUCT;

// **** D18F5x178 Register Definition ****
// Address
#define D18F5x178_ADDRESS                                       0x178
// Type
#define D18F5x178_TYPE                                          TYPE_D18F5

// Field Data
#define D18F5x178_Reserved_1_0_OFFSET                           0
#define D18F5x178_Reserved_1_0_WIDTH                            2
#define D18F5x178_Reserved_1_0_MASK                             0x3
#define D18F5x178_CstateFusionDis_OFFSET                        2
#define D18F5x178_CstateFusionDis_WIDTH                         1
#define D18F5x178_CstateFusionDis_MASK                          0x4
#define D18F5x178_CstateThreeWayHsEn_OFFSET                     3
#define D18F5x178_CstateThreeWayHsEn_WIDTH                      1
#define D18F5x178_CstateThreeWayHsEn_MASK                       0x8
#define D18F5x178_Reserved_17_4_OFFSET                          4
#define D18F5x178_Reserved_17_4_WIDTH                           14
#define D18F5x178_Reserved_17_4_MASK                            0x3FFF0
#define D18F5x178_CstateFusionHsDis_OFFSET                      18
#define D18F5x178_CstateFusionHsDis_WIDTH                       1
#define D18F5x178_CstateFusionHsDis_MASK                        0x40000
#define D18F5x178_SwGfxDis_OFFSET                               19
#define D18F5x178_SwGfxDis_WIDTH                                1
#define D18F5x178_SwGfxDis_MASK                                 0x80000
#define D18F5x178_Reserved_31_20_OFFSET                         20
#define D18F5x178_Reserved_31_20_WIDTH                          12
#define D18F5x178_Reserved_31_20_MASK                           0xFFF00000

/// D18F5x178
typedef union {
  struct {                                                            ///<
    UINT32                                            Reserved_1_0:2; ///<
    UINT32                                         CstateFusionDis:1; ///<
    UINT32                                      CstateThreeWayHsEn:1; ///<
    UINT32                                           Reserved_17_4:14; ///<
    UINT32                                       CstateFusionHsDis:1; ///<
    UINT32                                                SwGfxDis:1; ///<
    UINT32                                          Reserved_31_20:12; ///<

  } Field;

  UINT32 Value;
} D18F5x178_STRUCT;

/// Fuse CZ
// **** D0F0xBC_xC0014000 Field Definition ****
// Address
#define D0F0xBC_xC0014000_ADDRESS                               0xC0014000

// Type
#define D0F0xBC_xC0014000_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014000_GPU_DIS_OFFSET                        0
#define D0F0xBC_xC0014000_GPU_DIS_WIDTH                         1
#define D0F0xBC_xC0014000_GPU_DIS_MASK                          0x1
#define D0F0xBC_xC0014000_Reserved1_31_OFFSET                   1
#define D0F0xBC_xC0014000_Reserved1_31_WIDTH                    31
#define D0F0xBC_xC0014000_Reserved1_31_MASK                     0xfffffffe

/// D0F0xBC_xC0014000
typedef union {
  struct {                                                              ///<
    UINT32                                                  GPU_DIS:1 ; ///<
    UINT32                                             Reserved1_31:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014000_STRUCT;

// **** D0F0xBC_xC0014004 Field Definition ****
// Address
#define D0F0xBC_xC0014004_ADDRESS                               0xC0014004

// Type
#define D0F0xBC_xC0014004_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014004_Reserved0_9_OFFSET                    0
#define D0F0xBC_xC0014004_Reserved0_9_WIDTH                     10
#define D0F0xBC_xC0014004_Reserved0_9_MASK                      0x3ff
#define D0F0xBC_xC0014004_GnbVid0_OFFSET                        10
#define D0F0xBC_xC0014004_GnbVid0_WIDTH                         8
#define D0F0xBC_xC0014004_GnbVid0_MASK                          0x3fc00
#define D0F0xBC_xC0014004_GnbVid1_OFFSET                        18
#define D0F0xBC_xC0014004_GnbVid1_WIDTH                         8
#define D0F0xBC_xC0014004_GnbVid1_MASK                          0x3fc0000
#define D0F0xBC_xC0014004_Reserved26_31_OFFSET                  26
#define D0F0xBC_xC0014004_Reserved26_31_WIDTH                   6
#define D0F0xBC_xC0014004_Reserved26_31_MASK                    0xfc000000

/// D0F0xBC_xC0014004
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_9:10; ///<
    UINT32                                                  GnbVid0:8 ; ///<
    UINT32                                                  GnbVid1:8 ; ///<
    UINT32                                            Reserved26_31:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014004_STRUCT;

// **** D0F0xBC_xC0014007 Field Definition ****
// Address
#define D0F0xBC_xC0014007_ADDRESS                               0xC0014007

// Type
#define D0F0xBC_xC0014007_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014007_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC0014007_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC0014007_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC0014007_GnbVid2_OFFSET                        2
#define D0F0xBC_xC0014007_GnbVid2_WIDTH                         8
#define D0F0xBC_xC0014007_GnbVid2_MASK                          0x3fc
#define D0F0xBC_xC0014007_Reserved10_31_OFFSET                  10
#define D0F0xBC_xC0014007_Reserved10_31_WIDTH                   22
#define D0F0xBC_xC0014007_Reserved10_31_MASK                    0xfffffc00

/// D0F0xBC_xC0014007
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                  GnbVid2:8 ; ///<
    UINT32                                            Reserved10_31:22; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014007_STRUCT;

// **** D0F0xBC_xC0014008 Field Definition ****
// Address
#define D0F0xBC_xC0014008_ADDRESS                               0xC0014008

// Type
#define D0F0xBC_xC0014008_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014008_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC0014008_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC0014008_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC0014008_GnbVid3_OFFSET                        2
#define D0F0xBC_xC0014008_GnbVid3_WIDTH                         8
#define D0F0xBC_xC0014008_GnbVid3_MASK                          0x3fc
#define D0F0xBC_xC0014008_GnbVid4_OFFSET                        10
#define D0F0xBC_xC0014008_GnbVid4_WIDTH                         8
#define D0F0xBC_xC0014008_GnbVid4_MASK                          0x3fc00
#define D0F0xBC_xC0014008_Reserved18_31_OFFSET                  18
#define D0F0xBC_xC0014008_Reserved18_31_WIDTH                   14
#define D0F0xBC_xC0014008_Reserved18_31_MASK                    0xfffc0000

/// D0F0xBC_xC0014008
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                  GnbVid3:8 ; ///<
    UINT32                                                  GnbVid4:8 ; ///<
    UINT32                                            Reserved18_31:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014008_STRUCT;

// **** D0F0xBC_xC001400C Field Definition ****
// Address
#define D0F0xBC_xC001400C_ADDRESS                               0xC001400c

// Type
#define D0F0xBC_xC001400C_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001400C_Reserved0_12_OFFSET                   0
#define D0F0xBC_xC001400C_Reserved0_12_WIDTH                    13
#define D0F0xBC_xC001400C_Reserved0_12_MASK                     0x1fff
#define D0F0xBC_xC001400C_MainPllOpFreqIdStartup_OFFSET         13
#define D0F0xBC_xC001400C_MainPllOpFreqIdStartup_WIDTH          7
#define D0F0xBC_xC001400C_MainPllOpFreqIdStartup_MASK           0xfe000
#define D0F0xBC_xC001400C_Reserved20_31_OFFSET                  20
#define D0F0xBC_xC001400C_Reserved20_31_WIDTH                   12
#define D0F0xBC_xC001400C_Reserved20_31_MASK                    0xfff00000

/// D0F0xBC_xC001400C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved0_12:13; ///<
    UINT32                                   MainPllOpFreqIdStartup:7 ; ///<
    UINT32                                            Reserved20_31:12; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001400C_STRUCT;

// **** D0F0xBC_xC0014104 Field Definition ****
// Address
#define D0F0xBC_xC0014104_ADDRESS                               0xC0014104

// Type
#define D0F0xBC_xC0014104_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014104_Reserved0_3_OFFSET                    0
#define D0F0xBC_xC0014104_Reserved0_3_WIDTH                     4
#define D0F0xBC_xC0014104_Reserved0_3_MASK                      0xf
#define D0F0xBC_xC0014104_GfxVid0_OFFSET                        4
#define D0F0xBC_xC0014104_GfxVid0_WIDTH                         8
#define D0F0xBC_xC0014104_GfxVid0_MASK                          0xff0
#define D0F0xBC_xC0014104_GfxVid1_OFFSET                        12
#define D0F0xBC_xC0014104_GfxVid1_WIDTH                         8
#define D0F0xBC_xC0014104_GfxVid1_MASK                          0xff000
#define D0F0xBC_xC0014104_GfxVid2_OFFSET                        20
#define D0F0xBC_xC0014104_GfxVid2_WIDTH                         8
#define D0F0xBC_xC0014104_GfxVid2_MASK                          0xff00000
#define D0F0xBC_xC0014104_Reserved28_31_OFFSET                  28
#define D0F0xBC_xC0014104_Reserved28_31_WIDTH                   4
#define D0F0xBC_xC0014104_Reserved28_31_MASK                    0xf0000000

/// D0F0xBC_xC0014104
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_3:4 ; ///<
    UINT32                                                  GfxVid0:8 ; ///<
    UINT32                                                  GfxVid1:8 ; ///<
    UINT32                                                  GfxVid2:8 ; ///<
    UINT32                                            Reserved28_31:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014104_STRUCT;

// **** D0F0xBC_xC0014107 Field Definition ****
// Address
#define D0F0xBC_xC0014107_ADDRESS                               0xC0014107

// Type
#define D0F0xBC_xC0014107_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014107_Reserved0_3_OFFSET                    0
#define D0F0xBC_xC0014107_Reserved0_3_WIDTH                     4
#define D0F0xBC_xC0014107_Reserved0_3_MASK                      0xf
#define D0F0xBC_xC0014107_GfxVid3_OFFSET                        4
#define D0F0xBC_xC0014107_GfxVid3_WIDTH                         8
#define D0F0xBC_xC0014107_GfxVid3_MASK                          0xff0
#define D0F0xBC_xC0014107_Reserved12_31_OFFSET                  12
#define D0F0xBC_xC0014107_Reserved12_31_WIDTH                   20
#define D0F0xBC_xC0014107_Reserved12_31_MASK                    0xfffff000

/// D0F0xBC_xC0014107
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_3:4 ; ///<
    UINT32                                                  GfxVid3:8 ; ///<
    UINT32                                            Reserved12_31:20; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014107_STRUCT;

// **** D0F0xBC_xC0014108 Field Definition ****
// Address
#define D0F0xBC_xC0014108_ADDRESS                               0xC0014108

// Type
#define D0F0xBC_xC0014108_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0014108_Reserved0_3_OFFSET                    0
#define D0F0xBC_xC0014108_Reserved0_3_WIDTH                     4
#define D0F0xBC_xC0014108_Reserved0_3_MASK                      0xf
#define D0F0xBC_xC0014108_GfxVid4_OFFSET                        4
#define D0F0xBC_xC0014108_GfxVid4_WIDTH                         8
#define D0F0xBC_xC0014108_GfxVid4_MASK                          0xff0
#define D0F0xBC_xC0014108_Reserved12_31_OFFSET                  12
#define D0F0xBC_xC0014108_Reserved12_31_WIDTH                   20
#define D0F0xBC_xC0014108_Reserved12_31_MASK                    0xfffff000

/// D0F0xBC_xC0014108
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_3:4 ; ///<
    UINT32                                                  GfxVid4:8 ; ///<
    UINT32                                            Reserved12_31:20; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0014108_STRUCT;

// **** D0F0xBC_xC00160C4 Field Definition ****
// Address
#define D0F0xBC_xC00160C4_ADDRESS                               0xC00160c4

// Type
#define D0F0xBC_xC00160C4_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160C4_Reserved0_17_OFFSET                   0
#define D0F0xBC_xC00160C4_Reserved0_17_WIDTH                    18
#define D0F0xBC_xC00160C4_Reserved0_17_MASK                     0x3ffff
#define D0F0xBC_xC00160C4_GnbVid5_OFFSET                        18
#define D0F0xBC_xC00160C4_GnbVid5_WIDTH                         8
#define D0F0xBC_xC00160C4_GnbVid5_MASK                          0x3fc0000
#define D0F0xBC_xC00160C4_Reserved26_31_OFFSET                  26
#define D0F0xBC_xC00160C4_Reserved26_31_WIDTH                   6
#define D0F0xBC_xC00160C4_Reserved26_31_MASK                    0xfc000000

/// D0F0xBC_xC00160C4
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved0_17:18; ///<
    UINT32                                                  GnbVid5:8 ; ///<
    UINT32                                            Reserved26_31:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160C4_STRUCT;

// **** D0F0xBC_xC00160C7 Field Definition ****
// Address
#define D0F0xBC_xC00160C7_ADDRESS                               0xC00160c7

// Type
#define D0F0xBC_xC00160C7_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160C7_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC00160C7_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC00160C7_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC00160C7_GnbVid6_OFFSET                        2
#define D0F0xBC_xC00160C7_GnbVid6_WIDTH                         8
#define D0F0xBC_xC00160C7_GnbVid6_MASK                          0x3fc
#define D0F0xBC_xC00160C7_Reserved10_31_OFFSET                  10
#define D0F0xBC_xC00160C7_Reserved10_31_WIDTH                   22
#define D0F0xBC_xC00160C7_Reserved10_31_MASK                    0xfffffc00

/// D0F0xBC_xC00160C7
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                  GnbVid6:8 ; ///<
    UINT32                                            Reserved10_31:22; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160C7_STRUCT;

// **** D0F0xBC_xC00160C8 Field Definition ****
// Address
#define D0F0xBC_xC00160C8_ADDRESS                               0xC00160c8

// Type
#define D0F0xBC_xC00160C8_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160C8_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC00160C8_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC00160C8_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC00160C8_GnbVid7_OFFSET                        2
#define D0F0xBC_xC00160C8_GnbVid7_WIDTH                         8
#define D0F0xBC_xC00160C8_GnbVid7_MASK                          0x3fc
#define D0F0xBC_xC00160C8_GnbVidOffset5_OFFSET                  10
#define D0F0xBC_xC00160C8_GnbVidOffset5_WIDTH                   8
#define D0F0xBC_xC00160C8_GnbVidOffset5_MASK                    0x3fc00
#define D0F0xBC_xC00160C8_GnbVidOffset6_OFFSET                  18
#define D0F0xBC_xC00160C8_GnbVidOffset6_WIDTH                   8
#define D0F0xBC_xC00160C8_GnbVidOffset6_MASK                    0x3fc0000
#define D0F0xBC_xC00160C8_Reserved26_31_OFFSET                  26
#define D0F0xBC_xC00160C8_Reserved26_31_WIDTH                   6
#define D0F0xBC_xC00160C8_Reserved26_31_MASK                    0xfc000000

/// D0F0xBC_xC00160C8
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                  GnbVid7:8 ; ///<
    UINT32                                            GnbVidOffset5:8 ; ///<
    UINT32                                            GnbVidOffset6:8 ; ///<
    UINT32                                            Reserved26_31:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160C8_STRUCT;

// **** D0F0xBC_xC00160CB Field Definition ****
// Address
#define D0F0xBC_xC00160CB_ADDRESS                               0xC00160cb

// Type
#define D0F0xBC_xC00160CB_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160CB_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC00160CB_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC00160CB_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC00160CB_GnbVidOffset7_OFFSET                  2
#define D0F0xBC_xC00160CB_GnbVidOffset7_WIDTH                   8
#define D0F0xBC_xC00160CB_GnbVidOffset7_MASK                    0x3fc
#define D0F0xBC_xC00160CB_Reserved10_31_OFFSET                  10
#define D0F0xBC_xC00160CB_Reserved10_31_WIDTH                   22
#define D0F0xBC_xC00160CB_Reserved10_31_MASK                    0xfffffc00

/// D0F0xBC_xC00160CB
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                            GnbVidOffset7:8 ; ///<
    UINT32                                            Reserved10_31:22; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160CB_STRUCT;

// **** D0F0xBC_xC00160CC Field Definition ****
// Address
#define D0F0xBC_xC00160CC_ADDRESS                               0xC00160cC

// Type
#define D0F0xBC_xC00160CC_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160CC_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC00160CC_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC00160CC_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC00160CC_AClkDid5_OFFSET                       2
#define D0F0xBC_xC00160CC_AClkDid5_WIDTH                        7
#define D0F0xBC_xC00160CC_AClkDid5_MASK                         0x1fc
#define D0F0xBC_xC00160CC_AClkDid6_OFFSET                       9
#define D0F0xBC_xC00160CC_AClkDid6_WIDTH                        7
#define D0F0xBC_xC00160CC_AClkDid6_MASK                         0xfe00
#define D0F0xBC_xC00160CC_AClkDid7_OFFSET                       16
#define D0F0xBC_xC00160CC_AClkDid7_WIDTH                        7
#define D0F0xBC_xC00160CC_AClkDid7_MASK                         0x7f0000
#define D0F0xBC_xC00160CC_DClkDid5_OFFSET                       23
#define D0F0xBC_xC00160CC_DClkDid5_WIDTH                        7
#define D0F0xBC_xC00160CC_DClkDid5_MASK                         0x3f800000
#define D0F0xBC_xC00160CC_Reserved30_31_OFFSET                  30
#define D0F0xBC_xC00160CC_Reserved30_31_WIDTH                   2
#define D0F0xBC_xC00160CC_Reserved30_31_MASK                    0xc0000000

/// D0F0xBC_xC00160CC
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                 AClkDid5:7 ; ///<
    UINT32                                                 AClkDid6:7 ; ///<
    UINT32                                                 AClkDid7:7 ; ///<
    UINT32                                                 DClkDid5:7 ; ///<
    UINT32                                            Reserved30_31:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160CC_STRUCT;

// **** D0F0xBC_xC00160CF Field Definition ****
// Address
#define D0F0xBC_xC00160CF_ADDRESS                               0xC00160cf

// Type
#define D0F0xBC_xC00160CF_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160CF_Reserved0_5_OFFSET                    0
#define D0F0xBC_xC00160CF_Reserved0_5_WIDTH                     6
#define D0F0xBC_xC00160CF_Reserved0_5_MASK                      0x3f
#define D0F0xBC_xC00160CF_DClkDid6_OFFSET                       6
#define D0F0xBC_xC00160CF_DClkDid6_WIDTH                        7
#define D0F0xBC_xC00160CF_DClkDid6_MASK                         0x1fc0
#define D0F0xBC_xC00160CF_Reserved13_31_OFFSET                  13
#define D0F0xBC_xC00160CF_Reserved13_31_WIDTH                   19
#define D0F0xBC_xC00160CF_Reserved13_31_MASK                    0xffffe000

/// D0F0xBC_xC00160CF
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_5:6 ; ///<
    UINT32                                                 DClkDid6:7 ; ///<
    UINT32                                            Reserved13_31:19; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160CF_STRUCT;

// **** D0F0xBC_xC00160D0 Field Definition ****
// Address
#define D0F0xBC_xC00160D0_ADDRESS                               0xC00160d0

// Type
#define D0F0xBC_xC00160D0_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160D0_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC00160D0_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC00160D0_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC00160D0_DClkDid7_OFFSET                       5
#define D0F0xBC_xC00160D0_DClkDid7_WIDTH                        7
#define D0F0xBC_xC00160D0_DClkDid7_MASK                         0xfe0
#define D0F0xBC_xC00160D0_DispClkDid5_OFFSET                    12
#define D0F0xBC_xC00160D0_DispClkDid5_WIDTH                     7
#define D0F0xBC_xC00160D0_DispClkDid5_MASK                      0x7f000
#define D0F0xBC_xC00160D0_DispClkDid6_OFFSET                    19
#define D0F0xBC_xC00160D0_DispClkDid6_WIDTH                     7
#define D0F0xBC_xC00160D0_DispClkDid6_MASK                      0x3f80000
#define D0F0xBC_xC00160D0_Reserved26_31_OFFSET                  26
#define D0F0xBC_xC00160D0_Reserved26_31_WIDTH                   6
#define D0F0xBC_xC00160D0_Reserved26_31_MASK                    0xfc000000

/// D0F0xBC_xC00160D0
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                                 DClkDid7:7 ; ///<
    UINT32                                              DispClkDid5:7 ; ///<
    UINT32                                              DispClkDid6:7 ; ///<
    UINT32                                            Reserved26_31:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160D0_STRUCT;

// **** D0F0xBC_xC00160D3 Field Definition ****
// Address
#define D0F0xBC_xC00160D3_ADDRESS                               0xC00160d3

// Type
#define D0F0xBC_xC00160D3_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160D3_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC00160D3_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC00160D3_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC00160D3_DispClkDid7_OFFSET                    2
#define D0F0xBC_xC00160D3_DispClkDid7_WIDTH                     7
#define D0F0xBC_xC00160D3_DispClkDid7_MASK                      0x1fc
#define D0F0xBC_xC00160D3_Reserved9_31_OFFSET                   9
#define D0F0xBC_xC00160D3_Reserved9_31_WIDTH                    23
#define D0F0xBC_xC00160D3_Reserved9_31_MASK                     0xfffffe00

/// D0F0xBC_xC00160D3
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                              DispClkDid7:7 ; ///<
    UINT32                                             Reserved9_31:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160D3_STRUCT;

// **** D0F0xBC_xC00160D4 Field Definition ****
// Address
#define D0F0xBC_xC00160D4_ADDRESS                               0xC00160d4

// Type
#define D0F0xBC_xC00160D4_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160D4_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC00160D4_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC00160D4_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC00160D4_EClkDid5_OFFSET                       1
#define D0F0xBC_xC00160D4_EClkDid5_WIDTH                        7
#define D0F0xBC_xC00160D4_EClkDid5_MASK                         0xfe
#define D0F0xBC_xC00160D4_EClkDid6_OFFSET                       8
#define D0F0xBC_xC00160D4_EClkDid6_WIDTH                        7
#define D0F0xBC_xC00160D4_EClkDid6_MASK                         0x7f00
#define D0F0xBC_xC00160D4_EClkDid7_OFFSET                       15
#define D0F0xBC_xC00160D4_EClkDid7_WIDTH                        7
#define D0F0xBC_xC00160D4_EClkDid7_MASK                         0x3f8000
#define D0F0xBC_xC00160D4_LClkDpmDid5_OFFSET                    22
#define D0F0xBC_xC00160D4_LClkDpmDid5_WIDTH                     7
#define D0F0xBC_xC00160D4_LClkDpmDid5_MASK                      0x1fc00000
#define D0F0xBC_xC00160D4_Reserved29_31_OFFSET                  29
#define D0F0xBC_xC00160D4_Reserved29_31_WIDTH                   3
#define D0F0xBC_xC00160D4_Reserved29_31_MASK                    0xe0000000

/// D0F0xBC_xC00160D4
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                                 EClkDid5:7 ; ///<
    UINT32                                                 EClkDid6:7 ; ///<
    UINT32                                                 EClkDid7:7 ; ///<
    UINT32                                              LClkDpmDid5:7 ; ///<
    UINT32                                            Reserved29_31:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160D4_STRUCT;

// **** D0F0xBC_xC00160D7 Field Definition ****
// Address
#define D0F0xBC_xC00160D7_ADDRESS                               0xC00160d7

// Type
#define D0F0xBC_xC00160D7_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160D7_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC00160D7_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC00160D7_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC00160D7_LClkDpmDid6_OFFSET                    5
#define D0F0xBC_xC00160D7_LClkDpmDid6_WIDTH                     7
#define D0F0xBC_xC00160D7_LClkDpmDid6_MASK                      0xfe0
#define D0F0xBC_xC00160D7_Reserved12_31_OFFSET                  12
#define D0F0xBC_xC00160D7_Reserved12_31_WIDTH                   20
#define D0F0xBC_xC00160CF_Reserved12_31_MASK                    0xfffff000

/// D0F0xBC_xC00160D7
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                              LClkDpmDid6:7 ; ///<
    UINT32                                            Reserved12_31:20; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160D7_STRUCT;

// **** D0F0xBC_xC00160D8 Field Definition ****
// Address
#define D0F0xBC_xC00160D8_ADDRESS                               0xC00160d8

// Type
#define D0F0xBC_xC00160D8_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160D8_Reserved0_3_OFFSET                    0
#define D0F0xBC_xC00160D8_Reserved0_3_WIDTH                     4
#define D0F0xBC_xC00160D8_Reserved0_3_MASK                      0xf
#define D0F0xBC_xC00160D8_LClkDpmDid7_OFFSET                    4
#define D0F0xBC_xC00160D8_LClkDpmDid7_WIDTH                     7
#define D0F0xBC_xC00160D8_LClkDpmDid7_MASK                      0x7f0
#define D0F0xBC_xC00160D8_SClkDid5_OFFSET                       11
#define D0F0xBC_xC00160D8_SClkDid5_WIDTH                        7
#define D0F0xBC_xC00160D8_SClkDid5_MASK                         0x3f800
#define D0F0xBC_xC00160D8_SClkDid6_OFFSET                       18
#define D0F0xBC_xC00160D8_SClkDid6_WIDTH                        7
#define D0F0xBC_xC00160D8_SClkDid6_MASK                         0x1fc0000
#define D0F0xBC_xC00160D8_SClkDid7_OFFSET                       25
#define D0F0xBC_xC00160D8_SClkDid7_WIDTH                        7
#define D0F0xBC_xC00160D8_SClkDid7_MASK                         0xfe000000

/// D0F0xBC_xC00160D08
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_3:4 ; ///<
    UINT32                                              LClkDpmDid7:7 ; ///<
    UINT32                                                 SClkDid5:7 ; ///<
    UINT32                                                 SClkDid6:7 ; ///<
    UINT32                                                 SClkDid7:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160D8_STRUCT;

// **** D0F0xBC_xC00160DC Field Definition ****
// Address
#define D0F0xBC_xC00160DC_ADDRESS                               0xC00160dc

// Type
#define D0F0xBC_xC00160DC_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160DC_VClkDid5_OFFSET                       0
#define D0F0xBC_xC00160DC_VClkDid5_WIDTH                        7
#define D0F0xBC_xC00160DC_VClkDid5_MASK                         0x7f
#define D0F0xBC_xC00160DC_VClkDid6_OFFSET                       7
#define D0F0xBC_xC00160DC_VClkDid6_WIDTH                        7
#define D0F0xBC_xC00160DC_VClkDid6_MASK                         0x3f80
#define D0F0xBC_xC00160DC_VClkDid7_OFFSET                       14
#define D0F0xBC_xC00160DC_VClkDid7_WIDTH                        7
#define D0F0xBC_xC00160DC_VClkDid7_MASK                         0x1fc000
#define D0F0xBC_xC00160DC_GfxVid5_OFFSET                        21
#define D0F0xBC_xC00160DC_GfxVid5_WIDTH                         8
#define D0F0xBC_xC00160DC_GfxVid5_MASK                          0x1fe00000
#define D0F0xBC_xC00160DC_Reserved29_31_OFFSET                  29
#define D0F0xBC_xC00160DC_Reserved29_31_WIDTH                   3
#define D0F0xBC_xC00160DC_Reserved29_31_MASK                    0xe0000000

/// D0F0xBC_xC00160DC
typedef union {
  struct {                                                              ///<
    UINT32                                                 VClkDid5:7 ; ///<
    UINT32                                                 VClkDid6:7 ; ///<
    UINT32                                                 VClkDid7:7 ; ///<
    UINT32                                                  GfxVid5:8 ; ///<
    UINT32                                            Reserved29_31:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160DC_STRUCT;

// **** D0F0xBC_xC00160DF Field Definition ****
// Address
#define D0F0xBC_xC00160DF_ADDRESS                               0xC00160df

// Type
#define D0F0xBC_xC00160DF_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160DF_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC00160DF_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC00160DF_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC00160DF_GfxVid6_OFFSET                        5
#define D0F0xBC_xC00160DF_GfxVid6_WIDTH                         8
#define D0F0xBC_xC00160DF_GfxVid6_MASK                          0x1fe0
#define D0F0xBC_xC00160DF_Reserved13_31_OFFSET                  13
#define D0F0xBC_xC00160DF_Reserved13_31_WIDTH                   19
#define D0F0xBC_xC00160DF_Reserved13_31_MASK                    0xffffe000

/// D0F0xBC_xC00160DF
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                                  GfxVid6:8 ; ///<
    UINT32                                            Reserved13_31:19; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160DF_STRUCT;

// **** D0F0xBC_xC00160E0 Field Definition ****
// Address
#define D0F0xBC_xC00160E0_ADDRESS                               0xC00160e0

// Type
#define D0F0xBC_xC00160E0_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160E0_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC00160E0_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC00160E0_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC00160E0_GfxVid7_OFFSET                        5
#define D0F0xBC_xC00160E0_GfxVid7_WIDTH                         8
#define D0F0xBC_xC00160E0_GfxVid7_MASK                          0x1fe0
#define D0F0xBC_xC00160E0_GfxVidOffset5_OFFSET                  13
#define D0F0xBC_xC00160E0_GfxVidOffset5_WIDTH                   8
#define D0F0xBC_xC00160E0_GfxVidOffset5_MASK                    0x1fe000
#define D0F0xBC_xC00160E0_GfxVidOffset6_OFFSET                  21
#define D0F0xBC_xC00160E0_GfxVidOffset6_WIDTH                   8
#define D0F0xBC_xC00160E0_GfxVidOffset6_MASK                    0x1fe00000
#define D0F0xBC_xC00160E0_Reserved29_31_OFFSET                  29
#define D0F0xBC_xC00160E0_Reserved29_31_WIDTH                   3
#define D0F0xBC_xC00160E0_Reserved29_31_MASK                    0xe0000000

/// D0F0xBC_xC00160E0
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                                  GfxVid7:8 ; ///<
    UINT32                                            GfxVidOffset5:8 ; ///<
    UINT32                                            GfxVidOffset6:8 ; ///<
    UINT32                                            Reserved29_31:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160E0_STRUCT;

// **** D0F0xBC_xC00160E3 Field Definition ****
// Address
#define D0F0xBC_xC00160E3_ADDRESS                               0xC00160e3

// Type
#define D0F0xBC_xC00160E3_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160E3_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC00160E3_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC00160E3_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC00160E3_GfxVidOffset7_OFFSET                  5
#define D0F0xBC_xC00160E3_GfxVidOffset7_WIDTH                   8
#define D0F0xBC_xC00160E3_GfxVidOffset7_MASK                    0x1fe0
#define D0F0xBC_xC00160E3_Reserved13_31_OFFSET                  13
#define D0F0xBC_xC00160E3_Reserved13_31_WIDTH                   19
#define D0F0xBC_xC00160E3_Reserved13_31_MASK                    0xffffe000

/// D0F0xBC_xC00160E3
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                            GfxVidOffset7:8 ; ///<
    UINT32                                            Reserved13_31:19; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160E3_STRUCT;

// **** D0F0xBC_xC00160F4 Field Definition ****
// Address
#define D0F0xBC_xC00160F4_ADDRESS                               0xC00160f4

// Type
#define D0F0xBC_xC00160F4_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160F4_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC00160F4_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC00160F4_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC00160F4_PowerplayPerfFlag5_OFFSET             5
#define D0F0xBC_xC00160F4_PowerplayPerfFlag5_WIDTH              1
#define D0F0xBC_xC00160F4_PowerplayPerfFlag5_MASK               0x20
#define D0F0xBC_xC00160F4_PowerplayPerfFlag6_OFFSET             6
#define D0F0xBC_xC00160F4_PowerplayPerfFlag6_WIDTH              1
#define D0F0xBC_xC00160F4_PowerplayPerfFlag6_MASK               0x40
#define D0F0xBC_xC00160F4_PowerplayPerfFlag7_OFFSET             7
#define D0F0xBC_xC00160F4_PowerplayPerfFlag7_WIDTH              1
#define D0F0xBC_xC00160F4_PowerplayPerfFlag7_MASK               0x80
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag5_OFFSET     8
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag5_WIDTH      1
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag5_MASK       0x100
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag6_OFFSET     9
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag6_WIDTH      1
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag6_MASK       0x200
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag7_OFFSET     10
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag7_WIDTH      1
#define D0F0xBC_xC00160F4_PowerplayPowerSavingsFlag7_MASK       0x400
#define D0F0xBC_xC00160F4_VCEFlag4_OFFSET                       11
#define D0F0xBC_xC00160F4_VCEFlag4_WIDTH                        8
#define D0F0xBC_xC00160F4_VCEFlag4_MASK                         0x7f800
#define D0F0xBC_xC00160F4_VCEFlag5_OFFSET                       19
#define D0F0xBC_xC00160F4_VCEFlag5_WIDTH                        8
#define D0F0xBC_xC00160F4_VCEFlag5_MASK                         0x7f80000
#define D0F0xBC_xC00160F4_Reserved27_31_OFFSET                  27
#define D0F0xBC_xC00160F4_Reserved27_31_WIDTH                   5
#define D0F0xBC_xC00160F4_Reserved27_31_MASK                    0xf8000000

/// D0F0xBC_xC00160F4
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                       PowerplayPerfFlag5:1 ; ///<
    UINT32                                       PowerplayPerfFlag6:1 ; ///<
    UINT32                                       PowerplayPerfFlag7:1 ; ///<
    UINT32                               PowerplayPowerSavingsFlag5:1 ; ///<
    UINT32                               PowerplayPowerSavingsFlag6:1 ; ///<
    UINT32                               PowerplayPowerSavingsFlag7:1 ; ///<
    UINT32                                                 VCEFlag4:8 ; ///<
    UINT32                                                 VCEFlag5:8 ; ///<
    UINT32                                            Reserved27_31:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160F4_STRUCT;

// **** D0F0xBC_xC00160F7 Field Definition ****
// Address
#define D0F0xBC_xC00160F7_ADDRESS                               0xC00160f7

// Type
#define D0F0xBC_xC00160F7_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160F7_Reserved0_2_OFFSET                    0
#define D0F0xBC_xC00160F7_Reserved0_2_WIDTH                     3
#define D0F0xBC_xC00160F7_Reserved0_2_MASK                      0x7
#define D0F0xBC_xC00160F7_VCEFlag6_OFFSET                       3
#define D0F0xBC_xC00160F7_VCEFlag6_WIDTH                        8
#define D0F0xBC_xC00160F7_VCEFlag6_MASK                         0x7f8
#define D0F0xBC_xC00160F7_Reserved11_31_OFFSET                  11
#define D0F0xBC_xC00160F7_Reserved11_31_WIDTH                   21
#define D0F0xBC_xC00160F7_Reserved11_31_MASK                    0xfffff800

/// D0F0xBC_xC00160F7
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_2:3 ; ///<
    UINT32                                                 VCEFlag6:8 ; ///<
    UINT32                                            Reserved11_31:21; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160F7_STRUCT;

// **** D0F0xBC_xC00160F8 Field Definition ****
// Address
#define D0F0xBC_xC00160F8_ADDRESS                               0xC00160f8

// Type
#define D0F0xBC_xC00160F8_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC00160F8_Reserved0_2_OFFSET                    0
#define D0F0xBC_xC00160F8_Reserved0_2_WIDTH                     3
#define D0F0xBC_xC00160F8_Reserved0_2_MASK                      0x7
#define D0F0xBC_xC00160F8_VCEFlag7_OFFSET                       3
#define D0F0xBC_xC00160F8_VCEFlag7_WIDTH                        8
#define D0F0xBC_xC00160F8_VCEFlag7_MASK                         0x7f8
#define D0F0xBC_xC00160F8_VCEMclk4_OFFSET                       11
#define D0F0xBC_xC00160F8_VCEMclk4_WIDTH                        1
#define D0F0xBC_xC00160F8_VCEMclk4_MASK                         0x800
#define D0F0xBC_xC00160F8_VCEMclk5_OFFSET                       12
#define D0F0xBC_xC00160F8_VCEMclk5_WIDTH                        1
#define D0F0xBC_xC00160F8_VCEMclk5_MASK                         0x1000
#define D0F0xBC_xC00160F8_VCEMclk6_OFFSET                       13
#define D0F0xBC_xC00160F8_VCEMclk6_WIDTH                        1
#define D0F0xBC_xC00160F8_VCEMclk6_MASK                         0x2000
#define D0F0xBC_xC00160F8_VCEMclk7_OFFSET                       14
#define D0F0xBC_xC00160F8_VCEMclk7_WIDTH                        1
#define D0F0xBC_xC00160F8_VCEMclk7_MASK                         0x4000
#define D0F0xBC_xC00160F8_Reserved15_31_OFFSET                  15
#define D0F0xBC_xC00160F8_Reserved15_31_WIDTH                   17
#define D0F0xBC_xC00160F8_Reserved15_31_MASK                    0xffff8000

/// D0F0xBC_xC00160F8
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_2:3 ; ///<
    UINT32                                                 VCEFlag7:8 ; ///<
    UINT32                                                 VCEMclk4:1 ; ///<
    UINT32                                                 VCEMclk5:1 ; ///<
    UINT32                                                 VCEMclk6:1 ; ///<
    UINT32                                                 VCEMclk7:1 ; ///<
    UINT32                                            Reserved15_31:17; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC00160F8_STRUCT;

// **** D0F0xBC_xC001704C Field Definition ****
// Address
#define D0F0xBC_xC001704C_ADDRESS                               0xC001704c

// Type
#define D0F0xBC_xC001704C_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001704C_Reserved0_11_OFFSET                   0
#define D0F0xBC_xC001704C_Reserved0_11_WIDTH                    12
#define D0F0xBC_xC001704C_Reserved0_11_MASK                     0xfff
#define D0F0xBC_xC001704C_NumBoostStates_OFFSET                 12
#define D0F0xBC_xC001704C_NumBoostStates_WIDTH                  3
#define D0F0xBC_xC001704C_NumBoostStates_MASK                   0x7000
#define D0F0xBC_xC001704C_Reserved15_31_OFFSET                  15
#define D0F0xBC_xC001704C_Reserved15_31_WIDTH                   17
#define D0F0xBC_xC001704C_Reserved15_31_MASK                    0xffff8000

/// D0F0xBC_xC001704C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved0_11:12; ///<
    UINT32                                           NumBoostStates:3 ; ///<
    UINT32                                            Reserved15_31:17; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001704C_STRUCT;

// **** D0F0xBC_xC001706C Field Definition ****
// Address
#define D0F0xBC_xC001706C_ADDRESS                               0xC001706c

// Type
#define D0F0xBC_xC001706C_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001706C_Reserved0_11_OFFSET                   0
#define D0F0xBC_xC001706C_Reserved0_11_WIDTH                    12
#define D0F0xBC_xC001706C_Reserved0_11_MASK                     0xfff
#define D0F0xBC_xC001706C_PowerplayTableRev_OFFSET              12
#define D0F0xBC_xC001706C_PowerplayTableRev_WIDTH               4
#define D0F0xBC_xC001706C_PowerplayTableRev_MASK                0xf000
#define D0F0xBC_xC001706C_Reserved16_22_OFFSET                  16
#define D0F0xBC_xC001706C_Reserved16_22_WIDTH                   7
#define D0F0xBC_xC001706C_Reserved16_22_MASK                    0x7f0000
#define D0F0xBC_xC001706C_PcieGen2Vid_OFFSET                    23
#define D0F0xBC_xC001706C_PcieGen2Vid_WIDTH                     3
#define D0F0xBC_xC001706C_PcieGen2Vid_MASK                      0x3800000
#define D0F0xBC_xC001706C_PcieGen3Vid_OFFSET                    26
#define D0F0xBC_xC001706C_PcieGen3Vid_WIDTH                     3
#define D0F0xBC_xC001706C_PcieGen3Vid_MASK                      0x1c000000
#define D0F0xBC_xC001706C_Reserved29_31_OFFSET                  29
#define D0F0xBC_xC001706C_Reserved29_31_WIDTH                   3
#define D0F0xBC_xC001706C_Reserved29_31_MASK                    0xe0000000

/// D0F0xBC_xC001706C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved0_11:12; ///<
    UINT32                                        PowerplayTableRev:4 ; ///<
    UINT32                                            Reserved16_22:7 ; ///<
    UINT32                                              PcieGen2Vid:3 ; ///<
    UINT32                                              PcieGen3Vid:3 ; ///<
    UINT32                                            Reserved29_31:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001706C_STRUCT;

// **** D0F0xBC_xC001706F Field Definition ****
// Address
#define D0F0xBC_xC001706F_ADDRESS                               0xC001706f

// Type
#define D0F0xBC_xC001706F_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001706F_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC001706F_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC001706F_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC001706F_SClkDid0_OFFSET                       5
#define D0F0xBC_xC001706F_SClkDid0_WIDTH                        7
#define D0F0xBC_xC001706F_SClkDid0_MASK                         0xfe0
#define D0F0xBC_xC001706F_Reserved12_31_OFFSET                  12
#define D0F0xBC_xC001706F_Reserved12_31_WIDTH                   20
#define D0F0xBC_xC001706F_Reserved12_31_MASK                    0xfffff000

/// D0F0xBC_xC001706F
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                                 SClkDid0:7 ; ///<
    UINT32                                            Reserved12_31:20; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001706F_STRUCT;

// **** D0F0xBC_xC0017070 Field Definition ****
// Address
#define D0F0xBC_xC0017070_ADDRESS                               0xC0017070

// Type
#define D0F0xBC_xC0017070_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017070_Reserved0_3_OFFSET                    0
#define D0F0xBC_xC0017070_Reserved0_3_WIDTH                     4
#define D0F0xBC_xC0017070_Reserved0_3_MASK                      0xf
#define D0F0xBC_xC0017070_SClkDid1_OFFSET                       4
#define D0F0xBC_xC0017070_SClkDid1_WIDTH                        7
#define D0F0xBC_xC0017070_SClkDid1_MASK                         0x7f0
#define D0F0xBC_xC0017070_SClkDid2_OFFSET                       11
#define D0F0xBC_xC0017070_SClkDid2_WIDTH                        7
#define D0F0xBC_xC0017070_SClkDid2_MASK                         0x3f800
#define D0F0xBC_xC0017070_SClkDid3_OFFSET                       18
#define D0F0xBC_xC0017070_SClkDid3_WIDTH                        7
#define D0F0xBC_xC0017070_SClkDid3_MASK                         0x1fc0000
#define D0F0xBC_xC0017070_SClkDid4_OFFSET                       25
#define D0F0xBC_xC0017070_SClkDid4_WIDTH                        7
#define D0F0xBC_xC0017070_SClkDid4_MASK                         0xfe000000

/// D0F0xBC_xC0017070
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_3:4 ; ///<
    UINT32                                                 SClkDid1:7 ; ///<
    UINT32                                                 SClkDid2:7 ; ///<
    UINT32                                                 SClkDid3:7 ; ///<
    UINT32                                                 SClkDid4:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017070_STRUCT;

// **** D0F0xBC_xC0017074 Field Definition ****
// Address
#define D0F0xBC_xC0017074_ADDRESS                               0xC0017074

// Type
#define D0F0xBC_xC0017074_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017074_DispClkDid0_OFFSET                    0
#define D0F0xBC_xC0017074_DispClkDid0_WIDTH                     7
#define D0F0xBC_xC0017074_DispClkDid0_MASK                      0x7f
#define D0F0xBC_xC0017074_DispClkDid1_OFFSET                    7
#define D0F0xBC_xC0017074_DispClkDid1_WIDTH                     7
#define D0F0xBC_xC0017074_DispClkDid1_MASK                      0x3f80
#define D0F0xBC_xC0017074_DispClkDid2_OFFSET                    14
#define D0F0xBC_xC0017074_DispClkDid2_WIDTH                     7
#define D0F0xBC_xC0017074_DispClkDid2_MASK                      0x1fc000
#define D0F0xBC_xC0017074_DispClkDid3_OFFSET                    21
#define D0F0xBC_xC0017074_DispClkDid3_WIDTH                     7
#define D0F0xBC_xC0017074_DispClkDid3_MASK                      0xfe00000
#define D0F0xBC_xC0017074_Reserved28_31_OFFSET                  28
#define D0F0xBC_xC0017074_Reserved28_31_WIDTH                   4
#define D0F0xBC_xC0017074_Reserved28_31_MASK                    0xf0000000

/// D0F0xBC_xC0017074
typedef union {
  struct {                                                              ///<
    UINT32                                              DispClkDid0:7 ; ///<
    UINT32                                              DispClkDid1:7 ; ///<
    UINT32                                              DispClkDid2:7 ; ///<
    UINT32                                              DispClkDid3:7 ; ///<
    UINT32                                            Reserved28_31:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017074_STRUCT;

// **** D0F0xBC_xC0017077 Field Definition ****
// Address
#define D0F0xBC_xC0017077_ADDRESS                               0xC0017077

// Type
#define D0F0xBC_xC0017077_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017077_Reserved0_3_OFFSET                    0
#define D0F0xBC_xC0017077_Reserved0_3_WIDTH                     4
#define D0F0xBC_xC0017077_Reserved0_3_MASK                      0xf
#define D0F0xBC_xC0017077_DispClkDid4_OFFSET                    4
#define D0F0xBC_xC0017077_DispClkDid4_WIDTH                     7
#define D0F0xBC_xC0017077_DispClkDid4_MASK                      0x7f0
#define D0F0xBC_xC0017077_Reserved11_31_OFFSET                  11
#define D0F0xBC_xC0017077_Reserved11_31_WIDTH                   21
#define D0F0xBC_xC0017077_Reserved11_31_MASK                    0xfffff800

/// D0F0xBC_xC0017077
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_3:4 ; ///<
    UINT32                                              DispClkDid4:7 ; ///<
    UINT32                                            Reserved11_31:21; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017077_STRUCT;

// **** D0F0xBC_xC0017078 Field Definition ****
// Address
#define D0F0xBC_xC0017078_ADDRESS                               0xC0017078

// Type
#define D0F0xBC_xC0017078_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017078_Reserved0_2_OFFSET                    0
#define D0F0xBC_xC0017078_Reserved0_2_WIDTH                     3
#define D0F0xBC_xC0017078_Reserved0_2_MASK                      0x7
#define D0F0xBC_xC0017078_LClkDpmDid0_OFFSET                    3
#define D0F0xBC_xC0017078_LClkDpmDid0_WIDTH                     7
#define D0F0xBC_xC0017078_LClkDpmDid0_MASK                      0x3f8
#define D0F0xBC_xC0017078_LClkDpmDid1_OFFSET                    10
#define D0F0xBC_xC0017078_LClkDpmDid1_WIDTH                     7
#define D0F0xBC_xC0017078_LClkDpmDid1_MASK                      0x1fc00
#define D0F0xBC_xC0017078_LClkDpmDid2_OFFSET                    17
#define D0F0xBC_xC0017078_LClkDpmDid2_WIDTH                     7
#define D0F0xBC_xC0017078_LClkDpmDid2_MASK                      0xfe0000
#define D0F0xBC_xC0017078_LClkDpmDid3_OFFSET                    24
#define D0F0xBC_xC0017078_LClkDpmDid3_WIDTH                     7
#define D0F0xBC_xC0017078_LClkDpmDid3_MASK                      0x7f000000
#define D0F0xBC_xC0017078_Reserved31_31_OFFSET                  31
#define D0F0xBC_xC0017078_Reserved31_31_WIDTH                   1
#define D0F0xBC_xC0017078_Reserved31_31_MASK                    0x80000000

/// D0F0xBC_xC0017078
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_2:3 ; ///<
    UINT32                                              LClkDpmDid0:7 ; ///<
    UINT32                                              LClkDpmDid1:7 ; ///<
    UINT32                                              LClkDpmDid2:7 ; ///<
    UINT32                                              LClkDpmDid3:7 ; ///<
    UINT32                                            Reserved31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017078_STRUCT;

// **** D0F0xBC_xC001707B Field Definition ****
// Address
#define D0F0xBC_xC001707B_ADDRESS                               0xC001707b

// Type
#define D0F0xBC_xC001707B_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001707B_Reserved0_6_OFFSET                    0
#define D0F0xBC_xC001707B_Reserved0_6_WIDTH                     7
#define D0F0xBC_xC001707B_Reserved0_6_MASK                      0x7f
#define D0F0xBC_xC001707B_LClkDpmDid4_OFFSET                    7
#define D0F0xBC_xC001707B_LClkDpmDid4_WIDTH                     7
#define D0F0xBC_xC001707B_LClkDpmDid4_MASK                      0x3f80
#define D0F0xBC_xC001707B_Reserved14_31_OFFSET                  14
#define D0F0xBC_xC001707B_Reserved14_31_WIDTH                   18
#define D0F0xBC_xC001707B_Reserved14_31_MASK                    0xffffc000

/// D0F0xBC_xC001707B
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_6:7 ; ///<
    UINT32                                              LClkDpmDid4:7 ; ///<
    UINT32                                            Reserved14_31:18; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001707B_STRUCT;

// **** D0F0xBC_xC001707C Field Definition ****
// Address
#define D0F0xBC_xC001707C_ADDRESS                               0xC001707c

// Type
#define D0F0xBC_xC001707C_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001707C_Reserved0_5_OFFSET                    0
#define D0F0xBC_xC001707C_Reserved0_5_WIDTH                     6
#define D0F0xBC_xC001707C_Reserved0_5_MASK                      0x3f
#define D0F0xBC_xC001707C_DClkDid0_OFFSET                       6
#define D0F0xBC_xC001707C_DClkDid0_WIDTH                        7
#define D0F0xBC_xC001707C_DClkDid0_MASK                         0x1fc0
#define D0F0xBC_xC001707C_DClkDid1_OFFSET                       13
#define D0F0xBC_xC001707C_DClkDid1_WIDTH                        7
#define D0F0xBC_xC001707C_DClkDid1_MASK                         0xfe000
#define D0F0xBC_xC001707C_DClkDid2_OFFSET                       20
#define D0F0xBC_xC001707C_DClkDid2_WIDTH                        7
#define D0F0xBC_xC001707C_DClkDid2_MASK                         0x7f00000
#define D0F0xBC_xC001707C_Reserved27_31_OFFSET                  27
#define D0F0xBC_xC001707C_Reserved27_31_WIDTH                   5
#define D0F0xBC_xC001707C_Reserved27_31_MASK                    0xf8000000

/// D0F0xBC_xC001707C
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_5:6 ; ///<
    UINT32                                                 DClkDid0:7 ; ///<
    UINT32                                                 DClkDid1:7 ; ///<
    UINT32                                                 DClkDid2:7 ; ///<
    UINT32                                            Reserved27_31:5 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001707C_STRUCT;

// **** D0F0xBC_xC001707F Field Definition ****
// Address
#define D0F0xBC_xC001707F_ADDRESS                               0xC001707f

// Type
#define D0F0xBC_xC001707F_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001707F_Reserved0_2_OFFSET                    0
#define D0F0xBC_xC001707F_Reserved0_2_WIDTH                     3
#define D0F0xBC_xC001707F_Reserved0_2_MASK                      0x7
#define D0F0xBC_xC001707F_DClkDid3_OFFSET                       3
#define D0F0xBC_xC001707F_DClkDid3_WIDTH                        7
#define D0F0xBC_xC001707F_DClkDid3_MASK                         0x3f8
#define D0F0xBC_xC001707F_Reserved10_31_OFFSET                  10
#define D0F0xBC_xC001707F_Reserved10_31_WIDTH                   22
#define D0F0xBC_xC001707F_Reserved10_31_MASK                    0xfffffc00

/// D0F0xBC_xC001707F
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_2:3 ; ///<
    UINT32                                                 DClkDid3:7 ; ///<
    UINT32                                            Reserved10_31:22; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001707F_STRUCT;

// **** D0F0xBC_xC0017080 Field Definition ****
// Address
#define D0F0xBC_xC0017080_ADDRESS                               0xC0017080

// Type
#define D0F0xBC_xC0017080_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017080_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC0017080_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC0017080_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC0017080_DClkDid4_OFFSET                       2
#define D0F0xBC_xC0017080_DClkDid4_WIDTH                        7
#define D0F0xBC_xC0017080_DClkDid4_MASK                         0x1fc
#define D0F0xBC_xC0017080_VClkDid0_OFFSET                       9
#define D0F0xBC_xC0017080_VClkDid0_WIDTH                        7
#define D0F0xBC_xC0017080_VClkDid0_MASK                         0xfe00
#define D0F0xBC_xC0017080_VClkDid1_OFFSET                       16
#define D0F0xBC_xC0017080_VClkDid1_WIDTH                        7
#define D0F0xBC_xC0017080_VClkDid1_MASK                         0x7f0000
#define D0F0xBC_xC0017080_VClkDid2_OFFSET                       23
#define D0F0xBC_xC0017080_VClkDid2_WIDTH                        7
#define D0F0xBC_xC0017080_VClkDid2_MASK                         0x3f800000
#define D0F0xBC_xC0017080_Reserved30_31_OFFSET                  30
#define D0F0xBC_xC0017080_Reserved30_31_WIDTH                   2
#define D0F0xBC_xC0017080_Reserved30_31_MASK                    0xc0000000

/// D0F0xBC_xC0017080
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                 DClkDid4:7 ; ///<
    UINT32                                                 VClkDid0:7 ; ///<
    UINT32                                                 VClkDid1:7 ; ///<
    UINT32                                                 VClkDid2:7 ; ///<
    UINT32                                            Reserved30_31:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017080_STRUCT;

// **** D0F0xBC_xC0017083 Field Definition ****
// Address
#define D0F0xBC_xC0017083_ADDRESS                               0xC0017083

// Type
#define D0F0xBC_xC0017083_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017083_Reserved0_5_OFFSET                    0
#define D0F0xBC_xC0017083_Reserved0_5_WIDTH                     6
#define D0F0xBC_xC0017083_Reserved0_5_MASK                      0x3f
#define D0F0xBC_xC0017083_VClkDid3_OFFSET                       6
#define D0F0xBC_xC0017083_VClkDid3_WIDTH                        7
#define D0F0xBC_xC0017083_VClkDid3_MASK                         0x1fc0
#define D0F0xBC_xC0017083_Reserved13_31_OFFSET                  13
#define D0F0xBC_xC0017083_Reserved13_31_WIDTH                   19
#define D0F0xBC_xC0017083_Reserved13_31_MASK                    0xffffe000

/// D0F0xBC_xC0017083
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_5:6 ; ///<
    UINT32                                                 VClkDid3:7 ; ///<
    UINT32                                            Reserved13_31:19; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017083_STRUCT;

// **** D0F0xBC_xC0017084 Field Definition ****
// Address
#define D0F0xBC_xC0017084_ADDRESS                               0xC0017084

// Type
#define D0F0xBC_xC0017084_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017084_Reserved0_4_OFFSET                    0
#define D0F0xBC_xC0017084_Reserved0_4_WIDTH                     5
#define D0F0xBC_xC0017084_Reserved0_4_MASK                      0x1f
#define D0F0xBC_xC0017084_VClkDid4_OFFSET                       5
#define D0F0xBC_xC0017084_VClkDid4_WIDTH                        7
#define D0F0xBC_xC0017084_VClkDid4_MASK                         0xfe0
#define D0F0xBC_xC0017084_EClkDid0_OFFSET                       12
#define D0F0xBC_xC0017084_EClkDid0_WIDTH                        7
#define D0F0xBC_xC0017084_EClkDid0_MASK                         0x7f000
#define D0F0xBC_xC0017084_EClkDid1_OFFSET                       19
#define D0F0xBC_xC0017084_EClkDid1_WIDTH                        7
#define D0F0xBC_xC0017084_EClkDid1_MASK                         0x3f80000
#define D0F0xBC_xC0017084_Reserved26_31_OFFSET                  26
#define D0F0xBC_xC0017084_Reserved26_31_WIDTH                   6
#define D0F0xBC_xC0017084_Reserved26_31_MASK                    0xfc000000

/// D0F0xBC_xC0017084
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_4:5 ; ///<
    UINT32                                                 VClkDid4:7 ; ///<
    UINT32                                                 EClkDid0:7 ; ///<
    UINT32                                                 EClkDid1:7 ; ///<
    UINT32                                            Reserved26_31:6 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017084_STRUCT;

// **** D0F0xBC_xC0017087 Field Definition ****
// Address
#define D0F0xBC_xC0017087_ADDRESS                               0xC0017087

// Type
#define D0F0xBC_xC0017087_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017087_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC0017087_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC0017087_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC0017087_EClkDid2_OFFSET                       2
#define D0F0xBC_xC0017087_EClkDid2_WIDTH                        7
#define D0F0xBC_xC0017087_EClkDid2_MASK                         0x1fc
#define D0F0xBC_xC0017087_Reserved9_31_OFFSET                   9
#define D0F0xBC_xC0017087_Reserved9_31_WIDTH                    23
#define D0F0xBC_xC0017087_Reserved9_31_MASK                     0xfffffe00

/// D0F0xBC_xC0017087
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                 EClkDid2:7 ; ///<
    UINT32                                             Reserved9_31:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017087_STRUCT;

// **** D0F0xBC_xC0017088 Field Definition ****
// Address
#define D0F0xBC_xC0017088_ADDRESS                               0xC0017088

// Type
#define D0F0xBC_xC0017088_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017088_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC0017088_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC0017088_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC0017088_EClkDid3_OFFSET                       1
#define D0F0xBC_xC0017088_EClkDid3_WIDTH                        7
#define D0F0xBC_xC0017088_EClkDid3_MASK                         0xfe
#define D0F0xBC_xC0017088_EClkDid4_OFFSET                       8
#define D0F0xBC_xC0017088_EClkDid4_WIDTH                        7
#define D0F0xBC_xC0017088_EClkDid4_MASK                         0x7f00
#define D0F0xBC_xC0017088_PowerplayPerfFlag_OFFSET              15
#define D0F0xBC_xC0017088_PowerplayPerfFlag_WIDTH               5
#define D0F0xBC_xC0017088_PowerplayPerfFlag_MASK                0xf8000
#define D0F0xBC_xC0017088_PowerplayPowerSavingsFlag_OFFSET      20
#define D0F0xBC_xC0017088_PowerplayPowerSavingsFlag_WIDTH       5
#define D0F0xBC_xC0017088_PowerplayPowerSavingsFlag_MASK        0x1f00000
#define D0F0xBC_xC0017088_Reserved25_31_OFFSET                  25
#define D0F0xBC_xC0017088_Reserved25_31_WIDTH                   7
#define D0F0xBC_xC0017088_Reserved25_31_MASK                    0xfe000000

/// D0F0xBC_xC0017088
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                                 EClkDid3:7 ; ///<
    UINT32                                                 EClkDid4:7 ; ///<
    UINT32                                        PowerplayPerfFlag:5 ; ///<
    UINT32                                PowerplayPowerSavingsFlag:5 ; ///<
    UINT32                                            Reserved25_31:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017088_STRUCT;

// **** D0F0xBC_xC0017107 Field Definition ****
// Address
#define D0F0xBC_xC0017107_ADDRESS                               0xC0017107

// Type
#define D0F0xBC_xC0017107_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017107_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC0017107_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC0017107_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC0017107_AClkDid0_OFFSET                       2
#define D0F0xBC_xC0017107_AClkDid0_WIDTH                        7
#define D0F0xBC_xC0017107_AClkDid0_MASK                         0x1fc


/// D0F0xBC_xC0017107
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                                 AClkDid0:7 ; ///<
    UINT32                                             Reserved9_31:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017107_STRUCT;

// **** D0F0xBC_xC0017108 Field Definition ****
// Address
#define D0F0xBC_xC0017108_ADDRESS                               0xC0017108

// Type
#define D0F0xBC_xC0017108_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017108_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC0017108_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC0017108_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC0017108_AClkDid1_OFFSET                       1
#define D0F0xBC_xC0017108_AClkDid1_WIDTH                        7
#define D0F0xBC_xC0017108_AClkDid1_MASK                         0xfe
#define D0F0xBC_xC0017108_AClkDid2_OFFSET                       8
#define D0F0xBC_xC0017108_AClkDid2_WIDTH                        7
#define D0F0xBC_xC0017108_AClkDid2_MASK                         0x7f00
#define D0F0xBC_xC0017108_AClkDid3_OFFSET                       15
#define D0F0xBC_xC0017108_AClkDid3_WIDTH                        7
#define D0F0xBC_xC0017108_AClkDid3_MASK                         0x3f8000
#define D0F0xBC_xC0017108_AClkDid4_OFFSET                       22
#define D0F0xBC_xC0017108_AClkDid4_WIDTH                        7
#define D0F0xBC_xC0017108_AClkDid4_MASK                         0x1fc00000
#define D0F0xBC_xC0017108_Reserved29_31_OFFSET                  29
#define D0F0xBC_xC0017108_Reserved29_31_WIDTH                   3
#define D0F0xBC_xC0017108_Reserved29_31_MASK                    0xe0000000

/// D0F0xBC_xC0017108
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                                 AClkDid1:7 ; ///<
    UINT32                                                 AClkDid2:7 ; ///<
    UINT32                                                 AClkDid3:7 ; ///<
    UINT32                                                 AClkDid4:7 ; ///<
    UINT32                                            Reserved29_31:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017108_STRUCT;

// **** D0F0xBC_xC001711C Field Definition ****
// Address
#define D0F0xBC_xC001711C_ADDRESS                               0xC001711c

// Type
#define D0F0xBC_xC001711C_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001711C_Reserved0_14_OFFSET                   0
#define D0F0xBC_xC001711C_Reserved0_14_WIDTH                    15
#define D0F0xBC_xC001711C_Reserved0_14_MASK                     0x7fff
#define D0F0xBC_xC001711C_VCEFlag0_OFFSET                       15
#define D0F0xBC_xC001711C_VCEFlag0_WIDTH                        8
#define D0F0xBC_xC001711C_VCEFlag0_MASK                         0x7f8000
#define D0F0xBC_xC001711C_VCEFlag1_OFFSET                       23
#define D0F0xBC_xC001711C_VCEFlag1_WIDTH                        8
#define D0F0xBC_xC001711C_VCEFlag1_MASK                         0x7f800000
#define D0F0xBC_xC001711C_Reserved31_31_OFFSET                  31
#define D0F0xBC_xC001711C_Reserved31_31_WIDTH                   1
#define D0F0xBC_xC001711C_Reserved31_31_MASK                    0x80000000

/// D0F0xBC_xC001711C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved0_14:15; ///<
    UINT32                                                 VCEFlag0:8 ; ///<
    UINT32                                                 VCEFlag1:8 ; ///<
    UINT32                                            Reserved31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001711C_STRUCT;

// **** D0F0xBC_xC001711F Field Definition ****
// Address
#define D0F0xBC_xC001711F_ADDRESS                               0xC001711f

// Type
#define D0F0xBC_xC001711F_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001711F_Reserved0_6_OFFSET                    0
#define D0F0xBC_xC001711F_Reserved0_6_WIDTH                     7
#define D0F0xBC_xC001711F_Reserved0_6_MASK                      0x7f
#define D0F0xBC_xC001711F_VCEFlag2_OFFSET                       7
#define D0F0xBC_xC001711F_VCEFlag2_WIDTH                        8
#define D0F0xBC_xC001711F_VCEFlag2_MASK                         0x7f80
#define D0F0xBC_xC001711F_Reserved15_31_OFFSET                  15
#define D0F0xBC_xC001711F_Reserved15_31_WIDTH                   17
#define D0F0xBC_xC001711F_Reserved15_31_MASK                    0xffff8000

/// D0F0xBC_xC001711F
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_6:7 ; ///<
    UINT32                                                 VCEFlag2:8 ; ///<
    UINT32                                            Reserved15_31:17; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001711F_STRUCT;

// **** D0F0xBC_xC0017120 Field Definition ****
// Address
#define D0F0xBC_xC0017120_ADDRESS                               0xC0017120

// Type
#define D0F0xBC_xC0017120_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017120_Reserved0_6_OFFSET                    0
#define D0F0xBC_xC0017120_Reserved0_6_WIDTH                     7
#define D0F0xBC_xC0017120_Reserved0_6_MASK                      0x7f
#define D0F0xBC_xC0017120_VCEFlag3_OFFSET                       7
#define D0F0xBC_xC0017120_VCEFlag3_WIDTH                        8
#define D0F0xBC_xC0017120_VCEFlag3_MASK                         0x7f80
#define D0F0xBC_xC0017120_VCEMclk_OFFSET                        15
#define D0F0xBC_xC0017120_VCEMclk_WIDTH                         4
#define D0F0xBC_xC0017120_VCEMclk_MASK                          0x78000
#define D0F0xBC_xC0017120_Reserved19_31_OFFSET                  19
#define D0F0xBC_xC0017120_Reserved19_31_WIDTH                   13
#define D0F0xBC_xC0017120_Reserved19_31_MASK                    0xfff80000

/// D0F0xBC_xC0017120
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_6:7 ; ///<
    UINT32                                                 VCEFlag3:8 ; ///<
    UINT32                                                  VCEMclk:4 ; ///<
    UINT32                                            Reserved19_31:13; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017120_STRUCT;

// **** D0F0xBC_xC001712C Field Definition ****
// Address
#define D0F0xBC_xC001712C_ADDRESS                               0xC001712c

// Type
#define D0F0xBC_xC001712C_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001712C_Reserved0_16_OFFSET                   0
#define D0F0xBC_xC001712C_Reserved0_16_WIDTH                    17
#define D0F0xBC_xC001712C_Reserved0_16_MASK                     0x1ffff
#define D0F0xBC_xC001712C_GnbVidOffset0_OFFSET                  17
#define D0F0xBC_xC001712C_GnbVidOffset0_WIDTH                   8
#define D0F0xBC_xC001712C_GnbVidOffset0_MASK                    0x1fe0000
#define D0F0xBC_xC001712C_Reserved25_31_OFFSET                  25
#define D0F0xBC_xC001712C_Reserved25_31_WIDTH                   7
#define D0F0xBC_xC001712C_Reserved25_31_MASK                    0xfe000000

/// D0F0xBC_xC001712C
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved0_16:17; ///<
    UINT32                                            GnbVidOffset0:8 ; ///<
    UINT32                                            Reserved25_31:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001712C_STRUCT;

// **** D0F0xBC_xC001712F Field Definition ****
// Address
#define D0F0xBC_xC001712F_ADDRESS                               0xC001712f

// Type
#define D0F0xBC_xC001712F_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC001712F_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC001712F_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC001712F_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC001712F_GnbVidOffset1_OFFSET                  1
#define D0F0xBC_xC001712F_GnbVidOffset1_WIDTH                   8
#define D0F0xBC_xC001712F_GnbVidOffset1_MASK                    0x1fe
#define D0F0xBC_xC001712F_Reserved9_31_OFFSET                   9
#define D0F0xBC_xC001712F_Reserved9_31_WIDTH                    23
#define D0F0xBC_xC001712F_Reserved9_31_MASK                     0xfffffe00

/// D0F0xBC_xC001712F
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                            GnbVidOffset1:8 ; ///<
    UINT32                                             Reserved9_31:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC001712F_STRUCT;

// **** D0F0xBC_xC0017130 Field Definition ****
// Address
#define D0F0xBC_xC0017130_ADDRESS                               0xC0017130

// Type
#define D0F0xBC_xC0017130_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017130_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC0017130_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC0017130_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC0017130_GnbVidOffset2_OFFSET                  1
#define D0F0xBC_xC0017130_GnbVidOffset2_WIDTH                   8
#define D0F0xBC_xC0017130_GnbVidOffset2_MASK                    0x1fe
#define D0F0xBC_xC0017130_GnbVidOffset3_OFFSET                  9
#define D0F0xBC_xC0017130_GnbVidOffset3_WIDTH                   8
#define D0F0xBC_xC0017130_GnbVidOffset3_MASK                    0x1fe00
#define D0F0xBC_xC0017130_GnbVidOffset4_OFFSET                  17
#define D0F0xBC_xC0017130_GnbVidOffset4_WIDTH                   8
#define D0F0xBC_xC0017130_GnbVidOffset4_MASK                    0x1fe0000
#define D0F0xBC_xC0017130_Reserved25_31_OFFSET                  25
#define D0F0xBC_xC0017130_Reserved25_31_WIDTH                   7
#define D0F0xBC_xC0017130_Reserved25_31_MASK                    0xfe000000

/// D0F0xBC_xC0017130
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                            GnbVidOffset2:8 ; ///<
    UINT32                                            GnbVidOffset3:8 ; ///<
    UINT32                                            GnbVidOffset4:8 ; ///<
    UINT32                                            Reserved25_31:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017130_STRUCT;

// **** D0F0xBC_xC0017134 Field Definition ****
// Address
#define D0F0xBC_xC0017134_ADDRESS                               0xC0017134

// Type
#define D0F0xBC_xC0017134_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017134_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC0017134_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC0017134_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC0017134_GfxVidOffset0_OFFSET                  1
#define D0F0xBC_xC0017134_GfxVidOffset0_WIDTH                   8
#define D0F0xBC_xC0017134_GfxVidOffset0_MASK                    0x1fe
#define D0F0xBC_xC0017134_GfxVidOffset1_OFFSET                  9
#define D0F0xBC_xC0017134_GfxVidOffset1_WIDTH                   8
#define D0F0xBC_xC0017134_GfxVidOffset1_MASK                    0x1fe00
#define D0F0xBC_xC0017134_GfxVidOffset2_OFFSET                  17
#define D0F0xBC_xC0017134_GfxVidOffset2_WIDTH                   8
#define D0F0xBC_xC0017134_GfxVidOffset2_MASK                    0x1fe0000
#define D0F0xBC_xC0017134_Reserved25_31_OFFSET                  25
#define D0F0xBC_xC0017134_Reserved25_31_WIDTH                   7
#define D0F0xBC_xC0017134_Reserved25_31_MASK                    0xfe000000

/// D0F0xBC_xC0017134
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                            GfxVidOffset0:8 ; ///<
    UINT32                                            GfxVidOffset1:8 ; ///<
    UINT32                                            GfxVidOffset2:8 ; ///<
    UINT32                                            Reserved25_31:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017134_STRUCT;

// **** D0F0xBC_xC0017137 Field Definition ****
// Address
#define D0F0xBC_xC0017137_ADDRESS                               0xC0017137

// Type
#define D0F0xBC_xC0017137_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017137_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC0017137_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC0017137_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC0017137_GfxVidOffset3_OFFSET                  1
#define D0F0xBC_xC0017137_GfxVidOffset3_WIDTH                   8
#define D0F0xBC_xC0017137_GfxVidOffset3_MASK                    0x1fe
#define D0F0xBC_xC0017137_Reserved9_31_OFFSET                   9
#define D0F0xBC_xC0017137_Reserved9_31_WIDTH                    23
#define D0F0xBC_xC0017137_Reserved9_31_MASK                     0xfffffe00

/// D0F0xBC_xC0017137
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                            GfxVidOffset3:8 ; ///<
    UINT32                                             Reserved9_31:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017137_STRUCT;

// **** D0F0xBC_xC0017138 Field Definition ****
// Address
#define D0F0xBC_xC0017138_ADDRESS                               0xC0017138

// Type
#define D0F0xBC_xC0017138_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017138_Reserved0_0_OFFSET                    0
#define D0F0xBC_xC0017138_Reserved0_0_WIDTH                     1
#define D0F0xBC_xC0017138_Reserved0_0_MASK                      0x1
#define D0F0xBC_xC0017138_GfxVidOffset4_OFFSET                  1
#define D0F0xBC_xC0017138_GfxVidOffset4_WIDTH                   8
#define D0F0xBC_xC0017138_GfxVidOffset4_MASK                    0x1fe
#define D0F0xBC_xC0017138_Reserved9_31_OFFSET                   9
#define D0F0xBC_xC0017138_Reserved9_31_WIDTH                    23
#define D0F0xBC_xC0017138_Reserved9_31_MASK                     0xfffffe00

/// D0F0xBC_xC0017138
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                            GfxVidOffset4:8 ; ///<
    UINT32                                             Reserved9_31:23; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017138_STRUCT;

// **** D0F0xBC_xC0017164 Field Definition ****
// Address
#define D0F0xBC_xC0017164_ADDRESS                               0xC0017164

// Type
#define D0F0xBC_xC0017164_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017164_Reserved0_1_OFFSET                    0
#define D0F0xBC_xC0017164_Reserved0_1_WIDTH                     2
#define D0F0xBC_xC0017164_Reserved0_1_MASK                      0x3
#define D0F0xBC_xC0017164_ReqSclkSel0_OFFSET                    2
#define D0F0xBC_xC0017164_ReqSclkSel0_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel0_MASK                      0x3c
#define D0F0xBC_xC0017164_ReqSclkSel1_OFFSET                    6
#define D0F0xBC_xC0017164_ReqSclkSel1_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel1_MASK                      0x3c0
#define D0F0xBC_xC0017164_ReqSclkSel2_OFFSET                    10
#define D0F0xBC_xC0017164_ReqSclkSel2_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel2_MASK                      0x3c00
#define D0F0xBC_xC0017164_ReqSclkSel3_OFFSET                    14
#define D0F0xBC_xC0017164_ReqSclkSel3_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel3_MASK                      0x3c000
#define D0F0xBC_xC0017164_ReqSclkSel4_OFFSET                    18
#define D0F0xBC_xC0017164_ReqSclkSel4_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel4_MASK                      0x3c0000
#define D0F0xBC_xC0017164_ReqSclkSel5_OFFSET                    22
#define D0F0xBC_xC0017164_ReqSclkSel5_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel5_MASK                      0x3c00000
#define D0F0xBC_xC0017164_ReqSclkSel6_OFFSET                    26
#define D0F0xBC_xC0017164_ReqSclkSel6_WIDTH                     4
#define D0F0xBC_xC0017164_ReqSclkSel6_MASK                      0x3c000000

/// D0F0xBC_xC0017164
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_1:2 ; ///<
    UINT32                                              ReqSclkSel0:4 ; ///<
    UINT32                                              ReqSclkSel1:4 ; ///<
    UINT32                                              ReqSclkSel2:4 ; ///<
    UINT32                                              ReqSclkSel3:4 ; ///<
    UINT32                                              ReqSclkSel4:4 ; ///<
    UINT32                                              ReqSclkSel5:4 ; ///<
    UINT32                                              ReqSclkSel6:4 ; ///<
    UINT32                                            Reserved30_31:2 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017164_STRUCT;

// **** D0F0xBC_xC0017167 Field Definition ****
// Address
#define D0F0xBC_xC0017167_ADDRESS                               0xC0017167

// Type
#define D0F0xBC_xC0017167_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xC0017167_ReqSclkSel7_OFFSET                    6
#define D0F0xBC_xC0017167_ReqSclkSel7_WIDTH                     4
#define D0F0xBC_xC0017167_ReqSclkSel7_MASK                      0x3c0

/// D0F0xBC_xC0017167
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_5:6 ; ///<
    UINT32                                              ReqSclkSel7:4 ; ///<
    UINT32                                           Reserved10_31:22 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xC0017167_STRUCT;

  // **** D0F0xBC_xD8230F00 Field Definition ****
// Address
#define D0F0xBC_xD8230F00_ADDRESS                               0xD8230F00

// Type
#define D0F0xBC_xD8230F00_TYPE                                  TYPE_D0F0xBC
#define D0F0xBC_xD8230F00_COF_VID_PROG_OFFSET                  1
#define D0F0xBC_xD8230F00_COF_VID_PROG_WIDTH                   1
#define D0F0xBC_xD8230F00_COF_VID_PROG_MASK                    0x2

/// D0F0xBC_xD8230F00
typedef union {
  struct {                                                              ///<
    UINT32                                              Reserved0_0:1 ; ///<
    UINT32                                             COF_VID_PROG:1 ; ///<
    UINT32                                             Reserved2_31:30; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xD8230F00_STRUCT;


// **** D0F0x4C Register Definition ****
// Address
#define D0F0x4C_ADDRESS                                         0x4c
// Type
#define D0F0x4C_TYPE                                            TYPE_D0F0

// **** D0F0x64_x17 Register Definition ****
// Address
#define D0F0x64_x17_ADDRESS                                     0x17
// Type
#define D0F0x64_x17_TYPE                                        TYPE_D0F0x64

// **** D0F0x64_x18 Register Definition ****
// Address
#define D0F0x64_x18_ADDRESS                                     0x18
// Type
#define D0F0x64_x18_TYPE                                        TYPE_D0F0x64

// **** D0F0x64_x19 Register Definition ****
// Address
#define D0F0x64_x19_ADDRESS                                     0x19
// Type
#define D0F0x64_x19_TYPE                                        TYPE_D0F0x64


// **** D0F0x64_x1A Register Definition ****
// Address
#define D0F0x64_x1A_ADDRESS                                     0x1a
// Type
#define D0F0x64_x1A_TYPE                                        TYPE_D0F0x64

// **** D0F0x64_x4E Register Definition ****
// Address
#define D0F0x64_x4E_ADDRESS                                     0x4e
// Type
#define D0F0x64_x4E_TYPE                                        TYPE_D0F0x64

// **** D0F0x84 Register Definition ****
// Address
#define D0F0x84_ADDRESS                                         0x84
// Type
#define D0F0x84_TYPE                                            TYPE_D0F0

// **** D0F0x90 Register Definition ****
// Address
#define D0F0x90_ADDRESS                                         0x90
// Type
#define D0F0x90_TYPE                                            TYPE_D0F0

// **** D18F1xF0 Register Definition ****
// Address
#define D18F1xF0_ADDRESS                                        0xF0
// Type
#define D18F1xF0_TYPE                                           TYPE_D18F1

// **** D18F1x200 Register Definition ****
// Address
#define D18F1x200_ADDRESS                                       0x200
// Type
#define D18F1x200_TYPE                                          TYPE_D18F1

// **** D18F1x204 Register Definition ****
// Address
#define D18F1x204_ADDRESS                                       0x204
// Type
#define D18F1x204_TYPE                                          TYPE_D18F1

// **** D18F1x208 Register Definition ****
// Address
#define D18F1x208_ADDRESS                                       0x208
// Type
#define D18F1x208_TYPE                                          TYPE_D18F1

// **** D18F1x20C Register Definition ****
// Address
#define D18F1x20C_ADDRESS                                       0x20C
// Type
#define D18F1x20C_TYPE                                          TYPE_D18F1

// **** D18F1x240 Register Definition ****
// Address
#define D18F1x240_ADDRESS                                       0x240
// Type
#define D18F1x240_TYPE                                          TYPE_D18F1

// **** D18F1x244 Register Definition ****
// Address
#define D18F1x244_ADDRESS                                       0x244
// Type
#define D18F1x244_TYPE                                          TYPE_D18F1

// **** D18F2x40_dct1 Register Definition ****
// Address
#define D18F2x40_dct1_ADDRESS                                   0x40
// Type
#define D18F2x40_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x40_dct0 Register Definition ****
// Address
#define D18F2x40_dct0_ADDRESS                                   0x40
// Type
#define D18F2x40_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x44_dct1 Register Definition ****
// Address
#define D18F2x44_dct1_ADDRESS                                   0x44
// Type
#define D18F2x44_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x44_dct0 Register Definition ****
// Address
#define D18F2x44_dct0_ADDRESS                                   0x44
// Type
#define D18F2x44_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x48_dct1 Register Definition ****
// Address
#define D18F2x48_dct1_ADDRESS                                   0x48
// Type
#define D18F2x48_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x48_dct0 Register Definition ****
// Address
#define D18F2x48_dct0_ADDRESS                                   0x48
// Type
#define D18F2x48_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x4C_dct0 Register Definition ****
// Address
#define D18F2x4C_dct0_ADDRESS                                   0x4C
// Type
#define D18F2x4C_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x4C_dct1 Register Definition ****
// Address
#define D18F2x4C_dct1_ADDRESS                                   0x4C
// Type
#define D18F2x4C_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x60_dct1 Register Definition ****
// Address
#define D18F2x60_dct1_ADDRESS                                   0x60
// Type
#define D18F2x60_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x60_dct0 Register Definition ****
// Address
#define D18F2x60_dct0_ADDRESS                                   0x60
// Type
#define D18F2x60_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x64_dct0 Register Definition ****
// Address
#define D18F2x64_dct0_ADDRESS                                   0x64
// Type
#define D18F2x64_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x64_dct1 Register Definition ****
// Address
#define D18F2x64_dct1_ADDRESS                                   0x64
// Type
#define D18F2x64_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x78_dct0 Register Definition ****
// Address
#define D18F2x78_dct0_ADDRESS                                   0x78
// Type
#define D18F2x78_dct0_TYPE                                      TYPE_D18F2_dct0
// Field Data
#define D18F2x78_dct0_ChanVal_OFFSET                            0
#define D18F2x78_dct0_ChanVal_WIDTH                             1
#define D18F2x78_dct0_ChanVal_MASK                              0x1
#define D18F2x78_dct0_Reserved_1_1_OFFSET                       1
#define D18F2x78_dct0_Reserved_1_1_WIDTH                        1
#define D18F2x78_dct0_Reserved_1_1_MASK                         0x2
#define D18F2x78_dct0_GsyncDis_OFFSET                           2
#define D18F2x78_dct0_GsyncDis_WIDTH                            1
#define D18F2x78_dct0_GsyncDis_MASK                             0x4
#define D18F2x78_dct0_Reserved_3_3_OFFSET                       3
#define D18F2x78_dct0_Reserved_3_3_WIDTH                        1
#define D18F2x78_dct0_Reserved_3_3_MASK                         0x8
#define D18F2x78_dct0_PtrInitReq_OFFSET                         4
#define D18F2x78_dct0_PtrInitReq_WIDTH                          1
#define D18F2x78_dct0_PtrInitReq_MASK                           0x10
#define D18F2x78_dct0_Reserved_7_5_OFFSET                       5
#define D18F2x78_dct0_Reserved_7_5_WIDTH                        3
#define D18F2x78_dct0_Reserved_7_5_MASK                         0xe0
#define D18F2x78_dct0_DramType_OFFSET                           8
#define D18F2x78_dct0_DramType_WIDTH                            3
#define D18F2x78_dct0_DramType_MASK                             0x700
#define D18F2x78_dct0_Reserved_14_11_OFFSET                     11
#define D18F2x78_dct0_Reserved_14_11_WIDTH                      4
#define D18F2x78_dct0_Reserved_14_11_MASK                       0x7800
#define D18F2x78_dct0_Reserved_15_15_OFFSET                     15
#define D18F2x78_dct0_Reserved_15_15_WIDTH                      1
#define D18F2x78_dct0_Reserved_15_15_MASK                       0x8000
#define D18F2x78_dct0_Reserved_16_16_OFFSET                     16
#define D18F2x78_dct0_Reserved_16_16_WIDTH                      1
#define D18F2x78_dct0_Reserved_16_16_MASK                       0x10000
#define D18F2x78_dct0_AddrCmdTriEn_OFFSET                       17
#define D18F2x78_dct0_AddrCmdTriEn_WIDTH                        1
#define D18F2x78_dct0_AddrCmdTriEn_MASK                         0x20000
#define D18F2x78_dct0_Reserved_19_18_OFFSET                     18
#define D18F2x78_dct0_Reserved_19_18_WIDTH                      2
#define D18F2x78_dct0_Reserved_19_18_MASK                       0xc0000
#define D18F2x78_dct0_Reserved_27_20_OFFSET                     20
#define D18F2x78_dct0_Reserved_27_20_WIDTH                      8
#define D18F2x78_dct0_Reserved_27_20_MASK                       0xff00000
#define D18F2x78_dct0_Reserved_29_28_OFFSET                     28
#define D18F2x78_dct0_Reserved_29_28_WIDTH                      2
#define D18F2x78_dct0_Reserved_29_28_MASK                       0x30000000
#define D18F2x78_dct0_DramSprLock_OFFSET                        30
#define D18F2x78_dct0_DramSprLock_WIDTH                         1
#define D18F2x78_dct0_DramSprLock_MASK                          0x40000000
#define D18F2x78_dct0_Reserved_31_31_OFFSET                     31
#define D18F2x78_dct0_Reserved_31_31_WIDTH                      1
#define D18F2x78_dct0_Reserved_31_31_MASK                       0x80000000

/// D18F2x78_dct0
typedef union {
  struct {                                                              ///<
    UINT32                                                  ChanVal:1 ; ///<
    UINT32                                             Reserved_1_1:1 ; ///<
    UINT32                                                 GsyncDis:1 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                               PtrInitReq:1 ; ///<
    UINT32                                             Reserved_7_5:3 ; ///<
    UINT32                                                 DramType:3 ; ///<
    UINT32                                           Reserved_14_11:4 ; ///<
    UINT32                                           Reserved_15_15:1 ; ///<
    UINT32                                           Reserved_16_16:1 ; ///<
    UINT32                                             AddrCmdTriEn:1 ; ///<
    UINT32                                           Reserved_19_18:2 ; ///<
    UINT32                                           Reserved_27_20:8 ; ///<
    UINT32                                           Reserved_29_28:2 ; ///<
    UINT32                                              DramSprLock:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F2x78_dct0_STRUCT;

// **** D18F2x78_dct1 Register Definition ****
// Address
#define D18F2x78_dct1_ADDRESS                                   0x78
// Type
#define D18F2x78_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x80_dct0 Register Definition ****
// Address
#define D18F2x80_dct0_ADDRESS                                   0x80
// Type
#define D18F2x80_dct0_TYPE                                      TYPE_D18F2_dct0

// **** D18F2x80_dct1 Register Definition ****
// Address
#define D18F2x80_dct1_ADDRESS                                   0x80
// Type
#define D18F2x80_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x90_dct0 Register Definition ****
// Address
#define D18F2x90_dct0_ADDRESS                                   0x90

// Type
#define D18F2x90_dct0_TYPE                                      TYPE_D18F2_dct0
// Field Data
#define D18F2x90_dct0_ExitSelfRef_OFFSET                        1
#define D18F2x90_dct0_ExitSelfRef_WIDTH                         1
#define D18F2x90_dct0_ExitSelfRef_MASK                          0x2
#define D18F2x90_dct0_DataScrambleEn_OFFSET                     7
#define D18F2x90_dct0_DataScrambleEn_WIDTH                      1
#define D18F2x90_dct0_DataScrambleEn_MASK                       0x80
#define D18F2x90_dct0_ParEn_OFFSET                              8
#define D18F2x90_dct0_ParEn_WIDTH                               1
#define D18F2x90_dct0_ParEn_MASK                                0x100
#define D18F2x90_dct0_WrCrcEn_OFFSET                            9
#define D18F2x90_dct0_WrCrcEn_WIDTH                             1
#define D18F2x90_dct0_WrCrcEn_MASK                              0x200
#define D18F2x90_dct0_CrcUnCorEn_OFFSET                         10
#define D18F2x90_dct0_CrcUnCorEn_WIDTH                          1
#define D18F2x90_dct0_CrcUnCorEn_MASK                           0x400
#define D18F2x90_dct0_X4Dimm_OFFSET                             12
#define D18F2x90_dct0_X4Dimm_WIDTH                              4
#define D18F2x90_dct0_X4Dimm_MASK                               0xf000
#define D18F2x90_dct0_UnbuffDimm_OFFSET                         16
#define D18F2x90_dct0_UnbuffDimm_WIDTH                          1
#define D18F2x90_dct0_UnbuffDimm_MASK                           0x10000
#define D18F2x90_dct0_UnbuffDimm_VALUE                          0x1
#define D18F2x90_dct0_EnterSelfRef_OFFSET                       17
#define D18F2x90_dct0_EnterSelfRef_WIDTH                        1
#define D18F2x90_dct0_EnterSelfRef_MASK                         0x20000
#define D18F2x90_dct0_PendRefPayback_OFFSET                     18
#define D18F2x90_dct0_PendRefPayback_WIDTH                      1
#define D18F2x90_dct0_PendRefPayback_MASK                       0x40000
#define D18F2x90_dct0_PendRefPayback_VALUE                      0x0
#define D18F2x90_dct0_DimmEccEn_OFFSET                          19
#define D18F2x90_dct0_DimmEccEn_WIDTH                           1
#define D18F2x90_dct0_DimmEccEn_MASK                            0x80000
#define D18F2x90_dct0_DynPageCloseEn_OFFSET                     20
#define D18F2x90_dct0_DynPageCloseEn_WIDTH                      1
#define D18F2x90_dct0_DynPageCloseEn_MASK                       0x100000
#define D18F2x90_dct0_IdleCycLowLimit_OFFSET                    21
#define D18F2x90_dct0_IdleCycLowLimit_WIDTH                     2
#define D18F2x90_dct0_IdleCycLowLimit_MASK                      0x600000
#define D18F2x90_dct0_ForceAutoPchg_OFFSET                      23
#define D18F2x90_dct0_ForceAutoPchg_WIDTH                       1
#define D18F2x90_dct0_ForceAutoPchg_MASK                        0x800000
#define D18F2x90_dct0_StagRefEn_OFFSET                          24
#define D18F2x90_dct0_StagRefEn_WIDTH                           1
#define D18F2x90_dct0_StagRefEn_MASK                            0x1000000
#define D18F2x90_dct0_StagRefEn_VALUE                           0x1
#define D18F2x90_dct0_PendRefPaybackS3En_OFFSET                 25
#define D18F2x90_dct0_PendRefPaybackS3En_WIDTH                  1
#define D18F2x90_dct0_PendRefPaybackS3En_MASK                   0x2000000
#define D18F2x90_dct0_PendRefPaybackS3En_VALUE                  0x1
#define D18F2x90_dct0_DisDllShutdownSR_OFFSET                   27
#define D18F2x90_dct0_DisDllShutdownSR_WIDTH                    1
#define D18F2x90_dct0_DisDllShutdownSR_MASK                     0x8000000
#define D18F2x90_dct0_IdleCycLimit_OFFSET                       28
#define D18F2x90_dct0_IdleCycLimit_WIDTH                        4
#define D18F2x90_dct0_IdleCycLimit_MASK                         0xf0000000
#define D18F2x90_dct0_IdleCycLimit_VALUE                        0x8

/// D18F2x90_dct0
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                              ExitSelfRef:1 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                             Reserved_3_3:1 ; ///<
    UINT32                                             Reserved_4_4:1 ; ///<
    UINT32                                             Reserved_5_5:1 ; ///<
    UINT32                                             Reserved_6_6:1 ; ///<
    UINT32                                           DataScrambleEn:1 ; ///<
    UINT32                                                    ParEn:1 ; ///<
    UINT32                                                  WrCrcEn:1 ; ///<
    UINT32                                               CrcUnCorEn:1 ; ///<
    UINT32                                           Reserved_11_11:1 ; ///<
    UINT32                                                   X4Dimm:4 ; ///<
    UINT32                                               UnbuffDimm:1 ; ///<
    UINT32                                             EnterSelfRef:1 ; ///<
    UINT32                                           PendRefPayback:1 ; ///<
    UINT32                                                DimmEccEn:1 ; ///<
    UINT32                                           DynPageCloseEn:1 ; ///<
    UINT32                                          IdleCycLowLimit:2 ; ///<
    UINT32                                            ForceAutoPchg:1 ; ///<
    UINT32                                                StagRefEn:1 ; ///<
    UINT32                                       PendRefPaybackS3En:1 ; ///<
    UINT32                                           Reserved_26_26:1 ; ///<
    UINT32                                         DisDllShutdownSR:1 ; ///<
    UINT32                                             IdleCycLimit:4 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F2x90_dct0_STRUCT;

// **** D18F2x90_dct1 Register Definition ****
// Address
#define D18F2x90_dct1_ADDRESS                                   0x90

// Type
#define D18F2x90_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x94_dct0 Register Definition ****
// Address
#define D18F2x94_dct0_ADDRESS                                   0x94
// Type
#define D18F2x94_dct0_TYPE                                      TYPE_D18F2_dct0
// Field Data
#define D18F2x94_dct0_MemClkFreq_OFFSET                         0
#define D18F2x94_dct0_MemClkFreq_WIDTH                          5
#define D18F2x94_dct0_MemClkFreq_MASK                           0x1f
#define D18F2x94_dct0_MemClkFreqVal_OFFSET                      7
#define D18F2x94_dct0_MemClkFreqVal_WIDTH                       1
#define D18F2x94_dct0_MemClkFreqVal_MASK                        0x80
#define D18F2x94_dct0_ZqcsInterval_OFFSET                       10
#define D18F2x94_dct0_ZqcsInterval_WIDTH                        3
#define D18F2x94_dct0_ZqcsInterval_MASK                         0x1c00
#define D18F2x94_dct0_DisDramInterface_OFFSET                   14
#define D18F2x94_dct0_DisDramInterface_WIDTH                    1
#define D18F2x94_dct0_DisDramInterface_MASK                     0x4000
#define D18F2x94_dct0_PowerDownEn_OFFSET                        15
#define D18F2x94_dct0_PowerDownEn_WIDTH                         1
#define D18F2x94_dct0_PowerDownEn_MASK                          0x8000
#define D18F2x94_dct0_PowerDownEn_VALUE                         0x1
#define D18F2x94_dct0_PowerDownMode_OFFSET                      16
#define D18F2x94_dct0_PowerDownMode_WIDTH                       1
#define D18F2x94_dct0_PowerDownMode_MASK                        0x10000
#define D18F2x94_dct0_PowerDownMode_VALUE                       0x1
#define D18F2x94_dct0_SlowAccessMode_OFFSET                     20
#define D18F2x94_dct0_SlowAccessMode_WIDTH                      1
#define D18F2x94_dct0_SlowAccessMode_MASK                       0x100000
#define D18F2x94_dct0_BankSwizzleMode_OFFSET                    22
#define D18F2x94_dct0_BankSwizzleMode_WIDTH                     1
#define D18F2x94_dct0_BankSwizzleMode_MASK                      0x400000
#define D18F2x94_dct0_On3RdCasStallMode_OFFSET                  23
#define D18F2x94_dct0_On3RdCasStallMode_WIDTH                   1
#define D18F2x94_dct0_On3RdCasStallMode_MASK                    0x800000
#define D18F2x94_dct0_DcqBypassMax_OFFSET                       24
#define D18F2x94_dct0_DcqBypassMax_WIDTH                        5
#define D18F2x94_dct0_DcqBypassMax_MASK                         0x1f000000
#define D18F2x94_dct0_BankGroupSwap_OFFSET                      29
#define D18F2x94_dct0_BankGroupSwap_WIDTH                       1
#define D18F2x94_dct0_BankGroupSwap_MASK                        0x20000000
#define D18F2x94_dct0_DcqSafeByp_OFFSET                         30
#define D18F2x94_dct0_DcqSafeByp_WIDTH                          1
#define D18F2x94_dct0_DcqSafeByp_MASK                           0x40000000
#define D18F2x94_dct0_DphyMemPsSelEn_OFFSET                     31
#define D18F2x94_dct0_DphyMemPsSelEn_WIDTH                      1
#define D18F2x94_dct0_DphyMemPsSelEn_MASK                       0x80000000
#define D18F2x94_dct0_DphyMemPsSelEn_VALUE                      0x0

/// D18F2x94_dct0
typedef union {
  struct {                                                              ///<
    UINT32                                               MemClkFreq:5 ; ///<
    UINT32                                             Reserved_6_5:2 ; ///<
    UINT32                                            MemClkFreqVal:1 ; ///<
    UINT32                                             Reserved_9_8:2 ; ///<
    UINT32                                             ZqcsInterval:3 ; ///<
    UINT32                                           Reserved_13_13:1 ; ///<
    UINT32                                         DisDramInterface:1 ; ///<
    UINT32                                              PowerDownEn:1 ; ///<
    UINT32                                            PowerDownMode:1 ; ///<
    UINT32                                           Reserved_17_17:1 ; ///<
    UINT32                                           Reserved_18_18:1 ; ///<
    UINT32                                           Reserved_19_19:1 ; ///<
    UINT32                                           SlowAccessMode:1 ; ///<
    UINT32                                           Reserved_21_21:1 ; ///<
    UINT32                                          BankSwizzleMode:1 ; ///<
    UINT32                                        On3RdCasStallMode:1 ; ///<
    UINT32                                             DcqBypassMax:5 ; ///<
    UINT32                                            BankGroupSwap:1 ; ///<
    UINT32                                               DcqSafeByp:1 ; ///<
    UINT32                                           DphyMemPsSelEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F2x94_dct0_STRUCT;

// **** D18F2x94_dct1 Register Definition ****
// Address
#define D18F2x94_dct1_ADDRESS                                   0x94
// Type
#define D18F2x94_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2xA8_dct0 Register Definition ****
// Address
#define D18F2xA8_dct0_ADDRESS                                   0xA8
// Type
#define D18F2xA8_dct0_TYPE                                      TYPE_D18F2_dct0
// Field Data
#define D18F2xA8_dct0_EffArbDis_OFFSET                          0
#define D18F2xA8_dct0_EffArbDis_WIDTH                           1
#define D18F2xA8_dct0_EffArbDis_MASK                            0x1
#define D18F2xA8_dct0_EffArbDis_VALUE                           0x0
#define D18F2xA8_dct0_GmcUrgPriMode_OFFSET                      1
#define D18F2xA8_dct0_GmcUrgPriMode_WIDTH                       1
#define D18F2xA8_dct0_GmcUrgPriMode_MASK                        0x2
#define D18F2xA8_dct0_LrDimmEnhRefEn_OFFSET                     3
#define D18F2xA8_dct0_LrDimmEnhRefEn_WIDTH                      1
#define D18F2xA8_dct0_LrDimmEnhRefEn_MASK                       0x8
#define D18F2xA8_dct0_ExtendedParityEn_OFFSET                   4
#define D18F2xA8_dct0_ExtendedParityEn_WIDTH                    1
#define D18F2xA8_dct0_ExtendedParityEn_MASK                     0x10
#define D18F2xA8_dct0_ExtendedParityEn_VALUE                    0x0
#define D18F2xA8_dct0_SubMemclkRegDly_OFFSET                    5
#define D18F2xA8_dct0_SubMemclkRegDly_WIDTH                     1
#define D18F2xA8_dct0_SubMemclkRegDly_MASK                      0x20
#define D18F2xA8_dct0_LrDimmErrOutMonEn_OFFSET                  6
#define D18F2xA8_dct0_LrDimmErrOutMonEn_WIDTH                   1
#define D18F2xA8_dct0_LrDimmErrOutMonEn_MASK                    0x40
#define D18F2xA8_dct0_LrDimmMrsCtrl_OFFSET                      7
#define D18F2xA8_dct0_LrDimmMrsCtrl_WIDTH                       1
#define D18F2xA8_dct0_LrDimmMrsCtrl_MASK                        0x80
#define D18F2xA8_dct0_MrsCtrlWordCS_7_0__OFFSET                 8
#define D18F2xA8_dct0_MrsCtrlWordCS_7_0__WIDTH                  8
#define D18F2xA8_dct0_MrsCtrlWordCS_7_0__MASK                   0xff00
#define D18F2xA8_dct0_DisParallelMemPhySrExit_OFFSET            18
#define D18F2xA8_dct0_DisParallelMemPhySrExit_WIDTH             1
#define D18F2xA8_dct0_DisParallelMemPhySrExit_MASK              0x40000
#define D18F2xA8_dct0_PDPhyPSDis_OFFSET                         19
#define D18F2xA8_dct0_PDPhyPSDis_WIDTH                          1
#define D18F2xA8_dct0_PDPhyPSDis_MASK                           0x80000
#define D18F2xA8_dct0_PDPhyPSDis_VALUE                          0x0
#define D18F2xA8_dct0_BankSwap_OFFSET                           20
#define D18F2xA8_dct0_BankSwap_WIDTH                            1
#define D18F2xA8_dct0_BankSwap_MASK                             0x100000
#define D18F2xA8_dct0_AggrPDEn_OFFSET                           21
#define D18F2xA8_dct0_AggrPDEn_WIDTH                            1
#define D18F2xA8_dct0_AggrPDEn_MASK                             0x200000
#define D18F2xA8_dct0_AggrPDEn_VALUE                            0x1
#define D18F2xA8_dct0_PrtlChPDEnhEn_OFFSET                      22
#define D18F2xA8_dct0_PrtlChPDEnhEn_WIDTH                       1
#define D18F2xA8_dct0_PrtlChPDEnhEn_MASK                        0x400000
#define D18F2xA8_dct0_PrtlChPDEnhEn_VALUE                       0x0
#define D18F2xA8_dct0_OppWrEnhDis_OFFSET                        23
#define D18F2xA8_dct0_OppWrEnhDis_WIDTH                         1
#define D18F2xA8_dct0_OppWrEnhDis_MASK                          0x800000
#define D18F2xA8_dct0_DisReqEob_OFFSET                          24
#define D18F2xA8_dct0_DisReqEob_WIDTH                           1
#define D18F2xA8_dct0_DisReqEob_MASK                            0x1000000
#define D18F2xA8_dct0_CsMux45_OFFSET                            26
#define D18F2xA8_dct0_CsMux45_WIDTH                             1
#define D18F2xA8_dct0_CsMux45_MASK                              0x4000000
#define D18F2xA8_dct0_CsMux67_OFFSET                            27
#define D18F2xA8_dct0_CsMux67_WIDTH                             1
#define D18F2xA8_dct0_CsMux67_MASK                              0x8000000
#define D18F2xA8_dct0_FastSelfRefEntryDis_OFFSET                28
#define D18F2xA8_dct0_FastSelfRefEntryDis_WIDTH                 1
#define D18F2xA8_dct0_FastSelfRefEntryDis_MASK                  0x10000000
#define D18F2xA8_dct0_RefChCmdMgtDis_OFFSET                     29
#define D18F2xA8_dct0_RefChCmdMgtDis_WIDTH                      1
#define D18F2xA8_dct0_RefChCmdMgtDis_MASK                       0x20000000
#define D18F2xA8_dct0_PerRankTimingEn_OFFSET                    31
#define D18F2xA8_dct0_PerRankTimingEn_WIDTH                     1
#define D18F2xA8_dct0_PerRankTimingEn_MASK                      0x80000000
#define D18F2xA8_dct0_PerRankTimingEn_VALUE                     0x1

/// D18F2xA8_dct0
typedef union {
  struct {                                                              ///<
    UINT32                                                EffArbDis:1 ; ///<
    UINT32                                            GmcUrgPriMode:1 ; ///<
    UINT32                                             Reserved_2_2:1 ; ///<
    UINT32                                           LrDimmEnhRefEn:1 ; ///<
    UINT32                                         ExtendedParityEn:1 ; ///<
    UINT32                                          SubMemclkRegDly:1 ; ///<
    UINT32                                        LrDimmErrOutMonEn:1 ; ///<
    UINT32                                            LrDimmMrsCtrl:1 ; ///<
    UINT32                                       MrsCtrlWordCS_7_0_:8 ; ///<
    UINT32                                           Reserved_17_16:2 ; ///<
    UINT32                                  DisParallelMemPhySrExit:1 ; ///<
    UINT32                                               PDPhyPSDis:1 ; ///<
    UINT32                                                 BankSwap:1 ; ///<
    UINT32                                                 AggrPDEn:1 ; ///<
    UINT32                                            PrtlChPDEnhEn:1 ; ///<
    UINT32                                              OppWrEnhDis:1 ; ///<
    UINT32                                                DisReqEob:1 ; ///<
    UINT32                                           Reserved_25_25:1 ; ///<
    UINT32                                                  CsMux45:1 ; ///<
    UINT32                                                  CsMux67:1 ; ///<
    UINT32                                      FastSelfRefEntryDis:1 ; ///<
    UINT32                                           RefChCmdMgtDis:1 ; ///<
    UINT32                                           Reserved_30_30:1 ; ///<
    UINT32                                          PerRankTimingEn:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F2xA8_dct0_STRUCT;

// **** D18F2xA8_dct1 Register Definition ****
// Address
#define D18F2xA8_dct1_ADDRESS                                   0xA8
// Type
#define D18F2xA8_dct1_TYPE                                      TYPE_D18F2_dct1

// **** D18F2x110 Register Definition ****
// Address
#define D18F2x110_ADDRESS                                       0x110

// Type
#define D18F2x110_TYPE                                          TYPE_D18F2

// **** D18F2x114 Register Definition ****
// Address
#define D18F2x114_ADDRESS                                       0x114
// Type
#define D18F2x114_TYPE                                          TYPE_D18F2

// **** D18F2x2E0_dct0 Register Definition ****
// Address
#define D18F2x2E0_dct0_ADDRESS                                  0x2e0

// Type
#define D18F2x2E0_dct0_TYPE                                     TYPE_D18F2_dct0
// Field Data
#define D18F2x2E0_dct0_CurMemPstate_OFFSET                      0
#define D18F2x2E0_dct0_CurMemPstate_WIDTH                       1
#define D18F2x2E0_dct0_CurMemPstate_MASK                        0x1
#define D18F2x2E0_dct0_Reserved_3_1_OFFSET                      1
#define D18F2x2E0_dct0_Reserved_3_1_WIDTH                       3
#define D18F2x2E0_dct0_Reserved_3_1_MASK                        0xe
#define D18F2x2E0_dct0_VrefTrain3Mrs6_OFFSET                    4
#define D18F2x2E0_dct0_VrefTrain3Mrs6_WIDTH                     1
#define D18F2x2E0_dct0_VrefTrain3Mrs6_MASK                      0x10
#define D18F2x2E0_dct0_VrefTrainMrsEn_OFFSET                    5
#define D18F2x2E0_dct0_VrefTrainMrsEn_WIDTH                     1
#define D18F2x2E0_dct0_VrefTrainMrsEn_MASK                      0x20
#define D18F2x2E0_dct0_Reserved_15_6_OFFSET                     6
#define D18F2x2E0_dct0_Reserved_15_6_WIDTH                      10
#define D18F2x2E0_dct0_Reserved_15_6_MASK                       0xffc0
#define D18F2x2E0_dct0_MxMrsEn_OFFSET                           16
#define D18F2x2E0_dct0_MxMrsEn_WIDTH                            8
#define D18F2x2E0_dct0_MxMrsEn_MASK                             0xff0000
#define D18F2x2E0_dct0_M1MemClkFreq_OFFSET                      24
#define D18F2x2E0_dct0_M1MemClkFreq_WIDTH                       5
#define D18F2x2E0_dct0_M1MemClkFreq_MASK                        0x1f000000
#define D18F2x2E0_dct0_Reserved_29_29_OFFSET                    29
#define D18F2x2E0_dct0_Reserved_29_29_WIDTH                     1
#define D18F2x2E0_dct0_Reserved_29_29_MASK                      0x20000000
#define D18F2x2E0_dct0_FastMstateDis_OFFSET                     30
#define D18F2x2E0_dct0_FastMstateDis_WIDTH                      1
#define D18F2x2E0_dct0_FastMstateDis_MASK                       0x40000000
#define D18F2x2E0_dct0_Reserved_31_31_OFFSET                    31
#define D18F2x2E0_dct0_Reserved_31_31_WIDTH                     1
#define D18F2x2E0_dct0_Reserved_31_31_MASK                      0x80000000

/// D18F2x2E0_dct0
typedef union {
  struct {                                                              ///<
    UINT32                                             CurMemPstate:1 ; ///<
    UINT32                                             Reserved_3_1:3 ; ///<
    UINT32                                           VrefTrain3Mrs6:1 ; ///<
    UINT32                                           VrefTrainMrsEn:1 ; ///<
    UINT32                                            Reserved_15_6:10; ///<
    UINT32                                                  MxMrsEn:8 ; ///<
    UINT32                                             M1MemClkFreq:5 ; ///<
    UINT32                                           Reserved_29_29:1 ; ///<
    UINT32                                            FastMstateDis:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F2x2E0_dct0_STRUCT;

// **** D18F2x2E0_dct1 Register Definition ****
// Address
#define D18F2x2E0_dct1_ADDRESS                                  0x2e0

// Type
#define D18F2x2E0_dct1_TYPE                                     TYPE_D18F2_dct1

// Field Data
#define D18F2x2E0_dct1_CurMemPstate_OFFSET                      0
#define D18F2x2E0_dct1_CurMemPstate_WIDTH                       1
#define D18F2x2E0_dct1_CurMemPstate_MASK                        0x1
#define D18F2x2E0_dct1_Reserved_3_1_OFFSET                      1
#define D18F2x2E0_dct1_Reserved_3_1_WIDTH                       3
#define D18F2x2E0_dct1_Reserved_3_1_MASK                        0xe
#define D18F2x2E0_dct1_VrefTrain3Mrs6_OFFSET                    4
#define D18F2x2E0_dct1_VrefTrain3Mrs6_WIDTH                     1
#define D18F2x2E0_dct1_VrefTrain3Mrs6_MASK                      0x10
#define D18F2x2E0_dct1_VrefTrainMrsEn_OFFSET                    5
#define D18F2x2E0_dct1_VrefTrainMrsEn_WIDTH                     1
#define D18F2x2E0_dct1_VrefTrainMrsEn_MASK                      0x20
#define D18F2x2E0_dct1_Reserved_15_6_OFFSET                     6
#define D18F2x2E0_dct1_Reserved_15_6_WIDTH                      10
#define D18F2x2E0_dct1_Reserved_15_6_MASK                       0xffc0
#define D18F2x2E0_dct1_MxMrsEn_OFFSET                           16
#define D18F2x2E0_dct1_MxMrsEn_WIDTH                            8
#define D18F2x2E0_dct1_MxMrsEn_MASK                             0xff0000
#define D18F2x2E0_dct1_M1MemClkFreq_OFFSET                      24
#define D18F2x2E0_dct1_M1MemClkFreq_WIDTH                       5
#define D18F2x2E0_dct1_M1MemClkFreq_MASK                        0x1f000000
#define D18F2x2E0_dct1_Reserved_29_29_OFFSET                    29
#define D18F2x2E0_dct1_Reserved_29_29_WIDTH                     1
#define D18F2x2E0_dct1_Reserved_29_29_MASK                      0x20000000
#define D18F2x2E0_dct1_FastMstateDis_OFFSET                     30
#define D18F2x2E0_dct1_FastMstateDis_WIDTH                      1
#define D18F2x2E0_dct1_FastMstateDis_MASK                       0x40000000
#define D18F2x2E0_dct1_Reserved_31_31_OFFSET                    31
#define D18F2x2E0_dct1_Reserved_31_31_WIDTH                     1
#define D18F2x2E0_dct1_Reserved_31_31_MASK                      0x80000000

/// D18F2x2E0_dct1
typedef union {
  struct {                                                              ///<
    UINT32                                             CurMemPstate:1 ; ///<
    UINT32                                             Reserved_3_1:3 ; ///<
    UINT32                                           VrefTrain3Mrs6:1 ; ///<
    UINT32                                           VrefTrainMrsEn:1 ; ///<
    UINT32                                            Reserved_15_6:10; ///<
    UINT32                                                  MxMrsEn:8 ; ///<
    UINT32                                             M1MemClkFreq:5 ; ///<
    UINT32                                           Reserved_29_29:1 ; ///<
    UINT32                                            FastMstateDis:1 ; ///<
    UINT32                                           Reserved_31_31:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D18F2x2E0_dct1_STRUCT;

// **** GMMx15C0 Register Definition ****
// Address
#define GMMx15C0_ADDRESS                                        0x15C0
// Type
#define GMMx15C0_TYPE                                           TYPE_GMM

// **** GMMx1740 Register Definition ****
// Address
#define GMMx1740_ADDRESS                                        0x1740

// Type
#define GMMx1740_TYPE                                           TYPE_GMM
// Field Data
#define GMMx1740_BIOS_SCRATCH_7_OFFSET                          0
#define GMMx1740_BIOS_SCRATCH_7_WIDTH                           32
#define GMMx1740_BIOS_SCRATCH_7_MASK                            0xffffffff
// VBIOS post check bit
#define ATOM_S7_ASIC_INIT_COMPLETEb1                            0x200

/// GMMx1740
typedef union {
  struct {                                                              ///<
    UINT32                                           BIOS_SCRATCH_7:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx1740_STRUCT;

// **** GMMx2014 Register Definition ****
// Address
#define GMMx2014_ADDRESS                                        0x2014
// Type
#define GMMx2014_TYPE                                           TYPE_GMM

// **** GMMx2018 Register Definition ****
// Address
#define GMMx2018_ADDRESS                                        0x2018
// Type
#define GMMx2018_TYPE                                           TYPE_GMM

// **** GMMx201C Register Definition ****
// Address
#define GMMx201C_ADDRESS                                        0x201c
// Type
#define GMMx201C_TYPE                                           TYPE_GMM

// **** GMMx2020 Register Definition ****
// Address
#define GMMx2020_ADDRESS                                        0x2020
// Type
#define GMMx2020_TYPE                                           TYPE_GMM

// **** GMMx2024 Register Definition ****
// Address
#define GMMx2024_ADDRESS                                        0x2024
// Type
#define GMMx2024_TYPE                                           TYPE_GMM

// Field Data
#define GMMx2024_FB_BASE_OFFSET                                 0
#define GMMx2024_FB_BASE_WIDTH                                  16
#define GMMx2024_FB_BASE_MASK                                   0xFFFF
#define GMMx2024_FB_TOP_OFFSET                                  16
#define GMMx2024_FB_TOP_WIDTH                                   16
#define GMMx2024_FB_TOP_MASK                                    0xFFFF0000

/// GMMx2024
typedef union {
  struct {                                                            ///<
    UINT32                                                 FB_BASE:16; ///<
    UINT32                                                  FB_TOP:16; ///<

  } Field;

  UINT32 Value;
} GMMx2024_STRUCT;

// **** GMMx2068 Register Definition ****
// Address
#define GMMx2068_ADDRESS                                        0x2068
// Type
#define GMMx2068_TYPE                                           TYPE_GMM

// Field Data
#define GMMx2068_FB_OFFSET_OFFSET                               0
#define GMMx2068_FB_OFFSET_WIDTH                                18
#define GMMx2068_FB_OFFSET_MASK                                 0x3FFFF
#define GMMx2068_Reserved_31_18_OFFSET                          18
#define GMMx2068_Reserved_31_18_WIDTH                           14
#define GMMx2068_Reserved_31_18_MASK                            0xFFFC0000

/// GMMx2068
typedef union {
  struct {                                                            ///<
    UINT32                                               FB_OFFSET:18; ///<
    UINT32                                          Reserved_31_18:14; ///<

  } Field;

  UINT32 Value;
} GMMx2068_STRUCT;

// **** GMMx206C Register Definition ****
// Address
#define GMMx206C_ADDRESS                                        0x206c

// Type
#define GMMx206C_TYPE                                           TYPE_GMM
// Field Data
#define GMMx206C_DEFAULT_STEERING_OFFSET                        0
#define GMMx206C_DEFAULT_STEERING_WIDTH                         2
#define GMMx206C_DEFAULT_STEERING_MASK                          0x3
#define GMMx206C_Reserved_OFFSET                                2
#define GMMx206C_Reserved_WIDTH                                 30
#define GMMx206C_Reserved_MASK                                  0xfffffffc

/// GMMx206C
typedef union {
  struct {                                                              ///<
    UINT32                                         DEFAULT_STEERING:2 ; ///<
    UINT32                                                 Reserved:30; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx206C_STRUCT;

// **** GMMx20AC Register Definition ****
// Address
#define GMMx20AC_ADDRESS                                        0x20ac
// Type
#define GMMx20AC_TYPE                                           TYPE_GMM

// **** GMMx20B8 Register Definition ****
// Address
#define GMMx20B8_ADDRESS                                        0x20B8
// Type
#define GMMx20B8_TYPE                                           TYPE_GMM

// **** GMMx20BC Register Definition ****
// Address
#define GMMx20BC_ADDRESS                                        0x20BC
// Type
#define GMMx20BC_TYPE                                           TYPE_GMM

// **** GMMx20C0 Register Definition ****
// Address
#define GMMx20C0_ADDRESS                                        0x20C0
// Type
#define GMMx20C0_TYPE                                           TYPE_GMM

// **** GMMx20EC Register Definition ****
// Address
#define GMMx20EC_ADDRESS                                        0x20ec
// Type
#define GMMx20EC_TYPE                                           TYPE_GMM

// **** GMMx2108 Register Definition ****
// Address
#define GMMx2108_ADDRESS                                        0x2108
// Type
#define GMMx2108_TYPE                                           TYPE_GMM

// **** GMMx2120 Register Definition ****
// Address
#define GMMx2120_ADDRESS                                        0x2120
// Type
#define GMMx2120_TYPE                                           TYPE_GMM

// **** GMMx2178 Register Definition ****
// Address
#define GMMx2178_ADDRESS                                        0x2178
// Type
#define GMMx2178_TYPE                                           TYPE_GMM

// **** GMMx2180 Register Definition ****
// Address
#define GMMx2180_ADDRESS                                        0x2180
// Type
#define GMMx2180_TYPE                                           TYPE_GMM

// **** GMMx2188 Register Definition ****
// Address
#define GMMx2188_ADDRESS                                        0x2188
// Type
#define GMMx2188_TYPE                                           TYPE_GMM

// **** GMMx2194 Register Definition ****
// Address
#define GMMx2194_ADDRESS                                        0x2194
// Type
#define GMMx2194_TYPE                                           TYPE_GMM

// **** GMMx21B8 Register Definition ****
// Address
#define GMMx21B8_ADDRESS                                        0x21b8
// Type
#define GMMx21B8_TYPE                                           TYPE_GMM

// **** GMMx21D8 Register Definition ****
// Address
#define GMMx21D8_ADDRESS                                        0x21d8
// Type
#define GMMx21D8_TYPE                                           TYPE_GMM

// **** GMMx21F4 Register Definition ****
// Address
#define GMMx21F4_ADDRESS                                        0x21f4
// Type
#define GMMx21F4_TYPE                                           TYPE_GMM

// **** GMMx2204 Register Definition ****
// Address
#define GMMx2204_ADDRESS                                        0x2204
// Type
#define GMMx2204_TYPE                                           TYPE_GMM

// **** GMMx2214 Register Definition ****
// Address
#define GMMx2214_ADDRESS                                        0x2214
// Type
#define GMMx2214_TYPE                                           TYPE_GMM

// **** GMMx2208 Register Definition ****
// Address
#define GMMx2208_ADDRESS                                        0x2208
// Type
#define GMMx2208_TYPE                                           TYPE_GMM

// **** GMMx2218 Register Definition ****
// Address
#define GMMx2218_ADDRESS                                        0x2218
// Type
#define GMMx2218_TYPE                                           TYPE_GMM

// **** GMMx221C Register Definition ****
// Address
#define GMMx221C_ADDRESS                                        0x221C
// Type
#define GMMx221C_TYPE                                           TYPE_GMM

// **** GMMx2220 Register Definition ****
// Address
#define GMMx2220_ADDRESS                                        0x2220
// Type
#define GMMx2220_TYPE                                           TYPE_GMM

// **** GMMx2244 Register Definition ****
// Address
#define GMMx2244_ADDRESS                                        0x2244
// Type
#define GMMx2244_TYPE                                           TYPE_GMM

// **** GMMx2248 Register Definition ****
// Address
#define GMMx2248_ADDRESS                                        0x2248
// Type
#define GMMx2248_TYPE                                           TYPE_GMM

// **** GMMx224C Register Definition ****
// Address
#define GMMx224C_ADDRESS                                        0x224C
// Type
#define GMMx224C_TYPE                                           TYPE_GMM

// **** GMMx2294 Register Definition ****
// Address
#define GMMx2294_ADDRESS                                        0x2294
// Type
#define GMMx2294_TYPE                                           TYPE_GMM

// **** GMMx2478 Register Definition ****
// Address
#define GMMx2478_ADDRESS                                        0x2478
// Type
#define GMMx2478_TYPE                                           TYPE_GMM

// **** GMMx25C8 Register Definition ****
// Address
#define GMMx25C8_ADDRESS                                        0x25c8
// Type
#define GMMx25C8_TYPE                                           TYPE_GMM

// **** GMMx25CC Register Definition ****
// Address
#define GMMx25CC_ADDRESS                                        0x25CC
// Type
#define GMMx25CC_TYPE                                           TYPE_GMM

// **** GMMx25E0 Register Definition ****
// Address
#define GMMx25E0_ADDRESS                                        0x25e0
// Type
#define GMMx25E0_TYPE                                           TYPE_GMM

// **** GMMx25E4 Register Definition ****
// Address
#define GMMx25E4_ADDRESS                                        0x25e4
// Type
#define GMMx25E4_TYPE                                           TYPE_GMM

// **** GMMx25E8 Register Definition ****
// Address
#define GMMx25E8_ADDRESS                                        0x25e8
// Type
#define GMMx25E8_TYPE                                           TYPE_GMM

// **** GMMx2624 Register Definition ****
// Address
#define GMMx2624_ADDRESS                                        0x2624
// Type
#define GMMx2624_TYPE                                           TYPE_GMM

// **** GMMx2628 Register Definition ****
// Address
#define GMMx2628_ADDRESS                                        0x2628
// Type
#define GMMx2628_TYPE                                           TYPE_GMM

// **** GMMx262C Register Definition ****
// Address
#define GMMx262C_ADDRESS                                        0x262c
// Type
#define GMMx262C_TYPE                                           TYPE_GMM

// **** GMMx2648 Register Definition ****
// Address
#define GMMx2648_ADDRESS                                        0x2648
// Type
#define GMMx2648_TYPE                                           TYPE_GMM

// **** GMMx264C Register Definition ****
// Address
#define GMMx264C_ADDRESS                                        0x264C
// Type
#define GMMx264C_TYPE                                           TYPE_GMM

// **** GMMx2650 Register Definition ****
// Address
#define GMMx2650_ADDRESS                                        0x2650
// Type
#define GMMx2650_TYPE                                           TYPE_GMM

// **** GMMx2700 Register Definition ****
// Address
#define GMMx2700_ADDRESS                                        0x2700
// Type
#define GMMx2700_TYPE                                           TYPE_GMM

// **** GMMx2738 Register Definition ****
// Address
#define GMMx2738_ADDRESS                                        0x2738
// Type
#define GMMx2738_TYPE                                           TYPE_GMM

// **** GMMx2760 Register Definition ****
// Address
#define GMMx2760_ADDRESS                                        0x2760
// Type
#define GMMx2760_TYPE                                           TYPE_GMM

// **** GMMx2764 Register Definition ****
// Address
#define GMMx2764_ADDRESS                                        0x2764
// Type
#define GMMx2764_TYPE                                           TYPE_GMM

// **** GMMx2768 Register Definition ****
// Address
#define GMMx2768_ADDRESS                                        0x2768
// Type
#define GMMx2768_TYPE                                           TYPE_GMM

// **** GMMx276C Register Definition ****
// Address
#define GMMx276C_ADDRESS                                        0x276C
// Type
#define GMMx276C_TYPE                                           TYPE_GMM

// **** GMMx2774 Register Definition ****
// Address
#define GMMx2774_ADDRESS                                        0x2774
// Type
#define GMMx2774_TYPE                                           TYPE_GMM

// **** GMMx2778 Register Definition ****
// Address
#define GMMx2778_ADDRESS                                        0x2778
// Type
#define GMMx2778_TYPE                                           TYPE_GMM

// **** GMMx277C Register Definition ****
// Address
#define GMMx277C_ADDRESS                                        0x277c
// Type
#define GMMx277C_TYPE                                           TYPE_GMM

// **** GMMx2780 Register Definition ****
// Address
#define GMMx2780_ADDRESS                                        0x2780
// Type
#define GMMx2780_TYPE                                           TYPE_GMM

// **** GMMx278C Register Definition ****
// Address
#define GMMx278C_ADDRESS                                        0x278c
// Type
#define GMMx278C_TYPE                                           TYPE_GMM

// **** GMMx2790 Register Definition ****
// Address
#define GMMx2790_ADDRESS                                        0x2790
// Type
#define GMMx2790_TYPE                                           TYPE_GMM

// **** GMMx2794 Register Definition ****
// Address
#define GMMx2794_ADDRESS                                        0x2794
// Type
#define GMMx2794_TYPE                                           TYPE_GMM

// **** GMMx2798 Register Definition ****
// Address
#define GMMx2798_ADDRESS                                        0x2798
// Type
#define GMMx2798_TYPE                                           TYPE_GMM

// **** GMMx27C0 Register Definition ****
// Address
#define GMMx27C0_ADDRESS                                        0x27c0
// Type
#define GMMx27C0_TYPE                                           TYPE_GMM

// **** GMMx27C4 Register Definition ****
// Address
#define GMMx27C4_ADDRESS                                        0x27c4
// Type
#define GMMx27C4_TYPE                                           TYPE_GMM

// **** GMMx27D0 Register Definition ****
// Address
#define GMMx27D0_ADDRESS                                        0x27d0
// Type
#define GMMx27D0_TYPE                                           TYPE_GMM

// **** GMMx27D4 Register Definition ****
// Address
#define GMMx27D4_ADDRESS                                        0x27d4
// Type
#define GMMx27D4_TYPE                                           TYPE_GMM

// **** GMMx27A4 Register Definition ****
// Address
#define GMMx27A4_ADDRESS                                        0x27a4
// Type
#define GMMx27A4_TYPE                                           TYPE_GMM

// **** GMMx27A8 Register Definition ****
// Address
#define GMMx27A8_ADDRESS                                        0x27a8
// Type
#define GMMx27A8_TYPE                                           TYPE_GMM

// **** GMMx27E4 Register Definition ****
// Address
#define GMMx27E4_ADDRESS                                        0x27e4
// Type
#define GMMx27E4_TYPE                                           TYPE_GMM

// **** GMMx27F0 Register Definition ****
// Address
#define GMMx27F0_ADDRESS                                        0x27f0
// Type
#define GMMx27F0_TYPE                                           TYPE_GMM

// **** GMMx27FC Register Definition ****
// Address
#define GMMx27FC_ADDRESS                                        0x27fc
// Type
#define GMMx27FC_TYPE                                           TYPE_GMM

// **** GMMx2808 Register Definition ****
// Address
#define GMMx2808_ADDRESS                                        0x2808
// Type
#define GMMx2808_TYPE                                           TYPE_GMM

// **** GMMx2814 Register Definition ****
// Address
#define GMMx2814_ADDRESS                                        0x2814
// Type
#define GMMx2814_TYPE                                           TYPE_GMM

// **** GMMx2818 Register Definition ****
// Address
#define GMMx2818_ADDRESS                                        0x2818
// Type
#define GMMx2818_TYPE                                           TYPE_GMM

// **** GMMx281C Register Definition ****
// Address
#define GMMx281C_ADDRESS                                        0x281C
// Type
#define GMMx281C_TYPE                                           TYPE_GMM

// **** GMMx2820 Register Definition ****
// Address
#define GMMx2820_ADDRESS                                        0x2820
// Type
#define GMMx2820_TYPE                                           TYPE_GMM

// **** GMMx2824 Register Definition ****
// Address
#define GMMx2824_ADDRESS                                        0x2824
// Type
#define GMMx2824_TYPE                                           TYPE_GMM

// **** GMMx2828 Register Definition ****
// Address
#define GMMx2828_ADDRESS                                        0x2828
// Type
#define GMMx2828_TYPE                                           TYPE_GMM

// **** GMMx282C Register Definition ****
// Address
#define GMMx282C_ADDRESS                                        0x282C
// Type
#define GMMx282C_TYPE                                           TYPE_GMM

// **** GMMx2830 Register Definition ****
// Address
#define GMMx2830_ADDRESS                                        0x2830
// Type
#define GMMx2830_TYPE                                           TYPE_GMM

// **** GMMx2834 Register Definition ****
// Address
#define GMMx2834_ADDRESS                                        0x2834
// Type
#define GMMx2834_TYPE                                           TYPE_GMM

// **** GMMx2838 Register Definition ****
// Address
#define GMMx2838_ADDRESS                                        0x2838
// Type
#define GMMx2838_TYPE                                           TYPE_GMM

// **** GMMx283C Register Definition ****
// Address
#define GMMx283C_ADDRESS                                        0x283C
// Type
#define GMMx283C_TYPE                                           TYPE_GMM

// **** GMMx2840 Register Definition ****
// Address
#define GMMx2840_ADDRESS                                        0x2840
// Type
#define GMMx2840_TYPE                                           TYPE_GMM

// **** GMMx2844 Register Definition ****
// Address
#define GMMx2844_ADDRESS                                        0x2844
// Type
#define GMMx2844_TYPE                                           TYPE_GMM

// **** GMMx2848 Register Definition ****
// Address
#define GMMx2848_ADDRESS                                        0x2848
// Type
#define GMMx2848_TYPE                                           TYPE_GMM

// **** GMMx284C Register Definition ****
// Address
#define GMMx284C_ADDRESS                                        0x284C
// Type
#define GMMx284C_TYPE                                           TYPE_GMM

// **** GMMx2850 Register Definition ****
// Address
#define GMMx2850_ADDRESS                                        0x2850
// Type
#define GMMx2850_TYPE                                           TYPE_GMM

// **** GMMx2854 Register Definition ****
// Address
#define GMMx2854_ADDRESS                                        0x2854
// Type
#define GMMx2854_TYPE                                           TYPE_GMM

// **** GMMx2858 Register Definition ****
// Address
#define GMMx2858_ADDRESS                                        0x2858
// Type
#define GMMx2858_TYPE                                           TYPE_GMM

// **** GMMx285C Register Definition ****
// Address
#define GMMx285C_ADDRESS                                        0x285C
// Type
#define GMMx285C_TYPE                                           TYPE_GMM

// **** GMMx2860 Register Definition ****
// Address
#define GMMx2860_ADDRESS                                        0x2860
// Type
#define GMMx2860_TYPE                                           TYPE_GMM

// **** GMMx2864 Register Definition ****
// Address
#define GMMx2864_ADDRESS                                        0x2864
// Type
#define GMMx2864_TYPE                                           TYPE_GMM

// **** GMMx2868 Register Definition ****
// Address
#define GMMx2868_ADDRESS                                        0x2868
// Type
#define GMMx2868_TYPE                                           TYPE_GMM

// **** GMMx286C Register Definition ****
// Address
#define GMMx286C_ADDRESS                                        0x286C
// Type
#define GMMx286C_TYPE                                           TYPE_GMM

// **** GMMx2878 Register Definition ****
// Address
#define GMMx2878_ADDRESS                                        0x2878

// Type
#define GMMx2878_TYPE                                           TYPE_GMM
// Field Data
#define GMMx2878_DEF_OFFSET                                     0
#define GMMx2878_DEF_WIDTH                                      28
#define GMMx2878_DEF_MASK                                       0xfffffff
#define GMMx2878_LOCK_MC_FUS_DRAM_REGS_OFFSET                   28
#define GMMx2878_LOCK_MC_FUS_DRAM_REGS_WIDTH                    1
#define GMMx2878_LOCK_MC_FUS_DRAM_REGS_MASK                     0x10000000
#define GMMx2878_Reserved_OFFSET                                29
#define GMMx2878_Reserved_WIDTH                                 3
#define GMMx2878_Reserved_MASK                                  0xe0000000

/// GMMx2878
typedef union {
  struct {                                                              ///<
    UINT32                                                      DEF:28; ///<
    UINT32                                    LOCK_MC_FUS_DRAM_REGS:1 ; ///<
    UINT32                                                 Reserved:3 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx2878_STRUCT;

// **** GMMx28CC Register Definition ****
// Address
#define GMMx28CC_ADDRESS                                        0x28cc
// Type
#define GMMx28CC_TYPE                                           TYPE_GMM

// **** GMMx28D4 Register Definition ****
// Address
#define GMMx28D4_ADDRESS                                        0x28d4
// Type
#define GMMx28D4_TYPE                                           TYPE_GMM

// **** GMMx28D8 Register Definition ****
// Address
#define GMMx28D8_ADDRESS                                        0x28d8

// Type
#define GMMx28D8_TYPE                                           TYPE_GMM
// Field Data
#define GMMx28D8_WR_COMBINE_OFF_OFFSET                          0
#define GMMx28D8_WR_COMBINE_OFF_WIDTH                           1
#define GMMx28D8_WR_COMBINE_OFF_MASK                            0x1
#define GMMx28D8_SCLK_CG_DISABLE_OFFSET                         1
#define GMMx28D8_SCLK_CG_DISABLE_WIDTH                          1
#define GMMx28D8_SCLK_CG_DISABLE_MASK                           0x2
#define GMMx28D8_PRB_FILTER_DISABLE_OFFSET                      2
#define GMMx28D8_PRB_FILTER_DISABLE_WIDTH                       1
#define GMMx28D8_PRB_FILTER_DISABLE_MASK                        0x4
#define GMMx28D8_ARB_NRT_STACK_DISABLE_OFFSET                   3
#define GMMx28D8_ARB_NRT_STACK_DISABLE_WIDTH                    1
#define GMMx28D8_ARB_NRT_STACK_DISABLE_MASK                     0x8
#define GMMx28D8_ARB_FIXED_PRIORITY_OFFSET                      4
#define GMMx28D8_ARB_FIXED_PRIORITY_WIDTH                       1
#define GMMx28D8_ARB_FIXED_PRIORITY_MASK                        0x10
#define GMMx28D8_PRIORITY_UPDATE_DISABLE_OFFSET                 5
#define GMMx28D8_PRIORITY_UPDATE_DISABLE_WIDTH                  1
#define GMMx28D8_PRIORITY_UPDATE_DISABLE_MASK                   0x20
#define GMMx28D8_RT_BYPASS_OFF_OFFSET                           6
#define GMMx28D8_RT_BYPASS_OFF_WIDTH                            1
#define GMMx28D8_RT_BYPASS_OFF_MASK                             0x40
#define GMMx28D8_SYNC_ON_ERROR_DISABLE_OFFSET                   7
#define GMMx28D8_SYNC_ON_ERROR_DISABLE_WIDTH                    1
#define GMMx28D8_SYNC_ON_ERROR_DISABLE_MASK                     0x80
#define GMMx28D8_SYNC_REFLECT_DISABLE_OFFSET                    8
#define GMMx28D8_SYNC_REFLECT_DISABLE_WIDTH                     1
#define GMMx28D8_SYNC_REFLECT_DISABLE_MASK                      0x100
#define GMMx28D8_Reserved_OFFSET                                9
#define GMMx28D8_Reserved_WIDTH                                 1
#define GMMx28D8_Reserved_MASK                                  0x200
#define GMMx28D8_ARB_STALL_EN_OFFSET                            10
#define GMMx28D8_ARB_STALL_EN_WIDTH                             1
#define GMMx28D8_ARB_STALL_EN_MASK                              0x400
#define GMMx28D8_CREDIT_STALL_EN_OFFSET                         11
#define GMMx28D8_CREDIT_STALL_EN_WIDTH                          1
#define GMMx28D8_CREDIT_STALL_EN_MASK                           0x800
#define GMMx28D8_ARB_STALL_SET_SEL_OFFSET                       12
#define GMMx28D8_ARB_STALL_SET_SEL_WIDTH                        2
#define GMMx28D8_ARB_STALL_SET_SEL_MASK                         0x3000
#define GMMx28D8_ARB_STALL_CLR_SEL_OFFSET                       14
#define GMMx28D8_ARB_STALL_CLR_SEL_WIDTH                        2
#define GMMx28D8_ARB_STALL_CLR_SEL_MASK                         0xc000
#define GMMx28D8_CREDIT_STALL_SET_SEL_OFFSET                    16
#define GMMx28D8_CREDIT_STALL_SET_SEL_WIDTH                     2
#define GMMx28D8_CREDIT_STALL_SET_SEL_MASK                      0x30000
#define GMMx28D8_CREDIT_STALL_CLR_SEL_OFFSET                    18
#define GMMx28D8_CREDIT_STALL_CLR_SEL_WIDTH                     2
#define GMMx28D8_CREDIT_STALL_CLR_SEL_MASK                      0xc0000
#define GMMx28D8_WR_REORDER_OFF_OFFSET                          20
#define GMMx28D8_WR_REORDER_OFF_WIDTH                           1
#define GMMx28D8_WR_REORDER_OFF_MASK                            0x100000
#define GMMx28D8_Reserved21_31_OFFSET                           21
#define GMMx28D8_Reserved21_31_WIDTH                            11
#define GMMx28D8_Reserved21_31_MASK                             0xffe00000

/// GMMx28D8
typedef union {
  struct {                                                              ///<
    UINT32                                           WR_COMBINE_OFF:1 ; ///<
    UINT32                                          SCLK_CG_DISABLE:1 ; ///<
    UINT32                                       PRB_FILTER_DISABLE:1 ; ///<
    UINT32                                    ARB_NRT_STACK_DISABLE:1 ; ///<
    UINT32                                       ARB_FIXED_PRIORITY:1 ; ///<
    UINT32                                  PRIORITY_UPDATE_DISABLE:1 ; ///<
    UINT32                                            RT_BYPASS_OFF:1 ; ///<
    UINT32                                    SYNC_ON_ERROR_DISABLE:1 ; ///<
    UINT32                                     SYNC_REFLECT_DISABLE:1 ; ///<
    UINT32                                                 Reserved:1 ; ///<
    UINT32                                             ARB_STALL_EN:1 ; ///<
    UINT32                                          CREDIT_STALL_EN:1 ; ///<
    UINT32                                        ARB_STALL_SET_SEL:2 ; ///<
    UINT32                                        ARB_STALL_CLR_SEL:2 ; ///<
    UINT32                                     CREDIT_STALL_SET_SEL:2 ; ///<
    UINT32                                     CREDIT_STALL_CLR_SEL:2 ; ///<
    UINT32                                           WR_REORDER_OFF:1 ; ///<
    UINT32                                            Reserved21_31:11; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx28D8_STRUCT;

// **** GMMx28DC Register Definition ****
// Address
#define GMMx28DC_ADDRESS                                        0x28dc
// Type
#define GMMx28DC_TYPE                                           TYPE_GMM

// **** GMMx2C04 Register Definition ****
// Address
#define GMMx2C04_ADDRESS                                        0x2C04
// Type
#define GMMx2C04_TYPE                                           TYPE_GMM

// Field Data
#define GMMx2C04_NONSURF_BASE_OFFSET                            0
#define GMMx2C04_NONSURF_BASE_WIDTH                             32
#define GMMx2C04_NONSURF_BASE_MASK                              0xFFFFFFFF

/// GMMx2C04
typedef union {
  struct {                                                            ///<
    UINT32                                            NONSURF_BASE:32; ///<

  } Field;

  UINT32 Value;
} GMMx2C04_STRUCT;

// **** GMMx3500 Register Definition ****
// Address
#define GMMx3500_ADDRESS                                        0x3500
// Type
#define GMMx3500_TYPE                                           TYPE_GMM

// **** GMMx3504 Register Definition ****
// Address
#define GMMx3504_ADDRESS                                        0x3504
// Type
#define GMMx3504_TYPE                                           TYPE_GMM

// **** GMMx3508 Register Definition ****
// Address
#define GMMx3508_ADDRESS                                        0x3508

// Type
#define GMMx3508_TYPE                                           TYPE_GMM
// Field Data
#define GMMx3508_RENG_EXECUTE_ON_PWR_UP_OFFSET                  0
#define GMMx3508_RENG_EXECUTE_ON_PWR_UP_WIDTH                   1
#define GMMx3508_RENG_EXECUTE_ON_PWR_UP_MASK                    0x1
#define GMMx3508_RENG_EXECUTE_NOW_OFFSET                        1
#define GMMx3508_RENG_EXECUTE_NOW_WIDTH                         1
#define GMMx3508_RENG_EXECUTE_NOW_MASK                          0x2
#define GMMx3508_RENG_EXECUTE_NOW_START_PTR_OFFSET              2
#define GMMx3508_RENG_EXECUTE_NOW_START_PTR_WIDTH               10
#define GMMx3508_RENG_EXECUTE_NOW_START_PTR_MASK                0xffc
#define GMMx3508_RENG_EXECUTE_DSP_END_PTR_OFFSET                12
#define GMMx3508_RENG_EXECUTE_DSP_END_PTR_WIDTH                 10
#define GMMx3508_RENG_EXECUTE_DSP_END_PTR_MASK                  0x3ff000
#define GMMx3508_RENG_EXECUTE_END_PTR_OFFSET                    22
#define GMMx3508_RENG_EXECUTE_END_PTR_WIDTH                     10
#define GMMx3508_RENG_EXECUTE_END_PTR_MASK                      0xffc00000

/// GMMx3508
typedef union {
  struct {                                                              ///<
    UINT32                                   RENG_EXECUTE_ON_PWR_UP:1 ; ///<
    UINT32                                         RENG_EXECUTE_NOW:1 ; ///<
    UINT32                               RENG_EXECUTE_NOW_START_PTR:10; ///<
    UINT32                                 RENG_EXECUTE_DSP_END_PTR:10; ///<
    UINT32                                     RENG_EXECUTE_END_PTR:10; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx3508_STRUCT;

// **** GMMx350C Register Definition ****
// Address
#define GMMx350C_ADDRESS                                        0x350c

// Type
#define GMMx350C_TYPE                                           TYPE_GMM
// Field Data
#define GMMx350C_RENG_EXECUTE_NONSECURE_START_PTR_OFFSET        0
#define GMMx350C_RENG_EXECUTE_NONSECURE_START_PTR_WIDTH         10
#define GMMx350C_RENG_EXECUTE_NONSECURE_START_PTR_MASK          0x3ff
#define GMMx350C_RENG_EXECUTE_NOW_MODE_OFFSET                   10
#define GMMx350C_RENG_EXECUTE_NOW_MODE_WIDTH                    1
#define GMMx350C_RENG_EXECUTE_NOW_MODE_MASK                     0x400
#define GMMx350C_RENG_EXECUTE_ON_REG_UPDATE_OFFSET              11
#define GMMx350C_RENG_EXECUTE_ON_REG_UPDATE_WIDTH               1
#define GMMx350C_RENG_EXECUTE_ON_REG_UPDATE_MASK                0x800
#define GMMx350C_RENG_SRBM_CREDITS_MCD_OFFSET                   12
#define GMMx350C_RENG_SRBM_CREDITS_MCD_WIDTH                    4
#define GMMx350C_RENG_SRBM_CREDITS_MCD_MASK                     0xf000
#define GMMx350C_STCTRL_STUTTER_EN_OFFSET                       16
#define GMMx350C_STCTRL_STUTTER_EN_WIDTH                        1
#define GMMx350C_STCTRL_STUTTER_EN_MASK                         0x10000
#define GMMx350C_STCTRL_GMC_IDLE_THRESHOLD_OFFSET               17
#define GMMx350C_STCTRL_GMC_IDLE_THRESHOLD_WIDTH                2
#define GMMx350C_STCTRL_GMC_IDLE_THRESHOLD_MASK                 0x60000
#define GMMx350C_STCTRL_SRBM_IDLE_THRESHOLD_OFFSET              19
#define GMMx350C_STCTRL_SRBM_IDLE_THRESHOLD_WIDTH               2
#define GMMx350C_STCTRL_SRBM_IDLE_THRESHOLD_MASK                0x180000
#define GMMx350C_STCTRL_IGNORE_PRE_SR_OFFSET                    21
#define GMMx350C_STCTRL_IGNORE_PRE_SR_WIDTH                     1
#define GMMx350C_STCTRL_IGNORE_PRE_SR_MASK                      0x200000
#define GMMx350C_STCTRL_IGNORE_ALLOW_STOP_OFFSET                22
#define GMMx350C_STCTRL_IGNORE_ALLOW_STOP_WIDTH                 1
#define GMMx350C_STCTRL_IGNORE_ALLOW_STOP_MASK                  0x400000
#define GMMx350C_STCTRL_IGNORE_SR_COMMIT_OFFSET                 23
#define GMMx350C_STCTRL_IGNORE_SR_COMMIT_WIDTH                  1
#define GMMx350C_STCTRL_IGNORE_SR_COMMIT_MASK                   0x800000
#define GMMx350C_STCTRL_IGNORE_PROTECTION_FAULT_OFFSET          24
#define GMMx350C_STCTRL_IGNORE_PROTECTION_FAULT_WIDTH           1
#define GMMx350C_STCTRL_IGNORE_PROTECTION_FAULT_MASK            0x1000000
#define GMMx350C_STCTRL_DISABLE_ALLOW_SR_OFFSET                 25
#define GMMx350C_STCTRL_DISABLE_ALLOW_SR_WIDTH                  1
#define GMMx350C_STCTRL_DISABLE_ALLOW_SR_MASK                   0x2000000
#define GMMx350C_STCTRL_DISABLE_GMC_OFFLINE_OFFSET              26
#define GMMx350C_STCTRL_DISABLE_GMC_OFFLINE_WIDTH               1
#define GMMx350C_STCTRL_DISABLE_GMC_OFFLINE_MASK                0x4000000
#define GMMx350C_CRITICAL_REGS_LOCK_OFFSET                      27
#define GMMx350C_CRITICAL_REGS_LOCK_WIDTH                       1
#define GMMx350C_CRITICAL_REGS_LOCK_MASK                        0x8000000
#define GMMx350C_ALLOW_DEEP_SLEEP_MODE_OFFSET                   28
#define GMMx350C_ALLOW_DEEP_SLEEP_MODE_WIDTH                    3
#define GMMx350C_ALLOW_DEEP_SLEEP_MODE_MASK                     0x70000000
#define GMMx350C_STCTRL_FORCE_ALLOW_SR_OFFSET                   31
#define GMMx350C_STCTRL_FORCE_ALLOW_SR_WIDTH                    1
#define GMMx350C_STCTRL_FORCE_ALLOW_SR_MASK                     0x80000000

/// GMMx350C
typedef union {
  struct {                                                              ///<
    UINT32                         RENG_EXECUTE_NONSECURE_START_PTR:10; ///<
    UINT32                                    RENG_EXECUTE_NOW_MODE:1 ; ///<
    UINT32                               RENG_EXECUTE_ON_REG_UPDATE:1 ; ///<
    UINT32                                    RENG_SRBM_CREDITS_MCD:4 ; ///<
    UINT32                                        STCTRL_STUTTER_EN:1 ; ///<
    UINT32                                STCTRL_GMC_IDLE_THRESHOLD:2 ; ///<
    UINT32                               STCTRL_SRBM_IDLE_THRESHOLD:2 ; ///<
    UINT32                                     STCTRL_IGNORE_PRE_SR:1 ; ///<
    UINT32                                 STCTRL_IGNORE_ALLOW_STOP:1 ; ///<
    UINT32                                  STCTRL_IGNORE_SR_COMMIT:1 ; ///<
    UINT32                           STCTRL_IGNORE_PROTECTION_FAULT:1 ; ///<
    UINT32                                  STCTRL_DISABLE_ALLOW_SR:1 ; ///<
    UINT32                               STCTRL_DISABLE_GMC_OFFLINE:1 ; ///<
    UINT32                                       CRITICAL_REGS_LOCK:1 ; ///<
    UINT32                                    ALLOW_DEEP_SLEEP_MODE:3 ; ///<
    UINT32                                    STCTRL_FORCE_ALLOW_SR:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx350C_STRUCT;

// **** GMMx3538 Register Definition ****
// Address
#define GMMx3538_ADDRESS                                        0x3538
// Type
#define GMMx3538_TYPE                                           TYPE_GMM

// **** GMMx353C Register Definition ****
// Address
#define GMMx353C_ADDRESS                                        0x353c
// Type
#define GMMx353C_TYPE                                           TYPE_GMM

// **** GMMx3544 Register Definition ****
// Address
#define GMMx3544_ADDRESS                                        0x3544
// Type
#define GMMx3544_TYPE                                           TYPE_GMM

// **** GMMx3700 Register Definition ****
// Address
#define GMMx3700_ADDRESS                                        0x3700
// Type
#define GMMx3700_TYPE                                           TYPE_GMM

// **** GMMx3704 Register Definition ****
// Address
#define GMMx3704_ADDRESS                                        0x3704
// Type
#define GMMx3704_TYPE                                           TYPE_GMM

// **** GMMx3748 Register Definition ****
// Address
#define GMMx3748_ADDRESS                                        0x3748
// Type
#define GMMx3748_TYPE                                           TYPE_GMM

// **** GMMx3750 Register Definition ****
// Address
#define GMMx3750_ADDRESS                                        0x3750
// Type
#define GMMx3750_TYPE                                           TYPE_GMM

// **** GMMx3754 Register Definition ****
// Address
#define GMMx3754_ADDRESS                                        0x3754
// Type
#define GMMx3754_TYPE                                           TYPE_GMM

// **** GMMx3758 Register Definition ****
// Address
#define GMMx3758_ADDRESS                                        0x3758
// Type
#define GMMx3758_TYPE                                           TYPE_GMM

// **** GMMx375C Register Definition ****
// Address
#define GMMx375C_ADDRESS                                        0x375c
// Type
#define GMMx375C_TYPE                                           TYPE_GMM

// **** GMMx3760 Register Definition ****
// Address
#define GMMx3760_ADDRESS                                        0x3760
// Type
#define GMMx3760_TYPE                                           TYPE_GMM

// **** GMMx3764 Register Definition ****
// Address
#define GMMx3764_ADDRESS                                        0x3764
// Type
#define GMMx3764_TYPE                                           TYPE_GMM

// **** GMMx3768 Register Definition ****
// Address
#define GMMx3768_ADDRESS                                        0x3768
// Type
#define GMMx3768_TYPE                                           TYPE_GMM

// **** GMMx376C Register Definition ****
// Address
#define GMMx376C_ADDRESS                                        0x376C
// Type
#define GMMx376C_TYPE                                           TYPE_GMM

// **** GMMx37F0 Register Definition ****
// Address
#define GMMx37F0_ADDRESS                                        0x37f0
// Type
#define GMMx37F0_TYPE                                           TYPE_GMM

// **** GMMx37F4 Register Definition ****
// Address
#define GMMx37F4_ADDRESS                                        0x37f4
// Type
#define GMMx37F4_TYPE                                           TYPE_GMM

// **** GMMx37F8 Register Definition ****
// Address
#define GMMx37F8_ADDRESS                                        0x37f8
// Type
#define GMMx37F8_TYPE                                           TYPE_GMM

// **** GMMx37FC Register Definition ****
// Address
#define GMMx37FC_ADDRESS                                        0x37fc
// Type
#define GMMx37FC_TYPE                                           TYPE_GMM

// **** GMMx5228 Register Definition ****
// Address
#define GMMx5228_ADDRESS                                        0x5228

// Type
#define GMMx5228_TYPE                                           TYPE_GMM
// Field Data
#define GMMx5228_BIF_MEM_SD_EN_OFFSET                           0
#define GMMx5228_BIF_MEM_SD_EN_WIDTH                            1
#define GMMx5228_BIF_MEM_SD_EN_MASK                             0x1
#define GMMx5228_Reserved_OFFSET                                1
#define GMMx5228_Reserved_WIDTH                                 15
#define GMMx5228_Reserved_MASK                                  0xfffe
#define GMMx5228_BIF_MEM_SD_TIMER_OFFSET                        16
#define GMMx5228_BIF_MEM_SD_TIMER_WIDTH                         16
#define GMMx5228_BIF_MEM_SD_TIMER_MASK                          0xffff0000

/// GMMx5228
typedef union {
  struct {                                                              ///<
    UINT32                                            BIF_MEM_SD_EN:1 ; ///<
    UINT32                                                 Reserved:15; ///<
    UINT32                                         BIF_MEM_SD_TIMER:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx5228_STRUCT;

// **** GMMx5428 Register Definition ****
// Address
#define GMMx5428_ADDRESS                                        0x5428
// Type
#define GMMx5428_TYPE                                           TYPE_GMM

// Field Data
#define GMMx5428_CONFIG_MEMSIZE_OFFSET                          0
#define GMMx5428_CONFIG_MEMSIZE_WIDTH                           32
#define GMMx5428_CONFIG_MEMSIZE_MASK                            0xFFFFFFFF

/// GMMx5428
typedef union {
  struct {                                                            ///<
    UINT32                                          CONFIG_MEMSIZE:32; ///<

  } Field;

  UINT32 Value;
} GMMx5428_STRUCT;

// **** GMMx5490 Register Definition ****
// Address
#define GMMx5490_ADDRESS                                        0x5490
// Type
#define GMMx5490_TYPE                                           TYPE_GMM

// Field Data
#define GMMx5490_FB_READ_EN_OFFSET                              0
#define GMMx5490_FB_READ_EN_WIDTH                               1
#define GMMx5490_FB_READ_EN_MASK                                0x1
#define GMMx5490_FB_WRITE_EN_OFFSET                             1
#define GMMx5490_FB_WRITE_EN_WIDTH                              1
#define GMMx5490_FB_WRITE_EN_MASK                               0x2
#define GMMx5490_Reserved_31_2_OFFSET                           2
#define GMMx5490_Reserved_31_2_WIDTH                            30
#define GMMx5490_Reserved_31_2_MASK                             0xFFFFFFFC

/// GMMx5490
typedef union {
  struct {                                                            ///<
    UINT32                                              FB_READ_EN:1; ///<
    UINT32                                             FB_WRITE_EN:1; ///<
    UINT32                                           Reserved_31_2:30; ///<

  } Field;

  UINT32 Value;
} GMMx5490_STRUCT;

// **** GMMx5C40 Register Definition ****
// Address
#define GMMx5C40_ADDRESS                                        0x5c40

// Type
#define GMMx5C40_TYPE                                           TYPE_GMM
// Field Data
#define GMMx5C40_PLL_MACRO_CNTL_RESERVED_OFFSET                 0
#define GMMx5C40_PLL_MACRO_CNTL_RESERVED_WIDTH                  32
#define GMMx5C40_PLL_MACRO_CNTL_RESERVED_MASK                   0xffffffff

/// GMMx5C40
typedef union {
  struct {                                                              ///<
    UINT32                                  PLL_MACRO_CNTL_RESERVED:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx5C40_STRUCT;

// **** GMMx60D0 Register Definition ****
// Address
#define GMMx60D0_ADDRESS                                        0x60d0

// Type
#define GMMx60D0_TYPE                                           TYPE_GMM
// Field Data
#define GMMx60D0_PORT_CONNECTIVITY_OFFSET                       0
#define GMMx60D0_PORT_CONNECTIVITY_WIDTH                        3
#define GMMx60D0_PORT_CONNECTIVITY_MASK                         0x7
#define GMMx60D0_Reserved_OFFSET                                3
#define GMMx60D0_Reserved_WIDTH                                 1
#define GMMx60D0_Reserved_MASK                                  0x8
#define GMMx60D0_PORT_CONNECTIVITY_OVERRIDE_ENABLE_OFFSET       4
#define GMMx60D0_PORT_CONNECTIVITY_OVERRIDE_ENABLE_WIDTH        1
#define GMMx60D0_PORT_CONNECTIVITY_OVERRIDE_ENABLE_MASK         0x10
#define GMMx60D0_Reserved5_31_OFFSET                            5
#define GMMx60D0_Reserved5_31_WIDTH                             27
#define GMMx60D0_Reserved5_31_MASK                              0xffffffe0

/// GMMx60D0
typedef union {
  struct {                                                              ///<
    UINT32                                        PORT_CONNECTIVITY:3 ; ///<
    UINT32                                                 Reserved:1 ; ///<
    UINT32                        PORT_CONNECTIVITY_OVERRIDE_ENABLE:1 ; ///<
    UINT32                                             Reserved5_31:27; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx60D0_STRUCT;

// **** GMMx6CD4 Register Definition ****
// Address
#define GMMx6CD4_ADDRESS                                        0x6cd4

// Type
#define GMMx6CD4_TYPE                                           TYPE_GMM
// Field Data
#define GMMx6CD4_STUTTER_ENABLE_OFFSET                          0
#define GMMx6CD4_STUTTER_ENABLE_WIDTH                           1
#define GMMx6CD4_STUTTER_ENABLE_MASK                            0x1
#define GMMx6CD4_Reserved_OFFSET                                1
#define GMMx6CD4_Reserved_WIDTH                                 3
#define GMMx6CD4_Reserved_MASK                                  0xe
#define GMMx6CD4_STUTTER_IGNORE_CURSOR_OFFSET                   4
#define GMMx6CD4_STUTTER_IGNORE_CURSOR_WIDTH                    1
#define GMMx6CD4_STUTTER_IGNORE_CURSOR_MASK                     0x10
#define GMMx6CD4_STUTTER_IGNORE_ICON_OFFSET                     5
#define GMMx6CD4_STUTTER_IGNORE_ICON_WIDTH                      1
#define GMMx6CD4_STUTTER_IGNORE_ICON_MASK                       0x20
#define GMMx6CD4_STUTTER_IGNORE_VGA_OFFSET                      6
#define GMMx6CD4_STUTTER_IGNORE_VGA_WIDTH                       1
#define GMMx6CD4_STUTTER_IGNORE_VGA_MASK                        0x40
#define GMMx6CD4_STUTTER_IGNORE_FBC_OFFSET                      7
#define GMMx6CD4_STUTTER_IGNORE_FBC_WIDTH                       1
#define GMMx6CD4_STUTTER_IGNORE_FBC_MASK                        0x80
#define GMMx6CD4_STUTTER_WM_HIGH_FORCE_ON_OFFSET                8
#define GMMx6CD4_STUTTER_WM_HIGH_FORCE_ON_WIDTH                 1
#define GMMx6CD4_STUTTER_WM_HIGH_FORCE_ON_MASK                  0x100
#define GMMx6CD4_STUTTER_WM_HIGH_EXCLUDES_VBLANK_OFFSET         9
#define GMMx6CD4_STUTTER_WM_HIGH_EXCLUDES_VBLANK_WIDTH          1
#define GMMx6CD4_STUTTER_WM_HIGH_EXCLUDES_VBLANK_MASK           0x200
#define GMMx6CD4_STUTTER_URGENT_IN_NOT_SELF_REFRESH_OFFSET      10
#define GMMx6CD4_STUTTER_URGENT_IN_NOT_SELF_REFRESH_WIDTH       1
#define GMMx6CD4_STUTTER_URGENT_IN_NOT_SELF_REFRESH_MASK        0x400
#define GMMx6CD4_STUTTER_SELF_REFRESH_FORCE_ON_OFFSET           11
#define GMMx6CD4_STUTTER_SELF_REFRESH_FORCE_ON_WIDTH            1
#define GMMx6CD4_STUTTER_SELF_REFRESH_FORCE_ON_MASK             0x800
#define GMMx6CD4_Reserved12_15_OFFSET                           12
#define GMMx6CD4_Reserved12_15_WIDTH                            4
#define GMMx6CD4_Reserved12_15_MASK                             0xf000
#define GMMx6CD4_STUTTER_EXIT_SELF_REFRESH_WATERMARK_OFFSET     16
#define GMMx6CD4_STUTTER_EXIT_SELF_REFRESH_WATERMARK_WIDTH      16
#define GMMx6CD4_STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK       0xffff0000

/// GMMx6CD4
typedef union {
  struct {                                                              ///<
    UINT32                                           STUTTER_ENABLE:1 ; ///<
    UINT32                                                 Reserved:3 ; ///<
    UINT32                                    STUTTER_IGNORE_CURSOR:1 ; ///<
    UINT32                                      STUTTER_IGNORE_ICON:1 ; ///<
    UINT32                                       STUTTER_IGNORE_VGA:1 ; ///<
    UINT32                                       STUTTER_IGNORE_FBC:1 ; ///<
    UINT32                                 STUTTER_WM_HIGH_FORCE_ON:1 ; ///<
    UINT32                          STUTTER_WM_HIGH_EXCLUDES_VBLANK:1 ; ///<
    UINT32                       STUTTER_URGENT_IN_NOT_SELF_REFRESH:1 ; ///<
    UINT32                            STUTTER_SELF_REFRESH_FORCE_ON:1 ; ///<
    UINT32                                            Reserved12_15:4 ; ///<
    UINT32                      STUTTER_EXIT_SELF_REFRESH_WATERMARK:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx6CD4_STRUCT;

// **** GMMx6CD8 Register Definition ****
// Address
#define GMMx6CD8_ADDRESS                                        0x6cd8

// Type
#define GMMx6CD8_TYPE                                           TYPE_GMM

// **** GMMx74D8 Register Definition ****
// Address
#define GMMx74D8_ADDRESS                                        0x74d8

// Type
#define GMMx74D8_TYPE                                           TYPE_GMM

// **** GMMx7CD8 Register Definition ****
// Address
#define GMMx7CD8_ADDRESS                                        0x7cd8

// Type
#define GMMx7CD8_TYPE                                           TYPE_GMM

// **** GMMxD008 Register Definition ****
// Address
#define GMMxD008_ADDRESS                                        0xd008

// Type
#define GMMxD008_TYPE                                           TYPE_GMM
// Field Data
#define GMMxD008_Reserved_OFFSET                                0
#define GMMxD008_Reserved_WIDTH                                 8
#define GMMxD008_Reserved_MASK                                  0xff
#define GMMxD008_MEM_POWER_OVERRIDE_OFFSET                      8
#define GMMxD008_MEM_POWER_OVERRIDE_WIDTH                       1
#define GMMxD008_MEM_POWER_OVERRIDE_MASK                        0x100
#define GMMxD008_MEM_POWER_LS_EN_OFFSET                         9
#define GMMxD008_MEM_POWER_LS_EN_WIDTH                          1
#define GMMxD008_MEM_POWER_LS_EN_MASK                           0x200
#define GMMxD008_MEM_POWER_DS_EN_OFFSET                         10
#define GMMxD008_MEM_POWER_DS_EN_WIDTH                          1
#define GMMxD008_MEM_POWER_DS_EN_MASK                           0x400
#define GMMxD008_MEM_POWER_SD_EN_OFFSET                         11
#define GMMxD008_MEM_POWER_SD_EN_WIDTH                          1
#define GMMxD008_MEM_POWER_SD_EN_MASK                           0x800
#define GMMxD008_MEM_POWER_DELAY_OFFSET                         12
#define GMMxD008_MEM_POWER_DELAY_WIDTH                          10
#define GMMxD008_MEM_POWER_DELAY_MASK                           0x3ff000
#define GMMxD008_Reserved22_31_OFFSET                           22
#define GMMxD008_Reserved22_31_WIDTH                            10
#define GMMxD008_Reserved22_31_MASK                             0xffc00000

/// GMMxD008
typedef union {
  struct {                                                              ///<
    UINT32                                                 Reserved:8 ; ///<
    UINT32                                       MEM_POWER_OVERRIDE:1 ; ///<
    UINT32                                          MEM_POWER_LS_EN:1 ; ///<
    UINT32                                          MEM_POWER_DS_EN:1 ; ///<
    UINT32                                          MEM_POWER_SD_EN:1 ; ///<
    UINT32                                          MEM_POWER_DELAY:10; ///<
    UINT32                                            Reserved22_31:10; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMxD008_STRUCT;

// **** GMMxD808 Register Definition ****
// Address
#define GMMxD808_ADDRESS                                        0xd808

// Type
#define GMMxD808_TYPE                                           TYPE_GMM
// Field Data
#define GMMxD808_Reserved_OFFSET                                0
#define GMMxD808_Reserved_WIDTH                                 8
#define GMMxD808_Reserved_MASK                                  0xff
#define GMMxD808_MEM_POWER_OVERRIDE_OFFSET                      8
#define GMMxD808_MEM_POWER_OVERRIDE_WIDTH                       1
#define GMMxD808_MEM_POWER_OVERRIDE_MASK                        0x100
#define GMMxD808_MEM_POWER_LS_EN_OFFSET                         9
#define GMMxD808_MEM_POWER_LS_EN_WIDTH                          1
#define GMMxD808_MEM_POWER_LS_EN_MASK                           0x200
#define GMMxD808_MEM_POWER_DS_EN_OFFSET                         10
#define GMMxD808_MEM_POWER_DS_EN_WIDTH                          1
#define GMMxD808_MEM_POWER_DS_EN_MASK                           0x400
#define GMMxD808_MEM_POWER_SD_EN_OFFSET                         11
#define GMMxD808_MEM_POWER_SD_EN_WIDTH                          1
#define GMMxD808_MEM_POWER_SD_EN_MASK                           0x800
#define GMMxD808_MEM_POWER_DELAY_OFFSET                         12
#define GMMxD808_MEM_POWER_DELAY_WIDTH                          10
#define GMMxD808_MEM_POWER_DELAY_MASK                           0x3ff000
#define GMMxD808_Reserved22_31_OFFSET                           22
#define GMMxD808_Reserved22_31_WIDTH                            10
#define GMMxD808_Reserved22_31_MASK                             0xffc00000

/// GMMxD808
typedef union {
  struct {                                                              ///<
    UINT32                                                 Reserved:8 ; ///<
    UINT32                                       MEM_POWER_OVERRIDE:1 ; ///<
    UINT32                                          MEM_POWER_LS_EN:1 ; ///<
    UINT32                                          MEM_POWER_DS_EN:1 ; ///<
    UINT32                                          MEM_POWER_SD_EN:1 ; ///<
    UINT32                                          MEM_POWER_DELAY:10; ///<
    UINT32                                            Reserved22_31:10; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMxD808_STRUCT;

// **** GMMx1206C Register Definition ****
// Address
#define GMMx1206C_ADDRESS                                        0x1206c
// Type
#define GMMx1206C_TYPE                                           TYPE_GMM

// Field Data
#define GMMx1206C_LVTMA_PWRSEQ_EN_OFFSET                         0
#define GMMx1206C_LVTMA_PWRSEQ_EN_WIDTH                          1
#define GMMx1206C_LVTMA_PWRSEQ_EN_MASK                           0x1
#define GMMx1206C_LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN_OFFSET 1
#define GMMx1206C_LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN_WIDTH 1
#define GMMx1206C_LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN_MASK 0x2
#define GMMx1206C_Reserved_3_2_OFFSET                            2
#define GMMx1206C_Reserved_3_2_WIDTH                             2
#define GMMx1206C_Reserved_3_2_MASK                              0xC
#define GMMx1206C_LVTMA_PWRSEQ_TARGET_STATE_OFFSET               4
#define GMMx1206C_LVTMA_PWRSEQ_TARGET_STATE_WIDTH                1
#define GMMx1206C_LVTMA_PWRSEQ_TARGET_STATE_MASK                 0x10
#define GMMx1206C_Reserved_7_5_OFFSET                            5
#define GMMx1206C_Reserved_7_5_WIDTH                             3
#define GMMx1206C_Reserved_7_5_MASK                              0xE0
#define GMMx1206C_LVTMA_SYNCEN_OFFSET                            8
#define GMMx1206C_LVTMA_SYNCEN_WIDTH                             1
#define GMMx1206C_LVTMA_SYNCEN_MASK                              0x100
#define GMMx1206C_LVTMA_SYNCEN_OVRD_OFFSET                       9
#define GMMx1206C_LVTMA_SYNCEN_OVRD_WIDTH                        1
#define GMMx1206C_LVTMA_SYNCEN_OVRD_MASK                         0x200
#define GMMx1206C_LVTMA_SYNCEN_POL_OFFSET                        10
#define GMMx1206C_LVTMA_SYNCEN_POL_WIDTH                         1
#define GMMx1206C_LVTMA_SYNCEN_POL_MASK                          0x400
#define GMMx1206C_Reserved_15_11_OFFSET                          11
#define GMMx1206C_Reserved_15_11_WIDTH                           5
#define GMMx1206C_Reserved_15_11_MASK                            0xF800
#define GMMx1206C_LVTMA_DIGON_OFFSET                             16
#define GMMx1206C_LVTMA_DIGON_WIDTH                              1
#define GMMx1206C_LVTMA_DIGON_MASK                               0x10000
#define GMMx1206C_LVTMA_DIGON_OVRD_OFFSET                        17
#define GMMx1206C_LVTMA_DIGON_OVRD_WIDTH                         1
#define GMMx1206C_LVTMA_DIGON_OVRD_MASK                          0x20000
#define GMMx1206C_LVTMA_DIGON_POL_OFFSET                         18
#define GMMx1206C_LVTMA_DIGON_POL_WIDTH                          1
#define GMMx1206C_LVTMA_DIGON_POL_MASK                           0x40000
#define GMMx1206C_Reserved_23_19_OFFSET                          19
#define GMMx1206C_Reserved_23_19_WIDTH                           5
#define GMMx1206C_Reserved_23_19_MASK                            0xF80000
#define GMMx1206C_LVTMA_BLON_OFFSET                              24
#define GMMx1206C_LVTMA_BLON_WIDTH                               1
#define GMMx1206C_LVTMA_BLON_MASK                                0x1000000
#define GMMx1206C_LVTMA_BLON_OVRD_OFFSET                         25
#define GMMx1206C_LVTMA_BLON_OVRD_WIDTH                          1
#define GMMx1206C_LVTMA_BLON_OVRD_MASK                           0x2000000
#define GMMx1206C_LVTMA_BLON_POL_OFFSET                          26
#define GMMx1206C_LVTMA_BLON_POL_WIDTH                           1
#define GMMx1206C_LVTMA_BLON_POL_MASK                            0x4000000
#define GMMx1206C_Reserved_31_27_OFFSET                          27
#define GMMx1206C_Reserved_31_27_WIDTH                           5
#define GMMx1206C_Reserved_31_27_MASK                            0xF8000000

/// GMMx1206C
typedef union {
  struct {                                                            ///<
    UINT32                                         LVTMA_PWRSEQ_EN:1; ///<
    UINT32            LVTMA_PWRSEQ_DISABLE_SYNCEN_CONTROL_OF_TX_EN:1; ///<
    UINT32                                            Reserved_3_2:2; ///<
    UINT32                               LVTMA_PWRSEQ_TARGET_STATE:1; ///<
    UINT32                                            Reserved_7_5:3; ///<
    UINT32                                            LVTMA_SYNCEN:1; ///<
    UINT32                                       LVTMA_SYNCEN_OVRD:1; ///<
    UINT32                                        LVTMA_SYNCEN_POL:1; ///<
    UINT32                                          Reserved_15_11:5; ///<
    UINT32                                             LVTMA_DIGON:1; ///<
    UINT32                                        LVTMA_DIGON_OVRD:1; ///<
    UINT32                                         LVTMA_DIGON_POL:1; ///<
    UINT32                                          Reserved_23_19:5; ///<
    UINT32                                              LVTMA_BLON:1; ///<
    UINT32                                         LVTMA_BLON_OVRD:1; ///<
    UINT32                                          LVTMA_BLON_POL:1; ///<
    UINT32                                          Reserved_31_27:5; ///<

  } Field;

  UINT32 Value;
} GMMx1206C_STRUCT;

// **** GMMx1474C Register Definition ****
// Address
#define GMMx1474C_ADDRESS                                       0x1474c

// Type
#define GMMx1474C_TYPE                                          TYPE_GMM
// Field Data
#define GMMx1474C_ACP_I2S_PIN_CONFIG_OFFSET                     0
#define GMMx1474C_ACP_I2S_PIN_CONFIG_WIDTH                      2
#define GMMx1474C_ACP_I2S_PIN_CONFIG_MASK                       0x3
#define GMMx1474C_Reserved_OFFSET                               2
#define GMMx1474C_Reserved_WIDTH                                30
#define GMMx1474C_Reserved_MASK                                 0xfffffffc

/// GMMx1474C
typedef union {
  struct {                                                              ///<
    UINT32                                       ACP_I2S_PIN_CONFIG:2 ; ///<
    UINT32                                                 Reserved:30; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx1474C_STRUCT;

// **** GMMx14750 Register Definition ****
// Address
#define GMMx14750_ADDRESS                                       0x14750

// Type
#define GMMx14750_TYPE                                          TYPE_GMM
// Field Data
#define GMMx14750_AZ_I2S_SELECT_OFFSET                          0
#define GMMx14750_AZ_I2S_SELECT_WIDTH                           1
#define GMMx14750_AZ_I2S_SELECT_MASK                            0x1
#define GMMx14750_Reserved_OFFSET                               1
#define GMMx14750_Reserved_WIDTH                                31
#define GMMx14750_Reserved_MASK                                 0xfffffffe

/// GMMx14750
typedef union {
  struct {                                                              ///<
    UINT32                                            AZ_I2S_SELECT:1 ; ///<
    UINT32                                                 Reserved:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} GMMx14750_STRUCT;

// **** GMMx3E650 Register Definition ****
// Address
#define GMMx3E650_ADDRESS                                        0x3e650
// Type
#define GMMx3E650_TYPE                                           TYPE_GMM

// **** GMMx3E654 Register Definition ****
// Address
#define GMMx3E654_ADDRESS                                        0x3e654
// Type
#define GMMx3E654_TYPE                                           TYPE_GMM

// **** GMMx3E658 Register Definition ****
// Address
#define GMMx3E658_ADDRESS                                        0x3e658
// Type
#define GMMx3E658_TYPE                                           TYPE_GMM

// **** GMMx3E65C Register Definition ****
// Address
#define GMMx3E65C_ADDRESS                                        0x3e65c
// Type
#define GMMx3E65C_TYPE                                           TYPE_GMM

// **** GMMx3E640 Register Definition ****
// Address
#define GMMx3E640_ADDRESS                                        0x3e640
// Type
#define GMMx3E640_TYPE                                           TYPE_GMM

// **** GMMx3E644 Register Definition ****
// Address
#define GMMx3E644_ADDRESS                                        0x3e644
// Type
#define GMMx3E644_TYPE                                           TYPE_GMM

// **** GMMx3E648 Register Definition ****
// Address
#define GMMx3E648_ADDRESS                                        0x3e648
// Type
#define GMMx3E648_TYPE                                           TYPE_GMM

// **** GMMx3E64C Register Definition ****
// Address
#define GMMx3E64C_ADDRESS                                        0x3e64c
// Type
#define GMMx3E64C_TYPE                                           TYPE_GMM



/// Manually added registers for BTC
// Address
#define D0F0xBC_xC0107120_ADDRESS                                    0xC0107120

// Type
#define D0F0xBC_XC0107120_TYPE                                       TYPE_D0F0xBC

// **** D0F0xBC_xBCComplete Structure Pointer ****
// Address
#define D0F0xBC_x20050_ADDRESS                                       0x20050

// Type
#define D0F0xBC_x20050_TYPE                                          TYPE_D0F0xBC

// **** D0F0xBC_xBCComplete Register Definition ****
// Type
#define D0F0xBC_xBCComplete_TYPE                                     TYPE_D0F0xBC

// For NEW firmware
/// D0F0xBC_xBCComplete
typedef union {
  struct {                                                              ///<
    UINT32                                               Reserved1:24 ; ///<
    UINT32                                             BCCompleted:8  ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xBCComplete_STRUCT;

// **** D0F0xBC_xdV0 Register Definition ****
// Type
#define D0F0xBC_xdV0_TYPE                                     TYPE_D0F0xBC

/// D0F0xBC_xdV0
typedef union {
  struct {                                                              ///<
    UINT32                                                     dV0:32 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xdV0_STRUCT;


// **** D0F0xBC_xdV1 Register Definition ****
// Type
#define D0F0xBC_xdV1_TYPE                                     TYPE_D0F0xBC

/// D0F0xBC_xdV1
typedef union {
  struct {                                                              ///<
    UINT32                                                     dV0:32 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xdV1_STRUCT;

// **** D0F0xBC_xdV2 Register Definition ****
// Type
#define D0F0xBC_xdV2_TYPE                                     TYPE_D0F0xBC

/// D0F0xBC_xdV2
typedef union {
  struct {                                                              ///<
    UINT32                                                     dV0:32 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xdV2_STRUCT;


// For NEW firmware
/// D0F0xBC_xC0107120
typedef union {
  struct {                                                              ///<
    UINT32                                            Reserved0_14:15 ; ///<
    UINT32                                           BC_EnableSoft:1  ; ///<
    UINT32                                           BC_EnableHard:1  ; ///<
    UINT32                                           Reserved17_31:15 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xBC_xc0107120_STRUCT;


// **** D8F0xE8 Register Definition ****
// Address
#define D8F0xE8_ADDRESS                                         0xE8

// **** D8F0xEC_x4A Register Definition ****
// Address
#define D8F0xEC_x4A_ADDRESS                                     0x4A
// Type
#define D8F0xEC_x4A_TYPE                                        TYPE_D8F0xEC

// Field Data
#define D8F0xEC_x4A_Reserved_23_0_OFFSET                         0
#define D8F0xEC_x4A_Reserved_23_0_WIDTH                          24
#define D8F0xEC_x4A_Reserved_23_0_MASK                           0xFFFFFF
#define D8F0xEC_x4A_Reserved_30_24_OFFSET                        24
#define D8F0xEC_x4A_Reserved_30_24_WIDTH                         7
#define D8F0xEC_x4A_Reserved_30_24_MASK                          0x7F000000
#define D8F0xEC_x4A_Reserved_31_31_OFFSET                        31
#define D8F0xEC_x4A_Reserved_31_31_WIDTH                         1
#define D8F0xEC_x4A_Reserved_31_31_MASK                          0x80000000

/// D8F0xEC_x4A
typedef union {
  struct {                                                             ///<
    UINT32                                          Reserved_23_0:24;  ///<
    UINT32                                          Reserved_30_24:7 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;
  UINT32 Value;
} D8F0xEC_x4A_STRUCT;

// **** D8F0xEC_x4C Register Definition ****
// Address
#define D8F0xEC_x4C_ADDRESS                                     0x4C
// Type
#define D8F0xEC_x4C_TYPE                                        TYPE_D8F0xEC

// Field Data
#define D8F0xEC_x4C_Reserved_23_0_OFFSET                         0
#define D8F0xEC_x4C_Reserved_23_0_WIDTH                          24
#define D8F0xEC_x4C_Reserved_23_0_MASK                           0xFFFFFF
#define D8F0xEC_x4C_Reserved_30_24_OFFSET                        24
#define D8F0xEC_x4C_Reserved_30_24_WIDTH                         7
#define D8F0xEC_x4C_Reserved_30_24_MASK                          0x7F000000
#define D8F0xEC_x4C_Reserved_31_31_OFFSET                        31
#define D8F0xEC_x4C_Reserved_31_31_WIDTH                         1
#define D8F0xEC_x4C_Reserved_31_31_MASK                          0x80000000

/// D8F0xEC_x4C
typedef union {
  struct {                                                             ///<
    UINT32                                          Reserved_23_0:24;  ///<
    UINT32                                          Reserved_30_24:7 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;
  UINT32 Value;
} D8F0xEC_x4C_STRUCT;

// **** D8F0xEC_x50 Register Definition ****
// Address
#define D8F0xEC_x50_ADDRESS                                     0x50
// Type
#define D8F0xEC_x50_TYPE                                        TYPE_D8F0xEC

// **** D9F2x04 Register Definition ****
// Address
#define D9F2x04_ADDRESS                                         0x4

// Type
#define D9F2x04_TYPE                                            TYPE_D9F2
// Field Data
#define D9F2x04_Reserved_0_0_OFFSET                             0
#define D9F2x04_Reserved_0_0_WIDTH                              1
#define D9F2x04_Reserved_0_0_MASK                               0x1
#define D9F2x04_MemSpaceEn_OFFSET                               1
#define D9F2x04_MemSpaceEn_WIDTH                                1
#define D9F2x04_MemSpaceEn_MASK                                 0x2
#define D9F2x04_BusMasterEn_OFFSET                              2
#define D9F2x04_BusMasterEn_WIDTH                               1
#define D9F2x04_BusMasterEn_MASK                                0x4
#define D9F2x04_Reserved_5_3_OFFSET                             3
#define D9F2x04_Reserved_5_3_WIDTH                              3
#define D9F2x04_Reserved_5_3_MASK                               0x38
#define D9F2x04_ParityErrorResp_OFFSET                          6
#define D9F2x04_ParityErrorResp_WIDTH                           1
#define D9F2x04_ParityErrorResp_MASK                            0x40
#define D9F2x04_Reserved_7_7_OFFSET                             7
#define D9F2x04_Reserved_7_7_WIDTH                              1
#define D9F2x04_Reserved_7_7_MASK                               0x80
#define D9F2x04_SerrEn_OFFSET                                   8
#define D9F2x04_SerrEn_WIDTH                                    1
#define D9F2x04_SerrEn_MASK                                     0x100
#define D9F2x04_Reserved_9_9_OFFSET                             9
#define D9F2x04_Reserved_9_9_WIDTH                              1
#define D9F2x04_Reserved_9_9_MASK                               0x200
#define D9F2x04_InterruptDis_OFFSET                             10
#define D9F2x04_InterruptDis_WIDTH                              1
#define D9F2x04_InterruptDis_MASK                               0x400
#define D9F2x04_Reserved_18_11_OFFSET                           11
#define D9F2x04_Reserved_18_11_WIDTH                            8
#define D9F2x04_Reserved_18_11_MASK                             0x7f800
#define D9F2x04_IntStatus_OFFSET                                19
#define D9F2x04_IntStatus_WIDTH                                 1
#define D9F2x04_IntStatus_MASK                                  0x80000
#define D9F2x04_CapList_OFFSET                                  20
#define D9F2x04_CapList_WIDTH                                   1
#define D9F2x04_CapList_MASK                                    0x100000
#define D9F2x04_Reserved_23_21_OFFSET                           21
#define D9F2x04_Reserved_23_21_WIDTH                            3
#define D9F2x04_Reserved_23_21_MASK                             0xe00000
#define D9F2x04_MasterDataParityErr_OFFSET                      24
#define D9F2x04_MasterDataParityErr_WIDTH                       1
#define D9F2x04_MasterDataParityErr_MASK                        0x1000000
#define D9F2x04_Reserved_26_25_OFFSET                           25
#define D9F2x04_Reserved_26_25_WIDTH                            2
#define D9F2x04_Reserved_26_25_MASK                             0x6000000
#define D9F2x04_SignaledTargetAbort_OFFSET                      27
#define D9F2x04_SignaledTargetAbort_WIDTH                       1
#define D9F2x04_SignaledTargetAbort_MASK                        0x8000000
#define D9F2x04_ReceivedTargetAbort_OFFSET                      28
#define D9F2x04_ReceivedTargetAbort_WIDTH                       1
#define D9F2x04_ReceivedTargetAbort_MASK                        0x10000000
#define D9F2x04_ReceivedMasterAbort_OFFSET                      29
#define D9F2x04_ReceivedMasterAbort_WIDTH                       1
#define D9F2x04_ReceivedMasterAbort_MASK                        0x20000000
#define D9F2x04_SignaledSystemErr_OFFSET                        30
#define D9F2x04_SignaledSystemErr_WIDTH                         1
#define D9F2x04_SignaledSystemErr_MASK                          0x40000000
#define D9F2x04_DetectedParityErr_OFFSET                        31
#define D9F2x04_DetectedParityErr_WIDTH                         1
#define D9F2x04_DetectedParityErr_MASK                          0x80000000

/// D9F2x04
typedef union {
  struct {                                                              ///<
    UINT32                                             Reserved_0_0:1 ; ///<
    UINT32                                               MemSpaceEn:1 ; ///<
    UINT32                                              BusMasterEn:1 ; ///<
    UINT32                                             Reserved_5_3:3 ; ///<
    UINT32                                          ParityErrorResp:1 ; ///<
    UINT32                                             Reserved_7_7:1 ; ///<
    UINT32                                                   SerrEn:1 ; ///<
    UINT32                                             Reserved_9_9:1 ; ///<
    UINT32                                             InterruptDis:1 ; ///<
    UINT32                                           Reserved_18_11:8 ; ///<
    UINT32                                                IntStatus:1 ; ///<
    UINT32                                                  CapList:1 ; ///<
    UINT32                                           Reserved_23_21:3 ; ///<
    UINT32                                      MasterDataParityErr:1 ; ///<
    UINT32                                           Reserved_26_25:2 ; ///<
    UINT32                                      SignaledTargetAbort:1 ; ///<
    UINT32                                      ReceivedTargetAbort:1 ; ///<
    UINT32                                      ReceivedMasterAbort:1 ; ///<
    UINT32                                        SignaledSystemErr:1 ; ///<
    UINT32                                        DetectedParityErr:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2x04_STRUCT;

// **** D9F2x44 Register Definition ****
// Address
#define D9F2x44_ADDRESS                                         0x44

// Type
#define D9F2x44_TYPE                                            TYPE_D9F2
// Field Data
#define D9F2x44_PmNxtPtrW_OFFSET                                0
#define D9F2x44_PmNxtPtrW_WIDTH                                 8
#define D9F2x44_PmNxtPtrW_MASK                                  0xff
#define D9F2x44_PcieFlrSupW_OFFSET                              8
#define D9F2x44_PcieFlrSupW_WIDTH                               1
#define D9F2x44_PcieFlrSupW_MASK                                0x100
#define D9F2x44_PciFlrSupW_OFFSET                               9
#define D9F2x44_PciFlrSupW_WIDTH                                1
#define D9F2x44_PciFlrSupW_MASK                                 0x200
#define D9F2x44_PmeSupportW_OFFSET                              10
#define D9F2x44_PmeSupportW_WIDTH                               5
#define D9F2x44_PmeSupportW_MASK                                0x7c00
#define D9F2x44_SetPmeStatus_OFFSET                             15
#define D9F2x44_SetPmeStatus_WIDTH                              1
#define D9F2x44_SetPmeStatus_MASK                               0x8000
#define D9F2x44_DeviceIdW_OFFSET                                16
#define D9F2x44_DeviceIdW_WIDTH                                 16
#define D9F2x44_DeviceIdW_MASK                                  0xffff0000

/// D9F2x44
typedef union {
  struct {                                                              ///<
    UINT32                                                PmNxtPtrW:8 ; ///<
    UINT32                                              PcieFlrSupW:1 ; ///<
    UINT32                                               PciFlrSupW:1 ; ///<
    UINT32                                              PmeSupportW:5 ; ///<
    UINT32                                             SetPmeStatus:1 ; ///<
    UINT32                                                DeviceIdW:16; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2x44_STRUCT;

// **** D9F2x48 Register Definition ****
// Address
#define D9F2x48_ADDRESS                                         0x48

// Type
#define D9F2x48_TYPE                                            TYPE_D9F2
// Field Data
#define D9F2x48_Bar0En_OFFSET                                   0
#define D9F2x48_Bar0En_WIDTH                                    1
#define D9F2x48_Bar0En_MASK                                     0x1
#define D9F2x48_Bar1En_OFFSET                                   1
#define D9F2x48_Bar1En_WIDTH                                    1
#define D9F2x48_Bar1En_MASK                                     0x2
#define D9F2x48_Reserved_4_2_OFFSET                             2
#define D9F2x48_Reserved_4_2_WIDTH                              3
#define D9F2x48_Reserved_4_2_MASK                               0x1c
#define D9F2x48_MsixBarEn_OFFSET                                5
#define D9F2x48_MsixBarEn_WIDTH                                 1
#define D9F2x48_MsixBarEn_MASK                                  0x20
#define D9F2x48_Reserved_8_6_OFFSET                             6
#define D9F2x48_Reserved_8_6_WIDTH                              3
#define D9F2x48_Reserved_8_6_MASK                               0x1c0
#define D9F2x48_Bar1Hide_OFFSET                                 9
#define D9F2x48_Bar1Hide_WIDTH                                  1
#define D9F2x48_Bar1Hide_MASK                                   0x200
#define D9F2x48_Reserved_16_10_OFFSET                           10
#define D9F2x48_Reserved_16_10_WIDTH                            7
#define D9F2x48_Reserved_16_10_MASK                             0x1fc00
#define D9F2x48_Bar1Lock_OFFSET                                 17
#define D9F2x48_Bar1Lock_WIDTH                                  1
#define D9F2x48_Bar1Lock_MASK                                   0x20000
#define D9F2x48_Reserved_31_18_OFFSET                           18
#define D9F2x48_Reserved_31_18_WIDTH                            14
#define D9F2x48_Reserved_31_18_MASK                             0xfffc0000

/// D9F2x48
typedef union {
  struct {                                                              ///<
    UINT32                                                   Bar0En:1 ; ///<
    UINT32                                                   Bar1En:1 ; ///<
    UINT32                                             Reserved_4_2:3 ; ///<
    UINT32                                                MsixBarEn:1 ; ///<
    UINT32                                             Reserved_8_6:3 ; ///<
    UINT32                                                 Bar1Hide:1 ; ///<
    UINT32                                           Reserved_16_10:7 ; ///<
    UINT32                                                 Bar1Lock:1 ; ///<
    UINT32                                           Reserved_31_18:14; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2x48_STRUCT;

// **** D9F2xE8 Register Definition ****
// Address
#define D9F2xE8_ADDRESS                                         0xE8

// **** D9F2xEC_x4A Register Definition ****
// Address
#define D9F2xEC_x4A_ADDRESS                                     0x4A
// Type
#define D9F2xEC_x4A_TYPE                                        TYPE_D9F2xEC

// Field Data
#define D9F2xEC_x4A_Reserved_23_0_OFFSET                         0
#define D9F2xEC_x4A_Reserved_23_0_WIDTH                          24
#define D9F2xEC_x4A_Reserved_23_0_MASK                           0xFFFFFF
#define D9F2xEC_x4A_Reserved_30_24_OFFSET                        24
#define D9F2xEC_x4A_Reserved_30_24_WIDTH                         7
#define D9F2xEC_x4A_Reserved_30_24_MASK                          0x7F000000
#define D9F2xEC_x4A_Reserved_31_31_OFFSET                        31
#define D9F2xEC_x4A_Reserved_31_31_WIDTH                         1
#define D9F2xEC_x4A_Reserved_31_31_MASK                          0x80000000

/// D9F2xEC_x4A
typedef union {
  struct {                                                             ///<
    UINT32                                          Reserved_23_0:24;  ///<
    UINT32                                          Reserved_30_24:7 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;
  UINT32 Value;
} D9F2xEC_x4A_STRUCT;

// **** D9F2xEC_x4C Register Definition ****
// Address
#define D9F2xEC_x4C_ADDRESS                                     0x4C
// Type
#define D9F2xEC_x4C_TYPE                                        TYPE_D9F2xEC

// Field Data
#define D9F2xEC_x4C_Reserved_23_0_OFFSET                         0
#define D9F2xEC_x4C_Reserved_23_0_WIDTH                          24
#define D9F2xEC_x4C_Reserved_23_0_MASK                           0xFFFFFF
#define D9F2xEC_x4C_Reserved_30_24_OFFSET                        24
#define D9F2xEC_x4C_Reserved_30_24_WIDTH                         7
#define D9F2xEC_x4C_Reserved_30_24_MASK                          0x7F000000
#define D9F2xEC_x4C_Reserved_31_31_OFFSET                        31
#define D9F2xEC_x4C_Reserved_31_31_WIDTH                         1
#define D9F2xEC_x4C_Reserved_31_31_MASK                          0x80000000

/// D9F2xEC_x4C
typedef union {
  struct {                                                             ///<
    UINT32                                          Reserved_23_0:24;  ///<
    UINT32                                          Reserved_30_24:7 ; ///<
    UINT32                                          Reserved_31_31:1 ; ///<
  } Field;
  UINT32 Value;
} D9F2xEC_x4C_STRUCT;

// **** D9F2xEC_x50 Register Definition ****
// Address
#define D9F2xEC_x50_ADDRESS                                     0x50
// Type
#define D9F2xEC_x50_TYPE                                        TYPE_D9F2xEC

// **** D9F2xF0 Register Definition ****
// Address
#define D9F2xF0_ADDRESS                                         0xf0

// **** D9F2xF4_x0F Register Definition ****
// Address
#define D9F2xF4_x0F_ADDRESS                                     0xf

// Type
#define D9F2xF4_x0F_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x0F_Bar0MapLock_OFFSET                          0
#define D9F2xF4_x0F_Bar0MapLock_WIDTH                           1
#define D9F2xF4_x0F_Bar0MapLock_MASK                            0x1
#define D9F2xF4_x0F_Bar1MapLock_OFFSET                          1
#define D9F2xF4_x0F_Bar1MapLock_WIDTH                           1
#define D9F2xF4_x0F_Bar1MapLock_MASK                            0x2
#define D9F2xF4_x0F_Reserved_31_2_OFFSET                        2
#define D9F2xF4_x0F_Reserved_31_2_WIDTH                         30
#define D9F2xF4_x0F_Reserved_31_2_MASK                          0xfffffffc

/// D9F2xF4_x0F
typedef union {
  struct {                                                              ///<
    UINT32                                              Bar0MapLock:1 ; ///<
    UINT32                                              Bar1MapLock:1 ; ///<
    UINT32                                            Reserved_31_2:30; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x0F_STRUCT;

// **** D9F2xF4_x10 Register Definition ****
// Address
#define D9F2xF4_x10_ADDRESS                                     0x10

// Type
#define D9F2xF4_x10_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x10_BarMap_OFFSET                               0
#define D9F2xF4_x10_BarMap_WIDTH                                32
#define D9F2xF4_x10_BarMap_MASK                                 0xffffffff

/// D9F2xF4_x10
typedef union {
  struct {                                                              ///<
    UINT32                                                   BarMap:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x10_STRUCT;

// **** D9F2xF4_x11 Register Definition ****
// Address
#define D9F2xF4_x11_ADDRESS                                     0x11

// Type
#define D9F2xF4_x11_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x11_BarMap_OFFSET                               0
#define D9F2xF4_x11_BarMap_WIDTH                                32
#define D9F2xF4_x11_BarMap_MASK                                 0xffffffff

/// D9F2xF4_x11
typedef union {
  struct {                                                              ///<
    UINT32                                                   BarMap:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x11_STRUCT;

// **** D9F2xF4_x12 Register Definition ****
// Address
#define D9F2xF4_x12_ADDRESS                                     0x12

// Type
#define D9F2xF4_x12_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x12_BarMap_OFFSET                               0
#define D9F2xF4_x12_BarMap_WIDTH                                32
#define D9F2xF4_x12_BarMap_MASK                                 0xffffffff

/// D9F2xF4_x12
typedef union {
  struct {                                                              ///<
    UINT32                                                   BarMap:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x12_STRUCT;

// **** D9F2xF4_x13 Register Definition ****
// Address
#define D9F2xF4_x13_ADDRESS                                     0x13

// Type
#define D9F2xF4_x13_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x13_BarMap_OFFSET                               0
#define D9F2xF4_x13_BarMap_WIDTH                                32
#define D9F2xF4_x13_BarMap_MASK                                 0xffffffff

/// D9F2xF4_x13
typedef union {
  struct {                                                              ///<
    UINT32                                                   BarMap:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x13_STRUCT;

// **** D9F2xF4_x20 Register Definition ****
// Address
#define D9F2xF4_x20_ADDRESS                                     0x20

// Type
#define D9F2xF4_x20_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x20_Aper0Lock_OFFSET                            0
#define D9F2xF4_x20_Aper0Lock_WIDTH                             1
#define D9F2xF4_x20_Aper0Lock_MASK                              0x1
#define D9F2xF4_x20_Aper1Lock_OFFSET                            1
#define D9F2xF4_x20_Aper1Lock_WIDTH                             1
#define D9F2xF4_x20_Aper1Lock_MASK                              0x2
#define D9F2xF4_x20_Aper0En_OFFSET                              2
#define D9F2xF4_x20_Aper0En_WIDTH                               1
#define D9F2xF4_x20_Aper0En_MASK                                0x4
#define D9F2xF4_x20_Aper1En_OFFSET                              3
#define D9F2xF4_x20_Aper1En_WIDTH                               1
#define D9F2xF4_x20_Aper1En_MASK                                0x8
#define D9F2xF4_x20_Aper0RoMap_OFFSET                           4
#define D9F2xF4_x20_Aper0RoMap_WIDTH                            2
#define D9F2xF4_x20_Aper0RoMap_MASK                             0x30
#define D9F2xF4_x20_Aper1RoMap_OFFSET                           6
#define D9F2xF4_x20_Aper1RoMap_WIDTH                            2
#define D9F2xF4_x20_Aper1RoMap_MASK                             0xc0
#define D9F2xF4_x20_Aper0NsnoopMap_OFFSET                       8
#define D9F2xF4_x20_Aper0NsnoopMap_WIDTH                        2
#define D9F2xF4_x20_Aper0NsnoopMap_MASK                         0x300
#define D9F2xF4_x20_Reserved_10_10_OFFSET                       10
#define D9F2xF4_x20_Reserved_10_10_WIDTH                        1
#define D9F2xF4_x20_Reserved_10_10_MASK                         0x400
#define D9F2xF4_x20_Aper1NsnoopMap_OFFSET                       11
#define D9F2xF4_x20_Aper1NsnoopMap_WIDTH                        2
#define D9F2xF4_x20_Aper1NsnoopMap_MASK                         0x1800
#define D9F2xF4_x20_Reserved_15_13_OFFSET                       13
#define D9F2xF4_x20_Reserved_15_13_WIDTH                        3
#define D9F2xF4_x20_Reserved_15_13_MASK                         0xe000
#define D9F2xF4_x20_RspbufSize_OFFSET                           16
#define D9F2xF4_x20_RspbufSize_WIDTH                            6
#define D9F2xF4_x20_RspbufSize_MASK                             0x3f0000
#define D9F2xF4_x20_Reserved_31_22_OFFSET                       22
#define D9F2xF4_x20_Reserved_31_22_WIDTH                        10
#define D9F2xF4_x20_Reserved_31_22_MASK                         0xffc00000

/// D9F2xF4_x20
typedef union {
  struct {                                                              ///<
    UINT32                                                Aper0Lock:1 ; ///<
    UINT32                                                Aper1Lock:1 ; ///<
    UINT32                                                  Aper0En:1 ; ///<
    UINT32                                                  Aper1En:1 ; ///<
    UINT32                                               Aper0RoMap:2 ; ///<
    UINT32                                               Aper1RoMap:2 ; ///<
    UINT32                                           Aper0NsnoopMap:2 ; ///<
    UINT32                                           Reserved_10_10:1 ; ///<
    UINT32                                           Aper1NsnoopMap:2 ; ///<
    UINT32                                           Reserved_15_13:3 ; ///<
    UINT32                                               RspbufSize:6 ; ///<
    UINT32                                           Reserved_31_22:10; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x20_STRUCT;

// **** D9F2xF4_x21 Register Definition ****
// Address
#define D9F2xF4_x21_ADDRESS                                     0x21

// Type
#define D9F2xF4_x21_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x21_Pasid_OFFSET                                0
#define D9F2xF4_x21_Pasid_WIDTH                                 24
#define D9F2xF4_x21_Pasid_MASK                                  0xffffff
#define D9F2xF4_x21_PasidEn_OFFSET                              24
#define D9F2xF4_x21_PasidEn_WIDTH                               1
#define D9F2xF4_x21_PasidEn_MASK                                0x1000000
#define D9F2xF4_x21_Reserved_31_25_OFFSET                       25
#define D9F2xF4_x21_Reserved_31_25_WIDTH                        7
#define D9F2xF4_x21_Reserved_31_25_MASK                         0xfe000000

/// D9F2xF4_x21
typedef union {
  struct {                                                              ///<
    UINT32                                                    Pasid:24; ///<
    UINT32                                                  PasidEn:1 ; ///<
    UINT32                                           Reserved_31_25:7 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x21_STRUCT;

// **** D9F2xF4_x28 Register Definition ****
// Address
#define D9F2xF4_x28_ADDRESS                                     0x28

// Type
#define D9F2xF4_x28_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x28_Aper0Base_OFFSET                            0
#define D9F2xF4_x28_Aper0Base_WIDTH                             32
#define D9F2xF4_x28_Aper0Base_MASK                              0xffffffff

/// D9F2xF4_x28
typedef union {
  struct {                                                              ///<
    UINT32                                                Aper0Base:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x28_STRUCT;

// **** D9F2xF4_x29 Register Definition ****
// Address
#define D9F2xF4_x29_ADDRESS                                     0x29

// Type
#define D9F2xF4_x29_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x29_Aper0Base_OFFSET                            0
#define D9F2xF4_x29_Aper0Base_WIDTH                             32
#define D9F2xF4_x29_Aper0Base_MASK                              0xffffffff

/// D9F2xF4_x29
typedef union {
  struct {                                                              ///<
    UINT32                                                Aper0Base:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x29_STRUCT;

// **** D9F2xF4_x2A Register Definition ****
// Address
#define D9F2xF4_x2A_ADDRESS                                     0x2a

// Type
#define D9F2xF4_x2A_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x2A_Aper0Limit_OFFSET                           0
#define D9F2xF4_x2A_Aper0Limit_WIDTH                            32
#define D9F2xF4_x2A_Aper0Limit_MASK                             0xffffffff

/// D9F2xF4_x2A
typedef union {
  struct {                                                              ///<
    UINT32                                               Aper0Limit:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x2A_STRUCT;

// **** D9F2xF4_x2B Register Definition ****
// Address
#define D9F2xF4_x2B_ADDRESS                                     0x2b

// Type
#define D9F2xF4_x2B_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x2B_Aper0Limit_OFFSET                           0
#define D9F2xF4_x2B_Aper0Limit_WIDTH                            32
#define D9F2xF4_x2B_Aper0Limit_MASK                             0xffffffff

/// D9F2xF4_x2B
typedef union {
  struct {                                                              ///<
    UINT32                                               Aper0Limit:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x2B_STRUCT;

// **** D9F2xF4_x2C Register Definition ****
// Address
#define D9F2xF4_x2C_ADDRESS                                     0x2c

// Type
#define D9F2xF4_x2C_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x2C_Aper0Map_OFFSET                             0
#define D9F2xF4_x2C_Aper0Map_WIDTH                              32
#define D9F2xF4_x2C_Aper0Map_MASK                               0xffffffff

/// D9F2xF4_x2C
typedef union {
  struct {                                                              ///<
    UINT32                                                 Aper0Map:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x2C_STRUCT;

// **** D9F2xF4_x2D Register Definition ****
// Address
#define D9F2xF4_x2D_ADDRESS                                     0x2d

// Type
#define D9F2xF4_x2D_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x2D_Aper0Map_OFFSET                             0
#define D9F2xF4_x2D_Aper0Map_WIDTH                              32
#define D9F2xF4_x2D_Aper0Map_MASK                               0xffffffff

/// D9F2xF4_x2D
typedef union {
  struct {                                                              ///<
    UINT32                                                 Aper0Map:32; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x2D_STRUCT;

// **** D9F2xF4_x48 Register Definition ****
// Address
#define D9F2xF4_x48_ADDRESS                                     0x48

// Type
#define D9F2xF4_x48_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x48_InterruptPolarity_OFFSET                    0
#define D9F2xF4_x48_InterruptPolarity_WIDTH                     1
#define D9F2xF4_x48_InterruptPolarity_MASK                      0x1
#define D9F2xF4_x48_Reserved_31_1_OFFSET                        1
#define D9F2xF4_x48_Reserved_31_1_WIDTH                         31
#define D9F2xF4_x48_Reserved_31_1_MASK                          0xfffffffe

/// D9F2xF4_x48
typedef union {
  struct {                                                              ///<
    UINT32                                        InterruptPolarity:1 ; ///<
    UINT32                                            Reserved_31_1:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x48_STRUCT;

// **** D9F2xF4_x49 Register Definition ****
// Address
#define D9F2xF4_x49_ADDRESS                                     0x49

// Type
#define D9F2xF4_x49_TYPE                                        TYPE_D9F2xF4
// Field Data
#define D9F2xF4_x49_InterruptEnable_OFFSET                      0
#define D9F2xF4_x49_InterruptEnable_WIDTH                       1
#define D9F2xF4_x49_InterruptEnable_MASK                        0x1
#define D9F2xF4_x49_Reserved_31_1_OFFSET                        1
#define D9F2xF4_x49_Reserved_31_1_WIDTH                         31
#define D9F2xF4_x49_Reserved_31_1_MASK                          0xfffffffe

/// D9F2xF4_x49
typedef union {
  struct {                                                              ///<
    UINT32                                          InterruptEnable:1 ; ///<
    UINT32                                            Reserved_31_1:31; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D9F2xF4_x49_STRUCT;

// **** D0F0xC0 Register Definition ****
// Address
#define D0F0xC0_ADDRESS                                         0xC0

// **** D0F0xC4_x1 Register Definition ****
// Address
#define D0F0xC4_x1_ADDRESS                                     0x1

// Type
#define D0F0xC4_x1_TYPE                                        TYPE_D0F0xC4
// Field Data
#define D0F0xC4_x1_ParityErrGenGroupSel_OFFSET                 0
#define D0F0xC4_x1_ParityErrGenGroupSel_WIDTH                  8
#define D0F0xC4_x1_ParityErrGenGroupSel_MASK                   0xFF
#define D0F0xC4_x1_ParityErrGenGroupTypeSel_OFFSET             8
#define D0F0xC4_x1_ParityErrGenGroupTypeSel_WIDTH              1
#define D0F0xC4_x1_ParityErrGenGroupTypeSel_MASK               0x100
#define D0F0xC4_x1_Reserved_10_9_OFFSET                        9
#define D0F0xC4_x1_Reserved_10_9_WIDTH                         2
#define D0F0xC4_x1_Reserved_10_9_MASK                          0x600
#define D0F0xC4_x1_ParityErrGenIdSel_OFFSET                    11
#define D0F0xC4_x1_ParityErrGenIdSel_WIDTH                     5
#define D0F0xC4_x1_ParityErrGenIdSel_MASK                      0xF800
#define D0F0xC4_x1_ParityErrGenCmd_OFFSET                      16
#define D0F0xC4_x1_ParityErrGenCmd_WIDTH                       3
#define D0F0xC4_x1_ParityErrGenCmd_MASK                        0x70000
#define D0F0xC4_x1_Reserved_29_19_OFFSET                       19
#define D0F0xC4_x1_Reserved_29_19_WIDTH                        11
#define D0F0xC4_x1_Reserved_29_19_MASK                         0x3FF80000
#define D0F0xC4_x1_ParityErrGenTrigger_OFFSET                  30
#define D0F0xC4_x1_ParityErrGenTrigger_WIDTH                   1
#define D0F0xC4_x1_ParityErrGenTrigger_MASK                    0x40000000
#define D0F0xC4_x1_ParityErrGenInjectAllow_OFFSET              31
#define D0F0xC4_x1_ParityErrGenInjectAllow_WIDTH               1
#define D0F0xC4_x1_ParityErrGenInjectAllow_MASK                0x80000000

/// D0F0xC4_x1
typedef union {
  struct {                                                              ///<
    UINT32                                     ParityErrGenGroupSel:8 ; ///<
    UINT32                                 ParityErrGenGroupTypeSel:1 ; ///<
    UINT32                                            Reserved_10_9:2 ; ///<
    UINT32                                        ParityErrGenIdSel:5 ; ///<
    UINT32                                          ParityErrGenCmd:3 ; ///<
    UINT32                                           Reserved_29_19:11; ///<
    UINT32                                      ParityErrGenTrigger:1 ; ///<
    UINT32                                  ParityErrGenInjectAllow:1 ; ///<
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} D0F0xC4_x1_STRUCT;

#endif

