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
//;   AaeonRunningTimeDxe.c
//;
//;------------------------------------------------------------------------------
//;
//; Abstract:
//;   A DXE driver to process PowerOnTime and PreviousRunTime variable.
//;

#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include <Library\BaseLib.h>
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

EFI_STATUS
EFIAPI
DxeInitRunningTime(
    IN EFI_HANDLE         ImageHandle,  
    IN EFI_SYSTEM_TABLE   *SystemTable
)
/*++
Routine Description:
  Function entry point. 
--*/
{
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

    InitAmiLib(ImageHandle, SystemTable);

    //
    // Get system time and translate to number of minutes since year 1970.
    //
	Status = pRS->GetTime (
                    	&CurrentTime,
                    	&Capabilities
                    	);
    if (EFI_ERROR(Status)) {
        return EFI_NOT_FOUND;
    }
    // Do nothing if system time is invalid. The purpose is to fix potential issue that 
    // running time will increase abnormally after setting system time right after COMS load default.
    if (CurrentTime.Year < 2017) {
        return EFI_SUCCESS;
    }
    CurrentTimeInMinute = TimeToMinute (CurrentTime);

    //
    // Get power on time in minutes, if not exist set CurrentTimeInMinute to PowerOnTime.
    // PowerOnTime will be deleted after CMOS battery loss or off-line BIOS flash.
    //
  	Status = pRS->GetVariable(
                      	L"PowerOnTime",
                      	&AaeonRunTimeleGuid,
                      	NULL,
                      	&Size,
                      	&PowerOnTimeInMinute
                      	);
    if (Status == EFI_NOT_FOUND){
    	Status = pRS->SetVariable(
                        L"PowerOnTime",
                        &AaeonRunTimeleGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        Size,
                        &CurrentTimeInMinute
                        );
    }
    //
    // If user set the system time to past time, then also sync system time to power on time.
    // It's to prevent minus Running Time
    //
    if (CurrentTimeInMinute < PowerOnTimeInMinute) {
        PowerOnTimeInMinute = CurrentTimeInMinute;
    	Status = pRS->SetVariable(
                        L"PowerOnTime",
                        &AaeonRunTimeleGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        Size,
                        &PowerOnTimeInMinute);
    }

    //
    // Get PreviousRunTime in minutes, if not exist set it to 0.
    //
  	Status = pRS->GetVariable(
                      	L"PreviousRunTime", 
                      	&AaeonRunTimeleGuid,
                      	NULL,
                      	&Size,
                      	&PreviousRunTimeInMinute
                      	);
    if (Status == EFI_NOT_FOUND){
        // PreviousRunTime will be deleted after CMOS battery loss or off-line BIOS flash.
        PreviousRunTimeInMinute = 0;
    	Status = pRS->SetVariable(
                        L"PreviousRunTime",
                        &AaeonRunTimeleGuid,
                        EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                        Size,
                        &PreviousRunTimeInMinute
                        );
    }

    return EFI_SUCCESS;
}
