//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  This file contains the test for Manufacturing Mode
 */



#include <AmiHsti.h>
extern CHAR16 ImplementationId[];

/**
    Tests to see if the system is booting with Manufacturing mode settings.
    
    

 */
VOID ManufacturingMode( VOID
//        IN CHAR16 *ImplementationID OPTIONAL
        )
{
    UINT64 ImplementationBitMap;
    UINT8 TestBit;
    EFI_BOOT_MODE BootMode;
    
    TestBit = PcdGet8(AmiPcdHstiManufacturingModeImplementationBit);
    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);

    DEBUG((DEBUG_INFO, "Manufacturing Mode!!  TestBit = %d   BitMap = %X\r\n", TestBit, ImplementationBitMap));

    
    // check if test should be run for this system
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "Manufacturing Mode is not implemented!!  TestBit = %X   BitMap = %X\r\n", TestBit, ImplementationBitMap));
        return;
    }

    DEBUG((DEBUG_INFO, "AMI HSTI - Running Manufacturing Mode\r\n"));

    BootMode = GetBootMode();
    
    if (BootMode == BOOT_WITH_MFG_MODE_SETTINGS)
    {
        ReportError(TestBit, 1, STRING_TOKEN(AMI_HSTI_MANUFACTURING_MODE));
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting Manufacturing Mode verification bits\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
    }
}
