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
 * @e \$Revision: 312980 $   @e \$Date: 2015-02-13 12:00:33 -0800 (Fri, 13 Feb 2015) $
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

//AB IO BASE
#define ALINK_ACCESS_INDEX                 0x0CD8
#define ALINK_ACCESS_DATA                  ALINK_ACCESS_INDEX + 4

#define CFG_ADDR_PORT                      0xCF8
#define CFG_DATA_PORT                      0xCFC

//Misc
#define R_FCH_ACPI_PM1_STATUS              0x00
#define R_FCH_ACPI_PM1_ENABLE              0x02
#define R_FCH_ACPI_PM_CONTROL              0x04
#define R_FCH_ACPI_EVENT_STATUS            0x20
#define R_FCH_ACPI_EVENT_ENABLE            0x24
#define R_FCH_PM_ACPI_PMA_CNT_BLK_LO       0x2C

// ACPI Sleep Type
#define ACPI_SLPTYP_S0                     0
#define ACPI_SLPTYP_S1                     1
#define ACPI_SLPTYP_S3                     3
#define ACPI_SLPTYP_S4                     4
#define ACPI_SLPTYP_S5                     5

#define SMBUS_BUS_DEV_FUN           ((0x14 << 3) + 0)
#define FCH_ISA_BUS          0
#define FCH_ISA_DEV          20
#define FCH_ISA_FUNC         0
#define LPC_BUS_DEV_FUN             ((0x14 << 3) + 3)
#define FCH_LPC_BUS          0
#define FCH_LPC_DEV          20
#define FCH_LPC_FUNC         3
#define SD_BUS_DEV_FUN            ((0x14 << 3) + 6)      // SD Controller
#define SD_PCI_BUS           0
#define SD_PCI_DEV           20
#define SD_PCI_FUNC          6

#define ACPI_MMIO_BASE       0xFED80000ul
 #define FCH_CFG_BASE           0x000   // DWORD
 #define SMI_BASE               0x200   // DWORD
 #define PMIO_BASE              0x300   // DWORD
 #define PMIO2_BASE             0x400   // BYTE
 #define BIOS_RAM_BASE          0x500   // BYTE
 #define CMOS_RAM_BASE          0x600   // BYTE
 #define CMOS_BASE              0x700   // BYTE
 #define ASF_BASE               0x900   // DWORD
 #define SMBUS_BASE             0xA00   // DWORD
 #define WATCHDOG_BASE          0xB00   //
 #define HPET_BASE              0xC00   // DWORD
 #define IOMUX_BASE             0xD00   // BYTE
 #define MISC_BASE              0xE00
 #define SERIAL_DEBUG_BASE      0x1000
 #define SHADOW_TIMER_BASE      0x1100
 #define REMOTE_GPIO_BASE       0x1200
 #define REMOTE_MISC2_BASE      0x1300
 #define GFX_DAC_BASE           0x1400
 #define GPIO_BANK0_BASE        0x1500   // DWORD
 #define GPIO_BANK1_BASE        0x1600   // DWORD
 #define GPIO_BANK2_BASE        0x1700   // DWORD
 #define GPIO_BANK3_BASE        0x1800
 #define ACDC_BASE              0x1D00
 #define AOAC_BASE              0x1E00

//
// AB Configuration
//
// RegSpace field (AB_INDEX[31:29]
#define AXINDC         0               // AXINDC
#define AXINDP         2               // AXINDP
#define ABCFG          6               // ABCFG
#define AXCFG          4               // AXCFG
#define RCINDXC        1               // PCIEIND
#define RCINDXP        3               // PCIEIND_P

//
// ABCFG Registers
//
#define FCH_ABCFG_REG00     0x00  // VENDOR ID
#define FCH_ABCFG_REG08     0x08  // REVISION ID
#define FCH_ABCFG_REG40     0x40  // BL_EVENTCNT0LO
#define FCH_ABCFG_REG44     0x44  // BL_EVENTCNT1LO
#define FCH_ABCFG_REG48     0x48  // BL_EVENTCNTSEL
#define FCH_ABCFG_REG4A     0x4A  // BL_EVENTCNT0HI
#define FCH_ABCFG_REG4B     0x4B  // BL_EVENTCNT1HI
#define FCH_ABCFG_REG4C     0x4C  // BL_EVENTCNTCTL
#define FCH_ABCFG_REG50     0x50  // MISCCTL_50
#define FCH_ABCFG_REG54     0x54  // MISCCTL_54
#define FCH_ABCFG_REG58     0x58  // BL RAB CONTROL
#define FCH_ABCFG_REG60     0x60  // LINKWIDTH_CTL
#define FCH_ABCFG_REG64     0x64  // LINKWIDTH_UP_INTERVAL
#define FCH_ABCFG_REG68     0x68  // LINKWIDTH_DN_INVERVAL
#define FCH_ABCFG_REG6C     0x6C  // LINKWIDTH_UPSTREAM_DWORDS
#define FCH_ABCFG_REG70     0x70  // LINKWIDTH_DOWNSTREAM_DWORDS
#define FCH_ABCFG_REG74     0x74  // LINKWIDTH_THRESHOLD_INCREASE
#define FCH_ABCFG_REG78     0x78  // LINKWIDTH_THRESHOLD_DECREASE
#define FCH_ABCFG_REG80     0x80  // BL DMA PREFETCH CONTROL
#define FCH_ABCFG_REG88     0x88  //
#define FCH_ABCFG_REG8C     0x8C  //
#define FCH_ABCFG_REG90     0x90  // BIF CONTROL 0
#define FCH_ABCFG_REG94     0x94  // MSI CONTROL
#define FCH_ABCFG_REG98     0x98  // BIF CONTROL 1
#define FCH_ABCFG_REG9C     0x9C  // MISCCTL_9C
#define FCH_ABCFG_REGA0     0xA0  // BIF PHY CONTROL ENABLE
#define FCH_ABCFG_REGA4     0xA4  // BIF PHY CONTROL A4
#define FCH_ABCFG_REGA8     0xA8  // BIF PHY CONTROL A8
#define FCH_ABCFG_REGB0     0xB0  // HYPERFLASH-PCIE PORT MAPPING
#define FCH_ABCFG_REGB8     0xB8  //
#define FCH_ABCFG_REGB4     0xB4  //
#define FCH_ABCFG_REGBC     0xBC  //
#define FCH_ABCFG_REGC0     0xC0  // PCIE_GPP_ENABLE
#define FCH_ABCFG_REGC4     0xC4  // PCIE_P2P_INT_MAP
#define FCH_ABCFG_REGD0     0xD0  // MCTP_VDM_TX_FIFO_DATA
#define FCH_ABCFG_REGD4     0xD4  // MCTP_VMD_TX_CONTROL
#define FCH_ABCFG_REGE0     0xE0  // MCTP_VDM_RX_FIFO_DATA
#define FCH_ABCFG_REGE4     0xE4  // MCTP_VDM_RX_FIFO_STATUS
#define FCH_ABCFG_REGEC     0xEC  // MCTP_VDM_CONTROL
#define FCH_ABCFG_REGF0     0xF0  // GPP_UPSTREAM_CONTROL
#define FCH_ABCFG_REGF4     0xF4  // GPP_SYSTEM_ERROR_CONTROL
#define FCH_ABCFG_REGFC     0xFC  // FCH_TRAP_CONTROL
#define FCH_ABCFG_REG100    0x100 // FCH_TRAP0_ADDRL
#define FCH_ABCFG_REG104    0x104 // FCH_TRAP0_ADDRH
#define FCH_ABCFG_REG108    0x108 // FCH_TRAP0_CMD
#define FCH_ABCFG_REG10C    0x10C // FCH_TRAP1_DATA
#define FCH_ABCFG_REG110    0x110 // FCH_TRAP1_ADDRL
#define FCH_ABCFG_REG114    0x114 // FCH_TRAP1_ADDRH
#define FCH_ABCFG_REG118    0x118 // FCH_TRAP1_CMD
#define FCH_ABCFG_REG11C    0x11C // FCH_TRAP1_DATA
#define FCH_ABCFG_REG120    0x120 // FCH_TRAP2_ADDRL
#define FCH_ABCFG_REG124    0x124 // FCH_TRAP2_ADDRH
#define FCH_ABCFG_REG128    0x128 // FCH_TRAP2_CMD
#define FCH_ABCFG_REG12C    0x12C // FCH_TRAP2_DATA
#define FCH_ABCFG_REG130    0x130 // FCH_TRAP3_ADDRL
#define FCH_ABCFG_REG134    0x134 // FCH_TRAP3_ADDRH
#define FCH_ABCFG_REG138    0x138 // FCH_TRAP3_CMD
#define FCH_ABCFG_REG13C    0x13C // FCH_TRAP3_DATA
#define FCH_ABCFG_REG180    0x180 // FCH_DMA_TRAFFIC_CONTROL
#define FCH_ABCFG_REG184    0x184 // FCH_AXI_DMA_MEMORY_POWER_SAVING
#define FCH_ABCFG_REG208    0x208 // SDP_MISC
#define FCH_ABCFG_REG228    0x228 // SDP_DISCONNECT_CTL
#define FCH_ABCFG_REG22C    0x22C // SDP_DS_CTL1
#define FCH_ABCFG_REG238    0x238 // SDP_RSMU_CTL
#define FCH_ABCFG_REG300    0x300 // MCTP_VDM_RX_SMI_CONTROL
#define FCH_ABCFG_REG310    0x310 // BIF_GPP_STRAP_SYSTEM_0
#define FCH_ABCFG_REG314    0x314 // BIF_GPP_STRAP_SYSTEM_1
#define FCH_ABCFG_REG31C    0x31C // BIF_GPP_STRAP_LINK_CONTROL_0
#define FCH_ABCFG_REG320    0x320 // BIF_GPP_STRAP_LINK_CONTROL_LANE_A
#define FCH_ABCFG_REG324    0x324 // BIF_GPP_STRAP_LINK_CONTROL_LANE_B
#define FCH_ABCFG_REG328    0x328 // BIF_GPP_STRAP_LINK_CONTROL_LANE_C
#define FCH_ABCFG_REG32C    0x32C // BIF_GPP_STRAP_LINK_CONTROL_LANE_D
#define FCH_ABCFG_REG330    0x330 // BIF_GPP_STRAP_BIF_0
#define FCH_ABCFG_REG334    0x334 // BIF_GPP_STRAP_BIF_1
#define FCH_ABCFG_REG338    0x338 // BIF_GPP_STRAP_BIF_2
#define FCH_ABCFG_REG340    0x340 // BIF_GPP_STRAP_BIF_LANE_A
#define FCH_ABCFG_REG344    0x344 // BIF_GPP_STRAP_BIF_LANE_B
#define FCH_ABCFG_REG348    0x348 // BIF_GPP_STRAP_BIF_LANE_C
#define FCH_ABCFG_REG34C    0x34C // BIF_GPP_STRAP_BIF_LANE_D
#define FCH_ABCFG_REG350    0x350 // BIF_GPP_STRAP_PHY_LOGICAL _0
#define FCH_ABCFG_REG354    0x354 // BIF_GPP_STRAP_PHY_LOGICAL _1
#define FCH_ABCFG_REG404    0x404 // GPP0_SHADOW_COMMAND
#define FCH_ABCFG_REG418    0x418 // GPP0_SHADOW_BUS_NUMBER
#define FCH_ABCFG_REG41C    0x41C // GPP0_SHADOW_IO_LIMIT_BASE
#define FCH_ABCFG_REG420    0x420 // GPP0_SHADOW_MEM_LIMIT_BASE
#define FCH_ABCFG_REG424    0x424 // GPP0_SHADOW_PREF_MEM_LIMIT_BASE
#define FCH_ABCFG_REG428    0x428 // GPP0_SHADOW_PREF_MEM_BASE_UPPER
#define FCH_ABCFG_REG42C    0x42C // GPP0_SHADOW_PREF_MEM_LIMIT_UPPER
#define FCH_ABCFG_REG430    0x430 // GPP0_SHADOW_IO_LIMIT_BASE_UPPER
#define FCH_ABCFG_REG43C    0x43C // GPP0_SHADOW_BRIDGE_CONTROL
#define FCH_ABCFG_REG444    0x444 // GPP1_SHADOW_COMMAND
#define FCH_ABCFG_REG458    0x458 // GPP1_SHADOW_BUS_NUMBER
#define FCH_ABCFG_REG45C    0x45C // GPP1_SHADOW_IO_LIMIT_BASE
#define FCH_ABCFG_REG460    0x460 // GPP1_SHADOW_MEM_LIMIT_BASE
#define FCH_ABCFG_REG464    0x464 // GPP1_SHADOW_PREF_MEM_LIMIT_BASE
#define FCH_ABCFG_REG468    0x468 // GPP1_SHADOW_PREF_MEM_BASE_UPPER
#define FCH_ABCFG_REG46C    0x46C // GPP1_SHADOW_PREF_MEM_LIMIT_UPPER
#define FCH_ABCFG_REG470    0x470 // GPP1_SHADOW_IO_LIMIT_BASE_UPPER
#define FCH_ABCFG_REG47C    0x47C // GPP1_SHADOW_BRIDGE_CONTROL
#define FCH_ABCFG_REG484    0x484 // GPP2_SHADOW_COMMAND
#define FCH_ABCFG_REG498    0x498 // GPP2_SHADOW_BUS_NUMBER
#define FCH_ABCFG_REG49C    0x49C // GPP2_SHADOW_IO_LIMIT_BASE
#define FCH_ABCFG_REG4A0    0x4A0 // GPP2_SHADOW_MEM_LIMIT_BASE
#define FCH_ABCFG_REG4A4    0x4A4 // GPP2_SHADOW_PREF_MEM_LIMIT_BASE
#define FCH_ABCFG_REG4A8    0x4A8 // GPP2_SHADOW_PREF_MEM_BASE_UPPER
#define FCH_ABCFG_REG4AC    0x4AC // GPP2_SHADOW_PREF_MEM_LIMIT_UPPER
#define FCH_ABCFG_REG4B0    0x4B0 // GPP2_SHADOW_IO_LIMIT_BASE_UPPER
#define FCH_ABCFG_REG4BC    0x4BC // GPP2_SHADOW_BRIDGE_CONTROL
#define FCH_ABCFG_REG4C4    0x4C4 // GPP3_SHADOW_COMMAND
#define FCH_ABCFG_REG4D8    0x4D8 // GPP3_SHADOW_BUS_NUMBER
#define FCH_ABCFG_REG4DC    0x4DC // GPP3_SHADOW_IO_LIMIT_BASE
#define FCH_ABCFG_REG4E0    0x4E0 // GPP3_SHADOW_MEM_LIMIT_BASE
#define FCH_ABCFG_REG4E4    0x4E4 // GPP3_SHADOW_PREF_MEM_LIMIT_BASE
#define FCH_ABCFG_REG4E8    0x4E8 // GPP3_SHADOW_PREF_MEM_BASE_UPPER
#define FCH_ABCFG_REG4EC    0x4EC // GPP3_SHADOW_PREF_MEM_LIMIT_UPPER
#define FCH_ABCFG_REG4F0    0x4F0 // GPP3_SHADOW_IO_LIMIT_BASE_UPPER
#define FCH_ABCFG_REG4FC    0x4FC // GPP3_SHADOW_BRIDGE_CONTROL
#define FCH_ABCFG_REG10040  0x10040ul  // AL_EVENTCNT0LO
#define FCH_ABCFG_REG10044  0x10044ul  // AL_EVENTCNT1LO
#define FCH_ABCFG_REG10048  0x10048ul  // AL_EVENTCNTSEL
#define FCH_ABCFG_REG1004A  0x1004Aul  // AL_EVENTCNT0HI
#define FCH_ABCFG_REG1004B  0x1004Bul  // AL_EVENTCNT1HI
#define FCH_ABCFG_REG1004C  0x1004Cul  // AL_EVENTCNTCTL
#define FCH_ABCFG_REG10050  0x10050ul  // MISCCTL_10050
#define FCH_ABCFG_REG10054  0x10054ul  // AL_ARB_CTL
#define FCH_ABCFG_REG10056  0x10056ul  // AL_CLK_CTL
#define FCH_ABCFG_REG10058  0x10058ul  // AL RAB CONTROL
#define FCH_ABCFG_REG1005C  0x1005Cul  // AL MLT CONTROL
#define FCH_ABCFG_REG10060  0x10060ul  // AL DMA PREFETCH ENABLE
#define FCH_ABCFG_REG10064  0x10064ul  // AL DMA PREFETCH FLUSH CONTROL
#define FCH_ABCFG_REG10068  0x10068ul  // AL PREFETCH LIMIT
#define FCH_ABCFG_REG1006C  0x1006Cul  // AL DMA PREFETCH CONTROL
#define FCH_ABCFG_REG10070  0x10070ul  // MISCCTL_10070
#define FCH_ABCFG_REG10080  0x10080ul  // CLKMUXSTATUS
#define FCH_ABCFG_REG10090  0x10090ul  // BIF CONTROL 0
#define FCH_ABCFG_REG1009C  0x1009Cul  // MISCCTL_1009C

//
// AXINDC Registers
//
#define FCH_AX_INDXC_REG10  0x10
#define FCH_AX_INDXC_REG30  0x30
#define FCH_AX_DATAC_REG34  0x34
#define FCH_AX_INDXP_REG38  0x38
#define FCH_AX_DATAP_REG3C  0x3C

//Sata
#define FCH_SATA_REG00           0x000   // Vendor ID - R- 16 bits
#define FCH_SATA_REG02           0x002   // Device ID - RW -16 bits
#define FCH_SATA_REG04           0x004   // PCI Command - RW - 16 bits
#define FCH_SATA_REG06           0x006   // PCI Status - RW - 16 bits
#define FCH_SATA_REG08           0x008   // Revision ID/PCI Class Code - R - 32 bits - Offset: 08
#define FCH_SATA_REG0C           0x00C   // Cache Line Size - R/W - 8bits
#define FCH_SATA_REG0D           0x00D   // Latency Timer - RW - 8 bits
#define FCH_SATA_REG0E           0x00E   // Header Type - R - 8 bits
#define FCH_SATA_REG0F           0x00F   // BIST - R - 8 bits
#define FCH_SATA_REG10           0x010   // Base Address Register 0 - RW - 32 bits
#define FCH_SATA_REG14           0x014   // Base Address Register 1 - RW- 32 bits
#define FCH_SATA_REG18           0x018   // Base Address Register 2 - RW - 32 bits
#define FCH_SATA_REG1C           0x01C   // Base Address Register 3 - RW - 32 bits
#define FCH_SATA_REG20           0x020   // Base Address Register 4 - RW - 32 bits
#define FCH_SATA_REG24           0x024   // Base Address Register 5 - RW - 32 bits
#define FCH_SATA_REG2C           0x02C   // Subsystem Vendor ID - R - 16 bits
#define FCH_SATA_REG2D           0x02D   // Subsystem ID - R - 16 bits
#define FCH_SATA_REG30           0x030   // Expansion ROM Base Address - 32 bits
#define FCH_SATA_REG34           0x034   // Capabilities Pointer - R - 32 bits
#define FCH_SATA_REG3C           0x03C   // Interrupt Line - RW - 8 bits
#define FCH_SATA_REG3D           0x03D   // Interrupt Pin - R - 8 bits
#define FCH_SATA_REG3E           0x03E   // Min Grant - R - 8 bits
#define FCH_SATA_REG3F           0x03F   // Max Latency - R - 8 bits
#define FCH_SATA_REG40           0x040   // Configuration - RW - 32 bits
#define FCH_SATA_REG44           0x044   // Software Data Register - RW - 32 bits
#define FCH_SATA_REG48           0x048
#define FCH_SATA_REG4C           0x04C
#define FCH_SATA_REG50           0x050
#define FCH_SATA_REG52           0x052
#define FCH_SATA_REG54           0x054
#define FCH_SATA_REG58           0x058
#define FCH_SATA_REG5C           0x05C
#define FCH_SATA_REG5D           0x05D
#define FCH_SATA_REG5E           0x05E
#define FCH_SATA_REG60           0x060
#define FCH_SATA_REG64           0x064
#define FCH_SATA_REG68           0x068
#define FCH_SATA_REG69           0x069
#define FCH_SATA_REG70           0x070
#define FCH_SATA_REG74           0x074
#define FCH_SATA_REG78           0x078
#define FCH_SATA_REG7C           0x07C
#define FCH_SATA_REG80           0x080
#define FCH_SATA_REG84           0x084
#define FCH_SATA_REG86           0x086
#define FCH_SATA_REG87           0x087
#define FCH_SATA_REG88           0x088
#define FCH_SATA_REG8A           0x08A
#define FCH_SATA_REG8C           0x08C
#define FCH_SATA_REG8E           0x08E
#define FCH_SATA_REG90           0x090
#define FCH_SATA_REG92           0x092
#define FCH_SATA_REG94           0x094
#define FCH_SATA_REG96           0x096
#define FCH_SATA_REG98           0x098
#define FCH_SATA_REG9C           0x09C
#define FCH_SATA_REGA0           0x0A0
#define FCH_SATA_REGA4           0x0A4
#define FCH_SATA_REGA5           0x0A5
#define FCH_SATA_REGA8           0x0A8
#define FCH_SATA_REGAD           0x0AD
#define FCH_SATA_REGB0           0x0B0
#define FCH_SATA_REGB5           0x0B5
#define FCH_SATA_REGBD           0x0BD
#define FCH_SATA_REGC0           0x0C0
#define FCH_SATA_REGC4           0x0C4

#define FCH_SATA_BAR5_REG00      0x000   // PCI Bus Master - IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG04      0x004   // PRD Table Address - IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG08      0x008   // PCI Bus Master - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REG0C      0x00C   // PRD Table Address - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REG10      0x010   // PCI Bus Master2 - IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG1C      0x01C
#define FCH_SATA_BAR5_REG18      0x018   // PCI Bus Master2 - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REG20      0x020   // PRD Address - IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG24      0x024   // PCI Bus Master Byte Count - IDE0- RW - 32 bits
#define FCH_SATA_BAR5_REG28      0x028   // PRD Address - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REG2C      0x02C   // PCI Bus Master Byte Count - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REG40      0x040   // FIFO Valid Byte Count and Control - IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG44      0x044   // FIFO Valid Byte Count and Control - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REG48      0x048   // System Configuration Status - Command - RW - 32 bits
#define FCH_SATA_BAR5_REG4C      0x04C   // System Software Data Register - RW - 32 bits
#define FCH_SATA_BAR5_REG50      0x050   // FLAS Memory Address - Command + Status - RW - 32 bits
#define FCH_SATA_BAR5_REG54      0x054   // FLAS Memory Data - RW - 32 bits
#define FCH_SATA_BAR5_REG58      0x058   // EEPROM Memory Address - Command + Status - RW - 32 bits
#define FCH_SATA_BAR5_REG5C      0x05C   // EEPROM Memory Data - RW - 32 bits
#define FCH_SATA_BAR5_REG60      0x060   // FIFO Port - IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG68      0x068   // FIFO Pointers1- IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG6C      0x06C   // FIFO Pointers2- IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REG70      0x070   // FIFO Port - IDE1- RW - 32 bits
#define FCH_SATA_BAR5_REG78      0x078   // FIFO Pointers1- IDE1- RW - 32 bits
#define FCH_SATA_BAR5_REG7C      0x07C   // FIFO Pointers2- IDE1- RW - 32 bits
#define FCH_SATA_BAR5_REG80      0x080   // IDE0 Task File Register 0- RW - 32 bits
#define FCH_SATA_BAR5_REG84      0x084   // IDE0 Task File Register 1- RW - 32 bits
#define FCH_SATA_BAR5_REG88      0x088   // IDE0 Task File Register 2- RW - 32 bits
#define FCH_SATA_BAR5_REG8C      0x08C   // IDE0 Read Data - RW - 32 bits
#define FCH_SATA_BAR5_REG90      0x090   // IDE0 Task File Register 0 - Command Buffering - RW - 32 bits
#define FCH_SATA_BAR5_REG94      0x094   // IDE0 Task File Register 1 - Command Buffering - RW - 32 bits
#define FCH_SATA_BAR5_REG9C      0x09C   // IDE0 Virtual DMA/PIO Read Byte Count - RW - 32 bits
#define FCH_SATA_BAR5_REGA0      0x0A0   // IDE0 Task File Configuration + Status - RW - 32 bits
#define FCH_SATA_BAR5_REGB4      0x0B4   // Data Transfer Mode -IDE0 - RW - 32 bits
#define FCH_SATA_BAR5_REGC0      0x0C0   // IDE1 Task File Register 0 - RW - 32 bits
#define FCH_SATA_BAR5_REGC4      0x0C4   // IDE1 Task File Register 1 - RW - 32 bits
#define FCH_SATA_BAR5_REGC8      0x0C8   // IDE1 Task File Register 2 - RW - 32 bits
#define FCH_SATA_BAR5_REGCC      0x0CC   //  Read/Write Data - RW - 32 bits
#define FCH_SATA_BAR5_REGD0      0x0D0   // IDE1 Task File Register 0 - Command Buffering - RW - 32 bits
#define FCH_SATA_BAR5_REGD4      0x0D4   // IDE1 Task File Register 1 - Command Buffering - RW - 32 bits
#define FCH_SATA_BAR5_REGDC      0x0DC   // IDE1 Virtual DMA/PIO Read Byte Count - RW - 32 bits
#define FCH_SATA_BAR5_REGE0      0x0E0   // IDE1 Task File Configuration + Status - RW - 32 bits
#define FCH_SATA_BAR5_REGF4      0x0F4   // Data Transfer Mode - IDE1 - RW - 32 bits
#define FCH_SATA_BAR5_REGF8      0x0F8   // PORT Configuration
#define FCH_SATA_BAR5_REGFC      0x0FC
#define FCH_SATA_BAR5_REG100     0x0100  // Serial ATA SControl - RW - 32 bits - [Offset: 100h (channel 1) / 180
#define FCH_SATA_BAR5_REG104     0x0104  // Serial ATA Sstatus - RW - 32 bits - [Offset: 104h (channel 1) / 184h (cannel
#define FCH_SATA_BAR5_REG108     0x0108  // Serial ATA Serror - RW - 32 bits - [Offset: 108h (channel 1) / 188h (cannel
#define FCH_SATA_BAR5_REG10C     0x010C  // Serial ATA Sdevice - RW - 32 bits - [Offset: 10Ch (channel 1) / 18Ch (cannel
#define FCH_SATA_BAR5_REG110     0x0110  //
#define FCH_SATA_BAR5_REG144     0x0144  // Serial ATA PY Configuration - RW - 32 bits
#define FCH_SATA_BAR5_REG148     0x0148  // SIEN - RW - 32 bits - [Offset: 148 (channel 1) / 1C8 (cannel 2)]
#define FCH_SATA_BAR5_REG14C     0x014C  // SFISCfg - RW - 32 bits - [Offset: 14C (channel 1) / 1CC (cannel 2)]
#define FCH_SATA_BAR5_REG120     0x0120  //
#define FCH_SATA_BAR5_REG128     0x0128  // Port Serial ATA Status
#define FCH_SATA_BAR5_REG12C     0x012C  // Port Serial ATA Control
#define FCH_SATA_BAR5_REG130     0x0130
#define FCH_SATA_BAR5_REG1B0     0x01B0
#define FCH_SATA_BAR5_REG230     0x0230
#define FCH_SATA_BAR5_REG2B0     0x02B0
#define FCH_SATA_BAR5_REG330     0x0330
#define FCH_SATA_BAR5_REG3B0     0x03B0
#define FCH_SATA_BAR5_REG430     0x0430
#define FCH_SATA_BAR5_REG4B0     0x04B0

//
//  FCH CFG device  0x780B
//  Device 20 (0x14) Func 0
//
#define FCH_CFG_REG00            0x000       // VendorID - R
#define FCH_CFG_REG02            0x002       // DeviceID - R
#define FCH_CFG_REG04            0x004       // Command- RW
#define FCH_CFG_REG05            0x005       // Command- RW
#define FCH_CFG_REG06            0x006       // STATUS- RW
#define FCH_CFG_REG08            0x008       // Revision ID/Class Code- R
#define FCH_CFG_REG0A            0x00A       //
#define FCH_CFG_REG0B            0x00B       //
#define FCH_CFG_REG0C            0x00C       // Cache Line Size- R
#define FCH_CFG_REG0D            0x00D       // Latency Timer- R
#define FCH_CFG_REG0E            0x00E       // Header Type- R
#define FCH_CFG_REG0F            0x00F       // BIST- R
#define FCH_CFG_REG10            0x010       // Base Address 0- R
#define FCH_CFG_REG11            0x011       //;
#define FCH_CFG_REG12            0x012       //;
#define FCH_CFG_REG13            0x013       //;
#define FCH_CFG_REG14            0x014       // Base Address 1- R
#define FCH_CFG_REG18            0x018       // Base Address 2- R
#define FCH_CFG_REG1C            0x01C       // Base Address 3- R
#define FCH_CFG_REG20            0x020       // Base Address 4- R
#define FCH_CFG_REG24            0x024       // Base Address 5- R
#define FCH_CFG_REG28            0x028       // Cardbus CIS Pointer- R
#define FCH_CFG_REG2C            0x02C       // Subsystem Vendor ID- W
#define FCH_CFG_REG2E            0x02E       // Subsystem ID- W
#define FCH_CFG_REG30            0x030       // Expansion ROM Base Address - R
#define FCH_CFG_REG34            0x034       // Capability Pointer - R  (800) default changed as 0x00
#define FCH_CFG_REG3C            0x03C       // Interrupt Line - R
#define FCH_CFG_REG3D            0x03D       // Interrupt Pin - R
#define FCH_CFG_REG3E            0x03E       // Min_Gnt - R
#define FCH_CFG_REG3F            0x03F       // Max_Lat - R


//
//  FCH LPC Device  0x780E
//  Device 20 (0x14) Func 3
//
#define FCH_LPC_REG00            0x00        // VID- R
#define FCH_LPC_REG02            0x02        // DID- R
#define FCH_LPC_REG04            0x04        // CMD- RW
#define FCH_LPC_REG06            0x06        // STATUS- RW
#define FCH_LPC_REG08            0x08        // Revision  ID/Class Code - R
#define FCH_LPC_REG0C            0x0C        // Cache Line Size - R
#define FCH_LPC_REG0D            0x0D        // Latency Timer - R
#define FCH_LPC_REG0E            0x0E        // Header Type - R
#define FCH_LPC_REG0F            0x0F        // BIST- R
#define FCH_LPC_REG10            0x10        // Base Address Reg 0- RW*
#define FCH_LPC_REG2C            0x2C        // Subsystem ID & Subsystem Vendor ID - Wo/Ro
#define FCH_LPC_REG34            0x34        // Capabilities Pointer - Ro
#define FCH_LPC_REG40            0x40        // PCI Control - RW
#define FCH_LPC_REG44            0x44        // IO Port Decode Enable Register 1- RW
#define FCH_LPC_REG45            0x45        // IO Port Decode Enable Register 2- RW
#define FCH_LPC_REG46            0x46        // IO Port Decode Enable Register 3- RW
#define FCH_LPC_REG47            0x47        // IO Port Decode Enable Register 4- RW
#define FCH_LPC_REG48            0x48        // IO/Mem Port Decode Enable Register 5- RW
#define FCH_LPC_REG49            0x49        // LPC Sync Timeout Count - RW
#define FCH_LPC_REG4A            0x4A        // IO/Mem Port Decode Enable Register 6- RW
#define FCH_LPC_REG4C            0x4C        // Memory Range Register - RW
#define FCH_LPC_REG50            0x50        // Rom Protect 0 - RW
#define FCH_LPC_REG54            0x54        // Rom Protect 1 - RW
#define FCH_LPC_REG58            0x58        // Rom Protect 2 - RW
#define FCH_LPC_REG5C            0x5C        // Rom Protect 3 - RW
#define FCH_LPC_REG60            0x60        // PCI Memory Start Address of LPC Target Cycles -
#define FCH_LPC_REG62            0x62        // PCI Memory End Address of LPC Target Cycles -
#define FCH_LPC_REG64            0x64        // PCI IO base Address of Wide Generic Port - RW
#define FCH_LPC_REG65            0x65
#define FCH_LPC_REG66            0x66
#define FCH_LPC_REG67            0x67
#define FCH_LPC_REG68            0x68        // LPC ROM Address Range 1 (Start Address) - RW
#define FCH_LPC_REG69            0x69
#define FCH_LPC_REG6A            0x6A        // LPC ROM Address Range 1 (End Address) - RW
#define FCH_LPC_REG6B            0x6B
#define FCH_LPC_REG6C            0x6C        // LPC ROM Address Range 2 (Start Address)- RW
#define FCH_LPC_REG6D            0x6D
#define FCH_LPC_REG6E            0x6E        // LPC ROM Address Range 2 (End Address) - RW
#define FCH_LPC_REG6F            0x6F
#define FCH_LPC_REG70            0x70        // Firmware ub Select - RW*
#define FCH_LPC_REG71            0x71
#define FCH_LPC_REG72            0x72
#define FCH_LPC_REG73            0x73
#define FCH_LPC_REG74            0x74        // Alternative Wide IO Range Enable- W/R
#define FCH_LPC_REG78            0x78        // Miscellaneous Control Bits- W/R
#define FCH_LPC_REG79            0x79        // Miscellaneous Control Bits- W/R
#define FCH_LPC_REG7C            0x7C        // TPM (trusted plant form module) reg- W/R
#define FCH_LPC_REG9C            0x9C
#define FCH_LPC_REG80            0x80        // MSI Capability Register- R
#define FCH_LPC_REGA0            0x0A0       // SPI base address
#define FCH_LPC_REGA1            0x0A1       // SPI base address
#define FCH_LPC_REGA2            0x0A2       // SPI base address
#define FCH_LPC_REGA3            0x0A3       // SPI base address
#define FCH_LPC_REGA4            0x0A4
#define FCH_LPC_REGB8            0x0B8
#define FCH_LPC_REGBA            0x0BA       // EcControl
#define FCH_LPC_REGBB            0x0BB       // HostControl
#define FCH_LPC_REGC8            0x0C8
#define FCH_LPC_REGCC            0x0CC       // AutoRomCfg
#define FCH_LPC_REGD0            0x0D0
#define FCH_LPC_REGD3            0x0D3
#define FCH_LPC_REGD4            0x0D4

//
//  FCH SD
//  Device 20 (0x14) Func 6
//
#define SD_PCI_REG10              0x10
#define SD_PCI_REG2C              0x2C
#define SD_PCI_REGA4              0xA4
#define SD_PCI_REGA8              0xA8
#define SD_PCI_REGAC              0xAC
#define SD_PCI_REGB0              0xB0
#define SD_PCI_REGB8              0xB8
#define SD_PCI_REGBC              0xBC
#define SD_PCI_REGD0              0xD0
#define SD_PCI_REGF0              0xF0
#define SD_PCI_REGF4              0xF4
#define SD_PCI_REGF8              0xF8
#define SD_PCI_REGFC              0xFC
#define FCH_SD_BAR_REG28          0x28       // SDHC_CTRL1
 #define SD_CARD_PRESENT           BIT0
#define FCH_SD_BAR_REG2C          0x2C       // SDHC_CTRL2
 #define FCH_SD_FREQUENCY_SLT      BIT2
#define FCH_SD_BAR_REG3C          0x3C       // SDHC_HOST_CTRL2
 #define FCH_SD_1_8V               BIT3

//
//  FCH MMIO Base (SMI)
//    offset : 0x200
//
#define FCH_SMI_REG00            0x00         // EventStatus
#define FCH_SMI_REG04            0x04         // EventEnable
#define FCH_SMI_REG08            0x08         // SciTrig
#define FCH_SMI_REG0C            0x0C         // SciLevl
#define FCH_SMI_REG10            0x10         // SmiSciStatus
#define FCH_SMI_REG14            0x14         // SmiSciEn
#define FCH_SMI_REG18            0x18         // ForceSciEn
#define FCH_SMI_REG1C            0x1C         // SciRwData
#define FCH_SMI_REG3C            0x3C         // DataErrorStatus
#define FCH_SMI_REG20            0x20         // SciS0En
#define FCH_SMI_Gevent0          0x40         // SciMap0
#define FCH_SMI_Gevent1          0x41         // SciMap1
#define FCH_SMI_Gevent2          0x42         // SciMap2
#define FCH_SMI_Gevent3          0x43         // SciMap3
#define FCH_SMI_Gevent4          0x44         // SciMap4
#define FCH_SMI_Gevent5          0x45         // SciMap5
#define FCH_SMI_Gevent6          0x46         // SciMap6
#define FCH_SMI_Gevent7          0x47         // SciMap7
#define FCH_SMI_Gevent8          0x48         // SciMap8
#define FCH_SMI_Gevent9          0x49         // SciMap9
#define FCH_SMI_Gevent10         0x4A         // SciMap10
#define FCH_SMI_Gevent11         0x4B         // SciMap11
#define FCH_SMI_Gevent12         0x4C         // SciMap12
#define FCH_SMI_Gevent13         0x4D         // SciMap13
#define FCH_SMI_Gevent14         0x4E         // SciMap14
#define FCH_SMI_Gevent15         0x4F         // SciMap15
#define FCH_SMI_Gevent16         0x50         // SciMap16
#define FCH_SMI_Gevent17         0x51         // SciMap17
#define FCH_SMI_Gevent18         0x52         // SciMap18
#define FCH_SMI_Gevent19         0x53         // SciMap19
#define FCH_SMI_Gevent20         0x54         // SciMap20
#define FCH_SMI_Gevent21         0x55         // SciMap21
#define FCH_SMI_Gevent22         0x56         // SciMap22
#define FCH_SMI_Gevent23         0x57         // SciMap23
#define FCH_SMI_SCIMAP24         0x58         // SciMap24
#define FCH_SMI_SCIMAP25         0x59         // SciMap25
#define FCH_SMI_SCIMAP26         0x5A         // SciMap26
#define FCH_SMI_SCIMAP27         0x5B         // SciMap27
#define FCH_SMI_SCIMAP28         0x5C         // SciMap28
#define FCH_SMI_SCIMAP29         0x5D         // SciMap29
#define FCH_SMI_SCIMAP30         0x5E         // SciMap30
#define FCH_SMI_SCIMAP31         0x5F         // SciMap31
#define FCH_SMI_SCIMAP32         0x60         // SciMap32
#define FCH_SMI_SCIMAP33         0x61         // SciMap33
#define FCH_SMI_SCIMAP34         0x62         // SciMap34
#define FCH_SMI_SCIMAP35         0x63         // SciMap35
#define FCH_SMI_SCIMAP36         0x64         // SciMap36
#define FCH_SMI_SCIMAP37         0x65         // SciMap37
#define FCH_SMI_SCIMAP38         0x66         // SciMap38
#define FCH_SMI_SCIMAP39         0x67         // SciMap39
#define FCH_SMI_SCIMAP40         0x68         // SciMap40
#define FCH_SMI_SCIMAP41         0x69         // SciMap41
#define FCH_SMI_SCIMAP42         0x6A         // SciMap42
#define FCH_SMI_SCIMAP43         0x6B         // SciMap43
#define FCH_SMI_SCIMAP44         0x6C         // SciMap44
#define FCH_SMI_SCIMAP45         0x6D         // SciMap45
#define FCH_SMI_SCIMAP46         0x6E         // SciMap46
#define FCH_SMI_SCIMAP47         0x6F         // SciMap47
#define FCH_SMI_SCIMAP48         0x70         // SciMap48
#define FCH_SMI_SCIMAP49         0x71         // SciMap49
#define FCH_SMI_SCIMAP50         0x72         // SciMap50
#define FCH_SMI_SCIMAP51         0x73         // SciMap51
#define FCH_SMI_SCIMAP52         0x74         // SciMap52
#define FCH_SMI_SCIMAP53         0x75         // SciMap53
#define FCH_SMI_SCIMAP54         0x76         // SciMap54
#define FCH_SMI_SCIMAP55         0x77         // SciMap55
#define FCH_SMI_SCIMAP56         0x78         // SciMap56
#define FCH_SMI_SCIMAP57         0x79         // SciMap57
#define FCH_SMI_SCIMAP58         0x7A         // SciMap58

#define FCH_SMI_REG80            0x80         // SmiStatus0
#define FCH_SMI_REG84            0x84         // SmiStatus1
#define FCH_SMI_REG88            0x88         // SmiStatus2
#define FCH_SMI_REG8C            0x8C         // SmiStatus3
#define FCH_SMI_REG90            0x90         // SmiStatus4
#define FCH_SMI_REG94            0x94         // SmiPointer
#define FCH_SMI_REG96            0x96         // SmiTimer
#define FCH_SMI_REG98            0x98         // SmiTrig
#define FCH_SMI_REG9C            0x9C         // SmiTrig
#define FCH_SMI_REGA0            0xA0
#define FCH_SMI_REGA1            0xA1
#define FCH_SMI_REGA2            0xA2
#define FCH_SMI_REGA3            0xA3
#define FCH_SMI_REGA4            0xA4
#define FCH_SMI_REGA5            0xA5
#define FCH_SMI_REGA6            0xA6
#define FCH_SMI_REGA7            0xA7
#define FCH_SMI_REGA8            0xA8
#define FCH_SMI_REGA9            0xA9
#define FCH_SMI_REGAA            0xAA
#define FCH_SMI_REGAB            0xAB
#define FCH_SMI_REGAC            0xAC
#define FCH_SMI_REGAD            0xAD
#define FCH_SMI_REGAE            0xAE
#define FCH_SMI_REGAF            0xAF
#define FCH_SMI_REGB0            0xB0
#define FCH_SMI_REGB1            0xB1
#define FCH_SMI_REGB2            0xB2
#define FCH_SMI_REGB3            0xB3
#define FCH_SMI_REGB4            0xB4
#define FCH_SMI_REGB5            0xB5
#define FCH_SMI_REGB6            0xB6
#define FCH_SMI_REGB7            0xB7
#define FCH_SMI_REGB8            0xB8
#define FCH_SMI_REGB9            0xB9
#define FCH_SMI_REGBA            0xBA
#define FCH_SMI_REGBB            0xBB
#define FCH_SMI_REGBC            0xBC
#define FCH_SMI_REGBD            0xBD
#define FCH_SMI_REGBE            0xBE
#define FCH_SMI_REGBF            0xBF
#define FCH_SMI_REGC0            0xC0
#define FCH_SMI_REGC1            0xC1
#define FCH_SMI_REGC2            0xC2
#define FCH_SMI_REGC3            0xC3
#define FCH_SMI_REGC4            0xC4
#define FCH_SMI_REGC5            0xC5
#define FCH_SMI_REGC6            0xC6
#define FCH_SMI_REGC7            0xC7
#define FCH_SMI_REGC8            0xC8
#define FCH_SMI_REGCA            0xCA
#define FCH_SMI_REGCC            0xCC
#define FCH_SMI_REGCE            0xCE
#define FCH_SMI_REGD0            0xD0
#define FCH_SMI_REGD4            0xD4
#define FCH_SMI_REGD8            0xD8
#define FCH_SMI_REGDC            0xDC
#define FCH_SMI_REGE0            0xE0
#define FCH_SMI_REGE4            0xE4
#define FCH_SMI_REGE8            0xE8
#define FCH_SMI_REGEC            0xEC
#define FCH_SMI_REGF0            0xF0
#define FCH_SMI_REGF4            0xF4
#define FCH_SMI_REGF8            0xF8
#define FCH_SMI_REGFC            0xFC
 #define FCH_SMI_TRAPPING_WRITE   0x01
 #define SMI_TIMER_ENABLE         BIT15

//
//  FCH MMIO Base (PMIO)
//    offset : 0x300
//
#define FCH_PMIOA_REG00          0x00         // ISA Decode
#define FCH_PMIOA_REG04          0x04         // ISA Control
#define FCH_PMIOA_REG08          0x08         // PCI Control
#define FCH_PMIOA_REG0C          0x0C         // StpClkSmaf
#define FCH_PMIOA_REG10          0x10         // ToggleOnCf9
#define FCH_PMIOA_REG12          0x12         //
#define FCH_PMIOA_REG14          0x14         //
#define FCH_PMIOA_REG16          0x16         //
#define FCH_PMIOA_REG18          0x18         //
#define FCH_PMIOA_REG1C          0x1C         //
#define FCH_PMIOA_REG1E          0x1E         //
#define FCH_PMIOA_REG20          0x20         //
#define FCH_PMIOA_REG22          0x22         //
#define FCH_PMIOA_REG24          0x24         //
#define FCH_PMIOA_REG26          0x26         //
#define FCH_PMIOA_REG28          0x28         //
#define FCH_PMIOA_REG2A          0x2A         //
#define FCH_PMIOA_REG2C          0x2C         //
#define FCH_PMIOA_REG2E          0x2E         //
#define FCH_PMIOA_REG34          0x34         //
#define FCH_PMIOA_REG3C          0x3C         //
#define FCH_PMIOA_REG40          0x40         //
#define FCH_PMIOA_REG44          0x44         // BootTimerEn
#define FCH_PMIOA_REG48          0x48         //
#define FCH_PMIOA_REG4C          0x4C         //
#define FCH_PMIOA_REG50          0x50         //
#define FCH_PMIOA_REG54          0x54         // SerialIrqConfig
#define FCH_PMIOA_REG56          0x56         // RtcControl
#define FCH_PMIOA_REG58          0x58         // VRT_T1
#define FCH_PMIOA_REG59          0x59         // VRT_T2
#define FCH_PMIOA_REG5A          0x5A         // IntruderControl
#define FCH_PMIOA_REG5B          0x5B         // RtcShadow
#define FCH_PMIOA_REG5C          0x5C
#define FCH_PMIOA_REG5D          0x5D
#define FCH_PMIOA_REG5E          0x5E         // RtcExtIndex
#define FCH_PMIOA_REG5F          0x5F         // RtcExtData
#define FCH_PMIOA_REG60          0x60         // AcpiPm1EvtBlk
#define FCH_PMIOA_REG62          0x62         // AcpiPm1CntBlk
#define FCH_PMIOA_REG64          0x64         // AcpiPmTmrBlk
#define FCH_PMIOA_REG66          0x66         // P_CNTBlk
#define FCH_PMIOA_REG68          0x68         // AcpiGpe0Blk
#define FCH_PMIOA_REG6A          0x6A         // AcpiSmiCmd
#define FCH_PMIOA_REG6C          0x6C         // AcpiPm2CntBlk
#define FCH_PMIOA_REG6E          0x6E         // AcpiPmaCntBlk
#define FCH_PMIOA_REG70          0x70         //
#define FCH_PMIOA_REG74          0x74         // AcpiConfig
#define FCH_PMIOA_REG78          0x78         // WakeIoAddr
#define FCH_PMIOA_REG7A          0x7A         // HaltCountEn
#define FCH_PMIOA_REG7C          0x7C         // C1eWrPortAdr
#define FCH_PMIOA_REG7E          0x7E         // CStateEn
#define FCH_PMIOA_REG7F          0x7F         // CStateEn
#define FCH_PMIOA_REG80          0x80         // BreakEvent
#define FCH_PMIOA_REG84          0x84         // AutoArbEn
#define FCH_PMIOA_REG88          0x88         // CStateControl
#define FCH_PMIOA_REG89          0x89         //
#define FCH_PMIOA_REG8C          0x8C         //
#define FCH_PMIOA_REG8E          0x8E         // PopUpEndTime
#define FCH_PMIOA_REG90          0x90         // C4Control
#define FCH_PMIOA_REG94          0x94         // CStateTiming0
#define FCH_PMIOA_REG96          0x96         //
#define FCH_PMIOA_REG97          0x97         //
#define FCH_PMIOA_REG98          0x98         // CStateTiming1
#define FCH_PMIOA_REG99          0x99         //
#define FCH_PMIOA_REG9B          0x9B         //
#define FCH_PMIOA_REG9C          0x9C         // C2Count
#define FCH_PMIOA_REG9D          0x9D         // C3Count
#define FCH_PMIOA_REG9E          0x9E         // C4Count
#define FCH_PMIOA_REGA0          0xA0         // MessageCState
#define FCH_PMIOA_REGA4          0xA4         //
#define FCH_PMIOA_REGA8          0xA8         //
#define FCH_PMIOA_REGAA          0xAA         //
#define FCH_PMIOA_REGAC          0xAC         //
#define FCH_PMIOA_REGAE          0xAE         //
#define FCH_PMIOA_REGB0          0xB0         //
#define FCH_PMIOA_REGB4          0xB4         //
#define FCH_PMIOA_REGB6          0xB6         //
#define FCH_PMIOA_REGB7          0xB7         //
#define FCH_PMIOA_REGB8          0xB8         // TPRESET2
#define FCH_PMIOA_REGB9          0xB9         //
#define FCH_PMIOA_REGBA          0xBA         // S_StateControl
#define FCH_PMIOA_REGBB          0xBB         //
#define FCH_PMIOA_REGBC          0xBC         // ThrottlingControl
#define FCH_PMIOA_REGBE          0xBE         // ResetControl
#define FCH_PMIOA_REGBF          0xBF         // ResetControl
#define FCH_PMIOA_REGC0          0xC0         // S5Status
#define FCH_PMIOA_REGC2          0xC2         // ResetStatus
#define FCH_PMIOA_REGC4          0xC4         // ResetCommand
#define FCH_PMIOA_REGC5          0xC5         // CF9Shadow
#define FCH_PMIOA_REGC6          0xC6         // HTControl
#define FCH_PMIOA_REGC8          0xC8         // Misc
#define FCH_PMIOA_REGCC          0xCC         // IoDrvSth
#define FCH_PMIOA_REGD0          0xD0         //
#define FCH_PMIOA_REGD2          0xD2         // PmioDebug
#define FCH_PMIOA_REGD3          0xD3         //
#define FCH_PMIOA_REGD5          0xD5         // AltMmioEn
#define FCH_PMIOA_REGD6          0xD6         // AltMmioBase
#define FCH_PMIOA_REGD7          0xD7         //
#define FCH_PMIOA_REGD8          0xD8         // MiscIndex
#define FCH_PMIOA_REGD9          0xD9         // MiscData
#define FCH_PMIOA_REGDA          0xDA         //
#define FCH_PMIOA_REGDC          0xDC         // HyperFlashConfig
#define FCH_PMIOA_REGDE          0xDE         // ABConfig
#define FCH_PMIOA_REGE0          0xE0         // ABRegBar
#define FCH_PMIOA_REGE4          0xE4
#define FCH_PMIOA_REGE6          0xE6         //
#define FCH_PMIOA_REGE7          0xE7
#define FCH_PMIOA_REGE8          0xE8
#define FCH_PMIOA_REGEA          0xEA         //
#define FCH_PMIOA_REGEB          0xEB         //
#define FCH_PMIOA_REGEC          0xEC         // LpcGating
#define FCH_PMIOA_REGED          0xED         //
#define FCH_PMIOA_REGEE          0xEE         //
#define FCH_PMIOA_REGEF          0xEF         //
#define FCH_PMIOA_REGF0          0xF0         //
#define FCH_PMIOA_REGF2          0xF2         //
#define FCH_PMIOA_REGF3          0xF3         //
#define FCH_PMIOA_REGF4          0xF4         //
#define FCH_PMIOA_REGF6          0xF6         //
#define FCH_PMIOA_REGF8          0xF8         //
#define FCH_PMIOA_REGFC          0xFC         // TraceMemoryEn

//
//  FCH MMIO Base (PMIO2)
//    offset : 0x400
//
#define FCH_PMIO2_REG00          0x00        // Fan0InputControl
#define FCH_PMIO2_REG01          0x01        // Fan0Control
#define FCH_PMIO2_REG02          0x02        // Fan0Freq
#define FCH_PMIO2_REG03          0x03        // LowDuty0
#define FCH_PMIO2_REG04          0x04        // MidDuty0

#define FCH_PMIO2_REG10          0x00        // Fan1InputControl
#define FCH_PMIO2_REG11          0x01        // Fan1Control
#define FCH_PMIO2_REG12          0x02        // Fan1Freq
#define FCH_PMIO2_REG13          0x03        // LowDuty1
#define FCH_PMIO2_REG14          0x04        // MidDuty1

#define FCH_PMIO2_REG63          0x63        // SampleFreqDiv
#define FCH_PMIO2_REG69          0x69        // Fan0 Speed
#define FCH_PMIO2_REG95          0x95        // Temperature
#define FCH_PMIO2_REGB8          0xB8        // Voltage
#define FCH_PMIO2_REGEA          0xEA        // Hwm_Calibration

#define FCH_PMIO2_REG92          0x92        //
#define FCH_PMIO2_REGF8          0xF8        // VoltageSamleSel
#define FCH_PMIO2_REGF9          0xF9        // TempSampleSel

//
//  FCH MMIO Base (GPIO BANK0)
//    offset : 0x1500
//
#define FCH_GPIO_PULL_UP_ENABLE      BIT4
#define FCH_GPIO_PULL_DOWN_ENABLE    BIT5
#define FCH_GPIO_OUTPUT_VALUE        BIT6
#define FCH_GPIO_OUTPUT_ENABLE       (1 << 7)

#define FCH_GPIO_014_BP_AGPIO5            0x14
#define FCH_GPIO_018_BP_AGPIO6            0x18

#define FCH_GPIO_10C_GPIO55_AGPI067       0x10C
#define FCH_GPIO_118_GPIO59_AGPI070       0x118

//
//  FCH MMIO Base (IoMux)
//    offset : 0xD00
//

//
//  FCH MMIO Base (SMBUS)
//    offset : 0xA00
//
#define FCH_SMBUS_REG00               0x00        // SMBusStatus
#define FCH_SMBUS_REG01               0x01        // SMBusSlaveStatus
#define FCH_SMBUS_REG02               0x02        // SMBusControl
 #define FCH_SMB_CMD_QUICK             0x00 << 2  // Quick Read or Write
 #define FCH_SMB_CMD_BYTE              0x01 << 2  // Byte Read or Write
 #define FCH_SMB_CMD_BYTE_DATA         0x02 << 2  // Byte Data Read or Write
 #define FCH_SMB_CMD_WORD_DATA         0x03 << 2  // Word Data Read or Write
 #define FCH_SMB_CMD_BLOCK             0x05 << 2  // Block Read or Write
 #define FCH_SMB_CMD_START             BIT6
#define FCH_SMBUS_REG03               0x03        // SMBusHostCmd
#define FCH_SMBUS_REG04               0x04        // SMBusAddress
#define FCH_SMBUS_REG05               0x05        // SMBusData0
#define FCH_SMBUS_REG06               0x06        // SMBusData1
#define FCH_SMBUS_REG07               0x07        // SMBusBlockData
#define FCH_SMBUS_REG08               0x08        // SMBusSlaveControl
#define FCH_SMBUS_REG12               0x12        //   I2CbusConfig
#define FCH_SMBUS_REG14               0x14        // SMBusAutoPoll
 #define FCH_SMB_AUTO_POLL_EN          BIT0
 #define FCH_SMB_POLL2BYTE             BIT7
#define FCH_SMBUS_REG16               0x16        // SMBusPausePoll
#define FCH_SMBUS_REG17               0x17        // SMBusHostCmd2

//
//  FCH MMIO Base (MISC)
//    offset : 0xE00
//
#define FCH_MISC_REG00           0x00        //  ClkCntrl0
#define FCH_MISC_REG04           0x04        //  ClkCntrl1
#define FCH_MISC_REG08           0x08        //  ClkCntrl2
#define FCH_MISC_REG0C           0x0C        //  ClkCntrl3
#define FCH_MISC_REG10           0x10        //  ClkCntrl4
#define FCH_MISC_REG14           0x14        //   ClkCntrl5
#define FCH_MISC_REG18           0x18        //   ClkCntrl6
#define FCH_MISC_REG1C           0x1C
#define FCH_MISC_REG20           0x20
#define FCH_MISC_REG30           0x30         // OscFreqCounter
#define FCH_MISC_REG34           0x34         //  HpetClkPeriod
#define FCH_MISC_REG28           0x28         //  ClkDrvSth2
#define FCH_MISC_REG2C           0x2C
#define FCH_MISC_REG40           0x40         //  MiscCntrl      for clock only
#define FCH_MISC_REG41           0x41         //  MiscCntr2
#define FCH_MISC_REG42           0x42         //  MiscCntr3
#define FCH_MISC_REG44           0x44         //  ValueOnPort80
#define FCH_MISC_REG50           0x50         //
#define FCH_MISC_REG6C           0x6C         //  EcoBit2
#define FCH_MISC_REG80           0x80
#define FCH_MISC_REGB6           0xB6
#define FCH_MISC_REG84           0x84         //  StrapOverride
#define FCH_MISC_REGC0           0xC0        //  CPU_Pstate0
#define FCH_MISC_REGC4           0xC4         //  CPU_Pstate1
#define FCH_MISC_REGD0           0xD0         //  CPU_Cstate0
#define FCH_MISC_REGD4           0xD4         //  CPU_Cstate1
#define FCH_MISC_REGF0           0xF0         //  SataPortSts

//
//  FCH MMIO Base (SERIAL_DEBUG_BASE)
//    offset : 0x1000
//
#define FCH_SDB_REG00            0x00        //
#define FCH_SDB_REG74            0x74


//
//  FCH RTC register
//
#define FCH_RTC_REG00            0x00        // Seconds - RW
#define FCH_RTC_REG01            0x01        // Seconds Alarm - RW
#define FCH_RTC_REG02            0x02        // Minutes - RW
#define FCH_RTC_REG03            0x03        // Minutes Alarm - RW
#define FCH_RTC_REG04            0x04        // ours - RW
#define FCH_RTC_REG05            0x05        // ours Alarm- RW
#define FCH_RTC_REG06            0x06        // Day of Week - RW
#define FCH_RTC_REG07            0x07        // Date of Mont - RW
#define FCH_RTC_REG08            0x08        // Mont - RW
#define FCH_RTC_REG09            0x09        // Year - RW
#define FCH_RTC_REG0A            0x0A        // Register A - RW
#define FCH_RTC_REG0B            0x0B        // Register B - RW
#define FCH_RTC_REG0C            0x0C        // Register C - R
#define FCH_RTC_REG0D            0x0D        // DateAlarm - RW
#define FCH_RTC_REG32            0x32        // AltCentury - RW
#define FCH_RTC_REG48            0x48        // Century - RW
#define FCH_RTC_REG50            0x50        // Extended RAM Address Port - RW
#define FCH_RTC_REG53            0x53        // Extended RAM Data Port - RW
#define FCH_RTC_REG7E            0x7E        // RTC Time Clear - RW
#define FCH_RTC_REG7F            0x7F        // RTC RAM Enable - RW

#define FCH_ECMOS_REG00          0x00        // scratch - reg
#define FCH_ECMOS_REG01          0x01
#define FCH_ECMOS_REG02          0x02
#define FCH_ECMOS_REG03          0x03
#define FCH_ECMOS_REG04          0x04
#define FCH_ECMOS_REG05          0x05
#define FCH_ECMOS_REG06          0x06
#define FCH_ECMOS_REG07          0x07
#define FCH_ECMOS_REG08          0x08        // save 32BIT Physical address of Config structure
#define FCH_ECMOS_REG09          0x09
#define FCH_ECMOS_REG0A          0x0A
#define FCH_ECMOS_REG0B          0x0B
#define FCH_ECMOS_REG0C          0x0C        //;save MODULE_ID
#define FCH_ECMOS_REG0D          0x0D        //;Reserve for NB

//  FCH AOAC Base (FCH_AOAC_BASE)
//    offset : 0x1E00
//
#define FCH_AOAC_REG00           0x00         // PerfMonControl
#define FCH_AOAC_REG04           0x04         // PerfMonTimeLimit
#define FCH_AOAC_REG08           0x08         // PerfMonWeight[3:0]
#define FCH_AOAC_REG0C           0x0C         // PerfMonWeight[7:4]
#define FCH_AOAC_REG10           0x10         // PerfMonTrafficCnt[1:0]
#define FCH_AOAC_REG14           0x14         // PerfMonTrafficCnt[3:2]
#define FCH_AOAC_REG18           0x18         // PerfMonTrafficCnt[5:4]
#define FCH_AOAC_REG1C           0x1C         // PerfMonTrafficCnt[7:6]
#define FCH_AOAC_REG20           0x20         // PerfMonTrafficCntAll
#define FCH_AOAC_REG24           0x24         // PerfMonIntrCnt
#define FCH_AOAC_REG28           0x28         //
#define FCH_AOAC_REG2C           0x2C         //
#define FCH_AOAC_REG30           0x30         // Alternative HPET Timer
#define FCH_AOAC_REG34           0x34         // Alternative HPET Timer (HIGH 32BITS)
#define FCH_AOAC_REG38           0x38         // Alternative HPET Alarm
#define FCH_AOAC_REG3C           0x3C         // Alternative HPET Alarm (HIGH 32BITS)
/*
FCH_AOAC_REG4X-7x Control field
*/
#define AOAC_TARGET_DEVICE_STATE  (BIT0 + BIT1) // TargetedDeviceState -
                                                //   00 - D0 un-initialized
                                                //   01 - D0 initialized
                                                //   10 - D1/D2/D3hot
                                                //   11 - D3cold
                                                //
#define AOAC_DEVICE_STATE         BIT2          // DeviceState
                                                //   0 - Device power is removed
                                                //   1 - Device power is applied
#define AOAC_PWR_ON_DEV           BIT3          // PwrOnDev -
                                                //  If IsSwControl==0, software can write this bit to trigger a HW
                                                //     controlled power-down or reset sequence to the device.
                                                //   0 - Power down the device.
                                                //   1 - Power up the device.
                                                //
#define AOAC_SW_PWR_ON_RSTB       BIT4          // SwPwrOnRstB -
                                                //
                                                //   0 - PwrRstB is asserted to the device if IsSwControl==1.
                                                //   1 - 1=PwrRstB is de-asserted to the device if IsSwControl==1.
                                                //
#define AOAC_SW_REF_CLK_OK        BIT5          // SwRefClkOk -
                                                //
                                                //   0 - 0=RefClkOk is de-asserted to the device if IsSwControl==1.
                                                //   1 - RefClkOk is asserted to the device if IsSwControl==1.
                                                //
#define AOAC_SW_RST_B             BIT6          // SwRstB -
                                                //   0 - RstB is asserted to the device if IsSwControl==1.
                                                //   1 - RstB is deasserted to the device if IsSwControl==1.
                                                //
#define AOAC_IS_SW_CONTROL        BIT7          // IsSwControl
                                                //      To avoid glitch on the reset signals, software must set bit IsSwControl first before programming bit
                                                //      SwPwrOnRstB, SwRefClkOk and SwRstB.
                                                //   0 - Hardware controls control signals (PwrRstB, RefClkOk, RstB) to the device.
                                                //   1 - Software controls control signals (PwrRstB, RefClkOk, RstB) to the device.
                                                //
/*
FCH_AOAC_REG4X-7x State field
*/
#define A0AC_PWR_RST_STATE        BIT0
#define AOAC_RST_CLK_OK_STATE     BIT1
#define AOAC_RST_B_STATE          BIT2
#define AOAC_DEV_OFF_GATING_STATE BIT3
#define AOAC_D3COLD               BIT4
#define AOAC_CLK_OK_STATE         BIT5
#define AOAC_STAT0                BIT6
#define AOAC_STAT1                BIT7
#define FCH_AOAC_REG40           0x40         // ClkGen Control
#define FCH_AOAC_REG41           0x41         // ClkGen State
#define FCH_AOAC_REG42           0x42         // AB Control
#define FCH_AOAC_REG43           0x43         // AB State
#define FCH_AOAC_REG44           0x44         // ACPI S0 Control
#define FCH_AOAC_REG45           0x45         // ACPI S0 State
#define FCH_AOAC_REG46           0x46         // ACPI S5 Control
#define FCH_AOAC_REG47           0x47         // ACPI S5 State
#define FCH_AOAC_REG48           0x48         // LPC Control
#define FCH_AOAC_REG49           0x49         // LPC State
#define FCH_AOAC_REG4A           0x4A         // I_2_C 0 Control
#define FCH_AOAC_REG4B           0x4B         // I_2_C 0 State
#define FCH_AOAC_REG4C           0x4C         // I_2_C 1 Control
#define FCH_AOAC_REG4D           0x4D         // I_2_C 1 State
#define FCH_AOAC_REG4E           0x4E         // I_2_C 2 Control
#define FCH_AOAC_REG4F           0x4F         // I_2_C 2 State
#define FCH_AOAC_REG50           0x50         // I_2_C 3 Control
#define FCH_AOAC_REG51           0x51         // I_2_C 3 State

#define FCH_AOAC_REG56           0x56         // UART0 Control
#define FCH_AOAC_REG57           0x57         // UART0 State
#define FCH_AOAC_REG58           0x58         // UART1 Control
#define FCH_AOAC_REG59           0x59         // UART1 State

#define FCH_AOAC_REG62           0x62         // AMBA Control
#define FCH_AOAC_REG63           0x63         // AMBA State

#define FCH_AOAC_REG72           0x72         // SD1 Control
#define FCH_AOAC_REG73           0x73         // SD1 State
#define FCH_AOAC_REG76           0x76         // eSPI Control
#define FCH_AOAC_REG77           0x77         // eSPI State
#define FCH_AOAC_REG78           0x78         // eMMC Control
#define FCH_AOAC_REG79           0x79         // eMMC State
#define FCH_AOAC_REG7C           0x7C         // NB Control
#define FCH_AOAC_REG7D           0x7D         // NB State
#define FCH_AOAC_REG7E           0x7E         // APU Control
#define FCH_AOAC_REG7F           0x7F         // APU State
#define FCH_AOAC_REG80           0x80         //
#define FCH_AOAC_REG84           0x84         //
#define FCH_AOAC_REG88           0x88         //
#define FCH_AOAC_REG8C           0x8C         //
#define FCH_AOAC_REG90           0x90         //
#define FCH_AOAC_REG94           0x94         //
 #define S0I3CTRL_ARBITERDIS           BIT14
 #define S0I3CTRL_INTERRUPTDIS         BIT15
#define FCH_AOAC_REG98           0x98         //
#define FCH_AOAC_REG9C           0x9C         //
#define FCH_AOAC_REGA0           0xA0         //
#define FCH_AOAC_REGA4           0xA4         //
#define FCH_AOAC_REGA8           0xA8         //
#define FCH_AOAC_REGAC           0xAC         //
#define FCH_AOAC_REGB0           0xB0         //
#define FCH_AOAC_REGB4           0xB4         //
#define FCH_AOAC_REGB8           0xB8         //
#define FCH_AOAC_REGBC           0xBC         //
#define FCH_AOAC_REGC0           0xC0         //
#define FCH_AOAC_REGC4           0xC4         //
#define FCH_AOAC_REGC8           0xC8         //
#define FCH_AOAC_REGCC           0xCC         //
#define FCH_AOAC_REGD0           0xD0         //
#define FCH_AOAC_REGD4           0xD4         //
#define FCH_AOAC_REGD8           0xD8         //
#define FCH_AOAC_REGDC           0xDC         //
#define FCH_AOAC_REGE0           0xE0         //
#define FCH_AOAC_REGE4           0xE4         //
#define FCH_AOAC_REGE8           0xE8         //
#define FCH_AOAC_REGEC           0xEC         //
#define FCH_AOAC_REGF0           0xF0         //
#define FCH_AOAC_REGF4           0xF4         //
#define FCH_AOAC_REGF8           0xF8         //
#define FCH_AOAC_REGFC           0xFC         //

#define FCH_IOMAP_REG00          0x000   // Dma_C 0
#define FCH_IOMAP_REG02          0x002   // Dma_C 1
#define FCH_IOMAP_REG04          0x004   // Dma_C 2
#define FCH_IOMAP_REG06          0x006   // Dma_C 3
#define FCH_IOMAP_REG08          0x008   // Dma_Status
#define FCH_IOMAP_REG09          0x009   // Dma_WriteRest
#define FCH_IOMAP_REG0A          0x00A   // Dma_WriteMask
#define FCH_IOMAP_REG0B          0x00B   // Dma_WriteMode
#define FCH_IOMAP_REG0C          0x00C   // Dma_Clear
#define FCH_IOMAP_REG0D          0x00D   // Dma_MasterClr
#define FCH_IOMAP_REG0E          0x00E   // Dma_ClrMask
#define FCH_IOMAP_REG0F          0x00F   // Dma_AllMask
#define FCH_IOMAP_REG20          0x020   // IntrCntrlReg1
#define FCH_IOMAP_REG21          0x021   // IntrCntrlReg2
#define FCH_IOMAP_REG40          0x040   // TimerC0
#define FCH_IOMAP_REG41          0x041   // TimerC1
#define FCH_IOMAP_REG42          0x042   // TimerC2
#define FCH_IOMAP_REG43          0x043   // Tmr1CntrlWord
#define FCH_IOMAP_REG61          0x061   // Nmi_Status
#define FCH_IOMAP_REG70          0x070   // Nmi_Enable
#define FCH_IOMAP_REG71          0x071   // RtcDataPort
#define FCH_IOMAP_REG72          0x072   // AlternatRtcAddrPort
#define FCH_IOMAP_REG73          0x073   // AlternatRtcDataPort
#define FCH_IOMAP_REG80          0x080   // Dma_Page_Reserved0
#define FCH_IOMAP_REG81          0x081   // Dma_PageC2
#define FCH_IOMAP_REG82          0x082   // Dma_PageC3
#define FCH_IOMAP_REG83          0x083   // Dma_PageC1
#define FCH_IOMAP_REG84          0x084   // Dma_Page_Reserved1
#define FCH_IOMAP_REG85          0x085   // Dma_Page_Reserved2
#define FCH_IOMAP_REG86          0x086   // Dma_Page_Reserved3
#define FCH_IOMAP_REG87          0x087   // Dma_PageC0
#define FCH_IOMAP_REG88          0x088   // Dma_Page_Reserved4
#define FCH_IOMAP_REG89          0x089   // Dma_PageC6
#define FCH_IOMAP_REG8A          0x08A   // Dma_PageC7
#define FCH_IOMAP_REG8B          0x08B   // Dma_PageC5
#define FCH_IOMAP_REG8C          0x08C   // Dma_Page_Reserved5
#define FCH_IOMAP_REG8D          0x08D   // Dma_Page_Reserved6
#define FCH_IOMAP_REG8E          0x08E   // Dma_Page_Reserved7
#define FCH_IOMAP_REG8F          0x08F   // Dma_Refres
#define FCH_IOMAP_REG92          0x092   // FastInit
#define FCH_IOMAP_REGA0          0x0A0   // IntrCntrl2Reg1
#define FCH_IOMAP_REGA1          0x0A1   // IntrCntrl2Reg2
#define FCH_IOMAP_REGC0          0x0C0   // Dma2_C4Addr
#define FCH_IOMAP_REGC2          0x0C2   // Dma2_C4Cnt
#define FCH_IOMAP_REGC4          0x0C4   // Dma2_C5Addr
#define FCH_IOMAP_REGC6          0x0C6   // Dma2_C5Cnt
#define FCH_IOMAP_REGC8          0x0C8   // Dma2_C6Addr
#define FCH_IOMAP_REGCA          0x0CA   // Dma2_C6Cnt
#define FCH_IOMAP_REGCC          0x0CC   // Dma2_C7Addr
#define FCH_IOMAP_REGCE          0x0CE   // Dma2_C7Cnt
#define FCH_IOMAP_REGD0          0x0D0   // Dma_Status
#define FCH_IOMAP_REGD2          0x0D2   // Dma_WriteRest
#define FCH_IOMAP_REGD4          0x0D4   // Dma_WriteMask
#define FCH_IOMAP_REGD6          0x0D6   // Dma_WriteMode
#define FCH_IOMAP_REGD8          0x0D8   // Dma_Clear
#define FCH_IOMAP_REGDA          0x0DA   // Dma_Clear
#define FCH_IOMAP_REGDC          0x0DC   // Dma_ClrMask
#define FCH_IOMAP_REGDE          0x0DE   // Dma_ClrMask
#define FCH_IOMAP_REGED          0x0ED   // DUMMY IO PORT
#define FCH_IOMAP_REGF0          0x0F0   // NCP_Error
#define FCH_IOMAP_REG40B         0x040B  // DMA1_Extend
#define FCH_IOMAP_REG4D0         0x04D0  // IntrEdgeControl
#define FCH_IOMAP_REG4D6         0x04D6  // DMA2_Extend
#define FCH_IOMAP_REGC00         0x0C00  // Pci_Intr_Index
#define FCH_IOMAP_REGC01         0x0C01  // Pci_Intr_Data
#define FCH_IOMAP_REGC14         0x0C14  // Pci_Error
#define FCH_IOMAP_REGC50         0x0C50  // CMIndex
#define FCH_IOMAP_REGC51         0x0C51  // CMData
#define FCH_IOMAP_REGC52         0x0C52  // GpmPort
#define FCH_IOMAP_REGC6F         0x0C6F  // Isa_Misc
#define FCH_IOMAP_REGCD0         0x0CD0  // PMio2_Index
#define FCH_IOMAP_REGCD1         0x0CD1  // PMio2_Data
#define FCH_IOMAP_REGCD4         0x0CD4  // BIOSRAM_Index
#define FCH_IOMAP_REGCD5         0x0CD5  // BIOSRAM_Data
#define FCH_IOMAP_REGCD6         0x0CD6  // PM_Index
#define FCH_IOMAP_REGCD7         0x0CD7  // PM_Data
#define FCH_IOMAP_REGCF9         0x0CF9  // CF9Rst reg

#define FCH_IRQ_INTA             0x00    // INTA#
#define FCH_IRQ_INTB             0x01    // INTB#
#define FCH_IRQ_INTC             0x02    // INTC#
#define FCH_IRQ_INTD             0x03    // INTD#
#define FCH_IRQ_INTE             0x04    // INTE#
#define FCH_IRQ_INTF             0x05    // INTF#
#define FCH_IRQ_INTG             0x06    // INTG#
#define FCH_IRQ_INTH             0x07    // INTH#
#define FCH_IRQ_SCI              0x10    // SCI
#define FCH_IRQ_SMBUS0           0x11    // SMBUS0
#define FCH_IRQ_ASF              0x12    // ASF

#define FCH_IRQ_IOAPIC           0x80    // Select IRQ routing to IoApic mode
#define FCH_IRQ_PIC              0x00    // Select IRQ routing to PIC mode

//
// FCH SPI
//
#define FCH_SPI_MMIO_REG00       0x00        //SPI_
 #define FCH_SPI_OPCODE           0x000000FFl  //
 #define FCH_SPI_TX_COUNT         0x00000F00l  //
 #define FCH_SPI_RX_COUNT         0x0000F000l  //
 #define FCH_SPI_EXEC_OPCODE      0x00010000l  //
 #define FCH_SPI_FIFO_PTR_CRL     0x00100000l  //
 #define FCH_SPI_FIFO_PTR_INC     0x00200000l  //
 #define FCH_SPI_BUSY             0x80000000l  //

#define FCH_SPI_MMIO_REG0C       0x0C        //SPI_Cntrl1 Register
 #define FCH_SPI_PARAMETER        0x000000FFl  //
 #define FCH_SPI_FIFO_PTR         0x00000700l  //
 #define FCH_SPI_BYTE_PROGRAM     0xFF000000l  //
#define FCH_SPI_MMIO_REG1C       0x1C        //
#define FCH_SPI_MMIO_REG1D       0x1D        //
#define FCH_SPI_MMIO_REG1E       0x1E        //
#define FCH_SPI_MMIO_REG1F       0x1F        //
 #define FCH_SPI_MMIO_REG1F_X05_TX_BYTE_COUNT   0x05
 #define FCH_SPI_MMIO_REG1F_X06_RX_BYTE_COUNT   0x06

#define FCH_SPI_MMIO_REG20       0x20        //
#define FCH_SPI_MMIO_REG22       0x22        //
#define FCH_SPI_MMIO_REG2C       0x2C        //
#define FCH_SPI_MMIO_REG38       0x38        //
#define FCH_SPI_MMIO_REG32       0x32        //
#define FCH_SPI_MMIO_REG3C       0x3C        //

#define FCH_SPI_MMIO_REG45_CMDCODE           0x45        //
#define FCH_SPI_MMIO_REG47_CMDTRIGGER        0x47        //
#define FCH_SPI_MMIO_REG48_TXBYTECOUNT       0x48        //
#define FCH_SPI_MMIO_REG4B_RXBYTECOUNT       0x4B        //
#define FCH_SPI_MMIO_REG4C_SPISTATUS         0x4C        //
#define FCH_SPI_MMIO_REG4E       0x4E        //
#define FCH_SPI_MMIO_REG50_Addr32_Ctrl0       0x50        //
#define FCH_SPI_MMIO_REG80_FIFO              0x80        //

#define FCH_SPI_RETRY_TIMES      0x3         //

#define FCH_SPI_MODE_FAST        0x7        //
#define FCH_SPI_MODE_NORMAL      0x6        //
#define FCH_SPI_MODE_QUAL_144    0x5        //
#define FCH_SPI_MODE_QUAL_122    0x4        //
#define FCH_SPI_MODE_QUAL_114    0x3        //
#define FCH_SPI_MODE_QUAL_112    0x2        //
#define FCH_SPI_MODE_NORMAL_33M  0x0        //

#define FCH_SPI_DEVICE_MODE_DIS  0x7        //
#define FCH_SPI_DEVICE_MODE_144  0x4        //
#define FCH_SPI_DEVICE_MODE_114  0x3        //
#define FCH_SPI_DEVICE_MODE_122  0x2        //
#define FCH_SPI_DEVICE_MODE_112  0x1        //
#define FCH_SPI_DEVICE_MODE_FAST 0x0        //

#define FCH_SPI_SPEED_16M        0x4        //
#define FCH_SPI_SPEED_22M        0x3        //
#define FCH_SPI_SPEED_33M        0x2        //
#define FCH_SPI_SPEED_66M        0x1        //
#define FCH_SPI_SPEED_100M       0x5        //

//
//  FCH eMMC
//  Base 0xFEDD5800
//
#define FCH_EMMC_CFG_BASE               0xFEDD5800ul
#define FCH_EMMC_HC_BASE                0xFEDD5000ul
#define FCH_EMMC_CFG_REG10              (FCH_EMMC_CFG_BASE + 0x10)
#define FCH_EMMC_CFG_REG2C              (FCH_EMMC_CFG_BASE + 0x2C)
#define FCH_EMMC_CFG_REGA4              (FCH_EMMC_CFG_BASE + 0xA4)
#define FCH_EMMC_CFG_REGA8              (FCH_EMMC_CFG_BASE + 0xA8)
#define FCH_EMMC_CFG_REGAC              (FCH_EMMC_CFG_BASE + 0xAC)
#define FCH_EMMC_CFG_REGB0              (FCH_EMMC_CFG_BASE + 0xB0)
#define FCH_EMMC_CFG_REGB8              (FCH_EMMC_CFG_BASE + 0xB8)
#define FCH_EMMC_CFG_REGBC              (FCH_EMMC_CFG_BASE + 0xBC)
#define FCH_EMMC_CFG_REGD0              (FCH_EMMC_CFG_BASE + 0xD0)
#define FCH_EMMC_CFG_REGF0              (FCH_EMMC_CFG_BASE + 0xF0)
#define FCH_EMMC_CFG_REGF4              (FCH_EMMC_CFG_BASE + 0xF4)
#define FCH_EMMC_CFG_REGF8              (FCH_EMMC_CFG_BASE + 0xF8)
#define FCH_EMMC_CFG_REGFA              (FCH_EMMC_CFG_BASE + 0xFA)
#define FCH_EMMC_CFG_REGFC              (FCH_EMMC_CFG_BASE + 0xFC)
#define FCH_EMMC_CFG_REGFE              (FCH_EMMC_CFG_BASE + 0xFE)
#define FCH_EMMC_CFG_REG116             (FCH_EMMC_CFG_BASE + 0x116)

//
// FCH AL2AHB
//
#define FCH_AL2AHB_BASE                  0xFEDC0000ul
#define FCH_AL2AHBx10_CONTROL                           0xFEDC0010ul
 #define FCH_AL2AHBx10_CONTROL_CLOCK_GATE_EN            BIT1
#define FCH_AL2AHBx20_LEGACY_UART_IO_ENABLE             0xFEDC0020ul
#define FCH_AL2AHBx30_HCLK_CONTROL                      0xFEDC0030ul
 #define FCH_AL2AHBx30_HCLK_CONTROL_CLOCK_GATE_EN       BIT1

#define FCH_REG00                     0x00
#define FCH_REG01                     0x01
#define FCH_REG02                     0x02
#define FCH_REG03                     0x03
#define FCH_REG04                     0x04
#define FCH_REG05                     0x05
#define FCH_REG06                     0x06
#define FCH_REG07                     0x07
#define FCH_REG08                     0x08
#define FCH_REG09                     0x09
#define FCH_REG0A                     0x0A
#define FCH_REG0B                     0x0B
#define FCH_REG0C                     0x0C
#define FCH_REG0D                     0x0D
#define FCH_REG0E                     0x0E
#define FCH_REG0F                     0x0F
#define FCH_REG10                     0x10
#define FCH_REG11                     0x11
#define FCH_REG12                     0x12
#define FCH_REG13                     0x13
#define FCH_REG14                     0x14
#define FCH_REG15                     0x15
#define FCH_REG16                     0x16
#define FCH_REG17                     0x17
#define FCH_REG18                     0x18
#define FCH_REG19                     0x19
#define FCH_REG1A                     0x1A
#define FCH_REG1B                     0x1B
#define FCH_REG1C                     0x1C
#define FCH_REG1D                     0x1D
#define FCH_REG1E                     0x1E
#define FCH_REG1F                     0x1F
#define FCH_REG20                     0x20
#define FCH_REG21                     0x21
#define FCH_REG22                     0x22
#define FCH_REG23                     0x23
#define FCH_REG24                     0x24
#define FCH_REG25                     0x25
#define FCH_REG26                     0x26
#define FCH_REG27                     0x27
#define FCH_REG28                     0x28
#define FCH_REG29                     0x29
#define FCH_REG2A                     0x2A
#define FCH_REG2B                     0x2B
#define FCH_REG2C                     0x2C
#define FCH_REG2D                     0x2D
#define FCH_REG2E                     0x2E
#define FCH_REG2F                     0x2F
#define FCH_REG30                     0x30
#define FCH_REG31                     0x31
#define FCH_REG32                     0x32
#define FCH_REG33                     0x33
#define FCH_REG34                     0x34
#define FCH_REG35                     0x35
#define FCH_REG36                     0x36
#define FCH_REG37                     0x37
#define FCH_REG38                     0x38
#define FCH_REG39                     0x39
#define FCH_REG3A                     0x3A
#define FCH_REG3B                     0x3B
#define FCH_REG3C                     0x3C
#define FCH_REG3D                     0x3D
#define FCH_REG3E                     0x3E
#define FCH_REG3F                     0x3F
#define FCH_REG40                     0x40
#define FCH_REG41                     0x41
#define FCH_REG42                     0x42
#define FCH_REG43                     0x43
#define FCH_REG44                     0x44
#define FCH_REG45                     0x45
#define FCH_REG46                     0x46
#define FCH_REG47                     0x47
#define FCH_REG48                     0x48
#define FCH_REG49                     0x49
#define FCH_REG4A                     0x4A
#define FCH_REG4B                     0x4B
#define FCH_REG4C                     0x4C
#define FCH_REG4D                     0x4D
#define FCH_REG4E                     0x4E
#define FCH_REG4F                     0x4F
#define FCH_REG50                     0x50
#define FCH_REG51                     0x51
#define FCH_REG52                     0x52
#define FCH_REG53                     0x53
#define FCH_REG54                     0x54
#define FCH_REG55                     0x55
#define FCH_REG56                     0x56
#define FCH_REG57                     0x57
#define FCH_REG58                     0x58
#define FCH_REG59                     0x59
#define FCH_REG5A                     0x5A
#define FCH_REG5B                     0x5B
#define FCH_REG5C                     0x5C
#define FCH_REG5D                     0x5D
#define FCH_REG5E                     0x5E
#define FCH_REG5F                     0x5F
#define FCH_REG60                     0x60
#define FCH_REG61                     0x61
#define FCH_REG62                     0x62
#define FCH_REG63                     0x63
#define FCH_REG64                     0x64
#define FCH_REG65                     0x65
#define FCH_REG66                     0x66
#define FCH_REG67                     0x67
#define FCH_REG68                     0x68
#define FCH_REG69                     0x69
#define FCH_REG6A                     0x6A
#define FCH_REG6B                     0x6B
#define FCH_REG6C                     0x6C
#define FCH_REG6D                     0x6D
#define FCH_REG6E                     0x6E
#define FCH_REG6F                     0x6F
#define FCH_REG70                     0x70
#define FCH_REG71                     0x71
#define FCH_REG72                     0x72
#define FCH_REG73                     0x73
#define FCH_REG74                     0x74
#define FCH_REG75                     0x75
#define FCH_REG76                     0x76
#define FCH_REG77                     0x77
#define FCH_REG78                     0x78
#define FCH_REG79                     0x79
#define FCH_REG7A                     0x7A
#define FCH_REG7B                     0x7B
#define FCH_REG7C                     0x7C
#define FCH_REG7D                     0x7D
#define FCH_REG7E                     0x7E
#define FCH_REG7F                     0x7F
#define FCH_REG80                     0x80
#define FCH_REG81                     0x81
#define FCH_REG82                     0x82
#define FCH_REG83                     0x83
#define FCH_REG84                     0x84
#define FCH_REG85                     0x85
#define FCH_REG86                     0x86
#define FCH_REG87                     0x87
#define FCH_REG88                     0x88
#define FCH_REG89                     0x89
#define FCH_REG8A                     0x8A
#define FCH_REG8B                     0x8B
#define FCH_REG8C                     0x8C
#define FCH_REG8D                     0x8D
#define FCH_REG8E                     0x8E
#define FCH_REG8F                     0x8F
#define FCH_REG90                     0x90
#define FCH_REG91                     0x91
#define FCH_REG92                     0x92
#define FCH_REG93                     0x93
#define FCH_REG94                     0x94
#define FCH_REG95                     0x95
#define FCH_REG96                     0x96
#define FCH_REG97                     0x97
#define FCH_REG98                     0x98
#define FCH_REG99                     0x99
#define FCH_REG9A                     0x9A
#define FCH_REG9B                     0x9B
#define FCH_REG9C                     0x9C
#define FCH_REG9D                     0x9D
#define FCH_REG9E                     0x9E
#define FCH_REG9F                     0x9F
#define FCH_REGA0                     0xA0
#define FCH_REGA1                     0xA1
#define FCH_REGA2                     0xA2
#define FCH_REGA3                     0xA3
#define FCH_REGA4                     0xA4
#define FCH_REGA5                     0xA5
#define FCH_REGA6                     0xA6
#define FCH_REGA7                     0xA7
#define FCH_REGA8                     0xA8
#define FCH_REGA9                     0xA9
#define FCH_REGAA                     0xAA
#define FCH_REGAB                     0xAB
#define FCH_REGAC                     0xAC
#define FCH_REGAD                     0xAD
#define FCH_REGAE                     0xAE
#define FCH_REGAF                     0xAF
#define FCH_REGB0                     0xB0
#define FCH_REGB1                     0xB1
#define FCH_REGB2                     0xB2
#define FCH_REGB3                     0xB3
#define FCH_REGB4                     0xB4
#define FCH_REGB5                     0xB5
#define FCH_REGB6                     0xB6
#define FCH_REGB7                     0xB7
#define FCH_REGB8                     0xB8
#define FCH_REGB9                     0xB9
#define FCH_REGBA                     0xBA
#define FCH_REGBB                     0xBB
#define FCH_REGBC                     0xBC
#define FCH_REGBD                     0xBD
#define FCH_REGBE                     0xBE
#define FCH_REGBF                     0xBF
#define FCH_REGC0                     0xC0
#define FCH_REGC1                     0xC1
#define FCH_REGC2                     0xC2
#define FCH_REGC3                     0xC3
#define FCH_REGC4                     0xC4
#define FCH_REGC5                     0xC5
#define FCH_REGC6                     0xC6
#define FCH_REGC7                     0xC7
#define FCH_REGC8                     0xC8
#define FCH_REGC9                     0xC9
#define FCH_REGCA                     0xCA
#define FCH_REGCB                     0xCB
#define FCH_REGCC                     0xCC
#define FCH_REGCD                     0xCD
#define FCH_REGCE                     0xCE
#define FCH_REGCF                     0xCF
#define FCH_REGD0                     0xD0
#define FCH_REGD1                     0xD1
#define FCH_REGD2                     0xD2
#define FCH_REGD3                     0xD3
#define FCH_REGD4                     0xD4
#define FCH_REGD5                     0xD5
#define FCH_REGD6                     0xD6
#define FCH_REGD7                     0xD7
#define FCH_REGD8                     0xD8
#define FCH_REGD9                     0xD9
#define FCH_REGDA                     0xDA
#define FCH_REGDB                     0xDB
#define FCH_REGDC                     0xDC
#define FCH_REGDD                     0xDD
#define FCH_REGDE                     0xDE
#define FCH_REGDF                     0xDF
#define FCH_REGE0                     0xE0
#define FCH_REGE1                     0xE1
#define FCH_REGE2                     0xE2
#define FCH_REGE3                     0xE3
#define FCH_REGE4                     0xE4
#define FCH_REGE5                     0xE5
#define FCH_REGE6                     0xE6
#define FCH_REGE7                     0xE7
#define FCH_REGE8                     0xE8
#define FCH_REGE9                     0xE9
#define FCH_REGEA                     0xEA
#define FCH_REGEB                     0xEB
#define FCH_REGEC                     0xEC
#define FCH_REGED                     0xED
#define FCH_REGEE                     0xEE
#define FCH_REGEF                     0xEF
#define FCH_REGF0                     0xF0
#define FCH_REGF1                     0xF1
#define FCH_REGF2                     0xF2
#define FCH_REGF3                     0xF3
#define FCH_REGF4                     0xF4
#define FCH_REGF5                     0xF5
#define FCH_REGF6                     0xF6
#define FCH_REGF7                     0xF7
#define FCH_REGF8                     0xF8
#define FCH_REGF9                     0xF9
#define FCH_REGFA                     0xFA
#define FCH_REGFB                     0xFB
#define FCH_REGFC                     0xFC
#define FCH_REGFD                     0xFD
#define FCH_REGFE                     0xFE
#define FCH_REGFF                     0xFF

#define RTC_WORKAROUND_SECOND           0x00
#define RTC_VALID_SECOND_VALUE          0x59
#define RTC_SECOND_RESET_VALUE          0x30
#define RTC_SECOND_LOWER_NIBBLE         0x0F
#define RTC_VALID_SECOND_VALUE_LN       0x09

//PGFSM definition
#define PGFSM_CMD_POWER_DOWN                 (0x00 << 1)
#define PGFSM_CMD_POWER_UP                   (0x01 << 1)
#define PGFSM_CMD_POWER_WRITE                (0x02 << 1)
#define PGFSM_CMD_POWER_READ                 (0x03 << 1)
#define PGFSM_SOFTWARE_CONTROL               BIT0
#define PGFSM_STATUS_PWR_STS                 (BIT0 + BIT1)
#define PGFSM_STATUS_PWR_ON                  0
#define PGFSM_STATUS_PWR_OFF                 BIT1
#define PGFSM_SELECT_0                       BIT8

//Soc ID
#define AMD_D0F0   ((0 << 3) + 0)
#define AMD_D18F0  ((0x18 << 3) + 0)

#define SOC_ZPID                             0x14501022ul
#define DF_ZPID                              0x14601022ul
#define SOC_SSPID                            0x14901022ul

//CPU Package Type
#define PKG_SP4                              0x1
#define PKG_AM4                              0x2
#define PKG_SP4_R2                           0x3
#define PKG_SP3                              0x4
#define PKG_SP3_R2                           0x7

#define ACPIMMIO32(x) (*(volatile UINT32*)(UINTN)(x))
#define ACPIMMIO16(x) (*(volatile UINT16*)(UINTN)(x))
#define ACPIMMIO8(x)  (*(volatile UINT8*)(UINTN)(x))
#ifndef FCH_DEADLOOP
  #define FCH_DEADLOOP()    { volatile UINTN __i; __i = 1; while (__i); }
#endif

