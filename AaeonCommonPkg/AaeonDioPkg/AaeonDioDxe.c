
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.


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
AaeonDioDxeInit (
)
{
	EFI_STATUS Status = EFI_SUCCESS;
    	EFI_GUID	SetupGuid = SETUP_GUID;
    	SETUP_DATA	SetupData;
    	UINTN		VariableSize = sizeof(SetupData);
    	UINT32		Attribute = 0;

	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );

	//if(SetupData.AaeonDioRunOnce == 0){
	if(SetupData.AaeonCommonFeaturesSyncReady == 0){
		{
			UINT8	i, DioInOut_Data8[8], DioOutLevel_Data8[8];

			#if defined(SECOND_DIO_SUPPORT) && (SECOND_DIO_SUPPORT == 1)
			UINT8	SecondDioInOut_Data8[8], SecondDioOutLevel_Data8[8];
			#endif
	
			for (i = 0; i < 8; i++)
			{
				DioInOut_Data8[i] = SetupData.DIO[i];
				DioOutLevel_Data8[i] = SetupData.DIO_LV[i];
			}
			#if defined(SECOND_DIO_SUPPORT) && (SECOND_DIO_SUPPORT == 1)
			{			
				for (i = 0; i < 8; i++)
				{
					SecondDioInOut_Data8[i] = SetupData.DIO2[i];
					SecondDioOutLevel_Data8[i] = SetupData.DIO2_LV[i];
				}
			}
			#endif //SECOND_DIO_SUPPORT == 1
			// Coding here for project function support
			// >>
			// Source:
			//		DioInOut_Data8[8]
			//		DioOutLevel_Data8[8]
			//		SecondDioInOut_Data8[8]
			//		SecondDioOutLevel_Data8[8]

			// <<
		}
		
		Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	} //if(SetupData.AaeonCommonFeaturesSyncReady == 0)
	return Status;
}
