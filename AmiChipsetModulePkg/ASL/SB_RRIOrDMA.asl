//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

Scope(\_SB)
{
    Scope(PCI0)
    {
        Scope(SBRG)
        {
/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    RRIO
;
; Description:  Dummy control method. Required when I/O Positive decoding's disabled
;  Input: Nothing
;  Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
    Method(RRIO, 4) { Store("RRIO", Debug) }

/*
;<AMI_PHDR_START>
;------------------------------------------------------------------------
;
; Procedure:    rDMA
;
; Description:  Dummy control method. Required when I/O Positive decoding's disabled
;  Input: Nothing
;  Output: Nothing
;
;-------------------------------------------------------------------------
;<AMI_PHDR_END>
*/
    Method(rDMA, 3) { Store("rDMA", Debug) }

        } // End Scope(SBRG)
    } // End Scope(PCI0)
} // End Scope (\_SB)

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************