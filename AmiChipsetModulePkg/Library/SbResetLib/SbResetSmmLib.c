//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//*************************************************************************
/** @file SbResetSmmLib.c
    This file contains code for SbResetSmmLib.c
    in the DXE stage.

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

// UDK Header
#include <PiSmm.h>
#include <Core/PiSmmCore/PiSmmCore.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Protocol/AmiUsbController.h>

#include <Token.h>

// Produced Protocols

// Consumed Protocols


VOID EFIAPI UpdateFchFullHardResetValue(BOOLEAN Value);
#if HW_REDUCE_ACDCTIMER_SUPPORT	
VOID EFIAPI UpdateHwReduceValue(BOOLEAN Value);
#endif
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

//VOID	*gSbResetReg = NULL;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

VOID ShutdownUsbLegacy(VOID)
{    
    AMI_USB_SMM_PROTOCOL *gAmiUsbSmmProtocol = NULL;
    API_FUNC        UsbLegacyControl;
    URP_STRUC       Urp;
    EFI_STATUS      Status; 
    
    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "SMM:Shutdown USB legacy in SMM\n\r"));
    Status = gSmst->SmmLocateProtocol(&gAmiUsbSmmProtocolGuid , NULL,
                                        &gAmiUsbSmmProtocol);
    if (!EFI_ERROR(Status)){        
        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "SMM:Shutdown USBAPI_UsbLegacyControl in UsbApiTable \n\r"));
        // USBAPI_UsbLegacyControl is the 18th API_FUNC in UsbApiTable.       
        UsbLegacyControl = (API_FUNC)gAmiUsbSmmProtocol->UsbApiTable[18];
        if (UsbLegacyControl != NULL) {
 //           Urp.bSubFunc = STOP_USB_CONTROLLER;
            Urp.SubFunc = STOP_USB_CONTROLLER; 
            UsbLegacyControl(&Urp);
        } 
    }
}

/**
    This function to construct the smm and runtime code for reset
    service.

               
    @param ImageHandle 
    @param SystemTable 

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SbResetSmmLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    BOOLEAN     Value;

    Value = PcdGetBool (PcdFchFullHardReset);
    UpdateFchFullHardResetValue(Value);
#if HW_REDUCE_ACDCTIMER_SUPPORT		
    Value = PcdGetBool(PcdReduceHardwareEnable);
    UpdateHwReduceValue(Value); // Update value for Runtime using.
#endif
    return Status;
}

