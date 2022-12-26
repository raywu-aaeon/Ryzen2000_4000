//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <PiPei.h>
#include <Library/PeiServicesLib.h> 
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library\MemoryAllocationLib.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Sb.h>
#include <ppi\NBPPI.h>
#include <ppi\SBPPI.h>
#include <Ppi/Stall.h>
#include <AaeonCommonLib.h>
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
//----------------------------------------------------------------------------
//
// Procedure:   WatchDogRobotPeiEntryPoint
//
// Description: This function is the entry point for WatchDogRobotPei.
//              It will follow bios setting to set watchdog function in PEI phase.
//
// Input:       FfsHeader   - Pointer to the FFS file header.
//              PeiServices - Pointer to the PEI services table.
//
// Output:      EFI_SUCCESS
//
// Notes:       This routine is called before memory init.
//----------------------------------------------------------------------------

EFI_STATUS
EFIAPI
WatchRobotPeiEntryPoint (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
  )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    SETUP_DATA             SetupData;
    UINTN                       VariableSize = sizeof( SETUP_DATA );
    EFI_GUID                gSetupGuid = SETUP_GUID;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI     *ReadOnlyVariable = NULL;

    Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
    Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );  
    
    if (SetupData.WatchDogPost != 0)
    {
        AaeonEnableWatchDog(ROBOT_WDT_CHIP_TYPE,0,SetupData.TimerSecond);
    }

    return Status;
}

