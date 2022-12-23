/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD UNB Register Table Related Functions
 *
 * Contains the definition of the UNB PCI registers with BKDG recommended values
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
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

#ifndef _UNB_REGISTERS_H_
#define _UNB_REGISTERS_H_
#pragma pack (push, 1)

/*
 *--------------------------------------------------------------
 *
 *                      M O D U L E S    U S E D
 *
 *---------------------------------------------------------------
 */

/*
 *--------------------------------------------------------------
 *
 *                      D E F I N I T I O N S  /  M A C R O S
 *
 *---------------------------------------------------------------
 */

#define NM_NB_PS_REG 4               /* Number of NB P-state registers */
#define NB_CFG_HIGH_REG              0x8C


/*
 * --------------------------------------------------------------------------------------
 *
 *             D E F I N E S    /   T Y P E D E F S   /  S T R U C T U R E S
 *
 * --------------------------------------------------------------------------------------
 */
/* SVI VID Encoding */

///< Union structure of VID in SVI1/SVI2 modes
typedef union {
  UINT32     RawVid;                 ///< Raw VID value
  struct {                           ///< SVI2 mode VID structure
    UINT32   Vid_6_0:7;              ///< Vid[6:0] of SVI2 mode
    UINT32   Vid_7:1;                ///< Vid[7] of SVI2 mode
  } SVI2;
  struct {                           ///< SVI1 mode VID structure
    UINT32   Vid_LSB_Ignore:1;       ///< Ignored LSB of 8bit VID encoding in SVI1 mode
    UINT32   Vid_6_0:1;              ///< Vid[6:0] of SVI mode
  } SVI1;
} SVI_VID;

/* Software P-state Limit Register F3x68 */
#define SW_PSTATE_LIMIT_REG 0x68
#define SW_PSTATE_LIMIT_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_3, SW_PSTATE_LIMIT_REG))

/// Software P-state Limit Register
typedef struct {
  UINT32 :5;                         ///< Reserved
  UINT32 SwPstateLimitEn:1;          ///< SwPstateLimitEn
  UINT32 :22;                        ///< Reserved
  UINT32 SwPstateLimit:3;            ///< SwPstateLimit
  UINT32 :1;                         ///< Reserved
} SW_PSTATE_LIMIT_REGISTER;

/* Popup P-state Register F3xA8 */
#define POPUP_PSTATE_REG 0xA8
#define POPUP_PSTATE_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_3, POPUP_PSTATE_REG))

/// Popup P-state Register
typedef struct {
  UINT32 :24;                        ///< Reserved
  UINT32 Reserved:1;                 ///< Reserved
  UINT32 :4;                         ///< Reserved
  UINT32 PopDownPstate:3;            ///< PopDownPstate
} POPUP_PSTATE_REGISTER;

/* Clock Power/Timing Control 2 Register F3xDC */
#define CPTC2_REG 0xDC
#define CPTC2_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_3, CPTC2_REG))

/// Clock Power Timing Control 2 PCI Register
typedef struct {
  UINT32 :7;                         ///< Reserved
  UINT32 FastSprSaveRestEn:1;        ///< FastSprSaveRestEn
  UINT32 HwPstateMaxVal:3;           ///< HW P-state maximum value
  UINT32 :1;                         ///< Reserved
  UINT32 NbsynPtrAdj:3;              ///< NB/Core sync FIFO ptr adjust
  UINT32 NbsynPtrAdjPstate_0:1;      ///< NB/core synchronization FIFO pointer adjust P-state[0]
  UINT32 CacheFlushOnHaltCtl:3;      ///< Cache flush on halt control
  UINT32 CacheFlushOnHaltTmr:7;      ///< Cache flush on halt timer
  UINT32 IgnCpuPrbEn:1;              ///< ignore CPU probe enable
  UINT32 NbsynPtrAdjLo:3;            ///< NB/core synchronization FIFO pointer adjust low
  UINT32 NbsynPtrAdjPstate_2_1:2;    ///< NB/core synchronization FIFO pointer adjust P-state[2:1]
} CLK_PWR_TIMING_CTRL2_REGISTER;

/* Northbridge Capabilities Register F3xE8 */
#define NB_CAPS_REG 0xE8
#define NB_CAPS_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_3, NB_CAPS_REG))

/// Northbridge Capabilities PCI Register
typedef struct {
  UINT32 :1;                         ///< Reserved
  UINT32 DualNode:1;                 ///< Dual-node multi-processor capable
  UINT32 EightNode:1;                ///< Eight-node multi-processor capable
  UINT32 Ecc:1;                      ///< ECC capable
  UINT32 Chipkill:1;                 ///< Chipkill ECC capable
  UINT32 :3;                         ///< Reserved
  UINT32 MctCap:1;                   ///< Memory controller capable
  UINT32 SvmCapable:1;               ///< SVM capable
  UINT32 HtcCapable:1;               ///< HTC capable
  UINT32 :3;                         ///< Reserved
  UINT32 MultVidPlane:1;             ///< Multiple VID plane capable
  UINT32 :4;                         ///< Reserved
  UINT32 x2Apic:1;                   ///< x2Apic capability
  UINT32 :4;                         ///< Reserved
  UINT32 MemPstateCap:1;             ///< Memory P-state capable
  UINT32 :3;                         ///< Reserved
  UINT32 SUCCOR:1;                   ///< SUCCOR
  UINT32 :3;                         ///< Reserved
} NB_CAPS_REGISTER;

/* Hardware thermal control register */
#define HTC_REG 0xD8200C64ul

/// Hardware Thermal Control PCI Register
typedef struct {
  UINT32 HtcEn:1;                    ///< HTC Enable
  UINT32 :3;                         ///< Reserved
  UINT32 HtcAct:1;                   ///< HTC Active State
  UINT32 HtcActLog:1;                ///< HTC Active Log
  UINT32 HtcApicHiEn:1;              ///< P-state limit higher APIC interrupt enable
  UINT32 HtcApicLoEn:1;              ///< P-state limit lower APIC interrupt enable
  UINT32 :2;                         ///< Reserved
  UINT32 HtcToGnbEn:1;               ///< HtcToGnbEn
  UINT32 ProcHotToGnbEn:1;           ///< ProcHotToGnbEn
  UINT32 :4;                         ///< Reserved
  UINT32 HtcTmpLmt:7;                ///< HTC temperature limit
  UINT32 HtcSlewSel:1;               ///< HTC slew-controlled temp select
  UINT32 HtcHystLmt:4;               ///< HTC hysteresis
  UINT32 HtcPstateLimit:3;           ///< HTC P-state limit select
  UINT32 :1;                         ///< Reserved
} HTC_REGISTER;

/* Northbridge Configuration 4  F5x88*/
#define NB_CFG_REG4 0x88
#define NB_CFG_REG4_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_5, NB_CFG_REG4))

/// Northbridge Configuration 4 PCI Register
typedef struct {
  UINT32 :14;                        ///< Reserved
  UINT32 DisHldRegRdRspChk:1;        ///< DisHldRegRdRspChk
  UINT32 :3;                         ///< Reserved
  UINT32 EnCstateBoostBlockCC6Exit:1;///< EnCstateBoostBlockCC6Exit
  UINT32 :5;                         ///< Reserved
  UINT32 DisHbNpReqBusLock:1;        ///< DisHbNpReqBusLock
  UINT32 :7;                         ///< Reserved
} NB_CFG_4_REGISTER;

/* C-state Control 1 Register D18F4x118 */
#define CSTATE_CTRL1_REG 0x118
#define CSTATE_CTRL1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_4, CSTATE_CTRL1_REG))

/// C-state Control 1 Register
typedef struct {
  UINT32 CpuPrbEnCstAct0:1;          ///< Core direct probe enable
  UINT32 CacheFlushEnCstAct0:1;      ///< Cache flush enable
  UINT32 CacheFlushTmrSelCstAct0:2;  ///< Cache flush timer select
  UINT32 :1;                         ///< Reserved
  UINT32 ClkDivisorCstAct0:3;        ///< Clock divisor
  UINT32 PwrGateEnCstAct0:1;         ///< Power gate enable
  UINT32 PwrOffEnCstAct0:1;          ///< C-state action field 3
  UINT32 NbPwrGate0:1;               ///< NB power-gating 0
  UINT32 NbClkGate0:1;               ///< NB clock-gating 0
  UINT32 SelfRefr0:1;                ///< Self-refresh 0
  UINT32 SelfRefrEarly0:1;           ///< Allow early self-refresh 0
  UINT32 :2;                         ///< Reserved
  UINT32 CpuPrbEnCstAct1:1;          ///< Core direct probe enable
  UINT32 CacheFlushEnCstAct1:1;      ///< Cache flush eable
  UINT32 CacheFlushTmrSelCstAct1:2;  ///< Cache flush timer select
  UINT32 :1;                         ///< Reserved
  UINT32 ClkDivisorCstAct1:3;        ///< Clock divisor
  UINT32 PwrGateEnCstAct1:1;         ///< Power gate enable
  UINT32 PwrOffEnCstAct1:1;          ///< C-state action field 3
  UINT32 NbPwrGate1:1;               ///< NB power-gating 1
  UINT32 NbClkGate1:1;               ///< NB clock-gating 1
  UINT32 SelfRefr1:1;                ///< Self-refresh 1
  UINT32 SelfRefrEarly1:1;           ///< Allow early self-refresh 1
  UINT32 :2;                         ///< Reserved
} CSTATE_CTRL1_REGISTER;

/* C-state Control 2 Register D18F4x11C */
#define CSTATE_CTRL2_REG 0x11C
#define CSTATE_CTRL2_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_4, CSTATE_CTRL2_REG))

/// C-state Control 2 Register
typedef struct {
  UINT32 CpuPrbEnCstAct2:1;          ///< Core direct probe enable
  UINT32 CacheFlushEnCstAct2:1;      ///< Cache flush eable
  UINT32 CacheFlushTmrSelCstAct2:2;  ///< Cache flush timer select
  UINT32 :1;                         ///< Reserved
  UINT32 ClkDivisorCstAct2:3;        ///< Clock divisor
  UINT32 PwrGateEnCstAct2:1;         ///< Power gate enable
  UINT32 PwrOffEnCstAct2:1;          ///< C-state action field 3
  UINT32 NbPwrGate2:1;               ///< NB power-gating 2
  UINT32 NbClkGate2:1;               ///< NB clock-gating 2
  UINT32 SelfRefr2:1;                ///< Self-refresh 2
  UINT32 SelfRefrEarly2:1;           ///< Allow early self-refresh 2
  UINT32 :18;                        ///< Reserved
} CSTATE_CTRL2_REGISTER;

/* Cstate Policy Control 1 Register D18F4x128 */
#define CSTATE_POLICY_CTRL1_REG 0x128
#define CSTATE_POLICY_CTRL1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_4, CSTATE_POLICY_CTRL1_REG))

/// Cstate Policy Control 1 Register
typedef struct {
  UINT32 CoreCStateMode:1;            ///< Specifies C-State actions
  UINT32 CoreCstatePolicy:1;          ///< Specified processor arbitration of voltage and frequency
  UINT32 HaltCstateIndex:3;           ///< Specifies the IO-based C-state that is invoked by a HLT instruction
  UINT32 CacheFlushTmr:7;             ///< Cache flush timer
  UINT32 :6;                          ///< Reserved
  UINT32 CacheFlushSucMonThreshold:3; ///< Cache flush success monitor threshold
  UINT32 CacheFlushSucMonTmrSel:2;    ///< Cache flush success monitor timer select
  UINT32 CacheFlushSucMonMispredictAct:2; ///< Cache flush success monitor mispredict action
  UINT32 :6;                          ///< Reserved
  UINT32 CstateMsgDis:1;              ///< C-state messaging disable
} CSTATE_POLICY_CTRL1_REGISTER;

/* Core Performance Boost Control Register D18F4x15C */
#define CPB_CTRL_REG 0x15C
#define CPB_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_4, CPB_CTRL_REG))

/// Core Performance Boost Control Register of Family 15h common aceess
typedef struct {
  UINT32 BoostSrc:2;                 ///< Boost source
  UINT32 NumBoostStates:3;           ///< Number of boosted states
  UINT32 :2;                         ///< Reserved
  UINT32 ApmMasterEn:1;              ///< APM master enable
  UINT32 CstatePowerEn:1;            ///< C-state power enable
  UINT32 LpmOnVidNop:1;              ///< LpmOnVidNop
  UINT32 LpmTrigger:1;               ///< LpmTrigger
  UINT32 :20;                        ///< Reserved
  UINT32 BoostLock:1;                ///< BoostLock
} CPB_CTRL_REGISTER;

/* Compute Unit Status 1  */
#define CU_STATUS_1 0x80
#define CU_STATUS_1_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_5, CU_STATUS_1))

/// Compute Unit Status 1 Register
typedef struct {
  UINT32 Enabled:8;                  ///< At least one core of a compute unit is enabled
  UINT32 :8;                         ///< Reserved
  UINT32 DualCore:8;                 ///< Both cores of a compute unit are enabled
  UINT32 :8;                         ///< Reserved
} CU_STATUS_1_REGISTER;

/* Northbridge P-state [3:0] F5x1[6C:60]  */
#define NB_PSTATE_0 0x160
#define NB_PSTATE_0_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_5, NB_PSTATE_0))

/// Northbridge P-state Register
typedef struct {
  UINT32 NbPstateEn:1;               ///< NB P-state enable
  UINT32 NbFid_5_0:6;                ///< NB frequency ID[5:0]
  UINT32 NbDid:1;                    ///< NB divisor ID
  UINT32 :2;                         ///< Reserved
  UINT32 NbVid_6_0:7;                ///< NB VID[6:0]
  UINT32 :1;                         ///< Reserved
  UINT32 MemPstate:1;                ///< Memory P-State
  UINT32 :2;                         ///< Reserved
  UINT32 NbVid_7:1;                  ///< NB VID[7]
  UINT32 NbIddDiv:2;                 ///< northbridge current divisor
  UINT32 NbIddValue:8;               ///< northbridge current value
} NB_PSTATE_REGISTER;

#define NB_PSTATE_REGISTER_NbVid_6_0_OFFSET      10
#define NB_PSTATE_REGISTER_NbVid_6_0_WIDTH       7
#define NB_PSTATE_REGISTER_NbVid_6_0_MASK        0x0001FC00ul
#define NB_PSTATE_REGISTER_NbVid_7_OFFSET        21
#define NB_PSTATE_REGISTER_NbVid_7_WIDTH         1
#define NB_PSTATE_REGISTER_NbVid_7_MASK          0x00200000ul

#define GetF15CzNbVid(NbPstateRegister) ( \
    (((NB_PSTATE_REGISTER *) NbPstateRegister)->NbVid_7 << NB_PSTATE_REGISTER_NbVid_6_0_WIDTH) \
    | ((NB_PSTATE_REGISTER *) NbPstateRegister)->NbVid_6_0)

#define SetF15CzNbVid(NbPstateRegister, NewNbVid) { \
    ((NB_PSTATE_REGISTER *) NbPstateRegister)->NbVid_6_0 = ((SVI_VID *) NewNbVid)->SVI2.Vid_6_0; \
    ((NB_PSTATE_REGISTER *) NbPstateRegister)->NbVid_7 = ((SVI_VID *) NewNbVid)->SVI2.Vid_7; \
  }

#define ConvertVidInuV(Vid)   (1550000 - (6250 * Vid)) ///< Convert VID in uV.

/* Northbridge P-state Status */
#define NB_PSTATE_CTRL 0x170
#define NB_PSTATE_CTRL_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_5, NB_PSTATE_CTRL))

/// Northbridge P-state Control Register
typedef struct {
  UINT32 NbPstateMaxVal:2;           ///< NB P-state maximum value
  UINT32 :1;                         ///< Reserved
  UINT32 NbPstateLo:2;               ///< NB P-state low
  UINT32 :1;                         ///< Reserved
  UINT32 NbPstateHi:2;               ///< NB P-state high
  UINT32 :1;                         ///< Reserved
  UINT32 NbPstateThreshold:4;        ///< NB P-state threshold
  UINT32 NbPstateDisOnP0:1;          ///< NB P-state disable on P0
  UINT32 SwNbPstateLoDis:1;          ///< Software NB P-state low disable
  UINT32 :8;                         ///< Reserved
  UINT32 NbPstateGnbSlowDis:1;       ///< Disable NB P-state transition take GnbSlow into account.
  UINT32 NbPstateLoRes:3;            ///< NB P-state low residency timer
  UINT32 NbPstateHiRes:3;            ///< NB P-state high residency timer
  UINT32 NbPstateFidVidSbcEn:1;      ///< NbPstateFidVidSbcEn
  UINT32 MemPstateDis:1;             ///< Memory P-state disable
} NB_PSTATE_CTRL_REGISTER;


/* Northbridge P-state Status */
#define NB_PSTATE_STATUS 0x174
#define NB_PSTATE_STATUS_PCI_ADDR (MAKE_SBDFO (0, 0, 0x18, FUNC_5, NB_PSTATE_STATUS))

/// Northbridge P-state Status Register
typedef struct {
  UINT32 NbPstateDis:1;              ///< Nb pstate disable
  UINT32 StartupNbPstate:2;          ///< startup northbridge Pstate number
  UINT32 CurNbFid_5_0:6;             ///< Current NB FID[5:0]
  UINT32 CurNbDid:1;                 ///< Current NB DID
  UINT32 :2;                         ///< Reserved
  UINT32 CurNbVid_6_0:7;             ///< Current NB VID[6:0]
  UINT32 CurNbPstate:2;              ///< Current NB Pstate
  UINT32 :1;                         ///< Reserved
  UINT32 CurNbPstateLo:1;            ///< CurNbPstateLo
  UINT32 CurNbVid_7:1;               ///< Current NB VID[7]
  UINT32 CurMemPstate:1;             ///< Current memory P-state
  UINT32 :6;                         ///< Reserved
  UINT32 Reserved:1;                 ///< Reserved
} NB_PSTATE_STS_REGISTER;

#define NB_PSTATE_STS_REGISTER_CurNbFid_5_0_OFFSET      3
#define NB_PSTATE_STS_REGISTER_CurNbFid_5_0_WIDTH       6
#define NB_PSTATE_STS_REGISTER_CurNbFid_5_0_MASK        0x000001F8ul

#define GetF15CzCurNbFid(NbPstateRegister) ( \
    ((NB_PSTATE_STS_REGISTER *) NbPstateRegister)->CurNbFid_5_0)

#define NB_PSTATE_STS_REGISTER_CurNbVid_6_0_OFFSET      12
#define NB_PSTATE_STS_REGISTER_CurNbVid_6_0_WIDTH       7
#define NB_PSTATE_STS_REGISTER_CurNbVid_6_0_MASK        0x0007F000ul
#define NB_PSTATE_STS_REGISTER_CurNbVid_7_OFFSET        23
#define NB_PSTATE_STS_REGISTER_CurNbVid_7_WIDTH         1
#define NB_PSTATE_STS_REGISTER_CurNbVid_7_MASK          0x00800000ul

#define GetF15CzCurNbVid(NbPstateStsRegister) ( \
    (((NB_PSTATE_STS_REGISTER *) NbPstateStsRegister)->CurNbVid_7 << NB_PSTATE_STS_REGISTER_CurNbVid_6_0_WIDTH) \
    | ((NB_PSTATE_STS_REGISTER *) NbPstateStsRegister)->CurNbVid_6_0)


#pragma pack (pop)
#endif      // _UNB_REGISTERS_H_


