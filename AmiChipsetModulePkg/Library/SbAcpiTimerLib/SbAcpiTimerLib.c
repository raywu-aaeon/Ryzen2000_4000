//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file SbAcpiTimerLib.c
    This file contains south bridge related TimeLib library
    instance

**/
//**********************************************************************

// Module specific Includes
//#include "Efi.h"
#include "Uefi.h"
#include "Token.h"
#include "Sb.h"
#include <AmiCspLib.h>
#include <Library/IoLib.h>


/**
    This function delays for the number of micro seconds passed in

    @param DelayTime Number of microseconds(us) to delay

    @retval UINTN Value passed in for microseconds delay

**/

UINTN
EFIAPI
MicroSecondDelay(
    IN  UINTN   DelayTime
    )
{
    // The following code is to generate delay for specified amount
    //    of micro seconds using ACPI timer.
    UINTN       TicksNeeded;
    UINT32      TimerValue, NewTimerValue;
    UINTN       OverFlow;
    UINTN       TheRest, EndValue;
    UINT16      BaseAddr;


    // Set up timer to point to the ACPI Timer register
    BaseAddr = PM_BASE_ADDRESS + ACPI_IOREG_PM1_TMR; 

    // There are 3.58 ticks per us, so we have to convert the number of us passed
    //  in to the number of ticks that need to pass before the timer has expired
    // Convert us to Ticks, don't loose significant figures or as few as possible
    //  do integer math in ticks/tens of ns and then divide by 100 to get ticks
    //  per us
    OverFlow = 0;

    TheRest = TicksNeeded = (DelayTime * 358) / 100;

    // 32 bits corresponds to approz 71 mins  no delay should be that long
    // otherwise
    // Get the number of times the counter will have to overflow to delay as long
    // as needed
    if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) {
        // compiler error when NUM_BITS_IN_ACPI_TIMER=32
        //#### OverFlow = TicksNeeded / (1 << NUM_BITS_IN_ACPI_TIMER);
        //#### TheRest = TicksNeeded % (1 << NUM_BITS_IN_ACPI_TIMER);
    }

    // read ACPI Timer
    TimerValue = IoRead32(BaseAddr);

    // need to adjust the values based off of the start time
    EndValue = TheRest + TimerValue;

    // check for overflow on addition.  possibly a problem
    if (EndValue < TimerValue) {
      OverFlow++;
    }
    // here make sure that EndValue is less than the max value
    // of the counter
    else if (NUM_BITS_IN_ACPI_TIMER < MAX_ACPI_TIMER_BITS) {
      // compiler error when NUM_BITS_IN_ACPI_TIMER=32
      //### OverFlow += EndValue / (1 << NUM_BITS_IN_ACPI_TIMER);
      //### EndValue = EndValue % (1 << NUM_BITS_IN_ACPI_TIMER);
    }

    // let the timer wrap around as many times as calculated
    while (OverFlow) {
        // read timer amd look to see if the new value read is less than
        // the current timer value.  if this happens the timer overflowed
        NewTimerValue = IoRead32(BaseAddr);

        if (NewTimerValue < TimerValue)
          OverFlow--;

        TimerValue = NewTimerValue;
    }

    // now wait for the correct number of ticks that need to occur after
    //  all the needed overflows
    while (EndValue > TimerValue) {
        NewTimerValue = IoRead32(BaseAddr);

        // check to see if the timer overflowed.  if it did then
        // the time has elapsed. Because EndValue should be greater than TimerValue
        if (NewTimerValue < TimerValue)
            break;

        TimerValue = NewTimerValue;
    }

    return DelayTime;
}


UINT64
EFIAPI
GetPerformanceCounter (
  VOID
  )
{
  return (UINT64)IoRead32(PM_BASE_ADDRESS + ACPI_IOREG_PM1_TMR);
}

UINT64
EFIAPI
GetPerformanceCounterProperties (
  OUT      UINT64                    *StartValue,  OPTIONAL
  OUT      UINT64                    *EndValue     OPTIONAL
  )
{
  if (StartValue != NULL) {
    *StartValue = 0;
  }

  if (EndValue != NULL) {
    *EndValue = 0xFFFFFFFF;
  }

  return 3579545;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
