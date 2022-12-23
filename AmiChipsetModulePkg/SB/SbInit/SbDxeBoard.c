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
/** @file SbDxeBoard.c
    This file contains DXE stage board component code for
    Template SB

**/
//*************************************************************************

// Module specific Includes
#include "Token.h"
#include "Efi.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AmiCspLib.h>
#include <SbElinks.h>

// Produced Protocols

// GUID Definitions

// Portable Constants

// Function Prototypes

// PPI interface definition


// Protocols that are installed

// Function Definition


/**
    This function initializes the board specific component in
    in the chipset South bridge

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
SbDxeBoardInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
	)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FCH- temporary workaround for EIP:63293
//  find out root cause later.
//#####if (AMD_SB_HARD_CODING_FOR_EIP20813_SUPPORT)
    //
    // Below for patch EIP:20813.
    // We can disable this after "4.6.3.1_CSM.7.57_66" component.
    // CSP disable it in default.
    //
    //####UINT8       NBFamilyID;
    //####//--AMDSB_POLICY_PROTOCOL       *AmdSbPolicy=NULL;
    //####//--Status = pBS->LocateProtocol(&gAmdSbPolicyProtocolGuid, NULL, &AmdsbPolicy);
    //####//--ASSERT_EFI_ERROR(Status);
    //####NBFamilyID = READ_PCI8(SB_PCI_CFG_ADDRESS(0,0,0,0x89));
    //####// below NB_REV_A12
    //####if ((NBFamilyID & 3) <= 0x01){
        UINT16      IsaIRQ;
        Status = AmiIsaIrqMask(&IsaIRQ, TRUE);
        if(Status == EFI_NOT_FOUND) {
            IsaIRQ=ISA_IRQ_MASK | BIT07;
            Status=AmiIsaIrqMask(&IsaIRQ, FALSE);
        }else if(!(IsaIRQ&BIT07)) {
            IsaIRQ |= BIT07;
            Status=AmiIsaIrqMask(&IsaIRQ, FALSE);
        }
    //####}
//#####endif
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
