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
extern EFI_RUNTIME_SERVICES *gRT;

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
//----------------------------------------------------------------------------
//
// Procedure:   PowerOnRobotDxeInit
//
// Description: This function will follow bios setting to Period of time 
//              for Robot to hold BIOS from POST.
// Input:       
//
// Output:      EFI_SUCCESS
//
// Notes:       
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
PowerOnRobotDxeInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS Status = EFI_SUCCESS;
        EFI_GUID    SetupGuid = SETUP_GUID;
        SETUP_DATA  SetupData;
        UINTN       VariableSize = sizeof(SetupData);
        UINT32      Attribute = 0;

    Status = gRT->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );
    if(SetupData.DelayPOST == 1)
    {
        gBS->Stall(SetupData.DelayedTime * 1000000);
    }

    return Status;
}

