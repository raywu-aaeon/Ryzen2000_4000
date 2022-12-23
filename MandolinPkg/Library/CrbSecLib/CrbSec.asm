        TITLE CRBSEC.ASM -- Chipset Reference Board SEC initialization
;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

;*************************************************************************
; $Header: $
;
; $Revision: $
;
; $Date: $
;*************************************************************************
;<AMI_FHDR_START>
;
; Name:         CrbSecLib.asm
;
; Description:  Program any workaround or initialization needed before
;               enabling Cache as memory in the SEC stage for CRB.
;
;<AMI_FHDR_END>
;*************************************************************************

;----------------------------------------------------------------------------
        INCLUDE token.equ
;----------------------------------------------------------------------------

.586P
.XMM
.MODEL SMALL, C

; Externs
EXTERN  SecCrb_EarlyInitEnd:NEAR32

; Define the equates here

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  STARTS
;----------------------------------------------------------------------------
STARTUP_SEG     SEGMENT     PARA PUBLIC 'CODE' USE32

;<AMI_PHDR_START>
;----------------------------------------------------------------------------
;
; Procedure:    SecCrb_EarlyInit
;
; Description:  This routine initializes CRB for PEI preparation
;
; Input:        ESP BIST Info
;               EBP Reset ID (EDX at reset)
;               Stack not available
;
; Output:       None
;
; Modified:     All, except EBP and ESP
;
; Notes:        NBSEC & SBSEC initialization is done at this point.
;----------------------------------------------------------------------------
;<AMI_PHDR_END>

SecCrb_EarlyInit     PROC PUBLIC


        jmp     SecCrb_EarlyInitEnd
SecCrb_EarlyInit     ENDP

;----------------------------------------------------------------------------
;       STARTUP_SEG  S E G M E N T  ENDS
;----------------------------------------------------------------------------
STARTUP_SEG     ENDS
END

;*************************************************************************
;*************************************************************************
;**                                                                     **
;**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
;**                                                                     **
;**                       All Rights Reserved.                          **
;**                                                                     **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
;**                                                                     **
;**                       Phone: (770)-246-8600                         **
;**                                                                     **
;*************************************************************************
;*************************************************************************

