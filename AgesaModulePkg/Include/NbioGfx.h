/* $NoKeywords:$ */
/**
 * @file
 *
 * Initialize GFX configuration data structure.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
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

#ifndef _NBIOGFX_H_
#define _NBIOGFX_H_

#include <AGESA.h>
#include <Gnb.h>
//
// Assume standard IA-32 alignment.
// BugBug: Need to check portability of long long
//
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef unsigned short      uint16_t;
typedef short               int16_t;
typedef unsigned char       uint8_t;
typedef signed char         int8_t;

#define DEVICE_DFP                                0x1
#define DEVICE_CRT                                0x2
#define DEVICE_LCD                                0x3


#define CONNECTOR_DISPLAYPORT_ENUM                0x3013
#define CONNECTOR_HDMI_TYPE_A_ENUM                0x300c
#define CONNECTOR_SINGLE_LINK_DVI_D_ENUM          0x3003
#define CONNECTOR_DUAL_LINK_DVI_D_ENUM            0x3004
#define CONNECTOR_SINGLE_LINK_DVI_I_ENUM          0x3001
#define CONNECTOR_DUAL_LINK_DVI_I_ENUM            0x3002
#define CONNECTOR_VGA_ENUM                        0x3005
#define CONNECTOR_LVDS_ENUM                       0x300E
#define CONNECTOR_eDP_ENUM                        0x3014
#define CONNECTOR_LVDS_eDP_ENUM                   0x3016
//DP to VGA:
#define ENCODER_DP2VGA_ENUM_ID1                   0x2123
//DP to LVDS:
#define ENCODER_DP2LVDS_ENUM_ID2                  0x2223
//Hudson-2 NutMeg DP to VGA:
#define ENCODER_ALMOND_ENUM_ID1                   0x2122
#define ENCODER_NOT_PRESENT                       0x0000

// no eDP->LVDS translator chip
#define eDP_TO_LVDS_RX_DISABLE                    0x00
// common eDP->LVDS translator chip without AMD SW init
#define eDP_TO_LVDS_COMMON_ID                     0x01
// Third party translator which requires AMD SW init
#define eDP_TO_LVDS_SWINIT_ID                     0x02


#define ATOM_DEVICE_CRT1_SUPPORT                  0x0001
#define ATOM_DEVICE_DFP1_SUPPORT                  0x0008
#define ATOM_DEVICE_DFP6_SUPPORT                  0x0040
#define ATOM_DEVICE_DFP2_SUPPORT                  0x0080
#define ATOM_DEVICE_DFP3_SUPPORT                  0x0200
#define ATOM_DEVICE_DFP4_SUPPORT                  0x0400
#define ATOM_DEVICE_DFP5_SUPPORT                  0x0800
#define ATOM_DEVICE_LCD1_SUPPORT                  0x0002
#pragma pack(push, 1)
/// Graphics card information structure

/// dpphy_override
typedef enum {
  ATOM_ENABLE_DVI_TUNINGSET   = 0x01,        ///<
  ATOM_ENABLE_HDMI_TUNINGSET  = 0x02,        ///<
  ATOM_ENABLE_HDMI6G_TUNINGSET  = 0x04,      ///<
  ATOM_ENABLE_DP_TUNINGSET  = 0x08,          ///<
  ATOM_ENABLE_DP_HBR3_TUNINGSET  = 0x10,     ///<
  ATOM_ENABLE_DP_HBR_TUNINGSET  = 0x20,      ///<
  ATOM_ENABLE_DP_HBR2_TUNINGSET  = 0x40,     ///<
  ATOM_ENABLE_EDP_TUNINGSET  = 0x80,         ///<
} ATOM_SYSINFO_DPPHY_OVERRIDE;               ///<

typedef UINT32 ULONG;
typedef UINT16 USHORT;
typedef UINT8  UCHAR;

/// Driver interface header structure
typedef struct _ATOM_COMMON_TABLE_HEADER {
  USHORT                      usStructureSize;             ///< Structure size
  UCHAR                       ucTableFormatRevision;       ///< Format revision number
  UCHAR                       ucTableContentRevision;      ///< Contents revision number
} ATOM_COMMON_TABLE_HEADER;

/// IntegrateSystemInfoTable is used for Raven APU


//
// Camera Info (9.10)
//
typedef struct _atom_camera_dphy_timing_param
{
  uint8_t  profile_id;       // SENSOR_PROFILES
  uint32_t param;            //<
} ATOM_CAMERA_DPHY_TIMING_PARAM;

typedef struct _atom_camera_dphy_elec_param {
  uint16_t param[3];
} ATOM_CAMERA_DPHY_ELEC_PARAM;

typedef struct _atom_camera_module_info {
  uint8_t module_id;                    // 0: Rear, 1: Front right of user, 2: Front left of user
  uint8_t module_name[8];               ///<
  ATOM_CAMERA_DPHY_TIMING_PARAM timingparam[6]; // Exact number is under estimation and confirmation from sensor vendor
} ATOM_CAMERA_MODULE_INFO;

typedef struct _atom_camera_flashlight_info {
  uint8_t flashlight_id;                // 0: Rear, 1: Front
  uint8_t flashlight_name[8];           ///<
} ATOM_CAMERA_FLASHLIGHT_INFO;

typedef struct _atom_camera_data {
  uint32_t versionCode;
  ATOM_CAMERA_MODULE_INFO cameraInfo[3];      // Assuming 3 camera sensors max
  ATOM_CAMERA_FLASHLIGHT_INFO flashInfo;      // Assuming 1 flashlight max
  ATOM_CAMERA_DPHY_ELEC_PARAM dphy_param;
  uint32_t crc_val;         // CRC
} ATOM_CAMERA_DATA;

typedef struct _atom_i2c_reg_info {
  uint8_t ucI2cRegIndex;         ///<
  uint8_t ucI2cRegVal;           ///<
} atom_i2c_reg_info;

typedef struct _atom_hdmi_retimer_redriver_set {
  uint8_t HdmiSlvAddr;                        ///<
  uint8_t HdmiRegNum;                         ///<
  uint8_t Hdmi6GRegNum;                       ///<
  atom_i2c_reg_info HdmiRegSetting[9];        ///<
  atom_i2c_reg_info Hdmi6GhzRegSetting[3];    ///<
} atom_hdmi_retimer_redriver_set;

//
// 14nm display PHY HDMI/DVI setting override (9.11)
//

typedef struct _atom_14nm_dpphy_dvihdmi_tuningset {
  uint32_t max_symclk_in10khz;
  uint8_t encoder_mode;            //atom_encode_mode_def, =2: DVI, =3: HDMI mode
  uint8_t phy_sel;                 //bit vector of phy, bit0= phya, bit1=phyb, ....bit5 = phyf
  uint16_t margindeemph;           //COMMON_MAR_DEEMPH_NOM[7:0]tx_margin_nom [15:8]deemph_gen1_nom
  uint8_t deemph_6db_4;            //COMMON_SELDEEMPH60[31:24]deemph_6db_4
  uint8_t boostadj;                //CMD_BUS_GLOBAL_FOR_TX_LANE0 [19:16]tx_boost_adj  [20]tx_boost_en  [23:22]tx_binary_ron_code_offset
  uint8_t tx_driver_fifty_ohms;    //COMMON_ZCALCODE_CTRL[21].tx_driver_fifty_ohms
  uint8_t deemph_sel;              //MARGIN_DEEMPH_LANE0.DEEMPH_SEL
} ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET;


typedef struct _atom_14nm_dpphy_dp_setting {
  uint8_t dp_vs_pemph_level;       //enum of atom_dp_vs_preemph_def
  uint16_t margindeemph;           //COMMON_MAR_DEEMPH_NOM[7:0]tx_margin_nom [15:8]deemph_gen1_nom
  uint8_t deemph_6db_4;            //COMMON_SELDEEMPH60[31:24]deemph_6db_4
  uint8_t boostadj;                //CMD_BUS_GLOBAL_FOR_TX_LANE0 [19:16]tx_boost_adj  [20]tx_boost_en  [23:22]tx_binary_ron_code_offset
} ATOM_14NM_DPPHY_DP_SETTING;


typedef struct _atom_14nm_dpphy_dp_tuningset {
  uint8_t phy_sel;                 // bit vector of phy, bit0= phya, bit1=phyb, ....bit5 = phyf
  uint8_t version;                 ///<
  uint16_t table_size;             // size of atom_14nm_dpphy_dp_tuningset
  uint16_t reserved;
  ATOM_14NM_DPPHY_DP_SETTING dptuning[10];
} ATOM_14NM_DPPHY_DP_TUNINGSET;

/// Link ping mapping for DP/eDP/LVDS
typedef struct _ATOM_DP_CONN_CHANNEL_MAPPING {
  UCHAR ucDP_Lane0_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane0, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDP_Lane1_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane1, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDP_Lane2_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane2, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDP_Lane3_Source  :2;                      ///< Define which pin connect to DP connector DP_Lane3, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
} ATOM_DP_CONN_CHANNEL_MAPPING;

/// Link ping mapping for DVI/HDMI
typedef struct _ATOM_DVI_CONN_CHANNEL_MAPPING {
  UCHAR ucDVI_DATA2_Source  :2;                     ///< Define which pin connect to DVI connector data Lane2, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDVI_DATA1_Source  :2;                     ///< Define which pin connect to DVI connector data Lane1, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDVI_DATA0_Source  :2;                     ///< Define which pin connect to DVI connector data Lane0, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
  UCHAR ucDVI_CLK_Source    :2;                     ///< Define which pin connect to DVI connector clock lane, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
} ATOM_DVI_CONN_CHANNEL_MAPPING;

/// External Display Path
typedef struct _EXT_DISPLAY_PATH {
  USHORT                      usDeviceTag;          ///< A bit vector to show what devices are supported
  USHORT                      usDeviceACPIEnum;     ///< 16bit device ACPI id.
  USHORT                      usDeviceConnector;    ///< A physical connector for displays to plug in, using object connector definitions
  UCHAR                       ucExtAUXDDCLutIndex;  ///< An index into external AUX/DDC channel LUT
  UCHAR                       ucExtHPDPINLutIndex;  ///< An index into external HPD pin LUT
  USHORT                      usExtEncoderObjId;    ///< external encoder object id
  union {                                           ///< Lane mapping
    UCHAR                     ucChannelMapping;     ///< lane mapping on connector (ucChannelMapping=0 use default)
    ATOM_DP_CONN_CHANNEL_MAPPING  asDPMapping;      ///< lane mapping on connector (ucChannelMapping=0 use default)
    ATOM_DVI_CONN_CHANNEL_MAPPING asDVIMapping;     ///< lane mapping on connector (ucChannelMapping=0 use default)
  } ChannelMapping;
  UCHAR                       ucChPNInvert;         ///< Bit vector for up to 8 lanes. 0: P and N is not invert, 1: P and N is inverted
  USHORT                      usCaps;               ///< Capabilities IF BIT[0] == 1, downgrade phy link to DP1.1
  USHORT                      usReserved;           ///< Reserved
} EXT_DISPLAY_PATH;

/// External Display Connection Information
typedef  struct _ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO {
  ATOM_COMMON_TABLE_HEADER    sHeader;              ///< Standard Header
  UCHAR                       ucGuid [16];          ///< Guid
  EXT_DISPLAY_PATH            sPath[7];             ///< External Display Path
  UCHAR                       ucChecksum;           ///< Checksum
  UCHAR                       uc3DStereoPinId;      ///< 3D Stereo Pin ID
  UCHAR                       ucRemoteDisplayConfig;   ///< Bit0=1:Enable Wireless Display through APU VCE HW function
  UCHAR                       uceDPToLVDSRxId;      ///< 3rd party eDP to LVDS translator chip presented. 0:no, 1:chip without AMD SW init, 2:Third party translator which require AMD SW init
  UCHAR                       ucFixDPVoltageSwing;  ///< The value match DPCD register DPx_LANE_SET defined in DP spec
  UCHAR                       Reserved [3];         ///< Reserved
} ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO;

typedef struct _atom_integrated_system_info_v1_11
{
  ATOM_COMMON_TABLE_HEADER  table_header;
  UINT32  vbios_misc;                       //enum of atom_system_vbiosmisc_def
  UINT32  gpucapinfo;                       //enum of atom_system_gpucapinf_def
  UINT32  system_config;
  UINT32  cpucapinfo;
  uint16_t  gpuclk_ss_percentage;             //unit of 0.001%,   1000 mean 1%
  uint16_t  gpuclk_ss_type;
  uint16_t  lvds_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  uint16_t  lvds_ss_rate_10hz;
  uint16_t  hdmi_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  uint16_t  hdmi_ss_rate_10hz;
  uint16_t  dvi_ss_percentage;                //unit of 0.001%,   1000 mean 1%
  uint16_t  dvi_ss_rate_10hz;
  uint16_t  dpphy_override;                   // bit vector, enum of atom_sysinfo_dpphy_override_def
  uint16_t  lvds_misc;                        // enum of atom_sys_info_lvds_misc_def
  uint16_t  backlight_pwm_hz;                 // pwm frequency in hz
  uint8_t   memorytype;                       // enum of atom_sys_mem_type
  uint8_t   umachannelnumber;                 // number of memory channels
  uint8_t   pwr_on_digon_to_de;               /* all pwr sequence numbers below are in uint of 4ms */
  uint8_t   pwr_on_de_to_vary_bl;
  uint8_t   pwr_down_vary_bloff_to_de;
  uint8_t   pwr_down_de_to_digoff;
  uint8_t   pwr_off_delay;
  uint8_t   pwr_on_vary_bl_to_blon;
  uint8_t   pwr_down_bloff_to_vary_bloff;
  uint8_t   min_allowed_bl_level;
  uint8_t   htc_hyst_limit;
  uint8_t   htc_tmp_limit;
  uint8_t   reserved1;
  uint8_t   reserved2;
  ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO extdispconninfo;
  ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET dvi_tuningset;
  ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET hdmi_tuningset;
  ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET hdmi6g_tuningset;
  ATOM_14NM_DPPHY_DP_TUNINGSET dp_tuningset;
  ATOM_14NM_DPPHY_DP_TUNINGSET dp_hbr3_tuningset;
  ATOM_CAMERA_DATA  camera_info;
  atom_hdmi_retimer_redriver_set dp0_retimer_redriver_set;
  atom_hdmi_retimer_redriver_set dp1_retimer_redriver_set;
  atom_hdmi_retimer_redriver_set dp2_retimer_redriver_set;
  atom_hdmi_retimer_redriver_set dp3_retimer_redriver_set;
  ATOM_14NM_DPPHY_DP_TUNINGSET dp_hbr_tuningset;    //hbr 2.7G dp tuning set
  ATOM_14NM_DPPHY_DP_TUNINGSET dp_hbr2_tuningset;   //hbr2 5.4G dp turnig set
  ATOM_14NM_DPPHY_DP_TUNINGSET edp_tuningset;       //edp tuning set
  uint32_t  reserved[66];
} ATOM_INTEGRATED_SYSTEM_INFO_V1_11;


/// this Table is used for Carrizo APU
typedef struct _ATOM_FUSION_SYSTEM_INFO_V9 {
  ATOM_INTEGRATED_SYSTEM_INFO_V1_11  sIntegratedSysInfo;      ///< Refer to ATOM_INTEGRATED_SYSTEM_INFO_V1_11 definition.
  ULONG                             ulPowerplayTable[256];    ///< This 512 bytes memory is used to save ATOM_PPLIB_POWERPLAYTABLE5, starting form ulPowerplayTable[0]
} ATOM_FUSION_SYSTEM_INFO_V9;

#pragma pack(pop)



#define GNB_SBDFO MAKE_SBDFO(0, 0, 0, 0, 0)

/// Define configuration values for ulGPUCapInfo
// BIT[0] - TMDS/HDMI Coherent Mode 0: use cascade PLL mode, 1: use single PLL mode.
#define GPUCAPINFO_TMDS_HDMI_USE_CASCADE_PLL_MODE      0x00ul
#define GPUCAPINFO_TMDS_HDMI_USE_SINGLE_PLL_MODE       0x01ul

// BIT[1] - DP mode 0: use cascade PLL mode, 1: use single PLL mode
#define GPUCAPINFO_DP_MODE_USE_CASCADE_PLL_MODE        0x00ul
#define GPUCAPINFO_DP_USE_SINGLE_PLL_MODE              0x02ul

// BIT[3] - AUX HW mode detection logic 0: Enable, 1: Disable
#define GPUCAPINFO_AUX_HW_MODE_DETECTION_ENABLE        0x00ul
#define GPUCAPINFO_AUX_HW_MODE_DETECTION_DISABLE       0x08ul

// BIT[4] - DFS bypass 0: Disable, 1: Enable
#define GPUCAPINFO_DFS_BYPASS_DISABLE       0x00ul
#define GPUCAPINFO_DFS_BYPASS_ENABLE        0x10ul
#define GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT  0x20ul

// BIT[16]=1 indicate SMC firmware is able to support GNB fast resume function
#define GPUCAPS__GNB_FAST_RESUME_CAPABLE    0x10000ul

// BIT[17] - Enable battery boost feature 0: Disable, 1: Enable
#define GPUCAPINFO_BATTERY_BOOST_ENABLE       0x20000ul

#endif

