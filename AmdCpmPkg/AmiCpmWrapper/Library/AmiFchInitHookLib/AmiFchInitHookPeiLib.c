//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiFchInitHookPeiLib.c
    This file contains code for AmiFchInitHookPeiLib initialization in the PEI stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiPei.h>

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
    This function is the FCH Hook for FchPlatformPTPeiInit.

    @param FchPTData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
AmiFchPlatformPTPeiInit (
  IN      VOID                          *FchPTData
  )
{
	return EFI_SUCCESS;
}

/**
    This function is the FCH Hook for FchPlatformOemPeiInit.

    @param FchData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
AmiFchPlatformOemPeiInit (
  IN      VOID                          *FchData
  )
{
	return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
