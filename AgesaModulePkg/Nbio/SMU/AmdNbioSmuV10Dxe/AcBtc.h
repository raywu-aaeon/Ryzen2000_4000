/**
 * @file
 *
 * Ac BTC definitions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Nbio
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#ifndef _AC_BTC_H_
#define _AC_BTC_H_

/// Table Register Entry
typedef struct {
  UINT64          DataIn1[0x300];          /// <.data_in1 resq 0x40
  UINT64          DataIn2[0x300];          /// <.data_in2 resq 0x40
  UINT64          DataIn3[0x300];          /// <.data_in3 resq 0x40
  UINT64          DataIn4[0x300];          /// <.data_in4 resq 0x40
  UINT64          DataIn5[0x300];          /// <.data_in5 resq 0x40
  UINT64          DataIn6[0x300];          /// <.data_in6 resq 0x40
  UINT64          DataIn7[0x300];          /// <.data_in7 resq 0x40
  UINT64          DataIn8[0x300];          /// <.data_in8 resq 0x40
  UINT64          DataOut1[0x300];         /// <.data_out1 resq 0x40
  UINT64          DataOut2[0x300];         /// <.data_out2 resq 0x40
  UINT64          DataOut3[0x300];         /// <.data_out3 resq 0x40
  UINT64          DataOut4[0x300];         /// <.data_out4 resq 0x40
  UINT64          DataOut5[0x300];         /// <.data_out5 resq 0x40
  UINT64          DataOut6[0x300];         /// <.data_out6 resq 0x40
  UINT64          DataOut7[0x300];         /// <.data_out7 resq 0x40
  UINT64          DataOut8[0x300];         /// <.data_out8 resq 0x40
  UINT64          SynchLine;              /// <.synch_line resq 0x1
  UINT64          ActiveFPLoopCount1[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount2[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount3[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount4[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount5[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount6[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount7[30];  /// <.activeFP_loop_count resq 16
  UINT64          ActiveFPLoopCount8[30];  /// <.activeFP_loop_count resq 16
  UINT64          IdleFPLoopCount1[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount2[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount3[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount4[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount5[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount6[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount7[30];     /// <.idleFP_loop_count resq 16
  UINT64          IdleFPLoopCount8[30];     /// <.idleFP_loop_count resq 16
  UINT64          ThirdDNop1[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop2[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop3[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop4[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop5[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop6[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop7[30];           /// <.thirdD_nop resq 16
  UINT64          ThirdDNop8[30];           /// <.thirdD_nop resq 16
  UINT64          BasePtr[0x500];         /// <.BasePtr2 resq 0x500
  UINTN           tscWaitCount;             /// <. 2mS TSC count
} ACBTC_WORKLOAD_STRUCT;

EFI_STATUS
EFIAPI
StartBtc (
  );

EFI_STATUS
EFIAPI
RunBtc (
  );

VOID
AfterBtc (
  );

VOID
EFIAPI
CallbackAcBtc (
  IN      EFI_EVENT  Event,
  IN      VOID       *Context
  );

#endif

