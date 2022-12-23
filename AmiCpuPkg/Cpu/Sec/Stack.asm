;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************

;**********************************************************************
;<AMI_FHDR_START>
;
; Name: Stack.asm
;
; Description:	Switch stack from CAR to permanent memory
;
;<AMI_FHDR_END>
;**********************************************************************

.686p
.model  FLAT, C
.code

;<AMI_PHDR_START>    
;-----------------------------------------------------------------------------
; Procedure: SecSwitchStack
;
; Description:
;   VOID EFIAPI SecSwitchStack( UINT32 OldStack, UINT32 NewStack )
;   Switch stack from CAR to permanent memory
;
; Input:
;   IN  UINT32  OldStack - pointer to old stack base
;   IN  UINT32  NewStack - pointer to new stack base
;
; Output:
;   VOID
;
; Notes:
;   Assuming that NewStack > OldStack, no checking made
;
;-----------------------------------------------------------------------------    
;<AMI_PHDR_END>

SecSwitchStack   PROC

        push    ecx
        push    edi
        push    esi
        push    eax

        mov     eax, [esp + 18h]        ; New stack base
        sub     eax, [esp + 14h]        ; EAX = bases offset

        mov     ecx, esp
        sub     ecx, [esp + 14h]        ; calculate ESP offset relative to base
        mov     edi, [esp + 18h]        ; New stack base
        add     edi, ecx
        mov     esi, esp
        mov     ecx, 7                  ; four regs + ret addr + two params, params can be ignored
        cld
        rep     movsd

        add     esp, eax                ; switch ESP
        add     ebp, eax                ; switch EBP

        pop     eax
        pop     esi
        pop     edi
        pop     ecx
        ret
SecSwitchStack   ENDP

    END

;**********************************************************************
;**********************************************************************
;**                                                                  **
;**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
;**                                                                  **
;**                       All Rights Reserved.                       **
;**                                                                  **
;**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
;**                                                                  **
;**                       Phone: (770)-246-8600                      **
;**                                                                  **
;**********************************************************************
;**********************************************************************
