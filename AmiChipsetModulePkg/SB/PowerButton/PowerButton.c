//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//*************************************************************************
/** @file PowerButton.c
    Provide functions to register and handle Powerbutton
    functionality.

**/
//*************************************************************************

//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <Library/AmiCspSmmServicesLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/AmiFchIoAccessLib.h>
#include <Sb.h>

static BOOLEAN IsReduceHardwareEnable = FALSE;

/**
    If the power button is pressed, then this function is called.

    @param DispatchHandle Handle of dispatch function, for when interfacing
        with the parent SMM driver, will be the address of linked
        list link in the call back record.
    @param DispatchContext Pointer to the dispatch function's context.

    @retval VOID

**/
EFI_STATUS SbPwrBtnHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL
)
{
    /** PORTING REQUIRED **/
    if (IsReduceHardwareEnable){
     
#if  ( MODERN_STANDBY_POWER_BUTTON_BEHAVIOR == 0 )
      DEBUG(( DEBUG_INFO, "SbPwrBtnHandler(MS) : Please press 4s powerbutton for shutdown system.\n")); 
#else
      DEBUG(( DEBUG_INFO, "SbPwrBtnHandler(MS) : Update GPIO setting for powerbutton. \n")); 
      *(volatile UINT8 *)(SB_MMIO_BASE + GPIO_BANK0_BASE + 1 ) = 0xE3; // Update GPIO setting for powerbutton.       
#endif
    
    }
    return EFI_SUCCESS;
}

/**
    Installs South Bridge Power Button SMI Handler

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS
**/

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
    EFI_STATUS                              Status;
    EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *PowerButton;
    EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT   DispatchContext = {EfiPowerButtonEntry};
    EFI_HANDLE                              Handle = NULL;

    if (PcdGetBool(PcdReduceHardwareEnable)){

        IsReduceHardwareEnable = TRUE;
    }
    
    Status = gSmst->SmmLocateProtocol(
                      &gEfiSmmPowerButtonDispatch2ProtocolGuid,
                      NULL,
                      &PowerButton
                      );

    if (EFI_ERROR(Status)) return Status;

    Status = PowerButton->Register (
                            PowerButton,
                            SbPwrBtnHandler,
                            &DispatchContext,
                            &Handle
                            );

    return Status;
}

/**
    This is the entrypoint of the Power button driver.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS
**/

EFI_STATUS
EFIAPI
PowerButtonEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    return CspInitSmmHandler(ImageHandle, SystemTable, InSmmFunction);
}

