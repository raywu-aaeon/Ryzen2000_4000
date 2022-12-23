/* $NoKeywords:$ */
/**
 * @file
 *
 * Config Fch xGbE controller
 *
 * Init Usb Controller features (PEI phase).
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 309083 $   @e \$Date: 2014-12-09 09:28:24 -0800 (Tue, 09 Dec 2014) $
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
*/
#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE PROC_FCH_TAISHAN_TSXGBE_TSXGBELIB_FILECODE

//<Embedded_Override_Start>
//
// MAC_HW_Feature1 Register Bitfields:
//

#define SMN_GMAC0_MAC_HW_Feature1_ADDRESS                      0x16300120UL
#define SMN_GMAC1_MAC_HW_Feature1_ADDRESS                      0x16320120UL


/// Bitfield Description : MTL Receive FIFO Size.
/// This field contains the configured value of MTL Rx FIFO in bytes expressed as Log to base 2 minus 7, that is, Log2(RXFIFO_SIZE) ' 7:
/// -  00011: 1,024 bytes
/// -  00100: 2,048 bytes
/// -  00101: 4,096 bytes
/// -  00110: 8,192 bytes
/// -  00111: 16,384 bytes
/// -  01000: 32 KB
/// -  01001: 64 KB
/// -  01010: 128 KB
/// -  01011: 256 KB
/// -  01100'11111:
#define MAC_HW_Feature1_RXFIFOSIZE_OFFSET                      0
#define MAC_HW_Feature1_RXFIFOSIZE_WIDTH                       5
#define MAC_HW_Feature1_RXFIFOSIZE_MASK                        0x1f


/// Bitfield Description : MTL Transmit FIFO Size.
/// This field contains the configured value of MTL Tx FIFO in bytes expressed as Log to base 2 minus 7, that is, Log2(TXFIFO_SIZE) ' 7:
/// -  00011: 1,024 bytes
/// -  00100: 2,048 bytes
/// -  00101: 4,096 bytes
/// -  00110: 8,192 bytes
/// -  00111: 16,384 bytes
/// -  01000: 32 KB
/// -  01001: 64 KB
/// -  01010: 128 KB
/// -  01011: 256 KB
/// -  01100-11111:
#define MAC_HW_Feature1_TXFIFOSIZE_OFFSET                      6
#define MAC_HW_Feature1_TXFIFOSIZE_WIDTH                       5
#define MAC_HW_Feature1_TXFIFOSIZE_MASK                        0x7c0


#define FCH_SS_XGBE_PORT_PROPERTY2_RX_BUF_SIZE_OFFSET          16
#define FCH_SS_XGBE_PORT_PROPERTY2_TX_BUF_SIZE_OFFSET          0

#define FCH_SS_XGBE_PORT_PROPERTY2_BUF_COV_IN_16K_BITS          5

//
// MAC_HW_Feature2 Register Bitfields:
//

#define SMN_GMAC0_MAC_HW_Feature2_ADDRESS                      0x16300124UL
#define SMN_GMAC1_MAC_HW_Feature2_ADDRESS                      0x16320124UL

/// Bitfield Description : Number of MTL Receive Queues.
/// This field indicates the number of MTL Receive queues:
/// -  0000: 1 MTL Rx Queue
/// -  0001: 2 MTL Rx Queues
/// -  ..
/// -  1011: 12 MTL Rx
#define MAC_HW_Feature2_RXQCNT_OFFSET                          0
#define MAC_HW_Feature2_RXQCNT_WIDTH                           4
#define MAC_HW_Feature2_RXQCNT_MASK                            0xf

/// Bitfield Description : Number of MTL Transmit Queues.
/// This field indicates the number of MTL Transmit queues:
/// -  0000: 1 MTL Tx Queue
/// -  0001: 2 MTL Tx Queues
/// -  ..
/// -  1111: 16 MTL Tx
#define MAC_HW_Feature2_TXQCNT_OFFSET                          6
#define MAC_HW_Feature2_TXQCNT_WIDTH                           4
#define MAC_HW_Feature2_TXQCNT_MASK                            0x3c0

/// Bitfield Description : Number of DMA Receive Channels.
/// This field indicates the number of DMA Receive channels:
/// -  0000: 1 DMA Rx Channel
/// -  0001: 2 DMA Rx Channels
/// -  ..
/// -  1111: 16 DMA Rx
#define MAC_HW_Feature2_RXCHCNT_OFFSET                         12
#define MAC_HW_Feature2_RXCHCNT_WIDTH                          4
#define MAC_HW_Feature2_RXCHCNT_MASK                           0xf000


/// Bitfield Description : Number of DMA Transmit Channels.
/// This field indicates the number of DMA Transmit channels:
/// -  0000: 1 DMA Tx Channel
/// -  0001: 2 DMA Tx Channels
/// -  ..
/// -  1111: 16 DMA Tx
#define MAC_HW_Feature2_TXCHCNT_OFFSET                         18
#define MAC_HW_Feature2_TXCHCNT_WIDTH                          4
#define MAC_HW_Feature2_TXCHCNT_MASK                           0x3c0000



#define FCH_PORT_PROPERTY1_TX_QUEUE_OFFSET                     0
#define FCH_PORT_PROPERTY1_RX_QUEUE_OFFSET                     8
#define FCH_PORT_PROPERTY1_TX_DMA_CHANNEL_OFFSET               16
#define FCH_PORT_PROPERTY1_RX_DMA_CHANNEL_OFFSET               24
//<Embedded_Override_End>

/**
 * FchSsXgbePortClockGate - Clock Gate xGbE port
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] Port       Port Number in current Die
 *
 */
VOID
FchSsXgbePortClockGate (
  IN  UINT32   DieBusNum,
  IN  UINT8    Port
  )
{
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_CLK_GATE + Port * 4, ~(UINT32)BIT0, BIT0, NULL);
}

/**
 * FchSsXgbePortPlatformConfig - Initialize xGbE port
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] PortNum    Port Number in current Die
 * @param[in] SystemPort Port Number in the system
 * @param[in] PortData   Port configuration structure pointer.
 *
 */
VOID
FchSsXgbePortPlatformConfig (
  IN  UINT32   DieBusNum,
  IN  UINT8    PortNum,
  IN  UINT32   SystemPort,
  IN  VOID     *PortData
  )
{
  UINT32                 XgbePortProperty;
  FCH_XGBE_PORT          *FchXgbePort;
//<Embedded_Override_Start> 
  UINT32                 MacHwFeature;
//<Embedded_Override_End>

  FchXgbePort = (FCH_XGBE_PORT *)PortData;

  SystemPort &= 0xFF;
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY0 + PortNum * 0x20, 0xFFFFFF00, SystemPort, NULL);

  XgbePortProperty = (UINT32) (FchXgbePort->XgbePortPlatformConfig) << 8;
  XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSupportedSpeed) << 23;
  XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortConnectedType) << 28;
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY0 + PortNum * 0x20, 0x0870F0FF, XgbePortProperty, NULL);
  
//<Embedded_Override_Start>  
  //FCH_SS_XGBE_PORT0_PROPERTY1
  /// -  0000: 1 DMA Rx Channel
  /// -  0001: 2 DMA Rx Channels
  /// -  ..
  /// -  1111: 16 DMA Rx
  FchSmnRead (DieBusNum, SMN_GMAC0_MAC_HW_Feature2_ADDRESS + PortNum * 0x20000, &MacHwFeature, NULL);
  XgbePortProperty =  (((( MacHwFeature & MAC_HW_Feature2_TXQCNT_MASK ) >> MAC_HW_Feature2_TXQCNT_OFFSET) + 1) << FCH_PORT_PROPERTY1_TX_QUEUE_OFFSET)
                        | (((( MacHwFeature & MAC_HW_Feature2_RXQCNT_MASK ) >> MAC_HW_Feature2_RXQCNT_OFFSET) + 1)  << FCH_PORT_PROPERTY1_RX_QUEUE_OFFSET)
						| (((( MacHwFeature & MAC_HW_Feature2_TXCHCNT_MASK ) >> MAC_HW_Feature2_TXCHCNT_OFFSET) + 1)  << FCH_PORT_PROPERTY1_TX_DMA_CHANNEL_OFFSET)
						| (((( MacHwFeature & MAC_HW_Feature2_RXCHCNT_MASK ) >> MAC_HW_Feature2_RXCHCNT_OFFSET) + 1)  << FCH_PORT_PROPERTY1_RX_DMA_CHANNEL_OFFSET);
  
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY1 + PortNum * 0x20, 0x0, XgbePortProperty, NULL);
  
  //FCH_SS_XGBE_PORT0_PROPERTY2
  FchSmnRead (DieBusNum, SMN_GMAC0_MAC_HW_Feature1_ADDRESS + PortNum * 0x20000, &MacHwFeature, NULL);
  XgbePortProperty =  ((((MacHwFeature & MAC_HW_Feature1_RXFIFOSIZE_MASK) >> MAC_HW_Feature1_RXFIFOSIZE_OFFSET) -  FCH_SS_XGBE_PORT_PROPERTY2_BUF_COV_IN_16K_BITS ) << FCH_SS_XGBE_PORT_PROPERTY2_RX_BUF_SIZE_OFFSET ) 
                      | ((((MacHwFeature & MAC_HW_Feature1_TXFIFOSIZE_MASK) >> MAC_HW_Feature1_TXFIFOSIZE_OFFSET) - FCH_SS_XGBE_PORT_PROPERTY2_BUF_COV_IN_16K_BITS) << FCH_SS_XGBE_PORT_PROPERTY2_TX_BUF_SIZE_OFFSET ) ;
  
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY2 + PortNum * 0x20, 0x0, XgbePortProperty, NULL);
//<Embedded_Override_End>

  if (FchXgbePort->XgbePortConnectedType == 1) {
    //
    // SFP+
    //
    XgbePortProperty = (UINT32) (FchXgbePort->XgbePortSfpI2cAddress) << 8;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpTxFaultGpio) << 12;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpRsGpio) << 16;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpModAbsGpio) << 20;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpRxLosGpio) << 24;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpGpioMask) << 28;
    FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY3 + PortNum * 0x20, 0x000008FF, XgbePortProperty, NULL);

    XgbePortProperty = (UINT32) (FchXgbePort->XgbePortSfpTwiAddress & 0x7);
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpTwiBus) << 4;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortSfpTwiAddress & 0xF8) << 5;
    FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY4 + PortNum * 0x20, 0x000008FF, XgbePortProperty, NULL);

    //
    // I2C PAD MUX
    //
    FchSmnRW (DieBusNum, FCH_SS_XGBE_PAD_MUX0, ~(UINT32)(0x0F << (PortNum * 8)), (UINT32) (FchXgbePort->XgbaPortPadI2C) << (PortNum * 8), NULL);
  } else if(FchXgbePort->XgbePortConnectedType == 2) {
    //
    // MDIO
    //
    XgbePortProperty = (UINT32) (FchXgbePort->XgbePortMdioId) << 16;
    FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY0 + PortNum * 0x20, 0xFFF0FFFF, XgbePortProperty, NULL);

    XgbePortProperty = (UINT32) (FchXgbePort->XgbePortMdioResetType);
    if (FchXgbePort->XgbePortMdioResetType == 1) {
      //
      // I2C GPIO
      //
      XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortMdioResetI2cAddress) << 8;
      XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortResetGpioNum) << 12;
      FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY3 + PortNum * 0x20, 0xFFFF08FC, XgbePortProperty, NULL);

      //
      // I2C PAD MUX
      //
      FchSmnRW (DieBusNum, FCH_SS_XGBE_PAD_MUX0, ~(UINT32)(0x0F << (PortNum * 8)), (UINT32) (FchXgbePort->XgbaPortPadI2C) << (PortNum * 8), NULL);
    } else if (FchXgbePort->XgbePortMdioResetType == 2) {
      //
      // Integrated GPIO
      //
      XgbePortProperty |= (UINT32) (FchXgbePort->XgbePortResetGpioNum) << 4;
      FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY3 + PortNum * 0x20, 0xFFFFFFCC, XgbePortProperty, NULL);

      // GPIO PAD
      FchSmnRW (DieBusNum, FCH_SS_XGBE_PAD_MUX1, ~(UINT32)(0x0F << (PortNum * 8)), (UINT32) (FchXgbePort->XgbaPortPadGpio) << (PortNum * 8), NULL);
    }

    //
    // MDIO PAD MUX
    //
    FchSmnRW (DieBusNum, FCH_SS_XGBE_PAD_MUX0, ~(UINT32)(0xF0 << (PortNum * 8)), (UINT32) (FchXgbePort->XgbaPortPadMdio) << (PortNum * 8 + 4), NULL);
  }

  if (FchXgbePort->XgbaPortRedriverPresent) {
    //
    // Redriver
    //
    XgbePortProperty = (UINT32) (FchXgbePort->XgbaPortRedriverAddress) << 16;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbaPortRedriverInterface) << 23;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbaPortRedriverLane) << 24;
    XgbePortProperty |= (UINT32) (FchXgbePort->XgbaPortRedriverModel) << 28;
    XgbePortProperty |= BIT31;
    FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_PROPERTY4 + PortNum * 0x20, 0x0000FFFF, XgbePortProperty, NULL);
  }
}

/**
 * FchSsXgbePortMacAddress - Initialize xGbE port
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] PortNum    Port Number in current Die
 * @param[in] MacData   Port configuration structure pointer.
 *
 */
VOID
FchSsXgbePortMacAddress (
  IN  UINT32   DieBusNum,
  IN  UINT8    PortNum,
  IN  VOID     *MacData
  )
{
  UINT32                 FchXgbeMacAddress;
  FCH_XGBE_MAC           *FchXgbePortMac;

  FchXgbePortMac = (FCH_XGBE_MAC *)MacData;
  FchXgbeMacAddress = FchXgbePortMac->XgbePortMacAddressLow;
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_MAC_ADDR_LOW + PortNum * 0x8, 0x00, FchXgbeMacAddress, NULL);

  FchXgbeMacAddress = FchXgbePortMac->XgbePortMacAddressHigh;
  FchXgbeMacAddress &= 0xFFFF;
  FchXgbeMacAddress |= BIT31;
  FchSmnRW (DieBusNum, FCH_SS_XGBE_PORT0_MAC_ADDR_HIGH + PortNum * 0x8, 0x00, FchXgbeMacAddress, NULL);
}

/**
 * FchSsXgbePortPtpInit - Initialize xGbE port
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] PortNum    Port Number in current Die
 * @param[in] PortData   Port configuration structure pointer.
 *
 */
VOID
FchSsXgbePortPtpInit (
  IN  UINT32   DieBusNum,
  IN  UINT8    PortNum,
  IN  VOID     *PortData
  )
{

}

/**
 * FchSsXgbePadEnable - Enable Pad IOMUX
 *
 *
 * @param[in] DieBusNum  Bus Number of current Die
 * @param[in] XgbeData   Pointer to xGbE data structure
 *
 */
VOID
FchSsXgbePadEnable (
  IN  UINT32   DieBusNum,
  IN  VOID     *XgbeData
  )
{
  FCH_XGBE     *LocalXgbeData;
  LocalXgbeData = (FCH_XGBE *)XgbeData;

  if (LocalXgbeData->XgbeMdio0Enable) {
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x0A,0x00, 0x3, NULL);
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x28,0x00, 0x2, NULL); //PLAT-18025
  }

  if (LocalXgbeData->XgbeMdio1Enable) {
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x09,0x00, 0x2, NULL);
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x17,0x00, 0x2, NULL);
  }

//<Embedded_Override_Start>
#if 0
  if (LocalXgbeData->XgbeSfpEnable) {
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x93,0x00, 0x1, NULL);
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x94,0x00, 0x1, NULL);
  }
#endif

  if (LocalXgbeData->XgbeSfpEnable) {
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x09,0x00, 0x2, NULL);
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x17,0x00, 0x2, NULL);

    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x0A,0x00, 0x3, NULL);
    FchSmnRW8 (DieBusNum, FCH_SS_SMN_IOMUX_BASE + 0x28,0x00, 0x2, NULL); //PLAT-18025
  }
//<Embedded_Override_End>
 
}

