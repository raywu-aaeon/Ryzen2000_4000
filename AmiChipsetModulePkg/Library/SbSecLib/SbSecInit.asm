;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
;
;**********************************************************************
;<AMI_FHDR_START>
;----------------------------------------------------------------------
;
; Name:     SbSecInit.asm
;
; Description:  Program any workaround or initialization needed before
;       enabling Cache as memory in the SEC stage
;
; Notes:    None of the chipset initialization is done at this point.
;       System is exactly as if came out of RESET.
;
;----------------------------------------------------------------------
;<AMI_FHDR_END>
;**********************************************************************
include token.equ

.586P
.XMM
.MODEL SMALL, C

; Externs
EXTERN  SECSB_EarlyInitEnd:NEAR32

; Define the equates here
PCI_INDEX           EQU 0CF8h
PCI_DATA            EQU 0CFCh
PCI_ENBIT           EQU 080000000h
MSR_XAPIC_BASE      EQU 01Bh
XAPIC_BASE_BSP_BIT  EQU 008d
;AMD SB800 LPC(ISA) Bridge...
SB_BUS              EQU 00h
SB_DEV              EQU 14h
SB_DEV_FUN          EQU ((SB_DEV SHL 3) + 3)
SB_BUS_DEV_FUN          EQU (((SB_BUS SHL 8) + SB_DEV_FUN) SHL 8)
;AMD SB800 SB PCI-to-PCI Bridge...
SBBR_BUS            EQU 00h
SBBR_DEV            EQU 14h
SBBR_DEV_FUN            EQU ((SBBR_DEV SHL 3) + 4)
SBBR_BUS_DEV_FUN        EQU (((SBBR_BUS SHL 8) + SBBR_DEV_FUN) SHL 8)
;SMBUS/ACPI Device...
SMBUS_BUS           EQU 00h
SMBUS_DEV           EQU 14h
SMBUS_DEV_FUN           EQU ((SMBUS_DEV SHL 3) + 0)
SMBUS_BUS_DEV_FUN       EQU ((SMBUS_BUS SHL 8) + SMBUS_DEV_FUN)
PM_IO_INDEX         EQU 0CD6H
PM_IO_DATA          EQU 0CD7H

SECSB_SIO_LPC_2E2F      = 0
SECSB_SERIAL_PORT       = 0
SECSB_DECODE_6064       = 0

IFDEF MKF_SB_SEC_DEBUG_MODE
SECSB_SERIAL_PORT       = 1
SECSB_SIO_LPC_2E2F      = 1
ENDIF

IFDEF MKF_SIO_SUPPORT
IF MKF_SIO_SUPPORT
SECSB_SIO_LPC_2E2F      = 1
SECSB_DECODE_6064       = 1
ENDIF
ENDIF

IFDEF MKF_AMDCRBEC_SUPPORT
IF MKF_AMDCRBEC_SUPPORT
SECSB_SIO_LPC_2E2F      = 1
SECSB_DECODE_6064       = 1
ENDIF
ENDIF

;-------------------------------------------------------
; replace above token
; That is for compatible new SIO component.
; The SIO_SUPPORT doesn't have "TargetEQU = Yes" in SDL.
;-------------------------------------------------------
IFDEF SECSB_SIO_SUPPORT
SECSB_SIO_LPC_2E2F      = 1
;;###SECSB_DECODE_6064      = 1
ENDIF

SECSB_LPC_PORT80 = MKF_SB_LPC_PORT80_SUPPORT
SECSB_PCI_PORT80 = MKF_SB_PCI_PORT80_SUPPORT

;; We need decode all of ROM, some PEIM in the FV_MAIN
SECSB_FLASH_DECODE = 1
SECSB_FLASH_SIZE = MKF_FLASH_SIZE
;----------------------------------------------------------------------------
;   STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG     SEGMENT     PARA PUBLIC 'CODE' USE32
;----------------------------------------------------------------------------
; Input: AH = Reg. number to be written
;    stack available
; Output: AL = Data
; Register destory: AX, DX
;------------------------------------------------------------------------------;
READ_IO_PMU MACRO
    mov     al, ah
    mov     dx, PM_IO_INDEX
    out     dx, al
    out     0edh, al                ; I/O delay
    out     0edh, al                ; I/O delay
    mov     dx, PM_IO_DATA
    in      al, dx
    out     0edh, al                ; I/O delay
    out     0edh, al                ; I/O delay

ENDM

;----------------------------------------------------------------------------
; Input: AH = Reg. number to be written
;    AL = Data to be written
;    stack available
; Output: NONE
; Register destory: AX, DX
;----------------------------------------------------------------------------
WRITE_IO_PMU MACRO
    xchg    al, ah  ;AL = Reg.
                    ;AH = Data
    mov     dx, PM_IO_INDEX
    out     dx, al
    out     0edh, al                ; I/O delay
    out     0edh, al                ; I/O delay
    xchg    al, ah
    mov     dx, PM_IO_DATA
    out     dx, al
    out     0edh, al                ; I/O delay
    out     0edh, al                ; I/O delay
ENDM

CKP_POINT MACRO TheCkp
    mov     al, TheCkp
    out     80h, al
ENDM

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECSB_EarlyInit
;
; Description:  This routine initializes South bridge for PEI preparation
;
; Input:    ESP BIST Info
;       EBP Reset ID (EDX at reset)
;       Stack not available
;
; Output:   None
;
; Modified: All, except EBP and ESP
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
SECSB_EarlyInit     PROC PUBLIC

    xor eax,eax

    CKP_POINT 04h
    xor eax,eax

    ;; init for BSP only
    mov ecx, MSR_XAPIC_BASE
    rdmsr
    bt  ax, XAPIC_BASE_BSP_BIT
    jnc SECSB_EarlyInitEnd ;; Not BSP

IFDEF MKF_CMOS_MANAGER_SUPPORT              ; (EIP46657.2+)
IF MKF_CMOS_MANAGER_SUPPORT                 ; (EIP46657.1)>
    mov ah, 059h                            ; PM_Reg 59: VRT_T2
    mov al, 10h                             ; 10h is the recommended value by AMD
    WRITE_IO_PMU
ENDIF                                       ; <(EIP46657.1)
ENDIF                                       ; (EIP46657.2+)

    ;;
    ;; Enable following Io decoding -
    ;;    0x20, 0x21, 0xA0, 0xA1 (PIC);
    ;;    0x40, 0x41, 0x42, 0x43, 0x61 (8254 timer);
    ;;    0x70, 0x71, 0x72, 0x73 (RTC);
    ;;    0x92.
    ;;
    mov     ah, 00h
    READ_IO_PMU
    or      al, 001h
    WRITE_IO_PMU

;;Check CMOS offset MKF_CMOS_BAD_CHECK_ADDRESS
    mov al,MKF_CMOS_BAD_CHECK_ADDRESS
    out 72h,al
    in al,73h
    cmp al,0aah
    jz  SkipCheckCMOS
    
    ;; Check CMOS status
    mov bh, 2Dh                             ; Check CMOS 10h~2Dh
    mov bl, 10h
CheckCMOSReset:
    mov al, bl
    out 70h, al
    jmp $+2
    in  al, 71h
    jmp $+2
    cmp al, 0h
    jnz SkipCheckCMOS
    inc bl
    cmp bl,bh
    jle CheckCMOSReset
    mov al, 0Eh                             ; Reset CMOS 0Eh as 0xFF
    out 70h, al
    jmp $+2
    mov al, 0FFh
    out 71h, al
    jmp $+2

    mov al,MKF_CMOS_BAD_CHECK_ADDRESS
    out 72h,al
    mov al,55h
    out 73h,al                          ;Reset CMOS MKF_CMOS_BAD_CHECK_ADDRESS as 0x55
    
SkipCheckCMOS:

    ;; Select CMOS Bank0
    mov     al, 0ah
    out     70h, al
    jmp     $+2
    in      al, 71h
    jmp     $+2
    and     al, 0EFh                        ; Clear bit 4 = select bank0
    out     71h, al
    jmp     $+2

    ;;
    ;; Disable BootTimer (watch dog)
    ;;
    mov ah, 47h
    READ_IO_PMU
    or al, 80h
    WRITE_IO_PMU


    ;;
    ;; Enable LPC bridge
    ;;
    mov     ah, 0ECh
    READ_IO_PMU
    or      al, 001h
    WRITE_IO_PMU

IF SECSB_SIO_LPC_2E2F
    ;;
    ;; decode 2e/2f,4e/4f,
    ;;
    mov dx,PCI_INDEX
    mov eax,(PCI_ENBIT + SB_BUS_DEV_FUN + 048h)
    out dx,eax
    mov dx,PCI_DATA
    mov al, 03h     ;; 2e/2f, 4e/4f
    out dx,al
ENDIF

IF SECSB_DECODE_6064
    ;;
    ;; LPC decode 0x60 and 0x64
    ;;
    mov dx,PCI_INDEX
    mov eax,(PCI_ENBIT + SB_BUS_DEV_FUN + (047h AND (NOT 3)))
    out dx,eax
    mov dx,(PCI_DATA+(047h AND 3))
    in  al,dx
    or  al,(1 SHL 5)
    out dx,al
ENDIF

IF SECSB_SERIAL_PORT
    ;; AMD Serial Port decode
    mov dx,PCI_INDEX
    mov eax,(PCI_ENBIT + SB_BUS_DEV_FUN + 044h)
    out dx,eax
    mov dx,PCI_DATA
    in  al,dx
    or  al,040h ;; port 0
    ;;###or  al,0C0h ;; port 0 and 1
    out dx,al
ENDIF

IF SECSB_FLASH_DECODE
    ;;
    ;; We need decode all of ROM, some PEIM in the FV_MAIN
    ;; Enable Top 4G Flash map for MicroCode update
    ;;
    mov dx,PCI_INDEX
    mov eax,(PCI_ENBIT + SB_BUS_DEV_FUN + 06Ch)
    out dx,eax
    mov dx,PCI_DATA
    mov eax,-1
    mov al,NOT ((SECSB_FLASH_SIZE SHR 16)-1)
    out dx,eax
ENDIF

IF SECSB_LPC_PORT80
    ;; AMD LPC PORT 80 decode
    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SB_BUS_DEV_FUN + (04Ah AND (NOT 3)))
    out dx, eax
    mov dx, (PCI_DATA + (04Ah AND 3))
    in  al, dx
    or  al, 020h
    out dx, al
ENDIF ; IF SECSB_LPC_PORT80

IF SECSB_PCI_PORT80
    ;; AMD PCI PORT 80 decode
    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SBBR_BUS_DEV_FUN + (04Bh AND (NOT 3)))
    out dx, eax
    mov dx, (PCI_DATA + (04Bh AND 3))
    in  al, dx
    or  al, 0d0h
    out dx, al

    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SBBR_BUS_DEV_FUN + 040h)
    out dx, eax
    mov dx, PCI_DATA
    in  al, dx
    and al, 0dfh
    or  al, 020h
    out dx, al

    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SBBR_BUS_DEV_FUN + 050h)
    out dx, eax
    mov dx, PCI_DATA
    in  al, dx
    and al, 02h
    or  al, 01h
    out dx, al

    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SBBR_BUS_DEV_FUN + 01ch)
    out dx, eax
    mov dx, PCI_DATA
    in  al, dx
    and al, 00h
    or  al, 0f0h
    out dx, al

    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SBBR_BUS_DEV_FUN + (01dh AND (NOT 3)))
    out dx, eax
    mov dx, (PCI_DATA + (01dh AND 3))
    in  al, dx
    and al, 00h
    or  al, 00h
    out dx, al

    mov dx, PCI_INDEX
    mov eax, (PCI_ENBIT + SBBR_BUS_DEV_FUN + 04h)
    out dx, eax
    mov dx, PCI_DATA
    in  al, dx
    and al, 00h
    or  al, 021h
    out dx, al
ENDIF ; IF SECSB_PCI_PORT80

    jmp SECSB_EarlyInitEnd
SECSB_EarlyInit     ENDP

;----------------------------------------------------------------------------
;   STARTUP_SEG  S E G M E N T  ENDS
;----------------------------------------------------------------------------
STARTUP_SEG     ENDS

END
;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
