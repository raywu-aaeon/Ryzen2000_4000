
#include <Setup.h>
#include <AmiCspLibInc.h>
#include <AmiDxeLib.h>

EFI_STATUS Ptn3460CallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
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

			// Coding here for project function support
			// >>
			// Source:
			//		
			//		
			//		
			//		

			// <<
		}

		Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	}

	return EFI_SUCCESS;
}