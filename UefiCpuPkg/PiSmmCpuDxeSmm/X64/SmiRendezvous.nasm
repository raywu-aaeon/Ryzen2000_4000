;------------------------------------------------------------------------------ ;
; Copyright (c) 2016 - 2019, Intel Corporation. All rights reserved.<BR>
; Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
; SPDX-License-Identifier: BSD-2-Clause-Patent
;
; Module Name:
;
;   SmiEntry.nasm
;
; Abstract:
;
;   Code template of the SMI handler for a particular processor
;
;-------------------------------------------------------------------------------

%macro SETSSBSY        0
    DB 0xF3, 0x0F, 0x01, 0xE8
%endmacro

%macro READSSP_RAX     0
    DB 0xF3, 0x48, 0x0F, 0x1E, 0xC8
%endmacro

%macro INCSSP_RAX      0
    DB 0xF3, 0x48, 0x0F, 0xAE, 0xE8
%endmacro



extern ASM_PFX(SmiRendezvous)
extern ASM_PFX(CpuSmmDebugEntry)
extern ASM_PFX(CpuSmmDebugExit)

    DEFAULT REL
    SECTION .text

global ASM_PFX(SmiRendezvousEntry)
BITS 64
;Below function will be invoke in both CPL0 mode and CPL3 mode
;Input for this func, rdx CpuIndex, r15 return address
;If it executed in CPL0 mode, it can return back to SmiEntry by jmp r15
;If it executed in CPL3 mode, it can return back to SmiEntry through callgate provide in r15
;This routine need to ensure stack balance
SmiRendezvousEntry:
    mov     rbx, rdx
    add     rsp, -0x20


    mov     rcx, rbx
    call    ASM_PFX(CpuSmmDebugEntry)

    mov     rcx, rbx
    call    ASM_PFX(SmiRendezvous)

    mov     rcx, rbx
    call    ASM_PFX(CpuSmmDebugExit)

    add     rsp, 0x20

    mov     ax, cs
    and     ax, 0x03
    cmp     al, 0x03                                              ;   query to see if CPL3
    jz      Callgate
    jmp     r15                                                   ;   r15 contain the return address to SmiEntry
Callgate:
;   invoke CALL GATE
;   In a call-gate transfer, the CS selector points to a call-gate descriptor rather than a code-segment descriptor, and the rIP is ignored
;   (but required by the instruction).
    push    r15
    call    far qword [rsp]             ; return to ring 0 via call gate
    jmp     $                           ; Code should not reach here
