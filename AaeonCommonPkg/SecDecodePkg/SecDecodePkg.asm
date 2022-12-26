
 INCLUDE token.equ

.586P
.XMM
.MODEL SMALL,C
.code

; Externs
EXTERN SecDecodePkg_EarlyInitEnd:NEAR32

;PUBLIC SecDecodePkg_EarlyInit

; Define the equates here
BIT00          equ 00000001h
BIT01          equ 00000002h
BIT02          equ 00000004h
BIT03          equ 00000008h
BIT04          equ 00000010h
BIT05          equ 00000020h
BIT06          equ 00000040h
BIT07          equ 00000080h
BIT08          equ 00000100h
BIT09          equ 00000200h

PCI_LPC_BASE   equ 8000F800h

LPC_IO_DEC     equ 80h
LPC_GEN1_DEC   equ 84h
LPC_GEN2_DEC   equ 88h
LPC_GEN3_DEC   equ 8Ch
LPC_GEN4_DEC   equ 90h
IO_DEC_DEFAULT equ 370F0010h

PCI_P2SB_BASE  equ 8000F900h

P2SB_PCICMD     equ 04h
P2SB_SBREG_BAR  equ 010h
P2SB_HIDING_REG equ 0E0h
PCR_DMI_PID     equ 0EFh
PCR_DMI_LPCLGIR1 equ 2730h       ; LPC Generic I/O Range 1
PCR_DMI_LPCLGIR2 equ 2734h       ; LPC Generic I/O Range 2
PCR_DMI_LPCLGIR3 equ 2738h       ; LPC Generic I/O Range 3
PCR_DMI_LPCLGIR4 equ 273Ch       ; LPC Generic I/O Range 4
PCR_DMI_LPCIOD equ 2770h
PCR_DMI_LPCIOE equ 2774h

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure: SecDecodePkg_EarlyInit
;
; Description: This routine initializes South bridge for PEI preparation
;
; Input: ESP BIST Info
;  EBP Reset ID (EDX at reset)
;  Stack not available
;
; Output: None
;
; Modified: All, except EBP and ESP
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>
SecDecodePkg_EarlyInit  PROC NEAR PUBLIC
IF MKF_PCH_IO_DECODE_IN_SEC
 IF MKF_PCH_DMI_IO_DECODE
 	;Make sure P2SB is not hidden
        mov dx, 0CF8h
        mov eax, (PCI_P2SB_BASE + P2SB_HIDING_REG)
        out dx, eax
        add dx, 04h
        in  eax, dx
        and eax, 0FFFFFEFFh
        out dx, eax

 	;Set P2SB Base Address
        mov dx, 0CF8h
        mov eax, (PCI_P2SB_BASE + P2SB_SBREG_BAR)
        out dx, eax
        add dx, 04h
        mov eax, MKF_PCR_BASE_ADDRESS
        out dx, eax

 	;Set Memory Space Enable (MSE) for P2SB Base MMIO
        mov dx, 0CF8h
        mov eax, (PCI_P2SB_BASE + P2SB_PCICMD)
        out dx, eax
        add dx, 04h
        in  eax, dx
        or  eax, BIT01
        out dx, eax

 	;Point to P2SB DMI MMIO Base Address
        mov edi, (MKF_PCR_BASE_ADDRESS + (PCR_DMI_PID SHL 16))

	mov eax, MKF_PCH_LPC_IO_DECODE_RANGE
        mov dword ptr[edi + PCR_DMI_LPCIOD], eax
        mov eax, (MKF_PCH_LPC_IO_DECODE_EN AND 00FFh)
        mov dword ptr[edi + PCR_DMI_LPCIOE], eax
 ENDIF	; MKF_PCH_DMI_IO_DECODE
  
 ;Enable LPC IO decoding
        mov dx, 0CF8h
        mov eax, (PCI_LPC_BASE + LPC_IO_DEC)
        out dx, eax
        add dx, 04h
        mov eax, (MKF_PCH_LPC_IO_DECODE_EN shl 16) + (MKF_PCH_LPC_IO_DECODE_RANGE)
        out dx, eax

 IF MKF_PCH_GEN_DECODE_RANGE_1
 ;Enable Generic Decode Range 1 decoding
        mov dx, 0CF8h
        mov eax, (PCI_LPC_BASE + LPC_GEN1_DEC) ; 84h
        out dx, eax
        add dx, 04h
        mov eax, ((MKF_PCH_GEN_DECODE_RANGE_1 AND 0FFFFh) OR (MKF_PCH_GEN_DECODE_MASK_1 SHL 16))
        bts eax, 0
        out dx, eax

	IF MKF_PCH_DMI_IO_DECODE
          mov dword ptr[edi + PCR_DMI_LPCLGIR1], eax
        ENDIF	; MKF_PCH_DMI_IO_DECODE
 ENDIF

 IF MKF_PCH_GEN_DECODE_RANGE_2
 ;Enable Generic Decode Range 2 decoding
        mov dx, 0CF8h
        mov eax, (PCI_LPC_BASE + LPC_GEN2_DEC) ; 88h
        out dx, eax
        add dx, 04h
        mov eax, ((MKF_PCH_GEN_DECODE_RANGE_2 AND 0FFFFh) OR (MKF_PCH_GEN_DECODE_MASK_2 SHL 16))
        bts eax, 0
        out dx, eax

	IF MKF_PCH_DMI_IO_DECODE
          mov dword ptr[edi + PCR_DMI_LPCLGIR2], eax
        ENDIF	; MKF_PCH_DMI_IO_DECODE
 ENDIF

 IF MKF_PCH_GEN_DECODE_RANGE_3
 ;Enable Generic Decode Range 3 decoding
        mov dx, 0CF8h
        mov eax, (PCI_LPC_BASE + LPC_GEN3_DEC) ; 8Ch
        out dx, eax
        add dx, 04h
        mov eax, ((MKF_PCH_GEN_DECODE_RANGE_3 AND 0FFFFh) OR (MKF_PCH_GEN_DECODE_MASK_3 SHL 16))
        bts eax, 0
        out dx, eax

	IF MKF_PCH_DMI_IO_DECODE
          mov dword ptr[edi + PCR_DMI_LPCLGIR3], eax
        ENDIF	; MKF_PCH_DMI_IO_DECODE
 ENDIF

 IF MKF_PCH_GEN_DECODE_RANGE_4
 ;Enable Generic Decode Range 4 decoding
        mov dx, 0CF8h
        mov eax, (PCI_LPC_BASE + LPC_GEN4_DEC) ; 90h
        out dx, eax
        add dx, 04h
        mov eax, ((MKF_PCH_GEN_DECODE_RANGE_4 AND 0FFFFh) OR (MKF_PCH_GEN_DECODE_MASK_4 SHL 16))
        bts eax, 0
        out dx, eax

	IF MKF_PCH_DMI_IO_DECODE
          mov dword ptr[edi + PCR_DMI_LPCLGIR4], eax
        ENDIF	; MKF_PCH_DMI_IO_DECODE
 ENDIF
ENDIF  ; IF MKF_PCH_IO_DECODE_IN_SEC
        jmp SecDecodePkg_EarlyInitEnd
SecDecodePkg_EarlyInit  ENDP

END
