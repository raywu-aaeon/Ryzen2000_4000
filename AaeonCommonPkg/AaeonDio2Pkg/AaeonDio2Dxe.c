
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include "AaeonDio2.h"

// Produced Protocols

// Consumed Protocols

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

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------
EFI_STATUS
EFIAPI
AaeonDio2DxeInit (
)
{
	EFI_STATUS 	Status = EFI_SUCCESS;
    	EFI_GUID	SetupGuid = SETUP_GUID;
    	SETUP_DATA	SetupData;
    	UINTN		VariableSize = sizeof(SetupData);
    	UINT32		Attribute = 0;

	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);

	if(SetupData.AaeonCommonFeaturesSyncReady == 0)
	{
		Status = DioInit(&SetupData);

		Status = pRS->SetVariable( L"Setup", &SetupGuid, Attribute, VariableSize, &SetupData);
	} //if(SetupData.AaeonCommonFeaturesSyncReady == 0)

	return Status;
}
