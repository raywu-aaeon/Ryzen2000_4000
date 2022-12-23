//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/**@file SignalSetupConfig.c
  This file will handle Setup Configuration changed. And it will report to HardwareSignature's final value..
*/
//---------------------------------------------------------------------------
#include <Token.h>
#include <Uefi.h>
#include <HardwareChangeProtocol.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
STATIC EFI_GUID  gSetupUpdateCountGuid = AMI_SETUP_UPDATE_COUNT_GUID;

/**
 * Set setup  count to NVRAM.
 * 
 * This function saves the setup count into NVRAM.
 * 
 * @param[in]   ChangeTime              setup times.                 
 * 
 * @retval      EFI_SUCCESS             ChangeTime is written successfully
 * @retval      EFI_INVALID_PARAMETER   ChangeTime is invalid
  
**/

EFI_STATUS 
SetSetupCountToNvram (
    IN UINT32 *ChangeTime )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(UINT32);

    if (ChangeTime == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = gRT->SetVariable (AMI_HARDWARE_SIGNATURE_SETUP_UPDATE_COUNT_VARIABLE, 
                               &gSetupUpdateCountGuid,
                               EFI_VARIABLE_NON_VOLATILE |
                               EFI_VARIABLE_BOOTSERVICE_ACCESS |
                               EFI_VARIABLE_RUNTIME_ACCESS,
                               VarSize, 
                               ChangeTime); 
    
    return Status;    
}

/**
 * Get the setup update count data.
 * 
 * This function gets the setup update times from NVRAM.
 * 
 * @param[in,out]   ChangeTime              The setup update times.
 * 
 * @retval          EFI_SUCCESS             Get the setup update change times successfully.
 * @retval          EFI_INVALID_PARAMETER   ChangeTime is NULL.
**/

EFI_STATUS 
GetSetupCountFromNvram (
    IN OUT UINT32 *ChangeTime )
{
    EFI_STATUS          Status;
    UINTN               VarSize = sizeof(UINT32);

    if (ChangeTime == NULL)
        return EFI_INVALID_PARAMETER;
    
    Status = gRT->GetVariable (AMI_HARDWARE_SIGNATURE_SETUP_UPDATE_COUNT_VARIABLE, 
                               &gSetupUpdateCountGuid,
                               NULL, 
                               &VarSize, 
                               ChangeTime); 

    if (EFI_ERROR(Status))
    {
        gBS->SetMem (ChangeTime, sizeof(UINT32), 0);
    }
    
    return Status;    
}

/**
 * Count the setup change times.
 * 
 * This function process the setup change count times.
 * It  links function SavedConfigChanges in AMITSE module.
 * 
 * @retval  None.
**/

VOID 
EFIAPI
SetupChangeCount ()
{
    UINT32 SetupCount;

    SetupCount=0;
    GetSetupCountFromNvram (&SetupCount);
    SetupCount++;
    SetSetupCountToNvram (&SetupCount);
    return;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


