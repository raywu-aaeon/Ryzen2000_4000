//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//*************************************************************************
/** @file SbResetRtLib.c
    This file contains code for SbResetRtLib.c
**/
#include <Token.h>
#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Protocol/AmiUsbController.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
VOID EFIAPI UpdateFchFullHardResetValue(BOOLEAN Value);
#if HW_REDUCE_ACDCTIMER_SUPPORT	
VOID EFIAPI UpdateHwReduceValue(BOOLEAN Value);
#endif
//---------------------------------------------------------------------------
// Variable Declaration(s)
static EFI_EVENT    UsbProtocolRtEvent = NULL;

static EFI_USB_PROTOCOL *gUsbProtocol = NULL;

/**

    @param VOID

    @retval VOID

**/
VOID ShutdownUsbLegacy(VOID)
{
    if(gUsbProtocol != NULL) {
        if (UsbProtocolRtEvent != NULL) {
            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Shutdown USB legacy in runtime\n\r"));
            gUsbProtocol->UsbRtShutDownLegacy();
        }// end of UsbProtocolRtEvent!=NULL
    }
}

/**
    Get USB Protocol

        
    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

VOID
GetUsbProtocol (
  IN  EFI_EVENT                Event,
  IN  VOID                     *Context
  )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    Status = gBS->LocateProtocol(&gEfiUsbProtocolGuid, NULL, &gUsbProtocol);
    ASSERT(Status == EFI_SUCCESS);
    if (Event != NULL) gBS->CloseEvent(Event);
}

/**
    This function is the reset call interface function published
    by the reset

    @param VOID

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
RETURN_STATUS
EFIAPI
SbResetLibConstructor (
  )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    BOOLEAN     Value;
#if AMIUSB_SUPPORT
    VOID        *SbResetReg = NULL;

    UsbProtocolRtEvent = EfiCreateProtocolNotifyEvent(&gEfiUsbProtocolGuid, TPL_CALLBACK, GetUsbProtocol, NULL, &SbResetReg);
    ASSERT(UsbProtocolRtEvent != NULL);
#endif
    Value = PcdGetBool (PcdFchFullHardReset);
    UpdateFchFullHardResetValue(Value);
#if HW_REDUCE_ACDCTIMER_SUPPORT
    Value = PcdGetBool(PcdReduceHardwareEnable);
    UpdateHwReduceValue(Value); // Update value for Runtime using.
#endif    
    return Status;
}


