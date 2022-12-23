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

;======================================================================
; SynchronizeAllApsF17Rv:  Wrapper code for boot time calibration workloads
;
;   In:
;       rdx - monitor address
;       rcx - increment address
;
;   Out:
;       None
;
;   Destroyed:
;       None
;
;======================================================================
SynchronizeAllApsF17Rv PROC PUBLIC
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

;  cli
  lock  inc dword Ptr [rcx]
;  mov   rax, rdx
;  mov   rcx, 0
;  mov   rdx, 0
;  monitor rax, rcx, rdx
;  mov   rax, 0
;  mov   rcx, 0
;  mwait rax, rcx

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
SynchronizeAllApsF17Rv ENDP

END


