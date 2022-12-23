;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************

;<AMI_FHDR_START>
;----------------------------------------------------------------------
;
; Name:     AmiCpmWrapperSECInit.asm.
;
; Description:  Program any workaround or initialization needed before
;       enabling Cache as memory in the SEC stage
;
; Notes:    None of the chipset initialization is done at this point.
;       System is exactly as if came out of RESET.
;
;----------------------------------------------------------------------
;<AMI_FHDR_END>
.586p
.xmm
.MODEL SMALL, C

;-------------------------------------------------------------------------
INCLUDE Token.equ
;-------------------------------------------------------------------------
; Externs
EXTERN  SECCPM_EarlyInitEnd:NEAR32

AMD_MSR_MMIO_CFG_BASE = 0C0010058h  ;MSRC001_0058 MMIO Configuration Base Address

IFNDEF MKF_PCIEX_LENGTH
MKF_PCIEX_LENGTH =10000000h
ENDIF

IFNDEF MKF_PCIEX_BASE_ADDRESS
MKF_PCIEX_BASE_ADDRESS =0e0000000h
ENDIF

;----------------------------------------------------------------------------
;   STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG     SEGMENT     PARA PUBLIC 'CODE' USE32


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECCPM_EarlyInit
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
SECCPM_EarlyInit     PROC PUBLIC

IFDEF MKF_CPM_SEC_PCIE_BASE_ENABLED AND MKF_CPM_SEC_PCIE_BASE_ENABLED EQ 1

    mov ebx, MKF_PCIEX_LENGTH
    shr ebx,20  ;Align 1M
    mov eax, ebx
    bsf eax, ebx
    jnz EncodedSize
    mov al,32
EncodedSize:
    shl eax,2		; BusRange [BIT2:5]
    or eax,1		; enable the MMIO
    or eax,MKF_PCIEX_BASE_ADDRESS;MMIO SPACE Base [BIT20:47]
    xor edx,edx
    mov ecx,AMD_MSR_MMIO_CFG_BASE
    wrmsr

ENDIF
    jmp SECCPM_EarlyInitEnd
SECCPM_EarlyInit     ENDP

;----------------------------------------------------------------------------
;   STARTUP_SEG  S E G M E N T  ENDS
;----------------------------------------------------------------------------
STARTUP_SEG     ENDS

END
;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
