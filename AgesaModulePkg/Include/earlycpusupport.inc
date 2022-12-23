;*****************************************************************************
; AMD Generic Encapsulated Software Architecture
;
; $Workfile:: earlycpusupport.inc
;
;  $Revision$    $Date$
;
; Description:
;
;*****************************************************************************
;
; Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
;
;******************************************************************************
    .LIST
    .mmx

UINT64    TEXTEQU     <QWORD>
UINT32    TEXTEQU     <DWORD>

; Build Configuration values for BLDGCFG_AP_MTRR_SETTINGS
AP_MTRR_SETTINGS  STRUCT
  MsrAddr       UINT32 ?  ; < Fixed-Sized MTRR address
  MsrData       UINT64 ?  ; < MTRR Settings
AP_MTRR_SETTINGS  ENDS

STACK_AT_TOP            EQU 0           ; Stack is at the top of CAR
STACK_AT_BOTTOM         EQU 1           ; Stack is at the bottom of CAR

AP_COMM_APIC            EQU 0           ; AP communicates by local APIC
AP_COMM_PCI             EQU 1           ; AP communicates by PCI

;; Below definition MUST be the same as cpuApCommPci.h
MMIO_CFG_BASE           EQU 0C0010058h  ; MMIO Configuration Base Address
AP_COMM_CORE0_DATA_ADDR    TEXTEQU  <MAKE_SBDFO 0, 0, 24, 5, 1D8h>
AP_COMM_CORE0_CONTROL_ADDR TEXTEQU  <MAKE_SBDFO 0, 0, 24, 5, 1E8h>
AP_COMM_CONTROL_BITS_WIDTH EQU      8
AP_COMM_CONTROL_MASK       EQU      0FFh

APIC_BASE_ADDRESS       EQU 0000001Bh
    APIC_BSC                EQU 8       ; Boot Strap Core

APIC_MSG_REG            EQU 380h        ; Location of BSC message
    APIC_MSG            EQU 00DE00ADh   ; Message data
    APIC_INVD_ALL_DONE_MSG  EQU     00AD00DEh ; Indicate all cores have invalidated
APIC_CMD_LO_REG         EQU 300h        ; APIC command low
APIC_CMD_HI_REG         EQU 310h        ; APIC command high
    CMD_REG_TO_READ_DATA EQU 00000338h  ; APIC command for remote read of APIC_MSG_REG
    REMOTE_READ_STS       EQU 00030000h ; Remote read status mask
    REMOTE_DELIVERY_PEND  EQU 00010000h ; Remote read is pending
    REMOTE_DELIVERY_DONE  EQU 00020000h ; Remote read is complete
    DELIVERY_STS_BIT    EQU 12          ; Delivery status valid bit
APIC_ID_REG             EQU 0020h       ; Local APIC ID offset
    APIC20_APICID       EQU 24
APIC_REMOTE_READ_REG    EQU 00C0h       ; Remote read offset

; Flags can only run from bits 31 to 24.  Bits 23:0 are in use.
AMD_CU_NEED_TO_WAIT     EQU 31
AMD_CU_SEND_INVD_MSG    EQU 30
AMD_CU_RESTORE_ES       EQU 29

AMD_MTRR_VARIABLE_BASE0 EQU 0200h
AMD_MTRR_VARIABLE_BASE6 EQU 020Ch
AMD_MTRR_VARIABLE_BASE7 EQU 020Eh
    VMTRR_VALID             EQU     11
    MTRR_TYPE_WB            EQU     06h
    MTRR_TYPE_WP            EQU     05h
    MTRR_TYPE_WT            EQU     04h
    MTRR_TYPE_UC            EQU     00h
AMD_MTRR_VARIABLE_MASK0 EQU 0201h
AMD_MTRR_VARIABLE_MASK7 EQU 020Fh
AMD_MTRR_FIX64k_00000   EQU 0250h
AMD_MTRR_FIX16k_80000   EQU 0258h
AMD_MTRR_FIX16k_A0000   EQU 0259h
AMD_MTRR_FIX4k_C0000    EQU 0268h
AMD_MTRR_FIX4k_C8000    EQU 0269h
AMD_MTRR_FIX4k_D0000    EQU 026Ah
AMD_MTRR_FIX4k_D8000    EQU 026Bh
AMD_MTRR_FIX4k_E0000    EQU 026Ch
AMD_MTRR_FIX4k_E8000    EQU 026Dh
AMD_MTRR_FIX4k_F0000    EQU 026Eh
AMD_MTRR_FIX4k_F8000    EQU 026Fh
CPU_LIST_TERMINAL       EQU 0FFFFFFFFh

AMD_MTRR_DEFTYPE        EQU 02FFh
    WB_DRAM_TYPE            EQU 1Eh     ; MemType - memory type
    MTRR_DEF_TYPE_EN        EQU 11      ; MtrrDefTypeEn - variable and fixed MTRRs default enabled
    MTRR_DEF_TYPE_FIX_EN    EQU 10      ; MtrrDefTypeEn - fixed MTRRs default enabled

HWCR                    EQU 0C0010015h  ; Hardware Configuration
    INVD_WBINVD             EQU 4       ;   INVD to WBINVD conversion

IORR_BASE               EQU 0C0010016h  ; IO Range Regusters Base/Mask, 2 pairs
                                        ;   uses 16h - 19h
TOP_MEM                 EQU 0C001001Ah  ; Top of Memory
TOP_MEM2                EQU 0C001001Dh  ; Top of Memory2

LS_CFG3                 EQU 0C001101Ch  ; Load-Store Configuration 3
    DIS_SS_F15CZ            EQU 7       ;   Disable Streaming Store functionality
    DC_DIS_SPEC_TLB_RLD_F15CZ   EQU 20  ;   Disable speculative TLB reloads
    DC_DIS_HW_PF_F15CZ      EQU 23      ;   Hardware prefetches bit

LS_CFG                  EQU 0C0011020h  ; Load-Store Configuration
    DIS_SS                  EQU 28      ;   Family 15h:Disable Streaming Store functionality

IC_CFG                  EQU 0C0011021h  ; Instruction Cache Config Register
    IC_DIS_SPEC_TLB_RLD     EQU 9       ;   Disable speculative TLB reloads

DC_CFG                  EQU 0C0011022h  ; Data Cache Configuration
    DC_DIS_SPEC_TLB_RLD     EQU 4       ;   Disable speculative TLB reloads
    DC_DIS_SPEC_TLB_WALK    EQU 4       ;   Disable speculative table-walks
    DIS_HW_PF               EQU 13      ;   Hardware prefetches bit

CU_CFG                  EQU 0C0011023h  ; Family 15h: Combined Unit Configuration
    L2_WAY_LOCK_EN          EQU 23      ;   L2WayLock - L2 way lock enable
    L2_FIRST_LOCKED_WAY     EQU 19      ;   L2FirstLockedWay - first L2 way lockedh
    L2_FIRST_LOCKED_WAY_OR_MASK  EQU 000780000h

CU_CFG2                 EQU 0C001102Ah  ; Family 15h: Combined Unit Configuration 2

CU_CFG3                 EQU 0C001102Bh  ; Combined Unit Configuration 3
TW_CFG                  EQU 0C0011023h  ; Family 15h: Combined Unit Configuration
    COMBINE_CR0_CD          EQU 49      ;   Combine CR0.CD for both cores of a compute unit

L2I_CFG                 EQU 0C00110A0h  ; L2I Configuration
    L2_RINSER_DIS       EQU 20          ;   L2 rinser disable
    PREFETCHER_DIS      EQU 7           ;   L2 prefetcher disable
    CACHE_IC_ATTR_DIS   EQU 3           ;   Inserting IC attributes into the L2 disable

CR0_PE                  EQU 0           ; Protection Enable
CR0_NW                  EQU 29          ; Not Write-through
CR0_CD                  EQU 30          ; Cache Disable
CR0_PG                  EQU 31          ; Paging Enable

; CPUID Functions

CPUID_MODEL             EQU 1
    LOCAL_APIC_ID       EQU 24          ;   LocalApicId - initial local APIC physical ID

AMD_CPUID_L2Cache       EQU 80000006h   ; L2/L3 cache info
AMD_CPUID_APIC          EQU 80000008h   ; Long Mode and APIC info., core count
    APIC_ID_CORE_ID_SIZE     EQU 12     ; ApicIdCoreIdSize bit position
AMD_CPUID_EXT_APIC      EQU 8000001Eh   ; Extended APICID information

NB_CFG                  EQU 0C001001Fh  ; Northbridge Configuration Register
    INIT_APIC_ID_CPU_ID_LO   EQU 54     ;   InitApicIdCpuIdLo - is core# in high or low half of APIC ID?
    ENABLE_CF8_EXT_CFG       EQU 46     ;   EnableCf8ExtCfg - enable CF8 extended configuration cycles

MTRR_SYS_CFG            EQU 0C0010010h  ; System Configuration Register
  SYS_UC_LOCK_EN            EQU 17      ;   SysUcLockEn      System lock command enable
  MTRR_FIX_DRAM_EN          EQU 18      ;   MtrrFixDramEn    MTRR fixed RdDram and WrDram attributes enable
  MTRR_FIX_DRAM_MOD_EN      EQU 19      ;   MtrrFixDramModEn MTRR fixed RdDram and WrDram modification enable
  MTRR_VAR_DRAM_EN          EQU 20      ;   MtrrVarDramEn    MTRR variable DRAM enable

COMPUTE_UNIT_STATUS     EQU 08000C580h  ; Compute Unit Status Register
  QUAD_CORE                 EQU 24      ;   QuadCore         four cores of a compute unit are enabled
  DUAL_CORE                 EQU 16      ;   DualCore         two cores of a compute unit are enabled
  TRIPLE_CORE               EQU 8       ;   TripleCore       three cores of a compute unit are enabled
  CU_ENABLED                EQU 0       ;   Enabled          at least one core of a compute unit is enabled

; PCI Registers
FUNC_3                      EQU 3
MCA_NB_CFG                  EQU 44h     ; MCA NB Configuration
  CPU_ERR_DIS               EQU 6       ;   CPU error response disable

PRODUCT_INFO_REG1           EQU 1FCh    ; Product Information Register 1

; Local use flags, in upper most byte of ESI
FLAG_UNKNOWN_FAMILY               EQU 24    ; Signals that the family# of the installed processor is not recognized
FLAG_STACK_REENTRY                EQU 25    ; Signals that the environment has made a re-entry (2nd) call to set up the stack
FLAG_IS_PRIMARY                   EQU 26    ; Signals that this core is the primary within the compute unit
FLAG_CORE_NOT_IDENTIFIED          EQU 27    ; Signals that the cores/compute units of the installed processor is not recognized
FLAG_FORCE_32K_STACK              EQU 28    ; Signals to force 32KB stack size for BSP core
FLAG_DRAM_AVAILABLE               EQU 29    ; Signals that DRAM is present

; Error code returned in EDX by AMD_ENABLE_STACK_PRIVATE
IFNDEF CPU_EVENT_UNKNOWN_PROCESSOR_FAMILY
       CPU_EVENT_UNKNOWN_PROCESSOR_FAMILY     EQU   008010500h
ENDIF
IFNDEF CPU_EVENT_STACK_REENTRY
       CPU_EVENT_STACK_REENTRY                EQU   008020500h
ENDIF
IFNDEF CPU_EVENT_CORE_NOT_IDENTIFIED
       CPU_EVENT_CORE_NOT_IDENTIFIED          EQU   008030500h
ENDIF
IFNDEF CPU_EVENT_STACK_BASE_OUT_OF_BOUNDS
       CPU_EVENT_STACK_BASE_OUT_OF_BOUNDS     EQU   008040500h
ENDIF
IFNDEF CPU_EVENT_STACK_SIZE_INVALID
       CPU_EVENT_STACK_SIZE_INVALID           EQU   008050500h
ENDIF

; AGESA_STATUS values
IFNDEF AGESA_SUCCESS
       AGESA_SUCCESS  EQU 0
ENDIF
IFNDEF AGESA_WARNING
       AGESA_WARNING  EQU 4
ENDIF
IFNDEF AGESA_FATAL
       AGESA_FATAL    EQU 7
ENDIF
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

MAKE_SBDFO MACRO Seg, Bus, Dev, Fun, Off
    mov   eax, ((Seg SHL 28) OR (Bus SHL 20) OR (Dev SHL 15) OR (Fun SHL 12) OR (Off))
  ENDM

MAKE_EXT_PCI_ADDR MACRO Seg, Bus, Dev, Func, Offset
    mov   eax, ((1 SHL 31) OR (Seg SHL 28) OR (((Offset AND 0F00h) SHR 8) SHL 24) OR (Bus SHL 16) OR (Dev SHL 11) OR (Func SHL 8) OR (Offset AND 0FCh))
  ENDM

;---------------------------------------------------
; LoadTableAddress
;       Due to the various assembly methodologies used by BIOS vendors, this macro is needed to abstract the
;       loading of the address of a table. The default is the standard LEA instruction with table address.
;       The IBV that needs to use an alternative method can define their version of the macro prior to including
;       this file into their source.
;       An alternative example:
;         LoadTableAddress  MACRO MyTable
;           LEA   eax, -(LAST_ADDRESS - MyTable)
;---------------------------------------------------
IFNDEF LoadTableAddress
  LoadTableAddress        Macro TargetTable
       LEA   eax, TargetTable
  ENDM
ENDIF


;;***************************************************************************
;;
;;                      CPU STRUCTURES - PUBLIC
;;
;;***************************************************************************
CPU_FAMILY_INFO     STRUC
    L2_MIN_SIZE         WORD    ?       ; Minimum size of the L2 cache for this family, in K
    NUM_SHARED_CORES    BYTE    ?       ; Number of cores sharing an L2 cache
    L2_ALLOC_MEM        BYTE    ?       ; L2 space reserved for memory training, in K
    L2_ALLOC_EXE        WORD    ?       ; L2 space reserved for EXE CACHE, in K. 0 means unlimited.
    SIZE_ADDRESS_BUS    BYTE    ?       ; Number of address bits supported by this family
    FAMILY_RESERVED     BYTE    ?       ; reserved, pad to DWORD size
CPU_FAMILY_INFO     ENDS


CPU_DEADLOOP MACRO

@@:
    out     84h, al
    jmp     @B

ENDM



