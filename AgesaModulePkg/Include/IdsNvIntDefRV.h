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

#ifndef _IDS_NV_INT_DEF_RV_H_
#define _IDS_NV_INT_DEF_RV_H_

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

///Memory Holes at 2G and 5G (512MB)
///Allocate 512MB memory holes at 2G and 5G
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CPU_GEN_MEM_HOLE_AT2_GAND5_G;

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
///Control LS_CFG[LsCfgDisSpecLockMap]
typedef enum {
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_SPEC_LOCK_MAP_DIS;

///Disable uop Cache
///Control IC_CFG[IcCfgDisOc]
typedef enum {
  IDSOPT_DBG_CPU_GEN_UOP_CACHE_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_UOP_CACHE_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_UOP_CACHE_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_UOP_CACHE_DIS;

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

///Disable L1 Stream HW Prefetcher
///Control DC_CFG[DisStreamHwPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L1_STREAM_HW_PRE_F_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L1_STREAM_HW_PRE_F_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L1_STREAM_HW_PRE_F_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L1_STREAM_HW_PRE_F_DIS;

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

///L2 Stream Prefetcher
///Control L2_PFCFG[EnableStreamPf]
typedef enum {
  IDSOPT_DBG_CPU_GEN_L2_STREAM_PF_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_L2_STREAM_PF_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_L2_STREAM_PF_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_L2_STREAM_PF;

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

///FP_CFG: MSC_CAC_TH
///Control FP_CFG[MSC_CAC_TH]
#define IDSOPT_DBG_CPU_GEN_MSC_CAC_TH_MIN 0 ///< Min of FP_CFG: MSC_CAC_TH
#define IDSOPT_DBG_CPU_GEN_MSC_CAC_TH_MAX 0x1f ///< Max of FP_CFG: MSC_CAC_TH

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
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_128 = 3,///<128
  IDSOPT_DBG_CPU_GEN_SCE_LIVELOCK_THRESH_AUTO = 7,///<Auto
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
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_16 = 3,///<16
  IDSOPT_DBG_CPU_GEN_SCE_DIDT_TIME_CONST_AUTO = 7,///<Auto
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

///OcInterPickGroupFusionDisable
///Control DE_CFG[DecfgOcInterPickGroupFusionDisable]
typedef enum {
  IDSOPT_DBG_CPU_GEN_OC_INT_PICK_GP_FUSION_DIS_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_GEN_OC_INT_PICK_GP_FUSION_DIS_ENABLE = 1,///<Enable
  IDSOPT_DBG_CPU_GEN_OC_INT_PICK_GP_FUSION_DIS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_GEN_OC_INT_PICK_GP_FUSION_DIS;

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

///Combo DSM script application
///Can be used to disable the combo DSM script automatically applied to RV-Bx silicon.  Only applies to non-secure parts.
typedef enum {
  IDSOPT_DBG_CPU_GEN_COMBO_DSM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_GEN_COMBO_DSM_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_GEN_COMBO_DSM;

///SmmLock Control
///Disabling this feature forces SmmLock to be cleared
typedef enum {
  IDSOPT_DBG_CPU_SMM_LOCK_CONTROL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_SMM_LOCK_CONTROL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_SMM_LOCK_CONTROL;

///Core Dynamic Pwr Monitor (DPM) Control
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

///Core MSR Access Enable
///This control enables/disables the MSR Access in the Core.\n 0 = Core MSR Access ENABLED (DPM_CFG[MsrAccessDisable] = 0)\n 1 = Core MSR Access DISABLED (DPM_CFG[MsrAccessDisable] = 1)
typedef enum {
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_0 = 0,///<0
  IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS_1 = 1,///<1
} IDSOPT_DBG_CPU_PWR_DPM_MSR_ACCESS;

///BTC Control
///This turns on/off BTC workload/calibration - this will be off and default GB used early in program\n Auto = BTC Enabled\n Disable = BTC disabled
typedef enum {
  IDSOPT_DBG_CPU_PWR_BTC_CTRL_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_PWR_BTC_CTRL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_PWR_BTC_CTRL;

///ACPI _PSS
///Enable / disable the P-state object declaration to the OS.
typedef enum {
  IDSOPT_DBG_CPU_PM_CTL_PSS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_PM_CTL_PSS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_PM_CTL_PSS_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_PM_CTL_PSS;

///ACPI C3 Control
typedef enum {
  IDSOPT_DBG_CPU_ACPI_C3_CTL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CPU_ACPI_C3_CTL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_CPU_ACPI_C3_CTL_AUTO = 3,///<Auto
} IDSOPT_DBG_CPU_ACPI_C3_CTL;

///CC6 Control
///Auto = Use default settings for CC6 enable\nManual = User can set CC6 enable
typedef enum {
  IDSOPT_DBG_CPU_CC6_CTL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_CC6_CTL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_CC6_CTL;

///CC6 Enable
///0 = CC6 is disabled\n1 = CC6 is enabled
typedef enum {
  IDSOPT_DBG_CPU_CC6_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_CC6_EN_ENABLE = 1,///<Enable
} IDSOPT_DBG_CPU_CC6_EN;

///PC6 Control
///Auto = Use default settings for PC6 enable\nManual = User can set PC6 enable
typedef enum {
  IDSOPT_DBG_CPU_PC6_CTL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_PC6_CTL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_PC6_CTL;

///PC6 Enable
///0 = PC6 is disabled\n1 = PC6 is enabled
typedef enum {
  IDSOPT_DBG_CPU_PC6_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_PC6_EN_ENABLE = 1,///<Enable
} IDSOPT_DBG_CPU_PC6_EN;

///Core PopDn P-state Control
///Auto = Use default settings for PopDn P-state\nManual = User can set custom settings for PopDn P-state
typedef enum {
  IDSOPT_DBG_CPU_POP_DN_PSTATE_CTL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_POP_DN_PSTATE_CTL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_POP_DN_PSTATE_CTL;

///Core PopDn P-state Enable
///0 = Core PopDn P-state is disabled\n1 = Core PopDn P-state is enabled
typedef enum {
  IDSOPT_DBG_CPU_POP_DN_PSTATE_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_POP_DN_PSTATE_EN_ENABLE = 1,///<Enable
} IDSOPT_DBG_CPU_POP_DN_PSTATE_EN;

///Core PopDn P-state DFSID
///Specify the PopDn P-state DFSID
#define IDSOPT_DBG_CPU_POP_DN_PSTATE_DFS_ID_MIN 0 ///< Min of Core PopDn P-state DFSID
#define IDSOPT_DBG_CPU_POP_DN_PSTATE_DFS_ID_MAX 0x3f ///< Max of Core PopDn P-state DFSID

///CC6 PopDn P-state Control
///Auto = Use default settings for CC6 (Cacheflush) PopDn\nManual = User can set custom settings for CC6 (Cacheflush) PopDn
typedef enum {
  IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_CTL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_CTL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_CTL;

///CC6 PopDn P-state Enable
///0 = Core PopDn P-state disabled\n1 = Core PopDn P-state enabled
typedef enum {
  IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_EN_ENABLE = 1,///<Enable
} IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_EN;

///CC6 PopDn P-state DFSID
///Specify the CC6 PopDn P-state DFSID
#define IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_DFS_ID_MIN 0 ///< Min of CC6 PopDn P-state DFSID
#define IDSOPT_DBG_CPU_CC6_POP_DN_PSTATE_DFS_ID_MAX 0x3f ///< Max of CC6 PopDn P-state DFSID

///CC6 PopUp P-state Control
///Auto = Use default settings for CC6 (Exit) PopUp\nManual = User can set custom settings for CC6 (Exit) PopUp
typedef enum {
  IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_CTL_MANUAL = 0,///<Manual
  IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_CTL_AUTO = 1,///<Auto
} IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_CTL;

///CC6 PopUp P-state Enable
///0 = Core PopUp disabled\n1 = Core PopUp enabled
typedef enum {
  IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_EN_ENABLE = 1,///<Enable
} IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_EN;

///CC6 PopUp P-state DFSID
///Specify the CC6 PopUp P-state DFSID
#define IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_DFS_ID_MIN 0 ///< Min of CC6 PopUp P-state DFSID
#define IDSOPT_DBG_CPU_CC6_POP_UP_PSTATE_DFS_ID_MAX 0x3f ///< Max of CC6 PopUp P-state DFSID

///C1 Latency
#define IDSOPT_DBG_CPU_C1_LATENCY_MIN 0 ///< Min of C1 Latency
#define IDSOPT_DBG_CPU_C1_LATENCY_MAX 5000 ///< Max of C1 Latency

///C2 Latency
#define IDSOPT_DBG_CPU_C2_LATENCY_MIN 0 ///< Min of C2 Latency
#define IDSOPT_DBG_CPU_C2_LATENCY_MAX 5000 ///< Max of C2 Latency

///C3 Latency
#define IDSOPT_DBG_CPU_C3_LATENCY_MIN 0 ///< Min of C3 Latency
#define IDSOPT_DBG_CPU_C3_LATENCY_MAX 5000 ///< Max of C3 Latency

///SMM handler size per thread
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_FOR_SMM_PER_THREAD_MIN 0 ///< Min of SMM handler size per thread
#define IDSOPT_DBG_CPU_MEM_HOLE_FOR_SMM_PER_THREAD_MAX 4294967295 ///< Max of SMM handler size per thread

///Memory Hole on Die 0
///in MB
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE0_MIN 0 ///< Min of Memory Hole on Die 0
#define IDSOPT_DBG_CPU_MEM_HOLE_DIE0_MAX 4294967295 ///< Max of Memory Hole on Die 0

///Node 0 Debug Memory Hole
///Enable Debug Memory Hole
typedef enum {
  IDSOPT_DBG_CPU_GEN_MEM_HOLE0_AUTO = 0,///<Auto
  IDSOPT_DBG_CPU_GEN_MEM_HOLE0_32M = 2,///<32M
  IDSOPT_DBG_CPU_GEN_MEM_HOLE0_64M = 4,///<64M
  IDSOPT_DBG_CPU_GEN_MEM_HOLE0_128M = 8,///<128M
  IDSOPT_DBG_CPU_GEN_MEM_HOLE0_256M = 16,///<256M
} IDSOPT_DBG_CPU_GEN_MEM_HOLE0;

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

///TCDX bypasses control
///Controls TCDX bypasses DF::TCDXConfig[BypassEnable]
typedef enum {
  IDSOPT_DF_DBG_TCDX_BYPASS_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_TCDX_BYPASS_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_TCDX_BYPASS_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_TCDX_BYPASS_CTRL;

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

///PC6 ramp hint ctrl - FCH
///Controls DF::DfPc6ServiceControl[Pc6RampOnFchHint]
typedef enum {
  IDSOPT_DF_DBG_PC6_RAMP_HINT_FCH_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PC6_RAMP_HINT_FCH_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PC6_RAMP_HINT_FCH_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PC6_RAMP_HINT_FCH_CTRL;

///PC6 ramp hint ctrl - GMI
///Controls DF::DfPc6ServiceControl[Pc6RampOnGmiHint]
typedef enum {
  IDSOPT_DF_DBG_PC6_RAMP_HINT_GMI_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PC6_RAMP_HINT_GMI_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PC6_RAMP_HINT_GMI_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PC6_RAMP_HINT_GMI_CTRL;

///PC6 hint FCH GMI prop ctrl
///Controls DF::DfPc6ServiceControl[PropagateFchHintToGmi]
typedef enum {
  IDSOPT_DF_DBG_PC6_HINT_FCH_GMI_PROP_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PC6_HINT_FCH_GMI_PROP_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PC6_HINT_FCH_GMI_PROP_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PC6_HINT_FCH_GMI_PROP_CTRL;

///DF picker load step control
///Controls DF::PwrMgtCfg0[PickLoadStepCstateEn]
typedef enum {
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_PICKER_LOAD_STEP_CTRL;

///DF clock gating control
///Controls DF::PwrMgtCfg0[ClkGateDis]
typedef enum {
  IDSOPT_DF_DBG_CLK_GATING_CTRL_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CLK_GATING_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CLK_GATING_CTRL_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CLK_GATING_CTRL;

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

///CS Force Order for EA requests
///Controls DF::CoherentSlaveModeCtrlA0[ForceEAInOrder]
typedef enum {
  IDSOPT_DF_DBG_CS_FORCE_ORDER_EA_REQ_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CS_FORCE_ORDER_EA_REQ_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CS_FORCE_ORDER_EA_REQ_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CS_FORCE_ORDER_EA_REQ;

///CS Req Bypass for EA requests
///Controls DF::CoherentSlaveConfigA2[DisReqBypEA]
typedef enum {
  IDSOPT_DF_DBG_CS_REQ_BYPASS_EA_REQ_DISABLED = 0,///<Disabled
  IDSOPT_DF_DBG_CS_REQ_BYPASS_EA_REQ_ENABLED = 1,///<Enabled
  IDSOPT_DF_DBG_CS_REQ_BYPASS_EA_REQ_AUTO = 3,///<Auto
} IDSOPT_DF_DBG_CS_REQ_BYPASS_EA_REQ;

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

///Data Scramble
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_DATA_SCRAMBLE_DDR4_ENABLED = 0x1,///<Enabled
  IDSOPT_DBG_MEM_CTRLLER_DATA_SCRAMBLE_DDR4_DISABLED = 0x0,///<Disabled
  IDSOPT_DBG_MEM_CTRLLER_DATA_SCRAMBLE_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_CTRLLER_DATA_SCRAMBLE_DDR4;

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

///Memory P-state
typedef enum {
  IDSOPT_DBG_MEM_PSTATES_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PSTATES_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_PSTATES_DDR4_DISABLED = 0,///<Disabled
} IDSOPT_DBG_MEM_PSTATES_DDR4;

///DRAM Address Command Parity Retry
///UMC_CH::RecCtrl[RecEn][0] and UMC_CH::RecCtrl[MaxParRply].
typedef enum {
  IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_ADDR_CMD_PARITY_RETRY_DDR4;

///Max Parity Error Replay
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
#define IDSOPT_DBG_MEM_WRITE_CRC_ERROR_MAX_REPLAY_DDR4_MIN 0 ///< Min of Max Write CRC Error Replay
#define IDSOPT_DBG_MEM_WRITE_CRC_ERROR_MAX_REPLAY_DDR4_MAX 0x3f ///< Max of Max Write CRC Error Replay

///Inject TX Command Parity Errors
/// DF is requesting a UMC CBS option for injecting TX command parity errors as this will generate RETRANSMIT commands. The following webpage describes the recipe: http://twiki.amd.com/twiki/bin/view/DFArch/UmcRetransmitRecipe
typedef enum {
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_ENABLE = 1,///<Enable
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_DISABLE = 0,///<Disable
  IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4_AUTO = 0xFF,///<Auto
} IDSOPT_DBG_MEM_INJECT_TX_CMD_PARITY_ERRORS_DDR4;

///Data Bus Configuration User Controls
///Specify the mode for drive strength to Auto or Manual
typedef enum {
  IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4_MANUAL = 1,///<Manual
} IDSOPT_DBG_MEM_DATA_BUS_CONFIG_CTL_DDR4;

///ProcODT
///Specifies the Processor ODT
typedef enum {
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_HIGHIMPEDANCE = 0,///<High Impedance
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_480OHM = 1,///<480 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_240OHM = 2,///<240 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_160OHM = 3,///<160 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_120OHM = 8,///<120 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_96OHM = 9,///<96 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_80OHM = 10,///<80 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_686OHM = 11,///<68.6 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_60OHM = 0x18,///<60 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_533OHM = 0x19,///<53.3 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_48OHM = 0x1A,///<48 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_436OHM = 0x1B,///<43.6 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_40OHM = 0x38,///<40 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_369OHM = 0x39,///<36.9 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_343OHM = 0x3A,///<34.3 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_32OHM = 0x3B,///<32 ohm
  IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4_30OHM = 0x3E,///<30 ohm
} IDSOPT_DBG_MEM_CTRLLER_PROC_ODT_DDR4;

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
#define IDSOPT_DBG_MEM_PHY_RX_CLK_DLY_OVERRIDE_VALUE_MAX 0xff ///< Max of RxClkDly Override Value

///RxPbDly Override Op
typedef enum {
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_PLUS = 0,///<Plus
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_MINUS = 1,///<Minus
  IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP_OVERRIDE = 2,///<Override
} IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_OP;

///RxPbDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_VALUE_MIN 0 ///< Min of RxPbDly Override Value
#define IDSOPT_DBG_MEM_PHY_RX_PB_DLY_OVERRIDE_VALUE_MAX 0xff ///< Max of RxPbDly Override Value

///VrefDAC1 Override Op
typedef enum {
  IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_OP_AUTO = 0xFF,///<Auto
  IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_OP_PLUS = 0,///<Plus
  IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_OP_MINUS = 1,///<Minus
  IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_OP_OVERRIDE = 2,///<Override
} IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_OP;

///VrefDAC1 Override Value
#define IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_VALUE_MIN 0 ///< Min of VrefDAC1 Override Value
#define IDSOPT_DBG_MEM_PHY_VREF_DA_C1_OVERRIDE_VALUE_MAX 0xff ///< Max of VrefDAC1 Override Value

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
///Control DBGU NBIO trace to DRAM
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

///DBGU_GFX trace to DRAM
///Control DBGU GFX trace to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU_GFX_TO_DRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU_GFX_TO_DRAM_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU_GFX_TO_DRAM_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU_GFX_TO_DRAM_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU_GFX_TO_DRAM_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU_GFX_TO_DRAM;

///DBGU0 trace to DRAM
///Control DBGU0 trace to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU0_TO_DRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU0_TO_DRAM_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU0_TO_DRAM_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU0_TO_DRAM_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU0_TO_DRAM_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU0_TO_DRAM;

///DBGU1 trace to DRAM
///Control DBGU1 trace to DRAM
typedef enum {
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_1MB = 1,///<1 MB
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_4MB = 2,///<4 MB
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_16MB = 3,///<16 MB
  IDSOPT_DBG_GNB_DBGU1_TO_DRAM_64MB = 4,///<64 MB
} IDSOPT_DBG_GNB_DBGU1_TO_DRAM;

///64 bytes write combine control
///Control for en/dis combining writes into 64-byte requests
typedef enum {
  IDSOPT_DBG_GNB_GFX64_BYTES_WR_COMBINE_CTL_0 = 0,///<0
  IDSOPT_DBG_GNB_GFX64_BYTES_WR_COMBINE_CTL_1 = 1,///<1
  IDSOPT_DBG_GNB_GFX64_BYTES_WR_COMBINE_CTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX64_BYTES_WR_COMBINE_CTL;

///UMA Steering
///Set UMA Steering
typedef enum {
  IDSOPT_DBG_GNB_GFX_UMA_STEERING_0 = 0,///<0
  IDSOPT_DBG_GNB_GFX_UMA_STEERING_1 = 1,///<1
  IDSOPT_DBG_GNB_GFX_UMA_STEERING_2 = 2,///<2
  IDSOPT_DBG_GNB_GFX_UMA_STEERING_3 = 3,///<3
  IDSOPT_DBG_GNB_GFX_UMA_STEERING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_UMA_STEERING;

///GFX CUs/RB Control
///GFX CUs/RB Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_SIMD_QP_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_SIMD_QP_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_SIMD_QP_CTL;

///InactiveCUs
///InactiveCUs
#define IDSOPT_DBG_GNB_GFX_INACTIVE_C_US_MIN 0 ///< Min of InactiveCUs
#define IDSOPT_DBG_GNB_GFX_INACTIVE_C_US_MAX 0xffff ///< Max of InactiveCUs

///RBBackendDisable
///RBBackendDisable
#define IDSOPT_DBG_GNB_GFX_RB_BACKEND_DISABLE_MIN 0 ///< Min of RBBackendDisable
#define IDSOPT_DBG_GNB_GFX_RB_BACKEND_DISABLE_MAX 0xff ///< Max of RBBackendDisable

///RB Map for PKR
///RB Map for PKR
#define IDSOPT_DBG_GNB_GFX_RB_MAPFOR_PKR_MIN 0 ///< Min of RB Map for PKR
#define IDSOPT_DBG_GNB_GFX_RB_MAPFOR_PKR_MAX 0x3 ///< Max of RB Map for PKR

///Wireless Display Support
///Enable Wireless Display Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_WIRELESS_DISPLAY_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_WIRELESS_DISPLAY_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_WIRELESS_DISPLAY_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_WIRELESS_DISPLAY_SUPPORT;

///Vector Engine (VE) EDC Enable
///Use this option to enable / disable Vector Engine (VE) Error Detection and Correction (EDC). Auto will set VE to enabled.
typedef enum {
  IDSOPT_DBG_GNB_GFX_VECT_ENG_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_GFX_VECT_ENG_EN_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_GFX_VECT_ENG_EN_AUTO = 2,///<Auto
} IDSOPT_DBG_GNB_GFX_VECT_ENG_EN;

///LCD backlight control
///LCD backlight control
typedef enum {
  IDSOPT_DBG_GNB_GFX_LCD_BACK_LIGHT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_LCD_BACK_LIGHT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_LCD_BACK_LIGHT_CTL;

///LCD backlight
///LCD backlight
#define IDSOPT_DBG_GNB_GFX_LCD_BACK_LIGHT_MIN 0 ///< Min of LCD backlight
#define IDSOPT_DBG_GNB_GFX_LCD_BACK_LIGHT_MAX 0xffff ///< Max of LCD backlight

///Dynamic Refresh Rate Control
///Dynamic Refresh Rate Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_DRR_CONTROL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_DRR_CONTROL_AUTO = 0x0F,///<Auto
} IDSOPT_DBG_GNB_GFX_DRR_CONTROL;

///Panel Min Refresh Rate
///LCD Panel Min Refresh Rate
#define IDSOPT_DBG_GNB_GFX_LCD_MIN_REFRESH_RATE_MIN 0 ///< Min of Panel Min Refresh Rate
#define IDSOPT_DBG_GNB_GFX_LCD_MIN_REFRESH_RATE_MAX 0xff ///< Max of Panel Min Refresh Rate

///INTGFX IOMMUv1 Disabled
///Allow gfx non-snoop system traffic to bypass IOMMU and route through Garlic when IOMMUv1 is not required
typedef enum {
  IDSOPT_DBG_GNB_L2_DEBUG3_BIT31_0 = 0,///<0
  IDSOPT_DBG_GNB_L2_DEBUG3_BIT31_1 = 1,///<1
  IDSOPT_DBG_GNB_L2_DEBUG3_BIT31_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_L2_DEBUG3_BIT31;

///ACP engine
///Reserve system memory for ACP engine
typedef enum {
  IDSOPT_DBG_GNB_REV_MEM_AC_PENGINE_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_REV_MEM_AC_PENGINE_NO_ACP_SIZE = 0x0,///<NO_ACP_SIZE
  IDSOPT_DBG_GNB_REV_MEM_AC_PENGINE_ACP_SIZE_2MB = 0x20,///<ACP_SIZE_2MB
  IDSOPT_DBG_GNB_REV_MEM_AC_PENGINE_ACP_SIZE_4MB = 0x40,///<ACP_SIZE_4MB
} IDSOPT_DBG_GNB_REV_MEM_AC_PENGINE;

///Enabling Internal Parity Error Detection
///Enabling Internal Parity Error Detection
typedef enum {
  IDSOPT_DBG_GNB_PARITY_ERROR_CONFIG_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_PARITY_ERROR_CONFIG_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PARITY_ERROR_CONFIG_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_PARITY_ERROR_CONFIG;

///VGA Hole
///0 means VGA range is decoded as system memory, 1 means VGA range is decoded as MMIO region.
typedef enum {
  IDSOPT_DBG_GNB_VGA_HOLE_0 = 0,///<0
  IDSOPT_DBG_GNB_VGA_HOLE_1 = 1,///<1
  IDSOPT_DBG_GNB_VGA_HOLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_VGA_HOLE;

///PCIe Memory Power Deep Sleep in L1
typedef enum {
  IDSOPT_DBG_PCIE_MEMORY_POWER_DEEP_SLEEP_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_PCIE_MEMORY_POWER_DEEP_SLEEP_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PCIE_MEMORY_POWER_DEEP_SLEEP_IN_L1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_PCIE_MEMORY_POWER_DEEP_SLEEP_IN_L1;

///PCIe Memory Power Shut Down in L1
typedef enum {
  IDSOPT_DBG_PCIE_MEMORY_POWER_SHUT_DOWN_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_PCIE_MEMORY_POWER_SHUT_DOWN_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PCIE_MEMORY_POWER_SHUT_DOWN_IN_L1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_PCIE_MEMORY_POWER_SHUT_DOWN_IN_L1;

///PCIe AtomicOps Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ATOMIC_OPS_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_GFX_ATOMIC_OPS;

///HDMI Spread Spectrum Percentage Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_HDMI_SS_PERCENTAGE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_HDMI_SS_PERCENTAGE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_HDMI_SS_PERCENTAGE_CTL;

///HDMI Spread Spectrum Percentage
#define IDSOPT_DBG_GNB_GFX_HDMI_SS_PERCENTAGE_MIN 0 ///< Min of HDMI Spread Spectrum Percentage
#define IDSOPT_DBG_GNB_GFX_HDMI_SS_PERCENTAGE_MAX 100 ///< Max of HDMI Spread Spectrum Percentage

///HDMI Spread Spectrum Rate in 10Hz Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_HDMI_SS_RATE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_HDMI_SS_RATE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_HDMI_SS_RATE_CTL;

///HDMI Spread Spectrum Rate in 10Hz
#define IDSOPT_DBG_GNB_GFX_HDMI_SS_RATE_MIN 0 ///< Min of HDMI Spread Spectrum Rate in 10Hz
#define IDSOPT_DBG_GNB_GFX_HDMI_SS_RATE_MAX 0xffff ///< Max of HDMI Spread Spectrum Rate in 10Hz

///Dvi Spread Spectrum Percentage Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_DVI_SS_PERCENTAGE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_DVI_SS_PERCENTAGE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_DVI_SS_PERCENTAGE_CTL;

///Dvi Spread Spectrum Percentage
#define IDSOPT_DBG_GNB_GFX_DVI_SS_PERCENTAGE_MIN 0 ///< Min of Dvi Spread Spectrum Percentage
#define IDSOPT_DBG_GNB_GFX_DVI_SS_PERCENTAGE_MAX 100 ///< Max of Dvi Spread Spectrum Percentage

///Dvi Spread Spectrum Rate in 10Hz Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_DVI_SS_RATE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_DVI_SS_RATE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_DVI_SS_RATE_CTL;

///Dvi Spread Spectrum Rate in 10Hz
#define IDSOPT_DBG_GNB_GFX_DVI_SS_RATE_MIN 0 ///< Min of Dvi Spread Spectrum Rate in 10Hz
#define IDSOPT_DBG_GNB_GFX_DVI_SS_RATE_MAX 0xffff ///< Max of Dvi Spread Spectrum Rate in 10Hz

///Platfrom Type
///Platfrom type for PP
typedef enum {
  IDSOPT_DBG_GNB_GFX_PLATFROM_TYPE_MOBILE = 1,///<Mobile
  IDSOPT_DBG_GNB_GFX_PLATFROM_TYPE_DESKTOP = 2,///<Desktop
  IDSOPT_DBG_GNB_GFX_PLATFROM_TYPE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_PLATFROM_TYPE;

///Power Play Table Override
///Override Power play table fuses
typedef enum {
  IDSOPT_DBG_GNB_GFX_POWER_PLAY_OVERRIDE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_POWER_PLAY_OVERRIDE_SIMPLE = 1,///<Simple
} IDSOPT_DBG_GNB_GFX_POWER_PLAY_OVERRIDE;

///Load from Fuses
///Load option values from fuses
typedef enum {
  IDSOPT_DBG_GNB_GFX_LOAD_FROM_FUSES_NONE = 0,///<None
  IDSOPT_DBG_GNB_GFX_LOAD_FROM_FUSES_LOAD = 1,///<Load
} IDSOPT_DBG_GNB_GFX_LOAD_FROM_FUSES;

///VddNbVid 0
///VID 0: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D0_MIN 0 ///< Min of VddNbVid 0
#define IDSOPT_DBG_GNB_GFX_PP_VI_D0_MAX 0xf9 ///< Max of VddNbVid 0

///VddNbVid 1
///VID 1: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D1_MIN 0 ///< Min of VddNbVid 1
#define IDSOPT_DBG_GNB_GFX_PP_VI_D1_MAX 0xf9 ///< Max of VddNbVid 1

///VddNbVid 2
///VID 2: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D2_MIN 0 ///< Min of VddNbVid 2
#define IDSOPT_DBG_GNB_GFX_PP_VI_D2_MAX 0xf9 ///< Max of VddNbVid 2

///VddNbVid 3
///VID 3: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D3_MIN 0 ///< Min of VddNbVid 3
#define IDSOPT_DBG_GNB_GFX_PP_VI_D3_MAX 0xf9 ///< Max of VddNbVid 3

///VddNbVid 4
///VID 4: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D4_MIN 0 ///< Min of VddNbVid 4
#define IDSOPT_DBG_GNB_GFX_PP_VI_D4_MAX 0xf9 ///< Max of VddNbVid 4

///VddNbVid 5
///VID 4: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D5_MIN 0 ///< Min of VddNbVid 5
#define IDSOPT_DBG_GNB_GFX_PP_VI_D5_MAX 0xf9 ///< Max of VddNbVid 5

///VddNbVid 6
///VID 4: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D6_MIN 0 ///< Min of VddNbVid 6
#define IDSOPT_DBG_GNB_GFX_PP_VI_D6_MAX 0xf9 ///< Max of VddNbVid 6

///VddNbVid 7
///VID 4: 249(0xF9) means Fused. 0xF9 means Auto.
#define IDSOPT_DBG_GNB_GFX_PP_VI_D7_MIN 0 ///< Min of VddNbVid 7
#define IDSOPT_DBG_GNB_GFX_PP_VI_D7_MAX 0xf9 ///< Max of VddNbVid 7

///PowerplayPerfFlag
///PowerplayPerfFlag
#define IDSOPT_DBG_GNB_GFX_POWERPLAY_PERF_FLAG_MIN 0 ///< Min of PowerplayPerfFlag
#define IDSOPT_DBG_GNB_GFX_POWERPLAY_PERF_FLAG_MAX 0xff ///< Max of PowerplayPerfFlag

///PowerplayPowerSavingsFlag
///PowerplayPowerSavingsFlag
#define IDSOPT_DBG_GNB_GFX_POWERPLAY_POWER_SAVINGS_FLAG_MIN 0 ///< Min of PowerplayPowerSavingsFlag
#define IDSOPT_DBG_GNB_GFX_POWERPLAY_POWER_SAVINGS_FLAG_MAX 0xff ///< Max of PowerplayPowerSavingsFlag

///SclkDid #0
///SclkDid #0
#define IDSOPT_DBG_GNB_GFX_SCLK_DID0_MIN 0 ///< Min of SclkDid #0
#define IDSOPT_DBG_GNB_GFX_SCLK_DID0_MAX 0xff ///< Max of SclkDid #0

///SclkDid #1
///SclkDid #1
#define IDSOPT_DBG_GNB_GFX_SCLK_DID1_MIN 0 ///< Min of SclkDid #1
#define IDSOPT_DBG_GNB_GFX_SCLK_DID1_MAX 0xff ///< Max of SclkDid #1

///SclkDid #2
///SclkDid #2
#define IDSOPT_DBG_GNB_GFX_SCLK_DID2_MIN 0 ///< Min of SclkDid #2
#define IDSOPT_DBG_GNB_GFX_SCLK_DID2_MAX 0xff ///< Max of SclkDid #2

///SclkDid #3
///SclkDid #3
#define IDSOPT_DBG_GNB_GFX_SCLK_DID3_MIN 0 ///< Min of SclkDid #3
#define IDSOPT_DBG_GNB_GFX_SCLK_DID3_MAX 0xff ///< Max of SclkDid #3

///SclkDid #4
///SclkDid #4
#define IDSOPT_DBG_GNB_GFX_SCLK_DID4_MIN 0 ///< Min of SclkDid #4
#define IDSOPT_DBG_GNB_GFX_SCLK_DID4_MAX 0xff ///< Max of SclkDid #4

///SclkDid #5
///SclkDid #5
#define IDSOPT_DBG_GNB_GFX_SCLK_DID5_MIN 0 ///< Min of SclkDid #5
#define IDSOPT_DBG_GNB_GFX_SCLK_DID5_MAX 0xff ///< Max of SclkDid #5

///SclkDid #6
///SclkDid #6
#define IDSOPT_DBG_GNB_GFX_SCLK_DID6_MIN 0 ///< Min of SclkDid #6
#define IDSOPT_DBG_GNB_GFX_SCLK_DID6_MAX 0xff ///< Max of SclkDid #6

///SclkDid #7
///SclkDid #7
#define IDSOPT_DBG_GNB_GFX_SCLK_DID7_MIN 0 ///< Min of SclkDid #7
#define IDSOPT_DBG_GNB_GFX_SCLK_DID7_MAX 0xff ///< Max of SclkDid #7

///NCLK FID #0
///NCLK FID #0
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D0_MIN 0 ///< Min of NCLK FID #0
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D0_MAX 0xff ///< Max of NCLK FID #0

///NCLK FID #1
///NCLK FID #1
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D1_MIN 0 ///< Min of NCLK FID #1
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D1_MAX 0xff ///< Max of NCLK FID #1

///NCLK FID #2
///NCLK FID #2
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D2_MIN 0 ///< Min of NCLK FID #2
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D2_MAX 0xff ///< Max of NCLK FID #2

///NCLK FID #3
///NCLK FID #3
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D3_MIN 0 ///< Min of NCLK FID #3
#define IDSOPT_DBG_GNB_GFX_NCLKFI_D3_MAX 0xff ///< Max of NCLK FID #3

///NCLK DID #0
///NCLK DID #0
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D0_MIN 0 ///< Min of NCLK DID #0
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D0_MAX 0xff ///< Max of NCLK DID #0

///NCLK DID #1
///NCLK DID #1
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D1_MIN 0 ///< Min of NCLK DID #1
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D1_MAX 0xff ///< Max of NCLK DID #1

///NCLK DID #2
///NCLK DID #2
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D2_MIN 0 ///< Min of NCLK DID #2
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D2_MAX 0xff ///< Max of NCLK DID #2

///NCLK DID #3
///NCLK DID #3
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D3_MIN 0 ///< Min of NCLK DID #3
#define IDSOPT_DBG_GNB_GFX_NCLKDI_D3_MAX 0xff ///< Max of NCLK DID #3

///VClkDid #0
///VClkDid #0
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID0_MIN 0 ///< Min of VClkDid #0
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID0_MAX 0xff ///< Max of VClkDid #0

///VClkDid #1
///VClkDid #1
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID1_MIN 0 ///< Min of VClkDid #1
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID1_MAX 0xff ///< Max of VClkDid #1

///VClkDid #2
///VClkDid #2
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID2_MIN 0 ///< Min of VClkDid #2
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID2_MAX 0xff ///< Max of VClkDid #2

///VClkDid #3
///VClkDid #3
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID3_MIN 0 ///< Min of VClkDid #3
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID3_MAX 0xff ///< Max of VClkDid #3

///VClkDid #4
///VClkDid #4
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID4_MIN 0 ///< Min of VClkDid #4
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID4_MAX 0xff ///< Max of VClkDid #4

///VClkDid #5
///VClkDid #5
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID5_MIN 0 ///< Min of VClkDid #5
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID5_MAX 0xff ///< Max of VClkDid #5

///VClkDid #6
///VClkDid #6
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID6_MIN 0 ///< Min of VClkDid #6
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID6_MAX 0xff ///< Max of VClkDid #6

///VClkDid #7
///VClkDid #7
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID7_MIN 0 ///< Min of VClkDid #7
#define IDSOPT_DBG_GNB_GFX_V_CLK_DID7_MAX 0xff ///< Max of VClkDid #7

///DClkDid #0
///DClkDid #0
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID0_MIN 0 ///< Min of DClkDid #0
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID0_MAX 0xff ///< Max of DClkDid #0

///DClkDid #1
///DClkDid #1
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID1_MIN 0 ///< Min of DClkDid #1
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID1_MAX 0xff ///< Max of DClkDid #1

///DClkDid #2
///DClkDid #2
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID2_MIN 0 ///< Min of DClkDid #2
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID2_MAX 0xff ///< Max of DClkDid #2

///DClkDid #3
///DClkDid #3
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID3_MIN 0 ///< Min of DClkDid #3
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID3_MAX 0xff ///< Max of DClkDid #3

///DClkDid #4
///DClkDid #4
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID4_MIN 0 ///< Min of DClkDid #4
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID4_MAX 0xff ///< Max of DClkDid #4

///DClkDid #5
///DClkDid #5
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID5_MIN 0 ///< Min of DClkDid #5
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID5_MAX 0xff ///< Max of DClkDid #5

///DClkDid #6
///DClkDid #6
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID6_MIN 0 ///< Min of DClkDid #6
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID6_MAX 0xff ///< Max of DClkDid #6

///DClkDid #7
///DClkDid #7
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID7_MIN 0 ///< Min of DClkDid #7
#define IDSOPT_DBG_GNB_GFX_D_CLK_DID7_MAX 0xff ///< Max of DClkDid #7

///EclkDid Control
///EclkDid Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_ECLK_DID_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_ECLK_DID_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_ECLK_DID_CTL;

///EclkDid #0
///EclkDid #0
#define IDSOPT_DBG_GNB_GFX_ECLK_DID0_MIN 0 ///< Min of EclkDid #0
#define IDSOPT_DBG_GNB_GFX_ECLK_DID0_MAX 0xff ///< Max of EclkDid #0

///EclkDid #1
///EclkDid #1
#define IDSOPT_DBG_GNB_GFX_ECLK_DID1_MIN 0 ///< Min of EclkDid #1
#define IDSOPT_DBG_GNB_GFX_ECLK_DID1_MAX 0xff ///< Max of EclkDid #1

///EclkDid #2
///EclkDid #2
#define IDSOPT_DBG_GNB_GFX_ECLK_DID2_MIN 0 ///< Min of EclkDid #2
#define IDSOPT_DBG_GNB_GFX_ECLK_DID2_MAX 0xff ///< Max of EclkDid #2

///EclkDid #3
///EclkDid #3
#define IDSOPT_DBG_GNB_GFX_ECLK_DID3_MIN 0 ///< Min of EclkDid #3
#define IDSOPT_DBG_GNB_GFX_ECLK_DID3_MAX 0xff ///< Max of EclkDid #3

///EclkDid #4
///EclkDid #4
#define IDSOPT_DBG_GNB_GFX_ECLK_DID4_MIN 0 ///< Min of EclkDid #4
#define IDSOPT_DBG_GNB_GFX_ECLK_DID4_MAX 0xff ///< Max of EclkDid #4

///EclkDid #5
///EclkDid #5
#define IDSOPT_DBG_GNB_GFX_ECLK_DID5_MIN 0 ///< Min of EclkDid #5
#define IDSOPT_DBG_GNB_GFX_ECLK_DID5_MAX 0xff ///< Max of EclkDid #5

///EclkDid #6
///EclkDid #6
#define IDSOPT_DBG_GNB_GFX_ECLK_DID6_MIN 0 ///< Min of EclkDid #6
#define IDSOPT_DBG_GNB_GFX_ECLK_DID6_MAX 0xff ///< Max of EclkDid #6

///EclkDid #7
///EclkDid #7
#define IDSOPT_DBG_GNB_GFX_ECLK_DID7_MIN 0 ///< Min of EclkDid #7
#define IDSOPT_DBG_GNB_GFX_ECLK_DID7_MAX 0xff ///< Max of EclkDid #7

///SamClkDid #0
///SamClkDid #0
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID0_MIN 0 ///< Min of SamClkDid #0
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID0_MAX 0xff ///< Max of SamClkDid #0

///SamClkDid #1
///SamClkDid #1
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID1_MIN 0 ///< Min of SamClkDid #1
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID1_MAX 0xff ///< Max of SamClkDid #1

///SamClkDid #2
///SamClkDid #2
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID2_MIN 0 ///< Min of SamClkDid #2
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID2_MAX 0xff ///< Max of SamClkDid #2

///SamClkDid #3
///SamClkDid #3
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID3_MIN 0 ///< Min of SamClkDid #3
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID3_MAX 0xff ///< Max of SamClkDid #3

///SamClkDid #4
///SamClkDid #4
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID4_MIN 0 ///< Min of SamClkDid #4
#define IDSOPT_DBG_GNB_GFX_SAM_CLK_DID4_MAX 0xff ///< Max of SamClkDid #4

///VceFlags Control
///VceFlags Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_VCE_FLAGS_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_VCE_FLAGS_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_VCE_FLAGS_CTL;

///VceFlags #0
///VceFlags #0
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS0_MIN 0 ///< Min of VceFlags #0
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS0_MAX 0xff ///< Max of VceFlags #0

///VceFlags #1
///VceFlags #1
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS1_MIN 0 ///< Min of VceFlags #1
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS1_MAX 0xff ///< Max of VceFlags #1

///VceFlags #2
///VceFlags #2
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS2_MIN 0 ///< Min of VceFlags #2
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS2_MAX 0xff ///< Max of VceFlags #2

///VceFlags #3
///VceFlags #3
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS3_MIN 0 ///< Min of VceFlags #3
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS3_MAX 0xff ///< Max of VceFlags #3

///VceFlags #4
///VceFlags #4
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS4_MIN 0 ///< Min of VceFlags #4
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS4_MAX 0xff ///< Max of VceFlags #4

///VceFlags #5
///VceFlags #5
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS5_MIN 0 ///< Min of VceFlags #5
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS5_MAX 0xff ///< Max of VceFlags #5

///VceFlags #6
///VceFlags #6
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS6_MIN 0 ///< Min of VceFlags #6
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS6_MAX 0xff ///< Max of VceFlags #6

///VceFlags #7
///VceFlags #7
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS7_MIN 0 ///< Min of VceFlags #7
#define IDSOPT_DBG_GNB_GFX_VCE_FLAGS7_MAX 0xff ///< Max of VceFlags #7

///VceMclk Control
///VceMclk Control
typedef enum {
  IDSOPT_DBG_GNB_GFX_VCE_MCLK_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GFX_VCE_MCLK_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_VCE_MCLK_CTL;

///VceMclk
///VceMclk
#define IDSOPT_DBG_GNB_GFX_VCE_MCLK_MIN 0 ///< Min of VceMclk
#define IDSOPT_DBG_GNB_GFX_VCE_MCLK_MAX 0xff ///< Max of VceMclk

///DISPCLK_DID #0
///DISPCLK_DID #0
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D0_MIN 0 ///< Min of DISPCLK_DID #0
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D0_MAX 0xff ///< Max of DISPCLK_DID #0

///DISPCLK_DID #1
///DISPCLK_DID #1
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D1_MIN 0 ///< Min of DISPCLK_DID #1
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D1_MAX 0xff ///< Max of DISPCLK_DID #1

///DISPCLK_DID #2
///DISPCLK_DID #2
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D2_MIN 0 ///< Min of DISPCLK_DID #2
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D2_MAX 0xff ///< Max of DISPCLK_DID #2

///DISPCLK_DID #3
///DISPCLK_DID #3
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D3_MIN 0 ///< Min of DISPCLK_DID #3
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D3_MAX 0xff ///< Max of DISPCLK_DID #3

///DISPCLK_DID #4
///DISPCLK_DID #4
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D4_MIN 0 ///< Min of DISPCLK_DID #4
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D4_MAX 0xff ///< Max of DISPCLK_DID #4

///DISPCLK_DID #5
///DISPCLK_DID #5
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D5_MIN 0 ///< Min of DISPCLK_DID #5
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D5_MAX 0xff ///< Max of DISPCLK_DID #5

///DISPCLK_DID #6
///DISPCLK_DID #6
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D6_MIN 0 ///< Min of DISPCLK_DID #6
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D6_MAX 0xff ///< Max of DISPCLK_DID #6

///DISPCLK_DID #7
///DISPCLK_DID #7
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D7_MIN 0 ///< Min of DISPCLK_DID #7
#define IDSOPT_DBG_GNB_GFX_DISPCLK_DI_D7_MAX 0xff ///< Max of DISPCLK_DID #7

///PCIe Gen2 VID
///PCIe Gen2 VID
typedef enum {
  IDSOPT_DBG_GNB_GFX_PCIE_GEN2_VID_VOLTAGEFROMPRESENTSETTINGONVID0 = 0,///<Voltage from present setting on VID 0
  IDSOPT_DBG_GNB_GFX_PCIE_GEN2_VID_VOLTAGEFROMPRESENTSETTINGONVID1 = 1,///<Voltage from present setting on VID 1
  IDSOPT_DBG_GNB_GFX_PCIE_GEN2_VID_VOLTAGEFROMPRESENTSETTINGONVID2 = 2,///<Voltage from present setting on VID 2
  IDSOPT_DBG_GNB_GFX_PCIE_GEN2_VID_VOLTAGEFROMPRESENTSETTINGONVID3 = 3,///<Voltage from present setting on VID 3
  IDSOPT_DBG_GNB_GFX_PCIE_GEN2_VID_VOLTAGEFROMPRESENTSETTINGONVID4 = 4,///<Voltage from present setting on VID 4
} IDSOPT_DBG_GNB_GFX_PCIE_GEN2_VID;

///SClk Thermal Did
///SClk Thermal Did
#define IDSOPT_DBG_GNB_GFX_SCLK_THERMAL_DID_MIN 0 ///< Min of SClk Thermal Did
#define IDSOPT_DBG_GNB_GFX_SCLK_THERMAL_DID_MAX 0xff ///< Max of SClk Thermal Did

///GfxVid #0
///GfxVid #0
#define IDSOPT_DBG_GNB_GFX_GFX_VID0_MIN 0 ///< Min of GfxVid #0
#define IDSOPT_DBG_GNB_GFX_GFX_VID0_MAX 0xff ///< Max of GfxVid #0

///GfxVid #1
///GfxVid #1
#define IDSOPT_DBG_GNB_GFX_GFX_VID1_MIN 0 ///< Min of GfxVid #1
#define IDSOPT_DBG_GNB_GFX_GFX_VID1_MAX 0xff ///< Max of GfxVid #1

///GfxVid #2
///GfxVid #2
#define IDSOPT_DBG_GNB_GFX_GFX_VID2_MIN 0 ///< Min of GfxVid #2
#define IDSOPT_DBG_GNB_GFX_GFX_VID2_MAX 0xff ///< Max of GfxVid #2

///GfxVid #3
///GfxVid #3
#define IDSOPT_DBG_GNB_GFX_GFX_VID3_MIN 0 ///< Min of GfxVid #3
#define IDSOPT_DBG_GNB_GFX_GFX_VID3_MAX 0xff ///< Max of GfxVid #3

///GfxVid #4
///GfxVid #4
#define IDSOPT_DBG_GNB_GFX_GFX_VID4_MIN 0 ///< Min of GfxVid #4
#define IDSOPT_DBG_GNB_GFX_GFX_VID4_MAX 0xff ///< Max of GfxVid #4

///GfxVid #5
///GfxVid #5
#define IDSOPT_DBG_GNB_GFX_GFX_VID5_MIN 0 ///< Min of GfxVid #5
#define IDSOPT_DBG_GNB_GFX_GFX_VID5_MAX 0xff ///< Max of GfxVid #5

///GfxVid #6
///GfxVid #6
#define IDSOPT_DBG_GNB_GFX_GFX_VID6_MIN 0 ///< Min of GfxVid #6
#define IDSOPT_DBG_GNB_GFX_GFX_VID6_MAX 0xff ///< Max of GfxVid #6

///GfxVid #7
///GfxVid #7
#define IDSOPT_DBG_GNB_GFX_GFX_VID7_MIN 0 ///< Min of GfxVid #7
#define IDSOPT_DBG_GNB_GFX_GFX_VID7_MAX 0xff ///< Max of GfxVid #7

///AcpClkDid #0
///AcpClkDid #0
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID0_MIN 0 ///< Min of AcpClkDid #0
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID0_MAX 0xff ///< Max of AcpClkDid #0

///AcpClkDid #1
///AcpClkDid #1
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID1_MIN 0 ///< Min of AcpClkDid #1
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID1_MAX 0xff ///< Max of AcpClkDid #1

///AcpClkDid #2
///AcpClkDid #2
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID2_MIN 0 ///< Min of AcpClkDid #2
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID2_MAX 0xff ///< Max of AcpClkDid #2

///AcpClkDid #3
///AcpClkDid #3
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID3_MIN 0 ///< Min of AcpClkDid #3
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID3_MAX 0xff ///< Max of AcpClkDid #3

///AcpClkDid #4
///AcpClkDid #4
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID4_MIN 0 ///< Min of AcpClkDid #4
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID4_MAX 0xff ///< Max of AcpClkDid #4

///AcpClkDid #5
///AcpClkDid #5
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID5_MIN 0 ///< Min of AcpClkDid #5
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID5_MAX 0xff ///< Max of AcpClkDid #5

///AcpClkDid #6
///AcpClkDid #6
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID6_MIN 0 ///< Min of AcpClkDid #6
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID6_MAX 0xff ///< Max of AcpClkDid #6

///AcpClkDid #7
///AcpClkDid #7
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID7_MIN 0 ///< Min of AcpClkDid #7
#define IDSOPT_DBG_GNB_GFX_ACP_CLK_DID7_MAX 0xff ///< Max of AcpClkDid #7

///DP0
///DP0
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0_DP = 0,///<DP
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0_EDP = 1,///<eDP
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0_SINGLELINKDVI = 2,///<Single Link DVI
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0_HDMI = 4,///<HDMI
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0_TRAVISL = 6,///<Travis-L
} IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P0;

///Display 0 HDMI2.0 Support
///Display HDMI2.0 Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISPLAY0_HDM_I20_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_DISPLAY0_HDM_I20_EN_PI3EQX1204 = 4,///<PI3EQX1204
  IDSOPT_DBG_GNB_GFX_DISPLAY0_HDM_I20_EN_TISN65DP159RSBT = 8,///<TISN65DP159RSBT
  IDSOPT_DBG_GNB_GFX_DISPLAY0_HDM_I20_EN_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_DISPLAY0_HDM_I20_EN;

///DP1
///DP1
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1_DP = 0,///<DP
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1_EDP = 1,///<eDP
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1_SINGLELINKDVI = 2,///<Single Link DVI
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1_HDMI = 4,///<HDMI
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1_TRAVISL = 6,///<Travis-L
} IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P1;

///Display 1 HDMI2.0 Support
///Display HDMI2.0 Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISPLAY1_HDM_I20_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_DISPLAY1_HDM_I20_EN_PI3EQX1204 = 4,///<PI3EQX1204
  IDSOPT_DBG_GNB_GFX_DISPLAY1_HDM_I20_EN_TISN65DP159RSBT = 8,///<TISN65DP159RSBT
  IDSOPT_DBG_GNB_GFX_DISPLAY1_HDM_I20_EN_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_DISPLAY1_HDM_I20_EN;

///DP2
///DP2
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2_DP = 0,///<DP
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2_EDP = 1,///<eDP
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2_SINGLELINKDVI = 2,///<Single Link DVI
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2_HDMI = 4,///<HDMI
  IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2_TRAVISL = 6,///<Travis-L
} IDSOPT_DBG_GNB_GFX_DISPLAY_PHY_D_P2;

///Display 2 HDMI2.0 Support
///Display HDMI2.0 Support
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISPLAY2_HDM_I20_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_DISPLAY2_HDM_I20_EN_PI3EQX1204 = 4,///<PI3EQX1204
  IDSOPT_DBG_GNB_GFX_DISPLAY2_HDM_I20_EN_TISN65DP159RSBT = 8,///<TISN65DP159RSBT
  IDSOPT_DBG_GNB_GFX_DISPLAY2_HDM_I20_EN_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_GFX_DISPLAY2_HDM_I20_EN;

///EDP 1.4 VSMode
///EDP v1.4 VSMode.
typedef enum {
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_EDP_VS_LEGACY_MODE = 0,///<EDP_VS_LEGACY_MODE
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_EDP_VS_LOW_VDIFF_MODE = 1,///<EDP_VS_LOW_VDIFF_MODE
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_EDP_VS_HIGH_VDIFF_MODE = 2,///<EDP_VS_HIGH_VDIFF_MODE
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_EDP_VS_STRETCH_MODE = 3,///<EDP_VS_STRETCH_MODE
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_EDP_VS_SINGLE_VDIFF_MODE = 4,///<EDP_VS_SINGLE_VDIFF_MODE
  IDSOPT_DBG_GNBE_D_P14_VS_MODE_EDP_VS_VARIABLE_PREM_MODE = 5,///<EDP_VS_VARIABLE_PREM_MODE
} IDSOPT_DBG_GNBE_D_P14_VS_MODE;

///GFX PSI_L VID enable
///0/1 means write 0 or 1 to register. 1=Control over the PSI_L signal is as specified by the PsiVid field of this register. 0=PSI_L is always high.
typedef enum {
  IDSOPT_DBG_GFX_PWR_PSI_VID_EN_0 = 0,///<0
  IDSOPT_DBG_GFX_PWR_PSI_VID_EN_1 = 1,///<1
  IDSOPT_DBG_GFX_PWR_PSI_VID_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_GFX_PWR_PSI_VID_EN;

///GFX PSI_L VID
///GFX PSI_L VID
#define IDSOPT_DBG_GFX_PWR_NB_PSI_VID_MIN 0 ///< Min of GFX PSI_L VID
#define IDSOPT_DBG_GFX_PWR_NB_PSI_VID_MAX 0x7f ///< Max of GFX PSI_L VID

///GFX Core PSI1_L enable
///0=PSI1_L for VDD is deasserted. 1=PSI1_L for VDD is asserted when all cores are in CC6.
typedef enum {
  IDSOPT_DBG_GFX_PWR_CORE_PSI1L_EN_0 = 0,///<0
  IDSOPT_DBG_GFX_PWR_CORE_PSI1L_EN_1 = 1,///<1
  IDSOPT_DBG_GFX_PWR_CORE_PSI1L_EN_AUTO = 3,///<Auto
} IDSOPT_DBG_GFX_PWR_CORE_PSI1L_EN;

///DP0 retimer-redriver Enable
///retimer-redriver Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P0_HDMI_RE_DRIVER_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P0_HDMI_RE_DRIVER_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P0_HDMI_RE_DRIVER_EN;

///DP0 Hdmi Slave Address
///Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P0_EXT_HDMI_RE_DRV_SLV_ADDR_MIN 0 ///< Min of DP0 Hdmi Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P0_EXT_HDMI_RE_DRV_SLV_ADDR_MAX 0xff ///< Max of DP0 Hdmi Slave Address

///DP0 Hdmi Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P0_EXT_HDMI_RE_DRV_REG_NUM_MIN 0 ///< Min of DP0 Hdmi Register Number
#define IDSOPT_DBG_GNB_GFX_D_P0_EXT_HDMI_RE_DRV_REG_NUM_MAX 0x9 ///< Max of DP0 Hdmi Register Number

///DP0 Hdmi6G Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P0_EXT_HDM_I6_G_RE_DRV_REG_NUM_MIN 0 ///< Min of DP0 Hdmi6G Register Number
#define IDSOPT_DBG_GNB_GFX_D_P0_EXT_HDM_I6_G_RE_DRV_REG_NUM_MAX 0x3 ///< Max of DP0 Hdmi6G Register Number

///DP0 Hdmi Register Setting Enable
///DP0 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG_SETTING_EN;

///Hdmi Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG0_INDEX_MIN 0 ///< Min of Hdmi Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG0_INDEX_MAX 0xff ///< Max of Hdmi Reg[0] Index

///Hdmi Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG0_VAL_MIN 0 ///< Min of Hdmi Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG0_VAL_MAX 0xff ///< Max of Hdmi Reg[0] Value

///Hdmi Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG1_INDEX_MIN 0 ///< Min of Hdmi Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG1_INDEX_MAX 0xff ///< Max of Hdmi Reg[1] Index

///Hdmi Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG1_VAL_MIN 0 ///< Min of Hdmi Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG1_VAL_MAX 0xff ///< Max of Hdmi Reg[1] Value

///Hdmi Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG2_INDEX_MIN 0 ///< Min of Hdmi Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG2_INDEX_MAX 0xff ///< Max of Hdmi Reg[2] Index

///Hdmi Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG2_VAL_MIN 0 ///< Min of Hdmi Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG2_VAL_MAX 0xff ///< Max of Hdmi Reg[2] Value

///Hdmi Reg[3] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG3_INDEX_MIN 0 ///< Min of Hdmi Reg[3] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG3_INDEX_MAX 0xff ///< Max of Hdmi Reg[3] Index

///Hdmi Reg[3] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG3_VAL_MIN 0 ///< Min of Hdmi Reg[3] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG3_VAL_MAX 0xff ///< Max of Hdmi Reg[3] Value

///Hdmi Reg[4] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG4_INDEX_MIN 0 ///< Min of Hdmi Reg[4] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG4_INDEX_MAX 0xff ///< Max of Hdmi Reg[4] Index

///Hdmi Reg[4] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG4_VAL_MIN 0 ///< Min of Hdmi Reg[4] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG4_VAL_MAX 0xff ///< Max of Hdmi Reg[4] Value

///Hdmi Reg[5] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG5_INDEX_MIN 0 ///< Min of Hdmi Reg[5] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG5_INDEX_MAX 0xff ///< Max of Hdmi Reg[5] Index

///Hdmi Reg[5] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG5_VAL_MIN 0 ///< Min of Hdmi Reg[5] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG5_VAL_MAX 0xff ///< Max of Hdmi Reg[5] Value

///Hdmi Reg[6] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG6_INDEX_MIN 0 ///< Min of Hdmi Reg[6] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG6_INDEX_MAX 0xff ///< Max of Hdmi Reg[6] Index

///Hdmi Reg[6] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG6_VAL_MIN 0 ///< Min of Hdmi Reg[6] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG6_VAL_MAX 0xff ///< Max of Hdmi Reg[6] Value

///Hdmi Reg[7] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG7_INDEX_MIN 0 ///< Min of Hdmi Reg[7] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG7_INDEX_MAX 0xff ///< Max of Hdmi Reg[7] Index

///Hdmi Reg[7] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG7_VAL_MIN 0 ///< Min of Hdmi Reg[7] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG7_VAL_MAX 0xff ///< Max of Hdmi Reg[7] Value

///Hdmi Reg[8] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG8_INDEX_MIN 0 ///< Min of Hdmi Reg[8] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG8_INDEX_MAX 0xff ///< Max of Hdmi Reg[8] Index

///Hdmi Reg[8] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG8_VAL_MIN 0 ///< Min of Hdmi Reg[8] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDMI_REG8_VAL_MAX 0xff ///< Max of Hdmi Reg[8] Value

///DP0 Hdmi6G Register Setting Enable
///DP0 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG_SETTING_EN;

///Hdmi6G Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG0_INDEX_MIN 0 ///< Min of Hdmi6G Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG0_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[0] Index

///Hdmi6G Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG0_VAL_MIN 0 ///< Min of Hdmi6G Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG0_VAL_MAX 0xff ///< Max of Hdmi6G Reg[0] Value

///Hdmi6G Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG1_INDEX_MIN 0 ///< Min of Hdmi6G Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG1_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[1] Index

///Hdmi6G Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG1_VAL_MIN 0 ///< Min of Hdmi6G Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG1_VAL_MAX 0xff ///< Max of Hdmi6G Reg[1] Value

///Hdmi6G Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG2_INDEX_MIN 0 ///< Min of Hdmi6G Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG2_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[2] Index

///Hdmi6G Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG2_VAL_MIN 0 ///< Min of Hdmi6G Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P0_HDM_I6_G_REG2_VAL_MAX 0xff ///< Max of Hdmi6G Reg[2] Value

///DP1 retimer-redriver Enable
///retimer-redriver Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P1_HDMI_RE_DRIVER_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P1_HDMI_RE_DRIVER_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P1_HDMI_RE_DRIVER_EN;

///DP1 Hdmi Slave Address
///Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P1_EXT_HDMI_RE_DRV_SLV_ADDR_MIN 0 ///< Min of DP1 Hdmi Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P1_EXT_HDMI_RE_DRV_SLV_ADDR_MAX 0xff ///< Max of DP1 Hdmi Slave Address

///DP1 Hdmi Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P1_EXT_HDMI_RE_DRV_REG_NUM_MIN 0 ///< Min of DP1 Hdmi Register Number
#define IDSOPT_DBG_GNB_GFX_D_P1_EXT_HDMI_RE_DRV_REG_NUM_MAX 0x9 ///< Max of DP1 Hdmi Register Number

///DP1 Hdmi6G Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P1_EXT_HDM_I6_G_RE_DRV_REG_NUM_MIN 0 ///< Min of DP1 Hdmi6G Register Number
#define IDSOPT_DBG_GNB_GFX_D_P1_EXT_HDM_I6_G_RE_DRV_REG_NUM_MAX 0x3 ///< Max of DP1 Hdmi6G Register Number

///DP1 Hdmi Register Setting Enable
///DP1 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG_SETTING_EN;

///Hdmi Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG0_INDEX_MIN 0 ///< Min of Hdmi Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG0_INDEX_MAX 0xff ///< Max of Hdmi Reg[0] Index

///Hdmi Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG0_VAL_MIN 0 ///< Min of Hdmi Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG0_VAL_MAX 0xff ///< Max of Hdmi Reg[0] Value

///Hdmi Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG1_INDEX_MIN 0 ///< Min of Hdmi Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG1_INDEX_MAX 0xff ///< Max of Hdmi Reg[1] Index

///Hdmi Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG1_VAL_MIN 0 ///< Min of Hdmi Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG1_VAL_MAX 0xff ///< Max of Hdmi Reg[1] Value

///Hdmi Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG2_INDEX_MIN 0 ///< Min of Hdmi Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG2_INDEX_MAX 0xff ///< Max of Hdmi Reg[2] Index

///Hdmi Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG2_VAL_MIN 0 ///< Min of Hdmi Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG2_VAL_MAX 0xff ///< Max of Hdmi Reg[2] Value

///Hdmi Reg[3] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG3_INDEX_MIN 0 ///< Min of Hdmi Reg[3] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG3_INDEX_MAX 0xff ///< Max of Hdmi Reg[3] Index

///Hdmi Reg[3] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG3_VAL_MIN 0 ///< Min of Hdmi Reg[3] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG3_VAL_MAX 0xff ///< Max of Hdmi Reg[3] Value

///Hdmi Reg[4] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG4_INDEX_MIN 0 ///< Min of Hdmi Reg[4] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG4_INDEX_MAX 0xff ///< Max of Hdmi Reg[4] Index

///Hdmi Reg[4] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG4_VAL_MIN 0 ///< Min of Hdmi Reg[4] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG4_VAL_MAX 0xff ///< Max of Hdmi Reg[4] Value

///Hdmi Reg[5] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG5_INDEX_MIN 0 ///< Min of Hdmi Reg[5] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG5_INDEX_MAX 0xff ///< Max of Hdmi Reg[5] Index

///Hdmi Reg[5] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG5_VAL_MIN 0 ///< Min of Hdmi Reg[5] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG5_VAL_MAX 0xff ///< Max of Hdmi Reg[5] Value

///Hdmi Reg[6] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG6_INDEX_MIN 0 ///< Min of Hdmi Reg[6] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG6_INDEX_MAX 0xff ///< Max of Hdmi Reg[6] Index

///Hdmi Reg[6] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG6_VAL_MIN 0 ///< Min of Hdmi Reg[6] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG6_VAL_MAX 0xff ///< Max of Hdmi Reg[6] Value

///Hdmi Reg[7] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG7_INDEX_MIN 0 ///< Min of Hdmi Reg[7] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG7_INDEX_MAX 0xff ///< Max of Hdmi Reg[7] Index

///Hdmi Reg[7] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG7_VAL_MIN 0 ///< Min of Hdmi Reg[7] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG7_VAL_MAX 0xff ///< Max of Hdmi Reg[7] Value

///Hdmi Reg[8] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG8_INDEX_MIN 0 ///< Min of Hdmi Reg[8] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG8_INDEX_MAX 0xff ///< Max of Hdmi Reg[8] Index

///Hdmi Reg[8] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG8_VAL_MIN 0 ///< Min of Hdmi Reg[8] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDMI_REG8_VAL_MAX 0xff ///< Max of Hdmi Reg[8] Value

///DP1 Hdmi6G Register Setting Enable
///DP1 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG_SETTING_EN;

///Hdmi6G Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG0_INDEX_MIN 0 ///< Min of Hdmi6G Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG0_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[0] Index

///Hdmi6G Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG0_VAL_MIN 0 ///< Min of Hdmi6G Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG0_VAL_MAX 0xff ///< Max of Hdmi6G Reg[0] Value

///Hdmi6G Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG1_INDEX_MIN 0 ///< Min of Hdmi6G Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG1_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[1] Index

///Hdmi6G Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG1_VAL_MIN 0 ///< Min of Hdmi6G Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG1_VAL_MAX 0xff ///< Max of Hdmi6G Reg[1] Value

///Hdmi6G Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG2_INDEX_MIN 0 ///< Min of Hdmi6G Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG2_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[2] Index

///Hdmi6G Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG2_VAL_MIN 0 ///< Min of Hdmi6G Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P1_HDM_I6_G_REG2_VAL_MAX 0xff ///< Max of Hdmi6G Reg[2] Value

///DP2 retimer-redriver Enable
///retimer-redriver Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P2_HDMI_RE_DRIVER_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P2_HDMI_RE_DRIVER_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P2_HDMI_RE_DRIVER_EN;

///DP2 Hdmi Slave Address
///Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P2_EXT_HDMI_RE_DRV_SLV_ADDR_MIN 0 ///< Min of DP2 Hdmi Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P2_EXT_HDMI_RE_DRV_SLV_ADDR_MAX 0xff ///< Max of DP2 Hdmi Slave Address

///DP2 Hdmi Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P2_EXT_HDMI_RE_DRV_REG_NUM_MIN 0 ///< Min of DP2 Hdmi Register Number
#define IDSOPT_DBG_GNB_GFX_D_P2_EXT_HDMI_RE_DRV_REG_NUM_MAX 0x9 ///< Max of DP2 Hdmi Register Number

///DP2 Hdmi6G Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P2_EXT_HDM_I6_G_RE_DRV_REG_NUM_MIN 0 ///< Min of DP2 Hdmi6G Register Number
#define IDSOPT_DBG_GNB_GFX_D_P2_EXT_HDM_I6_G_RE_DRV_REG_NUM_MAX 0x3 ///< Max of DP2 Hdmi6G Register Number

///DP2 Hdmi Register Setting Enable
///DP2 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG_SETTING_EN;

///Hdmi Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG0_INDEX_MIN 0 ///< Min of Hdmi Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG0_INDEX_MAX 0xff ///< Max of Hdmi Reg[0] Index

///Hdmi Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG0_VAL_MIN 0 ///< Min of Hdmi Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG0_VAL_MAX 0xff ///< Max of Hdmi Reg[0] Value

///Hdmi Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG1_INDEX_MIN 0 ///< Min of Hdmi Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG1_INDEX_MAX 0xff ///< Max of Hdmi Reg[1] Index

///Hdmi Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG1_VAL_MIN 0 ///< Min of Hdmi Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG1_VAL_MAX 0xff ///< Max of Hdmi Reg[1] Value

///Hdmi Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG2_INDEX_MIN 0 ///< Min of Hdmi Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG2_INDEX_MAX 0xff ///< Max of Hdmi Reg[2] Index

///Hdmi Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG2_VAL_MIN 0 ///< Min of Hdmi Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG2_VAL_MAX 0xff ///< Max of Hdmi Reg[2] Value

///Hdmi Reg[3] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG3_INDEX_MIN 0 ///< Min of Hdmi Reg[3] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG3_INDEX_MAX 0xff ///< Max of Hdmi Reg[3] Index

///Hdmi Reg[3] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG3_VAL_MIN 0 ///< Min of Hdmi Reg[3] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG3_VAL_MAX 0xff ///< Max of Hdmi Reg[3] Value

///Hdmi Reg[4] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG4_INDEX_MIN 0 ///< Min of Hdmi Reg[4] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG4_INDEX_MAX 0xff ///< Max of Hdmi Reg[4] Index

///Hdmi Reg[4] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG4_VAL_MIN 0 ///< Min of Hdmi Reg[4] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG4_VAL_MAX 0xff ///< Max of Hdmi Reg[4] Value

///Hdmi Reg[5] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG5_INDEX_MIN 0 ///< Min of Hdmi Reg[5] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG5_INDEX_MAX 0xff ///< Max of Hdmi Reg[5] Index

///Hdmi Reg[5] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG5_VAL_MIN 0 ///< Min of Hdmi Reg[5] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG5_VAL_MAX 0xff ///< Max of Hdmi Reg[5] Value

///Hdmi Reg[6] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG6_INDEX_MIN 0 ///< Min of Hdmi Reg[6] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG6_INDEX_MAX 0xff ///< Max of Hdmi Reg[6] Index

///Hdmi Reg[6] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG6_VAL_MIN 0 ///< Min of Hdmi Reg[6] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG6_VAL_MAX 0xff ///< Max of Hdmi Reg[6] Value

///Hdmi Reg[7] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG7_INDEX_MIN 0 ///< Min of Hdmi Reg[7] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG7_INDEX_MAX 0xff ///< Max of Hdmi Reg[7] Index

///Hdmi Reg[7] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG7_VAL_MIN 0 ///< Min of Hdmi Reg[7] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG7_VAL_MAX 0xff ///< Max of Hdmi Reg[7] Value

///Hdmi Reg[8] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG8_INDEX_MIN 0 ///< Min of Hdmi Reg[8] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG8_INDEX_MAX 0xff ///< Max of Hdmi Reg[8] Index

///Hdmi Reg[8] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG8_VAL_MIN 0 ///< Min of Hdmi Reg[8] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDMI_REG8_VAL_MAX 0xff ///< Max of Hdmi Reg[8] Value

///DP2 Hdmi6G Register Setting Enable
///DP2 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG_SETTING_EN;

///Hdmi6G Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG0_INDEX_MIN 0 ///< Min of Hdmi6G Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG0_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[0] Index

///Hdmi6G Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG0_VAL_MIN 0 ///< Min of Hdmi6G Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG0_VAL_MAX 0xff ///< Max of Hdmi6G Reg[0] Value

///Hdmi6G Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG1_INDEX_MIN 0 ///< Min of Hdmi6G Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG1_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[1] Index

///Hdmi6G Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG1_VAL_MIN 0 ///< Min of Hdmi6G Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG1_VAL_MAX 0xff ///< Max of Hdmi6G Reg[1] Value

///Hdmi6G Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG2_INDEX_MIN 0 ///< Min of Hdmi6G Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG2_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[2] Index

///Hdmi6G Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG2_VAL_MIN 0 ///< Min of Hdmi6G Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P2_HDM_I6_G_REG2_VAL_MAX 0xff ///< Max of Hdmi6G Reg[2] Value

///DP3 retimer-redriver Enable
///retimer-redriver Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P3_HDMI_RE_DRIVER_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P3_HDMI_RE_DRIVER_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P3_HDMI_RE_DRIVER_EN;

///DP3 Hdmi Slave Address
///Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P3_EXT_HDMI_RE_DRV_SLV_ADDR_MIN 0 ///< Min of DP3 Hdmi Slave Address
#define IDSOPT_DBG_GNB_GFX_D_P3_EXT_HDMI_RE_DRV_SLV_ADDR_MAX 0xff ///< Max of DP3 Hdmi Slave Address

///DP3 Hdmi Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P3_EXT_HDMI_RE_DRV_REG_NUM_MIN 0 ///< Min of DP3 Hdmi Register Number
#define IDSOPT_DBG_GNB_GFX_D_P3_EXT_HDMI_RE_DRV_REG_NUM_MAX 0x9 ///< Max of DP3 Hdmi Register Number

///DP3 Hdmi6G Register Number
///Register Number
#define IDSOPT_DBG_GNB_GFX_D_P3_EXT_HDM_I6_G_RE_DRV_REG_NUM_MIN 0 ///< Min of DP3 Hdmi6G Register Number
#define IDSOPT_DBG_GNB_GFX_D_P3_EXT_HDM_I6_G_RE_DRV_REG_NUM_MAX 0x3 ///< Max of DP3 Hdmi6G Register Number

///DP3 Hdmi Register Setting Enable
///DP3 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG_SETTING_EN;

///Hdmi Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG0_INDEX_MIN 0 ///< Min of Hdmi Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG0_INDEX_MAX 0xff ///< Max of Hdmi Reg[0] Index

///Hdmi Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG0_VAL_MIN 0 ///< Min of Hdmi Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG0_VAL_MAX 0xff ///< Max of Hdmi Reg[0] Value

///Hdmi Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG1_INDEX_MIN 0 ///< Min of Hdmi Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG1_INDEX_MAX 0xff ///< Max of Hdmi Reg[1] Index

///Hdmi Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG1_VAL_MIN 0 ///< Min of Hdmi Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG1_VAL_MAX 0xff ///< Max of Hdmi Reg[1] Value

///Hdmi Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG2_INDEX_MIN 0 ///< Min of Hdmi Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG2_INDEX_MAX 0xff ///< Max of Hdmi Reg[2] Index

///Hdmi Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG2_VAL_MIN 0 ///< Min of Hdmi Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG2_VAL_MAX 0xff ///< Max of Hdmi Reg[2] Value

///Hdmi Reg[3] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG3_INDEX_MIN 0 ///< Min of Hdmi Reg[3] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG3_INDEX_MAX 0xff ///< Max of Hdmi Reg[3] Index

///Hdmi Reg[3] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG3_VAL_MIN 0 ///< Min of Hdmi Reg[3] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG3_VAL_MAX 0xff ///< Max of Hdmi Reg[3] Value

///Hdmi Reg[4] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG4_INDEX_MIN 0 ///< Min of Hdmi Reg[4] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG4_INDEX_MAX 0xff ///< Max of Hdmi Reg[4] Index

///Hdmi Reg[4] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG4_VAL_MIN 0 ///< Min of Hdmi Reg[4] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG4_VAL_MAX 0xff ///< Max of Hdmi Reg[4] Value

///Hdmi Reg[5] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG5_INDEX_MIN 0 ///< Min of Hdmi Reg[5] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG5_INDEX_MAX 0xff ///< Max of Hdmi Reg[5] Index

///Hdmi Reg[5] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG5_VAL_MIN 0 ///< Min of Hdmi Reg[5] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG5_VAL_MAX 0xff ///< Max of Hdmi Reg[5] Value

///Hdmi Reg[6] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG6_INDEX_MIN 0 ///< Min of Hdmi Reg[6] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG6_INDEX_MAX 0xff ///< Max of Hdmi Reg[6] Index

///Hdmi Reg[6] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG6_VAL_MIN 0 ///< Min of Hdmi Reg[6] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG6_VAL_MAX 0xff ///< Max of Hdmi Reg[6] Value

///Hdmi Reg[7] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG7_INDEX_MIN 0 ///< Min of Hdmi Reg[7] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG7_INDEX_MAX 0xff ///< Max of Hdmi Reg[7] Index

///Hdmi Reg[7] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG7_VAL_MIN 0 ///< Min of Hdmi Reg[7] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG7_VAL_MAX 0xff ///< Max of Hdmi Reg[7] Value

///Hdmi Reg[8] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG8_INDEX_MIN 0 ///< Min of Hdmi Reg[8] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG8_INDEX_MAX 0xff ///< Max of Hdmi Reg[8] Index

///Hdmi Reg[8] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG8_VAL_MIN 0 ///< Min of Hdmi Reg[8] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDMI_REG8_VAL_MAX 0xff ///< Max of Hdmi Reg[8] Value

///DP3 Hdmi6G Register Setting Enable
///DP3 Register Setting Enable
typedef enum {
  IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG_SETTING_EN_AUTO = 0xff,///<Auto
  IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG_SETTING_EN_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG_SETTING_EN;

///Hdmi6G Reg[0] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG0_INDEX_MIN 0 ///< Min of Hdmi6G Reg[0] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG0_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[0] Index

///Hdmi6G Reg[0] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG0_VAL_MIN 0 ///< Min of Hdmi6G Reg[0] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG0_VAL_MAX 0xff ///< Max of Hdmi6G Reg[0] Value

///Hdmi6G Reg[1] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG1_INDEX_MIN 0 ///< Min of Hdmi6G Reg[1] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG1_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[1] Index

///Hdmi6G Reg[1] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG1_VAL_MIN 0 ///< Min of Hdmi6G Reg[1] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG1_VAL_MAX 0xff ///< Max of Hdmi6G Reg[1] Value

///Hdmi6G Reg[2] Index
///I2c Register Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG2_INDEX_MIN 0 ///< Min of Hdmi6G Reg[2] Index
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG2_INDEX_MAX 0xff ///< Max of Hdmi6G Reg[2] Index

///Hdmi6G Reg[2] Value
///I2c Register Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG2_VAL_MIN 0 ///< Min of Hdmi6G Reg[2] Value
#define IDSOPT_DBG_GNB_GFX_D_P3_HDM_I6_G_REG2_VAL_MAX 0xff ///< Max of Hdmi6G Reg[2] Value

///SATA PHY Tuning
typedef enum {
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_NONE = 0,///<None
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_SHORTERTRACELENGTH = 4,///<Shorter Trace Length
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_LONGERTRACELENGTH = 5,///<Longer Trace Length
  IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_SATA_PHY_TUNING;

///PCIe lanes topology
///Set PCIe lanes Topology
typedef enum {
  IDSOPT_DBG_GNB_PCIE_LANES_TOPO_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_LANES_TOPO_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_LANES_TOPO;

///Dev1Func1 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_ENGINE_TYPE;

///Dev1Func1 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_START_LANE_ID_MIN 0 ///< Min of Dev1Func1 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_START_LANE_ID_MAX 0xff ///< Max of Dev1Func1 Start Lane ID

///Dev1Func1 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_END_LANE_ID_MIN 0 ///< Min of Dev1Func1 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC1_END_LANE_ID_MAX 0xff ///< Max of Dev1Func1 End Lane ID

///Dev1Func2 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_ENGINE_TYPE;

///Dev1Func2 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_START_LANE_ID_MIN 0 ///< Min of Dev1Func2 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_START_LANE_ID_MAX 0xff ///< Max of Dev1Func2 Start Lane ID

///Dev1Func2 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_END_LANE_ID_MIN 0 ///< Min of Dev1Func2 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC2_END_LANE_ID_MAX 0xff ///< Max of Dev1Func2 End Lane ID

///Dev1Func3 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_ENGINE_TYPE;

///Dev1Func3 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_START_LANE_ID_MIN 0 ///< Min of Dev1Func3 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_START_LANE_ID_MAX 0xff ///< Max of Dev1Func3 Start Lane ID

///Dev1Func3 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_END_LANE_ID_MIN 0 ///< Min of Dev1Func3 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC3_END_LANE_ID_MAX 0xff ///< Max of Dev1Func3 End Lane ID

///Dev1Func4 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_ENGINE_TYPE;

///Dev1Func4 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_START_LANE_ID_MIN 0 ///< Min of Dev1Func4 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_START_LANE_ID_MAX 0xff ///< Max of Dev1Func4 Start Lane ID

///Dev1Func4 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_END_LANE_ID_MIN 0 ///< Min of Dev1Func4 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC4_END_LANE_ID_MAX 0xff ///< Max of Dev1Func4 End Lane ID

///Dev1Func5 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_ENGINE_TYPE;

///Dev1Func5 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_START_LANE_ID_MIN 0 ///< Min of Dev1Func5 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_START_LANE_ID_MAX 0xff ///< Max of Dev1Func5 Start Lane ID

///Dev1Func5 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_END_LANE_ID_MIN 0 ///< Min of Dev1Func5 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC5_END_LANE_ID_MAX 0xff ///< Max of Dev1Func5 End Lane ID

///Dev1Func6 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_ENGINE_TYPE;

///Dev1Func6 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_START_LANE_ID_MIN 0 ///< Min of Dev1Func6 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_START_LANE_ID_MAX 0xff ///< Max of Dev1Func6 Start Lane ID

///Dev1Func6 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_END_LANE_ID_MIN 0 ///< Min of Dev1Func6 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC6_END_LANE_ID_MAX 0xff ///< Max of Dev1Func6 End Lane ID

///Dev1Func7 Engine type
///set the engine type
typedef enum {
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_ENGINE_TYPE_UNUSEDENGINE = 0,///<Unused Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_ENGINE_TYPE_PCIEENGINE = 0x1,///<Pcie Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_ENGINE_TYPE_SATAENGINE = 0x3,///<SATA Engine
  IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_ENGINE_TYPE_ETHERNETENGINE = 0x10,///<Ethernet Engine
} IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_ENGINE_TYPE;

///Dev1Func7 Start Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_START_LANE_ID_MIN 0 ///< Min of Dev1Func7 Start Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_START_LANE_ID_MAX 0xff ///< Max of Dev1Func7 Start Lane ID

///Dev1Func7 End Lane ID
///[255] - Not allocated\nStart - End Lane ID\n 0       0, 1, 3\n 1       0, 1\n 2       2, 3\n 3       0, 2, 3\n 4       4, 5, 7, 11\n 5       4, 5\n 6       6, 7\n 7       4, 6, 7\n 8       8, 9, 11, 15\n 9       8, 9\n 10      10, 11\n 11      4, 8, 10, 11\n 12      12, 13, 15\n 13      12, 13\n 14      14, 15\n 15      8, 12, 14, 15\n\nCannot assign overlapping groups of lanes between ports.
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_END_LANE_ID_MIN 0 ///< Min of Dev1Func7 End Lane ID
#define IDSOPT_DBG_GNB_PCIE_DEV1_FUNC7_END_LANE_ID_MAX 0xff ///< Max of Dev1Func7 End Lane ID

///Port Training(PCIe Port0)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT0_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT0_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_TRAINING;

///Hotplug Support(PCIe Port0)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT0_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT0_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT0_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_HOTPLUG;

///Speed Mode(PCIe Port0)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT0_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT0_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT0_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT0_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_SPEED_MODE;

///Compliance Mode(PCIe Port0)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT0_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT0_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_COMPLIANCE_MODE;

///Link ASPM(PCIe Port0)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT0_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT0_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(Pcie Port0)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT0_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT0_POWEROFF_IN_L1_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PORT0_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_PORT0_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port0) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT0_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT0_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port0)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT0_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port0)
#define IDSOPT_DBG_GNB_PCIE_PORT0_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port0)

///L1 Immediate ACK(PCIe Port0)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT0_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT0_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_L1_IMM_ACK;

///TX De-emphasis(PCIe Port0)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_TX_DEEMPHASIS;

///TX Margin(PCIe Port0)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_TX_MARGIN;

///Scrambler control(PCIe Port0)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT0_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT0_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port0)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT0_EQUAL_SEARCH_MODE_GRADIENTSEARCH = 0,///<Gradient Search
  IDSOPT_GNB_DBG_PORT0_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT0_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT0_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT0_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT0_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port0)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT0_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_CFG_USC_EQ_NOT_REQD;

///PM L1 SS
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT0_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT0_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT0_PM_L1_SS;

///L1.1
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT0_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT0_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT0_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT0_L1_1;

///L1.2
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT0_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT0_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT0_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT0_L1_2;

///LC FOM TIME(PCIe Port0)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT0_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT0_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT0_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT0_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT0_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT0_LC_FOM_TIME;

///Port Reversal(PCIe Port0)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT0_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT0_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT0_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT0_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port0)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_CFG_DS_TX_PRESET;

///Upstream Tx Preset(PCIe Port0)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT0_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(PCIe Port0)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT0_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(PCIe Port0)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT0_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_CFG_US_RX_HINT;

///Bypass Gen3 EQ(PCIe Port0)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT0_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port0)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT0_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIe Port0)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT0_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port0)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT0_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_SRIS_SRNS;

///SRIS_EN(PCIe Port0)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT0_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port0)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT0_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port0)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT0_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT0_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT0_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port0)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT0_MAX_PAYLOAD_SIZE;

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port0)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port0)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT0_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT0_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT0_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT0_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT0_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT0_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Initial Offset Calibration Enable(PCIe Port0)
///Defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT0_INIT_OFFSET_CANCELLATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PORT0_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT0_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT0_INIT_OFFSET_CANCELLATION;

///Gen3 DFE Control(PCIe Port0)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT0_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT0_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT0_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT0_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT0_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT0_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT0_DFE_CONTROL;

///LEQ Control(PCIe Port0)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT0_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT0_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT0_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT0_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT0_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port0)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT0_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT0_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT0_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT0_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port0)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT0_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT0_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT0_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT0_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port0)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT0_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT0_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT0_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT0_PI_OFFSET_CALIBRATION;

///Flow Control Credits Control(PCIe Port0)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT0_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT0_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT0_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port0)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT0_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port0)
#define IDSOPT_DBG_GNB_PORT0_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port0)

///NP-DATA(PCIe Port0)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT0_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port0)
#define IDSOPT_DBG_GNB_PORT0_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port0)

///P-HDR(PCIe Port0)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT0_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port0)
#define IDSOPT_DBG_GNB_PORT0_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port0)

///P-DATA(PCIe Port0)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT0_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port0)
#define IDSOPT_DBG_GNB_PORT0_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port0)

///CPL-HDR(PCIe Port0)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT0_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port0)
#define IDSOPT_DBG_GNB_PORT0_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port0)

///CPL-DATA(PCIe Port0)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT0_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port0)
#define IDSOPT_DBG_GNB_PORT0_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port0)

///Gen1(PCIe Port0)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT0_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT0_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT0_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT0_SPC_GEN1;

///Gen2(PCIe Port0)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_D1_F1_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_D1_F1_SPC_GEN2;

///Port Training(PCIe Port1)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT1_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT1_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_TRAINING;

///Hotplug Support(PCIe Port1)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT1_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT1_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT1_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_HOTPLUG;

///Speed Mode(PCIe Port1)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT1_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT1_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT1_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT1_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_SPEED_MODE;

///Compliance Mode(PCIe Port1)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT1_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT1_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_COMPLIANCE_MODE;

///Link ASPM(PCIe Port1)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT1_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT1_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(Pcie Port1)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT1_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT1_POWEROFF_IN_L1_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PORT1_POWEROFF_IN_L1_DISABLED = 16,///<Disabled
} IDSOPT_DBG_NBIO_PORT1_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port1) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT1_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT1_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port1)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT1_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port1)
#define IDSOPT_DBG_GNB_PCIE_PORT1_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port1)

///L1 Immediate ACK(PCIe Port1)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT1_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT1_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_L1_IMM_ACK;

///TX De-emphasis(PCIe Port1)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_TX_DEEMPHASIS;

///TX Margin(PCIe Port1)
///TX Margin
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_0 = 0,///<0
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_1 = 1,///<1
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_2 = 2,///<2
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_3 = 3,///<3
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_4 = 4,///<4
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_5 = 5,///<5
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_6 = 6,///<6
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_7 = 7,///<7
  IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_TX_MARGIN;

///Scrambler control(PCIe Port1)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT1_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT1_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port1)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT1_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT1_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT1_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT1_EQUAL_SEARCH_MODE_PRESET = 3,///<Preset 
  IDSOPT_GNB_DBG_PORT1_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT1_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port1)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT1_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(PCIe Port1)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT1_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT1_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT1_PM_L1_SS;

///L1.1(PCIe Port1)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT1_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT1_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT1_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT1_L1_1;

///L1.2(PCIe Port1)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT1_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT1_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT1_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT1_L1_2;

///LC FOM TIME(PCIe Port1)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT1_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT1_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT1_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT1_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT1_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT1_LC_FOM_TIME;

///Port Reversal(PCIe Port1)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT1_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT1_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT1_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT1_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port1)
///Set downstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_CFG_DS_TX_PRESET;

///Upstream Tx Preset(PCIe Port1)
///Set upstream Tx preset
typedef enum {
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P0 = 0,///<P0
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P1 = 1,///<P1
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P2 = 2,///<P2
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P3 = 3,///<P3
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P4 = 4,///<P4
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P5 = 5,///<P5
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P6 = 6,///<P6
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P7 = 7,///<P7
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P8 = 8,///<P8
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P9 = 9,///<P9
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_P10 = 0xA,///<P10
  IDSOPT_GNB_PORT1_CFG_US_TX_PRESET_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_CFG_US_TX_PRESET;

///Downstream Rx Preset Hint(PCIe Port1)
///Set downstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT1_CFG_DS_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_CFG_DS_RX_HINT;

///Upstream Rx Preset Hint(PCIe Port1)
///Set upstream Rx preset hint
typedef enum {
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P0 = 0,///<P0
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P1 = 1,///<P1
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P2 = 2,///<P2
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P3 = 3,///<P3
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P4 = 4,///<P4
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P5 = 5,///<P5
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P6 = 6,///<P6
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_P7 = 7,///<P7
  IDSOPT_GNB_PORT1_CFG_US_RX_HINT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_CFG_US_RX_HINT;

///Bypass Gen3 EQ(PCIe Port1)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT1_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port1)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT1_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIe Port1)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT1_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port1)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT1_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_SRIS_SRNS;

///SRIS_EN(PCIe Port1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT1_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT1_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port1)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT1_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT1_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT1_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port1)
///Max allowed payload size in bytes
typedef enum {
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_128 = 0,///<MAX_PAYLOAD_128
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_256 = 1,///<MAX_PAYLOAD_256
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_512 = 2,///<MAX_PAYLOAD_512
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_1024 = 3,///<MAX_PAYLOAD_1024
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_2048 = 4,///<MAX_PAYLOAD_2048
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_MAX_PAYLOAD_4096 = 5,///<MAX_PAYLOAD_4096
  IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT1_MAX_PAYLOAD_SIZE;

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port1)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port1)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT1_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT1_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT1_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT1_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT1_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT1_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Gen3 DFE Control(PCIe Port1)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT1_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT1_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT1_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT1_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT1_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT1_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT1_DFE_CONTROL;

///LEQ Control(PCIe Port1)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT1_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT1_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT1_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT1_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT1_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port1)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT1_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT1_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT1_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT1_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port1)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT1_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT1_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT1_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT1_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port1)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT1_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT1_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT1_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT1_PI_OFFSET_CALIBRATION;

///Initial Offset calibration(PCIe Port1)
///defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT1_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_PORT1_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT1_INIT_OFFSET_CANCELLATION_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_PORT1_INIT_OFFSET_CANCELLATION;

///Flow Control Credits Control(PCIe Port1)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT1_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT1_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT1_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port1)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT1_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port1)
#define IDSOPT_DBG_GNB_PORT1_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port1)

///NP-DATA(PCIe Port1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT1_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port1)
#define IDSOPT_DBG_GNB_PORT1_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port1)

///P-HDR(PCIe Port1)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT1_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port1)
#define IDSOPT_DBG_GNB_PORT1_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port1)

///P-DATA(PCIe Port1)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT1_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port1)
#define IDSOPT_DBG_GNB_PORT1_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port1)

///CPL-HDR(PCIe Port1)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT1_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port1)
#define IDSOPT_DBG_GNB_PORT1_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port1)

///CPL-DATA(PCIe Port1)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT1_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port1)
#define IDSOPT_DBG_GNB_PORT1_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port1)

///Gen1(PCIe Port1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN1;

///Gen2(PCIe Port1)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT1_SPC_GEN2;

///Port Training(PCIe Port2)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_TRAINING;

///Hotplug Support(PCIe Port2)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_HOTPLUG;

///Speed Mode(PCIe Port2)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_SPEED_MODE;

///Compliance Mode(PCIe Port2)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_COMPLIANCE_MODE;

///Link ASPM(PCIe Port2)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(Pcie Port2)
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1_ENABLE = 1,///<Enable
  IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_PORT2_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port2) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port2)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port2)
#define IDSOPT_DBG_GNB_PCIE_PORT2_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port2)

///L1 Immediate ACK(PCIe Port2)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_L1_IMM_ACK;

///TX De-emphasis(PCIe Port2)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_TX_DEEMPHASIS;

///TX Margin(PCIe Port2)
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

///Scrambler control(PCIe Port2)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port2)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT2_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port2)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(PCIe Port2)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT2_PM_L1_SS;

///L1.1(PCIe Port2)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT2_L1_1;

///L1.2(PCIe Port2)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT2_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT2_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT2_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT2_L1_2;

///LC FOM TIME(PCIe Port2)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT2_LC_FOM_TIME;

///Port Reversal(PCIe Port2)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT2_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port2)
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

///Upstream Tx Preset(PCIe Port2)
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

///Downstream Rx Preset Hint(PCIe Port2)
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

///Upstream Rx Preset Hint(PCIe Port2)
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

///Bypass Gen3 EQ(PCIe Port2)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port2)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIe Port2)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port2)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_SRNS;

///SRIS_EN(PCIe Port2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port2)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT2_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port2)
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

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port2)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port2)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT2_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT2_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT2_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT2_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT2_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT2_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Initial Offset Calibration Enable(PCIe Port2)
///Defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT2_INIT_OFFSET_CANCELLATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PORT2_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT2_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT2_INIT_OFFSET_CANCELLATION;

///Gen3 DFE Control(PCIe Port2)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT2_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT2_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT2_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT2_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT2_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT2_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT2_DFE_CONTROL;

///LEQ Control(PCIe Port2)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT2_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT2_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT2_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT2_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT2_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port2)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT2_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT2_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT2_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT2_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port2)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT2_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT2_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT2_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT2_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port2)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT2_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT2_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT2_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT2_PI_OFFSET_CALIBRATION;

///Flow Control Credits Control(PCIe Port2)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT2_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT2_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT2_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port2)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port2)
#define IDSOPT_DBG_GNB_PORT2_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port2)

///NP-DATA(PCIe Port2)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port2)
#define IDSOPT_DBG_GNB_PORT2_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port2)

///P-HDR(PCIe Port2)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port2)
#define IDSOPT_DBG_GNB_PORT2_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port2)

///P-DATA(PCIe Port2)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT2_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port2)
#define IDSOPT_DBG_GNB_PORT2_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port2)

///CPL-HDR(PCIe Port2)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT2_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port2)
#define IDSOPT_DBG_GNB_PORT2_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port2)

///CPL-DATA(PCIe Port2)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT2_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port2)
#define IDSOPT_DBG_GNB_PORT2_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port2)

///Gen1(PCIe Port2)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN1;

///Gen2(PCIe Port2)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT2_SPC_GEN2;

///Port Training(PCIe Port3)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_TRAINING;

///Hotplug Support(PCIe Port3)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_HOTPLUG;

///Speed Mode(PCIe Port3)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_SPEED_MODE;

///Compliance Mode(PCIe Port3)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_COMPLIANCE_MODE;

///Link ASPM(PCIe Port3)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(PCIe Port3)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT3_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port3) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port3)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port3)
#define IDSOPT_DBG_GNB_PCIE_PORT3_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port3)

///L1 Immediate ACK(PCIe Port3)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_L1_IMM_ACK;

///TX De-emphasis(PCIe Port3)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_TX_DEEMPHASIS;

///TX Margin(PCIe Port3)
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

///Scrambler control(PCIe Port3)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port3)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_PRESETSEARCH = 0x3,///<Preset Search
  IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT3_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port3)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(PCIe Port3)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT3_PM_L1_SS;

///L1.1(PCIe Port3)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT3_L1_1;

///L1.2(PCIe Port3)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT3_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT3_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT3_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT3_L1_2;

///Dynamic Lanes Power State for Linkwidth Switch(Dev1Func4)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT3_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(PCIe Port3)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT3_LC_FOM_TIME;

///Port Reversal(PCIe Port3)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT3_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port3)
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

///Upstream Tx Preset(PCIe Port3)
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

///Downstream Rx Preset Hint(PCIe Port3)
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

///Upstream Rx Preset Hint(PCIe Port3)
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

///Bypass Gen3 EQ(PCIe Port3)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port3)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIe Port3)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port3)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_SRNS;

///SRIS_EN(PCIe Port3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port3)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT3_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port3)
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

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port3)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port3)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT3_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT3_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT3_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT3_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT3_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT3_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Initial Offset Calibration Enable(PCIe Port3)
///Defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT3_INIT_OFFSET_CANCELLATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PORT3_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT3_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT3_INIT_OFFSET_CANCELLATION;

///Gen3 DFE Control(PCIe Port3)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT3_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT3_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT3_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT3_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT3_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT3_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT3_DFE_CONTROL;

///LEQ Control(PCIe Port3)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT3_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT3_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT3_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT3_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT3_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port3)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT3_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT3_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT3_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT3_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port3)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT3_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT3_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT3_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT3_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port3)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT3_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT3_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT3_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT3_PI_OFFSET_CALIBRATION;

///Flow Control Credits Control(PCIe Port3)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT3_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT3_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT3_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port3)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port3)
#define IDSOPT_DBG_GNB_PORT3_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port3)

///NP-DATA(PCIe Port3)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port3)
#define IDSOPT_DBG_GNB_PORT3_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port3)

///P-HDR(PCIe Port3)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port3)
#define IDSOPT_DBG_GNB_PORT3_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port3)

///P-DATA(PCIe Port3)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT3_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port3)
#define IDSOPT_DBG_GNB_PORT3_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port3)

///CPL-HDR(PCIe Port3)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT3_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port3)
#define IDSOPT_DBG_GNB_PORT3_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port3)

///CPL-DATA(PCIe Port3)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT3_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port3)
#define IDSOPT_DBG_GNB_PORT3_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port3)

///Gen1(PCIe Port3)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN1;

///Gen2(PCIe Port3)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT3_SPC_GEN2;

///Port Training(PCIe Port4)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_TRAINING;

///Hotplug Support(PCIe Port4)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_HOTPLUG;

///Speed Mode(PCIe Port4)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_SPEED_MODE;

///Compliance Mode(PCIe Port4)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_COMPLIANCE_MODE;

///Link ASPM(PCIe Port4)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(PCIe Port4)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT4_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port4) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port4)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port4)
#define IDSOPT_DBG_GNB_PCIE_PORT4_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port4)

///L1 Immediate ACK(PCIe Port4)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_L1_IMM_ACK;

///TX De-emphasis(PCIe Port4)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_TX_DEEMPHASIS;

///TX Margin(PCIe Port4)
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

///Scrambler control(PCIe Port4)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port4)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT4_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port4)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(PCIe Port4)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT4_PM_L1_SS;

///L1.1(PCIe Port4)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT4_L1_1;

///L1.2(PCIe Port4)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT4_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT4_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT4_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT4_L1_2;

///Dynamic Lanes Power State for Linkwidth Switch(PCIe Port4)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT4_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(PCIe Port4)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT4_LC_FOM_TIME;

///Port Reversal(PCIe Port4)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT4_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port4)
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

///Upstream Tx Preset(PCIe Port4)
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

///Downstream Rx Preset Hint(PCIe Port4)
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

///Upstream Rx Preset Hint(PCIe Port4)
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

///Bypass Gen3 EQ(PCIe Port4)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port4)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIePort4)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port4)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_SRNS;

///SRIS_EN(PCIe Port4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port4)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT4_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port4)
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

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port4)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port4)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT4_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT4_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT4_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT4_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT4_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT4_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Initial Offset Calibration Enable(PCIe Port4)
///Defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT4_INIT_OFFSET_CANCELLATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PORT4_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT4_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT4_INIT_OFFSET_CANCELLATION;

///Gen3 DFE Control(PCIe Port4)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT4_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT4_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT4_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT4_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT4_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT4_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT4_DFE_CONTROL;

///LEQ Control(PCIe Port4)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT4_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT4_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT4_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT4_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT4_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port4)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT4_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT4_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT4_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT4_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port4)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT4_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT4_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT4_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT4_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port4)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT4_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT4_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT4_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT4_PI_OFFSET_CALIBRATION;

///Flow Control Credits Control(PCIe Port4)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT4_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT4_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT4_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port4)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port4)
#define IDSOPT_DBG_GNB_PORT4_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port4)

///NP-DATA(PCIe Port4)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port4)
#define IDSOPT_DBG_GNB_PORT4_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port4)

///P-HDR(PCIe Port4)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port4)
#define IDSOPT_DBG_GNB_PORT4_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port4)

///P-DATA(PCIe Port4)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT4_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port4)
#define IDSOPT_DBG_GNB_PORT4_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port4)

///CPL-HDR(PCIe Port4)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT4_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port4)
#define IDSOPT_DBG_GNB_PORT4_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port4)

///CPL-DATA(PCIe Port4)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT4_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port4)
#define IDSOPT_DBG_GNB_PORT4_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port4)

///Gen1(PCIe Port4)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN1;

///Gen2(PCIe Port4)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT4_SPC_GEN2;

///Port Training(PCIe Port5)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_TRAINING;

///Hotplug Support(PCIe Port5)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_HOTPLUG;

///Speed Mode(PCIe Port5)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_SPEED_MODE;

///Compliance Mode(PCIe Port5)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_COMPLIANCE_MODE;

///Link ASPM(PCIe Port5)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(PCIe Port5)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT5_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port5) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port5)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port5)
#define IDSOPT_DBG_GNB_PCIE_PORT5_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port5)

///L1 Immediate ACK(PCIe Port5)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_L1_IMM_ACK;

///TX De-emphasis(PCIe Port5)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_TX_DEEMPHASIS;

///TX Margin(PCIe Port5)
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

///Scrambler control(PCIe Port5)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT7_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port5)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_PRESETSEARCH = 0x03,///<Preset Search
  IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PORT5_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port5)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(PCIe Port5)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT5_PM_L1_SS;

///L1.1(PCIe Port5)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT5_L1_1;

///L1.2(PCIe Port5)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT5_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT5_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT5_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT5_L1_2;

///Dynamic Lanes Power State for Linkwidth Switch(PCIe Port5)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT5_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(PCIe Port5)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT5_LC_FOM_TIME;

///Port Reversal(PCIe Port5)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT5_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port5)
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

///Upstream Tx Preset(PCIe Port5)
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

///Downstream Rx Preset Hint(PCIe Port5)
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

///Upstream Rx Preset Hint(PCIe Port5)
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

///Bypass Gen3 EQ(PCIe Port5)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port5)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIe Port5)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port5)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_SRNS;

///SRIS_EN(PCIe Port5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port5)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT5_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port5)
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

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port5)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port5)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT5_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT5_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT5_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT5_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT5_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT5_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Initial Offset Calibration Enable(PCIe Port5)
///Defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT5_INIT_OFFSET_CANCELLATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PORT5_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT5_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT5_INIT_OFFSET_CANCELLATION;

///Gen3 DFE Control(PCIe Port5)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT5_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT5_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT5_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT5_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT5_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT5_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT5_DFE_CONTROL;

///LEQ Control(PCIe Port5)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT5_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT5_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT5_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT5_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT5_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port5)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT5_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT5_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT5_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT5_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port5)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT5_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT5_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT5_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT5_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port5)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT5_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT5_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT5_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT5_PI_OFFSET_CALIBRATION;

///Flow Control Credits Control(PCIe Port5)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT5_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT5_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT5_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port5)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port5)
#define IDSOPT_DBG_GNB_PORT5_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port5)

///NP-DATA(PCIe Port5)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port5)
#define IDSOPT_DBG_GNB_PORT5_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port5)

///P-HDR(PCIe Port5)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port5)
#define IDSOPT_DBG_GNB_PORT5_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port5)

///P-DATA(PCIe Port5)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT5_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port5)
#define IDSOPT_DBG_GNB_PORT5_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port5)

///CPL-HDR(PCIe Port5)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT5_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port5)
#define IDSOPT_DBG_GNB_PORT5_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port5)

///CPL-DATA(PCIe Port5)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT5_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port5)
#define IDSOPT_DBG_GNB_PORT5_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port5)

///Gen1(PCIe Port5)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN1;

///Gen2(PCIe Port5)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT5_SPC_GEN2;

///Port Training(PCIe Port6)
///Set PCIe port Training
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_TRAINING;

///Hotplug Support(PCIe Port6)
///Set Hotplug
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_DISABLED = 0,///<Disabled 
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_BASIC = 1,///<Basic
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_ENHANCED = 3,///<Enhanced
  IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_HOTPLUG;

///Speed Mode(PCIe Port6)
///Set PCIe port speed and capability
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_MAXIMUMSPEED = 0,///<Maximum speed
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_GEN1 = 1,///<GEN1
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_GEN2 = 2,///<GEN2
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_GEN3 = 3,///<GEN3
  IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_SPEED_MODE;

///Compliance Mode(PCIe Port6)
///Enable compliance mode
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_COMPLIANCE_MODE;

///Link ASPM(PCIe Port6)
///Enable port ASPM
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM_L1 = 2,///<L1
  IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_LINK_ASPM;

///Poweroff Phy Lanes and PLL in L1(PCIe Port6)
///Poweroff Phy Lanes and PLL in L1
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1_ENABLE = 1,///<Enable
} IDSOPT_DBG_NBIO_PORT6_POWEROFF_IN_L1;

///Slot Power Limit,W(PCIe Port6) Control
///Slot Power Limit in Watt
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_CTL;

///Slot Power Limit,W(PCIe Port6)
///Slot Power Limit in Watt
#define IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_MIN 0 ///< Min of Slot Power Limit,W(PCIe Port6)
#define IDSOPT_DBG_GNB_PCIE_PORT6_SLOT_POWER_LIMIT_MAX 255 ///< Max of Slot Power Limit,W(PCIe Port6)

///L1 Immediate ACK(PCIe Port6)
///L1 Immediate ACK
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_L1_IMM_ACK;

///TX De-emphasis(PCIe Port6)
///TX De-emphasis
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS_60DB = 1,///<6.0 dB
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS_35DB = 2,///<3.5 dB
  IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_TX_DEEMPHASIS;

///TX Margin(PCIe Port6)
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

///Scrambler control(PCIe Port6)
///Scrambler control
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL_DISABLED = 1,///<Disabled
  IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL_ENABLED = 2,///<Enabled
  IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_SCRAMBLER_CNTL;

///Equalization Search Mode(PCIe Port6)
///Set Equalization Search Mode
typedef enum {
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_BASICSEARCH = 0,///<Basic Search
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH = 1,///<Exhaustive Search
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_EXHAUSTIVESEARCH3X3 = 2,///<Exhaustive Search + 3x3
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_PRESETSEARCH = 3,///<Preset Search
  IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE_AUTO = 0xF,///<Auto
} IDSOPT_GNB_DBG_PORT6_EQUAL_SEARCH_MODE;

///Disable Gen3 EQ Phase2/3 (PCIe Port6)
///Disable Gen3 EQ Phase2/3
typedef enum {
  IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_CFG_USC_EQ_NOT_REQD;

///PM L1 SS(PCIe Port6)
///Enable for PM L1 SS and ASPM L1 SS
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_PM_L1_SS_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_PM_L1_SS_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT6_PM_L1_SS;

///L1.1(PCIe Port6)
///Enable for L1.1
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_L1_1_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_L1_1_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_L1_1_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT6_L1_1;

///L1.2(PCIe Port6)
///Enable for L1.2
typedef enum {
  IDSOPT_DBG_NBIO_PORT6_L1_2_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_PORT6_L1_2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_NBIO_PORT6_L1_2_ENABLED = 1,///<Enabled
} IDSOPT_DBG_NBIO_PORT6_L1_2;

///Dynamic Lanes Power State for Linkwidth Switch(PCIe Port6)
///Dynamic Lanes Power State for Linkwidth Switch
typedef enum {
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_1 = 1,///<1
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_2 = 2,///<2
  IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH_3 = 3,///<3
} IDSOPT_DBG_NBIOS_PORT6_DYN_LANES_LINK_SWITCH;

///LC FOM TIME(PCIe Port6)
///Selects Figure of Merit time required by the PHY
typedef enum {
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_300US = 0,///<300us
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_200US = 1,///<200us
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_100US = 2,///<100us
  IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME_LESSTHAN100US = 3,///<Less than 100us
} IDSOPT_DBG_NBIOS_PORT6_LC_FOM_TIME;

///Port Reversal(PCIe Port6)
///per port reversal enablement
typedef enum {
  IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL_0 = 0,///<0
  IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL_1 = 1,///<1
} IDSOPT_DBG_NBIOS_PORT6_PORT_REVERSAL;

///Downstream Tx Preset(PCIe Port6)
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

///Upstream Tx Preset(PCIe Port6)
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

///Downstream Rx Preset Hint(PCIe Port6)
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

///Upstream Rx Preset Hint(PCIe Port6)
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

///Bypass Gen3 EQ(PCIe Port6)
///Bypass Gen3 EQ
typedef enum {
  IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_BYPASS_GEN3_EQ;

///Enable 3x3 Search(PCIe Port6)
///Enable 3x3 Search
typedef enum {
  IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_ENABLE3X3_SEARCH;

///Enable Safe Search(PCIe Port6)
///Enable Safe Search
typedef enum {
  IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_ENABLE_SAFE_SEARCH;

///SRIS_SRNS(PCIe Port6)
///SRIS_SRNS
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_SRNS_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_SRNS_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_SRNS_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_SRNS;

///SRIS_EN(PCIe Port6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_EN;

///SRIS_AUTODETECT_EN(PCIe Port6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT6_SRIS_AUTODETECT_EN;

///SRIS_LOWER_SKP_SUPPORT(PCIe Port6)
///SRIS_EN
typedef enum {
  IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_PORT8_SRIS_LOWER_SKP_SUPPORT;

///Max_Payload_Size(Port6)
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

///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port6)
///Dynamic Power Down Unused Lanes in Link Width Change (PCIe Port6)
typedef enum {
  IDSOPT_DBG_GNB_PCIE_PORT6_DYNAMIC_POWER_DOWN_UNUSED_LANES_ON = 0,///<On
  IDSOPT_DBG_GNB_PCIE_PORT6_DYNAMIC_POWER_DOWN_UNUSED_LANES_P0S = 1,///<P0s
  IDSOPT_DBG_GNB_PCIE_PORT6_DYNAMIC_POWER_DOWN_UNUSED_LANES_P1 = 2,///<P1
  IDSOPT_DBG_GNB_PCIE_PORT6_DYNAMIC_POWER_DOWN_UNUSED_LANES_P2 = 3,///<P2
  IDSOPT_DBG_GNB_PCIE_PORT6_DYNAMIC_POWER_DOWN_UNUSED_LANES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PCIE_PORT6_DYNAMIC_POWER_DOWN_UNUSED_LANES;

///Initial Offset Calibration Enable(PCIe Port6)
///Defines whether Initial Offset calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT6_INIT_OFFSET_CANCELLATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PORT6_INIT_OFFSET_CANCELLATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT6_INIT_OFFSET_CANCELLATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT6_INIT_OFFSET_CANCELLATION;

///Gen3 DFE Control(PCIe Port6)
///Defines the configuration of the DFE Control
typedef enum {
  IDSOPT_DBG_GNB_PORT6_DFE_CONTROL_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT6_DFE_CONTROL_1TAPDFE = 4,///<1-tap DFE
  IDSOPT_DBG_GNB_PORT6_DFE_CONTROL_1TAPDFEWITHFUTUREBITFILTERING = 5,///<1-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT6_DFE_CONTROL_2TAPDFE = 6,///<2-tap DFE
  IDSOPT_DBG_GNB_PORT6_DFE_CONTROL_2TAPDFEWITHFUTUREBITFILTERING = 7,///<2-tap DFE with Future Bit Filtering
  IDSOPT_DBG_GNB_PORT6_DFE_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT6_DFE_CONTROL;

///LEQ Control(PCIe Port6)
///Defines the configuration of the LEQ Control
typedef enum {
  IDSOPT_DBG_GNB_PORT6_LEQ_CONTROL_DCGAINANDPOLEADAPTATION = 3,///<DC Gain and Pole Adaptation
  IDSOPT_DBG_GNB_PORT6_LEQ_CONTROL_LEQDISABLED = 0,///<LEQ Disabled
  IDSOPT_DBG_GNB_PORT6_LEQ_CONTROL_DCGAINADAPTATION = 2,///<DC Gain Adaptation
  IDSOPT_DBG_GNB_PORT6_LEQ_CONTROL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT6_LEQ_CONTROL;

///Dynamic Offset Calibration(PCIe Port6)
///whether Dynamic Offset Calibration is enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT6_DYNAMIC_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT6_DYNAMIC_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT6_DYNAMIC_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT6_DYNAMIC_OFFSET_CALIBRATION;

///FOM Calculation(PCIe Port6)
///defines whether FOM Calculation will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT6_FOM_CALCULATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT6_FOM_CALCULATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT6_FOM_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT6_FOM_CALCULATION;

///PI Offset Calibration(PCIe Port6)
///defines whether PI Offset Calibration will be enabled or not
typedef enum {
  IDSOPT_DBG_GNB_PORT8_PI_OFFSET_CALIBRATION_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_PORT8_PI_OFFSET_CALIBRATION_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_PORT8_PI_OFFSET_CALIBRATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PORT8_PI_OFFSET_CALIBRATION;

///Flow Control Credits Control(PCIe Port6)
///Flow Control Credits
typedef enum {
  IDSOPT_DBG_GNB_PORT6_FLOW_CONTROL_CREDITS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_PORT6_FLOW_CONTROL_CREDITS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_PORT6_FLOW_CONTROL_CREDITS_CTL;

///NP-HDR(PCIe Port6)
///Non-Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_NPH_CREDITS_MIN 0 ///< Min of NP-HDR(PCIe Port6)
#define IDSOPT_DBG_GNB_PORT6_NPH_CREDITS_MAX 0xff ///< Max of NP-HDR(PCIe Port6)

///NP-DATA(PCIe Port6)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_NPD_CREDITS_MIN 0 ///< Min of NP-DATA(PCIe Port6)
#define IDSOPT_DBG_GNB_PORT6_NPD_CREDITS_MAX 0xff ///< Max of NP-DATA(PCIe Port6)

///P-HDR(PCIe Port6)
///Posted Header Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_PH_CREDITS_MIN 0 ///< Min of P-HDR(PCIe Port6)
#define IDSOPT_DBG_GNB_PORT6_PH_CREDITS_MAX 0xff ///< Max of P-HDR(PCIe Port6)

///P-DATA(PCIe Port6)
///Non-Posted Data Flow Control Advertised Credits
#define IDSOPT_DBG_GNB_PORT6_PD_CREDITS_MIN 0 ///< Min of P-DATA(PCIe Port6)
#define IDSOPT_DBG_GNB_PORT6_PD_CREDITS_MAX 0xff ///< Max of P-DATA(PCIe Port6)

///CPL-HDR(PCIe Port6)
///Completion Header Flow Control Credits
#define IDSOPT_DBG_GNB_PORT6_CPLH_CREDITS_MIN 0 ///< Min of CPL-HDR(PCIe Port6)
#define IDSOPT_DBG_GNB_PORT6_CPLH_CREDITS_MAX 0xff ///< Max of CPL-HDR(PCIe Port6)

///CPL-DATA(PCIe Port6)
///Completion Data Flow Control Credits
#define IDSOPT_DBG_GNB_PORT6_CPLD_CREDITS_MIN 0 ///< Min of CPL-DATA(PCIe Port6)
#define IDSOPT_DBG_GNB_PORT6_CPLD_CREDITS_MAX 0xff ///< Max of CPL-DATA(PCIe Port6)

///Gen1(PCIe Port6)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN1_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN1_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN1_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN1;

///Gen2(PCIe Port6)
///SPC
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN2_1SYM = 0,///<1 sym
  IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN2_2SYM = 1,///<2 sym
  IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PC_IE_PORT6_SPC_GEN2;

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

///Allow Aggressive Power Saving from PCS(GFX)
///Allow Aggressive Power Saving from PCS
typedef enum {
  IDSOPT_DBG_GNB_GFX_POWER_PCS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_POWER_PCS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_POWER_PCS_CTL;

///AllowPS3
///AllowPS3
typedef enum {
  IDSOPT_DBG_GNB_GFX_ALLOW_P_S3_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_ALLOW_P_S3_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_ALLOW_P_S3_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_ALLOW_P_S3;

///DisablePS4
///DisablePS4
typedef enum {
  IDSOPT_DBG_GNB_GFX_DISABLE_P_S4_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_DISABLE_P_S4_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_DISABLE_P_S4_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_DISABLE_P_S4;

///EIDetectorCycleEn(GFX)
///EIDetectorCycleEn
typedef enum {
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_CYCLE_EN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_CYCLE_EN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_CYCLE_EN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_GFX_EI_DETECTOR_CYCLE_EN;

///EIDetectorOnTimeCtrl(GFX)
///Master PLL Selection
typedef enum {
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_ON_TIME_CTRL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_ON_TIME_CTRL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_EI_DETECTOR_ON_TIME_CTRL;

///EIDetectorOnTime
///EIDetectorOnTime
#define IDSOPT_DBG_GNB_GFX_EI_DETECTOR_ON_TIME_MIN 0 ///< Min of EIDetectorOnTime
#define IDSOPT_DBG_GNB_GFX_EI_DETECTOR_ON_TIME_MAX 0xffff ///< Max of EIDetectorOnTime

///EIDetectorOffTimeCtrl(GFX)
///EIDetectorOffTimeCtrl
typedef enum {
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_OFF_TIME_CTRL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GNB_GFX_EI_DETECTOR_OFF_TIME_CTRL_AUTO = 0,///<Auto
} IDSOPT_DBG_GNB_GFX_EI_DETECTOR_OFF_TIME_CTRL;

///EIDetectorOffTime
///EIDetectorOffTime
#define IDSOPT_DBG_GNB_GFX_EI_DETECTOR_OFF_TIME_MIN 0 ///< Min of EIDetectorOffTime
#define IDSOPT_DBG_GNB_GFX_EI_DETECTOR_OFF_TIME_MAX 0xffff ///< Max of EIDetectorOffTime

///Receiver Detection Pooling Control
///Receiver detection pooling time
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_RECEIVER_DETECT_POOLING_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PC_IE_RECEIVER_DETECT_POOLING_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PC_IE_RECEIVER_DETECT_POOLING_CTL;

///Receiver Detection Pooling
///Receiver detection pooling time
#define IDSOPT_DBG_GNB_PC_IE_RECEIVER_DETECT_POOLING_MIN 2 ///< Min of Receiver Detection Pooling
#define IDSOPT_DBG_GNB_PC_IE_RECEIVER_DETECT_POOLING_MAX 255 ///< Max of Receiver Detection Pooling

///Reset To training Delay Control
///Reset To training Delay
typedef enum {
  IDSOPT_DBG_GNB_PC_IE_RESET_TO_TRAINING_DELAY_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_PC_IE_RESET_TO_TRAINING_DELAY_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_GNB_PC_IE_RESET_TO_TRAINING_DELAY_CTL;

///Reset To training Delay
///Reset To training Delay
#define IDSOPT_DBG_GNB_PC_IE_RESET_TO_TRAINING_DELAY_MIN 0 ///< Min of Reset To training Delay
#define IDSOPT_DBG_GNB_PC_IE_RESET_TO_TRAINING_DELAY_MAX 65535 ///< Max of Reset To training Delay

///Breakpoint (Before reconfiguration)
typedef enum {
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT1_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT1_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT1;

///Breakpoint (Before GPP training)
typedef enum {
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT2_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT2_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT2;

///Breakpoint (Before Gen2 init )
typedef enum {
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT3_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT3_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT3;

///Breakpoint (Before Gen3 Init)
typedef enum {
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT4_AUTO = 0,///<Auto
  IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT4_ENABLE = 1,///<Enable
} IDSOPT_DBG_GNB_GEN_HDT_BREAKPOINT4;

///PCIe ARI Support
///Enables Alternative Routing-ID Interpretation
typedef enum {
  IDSOPT_GNB_DBG_PCIE_ARI_SUPPORT_DISABLE = 0,///<Disable
  IDSOPT_GNB_DBG_PCIE_ARI_SUPPORT_ENABLE = 1,///<Enable
  IDSOPT_GNB_DBG_PCIE_ARI_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_GNB_DBG_PCIE_ARI_SUPPORT;

///AER Enable
///Enable or Disable AER
typedef enum {
  IDSOPT_DBG_GNB_DBG_AER_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_DBG_AER_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBG_AER_ENABLE_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_AER_ENABLE;

///LTR Enable
///Enable or Disable LTR
typedef enum {
  IDSOPT_DBG_GNB_DBG_LTR_ENABLE_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_DBG_LTR_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_DBG_LTR_ENABLE_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_DBG_LTR_ENABLE;

///PHY_A0_PCIe Dynamic Control Enable
typedef enum {
  IDSOPT_DBG_PCIE_PHY_A0_DYN_CNTRL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PCIE_PHY_A0_DYN_CNTRL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PCIE_PHY_A0_DYN_CNTRL_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PCIE_PHY_A0_DYN_CNTRL;

///PHY_A1_SATA Dynamic Control Enable
typedef enum {
  IDSOPT_DBG_PCIE_PHY_A1_DYN_CNTRL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PCIE_PHY_A1_DYN_CNTRL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PCIE_PHY_A1_DYN_CNTRL_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PCIE_PHY_A1_DYN_CNTRL;

///PHY_A2_PCIe Dynamic Control Enable
typedef enum {
  IDSOPT_DBG_PCIE_PHY_A2_DYN_CNTRL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PCIE_PHY_A2_DYN_CNTRL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PCIE_PHY_A2_DYN_CNTRL_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PCIE_PHY_A2_DYN_CNTRL;

///PHY_A3_4_PCIe Dynamic Control Enable
typedef enum {
  IDSOPT_DBG_PCIE_PHY_A3_4_DYN_CNTRL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_PCIE_PHY_A3_4_DYN_CNTRL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_PCIE_PHY_A3_4_DYN_CNTRL_AUTO = 0xF,///<Auto
} IDSOPT_DBG_PCIE_PHY_A3_4_DYN_CNTRL;

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

///Low Bandwidth Threshold
///When operating at the Gen1 data rate, a low bandwidth hint is generated when the Link is idle for longer than the percentage selected
typedef enum {
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_0 = 0,///<0%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_5 = 1,///<5%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_10 = 2,///<10%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_15 = 3,///<15%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_20 = 4,///<20%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_25 = 5,///<25%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_30 = 6,///<30%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_40 = 7,///<40%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_50 = 8,///<50%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_60 = 9,///<60%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_70 = 10,///<70%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_75 = 11,///<75%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_80 = 12,///<80%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_90 = 13,///<90%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_95 = 14,///<95%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_100 = 15,///<100%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_AUTO = 16,///<Auto
} IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD;

///High Bandwidth Threshold
///When operating at the Gen1 data rate, a high bandwidth hint is generated when the Link is idle for less than the percentage selected
typedef enum {
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_0 = 0,///<0%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_5 = 1,///<5%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_10 = 2,///<10%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_15 = 3,///<15%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_20 = 4,///<20%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_25 = 5,///<25%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_30 = 6,///<30%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_40 = 7,///<40%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_50 = 8,///<50%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_60 = 9,///<60%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_70 = 10,///<70%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_75 = 11,///<75%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_80 = 12,///<80%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_90 = 13,///<90%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_95 = 14,///<95%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_100 = 15,///<100%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_AUTO = 16,///<Auto
} IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD;

///Gen2 Low Bandwidth Threshold
///When operating at the Gen2 data rate, a low bandwidth hint is generated when the Link is idle for longer than the percentage selected
typedef enum {
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_0 = 0,///<0%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_5 = 1,///<5%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_10 = 2,///<10%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_15 = 3,///<15%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_20 = 4,///<20%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_25 = 5,///<25%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_30 = 6,///<30%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_40 = 7,///<40%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_50 = 8,///<50%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_60 = 9,///<60%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_70 = 10,///<70%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_75 = 11,///<75%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_80 = 12,///<80%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_90 = 13,///<90%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_95 = 14,///<95%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_100 = 15,///<100%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2_AUTO = 16,///<Auto
} IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G2;

///Gen2 High Bandwidth Threshold
///When operating at the Gen2 data rate, a high bandwidth hint is generated when the Link is idle for less than the percentage selected
typedef enum {
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_0 = 0,///<0%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_5 = 1,///<5%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_10 = 2,///<10%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_15 = 3,///<15%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_20 = 4,///<20%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_25 = 5,///<25%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_30 = 6,///<30%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_40 = 7,///<40%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_50 = 8,///<50%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_60 = 9,///<60%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_70 = 10,///<70%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_75 = 11,///<75%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_80 = 12,///<80%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_90 = 13,///<90%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_95 = 14,///<95%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_100 = 15,///<100%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2_AUTO = 16,///<Auto
} IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G2;

///Gen3 Low Bandwidth Threshold
///When operating at the Gen3 data rate, a low bandwidth hint is generated when the Link is idle for longer than the percentage selected
typedef enum {
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_0 = 0,///<0%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_5 = 1,///<5%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_10 = 2,///<10%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_15 = 3,///<15%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_20 = 4,///<20%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_25 = 5,///<25%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_30 = 6,///<30%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_40 = 7,///<40%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_50 = 8,///<50%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_60 = 9,///<60%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_70 = 10,///<70%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_75 = 11,///<75%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_80 = 12,///<80%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_90 = 13,///<90%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_95 = 14,///<95%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_100 = 15,///<100%
  IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3_AUTO = 16,///<Auto
} IDSOPT_DBG_GNB_LOW_BANDWIDTH_THRESHOLD_G3;

///Gen3 High Bandwidth Threshold
///When operating at the Gen3 data rate, a high bandwidth hint is generated when the Link is idle for less than the percentage selected
typedef enum {
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_0 = 0,///<0%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_5 = 1,///<5%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_10 = 2,///<10%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_15 = 3,///<15%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_20 = 4,///<20%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_25 = 5,///<25%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_30 = 6,///<30%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_40 = 7,///<40%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_50 = 8,///<50%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_60 = 9,///<60%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_70 = 10,///<70%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_75 = 11,///<75%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_80 = 12,///<80%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_90 = 13,///<90%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_95 = 14,///<95%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_100 = 15,///<100%
  IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3_AUTO = 16,///<Auto
} IDSOPT_DBG_GNB_HIGH_BANDWIDTH_THRESHOLD_G3;

///Bandwidth Hint Count
///Bandwidth Hint Counter (percent idle mode) - select the sample time over which the idle Link will be tracked
typedef enum {
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_100US = 0,///<100 uS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_400US = 1,///<400 uS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_1MS = 2,///<1 mS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_4MS = 3,///<4 mS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_10MS = 4,///<10 mS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_40MS = 5,///<40 mS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_100MS = 6,///<100 mS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_400MS = 7,///<400 mS
  IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT_AUTO = 15,///<Auto
} IDSOPT_DBG_GNB_BANDWIDTH_HINT_COUNT;

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

///SST clock gating
///SST clock gating
typedef enum {
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_PMM_SST_CLOCK_GATING;

///IOHC Power Gating
///IOHC Power Gating
typedef enum {
  IDSOPT_DBG_GNB_NB_IOHC_POWER_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOHC_POWER_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOHC_POWER_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOHC_POWER_GATING;

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

///IOMMU Dynamic PG
///IOMMU Dynamic PG
typedef enum {
  IDSOPT_DBG_GNB_NB_IOMMU_DYNAMIC_PG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOMMU_DYNAMIC_PG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOMMU_DYNAMIC_PG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOMMU_DYNAMIC_PG;

///IOMMU L2 Memory PG
///IOMMU L2 Memory PG
typedef enum {
  IDSOPT_DBG_GNB_NB_IOMMU_L2_MEMORY_PG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_NB_IOMMU_L2_MEMORY_PG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_NB_IOMMU_L2_MEMORY_PG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_NB_IOMMU_L2_MEMORY_PG;

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

///NBIF PG
///NBIF PG
typedef enum {
  IDSOPT_DBG_NBIO_NBIF_PG_AUTO = 0xf,///<Auto
  IDSOPT_DBG_NBIO_NBIF_PG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_NBIO_NBIF_PG_DISABLED = 0,///<Disabled
} IDSOPT_DBG_NBIO_NBIF_PG;

///NBIF PG Hysteresis
#define IDSOPT_DBG_NBIO_NBIF_PG_HYSTERESIS_MIN 0 ///< Min of NBIF PG Hysteresis
#define IDSOPT_DBG_NBIO_NBIF_PG_HYSTERESIS_MAX 0xff ///< Max of NBIF PG Hysteresis

///IOHC Global CG Control
typedef enum {
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_AUTO = 0xf,///<Auto
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_ENABLED = 1,///<Enabled
  IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL_DISABLED = 0,///<Disabled
} IDSOPT_CBS_NBIO_IOHC_GLOBAL_CG_CTRL;

///  IOHC CG Hysteresis
#define IDSOPT_DBG_NBIO_IOHC_CG_HYSTERESIS_MIN 0 ///< Min of   IOHC CG Hysteresis
#define IDSOPT_DBG_NBIO_IOHC_CG_HYSTERESIS_MAX 0xff ///< Max of   IOHC CG Hysteresis

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

///PHY Power Gating
///Enable/Disable PHY Power Gating
typedef enum {
  IDSOPT_DBG_GNB_PHY_POWER_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_PHY_POWER_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_PHY_POWER_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_PHY_POWER_GATING;

///Shubclk Dpm Control (RV2 only)
///SHUBCLK DPM CONTROL
typedef enum {
  IDSOPT_DBG_GNB_SHUBCLK_DPM_CONTROL_AUTO = 0xf,///<Auto
  IDSOPT_DBG_GNB_SHUBCLK_DPM_CONTROL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SHUBCLK_DPM_CONTROL_DISABLED = 0,///<Disabled
} IDSOPT_DBG_GNB_SHUBCLK_DPM_CONTROL;

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
} IDSOPT_DBG_GNB_NB_P_BR6_DEV_FN_MAP;

///PhyA0 Owner (Lane0-1)
///PhyA0 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A0_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A0_OWNER_SATA = 2,///<SATA
  IDSOPT_DBG_GNB_PHY_A0_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_A0_OWNER;

///PhyA1 Owner (Lane2-3)
///PhyA1 Owner
typedef enum {
  IDSOPT_DBG_GNB_PHY_A1_OWNER_PCIE = 1,///<PCIe
  IDSOPT_DBG_GNB_PHY_A1_OWNER_SATA = 2,///<SATA
  IDSOPT_DBG_GNB_PHY_A1_OWNER_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_PHY_A1_OWNER;

///AB Clock Gating
///Enable or disable AB clock gating
typedef enum {
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_GPP_AB_CLOCK_GATING;

///AB Memory Power Saving
///Enable/disable AB Memory Power Saving
typedef enum {
  IDSOPT_DBG_FCH_SYSTEM_AB_MEMORY_POWER_SAVING_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SYSTEM_AB_MEMORY_POWER_SAVING_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SYSTEM_AB_MEMORY_POWER_SAVING_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SYSTEM_AB_MEMORY_POWER_SAVING;

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
  IDSOPT_SDPHOST_BYPASS_DATA_PACK_ENABLE = 0,///<Enable
  IDSOPT_SDPHOST_BYPASS_DATA_PACK_DISABLE = 1,///<Disable
} IDSOPT_SDPHOST_BYPASS_DATA_PACK;

///SDPHOST_DIS_NPMWR_PROTECT
typedef enum {
  IDSOPT_SDPHOST_DIS_NPMWR_PROTECT_ENABLE = 0,///<Enable
  IDSOPT_SDPHOST_DIS_NPMWR_PROTECT_DISABLE = 1,///<Disable
} IDSOPT_SDPHOST_DIS_NPMWR_PROTECT;

///SATA Set MaxGen2 Capability
///Select whether or not Enable SATA MaxGen2 Capability
typedef enum {
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SET_MAX_GEN2;

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

///SATA SGPIO
///Eable SGPIO feature
typedef enum {
  IDSOPT_DBG_FCH_SATA_SGPIO0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_SATA_SGPIO0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_SATA_SGPIO0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_SATA_SGPIO0;

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

///eSATA Port0
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT0_AUTO = 0xF,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT0;

///eSATA Port1
typedef enum {
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_ISATA = 0,///<iSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_ESATA = 1,///<eSATA
  IDSOPT_DBG_FCH_SATAE_SATA_PORT1_AUTO = 0xF,///<Auto
} IDSOPT_DBG_FCH_SATAE_SATA_PORT1;

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
  IDSOPT_DBG_FCH_SYSTEM_WDT_ENABLE_AUTO = 2,///<Auto
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

///USB DBGCLK Enable
typedef enum {
  IDSOPT_DBG_USBDBGCLK_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_USBDBGCLK_ENABLE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_USBDBGCLK_ENABLE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_USBDBGCLK_ENABLE;

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

///Adma2 Support
typedef enum {
  IDSOPT_DBG_FCH_EMMC_ADMA2_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_ADMA2_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_EMMC_ADMA2_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_ADMA2_SUPPORT;

///Adma Support
typedef enum {
  IDSOPT_DBG_FCH_EMMC_ADMA_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_ADMA_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_EMMC_ADMA_SUPPORT_AUTO = 2,///<Auto
} IDSOPT_DBG_FCH_EMMC_ADMA_SUPPORT;

///Sdma Support
typedef enum {
  IDSOPT_DBG_FCH_EMMC_SDMA_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_SDMA_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_EMMC_SDMA_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_SDMA_SUPPORT;

///A64B Support
typedef enum {
  IDSOPT_DBG_FCH_EMMC_A64B_SUPPORT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_FCH_EMMC_A64B_SUPPORT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_FCH_EMMC_A64B_SUPPORT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_FCH_EMMC_A64B_SUPPORT;

///Device Removable
///Device Removable. bit[3:0] Controler0 port0-3, bit[5:4]\n          Controller1 Port0/1.
#define IDSOPT_FCH_DEBUG_USB_DEVICE_REMOVABLE_MIN 0 ///< Min of Device Removable
#define IDSOPT_FCH_DEBUG_USB_DEVICE_REMOVABLE_MAX 0x3F ///< Max of Device Removable

///Port Force Gen1
///Force Usb3 port force gen1. bit[3:0] Controler0 port0-3.\n
#define IDSOPT_FCH_DEBUG_USB_PORT_FORCE_GEN1_MIN 0 ///< Min of Port Force Gen1
#define IDSOPT_FCH_DEBUG_USB_PORT_FORCE_GEN1_MAX 0x0F ///< Max of Port Force Gen1

///U3 RxDet WA
///Enable U3 RxDet WA on selected Port
typedef enum {
  IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE_CONTROLLER0PORT0 = 0x1,///<Controller0 Port0
  IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE_CONTROLLER0PORT1 = 0x2,///<Controller0 Port1
  IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE_CONTROLLER0PORT2 = 0x4,///<Controller0 Port2
  IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE_CONTROLLER0PORT3 = 0x8,///<Controller0 Port3
  IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE_CONTROLLER1PORT0 = 0x10,///<Controller1 Port0
} IDSOPT_FCH_DEBUG_USB_U3_RX_DET_WA_ENABLE;

///Early Debug Select Enable
///Enable Early Debug Select.\n
typedef enum {
  IDSOPT_FCH_DEBUG_USB_EARLY_DEBUG_SELECT_ENABLE_DISABLED = 0,///<Disabled
  IDSOPT_FCH_DEBUG_USB_EARLY_DEBUG_SELECT_ENABLE_ENABLED = 1,///<Enabled
} IDSOPT_FCH_DEBUG_USB_EARLY_DEBUG_SELECT_ENABLE;

///TXVREFTUNE
///HS DC Voltage Level Adjustment
#define IDSOPT_C0_P0_TXVREFTUNE_MIN 0 ///< Min of TXVREFTUNE
#define IDSOPT_C0_P0_TXVREFTUNE_MAX 0xf ///< Max of TXVREFTUNE

///TXPREEMPAMPTUNE
///HS Transmitter Pre-Emphasis Current Control
#define IDSOPT_C0_P0_TXPREEMPAMPTUNE_MIN 0 ///< Min of TXPREEMPAMPTUNE
#define IDSOPT_C0_P0_TXPREEMPAMPTUNE_MAX 0x3 ///< Max of TXPREEMPAMPTUNE

///COMPDSTUNE
///Disconnect Threshold Adjustment
#define IDSOPT_C0_P0_COMPDSTUNE_MIN 0 ///< Min of COMPDSTUNE
#define IDSOPT_C0_P0_COMPDSTUNE_MAX 0x7 ///< Max of COMPDSTUNE

///SQRXTUNE
///Squelch Threshold Adjustment
#define IDSOPT_C0_P0_SQRXTUNE_MIN 0 ///< Min of SQRXTUNE
#define IDSOPT_C0_P0_SQRXTUNE_MAX 0x7 ///< Max of SQRXTUNE

///TXFSLSTUNE
///FS/LS Source Impedance Adjustment
#define IDSOPT_C0_P0_TXFSLSTUNE_MIN 0 ///< Min of TXFSLSTUNE
#define IDSOPT_C0_P0_TXFSLSTUNE_MAX 0xf ///< Max of TXFSLSTUNE

///TXPREEMPPULSETUNE
///HS Transmitter Pre-Emphasis Duration Control
#define IDSOPT_C0_P0_TXPREEMPPULSETUNE_MIN 0 ///< Min of TXPREEMPPULSETUNE
#define IDSOPT_C0_P0_TXPREEMPPULSETUNE_MAX 0x1 ///< Max of TXPREEMPPULSETUNE

///TXRISETUNE
///HS Transmitter Rise/Fall Time Adjustment
#define IDSOPT_C0_P0_TXRISETUNE_MIN 0 ///< Min of TXRISETUNE
#define IDSOPT_C0_P0_TXRISETUNE_MAX 0x3 ///< Max of TXRISETUNE

///TXHSXVTUNE
///Transmitter High-Speed Crossover Adjustment
#define IDSOPT_C0_P0_TXHSXVTUNE_MIN 0 ///< Min of TXHSXVTUNE
#define IDSOPT_C0_P0_TXHSXVTUNE_MAX 0x3 ///< Max of TXHSXVTUNE

///TXRESTUNE
///USB Source Impedance Adjustment
#define IDSOPT_C0_P0_TXRESTUNE_MIN 0 ///< Min of TXRESTUNE
#define IDSOPT_C0_P0_TXRESTUNE_MAX 0x3 ///< Max of TXRESTUNE

///TXVREFTUNE
///HS DC Voltage Level Adjustment
#define IDSOPT_C0_P1_TXVREFTUNE_MIN 0 ///< Min of TXVREFTUNE
#define IDSOPT_C0_P1_TXVREFTUNE_MAX 0xf ///< Max of TXVREFTUNE

///TXPREEMPAMPTUNE
///HS Transmitter Pre-Emphasis Current Control
#define IDSOPT_C0_P1_TXPREEMPAMPTUNE_MIN 0 ///< Min of TXPREEMPAMPTUNE
#define IDSOPT_C0_P1_TXPREEMPAMPTUNE_MAX 0x3 ///< Max of TXPREEMPAMPTUNE

///COMPDSTUNE
///Disconnect Threshold Adjustment
#define IDSOPT_C0_P1_COMPDSTUNE_MIN 0 ///< Min of COMPDSTUNE
#define IDSOPT_C0_P1_COMPDSTUNE_MAX 0x7 ///< Max of COMPDSTUNE

///SQRXTUNE
///Squelch Threshold Adjustment
#define IDSOPT_C0_P1_SQRXTUNE_MIN 0 ///< Min of SQRXTUNE
#define IDSOPT_C0_P1_SQRXTUNE_MAX 0x7 ///< Max of SQRXTUNE

///TXFSLSTUNE
///FS/LS Source Impedance Adjustment
#define IDSOPT_C0_P1_TXFSLSTUNE_MIN 0 ///< Min of TXFSLSTUNE
#define IDSOPT_C0_P1_TXFSLSTUNE_MAX 0xf ///< Max of TXFSLSTUNE

///TXPREEMPPULSETUNE
///HS Transmitter Pre-Emphasis Duration Control
#define IDSOPT_C0_P1_TXPREEMPPULSETUNE_MIN 0 ///< Min of TXPREEMPPULSETUNE
#define IDSOPT_C0_P1_TXPREEMPPULSETUNE_MAX 0x1 ///< Max of TXPREEMPPULSETUNE

///TXRISETUNE
///HS Transmitter Rise/Fall Time Adjustment
#define IDSOPT_C0_P1_TXRISETUNE_MIN 0 ///< Min of TXRISETUNE
#define IDSOPT_C0_P1_TXRISETUNE_MAX 0x3 ///< Max of TXRISETUNE

///TXHSXVTUNE
///Transmitter High-Speed Crossover Adjustment
#define IDSOPT_C0_P1_TXHSXVTUNE_MIN 0 ///< Min of TXHSXVTUNE
#define IDSOPT_C0_P1_TXHSXVTUNE_MAX 0x3 ///< Max of TXHSXVTUNE

///TXRESTUNE
///USB Source Impedance Adjustment
#define IDSOPT_C0_P1_TXRESTUNE_MIN 0 ///< Min of TXRESTUNE
#define IDSOPT_C0_P1_TXRESTUNE_MAX 0x3 ///< Max of TXRESTUNE

///TXVREFTUNE
///HS DC Voltage Level Adjustment
#define IDSOPT_C0_P2_TXVREFTUNE_MIN 0 ///< Min of TXVREFTUNE
#define IDSOPT_C0_P2_TXVREFTUNE_MAX 0xf ///< Max of TXVREFTUNE

///TXPREEMPAMPTUNE
///HS Transmitter Pre-Emphasis Current Control
#define IDSOPT_C0_P2_TXPREEMPAMPTUNE_MIN 0 ///< Min of TXPREEMPAMPTUNE
#define IDSOPT_C0_P2_TXPREEMPAMPTUNE_MAX 0x3 ///< Max of TXPREEMPAMPTUNE

///COMPDSTUNE
///Disconnect Threshold Adjustment
#define IDSOPT_C0_P2_COMPDSTUNE_MIN 0 ///< Min of COMPDSTUNE
#define IDSOPT_C0_P2_COMPDSTUNE_MAX 0x7 ///< Max of COMPDSTUNE

///SQRXTUNE
///Squelch Threshold Adjustment
#define IDSOPT_C0_P2_SQRXTUNE_MIN 0 ///< Min of SQRXTUNE
#define IDSOPT_C0_P2_SQRXTUNE_MAX 0x7 ///< Max of SQRXTUNE

///TXFSLSTUNE
///FS/LS Source Impedance Adjustment
#define IDSOPT_C0_P2_TXFSLSTUNE_MIN 0 ///< Min of TXFSLSTUNE
#define IDSOPT_C0_P2_TXFSLSTUNE_MAX 0xf ///< Max of TXFSLSTUNE

///TXPREEMPPULSETUNE
///HS Transmitter Pre-Emphasis Duration Control
#define IDSOPT_C0_P2_TXPREEMPPULSETUNE_MIN 0 ///< Min of TXPREEMPPULSETUNE
#define IDSOPT_C0_P2_TXPREEMPPULSETUNE_MAX 0x1 ///< Max of TXPREEMPPULSETUNE

///TXRISETUNE
///HS Transmitter Rise/Fall Time Adjustment
#define IDSOPT_C0_P2_TXRISETUNE_MIN 0 ///< Min of TXRISETUNE
#define IDSOPT_C0_P2_TXRISETUNE_MAX 0x3 ///< Max of TXRISETUNE

///TXHSXVTUNE
///Transmitter High-Speed Crossover Adjustment
#define IDSOPT_C0_P2_TXHSXVTUNE_MIN 0 ///< Min of TXHSXVTUNE
#define IDSOPT_C0_P2_TXHSXVTUNE_MAX 0x3 ///< Max of TXHSXVTUNE

///TXRESTUNE
///USB Source Impedance Adjustment
#define IDSOPT_C0_P2_TXRESTUNE_MIN 0 ///< Min of TXRESTUNE
#define IDSOPT_C0_P2_TXRESTUNE_MAX 0x3 ///< Max of TXRESTUNE

///TXVREFTUNE
///HS DC Voltage Level Adjustment
#define IDSOPT_C0_P3_TXVREFTUNE_MIN 0 ///< Min of TXVREFTUNE
#define IDSOPT_C0_P3_TXVREFTUNE_MAX 0xf ///< Max of TXVREFTUNE

///TXPREEMPAMPTUNE
///HS Transmitter Pre-Emphasis Current Control
#define IDSOPT_C0_P3_TXPREEMPAMPTUNE_MIN 0 ///< Min of TXPREEMPAMPTUNE
#define IDSOPT_C0_P3_TXPREEMPAMPTUNE_MAX 0x3 ///< Max of TXPREEMPAMPTUNE

///COMPDSTUNE
///Disconnect Threshold Adjustment
#define IDSOPT_C0_P3_COMPDSTUNE_MIN 0 ///< Min of COMPDSTUNE
#define IDSOPT_C0_P3_COMPDSTUNE_MAX 0x7 ///< Max of COMPDSTUNE

///SQRXTUNE
///Squelch Threshold Adjustment
#define IDSOPT_C0_P3_SQRXTUNE_MIN 0 ///< Min of SQRXTUNE
#define IDSOPT_C0_P3_SQRXTUNE_MAX 0x7 ///< Max of SQRXTUNE

///TXFSLSTUNE
///FS/LS Source Impedance Adjustment
#define IDSOPT_C0_P3_TXFSLSTUNE_MIN 0 ///< Min of TXFSLSTUNE
#define IDSOPT_C0_P3_TXFSLSTUNE_MAX 0xf ///< Max of TXFSLSTUNE

///TXPREEMPPULSETUNE
///HS Transmitter Pre-Emphasis Duration Control
#define IDSOPT_C0_P3_TXPREEMPPULSETUNE_MIN 0 ///< Min of TXPREEMPPULSETUNE
#define IDSOPT_C0_P3_TXPREEMPPULSETUNE_MAX 0x1 ///< Max of TXPREEMPPULSETUNE

///TXRISETUNE
///HS Transmitter Rise/Fall Time Adjustment
#define IDSOPT_C0_P3_TXRISETUNE_MIN 0 ///< Min of TXRISETUNE
#define IDSOPT_C0_P3_TXRISETUNE_MAX 0x3 ///< Max of TXRISETUNE

///TXHSXVTUNE
///Transmitter High-Speed Crossover Adjustment
#define IDSOPT_C0_P3_TXHSXVTUNE_MIN 0 ///< Min of TXHSXVTUNE
#define IDSOPT_C0_P3_TXHSXVTUNE_MAX 0x3 ///< Max of TXHSXVTUNE

///TXRESTUNE
///USB Source Impedance Adjustment
#define IDSOPT_C0_P3_TXRESTUNE_MIN 0 ///< Min of TXRESTUNE
#define IDSOPT_C0_P3_TXRESTUNE_MAX 0x3 ///< Max of TXRESTUNE

///TXVREFTUNE
///HS DC Voltage Level Adjustment
#define IDSOPT_C1_P0_TXVREFTUNE_MIN 0 ///< Min of TXVREFTUNE
#define IDSOPT_C1_P0_TXVREFTUNE_MAX 0xf ///< Max of TXVREFTUNE

///TXPREEMPAMPTUNE
///HS Transmitter Pre-Emphasis Current Control
#define IDSOPT_C1_P0_TXPREEMPAMPTUNE_MIN 0 ///< Min of TXPREEMPAMPTUNE
#define IDSOPT_C1_P0_TXPREEMPAMPTUNE_MAX 0x3 ///< Max of TXPREEMPAMPTUNE

///COMPDSTUNE
///Disconnect Threshold Adjustment
#define IDSOPT_C1_P0_COMPDSTUNE_MIN 0 ///< Min of COMPDSTUNE
#define IDSOPT_C1_P0_COMPDSTUNE_MAX 0x7 ///< Max of COMPDSTUNE

///SQRXTUNE
///Squelch Threshold Adjustment
#define IDSOPT_C1_P0_SQRXTUNE_MIN 0 ///< Min of SQRXTUNE
#define IDSOPT_C1_P0_SQRXTUNE_MAX 0x7 ///< Max of SQRXTUNE

///TXFSLSTUNE
///FS/LS Source Impedance Adjustment
#define IDSOPT_C1_P0_TXFSLSTUNE_MIN 0 ///< Min of TXFSLSTUNE
#define IDSOPT_C1_P0_TXFSLSTUNE_MAX 0xf ///< Max of TXFSLSTUNE

///TXPREEMPPULSETUNE
///HS Transmitter Pre-Emphasis Duration Control
#define IDSOPT_C1_P0_TXPREEMPPULSETUNE_MIN 0 ///< Min of TXPREEMPPULSETUNE
#define IDSOPT_C1_P0_TXPREEMPPULSETUNE_MAX 0x1 ///< Max of TXPREEMPPULSETUNE

///TXRISETUNE
///HS Transmitter Rise/Fall Time Adjustment
#define IDSOPT_C1_P0_TXRISETUNE_MIN 0 ///< Min of TXRISETUNE
#define IDSOPT_C1_P0_TXRISETUNE_MAX 0x3 ///< Max of TXRISETUNE

///TXHSXVTUNE
///Transmitter High-Speed Crossover Adjustment
#define IDSOPT_C1_P0_TXHSXVTUNE_MIN 0 ///< Min of TXHSXVTUNE
#define IDSOPT_C1_P0_TXHSXVTUNE_MAX 0x3 ///< Max of TXHSXVTUNE

///TXRESTUNE
///USB Source Impedance Adjustment
#define IDSOPT_C1_P0_TXRESTUNE_MIN 0 ///< Min of TXRESTUNE
#define IDSOPT_C1_P0_TXRESTUNE_MAX 0x3 ///< Max of TXRESTUNE

///TXVREFTUNE
///HS DC Voltage Level Adjustment
#define IDSOPT_C1_P1_TXVREFTUNE_MIN 0 ///< Min of TXVREFTUNE
#define IDSOPT_C1_P1_TXVREFTUNE_MAX 0xf ///< Max of TXVREFTUNE

///TXPREEMPAMPTUNE
///HS Transmitter Pre-Emphasis Current Control
#define IDSOPT_C1_P1_TXPREEMPAMPTUNE_MIN 0 ///< Min of TXPREEMPAMPTUNE
#define IDSOPT_C1_P1_TXPREEMPAMPTUNE_MAX 0x3 ///< Max of TXPREEMPAMPTUNE

///COMPDSTUNE
///Disconnect Threshold Adjustment
#define IDSOPT_C1_P1_COMPDSTUNE_MIN 0 ///< Min of COMPDSTUNE
#define IDSOPT_C1_P1_COMPDSTUNE_MAX 0x7 ///< Max of COMPDSTUNE

///SQRXTUNE
///Squelch Threshold Adjustment
#define IDSOPT_C1_P1_SQRXTUNE_MIN 0 ///< Min of SQRXTUNE
#define IDSOPT_C1_P1_SQRXTUNE_MAX 0x7 ///< Max of SQRXTUNE

///TXFSLSTUNE
///FS/LS Source Impedance Adjustment
#define IDSOPT_C1_P1_TXFSLSTUNE_MIN 0 ///< Min of TXFSLSTUNE
#define IDSOPT_C1_P1_TXFSLSTUNE_MAX 0xf ///< Max of TXFSLSTUNE

///TXPREEMPPULSETUNE
///HS Transmitter Pre-Emphasis Duration Control
#define IDSOPT_C1_P1_TXPREEMPPULSETUNE_MIN 0 ///< Min of TXPREEMPPULSETUNE
#define IDSOPT_C1_P1_TXPREEMPPULSETUNE_MAX 0x1 ///< Max of TXPREEMPPULSETUNE

///TXRISETUNE
///HS Transmitter Rise/Fall Time Adjustment
#define IDSOPT_C1_P1_TXRISETUNE_MIN 0 ///< Min of TXRISETUNE
#define IDSOPT_C1_P1_TXRISETUNE_MAX 0x3 ///< Max of TXRISETUNE

///TXHSXVTUNE
///Transmitter High-Speed Crossover Adjustment
#define IDSOPT_C1_P1_TXHSXVTUNE_MIN 0 ///< Min of TXHSXVTUNE
#define IDSOPT_C1_P1_TXHSXVTUNE_MAX 0x3 ///< Max of TXHSXVTUNE

///TXRESTUNE
///USB Source Impedance Adjustment
#define IDSOPT_C1_P1_TXRESTUNE_MIN 0 ///< Min of TXRESTUNE
#define IDSOPT_C1_P1_TXRESTUNE_MAX 0x3 ///< Max of TXRESTUNE

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

///FCLK:UCLK mode
///select FCLK:UCLK mode(1 = UCLKDiv1Mode; 0 = not UCLKDiv1Mode)
typedef enum {
  IDSOPT_DBG_CBS_SMU_FCLKUCLK_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_CBS_SMU_FCLKUCLK_MODE_0 = 0,///<0
  IDSOPT_DBG_CBS_SMU_FCLKUCLK_MODE_1 = 1,///<1
} IDSOPT_DBG_CBS_SMU_FCLKUCLK_MODE;

///Vdd Off Vid Control
///Auto = Use the default Vdd Off Vid\nManual = User can set customized Vdd Off Vid
typedef enum {
  IDSOPT_DBG_VDD_OFF_VID_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_VDD_OFF_VID_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_VDD_OFF_VID_CTL;

///Vdd Off Vid
///Vdd Off Vid [mV] = 0 to 1550 mV
#define IDSOPT_DBG_VDD_OFF_VID_MIN 0 ///< Min of Vdd Off Vid
#define IDSOPT_DBG_VDD_OFF_VID_MAX 0x60E ///< Max of Vdd Off Vid

///Ulv Vid Offset Control
///Auto = Use the default Ulv Vid Offset\nManual = User can set customized Ulv Vid Offset
typedef enum {
  IDSOPT_DBG_ULV_VID_OFFSET_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_ULV_VID_OFFSET_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_ULV_VID_OFFSET_CTL;

///Ulv Vid Offset
///Ulv Vid Offset = 0 to 15 decimal
#define IDSOPT_DBG_ULV_VID_OFFSET_MIN 0 ///< Min of Ulv Vid Offset
#define IDSOPT_DBG_ULV_VID_OFFSET_MAX 0xf ///< Max of Ulv Vid Offset

///Vmin Frequency Control
///Auto = Use the default value\nManual = User can set customized Vmin Frequency in MHz
typedef enum {
  IDSOPT_DBG_NBIO_VMIN_FREQ_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_VMIN_FREQ_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_VMIN_FREQ_CTL;

///Vmin Frequency
///Vmin Frequency in MHz
#define IDSOPT_DBG_NBIO_VMIN_FREQ_MIN 0 ///< Min of Vmin Frequency
#define IDSOPT_DBG_NBIO_VMIN_FREQ_MAX 0xffffffff ///< Max of Vmin Frequency

///Min S0i3 Sleep TimeMs Control
///Auto = 5000
typedef enum {
  IDSOPT_DBG_NBIO_MIN_S0I3_SLEEP_TIME_MS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_NBIO_MIN_S0I3_SLEEP_TIME_MS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_NBIO_MIN_S0I3_SLEEP_TIME_MS_CTL;

///Min S0i3 Sleep TimeMs
///Min S0i3 Sleep Time Ms
#define IDSOPT_DBG_NBIO_MIN_S0I3_SLEEP_TIME_MS_MIN 0 ///< Min of Min S0i3 Sleep TimeMs
#define IDSOPT_DBG_NBIO_MIN_S0I3_SLEEP_TIME_MS_MAX 0xffffffff ///< Max of Min S0i3 Sleep TimeMs

///FMax Frequency Control
///Auto = Use the default value\nManual = User can set customized FMax Frequency in MHz
typedef enum {
  IDSOPT_DBG_FMAX_FREQ_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_FMAX_FREQ_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_FMAX_FREQ_CTL;

///FMax Frequency
///FMax Frequency in MHz
#define IDSOPT_DBG_F_MAX_FREQ_MIN 0 ///< Min of FMax Frequency
#define IDSOPT_DBG_F_MAX_FREQ_MAX 0xffffffff ///< Max of FMax Frequency

///EnableSMUPostCode
///Enable SMU Post Code (1 = Enable; 0 = Disable)
typedef enum {
  IDSOPT_DBG_CBS_SMU_ENABLE_SMU_POST_CODE_MODE_AUTO = 0xf,///<Auto
  IDSOPT_DBG_CBS_SMU_ENABLE_SMU_POST_CODE_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_CBS_SMU_ENABLE_SMU_POST_CODE_MODE_ENABLED = 1,///<Enabled
} IDSOPT_DBG_CBS_SMU_ENABLE_SMU_POST_CODE_MODE;

///CCLK_CONTROLLER
///FEATURE_CCLK_CONTROLLER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUCCLK_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUCCLK_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUCCLK_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUCCLK_CONTROLLER;

///FAN_CONTROLLER
///FEATURE_FAN_CONTROLLER_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUFAN_CONTROLLER_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUFAN_CONTROLLER_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUFAN_CONTROLLER_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUFAN_CONTROLLER;

///DATA_CALCULATION
///FEATURE_DATA_CALCULATION_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDATA_CALCULATION_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDATA_CALCULATION_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDATA_CALCULATION_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDATA_CALCULATION;

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

///THERMAL
///FEATURE_THERMAL_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUTHERMAL_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUTHERMAL_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUTHERMAL_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUTHERMAL;

///FIT
///FEATURE_FIT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUFIT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUFIT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUFIT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUFIT;

///EDC
///FEATURE_EDC_BIT
typedef enum {
  IDSOPT_DBG_GNB_SMU_EDC_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_EDC_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_EDC_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_EDC;

///PLL_POWER_DOWN
///FEATURE_PLL_POWER_DOWN_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPLL_POWER_DOWN_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPLL_POWER_DOWN_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPLL_POWER_DOWN_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPLL_POWER_DOWN;

///ULV
///FEATURE_ULV_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUULV_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUULV_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUULV_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUULV;

///VDDOFF
///FEATURE_VDDOFF_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUVDDOFF_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUVDDOFF_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUVDDOFF_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUVDDOFF;

///VCN_DPM
///FEATURE_VCN_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUVCN_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUVCN_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUVCN_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUVCN_DPM;

///ACP_DPM
///FEATURE_ACP_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUACP_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUACP_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUACP_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUACP_DPM;

///ISP_DPM
///FEATURE_ISP_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUISP_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUISP_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUISP_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUISP_DPM;

///FCLK_DPM
///FEATURE_FCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUFCLK_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUFCLK_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUFCLK_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUFCLK_DPM;

///SOCCLK_DPM
///FEATURE_SOCCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUSOCCLK_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUSOCCLK_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUSOCCLK_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUSOCCLK_DPM;

///MP0CLK_DPM
///FEATURE_MP0CLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUM_P0_CLK_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUM_P0_CLK_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUM_P0_CLK_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUM_P0_CLK_DPM;

///LCLK_DPM
///FEATURE_LCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMULCLK_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMULCLK_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMULCLK_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMULCLK_DPM;

///SHUBCLK_DPM
///FEATURE_SHUBCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUSHUBCLK_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUSHUBCLK_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUSHUBCLK_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUSHUBCLK_DPM;

///DCEFCLK_DPM
///FEATURE_DCEFCLK_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDCEFCLK_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDCEFCLK_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDCEFCLK_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDCEFCLK_DPM;

///GFX_DPM
///FEATURE_GFX_DPM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUGFX_DPM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUGFX_DPM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUGFX_DPM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUGFX_DPM;

///DS_GFXCLK
///FEATURE_DS_GFXCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_GFXCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_GFXCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_GFXCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_GFXCLK;

///DS_SOCCLK
///FEATURE_DS_SOCCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_SOCCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_SOCCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_SOCCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_SOCCLK;

///DS_LCLK
///FEATURE_DS_LCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_LCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_LCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_LCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_LCLK;

///DS_DCEFCLK
///FEATURE_DS_DCEFCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_DCEFCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_DCEFCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_DCEFCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_DCEFCLK;

///DS_SHUBCLK
///FEATURE_DS_SHUBCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_SHUBCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_SHUBCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_SHUBCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_SHUBCLK;

///RM
///FEATURE_RM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMURM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMURM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMURM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMURM;

///S0i2
///FEATURE_S0i2_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMU_S0I2_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMU_S0I2_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMU_S0I2_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMU_S0I2;

///WHISPER_MODE
///FEATURE_WHISPER_MODE_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUWHISPER_MODE_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUWHISPER_MODE_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUWHISPER_MODE_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUWHISPER_MODE;

///DS_FCLK
///FEATURE_DS_FCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_FCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_FCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_FCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_FCLK;

///DS_SMNCLK
///FEATURE_DS_SMNCLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_SMNCLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_SMNCLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_SMNCLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_SMNCLK;

///DS_MP1CLK
///FEATURE_DS_MP1CLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_M_P1_CLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_M_P1_CLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_M_P1_CLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_M_P1_CLK;

///DS_MP0CLK
///FEATURE_DS_MP0CLK_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_M_P0_CLK_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_M_P0_CLK_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_M_P0_CLK_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_M_P0_CLK;

///SMU CG
///Smu Clk Gating
typedef enum {
  IDSOPT_DBG_GNB_SMUMGCG_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUMGCG_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUMGCG_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUMGCG;

///FUSE_PG
///FEATURE_DS_FUSE_SRAM_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUDS_FUSE_SRAM_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUDS_FUSE_SRAM_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUDS_FUSE_SRAM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUDS_FUSE_SRAM;

///GFX_CKS
///FEATURE_GFX_CKS_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUGFX_CKS_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUGFX_CKS_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUGFX_CKS_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUGFX_CKS;

///PSI0
///FEATURE_PSI0_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPS_I0_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPS_I0_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPS_I0_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPS_I0;

///PROCHOT
///FEATURE_PROCHOT_MASK
typedef enum {
  IDSOPT_DBG_GNB_SMUPROCHOT_DISABLED = 0,///<Disabled
  IDSOPT_DBG_GNB_SMUPROCHOT_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUPROCHOT_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GNB_SMUPROCHOT;

///CPUOFF
///FEATURE_CPUOFF_BIT
typedef enum {
  IDSOPT_DBG_GNB_SMUCPUOFF_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_SMUCPUOFF_ENABLED = 1,///<Enabled
  IDSOPT_DBG_GNB_SMUCPUOFF_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMUCPUOFF;

///STAPM
///FEATURE_STAPM_BIT
typedef enum {
  IDSOPT_DBG_GNB_SMUSTAPM_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_SMUSTAPM_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_SMUSTAPM_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMUSTAPM;

///CORE_CSTATES
///FEATURE_CORE_CSTATES_BIT
typedef enum {
  IDSOPT_DBG_GNB_SMU_CORE_C_STATES_DISABLE = 0,///<Disable
  IDSOPT_DBG_GNB_SMU_CORE_C_STATES_ENABLE = 1,///<Enable
  IDSOPT_DBG_GNB_SMU_CORE_C_STATES_AUTO = 0xF,///<Auto
} IDSOPT_DBG_GNB_SMU_CORE_C_STATES;

///TDP Control
///Auto = Use the default sustained power limit\nManual = User can set customized sustained power limit
typedef enum {
  IDSOPT_DBG_TDP_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_TDP_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_TDP_CTL;

///TDP
///Sustained power limit [mW]
#define IDSOPT_DBG_TDP_MIN 0 ///< Min of TDP
#define IDSOPT_DBG_TDP_MAX 0xffffffff ///< Max of TDP

///PPT Control
///Auto = Use the default PPT Limits\nManual = User can set customized PPT Limits
typedef enum {
  IDSOPT_DBG_PPT_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_PPT_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_PPT_CTL;

///Fast PPT Limit
///Fast PPT Limit [mW]
#define IDSOPT_DBG_FAST_PPT_LIMIT_MIN 0 ///< Min of Fast PPT Limit
#define IDSOPT_DBG_FAST_PPT_LIMIT_MAX 0xffffffff ///< Max of Fast PPT Limit

///Slow PPT Limit
///Slow PPT Limit [mW]
#define IDSOPT_DBG_SLOW_PPT_LIMIT_MIN 0 ///< Min of Slow PPT Limit
#define IDSOPT_DBG_SLOW_PPT_LIMIT_MAX 0xffffffff ///< Max of Slow PPT Limit

///Slow PPT time constant(seconds)
///Slow PPT Time Constant [seconds]
#define IDSOPT_DBG_SLOW_PPT_TIME_CONSTANT_MIN 0 ///< Min of Slow PPT time constant(seconds)
#define IDSOPT_DBG_SLOW_PPT_TIME_CONSTANT_MAX 0xffffffff ///< Max of Slow PPT time constant(seconds)

///STAPM Control
typedef enum {
  IDSOPT_DBG_STAPM_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_STAPM_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_STAPM_CTL;

///STAPM Boost
///STAPM Boost Enable [1 = boost disabled; 2 = boost enabled]
typedef enum {
  IDSOPT_DBG_STAPM_BOOST_AUTO = 0xF,///<Auto
  IDSOPT_DBG_STAPM_BOOST_DISABLE = 0,///<Disable
  IDSOPT_DBG_STAPM_BOOST_ENABLE = 1,///<Enable
} IDSOPT_DBG_STAPM_BOOST;

///Tskin Time Constant
///Tskin time constant [seconds]
#define IDSOPT_DBG_TSKIN_TIME_CONSTANT_MIN 0 ///< Min of Tskin Time Constant
#define IDSOPT_DBG_TSKIN_TIME_CONSTANT_MAX 0xffffffff ///< Max of Tskin Time Constant

///TDC Control
///Auto = Use the fused VDDCR_CPU TDC limit\nManual = User can set customized VDDCR_CPU TDC limit
typedef enum {
  IDSOPT_DBG_TDC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_TDC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_TDC_CTL;

///TDC_VDDCR_VDD
///VDDCR_CPU TDC Limit [mA]
#define IDSOPT_DBG_TDCVDD_LIMIT_MIN 0 ///< Min of TDC_VDDCR_VDD
#define IDSOPT_DBG_TDCVDD_LIMIT_MAX 0xffffffff ///< Max of TDC_VDDCR_VDD

///TDC_VDDCR_SOC
///VDDCR_SOC TDC Limit [mA]
#define IDSOPT_DBG_TDCSOC_LIMIT_MIN 0 ///< Min of TDC_VDDCR_SOC
#define IDSOPT_DBG_TDCSOC_LIMIT_MAX 4294967295 ///< Max of TDC_VDDCR_SOC

///EDC Control
///Auto = Use the fused VDDCR_CPU TDC limit\nManual = User can set customized VDDCR_CPU TDC limit
typedef enum {
  IDSOPT_DBG_EDC_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_EDC_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_EDC_CTL;

///EDC_VDDCR_VDD
///VDDCR_CPU EDC Limit [mA]
#define IDSOPT_DBG_EDCVDD_LIMIT_MIN 0 ///< Min of EDC_VDDCR_VDD
#define IDSOPT_DBG_EDCVDD_LIMIT_MAX 0xffffffff ///< Max of EDC_VDDCR_VDD

///EDC_VDDCR_SOC
///VDDCR_SOC EDC Limit [mA]
#define IDSOPT_DBG_EDCSOC_LIMIT_MIN 0 ///< Min of EDC_VDDCR_SOC
#define IDSOPT_DBG_EDCSOC_LIMIT_MAX 0xffffffff ///< Max of EDC_VDDCR_SOC

///PSI0 Control
///Auto = Use the default EDC limits\nManual = User can set customized EDC limits
typedef enum {
  IDSOPT_DBG_PS_I0_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_PS_I0_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_PS_I0_CTL;

///PSI0_VDDCR_VDD
///VDDCR_VDD PSI0 Limit [mA]
#define IDSOPT_DBG_PS_I0_VDD_LIMIT_MIN 0 ///< Min of PSI0_VDDCR_VDD
#define IDSOPT_DBG_PS_I0_VDD_LIMIT_MAX 0xffffffff ///< Max of PSI0_VDDCR_VDD

///PSI0_VDDCR_SOC
///VDDCR_SOC PSI0 Limit [mA]
#define IDSOPT_DBG_PS_I0_SOC_LIMIT_MIN 0 ///< Min of PSI0_VDDCR_SOC
#define IDSOPT_DBG_PS_I0_SOC_LIMIT_MAX 0xffffffff ///< Max of PSI0_VDDCR_SOC

///Thermal Control
///Auto = Use the default TctlMax\nManual = User can set customized TctlMax
typedef enum {
  IDSOPT_DBG_THM_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_THM_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_THM_CTL;

///TctlMax
///Maximum operating temperature [Tctrl]
#define IDSOPT_DBG_TCTL_MAX_LIMIT_MIN 0 ///< Min of TctlMax
#define IDSOPT_DBG_TCTL_MAX_LIMIT_MAX 0xffffffff ///< Max of TctlMax

///PROCHOT Control
///Auto = Use the default PROCHOT deassertion ramp time\nManual = User can set customized PROCHOT deassertion ramp time
typedef enum {
  IDSOPT_DBG_PROCHOT_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_PROCHOT_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_PROCHOT_CTL;

///PROCHOT Deassertion Ramp Time
///PROCHOT deassertion ramp time [ms]
#define IDSOPT_DBG_PROCHOT_RAMP_TIME_MIN 0 ///< Min of PROCHOT Deassertion Ramp Time
#define IDSOPT_DBG_PROCHOT_RAMP_TIME_MAX 0xffffffff ///< Max of PROCHOT Deassertion Ramp Time

///AA Control
typedef enum {
  IDSOPT_DBG_AA_CTL_AUTO = 0xF,///<Auto
  IDSOPT_DBG_AA_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_AA_CTL;

///AA Mode Enable
///A+A Mode Enable
typedef enum {
  IDSOPT_DBG_AA_EN_AUTO = 0xF,///<Auto
  IDSOPT_DBG_AA_EN_DISABLE = 0,///<Disable
  IDSOPT_DBG_AA_EN_ENABLE = 1,///<Enable
} IDSOPT_DBG_AA_EN;

///AVFS Control
///Auto = Use the default AVFS coefficients\nManual = User can set customized AVFS coefficients
typedef enum {
  IDSOPT_DBG_AVFS_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_AVFS_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_AVFS_CTL;

///CorePsfFreq2
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_FREQ2_MIN 0 ///< Min of CorePsfFreq2
#define IDSOPT_DBG_AVFS_CORE_PSF_FREQ2_MAX 0xffffffff ///< Max of CorePsfFreq2

///CorePsfFreq
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_FREQ_MIN 0 ///< Min of CorePsfFreq
#define IDSOPT_DBG_AVFS_CORE_PSF_FREQ_MAX 0xffffffff ///< Max of CorePsfFreq

///CorePsfGfxActive
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_GFX_ACTIVE_MIN 0 ///< Min of CorePsfGfxActive
#define IDSOPT_DBG_AVFS_CORE_PSF_GFX_ACTIVE_MAX 0xffffffff ///< Max of CorePsfGfxActive

///CorePsfTemp
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_TEMP_MIN 0 ///< Min of CorePsfTemp
#define IDSOPT_DBG_AVFS_CORE_PSF_TEMP_MAX 0xffffffff ///< Max of CorePsfTemp

///CorePsfSidd
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_SIDD_MIN 0 ///< Min of CorePsfSidd
#define IDSOPT_DBG_AVFS_CORE_PSF_SIDD_MAX 0xffffffff ///< Max of CorePsfSidd

///CorePsfCac
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_CAC_MIN 0 ///< Min of CorePsfCac
#define IDSOPT_DBG_AVFS_CORE_PSF_CAC_MAX 0xffffffff ///< Max of CorePsfCac

///CorePsfNumActiveCores
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_MIN 0 ///< Min of CorePsfNumActiveCores
#define IDSOPT_DBG_AVFS_CORE_PSF_NUM_ACTIVE_CORES_MAX 0xffffffff ///< Max of CorePsfNumActiveCores

///CorePsfSigma
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_MIN 0 ///< Min of CorePsfSigma
#define IDSOPT_DBG_AVFS_CORE_PSF_SIGMA_MAX 0xffffffff ///< Max of CorePsfSigma

///CorePsfIddMaxCpu
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_IDD_MAX_CPU_MIN 0 ///< Min of CorePsfIddMaxCpu
#define IDSOPT_DBG_AVFS_CORE_PSF_IDD_MAX_CPU_MAX 0xffffffff ///< Max of CorePsfIddMaxCpu

///CorePsfIddMaxGfx
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_IDD_MAX_GFX_MIN 0 ///< Min of CorePsfIddMaxGfx
#define IDSOPT_DBG_AVFS_CORE_PSF_IDD_MAX_GFX_MAX 0xffffffff ///< Max of CorePsfIddMaxGfx

///CorePsfAcBtc
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_CORE_PSF_AC_BTC_MIN 0 ///< Min of CorePsfAcBtc
#define IDSOPT_DBG_AVFS_CORE_PSF_AC_BTC_MAX 0xffffffff ///< Max of CorePsfAcBtc

///L3PsfFreq2
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_FREQ2_MIN 0 ///< Min of L3PsfFreq2
#define IDSOPT_DBG_AVFS_L3_PSF_FREQ2_MAX 0xffffffff ///< Max of L3PsfFreq2

///L3PsfFreq
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_FREQ_MIN 0 ///< Min of L3PsfFreq
#define IDSOPT_DBG_AVFS_L3_PSF_FREQ_MAX 0xffffffff ///< Max of L3PsfFreq

///L3PsfGfxActive
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_GFX_ACTIVE_MIN 0 ///< Min of L3PsfGfxActive
#define IDSOPT_DBG_AVFS_L3_PSF_GFX_ACTIVE_MAX 0xffffffff ///< Max of L3PsfGfxActive

///L3PsfTemp
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_TEMP_MIN 0 ///< Min of L3PsfTemp
#define IDSOPT_DBG_AVFS_L3_PSF_TEMP_MAX 0xffffffff ///< Max of L3PsfTemp

///L3PsfSidd
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_SIDD_MIN 0 ///< Min of L3PsfSidd
#define IDSOPT_DBG_AVFS_L3_PSF_SIDD_MAX 0xffffffff ///< Max of L3PsfSidd

///L3PsfCac
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_CAC_MIN 0 ///< Min of L3PsfCac
#define IDSOPT_DBG_AVFS_L3_PSF_CAC_MAX 0xffffffff ///< Max of L3PsfCac

///L3PsfNumActiveCores
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_MIN 0 ///< Min of L3PsfNumActiveCores
#define IDSOPT_DBG_AVFS_L3_PSF_NUM_ACTIVE_CORES_MAX 0xffffffff ///< Max of L3PsfNumActiveCores

///L3PsfSigma
///Unsigned integer [Q8.24] --> 8 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_SIGMA_MIN 0 ///< Min of L3PsfSigma
#define IDSOPT_DBG_AVFS_L3_PSF_SIGMA_MAX 0xffffffff ///< Max of L3PsfSigma

///L3PsfIddMaxCpu
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_IDD_MAX_CPU_MIN 0 ///< Min of L3PsfIddMaxCpu
#define IDSOPT_DBG_AVFS_L3_PSF_IDD_MAX_CPU_MAX 0xffffffff ///< Max of L3PsfIddMaxCpu

///L3PsfIddMaxGfx
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_IDD_MAX_GFX_MIN 0 ///< Min of L3PsfIddMaxGfx
#define IDSOPT_DBG_AVFS_L3_PSF_IDD_MAX_GFX_MAX 0xffffffff ///< Max of L3PsfIddMaxGfx

///L3PsfAcBtc
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_L3_PSF_AC_BTC_MIN 0 ///< Min of L3PsfAcBtc
#define IDSOPT_DBG_AVFS_L3_PSF_AC_BTC_MAX 0xffffffff ///< Max of L3PsfAcBtc

///GfxPsfFreq2
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_FREQ2_MIN 0 ///< Min of GfxPsfFreq2
#define IDSOPT_DBG_AVFS_GFX_PSF_FREQ2_MAX 0xffffffff ///< Max of GfxPsfFreq2

///GfxPsfFreq
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_FREQ_MIN 0 ///< Min of GfxPsfFreq
#define IDSOPT_DBG_AVFS_GFX_PSF_FREQ_MAX 0xffffffff ///< Max of GfxPsfFreq

///GfxPsfGfxActive
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_GFX_ACTIVE_MIN 0 ///< Min of GfxPsfGfxActive
#define IDSOPT_DBG_AVFS_GFX_PSF_GFX_ACTIVE_MAX 0xffffffff ///< Max of GfxPsfGfxActive

///GfxPsfTemp
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_TEMP_MIN 0 ///< Min of GfxPsfTemp
#define IDSOPT_DBG_AVFS_GFX_PSF_TEMP_MAX 0xffffffff ///< Max of GfxPsfTemp

///GfxPsfSidd
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_SIDD_MIN 0 ///< Min of GfxPsfSidd
#define IDSOPT_DBG_AVFS_GFX_PSF_SIDD_MAX 0xffffffff ///< Max of GfxPsfSidd

///GfxPsfCac
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_CAC_MIN 0 ///< Min of GfxPsfCac
#define IDSOPT_DBG_AVFS_GFX_PSF_CAC_MAX 0xffffffff ///< Max of GfxPsfCac

///GfxPsfNumActiveCores
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_NUM_ACTIVE_CORES_MIN 0 ///< Min of GfxPsfNumActiveCores
#define IDSOPT_DBG_AVFS_GFX_PSF_NUM_ACTIVE_CORES_MAX 0xffffffff ///< Max of GfxPsfNumActiveCores

///GfxPsfSigma
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_SIGMA_MIN 0 ///< Min of GfxPsfSigma
#define IDSOPT_DBG_AVFS_GFX_PSF_SIGMA_MAX 0xffffffff ///< Max of GfxPsfSigma

///GfxPsfIddMaxCpu
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_IDD_MAX_CPU_MIN 0 ///< Min of GfxPsfIddMaxCpu
#define IDSOPT_DBG_AVFS_GFX_PSF_IDD_MAX_CPU_MAX 0xffffffff ///< Max of GfxPsfIddMaxCpu

///GfxPsfIddMaxGfx
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_IDD_MAX_GFX_MIN 0 ///< Min of GfxPsfIddMaxGfx
#define IDSOPT_DBG_AVFS_GFX_PSF_IDD_MAX_GFX_MAX 0xffffffff ///< Max of GfxPsfIddMaxGfx

///GfxPsfAcBtc
///Signed integer [Q8.24] --> 1 sign bit; 7 integer bits; 24 fractional bits
#define IDSOPT_DBG_AVFS_GFX_PSF_AC_BTC_MIN 0 ///< Min of GfxPsfAcBtc
#define IDSOPT_DBG_AVFS_GFX_PSF_AC_BTC_MAX 0xffffffff ///< Max of GfxPsfAcBtc

///Core DLDO Core
///0 = Normal Regulation\n1 = Bypass to VDDCR_VDD
typedef enum {
  IDSOPT_DBG_CORE_DLDO_0 = 0,///<0
  IDSOPT_DBG_CORE_DLDO_1 = 1,///<1
  IDSOPT_DBG_CORE_DLDO_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CORE_DLDO;

///GFX DLDO Core
///0 = Normal Regulation\n1 = Bypass to VDDCR_VDD
typedef enum {
  IDSOPT_DBG_GFX_DLDO_0 = 0,///<0
  IDSOPT_DBG_GFX_DLDO_1 = 1,///<1
  IDSOPT_DBG_GFX_DLDO_AUTO = 0xf,///<Auto
} IDSOPT_DBG_GFX_DLDO;

///CLDO VDDP
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM
typedef enum {
  IDSOPT_DBG_CLDO_VDDP_NORMALREGULATION = 0,///<Normal Regulation
  IDSOPT_DBG_CLDO_VDDP_BYPASSTOVDDCR_SOC = 1,///<Bypass to VDDCR_SOC
  IDSOPT_DBG_CLDO_VDDP_BYPASSTOVDDIO_MEM = 2,///<Bypass to VDDIO_MEM
  IDSOPT_DBG_CLDO_VDDP_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_VDDP;

///CLDO VDDM
///0 = Normal Regulation\n1 = Bypass to VDDCR_SOC\n2 = Bypass to VDDIO_MEM
typedef enum {
  IDSOPT_DBG_CLDO_VDDM_NORMALREGULATION = 0,///<Normal Regulation
  IDSOPT_DBG_CLDO_VDDM_BYPASSTOVDDCR_SOC = 1,///<Bypass to VDDCR_SOC
  IDSOPT_DBG_CLDO_VDDM_BYPASSTOVDDIO_MEM = 2,///<Bypass to VDDIO_MEM
  IDSOPT_DBG_CLDO_VDDM_AUTO = 0xf,///<Auto
} IDSOPT_DBG_CLDO_VDDM;

///VDDP Voltage Control
///Auto = Use default VDDP voltage\nManual = User can set custom VDDP voltage
typedef enum {
  IDSOPT_DBG_VDDP_VOLTAGE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_VDDP_VOLTAGE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_VDDP_VOLTAGE_CTL;

///VDDP Voltage
///Specify the target VDDP voltage [mV]
#define IDSOPT_DBG_VDDP_VOLTAGE_MIN 0 ///< Min of VDDP Voltage
#define IDSOPT_DBG_VDDP_VOLTAGE_MAX 0x7d0 ///< Max of VDDP Voltage

///VDDM Voltage Control
///Auto = Use default VDDM voltage\nManual = User can set custom VDDM voltage
typedef enum {
  IDSOPT_DBG_VDDM_VOLTAGE_CTL_AUTO = 0,///<Auto
  IDSOPT_DBG_VDDM_VOLTAGE_CTL_MANUAL = 1,///<Manual
} IDSOPT_DBG_VDDM_VOLTAGE_CTL;

///VDDM Voltage
///Specify the target VDDM voltage [mV]
#define IDSOPT_DBG_VDDM_VOLTAGE_MIN 0 ///< Min of VDDM Voltage
#define IDSOPT_DBG_VDDM_VOLTAGE_MAX 0x7d0 ///< Max of VDDM Voltage

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

///Core Dldo Psm Margin Control
///Manual = User can set customized Dldo Psm Margin
typedef enum {
  IDSOPT_DBG_CBS_DBG_DLDO_PSM_MARGIN_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CBS_DBG_DLDO_PSM_MARGIN_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CBS_DBG_DLDO_PSM_MARGIN_CTL;

///Core Dldo Psm Margin
///Specify the PSM offset to apply to the DLDOs -- signed integer [1 PSM count ~ 1.8mV]\n 0 = Invalid value.
#define IDSOPT_DBG_DLDO_PSM_MARGIN_MIN 0 ///< Min of Core Dldo Psm Margin
#define IDSOPT_DBG_DLDO_PSM_MARGIN_MAX 0xffffffff ///< Max of Core Dldo Psm Margin

///GFX Dldo Psm Margin Control
///Specify the PSM offset to apply to the GFX DLDOs -- signed integer [1 PSM count ~ 1.8mV]
typedef enum {
  IDSOPT_DBG_GFX_DLDO_PSM_MARGIN_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_GFX_DLDO_PSM_MARGIN_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_GFX_DLDO_PSM_MARGIN_CTL;

///GFX Dldo Psm Margin
///Specify the PSM offset to apply to the GFX DLDOs -- signed integer [1 PSM count ~ 1.8mV]
#define IDSOPT_DBG_GFX_DLDO_PSM_MARGIN_MIN 0 ///< Min of GFX Dldo Psm Margin
#define IDSOPT_DBG_GFX_DLDO_PSM_MARGIN_MAX 0xffffffff ///< Max of GFX Dldo Psm Margin

///VDDCR_VDD Voltage Offset Control
///Manual = User can set customized VDDCR_VDD Voltage Offset
typedef enum {
  IDSOPT_DBG_VDDCR_VDD_VOLTAGE_OFFSET_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_VDDCR_VDD_VOLTAGE_OFFSET_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_VDDCR_VDD_VOLTAGE_OFFSET_CTL;

///VDDCR_VDD Voltage Offset
///Specify the voltage offset to apply to VDDCR_VDD -- signed integer [mV]
#define IDSOPT_DBG_VDDCR_VDD_VOLTAGE_OFFSET_MIN 0 ///< Min of VDDCR_VDD Voltage Offset
#define IDSOPT_DBG_VDDCR_VDD_VOLTAGE_OFFSET_MAX 0xffffffff ///< Max of VDDCR_VDD Voltage Offset

///VDDCR_SOC Voltage Offset Control
///Manual = User can set customized VDDCR_SOC Voltage Offset
typedef enum {
  IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_CTL;

///VDDCR_SOC Voltage Offset
///Specify the voltage offset to apply to VDDCR_SOC -- signed integer [mV]
#define IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_MIN 0 ///< Min of VDDCR_SOC Voltage Offset
#define IDSOPT_DBG_VDDCR_SOC_VOLTAGE_OFFSET_MAX 0xffffffff ///< Max of VDDCR_SOC Voltage Offset

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

///UseCcxFreqCurveFuses
///0 = Use SMU FW default CCLK FtoP, PtoV and FtoV curves\n1 = Use fused CCLK FtoP, PtoV and FtoV curves
typedef enum {
  IDSOPT_DBG_USE_CCX_FREQ_CURVE_FUSES_0 = 0,///<0
  IDSOPT_DBG_USE_CCX_FREQ_CURVE_FUSES_1 = 1,///<1
  IDSOPT_DBG_USE_CCX_FREQ_CURVE_FUSES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_USE_CCX_FREQ_CURVE_FUSES;

///UseGfxFreqCurveFuses
///0 = Use SMU FW default GFXCLK FtoP and PtoV curves\n1 = Use fused GFXCLK FtoP and PtoV curves
typedef enum {
  IDSOPT_DBG_USE_GFX_FREQ_CURVE_FUSES_0 = 0,///<0
  IDSOPT_DBG_USE_GFX_FREQ_CURVE_FUSES_1 = 1,///<1
  IDSOPT_DBG_USE_GFX_FREQ_CURVE_FUSES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_USE_GFX_FREQ_CURVE_FUSES;

///UseCacSiddFuses
///0 = Use SMU FW default CAC and SIDD coefficients\n1 = Use fused CAC and SIDD coefficients
typedef enum {
  IDSOPT_DBG_USE_CAC_SIDD_FUSES_0 = 0,///<0
  IDSOPT_DBG_USE_CAC_SIDD_FUSES_1 = 1,///<1
  IDSOPT_DBG_USE_CAC_SIDD_FUSES_AUTO = 0xf,///<Auto
} IDSOPT_DBG_USE_CAC_SIDD_FUSES;

///DC BTC
///0 = Do not run DC BTC\n1 = Run DC BTC\nAuto = Use default DC BTC settings
typedef enum {
  IDSOPT_DBG_DC_BTC_0 = 0,///<0
  IDSOPT_DBG_DC_BTC_1 = 1,///<1
  IDSOPT_DBG_DC_BTC_AUTO = 0xF,///<Auto
} IDSOPT_DBG_DC_BTC;

///AC BTC
///0 = Do not run AC BTC\n1 = Run AC BTC in single frequency mode\n2 = Run AC BTC in 3 frequency mode\nAuto = Use default AC BTC settings
typedef enum {
  IDSOPT_DBG_AC_BTC_0 = 0,///<0
  IDSOPT_DBG_AC_BTC_1 = 1,///<1
  IDSOPT_DBG_AC_BTC_2 = 2,///<2
  IDSOPT_DBG_AC_BTC_AUTO = 0xF,///<Auto
} IDSOPT_DBG_AC_BTC;

///PSI
typedef enum {
  IDSOPT_DBG_NBIO_PSI_DISABLE_DISABLE = 1,///<Disable
  IDSOPT_DBG_NBIO_PSI_DISABLE_AUTO = 0xF,///<Auto
} IDSOPT_DBG_NBIO_PSI_DISABLE;

///Dd Stretch Thresh Control
///Enable means use the GfxStretchThresh value below
typedef enum {
  IDSOPT_DBG_CBS_DBG_DD_STRETCH_THRESH_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CBS_DBG_DD_STRETCH_THRESH_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CBS_DBG_DD_STRETCH_THRESH_CTL;

///Dd Stretch Thresh
///1 = 2.5%, range is 1 to 7
#define IDSOPT_DBG_DD_STRETCH_THRESH_MIN 0 ///< Min of Dd Stretch Thresh
#define IDSOPT_DBG_DD_STRETCH_THRESH_MAX 0x7 ///< Max of Dd Stretch Thresh

///Gfx Stretch Amount Control
///Enable means use the GfxStretchAmount value below
typedef enum {
  IDSOPT_DBG_CBS_DBG_GFX_STRETCH_AMOUNT_EN_CTL_MANUAL = 1,///<Manual
  IDSOPT_DBG_CBS_DBG_GFX_STRETCH_AMOUNT_EN_CTL_AUTO = 0,///<Auto
} IDSOPT_DBG_CBS_DBG_GFX_STRETCH_AMOUNT_EN_CTL;

///Gfx Stretch Amount
///the stretch amount acceptable range is from 0x0 to 0x5
#define IDSOPT_DBG_CBS_DBG_GFX_STRETCH_AMOUNT_MIN 0 ///< Min of Gfx Stretch Amount
#define IDSOPT_DBG_CBS_DBG_GFX_STRETCH_AMOUNT_MAX 0x5 ///< Max of Gfx Stretch Amount

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

///VDDCR_VDD Full Scale2 Telemetry Current (mA)
///Specify the VDDCR_VDD telemetry current slope2 [mA]
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE2_MIN 0 ///< Min of VDDCR_VDD Full Scale2 Telemetry Current (mA)
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE2_MAX 0xffffffff ///< Max of VDDCR_VDD Full Scale2 Telemetry Current (mA)

///VDDCR_VDD Full Scale3 Telemetry Current (mA)
///Specify the VDDCR_VDD telemetry current slope3 [mA]
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE3_MIN 0 ///< Min of VDDCR_VDD Full Scale3 Telemetry Current (mA)
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE3_MAX 0xffffffff ///< Max of VDDCR_VDD Full Scale3 Telemetry Current (mA)

///VDDCR_VDD Full Scale4 Telemetry Current (mA)
///Specify the VDDCR_VDD telemetry current slope4 [mA]
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE4_MIN 0 ///< Min of VDDCR_VDD Full Scale4 Telemetry Current (mA)
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE4_MAX 0xffffffff ///< Max of VDDCR_VDD Full Scale4 Telemetry Current (mA)

///VDDCR_VDD Full Scale5 Telemetry Current (mA)
///Specify the VDDCR_VDD telemetry current slope5 [mA]
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE5_MIN 0 ///< Min of VDDCR_VDD Full Scale5 Telemetry Current (mA)
#define IDSOPT_DBG_TELEMETRY_VDD_SLOPE5_MAX 0xffffffff ///< Max of VDDCR_VDD Full Scale5 Telemetry Current (mA)

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
  IDSOPT_DBG_MISC_GR_A1_TIME_POINT_EARLYBEFOREMEMORYINIT = 1,///<Early - before Memory Init
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
  IDSOPT_DBG_MISC_GR_A2_TIME_POINT_EARLYBEFOREMEMORYINIT = 1,///<Early - before Memory Init
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
  IDSOPT_DBG_MISC_GR_A3_TIME_POINT_EARLYBEFOREMEMORYINIT = 1,///<Early - before Memory Init
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
  IDSOPT_DBG_MISC_GR_A4_TIME_POINT_EARLYBEFOREMEMORYINIT = 1,///<Early - before Memory Init
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
  IDSOPT_DBG_MISC_GR_A5_TIME_POINT_EARLYBEFOREMEMORYINIT = 1,///<Early - before Memory Init
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
  IDSOPT_DBG_MISC_GR_A6_TIME_POINT_EARLYBEFOREMEMORYINIT = 1,///<Early - before Memory Init
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


#endif //_IDS_NV_INT_DEF_RV_H_

