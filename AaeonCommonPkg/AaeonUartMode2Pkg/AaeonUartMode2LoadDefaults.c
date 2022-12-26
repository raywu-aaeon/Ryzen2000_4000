//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <SioSetup.h>
#include <GenericSio.h>
#include <Library/AmiSdlLib.h>
#include <Setup.h>
#include "AaeonUartMode2.h"

extern BOOLEAN gBrowserCallbackEnabled;
extern BOOLEAN gEnableDrvNotification;

//----------------------------------------------------------------------------
//
// Procedure:   UartModeDefaultInit
//
// Description: This function is runtime overriding UART mode default by setup 
//              item "UART Mode Default"
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
	IN CHAR16	*SioNvDataName,
	IN SETUP_DATA	*SetupData
)
{
	EFI_STATUS 			Status = EFI_SUCCESS;
	EFI_GUID			SioSetupGuid = SIO_VARSTORE_GUID;
	UINTN				SioVariableSize = sizeof(SIO_DEV_NV_DATA);
	SIO_DEV_NV_DATA		SioSetupData;
	UINT32				Attribute = 0;
	UINT8				DEFAULT_DEV_MODE = SetupData->AaeonUartMode2Default[UartModeIndex];

    Status = HiiLibGetBrowserData(&SioVariableSize, &SioSetupData, &SioSetupGuid, SioNvDataName);

    TRACE((-1,"UartModeDefaultInit: Get %S %r\n", SioNvDataName, Status));
    if(Status == EFI_SUCCESS)
    {

    	TRACE((-1,"UartModeDefaultInit: %S, DevMode %X\n", SioNvDataName, SioSetupData.DevMode));
    	if(SioSetupData.DevMode != DEFAULT_DEV_MODE)
    	{
    		SioSetupData.DevMode = DEFAULT_DEV_MODE;
    		Status = HiiLibSetBrowserData(SioVariableSize, &SioSetupData, &SioSetupGuid, SioNvDataName);
    		
    		TRACE((-1,"UartModeDefaultInit: Set %S %r\n", SioNvDataName, Status));					
    	}
    }

	return Status;
}
//----------------------------------------------------------------------------
//
// Procedure:   UartModeLoadDefaults
//
// Description: This function is override UART mode default of SIO dynamic  
//              setup when load BIOS setup default
//
// Input:       *defaults - VOID
//              data - To avoid draw MessageBox when data is passed as NULL 
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID UartModeLoadDefaults (VOID *defaults, UINTN data )
{
	EFI_STATUS 					Status = EFI_SUCCESS;	
    EFI_GUID					SetupGuid = SETUP_GUID;
    SETUP_DATA					SetupData;
    UINTN						VariableSize = sizeof(SetupData);
	UINTN						i,j;
	AMI_SDL_SIO_CHIP_INFO 		*sio;
	CHAR16      				SioNvDataName[40];
	UINT32						Attribute = 0;
	UINT8						UartNum, UartModeIndex;
//---------------------		
	gBrowserCallbackEnabled = TRUE;
	gEnableDrvNotification = TRUE;

    AmiSdlInitBoardInfo();
    sio=&gSdlSioData->SioDev[0];    
    		
	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);	

	TRACE((-1,"UartModeLoadDefaults: Get %d SIO Chip.\n", gSdlSioData->SioCount));
    for(j=0; j<gSdlSioData->SioCount; j++)
    {
		AMI_SDL_LOGICAL_DEV_INFO	*ld;
		TRACE((-1,"UartModeLoadDefaults: Get %d LD on SIO Chip %d.\n", sio->LogicalDevCount, gSdlSioData->SioCount));
    //--------------------------------
    	for(i=0; i<sio->LogicalDevCount; i++)
    	{
    		ld=&sio->LogicalDev[i];

			if(ld->Type == dsUART)
			{  
				UartNum = ld->Uid;

				for (UartModeIndex = 0; UartModeIndex < MAX_UARTMODE_NUM; UartModeIndex++)
				{				
					if (SetupData.AaeonUartMode2[UartModeIndex] == Enabled && SetupData.AaeonUartMode2Uid[UartModeIndex] == UartNum)
					{												
			    		Swprintf(SioNvDataName, LD_NV_VAR_NAME_FORMAT, j, i);    		
			    		Status = UartModeDefaultInit(UartNum, UartModeIndex, SioNvDataName, &SetupData);		    		
    				}
    			}		    
							
			}
		}
    	//Advance to the next SIO CHIP in Multiple Sio case.
    	sio=(AMI_SDL_SIO_CHIP_INFO*)(ld+1);
	}

    gBrowserCallbackEnabled = FALSE;
	gEnableDrvNotification = FALSE;	
}
