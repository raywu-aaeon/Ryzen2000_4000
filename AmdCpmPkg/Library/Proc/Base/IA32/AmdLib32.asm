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

.586p
.model  flat
.code

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write IO byte
; *
; *  @param[in]   Address IO port address
; *  @param[in]   Data    IO port Value
; */
public  CpmIoWrite8
CpmIoWrite8     PROC NEAR C USES DX AX Address:WORD, Data:Byte
        mov     dx, Address
        mov     al, Data
        out     dx, al
        ret
CpmIoWrite8     ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write IO word
; *
; *  @param[in]   Address IO port address
; *  @param[in]   Data    IO port Value
; */
public CpmIoWrite16
CpmIoWrite16    PROC NEAR C USES DX AX Address:WORD, Data:WORD
        mov     dx, Address
        mov     ax, Data
        out     dx, ax
        ret
CpmIoWrite16    ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write IO dword
; *
; *  @param[in]   Address IO port address
; *  @param[in]   Data    IO port Value
; */
public CpmIoWrite32
CpmIoWrite32    PROC NEAR C USES DX EAX Address:WORD, Data:DWORD
        mov     dx, Address
        mov     eax, Data
        out     dx, eax
        ret
CpmIoWrite32    ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read IO byte
; *
; *  @param[in] - IO port address
; *  @retval      IO port Value
; */
public CpmIoRead8
CpmIoRead8      PROC NEAR C USES DX Address:WORD
        mov     dx, Address
        in      al, dx
        ret
CpmIoRead8      ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read IO word
; *
; *  @param[in]   Address IO port address
; *  @retval      IO port Value
; */
public CpmIoRead16
CpmIoRead16     PROC NEAR C USES DX Address:WORD
        mov     dx, Address
        in      ax, dx
        ret
CpmIoRead16     ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read IO dword
; *
; *  @param[in]   Address  IO port address
; *  @retval      IO port Value
; */
public CpmIoRead32
CpmIoRead32     PROC NEAR C USES DX Address:WORD
        mov     dx, Address
        in      eax, dx
        ret
CpmIoRead32     ENDP


;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read MSR
; *
; *  @param[in]  Address  MSR Address
; *  @retval     MSR register Value
; */
public CpmMsrRead
CpmMsrRead      PROC NEAR C USES ECX Address:DWORD
        mov     ecx, Address
        rdmsr
        ret
CpmMsrRead      ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Write MSR
; *
; *  @param[in]  Address    MSR Address
; *  @param[in]  Data       MSR Register Data
; */
public CpmMsrWrite
CpmMsrWrite     PROC NEAR C USES ECX Address:DWORD, Data:QWORD
        mov     ecx, Address
        mov     eax, DWORD PTR Data[0]
        mov     edx, DWORD PTR Data[4]
        wrmsr
        ret
CpmMsrWrite     ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read CPUID Raw Data
; *
; *  @param[in]  Func   CPUID function
; *  @param[in]  DATA   Pointer to CPUID_DATA to save cpuid data
; */
public CpmCpuidRawRead
CpmCpuidRawRead PROC NEAR C  Func:DWORD, DATA:PTR
        pushad
        mov     eax, Func
        cpuid
        mov     esi, DATA
        mov     [esi],   eax
        mov     [esi+4], ebx
        mov     [esi+8], ecx
        mov     [esi+12],edx
        popad
        ret
CpmCpuidRawRead ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Read TSC
; *
; *  @retval     Time stamp counter value
; */
public CpmReadTsc
CpmReadTsc      PROC    NEAR C
        rdtsc
        ret
CpmReadTsc      ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Find the most right hand side non-zero bit.
; *
; * @param[in]  Value       Value
; */
PUBLIC CpmBitScanForward
CpmBitScanForward PROC NEAR C Value:DWORD
    mov eax, Value
    bsf eax, Value
    .if (Zero?)
      mov al,32
    .endif
    ret
CpmBitScanForward  ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Find the most left hand side non-zero bit.
; *
; * @param[in]  Value       Value
; */
PUBLIC CpmBitScanReverse
CpmBitScanReverse PROC NEAR C Value:DWORD
    mov eax, Value
    bsr eax, Value
    .if (Zero?)
      mov al,0FFh
    .endif
    ret
CpmBitScanReverse  ENDP

END
