
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include <AaeonCommonLib.h>
#include "AaeonDio3.h"

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
EFI_STATUS
EFIAPI
DioInit ( 
	IN SETUP_DATA	*SetupData
)
{
	EFI_STATUS 	Status = EFI_SUCCESS;
	UINT8		ChipType;
	UINT8		i, DioVal, DioType, DioNum;

	for (i = 0; i < FIRST_DIO_NUMBER; i++)
	{
		DioNum = SetupData->DioGpioNum[i];
		DioVal = SetupData->DioLevel[i];
		DioType = SetupData->DioDirection[i];
		ChipType = SetupData->DioSource;
		AaeonSetGpio(DioNum, DioVal, DioType, ChipType, SetupData);
	}	
	
#if (SECOND_DIO_NUMBER > 0)
	for (i = 0; i < SECOND_DIO_NUMBER; i++)
	{			
		DioNum = SetupData->Dio2GpioNum[i];
		DioVal = SetupData->Dio2Level[i];
		DioType = SetupData->Dio2Direction[i];
		ChipType = SetupData->Dio2Source;
		AaeonSetGpio(DioNum, DioVal, DioType, ChipType, SetupData);
	}
#endif //SECOND_DIO_NUMBER > 0

// TODO: Porting may be required if 3rd DIO controller is supported.
#if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
	for (i = 0; i < SECOND_DIO_NUMBER; i++)
	{			
		DioNum = SetupData->Dio3GpioNum[i];
		DioVal = SetupData->Dio3Level[i];
		DioType = SetupData->Dio3Direction[i];
		ChipType = SetupData->Dio3Source;
		AaeonSetGpio(DioNum, DioVal, DioType, ChipType, SetupData);
	}
#endif //THIRD_DIO_NUMBER > 0

	return Status;
}

EFI_STATUS
EFIAPI
AaeonDio3DxeInit (
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
