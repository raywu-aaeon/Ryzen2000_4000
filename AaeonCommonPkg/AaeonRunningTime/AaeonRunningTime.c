//;******************************************************************************
//;* Copyright (c) 2017, Aaeon Corporation. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Aaeon Corporation.
//;*
//;******************************************************************************
//; ModuleName:
//;
//;   AaeonRunningTime.c
//;
//;------------------------------------------------------------------------------
//;
//; Abstract:
//;   A setup item call back file
//;   

#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include <Library\BaseLib.h>
#include <Guid\GlobalVariable.h>
#include <Library\UefiBootServicesTableLib.h>
#include <Library\UefiRuntimeServicesTableLib.h>

#define IsLeap(y)   (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))
#define MINSPERHOUR (60)
#define MINSPERDAY  (24 * MINSPERHOUR)

static EFI_GUID     AaeonRunTimeleGuid = {0xCE066E0D, 0x1893, 0x4FF5, {0x81, 0x89, 0x0B, 0xF8, 0x8F, 0xF1, 0x6B, 0xCA}};

//
//  The arrays give the cumulative number of days up to the first of the
//  month number used as the index (1 -> 12) for regular and leap years.
//  The value at index 13 is for the whole year.
//
static UINTN CumulativeDays[2][14] = {
  {
    0,
    0,
    31,
    31 + 28,
    31 + 28 + 31,
    31 + 28 + 31 + 30,
    31 + 28 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31
  },
  {
    0,
    0,
    31,
    31 + 29,
    31 + 29 + 31,
    31 + 29 + 31 + 30,
    31 + 29 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 
  }
};

static UINT64 TimeToMinute (EFI_TIME CurrentTime)
/*++
Routine Description:
    A function to translate system time to number of minutes since year 1970.
--*/
{
    UINT64    CalTimeInMinute = 0;
    UINTN     Year;

    //
    // Years Handling
    // UTime should now be set to 00:00:00 on Jan 1 of the current year.
    //
    for (Year = 1970, CalTimeInMinute = 0; Year != CurrentTime.Year; Year++) {
      CalTimeInMinute = CalTimeInMinute + (CumulativeDays[IsLeap(Year)][13] * MINSPERDAY);
    }

    //
    // Add in number of seconds for current Month, Day, Hour, Minute and TimeZone adjustment
    //
    CalTimeInMinute = CalTimeInMinute + 
                      (CumulativeDays[IsLeap(CurrentTime.Year)][CurrentTime.Month] * MINSPERDAY) + 
                      (((CurrentTime.Day > 0) ? CurrentTime.Day - 1 : 0) * MINSPERDAY) + 
                      (CurrentTime.Hour * MINSPERHOUR) + 
                      (CurrentTime.Minute);

    return CalTimeInMinute;
}

static VOID AAInitString(EFI_HII_HANDLE HiiHandle, STRING_REF StrRef, CHAR16 *sFormat, ...)
{
    CHAR16 s[1024];
    VA_LIST  ArgList;
    VA_START(ArgList,sFormat);
    Swprintf_s_va_list(s,sizeof(s),sFormat,ArgList);
    VA_END(ArgList);
    HiiLibSetString(HiiHandle, StrRef, s);
}

VOID AaeonRunningTimeCallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
	CALLBACK_PARAMETERS	    *Callback;
    EFI_STATUS              Status;
    EFI_TIME                CurrentTime;
    EFI_TIME_CAPABILITIES   Capabilities;
    UINT64 		            CurrentTimeInMinute;
    UINT64 		            PowerOnTimeInMinute;
    UINT64 		            PreviousRunTimeInMinute;
    UINTN 		            Size = sizeof(UINT64);

    CurrentTimeInMinute = 0;
    PowerOnTimeInMinute = 0;
    PreviousRunTimeInMinute = 0;

	Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return;

    //
    // Get system time and translate to number of minutes since year 1970.
    //
	Status = gRT->GetTime (
                	&CurrentTime,
                	&Capabilities
                	);
    if (EFI_ERROR(Status)) {
        AAInitString(HiiHandle,STRING_TOKEN(AAEON_STR_RUN_TIME_VAL), L"Get RTC Time Failed");
        return;
    }
    // Do nothing if system time is invalid. The purpose is to fix potential issue that 
    // running time will increase abnormally after setting system time right after COMS load default.
    if (CurrentTime.Year < 2017) {
        AAInitString(HiiHandle,STRING_TOKEN(AAEON_STR_RUN_TIME_VAL), L"Systime is invalid");
        return;
    }
    CurrentTimeInMinute = TimeToMinute (CurrentTime);

    //
    // Get power on time in minutes.
    //
  	Status = gRT->GetVariable(
                  	L"PowerOnTime",
                  	&AaeonRunTimeleGuid,
                  	NULL,
                  	&Size,
                  	&PowerOnTimeInMinute
                  	);
    if (Status == EFI_NOT_FOUND){
        // PowerOnTime will be deleted after CMOS battery loss or off-line BIOS flash.
        AAInitString(HiiHandle,STRING_TOKEN(AAEON_STR_RUN_TIME_VAL), L"Get PowerOnTime Failed");
        return;
    }
    //
    // If user set the system time to past time, then also sync system time to power on time, but don't set PowerOnTimeInMinute
    // variable here to save NvRam space. It will be set via AaeonRunningTimeDxe.c or S5andPowerBtnSMI.c
    //
    if (CurrentTimeInMinute < PowerOnTimeInMinute) {
        // It's to prevent minus Running Time.
        PowerOnTimeInMinute = CurrentTimeInMinute;
    }

  	Status = gRT->GetVariable(
                    L"PreviousRunTime",
                    &AaeonRunTimeleGuid,
                    NULL,
                    &Size,
                    &PreviousRunTimeInMinute
                    );
    if (Status == EFI_NOT_FOUND){
        // PreviousRunTime will be deleted after CMOS battery loss or off-line BIOS flash.
        AAInitString(HiiHandle,STRING_TOKEN(AAEON_STR_RUN_TIME_VAL), L"Get PreviousRunTime Failed");
        return;
    }

    AAInitString(HiiHandle,STRING_TOKEN(AAEON_STR_RUN_TIME_VAL), L"%d Hours",
                 (CurrentTimeInMinute - PowerOnTimeInMinute + PreviousRunTimeInMinute) / 60);

	return;
}
