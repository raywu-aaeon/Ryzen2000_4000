//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************

/** @file RsdpPlusLink.c 
	Contain E-link functions.

**/
//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include "ShadowRamProtocol.h"
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
SHADOW_RAM_PROTOCOL	*gShadowRamProtocol;

//---------------------------------------------------------------------------

/**
    BeforeEfiBootLaunchHook eLink function.
    
**/
VOID
EFIAPI
UpdateShadow(VOID)
{
	EFI_STATUS	Status;
    EFI_GUID    ShadowRamProtocolGuid = SHADOW_RAM_PROTOCOL_GUID;
	
	Status = gBS->LocateProtocol(&ShadowRamProtocolGuid, NULL, (VOID**) &gShadowRamProtocol);
    if(!EFI_ERROR(Status))
	    gShadowRamProtocol->UpdateShadowBeforEfiBoot();
		
	return;
}

/**
    AfterEfiBootLaunchHook eLink function.
    
**/
VOID
EFIAPI
EraseShadow(VOID)
{
	EFI_STATUS	Status;
	EFI_GUID    ShadowRamProtocolGuid = SHADOW_RAM_PROTOCOL_GUID;

	Status = gBS->LocateProtocol(&ShadowRamProtocolGuid, NULL, (VOID**) &gShadowRamProtocol);
    if(!EFI_ERROR(Status))
	    gShadowRamProtocol->EraseShadowAfterEfiBoot();
	
	return;
}

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
