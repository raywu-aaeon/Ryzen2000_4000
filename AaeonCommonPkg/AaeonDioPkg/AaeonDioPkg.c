
#include <Setup.h>
#include <AmiCspLibInc.h>
#include <AmiDxeLib.h>

//VOID RayDebug80(UINT8 Time, UINT8 Code){
//	UINTN i;
//	
//	i = 0x0FFFF | (Time << 16);
//	while(i != 0){
//		IoWrite8(0x80, Code);
//		i--;
//	}
//}

EFI_STATUS AaeonDioCallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
	CALLBACK_PARAMETERS	*Callback;
	//EFI_BROWSER_ACTION_REQUEST	*CallbackActionRequest;
	
	Callback = GetCallbackParameters();
        //CallbackActionRequest = Callback->ActionRequest;

	if(!Callback)
		return EFI_SUCCESS;
	//TRACE((-1,"Callback->Action=%x\n",  Callback->Action));

	if (Callback->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD)
		return EFI_UNSUPPORTED; 
    
	if (Callback->Action == EFI_BROWSER_ACTION_FORM_OPEN || Callback->Action == EFI_BROWSER_ACTION_CHANGING)
		return EFI_SUCCESS;

	if (Callback->Action == EFI_BROWSER_ACTION_FORM_CLOSE)
	{
		EFI_STATUS		Status;
    		EFI_GUID		SetupGuid = SETUP_GUID;
    		SETUP_DATA		SetupData;
    		UINTN			VariableSize = sizeof(SetupData);
    		UINT32			Attribute = 0;
//		//UINTN			BrowserSetupSize = sizeof(SETUP_DATA);
//		//SETUP_DATA		*BrowserSetupData = NULL;
//		//EFI_GUID		BrowserSetupGuid = SETUP_GUID;
//
//		//Status = HiiLibGetBrowserData (&BrowserSetupSize, BrowserSetupData, &BrowserSetupGuid, L"Setup");
		Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );

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

		//SetupData.AaeonDioRunOnce = 1;
		Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	}

	return EFI_SUCCESS;
}