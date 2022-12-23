//*************************************************************************
//*************************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************

//*************************************************************************
/** @file SbPeiBoard.c
    This file contains PEI stage board component code for
    Template SB

**/
//*************************************************************************

// Module specific Includes
#include <Efi.h>
#include <Pei.h>
#include <Token.h>
#include <AmiLib.h>
#include <AmiPeiLib.h>
#include "Sb.h"
#include "AmiCspLib.h"
#include <AmiChipsetIoLib.h>
#include <Ppi/CspLibPpi.h>
#include <Ppi/NbPpi.h>
//-----------------------------------------------
// Function Prototypes
//-----------------------------------------------

EFI_STATUS
CRB_StopBootupTimer (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi
  );

//-----------------------------------------------
// GUID Definitions
//-----------------------------------------------
EFI_GUID gNbInitPolicyGuid = AMI_PEI_NBINIT_POLICY_PPI_GUID;

//-----------------------------------------------
// Produced PPIs
//-----------------------------------------------
static EFI_PEI_NOTIFY_DESCRIPTOR mNotifyList[] = {
              { EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | \
                                EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
                &gNbInitPolicyGuid,   CRB_StopBootupTimer}
              };

//-----------------------------------------------
// Portable Constants
//-----------------------------------------------

//-----------------------------------------------
// PPI interface definition
//-----------------------------------------------

/**
    This hook gets called just after bios gets control at
    power-on.  We want to assert reset to the PCIE as early as
    possible.

**/
EFI_STATUS
CRB_StopBootupTimer (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *NullPpi
  )
{
//It has disabled in the SB800 CIMX code
//    RW_IO8_PMIO(SB_PMIOA_REG44+3,BIT7,0); //disable NB boot timer function.
    return EFI_SUCCESS;
}


/**
    This function is the entry point for this PEI. This function
    initializes the chipset SB

    @param FfsHeader Pointer to the FFS file header
    @param PeiServices Pointer to the PEI services table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  Init SUB CRB

**/
EFI_STATUS
EFIAPI
SBPEI_Board (
  IN EFI_PEI_FILE_HANDLE   FileHandle,
  IN EFI_PEI_SERVICES          **PeiServices
  )
{
    EFI_STATUS          Status;

    Status = (*PeiServices)->NotifyPpi (PeiServices, &mNotifyList[0]);
    ASSERT_PEI_ERROR (PeiServices, Status);

#if SB_LPC_PORT80_SUPPORT
    SET_PCI8_SB(0x4A, BIT05); // LPC: Port80
#endif

    //Make PCI reset if KBRST# is asserted.
    //SET_MEM8 (ACPI_MMIO_BASE + PMIO_BASE + SB_PMIOA_REGBE,BIT01);  //EIP26515+

#if SB_KBC_ASSERT_CLEAR
    RESET_MEM8 (ACPI_MMIO_BASE + PMIO_BASE + SB_PMIOA_REGBE,BIT01);
#endif
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

