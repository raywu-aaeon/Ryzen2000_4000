/*****************************************************************************
 *
 * Copyright 2016 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 ******************************************************************************
 */

#include <AmdCpmPei.h>
#include <AmdCpmBaseIo.h>
#include <AmdCpmBase.h>
#include "AmdCpmOemInitPeim.h"
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
#include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>
#include <Library/IoLib.h>
#include <Fch.h>
#include <FchXgbe.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <NbioGfx.h>

#define REV_A_BOARD 1
#define AGPIO116 116
#define EGPIO120 120
#define EGPIO121 121
#define EGPIO131 131
#define SMUFUSEx000005A0_ADDRESS 0x0005D5A0
#define SMUFUSEx000005A4_ADDRESS 0x0005D5A4
#define R2K_OPN_R2312 "R2312 "
//
// OEM CPM Table Definition
//

//
// Platform Id Table: Get Board Id from GPIO pins
//
AMD_CPM_PLATFORM_ID_TABLE           gCpmPlatformIdTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GET_PLATFORM_ID, sizeof (gCpmPlatformIdTable) / sizeof (UINT8), 0, 0, 0, 1},
  {
    // [0x0000: 0x00FF]: FCH GPIO Pin
    // [0x0100: 0x01FF]: KBC GPIO Pin on Reference Board
    // [0x0200: 0x02FF]: ECRAM GPIO Pin on Reference Board
    //0x0200, // BOARD_ID0
    //0x0201, // BOARD_ID1
    //0x0202, // BOARD_ID2
    //0x0203, // BOARD_ID3
    //0x0204, // BOARD_ID4
    0xFF
  }
};

//
// Convert Table from Board Id to Platform Id
//
AMD_CPM_PLATFORM_ID_CONVERT_TABLE   gCpmPlatformIdConvertTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table contect
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GET_PLATFORM_ID_CONVERT, sizeof (gCpmPlatformIdConvertTable) / sizeof (UINT8), 0, 0, 0, 1},
  {
//  {UINT8  CpuRevisionId;  // CPU Revision ID
//   UINT16 OriginalIdMask; // Platform Id mask from platform Id table
//   UINT16 OriginalId;     // Platform Id from platform Id table
//   UINT16 ConvertedId;    // Platform Id which is used to check whether // CPM table supports current platform},
                                                      //  ID4 ID3 ID2
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0000, 0x0000}, //    0   0   0   Mandolin     Regulator Board RV  =>platform mask = 0x00000001
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0004, 0x0001}, //    0   0   1   Tambourine             Board RV  =>platform mask = 0x00000002
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0008, 0x0002}, //    0   1   0   Mandolin DAP Regulator Board RV  =>platform mask = 0x00000004
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0018, 0x0003}, //    1   1   0   Mandolin DAP 2PHASE    Board RV  =>platform mask = 0x00000008
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0010, 0x0004}, //    1   0   0   Mandolin     2PHASE    Board RV  =>platform mask = 0x00000010
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0000, 0x0008}, //    0   0   0   Mandolin     Regulator Board RV2 =>platform mask = 0x00000100
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0004, 0x0009}, //    0   0   1   Tambourine             Board RV2 =>platform mask = 0x00000200
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0008, 0x000A}, //    0   1   0   Mandolin DAP Regulator Board RV2 =>platform mask = 0x00000400
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0018, 0x000B}, //    1   1   0   Mandolin DAP 2PHASE    Board RV2 =>platform mask = 0x00000800
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0010, 0x000C}, //    1   0   0   Mandolin     2PHASE    Board RV2 =>platform mask = 0x00001000
    0xFFFF,
  }
};

//
// Pre-Init Table
//
AMD_CPM_PRE_INIT_TABLE              gCpmPreInitTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_PRE_INIT, sizeof (gCpmPreInitTable) / sizeof (UINT8), 0, 0, 0, 0x01},
  {
//  {UINT8  Type;     // Register type. 0: FCH MMIO. 1: PCI
//   UINT8  Select;   // Register sub-type
//   UINT8  Offset;   // Register offset
//   UINT8  AndMask;  // AND mask
//   UINT8  OrMask;   // OR mask
//   UINT8  Stage;    // Stage number},
    {0x00, 0x03, 0xEA, 0xFE, 0x01, CPM_PRE_INIT_STAGE_0, NORMAL_PURPOSE}, // PM_RegEA[0]: PCIDisable = 1
    0xFF,
  }
};

//
// GPIO Init Table for Bilby and R1000 silicon support
//
AMD_CPM_GPIO_INIT_TABLE             gCpmGpioInitTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_INIT, sizeof (gCpmGpioInitTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  {
//         (socket,die,gpio,function,        output,           pullup)
    GPIO_DEFINITION (0,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // PWR_BTN#
    GPIO_DEFINITION (1,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SYS_RST#
    GPIO_DEFINITION (2,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // WAKE#
    GPIO_DEFINITION (3,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // Pull Up +3.3VSB
    GPIO_DEFINITION (4,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // Pull-Down GND
    GPIO_DEFINITION (5,   GPIO_FUNCTION_1,  GPIO_OUTPUT_LOW,  GPIO_PD_EN,     GPIO_STICKY_DIS),   // SSD_DEVSLP
    GPIO_DEFINITION (6,   GPIO_FUNCTION_0,  GPIO_OUTPUT_LOW,  GPIO_PD_EN,     GPIO_STICKY_DIS),   // AGPIO6 (for PCIe Slot Resets)
    GPIO_DEFINITION (7,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // AGPIO7/DP2_HDMI2_SEL (Unused)
    GPIO_DEFINITION (8,   GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // AGPIO8/DP3_HDMI3_SEL (Unused)
    GPIO_DEFINITION (9,   GPIO_FUNCTION_0,  GPIO_INPUT, 		  GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // PHY1_MDIO_CLK (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (10,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // MDIO_SCLK0 (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (11,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // BLINK_AGPIO11/Pull-Up +3.3VSB
    GPIO_DEFINITION (12,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // VDDP_SET (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (13,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // USB_OC5# (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (14,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // USB_OC4# (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (16,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // USB_OC0# (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (17,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // USB_OC1#
    GPIO_DEFINITION (18,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // USB_OC2# (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (19,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SCLK1 (Currently set to GPIO Input)
    GPIO_DEFINITION (20,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SDATA1 (Currently set to GPIO Input)
    GPIO_DEFINITION (21,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // LPCPD#_A (Unused)/Floating
    GPIO_DEFINITION (22,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // LPC_PME# (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (23,  GPIO_FUNCTION_3,  GPIO_INPUT, 		  GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // PHY1_MDIO_DATA (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (24,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // USB_OC3# (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (26,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // PCIE_RST#_R
    GPIO_DEFINITION (27,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // PCIE_RST1#_R (Unused)/Floating
    GPIO_DEFINITION (29,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SPI_TPM_CS#
    GPIO_DEFINITION (30,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SPI_CS2# (Unused)/Pull-Up +1.8V_ALW
    GPIO_DEFINITION (31,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // DISPLAY_SELECT1 (Unused)/Pull-Up +3.3V_RUN
// Leave default -     GPIO_DEFINITION (32,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LPC_RST#
    GPIO_DEFINITION (39,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // AGPIO39 (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (40,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // MDIO_SDAT0 (Unused)/Pull-Up +3.3VSB
    GPIO_DEFINITION (41,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // EGPIO41 (Unused)/TP38
    GPIO_DEFINITION (42,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // GPP_10G_SELECT (Unused)/Pull-Up +3.3V_RUN
    GPIO_DEFINITION (67,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // EGPIO67/Pull-Down GND
    GPIO_DEFINITION (68,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // N/A Floating
    GPIO_DEFINITION (69,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // PCI_X4_PRSNT# (Unused)/Pull-Up +3.3V_RUN
    GPIO_DEFINITION (70,  GPIO_FUNCTION_0,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // N/A Floating
// Leave default -     GPIO_DEFINITION (74,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LPC_CLK0
// Leave default -     GPIO_DEFINITION (75,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LPC_CLK1
    GPIO_DEFINITION (76,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_EN,     GPIO_STICKY_DIS),   // AGPIO76 (Unused)/TP5
    GPIO_DEFINITION (84,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // FANTACH0 (Unused)/Pull-Up +3.3V_RUN
    GPIO_DEFINITION (85,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // FANOUT0 (Unused)/Pull-Up +3.3V_RUN
    GPIO_DEFINITION (86,  GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // AGPIO86/Pull-Up +3.3V_RUN
// Leave default -     GPIO_DEFINITION (87,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // SERIRQ
    GPIO_DEFINITION (88,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // LPC_CLKRUN# (Unused)/Floating
    GPIO_DEFINITION (89,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // APU_COMBO_GPP_SW (Unused)/Pull-Up +3.3V_RUN
    GPIO_DEFINITION (90,  GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // AGPIO90/Pull-Up +3.3V_RUN
    GPIO_DEFINITION (91,  GPIO_FUNCTION_0,  GPIO_OUTPUT_HIGH, GPIO_PD_EN,     GPIO_STICKY_DIS),   // PC_BEEP
// Leave default -     GPIO_DEFINITION (92,  GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LAN1_CLKREQ#
// Leave default -     GPIO_DEFINITION (104, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LAD0_A
// Leave default -     GPIO_DEFINITION (105, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LAD1_A
// Leave default -     GPIO_DEFINITION (106, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LAD2_A
// Leave default -     GPIO_DEFINITION (107, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // LAD3_A
    GPIO_DEFINITION (108, GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // EC_ESPI_ALERT# (Unused)/Pull-Up +1.8V_RUN
    GPIO_DEFINITION (113, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SCLK0
    GPIO_DEFINITION (114, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SDATA0
    GPIO_DEFINITION (115, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // LAN2_CLKREQ#
    GPIO_DEFINITION (116, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // M2_BKEY_CLKREQ#
    GPIO_DEFINITION (120, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // MINI1_CLKREQ#
    GPIO_DEFINITION (121, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // CLK_REQ6# (Unused)/Pull-Down GND
// Leave default -     GPIO_DEFINITION (129, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_EN,     GPIO_STICKY_DIS),   // KBRST#
// Leave default -     GPIO_DEFINITION (130, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // SATA_ACT#
// Leave default -     GPIO_DEFINITION (131, GPIO_FUNCTION_0,  GPIO_NA,          GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // M2_MKEY_CLKREQ#
    GPIO_DEFINITION (132, GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // CLK_REQ4# (Unused)
    GPIO_DEFINITION (135, GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // APU_UART0_CTS# (Unused)/Floating
    GPIO_DEFINITION (136, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // APU_UART0_RXD (Unused)/Pull-Up +1.8V_RUN
    GPIO_DEFINITION (137, GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_EN,     GPIO_STICKY_DIS),   // APU_UART0_RTS# (Unused)/Floating
    GPIO_DEFINITION (138, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_EN,     GPIO_STICKY_DIS),   // APU_UART0_TXD (Unused)/Floating
    GPIO_DEFINITION (139, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_PD_DIS, GPIO_STICKY_DIS),   // APU_UART0_INTR (Unused)/Pull-Up +1.8V_RUN
    GPIO_DEFINITION (140, GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // APU_UART1_CTS# (Unused)/TP13
    GPIO_DEFINITION (141, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // APU_UART1_RXD (Unused)/TP12
    GPIO_DEFINITION (142, GPIO_FUNCTION_2,  GPIO_INPUT,       GPIO_PU_EN,     GPIO_STICKY_DIS),   // APU_UART1_RTS# (Unused)/TP8
    GPIO_DEFINITION (143, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PU_EN,     GPIO_STICKY_DIS),   // APU_UART1_TXD (Unused)/TP10
    GPIO_DEFINITION (144, GPIO_FUNCTION_1,  GPIO_INPUT,       GPIO_PD_EN,     GPIO_STICKY_DIS),   // APU_UART1_INTR (Unused)/TP7
    0xFF,
  }
};

//
// GEVENT Init Table
//
AMD_CPM_GEVENT_INIT_TABLE           gCpmGeventInitTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GEVENT_INIT, sizeof (gCpmGeventInitTable) / sizeof (UINT8), 0, 0, 0, 0x00000001},
  {//                  GEvent EventEnable   SciTrigE      SciLevl         SmiSciEn        SciS0En         SciMap      SmiTrig       SmiControl
//  GEVENT_DEFINITION (0x02,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_02,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT02: DP0_HDMI0_SEL (Unused)
//  GEVENT_DEFINITION (0x03,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_03,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT03: LPC_PME# (Unused)
//  GEVENT_DEFINITION (0x04,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_04,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT04: DP1_HDMI1_SEL (Unused)
//  GEVENT_DEFINITION (0x06,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_06,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT06: PC_BEEP
//  GEVENT_DEFINITION (0x07,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_LEVEL, SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_07,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT07: DEVSLP0
    GEVENT_DEFINITION (0x08,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_08,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT08: PCIE_WAKE_UP#/WAKE_ON_WAN#
//  GEVENT_DEFINITION (0x0B,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_11,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT11: DP3_HDMI3_SEL (Unused)
//  GEVENT_DEFINITION (0x0E,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_14,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT14: USB_OC2# (Unused)
//  GEVENT_DEFINITION (0x10,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_16,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT16: PHY1_MDIO_DATA (Unused)
//  GEVENT_DEFINITION (0x15,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_21,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT21: PWR_BTN#
//  GEVENT_DEFINITION (0x16,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_22,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT22: PHY1_MDIO_CLK (Unused)
//  GEVENT_DEFINITION (ZPODD_DUMMY_EVENT, EVENT_ENABLE, SCITRIG_HI, SCILEVEL_EDGE, SMISCI_DISABLE, SCIS0_DISABLE, ZPODD_DUMMY_EVENT, SMITRIG_HI, SMICONTROL_DISABLE), // GEVENT31: ZPODD Dummy Gevent31
    0xFF,
  }
};


//
// CPM GPIO Module
//
AMD_CPM_GPIO_DEVICE_CONFIG_TABLE    gCpmGpioDeviceConfigTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_DEVICE_CONFIG, sizeof (gCpmGpioDeviceConfigTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  {//                       DeviceId          Enable            Assert  Deassert  Hotplugs
      GPIO_DEVICE_DEFINITION (DEVICE_ID_MXM,    CPM_DEVICE_AUTO,    0,          1,          0   ),
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_ODD,    CPM_DEVICE_AUTO,    0,          0,          0   ),
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_SD,     CPM_DEVICE_ON,      0,          0,          0   ),
      GPIO_DEVICE_DEFINITION (DEVICE_ID_DT,     CPM_DEVICE_ON,      1,          0,          0   ),
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_WLAN,   CPM_DEVICE_ON,      0,          0,          0   ),    //SATA 0;/    GPIO_DEVICE_DEFINITION (DEVICE_ID_LAN,    CPM_DEVICE_ON,      1,          1,          0   ),
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_WWAN,   CPM_DEVICE_ON,      0,          0,          0   ),    //WWAN 0;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_LAN,    CPM_DEVICE_ON,      0,          0,          0   ),
      GPIO_DEVICE_DEFINITION (DEVICE_ID_HDD0,   CPM_DEVICE_AUTO,    0,          0,          0   ),    //SATA 0;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_ODD,    CPM_DEVICE_ON,      0,          0,          0   ),    //SATA 1;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_SSD,    CPM_DEVICE_ON,      0,          0,          0   ),    //SSD   ;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_RCAM,   CPM_DEVICE_ON,      0,          0,          0   ),    //SATA 0;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_FCAM,   CPM_DEVICE_ON,      0,          0,          0   ),    //SATA 0;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_LOM,    CPM_DEVICE_ON,      0,          0,          0   ),    //SATA 0;
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_USB_TYPE_C0, CPM_DEVICE_OFF,     0,          0,          0   ), // HDMI over USB Type C Port 0 control
//    GPIO_DEVICE_DEFINITION (DEVICE_ID_USB_TYPE_C1, CPM_DEVICE_OFF,     0,          0,          0   ), // HDMI over USB Type C Port 1 control
    0xFF,
  }
};

//
// CPM Device Detection Table for Gardenia-BP RevA
//
AMD_CPM_GPIO_DEVICE_DETECTION_TABLE gCpmGpioDeviceDetectionTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_DEVICE_DETECTION, sizeof (gCpmGpioDeviceDetectionTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  {
//  {UINT8  DeviceId; // Device Id
//   UINT8  Type;     // Detection type. 0: One GPIO pin. 1: Two GPIO pins. 2: Special Pin
//   UINT16 PinNum1;  // Pin number of GPIO 1
//   UINT8  Value1;   // Value of GPIO 1
//   UINT16 PinNum2;  // Pin number of GPIO 2
//   UINT8  Value2;   // Value of GPIO 2
//   UINT16 PinNum3;  // Pin number of GPIO 3
//   UINT8  Value3;   // Value of GPIO 3},
//  { DEVICE_ID_ODD,   0,    ZPODD_DETECT_PIN,  ZPODD_DETECT_VALUE,     0,  0 },          // ODD_PLUGIN#: GEVENT14#
    { DEVICE_ID_MXM,   0,    MXM_PRESENT,       MXM_DETECT_VALUE,       0,  0 },
    { DEVICE_ID_SSD,   0,    0x5C,              1               ,       0,  0 },
//  { DEVICE_ID_WWAN,  0,    0x233,             1               ,       0,  0 },
    { DEVICE_ID_DT,    0,    DTDEVICE_DETECT,   DTDEVICE_DETECT_VALUE,  0,  0 },
    0xFF,
  }
};

//
// CPM Device Reset Table
//
AMD_CPM_GPIO_DEVICE_RESET_TABLE gCpmGpioDeviceResetTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_DEVICE_RESET, sizeof (gCpmGpioDeviceResetTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  {
//  {UINT8  DeviceId;       // Device Id
//   UINT8  Mode;           // Reset mode     // 0: Reset Assert. // 1: Reset De-assert             // 2: Delay between Assert and Deassert
//   UINT8  Type;           // Register type  // 0: GPIO.         // 1: Special pin.if Mode = 0 or 1
//   UINT32 ((UINT16)Pin + ((UINT8)Value << 16));                 // GPIO pin value
//   UINT8  InitFlag;       // Init flag in post},
    { DEVICE_ID_MXM,  CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_GPIO_PIN (MXM_RESET, 0),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO140
    { DEVICE_ID_DT,   CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_GPIO_PIN (DT_RESET, 0),   GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[6] (BIT46)
    //{ DEVICE_ID_WLAN, CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WLAN_RESET, 0), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[7] (BIT47)
    //{ DEVICE_ID_LAN,  CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (LAN_RESET, 0),  GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[4] (BIT44)
    //{ DEVICE_ID_WWAN, CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WWAN_RESET, 0), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[5] (BIT45)
    //{ DEVICE_ID_SSD,  CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_GPIO_PIN (SSD_RESET, 0),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO40
    { DEVICE_ID_MXM,  CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_GPIO_PIN (MXM_RESET, 1),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO140
    { DEVICE_ID_DT,   CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_GPIO_PIN (DT_RESET, 1),   GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[6] (BIT46)
    //{ DEVICE_ID_WLAN, CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WLAN_RESET, 1), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[7] (BIT47)
    //{ DEVICE_ID_LAN,  CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (LAN_RESET, 1),  GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[4] (BIT44)
    //{ DEVICE_ID_WWAN, CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WWAN_RESET, 1), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[5] (BIT45)
    //{ DEVICE_ID_SSD,  CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_GPIO_PIN (SSD_RESET, 1),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO40
    0xFF,
  }
};

//
// CPM GPIO Device Init Table (Power On/Off) - RevA
//
AMD_CPM_GPIO_DEVICE_POWER_TABLE gCpmGpioDevicePowerTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_DEVICE_POWER, sizeof (gCpmGpioDevicePowerTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  {
//  {UINT8  DeviceId;       // Device Id
//   UINT8  Mode;           // Device Power Mode. 1: Power On. 0: Power Off
//   UINT8  Type;           // Device Power Item. 0: Set GPIO. 1: Wait GPIO. 2: Add Delay
//   UINT32 ((UINT16)Pin + ((UINT8)Value << 16));                 // GPIO pin value or delay timer
//   UINT8  InitFlag;       // Init flag in post},
  //{DEVICE_ID_MXM,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ON, 0),          GPIO_DEVICE_INIT_STAGE_DUMMY},
  //{DEVICE_ID_MXM,  CPM_POWER_OFF, CPM_POWER_DELAY, 1000,                                    GPIO_DEVICE_INIT_STAGE_DUMMY},
  //{DEVICE_ID_MXM,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 0),      GPIO_DEVICE_INIT_STAGE_DUMMY},
  //{DEVICE_ID_LAN,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (LAN_POWER_CONTROL_REVA, 0),GPIO_DEVICE_INIT_DISABLE},
  //{DEVICE_ID_LAN,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LOM_PWR_EN, 0),      GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_SSD,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (23, 0),                    GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_RCAM, CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (71, 0),                    GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_FCAM, CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (5, 0),                     GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_HDD0, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (0x33, 0),            GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_ODD,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (ZPODD_POWER_CONTROL, 0),   GPIO_DEVICE_INIT_DISABLE},
  //{DEVICE_ID_DT,   CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (DT_POWER_EN, 0),     GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WLAN, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WLAN_POWER_EN, 0),   GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_LAN,  CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LAN_POWER_EN, 0),      GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_CARD_POWER_OFF_L, 0), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_RADIO_PERMITTED, 0),  GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_OFF, CPM_POWER_DELAY, 100,                                     GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_POWER_EN, 0),        GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WIFI, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WIFI_POWER_EN, 0),      GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C0, CPM_POWER_OFF, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC0_AUX, 0), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C0, CPM_POWER_OFF, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC0_MUX, 1), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C1, CPM_POWER_OFF, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC1_AUX, 0), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C1, CPM_POWER_OFF, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC1_MUX, 1), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_MXM,  CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 1),      GPIO_DEVICE_INIT_STAGE_DUMMY},
  //{DEVICE_ID_MXM,  CPM_POWER_ON,  CPM_POWER_DELAY, 1000,                                    GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_MXM,  CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ON, 1),          GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_MXM,  CPM_POWER_ON,  CPM_POWER_DELAY, 100000,                                  GPIO_DEVICE_INIT_STAGE_DUMMY},
  //{DEVICE_ID_MXM,  CPM_POWER_ON,  CPM_POWER_WAIT,  CPM_GPIO_PIN (MXM_POWER_GOOD, 1),        GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_MXM,  CPM_POWER_ON,  CPM_POWER_DELAY, 200,                                     GPIO_DEVICE_INIT_STAGE_DUMMY},
  //{DEVICE_ID_SSD,  CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (23, 1),                    GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_RCAM, CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (71, 1),                    GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_FCAM, CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (5, 1),                     GPIO_DEVICE_INIT_STAGE_2},
  //{DEVICE_ID_HDD0, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (0x33, 1),            GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_ODD,  CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (ZPODD_POWER_CONTROL, 1),   GPIO_DEVICE_INIT_DISABLE},
  //{DEVICE_ID_DT,   CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (DT_POWER_EN, 1),     GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WLAN, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WLAN_POWER_EN, 1),   GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_LAN,  CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LAN_POWER_EN, 1),      GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_RADIO_PERMITTED, 1),GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_POWER_EN, 1),  GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_ON,  CPM_POWER_DELAY, 100,                                     GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WWAN, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_CARD_POWER_OFF_L, 1),GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_WIFI, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WIFI_POWER_EN, 1),      GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C0, CPM_POWER_ON, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC0_AUX, 1), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C0, CPM_POWER_ON, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC0_MUX, 0), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C1, CPM_POWER_ON, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC1_AUX, 1), GPIO_DEVICE_INIT_STAGE_1},
  //{DEVICE_ID_USB_TYPE_C1, CPM_POWER_ON, CPM_POWER_SET, CPM_ECRAM_GPIO_PIN (HDMI_USBC1_MUX, 0), GPIO_DEVICE_INIT_STAGE_1},
  0xFF,
  }
};

//
// PCIE Clock Table
//
AMD_CPM_PCIE_CLOCK_TABLE    gCpmPcieClockTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_PCIE_CLOCK, sizeof (gCpmPcieClockTable) / sizeof (UINT8), 0, 0, 0x000000FF, 0x0F},
  {
//  {UINT8  ClkId;              // FCH PCIe Clock
//   UINT8  ClkReq;             // FCH PCIe ClkReq
//   UINT8  ClkIdExt;           // External Clock Source
//   UINT8  ClkReqExt;          // External ClkReq
//   UINT8  DeviceId;           // Device Id. No Device Id if 0xFF
//   UINT8  Device;             // Device Number of PCIe bridge
//   UINT8  Function;           // Function Number of PCIe bridge
//   UINT8  SlotCheck;          // Slot Check Flag: // BIT0: Check PCI Space // BIT1: Check GPIO pin // BIT2: Check Clock Power Management Enable // BIT3~6: Reserved // BIT7: Change PCIe Clock in ACPI method
//   UINT32 SpecialFunctionId;  // Id of Special Function}
//        (socket,die, ClkId,     ClkReq,     DeviceId,             Device,Function,SlotCheck)
    PCIE_INCLK (0, 0,  GPP_CLK0,  CLK_REQ0,   DEVICE_ID_LAN,         1,     1,       CLKPM_CHECK), // LAN1 RTL8125BG (LAN1_1)
    PCIE_INCLK (0, 0,  GPP_CLK1,  CLK_REQ1,   DEVICE_ID_LAN,         1,     2,       CLKPM_CHECK), // LAN2 RTL8125BG (LAN2_1)
    PCIE_INCLK (0, 0,  GPP_CLK2,  CLK_REQ2,   DEVICE_ID_M2_CONNECT,  1,     3,       CLKPM_CHECK), // M.2-B Key (B_KEY1)
    PCIE_INCLK (0, 0,  GPP_CLK5,  CLK_REQ5,   DEVICE_ID_DT,          1,     6,       CLKPM_CHECK), // Mini-PCIe (MINIPCIE1)
    PCIE_INCLK (0, 0,  GPP_CLK3,  CLK_REQ3,   DEVICE_ID_M2_CONNECT2, 1,     4,       CLKPM_CHECK), // M.2-M Key (M_KEY1)
    PCIE_INCLK (0, 0,  GPP_CLK4,  CLK_ENABLE, DEVICE_ID_DT,          1,     5,       CLKPM_CHECK), // PCI-E X8 SLOT (PCIE1)
    PCIE_INCLK (0, 0,  GPP_CLK6,  CLK_ENABLE, DEVICE_ID_DT,          1,     7,       CLKPM_CHECK), // PCI-E X8 SLOT (PCIE1)
    0xFF,
  }
};

//
// PCIE Clock Table - RV2
//
AMD_CPM_PCIE_CLOCK_TABLE    gCpmPcieClockTable_RV2 = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_PCIE_CLOCK, sizeof (gCpmPcieClockTable_RV2) / sizeof (UINT8), 0, 0, 0x3F001F00, 0x0F},
  {
//  {UINT8  ClkId;              // FCH PCIe Clock
//   UINT8  ClkReq;             // FCH PCIe ClkReq
//   UINT8  ClkIdExt;           // External Clock Source
//   UINT8  ClkReqExt;          // External ClkReq
//   UINT8  DeviceId;           // Device Id. No Device Id if 0xFF
//   UINT8  Device;             // Device Number of PCIe bridge
//   UINT8  Function;           // Function Number of PCIe bridge
//   UINT8  SlotCheck;          // Slot Check Flag: // BIT0: Check PCI Space // BIT1: Check GPIO pin // BIT2: Check Clock Power Management Enable // BIT3~6: Reserved // BIT7: Change PCIe Clock in ACPI method
//   UINT32 SpecialFunctionId;  // Id of Special Function}
//        (socket,die, ClkId,     ClkReq,     DeviceId,             Device,Function,SlotCheck)
    PCIE_INCLK (0, 0,  GPP_CLK0,  CLK_REQ0,   DEVICE_ID_LAN,         1,     1,       CLKPM_CHECK), // LAN1 RTL8125BG (LAN1_1)
    PCIE_INCLK (0, 0,  GPP_CLK1,  CLK_REQ1,   DEVICE_ID_LAN,         1,     2,       CLKPM_CHECK), // LAN2 RTL8125BG (LAN2_1)
    PCIE_INCLK (0, 0,  GPP_CLK2,  CLK_REQ2,   DEVICE_ID_M2_CONNECT,  1,     3,       CLKPM_CHECK), // M.2-B Key (B_KEY1)
    PCIE_INCLK (0, 0,  GPP_CLK5,  CLK_REQ5,   DEVICE_ID_DT,          1,     6,       CLKPM_CHECK), // Mini-PCIe (MINIPCIE1)
    PCIE_INCLK (0, 0,  GPP_CLK3,  CLK_REQ3,   DEVICE_ID_M2_CONNECT2, 1,     4,       CLKPM_CHECK), // M.2-M Key (M_KEY1)
    PCIE_INCLK (0, 0,  GPP_CLK4,  CLK_ENABLE, DEVICE_ID_DT,          1,     5,       CLKPM_CHECK), // PCI-E X8 SLOT (PCIE1)
    PCIE_INCLK (0, 0,  GPP_CLK6,  CLK_ENABLE, DEVICE_ID_DT,          1,     7,       CLKPM_CHECK), // PCI-E X8 SLOT (PCIE1)
    0xFF,
  }
};


//
// CPM DXIO Topology Table
//
/// Note: DO NOT change the seqeunce of the PCIe slot, NVME , M.2 and SATA Express engines
// PCie Complex will only have DxioPcieEngine and will not include Sata and unused engine components in AGESA.
// Device and function assignment happen to all PCIe devices with respect to PCIe complex and DXIP topology table sequence.
// All PCie complex should be defined first in the table. So we have defined PCIe Slot and NVMe  first in the table.
// Later Sata and M.2 Sata defined. We should not define any PCIe device after other components as per AGESA functanality.
AMD_CPM_DXIO_TOPOLOGY_TABLE gCpmDxioTopologyTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_DXIO_TOPOLOGY, sizeof (gCpmDxioTopologyTable) / sizeof (UINT8), 0, 0, 0x000000FF, 0x0000000F},
  0,  // SocketId
  {   // DXIO_PORT_DESCRIPTOR
//  { UINT32  Flags;                    /**< Descriptor flags
//    #define DXIO_ENGINE_DATA_INITIALIZER(mType, mStartLane, mEndLane, mHotplug, mGpioGroupId) {mType, mHotplug, 0, mStartLane, mEndLane, mGpioGroupId, 0, 0, 0}
//    #define DXIO_PORT_DATA_INITIALIZER_PCIE(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport) \
//            {mPortPresent, mDevAddress, mDevFunction, mMaxLinkSpeed, mAspm, mAspmL1_1, mAspmL1_2, 0, mHotplug, {0, mMaxLinkCap, 0, mClkPmSupport}, {0, 0, 0}, DxioEndpointDetect}
    {
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 0, 0, HotPluggableDisabled, DEVICE_ID_LAN),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        1,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmDisabled,                     // DxioAspmL0sL1, // ASPM
        DxioAspmL11Disabled,                  // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Disabled,                  // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_ENABLE                              // CLKREQ#
      )
    },
    {
      DESCRIPTOR_TERMINATE_LIST,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 1, 1, HotPluggableDisabled, DEVICE_ID_LAN),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        1,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmDisabled,                     // DxioAspmL0sL1, // ASPM
        DxioAspmL11Disabled,                  // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Disabled,                  // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_ENABLE                              // CLKREQ#
      )
    }
  },  // End of DXIO_PORT_DESCRIPTOR
  {   // DDI_DESCRIPTOR
    { // DDI0 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux1, Hdp1)
    },
    { // DDI1 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux2, Hdp2)
    },
    { // DDI2 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux3, Hdp3)
    },
    { // DDI3 - DP
      DESCRIPTOR_TERMINATE_LIST,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux4, Hdp4)
    }
  }   // End of PCIe_DDI_DESCRIPTOR
};

//
// CPM DXIO Topology Table - RV2
//
/// Note: DO NOT change the seqeunce of the PCIe slot, NVME , M.2 and SATA Express engines
// PCie Complex will only have DxioPcieEngine and will not include Sata and unused engine components in AGESA.
// Device and function assignment happen to all PCIe devices with respect to PCIe complex and DXIP topology table sequence.
// All PCie complex should be defined first in the table. So we have defined PCIe Slot and NVMe  first in the table.
// Later Sata and M.2 Sata defined. We should not define any PCIe device after other components as per AGESA functanality.
AMD_CPM_DXIO_TOPOLOGY_TABLE gCpmDxioTopologyTable_RV2 = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_DXIO_TOPOLOGY, sizeof (gCpmDxioTopologyTable_RV2) / sizeof (UINT8), 0, 0, 0x3F001F00, 0x0000000F},
  0,  // SocketId
  {   // DXIO_PORT_DESCRIPTOR
//  { UINT32  Flags;                    /**< Descriptor flags
//    #define DXIO_ENGINE_DATA_INITIALIZER(mType, mStartLane, mEndLane, mHotplug, mGpioGroupId) {mType, mHotplug, 0, mStartLane, mEndLane, mGpioGroupId, 0, 0, 0}
//    #define DXIO_PORT_DATA_INITIALIZER_PCIE(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport) \
//  {mPortPresent, mDevAddress, mDevFunction, mMaxLinkSpeed, mAspm, mAspmL1_1, mAspmL1_2, 0, mHotplug, {0, mMaxLinkCap, 0, mClkPmSupport}, {0, 0, 0}, DxioEndpointDetect}
    { // DEVICE_ID_MXM                        Entry 0
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 11, 8, HotPluggableDisabled, DEVICE_ID_MXM),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        1,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ3                              // CLKREQ#
      )
    },
    { // DEVICE_ID_DT                       Entry 1
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 4, 5, HotPluggableDisabled, DEVICE_ID_DT),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        2,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ4                              // CLKREQ#
      )
    },
    { // PCIE M.2 x2                         Entry 2
     0,
     DXIO_ENGINE_DATA_INITIALIZER(DxioUnusedEngine, 0, 1, HotPluggableDisabled, DEVICE_ID_SSD),
     DXIO_PORT_DATA_INITIALIZER_PCIE_V2(
       DxioPortEnabled,                     // Port Present
       1,                                    // Requested Device
       5,                                    // Requested Function
       DxioHotplugDisabled,                  // Hotplug
       DxioGenMaxSupported,                  // Max Link Speed
       DxioGenMaxSupported,                  // Max Link Capability
       DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
       DxioAspmL11Disabled,                  // ASPM L1.1  // 0:disabled, 1:Enabled
       DxioAspmL12Disabled,                  // ASPM L1.2  // 0:disabled, 1:Enabled
       DxioClkPmSupportDisabled,             // Clock PM
       CLK_REQ2              				 // CLKREQ#
       )
    },
    { // PCIE M.2 x2                         Entry 3  //R1000 supports only X2 .
     0,
     DXIO_ENGINE_DATA_INITIALIZER(DxioUnusedEngine, 2, 3, HotPluggableDisabled, DEVICE_ID_SSD),
     DXIO_PORT_DATA_INITIALIZER_PCIE_V2(
       DxioPortEnabled,                     // Port Present
       1,                                    // Requested Device
       5,                                    // Requested Function
       DxioHotplugDisabled,                  // Hotplug
       DxioGenMaxSupported,                  // Max Link Speed
       DxioGenMaxSupported,                  // Max Link Capability
       DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
       DxioAspmL11Disabled,                  // ASPM L1.1  // 0:disabled, 1:Enabled
       DxioAspmL12Disabled,                  // ASPM L1.2  // 0:disabled, 1:Enabled
       DxioClkPmSupportDisabled,             // Clock PM
       CLK_REQ2              				 // CLKREQ#
       )
    },	
    { // DEVICE_ID_SATA_EXPRESS    iSata     Entry 4
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioSATAEngine, 3, 3, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_SATA_V2 (DxioPortEnabled, DxioSataChannelLong)    // Port Present
      PHY_PARAMS_START                           // The SATA PHY tuning values must be configured to all DxioSATAEngine 
        PHY_PARAM (GEN1_txX_eq_pre, 0),          // otherwise the values won't be changed in the register.
        PHY_PARAM (GEN1_txX_eq_main, 0x20),
        PHY_PARAM (GEN1_txX_eq_post, 0x06),
        PHY_PARAM (GEN2_txX_eq_pre, 0),
        PHY_PARAM (GEN2_txX_eq_main, 0x22),
        PHY_PARAM (GEN2_txX_eq_post, 0x18),
        PHY_PARAM (GEN3_txX_eq_pre, 0x0),
        PHY_PARAM (GEN3_txX_eq_main, 0x1D),
        PHY_PARAM (GEN3_txX_eq_post, 0x2C),
      PHY_PARAMS_END
    },
    { // DEVICE_ID_SATA_EXPRESS    M.2 Sata  Entry 5  
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioSATAEngine, 2, 2, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_SATA_V2 (DxioPortEnabled, DxioSataChannelLong)    // Port Present
      PHY_PARAMS_START
        PHY_PARAM (GEN1_txX_eq_pre, 0),
        PHY_PARAM (GEN1_txX_eq_main, 0x20),
        PHY_PARAM (GEN1_txX_eq_post, 0x06),
        PHY_PARAM (GEN2_txX_eq_pre, 0),
        PHY_PARAM (GEN2_txX_eq_main, 0x22),
        PHY_PARAM (GEN2_txX_eq_post, 0x18),
        PHY_PARAM (GEN3_txX_eq_pre, 0x0),
        PHY_PARAM (GEN3_txX_eq_main, 0x1D),
        PHY_PARAM (GEN3_txX_eq_post, 0x2C),
      PHY_PARAMS_END
    },

    { // P0 - Ehernet Port 0        		Entry 6
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioEthernetEngine, 0, 0, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_ENET (
        DxioPortEnabled,            // Port Present
        0,    /// mPortNum
        8,    /// mPlatConf 		(10G Base T => Default, 8 = SFP+)
        0,    /// mMdioId           (If MDIO is not used by this port, set this to 0)
        0xD,  /// mSuppSpeed		(For SFP+ connectors, 10G, 1G and 100M support should be indicated)
        1,    /// mConnType  		(1 = SFP+ Connection I2C interface, 2 = MDIO PHY)
        0,    /// mMdioReset 		(MDIO Reset Type, Integrated GPIO)
        0,    /// mMdioGpioResetNum (Integrated GPIO number for reset)
        1,    /// mSfpGpioAdd 		(Lower I2C address of GPIO Expander PCA9535)
        0xE,  /// mTxFault,		    (I/O1_6 connected SFP+_XGB0_TX_FAULT 0_0 to 0_7 = 8 , 1_0 to 1_6 = 7 , 8+7= 15-1 = E ( -1 for excluding for 0)
        0,    /// mRs,
        0xC,  /// mModAbs,
        0xD,  /// mRxLoss,
        0x2,  /// mSfpGpioMask, 	(xx1xb = RS not supported)
        0x3,  /// mSfpMux, 		    (Lower address of Mux PCA 9545 or 111b if SFP+ directly connected to I2C) //SFP+ TWI Multiplexer
        0x0,  /// mSfpBusSeg, 		(SFP BUS Segment. Downstream channels of PCA9545) //SFP+ TWI Bus Segment
        0x1C, /// mSfpMuxUpAdd, 	(Upper address of Mux PCA 9545) 
        0x0,  /// mRedriverAddress,
        1,    /// mRedriverInterface, 	(1 => I2C, 0 => MDIO)
        0,    /// mRedriverLane,
        0,    /// mRedriverModel,
        0,    /// mRedriverPresent,
        0x1,  /// mPadMux0, 		(Pad Mux Setting)
        0,    /// mPadMux1, 		(Pad Mux Setting)
        0x0,  /// mMacAddressLo,    (TO BE FILLED IN BY CODE)
        0x0,  /// mMacAddressHi,    (TO BE FILLED IN BY CODE)
        0,  /// mTxEqPre,  TBD    //TODO
        32,  /// mTxEqMain, TBD    //TODO
        32   /// mTxEqPost  TBD    //TODO
      )
    },
    {   // P1 - Ethernet Port1      	//entry 7
        DESCRIPTOR_TERMINATE_LIST,
        DXIO_ENGINE_DATA_INITIALIZER (DxioEthernetEngine, 1, 1, HotPluggableDisabled, 1),
        DXIO_PORT_DATA_INITIALIZER_ENET (
        DxioPortEnabled,            // Port Present
        1,    /// mPortNum
        8,    /// mPlatConf 		(10G Base T => Default, 8 = SFP+)
        0,    /// mMdioId           (If MDIO is not used by this port, set this to 0)
        0xD,  /// mSuppSpeed		(For SFP+ connectors, 10G, 1G and 100M support should be indicated)
        1,    /// mConnType  		(1 = SFP+ Connection I2C interface, 2 = MDIO PHY)
        0,    /// mMdioReset 		(MDIO Reset Type, Integrated GPIO)
        0,    /// mMdioGpioResetNum (Integrated GPIO number for reset)
        1,    /// mSfpGpioAdd 		(Lower I2C address of GPIO Expander PCA9535)
        0x6,  /// mTxFault,		    (I/O0_6 connected SFP+_XGB1_TX_FAULT 0_0 to 0_6 = 7  7-1 = 6 ( -1 for excluding for 0)
        0,    /// mRs,
        0x4,  /// mModAbs,
        0x5,  /// mRxLoss,
        0x2,  /// mSfpGpioMask, 	(xx1xb = RS not supported)
        0x3,  /// mSfpMux, 		    (Lower address of Mux PCA 9545 or 111b if SFP+ directly connected to I2C) //SFP+ TWI Multiplexer
        0x1,  /// mSfpBusSeg, 		(SFP BUS Segment. Downstream channels of PCA954) //SFP+ TWI Bus Segment
        0x1C, /// mSfpMuxUpAdd, 	(Upper address of Mux PCA 9545) 
        0x0,  /// mRedriverAddress,
        1,    /// mRedriverInterface, 	(1 => I2C, 0 => MDIO)
        0,    /// mRedriverLane,
        0,    /// mRedriverModel,
        0,    /// mRedriverPresent,
        0x1,  /// mPadMux0, 		(Pad Mux Setting)
        0,    /// mPadMux1, 		(Pad Mux Setting)
        0x0,  /// mMacAddressLo,    (TO BE FILLED IN BY CODE)
        0x0,  /// mMacAddressHi,    (TO BE FILLED IN BY CODE)
        0,  /// mTxEqPre,
        33,  /// mTxEqMain,
        28   /// mTxEqPost
      )
    }
  },  // End of DXIO_PORT_DESCRIPTOR
  {   // DDI_DESCRIPTOR
    { // DDI0 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux1, Hdp1)
    },
    { // DDI1 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux2, Hdp2)
    },
    // DDI2 is disconnected for R1000. Use DDI3 for 3rd Display	
    { // DDI3 - DP
      DESCRIPTOR_TERMINATE_LIST,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux4, Hdp4)
    }
  }   // End of PCIe_DDI_DESCRIPTOR
};

//
// CPM Display Feature Module
//

//
// CPM Device Path Table
//
AMD_CPM_DEVICE_PATH_TABLE gCpmDevicePathTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_DEVICE_PATH, sizeof (gCpmDevicePathTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  {
//  {AMD_CPM_DISPLAY_FEATURE_SUPPORT FeatureMask; // See AMD_CPM_DISPLAY_FEATURE_SUPPORT
//   UINT8                           IsDgpu;      // Is Igpu or Dgpu. 0: iGpu; 1: dGpu
//   AMD_CPM_PCI_DEVICE_FUNCTION     Bridge;      // Device and function number of PCIe Bridge
//   AMD_CPM_PCI_DEVICE_FUNCTION     Device;      // Device and function number of Display Device
//   UINT8                           DeviceId;    // Device Id to control GPIO
//   UINT8                           Mode;        // Power mode
//   UINT8                           DeviceIdVcc; // Device Id for Vcc when D3Cold is supported}
    {0x80000003, 0x00, {8, 1}, {0, 0}},                                                    // PowerXpress|HCF, iGPU, (0,8,1)/(0,0)
    {0x8000000B, 0x01, {1, 1}, {0, 0}, DEVICE_ID_VGAMUXSEL, CPM_POWER_OFF, DEVICE_ID_MXM}, // PowerXpress|HCF, dGPU, (0,1,1)/(0,0)
    {0x80000000, 0x01, {1, 2}, {0, 0}},                                                    // dGPU, (0,1,2)/(0,0)
    {0x00000000, 0x00, {0, 0}, {0, 0}},
  }
};

//
// CPM Display Feature Table
//
AMD_CPM_DISPLAY_FEATURE_TABLE gCpmDisplayFeatureTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_DISPLAY_FEATURE, sizeof (gCpmDisplayFeatureTable) / sizeof (UINT8), 0, 0, 0, 0x0000000F},
  1,                            // UINT8  FunctionDisableMask;  // BIT0: Disable SetSsid. BIT1: Disable AddSsdt
  DEVICE_ID_MXM,                // UINT8  MxmDeviceId;          // Device Id for MXM
  0xFF,                         // UINT8  MxmOverTempEvent;     // GEVENT pin number for MXM_OVERT#
  2,                            // UINT8  MxmOverTempStateId;   // Forced Power State Id if MXM_OVERT# is low
  0x02,                         // UINT8  DisplayConnectEvent;  // GEVENT pin number for Discrete GPU display connect/disconnect event
  0,                            // UINT8  DockingDeviceId;      // Bit[0-6]: Device Id for docking detection if Bit7 = 0  // Forced docking status if Bit7 = 1
  0,                            // UINT8  MuxFlag;              // The flag for Mux-Based Power Xpress
  0,                            // UINT8  DisplayMuxDeviceId;   // Device Id for Display Mux
  0,                            // UINT8  I2xMuxDeviceId;       //
  10,                           // UINT8  AtpxConnector8Number; // Number of reported display connectors in ATPX sub-function 8
  {                             // AMD_CPM_DISPLAY_CONNECTOR_8 AtpxConnector8[AMD_ATPX_CONNECTOR_8_SIZE]; // The Connector information for ATPX sub-function 8
    {0x05, 0x00, 0x00, 0x0110}, // Connector #0: LCD1 on iGPU
    {0x07, 0x03, 0x00, 0x0210}, // Connector #1: DFP1 on iGPU
    {0x07, 0x07, 0x00, 0x0220}, // Connector #2: DFP2 on iGPU
    {0x07, 0x09, 0x00, 0x0230}, // Connector #3: DFP3 on iGPU
    {0x07, 0x0A, 0x00, 0x0240}, // Connector #4: DFP4 on iGPU
    {0x01, 0x00, 0x01, 0x0110}, // Connector #5: LCD1 on dGPU
    {0x03, 0x03, 0x01, 0x0210}, // Connector #6: DFP1 on dGPU
    {0x03, 0x07, 0x01, 0x0220}, // Connector #7: DFP2 on dGPU
    {0x03, 0x09, 0x01, 0x0230}, // Connector #8: DFP3 on dGPU
    {0x03, 0x0A, 0x01, 0x0240}, // Connector #9: DFP4 on dGPU
  },
  0,                            // UINT8 AtpxConnector9Number;  // Number of reported display connectors in ATPX sub-function 9
  {                             // AMD_CPM_DISPLAY_CONNECTOR_9 AtpxConnector9[AMD_ATPX_CONNECTOR_9_SIZE]; // The Connector information for ATPX sub-function 9
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00},
  },
  0x59,                         // UINT32 AtifSupportedNotificationMask; // Supported Notifications Mask in ATIF sub-function 0
  7,                            // UINT8  AtifDeviceCombinationNumber;   // The number of Display Device Combination
  {                             // UINT8  AtifDeviceCombinationBuffer[AMD_ATIF_DEVICE_COMBINATION_BUFFER_SIZE]; // The data of Display Device Combination
    0x01, 0x02, 0x08, 0x80, 0x03, 0x09, 0x81 // AtifDeviceCombinationBuffer[20];
  },
  {                             // UINT8  Atif16Buffer[0x100];           // The data for Query Brightness Transfer Characteristics
    0x6C, 0x00,                 // WORD Structure Size : 0x6A
    0x00, 0x00,                 // WORD Flags          : Reserved
    0x00,                       // BYTE        Error Code     : 0x00
    0x64,                       // BYTE        AC Level       : 100%
    0x20,                       // BYTE        DC Level       : 32%
    0x0C,                       // BYTE        Minimum signal : 12
    0xFF,                       // BYTE        Maximum signal : 255
    0x31,                       // BYTE        Count          : 49
    0x02, 0x0E,                 // BYTE-BYTE    First Lumi/Signal: 2% - 14
    0x04, 0x10,                 // BYTE-BYTE
    0x06, 0x12,                 // BYTE-BYTE
    0x08, 0x15,                 // BYTE-BYTE
    0x0A, 0x17,                 // BYTE-BYTE
    0x0C, 0x1A,                 // BYTE-BYTE
    0x0E, 0x1D,                 // BYTE-BYTE
    0x10, 0x20,                 // BYTE-BYTE
    0x12, 0x23,                 // BYTE-BYTE
    0x14, 0x26,                 // BYTE-BYTE
    0x16, 0x29,                 // BYTE-BYTE
    0x18, 0x2C,                 // BYTE-BYTE
    0x1A, 0x30,                 // BYTE-BYTE
    0x1C, 0x34,                 // BYTE-BYTE
    0x1E, 0x37,                 // BYTE-BYTE
    0x20, 0x3B,                 // BYTE-BYTE
    0x22, 0x3E,                 // BYTE-BYTE
    0x24, 0x43,                 // BYTE-BYTE
    0x26, 0x47,                 // BYTE-BYTE
    0x28, 0x4B,                 // BYTE-BYTE
    0x2A, 0x50,                 // BYTE-BYTE
    0x2C, 0x54,                 // BYTE-BYTE
    0x2E, 0x58,                 // BYTE-BYTE
    0x30, 0x5D,                 // BYTE-BYTE
    0x32, 0x62,                 // BYTE-BYTE
    0x34, 0x67,                 // BYTE-BYTE
    0x36, 0x6C,                 // BYTE-BYTE
    0x38, 0x71,                 // BYTE-BYTE
    0x3A, 0x76,                 // BYTE-BYTE
    0x3C, 0x7B,                 // BYTE-BYTE
    0x3E, 0x81,                 // BYTE-BYTE
    0x40, 0x87,                 // BYTE-BYTE
    0x42, 0x8C,                 // BYTE-BYTE
    0x44, 0x92,                 // BYTE-BYTE
    0x46, 0x98,                 // BYTE-BYTE
    0x48, 0x9E,                 // BYTE-BYTE
    0x4A, 0xA4,                 // BYTE-BYTE
    0x4C, 0xAB,                 // BYTE-BYTE
    0x4E, 0xB1,                 // BYTE-BYTE
    0x50, 0xB7,                 // BYTE-BYTE
    0x52, 0xBE,                 // BYTE-BYTE
    0x54, 0xC5,                 // BYTE-BYTE
    0x56, 0xCC,                 // BYTE-BYTE
    0x58, 0xD3,                 // BYTE-BYTE
    0x5A, 0xDA,                 // BYTE-BYTE
    0x5C, 0xE1,                 // BYTE-BYTE
    0x5E, 0xE8,                 // BYTE-BYTE
    0x60, 0xF0,                 // BYTE-BYTE
    0x62, 0xF7                  // BYTE-BYTE   Last Lumi/Signal: 98% - 250
  }
};

/*  No ZPODD support in Dibbler / Bilby
//
// CPM Zero Power Odd Table RevB
//
AMD_CPM_ZERO_POWER_ODD_TABLE      gCpmZeroPowerOddTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_ZERO_POWER_ODD, sizeof (gCpmZeroPowerOddTable) / sizeof (UINT8), 0, 0, 0x0, 0x0000000F},
  DEVICE_ID_ODD,        // UINT8 DeviceId;            // Device Id
  ZPODD_DA_GPIO,        // UINT8 EventPin1;           // Event Pin Number for ODD_DA#
  ZPODD_PLUGIN_GPIO,   // UINT8 EventPin2;           // Event Pin Number for ODD_PLUGIN#
  ZPODD_DUMMY_EVENT,    // UINT8 EventPin3;           // Dummy Event
  ZPODD_SATA_MASK,      // UINT8 SataModeSupportMask; // Mask of SATA mode to support  ///< BIT0: IDE Mode ///< BIT1: AHCI Mode  ///< BIT2: RAID Mode  ///< BIT3: AMD AHCI Mode
  ZPODD_SATA_PORT,      // UINT8 SataPortId;          // Sata Port Number for Odd
  ZPODD_DA_SOURCE,      // UINT8 EventSource1;        // Source of ODD_DA#     - 0: FCH GPIO Pin, 1: KBC GPIO Pin, 2: ECRAM GPIO Pin
  ZPODD_PLUGIN_SOURCE,  // UINT8 EventSource2;        // Source of ODD_PLUGIN# - 0: FCH GPIO Pin, 1: KBC GPIO Pin, 2: ECRAM GPIO Pin
  ZPODD_DA_FALLING,     // UINT8 QEventFalling1;      // QEvent Number for ODD_DA#     FALLING  if EventSource1 = 1 or 2
  ZPODD_DA_RISING,      // UINT8 QEventRising1;       // QEvent Number for ODD_DA#     RISING   if EventSource1 = 1 or 2
  ZPODD_PLUGIN_FALLING, // UINT8 QEventFalling2;      // QEvent Number for ODD_PLUGIN# FALLING if EventSource2 = 1 or 2
  ZPODD_PLUGIN_RISING,  // UINT8 QEventRising2;       // QEvent Number for ODD_PLUGIN# RISING  if EventSource2 = 1 or 2
};
*/

//
// Save Context Table
//
AMD_CPM_SAVE_CONTEXT_TABLE        gCpmSaveContextTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_SAVE_CONTEXT, sizeof (gCpmSaveContextTable) / sizeof (UINT8), 0, 0, 0, 0x01},
  0x05, // UINT8 BufferType;   // Buffer Type. 5: BIOS RAM. Other: Reserved.
  0x50, // UINT8 BufferOffset; // Buffer Offset
  0x10, // UINT8 BufferSize;   // Buffer Size
};
/*  we don't support ADAPTIVE S4 and Ucsi in Dibbler / Bilby
//
// Adaptive S4 Table
//
AMD_CPM_ADAPTIVE_S4_TABLE         gCpmAdaptiveS4Table = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_ADAPTIVE_S4, sizeof (gCpmAdaptiveS4Table) / sizeof (UINT8), 0, 0, 0, 0x0F},
  0x05, // UINT8 BufferType;   // Buffer Type. 5: BIOS RAM. Other: Reserved.
  0x40, // UINT8 BufferOffset; // Buffer Offset
  0x0C, // UINT8 BufferSize;   // Buffer Size
  0xE0  // UINT8 EcRamOffset;  // Offset of EC RAM
};

//
// UCSI Table
//
AMD_CPM_UCSI_TABLE         gCpmUcsiTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_UCSI, sizeof (gCpmUcsiTable) / sizeof (UINT8), 0, 0, 0, 0x0F},
  0x00, // UINT32 EcUcsiLocation;   // EC UCSI Location. // 0: EmbeddedControl. others: System Memory Address
  0x64, // UINT8  EcCciLocation;    // EC UCSI USB Type-C Command Status & Connector Change Indication Offset
  0x68, // UINT8  EcCtlLocation;    // EC UCSI USB Type-C Control Offset
  0x70, // UINT8  EcMgiLocation;    // EC UCSI USB Type-C Message In Offset
  0x80, // UINT8  EcMgoLocation;    // EC UCSI USB Type-C Message Out Offset
  0xE0, // UINT8  EcUcsiCommand;    // EC UCSI Command
  0x668,// UINT16 EcUcsiCommandIo;  // EC UCSI Command IO Port
  0x50, // UINT8  EcUcsiQEvent;     // EC UCSI QEvent Number
  {     // UINT8  Reserved[48];     // Reserve for UCSI OPM ACPI OperationRegion CpmUcsiOperationRegion
    0x00
  },
  {     // AMD_UCSI_PLD_INFO Port[UCSI_PORT_NUMBER];              // UCSI Port _PLD information
    {0x00000082, 0x00000000, 0x02001D51, 0x00000001, 0xFFFFFFFF}, // UCSI Port 0 _PLD information
    {0x00000082, 0x00000000, 0x02801D51, 0x00000001, 0xFFFFFFFF}, // UCSI Port 1 _PLD information
  }
};
*/

// Azalia verb table for 898/899
//

UINT32 AzaliaCodecVerbTable[] = {
        0x10EC0899,                                       // Start of 0x10EC0899
        0x00172050, 0x001721C9, 0x00172222, 0x00172310,   // HDA Codec Subsystem ID  : 0x1022C950
        0x0017FF00, 0x0017FF00, 0x0017FF00, 0x0017FF00,   // Widget node 0x01 :
        0x01171C00, 0x01171D00, 0x01171E33, 0x01171F40,   // Pin widget 0x11 - S/PDIF-OUT2
        0x01271CF0, 0x01271D11, 0x01271E11, 0x01271F41,   // Pin widget 0x12 - DMIC
        0x01471C10, 0x01471D40, 0x01471E01, 0x01471F01,   // Pin widget 0x14 - FRONT (Port-D)
        0x01571C14, 0x01571D10, 0x01571E01, 0x01571F01,   // Pin widget 0x15 - SURR (Port-A)
        0x01671C11, 0x01671D60, 0x01671E01, 0x01671F01,   // Pin widget 0x16 - CEN/LFE (Port-G)
        0x01771CF0, 0x01771D11, 0x01771E11, 0x01771F41,   // Pin widget 0x17 - SIDESURR (Port-H)
        0x01871C40, 0x01871D90, 0x01871EA1, 0x01871F01,   // Pin widget 0x18 - MIC1 (Port-B)
        0x01971C50, 0x01971D10, 0x01971EA1, 0x01971F02,   // Pin widget 0x19 - MIC2 (Port-F)
        0x01A71C60, 0x01A71D30, 0x01A71E81, 0x01A71F01,   // Pin widget 0x1A - LINE1 (Port-C)
        0x01B71C20, 0x01B71D10, 0x01B71E21, 0x01B71F02,   // Pin widget 0x1B - LINE2 (Port-E)
        0x01C71CF0, 0x01C71D11, 0x01C71E11, 0x01C71F41,   // Pin widget 0x1C - CD-IN
        0x01D71C01, 0x01D71DF6, 0x01D71E26, 0x01D71F40,   // Pin widget 0x1D - BEEP-IN
        0x01E71C30, 0x01E71D11, 0x01E71E45, 0x01E71F01,   // Pin widget 0x1E - S/PDIF-OUT1
        0x01F71CF0, 0x01F71D11, 0x01F71E11, 0x01F71F41,   // Pin widget 0x1F - S/PDIF-IN
        0x02050007, 0x02040180, 0x02050001, 0x0204C7AA,   // Widget node 0x20 :
        0x02050015, 0x0204026A, 0x02050008, 0x02040071,   // Widget node 0x20 - 1 :
        0xFFFFFFFF,                                       // End of 0x10EC0899
        0x10EC0898,                                       // Start of 0x10EC0898
        0x00172050, 0x001721C9, 0x00172222, 0x00172310,   // HDA Codec Subsystem ID  : 0x1022C950
        0x0017FF00, 0x0017FF00, 0x0017FF00, 0x0017FF00,   // Widget node 0x01 :
        0x01171C00, 0x01171D00, 0x01171E33, 0x01171F40,   // Pin widget 0x11 - S/PDIF-OUT2
        0x01271CF0, 0x01271D11, 0x01271E11, 0x01271F41,   // Pin widget 0x12 - DMIC
        0x01471C10, 0x01471D40, 0x01471E01, 0x01471F01,   // Pin widget 0x14 - FRONT (Port-D)
        0x01571C14, 0x01571D10, 0x01571E01, 0x01571F01,   // Pin widget 0x15 - SURR (Port-A)
        0x01671C11, 0x01671D60, 0x01671E01, 0x01671F01,   // Pin widget 0x16 - CEN/LFE (Port-G)
        0x01771CF0, 0x01771D11, 0x01771E11, 0x01771F41,   // Pin widget 0x17 - SIDESURR (Port-H)
        0x01871C40, 0x01871D90, 0x01871EA1, 0x01871F01,   // Pin widget 0x18 - MIC1 (Port-B)
        0x01971C50, 0x01971D10, 0x01971EA1, 0x01971F02,   // Pin widget 0x19 - MIC2 (Port-F)
        0x01A71C60, 0x01A71D30, 0x01A71E81, 0x01A71F01,   // Pin widget 0x1A - LINE1 (Port-C)
        0x01B71C20, 0x01B71D10, 0x01B71E21, 0x01B71F02,   // Pin widget 0x1B - LINE2 (Port-E)
        0x01C71CF0, 0x01C71D11, 0x01C71E11, 0x01C71F41,   // Pin widget 0x1C - CD-IN
        0x01D71C01, 0x01D71DF6, 0x01D71E26, 0x01D71F40,   // Pin widget 0x1D - BEEP-IN
        0x01E71C30, 0x01E71D11, 0x01E71E45, 0x01E71F01,   // Pin widget 0x1E - S/PDIF-OUT1
        0x01F71CF0, 0x01F71D11, 0x01F71E11, 0x01F71F41,   // Pin widget 0x1F - S/PDIF-IN
        0x02050007, 0x02040180, 0x02050001, 0x0204C7AA,   // Widget node 0x20 :
        0x02050015, 0x0204026A, 0x02050008, 0x02040071,   // Widget node 0x20 - 1 :
        0xFFFFFFFF,                                       // End of 0x10EC0898
        0xFFFFFFFF, 0xFFFFFFFF                            // End of AzaliaCodecVerbTable
};

UINT8 Hdmi0RetimerRedriverR1000[] = {
    0xBA, // HdmiSlvAddr
    0x03, // HdmiRegNum
    0x03, // Hdmi6GRegNum
    0x0A, 0x13,  // HdmiRegSetting[0].ucI2cRegIndex , HdmiRegSetting[0].ucI2cRegVal
    0x0B, 0xC8,  // HdmiRegSetting[1].ucI2cRegIndex , HdmiRegSetting[1].ucI2cRegVal
    0x0C, 0xD4,  // HdmiRegSetting[2].ucI2cRegIndex , HdmiRegSetting[2].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[3].ucI2cRegIndex , HdmiRegSetting[3].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[4].ucI2cRegIndex , HdmiRegSetting[4].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[5].ucI2cRegIndex , HdmiRegSetting[5].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[6].ucI2cRegIndex , HdmiRegSetting[6].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[7].ucI2cRegIndex , HdmiRegSetting[7].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[8].ucI2cRegIndex , HdmiRegSetting[8].ucI2cRegVal
    0x0A, 0x13,  // Hdmi6GhzRegSetting[0].ucI2cRegIndex , Hdmi6GhzRegSetting[0].ucI2cRegVal
    0x0B, 0xDA,  // Hdmi6GhzRegSetting[1].ucI2cRegIndex , Hdmi6GhzRegSetting[1].ucI2cRegVal
    0x0C, 0x3D   // Hdmi6GhzRegSetting[2].ucI2cRegIndex , Hdmi6GhzRegSetting[2].ucI2cRegVal
};

UINT8 Hdmi1RetimerRedriverR1000[] = {
    0xBC, // HdmiSlvAddr
    0x03, // HdmiRegNum
    0x03, // Hdmi6GRegNum
    0x0A, 0x13,  // HdmiRegSetting[0].ucI2cRegIndex , HdmiRegSetting[0].ucI2cRegVal
    0x0B, 0xC8,  // HdmiRegSetting[1].ucI2cRegIndex , HdmiRegSetting[1].ucI2cRegVal
    0x0C, 0xB4,  // HdmiRegSetting[2].ucI2cRegIndex , HdmiRegSetting[2].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[3].ucI2cRegIndex , HdmiRegSetting[3].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[4].ucI2cRegIndex , HdmiRegSetting[4].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[5].ucI2cRegIndex , HdmiRegSetting[5].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[6].ucI2cRegIndex , HdmiRegSetting[6].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[7].ucI2cRegIndex , HdmiRegSetting[7].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[8].ucI2cRegIndex , HdmiRegSetting[8].ucI2cRegVal
    0x0A, 0x13,  // Hdmi6GhzRegSetting[0].ucI2cRegIndex , Hdmi6GhzRegSetting[0].ucI2cRegVal
    0x0B, 0xDA,  // Hdmi6GhzRegSetting[1].ucI2cRegIndex , Hdmi6GhzRegSetting[1].ucI2cRegVal
    0x0C, 0x3D   // Hdmi6GhzRegSetting[2].ucI2cRegIndex , Hdmi6GhzRegSetting[2].ucI2cRegVal
};

UINT8 Hdmi0RetimerRedriverV1000[] = {
    0xBA, // HdmiSlvAddr
    0x03, // HdmiRegNum
    0x03, // Hdmi6GRegNum
    0x0A, 0x13,  // HdmiRegSetting[0].ucI2cRegIndex , HdmiRegSetting[0].ucI2cRegVal
    0x0B, 0xC8,  // HdmiRegSetting[1].ucI2cRegIndex , HdmiRegSetting[1].ucI2cRegVal
    0x0C, 0xD9,  // HdmiRegSetting[2].ucI2cRegIndex , HdmiRegSetting[2].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[3].ucI2cRegIndex , HdmiRegSetting[3].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[4].ucI2cRegIndex , HdmiRegSetting[4].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[5].ucI2cRegIndex , HdmiRegSetting[5].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[6].ucI2cRegIndex , HdmiRegSetting[6].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[7].ucI2cRegIndex , HdmiRegSetting[7].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[8].ucI2cRegIndex , HdmiRegSetting[8].ucI2cRegVal
    0x0A, 0x13,  // Hdmi6GhzRegSetting[0].ucI2cRegIndex , Hdmi6GhzRegSetting[0].ucI2cRegVal
    0x0B, 0xDA,  // Hdmi6GhzRegSetting[1].ucI2cRegIndex , Hdmi6GhzRegSetting[1].ucI2cRegVal
    0x0C, 0x3D   // Hdmi6GhzRegSetting[2].ucI2cRegIndex , Hdmi6GhzRegSetting[2].ucI2cRegVal
};

UINT8 Hdmi1RetimerRedriverV1000[] = {
    0xBC, // HdmiSlvAddr
    0x03, // HdmiRegNum
    0x03, // Hdmi6GRegNum
    0x0A, 0x13,  // HdmiRegSetting[0].ucI2cRegIndex , HdmiRegSetting[0].ucI2cRegVal
    0x0B, 0xD8,  // HdmiRegSetting[1].ucI2cRegIndex , HdmiRegSetting[1].ucI2cRegVal
    0x0C, 0x91,  // HdmiRegSetting[2].ucI2cRegIndex , HdmiRegSetting[2].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[3].ucI2cRegIndex , HdmiRegSetting[3].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[4].ucI2cRegIndex , HdmiRegSetting[4].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[5].ucI2cRegIndex , HdmiRegSetting[5].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[6].ucI2cRegIndex , HdmiRegSetting[6].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[7].ucI2cRegIndex , HdmiRegSetting[7].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[8].ucI2cRegIndex , HdmiRegSetting[8].ucI2cRegVal
    0x0A, 0x13,  // Hdmi6GhzRegSetting[0].ucI2cRegIndex , Hdmi6GhzRegSetting[0].ucI2cRegVal
    0x0B, 0xDA,  // Hdmi6GhzRegSetting[1].ucI2cRegIndex , Hdmi6GhzRegSetting[1].ucI2cRegVal
    0x0C, 0x3D   // Hdmi6GhzRegSetting[2].ucI2cRegIndex , Hdmi6GhzRegSetting[2].ucI2cRegVal
};
//
// OEM CPM Table definition end
//

/*----------------------------------------------------------------------------------------*/
/**
 * Detect MXM card presence
 *
 * This function returns the presence of MXM card
 *
 * @param[in]     This           Pointer to AMD CPM Table PPI
 *
 * @retval        TURE  - MXM card is present
 * @retval        FALSE - MXM card is not present
 *
 */
BOOLEAN
MxmPresent (
  IN       AMD_CPM_TABLE_PPI   *This
  )
{
  AMD_CPM_TABLE_PPI       *CpmTablePpiPtr;
//  AMD_CPM_GPIO_INIT_TABLE *GpioTablePtr;
//  AMD_CPM_GPIO_ITEM       *TablePtr;

  CpmTablePpiPtr = This;
//  if (CpmTablePpiPtr) {
//    GpioTablePtr = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_GPIO_INIT);
//    if (GpioTablePtr) {
//      TablePtr = &GpioTablePtr->GpioList[0];
//      while (TablePtr->Pin != 0xFF ) {
//        if(TablePtr->Pin == 0x45) {
//          CpmTablePpiPtr->CommonFunction.SetGpio (CpmTablePpiPtr, TablePtr->Pin, TablePtr->Setting.Raw);
//          break;
//        }
//        TablePtr++;
//      }
//    }
//  }
  return (CpmTablePpiPtr->CommonFunction.DetectDevice (CpmTablePpiPtr, DEVICE_ID_MXM, NULL));
}

/*----------------------------------------------------------------------------------------*/
/**
 * Update SMBUS port
 *
 * @param[in]     AmdCpmTablePpi            Pointer to AMD CPM Table PPI
 *
 */
VOID
SetSmBusPort (
  IN       AMD_CPM_TABLE_PPI            *AmdCpmTablePpi
  )
{
  UINT16                  LoopCount;
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;

  MainTablePtr        = AmdCpmTablePpi->MainTablePtr;
  CommonFunctionPtr   = &AmdCpmTablePpi->CommonFunction;

  // Hold the SMBUS Semaphore first. (SMBUSx08[4, HostSemaphore])
  LoopCount = 100;
  do {
    // Set HostSemaphore
    CommonFunctionPtr->MmioOr8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x0A00 + 0x08), BIT4);
    CommonFunctionPtr->IoRead8(0xed);    // 0xed IO Delay
    CommonFunctionPtr->IoRead8(0xed);    // 0xed IO Delay
    LoopCount--;
  } while (LoopCount > 0 &&
           0 == (CommonFunctionPtr->MmioRead8 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x0A00 + 0x08)) & BIT4));

  // Make sure SMBUS port PMx00[20:19, SmBus0Sel] is 0.
  LoopCount = 100;
  while (LoopCount > 0 &&
         0 != (CommonFunctionPtr->MmioRead32 ((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x0300 + 0x00)) & (BIT19 + BIT20))) {
    CommonFunctionPtr->MmioAnd32((UINT32)(MainTablePtr->AcpiMemIoBaseAddr + 0x0300 + 0x00), ~(UINT32) (BIT19 + BIT20));
    CommonFunctionPtr->IoRead8(0xed);    // 0xed IO Delay
    LoopCount--;
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * Detect PCIe Devices Automatically
 *
 * This function patches PCIe Topology Override Table by detecting PCIe devices
 * automatically.
 *
 * @param[in]     AmdCpmTablePpi                Pointer to AMD CPM Table PPI
 * @param[in]     DxioTopologyTablePtr          Pointer to Dxio Topology Table
 * @param[in]     AmdPbsConfiguration           Pointer to the structure of AMD_PBS_SETUP_OPTION
 * @param[out]    TravisStatus                  Current Travis Status
 * @param[in]     BoardId                       Current Board ID
 *
 */
VOID
DetectPcieDevices (
  IN       AMD_CPM_TABLE_PPI            *AmdCpmTablePpi,
  IN       AMD_CPM_DXIO_TOPOLOGY_TABLE  *DxioTopologyTablePtr,
  IN       AMD_PBS_SETUP_OPTION         *AmdPbsConfiguration,
  IN OUT   UINT8                        *TravisStatus,
  IN       UINT16                       BoardId
  )
{
  DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-End\n"));
}


/*----------------------------------------------------------------------------------------*/
/**
 * Update GPIO Device Config Table
 *
 * @param[in]     GpioDeviceConfigTablePtr  Pointer to GPIO Device Config Table
 * @param[in]     DeviceId                  Device Id to update
 * @param[in]     Mode                      Value. 0: Disable. 1: Enable
 *
 */
VOID
SetDevice (
  IN       AMD_CPM_GPIO_DEVICE_CONFIG_TABLE     *GpioDeviceConfigTablePtr,
  IN       UINT8                                DeviceId,
  IN       UINT8                                Mode
  )
{
  UINT8   Index;
  UINT8   GpioDeviceId;
  for (Index = 0; Index < AMD_GPIO_DEVICE_SIZE; Index ++) {
    GpioDeviceId = GpioDeviceConfigTablePtr->DeviceList[Index].DeviceId;
    if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
      break;
    }
    if (GpioDeviceId == DeviceId) {
      GpioDeviceConfigTablePtr->DeviceList[Index].Config.Setting.Enable = Mode;
      break;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * 0 = RV1 single source
 * 1 = RV2 single source
 * 2 = RV1  B4 Dual source
 * 3 = RV2 dual source
 * 
 * FALSE - Rv2
 * TRUE - Rv
 */
BOOLEAN
CheckRvOpn (
  )
{
  UINT32        TempData32;

  TempData32 =  (PcdGet32 (PcdGetRVFamilyOPN) >> 30) & 0x3;

  if (TempData32 == 1) {
    return FALSE;
  } else if (TempData32 == 3) {
    return FALSE;
  }
  return TRUE;
}

//<Embedded_Override_Start>    
/* -----------------------------------------------------------------------------*/
/**
 *
 *  CpmGetOPNNameString
 *
 *  @param[in]  OPNString     OPNString Pointer
 *
 *  Description:
 *    Gets the OPN part String .
 *
 *  @retval VOID
 *
 */
VOID CpmGetOPNNameString( AMD_CPM_TABLE_PPI *AmdCpmTablePpi, CHAR8 *OPNString )
{
    UINT32              RegisterData;

    if(OPNString == NULL)
        return;
    
    RegisterData = AmdCpmTablePpi->CommonFunction.SmnRead32  (AmdCpmTablePpi, 0, 0, 0, SMUFUSEx000005A0_ADDRESS, 0);
    
    //OPN string is present in the offsets 5-11,12-18,19-25,26-31
    
    OPNString[0] = (RegisterData >> 5)&0x7F;
    OPNString[1] = (RegisterData >> 12)&0x7F;
    OPNString[2] = (RegisterData >> 19)&0x7F;
    OPNString[3] = (RegisterData >> 26)&0x7F;
    
    RegisterData = AmdCpmTablePpi->CommonFunction.SmnRead32  (AmdCpmTablePpi, 0, 0, 0, SMUFUSEx000005A4_ADDRESS, 0);
    //OPN Contunuity string is present in the offsets 1-7,8-15
    OPNString[4] = (RegisterData >> 1)&0x7F;
    OPNString[5] = (RegisterData >> 8)&0x7F;
    
    IDS_HDT_CONSOLE (MAIN_FLOW, "\nOPN Name String:%c%c%c%c%c%c\n", OPNString[0],OPNString[1],OPNString[2],OPNString[3],OPNString[4],OPNString[5]);

}
//<Embedded_Override_End>
/**
 *
 * This function updates the CLK  as per Bilby rev A board design
 *
 */

VOID
EFIAPI
RevADxioTableClkTableOverride (
  AMD_CPM_DXIO_TOPOLOGY_TABLE       *DxioTopologyTablePtr,
  AMD_CPM_PCIE_CLOCK_TABLE          *PcieClockTablePtr
  )
{

  DXIO_PORT_DESCRIPTOR              *DxioPort;

  //DXIO Table init
  DxioPort = &(DxioTopologyTablePtr->Port[0]);

  DxioPort[0].Port.ClkReq = CLK_REQ6; //Clk Req for PCIe x8 GFX SLOT
  DxioPort[2].Port.ClkReq = CLK_REQ5; //Clk Req for PCIe M.2  SLOT (x2)
  DxioPort[3].Port.ClkReq = CLK_REQ5; //Clk Req for PCIe M.2  SLOT (x4)

  //CLK

  if (PcieClockTablePtr) {
    DEBUG((DEBUG_INFO, "RevADxioTableClkTableOverride done \n"));
    PcieClockTablePtr->Item[0].ClkId = GPP_CLK6; //Clk entry for PCIe x8 GFX SLOT
    PcieClockTablePtr->Item[0].ClkReq = CLK_REQ6;
    PcieClockTablePtr->Item[2].ClkId = GPP_CLK5; //Clk entry for PCIe x4 M.2 SSD SLOT
    PcieClockTablePtr->Item[2].ClkReq = CLK_REQ5;
  }

}

/**
 *
 * This function updates the GPIO Table as per Bilby rev A board design
 *
 */
VOID
EFIAPI
RevAGpioOverride (
  AMD_CPM_GPIO_INIT_TABLE           *GpioInitTablePtr
  )
{
  UINT16 Value = 0x0,Index = 0;

  DEBUG((DEBUG_INFO, "Rev A GPIO programming \n"));

  for (Index = 0;GpioInitTablePtr->GpioList[Index].Pin != 0xFF;Index++) {
    switch (GpioInitTablePtr->GpioList[Index].Pin) {
      case AGPIO116:
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_1, GPIO_INPUT, GPIO_PU_EN, GPIO_STICKY_DIS);
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        break;
      case EGPIO120:
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_1,  GPIO_INPUT, GPIO_PU_PD_DIS, GPIO_STICKY_DIS);
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        break;
      case EGPIO121:
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_0,  GPIO_INPUT, GPIO_PD_EN,     GPIO_STICKY_DIS);
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        break;
      case EGPIO131:
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_3,  GPIO_INPUT, GPIO_PU_EN,     GPIO_STICKY_DIS);
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        break;
    }
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 * CPM Override Function After AMD CPM Table PPI
 *
 * This function updates CPM OEM Tables according to setup options or the value to be detected
 * on run time after AMD CPM Table PPI is installed.
 *
 * @param[in]     PeiServices    Pointer to Pei Services
 *
 * @retval        EFI_SUCCESS    Function initialized successfully
 * @retval        EFI_ERROR      Function failed (see error for more details)
 *
 */
EFI_STATUS
EFIAPI
AmdCpmTableOverride (
  IN       EFI_PEI_SERVICES       **PeiServices
  )
{
  EFI_STATUS                        Status;

  AMD_CPM_TABLE_PPI                 *AmdCpmTablePpi;
  AMD_CPM_MAIN_TABLE                *MainTablePtr;
  AMD_CPM_PCIE_CLOCK_TABLE          *PcieClockTablePtr;
  AMD_CPM_DXIO_TOPOLOGY_TABLE       *DxioTopologyTablePtr;
  AMD_CPM_GPIO_DEVICE_CONFIG_TABLE  *GpioDeviceConfigTablePtr;
  AMD_CPM_OTHER_HOTPLUG_CARD_TABLE  *DtHotplugTablePtr;
  AMD_CPM_GPIO_DEVICE_POWER_TABLE   *PowerTablePtr;
  AMD_PBS_SETUP_OPTION              AmdPbsConfiguration;
  AMD_CPM_GPIO_INIT_TABLE           *GpioInitTablePtr;

  UINTN                             Index;
  UINT16                            BoardId;
  UINT8                             TravisStatus;
  DXIO_PORT_DESCRIPTOR              *DxioPort;
  UINT32                            DeviceEnableMap;
  UINT16                            OriginalBoardId;
  BOOLEAN                           Tambourine;
  UINT32                            *TableAddress;
  DDI_DESCRIPTOR                    *DdiPort;
  //UINT8                             Value8;
  //UINT8                             Offset;
  UINT16                            Value;

  ATOM_14NM_DPPHY_DP_SETTING        *DpPtr;
  ATOM_14NM_DPPHY_DP_SETTING        *TempDpPtr;  
  UINT32                            Count;
  UINT32                            Value32;
  CHAR8 OPNNameString[10] = {0};

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Start\n"));
  Index = 0;
  TravisStatus = 0;

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LocatePpi-gAmdCpmTablePpiGuid\n"));
  Status = (*PeiServices)->LocatePpi (
                           PeiServices,
                           &gAmdCpmTablePpiGuid,
                           0,
                           NULL,
                           (VOID**)&AmdCpmTablePpi
                           );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-End-1-Status=%r\n", Status));
    return Status;
  }

  CpmGetOPNNameString(AmdCpmTablePpi, OPNNameString);

  MainTablePtr = AmdCpmTablePpi->MainTablePtr;
  //Get Board ID (RevA/B)
  BoardId = PcdGet16 (CurrentPlatformId);
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-BoardId=%04X\n", BoardId));

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-AmdCpmOemSetupOption\n"));
  Status = GetAmdPbsConfiguration (&AmdPbsConfiguration);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-End-2-Status=%r\n", Status));
    return Status;
  }

  PcdSet8(PcdSdConfig, AmdPbsConfiguration.FchSdConfig);

  OriginalBoardId = PcdGet16 (OriginalPlatformId);
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-OriginalBoardId=%04X\n", OriginalBoardId));

  if (OriginalBoardId & BIT2) { // OriginalBoardId BIT2 = 1 is Tambourine
    Tambourine = 1 ;
    DEBUG((DEBUG_INFO, "Tambourine Board\n"));
  } else{
    Tambourine = 0 ;
    DEBUG((DEBUG_INFO, "Bilby Board\n"));
  }

  DxioTopologyTablePtr      = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_DXIO_TOPOLOGY);
  PcieClockTablePtr         = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_PCIE_CLOCK);
  GpioDeviceConfigTablePtr  = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GPIO_DEVICE_CONFIG);
  DtHotplugTablePtr         = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD);
  PowerTablePtr             = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GPIO_DEVICE_POWER);
  GpioInitTablePtr          = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GPIO_INIT);


  if(PcdGet8 (PcdBoardRevision)== REV_A_BOARD) {
    DEBUG((DEBUG_INFO, "Bilby Rev A board Programming\n"));
    RevAGpioOverride(GpioInitTablePtr);
    RevADxioTableClkTableOverride(DxioTopologyTablePtr,PcieClockTablePtr);
  }

  if (AmdPbsConfiguration.AmdBlinkLed >= 2) {
    if (GpioInitTablePtr) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Set Blink pin as GPIO\n"));
      Index = 0;
      while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
        if (GpioInitTablePtr->GpioList[Index].Pin == 11) {
          GpioInitTablePtr->GpioList[Index].Setting.Raw = 0x880 + (AmdPbsConfiguration.AmdBlinkLed - 2);  // Set GPIO_FUNCTION_0 + GPIO_OUTPUT_LOW/HIGH
        }
        Index++;
      }
    }
  } else if (AmdPbsConfiguration.AmdBlinkLed == 1) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Turn on Blink Led\n"));
    Value32 = AmdCpmTablePpi->CommonFunction.MmioRead32 (MainTablePtr->AcpiMemIoBaseAddr + 0x0300 + 0xE4);
    Value32 &= ~(UINT32)(BIT1 + BIT0);
    Value32 |= (UINT32)(BIT1 + BIT0);
    AmdCpmTablePpi->CommonFunction.MmioWrite32 (MainTablePtr->AcpiMemIoBaseAddr + 0x0300 + 0xE4, Value32);
  }
  PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 132000);  // mA
  PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
  PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);   // mA
  PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
  DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Bilby\n"));

  DeviceEnableMap = PcdGet32(FchRTDeviceEnableMap);
  if ((FixedPcdGet8 (PcdFchUartPort) == 0) || (PcdGet64 (PcdSerialRegisterBase) == 0xFEDC9000) || (PcdGet64 (PcdAmdIdsDebugPrintSerialPort) == 0xFEDC9000)) {
    DeviceEnableMap |= BIT11;
    PcdSet32(FchRTDeviceEnableMap, DeviceEnableMap);
  }

  if (GpioInitTablePtr && ((DeviceEnableMap & (UINT32) BIT11) == BIT11)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (GpioInitTablePtr & DeviceEnableMap BIT11=1)\n"));
    Index = 0;
    while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
      if (GpioInitTablePtr->GpioList[Index].Pin >= 135 && GpioInitTablePtr->GpioList[Index].Pin <= 139) {
        // GPIO_DEF_V2 (0, 0, 135, GPIO_FUNCTION_0, GPIO_NA, GPIO_PU_PD_DIS), // Set to UART0_CTS_L
        // GPIO_DEF_V2 (0, 0, 136, GPIO_FUNCTION_0, GPIO_NA, GPIO_PU_PD_DIS), // Set to UART0_RXD
        // GPIO_DEF_V2 (0, 0, 137, GPIO_FUNCTION_0, GPIO_NA, GPIO_PU_PD_DIS), // Set to UART0_RTS_L
        // GPIO_DEF_V2 (0, 0, 138, GPIO_FUNCTION_0, GPIO_NA, GPIO_PU_PD_DIS), // Set to UART0_TXD
        // GPIO_DEF_V2 (0, 0, 139, GPIO_FUNCTION_0, GPIO_NA, GPIO_PU_PD_DIS), // Set to UART0_INTR
        GpioInitTablePtr->GpioList[Index].Setting.Raw = 0x888;
      }
      Index++;
    }
  }

  // Display Features
  MainTablePtr->DisplayFeature.Config.D3ColdSupport = (AmdPbsConfiguration.SpecialVgaFeature == 4) ? 1 : 0;
  MainTablePtr->DisplayFeature.Config.HybridGraphicsSupport = (AmdPbsConfiguration.SpecialVgaFeature == 4) ? 1 : 0;
  MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX = (AmdPbsConfiguration.DgpuAudio == 0) ? 1 : 0;

  if (AmdPbsConfiguration.NonEvalDgpuSupport) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (NonEvalDgpuSupport)\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Set NonEvalDgpuSupport to 1\n"));
    MainTablePtr->DisplayFeature.Config.NonEvalDgpuSupport = 1;
    if (PowerTablePtr) {
      Index = 0;
      while (PowerTablePtr->DevicePowerList[Index].DeviceId != 0xFF) {
        if (PowerTablePtr->DevicePowerList[Index].DeviceId == DEVICE_ID_MXM && PowerTablePtr->DevicePowerList[Index].Mode == CPM_POWER_ON && PowerTablePtr->DevicePowerList[Index].Type == CPM_POWER_WAIT) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-(Item[%X].DeviceId == DEVICE_ID_MXM & CPM_POWER_ON & CPM_POWER_WAIT)\n", Index));
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Use delay 100ms instead of wait EVAL_PWRGD to high\n"));
          PowerTablePtr->DevicePowerList[Index].Type = CPM_POWER_DELAY;
          PowerTablePtr->DevicePowerList[Index].Config.Stall = 100000;
        }
        Index++;
      }
    }
  }
  MainTablePtr->KbcSupport = AmdPbsConfiguration.KbcSupport;

  if ((AmdPbsConfiguration.PrimaryVideoAdaptor == 2)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (PrimaryVideoAdaptor == 2)\n"));
    MainTablePtr->DisplayFeature.Config.IsDgpuPrimary = 1;
  }
  
  if(AmdPbsConfiguration.DisplaySelect1 == 0)  // 0 => HDMI , 1 => DP (Default)
  {
    Index = 0;
    while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
      if (GpioInitTablePtr->GpioList[Index].Pin == 31) {
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_2,  GPIO_OUTPUT_LOW, GPIO_PD_EN,     GPIO_STICKY_DIS);
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride- DisplaySelect1 GPIO31 set to low value = %d \n", Value));
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        break;
      }
      Index++;
    }

    DdiPort = &(DxioTopologyTablePtr->Ddi[0]);	
    DdiPort[0].Ddi.ConnectorType = ConnectorTypeHDMI;
    DdiPort[0].Ddi.Flags |= EXT_DISPLAY_PATH_CAPS_HDMI20_TISN65DP159RSBT;    
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride    DisplaySelect1 selected HDMI \n"));

    if(CheckRvOpn()) {
      TableAddress = (UINT32 *)&Hdmi0RetimerRedriverV1000[0];
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcdCfgDp0RetimerRedriverTable-TableAddress = %x\n", TableAddress));
      PcdSet32 (PcdCfgDp0RetimerRedriverTable, (UINT32)TableAddress);	
    } else {
      TableAddress = (UINT32 *)&Hdmi0RetimerRedriverR1000[0];
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcdCfgDp0RetimerRedriverTable-TableAddress = %x\n", TableAddress));
      PcdSet32 (PcdCfgDp0RetimerRedriverTable, (UINT32)TableAddress);
    }
  }
  if(AmdPbsConfiguration.DisplaySelect2 == 0) // 0 => HDMI , 1 => DP (Default)
  {
    Index = 0; 
    while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
      if (GpioInitTablePtr->GpioList[Index].Pin == 29) {
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_1,  GPIO_OUTPUT_LOW, GPIO_PD_EN,     GPIO_STICKY_DIS);
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride- DisplaySelect1 GPIO29 set to low value = %d \n", Value));
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        break;
      }
      Index++;	  
    }

    DdiPort = &(DxioTopologyTablePtr->Ddi[0]);	
    DdiPort[1].Ddi.ConnectorType = ConnectorTypeHDMI;
    DdiPort[1].Ddi.Flags |= EXT_DISPLAY_PATH_CAPS_HDMI20_TISN65DP159RSBT;    
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride   DisplaySelect2 selected HDMI \n"));

    if(CheckRvOpn()) {
      TableAddress = (UINT32 *)&Hdmi1RetimerRedriverV1000[0];
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcdCfgDp1RetimerRedriverTable-TableAddress = %x\n", TableAddress));
      PcdSet32 (PcdCfgDp1RetimerRedriverTable, (UINT32)TableAddress);	
    } else {
      TableAddress = (UINT32 *)&Hdmi1RetimerRedriverR1000[0];
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcdCfgDp1RetimerRedriverTable-TableAddress = %x\n", TableAddress));
      PcdSet32 (PcdCfgDp1RetimerRedriverTable, (UINT32)TableAddress);
    }
  }
    
  
#ifdef CONNECTED_STANDBY_SUPPORT
  // Modern Standby Support
  MainTablePtr->ModernStandbyEn	= AmdPbsConfiguration.ModernStandbyEn;

  if (AmdPbsConfiguration.ModernStandbyEn == 1) {
    PcdSetBool(PcdConnectStandbyEnable, 1);
  } else {
    PcdSetBool(PcdConnectStandbyEnable, 0);
  }
#endif


  
  // Clock control
  MainTablePtr->UnusedGppClkOffEn = AmdPbsConfiguration.UnusedGppClkOff;

  DxioPort = &(DxioTopologyTablePtr->Port[0]);

  DEBUG((-1,"ray_trace::DxioPort[0].EngineData.StartLane = 0x%X\n",DxioPort[0].EngineData.StartLane));
  //RV2 workaround
  if (BoardId >= 0x0008) {
    DEBUG((DEBUG_INFO, "Apply RV2 workaround\n"));
    PcdSet8 (PcdPsppPolicy, 0);
  }  
  
  //Update Dxio Table for R2312 OPN.
  if (!AsciiStrCmp(OPNNameString, R2K_OPN_R2312)) {
    DxioPort[0].EngineData.StartLane = 11;
    DxioPort[0].EngineData.EndLane = 8;

    DxioPort[1].EngineData.StartLane = 4;
    DxioPort[1].EngineData.EndLane = 5;

    DxioPort[2].EngineData.StartLane = 0;
    DxioPort[2].EngineData.EndLane = 1;

    DxioPort[3].EngineData.StartLane = 2;
    DxioPort[3].EngineData.EndLane = 3;

    //Disable DDI 2 
    DdiPort = &(DxioTopologyTablePtr->Ddi[0]);
    DdiPort[2].Ddi.ConnectorType = UnusedType;
    DEBUG((DEBUG_INFO, "R2312 OPN override updated\n"));
  }

  // 
  //  GPIO42    GPIO89	10G-XGbe  NVMe SSD   M.2 Sata   iSata-R1000  iSata-V1000
  //    1        0		yes       No         No			Yes   			No       ( XGBE with x2NvMe on V1000 only)			
  //    0        1		No        No         Yes        Yes  			No		 ( No settings Exposed)	
  //    1        1      yes       No         Yes        Yes 			Yes		 ( XGBe and M.2 )	
  //    0        0      No        Yes        Np         Yes 			No       ( Select PCIeX2 or PCIe X4)
  //    
  if ((AmdPbsConfiguration.XgbeVsPcieXn == 1) || (AmdPbsConfiguration.XgbeVsPcieXn == 2)) { // 0 => XGBE (default) , 1 => PCIeX2 , 2  => PCIeX4 , 3 = XGBE X2 and Pciex2
    Index = 0x0;
    while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
      if (GpioInitTablePtr->GpioList[Index].Pin == 42) {
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_0, GPIO_OUTPUT_LOW, GPIO_PU_EN, GPIO_STICKY_DIS);
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride- XGBE to PCIE X2 Value = %x\n", Value));
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        if(AmdPbsConfiguration.XgbeVsPcieXn == 1) {        
            DxioPort[2].EngineData.EngineType = DxioPcieEngine;   //Entry 2 Enable M.2 NVME X2
            DxioPort[3].Port.PortPresent = DxioPortDisabled;
        } else{
            DxioPort[3].EngineData.EngineType = DxioPcieEngine;   //Entry 3 Enable M.2 NVME X4
            DxioPort[2].Port.PortPresent = DxioPortDisabled;
        }
        // Disable isata entry (Phy3) to enable NvMe - only for RV1 Silicon(v1000) . 
        if(CheckRvOpn()){ 
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride- V1000 iSata Disabled \n"));
          DxioPort[4].EngineData.EngineType = DxioUnusedEngine; // Entry 4 is iSata
          DxioPort[4].Port.PortPresent = DxioPortDisabled;
        }
        DxioPort[6].EngineData.EngineType = DxioUnusedEngine; //Entry 6 is XGBE
        DxioPort[6].Port.PortPresent = DxioPortDisabled;
        DxioPort[7].EngineData.EngineType = DxioUnusedEngine; // Entry 7 is XGBE
        DxioPort[7].Port.PortPresent = DxioPortDisabled;
        PcdSetBool (PcdXgbePort0ConfigEn,0); 
        PcdSetBool (PcdXgbePort1ConfigEn,0);
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride XGBE disabled\n"));
      }
      if (GpioInitTablePtr->GpioList[Index].Pin == 89) {
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_2, GPIO_OUTPUT_LOW, GPIO_PD_EN, GPIO_STICKY_DIS);
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride GPIO 89  Value = %x\n", Value));
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
        DxioPort[5].EngineData.EngineType = DxioUnusedEngine; // Entry 5 is M.2 Sata
        DxioPort[5].Port.PortPresent      = DxioPortDisabled;
      }
      Index++;
    }  
  } else {
      if ((AmdPbsConfiguration.XgbeVsPcieXn == 3)&&(CheckRvOpn())) {
        DEBUG((DEBUG_INFO, "Programming to Enable XGBE(Phy0,Phy1) and x2 NVME(Phy2,Phy3) on V1000 only\n"));
        //Enable Pcie Lane Phy2 and Phy3 as NvMe 
        DxioPort[2].EngineData.EngineType = DxioPcieEngine;   //Entry 2 Enable M.2 x2 NVME
        DxioPort[3].Port.PortPresent = DxioPortDisabled;
    
        //Disable the Pcie Lane  Phy3 as Sata Engine because NvMe is enabled
        DxioPort[4].EngineData.EngineType = DxioUnusedEngine; // Entry 4 is iSata
        DxioPort[4].Port.PortPresent = DxioPortDisabled;
    
        DxioPort[5].EngineData.EngineType = DxioUnusedEngine; // Entry 5 is M.2 Sata
        DxioPort[5].Port.PortPresent      = DxioPortDisabled;	
        Index =0;
        while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
          if (GpioInitTablePtr->GpioList[Index].Pin == 89) {
            Value = GPIO_CONTROL_REG(GPIO_FUNCTION_2, GPIO_OUTPUT_LOW, GPIO_PD_EN, GPIO_STICKY_DIS);
            DEBUG((DEBUG_INFO, "Setting GPIO 89 to Low to enable x2  NVME\n"));
            GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
            break;
          }
          Index++;
        }
      }
      if(!PcdGet8(PcdXgbeDisable)) {
        ConfigureEthernetDxioPorts (&DxioPort, AmdPbsConfiguration.XgbePortPhySwitch);
        UpdateXgbeFchPcds(PeiServices, &DxioPort);
        }
        else{
          DxioPort[6].EngineData.EngineType = DxioUnusedEngine; //Entry 6 is XGBE
          DxioPort[6].Port.PortPresent = DxioPortDisabled;
          DxioPort[7].EngineData.EngineType = DxioUnusedEngine; // Entry 7 is XGBE
          DxioPort[7].Port.PortPresent = DxioPortDisabled;
          PcdSetBool (PcdXgbePort0ConfigEn,0); 
          PcdSetBool (PcdXgbePort1ConfigEn,0);
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride default XGBE disabled\n"));
        }
  }

  //AGPIO86 High for LPC and Low for eMMC & SD (Need reworks for SD) . Default High selected in CpmOemTable
  if (PcdGet8(PcdEmmcEnable) != 0) { //Default PcdEmmcEnable as disabled.
    Index = 0;
    while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
      if (GpioInitTablePtr->GpioList[Index].Pin == 86) {
        PcdSet8 (PcdIoPort80LpcDecodeEn, 0x0);
        Value = GPIO_CONTROL_REG(GPIO_FUNCTION_1, GPIO_OUTPUT_LOW, GPIO_PD_EN, GPIO_STICKY_DIS);
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride eMMC selected Value = %x\n", Value));
        GpioInitTablePtr->GpioList[Index].Setting.Raw = Value;
      }  
      Index++;
    } 
  }
 
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DetectPcieDevices\n"));
  DetectPcieDevices (AmdCpmTablePpi, DxioTopologyTablePtr, &AmdPbsConfiguration, &TravisStatus, BoardId);

  if (AmdPbsConfiguration.EvalAutoDetection) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (EvalAutoDetection)\n"));
    if (PowerTablePtr) {
      Index = 0;
      while (PowerTablePtr->DevicePowerList[Index].DeviceId != 0xFF) {
        if (PowerTablePtr->DevicePowerList[Index].DeviceId == DEVICE_ID_MXM && PowerTablePtr->DevicePowerList[Index].Mode == CPM_POWER_OFF) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-(Item[%X].DeviceId == DEVICE_ID_MXM & CPM_POWER_OFF)\n", Index));
          PowerTablePtr->DevicePowerList[Index].InitFlag = GPIO_DEVICE_INIT_STAGE_1;
        }
        Index++;
      }
    }
  }


  if (PcieClockTablePtr) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (PcieClockTablePtr)\n"));
    if (!AmdPbsConfiguration.ClockRequest2) {
      // DEVICE_ID_SSD ClockRequest2 is disabled - Clear SlotCheck BIT2 - Don't check Clock Power Management
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest2 (DEVICE_ID_SSD) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK2) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK2, Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2 BIT3\n", Index));
          PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
        }
        Index++;
      }
    }
    if (!AmdPbsConfiguration.ClockRequest3) {
      // DEVICE_ID_WIFI ClockRequest3 is disabled - Clear SlotCheck BIT2 - Don't check Clock Power Management
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest3 (DEVICE_ID_WIFI) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK3) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK3, Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2 BIT3\n", Index));
          PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
        }
        Index++;
      }
    }
    if (!AmdPbsConfiguration.ClockRequest4) {
      // DEVICE_ID_DT ClockRequest4 is disabled
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest4 (DEVICE_ID_DT) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK4) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK4\n", Index));
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl > 0-Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2 BIT3\n"));
          PcieClockTablePtr->Item[Index].ClkReq = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
        }
        Index++;
      }
    }

    if (!AmdPbsConfiguration.ClockRequest5) {
      // DEVICE_ID_SSD ClockRequest5 is disabled - Clear SlotCheck BIT2 - Don't check Clock Power Management
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest5 (DEVICE_ID_SSD) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK5) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK5, Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2\n", Index));
          PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
        }
        Index++;
      }
    }
    if (!AmdPbsConfiguration.ClockRequest6) {
      // DEVICE_ID_MXM ClockRequest6 is disabled - Clear SlotCheck BIT2 - Don't check Clock Power Management
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest6 (DEVICE_ID_MXM) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK6) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK6, Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2\n", Index));
          PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
        }
        Index++;
      }
    }
    Index = 0;
    while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
      DEBUG((DEBUG_INFO, "  Item[%X] Socket=%02X Die=%02X Bridge=%02X Miscid=%02X", Index, \
            (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 24) & 0xF, (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 20) & 0xF, \
            (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 16) & 0xF, (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 28) & 0xF));
      DEBUG((DEBUG_INFO, " ClkId=%02X ClkReq=%02X ClkIdExt=%02X ClkReqExt=%02X DeviceId=%02X", \
            PcieClockTablePtr->Item[Index].ClkId,    PcieClockTablePtr->Item[Index].ClkReq, \
            PcieClockTablePtr->Item[Index].ClkIdExt, PcieClockTablePtr->Item[Index].ClkReqExt, PcieClockTablePtr->Item[Index].DeviceId));
      DEBUG((DEBUG_INFO, " Device=%02X Function=%02X SlotCheck=%02X SpecialFunctionId=%04X\n", \
            PcieClockTablePtr->Item[Index].Device,     PcieClockTablePtr->Item[Index].Function, \
            PcieClockTablePtr->Item[Index].SlotCheck, (PcieClockTablePtr->Item[Index].SpecialFunctionId & 0xFFFF)));
      Index++;
    }
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Final-PcieClockTable\n"));
  }

  if (AmdPbsConfiguration.VDDP == 1) {
    DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage = 0.8V - Drive GPIO12 to high \n"));
    Index = 0;
    while (GpioInitTablePtr->GpioList[Index].Pin != 0xFF) {
      if (GpioInitTablePtr->GpioList[Index].Pin == 12) {
        GpioInitTablePtr->GpioList[Index].Setting.Gpio.Out = GPIO_OUTPUT_HIGH;
        break;
      }
      Index++;
    }
  }

  TableAddress = &AzaliaCodecVerbTable[0];
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcdCfgAzaliaCodecVerbTable-TableAddress = %x\n", TableAddress));
  PcdSet32 (PcdCfgAzaliaCodecVerbTable, (UINT32)TableAddress);

  //DP registers tunning
  //
  if (CheckRvOpn() == FALSE) {
    Status = (**PeiServices).AllocatePool (
                PeiServices,
                sizeof (ATOM_14NM_DPPHY_DP_SETTING) * 10,
                &DpPtr
                );
     
    if (!EFI_ERROR (Status)) {
      TempDpPtr = DpPtr;
  
      //HBR3
      PcdSet8  (PcdAmdDpHbr3PhySel, 0xF);
      PcdSet8  (PcdAmdDpHbr3Version, 0x0);
      PcdSet16 (PcdAmdDpHbr3TableSize, 0x5);
  
      Count = 0;
      ///0
      TempDpPtr[Count].dp_vs_pemph_level = 0x2;
      TempDpPtr[Count].margindeemph = 0x0019;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///1
      TempDpPtr[Count].dp_vs_pemph_level = 0x08;
      TempDpPtr[Count].margindeemph = 0x2934;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///2
      TempDpPtr[Count].dp_vs_pemph_level = 0x09;
      TempDpPtr[Count].margindeemph = 0x291C;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///3
      TempDpPtr[Count].dp_vs_pemph_level = 0x10;
      TempDpPtr[Count].margindeemph = 0x4214;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;

      ///4
      TempDpPtr[Count].dp_vs_pemph_level = 0x18;
      TempDpPtr[Count].margindeemph = 0x4C00;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x9F;
      Count++;
  
      for (Index = Count; Index < 10; Index++) {
    	TempDpPtr[Index].dp_vs_pemph_level = 0xFF;
    	TempDpPtr[Index].margindeemph = 0;
    	TempDpPtr[Index].deemph_6db_4 = 0;
    	TempDpPtr[Index].boostadj = 0;
      }
    }
  
    PcdSet32 (PcdAtomDpHbr3PhyDpSetting, (UINT32)(UINTN)&DpPtr[0]);
    PcdSet16 (PcdAmdDpPhyOverride, ATOM_ENABLE_DP_HBR3_TUNINGSET);
  }	
  
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-End-3-Status=%r\n", Status));
  return Status;
}

EFI_STATUS
EFIAPI
ConfigureEthernetDxioPorts (
  IN DXIO_PORT_DESCRIPTOR** DxioPort,
  IN UINT8 PhyMode
  )
{
  DXIO_PORT_DESCRIPTOR* DxioPortList = (*DxioPort);
  AMD_PBS_SETUP_OPTION              AmdPbsConfiguration;
  EFI_STATUS                        Status;
  DEBUG((DEBUG_INFO, "In ConfigureEthernetDxioPorts\n"));

  if (DxioPortList == NULL) {
    DEBUG((DEBUG_INFO, "ConfigureEthernetDxioPorts, Invalid Port List\n"));
    return EFI_INVALID_PARAMETER;
  }
  Status = GetAmdPbsConfiguration (&AmdPbsConfiguration);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-ConfigureEthernetDxioPorts-Status=%r\n", Status));
    return Status;
  }
  while(1) {
    if((DxioPortList->EngineData.EngineType == DxioEthernetEngine)) {
      DEBUG((DEBUG_INFO, "ConfigureEthernetDxioPorts, found DxioEthernetEngine\n"));
      if (PhyMode == XGBE_PHY_MODE_RJ45 || PhyMode == XGBE_PHY_MODE_BACKPLANE) {
        DxioPortList->EtherNet.PadMux1                = 0x0;
        DxioPortList->EtherNet.EthPortProp0.MdioId   = 0;
        DxioPortList->EtherNet.EthPortProp0.PlatConf  = XGBE_10G_1G_BACKPLANE;
        DxioPortList->EtherNet.EthPortProp0.ConnType  = XGBE_BACKPLANE_CONNECTION;
        DxioPortList->EtherNet.EthPortProp0.SuppSpeed = (XGBE_PORT_SPEED_10G | XGBE_PORT_SPEED_1G | XGBE_PORT_SPEED_100M);
        DxioPortList->EtherNet.PadMux0 = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0x10 : 0x20;
        if (PhyMode == XGBE_PHY_MODE_RJ45) {
          PcdSetBool(PcdXgbeMdio0, TRUE);
          PcdSetBool(PcdXgbeMdio1, TRUE);
        } else {
          PcdSetBool(PcdXgbeMdio0, FALSE);
          PcdSetBool(PcdXgbeMdio1, FALSE);
        }
        PcdSetBool(PcdXgbeSfp,   FALSE);
        DxioPortList->EtherNet.PadMux1                  = 0;
        DxioPortList->EtherNet.EthPortProp3.Rs          = 0;
        DxioPortList->EtherNet.EthPortProp4.SfpMux      = 0;
        DxioPortList->EtherNet.EthPortTxEq.TxEqPre      = 0;
        DxioPortList->EtherNet.EthPortTxEq.TxEqMain     = 0;
        DxioPortList->EtherNet.EthPortTxEq.TxEqPost     = 0;
        DxioPortList->EtherNet.EthPortProp3.SfpGpioMask = 0;
        DxioPortList->EtherNet.EthPortProp3.SfpGpioAdd  = 1;
        DxioPortList->EtherNet.EthPortProp4.SfpMuxUpAdd = 0;
        DxioPortList->EtherNet.EthPortProp4.RedriverAddress = 0;
        DxioPortList->EtherNet.EthPortProp4.RedriverInterface = 0;	
        DxioPortList->EtherNet.EthPortProp4.RedriverLane = 0;		
        DxioPortList->EtherNet.EthPortProp4.RedriverModel = 0;	
        DxioPortList->EtherNet.EthPortProp4.RedriverPresent = 0;		
        DxioPortList->EtherNet.EthPortProp3.TxFault   = 0;
        DxioPortList->EtherNet.EthPortProp3.ModAbs    = 0;
        DxioPortList->EtherNet.EthPortProp3.RxLoss    = 0;
        DxioPortList->EtherNet.EthPortProp4.SfpBusSeg = 0;
        // 0 - 1G , 1 - 10G , 2 - 100Mbps , 3 = 10G/1G/100Mbps
        if (AmdPbsConfiguration.XgbePortSpeedSwitch == 0x1) {
          DxioPortList->EtherNet.EthPortProp0.SuppSpeed = XGBE_PORT_SPEED_10G ;
        }else if (AmdPbsConfiguration.XgbePortSpeedSwitch == 0x2) {
            DxioPortList->EtherNet.EthPortProp0.SuppSpeed = XGBE_PORT_SPEED_100M;
        }else if (AmdPbsConfiguration.XgbePortSpeedSwitch == 0x3) {
            DxioPortList->EtherNet.EthPortProp0.SuppSpeed = (XGBE_PORT_SPEED_10G | XGBE_PORT_SPEED_1G | XGBE_PORT_SPEED_100M);
        }else if (AmdPbsConfiguration.XgbePortSpeedSwitch == 0x0) {
            DxioPortList->EtherNet.EthPortProp0.SuppSpeed = XGBE_PORT_SPEED_1G;
        }else if (AmdPbsConfiguration.XgbePortSpeedSwitch == 0x4) {
            DxioPortList->EtherNet.EthPortProp0.SuppSpeed = XGBE_PORT_SPEED_2_5G;
        }

        if( PhyMode == XGBE_PHY_MODE_BACKPLANE){

           DxioPortList->EtherNet.EthPortProp0.PlatConf = XGBE_10G_1G_BACKPLANE;
           DxioPortList->EtherNet.EthPortProp3.MdioReset = 0;
           DxioPortList->EtherNet.EthPortProp0.ConnType  = XGBE_BACKPLANE_CONNECTION;

           if(  DxioPortList->EtherNet.EthPortProp0.SuppSpeed == XGBE_PORT_SPEED_2_5G)
		  		 DxioPortList->EtherNet.EthPortProp0.PlatConf = XGBE_2_5G_BACKPLANE;    
        }
        else {
            DxioPortList->EtherNet.EthPortProp0.PlatConf = AmdPbsConfiguration.XgbePortRJ45Mode;
            if(DxioPortList->EtherNet.EthPortProp0.PlatConf != XGBE_10G_1G_BACKPLANE){
            DxioPortList->EtherNet.EthPortProp0.ConnType = XGBE_CONNECTION_MDIO_PHY;
            if ((DxioPortList->EtherNet.EthPortProp0.PlatConf == XGBE_SOLDERED_DOWN_1000BASE_T) || (DxioPortList->EtherNet.EthPortProp0.PlatConf == XGBE_SOLDERED_DOWN_NBASE_T))
               DxioPortList->EtherNet.EthPortProp0.SuppSpeed = (XGBE_PORT_SPEED_1G | XGBE_PORT_SPEED_100M);
            }
        }

        DEBUG((DEBUG_INFO, "PlatConf  = %x\n", DxioPortList->EtherNet.EthPortProp0.PlatConf));
        DEBUG((DEBUG_INFO, "ConnType  = %x\n", DxioPortList->EtherNet.EthPortProp0.ConnType));
        DEBUG((DEBUG_INFO, "SuppSpeed = %x\n", DxioPortList->EtherNet.EthPortProp0.SuppSpeed));
        DEBUG((DEBUG_INFO, "PadMux0   = %x\n", DxioPortList->EtherNet.PadMux0));
      } else {
        DxioPortList->EtherNet.PadMux1                  = 0x0;
        DxioPortList->EtherNet.EthPortProp3.Rs          = 0x0;
        DxioPortList->EtherNet.EthPortProp4.SfpMux      = 0x3;   //Lower address of Mux PCA 9545 or 111b if SFP+ directly connected to I2C
        // DxioPortList->EtherNet.EthPortTxEq.TxEqPre      = 0x14;
        // DxioPortList->EtherNet.EthPortTxEq.TxEqMain     = 0x18;
        // DxioPortList->EtherNet.EthPortTxEq.TxEqPost     = 0x2C;
        DxioPortList->EtherNet.EthPortProp3.SfpGpioMask = 0x2;
        DxioPortList->EtherNet.EthPortProp3.SfpGpioAdd  = 0x1;   //Lower I2C address of GPIO Expander PCA9535)
        DxioPortList->EtherNet.EthPortProp4.SfpMuxUpAdd = 0x1C;
        DxioPortList->EtherNet.EthPortProp4.RedriverAddress = 0;
        DxioPortList->EtherNet.EthPortProp4.RedriverInterface = 1;	
        DxioPortList->EtherNet.EthPortProp4.RedriverLane = 0;
        DxioPortList->EtherNet.EthPortProp4.RedriverModel = 0;
        DxioPortList->EtherNet.EthPortProp4.RedriverPresent = 0;
        DxioPortList->EtherNet.EthPortProp0.PlatConf    = XGBE_SFP_PLUS_CONNECTOR;
        DxioPortList->EtherNet.EthPortProp0.ConnType    = XGBE_SFP_PLUS_CONNECTION;
        DxioPortList->EtherNet.EthPortProp0.SuppSpeed   = (XGBE_PORT_SPEED_10G | XGBE_PORT_SPEED_1G | XGBE_PORT_SPEED_100M);

        DxioPortList->EtherNet.EthPortProp3.TxFault   = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0xE : 0x6;
        DxioPortList->EtherNet.EthPortProp3.ModAbs    = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0xC : 0x4;
        DxioPortList->EtherNet.EthPortProp3.RxLoss    = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0xD : 0x5;
        DxioPortList->EtherNet.EthPortProp4.SfpBusSeg = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0x0 : 0x1;
        DxioPortList->EtherNet.PadMux0                = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0x1 : 0x1;       		

        DEBUG((DEBUG_INFO, "PadMux1      = %x\n", DxioPortList->EtherNet.PadMux1));
        DEBUG((DEBUG_INFO, "Rs           = %x\n", DxioPortList->EtherNet.EthPortProp3.Rs));
        DEBUG((DEBUG_INFO, "SfpMux       = %x\n", DxioPortList->EtherNet.EthPortProp4.SfpMux));
        DEBUG((DEBUG_INFO, "TxEqPre      = %x\n", DxioPortList->EtherNet.EthPortTxEq.TxEqPre));
        DEBUG((DEBUG_INFO, "TxEqMain     = %x\n", DxioPortList->EtherNet.EthPortTxEq.TxEqMain));
        DEBUG((DEBUG_INFO, "TxEqPost     = %x\n", DxioPortList->EtherNet.EthPortTxEq.TxEqPost));
        DEBUG((DEBUG_INFO, "SfpGpioMask  = %x\n", DxioPortList->EtherNet.EthPortProp3.SfpGpioMask));
        DEBUG((DEBUG_INFO, "SfpGpioAdd   = %x\n", DxioPortList->EtherNet.EthPortProp3.SfpGpioAdd));
        DEBUG((DEBUG_INFO, "SfpMuxUpAdd  = %x\n", DxioPortList->EtherNet.EthPortProp4.SfpMuxUpAdd));
        DEBUG((DEBUG_INFO, "PlatConf     = %x\n", DxioPortList->EtherNet.EthPortProp0.PlatConf));
        DEBUG((DEBUG_INFO, "ConnType     = %x\n", DxioPortList->EtherNet.EthPortProp0.ConnType));
        DEBUG((DEBUG_INFO, "SuppSpeed    = %x\n", DxioPortList->EtherNet.EthPortProp0.SuppSpeed));
        DEBUG((DEBUG_INFO, "TxFault      = %x\n", DxioPortList->EtherNet.EthPortProp3.TxFault));
        DEBUG((DEBUG_INFO, "ModAbs       = %x\n", DxioPortList->EtherNet.EthPortProp3.ModAbs));
        DEBUG((DEBUG_INFO, "RxLoss       = %x\n", DxioPortList->EtherNet.EthPortProp3.RxLoss));
        DEBUG((DEBUG_INFO, "SfpBusSeg    = %x\n", DxioPortList->EtherNet.EthPortProp4.SfpBusSeg));
        DEBUG((DEBUG_INFO, "PadMux0      = %x\n", DxioPortList->EtherNet.PadMux0));
        PcdSetBool(PcdXgbeSfp,   TRUE);
        PcdSetBool(PcdXgbeMdio0, FALSE);
        PcdSetBool(PcdXgbeMdio1, FALSE);
      }
    }
     
    if((DxioPortList->Flags & DESCRIPTOR_TERMINATE_LIST) == DESCRIPTOR_TERMINATE_LIST) { //condition check to exit the loop
      break;        
    }    
    DxioPortList++;         
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UpdateXgbeFchPcds (
  IN EFI_PEI_SERVICES** PeiServices,
  IN DXIO_PORT_DESCRIPTOR** DxioPort
  )
{
  UINTN PcdBufSize = sizeof(FCH_XGBE_PORT);
  EFI_STATUS Status = EFI_SUCCESS;
  VOID* Buffer  = NULL;
  FCH_XGBE_PORT* Port0 = NULL;
  FCH_XGBE_PORT *Port1 = NULL;
  FCH_XGBE_PORT *PortPtr = NULL;
  DXIO_PORT_DESCRIPTOR* DxioPortList = (*DxioPort);

  DEBUG((DEBUG_INFO, "In UpdateXgbeFchPcds\n"));

  if (DxioPortList == NULL) {
    DEBUG((DEBUG_INFO, "UpdateXgbeFchPcds, Invalid Port List\n"));
    return EFI_INVALID_PARAMETER;
  }

  DEBUG((DEBUG_INFO, "UpdateXgbeFchPcds Port0 = %08X, Port1 = %08X, Len = %x\n", Port0, Port1, sizeof(FCH_XGBE_PORT)));
  while(1) {
    if((DxioPortList->EngineData.EngineType == DxioEthernetEngine)) {
      DEBUG((DEBUG_INFO, "UpdateXgbeFchPcds, found DxioEthernetEngine\n"));
      if (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) {
        Status = (*PeiServices)->AllocatePool (
                                   PeiServices,
                                   sizeof(FCH_XGBE_PORT),
                                   (VOID**)&Port0
                                   );
        if (EFI_ERROR (Status)) {
          DEBUG((DEBUG_INFO, "UpdateXgbeFchPcds AllocatePool failed, Status = %r\n", Status));
          return Status;
        }
        (*PeiServices)->SetMem(Port0, sizeof(FCH_XGBE_PORT), 0x0);
      }

      if (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_1) {
        Status = (*PeiServices)->AllocatePool (
                                   PeiServices,
                                   sizeof(FCH_XGBE_PORT),
                                   (VOID**)&Port1
                                   );
        if (EFI_ERROR (Status)) {
          DEBUG((DEBUG_INFO, "UpdateXgbeFchPcds AllocatePool failed, Status = %r\n", Status));
          return Status;
        }
        (*PeiServices)->SetMem(Port1, sizeof(FCH_XGBE_PORT), 0x0);
      }
      PortPtr = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? Port0 : Port1;
      PortPtr->XgbePortConfig  = 0x1;
      PortPtr->XgbePortPlatformConfig = (UINT8) DxioPortList->EtherNet.EthPortProp0.PlatConf;
      PortPtr->XgbePortSupportedSpeed  = (UINT8) DxioPortList->EtherNet.EthPortProp0.SuppSpeed;
      PortPtr->XgbePortConnectedType  = (UINT8) DxioPortList->EtherNet.EthPortProp0.ConnType;
      PortPtr->XgbePortMdioId         = (UINT8) DxioPortList->EtherNet.EthPortProp0.MdioId;

      DEBUG((DEBUG_INFO, "PortPtr->XgbePortConfig         = %x\n", PortPtr->XgbePortConfig));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortPlatformConfig = %x\n", PortPtr->XgbePortPlatformConfig));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSupportedSpeed = %x\n", PortPtr->XgbePortSupportedSpeed));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortConnectedType  = %x\n", PortPtr->XgbePortConnectedType));

      PortPtr->XgbePortMdioResetType        = (UINT8) DxioPortList->EtherNet.EthPortProp3.MdioReset;
      PortPtr->XgbePortResetGpioNum         = (UINT8) DxioPortList->EtherNet.EthPortProp3.MdioGpioResetNum;
      PortPtr->XgbePortMdioResetI2cAddress  = (UINT8) 0x0;
      PortPtr->XgbePortSfpI2cAddress        = (UINT8) DxioPortList->EtherNet.EthPortProp3.SfpGpioAdd;
      PortPtr->XgbePortSfpTxFaultGpio       = (UINT8) DxioPortList->EtherNet.EthPortProp3.TxFault;
      PortPtr->XgbePortSfpRsGpio            = (UINT8) DxioPortList->EtherNet.EthPortProp3.Rs;
      PortPtr->XgbePortSfpModAbsGpio        = (UINT8) DxioPortList->EtherNet.EthPortProp3.ModAbs;
      PortPtr->XgbePortSfpRxLosGpio         = (UINT8) DxioPortList->EtherNet.EthPortProp3.RxLoss;
      PortPtr->XgbePortSfpGpioMask          = (UINT8) DxioPortList->EtherNet.EthPortProp3.SfpGpioMask;

      DEBUG((DEBUG_INFO, "PortPtr->XgbePortMdioResetType       = %x\n", PortPtr->XgbePortMdioResetType));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortResetGpioNum        = %x\n", PortPtr->XgbePortResetGpioNum));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortMdioResetI2cAddress = %x\n", PortPtr->XgbePortMdioResetI2cAddress));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSfpI2cAddress       = %x\n", PortPtr->XgbePortSfpI2cAddress));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSfpTxFaultGpio      = %x\n", PortPtr->XgbePortSfpTxFaultGpio));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSfpRxLosGpio        = %x\n", PortPtr->XgbePortSfpRxLosGpio));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSfpGpioMask         = %x\n", PortPtr->XgbePortSfpGpioMask));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSfpRsGpio           = %x\n", PortPtr->XgbePortSfpRsGpio));
      DEBUG((DEBUG_INFO, "PortPtr->XgbePortSfpModAbsGpio       = %x\n", PortPtr->XgbePortSfpModAbsGpio));

      PortPtr->XgbePortSfpTwiAddress     = (UINT8) (( DxioPortList->EtherNet.EthPortProp4.SfpMuxUpAdd << 3 ) | ( DxioPortList->EtherNet.EthPortProp4.SfpMux));
      PortPtr->XgbePortSfpTwiBus         = (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) ? 0x0 : 0x1;
      PortPtr->XgbaPortRedriverPresent   = (UINT8) DxioPortList->EtherNet.EthPortProp4.RedriverPresent;
      PortPtr->XgbaPortRedriverModel     = (UINT8) DxioPortList->EtherNet.EthPortProp4.RedriverModel;
      PortPtr->XgbaPortRedriverInterface = (UINT8) DxioPortList->EtherNet.EthPortProp4.RedriverInterface;
      PortPtr->XgbaPortRedriverAddress   = (UINT8) DxioPortList->EtherNet.EthPortProp4.RedriverAddress;
      PortPtr->XgbaPortRedriverLane      = (UINT8) DxioPortList->EtherNet.EthPortProp4.RedriverLane;
      PortPtr->XgbaPortPadGpio           = 0x0;
      // change PadMux based on the sideband connection MDIO/SFP+
      if (PortPtr->XgbePortConnectedType == XGBE_CONNECTION_MDIO_PHY) {
        PortPtr->XgbaPortPadMdio           = (UINT8) ((DxioPortList->EtherNet.PadMux0 >> 4) & 0xFF);
      } else {
         PortPtr->XgbaPortPadI2C            = (UINT8) DxioPortList->EtherNet.PadMux0;
      }
      PortPtr->Reserve1                  = 0x0;
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortRedriverModel     = %x\n", PortPtr->XgbaPortRedriverModel));
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortRedriverInterface = %x\n", PortPtr->XgbaPortRedriverInterface));
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortRedriverAddress   = %x\n", PortPtr->XgbaPortRedriverAddress));
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortRedriverLane      = %x\n", PortPtr->XgbaPortRedriverLane));
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortPadGpio           = %x\n", PortPtr->XgbaPortPadGpio));
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortPadMdio           = %x\n", PortPtr->XgbaPortPadMdio));
      DEBUG((DEBUG_INFO, "PortPtr->XgbaPortPadI2C            = %x\n", PortPtr->XgbaPortPadI2C));
      DEBUG((DEBUG_INFO, "PortPtr->Reserve1                  = %x\n", PortPtr->Reserve1));

      if (DxioPortList->EtherNet.EthPortProp0.PortNum == ETH_PORT_0) {
        Buffer = PcdSetPtr(PcdXgbePort0Table, &PcdBufSize, (VOID*) Port0);
      } else {
         Buffer = PcdSetPtr(PcdXgbePort1Table, &PcdBufSize, (VOID*) Port1);
      }
      Status = (Buffer != NULL) ? EFI_SUCCESS : EFI_BUFFER_TOO_SMALL;
      DEBUG((DEBUG_INFO, "PcdSetPtr  , Status = %r\n", Status));
      DEBUG((DEBUG_INFO, "PcdBufSzie = %x\n", PcdBufSize));
    }
    if ((DxioPortList->Flags & DESCRIPTOR_TERMINATE_LIST) == DESCRIPTOR_TERMINATE_LIST) {
      break;  
    }
    DxioPortList++;                      
  }
  return Status;
}
