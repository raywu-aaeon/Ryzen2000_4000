//----------------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSxDispatch2.h>
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
typedef EFI_STATUS (AAEON_SX_SMI_HOOK)(SETUP_DATA *SetupData);

extern AAEON_SX_SMI_HOOK AAEON_S3_SMI_FUNCTIONS EndOfAaeonSxSmiFunctions;
AAEON_SX_SMI_HOOK *AaeonS3SmiFunction[] = { AAEON_S3_SMI_FUNCTIONS NULL };

extern AAEON_SX_SMI_HOOK AAEON_S4_SMI_FUNCTIONS EndOfAaeonSxSmiFunctions;
AAEON_SX_SMI_HOOK *AaeonS4SmiFunction[] = { AAEON_S4_SMI_FUNCTIONS NULL };

extern AAEON_SX_SMI_HOOK AAEON_S5_SMI_FUNCTIONS EndOfAaeonSxSmiFunctions;
AAEON_SX_SMI_HOOK *AaeonS5SmiFunction[] = { AAEON_S5_SMI_FUNCTIONS NULL };

EFI_GUID	gSetupGuid = SETUP_GUID;
SETUP_DATA	gSetupData;
//----------------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------------
// Variable Declaration(s)
EFI_STATUS S3SleepSmiOccurred (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
{
	EFI_STATUS	Status;
	UINTN		i;

	for(i = 0; AaeonS3SmiFunction[i] != NULL; i++)
	{
	    Status = AaeonS3SmiFunction[i](&gSetupData);
	}

	return Status;
}
EFI_STATUS S4SleepSmiOccurred (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
{
	EFI_STATUS	Status;
	UINTN		i;

	for(i = 0; AaeonS4SmiFunction[i] != NULL; i++)
	{
	    Status = AaeonS4SmiFunction[i](&gSetupData);
	}

	return Status;
}
EFI_STATUS S5SleepSmiOccurred (
	IN EFI_HANDLE       DispatchHandle,
	IN CONST VOID       *DispatchContext OPTIONAL,
	IN OUT VOID         *CommBuffer OPTIONAL,
	IN OUT UINTN        *CommBufferSize OPTIONAL )
{
	EFI_STATUS	Status;
	UINTN		i;

	for(i = 0; AaeonS5SmiFunction[i] != NULL; i++)
	{
	    Status = AaeonS5SmiFunction[i](&gSetupData);
	}

	return Status;
}

EFI_STATUS InSmmFunction (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
	EFI_STATUS	Status;
	EFI_HANDLE	hS3Smi;
	EFI_HANDLE	hS4Smi;
	EFI_HANDLE	hS5Smi;
	EFI_SMM_SX_DISPATCH2_PROTOCOL    *SxDispatch;
	EFI_SMM_SX_REGISTER_CONTEXT     S3DispatchContext = {SxS3, SxEntry};
	EFI_SMM_SX_REGISTER_CONTEXT     S4DispatchContext = {SxS4, SxEntry};
	EFI_SMM_SX_REGISTER_CONTEXT     S5DispatchContext = {SxS5, SxEntry};

	Status = InitAmiSmmLib( ImageHandle, SystemTable );
	if (EFI_ERROR(Status)) return Status;
	Status = pSmst->SmmLocateProtocol( &gEfiSmmSxDispatch2ProtocolGuid , \
	                                   NULL, \
	                                   &SxDispatch );

	if (EFI_ERROR(Status)) return Status;

	// Register Sleep SMI Handlers
	Status = SxDispatch->Register( SxDispatch, \
	                               S3SleepSmiOccurred, \
	                               &S3DispatchContext, \
	                               &hS3Smi );
	if (EFI_ERROR(Status)) return Status;

	Status = SxDispatch->Register( SxDispatch, \
	                               S4SleepSmiOccurred, \
	                               &S4DispatchContext, \
	                               &hS4Smi );
	if (EFI_ERROR(Status)) return Status;

	Status = SxDispatch->Register( SxDispatch, \
	                               S5SleepSmiOccurred, \
	                               &S5DispatchContext, \
	                               &hS5Smi );
	return Status;
}

EFI_STATUS AaeonSxSmi_Init (
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