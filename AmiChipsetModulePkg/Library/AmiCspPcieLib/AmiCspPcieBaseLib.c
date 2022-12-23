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

/** @file AmiCspPcieBaseLib.c
    Chipset Pci Express Library implementation

*/

#include <Uefi.h>
#include <Library/PcdLib.h>

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

// GUID Definition(s)

// Protocol/Ppi Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//Generic PCIE Library porting hooks

/**
  Gets the base address of PCI Express.
  
  This internal functions retrieves PCI Express Base Address via a PCD entry
  PcdPciExpressBaseAddress.
  
  @return The base address of PCI Express.

**/
UINTN
CspGetPciExpressBaseAddress (
  VOID
  )
{
  return (UINTN) PcdGet64 (PcdPciExpressBaseAddress);
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
