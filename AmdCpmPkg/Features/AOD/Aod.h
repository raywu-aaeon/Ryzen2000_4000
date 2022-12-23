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
 ******************************************************************************
 */

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

#ifndef _AOD_SMM_H_
#define _AOD_SMM_H_

#pragma pack(push, 1)

#define MAX_DIE_SUPPORT           8
#define AMD_VENDOR_ID             0x1022

#define CH_SMN_BASE_CH0_MP0       0x00050000
#define CH_SMN_BASE_CH1_MP0       0x00150000
#define CTL_SMN_BASE_CH0_MP0      0x00051000
#define CTL_SMN_BASE_CH1_MP0      0x00151000

#define DRAM_CONFIGURATION          0x00000200
#define DRAM_TIMING1                0x00000204
#define DRAM_TIMING2                0x00000208
#define DRAM_TIMING3                0x0000020C
#define DRAM_TIMING4                0x00000210
#define DRAM_TIMING5                0x00000214
#define DRAM_TIMING6                0x00000218
#define DRAM_TIMING7                0x0000021C
#define DRAM_TIMING8                0x00000220
#define DRAM_TIMING9                0x00000224
#define DRAM_TIMING10               0x00000228
#define DRAM_TIMING11               0x0000022C
#define DRAM_TIMING12               0x00000230
#define DRAM_TIMING13               0x00000234
#define DRAM_TIMING14               0x00000238
#define DRAM_TIMING15               0x0000023C
#define DRAM_TIMING17               0x00000244
#define DRAM_TIMING20               0x00000250
#define DRAM_TIMING21               0x00000254
#define DRAM_TIMING22               0x00000258
#define DRAM_TIMING23               0x0000025C
#define DRAM_TRFC_TIMING            0x00000260
#define DRAM_ODT_TIMING             0x00000280
#define DRAM_SPAZ_CONTROL           0x0000012C

#define CTL_APB_COMMAND             0x00000800
#define CTL_APB_DATA                0x00000804
#define CTL_TXODTDRVSTREN           0x0001004D

#define AOD_MEMORY_BUFFER_VERSION   4


typedef enum {
  GET_MEM_DATA_BUFFER     = 0x80000000,
  GET_VDDIO               = 0x40000000,
  GET_VTT                 = 0x20000000,
  SET_MEMORY_CLOCK        = 0x00000001,
  SET_TCL                 = 0x00000002,
  SET_TRCDRD              = 0x00000004,
  SET_TRCDWR              = 0x00000008,
  SET_TRP                 = 0x00000010,
  SET_TRAS                = 0x00000020,
  SET_VDDIO               = 0x00000100,
  SET_VTT                 = 0x00000200,
  GET_VPP                 = 0x00001000,  // Get VPP
  SET_VPP                 = 0x00002000,  // Set VPP
  SET_PROC_ODT            = 0x00003000,  // Set procODT
  SET_TRCPAGE             = 0x00004000,  // Set Trcpage
  SET_TRC                 = 0x00005000,  // Set Trc
  SET_TRFC                = 0x00006000,  // Set Trfc
  SET_TRFC2               = 0x00007000,  // Set Trfc2
  SET_TRFC4               = 0x00008000,  // Set Trfc4
  SET_TFAW                = 0x00009000,  // Set Tfaw
  SET_TRRDS               = 0x0000A000,  // Set TrrdS
  SET_TRRDL               = 0x0000B000,  // Set TrrdL
  SET_TWR                 = 0x0000C000,  // Set Twr
  SET_TWTRS               = 0x0000D000,  // Set TwtrS
  SET_TWTRL               = 0x0000E000,  // Set TwtrL
  SET_TCKE                = 0x0000F000,  // Set tCKE
  SET_TCWL                = 0x00010000,  // Set Tcwl
  SET_TRTP                = 0x00020000,  // Set Trtp
  SET_TRDRDSC             = 0x00030000,  // Set TrdrdSc
  SET_TRDRDSCL            = 0x00040000,  // Set TrdrdScL
  SET_TRDRDSD             = 0x00050000,  // Set TrdrdSd
  SET_TRDRDDD             = 0x00060000,  // Set TrdrdDd
  SET_TWRWRSC             = 0x00070000,  // Set TwrwrSc
  SET_TWRWRSCL            = 0x00080000,  // Set TwrwrScL
  SET_TWRWRSD             = 0x00090000,  // Set TwrwrSd
  SET_TWRWRDD             = 0x000A0000,  // Set TwrwrDd
  SET_TRDWR               = 0x000B0000,  // Set Trdwr
  SET_TWRRD               = 0x000C0000,  // Set Twrrd
  SET_GEAR_DOWN_EN        = 0x000D0000,  // Set GearDownEn
  SET_CMD_2T              = 0x000E0000,  // Set Cmd2T
  SET_RTT_NOM             = 0x000F0000,  // Set RTTNom
  SET_RTT_WR              = 0x00100000,  // Set RTTWR
  SET_RTT_PARK            = 0x00200000,  // Set RTTPARK
  SET_POWER_DOWN_EN       = 0x00300000,  // Set PowerDownEn
  SET_SMT_EN              = 0x00400000,  // Set SMTEn
  SW_DOWNCORE_CONFIG      = 0x00500000,  // Software downcore config
  SET_EDC_TROTTLER_CONTROL = 0x00600000,  // Set EDC Throttler Control
  SET_CLDO_VDDP            = 0x00700000,  // Set CLDO_VDDP
  SET_ADDR_CMD_SETUP       = 0x00800000,  // Set AddrCmdSetup
  SET_CS_ODT_SETUP         = 0x00900000,  // Set CsOdtSetup
  SET_CKE_SETUP            = 0x00A00000,  // Set CKE SETUP
  SET_CAD_BUS_CLK_DRV_STREN          = 0x00B00000, // Set CadBusClkDrvStren
  SET_CAD_BUS_ADDR_DRV_STREN         = 0x00C00000, // Set CadBusAddrDrvStren
  SET_CAD_BUS_CS_ODT_CMD_DRV_STREN   = 0x00D00000, // Set CsOdtCmdDrvStren
  SET_CAD_BUS_CKE_DRV_STREN          = 0x00E00000, // Set CkeDrvStren
  SET_INTERLEAVE_MODE                = 0x00100001, // Set mem interleaving mode
  SET_INTERLEAVE_SIZE                = 0x00100002, // Set mem interleaving size
  SET_FCLK_OC_MODE                   = 0x00100003, // Set FCLK OC enable mode
  SET_SOC_VID                        = 0x00100004, // Set VDDCR_SOC VID
  COMMAND_BUFFER_START               = 0x01000000, // Commad Buffer Start
  COMMAND_BUFFER_END                 = 0x02000000, // Commad Buffer End
} MemCommad;


#if AOD_MEMORY_BUFFER_VERSION <= 3
typedef struct _AodMemoryBufferStruct {
  UINT32     AodMemBufferSignature;
  UINT32     Version;
  UINT32     Command;
  UINT16     MemClkFreq;
  UINT8      Tcl;
  UINT8      Trcdrd;
  UINT8      Trcdwr;
  UINT8      Tras;
  UINT8      Trp;
  UINT16     VddioMV;
  UINT16     VTTMV;
  UINT8      MemReserved[9];
} AodMemoryBufferStruct;
#else
typedef struct _DownBitmapStruct {
  UINT16     DownCoreBitmap    : 8; // 0xFF means all cores enabled
  UINT16     DieNum            : 7;
  UINT16     IsBitmap          : 1;
} DownCoreBitmapStruct;

typedef union _DowncoreUnion {
  DownCoreBitmapStruct DownCoreConfig;
  UINT16               ActiveCoreNum;
} DowncoreUnion;

typedef struct _AodMemoryBufferStruct {  // Size: 184
  UINT32     AodMemBufferSignature;    // offset 0x0
  UINT32     Version;                  // offset 0x4
  UINT32     Command;                  // offset 0x8
  UINT16     MemClkFreq;               // offset 0xC
  UINT8      Tcl;                      // offset 0xE
  UINT8      Trcdrd;                   // offset 0xF
  UINT8      Trcdwr;                   //offset 0x10
  UINT8      Tras;                     // offset 0x11
  UINT8      Trp;                      // offset 0x12
  UINT16     VddioMV;                  // offset 0x13
  UINT16     VTTMV;                    // offset 0x15
  UINT16     VPPMV;                    // offset 0x17
  UINT16     procODT;                  // offset 0x19
  UINT16     Trcpage;                  // offset 0x1B
  UINT8      Trc;                      // offset 0x1D
  UINT16     Trfc;                     // offset 0x1E
  UINT16     Trfc2;                    // offset 0x20
  UINT16     Trfc4;                    // offset 0x22
  UINT8      Tfaw;                     // offset 0x24
  UINT8      TrrdS;                    // offset 0x25
  UINT8      TrrdL;                    // offset 0x26
  UINT8      Twr;                      // offset 0x27
  UINT8      TwtrS;                    // offset 0x28
  UINT8      TwtrL;                    // offset 0x29
  UINT8      TCke;                     // offset 0x2A
  UINT8      Tcwl;                     // offset 0x2B
  UINT8      Trtp;                     // offset 0x2C
  UINT8      TrdrdSc;                  // offset 0x2D
  UINT8      TrdrdScL;                 // offset 0x2E
  UINT8      TrdrdSd;                  // offset 0x2F
  UINT8      TrdrdDd;                  // offset 0x30
  UINT8      TwrwrSc;                  // offset 0x31
  UINT8      TwrwrScL;                 // offset 0x32
  UINT8      TwrwrSd;                  // offset 0x33
  UINT8      TwrwrDd;                  // offset 0x34
  UINT8      Trdwr;                    // offset 0x35
  UINT8      Twrrd;                    // offset 0x36
  UINT8      GearDownEn;               // offset 0x37
  UINT8      Cmd2t;                    // offset 0x38
  UINT8      RttNom;                   // offset 0x39
  UINT8      RttWR;                    // offset 0x3A
  UINT8      RttPark;                  // offset 0x3B
  UINT8      PowerDownEn;              // offset 0x3C
  UINT8      OcDisable;                // offset 0x3D
  UINT32     OcVoltageMax;             // offset 0x3E
  UINT32     OcFrequencyMax;           // offset 0x42
  UINT8      SmtEnabled;               // offset 0x46
  INT32      TempOffset;               // offset 0x47
  UINT8      EdcThrottlerCtrl;         // offset 0x4B
  DowncoreUnion  DownCore;             // offset 0x4C
  UINT8      AddrCmdSetup;             // offset 0x4E
  UINT8      CsOdtSetup;               // offset 0x4F
  UINT8      CkeSetup;                 // offset 0x50
  UINT8      CadBusClkDrvStren;        // offset 0x51
  UINT8      CadBusAddrDrvStren;       // offset 0x52
  UINT8      CadBusCsOdtCmdDrvStren;   // offset 0x53
  UINT8      CadBusCkeDrvStren;        // offset 0x54
  UINT16     CldoVddp;                 // offset 0x55
  UINT8      EdcThrottlerCtrlOpnValue; // offset 0x57
  UINT32     MemInterleavingCap;       // offset 0x58
  UINT32     MemInterleavingMode;      // offset 0x5C
  UINT32     InterleavingSize;         // offset 0x60
  UINT32     PptPlatformPCD;           // offset 0x64
  UINT32     TdcPlatformPCD;           // offset 0x68
  UINT32     EdcPlatformPCD;           // offset 0x6C
  UINT8      FclkOcMode;               // offset 0x70
  UINT8      VddcrSocVid;              // offset 0x71
  UINT8      MemReserved[70];          // offset 0x72
} AodMemoryBufferStruct;
#endif

typedef struct _AodCpuBiosStruct {   // Size: 60
  UINT32     AodCpuBiosSignature;    // offset 0x0
  UINT32     Version;                // offset 0x4
  UINT8      OcDisable;              // offset 0x8
  UINT32     OcVoltageMax;           // offset 0x9
  UINT32     OcFrequencyMax;         // offset 0xD
  UINT8      SmtEnabled;             // offset 0x11
  UINT16     ActiveCoreNum;          // offset 0x12
  INT32      TempOffset;             // offset 0x14
  UINT8      EdcThrottlerCtrl;       // offset 0x18
  UINT8      AddrCmdSetup;           // offset 0x19
  UINT8      CsOdtSetup;             // offset 0x1A
  UINT8      CkeSetup;               // offset 0x1B
  UINT8      CadBusClkDrvStren;      // offset 0x1C
  UINT8      CadBusAddrDrvStren;     // offset 0x1D
  UINT8      CadBusCsOdtCmdDrvStren; // offset 0x1E
  UINT8      CadBusCkeDrvStren;      // offset 0x1F
  UINT16     CldoVddp;               // offset 0x20
  UINT8      RttNom;                 // offset 0x22
  UINT8      RttWR;                  // offset 0x23
  UINT8      RttPark;                // offset 0x24
  UINT16     procODT;                // offset 0x25
  UINT8      EdcThrottlerCtrlOpnValue; // offset 0x27
  UINT32     MemInterleavingCap;       // offset 0x28
  UINT32     MemInterleavingMode;      // offset 0x2C
  UINT32     InterleavingSize;         // offset 0x30
  UINT32     PptPlatformPCD;           // offset 0x34
  UINT32     TdcPlatformPCD;           // offset 0x38
  UINT32     EdcPlatformPCD;           // offset 0x3C
  UINT16     MemVddioStepping;         // offset 0x40
  UINT8      CpuReserved[6];           // offset 0x42
} AodCpuBiosStruct;

typedef struct _AodNvAreaStruct {   // Size: 200
  UINT16                    AodSmiCmd;
  UINT32                    AodSmiStatus;
  UINT16                    Reserved1;
  AodMemoryBufferStruct     AodMemBuffer;
  UINT8                     Reserved2[8];
} AodNvAreaStruct;

typedef struct _AOD_NV_AREA_UPDATED_PROTOCOL {
  UINT32              Version;
  AodNvAreaStruct    *AodNvAreaPtr;
  AodCpuBiosStruct   *AodCpuBiosStuctPtr;
} AOD_NV_AREA_UPDATED_PROTOCOL ;


#pragma pack(pop)


#endif
