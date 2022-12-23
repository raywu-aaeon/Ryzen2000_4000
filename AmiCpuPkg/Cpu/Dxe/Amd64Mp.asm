;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

;<AMI_FHDR_START>
;---------------------------------------------------------------------------
;
; Name:         Amd64Mp.asm
;
; Description:	CPU MP and interrupt specific code
;
;<AMI_FHDR_END>
;*************************************************************************

.code
include token.equ

public InterruptHandlerStart
public InterruptHandlerSize
public InterruptHandlerTblFixup

EFI_FX_SAVE_STATE_X64 STRUCT
    Fcw         dw ?
    Fsw         dw ?
    Ftw         dw ?
    Opcode      dw ?
    RegRip      dq ?
    DataOffset  dq ?
    Rsv1        db 8  dup (?)
    St0Mm0      db 10 dup (?)
    Rsv2        db 6  dup (?)
    St1Mm1      db 10 dup (?)
    Rsv3        db 6  dup (?)
    St2Mm2      db 10 dup (?)
    Rsv4        db 6  dup (?)
    St3Mm3      db 10 dup (?)
    Rsv5        db 6  dup (?)
    St4Mm4      db 10 dup (?)
    Rsv6        db 6  dup (?)
    St5Mm5      db 10 dup (?)
    Rsv7        db 6  dup (?)
    St6Mm6      db 10 dup (?)
    Rsv8        db 6  dup (?)
    St7Mm7      db 10 dup (?)
    Rsv9        db 6  dup (?)
    RegXmm0     db 16 dup (?)
    RegXmm1     db 16 dup (?)
    RegXmm2     db 16 dup (?)
    RegXmm3     db 16 dup (?)
    RegXmm4     db 16 dup (?)
    RegXmm5     db 16 dup (?)
    RegXmm6     db 16 dup (?)
    RegXmm7     db 16 dup (?)
    RegXmm8     db 16 dup (?)
    RegXmm9     db 16 dup (?)
    RegXmm10    db 16 dup (?)
    RegXmm11    db 16 dup (?)
    RegXmm12    db 16 dup (?)
    RegXmm13    db 16 dup (?)
    RegXmm14    db 16 dup (?)
    RegXmm15    db 16 dup (?)
    Rsv10       db 96 dup (?)
EFI_FX_SAVE_STATE_X64 ENDS


EFI_SYSTEM_CONTEXT_X64 STRUCT
    ExceptionData dq ?
    FxSaveState EFI_FX_SAVE_STATE_X64 <>
    RegDr0      dq ?
    RegDr1      dq ?
    RegDr2      dq ?
    RegDr3      dq ?
    RegDr6      dq ?
    RegDr7      dq ?
    RegCr0      dq ?
    RegCr1      dq ?  ;Reserved 
    RegCr2      dq ?
    RegCr3      dq ?
    RegCr4      dq ?
    RegCr8      dq ?
    RegRflags   dq ?
    RegLdtr     dq ?
    RegTr       dq ?
    RegGdtr     dq ?, ?
    RegIdtr     dq ?, ?
    RegRip      dq ?
    RegGs       dq ?
    RegFs       dq ?
    RegEs       dq ?
    RegDs       dq ?
    RegCs       dq ?
    RegSs       dq ?
    RegRdi      dq ?
    RegRsi      dq ?
    RegRbp      dq ?
    RegRsp      dq ?
    RegRbx      dq ?
    RegRdx      dq ?
    RegRcx      dq ?
    RegRax      dq ?
    RegR8       dq ?
    RegR9       dq ?
    RegR10      dq ?
    RegR11      dq ?
    RegR12      dq ?
    RegR13      dq ?
    RegR14      dq ?
    RegR15      dq ?
EFI_SYSTEM_CONTEXT_X64 ENDS

INT_DATA_NO_EX STRUCT
    Retoffs     dq ?
    RetSeg      dq ?
    Flags       dq ?
    RegRsp      dq ?
    RegSs       dq ?
INT_DATA_NO_EX ENDS

INT_DATA_EX STRUCT
    ErrorCode   dq ?
    Retoffs     dq ?
    RetSeg      dq ?
    Flags       dq ?
    RegRsp      dq ?
    RegSs       dq ?
INT_DATA_EX ENDS

INT_DATA UNION
    NoEx    INT_DATA_NO_EX <>
    Ex      INT_DATA_EX <>
INT_DATA ENDS

INT_HDL_ENTRY_STACK STRUCT
    RegRdi      dq ?
    Handler     dq ?
    RegRax      dq ?
    Exception   dq ?
    IntData INT_DATA <>
INT_HDL_ENTRY_STACK ENDS


align 16
CpuSupportInterruptHandlerStart equ $

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure: EfiCpuEnableInterrupt
;
; Description: Enable CPU Interrupts.
;
; Input:
;      eax interrupt number
;
; Output:
;      None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

CommonEntry:
        cli
        push    rbx
        mov     rbx, [rsp + 10h]
        ;mov rax, InterruptPtrTable
            db 48h, 0B8h
InterruptPtrTableAddrFixup EQU $
            dq  0
        lea     rax, [rax + rbx * 8]
        cmp     qword ptr [rax], 00h    ; Zero if no int handler installed.
        pop     rbx
        je      NoIntHandler

        push    qword ptr [rax]         ;push handler        
        push    rdi                     ;Must manually update edi since it is being destoryed.
        mov     rdi, rsp

        ;rsp is aligned for fxsave below.
        and     rsp, 0fffffff0h         ;Align to 16-byte boundary.

        ;The registers are stored on stack to match EFI_SYSTEM_CONTEXT_X64
        push    r15
        push    r14
        push    r13
        push    r12
        push    r11
        push    r10
        push    r9
        push    r8
        push    rax
        push    rcx
        push    rdx
        push    rbx
        push    rsp
        push    rbp
        push    rsi
        push    rdi
        xor     eax, eax
        mov     ax, ss
        push    rax
        mov     ax, cs
        push    rax
        mov     ax, ds
        push    rax
        mov     ax, es
        push    rax
        mov     ax, fs
        push    rax
        mov     ax, gs
        push    rax

        sub     esp, 64 ;RIP, idtr, gdtr, etc. updated later
        mov     rax, cr8
        push    rax
        mov     rax, cr4
        push    rax        
        mov     rax, cr3
        push    rax
        mov     rax, cr2
        push    rax
        push    0       ;reserved
        mov     rax, cr0
        push    rax
        mov     rax, dr7
        push    rax
        mov     rax, dr6
        push    rax
        mov     rax, dr3
        push    rax
        mov     rax, dr2
        push    rax
        mov     rax, dr1
        push    rax
        mov     rax, dr0
        push    rax
        sub     rsp, size EFI_FX_SAVE_STATE_X64
        fxsave  [rsp]
        push    rax ;Exception data added later. Dummy push.

        mov     rbp, rsp    ;rbp = EFI_SYSTEM_CONTEXT_X64

        xor     eax, eax
        str     ax
        mov     (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegTr, rax

        ;Clear upper bytes
        xor     eax, eax
        mov     (EFI_SYSTEM_CONTEXT_X64 ptr [rbp + 8]).RegGdtr, rax
        sgdt    (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegGdtr
        mov     rbx, (EFI_SYSTEM_CONTEXT_X64 ptr [rbp + 2]).RegGdtr
        mov     rax, [rbx + 8 * rax]
        mov     (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegLdtr, rax

        ;Clear upper bytes
        xor     eax, eax
        mov     (EFI_SYSTEM_CONTEXT_X64 ptr [rbp + 8]).RegIdtr, rax
        sidt    (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegIdtr

        mov     rax, (INT_HDL_ENTRY_STACK ptr [rdi]).RegRax
        mov     (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRax, rax

        mov     rax, (INT_HDL_ENTRY_STACK ptr [edi]).RegRdi
        mov     (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRdi, rax

        ;Some Exceptions have a exception code. Others don't.
        ;INT_HDL_ENTRY_STACK is the structure on stack above EFI_SYSTEM_CONTEXT_X64.
        ;This contains the original stack, rip, exception code, and other saved registers.
        mov     rax, (INT_HDL_ENTRY_STACK ptr [rdi]).Exception
        ;8, 10 - 14, 17
        cmp     al, 7
        jle     noerrcode
        cmp     al, 9
        je      noerrcode
        ;int 15 not defined
        cmp     al, 16
        je      noerrcode
        cmp     al, 18
        jae     noerrcode
;errcode:       
        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.Ex.ErrorCode
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).ExceptionData, rax

        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.Ex.Flags
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRflags, rax

        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.Ex.Retoffs
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRip, rax
        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.Ex.RetSeg
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegCs, rax

        mov   rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.Ex.RegSs
        mov   (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegSs, rax
        mov   rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.Ex.RegRsp
        mov   (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRsp, rax

        jmp     gotointerrupt

noerrcode:
        xor eax, eax
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).ExceptionData, rax

        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.NoEx.Flags
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRflags, rax

        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.NoEx.Retoffs
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRip, rax
        mov rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.NoEx.RetSeg
        mov (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegCs, rax

        mov   rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.NoEx.RegSs
        mov   (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegSs, rax
        mov   rax, (INT_HDL_ENTRY_STACK ptr [rdi]).IntData.NoEx.RegRsp
        mov   (EFI_SYSTEM_CONTEXT_X64 ptr [rbp]).RegRsp, rax
        
gotointerrupt:        

        cld

        mov     rdx, rbp                ;currently esp = ebp
        mov     rbp, rsp
        and     rsp, 0FFFFFFF0h         ;guarantee 16-byte stack alignment
        
       
        ;Call the interrupt handler which has this C function.
        ;VOID (*EFI_CPU_INTERRUPT_HANDLER) (
        ;     IN EFI_EXCEPTION_TYPE   InterruptType,
        ;     IN EFI_SYSTEM_CONTEXT   SystemContext)
        mov     rcx, (INT_HDL_ENTRY_STACK ptr [edi]).Exception
        mov     rax, (INT_HDL_ENTRY_STACK ptr [edi]).Handler

        sub     rsp, 32
        call    rax

        mov     rsp, rbp

        fxrstor (EFI_SYSTEM_CONTEXT_X64 ptr [rsp]).FxSaveState

        ;Remove data to on stack to discard.
        add     rsp, size EFI_SYSTEM_CONTEXT_X64 - 16 * 8

        ;Restore the original registers.
        add     rsp, 8  ;Skip rdi. This the original. We need the current rdi..
        pop     rsi
        pop     rbp
        add     rsp, 8  ;Skip rsp. This is the original. We the current rsp.
        pop     rbx
        pop     rdx
        pop     rcx
        pop     rax
        pop     r8
        pop     r9
        pop     r10
        pop     r11
        pop     r12
        pop     r13
        pop     r14
        pop     r15

        mov     rsp, rdi
        pop     rdi
        add     rsp, 8      ;remove handler saved on stack.
NoIntHandler:
        pop     rax
        add     rsp, 8      ;remove exception
        iretq               ;flags are restored on iretd
align 16

InterruptHandlerEnd equ $
InterruptHandlerStart    dq CpuSupportInterruptHandlerStart
InterruptHandlerSize     dq InterruptHandlerEnd - CpuSupportInterruptHandlerStart
InterruptHandlerTblFixup dd InterruptPtrTableAddrFixup - CpuSupportInterruptHandlerStart

DATA_SEL EQU 8
CODE_SEL EQU 10h

;public MpStart
;public MpRestart
public JmpToMpStart
public JmpAddress
public JmpToMpStartSize

CPU_INFO_INIT STRUCT
	Id			dd ?
	CpuNum			dd ?
CPU_INFO_INIT ENDS

CPU_CONTROL STRUCT 8
	Function		dq ?		;If not zero, CPU thread is executing this function.
	Context			dq ?		;Cpu context.
	Stack			dq ?		;Initial stack address of AP during init. The actual stack pointer can change.
	Id			dd ?		;Apic Id
	Halted			db ?		;Signal to halt CPU.
CPU_CONTROL	ENDS

ZERO_DATA   STRUCT
    Gdt             dq  ?
    GdtPadding      dd  ?       ; GDT64 takes 10 bytes
    NumAps          dd  ?
    ApGlobalData    dq  ?       ; make ApGlobalData 64 bit wide
    PageTable       dd  ?
    TOM             dd  ?
    EnteredHoldLoop dd  ?
    EightByteAlign  dd  ?
ZERO_DATA	ENDS

OFFS_NUMAPS EQU SIZEOF ZERO_DATA.Gdt + SIZEOF ZERO_DATA.GdtPadding
OFFS_PTABLE EQU OFFS_NUMAPS + SIZEOF ZERO_DATA.NumAps + SIZEOF ZERO_DATA.ApGlobalData

AP_GLOBAL_DATA_STRUCT	STRUCT
	CpuControl		dq ?		;Pointer to CPU_CONTROL structures.
	HaltLoopEntry		dq ?		;If runtime halt loop, jump here to halt.
	ReleaseCpu		dq ?		;Release CPU
	Idt             	dd ?            ;Interrupt table pointer
	CpuSync			db ?		;Count CPU for sync during init.
	BSP			db ?		;BSP number. Initially 0.
	NumCpu			db ?		;Number of CPUs including BSP.
	RunningAps		db ?		;AP thread executing count.
	HaltedCpus		db ?		;Count of all halted CPUs.
AP_GLOBAL_DATA_STRUCT	ENDS

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	_MpStart
;
; Description:	This routine is called by all APs. It is the holding loop
;	for APs to control threads.
;
; Input:	None	
;
; Output:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
MpStart proc
	mov		ax, DATA_SEL
	mov		ds, ax
	mov		es, ax
	mov		ss, ax
	mov		fs, ax
	mov		gs, ax

	cld
    xor     rbx, rbx
	xor		rdx, rdx
;	mov		ebx, ds:[12+MKF_MP_ZERO_DATA_ADDRESS]	;Get AP_GLOBAL_DATA_STRUCT
;Agd64	mov		ebx, (ZERO_DATA ptr [rdx]).ApGlobalData
	mov		rbx, (ZERO_DATA ptr [rdx]).ApGlobalData

    mov   eax, MKF_APIC_BASE + MKF_APIC_ID_REGISTER
    mov   edi, [eax]
    shr   edi, 24
IF MKF_USE_AP_HLT
        mov   rcx, 0
        mov   ecx, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).Idt
        lidt  fword ptr [rcx]
ENDIF
    ;Hold CPUS until ready.
        xor   rsi, rsi
;       lock inc DWORD ptr ds:[24+MKF_MP_ZERO_DATA_ADDRESS]
        lock inc DWORD ptr (ZERO_DATA ptr [rdx]).EnteredHoldLoop
    
HOLD_CPU:
	pause
	xchg rsi, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).ReleaseCpu
	or	rsi, rsi			;ecx = CPU_INFO_INIT
	jz	HOLD_CPU

	mov (CPU_INFO_INIT ptr [rsi]).Id, edi

	lock dec (AP_GLOBAL_DATA_STRUCT ptr [rbx]).CpuSync

HOLD_CPU2:
	pause
	mov ecx, (CPU_INFO_INIT ptr [rsi]).CpuNum
	cmp	ecx, 0ffffffffh
	je HOLD_CPU2

	;Note here: cl = CPU number.
    xor     rsi, rsi
	mov	    esi, ecx				;ecx = esi = CPU Count
	mov		rax, sizeof CPU_CONTROL
	mul		esi						;eax = sizeof CPU_CONTROL * CPU Number, edx = 0
	mov		rsi, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).CpuControl
	add		rsi, rax				;esi = address of CpuControl for CPU.
	mov		rsp, (CPU_CONTROL ptr [rsi]).Stack
	mov		(CPU_CONTROL ptr [rsi]).Id, edi

	;Let BSP know CPU number was received.
	lock dec (AP_GLOBAL_DATA_STRUCT ptr [rbx]).CpuSync

MP_COMMON_ENTRY::
	;Initialize CPUS
;	finit			;Initialize FPU on BSP

	mov	rax, cr4
	or  ax, 1 SHL 9 + 1 SHL 10
	mov	cr4, rax		;In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10

;---Holding loop for CPU threads---
HOLD_CPU3:
        pause
        cmp   (CPU_CONTROL ptr [rsi]).Halted, 0
        jne   Halt_Cpu

    ;Number of Running CPUs set before CPU is released here.
        cmp   (CPU_CONTROL ptr [rsi]).Function, 0
IF NOT MKF_USE_AP_HLT
        je    HOLD_CPU3
ELSE	
        jne   Funcexec
        hlt
        jmp   HOLD_CPU3

Funcexec:
ENDIF
        push  rbx
        push  rsi
        push  rcx
        push  rdx
        sub   rsp, 32

    	;rcx =CPU count
    	mov  rdx, (CPU_CONTROL ptr [rsi]).Context

	;Call   PE32 function
	call	(CPU_CONTROL ptr [rsi]).Function

        add   rsp, 32
        pop   rdx
        pop   rcx
        pop   rsi
        pop   rbx

        cmp   (CPU_CONTROL ptr [rsi]).Function, -1          ;Check if BSP change
        jne   @f
    ;--Switch BSP here--
        xchg  (AP_GLOBAL_DATA_STRUCT ptr [rbx]).BSP,cl      ;ecx = new AP, set new BSP
    ;Get address of CpuControl for CPU.
        mov   rsi, rcx
        mov   rax, sizeof CPU_CONTROL
        mul   rsi           ;rax = sizeof CPU_CONTROL * CPU Number, rdx = 0
        mov   rsi, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).CpuControl
        add   rsi, rax      ;rsi = address of CpuControl for CPU.
@@:
        mov   (CPU_CONTROL ptr [rsi]).Function, 0

    ;Sync CPUs
        lock  dec (AP_GLOBAL_DATA_STRUCT ptr [rbx]).RunningAps  ;Num of Cpus in wait loop.

        jmp   HOLD_CPU3
;---Cpus that are halted come here.---
Halt_Cpu:
	lock	inc (AP_GLOBAL_DATA_STRUCT ptr [rbx]).HaltedCpus

	;If Halt loop in ram, jump to it.
	cmp	(AP_GLOBAL_DATA_STRUCT ptr [rbx]).HaltLoopEntry, 0
	je	@f
	jmp	(AP_GLOBAL_DATA_STRUCT ptr [rbx]).HaltLoopEntry
@@:
	cli
	hlt
	jmp @b
MpStart endp

MpRestart proc
	mov		ax, DATA_SEL
	mov		ds, ax
	mov		es, ax
	mov		ss, ax
	mov		fs, ax
	mov		gs, ax

	cld
    xor     rbx, rbx

	xor		rdx, rdx
    lock inc DWORD ptr (ZERO_DATA ptr [rdx]).NumAps
;	mov		ebx, ds:[12+MKF_MP_ZERO_DATA_ADDRESS]	;Get AP_GLOBAL_DATA_STRUCT
;Agd64	mov		ebx, (ZERO_DATA ptr [rdx]).ApGlobalData
	mov		rbx, (ZERO_DATA ptr [rdx]).ApGlobalData
    ; retrive the IDT table, the AP's IDTR will be erased after waking up by SIPI
    ; the IDT table pointer is saved in StartAllAps of CpuMp.c
    mov     rcx, 0
    mov     ecx, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).Idt
    lidt    fword ptr [rcx]

	mov rcx, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).ReleaseCpu
	;Note here: cl = CPU number.
	mov		esi, ecx				;ecx = esi = CPU Count
	mov		eax, sizeof CPU_CONTROL
	mul		esi						;eax = sizeof CPU_CONTROL * CPU Number, edx = 0
	mov		rsi, (AP_GLOBAL_DATA_STRUCT ptr [rbx]).CpuControl
	add		esi, eax				;esi = address of CpuControl for CPU.
	mov		rsp, (CPU_CONTROL ptr [rsi]).Stack

	mov		(CPU_CONTROL ptr [rsi]).Function, 0
	cmp		(CPU_CONTROL ptr [rsi]).Halted, 0
	jz		@f
	mov		(CPU_CONTROL ptr [rsi]).Halted, 0
	dec		(AP_GLOBAL_DATA_STRUCT ptr [rbx]).HaltedCpus
@@:
    lock inc DWORD ptr (ZERO_DATA ptr [rdx]).EnteredHoldLoop
	jmp		MP_COMMON_ENTRY
MpRestart endp


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	_JmpToMpStart
;
; Description:	This routine is the SIPI AP entry point. It counts CPUs and
;	switches to protected mode and gives control to MpStart. This routine will
;	be copied below 1MB.
;
; Input:	None	
;
; Output:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
JmpToMpStart proc
        ;***NOTE***
        ;***NOTE***
        ;***NOTE***
        ;---16 bit in 32 bit assembler--
        ;---Some 16-bit and 32-bit assembly is the same, others are not.---
        ;---Need to use some machine code.---

    ;---------------------------------------------------------------
    ; (*ZERO_DATA)->NumAps++ (Count APs)
    ;---------------------------------------------------------------
	;lock inc byte ptr [(ZERO_DATA).NumAps + MKF_MP_ZERO_DATA_ADDRESS]	;Count CPU
		db 0f0h, 0feh, 6
		dw OFFS_NUMAPS + MKF_MP_ZERO_DATA_ADDRESS

    ;---------------------------------------------------------------
	;Switch to protected mode
    ;---------------------------------------------------------------
	;lgdt	fword ptr [ ]
		db	66h,0fh,1,16h
		dw	SIZEOF ZERO_DATA

	mov		rax, cr0        ;===>actualy mov eax, cr0
	or      al, 1			;Set PE bit
	mov		cr0, rax      	;===>actualy mov cr0, eax

    ;---------------------------------------------------------------
	; In 16 bit protected mode, hack retf to initialize CS by
    ; first pushing the new CS and then pushing/modifying
    ; the EIP so that retf returns @ In_prot_mode.
    ;---------------------------------------------------------------
    ;;jmp $
    ;db 0ebh, 0feh

    ;In 16 bit protected mode
    ;jmp  10h:In_prot_mode 
        db      66h, 0EAh
        dw      ((In_prot_mode - JmpToMpStart) + MKF_MP_JUMP_FUNCTION_ADDRESS)
        dw      00h
        dw      CODE_SEL
In_prot_mode: 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ;mov eax, [16+MKF_MP_ZERO_DATA_ADDRESS]  ;PageTable
        db 8bh, 5
        dd OFFS_PTABLE

	mov cr3, rax		;Set CR3 to first page directory pointer table

	mov rax, cr4        ;actually eax
	or al, 020h			;Enable PAE
	mov cr4, rax

	;Enable long mode in msr register. Doesn't actually enter long mode yet.
	mov ecx, 0c0000080h
	rdmsr
	bts eax, 8	
	wrmsr

	;Enable paging
	mov rax, cr0        ;actually eax
	bts	eax, 31
        mov   cr0, rax        ;Now in long mode compatibility.
	jmp	@f
@@:

    db      0EAh
    dd      ((In_long_mode - JmpToMpStart) + MKF_MP_JUMP_FUNCTION_ADDRESS)
    dw      38h                 ; 64 bit code selector
In_long_mode:
    mov     eax, MKF_MP_ZERO_DATA_ADDRESS
    lgdt    fword ptr[eax]
    ;jmp    &_MpStart	
    db      48h
    lea     eax, JmpAddress
    jmp     qword ptr[rax]
;#      db  0eah
JmpAddress  dd  ?
JAddr1      dd  0
;       dw  38h
JmpToMpStart endp
JmpToMpStartEnd		equ $
JmpToMpStartSize	dq offset JmpToMpStartEnd - JmpToMpStart

SWITCH_CONTEXT struct
	Stack		dq ?
	pStack2		dq ?	;Pointer to Stack on other SwitchContext
	pApFunction	dq ?	;Pointer to CPU_CONTROL Function of new BSP.
SWITCH_CONTEXT ends

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	CpuSwitchStacks
;
; Description:	This routine is actually switches to a new BSP by switching stacks.
;
; Input:	IN UINT8 CPU
;			IN VOID *Context	
;
; Output:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
CpuSwitchStacks proc public
    pushf
	mov	rax, (SWITCH_CONTEXT ptr [rdx]).pStack2
	mov	[rax], rsp		;Pass current stack to other CPU for new Stack

@@:
	pause
	mov	rsp, (SWITCH_CONTEXT ptr [rdx]).Stack	;Get new stack from other CPU
	or	rsp, rsp
	jz	@b				;Is new stack address available.

    popf
	mov rax, (SWITCH_CONTEXT ptr [rdx]).pApFunction
	mov	qword ptr [rax], -1	;Set Function of new BSP to -1.
	ret
CpuSwitchStacks endp


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SwitchBspProgramReg
;
; Description:  This routine is called to change the APIC BAR(Msr 0000001B).
;
; Input:
;   IN rdx        Context
;   IN rcx        Cpu count
;
; Output:       None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
;Use Assembly to guarentee register/stack usage for call to switch stacks.
SwitchBspProgramReg proc public
        push  rdx
        push  rcx
        push  rbx
        push  rax
        push  rsi
        cmp   rdx, rcx
        jne   SetApIndicator
        mov   ecx, 1bh
        rdmsr
        or      eax, 0100h  ;Set BSP indicator
        wrmsr
        ;First, Set APICF0 Spurious-Interrupt Vector (SVR)
        ;The APICSWEn(APIC software enable) should be set
        ;so that 350/360 can be set.
        mov   esi, MKF_LOCAL_APIC_BASE + MKF_APIC_SPURIOUS_VECTOR_REGISTER
        mov   eax, [esi]
        or    eax, 0100h
        mov   [esi], eax  
        ;Set this processor's LVT LINIT[1:0]
        ;Set 350 LINT0
        mov   esi, MKF_LOCAL_APIC_BASE + MKF_APIC_LVT_LINT0_REGISTER
        mov   eax, [esi]
        and   eax, 0FFFE58FFh
        mov   [esi], eax      ; clear Mask bit
        or    eax, 00000700h
        mov   [esi], eax      ; then set message type
        ;Set 360 LINT1
        mov   esi, MKF_LOCAL_APIC_BASE + MKF_APIC_LVT_LINT1_REGISTER
        mov   eax, [esi]
        and   eax, 0FFFE58FFh
        mov   [esi], eax      ; clear Mask bit
        or    eax, 00000400h
        mov   [esi], eax      ; then set message type
        jmp SetDone
SetApIndicator:
        mov   ecx, 1bh
        rdmsr
        and   eax, 0FFFFFEFFh ;Set Ap indicator
        wrmsr
        ;Mask this processor's LVT LINT[1:0]
        ;Mask 350 LINT1
        mov   esi, MKF_LOCAL_APIC_BASE + MKF_APIC_LVT_LINT0_REGISTER
        mov   eax, [esi]
        and   eax, 0FFFE58FFh
        or    eax, 00010000h
        mov   [esi], eax
        ;Mask this processor's LVT LINT[1:0]
        ;Mask 360 LINT1
        mov   esi, MKF_LOCAL_APIC_BASE + MKF_APIC_LVT_LINT1_REGISTER
        mov   eax, [esi]
        and   eax, 0FFFE58FFh
        or    eax, 00010000h
        mov   [esi], eax
SetDone:
        pop   rsi
        pop   rax
        pop   rbx
        pop   rcx
        pop   rdx
    ret
SwitchBspProgramReg endp

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SwitchBsp
;
; Description:  This routine is called to switch to a new BSP.
;
; Input:
;   IN VOID         *MpData
;   IN UINT8        *NewBsp
;   IN VOID (*Function)(UINT8 Cpu, VOID *Context) OPTIONAL
;   IN VOID *Context        OPTIONAL
;
; Output:       None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
;Use Assembly to guarantee register/stack usage for call to switch stacks.

SwitchBsp proc

;MpData = rcx
;NewBsp = dl
;Function = r8
;Context = r9

        push    rbx
        push    rsi
        push    rdi
        push    rbp
        push    r15
        push    r14
        push    r13
        push    r12
        push    r11
        push    r10
        push    r9
        push    r8

        mov     rbp, rsp
        sub     rsp, size SWITCH_CONTEXT * 2
        ContextOldBsp EQU (SWITCH_CONTEXT ptr [rbp - size SWITCH_CONTEXT])
        ContextNewBsp EQU (SWITCH_CONTEXT ptr [rbp - size SWITCH_CONTEXT * 2])

;---Validate Inputs---
        cmp     dl, (AP_GLOBAL_DATA_STRUCT ptr [rcx]).NumCpu
        jae     SwitchBspExit           ; Check if CPU exists

        xor     ebx, ebx
        mov     bl, (AP_GLOBAL_DATA_STRUCT ptr [rcx]).BSP
        cmp     dl, bl
        je      SwitchBspExit           ; Check if already BSP

;---Init SWITCH_CONTEXT---
        ;The switch is made by exchange stacks.
        lea     rsi, ContextOldBsp.Stack
        lea     rdi, ContextNewBsp.Stack

        xor     rax, rax
        mov     ContextOldBsp.Stack, rax ; This will be updated by new BSP
        mov     ContextOldBsp.pStack2, rdi ; Points to new BSP so old BSP can update it.
        mov     ContextNewBsp.Stack, rax ; This will be updated by old BSP
        mov     ContextNewBsp.pStack2, rsi ; Points to old BSP so new BSP can update it.

;---Get AP Cpu Control Structure---
        mov     rsi, (AP_GLOBAL_DATA_STRUCT ptr [rcx]).CpuControl
        mov     rdi, rsi

        mov     eax, sizeof CPU_CONTROL
        push    rdx
        mul     dl                      ; This changes dx
        pop     rdx
        add     esi, eax                ; rsi = New Bsp AP_CPU_CONTROL

        lea     rax, (CPU_CONTROL ptr [rsi]).Function
        mov     ContextOldBsp.pApFunction, rax
        mov     ContextNewBsp.pApFunction, rax

;---Validate if not halted. ---
        cmp     (CPU_CONTROL ptr [rsi]).Halted, 0
        jne     SwitchBspExit           ; Can't switch if halted.

;---Get this CPU Control Structure--
        movzx   ebx,  (AP_GLOBAL_DATA_STRUCT ptr [rcx]).BSP
        mov     eax, sizeof CPU_CONTROL
        push    rdx
        mul     bl                      ; This changes dx
        pop     rdx
        add     edi, eax                ; rdi = Old Bsp AP_CPU_CONTROL
;---Switch addresses in control structure---
        mov     rax,  (CPU_CONTROL ptr [rsi]).Stack
        xchg    rax, (CPU_CONTROL ptr [rdi]).Stack
        mov     (CPU_CONTROL ptr [rsi]).Stack, rax

;---Wait until New BSP is idle. ---
@@:
        pause
        cmp     (AP_GLOBAL_DATA_STRUCT ptr [rcx]).RunningAps, 0
        ja      @b

;---Call Function if exists---
        or      r8, r8
        jz      NoFunction

    ;Call function on New Bsp
        lock  inc (AP_GLOBAL_DATA_STRUCT ptr [rcx]).RunningAps
        mov   (CPU_CONTROL ptr [rsi]).Context, r9
        mov   (CPU_CONTROL ptr [rsi]).Function, r8 ; This releases the New Bsp
IF MKF_USE_AP_HLT
        mov   eax, (CPU_CONTROL ptr [rsi]).Id
        shl   eax, 24
        push  rbx
        mov   rbx, MKF_LOCAL_APIC_BASE + MKF_APIC_ICR_HIGH_REGISTER
        mov   DWORD PTR[rbx], eax
        mov   bx, MKF_APIC_ICR_LOW_REGISTER
        mov   DWORD PTR[rbx], 400h
        pop   rbx
ENDIF

    ;Call function on Current BSP
    ;Save volatile registers
        push    rbx 
        push    rcx
        push    rdx
        mov     rdx, r9
        mov     rcx, rbx                ; rcx = CPU Count
    ;rbx is setup for AP holding loop. This CPU will not return.

        call    r8

        pop     rdx
        pop     rcx
        pop     rbx
    ;Wait until Idle
@@:
        pause
        cmp     (AP_GLOBAL_DATA_STRUCT ptr [rcx]).RunningAps, 0
        ja      @b

NoFunction:
;----------- Switch the Stacks. -------------------------------
        lea   rax, ContextNewBsp
        lock  inc (AP_GLOBAL_DATA_STRUCT ptr [rcx]).RunningAps
        mov   (CPU_CONTROL ptr [rsi]).Context, rax
        mov   rax, CpuSwitchStacks
        mov   (CPU_CONTROL ptr [rsi]).Function, rax ;Execute on new bsp
IF MKF_USE_AP_HLT
        mov   eax, (CPU_CONTROL ptr [rsi]).Id
        shl   eax, 24
        push  rbx
        mov   rbx, MKF_LOCAL_APIC_BASE + MKF_APIC_ICR_HIGH_REGISTER
        mov   DWORD PTR[rbx], eax
        mov   bx, MKF_APIC_ICR_LOW_REGISTER
        mov   DWORD PTR[rbx], 400h
        pop   rbx
ENDIF 
        push  rbx
        push  rcx
        push  rdx
        push  rbp                     ; AP taking over doesn't have rbp. 
                                        ; Get from stack after routine.

        xchg    rcx, rbx
        lea     rdx, ContextOldBsp
        call    CpuSwitchStacks

        pop     rbp
        pop     rdx
        pop     rcx
        pop     rbx
    ;---Now new BSP is executing with old BSP stack.---

;---Wait until the CPU APs exit.---
@@:
        pause
        cmp     (AP_GLOBAL_DATA_STRUCT ptr [rcx]).RunningAps, 0
        ja      @b

;---Finish setting up new BSP.---
SwitchBspExit:
        mov    rsp, rbp
	    pop     r8
	    pop     r9
	    pop     r10
	    pop     r11
	    pop     r12
	    pop     r13
	    pop     r14
	    pop     r15
        pop    rbp
        pop    rdi
        pop    rsi
        pop    rbx
        ret
SwitchBsp endp

END

;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************
