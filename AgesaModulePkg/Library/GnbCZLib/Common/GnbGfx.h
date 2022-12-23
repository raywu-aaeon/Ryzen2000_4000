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
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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

#ifndef _GNBGFX_H_
#define _GNBGFX_H_

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
typedef struct {
  UINT32   AmdPcieGfxCardBitmap;                  ///< AMD PCIE graphics card information
  UINT32   PcieGfxCardBitmap;                     ///< All PCIE graphics card information
  UINT32   PciGfxCardBitmap;                      ///< All PCI graphics card information
} GFX_CARD_CARD_INFO;

/// UMA Steering to either Garlic bus or Enum bus
typedef enum {
  iGpuVgaAdapter,                                       ///< Configure iGPU as VGA adapter
  iGpuVgaNonAdapter                                     ///< Configure iGPU as non VGA adapter
} GFX_IGPU_VGA_MODE;

/// UMA Steering Mode
typedef enum {
  DefaultGarlic,                                        ///< Default garlic except system snooped to onion
  SystemTrafficOnion,                                   ///< System traffic to onion
  Onion,                                                ///< Onion
  Garlic,                                               ///< Garlic
} UMA_STEERING;

/// User Options
typedef enum {
  OptionDisabled,                                       ///< Disabled
  OptionEnabled                                         ///< Enabled
} CONTROL_OPTION;

/// GFX enable Policy
typedef enum {
  GmcPowerGatingDisabled,                               ///< Disable Power gating
  GmcPowerGatingStutterOnly,                            ///< GMC Stutter Only mode
  GmcPowerGatingWithStutter                            ///< GMC Power gating with Stutter mode
} GMC_POWER_GATING;

/// Internal GFX mode
typedef enum {
  GfxControllerLegacyBridgeMode,                        ///< APC bridge Legacy mode
  GfxControllerPcieEndpointMode,                        ///< IGFX PCIE Bus 0, Device 1
} GFX_CONTROLLER_MODE;

/// Graphics Platform Configuration
typedef struct {
  PVOID                       StdHeader;                ///< Standard Header
  PCI_ADDR                    GfxPciAddress;            ///< Graphics PCI Address
  UMA_INFO                    UmaInfo;                  ///< UMA Information
  UINT64                      GmmBase;                  ///< GMM Base
  UINT8                       GnbHdAudio;               ///< Control GFX HD Audio controller(Used for HDMI and DP display output),
                                                        ///< essentially it enables function 1 of graphics device.
                                                        ///< @li 0 = HD Audio disable
                                                        ///< @li 1 = HD Audio enable
  UINT8                       AbmSupport;               ///< Automatic adjust LVDS/eDP Back light level support.It is
                                                        ///< characteristic specific to display panel which used by platform design.
                                                        ///< @li 0 = ABM support disabled
                                                        ///< @li 1 = ABM support enabled
  UINT8                       DynamicRefreshRate;       ///< Adjust refresh rate on LVDS/eDP.
  UINT16                      LcdBackLightControl;      ///< The PWM frequency to LCD backlight control.
                                                        ///< If equal to 0 backlight not controlled by iGPU.
  UINT32                      AmdPlatformType;          ///< Platform type
  UMA_STEERING                UmaSteering;              ///< UMA Steering
  GFX_IGPU_VGA_MODE           iGpuVgaMode;              ///< iGPU VGA mode
  BOOLEAN                     GmcClockGating;           ///< Clock gating
  BOOLEAN                     GmcLockRegisters;         ///< GmcLock Registers
  BOOLEAN                     GfxFusedOff;              ///< Record if GFX is fused off.
  GMC_POWER_GATING            GmcPowerGating;           ///< Gmc Power Gating.
  UINT8                       Gnb3dStereoPinIndex;      ///< 3D Stereo Pin ID
  GFX_CONTROLLER_MODE         GfxControllerMode;        ///< Gfx controller mode
  UINT16                      LvdsSpreadSpectrum;       ///< Spread spectrum value in 0.01 %
  UINT16                      LvdsSpreadSpectrumRate;   ///< Spread spectrum frequency used by SS hardware logic in unit of 10Hz, 0 - default frequency 40kHz
  UINT8                       LvdsPowerOnSeqDigonToDe;    ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqDeToVaryBl;   ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqDeToDigon;    ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqVaryBlToDe;   ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqOnToOffDelay; ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqVaryBlToBlon; ///< Panel initialization timing.
  UINT8                       LvdsPowerOnSeqBlonToVaryBl; ///< Panel initialization timing.
  UINT16                      LvdsMaxPixelClockFreq;      ///< The maximum pixel clock frequency supported.
  UINT32                      LcdBitDepthControlValue;    ///< The LCD bit depth control settings.
  UINT8                       Lvds24bbpPanelMode;         ///< The LVDS 24 BBP mode.
  LVDS_MISC_CONTROL           LvdsMiscControl;            ///< THe LVDS swap/Hsync/Vsync/BLON/Volt-overwrite control
  GFX_CARD_CARD_INFO          GfxDiscreteCardInfo;        ///< Discrete GFX card info
  UINT16                      PcieRefClkSpreadSpectrum;   ///< Spread spectrum value in 0.01 %
  BOOLEAN                     GnbRemoteDisplaySupport;    ///< Wireless Display Enable
  UINT8                       LVDSVoltAdjust;             ///< when ucLVDSMisc[5]=1, then this value will be programmed to register LVDS_CTRL_4 to adjust LVDS output voltage
  DISPLAY_MISC_CONTROL        DisplayMiscControl;         ///< The Display misc control
  DP_FIXED_VOLT_SWING_TYPE    DpFixedVoltSwingType;       ///< To indicate fixed voltage swing value
  UINT8                       MinAllowedBLLevel;          ///< Minimum allowed LCD backlight level
  UINT8                       EDPv1_4VSMode;              ///< eDP 1.4 VSMode
  UINT8                       ExtHDMIReDrvSlvAddr;        ///< address of re-driver/re-timer chip
  UINT8                       ExtHDMIReDrvRegNum;         ///< number of register/value
  UINT64                      ExtHDMIRegSetting;          ///< list of register/value
  UINT8                       DP0ExtHDMIReDrvSlvAddr;     ///< address of re-driver/re-timer chip
  UINT8                       DP0ExtHDMIReDrvRegNum;      ///< number of register/value
  UINT64                      DP0ExtHDMIRegSetting;       ///< list of register/value
  UINT8                       DP1ExtHDMIReDrvSlvAddr;     ///< address of re-driver/re-timer chip
  UINT8                       DP1ExtHDMIReDrvRegNum;      ///< number of register/value
  UINT64                      DP1ExtHDMIRegSetting;       ///< list of register/value
  UINT8                       DP2ExtHDMIReDrvSlvAddr;     ///< address of re-driver/re-timer chip
  UINT8                       DP2ExtHDMIReDrvRegNum;      ///< number of register/value
  UINT64                      DP2ExtHDMIRegSetting;       ///< list of register/value
  UINT8                       DP0ExtHDMI6GRegNum;         ///< number of register/value
  UINT64                      DP0ExtHDMI6GhzRegSetting;   ///< list of register/value
  UINT8                       DP1ExtHDMI6GRegNum;         ///< number of register/value
  UINT64                      DP1ExtHDMI6GhzRegSetting;   ///< list of register/value
  UINT8                       DP2ExtHDMI6GRegNum;         ///< number of register/value
  UINT64                      DP2ExtHDMI6GhzRegSetting;   ///< list of register/value
  UINT16                      BootUpDisplayDevice;        ///< Boot up display device
} GFX_PLATFORM_CONFIG;


typedef UINT32 ULONG;
typedef UINT16 USHORT;
typedef UINT8  UCHAR;

/// Driver interface header structure
typedef struct _ATOM_COMMON_TABLE_HEADER {
  USHORT                      usStructureSize;             ///< Structure size
  UCHAR                       ucTableFormatRevision;       ///< Format revision number
  UCHAR                       ucTableContentRevision;      ///< Contents revision number
} ATOM_COMMON_TABLE_HEADER;

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

/// DispClk to VID relation table
typedef struct _ATOM_CLK_VOLT_CAPABILITY {
  ULONG                       ulVoltageIndex;       ///< The Voltage Index indicated by FUSE, same voltage index shared with SCLK DPM fuse table
  ULONG                       ulMaximumSupportedCLK;///< Maximum clock supported with specified voltage index, unit in 10kHz
} ATOM_CLK_VOLT_CAPABILITY;

/// Available Sclk table
typedef struct _ATOM_AVAILABLE_SCLK_LIST {
  ULONG                        ulSupportedSCLK;     ///< Maximum clock supported with specified voltage index,  unit in 10kHz
  USHORT                       usVoltageIndex;      ///< The Voltage Index indicated by FUSE for specified SCLK
  USHORT                       usVoltageID;         ///< The Voltage ID indicated by FUSE for specified SCLK
} ATOM_AVAILABLE_SCLK_LIST;

/// TDP Configuration Bitfields
typedef struct _ATOM_TDP_CONFIG_BITS {
  UINT32                       uCTDP_Enable:2;      ///< = (uCTDP_Value > uTDP_Value? 2: (uCTDP_Value < uTDP_Value))
  UINT32                       uCTDP_Value:14;      ///< Override value in tens of milli watts
  UINT32                       uTDP_Value:14;       ///< Original TDP value in tens of milli watts
  UINT32                       uReserved:2;         ///< Reserved
} ATOM_TDP_CONFIG_BITS;

/// TDP Configuration Union
typedef union _ATOM_TDP_CONFIG {
  ATOM_TDP_CONFIG_BITS         TDP_config;          ///< Field-wise access
  ULONG                        TDP_config_all;      ///< Access to all
} ATOM_TDP_CONFIG;

/// Clock Voltage Capability
typedef struct _ATOM_CLK_VOLT_CAPABILITY_V2 {
  USHORT     usVoltageLevel;                      ///< The real Voltage Level round up value in unit of mv
  ULONG      ulMaximumSupportedCLK;               ///< Maximum clock supported with specified voltage index, unit in 10kHz
} ATOM_CLK_VOLT_CAPABILITY_V2;

/// HDMI re-driver register information
typedef struct _ATOM_I2C_REG_INFO {
  UCHAR ucI2cRegIndex;                              ///< HDMI re-driver Register Index
  UCHAR ucI2cRegVal;                                ///< HDMI re-driver Register Value
} ATOM_I2C_REG_INFO;

/// IntegrateSystemInfoTable is used for Czrrizo APU
typedef struct _ATOM_INTEGRATED_SYSTEM_INFO_V1_9 {
  ATOM_COMMON_TABLE_HEADER    sHeader;                            ///<
  ULONG                       ulBootUpEngineClock;                ///<
  ULONG                       ulDentistVCOFreq;                   ///<
  ULONG                       ulBootUpUMAClock;                   ///<
  ATOM_CLK_VOLT_CAPABILITY    sDISPCLK_Voltage[4];                ///< * no longer used, keep it as is to avoid driver compiling error
  ULONG                       ulBootUpReqDisplayVector;           ///<
  ULONG                       ulVBIOSMisc;                        ///<
  ULONG                       ulGPUCapInfo;                       ///<
  ULONG                       ulDISP_CLK2Freq;                    ///< *
  USHORT                      usRequestedPWMFreqInHz;             ///<
  UCHAR                       ucHtcTmpLmt;                        ///<
  UCHAR                       ucHtcHystLmt;                       ///<
  ULONG                       ulReserved2;                        ///<
  ULONG                       ulSystemConfig;                     ///<
  ULONG                       ulCPUCapInfo;                       ///<
  ULONG                       ulReserved3;                        ///<
  USHORT                      usGPUReservedSysMemSize;            ///<
  USHORT                      usExtDispConnInfoOffset;            ///<
  USHORT                      usPanelRefreshRateRange;            ///<
  UCHAR                       ucMemoryType;                       ///<
  UCHAR                       ucUMAChannelNumber;                 ///<
  //UCHAR                       strVBIOSMsg[40];                  ///<
  UCHAR                       ucDP0_ExtHdmiSlvAddr;               ///< * retimer redriver
  UCHAR                       ucDP0_ExtHdmiRegNum;                ///< * retimer redriver
  ATOM_I2C_REG_INFO           asDP0_ExtHdmiRegSetting[9];         ///< * retimer redriver
  UCHAR                       ucDP1_ExtHdmiSlvAddr;               ///< * retimer redriver
  UCHAR                       ucDP1_ExtHdmiRegNum;                ///< * retimer redriver
  ATOM_I2C_REG_INFO           asDP1_ExtHdmiRegSetting[9];         ///< * retimer redriver
  ATOM_TDP_CONFIG             asTdpConfig;                        ///< *
  //UCHAR                       ucExtHDMIReDrvSlvAddr;            ///< *
  //UCHAR                       ucExtHDMIReDrvRegNum;             ///< *
  //ATOM_I2C_REG_INFO           asExtHDMIRegSetting[9];           ///< *
  union {
  UCHAR                       ucExtHDMIReDrvSlvAddr;              ///< * retimer redriver
  UCHAR                       ucDP2_ExtHdmiSlvAddr;               ///< * retimer redriver
  }ucReDrvSlvAddr;
  union {
  UCHAR                       ucExtHDMIReDrvRegNum;               ///< * retimer redriver
  UCHAR                       ucDP2_ExtHdmiRegNum;                ///< * retimer redriver
  }UcReDrvRegNum;
  union {
  ATOM_I2C_REG_INFO           asExtHDMIRegSetting[9];             ///< * retimer redriver
  ATOM_I2C_REG_INFO           asDP2_ExtHdmiRegSetting[9];         ///< * retimer redriver
  }asReDrvRegSetting;
  // ULONG                       ulReserved[2];                   ///< *
  ATOM_I2C_REG_INFO           asDP0_ExtHdmi6GhzRegSetting[3];     ///< * retimer redriver
  UCHAR                       ucDP0_ExtHDMI6GRegNum;              ///< * retimer redriver
  UCHAR                       ucDP1_ExtHDMI6GRegNum;              ///< * retimer redriver
  ATOM_CLK_VOLT_CAPABILITY_V2 sDispClkVoltageMapping[8];          ///< *
  ATOM_AVAILABLE_SCLK_LIST    sAvail_SCLK[5];                     ///< * no longer used, keep it as is to avoid driver compiling error
  ULONG                       ulGMCRestoreResetTime;              ///<
  ULONG                       ulReserved4;                        ///<
  ULONG                       ulIdleNClk;                         ///<
  ULONG                       ulDDR_DLL_PowerUpTime;              ///<
  ULONG                       ulDDR_PLL_PowerUpTime;              ///<
  USHORT                      usPCIEClkSSPercentage;              ///<
  USHORT                      usPCIEClkSSType;                    ///<
  USHORT                      usLvdsSSPercentage;                 ///<
  USHORT                      usLvdsSSpreadRateIn10Hz;            ///<
  USHORT                      usHDMISSPercentage;                 ///<
  USHORT                      usHDMISSpreadRateIn10Hz;            ///<
  USHORT                      usDVISSPercentage;                  ///<
  USHORT                      usDVISSpreadRateIn10Hz;             ///<
  ULONG                       ulGPUReservedSysMemBaseAddrLo;      ///<
  ULONG                       ulGPUReservedSysMemBaseAddrHi;      ///<
  //ULONG                       ulReserved5[3];                   ///< *
  ATOM_I2C_REG_INFO           asDP1_ExtHdmi6GhzRegSetting[3];     ///< * retimer redriver
  ATOM_I2C_REG_INFO           asDP2_ExtHdmi6GhzRegSetting[3];     ///< * retimer redriver
  USHORT                      usMaxLVDSPclkFreqInSingleLink;      ///<
  UCHAR                       ucLvdsMisc;                         ///<
  UCHAR                       ucLVDSVoltAdjust;                   ///<
  UCHAR                       ucLVDSPwrOnSeqDIGONtoDE_in4Ms;      ///<
  UCHAR                       ucLVDSPwrOnSeqDEtoVARY_BL_in4Ms;    ///<
  UCHAR                       ucLVDSPwrOffSeqVARY_BLtoDE_in4Ms;   ///<
  UCHAR                       ucLVDSPwrOffSeqDEtoDIGON_in4Ms;     ///<
  UCHAR                       ucLVDSOffToOnDelay_in4Ms;           ///<
  UCHAR                       ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms;  ///<
  UCHAR                       ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms; ///<
  UCHAR                       ucMinAllowedBL_Level;               ///<
  ULONG                       ulLCDBitDepthControlVal;            ///<
  ULONG                       ulNbpStateMemclkFreq[4];            ///< * only 2 level is changed.
  ULONG                       ulPSPVersion;                       ///< *
  ULONG                       ulNbpStateNClkFreq[4];              ///<
  USHORT                      usNBPStateVoltage[4];               ///<
  USHORT                      usBootUpNBVoltage;                  ///<
  UCHAR                       ucEDPv1_4VSMode;                    ///< *
  //UCHAR                       ucReserved2;                      ///< *
  UCHAR                       ucDP2_ExtHDMI6GRegNum;              ///< * retimer redriver
  ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO sExtDispConnInfo;         ///<
} ATOM_INTEGRATED_SYSTEM_INFO_V1_9;
#pragma pack(pop)

/// this Table is used for Carrizo APU
typedef struct _ATOM_FUSION_SYSTEM_INFO_V5 {
  ATOM_INTEGRATED_SYSTEM_INFO_V1_9  sIntegratedSysInfo;      ///< Refer to ATOM_INTEGRATED_SYSTEM_INFO_V1_9 definition.
  ULONG                             ulPowerplayTable[128];   ///< This 512 bytes memory is used to save ATOM_PPLIB_POWERPLAYTABLE5, starting form ulPowerplayTable[0]
} ATOM_FUSION_SYSTEM_INFO_V5;

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

