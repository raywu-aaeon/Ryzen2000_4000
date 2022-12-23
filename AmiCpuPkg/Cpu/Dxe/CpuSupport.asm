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
;-----------------------------------------------------------------------
;
; Name:		CPUSupport.asm
;
; Description:	This is the CPU support file that contains assembly
;		language routines for the DXE CPU Module.  This file
;		also contains the default interrupt handlers.
;
;-----------------------------------------------------------------------
;<AMI_FHDR_END>

ifndef EFIx64

.686p
.model  flat        
.code

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure:	TempGPInterruptHandler
;
; Description: This routine returns from a NULL interrupt for GPF generated
;
; Input:
;      IN EFI_EXCEPTION_TYPE   Exception
;      IN EFI_SYSTEM_CONTEXT   Context
;
; Output:
;      None
;---------------------------------------------------------------------------
;<AMI_PHDR_END>

_TempGPInterruptHandler PROC
	mov esp, 0
	ret
_TempGPInterruptHandler ENDP

else
.code

;<AMI_PHDR_START>
;---------------------------------------------------------------------------
;
; Procedure:	TempGPInterruptHandler
;
; Description: This routine returns from a NULL interrupt for GPF generated
;
; Input:
;      IN EFI_EXCEPTION_TYPE   Exception
;      IN EFI_SYSTEM_CONTEXT   Context
;
; Output:
;      None
;---------------------------------------------------------------------------
;<AMI_PHDR_END>

TempGPInterruptHandler  PROC
	mov rsp, 0
	ret
TempGPInterruptHandler  ENDP

AsmIret PROC
        iretq
AsmIret ENDP

endif

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
