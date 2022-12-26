
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.

#include <Protocol/AmiSio.h>
#include <AmiGenericSio.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
//extern VOID RayDebug80(UINT8 Time, UINT8 Code);
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
AaeonUartModeInit (
)
{
	EFI_STATUS Status = EFI_SUCCESS;
    	EFI_GUID	SetupGuid = SETUP_GUID;
    	SETUP_DATA	SetupData;
    	UINTN		VariableSize = sizeof(SetupData);
    	UINT32		Attribute = 0;

	EFI_HANDLE	*Handle = NULL;
	UINTN		Count, i;
    	EFI_GUID	gEfiAmiSioProtocolGuid = EFI_AMI_SIO_PROTOCOL_GUID;
	AMI_SIO_PROTOCOL    *AmiSio;
	SIO_DEV2            *Dev = NULL;

	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );
	if(EFI_ERROR(Status)) return Status;

	Status = pBS->LocateHandleBuffer(ByProtocol, &gEfiAmiSioProtocolGuid, NULL, &Count, &Handle);
	if(EFI_ERROR(Status)) return Status;

	{
		for (i = 0; i < Count; i++)
		{
			Status = pBS->HandleProtocol(Handle[i],&gEfiAmiSioProtocolGuid, &AmiSio);
			if (EFI_ERROR(Status)) continue;

			Dev = (SIO_DEV2*)(UINTN)AmiSio;
			if (Dev->DeviceInfo->Type != dsUART) continue;  // not COM port
			if (Dev->VlData.DevImplemented == 0)
			{
				continue;
			}

			{
				static CHAR16 AaeonUartModeStr1[] = L"RS232";
				static CHAR16 AaeonUartModeStr2[] = L"RS422";
				static CHAR16 AaeonUartModeStr3[] = L"RS485";
				static CHAR16 AaeonUartModeHelp[] = L"UART RS232, 422, 485 selection";
				
				Dev->DevModeCnt = 3;
				Dev->DevModeStr = MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
				if(Dev->DevModeStr == NULL) {
				        Status = EFI_OUT_OF_RESOURCES;
				        ASSERT_EFI_ERROR(Status);
				        return Status;
				}
				Dev->DevModeStr[0] = &AaeonUartModeStr1[0];
				Dev->DevModeStr[1] = &AaeonUartModeStr2[0];
				Dev->DevModeStr[2] = &AaeonUartModeStr3[0];
				Dev->DevModeStr[3] = &AaeonUartModeHelp[0];
			}
		}
	}
	pBS->FreePool(Handle);

	// RunOnce supported for setup variable API
	{
		if(SetupData.AaeonCommonFeaturesSyncReady == 0)
		{
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
				//
				//		case 1: //RS422
				//			break;
				//
				//		case 2: //RS485
				//			break;
				//
				//		default:
				//			break;
				//
				//	}
				//}
			}

			Status = pRS->SetVariable( L"Setup", &SetupGuid,
				Attribute,
				VariableSize, &SetupData);
		}
	}

	return Status;
}
