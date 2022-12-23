;*****************************************************************************
;
; Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
;*****************************************************************************

.code
;/*++

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write IO byte
; *
; *  @param[in]   CX    IO port address
; *  @param[in]   DL    IO port Value
; */
PUBLIC  CpmIoWrite8
CpmIoWrite8     PROC
        mov     al, dl
        mov     dx, cx
        out     dx, al
        ret
CpmIoWrite8     ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write IO word
; *
; *  @param[in]   CX      IO port address
; *  @param[in]   DX      IO port Value
; */
PUBLIC  CpmIoWrite16
CpmIoWrite16    PROC
        mov     ax, dx
        mov     dx, cx
        out     dx, ax
        ret
CpmIoWrite16    ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write IO dword
; *
; *  @param[in]   CX      IO port address
; *  @param[in]   EDX     IO port Value
; */
PUBLIC CpmIoWrite32
CpmIoWrite32    PROC
        mov     eax, edx
        mov     dx, cx
        out     dx, eax
        ret
CpmIoWrite32    ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read IO byte
; *
; *  @param[in] CX  IO port address
; *  @retval    AL  IO port Value
; */
PUBLIC CpmIoRead8
CpmIoRead8      PROC
        mov     dx, cx
        in      al, dx
        ret
CpmIoRead8      ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read IO word
; *
; *  @param[in]   CX  IO port address
; *  @retval      AX  IO port Value
; */
PUBLIC CpmIoRead16
CpmIoRead16     PROC
        mov     dx, cx
        in      ax, dx
        ret
CpmIoRead16     ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read IO dword
; *
; *  @param[in]   CX  IO port address
; *  @retval      EAX IO port Value
; */
PUBLIC CpmIoRead32
CpmIoRead32     PROC
        mov     dx, cx
        in      eax, dx
        ret
CpmIoRead32     ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read MSR
; *
; *  @param[in]  RCX      MSR Address
; *  @retval     RAX      MSR Register Value
; */
PUBLIC CpmMsrRead
CpmMsrRead      PROC
        rdmsr
        and     rax, 0ffffffffh
        shl     rdx, 32
        or      rax, rdx
        ret
CpmMsrRead      ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write MSR
; *
; *  @param[in]  RCX        MSR Address
; *  @param[in]  RDX        MSR Register Data
; */
PUBLIC CpmMsrWrite
CpmMsrWrite     PROC
        mov     rax, rdx
        and     rax, 0ffffffffh
        shr     rdx, 32
        wrmsr
        ret
CpmMsrWrite     ENDP


;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read CPUID Raw Data
; *
; *  @param[in]  RCX    CPUID function
; *  @param[in]  RDX    Pointer to CPUID_DATA to save cpuid data
; */
PUBLIC CpmCpuidRawRead
CpmCpuidRawRead   PROC
    push rbx
    push rsi
    mov  rsi, rdx
    mov  rax, rcx
    cpuid
    mov [rsi],   eax
    mov [rsi+4], ebx
    mov [rsi+8], ecx
    mov [rsi+12],edx
    pop rsi
    pop rbx
    ret
CpmCpuidRawRead   ENDP


;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read TSC
; *
; *  @retval    RAX Time stamp counter value
; */

PUBLIC CpmReadTsc
CpmReadTsc      PROC
        rdtsc
        and     rax, 0ffffffffh
        shl     rdx, 32
        or      rax, rdx
        ret
CpmReadTsc      ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Find the most right hand side non-zero bit with
; *
; * @param[in]  ECX       Value
; */
PUBLIC CpmBitScanForward
CpmBitScanForward PROC
    bsf eax, ecx
    jnz nonZeroSource
    mov al,32
nonZeroSource:
    ret
CpmBitScanForward  ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Find the most left hand side non-zero bit.
; *
; * @param[in]  ECX       Value
; */
PUBLIC CpmBitScanReverse
CpmBitScanReverse PROC
    bsr eax, ecx
    jnz nonZeroSource
    mov al,0FFh
nonZeroSource:
    ret
CpmBitScanReverse  ENDP

END
