
#include <Setup.h>
#include <AmiCspLibInc.h>
#include <AmiDxeLib.h>
#include <SioSetup.h>
#include <token.h>
#include "PTN3460Cfg.h"

#include <Protocol\SmbusHc.h>
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_BOOT_SERVICES     *gBS;

EFI_SMBUS_HC_PROTOCOL           *gSmbusProtocol = NULL;

extern PTN3460_CFG_HOOK PTN3460_PANEL1_TSE_BLKCTL_FUNC EndOfPtn3460Panel1TseBlkCtlFunc;
PTN3460_CFG_HOOK *Ptn3460Panel1TseBlkCtl[] = { PTN3460_PANEL1_TSE_BLKCTL_FUNC NULL };
extern PTN3460_CFG_HOOK PTN3460_PANEL2_TSE_BLKCTL_FUNC EndOfPtn3460Panel2TseBlkCtlFunc;
PTN3460_CFG_HOOK *Ptn3460Panel2TseBlkCtl[] = { PTN3460_PANEL2_TSE_BLKCTL_FUNC NULL };

EFI_STATUS AaeonPtn3460CallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
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
		//Dummy callback
		return EFI_SUCCESS;
	}

	return EFI_SUCCESS;
}

VOID UpdatePTN3460PwmBacklight(AAEON_PTN3460_CFG *PanelCfg)
{
	EFI_STATUS                  Status = EFI_SUCCESS;
    EFI_SMBUS_DEVICE_ADDRESS    SlaveAddress;
    UINTN                       Length = 1;
    UINT8                       data = 0, RegVal[2];
    UINT16                      value = 0;
	
    if (gSmbusProtocol == NULL)
    {
        Status = pBS->LocateProtocol (&gEfiSmbusHcProtocolGuid, NULL, (VOID **) &gSmbusProtocol);
        if (EFI_ERROR(Status))
        	return;
    }

    SlaveAddress.SmbusDeviceAddress = PanelCfg->SlaveAddr;
    
    value = ( PanelCfg->BacklightType == 1 ) ? 
   			( PanelCfg->BacklightLv == 10 ? 4095 : 400 * PanelCfg->BacklightLv): 
   			( PanelCfg->BacklightLv == 0 ? 4095 : 400 * (10 - PanelCfg->BacklightLv));
   	data = (value & 0xFF00) >> 8;
   	RegVal[0] = data;
   	data = (value & 0xFF);
   	RegVal[1] = data;

   	// Backlight, 0x90-0x91
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddress, 0x90, EfiSmbusWriteByte, FALSE, &Length, &RegVal[0]);
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddress, 0x91, EfiSmbusWriteByte, FALSE, &Length, &RegVal[1]);
    
    return;
}

void TseBlkCtlPanel1(AAEON_PTN3460_CFG *PanelCfg)
{
    UINTN i = 0;
    
    UpdatePTN3460PwmBacklight(PanelCfg);
    for(i = 0; Ptn3460Panel1TseBlkCtl[i] != NULL; i++)
    {
    	Ptn3460Panel1TseBlkCtl[i](PanelCfg);
    }
    
	return;
}

#if (PTN3460_SUPPORT_NUMBER > 1)
void TseBlkCtlPanel2(AAEON_PTN3460_CFG *PanelCfg)
{
    UINTN i = 0;
    
    UpdatePTN3460PwmBacklight(PanelCfg);
    for(i = 0; Ptn3460Panel2TseBlkCtl[i] != NULL; i++)
    {
    	Ptn3460Panel2TseBlkCtl[i](PanelCfg);
    }
    
	return;
}
#endif

EFI_STATUS AaeonPtn3460BlkLvCallbackEntry(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
	EFI_STATUS                  Status = EFI_SUCCESS;
	CALLBACK_PARAMETERS         *Callback = NULL;
	EFI_GUID		            SetupGuid = SETUP_GUID;
	SETUP_DATA		            SetupData;
	UINTN			            VariableSize = sizeof(SETUP_DATA);
	AAEON_PTN3460_CFG           PanelCfg;
	
	Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
       return EFI_UNSUPPORTED;

    Status = HiiLibGetBrowserData(&VariableSize, &SetupData, &SetupGuid, L"Setup");

    switch(Key)
    {
    	case PTN3460_BLKMODE_KEY:	
    	case PTN3460_BLKLV1_KEY:
    	case PTN3460_BLKTYPE1_KEY:
    	    PanelCfg.SlaveAddr = PTN3460_SLAVE_ADDRESS1;
    	    PanelCfg.Enabled = SetupData.PTN3460En1;
			PanelCfg.BacklightMode = SetupData.PTN3460PanelBacklightMode;
    	    PanelCfg.PanelType = SetupData.PTN3460PanelType1;
    	    PanelCfg.PanelMode = SetupData.PTN3460PanelMode1;
    	    PanelCfg.ColorDepth = SetupData.PTN3460PanelColor1;
    	    PanelCfg.BacklightPwmFreq = SetupData.PTN3460PanelBacklightPwmFreq1;   

    	    if (Key == PTN3460_BLKLV1_KEY)
    	    {
    	    	PanelCfg.BacklightLv = Callback->Value->u8;
    	    	PanelCfg.BacklightType = SetupData.PTN3460PanelBacklightType1;
    	    } 
    	    if (Key == PTN3460_BLKTYPE1_KEY)
    	    {
        	    PanelCfg.BacklightLv = SetupData.PTN3460PanelBacklight1;
        	    PanelCfg.BacklightType = Callback->Value->u8;
    	    }
    	    TseBlkCtlPanel1(&PanelCfg);
   	    break;

#if (PTN3460_SUPPORT_NUMBER == 2)
    	case PTN3460_BLKLV2_KEY:
    	case PTN3460_BLKTYPE2_KEY:
    	    PanelCfg.SlaveAddr = PTN3460_SLAVE_ADDRESS2;
    	    PanelCfg.Enabled = SetupData.PTN3460En2;
    	    PanelCfg.PanelType = SetupData.PTN3460PanelType2;
    	    PanelCfg.PanelMode = SetupData.PTN3460PanelMode2;
    	    PanelCfg.ColorDepth = SetupData.PTN3460PanelColor2;
    	    PanelCfg.BacklightPwmFreq = SetupData.PTN3460PanelBacklightPwmFreq2;

    	    if (Key == PTN3460_BLKLV2_KEY)
    	    {
    	    	PanelCfg.BacklightLv = Callback->Value->u8;
    	    	PanelCfg.BacklightType = SetupData.PTN3460PanelBacklightType2;
    	    } 
    	    if (Key == PTN3460_BLKTYPE2_KEY)
    	    {
        	    PanelCfg.BacklightLv = SetupData.PTN3460PanelBacklight2;
        	    PanelCfg.BacklightType = Callback->Value->u8;
    	    }
    	    TseBlkCtlPanel2(&PanelCfg);
    	break;
#endif
    	default:
    	break;
    }

   	return EFI_SUCCESS;
}
