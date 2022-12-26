
#include <Setup.h>
#include <AmiCspLibInc.h>
#include <AmiDxeLib.h>
#include "AaeonDio2.h"

EFI_STATUS AaeonDio2CallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
	EFI_STATUS	Status;
    	EFI_GUID	SetupGuid = SETUP_GUID;
    	SETUP_DATA	SetupData;
    	UINTN		VariableSize = sizeof(SetupData);
    	UINT32		Attribute = 0;

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
		Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);
	
		Status = DioInit(&SetupData);

		Status = pRS->SetVariable( L"Setup", &SetupGuid, Attribute, VariableSize, &SetupData);
	}

	return EFI_SUCCESS;
}