//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//*************************************************************************
/** @file SbFchSpiProtectHstiLib.c

**/
//*************************************************************************
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Token.h>
#include <AmiHobs.h>
#include <Library/DebugLib.h>
#include <AmiHstiPkg/HstiAmi/AmiHsti.h>
#include <AmdSpiRomProtect.h>

extern CHAR16 ImplementationId[];


VOID SbFchSpiProtectTest(VOID)

{
    UINT64 ImplementationBitMap;
    BOOLEAN Error = FALSE;
    UINT8 TestBit;    
    volatile UINT8  *SPIBASE = (UINT8*)(UINTN)SPI_BASE_ADDRESS;
    
#if  defined AMD_PSP_ROM_ARMOR2_SMM_SUPPORT && AMD_PSP_ROM_ARMOR2_SMM_SUPPORT == 1      
        if (PcdGetBool(PcdAmdPspRomArmor2Enabled)){
            DEBUG((DEBUG_INFO, "AMI HSTI- AMD Spi Protect test not support Armor2.\r\n"));
            return;                                     
        }
#endif
        
        if (*(volatile UINT32*)SPIBASE == 0xFFFFFFFF){
            DEBUG((DEBUG_INFO, "AMI HSTI- AMD Spi Protect test not support Armor1.\r\n"));
            return; 
        }
                
//    TestBit = PcdGet8(AmiPcdHstiAmdFwProtectSpiImplementationBit); 
    TestBit = AmiHstiAmdFwProtectSpiImplementationBit;
    // get the PCD that defines the Bitmap of Implemented Tests for the IBV
    ImplementationBitMap = PcdGet64(AmiPcdHstiImplementedTestBitmap);
    
    DEBUG((DEBUG_INFO, "AMI HSTI - AMD SPI Protect test BitMap %0lx, TesBit %d\r\n", ImplementationBitMap, TestBit));
    // check if test should be run for this system
    // cppcheck-suppress knownConditionTrueFalse
    if ((TestBit == 0xFF) || !(ImplementationBitMap & ((UINT64)1 << TestBit) ))
    {
        DEBUG((DEBUG_INFO, "AMI HSTI- AMD Spi Protect test is not implemented\r\n"));
        return;
    }
    

    if ((*(SPIBASE + 2) & (BIT07 | BIT6))){ 
       //Unlocked
        Error = TRUE;
    }

     DEBUG((DEBUG_ERROR, "AMI HSTI- AMD Spi Protect test Error %x\n",  Error));
        
    if (Error)
    {
        ReportError(TestBit, 1, STRING_TOKEN(STR_AMI_HSTI_ERROR_SPI_PROTECT_HELP));
        // cppcheck-suppress unreadVariable
        Error = TRUE;
    }
    else
    {
        DEBUG((DEBUG_INFO, "Setting AMI HSTI- AMD Spi Protect test bit\n\r"));

        HstiLibSetFeaturesVerified(PLATFORM_SECURITY_ROLE_PLATFORM_IBV, ImplementationId, TestBit / 8, 1 << (TestBit % 8));
    }
}
