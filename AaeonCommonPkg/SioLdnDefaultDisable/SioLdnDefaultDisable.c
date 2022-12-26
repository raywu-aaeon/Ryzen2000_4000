//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Uefi.h>
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Token.h>
#include <Setup.h>
#include <SioSetup.h>
#include <SioLdnDefaultDisable.h>
#include "AaeonCommonPkg\AaeonSetup\AaeonSetup.h"
 
AAEON_LDN_Default LdnDefault[]=
{
	SIO_DEFAULT_OVERRIDE_TABLE_LIST
};
#if (SIO_SETUP_USE_APTIO_4_STYLE == 0)
//**********************************************************************
// SioLdnDefaultDisable
//**********************************************************************
//Override SIO Ldn Default Setting.
//For A5 Style , SIO Ldn Default is enabled
//We can override it as default is disabled
//for some specific customer request and don't  
//let us to modify token xxxx_Present 
//
//
VOID SioLdnDefaultDisable()
{
    EFI_STATUS Status;
    AAEON_SIOD4PATCH_DATA SioD4Patch;
	UINTN		VariableSize = sizeof(AAEON_SIOD4PATCH_DATA);
	UINT32      	Attributes;
	EFI_GUID 	AaeonSetupGuid = AAEON_VAR_GUID;
	EFI_GUID	SioSetupGuid = SIO_VARSTORE_GUID;
	UINTN		SioVariableSize = sizeof(SIO_DEV_NV_DATA);
	SIO_DEV_NV_DATA	SioSetupData;
	EFI_STRING	SioLdName; 
	UINT8 		i=0;
    
	Status = pRS->GetVariable(L"DynSioD4Patch", &AaeonSetupGuid, &Attributes, &VariableSize, &SioD4Patch);
	
	if (Status == EFI_NOT_FOUND) //first boot after BIOS flash
	{
	    TRACE((-1, "[PatchDynSioDefaults] May first boot after BIOS flash\n"));

		SioD4Patch.PatchFlag = 1;
		pRS->SetVariable(L"DynSioD4Patch", &AaeonSetupGuid, (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS), VariableSize, &SioD4Patch);
		
		while (LdnDefault[i].Enable != 0xFF)
		{
			SioLdName = LdnDefault[i].LdnName;
			Status = pRS->GetVariable(SioLdName, &SioSetupGuid, &Attributes, &SioVariableSize, &SioSetupData);
			if (!EFI_ERROR(Status) || (Status == EFI_NOT_FOUND))
			{
				SioSetupData.DevEnable = LdnDefault[i].Enable;       	
				Status = pRS->SetVariable(SioLdName, &SioSetupGuid, Attributes, SioVariableSize, &SioSetupData);
				TRACE((-1, "[PatchDynSioDefaults] Updating SioLdn(%r)\n", Status));
			}
			i++;
		}		
	}
}
#endif









