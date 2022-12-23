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
;-------------------------------------------------------------------------
;
; Name:         CPUEarlyInit.ASM
;
; Description:  Program any workaround or initialization needed before
;               enabling Cache as memory in the SEC stage
;
;-------------------------------------------------------------------------
;<AMI_FHDR_END>

.586p
.xmm
.MODEL SMALL, C

;-------------------------------------------------------------------------
INCLUDE CPU.EQU
;-------------------------------------------------------------------------

; Externs
;-------------------------------------------------------------------------
EXTERN  SECCPU_EarlyInitEnd:NEAR32

IF MKF_AGESA_AP_INIT_BY_CMOS
EXTERN  GetApInitVectorEnd:NEAR32
ENDIF
;-------------------------------------------------------------------------
; Define the equates here

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG             SEGMENT         PARA PUBLIC 'CODE' USE32


;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SECCPU_EarlyInit
;
; Description:  This routine initializes CPU or perform the work arounds
;               needed before enabling cache as memory
;
; Input:        ESP     BIST Info
;               EBP     Reset ID (EDX at reset)
;               Stack not available
;
; Output:       None
;
; Modified:     All, except EBP and ESP
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

SECCPU_EarlyInit                PROC PUBLIC
; SAVE ESP in MMX register
        movd    mm0, esp
        mov     ecx, MSR_XAPIC_BASE             ; Enable local APIC
        rdmsr
        bts     eax, 11 ; Enable the APIC
        wrmsr
        movd    esp, mm0

        jmp     SECCPU_EarlyInitEnd
SECCPU_EarlyInit                ENDP


IF MKF_AGESA_AP_INIT_BY_CMOS
;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    GetApInitVector
;
; Description:  This routine gets the vector that AP will jump to
;
; Input:        None
;               Stack not available
;
; Output:       edi     - address that AP will jump to
;
; Modified:     edi, al, ecx
;
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

GetApInitVector     PROC    PUBLIC

        xor     edi, edi

        mov     al, MKF_AGESA_AP_INIT_CMOS_LOCATION_OFFSET + 3
        out     72h, al
        in      al, 73h
        movzx   edi, al
        shl     edi, 24

        mov     al, MKF_AGESA_AP_INIT_CMOS_LOCATION_OFFSET + 2
        out     72h, al
        in      al, 73h
        movzx   ecx, al
        shl     ecx, 16
        or      edi, ecx

        mov     al, MKF_AGESA_AP_INIT_CMOS_LOCATION_OFFSET + 1
        out     72h, al
        in      al, 73h
        movzx   ecx, al
        shl     ecx, 08
        or      edi, ecx

        mov     al, MKF_AGESA_AP_INIT_CMOS_LOCATION_OFFSET
        out     72h, al
        in      al, 73h
        movzx   ecx, al
        or      edi, ecx        ; edi is the address that AP will jump to

        jmp     GetApInitVectorEnd

GetApInitVector     ENDP

ENDIF   ;IF MKF_AGESA_AP_INIT_BY_CMOS

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  ENDS
;----------------------------------------------------------------------------
STARTUP_SEG             ENDS

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
