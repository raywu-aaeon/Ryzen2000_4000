/* $NoKeywords:$ */
/**
 * @file
 *
 * Agesa structures and definitions
 *
 * Contains AMD AGESA core interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
 * @e \$Revision: 317069 $   @e \$Date: 2015-04-20 11:25:50 -0700 (Mon, 20 Apr 2015) $
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


#ifndef _FCHXGBE_H_
#define _FCHXGBE_H_

#pragma pack (push, 1)

///
/// XGBE Port structure
///
typedef struct {
  BOOLEAN               XgbePortConfig;                 ///< XGbE controller Port Config Enable/disable
  UINT8                 XgbePortPlatformConfig;         ///< Platform Config
                                                        ///  @li   <b>0000</b> - Reserved
                                                        ///  @li   <b>0001</b> - 10G/1G Backplane
                                                        ///  @li   <b>0010</b> - 2.5G Backplane
                                                        ///  @li   <b>0011</b> - 1000Base-T
                                                        ///  @li   <b>0100</b> - 1000Base-X
                                                        ///  @li   <b>0101</b> - NBase-T
                                                        ///  @li   <b>0110</b> - 10GBase-T
                                                        ///  @li   <b>0111</b> - 10GBase-X
                                                        ///  @li   <b>1000</b> - SFP+
  UINT8                 XgbePortSupportedSpeed;         ///< Indicated Ethernet speeds supported on platform
                                                        ///  @li   <b>1xxx</b> - 10G
                                                        ///  @li   <b>x1xx</b> - 2.5G
                                                        ///  @li   <b>xx1x</b> - 1G
                                                        ///  @li   <b>xxx1</b> - 100M
  UINT8                 XgbePortConnectedType;          ///< PHY connected type
                                                        ///  @li   <b>000</b> - Port not used
                                                        ///  @li   <b>001</b> - SFP+
                                                        ///  @li   <b>010</b> - MDIO
                                                        ///  @li   <b>100</b> - Backplane connection
  UINT8                 XgbePortMdioId;                 ///< MDIO ID of the PHY associated with this port
  UINT8                 XgbePortMdioResetType;          ///< MDIO PHY reset type
                                                        ///  @li   <b>00</b> - None
                                                        ///  @li   <b>01</b> - I2C GPIO
                                                        ///  @li   <b>10</b> - Integrated GPIO
                                                        ///  @li   <b>11</b> - Reserved
  UINT8                 XgbePortResetGpioNum;           ///< GPIO used to control the reset
  UINT8                 XgbePortMdioResetI2cAddress;    ///< I2C address of PCA9535 MDIO reset GPIO
  UINT8                 XgbePortSfpI2cAddress;          ///< I2C address of PCA9535 for SFP
  UINT8                 XgbePortSfpTxFaultGpio;         ///< GPIO number for SFP+ TX_FAULT
  UINT8                 XgbePortSfpRsGpio;              ///< GPIO number for SFP+ RS
  UINT8                 XgbePortSfpModAbsGpio;          ///< GPIO number for SFP+ Mod_ABS
  UINT8                 XgbePortSfpRxLosGpio;           ///< GPIO number for SFP+ Rx_LOS
  UINT8                 XgbePortSfpGpioMask;            ///< GPIO Mask for SFP+
                                                        ///  @li   <b>1xxx</b> - Rx_LOS not supported
                                                        ///  @li   <b>x1xx</b> - Mod_ABS not supported
                                                        ///  @li   <b>xx1x</b> - RS not supported
                                                        ///  @li   <b>xxx1</b> - TX_FAULT not supported
  UINT8                 XgbePortSfpTwiAddress;          ///< Address of PCA9545 I2C multiplexor
  UINT8                 XgbePortSfpTwiBus;              ///< Downstream channel of PCA9545
  BOOLEAN               XgbaPortRedriverPresent;        ///< Redriver Present or not
  UINT8                 Reserve0[3];                    ///< Reserved
  UINT8                 XgbaPortRedriverModel;          ///< Redriver Model
                                                        ///  @li   <b>00</b> - InPhi 4223
                                                        ///  @li   <b>01</b> - InPhi 4227
  UINT8                 XgbaPortRedriverInterface;      ///< Redriver Interface
                                                        ///  @li   <b>00</b> - MDIO
                                                        ///  @li   <b>01</b> - I2C
  UINT8                 XgbaPortRedriverAddress;        ///< Redriver Address
  UINT8                 XgbaPortRedriverLane;           ///< Redriver Lane
  UINT8                 XgbaPortPadGpio;                ///< Portx_GPIO Pad selection
                                                        ///  @li   <b>001</b> - MDIO0 pin
                                                        ///  @li   <b>010</b> - MDIO1 pin
                                                        ///  @li   <b>100</b> - SFP pin
  UINT8                 XgbaPortPadMdio;                ///< Portx_Mdio Pad selection
                                                        ///  @li   <b>001</b> - MDIO0 pin
                                                        ///  @li   <b>010</b> - MDIO1 pin
                                                        ///  @li   <b>100</b> - SFP pin
  UINT8                 XgbaPortPadI2C;                 ///< Portx_I2C Pad selection
                                                        ///  @li   <b>001</b> - MDIO0 pin
                                                        ///  @li   <b>010</b> - MDIO1 pin
                                                        ///  @li   <b>100</b> - SFP pin
  UINT8                 Reserve1;                       ///< Reserved
} FCH_XGBE_PORT;

///
/// XGBE MAC Address
///
typedef struct {
  UINT32                XgbePortMacAddressLow;          ///< XGbE controller Port MAC address
  UINT32                XgbePortMacAddressHigh;         ///< XGbE controller Port MAC address
} FCH_XGBE_MAC;

///
/// XGBE Configure structure
///
typedef struct {
  FCH_XGBE_PORT         Port[4];                        ///
  FCH_XGBE_MAC          Mac[4];                         ///
  BOOLEAN               XgbeMdio0Enable;                ///< XGbe controller Sideband MDIO0 enable/disable
  BOOLEAN               XgbeMdio1Enable;                ///< XGbe controller Sideband MDIO1 enable/disable
  BOOLEAN               XgbeSfpEnable;                  ///< XGbe controller Sideband SFP enable/disable
  UINT32                MaxPortNum;                     ///
} FCH_XGBE;

#pragma pack (pop)

#endif // _FCHXGBE_H_

