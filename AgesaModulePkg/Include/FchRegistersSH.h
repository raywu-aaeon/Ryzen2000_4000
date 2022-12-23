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
#define FCH_REVISION                         "0.6.0.2"
#define FCH_ID                               "FCH_602"
#define FCH_VERSION                          0x0602

#define SHASTA_MAX_FCH_SUPPORT               1

#define AMD_D0F0   ((0 << 3) + 0)
#define AMD_D18F0  ((0x18 << 3) + 0)

#define SOC_RNID                             0x14801022ul
#define DF_RNID                              0x14481022ul

//CPU Package Type

#define SHASTA_FCH_SATA_DID                  0x7901
#define SHASTA_FCH_SATA_AHCI_DID             0x7901
#define SHASTA_FCH_SATA_AMDAHCI_DID          0x7904
#define SHASTA_FCH_SATA_RAID_DID             0x7916
#define SHASTA_FCH_SATA_RAID_DID2            0x7917

#define SHASTA_FCH_USB_XHCI_DID              0x7914
#define SHASTA_FCH_SMBUS_DID                 0x790B      // Dev 0x14 Func 0
#define SHASTA_FCH_LPC_DID                   0x790E      // Dev 0x14 Func 3
#define SHASTA_FCH_SD_DID                    0x7906      // Dev 0x14 Func 7

#define PGFSM_CMD_POWER_DOWN                 (0x00 << 1)
#define PGFSM_CMD_POWER_UP                   (0x01 << 1)
#define PGFSM_CMD_POWER_WRITE                (0x02 << 1)
#define PGFSM_CMD_POWER_READ                 (0x03 << 1)
#define PGFSM_SOFTWARE_CONTROL               BIT0

#define PGFSM_STATUS_PWR_STS                 (BIT0 + BIT1)
#define PGFSM_STATUS_PWR_ON                  0
#define PGFSM_STATUS_PWR_OFF                 BIT1

#define PGFSM_SELECT_0                       BIT8
//
// SD controller
//
#define SHASTA_SD_BUS_DEV_FUN                ((0x14 << 3) + 6)
#define SHASTA_SD_PCI_DEV                    20
#define SHASTA_SD_PCI_FUNC                   6

//
// SATA
//
#define SHASTA_SATA_CONTROLLER_NUM           2
#define SHASTA_SATA_PORT_NUM                 2

//SATA0 RSMU registers
#define FCH_SMN_SATA_RSMU_BASE               0x090A8000ul
#define FCH_SMN_SATA_CONTROL_BASE            0x03100000ul
#define FCH_SMN_SATA_CONTROL_RSMU            FCH_SMN_SATA_CONTROL_BASE
#define FCH_SMN_SATA_CONTROL_BAR5            FCH_SMN_SATA_CONTROL_BASE + 0x1000
#define FCH_SMN_SATA_CONTROL_SLOR            FCH_SMN_SATA_CONTROL_BASE + 0x1800

//SATA1 Address Offset
#define FCH_SMN_SATA_RSMU_BASE_STEP          0x1000ul
#define FCH_SMN_SATA_CONTROL_STEP            0x100000ul

#define FCH_SATA_RSMU_COLD_RESETB            FCH_SMN_SATA_RSMU_BASE + 0x04
#define FCH_SATA_RSMU_HARD_RESETB            FCH_SMN_SATA_RSMU_BASE + 0x08

#define FCH_SH_SATA_MISC_CONTROL             FCH_SMN_SATA_CONTROL_RSMU + 0x00     //0x00
#define FCH_SH_SATA_OOB_CONTROL              FCH_SMN_SATA_CONTROL_RSMU + 0x02     //0x02
#define FCH_SH_SATA_AOAC_CONTROL             FCH_SMN_SATA_CONTROL_RSMU + 0x04     //0x04
#define FCH_SH_SATA_EVENT_SELECT             FCH_SMN_SATA_CONTROL_RSMU + 0x08     //0x08
#define FCH_SH_SATA_NBIF_CONTROL             FCH_SMN_SATA_CONTROL_RSMU + 0x0A     //0x0A
//  Sata0: nBIF0 DEV1 Func0
#define FCH_SMN_SATA0_NBIF_STRAP0            0x10135000ul
#define FCH_SMN_SATA0_NBIF_STRAP3            0x1013500Cul
#define FCH_SMN_SATA0_NBIF_STRAP13           0x10135034ul
#define FCH_SH_SATA0_SMN_PCICFG              0x10148000ul
//  Sata1
#define FCH_SMN_SATA1_NBIF_STRAP0            0x10135200ul
#define FCH_SMN_SATA1_NBIF_STRAP3            0x1013520Cul
#define FCH_SMN_SATA1_NBIF_STRAP13           0x10135234ul
#define FCH_SH_SATA1_SMN_PCICFG              0x10149000ul
#define FCH_SMN_SATA_NBIF_STRAP_STEP         0x200ul
#define FCH_SH_SATA1_SMN_PCICFG_STEP         0x1000ul
//  Sata: NBIF1DEVINDCFG IOHC_Bridge_CNTL  //RN needs to check with NBIO???
#define FCH_SH_NBIF1DEVINDCFG_IOHC_Bridge_CNTL               0x13B39404ul
#define FCH_SH_NBIF1DEVINDCFG_IOHC_Bridge_CNTL_NBIO_STEP     0x00100000ul
#define FCH_SH_NBIF1DEVINDCFG_IOHC_Bridge_CNTL_PORT_STEP     0x00000400ul

//
// USB
//
//  RN has 2 XHCI controller
#define FCH_SH_USB0_SMN_BASE                 0x16C00000ul        //0x16C00000ul
#define FCH_SH_USB1_SMN_BASE                 0x16E00000ul        //0x16E00000ul
#define FCH_SH_USB_CONTROLLER_SMN_STEP       0x200000ul          //0x16E00000ul

//USB RSMU registers
#define FCH_SH_USB_RSMU_PGFSM_CNTL           0x0004D520ul        //0x0004D520ul
#define FCH_SH_USB_RSMU_PGFSM_WR_DATA        0x0004D524ul        //0x0004D524ul
#define FCH_SH_USB_RSMU_PGFSM_RD_DATA        0x0004D528ul        //0x0004D528ul

//USB3 IP registers
#define FCH_SH_USB_GUCTL1                    0x16C0C11Cul        //0x16C0C11C
#define FCH_SH_USB_GUCTL                     0x16C0C12Cul        //0x16C0C12C
#define FCH_SH_USB_GUSB3PIPECTL0             0x16C0C2C0ul        //0x16C0C2C0
#define FCH_SH_USB_GUSB3PIPECTL1             0x16C0C2C4ul        //0x16C0C2C4
#define FCH_SH_USB_GUSB3PIPECTL2             0x16C0C2C8ul        //0x16C0C2C8
#define FCH_SH_USB_GUSB3PIPECTL3             0x16C0C2CCul        //0x16C0C2CC

//USB3 CONTAINER Registers
#define FCH_SMN_USB_CONTAINER                0x16D80000ul
#define FCH_SH_USB_SHADOWED_POWERSTATE       FCH_SMN_USB_CONTAINER + 0x14         //0x14
#define FCH_SH_USB_RESET                     FCH_SMN_USB_CONTAINER + 0x100        //0x100
  #define FCH_SH_USB_S5_RESET                 (1 << 0x00)
  #define FCH_SH_USB_CONTROLLER_RESET         (1 << 0x01)
  #define FCH_SH_USB_PHY_RESET                (1 << 0x02)
#define FCH_SH_USB_PGFSM_OVERRIDE            FCH_SMN_USB_CONTAINER + 0x104        //0x104
#define FCH_SH_USB_CURRENT_PWR_STS           FCH_SMN_USB_CONTAINER + 0x108        //0x108
#define FCH_SH_USB_DEVICE_REMOVABLE          FCH_SMN_USB_CONTAINER + 0x114        //0x114
#define FCH_SH_USB_INTERRUPT_CONTROL         FCH_SMN_USB_CONTAINER + 0x118        //0x118
#define FCH_SH_USB_PORT_OCMAPPING0           FCH_SMN_USB_CONTAINER + 0x120        //0x120
#define FCH_SH_USB_PORT_DISABLE0             FCH_SMN_USB_CONTAINER + 0x128        //0x128
#define FCH_SH_USB_PORT_CONTROL              FCH_SMN_USB_CONTAINER + 0x130        //0x130

#define FCH_SH_USB_PHY0_RX_OVRD_IN_HI        0x16D04018ul        //0x4018
#define FCH_SH_USB_PHY1_RX_OVRD_IN_HI        0x16D04418ul        //0x4418
#define FCH_SH_USB_PHY2_RX_OVRD_IN_HI        0x16D04818ul        //0x4818
#define FCH_SH_USB_PHY3_RX_OVRD_IN_HI        0x16D04C18ul        //0x4C18
  #define RX_EQ_OVRD                         BIT11
  #define RX_EQ                              (BIT8 + BIT9 + BIT10)
  #define RX_EQ_EN_OVRD                      BIT7
  #define RX_EQ_EN                           BIT6
#define FCH_SH_USB_PHY0_PHYINTERNALLANEREGISTER        0x16D04098ul        //0x4098
#define FCH_SH_USB_PHY1_PHYINTERNALLANEREGISTER        0x16D04498ul        //0x4498
#define FCH_SH_USB_PHY2_PHYINTERNALLANEREGISTER        0x16D04898ul        //0x4898
#define FCH_SH_USB_PHY3_PHYINTERNALLANEREGISTER        0x16D04C98ul        //0x4C98

#define FCH_SH_USBPHYCTRLx0004_PHYPARACTL1             0x16D08004ul        //0x8004
#define FCH_SH_USBPHYCTRLx0008_PHYPARACTL2             0x16D08008ul        //0x8008

#define FCH_SH_USB_PHY0_PHYCFG0              0x16D08200ul        //0x8200
#define FCH_SH_USB_PHY1_PHYCFG0              0x16D08600ul        //0x8600
#define FCH_SH_USB_PHY2_PHYCFG0              0x16D08A00ul        //0x8A00
#define FCH_SH_USB_PHY3_PHYCFG0              0x16D08E00ul        //0x8E00
#define FCH_SH_USB_PHY0_LANEPARACTL0         0x16D0C000ul        //0xC000
#define FCH_SH_USB_PHY1_LANEPARACTL0         0x16D0C400ul        //0xC400
#define FCH_SH_USB_PHY2_LANEPARACTL0         0x16D0C800ul        //0xC800
#define FCH_SH_USB_PHY3_LANEPARACTL0         0x16D0CC00ul        //0xCC00
#define FCH_SH_USB_PHY0PARACTL2              0x16D08008ul        //0x8008
#define FCH_SH_USB_PHY1PARACTL2              0x16D08408ul        //0x8408
#define FCH_SH_USB_PHY2PARACTL2              0x16D08808ul        //0x8808
#define FCH_SH_USB_PHY3PARACTL2              0x16D08C08ul        //0x8C08

#define FCH_SH_USB0_NBIF_STRAP0              0x10134600ul
#define FCH_SH_USB0_SMN_PCICFG               0x10143000ul
#define FCH_SH_USB1_NBIF_STRAP0              0x10134800ul
#define FCH_SH_USB1_SMN_PCICFG               0x10144000ul

//FCH register SMN address
#define FCH_SMN_SMI_BASE                     0x02D01200ul
#define FCH_SMN_IOMUX_BASE                   0x02D01D00ul
#define FCH_SMN_MISC_BASE                    0x02D01E00ul
#define FCH_SMN_GPIO_BASE                    0x02D02500ul

#define FCH_SH_IRQ_INTA         0x00
#define FCH_SH_IRQ_INTB         0x01
#define FCH_SH_IRQ_INTC         0x02
#define FCH_SH_IRQ_INTD         0x03
#define FCH_SH_IRQ_GENINT2      0x05
#define FCH_SH_IRQ_SCI          0x10    // SCI
#define FCH_SH_IRQ_SMBUS0       0x11    // SMBUS0
#define FCH_SH_IRQ_ASF          0x12    // ASF
#define FCH_SH_IRQ_SD           0x17    // SD
#define FCH_SH_IRQ_SDIO         0x1A    // SDIO
#define FCH_SH_IRQ_GPIOa        0x21
#define FCH_SH_IRQ_GPIOb        0x22
#define FCH_SH_IRQ_GPIOc        0x23
#define FCH_SH_IRQ_SATA         0x41    // SATA
#define FCH_SH_IRQ_EMMC         0x43    // EMMC
#define FCH_SH_IRQ_GPIO         0x62    // GPIO
#define FCH_SH_IRQ_I2C0         0x70    // I2C0
#define FCH_SH_IRQ_I2C1         0x71    // I2C1
#define FCH_SH_IRQ_I2C2         0x72    // I2C2
#define FCH_SH_IRQ_I2C3         0x73    // I2C3
#define FCH_SH_IRQ_UART0        0x74    // UART0
#define FCH_SH_IRQ_UART1        0x75    // UART1
#define FCH_SH_IRQ_I2C4         0x76    // I2C4
#define FCH_SH_IRQ_I2C5         0x77    // I2C5
#define FCH_SH_IRQ_UART2        0x78    // UART2
#define FCH_SH_IRQ_UART3        0x79    // UART3

//SciMap
#define FCH_SMI_SciMap0         0x40                          // SciMap0
#define FCH_SMI_SH_GENINT1      (FCH_SMI_SciMap0 + 0)         // SciMap0
#define FCH_SMI_SH_GENINT2      (FCH_SMI_SciMap0 + 1)         // SciMap1
#define FCH_SMI_SH_AGPIO3       (FCH_SMI_SciMap0 + 2)         // SciMap2
#define FCH_SMI_SH_LpcPme       (FCH_SMI_SciMap0 + 3)         // SciMap3
#define FCH_SMI_SH_AGPIO4       (FCH_SMI_SciMap0 + 4)         // SciMap4
#define FCH_SMI_SH_LpcPd        (FCH_SMI_SciMap0 + 5)         // SciMap5
#define FCH_SMI_SH_SPKR         (FCH_SMI_SciMap0 + 6)         // SciMap6
#define FCH_SMI_SH_AGPIO5       (FCH_SMI_SciMap0 + 7)         // SciMap7
#define FCH_SMI_SH_WAKE         (FCH_SMI_SciMap0 + 8)         // SciMap8
#define FCH_SMI_SH_LpcSmi       (FCH_SMI_SciMap0 + 9)         // SciMap9
#define FCH_SMI_SH_AGPIO6       (FCH_SMI_SciMap0 + 10)        // SciMap10
#define FCH_SMI_SH_AGPIO76      (FCH_SMI_SciMap0 + 11)        // SciMap11
#define FCH_SMI_SH_UsbOc0       (FCH_SMI_SciMap0 + 12)        // SciMap12
#define FCH_SMI_SH_UsbOc1       (FCH_SMI_SciMap0 + 13)        // SciMap13
#define FCH_SMI_SH_UsbOc2       (FCH_SMI_SciMap0 + 14)        // SciMap14
#define FCH_SMI_SH_UsbOc3       (FCH_SMI_SciMap0 + 15)        // SciMap15
#define FCH_SMI_SH_AGPIO23      (FCH_SMI_SciMap0 + 16)        // SciMap16
#define FCH_SMI_SH_EspiReset    (FCH_SMI_SciMap0 + 17)        // SciMap17
#define FCH_SMI_SH_FanIn0       (FCH_SMI_SciMap0 + 18)        // SciMap18
#define FCH_SMI_SH_SysReset     (FCH_SMI_SciMap0 + 19)        // SciMap19
#define FCH_SMI_SH_AGPIO40      (FCH_SMI_SciMap0 + 20)        // SciMap20
#define FCH_SMI_SH_PwrBtn       (FCH_SMI_SciMap0 + 21)        // SciMap21
#define FCH_SMI_SH_AGPIO9       (FCH_SMI_SciMap0 + 22)        // SciMap22
#define FCH_SMI_SH_AGPIO8       (FCH_SMI_SciMap0 + 23)        // SciMap23
#define FCH_SMI_SH_Mp2Wake      (FCH_SMI_SciMap0 + 24)        // SciMap24
#define FCH_SMI_SH_Mp2Gpio0     (FCH_SMI_SciMap0 + 25)        // SciMap25
#define FCH_SMI_SH_eSPI         (FCH_SMI_SciMap0 + 26)        // SciMap26
#define FCH_SMI_SH_EspiWakePme  (FCH_SMI_SciMap0 + 27)        // SciMap27
#define FCH_SMI_SH_Mp2Gpio1     (FCH_SMI_SciMap0 + 25)        // SciMap28
#define FCH_SMI_SH_NbGppPme     (FCH_SMI_SciMap0 + 29)        // SciMap29
#define FCH_SMI_SH_NbGppHp      (FCH_SMI_SciMap0 + 30)        // SciMap30
#define FCH_SMI_SH_FakeSts0     (FCH_SMI_SciMap0 + 33)        // SciMap33
#define FCH_SMI_SH_FakeSts1     (FCH_SMI_SciMap0 + 34)        // SciMap34
#define FCH_SMI_SH_FakeSts2     (FCH_SMI_SciMap0 + 35)        // SciMap35
#define FCH_SMI_SH_Sata0Pme     (FCH_SMI_SciMap0 + 37)        // SciMap37
#define FCH_SMI_SH_Sata1Pme     (FCH_SMI_SciMap0 + 38)        // SciMap38
#define FCH_SMI_SH_AzaliaPme    (FCH_SMI_SciMap0 + 39)        // SciMap39
#define FCH_SMI_SH_GpioInt      (FCH_SMI_SciMap0 + 41)        // SciMap41
#define FCH_SMI_SH_AltHPET      (FCH_SMI_SciMap0 + 43)        // SciMap43
#define FCH_SMI_SH_FanThGevent  (FCH_SMI_SciMap0 + 44)        // SciMap44
#define FCH_SMI_SH_ASF          (FCH_SMI_SciMap0 + 45)        // SciMap45
#define FCH_SMI_SH_I2sWake      (FCH_SMI_SciMap0 + 46)        // SciMap46
#define FCH_SMI_SH_Smbus0       (FCH_SMI_SciMap0 + 47)        // SciMap47
#define FCH_SMI_SH_TWRN         (FCH_SMI_SciMap0 + 48)        // SciMap48
#define FCH_SMI_SH_TrafficMon   (FCH_SMI_SciMap0 + 49)        // SciMap49
#define FCH_SMI_SH_LLB          (FCH_SMI_SciMap0 + 50)        // SciMap50
#define FCH_SMI_SH_PwrBtnEvt    (FCH_SMI_SciMap0 + 51)        // SciMap51
#define FCH_SMI_SH_PROHOT       (FCH_SMI_SciMap0 + 52)        // SciMap52
#define FCH_SMI_SH_ApuHw        (FCH_SMI_SciMap0 + 53)        // SciMap53
#define FCH_SMI_SH_ApuSci       (FCH_SMI_SciMap0 + 54)        // SciMap54
#define FCH_SMI_SH_RasEvt       (FCH_SMI_SciMap0 + 55)        // SciMap55
#define FCH_SMI_SH_XhcWake      (FCH_SMI_SciMap0 + 57)        // SciMap57
#define FCH_SMI_SH_AcDcTimer    (FCH_SMI_SciMap0 + 58)        // SciMap58

