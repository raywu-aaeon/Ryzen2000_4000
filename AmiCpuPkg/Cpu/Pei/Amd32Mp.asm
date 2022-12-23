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
; Name:         Amd32Mp.asm
;
; Description:	CPU MP and interrupt specific code
;
;---------------------------------------------------------------------------
;<AMI_FHDR_END>

.686p
.xmm
.model  flat
.code

include token.equ
include cpu\include\cpu.equ

public _InterruptHandlerStart
public _InterruptHandlerSize
public _InterruptHandlerTblFixup

EFI_FX_SAVE_STATE_IA32 STRUCT
    Fcw         dw ?
    Fsw         dw ?
    Ftw         dw ?
    Opcode      dw ?
    RegEip      dd ?
    RegCs       dw ?
    Rsv1        dw ?
    DataOffset  dd ?
    RegDs       dw ?
    Rsv2        db 10 dup (?)
    St0Mm0      db 10 dup (?)
    Rsv3        db 6  dup (?)
    St1Mm1      db 10 dup (?)
    Rsv4        db 6  dup (?)
    St2Mm2      db 10 dup (?)
    Rsv5        db 6  dup (?)
    St3Mm3      db 10 dup (?)
    Rsv6        db 6  dup (?)
    St4Mm4      db 10 dup (?)
    Rsv7        db 6  dup (?)
    St5Mm5      db 10 dup (?)
    Rsv8        db 6  dup (?)
    St6Mm6      db 10 dup (?)
    Rsv9        db 6  dup (?)
    St7Mm7      db 10 dup (?)
    Rsv10       db 6  dup (?)
    RegXmm0     db 16 dup (?)
    RegXmm1     db 16 dup (?)
    RegXmm2     db 16 dup (?)
    RegXmm3     db 16 dup (?)
    RegXmm4     db 16 dup (?)
    RegXmm5     db 16 dup (?)
    RegXmm6     db 16 dup (?)
    RegXmm7     db 16 dup (?)
    Rsv11       db 224 dup (?)
EFI_FX_SAVE_STATE_IA32 ENDS

;Only #if (EFI_SPECIFICATION_VERSION >= 0x00020000)


EFI_SYSTEM_CONTEXT_IA32 STRUCT
        ExceptionData dd ?
  		FxSaveState EFI_FX_SAVE_STATE_IA32 <>
        RegDr0      dd ?
        RegDr1      dd ?
        RegDr2      dd ?
        RegDr3      dd ?
        RegDr6      dd ?
        RegDr7      dd ?
        RegCr0      dd ?
        RegCr1      dd ?     ;Reserved
        RegCr2      dd ?
        RegCr3      dd ?
        RegCr4      dd ?
        RegEflags   dd ?
        RegLdtr     dd ?
        RegTr       dd ?
        RegGdtr     dd ?, ?
        RegIdtr     dd ?, ?
        RegEip      dd ?
        RegGs       dd ?
        RegFs       dd ?
        RegEs       dd ?
        RegDs       dd ?
        RegCs       dd ?
        RegSs       dd ?
        RegEdi      dd ?
        RegEsi      dd ?
        RegEbp      dd ?
        RegEsp      dd ?
        RegEbx      dd ?
        RegEdx      dd ?
        RegEcx      dd ?
        RegEax      dd ?
EFI_SYSTEM_CONTEXT_IA32 ENDS


INT_DATA_NO_EX STRUCT
    Retoffs     dd ?
    RetSeg      dd ?
    Flags       dd ?
INT_DATA_NO_EX ENDS

INT_DATA_EX STRUCT
    ErrorCode   dd ?
    Retoffs     dd ?
    RetSeg      dd ?
    Flags       dd ?
INT_DATA_EX ENDS

INT_DATA UNION
    NoEx    INT_DATA_NO_EX <>
    Ex      INT_DATA_EX <>
INT_DATA ENDS


INT_HDL_ENTRY_STACK STRUCT
    RegEdi      dd ?
    Handler     dd ?
    RegEax      dd ?
    Exception   dd ?
    IntData INT_DATA <>
INT_HDL_ENTRY_STACK ENDS

InterruptHandlerStart equ $
;**********************************************************************
;<AMI_PHDR_START>
;
; Procedure:	EfiCpuEnableInterrupt
;
; Description:	Enable CPU Interrupts.
;
; Input:
;      eax interrupt number
;
; Output:
;      None
;
; Modified:
;
; Referrals:
;
; Notes:
;  Here is the control flow of this function:
;  Note: System Context is a NULL pointer. It is not used.
;  1. Disable interrupts.
;  2. Save processor registers that may change.
;  3. If interrupt handler routine installed, call interrupt handler routine.
;  4. Restore registers from stack.
;  5. Return from interrupt.
;
;<AMI_PHDR_END>
;**********************************************************************
CommonEntry:
        cli
        mov    eax, [esp + 4]           ;Interrupt number.
        shl    eax, 2
        
        ;add    eax, InterruptPtrTable
                db      05
InterruptPtrTableAddrFixup      EQU $
                dd      0
        cmp     dword ptr [eax], 00h    ;Zero if no int handler installed.
        je      NoIntHandler
        push    dword ptr [eax]         ;push handler        
        push    edi                     ;Must manually update edi since it is being destoryed.
        mov     edi, esp

        ;esp is aligned for fxsave below.
        and     esp, 0fffffff0h         ;Align to 16-byte boundary.
        sub     esp, 0ch                ;Set end byte to 4, so fxsave in structure will be alligned on 16 byte boundary.

        ;The registers are stored on stack to match EFI_SYSTEM_CONTEXT_IA32
        ;esp, eax will be updated later to correct values
        pushad
        xor     eax, eax
        mov     ax, ss
        push    eax
        mov     ax, cs
        push    eax
        mov     ax, ds
        push    eax
        mov     ax, es
        push    eax
        mov     ax, fs
        push    eax
        mov     ax, gs
        push    eax
        sub     esp, 32 ;EIP, idtr, gdtr, etc. updated later
        mov     eax, cr4
        push    eax        
        mov     eax, cr3
        push    eax
        mov     eax, cr2
        push    eax
        pushd   0       ;reserved
        mov     eax, cr0
        push    eax
        mov     eax, dr7
        push    eax
        mov     eax, dr6
        push    eax
        mov     eax, dr3
        push    eax
        mov     eax, dr2
        push    eax
        mov     eax, dr1
        push    eax
        mov     eax, dr0
        push    eax

        sub     esp, size EFI_FX_SAVE_STATE_IA32
        fxsave  [esp]

        push    eax         ;Exception data added later. Dummy push.

        mov     ebp, esp    ;ebp = EFI_SYSTEM_CONTEXT_X64

        xor     eax, eax
        str     ax
        mov     (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegTr, eax

        sgdt    (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegGdtr
        mov     ebx, (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp + 2]).RegGdtr
        mov     eax, [ebx + 8 * eax]
        mov     (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegLdtr, eax

        sidt    (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegIdtr

        mov     eax, (INT_HDL_ENTRY_STACK ptr [edi]).RegEax
        mov     (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEax, eax

        mov     eax, (INT_HDL_ENTRY_STACK ptr [edi]).RegEdi
        mov     (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEdi, eax

        ;Some Exceptions have a exception code. Others don't.
        ;INT_HDL_ENTRY_STACK is the structure on stack above EFI_SYSTEM_CONTEXT_IA32.
        ;This contains the original eip, exception code, and other saved registers.
        mov     eax, (INT_HDL_ENTRY_STACK ptr [edi]).Exception
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
        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.Ex.ErrorCode
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).ExceptionData, eax

        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.Ex.Flags
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEflags, eax

        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.Ex.Retoffs
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEip, eax

        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.Ex.RetSeg
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegCs, eax

        xor   eax, eax
        mov   ax, ss
        mov   (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegSs, eax

        lea   eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.Ex.Flags + 4
        mov   (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEsp, eax

        jmp     gotointerrupt

noerrcode:
        xor eax, eax
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).ExceptionData, eax

        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.NoEx.Flags
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEflags, eax

        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.NoEx.Retoffs
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEip, eax

        mov eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.NoEx.RetSeg
        mov (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegCs, eax

        xor   eax, eax
        mov   ax, ss
        mov   (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegSs, eax

        lea   eax, (INT_HDL_ENTRY_STACK ptr [edi]).IntData.NoEx.Flags + 4
        mov   (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEsp, eax

        
gotointerrupt:        
        mov     ebx, (INT_HDL_ENTRY_STACK ptr [edi]).Exception
        mov     eax, (INT_HDL_ENTRY_STACK ptr [edi]).Handler
        
        cld
        
        mov     esi, ebp                ;currently esp = ebp
        mov     ebp, esp
        and     esp, 0FFFFFFF0h         ;guarantee 16-byte stack alignment
        

        ;Call the interrupt handler which has this C function.
        ;VOID (*EFI_CPU_INTERRUPT_HANDLER) (
        ;     IN EFI_EXCEPTION_TYPE   InterruptType,
        ;     IN EFI_SYSTEM_CONTEXT   SystemContext)
        
        ;These registers are saved/restored by the function: ESI, EDI, EBX, and EBP

        push    esi              ;SystemContext
        push    ebx              ;InterruptType
        call    eax
        mov     esp, ebp

        mov     (EFI_SYSTEM_CONTEXT_IA32 ptr [ebp]).RegEdi, edi     ;Must restore before popad

        fxrstor (EFI_SYSTEM_CONTEXT_IA32 ptr [esp]).FxSaveState

        ;Remove data to on stack to discard.
        add     esp, size EFI_SYSTEM_CONTEXT_IA32 - 32

        ;Restore the original registers.
        popad
        mov     esp, edi    ;stack is updated with actual edi before popad.
        pop     edi
        add     esp, 4      ;remove handler
NoIntHandler:
        pop     eax
        add     esp, 4      ;remove exception
        iretd               ;flags are restored on iretd
InterruptHandlerEnd equ $
_InterruptHandlerStart	dd offset InterruptHandlerStart
_InterruptHandlerSize	dd offset InterruptHandlerEnd - offset InterruptHandlerStart
_InterruptHandlerTblFixup dd InterruptPtrTableAddrFixup - InterruptHandlerStart

DATA_SEL EQU 8
CODE_SEL EQU 10h

public _MpStart
public _MpRestart
public _JmpToMpStart
public _JmpAddress
public _JmpToMpStartSize

CPU_INFO_INIT STRUCT
	Id				dd ?
	CpuNum			dd ?
CPU_INFO_INIT ENDS

CPU_CONTROL STRUCT 4
	Function		dd ?		;If not zero, CPU thread is executing this function.
	Context			dd ?		;Cpu context.
	Stack			dd ?		;Initial stack address of AP during init. The actual stack pointer can change.
	Id				dd ?		;Apic Id
	Halted			db ?		;Signal to halt CPU.
CPU_CONTROL	ENDS

ZERO_DATA   STRUCT
    Gdt             dq  ?
    GdtPadding      dd  ?       ; GDT64 takes 10 bytes
    NumAps          dd  ?
    ApGlobalData    dd  ?
    ApGlobalData64  dd  ?       ; Agd64bit
    PageTable       dd  ?
    TOM             dd  ?
    EnteredHoldLoop dd  ?
ZERO_DATA   ENDS

AP_GLOBAL_DATA_STRUCT	STRUCT
	CpuControl		dd ?		;Pointer to CPU_CONTROL structures.
	HaltLoopEntry	dd ?		;If runtime halt loop, jump here to halt.
	ReleaseCpu		dd ?		;Release CPU
    Idt             dd ?        ;Idt table pointer
	CpuSync			db ?		;Count CPU for sync during init.
	BSP				db ?		;BSP number. Initially 0.
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
;	            for APs to control threads.
;
; Input:	None	
;
; Output:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
_MpStart proc
	mov		ax, DATA_SEL
	mov		ds, ax
	mov		es, ax
	mov		ss, ax
	mov		fs, ax
	mov		gs, ax

	cld

	xor		edx, edx
;	mov		ebx, ds:[12+MKF_MP_ZERO_DATA_ADDRESS]	;Get AP_GLOBAL_DATA_STRUCT
	mov		ebx, ds:(ZERO_DATA ptr [edx]).ApGlobalData

	mov		edi, ds:[MKF_APIC_BASE + MKF_APIC_ID_REGISTER]
	shr		edi, 24

;;Set TOM for Aps
;;This is needed for some Stack Adjustment when the APs are initialized first time
;;If the below code is not applied, the system will behave undetermined, when AP TOM and
;;BSP TOM are not same....This part only applicable for AMD32Mp.asm and not AMD64mp.asm,
;;as the later file used only for DXE Phase.
	mov		ecx, 0C001001Ah
	rdmsr
;	cmp		eax, ds:[20+MKF_MP_ZERO_DATA_ADDRESS]
	cmp		eax, ds:(ZERO_DATA ptr [edx]).TOM
	je		No_TOM_Change
;	mov		eax, ds:[20+MKF_MP_ZERO_DATA_ADDRESS]
	mov		eax, ds:(ZERO_DATA ptr [edx]).TOM
	xor		edx, edx
	wrmsr
No_TOM_Change:
	;Hold CPUS until ready.
	xor	esi, esi

;	lock inc DWORD ptr ds:[24+MKF_MP_ZERO_DATA_ADDRESS]
	lock inc DWORD ptr ds:(ZERO_DATA ptr [edx]).EnteredHoldLoop
HOLD_CPU:
	pause
	xchg esi, ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).ReleaseCpu
	or	esi, esi			;esi = Cpu Info Init structure
	jz	HOLD_CPU

	mov ds:(CPU_INFO_INIT ptr [esi]).Id, edi

	lock dec ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).CpuSync

HOLD_CPU2:
	pause
	mov ecx, ds:(CPU_INFO_INIT ptr [esi]).CpuNum
	cmp	ecx, 0ffffffffh
	je HOLD_CPU2

	;Let BSP know CPU number was received.
	lock dec ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).CpuSync

	;Note here: cl = CPU number.
	mov		esi, ecx				;ecx = esi = CPU Count
	mov		eax, sizeof CPU_CONTROL
	mul		esi						;eax = sizeof CPU_CONTROL * CPU Number, edx = 0
	mov		esi, ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).CpuControl
	add		esi, eax				;esi = address of CpuControl for CPU.
	mov		esp, ds:(CPU_CONTROL ptr [esi]).Stack
	mov		ds:(CPU_CONTROL ptr [esi]).Id, edi

MP_COMMON_ENTRY::
	;Initialize CPUS
	finit			;Initialize FPU on BSP

    ; Disable support for FXSAVE/FXRSTOR instruction and
    ; Disable SIMD floating-point exceptions
	mov	eax, cr4
	or  ax, 1 SHL 9 + 1 SHL 10
	mov	cr4, eax		;In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10

;---Holding loop for CPU threads---
HOLD_CPU3:
	pause
	cmp	ds:(CPU_CONTROL ptr [esi]).Halted, 1
	je	Halt_Cpu
	
	;Number of Running CPUs set before CPU is released here.
	cmp	ds:(CPU_CONTROL ptr [esi]).Function, 0
	je	HOLD_CPU3

	push	ecx
	push	ebx
	push	esi

	push	ds:(CPU_CONTROL ptr [esi]).Context
	push	ecx			;CPU count
	;Call   PE32 function
	call	ds:(CPU_CONTROL ptr [esi]).Function
	add		esp, 8

	pop		esi
	pop		ebx
	pop		ecx

	cmp		ds:(CPU_CONTROL ptr [esi]).Function, -1				;Check if BSP change
	jne		@f
	;--Switch BSP here--
	xchg	ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).BSP,cl		;ecx = new AP, set new BSP
	;Get address of CpuControl for CPU.
	mov		esi, ecx
	mov		eax, sizeof CPU_CONTROL
	mul		esi						;eax = sizeof CPU_CONTROL * CPU Number, edx = 0
	mov		esi, ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).CpuControl
	add		esi, eax				;esi = address of CpuControl for CPU.
@@:
	mov		ds:(CPU_CONTROL ptr [esi]).Function, 0

	;Sync CPUs
	lock dec ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).RunningAps	;Num of Cpus in wait loop.

	jmp	HOLD_CPU3
;---Cpus that are halted come here.---
Halt_Cpu:
	lock	inc ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).HaltedCpus

	;If Halt loop in ram, jump to it.
	cmp	ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).HaltLoopEntry, 0
	je	@f
	jmp	ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).HaltLoopEntry
@@:
	cli
	hlt
	jmp @b
_MpStart endp

_MpRestart proc
	mov		ax, DATA_SEL
	mov		ds, ax
	mov		es, ax
	mov		ss, ax
	mov		fs, ax
	mov		gs, ax

	cld
	xor		edx, edx
    lock inc DWORD ptr ds:(ZERO_DATA ptr [edx]).NumAps
;	mov		ebx, ds:[12+MKF_MP_ZERO_DATA_ADDRESS]	;Get AP_GLOBAL_DATA_STRUCT
	mov		ebx, ds:(ZERO_DATA ptr [edx]).ApGlobalData

	mov ecx, ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).ReleaseCpu
	;Note here: cl = CPU number.
	mov		esi, ecx				;ecx = esi = CPU Count
	mov		eax, sizeof CPU_CONTROL
	mul		esi						;eax = sizeof CPU_CONTROL * CPU Number, edx = 0
	mov		esi, ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).CpuControl
	add		esi, eax				;esi = address of CpuControl for CPU.
	mov		esp, ds:(CPU_CONTROL ptr [esi]).Stack

	mov		ds:(CPU_CONTROL ptr [esi]).Function, 0
	cmp		ds:(CPU_CONTROL ptr [esi]).Halted, 0
	jz		@f
	mov		ds:(CPU_CONTROL ptr [esi]).Halted, 0
	dec		ds:(AP_GLOBAL_DATA_STRUCT ptr [ebx]).HaltedCpus
@@:
    lock inc DWORD ptr ds:(ZERO_DATA ptr [edx]).EnteredHoldLoop
	jmp		MP_COMMON_ENTRY
_MpRestart endp


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	_JmpToMpStart
;
; Description:	This routine is the SIPI AP entry point. It counts CPUs and
;	            and gives control to MpStart or MpRestart. This routine will
;	            be copied below 1MB.
;
; Input:	None	
;
; Output:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

_JmpToMpStart proc

    ;---------------------------------------------------------------
    ; (*ZERO_DATA)->NumAps++ (Count APs)
    ;---------------------------------------------------------------
	;lock inc byte ptr ds:[0Ch]	;Count CPU
		db 0f0h, 0feh, 6
        dw 0Ch+MKF_MP_ZERO_DATA_ADDRESS

    ;---------------------------------------------------------------
	; Switch to protected mode
    ;---------------------------------------------------------------
	;lgdt	fword ptr [0]
		db	66h,0fh,1,16h
		dw	0
	mov		eax, cr0
	or      al, 1			;Set PE bit
	mov		cr0, eax      	;Turn on Protected Mode

        ; Set cs segment with a far jump
        ; jmp CODE_SEL:AP_P32MODE
        BYTE    66h, 0eah
        DWORD    JmpToMpStart_P32Mode-_JmpToMpStart+MKF_MP_JUMP_FUNCTION_ADDRESS
;        WORD    0ffffh
        WORD    CODE_SEL

JmpToMpStart_P32Mode::

; Disable cache
;;;; Commented - causing code corruption when PF enabled. 
;;;;	wbinvd
;;;;        mov     eax, CR0
;;;;        or      eax, 060000000h         ; Set the CD & NW bits
;;;;        mov     CR0, eax

; Enable MTRR & MSR
; Enable Fixed MTRR extensions
; Enable TOM and IORRs
        mov     ecx, MSR_SYS_CFG                        ; Get SYSCFG
        rdmsr
        bts     eax, MTRRFixDRAMModEnBit                ; Make RDMem and WRMem bits 
                                                        ; visible in Fixed MTRRs
        bts     eax, MTRRFixDRAMEnBit                   ; Enable Fixed MTRR extensions
        bts     eax, MTRRVarDRAMEnBit
        wrmsr

	;jmp	10:&_MpStart	
		db	0eah
_JmpAddress	dd ?
		dw	CODE_SEL
_JmpToMpStart endp
JmpToMpStartEnd		equ $
_JmpToMpStartSize	dd offset JmpToMpStartEnd - _JmpToMpStart


SWITCH_CONTEXT struct
	Stack		dd ?
	pStack2		dd ?	;Pointer to Stack on other SwitchContext
	pApFunction	dd ?	;Pointer to CPU_CONTROL Function of new BSP.
SWITCH_CONTEXT ends

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	_CpuSwitchStacks
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
_CpuSwitchStacks proc public
	mov	esi, [esp + 8]	;Context
	mov	eax, ds:(SWITCH_CONTEXT ptr [esi]).pStack2
	mov	[eax], esp		;Pass current stack to other CPU for new Stack

@@:
	pause
	mov	esp, ds:(SWITCH_CONTEXT ptr [esi]).Stack	;Get new stack from other CPU
	or	esp, esp
	jz	@b				;Is new stack address available.

	mov eax, ds:(SWITCH_CONTEXT ptr [esi]).pApFunction
	mov	dword ptr [eax], -1	;Set Function of new BSP to -1.
	ret
_CpuSwitchStacks endp


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:	SwitchBsp
;
; Description:	This routine is called to switch to a new BSP.
;
; Input:	IN VOID		*MpData
;			IN UINT8	*NewBsp	
;			IN VOID (*Function)(UINT8 Cpu, VOID *Context) OPTIONAL
;			IN VOID *Context	OPTIONAL
;
; Output:	None
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
;Use Assembly to guarentee register/stack usage for call to switch stacks.
SwitchBsp proc C MpData:DWORD, NewBsp:BYTE, Function:DWORD, Context:DWORD 
    local ContextOldBsp:SWITCH_CONTEXT, ContextNewBsp:SWITCH_CONTEXT
	pushad

	mov	edx, MpData
	movzx	ebx, NewBsp

;---Validate Inputs---
	cmp	bl, ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).NumCpu
	jae SwitchBspExit	;Check if CPU exists

	movzx	ecx, ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).BSP
	cmp	bl, cl
	je	SwitchBspExit	;Check if already BSP

;---Init SWITCH_CONTEXT---
	;The switch is made by exchange stacks.
	lea esi, ContextOldBsp.Stack
	lea edi, ds:ContextNewBsp.Stack

	mov ContextOldBsp.Stack, 0			;This will be updated by new BSP
	mov ContextOldBsp.pStack2, edi		;Points to new BSP so old BSP can update it.
	mov ContextNewBsp.Stack, 0			;This will be updated by old BSP
	mov ContextNewBsp.pStack2, esi		;Points to old BSP so new BSP can update it.

;---Get AP Cpu Control Structure---
	mov esi, ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).CpuControl
	mov edi, esi

	mov	eax, sizeof CPU_CONTROL
	mul bx			;This changes dx
	mov	edx, MpData	;Reload edx
	add	esi, eax	;esi = New Bsp AP_CPU_CONTROL

	lea	eax, ds:(CPU_CONTROL ptr [esi]).Function
	mov	ContextOldBsp.pApFunction, eax
	mov	ContextNewBsp.pApFunction, eax

;---Validate if not halted. ---
	cmp ds:(CPU_CONTROL ptr [esi]).Halted, 0
	jne	SwitchBspExit		;Can't switch if halted.

;---Get this CPU Control Structure--
	movzx ebx,  ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).BSP
	mov	eax, sizeof CPU_CONTROL
	mul bx			;This changes dx
	mov	edx, MpData	;Reload edx
	add	edi, eax	;edi = Old Bsp AP_CPU_CONTROL
;---Switch addresses in control structure---
	mov eax,  ds:(CPU_CONTROL ptr [esi]).Stack
	xchg eax, ds:(CPU_CONTROL ptr [edi]).Stack
	mov ds:(CPU_CONTROL ptr [esi]).Stack, eax

;---Wait until New BSP is idle. ---
@@:
	pause
	cmp	ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).RunningAps, 0
	ja @b

;---Call Function if exists---
	mov	ebx, Function
	or	ebx, ebx
	jz	NoFunction

	;Call function on New Bsp
	lock inc ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).RunningAps
	mov	eax, Context
	mov	ds:(CPU_CONTROL ptr [esi]).Context, eax
	mov ds:(CPU_CONTROL ptr [esi]).Function, ebx	;This releases the New Bsp

	;Call function on Current BSP	
	pushad
	push	Context
	push	ecx			;CPU count
	call	ebx
	add		esp, 8
	popad

	;Wait until Idle
@@:
	pause
	cmp	ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).RunningAps, 0
	ja @b
NoFunction:
;----------- Switch the Stacks. -------------------------------
	lea eax, ContextNewBsp
	lock inc ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).RunningAps
	mov	ds:(CPU_CONTROL ptr [esi]).Context, eax
	mov ds:(CPU_CONTROL ptr [esi]).Function, _CpuSwitchStacks	;Execute on new bsp

	push edx
	push esi

	lea	eax, ContextOldBsp
	push eax
	push ecx
	call _CpuSwitchStacks
	add	esp, 8
	pop esi
	pop edx

	;---Now new BSP is executing with old BSP stack.---

;---Wait until the CPU APs exit.---
@@:
	pause
	cmp	ds:(AP_GLOBAL_DATA_STRUCT ptr [edx]).RunningAps, 0
	ja @b

;---Finish setting up new BSP.---
SwitchBspExit:
	popad
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
