/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Excavator CPU Register definition
 *
 * Contains the definition of the CPU CPUID MSRs and PCI registers with BKDG recommended values
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Ccx/Xv
 * @e \$Revision: 324690 $   @e \$Date: 2015-08-20 15:25:44 +0800 (Thu, 20 Aug 2015) $
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

#ifndef _CCX_REGISTERS_XV_H_
#define _CCX_REGISTERS_XV_H_
#pragma pack (push, 1)

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

/* Floating Point Configuration Register 0xC0011028 */
#define MSR_FP_CFG 0xC0011028ul

/// Floating Point Configuration MSR Register
typedef struct {
  UINT64 :16;                        ///< Reserved
  UINT64 DiDtMode:1;                 ///< Di/Dt Mode
  UINT64 :1;                         ///< Reserved
  UINT64 DiDtCfg0:5;                 ///< Di/Dt Config 0
  UINT64 :2;                         ///< Reserved
  UINT64 DiDtCfg2:2;                 ///< Di/Dt Config 2
  UINT64 DiDtCfg1:8;                 ///< Di/Dt Config 1
  UINT64 :5;                         ///< Reserved
  UINT64 DiDtCfg3:1;                 ///< Di/Dt Config 3
  UINT64 DiDtCfg4:4;                 ///< Di/Dt Config 4
  UINT64 :19;                        ///< Reserved
} FP_CFG_MSR;

/// LWP_CFG
typedef struct {
  UINT64 :32;              ///< Reserved
  UINT64 LwpCoreId:8;      ///< core ID
  UINT64 :24;              ///< Reserved
} LWP_CFG_MSR;

/// NB Machine Check Misc 4 (DRAM Thresholding) 0, 0x00000413
typedef struct {
  UINT64 :24;                        ///< Reserved
  UINT64 BlkPtr:8;                   ///< Block pointer for additional MISC registers
  UINT64 ErrCnt:12;                  ///< Error counter
  UINT64 :4;                         ///< Reserved
  UINT64 Ovrflw:1;                   ///< Overflow
  UINT64 IntType:2;                  ///< Interrupt type
  UINT64 CntEn:1;                    ///< Counter enable
  UINT64 LvtOffset:4;                ///< LVT offset
  UINT64 :4;                         ///< Reserved
  UINT64 IntP:1;                     ///< Intp
  UINT64 Locked:1;                   ///< Locked
  UINT64 CntP:1;                     ///< Counter present
  UINT64 Valid:1;                    ///< Valid
} MC4_MISC0_MSR;

/// NB Machine Check Misc 4 (Link thresholding) 1, 0xC0000408
typedef struct {
  UINT64 :32;                        ///< Reserved
  UINT64 ErrCnt:12;                  ///< Error counter
  UINT64 :4;                         ///< Reserved
  UINT64 Ovrflw:1;                   ///< Overflow
  UINT64 IntType:2;                  ///< Interrupt type
  UINT64 CntEn:1;                    ///< Counter enable
  UINT64 LvtOffset:4;                ///< LVT offset
  UINT64 :4;                         ///< Reserved
  UINT64 IntP:1;                     ///< IntP
  UINT64 Locked:1;                   ///< Locked
  UINT64 CntP:1;                     ///< Counter present
  UINT64 Valid:1;                    ///< Valid
} MC4_MISC1_MSR;

/* P-state Current Limit Register 0xC0010061 */
#define MSR_PSTATE_CURRENT_LIMIT 0xC0010061ul // F15 Shared

/// Pstate Current Limit MSR Register
typedef struct {
  UINT64 CurPstateLimit:3;           ///< Current Pstate Limit
  UINT64 :1;                         ///< Reserved
  UINT64 PstateMaxVal:3;             ///< Pstate Max Value
  UINT64 :57;                        ///< Reserved
} PSTATE_CURLIM_MSR;


/* P-state Control Register 0xC0010062 */
#define MSR_PSTATE_CTL 0xC0010062ul    // F15 Shared

/// Pstate Control MSR Register
typedef struct {
  UINT64 PstateCmd:3;                ///< Pstate change command
  UINT64 :61;                        ///< Reserved
} PSTATE_CTRL_MSR;


/* P-state Status Register 0xC0010063 */
#define MSR_PSTATE_STS 0xC0010063ul

/// Pstate Status MSR Register
typedef struct {
  UINT64 CurPstate:3;                ///< Current Pstate
  UINT64 :61;                        ///< Reserved
} PSTATE_STS_MSR;

/* P-state Registers 0xC00100[6B:64] */
#define MSR_PSTATE_0 0xC0010064ul
#define NM_PS_REG    8

/// P-state MSR
typedef struct {
  UINT64 CpuFid_5_0:6;               ///< CpuFid[5:0]
  UINT64 CpuDid:3;                   ///< CpuDid
  UINT64 CpuVid:8;                   ///< CpuVid
  UINT64 :5;                         ///< Reserved
  UINT64 NbPstate:1;                 ///< NbPstate
  UINT64 :9;                         ///< Reserved
  UINT64 IddValue:8;                 ///< IddValue
  UINT64 IddDiv:2;                   ///< IddDiv
  UINT64 :21;                        ///< Reserved
  UINT64 PsEnable:1;                 ///< Pstate Enable
} PSTATE_MSR;

/* COFVID Control Register 0xC0010070 */
#define MSR_COFVID_CTL 0xC0010070ul

/// COFVID Control MSR Register
typedef struct {
  UINT64 CpuFid_5_0:6;               ///< CpuFid[5:0]
  UINT64 CpuDid:3;                   ///< CpuDid
  UINT64 CpuVid_6_0:7;               ///< CpuVid[6:0]
  UINT64 PstateId:3;                 ///< Pstate ID
  UINT64 :1;                         ///< Reserved
  UINT64 CpuVid_7:1;                 ///< CpuVid[7]
  UINT64 :1;                         ///< Reserved
  UINT64 NbPstate:1;                 ///< Northbridge P-state
  UINT64 :1;                         ///< Reserved
  UINT64 NbVid:8;                    ///< NbVid
  UINT64 :32;                        ///< Reserved
} COFVID_CTRL_MSR;

/* COFVID Status Register 0xC0010071 */
#define MSR_COFVID_STS 0xC0010071ul

/// COFVID Status MSR Register
typedef struct {
  UINT64 CurCpuFid:6;                ///< Current CpuFid
  UINT64 CurCpuDid:3;                ///< Current CpuDid
  UINT64 CurCpuVid_6_0:7;            ///< Current CpuVid[6:0]
  UINT64 CurPstate:3;                ///< Current Pstate
  UINT64 :1;                         ///< Reserved
  UINT64 CurCpuVid_7:1;              ///< Current CpuVid[7]
  UINT64 :2;                         ///< Reserved
  UINT64 NbPstateDis:1;              ///< NbPstate Disable
  UINT64 CurNbVid:8;                 ///< Current NbVid[7:0]
  UINT64 StartupPstate:3;            ///< Startup Pstate
  UINT64 :14;                        ///< Reserved
  UINT64 MaxCpuCof:6;                ///< MaxCpuCof
  UINT64 :1;                         ///< Reserved
  UINT64 CurPstateLimit:3;           ///< Current Pstate Limit
  UINT64 MaxNbCof:5;                 ///< MaxNbCof
} COFVID_STS_MSR;

#define COFVID_STS_MSR_CurCpuVid_6_0_OFFSET       9
#define COFVID_STS_MSR_CurCpuVid_6_0_WIDTH        7
#define COFVID_STS_MSR_CurCpuVid_6_0_MASK         0xFE00
#define COFVID_STS_MSR_CurCpuVid_7_OFFSET         20
#define COFVID_STS_MSR_CurCpuVid_7_WIDTH          1
#define COFVID_STS_MSR_CurCpuVid_7_MASK           0x100000ul

#define GetF15CzCurCpuVid(CofVidStsMsr) ( \
  LShiftU64 (((COFVID_STS_MSR *) CofVidStsMsr)->CurCpuVid_7, COFVID_STS_MSR_CurCpuVid_6_0_WIDTH) \
  | ((COFVID_STS_MSR *) CofVidStsMsr)->CurCpuVid_6_0)

/* C-state Address Register 0xC0010073 */
#define MSR_CSTATE_ADDRESS 0xC0010073ul

/// C-state Address MSR Register
typedef struct {
  UINT64 CstateAddr:16;              ///< C-state address
  UINT64 :48;                        ///< Reserved
} CSTATE_ADDRESS_MSR;

#pragma pack (pop)
#endif      // _CCX_REGISTERS_XV_H_


