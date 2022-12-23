;/**
; * @file
; *
; *
; * @xrefitem bom "File Content Label" "Release Content"
; * @e project:      AGESA
; * @e sub-project:  Ccx
; * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
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

.code

EXTRN BspMsrLocation:DWORD
EXTRN ApSyncLocation:DWORD
EXTRN AllowToLaunchNextThreadLocation:DWORD
EXTRN ApStackBasePtr:NEAR PTR QWORD
EXTRN RegSettingBeforeLaunchingNextThread:NEAR
EXTRN ApEntryPointInC:NEAR
EXTRN ApGdtDescriptor:WORD

ApAsmCode PROC

  mov ax, 30h
  mov ds, ax
  mov es, ax
  mov ss, ax

  ; Reset RSP
  mov eax, 1
  cpuid
  shr ebx, 24

  ; Use 1-based APIC ID to index into the top of this AP's stack
  xor rax, rax
  mov eax, ebx
  mov ecx, 0400h
  mul ecx

  ; Make space for the first qword
  sub eax, 8

  mov rsi, ApStackBasePtr
  add rax, rsi
  mov rsp, rax

  ; Enable Fixed MTRR modification
  mov ecx, 0C0010010h
  rdmsr
  or  eax, 00080000h
  wrmsr

  ; Setup MSRs to BSP values
  mov esi, BspMsrLocation
MsrStart:
  mov ecx, [esi]
  cmp ecx, 0FFFFFFFFh
  jz MsrDone
  add esi, 4
  mov eax, [esi]
  add esi, 4
  mov edx, [esi]
  wrmsr
  add esi, 4
  jmp MsrStart

MsrDone:
  ; Disable Fixed MTRR modification and enable MTRRs
  mov ecx, 0C0010010h
  rdmsr
  and eax, 0FFF7FFFFh
  or  eax, 00140000h
  bt  eax, 21
  jnc Tom2Disabled
  bts eax, 22
Tom2Disabled:
  wrmsr

  ; Enable caching
  mov rax, cr0
  btr eax, 30
  btr eax, 29
  mov cr0, rax

  ; Call into C code before next thread is launched
  call RegSettingBeforeLaunchingNextThread

  ; Increment call count to allow to launch next thread
  mov esi, AllowToLaunchNextThreadLocation
  lock inc WORD PTR [esi]

  ; Call into C code
  call ApEntryPointInC

  ; Set up resident GDT
  lea rsi, ApGdtDescriptor
  lgdt FWORD PTR [rsi]
  lea rbx, NewGdtAddress
  lea rsi, NewGdtOffset
  mov [rsi], ebx
  lea rsi, NewGdtOffset
  jmp far ptr [rsi]
NewGdtAddress:

  ; Increment call count to indicate core is done running
  mov esi, ApSyncLocation
  lock inc WORD PTR [esi]

  ; Hlt
@@:
  cli
  hlt
  jmp @B

ApAsmCode ENDP

NewGdtOffset LABEL DWORD
  DD  ?
NewGdtSelector LABEL WORD
  DW  0038h

END

