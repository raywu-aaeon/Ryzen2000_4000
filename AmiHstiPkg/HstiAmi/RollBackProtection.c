//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  This file contains the test for Firmware rollback protection verification
 */

#include <AmiHsti.h>

extern CHAR16 ImplementationId[];

VOID FirmwareRollbackProtection( VOID )
{
    UINT64 ImplementationBitMap;
    BOOLEAN Error = FALSE;
    UINT8  TestBit;

    TestBit = PcdGet8(AmiPcdHstiFirmwareRollbackImplementationBit);

    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    DEBUG((DEBUG_INFO, "Firmware Rollback Protection BitMap %0lx, TesBit %d\r\n", ImplementationBitMap, TestBit));
    
    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "Firmware Rollback Protection is not implemented\r\n"));
        return;
    }

    if (!PcdGetBool(AmiPcdFirmwareRollbackProtection))
            Error = TRUE;

    if (Error)
    {
        ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_ERROR_FIRMWARE_ROLLBACK));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting firmware rollback verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_BIOS_FIRMWARE_ROLLBACK_PROTECTION / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_BIOS_FIRMWARE_ROLLBACK_PROTECTION % 8));
#endif

    }

}
