
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include <AaeonElinkFunctions.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
typedef EFI_STATUS (AAEON_DXE_INIT_HOOK)();

extern AAEON_DXE_INIT_HOOK AAEON_DXE_INIT_FUNCTIONS EndOfAaeonDxeInitFunctions;
AAEON_DXE_INIT_HOOK *AaeonDxeInitFun[] = { AAEON_DXE_INIT_FUNCTIONS NULL };

typedef EFI_STATUS (AAEON_READY_TO_BOOT_INIT_HOOK)();

extern AAEON_DXE_INIT_HOOK AAEON_READY_TO_BOOT_INIT_FUNCTIONS EndOfAaeonReadytobootFunctions;
AAEON_DXE_INIT_HOOK *AaeonReadytobootFun[] = { AAEON_READY_TO_BOOT_INIT_FUNCTIONS NULL };
// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
VOID RayDebug80(UINT8 Time, UINT8 Code){
	UINTN i;
	
	i = 0x0FFFF | (Time << 16);
	while(i != 0){
		IoWrite8(0x80, Code);
		i--;
	}
}
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)
//---------------------------------------------------------------------------
VOID AaeonReadyToBootEvent(IN EFI_EVENT Event, IN VOID *Context)
{
	EFI_STATUS	Status;
	UINTN		i = 0;

	for(i = 0; AaeonReadytobootFun[i] != NULL; i++)
	{
		Status = AaeonReadytobootFun[i]();
	}

	pBS->CloseEvent(Event);
}

EFI_STATUS
EFIAPI
AaeonCommonDxeReset (
  )
{
	EFI_STATUS Status = EFI_SUCCESS;
    	EFI_GUID	SetupGuid = SETUP_GUID;
    	SETUP_DATA	SetupData;
    	UINTN		VariableSize = sizeof(SetupData);
    	UINT32		Attribute = 0;

	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );

	if( // Flags Validation _Begin >>
		//#if defined(AaeonDioPkg_SUPPORT) && (AaeonDioPkg_SUPPORT == 1)
		//	SetupData.AaeonDioRunOnce == 0 ||
		//#endif

		SetupData.AaeonCommonFeaturesSyncReady == 0 ||
		// ...
		0x00 // Flags Validation _End <<
	)
	{
		// Confirm Flags _Begin >>
		//#if defined(AaeonDioPkg_SUPPORT) && (AaeonDioPkg_SUPPORT == 1)
		//	SetupData.AaeonDioRunOnce = 1;
		//#endif
		SetupData.AaeonCommonFeaturesSyncReady = 1;

		// ...
		// Confirm Flags _End <<

		Status = pRS->SetVariable( L"Setup", &SetupGuid, Attribute, VariableSize, &SetupData);

		RayDebug80(0x02, 0xEE);
		IoWrite8(0xCF9, 0x06);
	} //if(SetupData.AaeonDioRunOnce == 0)
	return Status;
}

EFI_STATUS
EFIAPI
AaeonCommonDxeInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	EFI_STATUS Status = EFI_SUCCESS;
	UINTN	i;
//    	EFI_GUID	SetupGuid = SETUP_GUID;
//    	SETUP_DATA	SetupData;
//    	UINTN		VariableSize = sizeof(SetupData);
	EFI_EVENT    EvtReadyToBoot;

	InitAmiLib(ImageHandle, SystemTable);
//	
//	Status = pRS->GetVariable( L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData );
	CreateReadyToBootEvent(TPL_NOTIFY, AaeonReadyToBootEvent, NULL, &EvtReadyToBoot);

	for(i = 0; AaeonDxeInitFun[i] != NULL; i++)
	{
	    Status = AaeonDxeInitFun[i]();
	}
	
	return Status;
}
