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

//*************************************************************************
/** @file SbGetCapsuleFlagLib.c
    This file contains code for SbGetCapsuleFlagLib
    initialization in the PEI stage.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>
#include <Library/PciLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/DebugLib.h>

#include <Guid/CapsuleVendor.h>
#include <Ppi/ReadOnlyVariable2.h>

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

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    return Capsule Flag status.

    @param VOID

               
    @retval TRUE TRUE means capsule mode.
    @retval FALSE FALSE means not capsule mode.

    @note  .
**/
BOOLEAN
SbGetCapsuleFlag (
  )
{
	CONST EFI_PEI_SERVICES    		**PeiServices = GetPeiServicesTablePointer();
    EFI_STATUS                  	Status = EFI_SUCCESS;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
    UINTN                   		Size;
    BOOLEAN							CapsuleFlag = FALSE;

    Status = (*PeiServices)->LocatePpi( PeiServices,
                                &gEfiPeiReadOnlyVariable2PpiGuid,
                                0,
                                NULL,
                                &ReadOnlyVariable );
    if(!EFI_ERROR(Status)) {
		Size = 0;
		Status = ReadOnlyVariable->GetVariable(
										ReadOnlyVariable,
										EFI_CAPSULE_VARIABLE_NAME,
										&gEfiCapsuleVendorGuid,
										NULL,
										&Size,
										NULL
										);
		// if EFI_NOT_FOUND that means the EFI_CAPSULE_VARIABLE_NAME was cleared in the SecFlashUpdDxe_Init.
		// if EFI_BUFFER_TOO_SMALL that means we have capsule.
		if (Status == EFI_BUFFER_TOO_SMALL) {
			CapsuleFlag = TRUE;
		} else if (Status == EFI_NOT_FOUND) {
			CapsuleFlag = FALSE;
		}
    }
    return CapsuleFlag;
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
