/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Zen CPU Register definition
 *
 * Contains the definition of the CPU CPUID MSRs and PCI registers with BKDG recommended values
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Ccx/Rv
 * @e \$Revision$   @e \$Date$
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

#ifndef _CCX_REGISTERS_RV_H_
#define _CCX_REGISTERS_RV_H_
#pragma pack (push, 1)

/* CPUID_Fn80000001_EBX[PkgType] definitions */
#define  RV_SOCKET_FP5  0
#define  RV_SOCKET_AM4  2
#define  RV_SOCKET_FT5  3

/* P-state Registers 0xC001006[B:4] */
#define MSR_PSTATE_0 0xC0010064ul
#define MSR_PSTATE_1 0xC0010065ul
#define MSR_PSTATE_2 0xC0010066ul
#define MSR_PSTATE_3 0xC0010067ul
#define MSR_PSTATE_4 0xC0010068ul
#define MSR_PSTATE_5 0xC0010069ul
#define MSR_PSTATE_6 0xC001006Aul
#define MSR_PSTATE_7 0xC001006Bul

#define PS_REG_BASE MSR_PSTATE_0     /* P-state Register base */
#define PS_MAX_REG  MSR_PSTATE_7     /* Maximum P-State Register */
#define PS_MIN_REG  MSR_PSTATE_0     /* Minimum P-State Register */
#define NM_PS_REG 8                  /* number of P-state MSR registers */

/* P-state Current Limit Register 0xC0010061 */
#define MSR_PSTATE_CURRENT_LIMIT 0xC0010061ul // F15 Shared

/// Pstate Current Limit MSR Register
typedef union {
  /// Bitfields of Pstate Current Limit MSR Register
  struct {
    UINT64 CurPstateLimit:3;           ///< Current Pstate Limit
    UINT64 :1;                         ///< Reserved
    UINT64 PstateMaxVal:3;             ///< Pstate Max Value
    UINT64 :57;                        ///< Reserved
  } Field;
  UINT64  Value;
} PSTATE_CURLIM_MSR;

/* P-state Control Register 0xC0010062 */
#define MSR_PSTATE_CTL 0xC0010062ul    // F15 Shared

/// Pstate Control MSR Register
typedef union {
  /// Bitfields of Pstate Control MSR Register
  struct {
    UINT64 PstateCmd:3;                ///< Pstate change command
    UINT64 :61;                        ///< Reserved
  } Field;
  UINT64  Value;
} PSTATE_CTRL_MSR;

/* P-state Status Register 0xC0010063 */
#define MSR_PSTATE_STS 0xC0010063ul

/// Pstate Status MSR Register
typedef union {
  /// Bitfields of Pstate Status MSR Register
  struct {
    UINT64 CurPstate:3;                ///< Current Pstate
    UINT64 :61;                        ///< Reserved
  } Field;
  UINT64  Value;
} PSTATE_STS_MSR;

/* P-state Registers 0xC00100[6B:64] */
#define MSR_PSTATE_0 0xC0010064ul
#define NM_PS_REG    8

/// P-state MSR
typedef union {
  /// Bitfields of P-state MSR
  struct {
    UINT64 CpuFid_7_0:8;               ///< CpuFid[7:0]
    UINT64 CpuDfsId:6;                 ///< CpuDfsId
    UINT64 CpuVid:8;                   ///< CpuVid
    UINT64 IddValue:8;                 ///< IddValue
    UINT64 IddDiv:2;                   ///< IddDiv
    UINT64 :31;                        ///< Reserved
    UINT64 PstateEn:1;                 ///< Pstate Enable
  } Field;
  UINT64  Value;
} PSTATE_MSR;

/* C-state Base Address Register 0xC0010073 */
#define MSR_CSTATE_ADDRESS 0xC0010073ul

/// C-state Address MSR Register
typedef union {
  /// Bitfields of C-state Address MSR Register
  struct {
    UINT64 CstateAddr:16;              ///< C-state address
    UINT64 :48;                        ///< Reserved
  } Field;
  UINT64  Value;
} CSTATE_ADDRESS_MSR;

/* Power Management Miscellaneous Register 0xC0010292 */
#define MSR_PWR_MGMT_MISC  0xC0010292ul

/// Power Management Miscellaneous MSR
typedef union {
  /// Bitfields of Power Management Miscellaneous MSR
  struct {
    UINT64 CurHwPstateLimit:3;        ///< Current HW Pstate limit
    UINT64 StartupPstate:3;           ///< Start up Pstate
    UINT64 DFPstateDis:1;             ///< DF Pstate disable
    UINT64 CurDFVid:8;                ///< Current DF VID
    UINT64 MaxCpuCof:6;               ///< Maximum CPU COF
    UINT64 MaxDFCof:5;                ///< Maximum DF COF
    UINT64 CpbCap:3;                  ///< CPB capability
    UINT64 :3;                        ///< Reserved
    UINT64 PC6En:1;                   ///< PC6 enable
    UINT64 :31;                       ///< Reserved
  } Field;
  UINT64  Value;
} PWR_MGMT_MISC_MSR;

/* Hardware PState Status Register 0xC0010293 */
#define MSR_HW_PSTATE_STATUS  0xC0010293ul

/// Hardware PState Status MSR
typedef union {
  /// Bitfields of Hardware PState Status MSR
  struct {
    UINT64 CurCpuFid:8;               ///< Current Pstate FID
    UINT64 CurCpuDfsId:6;             ///< Current Pstate DfsId
    UINT64 CurCpuVid:8;               ///< Current Pstate VID
    UINT64 CurHwPstate:3;             ///< Current Hw Pstate
    UINT64 :39;                       ///< Reserved
  } Field;
  UINT64  Value;
} HW_PSTATE_STATUS_MSR;

/* C-state Policy Register 0xC0010294 */
#define MSR_CSTATE_POLICY  0xC0010294ul

/// C-state Policy MSR
typedef union {
  /// Bitfields of C-state Policy MSR
  struct {
    UINT64  CC1_TMRSEL:2;              ///< CC1 Timer Select
    UINT64  CC1_TMRLEN:5;              ///< CC1 Timer Length
    UINT64  HYST_TMRSEL:2;             ///< Hysteresis Timer Select
    UINT64  HYST_TMRLEN:5;             ///< Hysteresis Timer Length
    UINT64  CFOH_TMRLEN:7;             ///< Cache Flush On Halt Timer Length
    UINT64  :11;                       ///< Reserved
    UINT64  CFSM_DURATION:7;           ///< Cache Flush Success Monitor Duration
    UINT64  CFSM_THRESHOLD:3;          ///< Cache Flush Success Monitor Threshold
    UINT64  CFSM_MISPREDACT:2;         ///< Cache Flush Success Monitor Mispredict Action
    UINT64  IRM_DECRRATE:5;            ///< Interrupt Rate Monitor Decrement Rate
    UINT64  IRM_BURSTEN:3;             ///< Interrupt Rate Monitor Burst Enable
    UINT64  IRM_THRESHOLD:4;           ///< Interrupt Rate Monitor Threshold
    UINT64  IRM_MAXDEPTH:4;            ///< Interrupt Rate Monitor Max Depth
    UINT64  CIT_EN:1;                  ///< Cstate Idle Tracker Enable
    UINT64  CIT_FASTSAMPLE:1;          ///< Cstate Idle Tracker FASTSAMPLE
    UINT64  :2;                        ///< Reserved
  } Field;
  UINT64  Value;
} CSTATE_POLICY_MSR;

/* C-state Configuration Register 0xC0010296 */
#define MSR_CSTATE_CFG  0xC0010296ul

/// C-state Configuration MSR
typedef union {
  /// Bitfields of C-state Configuration MSR
  struct {
    UINT64  CCR0_CC1DFSID:6;           ///< CCR0 CC1 DFS ID
    UINT64  CCR0_CC6EN:1;              ///< CCR0 CC6 Enable
    UINT64  :1;                        ///< Reserved
    UINT64  CCR1_CC1DFSID:6;           ///< CCR1 CC1 DFS ID
    UINT64  CCR1_CC6EN:1;              ///< CCR1 CC6 Enable
    UINT64  :1;                        ///< Reserved
    UINT64  CCR2_CC1DFSID:6;           ///< CCR2 CC1 DFS ID
    UINT64  CCR2_CC6EN:1;              ///< CCR2 CC6 Enable
    UINT64  :41;                       ///< Reserved
  } Field;
  UINT64  Value;
} CSTATE_CFG_MSR;

/* Power Management Default Register 0xC0010297 */
#define MSR_PWR_MGMT_DFLT  0xC0010297ul

/// Power Management Default MSR
typedef union {
  /// Bitfields of Power Management Default MSR
  struct {
    UINT64  CC6EXIT_DFSID:6;           ///< CC6 Exit DFS ID
    UINT64  CC6EXIT_POPUP_EN:1;        ///< CC6 Exit Pop Up Enable
    UINT64  CC6CF_DFSID:6;             ///< CC6 CF DFS ID
    UINT64  CC6CF_POPDN_EN:1;          ///< CC6 CF Pop Down Enable
    UINT64  CC6EXIT_STRETCHEN:1;       ///< CC6 Exit Stretch Enable
    UINT64  CC6EXIT_STRETCHCLKDIV2:1;  ///< CC6 Exit Stretch Clock Div 2
    UINT64  CC6EXIT_STRETCHALLDIV2:1;  ///< CC6 Exit Stretch All Div 2
    UINT64  CC6CF_STRETCHEN:1;         ///< CC6 CF Stretch Enable
    UINT64  CC6CF_STRETCHCLKDIV2:1;    ///< CC6 CF Stretch Clock Div 2
    UINT64  CC6CF_STRETCHALLDIV2:1;    ///< CC6 CF Stretch All Div 2
    UINT64  :44;                       ///< Reserved
  } Field;
  UINT64  Value;
} PWR_MGMT_DFLT_MSR;

/* MCA MISC Register 0xC0002xx3 */
#define MSR_MCA_MISC_BANK0 0xC0002003ul

/// MCA Config MSR
typedef union {
  /// Bitfields of MCA MISC MSR
  struct {
    UINT64  :24;                                 ///< Reserved
    UINT64  BlkPtr:8;                            ///< Extended MISC MSR block
    UINT64  ErrCnt:12;                           ///< Starting value of the error counter
    UINT64  :4;                                  ///< Reserved
    UINT64  Ovrflw:1;                            ///< Overflow
    UINT64  ThresholdIntType:2;                  ///< the type of interrupt signaled when Ovrflw is set
    UINT64  CntEn:1;                             ///< Count thresholding errors
    UINT64  LvtOffset:4;                         ///< the address of the LVT entry in the APIC registers
    UINT64  :4;                                  ///< Reserved
    UINT64  IntP:1;                              ///< IntP
    UINT64  Locked:1;                            ///< Locked
    UINT64  CntP:1;                              ///< CntP
    UINT64  Valid:1;                             ///< Valid
  } Field;
  UINT64  Value;
} MCA_MISC_MSR;


/* MCA Config Register 0xC0002xx4 */
#define MSR_MCA_CFG_BANK0  0xC0002004ul

/// MCA Config MSR
typedef union {
  /// Bitfields of MCA Config MSR
  struct {
    UINT64  McaX:1;                              ///< McaX
    UINT64  TransparentErrorLoggingSupported:1;  ///< TransparentErrorLoggingSupported
    UINT64  DeferredErrorLoggingSupported:1;     ///< DeferredErrorLoggingSupported
    UINT64  :2;                                  ///< Reserved
    UINT64  DeferredIntTypeSupported:1;          ///< DeferredIntTypeSupported
    UINT64  :26;                                 ///< Reserved
    UINT64  McaXEnable:1;                        ///< McaXEnable
    UINT64  TransparentErrorLoggingEnable:1;     ///< TransparentErrorLoggingEnable
    UINT64  LogDeferredInMcaStat:1;              ///< LogDeferredInMcaStat
    UINT64  :2;                                  ///< Reserved
    UINT64  DeferredIntType:2;                   ///< DeferredIntType
    UINT64  :25;                                 ///< Reserved
  } Field;
  UINT64  Value;
} MCA_CONFIG_MSR;

#pragma pack (pop)
#endif      // _CCX_REGISTERS_RV_H_


