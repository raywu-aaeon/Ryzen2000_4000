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
#define SANDSTONE_SD_BUS_DEV_FUN             ((0x14 << 3) + 6)      // SD Controller
#define SANDSTONE_SD_PCI_DEV                 20
#define SANDSTONE_SD_PCI_FUNC                6

#define SANDSTONE_BUSAPORT_BUS_DEV_FUN       ((0x8 << 3) + 1)
#define SANDSTONE_BUSBPORT_BUS_DEV_FUN       ((0x8 << 3) + 2)

#define SANDSTONE_SATA_DEV_FUN               ((0x0 << 3) + 0)
#define SANDSTONE_SATA_DEV                   0
#define SANDSTONE_SATA_FUN                   0
#define SANDSTONE_SATA_PORT_NUM              2

#define SANDSTONE_MAX_FCH_SUPPORT            1

#define SANDSTONE_FCH_SATA_DID               0x7901
#define SANDSTONE_FCH_SATA_AHCI_DID          0x7901
#define SANDSTONE_FCH_SATA_AMDAHCI_DID       0x7904
#define SANDSTONE_FCH_SATA_RAID_DID          0x7916

#define SANDSTONE_FCH_USB_XHCI_DID           0x7914      // Dev 0x10 Func 0
#define SANDSTONE_FCH_SMBUS_DID              0x790B      // Dev 0x14 Func 0
#define SANDSTONE_FCH_LPC_DID                0x790E      // Dev 0x14 Func 3
#define SANDSTONE_FCH_SD_DID                 0x7906      // Dev 0x14 Func 7

#define PGFSM_CMD_POWER_DOWN                 (0x00 << 1)
#define PGFSM_CMD_POWER_UP                   (0x01 << 1)
#define PGFSM_CMD_POWER_WRITE                (0x02 << 1)
#define PGFSM_CMD_POWER_READ                 (0x03 << 1)
#define PGFSM_SOFTWARE_CONTROL               BIT0

#define PGFSM_STATUS_PWR_STS                 (BIT0 + BIT1)
#define PGFSM_STATUS_PWR_ON                  0
#define PGFSM_STATUS_PWR_OFF                 BIT1

#define PGFSM_SELECT_0                       BIT8

//USB RSMU registers
#define FCH_SS_USB_RSMU_PGFSM_CNTL           0x0004D520ul        //0x0004D520ul
#define FCH_SS_USB_RSMU_PGFSM_WR_DATA        0x0004D524ul        //0x0004D524ul
#define FCH_SS_USB_RSMU_PGFSM_RD_DATA        0x0004D528ul        //0x0004D528ul

//USB3 IP registers
#define FCH_SS_USB_GUCTL1                    0x16C0C11Cul        //0x16C0C11C
#define FCH_SS_USB_GUCTL                     0x16C0C12Cul        //0x16C0C12C
#define FCH_SS_USB_GUSB3PIPECTL0             0x16C0C2C0ul        //0x16C0C2C0
#define FCH_SS_USB_GUSB3PIPECTL1             0x16C0C2C4ul        //0x16C0C2C4
#define FCH_SS_USB_GUSB3PIPECTL2             0x16C0C2C8ul        //0x16C0C2C8
#define FCH_SS_USB_GUSB3PIPECTL3             0x16C0C2CCul        //0x16C0C2CC
#define FCH_SS_USB_GDMAHLRATIO               0x16C0C624ul        //0x16C0C624

#define FCH_SS_USB1_GUCTL1                   0x16E0C11Cul        //0x16E0C11C
#define FCH_SS_USB1_GUCTL                    0x16E0C12Cul        //0x16E0C12C
#define FCH_SS_USB1_GDMAHLRATIO              0x16E0C624ul        //0x16E0C624

//USB3 CONTAINER Registers
#define FCH_SS_SMN_USB_CONTAINER             0x16D80000ul
#define FCH_SS_USB_SHADOWED_POWERSTATE       FCH_SS_SMN_USB_CONTAINER + 0x14         //0x14
#define FCH_SS_USB_SMU_ASSIST_POWER_STS_CNTL FCH_SS_SMN_USB_CONTAINER + 0x1C         //0x1C 
#define FCH_SS_USB_RESET                     FCH_SS_SMN_USB_CONTAINER + 0x100        //0x100
  #define FCH_SS_USB_S5_RESET                 (1 << 0x00)
  #define FCH_SS_USB_CONTROLLER_RESET         (1 << 0x01)
  #define FCH_SS_USB_PHY_RESET                (1 << 0x02)
#define FCH_SS_USB_PGFSM_OVERRIDE            FCH_SS_SMN_USB_CONTAINER + 0x104        //0x104
#define FCH_SS_USB_CURRENT_PWR_STS           FCH_SS_SMN_USB_CONTAINER + 0x108        //0x108
#define FCH_SS_USB_POWER_CLK_CONTROL         FCH_SS_SMN_USB_CONTAINER + 0x10C        //0x10C
#define FCH_SS_USB_INTERRUPT_CONTROL         FCH_SS_SMN_USB_CONTAINER + 0x118        //0x118
#define FCH_SS_USB_PORT_OCMAPPING0           FCH_SS_SMN_USB_CONTAINER + 0x120        //0x120
#define FCH_SS_USB_PORT_DISABLE0             FCH_SS_SMN_USB_CONTAINER + 0x128        //0x128
#define FCH_SS_USB_PORT_CONTROL              FCH_SS_SMN_USB_CONTAINER + 0x130        //0x130

#define FCH_SS_USB31_PHY0_LANEPARACTL5       0x16D6C014ul        //0xC014
#define FCH_SS_USB31_PHY1_LANEPARACTL5       0x16D6C414ul        //0xC414
#define FCH_SS_USB31_PHY2_LANEPARACTL5       0x16D6C814ul        //0xC814
#define FCH_SS_USB31_PHY3_LANEPARACTL5       0x16D6CC14ul        //0xCC14

#define FCH_SS_USB30_PHY0_INTERNAL_LANE      0x16F04018ul        //0x16F04018

#define FCH_SS_USB_NBIF_STRAP0               0x10134600ul
#define FCH_SS_USB1_NBIF_STRAP0              0x10134800ul
#define FCH_SS_USB_SMN_PCICFG                0x10143000ul
#define FCH_SS_USB1_SMN_PCICFG               0x10144000ul

//SATA RSMU registers
#define FCH_SS_SMN_SATA_RSMU_BASE            0x010A8000ul
#define FCH_SS_SMN_SATA_CONTROL_RSMU         0x03100000ul
#define FCH_SS_SMN_SATA_CONTROL_BAR5         0x03101000ul
#define FCH_SS_SMN_SATA_CONTROL_SLOR         0x03101800ul

//RSMU registers
#define FCH_SS_RSMU_SATA_PGFSM_CNTL          0x0004D420ul        //0x0004D520ul
#define FCH_SS_RSMU_SATA_PGFSM_WR_DATA       0x0004D424ul        //0x0004D524ul
#define FCH_SS_RSMU_SATA_PGFSM_RD_DATA       0x0004D428ul        //0x0004D528ul

#define FCH_SATA_RSMU_COLD_RESETB            FCH_SS_SMN_SATA_RSMU_BASE + 0x04
#define FCH_SATA_RSMU_HARD_RESETB            FCH_SS_SMN_SATA_RSMU_BASE + 0x08

#define FCH_SS_SATA_MISC_CONTROL             FCH_SS_SMN_SATA_CONTROL_RSMU + 0x00     //0x00
#define FCH_SS_SATA_OOB_CONTROL              FCH_SS_SMN_SATA_CONTROL_RSMU + 0x02     //0x02
#define FCH_SS_SATA_AOAC_CONTROL             FCH_SS_SMN_SATA_CONTROL_RSMU + 0x04     //0x04
#define FCH_SS_SATA_EVENT_SELECT             FCH_SS_SMN_SATA_CONTROL_RSMU + 0x08     //0x08
#define FCH_SS_SATA_NBIF_CONTROL             FCH_SS_SMN_SATA_CONTROL_RSMU + 0x0A     //0x0A

#define FCH_SS_SATA_MISC_CONTROL4            FCH_SS_SMN_SATA_CONTROL_SLOR + 0x10     //0x10

#define FCH_RCC_DEV1_PORT_STRAP0             0x10131200ul
#define FCH_RCC_DEV1_EPF2_STRAP0             0x10135400ul
#define FCH_IOHC_Bridge_CNTL_INST8           0x13B38404ul

#define FCH_SS_SMN_SATA_NBIF_STRAP0          0x10135000ul
#define FCH_SS_SMN_SATA_NBIF_STRAP2          0x10135008ul
#define FCH_SS_SMN_SATA_NBIF_STRAP3          0x1013500Cul
#define FCH_SS_SMN_SATA_NBIF_STRAP4          0x10135010ul
#define FCH_SS_SMN_SATA_NBIF_STRAP13         0x10135034ul

#define FCH_SS_SMN_SATA_PCICFG               0x10148000ul

//xGbE registers
#define FCH_SS_SMN_XGBE_MMIO0_BASE           0x1631F000ul

#define FCH_SS_XGBE_PAD_MUX0                 FCH_SS_SMN_XGBE_MMIO0_BASE + 0x00
#define FCH_SS_XGBE_PAD_MUX1                 FCH_SS_SMN_XGBE_MMIO0_BASE + 0x04
#define FCH_SS_XGBE_PORT0_CLK_GATE           FCH_SS_SMN_XGBE_MMIO0_BASE + 0x30
#define FCH_SS_XGBE_PORT0_PROPERTY0          FCH_SS_SMN_XGBE_MMIO0_BASE + 0x800
#define FCH_SS_XGBE_PORT0_PROPERTY1          FCH_SS_SMN_XGBE_MMIO0_BASE + 0x804
#define FCH_SS_XGBE_PORT0_PROPERTY2          FCH_SS_SMN_XGBE_MMIO0_BASE + 0x808
#define FCH_SS_XGBE_PORT0_PROPERTY3          FCH_SS_SMN_XGBE_MMIO0_BASE + 0x80C
#define FCH_SS_XGBE_PORT0_PROPERTY4          FCH_SS_SMN_XGBE_MMIO0_BASE + 0x810
#define FCH_SS_XGBE_PORT0_PROPERTY5          FCH_SS_SMN_XGBE_MMIO0_BASE + 0x814
#define FCH_SS_XGBE_PORT0_MAC_ADDR_LOW       FCH_SS_SMN_XGBE_MMIO0_BASE + 0x880
#define FCH_SS_XGBE_PORT0_MAC_ADDR_HIGH      FCH_SS_SMN_XGBE_MMIO0_BASE + 0x884

#define FCH_NBIFSHUBMM0x00011000_SYSHUB_DS_CTRL_SHUBCLK 0x01411000ul
#define FCH_DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE BIT19

#define FCH_SS_RCC_DEV1_EPF1_STRAP0          0x10135200ul
#define FCH_SS_SMN_XGBE0_NBIF_STRAP0         0x10234800ul

//FCH register SMN address
#define FCH_SS_SMN_IOMUX_BASE                0x02D01D00ul
#define FCH_SS_SMN_MISC_BASE                 0x02D01E00ul
#define FCH_SS_SMN_GPIO_BASE                 0x02D02500ul

#define FCH_SS_IRQ_INTA         0x00
#define FCH_SS_IRQ_INTB         0x01
#define FCH_SS_IRQ_INTC         0x02
#define FCH_SS_IRQ_INTD         0x03
#define FCH_SS_IRQ_GENINT2      0x05
#define FCH_SS_IRQ_SCI          0x10    // SCI
#define FCH_SS_IRQ_SMBUS0       0x11    // SMBUS0
#define FCH_SS_IRQ_ASF          0x12    // ASF
#define FCH_SS_IRQ_GBE0         0x14    // GBE0
#define FCH_SS_IRQ_GBE1         0x15    // GBE1
#define FCH_SS_IRQ_SD           0x17    // SD
#define FCH_SS_IRQ_SDIO         0x1A    // SDIO
#define FCH_SS_IRQ_GPIOa        0x21
#define FCH_SS_IRQ_GPIOb        0x22
#define FCH_SS_IRQ_GPIOc        0x23
#define FCH_SS_IRQ_USB_EMU      0x30    // AMD USB Emulation Interrupt
#define FCH_SS_IRQ_USB_DR0      0x31    // USB DualRole Intr0
#define FCH_SS_IRQ_USB_DR1      0x32    // USB DualRole Intr1
#define FCH_SS_IRQ_USB_XHCI0    0x34    // XHCI0
#define FCH_SS_IRQ_USB_SSIC     0x35    // SSIC
#define FCH_SS_IRQ_SATA         0x41    // SATA
#define FCH_SS_IRQ_UFS          0x42    // UFS
#define FCH_SS_IRQ_EMMC         0x43    // EMMC
#define FCH_SS_IRQ_GPIO         0x62    // GPIO
#define FCH_SS_IRQ_I2C0         0x70    // I2C0
#define FCH_SS_IRQ_I2C1         0x71    // I2C1
#define FCH_SS_IRQ_I2C2         0x72    // I2C2
#define FCH_SS_IRQ_I2C3         0x73    // I2C3
#define FCH_SS_IRQ_UART0        0x74    // UART0
#define FCH_SS_IRQ_UART1        0x75    // UART1
#define FCH_SS_IRQ_I2C4         0x76    // I2C4
#define FCH_SS_IRQ_I2C5         0x77    // I2C5
#define FCH_SS_IRQ_UART2        0x78    // UART2
#define FCH_SS_IRQ_UART3        0x79    // UART3

//SciMap
#define FCH_SS_SMI_SciMap0         0x40                          // SciMap0
#define FCH_SMI_SS_GENINT1      (FCH_SS_SMI_SciMap0 + 0)         // SciMap0
#define FCH_SMI_SS_GENINT2      (FCH_SS_SMI_SciMap0 + 1)         // SciMap1
#define FCH_SMI_SS_AGPIO3       (FCH_SS_SMI_SciMap0 + 2)         // SciMap2
#define FCH_SMI_SS_LpcPme       (FCH_SS_SMI_SciMap0 + 3)         // SciMap3
#define FCH_SMI_SS_AGPIO4       (FCH_SS_SMI_SciMap0 + 4)         // SciMap4
#define FCH_SMI_SS_LpcPd        (FCH_SS_SMI_SciMap0 + 5)         // SciMap5
#define FCH_SMI_SS_SPKR         (FCH_SS_SMI_SciMap0 + 6)         // SciMap6
#define FCH_SMI_SS_AGPIO5       (FCH_SS_SMI_SciMap0 + 7)         // SciMap7
#define FCH_SMI_SS_WAKE         (FCH_SS_SMI_SciMap0 + 8)         // SciMap8
#define FCH_SMI_SS_LpcSmi       (FCH_SS_SMI_SciMap0 + 9)         // SciMap9
#define FCH_SMI_SS_AGPIO6       (FCH_SS_SMI_SciMap0 + 10)        // SciMap10
#define FCH_SMI_SS_AGPIO76      (FCH_SS_SMI_SciMap0 + 11)        // SciMap11
#define FCH_SMI_SS_UsbOc0       (FCH_SS_SMI_SciMap0 + 12)        // SciMap12
#define FCH_SMI_SS_UsbOc1       (FCH_SS_SMI_SciMap0 + 13)        // SciMap13
#define FCH_SMI_SS_UsbOc2       (FCH_SS_SMI_SciMap0 + 14)        // SciMap14
#define FCH_SMI_SS_UsbOc3       (FCH_SS_SMI_SciMap0 + 15)        // SciMap15
#define FCH_SMI_SS_AGPIO23      (FCH_SS_SMI_SciMap0 + 16)        // SciMap16
#define FCH_SMI_SS_EspiReset    (FCH_SS_SMI_SciMap0 + 17)        // SciMap17
#define FCH_SMI_SS_FanIn0       (FCH_SS_SMI_SciMap0 + 18)        // SciMap18
#define FCH_SMI_SS_SysReset     (FCH_SS_SMI_SciMap0 + 19)        // SciMap19
#define FCH_SMI_SS_AGPIO40      (FCH_SS_SMI_SciMap0 + 20)        // SciMap20
#define FCH_SMI_SS_PwrBtn       (FCH_SS_SMI_SciMap0 + 21)        // SciMap21
#define FCH_SMI_SS_AGPIO9       (FCH_SS_SMI_SciMap0 + 22)        // SciMap22
#define FCH_SMI_SS_AGPIO8       (FCH_SS_SMI_SciMap0 + 23)        // SciMap23
#define FCH_SMI_SS_eSPI         (FCH_SS_SMI_SciMap0 + 26)        // SciMap26
#define FCH_SMI_SS_EspiWakePme  (FCH_SS_SMI_SciMap0 + 27)        // SciMap27
#define FCH_SMI_SS_NbGppPme     (FCH_SS_SMI_SciMap0 + 29)        // SciMap29
#define FCH_SMI_SS_NbGppHp      (FCH_SS_SMI_SciMap0 + 30)        // SciMap30
#define FCH_SMI_SS_FakeSts0     (FCH_SS_SMI_SciMap0 + 33)        // SciMap33
#define FCH_SMI_SS_FakeSts1     (FCH_SS_SMI_SciMap0 + 34)        // SciMap34
#define FCH_SMI_SS_FakeSts2     (FCH_SS_SMI_SciMap0 + 35)        // SciMap35
#define FCH_SMI_SS_Sata0Pme     (FCH_SS_SMI_SciMap0 + 37)        // SciMap37
#define FCH_SMI_SS_Sata1Pme     (FCH_SS_SMI_SciMap0 + 38)        // SciMap38
#define FCH_SMI_SS_AzaliaPme    (FCH_SS_SMI_SciMap0 + 39)        // SciMap39
#define FCH_SMI_SS_GpioInt      (FCH_SS_SMI_SciMap0 + 41)        // SciMap41
#define FCH_SMI_SS_AltHPET      (FCH_SS_SMI_SciMap0 + 43)        // SciMap43
#define FCH_SMI_SS_FanThGevent  (FCH_SS_SMI_SciMap0 + 44)        // SciMap44
#define FCH_SMI_SS_ASF          (FCH_SS_SMI_SciMap0 + 45)        // SciMap45
#define FCH_SMI_SS_I2sWake      (FCH_SS_SMI_SciMap0 + 46)        // SciMap46
#define FCH_SMI_SS_Smbus0       (FCH_SS_SMI_SciMap0 + 47)        // SciMap47
#define FCH_SMI_SS_TWRN         (FCH_SS_SMI_SciMap0 + 48)        // SciMap48
#define FCH_SMI_SS_TrafficMon   (FCH_SS_SMI_SciMap0 + 49)        // SciMap49
#define FCH_SMI_SS_PwrBtnEvt    (FCH_SS_SMI_SciMap0 + 51)        // SciMap51
#define FCH_SMI_SS_PROHOT       (FCH_SS_SMI_SciMap0 + 52)        // SciMap52
#define FCH_SMI_SS_ApuHw        (FCH_SS_SMI_SciMap0 + 53)        // SciMap53
#define FCH_SMI_SS_ApuSci       (FCH_SS_SMI_SciMap0 + 54)        // SciMap54
#define FCH_SMI_SS_RasEvt       (FCH_SS_SMI_SciMap0 + 55)        // SciMap55
#define FCH_SMI_SS_XhcWake      (FCH_SS_SMI_SciMap0 + 57)        // SciMap57
#define FCH_SMI_SS_AcDcTimer    (FCH_SS_SMI_SciMap0 + 58)        // SciMap58


