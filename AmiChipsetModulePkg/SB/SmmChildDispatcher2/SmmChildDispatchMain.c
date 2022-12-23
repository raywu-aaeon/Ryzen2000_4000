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
/** @file SmmChildDispatchMain.c
    This file contains implementation of module entry point,
    generic RegisterHandler and UnregisterHandler routines
    and main dispatcher loop.

**/
//*************************************************************************

#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>
#include <AmiDxeLib.h>
#include <Token.h>
#include "SmmChildDispatch.h"
#include "SmmChildDispatchProtocol.h"
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmCpu.h>


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

EFI_STATUS
SwSmiHook (
  IN CONST EFI_GUID  *Protocol,
  IN VOID            *Interface,
  IN EFI_HANDLE      Handle
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// External Declaration(s)

// Function Definition(s)

/**
    This function implements main SMI dispatcher loop

    @param SmmImageHandle SMM image handle
    @param CommunicationBuffer pointer to optional communication buffer
    @param SourceSize pointer to size of communication buffer

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
ChildDispatcher (
  IN EFI_HANDLE           DispatchHandle,
  IN CONST VOID           *DispatchContext OPTIONAL,
  IN OUT VOID             *CommBuffer OPTIONAL,
  IN OUT UINTN            *CommBufferSize OPTIONAL
  )
{
/*    UINT32 Index;
    BOOLEAN HandledSmi;

    do
    {
        HandledSmi = FALSE;
        for(Index = EfiSmmSwSmi; Index < EfiSmmMaxSmi; Index++)
        {
            if(SmmHandler[Index].HandlerProtocol.GetContext != NULL &&
               SmmHandler[Index].HandlerProtocol.GetContext())
            {
                SmmHandler[Index].HandlerProtocol.DispatchSmi();
                HandledSmi = TRUE;
            }
        }
    } while (HandledSmi);

    ClearAllSmi();
*/
    return EFI_HANDLER_SUCCESS;
}

/**
    SMM Child Dispatcher module entry point

    @param ImageHandle Image handle
    @param SystemTable pointer to system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SmmChildDispatch2EntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
	EFI_STATUS		Status = EFI_SUCCESS;
	EFI_HANDLE		Handle;
	VOID			*Registration;

	//--gSmst->SmiManage();
	Status = gSmst->SmiHandlerRegister(ChildDispatcher, NULL, &Handle);

	Status = gSmst->SmmRegisterProtocolNotify(&gEfiSmmSwDispatch2ProtocolGuid, SwSmiHook, &Registration);

	return Status;
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
