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

//*************************************************************************
/** @file SbRunSmm.c
    This file contains code for SouthBridge runtime SMM
    protocol

**/
//*************************************************************************

// Module specific Includes

#include "Token.h"
#include <Library/AmiCspSmmServicesLib.h>
#include <Library/AmiChipsetRuntimeServiceLib.h>

/**
    Submit runtime services both SMM and runtime.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
SbRuntimeServiceInit (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
    gRT->ResetSystem    = AmiChipsetResetSystem;
    gRT->GetTime        = AmiChipsetGetTime;
    gRT->SetTime        = AmiChipsetSetTime;
    gRT->GetWakeupTime  = AmiChipsetGetWakeupTime;
    gRT->SetWakeupTime  = AmiChipsetSetWakeupTime;

    return EFI_SUCCESS;
}

/**
    This function is the entry point for this SMM. This function
    installs the runtime services related to SB in SMM.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SbRuntimeSmmInitEntryPoint (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    return CspInitSmmHandler(ImageHandle, SystemTable, SbRuntimeServiceInit);
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
