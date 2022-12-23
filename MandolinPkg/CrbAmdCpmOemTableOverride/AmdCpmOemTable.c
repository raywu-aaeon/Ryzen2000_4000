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

#include <AmdCpmPei.h>
#include <AmdCpmBaseIo.h>
#include <AmdCpmBase.h>
#include "Pei/AmdCpmOemInitPei/AmdCpmOemInitPeim.h" // AMI_OVERRIDE : Different from original AmdCpmOemTable.c.
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
#include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>
#include <Library/IoLib.h>
#include <Fch.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <NbioGfx.h>


VOID
I2cTouchDeviceIntGpioInit (
  VOID
);

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
    0x0200, // BOARD_ID0
    0x0201, // BOARD_ID1
    0x0202, // BOARD_ID2
    0x0203, // BOARD_ID3
    0x0204, // BOARD_ID4
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
    //For Modern-standby boards support
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0001, 0x0010}, //    0   0   0   Mandolin     Regulator Board RV  =>platform mask = 0x00010000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0005, 0x0011}, //    0   0   1   Tambourine             Board RV  =>platform mask = 0x00020000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0009, 0x0012}, //    0   1   0   Mandolin DAP Regulator Board RV  =>platform mask = 0x00040000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0019, 0x0013}, //    1   1   0   Mandolin DAP 2PHASE    Board RV  =>platform mask = 0x00080000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0011, 0x0014}, //    1   0   0   Mandolin     2PHASE    Board RV  =>platform mask = 0x00100000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0015, 0x0015}, //    1   0   0   Mandolin     2PHASE    Board RV  =>platform mask = 0x00200000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0001, 0x0018}, //    0   0   0   Mandolin     Regulator Board RV2 =>platform mask = 0x01000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0005, 0x0019}, //    0   0   1   Tambourine             Board RV2 =>platform mask = 0x02000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0009, 0x001A}, //    0   1   0   Mandolin DAP Regulator Board RV2 =>platform mask = 0x04000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0019, 0x001B}, //    1   1   0   Mandolin DAP 2PHASE    Board RV2 =>platform mask = 0x08000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0011, 0x001C}, //    1   0   0   Mandolin     2PHASE    Board RV2 =>platform mask = 0x10000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0015, 0x001D}, //    1   0   0   Mandolin     2PHASE    Board RV2 =>platform mask = 0x20000000
    //For RV2 CLKREQ#5/CLKREQ#6 rework board.
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0002, 0x0005}, //    0   0   0   Mandolin     Regulator Board RV  =>platform mask = 0x00000020
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x000A, 0x0005}, //    0   1   0   Mandolin DAP Regulator Board RV  =>platform mask = 0x00000020
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x001A, 0x0005}, //    1   1   0   Mandolin DAP 2PHASE    Board RV  =>platform mask = 0x00000020
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0012, 0x0005}, //    1   0   0   Mandolin     2PHASE    Board RV  =>platform mask = 0x00000020
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0006, 0x0005}, //    0   0   1   Tambourine             Board RV  =>platform mask = 0x00000002
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0002, 0x000D}, //    0   0   0   Mandolin     Regulator Board RV2 =>platform mask = 0x00002000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x000A, 0x000D}, //    0   1   0   Mandolin DAP Regulator Board RV2 =>platform mask = 0x00002000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x001A, 0x000D}, //    1   1   0   Mandolin DAP 2PHASE    Board RV2 =>platform mask = 0x00002000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0012, 0x000D}, //    1   0   0   Mandolin     2PHASE    Board RV2 =>platform mask = 0x00002000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0006, 0x000D}, //    0   0   1   Tambourine             Board RV2 =>platform mask = 0x00000200
    // MS + ClkReq
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0003, 0x0016}, //    0   0   0   Mandolin     Regulator Board RV  =>platform mask = 0x00010000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0007, 0x0016}, //    0   0   1   Tambourine             Board RV  =>platform mask = 0x00020000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x000B, 0x0016}, //    0   1   0   Mandolin DAP Regulator Board RV  =>platform mask = 0x00040000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x001B, 0x0016}, //    1   1   0   Mandolin DAP 2PHASE    Board RV  =>platform mask = 0x00080000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0013, 0x0016}, //    1   0   0   Mandolin     2PHASE    Board RV  =>platform mask = 0x00100000
    {CPM_CPU_REVISION_ID_RV, 0x001F, 0x0017, 0x0016}, //    1   0   0   Mandolin     2PHASE    Board RV  =>platform mask = 0x00200000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0003, 0x001E}, //    0   0   0   Mandolin     Regulator Board RV2 =>platform mask = 0x01000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0007, 0x001E}, //    0   0   1   Tambourine             Board RV2 =>platform mask = 0x02000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x000B, 0x001E}, //    0   1   0   Mandolin DAP Regulator Board RV2 =>platform mask = 0x04000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x001B, 0x001E}, //    1   1   0   Mandolin DAP 2PHASE    Board RV2 =>platform mask = 0x08000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0013, 0x001E}, //    1   0   0   Mandolin     2PHASE    Board RV2 =>platform mask = 0x10000000
    {CPM_CPU_REVISION_ID_RV2,0x001F, 0x0017, 0x001E}, //    1   0   0   Mandolin     2PHASE    Board RV2 =>platform mask = 0x20000000
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
//   UINT8  Purpose;  // Purpose. 0: For Normal Purpose. 1: For Modern Standby Purpose.
    {0x00, 0x03, 0xEA, 0xFE, 0x01, CPM_PRE_INIT_STAGE_0, NORMAL_PURPOSE}, // PM_RegEA[0]: PCIDisable = 1
    {0x00, 0x0D, 0x1A, 0xFC, 0x00, CPM_PRE_INIT_STAGE_2, NORMAL_PURPOSE}, // IOMUXx0001A[1:0]: PCIE_RST_L = 0
//  {0x00, 0x03, 0x75, 0xFC, 0x02, CPM_PRE_INIT_STAGE_1, MODERN_STANDBY}, // PM_Reg74[9:8] This is a sample for Modern Standby Init. Don't do Modern Standby Init at Stage 0, because MainTablePtr->ModernStandbyEn doesn't be overrided at Stage 0.
    //for modern standby
    {0x00, 0x03, 0x75, 0xFC, 0x01, CPM_PRE_INIT_STAGE_2, NORMAL_PURPOSE},
    // Power button; Clear WakeSts & InterruptSts; Enable wake in S0I3 state; set to Level trigger; Enable interrupt delivery
    {0x00, 0x15, 0x01, 0x00, 0xE1, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x03, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // PwrBtnEn = 0, AcpiReducedHWEn = 1
    {0x00, 0x03, 0x75, 0xFC, 0x02, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    //Enable power button to wait the system after 4s shutdown
    {0x00, 0x0E, 0x51, 0xEF, 0x10, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // AC/DC timer
    {0x00, 0x15, 0xD1, 0x00, 0xE1, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0xD3, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // XHCI0 PME
    {0x00, 0x15, 0xE9, 0x00, 0xE1, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0xEB, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // XHCI0 PME
    {0x00, 0x15, 0xED, 0x00, 0xE1, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0xEF, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // NbGPP PME 172
    {0x00, 0x17, 0xB1, 0x00, 0x21, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x17, 0xB3, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // SD_CD# for FCH SDIO card erader
    {0x00, 0x16, 0x11, 0x00, 0x20, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x16, 0x13, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // PCIE_WAKE_UP# => AGPIO2 (0xFED81508)
    {0x00, 0x15, 0x09, 0x00, 0xE3, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x0B, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    //WLAN
    {0x00, 0x15, 0x39, 0x00, 0xE3, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x3B, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    //WWAN
    {0x00, 0x15, 0x45, 0x00, 0xE3, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x47, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    //x4DT
    {0x00, 0x15, 0x61, 0x00, 0xE3, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x63, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // TPAD_ATTN#
    {0x00, 0x15, 0x25, 0x00, 0x23, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x27, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // WoV Int_ACP_FCH_AZ_Wake => AGPIO61
    {0x00, 0x15, 0xF5, 0x00, 0x20, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0xF7, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    // LPC_SCI# (EC SCI) => LPC_PME_L_AGPIO22 (0xFED81558)
    {0x00, 0x15, 0x59, 0x00, 0x20, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0x5B, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    //GPIO44 for timer alarm
    {0x00, 0x15, 0xB1, 0x00, 0x20, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    {0x00, 0x15, 0xB3, 0xFF, 0x30, CPM_PRE_INIT_STAGE_2, MODERN_STANDBY},
    0xFF,
  }
};

//
// GPIO Init Table for Mandolin
//
AMD_CPM_GPIO_INIT_TABLE             gCpmGpioInitTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_INIT, sizeof (gCpmGpioInitTable) / sizeof (UINT8), 0, 0, 0x00003F3F, 0x0000000F},
  {
//         (socket,die,gpio,function,        output,           pullup)
    GPIO_DEF_V2 (0, 0, 40,  GPIO_FUNCTION_0, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // AGPIO40 // SGPIO_DATAIN // MDIO0_SDA // SSD_RESET#
    GPIO_DEF_V2 (0, 0, 140, GPIO_FUNCTION_2, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // UART1_CTS_L/UART3_TXD/EGPIO140 // MXM_RESET#
    GPIO_DEF_V2 (0, 0, 2,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // PCIE_WAKE_UP#
    GPIO_DEF_V2 (0, 0, 3,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AGPIO3 // "DP_HPD_DIG",hot plug detection from EVAL card
    GPIO_DEF_V2 (0, 0, 4,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AGPIO4 // "DASH_SMI#", from USB2.0 HDR
    GPIO_DEF_V2 (0, 0, 7,   GPIO_FUNCTION_1, GPIO_NA,          GPIO_PD_EN    ), // AGPIO7/FCH_ACP_I2S_SDIN  // Set to FCH_ACP_I2S_SDIN
    GPIO_DEF_V2 (0, 0, 8,   GPIO_FUNCTION_1, GPIO_NA,          GPIO_PD_EN    ), // AGPIO8/FCH_ACP_I2S_LRCLK // Set to FCH_ACP_I2S_LRCLK
//    GPIO_DEF_V2 (0, 0, 9,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_EN    ), // AGPIO9/SGPIO_DATAOUT/MDIO1_SCL // "TPAD_ATTN#", alert from touch pad
    GPIO_DEF_V2 (0, 0, 11,  GPIO_FUNCTION_1, GPIO_NA,          GPIO_PU_PD_DIS), // BLINK/AGPIO11 // "BLINK", to power state indicator LED
    GPIO_DEF_V2 (0, 0, 12,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // LLB_L/AGPIO12 // "TEX_REQ#", interrupt from touch panel
    GPIO_DEF_V2 (0, 0, 13,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // USB_OC5_L/AGPIO13 // HP_MIC_DET#
    GPIO_DEF_V2 (0, 0, 14,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // USB_OC4_L/AGPIO14 // SENSOR_MISC3
    GPIO_DEF_V2 (0, 0, 17,  GPIO_FUNCTION_1, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // USB_OC1_L/AGPIO17 // SENSOR_MISC1
    GPIO_DEF_V2 (0, 0, 18,  GPIO_FUNCTION_1, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // USB_OC2_L/AGPIO18 // SENSOR_MISC2
    GPIO_DEF_V2 (0, 0, 21,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_EN    ), // LPC_PD_L/SD_CMD/AGPIO21 // LPC_PD_L
    GPIO_DEF_V2 (0, 0, 22,  GPIO_FUNCTION_2, GPIO_INPUT,       GPIO_PU_EN    ), // LPC_PME_L/EMMC_PWR_CTRL/AGPIO22 // EC_SCI#
    GPIO_DEF_V2 (0, 0, 23,  GPIO_FUNCTION_3, GPIO_INPUT,       GPIO_PU_EN    ), // AC_PRES/SGPIO_LOAD/MDIO1_SDA/AGPIO23 // AGPIO23
    GPIO_DEF_V2 (0, 0, 24,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // USB_OC3_L/AGPIO24 // SENSOR_MISC4
    GPIO_DEF_V2 (0, 0, 32,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_EN    ), // LPC_RST_L/SD_WP_L/AGPIO32 // LPC_RST_L
    GPIO_DEF_V2 (0, 0, 42,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // EGPIO42 // CAM1_EN // Control by DEVICE_ID_FCAM
    GPIO_DEF_V2 (0, 0, 141, GPIO_FUNCTION_1, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // UART1_RXD/EGPIO141 // MXM_POWER_ENABLE
    GPIO_DEF_V2 (0, 0, 142, GPIO_FUNCTION_2, GPIO_OUTPUT_HIGH, GPIO_PU_PD_DIS), // UART1_RTS_L/UART3_RXD/EGPIO142 // MXM_POWER_ON
    GPIO_DEF_V2 (0, 0, 143, GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // UART1_TXD/EGPIO143 // MXM_POWER_GOOD
    GPIO_DEF_V2 (0, 0, 144, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // UART1_INTR/AGPIO144 // UART1_INTR
    GPIO_DEF_V2 (0, 0, 67,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PD_EN    ), // SPI_ROM_REQ/EGPIO67 // SPI_ROM_REQ
    GPIO_DEF_V2 (0, 0, 68,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // AGPIO68/EMMC_CD // SD_CD_SGPIO_CLK
    GPIO_DEF_V2 (0, 0, 69,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AGPIO69 // NFC_APU_IRQ#
    GPIO_DEF_V2 (0, 0, 70,  GPIO_FUNCTION_1, GPIO_NA,          GPIO_PU_PD_DIS), // EGPIO70/EMMC_CLK/SD_CLK // SDIO_EMMC_CLK
    GPIO_DEF_V2 (0, 0, 74,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LPCCLK0/EGPIO74 // LPCCLK0
    GPIO_DEF_V2 (0, 0, 75,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LPCCLK1/EGPIO75 // LPCCLK1
    GPIO_DEF_V2 (0, 0, 76,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // SPI_ROM_GNT/EGPIO76 // SPI_ROM_GNT#
    GPIO_DEF_V2 (0, 0, 86,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // LPC_SMI_L/AGPIO86 // EC_SMI#
    GPIO_DEF_V2 (0, 0, 87,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // SERIRQ/AGPIO87 // SERIRQ
    GPIO_DEF_V2 (0, 0, 88,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // LPC_CLKRUN_L/AGPIO88 // LPC_CLKRUN_L
    GPIO_DEF_V2 (0, 0, 89,  GPIO_FUNCTION_2, GPIO_NA,          GPIO_PU_PD_DIS), // GENINT1_L/PSP_INTR0/AGPIO89 // REAR_CAM_PWREN // Control by DEVICE_ID_RCAM
    GPIO_DEF_V2 (0, 0, 90,  GPIO_FUNCTION_2, GPIO_INPUT,       GPIO_PU_PD_DIS), // GENINT2_L/PSP_INTR1/AGPIO90 // I2S_CODEC_INT
    GPIO_DEF_V2 (0, 0, 91,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // SPKR/AGPIO91 // PC_BEEP
    GPIO_DEF_V2 (0, 0, 104, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD0/SD_DATA0/EGPIO104 // LAD0
    GPIO_DEF_V2 (0, 0, 105, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD1/SD_DATA1/EGPIO105 // LAD1
    GPIO_DEF_V2 (0, 0, 106, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD2/SD_DATA2/EGPIO106 // LAD2
    GPIO_DEF_V2 (0, 0, 107, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD3/SD_DATA3/EGPIO107 // LAD3
    GPIO_DEF_V2 (0, 0, 108, GPIO_FUNCTION_1, GPIO_NA,          GPIO_PU_PD_DIS), // LDRQ0_L/ESPI_ALERT_D1/EGPIO108 // EC_ESPI_ALERT#
    GPIO_DEF_V2 (0, 0, 109, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LFRAME_L/EGPIO109 // LFRAME_L
//  GPIO_DEF_V2 (0, 0, 136, GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // UART0_RXD/EGPIO136
    GPIO_DEF_V2 (0, 0, 137, GPIO_FUNCTION_2, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // UART0_RTS_L/EGPIO137 // APU_NFC_DWL_REQ#
    GPIO_DEF_V2 (0, 0, 138, GPIO_FUNCTION_1, GPIO_OUTPUT_HIGH, GPIO_PU_PD_DIS), // UART0_TXD/EGPIO138 // APU_NFC_WAKE#
    GPIO_DEF_V2 (0, 0, 139, GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // UART0_INTR/AGPIO139 // TPM_PIRQ#
    GPIO_DEF_V2 (0, 0, 251, GPIO_FUNCTION_0, GPIO_OUTPUT_HIGH, GPIO_PU_PD_DIS), // ECRAMxB2[3] // ECGPIO042, HDD_PWR_EN
    0xFF,
  }
};

//
// GPIO Init Table for Mandolin + Modern-standby support
//
AMD_CPM_GPIO_INIT_TABLE             gCpmGpioInitTableMs = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_INIT, sizeof (gCpmGpioInitTableMs) / sizeof (UINT8), 0, 0, 0x7F7F0000, 0x0000000F},
  {
//         (socket,die,gpio,function,        output,           pullup)
    GPIO_DEF_V2 (0, 0, 40,  GPIO_FUNCTION_0, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // AGPIO40 // SGPIO_DATAIN // MDIO0_SDA // SSD_RESET#
    GPIO_DEF_V2 (0, 0, 140, GPIO_FUNCTION_2, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // UART1_CTS_L/UART3_TXD/EGPIO140 // MXM_RESET#
    GPIO_DEF_V2 (0, 0, 2,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // PCIE_WAKE_UP#
    GPIO_DEF_V2 (0, 0, 3,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AGPIO3 // "DP_HPD_DIG",hot plug detection from EVAL card
    GPIO_DEF_V2 (0, 0, 4,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AGPIO4 // "DASH_SMI#", from USB2.0 HDR
    GPIO_DEF_V2 (0, 0, 6,   GPIO_FUNCTION_0, GPIO_OUTPUT_HIGH, GPIO_PU_EN    ), // GPIO6/DEVSLP1 // M.2 SSD POWER ENABLE
    GPIO_DEF_V2 (0, 0, 7,   GPIO_FUNCTION_1, GPIO_NA,          GPIO_PD_EN    ), // AGPIO7/FCH_ACP_I2S_SDIN  // Set to FCH_ACP_I2S_SDIN
    GPIO_DEF_V2 (0, 0, 8,   GPIO_FUNCTION_1, GPIO_NA,          GPIO_PD_EN    ), // AGPIO8/FCH_ACP_I2S_LRCLK // Set to FCH_ACP_I2S_LRCLK
//    GPIO_DEF_V2 (0, 0, 9,   GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_EN    ), // AGPIO9/SGPIO_DATAOUT/MDIO1_SCL // "TPAD_ATTN#", alert from touch pad
    GPIO_DEF_V2 (0, 0, 11,  GPIO_FUNCTION_1, GPIO_NA,          GPIO_PU_PD_DIS), // BLINK/AGPIO11 // "BLINK", to power state indicator LED
    GPIO_DEF_V2 (0, 0, 12,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // LLB_L/AGPIO12 // "TEX_REQ#", interrupt from touch panel
    GPIO_DEF_V2 (0, 0, 13,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // USB_OC5_L/AGPIO13 // HP_MIC_DET#
    GPIO_DEF_V2 (0, 0, 14,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // USB_OC4_L/AGPIO14 // wlan wakeup
    GPIO_DEF_V2 (0, 0, 17,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // USB_OC1_L/AGPIO17 // wwan wakeup
    GPIO_DEF_V2 (0, 0, 18,  GPIO_FUNCTION_1, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // USB_OC2_L/AGPIO18 // SENSOR_MISC2
    GPIO_DEF_V2 (0, 0, 21,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_EN    ), // LPC_PD_L/SD_CMD/AGPIO21 // LPC_PD_L
    GPIO_DEF_V2 (0, 0, 22,  GPIO_FUNCTION_2, GPIO_INPUT,       GPIO_PU_EN    ), // LPC_PME_L/EMMC_PWR_CTRL/AGPIO22 // EC_SCI#
    GPIO_DEF_V2 (0, 0, 23,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AC_PRES/SGPIO_LOAD/MDIO1_SDA/AGPIO23 // AGPIO23
    GPIO_DEF_V2 (0, 0, 24,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // USB_OC3_L/AGPIO24 // DT SLOT WAKEUP
    GPIO_DEF_V2 (0, 0, 32,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_EN    ), // LPC_RST_L/SD_WP_L/AGPIO32 // LPC_RST_L
    GPIO_DEF_V2 (0, 0, 42,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // EGPIO42 // CAM1_EN // Control by DEVICE_ID_FCAM
    GPIO_DEF_V2 (0, 0, 141, GPIO_FUNCTION_1, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // UART1_RXD/EGPIO141 // MXM_POWER_ENABLE
    GPIO_DEF_V2 (0, 0, 142, GPIO_FUNCTION_2, GPIO_OUTPUT_HIGH, GPIO_PU_PD_DIS), // UART1_RTS_L/UART3_RXD/EGPIO142 // MXM_POWER_ON
    GPIO_DEF_V2 (0, 0, 143, GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // UART1_TXD/EGPIO143 // MXM_POWER_GOOD
    GPIO_DEF_V2 (0, 0, 144, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // UART1_INTR/AGPIO144 // UART1_INTR
    GPIO_DEF_V2 (0, 0, 67,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PD_EN    ), // SPI_ROM_REQ/EGPIO67 // SPI_ROM_REQ
    GPIO_DEF_V2 (0, 0, 68,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // AGPIO68/EMMC_CD // SD_CD_SGPIO_CLK
    GPIO_DEF_V2 (0, 0, 69,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // AGPIO69 // NFC_APU_IRQ#
    GPIO_DEF_V2 (0, 0, 70,  GPIO_FUNCTION_1, GPIO_NA,          GPIO_PU_PD_DIS), // EGPIO70/EMMC_CLK/SD_CLK // SDIO_EMMC_CLK
    GPIO_DEF_V2 (0, 0, 74,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LPCCLK0/EGPIO74 // LPCCLK0
    GPIO_DEF_V2 (0, 0, 75,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LPCCLK1/EGPIO75 // LPCCLK1
    GPIO_DEF_V2 (0, 0, 76,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // SPI_ROM_GNT/EGPIO76 // SPI_ROM_GNT#
    GPIO_DEF_V2 (0, 0, 86,  GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // LPC_SMI_L/AGPIO86 // EC_SMI#
    GPIO_DEF_V2 (0, 0, 87,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // SERIRQ/AGPIO87 // SERIRQ
    GPIO_DEF_V2 (0, 0, 88,  GPIO_FUNCTION_0, GPIO_INPUT,       GPIO_PU_PD_DIS), // LPC_CLKRUN_L/AGPIO88 // LPC_CLKRUN_L
    GPIO_DEF_V2 (0, 0, 89,  GPIO_FUNCTION_2, GPIO_NA,          GPIO_PU_PD_DIS), // GENINT1_L/PSP_INTR0/AGPIO89 // REAR_CAM_PWREN // Control by DEVICE_ID_RCAM
    GPIO_DEF_V2 (0, 0, 90,  GPIO_FUNCTION_2, GPIO_INPUT,       GPIO_PU_PD_DIS), // GENINT2_L/PSP_INTR1/AGPIO90 // I2S_CODEC_INT
    GPIO_DEF_V2 (0, 0, 91,  GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // SPKR/AGPIO91 // PC_BEEP
    GPIO_DEF_V2 (0, 0, 104, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD0/SD_DATA0/EGPIO104 // LAD0
    GPIO_DEF_V2 (0, 0, 105, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD1/SD_DATA1/EGPIO105 // LAD1
    GPIO_DEF_V2 (0, 0, 106, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD2/SD_DATA2/EGPIO106 // LAD2
    GPIO_DEF_V2 (0, 0, 107, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LAD3/SD_DATA3/EGPIO107 // LAD3
    GPIO_DEF_V2 (0, 0, 108, GPIO_FUNCTION_1, GPIO_NA,          GPIO_PU_PD_DIS), // LDRQ0_L/ESPI_ALERT_D1/EGPIO108 // EC_ESPI_ALERT#
    GPIO_DEF_V2 (0, 0, 109, GPIO_FUNCTION_0, GPIO_NA,          GPIO_PU_PD_DIS), // LFRAME_L/EGPIO109 // LFRAME_L
//  GPIO_DEF_V2 (0, 0, 136, GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_PD_DIS), // UART0_RXD/EGPIO136
    GPIO_DEF_V2 (0, 0, 137, GPIO_FUNCTION_2, GPIO_OUTPUT_LOW,  GPIO_PU_PD_DIS), // UART0_RTS_L/EGPIO137 // APU_NFC_DWL_REQ#
    GPIO_DEF_V2 (0, 0, 138, GPIO_FUNCTION_1, GPIO_OUTPUT_HIGH, GPIO_PU_PD_DIS), // UART0_TXD/EGPIO138 // APU_NFC_WAKE#
    GPIO_DEF_V2 (0, 0, 139, GPIO_FUNCTION_1, GPIO_INPUT,       GPIO_PU_EN    ), // UART0_INTR/AGPIO139 // TPM_PIRQ#
    GPIO_DEF_V2 (0, 0, 251, GPIO_FUNCTION_0, GPIO_OUTPUT_HIGH, GPIO_PU_PD_DIS), // ECRAMxB2[3] // ECGPIO042, HDD_PWR_EN
    0xFF,
  }
};

//
// GEVENT Init Table Mandolin
//
AMD_CPM_GEVENT_INIT_TABLE           gCpmGeventInitTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GEVENT_INIT, sizeof (gCpmGeventInitTable) / sizeof (UINT8), 0, 0, 0x00003F3F, 0x00000001},
  {//                  GEvent EventEnable   SciTrigE      SciLevl         SmiSciEn        SciS0En         SciMap      SmiTrig       SmiControl
    GEVENT_DEFINITION (0x02,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_02,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT02: DP_HPD_DIG
    GEVENT_DEFINITION (0x03,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_03,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT03: EC_SCI#
    GEVENT_DEFINITION (0x04,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_04,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT04: DASH_SMI
//  GEVENT_DEFINITION (0x06,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_06,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT06: PC_BEEP
//  GEVENT_DEFINITION (0x07,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_LEVEL, SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_07,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT07: DEVSLP0
    GEVENT_DEFINITION (0x08,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_08,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT08: PCIE_WAKE_UP#/WAKE_ON_WAN#
    GEVENT_DEFINITION (0x09,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_09,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT09: EC_SMI#, alternate EC SCI# when eMMC/SD enabled.
    GEVENT_DEFINITION (0x0B,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_11,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT11: BT_I2S_DIN_HDR
//  GEVENT_DEFINITION (0x0E,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_14,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT14: SENSOR_MISC2
//  GEVENT_DEFINITION (0x10,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_16,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT16:
//  GEVENT_DEFINITION (0x15,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_21,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT21: PWR_BTN#
    GEVENT_DEFINITION (0x16,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_22,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT22: TPAD_ATTN#
    GEVENT_DEFINITION (ZPODD_DUMMY_EVENT, EVENT_ENABLE, SCITRIG_HI, SCILEVEL_EDGE, SMISCI_DISABLE, SCIS0_DISABLE, ZPODD_DUMMY_EVENT, SMITRIG_HI, SMICONTROL_DISABLE), // GEVENT31: ZPODD Dummy Gevent31
    0xFF,
  }
};

//
// GEVENT Init Table for Mandolin + Modern-standby support
//
AMD_CPM_GEVENT_INIT_TABLE           gCpmGeventInitTableMs = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GEVENT_INIT, sizeof (gCpmGeventInitTableMs) / sizeof (UINT8), 0, 0, 0x7F7F0000, 0x00000001},
  {//                  GEvent EventEnable   SciTrigE      SciLevl         SmiSciEn        SciS0En         SciMap      SmiTrig       SmiControl
    GEVENT_DEFINITION (0x02,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_02,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT02: DP_HPD_DIG
    GEVENT_DEFINITION (0x03,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_03,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT03: EC_SCI#
    GEVENT_DEFINITION (0x04,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_04,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT04: DASH_SMI
//  GEVENT_DEFINITION (0x06,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_06,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT06: PC_BEEP
//  GEVENT_DEFINITION (0x07,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_LEVEL, SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_07,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT07: DEVSLP0
    GEVENT_DEFINITION (0x08,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_08,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT08: PCIE_WAKE_UP#/WAKE_ON_WAN#
    GEVENT_DEFINITION (0x09,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_09,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT09: EC_SMI#, alternate EC SCI# when eMMC/SD enabled.
    GEVENT_DEFINITION (0x0B,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_11,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT11: BT_I2S_DIN_HDR
    GEVENT_DEFINITION (0x0D,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_13,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT13: WAKE_WAKE#
//  GEVENT_DEFINITION (0x0E,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_14,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT14: SENSOR_MISC2
    GEVENT_DEFINITION (0x0F,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_15,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT15: x4 DT wakeup#
//  GEVENT_DEFINITION (0x10,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_16,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT16:
//  GEVENT_DEFINITION (0x15,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_21,  SMITRIG_HI,   SMICONTROL_DISABLE), // GEVENT21: PWR_BTN#
    GEVENT_DEFINITION (0x16,  EVENT_ENABLE, SCITRIG_LOW,  SCILEVEL_EDGE,  SMISCI_DISABLE, SCIS0_DISABLE,  SCIMAP_22,  SMITRIG_LOW,  SMICONTROL_DISABLE), // GEVENT22: TPAD_ATTN#
    GEVENT_DEFINITION (ZPODD_DUMMY_EVENT, EVENT_ENABLE, SCITRIG_HI, SCILEVEL_EDGE, SMISCI_DISABLE, SCIS0_DISABLE, ZPODD_DUMMY_EVENT, SMITRIG_HI, SMICONTROL_DISABLE), // GEVENT31: ZPODD Dummy Gevent31
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
  {//                       DeviceId               Enable           Assert Deassert Hotplugs
    GPIO_DEVICE_DEFINITION (DEVICE_ID_MXM,         CPM_DEVICE_AUTO, 0,     1,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_DT,          CPM_DEVICE_ON,   0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_WLAN,        CPM_DEVICE_ON,   0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_LAN,         CPM_DEVICE_ON,   0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_WWAN,        CPM_DEVICE_ON,   0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_SSD,         CPM_DEVICE_ON,   1,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_ODD,         CPM_DEVICE_AUTO, 0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_HDD0,        CPM_DEVICE_AUTO, 0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_RCAM,        CPM_DEVICE_ON,   0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_FCAM,        CPM_DEVICE_ON,   0,     0,       0),
    GPIO_DEVICE_DEFINITION (DEVICE_ID_USB_TYPE_C0, CPM_DEVICE_OFF,  0,     0,       0), // HDMI over USB Type C Port 0 control
    GPIO_DEVICE_DEFINITION (DEVICE_ID_USB_TYPE_C1, CPM_DEVICE_OFF,  0,     0,       0), // HDMI over USB Type C Port 1 control
    GPIO_DEVICE_DEFINITION (DEVICE_ID_NGPU,        CPM_DEVICE_OFF,  0,     0,       0),
    0xFF,
  }
};

//
// CPM Device Detection Table for Mandolin
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
    {DEVICE_ID_ODD,  0, ZPODD_DETECT_PIN, ZPODD_DETECT_VALUE,    0, 0}, // ODD_PLUGIN#: GEVENT14#
    {DEVICE_ID_MXM,  0, MXM_PRESENT,      MXM_DETECT_VALUE,      0, 0},
    {DEVICE_ID_HDD0, 0, 0x233,            1,                     0, 0},
//  {DEVICE_ID_WWAN, 0, 0x233,            1,                     0, 0},
    {DEVICE_ID_DT,   0, DTDEVICE_DETECT,  DTDEVICE_DETECT_VALUE, 0, 0},
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
    { DEVICE_ID_NGPU, CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_GPIO_PIN (MXM_RESET, 0),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO140
    { DEVICE_ID_DT,   CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (DT_RESET, 0),   GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[6] (BIT46)
    { DEVICE_ID_WLAN, CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WLAN_RESET, 0), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[7] (BIT47)
    { DEVICE_ID_LAN,  CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (LAN_RESET, 0),  GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[4] (BIT44)
    { DEVICE_ID_WWAN, CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WWAN_RESET, 0), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[5] (BIT45)
    { DEVICE_ID_SSD,  CPM_RESET_ASSERT,   CPM_RESET_GPIO, CPM_GPIO_PIN (SSD_RESET, 0),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO40
    { DEVICE_ID_MXM,  CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_GPIO_PIN (MXM_RESET, 1),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO140
    { DEVICE_ID_NGPU, CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_GPIO_PIN (MXM_RESET, 1),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO140
    { DEVICE_ID_DT,   CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (DT_RESET, 1),   GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[6] (BIT46)
    { DEVICE_ID_WLAN, CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WLAN_RESET, 1), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[7] (BIT47)
    { DEVICE_ID_LAN,  CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (LAN_RESET, 1),  GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[4] (BIT44)
    { DEVICE_ID_WWAN, CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_ECRAM_GPIO_PIN (WWAN_RESET, 1), GPIO_DEVICE_INIT_STAGE_DUMMY},  // ECRAM xB1[5] (BIT45)
    { DEVICE_ID_SSD,  CPM_RESET_DEASSERT, CPM_RESET_GPIO, CPM_GPIO_PIN (SSD_RESET, 1),        GPIO_DEVICE_INIT_STAGE_DUMMY},  // FCH GPIO40
    0xFF,
  }
};

//
// CPM GPIO Device Init Table (Power On/Off) - Mandolin
//
AMD_CPM_GPIO_DEVICE_POWER_TABLE gCpmGpioDevicePowerTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_DEVICE_POWER, sizeof (gCpmGpioDevicePowerTable) / sizeof (UINT8), 0, 0, 0x00003F3F, 0x0000000F},
  {
//  {UINT8  DeviceId;       // Device Id
//   UINT8  Mode;           // Device Power Mode. 1: Power On. 0: Power Off
//   UINT8  Type;           // Device Power Item. 0: Set GPIO. 1: Wait GPIO. 2: Add Delay
//   UINT32 ((UINT16)Pin + ((UINT8)Value << 16));                 // GPIO pin value or delay timer
//   UINT8  InitFlag;       // Init flag in post},
  {DEVICE_ID_MXM,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 0),            GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_OFF, CPM_POWER_DELAY, 1000,                                          GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ON, 0),                GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_NGPU,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 0),            GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_SSD,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (SSD_POWER_EN, 0),                GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_RCAM,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (RCAM_POWER_EN, 0),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_FCAM,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (FCAM_POWER_EN, 0),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_HDD0,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (0x33, 0),                  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_ODD,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (ZPODD_POWER_CONTROL, 0),         GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_DT,          CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (DT_POWER_EN, 0),           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WLAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WLAN_POWER_EN, 0),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_LAN,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LAN_POWER_EN, 0),          GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_CARD_POWER_OFF_L, 0), GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_RADIO_PERMITTED, 0),  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_DELAY, 100,                                           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_POWER_EN, 0),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C0, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC0_AUX, 0),        GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C1, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC1_AUX, 0),        GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ON, 1),                GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_DELAY, 30000,                                         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 1),            GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_DELAY, 100000,                                        GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_WAIT,  CPM_GPIO_PIN (MXM_POWER_GOOD, 1),              GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_DELAY, 200,                                           GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_NGPU,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 1),            GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_NGPU,        CPM_POWER_ON,  CPM_POWER_DELAY, 7000,                                          GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_SSD,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (SSD_POWER_EN, 1),                GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_RCAM,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (RCAM_POWER_EN, 1),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_FCAM,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (FCAM_POWER_EN, 1),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_HDD0,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (0x33, 1),                  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_ODD,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (ZPODD_POWER_CONTROL, 1),         GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_DT,          CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (DT_POWER_EN, 1),           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WLAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WLAN_POWER_EN, 1),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_LAN,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LAN_POWER_EN, 1),          GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_RADIO_PERMITTED, 1),  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_POWER_EN, 1),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_DELAY, 100,                                           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_CARD_POWER_OFF_L, 1), GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C0, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC0_AUX, 1),        GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C1, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC1_AUX, 1),        GPIO_DEVICE_INIT_STAGE_1},
  0xFF,
  }
};

//
// CPM GPIO Device Init Table (Power On/Off) - Mandolin + Modern-standby support
//
AMD_CPM_GPIO_DEVICE_POWER_TABLE gCpmGpioDevicePowerTableMs = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_GPIO_DEVICE_POWER, sizeof (gCpmGpioDevicePowerTableMs) / sizeof (UINT8), 0, 0, 0x7F7F0000, 0x0000000F},
  {
//  {UINT8  DeviceId;       // Device Id
//   UINT8  Mode;           // Device Power Mode. 1: Power On. 0: Power Off
//   UINT8  Type;           // Device Power Item. 0: Set GPIO. 1: Wait GPIO. 2: Add Delay
//   UINT32 ((UINT16)Pin + ((UINT8)Value << 16));                 // GPIO pin value or delay timer
//   UINT8  InitFlag;       // Init flag in post},
  {DEVICE_ID_MXM,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 0),            GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_OFF, CPM_POWER_DELAY, 1000,                                          GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ON, 0),                GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_NGPU,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 0),            GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_SSD,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (PCO_SSD_POWER_EN, 0),                GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_RCAM,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (RCAM_POWER_EN, 0),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_FCAM,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (FCAM_POWER_EN, 0),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_HDD0,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (0x33, 0),                  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_ODD,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_GPIO_PIN (ZPODD_POWER_CONTROL, 0),         GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_DT,          CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (DT_POWER_EN, 0),           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WLAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WLAN_POWER_EN, 0),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_LAN,         CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LAN_POWER_EN, 0),          GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_CARD_POWER_OFF_L, 0), GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_RADIO_PERMITTED, 0),  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_DELAY, 100,                                           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_POWER_EN, 0),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C0, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC0_AUX, 0),        GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C1, CPM_POWER_OFF, CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC1_AUX, 0),        GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ON, 1),                GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_DELAY, 30000,                                         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 1),            GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_DELAY, 100000,                                        GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_WAIT,  CPM_GPIO_PIN (MXM_POWER_GOOD, 1),              GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_MXM,         CPM_POWER_ON,  CPM_POWER_DELAY, 200,                                           GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_NGPU,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (MXM_POWER_ENABLE, 1),            GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_NGPU,        CPM_POWER_ON,  CPM_POWER_DELAY, 7000,                                          GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_SSD,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (PCO_SSD_POWER_EN, 1),                GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_RCAM,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (RCAM_POWER_EN, 1),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_FCAM,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (FCAM_POWER_EN, 1),               GPIO_DEVICE_INIT_STAGE_2},
  {DEVICE_ID_HDD0,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (0x33, 1),                  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_ODD,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_GPIO_PIN (ZPODD_POWER_CONTROL, 1),         GPIO_DEVICE_INIT_STAGE_DUMMY},
  {DEVICE_ID_DT,          CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (DT_POWER_EN, 1),           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WLAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WLAN_POWER_EN, 1),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_LAN,         CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (LAN_POWER_EN, 1),          GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_RADIO_PERMITTED, 1),  GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_POWER_EN, 1),         GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_DELAY, 100,                                           GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_WWAN,        CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (WWAN_CARD_POWER_OFF_L, 1), GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C0, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC0_AUX, 1),        GPIO_DEVICE_INIT_STAGE_1},
  {DEVICE_ID_USB_TYPE_C1, CPM_POWER_ON,  CPM_POWER_SET,   CPM_ECRAM_GPIO_PIN (HDMI_USBC1_AUX, 1),        GPIO_DEVICE_INIT_STAGE_1},
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
  {CPM_SIGNATURE_PCIE_CLOCK, sizeof (gCpmPcieClockTable) / sizeof (UINT8), 0, 0, 0x007F003F, 0x0F},
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
//        (socket,die, ClkId,     ClkReq,     DeviceId,       Device,Function,SlotCheck)
    PCIE_INCLK (0, 0,  GPP_CLK6,  CLK_REQ6,   DEVICE_ID_MXM,  1,     1,       CLKPM_CHECK), // MXM
    PCIE_INCLK (0, 0,  GPP_CLK0,  CLK_REQ0,   DEVICE_ID_WLAN, 1,     2,       CLKPM_CHECK), // WLAN
    PCIE_INCLK (0, 0,  GPP_CLK1,  CLK_REQ1,   DEVICE_ID_LAN,  1,     3,       CLKPM_CHECK), // GBE
    PCIE_INCLK (0, 0,  GPP_CLK2,  CLK_REQ2,   DEVICE_ID_WWAN, 1,     4,       CLKPM_CHECK), // WWAN/GPS
    PCIE_INCLK (0, 0,  GPP_CLK3,  CLK_REQ3,   DEVICE_ID_WIFI, 1,     5,       CLKPM_CHECK), // WIFI
    PCIE_INCLK (0, 0,  GPP_CLK4,  CLK_REQ4,   DEVICE_ID_DT,   1,     2,       CLKPM_CHECK), // DT X4 SLOT
    PCIE_INCLK (0, 0,  GPP_CLK5,  CLK_REQ5,   DEVICE_ID_SSD,  1,     7,       CLKPM_CHECK), // SSD
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
  {CPM_SIGNATURE_PCIE_CLOCK, sizeof (gCpmPcieClockTable_RV2) / sizeof (UINT8), 0, 0, 0x7F003F00, 0x0F},
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
//        (socket,die, ClkId,     ClkReq,     DeviceId,       Device,Function,SlotCheck)
    PCIE_INCLK (0, 0,  GPP_CLK6,  CLK_REQ6,   DEVICE_ID_MXM,  1,     1,       CLKPM_CHECK), // MXM
    PCIE_INCLK (0, 0,  GPP_CLK0,  CLK_REQ0,   DEVICE_ID_WLAN, 1,     2,       CLKPM_CHECK), // WLAN
    PCIE_INCLK (0, 0,  GPP_CLK1,  CLK_REQ1,   DEVICE_ID_LAN,  1,     3,       CLKPM_CHECK), // GBE
    PCIE_INCLK (0, 0,  GPP_CLK4,  CLK_REQ4,   DEVICE_ID_DT,   1,     2,       CLKPM_CHECK), // DT X4 SLOT
    PCIE_INCLK (0, 0,  GPP_CLK5,  CLK_REQ5,   DEVICE_ID_SSD,  1,     5,       CLKPM_CHECK), // SSD
    0xFF,
  }
};


//
// CPM DXIO Topology Table
//
/// Note: DO NOT change the seqeunce of the PCIe slot, M.2 and SATA Express engines
AMD_CPM_DXIO_TOPOLOGY_TABLE gCpmDxioTopologyTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_DXIO_TOPOLOGY, sizeof (gCpmDxioTopologyTable) / sizeof (UINT8), 0, 0, 0x007F003F, 0x0000000F},
  0,  // SocketId
  {   // DXIO_PORT_DESCRIPTOR
//  { UINT32  Flags;                    /**< Descriptor flags
//    #define DXIO_ENGINE_DATA_INITIALIZER(mType, mStartLane, mEndLane, mHotplug, mGpioGroupId) {mType, mHotplug, 0, mStartLane, mEndLane, mGpioGroupId, 0, 0, 0}
//    #define DXIO_PORT_DATA_INITIALIZER_PCIE(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport) \
//            {mPortPresent, mDevAddress, mDevFunction, mMaxLinkSpeed, mAspm, mAspmL1_1, mAspmL1_2, 0, mHotplug, {0, mMaxLinkCap, 0, mClkPmSupport}, {0, 0, 0}, DxioEndpointDetect}
    { // DEVICE_ID_MXM                        Entry 0
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 8, 15, HotPluggableDisabled, DEVICE_ID_MXM),
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
        CLK_REQ6                              // CLKREQ#
      )
    },
    { // DEVICE_ID_SSD                        Entry 1
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 0, 1, HotPluggableDisabled, DEVICE_ID_SSD),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        7,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ5                              // CLKREQ#
      )
    },
    { // DEVICE_ID_WLAN                       Entry 2
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 4, 4, HotPluggableDisabled, DEVICE_ID_WLAN),
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
        CLK_REQ0                              // CLKREQ#
      )
    },
    { // DEVICE_ID_LAN                        Entry 3
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 5, 5, HotPluggableDisabled, DEVICE_ID_LAN),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        3,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ1                              // CLKREQ#
      )
    },
    { // DEVICE_ID_WWAN                       Entry 4
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 6, 6, HotPluggableDisabled, DEVICE_ID_WWAN),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        4,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ2                              // CLKREQ#
      )
    },
    { // DEVICE_ID_WIFI                       Entry 5
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 7, 7, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        5,                                    // Requested Function
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
    { // DEVICE_ID_SATA_EXPRESS               Entry 6
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioUnusedEngine, 2, 3, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        6,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Disabled,                  // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Disabled,                  // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        DxioClkPmSupportDisabled              // CLKREQ#
      )
    },
    { // DEVICE_ID_SATA_EXPRESS               Entry 7
      DESCRIPTOR_TERMINATE_LIST,
      DXIO_ENGINE_DATA_INITIALIZER (DxioSATAEngine, 2, 3, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_SATA_V2 (DxioPortEnabled, DxioSataChannelLong)    // Port Present
    }
  },  // End of DXIO_PORT_DESCRIPTOR
  {   // DDI_DESCRIPTOR
    { // DDI0 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux1, Hdp1)
    },
    { // DDI1 - eDP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeEDP, Aux2, Hdp2)
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
/// Note: DO NOT change the seqeunce of the PCIe slot, M.2 and SATA Express engines
AMD_CPM_DXIO_TOPOLOGY_TABLE gCpmDxioTopologyTable_RV2 = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_DXIO_TOPOLOGY, sizeof (gCpmDxioTopologyTable_RV2) / sizeof (UINT8), 0, 0, 0x7F003F00, 0x0000000F},
  0,  // SocketId
  {   // DXIO_PORT_DESCRIPTOR
//  { UINT32  Flags;                    /**< Descriptor flags
//    #define DXIO_ENGINE_DATA_INITIALIZER(mType, mStartLane, mEndLane, mHotplug, mGpioGroupId) {mType, mHotplug, 0, mStartLane, mEndLane, mGpioGroupId, 0, 0, 0}
//    #define DXIO_PORT_DATA_INITIALIZER_PCIE(mPortPresent, mDevAddress, mDevFunction, mHotplug, mMaxLinkSpeed, mMaxLinkCap, mAspm, mAspmL1_1, mAspmL1_2,  mClkPmSupport) \
//            {mPortPresent, mDevAddress, mDevFunction, mMaxLinkSpeed, mAspm, mAspmL1_1, mAspmL1_2, 0, mHotplug, {0, mMaxLinkCap, 0, mClkPmSupport}, {0, 0, 0}, DxioEndpointDetect}
    { // DEVICE_ID_MXM                        Entry 0
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 8, 11, HotPluggableDisabled, DEVICE_ID_MXM),
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
        CLK_REQ6                              // CLKREQ#
      )
    },
    { // DEVICE_ID_SSD                        Entry 1
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 0, 1, HotPluggableDisabled, DEVICE_ID_SSD),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        5,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ5                              // CLKREQ#
      )
    },
    { // DEVICE_ID_WLAN                       Entry 2
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 4, 4, HotPluggableDisabled, DEVICE_ID_WLAN),
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
        CLK_REQ0                              // CLKREQ#
      )
    },
    { // DEVICE_ID_LAN                        Entry 3
      0,
      DXIO_ENGINE_DATA_INITIALIZER (DxioPcieEngine, 5, 5, HotPluggableDisabled, DEVICE_ID_LAN),
      DXIO_PORT_DATA_INITIALIZER_PCIE_V2 (
        DxioPortEnabled,                      // Port Present
        1,                                    // Requested Device
        3,                                    // Requested Function
        DxioHotplugDisabled,                  // Hotplug
        DxioGenMaxSupported,                  // Max Link Speed
        DxioGenMaxSupported,                  // Max Link Capability
        DxioAspmL1,                           // DxioAspmL0sL1, // ASPM
        DxioAspmL11Enabled,                   // ASPM L1.1  // 0:disabled, 1:Enabled
        DxioAspmL12Enabled,                   // ASPM L1.2  // 0:disabled, 1:Enabled
        DxioClkPmSupportDisabled,             // Clock PM
        CLK_REQ1                              // CLKREQ#
      )
    },
    { // DEVICE_ID_SATA_EXPRESS               Entry 4
      DESCRIPTOR_TERMINATE_LIST,
      DXIO_ENGINE_DATA_INITIALIZER (DxioSATAEngine, 2, 3, HotPluggableDisabled, 1),
      DXIO_PORT_DATA_INITIALIZER_SATA_V2 (DxioPortEnabled, DxioSataChannelLong)    // Port Present
    }
  },  // End of DXIO_PORT_DESCRIPTOR
  {   // DDI_DESCRIPTOR
    { // DDI0 - DP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeDP, Aux1, Hdp1)
    },
    { // DDI1 - eDP
      0,
      PCIE_DDI_DATA_INITIALIZER (ConnectorTypeEDP, Aux2, Hdp2)
    },
    { // DDI2 - DP
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
  0,                            // UINT8  FunctionDisableMask;  // BIT0: Disable SetSsid. BIT1: Disable AddSsdt
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
  },
  0,                            // UINT16 MacoGpio;         // MACO_EN GPIO pin number for Discrete GPU BxMACO Support          // FCH GPIO 11
  MXM_POWER_ENABLE,             // UINT16 MxmPwrEnGpio;     // MXM_POWER_ENABLE GPIO pin number for Discrete GPU BOMACO Support // FCH GPIO 141
  0,                            // UINT8  TimeMacoUpPwrDn;  // MACO Entry (us): MACO_EN assert to PWR_EN deassert     // Min: 10us
  0,                            // UINT8  TimePwrDnRstDn;   // MACO Entry (ms): PWR_EN deassert to PERSTb assert      // Min: 20ms
  0,                            // UINT8  TimePwrUpRstUp;   // MACO Exit  (ms): PWR_EN assert to PERSTb deassert      // Min: 20ms
  0                             // UINT8  TimeRstUpMacoDn;  // MACO Exit  (ms): PERSTb deassert to MACO_EN deassert   // Min: 1ms
};

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
  ZPODD_PLUGIN_GPIO,    // UINT8 EventPin2;           // Event Pin Number for ODD_PLUGIN#
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
  0x60, // UINT8  EcVersionLocation;// EC UCSI USB Type-C Interface Version Number Offset
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

//
// CPM DT Card Table
//
AMD_CPM_OTHER_HOTPLUG_CARD_TABLE  gCpmDesktopSlotTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table contect
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD, sizeof (gCpmDesktopSlotTable) / sizeof (UINT8), 0, 0, 0, 0x0F},
  1,                    // UINT8 Number;        // Card Number: 0 ~ 2
  DTDEVICE_BRIDGE_DEV,  // UINT8 Device0;       // Device Number of PCIe Bridge for Card 0
  DTDEVICE_BRIDGE_FUN,  // UINT8 Function0;     // Function Number of PCIe Bridge for Card 0
  2,                    // UINT8 EventSource0;  // Event Source for Card 0 - 0: FCH GPIO Pin, 1: KBC GPIO Pin, 2: ECRAM GPIO Pin
  0,                    // UINT8 EventPin0;     // Event Number for Card 0 if EventSource0 = 0
  0x24,                 // UINT8 QEventFalling0;// QEvent Number for Card 0 - FALLING if EventSource0 = 1 or 2
  0x25,                 // UINT8 QEventRising0; // QEvent Number for Card 0 - RISING  if EventSource0 = 1 or 2
  0,                    // UINT8 HotPlugMode0;  // Pcie HotPlug Mode of for Card 0 - 0: Basic Mode, 1: Enhanced Mode
  DEVICE_ID_DT,         // UINT8 DeviceId0;     // Device Id for Card 0
  0xFF,                 // UINT8 Device1;       // Device Number of PCIe Bridge for Card 1
  0xFF,                 // UINT8 Function1;     // Function Number of PCIe Bridge for Card 1
  0xFF,                 // UINT8 EventSource1;  // Event Source for Card 1 - 0: FCH GPIO Pin, 1: KBC GPIO Pin, 2: ECRAM GPIO Pin
  0xFF,                 // UINT8 EventPin1;     // Event Number for Card 1 if EventSource1 = 0
  0xFF,                 // UINT8 QEventFalling1;// QEvent Number for Card 1 - FALLING if EventSource1 = 1 or 2
  0xFF,                 // UINT8 QEventRising1; // QEvent Number for Card 1 - RISING  if EventSource1 = 1 or 2
  0xFF,                 // UINT8 HotPlugMode1;  // Pcie HotPlug Mode of for Card 1 - 0: Basic Mode, 1: Enhanced Mode
  0xFF                  // UINT8 DeviceId1;     // Device Id  for Card 1
};

//
// Low Power Ethernet Table
//
AMD_CPM_LOW_POWER_ETHERNET_TABLE  gCpmLowPowerEthernetTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_PCIE_LOW_POWER_ETHERNET, sizeof (gCpmLowPowerEthernetTable) / sizeof (UINT8), 0, 0, 0, 0x0F},
  1,            // UINT8  Device;                     ///< Device Number of PCIe Bridge for Low Power Ethernet
  3,            // UINT8  Function;                   ///< Function Number of PCIe Bridge for Low Power Ethernet
  0x46,         // UINT8  QEventCablePlugOut;         ///< QEvent Number for Ethernet Cable Plug Out
  0x47,         // UINT8  QEventCablePlugIn;          ///< QEvent Number for Ethernet Cable Plug In
  LAN_LOW_PWR,  // UINT8  LanLowPowerPin;             ///< EC GPIO Pin Number for LAN_LOW_PWR
  DEVICE_ID_LAN // UINT8  DeviceId;                   ///< Device Id for Low Power Ethernet
};

//
// Wireless LAN Recovery Table
//
AMD_CPM_WIRELESS_LAN_RECOVERY_TABLE  gCpmWirelessLanRecoveryTable = {
//{  UINT32 TableSignature;   // Signature of CPM table
//   UINT16 TableSize;        // Table size
//   UINT8  FormatRevision;   // Revision of table format
//   UINT8  ContentRevision;  // Revision of table content
//   UINT32 PlatformMask;     // The mask of platform table supports
//   UINT32 Attribute;        // Table attribute},
  {CPM_SIGNATURE_WIRELESS_LAN_RECOVERY, sizeof (gCpmWirelessLanRecoveryTable) / sizeof (UINT8), 0, 0, 0, 0x0F},
  1,             // UINT8  Device;                     ///< Device Number of PCIe Bridge for Wireless LAN
  2,             // UINT8  Function;                   ///< Function Number of PCIe Bridge for Wireless LAN
  WLAN_RESET,    // UINT8  WlanResetPin;               ///< EC GPIO Pin Number for WLAN_RESET
  DEVICE_ID_WLAN // UINT8  DeviceId;                   ///< Device Id for Wireless LAN
};

UINT32 AzaliaCodecVerbTable[] = {
  0x10EC0701,
  0x00172001, 0x001721D0, 0x00172222, 0x00172310,   // HDA Codec Subsystem ID  : 0x1022D001
  0x0017FF00, 0x0017FF00, 0x0017FF00, 0x0017FF00,   // Widget node 0x01 :
  0x01271C40, 0x01271D01, 0x01271EA6, 0x01271FB7,   // Pin widget 0x12 - DMIC
  0x01371C00, 0x01371D00, 0x01371E00, 0x01371F40,   // Pin widget 0x13 - DMIC
  0x01471C10, 0x01471D01, 0x01471E17, 0x01471F90,   // Pin widget 0x14 - FRONT (Port-D)
  0x01571CF0, 0x01571D11, 0x01571E11, 0x01571F41,   // Pin widget 0x15 - I2S-OUT
  0x01671CF0, 0x01671D11, 0x01671E11, 0x01671F41,   // Pin widget 0x16 - LINE3 (Port-B)
  0x01771CF0, 0x01771D11, 0x01771E11, 0x01771F41,   // Pin widget 0x17 - I2S-OUT
  0x01871CF0, 0x01871D11, 0x01871E11, 0x01871F41,   // Pin widget 0x18 - I2S-IN
  0x01971CF0, 0x01971D11, 0x01971E11, 0x01971F41,   // Pin widget 0x19 - MIC2 (Port-F)
  0x01A71CF0, 0x01A71D11, 0x01A71E11, 0x01A71F41,   // Pin widget 0x1A - LINE1 (Port-C)
  0x01B71C50, 0x01B71D10, 0x01B71EA1, 0x01B71F04,   // Pin widget 0x1B - LINE2 (Port-E)
  0x01D71C01, 0x01D71D00, 0x01D71E60, 0x01D71F40,   // Pin widget 0x1D - PC-BEEP
  0x01E71C30, 0x01E71D11, 0x01E71E45, 0x01E71F04,   // Pin widget 0x1E - S/PDIF-OUT
  0x01F71CF0, 0x01F71D11, 0x01F71E11, 0x01F71F41,   // Pin widget 0x1F - S/PDIF-IN
  0x02171C20, 0x02171D10, 0x02171E21, 0x02171F04,   // Pin widget 0x21 - HP-OUT (Port-I)
  0x02971CF0, 0x02971D11, 0x02971E11, 0x02971F41,   // Pin widget 0x29 - I2S-IN
  0x02050038, 0x02047901, 0x0205006B, 0x02040260,   // NID 0x20 -0 Set Class-D output power as 2.2W@4 Ohm, and MIC2-VREFO-R is controlled by Line2 port.
  0x0205001A, 0x02048C03, 0x02050045, 0x0204B289,   // NID 0x20 - 1
  0x0205004A, 0x0204201B, 0x0205004A, 0x0204201B,   // NID 0x20 - 2
  0x02050010, 0x02040420, 0x01470C00, 0x02050036,   // Dos beep path - 1
  0x02047151, 0x01470740, 0x0143B000, 0x01470C02,   // Dos beep path - 2
  0xFFFFFFFF,                                       // End of 0x10EC0701
  0x10EC0285,
  0x00172002, 0x001721D0, 0x00172222, 0x00172310,   //HDA Codec Subsystem ID  : 0x1022D002
  0x0017FF00, 0x0017FF00, 0x0017FF00, 0x0017FF00,   //Widget node 0x01 :
  0x01271C40, 0x01271D01, 0x01271EA6, 0x01271FB7,   //Pin widget 0x12 - DMIC
  0x01371C00, 0x01371D00, 0x01371E00, 0x01371F40,   //Pin widget 0x13 - DMIC
  0x01471C10, 0x01471D01, 0x01471E17, 0x01471F90,   //Pin widget 0x14 - Front (Port-D)
  0x01671CF0, 0x01671D11, 0x01671E11, 0x01671F41,   //Pin widget 0x16 - NPC
  0x01771CF0, 0x01771D11, 0x01771E11, 0x01771F41,   //Pin widget 0x17 - I2S OUT
  0x01871CF0, 0x01871D11, 0x01871E11, 0x01871F41,   //Pin widget 0x18 - I2S IN
  0x01971CF0, 0x01971D11, 0x01971E11, 0x01971F41,   //Pin widget 0x19 - MIC2 (Port-F)
  0x01A71CF0, 0x01A71D11, 0x01A71E11, 0x01A71F41,   //Pin widget 0x1A - NPC
  0x01B71C30, 0x01B71D90, 0x01B71EA1, 0x01B71F04,   //Pin widget 0x1B - LINE2 (Port-E)
  0x01D71C2D, 0x01D71D19, 0x01D71E66, 0x01D71F40,   //Pin widget 0x1D - BEEP-IN
  0x01E71CF0, 0x01E71D11, 0x01E71E11, 0x01E71F41,   //Pin widget 0x1E - S/PDIF-OUT
  0x02171C20, 0x02171D10, 0x02171E21, 0x02171F04,   //Pin widget 0x21 - HP1-OUT (Port-I)
  0x05C50011, 0x05C40003, 0x05C50011, 0x05C40003,   //disable Silence detect delay turn off
  0x0205003C, 0x0204F254, 0x0205003C, 0x0204F214,   //Class-D power on reset
  0x02050045, 0x0204B009, 0x02050063, 0x02040020,   //Set TRS + turn off MIC2 VREFO gating with HP-JD.
  0x0205004A, 0x020420B0, 0x02050009, 0x02043803,   //Enable HP JD + Set JD2 to 1 port JD for WoV
  0x0205000B, 0x0204777A, 0x0205000B, 0x0204777A,   //Set TRS + Set JD2 pull up.
  0x02050038, 0x02043909, 0x05C50000, 0x05C43482,   //NID 0x20 set class-D to 2W@4ohm (+12dB gain) + Set sine tone gain(0x34)
  0x05350000, 0x0534002A, 0x05350000, 0x0534002A,   //Disable EQ + set 100Hz 2nd High Pass filter 
  0x0535001d, 0x05340800, 0x0535001e, 0x05340800,   //Left Channel-1
  0x05350005, 0x053403F6, 0x05350006, 0x0534854C,   //Left Channel-2
  0x05350007, 0x05341E09, 0x05350008, 0x05346472,   //Left Channel-3
  0x05350009, 0x053401FB, 0x0535000A, 0x05344836,   //Left Channel-4
  0x0535000B, 0x05341C00, 0x0535000C, 0x05340000,   //Left Channel-5
  0x0535000D, 0x05340200, 0x0535000E, 0x05340000,   //Left Channel-6
  0x05450000, 0x05440000, 0x0545001d, 0x05440800,   //Right Channel-1
  0x0545001e, 0x05440800, 0x05450005, 0x054403F6,   //Right Channel-2
  0x05450006, 0x0544854C, 0x05450007, 0x05441E09,   //Right Channel-3
  0x05450008, 0x05446472, 0x05450009, 0x054401FB,   //Right Channel-4
  0x0545000A, 0x05444836, 0x0545000B, 0x05441C00,   //Right Channel-5
  0x0545000C, 0x05440000, 0x0545000D, 0x05440200,   //Right Channel-6
  0x0545000E, 0x05440000, 0x05350000, 0x0534C02A,   //Right Channel-7+ EQ Update & Enable
  0x05D50006, 0x05D44C50, 0x05D50002, 0x05D46004,   //AGC-1 Disable + (Front Gain=0dB )
  0x05D50003, 0x05D45E5E, 0x05D50001, 0x05D4D783,   //AGC-2   (Back Boost Gain= -0.375dB  ,Limiter = -1.125dB)
  0x05D50009, 0x05D451FF, 0x05D50006, 0x05D44E50,   //AGC-3 + AGC Enable
  0x02050010, 0x02040020, 0x02050040, 0x02048800,   //EAPD set to verb-control.
  0x02050030, 0x02049000, 0x02050037, 0x0204FE15,   //Class D silent detection Enable -84dB threshold
  0x05B50006, 0x05B40044, 0x05A50001, 0x05A4001F,   //Set headphone gain and Set pin1 to GPIO2
  0xFFFFFFFF,                                       // End of 0x10EC0701
  0xFFFFFFFF, 0xFFFFFFFF                            // End of AzaliaCodecVerbTable
};

UINT8 HdmiRetimerRedriver[] = {
    0xBA, // HdmiSlvAddr
    0x03, // HdmiRegNum
    0x03, // Hdmi6GRegNum
    0x0A, 0x13,  // HdmiRegSetting[0].ucI2cRegIndex , HdmiRegSetting[0].ucI2cRegVal
    0x0B, 0xC8,  // HdmiRegSetting[1].ucI2cRegIndex , HdmiRegSetting[1].ucI2cRegVal
    0x0C, 0x91,  // HdmiRegSetting[2].ucI2cRegIndex , HdmiRegSetting[2].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[3].ucI2cRegIndex , HdmiRegSetting[3].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[4].ucI2cRegIndex , HdmiRegSetting[4].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[5].ucI2cRegIndex , HdmiRegSetting[5].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[6].ucI2cRegIndex , HdmiRegSetting[6].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[7].ucI2cRegIndex , HdmiRegSetting[7].ucI2cRegVal
    0x00, 0x00,  // HdmiRegSetting[8].ucI2cRegIndex , HdmiRegSetting[8].ucI2cRegVal
    0x0A, 0x13,  // Hdmi6GhzRegSetting[0].ucI2cRegIndex , Hdmi6GhzRegSetting[0].ucI2cRegVal
    0x0B, 0xDA,  // Hdmi6GhzRegSetting[1].ucI2cRegIndex , Hdmi6GhzRegSetting[1].ucI2cRegVal
    0x0C, 0x1D   // Hdmi6GhzRegSetting[2].ucI2cRegIndex , Hdmi6GhzRegSetting[2].ucI2cRegVal
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
 * @param[in]     CurrentBoardId                Current Board ID
 *
 */
VOID
DetectPcieDevices (
  IN       AMD_CPM_TABLE_PPI            *AmdCpmTablePpi,
  IN       AMD_CPM_DXIO_TOPOLOGY_TABLE  *DxioTopologyTablePtr,
  IN       AMD_PBS_SETUP_OPTION         *AmdPbsConfiguration,
  IN OUT   UINT8                        *TravisStatus,
  IN       UINT16                       CurrentBoardId
  )
{
  EFI_STATUS              Status;
  DXIO_PORT_DESCRIPTOR    *PciePort;
  DDI_DESCRIPTOR          *DdiPort;
  UINT8                   ConnectorType,Index;
  UINT8                   SmbusSlaveAddress;
  UINTN                   DdiIndex;
//  UINTN                   PciePortIndex;
  UINT16                  OriginalBoardId;
  UINT32                  *TableAddress;

  PciePort = &(DxioTopologyTablePtr->Port[0]);
  DdiPort = &(DxioTopologyTablePtr->Ddi[0]);

  DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-Start\n"));
//  if ((!MxmPresent (AmdCpmTablePpi)) && (AmdPbsConfiguration->EvalAutoDetection == 1)) {
//    // Disable GFX x8 port
//    for (PciePortIndex = 0; PciePortIndex < AMD_PCIE_PORT_DESCRIPTOR_SIZE; PciePortIndex ++) {
//      if (PciePort[PciePortIndex].Port.ResetId == DEVICE_ID_MXM) {
//        PciePort[PciePortIndex].Port.PortPresent = PortDisabled;
//        break;
//      }
//    }
//  }

  OriginalBoardId = PcdGet16 (OriginalPlatformId);

  if (OriginalBoardId & BIT2) { // OriginalBoardId BIT2 = 1 is Tambourine
    DEBUG((DEBUG_INFO, "Tambourine board\n"));
    DdiPort[1].Ddi.ConnectorType = ConnectorTypeHDMI;
    Index =1 ;
  } else{
    DEBUG((DEBUG_INFO, "Mandolin board\n"));
    Index =2 ;
  }

  DdiIndex = 0;
  if (AmdPbsConfiguration->TouchPad == 3) {
    /*
     * (TouchPad == 3) means the TouchPad is attached on I2C2.
     * Skip to detect DDI ports 0, just leave it as default
     */
    DdiIndex = 1;
  }

  *TravisStatus = 0;
  // Update DDI information
  for ( ; DdiIndex < Index; DdiIndex++) {
    SmbusSlaveAddress = (UINT8) ((0x40 + DdiIndex * 2) >> 1);
    DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-ReadSmbus-SmbusSlaveAddress = 0x%X DdiIndex = 0x%X\n", SmbusSlaveAddress, DdiIndex));
    // Workaround for system shows blackscreen when POST and under OS intermittently (PLAT-2984) >>>>
    SetSmBusPort(AmdCpmTablePpi);
    // The Semaphore allocated by SetSmBusPort() will be released in SmBusExecute() by following function call.
    // End of the workaround <<<<
    Status = AmdCpmTablePpi->CommonFunction.ReadSmbus (AmdCpmTablePpi, 0, SmbusSlaveAddress, 0, 1, &ConnectorType);
    if (!EFI_ERROR (Status)) {
      DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-ReadSmbus-SmbusSlaveAddress = 0x%X DdiIndex = 0x%X ConnectorType = 0x%X\n", SmbusSlaveAddress, DdiIndex, ConnectorType));
      switch (ConnectorType) {
      case 0x10:
      case 0x90:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x10-0x90-ConnectorTypeDP\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeDP;
        break;
      case 0x20:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x20-ConnectorTypeSingleLinkDVI\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeSingleLinkDVI;
        break;
      case 0x30:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x30-ConnectorTypeHDMI\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeHDMI;
        break;
      case 0x31:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x31-ConnectorTypeHDMI-EXT_DISPLAY_PATH_CAPS_HDMI20_TISN65DP159RSBT\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeHDMI;
        DdiPort[DdiIndex].Ddi.Flags |= EXT_DISPLAY_PATH_CAPS_HDMI20_TISN65DP159RSBT;  // HDMI 2.0 re-timer
        break;
      case 0x38:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x38-ConnectorTypeHDMI-EXT_DISPLAY_PATH_CAPS_HDMI20_PI3EQX1204\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeHDMI;
        DdiPort[DdiIndex].Ddi.Flags |= EXT_DISPLAY_PATH_CAPS_HDMI20_PI3EQX1204;       // HDMI 2.0 re-driver
        break;
      case 0x08:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x08-ConnectorTypeDP-EXT_DISPLAY_PATH_CAPS_HDMI20_PARADE_PS175\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeDP;
        DdiPort[DdiIndex].Ddi.Flags |= EXT_DISPLAY_PATH_CAPS_HDMI20_PARADE_PS175;     // HDCP 2.2 converter
        break;
      case 0x40:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x40-ConnectorTypeDualLinkDVI\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeDualLinkDVI;
        break;
      case 0x50:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x50-ConnectorTypeEDP\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeEDP;
        break;
      case 0x60:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x60-ConnectorTypeDpToLvds\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeDpToLvds;                  // LVDS Travis
        *TravisStatus |= BIT0;
        break;
      case 0x64:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x64-ConnectorTypeEDPToLvdsSwInit\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeEDPToLvdsSwInit;           // LVDS Realtek
        break;
      case 0x70:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-0x70-ConnectorTypeAutoDetect\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = ConnectorTypeAutoDetect;
        break;
      default:
        DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-default-Keep the default DDI setting\n"));
        DdiPort[DdiIndex].Ddi.ConnectorType = UnusedType;
        break;
      }
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-ReadSmbus-SmbusSlaveAddress = 0x%X DdiIndex = 0x%X ERROR ERROR ERROR\n", SmbusSlaveAddress, DdiIndex));
      DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-Not-PcdSimpleSltSupport-ConnectorTypeAutoDetect\n"));
      if (!PcdGet8 (PcdSimpleSltSupport)) {
        DdiPort[DdiIndex].Ddi.ConnectorType = UnusedType;
      }
    }
  }

  for (DdiIndex = 0; DdiIndex < Index; DdiIndex++) {
    if (DdiPort[DdiIndex].Ddi.ConnectorType == ConnectorTypeHDMI) {
      switch (DdiIndex) {
        case 0:
          DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-Updtae-ReTimer-Setting-DDI%x\n", DdiIndex));
          TableAddress = (UINT32 *)&HdmiRetimerRedriver[0];
          PcdSet32 (PcdCfgDp0RetimerRedriverTable, (UINT32)TableAddress);                  
          break;

        case 1:
          DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-Updtae-ReTimer-Setting-DDI%x\n", DdiIndex));
          TableAddress = (UINT32 *)&HdmiRetimerRedriver[0];
          PcdSet32 (PcdCfgDp1RetimerRedriverTable, (UINT32)TableAddress);
          break;

        case 2:
          DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-Updtae-ReTimer-Setting-DDI%x\n", DdiIndex));
          TableAddress = (UINT32 *)&HdmiRetimerRedriver[0];
          PcdSet32 (PcdCfgDp2RetimerRedriverTable, (UINT32)TableAddress);
          break;

        default:
          break;
      }
    }
  }

  if (AmdPbsConfiguration->HdmiOverUsbTypeC0 == 1) {
    DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-HdmiOverUsbTypeC0 = 1 - ConnectorTypeHDMI\n"));
    DdiPort[2].Ddi.ConnectorType = ConnectorTypeHDMI;
  }

  if (AmdPbsConfiguration->HdmiOverUsbTypeC1 == 1) {
    DEBUG((DEBUG_INFO, "OEM-PEI-DetectPcieDevices-HdmiOverUsbTypeC1 = 1 - ConnectorTypeHDMI\n"));
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {    // RV board only, not for RV2 board
      DdiPort[3].Ddi.ConnectorType = ConnectorTypeHDMI;
    }
  }

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
  IN       EFI_PEI_SERVICES           **PeiServices
  )
{
  EFI_STATUS                          Status;
  AMD_CPM_TABLE_PPI                   *AmdCpmTablePpi;
  AMD_CPM_MAIN_TABLE                  *MainTablePtr;
  AMD_CPM_PCIE_CLOCK_TABLE            *PcieClockTablePtr;
  AMD_CPM_DXIO_TOPOLOGY_TABLE         *DxioTopologyTablePtr;
  AMD_CPM_GPIO_DEVICE_CONFIG_TABLE    *GpioDeviceConfigTablePtr;
  AMD_CPM_OTHER_HOTPLUG_CARD_TABLE    *DtHotplugTablePtr;
  AMD_CPM_GPIO_DEVICE_POWER_TABLE     *PowerTablePtr;
  AMD_PBS_SETUP_OPTION                AmdPbsConfiguration;
  AMD_CPM_GPIO_INIT_TABLE             *GpioInitTablePtr;
  AMD_CPM_DISPLAY_FEATURE_TABLE       *DisplayFeatureTablePtr;
  AMD_CPM_LOW_POWER_ETHERNET_TABLE    *LowPowerEthernetTablePtr;
  AMD_CPM_DEVICE_PATH_TABLE           *DevicePathTablePtr;
  AMD_CPM_GEVENT_INIT_TABLE           *GeventTablePtr;
  AMD_CPM_WIRELESS_LAN_RECOVERY_TABLE *WirelessLanRecoveryTablePtr;
  UINTN                               Index;
  UINT16                              CurrentBoardId;
  UINT8                               TravisStatus;
  DXIO_PORT_DESCRIPTOR                *DxioPort;
  UINT32                              DeviceEnableMap;
  UINT16                              OriginalBoardId;
  BOOLEAN                             Tambourine;
  UINT32                              *TableAddress;
  UINT8                               Value8;
  UINT8                               Offset;
  UINT8                               Value8_1;
  UINT8                               Index8;
  UINT32                              ECFwVersion;
  UINT16                              USBPDFwVersion;
  UINT32                              Value32;
  ATOM_14NM_DPPHY_DP_SETTING          *DpPtr;
  ATOM_14NM_DPPHY_DP_SETTING          *TempDpPtr;
  UINT32                              Count;

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Start\n"));
  Index = 0;
  TravisStatus = 0;

  I2cTouchDeviceIntGpioInit ();

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

  MainTablePtr = AmdCpmTablePpi->MainTablePtr;
  // Get CurrentBoardId
  CurrentBoardId = PcdGet16 (CurrentPlatformId);
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-CurrentBoardId=%04X\n", CurrentBoardId));

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-GetAmdPbsConfiguration\n"));
  Status = GetAmdPbsConfiguration (&AmdPbsConfiguration);
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-End-2-Status=%r\n", Status));
    return Status;
  }

  // Get CurrentBoardId
  OriginalBoardId = PcdGet16 (OriginalPlatformId);
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-OriginalBoardId=%04X\n", OriginalBoardId));

  if (OriginalBoardId & BIT2) { // OriginalBoardId BIT2 = 1 is Tambourine
    Tambourine = 1 ;
    DEBUG((DEBUG_INFO, "Tambourine Board\n"));
  } else{
    Tambourine = 0 ;
    DEBUG((DEBUG_INFO, "Mandolin Board\n"));
  }

  DxioTopologyTablePtr        = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_DXIO_TOPOLOGY);
  PcieClockTablePtr           = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_PCIE_CLOCK);
  GpioDeviceConfigTablePtr    = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GPIO_DEVICE_CONFIG);
  DtHotplugTablePtr           = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD);
  PowerTablePtr               = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GPIO_DEVICE_POWER);
  GpioInitTablePtr            = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GPIO_INIT);
  DisplayFeatureTablePtr      = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_DISPLAY_FEATURE);
  LowPowerEthernetTablePtr    = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_PCIE_LOW_POWER_ETHERNET);
  WirelessLanRecoveryTablePtr = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_WIRELESS_LAN_RECOVERY);
  DevicePathTablePtr          = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_DEVICE_PATH);
  GeventTablePtr              = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_GEVENT_INIT);

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

  // Raven Telemetry Slope/Offset (BIOS to SMU)
  if (( OriginalBoardId & 0x1D ) == BIT2) {                     // Tambourine
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 125000);  // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25600);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Tambourine\n"));
  } else if (( OriginalBoardId & 0x1D ) == 0) {                 // Mandolin
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 132000);  // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Mandolin\n"));
  } else if (( OriginalBoardId & 0x1D ) == BIT3) {              // Mandolin DAP
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 132000);  // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Mandolin DAP\n"));
  } else if (( OriginalBoardId & 0x1D ) == (BIT3 + BIT4)) {     // Mandolin DAP2
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 74000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25600);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Mandolin DAP2\n"));
  } else if (( OriginalBoardId & 0x1D ) == BIT4) {              // Mandolin 2PHASE board
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 74000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Mandolin 2PHASE board\n"));
  } else if (( OriginalBoardId & 0x1D ) == (BIT2 + BIT4)) {     // Tambourine 2PHASE board
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 74000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Tambourine 2PHASE board\n"));
  } else if (( OriginalBoardId & 0x1D ) == (BIT0 + BIT3 + BIT4)) {  // Picasso-Mandolin DAP board-VDD-2phase
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 76000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25600);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Picasso-Mandolin DAP board-VDD-2phase\n"));
  } else if (( OriginalBoardId & 0x1D ) == (BIT0 + BIT4)) {     // Picasso-Mandolin board-VDD-2phase
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 76000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25600);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Picasso-Mandolin board-VDD-2phase\n"));
  } else if (( OriginalBoardId & 0x1D ) == (BIT0 + BIT2 + BIT4)) {  // Picasso-Tamborine Board-VDD-2phase
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 76000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25600);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Picasso-Tamborine Board-VDD-2phase\n"));
  } else if (( OriginalBoardId & 0x1D ) == BIT0) {              // Picasso-Mandolin board-VDD-3phase
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 132000);  // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Picasso-Mandolin board-VDD-3phase\n"));
  } else if (( OriginalBoardId & 0x1D ) == (BIT0 + BIT2)) {    // Picasso-Tambourine Board-VDD-3phase
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 125000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25600);   // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Picasso-Tambourine Board-VDD-3phase\n"));          
  } else if (( OriginalBoardId & 0x1D ) == (BIT0 + BIT3)) {      // Picasso-Mandolin DAP board-VDD-3phase
    PcdSet32(PcdTelemetry_VddcrVddfull_Scale_Current, 132000);   // mA
    PcdSet32(PcdTelemetry_VddcrVddOffset, 0);
    PcdSet32(PcdTelemetry_VddcrSocfull_Scale_Current, 25000);    // mA
    PcdSet32(PcdTelemetry_VddcrSocOffset, 0);
    DEBUG((DEBUG_INFO, "Telemetry Slope/Offset : Picasso-Mandolin DAP board-VDD-3phase\n"));
  } else {
    DEBUG((DEBUG_INFO, "Unknown Board\n"));
  }

  DeviceEnableMap = PcdGet32 (FchRTDeviceEnableMap);
  if ((FixedPcdGet8 (PcdFchUartPort) == 0) || (PcdGet64 (PcdSerialRegisterBase) == 0xFEDC9000) || (PcdGet64 (PcdAmdIdsDebugPrintSerialPort) == 0xFEDC9000)) {
    DeviceEnableMap |= BIT11;
    PcdSet32(FchRTDeviceEnableMap, DeviceEnableMap);
  }
  if ((AmdPbsConfiguration.NfcSensor >= 1) && ((DeviceEnableMap & (UINT32) BIT11) == BIT11)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (NfcSensor>=1 & DeviceEnableMap BIT11=1)\n"));
    DeviceEnableMap &= ~(UINT32) BIT11;               // # BIT11 = 0 disable UART0
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

  DEBUG ((EFI_D_INFO, "-->  AmdPbsConfiguration.amdAcDcSwitch = 0x%x\n", AmdPbsConfiguration.amdAcDcSwitch));
  DEBUG ((EFI_D_INFO, "-->  AmdPbsConfiguration.amdDcTimer = 0x%x\n", AmdPbsConfiguration.amdDcTimer));
  DEBUG ((EFI_D_INFO, "-->  AmdPbsConfiguration.amdAcTimer = 0x%x\n", AmdPbsConfiguration.amdAcTimer));


  Offset = EC_STATUS_INDEX;
  AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);

  Value8 &= ~(1<<1);           //Set BIT1 to 0
  Value8 |= (AmdPbsConfiguration.amdAcDcSwitch << 1);
  AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

  if (AmdPbsConfiguration.amdAcDcSwitch) {
    Offset = TIEC_DC_TIMER;
    Value8 = AmdPbsConfiguration.amdDcTimer;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = TIEC_AC_TIMER;
    Value8 = AmdPbsConfiguration.amdAcTimer;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);
  }

  // Display Features
  MainTablePtr->DisplayFeature.Config.D3ColdSupport = (AmdPbsConfiguration.D3ColdSupport == 1) ? 1 : 0;
  MainTablePtr->DisplayFeature.Config.HybridGraphicsSupport = (AmdPbsConfiguration.SpecialVgaFeature == 4) ? 1 : 0;
  if ((MainTablePtr->DisplayFeature.Config.D3ColdSupport == 0) && (MainTablePtr->DisplayFeature.Config.HybridGraphicsSupport == 0)) {
    MainTablePtr->DisplayFeature.Config.DgpuHotPlugMode = 0;
    MainTablePtr->DisplayFeature.Config.PmeTurnOffSupport = 0;
  } else {
    MainTablePtr->DisplayFeature.Config.DgpuHotPlugMode = (AmdPbsConfiguration.DgpuHotPlugMode == 1) ? 1 : 0;
    MainTablePtr->DisplayFeature.Config.PmeTurnOffSupport = (AmdPbsConfiguration.PmeTurnOffSupport == 1) ? 1 : 0;
  }
  MainTablePtr->DisplayFeature.Config.DgpuD3ColdHpdSupport = (AmdPbsConfiguration.DgpuD3ColdHpdSupport == 1) ? 1 : 0;
  MainTablePtr->DisplayFeature.Config.PulseGeneratorSupport = (AmdPbsConfiguration.DgpuHpdCircuitry == 1) ? 1 : 0;
  MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX = (AmdPbsConfiguration.DgpuAudio == 0) ? 1 : 0;
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-D3ColdSupport = %X\n", MainTablePtr->DisplayFeature.Config.D3ColdSupport));
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-HybridGraphicsSupport = %X\n", MainTablePtr->DisplayFeature.Config.HybridGraphicsSupport));
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DgpuHotPlugMode = %X\n", MainTablePtr->DisplayFeature.Config.DgpuHotPlugMode));
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DgpuD3ColdHpdSupport = %X\n", MainTablePtr->DisplayFeature.Config.DgpuD3ColdHpdSupport));
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PmeTurnOffSupport = %X\n", MainTablePtr->DisplayFeature.Config.PmeTurnOffSupport));
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PulseGeneratorSupport = %X\n", MainTablePtr->DisplayFeature.Config.PulseGeneratorSupport));
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DisableDgpuAudioInPX = %X\n", MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX));

  if (AmdPbsConfiguration.DgpuMaco == 1) {
    DisplayFeatureTablePtr->MacoGpio = MACO_EN;
    DisplayFeatureTablePtr->TimeMacoUpPwrDn = (AmdPbsConfiguration.TimeMacoUpPwrDn <= 9) ? 1 : (AmdPbsConfiguration.TimeMacoUpPwrDn - 8);
    DisplayFeatureTablePtr->TimePwrDnRstDn  = AmdPbsConfiguration.TimePwrDnRstDn;
    DisplayFeatureTablePtr->TimePwrUpRstUp  = AmdPbsConfiguration.TimePwrUpRstUp;
    DisplayFeatureTablePtr->TimeRstUpMacoDn = AmdPbsConfiguration.TimeRstUpMacoDn;
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-MacoGpio        = %d\n",    DisplayFeatureTablePtr->MacoGpio));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-TimeMacoUpPwrDn = %d us\n", DisplayFeatureTablePtr->TimeMacoUpPwrDn));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-TimePwrDnRstDn  = %d ms\n", DisplayFeatureTablePtr->TimePwrDnRstDn));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-TimePwrUpRstUp  = %d ms\n", DisplayFeatureTablePtr->TimePwrUpRstUp));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-TimeRstUpMacoDn = %d ms\n", DisplayFeatureTablePtr->TimeRstUpMacoDn));
  }

  if (AmdPbsConfiguration.NonEvalDgpuSupport) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (NonEvalDgpuSupport)\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Set NonEvalDgpuSupport to 1\n"));
    MainTablePtr->DisplayFeature.Config.NonEvalDgpuSupport = 1;
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_MXM, CPM_DEVICE_ON);
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

  // ZP-ODD
  if (AmdPbsConfiguration.ZeroPowerOddEn) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-if (ZeroPowerOddEn)\n"));
    //ZeroPowerOddEn, OddHotplugEn & Enable _PRW
    MainTablePtr->ZeroPowerOddEn = BIT0 | BIT1 | BIT2 | BIT3;
  }

  // UCSI Support
  MainTablePtr->UcsiEn            = AmdPbsConfiguration.UcsiEn;

#ifdef MODERN_STANDBY_SUPPORT
  // Modern Standby Support
  MainTablePtr->ModernStandbyEn   = AmdPbsConfiguration.ReduceHardwareEn;
#endif

  // Sensor Fusion User Mode Driver
  MainTablePtr->SensorFusionEn    = AmdPbsConfiguration.SensorFusionEn;

  // Clock control
  MainTablePtr->UnusedGppClkOffEn = AmdPbsConfiguration.UnusedGppClkOff;

  // Device control
  DxioPort = &(DxioTopologyTablePtr->Port[0]);

  if (OriginalBoardId & BIT1) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClkReqReworkBoard\n"));
    for (Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++) {
      if (DxioPort[Index].EngineData.GpioGroupId == DEVICE_ID_MXM) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioOverride-MXM-CLK_REQ3\n"));
        DxioPort[Index].Port.ClkReq = CLK_REQ3;
      }
      if (DxioPort[Index].EngineData.GpioGroupId == DEVICE_ID_SSD) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioOverride-SSD-CLK_REQ2\n"));
        DxioPort[Index].Port.ClkReq = CLK_REQ2;
      }
      if (DxioPort[Index].EngineData.GpioGroupId == DEVICE_ID_WIFI) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioOverride-WIFI-CLK_REQ6\n"));
        DxioPort[Index].Port.ClkReq = CLK_REQ6;
        DxioPort[Index].Port.PortPresent = DxioPortDisabled;
      }
      if (DxioPort[Index].EngineData.GpioGroupId == DEVICE_ID_WWAN) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioOverride-WIFI-CLK_REQ5\n"));
        DxioPort[Index].Port.ClkReq = CLK_REQ5;
        DxioPort[Index].Port.PortPresent = DxioPortDisabled;
      }
    }
    Index = 0;
    while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
      if (PcieClockTablePtr->Item[Index].DeviceId == DEVICE_ID_MXM) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClkOverride-MXM-ClkId:%x, ClkReq:%x\n", GPP_CLK3, CLK_REQ3));
        PcieClockTablePtr->Item[Index].ClkId = GPP_CLK3;
        PcieClockTablePtr->Item[Index].ClkReq = CLK_REQ3;
      }
      if (PcieClockTablePtr->Item[Index].DeviceId == DEVICE_ID_SSD) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClkOverride-SSD-ClkId:%x, ClkReq:%x\n", GPP_CLK2, CLK_REQ2));
        PcieClockTablePtr->Item[Index].ClkId = GPP_CLK2;
        PcieClockTablePtr->Item[Index].ClkReq = CLK_REQ2;
      }
      if (PcieClockTablePtr->Item[Index].DeviceId == DEVICE_ID_WIFI) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClkOverride-WIFI-ClkId:%x, ClkReq:%x\n", GPP_CLK6, CLK_REQ6));
        PcieClockTablePtr->Item[Index].ClkId = GPP_CLK6;
        PcieClockTablePtr->Item[Index].ClkReq = CLK_REQ6;
      }
      if (PcieClockTablePtr->Item[Index].DeviceId == DEVICE_ID_WWAN) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClkOverride-WWAB-ClkId:%x, ClkReq:%x\n", GPP_CLK5, CLK_REQ5));
        PcieClockTablePtr->Item[Index].ClkId = GPP_CLK5;
        PcieClockTablePtr->Item[Index].ClkReq = CLK_REQ5;
      }
      Index++;
    }
  }

  // Notify EC to change power control by HW Jump
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Notify EC to change power control by HW Jump\n"));
  if (AmdPbsConfiguration.WlanPowerControl == 2) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WlanPowerControl = Manual\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 1\n", WLAN_Manual_EN));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, WLAN_Manual_EN , 1);
  } else {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WlanPowerControl != Manual\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 0\n", WLAN_Manual_EN));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, WLAN_Manual_EN , 0);
  }

  if (AmdPbsConfiguration.LanPowerControl == 2) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanPowerControl = Manual\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 1\n", LAN_Manual_EN));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, LAN_Manual_EN , 1);
  } else {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanPowerControl != Manual\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 0\n", LAN_Manual_EN));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, LAN_Manual_EN , 0);
  }

  if (AmdPbsConfiguration.WwanPowerEn == 2) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Manual\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 1\n", WWAN_Manual_EN));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, WWAN_Manual_EN , 1);
  } else {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn != Manual\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 0\n", WWAN_Manual_EN));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, WWAN_Manual_EN , 0);
  }

  if (AmdPbsConfiguration.DtSlotPowerControl == 0) {
    // DT Slot is disabled
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl = Disabled\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_DT = CPM_DEVICE_OFF\n"));
    DxioPort[2].Port.PortPresent          = DxioPortEnabled;
    DxioPort[2].EngineData.EngineType     = DxioPcieEngine;
    DxioPort[3].Port.PortPresent          = DxioPortEnabled;
    DxioPort[3].EngineData.EngineType     = DxioPcieEngine;
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {                          // RV board only, not for RV2 board
      DxioPort[4].Port.PortPresent        = DxioPortEnabled;
      DxioPort[4].EngineData.EngineType   = DxioPcieEngine;
      DxioPort[5].Port.PortPresent        = DxioPortEnabled;
      DxioPort[5].EngineData.EngineType   = DxioPcieEngine;
    }
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_DT, CPM_DEVICE_OFF);

    // DEVICE_ID_WLAN & DEVICE_ID_WIFI
    if (AmdPbsConfiguration.WlanPowerControl != 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WlanPowerControl = Enabled\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WLAN = CPM_DEVICE_ON\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WLAN, CPM_DEVICE_ON);
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WlanPowerControl = Disabled\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WLAN = CPM_DEVICE_OFF\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WLAN, CPM_DEVICE_OFF);
    }

    // DEVICE_ID_LAN
    if (AmdPbsConfiguration.LanPowerControl != 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanPowerControl = Enabled\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_LAN = CPM_DEVICE_ON\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_LAN, CPM_DEVICE_ON);
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanPowerControl = Disabled\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_LAN = CPM_DEVICE_OFF\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_LAN, CPM_DEVICE_OFF);
    }

    // DEVICE_ID_WWAN
    if (Tambourine) {
      // Tambourine only
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Disabled (Tambourine no WWAN)\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
    } else {
      // Mandolin only
      if (AmdPbsConfiguration.WwanPowerEn != 0) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Enabled (Mandolin)\n"));
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_ON\n"));
        SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_ON);
      } else {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Disabled (Mandolin)\n"));
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
        SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
      }
    }

  } else if (AmdPbsConfiguration.DtSlotPowerControl == 1) {
    // DT Slot is enabled and set to X4
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl = Enabled & X4\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_DT = CPM_DEVICE_ON\n"));
    DxioPort[2].Port.PortPresent          = DxioPortEnabled;
    DxioPort[2].EngineData.EngineType     = DxioPcieEngine;
    DxioPort[2].Port.ClkReq               = CLK_REQ4;
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {                          // RV board only, not for RV2 board
      DxioPort[2].EngineData.EndLane      = 7;
    } else {
      DxioPort[2].EngineData.EndLane      = 5;
    }
    DxioPort[2].EngineData.GpioGroupId    = DEVICE_ID_DT;
    DxioPort[3].Port.PortPresent          = DxioPortDisabled;
    DxioPort[3].EngineData.EngineType     = DxioUnusedEngine;
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {                          // RV board only, not for RV2 board
      DxioPort[4].Port.PortPresent        = DxioPortDisabled;
      DxioPort[4].EngineData.EngineType   = DxioUnusedEngine;
      DxioPort[5].Port.PortPresent        = DxioPortDisabled;
      DxioPort[5].EngineData.EngineType   = DxioUnusedEngine;
    }
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_DT, CPM_DEVICE_ON);

    // DEVICE_ID_WLAN & DEVICE_ID_WIFI
    // DEVICE_ID_LAN
    // DEVICE_ID_WWAN
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WLAN = CPM_DEVICE_OFF\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WLAN, CPM_DEVICE_OFF);
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_LAN = CPM_DEVICE_OFF\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_LAN, CPM_DEVICE_OFF);
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
  } else if (AmdPbsConfiguration.DtSlotPowerControl == 2) {
    // DT Slot is enabled and set to X2
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl = Enabled & X2\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_DT = CPM_DEVICE_ON\n"));
    DxioPort[2].Port.PortPresent          = DxioPortEnabled;
    DxioPort[2].EngineData.EngineType     = DxioPcieEngine;
    DxioPort[2].Port.ClkReq               = CLK_REQ4;
    DxioPort[2].EngineData.EndLane        = 5;
    DxioPort[2].EngineData.GpioGroupId    = DEVICE_ID_DT;
    DxioPort[3].Port.PortPresent          = DxioPortDisabled;
    DxioPort[3].EngineData.EngineType     = DxioUnusedEngine;
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {    // RV board only, not for RV2 board
      if (Tambourine) { // Tambourine hardwired GPP2,GPP3 to DT slot.
        DxioPort[4].Port.PortPresent      = DxioPortDisabled;
        DxioPort[4].EngineData.EngineType = DxioUnusedEngine;
        DxioPort[5].Port.PortPresent      = DxioPortDisabled;
        DxioPort[5].EngineData.EngineType = DxioUnusedEngine;
      } else {
        DxioPort[4].Port.PortPresent      = DxioPortEnabled;
        DxioPort[4].EngineData.EngineType = DxioPcieEngine;
        DxioPort[5].Port.PortPresent      = DxioPortEnabled;
        DxioPort[5].EngineData.EngineType = DxioPcieEngine;
      }
    }
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_DT, CPM_DEVICE_ON);

    // DEVICE_ID_WLAN & DEVICE_ID_WIFI
    // DEVICE_ID_LAN
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WLAN = CPM_DEVICE_OFF\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WLAN, CPM_DEVICE_OFF);
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_LAN = CPM_DEVICE_OFF\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_LAN, CPM_DEVICE_OFF);
    // DEVICE_ID_WWAN
    if (Tambourine) {
      // Tambourine only
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Disabled (Tambourine no WWAN)\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
    } else {
      // Mandolin only
      if (AmdPbsConfiguration.WwanPowerEn != 0) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Enabled (Mandolin)\n"));
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_ON\n"));
        SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_ON);
      } else {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Disabled (Mandolin)\n"));
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
        SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
      }
    }
  } else if (AmdPbsConfiguration.DtSlotPowerControl == 3) {
    // DT Slot is enabled and set to X1
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl = Enabled & X1\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_DT = CPM_DEVICE_ON\n"));
    DxioPort[2].Port.PortPresent          = DxioPortEnabled;
    DxioPort[2].EngineData.EngineType     = DxioPcieEngine;
    DxioPort[2].Port.ClkReq               = CLK_REQ4;
    DxioPort[2].EngineData.GpioGroupId    = DEVICE_ID_DT;
    DxioPort[3].Port.PortPresent          = DxioPortEnabled;
    DxioPort[3].EngineData.EngineType     = DxioPcieEngine;
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {                          // RV board only, not for RV2 board
      if (Tambourine) { // Tambourine hardwired GPP2,GPP3 to DT slot.
        DxioPort[4].Port.PortPresent      = DxioPortDisabled;
        DxioPort[4].EngineData.EngineType = DxioUnusedEngine;
        DxioPort[5].Port.PortPresent      = DxioPortDisabled;
        DxioPort[5].EngineData.EngineType = DxioUnusedEngine;
      } else {
        DxioPort[4].Port.PortPresent      = DxioPortEnabled;
        DxioPort[4].EngineData.EngineType = DxioPcieEngine;
        DxioPort[5].Port.PortPresent      = DxioPortEnabled;
        DxioPort[5].EngineData.EngineType = DxioPcieEngine;
      }
    }
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_DT, CPM_DEVICE_ON);

    // DEVICE_ID_WLAN & DEVICE_ID_WIFI
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WLAN = CPM_DEVICE_OFF\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WLAN, CPM_DEVICE_OFF);

    // DEVICE_ID_LAN
    if (AmdPbsConfiguration.LanPowerControl != 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanPowerControl = Enabled\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_LAN = CPM_DEVICE_ON\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_LAN, CPM_DEVICE_ON);
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanPowerControl = Disabled\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_LAN = CPM_DEVICE_OFF\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_LAN, CPM_DEVICE_OFF);
    }

    // DEVICE_ID_WWAN
    if (Tambourine) {
      // Tambourine only
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Disabled (Tambourine no WWAN)\n"));
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
      SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
    } else {
      // Mandolin only
      if (AmdPbsConfiguration.WwanPowerEn != 0) {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Enabled (Mandolin)\n"));
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_ON\n"));
        SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_ON);
      } else {
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WwanPowerEn = Disabled (Mandolin)\n"));
        DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDevice-DEVICE_ID_WWAN = CPM_DEVICE_OFF\n"));
        SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_WWAN, CPM_DEVICE_OFF);
      }
    }
  }

  // Lan Low Power Mode
  if (((AmdPbsConfiguration.LanPowerControl != 0) && (AmdPbsConfiguration.LanLowPowerMode != 0)) && (!Tambourine)) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanLowPowerMode = Enabled\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Notify EC the LPM is enabled\n"));
    // Disable LAN_LOW_PWR - ECRAM xB0[7](BIT39)
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, (0x200 + LAN_LOW_PWR), 0);
    // Enable LAN_LOW_PWR_EN - ECRAM xB7[0](BIT88)
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, (0x200 + LAN_LOW_PWR_EN), 1);
    if (LowPowerEthernetTablePtr) {
      if (DxioTopologyTablePtr) {
        for (Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++) {
          if (DxioPort[Index].EngineData.GpioGroupId == LowPowerEthernetTablePtr->DeviceId) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Find DeviceId = 0x%X\n", LowPowerEthernetTablePtr->DeviceId));
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Set HotplugEnhanced\n"));
            DxioPort[Index].Port.LinkHotplug  = HotplugEnhanced;
            continue;
          }
        }
      }
      if (PcieClockTablePtr) {
        Index = 0;
        while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
          if (PcieClockTablePtr->Item[Index].DeviceId == LowPowerEthernetTablePtr->DeviceId) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClockTablePtr-Find DeviceId = 0x%X\n", LowPowerEthernetTablePtr->DeviceId));
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClockTablePtr-Add ACPI_CHANGE in SlotCheck\n"));
            PcieClockTablePtr->Item[Index].SlotCheck |= ACPI_CHANGE;
          }
          Index++;
        }
      }
    }
  } else {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-LanLowPowerMode = Disabled\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Notify EC the LPM is disabled\n"));
    // Disable LAN_LOW_PWR_EN - ECRAM xB7[0](BIT88)
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, (0x200 + LAN_LOW_PWR_EN), 0);
    if (LowPowerEthernetTablePtr) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-RemoveTable-CPM_SIGNATURE_PCIE_LOW_POWER_ETHERNET\n"));
      AmdCpmTablePpi->CommonFunction.RemoveTable (AmdCpmTablePpi, LowPowerEthernetTablePtr);
    }
  }

  if (AmdPbsConfiguration.WlanRecovery != 0) {
    if (WirelessLanRecoveryTablePtr) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WirelessLanRecovery = Enabled\n"));
      if (DxioTopologyTablePtr) {
        for (Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++) {
          if (DxioPort[Index].EngineData.GpioGroupId == WirelessLanRecoveryTablePtr->DeviceId) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Find DeviceId = 0x%X\n", LowPowerEthernetTablePtr->DeviceId));
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Set HotplugEnhanced\n"));
            DxioPort[Index].Port.LinkHotplug  = HotplugEnhanced;
            continue;
          }
        }
      }
      if (PcieClockTablePtr) {
        Index = 0;
        while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
          if (PcieClockTablePtr->Item[Index].DeviceId == LowPowerEthernetTablePtr->DeviceId) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClockTablePtr-Find DeviceId = 0x%X\n", LowPowerEthernetTablePtr->DeviceId));
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClockTablePtr-Add ACPI_CHANGE in SlotCheck\n"));
            PcieClockTablePtr->Item[Index].SlotCheck |= ACPI_CHANGE;
          }
          Index++;
        }
      }
    }
  } else {
    if (WirelessLanRecoveryTablePtr) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-RemoveTable-CPM_SIGNATURE_WIRELESS_LAN_RECOVERY\n"));
      AmdCpmTablePpi->CommonFunction.RemoveTable (AmdCpmTablePpi, WirelessLanRecoveryTablePtr);
    }
  }

  if (AmdPbsConfiguration.SataPort0HddPowerEn == 0) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_HDD0, CPM_DEVICE_OFF);
  }  else if (AmdPbsConfiguration.SataPort0HddPowerEn == 1){
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_HDD0, CPM_DEVICE_ON);
  }

  if (AmdPbsConfiguration.SataPort1OddPowerEn == 0) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_ODD, CPM_DEVICE_OFF);
    if (PowerTablePtr) {
      Index = 0;
      while (PowerTablePtr->DevicePowerList[Index].DeviceId != 0xFF) {
        if (PowerTablePtr->DevicePowerList[Index].DeviceId == DEVICE_ID_ODD && \
            PowerTablePtr->DevicePowerList[Index].Mode == CPM_POWER_OFF && \
            PowerTablePtr->DevicePowerList[Index].InitFlag == GPIO_DEVICE_INIT_STAGE_DUMMY) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-(Item[%X].DeviceId == DEVICE_ID_ODD & CPM_POWER_OFF", Index));
          DEBUG((DEBUG_INFO, " Replace GPIO_DEVICE_INIT_STAGE_DUMMY with GPIO_DEVICE_INIT_STAGE_1)\n"));
          PowerTablePtr->DevicePowerList[Index].InitFlag = GPIO_DEVICE_INIT_STAGE_1;
        }
        Index++;
      }
    }
  } else {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_ODD, CPM_DEVICE_ON);
  }

  if (AmdPbsConfiguration.SataPortSsdPowerEn == 0) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_SSD, CPM_DEVICE_OFF);
  } else if (AmdPbsConfiguration.SataPortSsdPowerEn == 1) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_SSD, CPM_DEVICE_ON);
  } else if (AmdPbsConfiguration.SataPortSsdPowerEn == 2) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_SSD, CPM_DEVICE_ON);
    if (!Tambourine && ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) && (AmdPbsConfiguration.SataPort0HddPowerEn == 0) && (AmdPbsConfiguration.SataPort1OddPowerEn == 0)) {
      // RV board only, not for RV2 board and not for Tambourine board
      for (Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++) {
        if ((DxioPort[Index].EngineData.GpioGroupId == DEVICE_ID_SSD) && (DxioPort[Index].EngineData.StartLane == 0)) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Find DeviceId = DEVICE_ID_SSD\n"));
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Enable SSD x4\n"));
          DxioPort[Index].EngineData.EndLane = 3;
        } else if ((DxioPort[Index].EngineData.StartLane == 2) && (DxioPort[Index].EngineData.EndLane == 3)) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Find StartLane = 2 & EndLane = 3\n"));
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Set EngineType = DxioUnusedEngine\n"));
          DxioPort[Index].EngineData.EngineType = DxioUnusedEngine;
        }
      }
    }
  }

  if (AmdPbsConfiguration.RearCameraPowerEn != 1) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_RCAM, CPM_DEVICE_OFF);
  } else {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_RCAM, CPM_DEVICE_ON);
  }

  if (AmdPbsConfiguration.FrontCameraPowerEn != 1) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_FCAM, CPM_DEVICE_OFF);
  } else {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_FCAM, CPM_DEVICE_ON);
  }

  if (AmdPbsConfiguration.HdmiOverUsbTypeC0 != 1) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_USB_TYPE_C0, CPM_DEVICE_OFF);
  } else {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_USB_TYPE_C0, CPM_DEVICE_ON);
  }

  if (AmdPbsConfiguration.HdmiOverUsbTypeC1 != 1) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_USB_TYPE_C1, CPM_DEVICE_OFF);
  } else {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_USB_TYPE_C1, CPM_DEVICE_ON);
  }

  if (AmdPbsConfiguration.NVDgpuPowerEnable == 1) {
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_NGPU, CPM_DEVICE_ON);
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_MXM, CPM_DEVICE_OFF);
    PcdSet64 (PcdCpmIgnoreOemTableId, 0x444C4333444D5043);                        // Ignore override ACPI Oem Table Id = CPMD3CLD
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetGpio-Pin = 0x%X to 1 for NVIDIA DGPU_SEL# B17 pin\n", MXM_PRESENT));
    AmdCpmTablePpi->CommonFunction.SetGpio (AmdCpmTablePpi, MXM_PRESENT, 1);      // Output NVIDIA DGPU_SEL# B17 pin to high
    if (DevicePathTablePtr) {
      for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
        if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
          break;
        } else if (DevicePathTablePtr->Path[Index].IsDgpu && (DevicePathTablePtr->Path[Index].DeviceIdVcc == DEVICE_ID_MXM)) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DevicePathTablePtr- Use DEVICE_ID_NGPU instead of  DEVICE_ID_MXM\n"));
          DevicePathTablePtr->Path[Index].DeviceIdVcc = DEVICE_ID_NGPU;
        }
      }
    }
  } else {
    PcdSet64 (PcdCpmIgnoreOemTableId, 0);                                         // Clear ACPI Oem Table Id = CPMD3CLD
  }

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DetectPcieDevices\n"));
  DetectPcieDevices (AmdCpmTablePpi, DxioTopologyTablePtr, &AmdPbsConfiguration, &TravisStatus, CurrentBoardId);

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
    if (TravisStatus) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-TravisStatus = 1\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK3) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK3, Set ClkReq=CLK_ENABLE & SlotCheck=NON_SLOT_CHECK\n", Index));
          PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck = NON_SLOT_CHECK;
        }
        Index++;
      }
    }
    if (!AmdPbsConfiguration.ClockRequest0) {
      // DEVICE_ID_WLAN ClockRequest0 is disabled
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest0 (DEVICE_ID_WLAN) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK0) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK0\n", Index));
          if (AmdPbsConfiguration.WlanPowerControl == 0) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WlanPowerControl=0-Set ClkReq=CLK_DISABLE & Set SlotCheck=ACPI_CHANGE\n"));
            PcieClockTablePtr->Item[Index].ClkReq    = CLK_DISABLE;
            PcieClockTablePtr->Item[Index].SlotCheck = ACPI_CHANGE;
          } else {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl=0-Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2 BIT3\n"));
            PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
            PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
          }
        }
        Index++;
      }
    } else {
      // DEVICE_ID_WLAN ClockRequest0 is enabled
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest0 (DEVICE_ID_WLAN) = Enabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK0) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK0\n", Index));
          if (AmdPbsConfiguration.WlanPowerControl == 0) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-WlanPowerControl = 0-Set ClkReq=CLK_DISABLE & Set SlotCheck=ACPI_CHANGE\n"));
            PcieClockTablePtr->Item[Index].ClkReq    = CLK_DISABLE;
            PcieClockTablePtr->Item[Index].SlotCheck = ACPI_CHANGE;
          }
        }
        Index++;
      }
    }
    if (!AmdPbsConfiguration.ClockRequest1) {
      // DEVICE_ID_LAN ClockRequest1 is disabled - Clear SlotCheck BIT2 - Don't check Clock Power Management
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest1 (DEVICE_ID_LAN) = Disabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK1) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK1, Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2 BIT3\n", Index));
          PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
          PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
        }
        Index++;
      }
    }
    if (!AmdPbsConfiguration.ClockRequest2) {
      // DEVICE_ID_WWAN ClockRequest2 is disabled - Clear SlotCheck BIT2 - Don't check Clock Power Management
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest2 (DEVICE_ID_WWAN) = Disabled\n"));
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
          if (AmdPbsConfiguration.DtSlotPowerControl == 0) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl = 0-Set ClkReq=CLK_DISABLE & Set SlotCheck=ACPI_CHANGE\n"));
            PcieClockTablePtr->Item[Index].ClkReq    = CLK_DISABLE;
            PcieClockTablePtr->Item[Index].SlotCheck = ACPI_CHANGE;
          } else {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl > 0-Set ClkReq=CLK_ENABLE & Clear SlotCheck BIT2 BIT3\n"));
            PcieClockTablePtr->Item[Index].ClkReq    = CLK_ENABLE;
            PcieClockTablePtr->Item[Index].SlotCheck &= ~L1SS_CLKPM_ONLY;
          }
        }
        Index++;
      }
    } else {
      // DEVICE_ID_DT ClockRequest4 is enabled
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-ClockRequest4 (DEVICE_ID_DT) = Enabled\n"));
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].ClkId == GPP_CLK4) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Item[%X].ClkId=GPP_CLK4\n", Index));
          if (AmdPbsConfiguration.DtSlotPowerControl == 0) {
            DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtSlotPowerControl = 0-Set ClkReq=CLK_DISABLE & Set SlotCheck=ACPI_CHANGE\n"));
            PcieClockTablePtr->Item[Index].ClkReq    = CLK_DISABLE;
            PcieClockTablePtr->Item[Index].SlotCheck = ACPI_CHANGE;
          }
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
  }

  if (!AmdPbsConfiguration.DtHotPlugEnable) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtHotPlugEnable = Disabled\n"));
    if (DtHotplugTablePtr) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-RemoveTable-CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD\n"));
      AmdCpmTablePpi->CommonFunction.RemoveTable (AmdCpmTablePpi, DtHotplugTablePtr);
    }
  } else {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DtHotPlugEnable = Enabled\n"));
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-SetDeviceConfigTable-DEVICE_ID_DT-CPM_DEVICE_AUTO\n"));
    SetDevice (GpioDeviceConfigTablePtr, DEVICE_ID_DT, CPM_DEVICE_AUTO);
    if (AmdPbsConfiguration.DtHotPlugMode) {
      DtHotplugTablePtr->HotPlugMode0 = 1;
    }
    if (PcieClockTablePtr && DtHotplugTablePtr) {
      Index = 0;
      while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
        if (PcieClockTablePtr->Item[Index].DeviceId == DEVICE_ID_DT) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClockTablePtr-Find DEVICE_ID_DT\n"));
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcieClockTablePtr-Set CLK_ENABLE and NON_SLOT_CHECK + ACPI_CHANGE\n"));
          PcieClockTablePtr->Item[Index].SlotCheck = CLKPM_ONLY | ACPI_CHANGE;
        }
        Index++;
      }
    }
    if (DxioTopologyTablePtr && DtHotplugTablePtr) {
      for (Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++) {
        if (DxioPort[Index].EngineData.GpioGroupId == DEVICE_ID_DT) {
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Find DEVICE_ID_DT\n"));
          DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-DxioTopologyTablePtr-Disable Aspm & L1_1 & L1_2\n"));
          DxioPort[Index].Port.LinkAspm     = DxioAspmDisabled;
          DxioPort[Index].Port.LinkAspmL1_1 = DxioAspmL11Disabled;
          DxioPort[Index].Port.LinkAspmL1_2 = DxioAspmL12Disabled;
          continue;
        }
      }
    }
  }

  if (PcieClockTablePtr) {
    Index = 0;
    while (PcieClockTablePtr->Item[Index].ClkId != 0xFF) {
      DEBUG((DEBUG_INFO, "  Item[%X] Socket=%02X Die=%02X Bridge=%02X Miscid=%02X", Index, \
            (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 24) & 0xF, (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 20) & 0xF, \
            (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 16) & 0xF, (PcieClockTablePtr->Item[Index].SpecialFunctionId >> 28) & 0xF));
      DEBUG((DEBUG_INFO, " ClkId=%02X ClkReq=%02X ClkIdExt=%02X ClkReqExt=%02X DeviceId=%02X", \
            PcieClockTablePtr->Item[Index].ClkId,    PcieClockTablePtr->Item[Index].ClkReq, \
            PcieClockTablePtr->Item[Index].ClkIdExt, PcieClockTablePtr->Item[Index].ClkReqExt, PcieClockTablePtr->Item[Index].DeviceId));
      DEBUG((DEBUG_INFO, " Device=%02X Function=%02X SlotCheck=%02X SpecialFunctionId=%04X\n", \
            PcieClockTablePtr->Item[Index].Device, PcieClockTablePtr->Item[Index].Function, \
            PcieClockTablePtr->Item[Index].SlotCheck, (PcieClockTablePtr->Item[Index].SpecialFunctionId & 0xFFFF)));
      Index++;
    }
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Final-PcieClockTable\n"));
  }

  //VDDP adjustment for corner SI test
  if (Tambourine) {
    Value8_1 = 0x64;

    // VDDP is 5mv/bit..
    if (AmdPbsConfiguration.VDDP == 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage = 0.9V\n"));
    } else if ( (AmdPbsConfiguration.VDDP > 0) && (AmdPbsConfiguration.VDDP < 11)) {
      Value8_1 += AmdPbsConfiguration.VDDP * 2;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage increased to %lx\n", Value8_1));
    } else if ( (AmdPbsConfiguration.VDDP >= 11 && (AmdPbsConfiguration.VDDP <= 20))) {
      Value8_1 -= (AmdPbsConfiguration.VDDP - 10) * 2;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage decreased to %lx\n", Value8_1));
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage = Invalid\n"));
    }

    Offset = 0x90;
    Value8 = 0x21; // Register (0x21)
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x91;
    Value8 = Value8_1;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    Value8 = (0x5E << 1); //TI PMIC is 0x5E
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    do {
      AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
      DEBUG((DEBUG_INFO, "Wait ECRAMx92 !=0xCC for VDDP\n"));
    } while (Value8 == 0xCC);

    //VDD_18 adjustment for corner SI test
    Value8_1 = 0x70;

    //VDD_18 is 12.5mv/bit
    if (AmdPbsConfiguration.VDD18 == 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage = 1.8V\n"));
    } else if ( (AmdPbsConfiguration.VDD18 > 0) && (AmdPbsConfiguration.VDD18 < 11)) {
      Value8_1 += AmdPbsConfiguration.VDD18 + 1;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage increased to %lx\n", Value8_1));
    } else if ( (AmdPbsConfiguration.VDD18 >= 11 && (AmdPbsConfiguration.VDD18 <= 20))) {
      Value8_1 -= (AmdPbsConfiguration.VDD18 - 9) ;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage decreased to %lx\n", Value8_1));
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage = Invalid\n"));
    }

    Offset = 0x90;
    Value8 = 0x23; //   Register (0x23)
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x91;
    Value8 = Value8_1;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    Value8 = (0x5E << 1); //TI PMIC is 0x5E
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    do {
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    DEBUG((DEBUG_INFO, "Wait ECRAMx92 !=0xCC for VDD18\n"));
    } while ( Value8 == 0xCC );
  } else {
    Value8_1 = 0x28;

    if (AmdPbsConfiguration.VDDP == 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage = 0.9V\n"));
    } else if ( (AmdPbsConfiguration.VDDP > 0) && (AmdPbsConfiguration.VDDP < 11)) {
      Value8_1 += AmdPbsConfiguration.VDDP;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage increased to %lx\n", Value8_1));
    } else if ( (AmdPbsConfiguration.VDDP >= 11 && (AmdPbsConfiguration.VDDP <= 20))) {
      Value8_1 += 10;
      Value8_1 -= AmdPbsConfiguration.VDDP;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage decreased to %lx\n", Value8_1));
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDDP Voltage = Invalid\n"));
    }

    Offset = 0x90;
    Value8 = 0x06;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x91;
    Value8 = Value8_1;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    Value8 = (0x6E << 1);
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    do {
      AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
      DEBUG((DEBUG_INFO, "Wait ECRAMx92 !=0xCC for VDDP\n"));
    } while (Value8 == 0xCC);

    //VDD_18 adjustment for corner SI test
    Value8_1 = 0x23;

    if (AmdPbsConfiguration.VDD18 == 0) {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage = 1.8V\n"));
    } else if ( (AmdPbsConfiguration.VDD18 > 0) && (AmdPbsConfiguration.VDD18 < 11)) {
      Value8_1 += 3;
      Value8_1 += AmdPbsConfiguration.VDD18;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage increased to %lx\n", Value8_1));
    } else if ( (AmdPbsConfiguration.VDD18 >= 11 && (AmdPbsConfiguration.VDD18 <= 20))) {
      Value8_1 += 7;
      Value8_1 -= AmdPbsConfiguration.VDD18;
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage decreased to %lx\n", Value8_1));
    } else {
      DEBUG((DEBUG_INFO, "OEM-PEI-VDD18 Voltage = Invalid\n"));
    }

    Offset = 0x90;
    Value8 = 0x08;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x91;
    Value8 = Value8_1;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    Value8 = (0x6E << 1);
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    do {
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    DEBUG((DEBUG_INFO, "Wait ECRAMx92 !=0xCC for VDD18\n"));
    } while ( Value8 == 0xCC );
    
    // 5V_S5 setting
    Offset = 0x90;
    Value8 = 0x04;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x91;
    Value8 = 0x6c + (3 * AmdPbsConfiguration.S5_5V);
    DEBUG((DEBUG_INFO, "OEM-PEI-5V_S5 Voltage = 0x%x\n", Value8));    
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    Value8 = (0x6E << 1);
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    do {
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    DEBUG((DEBUG_INFO, "Wait ECRAMx92 !=0xCC for VDD18\n"));        
    } while ( Value8 == 0xCC );    
  } // End of if (Tambourine)

  Offset = 0xB7;
  AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
  if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {
    DEBUG((DEBUG_INFO, "If RV1, keep ECRAMxB7[6] to 0\n"));
    Value8 &= ~BIT6;
  } else {
    DEBUG((DEBUG_INFO, "If RV2, set ECRAMxB7[6] to 1\n"));
    Value8 |= BIT6;
  }
  AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

  //
  //ECRAM 0xB7 bit 5 (ECRAMxB7[5]),
  //  0 - use AGPIO22 for SCI events (default)
  //  1 - use AGPIO86 for SCI events
  //
  if (PcdGet8(PcdEmmcEnable) == 0) {
    DEBUG((DEBUG_INFO, "eMMC Disabled, Set ECRAMxB7[5]:0\n"));
    Offset = 0xB7;
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    Value8 &= ~BIT5;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Index = 0;
    while (GeventTablePtr->GeventList[Index].Pin != 0xFF) {
      if (GeventTablePtr->GeventList[Index].Pin == 0x09) {
        DEBUG((DEBUG_INFO, "Disable GEVENT 09.\n"));
        GeventTablePtr->GeventList[Index].Setting.Gevent.EventEnable = 0;
      }
      Index++;
    }

  } else {
    DEBUG((DEBUG_INFO, "eMMC enabled, Set ECRAMxB7[5]:1\n"));
    Offset = 0xB7;
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    Value8 |= BIT5;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Index = 0;
    while (GeventTablePtr->GeventList[Index].Pin != 0xFF) {
      if (GeventTablePtr->GeventList[Index].Pin == 0x03) {
        DEBUG((DEBUG_INFO, "Disable GEVENT 03.\n"));
        GeventTablePtr->GeventList[Index].Setting.Gevent.EventEnable = 0;
      }
      Index++;
    }
  }

  //Read EC FwVersion

  ECFwVersion = 0;
  Value8_1 = 0;

  for (Index8 = 0; Index8 < 5; Index8++) {
    Offset = (0xC6 - Index8);
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    if ( Value8 == 0x2E ) {
      continue;
    }
    ECFwVersion |= (UINT32)(Value8 << ( 8 * Value8_1));
    Value8_1 += 1;
  }

  DEBUG((DEBUG_INFO, "ECFwVersion = %lx\n", ECFwVersion));
  PcdSet32 (PcdECFwVersion, ECFwVersion);

  //Read USBPD FwVersion
  Offset = 0x31;
  Value8 = 0xDB;
  AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

  Offset = 0x30;
  AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
  Value8_1 = ( Value8 & 0x0F );

  Offset = 0x30;
  Value8 |= 0x80;
  AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

  do {
    Offset = 0x30;
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    Value8 &= 0x0F;
    DEBUG((DEBUG_INFO, "Wait ECRAMx30 Changes\n"));
  } while ( Value8 == Value8_1 );

  USBPDFwVersion = 0;

  for (Index8 = 0; Index8 < 2; Index8++) {
    Offset = (0x26 + Index8);
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    USBPDFwVersion |= (UINT16)(Value8 << ( 8 - 8 * Index8));
  }

  DEBUG((DEBUG_INFO, "USBPDFwSection1Version = %lx\n", USBPDFwVersion));
  PcdSet16 (PcdUSBPDFwSection1Version, USBPDFwVersion);

  USBPDFwVersion = 0;

  for (Index8 = 0; Index8 < 2; Index8++) {
    Offset = (0x2E + Index8);
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    USBPDFwVersion |= (UINT16)(Value8 << ( 8 - 8 * Index8));
  }

  DEBUG((DEBUG_INFO, "USBPDFwSection2Version = %lx\n", USBPDFwVersion));
  PcdSet16 (PcdUSBPDFwSection2Version, USBPDFwVersion);

  if (AmdPbsConfiguration.AmdDptcControl == 1) {
    DEBUG((DEBUG_INFO, "Dynamic Power and Thermal Control Interface Enable\n"));
    Offset = 0x31;
    Value8 = 0xDF;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);
    Offset = 0x00;
    Value8 = 0x01;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);
  } else {
    DEBUG((DEBUG_INFO, "Dynamic Power and Thermal Control Interface Disable\n"));
    Offset = 0x31;
    Value8 = 0xDF;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);
    Offset = 0x00;
    Value8 = 0x00;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);
  }

  //Read PMIC version

  // Try as ANPEC first

  Offset = 0x90;
  Value8 = 0x01;
  AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

  Offset = 0x92;
  Value8 = ((0x6E << 1) + 1);
  AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

  Offset = 0x92;
  do {
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    DEBUG((DEBUG_INFO, "Polling PMIC ANPEC \n"));
  } while ( Value8 == 0xCC );

  if ( Value8 == 0xAC ) {
    Offset = 0x91;
    AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
    DEBUG((DEBUG_INFO, "PMIC is ANPEC , version = %lx\n", Value8));
  } else {
    // ANPEC fails, Try as TI second
    DEBUG((DEBUG_INFO, "ANPEC fails, Try as TI second \n"));
    Offset = 0x90;
    Value8 = 0x01;
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    Value8 = ((0x5E << 1)+ 1);
    AmdCpmTablePpi->CommonFunction.EcRamWrite (CFG_CPM_ECRAM_BASE_ADDR, 0x81, &Offset, &Value8);

    Offset = 0x92;
    do {
      AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
      DEBUG((DEBUG_INFO, "Polling PMIC TI \n"));
    } while ( Value8 == 0xCC );

    if ( Value8 == 0xAC ) {
      Offset = 0x91;
      AmdCpmTablePpi->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8);
      DEBUG((DEBUG_INFO, "PMIC is TI , version = %lx\n", Value8));
    } else {
      Value8 = 0xFF;
      DEBUG((DEBUG_INFO, "Unknown PMIC \n"));
    }
  }

  PcdSet8(PmicVersion, Value8);

  if ((AmdPbsConfiguration.AmdPspKvmMouseProtocol == AMD_PSP_KVM_ABSOLUTE) || (AmdPbsConfiguration.AmdPspKvmMouseProtocol == AMD_PSP_KVM_SIMPLE)) {
    DEBUG((DEBUG_INFO, "AmdPspKvmMouseProtocol %x\n", AmdPbsConfiguration.AmdPspKvmMouseProtocol));
    PcdSet8(PcdAmdPspKvmMouseProtocol, AmdPbsConfiguration.AmdPspKvmMouseProtocol);
  }

  TableAddress = &AzaliaCodecVerbTable[0];
  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-PcdCfgAzaliaCodecVerbTable-TableAddress = %x\n", TableAddress));
  PcdSet32 (PcdCfgAzaliaCodecVerbTable, (UINT32)TableAddress);

  if (Tambourine) {
    DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Tambourine-PCO-RV2-PcdAtomDpHbr3PhyDpSetting\n"));
    Status = (**PeiServices).AllocatePool (
                                 PeiServices,
                                 sizeof(ATOM_14NM_DPPHY_DP_SETTING)*20,
                                 &DpPtr
                                 );

    if (!EFI_ERROR(Status)) {

      TempDpPtr = DpPtr;

      // HBR2
      PcdSet8  (PcdAmdDpHbr2PhySel, 0xC);
      PcdSet8  (PcdAmdDpHbr2Version, 0x0);
      PcdSet16 (PcdAmdDpHbr2TableSize, 0x5);

      Count = 0;
      TempDpPtr[Count].dp_vs_pemph_level = 0;
      TempDpPtr[Count].margindeemph = 0x004b;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///1
      TempDpPtr[Count].dp_vs_pemph_level = 2;
      TempDpPtr[Count].margindeemph = 0x0017;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///2
      TempDpPtr[Count].dp_vs_pemph_level = 0x08;
      TempDpPtr[Count].margindeemph = 0x2A34;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///3
      TempDpPtr[Count].dp_vs_pemph_level = 0x09;
      TempDpPtr[Count].margindeemph = 0x2A1C;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///4
      TempDpPtr[Count].dp_vs_pemph_level = 0x10;
      TempDpPtr[Count].margindeemph = 0x4514;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///5
      TempDpPtr[Count].dp_vs_pemph_level = 0x11;
      TempDpPtr[Count].margindeemph = 0x3E01;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x9F;
      Count++;
      ///6
      TempDpPtr[Count].dp_vs_pemph_level = 0x18;
      TempDpPtr[Count].margindeemph = 0x5100;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x9F;
      Count++;

      for (Index = Count; Index < 10; Index++) {
        TempDpPtr[Index].dp_vs_pemph_level = 0xFF;
        TempDpPtr[Index].margindeemph = 0;
        TempDpPtr[Index].deemph_6db_4 = 0;
        TempDpPtr[Index].boostadj = 0;
      }

      // HBR3
      TempDpPtr = &(DpPtr[10]);
      PcdSet8  (PcdAmdDpHbr3PhySel, 0xC);
      PcdSet8  (PcdAmdDpHbr3Version, 0x0);
      PcdSet16 (PcdAmdDpHbr3TableSize, 0x5);

      Count = 0;
      TempDpPtr[Count].dp_vs_pemph_level = 0;
      TempDpPtr[Count].margindeemph = 0x004b;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///1
      TempDpPtr[Count].dp_vs_pemph_level = 2;
      TempDpPtr[Count].margindeemph = 0x0017;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///2
      TempDpPtr[Count].dp_vs_pemph_level = 0x08;
      TempDpPtr[Count].margindeemph = 0x2A34;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///3
      TempDpPtr[Count].dp_vs_pemph_level = 0x09;
      TempDpPtr[Count].margindeemph = 0x2A1C;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///4
      TempDpPtr[Count].dp_vs_pemph_level = 0x10;
      TempDpPtr[Count].margindeemph = 0x4514;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x80;
      Count++;
      ///5
      TempDpPtr[Count].dp_vs_pemph_level = 0x11;
      TempDpPtr[Count].margindeemph = 0x3E01;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x9F;
      Count++;
      ///6
      TempDpPtr[Count].dp_vs_pemph_level = 0x18;
      TempDpPtr[Count].margindeemph = 0x5100;
      TempDpPtr[Count].deemph_6db_4 = 0;
      TempDpPtr[Count].boostadj = 0x9F;
      Count++;

      for (Index = Count; Index < 10; Index++) {
        TempDpPtr[Index].dp_vs_pemph_level = 0xFF;
        TempDpPtr[Index].margindeemph = 0;
        TempDpPtr[Index].deemph_6db_4 = 0;
        TempDpPtr[Index].boostadj = 0;
      }
      PcdSet32(PcdAtomDpHbr2TuningSetting, (UINT32)(UINTN)&DpPtr[0]);
      PcdSet32(PcdAtomDpHbr3PhyDpSetting, (UINT32)(UINTN)&DpPtr[10]);
      PcdSet16(PcdAmdDpPhyOverride, ATOM_ENABLE_DP_HBR2_TUNINGSET|ATOM_ENABLE_DP_HBR3_TUNINGSET);
    }
  } else {
    if ((CurrentBoardId < 8) || (CurrentBoardId >= 0x10 && CurrentBoardId < 0x18)) {
      DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-Mandolin-PCO-PcdAtomDpHbr3PhyDpSetting\n"));
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
  }

  if (AmdPbsConfiguration.RT3663VrmPsi0En == 1) {
    PcdSetBool(PcdRichtekVrmPsi0Workaround,1);
    DEBUG((DEBUG_INFO, "RT3663VrmPsi0 = Enabled\n"));
  } else {
    PcdSetBool(PcdRichtekVrmPsi0Workaround,0);
    DEBUG((DEBUG_INFO, "RT3663VrmPsi0 = Disabled\n"));
  }

  DEBUG((DEBUG_INFO, "OEM-PEI-AmdCpmTableOverride-End-3-Status=%r\n", Status));
  return Status;
}

#define  GPIO_PIN_I2C_TOUCH_PAD_INT  0x9
#define  GPIO_MUX_I2C_TOUCH_PAD_INT  GPIO_FUNCTION_0

#define  GPIO_PIN_I2C_TOUCH_PNL_INT  0x0
#define  GPIO_MUX_I2C_TOUCH_PNL_INT  GPIO_FUNCTION_0

VOID
I2cTouchDeviceIntGpioInit (
  VOID
)
{
  //
  UINT8   Data8 = 0x0;
  UINT32  Data32 = 0x0;
  UINT32  Address = 0x0;
  UINT32  Reg = 0x0;
  UINT32  Mask = 0x0;
  //
  // refer to ppr.3, 13.2.16.1 IOMUX Registers
  //
  Address = ACPI_MMIO_BASE + IOMUX_BASE;                // MuxReg Base
  //
  Reg = GPIO_PIN_I2C_TOUCH_PAD_INT;                     // GPIO : I2C PAD INT#
  Data8 = (MmioRead8 (Address + Reg) & 0xFC);
  Data8 = (Data8 | GPIO_MUX_I2C_TOUCH_PAD_INT);         // MUX : GPIO
  MmioWrite8 ((Address + Reg), Data8);

  // Reg = GPIO_PIN_I2C_TOUCH_PNL_INT;                  // GPIO : I2C PNL INT#
  // Data8 = (MmioRead8 (Address + Reg) & 0xFC);
  // Data8 = (Data8 | GPIO_MUX_I2C_TOUCH_PNL_INT);      // MUX : GPIO
  // MmioWrite8 ((Address + Reg), Data8);

  //
  // refer to ppr.3, 13.2.16.2 GPIO Registers
  //
  Address = ACPI_MMIO_BASE + GPIO_BANK0_BASE;           // GpioReg (Bank 0) Base
  //
  Mask = ((0x1 << 8) | (0x3 << 9) | (0x3 << 11) | (0x7 << 19) | (0x3 << 22));
  //

  Reg = ((UINTN) GPIO_PIN_I2C_TOUCH_PAD_INT) << 2;      // GPIO : I2C PAD INT#
  Data32 = MmioRead32 (Address + Reg);
  Data32 = Data32 & (~Mask) ;

  //
  // Level trigger, Active Low, Enable interrupt delivery & Status,
  // PullupEnable, PullDown disable, Input.
  //
  Data32 = Data32 | ((0x1 << 8) | (0x1 << 9) | (0x3 << 11) | (0x2 << 19));

  MmioWrite32 ((Address + Reg), Data32);

  // Reg =  ((UINTN) GPIO_PIN_I2C_TOUCH_PNL_INT) << 2;  // GPIO : I2C PNL INT#
  // Data32 = MmioRead32 (Address + Reg);
  // Data32 = Data32 & (~Mask) ;

  // //
  // // Level trigger, Active Low, Enable interrupt delivery & Status,
  // // PullupEnable, PullDown disable, Input.
  // //
  // Data32 = Data32 | ((0x1 << 8) | (0x1 << 9) | (0x3 << 11) | (0x2 << 19));
  //
  // MmioWrite32 ((Address + Reg), Data32);

  return;
}
