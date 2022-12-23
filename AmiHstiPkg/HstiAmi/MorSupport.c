//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file
  This file contains the test to verify that MOR support is active
 */

#include <AmiHsti.h>

extern EFI_GUID gEfiMemoryOverwriteControlDataGuid;

extern CHAR16 ImplementationId[];


VOID MorSupportTest( VOID
        )
{
    UINT64 ImplementationBitMap;
    VOID *Buffer;
    UINT8 TestBit;

    TestBit = PcdGet8(AmiPcdHstiMorSupportImplementationBit);

    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    DEBUG((DEBUG_INFO, "MOR Support !!  TestBit = %d   BitMap = %X\r\n", TestBit, ImplementationBitMap));

    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "MorSupportTest is not implemented\r\n"));
        return;
    }

    DEBUG((DEBUG_INFO, "AMI HSTI - Running MorSupportTest\r\n"));

    Buffer = GetVariable( L"MemoryOverwriteRequestControl", &gEfiMemoryOverwriteControlDataGuid);
    if (Buffer == NULL)
    {
        ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_ERROR_MOR_STRENGTH));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting MOR Bits verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_MOR_BIT_ENABLED / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_MOR_BIT_ENABLED % 8));
#endif

    }
}
