; ****************************************************************************
; *
; * @file
; *
; * Agesa structures and definitions
; *
; * Contains AMD AGESA core interface
; *
; * @xrefitem bom "File Content Label" "Release Content"
; * @e project:      AGESA
; * @e sub-project:  Include
; * @e \$Revision: 327797 $   @e \$Date: 2015-09-25 02:07:15 -0500 (Fri, 25 Sep 2015) $
;
; ****************************************************************************
; *
; * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
; *
; *******************************************************************************

UINT64    TEXTEQU     <QWORD>
UINT32    TEXTEQU     <DWORD>

;;***************************************************************************
;;
;;                      CPU MACROS - PUBLIC
;;
;;***************************************************************************
_WRMSR macro
  db  0Fh, 30h
  endm

_RDMSR macro
  db  0Fh, 32h
  endm


; Build Configuration values for BLDGCFG_AP_MTRR_SETTINGS
AP_MTRR_SETTINGS  STRUCT
  MsrAddr       UINT32 ?  ; < Fixed-Sized MTRR address
  MsrData       UINT64 ?  ; < MTRR Settings
AP_MTRR_SETTINGS  ENDS

AMD_AP_MTRR_FIX64k_00000    EQU 000000250h
AMD_AP_MTRR_FIX16k_80000    EQU 000000258h
AMD_AP_MTRR_FIX16k_A0000    EQU 000000259h
AMD_AP_MTRR_FIX4k_C0000     EQU 000000268h
AMD_AP_MTRR_FIX4k_C8000     EQU 000000269h
AMD_AP_MTRR_FIX4k_D0000     EQU 00000026Ah
AMD_AP_MTRR_FIX4k_D8000     EQU 00000026Bh
AMD_AP_MTRR_FIX4k_E0000     EQU 00000026Ch
AMD_AP_MTRR_FIX4k_E8000     EQU 00000026Dh
AMD_AP_MTRR_FIX4k_F0000     EQU 00000026Eh
AMD_AP_MTRR_FIX4k_F8000     EQU 00000026Fh
CPU_LIST_TERMINAL           EQU 0FFFFFFFFh

AMD_MTRR_VARIABLE_BASE6 EQU 020Ch
AMD_MTRR_VARIABLE_BASE7 EQU 020Eh
AMD_MTRR_VARIABLE_MASK7 EQU 020Fh

TW_CFG                  EQU 0C0011023h
    COMBINE_CR0_CD      EQU 49

HWCR                    EQU 0C0010015h  ; Hardware Configuration
    INVD_WBINVD             EQU 4       ;   INVD to WBINVD conversion

CR0_PE                  EQU 0           ; Protection Enable
CR0_NW                  EQU 29          ; Not Write-through
CR0_CD                  EQU 30          ; Cache Disable

MTRR_SYS_CFG            EQU 0C0010010h  ; System Configuration Register
  MTRR_FIX_DRAM_EN          EQU 18      ;   MtrrFixDramEn    MTRR fixed RdDram and WrDram attributes enable
  MTRR_FIX_DRAM_MOD_EN      EQU 19      ;   MtrrFixDramModEn MTRR fixed RdDram and WrDram modification enable
  MTRR_VAR_DRAM_EN          EQU 20      ;   MtrrVarDramEn    MTRR variable DRAM enable

AMD_MTRR_DEFTYPE        EQU 02FFh
    MTRR_DEF_TYPE_EN        EQU 11      ; MtrrDefTypeEn - variable and fixed MTRRs default enabled
    MTRR_DEF_TYPE_FIX_EN    EQU 10      ; MtrrDefTypeEn - fixed MTRRs default enabled

AMD_CPUID_APIC          EQU 80000008h   ; Long Mode and APIC info., core count
    APIC_ID_CORE_ID_SIZE     EQU 12     ; ApicIdCoreIdSize bit position

APIC_BASE_ADDRESS       EQU 0000001Bh

; Flags can only run from bits 31 to 24.  Bits 23:0 are in use.
AMD_CU_NEED_TO_WAIT     EQU 31
AMD_CU_SEND_INVD_MSG    EQU 30
AMD_CU_RESTORE_ES       EQU 29

APIC_ID_REG             EQU 0020h       ; Local APIC ID offset
  APIC20_APICID       EQU 24

APIC_MSG_REG            EQU 380h        ; Location of BSC message
    APIC_MSG            EQU 00DE00ADh   ; Message data
APIC_CMD_LO_REG         EQU 300h        ; APIC command low
APIC_CMD_HI_REG         EQU 310h        ; APIC command high
    CMD_REG_TO_READ_DATA EQU 00000338h  ; APIC command for remote read of APIC_MSG_REG
    DELIVERY_STS_BIT    EQU 12          ; Delivery status valid bit
    REMOTE_READ_STS       EQU 00030000h ; Remote read status mask
    REMOTE_DELIVERY_PEND  EQU 00010000h ; Remote read is pending
    REMOTE_DELIVERY_DONE  EQU 00020000h ; Remote read is complete
APIC_REMOTE_READ_REG    EQU 00C0h       ; Remote read offset


FLAG_IS_PRIMARY                   EQU 26    ; Signals that this core is the primary within the compute unit

; CPUID Functions

CPUID_MODEL             EQU 1

AMD_CPUID MACRO arg0
  IFB <arg0>
    mov   eax, 1
    db    0Fh, 0A2h                     ; Execute instruction
    bswap eax
    xchg  al, ah                        ; Ext model in al now
    rol   eax, 8                        ; Ext model in ah, model in al
    and   ax, 0FFCFh                    ; Keep 23:16, 7:6, 3:0
  ELSE
    mov   eax, arg0
    db    0Fh, 0A2h
  ENDIF
ENDM

;----------------------------------------------
;
; AMD_DISABLE_STACK_FAMILY_HOOK Macro - Stackless
;
;   Return any family specific controls to their 'standard'
;   settings for using cache with main memory.
;
; Inputs:
;       ESI - node#, core#, flags from GET_NODE_ID_CORE_ID
; Outputs:
;       none
; Destroyed:
;       eax, ebx, ecx, edx
;----------------------------------------------
AMD_DISABLE_STACK_FAMILY_HOOK MACRO

    AMD_DISABLE_STACK_FAMILY_HOOK_F17

ENDM

;----------------------------------------------
;
; AMD_DISABLE_STACK_FAMILY_HOOK_F17 Macro - Stackless
;
;   Return any family specific controls to their 'standard'
;   settings for using cache with main memory.
;
; Inputs:
;       ESI - [31:24] flags; [15:8]= Node#; [7:0]= core#
; Outputs:
;       none
; Destroyed:
;       eax, ebx, ecx, edx
;
; Family 15h CZ requirements:
;   * INVD or WBINVD
;   * MSRC001_0015[INVD_WBINVD]=1
;   * MSRC001_101C[DisSS]=0
;   * MSRC001_1021[DisSpecTlb]=0
;   * MSRC001_101C[DisSpecTlb]=0
;   * MSRC001_101C[DisHwPf]=0
;---------------------------------------------------
AMD_DISABLE_STACK_FAMILY_HOOK_F17 MACRO
    local   fam17_disable_stack_hook_exit

    AMD_CPUID   CPUID_MODEL
    mov     ebx, eax                    ; Save revision info to EBX
    shr     eax, 20                     ; AL = cpu extended family
    cmp     al, 07h                     ; Is this family 17h?
    jnz     fam17_disable_stack_hook_exit ; Br if no

    mov     edi, ebx                    ; Save revision info to EDI
    AMD_CPUID   AMD_CPUID_APIC
    mov     al, cl                      ; AL = number of cores - 1
    shr     cx, APIC_ID_CORE_ID_SIZE    ; CL = ApicIdCoreIdSize
    mov     bx, 1
    shl     bl, cl                      ; BL = theoretical number of cores on socket
    dec     bx                          ; BL = core number on socket mask
    mov     ah, bl                      ; AH = core number on socket mask
    mov     ebx, edi                    ; Restore revision info to EBX
    mov     di, ax                      ; DI[15:8] = core number mask, DI[7:0] = number of cores - 1

    and     ebx, 0F00FFh
    mov     eax, ebx
    shr     eax, 8
    or      bx, ax                      ; Save Extended Model, Model and Stepping to BX
                                        ; [11:8] = Extended Model, [7:4] = Model, [3:0] = Stepping

    ;; A handshake is required to ensure that all cores on a node invalidate in sync.
    ;    Entry:
    ;      BX: [11:8] = Extended Model,   [7:4] = Model, [3:0] = Stepping
    ;      DI: [15:8] = core number mask, [7:0] = number of cores - 1
    HANDSHAKE_F17

    ;    Exit:
    ;     BX:
    ;       HANDSHAKE_F15      - [11:8] = Extended Model,   [7:4] = Model, [3:0] = Stepping
    ;       HANDSHAKE_F15_PCI  - [7:0]  = Core ID
    ;     EDI: CU flag
    ;       bit[31] - AMD_CU_NEED_TO_WAIT
    ;       bit[30] - AMD_CU_SEND_INVD_MSG
    ;       bit[29] - AMD_CU_RESTORE_ES

    ; Do Standard Family 17 work
    mov     ecx, HWCR                   ; MSR:C001_0015h
    _RDMSR
    bts     eax, INVD_WBINVD            ; Turn on INVD -> WBINVD conversion
    _WRMSR

    mov     ecx, TW_CFG                ; MSR:C001_1023
    _RDMSR
    bts     edx, (COMBINE_CR0_CD - 32)  ; Set CombineCr0Cd bit
    _WRMSR

    bt      edi, AMD_CU_SEND_INVD_MSG
    .if (carry?)
        ;; Non core zero needs to signal to core 0 to proceed
        SIGNAL_OTHER_CORE_F17
    .endif

fam17_disable_stack_hook_exit:
ENDM

;---------------------------------------------------
;
; HANDSHAKE_F17 Macro - Stackless
;
;   A handshake is required to ensure that all cores
;   on a node invalidate in sync.
;
; Inputs:
;     BX:  [11:8] = Extended Model,   [7:4] = Model, [3:0] = Stepping
;     DI:  [15:8] = core number mask, [7:0] = number of cores - 1
; Outputs:
;     BX:  [11:8] = Extended Model,   [7:4] = Model, [3:0] = Stepping
;     EDI: CU flag
;       bit[31] - AMD_CU_NEED_TO_WAIT
;       bit[30] - AMD_CU_SEND_INVD_MSG
;       bit[29] - AMD_CU_RESTORE_ES
; Destroyed:
;       eax, ebx, ecx, edx
;---------------------------------------------------
HANDSHAKE_F17 MACRO
    local   fam17_disable_stack_remote_read_exit

    mov     ecx, APIC_BASE_ADDRESS
    _RDMSR
    mov     dx, bx                      ; Save Extended Model, Model and Stepping to DX
    shl     edx, 16                     ; EDX[31:16] = Extended Model, Model and Stepping
    mov     ebx, eax                    ; EBX = LAPIC base
    xor     ecx, ecx                    ; Zero out CU flags
    bts     ecx, AMD_CU_NEED_TO_WAIT    ; Default to waiting
    bts     ecx, AMD_CU_SEND_INVD_MSG   ; Default to signaling
    mov     eax, CR0
    bt      ax, CR0_PE                  ; Are we in protected mode?
    .if (!carry?)
        bts     ecx, AMD_CU_RESTORE_ES  ; Indicate ES restore is required
        mov     cx, es                  ; Save ES segment register to CX
        xor     ax, ax
        mov     es, ax                  ; Set ES to big real mode selector for 4GB access
    .endif

    and     bx, 0F000h                  ; EBX = LAPIC base, offset 0
    or      bl, APIC_ID_REG
    mov     eax, es:[ebx]               ; EAX[31:24] = APIC ID
    shr     eax, APIC20_APICID          ; AL = APIC ID
    mov     ah, al                      ; AH = APIC ID
    mov     dx, di                      ; DH = core mask
    and     ah, dh                      ; AH = core number
    .if (zero?)
        ;; Core 0 of a socket
        btr     ecx, AMD_CU_SEND_INVD_MSG ; No need to signal after INVD
        .if (dl != 0)
            ;; This socket has multiple cores
            and     bx, 0F000h          ; EBX = LAPIC base, offset 0
            or      bx, APIC_MSG_REG
            mov     edi, APIC_MSG
            mov     es:[ebx], edi       ; Signal for non core 0s to complete CAR breakdown
        .else
            btr     ecx, AMD_CU_NEED_TO_WAIT ; No need to wait on a single core CPU
        .endif
    .endif

    bt     ecx, AMD_CU_NEED_TO_WAIT
    .if (carry?)
        .if (ah == dl)
            ;; This is the highest numbered core on this socket -- wait on core 0
            not     dh                  ; Flip the mask to determine local core 0's APIC ID
            and     al, dh              ; AL = target APIC ID
        .else
            ;; All other cores (including core 0) wait on the next highest core.
            ;; In this way, cores will halt in a cascading fashion down to 0.
            inc     al
        .endif

        shl     eax, APIC20_APICID
        and     bx, 0F000h
        or      bx, APIC_CMD_HI_REG
        mov     es:[ebx], eax           ; Set target APIC ID

        ;; Use bits 23:16 as a timeout for unresponsive cores
        ror     ecx, 8
        mov     ch, 0FFh
        stc
        .while (carry?)
            and     bx, 0F000h          ; EBX = LAPIC base, offset 0
            or      bx, APIC_CMD_LO_REG
            mov     eax, CMD_REG_TO_READ_DATA
            mov     es:[ebx], eax       ; Fire remote read IPI
            inc     ch                  ; Pre increment the timeout
            stc
            .while (carry?)
                dec     ch              ; Check the timeout
                jz      fam17_disable_stack_remote_read_exit   ; Branch if there is an unresponsive core
                mov     eax, es:[ebx]
                bt      eax, DELIVERY_STS_BIT
            .endw
            stc
            .while (carry?)
                mov     eax, es:[ebx]
                and     eax, REMOTE_READ_STS
                .if (eax == REMOTE_DELIVERY_PEND)
                    dec     ch          ; Check the timeout
                    jz      fam17_disable_stack_remote_read_exit   ; Branch if there is an unresponsive core
                    stc
                .else
                    clc
                .endif
            .endw
            .if (eax == REMOTE_DELIVERY_DONE)
                and     bx, 0F000h      ; EBX = LAPIC base, offset 0
                or      bl, APIC_REMOTE_READ_REG
                mov     eax, es:[ebx]
                .if (eax == APIC_MSG)
                    clc
                .else
                    stc
                .endif
            .else
                dec     ch              ; Check the timeout
                jz      fam17_disable_stack_remote_read_exit   ; Branch if there is an unresponsive core
                stc
            .endif
        .endw

fam17_disable_stack_remote_read_exit:
        rol     ecx, 8                  ; Restore ECX

    .endif
    bt      ecx, AMD_CU_RESTORE_ES
    .if (carry?)
        mov     es, cx
    .endif
    mov     edi, ecx                    ; EDI = CU flags
    shr     edx, 16
    mov     bx,  dx
ENDM

;---------------------------------------------------
;
; SIGNAL_OTHER_CORE_F17 Macro - Stackless
;
;   Non core zero needs to signal to other cores to proceed
;
; Inputs:
;     BX:  Core ID
;     DI:  [15:8] = core number mask, [7:0] = number of cores - 1
; Outputs:

; Destroyed:
;       eax, ebx, ecx, edx
;---------------------------------------------------
SIGNAL_OTHER_CORE_F17 MACRO
    mov     ecx, APIC_BASE_ADDRESS
    _RDMSR
    mov     ebx, eax                ; EBX = LAPIC base
    and     bx, 0F000h              ; EBX = LAPIC base, offset 0
    or      bx, APIC_MSG_REG
    mov     eax, APIC_MSG
    mov     es:[ebx], eax           ; Signal for core 0 to complete CAR breakdown
ENDM

