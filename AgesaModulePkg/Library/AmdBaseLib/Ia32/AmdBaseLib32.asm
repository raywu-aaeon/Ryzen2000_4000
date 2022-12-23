;/**
; * @file
; *
; * Agesa library 32bit
; *
; * Contains AMD AGESA Library
; *
; * @xrefitem bom "File Content Label" "Release Content"
; * @e project:      AGESA
; * @e sub-project:  Lib
; * @e \$Revision: 312770 $   @e \$Date: 2015-02-11 13:24:42 +0800 (Wed, 11 Feb 2015) $
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

.586p
.xmm
.model  flat
ASSUME FS:NOTHING
.code

;/*---------------------------------------------------------------------------------------*/
;/**
; *  Enter debugger on SimNow
; *
; * @retval  Flag to indicate execution of Port 80 loop code.
; *
; */
PUBLIC LibAmdSimNowEnterDebugger
LibAmdSimNowEnterDebugger PROC NEAR C USES EBX ECX EDX ESI
    mov     si, 0                   ; Clear SI to indicate display message on port 80
    mov     eax, 0BACCD00Bh         ; Backdoor in SimNow
    mov     ebx, 2                  ; Select breakpoint feature
    cpuid

    mov     ax, si                  ; Return value in SI
    ret
LibAmdSimNowEnterDebugger ENDP


;/*---------------------------------------------------------------------------------------*/
;/**
; *  Force breakpoint on HDT
; *
; *
; */
PUBLIC LibAmdHDTBreakPoint
LibAmdHDTBreakPoint PROC NEAR C

    pushad

    mov ecx, 0C001100Ah             ;bit 0 = HDT redirect
    mov edi, 09C5A203Ah             ;Password
    RDMSR                           ;
    or al, 1                        ;
    WRMSR                           ;
    mov al, 0B2h                    ;Marker = B2
    db 0F1h                         ;ICEBP

    popad
    ret

LibAmdHDTBreakPoint ENDP

;/*---------------------------------------------------------------------------------------*/
;/**
; *  FPU init
; *
; *
; */

PUBLIC LibAmdFinit
LibAmdFinit  PROC NEAR C
    finit
    ret
LibAmdFinit  ENDP

END

