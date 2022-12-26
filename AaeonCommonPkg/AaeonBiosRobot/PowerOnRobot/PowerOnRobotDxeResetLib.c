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
#include <AaeonBiosRobotCommonLib.h>

// Produced Protocols

// Consumed Protocols
#include <Protocol/S3SaveState.h>

extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_RUNTIME_SERVICES    *pRS;
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// Procedure:   PowerOnRobotDxeReset
//
// Description: This function will follow bios setting to Reset system once
//               on each boot.
// Input:       
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called after Full System Initialization.
//----------------------------------------------------------------------------

VOID PowerOnRobotDxeReset()
{
    UINT8 ResetFlag=0;
    UINT8 SameBootTime = 0;
    EFI_STATUS Status = EFI_SUCCESS;
        EFI_GUID    SetupGuid = SETUP_GUID;
        SETUP_DATA  SetupData;
        UINTN       VariableSize = sizeof(SetupData);
        UINT32      Attribute = 0;
        
    Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );
    if (SetupData.ResetSystemOnce == 1)
    {
        IoWrite8(CMOS_BANK0_INDEX,BIOS_ROBOT_FLAG_REG);
        ResetFlag = IoRead8(CMOS_BANK0_DATA) & POWER_ON_RESET_FLAG_VALUE;
        if (SetupData.AaeonCommonFeaturesSyncReady == 1)
        {                        
            if(ResetFlag != POWER_ON_RESET_FLAG_VALUE)
            {
                IoWrite8(CMOS_BANK0_INDEX,BIOS_ROBOT_FLAG_REG);
                IoWrite8(CMOS_BANK0_DATA,IoRead8(CMOS_BANK0_DATA)|POWER_ON_RESET_FLAG_VALUE);
                if (SetupData.PORResetType == 0)
                    IoWrite8(0xCF9, 0x06);
                if (SetupData.PORResetType == 1)
                    IoWrite8(0xCF9, 0xE);
            } else {
                IoWrite8(CMOS_BANK0_INDEX,BIOS_ROBOT_FLAG_REG);
                IoWrite8(CMOS_BANK0_DATA,IoRead8(CMOS_BANK0_DATA) & ~POWER_ON_RESET_FLAG_VALUE);
            }
        }
    }
}

