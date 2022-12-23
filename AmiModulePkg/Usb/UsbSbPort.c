//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file UsbSb.c
    USB South Bridge Porting Hooks

**/

#include <AmiUsb.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/AmiUsbSmmGlobalDataValidationLib.h>
#include <Library/DxeSmmUsbSbLib.h>

/**
    This function is call to get SMI source.
    
    @param  SmiSource        Ptr to SMI source.
                             0x00: No SMI source enable. 
                             0x01: Timer SMI source is enable. 

    @retval EFI_UNSUPPORTED  This routine is not support.
            EFI_SUCCESS      Success to get SMI source.           
**/

EFI_STATUS
EFIAPI
GetSmiSource(
  IN UINT8  *SmiSource
)
{

    //
    // Get SMI source 
    //
    // *SmiSource  = 0x00  : No SMI enable
    // *SmiSource |= 0x01  : Timer SMI source is enable.   //PERIODIC_TIMER_SMI_SOURCE_IS_ENABLE
    //

    return  EFI_UNSUPPORTED;
}

/**
    This function is for enable/disable Timer SMI.
    @param  EnableSmi        TRUE: Enable timer SMI; otherwise, disable timer SMI.
    @retval EFI_STATUS       Status of the operation
**/

EFI_STATUS
EFIAPI
SettingTimerSMI(
  IN BOOLEAN  EnableSmi
){
   EFI_STATUS Status = EFI_SUCCESS;

   if (EnableSmi){
       //
       // Re-enable Periodic Timer SMI 
       //

   } else{        
       //
       // Disable Periodic Timer SMI
       //

   }
  return  Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
