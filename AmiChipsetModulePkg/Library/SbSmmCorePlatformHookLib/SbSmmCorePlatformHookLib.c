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

/** @file SbSmmCorePlatformHookLib.c
    This file contains code for South Bridge SMM Core Platform Hook

*/

#include <Library/SmmCorePlatformHookLib.h>
#include <Token.h>
#include <Library/AmiSmmLib.h>


/**
    Performs South Bridge specific tasks before/after invoking registered SMI 
    handlers.

    @param SaveContext - TRUE = Save / FALSE = Restore

    @retval EFI_SUCCESS - The South Bridge platform hook completes 
                          successfully.

**/
VOID
SbPlatformHookBeforeAfterSmmDispatch (
    IN BOOLEAN        SaveContext
    )
{
    SbSmmSaveRestoreStates (SaveContext);
}

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
