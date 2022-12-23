/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#ifndef _AMD_CPM_OEM_INIT_PEIM_H_
#define _AMD_CPM_OEM_INIT_PEIM_H_

#define AMD_CPM_OEM_REVISION    0x1080

#define GPIO_STICKY_DIS     0
#define GPIO_STICKY_EN      1
#define GPIO_FUNCTION_0     0
#define GPIO_FUNCTION_1     1
#define GPIO_FUNCTION_2     2
#define GPIO_FUNCTION_3     3
#define GPIO_FUNCTION_4     4
#define GPIO_FUNCTION_5     5
#define GPIO_FUNCTION_6     6
#define GPIO_FUNCTION_7     7
#define GPIO_PD_EN          0
#define GPIO_PU_EN          1
#define GPIO_PU_PD_DIS      2
#define GPIO_OUTPUT_LOW     0
#define GPIO_OUTPUT_HIGH    1
#define GPIO_INPUT          2
#define GPIO_NA             3


#define EVENT_DISABLE               0
#define EVENT_ENABLE                1
#define SCITRIG_LOW                 0
#define SCITRIG_HI                  1
#define SCITRIG_AUTO                3
#define SCILEVEL_EDGE               0
#define SCILEVEL_LEVEL              1
#define SMISCI_DISABLE              0
#define SMISCI_ENABLE               1
#define SCIS0_DISABLE               0
#define SCIS0_ENABLE                1
#define SCIMAP_00                   0
#define SCIMAP_01                   1
#define SCIMAP_02                   2
#define SCIMAP_03                   3
#define SCIMAP_04                   4
#define SCIMAP_05                   5
#define SCIMAP_06                   6
#define SCIMAP_07                   7
#define SCIMAP_08                   8
#define SCIMAP_09                   9
#define SCIMAP_10                   10
#define SCIMAP_11                   11
#define SCIMAP_12                   12
#define SCIMAP_13                   13
#define SCIMAP_14                   14
#define SCIMAP_15                   15
#define SCIMAP_16                   16
#define SCIMAP_17                   17
#define SCIMAP_18                   18
#define SCIMAP_19                   19
#define SCIMAP_20                   20
#define SCIMAP_21                   21
#define SCIMAP_22                   22
#define SCIMAP_23                   23
#define SMITRIG_LOW                 0
#define SMITRIG_HI                  1
#define SMICONTROL_DISABLE          0
#define SMICONTROL_SMI              1
#define SMICONTROL_NMI              2
#define SMICONTROL_IRQ13            3

#define MISC_BASE                   0xE00
#define FCH_MISC_REG00              0x00        // ClkCntrl0
#define FCH_MISC_REG04              0x04        // ClkCntrl1

// MXM defination
#define MXM_PRESENT                 0x3
#define MXM_DETECT_VALUE            0
#define MXM_RESET                   0x6
#define MXM_POWER_ENABLE            141
#define MXM_POWER_ON                142
#define MXM_POWER_GOOD              143

// SSD
#define SSD_RESET                   40          // FCH GPIO40
#define SSD_POWER_EN                23          // FCH GPIO23

// DT power control
#define DT_RESET                    0x6
#define DT_POWER_EN                 49

// WLAN
#define WLAN_RESET                  47          // ECRAM xB1[7] (BIT47)
#define WLAN_POWER_EN               34          // ECRAM xB0[2] (BIT34)
#define WLAN_RADIO_PERMITTED        33          // ECRAM xB0[1] (BIT33)
#define WLAN_Manual_EN              0x200 + 83  // ECRAM xB6[3] (BIT83)

// LAN
#define LAN_RESET                   44          // ECRAM xB1[4] (BIT44)
#define LAN_POWER_EN                50          // ECRAM xB2[2] (BIT50)
#define LAN_Manual_EN               0x200 + 85  // ECRAM xB6[5] (BIT85)

// WWAN
#define WWAN_RESET                  45          // ECRAM xB1[5] (BIT45)
#define WWAN_POWER_EN               38          // ECRAM xB0[6] (BIT38)
#define WWAN_POWER_OFF_L            6           // ECRAM xAC[6] (BIT6)
#define WWAN_CARD_POWER_OFF_L       37          // ECRAM xB0[5] (BIT37)
#define WWAN_RADIO_PERMITTED        65          // ECRAM xB6[1] (BIT65)
#define WWAN_Manual_EN              0x200 + 84  // ECRAM xB6[4] (BIT84)


// WIFI
#define WIFI_RESET                  47
#define WIFI_POWER_EN               34
/*
// DEVICE_ID_RCAM
#define RCAM_POWER_EN               89    // AGPIO89 S0 Power Domain

// DEVICE_ID_FCAM
#define FCAM_POWER_EN               42    // EGPIO42 S5 Power Domain

//ZPODD defination
#define ZPODD_DETECT_PIN            0x200 + 6     // ECRAM xAC[6](BIT6)
#define ZPODD_DETECT_VALUE          0             // Low Active
#define ZPODD_POWER_CONTROL         0x200 + 52    // ECRAM xB2[4](BIT52)

#define ZPODD_DA_GPIO               8             // ECRAM xAD[0](BIT8)
#define ZPODD_PLUGIN_GPIO           6             // ECRAM xAC[6](BIT6)
#define ZPODD_DUMMY_EVENT           31            // Set to Dummy Gevent31
#define ZPODD_SATA_MASK             0x0F
#define ZPODD_SATA_PORT             0x01
#define ZPODD_DA_SOURCE             2             // ECRAM GPIO Pin
#define ZPODD_PLUGIN_SOURCE         2             // ECRAM GPIO Pin
#define ZPODD_DA_FALLING            0x42          // ECRAM _Q42 QEvent
#define ZPODD_DA_RISING             0x43          // ECRAM _Q43 QEvent
#define ZPODD_PLUGIN_FALLING        0x40          // ECRAM _Q40 QEvent
#define ZPODD_PLUGIN_RISING         0x41          // ECRAM _Q41 QEvent
*/

// NFC
#define NFC_POWER_CONTROL           0x40

// SD
#define SD_POWER_CONTROL_REVB       119

// HDMI over USB Type C Port 0 control
#define HDMI_USBC0_AUX              86          // ECRAM xB6[6] (BIT86)

// HDMI over USB Type C Port 1 control
#define HDMI_USBC1_AUX              87          // ECRAM xB6[7] (BIT87)

//DT device  defination
#define DTDEVICE_BRIDGE_DEV      0x02
#define DTDEVICE_BRIDGE_FUN      0x04
#define DTDEVICE_GEVENT          0x0B
#define DTDEVICE_DETECT          0x45            // AGPIO 69
#define DTDEVICE_DETECT_VALUE    0
#define DTDEVICE_TEST_GEVENT     0x10

//WLAN device  defination
#define WLANDEVICE_DETECT          0x200 + 34
#define WLANDEVICE_DETECT_VALUE    1

// LAN device  defination
#define LANDEVICE_DETECT            0x200 + 50
#define LANDEVICE_DETECT_VALUE      1

// WWAN device  defination
#define WWANDEVICE_DETECT           0x200 + 38
#define WWANDEVICE_DETECT_VALUE     1

// WIFI device  defination
#define WIFIDEVICE_DETECT           0x200 + 34
#define WIFIDEVICE_DETECT_VALUE     1

//Wireless Button defination
#define WIRELESS_BRIDGE_DEV1        0x02
#define WIRELESS_BRIDGE_FUN1        0x04
#define WIRELESS_BRIDGE_DEV2        0x02
#define WIRELESS_BRIDGE_FUN2        0x05
#define WIRELESS_BUTTON_GEVENT      0x07

#define TIEC_RAM_GPO2_OFFSET        0xAC
#define BoardRevA                   0
#define BoardRevB                   1

#define OEM_EC_CMD_STATUS_PORT      0x666
#define OEM_EC_CMD_DATA_PORT        0x662
#define OEM_EC_TIME_OUT             0x10000
#define OEM_EC_KEY_OBF              1
#define OEM_EC_KEY_IBF              2

#define EC_STATUS_INDEX             0xCF
#define TIEC_DC_TIMER               0xC7
#define TIEC_AC_TIMER               0xC8

#define AMD_PSP_KVM_DISABLE       0x0
#define AMD_PSP_KVM_ENABLE        0x1
#define AMD_PSP_KVM_AUTO          0x3

#define AMD_PSP_KVM_ABSOLUTE      0x0
#define AMD_PSP_KVM_SIMPLE        0x1

// delay is microseconds.
#define PHY_RESET_DELAY 10000


#define PHY_RESET_GPIO            0x1B
#define I2C_SMBUS_GPIO_19         0x13
#define I2C_SMBUS_GPIO_20         0x14

#define USB_PD_PORT0_CONTROL     0xFEDC6600
#define USB_PD_PORT1_CONTROL     0xFEDC6610

#define DxioInputParserGetNextDescriptor(Descriptor) (Descriptor != NULL ? ((((Descriptor->Flags & DESCRIPTOR_TERMINATE_LIST) != 0) ? NULL : (++Descriptor))) : NULL)

#define GPIO_CONTROL_REG(function, output, pullup, sticky) (function <= 3 ? 0x800 : 0) + \
                                                           (function << 8) +  \
                                                           (output < 3 ? (output < 2 ? output : 0x02) : 0x08) + \
                                                           ((sticky == 1) || (pullup < 3) ? ((sticky == 1 ? 0x10 : 0) + (pullup == 0 ? 0x40 : 0) + \
                                                           (pullup == 1 ? 0x20 : 0) + 0x80) : 0)

typedef enum {
  ETH_PORT_0 = 0x0,
  ETH_PORT_1,
  MAX_ETH_PORTS
} XGBE_MAX_PORTS;

typedef enum {
  XGBE_PHY_MODE_RJ45 = 0x0,
  XGBE_PHY_MODE_SFP_PLUS,
  XGBE_PHY_MODE_BACKPLANE
} XGBE_PORT_PHY_MODES;

typedef enum {
  XGBE_RESERVED = 0x0,
  XGBE_10G_1G_BACKPLANE,
  XGBE_2_5G_BACKPLANE,
  XGBE_SOLDERED_DOWN_1000BASE_T,
  XGBE_SOLDERED_DOWN_1000BASE_X,
  XGBE_SOLDERED_DOWN_NBASE_T,
  XGBE_SOLDERED_DOWN_10GBASE_T,
  XGBE_SOLDERED_DOWN_10GBASE_R,
  XGBE_SFP_PLUS_CONNECTOR
} XGBE_PORT_PROPERTY0_PLATFORM_CONFIG;

typedef enum {
  XGBE_PORT_SPEED_10G  = 0x8,
  XGBE_PORT_SPEED_2_5G = 0x4,
  XGBE_PORT_SPEED_1G   = 0x2,
  XGBE_PORT_SPEED_100M = 0x1,
} XGBE_PORT_PROPERTY0_SPEED_CONFIG;

typedef enum {
  XGBE_BACKPLANE_CONNECTION = 0x4,
  XGBE_CONNECTION_MDIO_PHY  = 0x2,
  XGBE_SFP_PLUS_CONNECTION  = 0x1,
  XGBE_PORT_NOT_USED        = 0x0
} XGBE_PORT_PORPERTY0_CONNECTION_TYPE;

typedef enum {
  XGBE_RXLOSS_NOT_SUPPORTED  = 0x8,
  XGBE_MODABS_NOT_SUPPORTED  = 0x4,
  XGBE_RS_NOT_SUPPORTED      = 0x2,
  XGBE_TXFAULT_NOT_SUPPORTED = 0x1,
} XGBE_PORT_PROPERTY3_SFP_GPIO_MASK;

typedef enum {
  XGBE_PCA9545A          = 0x1C,
  XGBE_PCA9545B          = 0x1A,
  XGBE_PCA9545C          = 0x16,
  XGBE_SFP_DIRECT_TO_I2C = 0x1F,
} XGBE_PORT_PROPERTY4_SFP_TWI_MUX_ADDR;

typedef union {
  UINT32 RegVal;
  struct {
    UINT32 Us1                    : 1;
    UINT32 Us0                    : 1;
    UINT32 Ts1                    : 1;
    UINT32 Ts0                    : 1;
    UINT32 Dp_Reserve             : 1;
    UINT32 Xtra_RfMux             : 3;
    UINT32 Usb_Pd_RfMux_Override  : 1;
    UINT32 Usb_Pd_Dp_Override     : 1;
    UINT32 Rsvd                   : 22;
  } Bits;
} USB_PD_PORT_CONTROL;

/// Physical or virtual on-board device Id.

typedef enum {
  DEVICE_ID_TEMP =                    0x00,
  DEVICE_ID_MXM =                     0x04,                       ///< Device Id for MXM
  DEVICE_ID_LAN =                     0x06,                       ///< Device Id for DT MPCIE
  DEVICE_ID_MPCIE1 =                  0x07,                       ///< Device Id for On-board LAN
  DEVICE_ID_DDI3 =                    0x08,                       ///< Device Id for DDI3
  DEVICE_ID_EXPRESSCARD =             0x09,                       ///< Device Id for Express Card
  DEVICE_ID_HDD0 =                    0x0A,                       ///< Device Id for HDD0
  DEVICE_ID_HDD2 =                    0x0B,                       ///< Device Id for HDD2
  DEVICE_ID_BT =                      0x0C,                       ///< Device Id for BlueTooth
  DEVICE_ID_WIRELESS =                0x0D,                       ///< Device Id for WLAN, WWAN, Mini PCIE on DMC slot
  DEVICE_ID_RADIO =                   0x0E,                       ///< Device Id for Radio of WLAN, WWAN, Mini PCIE on DMC slot
  DEVICE_ID_SWINGMODE =               0x10,                       ///< Device Id for virtual device to switch PEX_STD_SW#
  DEVICE_ID_POWERLEVEL =              0x11,                       ///< Device Id for virtual device to switch FCH_PWR_LV
  DEVICE_ID_VGAMUXSEL =               0x12,                       ///< Device Id for virtual device to switch VGA_MUX_SEL
  DEVICE_ID_DT =                      0x13,                       ///< Device Id for DT MPCIE
  DEVICE_ID_MPCIE2 =                  0x14,                       ///< Device Id for Mini PCIE 2
  DEVICE_ID_ODD =                     0x39,                       ///< Device Id for ODD
  DEVICE_ID_NFC =                     0x15,                       ///< Device Id for NFC
  DEVICE_ID_SD =                      0x16,                       ///< Device Id for SD
  DEVICE_ID_M2_CONNECT =              0X17,                       ///< Device M2 connect
  DEVICE_ID_M2_CONNECT2 =             0x18,                       ///< Device M2 connect2
  DEVICE_ID_WWAN =                    0x19,                       ///< Device Id for WWAN
  DEVICE_ID_DP0 =                     0x1A,                       ///< Device Id for Dp0
  DEVICE_ID_SSD =                     0x1B,                       ///< Device Id for SSD
  DEVICE_ID_RCAM =                    0x1C,                       ///< Device Id for Rear Camera
  DEVICE_ID_FCAM =                    0x1D,                       ///< Device Id for Front Camera
  DEVICE_ID_WLAN =                    0x1E,                       ///< Device Id for WLAN
  DEVICE_ID_LOM =                     0x1F,                       ///< Device Id for LoM
  DEVICE_ID_USB_TYPE_C0 =             0x20,                       ///< Device Id for USB Type C Port 0
  DEVICE_ID_USB_TYPE_C1 =             0x21,                       ///< Device Id for USB Type C Port 1
  DEVICE_ID_WIFI =                    0x22,                       ///< Device Id for WIFI
  DEVICE_ID_UMI,
} CPM_GPIO_DEVICE_ID;


/// Configuration values for RV GppClk in Fch

typedef enum {
  GPP_CLK0 =                          0x00,                       ///< GPP_CLK0
  GPP_CLK1 =                          0x01,                       ///< GPP_CLK1
  GPP_CLK4 =                          0x02,                       ///< GPP_CLK4
  GPP_CLK2 =                          0x03,                       ///< GPP_CLK2
  GPP_CLK3 =                          0x04,                       ///< GPP_CLK3
  GPP_CLK5 =                          0x05,                       ///< GPP_CLK5
  GPP_CLK6 =                          0x06,                       ///< GPP_CLK6
  GPP_SKIP =                          0xFE,                       ///< SKIP
} CPM_GPP_CLK;

/// Configuration values for SrcClk in ClkGen

typedef enum {
  SRC_CLK0 =                          0x00,                       ///< SRC0
  SRC_CLK1,                                                       ///< SRC1
  SRC_CLK2,                                                       ///< SRC2
  SRC_CLK3,                                                       ///< SRC3
  SRC_CLK4,                                                       ///< SRC4
  SRC_CLK5,                                                       ///< SRC5
  SRC_CLK6,                                                       ///< SRC6
  SRC_CLK7,                                                       ///< SRC7
  SRC_CLK8,                                                       ///< SRC8
  SRC_CLK9,                                                       ///< SRC9
  SRC_CLK10,                                                      ///< SRC10
  SRC_CLK11,                                                      ///< SRC11
  SRC_SKIP =                          0xFE,                       ///< SKIP
} CPM_SRC_CLK;

/// Configuration values for RV ClkReq

typedef enum {
  CLK_DISABLE =                       0x00,                       ///< CLK_DISABLE
  CLK_REQ0    =                       0x01,                       ///< CLK_REQ0
  CLK_REQ1    =                       0x02,                       ///< CLK_REQ1
  CLK_REQ2    =                       0x03,                       ///< CLK_REQ2
  CLK_REQ3    =                       0x04,                       ///< CLK_REQ3
  CLK_REQ4    =                       0x05,                       ///< CLK_REQ4
  CLK_REQ5    =                       0x06,                       ///< CLK_REQ5
  CLK_REQ6    =                       0x07,                       ///< CLK_REQ6
  CLK_ENABLE  =                       0xFF,                       ///< CLK_ENABLE
} CPM_CLK_REQ;

UINT8
OemEcRead (
  IN UINT8                        Index
  );

STATIC
EFI_STATUS
OemWaitKbcIbe (
  IN UINT16                     CommandState
  );

STATIC
EFI_STATUS
OemWaitKbcObf (
  IN UINT16                       CommandState
  );

STATIC
EFI_STATUS
OemReadKbc (
  IN UINT16                       CommandState,
  IN OUT UINT8                    *Data
  );

STATIC
EFI_STATUS
OemWriteKbc (
  IN UINT16                       CommandState,
  IN UINT8                        Data
  );

EFI_STATUS
EFIAPI
AmdXgbeMacAddr (
    IN CONST EFI_PEI_SERVICES     **PeiServices
  );

EFI_STATUS
EFIAPI
XgbeMdioPhyReset (
  IN CONST EFI_PEI_SERVICES     **PeiServices
  );

EFI_STATUS
EFIAPI
ConfigureRfMuxforDPPorts (
  IN CONST EFI_PEI_SERVICES** PeiServices
  );

EFI_STATUS
EFIAPI
ProgramI2CGpioToSmbus (
  IN CONST EFI_PEI_SERVICES** PeiServices
  );

EFI_STATUS
EFIAPI
AmdCpmOemInitPeimNotifyCallback (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

EFI_STATUS
EFIAPI
ConfigureEthernetDxioPorts (
  IN DXIO_PORT_DESCRIPTOR** DxioPort,
  IN UINT8 PhyMode
  );

EFI_STATUS
EFIAPI
UpdateXgbeFchPcds (
  IN EFI_PEI_SERVICES** PeiServices,
  IN DXIO_PORT_DESCRIPTOR** DxioPort
  );
#endif
