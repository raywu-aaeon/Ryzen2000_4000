/* $NoKeywords:$ */
/**
 * @file
 *
 * Platform PCIe Complex Definitions
 *
 * Contains AMD AGESA core interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
 **/


#ifndef _AMD_PCIE_COMPLEX_H_
#define _AMD_PCIE_COMPLEX_H_

//
//
// AGESA Types and Definitions
//
//

/*----------------------------------------------------------------------------
 *   GNB PCIe configuration info
 *----------------------------------------------------------------------------
 */

#define DESCRIPTOR_TERMINATE_LIST           0x80000000ull
#define DESCRIPTOR_IGNORE                   0x40000000ull

#define PCIE_PORT_PARAMETER_COUNT  64

/// PCIe link initialization
typedef enum {
  DxioEndpointDetect = 0,                                    ///< Detect endpoint presence
  DxioEndpointNotPresent                                     ///< Endpoint not present (or connected). Used in case there is alternative way to determine
                                                             ///< if device present on board or in slot. For example GPIO can be used to determine device presence.
} DXIO_ENDPOINT_STATUS;

//------------------------------------------------------------------------------
// DXIO ANCILLARY DATA FOR PSPP
//------------------------------------------------------------------------------

#define PsppThreshold0Percent     0
#define PsppThreshold5Percent     1
#define PsppThreshold10Percent    2
#define PsppThreshold15Percent    3
#define PsppThreshold20Percent    4
#define PsppThreshold25Percent    5
#define PsppThreshold30Percent    6
#define PsppThreshold40Percent    7
#define PsppThreshold50Percent    8
#define PsppThreshold60Percent    9
#define PsppThreshold70Percent    10
#define PsppThreshold75Percent    11
#define PsppThreshold80Percent    12
#define PsppThreshold90Percent    13
#define PsppThreshold95Percent    14
#define PsppThreshold100Percent   15

typedef union {
  struct {                                                              ///<
    UINT32         lowBWThreshold    : 4 ; ///< Low Bandwidth Threshold
    UINT32         HighBWThreshold   : 4 ; ///< High Bandwidth Threshold
    UINT32         lowBWThresholdG2  : 4 ; ///< Low Bandwidth Threshold
    UINT32         HighBWThresholdG2 : 4 ; ///< High Bandwidth Threshold
    UINT32         lowBWThresholdG3  : 4 ; ///< Low Bandwidth Threshold
    UINT32         HighBWThresholdG3 : 4 ; ///< High Bandwidth Threshold
    UINT32         reserved          : 5 ; ///<
    UINT32         BWHintCount       : 3 ; ///< Bandwidth Count
  } Field;                                                              ///<
  UINT32 Value;                                                         ///<
} DXIO_ANCILLARYPORTDATA_PSPP;

// --------------------------------------------------------------------------------------------------
// PHY Programming Data

typedef struct {
  IN       UINT16               ParamType;
  IN       UINT16               ParamValue;
} PORT_PARAM;

typedef struct {
  IN       PORT_PARAM           PhyParam [PCIE_PORT_PARAMETER_COUNT];
} PORT_PARAMS;

#define PORT_PARAMS_START  ,{{
#define PORT_PARAMS_END    }}
#define PORT_PARAM(x,y)    {x, y}

typedef enum {
  PP_DEVICE = 1             ,
  PP_FUNCTION               ,
  PP_PORT_PRESENT           ,
  PP_LINK_SPEED_CAP         ,
  PP_LINK_ASPM              ,
  PP_HOTPLUG_TYPE           ,
  PP_CLKREQ                 ,
  PP_ASPM_L1_1              ,
  PP_ASPM_L1_2              ,
  PP_COMPLIANCE             ,
  PP_SAFE_MODE              ,
  PP_CHIPSET_LINK           ,
  PP_CLOCK_PM               ,
  PP_CHANNELTYPE            ,
  PP_TURN_OFF_UNUSED_LANES  ,
  PP_APIC_GROUPMAP          ,
  PP_APIC_SWIZZLE           ,
  PP_APIC_BRIDGEINT         ,
  PP_PHY_PARAM
} DXIO_PORT_PARAM_TYPE;

#define PORT_PHY_PARAM(x,y) PORT_PARAM(PP_PHY_PARAM, ((y << 8) + x))

// --------------------------------------------------------------------------------------------------
// PHY Programming Data

typedef struct {
  IN       UINT8                ParamType;
  IN       UINT8                ParamValue;
} DXIO_PHY_PARAM;

typedef struct {
  IN       DXIO_PHY_PARAM       PhyParam [44];
} PHY_DATA;

#define PHY_PARAMS_START  ,{{
#define PHY_PARAMS_END    }}
#define PHY_PARAM(x,y)    {x, y}

typedef enum {
  rxX_los_threshold = 1     ,
  rx_vref_ctrl              ,
  SSC_OFF_FRUG1             ,
  SSC_OFF_PHUG1             ,

  GEN1_txX_eq_pre = (1 << 6),
  GEN1_txX_eq_main          ,
  GEN1_txX_eq_post          ,
  GEN1_txX_iboost_lvl       ,
  GEN1_txX_vboost_en        ,
  GEN1_Unsupported1         ,
  GEN1_Unsupported2         ,
  GEN1_rxX_eq_att_lvl       ,
  GEN1_rxX_eq_vga1_gain     ,
  GEN1_rxX_eq_vga2_gain     ,
  GEN1_rxX_eq_ctle_pole     ,
  GEN1_rxX_eq_ctle_boost    ,
  GEN1_rxX_eq_dfe_tap1      ,
  GEN1_tx_vboost_lvl        ,

  GEN2_txX_eq_pre = (2 << 6),
  GEN2_txX_eq_main          ,
  GEN2_txX_eq_post          ,
  GEN2_txX_iboost_lvl       ,
  GEN2_txX_vboost_en        ,
  GEN2_Unsupported1         ,
  GEN2_Unsupported2         ,
  GEN2_rxX_eq_att_lvl       ,
  GEN2_rxX_eq_vga1_gain     ,
  GEN2_rxX_eq_vga2_gain     ,
  GEN2_rxX_eq_ctle_pole     ,
  GEN2_rxX_eq_ctle_boost    ,
  GEN2_rxX_eq_dfe_tap1      ,
  GEN2_tx_vboost_lvl        ,

  GEN3_txX_eq_pre = (3 << 6),
  GEN3_txX_eq_main          ,
  GEN3_txX_eq_post          ,
  GEN3_txX_iboost_lvl       ,
  GEN3_txX_vboost_en        ,
  GEN3_rxX_adapt_afe_en     ,
  GEN3_rxX_adapt_dfe_en     ,
  GEN3_rxX_eq_att_lvl       ,
  GEN3_rxX_eq_vga1_gain     ,
  GEN3_rxX_eq_vga2_gain     ,
  GEN3_rxX_eq_ctle_pole     ,
  GEN3_rxX_eq_ctle_boost    ,
  GEN3_rxX_eq_dfe_tap1      ,
  GEN3_tx_vboost_lvl
} DXIO_PHY_PARAM_TYPE;

// --------------------------------------------------------------------------------------------------
// PCIe specific data structures

/// PCIe port misc extended controls
typedef struct  {
  IN      UINT8                     LinkComplianceMode     :1;  ///< Force port into compliance mode (device will not be trained, port output compliance pattern)
  IN      UINT8                     LinkSafeMode           :1;  /**< Safe mode PCIe capability. (Parameter may limit PCIe speed requested through DXIO_PORT_DATA::LinkSpeedCapability)
                                                                 *  @li @b 0 - port can advertize muximum supported capability
                                                                 *  @li @b 1 - port limit advertized capability and speed to PCIe Gen1
                                                                 */
  IN      UINT8                     SbLink                 :1;  /**< PCIe link type
                                                                 *  @li @b 0 - General purpose port
                                                                 *  @li @b 1 - Port connected to SB
                                                                 */
  IN      UINT8                     ClkPmSupport           :1;  /**< Clock Power Management Support
                                                                 *  @li @b 0 - Clock Power Management not configured
                                                                 *  @li @b 1 - Clock Power Management configured according to PCIe device capability
                                                                 */
  IN      UINT8                     ChannelType            :3;  /**< Channel Type
                                                                 *  @li @b 0 - Channel Type Not Specified
                                                                 *  @li @b 1 - Channel Type Short Trace
                                                                 *  @li @b 2 - Channel Type Long Trace
                                                                 */
  IN      UINT8                     TurnOffUnusedLanes     :1;   /**< Turn Off Unused Lanes
                                                                 *  @li @b 0 -
                                                                 *  @li @b 1 -
                                                                 */
} DXIO_PORT_MISC_CONTROL;

/// The IO APIC Interrupt Mapping Info
typedef struct {
  IN      UINT8                     GroupMap;               /**< Group mapping for slot or endpoint device (connected to PCIE port) interrupts .
                                                             *  @li <b>0</b> - IGNORE THIS STRUCTURE AND USE RECOMMENDED SETTINGS
                                                             *  @li <b>1</b> - mapped to Grp 0 (Interrupts 0..3   of IO APIC redirection table)
                                                             *  @li <b>2</b> - mapped to Grp 1 (Interrupts 4..7   of IO APIC redirection table)
                                                             *  @li ...
                                                             *  @li <b>8</b> - mapped to Grp 7 (Interrupts 28..31 of IO APIC redirection table)
                                                             */
  IN      UINT8                     Swizzle;                /**< Swizzle interrupt in the Group.
                                                             *  @li <b>0</b> - ABCD
                                                             *  @li <b>1</b> - BCDA
                                                             *  @li <b>2</b> - CDAB
                                                             *  @li <b>3</b> - DABC
                                                             */
  IN      UINT8                     BridgeInt;              /**< IOAPIC redirection table entry for PCIE bridge interrupt
                                                             *  @li <b>0</b>  - Entry 0  of IO APIC redirection table
                                                             *  @li <b>1</b>  - Entry 1  of IO APIC redirection table
                                                             *  @li ...
                                                             *  @li <b>31</b> - Entry 31 of IO APIC redirection table
                                                             */
} DXIO_APIC_DEVICE_INFO;

/// PCIe port configuration data
typedef struct  {
  IN       UINT8                   PortPresent         :1 ;   ///< Enable PCIe port for initialization.
  IN       UINT8                   Reserved1           :7 ;   /// Unused bits
  IN       UINT8                   DeviceNumber        :5 ;   /**< PCI Device number for port.
                                                               *   @li @b 0 - Native port device number
                                                               *   @li @b N - Port device number (See available configurations in BKDG
                                                               */
  IN       UINT8                   FunctionNumber      :3 ;   ///< Reserved for future use
  IN       UINT8                   LinkSpeedCapability :2 ;   /**< PCIe link speed/
                                                               *  @li @b 0 - Maximum supported by silicon
                                                               *  @li @b 1 - Gen1
                                                               *  @li @b 2 - Gen2
                                                               *  @li @b 3 - Gen3
                                                               */
  IN       UINT8                   AutoSpdChng         :2 ;   /**< Upstread Auto Speed Change Allowed/
                                                               *  @li @b 0 - Use default implementation (Disabled for Gen1, Enabled for Gen2/3)
                                                               *  @li @b 1 - Always Disabled
                                                               *  @li @b 2 - Always Enabled
                                                               *  @li @b 3 - Reserved
                                                               */
  IN       UINT8                   EqPreset            :4 ;   /**< Gen3 Equalization Preset */
  IN       UINT8                   LinkAspm            :2 ;   /**< ASPM control. (see AgesaPcieLinkAspm for additional option to control ASPM)
                                                               *  @li @b 0 - Disabled
                                                               *  @li @b 1 - L0s only
                                                               *  @li @b 2 - L1 only
                                                               *  @li @b 3 - L0s and L1
                                                               */
  IN       UINT8                   LinkAspmL1_1        :1 ;   /**< ASPM control. (see AgesaPcieLinkAspm for additional option to control ASPM)
                                                               *  @li @b 0 - Disabled
                                                               *  @li @b 1 - Enabled
                                                               */
  IN       UINT8                   LinkAspmL1_2        :1 ;   /**< ASPM control. (see AgesaPcieLinkAspm for additional option to control ASPM)
                                                               *  @li @b 0 - Disabled
                                                               *  @li @b 1 - Enabled
                                                               */
  IN       UINT8                   ClkReq              :4 ;   /**< ASPM Reserved Field
                                                               *  @li @b 0 - NONE
                                                               *  @li @b 1 - CLKREQ0 signal
                                                               *  @li @b 2 - CLKREQ1 signal
                                                               *  @li @b 3 - CLKREQ2 signal
                                                               *  @li @b 4 - CLKREQ3 signal
                                                               *  @li @b 5 - CLKREQG signal
                                                               */
  IN       UINT8                   LinkHotplug;              /**< Hotplug control.
                                                               *  @li @b 0 - Disabled
                                                               *  @li @b 1 - Basic
                                                               *  @li @b 2 - Server
                                                               *  @li @b 3 - Enhanced
                                                               */
  IN       UINT8                   SlotPowerLimit;           ///< PCIe slot power limit.
  IN       UINT8                   SlotPowerLimitScale :2 ;  /**< PCIe slot power limit Scale.
                                                               *  @li @b 00b = 1.0x
                                                               *  @li @b 01b = 0.1x
                                                               *  @li @b 10b = 0.01x
                                                               *  @li @b 11b = 0.001x
                                                               */
  IN       UINT8                   Reserved3           :6 ;  /// Unused bits
  IN       DXIO_PORT_MISC_CONTROL  MiscControls;             ///< Misc extended controls
  IN       DXIO_APIC_DEVICE_INFO   ApicDeviceInfo;           ///< IOAPIC device programming info
  IN       DXIO_ENDPOINT_STATUS    EndpointStatus;           ///< PCIe endpoint (device connected to PCIe port) status
} DXIO_PORT_DATA;


// --------------------------------------------------------------------------------------------------
// EtherNet specific data structures

typedef struct  {
  IN       UINT32               PortNum           :8;     ///< Port Number
  IN       UINT32               PlatConf          :4;     /**< Platform Config
                                                            *  0 = Reserved
                                                            *  1 = 10G/1G BackPlane
                                                            *  2 = 2.5G BackPlane
                                                            *  3= Soldered down 1000Base-T
                                                            *  4 = Soldered down 1000Base-X
                                                            *  5 = Soldered down NBase-T
                                                            *  6 = Soldered down 10GBase-T
                                                            *  7 = Soldered down 10GBase-r
                                                            *  8 = SFP+ Connector
                                                            */
  IN       UINT32               Reserved1         :4;     ///< Unused 12-15
  IN       UINT32               MdioId            :5;     ///< MDIO ID when MDIO Side band is used
  IN       UINT32               Reserved2         :2;     ///< Unused 21-22
  IN       UINT32               SuppSpeed         :4;     /**< Supported Speeds by Platform
                                                            *  1 = 100M Supported
                                                            *  2 = 1G Supported
                                                            *  4 = 2.5G Supported
                                                            *  8 = 10G Supported
                                                            */
  IN       UINT32               Reserved3         :1;     ///< Unused 27
  IN       UINT32               ConnType          :3;     /**< Supported Speeds by Platform
                                                            *  0 = Port not Used
                                                            *  1 = SFP+ Connection I2C interface
                                                            *  2 = MDIO PHY
                                                            *  4 = Backplane Connection
                                                            */
  IN       UINT32               Reserved4         :1;     ///< Unused 31
} ETH_PORT_PROPERTY0;

typedef struct  {
  IN       UINT32               MdioReset         :2;     /**< MDIO Reset Type
                                                            *  0 = None
                                                            *  1 = I2C GPIO
                                                            *  2 = Integrated GPIO
                                                            *  3 = Reserved
                                                            */
  IN       UINT32               Reserved1         :2;     ///< Unused 2-3
  IN       UINT32               MdioGpioResetNum  :2;     ///< Integrated GPIO number for reset
  IN       UINT32               Reserved2         :2;     ///< Unused 6-7
  IN       UINT32               SfpGpioAdd        :3;     ///< Lower I2C address of GPIO Expander PCA9535
  IN       UINT32               Reserved3         :1;     ///< Unused 11
  IN       UINT32               TxFault           :4;     ///< TX FAULT
  IN       UINT32               Rs                :4;     ///< RS Signal
  IN       UINT32               ModAbs            :4;     ///< MOD_ABS signal
  IN       UINT32               RxLoss            :4;     ///< Rx_LOS signal
  IN       UINT32               SfpGpioMask       :4;     ///< SFP+ sideband signals that are not supported by platform
} ETH_PORT_PROPERTY3;

typedef struct  {
  IN       UINT32               SfpMux            :3;     ///< Lower address of Mux PCA 9545
  IN       UINT32               Reserved1         :1;     ///< Unused 3
  IN       UINT32               SfpBusSeg         :3;     ///< SFP BUS Segment. Downstream channels of PCA9545
  IN       UINT32               Reserved2         :1;     ///< Unused 7
  IN       UINT32               SfpMuxUpAdd       :5;     ///< Upper address of Mux PCA 9545
  IN       UINT32               Reserved3         :3;     ///< Unused 13-15
  IN       UINT32               RedriverAddress   :7;     ///< Address of ReDriver
  IN       UINT32               RedriverInterface :1;     ///< ReDriver Interface Descriptor
  IN       UINT32               RedriverLane      :3;     ///< ReDriver Lane number
  IN       UINT32               Reserved4         :1;     ///< Unused 27
  IN       UINT32               RedriverModel     :3;     ///< ReDriver Model
  IN       UINT32               RedriverPresent   :1;     ///< Redriver Present
} ETH_PORT_PROPERTY4;

typedef struct  {
  IN       UINT32               TxEqPre           :6;     ///< TX EQ PRE
  IN       UINT32               Reserved1         :2;     ///< Unused 7-6
  IN       UINT32               TxEqMain          :6;     ///< TX EQ MAIN
  IN       UINT32               Reserved2         :2;     ///< Unused 15-14
  IN       UINT32               TxEqPost          :6;     ///< TX EQ POST
  IN       UINT32               Reserved3         :10;    ///< Unused 31-23
} ETH_PORT_TXEQ;

/// Ethernet PCIe port configuration data
typedef struct  {
  IN       ETH_PORT_PROPERTY0   EthPortProp0;             ///< XGBE_PORT_PROPERTY_0
  IN       ETH_PORT_PROPERTY3   EthPortProp3;             ///< XGBE_PORT_PROPERTY_3
  IN       ETH_PORT_PROPERTY4   EthPortProp4;             ///< XGBE_PORT_PROPERTY_4
  IN       UINT32               PadMux0;                  ///< PadMux0 Setting (8 bits)
  IN       UINT32               PadMux1;                  ///< PadMux1 Setting (8 bits)
  IN       UINT32               MacAddressLo;             ///< Lower 32 bits of MAC Address
  IN       UINT32               MacAddressHi;             ///< Upper 32 bits of MAC Address
  IN       ETH_PORT_TXEQ        EthPortTxEq;              ///< TX EQ Settings
} ETHERNET_PORT_DATA;


// --------------------------------------------------------------------------------------------------
// High level data structures for passing topology from platform to AGESA


/// Engine Configuration
typedef struct {
  IN       UINT8                EngineType;               /**< Engine type
                                                           *  @li @b 0 -  Ignore engine configuration
                                                           *  @li @b 1 -  PCIe port
                                                           *  @li @b 2 -  DDI
                                                           */
  IN       UINT8                HotPluggable  :1;         /**<HotPluggable
                                                           *  @li @b 0 - Link is NOT Hot-Switchable
                                                           *  @li @b 1 - Link IS Hot-Switchable
                                                           */
  IN       UINT8                Reserved1     :7;         /**< Unused field, leave as 0
                                                           */
  IN       UINT8                StartLane;                /**< Start Lane ID (in reversed configuration StartLane > EndLane)
                                                           * Refer to lane descriptions and supported configurations in BKDG
                                                           */
  IN       UINT8                EndLane;                  /**< End lane ID (in reversed configuration StartLane > EndLane)
                                                           * Refer to lane descriptions and supported configurations in BKDG
                                                           */
  IN       UINT8                GpioGroupId;              /**< Unique identifier for the GPIO or GPIO group associated with
                                                           * this engine.  GPIOs are used for hotplug notification and link
                                                           * type (e.g SATA Express or PCIe)
                                                           */
  IN       UINT8                DxioStartLane;            /**< Internal coding of start lane
                                                           */
  IN       UINT8                DxioEndLane;              /**< Internal coding of end lane
                                                           */
  IN       UINT8                Reserved4;                /**< Unused field, leave as 0
                                                           */
} DXIO_ENGINE_DATA;

/// DDI channel lane mapping
typedef struct {                                          ///< Structure that discribe lane mapping
  IN      UINT8              Lane0   :2;                  /**< Lane 0 mapping
                                                           *  @li @b 0 - Map to lane 0
                                                           *  @li @b 1 - Map to lane 1
                                                           *  @li @b 2 - Map to lane 2
                                                           *  @li @b 2 - Map to lane 3
                                                           */
  IN      UINT8              Lane1   :2;                  ///< Lane 1 mapping (see "Lane 0 mapping")
  IN      UINT8              Lane2   :2;                  ///< Lane 2 mapping (see "Lane 0 mapping")
  IN      UINT8              Lane3   :2;                  ///< Lane 3 mapping (see "Lane 0 mapping")
} DXIO_CHANNEL_MAPPING;

/// Common Channel Mapping
typedef union {
  IN      UINT8                ChannelMappingValue;       ///< Raw lane mapping
  IN      DXIO_CHANNEL_MAPPING      ChannelMapping;            ///< Channel mapping
} DXIO_CONN_CHANNEL_MAPPING;

/// DDI Configuration data
typedef struct  {
  IN       UINT8                ConnectorType;            /**< Display Connector Type
                                                            *  @li @b 0 - DP
                                                            *  @li @b 1 - eDP
                                                            *  @li @b 2 - Single Link DVI-D
                                                            *  @li @b 3 - Dual  Link DVI-D (see @ref DualLinkDviDescription "Example Dual Link DVI connector description")
                                                            *  @li @b 4 - HDMI
                                                            *  @li @b 5 - DP-to-VGA
                                                            *  @li @b 6 - DP-to-LVDS
                                                            *  @li @b 7 - Hudson-2 NutMeg DP-to-VGA
                                                            *  @li @b 8 - Single Link DVI-I
                                                            *  @li @b 9 - Native CRT (Family 0x14)
                                                            *  @li @b 10 - Native LVDS (Family 0x14)
                                                            *  @li @b 11 - Auto detect LCD panel connector type. VBIOS is able to auto detect the LVDS connector type: native LVDS, eDP or DP-to-LVDS
                                                            *              The auto detection method only support panel with EDID.
                                                            */
  IN       UINT8                AuxIndex;                 /**< Indicates which AUX or DDC Line is used
                                                            *  @li @b 0 - AUX1
                                                            *  @li @b 1 - AUX2
                                                            *  @li @b 2 - AUX3
                                                            *  @li @b 3 - AUX4
                                                            *  @li @b 4 - AUX5
                                                            *  @li @b 5 - AUX6
                                                            */
  IN       UINT8                HdpIndex;                 /**< Indicates which HDP pin is used
                                                            *  @li @b 0 - HDP1
                                                            *  @li @b 1 - HDP2
                                                            *  @li @b 2 - HDP3
                                                            *  @li @b 3 - HDP4
                                                            *  @li @b 4 - HDP5
                                                            *  @li @b 5 - HDP6
                                                            */
  IN       DXIO_CONN_CHANNEL_MAPPING Mapping[2];               /**< Set specific mapping of lanes to connector pins
                                                            *  @li Mapping[0] define mapping for group of 4 lanes starting at PCIe_ENGINE_DATA.StartLane
                                                            *  @li Mapping[1] define mapping for group of 4 lanes ending at PCIe_ENGINE_DATA.EndLane (only applicable for Dual DDI link)
                                                            *  if Mapping[x] set to 0 than default mapping assumed
                                                            */
  IN       UINT8                LanePnInversionMask;      /**< Specifies whether to invert the state of P and N for each lane. Each bit represents a PCIe lane on the DDI port.
                                                            *  @li 0 - Do not invert (default)
                                                            *  @li 1 - Invert P and N on this lane
                                                            */
  IN       UINT8                Flags;                    /**< Capabilities flags
                                                            *  @li Flags bit[0] DDI_DATA_FLAGS_DP1_1_ONLY Selects downgrade PHY link to DP1.1
                                                            *  @li Flags bit[7:1] Reserved
                                                            */
} DDI_DATA;

/// PCIe port descriptor
typedef struct {
  IN       UINT32               Flags;                    /**< Descriptor flags
                                                           * @li @b Bit31 - last descriptor in complex
                                                           */
  IN       DXIO_ENGINE_DATA     EngineData;               ///< Engine data
  IN       DXIO_PORT_DATA       Port;                     ///< PCIe port specific configuration info
  IN       ETHERNET_PORT_DATA   EtherNet;                 ///< Ancillary data for EtherNet
  IN       PHY_DATA             Phy;                      ///< Ancillary data for PHY programming customization
  IN       PORT_PARAMS          PortParams;               ///< Extensible port parameter list for simplified topology structure
} DXIO_PORT_DESCRIPTOR;

/// DDI descriptor
typedef struct {
  IN       UINT32          Flags;                    /**< Descriptor flags
                                                           * @li @b Bit31 - last descriptor in complex
                                                           */
  IN       DDI_DATA        Ddi;                      ///< DDI port specific configuration info
} DDI_DESCRIPTOR;


/// PCIe Complex descriptor
typedef struct {
  IN       UINT32               Flags;                    /**< Descriptor flags
                                                           * @li @b Bit31 - last descriptor in topology
                                                           */
  IN       UINT32               SocketId;                 ///< Socket Id
  IN       DXIO_PORT_DESCRIPTOR *PciePortList;            ///< Pointer to array of PCIe port descriptors or NULL (Last element of array must be terminated with DESCRIPTOR_TERMINATE_LIST).
  IN       DDI_DESCRIPTOR       *DdiLinkList;             ///< Reserved for compatibility with FM15
  IN       VOID                 *Reserved2;               ///< Reserved for future use
  IN       UINT32               BmcLinkLocation;          ///< Identifies the socket/die location of a BMC link (Used by AGESA, input not required)
} DXIO_COMPLEX_DESCRIPTOR;

/// Engine descriptor type
typedef enum {
  DxioUnusedEngine = 0,                                   ///< Unused descriptor
  DxioPcieEngine = 1,                                     ///< PCIe port
  DxioUSBEngine = 2,                                      ///< USB port
  DxioSATAEngine = 3,                                     ///< SATA
  DxioDPEngine = 8,                                       ///< Digital Display
  DxioEthernetEngine = 0x10,                              ///< Ethernet (GBe, XGBe)
  DxioGOPEngine = 0x20,                                   ///< GOP ///@todo
  DxioNTBDevice = 0x60,                                   ///< For NBIF NTB Enable - DO NOT USE FOR DXIO
  DxioHDaudioEngine,                                      ///< For NBIF HDaudtio Enable - DO NOT USE FOR DXIO
  DxioACPEngine,                                          ///< For NBIF ACP Enable - DO NOT USE FOR DXIO
  DxioMP2Engine,                                          ///< For NBIF MP2 Enable - DO NOT USE FOR DXIO
  DxioMaxPcieEngine                                       ///< Max engine type for boundary check.
} DXIO_ENGINE_TYPE;

/// PCIe link capability/speed
typedef enum  {
  DxioGenMaxSupported,                                    ///< Maximum supported
  DxioGen1 = 1,                                           ///< Gen1
  DxioGen2,                                               ///< Gen2
  DxioGen3,                                               ///< Gen3
  DxioGen4,                                               ///< Gen4
  MaxDxioGen                                              ///< Max Gen for boundary check
} DXIO_LINK_SPEED_CAP;

/// PCIe link ASPM
typedef enum {
  DxioAspmDisabled,                                           ///< Disabled
  DxioAspmL0s,                                                ///< PCIe L0s link state
  DxioAspmL1,                                                 ///< PCIe L1 link state
  DxioAspmL0sL1,                                              ///< PCIe L0s & L1 link state
  DxioMaxAspm                                                 ///< Not valid value, used to verify input
} DXIO_ASPM_TYPE;

/// PCIe link hotplug support
typedef enum {
  DxioHotplugDisabled,                                        ///< Hotplug disable
  DxioHotplugBasic,                                           ///< Basic Hotplug
  DxioHotplugServerExpress,                                   ///< Server Hotplug Express Module
  DxioHotplugEnhanced,                                        ///< Enhanced
  DxioHotplugInboard,                                         ///< Inboard
  DxioHotplugServerEntSSD,                                    ///< Server Hotplug Enterprise SSD
  MaxDxioHotplug                                              ///< Not valid value, used to verify input
} DXIO_LINK_HOTPLUG_TYPE;

/// PCIe link initialization
typedef enum {
  DxioPortDisabled,                                           ///< Disable
  DxioPortEnabled                                             ///< Enable
} DXIO_PORT_ENABLE;

/// PCIe ClkPmSupport initialization
typedef enum {
  DxioClkPmSupportDisabled,                                   ///< Disable
  DxioClkPmSupportEnabled                                     ///< Enable
} DXIO_CLKPM_SUPPORT_ENABLE;

/// SATA ChannelType initialization
typedef enum {
  DxioSataChannelOther,                                       ///< Default Channel Type
  DxioSataChannelShort,                                       ///< Short Trace Channel Type
  DxioSataChannelLong                                         ///< Long Trace Channel Type
} DXIO_SATA_CHANNEL_TYPE;

/// CLKREQ signal Type initialization
typedef enum {
  DxioClkReqNone,                                             ///< Default None
  DxioClkReq0,                                                ///< CLKREQ0 signal
  DxioClkReq1,                                                ///< CLKREQ1 signal
  DxioClkReq2,                                                ///< CLKREQ2 signal
  DxioClkReq3,                                                ///< CLKREQ3 signal
  DxioClkReqG,                                                ///< CLKREQG signal
} DXIO_CLKREQ_TYPE;

/// Equalization Preset Search mode options
typedef enum {
  DxioEqPresetSearchDirectional,                              ///< Eq Preset Search Mode - Directional - do not use
  DxioEqPresetSearchExhaustive,                               ///< Eq Preset Search Mode - Exhaustive
  DxioEqPresetSearchUnsupported,                              ///< Eq Preset Search Mode - Unsupported - do not use
  DxioEqPresetSearchPreset,                                   ///< Eq Preset Search Mode - Preset
} DXIO_EQPRESET_TYPE;


// Macro for statically initializing various structures
// Simplified versions
#define  DXIO_ENGINE_INITIALIZER(mType, mStartLane, mEndLane, mResetId) {mType, 0, 0, mStartLane, mEndLane, mResetId, 0, 0, 0}

#define  DXIO_PORT_INITIALIZER(mPortPresent) \
                               {mPortPresent, 0, 0, DxioGenMaxSupported, AspmL0sL1, DxioAspmDisabled, DxioAspmDisabled, 0, DxioHotplugDisabled, \
                               {0, DxioGenMaxSupported, 0, DxioClkPmSupportDisabled, 0, 1}, {0, 0, 0}, DxioEndpointDetect}, \
                               {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}, {{{0, 0}}}

// Traditional versions
#define  DXIO_ENGINE_DATA_INITIALIZER(mType, mStartLane, mEndLane, mHotplug, mGpioGroupId) {mType, mHotplug, 0, mStartLane, mEndLane, mGpioGroupId, 0, 0, 0}

#define  DXIO_PORT_DATA_INITIALIZER_PCIE(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, \
                                         mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport) \
                                        {mPortPresent, 0, mDevAddress, mDevFunction, mMaxLinkSpeed, 0, 0, mAspm, mAspmL1_1, \
                                         mAspmL1_2, 0, mHotplug, 0, 0, 0, {0, mMaxLinkCap, 0, mClkPmSupport, 0, 1}, {0, 0, 0}, \
                                         DxioEndpointDetect}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_PCIE_V2(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, \
                                         mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport, mClkReq) \
                                        {mPortPresent, 0, mDevAddress, mDevFunction, mMaxLinkSpeed, 0, 0, mAspm, mAspmL1_1, \
                                         mAspmL1_2, mClkReq, mHotplug, 0, 0, 0, {0, mMaxLinkCap, 0, mClkPmSupport, 0, 1}, {0, 0, 0}, \
                                         DxioEndpointDetect}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_PCIE_V3(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, \
                                         mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport, mClkReq, mAutoSpdChange) \
                                        {mPortPresent, 0, mDevAddress, mDevFunction, mMaxLinkSpeed, mAutoSpdChange, 0, mAspm, mAspmL1_1, \
                                         mAspmL1_2, mClkReq, mHotplug, 0, 0, 0, {0, mMaxLinkCap, 0, mClkPmSupport, 0, 1}, {0, 0, 0}, \
                                         DxioEndpointDetect}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_PCIE_V4(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, \
                                         mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport, mClkReq, mAutoSpdChange, mSlotPowerLimit, mSlotPowerLimitScale) \
                                        {mPortPresent, 0, mDevAddress, mDevFunction, mMaxLinkSpeed, mAutoSpdChange, 0, mAspm, mAspmL1_1, \
                                         mAspmL1_2, mClkReq, mHotplug, mSlotPowerLimit, mSlotPowerLimitScale, 0, {0, mMaxLinkCap, 0, mClkPmSupport, 0, 1}, {0, 0, 0}, \
                                         DxioEndpointDetect}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_PCIE_V5(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, \
                                         mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport, mEqPreset) \
                                        {mPortPresent, 0, mDevAddress, mDevFunction, mMaxLinkSpeed, 0, mEqPreset, mAspm, mAspmL1_1, \
                                         mAspmL1_2, 0, mHotplug, {0, mMaxLinkCap, 0, mClkPmSupport, 0, 1}, {0, 0, 0}, \
                                         DxioEndpointDetect}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}


#define  DXIO_PORT_DATA_INITIALIZER_CHIP(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, \
                                         mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport) \
                                        {mPortPresent, 0, mDevAddress, mDevFunction, mMaxLinkSpeed, 0, 0, mAspm, mAspmL1_1, \
                                         mAspmL1_2, 0, mHotplug, 0, 0, 0, {0, mMaxLinkCap, 1, mClkPmSupport, 0, 0}, {0, 0, 0}, \
                                         DxioEndpointDetect}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_SATA(mPortPresent) {mPortPresent, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}, {0, 0, 0}, 0}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_SATA_V2(mPortPresent, mChannelType) {mPortPresent, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, mChannelType, 0}, {0, 0, 0}, 0}, \
                                         {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}}

#define  DXIO_PORT_DATA_INITIALIZER_ENET(mPortPresent, mPortNum, mPlatConf, mMdioId, mSuppSpeed, mConnType, mMdioReset, mMdioGpioResetNum, \
                                         mSfpGpioAdd, mTxFault, mRs, mModAbs, mRxLoss, mSfpGpioMask, mSfpMux, mSfpBusSeg, \
                                         mSfpMuxUpAdd, mRedriverAddress, mRedriverInterface, mRedriverLane, mRedriverModel, \
                                         mRedriverPresent, mPadMux0, mPadMux1, mMacAddressLo, mMacAddressHi, \
                                         mTxEqPre, mTxEqMain, mTxEqPost) \
                                        {mPortPresent, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}, {0, 0, 0}, 0}, \
                                        {{mPortNum, mPlatConf, 0, mMdioId, 0, mSuppSpeed, 0, mConnType, 0}, \
                                         {mMdioReset, 0, mMdioGpioResetNum, 0, mSfpGpioAdd, 0, mTxFault, mRs, mModAbs, mRxLoss, mSfpGpioMask}, \
                                         {mSfpMux, 0, mSfpBusSeg, 0, mSfpMuxUpAdd, 0, mRedriverAddress, mRedriverInterface, mRedriverLane, 0, mRedriverModel, mRedriverPresent}, \
                                         mPadMux0, mPadMux1, mMacAddressLo, mMacAddressHi, \
                                         {mTxEqPre, 0, mTxEqMain, 0, mTxEqPost, 0}}
#endif // _AGESA_H_

