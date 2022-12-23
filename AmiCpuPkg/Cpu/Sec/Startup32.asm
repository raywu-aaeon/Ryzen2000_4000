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
;----------------------------------------------------------------------------
; Name:         Startup32.asm
;
; Description:  Switch CPU to protected mode, initialize cache-as-RAM and
;               setup stack for PEI execution
;
;----------------------------------------------------------------------------
;<AMI_FHDR_END>

;----------------------------------------------------------------------------
; Assembler build options
;----------------------------------------------------------------------------
.686P
.XMM
.MODEL  SMALL, C
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
; Include files
;----------------------------------------------------------------------------
        INCLUDE token.equ
        INCLUDE cpu.equ
        INCLUDE mbiosmac.mac
        INCLUDE cpstack.inc
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
; Constant definitions
;----------------------------------------------------------------------------


IFDEF MKF_PSP_FV_BB_SIZE
SEC_FV_BB_SIZE = MKF_PSP_FV_BB_SIZE
SEC_FV_BB_BASE = 0FFFFFFFFh - MKF_PSP_FV_BB_SIZE + 1
ELSE
SEC_FV_BB_SIZE = MKF_FV_BB_SIZE
SEC_FV_BB_BASE = MKF_FV_BB_BASE
ENDIF

SEC_HIGH_MEMORY_JUMP = 1
IFDEF MKF_FV_REBASE_SUPPORT
IF MKF_FV_REBASE_SUPPORT
SEC_HIGH_MEMORY_JUMP = 0
ENDIF
ENDIF

;----------------------------------------------------------------------------
; Externs
;----------------------------------------------------------------------------
EXTERN  SECCoreAtPowerOn:NEAR32
PUBLIC  SECCoreAtPowerOnEnd
PUBLIC  SECCoreAPinitEnd
EXTERN  SECCoreAPinit:NEAR32
EXTERN  BeforeSECEntry:NEAR32
PUBLIC  BeforeSECEntryEnd
EXTERN  BeforeSEC_S3Entry:NEAR32
PUBLIC  BeforeSEC_S3EntryEnd

SecCEntry   PROTO   C

;----------------------------------------------------------------------------

;STARTUP_SEG SEGMENT USE32
;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG     SEGMENT PARA PUBLIC 'CODE' USE32

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
; Procedure:    _ModuleEntryPoint
;
; Description:  Switch CPU to protected mode, INIT CAR and setup stack.
;
; Input:        CPU registers at CPU reset
;
; Output:       None
;
; Modified:     All, except EBP and DS.
;
; Notes:        1. File contains both 16 bit & 32 bit code
;               2. Since the default code is 32 bit, 16 bit code are left
;                  as binary machine codes
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

_ModuleEntryPoint PROC PUBLIC

; <<----  Processor is in 16bit real mode  ---->>
; Mask the interrupts
        cli

;;              BYTE    0EBh, 0FEh              ; JMP $

; Checkpoint 00h
        BYTE    030h, 0C0h              ; xor al, al
        BYTE    0E6h, 080h              ; out 80h, al

; Save EAX (BIST data in ESP)
        BYTE    66h                     ; Operand size override
        mov     esp, eax

; Save EDX (ResetID data in EBP)
        BYTE    66h                     ; Operand size override
        mov     ebp, edx

; Prepare for protected mode switching

        ;Switch to protected mode
        ;lgdt   fword ptr cs:[GdtDescriptor] ; Relative to 4G.
;       db  66h,2eh,0fh,1,16h
;       dw  offset GdtDescriptor    ;<-------Problem------<

        db   66h
        mov  ebx, offset GdtDescriptor
        ;lgdt fword ptr cs:[bx]
        db  66h, 2eh,0fh,1,17h

        mov     eax, cr0
        or      al, 1           		; Set PE bit
        mov     cr0, eax        		; Turn on Protected Mode

; <<----  Processor is in 16bit protected mode  ---->>
        ; Clear the CPU prefetch queue
        jmp     $ + 2

; Setup segment registers with appropriate descriptor
;;      mov     ax, DATA_SEL
;;      mov     ds, ax
;;      mov     es, ax
;;      mov     ss, ax
;;      mov     fs, ax
;;      mov     gs, ax
        BYTE    66h                     ; Data size
        mov     eax, DATA_SEL
        BYTE    08Eh, 0D8h
        BYTE    08Eh, 0C0h
        BYTE    08Eh, 0D0h
        BYTE    08Eh, 0E0h
        BYTE    08Eh, 0E8h

        ;set cs segment
        ;jmp 10:CHANGE_CS
        db  66h, 0eah
        dd  changeCs                    ; Relative to 4G.
        dw  CODE_SEL
        
changeCs:
; <<----  Processor is in 32 bit protected mode  ---->>

        mov     edi, offset FC_MemJump
        jmp     FamilyCheck
FC_MemJump:
        je      F15_NoMemJump          ; Family 15 doesn't need jump to memory copy

IF SEC_HIGH_MEMORY_JUMP
; Jump to memory copy
        mov     eax, $
        and     eax, (SEC_FV_BB_SIZE - 1)
        add     eax, (MKF_HIGH_MEMORY_REGION_BB_BASE + 011h)
        jmp     eax
        jmp     F17_NoMmioSetup
ENDIF

; [Fam15 only]>
F15_NoMemJump:

;---  Adding MMIO Base and Limit - Early setup needed for system boot with real Hw
        mov     dx, 0cf8h
        mov     eax, 8000c184h
        out     dx, eax
        add     dx, 4
        mov     eax, 00FED880h
        out     dx, eax
        mov     dx, 0cf8h
        mov     eax, 8000c180h
        out     dx, eax
        add     dx, 4
        mov     eax, 00FED803h
        out     dx, eax
;;--- Adding MMIO Base and Limit
; [Fam15 only]<

F17_NoMmioSetup:
; Invoke the SECCore Init hook for other components to hook functions

; INPUT:
;       ESP     BIST information
;       EBP     Reset ID (value of EDX at reset)

        jmp     SECCoreAtPowerOn

SECCoreAtPowerOnEnd::
        ; We need to check the stack to determine if it is S3 path
        ; In SECCore_PspResEntry path, we push 53535353h, eax and esi before SECCoreAtPowerOn
        ; So it need add offset 12 (eax, ebx, esi) to get the signature we set.
        cmp     DWORD PTR [esp + 12], 53535353h
        jz      SECCoreAtPowerOnEnd_S3

        cld
        ChkPnt  011h

; Initialize FPU on BSP
;        fninit

; In CR4, set OSFXSR bit 9 and OSXMMEXCPT bit 10
        mov     eax, cr4
        or      ax, (1 SHL 9) + (1 SHL 10)
        mov     cr4, eax

        mov     edi, offset FC_Stack
        jmp     FamilyCheck

FC_Stack:
        jne     sbs_StackAvailable  ; Family 17 doesn't need to establish STACK

; [Fam15 only] >
        AMD_ENABLE_STACK_PRIVATE STACK_AT_TOP, MKF_CAR_TOTAL_SIZE, MKF_CAR_BASE_ADDRESS

; Validate stack availability
        mov     eax, 05A5AA5A5h
        push    eax
        nop
        nop
        pop     eax
        not     eax                     ; EAX = 0A5A55A5Ah
        push    eax
        nop
        nop
        xor     eax, eax
        pop     eax
        cmp     eax, 0A5A55A5Ah
        je      sbs_StackAvailable

sbs_StuckHere:
        mov     ax, 0E007h
        out     80h, ax
        cli
        hlt
        jmp     SHORT sbs_StuckHere

; [Fam15 only] <

sbs_StackAvailable:

; Use variable MTRRs to set ROM space to WP
        xor     edx, edx
        mov     eax, (FW_CODE_AREA_START OR WriteProtect)
        mov     ecx, MTRR_PHYS_BASE_7
        wrmsr
; Write the size
        mov     eax, (FW_CODE_AREA_SIZE_MASK OR ValidMask)
        mov     edx, MTRR_VAR_TOP_MASK_VALUE
        inc     ecx                     ; MTRR_PHYS_MASK_7
        wrmsr

        mov     edi, offset FC_BB_Cache
        jmp     FamilyCheck
FC_BB_Cache:
        je      F15_NoHighBBCache          ; Family 15 doesn't need to cache HIGH_MEMORY_REGION_BASE
        
        ;DisableCacheInCR0
        wbinvd
        mov     eax, cr0
        or      eax, 060000000h     ;SET CD, NW
        mov     cr0, eax
        wbinvd                  ;Invalidate cache
        ;IA32_MTRR_DEF_TYPE 0
        xor     edx, edx
        mov     eax, 0
        mov     ecx, 0x2FF
        wrmsr
; Use variable MTRRs to set HIGH_MEMORY_REGION_BASE space to WP
        xor     edx, edx
        mov     eax, (MKF_HIGH_MEMORY_REGION_BASE OR WriteBack)
        mov     ecx, MTRR_PHYS_BASE_6
        wrmsr

        mov     eax, (FW_CODE_AREA_SIZE_MASK OR ValidMask)
        mov     edx, MTRR_VAR_TOP_MASK_VALUE
        inc     ecx                     ; MTRR_PHYS_MASK_6
        wrmsr

        ;IA32_MTRR_DEF_TYPE 0
        ;enable Fixed and Variable MTRRs, default UC
        xor     edx, edx
        mov     eax, 3 Shl 10
        mov     ecx, 0x2FF
        wrmsr

        ;  VOID EnableCacheInCR0(VOID){
        ;// Enable cache
        mov     eax, cr0
        and     eax, 09fffffffh     ;SET CD, NW
        mov     cr0, eax
        wbinvd

        mov     esp, MKF_CAR_BASE_ADDRESS + MKF_CAR_TOTAL_SIZE

F15_NoHighBBCache:
;Check is BSP then continue
        mov     ecx, MSR_XAPIC_BASE
        rdmsr
        and     eax, 0100h
        cmp     eax, 0100h
        jne     Iam_AP


        pushd   027fh
        fldcw   WORD PTR [esp]          ; Set FP Control Word according UEFI
        add     esp, 4

  ;; |-------------------|---->
  ;; |Idt Table          |
  ;; |-------------------|
  ;; |PeiService Pointer |    PeiStackSize
  ;; |-------------------|
  ;; |                   |
  ;; |      Stack        |
  ;; |-------------------|----> StackBase (MKF_CAR_BASE_ADDRESS + MKF_CAR_TOTAL_SIZE/2)
  ;; |                   |
  ;; |                   |
  ;; |      Heap         |    PeiTemporaryRamSize
  ;; |                   |
  ;; |                   |
  ;; |-------------------|---->  TempRamBase


; Call SEC C CORE

        mov     edi, offset FC_BB_Base_Change
        jmp     FamilyCheck
FC_BB_Base_Change:
        je      F15_NoBBbaseChange          ; Family 15 doesn't need to re-base BB

        mov     eax, SEC_FV_BB_BASE
        and     eax, (SEC_FV_BB_SIZE - 1)
        add     eax, MKF_HIGH_MEMORY_REGION_BB_BASE
        push    eax

        mov     eax, MKF_CAR_BASE_ADDRESS
        push    eax
        mov     eax, MKF_CAR_TOTAL_SIZE
        push    eax
        jmp     F17_BaseChangeDone
F15_NoBBbaseChange:
        mov     eax, MKF_FV_BB_BASE
        push    eax
        mov     eax, MKF_CAR_BASE_ADDRESS
        push    eax
        mov     eax, MKF_CAR_TOTAL_SIZE
        push    eax
F17_BaseChangeDone:
        jmp     BeforeSECEntry

BeforeSECEntryEnd::
        call    SecCEntry

;----------FamilyCheckJmpEdi
FamilyCheck:
        mov     eax, AMD_CPUID_FMF      ; Family, Model, Stepping Identifiers
        cpuid
        and     eax, RAW_FAMILY_ID_MASK ; Get Base Model
        cmp     eax, F15_BR_RAW_ID      ; check if it is family 15h ?

        jmp     edi

;----------FamilyCheckJmpEdi

Iam_AP:

;;Read AP Launch Address
        jmp     SECCoreAPinit

SECCoreAPinitEnd::
        jmp     edi
;============================ PSP RESUME ==================================
;typedef struct _PSP_SMM_RSM_MEM_INFO {
;  UINT32                  BspStackSize;           // BSP Stack Size for resume
;  UINT32                  ApStackSize;            // AP Stack Size for resume
;  EFI_PHYSICAL_ADDRESS    StackPtr;              // Point to the base of Stack
;  EFI_PHYSICAL_ADDRESS    RsmHeapPtr;            // Point to the base of Resume Heap
;  UINT32                  HeapSize;               // Reserved Heap Size
;  UINT32                  TempRegionSize;         // Reserved Temp Region Size
;  EFI_PHYSICAL_ADDRESS    TempRegionPtr;         // Point to the base of Temporary Region (used for store the dynamic value during SMM SEC Phase)
;} PSP_SMM_RSM_MEM_INFO;

SECCore_PspResEntry::
        mov     esi, eax                ; Save Eax - pointer to PSP_SMM_RSM_MEM_INFO
        push    53535353h
        push    ebx                     ; Save Ebx - Signature CAPSULE_UPDATE_SIGNATURE
        push    eax                     ; Save Eax - pointer to PSP_SMM_RSM_MEM_INFO for AP

        cmp     ebx, CAPSULE_UPDATE_SIGNATURE
        jne     SkipCapsule
        ; Open SMRAM for capsule update, ROM is in SMRAM
        mov     ecx, 0C0010113h
        rdmsr
        btr     eax, 0
        btr     eax, 1
        wrmsr
        mov     ecx, 0C0010111h ; SMM_BASE
        rdmsr
        mov     eax, 30000h
        wrmsr

SkipCapsule:
;Clear Long Mode Enable 
        mov     ecx, 0c0000080h         ; EFER MSR number. 
        rdmsr            
        btr     eax, 8                  ; Set LME=0 
        wrmsr

;        mov     edi, offset FC_S3RomCache
;        jmp     FamilyCheck
;FC_S3RomCache:
;        jne     F17_NoRomCache          ; F17 doesn't need ROM cache

        xor     edx, edx
; Use variable MTRRs to set ROM space to WP
        mov     eax, (FW_CODE_AREA_START OR WriteProtect)
        mov     ecx, MTRR_PHYS_BASE_7
        wrmsr
; Write the size
        mov     eax, (FW_CODE_AREA_SIZE_MASK OR ValidMask)
        mov     edx, MTRR_VAR_TOP_MASK_VALUE
        inc     ecx                     ; MTRR_PHYS_MASK_7
        wrmsr

F17_NoRomCache:

        mov     ecx, MSR_XAPIC_BASE
        rdmsr
        and     eax, 0100h
        cmp     eax, 0100h
        je      BSP_S3

        mov     edi, offset FC_S3_AP
        jmp     FamilyCheck
FC_S3_AP:
        je      F15_S3_AP_NO_HALT
@@:
        cli                             ; Family 17h AP just halt here
        hlt
        jmp     @b

; [Fam15 only] >
F15_S3_AP_NO_HALT:
        ; AP related code
        lea     eax, [esp + 12]         ; 53535353h
        push    eax                     ; pointer to the top of stack, a signature 53535353h
        lea     eax, [esp]

        push    eax                     ; Address of mPspSmmRsmMemInfo, initialized by PSP SMM Resume code

        xor     eax, eax                ; APs don't have PeiServices, it should be a zero pointer
        push    eax                     ; IN EFI_PEI_SERVICES           **PeiServices
        lidt    FWORD PTR [esp+2]
;        pop     eax
;        pop     eax

        jmp     Iam_AP
; [Fam15 only] <

ALIGN 4
        db      51h,52h,53h,54h
        dd      OFFSET GDT_BASE         ; GDT offset
        dw      0010h                   ; CODE selector
        dw      0008h                   ; DATA selector
        dd      OFFSET SECCore_PspResEntry ; RSM Entry Point
        dd      00000EDFh               ; RSM EDX signature
BSP_S3:

        mov     edi, offset FC_S3_MemJump
        jmp     FamilyCheck
FC_S3_MemJump:
        je      F15_S3_NoMemJump

IF SEC_HIGH_MEMORY_JUMP
        mov     eax, $
        and     eax, (SEC_FV_BB_SIZE - 1)
        add     eax, (MKF_HIGH_MEMORY_REGION_BB_BASE + 011h)
        jmp     eax
ENDIF

F15_S3_NoMemJump:
        ; MMIO, etc>>
        push    edx
        push    eax
        mov     dx, 0cd6h
        mov     al, 4                   ; PMx04
        out     dx, al
        inc     dx                      ; CD7
        in      al, dx
        or      al, 2                   ; MMIO enable
        out     dx, al
        dec     dx                      ; cd6
        xor     ax,ax                   ; PMx00
        out     dx, al
        inc     dx
        in      al, dx
        or      al, 11h                 ; enable SMBUS decode, legacyIO Enable
        out     dx, al

        ;---  Adding MMIO Base and Limit - Early setup needed for system boot with real Hw
        mov     edi, offset FC_S3_MmioSetupCk
        jmp     FamilyCheck
FC_S3_MmioSetupCk:
        jne     F17_S3_NoMmioSetup
	
; [Fam15 only]>
        mov     dx, 0cf8h
        mov     eax, 8000c184h
        out     dx, eax
        add     dx, 4
        mov     eax, 00FED880h
        out     dx, eax
        mov     dx, 0cf8h
        mov     eax, 8000c180h
        out     dx, eax
        add     dx, 4
        mov     eax, 00FED803h
        out     dx, eax
; [Fam15 only]<

F17_S3_NoMmioSetup:

        pop     eax
        pop     edx

        ; re-programm PM_BASE
        push    ebx
        mov     ebx, 0FED80362h         ; Pm1CtlBlock Base
        mov     ax, MKF_PM_BASE_ADDRESS + 04h
        mov     WORD PTR [ebx], ax
        pop     ebx

        push    esi                     ; Save esi - pointer to PSP_SMM_RSM_MEM_INFO
        jmp     SECCoreAtPowerOn

SECCoreAtPowerOnEnd_S3::

        pop     esi                     ; restore esi - pointer to PSP_SMM_RSM_MEM_INFO

; Call SEC C CORE

        mov     edi, offset FC_S3_BB_Base_Change
        jmp     FamilyCheck
FC_S3_BB_Base_Change:
        je      F15_S3_NoBBbaseChange          ; Family 15 doesn't need to re-base BB

        mov     eax, SEC_FV_BB_BASE
        and     eax, (SEC_FV_BB_SIZE - 1)
        add     eax, MKF_HIGH_MEMORY_REGION_BB_BASE
        push    eax

        mov     eax, dword ptr[esi + 8]    ; MKF_CAR_BASE_ADDRESS
        push    eax
        mov     eax, dword ptr[esi]    ; MKF_CAR_TOTAL_SIZE
        push    eax
        jmp     F17_S3_BaseChangeDone

F15_S3_NoBBbaseChange:
        mov     eax, MKF_FV_BB_BASE
        push    eax
        mov     eax, dword ptr[esi + 8]    ; MKF_CAR_BASE_ADDRESS
        push    eax
        mov     eax, dword ptr[esi]    ; MKF_CAR_TOTAL_SIZE
        push    eax
F17_S3_BaseChangeDone:
        jmp     BeforeSEC_S3Entry

BeforeSEC_S3EntryEnd::
        call    SecCEntry
;==========================================================================
_ModuleEntryPoint ENDP


;----------------------------------------------
align 16
GDT_BASE:
NULL_SEL        equ     $ - GDT_BASE   ;NULL Selector 0
        dd  0, 0

DATA_SEL        equ     $ - GDT_BASE   ; Selector 8, Data 0-ffffffff 32 bit
        dd 0000ffffh
        dd 00cf9300h

CODE_SEL        equ     $ - GDT_BASE   ; Selector 10h, CODE 0-ffffffff 32 bit
        dd 0000ffffh
        dd 00cf9b00h

; We only need this because Intel DebugSupport driver
; (RegisterPeriodicCallback function) assumes that selector 0x20 is valid
; The funciton sets 0x20 as a code selector in IDT
;
; To switch to 16 bit, Selectors SYS16_CODE_SEL and SYS16_DATA_SEL are used.
;
; System data segment descriptor
;
SYS_DATA_SEL    equ     $ - GDT_BASE    ; Selector [0x18]
        dd 0000FFFFh                    ; 0 - f_ffff
        dd 00cf9300h                    ; data, expand-up, notwritable, 32-bit

; System code segment descriptor
SYS_CODE_SEL    equ     $ - GDT_BASE    ; Selector [0x20]
        dd 0000FFFFh                    ; 0 - f_ffff
        dd 00cf9b00h                    ; data, expand-up, writable, 32-bit
SPARE3_SEL      equ     $ - GDT_BASE    ; Selector [0x28]
        dd 0, 0
SYS_DATA64_SEL  equ     $ - GDT_BASE    ; Selector [0x30]
        dd 0000FFFFh
        dd 00cf9300h
SYS_CODE64_SEL  equ     $ - GDT_BASE    ; Selector [0x38]
        dd 0000FFFFh
        dd 00af9b00h
SPARE4_SEL      equ     $ - GDT_BASE    ; Selector [0x40]
        dd 0, 0
GDT_SIZE        equ     $ - GDT_BASE    ; Size of Descriptor Table

GdtDescriptor:
        dw  GDT_SIZE - 1                ; GDT limit
        dd  offset GDT_BASE             ; GDT base  Relative to 4G.

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  ENDS
;----------------------------------------------------------------------------
STARTUP_SEG     ENDS

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
