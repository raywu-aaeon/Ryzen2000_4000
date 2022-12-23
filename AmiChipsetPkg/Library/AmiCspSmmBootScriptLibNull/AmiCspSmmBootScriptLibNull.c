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

/** @file AmiCspSmmBootScriptLibNull.c
    This file contains code for AmiCspSmmBootScriptLibNull base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <Uefi.h>
#include <Protocol/S3SaveState.h>

// AMI Compatibility header


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
  Check if SMM lock

  @retval TRUE           	SMM is locked.
  @retval FALSE           	SMM is not locked.

**/

BOOLEAN
EFIAPI
CspIsSwitchBootScriptToSmm (
  )
{
	return FALSE;
}

/**
  Redirect S3 boot script to SMM

  @param  This                  A pointer to the EFI_S3_SAVE_STATE_PROTOCOL instance.
  @param  OpCode                The operation code (opcode) number.
  @param  ...                   Argument list that is specific to each opcode.

  @retval EFI_SUCCESS           NULL library just return.

**/
EFI_STATUS
EFIAPI
CspSaveBootScriptToSmm (
  IN CONST EFI_S3_SAVE_STATE_PROTOCOL      *This,
  IN       UINT16                           OpCode,
  ...
  )
{
	return EFI_SUCCESS;
}

/**
  Return a wrapper function.

  @retval NULL           Not support.

**/
EFI_S3_SAVE_STATE_PROTOCOL*
EFIAPI
CspGetBootScriptWrapper (
  )
{
	return NULL;
}

/**
  The constructor function initialize the AmiCspSmmBootScriptLibNull Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

RETURN_STATUS
EFIAPI
AmiCspSmmBootScriptLibNullConstructor (
  VOID
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    return Status;
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
