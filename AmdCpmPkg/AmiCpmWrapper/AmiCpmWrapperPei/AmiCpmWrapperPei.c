//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiCpmWrapperPei.c
    This file contains code for AmiCpmWrapperPei.c
    in the PEI stage.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#ifdef _AUTOGENH_3fbd651b_5f0b_47af_be25_ae35c63c8d5c
// The condition is the definition of AutoGen. This is for internal use to separate AM4/FP5 in one C source.
#define __AMI_CPM_WRAPPER_FP5
#endif

#ifdef _AUTOGENH_3fbd651b_5f0b_47af_be25_ae35c63c8d5d
// The condition is the definition of AutoGen. This is for internal use to separate AM4/FP5 in one C source.
#define __AMI_CPM_WRAPPER_AM4
#endif


#include <PiPei.h>
#include <Token.h>
#include <Library/PeimEntryPoint.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

// Consumed PPIs
#include <Ppi/EndOfPeiPhase.h>
#ifdef __AMI_CPM_WRAPPER_AM4
#include <AGESA.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Setup.h>
#endif
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)
#ifdef __AMI_CPM_WRAPPER_AM4
static EFI_GUID gSetupGuid = SETUP_GUID;
#endif
// External Declaration(s)

// Function Definition(s)
EFI_STATUS
CpmEndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);

// PPI Definition(s)

// PPI that are installed

// PPI that are notified
static EFI_PEI_NOTIFY_DESCRIPTOR  NotifyList[] =
{
    {(EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK
        | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiEndOfPeiSignalPpiGuid,
    CpmEndOfPeiCallback}
};

#ifdef __AMI_CPM_WRAPPER_AM4
#endif

//---------------------------------------------------------------------------

/**
    This function is the entry point for Ami Cpm Wrapper PEIM.
    This function initializes the AmiCpmWrapperPei in PEI phase.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  NONE.
**/

EFI_STATUS
EFIAPI
AmiCpmWrapperPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS          Status;

    
    Status = (**PeiServices).NotifyPpi (PeiServices, &NotifyList[0]);

    return Status;
}

/**
    This function is called at end of PEI phase. 

	@param  PeiServices Indirect reference to the PEI Services Table.
	@param  NotifyDesc Address of the notification descriptor data structure.
	@param  InvokePpi Address of the PPI that was installed.

	@return Status of the notification.

    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
CpmEndOfPeiCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_STATUS      Status;
    EFI_BOOT_MODE   SbBootMode;

    Status = (*PeiServices)->GetBootMode (PeiServices, &SbBootMode);
    ASSERT_EFI_ERROR (Status);

    if (SbBootMode == BOOT_ON_S3_RESUME) {

        // issue the CPM S3 resume.
        IoWrite8(SW_SMI_IO_ADDRESS, PcdGet8(AcpiRestoreSwSmi));
    }

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
