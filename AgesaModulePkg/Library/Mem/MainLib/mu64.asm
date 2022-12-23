;*****************************************************************************
; AMD Generic Encapsulated Software Architecture
;
;  $Workfile:: mu.asm   $ $Revision:: 309#$  $Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
; Description: Main memory controller system configuration for AGESA
;
;
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
;============================================================================


    .XLIST
    .LIST

    .CODE

;----------------------------------------------------------------------------
; _MFENCE();
;
_MFENCE macro
    db  0Fh,0AEh,0F0h
    endm

;===============================================================================
;MemUFlushPattern:
;
; Flush a pattern of 72 bit times (per DQ) from cache.  This procedure is used
;to ensure cache miss on the next read training.
;
;             In: Address   - Physical address to be flushed
;                 ClCount   - number of cachelines to be flushed
;            Out:
;
;All registers preserved.
;===============================================================================
MemUFlushPattern PROC PUBLIC Address:DWORD, ClCount:WORD
        push rdi
        push rcx
        mov edi,Address
        movzx ecx,ClCount
        @@:
        _MFENCE                     ; Force strong ordering of clflush
        db  64h,0Fh,0AEh,3Fh        ; MemUClFlush fs:[edi]
        _MFENCE
        add edi,64
        loop @B
        pop rcx
        pop rdi
        ret
MemUFlushPattern ENDP

;===============================================================================
;MemUReadCachelines:
;
; Read a pattern of 72 bit times (per DQ), to test dram functionality.  The
;pattern is a stress pattern which exercises both ISI and crosstalk.  The number
;of cache lines to fill is dependent on DCT width mode and burstlength.
;
;             In: Buffer    - pointer to a buffer where read data will be stored
;                 Address   - Physical address to be read
;                 ClCount   - number of cachelines to be read
;            Out:
;
;All registers preserved.
;===============================================================================
MemUReadCachelines PROC PUBLIC
        ret
MemUReadCachelines ENDP

;===============================================================================
;MemUWriteCachelines:
;   Write a test pattern to DRAM
;
;             In: Pattern   - pointer to the write pattern
;                 Address   - Physical address to be read
;                 ClCount   - number of cachelines to be read
;            Out:
;
;All registers preserved.
;===============================================================================
MemUWriteCachelines PROC PUBLIC
        ret
MemUWriteCachelines ENDP

;===============================================================================
;AlignPointerTo16Byte:
;   Modifies BufferPtr to be 16 byte aligned
;
;             In: BufferPtrPtr - Pointer to buffer pointer
;            Out: BufferPtrPtr - Pointer to buffer pointer that has been 16 byte aligned
;
;All registers preserved.
;===============================================================================
AlignPointerTo16Byte PROC PUBLIC BufferPtrPtr:NEAR PTR DWORD
        push rdx
        push rax
        mov rdx, BufferPtrPtr
        mov rax, [rdx]
        add rax, 16
        and ax, 0FFF0h
        mov [rdx], rax
        pop rax
        pop rdx
        ret
AlignPointerTo16Byte ENDP

;===============================================================================
;MemUMFenceInstr:
;   Serialize instruction
;
;             In:
;            Out:
;
;All registers preserved.
;===============================================================================
MemUMFenceInstr PROC PUBLIC
        _MFENCE
        ret
MemUMFenceInstr ENDP

    END

