#include <Setup.h>
#include <AmiCspLibInc.h>
#include <AmiDxeLib.h>
#include <token.h>
#include <AutoId.h>

#define ACLOSS_SRC_SB 0
#define ACLOSS_SRC_SIO 1

#define ACLOSS_LAST_STATE  0
#define ACLOSS_ALWAYS_ON   1
#define ACLOSS_ALWAYS_OFF  2

UINT8 MapToACPowerLoss[3] = STATEAFTERG3_MAP;

EFI_STATUS AaeonAcLossCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
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
			if (SetupData.AaeonPowerMode == 1)
			{
		    	//sync ac-powerlose item to "Always-on"
#if CRB_USE_VAR_STATEAFTERG3
				SetupData.StateAfterG3 = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#else
				SetupData.LastState = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#endif 


				#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
		    		SetupData.F81866RestoreACPowerLoss = 1;
				#endif
				#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
		    		SetupData.F81966RestoreACPowerLoss = 1;
				#endif		
				#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
		    		SetupData.F81804RestoreACPowerLoss = 1;
				#endif					    		
				#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
		    		SetupData.IT8728FRestoreACPowerLoss = 1;
				#endif
				#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
		    		SetupData.IT8625RestoreACPowerLoss = 1;
				#endif
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
		    		SetupData.NCT6791D_AC_PWR_LOSS = 1;
				#endif				
			} else 
			{
				switch (SetupData.AaeonRestoreACPowerLossSrc)
				{
					case ACLOSS_SRC_SB:
					default:
					{
#if CRB_USE_VAR_STATEAFTERG3
						SetupData.StateAfterG3 = MapToACPowerLoss[SetupData.AaeonRestoreACPowerLoss];
#else
						SetupData.LastState = MapToACPowerLoss[SetupData.AaeonRestoreACPowerLoss];
#endif 	

						//Patch SIO to bypass mode.
						//Note: If SIO doesn't support bypass mode, AC power loss function
						//      is always controlled by SIO
						#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
							SetupData.F81866RestoreACPowerLoss = 3;
						#endif
						#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
		    				SetupData.F81966RestoreACPowerLoss = 3;
						#endif				
						#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
		    				SetupData.F81804RestoreACPowerLoss = 3;
						#endif											
						#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
							SetupData.NCT6791D_AC_PWR_LOSS = 4;
						#endif
						#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
							SetupData.IT8728FRestoreACPowerLoss = 3;
						#endif
						#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
							SetupData.IT8625RestoreACPowerLoss = 3;
						#endif
					}
					break;

					case ACLOSS_SRC_SIO:
					{
						#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
							switch (SetupData.AaeonRestoreACPowerLoss)
							{
								case ACLOSS_LAST_STATE:
									SetupData.F81866RestoreACPowerLoss = 0;
									break;
								case ACLOSS_ALWAYS_ON:
									SetupData.F81866RestoreACPowerLoss = 1;
									break;
								case ACLOSS_ALWAYS_OFF: default:
									SetupData.F81866RestoreACPowerLoss = 2;
									break;
							}
						#endif
						#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
							switch (SetupData.AaeonRestoreACPowerLoss)
							{
								case ACLOSS_LAST_STATE:
									SetupData.F81966RestoreACPowerLoss = 0;
									break;
								case ACLOSS_ALWAYS_ON:
									SetupData.F81966RestoreACPowerLoss = 1;
									break;
								case ACLOSS_ALWAYS_OFF: default:
									SetupData.F81966RestoreACPowerLoss = 2;
									break;
							}
						#endif		
						#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
							switch (SetupData.AaeonRestoreACPowerLoss)
							{
								case ACLOSS_LAST_STATE:
									SetupData.F81804RestoreACPowerLoss = 0;
									break;
								case ACLOSS_ALWAYS_ON:
									SetupData.F81804RestoreACPowerLoss = 1;
									break;
								case ACLOSS_ALWAYS_OFF: default:
									SetupData.F81804RestoreACPowerLoss = 2;
									break;
							}
						#endif												
						#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
							switch (SetupData.AaeonRestoreACPowerLoss)
							{
								case ACLOSS_LAST_STATE:
									SetupData.IT8728FRestoreACPowerLoss = 0;
									break;
								case ACLOSS_ALWAYS_ON:
									SetupData.IT8728FRestoreACPowerLoss = 1;
									break;
								case ACLOSS_ALWAYS_OFF: default:
									SetupData.IT8728FRestoreACPowerLoss = 2;
									break;
							}
						#endif
						#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
							switch (SetupData.AaeonRestoreACPowerLoss)
							{
								case ACLOSS_LAST_STATE:
									SetupData.IT8625RestoreACPowerLoss = 0;
									break;
								case ACLOSS_ALWAYS_ON:
									SetupData.IT8625RestoreACPowerLoss = 1;
									break;
								case ACLOSS_ALWAYS_OFF: default:
									SetupData.IT8625RestoreACPowerLoss = 2;
									break;
							}
						#endif
						#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
							switch (SetupData.AaeonRestoreACPowerLoss)
							{
								case ACLOSS_LAST_STATE:
									SetupData.NCT6791D_AC_PWR_LOSS = 2;
									break;
								case ACLOSS_ALWAYS_ON:
									SetupData.NCT6791D_AC_PWR_LOSS = 1;
									break;
								case ACLOSS_ALWAYS_OFF: default:
									SetupData.NCT6791D_AC_PWR_LOSS = 0;
									break;
							}
						#endif
						//AAEON_APL_OVERRIDE, Patch Chipset to always on
#if CRB_USE_VAR_STATEAFTERG3
						SetupData.StateAfterG3 = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#else
						SetupData.LastState = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#endif 
					}
					break;
				}
			}
		}
		//SetupData.AaeonDioRunOnce = 1;
		Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	}

	return EFI_SUCCESS;
}
EFI_STATUS AaeonErpCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
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
			if (SetupData.AaeonErpMode == 1)
			{
				#if defined(F81866_ERP_SUPPORT) && (F81866_ERP_SUPPORT == 1)
					SetupData.F81866ErpMode = 2;
				#endif
				#if defined(F81966_ERP_SUPPORT) && (F81966_ERP_SUPPORT == 1)
					SetupData.F81966ErpMode = 2;
				#endif			
				#if defined(F81804_ERP_SUPPORT) && (F81804_ERP_SUPPORT == 1)
					SetupData.F81804ErpMode = 2;
				#endif							
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
					SetupData.NCT6791DDeepS5 = 1;
				#endif
			}
			else
			{ 
				#if defined(F81866_ERP_SUPPORT) && (F81866_ERP_SUPPORT == 1)
					SetupData.F81866ErpMode = 0;
				#endif
				#if defined(F81966_ERP_SUPPORT) && (F81966_ERP_SUPPORT == 1)
					SetupData.F81966ErpMode = 0;
				#endif	
				#if defined(F81804_ERP_SUPPORT) && (F81804_ERP_SUPPORT == 1)
					SetupData.F81804ErpMode = 0;
				#endif								
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
					SetupData.NCT6791DDeepS5 = 0;
				#endif
			}
		}

		//SetupData.AaeonDioRunOnce = 1;
		Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	}

	return EFI_SUCCESS;
}

//static EFI_GUID  gSetupGuid = SETUP_GUID;
//
////EFI_STATUS AaeonAcLossUpdate(SETUP_DATA *SetupData, UINT8 ActSrc, UINT8 Action)
//EFI_STATUS AaeonAcLossUpdate(SETUP_DATA *SetupData)
//{
//    EFI_STATUS  Status = EFI_SUCCESS;
//    
//    //if (ActSrc == ACLOSS_SRC_SB)
//    if (SetupData->AaeonRestoreACPowerLossSrc == ACLOSS_SRC_SB)
//    {
//    	//switch (Action)
//    	switch (SetupData->AaeonRestoreACPowerLoss)
//    	{
//    		case ACLOSS_LAST_STATE:
//        		SetupData->LastState = 2;
//        		break;
//    		case ACLOSS_ALWAYS_ON:
//        		SetupData->LastState = 1;
//        		break;
//    		case ACLOSS_ALWAYS_OFF: default:
//        		SetupData->LastState = 0;
//        		break;
//    	}
//
//    	//Patch SIO to bypass mode.
//    	//Note: If SIO doesn't support bypass mode, AC power loss function
//    	//      is always controlled by SIO
//	#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
//		SetupData->F81866RestoreACPowerLoss = 3;
//	#endif
//	#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
//		SetupData->NCT6791D_AC_PWR_LOSS = 4;
//	#endif
//
//    //} else if(ActSrc == ACLOSS_SRC_SIO)
//    } else if(SetupData->AaeonRestoreACPowerLossSrc == ACLOSS_SRC_SIO)
//    { 
//	#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
//    	//switch (Action)
//    	switch (SetupData->AaeonRestoreACPowerLoss)
//    	{
//    		case ACLOSS_LAST_STATE:
//        		SetupData->F81866RestoreACPowerLoss = 0;
//        		break;
//    		case ACLOSS_ALWAYS_ON:
//        		SetupData->F81866RestoreACPowerLoss = 1;
//        		break;
//    		case ACLOSS_ALWAYS_OFF: default:
//        		SetupData->F81866RestoreACPowerLoss = 2;
//        		break;
//    	}
//	#endif
//	#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
//	switch (SetupData->AaeonRestoreACPowerLoss)
//	{
//		case ACLOSS_LAST_STATE:
//			SetupData->IT8728FRestoreACPowerLoss = 0;
//			break;
//		case ACLOSS_ALWAYS_ON:
//			SetupData->IT8728FRestoreACPowerLoss = 1;
//			break;
//		case ACLOSS_ALWAYS_OFF: default:
//			SetupData->IT8728FRestoreACPowerLoss = 2;
//			break;
//	}
//	#endif
//	#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
//	switch (SetupData->AaeonRestoreACPowerLoss)
//	{
//		case ACLOSS_LAST_STATE:
//			SetupData->NCT6791D_AC_PWR_LOSS = 2;
//			break;
//		case ACLOSS_ALWAYS_ON:
//			SetupData->NCT6791D_AC_PWR_LOSS = 1;
//			break;
//		case ACLOSS_ALWAYS_OFF: default:
//			SetupData->NCT6791D_AC_PWR_LOSS = 0;
//			break;
//	}
//	#endif
//    	//Patch Chipset to always off
//		SetupData->LastState = 0;
//    } else {
//    	// Should not going to this case
//    	Status = EFI_SUCCESS;
//    }
//
//    return Status;
//}
//
//EFI_STATUS AaeonAcLossCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
//{
//    EFI_STATUS                         Status = EFI_SUCCESS;
//    SETUP_DATA                         *SetupData = NULL;
//    CALLBACK_PARAMETERS                *CallbackParameters = NULL;
//    UINTN                              SetupSize = sizeof(SETUP_DATA);
//    EFI_GUID                           SetupGuid = SETUP_GUID;
//
//    CallbackParameters = GetCallbackParameters();
//    //if(!CallbackParameters || CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGING) return EFI_UNSUPPORTED;
//    if(!CallbackParameters || CallbackParameters->Action != EFI_BROWSER_ACTION_FORM_CLOSE) return EFI_UNSUPPORTED;
//    
//    //Status = pBS->AllocatePool (EfiBootServicesData, SetupSize, &SetupData);
//    //if(EFI_ERROR(Status)) return Status;
//    //Status = HiiLibGetBrowserData (&SetupSize, SetupData, &gSetupGuid, L"Setup");
//    Status = pRS->GetVariable( L"Setup", &gSetupGuid, NULL, &SetupSize, &SetupData );
//    if(EFI_ERROR(Status)) return Status;
//
//    //if (Key == AAEON_ACLOSE_KEY)
//    //{
//    //	Status = AaeonAcLossUpdate(SetupData, SetupData->AaeonRestoreACPowerLossSrc, CallbackParameters->Value->u8);
//    //} else if (Key == AAEON_ACLOSESRC_KEY)
//    //{
//    //	Status = AaeonAcLossUpdate(SetupData, CallbackParameters->Value->u8, SetupData->AaeonRestoreACPowerLoss);
//    //}
//    Status = AaeonAcLossUpdate(SetupData);
//	 
//    //Status = HiiLibSetBrowserData (SetupSize, SetupData, &gSetupGuid, L"Setup");
//    Status = pRS->SetVariable( L"Setup", &gSetupGuid,
//		EFI_VARIABLE_BOOTSERVICE_ACCESS|EFI_VARIABLE_NON_VOLATILE,
//		SetupSize, &SetupData);
//    if(EFI_ERROR(Status)) return Status;	 
//	    
//    //if (SetupData != NULL) pBS->FreePool(SetupData);
//	
//    return Status;
//}
//
//EFI_STATUS AaeonErpCallback(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
//{
//    EFI_STATUS                         Status = EFI_SUCCESS;
//    SETUP_DATA                         *SetupData = NULL;
//    CALLBACK_PARAMETERS                *CallbackParameters = NULL;
//    UINTN                              SetupSize = sizeof(SETUP_DATA);
//
//    CallbackParameters = GetCallbackParameters();
//    //if(!CallbackParameters || CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGING) return EFI_UNSUPPORTED;
//    if(!CallbackParameters || CallbackParameters->Action != EFI_BROWSER_ACTION_FORM_CLOSE) return EFI_UNSUPPORTED;
//    
//    //Status = pBS->AllocatePool (EfiBootServicesData, SetupSize, &SetupData);
//    //if(EFI_ERROR(Status)) return Status;
//    //Status = HiiLibGetBrowserData (&SetupSize, SetupData, &gSetupGuid, L"Setup");
//    Status = pRS->GetVariable( L"Setup", &gSetupGuid, NULL, &SetupSize, &SetupData );
//    if(EFI_ERROR(Status)) return Status;
//    
//    //if (CallbackParameters->Value->u8 == 1)
//    if (SetupData->AaeonErpMode == 1)
//    {
//	#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
//		SetupData->F81866ErpMode = 2;
//	#endif
//	#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
//		SetupData->NCT6791DDeepS5 = 1;
//	#endif
//    } else
//    { 
//	#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
//		SetupData->F81866ErpMode = 0;
//	#endif
//	#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
//		SetupData->NCT6791DDeepS5 = 0;
//	#endif
//    }
//	 
//    //Status = HiiLibSetBrowserData (SetupSize, SetupData, &gSetupGuid, L"Setup");
//    Status = pRS->SetVariable( L"Setup", &gSetupGuid,
//		EFI_VARIABLE_BOOTSERVICE_ACCESS|EFI_VARIABLE_NON_VOLATILE,
//		SetupSize, &SetupData);
//    if(EFI_ERROR(Status)) return Status;	 
//	    
//    //if (SetupData != NULL) pBS->FreePool(SetupData);
//	
//    return Status;
//}