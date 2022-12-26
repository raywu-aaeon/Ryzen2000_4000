
#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <AmiCspLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.

#include "AaeonUartMode2.h"

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
//----------------------------------------------------------------------------
//
// Procedure:   UartModeDefaultInit
//
// Description: This function is overriding UART mode default by setup item 
//              "UART Mode Default"
//
// Input:       UartNum - The UID of target UART
//              UartModeIndex - The number of UART mode control item
//              *SioNvDataName - The SIO_DEV_NV_DATA name of target UART
//              *SetupData - Pointer of setup variable structure
//
// Output:      EFI_STATUS
//
// Notes:       
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
UartModeDefaultInit ( 
	IN UINT8 	UartNum,
	IN UINT8 	UartModeIndex,
	IN EFI_STRING	SioNvDataName,
	IN SETUP_DATA	*SetupData
)
{
	EFI_STATUS 			Status = EFI_NOT_FOUND;
	EFI_GUID			SioSetupGuid = SIO_VARSTORE_GUID;
	UINTN				SioVariableSize = sizeof(SIO_DEV_NV_DATA);
	SIO_DEV_NV_DATA		SioSetupData;
	UINT32				Attribute = 0;

	Status = pRS->GetVariable( SioNvDataName, &SioSetupGuid, &Attribute, &SioVariableSize, &SioSetupData );
	if(EFI_ERROR(Status)) return Status;

	SioSetupData.DevMode = SetupData->AaeonUartMode2Default[UartModeIndex];	

	Status = pRS->SetVariable(SioNvDataName, &SioSetupGuid, Attribute, SioVariableSize, &SioSetupData);
	if(EFI_ERROR(Status)) return Status;

	return Status;
}
//----------------------------------------------------------------------------
//
// Procedure:   AaeonUartMode2Init
//
// Description: This function is base on UART control items to creating the 
//              UART mode dynamic setup items and initialing UART mode
//
// Input:       VOID
//
// Output:      EFI_STATUS
//
// Notes:       
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
AaeonUartMode2Init (
)
{
	EFI_STATUS 			Status = EFI_NOT_FOUND;
    EFI_GUID			SetupGuid = SETUP_GUID;
    SETUP_DATA			SetupData;
    UINTN				VariableSize = sizeof(SetupData);

	EFI_HANDLE			*Handle = NULL;
	UINTN				Count, i;
    EFI_GUID			gEfiAmiSioProtocolGuid = EFI_AMI_SIO_PROTOCOL_GUID;
	AMI_SIO_PROTOCOL    *AmiSio;
	SIO_DEV2        	*Dev = NULL;
	EFI_STRING			SioNvDataName=NULL;
	UINT8				UartNum, UartLdn, UartModeIndex;
	UINT32				Attribute = 0;  
	

	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);
	if(EFI_ERROR(Status)) return Status;

	Status = pBS->LocateHandleBuffer(ByProtocol, &gEfiAmiSioProtocolGuid, NULL, &Count, &Handle);
	if(EFI_ERROR(Status)) return Status;


	for (i = 0; i < Count; i++)
	{
		Status = pBS->HandleProtocol(Handle[i],&gEfiAmiSioProtocolGuid, &AmiSio);
		if (EFI_ERROR(Status)) continue;

		Dev = (SIO_DEV2*)(UINTN)AmiSio;
		if (Dev->DeviceInfo->Type != dsUART) continue;  // not COM port
		if (Dev->VlData.DevImplemented == 0) continue;
		
		UartNum = Dev->DeviceInfo->Uid;
		UartLdn = Dev->DeviceInfo->Ldn;

		for (UartModeIndex = 0; UartModeIndex < MAX_UARTMODE_NUM; UartModeIndex++)
		{
			if (SetupData.AaeonUartMode2[UartModeIndex] == Enabled && SetupData.AaeonUartMode2Uid[UartModeIndex] == UartNum)
			{
				static CHAR16 AaeonUartMode2Str1[] = L"RS232";
				static CHAR16 AaeonUartMode2Str2[] = L"RS422";
				static CHAR16 AaeonUartMode2Str3[] = L"RS485";
				static CHAR16 AaeonUartMode2Help[] = L"UART RS232, 422, 485 selection";
				
				Dev->DevModeCnt = 3;
				Dev->DevModeStr = MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
				if(Dev->DevModeStr == NULL) {
				        Status = EFI_OUT_OF_RESOURCES;
				        ASSERT_EFI_ERROR(Status);
				        return Status;
				}
				Dev->DevModeStr[0] = &AaeonUartMode2Str1[0];
				Dev->DevModeStr[1] = &AaeonUartMode2Str2[0];
				Dev->DevModeStr[2] = &AaeonUartMode2Str3[0];
				Dev->DevModeStr[3] = &AaeonUartMode2Help[0];
	
				if(SetupData.AaeonCommonFeaturesSyncReady == 0)
				{
					SioNvDataName = GetSioLdVarName(Dev,FALSE);
					Status = UartModeDefaultInit(UartNum, UartModeIndex, SioNvDataName, &SetupData);
					Status = UartModeInit(UartNum, UartLdn, UartModeIndex, SioNvDataName, &SetupData);
				}
			}
		}


	}

	pBS->FreePool(Handle);

	Status = pRS->SetVariable( L"Setup", &SetupGuid, Attribute, VariableSize, &SetupData);

	return Status;
}
