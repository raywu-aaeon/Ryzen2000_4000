//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file AmdSpiRomProtectPei.c
    This file contains code for AMD SPI ROM Protect PEIM entrypoint

**/
//**********************************************************************
// Includes
// Statements that include other files
#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Library/DebugLib.h>

/**
    This function is the entry point for AmdSpiRomProtectPeiBin PEIM.
            

    @param FfsHeader Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS 
EFIAPI
AmdSpiRomProtectPei_Entry (
        IN EFI_PEI_FILE_HANDLE   FileHandle,  
        IN CONST EFI_PEI_SERVICES          **PeiServices )
{

    EFI_BOOT_MODE                   BootMode;
    EFI_STATUS                  Status=EFI_SUCCESS ; 



   Status = (*PeiServices)->GetBootMode(PeiServices, &BootMode);
    ASSERT_PEI_ERROR(PeiServices, Status);
    DEBUG ((DEBUG_INFO, "AmdSpiRomProtectPei_Entry.\n"));

    if (BootMode == BOOT_ON_S3_RESUME)
    {

    }   //BOOT_ON_S3_RESUME

    return Status;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
