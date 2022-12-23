//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file PspCspLib.c

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <PiSmm.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
//#include <Token.h>
#include <Protocol/SmmBase2.h>
#include <PspCspLib.h>
#include <Protocol/AmdCapsuleSmmHookProtocol.h>
#include <Protocol/SmmSxDispatch2.h>
#include <AmiDxeLib.h>
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)


// Type Definition(s)


//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)


BOOLEAN IsFamily15h(
    VOID );
/**
    This elink is to provide a call for sending Psp Mbox message
    for a Sx notification.

    @param VOID

    @retval VOID

**/
VOID
AmiPspCapsuleCallback(VOID)
{

    AMD_CAPSULE_SMM_HOOK_PROTOCOL   *AmdCapsuleSmmHookProtocol;
    UINT8                           Value8;
    EFI_STATUS                      Status;
    UINT32                          PspSxFlag;

    // Set a flag here for the indication of capsule
    IoWrite8 (0x72, PcdGet8(PcdCmosAgesaSpecified));
    Value8 = IoRead8(0x73);
    Value8 |= BIT6;
    IoWrite8(0x73, Value8);

    DEBUG ((DEBUG_INFO, "AmiPspCapsuleCallback entry \n"));

    Status = pSmst->SmmLocateProtocol (
                      &gAmdCapsuleSmmHookProtocolGuid,
                      NULL,
                      &AmdCapsuleSmmHookProtocol
                      );
    if (Status == EFI_SUCCESS)
    {
        PspSxFlag = PSP_CAPSULE_HOOK_FLAG_SXINFO_CLRSMMLCK;
//        if (PcdGetBool (PcdAmdS3SmmLockClearEnable))
        {
            if (IsFamily15h())
            {
                PspSxFlag = PSP_CAPSULE_HOOK_FLAG_SXINFO_NOCLRSMMLCK;
            }
        }
        AmdCapsuleSmmHookProtocol->Hook(PspSxFlag);
    }

    DEBUG ((DEBUG_INFO, "AmiPspCapsuleCallback exit \n"));
        
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
