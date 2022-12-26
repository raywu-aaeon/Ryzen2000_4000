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
//;   S5andPowerBtnSMI.c
//;
//;------------------------------------------------------------------------------
//;
//; Abstract:
//;   This is a DXE SMM driver to register power button and S5 SMI handler.
//;
#include <Uefi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Token.h>
#include <Setup.h>
#include <Protocol/SmmVariable.h>
#include <Library/BaseLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/PrintLib.h>

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

EFI_STATUS
EFIAPI
RunningTimePwrBtnSxHandler (SETUP_DATA *SetupData)
/*++
Routine Description:
    SMI handler to store running time of this boot back to variable PreviousRunTime.
    It's called when power button is pressed or S5 is executing.
--*/
{
    EFI_STATUS                Status;
    EFI_SMM_VARIABLE_PROTOCOL *SmmVarProtocol = NULL;
    EFI_TIME                  CurrentTime;
    UINT64 		              CurrentTimeInMinute;
    UINT64 		              ThisBootRunTimeInMinute;
    UINT64 		              PreviousRunTimeInMinute;
    UINT64 		              PowerOnTimeInMinute;
    UINTN 		              Size = sizeof(UINT64);

    CurrentTimeInMinute = 0;
    PowerOnTimeInMinute = 0;
    PreviousRunTimeInMinute = 0;

    Status =  pSmst->SmmLocateProtocol(&gEfiSmmVariableProtocolGuid, NULL, &SmmVarProtocol);
    if (EFI_ERROR(Status)) return Status;

    //
    // Get system time and translate to number of minutes since year 1970.
    //
    Status = pRS->GetTime (&CurrentTime, NULL);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    // Do nothing if system time is invalid. The purpose is to fix potential issue that 
    // running time will increase abnormally after setting system time right after COMS load default.
    if (CurrentTime.Year < 2017) {
        return EFI_SUCCESS;
    }
    CurrentTimeInMinute = TimeToMinute (CurrentTime);

    //
    // Get power on time in minutes.
    //
    Status = SmmVarProtocol->SmmGetVariable(
                    L"PowerOnTime",
                    &AaeonRunTimeleGuid,
                    NULL,
                    &Size,
                    &PowerOnTimeInMinute
                    );
    if (EFI_ERROR(Status)) {
        return Status;
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
    // Get PreviousRunTime in minutes.
    //
    Status = SmmVarProtocol->SmmGetVariable(
                    L"PreviousRunTime",
                    &AaeonRunTimeleGuid,
                    NULL,
                    &Size,
                    &PreviousRunTimeInMinute
                    );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Store ruinning time of this boot to PreviousRunTimeInMinute.
    //
    ThisBootRunTimeInMinute = CurrentTimeInMinute - PowerOnTimeInMinute + PreviousRunTimeInMinute;
    Status = SmmVarProtocol->SmmSetVariable (
                    L"PreviousRunTime",
                    &AaeonRunTimeleGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    Size,
                    &ThisBootRunTimeInMinute
                    );
    Status = SmmVarProtocol->SmmSetVariable (
                    L"PowerOnTime",
                    &AaeonRunTimeleGuid,
                    0,
                    0,
                    NULL
                    );

    return EFI_SUCCESS;
}
