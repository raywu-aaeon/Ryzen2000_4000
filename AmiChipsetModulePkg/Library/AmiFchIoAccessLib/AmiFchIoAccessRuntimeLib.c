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

/** @file AmiFchIoAccessRuntimeLib.c
    This file contains code for AmiFchIoAccessRuntimeLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
// UDK header
#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/DebugLib.h>
#include <Guid/EventGroup.h>

#include <Token.h>
// AMI Compatibility header


//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------

EFI_STATUS
EFIAPI
AmiFchIoAccessLibConstructor (
  VOID
  );

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------

extern EFI_PHYSICAL_ADDRESS mInternalFchAcpiMmioBase;

EFI_EVENT		mAmiFchIoAccessRuntimeLibVirtualNotifyEvent = NULL;

// Function Definition(s)

//---------------------------------------------------------------------------


/**
  Convert the physical FCH MMIO addresses.
  to virtual addresses.

  @param[in]    Event   The event that is being processed.
  @param[in]    Context The Event Context.
**/
VOID
EFIAPI
AmiFchIoAccessRuntimeLibVirtualNotify (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  //
  // Convert table pointer that is allocated from EfiRuntimeServicesData to a virtual address.
  //
  EfiConvertPointer (0, (VOID **) &mInternalFchAcpiMmioBase);
}

/**
  The constructor function initialize the AmiFchIoAccessRuntimeLib Library

  @retval EFI_SUCCESS   The constructor always returns RETURN_SUCCESS.

**/

RETURN_STATUS
EFIAPI
AmiFchIoAccessRuntimeLibConstructor (
  VOID
  )
{
  EFI_STATUS  Status;

  AmiFchIoAccessLibConstructor();
  //
  // Register SetVirtualAddressMap () notify function
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  AmiFchIoAccessRuntimeLibVirtualNotify,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &mAmiFchIoAccessRuntimeLibVirtualNotifyEvent
                  );
  ASSERT_EFI_ERROR (Status);

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
