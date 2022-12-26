//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AaeonPowerMode.c
//
// Description:	Need porting for different board
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include <AmiLib.h>
#include <token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AcpiRes.h>
#include <Protocol/SmmSxDispatch2.h>

extern  EFI_BOOT_SERVICES   *pBS;

EFI_GUID gSetupGuid                     = SETUP_GUID;
SETUP_DATA gSetupData;

//**********************************************************************
EFI_STATUS S5SmiCallback (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL )
{
	// TODO: Display message for shutdown system

	// System enter deadloop here for AT power mode
	EFI_DEADLOOP();

    return EFI_SUCCESS;
}


EFI_STATUS NotInSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    return EFI_SUCCESS;
}

EFI_STATUS InSmmFunction(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS  Status;
    EFI_SMM_SX_REGISTER_CONTEXT       SxDispatchContext;
    EFI_SMM_SX_DISPATCH2_PROTOCOL      *SxDispatchProtocol;
    EFI_HANDLE                        SxDispatchHandle;

    Status = pSmst->SmmLocateProtocol(&gEfiSmmSxDispatch2ProtocolGuid, NULL, &SxDispatchProtocol);
    if (EFI_ERROR(Status)) return Status;

	// Register the callback for S5 entry
    SxDispatchContext.Type  = SxS5;
    SxDispatchContext.Phase = SxEntry;
    Status = SxDispatchProtocol->Register(SxDispatchProtocol, S5SmiCallback, &SxDispatchContext, &SxDispatchHandle);

    ASSERT_EFI_ERROR (Status); 

    return Status;
}

EFI_STATUS EFIAPI AaeonPowerModeSmmInit (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    EFI_STATUS    Status ;
    UINTN        Size = sizeof(SETUP_DATA) ;

    InitAmiLib(ImageHandle, SystemTable);
    TRACE((-1, "AaeonPowerModeSmmInit Start\n"));

    Status = pRS->GetVariable( L"Setup", &gSetupGuid, NULL, &Size, &gSetupData);
    if(!EFI_ERROR(Status)){
        //
        //Register Handlers for AT power mode
        //
        if(gSetupData.AaeonPowerMode == 1)
            Status = InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NotInSmmFunction);
    }
    return Status;
}
