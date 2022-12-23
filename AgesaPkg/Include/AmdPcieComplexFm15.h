/* $NoKeywords:$ */
/**
 * @file
 *
 * Platform PCIe Complex Definitions for Family 15h
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


#ifndef _AMD_PCIE_COMPLEXFM15_H_
#define _AMD_PCIE_COMPLEXFM15_H_

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

/// PCIe link initialization
typedef enum {
  EndpointDetect = 0,                                     ///< Detect endpoint presence
  EndpointNotPresent                                      ///< Endpoint not present (or connected). Used in case there is alternative way to determine
                                                          ///< if device present on board or in slot. For example GPIO can be used to determine device presence.
} PCIE_ENDPOINT_STATUS;

/// PCIe port misc extended controls
typedef struct  {
  IN      UINT8                     LinkComplianceMode :1;  ///< Force port into compliance mode (device will not be trained, port output compliance pattern)
  IN      UINT8                     LinkSafeMode       :2;  /**< Safe mode PCIe capability. (Parameter may limit PCIe speed requested through PCIe_PORT_DATA::LinkSpeedCapability)
                                                             *  @li @b 0 - port can advertize muximum supported capability
                                                             *  @li @b 1 - port limit advertized capability and speed to PCIe Gen1
                                                             */
  IN      UINT8                     SbLink             :1;  /**< PCIe link type
                                                             *  @li @b 0 - General purpose port
                                                             *  @li @b 1 - Port connected to SB
                                                             */
  IN      UINT8                     ClkPmSupport       :1;  /**< Clock Power Management Support
                                                             *  @li @b 0 - Clock Power Management not configured
                                                             *  @li @b 1 - Clock Power Management configured according to PCIe device capability
                                                             */
} PCIe_PORT_MISC_CONTROL;

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
} APIC_DEVICE_INFO;

/// Initial Offset Calibration Control
typedef enum {
  ADAPT_IOC_DISABLED = 0,                                     ///< Initial Offset Calibration Disabled
  ADAPT_IOC_ENABLED                                           ///< Initial Offset Calibration Enabled
} ADAPT_IOC_CONTROL;

/// DFE Control values
typedef enum {
  ADAPT_DFE_CONTROL_DISABLED = 0,                             ///< DFE Disabled
  ADAPD_DFE_CONTROL_1TAP_DFE = 4,                             ///< 1-tap DFE
  ADAPD_DFE_CONTROL_1TAP_DFE_FBF,                             ///< 1-tap DFE with Future Bit Filtering
  ADAPD_DFE_CONTROL_2TAP_DFE,                                ///< 2-tap DFE
  ADAPD_DFE_CONTROL_2TAP_DFE_FBF                              ///< 2-tap DFE with Future Bit Filtering
} ADAPT_DFE_CONTROL;

/// LEQ Control values
typedef enum {
  ADAPT_LEQ_CONTROL_DISABLED = 0,                              ///< LEQ Disabled
  ADAPT_LEQ_CONTROL_DC_GAIN  = 2,                              ///< DC Gain Adaptation
  ADAPT_LEQ_CONTROL_DC_GAIN_POLE                               ///< DC Gain and Pole Adaptation
} ADAPT_LEQ_CONTROL;

/// Dynamic Offset Calibration Control
typedef enum {
  ADAPT_DOC_DISABLED = 0,                                      ///< Dynamic Offset Calibration Disabled
  ADAPT_DOC_ENABLED                                            ///< Dynamic Offset Calibration Enabled
} ADAPT_DOC_CONTROL;

/// FOM Calculation Control
typedef enum {
  ADAPT_FOMC_DISABLED = 0,                                    ///< FOM Calculation Disabled
  ADAPT_FOMC_ENABLED                                          ///< FOM Calculation Enabled
} ADAPT_FOMC_CONTROL;

/// PI Offset Calibration Control
typedef enum {
  ADAPT_PIOC_DISABLED = 0,                                    ///< PI Offset Calibration Disabled
  ADAPT_PIOC_ENABLED                                          ///< PI Offset Calibration Enabled
} ADAPT_PIOC_CONTROL;

/// GEN3 RxAdaptMode Configuration Structure
typedef struct {
  IN      BOOLEAN                InitOffsetCancellation;     ///< Initial Offset Cancellation Enable
  IN      UINT8                  DFEControl;                 ///< DFE Control
  IN      UINT8                  LEQControl;                 ///< LEQ Control
  IN      BOOLEAN                DynamicOffsetCalibration;   ///< Dynamic Offset Calibration Enable
  IN      BOOLEAN                FOMCalculation;             ///< FOM Calculation Enable
  IN      BOOLEAN                PIOffsetCalibration;        ///< PI Offset Calibratino Enable
} RX_ADAPT_MODE;

/// PCIe port configuration data
typedef struct  {
  IN       UINT8                   PortPresent;              ///< Enable PCIe port for initialization.
  IN       UINT8                   ChannelType;              /**< Channel type.
                                                               *  @li @b 0 - "lowLoss",
                                                               *  @li @b 1 - "highLoss",
                                                               *  @li @b 2 - "mob0db",
                                                               *  @li @b 3 - "mob3db",
                                                               *  @li @b 4 - "extnd6db"
                                                               *  @li @b 5 - "extnd8db"
                                                               */
  IN       UINT8                   DeviceNumber;             /**< PCI Device number for port.
                                                               *   @li @b 0 - Native port device number
                                                               *   @li @b N - Port device number (See available configurations in BKDG
                                                               */
  IN       UINT8                   FunctionNumber;           ///< Reserved for future use
  IN       UINT8                   LinkSpeedCapability;      /**< PCIe link speed/
                                                               *  @li @b 0 - Maximum supported by silicon
                                                               *  @li @b 1 - Gen1
                                                               *  @li @b 2 - Gen2
                                                               *  @li @b 3 - Gen3
                                                               */
  IN       UINT8                   LinkAspm;                 /**< ASPM control. (see AgesaPcieLinkAspm for additional option to control ASPM)
                                                               *  @li @b 0 - Disabled
                                                               *  @li @b 1 - L0s only
                                                               *  @li @b 2 - L1 only
                                                               *  @li @b 3 - L0s and L1
                                                               */
  IN       UINT8                   LinkHotplug;              /**< Hotplug control.
                                                               *  @li @b 0 - Disabled
                                                               *  @li @b 1 - Basic
                                                               *  @li @b 2 - Server
                                                               *  @li @b 3 - Enhanced
                                                               */
  IN       UINT8                   ResetId;                  /**< Arbitrary number greater than 0 assigned by platform firmware for GPIO
                                                               *   identification which control reset for given port.
                                                               *   Each port with unique GPIO should have unique ResetId assigned.
                                                               *   All ports use same GPIO to control reset should have same ResetId assigned.
                                                               *   see AgesaPcieSlotResetContol.
                                                               */
  IN       PCIe_PORT_MISC_CONTROL  MiscControls;             ///< Misc extended controls
  IN       APIC_DEVICE_INFO        ApicDeviceInfo;           ///< IOAPIC device programming info
  IN       PCIE_ENDPOINT_STATUS    EndpointStatus;           ///< PCIe endpoint (device connected to PCIe port) status
  IN       RX_ADAPT_MODE           RxAdaptMode;              ///< Gen3 RxAdaptMode configuration
} PCIe_PORT_DATA;

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
} CHANNEL_MAPPING;                                        ///< Lane mapping

/// Common Channel Mapping
typedef union {
  IN      UINT8                ChannelMappingValue;       ///< Raw lane mapping
  IN      CHANNEL_MAPPING      ChannelMapping;            ///< Channel mapping
} CONN_CHANNEL_MAPPING;

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
  IN       CONN_CHANNEL_MAPPING Mapping[2];               /**< Set specific mapping of lanes to connector pins
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
} PCIe_DDI_DATA;

/// Engine Configuration
typedef struct {
  IN       UINT8                EngineType;               /**< Engine type
                                                           *  @li @b 0 -  Ignore engine configuration
                                                           *  @li @b 1 -  PCIe port
                                                           *  @li @b 2 -  DDI
                                                           */
  IN       UINT16               StartLane;                /**< Start Lane ID (in reversed configuration StartLane > EndLane)
                                                           * Refer to lane descriptions and supported configurations in BKDG
                                                           */
  IN       UINT16               EndLane;                  /**< End lane ID (in reversed configuration StartLane > EndLane)
                                                           * Refer to lane descriptions and supported configurations in BKDG
                                                           */

} PCIe_ENGINE_DATA;

/// PCIe port descriptor
typedef struct {
  IN       UINT32               Flags;                    /**< Descriptor flags
                                                           * @li @b Bit31 - last descriptor in complex
                                                           */
  IN       PCIe_ENGINE_DATA     EngineData;               ///< Engine data
  IN       PCIe_PORT_DATA       Port;                     ///< PCIe port specific configuration info
} PCIe_PORT_DESCRIPTOR;

/// DDI descriptor
typedef struct {
  IN       UINT32               Flags;                    /**< Descriptor flags
                                                           * @li @b Bit31 - last descriptor in complex
                                                           */
  IN       PCIe_ENGINE_DATA     EngineData;               ///< Engine data
  IN       PCIe_DDI_DATA        Ddi;                      ///< DDI port specific configuration info
} PCIe_DDI_DESCRIPTOR;

/// PCIe Complex descriptor
typedef struct {
  IN       UINT32               Flags;                    /**< Descriptor flags
                                                           * @li @b Bit31 - last descriptor in topology
                                                           */
  IN       UINT32               SocketId;                 ///< Socket Id
  IN       PCIe_PORT_DESCRIPTOR *PciePortList;            ///< Pointer to array of PCIe port descriptors or NULL (Last element of array must be terminated with DESCRIPTOR_TERMINATE_LIST).
  IN       PCIe_DDI_DESCRIPTOR  *DdiLinkList;             ///< Pointer to array DDI link descriptors (Last element of array must be terminated with DESCRIPTOR_TERMINATE_LIST).
  IN       VOID                 *Reserved;                ///< Reserved for future use
} PCIe_COMPLEX_DESCRIPTOR;

/// Engine descriptor type
typedef enum {
  PcieUnusedEngine = 0,                                   ///< Unused descriptor
  PciePortEngine = 1,                                     ///< PCIe port
  PcieDdiEngine = 2,                                      ///< DDI
  MaxPcieEngine                                           ///< Max engine type for boundary check.
} PCIE_ENGINE_TYPE;

/// PCIe link capability/speed
typedef enum  {
  PcieGenMaxSupported,                                    ///< Maximum supported
  PcieGen1 = 1,                                           ///< Gen1
  PcieGen2,                                               ///< Gen2
  PcieGen3,                                               ///< Gen3
  MaxPcieGen                                              ///< Max Gen for boundary check
} PCIE_LINK_SPEED_CAP;

/// PCIe PSPP Power policy
typedef enum  {
  PsppDisabled,                                           ///< PSPP disabled
  PsppPerformance = 1,                                    ///< Performance
  PsppBalanceHigh,                                        ///< Balance-High
  PsppBalanceLow,                                         ///< Balance-Low
  PsppPowerSaving,                                        ///< Power Saving
  MaxPspp                                                 ///< Max Pspp for boundary check
} PCIE_PSPP_POLICY;

/// DDI display connector type
typedef enum {
  ConnectorTypeDP,                                        ///< DP
  ConnectorTypeEDP,                                       ///< eDP
  ConnectorTypeSingleLinkDVI,                             ///< Single Link DVI-D
  ConnectorTypeDualLinkDVI,                               ///< Dual  Link DVI-D
  ConnectorTypeHDMI,                                      ///< HDMI
  ConnectorTypeDpToVga,                                   ///< DP-to-VGA
  ConnectorTypeDpToLvds,                                  ///< DP-to-LVDS
  ConnectorTypeNutmegDpToVga,                             ///< Hudson-2 NutMeg DP-to-VGA
  ConnectorTypeSingleLinkDviI,                            ///< Single Link DVI-I
  ConnectorTypeCrt,                                       ///< CRT (VGA)
  ConnectorTypeLvds,                                      ///< LVDS
  ConnectorTypeEDPToLvds,                                 ///< 3rd party common eDP-to-LVDS translator chip without AMD SW init
  ConnectorTypeEDPToLvdsSwInit,                           ///< 3rd party eDP-to-LVDS translator which requires AMD SW init
  ConnectorTypeAutoDetect,                                ///< VBIOS auto detect connector type (native LVDS, eDP or DP-to-LVDS)
  MaxConnectorType                                        ///< Not valid value, used to verify input
} PCIE_CONNECTOR_TYPE;

/// PCIe link channel type
typedef enum {
  ChannelTypeLowLoss,                                     ///< Low Loss
  ChannelTypeHighLoss,                                    ///< High Loss
  ChannelTypeMob0db,                                      ///< Mobile 0dB
  ChannelTypeMob3db,                                      ///< Mobile 3dB
  ChannelTypeExt6db,                                      ///< Extended 6dB
  ChannelTypeExt8db,                                      ///< Extended 8dB
  MaxChannelType                                          ///< Not valid value, used to verify input
} PCIE_CHANNEL_TYPE;

/// PCIe link ASPM
typedef enum {
  AspmDisabled,                                           ///< Disabled
  AspmL0s,                                                ///< PCIe L0s link state
  AspmL1,                                                 ///< PCIe L1 link state
  AspmL0sL1,                                              ///< PCIe L0s & L1 link state
  MaxAspm                                                 ///< Not valid value, used to verify input
} PCIE_ASPM_TYPE;

/// PCIe link hotplug support
typedef enum {
  HotplugDisabled,                                        ///< Hotplug disable
  HotplugBasic,                                           ///< Basic Hotplug
  HotplugServer,                                          ///< Server Hotplug
  HotplugEnhanced,                                        ///< Enhanced
  HotplugInboard,                                         ///< Inboard
  MaxHotplug                                              ///< Not valid value, used to verify input
} PCIE_HOTPLUG_TYPE;

/// PCIe link initialization
typedef enum {
  PortDisabled,                                           ///< Disable
  PortEnabled                                             ///< Enable
} PCIE_PORT_ENABLE;

/// PCIe ACS capability - Access Control Services
typedef enum  {
  PcieAcsDisabled,                                        ///< Disabled
  PcieAcsEnabled,                                         ///< Enabled
} PCIE_ACS_CAP;

/// PCIe ClkPmSupport initialization
typedef enum {
  ClkPmSupportDisabled,                                   ///< Disable
  ClkPmSupportEnabled                                     ///< Enable
} CLKPM_SUPPORT_ENABLE;

/// DDI Aux channel
typedef enum {
  Aux1,                                                   ///< Aux1
  Aux2,                                                   ///< Aux2
  Aux3,                                                   ///< Aux3
  Aux4,                                                   ///< Aux4
  Aux5,                                                   ///< Aux5
  Aux6,                                                   ///< Aux6
  MaxAux                                                  ///< Not valid value, used to verify input
} PCIE_AUX_TYPE;

/// DDI Hdp Index
typedef enum {
  Hdp1,                                                   ///< Hdp1
  Hdp2,                                                   ///< Hdp2
  Hdp3,                                                   ///< Hdp3
  Hdp4,                                                   ///< Hdp4
  Hdp5,                                                   ///< Hdp5
  Hdp6,                                                   ///< Hdp6
  MaxHdp                                                  ///< Not valid value, used to verify input
} PCIE_HDP_TYPE;

/// PCIe_DDI_DATA.Flags definitions
#define DDI_DATA_FLAGS_DP1_1_ONLY                        0x01         ///< BIT[0] Selects downgrade PHY link to DP1.1
#define EXT_DISPLAY_PATH_CAPS_DP_FIXED_VS_EN             0x02         ///< BIT[1] VBIOS will always output fixed voltage swing during DP link training
#define EXT_DISPLAY_PATH_CAPS_HDMI20_PI3EQX1204          0x04         ///< BIT[2] HDMI 2.0 connector
#define EXT_DISPLAY_PATH_CAPS_HDMI20_TISN65DP159RSBT     0x08         ///< BIT[3] HDMI 2.0 connector

/// DP receiver definitions with fixed voltage swing
typedef enum {
  DP_VS_0_4V_0DB,                                         ///< 0x00
  DP_VS_0_6V_0DB,                                         ///< 0x01
  DP_VS_0_8V_0DB,                                         ///< 0x02
  DP_VS_1_2V_0DB,                                         ///< 0x03
  DP_VS_0_4V_3_5DB = 0x8,                                 ///< 0x08
  DP_VS_0_6V_3_5DB,                                       ///< 0x09
  DP_VS_0_8V_3_5DB,                                       ///< 0x0a
  DP_VS_0_4V_6DB = 0x10,                                  ///< 0x10
  DP_VS_0_6V_6DB,                                         ///< 0x11
  DP_VS_0_4V_9_5DB = 0x18                                 ///< 0x18
} DP_FIXED_VOLT_SWING_TYPE;

// definition for eDP 1.4 VSMode
#define EDP_VS_LEGACY_MODE                  0             ///< Legacy Mode
#define EDP_VS_LOW_VDIFF_MODE               1             ///< Low Vdiff Training Mode
#define EDP_VS_HIGH_VDIFF_MODE              2             ///< High Vdiff Training Mode
#define EDP_VS_STRETCH_MODE                 3             ///< Stretched DP training mode
#define EDP_VS_SINGLE_VDIFF_MODE            4             ///< Single Vdiff Training Mode
#define EDP_VS_VARIABLE_PREM_MODE           5             ///< Single Vdiff Training with Variable Transition Vdiff


// Macro for statically initializing various structures
#define  PCIE_ENGINE_DATA_INITIALIZER(mType, mStartLane, mEndLane) {mType, mStartLane, mEndLane}
#define  PCIE_PORT_DATA_INITIALIZER(mPortPresent, mChannelType, mDevAddress, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mResetId) \
{mPortPresent, mChannelType, mDevAddress, 0, mMaxLinkSpeed, mAspm, mHotplug, mResetId, {0, mMaxLinkCap, 0, 0}, {0, 0, 0}, EndpointDetect, \
{ADAPT_IOC_ENABLED, ADAPT_DFE_CONTROL_DISABLED, ADAPT_LEQ_CONTROL_DC_GAIN_POLE, ADAPT_DOC_DISABLED, ADAPT_FOMC_ENABLED, ADAPT_PIOC_DISABLED}}
#define  PCIE_PORT_DATA_INITIALIZER_V2(mPortPresent, mChannelType, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mResetId, mClkPmSupport) \
{mPortPresent, mChannelType, mDevAddress, mDevFunction, mMaxLinkSpeed, mAspm, mHotplug, mResetId, {0, mMaxLinkCap, 0, mClkPmSupport}, {0, 0, 0}, EndpointDetect, \
{ADAPT_IOC_ENABLED, ADAPT_DFE_CONTROL_DISABLED, ADAPT_LEQ_CONTROL_DC_GAIN_POLE, ADAPT_DOC_DISABLED, ADAPT_FOMC_ENABLED, ADAPT_PIOC_DISABLED}}
#define  PCIE_PORT_DATA_INITIALIZER_GEN3(mPortPresent, mChannelType, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mResetId, mClkPmSupport, \
mInitOffsetCancellation, mDFEControl, mLEQControl, mDynamicOffsetCalibration, mFOMCalculation, mPIOffsetCalibration) \
{mPortPresent, mChannelType, mDevAddress, mDevFunction, mMaxLinkSpeed, mAspm, mHotplug, mResetId, {0, mMaxLinkCap, 0, mClkPmSupport}, {0, 0, 0}, EndpointDetect, \
{mInitOffsetCancellation, mDFEControl, mLEQControl, mDynamicOffsetCalibration, mFOMCalculation, mPIOffsetCalibration}}
#define  PCIE_DDI_DATA_INITIALIZER(mConnectorType, mAuxIndex, mHpdIndex ) \
{mConnectorType, mAuxIndex, mHpdIndex, {0, 0}, 0, 0}
#define  PCIE_DDI_DATA_INITIALIZER_V1(mConnectorType, mAuxIndex, mHpdIndex, mMapping0, mMapping1, mPNInversion) \
{mConnectorType, mAuxIndex, mHpdIndex, {mMapping0, mMapping1}, mPNInversion, 0}
#define  PCIE_DDI_DATA_INITIALIZER_V2(mConnectorType, mAuxIndex, mHpdIndex, mMapping0, mMapping1, mPNInversion, mFlags) \
{mConnectorType, mAuxIndex, mHpdIndex, {mMapping0, mMapping1}, mPNInversion, mFlags}

#endif // _AGESA_H_

