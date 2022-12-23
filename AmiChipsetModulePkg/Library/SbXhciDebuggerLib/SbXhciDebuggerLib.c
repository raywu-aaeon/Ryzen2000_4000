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

/** @file SbXhciDebuggerLib.c
    This file contains code for SbXhciDebuggerLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <Base.h>
#include <Uefi.h>
#include <Library/DebugLib.h>


#include <Token.h>
// AMI Compatibility header


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef VOID FCH_TASK_ENTRY (IN VOID *FchCfg);

// Function Prototype(s)
VOID  FchInitEnvUsbXhci          (IN VOID  *FchDataPtr);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)
extern FCH_TASK_ENTRY *FchInitEnvTasksTable[];

// Function Definition(s)

//---------------------------------------------------------------------------


/**
  The dummy routine to replace AMD DXE XHCI code for Debugger.

**/

VOID
DummyFunction (
  IN  VOID     *FchDataPtr
  )
{

}

/**
  The constructor function to skip AMD DXE XHCI code for Debugger.

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

RETURN_STATUS
EFIAPI
SbXhciDebuggerLibConstructor (
  VOID
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
#if defined (USB_3_DEBUG_SUPPORT) && (USB_3_DEBUG_SUPPORT == 1)
#if defined (AMI_DEBUGGER_SUPPORT) && (AMI_DEBUGGER_SUPPORT == 1)
    UINTN						i = 0;
    FCH_TASK_ENTRY				*gHookFunc = &FchInitEnvUsbXhci;

    do {
    	if (FchInitEnvTasksTable[i] == gHookFunc) {
    		FchInitEnvTasksTable[i] = &DummyFunction;
    		break;
    	}
    	i++;
    } while (FchInitEnvTasksTable[i] != NULL);
#endif
#endif
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
