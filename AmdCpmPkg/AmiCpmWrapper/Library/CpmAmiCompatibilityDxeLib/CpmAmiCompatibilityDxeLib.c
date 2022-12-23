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

//*************************************************************************
/** @file CpmAmiCompatibilityDxeLib.c
    This file contains code for CpmAmiCompatibilityDxeLib.c
    in the DXE stage.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
//#include <AmdCpmDxe.h>
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PciLib.h>
#include <Library/S3PciLib.h>

// Produced Protocols

// Consumed Protocols


// AMI Compatibility Header.

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
    CPM need to depend on this protocol.

    @retval VOID

**/
VOID
InsatllAmdCpmProtocol (
  VOID
  )
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_HANDLE Handle = NULL;

    Status = gBS->InstallProtocolInterface (
    					&Handle,
    					&gAmdCpmAllPciIoProtocolsInstalledProtocolGuid,
    					EFI_NATIVE_INTERFACE,
    					NULL
    					);
    ASSERT_EFI_ERROR (Status);
}


/**
    This function is the entry point for CpmAmiCompatibilityDxeLib driver.
    This function initializes the CpmAmiCompatibilityDxeLib in DXE phase.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  .
**/

EFI_STATUS
EFIAPI
CpmAmiCompatibilityDxeLibInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS              Status = EFI_SUCCESS;
/*    UINT32					VidDid;

    //
    // Pci R/W and boot script sample by Mde library.
    //
    VidDid = PciRead32(PCI_LIB_ADDRESS(0, 0, 0, 0));
    S3PciWrite32(PCI_LIB_ADDRESS(0, 0, 0, 0),VidDid);
*/
    return Status;
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
