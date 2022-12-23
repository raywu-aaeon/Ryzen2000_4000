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

#ifndef _IDS_NV_INT_DEF_ZP_H_
#define _IDS_NV_INT_DEF_ZP_H_

///MCA0_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 0.
typedef enum {
  IDSOPT_DBG_CPU_MCA0_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA0_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA0_CTL_MASK_CTRL;

///MCA0_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_LOW_MIN 0 ///< Min of MCA0_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA0_CTL_MASK_LOW

///MCA0_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_HIGH_MIN 0 ///< Min of MCA0_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA0_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA0_CTL_MASK_HIGH

///MCA1_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 1.
typedef enum {
  IDSOPT_DBG_CPU_MCA1_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA1_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA1_CTL_MASK_CTRL;

///MCA1_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_LOW_MIN 0 ///< Min of MCA1_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA1_CTL_MASK_LOW

///MCA1_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_HIGH_MIN 0 ///< Min of MCA1_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA1_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA1_CTL_MASK_HIGH

///MCA2_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 2.
typedef enum {
  IDSOPT_DBG_CPU_MCA2_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA2_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA2_CTL_MASK_CTRL;

///MCA2_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_LOW_MIN 0 ///< Min of MCA2_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA2_CTL_MASK_LOW

///MCA2_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_HIGH_MIN 0 ///< Min of MCA2_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA2_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA2_CTL_MASK_HIGH

///MCA3_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 3.
typedef enum {
  IDSOPT_DBG_CPU_MCA3_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA3_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA3_CTL_MASK_CTRL;

///MCA3_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_LOW_MIN 0 ///< Min of MCA3_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA3_CTL_MASK_LOW

///MCA3_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_HIGH_MIN 0 ///< Min of MCA3_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA3_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA3_CTL_MASK_HIGH

///MCA4_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 4.
typedef enum {
  IDSOPT_DBG_CPU_MCA4_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA4_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA4_CTL_MASK_CTRL;

///MCA4_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_LOW_MIN 0 ///< Min of MCA4_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA4_CTL_MASK_LOW

///MCA4_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_HIGH_MIN 0 ///< Min of MCA4_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA4_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA4_CTL_MASK_HIGH

///MCA5_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 5.
typedef enum {
  IDSOPT_DBG_CPU_MCA5_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA5_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA5_CTL_MASK_CTRL;

///MCA5_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_LOW_MIN 0 ///< Min of MCA5_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA5_CTL_MASK_LOW

///MCA5_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_HIGH_MIN 0 ///< Min of MCA5_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA5_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA5_CTL_MASK_HIGH

///MCA6_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 6.
typedef enum {
  IDSOPT_DBG_CPU_MCA6_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA6_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA6_CTL_MASK_CTRL;

///MCA6_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_LOW_MIN 0 ///< Min of MCA6_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA6_CTL_MASK_LOW

///MCA6_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_HIGH_MIN 0 ///< Min of MCA6_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA6_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA6_CTL_MASK_HIGH

///MCA7_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 7.
typedef enum {
  IDSOPT_DBG_CPU_MCA7_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA7_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA7_CTL_MASK_CTRL;

///MCA7_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_LOW_MIN 0 ///< Min of MCA7_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA7_CTL_MASK_LOW

///MCA7_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_HIGH_MIN 0 ///< Min of MCA7_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA7_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA7_CTL_MASK_HIGH

///MCA8_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 8.
typedef enum {
  IDSOPT_DBG_CPU_MCA8_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA8_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA8_CTL_MASK_CTRL;

///MCA8_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_LOW_MIN 0 ///< Min of MCA8_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA8_CTL_MASK_LOW

///MCA8_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_HIGH_MIN 0 ///< Min of MCA8_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA8_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA8_CTL_MASK_HIGH

///MCA9_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 9.
typedef enum {
  IDSOPT_DBG_CPU_MCA9_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA9_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA9_CTL_MASK_CTRL;

///MCA9_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_LOW_MIN 0 ///< Min of MCA9_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA9_CTL_MASK_LOW

///MCA9_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_HIGH_MIN 0 ///< Min of MCA9_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA9_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA9_CTL_MASK_HIGH

///MCA10_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 10.
typedef enum {
  IDSOPT_DBG_CPU_MCA10_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA10_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA10_CTL_MASK_CTRL;

///MCA10_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_LOW_MIN 0 ///< Min of MCA10_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA10_CTL_MASK_LOW

///MCA10_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_HIGH_MIN 0 ///< Min of MCA10_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA10_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA10_CTL_MASK_HIGH

///MCA11_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 11.
typedef enum {
  IDSOPT_DBG_CPU_MCA11_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA11_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA11_CTL_MASK_CTRL;

///MCA11_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_LOW_MIN 0 ///< Min of MCA11_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA11_CTL_MASK_LOW

///MCA11_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_HIGH_MIN 0 ///< Min of MCA11_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA11_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA11_CTL_MASK_HIGH

///MCA12_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 12.
typedef enum {
  IDSOPT_DBG_CPU_MCA12_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA12_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA12_CTL_MASK_CTRL;

///MCA12_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_LOW_MIN 0 ///< Min of MCA12_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA12_CTL_MASK_LOW

///MCA12_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_HIGH_MIN 0 ///< Min of MCA12_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA12_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA12_CTL_MASK_HIGH

///MCA13_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 13.
typedef enum {
  IDSOPT_DBG_CPU_MCA13_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA13_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA13_CTL_MASK_CTRL;

///MCA13_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_LOW_MIN 0 ///< Min of MCA13_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA13_CTL_MASK_LOW

///MCA13_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_HIGH_MIN 0 ///< Min of MCA13_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA13_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA13_CTL_MASK_HIGH

///MCA14_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 14.
typedef enum {
  IDSOPT_DBG_CPU_MCA14_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA14_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA14_CTL_MASK_CTRL;

///MCA14_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_LOW_MIN 0 ///< Min of MCA14_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA14_CTL_MASK_LOW

///MCA14_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_HIGH_MIN 0 ///< Min of MCA14_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA14_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA14_CTL_MASK_HIGH

///MCA15_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 15.
typedef enum {
  IDSOPT_DBG_CPU_MCA15_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA15_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA15_CTL_MASK_CTRL;

///MCA15_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_LOW_MIN 0 ///< Min of MCA15_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA15_CTL_MASK_LOW

///MCA15_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_HIGH_MIN 0 ///< Min of MCA15_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA15_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA15_CTL_MASK_HIGH

///MCA16_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 16.
typedef enum {
  IDSOPT_DBG_CPU_MCA16_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA16_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA16_CTL_MASK_CTRL;

///MCA16_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_LOW_MIN 0 ///< Min of MCA16_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA16_CTL_MASK_LOW

///MCA16_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_HIGH_MIN 0 ///< Min of MCA16_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA16_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA16_CTL_MASK_HIGH

///MCA17_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 17.
typedef enum {
  IDSOPT_DBG_CPU_MCA17_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA17_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA17_CTL_MASK_CTRL;

///MCA17_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_LOW_MIN 0 ///< Min of MCA17_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA17_CTL_MASK_LOW

///MCA17_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_HIGH_MIN 0 ///< Min of MCA17_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA17_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA17_CTL_MASK_HIGH

///MCA18_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 18.
typedef enum {
  IDSOPT_DBG_CPU_MCA18_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA18_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA18_CTL_MASK_CTRL;

///MCA18_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_LOW_MIN 0 ///< Min of MCA18_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA18_CTL_MASK_LOW

///MCA18_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_HIGH_MIN 0 ///< Min of MCA18_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA18_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA18_CTL_MASK_HIGH

///MCA19_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 19.
typedef enum {
  IDSOPT_DBG_CPU_MCA19_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA19_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA19_CTL_MASK_CTRL;

///MCA19_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_LOW_MIN 0 ///< Min of MCA19_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA19_CTL_MASK_LOW

///MCA19_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_HIGH_MIN 0 ///< Min of MCA19_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA19_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA19_CTL_MASK_HIGH

///MCA20_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 20.
typedef enum {
  IDSOPT_DBG_CPU_MCA20_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA20_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA20_CTL_MASK_CTRL;

///MCA20_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_LOW_MIN 0 ///< Min of MCA20_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA20_CTL_MASK_LOW

///MCA20_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_HIGH_MIN 0 ///< Min of MCA20_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA20_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA20_CTL_MASK_HIGH

///MCA21_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 21.
typedef enum {
  IDSOPT_DBG_CPU_MCA21_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA21_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA21_CTL_MASK_CTRL;

///MCA21_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_LOW_MIN 0 ///< Min of MCA21_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA21_CTL_MASK_LOW

///MCA21_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_HIGH_MIN 0 ///< Min of MCA21_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA21_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA21_CTL_MASK_HIGH

///MCA22_CTL_MASK Control
///Manual allows for overriding MCA_CTL_MASK for bank 22.
typedef enum {
  IDSOPT_DBG_CPU_MCA22_CTL_MASK_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA22_CTL_MASK_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA22_CTL_MASK_CTRL;

///MCA22_CTL_MASK_LOW
///Value to program the lower 32 bits of the MCA_CTL_MASK for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_LOW_MIN 0 ///< Min of MCA22_CTL_MASK_LOW
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_LOW_MAX 0xffffffff ///< Max of MCA22_CTL_MASK_LOW

///MCA22_CTL_MASK_HIGH
///Value to program the upper 32 bits of the MCA_CTL_MASK for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_HIGH_MIN 0 ///< Min of MCA22_CTL_MASK_HIGH
#define IDSOPT_DBG_CPU_MCA22_CTL_MASK_HIGH_MAX 0xffffffff ///< Max of MCA22_CTL_MASK_HIGH

///MCG_CTL Control
///Manual allows for overriding MCG_CTL for bank 22.
typedef enum {
  IDSOPT_DBG_CPU_MCG_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCG_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCG_CTL_CTRL;

///MCG_CTL Value
///Value to program the lower 32 bits of the MCG_CTL MSR.
#define IDSOPT_DBG_CPU_MCG_CTL_VALUE_MIN 0 ///< Min of MCG_CTL Value
#define IDSOPT_DBG_CPU_MCG_CTL_VALUE_MAX 0x7fffff ///< Max of MCG_CTL Value

///MCA0_CTL Control
///Manual allows for overriding MCA_CTL for bank 0.
typedef enum {
  IDSOPT_DBG_CPU_MCA0_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA0_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA0_CTL_CTRL;

///MCA0_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_LOW_MIN 0 ///< Min of MCA0_CTL_LOW
#define IDSOPT_DBG_CPU_MCA0_CTL_LOW_MAX 0xffffffff ///< Max of MCA0_CTL_LOW

///MCA0_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 0.
#define IDSOPT_DBG_CPU_MCA0_CTL_HIGH_MIN 0 ///< Min of MCA0_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA0_CTL_HIGH_MAX 0xffffffff ///< Max of MCA0_CTL_HIGH

///MCA1_CTL Control
///Manual allows for overriding MCA_CTL for bank 1.
typedef enum {
  IDSOPT_DBG_CPU_MCA1_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA1_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA1_CTL_CTRL;

///MCA1_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_LOW_MIN 0 ///< Min of MCA1_CTL_LOW
#define IDSOPT_DBG_CPU_MCA1_CTL_LOW_MAX 0xffffffff ///< Max of MCA1_CTL_LOW

///MCA1_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 1.
#define IDSOPT_DBG_CPU_MCA1_CTL_HIGH_MIN 0 ///< Min of MCA1_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA1_CTL_HIGH_MAX 0xffffffff ///< Max of MCA1_CTL_HIGH

///MCA2_CTL Control
///Manual allows for overriding MCA_CTL for bank 2.
typedef enum {
  IDSOPT_DBG_CPU_MCA2_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA2_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA2_CTL_CTRL;

///MCA2_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_LOW_MIN 0 ///< Min of MCA2_CTL_LOW
#define IDSOPT_DBG_CPU_MCA2_CTL_LOW_MAX 0xffffffff ///< Max of MCA2_CTL_LOW

///MCA2_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 2.
#define IDSOPT_DBG_CPU_MCA2_CTL_HIGH_MIN 0 ///< Min of MCA2_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA2_CTL_HIGH_MAX 0xffffffff ///< Max of MCA2_CTL_HIGH

///MCA3_CTL Control
///Manual allows for overriding MCA_CTL for bank 3.
typedef enum {
  IDSOPT_DBG_CPU_MCA3_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA3_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA3_CTL_CTRL;

///MCA3_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_LOW_MIN 0 ///< Min of MCA3_CTL_LOW
#define IDSOPT_DBG_CPU_MCA3_CTL_LOW_MAX 0xffffffff ///< Max of MCA3_CTL_LOW

///MCA3_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 3.
#define IDSOPT_DBG_CPU_MCA3_CTL_HIGH_MIN 0 ///< Min of MCA3_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA3_CTL_HIGH_MAX 0xffffffff ///< Max of MCA3_CTL_HIGH

///MCA4_CTL Control
///Manual allows for overriding MCA_CTL for bank 4.
typedef enum {
  IDSOPT_DBG_CPU_MCA4_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA4_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA4_CTL_CTRL;

///MCA4_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_LOW_MIN 0 ///< Min of MCA4_CTL_LOW
#define IDSOPT_DBG_CPU_MCA4_CTL_LOW_MAX 0xffffffff ///< Max of MCA4_CTL_LOW

///MCA4_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 4.
#define IDSOPT_DBG_CPU_MCA4_CTL_HIGH_MIN 0 ///< Min of MCA4_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA4_CTL_HIGH_MAX 0xffffffff ///< Max of MCA4_CTL_HIGH

///MCA5_CTL Control
///Manual allows for overriding MCA_CTL for bank 5.
typedef enum {
  IDSOPT_DBG_CPU_MCA5_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA5_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA5_CTL_CTRL;

///MCA5_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_LOW_MIN 0 ///< Min of MCA5_CTL_LOW
#define IDSOPT_DBG_CPU_MCA5_CTL_LOW_MAX 0xffffffff ///< Max of MCA5_CTL_LOW

///MCA5_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 5.
#define IDSOPT_DBG_CPU_MCA5_CTL_HIGH_MIN 0 ///< Min of MCA5_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA5_CTL_HIGH_MAX 0xffffffff ///< Max of MCA5_CTL_HIGH

///MCA6_CTL Control
///Manual allows for overriding MCA_CTL for bank 6.
typedef enum {
  IDSOPT_DBG_CPU_MCA6_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA6_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA6_CTL_CTRL;

///MCA6_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_LOW_MIN 0 ///< Min of MCA6_CTL_LOW
#define IDSOPT_DBG_CPU_MCA6_CTL_LOW_MAX 0xffffffff ///< Max of MCA6_CTL_LOW

///MCA6_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 6.
#define IDSOPT_DBG_CPU_MCA6_CTL_HIGH_MIN 0 ///< Min of MCA6_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA6_CTL_HIGH_MAX 0xffffffff ///< Max of MCA6_CTL_HIGH

///MCA7_CTL Control
///Manual allows for overriding MCA_CTL for bank 7.
typedef enum {
  IDSOPT_DBG_CPU_MCA7_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA7_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA7_CTL_CTRL;

///MCA7_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_LOW_MIN 0 ///< Min of MCA7_CTL_LOW
#define IDSOPT_DBG_CPU_MCA7_CTL_LOW_MAX 0xffffffff ///< Max of MCA7_CTL_LOW

///MCA7_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 7.
#define IDSOPT_DBG_CPU_MCA7_CTL_HIGH_MIN 0 ///< Min of MCA7_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA7_CTL_HIGH_MAX 0xffffffff ///< Max of MCA7_CTL_HIGH

///MCA8_CTL Control
///Manual allows for overriding MCA_CTL for bank 8.
typedef enum {
  IDSOPT_DBG_CPU_MCA8_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA8_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA8_CTL_CTRL;

///MCA8_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_LOW_MIN 0 ///< Min of MCA8_CTL_LOW
#define IDSOPT_DBG_CPU_MCA8_CTL_LOW_MAX 0xffffffff ///< Max of MCA8_CTL_LOW

///MCA8_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 8.
#define IDSOPT_DBG_CPU_MCA8_CTL_HIGH_MIN 0 ///< Min of MCA8_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA8_CTL_HIGH_MAX 0xffffffff ///< Max of MCA8_CTL_HIGH

///MCA9_CTL Control
///Manual allows for overriding MCA_CTL for bank 9.
typedef enum {
  IDSOPT_DBG_CPU_MCA9_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA9_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA9_CTL_CTRL;

///MCA9_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_LOW_MIN 0 ///< Min of MCA9_CTL_LOW
#define IDSOPT_DBG_CPU_MCA9_CTL_LOW_MAX 0xffffffff ///< Max of MCA9_CTL_LOW

///MCA9_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 9.
#define IDSOPT_DBG_CPU_MCA9_CTL_HIGH_MIN 0 ///< Min of MCA9_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA9_CTL_HIGH_MAX 0xffffffff ///< Max of MCA9_CTL_HIGH

///MCA10_CTL Control
///Manual allows for overriding MCA_CTL for bank 10.
typedef enum {
  IDSOPT_DBG_CPU_MCA10_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA10_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA10_CTL_CTRL;

///MCA10_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_LOW_MIN 0 ///< Min of MCA10_CTL_LOW
#define IDSOPT_DBG_CPU_MCA10_CTL_LOW_MAX 0xffffffff ///< Max of MCA10_CTL_LOW

///MCA10_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 10.
#define IDSOPT_DBG_CPU_MCA10_CTL_HIGH_MIN 0 ///< Min of MCA10_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA10_CTL_HIGH_MAX 0xffffffff ///< Max of MCA10_CTL_HIGH

///MCA11_CTL Control
///Manual allows for overriding MCA_CTL for bank 11.
typedef enum {
  IDSOPT_DBG_CPU_MCA11_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA11_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA11_CTL_CTRL;

///MCA11_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_LOW_MIN 0 ///< Min of MCA11_CTL_LOW
#define IDSOPT_DBG_CPU_MCA11_CTL_LOW_MAX 0xffffffff ///< Max of MCA11_CTL_LOW

///MCA11_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 11.
#define IDSOPT_DBG_CPU_MCA11_CTL_HIGH_MIN 0 ///< Min of MCA11_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA11_CTL_HIGH_MAX 0xffffffff ///< Max of MCA11_CTL_HIGH

///MCA12_CTL Control
///Manual allows for overriding MCA_CTL for bank 12.
typedef enum {
  IDSOPT_DBG_CPU_MCA12_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA12_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA12_CTL_CTRL;

///MCA12_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_LOW_MIN 0 ///< Min of MCA12_CTL_LOW
#define IDSOPT_DBG_CPU_MCA12_CTL_LOW_MAX 0xffffffff ///< Max of MCA12_CTL_LOW

///MCA12_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 12.
#define IDSOPT_DBG_CPU_MCA12_CTL_HIGH_MIN 0 ///< Min of MCA12_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA12_CTL_HIGH_MAX 0xffffffff ///< Max of MCA12_CTL_HIGH

///MCA13_CTL Control
///Manual allows for overriding MCA_CTL for bank 13.
typedef enum {
  IDSOPT_DBG_CPU_MCA13_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA13_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA13_CTL_CTRL;

///MCA13_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_LOW_MIN 0 ///< Min of MCA13_CTL_LOW
#define IDSOPT_DBG_CPU_MCA13_CTL_LOW_MAX 0xffffffff ///< Max of MCA13_CTL_LOW

///MCA13_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 13.
#define IDSOPT_DBG_CPU_MCA13_CTL_HIGH_MIN 0 ///< Min of MCA13_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA13_CTL_HIGH_MAX 0xffffffff ///< Max of MCA13_CTL_HIGH

///MCA14_CTL Control
///Manual allows for overriding MCA_CTL for bank 14.
typedef enum {
  IDSOPT_DBG_CPU_MCA14_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA14_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA14_CTL_CTRL;

///MCA14_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_LOW_MIN 0 ///< Min of MCA14_CTL_LOW
#define IDSOPT_DBG_CPU_MCA14_CTL_LOW_MAX 0xffffffff ///< Max of MCA14_CTL_LOW

///MCA14_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 14.
#define IDSOPT_DBG_CPU_MCA14_CTL_HIGH_MIN 0 ///< Min of MCA14_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA14_CTL_HIGH_MAX 0xffffffff ///< Max of MCA14_CTL_HIGH

///MCA15_CTL Control
///Manual allows for overriding MCA_CTL for bank 15.
typedef enum {
  IDSOPT_DBG_CPU_MCA15_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA15_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA15_CTL_CTRL;

///MCA15_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_LOW_MIN 0 ///< Min of MCA15_CTL_LOW
#define IDSOPT_DBG_CPU_MCA15_CTL_LOW_MAX 0xffffffff ///< Max of MCA15_CTL_LOW

///MCA15_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 15.
#define IDSOPT_DBG_CPU_MCA15_CTL_HIGH_MIN 0 ///< Min of MCA15_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA15_CTL_HIGH_MAX 0xffffffff ///< Max of MCA15_CTL_HIGH

///MCA16_CTL Control
///Manual allows for overriding MCA_CTL for bank 16.
typedef enum {
  IDSOPT_DBG_CPU_MCA16_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA16_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA16_CTL_CTRL;

///MCA16_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_LOW_MIN 0 ///< Min of MCA16_CTL_LOW
#define IDSOPT_DBG_CPU_MCA16_CTL_LOW_MAX 0xffffffff ///< Max of MCA16_CTL_LOW

///MCA16_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 16.
#define IDSOPT_DBG_CPU_MCA16_CTL_HIGH_MIN 0 ///< Min of MCA16_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA16_CTL_HIGH_MAX 0xffffffff ///< Max of MCA16_CTL_HIGH

///MCA17_CTL Control
///Manual allows for overriding MCA_CTL for bank 17.
typedef enum {
  IDSOPT_DBG_CPU_MCA17_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA17_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA17_CTL_CTRL;

///MCA17_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_LOW_MIN 0 ///< Min of MCA17_CTL_LOW
#define IDSOPT_DBG_CPU_MCA17_CTL_LOW_MAX 0xffffffff ///< Max of MCA17_CTL_LOW

///MCA17_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 17.
#define IDSOPT_DBG_CPU_MCA17_CTL_HIGH_MIN 0 ///< Min of MCA17_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA17_CTL_HIGH_MAX 0xffffffff ///< Max of MCA17_CTL_HIGH

///MCA18_CTL Control
///Manual allows for overriding MCA_CTL for bank 18.
typedef enum {
  IDSOPT_DBG_CPU_MCA18_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA18_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA18_CTL_CTRL;

///MCA18_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_LOW_MIN 0 ///< Min of MCA18_CTL_LOW
#define IDSOPT_DBG_CPU_MCA18_CTL_LOW_MAX 0xffffffff ///< Max of MCA18_CTL_LOW

///MCA18_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 18.
#define IDSOPT_DBG_CPU_MCA18_CTL_HIGH_MIN 0 ///< Min of MCA18_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA18_CTL_HIGH_MAX 0xffffffff ///< Max of MCA18_CTL_HIGH

///MCA19_CTL Control
///Manual allows for overriding MCA_CTL for bank 19.
typedef enum {
  IDSOPT_DBG_CPU_MCA19_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA19_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA19_CTL_CTRL;

///MCA19_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_LOW_MIN 0 ///< Min of MCA19_CTL_LOW
#define IDSOPT_DBG_CPU_MCA19_CTL_LOW_MAX 0xffffffff ///< Max of MCA19_CTL_LOW

///MCA19_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 19.
#define IDSOPT_DBG_CPU_MCA19_CTL_HIGH_MIN 0 ///< Min of MCA19_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA19_CTL_HIGH_MAX 0xffffffff ///< Max of MCA19_CTL_HIGH

///MCA20_CTL Control
///Manual allows for overriding MCA_CTL for bank 20.
typedef enum {
  IDSOPT_DBG_CPU_MCA20_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA20_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA20_CTL_CTRL;

///MCA20_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_LOW_MIN 0 ///< Min of MCA20_CTL_LOW
#define IDSOPT_DBG_CPU_MCA20_CTL_LOW_MAX 0xffffffff ///< Max of MCA20_CTL_LOW

///MCA20_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 20.
#define IDSOPT_DBG_CPU_MCA20_CTL_HIGH_MIN 0 ///< Min of MCA20_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA20_CTL_HIGH_MAX 0xffffffff ///< Max of MCA20_CTL_HIGH

///MCA21_CTL Control
///Manual allows for overriding MCA_CTL for bank 21.
typedef enum {
  IDSOPT_DBG_CPU_MCA21_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA21_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA21_CTL_CTRL;

///MCA21_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_LOW_MIN 0 ///< Min of MCA21_CTL_LOW
#define IDSOPT_DBG_CPU_MCA21_CTL_LOW_MAX 0xffffffff ///< Max of MCA21_CTL_LOW

///MCA21_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 21.
#define IDSOPT_DBG_CPU_MCA21_CTL_HIGH_MIN 0 ///< Min of MCA21_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA21_CTL_HIGH_MAX 0xffffffff ///< Max of MCA21_CTL_HIGH

///MCA22_CTL Control
///Manual allows for overriding MCA_CTL for bank 22.
typedef enum {
  IDSOPT_DBG_CPU_MCA22_CTL_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_MCA22_CTL_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_MCA22_CTL_CTRL;

///MCA22_CTL_LOW
///Value to program the lower 32 bits of the MCA_CTL for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_LOW_MIN 0 ///< Min of MCA22_CTL_LOW
#define IDSOPT_DBG_CPU_MCA22_CTL_LOW_MAX 0xffffffff ///< Max of MCA22_CTL_LOW

///MCA22_CTL_HIGH
///Value to program the upper 32 bits of the MCA_CTL for bank 22.
#define IDSOPT_DBG_CPU_MCA22_CTL_HIGH_MIN 0 ///< Min of MCA22_CTL_HIGH
#define IDSOPT_DBG_CPU_MCA22_CTL_HIGH_MAX 0xffffffff ///< Max of MCA22_CTL_HIGH

///CR4.MCE Control
///Set / clear CR4.MCE bit.
typedef enum {
  IDSOPT_DBG_CPU_CR4_MCE_CTRL_CLEAR = 0,///<Clear
  IDSOPT_DBG_CPU_CR4_MCE_CTRL_SET = 1,///<Set
  IDSOPT_DBG_CPU_CR4_MCE_CTRL_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_CR4_MCE_CTRL;

///Lock Threshold Counters
///Set MCAi_MISC[Locked] = 0/1
typedef enum {
  IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS_0 = 0,///<0
  IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS_1 = 1,///<1
  IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_CPU_LOCK_THRESHOLD_COUNTERS;

///BTHB Core 0 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE0;

///BTHB Core 1 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1_8MB = 4,///< 8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE1;

///BTHB Core 2 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2_8MB = 4,///< 8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE2;

///BTHB Core 3 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE3;

///BTHB Core 4 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE4;

///BTHB Core 5 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE5;

///BTHB Core 6 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE6;

///BTHB Core 7 Hole Size
///Buffer size
typedef enum {
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_1MB = 1,///<1 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_2MB = 2,///<2 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_4MB = 3,///<4 MB
  IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7_8MB = 4,///<8 MB
} IDSOPT_DBG_CPU_GEN_BTHB_MEM_HOLE_CORE7;

///uCode Patching
///Enable or disable microcode patching. If disabled, no microcode patches will be loaded. If enabled, only patches that apply to the installed processor will be loaded.
typedef enum {
  IDSOPT_DBG_CPU_GEN_U_CODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_U_CODE_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_GEN_U_CODE;

///Sync Flood on MCA
///Enable or disable BIOS Sync Flood on MCA.
typedef enum {
  IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SYNC_FLOOD_MCA;

///Enable Redirect Shutdown to HDT
typedef enum {
  IDSOPT_DBG_CPU_GEN_REDIRECT_SHUTDOWN_TO_HDT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_REDIRECT_SHUTDOWN_TO_HDT_AUTO = 0,///<Auto
} IDSOPT_DBG_CPU_GEN_REDIRECT_SHUTDOWN_TO_HDT;

///Enable Redirect int1 int3 to HDT
///redirect debug exceptions and breakpoints to HDT
typedef enum {
  IDSOPT_DBG_CPU_GEN_REDIRECT_EXCEPTIONS_TO_HDT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_REDIRECT_EXCEPTIONS_TO_HDT_AUTO = 0,///<Auto
} IDSOPT_DBG_CPU_GEN_REDIRECT_EXCEPTIONS_TO_HDT;

///Exception Breakpoint Control
///Enable:\n  Set MSRC001_1018[8]=0x1\n  Set MSRC001_100A[17]=1\nDisable:\n  Set MSRC001_1018[8]=0x0\n  Set MSRC001_100A[17]=0
typedef enum {
  IDSOPT_DBG_CPU_EXCP_BP_CTRL_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_CPU_EXCP_BP_CTRL_ENABLE = 0x1,///<Enable
} IDSOPT_DBG_CPU_EXCP_BP_CTRL;

///Exception Vector
///Specifies an exception vector
#define IDSOPT_DBG_CPU_EXCP_VEC_MIN 0 ///< Min of Exception Vector
#define IDSOPT_DBG_CPU_EXCP_VEC_MAX 0xff ///< Max of Exception Vector

///LBR
///1=Enable last branch record.
typedef enum {
  IDSOPT_DBG_CPU_GEN_LBR_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_LBR_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_LBR_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LBR;

///HDT OUT
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDTOUT_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDTOUT_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDTOUT;

///ABL BreakPoint
///Enable : Enable Break Point Function for ABL\nDisable : Disable Break Point Function for ABL\nAuto : Keep default behavior
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_BP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_ABL_BP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_ABL_BP_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ABL_BP;

///ABL ConsoleOut
///Enable : Enable ConsoleOut Function for ABL\nDisable : Disable ConsoleOut Function for ABL\nAuto : Keep default behavior
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_CON_OUT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_ABL_CON_OUT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_ABL_CON_OUT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ABL_CON_OUT;

///ABL HDTOUT
///ABL HdtOut is require additional HDT perl script\nEnable : Enable HdtOut Function for ABL\nDisable : Disable HdtOut Function for ABL
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT;

///ABL HDTOUT Die Control
///AUTO, Select Die 0 for SCM, and Socket 0 Die 1 for MCM\nManual, Specified the Enabled Die by ABL HDTOUT Die bitmask option
typedef enum {
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_CTRL_AUTO = 0,///<AUTO
  IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_CTRL_MANUAL = 1,///<Manual
} IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_CTRL;

///ABL HDTOUT Die Bitmask
///Specified the ABLOUT enabled die through bit mask, each bit is corresponding to a die,  max support 2 sockets 4 dies. e.g. 0x16 enable Socket 0 Die 1 & Die 2, Socket 1 Die 0
#define IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_BIT_MASK_MIN 0 ///< Min of ABL HDTOUT Die Bitmask
#define IDSOPT_DBG_CPU_GEN_ABL_HDT_OUT_DIE_BIT_MASK_MAX 0xff ///< Max of ABL HDTOUT Die Bitmask

///HDT Breakpoint 1 (x86 AGESA start)
///Setting this option to enabled will cause the BIOS to force the system into HDT mode just before DRAM init, right after the backend code for the memory timing options is run and immediately before the DRAM enable bit is set. All of the registers for DCT init will be programmed, but the DRAM Init bit will not have been set yet.
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT1_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDT_BRKPT1;

///HDT Breakpoint 2 (Before PCI init)
///Setting this option to enabled will cause the BIOS to force the system into HDT mode just before PCI initialization.
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT2_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDT_BRKPT2;

///HDT Breakpoint 3 (Before OS)
///Setting this option to enabled will cause the BIOS to force the system into HDT mode very late in POST.
typedef enum {
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT3_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_HDT_BRKPT3_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_HDT_BRKPT3;

///IC DQ Stall Workaround
///Select which workaround for PLAT-9100 to apply to A0 parts with SMT enabled.  If SMT is disabled, neither workaround will be applied.\nNote: If BP[25] is set, IC_CFG[22:18] will be cleared to zero.\n'Auto' is NOT RECOMMENDED internally.
typedef enum {
  IDSOPT_DBG_CPU_GEN_IC_DQ_STALL_WA_BP25DISL2CORR = 0,///<BP[25]-Dis L2 Corr
  IDSOPT_DBG_CPU_GEN_IC_DQ_STALL_WA_IC5DISOPCACHE = 1,///<IC[5]-Dis Op Cache
  IDSOPT_DBG_CPU_GEN_IC_DQ_STALL_WA_NONE = 4,///<None
  IDSOPT_DBG_CPU_GEN_IC_DQ_STALL_WA_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_IC_DQ_STALL_WA;

///Core Watchdog Timer Disable
///Enable or disable CPU Watchdog Timer
typedef enum {
  IDSOPT_DBG_CPU_GEN_CPU_WDT_0 = 0,///<0
  IDSOPT_DBG_CPU_GEN_CPU_WDT_1 = 1,///<1
  IDSOPT_DBG_CPU_GEN_CPU_WDT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_CPU_WDT;

///ACPI WHEA
///Controls activation of CPU Machine Check Setting
typedef enum {
  IDSOPT_DBG_CPU_GEN_WHEA_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_WHEA_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_GEN_WHEA_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_WHEA;

///L3 way locking
///Number of ways allocated to trace data in the L3M.
typedef enum {
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_TWO = 0,///<Two
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_SIX = 1,///<Six
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_TEN = 2,///<Ten
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_FOURTEEN = 3,///<Fourteen
  IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L3_WAY_LOCK;

///L2 Range Lock Enable
///L2 Range Lock Enable
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_RANGE_LOCK_EN;

///L3 Range Lock Enable
///L3 Range Lock Enable
typedef enum {
  IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_CPU_GEN_L3_RANGE_LOCK_EN;

///RdRand
///Disable RdRand instruction
typedef enum {
  IDSOPT_DBG_CPU_GEN_RD_RAND_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_RD_RAND_DISABLE = 1,///<Disable
} IDSOPT_DBG_CPU_GEN_RD_RAND;

///RdSeed
///Disable RdSeed instruction
typedef enum {
  IDSOPT_DBG_CPU_GEN_RD_SEED_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RD_SEED_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_GEN_RD_SEED;

///SMEE
///Control secure memory encryption enable
typedef enum {
  IDSOPT_DBG_CPU_GEN_SMEE_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SMEE_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SMEE_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SMEE;

///SVM Lock
///Control SVM lock
typedef enum {
  IDSOPT_DBG_CPU_GEN_SVM_LOCK_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SVM_LOCK_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SVM_LOCK_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SVM_LOCK;

///Report Responsible Victim
///Control ChL3Cfg0[ReportResponsibleVic]
typedef enum {
  IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_REPORT_RESPONSIBLE_VIC;

///Report Shared Victim
///Control ChL3Cfg0[ReportSharedVic]
typedef enum {
  IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_REPORT_SHARED_VIC;

///Spec DRAM Rd Dis
///Control ChL3Cfg1[SpecDramRdDis]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_DRAM_RD_DIS;

///CacheLock Disable
///Control LS_CFG[LsCfgDisCacheLock]
typedef enum {
  IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_CACHE_LOCK_DIS;

///SpecLockMap Disable
///Control LS_CFG[LsCfgDisSpecLockMap]. Note: if the 'Enable IBS' option is Enabled, SpecLockMap will be disabled and setting this option to 'Enable' will have no effect on the bit field.
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS;

///Disable L1 Region HW Prefetcher
///Control DC_CFG[DisRegionHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_REG_HW_PRE_F_DIS;

///Disable L1 Stride HW Prefetcher
///Control DC_CFG[DisStrideHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_STRIDE_HW_PRE_F_DIS;

///Disable L1 HW Prefetcher
///Control DC_CFG[DisHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_HW_PRE_F_DIS;

///Disable 32K Pages
///Control TW_CFG[Dis32KPages]
typedef enum {
  IDSOPT_DBG_CPU_GEN32K_PAGES_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN32K_PAGES_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN32K_PAGES_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN32K_PAGES_DIS;

///Disable MemRenaming
///Control DE_CFG[DecfgMemRenameDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_MEM_RENAMING_DIS;

///Disable Recent
///Control BP_CFG[DIS_RECENT]
typedef enum {
  IDSOPT_DBG_CPU_GEN_RECENT_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RECENT_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_RECENT_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_RECENT_DIS;

///Disable L2 Pf Low Arb Pri
///Control L2_CFG[DisableL2PfLowArbPriority]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_PF_LO_ARB_PRI_DIS;

///L2 Stride Prefetcher
///Control L2_PFCFG[EnableStridePf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_STRIDE_PF;

///L2 Max Stride Distance
///Control L2_PFCFG[MaxStrideDist]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_20STRIDES = 0,///<20 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_16STRIDES = 1,///<16 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_12STRIDES = 2,///<12 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_8STRIDES = 3,///<8 Strides
  IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_MAX_STRIDE_DIST;

///Page Pf Hint Dis
///Control L2_PFCFG[DisablePagePfHint]
typedef enum {
  IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_PAGE_PF_HINT_DIS;

///L2 Max Stream Distance
///Control L2_PFCFG[MaxStreamDist]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_31LINES = 0,///<31 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_24LINES = 1,///<24 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_16LINES = 2,///<16 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_8LINES = 3,///<8 Lines
  IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_MAX_STREAM_DIST;

///L2 Page Pf Distance
///Control L2_PFCFG[PagePfDist]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_16LINES = 0,///<16 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_8LINES = 1,///<8 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_20LINES = 2,///<20 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_28LINES = 3,///<28 Lines
  IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_PG_PF_DIST;

///Stream Throttle Control
///Control L2_PFCFG[StreamThrottleControl]
typedef enum {
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_OFF = 0,///<Off
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_ON = 1,///<On
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_UPDATEIMM = 2,///<Update Imm
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_UPDATE128RSP = 3,///<Update 128 rsp
  IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_STREAM_THR_CTRL;

///Disable Spec TLB Reload
///Control DC_CFG[DisSpecTlbRld]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_TLB_RLD_DIS;

///Stack Engine Disable
///Control DE_CFG[DecfgStackEngineDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_STACK_ENG_DIS;

///Mem File Disable
///Control DE_CFG[DecfgMemfileDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_MEM_FILE_DIS;

///OC_BUILD_CNT_MAX
///Control IC_CFG[OC_BUILD_CNT_MAX]
#define IDSOPT_DBG_CPU_GEN_OC_BLD_CNT_MAX_MIN 0 ///< Min of OC_BUILD_CNT_MAX
#define IDSOPT_DBG_CPU_GEN_OC_BLD_CNT_MAX_MAX 0x1f ///< Max of OC_BUILD_CNT_MAX

///Mesh Gate Level
///Control ChL3Cfg0[MeshGateLvl]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_OFF = 0,///<Off
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_REQUEST = 1,///<Request
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_MEMORY = 2,///<Memory
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_DATAFLOW = 3,///<Dataflow
  IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_MESH_GATE_LVL;

///DelayedWakeEn
///Control ChL3Cfg0[DelayedWakeEn]
typedef enum {
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_DELAYED_WK_EN;

///Delayed Wake Count
///Control ChL3Cfg0[DelayedWakeCount]
typedef enum {
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_64VICTIMS = 0,///<64 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_128VICTIMS = 1,///<128 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_256VICTIMS = 2,///<256 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_512VICTIMS = 3,///<512 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_1024VICTIMS = 4,///<1024 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_2048VICTIMS = 5,///<2048 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_4096VICTIMS = 6,///<4096 Victims
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_UNLIMITED = 7,///<Unlimited
  IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_DELAYED_WK_CNT;

///Mesh Gate Hold
///Control ChL3Cfg1[MeshGateHold]
#define IDSOPT_DBG_CPU_GEN_MESH_GATE_HOLD_MIN 0 ///< Min of Mesh Gate Hold
#define IDSOPT_DBG_CPU_GEN_MESH_GATE_HOLD_MAX 0x3 ///< Max of Mesh Gate Hold

///L2EvictForceDcBackprobe
///Control L2_CFG[L2EvictForceDcBackprobe]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_EVICT_FORCE_DC_BK_PRB;

///L2WcbXrqSerializeTidAgnostic
///Control L2_CFG[L2WcbXrqSerializeTidAgnostic]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_WCB_XRQ_SER_TID_AGN;

///DisableLsReqPfPromotion
///Control L2_CFG[DisableLsReqPfPromotion]
typedef enum {
  IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LS_REQ_PF_PROM_DIS;

///TdPickThrottleEnable
///Control L2_CFG[TdPickThrottleEnable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_TD_PICK_THR_EN;

///DisableAllEarlyVbTokenRet
///Control L2_CFG[DisableAllEarlyVbTokenRet]
typedef enum {
  IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_EARLY_VB_TOK_RET_DIS;

///L2 Up Down Prefetcher
///Control L2_PFCFG[EnableUpDownPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_UP_DOWN_PF;

///FP_CFG: RET_DISACCF
///Control FP_CFG[RET_DISACCF]
typedef enum {
  IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_RET_DIS_ACC_F;

///FP_CFG: RET_ADVTOK_RET
///Control FP_CFG[RET_ADVTOK_RET]
#define IDSOPT_DBG_CPU_GEN_RET_ADV_TOK_RET_MIN 0 ///< Min of FP_CFG: RET_ADVTOK_RET
#define IDSOPT_DBG_CPU_GEN_RET_ADV_TOK_RET_MAX 0x7 ///< Max of FP_CFG: RET_ADVTOK_RET

///FP_CFG: SCE_THROTTLE_X87
///Control FP_CFG[SCE_THROTTLE_X87]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_THR_X87_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_THR_X87_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_THR_X87_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_THR_X87;

///FP_CFG: SCE_ENABLE_RRT
///Control FP_CFG[SCE_ENABLE_RRT]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_EN_RRT_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_EN_RRT_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_EN_RRT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_EN_RRT;

///FP_CFG: SCE_ALWAYS_THROTTLE
///Control FP_CFG[SCE_ALWAYS_THROTTLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_08 = 0,///<0/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_18 = 1,///<1/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_28 = 2,///<2/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_48 = 3,///<4/8
  IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_ALWAYS_THR;

///FP_CFG: SCE_LIVELOCK_THRESH
///Control FP_CFG[SCE_LIVELOCK_THRESH]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_16 = 0,///<16
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_32 = 1,///<32
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_64 = 2,///<64
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH;

///FP_CFG: SCE_DIDT_TH_ENABLE
///Control FP_CFG[SCE_DIDT_TH_ENABLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_EN;

///FP_CFG: SCE_DIDT_INJ_F_ENABLE
///Control FP_CFG[SCE_DIDT_INJ_F_ENABLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_F_EN;

///FP_CFG: SCE_DIDT_INJ_R_ENABLE
///Control FP_CFG[SCE_DIDT_INJ_R_ENABLE]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_R_EN;

///FP_CFG: SCE_DIDT_TH_SCHEME
///Control FP_CFG[SCE_DIDT_TH_SCHEME]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME_REACT = 0,///<React
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME_PRESET = 1,///<Preset
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_TH_SCHEME;

///FP_CFG: SCE_DIDT_TIMECONST
///Control FP_CFG[SCE_DIDT_TIMECONST]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_2 = 0,///<2
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_4 = 1,///<4
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_8 = 2,///<8
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST;

///FP_CFG: SCE_DIDT_TH_THRESH
///Control FP_CFG[SCE_DIDT_TH_THRESH]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH_REGULAR = 0,///<Regular
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH_LOW = 1,///<Low
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_THR_THRESH;

///FP_CFG: SCE_DIDT_INJ_THRESH
///Control FP_CFG[SCE_DIDT_INJ_THRESH]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_LOW = 0,///<Low
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_MEDLOW = 1,///<Med Low
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_MEDHIGH = 2,///<Med High
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_HIGH = 3,///<High
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH_AUTO = 7,///<Auto
} IDSOPT_DBG_CPU_GEN_SCE_DIDT_INJ_THRESH;

///L2 Stream Throttle Disable
///Control L2_PFCFG[L2StreamThrottleDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_STREAM_THR_DIS;

///BP Prefetch Disable
///Control BP_CFG[BpCfgDisPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_BP_PF_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BP_PF_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_BP_PF_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_BP_PF_DIS;

///BP Disable
///Control BP_CFG[DIS_L1BTB]
typedef enum {
  IDSOPT_DBG_CPU_GEN_BP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_BP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_BP_DIS;

///OC Token Bypass Disable
///Control IC_CFG[IcCfgDisOcTokenBypass]
typedef enum {
  IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_OC_TOK_BYP_DIS;

///Branch Fusion
///Control DE_CFG[DecfgBranchFusionDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_BRANCH_FUSION_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_BRANCH_FUSION_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_BRANCH_FUSION_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_BRANCH_FUSION;

///EX_CFG: FORCE_EXSCBUSY_GATER
///Control EX_CFG[FORCE_EXSCBUSY_GATER]
typedef enum {
  IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_FORCE_EXSC_BUSY_GATER;

///TW_CFG: CohMemTypesOnly
///Control TW_CFG[TwCfgCohMemTypesOnly]
typedef enum {
  IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_COH_MEM_TYP_ONLY;

///Locks to only schedule non-spec
///Control LS_CFG[LsCfgScnLockNs]
typedef enum {
  IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LS_CFG_SCN_LOCK_NS;

///ResyncOoOLdOnL1Evict
///Control LS_CFG[LsCfgResyncOoOLdOnL1Evict]
typedef enum {
  IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_RESYNC_OO_O_LD_ON_L1_EVICT;

///MemFile2EGS Disable
///Control LS_CFG[LsCfgDisMemfile2EGS]
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_MEM_FILE2_EGS_DIS;

///SpecWcReq Disable
///Control LS_CFG[LsCfgDisSpecWcReq]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_WC_REQ_DIS;

///ForceAllSbex
///Control LS_CFG[LsCfgForceAllSbex]
typedef enum {
  IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_FORCE_ALL_SBEX;

///DisLiveLockIgnMabIdxBlk
///Control LS_CFG2[DisLiveLockIgnMabIdxBlk]
typedef enum {
  IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_LIVE_LOCK_IGN_MAB_IDX_BLK_DIS;

///DisStIgnMabIdxBlk
///Control LS_CFG2[DisStIgnMabIdxBlk]
typedef enum {
  IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_ST_IGN_MAB_IDX_BLK_DIS;

///DisDcTagPaDcVFatalErr
///Control LS_CFG2[DisDcTagPaDcVFatalErr]
typedef enum {
  IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_DC_TAG_PA_DC_V_FATAL_ERR_DIS;

///WrSzLkUpDis
///Control ChL3Cfg0[WrSzLkUpDis]
typedef enum {
  IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_WR_SZ_LK_UP_DIS;

///DSM setup for 6346 detection
///Enables a DSM script to load on all cores to help quickly detect the 6346 bug.  Only applies to A0 silicon.
typedef enum {
  IDSOPT_DBG_CPU_GEN6346_DSM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN6346_DSM_AUTO = 3,///<Auto
  IDSOPT_DBG_CPU_GEN6346_DSM_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN6346_DSM;

///JitterEn
///Disable - DPM_CFG[60][JitterEn] = 0\nEnable  - DPM_CFG[60][JitterEn] = 1
typedef enum {
  IDSOPT_DBG_CPU_GEN_JITTER_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_JITTER_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_JITTER_EN_AUTO = 0xF,///<Auto
} IDSOPT_DBG_CPU_GEN_JITTER_EN;

///Combo DSM script application
///Can be used to disable the combo DSM script automatically applied to ZP-Bx silicon.  Only applies to non-secure parts.
typedef enum {
  IDSOPT_DBG_CPU_GEN_COMBO_DSM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_COMBO_DSM_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_GEN_COMBO_DSM;

///SmmLock Control
///Disabling this feature forces SmmLock to be cleared.
typedef enum {
  IDSOPT_DBG_CPU_SMM_LOCK_CONTROL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_SMM_LOCK_CONTROL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_SMM_LOCK_CONTROL;

///Core Digital Power Monitor (DPM) Control
///Auto = Use default settings for Core DPM\nManual = User can set custom settings for Core DPM
typedef enum {
  IDSOPT_DBG_CPU_PWR_DPM_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_PWR_DPM_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_PWR_DPM_CTRL;

///Core DPM Enable
///This control enables/disables the CAC accumulators in the Core.\n 0 = Core DPM disabled (DPM_CFG[CfgLocked] = 0)\n 1 = Core DPM enabled (DPM_CFG[CfgLocked] = 1)
typedef enum {
  IDSOPT_DBG_CPU_PWR_DPM_EN_0 = 0,///<0
  IDSOPT_DBG_CPU_PWR_DPM_EN_1 = 1,///<1
} IDSOPT_DBG_CPU_PWR_DPM_EN;

///Core MSR Access Disable
///This control enables/disables the MSR Access in the Core.\n 0 = Core MSR Access ENABLED (DPM_CFG[MsrAccessDisable] = 0)\n 1 = Core MSR Access DISABLED (DPM_CFG[MsrAccessDisable] = 1)
typedef enum {
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_0 = 0,///<0
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_1 = 1,///<1
} IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS;

///ACPI _PSS
///Enable / disable the P-state object declaration to the OS.
typedef enum {
  IDSOPT_DBG_CPU_PM_CTL_PSS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_PM_CTL_PSS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_PM_CTL_PSS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_PM_CTL_PSS;

///FP Throttle Control
///FP Throttle Control
typedef enum {
  IDSOPT_DBG_CPU_PM_FP_THROTTLE_CTRL_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_PM_FP_THROTTLE_CTRL_MANUAL = 1,///<Manual
} IDSOPT_DBG_CPU_PM_FP_THROTTLE_CTRL;

///FP Throttle
/// MSRC001_1028[52:48]=INPUT
#define IDSOPT_DBG_CPU_PM_FP_THROTTLE_MIN 0 ///< Min of FP Throttle
#define IDSOPT_DBG_CPU_PM_FP_THROTTLE_MAX 0x1f ///< Max of FP Throttle

///SC Throttle Control
///SC Throttle Control
typedef enum {
  IDSOPT_DBG_CPU_PM_SC_THROTTLE_CTRL_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_PM_SC_THROTTLE_CTRL_MANUAL = 1,///<Manual
} IDSOPT_DBG_CPU_PM_SC_THROTTLE_CTRL;

///SC Throttle
/// MSRC001_3230[5:1]=INPUT
#define IDSOPT_DBG_CPU_PM_SC_THROTTLE_MIN 0 ///< Min of SC Throttle
#define IDSOPT_DBG_CPU_PM_SC_THROTTLE_MAX 31 ///< Max of SC Throttle

///Memory Holes at 2G and 5G (512MB)
///Allocate 512MB memory holes at 2G and 5G
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G;

///SMM handler size per thread
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_FOR_SMM_PER_THREAD_MIN 0 ///< Min of SMM handler size per thread
#define IDSOPT_DBG_CPU_MEM_HOLE_FOR_SMM_PER_THREAD_MAX 4294967295 ///< Max of SMM handler size per thread

///Memory Hole on Socket 0 Die 0
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE0_MIN 0 ///< Min of Memory Hole on Socket 0 Die 0
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE0_MAX 4294967295 ///< Max of Memory Hole on Socket 0 Die 0

///Memory Hole on Socket 0 Die 1
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE1_MIN 0 ///< Min of Memory Hole on Socket 0 Die 1
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE1_MAX 4294967295 ///< Max of Memory Hole on Socket 0 Die 1

///Memory Hole on Socket 0 Die 2
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE2_MIN 0 ///< Min of Memory Hole on Socket 0 Die 2
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE2_MAX 4294967295 ///< Max of Memory Hole on Socket 0 Die 2

///Memory Hole on Socket 0 Die 3
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE3_MIN 0 ///< Min of Memory Hole on Socket 0 Die 3
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE3_MAX 4294967295 ///< Max of Memory Hole on Socket 0 Die 3

///Memory Hole on Socket 1 Die 0
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE4_MIN 0 ///< Min of Memory Hole on Socket 1 Die 0
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE4_MAX 4294967295 ///< Max of Memory Hole on Socket 1 Die 0

///Memory Hole on Socket 1 Die 1
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE5_MIN 0 ///< Min of Memory Hole on Socket 1 Die 1
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE5_MAX 4294967295 ///< Max of Memory Hole on Socket 1 Die 1

///Memory Hole on Socket 1 Die 2
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE6_MIN 0 ///< Min of Memory Hole on Socket 1 Die 2
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE6_MAX 4294967295 ///< Max of Memory Hole on Socket 1 Die 2

///Memory Hole on Socket 1 Die 3
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE7_MIN 0 ///< Min of Memory Hole on Socket 1 Die 3
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE7_MAX 4294967295 ///< Max of Memory Hole on Socket 1 Die 3

///Core master request ordering
///Can be used to force TgtStart/TgtDone ordering on all ReqBlockLevel 2 read or write sized requests.
typedef enum {
  IDSOPT_DF_DBG_CORE_MSTR_REQ_ORDERING_ALWAYSORDERED = 0,///<Always Ordered
  IDSOPT_DF_DBG_CORE_MSTR_REQ_ORDERING_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CORE_MSTR_REQ_ORDERING;

///I/O master request ordering
///Can be used to disable the Target Start shortcut.
typedef enum {
  IDSOPT_DF_DBG_IO_MSTR_REQ_ORDERING_ALWAYSORDERED = 0,///<Always Ordered
  IDSOPT_DF_DBG_IO_MSTR_REQ_ORDERING_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_IO_MSTR_REQ_ORDERING;

///Medium grain clock gating
///Controls the MGCG feature.
typedef enum {
  IDSOPT_DF_DBG_MGCG_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLEDNOHYST = 1,///<Enabled - no hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED1FCLKHYST = 2,///<Enabled - 1FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED2FCLKHYST = 3,///<Enabled - 2FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED3FCLKHYST = 4,///<Enabled - 3FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED4FCLKHYST = 5,///<Enabled - 4FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED5FCLKHYST = 6,///<Enabled - 5FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED6FCLKHYST = 7,///<Enabled - 6FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED7FCLKHYST = 8,///<Enabled - 7FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED8FLCKHYST = 9,///<Enabled - 8FLCK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED9FCLKHYST = 10,///<Enabled - 9FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED10FCLKHYST = 11,///<Enabled - 10FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED11FCLKHYST = 12,///<Enabled - 11FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED15FCLKHYST = 13,///<Enabled - 15FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED31FCLKHYST = 14,///<Enabled - 31FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_ENABLED63FCLKHYST = 15,///<Enabled - 63FCLK hyst
  IDSOPT_DF_DBG_MGCG_CTRL_AUTO = 31,///<Auto
} IDSOPT_DF_DBG_MGCG_CTRL;

///Disable MemCancel
///Controls DF::CCMConfig1[DisAllMemCancel]
typedef enum {
  IDSOPT_DF_DBG_MEM_CANCEL_DIS_FORCEOFF = 0,///<Force off
  IDSOPT_DF_DBG_MEM_CANCEL_DIS_FORCEON = 1,///<Force on
  IDSOPT_DF_DBG_MEM_CANCEL_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_MEM_CANCEL_DIS;

///Disable migratory probes
///Controls DF::CoherentSlaveConfigA1[DisPrbMig]
typedef enum {
  IDSOPT_DF_DBG_MIG_PRB_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_MIG_PRB_DIS_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_MIG_PRB_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_MIG_PRB_DIS;

///Redirect scrub limits
///Controls the number of redirect scrubs allowed at any one time (DF::RedirScrubCtrl[RedirScrubReqLmt])
typedef enum {
  IDSOPT_DF_DBG_REDIR_SCRUB_LMT_2 = 0,///<2
  IDSOPT_DF_DBG_REDIR_SCRUB_LMT_4 = 1,///<4
  IDSOPT_DF_DBG_REDIR_SCRUB_LMT_8 = 2,///<8
  IDSOPT_DF_DBG_REDIR_SCRUB_LMT_NOLIMIT = 3,///<No limit
  IDSOPT_DF_DBG_REDIR_SCRUB_LMT_AUTO = 7,///<Auto
} IDSOPT_DF_DBG_REDIR_SCRUB_LMT;

///Stop on SPF error detect
///Controls DF::SpfModeControl0[StopOnProtErrDet]
typedef enum {
  IDSOPT_DF_DBG_STOP_ON_SPF_ERROR_STOP = 0,///<Stop
  IDSOPT_DF_DBG_STOP_ON_SPF_ERROR_CONTINUE = 1,///<Continue
  IDSOPT_DF_DBG_STOP_ON_SPF_ERROR_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_STOP_ON_SPF_ERROR;

///Disable TCDX bypasses
///Controls TCDX bypasses DF::TCDXConfig[BypassEnable]
typedef enum {
  IDSOPT_DF_DBG_TCDX_BYPASS_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_TCDX_BYPASS_DIS_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_TCDX_BYPASS_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_TCDX_BYPASS_DIS;

///F1/F fetch probes - remote
///Controls DF::SpfModeControl0[DisSrcDieFetchRmtSkt]
typedef enum {
  IDSOPT_DF_DBG_F1F_FETCH_PRB_RMT_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_F1F_FETCH_PRB_RMT_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_F1F_FETCH_PRB_RMT_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_F1F_FETCH_PRB_RMT;

///F1/F fetch probes - local
///Controls DF::SpfModeControl0[DisSrcDieFetchLclSkt]
typedef enum {
  IDSOPT_DF_DBG_F1F_FETCH_PRB_LCL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_F1F_FETCH_PRB_LCL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_F1F_FETCH_PRB_LCL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_F1F_FETCH_PRB_LCL;

///F1/F fetch probes - on die
///Controls DF::SpfModeControl0[DisTgtDieFetch]
typedef enum {
  IDSOPT_DF_DBG_F1F_FETCH_PRB_TARGET_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_F1F_FETCH_PRB_TARGET_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_F1F_FETCH_PRB_TARGET_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_F1F_FETCH_PRB_TARGET;

///Disable SPF ways
///Can be used to disable ways of each bank. (DF::SpfWayDisable0 and Df::SpfWayDisable1). All four banks will be programmed the same way.
typedef enum {
  IDSOPT_DF_DBG_SPF_WAY_DIS_ALLWAYSENABLED = 0,///<All ways enabled
  IDSOPT_DF_DBG_SPF_WAY_DIS_1WAYDISABLED = 1,///<1 way disabled
  IDSOPT_DF_DBG_SPF_WAY_DIS_2WAYSDISABLED = 2,///<2 ways disabled
  IDSOPT_DF_DBG_SPF_WAY_DIS_4WAYSDISABLED = 3,///<4 ways disabled
  IDSOPT_DF_DBG_SPF_WAY_DIS_8WAYSDISABLED = 4,///<8 ways disabled
  IDSOPT_DF_DBG_SPF_WAY_DIS_11WAYSDISABLED = 5,///<11 ways disabled
  IDSOPT_DF_DBG_SPF_WAY_DIS_AUTO = 7,///<Auto
} IDSOPT_DF_DBG_SPF_WAY_DIS;

///I/O request bus lock control
///Can be used to force bus locks on all IO non-posted requests, not just atomics (DF::IOMConfig[EnReqBusLock])
typedef enum {
  IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IO_REQ_BUS_LOCK_CTRL;

///IOM PerfMon Ctrl - PrbRsp
///Controls DF:IOMConfig[LatMonFtiPrbRsp]
typedef enum {
  IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP_TGTDONE = 0,///<TgtDone
  IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP_PRBRSP = 1,///<PrbRsp
  IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IOM_PERF_MON_PRB_RSP;

///IOM PerfMon Ctrl - TgtSel
///Controls DF:IOMConfig[LatMonTgtSel]
typedef enum {
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_DRAM = 0,///<DRAM
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_IO = 1,///<I/O
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_INTERRUPTS = 2,///<Interrupts
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_SYSMGMT = 3,///<Sys mgmt
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_FENCE = 4,///<Fence
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_FLUSH = 5,///<Flush
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_IOSRSP = 6,///<IOS rsp
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_OTHERS = 7,///<Others
  IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL_AUTO = 15,///<Auto
} IDSOPT_DF_DBG_IOM_PERF_MON_TGT_SEL;

///Watchdog Timer Control
///Controls DF watchdog timers (DF::DfGlobalCtrl[WDTBaseSel])
typedef enum {
  IDSOPT_DF_DBG_WDT_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_WDT_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_WDT_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_WDT_CTRL;

///CAKE req & addr compression
///Controls request / address compression on links (DF::CakeCompCntlReq[CntlRdBlkEn,CntlRdSzFEn,CntlRdSzHEn,CntlWrSzFEn,CntlWrSzHEn])
typedef enum {
  IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_REQ_ADDR_COMPRESSION;

///CAKE data compression
///Controls data compression on links (DF::CakeCompCntlReq[CntlDatCompPatEn])
typedef enum {
  IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_DATA_COMPRESSION;

///CAKE resp command packing
///Controls response command packing on links (DF::CakeCntlRsp[CntlSrcDnEn,CntlTgtStEn,CntlTgtDnDEn,CntlTgtDnEn,CntlTknEn])
typedef enum {
  IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_RSP_CMD_PACKING;

///CAKE probe combining
///Controls probe combining on links (DF::CakePrbCmbCntl[CntlPrbCmbSrcDis, CntlPrbCmbTgtDis])
typedef enum {
  IDSOPT_DF_DBG_CAKE_PRB_COMBINING_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_PRB_COMBINING_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_PRB_COMBINING_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_PRB_COMBINING;

///CAKE IO addr compression bit
///Controls which address bit is used for I/O compression index (DF::CakeCompCntlReq[CntlCompZIomAddrBit])
typedef enum {
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT20 = 0,///<Bit 20
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT21 = 1,///<Bit 21
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT22 = 2,///<Bit 22
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_BIT23 = 3,///<Bit 23
  IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT_AUTO = 7,///<Auto
} IDSOPT_DF_DBG_CAKE_IO_ADDR_COMP_BIT;

///CAKE token thresholding
///Control CAKE token thresholding on ZP-Bx
typedef enum {
  IDSOPT_DF_DBG_CAKE_TKN_THRESH_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_TKN_THRESH_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_TKN_THRESH_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_TKN_THRESH;

///Optimize Cake data latency
///Enable disable CAKE data latency optimization on ZP-Bx
typedef enum {
  IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_OPT_CAKE_DAT_LAT;

///Disable I/O bus lock involvement
///Controls whether IOM participates (is locked by) bus locks (DF::PIEConfig[DisIOMLock])
typedef enum {
  IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IO_BUS_LOCK_INV_DIS;

///PIE PRQ broadcast limit
///Controls DF::PIEConfig[PrqBcstWRspLmt]
typedef enum {
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_NOLIMIT = 0,///<No limit
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_1 = 1,///<1
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_2 = 2,///<2
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_3 = 3,///<3
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_4 = 4,///<4
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_5 = 5,///<5
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_6 = 6,///<6
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_7 = 7,///<7
  IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT_AUTO = 15,///<Auto
} IDSOPT_DF_DBG_PIE_PRQ_BCST_LIMIT;

///Limit maximum I/O requests
///Limit the number of non-posted I/O requests from masters.  Select the master to limit.
typedef enum {
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_IOM = 0,///<IOM
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_CCM = 1,///<CCM
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_BOTH = 2,///<Both
  IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_LMT_MAX_IO_REQ_MASTER;

///Max I/O request limit
///Specify the number of non-posted I/O requests from the masters specified above.  The value specified will be applied directly to DF::MasterRequestControl[MstIoNpActReqLmt].  Note that '0' means that no limit is imposed.
#define IDSOPT_DF_DBG_LMT_MAX_IO_REQ_LIMIT_MIN 0 ///< Min of Max I/O request limit
#define IDSOPT_DF_DBG_LMT_MAX_IO_REQ_LIMIT_MAX 0x3f ///< Max of Max I/O request limit

///CCM LL thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LLElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LL_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LL_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LL_THRESH_CTRL;

///CCM LL thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LLElvPriReqThr]
#define IDSOPT_DF_DBG_CCM_LL_THRESH_MIN 0 ///< Min of CCM LL thresh
#define IDSOPT_DF_DBG_CCM_LL_THRESH_MAX 0xf ///< Max of CCM LL thresh

///CCM LL cumulative thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LLCumElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_CTRL;

///CCM LL cumulative thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LLCumElvPriReqThr].
#define IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_MIN 0 ///< Min of CCM LL cumulative thresh
#define IDSOPT_DF_DBG_CCM_LL_CUM_THRESH_MAX 0x3f ///< Max of CCM LL cumulative thresh

///CCM LP thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LPElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LP_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LP_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LP_THRESH_CTRL;

///CCM LP thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LPElvPriReqThr]
#define IDSOPT_DF_DBG_CCM_LP_THRESH_MIN 0 ///< Min of CCM LP thresh
#define IDSOPT_DF_DBG_CCM_LP_THRESH_MAX 0x7 ///< Max of CCM LP thresh

///CCM LP cumulative thresh control
///Controls DF::MasterLLAndLPRequestPriorityThr[LPCumElvPriReqThr].
typedef enum {
  IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_CTRL_MANUAL = 0,///<Manual
  IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_CTRL_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_CTRL;

///CCM LP cumulative thresh
///Specify the value for DF::MasterLLAndLPRequestPriorityThr[LPCumElvPriReqThr].
#define IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_MIN 0 ///< Min of CCM LP cumulative thresh
#define IDSOPT_DF_DBG_CCM_LP_CUM_THRESH_MAX 0x1f ///< Max of CCM LP cumulative thresh

///CCM bypass control
///Controls DF::CCMConfig[DisPrbReqByp, DisPrbRspByp, DisCcmReqQByp, DisCcmRspDQByp, DisCcmRspDataByp]
typedef enum {
  IDSOPT_DF_DBG_CCM_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CCM_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CCM_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CCM_BYPASS_CTRL;

///IOS resp bypass control
///Controls DF::IOMConfig[DisIosRspBypass]
typedef enum {
  IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IOS_RSP_BYPASS_CTRL;

///CAKE bypass control
///Controls DF::CakeSysConfig[FtiToGmiDatBypEn, GmiToFtiGmiDatBypEn]
typedef enum {
  IDSOPT_DF_DBG_CAKE_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CAKE_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CAKE_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CAKE_BYPASS_CTRL;

///CS bypass control
///Controls DF::CoherentSlaveConfigA1[DisRspByp, DisReqByp]
typedef enum {
  IDSOPT_DF_DBG_CS_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CS_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CS_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CS_BYPASS_CTRL;

///TgtStart control
///Controls whether or not the coherent slave sends a TgtStart packet (DF::CoherentSlaveConfigA1[DisTgtStrt])
typedef enum {
  IDSOPT_DF_DBG_TGT_START_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_TGT_START_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_TGT_START_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_TGT_START_CTRL;

///DF picker load step control
///Controls DF::PwrMgtCfg0[PickLoadStepCstateEn]
typedef enum {
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL;

///NVDIMM indicator to DF
///Controls DF::PstateS3Control [NvdimmSelfRefrEn]
typedef enum {
  IDSOPT_DF_DBG_NVDIMM_PRESENT_NVDIMMSPRESENT = 0,///<NVDIMMs present
  IDSOPT_DF_DBG_NVDIMM_PRESENT_NVDIMMSNOTPRESENT = 1,///<NVDIMMs not present
  IDSOPT_DF_DBG_NVDIMM_PRESENT_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_NVDIMM_PRESENT;

///DF Pstate change quiesce ctrl
///Controls DF::PstateS3Control[DfPstateChgDisableQuiesce]
typedef enum {
  IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PSTATE_QUIESCE_CTRL;

///DF Cstate clk pwr down ctrl
///Controls DF::CstateControl[DfCstateClkPwrDnEn]
typedef enum {
  IDSOPT_DF_DBG_CSTATE_CLK_PWR_DN_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CSTATE_CLK_PWR_DN_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CSTATE_CLK_PWR_DN_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CSTATE_CLK_PWR_DN_CTRL;

///DF Cstate self refresh ctrl
///Controls DF::CstateControl[DfCstateSelfRefrEn]
typedef enum {
  IDSOPT_DF_DBG_CSTATE_SELF_REFR_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CSTATE_SELF_REFR_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CSTATE_SELF_REFR_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CSTATE_SELF_REFR_CTRL;

///DF Cstate GMI pwr dn ctrl
///Controls DF::CstateControl[DfCstateGmiPwrDnEn]
typedef enum {
  IDSOPT_DF_DBG_CSTATE_GMI_PWR_DN_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CSTATE_GMI_PWR_DN_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CSTATE_GMI_PWR_DN_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CSTATE_GMI_PWR_DN_CTRL;

///DF Cstate xGMI pwr dn ctrl
///Controls DF::CstateControl[DfCstateXGmiPwrDnEn]
typedef enum {
  IDSOPT_DF_DBG_CSTATE_X_GMI_PWR_DN_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CSTATE_X_GMI_PWR_DN_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CSTATE_X_GMI_PWR_DN_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CSTATE_X_GMI_PWR_DN_CTRL;

///GMI / xGMI link error injection
///Inject GMI / xGMI link errors periodically.  Check the hardware config for which options are valid.  In the single link options, 'S' is socket and 'D' is internal die.
typedef enum {
  IDSOPT_DF_DBG_LINK_ERR_INJ_ALLGMILINKS = 0,///<All GMI links
  IDSOPT_DF_DBG_LINK_ERR_INJ_ALLXGMILINKS = 1,///<All xGMI links
  IDSOPT_DF_DBG_LINK_ERR_INJ_ALLLINKSGMIXGMI = 2,///<All links (GMI + xGMI)
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0D1 = 3,///<S0: D0-D1
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0D2 = 4,///<S0: D0-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0D3 = 5,///<S0: D0-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D1D2 = 6,///<S0: D1-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D1D3 = 7,///<S0: D1-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D2D3 = 8,///<S0: D2-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D0D1 = 9,///<S1: D0-D1
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D0D2 = 10,///<S1: D0-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D0D3 = 11,///<S1: D0-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D1D2 = 12,///<S1: D1-D2
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D1D3 = 13,///<S1: D1-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S1D2D3 = 14,///<S1: D2-D3
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D0XGMI = 15,///<S0: D0 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D1XGMI = 16,///<S0: D1 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D2XGMI = 17,///<S0: D2 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_S0D3XGMI = 18,///<S0: D3 xGMI
  IDSOPT_DF_DBG_LINK_ERR_INJ_AUTO = 31,///<Auto
} IDSOPT_DF_DBG_LINK_ERR_INJ;

///Allocate tokens for VC8 tracing
///Allocates tokens for VC8 tracing
typedef enum {
  IDSOPT_DF_DBG_VC8_TRACING_TOK_ALLOC_ALLOCATE = 0,///<Allocate
  IDSOPT_DF_DBG_VC8_TRACING_TOK_ALLOC_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_VC8_TRACING_TOK_ALLOC;

///REQ_CS
///Number of request credits to allocate in TCDX for CS tracing.  REQ_CS and REQ_IOMS should be a max of 3 if CS && IOMS tracing is on, else max of 5
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_CS_MIN 0 ///< Min of REQ_CS
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_CS_MAX 5 ///< Max of REQ_CS

///REQ_IOMS
///Number of request credits to allocate in TCDX for IOMS tracing.  REQ_CS and REQ_IOMS should be a max of 3 if CS && IOMS tracing is on, else max of 5
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_IOMS_MIN 0 ///< Min of REQ_IOMS
#define IDSOPT_DF_DBG_VC8_TRACING_REQ_IOMS_MAX 5 ///< Max of REQ_IOMS

///CSQ
///Number of CSQ entries to allocate.  Must not be 0 if either REQ_CS > 0 || REQ_IOMS > 0
#define IDSOPT_DF_DBG_VC8_TRACING_CSQ_MIN 0 ///< Min of CSQ
#define IDSOPT_DF_DBG_VC8_TRACING_CSQ_MAX 32 ///< Max of CSQ

///RSP_IOMS
///Number of response credits to allocate in IOMS for responses.  Must not be 0 if REQ_IOMS > 0
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_IOMS_MIN 0 ///< Min of RSP_IOMS
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_IOMS_MAX 5 ///< Max of RSP_IOMS

///RSP_TCDX
///Number of response credits to allocate in TCDX for responses.  Must not be 0 if either REQ_CS > 0 || REQ_IOMS > 0
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_TCDX_MIN 0 ///< Min of RSP_TCDX
#define IDSOPT_DF_DBG_VC8_TRACING_RSP_TCDX_MAX 5 ///< Max of RSP_TCDX

///Reduce credits - request
///Reduce request credits
typedef enum {
  IDSOPT_DF_DBG_REDUCE_CREDITS_REQ_REDUCECREDITS = 0,///<Reduce credits
  IDSOPT_DF_DBG_REDUCE_CREDITS_REQ_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_REDUCE_CREDITS_REQ;

///Reduce credits - probe
///Reduce probe credits
typedef enum {
  IDSOPT_DF_DBG_REDUCE_CREDITS_PRB_REDUCECREDITS = 0,///<Reduce credits
  IDSOPT_DF_DBG_REDUCE_CREDITS_PRB_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_REDUCE_CREDITS_PRB;

///Reduce credits - response
///Reduce response credits
typedef enum {
  IDSOPT_DF_DBG_REDUCE_CREDITS_RSP_REDUCECREDITS = 0,///<Reduce credits
  IDSOPT_DF_DBG_REDUCE_CREDITS_RSP_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_REDUCE_CREDITS_RSP;

///Disable load-step controls
///Sets DF::LoadStepHystCtl to all zero when DISABLE is selected. Use GRA to force a specific value into LoadStepHystCtl.
typedef enum {
  IDSOPT_DF_DBG_LOAD_STEP_CTRL_DIS_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_LOAD_STEP_CTRL_DIS_AUTO = 1,///<Auto
} IDSOPT_DF_DBG_LOAD_STEP_CTRL_DIS;

///DBGU_DF trace to DRAM
///Control DBGU DF tracing to DRAM
typedef enum {
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DBGU_DF_TRC_TO_DRAM;

///DF TCB IOMS trace to DRAM
///Control DF TCB IOMS trace to DRAM.
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOMS_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOMS_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOMS_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOMS_TRC_TO_DRAM;

///DF TCB IOCS0 trace to DRAM
///Control DF TCB IOCS0 trace to DRAM
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOCS0_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOCS0_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOCS0_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOCS0_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOCS0_TRC_TO_DRAM;

///DF TCB IOCS1 trace to DRAM
///Control DF TCB IOCS1 trace to DRAM
typedef enum {
  IDSOPT_DF_DBG_DF_TCB_IOCS1_TRC_TO_DRAM_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_DF_TCB_IOCS1_TRC_TO_DRAM_16MB = 1,///<16 MB
  IDSOPT_DF_DBG_DF_TCB_IOCS1_TRC_TO_DRAM_64MB = 2,///<64 MB
  IDSOPT_DF_DBG_DF_TCB_IOCS1_TRC_TO_DRAM_256MB = 3,///<256 MB
} IDSOPT_DF_DBG_DF_TCB_IOCS1_TRC_TO_DRAM;

///DF C-state control
///Enable / disable DF C-states (DF::CstateControl[DfCstateDisable])
typedef enum {
  IDSOPT_DF_DBG_CSTATE_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CSTATE_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CSTATE_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CSTATE_CTRL;

///Mask DF WDT errors from causing MCA
///This keeps the WDT enabled and will show up in scans, but won't let them cause a MCA.\n\nAUTO/Disabled (unmasked) doesn't touch the HWA errors.\nEnabled (masked) will set the following bits:\n  - DF::HardwareAssertMaskLow[4] in all CCM instances\n  - DF::HardwareAssertMaskLow[5] in all CCM instances\n  - DF::HardwareAssertMaskHigh[3] in all IOM instances
typedef enum {
  IDSOPT_DF_DBG_CSTATE_CTRL_MASK_WDT_FROM_CAUSING_MCA_ENABLED = 0,///<Enabled
  IDSOPT_DF_DBG_CSTATE_CTRL_MASK_WDT_FROM_CAUSING_MCA_DISABLED = 1,///<Disabled
  IDSOPT_DF_DBG_CSTATE_CTRL_MASK_WDT_FROM_CAUSING_MCA_AUTO = 0xF,///<Auto
} IDSOPT_DF_DBG_CSTATE_CTRL_MASK_WDT_FROM_CAUSING_MCA;

///CPU Masters receive probe responses
typedef enum {
  IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP_ENABLE = 1,///<Enable
  IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CPU_MSTR_RCV_PRB_RSP;

///I/O Masters receive probe responses
typedef enum {
  IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP_DISABLE = 0,///<Disable
  IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP_ENABLE = 1,///<Enable
  IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_IO_MSTR_RCV_PRB_RSP;

///Enforce supported frequency
///If this option is disable, and the target board does not support a certain VDDIO, then picking up a specific VDDIO through the CMOS option menu is required.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_ENFORCE_FREQ_DDR4;

///DRAM Timing User Controls
///DRAM Timing User Controls
typedef enum {
  IDSOPT_DBG_MEM_TIMING_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_CTL_DDR4;

///UclkDiv1M0
///UclkDiv1 option, relative to FCLK.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M0_DDR4;

///UclkDiv1M1
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M1_DDR4;

///UclkDiv1M2
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M2_DDR4;

///UclkDiv1M3
typedef enum {
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MEM_TIMING_UCLK_DIV1_M3_DDR4;

///Trtp
///Specifies the read CAS# to precharge time.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_5CLK = 0x5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_6CLK = 0x6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_7CLK = 0x7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRTP_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_DBG_MEM_TIMING_TRTP_DDR4;

///TrrdL
///Specify the row-to-row delay.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRRD_L_DDR4;

///TrrdS
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4_0CHCLK = 0xC,///<0Ch Clk
} IDSOPT_DBG_MEM_TIMING_TRRD_S_DDR4;

///Trc Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRC_CTL_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRC_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TRC_CTL_DDR4;

///Trc
///Specify the RAS# active to RAS# active time.
#define IDSOPT_DBG_MEM_TIMING_TRC_DDR4_MIN 29 ///< Min of Trc
#define IDSOPT_DBG_MEM_TIMING_TRC_DDR4_MAX 135 ///< Max of Trc

///Trdwr
///This sets the tWRTTO time.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1DHCLK = 0x1D,///<1Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1EHCLK = 0x1E,///<1Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4_1FHCLK = 0x1F,///<1Fh Clk
} IDSOPT_DBG_MEM_TIMING_TRDWR_DDR4;

///Twrrd
///Specify the write to read delay when accessing different DIMMs.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0CH = 0xC,///<0Ch
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0DH = 0xD,///<0Dh
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0EH = 0xE,///<0Eh
  IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4_0FH = 0xF,///<0Fh
} IDSOPT_DBG_MEM_TIMING_TWRRD_DDR4;

///TwtrL
///Specify the write to read delay when accessing the same DIMM.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4_2CLK = 2,///<2 Clk
} IDSOPT_DBG_MEM_TIMING_TWTR_L_DDR4;

///TwtrS
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4_0EHCLK = 0xE,///<0Eh Clk
} IDSOPT_DBG_MEM_TIMING_TWTR_S_DDR4;

///Tcwl
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_DBG_MEM_TIMING_TCWL_DDR4_16HCLK = 0x16,///<16h Clk
} IDSOPT_DBG_MEM_TIMING_TCWL_DDR4;

///TwrwrSc
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TWRWR_SC_DDR4;

///TwrwrSd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TWRWR_SD_DDR4;

///TwrwrDd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TWRWR_DD_DDR4;

///TrdrdSc
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRDRD_SC_DDR4;

///TrdrdSd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TRDRD_SD_DDR4;

///TrdrdDd
///write to write timing same DIMM same chip select.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_2CLK = 2,///<2 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_1CLK = 1,///<1 Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4_0FHCLK = 0xF,///<0Fh Clk
} IDSOPT_DBG_MEM_TIMING_TRDRD_DD_DDR4;

///Tref Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TREF_CTL_DDR4_MANUAL = 0x1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TREF_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TREF_CTL_DDR4;

///Tref
///Specify the tRef time.
#define IDSOPT_DBG_MEM_TIMING_TREF_DDR4_MIN 0 ///< Min of Tref
#define IDSOPT_DBG_MEM_TIMING_TREF_DDR4_MAX 0xffff ///< Max of Tref

///TrwtWB
///Specify the Trwtwb time.
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_3CLK = 3,///<3 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_4CLK = 4,///<4 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_5CLK = 5,///<5 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_6CLK = 6,///<6 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_7CLK = 7,///<7 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_8CLK = 8,///<8 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_9CLK = 9,///<9 Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0AHCLK = 0xA,///<0Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0BHCLK = 0xB,///<0Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0CHCLK = 0xC,///<0Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0DHCLK = 0xD,///<0Dh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0EHCLK = 0xE,///<0Eh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_0FHCLK = 0xF,///<0Fh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_10HCLK = 0x10,///<10h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_11HCLK = 0x11,///<11h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_12HCLK = 0x12,///<12h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_13HCLK = 0x13,///<13h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_14HCLK = 0x14,///<14h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_15HCLK = 0x15,///<15h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_16HCLK = 0x16,///<16h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_17HCLK = 0x17,///<17h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_19HCLK = 0x19,///<19h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_18HCLK = 0x18,///<18h Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_1AHCLK = 0x1A,///<1Ah Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_1BHCLK = 0x1B,///<1Bh Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_1CHCLK = 0x1C,///<1Ch Clk
  IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRWT_WB_DDR4;

///Trfc0 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRFC0_CTL_DDR4_MANUAL = 0x1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TRFC0_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRFC0_CTL_DDR4;

///Trfc0
///Specify the Trfcx time. D18F2x2A0_[10:0]
#define IDSOPT_DBG_MEM_TIMING_TRFC0_DDR4_MIN 0x1 ///< Min of Trfc0
#define IDSOPT_DBG_MEM_TIMING_TRFC0_DDR4_MAX 0x7ff ///< Max of Trfc0

///Trfc1 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRFC1_CTL_DDR4_MANUAL = 0x1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TRFC1_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TRFC1_CTL_DDR4;

///Trfc1
///Specify the Trfcx time. D18F2x2A0_[26:16]
#define IDSOPT_DBG_MEM_TIMING_TRFC1_DDR4_MIN 0x1 ///< Min of Trfc1
#define IDSOPT_DBG_MEM_TIMING_TRFC1_DDR4_MAX 0x7ff ///< Max of Trfc1

///Tcksrx Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TCKSRX_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TCKSRX_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TCKSRX_CTL_DDR4;

///Tcksrx
#define IDSOPT_DBG_MEM_TIMING_TCKSRX_DDR4_MIN 0 ///< Min of Tcksrx
#define IDSOPT_DBG_MEM_TIMING_TCKSRX_DDR4_MAX 0x3fff ///< Max of Tcksrx

///Tcksre Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TCKSRE_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TCKSRE_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TCKSRE_CTL_DDR4;

///Tcksre
#define IDSOPT_DBG_MEM_TIMING_TCKSRE_DDR4_MIN 0 ///< Min of Tcksre
#define IDSOPT_DBG_MEM_TIMING_TCKSRE_DDR4_MAX 0xff ///< Max of Tcksre

///Tpd Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TPD_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_TPD_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_TPD_CTL_DDR4;

///Tpd
#define IDSOPT_DBG_MEM_TIMING_TPD_DDR4_MIN 0x1 ///< Min of Tpd
#define IDSOPT_DBG_MEM_TIMING_TPD_DDR4_MAX 0xf ///< Max of Tpd

///Trddata_en Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TRDDATAEN_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TRDDATAEN_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TRDDATAEN_CTL_DDR4;

///Trddata_en
#define IDSOPT_DBG_MEM_TIMING_TRDDATAEN_DDR4_MIN 0 ///< Min of Trddata_en
#define IDSOPT_DBG_MEM_TIMING_TRDDATAEN_DDR4_MAX 0x7f ///< Max of Trddata_en

///Tphy_wrlat Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_CTL_DDR4_AUTO = 0,///<Auto
  IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_CTL_DDR4;

///Tphy_wrlat
#define IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_DDR4_MIN 0 ///< Min of Tphy_wrlat
#define IDSOPT_DBG_MEM_TIMING_TPHYWRLAT_DDR4_MAX 0x1f ///< Max of Tphy_wrlat

///Tphy_wrdata Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_CTL_DDR4;

///Tphy_wrdata
#define IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_DDR4_MIN 0 ///< Min of Tphy_wrdata
#define IDSOPT_DBG_MEM_TIMING_TPHYWRDATA_DDR4_MAX 0x7 ///< Max of Tphy_wrdata

///WrOdtOnDur
typedef enum {
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_WR_ODT_ON_DUR_DDR4;

///WrOdtTrnOnDly
typedef enum {
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_1 = 1,///<1
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_2 = 2,///<2
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_WR_ODT_TRN_ON_DLY_DDR4;

///RdOdtOnDur
typedef enum {
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_RD_ODT_ON_DUR_DDR4;

///RdOdtTrnOnDly
typedef enum {
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_1 = 1,///<1
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_2 = 2,///<2
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_3 = 3,///<3
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_4 = 4,///<4
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_5 = 5,///<5
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_6 = 6,///<6
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_7 = 7,///<7
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_8 = 8,///<8
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_9 = 9,///<9
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XA = 0xA,///<0xA
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XB = 0xB,///<0xB
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XC = 0xC,///<0xC
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XD = 0xD,///<0xD
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XE = 0xE,///<0xE
  IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4_0XF = 0xF,///<0xF
} IDSOPT_DBG_MEM_TIMING_RD_ODT_TRN_ON_DLY_DDR4;

///POdtStartDelayDqs Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_CTL_DDR4;

///POdtStartDelayDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_DDR4_MIN 0 ///< Min of POdtStartDelayDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQS_DDR4_MAX 3 ///< Max of POdtStartDelayDqs

///POdtStartDelayDq Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_CTL_DDR4;

///POdtStartDelayDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_DDR4_MIN 0 ///< Min of POdtStartDelayDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_START_DELAY_DQ_DDR4_MAX 0xf ///< Max of POdtStartDelayDq

///POdtTailWidthDqs Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_CTL_DDR4;

///POdtTailWidthDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_DDR4_MIN 0 ///< Min of POdtTailWidthDqs
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQS_DDR4_MAX 3 ///< Max of POdtTailWidthDqs

///POdtTailWidthDq Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_CTL_DDR4;

///POdtTailWidthDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_DDR4_MIN 0 ///< Min of POdtTailWidthDq
#define IDSOPT_DBG_MEM_TIMING_P_ODT_TAIL_WIDTH_DQ_DDR4_MAX 0xf ///< Max of POdtTailWidthDq

///Address Command Tristate Enable
///1=Tristate the address, command, and bank buses when a Deselect command is issued.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4_DISABLED = 1,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ADDR_CMD_TRI_EN_DDR4;

///Cmd2T
///Select between 1T and 2T mode on ADDR/CMD
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4_1T = 0,///<1T
  IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4_2T = 1,///<2T
  IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER2_T_MODE_DDR4;

///On DIMM Temperature Sensor Enable
///Enables the monitoring of the EVENT_L pin and indicates whether the on DIMM temperature sensors of the DIMMs on a channel are enabled.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ON_DIMM_TEMP_SENSOR_EN_DDR4;

///CmdThrottleMode Control
///Control command throttle mode.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_CTL_DDR4;

///CmdThrottleMode
///Control command throttle mode.
#define IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_DDR4_MIN 8 ///< Min of CmdThrottleMode
#define IDSOPT_DBG_MEM_CTRLLER_CMD_THROTTLE_MODE_DDR4_MAX 255 ///< Max of CmdThrottleMode

///Write CRC Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_WR_CRC_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_WR_CRC_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_WR_CRC_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_WR_CRC_EN_DDR4;

///Gear Down Mode
typedef enum {
  IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_GEAR_DOWN_MODE_DDR4;

///DRAM Hardware History Mechanism
///Disable DRAM Hardware History Mechanism: UMC_CH::EccCtrl[EccHardwareHistoryEn]. Default should be to set this to 1 if EccCtrl[EccSymbolSize]==x8
typedef enum {
  IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4_DISABLE = 16,///<Disable
  IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_HW_HISTORY_MECH_DDR4;

///DRAM Parity
typedef enum {
  IDSOPT_DBG_MEM_DRAM_PARITY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DRAM_PARITY_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_DRAM_PARITY_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_DRAM_PARITY_DDR4;

///RCD Parity
typedef enum {
  IDSOPT_DBG_MEM_RCD_PARITY_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_RCD_PARITY_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_RCD_PARITY_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_RCD_PARITY_DDR4;

///DBI
typedef enum {
  IDSOPT_DBG_MEM_DBI_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DBI_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_DBI_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_DBI_DDR4;

///AddrTweakEn Control
/// SMNx00050144 [Data Control] (DataCtrl)31:16 AddrTweakEn. Read-write. Reset: 0. Per key field that controls if encryption algorithm uses the physical address or not. Simple AES versus AES+Locality
typedef enum {
  IDSOPT_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_ADDR_TWEAK_EN_CTRL_DDR4;

///AddrTweakEn
#define IDSOPT_DBG_MEM_ADDR_TWEAK_EN_DDR4_MIN 0 ///< Min of AddrTweakEn
#define IDSOPT_DBG_MEM_ADDR_TWEAK_EN_DDR4_MAX 0xffff ///< Max of AddrTweakEn

///Data Encryption
///8 DataEncrEn. Read-write. Reset: 0. 0=Disable. 1=Enable. Enables data encryption. -  SMNx00050144 [Data Control] (DataCtrl) Bit 8
typedef enum {
  IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_DATA_ENCRYPTION_DDR4;

///Force Encryption
/// SMNx00050144 [Data Control] (DataCtrl) Bit 11 11 ForceEncrEn. Read-write. Reset: 0. 0=Disable. 1=Enable. Force region 0 data encryption for all requests.
typedef enum {
  IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_FORCE_ENCRYPTION_DDR4;

///UMC Key 0
typedef enum {
  IDSOPT_DBG_MEM_UMC_KEY0_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_UMC_KEY0_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_UMC_KEY0_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_UMC_KEY0_DDR4;

///DRAM Fine Granularity Refresh
typedef enum {
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_FIXED1X = 0,///<Fixed 1X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_FIXED2X = 1,///<Fixed 2X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_FIXED4X = 2,///<Fixed 4X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_OTF2X = 5,///<OTF 2X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_OTF4X = 6,///<OTF 4X
  IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_FINE_GRAN_REF_DDR4;

///DRAM Temperature Controlled Refresh Mode
typedef enum {
  IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_TEMP_CTRL_REF_MODE_DDR4;

///Data Mask
typedef enum {
  IDSOPT_DBG_MEM_DATA_MASK_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DATA_MASK_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_DATA_MASK_DDR4_DISABLED = 0,///<Disabled`
} IDSOPT_DBG_MEM_DATA_MASK_DDR4;

///RdPreamble Critical Speed
typedef enum {
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_AUTO = 0xFFFF,///<Auto
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1600 = 800,///<DDR1600
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1866 = 933,///<DDR1866
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2133 = 1067,///<DDR2133
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2400 = 1200,///<DDR2400
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2667 = 1333,///<DDR2667
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2933 = 1467,///<DDR2933
  IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4_DDR3200 = 1600,///<DDR3200
} IDSOPT_DBG_MEM_RD_PREAMBLE_CRITICAL_SPEED_DDR4;

///RdPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_RD_PREAMBLE_MSTATE_BITMAP_DDR4_MIN 0 ///< Min of RdPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_RD_PREAMBLE_MSTATE_BITMAP_DDR4_MAX 0xf ///< Max of RdPreamble M-state Bitmap

///WrPreamble Critical Speed
typedef enum {
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_AUTO = 0xFFFF,///<Auto
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1600 = 800,///<DDR1600
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR1866 = 933,///<DDR1866
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2133 = 1067,///<DDR2133
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2400 = 1200,///<DDR2400
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2667 = 1333,///<DDR2667
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR2933 = 1467,///<DDR2933
  IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4_DDR3200 = 1600,///<DDR3200
} IDSOPT_DBG_MEM_WR_PREAMBLE_CRITICAL_SPEED_DDR4;

///WrPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_WR_PREAMBLE_MSTATE_BITMAP_DDR4_MIN 0 ///< Min of WrPreamble M-state Bitmap
#define IDSOPT_DBG_MEM_WR_PREAMBLE_MSTATE_BITMAP_DDR4_MAX 0xf ///< Max of WrPreamble M-state Bitmap

///Memory Context Restore
///Configure the memory context restore mode. When enabled, DRAM re-retraining is avoided when possible and the POST latency is minimized.
typedef enum {
  IDSOPT_DBG_MEM_CONTEXT_RESTORE_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CONTEXT_RESTORE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CONTEXT_RESTORE_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_CONTEXT_RESTORE;

///ProcOdtAlwaysOn
typedef enum {
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4_1 = 1,///<1
} IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_ON_DDR4;

///ProcOdtAlwaysOff
typedef enum {
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4_1 = 1,///<1
} IDSOPT_DBG_MEM_PROC_ODT_ALWAYS_OFF_DDR4;

///Power Down Enable
///Enable or disable DDR power down mode, D18F2x94_dct[1:0][15]
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PWR_DN_EN_DDR4;

///Power Down Mode
///Set the DDR power down mode
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4_CHANNEL = 0,///<Channel
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4_CHIPSELECT = 1,///<Chip Select
  IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PWR_DN_MO_DDR4;

///Power Down Delay Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PD_DLY_CTL_DDR4;

///Power Down Delay
#define IDSOPT_DBG_MEM_CTRLLER_PD_DLY_DDR4_MIN 0 ///< Min of Power Down Delay
#define IDSOPT_DBG_MEM_CTRLLER_PD_DLY_DDR4_MAX 0xff ///< Max of Power Down Delay

///Aggressive Power Down Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_AGGRESSIVE_PWR_DOWN_EN_DDR4;

///Aggressive Power Down Delay Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_CTL_DDR4;

///Aggressive Power Down Delay
///Specifies a hysteresis count from the last DRAM activity for the DCT to close pages prior to precharge power down.
#define IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_DDR4_MIN 0x1 ///< Min of Aggressive Power Down Delay
#define IDSOPT_DBG_MEM_CTRLLER_AGGRE_PD_DLY_DDR4_MAX 0x3f ///< Max of Aggressive Power Down Delay

///Phy Power Saving
///Enable or disable DRAM Phy power savings.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_CTRLLER_PHY_POWER_SAVING_DDR4;

///Power Down Phy Power Save Disable
///1= Disable phy clock gating during precharge power down. 0=Enable phy clock gating during precharge power down to save power.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4_0 = 0,///<0
  IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4_1 = 1,///<1
  IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PD_PHY_POWER_SAVE_DIS_DDR4;

///All Memory Clks Enable
///This allows selection of all memory clocks enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ALL_MEM_CLKS_DDR4;

///All CKE Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ALL_CKE_DDR4;

///All CS Enable
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_ALL_CS_DDR4;

///DRAM Address Command Parity Retry
///UMC_CH::RecCtrl[RecEn][0] and UMC_CH::RecCtrl[MaxParRply].
typedef enum {
  IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4;

///Max Parity Error Replay
///Value in hex, 1, 2 or 3 is invalid.
#define IDSOPT_DBG_MEM_ADDR_CMD_PARITY_ERROR_MAX_REPLAY_DDR4_MIN 0 ///< Min of Max Parity Error Replay
#define IDSOPT_DBG_MEM_ADDR_CMD_PARITY_ERROR_MAX_REPLAY_DDR4_MAX 0x3f ///< Max of Max Parity Error Replay

///DRAM Write CRC Enable and Retry Limit
///UMC_CH::RecCtrl[RecEn][1] and UMC_CH::RecCtrl[MaxCrcRply].
typedef enum {
  IDSOPT_DBG_MEM_WRITE_CRC_RETRY_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_WRITE_CRC_RETRY_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_WRITE_CRC_RETRY_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_WRITE_CRC_RETRY_DDR4;

///Max Write CRC Error Replay
///Value in hex, 1, 2 or 3 is invalid.
#define IDSOPT_DBG_MEM_WRITE_CRC_ERROR_MAX_REPLAY_DDR4_MIN 0 ///< Min of Max Write CRC Error Replay
#define IDSOPT_DBG_MEM_WRITE_CRC_ERROR_MAX_REPLAY_DDR4_MAX 0x3f ///< Max of Max Write CRC Error Replay

///Inject TX Command Parity Errors
/// DF is requesting a UMC CBS option for injecting TX command parity errors as this will generate RETRANSMIT commands. The following webpage describes the recipe: http://twiki.amd.com/twiki/bin/view/DFArch/UmcRetransmitRecipe
typedef enum {
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4;

///Post Package Repair Enable
///Use this option to enable / disable Post package repair. Auto will set post package repair to disable.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_EN_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_EN_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_EN_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_EN_DDR4;

///Post Package Repair All Banks
///Use this option to enable / disable Post package repair on all banks. Auto will set post package repair on all banks to disable.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_BANKS_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_BANKS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_BANKS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_BANKS_DDR4;

///Post Package Repair All Ranks
///Use this option to enable / disable Post package repair on all ranks. Auto will set post package repair on all ranks to disable.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_RANKS_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_RANKS_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_RANKS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_POST_PACKAGE_REPAIR_ALL_RANKS_DDR4;

///Data Bus Configuration User Controls
///Specify the mode for drive strength to Auto or Manual
typedef enum {
  IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4;

///Data Drive Strength
///Specifies the Data Drive Strength
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_480OHM = 1,///<480 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_240OHM = 2,///<240 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_160OHM = 3,///<160 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_120OHM = 6,///<120 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_96OHM = 7,///<96 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_80OHM = 0xA,///<80 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_68OHM = 0xB,///<68 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_60OHM = 0xE,///<60 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_533OHM = 0xF,///<53.3 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_48OHM = 0x1A,///<48 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_436OHM = 0x1B,///<43.6 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_40OHM = 0x1E,///<40 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_369OHM = 0x1F,///<36.9 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_343OHM = 0x3A,///<34.3 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_32OHM = 0x3B,///<32 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_30OHM = 0x3E,///<30 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_282OHM = 0x3F,///<28.2 ohm
  IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4_HIZ = 0,///<HiZ
} IDSOPT_DBG_MEM_CTRLLER_DATA_DRV_STR_DDR4;

///RttNom
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RTT_NOMDISABLE = 0,///<Rtt_Nom Disable
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ4 = 1,///<RZQ/4
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ2 = 2,///<RZQ/2
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ6 = 3,///<RZQ/6
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ1 = 4,///<RZQ/1
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ5 = 5,///<RZQ/5
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ3 = 6,///<RZQ/3
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_RZQ7 = 7,///<RZQ/7
  IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_RTT_NOM_DDR4;

///RttWr
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_DYNAMICODTOFF = 0,///<Dynamic ODT Off
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_RZQ2 = 1,///<RZQ/2
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_RZQ1 = 2,///<RZQ/1
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_HIZ = 3,///<Hi-Z
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_RZQ3 = 4,///<RZQ/3
  IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_RTT_WR_DDR4;

///RttPark
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RTT_PARKDISABLE = 0,///<Rtt_PARK Disable
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ4 = 1,///<RZQ/4
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ2 = 2,///<RZQ/2
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ6 = 3,///<RZQ/6
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ1 = 4,///<RZQ/1
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ5 = 5,///<RZQ/5
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ3 = 6,///<RZQ/3
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_RZQ7 = 7,///<RZQ/7
  IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_RTT_PARK_DDR4;

///DRAM Output Driver Impedance
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4_RZQ7 = 0,///<RZQ/7
  IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4_RZQ5 = 1,///<RZQ/5
} IDSOPT_DBG_MEM_CTRLLER_DRAM_OUTPUT_DRV_DDR4;

///ARdPtrInitValMP0 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_CTL_DDR4;

///ARdPtrInitValMP0
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_DDR4_MIN 0 ///< Min of ARdPtrInitValMP0
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP0_DDR4_MAX 15 ///< Max of ARdPtrInitValMP0

///ARdPtrInitValMP1 Control
typedef enum {
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_CTL_DDR4;

///ARdPtrInitValMP1
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_DDR4_MIN 0 ///< Min of ARdPtrInitValMP1
#define IDSOPT_DBG_MEM_TIMING_A_RD_PTR_MP1_DDR4_MAX 127 ///< Max of ARdPtrInitValMP1

///DFI MRL Margin Control
typedef enum {
  IDSOPT_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_DFI_MRL_MARGIN_CTL_DDR4;

///DFI MRL Margin
#define IDSOPT_DBG_MEM_DFI_MRL_MARGIN_DDR4_MIN 0 ///< Min of DFI MRL Margin
#define IDSOPT_DBG_MEM_DFI_MRL_MARGIN_DDR4_MAX 31 ///< Max of DFI MRL Margin

///Per Rank Training
typedef enum {
  IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4_DISABLE = 0,///<Disable
} IDSOPT_DBG_MEM_PER_RANK_TIMING_DDR4;

///PMU Training Mode
///Use this option to select various PMU Training Mode. 1D Training is always performed for Reads and Writes. 2D may be performed for Reads, Writes or both.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DONLYTRAINING = 0,///<1D Only Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DAND2DREADTRAINING = 1,///<1D and 2D Read Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DAND2DWRITETRAINING = 2,///<1D and 2D Write Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_1DAND2DREADANDWRITETRAINING = 3,///<1D and 2D Read and Write Training
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_MODE_DDR4;

///MR6VrefDQ Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4_MANUAL = 1,///<Manual
  IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_CTRL_DDR4;

///MR6VrefDQ
#define IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_DDR4_MIN 0 ///< Min of MR6VrefDQ
#define IDSOPT_DBG_MEM_CTRLLER_MR6_VREF_DQ_DDR4_MAX 0x7f ///< Max of MR6VrefDQ

///DRAM Vref Range
typedef enum {
  IDSOPT_DBG_MEM_VREF_RANGE_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_VREF_RANGE_DDR4_RANGE1 = 1,///<Range 1
  IDSOPT_DBG_MEM_VREF_RANGE_DDR4_RANGE2 = 2,///<Range 2
} IDSOPT_DBG_MEM_VREF_RANGE_DDR4;

///DFE Read Training
///Perform 2D Read Training with DFE on.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_DFE_DDR4;

///FFE Write Training
///Perform 2D WriteTraining with FFE on.
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_PMU_TRAIN_FFE_DDR4;

///RxEnDly Override Op
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_PLUS = 0,///<Plus
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_MINUS = 1,///<Minus
  IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP_OVERRIDE = 2,///<Override
} IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_OP;

///RxEnDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_VALUE_MIN 0 ///< Min of RxEnDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_EN_DLY_OVERRIDE_VALUE_MAX 0xffff ///< Max of RxEnDly Override Value

///RxClkDly Override Op
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_OP_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_OP_PLUS = 0,///<Plus
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_OP_MINUS = 1,///<Minus
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_OP_OVERRIDE = 2,///<Override
} IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_OP;

///RxClkDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_VALUE_MIN 0 ///< Min of RxClkDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_VALUE_MAX 0xffff ///< Max of RxClkDly Override Value

///RxClkDly Override Turning Control
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_TURNING_CONTROL_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_TURNING_CONTROL_AFTER1D = 0,///<After 1D
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_TURNING_CONTROL_AFTER2D = 1,///<After 2D
} IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_TURNING_CONTROL;

///RxClkDly Override Instance Control
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_INSTANCE_CONTROL_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_INSTANCE_CONTROL_MANUAL = 0,///<Manual
} IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_INSTANCE_CONTROL;

///RxClkDly Override UMC Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_UMC_BIT_MASK_MIN 0 ///< Min of RxClkDly Override UMC Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_UMC_BIT_MASK_MAX 0x03 ///< Max of RxClkDly Override UMC Bitmask

///RxClkDly Override CS Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_CS_BIT_MASK_MIN 0 ///< Min of RxClkDly Override CS Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_CS_BIT_MASK_MAX 0xf ///< Max of RxClkDly Override CS Bitmask

///RxClkDly Override Byte Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_BYTE_BIT_MASK_MIN 0 ///< Min of RxClkDly Override Byte Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_BYTE_BIT_MASK_MAX 0x1ff ///< Max of RxClkDly Override Byte Bitmask

///RxClkDly Override Nibble Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_NIBBLE_BIT_MASK_MIN 0 ///< Min of RxClkDly Override Nibble Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_NIBBLE_BIT_MASK_MAX 0x3 ///< Max of RxClkDly Override Nibble Bitmask

///RxClkDly Override Pstate Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_PSTATE_BIT_MASK_MIN 0 ///< Min of RxClkDly Override Pstate Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_PSTATE_BIT_MASK_MAX 0xf ///< Max of RxClkDly Override Pstate Bitmask

///RxPBDly Override Op
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_PLUS = 0,///<Plus
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_MINUS = 1,///<Minus
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_OVERRIDE = 2,///<Override
} IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP;

///RxPBDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_VALUE_MIN 0 ///< Min of RxPBDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_VALUE_MAX 0xffff ///< Max of RxPBDly Override Value

///RxPBDly Override Turning Control
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_TURNING_CONTROL_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_TURNING_CONTROL_AFTER1D = 0,///<After 1D
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_TURNING_CONTROL_AFTER2D = 1,///<After 2D
} IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_TURNING_CONTROL;

///RxPBDly Override Instance Control
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_INSTANCE_CONTROL_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_INSTANCE_CONTROL_MANUAL = 0,///<Manual
} IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_INSTANCE_CONTROL;

///RxPBDly Override UMC Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_UMC_BIT_MASK_MIN 0 ///< Min of RxPBDly Override UMC Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_UMC_BIT_MASK_MAX 0x03 ///< Max of RxPBDly Override UMC Bitmask

///RxPBDly Override CS Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_CS_BIT_MASK_MIN 0 ///< Min of RxPBDly Override CS Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_CS_BIT_MASK_MAX 0xf ///< Max of RxPBDly Override CS Bitmask

///RxPBDly Override Byte Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_BYTE_BIT_MASK_MIN 0 ///< Min of RxPBDly Override Byte Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_BYTE_BIT_MASK_MAX 0x1ff ///< Max of RxPBDly Override Byte Bitmask

///RxPBDly Override DQ Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_DQ_BIT_MASK_MIN 0 ///< Min of RxPBDly Override DQ Bitmask
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_DQ_BIT_MASK_MAX 0x1ff ///< Max of RxPBDly Override DQ Bitmask

///Delay Weight2D Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_CTRL_DDR4;

///Delay Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_DDR4_MIN 0 ///< Min of Delay Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_DELAY_WEIGHT2_D_DDR4_MAX 255 ///< Max of Delay Weight2D

///Voltage Weight2D Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_CTRL_DDR4;

///Voltage Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_DDR4_MIN 0 ///< Min of Voltage Weight2D
#define IDSOPT_DBG_MEM_CTRLLER_PMU_VOLTAGE_WEIGHT2_D_DDR4_MAX 255 ///< Max of Voltage Weight2D

///Bits Per Point Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_CTRL_DDR4;

///Bits Per Point
#define IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_DDR4_MIN 0 ///< Min of Bits Per Point
#define IDSOPT_DBG_MEM_CTRLLER_PMU_BITS_PER_POINT_DDR4_MAX 255 ///< Max of Bits Per Point

///CPU Vref Training Seed Control
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_CTRL_DDR4;

///CPU Vref Training Seed
#define IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_DDR4_MIN 0 ///< Min of CPU Vref Training Seed
#define IDSOPT_DBG_MEM_CTRLLER_CPU_VREF_TRAINING_SEED_DDR4_MAX 0xff ///< Max of CPU Vref Training Seed

///Custom 1D Message Control 1
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL1;

///1D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET1_MIN 0 ///< Min of 1D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET1_MAX 0xffff ///< Max of 1D Message Offset 1

///1D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA1_MIN 0 ///< Min of 1D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA1_MAX 0xff ///< Max of 1D Message Data 1

///Custom 1D Message Control 2
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM1_D_MSG_CTRL2;

///1D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET2_MIN 0 ///< Min of 1D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_OFFSET2_MAX 0xffff ///< Max of 1D Message Offset 2

///1D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA2_MIN 0 ///< Min of 1D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER1_D_MSG_DATA2_MAX 0xff ///< Max of 1D Message Data 2

///Custom 2D message Control 1
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL1;

///2D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET1_MIN 0 ///< Min of 2D Message Offset 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET1_MAX 0xffff ///< Max of 2D Message Offset 1

///2D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA1_MIN 0 ///< Min of 2D Message Data 1
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA1_MAX 0xff ///< Max of 2D Message Data 1

///Custom 2D Message Control 2
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_CTRLLER_CUSTOM2_D_MSG_CTRL2;

///2D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET2_MIN 0 ///< Min of 2D Message Offset 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_OFFSET2_MAX 0xffff ///< Max of 2D Message Offset 2

///2D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA2_MIN 0 ///< Min of 2D Message Data 2
#define IDSOPT_DBG_MEM_CTRLLER2_D_MSG_DATA2_MAX 0xff ///< Max of 2D Message Data 2

///DBGU_NBIO trace to DRAM
///Control DBGU NBIO trac to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_TO_DRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_NBIO_TO_DRAM_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU_NBIO_TO_DRAM_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU_NBIO_TO_DRAM_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU_NBIO_TO_DRAM_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU_NBIO_TO_DRAM;

///DBGU_NBIO Port 80 Tracing
///Control DBGU_NBIO Diagnostic Port 80 Write Tracing
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TRACING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TRACING_ENABLED = 1,///<Enabled
} IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TRACING;

///DBGU_NBIO Port 80 Destination
///Selects the destination for Port 80 tracing
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_DESTINATION_TRACETODRB = 0,///<Trace to DRB
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_DESTINATION_TRACETODRAM = 1,///<Trace to DRAM
} IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_DESTINATION;

///DBGU_NBIO Port 80 Timestamps
typedef enum {
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP_ENABLED = 1,///<Enabled
} IDSOPT_DBG_GNB_DBGU_NBIO_PORT80_TIMESTAMP;

///DBGU_IO trace to DRAM
///Control DBGU IO trace to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU_IO_TO_DRAM;

///DBGU1 trace to DRAM
///Control DBGU1 trace to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU1_TO_DRAM;

///IVRS Options
///IVRS table
typedef enum {
  IDSOPT_DBG_GNB_DBGU_IVRS_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_DBGU_IVRS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_IVRS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBGU_IVRS;

///USB MSI-X CAP
///enable/disable USB MSI-X CAP
typedef enum {
  IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_NBIO_USB_MSIX_CAP_EN;

///Predefined Managed OC Setting
///Enable:\nPPT Limit = 197W\nTDC Limit = 114A\nEDC Limit = 168A
typedef enum {
  IDSOPT_DBG_NBIO_PREDEFINED_MOC_SETTING_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PREDEFINED_MOC_SETTING_EN_AUTO = 0xF,///<Auto
} IDSOPT_DBG_NBIO_PREDEFINED_MOC_SETTING_EN;

///XFR Enhancement Configuration
///XFR Enhancement Configuration:\n  Manual: manual setting of PPT, TDC and EDC
typedef enum {
  IDSOPT_DBG_NBIO_XF_R20_CTL_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_XF_R20_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_XF_R20_CTL;

///PPT Limit
///PPT Limit [W], Board Socket Power capability, adjustable up to motherboard programed PPT limit.
#define IDSOPT_DBG_NBIO_PPT_LIMIT_MIN 0 ///< Min of PPT Limit
#define IDSOPT_DBG_NBIO_PPT_LIMIT_MAX 0xffff ///< Max of PPT Limit

///TDC Limit
///TDC Limit [A], Board thermally constrained current delivery capability, adjustable up to motherboard programed board TDC limit.
#define IDSOPT_DBG_NBIO_TDC_LIMIT_MIN 0 ///< Min of TDC Limit
#define IDSOPT_DBG_NBIO_TDC_LIMIT_MAX 0xffff ///< Max of TDC Limit

///EDC Limit
///EDC Limit [A], Board electrically constrained current delivery capability, adjustable up to motherboard programed board EDC limit.
#define IDSOPT_DBG_NBIO_EDC_LIMIT_MIN 0 ///< Min of EDC Limit
#define IDSOPT_DBG_NBIO_EDC_LIMIT_MAX 0xffff ///< Max of EDC Limit

///Precision Boost Overdrive Scalar
///Manual = Part runs with a scalar of customized Value.
typedef enum {
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_CTL_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_NBIO_SMUFIT_LIMIT_CTL;

///customized Precision Boost Overdrive Scalar
///Precision Boost Overdrive increases the maximum boost voltage used (runs above parts specified maximum) and the amount of time spent at that voltage. The larger the value entered the larger the boost voltage used and the longer that voltage will be maintained.
typedef enum {
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_2X = 200,///<2X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_3X = 300,///<3X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_4X = 400,///<4X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_5X = 500,///<5X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_6X = 600,///<6X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_7X = 700,///<7X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_8X = 800,///<8X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_9X = 900,///<9X
  IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR_10X = 1000,///<10X
} IDSOPT_DBG_NBIO_SMUFIT_LIMIT_SCALAR;

///SATA PHY Tuning
typedef enum {
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_NONE = 0,///<None
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_SHORTERTRACELENGTH = 1,///<Shorter Trace Length
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_LONGERTRACELENGTH = 2,///<Longer Trace Length
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING;

///Maximum Read Request size
///the maximum Read Request size for the Function as a Requester
typedef enum {
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_128BYTES = 0,///<128 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_256BYTES = 1,///<256 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_512BYTES = 2,///<512 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_1024BYTES = 3,///<1024 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_2048BYTES = 4,///<2048 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_4096BYTES = 5,///<4096 bytes
  IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_GNB_DBG_MAX_READ_REQUEST_SIZE;

///LC_SCHEDULED_RXEQEVAL_INTERVAL
///Sets PCIE_LC_CNTL7.LC_SCHEDULED_RXEQEVAL_INTERVAL to the specified value.
typedef enum {
  IDSOPT_DBG_LC_SCHED_RX_EQ_EVAL_INT_0 = 0,///<0
  IDSOPT_DBG_LC_SCHED_RX_EQ_EVAL_INT_1 = 1,///<1
} IDSOPT_DBG_LC_SCHED_RX_EQ_EVAL_INT;

///LC_MULT_UPSTREAM_AUTO_SPD_CHNG_EN
///Defines the setting of this feature for all PCIe devices.  "Auto" uses the DXIO default setting of 0 for Gen1 and 1 for Gen2/3
typedef enum {
  IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO_DISABLED = 0,///<Disabled
  IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO_ENABLED = 1,///<Enabled
  IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO_AUTO = 0xF,///<Auto
} IDSOPT_DBG_LC_MULT_UPSTREAM_AUTO;

///Report EDB Errors
///Defines the setting of this feature for all PCIe devices.
typedef enum {
  IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS_AUTO = 0xF,///<Auto
  IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_REPORT_EDB_ERRORS;

///PCIe Controller 0
///Set PCIe lanes Topology
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_CONTROLLER0;

///Configuration number
///select Configuration number among:\nA - x16\nF - x8x8\nG - x8x4x4\nH - x8x4x2x2\nI - x8x4x2x1x1\nJ - x8x4x1x1x1x1\nK - x8x2x2x2x2\nL - x8x2x2x2x1x1\nM - x8x2x2x1x1x1x1\nN - x8x2x1x1x1x1x1x1\nP - x4x4x4x4\nQ - x4x4x4x2x2\nR - x4x4x4x2x1x1\nS - x4x4x4x1x1x1x1\nT - x4x4x2x2x2x2\nU - x4x4x2x2x2x1x1\nV - x4x4x2x2x1x1x1x1\nY - x4x2x2x2x2x2x2\nZ - x4x2x2x2x2x2x1x1\nF1- x2x2x2x2x2x2x2x2
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_A = 0,///<A
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_F = 1,///<F
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_G = 2,///<G
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_H = 3,///<H
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_I = 4,///<I
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_J = 5,///<J
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_K = 6,///<K
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_L = 7,///<L
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_M = 8,///<M
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_N = 9,///<N
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_P = 10,///<P
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_Q = 11,///<Q
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_R = 12,///<R
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_S = 13,///<S
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_T = 14,///<T
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_U = 15,///<U
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_V = 16,///<V
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_Y = 17,///<Y
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_Z = 18,///<Z
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION_F1 = 19,///<F1
} IDSOPT_DBG_GNB_PCIE_CONTROLLER0_CONFIGURATION;

///Reversal_all
///set reversal from wrapper, therefore the all 16 lanes and ports map are reversed
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_REVERSAL_ALL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_REVERSAL_ALL_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_REVERSAL_ALL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_CONTROLLER0_REVERSAL_ALL;

///Port_Order_En
///Port Order Enable
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_PORT_ORDER_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_PORT_ORDER_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER0_PORT_ORDER_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_CONTROLLER0_PORT_ORDER_EN;

/// Dev1Func1/Port_A Port Offset
/// Dev1Func1/Port_A Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F1_OFFSET_MIN 0 ///< Min of  Dev1Func1/Port_A Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F1_OFFSET_MAX 0xff ///< Max of  Dev1Func1/Port_A Port Offset

/// Dev1Func2/Port_B Port Offset
/// Dev1Func2/Port_B Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F2_OFFSET_MIN 0 ///< Min of  Dev1Func2/Port_B Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F2_OFFSET_MAX 0xff ///< Max of  Dev1Func2/Port_B Port Offset

/// Dev1Func3/Port_C Port Offset
/// Dev1Func3/Port_C Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F3_OFFSET_MIN 0 ///< Min of  Dev1Func3/Port_C Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F3_OFFSET_MAX 0xff ///< Max of  Dev1Func3/Port_C Port Offset

/// Dev1Func4/Port_D Port Offset
/// Dev1Func4/Port_D Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F4_OFFSET_MIN 0 ///< Min of  Dev1Func4/Port_D Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F4_OFFSET_MAX 0xff ///< Max of  Dev1Func4/Port_D Port Offset

/// Dev1Func5/Port_E Port Offset
/// Dev1Func5/Port_E Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F5_OFFSET_MIN 0 ///< Min of  Dev1Func5/Port_E Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F5_OFFSET_MAX 0xff ///< Max of  Dev1Func5/Port_E Port Offset

/// Dev1Func6/Port_F Port Offset
/// Dev1Func6/Port_F Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F6_OFFSET_MIN 0 ///< Min of  Dev1Func6/Port_F Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F6_OFFSET_MAX 0xff ///< Max of  Dev1Func6/Port_F Port Offset

/// Dev1Func7/Port_G Port Offset
/// Dev1Func7/Port_G Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F7_OFFSET_MIN 0 ///< Min of  Dev1Func7/Port_G Port Offset
#define IDSOPT_DBG_GNB_PCIE_D1_F7_OFFSET_MAX 0xff ///< Max of  Dev1Func7/Port_G Port Offset

/// Dev2Func1/Port_H Port Offset
/// Dev2Func1/Port_H Port Offset
#define IDSOPT_DBG_GNB_PCIE_D2_F1_OFFSET_MIN 0 ///< Min of  Dev2Func1/Port_H Port Offset
#define IDSOPT_DBG_GNB_PCIE_D2_F1_OFFSET_MAX 0xff ///< Max of  Dev2Func1/Port_H Port Offset

///PCIe Controller 1
///Set PCIe lanes Topology
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_CONTROLLER1;

///Configuration number
///select Configuration number among:\nA - x16\nF - x8x8\nG - x8x4x4\nH - x8x4x2x2\nI - x8x4x2x1x1\nJ - x8x4x1x1x1x1\nK - x8x2x2x2x2\nL - x8x2x2x2x1x1\nM - x8x2x2x1x1x1x1\nN - x8x2x1x1x1x1x1x1\nP - x4x4x4x4\nQ - x4x4x4x2x2\nR - x4x4x4x2x1x1\nS - x4x4x4x1x1x1x1\nT - x4x4x2x2x2x2\nU - x4x4x2x2x2x1x1\nV - x4x4x2x2x1x1x1x1\nY - x4x2x2x2x2x2x2\nZ - x4x2x2x2x2x2x1x1\nF1- x2x2x2x2x2x2x2x2
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_A = 0,///<A
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_F = 1,///<F
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_G = 2,///<G
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_H = 3,///<H
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_I = 4,///<I
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_J = 5,///<J
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_K = 6,///<K
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_L = 7,///<L
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_M = 8,///<M
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_N = 9,///<N
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_P = 10,///<P
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_Q = 11,///<Q
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_R = 12,///<R
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_S = 13,///<S
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_T = 14,///<T
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_U = 15,///<U
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_V = 16,///<V
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_Y = 17,///<Y
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_Z = 18,///<Z
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION_F1 = 19,///<F1
} IDSOPT_DBG_GNB_PCIE_CONTROLLER1_CONFIGURATION;

///Reversal_all
///set reversal from wrapper, therefore the all 16 lanes and ports map are reversed
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_REVERSAL_ALL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_REVERSAL_ALL_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_REVERSAL_ALL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_CONTROLLER1_REVERSAL_ALL;

///Port_Order_En
///Port Order Enable
typedef enum {
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_PORT_ORDER_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_PORT_ORDER_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PCIE_CONTROLLER1_PORT_ORDER_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_CONTROLLER1_PORT_ORDER_EN;

/// Dev3Func1/Port_A Port Offset
/// Dev3Func1/Port_A Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F1_OFFSET_MIN 0 ///< Min of  Dev3Func1/Port_A Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F1_OFFSET_MAX 0xff ///< Max of  Dev3Func1/Port_A Port Offset

/// Dev3Func2/Port_B Port Offset
/// Dev3Func2/Port_B Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F2_OFFSET_MIN 0 ///< Min of  Dev3Func2/Port_B Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F2_OFFSET_MAX 0xff ///< Max of  Dev3Func2/Port_B Port Offset

/// Dev3Func3/Port_C Port Offset
/// Dev3Func3/Port_C Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F3_OFFSET_MIN 0 ///< Min of  Dev3Func3/Port_C Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F3_OFFSET_MAX 0xff ///< Max of  Dev3Func3/Port_C Port Offset

/// Dev3Func4/Port_D Port Offset
/// Dev3Func4/Port_D Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F4_OFFSET_MIN 0 ///< Min of  Dev3Func4/Port_D Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F4_OFFSET_MAX 0xff ///< Max of  Dev3Func4/Port_D Port Offset

/// Dev3Func5/Port_E Port Offset
/// Dev3Func5/Port_E Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F5_OFFSET_MIN 0 ///< Min of  Dev3Func5/Port_E Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F5_OFFSET_MAX 0xff ///< Max of  Dev3Func5/Port_E Port Offset

/// Dev3Func6/Port_F Port Offset
/// Dev3Func6/Port_F Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F6_OFFSET_MIN 0 ///< Min of  Dev3Func6/Port_F Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F6_OFFSET_MAX 0xff ///< Max of  Dev3Func6/Port_F Port Offset

/// Dev3Func7/Port_G Port Offset
/// Dev3Func7/Port_G Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F7_OFFSET_MIN 0 ///< Min of  Dev3Func7/Port_G Port Offset
#define IDSOPT_DBG_GNB_PCIE_D3_F7_OFFSET_MAX 0xff ///< Max of  Dev3Func7/Port_G Port Offset

/// Dev4Func1/Port_H Port Offset
/// Dev4Func1/Port_H Port Offset
#define IDSOPT_DBG_GNB_PCIE_D4_F1_OFFSET_MIN 0 ///< Min of  Dev4Func1/Port_H Port Offset
#define IDSOPT_DBG_GNB_PCIE_D4_F1_OFFSET_MAX 0xff ///< Max of  Dev4Func1/Port_H Port Offset

///Port Training(Dev1Func1)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING;

///Hotplug Support(Dev1Func1)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG;

///Speed Mode(Dev1Func1)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE;

///Compliance Mode(Dev1Func1)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE;

///Link ASPM(Dev1Func1)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT2_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT2_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT2_L1_2;

///Poweroff Unused Phy Lanes and PLL
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT2_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT2_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT2_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT2_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT2_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT2_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT2_DYN_LANES_LINK_SWITCH;

///Slot Power Limit,W(Dev1Func1) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func1)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func1)
#define IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func1)

///L1 Immediate ACK(Dev1Func1)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK;

///TX De-emphasis(Dev1Func1)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS;

///TX Margin(Dev1Func1)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_TX_MARGIN;

///Scrambler control(Dev1Func1)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func1)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func1)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD;

///LC FOM TIME(Dev1Func1)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME;

///Port Reversal(Dev1Func1)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func1)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func1)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT2_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func1)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT2_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func1)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT2_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func1)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func1)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func1)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func1)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_SRNS;

///SRIS_EN(Dev1Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func1)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func1)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT2_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT2_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT2_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func1)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func1)
#define IDSOPT_DBG_GNB_PORT2_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func1)

///NP-DATA(Dev1Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func1)
#define IDSOPT_DBG_GNB_PORT2_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func1)

///P-HDR(Dev1Func1)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func1)
#define IDSOPT_DBG_GNB_PORT2_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func1)

///P-DATA(Dev1Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func1)
#define IDSOPT_DBG_GNB_PORT2_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func1)

///CPL-HDR(Dev1Func1)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT2_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func1)
#define IDSOPT_DBG_GNB_PORT2_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func1)

///CPL-DATA(Dev1Func1)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT2_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func1)
#define IDSOPT_DBG_GNB_PORT2_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func1)

///Gen1(Dev1Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F1_SPC_GEN1;

///Gen2(Dev1Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F1_SPC_GEN2;

///Gen3(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F1_SPC_GEN3;

///Port Training(Dev1Func2)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING;

///Hotplug Support(Dev1Func2)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG;

///Speed Mode(Dev1Func2)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE;

///Compliance Mode(Dev1Func2)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE;

///Link ASPM(Dev1Func2)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM;

///Slot Power Limit,W(Dev1Func2) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func2)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func2)
#define IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func2)

///L1 Immediate ACK(Dev1Func2)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK;

///TX De-emphasis(Dev1Func2)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS;

///TX Margin(Dev1Func2)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_TX_MARGIN;

///Scrambler control(Dev1Func2)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func2)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_PRESET = 3,///<Preset 
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func2)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev1Func2)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT3_PM_L1_SS;

///L1.1(Dev1Func2)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT3_L1_1;

///L1.2(Dev1Func2)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT3_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev1Func2)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT3_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev1Func2)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func2)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev1Func2)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME;

///Port Reversal(Dev1Func2)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func2)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func2)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT3_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func2)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT3_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func2)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT3_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func2)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func2)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func2)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func2)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_SRNS;

///SRIS_EN(Dev1Func2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func2)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func2)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT3_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT3_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT3_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func2)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func2)
#define IDSOPT_DBG_GNB_PORT3_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func2)

///NP-DATA(Dev1Func2)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func2)
#define IDSOPT_DBG_GNB_PORT3_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func2)

///P-HDR(Dev1Func2)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func2)
#define IDSOPT_DBG_GNB_PORT3_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func2)

///P-DATA(Dev1Func2)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func2)
#define IDSOPT_DBG_GNB_PORT3_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func2)

///CPL-HDR(Dev1Func2)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT3_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func2)
#define IDSOPT_DBG_GNB_PORT3_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func2)

///CPL-DATA(Dev1Func2)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT3_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func2)
#define IDSOPT_DBG_GNB_PORT3_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func2)

///Gen1(Dev1Func2)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F2_SPC_GEN1;

///Gen2(Dev1Func2)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F2_SPC_GEN2;

///Gen3(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F2_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F2_SPC_GEN3;

///Port Training(Dev1Func3)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING;

///Hotplug Support(Dev1Func3)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG;

///Speed Mode(Dev1Func3)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE;

///Compliance Mode(Dev1Func3)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE;

///Link ASPM(Dev1Func3)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM;

///Slot Power Limit,W(Dev1Func3) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func3)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func3)
#define IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func3)

///L1 Immediate ACK(Dev1Func3)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK;

///TX De-emphasis(Dev1Func3)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS;

///TX Margin(Dev1Func3)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_TX_MARGIN;

///Scrambler control(Dev1Func3)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func3)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev1Func3)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT4_PM_L1_SS;

///L1.1(Dev1Func3)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT4_L1_1;

///L1.2(Dev1Func3)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT4_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev1Func3)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT4_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev1Func3)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func3)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev1Func3)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME;

///Port Reversal(Dev1Func3)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT4_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func3)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT4_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func3)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT4_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func3)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func3)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func3)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func3)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_SRNS;

///SRIS_EN(Dev1Func3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func3)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func3)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT4_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT4_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT4_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func3)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func3)
#define IDSOPT_DBG_GNB_PORT4_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func3)

///NP-DATA(Dev1Func3)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func3)
#define IDSOPT_DBG_GNB_PORT4_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func3)

///P-HDR(Dev1Func3)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func3)
#define IDSOPT_DBG_GNB_PORT4_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func3)

///P-DATA(Dev1Func3)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func3)
#define IDSOPT_DBG_GNB_PORT4_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func3)

///CPL-HDR(Dev1Func3)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT4_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func3)
#define IDSOPT_DBG_GNB_PORT4_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func3)

///CPL-DATA(Dev1Func3)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT4_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func3)
#define IDSOPT_DBG_GNB_PORT4_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func3)

///Gen1(Dev1Func3)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D2_F3_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D2_F3_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D2_F3_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D2_F3_SPC_GEN1;

///Gen2(Dev1Func3)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F3_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F3_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F3_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F3_SPC_GEN2;

///Gen3(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_D1_F3_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F3_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F3_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F3_SPC_GEN3;

///Port Training(Dev1Func4)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT5_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_TRAINING;

///Hotplug Support(Dev1Func4)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG;

///Speed Mode(Dev1Func4)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE;

///Compliance Mode(Dev1Func4)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE;

///Link ASPM(Dev1Func4)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM;

///Slot Power Limit,W(Dev1Func4) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func4)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func4)
#define IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func4)

///L1 Immediate ACK(Dev1Func4)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK;

///TX De-emphasis(Dev1Func4)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS;

///TX Margin(Dev1Func4)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_TX_MARGIN;

///Scrambler control(Dev1Func4)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT5_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_PRESETSEARCH = 0x3,///<Preset Search
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func4)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev1Func4)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT5_PM_L1_SS;

///L1.1(Dev1Func4)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT5_L1_1;

///L1.2(Dev1Func4)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT5_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev1Func4)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT5_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev1Func4)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1_ENABLE = 16,///<Enable
} IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func4)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev1Func4)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME;

///Port Reversal(Dev1Func4)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT5_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func4)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT5_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func4)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT5_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func4)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func4)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func4)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func4)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_SRNS;

///SRIS_EN(Dev1Func4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func4)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func4)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT5_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT5_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT5_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func4)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func4)
#define IDSOPT_DBG_GNB_PORT5_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func4)

///NP-DATA(Dev1Func4)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func4)
#define IDSOPT_DBG_GNB_PORT5_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func4)

///P-HDR(Dev1Func4)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func4)
#define IDSOPT_DBG_GNB_PORT5_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func4)

///P-DATA(Dev1Func4)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func4)
#define IDSOPT_DBG_GNB_PORT5_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func4)

///CPL-HDR(Dev1Func4)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT5_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func4)
#define IDSOPT_DBG_GNB_PORT5_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func4)

///CPL-DATA(Dev1Func4)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT5_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func4)
#define IDSOPT_DBG_GNB_PORT5_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func4)

///Gen1(Dev1Func4)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F4_SPC_GEN1;

///Gen2(Dev1Func4)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F4_SPC_GEN2;

///Gen3(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F4_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F4_SPC_GEN3;

///Port Training(Dev1Func5)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING;

///Hotplug Support(Dev1Func5)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG;

///Speed Mode(Dev2Func5)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE;

///Compliance Mode(Dev1Func5)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE;

///Link ASPM(Dev1Func5)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM;

///Slot Power Limit,W(Dev1Func5) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func5)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func5)
#define IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func5)

///L1 Immediate ACK(Dev1Func5)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK;

///TX De-emphasis(Dev1Func5)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS;

///TX Margin(Dev1Func5)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_TX_MARGIN;

///Scrambler control(Dev1Func5)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func5)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func5)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev1Func5)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT6_PM_L1_SS;

///L1.1(Dev1Func5)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT6_L1_1;

///L1.2(Dev1Func5)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT6_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev1Func5)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT6_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev1Func5)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func5)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev1Func5)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME;

///Port Reversal(Dev1Func5)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func5)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func5)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT6_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func5)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT6_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func5)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT6_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func5)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func5)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func5)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func5)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_SRNS;

///SRIS_EN(Dev1Func5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func5)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func5)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT6_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT6_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT6_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func5)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func5)
#define IDSOPT_DBG_GNB_PORT6_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func5)

///NP-DATA(Dev1Func5)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func5)
#define IDSOPT_DBG_GNB_PORT6_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func5)

///P-HDR(Dev1Func5)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func5)
#define IDSOPT_DBG_GNB_PORT6_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func5)

///P-DATA(Dev1Func5)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func5)
#define IDSOPT_DBG_GNB_PORT6_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func5)

///CPL-HDR(Dev1Func5)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT6_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func5)
#define IDSOPT_DBG_GNB_PORT6_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func5)

///CPL-DATA(Dev1Func5)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT6_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func5)
#define IDSOPT_DBG_GNB_PORT6_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func5)

///Gen1(Dev1Func5)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F5_SPC_GEN1;

///Gen2(Dev1Func5)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F5_SPC_GEN2;

///Gen3(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F5_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F5_SPC_GEN3;

///Port Training(Dev1Func6)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING;

///Hotplug Support(Dev1Func6)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT7_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT7_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT7_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_HOTPLUG;

///Speed Mode(Dev1Func6)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT7_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT7_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT7_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT7_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_SPEED_MODE;

///Compliance Mode(Dev1Func6)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT7_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_COMPLIANCE_MODE;

///Link ASPM(Dev1Func6)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT7_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_LINK_ASPM;

///Slot Power Limit,W(Dev1Func6) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT7_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT7_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func6)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT7_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func6)
#define IDSOPT_DBG_GNB_PCIE_PORT7_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func6)

///L1 Immediate ACK(Dev1Func6)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT7_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_L1_IMM_ACK;

///TX De-emphasis(Dev1Func6)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_TX_DEEMPHASIS;

///TX Margin(Dev1Func6)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_TX_MARGIN;

///Scrambler control(Dev1Func6)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func6)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT7_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT7_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT7_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT7_EQUAL_SEARCH_MODE_PRESETSEARCH = 0x03,///<Preset Search
  IDSOPT_GNB_DBG_PORT7_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT7_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func6)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT7_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev1Func6)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT7_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT7_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT7_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT7_PM_L1_SS;

///L1.1(Dev1Func6)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT7_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT7_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT7_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT7_L1_1;

///L1.2(Dev1Func6)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT7_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT7_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT7_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT7_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev1Func6)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT7_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT7_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT7_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT7_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev1Func6)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT7_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT7_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT7_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT7_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func6)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT7_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT7_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT7_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT7_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT7_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT7_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev1Func6)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT7_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT7_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT7_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT7_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT7_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT7_LC_FOM_TIME;

///Port Reversal(Dev1Func6)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT7_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT7_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT7_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT7_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func6)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func6)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT7_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func6)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT7_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func6)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT7_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func6)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT7_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func6)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT7_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func6)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT7_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func6)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT7_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_SRIS_SRNS;

///SRIS_EN(Dev1Func6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT7_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT7_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT7_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT7_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT7_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func6)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT7_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func6)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT7_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT7_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT7_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func6)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT7_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func6)
#define IDSOPT_DBG_GNB_PORT7_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func6)

///NP-DATA(Dev1Func6)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT7_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func6)
#define IDSOPT_DBG_GNB_PORT7_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func6)

///P-HDR(Dev1Func6)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT7_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func6)
#define IDSOPT_DBG_GNB_PORT7_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func6)

///P-DATA(Dev1Func6)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT7_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func6)
#define IDSOPT_DBG_GNB_PORT7_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func6)

///CPL-HDR(Dev1Func6)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT7_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func6)
#define IDSOPT_DBG_GNB_PORT7_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func6)

///CPL-DATA(Dev1Func6)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT7_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func6)
#define IDSOPT_DBG_GNB_PORT7_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func6)

///Gen1(Dev1Func6)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F6_SPC_GEN1;

///Gen2(Dev1Func6)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F6_SPC_GEN2;

///Gen3(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F6_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F6_SPC_GEN3;

///Port Training(Dev1Func7)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT8_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT8_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_TRAINING;

///Hotplug Support(Dev1Func7)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT8_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT8_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT8_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_HOTPLUG;

///Speed Mode(Dev1Func7)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT8_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT8_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT8_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT8_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_SPEED_MODE;

///Compliance Mode(Dev1Func7)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT8_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT8_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_COMPLIANCE_MODE;

///Link ASPM(Dev1Func7)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT8_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT8_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_LINK_ASPM;

///Slot Power Limit,W(Dev1Func7) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT8_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT8_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev1Func7)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT8_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev1Func7)
#define IDSOPT_DBG_GNB_PCIE_PORT8_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev1Func7)

///L1 Immediate ACK(Dev1Func7)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT8_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT8_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_L1_IMM_ACK;

///TX De-emphasis(Dev1Func7)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_TX_DEEMPHASIS;

///TX Margin(Dev1Func7)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_TX_MARGIN;

///Scrambler control(Dev1Func7)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT8_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT8_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT8_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT8_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev1Func7)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT8_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT8_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT8_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT8_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT8_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT8_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev1Func7)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT8_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev1Func7)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT8_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT8_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT8_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT8_PM_L1_SS;

///L1.1(Dev1Func7)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT8_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT8_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT8_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT8_L1_1;

///L1.2(Dev1Func7)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT8_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT8_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT8_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT8_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev1Func7)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT8_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT8_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT8_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT8_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev1Func7)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT8_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT8_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT8_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT8_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func7)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT8_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT8_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT8_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT8_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT8_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT8_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev1Func7)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT8_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT8_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT8_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT8_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT8_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT8_LC_FOM_TIME;

///Port Reversal(Dev1Func7)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT8_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT8_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT8_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT8_PORT_REVERSAL;

///Downstream Tx Preset(Dev1Func7)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev1Func7)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT8_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev1Func7)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT8_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev1Func7)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT8_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev1Func7)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT8_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev1Func7)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT8_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev1Func7)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT8_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev1Func7)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT8_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_SRIS_SRNS;

///SRIS_EN(Dev1Func7)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT8_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev1Func7)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT8_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev1Func7)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev1Func7)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev1Func7)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT8_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT8_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT8_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev1Func7)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT8_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev1Func7)
#define IDSOPT_DBG_GNB_PORT8_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev1Func7)

///NP-DATA(Dev1Func7)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT8_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev1Func7)
#define IDSOPT_DBG_GNB_PORT8_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev1Func7)

///P-HDR(Dev1Func7)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT8_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev1Func7)
#define IDSOPT_DBG_GNB_PORT8_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev1Func7)

///P-DATA(Dev1Func7)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT8_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev1Func7)
#define IDSOPT_DBG_GNB_PORT8_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev1Func7)

///CPL-HDR(Dev1Func7)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT8_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev1Func7)
#define IDSOPT_DBG_GNB_PORT8_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev1Func7)

///CPL-DATA(Dev1Func7)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT8_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev1Func7)
#define IDSOPT_DBG_GNB_PORT8_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev1Func7)

///Gen1(Dev1Func7)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F7_SPC_GEN1;

///Gen2(Dev1Func7)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F7_SPC_GEN2;

///Gen3(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F7_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D1_F7_SPC_GEN3;

///Port Training(Dev2Func1)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT9_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT9_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_TRAINING;

///Hotplug Support(Dev2Func1)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT9_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT9_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT9_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_HOTPLUG;

///Speed Mode(Dev2Func1)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT9_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT9_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT9_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT9_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_SPEED_MODE;

///Compliance Mode(Dev2Func1)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT9_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT9_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_COMPLIANCE_MODE;

///Link ASPM(Dev2Func1)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT9_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT9_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_LINK_ASPM;

///Slot Power Limit,W(Dev2Func1) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT9_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT9_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev2Func1)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT9_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev2Func1)
#define IDSOPT_DBG_GNB_PCIE_PORT9_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev2Func1)

///L1 Immediate ACK(Dev2Func1)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT9_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT9_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_L1_IMM_ACK;

///TX De-emphasis(Dev2Func1)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_TX_DEEMPHASIS;

///TX Margin(Dev2Func1)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_TX_MARGIN;

///Scrambler control(Dev2Func1)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT9_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT9_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT9_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT9_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev2Func1)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT9_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT9_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT9_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 3,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT9_EQUAL_SEARCH_MODE_PRESETSEARCH = 2,///<Preset Search
  IDSOPT_GNB_DBG_PORT9_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT9_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev2Func1)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT9_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev2Func1)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT9_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT9_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT9_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT9_PM_L1_SS;

///L1.1(Dev2Func1)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT9_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT9_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT9_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT9_L1_1;

///L1.2(Dev2Func1)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT9_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT9_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT9_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT9_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev2Func1)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT9_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT9_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT9_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT9_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev2Func1)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT9_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT9_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT9_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT9_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev2Func1)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT9_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT9_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT9_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT9_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT9_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT9_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev2Func1)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT9_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT9_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT9_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT9_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT9_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT9_LC_FOM_TIME;

///Port Reversal(Dev2Func1)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT9_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT9_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT9_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT9_PORT_REVERSAL;

///Downstream Tx Preset(Dev2Func1)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev2Func1)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT9_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev2Func1)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT9_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev2Func1)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT9_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev2Func1)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT9_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev2Func1)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT9_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev2Func1)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT9_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev2Func1)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT9_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_SRIS_SRNS;

///SRIS_EN(Dev2Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT9_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev2Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT9_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev2Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT9_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT9_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT9_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev2Func1)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT9_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev2Func1)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT9_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT9_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT9_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev2Func1)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT9_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev2Func1)
#define IDSOPT_DBG_GNB_PORT9_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev2Func1)

///NP-DATA(Dev2Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT9_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev2Func1)
#define IDSOPT_DBG_GNB_PORT9_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev2Func1)

///P-HDR(Dev2Func1)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT9_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev2Func1)
#define IDSOPT_DBG_GNB_PORT9_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev2Func1)

///P-DATA(Dev2Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT9_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev2Func1)
#define IDSOPT_DBG_GNB_PORT9_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev2Func1)

///CPL-HDR(Dev2Func1)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT9_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev2Func1)
#define IDSOPT_DBG_GNB_PORT9_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev2Func1)

///CPL-DATA(Dev2Func1)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT9_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev2Func1)
#define IDSOPT_DBG_GNB_PORT9_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev2Func1)

///Gen1(Dev2Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D2_F1_SPC_GEN1;

///Gen2(Dev2Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D2_F1_SPC_GEN2;

///Gen3(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D2_F1_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D2_F1_SPC_GEN3;

///Port Training(Dev3Func1)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT10_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT10_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_TRAINING;

///Hotplug Support(Dev3Func1)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT10_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT10_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT10_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_HOTPLUG;

///Speed Mode(Dev3Func1)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_SPEED_MODE;

///Compliance Mode(Dev3Func1)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT10_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT10_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_COMPLIANCE_MODE;

///Link ASPM(Dev3Func1)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT10_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT10_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_LINK_ASPM;

///Slot Power Limit,W(Dev3Func1) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT10_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT10_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func1)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT10_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func1)
#define IDSOPT_DBG_GNB_PCIE_PORT10_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func1)

///L1 Immediate ACK(Dev3Func1)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT10_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT10_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_L1_IMM_ACK;

///TX De-emphasis(Dev3Func1)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_TX_DEEMPHASIS;

///TX Margin(Dev3Func1)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_TX_MARGIN;

///Scrambler control(Dev3Func1)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT10_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT10_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT10_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT10_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func1)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT10_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT10_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT10_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 3,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT10_EQUAL_SEARCH_MODE_PRESETSEARCH = 2,///<Preset Search
  IDSOPT_GNB_DBG_PORT10_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT10_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func1)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT10_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func1)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT10_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT10_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT10_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT10_PM_L1_SS;

///L1.1(Dev3Func1)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT10_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT10_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT10_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT10_L1_1;

///L1.2(Dev3Func1)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT10_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT10_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT10_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT10_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func1)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT10_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT10_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT10_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT10_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func1)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT10_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT10_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT10_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT10_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func1)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT10_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT10_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT10_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT10_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT10_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT10_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func1)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT10_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT10_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT10_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT10_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT10_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT10_LC_FOM_TIME;

///Port Reversal(Dev3Func1)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT10_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT10_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT10_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT10_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func1)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func1)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT10_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func1)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT10_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func1)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT10_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func1)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT10_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func1)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT10_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func1)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT10_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func1)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT10_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_SRIS_SRNS;

///SRIS_EN(Dev3Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT10_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT10_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT10_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT10_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT10_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func1)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT10_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func1)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT10_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT10_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT10_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func1)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT10_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func1)
#define IDSOPT_DBG_GNB_PORT10_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func1)

///NP-DATA(Dev3Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT10_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func1)
#define IDSOPT_DBG_GNB_PORT10_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func1)

///P-HDR(Dev3Func1)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT10_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func1)
#define IDSOPT_DBG_GNB_PORT10_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func1)

///P-DATA(Dev3Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT10_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func1)
#define IDSOPT_DBG_GNB_PORT10_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func1)

///CPL-HDR(Dev3Func1)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT10_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func1)
#define IDSOPT_DBG_GNB_PORT10_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func1)

///CPL-DATA(Dev3Func1)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT10_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func1)
#define IDSOPT_DBG_GNB_PORT10_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func1)

///Gen1(Dev3Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D3_F1_SPC_GEN1;

///Gen2(Dev3Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D3_F1_SPC_GEN2;

///Gen3(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D3_F1_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D3_F1_SPC_GEN3;

///Port Training(Dev3Func2)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT11_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT11_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_TRAINING;

///Hotplug Support(Dev3Func2)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT11_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT11_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT11_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_HOTPLUG;

///Speed Mode(Dev3Func2)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_SPEED_MODE;

///Compliance Mode(Dev3Func2)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT11_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT11_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_COMPLIANCE_MODE;

///Link ASPM(Dev3Func2)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT11_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT11_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_LINK_ASPM;

///Slot Power Limit,W(Dev3Func2) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT11_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT11_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func2)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT11_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func2)
#define IDSOPT_DBG_GNB_PCIE_PORT11_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func2)

///L1 Immediate ACK(Dev3Func2)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT11_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT11_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_L1_IMM_ACK;

///TX De-emphasis(Dev3Func2)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_TX_DEEMPHASIS;

///TX Margin(Dev3Func2)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_TX_MARGIN;

///Scrambler control(Dev3Func2)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT11_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT11_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT11_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT11_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func2)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT11_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT11_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT11_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT11_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT11_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT11_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func2)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT11_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func2)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT11_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT11_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT11_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT11_PM_L1_SS;

///L1.1(Dev3Func2)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT11_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT11_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT11_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT11_L1_1;

///L1.2(Dev3Func2)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT11_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT11_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT11_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT11_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func2)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT11_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT11_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT11_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT11_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func2)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT11_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT11_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT11_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT11_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func2)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT11_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT11_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT11_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT11_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT11_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT11_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func2)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT11_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT11_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT11_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT11_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT11_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT11_LC_FOM_TIME;

///Port Reversal(Dev3Func2)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT11_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT11_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT11_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT11_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func2)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func2)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT11_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func2)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT11_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func2)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT11_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func2)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT11_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func2)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT11_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func2)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT11_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func2)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT11_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_SRIS_SRNS;

///SRIS_EN(Dev3Func2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT11_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT11_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT11_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT11_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT11_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func2)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT11_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func2)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT11_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT11_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT11_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func2)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT11_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func2)
#define IDSOPT_DBG_GNB_PORT11_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func2)

///NP-DATA(Dev3Func2)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT11_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func2)
#define IDSOPT_DBG_GNB_PORT11_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func2)

///P-HDR(Dev3Func2)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT11_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func2)
#define IDSOPT_DBG_GNB_PORT11_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func2)

///P-DATA(Dev3Func2)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT11_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func2)
#define IDSOPT_DBG_GNB_PORT11_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func2)

///CPL-HDR(Dev3Func2)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT11_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func2)
#define IDSOPT_DBG_GNB_PORT11_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func2)

///CPL-DATA(Dev3Func2)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT11_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func2)
#define IDSOPT_DBG_GNB_PORT11_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func2)

///Gen1(Dev3Func2)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D3_F2_SPC_GEN1;

///Gen2(Dev3Func2)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D3_F2_SPC_GEN2;

///Gen3(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D3_F2_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_D3_F2_SPC_GEN3;

///Port Training(Dev3Func3)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT12_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT12_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_TRAINING;

///Hotplug Support(Dev3Func3)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT12_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT12_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT12_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_HOTPLUG;

///Speed Mode(Dev3Func3)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_SPEED_MODE;

///Compliance Mode(Dev3Func3)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT12_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT12_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_COMPLIANCE_MODE;

///Link ASPM(Dev3Func3)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT12_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT12_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_LINK_ASPM;

///Slot Power Limit,W(Dev3Func3) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT12_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT12_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func3)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT12_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func3)
#define IDSOPT_DBG_GNB_PCIE_PORT12_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func3)

///L1 Immediate ACK(Dev3Func3)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT12_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT12_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_L1_IMM_ACK;

///TX De-emphasis(Dev3Func3)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_TX_DEEMPHASIS;

///TX Margin(Dev3Func3)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_TX_MARGIN;

///Scrambler control(Dev3Func3)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT12_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT12_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT12_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT12_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT12_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT12_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT12_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT12_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT12_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT12_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func3)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT12_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func3)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT12_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT12_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT12_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT12_PM_L1_SS;

///L1.1(Dev3Func3)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT12_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT12_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT12_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT12_L1_1;

///L1.2(Dev3Func3)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT12_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT12_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT12_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT12_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func3)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT12_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT12_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT12_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT12_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func3)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT12_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT12_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT12_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT12_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func3)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT12_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT12_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT12_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT12_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT12_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT12_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func3)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT12_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT12_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT12_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT12_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT12_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT12_LC_FOM_TIME;

///Port Reversal(Dev3Func3)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT12_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT12_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT12_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT12_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func3)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func3)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT12_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func3)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT12_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func3)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT12_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func3)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT12_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func3)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT12_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func3)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT12_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func3)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT12_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_SRIS_SRNS;

///SRIS_EN(Dev3Func3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT12_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT12_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT12_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT12_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT12_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func3)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT12_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func3)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT12_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT12_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT12_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func3)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT12_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func3)
#define IDSOPT_DBG_GNB_PORT12_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func3)

///NP-DATA(Dev3Func3)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT12_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func3)
#define IDSOPT_DBG_GNB_PORT12_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func3)

///P-HDR(Dev3Func3)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT12_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func3)
#define IDSOPT_DBG_GNB_PORT12_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func3)

///P-DATA(Dev3Func3)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT12_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func3)
#define IDSOPT_DBG_GNB_PORT12_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func3)

///CPL-HDR(Dev3Func3)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT12_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func3)
#define IDSOPT_DBG_GNB_PORT12_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func3)

///CPL-DATA(Dev3Func3)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT12_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func3)
#define IDSOPT_DBG_GNB_PORT12_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func3)

///Gen1(Dev3Func3)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT12_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT12_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT12_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT12_SPC_GEN1;

///Gen2(Dev3Func3)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT12_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT12_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT12_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT12_SPC_GEN2;

///Gen3(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_PORT12_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT12_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT12_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PORT12_SPC_GEN3;

///Port Training(Dev3Func4)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT13_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT13_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_TRAINING;

///Hotplug Support(Dev3Func4)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT13_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT13_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT13_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_HOTPLUG;

///Speed Mode(Dev3Func4)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_SPEED_MODE;

///Compliance Mode(Dev3Func4)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT13_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT13_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_COMPLIANCE_MODE;

///Link ASPM(Dev3Func4)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT13_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT13_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_LINK_ASPM;

///Slot Power Limit,W(Dev3Func4) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT13_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT13_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func4)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT13_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func4)
#define IDSOPT_DBG_GNB_PCIE_PORT13_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func4)

///L1 Immediate ACK(Dev3Func4)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT13_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT13_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_L1_IMM_ACK;

///TX De-emphasis(Dev3Func4)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_TX_DEEMPHASIS;

///TX Margin(Dev3Func4)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_TX_MARGIN;

///Scrambler control(Dev3Func4)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT13_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT13_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT13_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT13_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT13_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT13_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT13_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT13_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT13_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT13_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func4)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT13_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func4)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT13_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT13_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT13_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT13_PM_L1_SS;

///L1.1(Dev3Func4)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT13_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT13_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT13_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT13_L1_1;

///L1.2(Dev3Func4)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT13_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT13_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT13_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT13_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func4)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT13_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT13_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT13_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT13_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func4)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT13_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT13_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT13_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT13_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func4)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT13_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT13_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT13_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT13_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT13_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT13_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func4)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT13_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT13_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT13_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT13_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT13_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT13_LC_FOM_TIME;

///Port Reversal(Dev3Func4)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT13_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT13_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT13_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT13_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func4)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func4)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT13_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func4)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT13_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func4)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT13_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func4)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT13_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func4)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT13_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func4)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT13_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func4)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT13_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_SRIS_SRNS;

///SRIS_EN(Dev3Func4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT13_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT13_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT13_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT13_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT13_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func4)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT13_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func4)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT13_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT13_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT13_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func4)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT13_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func4)
#define IDSOPT_DBG_GNB_PORT13_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func4)

///NP-DATA(Dev3Func4)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT13_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func4)
#define IDSOPT_DBG_GNB_PORT13_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func4)

///P-HDR(Dev3Func4)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT13_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func4)
#define IDSOPT_DBG_GNB_PORT13_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func4)

///P-DATA(Dev3Func4)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT13_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func4)
#define IDSOPT_DBG_GNB_PORT13_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func4)

///CPL-HDR(Dev3Func4)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT13_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func4)
#define IDSOPT_DBG_GNB_PORT13_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func4)

///CPL-DATA(Dev3Func4)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT13_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func4)
#define IDSOPT_DBG_GNB_PORT13_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func4)

///Gen1(Dev3Func4)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT13_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT13_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT13_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT13_SPC_GEN1;

///Gen2(Dev3Func4)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT13_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT13_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT13_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT13_SPC_GEN2;

///Gen3(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_PORT13_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT13_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT13_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PORT13_SPC_GEN3;

///Port Training(Dev3Func5)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT14_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT14_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_TRAINING;

///Hotplug Support(Dev3Func5)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT14_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT14_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT14_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_HOTPLUG;

///Speed Mode(Dev3Func5)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_SPEED_MODE;

///Compliance Mode(Dev3Func5)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT14_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT14_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_COMPLIANCE_MODE;

///Link ASPM(Dev3Func5)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT14_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT14_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_LINK_ASPM;

///Slot Power Limit,W(Dev3Func5) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT14_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT14_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func5)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT14_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func5)
#define IDSOPT_DBG_GNB_PCIE_PORT14_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func5)

///L1 Immediate ACK(Dev3Func5)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT14_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT14_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_L1_IMM_ACK;

///TX De-emphasis(Dev3Func5)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_TX_DEEMPHASIS;

///TX Margin(Dev3Func5)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_TX_MARGIN;

///Scrambler control(Dev3Func5)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT14_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT14_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT14_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT14_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func5)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT14_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT14_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT14_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT14_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT14_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT14_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func5)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT14_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func5)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT14_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT14_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT14_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT14_PM_L1_SS;

///L1.1(Dev3Func5)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT14_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT14_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT14_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT14_L1_1;

///L1.2(Dev3Func5)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT14_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT14_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT14_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT14_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func5)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT14_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT14_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT14_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT14_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func5)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT14_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT14_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT14_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT14_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func5)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT14_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT14_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT14_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT14_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT14_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT14_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func5)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT14_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT14_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT14_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT14_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT14_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT14_LC_FOM_TIME;

///Port Reversal(Dev3Func5)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT14_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT14_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT14_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT14_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func5)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func5)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT14_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func5)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT14_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func5)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT14_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func5)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT14_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func5)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT14_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func5)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT14_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func5)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT14_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_SRIS_SRNS;

///SRIS_EN(Dev3Func5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT14_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT14_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT14_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT14_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT14_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func5)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT14_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func5)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT14_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT14_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT14_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func5)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT14_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func5)
#define IDSOPT_DBG_GNB_PORT14_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func5)

///NP-DATA(Dev3Func5)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT14_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func5)
#define IDSOPT_DBG_GNB_PORT14_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func5)

///P-HDR(Dev3Func5)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT14_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func5)
#define IDSOPT_DBG_GNB_PORT14_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func5)

///P-DATA(Dev3Func5)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT14_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func5)
#define IDSOPT_DBG_GNB_PORT14_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func5)

///CPL-HDR(Dev3Func5)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT14_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func5)
#define IDSOPT_DBG_GNB_PORT14_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func5)

///CPL-DATA(Dev3Func5)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT14_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func5)
#define IDSOPT_DBG_GNB_PORT14_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func5)

///Gen1(Dev3Func5)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT14_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT14_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT14_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT14_SPC_GEN1;

///Gen2(Dev3Func5)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT14_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT14_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT14_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT14_SPC_GEN2;

///Gen3(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_PORT14_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT14_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT14_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PORT14_SPC_GEN3;

///Port Training(Dev3Func6)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT15_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT15_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_TRAINING;

///Hotplug Support(Dev3Func6)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT15_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT15_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT15_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_HOTPLUG;

///Speed Mode(Dev3Func6)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_SPEED_MODE;

///Compliance Mode(Dev3Func6)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT15_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT15_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_COMPLIANCE_MODE;

///Link ASPM(Dev3Func6)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT15_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT15_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_LINK_ASPM;

///Slot Power Limit,W(Dev3Func6) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT15_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT15_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func6)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT15_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func6)
#define IDSOPT_DBG_GNB_PCIE_PORT15_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func6)

///L1 Immediate ACK(Dev3Func6)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT15_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT15_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_L1_IMM_ACK;

///TX De-emphasis(Dev3Func6)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_TX_DEEMPHASIS;

///TX Margin(Dev3Func6)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_TX_MARGIN;

///Scrambler control(Dev3Func6)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT15_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT15_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT15_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT15_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func6)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT15_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT15_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT15_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT15_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT15_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT15_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func6)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT15_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func6)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT15_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT15_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT15_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT15_PM_L1_SS;

///L1.1(Dev3Func6)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT15_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT15_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT15_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT15_L1_1;

///L1.2(Dev3Func6)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT15_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT15_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT15_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT15_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func6)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT15_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT15_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT15_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT15_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func6)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT15_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT15_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT15_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT15_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func6)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT15_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT15_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT15_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT15_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT15_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT15_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func6)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT15_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT15_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT15_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT15_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT15_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT15_LC_FOM_TIME;

///Port Reversal(Dev3Func6)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT15_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT15_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT15_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT15_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func6)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func6)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT15_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func6)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT15_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func6)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT15_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func6)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT15_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func6)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT15_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func6)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT15_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func6)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT15_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_SRIS_SRNS;

///SRIS_EN(Dev3Func6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT15_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT15_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT15_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT15_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT15_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func6)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT15_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func6)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT15_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT15_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT15_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func6)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT15_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func6)
#define IDSOPT_DBG_GNB_PORT15_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func6)

///NP-DATA(Dev3Func6)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT15_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func6)
#define IDSOPT_DBG_GNB_PORT15_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func6)

///P-HDR(Dev3Func6)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT15_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func6)
#define IDSOPT_DBG_GNB_PORT15_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func6)

///P-DATA(Dev3Func6)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT15_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func6)
#define IDSOPT_DBG_GNB_PORT15_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func6)

///CPL-HDR(Dev3Func6)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT15_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func6)
#define IDSOPT_DBG_GNB_PORT15_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func6)

///CPL-DATA(Dev3Func6)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT15_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func6)
#define IDSOPT_DBG_GNB_PORT15_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func6)

///Gen1(Dev3Func6)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT15_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT15_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT15_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT15_SPC_GEN1;

///Gen2(Dev3Func6)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT15_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT15_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT15_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT15_SPC_GEN2;

///Gen3(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_PORT15_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT15_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT15_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PORT15_SPC_GEN3;

///Port Training(Dev3Func7)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT16_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT16_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_TRAINING;

///Hotplug Support(Dev3Func7)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT16_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT16_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT16_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_HOTPLUG;

///Speed Mode(Dev3Func7)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_SPEED_MODE;

///Compliance Mode(Dev3Func7)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT16_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT16_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_COMPLIANCE_MODE;

///Link ASPM(Dev3Func7)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT16_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT16_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_LINK_ASPM;

///Slot Power Limit,W(Dev3Func7) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT16_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT16_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev3Func7)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT16_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev3Func7)
#define IDSOPT_DBG_GNB_PCIE_PORT16_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev3Func7)

///L1 Immediate ACK(Dev3Func7)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT16_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT16_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_L1_IMM_ACK;

///TX De-emphasis(Dev3Func7)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_TX_DEEMPHASIS;

///TX Margin(Dev3Func7)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_TX_MARGIN;

///Scrambler control(Dev3Func7)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT16_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT16_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT16_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT16_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev3Func7)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT16_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT16_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT16_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT16_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT16_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT16_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev3Func7)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT16_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev3Func7)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT16_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT16_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT16_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT16_PM_L1_SS;

///L1.1(Dev3Func7)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT16_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT16_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT16_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT16_L1_1;

///L1.2(Dev3Func7)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT16_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT16_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT16_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT16_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev3Func7)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT16_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT16_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT16_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT16_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev3Func7)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT16_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT16_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT16_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT16_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev3Func7)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT16_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT16_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT16_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT16_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT16_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT16_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev3Func7)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT16_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT16_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT16_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT16_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT16_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT16_LC_FOM_TIME;

///Port Reversal(Dev3Func7)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT16_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT16_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT16_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT16_PORT_REVERSAL;

///Downstream Tx Preset(Dev3Func7)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev3Func7)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT16_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev3Func7)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT16_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev3Func7)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT16_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev3Func7)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT16_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev3Func7)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT16_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev3Func7)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT16_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev3Func7)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT16_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_SRIS_SRNS;

///SRIS_EN(Dev3Func7)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT16_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev3Func7)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT16_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev3Func7)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT16_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT16_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT16_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev3Func7)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT16_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev3Func7)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT16_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT16_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT16_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev3Func7)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT16_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev3Func7)
#define IDSOPT_DBG_GNB_PORT16_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev3Func7)

///NP-DATA(Dev3Func7)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT16_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev3Func7)
#define IDSOPT_DBG_GNB_PORT16_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev3Func7)

///P-HDR(Dev3Func7)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT16_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev3Func7)
#define IDSOPT_DBG_GNB_PORT16_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev3Func7)

///P-DATA(Dev3Func7)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT16_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev3Func7)
#define IDSOPT_DBG_GNB_PORT16_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev3Func7)

///CPL-HDR(Dev3Func7)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT16_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev3Func7)
#define IDSOPT_DBG_GNB_PORT16_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev3Func7)

///CPL-DATA(Dev3Func7)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT16_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev3Func7)
#define IDSOPT_DBG_GNB_PORT16_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev3Func7)

///Gen1(Dev3Func7)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT16_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT16_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT16_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT16_SPC_GEN1;

///Gen2(Dev3Func7)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT16_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT16_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT16_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT16_SPC_GEN2;

///Gen3(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_PORT16_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT16_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT16_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PORT16_SPC_GEN3;

///Port Training(Dev4Func1)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT17_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT17_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_TRAINING;

///Hotplug Support(Dev4Func1)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT17_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT17_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT17_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_HOTPLUG;

///Speed Mode(Dev4Func1)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE_GEN3OC = 4,///<GEN3 OC
  IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_SPEED_MODE;

///Compliance Mode(Dev4Func1)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT17_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT17_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_COMPLIANCE_MODE;

///Link ASPM(Dev4Func1)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT17_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT17_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_LINK_ASPM;

///Slot Power Limit,W(Dev4Func1) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT17_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT17_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(Dev4Func1)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT17_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(Dev4Func1)
#define IDSOPT_DBG_GNB_PCIE_PORT17_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(Dev4Func1)

///L1 Immediate ACK(Dev4Func1)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT17_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT17_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_L1_IMM_ACK;

///TX De-emphasis(Dev4Func1)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_TX_DEEMPHASIS;

///TX Margin(Dev4Func1)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_TX_MARGIN;

///Scrambler control(Dev4Func1)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT17_SCRAMBLER_CNTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT17_SCRAMBLER_CNTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT17_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT17_SCRAMBLER_CNTL;

///Equalization Search Mode(Dev4Func1)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT17_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT17_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT17_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT17_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT17_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT17_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (Dev4Func1)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT17_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(Dev4Func1)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT17_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT17_PM_L1_SS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT17_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT17_PM_L1_SS;

///L1.1(Dev4Func1)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT17_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT17_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT17_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT17_L1_1;

///L1.2(Dev4Func1)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT17_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT17_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT17_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT17_L1_2;

///Poweroff Unused Phy Lanes and PLL(Dev4Func1)
///Poweroff Unused Phy Lanes and PLL
typedef enum {
  IDSOPT_DBG_NBIO_PORT17_POWEROFF_UNUSED_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT17_POWEROFF_UNUSED_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT17_POWEROFF_UNUSED_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT17_POWEROFF_UNUSED;

///Poweroff Phy Lanes and PLL in L1(Dev4Func1)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT17_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT17_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT17_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT17_POWEROFF_IN_L1;

///Dynamic Lanes Power State for Linkwidth Switch(Dev4Func1)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT17_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT17_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT17_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT17_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT17_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT17_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(Dev4Func1)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT17_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT17_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT17_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT17_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT17_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT17_LC_FOM_TIME;

///Port Reversal(Dev4Func1)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT17_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT17_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT17_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT17_PORT_REVERSAL;

///Downstream Tx Preset(Dev4Func1)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_CFG_DS_TX_PRESET;

///Upstream Tx Preset(Dev4Func1)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT17_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(Dev4Func1)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT17_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(Dev4Func1)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT17_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_CFG_US_RX_HINT;

///Bypass Gen3 EQ(Dev4Func1)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT17_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_BYPASS_GEN3_EQ;

///Enable 3x3 Search(Dev4Func1)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT17_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_ENABLE3X3_SEARCH;

///Enable Safe Search(Dev4Func1)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT17_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(Dev4Func1)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT17_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_SRIS_SRNS;

///SRIS_EN(Dev4Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT17_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_SRIS_EN;

///SRIS_AUTODETECT_EN(Dev4Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT17_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(Dev4Func1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT17_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT17_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT17_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Dev4Func1)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT17_MAX_PAYLOAD_SIZE;

///Flow Control Credits Control(Dev4Func1)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT17_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT17_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT17_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(Dev4Func1)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT17_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(Dev4Func1)
#define IDSOPT_DBG_GNB_PORT17_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(Dev4Func1)

///NP-DATA(Dev4Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT17_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(Dev4Func1)
#define IDSOPT_DBG_GNB_PORT17_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(Dev4Func1)

///P-HDR(Dev4Func1)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT17_PH_CREDITS_MIN 0 ///< Min of P-HDR(Dev4Func1)
#define IDSOPT_DBG_GNB_PORT17_PH_CREDITS_MAX 0xff ///< Max of P-HDR(Dev4Func1)

///P-DATA(Dev4Func1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT17_PD_CREDITS_MIN 0 ///< Min of P-DATA(Dev4Func1)
#define IDSOPT_DBG_GNB_PORT17_PD_CREDITS_MAX 0xff ///< Max of P-DATA(Dev4Func1)

///CPL-HDR(Dev4Func1)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT17_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(Dev4Func1)
#define IDSOPT_DBG_GNB_PORT17_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(Dev4Func1)

///CPL-DATA(Dev4Func1)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT17_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(Dev4Func1)
#define IDSOPT_DBG_GNB_PORT17_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(Dev4Func1)

///Gen1(Dev4Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT17_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT17_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT17_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT17_SPC_GEN1;

///Gen2(Dev4Func1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PORT17_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT17_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT17_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT17_SPC_GEN2;

///Gen3(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_PORT17_SPC_GEN3_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PORT17_SPC_GEN3_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PORT17_SPC_GEN3_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PORT17_SPC_GEN3;

///LCLK Gating(GFX)
///Enable LCLK clock gating
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GFX_LCLK_GATING;

///Clock Gating (TxClk or RefClk branches)(GFX)
///Enable Clock gating (TXCLK, REFCLK)
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GFX_CLOCK_GATING;

///Master PLL Selection(GFX)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GFX_MASTER_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_MASTER_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_MASTER_PLL_CTL;

///MasterPLL
///MasterPLL
#define IDSOPT_DBG_GNB_GFX_MASTER_PLL_MIN 0 ///< Min of MasterPLL
#define IDSOPT_DBG_GNB_GFX_MASTER_PLL_MAX 0xff ///< Max of MasterPLL

///Force PLL PWR On when link in lower power mode(GFX)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GFX_FORCE_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_FORCE_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_FORCE_PLL_CTL;

///AllowPLLinPS4
///AllowPLLinPS4
typedef enum {
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_ALLOW_PL_LIN_P_S4;

///AllowPLLabovePS4
///AllowPLLabovePS4
typedef enum {
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_ALLOW_PL_LABOVE_P_S4;

///Force mplla on(GFX)
///Force mplla on
typedef enum {
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_FORCE_MPLLA_ON;

///Force mpllb on(GFX)
///Force mpllb on
typedef enum {
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_FORCE_MPLLB_ON;

///PCIe AtomicOps Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_GFX_ATOMIC_OPS;

///LCLK Gating(GPP)
///Enable LCLK clock gating
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GPP_LCLK_GATING;

///Clock Gating (TxClk or RefClk branches)(GPP)
///Enable Clock gating (TXCLK, REFCLK)
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_GPP_CLOCK_GATING;

///Master PLL Selection(GPP)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GPP_MASTER_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GPP_MASTER_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GPP_MASTER_PLL_CTL;

///MasterPLL
///MasterPLL
#define IDSOPT_DBG_GNB_GPP_MASTER_PLL_MIN 0 ///< Min of MasterPLL
#define IDSOPT_DBG_GNB_GPP_MASTER_PLL_MAX 0xff ///< Max of MasterPLL

///Force PLL PWR On when link in lower power mode(GPP)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GPP_FORCE_PLL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GPP_FORCE_PLL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GPP_FORCE_PLL_CTL;

///AllowPLLinPS4
///AllowPLLinPS4
typedef enum {
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GPP_ALLOW_PL_LIN_P_S4;

///AllowPLLabovePS4
///AllowPLLabovePS4
typedef enum {
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GPP_ALLOW_PL_LABOVE_P_S4;

///Force mplla on(GPP)
///Force mplla on
typedef enum {
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GPP_FORCE_MPLLA_ON;

///Force mpllb on(GPP)
///Force mpllb on
typedef enum {
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GPP_FORCE_MPLLB_ON;

///PCIe AtomicOps Support
///Enables AtomicOps on this PCIe controller
typedef enum {
  IDSOPT_DBG_GNB_GPP_ATOMIC_OPS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GPP_ATOMIC_OPS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GPP_ATOMIC_OPS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_GPP_ATOMIC_OPS;

///AER Dev1Func1
///AER Dev2Func1
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1;

///Bad TLP(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_TLP;

///Bad DLLP Status(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC1_ACS_VIOLATION_SEVERITY;

///AER Dev1Func2
///AER Dev1Func2
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2;

///Bad TLP(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_TLP;

///Bad DLLP Status(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC2_ACS_VIOLATION_SEVERITY;

///AER Dev1Func3
///AER Dev2Func1
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3;

///Bad TLP(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_TLP;

///Bad DLLP Status(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC3_ACS_VIOLATION_SEVERITY;

///AER Dev1Func4
///AER Dev1Func4
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4;

///Bad TLP(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_TLP;

///Bad DLLP Status(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC4_ACS_VIOLATION_SEVERITY;

///AER Dev1Func5
///AER Dev1Func5
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5;

///Bad TLP(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_TLP;

///Bad DLLP Status(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC5_ACS_VIOLATION_SEVERITY;

///AER Dev1Func6
///AER Dev1Func6
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6;

///Bad TLP(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_TLP;

///Bad DLLP Status(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC6_ACS_VIOLATION_SEVERITY;

///AER Dev1Func7
///AER Dev2Func1
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7;

///Bad TLP(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_TLP;

///Bad DLLP Status(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev1Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV1_FUNC7_ACS_VIOLATION_SEVERITY;

///AER Dev2Func1
///AER Dev2Func1
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1;

///Bad TLP(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_TLP;

///Bad DLLP Status(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV2_FUNC1_ACS_VIOLATION_SEVERITY;

///AER Dev3Func1
///AER Dev3Func1
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1;

///Bad TLP(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_TLP;

///Bad DLLP Status(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC1_ACS_VIOLATION_SEVERITY;

///AER Dev3Func2
///AER Dev3Func2
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2;

///Bad TLP(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_TLP;

///Bad DLLP Status(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func2)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC2_ACS_VIOLATION_SEVERITY;

///AER Dev3Func3
///AER Dev3Func3
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3;

///Bad TLP(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_TLP;

///Bad DLLP Status(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func3)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC3_ACS_VIOLATION_SEVERITY;

///AER Dev3Func4
///AER Dev3Func4
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4;

///Bad TLP(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_TLP;

///Bad DLLP Status(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func4)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC4_ACS_VIOLATION_SEVERITY;

///AER Dev3Func5
///AER Dev3Func5
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5;

///Bad TLP(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_TLP;

///Bad DLLP Status(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func5)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC5_ACS_VIOLATION_SEVERITY;

///AER Dev3Func6
///AER Dev3Func6
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6;

///Bad TLP(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_TLP;

///Bad DLLP Status(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func6)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC6_ACS_VIOLATION_SEVERITY;

///AER Dev3Func7
///AER Dev3Func7
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7;

///Bad TLP(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_TLP;

///Bad DLLP Status(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev3Func7)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV3_FUNC7_ACS_VIOLATION_SEVERITY;

///AER Dev4Func1
///AER Dev4Func1
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1;

///Bad TLP(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_TLP_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_TLP_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_TLP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_TLP;

///Bad DLLP Status(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_DLLP_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_DLLP_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_DLLP_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_BAD_DLLP_STATUS;

///Replay Number Rollover Status(Dev2Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_NUMBER_ROLLOVER_STATUS;

///Replay Timer Timeout Status(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_REPLAY_TIMER_TIMEOUT_STATUS;

///AdvisoryNonFatalError(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ADVISORY_NON_FATAL_ERROR_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ADVISORY_NON_FATAL_ERROR_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ADVISORY_NON_FATAL_ERROR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ADVISORY_NON_FATAL_ERROR;

///Data Link Protocol Error status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_MASK;

///Data Link Protocol Error status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_DATA_LINK_PROTOCOL_ERRORSTATUS_SEVERITY;

///Poisoned TLP Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_MASK;

///Poisoned TLP Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_POISONED_TLP_STATUS_SEVERITY;

///Completion Timeout Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_MASK;

///Completion Timeout Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETION_TIMEOUT_STATUS_SEVERITY;

///Completer Abort Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_MASK;

///Completer Abort Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_COMPLETER_ABORT_STATUS_SEVERITY;

///Unexpected Completion Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_MASK;

///Unexpected Completion Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNEXPECTED_COMPLETION_STATUS_SEVERITY;

///Malformed TLP Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_MASK;

///Malformed TLP Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_MALFORMED_TLP_STATUS_SEVERITY;

///ECRC Error Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_MASK;

///ECRC Error Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ECRC_ERROR_STATUS_SEVERITY;

///Unsupported Request Error Status Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_MASK;

///Unsupported Request Error Status Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_UNSUPPORTED_REQUEST_ERROR_STATUS_SEVERITY;

///Acs Violation Mask(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_MASK_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_MASK_ENABLED = 0,///<Enabled
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_MASK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_MASK;

///Acs Violation Severity(Dev4Func1)
typedef enum {
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_SEVERITY_NONFATAL = 0,///<non-fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_SEVERITY_FATAL = 1,///<fatal
  IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_SEVERITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_AER_DEV4_FUNC1_ACS_VIOLATION_SEVERITY;

///NBIO Global CG Override
typedef enum {
  IDSOPT_DBG_NBIO_GLOBAL_CG_OVERRIDE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_GLOBAL_CG_OVERRIDE_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_GLOBAL_CG_OVERRIDE;

///IOHC LCLK Clock Gating
///LCLK Gating (IOC)
typedef enum {
  IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PMM_IOHC_LCLK_GATING;

///IOMMU L1 Clock Gating
///IOMMU L1 LCLK Gating
typedef enum {
  IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOMMU_L1_CLOCK_GATING;

///IOMMU L2 Clock Gating
///IOMMU L2 LCLK Gating
typedef enum {
  IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOMMU_L2_CLOCK_GATING;

///SST clock gating
///SST clock gating
typedef enum {
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING;

///NBIF MGCG
///nBIF MCGC
typedef enum {
  IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_DISABLED = 0,///<Disabled
  IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_ENABLED = 1,///<Enabled
  IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_AUTO = 0xf,///<Auto
} IDSOPT_CBS_DBG_NBIO_NBIF_MGCG;

///NBIF MGCG Hysteresis
#define IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_HYSTERESIS_MIN 0 ///< Min of NBIF MGCG Hysteresis
#define IDSOPT_CBS_DBG_NBIO_NBIF_MGCG_HYSTERESIS_MAX 0xff ///< Max of NBIF MGCG Hysteresis

///SHUB MGCG
///SHUB (NGDC) MGCG
typedef enum {
  IDSOPT_DBG_NBIO_SHUB_MGCG_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_SHUB_MGCG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_SHUB_MGCG_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_SHUB_MGCG;

///SHUB MGCG Hysteresis
#define IDSOPT_DBG_NBIO_SHUB_MGCG_HYSTERESIS_MIN 0 ///< Min of SHUB MGCG Hysteresis
#define IDSOPT_DBG_NBIO_SHUB_MGCG_HYSTERESIS_MAX 0xff ///< Max of SHUB MGCG Hysteresis

///IOHC Global CG Control
typedef enum {
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_AUTO = 0xf,///<Auto
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_DISABLED = 0,///<Disabled
} IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL;

///  IOHC CG Hysteresis
#define IDSOPT_DBG_NBIO_IOHC_CG_HYSTERESIS_MIN 0 ///< Min of   IOHC CG Hysteresis
#define IDSOPT_DBG_NBIO_IOHC_CG_HYSTERESIS_MAX 255 ///< Max of   IOHC CG Hysteresis

///  IOHC CG CTRL0 CLK0
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK0_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK0_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK0;

///  IOHC CG CTRL0 CLK1
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK1_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK1_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK1;

///  IOHC CG CTRL0 CLK2
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK2_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK2_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK2;

///  IOHC CG CTRL0 CLK3
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK3_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK3_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK3;

///  IOHC CG CTRL0 CLK4
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK4_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK4;

///  IOHC CG CTRL0 CLK5
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK5_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK5_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK5;

///  IOHC CG CTRL0 CLK6
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK6_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK6_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK6;

///  IOHC CG CTRL0 CLK7
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK7_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK7_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK7;

///  IOHC CG CTRL0 CLK8
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK8_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK8_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK8;

///  IOHC CG CTRL0 CLK9
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK9_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK9_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL0_CLK9;

///  IOHC CG CTRL1 CLK0
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK0_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK0_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK0;

///  IOHC CG CTRL1 CLK1
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK1_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK1_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK1;

///  IOHC CG CTRL1 CLK2
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK2_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK2_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK2;

///  IOHC CG CTRL1 CLK3
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK3_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK3_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK3;

///  IOHC CG CTRL1 CLK4
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK4_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK4;

///  IOHC CG CTRL1 CLK5
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK5_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK5_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK5;

///  IOHC CG CTRL1 CLK6
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK6_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK6_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK6;

///  IOHC CG CTRL1 CLK7
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK7_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK7_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK7;

///  IOHC CG CTRL1 CLK8
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK8_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK8_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK8;

///  IOHC CG CTRL1 CLK9
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK9_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK9_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL1_CLK9;

///  IOHC CG CTRL2 CLK0
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK0_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK0_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK0;

///  IOHC CG CTRL2 CLK1
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK1_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK1_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK1;

///  IOHC CG CTRL2 CLK2
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK2_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK2_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK2;

///  IOHC CG CTRL2 CLK3
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK3_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK3_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK3;

///  IOHC CG CTRL2 CLK4
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK4_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK4_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK4;

///  IOHC CG CTRL2 CLK5
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK5_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK5_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK5;

///  IOHC CG CTRL2 CLK6
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK6_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK6_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK6;

///  IOHC CG CTRL2 CLK7
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK7_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK7_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK7;

///  IOHC CG CTRL2 CLK8
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK8_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK8_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK8;

///  IOHC CG CTRL2 CLK9
typedef enum {
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK9_ENABLED = 0,///<Enabled
  IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK9_DISABLED = 1,///<Disabled
} IDSOPT_DBG_NBIO_IOHC_CTRL2_CLK9;

///NTB Clock Gating
///Enable/Disable NTB Clock Gating
typedef enum {
  IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_NTB_CLOCK_ENABLE;

///SW Device ID Remapping
///SW Device ID Remapping
typedef enum {
  IDSOPT_DBG_GNB_NB_SW_DEVICE_ID_REMAPPING_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_NB_SW_DEVICE_ID_REMAPPING_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_NB_SW_DEVICE_ID_REMAPPING;

///PBr0 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR0_DEV_FN_MAP;

///PBr1 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR1_DEV_FN_MAP;

///PBr2 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR2_DEV_FN_MAP;

///PBr3 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR3_DEV_FN_MAP;

///PBr4 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR4_DEV_FN_MAP;

///PBr5 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR5_DEV_FN_MAP;

///PBr6 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP;

///PBr7 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR7_DEV_FN_MAP;

///PBr8 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR8_DEV_FN_MAP;

///PBr9 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR9_DEV_FN_MAP;

///PBr10 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR10_DEV_FN_MAP;

///PBr11 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR11_DEV_FN_MAP;

///PBr12 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F6 = 0x0E,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D1F7 = 0x0F,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR12_DEV_FN_MAP;

///PBr13 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR13_DEV_FN_MAP;

///PBr14 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR14_DEV_FN_MAP;

///PBr15 DevFnMap
typedef enum {
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F1 = 0x9,///<D1F1
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F2 = 0xA,///<D1F2
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F3 = 0xB,///<D1F3
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F4 = 0xC,///<D1F4
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F5 = 0xD,///<D1F5
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F6 = 0xE,///<D1F6
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D1F7 = 0xF,///<D1F7
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D2F1 = 0x11,///<D2F1
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F1 = 0x19,///<D3F1
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F2 = 0x1A,///<D3F2
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F3 = 0x1B,///<D3F3
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F4 = 0x1C,///<D3F4
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F5 = 0x1D,///<D3F5
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F6 = 0x1E,///<D3F6
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D3F7 = 0x1F,///<D3F7
  IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP_D4F1 = 0x21,///<D4F1
} IDSOPT_DBG_GNB_NB_P_BR15_DEV_FN_MAP;

///PhyA0 Owner (Lane0-1)
///PhyA0 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A0_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_A0_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A0_OWNER_SATA = 2,///<SATA
  IDSOPT_DBG_GNB_PHY_A0_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_A0_OWNER;

///PhyA1 Owner (Lane2-3)
///PhyA1 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A1_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_A1_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A1_OWNER_SATA = 2,///<SATA
  IDSOPT_DBG_GNB_PHY_A1_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_A1_OWNER;

///PhyA2 Owner (Lane4-7)
///PhyA2 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A2_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_A2_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A2_OWNER_SATA = 2,///<SATA
  IDSOPT_DBG_GNB_PHY_A2_OWNER_AUTO = 0xF,///<Auto
  IDSOPT_DBG_GNB_PHY_A2_OWNER_ETHERNET = 3,///<Ethernet
} IDSOPT_DBG_GNB_PHY_A2_OWNER;

///PhyA3 Owner (Lane8-11)
///PhyA3 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A3_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_A3_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A3_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_A3_OWNER;

///PhyA4 Owner (Lane12-15)
///PhyA4 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A4_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_A4_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A4_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_A4_OWNER;

///PhyB0 Owner (Lane0-1)
///PhyB0 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_B0_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_B0_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_B0_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_B0_OWNER;

///PhyB1 Owner (Lane2-3)
///PhyB1 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_B1_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_B1_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_B1_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_B1_OWNER;

///PhyB2 Owner (Lane4-7)
///PhyB2 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_B2_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_B2_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_B2_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_B2_OWNER;

///PhyB3 Owner (Lane8-11)
///PhyB3 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_B3_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_B3_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_B3_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_B3_OWNER;

///PhyB4 Owner (Lane12-15)
///PhyB4 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_B4_OWNER_GOP = 0,///<GoP
  IDSOPT_DBG_GNB_PHY_B4_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_B4_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_B4_OWNER;

///NBIO RAS Global Control
///NBIO RAS Global Control
typedef enum {
  IDSOPT_DBG_NBIORAS_GLOBAL_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIORAS_GLOBAL_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIORAS_GLOBAL_CTL;

///RAS_GLOBAL_STATUS_LO
///RAS Global Error Status
#define IDSOPT_DBG_RAS_GLOBAL_STATUS_LO_MIN 0 ///< Min of RAS_GLOBAL_STATUS_LO
#define IDSOPT_DBG_RAS_GLOBAL_STATUS_LO_MAX 0xffffffff ///< Max of RAS_GLOBAL_STATUS_LO

///RAS_GLOBAL_STATUS_HI
///RAS Global Error Status
#define IDSOPT_DBG_RAS_GLOBAL_STATUS_HI_MIN 0 ///< Min of RAS_GLOBAL_STATUS_HI
#define IDSOPT_DBG_RAS_GLOBAL_STATUS_HI_MAX 0xffffffff ///< Max of RAS_GLOBAL_STATUS_HI

///NBIO Misc RAS Control
///NBIO Misc RAS Control
typedef enum {
  IDSOPT_DBG_NBIO_MISC_RAS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_MISC_RAS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_MISC_RAS_CTL;

///MISC_RAS_CONTROL
///Miscellenous RAS Control
#define IDSOPT_DBG_MISC_RAS_CONTROL_MIN 0 ///< Min of MISC_RAS_CONTROL
#define IDSOPT_DBG_MISC_RAS_CONTROL_MAX 0xffffffff ///< Max of MISC_RAS_CONTROL

///NBIO Misc Severity Control
///NBIO Misc Severity Control
typedef enum {
  IDSOPT_DBG_NBIO_MISC_SEVERITY_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_MISC_SEVERITY_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_MISC_SEVERITY_CTL;

///MISC_SEVERITY_CONTROL
///Miscellenous Error Severity Control
#define IDSOPT_DBG_MISC_SEVERITY_CONTROL_MIN 0 ///< Min of MISC_SEVERITY_CONTROL
#define IDSOPT_DBG_MISC_SEVERITY_CONTROL_MAX 0xffffffff ///< Max of MISC_SEVERITY_CONTROL

///NBIO Error Event Action Control
///NBIO Error Event Action Control
typedef enum {
  IDSOPT_DBG_NBIO_ERROR_EVENT_ACTION_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_ERROR_EVENT_ACTION_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_ERROR_EVENT_ACTION_CTL;

///ErrEvent_ACTION_CONTROL
///Action controls when ErrEvent occurs
#define IDSOPT_DBG_ERR_EVENT_ACTION_CONTROL_MIN 0 ///< Min of ErrEvent_ACTION_CONTROL
#define IDSOPT_DBG_ERR_EVENT_ACTION_CONTROL_MAX 0xffffffff ///< Max of ErrEvent_ACTION_CONTROL

///NBIO Parity Control
///NBIO Parity Control
typedef enum {
  IDSOPT_DBG_NBIO_PARITY_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_PARITY_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_PARITY_CTL;

///PARITY_CONTROL_0
///Parity Control
#define IDSOPT_DBG_PARITY_CONTROL0_MIN 0 ///< Min of PARITY_CONTROL_0
#define IDSOPT_DBG_PARITY_CONTROL0_MAX 0xffffffff ///< Max of PARITY_CONTROL_0

///PARITY_CONTROL_1
///Parity Control
#define IDSOPT_DBG_PARITY_CONTROL1_MIN 0 ///< Min of PARITY_CONTROL_1
#define IDSOPT_DBG_PARITY_CONTROL1_MAX 0xffffffff ///< Max of PARITY_CONTROL_1

///PARITY_SEVERITY_CONTROL_UNCORR_0
///Parity Uncorrectable Groups Error Severity Control
#define IDSOPT_DBG_PARITY_SEVERITY_UNCORR_MIN 0 ///< Min of PARITY_SEVERITY_CONTROL_UNCORR_0
#define IDSOPT_DBG_PARITY_SEVERITY_UNCORR_MAX 0xffffffff ///< Max of PARITY_SEVERITY_CONTROL_UNCORR_0

///PARITY_SEVERITY_CONTROL_CORR_0
///Parity Correctable Groups Error Severity Control
#define IDSOPT_DBG_PARITY_SEVERITY_COR_R0_MIN 0 ///< Min of PARITY_SEVERITY_CONTROL_CORR_0
#define IDSOPT_DBG_PARITY_SEVERITY_COR_R0_MAX 0xffffffff ///< Max of PARITY_SEVERITY_CONTROL_CORR_0

///PARITY_SEVERITY_CONTROL_CORR_1
///Parity Correctable Groups Error Severity Control
#define IDSOPT_DBG_PARITY_SEVERITY_COR_R1_MIN 0 ///< Min of PARITY_SEVERITY_CONTROL_CORR_1
#define IDSOPT_DBG_PARITY_SEVERITY_COR_R1_MAX 0xffffffff ///< Max of PARITY_SEVERITY_CONTROL_CORR_1

///PARITY_SEVERITY_CONTROL_UCP_0
///Parity Correctable Groups Error Severity Control
#define IDSOPT_DBG_PARITY_SEVERITY_UCP_MIN 0 ///< Min of PARITY_SEVERITY_CONTROL_UCP_0
#define IDSOPT_DBG_PARITY_SEVERITY_UCP_MAX 0xffffffff ///< Max of PARITY_SEVERITY_CONTROL_UCP_0

///NBIO Poison Data Action Control
///Manual = User can set customized POISON_ACTION_CONTROL
typedef enum {
  IDSOPT_DBG_POISON_DATA_ACTION_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_POISON_DATA_ACTION_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_POISON_DATA_ACTION_CTL;

///POISON_ACTION_CONTROL
///POISON_ACTION_CONTROL
#define IDSOPT_DBG_POISON_ACTION_CONTROL_MIN 0 ///< Min of POISON_ACTION_CONTROL
#define IDSOPT_DBG_POISON_ACTION_CONTROL_MAX 0xffffffff ///< Max of POISON_ACTION_CONTROL

///NBIO Poison Mask
///Manual = User can set customized INTERNAL_POISON_MASK
typedef enum {
  IDSOPT_DBG_POISON_MASK_MANUAL = 1,///<Manual
  IDSOPT_DBG_POISON_MASK_AUTO = 0,///<Auto
} IDSOPT_DBG_POISON_MASK;

///INTERNAL_POISON_MASK
///INTERNAL_POISON_MASK
#define IDSOPT_DBG_INTERNAL_POISON_MASK_MIN 0 ///< Min of INTERNAL_POISON_MASK
#define IDSOPT_DBG_INTERNAL_POISON_MASK_MAX 0xff ///< Max of INTERNAL_POISON_MASK

///NBIO Egress Poison Mask
///Manual = User can set customized EGRESS_POISON_SEVERITY_DOWN/EGRESS_POISON_SEVERITY_UPPER
typedef enum {
  IDSOPT_DBG_EGRESS_POISON_MASK_MANUAL = 1,///<Manual
  IDSOPT_DBG_EGRESS_POISON_MASK_AUTO = 0,///<Auto
} IDSOPT_DBG_EGRESS_POISON_MASK;

///EGRESS_POISON_SEVERITY_DOWN
///EGRESS_POISON_SEVERITY_DOWN
#define IDSOPT_DBG_EGRESS_POISON_SEVERITY_DOWN_MIN 0 ///< Min of EGRESS_POISON_SEVERITY_DOWN
#define IDSOPT_DBG_EGRESS_POISON_SEVERITY_DOWN_MAX 0xffffffff ///< Max of EGRESS_POISON_SEVERITY_DOWN

///EGRESS_POISON_SEVERITY_UPPER
///EGRESS_POISON_SEVERITY_UPPER
#define IDSOPT_DBG_EGRESS_POISON_SEVERITY_UPPER_MIN 0 ///< Min of EGRESS_POISON_SEVERITY_UPPER
#define IDSOPT_DBG_EGRESS_POISON_SEVERITY_UPPER_MAX 0xffffffff ///< Max of EGRESS_POISON_SEVERITY_UPPER

///NBIO APML Control
///Manual = User can set customized APML_CONTROL
typedef enum {
  IDSOPT_DBG_APML_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_APML_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_APML_CTL;

///APML_CONTROL
///APML_CONTROL
#define IDSOPT_DBG_APML_CONTROL_MIN 0 ///< Min of APML_CONTROL
#define IDSOPT_DBG_APML_CONTROL_MAX 0xffffffff ///< Max of APML_CONTROL

///Overclocking Enable
///Disable Overclocking.  "Auto" will not force overclocking disabled
typedef enum {
  IDSOPT_DBG_OVERCLOCKING_ENABLE_AUTO = 0,///<Auto
  IDSOPT_DBG_OVERCLOCKING_ENABLE_DISABLE = 1,///<Disable
} IDSOPT_DBG_OVERCLOCKING_ENABLE;

///Overclocking Frequency Limit
///Value in MHz selects the maximum frequency setting allowed for overclocking support.
#define IDSOPT_DBG_OVERCLOCKING_FREQUENCY_LIMIT_MIN 0 ///< Min of Overclocking Frequency Limit
#define IDSOPT_DBG_OVERCLOCKING_FREQUENCY_LIMIT_MAX 8000 ///< Max of Overclocking Frequency Limit

///Overclocking Voltage Limit
///Value in mV selects the maximum voltage setting allowed for overclocking support.
#define IDSOPT_DBG_OVERCLOCKING_VOLTAGE_LIMIT_MIN 0 ///< Min of Overclocking Voltage Limit
#define IDSOPT_DBG_OVERCLOCKING_VOLTAGE_LIMIT_MAX 3000 ///< Max of Overclocking Voltage Limit

///AB Clock Gating
///Enable or disable AB clock gating
typedef enum {
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING;

///SDP Memory Power Saving
///Enable/disable SDP Memory Power Saving
typedef enum {
  IDSOPT_SBG_MEMORY_POWER_SAVING_ENABLED = 1,///<Enabled
  IDSOPT_SBG_MEMORY_POWER_SAVING_DISABLED = 0,///<Disabled
} IDSOPT_SBG_MEMORY_POWER_SAVING;

///SDP Clock Gating
///Enable/disable SDP Clock Gating
typedef enum {
  IDSOPT_SBG_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_SBG_CLOCK_GATING_DISABLED = 0,///<Disabled
} IDSOPT_SBG_CLOCK_GATING;

///XDMA DMA write 16-byte mode
///Enable/disable XDMA DMA Write 16 Byte Mode
typedef enum {
  IDSOPT_XDMA_DMA_WRITE16_BYTE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_XDMA_DMA_WRITE16_BYTE_MODE_DISABLED = 0,///<Disabled
} IDSOPT_XDMA_DMA_WRITE16_BYTE_MODE;

///XDMA Memory Power Saving
///Enable/disable XDMA Memory Power Saving
typedef enum {
  IDSOPT_XDMA_MEMORY_POWER_SAVING_ENABLED = 1,///<Enabled
  IDSOPT_XDMA_MEMORY_POWER_SAVING_DISABLED = 0,///<Disabled
} IDSOPT_XDMA_MEMORY_POWER_SAVING;

///XDMA PENDING NPR THRESHOLD
///XDMA PENDING NPR THRESHOLD
typedef enum {
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_32PENDINGNPR = 0,///<32 Pending NPR
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_1PENDINGNPR = 1,///<1 Pending NPR
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_4PENDINGNPR = 2,///<4 Pending NPR
  IDSOPT_XDMA_PENDING_NPR_THRESHOLD_28PENDINGNPR = 3,///<28 Pending NPR
} IDSOPT_XDMA_PENDING_NPR_THRESHOLD;

///XDMA DNCPL ORDER DIS
///XDMA DNCPL ORDER DIS
typedef enum {
  IDSOPT_XDMA_DNCPL_ORDER_DIS_ENABLED = 0,///<Enabled
  IDSOPT_XDMA_DNCPL_ORDER_DIS_DISABLED = 1,///<Disabled
} IDSOPT_XDMA_DNCPL_ORDER_DIS;

///SDPHOST_BYPASS_DATA_PACK
typedef enum {
  IDSOPT_SDPHOST_BYPASS_DATA_PACK_DISABLE = 0,///<Disable
  IDSOPT_SDPHOST_BYPASS_DATA_PACK_ENABLE = 1,///<Enable
} IDSOPT_SDPHOST_BYPASS_DATA_PACK;

///SDPHOST_DIS_NPMWR_PROTECT
typedef enum {
  IDSOPT_SDPHOST_DIS_NPMWR_PROTECT_DISABLE = 0,///<Disable
  IDSOPT_SDPHOST_DIS_NPMWR_PROTECT_ENABLE = 1,///<Enable
} IDSOPT_SDPHOST_DIS_NPMWR_PROTECT;

///SATA Set MaxGen2 Capability
///Select whether or not Enable SATA MaxGen2 Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2;

///SATA PHY Ref Clock
///Select SATA PHY Ref Clock
typedef enum {
  IDSOPT_DBG_FCH_SATA_CLK_MODE_EXT25MHZ = 0,///<Ext 25MHz
  IDSOPT_DBG_FCH_SATA_CLK_MODE_INT48MHZ = 1,///<Int 48MHz
  IDSOPT_DBG_FCH_SATA_CLK_MODE_INT100MHZ = 9,///<Int 100MHz
  IDSOPT_DBG_FCH_SATA_CLK_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_CLK_MODE;

///Aggressive Link PM Capability
///Select Enable or Disable Aggressive Link PM Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_AGGR_LINK_PM_CAP;

///Port Multiplier Capability
///Select Enable or Disable Port Multiplier Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MULT_CAP;

///Partial State Capability
///Select Enable or Disable Partial State Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_PSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_PSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_PSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PSC_CAP;

///Slumber State Capability
///Select Enable or Disable Slumber State Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_SSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SSC_CAP;

///Unused SATA Port Auto Shut Down
///Select Unused SATA Port Auto Shut Down or not
typedef enum {
  IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_CLK_AUTO_OFF;

///Options for FIS-based Switching Support
///Select Enable or Disable FIS-based Switching Support
typedef enum {
  IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_FIS_BASED_SWITCHING;

///Command Completion Coalescing Support
///Select Enable or Disable Command Completion Coalescing Support
typedef enum {
  IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_CCC_SUPPPORT;

///SATA MSI Capability
///Select Enable or Disable SATA MSI Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MSI_CAPABILITY;

///SATA Target Support 8 Devices
///Enable/disable SATA 8-device target support
typedef enum {
  IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_TARGET_SUPPORT8_DEVICE;

///Generic Mode
///Enable/disable SATA generic mode
typedef enum {
  IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE_ENABLED = 0,///<Enabled
  IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE_DISABLED = 1,///<Disabled
  IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_DISABLE_GENERIC_MODE;

///SATA AHCI Enclosure
///Enable/disable SATA AHCI enclosure management
typedef enum {
  IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_AHCI_ENCLOSURE_MANAGEMENT;

///SATA PHY PLL
///Enable/disable SATA PHY PLL shutdown
typedef enum {
  IDSOPT_DBG_FCH_SATA_PHY_PLL_SHUT_DOWN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_PHY_PLL_SHUT_DOWN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_PHY_PLL_SHUT_DOWN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PHY_PLL_SHUT_DOWN;

///SATA SGPIO
///Eable SGPIO feature
typedef enum {
  IDSOPT_DBG_FCH_SATA_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SGPIO0;

///eSATA Port0
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT0;

///eSATA Port1
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT1;

///eSATA Port2
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT2_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT2_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT2;

///eSATA Port3
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT3_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT3_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT3;

///eSATA Port4
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT4_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT4_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT4;

///eSATA Port5
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT5_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT5_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT5;

///eSATA Port6
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT6_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT6_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT6;

///eSATA Port7
///External SATA Port support
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT7_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT7_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT7;

///Sata mode for Port0
///SATA port mode for port 0
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT0_GEN1 = 1,///<Gen1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT0_GEN2 = 2,///<Gen2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT0;

///Sata mode for Port1
///SATA port mode for port 1
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT1_GEN1 = 1,///<Gen1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT1_GEN2 = 2,///<Gen2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT1;

///Sata mode for Port2
///Sata mode for Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT2_GEN1 = 1,///<Gen 1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT2_GEN2 = 2,///<Gen 2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT2;

///Sata mode for Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT3_GEN1 = 1,///<Gen 1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT3_GEN2 = 2,///<Gen 2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT3;

///Sata mode for Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT4_GEN1 = 1,///<Gen 1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT4_GEN2 = 2,///<Gen 2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT4;

///Sata mode for Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT5_GEN1 = 1,///<Gen 1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT5_GEN2 = 2,///<Gen 2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT5;

///Sata mode for Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT6_GEN1 = 1,///<Gen 1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT6_GEN2 = 2,///<Gen 2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT6;

///Sata mode for Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT7_GEN1 = 1,///<Gen 1
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT7_GEN2 = 2,///<Gen 2
  IDSOPT_DBG_FCH_SATA_PORT_MD_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_PORT_MD_PORT7;

///Die1 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ENABLE;

///Die2 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ENABLE;

///Die3 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ENABLE;

///Die4 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ENABLE;

///Die5 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ENABLE;

///Die6 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ENABLE;

///Die7 Sata Enable
///Enable or Disable Sata on Die1-7, Die0 is controlled by Common option.
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ENABLE;

///Die1 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT0;

///Die1 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT1;

///Die1 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT2;

///Die1 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT3;

///Die1 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT4;

///Die1 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT5;

///Die1 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT6;

///Die1 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_ESATA_PORT7;

///Die2 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT0;

///Die2 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT1;

///Die2 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT2;

///Die2 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT3;

///Die2 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT4;

///Die2 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT5;

///Die2 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT6;

///Die2 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_ESATA_PORT7;

///Die3 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT0;

///Die3 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT1;

///Die3 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT2;

///Die3 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT3;

///Die3 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT4;

///Die3 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT5;

///Die3 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT6;

///Die3 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_ESATA_PORT7;

///Die4 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT0;

///Die4 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT1;

///Die4 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT2;

///Die4 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT3;

///Die4 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT4;

///Die4 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT5;

///Die4 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT6;

///Die4 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_ESATA_PORT7;

///Die5 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT0;

///Die5 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT1;

///Die5 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT2;

///Die5 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT3;

///Die5 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT4;

///Die5 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT5;

///Die5 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT6;

///Die5 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_ESATA_PORT7;

///Die6 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT0;

///Die6 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT1;

///Die6 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT2;

///Die6 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT3;

///Die6 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT4;

///Die6 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT5;

///Die6 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT6;

///Die6 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_ESATA_PORT7;

///Die7 eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT0;

///Die7 eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT1;

///Die7 eSATA Port2
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT2;

///Die7 eSATA Port3
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT3;

///Die7 eSATA Port4
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT4;

///Die7 eSATA Port5
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT5;

///Die7 eSATA Port6
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT6;

///Die7 eSATA Port7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_ESATA_PORT7;

///Die1 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die1 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE1_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die2 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die2 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE2_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die3 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die3 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE3_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die4 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die4 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE4_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die5 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die5 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE5_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die6 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die6 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE6_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die7 DevSlp0 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP0;

///DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP0_NUM_MIN 0 ///< Min of DevSleep0 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP0_NUM_MAX 7 ///< Max of DevSleep0 Port Number

///Die7 DevSlp1 Enable
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP1;

///DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP1_NUM_MIN 0 ///< Min of DevSleep1 Port Number
#define IDSOPT_DBG_FCH_SATA_MCM_DIE7_DEV_SLP1_NUM_MAX 7 ///< Max of DevSleep1 Port Number

///Die1 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE1_SGPIO0;

///Die2 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE2_SGPIO0;

///Die3 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE3_SGPIO0;

///Die4 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE4_SGPIO0;

///Die5 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE5_SGPIO0;

///Die6 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE6_SGPIO0;

///Die7 Sata SGPIO
///Enable or Disable SataSgpio on Die1-7
typedef enum {
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_MCM_DIE7_SGPIO0;

///Timer Tick Tracking
///Enable/disable timer tick tracking
typedef enum {
  IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_FUSION_TIMER_TICK_TRACK;

///Clock Interrupt Tag
///Enable/disable tag on clock interrupt
typedef enum {
  IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_FUSION_CLOCK_INTERRUPT_TAG;

///SD debug mode
///Select SD Debug mode
typedef enum {
  IDSOPT_DBG_FCH_SD_CONFIG_AUTO = 0xf,///<Auto
  IDSOPT_DBG_FCH_SD_CONFIG_DMA = 1,///<DMA
  IDSOPT_DBG_FCH_SD_CONFIG_PIO = 2,///<PIO
} IDSOPT_DBG_FCH_SD_CONFIG;

///SD Clock Multiplier feature
///Select SD Clock Multiplier feature
typedef enum {
  IDSOPT_DBG_FCH_SD_CLOCK_MULTIPLIER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SD_CLOCK_MULTIPLIER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SD_CLOCK_MULTIPLIER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SD_CLOCK_MULTIPLIER;

///SDB
///Select whether or not set FCH debug function
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_SERIAL_DEBUG_BUS_ENABLE;

///HPET in FCH
///Select whether or not Enable HPET in FCH
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_HPET_ENABLE;

///Wathdog Timer (WDT) in FCH
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE;

///FCH Spread Spectrum
///Select whether or not Enable the Spread Spectrum Feature
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_SPREAD_SPECTRUM;

///Not Clear ThermalTrip Status
///Select whether or not Clear the ThermalTrip Status bit
typedef enum {
  IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_NO_CLR_THERMAL_TRIP;

///A Link Clock Gate Off
///A Link Clock Gate Off
typedef enum {
  IDSOPT_A_LINK_CLK_GATE_OFF_ENABLED = 1,///<Enabled
  IDSOPT_A_LINK_CLK_GATE_OFF_DISABLED = 0,///<Disabled
} IDSOPT_A_LINK_CLK_GATE_OFF;

///B Link Clock Gate Off
///B Link Clock Gate Off
typedef enum {
  IDSOPT_B_LINK_CLK_GATE_OFF_ENABLED = 1,///<Enabled
  IDSOPT_B_LINK_CLK_GATE_OFF_DISABLED = 0,///<Disabled
} IDSOPT_B_LINK_CLK_GATE_OFF;

///Reset after sync flood
///Enable AB to forward downstream sync-flood message to system\ncontroller.
typedef enum {
  IDSOPT_DBG_FCH_SYNCFLOOD_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_SYNCFLOOD_ENABLE_DISABLE = 0,///<Disable
  IDSOPT_DBG_FCH_SYNCFLOOD_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYNCFLOOD_ENABLE;

///Stress Reset Mode
///Select stress reset mode
typedef enum {
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_IO_WRITE_64_FE = 1,///<IO_WRITE_64_FE
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_IO_WRITE_CF9_06 = 2,///<IO_WRITE_CF9_06
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_IO_WRITE_CF9_0E = 3,///<IO_WRITE_CF9_0E
  IDSOPT_DBG_FCH_STRESS_RESET_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_STRESS_RESET_MODE;

///Long Timer SMI
///Whether to register long timer SMI in POST. Short Timer and Long Timer SMIs can be enabled exclusively, if both are enabled, only Long timer SMI will take effect
typedef enum {
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_LONG_TIMER_SMI;

///Long Timer SMI StartNow
///Whether to start the SMI immediately during registration
typedef enum {
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_LONG_TIMER_START_NOW;

///Long Timer CycleDuration
///Actual cycle duration = CycleDuration + 1 (ms), eg: CycleDuration = 999, then SMI frequency=1Hz
#define IDSOPT_DBG_FCH_SMI_LONG_TIMER_CYCLE_DURATION_MIN 0 ///< Min of Long Timer CycleDuration
#define IDSOPT_DBG_FCH_SMI_LONG_TIMER_CYCLE_DURATION_MAX 0x7fff ///< Max of Long Timer CycleDuration

///Short Timer SMI
///Whether to register short timer SMI in POST
typedef enum {
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_SHORT_TIMER_SMI;

///Short Timer SMI StartNow
///Whether to start the SMI immediately during registration
typedef enum {
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SMI_SHORT_TIMER_START_NOW;

///Short Timer CycleDuration
///Actual cycle duration = CycleDuration + 1 (us), eg: CycleDuration = 999, then SMI frequency=1000Hz
#define IDSOPT_DBG_FCH_SMI_SHORT_TIMER_CYCLE_DURATION_MIN 0 ///< Min of Short Timer CycleDuration
#define IDSOPT_DBG_FCH_SMI_SHORT_TIMER_CYCLE_DURATION_MAX 0x7fff ///< Max of Short Timer CycleDuration

///LPC_CLK0
typedef enum {
  IDSOPT_DBG_FCH_LPC_CL_K0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_LPC_CL_K0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_LPC_CL_K0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_LPC_CL_K0;

///LPC_CLK1
typedef enum {
  IDSOPT_DBG_FCH_LPC_CL_K1_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_LPC_CL_K1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_LPC_CL_K1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_LPC_CL_K1;

///USB ecc SMI Enable
typedef enum {
  IDSOPT_DBG_FCH_US_BECC_SMI_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_FCH_US_BECC_SMI_ENABLE_OFF = 0,///<Off
  IDSOPT_DBG_FCH_US_BECC_SMI_ENABLE_AUTO = 0xF,///<Auto
} IDSOPT_DBG_FCH_US_BECC_SMI_ENABLE;

///PT Aggressive Link PM Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_AGGR_LINK_PM_CAP;

///PT Partial State Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_PSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_PSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_PSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_PSC_CAP;

///PT Slumber State Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_SSC_CAP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_SSC_CAP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_SSC_CAP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_SSC_CAP;

///PT SATA MSI Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_MSI_CAPABILITY_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_MSI_CAPABILITY_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_MSI_CAPABILITY_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_MSI_CAPABILITY;

///PT Sata mode for Port0
///PT SATA port mode for port 0
typedef enum {
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_GEN1 = 1,///<Gen1
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_GEN2 = 2,///<Gen2
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_GEN3 = 3,///<Gen3
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_PORT_MD_PORT0;

///PT Sata mode for Port1
///PT SATA port mode for port 1
typedef enum {
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_GEN1 = 1,///<Gen1
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_GEN2 = 2,///<Gen2
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_GEN3 = 3,///<Gen3
  IDSOPT_DBG_PT_SATA_PORT_MD_PORT1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_SATA_PORT_MD_PORT1;

///PT Sata Hot Plug Capability
typedef enum {
  IDSOPT_DBG_PT_SATA_HOT_PLUG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_SATA_HOT_PLUG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_SATA_HOT_PLUG_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PT_SATA_HOT_PLUG;

///PT Securiry Lock
typedef enum {
  IDSOPT_DBG_PT_LOCK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_LOCK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_LOCK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_LOCK;

///PT AOAC
///AOAC
typedef enum {
  IDSOPT_DBG_PTAOAC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PTAOAC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PTAOAC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PTAOAC;

///PT HW LPM
typedef enum {
  IDSOPT_DBG_PTHW_LPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PTHW_LPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PTHW_LPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PTHW_LPM;

///PT DbC
typedef enum {
  IDSOPT_DBG_PT_DB_C_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PT_DB_C_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PT_DB_C_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PT_DB_C;

///PT XHC PME
///PT XHC PME
typedef enum {
  IDSOPT_DBG_PTXHC_PME_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PTXHC_PME_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PTXHC_PME_AUTO = 0xf,///<Auto
} IDSOPT_DBG_PTXHC_PME;

///override the HTFmax Frequenecy and HTFmax temp
///Auto = Use default Value\nManual = User override the HTFmax Frequenecy and HTFmax temp
typedef enum {
  IDSOPT_DGB_HT_FMAX_FREQ_TEMP_MANUAL = 1,///<Manual
  IDSOPT_DGB_HT_FMAX_FREQ_TEMP_AUTO = 0,///<Auto
} IDSOPT_DGB_HT_FMAX_FREQ_TEMP;

///HTFmax Frequenecy
///HTFmax Frequenecy(MH)
#define IDSOPT_DBG_OVERRIDE_HT_FMAX_FREQ_MIN 0 ///< Min of HTFmax Frequenecy
#define IDSOPT_DBG_OVERRIDE_HT_FMAX_FREQ_MAX 0xffff ///< Max of HTFmax Frequenecy

///HTFmax Temperature
///HTFmax Temperature(degrees C)
#define IDSOPT_DBG_OVERRIDE_HT_FMAX_TEMP_MIN 0 ///< Min of HTFmax Temperature
#define IDSOPT_DBG_OVERRIDE_HT_FMAX_TEMP_MAX 0xffff ///< Max of HTFmax Temperature

///MCM Data Transfer
///FEATURE_MCM_DATA_TRANSFER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUMCM_DATA_TRANS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUMCM_DATA_TRANS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUMCM_DATA_TRANS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUMCM_DATA_TRANS;

///Data Calculation
///FEATURE_DATA_CALCULATION_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_DATA_CALCULATION_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_DATA_CALCULATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_DATA_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_DATA_CALCULATION;

///PPT
///FEATURE_PPT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPPT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPPT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPPT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPPT;

///TDC
///FEATURE_TDC_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUTDC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUTDC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUTDC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUTDC;

///Thermal Controller
///FEATURE_THERMAL_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_THERMAL_CONTROLLER;

///Reliability Controller
///FEATURE_FIT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_RELIABILITY_CONTROLLER;

///QOS
///FEATURE_QOS_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUQOS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUQOS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUQOS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUQOS;

///PROCHOT
///FEATURE_PROCHOT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPROCHOT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPROCHOT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPROCHOT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPROCHOT;

///CCLK Controller
///FEATURE_CCLK_CONTROLLER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUCCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUCCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUCCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUCCLK;

///Voltage Controller
///FEATURE_VOLTAGE__CONTROLLER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_VOLTAGE_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_VOLTAGE_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_VOLTAGE_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_VOLTAGE_CONTROLLER;

///PCIe Hotplug
///FEATURE_PCIE_HOTPLUG_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPC_IE_HOTPLUG;

///Fan Controller
///FEATURE_FAN_CONTROLLER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_FAN_CONTROLLER;

///DLWM
///FEATURE_DLWM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDLWM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDLWM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDLWM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDLWM;

///Core Cstates
///FEATURE_CORE_CSTATES_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_CORE_CSTATES_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_CORE_CSTATES_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_CORE_CSTATES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_CORE_CSTATES;

///PC6
///FEATURE_PC6_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUP_C6_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUP_C6_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUP_C6_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUP_C6;

///Cstate Boost
///FEATURE_CSTATE_BOOST_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_CSTATE_BOOST_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_CSTATE_BOOST_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_CSTATE_BOOST_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_CSTATE_BOOST;

///FW Deep Sleep
///FEATURE_FW_DEEPSLEEP_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUFW_DEEP_SLEEP_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUFW_DEEP_SLEEP_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUFW_DEEP_SLEEP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUFW_DEEP_SLEEP;

///TDC Control
///Auto = Use the fused VDDCR_CPU TDC limit\nManual = User can set customized VDDCR_CPU TDC limit
typedef enum {
  IDSOPT_DBG_TDC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_TDC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_TDC_CTL;

///TDC
///VDDCR_CPU TDC Limit [A]
#define IDSOPT_DBG_TDC_LIMIT_MIN 0 ///< Min of TDC
#define IDSOPT_DBG_TDC_LIMIT_MAX 0xffffffff ///< Max of TDC

///EDC Control
///Auto = Use the fused VDDCR_CPU TDC limit\nManual = User can set customized VDDCR_CPU TDC limit
typedef enum {
  IDSOPT_DBG_EDC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_EDC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_EDC_CTL;

///EDC
///VDDCR_CPU EDC Limit [A]
#define IDSOPT_DBG_EDC_LIMIT_MIN 0 ///< Min of EDC
#define IDSOPT_DBG_EDC_LIMIT_MAX 0xffffffff ///< Max of EDC

///DLDO Core
///0 = Normal Regulation\n1 = Bypass to VDDCR_CPU
typedef enum {
  IDSOPT_DBG_CORE_DLDO_0 = 0,///<0
  IDSOPT_DBG_CORE_DLDO_1 = 1,///<1
  IDSOPT_DBG_CORE_DLDO_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CORE_DLDO;

///CLDO E12GA_GMI
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM
typedef enum {
  IDSOPT_DBG_CLDO_E12_GA_0 = 0,///<0
  IDSOPT_DBG_CLDO_E12_GA_1 = 1,///<1
  IDSOPT_DBG_CLDO_E12_GA_2 = 2,///<2
  IDSOPT_DBG_CLDO_E12_GA_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_E12_GA;

///CLDO DDR_GMI
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM
typedef enum {
  IDSOPT_DBG_CLDO_DDR_0 = 0,///<0
  IDSOPT_DBG_CLDO_DDR_1 = 1,///<1
  IDSOPT_DBG_CLDO_DDR_2 = 2,///<2
  IDSOPT_DBG_CLDO_DDR_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_DDR;

///CLDO WAFL_GMI
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM
typedef enum {
  IDSOPT_DBG_CLDO_WAFL_0 = 0,///<0
  IDSOPT_DBG_CLDO_WAFL_1 = 1,///<1
  IDSOPT_DBG_CLDO_WAFL_2 = 2,///<2
  IDSOPT_DBG_CLDO_WAFL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_WAFL;

///CLDO E12GB
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM\n*For SP3 and SP4 packages, this settings is NOT used.  The bypass setting for E12GB is used for WAFL_GMI in this case.
typedef enum {
  IDSOPT_DBG_CLDO_E12_GB_0 = 0,///<0
  IDSOPT_DBG_CLDO_E12_GB_1 = 1,///<1
  IDSOPT_DBG_CLDO_E12_GB_2 = 2,///<2
  IDSOPT_DBG_CLDO_E12_GB_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_E12_GB;

///CLDO VDDM0
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM\n For SP3 and SP4 packages, this settings is NOT used.  The bypass setting for E12GB is used for WAFL_GMI in this case.
typedef enum {
  IDSOPT_DBG_CLDO_VDDM0_0 = 0,///<0
  IDSOPT_DBG_CLDO_VDDM0_1 = 1,///<1
  IDSOPT_DBG_CLDO_VDDM0_2 = 2,///<2
  IDSOPT_DBG_CLDO_VDDM0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_VDDM0;

///CLDO VDDM1
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM
typedef enum {
  IDSOPT_DBG_CLDO_VDDM1_0 = 0,///<0
  IDSOPT_DBG_CLDO_VDDM1_1 = 1,///<1
  IDSOPT_DBG_CLDO_VDDM1_2 = 2,///<2
  IDSOPT_DBG_CLDO_VDDM1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_VDDM1;

///CLDO_VDDM Control
///Manual = User can set customized CLDO_VDDM voltage
typedef enum {
  IDSOPT_DBG_CLDO_VDDM_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CLDO_VDDM_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CLDO_VDDM_CTL;

///CLDO_VDDM voltage
///Warning: user must manually cold reset the system so that the CLDOs get re-latched otherwise the voltage change will not take into effect.\n\nCLDO_VDDM voltage [mV] 0 = Invalid value.
#define IDSOPT_DBG_CLDOVDD_MVOLTAGE_MIN 0 ///< Min of CLDO_VDDM voltage
#define IDSOPT_DBG_CLDOVDD_MVOLTAGE_MAX 0xffffffff ///< Max of CLDO_VDDM voltage

///Core Stretch Thresh Control
///Auto = Default core clock stretch thresh\nManual = User can set custom core clock stretch thresh
typedef enum {
  IDSOPT_DBG_CKS_CORE_STRETCH_THRESH_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CKS_CORE_STRETCH_THRESH_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CKS_CORE_STRETCH_THRESH_CTL;

///Core Stretch Thresh
///1 = 2.5%\n2 = 5.0%\n3 = 7.5%
typedef enum {
  IDSOPT_DBG_CKS_CORE_STRETCH_THRESH_1 = 1,///<1
  IDSOPT_DBG_CKS_CORE_STRETCH_THRESH_2 = 2,///<2
  IDSOPT_DBG_CKS_CORE_STRETCH_THRESH_3 = 3,///<3
} IDSOPT_DBG_CKS_CORE_STRETCH_THRESH;

///L3 Stretch Thresh Control
///Auto = Default L3 clock stretch thresh\nManual = User can set custom L3 clock stretch thresh
typedef enum {
  IDSOPT_DBG_CKS_L3_STRETCH_THRESH_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CKS_L3_STRETCH_THRESH_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CKS_L3_STRETCH_THRESH_CTL;

///L3 Stretch Thresh
///1 = 2.5%\n2 = 5.0%\n3 = 7.5%
typedef enum {
  IDSOPT_DBG_CKS_L3_STRETCH_THRESH_1 = 1,///<1
  IDSOPT_DBG_CKS_L3_STRETCH_THRESH_2 = 2,///<2
  IDSOPT_DBG_CKS_L3_STRETCH_THRESH_3 = 3,///<3
} IDSOPT_DBG_CKS_L3_STRETCH_THRESH;

///XI Separation Control
///Auto = Default XI separation settings\nManual = User can set custom XI separation settings
typedef enum {
  IDSOPT_DGB_XI_SEPARATION_CTL_MANUAL = 1,///<Manual
  IDSOPT_DGB_XI_SEPARATION_CTL_AUTO = 0,///<Auto
} IDSOPT_DGB_XI_SEPARATION_CTL;

///XI Separation High Frequency
///Specify the XI separation to use in the high CCLK frequency range
#define IDSOPT_DBG_XI_SEPARATION_HIGH_FREQ_MIN 0 ///< Min of XI Separation High Frequency
#define IDSOPT_DBG_XI_SEPARATION_HIGH_FREQ_MAX 0xff ///< Max of XI Separation High Frequency

///XI Separation Low Frequency
///Specify the XI separation to use in the low CCLK frequency range
#define IDSOPT_DBG_XI_SEPARATION_LOW_FREQ_MIN 0 ///< Min of XI Separation Low Frequency
#define IDSOPT_DBG_XI_SEPARATION_LOW_FREQ_MAX 0xff ///< Max of XI Separation Low Frequency

///CCLK Frequency Control
///Auto = Use default VDDCR_CPU voltage control\nManual = User can set custom VDDCR_CPU voltage control settings
typedef enum {
  IDSOPT_DGB_CCLK_FREQ_CTL_MANUAL = 1,///<Manual
  IDSOPT_DGB_CCLK_FREQ_CTL_AUTO = 0,///<Auto
} IDSOPT_DGB_CCLK_FREQ_CTL;

///Force CCLK Frequency
///Specify CCLK Frequency
#define IDSOPT_DBG_FORCE_CCLK_FREQ_MIN 0 ///< Min of Force CCLK Frequency
#define IDSOPT_DBG_FORCE_CCLK_FREQ_MAX 0xffffffff ///< Max of Force CCLK Frequency

///VDDCR_CPU Voltage Control
///VDDCR_CPU Voltage Control
typedef enum {
  IDSOPT_DBG_VDDCR_CPU_VOLTAGE_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_VDDCR_CPU_VOLTAGE_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_VDDCR_CPU_VOLTAGE_CTL;

///VDDCR_CPU Force VID Control
///Unforce = Do not force the VDDCR_CPU VID\nForce = Force the VDDCR_CPU VID
typedef enum {
  IDSOPT_DBG_VDDCR_CPU_FORCE_VID_CTL_FORCE = 1,///<Force
  IDSOPT_DBG_VDDCR_CPU_FORCE_VID_CTL_UNFORCE = 0,///<Unforce
} IDSOPT_DBG_VDDCR_CPU_FORCE_VID_CTL;

///VDDCR_CPU Force VID
///Specify CbsDbgVddcrCpuForceVid
#define IDSOPT_DBG_VDDCR_CPU_FORCE_VID_MIN 0 ///< Min of VDDCR_CPU Force VID
#define IDSOPT_DBG_VDDCR_CPU_FORCE_VID_MAX 0xff ///< Max of VDDCR_CPU Force VID

///VDDCR_CPU Voltage Offset
///Specify the voltage offset to apply to VDDCR_CPU -- signed integer [mV]
#define IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_MIN 0 ///< Min of VDDCR_CPU Voltage Offset
#define IDSOPT_DBG_VDDCR_CPU_VOLTAGE_OFFSET_MAX 0xffffffff ///< Max of VDDCR_CPU Voltage Offset

///AllocateDramBuffer Control
///Auto = No not allocate a DRAM buffer/n Menual = Allocate DRAM buffer
typedef enum {
  IDSOPT_DBG_DRAM_ALLOCATION_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_DRAM_ALLOCATION_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_DRAM_ALLOCATION_CTL;

///AllocateDramBuffer
///0 = No not allocate a DRAM buffer\nany non-zero value = Allocate DRAM buffer to size in MB defined in the setting
#define IDSOPT_DBG_CBS_DBG_ALLOCATE_DRAM_BUFFER_MIN 0 ///< Min of AllocateDramBuffer
#define IDSOPT_DBG_CBS_DBG_ALLOCATE_DRAM_BUFFER_MAX 0xffffffff ///< Max of AllocateDramBuffer

///Dldo Psm Margin Control
///Manual = User can set customized Dldo Psm Margin
typedef enum {
  IDSOPT_DBG_CBS_DBG_DLDO_PSM_MARGIN_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CBS_DBG_DLDO_PSM_MARGIN_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CBS_DBG_DLDO_PSM_MARGIN_CTL;

///Dldo Psm Margin
///Specify the PSM offset to apply to the DLDOs -- signed integer [1 PSM count ~ 1.8mV]\n 0 = Invalid value.
#define IDSOPT_DBG_DLDO_PSM_MARGIN_MIN 0 ///< Min of Dldo Psm Margin
#define IDSOPT_DBG_DLDO_PSM_MARGIN_MAX 0xffffffff ///< Max of Dldo Psm Margin

///FcwSlewFrac Control
///Auto = Use default FcwSlewFrac.L3FidTotalSteps\nManual = User can set custom FcwSlewFrac.L3FidTotalSteps
typedef enum {
  IDSOPT_DBG_FCW_SLEW_FRAC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_FCW_SLEW_FRAC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_FCW_SLEW_FRAC_CTL;

///FcwSlewFrac
///Specify the FcwSlewFrac.L3FidTotalSteps to use
#define IDSOPT_DBG_FCW_SLEW_FRAC_MIN 0 ///< Min of FcwSlewFrac
#define IDSOPT_DBG_FCW_SLEW_FRAC_MAX 0xffffffff ///< Max of FcwSlewFrac

///WaitVidCompDis
///0 = Use VOTF complete signal (VID on the fly)\n1 = Use internal timer in SVI logic
typedef enum {
  IDSOPT_DBG_WAIT_VID_COMP_DIS_0 = 0,///<0
  IDSOPT_DBG_WAIT_VID_COMP_DIS_1 = 1,///<1
  IDSOPT_DBG_WAIT_VID_COMP_DIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_WAIT_VID_COMP_DIS;

///UseTelemetryFor Throttling
///0 = Use CAC for throttling (default)\n1 = Use telemetry for throttling
typedef enum {
  IDSOPT_DBG_USE_TELEMETRY_THROTTLING_0 = 0,///<0
  IDSOPT_DBG_USE_TELEMETRY_THROTTLING_1 = 1,///<1
  IDSOPT_DBG_USE_TELEMETRY_THROTTLING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_USE_TELEMETRY_THROTTLING;

///DC BTC
///0 = Do not run DC BTC\n1 = Run DC BTC\nAuto = Use default DC BTC settings
typedef enum {
  IDSOPT_DBG_DC_BTC_0 = 0,///<0
  IDSOPT_DBG_DC_BTC_1 = 1,///<1
  IDSOPT_DBG_DC_BTC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_DC_BTC;

///AC BTC
///0 = Do not run AC BTC\n1 = Run AC BTC in single frequency mode\n2 = Run AC BTC in 3 frequency mode\nAuto = Use default AC BTC settings
typedef enum {
  IDSOPT_DBG_AC_BTC_0 = 0,///<0
  IDSOPT_DBG_AC_BTC_1 = 1,///<1
  IDSOPT_DBG_AC_BTC_2 = 2,///<2
  IDSOPT_DBG_AC_BTC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_AC_BTC;

///Frequency Control
///Manual = User can set decrease the max frequency
typedef enum {
  IDSOPT_DBG_SMU_FREQUENCY_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_SMU_FREQUENCY_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_SMU_FREQUENCY_CTL;

///Frequency to adjust
///Specify decrease the max frequency value(Mhz).
#define IDSOPT_DBG_SMU_FREQUENCY_ADJUST_MIN 0 ///< Min of Frequency to adjust
#define IDSOPT_DBG_SMU_FREQUENCY_ADJUST_MAX 0xffff ///< Max of Frequency to adjust

///Temperature Limit Control
///Manual = User can set Temperature Limit
typedef enum {
  IDSOPT_DBG_SMU_TEMPERATURE_LIMIT_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_SMU_TEMPERATURE_LIMIT_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_SMU_TEMPERATURE_LIMIT_CTL;

///Temperature limit
///Specify the max Temperature limit(C).
#define IDSOPT_DBG_SMU_TEMPERATURE_LIMIT_MIN 0 ///< Min of Temperature limit
#define IDSOPT_DBG_SMU_TEMPERATURE_LIMIT_MAX 0xff ///< Max of Temperature limit

///Telemetry Control
///Auto = Use default telemetry settings Manual = User can set custom telemetry settings
typedef enum {
  IDSOPT_DBG_TELEMETRY_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_TELEMETRY_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_TELEMETRY_CTL;

///VDDCR_VDD Full Scale Telemetry Current (mA)
///Specify the VDDCR_VDD telemetry current slope [mA]
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE_MIN 0 ///< Min of VDDCR_VDD Full Scale Telemetry Current (mA)
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE_MAX 0xffffffff ///< Max of VDDCR_VDD Full Scale Telemetry Current (mA)

///VDDCR_VDD Telemetry Offset Sign (positive/negative)
///Positive: VDDCR_VDD Telemetry Current Offset is positive value\nNegative: VDDCR_VDD Telemetry Current Offset is negative value
typedef enum {
  IDSOPT_DBG_TELEMETRY_VDD_OFFSET_SIGN_POSITIVE = 0,///<Positive
  IDSOPT_DBG_TELEMETRY_VDD_OFFSET_SIGN_NEGATIVE = 1,///<Negative
} IDSOPT_DBG_TELEMETRY_VDD_OFFSET_SIGN;

///VDDCR_VDD Telemetry Offset Value (mA)
///Specify the VDDCR_VDD telemetry current slope [mA]
#define IDSOPT_DBG_TELEMETRY_VDD_OFFSET_MIN 0 ///< Min of VDDCR_VDD Telemetry Offset Value (mA)
#define IDSOPT_DBG_TELEMETRY_VDD_OFFSET_MAX 0xffffffff ///< Max of VDDCR_VDD Telemetry Offset Value (mA)

///VDDCR_SOC Full Scale Telemetry Current (mA)
///Specify the VDDCR_SOC telemetry current slope [mA]
#define IDSOPT_DBG_TELEMETRY_SOC_SLOPE_MIN 0 ///< Min of VDDCR_SOC Full Scale Telemetry Current (mA)
#define IDSOPT_DBG_TELEMETRY_SOC_SLOPE_MAX 0xffffffff ///< Max of VDDCR_SOC Full Scale Telemetry Current (mA)

///VDDCR_SOC Telemetry Offset Sign (positive/negative)
///Positive: VDDCR_SOC Telemetry Current Offset is positive value\nNegative: VDDCR_SOC Telemetry Current Offset is negative value
typedef enum {
  IDSOPT_DBG_TELEMETRY_SOC_OFFSET_SIGN_POSITIVE = 0,///<Positive
  IDSOPT_DBG_TELEMETRY_SOC_OFFSET_SIGN_NEGATIVE = 1,///<Negative
} IDSOPT_DBG_TELEMETRY_SOC_OFFSET_SIGN;

///VDDCR_SOC Telemetry Offset Value (mA)
///Specify the VDDCR_SOC telemetry current slope [mA]
#define IDSOPT_DBG_TELEMETRY_SOC_OFFSET_MIN 0 ///< Min of VDDCR_SOC Telemetry Offset Value (mA)
#define IDSOPT_DBG_TELEMETRY_SOC_OFFSET_MAX 0xffffffff ///< Max of VDDCR_SOC Telemetry Offset Value (mA)

///AVFS Control
///Auto = Use the default AVFS coefficients\nManual = User can set customized AVFS coefficients
typedef enum {
  IDSOPT_DBG_AVFS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_AVFS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_AVFS_CTL;

///CorePsfFreq Sign
///Positive: CorePsfFreq value is positive value\nNegative: CorePsfFreq value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_FREQ_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_FREQ_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_FREQ_SIGN;

///CorePsfFreq
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_FREQ_MIN 0 ///< Min of CorePsfFreq
#define IDSOPT_DBG_AVFS_CORE_PSF_FREQ_MAX 0xffffffff ///< Max of CorePsfFreq

///CorePsfTemp Sign
///Positive: CorePsfTemp value is positive value\nNegative: CorePsfTemp value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_TEMP_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_TEMP_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_TEMP_SIGN;

///CorePsfTemp
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_TEMP_MIN 0 ///< Min of CorePsfTemp
#define IDSOPT_DBG_AVFS_CORE_PSF_TEMP_MAX 0xffffffff ///< Max of CorePsfTemp

///CorePsfSidd Sign
///Positive: CorePsfSidd value is positive value\nNegative: CorePsfSidd value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_SIDD_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_SIDD_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_SIDD_SIGN;

///CorePsfSidd
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_SIDD_MIN 0 ///< Min of CorePsfSidd
#define IDSOPT_DBG_AVFS_CORE_PSF_SIDD_MAX 0xffffffff ///< Max of CorePsfSidd

///CorePsfCac Sign
///Positive: CorePsfCac value is positive value\nNegative: CorePsfCac value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_CAC_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_CAC_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_CAC_SIGN;

///CorePsfCac
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_CAC_MIN 0 ///< Min of CorePsfCac
#define IDSOPT_DBG_AVFS_CORE_PSF_CAC_MAX 0xffffffff ///< Max of CorePsfCac

///CorePsfNumActiveCores Sign
///Positive: CorePsfNumActiveCores value is positive value\nNegative: CorePsfNumActiveCores value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_SIGN;

///CorePsfNumActiveCores
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_MIN 0 ///< Min of CorePsfNumActiveCores
#define IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_MAX 0xffffffff ///< Max of CorePsfNumActiveCores

///CorePsfOtherDie Sign
///Positive: CorePsfOtherDie value is positive value\nNegative: CorePsfOtherDie value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_OTHER_DIE_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_OTHER_DIE_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_OTHER_DIE_SIGN;

///CorePsfOtherDie
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_OTHER_DIE_MIN 0 ///< Min of CorePsfOtherDie
#define IDSOPT_DBG_AVFS_CORE_PSF_OTHER_DIE_MAX 0xffffffff ///< Max of CorePsfOtherDie

///CorePsfSigma Sign
///Positive: CorePsfSigma value is positive value\nNegative: CorePsfSigma value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_SIGN;

///CorePsfSigma
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_MIN 0 ///< Min of CorePsfSigma
#define IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_MAX 0xffffffff ///< Max of CorePsfSigma

///L3PsfFreq Sign
///Positive: L3PsfFreq value is positive value\nNegative: L3PsfFreq value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_FREQ_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_FREQ_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_FREQ_SIGN;

///L3PsfFreq
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_FREQ_MIN 0 ///< Min of L3PsfFreq
#define IDSOPT_DBG_AVFS_L3_PSF_FREQ_MAX 0xffffffff ///< Max of L3PsfFreq

///L3PsfTemp Sign
///Positive: L3PsfTemp value is positive value\nNegative: L3PsfTemp value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_TEMP_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_TEMP_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_TEMP_SIGN;

///L3PsfTemp
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_TEMP_MIN 0 ///< Min of L3PsfTemp
#define IDSOPT_DBG_AVFS_L3_PSF_TEMP_MAX 0xffffffff ///< Max of L3PsfTemp

///L3PsfSidd Sign
///Positive: L3PsfSidd value is positive value\nNegative: L3PsfSidd value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_SIDD_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_SIDD_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_SIDD_SIGN;

///L3PsfSidd
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_SIDD_MIN 0 ///< Min of L3PsfSidd
#define IDSOPT_DBG_AVFS_L3_PSF_SIDD_MAX 0xffffffff ///< Max of L3PsfSidd

///L3PsfCac Sign
///Positive: L3PsfCac value is positive value\nNegative: L3PsfCac value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_CAC_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_CAC_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_CAC_SIGN;

///L3PsfCac
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_CAC_MIN 0 ///< Min of L3PsfCac
#define IDSOPT_DBG_AVFS_L3_PSF_CAC_MAX 0xffffffff ///< Max of L3PsfCac

///L3PsfNumActiveCores Sign
///Positive: L3PsfNumActiveCores value is positive value\nNegative: L3PsfNumActiveCores value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_SIGN;

///L3PsfNumActiveCores
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_MIN 0 ///< Min of L3PsfNumActiveCores
#define IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_MAX 0xffffffff ///< Max of L3PsfNumActiveCores

///L3PsfOtherDie Sign
///Positive: L3PsfOtherDie value is positive value\nNegative: L3PsfOtherDie value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_OTHER_DIE_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_OTHER_DIE_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_OTHER_DIE_SIGN;

///L3PsfOtherDie
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_OTHER_DIE_MIN 0 ///< Min of L3PsfOtherDie
#define IDSOPT_DBG_AVFS_L3_PSF_OTHER_DIE_MAX 0xffffffff ///< Max of L3PsfOtherDie

///L3PsfSigma Sign
///Positive: L3PsfSigma value is positive value\nNegative: L3PsfSigma value is negative value
typedef enum {
  IDSOPT_DBG_AVFS_L3_PSF_SIGMA_SIGN_POSITIVE = 1,///<Positive
  IDSOPT_DBG_AVFS_L3_PSF_SIGMA_SIGN_NEGATIVE = 0,///<Negative
} IDSOPT_DBG_AVFS_L3_PSF_SIGMA_SIGN;

///L3PsfSigma
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_SIGMA_MIN 0 ///< Min of L3PsfSigma
#define IDSOPT_DBG_AVFS_L3_PSF_SIGMA_MAX 0xffffffff ///< Max of L3PsfSigma

///xGMI Link Width Control
///Auto = Use default xGMI link width controller settings\nManual = User can set custom xGMI link width controller settings
typedef enum {
  IDSOPT_DBGX_GMI_LINK_WIDTH_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBGX_GMI_LINK_WIDTH_CTL_AUTO = 0,///<Auto
} IDSOPT_DBGX_GMI_LINK_WIDTH_CTL;

///xGMI Force Link Width Control
///Unforce = Do not force the xGMI to a fixed width\nForce = Force the xGMI link to the user specified width
typedef enum {
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_CTL_UNFORCE = 0,///<Unforce
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_CTL_FORCE = 1,///<Force
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_CTL_AUTO = 0xf,///<Auto
} IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_CTL;

///xGMI Force Link Width
///0 = Force xGMI link width to x2\n1 = Force xGMI link width to x8\n2 = Force xGMI link width to x16
typedef enum {
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_0 = 0,///<0
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_1 = 1,///<1
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_2 = 2,///<2
  IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH_AUTO = 0xf,///<Auto
} IDSOPT_DBGX_GMI_FORCE_LINK_WIDTH;

///xGMI Max Link Width Control
///Auto = Use default xGMI max supported link width\nManual = User can set custom xGMI max link width
typedef enum {
  IDSOPT_DBGX_GMI_MAX_LINK_WIDTH_CTL_AUTO = 0,///<Auto
  IDSOPT_DBGX_GMI_MAX_LINK_WIDTH_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBGX_GMI_MAX_LINK_WIDTH_CTL;

///xGMI Max Link Width
///0 = Set max xGMI link width to x8\n1 = Set max xGMI link width to x16
typedef enum {
  IDSOPT_DBGX_GMI_MAX_LINK_WIDTH_0 = 0,///<0
  IDSOPT_DBGX_GMI_MAX_LINK_WIDTH_1 = 1,///<1
  IDSOPT_DBGX_GMI_MAX_LINK_WIDTH_AUTO = 0xf,///<Auto
} IDSOPT_DBGX_GMI_MAX_LINK_WIDTH;

///GRA Group 1
///Enable or disable GRA Group 1
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A1_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A1_USR_CTL;

///GRA1 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A1_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A1_REG_TYPE;

///GRA1 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A1_TIME_POINT;

///GRA1 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A1_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A1_GEN_REG_NODE;

///GRA1 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A1_BUS_MIN 0 ///< Min of GRA1 Bus
#define IDSOPT_DBG_MISC_GR_A1_BUS_MAX 255 ///< Max of GRA1 Bus

///GRA1 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A1_DEV_MIN 0 ///< Min of GRA1 Device
#define IDSOPT_DBG_MISC_GR_A1_DEV_MAX 31 ///< Max of GRA1 Device

///GRA1 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A1_FUN_MIN 0 ///< Min of GRA1 Function
#define IDSOPT_DBG_MISC_GR_A1_FUN_MAX 7 ///< Max of GRA1 Function

///GRA1 Offset
///If type=PCIIndirectReg, this offset specify the dataport. e.g. F0x64_12, x64 is the dataport
#define IDSOPT_DBG_MISC_GR_A1_OFFSET_MIN 0 ///< Min of GRA1 Offset
#define IDSOPT_DBG_MISC_GR_A1_OFFSET_MAX 0xfff ///< Max of GRA1 Offset

///GRA1 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A1_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A1_CORES;

///GRA1 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A1_NODE_MIN 0 ///< Min of GRA1 Node
#define IDSOPT_DBG_MISC_GR_A1_NODE_MAX 255 ///< Max of GRA1 Node

///GRA1 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A1_CORE_MIN 0 ///< Min of GRA1 Core
#define IDSOPT_DBG_MISC_GR_A1_CORE_MAX 127 ///< Max of GRA1 Core

///GRA1 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_MSR_HIGH_MIN 0 ///< Min of GRA1 MSR Address High
#define IDSOPT_DBG_MISC_GR_A1_MSR_HIGH_MAX 0xffff ///< Max of GRA1 MSR Address High

///GRA1 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_MSR_LOW_MIN 0 ///< Min of GRA1 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A1_MSR_LOW_MAX 0xffff ///< Max of GRA1 MSR Address Low

///GRA1 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A1_MMIO_HIGH_MIN 0 ///< Min of GRA1 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A1_MMIO_HIGH_MAX 0xffff ///< Max of GRA1 MMIO Address High

///GRA1 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A1_MMIO_LOW_MIN 0 ///< Min of GRA1 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A1_MMIO_LOW_MAX 0xffff ///< Max of GRA1 MMIO Address Low

///GRA1 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA1 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA1 PCI Indirect Register Offset[31:16]

///GRA1 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA1 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA1 PCI Indirect Register Offset[15:0]

///GRA1 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A1_PCI_INDIRECT_REG_WE_BIT;

///GRA1 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA1 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA1 GMMX Offset[31:16]

///GRA1 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_LOW_MIN 0 ///< Min of GRA1 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A1_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA1 GMMX Offset[15:0]

///GRA1 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_SMN_HIGH_MIN 0 ///< Min of GRA1 SMN Address High
#define IDSOPT_DBG_MISC_GR_A1_SMN_HIGH_MAX 0xffff ///< Max of GRA1 SMN Address High

///GRA1 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_SMN_LOW_MIN 0 ///< Min of GRA1 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A1_SMN_LOW_MAX 0xffff ///< Max of GRA1 SMN Address Low

///GRA1 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A1_DF_INSTANCE_MIN 0 ///< Min of GRA1 DF Instance
#define IDSOPT_DBG_MISC_GR_A1_DF_INSTANCE_MAX 0xff ///< Max of GRA1 DF Instance

///GRA1 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHEST_MIN 0 ///< Min of GRA1 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHEST_MAX 0xffff ///< Max of GRA1 Mask Value [63:48]

///GRA1 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHER_MIN 0 ///< Min of GRA1 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A1_AND_HIGHER_MAX 0xffff ///< Max of GRA1 Mask Value [47:32]

///GRA1 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWER_MIN 0 ///< Min of GRA1 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWER_MAX 0xffff ///< Max of GRA1 Mask Value [31:16]

///GRA1 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWEST_MIN 0 ///< Min of GRA1 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A1_AND_LOWEST_MAX 0xffff ///< Max of GRA1 Mask Value [15:0]

///GRA1 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHEST_MIN 0 ///< Min of GRA1 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHEST_MAX 0xffff ///< Max of GRA1 Or Value [63:48]

///GRA1 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHER_MIN 0 ///< Min of GRA1 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A1_OR_HIGHER_MAX 0xffff ///< Max of GRA1 Or Value [47:32]

///GRA1 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWER_MIN 0 ///< Min of GRA1 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWER_MAX 0xffff ///< Max of GRA1 Or Value [31:16]

///GRA1 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWEST_MIN 0 ///< Min of GRA1 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A1_OR_LOWEST_MAX 0xffff ///< Max of GRA1 Or Value [15:0]

///GRA Group 2
///Enable or disable GRA Group 2
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A2_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A2_USR_CTL;

///GRA2 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A2_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A2_REG_TYPE;

///GRA2 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A2_TIME_POINT;

///GRA2 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A2_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A2_GEN_REG_NODE;

///GRA2 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A2_BUS_MIN 0 ///< Min of GRA2 Bus
#define IDSOPT_DBG_MISC_GR_A2_BUS_MAX 255 ///< Max of GRA2 Bus

///GRA2 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A2_DEV_MIN 0 ///< Min of GRA2 Device
#define IDSOPT_DBG_MISC_GR_A2_DEV_MAX 31 ///< Max of GRA2 Device

///GRA2 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A2_FUN_MIN 0 ///< Min of GRA2 Function
#define IDSOPT_DBG_MISC_GR_A2_FUN_MAX 7 ///< Max of GRA2 Function

///GRA2 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A2_OFFSET_MIN 0 ///< Min of GRA2 Offset
#define IDSOPT_DBG_MISC_GR_A2_OFFSET_MAX 0xfff ///< Max of GRA2 Offset

///GRA2 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A2_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A2_CORES;

///GRA2 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A2_NODE_MIN 0 ///< Min of GRA2 Node
#define IDSOPT_DBG_MISC_GR_A2_NODE_MAX 255 ///< Max of GRA2 Node

///GRA2 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A2_CORE_MIN 0 ///< Min of GRA2 Core
#define IDSOPT_DBG_MISC_GR_A2_CORE_MAX 127 ///< Max of GRA2 Core

///GRA2 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_MSR_HIGH_MIN 0 ///< Min of GRA2 MSR Address High
#define IDSOPT_DBG_MISC_GR_A2_MSR_HIGH_MAX 0xffff ///< Max of GRA2 MSR Address High

///GRA2 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_MSR_LOW_MIN 0 ///< Min of GRA2 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A2_MSR_LOW_MAX 0xffff ///< Max of GRA2 MSR Address Low

///GRA2 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A2_MMIO_HIGH_MIN 0 ///< Min of GRA2 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A2_MMIO_HIGH_MAX 0xffff ///< Max of GRA2 MMIO Address High

///GRA2 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A2_MMIO_LOW_MIN 0 ///< Min of GRA2 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A2_MMIO_LOW_MAX 0xffff ///< Max of GRA2 MMIO Address Low

///GRA2 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA2 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA2 PCI Indirect Register Offset[31:16]

///GRA2 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA2 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA2 PCI Indirect Register Offset[15:0]

///GRA2 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A2_PCI_INDIRECT_REG_WE_BIT;

///GRA2 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA2 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA2 GMMX Offset[31:16]

///GRA2 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_LOW_MIN 0 ///< Min of GRA2 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A2_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA2 GMMX Offset[15:0]

///GRA2 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_SMN_HIGH_MIN 0 ///< Min of GRA2 SMN Address High
#define IDSOPT_DBG_MISC_GR_A2_SMN_HIGH_MAX 0xffff ///< Max of GRA2 SMN Address High

///GRA2 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_SMN_LOW_MIN 0 ///< Min of GRA2 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A2_SMN_LOW_MAX 0xffff ///< Max of GRA2 SMN Address Low

///GRA2 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A2_DF_INSTANCE_MIN 0 ///< Min of GRA2 DF Instance
#define IDSOPT_DBG_MISC_GR_A2_DF_INSTANCE_MAX 0xff ///< Max of GRA2 DF Instance

///GRA2 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHEST_MIN 0 ///< Min of GRA2 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHEST_MAX 0xffff ///< Max of GRA2 Mask Value [63:48]

///GRA2 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHER_MIN 0 ///< Min of GRA2 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A2_AND_HIGHER_MAX 0xffff ///< Max of GRA2 Mask Value [47:32]

///GRA2 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWER_MIN 0 ///< Min of GRA2 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWER_MAX 0xffff ///< Max of GRA2 Mask Value [31:16]

///GRA2 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWEST_MIN 0 ///< Min of GRA2 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A2_AND_LOWEST_MAX 0xffff ///< Max of GRA2 Mask Value [15:0]

///GRA2 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHEST_MIN 0 ///< Min of GRA2 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHEST_MAX 0xffff ///< Max of GRA2 Or Value [63:48]

///GRA2 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHER_MIN 0 ///< Min of GRA2 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A2_OR_HIGHER_MAX 0xffff ///< Max of GRA2 Or Value [47:32]

///GRA2 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWER_MIN 0 ///< Min of GRA2 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWER_MAX 0xffff ///< Max of GRA2 Or Value [31:16]

///GRA2 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWEST_MIN 0 ///< Min of GRA2 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A2_OR_LOWEST_MAX 0xffff ///< Max of GRA2 Or Value [15:0]

///GRA Group 3
///Enable or disable GRA Group 3
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A3_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A3_USR_CTL;

///GRA3 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A3_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A3_REG_TYPE;

///GRA3 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A3_TIME_POINT;

///GRA3 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A3_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A3_GEN_REG_NODE;

///GRA3 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A3_BUS_MIN 0 ///< Min of GRA3 Bus
#define IDSOPT_DBG_MISC_GR_A3_BUS_MAX 255 ///< Max of GRA3 Bus

///GRA3 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A3_DEV_MIN 0 ///< Min of GRA3 Device
#define IDSOPT_DBG_MISC_GR_A3_DEV_MAX 31 ///< Max of GRA3 Device

///GRA3 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A3_FUN_MIN 0 ///< Min of GRA3 Function
#define IDSOPT_DBG_MISC_GR_A3_FUN_MAX 7 ///< Max of GRA3 Function

///GRA3 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A3_OFFSET_MIN 0 ///< Min of GRA3 Offset
#define IDSOPT_DBG_MISC_GR_A3_OFFSET_MAX 0xfff ///< Max of GRA3 Offset

///GRA3 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A3_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A3_CORES;

///GRA3 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A3_NODE_MIN 0 ///< Min of GRA3 Node
#define IDSOPT_DBG_MISC_GR_A3_NODE_MAX 255 ///< Max of GRA3 Node

///GRA3 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A3_CORE_MIN 0 ///< Min of GRA3 Core
#define IDSOPT_DBG_MISC_GR_A3_CORE_MAX 127 ///< Max of GRA3 Core

///GRA3 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_MSR_HIGH_MIN 0 ///< Min of GRA3 MSR Address High
#define IDSOPT_DBG_MISC_GR_A3_MSR_HIGH_MAX 0xffff ///< Max of GRA3 MSR Address High

///GRA3 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_MSR_LOW_MIN 0 ///< Min of GRA3 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A3_MSR_LOW_MAX 0xffff ///< Max of GRA3 MSR Address Low

///GRA3 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A3_MMIO_HIGH_MIN 0 ///< Min of GRA3 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A3_MMIO_HIGH_MAX 0xffff ///< Max of GRA3 MMIO Address High

///GRA3 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A3_MMIO_LOW_MIN 0 ///< Min of GRA3 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A3_MMIO_LOW_MAX 0xffff ///< Max of GRA3 MMIO Address Low

///GRA3 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA3 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA3 PCI Indirect Register Offset[31:16]

///GRA3 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA3 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA3 PCI Indirect Register Offset[15:0]

///GRA3 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A3_PCI_INDIRECT_REG_WE_BIT;

///GRA3 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA3 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA3 GMMX Offset[31:16]

///GRA3 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_LOW_MIN 0 ///< Min of GRA3 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A3_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA3 GMMX Offset[15:0]

///GRA3 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_SMN_HIGH_MIN 0 ///< Min of GRA3 SMN Address High
#define IDSOPT_DBG_MISC_GR_A3_SMN_HIGH_MAX 0xffff ///< Max of GRA3 SMN Address High

///GRA3 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_SMN_LOW_MIN 0 ///< Min of GRA3 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A3_SMN_LOW_MAX 0xffff ///< Max of GRA3 SMN Address Low

///GRA3 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A3_DF_INSTANCE_MIN 0 ///< Min of GRA3 DF Instance
#define IDSOPT_DBG_MISC_GR_A3_DF_INSTANCE_MAX 0xff ///< Max of GRA3 DF Instance

///GRA3 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHEST_MIN 0 ///< Min of GRA3 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHEST_MAX 0xffff ///< Max of GRA3 Mask Value [63:48]

///GRA3 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHER_MIN 0 ///< Min of GRA3 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A3_AND_HIGHER_MAX 0xffff ///< Max of GRA3 Mask Value [47:32]

///GRA3 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWER_MIN 0 ///< Min of GRA3 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWER_MAX 0xffff ///< Max of GRA3 Mask Value [31:16]

///GRA3 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWEST_MIN 0 ///< Min of GRA3 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A3_AND_LOWEST_MAX 0xffff ///< Max of GRA3 Mask Value [15:0]

///GRA3 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHEST_MIN 0 ///< Min of GRA3 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHEST_MAX 0xffff ///< Max of GRA3 Or Value [63:48]

///GRA3 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHER_MIN 0 ///< Min of GRA3 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A3_OR_HIGHER_MAX 0xffff ///< Max of GRA3 Or Value [47:32]

///GRA3 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWER_MIN 0 ///< Min of GRA3 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWER_MAX 0xffff ///< Max of GRA3 Or Value [31:16]

///GRA3 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWEST_MIN 0 ///< Min of GRA3 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A3_OR_LOWEST_MAX 0xffff ///< Max of GRA3 Or Value [15:0]

///GRA Group 4
///Enable or disable GRA Group 4
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A4_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A4_USR_CTL;

///GRA4 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A4_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A4_REG_TYPE;

///GRA4 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A4_TIME_POINT;

///GRA4 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A4_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A4_GEN_REG_NODE;

///GRA4 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A4_BUS_MIN 0 ///< Min of GRA4 Bus
#define IDSOPT_DBG_MISC_GR_A4_BUS_MAX 255 ///< Max of GRA4 Bus

///GRA4 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A4_DEV_MIN 0 ///< Min of GRA4 Device
#define IDSOPT_DBG_MISC_GR_A4_DEV_MAX 31 ///< Max of GRA4 Device

///GRA4 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A4_FUN_MIN 0 ///< Min of GRA4 Function
#define IDSOPT_DBG_MISC_GR_A4_FUN_MAX 7 ///< Max of GRA4 Function

///GRA4 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A4_OFFSET_MIN 0 ///< Min of GRA4 Offset
#define IDSOPT_DBG_MISC_GR_A4_OFFSET_MAX 0xfff ///< Max of GRA4 Offset

///GRA4 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A4_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A4_CORES;

///GRA4 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A4_NODE_MIN 0 ///< Min of GRA4 Node
#define IDSOPT_DBG_MISC_GR_A4_NODE_MAX 255 ///< Max of GRA4 Node

///GRA4 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A4_CORE_MIN 0 ///< Min of GRA4 Core
#define IDSOPT_DBG_MISC_GR_A4_CORE_MAX 127 ///< Max of GRA4 Core

///GRA4 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_MSR_HIGH_MIN 0 ///< Min of GRA4 MSR Address High
#define IDSOPT_DBG_MISC_GR_A4_MSR_HIGH_MAX 0xffff ///< Max of GRA4 MSR Address High

///GRA4 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_MSR_LOW_MIN 0 ///< Min of GRA4 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A4_MSR_LOW_MAX 0xffff ///< Max of GRA4 MSR Address Low

///GRA4 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A4_MMIO_HIGH_MIN 0 ///< Min of GRA4 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A4_MMIO_HIGH_MAX 0xffff ///< Max of GRA4 MMIO Address High

///GRA4 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A4_MMIO_LOW_MIN 0 ///< Min of GRA4 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A4_MMIO_LOW_MAX 0xffff ///< Max of GRA4 MMIO Address Low

///GRA4 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA4 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA4 PCI Indirect Register Offset[31:16]

///GRA4 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA4 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA4 PCI Indirect Register Offset[15:0]

///GRA4 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A4_PCI_INDIRECT_REG_WE_BIT;

///GRA4 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA4 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA4 GMMX Offset[31:16]

///GRA4 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_LOW_MIN 0 ///< Min of GRA4 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A4_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA4 GMMX Offset[15:0]

///GRA4 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_SMN_HIGH_MIN 0 ///< Min of GRA4 SMN Address High
#define IDSOPT_DBG_MISC_GR_A4_SMN_HIGH_MAX 0xffff ///< Max of GRA4 SMN Address High

///GRA4 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_SMN_LOW_MIN 0 ///< Min of GRA4 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A4_SMN_LOW_MAX 0xffff ///< Max of GRA4 SMN Address Low

///GRA4 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A4_DF_INSTANCE_MIN 0 ///< Min of GRA4 DF Instance
#define IDSOPT_DBG_MISC_GR_A4_DF_INSTANCE_MAX 0xff ///< Max of GRA4 DF Instance

///GRA4 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHEST_MIN 0 ///< Min of GRA4 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHEST_MAX 0xffff ///< Max of GRA4 Mask Value [63:48]

///GRA4 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHER_MIN 0 ///< Min of GRA4 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A4_AND_HIGHER_MAX 0xffff ///< Max of GRA4 Mask Value [47:32]

///GRA4 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWER_MIN 0 ///< Min of GRA4 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWER_MAX 0xffff ///< Max of GRA4 Mask Value [31:16]

///GRA4 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWEST_MIN 0 ///< Min of GRA4 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A4_AND_LOWEST_MAX 0xffff ///< Max of GRA4 Mask Value [15:0]

///GRA4 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHEST_MIN 0 ///< Min of GRA4 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHEST_MAX 0xffff ///< Max of GRA4 Or Value [63:48]

///GRA4 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHER_MIN 0 ///< Min of GRA4 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A4_OR_HIGHER_MAX 0xffff ///< Max of GRA4 Or Value [47:32]

///GRA4 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWER_MIN 0 ///< Min of GRA4 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWER_MAX 0xffff ///< Max of GRA4 Or Value [31:16]

///GRA4 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWEST_MIN 0 ///< Min of GRA4 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A4_OR_LOWEST_MAX 0xffff ///< Max of GRA4 Or Value [15:0]

///GRA Group 5
///Enable or disable GRA Group 5
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A5_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A5_USR_CTL;

///GRA5 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A5_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A5_REG_TYPE;

///GRA5 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A5_TIME_POINT;

///GRA5 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A5_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A5_GEN_REG_NODE;

///GRA5 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A5_BUS_MIN 0 ///< Min of GRA5 Bus
#define IDSOPT_DBG_MISC_GR_A5_BUS_MAX 255 ///< Max of GRA5 Bus

///GRA5 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A5_DEV_MIN 0 ///< Min of GRA5 Device
#define IDSOPT_DBG_MISC_GR_A5_DEV_MAX 31 ///< Max of GRA5 Device

///GRA5 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A5_FUN_MIN 0 ///< Min of GRA5 Function
#define IDSOPT_DBG_MISC_GR_A5_FUN_MAX 7 ///< Max of GRA5 Function

///GRA5 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A5_OFFSET_MIN 0 ///< Min of GRA5 Offset
#define IDSOPT_DBG_MISC_GR_A5_OFFSET_MAX 0xfff ///< Max of GRA5 Offset

///GRA5 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A5_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A5_CORES;

///GRA5 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A5_NODE_MIN 0 ///< Min of GRA5 Node
#define IDSOPT_DBG_MISC_GR_A5_NODE_MAX 255 ///< Max of GRA5 Node

///GRA5 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A5_CORE_MIN 0 ///< Min of GRA5 Core
#define IDSOPT_DBG_MISC_GR_A5_CORE_MAX 127 ///< Max of GRA5 Core

///GRA5 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_MSR_HIGH_MIN 0 ///< Min of GRA5 MSR Address High
#define IDSOPT_DBG_MISC_GR_A5_MSR_HIGH_MAX 0xffff ///< Max of GRA5 MSR Address High

///GRA5 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_MSR_LOW_MIN 0 ///< Min of GRA5 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A5_MSR_LOW_MAX 0xffff ///< Max of GRA5 MSR Address Low

///GRA5 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A5_MMIO_HIGH_MIN 0 ///< Min of GRA5 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A5_MMIO_HIGH_MAX 0xffff ///< Max of GRA5 MMIO Address High

///GRA5 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A5_MMIO_LOW_MIN 0 ///< Min of GRA5 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A5_MMIO_LOW_MAX 0xffff ///< Max of GRA5 MMIO Address Low

///GRA5 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA5 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA5 PCI Indirect Register Offset[31:16]

///GRA5 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA5 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA5 PCI Indirect Register Offset[15:0]

///GRA5 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A5_PCI_INDIRECT_REG_WE_BIT;

///GRA5 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA5 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA5 GMMX Offset[31:16]

///GRA5 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_LOW_MIN 0 ///< Min of GRA5 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A5_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA5 GMMX Offset[15:0]

///GRA5 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_SMN_HIGH_MIN 0 ///< Min of GRA5 SMN Address High
#define IDSOPT_DBG_MISC_GR_A5_SMN_HIGH_MAX 0xffff ///< Max of GRA5 SMN Address High

///GRA5 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_SMN_LOW_MIN 0 ///< Min of GRA5 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A5_SMN_LOW_MAX 0xffff ///< Max of GRA5 SMN Address Low

///GRA5 DF Instance
///Enter the instance ID of the of the fabric device to apply the setting to, or 0xFF for broadcast.  Note that standard PCI can alternatively be used for broadcast.
#define IDSOPT_DBG_MISC_GR_A5_DF_INSTANCE_MIN 0 ///< Min of GRA5 DF Instance
#define IDSOPT_DBG_MISC_GR_A5_DF_INSTANCE_MAX 0xff ///< Max of GRA5 DF Instance

///GRA5 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHEST_MIN 0 ///< Min of GRA5 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHEST_MAX 0xffff ///< Max of GRA5 Mask Value [63:48]

///GRA5 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHER_MIN 0 ///< Min of GRA5 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A5_AND_HIGHER_MAX 0xffff ///< Max of GRA5 Mask Value [47:32]

///GRA5 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWER_MIN 0 ///< Min of GRA5 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWER_MAX 0xffff ///< Max of GRA5 Mask Value [31:16]

///GRA5 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWEST_MIN 0 ///< Min of GRA5 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A5_AND_LOWEST_MAX 0xffff ///< Max of GRA5 Mask Value [15:0]

///GRA5 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHEST_MIN 0 ///< Min of GRA5 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHEST_MAX 0xffff ///< Max of GRA5 Or Value [63:48]

///GRA5 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHER_MIN 0 ///< Min of GRA5 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A5_OR_HIGHER_MAX 0xffff ///< Max of GRA5 Or Value [47:32]

///GRA5 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWER_MIN 0 ///< Min of GRA5 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWER_MAX 0xffff ///< Max of GRA5 Or Value [31:16]

///GRA5 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWEST_MIN 0 ///< Min of GRA5 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A5_OR_LOWEST_MAX 0xffff ///< Max of GRA5 Or Value [15:0]

///GRA Group 6
///Enable or disable GRA Group 6
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_USR_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MISC_GR_A6_USR_CTL_ENABLED = 1,///<Enabled
} IDSOPT_DBG_MISC_GR_A6_USR_CTL;

///GRA6 Register Type
///Type of register, includes PCI, MSR or MMIO
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_PCI = 0,///<PCI
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_MSR = 1,///<MSR
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_MMIO = 2,///<MMIO
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_PCIINDIRECT = 3,///<PCI Indirect
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_GMMX = 4,///<GMMX
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_SMN = 5,///<SMN
  IDSOPT_DBG_MISC_GR_A6_REG_TYPE_DF = 6,///<DF
} IDSOPT_DBG_MISC_GR_A6_REG_TYPE;

///GRA6 When to Write
///When to modify the value specified by this option
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_VERYEARLYAFTERRESET = 0,///<Very Early - After Reset
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_LATEBEFOREPCIINIT = 2,///<Late - Before PCI Init
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_VERYLATEBEFOREOSBOOT = 3,///<Very Late - Before OS Boot
} IDSOPT_DBG_MISC_GR_A6_TIME_POINT;

///GRA6 Gen Reg Node
///Applied to all nodes or a single node
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_GEN_REG_NODE_ALLNODES = 0,///<All Nodes
  IDSOPT_DBG_MISC_GR_A6_GEN_REG_NODE_ENTERBUS_DEVICE = 1,///<Enter Bus_Device
} IDSOPT_DBG_MISC_GR_A6_GEN_REG_NODE;

///GRA6 Bus
///Decide whether this generic option should be applied to all buses or a single bus
#define IDSOPT_DBG_MISC_GR_A6_BUS_MIN 0 ///< Min of GRA6 Bus
#define IDSOPT_DBG_MISC_GR_A6_BUS_MAX 255 ///< Max of GRA6 Bus

///GRA6 Device
///Applied to all devices or a single device
#define IDSOPT_DBG_MISC_GR_A6_DEV_MIN 0 ///< Min of GRA6 Device
#define IDSOPT_DBG_MISC_GR_A6_DEV_MAX 31 ///< Max of GRA6 Device

///GRA6 Function
///This is to select the function of register to set
#define IDSOPT_DBG_MISC_GR_A6_FUN_MIN 0 ///< Min of GRA6 Function
#define IDSOPT_DBG_MISC_GR_A6_FUN_MAX 7 ///< Max of GRA6 Function

///GRA6 Offset
///Offset
#define IDSOPT_DBG_MISC_GR_A6_OFFSET_MIN 0 ///< Min of GRA6 Offset
#define IDSOPT_DBG_MISC_GR_A6_OFFSET_MAX 0xfff ///< Max of GRA6 Offset

///GRA6 Gen Reg Core
///Decide whether this generic option should be applied to all cores or a single core
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_CORES_ALLCORES = 0,///<All Cores
  IDSOPT_DBG_MISC_GR_A6_CORES_SPECIFYNODE_CORE = 1,///<Specify Node_Core
} IDSOPT_DBG_MISC_GR_A6_CORES;

///GRA6 Node
///Decide whether this generic option should be applied to specify node
#define IDSOPT_DBG_MISC_GR_A6_NODE_MIN 0 ///< Min of GRA6 Node
#define IDSOPT_DBG_MISC_GR_A6_NODE_MAX 255 ///< Max of GRA6 Node

///GRA6 Core
///Decide whether this generic option should be applied to specify core
#define IDSOPT_DBG_MISC_GR_A6_CORE_MIN 0 ///< Min of GRA6 Core
#define IDSOPT_DBG_MISC_GR_A6_CORE_MAX 127 ///< Max of GRA6 Core

///GRA6 MSR Address High
///This is to input the MSR address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_MSR_HIGH_MIN 0 ///< Min of GRA6 MSR Address High
#define IDSOPT_DBG_MISC_GR_A6_MSR_HIGH_MAX 0xffff ///< Max of GRA6 MSR Address High

///GRA6 MSR Address Low
///This is to input the MSR address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_MSR_LOW_MIN 0 ///< Min of GRA6 MSR Address Low
#define IDSOPT_DBG_MISC_GR_A6_MSR_LOW_MAX 0xffff ///< Max of GRA6 MSR Address Low

///GRA6 MMIO Address High
///This is to input the MMIO address [31:16]
#define IDSOPT_DBG_MISC_GR_A6_MMIO_HIGH_MIN 0 ///< Min of GRA6 MMIO Address High
#define IDSOPT_DBG_MISC_GR_A6_MMIO_HIGH_MAX 0xffff ///< Max of GRA6 MMIO Address High

///GRA6 MMIO Address Low
///This is to input the MMIO address [15:0]
#define IDSOPT_DBG_MISC_GR_A6_MMIO_LOW_MIN 0 ///< Min of GRA6 MMIO Address Low
#define IDSOPT_DBG_MISC_GR_A6_MMIO_LOW_MAX 0xffff ///< Max of GRA6 MMIO Address Low

///GRA6 PCI Indirect Register Offset[31:16]
///High portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 E030 is the high portion
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_HIGH_MIN 0 ///< Min of GRA6 PCI Indirect Register Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_HIGH_MAX 0xffff ///< Max of GRA6 PCI Indirect Register Offset[31:16]

///GRA6 PCI Indirect Register Offset[15:0]
///Low portion of PCI Indirect Register Offset. e.g. D0F0xBC_xE03000A8 00a8 is the Low portion
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_LOW_MIN 0 ///< Min of GRA6 PCI Indirect Register Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_OFF_LOW_MAX 0xffff ///< Max of GRA6 PCI Indirect Register Offset[15:0]

///GRA6 PCI Indirect Register Write Enable Bit
///Some PCI Indirect Register need set WriteEnable bit before write
typedef enum {
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT0 = 0,///<Bit0
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT2 = 2,///<Bit2
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT3 = 3,///<Bit3
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT4 = 4,///<Bit4
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT5 = 5,///<Bit5
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT1 = 1,///<Bit1
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT6 = 6,///<Bit6
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT7 = 7,///<Bit7
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT8 = 8,///<Bit8
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT9 = 9,///<Bit9
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT10 = 10,///<Bit10
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT11 = 11,///<Bit11
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT12 = 12,///<Bit12
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT13 = 13,///<Bit13
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT14 = 14,///<Bit14
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT15 = 15,///<Bit15
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT16 = 16,///<Bit16
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT17 = 17,///<Bit17
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT18 = 18,///<Bit18
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT19 = 19,///<Bit19
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT20 = 20,///<Bit20
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT21 = 21,///<Bit21
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT22 = 22,///<Bit22
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT23 = 23,///<Bit23
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT24 = 24,///<Bit24
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT25 = 25,///<Bit25
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT26 = 26,///<Bit26
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT27 = 27,///<Bit27
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT28 = 28,///<Bit28
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT29 = 29,///<Bit29
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT30 = 30,///<Bit30
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_BIT31 = 31,///<Bit31
  IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MISC_GR_A6_PCI_INDIRECT_REG_WE_BIT;

///GRA6 GMMX Offset[31:16]
///High portion of GMMX register e.g. GMMX12345678 1234 is the high portion
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_HIGH_MIN 0 ///< Min of GRA6 GMMX Offset[31:16]
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_HIGH_MAX 0xffff ///< Max of GRA6 GMMX Offset[31:16]

///GRA6 GMMX Offset[15:0]
///Low portion of GMMX register e.g. GMMX12345678 1234 is the low portion
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_LOW_MIN 0 ///< Min of GRA6 GMMX Offset[15:0]
#define IDSOPT_DBG_MISC_GR_A6_GMMX_OFF_LOW_MAX 0xffff ///< Max of GRA6 GMMX Offset[15:0]

///GRA6 SMN Address High
///This is to input the SMN address of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_SMN_HIGH_MIN 0 ///< Min of GRA6 SMN Address High
#define IDSOPT_DBG_MISC_GR_A6_SMN_HIGH_MAX 0xffff ///< Max of GRA6 SMN Address High

///GRA6 SMN Address Low
///This is to input the SMN address of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_SMN_LOW_MIN 0 ///< Min of GRA6 SMN Address Low
#define IDSOPT_DBG_MISC_GR_A6_SMN_LOW_MAX 0xffff ///< Max of GRA6 SMN Address Low

///GRA6 DF Instance
#define IDSOPT_DBG_MISC_GR_A6_DF_INSTANCE_MIN 0 ///< Min of GRA6 DF Instance
#define IDSOPT_DBG_MISC_GR_A6_DF_INSTANCE_MAX 0xff ///< Max of GRA6 DF Instance

///GRA6 Mask Value [63:48]
///This is to input the mask value of register to setMask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHEST_MIN 0 ///< Min of GRA6 Mask Value [63:48]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHEST_MAX 0xffff ///< Max of GRA6 Mask Value [63:48]

///GRA6 Mask Value [47:32]
///This is to input the mask value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHER_MIN 0 ///< Min of GRA6 Mask Value [47:32]
#define IDSOPT_DBG_MISC_GR_A6_AND_HIGHER_MAX 0xffff ///< Max of GRA6 Mask Value [47:32]

///GRA6 Mask Value [31:16]
///This is to input the mask value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWER_MIN 0 ///< Min of GRA6 Mask Value [31:16]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWER_MAX 0xffff ///< Max of GRA6 Mask Value [31:16]

///GRA6 Mask Value [15:0]
///This is to input the mask value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWEST_MIN 0 ///< Min of GRA6 Mask Value [15:0]
#define IDSOPT_DBG_MISC_GR_A6_AND_LOWEST_MAX 0xffff ///< Max of GRA6 Mask Value [15:0]

///GRA6 Or Value [63:48]
///This is to input the Or value of register to set [63:48]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHEST_MIN 0 ///< Min of GRA6 Or Value [63:48]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHEST_MAX 0xffff ///< Max of GRA6 Or Value [63:48]

///GRA6 Or Value [47:32]
///This is to input the Or value of register to set [47:32]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHER_MIN 0 ///< Min of GRA6 Or Value [47:32]
#define IDSOPT_DBG_MISC_GR_A6_OR_HIGHER_MAX 0xffff ///< Max of GRA6 Or Value [47:32]

///GRA6 Or Value [31:16]
///This is to input the Or value of register to set [31:16]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWER_MIN 0 ///< Min of GRA6 Or Value [31:16]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWER_MAX 0xffff ///< Max of GRA6 Or Value [31:16]

///GRA6 Or Value [15:0]
///This is to input the Or value of register to set [15:0]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWEST_MIN 0 ///< Min of GRA6 Or Value [15:0]
#define IDSOPT_DBG_MISC_GR_A6_OR_LOWEST_MAX 0xffff ///< Max of GRA6 Or Value [15:0]


#endif //_IDS_NV_INT_DEF_ZP_H_
