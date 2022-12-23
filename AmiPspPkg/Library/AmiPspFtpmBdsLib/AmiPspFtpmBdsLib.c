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

/** @file AmiPspfTpmLib.c
    This file contains code for AmiPspfTpmLib base library.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Uefi.h>
#include <Token.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Guid/AmiPsp.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SmmCommunication.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

#if (SOLUTION_TYPE == 1)
CHAR16 *CpuSwapString = L"\n New CPU installed, fTPM NV corrupted or fTPM NV structure changed.\n";
#else if (SOLUTION_TYPE == 0)
CHAR16 *CpuSwapString = L"\n fTPM NV corrupted or fTPM NV structure changed.\n";
#endif
CHAR16 *YesString_1 = L"    Press Y to reset fTPM, if you have BitLocker or encryption-enabled system, ";
CHAR16 *YesString_2 = L"    the system will not boot without a recovery key\n";
CHAR16 *NoString_1  = L"    Press N to keep previous fTPM record and continue system boot, fTPM will NOT";
CHAR16 *NoString_2  = L"    be enabled with new CPU unless fTPM is reset (reinitialized), you could swap";
CHAR16 *NoString_3  = L"    back to the old CPU to recover TPM related Keys and data\n";

EFI_SMM_COMMUNICATION_PROTOCOL  *SmmCommunication = NULL;
UINT8                           *CommunicateBuffer = NULL;
UINTN                           CommunicateBufferSize;
// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

/**
   This function issues a smi with end-user's decision.

  @param IN BOOLEAN Selection - A decision that made by end-user
                                Yes = clear TPM NV
                                No  = continue booting

    @retval None
 */
VOID AmiPspFtpmNvSmi(
    IN UINT8 Selection)
{
    EFI_STATUS                  Status;
    EFI_SMM_COMMUNICATE_HEADER  *SmmCommunicateHeader;

    DEBUG((DEBUG_INFO, "AmiPspFtpmNvSmi Entry\n"));

    //
    // Copy Smm Communicate Header Here
    //
    SmmCommunicateHeader = (EFI_SMM_COMMUNICATE_HEADER *)CommunicateBuffer;

    gBS->CopyMem(&SmmCommunicateHeader->HeaderGuid, &gAmiPspFtpmSmmCommunicationGuid, sizeof(EFI_GUID));
    SmmCommunicateHeader->MessageLength = 1;
    SmmCommunicateHeader->Data[0] = Selection;

    //
    // Issue the Smi.
    //
    Status = gBS->LocateProtocol(&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &SmmCommunication);
    DEBUG((DEBUG_INFO, "LocateProtocol SmmCommunication = %x\n", Status));
    if (EFI_ERROR(Status)) {
        SmmCommunication = NULL;
    }

    if (SmmCommunication != NULL)
    {
        Status = SmmCommunication->Communicate(SmmCommunication, CommunicateBuffer, &CommunicateBufferSize);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return;
        }
    }

    // Free the Memory Allocated for Communication.
    Status = gBS->FreePool(CommunicateBuffer);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return;
    }
   
}

/**
  This function is to display messages to notify user of CPU swapped, PSP NVRAM corrupted.
  User need determine to clear PSP NVRAM or not.

  @retval None
*/

VOID AmiPspFtpmDisplay ()
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    AMI_POST_MANAGER_PROTOCOL   *PostManager = NULL;
    EFI_INPUT_KEY               KeyData;
    UINT8                       Selection;

    DEBUG((DEBUG_INFO, "AmiPspFtpmDisplay Entry\n"));
    
    if (PcdGet32(PcdFtpmSmmCommunicateBuffer) == 0)
        return;

    CommunicateBuffer = (UINT8*)PcdGet32(PcdFtpmSmmCommunicateBuffer);
    DEBUG((DEBUG_INFO, "PcdFtpmSmmCommunicateBuffer = 0x%lx \n", CommunicateBuffer));

    CommunicateBufferSize = (UINTN)PcdGet32(PcdFtpmSmmCommunicateBufferSize);
    DEBUG((DEBUG_INFO, "PcdFtpmSmmCommunicateBufferSize = 0x%lx \n", CommunicateBufferSize));
    
    // locate the Ami Post Manager Protocol
    Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, (VOID **)&PostManager);
    if (EFI_ERROR(Status)) return;

    // Ensure screen is in Verbose mode
    PostManager->SwitchToPostScreen();

    // display Prompt
    PostManager->DisplayPostMessage(CpuSwapString);
    PostManager->DisplayPostMessage(YesString_1);
    PostManager->DisplayPostMessage(YesString_2);
    PostManager->DisplayPostMessage(NoString_1);
    PostManager->DisplayPostMessage(NoString_2);
    PostManager->DisplayPostMessage(NoString_3);

    do{
        Status = gST->ConIn->ReadKeyStroke(gST->ConIn, &KeyData);
        //DEBUG((DEBUG_INFO, "ReadKeyStroke status = %r\n", Status));
        if(Status ==  EFI_SUCCESS)
        {
            if ((KeyData.UnicodeChar == L'y') || (KeyData.UnicodeChar == L'Y'))
            {
                //yes
                DEBUG((DEBUG_INFO,"Yes key is pressed\n"));
                Selection = 1;
                AmiPspFtpmNvSmi(Selection);
                gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
            }
            else if ((KeyData.UnicodeChar == L'n') || (KeyData.UnicodeChar == L'N'))
            {
                //no
                DEBUG((DEBUG_INFO,"No key is pressed\n"));
                Selection = 0;
                AmiPspFtpmNvSmi(Selection);
                break;
            }
        }
    }while(TRUE);

    return;
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
