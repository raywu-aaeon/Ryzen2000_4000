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

/** @file AmiFchInitHookDxeLib.c
    This file contains code for AmiFchInitHookDxeLib.c
    in the DXE stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiDxe.h>

// Produced Protocols

// Consumed Protocols

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

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
    This function is the FCH Hook for FchPlatformImcDxeInit.

    @param FchImcData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
AmiFchPlatformImcDxeInit (
  IN      VOID                          *FchImcData
  )
{
	return EFI_SUCCESS;
}

/**
    This function is the FCH Hook for FchPlatformPTDxeInit.

    @param FchPTData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
AmiFchPlatformPTDxeInit (
  IN      VOID                          *FchPTData
  )
{
  return EFI_SUCCESS;
}

/**
    This function is the FCH Hook for FchPlatformOemDxeInit.

    @param FchData FCH parameter

    @retval EFI_STATUS EFI_SUCCESS

    @note  .
**/

EFI_STATUS
EFIAPI
AmiFchPlatformOemDxeInit (
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
