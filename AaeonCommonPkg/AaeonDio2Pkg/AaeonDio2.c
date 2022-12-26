
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include <AaeonCommonLib.h>
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
EFI_STATUS
EFIAPI
DioInit ( 
	IN SETUP_DATA	*SetupData
)
{
	EFI_STATUS 	Status = EFI_SUCCESS;
	UINT8		ChipType = SetupData->AaeonDio2Source;
	UINT8		i, DioVal, DioType, DioNum;

	for (i = 0; i < 8; i++)
	{
		DioNum = SetupData->AaeonDio2Gpio[i];
		DioVal = SetupData->DIO_LV[i];
		DioType = SetupData->DIO[i];
		AaeonSetGpio(DioNum, DioVal, DioType, ChipType, SetupData);

		#if defined(SECOND_DIO_SUPPORT) && (SECOND_DIO_SUPPORT == 1)			
		DioNum = SetupData->AaeonDio22Gpio[i];
		DioVal = SetupData->DIO2_LV[i];
		DioType = SetupData->DIO2[i];
		AaeonSetGpio(DioNum, DioVal, DioType, ChipType, SetupData);
		#endif //SECOND_DIO_SUPPORT == 1
	}	
	
	return Status;
}