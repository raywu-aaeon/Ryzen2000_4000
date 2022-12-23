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
/** @file ResetSmi.c
    Provide functions to register and handle SW SMI
    functionality.  

**/
//*************************************************************************

#include <Token.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Library/AmiCspSmmServicesLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>

#define AMI_SMM_SW_DISPATCH_PROTOCOL EFI_SMM_SW_DISPATCH2_PROTOCOL
#define AMI_SMM_SW_DISPATCH_CONTEXT  EFI_SMM_SW_REGISTER_CONTEXT


/**
    This is a software SMI Handler for OS Reset workaround.

    @param DispatchHandle 
    @param Context OPTIONAL,
    @param CommBuffer OPTIONAL,
    @param CommBufferSize OPTIONAL

    @retval VOID
**/

EFI_STATUS
OSResetSwSmiHandler (
  IN EFI_HANDLE	DispatchHandle,
  IN CONST VOID	*Context OPTIONAL,
  IN OUT VOID  	*CommBuffer OPTIONAL,
  IN OUT UINTN 	*CommBufferSize OPTIONAL
  )
{
	EFI_STATUS						Status = EFI_SUCCESS;

    if (CommBuffer != NULL) {
        if (((EFI_SMM_SW_CONTEXT*)CommBuffer)->CommandPort == ACPI_RESET_REG_VALUE) {
        	IoWrite8(0xCF9,0x06);//workaround to avoid system hang 0x11 when do reset in win7 and ubuntu os.
			while(1) {}
        }
    }
    return Status;
}

/** @file
    Install SW SMI Handlers for south bridge.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
    EFI_STATUS                      Status;
	EFI_SMM_SW_DISPATCH2_PROTOCOL  	*SwDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT     SwContext = {ACPI_RESET_REG_VALUE};
    EFI_HANDLE                      Handle = NULL;
	
    Status  = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, &SwDispatch);
    ASSERT_EFI_ERROR(Status);
    if (!EFI_ERROR(Status)) {
        Status  = SwDispatch->Register( SwDispatch, \
        		                         OSResetSwSmiHandler, \
                                         &SwContext, \
                                         &Handle );
        ASSERT_EFI_ERROR(Status);
    }
    return Status;
}
/**
    This function Registers SW SMI functionality.

    @param ImageHandle Handle for this FFS image
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
InitResetSmi(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{
#if OS_RESET_WORKAROUND
    return CspInitSmmHandler(ImageHandle, SystemTable, InSmmFunction);
#else
    return EFI_SUCCESS;
#endif
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
