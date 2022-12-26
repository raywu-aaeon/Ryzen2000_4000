//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PciLib.h>
#include <Library/S3PciLib.h>
#include <Library/BaseMemoryLib.h>

#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include <Protocol/SmmSwDispatch.h>
#include <AaeonBiosRobotCommonLib.h>
#include <AaeonCommonLib.h>
// Produced Protocols


extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_RUNTIME_SERVICES    *pRS;

//----------------------------------------------------------------------------
//
// Procedure:   EnableWatchDogRobotBeforeOS
//
// Description: This function will follow bios setting to Sends watch dog 
//              before booting OS.
//
// Input:       
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called before AcpiEnableCallbackList.
//----------------------------------------------------------------------------
VOID
EnableWatchRobotBeforeOS(
        IN EFI_HANDLE DispatchHandle,
        IN EFI_SMM_SW_DISPATCH_CONTEXT  *DispatchContext )
{

        EFI_STATUS              Status = EFI_SUCCESS;
        UINT8                   WatchDogOS = 0;
        UINT8                   Time = 0;
        IoWrite8(CMOS_BANK0_INDEX,BIOS_ROBOT_FLAG_REG);
        WatchDogOS = IoRead8(CMOS_BANK0_DATA) & OS_WATCH_DOG_FLAG_VALUE;
        
        IoWrite8(CMOS_BANK0_INDEX,OS_WATCH_DOG_TIME_FLAG_REG);
        Time = IoRead8(CMOS_BANK0_DATA);

        if (WatchDogOS == OS_WATCH_DOG_FLAG_VALUE)
        {
            AaeonEnableWatchDog(ROBOT_WDT_CHIP_TYPE, 1,Time);
        }
        
}
