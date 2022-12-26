#include <Token.h>
#include <AmiDxeLib.h>

#include <Setup.h>

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

#if /* not defined( TSE_FOR_APTIO_4_50) &&*/ !defined(NO_SETUP_COMPILE)  // Refer to SecureBoot.c

    if (Key == AAEON_SECURE_BOOT_MENU_REFRESH)
      Status = ForceSetupModeCallback(HiiHandle, Class, SubClass, SECURE_BOOT_MENU_REFRESH);

#endif // #ifdef NO_SETUP_COMPILE

    return Status;
}
