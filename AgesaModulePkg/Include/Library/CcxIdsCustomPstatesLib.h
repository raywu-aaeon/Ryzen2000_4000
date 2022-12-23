/* $NoKeywords:$ */
/**
 * @file
 *
 * Implement Custom Core Pstates
 *
 * Contains code that Custom Core Pstates
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision$   @e \$Date$
 *
 */
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

#ifndef _CCX_IDS_CUSTOM_PSTATES_LIB_H_
#define _CCX_IDS_CUSTOM_PSTATES_LIB_H_
#include <Library/AmdIdsHookLib.h>

#pragma pack (push, 1)

#define CCX_IDS_CORE_PSTATES_DISABLED 0
#define CCX_IDS_CORE_PSTATES_CUSTOM 1
#define CCX_IDS_CORE_PSTATES_AUTO 2

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

/// Custom Core Pstate
typedef struct {
  UINT8  Custom;            ///< Disable/Custom/Auto
  UINT8  CoreFid;           ///< Core FID
  UINT8  CoreDid;           ///< Core DID
  UINT8  CoreVid;           ///< Core VID
} IDS_CUSTOM_CORE_PSTATE;

/* P-state Current Limit Register 0xC0010061 */
#define MSR_PSTATE_CURRENT_LIMIT 0xC0010061ul

/// Pstate Current Limit MSR Register
typedef union {
  struct {                             ///< Bitfields of Pstate Current Limit MSR Register
    UINT64 CurPstateLimit:3;           ///< Current Pstate Limit
    UINT64 :1;                         ///< Reserved
    UINT64 PstateMaxVal:3;             ///< Pstate Max Value
    UINT64 :57;                        ///< Reserved
  } Field;
  UINT64  Value;
} IDS_PSTATE_CURLIM_MSR;

/// P-state MSR
typedef union {
  struct {                             ///< Bitfields of P-state MSR
    UINT64 CpuFid_7_0:8;               ///< CpuFid[7:0]
    UINT64 CpuDfsId:6;                 ///< CpuDfsId
    UINT64 CpuVid:8;                   ///< CpuVid
    UINT64 IddValue:8;                 ///< IddValue
    UINT64 IddDiv:2;                   ///< IddDiv
    UINT64 :31;                        ///< Reserved
    UINT64 PstateEn:1;                 ///< Pstate Enable
  } Field;
  UINT64  Value;
} IDS_PSTATE_MSR;


/// Update MSR
typedef struct {
  UINT32 MsrAddr;                      ///< MSR Address
  UINT64 MsrData;                      ///< MSR Data
} CCX_UPDATE_MSR;

VOID
CcxIdsCustomPstateSetMsrLib (
  IN       IDS_CUSTOM_CORE_PSTATE  *CustomPstates
  );

#pragma pack (pop)
#endif // _CCX_IDS_CUSTOM_PSTATES_ZEN_LIB_H_
