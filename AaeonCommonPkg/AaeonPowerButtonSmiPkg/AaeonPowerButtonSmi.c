//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <AaeonElinkFunctions.h>

//----------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------------
// Constant Definition(s)
//VOID RayDebug80(UINT8 Time, UINT8 Code){
//	UINTN i;
//	
//	i = 0x0FFFF | (Time << 16);
//	while(i != 0){
//		IoWrite8(0x80, Code);
//		i--;
//	}
//}

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
typedef EFI_STATUS (AAEON_POWER_BUTTON_SMI_HOOK)(IN SETUP_DATA *SetupData);

extern AAEON_POWER_BUTTON_SMI_HOOK AAEON_POWER_BUTTON_SMI_FUNCTIONS EndOfAaeonPowerButtonSmiFunctions;
AAEON_POWER_BUTTON_SMI_HOOK *AaeonPowerButtonSmiFunction[] = { AAEON_POWER_BUTTON_SMI_FUNCTIONS NULL };

EFI_GUID	gSetupGuid = SETUP_GUID;
UINT32      gSetupAttr;
SETUP_DATA	gSetupData;
//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)

EFI_STATUS AaeonPwrBtnHandler (
    IN EFI_HANDLE       DispatchHandle,
    IN CONST VOID       *DispatchContext OPTIONAL,
    IN OUT VOID         *CommBuffer OPTIONAL,
    IN OUT UINTN        *CommBufferSize OPTIONAL
)
{
	UINT8 i;
	EFI_STATUS Status = EFI_SUCCESS;
	
	for(i = 0; AaeonPowerButtonSmiFunction[i] != NULL; i++)
	{
	    Status = AaeonPowerButtonSmiFunction[i](&gSetupData);
	}

	return EFI_SUCCESS;
}

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
    EFI_STATUS                              Status;
    EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *PowerButton;
    EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT   DispatchContext = {EfiPowerButtonEntry};
    EFI_HANDLE                              Handle = NULL;


    Status  = pSmst->SmmLocateProtocol (
                      &gEfiSmmPowerButtonDispatch2ProtocolGuid,
                      NULL,
                      &PowerButton
                      );

    if (EFI_ERROR(Status)) return Status;

    Status = PowerButton->Register (
                            PowerButton,
                            AaeonPwrBtnHandler,
                            &DispatchContext,
                            &Handle
                            );

    return Status;
}

EFI_STATUS AaeonPowerButtonSmi_Init (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
	EFI_STATUS	Status;
	UINTN	    VariableSize = sizeof(SETUP_DATA);

	InitAmiLib(ImageHandle, SystemTable);
	Status = pRS->GetVariable( L"Setup", &gSetupGuid, NULL, &VariableSize, &gSetupData);
	if(EFI_ERROR(Status)) return Status;

	return InitSmmHandler(ImageHandle, SystemTable, InSmmFunction, NULL);
}