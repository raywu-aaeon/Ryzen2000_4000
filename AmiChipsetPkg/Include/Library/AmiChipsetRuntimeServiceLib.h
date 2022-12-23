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

/** @file AmiChipsetRuntimeServiceLib.h
  This file contains AMI chipset porting runtime server library functions 
  and data structure definitions.

*/

#ifndef _AMI_RUNTIME_SERVICE_SMM_LIB_H_
#define _AMI_RUNTIME_SERVICE_SMM_LIB_H_
#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Uefi.h>

//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------
typedef EFI_STATUS (EFIAPI SB_RUN_RESET_CALLBACK) (
  IN  EFI_RESET_TYPE  ResetType
);

typedef VOID (EFIAPI SB_INIT_RTC_CALLBACK) (
    VOID
);

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------

/**
    This function is the interface for the reset function.
        
    @param ResetType Type of reset to perform
    @param ResetStatus System status that caused the reset.  if part of 
           normal operation then this should be EFI_SUCCESS, Otherwise it 
           should reflect the state of the system that caused it.
    @param DataSize Size in bytes of the data to be logged
    @param ResetData Pointer to the data buffer that is to be logged - OPTIONAL
         
    @retval EFI_DEVICE_ERROR Even though it should never get that far

**/
EFI_STATUS
EFIAPI
AmiChipsetResetSystem (
	IN EFI_RESET_TYPE	ResetType,
	IN EFI_STATUS    	ResetStatus,
	IN UINTN         	DataSize,
	IN CHAR16        	*ResetData OPTIONAL
);

/**
    Return the current date and time
        
    @param Time Current time filled in EFI_TIME structure
    @param Capabilities Time capabilities (OPTIONAL)

    @retval EFI_SUCCESS		Always

    @note  
       Here is the control flow of this function:
       1. Read the original time format 12/24 hours and BCD/binary.
       2. Set the format to 24 hrs and binary.
       3. Read the 2 digit year.
       4. Add either 1900 or 2000, so the year is between 1998 - 2097.
       5. Read the month, day, hour, minute, second.
       6. Set the nanosecond to 0.
       7. Set the time to zone to unspecified.
       8. Set daylight savings value to 0.
       9. Restore the original time format.
       10. Set Capabilities with 1 second Resolution, 0 Accuracy (Unknown), 
           and False SetsToZero.
       11. Return EFI_SUCCESS.

**/
EFI_STATUS 
EFIAPI
AmiChipsetGetTime (
    OUT EFI_TIME                *Time,
    OUT EFI_TIME_CAPABILITIES   *Capabilities OPTIONAL
);

/**
    Sets the RTC time
        
    @param Time Time to set
         
    @retval EFI_SUCCESS Time is Set
    @retval EFI_INVALID_PARAMETER Time to Set is not valid.

    @note  
       Here is the control flow of this function:
       1. Read the original time format 12/24 hours and BCD/binary.
       2. Set the format to 24 hrs and binary.
       3. Verify the time to set. If it is an invalid time,
          restore the time format and return EFI_INVALID_PARAMETER.
       4. Change the 4 digit year to a 2 digit year.
       5. Stop the RTC time.
       6. Store time and data on the RTC.
       7. Read the month, day, hour, minute, second.
       8. Start the RTC time.
       9. Restore the original time format.
       10. Return EFI_SUCCESS.

**/
EFI_STATUS 
EFIAPI
AmiChipsetSetTime (
    IN EFI_TIME     *Time
);

/**
    Read the wake time. Read the status if it is enabled or if the system
    has woken up.
        
    @param Enabled Flag indicating the validity of wakeup time
    @param Pending Check if wake up time has expired.
    @param Time Current wake up time setting

    @retval EFI_SUCCESS (Always)

    @note  
       Here is the control flow of this function:
       1. Read the original time format 12/24 hours and BCD/binary.
       2. Set the format to 24 hrs and binary.
       3. Read the status if the wake up time is enabled or if it has expired.
       4. Set the wakeup time.
       5. Restore the original time format.
       6. Return EFI_SUCCESS.

**/
EFI_STATUS 
EFIAPI
AmiChipsetGetWakeupTime (
    OUT BOOLEAN     *Enabled,
    OUT BOOLEAN     *Pending,
    OUT EFI_TIME    *Time
);

/**
    Enable/disable and set wakeup time
        
    @param Enable Flag indicating whether to enable/disable the time
    @param Time Time to set as the wake up time - OPTIONAL
         
    @retval EFI_SUCCESS Time is Set and/or Enabled/Disabled.
    @retval EFI_INVALID_PARAMETER Invalid time or enabling with a NULL Time.

    @note  
      Here is the control flow of this function:
       1. Read the original time format 12/24 hours and BCD/binary.
       2. If Time is not NULL,
          a. Verify the wakeup time to set. If it is an invalid time,
             restore the time format and return EFI_INVALID_PARAMETER.
         	b. Set the wakeup time.
       3. If Time is NULL and Enable is true, restore original time format
          and return EFI_INVALID_PARAMETER.
       4. Enable/Disable wakeup.
       5. Restore the original time format.
       6. Return EFI_SUCCESS.

**/
EFI_STATUS 
EFIAPI
AmiChipsetSetWakeupTime (
    IN BOOLEAN      Enable,
    IN EFI_TIME     *Time OPTIONAL
);

/**
    This function initializes RTC

    @param VOID

    @retval VOID

**/
VOID 
EFIAPI
InitRtc (
    VOID
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif //_AMI_RUNTIME_SERVICE_SMM_LIB_H_
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

