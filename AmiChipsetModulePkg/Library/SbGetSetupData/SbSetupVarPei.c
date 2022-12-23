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

/** @file SbSetupVarPei.c
    This file contains code for SbSetupVarPei initialization in the PEI stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
//#include <PiPei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/PeiServicesTablePointerLib.h>

#include <Token.h>
// AMI Compatibility header
#include <Setup.h> // Optional. should use Mde Library instead.


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

static EFI_GUID gSetupGuid = SETUP_GUID;

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function get SETUP_DATA in DXE phase.

    @param SetupData Pointer to a SETUP data buffer.
    @param Service Pointer to the service. this is backward compatible.

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
SbSetupVar (
  IN OUT SETUP_DATA		*SetupData
  )
{
    EFI_STATUS                  	Status = EFI_SUCCESS;
    CONST EFI_PEI_SERVICES   		**PeiServices = GetPeiServicesTablePointer();
    EFI_PEI_READ_ONLY_VARIABLE2_PPI	*ReadOnlyVariable = NULL;
    UINTN                           VariableSize = sizeof(SETUP_DATA);

	Status = (*PeiServices)->LocatePpi(
								PeiServices, \
								&gEfiPeiReadOnlyVariable2PpiGuid, \
								0, \
								NULL, \
								&ReadOnlyVariable );

	if (!EFI_ERROR(Status)) {
		Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
												L"Setup", \
												&gSetupGuid, \
												NULL, \
												&VariableSize, \
												SetupData );
	}


    return Status;
}

/**
    !!! DO NOT USE THIS FUNCTION !!!
    This is a backward compatible function to return the gRT or PeiService for old function.

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

VOID*
EFIAPI
SbGetService (
  VOID
  )
{
	return (VOID*)GetPeiServicesTablePointer();
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
