//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
    This file contains test related to Secure Boot Bypass and for CSM 
    being disabled when Secure Boot is active

 */
#include <AmiHsti.h>

#include <Setup.h>
#include <ImageAuthentication.h>
#include <Protocol/LegacyBiosExt.h>

extern EFI_GUID gEfiGlobalVariableGuid;
extern CHAR16 ImplementationId[];

VOID SecureBootBypass( VOID
        )
{
    EFI_STATUS Status;
    UINT64 ImplementationBitMap;
    BOOLEAN Error = TRUE; // for this case error is initialized to true
    UINT8 TestBit;
    
    UINTN      DataSize;
    UINT8      SecureBootEnable = 0xFF;

    TestBit = PcdGet8(AmiPcdHstiSecureBootBypassImplementationBit);
    
    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    DEBUG((DEBUG_INFO, "SecureBootBypass BitMap %0lx, TesBit %d\r\n", ImplementationBitMap, TestBit));
    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "SecureBootBypass is not implemented\r\n"));
        return;
    }

    // SecureBoot variable to be installed along with NVRAM driver
    if (SecureBootEnable == 0xFF){
        DataSize = sizeof(UINT8);
        Status = pRS->GetVariable(EFI_SECURE_BOOT_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &DataSize, &SecureBootEnable);
        if (EFI_ERROR(Status)){
            SecureBootEnable = 0;
        }
    }
    // If secure boot is enabled, check the bypass status.  If bypass is enabled there is no error
    // SecureBoot Enabled - Bypass TRUE     = Error
    // SecureBoot Enabled - Bypass FALSE    = No Error
    // SecureBoot Disabled - Bypass XXXX    = Error
    // SecureBoot Disabled - Bypass XXXX    = Error
    if (SecureBootEnable == 1)
    {
        // Secure Boot is enabled, check for Bypass bring enabled.
        // Clear error if bypass is disabled
        if (!PcdGetBool(AmiPcdSecureBootBypass))
            Error = FALSE;
    }
    DEBUG((DEBUG_ERROR, "SecureBootBypass Error %x\n",  Error));
    
    if (Error)
    {
        ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_ERROR_SECURE_BOOT_BYPASS));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting Secure boot bypass verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_SECURE_BOOT_BYPASS / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_SECURE_BOOT_BYPASS % 8));
#endif
    }
  
}



VOID SecureBootCsmDisable( VOID
        )
{
    EFI_STATUS Status;
    UINT64 ImplementationBitMap;
    BOOLEAN Error = FALSE;
    UINT8 TestBit;
    
    UINTN      DataSize;
    UINT8      SecureBootEnable = 0xFF;
    EFI_LEGACY_BIOS_EXT_PROTOCOL *LegacyBoot;

    TestBit = PcdGet8(AmiPcdHstiSecureBootCsmDisableImplementationBit); 
    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    DEBUG((DEBUG_INFO, "SecureBootCsmDisable BitMap %0lx, TesBit %d\r\n", ImplementationBitMap, TestBit));
    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "SecureBootCsmDisable is not implemented\r\n"));
        return;
    }
    //
    // SecureBoot variable to be installed along with NVRAM driver
    //
    if (SecureBootEnable == 0xFF){
        DataSize = sizeof(UINT8);
        Status = pRS->GetVariable(EFI_SECURE_BOOT_MODE_NAME, &gEfiGlobalVariableGuid, NULL, &DataSize, &SecureBootEnable);
        if (EFI_ERROR(Status)){
            SecureBootEnable = 0;
        }
    }
    
    Status = gBS->LocateProtocol (
                    &gAmiLegacyBootProtocolGuid,
                    NULL,
                    (VOID **)&LegacyBoot
                    );

    
    // If secure boot is enabled, check the bypass status.  If bypass is enabled there is no error
    // SecureBoot Enabled - LegacyBootProtocol - Found  = Error
    // SecureBoot Enabled - LegacyBootProtocol - not Found  = No Error
    if ((SecureBootEnable == 1) && !EFI_ERROR(Status))
    {
            Error = TRUE;
    }    
        
    DEBUG((DEBUG_ERROR, "Secure Boot Csm Disable Error %x\n",  Error));
    
    if (Error)
    {
        ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_ERROR_SECURE_BOOT_CSM_DISABLE));
        Error = TRUE;
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting Secure Boot CSM Disable verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_SECURE_BOOT_BYPASS / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_NO_SECURE_BOOT_BYPASS % 8));
#endif
    }
}
