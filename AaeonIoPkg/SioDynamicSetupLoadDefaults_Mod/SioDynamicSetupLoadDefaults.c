//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file SioDynamicSetupLoadDefaults.c
  Sio Dynamic Setup Load Defaults.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <SioSetup.h>
#include <GenericSio.h>
#include <Library/AmiSdlLib.h>
#include <Library/PrintLib.h>

#define DEFAULT_DEV_ENABLE 1
#define DEFAULT_DEV_PRS_ID 0
#define DEFAULT_DEV_MODE 0

extern BOOLEAN gBrowserCallbackEnabled;
extern BOOLEAN gEnableDrvNotification;

VOID SioLoadSetupDefaults (VOID *defaults, UINTN data )
{
	EFI_STATUS              Status;
	AMI_SDL_SIO_CHIP_INFO 	*sio;
	UINTN                   i, j;
	EFI_GUID                ssg = SIO_VARSTORE_GUID;
	UINTN                   vs;
	CHAR16                  vname[40];
	SIO_DEV_NV_DATA         DevNvData;
	BOOLEAN                 NoDefault = FALSE;

	gBrowserCallbackEnabled = TRUE;
	gEnableDrvNotification = TRUE;
	
    AmiSdlInitBoardInfo();
	vs=sizeof(SIO_DEV_NV_DATA);
	sio=&gSdlSioData->SioDev[0];
	
	TRACE((-1,"SioDynamicSetup: Get %d SIO Chip.\n", gSdlSioData->SioCount));
    for(j=0; j<gSdlSioData->SioCount; j++)
    {
		AMI_SDL_LOGICAL_DEV_INFO	*ld;
		TRACE((-1,"SioDynamicSetup: Get %d LD on SIO Chip %d.\n", sio->LogicalDevCount, gSdlSioData->SioCount));
    	for(i=0; i<sio->LogicalDevCount; i++)
    	{
    		ld=&sio->LogicalDev[i];
    		//check if Ld implemented on thr board and Has Setup screen...
        	if(ld->Implemented && ld->HasSetup)
        	{
        		UnicodeSPrint(vname, 40*sizeof(CHAR16), L"NV_SIO%X_LD%X", j, i);
        		Status = HiiLibGetBrowserData(&vs, &DevNvData, &ssg, vname);
        		TRACE((-1,"SioDynamicSetup: Get %S %r\n", vname, Status));
        		if(Status == EFI_SUCCESS){
        			TRACE((-1,"SioDynamicSetup: %S, DevEnable %X, DevPrsId %X, DevMode %X\n", vname, DevNvData.DevEnable, DevNvData.DevPrsId, DevNvData.DevMode));
        			if(DevNvData.DevEnable != DEFAULT_DEV_ENABLE){
        				DevNvData.DevEnable = DEFAULT_DEV_ENABLE;
        				NoDefault = TRUE;
        			}
        			if(DevNvData.DevPrsId != DEFAULT_DEV_PRS_ID){
        				DevNvData.DevPrsId = DEFAULT_DEV_PRS_ID;
        				NoDefault = TRUE;
        			}
        			if(DevNvData.DevMode != DEFAULT_DEV_MODE){
        				DevNvData.DevMode = DEFAULT_DEV_MODE;
        				NoDefault = TRUE;
        			}
        			if(NoDefault){
        				Status = HiiLibSetBrowserData(vs, &DevNvData, &ssg, vname);
        				NoDefault = FALSE;
        				TRACE((-1,"SioDynamicSetup: Set %S %r\n", vname, Status));					
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

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
