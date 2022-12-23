/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Family 17h Zeppelin register defination
 *
 */
/*
 ******************************************************************************
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

#ifndef _FABRIC_REGISTERS_ZP_H_
#define _FABRIC_REGISTERS_ZP_H_
#pragma pack (push, 1)

#define  ZP_CS0_FABRIC_ID        0
#define  ZP_CS1_FABRIC_ID        1
#define  ZP_CCM0_FABRIC_ID       2
#define  ZP_CCM1_FABRIC_ID       3
#define  ZP_IOMS0_FABRIC_ID      4
#define  ZP_PIE_FABRIC_ID        5

#define  ZP_CS0_INSTANCE_ID      0
#define  ZP_CS1_INSTANCE_ID      1
#define  ZP_CCM0_INSTANCE_ID     2
#define  ZP_CCM1_INSTANCE_ID     3
#define  ZP_IOMS0_INSTANCE_ID    4
#define  ZP_PIE_INSTANCE_ID      5
#define  ZP_CAKE0_INSTANCE_ID    6
#define  ZP_CAKE1_INSTANCE_ID    7
#define  ZP_CAKE2_INSTANCE_ID    8
#define  ZP_CAKE3_INSTANCE_ID    9
#define  ZP_CAKE4_INSTANCE_ID   10
#define  ZP_CAKE5_INSTANCE_ID   11
#define  ZP_TCDX0_INSTANCE_ID   12
#define  ZP_TCDX1_INSTANCE_ID   13
#define  ZP_TCDX2_INSTANCE_ID   14
#define  ZP_TCDX3_INSTANCE_ID   15
#define  ZP_TCDX4_INSTANCE_ID   16
#define  ZP_TCDX5_INSTANCE_ID   17
#define  ZP_TCDX6_INSTANCE_ID   18

#define  ZP_NUM_CS_BLOCKS        2
#define  ZP_NUM_CCM_BLOCKS       2
#define  ZP_NUM_IOMS0_BLOCKS     1
#define  ZP_NUM_PIE_BLOCKS       1
#define  ZP_NUM_CAKE_BLOCKS      6
#define  ZP_NUM_TCDX_BLOCKS      7

#define  ZP_NUM_DF_BLOCKS        19

#define MAX_SOCKETS             2   ///< Max number of sockets in system
#define MAX_DIES_PER_SOCKET     4   ///< Max number of dies per socket
#define MAX_CHANNELS_PER_DIE    2   ///< Max Channels per die

#define FABRIC_ID_SOCKET_SHIFT      7
#define FABRIC_ID_SOCKET_SIZE_MASK  1
#define FABRIC_ID_DIE_SHIFT         5
#define FABRIC_ID_DIE_SIZE_MASK     3


/* Fabric Block Instance Count Register */
#define FABBLKINSTCOUNT_FUNC 0x0
#define FABBLKINSTCOUNT_REG  0x040
#define FABBLKINSTCOUNT_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FABBLKINSTCOUNT_FUNC, FABBLKINSTCOUNT_REG))

/// Fabric Block Instance Count Register
typedef union {
  struct {                           ///< Bitfields of Fabric Block Instance Count Register
    UINT32 BlkInstCount:8;           ///< Block Instance Count
    UINT32 :24;                      ///< Reserved
  } Field;
  UINT32  Value;
} FABRIC_BLK_INST_COUNT_REGISTER;

/* VGA Enable Register */
#define VGA_EN_FUNC 0x0
#define VGA_EN_REG  0x080
#define VGA_EN_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, VGA_EN_FUNC, VGA_EN_REG))

/// VGA Enable Register
typedef union {
  struct {                           ///< Bitfields of VGA Enable Register
    UINT32 VgaEn_VE:1;               ///< VGA Enable
    UINT32 VgaEn_NP:1;               ///< Non-Posted
    UINT32 VgaEn_CpuDis:1;           ///< CpuDis
    UINT32 :1;                       ///< Reserved
    UINT32 VgaEn_DstFabricID:8;      ///< Destination Fabric ID
    UINT32 :20;                      ///< Reserved
  } Field;
  UINT32  Value;
} VGA_EN_REGISTER;

/* Configuration Address Control Register */
#define CFGADDRESSCTRL_FUNC 0x0
#define CFGADDRESSCTRL_REG  0x084
#define CFGADDRESSCTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSCTRL_FUNC, CFGADDRESSCTRL_REG))

/// Configuration Address Control Register
typedef union {
  struct {                           ///< Bitfields of Configuration Address Control Register
    UINT32 SecBusNum:8;              ///< Secondary Bus Number
    UINT32 :24;                      ///< Reserved
  } Field;
  UINT32  Value;
} CFG_ADDRESS_CTRL_REGISTER;

/* Configuration Address Maps Register */
#define CFGADDRESSMAP_FUNC 0x0
#define CFGADDRESSMAP0_REG  0x0A0
#define CFGADDRESSMAP1_REG  0x0A4
#define CFGADDRESSMAP2_REG  0x0A8
#define CFGADDRESSMAP3_REG  0x0AC
#define CFGADDRESSMAP4_REG  0x0B0
#define CFGADDRESSMAP5_REG  0x0B4
#define CFGADDRESSMAP6_REG  0x0B8
#define CFGADDRESSMAP7_REG  0x0BC
#define CFGADDRESSMAP0_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP0_REG))
#define CFGADDRESSMAP1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP1_REG))
#define CFGADDRESSMAP2_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP2_REG))
#define CFGADDRESSMAP3_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP3_REG))
#define CFGADDRESSMAP4_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP4_REG))
#define CFGADDRESSMAP5_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP5_REG))
#define CFGADDRESSMAP6_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP6_REG))
#define CFGADDRESSMAP7_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CFGADDRESSMAP_FUNC, CFGADDRESSMAP7_REG))

/// Configuration Address Maps Register
typedef union {
  struct {                           ///< Bitfields of Configuration Address Maps Register
    UINT32 RE:1;                     ///< Read Enable
    UINT32 WE:1;                     ///< Write Enable
    UINT32 :2;                       ///< Reserved
    UINT32 DstFabricID:8;            ///< Destination Fabric ID
    UINT32 :4;                       ///< Reserved
    UINT32 BusNumBase:8;             ///< Bus Number Base
    UINT32 BusNumLimit:8;            ///< Bus Number Limit
  } Field;
  UINT32  Value;
} CFG_ADDRESS_MAP_REGISTER;

/* DRAM Hole Control Register */
#define DRAMHOLECTRL_FUNC 0x0
#define DRAMHOLECTRL_REG  0x104
#define DRAMHOLECTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMHOLECTRL_FUNC, DRAMHOLECTRL_REG)
#define DF_DramHoleControl    DRAMHOLECTRL_PCI_ADDR

/// DRAM Hole Control Register
typedef union {
  struct {                           ///< Bitfields of DRAM Hole Control Register
    UINT32 DramHoleValid:1;          ///< DRAM Hole Valid
    UINT32 :23;                      ///< Reserved
    UINT32 DramHoleBase:8;           ///< DRAM Hole Base
  } Field;
  UINT32  Value;
} DRAM_HOLE_CONTROL_REGISTER;

/* DRAM Regions */
#define NUMBER_OF_DRAM_REGIONS       0x10
#define DRAM_REGION_REGISTER_OFFSET  0x8

/* DRAM Base Address Register */
#define DRAMBASEADDR0_FUNC 0x0
#define DRAMBASEADDR0_REG  0x110
#define DRAMBASEADDR0_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMBASEADDR0_FUNC, DRAMBASEADDR0_REG)
#define DF_DramBaseAddress0    DRAMBASEADDR0_PCI_ADDR

#define DRAMBASEADDR1_FUNC 0x0
#define DRAMBASEADDR1_REG  0x118
#define DRAMBASEADDR1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMBASEADDR1_FUNC, DRAMBASEADDR1_REG)
#define DF_DramBaseAddress1    DRAMBASEADDR1_PCI_ADDR

#define DRAM_INTLV_ADDR_SEL_SHIFT         8
#define DRAM_INTLV_ADDR_SEL_MASK          0xFF
#define DRAM_INTLV_ADDR_SEL_SUPPORT_MASK  0x0F

/// DRAM Base Address Register
typedef union {
  struct {                           ///< Bitfields of DRAM Base Address Register
    UINT32 AddrRngVal:1;             ///< Address Range Valid
    UINT32 LgcyMmioHoleEn:1;         ///< Legacy MMIO Hole Enable
    UINT32 :2;                       ///< Reserved
    UINT32 IntLvNumChan:4;           ///< Interleave Number Of Channels
    UINT32 IntLvAddrSel:3;           ///< Interleave Address Select
    UINT32 :1;                       ///< Reserved
    UINT32 DramBaseAddr:20;          ///< DRAM Base Address
  } Field;
  UINT32  Value;
} DRAM_BASE_ADDRESS_REGISTER;

/* DRAM Limit Address Register */
#define DRAMLIMITADDR0_FUNC 0x0
#define DRAMLIMITADDR0_REG  0x114
#define DRAMLIMITADDR0_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMLIMITADDR0_FUNC, DRAMLIMITADDR0_REG)
#define DF_DramLimitAddress0    DRAMLIMITADDR0_PCI_ADDR

#define DRAMLIMITADDR1_FUNC 0x0
#define DRAMLIMITADDR1_REG  0x11C
#define DRAMLIMITADDR1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMLIMITADDR1_FUNC, DRAMLIMITADDR1_REG)
#define DF_DramLimitAddress1    DRAMLIMITADDR1_PCI_ADDR

/// DRAM Limit Address Register
typedef union {
  struct {                           ///< Bitfields of DRAM Limit Address Register
    UINT32 DstFabricID:8;            ///< Destination Fabric ID
    UINT32 IntLvNumSockets:1;        ///< Interleave Number Of Sockets
    UINT32 :1;                       ///< Reserved
    UINT32 IntLvNumDies:2;           ///< Interleave Number Of Dies
    UINT32 DramLimitAddr:20;         ///< DRAM Limit Address
  } Field;
  UINT32  Value;
} DRAM_LIMIT_ADDRESS_REGISTER;


/* DF Global Clock Gater Register */
#define DF_GLBL_CLK_GATER_FUNC 0x0
#define DF_GLBL_CLK_GATER_REG 0x3F0
#define DF_GLBL_CLK_GATER_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DF_GLBL_CLK_GATER_FUNC, DF_GLBL_CLK_GATER_REG))

/// DF Global Clock Gater Register
typedef union {
  struct {                                ///< Bitfields of DF Global Clock Gater Register
    UINT32 MGCGMode:4;                    ///< Mid-grain clock gating mode
    UINT32 :28;                           ///< Reserved
  } Field;
  UINT32 Value;
} DF_GLBL_CLK_GATER_REGISTER;

/* DF Global Control Register */
#define DF_GLBL_CTRL_FUNC 0x0
#define DF_GLBL_CTRL_REG 0x3F8
#define DF_GLBL_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DF_GLBL_CTRL_FUNC, DF_GLBL_CTRL_REG))

/// DF Global Control Register
typedef union {
  struct {                                ///< Bitfields of DF Global Control Register
    UINT32 :2;                            ///< Reserved
    UINT32 GlobalCC6SaveEn:1;             ///< Global CC6 save enable
    UINT32 DisImmSyncFloodOnFatalErr:1;   ///< Disable immediate sync flood on fatal error
    UINT32 WDTBaseSel:2;                  ///< Watchdog timer base select
    UINT32 :2;                            ///< Reserved
    UINT32 PIEWDTCntSel:3;                ///< PIE watchdog timer count select
    UINT32 :1;                            ///< Reserved
    UINT32 IOMWDTCntSel:3;                ///< IO master watchdog timer count select
    UINT32 :1;                            ///< Reserved
    UINT32 CCMWDTCntSel:3;                ///< Core coherent master watchdog timer count select
    UINT32 :13;                           ///< Reserved
  } Field;
  UINT32 Value;
} DF_GLBL_CTRL_REGISTER;

/* System Configuration Register */
#define SYSCFG_FUNC 0x1
#define SYSCFG_REG  0x200
#define SYSCFG_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, SYSCFG_FUNC, SYSCFG_REG))

/// System Configuration Register
typedef union {
  struct {                             ///< Bitfields of System Configuration Register
    UINT32 LocalDiePresent:4;          ///< Local Die Present
    UINT32 :1;                         ///< Reserved
    UINT32 OtherSocketPresent:1;       ///< Other Socket Present
    UINT32 LocalDieType0:2;            ///< Die type for local die 0
    UINT32 LocalDieType1:2;            ///< Die type for local die 1
    UINT32 LocalDieType2:2;            ///< Die type for local die 2
    UINT32 LocalDieType3:2;            ///< Die type for local die 3
    UINT32 :2;                         ///< Reserved
    UINT32 LocalDieIsMe:4;             ///< Internal die number
    UINT32 :1;                         ///< Reserved
    UINT32 MyDieType:2;                ///< Die type
    UINT32 :1;                         ///< Reserved
    UINT32 MyDieId:2;                  ///< Die ID
    UINT32 :1;                         ///< Reserved
    UINT32 MySocketId:1;               ///< Socket ID
    UINT32 :4;                         ///< Reserved
  } Field;
  UINT32  Value;
} SYS_CFG_REGISTER;

/* System Component Count Register */
#define SYSCOMPCOUNT_FUNC 0x1
#define SYSCOMPCOUNT_REG  0x204
#define SYSCOMPCOUNT_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, SYSCOMPCOUNT_FUNC, SYSCOMPCOUNT_REG))

/// System Configuration Register
typedef union {
  struct {                             ///< Bitfields of System Configuration Register
    UINT32 PIECount:8;                 ///< PIE Count
    UINT32 GCMCount:8;                 ///< GCM Count
    UINT32 IOMCount:8;                 ///< IOMS Count
    UINT32 :8;                         ///< Reserved
  } Field;
  UINT32  Value;
} SYS_COMP_COUNT_REGISTER;

/* DRAM Contention Monitor Register */
#define DRAM_CONT_MON_FUNC 0x2
#define DRAM_CONT_MON_REG 0x068
#define DRAM_CONT_MON_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAM_CONT_MON_FUNC, DRAM_CONT_MON_REG))

/// DRAM Contention Monitor Register
typedef union {
  struct {                                ///< Bitfields of DRAM Contention Monitor Register
    UINT32 DramContentionMonEn:1;         ///< DRAM contention monitor enable
    UINT32 DramContentionThresh:5;        ///< DRAM contention threshold
    UINT32 :2;                            ///< Reserved
    UINT32 UmcRdSampleWin:4;              ///< UMC read sample window
    UINT32 SpecDramRdSampleWin:4;         ///< Speculative DRAM read sample window
    UINT32 UmcRdThresh:8;                 ///< UMC read threshold
    UINT32 :8;                            ///< Reserved
  } Field;
  UINT32 Value;
} DRAM_CONT_MON_REGISTER;

/* Speculative DRAM Read Monitor Register */
#define SPEC_DRAM_RD_MON_FUNC 0x2
#define SPEC_DRAM_RD_MON_REG 0x06C
#define SPEC_DRAM_RD_MON_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, SPEC_DRAM_RD_MON_FUNC, SPEC_DRAM_RD_MON_REG))

/// Speculative DRAM Read Monitor Register
typedef union {
  struct {                                ///< Bitfields of Speculative DRAM Read Monitor Register
    UINT32 SpecDramRdMonEn:1;             ///< Speculative DRAM read monitor enable
    UINT32 SpecDramRdContentionThresh:5;  ///< Speculative DRAM read contention threshold
    UINT32 :2;                            ///< Reserved
    UINT32 SpecDramRdMissThresh:8;        ///< Speculative DRAM read miss threshold
    UINT32 UmcRdThreshLow:8;              ///< UMC read threshold low
    UINT32 UmcRdThreshHi:8;               ///< UMC read threshold high
  } Field;
  UINT32 Value;
} SPEC_DRAM_RD_MON_REGISTER;

/* IOM Control Register */
#define IOM_CTRL_FUNC 0x3
#define IOM_CTRL_REG 0x04C
#define IOM_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, IOM_CTRL_FUNC, IOM_CTRL_REG))

/// IOM Control Register
typedef union {
  struct {                              ///< Bitfields of IOM Control Register
    UINT32 EnIomActIntSysLmt:1;         ///< Enable limit on total number of active IOM
    UINT32 IomActIntSysLmt:2;           ///< Total number of active or outstanding IOM
    UINT32 :1;                          ///< Reserved
    UINT32 FrcIomNoSdpRdRspRule:1;      ///< Disable SDP Read Response ordering
    UINT32 FrcIomSdpVc7ToFtiVc4:1;      ///< Force mapping
    UINT32 FrcIomSdpVc2To7BLZero:1;     ///< Force BlockLevel
    UINT32 FrcIomSdpVc2To7Ordered:1;    ///< Treat commands as if PassPW = 0
    UINT32 FrcIomRspPPWPassPWOne:1;     ///< Force RspPWW and PPW bit to 1
    UINT32 :23;                         ///< Reserved
  } Field;
  UINT32 Value;
} IOM_CTRL_REGISTER;

/* CCM Configuration Register */
#define CCM_CFG_FUNC 0x3
#define CCM_CFG_REG 0x104
#define CCM_CFG_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CCM_CFG_FUNC, CCM_CFG_REG))

/// CCM Configuration Register
typedef union {
  struct {                                  ///< Bitfields of CCM Configuration Register
    UINT32 DisAllMemCancel:1;               ///< Disable MemCancel response.
    UINT32 DisRemoteMemCancel:1;            ///< Disable MemCancel to remote die.
    UINT32 DisPrbReqByp:1;                  ///< Disable Probe Request bypass path.
    UINT32 DisPrbRspByp:1;                  ///< Disable Probe Response bypass path.
    UINT32 DisCcmReqQByp:1;                 ///< Disable Request queue (REQQ) bypass path
    UINT32 DisCcmRspDQByp:1;                ///< Disable Read Response Bypass.
    UINT32 EnEarlyPrbRspDataReturn:1;       ///< Enable return of Probe Response dirty data to SDP without waiting for all system responses to be accumulated.
    UINT32 RspQRdRspWaterMark:6;            ///< Number of responses waiting to be scheduled to the data scheduler before the bypass path is disabled until the count falls below this threshold watermark.
    UINT32 FrcAnyVCPassPW:1;                ///< Enable PassPW bit always set.
    UINT32 FrcAnyVCRspPassPW:1;             ///< Enable Response PassPW always set
    UINT32 ForceCacheBlkRdZeroOrder:1;      ///< Force all cache block commands to fetch data in Zero word order.
    UINT32 DsPReqLmt:6;                     ///< Number of downstream Posted requests issued by CCM which may be outstanding on IO links.
    UINT32 DisSpecDramRead:1;               ///< Disable Speculative Dram Reads to Remote Die.
    UINT32 DisFastTPRWrHiPri:1;             ///< Disable high priority for Fast TPR writes
    UINT32 ForceChgToXReturnDat:1;          ///< Forces ChgToX to always return Data to CCX
    UINT32 ForceRdBlkLToC:1;                ///< Force RdBlkL to be issued as RdBlk to FTI.
    UINT32 DisMstAbtRsp:1;                  ///< Disable Master Abort Response
    UINT32 DisPciCfgMstAbtRsp:1;            ///< Disable PCI Config Master Abort Response
    UINT32 DisProtErrRsp:1;                 ///< Disable protocol violation on FTI Error Response
    UINT32 DisCcmRspDataByp:1;              ///< Disable Response Data Bypass
    UINT32 :2;                              ///< Reserved
  } Field;
  UINT32 Value;
} CCM_CFG_REGISTER;

/* CCM Configuration 1 Register */
#define CCM_CFG1_FUNC 0x3
#define CCM_CFG1_REG 0x108
#define CCM_CFG1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CCM_CFG1_FUNC, CCM_CFG1_REG))

/// CCM Configuration 1 Register
typedef union {
  struct {                                  ///< Bitfields of CCM Configuration 1 Register
    UINT32 DisReqQLPOrLLPreEmptiveByp:1;    ///< Disable Pre-emptive Bypass Path
    UINT32 DisReqQPickOutOfOrder:1;         ///< Disable out-of-order request picking
    UINT32 DisRspQPickOutOfOrder:1;         ///< Disable out-of-order response picking
    UINT32 DisPrbQPickOutOfOrder:1;         ///< Disable out-of-order probe picking
    UINT32 ForceCohSzRdWr:1;                ///< Force non-coherent commands as coherent versions
    UINT32 :1;                              ///< Reserved
    UINT32 EnExtPciGt8BTgtAbt:1;            ///< Enable extended PCI accesses
    UINT32 DisReqQResAntiStrv:1;            ///< Disable anti-starvation widget
    UINT32 DisFid0OrderMatch:1;             ///< Treat all CS as separate targets
    UINT32 EnUnorderedWrSzFullZeroConv:1;   ///< Enable WrSizedFull with ReqBlockLevel = 0
    UINT32 PrbPickStallSdpEn:1;             ///< PRBQ probe request picker is stalled
    UINT32 PrbPickStallFtiEn:1;             ///< PRBQ probe response picker is stalled
    UINT32 DatPickStallSdpEn:1;             ///< ORIGDQ picker is stalled
    UINT32 DatPickStallFtiEn:1;             ///< RSPDQ picker is stalled
    UINT32 DatDeallocStallSdpEn:1;          ///< ORIGDQ deallocation is stalled
    UINT32 DatDeallocStallFtiEn:1;          ///< RSPDQ deallocation is stalled
    UINT32 :3;                              ///< Reserved
    UINT32 ForceRequestOrdering:1;          ///< Force TgtStart/TgtDone ordering
    UINT32 AlarmClockCntSel:3;              ///< CCM alarm clock count select
    UINT32 AlarmClockBaseSel:2;             ///< CCM alarm clock timebase select
    UINT32 DisFullZeroConv:1;               ///< Disable conversion
    UINT32 :2;                              ///< Reserved
    UINT32 DisFtiParErr:1;                  ///< Disables parity error checking for FTI
    UINT32 DisRspdParErr:1;                 ///< Disables parity error checking for RSPD
    UINT32 DisSdpParErr:1;                  ///< Disables parity error checking for SPD
    UINT32 DisOrigdParErr:1;                ///< Disables parity error checking for ORIGD
  } Field;
  UINT32 Value;
} CCM_CFG1_REGISTER;

/* CAKE Response Compression Control Register */
#define CAKE_RSP_COMP_CTRL_FUNC 0x3
#define CAKE_RSP_COMP_CTRL_REG 0x280
#define CAKE_RSP_COMP_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CAKE_RSP_COMP_CTRL_FUNC, CAKE_RSP_COMP_CTRL_REG))

/* CAKE Request Compression Control Register */
#define CAKE_REQ_COMP_CTRL_FUNC 0x3
#define CAKE_REQ_COMP_CTRL_REG 0x284
#define CAKE_REQ_COMP_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CAKE_REQ_COMP_CTRL_FUNC, CAKE_REQ_COMP_CTRL_REG))

/* CAKE System Configuration Register */
#define CAKE_SYS_CFG_FUNC 0x3
#define CAKE_SYS_CFG_REG 0x288
#define CAKE_SYS_CFG_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CAKE_SYS_CFG_FUNC, CAKE_SYS_CFG_REG))

/// CAKE System Configuration Register
typedef union {
  struct {                                  ///< Bitfields of CAKE System Configuration Register
    UINT32 ConnDieId:4;                     ///< Connected Die ID
    UINT32 ConnRemoteXgmiDieId:4;           ///< Connected Remote XGMI Die ID
    UINT32 ConnLocalXgmiDieId:4;            ///< Connected Local XGMI Die ID
    UINT32 GmiConnType:2;                   ///< GMI Connection Type
    UINT32 FtiToGmiDatBypEn:1;              ///< FTI to GMI Data Bypass Enable
    UINT32 GmiToFtiDatBypEn:1;              ///< GMI to FTI Data Bypass Enable
    UINT32 GmiPackFlushFull:1;              ///< GMI Pack Flush Full
    UINT32 CakeDisblTillRst:1;              ///< CAKE Disable Until Reset
    UINT32 :14;                             ///< Reserved
  } Field;
  UINT32 Value;
} CAKE_SYS_CFG_REGISTER;

/* IOM Configuration 0 Register */
#define IOM_CFG_FUNC 0x3
#define IOM_CFG_REG 0x300
#define IOM_CFG_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, IOM_CFG_FUNC, IOM_CFG_REG))

/// IOM Configuration 0 Register
typedef union {
  struct {                                ///< Bitfields of IOM Configuration 0 Register
    UINT32 DisPairedCsMtch:1;             ///< Disable ordering of paired CS
    UINT32 DisBusLock:1;                  ///< Disable blocking commands for BusLock
    UINT32 EnReqBusLock:1;                ///< Block all NP commands
    UINT32 DisDbgPickStallFtiRsp:1;       ///< Disable DebugStall pick for Source Done
    UINT32 DisDbgPickStallSdpWrRsp:1;     ///< Disable DebugStall pick for SDP write
    UINT32 DisDbgPickStallSdpRdRsp:1;     ///< Disable DebugStall pick for SDP Read Response
    UINT32 SrcDnCsWrSzAnyPPW:1;           ///< Generate SrcDone for SDP request
    UINT32 SrcDnCsWrSzAnyBL:1;            ///< Generate SrcDone regardless of BlockLevel
    UINT32 DisSrcDnOnVc2ToVc7:1;          ///< Disable SrcDone for SDP from VC2 to VC7
    UINT32 AlarmClockBaseSel:2;           ///< IOM ordering AlarmClock timebase select
    UINT32 AlarmClockCntSel:3;            ///< IOM ordering AlarmClock Count select
    UINT32 IomHeartBeatEn:1;              ///< Configure IOM heartbeat monitoring
    UINT32 LoopBackIosRsp:1;              ///< Loop IOS reponse indication
    UINT32 ForceCohSzRdWr:1;              ///< Force probes to be issued
    UINT32 DisIoChnWrOrd:1;               ///< Disable IOS destination requests order
    UINT32 FrcIosRspPriZero:1;            ///< Force IOS reposnse to be low priority
    UINT32 DisTgtStartShortCut:1;         ///< Disable Target Start shortcut
    UINT32 LatMonFtiPrbRsp:1;             ///< Force latency monitor to measure probe response
    UINT32 LatMonTgtSel:3;                ///< Select performance Latency Monitor Target
    UINT32 DisIosRspBypass:1;             ///< Disable IOS response bypass path
    UINT32 EnAutoClrRspWtPriorOp:1;       ///< Enable automatic clearing of response wait code
    UINT32 DevMsgIoChnWrOnly:1;           ///< Allow device message requests to set chain bit
    UINT32 :5;                            ///< Reserved
  } Field;
  UINT32 Value;
} IOM_CFG_REGISTER;

/* Core Coherent Master Configuration Access Control */
#define CORE_MASTER_ACC_CTRL_FUNC 0x4
#define CORE_MASTER_ACC_CTRL_REG  0x44
#define CORE_MASTER_ACC_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CORE_MASTER_ACC_CTRL_FUNC, CORE_MASTER_ACC_CTRL_REG))

/// Core Coherent Master Configuration Access Control
typedef union {
  struct {                              ///< Bitfields of Core Coherent Master Configuration Access Control
    UINT32 EnableCf8ExtCfg:1;           ///< Enable PCI extended configuration register
    UINT32 DisPciCfgReg:1;              ///< Disable CFC/CF8 Accesses to IO space
    UINT32 :30;                         ///< Reserved
  } Field;
  UINT32 Value;
} CORE_MASTER_ACC_CTRL_REGISTER;

/* Fabric Indirect Config Access Address 3 Register */
#define FICAA3_FUNC 0x4
#define FICAA3_REG 0x05C
#define FICAA3_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FICAA3_FUNC, FICAA3_REG))

/// Fabric Indirect Config Access Address 3 Register
typedef union {
  struct {                           ///< Bitfields of Fabric Indirect Config Access Address 3 Register
    UINT32 CfgRegInstAccEn:1;        ///< CfgRegInstAccEn
    UINT32 :1;                       ///< Reserved
    UINT32 IndCfgAccRegNum:9;        ///< IndCfgAccRegNum
    UINT32 IndCfgAccFuncNum:3;       ///< IndCfgAccFuncNum
    UINT32 SixtyFourBitRegEn:1;      ///< SixtyFourBitRegEn
    UINT32 :1;                       ///< Reserved
    UINT32 CfgRegInstID:8;           ///< CfgRegInstID
    UINT32 :8;                       ///< Reserved
  } Field;                           ///<
  UINT32 Value;                      ///<
} FABRIC_IND_CFG_ACCESS_ADDR_3_REGISTER;

/* Fabric Indirect Config Access Data Low 3 Register */
#define FICAA3_DATA_LO_FUNC 0x4
#define FICAA3_DATA_LO_REG 0x98
#define FICAA3_DATA_LO_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FICAA3_DATA_LO_FUNC, FICAA3_DATA_LO_REG))

/* Fabric Indirect Config Access Data High 3 Register */
#define FICAA3_DATA_HI_FUNC 0x4
#define FICAA3_DATA_HI_REG 0x9C
#define FICAA3_DATA_HI_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FICAA3_DATA_HI_FUNC, FICAA3_DATA_HI_REG))

/* Master Request Control Register */
#define MASTER_REQ_CTRL_FUNC 0x4
#define MASTER_REQ_CTRL_REG 0x0C0
#define MASTER_REQ_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, MASTER_REQ_CTRL_FUNC, MASTER_REQ_CTRL_REG))

/// Master Request Control Register
typedef union {
  struct {                              ///< Bitfields of Master Request Control Register
    UINT32 EnPerDramChActReqLmt:1;      ///< Enable bypass saturation count
    UINT32 :3;                          ///< Reserved
    UINT32 MstDramActReqLmt:8;          ///< Master to DRAM Active Request Limit
    UINT32 MstIoNpActReqLmt:6;          ///< Master to IO Non-Posted Active Request Limit
    UINT32 :2;                          ///< Reserved
    UINT32 MstReqThrottle:5;            ///< Throttle rate of the Master components
    UINT32 :1;                          ///< Reserved
    UINT32 MstIoReqThrottle:5;          ///< IO request throttle rate
    UINT32 :1;                          ///< Reserved
  } Field;
  UINT32 Value;
} MASTER_REQ_CTRL_REGISTER;

/* Master Request Priority Register */
#define MASTER_REQ_PRI_FUNC 0x4
#define MASTER_REQ_PRI_REG 0x0C4
#define MASTER_REQ_PRI_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, MASTER_REQ_PRI_FUNC, MASTER_REQ_PRI_REG))

/// Master Request Priority Register
typedef union {
  struct {                             ///< Bitfields of Master Request Priority Register
    UINT32 UseSdpReqPri:1;             ///< Use SDP request priority
    UINT32 :3;                         ///< Reserved
    UINT32 DefRdReqPri:4;              ///< Default read request priority
    UINT32 DefWrReqPri:4;              ///< Default write request priority
    UINT32 LLRdReqPri:4;               ///< Light load read request priority
    UINT32 LPRdReqPri:4;               ///< Lone potato read request priority
    UINT32 :12;                        ///< Reserved
  } Field;
  UINT32 Value;
} MASTER_REQ_PRI_REGISTER;

/* Master Light Load And Lone Potato Request Priority Threshold Register */
#define MASTER_LL_LP_REQ_PRI_THRESH_FUNC 0x4
#define MASTER_LL_LP_REQ_PRI_THRESH_REG 0x0C8
#define MASTER_LL_LP_REQ_PRI_THRESH_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, MASTER_LL_LP_REQ_PRI_THRESH_FUNC, MASTER_LL_LP_REQ_PRI_THRESH_REG))

/// Master Light Load And Lone Potato Request Priority Threshold Register
typedef union {
  struct {                             ///< Bitfields of Master Light Load And Lone Potato Request Priority Threshold Register
    UINT32 LLElvPriReqThr:4;           ///< Light load elevated priority request threshold
    UINT32 :4;                         ///< Reserved
    UINT32 LLCumElvPriReqThr:6;        ///< Light load cumulative elevated priority request threshold
    UINT32 :2;                         ///< Reserved
    UINT32 LPElvPriReqThr:3;           ///< Lone potato elevated priority request threshold
    UINT32 :1;                         ///< Reserved
    UINT32 LPCumElvPriReqThr:5;        ///< Lone potato cumulative elevated priority request threshold
    UINT32 :7;                         ///< Reserved
  } Field;
  UINT32 Value;
} MASTER_LL_LP_REQ_PRI_THRESH_REGISTER;

/* Cstate Control Register */
#define CSTATE_CTRL_FUNC 0x5
#define CSTATE_CTRL_REG 0x300
#define CSTATE_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, CSTATE_CTRL_FUNC, CSTATE_CTRL_REG))

/// Cstate Control Register
typedef union {
  struct {                             ///< Bitfields of Cstate Control Register
    UINT32 DfInCstate:1;               ///< DF in CState
    UINT32 AllClientsIdle:1;           ///< All clients idle
    UINT32 AnyGmiDown:1;               ///< Any GMI down
    UINT32 DfRegsNotRestored:1;        ///< DF registers not restored
    UINT32 PickLoadStepBusy:1;         ///< Pick load step busy
    UINT32 DfCstateDisable:1;          ///< DF CState disable
    UINT32 DfCstateEntryDisable:1;     ///< DF CState entry disable
    UINT32 DfCstateAsyncWakeDisable:1; ///< DF CState asyncrhonous wake disable
    UINT32 DfCstateMmStutterOptEn:1;   ///< DF CState MM stutter
    UINT32 DfCstateMmPwrGateOptEn:1;   ///< DF CState MM power gate
    UINT32 DfCstateDceElptModeEn:1;    ///< DF CState DCE eLPT mode
    UINT32 DfCstatePwrGateEn:1;        ///< DF CState power gate
    UINT32 DfCstateClkPwrDnEn:1;       ///< DF CState clock power down
    UINT32 DfCstateSelfRefrEn:1;       ///< DF CState self refresh
    UINT32 DfCstateGmiPwrDnEn:1;       ///< DF CState GMI power down
    UINT32 DfCstateXgmiPwrDnEn:1;      ///< DF CState xGMI power down
    UINT32 PerDieDfCstateEn:1;         ///< Per die DF CState
    UINT32 :15;                        ///< Reserved
  } Field;
  UINT32 Value;
} CSTATE_CTRL_REGISTER;

/* Pstate S3/D3 Control Register */
#define PSTATE_S3D3_CTRL_FUNC 0x5
#define PSTATE_S3D3_CTRL_REG 0x304
#define PSTATE_S3D3_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, PSTATE_S3D3_CTRL_FUNC, PSTATE_S3D3_CTRL_REG))

/// Pstate S3/D3 Control Register
typedef union {
  struct {                                ///< Bitfields of Pstate S3/D3 Control Register
    UINT32 DfPstateChgBusy:1;             ///< DF Pstate change busy
    UINT32 DfS3EntryBusy:1;               ///< DF S3 entry busy
    UINT32 DfPstateChgReq:1;              ///< DF Pstate change request
    UINT32 ExpectDfPstateChg:1;           ///< Expect DF Pstate change
    UINT32 DfS3EntryReq:1;                ///< DF S3 entry request
    UINT32 NvdimmSelfRefrEn:1;            ///< NV DIMM self refresh enable
    UINT32 DfPstateChgDisableClkChg:1;    ///< DF Pstate change disable clock change
    UINT32 DfPstateChgDisableQuiesce:1;   ///< DF Pstate change disable quiesce
    UINT32 DfPstateChgDisableMstateChg:1; ///< DF Pstate change disable Mstate change
    UINT32 DfPstateChgDisableGmiChg:1;    ///< DF Pstate change disable GMI change
    UINT32 DfPstateChgDisableXgmiChg:1;   ///< DF Pstate change disable xGMI change
    UINT32 DfSaveStateStart:1;            ///< DF save state start
    UINT32 DfSaveStateDone:1;             ///< DF save state done
    UINT32 DfRestoreStateStart:1;         ///< DF restore state start
    UINT32 DfRestoreStateDone:1;          ///< DF restore state done
    UINT32 RecalibrateE12gPhyPllOnDfPstateChg:1; ///< Recal E12g phy PLL on DF Pstate change
    UINT32 :16;                           ///< Reserved
  } Field;
  UINT32 Value;
} PSTATE_S3D3_CTRL_REGISTER;

/* Multi-Die Hysteresis Control Register */
#define MULTIDIE_HYST_CTRL_FUNC 0x5
#define MULTIDIE_HYST_CTRL_REG 0x354
#define MULTIDIE_HYST_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, MULTIDIE_HYST_CTRL_FUNC, MULTIDIE_HYST_CTRL_REG))

/// Multi-Die Hysteresis Control Register
typedef union {
  struct {                             ///< Bitfields of Multi-Die Hysteresis Control Register
    UINT32 GmiDisconHyst:8;            ///< GMI disconnect hysteresis
    UINT32 XgmiDisconHyst:8;           ///< xGMI disconnect hysteresis
    UINT32 PerDieDfCstateHyst:8;       ///< Per die DF Cstate hysteresis
    UINT32 PerDieDfCstateHystScale:5;  ///< Per die DF Cstate hysteresis scale
    UINT32 :3;                         ///< Reserved
  } Field;
  UINT32 Value;
} MULTIDIE_HYST_CTRL_REGISTER;

/* Load Step Hysteresis Control Register */
#define LOAD_STEP_HYST_CTRL_FUNC 0x5
#define LOAD_STEP_HYST_CTRL_REG 0x358
#define LOAD_STEP_HYST_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, LOAD_STEP_HYST_CTRL_FUNC, LOAD_STEP_HYST_CTRL_REG))

/// Load Step Hysteresis Control Register
typedef union {
  struct {                             ///< Bitfields of Load Step Hysteresis Control Register
    UINT32 ClkLoadStepHyst:6;          ///< Clock load step hysteresis
    UINT32 ClkLoadStepHystScale:2;     ///< Clock load step hysteresis scale
    UINT32 GmiLoadStepHyst:6;          ///< GMI load step hysteresis
    UINT32 GmiLoadStepHystScale:2;     ///< GMI load step hysteresis scale
    UINT32 PickLoadStepHyst:6;         ///< Pick load step hysteresis
    UINT32 PickLoadStepHystScale:2;    ///< Pick load step hysteresis scale
    UINT32 PickLoadStepThrottle0:4;    ///< Pick load step throttle 0
    UINT32 PickLoadStepThrottle1:4;    ///< Pick load step throttle 1
  } Field;
  UINT32 Value;
} LOAD_STEP_HYST_CTRL_REGISTER;

/* DRAM Scrubber Base Address Register */
#define DRAMSCRUBBASEADDR_FUNC 0x6
#define DRAMSCRUBBASEADDR_REG  0x048
#define DRAMSCRUBBASEADDR_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMSCRUBBASEADDR_FUNC, DRAMSCRUBBASEADDR_REG)

/// DRAM Scrubber Base Address Register
typedef union {
  struct {                             ///< Bitfields of DRAM Scrubber Base Address Register
    UINT32 DramScrubEn:1;              ///< DRAM Scrub Enable
    UINT32 :3;                         ///< Reserved
    UINT32 DramScrubBaseAddr:28;       ///< DRAM Scrub Base Address
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_BASE_ADDR_REGISTER;

/* DRAM Scrubber Limit Address Register */
#define DRAMSCRUBLIMITADDR_FUNC 0x6
#define DRAMSCRUBLIMITADDR_REG  0x04C
#define DRAMSCRUBLIMITADDR_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMSCRUBLIMITADDR_FUNC, DRAMSCRUBLIMITADDR_REG)

/// DRAM Scrubber Limit Address Register
typedef union {
  struct {                             ///< Bitfields of DRAM Scrubber Limit Address Register
    UINT32 DramScrubRate:4;            ///< DRAM Scrub Rate
    UINT32 DramScrubLimitAddr:28;      ///< DRAM Scrub Limit Address
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_LIMIT_ADDR_REGISTER;

/* DRAM Scrubber Address Low Register */
#define DRAMSCRUBADDRLO_FUNC 0x6
#define DRAMSCRUBADDRLO_REG  0x050
#define DRAMSCRUBADDRLO_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMSCRUBADDRLO_FUNC, DRAMSCRUBADDRLO_REG)

/// DRAM Scrubber Address Low Register
typedef union {
  struct {                             ///< Bitfields of DRAM Scrubber Address Low Register
    UINT32 MemInitEnable:1;            ///< MemInitEnable
    UINT32 MemInitDone:1;              ///< MemInitDone
    UINT32 DisMemInit:1;               ///< DisMemInit
    UINT32 :3;                         ///< Reserved
    UINT32 SeqScrubAddrLo:26;          ///< SeqScrubAddrLo
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_ADDR_LO_REGISTER;

/* DRAM Scrubber Address High Register */
#define DRAMSCRUBADDRHI_FUNC 0x6
#define DRAMSCRUBADDRHI_REG  0x054
#define DRAMSCRUBADDRHI_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, DRAMSCRUBADDRHI_FUNC, DRAMSCRUBADDRHI_REG)

/// DRAM Scrubber Address High Register
typedef union {
  struct {                             ///< Bitfields of DRAM Scrubber Address High Register
    UINT32 SeqScrubAddrHi:16;          ///< SeqScrubAddrHi
    UINT32 :16;                        ///< Reserved
  } Fields;
  UINT32  Value;
} DRAM_SCRUB_ADDR_HI_REGISTER;

/* Redirect Scrubber Control Register */
#define REDIRECTSCRUBCTRL_FUNC 0x6
#define REDIRECTSCRUBCTRL_REG  0x058
#define REDIRECTSCRUBCTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, REDIRECTSCRUBCTRL_FUNC, REDIRECTSCRUBCTRL_REG)

/// DRAM Scrubber Address High Register
typedef union {
  struct {                             ///< Bitfields of DRAM Scrubber Address High Register
    UINT32 EnRedirScrub:1;             ///< Enable redirect scrub
    UINT32 RedirScrubReqLmt:2;         ///< Redirect Scrub limits
    UINT32 :29;                        ///< Reserved
  } Fields;
  UINT32  Value;
} REDIRECT_SCRUB_CTRL_REGISTER;

/* Trace Capture Buffer Control Register */
#define TCBCNTL_FUNC 0x6
#define TCBCNTL_REG  0x0DC
#define TCBCNTL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, TCBCNTL_FUNC, TCBCNTL_REG)

/// Trace Capture Buffer Control Register
typedef union {
  struct {                             ///< Bitfields of Trace Capture Buffer Control Register
    UINT32 TcbEn:1;                    ///< Enable Trace Capture Buffer.
    UINT32 TraceToDramEn:1;            ///< Enable Trace Capture Buffer Trace to DRAM mode.
    UINT32 AccTscMode:1;               ///< Enable Accurate TSC Mode.
    UINT32 TraceInbDat:1;              ///< This field determines which data channel is presented to Trace Capture Buffer for FrontEndD.
    UINT32 TraceInbPrb:1;              ///< This field determines which data channel is presented to Trace Capture Buffer for FrontEndB.
    UINT32 TraceReqChanFullUnitId:1;   ///< This field determines whether to trace full UnitId or full Attr field for Request channel.
    UINT32 TraceDramAddrMapSel:4;      ///< This field points to the AddrMap instance which is used to map the Trace Dram Address.
    UINT32 TscOverflowPktEn:1;         ///< TSC overflow info packet
    UINT32 TscOverflowChanSel:2;       ///< This field defines the Trace Capture Buffer Channel which is fed a TSC overflow in the event of an overflow.
    UINT32 TraceWbVcEn:1;              ///< WriteBack VC trace control.
    UINT32 TraceQWSel:2;               ///< Specify which part of the Trace Capture Buffer data value is stored with the data header.
    UINT32 TraceIosOutbDat:1;          ///< Trace IOS Outbound Data channel
    UINT32 TraceIomOutbDat:1;          ///< Trace IOM Outbound Data channel
    UINT32 TraceQosPri:2;              ///< This field determines the priority with which the trace writes are issued over FTI.
    UINT32 TscAltReset:1;              ///< TSC alternate reset value
    UINT32 :10;                        ///< Reserved
    UINT32 TcbCntlLock:1;              ///< Trace Capture Buffer Control Register write lock.
  } Field;
  UINT32  Value;
} TCB_CNTL_REGISTER;

/* Hardware Assert Status Low Register */
#define HWA_STS_LOW_FUNC 0x6
#define HWA_STS_LOW_REG 0x1F0
#define HWA_STS_LOW_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, HWA_STS_LOW_FUNC, HWA_STS_LOW_REG))

/// Hardware Assert Status Low Register
typedef union {
  struct {                             ///< Bitfields of Hardware Assert Status Low Register
    UINT32 HWAssert0:1;                ///< Hardware Assert 0
    UINT32 HWAssert1:1;                ///< Hardware Assert 1
    UINT32 HWAssert2:1;                ///< Hardware Assert 2
    UINT32 HWAssert3:1;                ///< Hardware Assert 3
    UINT32 HWAssert4:1;                ///< Hardware Assert 4
    UINT32 HWAssert5:1;                ///< Hardware Assert 5
    UINT32 HWAssert6:1;                ///< Hardware Assert 6
    UINT32 HWAssert7:1;                ///< Hardware Assert 7
    UINT32 HWAssert8:1;                ///< Hardware Assert 8
    UINT32 HWAssert9:1;                ///< Hardware Assert 9
    UINT32 HWAssert10:1;               ///< Hardware Assert 10
    UINT32 HWAssert11:1;               ///< Hardware Assert 11
    UINT32 HWAssert12:1;               ///< Hardware Assert 12
    UINT32 HWAssert13:1;               ///< Hardware Assert 13
    UINT32 HWAssert14:1;               ///< Hardware Assert 14
    UINT32 HWAssert15:1;               ///< Hardware Assert 15
    UINT32 HWAssert16:1;               ///< Hardware Assert 16
    UINT32 HWAssert17:1;               ///< Hardware Assert 17
    UINT32 HWAssert18:1;               ///< Hardware Assert 18
    UINT32 HWAssert19:1;               ///< Hardware Assert 19
    UINT32 HWAssert20:1;               ///< Hardware Assert 20
    UINT32 HWAssert21:1;               ///< Hardware Assert 21
    UINT32 HWAssert22:1;               ///< Hardware Assert 22
    UINT32 HWAssert23:1;               ///< Hardware Assert 23
    UINT32 HWAssert24:1;               ///< Hardware Assert 24
    UINT32 HWAssert25:1;               ///< Hardware Assert 25
    UINT32 HWAssert26:1;               ///< Hardware Assert 26
    UINT32 HWAssert27:1;               ///< Hardware Assert 27
    UINT32 HWAssert28:1;               ///< Hardware Assert 28
    UINT32 HWAssert29:1;               ///< Hardware Assert 29
    UINT32 HWAssert30:1;               ///< Hardware Assert 30
    UINT32 HWAssert31:1;               ///< Hardware Assert 31
  } Field;
  UINT32 Value;
} HWA_STS_LOW_REGISTER;

/* Hardware Assert Status High Register */
#define HWA_STS_HI_FUNC 0x6
#define HWA_STS_HI_REG 0x1F4
#define HWA_STS_HI_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, HWA_STS_HI_FUNC, HWA_STS_HI_REG))

/// Hardware Assert Status High Register
typedef union {
  struct {                             ///< Bitfields of Hardware Assert Status High Register
    UINT32 HWAssert0:1;                ///< Hardware Assert 0
    UINT32 HWAssert1:1;                ///< Hardware Assert 1
    UINT32 HWAssert2:1;                ///< Hardware Assert 2
    UINT32 HWAssert3:1;                ///< Hardware Assert 3
    UINT32 HWAssert4:1;                ///< Hardware Assert 4
    UINT32 HWAssert5:1;                ///< Hardware Assert 5
    UINT32 HWAssert6:1;                ///< Hardware Assert 6
    UINT32 HWAssert7:1;                ///< Hardware Assert 7
    UINT32 HWAssert8:1;                ///< Hardware Assert 8
    UINT32 HWAssert9:1;                ///< Hardware Assert 9
    UINT32 HWAssert10:1;               ///< Hardware Assert 10
    UINT32 HWAssert11:1;               ///< Hardware Assert 11
    UINT32 HWAssert12:1;               ///< Hardware Assert 12
    UINT32 HWAssert13:1;               ///< Hardware Assert 13
    UINT32 HWAssert14:1;               ///< Hardware Assert 14
    UINT32 HWAssert15:1;               ///< Hardware Assert 15
    UINT32 HWAssert16:1;               ///< Hardware Assert 16
    UINT32 HWAssert17:1;               ///< Hardware Assert 17
    UINT32 HWAssert18:1;               ///< Hardware Assert 18
    UINT32 HWAssert19:1;               ///< Hardware Assert 19
    UINT32 HWAssert20:1;               ///< Hardware Assert 20
    UINT32 HWAssert21:1;               ///< Hardware Assert 21
    UINT32 HWAssert22:1;               ///< Hardware Assert 22
    UINT32 HWAssert23:1;               ///< Hardware Assert 23
    UINT32 HWAssert24:1;               ///< Hardware Assert 24
    UINT32 HWAssert25:1;               ///< Hardware Assert 25
    UINT32 HWAssert26:1;               ///< Hardware Assert 26
    UINT32 HWAssert27:1;               ///< Hardware Assert 27
    UINT32 HWAssert28:1;               ///< Hardware Assert 28
    UINT32 HWAssert29:1;               ///< Hardware Assert 29
    UINT32 HWAssert30:1;               ///< Hardware Assert 30
    UINT32 HWAssert31:1;               ///< Hardware Assert 31
  } Field;
  UINT32 Value;
} HWA_STS_HI_REGISTER;

/* Hardware Assert Status Low Register */
#define HWA_MASK_LOW_FUNC 0x6
#define HWA_MASK_LOW_REG 0x1F8
#define HWA_MASK_LOW_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, HWA_MASK_LOW_FUNC, HWA_MASK_LOW_REG))

/// Hardware Assert Mask Low Register
typedef union {
  struct {                             ///< Bitfields of Hardware Assert Mask Low Register
    UINT32 HWAssertMsk0:1;             ///< Hardware Assert Mask 0
    UINT32 HWAssertMsk1:1;             ///< Hardware Assert Mask 1
    UINT32 HWAssertMsk2:1;             ///< Hardware Assert Mask 2
    UINT32 HWAssertMsk3:1;             ///< Hardware Assert Mask 3
    UINT32 HWAssertMsk4:1;             ///< Hardware Assert Mask 4
    UINT32 HWAssertMsk5:1;             ///< Hardware Assert Mask 5
    UINT32 HWAssertMsk6:1;             ///< Hardware Assert Mask 6
    UINT32 HWAssertMsk7:1;             ///< Hardware Assert Mask 7
    UINT32 HWAssertMsk8:1;             ///< Hardware Assert Mask 8
    UINT32 HWAssertMsk9:1;             ///< Hardware Assert Mask 9
    UINT32 HWAssertMsk10:1;            ///< Hardware Assert Mask 10
    UINT32 HWAssertMsk11:1;            ///< Hardware Assert Mask 11
    UINT32 HWAssertMsk12:1;            ///< Hardware Assert Mask 12
    UINT32 HWAssertMsk13:1;            ///< Hardware Assert Mask 13
    UINT32 HWAssertMsk14:1;            ///< Hardware Assert Mask 14
    UINT32 HWAssertMsk15:1;            ///< Hardware Assert Mask 15
    UINT32 HWAssertMsk16:1;            ///< Hardware Assert Mask 16
    UINT32 HWAssertMsk17:1;            ///< Hardware Assert Mask 17
    UINT32 HWAssertMsk18:1;            ///< Hardware Assert Mask 18
    UINT32 HWAssertMsk19:1;            ///< Hardware Assert Mask 19
    UINT32 HWAssertMsk20:1;            ///< Hardware Assert Mask 20
    UINT32 HWAssertMsk21:1;            ///< Hardware Assert Mask 21
    UINT32 HWAssertMsk22:1;            ///< Hardware Assert Mask 22
    UINT32 HWAssertMsk23:1;            ///< Hardware Assert Mask 23
    UINT32 HWAssertMsk24:1;            ///< Hardware Assert Mask 24
    UINT32 HWAssertMsk25:1;            ///< Hardware Assert Mask 25
    UINT32 HWAssertMsk26:1;            ///< Hardware Assert Mask 26
    UINT32 HWAssertMsk27:1;            ///< Hardware Assert Mask 27
    UINT32 HWAssertMsk28:1;            ///< Hardware Assert Mask 28
    UINT32 HWAssertMsk29:1;            ///< Hardware Assert Mask 29
    UINT32 HWAssertMsk30:1;            ///< Hardware Assert Mask 30
    UINT32 HWAssertMsk31:1;            ///< Hardware Assert Mask 31
  } Field;
  UINT32 Value;
} HWA_MASK_LOW_REGISTER;

/* Hardware Assert Mask High Register */
#define HWA_MASK_HI_FUNC 0x6
#define HWA_MASK_HI_REG 0x1FC
#define HWA_MASK_HI_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, HWA_MASK_HI_FUNC, HWA_MASK_HI_REG))

/// Hardware Assert Mask High Register
typedef union {
  struct {                             ///< Bitfields of Hardware Assert Mask High Register
    UINT32 HWAssertMsk0:1;             ///< Hardware Assert Mask 0
    UINT32 HWAssertMsk1:1;             ///< Hardware Assert Mask 1
    UINT32 HWAssertMsk2:1;             ///< Hardware Assert Mask 2
    UINT32 HWAssertMsk3:1;             ///< Hardware Assert Mask 3
    UINT32 HWAssertMsk4:1;             ///< Hardware Assert Mask 4
    UINT32 HWAssertMsk5:1;             ///< Hardware Assert Mask 5
    UINT32 HWAssertMsk6:1;             ///< Hardware Assert Mask 6
    UINT32 HWAssertMsk7:1;             ///< Hardware Assert Mask 7
    UINT32 HWAssertMsk8:1;             ///< Hardware Assert Mask 8
    UINT32 HWAssertMsk9:1;             ///< Hardware Assert Mask 9
    UINT32 HWAssertMsk10:1;            ///< Hardware Assert Mask 10
    UINT32 HWAssertMsk11:1;            ///< Hardware Assert Mask 11
    UINT32 HWAssertMsk12:1;            ///< Hardware Assert Mask 12
    UINT32 HWAssertMsk13:1;            ///< Hardware Assert Mask 13
    UINT32 HWAssertMsk14:1;            ///< Hardware Assert Mask 14
    UINT32 HWAssertMsk15:1;            ///< Hardware Assert Mask 15
    UINT32 HWAssertMsk16:1;            ///< Hardware Assert Mask 16
    UINT32 HWAssertMsk17:1;            ///< Hardware Assert Mask 17
    UINT32 HWAssertMsk18:1;            ///< Hardware Assert Mask 18
    UINT32 HWAssertMsk19:1;            ///< Hardware Assert Mask 19
    UINT32 HWAssertMsk20:1;            ///< Hardware Assert Mask 20
    UINT32 HWAssertMsk21:1;            ///< Hardware Assert Mask 21
    UINT32 HWAssertMsk22:1;            ///< Hardware Assert Mask 22
    UINT32 HWAssertMsk23:1;            ///< Hardware Assert Mask 23
    UINT32 HWAssertMsk24:1;            ///< Hardware Assert Mask 24
    UINT32 HWAssertMsk25:1;            ///< Hardware Assert Mask 25
    UINT32 HWAssertMsk26:1;            ///< Hardware Assert Mask 26
    UINT32 HWAssertMsk27:1;            ///< Hardware Assert Mask 27
    UINT32 HWAssertMsk28:1;            ///< Hardware Assert Mask 28
    UINT32 HWAssertMsk29:1;            ///< Hardware Assert Mask 29
    UINT32 HWAssertMsk30:1;            ///< Hardware Assert Mask 30
    UINT32 HWAssertMsk31:1;            ///< Hardware Assert Mask 31
  } Field;
  UINT32 Value;
} HWA_MASK_HI_REGISTER;

#pragma pack (pop)
#endif /* _FABRIC_REGISTERS_ZP_H_ */

