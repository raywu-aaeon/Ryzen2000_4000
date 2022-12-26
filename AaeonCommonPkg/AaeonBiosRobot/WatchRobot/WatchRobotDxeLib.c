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
// Produced Protocols

// Consumed Protocols
#include <AaeonCommonLib.h>
#include <AaeonBiosRobotCommonLib.h>
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_RUNTIME_SERVICES    *pRS;

//----------------------------------------------------------------------------
//
// Procedure:   WatchDogRobotDxe
//
// Description: This function will disable the watchdog timer for 
//              "Sends watch dog before BIOS POST" function.
//              This function will follow bios setting to register 
//              the OS_WATCH_DOG_FLAG_REG and OS_WATCH_DOG_TIME_FLAG_REG 
//              in CMOS.
//
// Input:       
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called after HandoffToTse.
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
WatchRobotDxe (
  )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    UINT8 Data8 = 0;
        EFI_GUID    SetupGuid = SETUP_GUID;
        SETUP_DATA  SetupData;
        UINTN       VariableSize = sizeof(SetupData);
        UINT32      Attribute = 0;

    Status = gRT->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );
    
    if (SetupData.WatchDogPost == 1)
    {
        AaeonDisableWatchDog(ROBOT_WDT_CHIP_TYPE);
    }
    
    IoWrite8(CMOS_BANK0_INDEX,BIOS_ROBOT_FLAG_REG);
    if (SetupData.WatchDogOS)
        IoWrite8(CMOS_BANK0_DATA,IoRead8(CMOS_BANK0_DATA)|OS_WATCH_DOG_FLAG_VALUE);
    else
        IoWrite8(CMOS_BANK0_DATA,IoRead8(CMOS_BANK0_DATA) & ~OS_WATCH_DOG_FLAG_VALUE);
    
    IoWrite8(CMOS_BANK0_INDEX,OS_WATCH_DOG_TIME_FLAG_REG);
    IoWrite8(CMOS_BANK0_DATA,SetupData.TimerMinute);
    
    return Status;
}
