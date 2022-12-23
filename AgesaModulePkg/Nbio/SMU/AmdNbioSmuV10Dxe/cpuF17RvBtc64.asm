;/**
; * @file
; *
; * AMD Family_17 Zepplen boot time calibration code
; *
; * @xrefitem bom "File Content Label" "Release Content"
; * @e project:      AGESA
; * @e sub-project:
; * @e \$Revision: 312756 $
; */
;*****************************************************************************
;
; Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
;
; AMD is granting you permission to use this software and documentation (if
; any) (collectively, the "Materials") pursuant to the terms and conditions of
; the Software License Agreement included with the Materials.  If you do not
; have a copy of the Software License Agreement, contact your AMD
; representative for a copy.
;
; You agree that you will not reverse engineer or decompile the Materials, in
; whole or in part, except as allowed by applicable law.
;
; WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
; ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
; INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
; MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
; CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
; OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
; exclusion of implied warranties, so the above exclusion may not apply to
; You.
;
; LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
; NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
; INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
; THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
; ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
; liability to You for all damages, losses, and causes of action (whether in
; contract, tort (including negligence) or otherwise) exceed the amount of
; $100 USD. You agree to defend, indemnify and hold harmless AMD and its
; licensors, and any of their directors, officers, employees, affiliates or
; agents from and against any and all loss, damage, liability and other
; expenses (including reasonable attorneys' fees), resulting from Your use of
; the Materials or violation of the terms and conditions of this Agreement.
;
; U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
; "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
; subject to the restrictions as set forth in FAR 52.227-14 and
; DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
; Government constitutes acknowledgment of AMD's proprietary rights in them.
;
; EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
; stated in the Software License Agreement.
;******************************************************************************
 text  SEGMENT

XSET_BV MACRO
        db 00fh, 001h, 0d1h
ENDM

XGET_BV MACRO
        db 00fh, 001h, 0d0h
ENDM


;======================================================================
; ExecuteF17RvBtc:  Wrapper code for boot time calibration workloads
;
;   In:
;       rdx - buffer address for workloads
;       rcx - test to run
;
;   Out:
;       None
;
;   Destroyed:
;       None
;
;======================================================================
ExecuteHalt PROC PUBLIC
cli
hlt
jmp ExecuteHalt
ExecuteHalt ENDP


;======================================================================
; ExecuteF17RvBtc:  Wrapper code for boot time calibration workloads
;
;   In:
;       rdx - buffer address for workloads
;       rcx - test to run
;
;   Out:
;       None
;
;   Destroyed:
;       None
;
;======================================================================
ExecuteF17RvBtc PROC PUBLIC
  push  rax
  push  rbx
  push  rcx
  push  rdx
  push  rdi
  push  rsi
  push  rbp
  push  r8
  push  r9
  push  r10
  push  r11
  push  r12
  push  r13
  push  r14
  push  r15
  pushfq

;;EGH do this alignment in c code before calling
;  add   rdx, 63
;  and   rdx, 0FFFFFFFFFFFFFFC0h
  push  rcx
  push  rdx
  mov   rax, 1
  cpuid
  bt    rcx, 26
  jc    SetupAVX
  pop   rdx
  pop   rcx
  jmp   NoAVX

SetupAVX:
  mov   r10, cr4
  mov   r11, r10
  bts   r10, 18
  mov   cr4, r10
  xor   rcx, rcx
  XGET_BV
  mov   r12, rax
  mov   r13, rdx
  mov   rax, 0dh
  cpuid
  xor   rdx, rdx
  xor   rcx, rcx
  XSET_BV
  pop   rdx
  pop   rcx
  push  r11
  push  r12
  push  r13
  call  cpuF17RvBtc
  pop   rdx
  pop   rax
  xor   rcx, rcx
  XSET_BV
  pop   r11
  mov   cr4, r11

NoAVX:
  popfq
  pop   r15
  pop   r14
  pop   r13
  pop   r12
  pop   r11
  pop   r10
  pop   r9
  pop   r8
  pop   rbp
  pop   rsi
  pop   rdi
  pop   rdx
  pop   rcx
  pop   rbx
  pop   rax
  ret
ExecuteF17RvBtc ENDP

;======================================================================
; cpuF17RvBtc: The workloads.
;
;   In:
;       rdx - buffer address for workloads
;       rcx - test to run
;
;   Out:
;       None
;
;   Destroyed:
;       Many
;
;======================================================================
cpuF17RvBtc PROC PUBLIC
include cpuF17RvBtc64.inc
cpuF17RvBtc ENDP

END


