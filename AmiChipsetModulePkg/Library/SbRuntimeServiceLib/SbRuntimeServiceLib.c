//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SbRuntimeServiceLib.c
    This file contains code for South Bridge runtime protocol

*/


// Module specific Includes
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/Rtc.h>
#include <Library/AmiChipsetRuntimeServiceLib.h>
#include <SbElinks.h>
#include <Library/AmiSbMiscLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <AmiStatusCodes.h>

#include <Library/RtcLib.h>

// Produced Protocols
#include <Protocol/Reset.h>
#include <Protocol/RealTimeClock.h>
#include <Protocol/Timer.h>

//----------------------------------------------------------------------------
//          Variable Declaration
//----------------------------------------------------------------------------
EFI_EVENT ResetEvent;
static BOOLEAN Runtime = FALSE;
static BOOLEAN  gTimeOut = FALSE;
static UINT16 gTimeZone;
static UINT8  gDaylight;

//This the number of days in a month - 1. (0 Based)
UINT8       DaysInMonth[] = {30, 27, 30, 29, 30,\
                                29, 30, 30, 29, 30, 29, 30};


static TIME_VARIABLE CachedTimeVariable;
static BOOLEAN CachedTimeVariableValid = FALSE;

// Function Prototypes
typedef VOID (SB_RESET_CALLBACK) (
    IN EFI_RESET_TYPE           ResetType,
    IN EFI_STATUS               ResetStatus,
    IN UINTN                    DataSize,
    IN VOID                     *ResetData OPTIONAL
);

// Function Definitions
extern SB_RESET_CALLBACK SB_RESET_CALLBACK_LIST EndOfList;
extern SB_INIT_RTC_CALLBACK SB_INIT_RTC_CALLBACK_LIST EndOfList1;
SB_RESET_CALLBACK* SbResetCallbackList[] = { SB_RESET_CALLBACK_LIST NULL };
SB_INIT_RTC_CALLBACK* SbInitRtcCallbackList[] = { SB_INIT_RTC_CALLBACK_LIST NULL };
//----------------------------------------------------------------------------
//   USUALLY NO PORTING REQUIRED FOR THE FOLLOWING ROUTINES
//----------------------------------------------------------------------------


/**
    This function is the interface for the reset function.  In
    the future, this may allow for a shared library for DXE and PEI.

    @param ResetType Type of reset to perform
    @param ResetStatus System status that caused the reset.  if part
        of normal operation then this should be
        EFI_SUCCESS, Otherwise it should reflect the
        state of the system that caused it
    @param DataSize Size in bytes of the data to be logged
    @param ResetData OPTIONAL      Pointer to the data buffer that is to be logged

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
EFIAPI
AmiChipsetResetSystem (
    IN EFI_RESET_TYPE   ResetType,
    IN EFI_STATUS       ResetStatus,
    IN UINTN            DataSize,
    IN CHAR16           *ResetData OPTIONAL
    )
{
    UINT32                  Index;

    for (Index = 0; SbResetCallbackList[Index] != NULL; Index++) {
      SbResetCallbackList[Index](ResetType, ResetStatus, DataSize, ResetData);
    }

    // do a cold reset of the system
    SBLib_ResetSystem (ResetType);

    // This should not get here
    return EFI_SUCCESS;
}

/**
    This function initializes RTC

    @param VOID

    @retval VOID

**/
VOID 
EFIAPI
InitRtc(VOID)
{
    UINT32                  Index;
    
#if !EXTERNAL_RTC_SUPPORT
    WriteRtcIndex(RTC_REG_B_INDEX, 0x82);
    WriteRtcIndex(RTC_REG_A_INDEX, 0x26);
    ReadRtcIndex(RTC_REG_C_INDEX);
    WriteRtcIndex(RTC_REG_B_INDEX, 0x02);
#endif
    
    for (Index = 0; SbInitRtcCallbackList[Index] != NULL; Index++) {
      SbInitRtcCallbackList[Index]();
    }
}

/**
    Enables Disables RTC Date and Time update cicles.

    @param Enable TRUE or FALSE to Enable\Disabe RTC Update.

    @retval VOID

**/
VOID SetUpdate(
    IN BOOLEAN Enable
)
{
    RTC_REG_B       RegB;
    UINT8           Set = (Enable) ? 0 : 1;

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    if (RegB.Set != Set) {
        RegB.Set = Set;
        WriteRtcIndex(RTC_REG_B_INDEX, RegB.REG_B);
    }
}

/**
    Check if RTC Date and Time update in progress and waits till
    it's over.

    @param VOID

    @retval VOID

**/
VOID CheckUpdateCmplete (VOID)
{
    volatile RTC_REG_A  RegA;
    UINTN               TimeOut = 0;

    RegA.REG_A = ReadRtcIndex(RTC_REG_A_INDEX);
    while (RegA.UpdInProgr) {
        RegA.REG_A = ReadRtcIndex(RTC_REG_A_INDEX);
        TimeOut++;
        if (TimeOut >= 0x0fffff) {
            gTimeOut = TRUE;
            return;
        }
    }

    gTimeOut = FALSE;
}

/**
    Returns an index that represents the day of the week of the date passed in

        
    @param Time pointer to EFI_TIME structure

        UINT8
    @retval d returns the index to the day of the week.  0 = Sunday, 1 = Monday ... 6 = Saturday

**/
UINT8 GetDayOfTheWeek (
    IN EFI_TIME         *Time
)
{
    UINT16      a;
    UINT16      m;
    UINT16      d;
    UINT16      y;

    a = (14 - Time->Month) / 12;
    y = Time->Year - a;
    m = Time->Month + 12 * a - 2;
    d = (Time->Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

    return (UINT8)d;
}

/**
    This routine verifies is this year leap year or not

    @param Time pointer to EFI_TIME structure

               
    @retval TRUE if this year is leap year
    @retval FALSE if this year is not leap year

**/
BOOLEAN IsLeapYear (
    IN EFI_TIME     *Time )
{
    if (Time->Year % 4 == 0) {
        if (Time->Year % 100 == 0) {
            if (Time->Year % 400 == 0) {
                return TRUE;
            } else {
                return FALSE;
            }
        } else {
            return TRUE;
        }
    } else {
        return FALSE;
    }
}

/**
    This routine verifies if time and data if needed, before
    setting the RTC

    @param Time Time to verify with

               
    @retval TRUE if valid time and date
    @retval FALSE if invalid time and date

    @note  Here is the control flow of this function:
              1. Decrease month and date to change to 0-base
              2. Validate Year, Month and Day. If invalid, return FALSE.
              3. Validate Hour, Minute, and Second. If invalid, return FALSE.
              4. Return True.

**/
BOOLEAN VerifyTime(
    IN EFI_TIME *Time
)
{
    //Always check these to satisfy EFI compliancy test even for setting wake-up time.
    UINT8 Month = Time->Month - 1;
    UINT8 Day   = Time->Day - 1;

    if (Time->Year < EARLIEST_YEAR || Time->Year > MAXIMUM_YEAR) return FALSE;
    if (Month > 11) return FALSE;             //0 based month
    if ((Month != 1) || (!IsLeapYear(Time))) { // Not leap year or not February.
        if (Day > DaysInMonth[Month]) return FALSE; //All values already adjusted for 0 based.
    } else {
        if (Day > 28) return FALSE; //February
    }

    if (Time->Hour > 23) return FALSE;
    if (Time->Minute > 59) return FALSE;
    if (Time->Second > 59) return FALSE;

    //Check these to satisfy EFI compliancy test.
    if (Time->Nanosecond > 999999999) return FALSE; //999,999,999
    if (Time->TimeZone < -1440) return FALSE;
    if (Time->TimeZone > 1440 && Time->TimeZone != \
                        EFI_UNSPECIFIED_TIMEZONE) return FALSE;

    return TRUE;
}

/**
    Check if RTC Mode and Format have appropriate values and sets
    them if necessary

    @param Set if true, force Rtc to 24 hour mode and binary format

    @retval EFI_SUCCESS Rtc mode and format have appropriate values
    @retval EFI_DEVICE_ERROR Rtc mode and/or format are invalid

**/
EFI_STATUS CheckRtc(
    IN BOOLEAN Set
)
{
    RTC_REG_B   RegB;

    //Check RTC Conditions and stuff
    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);

    if(RegB.Mode == 0 || RegB.Format == 1) {
        if(Set) {
            RegB.Mode = 1;                  // 0 - 12 hour mode              1 - 24 hour mode
            RegB.Format = 0;                // 0 - BCD Format                1 - Binary Format
            WriteRtcIndex(RTC_REG_B_INDEX,RegB.REG_B);
        } else {
            return EFI_DEVICE_ERROR;
        }
    }
    return EFI_SUCCESS;
}

/**
    Return the current date and time

    @param Time Current time filled in EFI_TIME structure
    @param Capabilities Time capabilities (OPTIONAL)

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  Here is the control flow of this function:
              1. Read the original time format 12/24 hours and BCD/binary.
              2. Set the format to 24 hrs and binary.
              3. Read the 2 digit year.
              4. Add either 1900 or 2000, so the year is between 1998 - 2097.
              5. Read the month, day, hour, minute, second.
              6. Set the nanosecond to 0.
              7. Set the time to zone to unspecified.
              8. Set daylight savings value to 0.
              9. Restore the original time format.
              10. Set Capabilities with 1 sec Resolution, 0 Accuracy (Unknown), and False SetsToZero.
              11. Return EFI_SUCCESS.

**/

EFI_STATUS
EFIAPI
AmiChipsetGetTime (
    OUT EFI_TIME                *Time,
    OUT EFI_TIME_CAPABILITIES   *Capabilities OPTIONAL
)
{
    EFI_STATUS    Status;
    UINT8         Year;
    BOOLEAN       IntState; //SmiState;
    UINTN         TimeVarSize = sizeof(TIME_VARIABLE);
//-------------------------
    if (Time == NULL) return EFI_INVALID_PARAMETER;
    //Check RTC Conditions (24h Mode and BCD is ON)
    Status=CheckRtc(FALSE);
    if(EFI_ERROR(Status)) return Status;
    //Get SMI State and disable it
    //SmiState=SbLib_GetSmiState();
//    SbLib_SmiDisable();
    //Get INTERRUPT State and disable it
    IntState = GetInterruptState();
    DisableInterrupts();
    // Wait till RTC is safe to read,
    CheckUpdateCmplete();
    if(gTimeOut) {
        InitRtc();
    }

    // After control comes back, we will have 488 u's to read data.
    Time->Second    = ReadRtcIndex(RTC_SECONDS_REG);
    Year            = ReadRtcIndex(RTC_YEAR_REG);
    Time->Month     = ReadRtcIndex(RTC_MONTH_REG);
    Time->Day       = ReadRtcIndex(RTC_DAY_OF_MONTH_REG);
    Time->Hour      = ReadRtcIndex(RTC_HOURS_REG);
    Time->Minute    = ReadRtcIndex(RTC_MINUTES_REG);
    if (Time->Second > ReadRtcIndex(RTC_SECONDS_REG)) {
      Year            = ReadRtcIndex(RTC_YEAR_REG);
      Time->Month     = ReadRtcIndex(RTC_MONTH_REG);
      Time->Day       = ReadRtcIndex(RTC_DAY_OF_MONTH_REG);
      Time->Hour      = ReadRtcIndex(RTC_HOURS_REG);
      Time->Minute  = ReadRtcIndex(RTC_MINUTES_REG);
      Time->Second  = ReadRtcIndex(RTC_SECONDS_REG);
    }

    //Restore SMIs and INTERRUPT State
    if(IntState) EnableInterrupts();
//    if(SmiState) SbLib_SmiEnable();

    //This Register is not affected by UIP bit so read it very last.
    // If RTC Year only 1 digit, EFI spec says years rang is 1998 - 2097
    Time->Year = ReadRtcIndex(ACPI_CENTURY_CMOS) * 100 + Year;
    Time->Nanosecond= 0;

    if(CachedTimeVariableValid) {
        Time->TimeZone  = CachedTimeVariable.TimeZone;
        Time->Daylight  = CachedTimeVariable.Daylight;
    } else {
        Status = gRT->GetVariable(
                        L"EfiTime",
                        &gEfiTimeVariableGuid,
                        NULL,
                        &TimeVarSize,
                        &CachedTimeVariable
                        );

        if (EFI_ERROR(Status)) {
            CachedTimeVariable.TimeZone = EFI_UNSPECIFIED_TIMEZONE;
            CachedTimeVariable.Daylight = 0;
        }

        Time->TimeZone  = CachedTimeVariable.TimeZone;
        Time->Daylight  = CachedTimeVariable.Daylight;
        CachedTimeVariableValid = TRUE;
    }


    if (Capabilities != NULL) {
        Capabilities->Resolution = 1;
        Capabilities->Accuracy = 0;
        Capabilities->SetsToZero = 0;
    }

    return  EFI_SUCCESS;
}

/**
    Sets the RTC time

    @param Time Time to set

               
    @retval EFI_SUCCESS Time is Set
    @retval EFI_INVALID_PARAMETER Time to Set is not valid.

    @note  Here is the control flow of this function:
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
)
{
    EFI_STATUS    Status = EFI_SUCCESS;

    //Check RTC Conditions and stuff
    CheckRtc(TRUE);

    if (Time == NULL) return EFI_INVALID_PARAMETER;
    if (!VerifyTime(Time)) return EFI_INVALID_PARAMETER;

    SetUpdate(FALSE);
    WriteRtcIndex(ACPI_CENTURY_CMOS, Time->Year / 100);
    WriteRtcIndex(RTC_YEAR_REG, Time->Year % 100);
    WriteRtcIndex(RTC_MONTH_REG,Time->Month);
    WriteRtcIndex(RTC_DAY_OF_MONTH_REG,Time->Day);
    // calculate the day of the week. Add 1, because Algorithm is 0 based and RTC is 1 based
    WriteRtcIndex(RTC_DAY_OF_WEEK_REG, GetDayOfTheWeek(Time) + 1);
    WriteRtcIndex(RTC_HOURS_REG,Time->Hour);
    WriteRtcIndex(RTC_MINUTES_REG,Time->Minute);
    WriteRtcIndex(RTC_SECONDS_REG,Time->Second);
    SetUpdate(TRUE);

    if(CachedTimeVariableValid &&
       CachedTimeVariable.TimeZone == Time->TimeZone &&
       CachedTimeVariable.Daylight == Time->Daylight)
        return EFI_SUCCESS;

    CachedTimeVariable.TimeZone  = Time->TimeZone;
    CachedTimeVariable.Daylight  = Time->Daylight;
    Status = gRT->SetVariable(
                        L"EfiTime",
                        &gEfiTimeVariableGuid,
                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                        sizeof(TIME_VARIABLE),
                        &CachedTimeVariable
                        );
    if(!EFI_ERROR(Status))
        CachedTimeVariableValid = TRUE;


    return  Status;
}

/**
    Read the wake time. Read the status if it is enabled or
    if the system has woken up.   

    @param Enabled Flag indicating the validity of wakeup time
    @param Pending Check if wake up time has expired.
    @param Time Current wake up time setting

    @retval EFI_STATUS

    @note  Here is the control flow of this function:
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
)
{
    RTC_REG_B   RegB;
    RTC_REG_C   RegC;
    RTC_REG_D   RegD;
    BOOLEAN     IntState;//, SmiState;
    EFI_STATUS  Status;
    UINT8       Year;
    EFI_TIME    RtcTime;    
    UINTN       DataSize;
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
    RTC_MONTH_ALARM_REG     RegMonthAlarm;
#endif

    if (!Enabled || !Pending || !Time)
        return EFI_INVALID_PARAMETER;

    //Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);
    if(EFI_ERROR(Status))
        return Status;

    //Get SMI State and disable it
   // SmiState = SbLib_GetSmiState();
   // SbLib_SmiDisable();

    //Get INTERRUPT State and disable it
    IntState = GetInterruptState();
    DisableInterrupts();

    // Wait till RTC is safe to read,
    CheckUpdateCmplete();
    if(gTimeOut)
        InitRtc();

    Time->Hour   = ReadRtcIndex(RTC_HOURS_ALARM_REG);
    Time->Minute = ReadRtcIndex(RTC_MINUTES_ALARM_REG);
    Time->Second = ReadRtcIndex(RTC_SECONDS_ALARM_REG);

    //Restore SMIs and INTERRUPT State
    if(IntState)
        EnableInterrupts();

    //if(SmiState)
    //    SbLib_SmiEnable();

    RegD.REG_D = ReadRtcIndex(RTC_REG_D_INDEX);
    Time->Day  = BcdToDecimal8(RegD.DateAlarm);
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
    RegMonthAlarm.REG_MONTH_ALARM = ReadRtcIndex(ACPI_ALARM_MONTH_CMOS);
    Time->Month = BcdToDecimal8(RegMonthAlarm.MonthAlarm);
#else
    Time->Month = ReadRtcIndex(RTC_MONTH_REG);
#endif

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);
    RegC.REG_C = ReadRtcIndex(RTC_REG_C_INDEX);

    *Enabled = RegB.AlarmInt;
    *Pending = RegC.AlarmFlag;

    Year = ReadRtcIndex(RTC_YEAR_REG);
    Time->Year = ReadRtcIndex(ACPI_CENTURY_CMOS) * 100 + Year;
    Time->TimeZone = gTimeZone;
    Time->Daylight = gDaylight;
    Time->Nanosecond = 0;

    //
    // Get the alarm info from variable
    //    
    DataSize = sizeof (EFI_TIME);
    Status = gRT->GetVariable (
                   L"RTCALARM",
                   &gEfiTimeVariableGuid,
                   NULL,
                   &DataSize,
                   &RtcTime
                   );
    if (!EFI_ERROR (Status)) {
        Time->Day = RtcTime.Day;
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
        Time->Month = RtcTime.Month;
#endif
      Time->Year     = RtcTime.Year;
      Time->TimeZone = RtcTime.TimeZone;
      Time->Daylight = RtcTime.Daylight;
    } else if (Status == EFI_NOT_FOUND) {
        // if user get the wake date without set.
        //      just init it.
        Time->Month = DEFAULT_MONTH;
        Time->Day   = DEFAULT_DAY;
        Time->Year  = DEFAULT_YEAR;
        Time->Daylight = 0;
        RtcTime.Day = Time->Day;
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
        RtcTime.Month = Time->Month;
#endif
        RtcTime.Year     = Time->Year;
        RtcTime.TimeZone = Time->TimeZone;
        RtcTime.Daylight = Time->Daylight;
        Status =  gRT->SetVariable (
                       L"RTCALARM",
                       &gEfiTimeVariableGuid,
                       EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                       sizeof (RtcTime),
                       &RtcTime
                       );
    }
    
    return EFI_SUCCESS;

}


/**
    Enable/disable and set wakeup time

    @param Enable Flag indicating whether to enable/disable the time
    @param Time Time to set

    @retval EFI_STATUS
            EFI_SUCCESS           Time is Set and/or Enabled/Disabled.
            EFI_INVALID_PARAMETER Invalid time or enabling with a NULL Time.

    @note  Here is the control flow of this function:
              1. Read the original time format 12/24 hours and BCD/binary.
              2. If Time is not NULL,
                  a. Verify the wakeup time to set. If it is an invalid time,
                     restore the time format and return EFI_INVALID_PARAMETER.
                  b. Set the wakeup time.
              3. If Time is NULL and Enable is true, restore original time 
                 format and return EFI_INVALID_PARAMETER.
              4. Enable/Disable wakeup.
              5. Restore the original time format.
              6. Return EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
AmiChipsetSetWakeupTime (
    IN BOOLEAN      Enable,
    IN EFI_TIME     *Time OPTIONAL
)
{
    RTC_REG_B   RegB;
    RTC_REG_D   RegD;
    UINT8       Day;
    EFI_STATUS  Status;
    EFI_TIME    RtcTime = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
    RTC_MONTH_ALARM_REG     RegMonthAlarm;
#endif

    //Check RTC Conditions (24h Mode and BCD is ON)
    Status = CheckRtc(FALSE);
    if(EFI_ERROR(Status))
        return Status;

    if (Time != NULL) {
        if (!VerifyTime(Time)) return EFI_INVALID_PARAMETER;
        if (Time->Year >= 2100) return EFI_INVALID_PARAMETER;
    } else {
        if (Enable) return EFI_INVALID_PARAMETER;
    }

    RegB.REG_B = ReadRtcIndex(RTC_REG_B_INDEX);

    SetUpdate(FALSE);
    if(Time != NULL) {
        RegD.REG_D = ReadRtcIndex(RTC_REG_D_INDEX);
        Day = DecimalToBcd8(Time->Day);
        RegD.DateAlarm = Day;
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
        // Month == 0 means don't care
        RegMonthAlarm.MonthAlarm = DecimalToBcd8(Time->Month);
        WriteRtcIndex(ACPI_ALARM_MONTH_CMOS, RegMonthAlarm.REG_MONTH_ALARM);
#endif
        WriteRtcIndex(RTC_HOURS_ALARM_REG,Time->Hour);
        WriteRtcIndex(RTC_MINUTES_ALARM_REG,Time->Minute);
        WriteRtcIndex(RTC_SECONDS_ALARM_REG,Time->Second);
        WriteRtcIndex(RTC_REG_D_INDEX,RegD.REG_D); //Day==0 means don't care
    }

    // Clear Alarm Flag
    ReadRtcIndex(RTC_REG_C_INDEX);
    RegB.REG_B &=0x0F; //Mask UIE,PIE Bit, some platform sometimes can't wake up
    
    //Set Enable/Disable
    RegB.AlarmInt = Enable;
    WriteRtcIndex(RTC_REG_B_INDEX,RegB.REG_B);

    SetUpdate(TRUE);
    
    //
    // Set the Y/M/D info to variable as it has no corresponding HW registers.
    //
    if (1) {  //### Always set for CSP internal test tool ### if (Enable) {
        if(Time != NULL) {
            RtcTime.Day = Time->Day;
#if defined(ACPI_ALARM_MONTH_CMOS) && (ACPI_ALARM_MONTH_CMOS != 0)
            RtcTime.Month = Time->Month;
#endif
            RtcTime.Year     = Time->Year;
            RtcTime.TimeZone = Time->TimeZone;
            RtcTime.Daylight = Time->Daylight;
            Status =  gRT->SetVariable (
                             L"RTCALARM",
                             &gEfiTimeVariableGuid,
                             EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                             sizeof (RtcTime),
                             &RtcTime
                             );
        }
    }

    return EFI_SUCCESS;
}

/**
    This function is the entry point for this DXE Driver. This function
    make the runtime services in SMM.

        
    @param ImageHandle Image handle
    @param SystemTable pointer to the UEFI System Table

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)
        Return Status based on errors that occurred while waiting for time to expire.

**/
EFI_STATUS
EFIAPI
SbRuntimeServiceLibConstructor (
  IN EFI_HANDLE			ImageHandle,
  IN EFI_SYSTEM_TABLE	*SystemTable
  )
{
	EFI_STATUS      Status = EFI_SUCCESS;
    EFI_TIME        Time;

    //MakeSure Mode, Format and REG_A is OK
    CheckRtc(TRUE);

    Status = AmiChipsetGetTime(&Time,NULL);

    if( EFI_ERROR(Status) || (!VerifyTime(&Time)))
    {
        EFI_TIME nt;

        #if defined(GENERIC_BAD_DATE_TIME_ERR_CODE_SUPPORT) && (GENERIC_BAD_DATE_TIME_ERR_CODE_SUPPORT != 0)
        ReportStatusCode (EFI_ERROR_CODE | EFI_ERROR_MINOR, GENERIC_BAD_DATE_TIME_ERROR);
        #endif

        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "\n\nTime: %d/%d/%d  %d:%d:%d\n",
            Time.Month,
            Time.Day,
            Time.Year,
            Time.Hour,
            Time.Minute,
            Time.Second
        ));

        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Nanosecond: %d TimeZone: %d\n\n\n",
            Time.Nanosecond,
            Time.TimeZone
        ));

        //if Time is invalid the battery probably has been removed
        //Let's setup RTC_REG_A just in case...
        WriteRtcIndex(RTC_REG_A_INDEX, 0x26);

        //Check to see what part of EFI_TIME was wrong.
        //reset unrelated to RTC fields.
        Time.TimeZone = EFI_UNSPECIFIED_TIMEZONE;
        Time.Daylight = 0;
        Time.Nanosecond = 0;

        nt = Time;

        nt.Hour   = 0;
        nt.Minute = 0;
        nt.Second = 0;

        if(VerifyTime(&nt)) {
            //if we here that means Time was wrong
            Time.Hour   = 0;
            Time.Minute = 0;
            Time.Second = 0;
        } else {
            //if we here that means Date was wrong
            Time.Month = DEFAULT_MONTH;
            Time.Day   = DEFAULT_DAY;
            Time.Year  = DEFAULT_YEAR;
        }
        //Here is the situation when both Time and Date is Incorrect.
        if(!VerifyTime(&Time)) {
            Time.Hour   = 0;
            Time.Minute = 0;
            Time.Second = 0;
            Time.Month = DEFAULT_MONTH;
            Time.Day   = DEFAULT_DAY;
            Time.Year  = DEFAULT_YEAR;
        }

        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "Reseting Invalid Date and Time to: %d/%d/%d  %d:%d:%d\n\n",
            Time.Month,
            Time.Day,
            Time.Year,
            Time.Hour,
            Time.Minute,
            Time.Second
         ));
        AmiChipsetSetTime(&Time);
    }

    return Status;
}

