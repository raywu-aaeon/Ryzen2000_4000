//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file SbSmi.c
    This file contains code for all South Bridge SMI events

*/

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <Library/AmiCspSmmServicesLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)

#define AMI_SMM_SW_DISPATCH_PROTOCOL EFI_SMM_SW_DISPATCH2_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_REGISTER_CONTEXT
#define AMI_SMM_SX_DISPATCH_PROTOCOL EFI_SMM_SX_DISPATCH2_PROTOCOL
#define AMI_SMM_SX_DISPATCH_CONTEXT  EFI_SMM_SX_REGISTER_CONTEXT
#define SMM_CHILD_DISPATCH_SUCCESS   EFI_SUCCESS

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//----------------------------------------------------------------------------

/**
    This is a template SB SMI GetContext for Porting.

    @param VOID

    @retval BOOLEAN

    @note  Here is the control flow of this function:
              1. Check if SB SMI source.
              2. If yes, return TRUE.
              3. If not, return FALSE.
**/
BOOLEAN GetSbSmiContext (VOID)
{
        return FALSE;
}

/**
    This is a template SB SMI Handler for Porting.

    @param VOID

    @retval VOID
**/
VOID SbSmiHandler (VOID)
{

}

/**
    This is a template SB software SMI Handler for Porting.

    @param DispatchHandle - SMI dispatcher handle
    @param DispatchContext - Points to an optional S/W SMI context
    @param CommBuffer - Points to the optional communication buffer
    @param CommBufferSize - Points to the size of the optional
                            communication buffer

    @retval EFI_STATUS if the new SMM PI is applied.
**/
EFI_STATUS SbSwSmiHandler (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
{
//    WRITE_IO8(0x80, SB_SWSMI);
    return SMM_CHILD_DISPATCH_SUCCESS;
}

/**
    This is a template SB Sx SMI Handler for Porting.

    @param DispatchHandle - SMI dispatcher handle
    @param DispatchContext - Points to an optional Sx SMI context
    @param CommBuffer - Points to the optional communication buffer
    @param CommBufferSize - Points to the size of the optional
                            communication buffer

    @retval EFI_STATUS if the new SMM PI is applied.
**/
EFI_STATUS SbSxSmiHandler (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
{
    return SMM_CHILD_DISPATCH_SUCCESS;
}

/**
    South Bridge SMM Child Dispatcher Handler.

    @param DispatchHandle - SMI dispatcher handle
    @param DispatchContext - Pointer to the dispatched context
    @param CommBuffer - Pointer to a collection of data in
                        memory that will be conveyed from a
                        non-SMM environment into an SMM 
                        environment 
    @param CommBufferSize - Pointer to the size of the CommBuffer

    @retval EFI_STATUS

    @note  Here is the control flow of this function:
              1. Read SMI source status registers.
              2. If source, call handler.
              3. Repeat #2 for all sources registered.
**/
EFI_STATUS SbChildDispatcher (
  IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
{
    if (GetSbSmiContext()) SbSmiHandler();

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------

/**
    Installs South Bridge SMM Child Dispatcher Handler.

    @param ImageHandle - Image handle
    @param SystemTable - Pointer to the system table

    @retval EFI_STATUS
**/
EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS                   Status;
    AMI_SMM_SW_DISPATCH_PROTOCOL *pSwDispatch;
    AMI_SMM_SX_DISPATCH_PROTOCOL *pSxDispatch;
    AMI_SMM_SW_DISPATCH_CONTEXT  SwContext = {SB_SWSMI};
    AMI_SMM_SX_DISPATCH_CONTEXT  SxContext = {SxS3, SxEntry};
    EFI_HANDLE                   Handle;
    EFI_HANDLE                   RootHandle;

    Status  = gSmst->SmmLocateProtocol( &gEfiSmmSwDispatch2ProtocolGuid, \
                                        NULL, \
                                        &pSwDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSwDispatch->Register( pSwDispatch, \
                                         SbSwSmiHandler, \
                                         &SwContext, \
                                         &Handle );
    }

    Status  = gSmst->SmmLocateProtocol( &gEfiSmmSxDispatch2ProtocolGuid, \
                                        NULL, \
                                        &pSxDispatch );
    if (!EFI_ERROR(Status)) {
        Status  = pSxDispatch->Register( pSxDispatch, \
                                         SbSxSmiHandler, \
                                         &SxContext, \
                                         &Handle );
    }

    Status  = gSmst->SmiHandlerRegister( SbChildDispatcher, \
                                         NULL, \
                                         &RootHandle );

    return Status;
}

/**
    Installs South Bridge SMM Child Dispatcher Handler.

    @param ImageHandle - Image handle
    @param SystemTable - Pointer to the system table

    @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
InitializeSbSmm (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    return CspInitSmmHandler(ImageHandle, SystemTable, InSmmFunction);
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
