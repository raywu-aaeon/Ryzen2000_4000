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

/** @file SbCsmDxeLib.c
    Implementation of the AmiCriticalSectionLib library class.

*/

#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol/Timer.h>
#if CSM_SUPPORT
#include <Protocol/LegacyBiosExt.h>
#endif

#if CSM_SUPPORT
UINT64                      mTimerPeriod = 0;
EFI_TIMER_ARCH_PROTOCOL     *mTimer = NULL;

/**
  Enable the main counter in the HPET Timer.

  @param  ThunkData  data from/to legacy16
  @param  Priority  BOOLEAN function is called before (TRUE) or after (FALSE) 16-bit code

  @retval EFI_OUT_OF_RESOURCES
  @retval EFI_INVALID_PARAMETER
  @retval EFI_SUCCESS
**/
EFI_STATUS SbCsm16CallCompanionFunctionsHook (
  IN OUT AMI_CSM_THUNK_DATA   *ThunkData,
  IN BOOLEAN                  Priority
  )
{
  EFI_STATUS Status;
#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
#else
  UINT64	 ThunkTimerPeriod = 550000;
#endif
  
  if (mTimer == NULL) {
    Status = pBS->LocateProtocol (&gEfiTimerArchProtocolGuid, NULL, &mTimer);
    ASSERT_EFI_ERROR(Status);
  }
  
  if (Priority) {
    mTimer->GetTimerPeriod (mTimer, &mTimerPeriod); 
#if defined(HPET_PROTOCOL_SUPPORT) && (HPET_PROTOCOL_SUPPORT != 0)
    if (mTimerPeriod != 0) {
      mTimer->SetTimerPeriod (mTimer, 0);
    }
#else
    mTimer->SetTimerPeriod (mTimer, ThunkTimerPeriod);
    mTimer->SetTimerPeriod (mTimer, 0);
#endif
  }
  else {
    if (mTimerPeriod != 0) {        
      mTimer->SetTimerPeriod (mTimer, mTimerPeriod);
    }
  }
  
  return EFI_SUCCESS;
}
#endif

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
