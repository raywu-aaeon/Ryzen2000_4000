/**
    AaeonSetupCallback.c
    Template callback file to be overridden for project porting.
    This file is added callback files. Callbacks for AAEON setup pages can be added here.

**/

#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include "AaeonSetup.h"

// External setup functions

// Callback functions


/* Example from AaeonSecureBoot
extern EFI_STATUS
ForceSetupModeCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key);

//----------------------------------------------------------------------------
// Procedure:   AaeonSecureBootCallback
//
// Description: 
//
// Input:       none
//
// Output:      VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//----------------------------------------------------------------------------
EFI_STATUS
AaeonSecureBootCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (Key == AAEON_SECURE_BOOT_MENU_REFRESH)  // Transfer AAEON key to original key.
      Status = ForceSetupModeCallback(HiiHandle, Class, SubClass, SECURE_BOOT_MENU_REFRESH);

    return Status;
}
*/
