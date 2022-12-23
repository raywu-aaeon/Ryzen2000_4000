//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  This file contains the test for External DMA availability
*/

#include <AmiHsti.h>

extern CHAR16 ImplementationId[];

VOID ExternalDeviceDMA( VOID )
{
    UINT64 ImplementationBitMap;
    UINT8 TestBit;
    
    TestBit = PcdGet8(AmiPcdHstiExternalDeviceDmaImplementationBit);

    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);

    DEBUG((DEBUG_INFO, "External Device DMA !!  TestBit = %d   BitMap = %X\r\n", TestBit, ImplementationBitMap));
    
    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "ExternalDeviceDMA is not implemented\r\n"));
        return;
    }

    DEBUG((DEBUG_INFO, "AMI HSTI - Running External DMA Test\r\n"));

    if (EXTERNAL_DMA_CAPABLE_DEVICES_SUPPORT != 0)
    {
        ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_ERROR_EXTERNAL_DMA));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting External DMA verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
#if defined (HSTI_REVISION) && (HSTI_REVISION == 1)
        HstiLibSetWindowsSecurityFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, 
                HSTI_WINDOWS_SECURITY_FEATURE_NO_UNAUTHENTICATED_DMA / 8,
                1 << (HSTI_WINDOWS_SECURITY_FEATURE_NO_UNAUTHENTICATED_DMA % 8));
#endif

    }
}
