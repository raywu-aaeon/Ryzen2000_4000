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

//*************************************************************************
/** @file SmiHandlerPorting.c
    This file contains SMM Child Dispatcher porting functions

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiSmm.h>
#include <Library/SmmServicesTableLib.h>
#include <Protocol/SmmCpu.h>


#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiSmm.h>
//###---#include "SmmChildDispatch.h"

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

EFI_SMM_CPU_PROTOCOL	static *gEfiSmmCpuProtocol = NULL;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

EFI_STATUS LocateSmmCpuProtocol(VOID *Smst)
{
    EFI_SMM_SYSTEM_TABLE2   *Smst2 = (EFI_SMM_SYSTEM_TABLE2*)Smst;
    EFI_STATUS				Status = EFI_SUCCESS;

    if (gEfiSmmCpuProtocol == NULL) {
		Status = Smst2->SmmLocateProtocol(
			&gEfiSmmCpuProtocolGuid,
			NULL,
			&gEfiSmmCpuProtocol
		);
		ASSERT_EFI_ERROR(Status);
    }

    return Status;
}

/**
    This function returns EAX saved value from CPU that caused SW SMI

    @param Cpu 

    @retval UINTN EAX saved value

    @note  Porting required

**/
UINTN GetEAX(IN UINTN Cpu)
{

//Porting required for different CPU
    EFI_STATUS              Status;
    EFI_GUID                SwSmiCpuTriggerGuid = SW_SMI_CPU_TRIGGER_GUID;
    SW_SMI_CPU_TRIGGER      *SwSmiCpuTrigger;
    //####UINTN                   Cpu = gSmst->CurrentlyExecutingCpu - 1; // CPU #
    UINT16                  i;
    UINT32                  RegEAX;

    LocateSmmCpuProtocol(gSmst);

    for (i = 0; i < gSmst->NumberOfTableEntries; i++) {
        if (guidcmp(&(gSmst->SmmConfigurationTable[i].VendorGuid), \
                                                  &SwSmiCpuTriggerGuid) == 0)
            break;
    }

    // If found table, check for the CPU that caused the software Smi.
    if (i != gSmst->NumberOfTableEntries) {
        SwSmiCpuTrigger = gSmst->SmmConfigurationTable[i].VendorTable;
        Cpu = SwSmiCpuTrigger->Cpu;
    }

    Status = gEfiSmmCpuProtocol->ReadSaveState ( \
                                            gEfiSmmCpuProtocol, \
                                            4, \
                                            EFI_SMM_SAVE_STATE_REGISTER_RAX, \
                                            Cpu, \
                                            &RegEAX );
    return RegEAX;

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
