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

/** @file SbCmos.c
    This file contains code for Chipset Reference Board Template
    initialization in the DXE stage

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiDxe.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Pci.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//-------------------------------------------------------------------
// PciHotPlugInit Protocol
//-------------------------------------------------------------------

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
// GUID Definition(s)

// Protocol Definition(s)


// GUID Definition(s)
static EFI_GUID guidVariableWrite = EFI_VARIABLE_WRITE_ARCH_PROTOCOL_GUID;
// External Declaration(s)

// Function Definition(s)


/**
    This callback function is called after Variable Write Protocol is 
    installed.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID SbVariableWriteCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS                      Status = EFI_SUCCESS;

    // Set CMOS "CMOS_BAD_CHECK_ADDRESS" as 55h at sbsecinit.asm
    // used CMOS "CMOS_BAD_CHECK_ADDRESS" to check the cmos good or not.
    IoWrite8(CMOS_BANK1_INDEX, CMOS_BAD_CHECK_ADDRESS);
    IoWrite8(CMOS_BANK1_DATA, 0xAA);  //Cmos flag,indicate cmos ok
    pBS->CloseEvent(Event);
}
/**
    This function is the entry point for CRB DXE driver.
    This function initializes the CRB in DXE phase.

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

    @retval EFI_STATUS EFI_SUCCESS

    @note  This routine is called very early, prior to SBDXE and NBDXE.
**/

EFI_STATUS
EFIAPI
SbCmosEntry (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_STATUS              Status = EFI_SUCCESS;
    EFI_EVENT           SbEvtVariableWriteProtocol  = NULL;
    VOID            *SbRegVariableWriteProtocol = NULL;
    InitAmiLib(ImageHandle, SystemTable);

    Status = RegisterProtocolCallback( &guidVariableWrite,\
                   SbVariableWriteCallback,\
                   NULL,\
                   &SbEvtVariableWriteProtocol,\
                   &SbRegVariableWriteProtocol );

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
