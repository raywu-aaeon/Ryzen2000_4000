
#include <Setup.h>
#include <AmiCspLibInc.h>
#include <AmiDxeLib.h>
#include <SioSetup.h>

//extern VOID RayDebug80(UINT8 Time, UINT8 Code);

EFI_STATUS AaeonUartModeCallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
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
		Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );
//		//Status = HiiLibGetBrowserData (&BrowserSetupSize, BrowserSetupData, &BrowserSetupGuid, L"Setup");

		// Data of setup variable API transmission
		{
			EFI_GUID		SioSetupGuid = SIO_VARSTORE_GUID;
			UINTN			SioVariableSize = sizeof(SIO_DEV_NV_DATA);
			SIO_DEV_NV_DATA		SioSetupData;
			EFI_STRING		SioNvDataName;

			// Reference to Build/GSIOSETUPVAR.H for "SioNvDataName" definition
			// Define what UART port you want to support UART modes selection

			SioNvDataName = L"";
			Status = pRS->GetVariable( SioNvDataName, &SioSetupGuid, NULL, &SioVariableSize, &SioSetupData );
			// Coding here for project function support
			// >>
			// Source:
			//		SioSetupData.DevMode
			{
				switch(SioSetupData.DevMode)
				{
					case 0: //RS232
						break;

					case 1: //RS422
						break;

					case 2: //RS485
						break;

					default:
						break;

				}
			}

			//SioNvDataName = L"";
			//Status = pRS->GetVariable( SioNvDataName, &SioSetupGuid, NULL, &SioVariableSize, &SioSetupData );
			//// Coding here for project function support
			//// >>
			//// Source:
			////		SioSetupData.DevMode
			//{
			//	switch(SioSetupData.DevMode)
			//	{
			//		case 0: //RS232
			//			break;
			//		case 1: //RS422
			//			break;
			//		case 2: //RS485
			//			break;
			//		default:
			//			break;
			//	}
			//}

			// <<
		}

		Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	}

	return EFI_SUCCESS;
}