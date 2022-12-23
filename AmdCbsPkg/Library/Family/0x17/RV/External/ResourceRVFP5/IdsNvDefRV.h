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
 *******************************************************************************
 **/


//This file is auto generated, don't edit it manually

#ifndef _IDS_NV_DEF_RV_H_
#define _IDS_NV_DEF_RV_H_

///RedirectForReturnDis
///From a workaround for GCC/C000005 issue for XV Core on CZ A0, setting MSRC001_1029 Decode Configuration (DE_CFG) bit 14 [DecfgNoRdrctForReturns] to 1
typedef enum {
  IDSOPT_CMN_CPU_GEN_W_A05_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_CPU_GEN_W_A05_1 = 1,///<1
  IDSOPT_CMN_CPU_GEN_W_A05_0 = 0,///<0
} IDSOPT_CMN_CPU_GEN_W_A05;

///L2 TLB Associativity
///0 - L2 TLB ways [11:8] are fully associative.  1 - =L2 TLB ways [11:8] are 4K-only.
typedef enum {
  IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC_0 = 0,///<0
  IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC_1 = 1,///<1
  IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC_AUTO = 3,///<Auto
} IDSOPT_CMN_CPU_L2_TLB_WAY_ALLOC;

///Platform First Error Handling
///Enable/disable PFEH, cloak individual banks, and mask deferred error interrupts from each bank.
typedef enum {
  IDSOPT_CMN_CPU_PFEH_ENABLE = 0,///<Enable
  IDSOPT_CMN_CPU_PFEH_DISABLE = 1,///<Disable
  IDSOPT_CMN_CPU_PFEH_AUTO = 3,///<Auto
} IDSOPT_CMN_CPU_PFEH;

///Core Performance Boost
///Disable CPB
typedef enum {
  IDSOPT_CMN_CPU_CPB_DISABLED = 0,///<Disabled
  IDSOPT_CMN_CPU_CPB_AUTO = 1,///<Auto
} IDSOPT_CMN_CPU_CPB;

///Global C-state Control
///Controls IO based C-state generation and DF C-states.
typedef enum {
  IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL_AUTO = 3,///<Auto
} IDSOPT_CMN_CPU_GLOBAL_CSTATE_CTRL;

///OC Mode
typedef enum {
  IDSOPT_CMN_CPU_OC_MODE_NORMALOPERATION = 0,///<Normal Operation
  IDSOPT_CMN_CPU_OC_MODE_OC1 = 1,///<OC1
  IDSOPT_CMN_CPU_OC_MODE_CUSTOMIZED = 5,///<Customized
} IDSOPT_CMN_CPU_OC_MODE;

///Streaming Stores Control
///Enables or disables the streaming stores functionality
typedef enum {
  IDSOPT_CMN_CPU_STREAMING_STORES_CTRL_DISABLED = 1,///<Disabled
  IDSOPT_CMN_CPU_STREAMING_STORES_CTRL_ENABLED = 0,///<Enabled
  IDSOPT_CMN_CPU_STREAMING_STORES_CTRL_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_CPU_STREAMING_STORES_CTRL;

///Enable IBS
///When IBS is enabled, SpecLockMap and Stack Engine are disabled.
typedef enum {
  IDSOPT_CMN_CPU_EN_IBS_DISABLED = 0,///<Disabled
  IDSOPT_CMN_CPU_EN_IBS_ENABLED = 1,///<Enabled
  IDSOPT_CMN_CPU_EN_IBS_AUTO = 3,///<Auto
} IDSOPT_CMN_CPU_EN_IBS;

///Custom Core Pstates Legal Disclaimer
///Legal Disclaimer
///Custom Core Pstates Legal Disclaimer 1
///Legal Disclaimer
///Custom Pstate0
///Disable - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P0_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P0_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P0;

///Frequency (MHz)
///Current core frequency in MHz
#define IDSOPT_CPU_COF_P0_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P0_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
///Voltage in uV (1V = 1000 * 1000 uV)
#define IDSOPT_CPU_VOLTAGE_P0_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P0_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate0 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST0_FID_MIN 0x10 ///< Min of Pstate0 FID
#define IDSOPT_CPU_PST0_FID_MAX 0xff ///< Max of Pstate0 FID

///Pstate0 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST0_DID_MIN 0x8 ///< Min of Pstate0 DID
#define IDSOPT_CPU_PST0_DID_MAX 0x30 ///< Max of Pstate0 DID

///Pstate0 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST0_VID_MIN 0 ///< Min of Pstate0 VID
#define IDSOPT_CPU_PST0_VID_MAX 0xff ///< Max of Pstate0 VID

///Custom Pstate1
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P1_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P1_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P1_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P1;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P1_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P1_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P1_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P1_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate1 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST1_FID_MIN 0x10 ///< Min of Pstate1 FID
#define IDSOPT_CPU_PST1_FID_MAX 0xff ///< Max of Pstate1 FID

///Pstate1 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST1_DID_MIN 0x8 ///< Min of Pstate1 DID
#define IDSOPT_CPU_PST1_DID_MAX 0x30 ///< Max of Pstate1 DID

///Pstate1 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST1_VID_MIN 0 ///< Min of Pstate1 VID
#define IDSOPT_CPU_PST1_VID_MAX 0xff ///< Max of Pstate1 VID

///Custom Pstate2
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P2_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P2_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P2_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P2;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P2_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P2_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P2_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P2_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate2 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST2_FID_MIN 0x10 ///< Min of Pstate2 FID
#define IDSOPT_CPU_PST2_FID_MAX 0xff ///< Max of Pstate2 FID

///Pstate2 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST2_DID_MIN 0x8 ///< Min of Pstate2 DID
#define IDSOPT_CPU_PST2_DID_MAX 0x30 ///< Max of Pstate2 DID

///Pstate2 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST2_VID_MIN 0 ///< Min of Pstate2 VID
#define IDSOPT_CPU_PST2_VID_MAX 0xff ///< Max of Pstate2 VID

///Custom Pstate3
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P3_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P3_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P3_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P3;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P3_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P3_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P3_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P3_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate3 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST3_FID_MIN 0x10 ///< Min of Pstate3 FID
#define IDSOPT_CPU_PST3_FID_MAX 0xff ///< Max of Pstate3 FID

///Pstate3 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST3_DID_MIN 0x8 ///< Min of Pstate3 DID
#define IDSOPT_CPU_PST3_DID_MAX 0x30 ///< Max of Pstate3 DID

///Pstate3 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST3_VID_MIN 0 ///< Min of Pstate3 VID
#define IDSOPT_CPU_PST3_VID_MAX 0xff ///< Max of Pstate3 VID

///Custom Pstate4
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P4_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P4_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P4_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P4;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P4_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P4_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P4_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P4_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate4 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST4_FID_MIN 0x10 ///< Min of Pstate4 FID
#define IDSOPT_CPU_PST4_FID_MAX 0xff ///< Max of Pstate4 FID

///Pstate4 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST4_DID_MIN 0x8 ///< Min of Pstate4 DID
#define IDSOPT_CPU_PST4_DID_MAX 0x30 ///< Max of Pstate4 DID

///Pstate4 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST4_VID_MIN 0 ///< Min of Pstate4 VID
#define IDSOPT_CPU_PST4_VID_MAX 0xff ///< Max of Pstate4 VID

///Custom Pstate5
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P5_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P5_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P5_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P5;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P5_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P5_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P5_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P5_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate5 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST5_FID_MIN 0x10 ///< Min of Pstate5 FID
#define IDSOPT_CPU_PST5_FID_MAX 0xff ///< Max of Pstate5 FID

///Pstate5 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST5_DID_MIN 0x8 ///< Min of Pstate5 DID
#define IDSOPT_CPU_PST5_DID_MAX 0x30 ///< Max of Pstate5 DID

///Pstate5 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST5_VID_MIN 0 ///< Min of Pstate5 VID
#define IDSOPT_CPU_PST5_VID_MAX 0xff ///< Max of Pstate5 VID

///Custom Pstate6
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P6_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P6_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P6_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P6;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P6_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P6_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P6_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P6_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate6 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST6_FID_MIN 0x10 ///< Min of Pstate6 FID
#define IDSOPT_CPU_PST6_FID_MAX 0xff ///< Max of Pstate6 FID

///Pstate6 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST6_DID_MIN 0x8 ///< Min of Pstate6 DID
#define IDSOPT_CPU_PST6_DID_MAX 0x30 ///< Max of Pstate6 DID

///Pstate6 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST6_VID_MIN 0 ///< Min of Pstate6 VID
#define IDSOPT_CPU_PST6_VID_MAX 0xff ///< Max of Pstate6 VID

///Custom Pstate7
///Disabled - disable this Pstate\nCustom - customize this Pstate, applicable only if PcdOcDisable=FALSE\n\nWARNING - DAMAGE CAUSED BY USE OF YOUR AMD PROCESSOR OUTSIDE OF SPECIFICATION OR IN EXCESS OF FACTORY SETTINGS ARE NOT COVERED UNDER YOUR AMD PRODUCT WARRANTY AND MAY NOT BE COVERED BY YOUR SYSTEM MANUFACTURER'S WARRANTY.\nOperating your AMD processor outside of specification or in excess of factory settings, including but not limited to overclocking, may damage or shorten the life of your processor or other system components, create system instabilities (e.g., data loss and corrupted images) and in extreme cases may result in total system failure. AMD does not provide support or service for issues or damages related to use of an AMD processor outside of processor specifications or in excess of factory settings.\n
typedef enum {
  IDSOPT_CPU_PST_CUSTOM_P7_DISABLED = 0,///<Disabled
  IDSOPT_CPU_PST_CUSTOM_P7_CUSTOM = 1,///<Custom
  IDSOPT_CPU_PST_CUSTOM_P7_AUTO = 2,///<Auto
} IDSOPT_CPU_PST_CUSTOM_P7;

///Frequency (MHz)
#define IDSOPT_CPU_COF_P7_MIN 0 ///< Min of Frequency (MHz)
#define IDSOPT_CPU_COF_P7_MAX 0xffffffff ///< Max of Frequency (MHz)

///Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P7_MIN 0 ///< Min of Voltage (uV)
#define IDSOPT_CPU_VOLTAGE_P7_MAX 0xffffffff ///< Max of Voltage (uV)

///Pstate7 FID
///Specifies the core frequency multiplier. COF = 200MHz * FID / DID
#define IDSOPT_CPU_PST7_FID_MIN 0x10 ///< Min of Pstate7 FID
#define IDSOPT_CPU_PST7_FID_MAX 0xff ///< Max of Pstate7 FID

///Pstate7 DID
///Specifies the core frequency divisor (DID[0] should zero if DID[5:0]>1Ah).
#define IDSOPT_CPU_PST7_DID_MIN 0x8 ///< Min of Pstate7 DID
#define IDSOPT_CPU_PST7_DID_MAX 0x30 ///< Max of Pstate7 DID

///Pstate7 VID
///Specifies the core voltage.
#define IDSOPT_CPU_PST7_VID_MIN 0 ///< Min of Pstate7 VID
#define IDSOPT_CPU_PST7_VID_MAX 0xff ///< Max of Pstate7 VID

///Relaxed EDC throttling
///Disabled - Part-specific EDC throttling protection enabled\nEnabled - Reduce the amount of time the processor will throttle\nAuto - AMD's recommendation (Disabled)\n
typedef enum {
  IDSOPT_CPU_RELAXED_EDC_THROTTLING_DISABLED = 0,///<Disabled
  IDSOPT_CPU_RELAXED_EDC_THROTTLING_ENABLED = 1,///<Enabled
  IDSOPT_CPU_RELAXED_EDC_THROTTLING_AUTO = 3,///<Auto
} IDSOPT_CPU_RELAXED_EDC_THROTTLING;

///Core/Thread Enablement Legal Disclaimer
///Legal Disclaimer
///Downcore control
///Sets the number of cores to be used. Once this option has been used to remove any cores, a POWER CYCLE is required in order for future selections to take effect.\nNOTE: Need to set "CBS -> FCH Common Options -> System Control -> Toggle All PwrGood On Cf9" as disabled.
typedef enum {
  IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_ONE = 1,///<ONE
  IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_TWO = 3,///<TWO
  IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_THREE = 4,///<THREE
  IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL_AUTO = 0,///<Auto
} IDSOPT_CMN_CPU_GEN_DOWNCORE_CTRL;

///SMTEN
///Can be used to disable symmetric multithreading. To re-enable SMT, a POWER CYCLE is needed after selecting the "Auto" option.\nWARNING - S3 is NOT SUPPORTED on systems where SMT is disabled.\nNOTE: Need to set "CBS -> FCH Common Options -> System Control -> Toggle All PwrGood On Cf9" as disabled.
typedef enum {
  IDSOPT_CMN_CPU_GEN_SMT_EN_DISABLE = 0,///<Disable
  IDSOPT_CMN_CPU_GEN_SMT_EN_AUTO = 0x1,///<Auto
} IDSOPT_CMN_CPU_GEN_SMT_EN;

///DRAM scrub time
///Provide a value that is the number of hours to scrub memory.
typedef enum {
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_1HOUR = 1,///<1 hour
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_4HOURS = 4,///<4 hours
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_8HOURS = 8,///<8 hours
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_16HOURS = 16,///<16 hours
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_24HOURS = 24,///<24 hours
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_48HOURS = 48,///<48 hours
  IDSOPT_DF_CMN_DRAM_SCRUB_TIME_AUTO = 0xFF,///<Auto
} IDSOPT_DF_CMN_DRAM_SCRUB_TIME;

///Redirect scrubber control
///Control DF::RedirScrubCtrl[EnRedirScrub]
typedef enum {
  IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_REDIR_SCRUB_CTRL;

///Disable DF sync flood propagation
///Control DF::PIEConfig[DisSyncFloodProp]
typedef enum {
  IDSOPT_DF_CMN_SYNC_FLOOD_PROP_SYNCFLOODDISABLED = 0,///<Sync flood disabled
  IDSOPT_DF_CMN_SYNC_FLOOD_PROP_SYNCFLOODENABLED = 1,///<Sync flood enabled
  IDSOPT_DF_CMN_SYNC_FLOOD_PROP_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_SYNC_FLOOD_PROP;

///GMI encryption control
///Control GMI link encryption
typedef enum {
  IDSOPT_DF_CMN_GMI_ENCRYPTION_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_GMI_ENCRYPTION_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_GMI_ENCRYPTION_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_GMI_ENCRYPTION;

///xGMI encryption control
///Control xGMI link encryption
typedef enum {
  IDSOPT_DF_CMN_X_GMI_ENCRYPTION_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_X_GMI_ENCRYPTION_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_X_GMI_ENCRYPTION_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_X_GMI_ENCRYPTION;

///CC6 memory region encryption
///Control whether or not the CC6 save/restore memory is encrypted
typedef enum {
  IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_CC6_MEM_ENCRYPTION;

///Location of private memory regions
///Controls whether or not the private memory regions (PSP, SMU and CC6) are at the top of DRAM or distributed. Note that distributed requires memory on all dies. Note that it will always be at the top of DRAM if some dies don't have memory regardless of this option's setting.
typedef enum {
  IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME_DISTRIBUTED = 0,///<Distributed
  IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME_CONSOLIDATED = 1,///<Consolidated
  IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_CC6_ALLOCATION_SCHEME;

///System probe filter
///Controls whether or not the probe filter is enabled. Has no effect on parts where the probe filter is fuse disabled.
typedef enum {
  IDSOPT_DF_CMN_SYS_PROBE_FILTER_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_SYS_PROBE_FILTER_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_SYS_PROBE_FILTER_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_SYS_PROBE_FILTER;

///Memory interleaving
///Controls fabric level memory interleaving (AUTO, none, channel, die, socket). Note that channel, die, and socket has requirements on memory populations and it will be ignored if the memory doesn't support the selected option.
typedef enum {
  IDSOPT_DF_CMN_MEM_INTLV_NONE = 0,///<None
  IDSOPT_DF_CMN_MEM_INTLV_CHANNEL = 1,///<Channel
  IDSOPT_DF_CMN_MEM_INTLV_DIE = 2,///<Die
  IDSOPT_DF_CMN_MEM_INTLV_SOCKET = 3,///<Socket
  IDSOPT_DF_CMN_MEM_INTLV_AUTO = 7,///<Auto
} IDSOPT_DF_CMN_MEM_INTLV;

///Memory interleaving size
///Controls the memory interleaving size. The valid values are AUTO, 256 bytes, 512 bytes, 1 Kbytes or 2Kbytes. This determines the starting address of the interleave (bit 8, 9, 10 or 11).
typedef enum {
  IDSOPT_DF_CMN_MEM_INTLV_SIZE_256BYTES = 0,///<256 Bytes
  IDSOPT_DF_CMN_MEM_INTLV_SIZE_512BYTES = 1,///<512 Bytes
  IDSOPT_DF_CMN_MEM_INTLV_SIZE_1KB = 2,///<1 KB
  IDSOPT_DF_CMN_MEM_INTLV_SIZE_2KB = 3,///<2 KB
  IDSOPT_DF_CMN_MEM_INTLV_SIZE_AUTO = 7,///<Auto
} IDSOPT_DF_CMN_MEM_INTLV_SIZE;

///Channel interleaving hash
///Controls whether or not the address bits are hashed during channel interleave mode. This field should not be used unless the interleaving is set to channel and the interleaving size is 256 or 512 bytes.
typedef enum {
  IDSOPT_DF_CMN_CHNL_INTLV_HASH_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_CHNL_INTLV_HASH_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_CHNL_INTLV_HASH_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_CHNL_INTLV_HASH;

///DF C-state control
///Enable / disable DF C-states (DF::CstateControl[DfCstateDisable])
typedef enum {
  IDSOPT_DF_CMN_CSTATE_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_CSTATE_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_CSTATE_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_CSTATE_CTRL;

///xGMI DLWM control
///Controls xGMI dynamic link width management feature.
typedef enum {
  IDSOPT_DF_CMNX_GMI_DLWM_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMNX_GMI_DLWM_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMNX_GMI_DLWM_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_CMNX_GMI_DLWM_CTRL;

///Freeze DF module queues on error
///Controls DF::DfGlobalCtrl[DisImmSyncFloodOnFatalError]\nDisabling this option sets DF:DfGlobalCtrl[DisImmSyncFloodOnFatalError]
typedef enum {
  IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_DISABLED = 0,///<Disabled
  IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_ENABLED = 1,///<Enabled
  IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_AUTO = 3,///<Auto
} IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR;

///DRAM Timing Configuration Legal Disclaimer
///DRAM Timing Configuration Legal Disclaimer 1
///Overclock
///Memory Overclock Settings
typedef enum {
  IDSOPT_CMN_MEM_OVERCLOCK_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_OVERCLOCK_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_CMN_MEM_OVERCLOCK_DDR4;

///Memory Clock Speed
///Set the memory clock frequency.
typedef enum {
  IDSOPT_CMN_MEM_SPEED_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_SPEED_DDR4_667MHZ = 0x14,///<667MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_800MHZ = 0x18,///<800MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_933MHZ = 0x1C,///<933MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1067MHZ = 0x20,///<1067MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1200MHZ = 0x24,///<1200MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1333MHZ = 0x28,///<1333MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1367MHZ = 0x29,///<1367MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1400MHZ = 0x2A,///<1400MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1433MHZ = 0x2B,///<1433MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1467MHZ = 0x2C,///<1467MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1500MHZ = 0x2D,///<1500MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1533MHZ = 0x2E,///<1533MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1567MHZ = 0x2F,///<1567MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1600MHZ = 0x30,///<1600MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1633MHZ = 0x31,///<1633MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1667MHZ = 0x32,///<1667MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1700MHZ = 0x33,///<1700MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1733MHZ = 0x34,///<1733MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1767MHZ = 0x35,///<1767MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1800MHZ = 0x36,///<1800MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1833MHZ = 0x37,///<1833MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1867MHZ = 0x38,///<1867MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1900MHZ = 0x39,///<1900MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1933MHZ = 0x3A,///<1933MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1967MHZ = 0x3B,///<1967MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_2000MHZ = 0x3C,///<2000MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_333MHZ = 4,///<333MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_400MHZ = 6,///<400MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_533MHZ = 0xA,///<533MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1050MHZ = 0x19,///<1050MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_1066MHZ = 0x1A,///<1066MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_2033MHZ = 0x3D,///<2033MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_2067MHZ = 0x3E,///<2067MHz
  IDSOPT_CMN_MEM_SPEED_DDR4_2100MHZ = 0x3F,///<2100MHz
} IDSOPT_CMN_MEM_SPEED_DDR4;

///Tcl
///Sets the tCL time.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1DHCLK = 0x1D,///<1Dh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1EHCLK = 0x1E,///<1Eh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_1FHCLK = 0x1F,///<1Fh Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_20HCLK = 0x20,///<20h Clk
  IDSOPT_CMN_MEM_TIMING_TCL_DDR4_21HCLK = 0x21,///<21h Clk
} IDSOPT_CMN_MEM_TIMING_TCL_DDR4;

///Trcdrd
///This sets the RAS# Active to CAS# read/write delay.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4_1BHCLK = 0x1B,///<1Bh Clk
} IDSOPT_CMN_MEM_TIMING_TRCDRD_DDR4;

///Trcdwr
///This sets the RAS# Active to CAS# read/write delay.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XACLK = 0xA,///<0xA Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XBCLK = 0xB,///<0xB Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XCCLK = 0xC,///<0xC Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XDCLK = 0xD,///<0xD Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XECLK = 0xE,///<0xE Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_0XFCLK = 0xF,///<0xF Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4_1BHCLK = 0x1B,///<1Bh Clk
} IDSOPT_CMN_MEM_TIMING_TRCDWR_DDR4;

///Trp
///Specify the row precharge time.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRP_DDR4_1BHCLK = 0x1B,///<1Bh Clk
} IDSOPT_CMN_MEM_TIMING_TRP_DDR4;

///Tras
///Specify the min RAS# active time.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1DHCLK = 0x1D,///<1Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1EHCLK = 0x1E,///<1Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_1FHCLK = 0x1F,///<1Fh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_20HCLK = 0x20,///<20h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_21HCLK = 0x21,///<21h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_22HCLK = 0x22,///<22h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_23HCLK = 0x23,///<23h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_24HCLK = 0x24,///<24h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_25HCLK = 0x25,///<25h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_26HCLK = 0x26,///<26h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_27HCLK = 0x27,///<27h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_28HCLK = 0x28,///<28h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_29HCLK = 0x29,///<29h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2AHCLK = 0x2A,///<2Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2BHCLK = 0x2B,///<2Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2CHCLK = 0x2C,///<2Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2DHCLK = 0x2D,///<2Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2EHCLK = 0x2E,///<2Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_2FHCLK = 0x2F,///<2Fh Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_30HCLK = 0x30,///<30h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_31HCLK = 0x31,///<31h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_32HCLK = 0x32,///<32h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_33HCLK = 0x33,///<33h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_34HCLK = 0x34,///<34h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_35HCLK = 0x35,///<35h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_36HCLK = 0x36,///<36h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_37HCLK = 0x37,///<37h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_38HCLK = 0x38,///<38h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_39HCLK = 0x39,///<39h Clk
  IDSOPT_CMN_MEM_TIMING_TRAS_DDR4_3AHCLK = 0x3A,///<3Ah Clk
} IDSOPT_CMN_MEM_TIMING_TRAS_DDR4;

///Trc Ctrl
///Specify Trc
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRC_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRC_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TRC_CTRL_DDR4;

///Trc
///Active to Active/Refresh Delay Time. Valid values 87h-1Dh.
#define IDSOPT_CMN_MEM_TIMING_TRC_DDR4_MIN 0x1d ///< Min of Trc
#define IDSOPT_CMN_MEM_TIMING_TRC_DDR4_MAX 0x87 ///< Max of Trc

///TrrdS
///Activate to Activate Delay Time, different bank group (tRRD_S)
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4_0CHCLK = 0xC,///<0Ch Clk
} IDSOPT_CMN_MEM_TIMING_TRRD_S_DDR4;

///TrrdL
///Activate to Activate Delay Time, same bank group (tRRD_L)
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4_0CHCLK = 0xC,///<0Ch Clk
} IDSOPT_CMN_MEM_TIMING_TRRD_L_DDR4;

///Tfaw Ctrl
///Specify Tfaw
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TFAW_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TFAW_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TFAW_CTRL_DDR4;

///Tfaw
///Four Activate Window Time. Valid values 36h-6h.
#define IDSOPT_CMN_MEM_TIMING_TFAW_DDR4_MIN 0x6 ///< Min of Tfaw
#define IDSOPT_CMN_MEM_TIMING_TFAW_DDR4_MAX 0x36 ///< Max of Tfaw

///TwtrS
///Minimum Write to Read Time, different bank group
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_CMN_MEM_TIMING_TWTR_S_DDR4;

///TwtrL
///Minimum Write to Read Time, same bank group
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_CMN_MEM_TIMING_TWTR_L_DDR4;

///Twr Ctrl
///Specify Twr
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWR_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWR_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TWR_CTRL_DDR4;

///Twr
///Minimum Write Recovery Time. Valid value 51h-Ah
#define IDSOPT_CMN_MEM_TIMING_TWR_DDR4_MIN 0xa ///< Min of Twr
#define IDSOPT_CMN_MEM_TIMING_TWR_DDR4_MAX 0x51 ///< Max of Twr

///Trcpage Ctrl
///Specify Trcpage
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TRCPAGE_CTRL_DDR4;

///Trcpage
///SDRAM Optional Features (tMAW, MAC). Valid value 3FFh - 0h
#define IDSOPT_CMN_MEM_TIMING_TRCPAGE_DDR4_MIN 0 ///< Min of Trcpage
#define IDSOPT_CMN_MEM_TIMING_TRCPAGE_DDR4_MAX 0x3ff ///< Max of Trcpage

///TrdrdScL Ctrl
///Specify TrdrdScL
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_CTRL_DDR4;

///TrdrdScL
///CAS to CAS Delay Time, same bank group. Valid values Fh-1h
#define IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_DDR4_MIN 0x1 ///< Min of TrdrdScL
#define IDSOPT_CMN_MEM_TIMING_TRDRD_SC_L_DDR4_MAX 0xf ///< Max of TrdrdScL

///TwrwrScL Ctrl
///Specify TwrwrScL
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_CTRL_DDR4;

///TwrwrScL
///CAS to CAS Delay Time, same bank group. Valid values 3Fh-1h
#define IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_DDR4_MIN 0x1 ///< Min of TwrwrScL
#define IDSOPT_CMN_MEM_TIMING_TWRWR_SC_L_DDR4_MAX 0x3f ///< Max of TwrwrScL

///Trfc Ctrl
///Specify Trfc
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRFC_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRFC_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TRFC_CTRL_DDR4;

///Trfc
///Refresh Recovery Delay Time (tRFC1). Valid values 3DEh-3Ch
#define IDSOPT_CMN_MEM_TIMING_TRFC_DDR4_MIN 0x3c ///< Min of Trfc
#define IDSOPT_CMN_MEM_TIMING_TRFC_DDR4_MAX 0x3de ///< Max of Trfc

///Trfc2 Ctrl
///Specify Trfc2
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRFC2_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRFC2_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TRFC2_CTRL_DDR4;

///Trfc2
///Refresh Recovery Delay Time (tRFC2).  Valid values 3DEh-3Ch
#define IDSOPT_CMN_MEM_TIMING_TRFC2_DDR4_MIN 0x3c ///< Min of Trfc2
#define IDSOPT_CMN_MEM_TIMING_TRFC2_DDR4_MAX 0x3de ///< Max of Trfc2

///Trfc4 Ctrl
///Specify Trfc4
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRFC4_CTRL_DDR4_AUTO = 0,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRFC4_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_TIMING_TRFC4_CTRL_DDR4;

///Trfc4
///Refresh Recovery Delay Time (tRFC4). Valid values 3DEh-3Ch
#define IDSOPT_CMN_MEM_TIMING_TRFC4_DDR4_MIN 0x3c ///< Min of Trfc4
#define IDSOPT_CMN_MEM_TIMING_TRFC4_DDR4_MAX 0x3de ///< Max of Trfc4

///Fail_CNT
///The number of training failure/retries required before boot from recovery mode
#define IDSOPT_CMN_MEM_OVERCLOCK_FAIL_CNT_MIN 0 ///< Min of Fail_CNT
#define IDSOPT_CMN_MEM_OVERCLOCK_FAIL_CNT_MAX 10 ///< Max of Fail_CNT

///ProcODT
///Specifies the Processor ODT
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_HIGHIMPEDANCE = 0,///<High Impedance
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_480OHM = 1,///<480 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_240OHM = 2,///<240 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_160OHM = 3,///<160 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_120OHM = 8,///<120 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_96OHM = 9,///<96 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_80OHM = 10,///<80 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_686OHM = 11,///<68.6 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_60OHM = 0x18,///<60 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_533OHM = 0x19,///<53.3 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_48OHM = 0x1A,///<48 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_436OHM = 0x1B,///<43.6 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_40OHM = 0x38,///<40 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_369OHM = 0x39,///<36.9 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_343OHM = 0x3A,///<34.3 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_32OHM = 0x3B,///<32 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_30OHM = 0x3E,///<30 ohm
  IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4_282OHM = 0x3F,///<28.2 ohm
} IDSOPT_CMN_MEM_CTRLLER_PROC_ODT_DDR4;

///Tcwl
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TCWL_DDR4_14HCLK = 0x14,///<14h Clk
} IDSOPT_CMN_MEM_TIMING_TCWL_DDR4;

///Trtp
///Specifies the read CAS# to precharge time.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_5CLK = 0x5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_6CLK = 0x6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_7CLK = 0x7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRTP_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_CMN_MEM_TIMING_TRTP_DDR4;

///Tcke
///Specifies the CKE minimum high and low pulse width in memory clock cycles.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1DHCLK = 0x1D,///<1Dh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1EHCLK = 0x1E,///<1Eh Clk
  IDSOPT_CMN_MEM_TIMING_TCKE_DDR4_1FHCLK = 0x1F,///<1Fh Clk
} IDSOPT_CMN_MEM_TIMING_TCKE_DDR4;

///TrdrdSc
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_TIMING_TRDRD_SC_DDR4;

///TrdrdSd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_CMN_MEM_TIMING_TRDRD_SD_DDR4;

///TrdrdDd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_CMN_MEM_TIMING_TRDRD_DD_DDR4;

///TwrwrSc
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_CMN_MEM_TIMING_TWRWR_SC_DDR4;

///TwrwrSd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_CMN_MEM_TIMING_TWRWR_SD_DDR4;

///TwrwrDd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_CMN_MEM_TIMING_TWRWR_DD_DDR4;

///Trdwr
///This sets the tWRTTO time.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1DHCLK = 0x1D,///<1Dh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1EHCLK = 0x1E,///<1Eh Clk
  IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4_1FHCLK = 0x1F,///<1Fh Clk
} IDSOPT_CMN_MEM_TIMING_TRDWR_DDR4;

///Twrrd
///Specify the write to read delay when accessing different DIMMs.
typedef enum {
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0CH = 0xC,///<0Ch
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0DH = 0xD,///<0Dh
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0EH = 0xE,///<0Eh
  IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4_0FH = 0xF,///<0Fh
} IDSOPT_CMN_MEM_TIMING_TWRRD_DDR4;

///Cmd2T
///Select between 1T and 2T mode on ADDR/CMD
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4_1T = 0,///<1T
  IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4_2T = 1,///<2T
  IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER2_T_MODE_DDR4;

///Gear Down Mode
typedef enum {
  IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_GEAR_DOWN_MODE_DDR4;

///Data Mask
typedef enum {
  IDSOPT_CMN_MEM_DATA_MASK_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_DATA_MASK_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_DATA_MASK_DDR4_DISABLED = 0,///<Disabled`
} IDSOPT_CMN_MEM_DATA_MASK_DDR4;

///Power Down Enable
///Enable or disable DDR power down mode
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_PWR_DN_EN_DDR4;

///CAD Bus Timing User Controls
///Setup time on CAD bus signals to Auto or Manual
typedef enum {
  IDSOPT_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_CAD_BUS_TIMING_CTL_DDR4;

///AddrCmdSetup
///Setup time on CAD bus signals. Valid values 3Fh-0h.
#define IDSOPT_CMN_MEM_ADDR_CMD_SETUP_DDR4_MIN 0 ///< Min of AddrCmdSetup
#define IDSOPT_CMN_MEM_ADDR_CMD_SETUP_DDR4_MAX 0x3f ///< Max of AddrCmdSetup

///CsOdtSetup
///Setup time on CAD bus signals. Valid values 3Fh-0h.
#define IDSOPT_CMN_MEM_CS_ODT_SETUP_DDR4_MIN 0 ///< Min of CsOdtSetup
#define IDSOPT_CMN_MEM_CS_ODT_SETUP_DDR4_MAX 0x3f ///< Max of CsOdtSetup

///CkeSetup
///Setup time on CAD bus signals. Valid values 3Fh-0h.
#define IDSOPT_CMN_MEM_CKE_SETUP_DDR4_MIN 0 ///< Min of CkeSetup
#define IDSOPT_CMN_MEM_CKE_SETUP_DDR4_MAX 0x3f ///< Max of CkeSetup

///CAD Bus Drive Strength User Controls
///Drive Strength on CAD bus signals to Auto or Manual
typedef enum {
  IDSOPT_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_CAD_BUS_DRV_STREN_CTL_DDR4;

///ClkDrvStren
typedef enum {
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_1200OHM = 0,///<120.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_600OHM = 1,///<60.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_400OHM = 3,///<40.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_300OHM = 7,///<30.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_240OHM = 15,///<24.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4_200OHM = 31,///<20.0 Ohm
} IDSOPT_CMN_MEM_CAD_BUS_CLK_DRV_STREN_DDR4;

///AddrCmdDrvStren
typedef enum {
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_1200OHM = 0,///<120.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_600OHM = 1,///<60.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_400OHM = 3,///<40.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_300OHM = 7,///<30.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_240OHM = 15,///<24.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4_200OHM = 31,///<20.0 Ohm
} IDSOPT_CMN_MEM_CAD_BUS_ADDR_CMD_DRV_STREN_DDR4;

///CsOdtDrvStren
typedef enum {
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_1200OHM = 0,///<120.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_600OHM = 1,///<60.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_400OHM = 3,///<40.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_300OHM = 7,///<30.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_240OHM = 15,///<24.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4_200OHM = 31,///<20.0 Ohm
} IDSOPT_CMN_MEM_CAD_BUS_CS_ODT_DRV_STREN_DDR4;

///CkeDrvStren
typedef enum {
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_1200OHM = 0,///<120.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_600OHM = 1,///<60.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_400OHM = 3,///<40.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_300OHM = 7,///<30.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_240OHM = 15,///<24.0 Ohm
  IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4_200OHM = 31,///<20.0 Ohm
} IDSOPT_CMN_MEM_CAD_BUS_CKE_DRV_STREN_DDR4;

///Data Bus Configuration User Controls
///Specify the mode for drive strength to Auto or Manual
typedef enum {
  IDSOPT_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_CMN_MEM_DATA_BUS_CONFIG_CTL_DDR4;

///RttNom
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RTT_NOMDISABLE = 0,///<Rtt_Nom Disable
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ4 = 1,///<RZQ/4
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ2 = 2,///<RZQ/2
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ6 = 3,///<RZQ/6
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ1 = 4,///<RZQ/1
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ5 = 5,///<RZQ/5
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ3 = 6,///<RZQ/3
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_RZQ7 = 7,///<RZQ/7
  IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_RTT_NOM_DDR4;

///RttWr
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_DYNAMICODTOFF = 0,///<Dynamic ODT Off
  IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_RZQ2 = 1,///<RZQ/2
  IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_RZQ1 = 2,///<RZQ/1
  IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_HIZ = 3,///<Hi-Z
  IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_RZQ3 = 4,///<RZQ/3
  IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_RTT_WR_DDR4;

///RttPark
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RTT_PARKDISABLE = 0,///<Rtt_PARK Disable
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ4 = 1,///<RZQ/4
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ2 = 2,///<RZQ/2
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ6 = 3,///<RZQ/6
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ1 = 4,///<RZQ/1
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ5 = 5,///<RZQ/5
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ3 = 6,///<RZQ/3
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_RZQ7 = 7,///<RZQ/7
  IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_RTT_PARK_DDR4;

///Data Poisoning
/// Enable/disable data poisoning: UMC_CH::EccCtrl[UcFatalEn] UMC_CH::EccCtrl[WrEccEn] Should be enabled/disabled together.
typedef enum {
  IDSOPT_CMN_MEM_DATA_POISONING_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_DATA_POISONING_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_DATA_POISONING_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_DATA_POISONING_DDR4;

///DRAM ECC Symbol Size
///DRAM ECC Symbol Size (x4/x8) - UMC_CH::EccCtrl[EccSymbolSize]
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4_X4 = 0,///<x4
  IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4_X8 = 1,///<x8
  IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_SYMBOL_SIZE_DDR4;

///DRAM ECC Enable
///Use this option to enable / disable DRAM ECC. Auto will set ECC to enable.
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_DRAM_ECC_EN_DDR4;

///TSME
///Transparent SME: AddrTweakEn = 1; ForceEncrEn =1; DataEncrEn = 0
typedef enum {
  IDSOPT_CMN_MEM_TSME_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_TSME_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_TSME_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_TSME_DDR4;

///Chipselect Interleaving
///Interleave memory blocks across the DRAM chip selects for node 0.
typedef enum {
  IDSOPT_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_MAPPING_BANK_INTERLEAVE_DDR4;

///BankGroupSwap
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_APU = 2,///<APU
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_CPU = 1,///<CPU
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_DDR4;

///BankGroupSwapAlt
typedef enum {
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_CTRLLER_BANK_GROUP_SWAP_ALT_DDR4;

///Address Hash Bank
///Enable or disable bank address hashing
typedef enum {
  IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_CMN_MEM_ADDRESS_HASH_BANK_DDR4;

///Address Hash CS
///Enable or disable CS address hashing
typedef enum {
  IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_CMN_MEM_ADDRESS_HASH_CS_DDR4;

///MBIST Enable
///Enable or disable Memory MBIST
typedef enum {
  IDSOPT_CMN_MEM_MBIST_EN_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_MBIST_EN_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_MBIST_EN_ENABLED = 1,///<Enabled
} IDSOPT_CMN_MEM_MBIST_EN;

///MBIST Test Mode
///Select MBIST Test Mode -Interface Mode (Tests Single and Multiple CS transactions and Basic Connectivity) or Data Eye Mode (Measures Voltage vs. Timing)
typedef enum {
  IDSOPT_CMN_MEM_MBIST_SUB_TEST_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_MBIST_SUB_TEST_INTERFACEMODE = 0,///<Interface Mode
  IDSOPT_CMN_MEM_MBIST_SUB_TEST_DATAEYEMODE = 1,///<Data Eye Mode
} IDSOPT_CMN_MEM_MBIST_SUB_TEST;

///MBIST Aggressors
///Enable or disable MBIST Aggressor test
typedef enum {
  IDSOPT_CMN_MEM_MBIST_AGGRESSORS_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_MBIST_AGGRESSORS_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_MBIST_AGGRESSORS_ENABLED = 1,///<Enabled
} IDSOPT_CMN_MEM_MBIST_AGGRESSORS;

///MBIST Per Bit Slave Die Reporting
///Reports 2D Data Eye Results in ABL Log for each DQ, Chipselect, and Channel
typedef enum {
  IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING_AUTO = 0xFF,///<Auto
  IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING_DISABLED = 0,///<Disabled
  IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING_ENABLED = 1,///<Enabled
} IDSOPT_CMN_MEM_MBIST_PER_BIT_SLAVE_DIE_REPORTING;

///System Configuration
///Warning: Select System Configuration may cause the system to hang, as some System Configuration may not be supported by your OPN.\n
typedef enum {
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_12WPORCONFIGURATION1COMMERCIALCONSUMER = 1,///<12W POR Configuration - 1 Commercial/Consumer
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_15WPORCONFIGURATION2COMMERCIALCONSUMER = 2,///<15W POR Configuration - 2 Commercial/Consumer
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_25WPORCONFIGURATION3COMMERCIALCONSUMER = 3,///<25W POR Configuration - 3 Commercial/Consumer
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_35WPORCONFIGURATION4CONSUMER = 4,///<35W POR Configuration - 4 Consumer
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_45WPORCONFIGURATION5CONSUMER = 5,///<45W POR Configuration - 5 Consumer
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_54WPORCONFIGURATION6CONSUMER = 6,///<54W POR Configuration - 6 Consumer
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_35WPORCONFIGURATION7EMBEDDED = 7,///<35W POR Configuration - 7 Embedded
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_45WPORCONFIGURATION8EMBEDDED = 8,///<45W POR Configuration - 8 Embedded
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_54WPORCONFIGURATION9EMBEDDED = 9,///<54W POR Configuration - 9 Embedded
  IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG_AUTO = 0xf,///<Auto
} IDSOPT_CMN_GNB_SMU_SYSTEM_CONFIG;

///Audio IOs
///Audio IOs control
typedef enum {
  IDSOPT_DBG_GNB_AUDIO_I_OS_AUTO = 0xF,///<Auto
  IDSOPT_DBG_GNB_AUDIO_I_OS_MAXHDAMINSOUNDWIRE = 0,///<MAX HDA / MIN SoundWire
  IDSOPT_DBG_GNB_AUDIO_I_OS_MAXMHDAMINSOUNDWIRE = 1,///<MAX mHDA / MIN SoundWire
  IDSOPT_DBG_GNB_AUDIO_I_OS_MAXSOUNDWIREMINHDA = 2,///<MAX SoundWire / MIN HDA
  IDSOPT_DBG_GNB_AUDIO_I_OS_MAXSOUNDWIREMINMHDA = 3,///<MAX SoundWire / MIN mHDA
  IDSOPT_DBG_GNB_AUDIO_I_OS_I2STDM = 0x4,///<I2S/TDM
  IDSOPT_DBG_GNB_AUDIO_I_OS_DISABLEAUDIOIOS = 7,///<DISABLE AUDIO IOs
  IDSOPT_DBG_GNB_AUDIO_I_OS_SOUNDWIRE = 0x8,///<Soundwire
} IDSOPT_DBG_GNB_AUDIO_I_OS;

///System Temperature Tracking
///System Temperature Tracking [0 = disabled; 1 = enabled]
typedef enum {
  IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_AUTO = 0xF,///<Auto
  IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_DISABLE = 0,///<Disable
  IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING_ENABLE = 1,///<Enable
} IDSOPT_CMN_SYSTEM_TEMPERATURE_TRACKING;

///Integrated Graphics Controller
///Enable Integrated Graphics controller
typedef enum {
  IDSOPT_CMN_GNB_GFXI_GPU_CONTROL_DISABLED = 0,///<Disabled
  IDSOPT_CMN_GNB_GFXI_GPU_CONTROL_FORCES = 2,///<Forces
  IDSOPT_CMN_GNB_GFXI_GPU_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_CMN_GNB_GFXI_GPU_CONTROL;

///UMA Mode
///UMA Mode
typedef enum {
  IDSOPT_CMN_GNB_GFX_UMA_MODE_AUTO = 0xf,///<Auto
  IDSOPT_CMN_GNB_GFX_UMA_MODE_UMA_SPECIFIED = 1,///<UMA_SPECIFIED
  IDSOPT_CMN_GNB_GFX_UMA_MODE_UMA_AUTO = 2,///<UMA_AUTO
} IDSOPT_CMN_GNB_GFX_UMA_MODE;

///UMA Version
///UMA Legacy Version\nUMA Non Legacy Version\nHybrid Secure
typedef enum {
  IDSOPT_CMN_GNB_GFX_UMA_VERSION_LEGACY = 0,///<Legacy
  IDSOPT_CMN_GNB_GFX_UMA_VERSION_NONLEGACY = 1,///<Non-Legacy
  IDSOPT_CMN_GNB_GFX_UMA_VERSION_HYBRIDSECURE = 2,///<Hybrid Secure
  IDSOPT_CMN_GNB_GFX_UMA_VERSION_AUTO = 0xf,///<Auto
} IDSOPT_CMN_GNB_GFX_UMA_VERSION;

///Display Resulotuon
///Display Resolution
typedef enum {
  IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_1920X1080ANDBELOW = 0,///<1920x1080 and below
  IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_2560X1600 = 1,///<2560x1600
  IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_3840X2160 = 2,///<3840x2160
  IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION_AUTO = 0xff,///<Auto
} IDSOPT_CMN_GNB_GFX_DISPLAY_RESOLUTION;

///UMA Frame buffer Size
///Set UMA FB size
typedef enum {
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_AUTO = 0xffffffff,///<Auto
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_64M = 64,///<64M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_128M = 128,///<128M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_256M = 256,///<256M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_384M = 384,///<384M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_512M = 512,///<512M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_80M = 80,///<80M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_96M = 96,///<96M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_768M = 768,///<768M
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_1G = 1024,///<1G
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_2G = 2048,///<2G
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_3G = 3072,///<3G
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_4G = 4096,///<4G
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_8G = 8192,///<8G
  IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE_16G = 16384,///<16G
} IDSOPT_CMN_GNB_GFX_UMA_FRAME_BUFFER_SIZE;

///NB Azalia
///Enable Integrate HD Audio controller
typedef enum {
  IDSOPT_CMN_GNB_GFX_NB_AZALIA_DISABLED = 0,///<Disabled
  IDSOPT_CMN_GNB_GFX_NB_AZALIA_ENABLED = 1,///<Enabled
  IDSOPT_CMN_GNB_GFX_NB_AZALIA_AUTO = 0xf,///<Auto
} IDSOPT_CMN_GNB_GFX_NB_AZALIA;

///IOMMU
///Enable/Disable IOMMU
typedef enum {
  IDSOPT_CMN_GNB_NB_IOMMU_DISABLED = 0,///<Disabled
  IDSOPT_CMN_GNB_NB_IOMMU_ENABLED = 1,///<Enabled
  IDSOPT_CMN_GNB_NB_IOMMU_AUTO = 0xf,///<Auto
} IDSOPT_CMN_GNB_NB_IOMMU;

///PSPP Policy
typedef enum {
  IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_DISABLED = 0,///<Disabled
  IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_PERFORMANCE = 1,///<Performance
  IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_BALANCED = 2,///<Balanced
  IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_POWERSAVING = 3,///<Power Saving
  IDSOPT_CMN_GNB_PCIE_PSPP_POLICY_AUTO = 0xf,///<Auto
} IDSOPT_CMN_GNB_PCIE_PSPP_POLICY;

///Fan Control
///Auto = Use the default fan controller settings\nManual = User can set customized fan controller settings
typedef enum {
  IDSOPT_DBG_FAN_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_FAN_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_FAN_CTL;

///Force PWM Control
///Unforce = Do not force the fan PWM\nForce = Force the fan PWM to the use specified value
typedef enum {
  IDSOPT_DBG_FORCE_PWM_CTL_FORCE = 1,///<Force
  IDSOPT_DBG_FORCE_PWM_CTL_UNFORCE = 0,///<Unforce
} IDSOPT_DBG_FORCE_PWM_CTL;

///Force PWM
///Specify the PWM to force the fan to [0-100]
#define IDSOPT_DBG_FORCE_PWM_MIN 0 ///< Min of Force PWM
#define IDSOPT_DBG_FORCE_PWM_MAX 100 ///< Max of Force PWM

///Fan Table Control
///Auto = Use the default fan table\nManual = User can set customized fan table
typedef enum {
  IDSOPT_DBG_FAN_TABLE_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_FAN_TABLE_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_FAN_TABLE_CTL;

///Low Temperature
///Low Temperature ['C]
#define IDSOPT_DBG_FAN_TABLE_TEMP_LOW_MIN 0 ///< Min of Low Temperature
#define IDSOPT_DBG_FAN_TABLE_TEMP_LOW_MAX 0xff ///< Max of Low Temperature

///Medium Temperature
///Medium Temperature ['C]
#define IDSOPT_DBG_FAN_TABLE_TEMP_MED_MIN 0 ///< Min of Medium Temperature
#define IDSOPT_DBG_FAN_TABLE_TEMP_MED_MAX 0xff ///< Max of Medium Temperature

///High Temperature
///High Temperature ['C]
#define IDSOPT_DBG_FAN_TABLE_TEMP_HIGH_MIN 0 ///< Min of High Temperature
#define IDSOPT_DBG_FAN_TABLE_TEMP_HIGH_MAX 0xff ///< Max of High Temperature

///Critical Temperature
///Critical Temperature ['C]
#define IDSOPT_DBG_FAN_TABLE_TEMP_CRITICAL_MIN 0 ///< Min of Critical Temperature
#define IDSOPT_DBG_FAN_TABLE_TEMP_CRITICAL_MAX 0xff ///< Max of Critical Temperature

///Low Pwm
///Low Pwm [0-100]
#define IDSOPT_DBG_FAN_TABLE_T_PWM_LOW_MIN 0 ///< Min of Low Pwm
#define IDSOPT_DBG_FAN_TABLE_T_PWM_LOW_MAX 100 ///< Max of Low Pwm

///Medium Pwm
///Medium Pwm [0-100]
#define IDSOPT_DBG_FAN_TABLE_PWM_MED_MIN 0 ///< Min of Medium Pwm
#define IDSOPT_DBG_FAN_TABLE_PWM_MED_MAX 100 ///< Max of Medium Pwm

///High Pwm
///High Pwm [0-100]
#define IDSOPT_DBG_FAN_TABLE_PWM_HIGH_MIN 0 ///< Min of High Pwm
#define IDSOPT_DBG_FAN_TABLE_PWM_HIGH_MAX 100 ///< Max of High Pwm

///Temperature Hysteresis
///Temperature Hysteresis ['C]
#define IDSOPT_DBG_FAN_TABLE_HYST_MIN 0 ///< Min of Temperature Hysteresis
#define IDSOPT_DBG_FAN_TABLE_HYST_MAX 0xff ///< Max of Temperature Hysteresis

///Pwm Frequency
///0 = 25kHz\n1 = 100Hz
typedef enum {
  IDSOPT_DBG_FAN_TABLE_PWM_FREQ_100HZ = 1,///<100Hz
  IDSOPT_DBG_FAN_TABLE_PWM_FREQ_25KHZ = 0,///<25kHz
} IDSOPT_DBG_FAN_TABLE_PWM_FREQ;

///Fan Polarity
///0 = negative\n1 = positive
typedef enum {
  IDSOPT_DBG_FAN_POLARITY_NEGATIVE = 0,///<Negative
  IDSOPT_DBG_FAN_POLARITY_POSITIVE = 1,///<Positive
} IDSOPT_DBG_FAN_POLARITY;

///SATA Controller
///Disable or enable OnChip SATA controller
typedef enum {
  IDSOPT_CMN_FCH_SATA_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_SATA_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_SATA_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_SATA_ENABLE;

///SATA Mode
///Select OnChip SATA Type. Don't select RAID for Raven FP5 platform. Raven FP5 doesn't support RAID.
typedef enum {
  IDSOPT_CMN_FCH_SATA_CLASS_AHCI = 2,///<AHCI
  IDSOPT_CMN_FCH_SATA_CLASS_AHCIASID0X7904 = 5,///<AHCI as ID 0x7904
  IDSOPT_CMN_FCH_SATA_CLASS_AUTO = 0xf,///<Auto
  IDSOPT_CMN_FCH_SATA_CLASS_RAID = 0x1,///<RAID
} IDSOPT_CMN_FCH_SATA_CLASS;

///Sata RAS Support
///Disable or enable Sata RAS Support
typedef enum {
  IDSOPT_CMN_FCH_SATA_RAS_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_SATA_RAS_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_SATA_RAS_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_SATA_RAS_SUPPORT;

///Sata Disabled AHCI Prefetch Function
///Disable or enable Sata Disabled AHCI Prefetch Function
typedef enum {
  IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_SATA_AHCI_DIS_PREFETCH_FUNCTION;

///Aggresive SATA Device Sleep Port 0
typedef enum {
  IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P0;

///Aggresive SATA Device Sleep Port 1
typedef enum {
  IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_FCH_SATA_AGGRESIVE_DEV_SLP_P1;

///XHCI0 controller enable
///Enable or disable USB3 controller.
typedef enum {
  IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_USB_XHC_I0_ENABLE;

///XHCI1 controller enable
///Enable or disable USB3 controller.
typedef enum {
  IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_USB_XHC_I1_ENABLE;

///Ac Loss Control
///Select Ac Loss Control Method
typedef enum {
  IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_ALWAYSOFF = 0,///<Always Off
  IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_ALWAYSON = 1,///<Always On
  IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_RESERVED = 2,///<Reserved
  IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW_PREVIOUS = 3,///<Previous
} IDSOPT_CMN_FCH_SYSTEM_PWR_FAIL_SHADOW;

///I2C 0 Enable
typedef enum {
  IDSOPT_CMN_FCH_I2_C0_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_I2_C0_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_I2_C0_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_I2_C0_CONFIG;

///I2C 1 Enable
typedef enum {
  IDSOPT_CMN_FCH_I2_C1_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_I2_C1_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_I2_C1_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_I2_C1_CONFIG;

///I2C 2 Enable
typedef enum {
  IDSOPT_CMN_FCH_I2_C2_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_I2_C2_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_I2_C2_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_I2_C2_CONFIG;

///I2C 3 Enable
typedef enum {
  IDSOPT_CMN_FCH_I2_C3_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_I2_C3_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_I2_C3_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_I2_C3_CONFIG;

///I2C 4 Enable
typedef enum {
  IDSOPT_CMN_FCH_I2_C4_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_I2_C4_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_I2_C4_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_I2_C4_CONFIG;

///I2C 5 Enable
typedef enum {
  IDSOPT_CMN_FCH_I2_C5_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_I2_C5_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_I2_C5_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_I2_C5_CONFIG;

///Uart 0 Enable
///Uart 0 has no HW FC if Uart 2 is enabled
typedef enum {
  IDSOPT_CMN_FCH_UART0_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART0_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_UART0_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART0_CONFIG;

///Uart 0 Legacy Options
typedef enum {
  IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X2E8 = 1,///<0x2E8
  IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X2F8 = 2,///<0x2F8
  IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X3E8 = 3,///<0x3E8
  IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_0X3F8 = 4,///<0x3F8
  IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART0_LEGACY_CONFIG;

///Uart 1 Enable
///Uart 1 has no HW FC if Uart 3 is enabled
typedef enum {
  IDSOPT_CMN_FCH_UART1_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART1_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_UART1_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART1_CONFIG;

///Uart 1 Legacy Options
typedef enum {
  IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X2E8 = 1,///<0x2E8
  IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X2F8 = 2,///<0x2F8
  IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X3E8 = 3,///<0x3E8
  IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_0X3F8 = 4,///<0x3F8
  IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART1_LEGACY_CONFIG;

///Uart 2 Enable (no HW FC)
typedef enum {
  IDSOPT_CMN_FCH_UART2_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART2_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_UART2_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART2_CONFIG;

///Uart 2 Legacy Options
typedef enum {
  IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X2E8 = 1,///<0x2E8
  IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X2F8 = 2,///<0x2F8
  IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X3E8 = 3,///<0x3E8
  IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_0X3F8 = 4,///<0x3F8
  IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART2_LEGACY_CONFIG;

///Uart 3 Enable (no HW FC)
typedef enum {
  IDSOPT_CMN_FCH_UART3_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART3_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_UART3_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART3_CONFIG;

///Uart 3 Legacy Options
typedef enum {
  IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X2E8 = 1,///<0x2E8
  IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X2F8 = 2,///<0x2F8
  IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X3E8 = 3,///<0x3E8
  IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_0X3F8 = 4,///<0x3F8
  IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_UART3_LEGACY_CONFIG;

///ESPI Enable
typedef enum {
  IDSOPT_CMN_FCH_ESPI_CONFIG_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_ESPI_CONFIG_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_ESPI_CONFIG_AUTO = 0xf,///<AUTO
} IDSOPT_CMN_FCH_ESPI_CONFIG;

///XGBE0 enable
///Enable or disable Ethernet controller.
typedef enum {
  IDSOPT_CMN_FCH_XGBE0_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_XGBE0_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_XGBE0_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_XGBE0_ENABLE;

///XGBE1 enable
///Enable or disable Ethernet controller.
typedef enum {
  IDSOPT_CMN_FCH_XGBE1_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_XGBE1_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_XGBE1_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_XGBE1_ENABLE;

///eMMC/SD Configure
typedef enum {
  IDSOPT_DBG_FCH_EMMC_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_ENABLE_SDNORMALSPEED = 1,///<SD Normal Speed
  IDSOPT_DBG_FCH_EMMC_ENABLE_SDHIGHSPEED = 2,///<SD High Speed
  IDSOPT_DBG_FCH_EMMC_ENABLE_SDUHSISDR50 = 3,///<SD UHSI-SDR50
  IDSOPT_DBG_FCH_EMMC_ENABLE_SDUHSIDDR50 = 4,///<SD UHSI-DDR50
  IDSOPT_DBG_FCH_EMMC_ENABLE_SDUHSISDR104 = 5,///<SD UHSI-SDR104
  IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCEMMCBACKWARDCOMPATIBILITY = 6,///<eMMC Emmc Backward Compatibility
  IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHIGHSPEEDSDR = 7,///<eMMC High Speed SDR
  IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHIGHSPEEDDDR = 8,///<eMMC High Speed DDR
  IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHS200 = 9,///<eMMC HS200
  IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHS400 = 10,///<eMMC HS400
  IDSOPT_DBG_FCH_EMMC_ENABLE_EMMCHS300 = 11,///<eMMC HS300
  IDSOPT_DBG_FCH_EMMC_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_ENABLE;

///Driver Type
///Bios will select MS driver for SD selections.
typedef enum {
  IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_AMDEMMCDRIVER = 0,///<AMD eMMC Driver
  IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_MSDRIVER = 1,///<MS Driver
  IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_MSEMMCDRIVER = 2,///<MS eMMC Driver
  IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_DRIVER_TYPE;

///D3 Cold Support
typedef enum {
  IDSOPT_DBG_FCH_EMMC_D3_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_D3_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_EMMC_D3_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_D3_SUPPORT;

///eMMC Boot
typedef enum {
  IDSOPT_DBG_FCH_EMMC_BOOT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_BOOT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_EMMC_BOOT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_BOOT;

///LPC Clock Run control
typedef enum {
  IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN_DISABLED = 0,///<Disabled
  IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN_ENABLED = 1,///<Enabled
  IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN_AUTO = 0xf,///<Auto
} IDSOPT_CMN_FCH_LPC_CLOCK_RUN_EN;

///Toggle All PwrGood On Cf9
typedef enum {
  IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9_DISABLED = 0,///<Disabled
  IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9_ENABLED = 1,///<Enabled
  IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9_AUTO = 2,///<Auto
} IDSOPT_CMN_TOGGLE_ALL_PWR_GOOD_ON_CF9;

///PT SATA Mode
///Select Promontory SATA Type
typedef enum {
  IDSOPT_CMN_PT_SATA_CLASS_AHCI = 0,///<AHCI
  IDSOPT_CMN_PT_SATA_CLASS_RAID = 1,///<RAID
  IDSOPT_CMN_PT_SATA_CLASS_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_CLASS;

///PT Aggresive SATA Device Sleep Port 0
typedef enum {
  IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P0;

///PT Aggresive SATA Device Sleep Port 1
typedef enum {
  IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_SATA_AGGRESIVE_DEV_SLP_P1;

///PT SATA Port 0 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT0_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT0_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT0_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT0_ENABLE;

///PT SATA Port 1 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT1_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT1_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT1_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT1_ENABLE;

///PT SATA Port 2 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT2_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT2_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT2_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT2_ENABLE;

///PT SATA Port 3 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT3_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT3_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT3_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT3_ENABLE;

///PT SATA Port 4 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT4_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT4_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT4_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT4_ENABLE;

///PT SATA Port 5 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT5_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT5_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT5_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT5_ENABLE;

///PT SATA Port 6 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT6_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT6_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT6_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT6_ENABLE;

///PT SATA Port 7 Enable
typedef enum {
  IDSOPT_CMN_PT_SATA_PORT7_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_SATA_PORT7_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_SATA_PORT7_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_SATA_PORT7_ENABLE;

///PT XHCI GEN1
typedef enum {
  IDSOPT_DBG_PT_XHCI_GEN1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_XHCI_GEN1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_XHCI_GEN1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_XHCI_GEN1;

///PT XHCI GEN2
typedef enum {
  IDSOPT_DBG_PT_XHCI_GEN2_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_XHCI_GEN2_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_XHCI_GEN2_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_XHCI_GEN2;

///PT USB Equalization4
typedef enum {
  IDSOPT_DBG_PT_USB_EQUALIZATION4_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB_EQUALIZATION4_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB_EQUALIZATION4_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB_EQUALIZATION4;

///PT USB Redriver
typedef enum {
  IDSOPT_DBG_PT_USB_REDRIVER_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB_REDRIVER_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB_REDRIVER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB_REDRIVER;

///PT USB31 PORT0
typedef enum {
  IDSOPT_DBG_PT_USB31_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB31_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB31_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB31_P0;

///PT USB31 PORT1
typedef enum {
  IDSOPT_DBG_PT_USB31_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB31_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB31_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB31_P1;

///PT USB30 PORT0
typedef enum {
  IDSOPT_DBG_PT_USB30_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB30_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB30_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB30_P0;

///PT USB30 PORT1
typedef enum {
  IDSOPT_DBG_PT_USB30_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB30_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB30_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB30_P1;

///PT USB30 PORT2
typedef enum {
  IDSOPT_DBG_PT_USB30_P2_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB30_P2_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB30_P2_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB30_P2;

///PT USB30 PORT3
typedef enum {
  IDSOPT_DBG_PT_USB30_P3_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB30_P3_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB30_P3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB30_P3;

///PT USB30 PORT4
typedef enum {
  IDSOPT_DBG_PT_USB30_P4_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB30_P4_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB30_P4_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB30_P4;

///PT USB30 PORT5
typedef enum {
  IDSOPT_DBG_PT_USB30_P5_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB30_P5_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB30_P5_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB30_P5;

///PT USB20 PORT0
typedef enum {
  IDSOPT_DBG_PT_USB20_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB20_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB20_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB20_P0;

///PT USB20 PORT1
typedef enum {
  IDSOPT_DBG_PT_USB20_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB20_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB20_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB20_P1;

///PT USB20 PORT2
typedef enum {
  IDSOPT_DBG_PT_USB20_P2_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB20_P2_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB20_P2_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB20_P2;

///PT USB20 PORT3
typedef enum {
  IDSOPT_DBG_PT_USB20_P3_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB20_P3_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB20_P3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB20_P3;

///PT USB20 PORT4
typedef enum {
  IDSOPT_DBG_PT_USB20_P4_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB20_P4_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB20_P4_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB20_P4;

///PT USB20 PORT5
typedef enum {
  IDSOPT_DBG_PT_USB20_P5_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_USB20_P5_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_USB20_P5_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_USB20_P5;

///PT USB31 PORT0
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB31_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB31_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB31_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB31_P0;

///PT USB31 PORT1
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB31_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB31_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB31_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB31_P1;

///PT USB30 PORT0
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB30_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB30_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB30_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB30_P0;

///PT USB30 PORT1
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB30_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB30_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB30_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB30_P1;

///PT USB20 PORT0
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB20_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB20_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB20_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB20_P0;

///PT USB20 PORT1
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB20_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB20_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB20_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB20_P1;

///PT USB20 PORT2
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB20_P2_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB20_P2_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB20_P2_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB20_P2;

///PT USB20 PORT3
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB20_P3_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB20_P3_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB20_P3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB20_P3;

///PT USB20 PORT4
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB20_P4_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB20_P4_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB20_P4_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB20_P4;

///PT USB20 PORT5
typedef enum {
  IDSOPT_DBG_PT_PROM2_USB20_P5_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM2_USB20_P5_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM2_USB20_P5_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM2_USB20_P5;

///PT USB31 PORT0
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB31_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB31_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB31_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB31_P0;

///PT USB31 PORT1
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB31_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB31_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB31_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB31_P1;

///PT USB30 PORT0
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB30_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB30_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB30_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB30_P0;

///PT USB20 PORT0
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB20_P0_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB20_P0_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB20_P0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB20_P0;

///PT USB20 PORT1
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB20_P1_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB20_P1_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB20_P1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB20_P1;

///PT USB20 PORT2
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB20_P2_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB20_P2_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB20_P2_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB20_P2;

///PT USB20 PORT3
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB20_P3_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB20_P3_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB20_P3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB20_P3;

///PT USB20 PORT4
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB20_P4_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB20_P4_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB20_P4_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB20_P4;

///PT USB20 PORT5
typedef enum {
  IDSOPT_DBG_PT_PROM1_USB20_P5_DISABLE = 0,///<Disable
  IDSOPT_DBG_PT_PROM1_USB20_P5_ENABLE = 1,///<Enable
  IDSOPT_DBG_PT_PROM1_USB20_P5_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_PROM1_USB20_P5;

///PT PCIE Port 0 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT0_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT0_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT0_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT0_ENABLE;

///PT PCIE Port 1 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT1_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT1_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT1_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT1_ENABLE;

///PT PCIE Port 2 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT2_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT2_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT2_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT2_ENABLE;

///PT PCIE Port 3 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT3_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT3_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT3_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT3_ENABLE;

///PT PCIE Port 4 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT4_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT4_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT4_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT4_ENABLE;

///PT PCIE Port 5 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT5_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT5_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT5_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT5_ENABLE;

///PT PCIE Port 6 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT6_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT6_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT6_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT6_ENABLE;

///PT PCIE Port 7 Enable
typedef enum {
  IDSOPT_CMN_PT_PCIE_PORT7_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_CMN_PT_PCIE_PORT7_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_CMN_PT_PCIE_PORT7_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_CMN_PT_PCIE_PORT7_ENABLE;


#endif //_IDS_NV_DEF_RV_H_

