/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH registers definition
 *
 *
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
#define TAISHAN_SD_BUS_DEV_FUN               ((0x14 << 3) + 6)      // SD Controller
#define TAISHAN_SD_PCI_DEV                   20
#define TAISHAN_SD_PCI_FUNC                  6

#define TAISHAN_BUSAPORT_BUS_DEV_FUN         ((0x8 << 3) + 1)
#define TAISHAN_SATA_DEV_FUN                 ((0x0 << 3) + 2)
#define TAISHAN_SATA_DEV                     0
#define TAISHAN_SATA_FUN                     2
#define TAISHAN_SATA_PORT_NUM                8

#define TAISHAN_MAX_FCH_SUPPORT              8

#define TAISHAN_FCH_SATA_DID                 0x7901
#define TAISHAN_FCH_SATA_AHCI_DID            0x7901
#define TAISHAN_FCH_SATA_AMDAHCI_DID         0x7904
#define TAISHAN_FCH_SATA_RAID_DID            0x7916
#define TAISHAN_FCH_SATA_RAID_DID2           0x7917

#define TAISHAN_FCH_USB_XHCI_DID             0x7914      // Dev 0x10 Func 0
#define TAISHAN_FCH_SMBUS_DID                0x790B      // Dev 0x14 Func 0
#define TAISHAN_FCH_LPC_DID                  0x790E      // Dev 0x14 Func 3
#define TAISHAN_FCH_SD_DID                   0x7906      // Dev 0x14 Func 7

//USB RSMU registers
#define FCH_TS_USB_RSMU_PGFSM_CNTL           0x0004D520ul        //0x0004D520ul
#define FCH_TS_USB_RSMU_PGFSM_WR_DATA        0x0004D524ul        //0x0004D524ul
#define FCH_TS_USB_RSMU_PGFSM_RD_DATA        0x0004D528ul        //0x0004D528ul

//USB3 IP registers
#define FCH_TS_USB_GUCTL1                    0x16C0C11Cul        //0x16C0C11C
#define FCH_TS_USB_GUCTL                     0x16C0C12Cul        //0x16C0C12C
#define FCH_TS_USB_GUSB3PIPECTL0             0x16C0C2C0ul        //0x16C0C2C0
#define FCH_TS_USB_GUSB3PIPECTL1             0x16C0C2C4ul        //0x16C0C2C4
#define FCH_TS_USB_GUSB3PIPECTL2             0x16C0C2C8ul        //0x16C0C2C8
#define FCH_TS_USB_GUSB3PIPECTL3             0x16C0C2CCul        //0x16C0C2CC

//USB3 CONTAINER Registers
#define FCH_TS_SMN_USB_CONTAINER             0x16D80000ul
#define FCH_TS_USB_SHADOWED_POWERSTATE       FCH_TS_SMN_USB_CONTAINER + 0x14         //0x14
#define FCH_TS_USB_RESET                     FCH_TS_SMN_USB_CONTAINER + 0x100        //0x100
  #define FCH_TS_USB_S5_RESET                 (1 << 0x00)
  #define FCH_TS_USB_CONTROLLER_RESET         (1 << 0x01)
  #define FCH_TS_USB_PHY_RESET                (1 << 0x02)
#define FCH_TS_USB_PGFSM_OVERRIDE            FCH_TS_SMN_USB_CONTAINER + 0x104        //0x104
#define FCH_TS_USB_CURRENT_PWR_STS           FCH_TS_SMN_USB_CONTAINER + 0x108        //0x108
#define FCH_TS_USB_DEVICE_REMOVABLE          FCH_TS_SMN_USB_CONTAINER + 0x114        //0x114
#define FCH_TS_USB_INTERRUPT_CONTROL         FCH_TS_SMN_USB_CONTAINER + 0x118        //0x118
#define FCH_TS_USB_PORT_OCMAPPING0           FCH_TS_SMN_USB_CONTAINER + 0x120        //0x120
#define FCH_TS_USB_PORT_DISABLE0             FCH_TS_SMN_USB_CONTAINER + 0x128        //0x128
#define FCH_TS_USB_PORT_CONTROL              FCH_TS_SMN_USB_CONTAINER + 0x130        //0x130

#define FCH_TS_USB_PHY0_RX_OVRD_IN_HI        0x16D04018ul        //0x4018
#define FCH_TS_USB_PHY1_RX_OVRD_IN_HI        0x16D04418ul        //0x4418
#define FCH_TS_USB_PHY2_RX_OVRD_IN_HI        0x16D04818ul        //0x4818
#define FCH_TS_USB_PHY3_RX_OVRD_IN_HI        0x16D04C18ul        //0x4C18
  #define RX_EQ_OVRD                         BIT11
  #define RX_EQ                              (BIT8 + BIT9 + BIT10)
  #define RX_EQ_EN_OVRD                      BIT7
  #define RX_EQ_EN                           BIT6
#define FCH_TS_USB_PHY0_PHYINTERNALLANEREGISTER        0x16D04098ul        //0x4098
#define FCH_TS_USB_PHY1_PHYINTERNALLANEREGISTER        0x16D04498ul        //0x4498
#define FCH_TS_USB_PHY2_PHYINTERNALLANEREGISTER        0x16D04898ul        //0x4898
#define FCH_TS_USB_PHY3_PHYINTERNALLANEREGISTER        0x16D04C98ul        //0x4C98

#define FCH_TS_USBPHYCTRLx0004_PHYPARACTL1             0x16D08004ul        //0x8004
#define FCH_TS_USBPHYCTRLx0008_PHYPARACTL2             0x16D08008ul        //0x8008

#define FCH_TS_USB_PHY0_PHYCFG0              0x16D08200ul        //0x8200
#define FCH_TS_USB_PHY1_PHYCFG0              0x16D08600ul        //0x8600
#define FCH_TS_USB_PHY2_PHYCFG0              0x16D08A00ul        //0x8A00
#define FCH_TS_USB_PHY3_PHYCFG0              0x16D08E00ul        //0x8E00
#define FCH_TS_USB_PHY0_LANEPARACTL0         0x16D0C000ul        //0xC000
#define FCH_TS_USB_PHY1_LANEPARACTL0         0x16D0C400ul        //0xC400
#define FCH_TS_USB_PHY2_LANEPARACTL0         0x16D0C800ul        //0xC800
#define FCH_TS_USB_PHY3_LANEPARACTL0         0x16D0CC00ul        //0xCC00
#define FCH_TS_USB_PHY0PARACTL2              0x16D08008ul        //0x8008
#define FCH_TS_USB_PHY1PARACTL2              0x16D08408ul        //0x8408
#define FCH_TS_USB_PHY2PARACTL2              0x16D08808ul        //0x8808
#define FCH_TS_USB_PHY3PARACTL2              0x16D08C08ul        //0x8C08

#define FCH_TS_USB_NBIF_STRAP0               0x10134600ul
#define FCH_TS_USB_SMN_PCICFG                0x10143000ul

//SATA RSMU registers
#define FCH_TS_SMN_SATA_RSMU_BASE            0x010A8000ul
#define FCH_TS_SMN_SATA_CONTROL_RSMU         0x03100000ul
#define FCH_TS_SMN_SATA_CONTROL_BAR5         0x03101000ul
#define FCH_TS_SMN_SATA_CONTROL_SLOR         0x03101800ul

#define FCH_TS_SATA_RSMU_COLD_RESETB         FCH_TS_SMN_SATA_RSMU_BASE + 0x04
#define FCH_TS_SATA_RSMU_HARD_RESETB         FCH_TS_SMN_SATA_RSMU_BASE + 0x08

#define FCH_TS_SATA_MISC_CONTROL             FCH_TS_SMN_SATA_CONTROL_RSMU + 0x00     //0x00
#define FCH_TS_SATA_OOB_CONTROL              FCH_TS_SMN_SATA_CONTROL_RSMU + 0x02     //0x02
#define FCH_TS_SATA_AOAC_CONTROL             FCH_TS_SMN_SATA_CONTROL_RSMU + 0x04     //0x04
#define FCH_TS_SATA_EVENT_SELECT             FCH_TS_SMN_SATA_CONTROL_RSMU + 0x08     //0x08
#define FCH_TS_SATA_NBIF_CONTROL             FCH_TS_SMN_SATA_CONTROL_RSMU + 0x0A     //0x0A

#define FCH_TS_SMN_SATA_NBIF_STRAP0          0x10234400ul
#define FCH_TS_SMN_SATA_NBIF_STRAP3          0x1023440Cul
#define FCH_TS_SMN_SATA_NBIF_STRAP13         0x10234434ul

#define FCH_TS_SATA_SMN_PCICFG               0x10242000ul

//xGbE registers
#define FCH_TS_SMN_XGBE_MMIO0_BASE           0x1631F000ul

#define FCH_TS_XGBE_PAD_MUX0                 FCH_SMN_XGBE_MMIO0_BASE + 0x00
#define FCH_TS_XGBE_PAD_MUX1                 FCH_SMN_XGBE_MMIO0_BASE + 0x04
#define FCH_TS_XGBE_PORT0_CLK_GATE           FCH_SMN_XGBE_MMIO0_BASE + 0x30
#define FCH_TS_XGBE_PORT0_PROPERTY0          FCH_SMN_XGBE_MMIO0_BASE + 0x800
#define FCH_TS_XGBE_PORT0_PROPERTY1          FCH_SMN_XGBE_MMIO0_BASE + 0x804
#define FCH_TS_XGBE_PORT0_PROPERTY2          FCH_SMN_XGBE_MMIO0_BASE + 0x808
#define FCH_TS_XGBE_PORT0_PROPERTY3          FCH_SMN_XGBE_MMIO0_BASE + 0x80C
#define FCH_TS_XGBE_PORT0_PROPERTY4          FCH_SMN_XGBE_MMIO0_BASE + 0x810
#define FCH_TS_XGBE_PORT0_PROPERTY5          FCH_SMN_XGBE_MMIO0_BASE + 0x814
#define FCH_TS_XGBE_PORT0_MAC_ADDR_LOW       FCH_SMN_XGBE_MMIO0_BASE + 0x880
#define FCH_TS_XGBE_PORT0_MAC_ADDR_HIGH      FCH_SMN_XGBE_MMIO0_BASE + 0x884

#define FCH_TS_SMN_XGBE0_NBIF_STRAP0         0x10234800ul

//FCH register SMN address
#define FCH_TS_SMN_SMI_BASE                  0x02D01200ul
#define FCH_TS_SMN_IOMUX_BASE                0x02D01D00ul
#define FCH_TS_SMN_MISC_BASE                 0x02D01E00ul
#define FCH_TS_SMN_GPIO_BASE                 0x02D02500ul

#define FCH_TS_IRQ_INTA         0x00
#define FCH_TS_IRQ_INTB         0x01
#define FCH_TS_IRQ_INTC         0x02
#define FCH_TS_IRQ_INTD         0x03
#define FCH_TS_IRQ_GENINT2      0x05
#define FCH_TS_IRQ_SCI          0x10    // SCI
#define FCH_TS_IRQ_SMBUS0       0x11    // SMBUS0
#define FCH_TS_IRQ_ASF          0x12    // ASF
#define FCH_TS_IRQ_GBE0         0x14    // GBE0
#define FCH_TS_IRQ_GBE1         0x15    // GBE1
#define FCH_TS_IRQ_SD           0x17    // SD
#define FCH_TS_IRQ_SDIO         0x1A    // SDIO
#define FCH_TS_IRQ_GPIOa        0x21
#define FCH_TS_IRQ_GPIOb        0x22
#define FCH_TS_IRQ_GPIOc        0x23
#define FCH_TS_IRQ_USB_EMU      0x30    // AMD USB Emulation Interrupt
#define FCH_TS_IRQ_USB_DR0      0x31    // USB DualRole Intr0
#define FCH_TS_IRQ_USB_DR1      0x32    // USB DualRole Intr1
#define FCH_TS_IRQ_USB_XHCI0    0x34    // XHCI0
#define FCH_TS_IRQ_USB_SSIC     0x35    // SSIC
#define FCH_TS_IRQ_SATA         0x41    // SATA
#define FCH_TS_IRQ_UFS          0x42    // UFS
#define FCH_TS_IRQ_EMMC         0x43    // EMMC
#define FCH_TS_IRQ_GPIO         0x62    // GPIO
#define FCH_TS_IRQ_I2C0         0x70    // I2C0
#define FCH_TS_IRQ_I2C1         0x71    // I2C1
#define FCH_TS_IRQ_I2C2         0x72    // I2C2
#define FCH_TS_IRQ_I2C3         0x73    // I2C3
#define FCH_TS_IRQ_UART0        0x74    // UART0
#define FCH_TS_IRQ_UART1        0x75    // UART1
#define FCH_TS_IRQ_I2C4         0x76    // I2C4
#define FCH_TS_IRQ_I2C5         0x77    // I2C5
#define FCH_TS_IRQ_UART2        0x78    // UART2
#define FCH_TS_IRQ_UART3        0x79    // UART3

//SciMap
#define FCH_SMI_TS_SciMap0      0x40                             // SciMap0
#define FCH_SMI_TS_GENINT1      (FCH_SMI_TS_SciMap0 + 0)         // SciMap0
#define FCH_SMI_TS_GENINT2      (FCH_SMI_TS_SciMap0 + 1)         // SciMap1
#define FCH_SMI_TS_AGPIO3       (FCH_SMI_TS_SciMap0 + 2)         // SciMap2
#define FCH_SMI_TS_LpcPme       (FCH_SMI_TS_SciMap0 + 3)         // SciMap3
#define FCH_SMI_TS_AGPIO4       (FCH_SMI_TS_SciMap0 + 4)         // SciMap4
#define FCH_SMI_TS_LpcPd        (FCH_SMI_TS_SciMap0 + 5)         // SciMap5
#define FCH_SMI_TS_SPKR         (FCH_SMI_TS_SciMap0 + 6)         // SciMap6
#define FCH_SMI_TS_AGPIO5       (FCH_SMI_TS_SciMap0 + 7)         // SciMap7
#define FCH_SMI_TS_WAKE         (FCH_SMI_TS_SciMap0 + 8)         // SciMap8
#define FCH_SMI_TS_LpcSmi       (FCH_SMI_TS_SciMap0 + 9)         // SciMap9
#define FCH_SMI_TS_AGPIO6       (FCH_SMI_TS_SciMap0 + 10)        // SciMap10
#define FCH_SMI_TS_AGPIO76      (FCH_SMI_TS_SciMap0 + 11)        // SciMap11
#define FCH_SMI_TS_UsbOc0       (FCH_SMI_TS_SciMap0 + 12)        // SciMap12
#define FCH_SMI_TS_UsbOc1       (FCH_SMI_TS_SciMap0 + 13)        // SciMap13
#define FCH_SMI_TS_UsbOc2       (FCH_SMI_TS_SciMap0 + 14)        // SciMap14
#define FCH_SMI_TS_UsbOc3       (FCH_SMI_TS_SciMap0 + 15)        // SciMap15
#define FCH_SMI_TS_AGPIO23      (FCH_SMI_TS_SciMap0 + 16)        // SciMap16
#define FCH_SMI_TS_EspiReset    (FCH_SMI_TS_SciMap0 + 17)        // SciMap17
#define FCH_SMI_TS_FanIn0       (FCH_SMI_TS_SciMap0 + 18)        // SciMap18
#define FCH_SMI_TS_SysReset     (FCH_SMI_TS_SciMap0 + 19)        // SciMap19
#define FCH_SMI_TS_AGPIO40      (FCH_SMI_TS_SciMap0 + 20)        // SciMap20
#define FCH_SMI_TS_PwrBtn       (FCH_SMI_TS_SciMap0 + 21)        // SciMap21
#define FCH_SMI_TS_AGPIO9       (FCH_SMI_TS_SciMap0 + 22)        // SciMap22
#define FCH_SMI_TS_AGPIO8       (FCH_SMI_TS_SciMap0 + 23)        // SciMap23
#define FCH_SMI_TS_eSPI         (FCH_SMI_TS_SciMap0 + 26)        // SciMap26
#define FCH_SMI_TS_EspiWakePme  (FCH_SMI_TS_SciMap0 + 27)        // SciMap27
#define FCH_SMI_TS_NbGppPme     (FCH_SMI_TS_SciMap0 + 29)        // SciMap29
#define FCH_SMI_TS_NbGppHp      (FCH_SMI_TS_SciMap0 + 30)        // SciMap30
#define FCH_SMI_TS_FakeSts0     (FCH_SMI_TS_SciMap0 + 33)        // SciMap33
#define FCH_SMI_TS_FakeSts1     (FCH_SMI_TS_SciMap0 + 34)        // SciMap34
#define FCH_SMI_TS_FakeSts2     (FCH_SMI_TS_SciMap0 + 35)        // SciMap35
#define FCH_SMI_TS_Sata0Pme     (FCH_SMI_TS_SciMap0 + 37)        // SciMap37
#define FCH_SMI_TS_Sata1Pme     (FCH_SMI_TS_SciMap0 + 38)        // SciMap38
#define FCH_SMI_TS_AzaliaPme    (FCH_SMI_TS_SciMap0 + 39)        // SciMap39
#define FCH_SMI_TS_GpioInt      (FCH_SMI_TS_SciMap0 + 41)        // SciMap41
#define FCH_SMI_TS_AltHPET      (FCH_SMI_TS_SciMap0 + 43)        // SciMap43
#define FCH_SMI_TS_FanThGevent  (FCH_SMI_TS_SciMap0 + 44)        // SciMap44
#define FCH_SMI_TS_ASF          (FCH_SMI_TS_SciMap0 + 45)        // SciMap45
#define FCH_SMI_TS_I2sWake      (FCH_SMI_TS_SciMap0 + 46)        // SciMap46
#define FCH_SMI_TS_Smbus0       (FCH_SMI_TS_SciMap0 + 47)        // SciMap47
#define FCH_SMI_TS_TWRN         (FCH_SMI_TS_SciMap0 + 48)        // SciMap48
#define FCH_SMI_TS_TrafficMon   (FCH_SMI_TS_SciMap0 + 49)        // SciMap49
#define FCH_SMI_TS_PwrBtnEvt    (FCH_SMI_TS_SciMap0 + 51)        // SciMap51
#define FCH_SMI_TS_PROHOT       (FCH_SMI_TS_SciMap0 + 52)        // SciMap52
#define FCH_SMI_TS_ApuHw        (FCH_SMI_TS_SciMap0 + 53)        // SciMap53
#define FCH_SMI_TS_ApuSci       (FCH_SMI_TS_SciMap0 + 54)        // SciMap54
#define FCH_SMI_TS_RasEvt       (FCH_SMI_TS_SciMap0 + 55)        // SciMap55
#define FCH_SMI_TS_XhcWake      (FCH_SMI_TS_SciMap0 + 57)        // SciMap57
#define FCH_SMI_TS_AcDcTimer    (FCH_SMI_TS_SciMap0 + 58)        // SciMap58


