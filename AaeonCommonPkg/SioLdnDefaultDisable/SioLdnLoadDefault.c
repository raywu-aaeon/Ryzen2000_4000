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

extern BOOLEAN gBrowserCallbackEnabled;
extern AAEON_LDN_Default LdnDefault[];

#if (SIO_SETUP_USE_APTIO_4_STYLE == 0)
VOID LoadDynSioDefaults(VOID *defaults, UINTN data )
{
 EFI_GUID SioSetupGuid = SIO_VARSTORE_GUID;
 UINTN  SioVariableSize = sizeof(SIO_DEV_NV_DATA);
 SIO_DEV_NV_DATA *SioSetupData = NULL;
 EFI_STRING	SioLdName; 
 EFI_STATUS  Status = EFI_SUCCESS;
 UINT32      Attributes;
 UINT8 		i=0;
 BOOLEAN     tmpBrowserCallbackEnabled = gBrowserCallbackEnabled;
 
 Status = pBS->AllocatePool(EfiBootServicesData, SioVariableSize, &SioSetupData);
    if (!EFI_ERROR(Status))
    {
	    while (LdnDefault[i].Enable != 0xFF)
	    {
		    
		   SioLdName = LdnDefault[i].LdnName;
		   Status = pRS->GetVariable(SioLdName, &SioSetupGuid, &Attributes, &SioVariableSize, SioSetupData);
		   if (!EFI_ERROR(Status) || (Status == EFI_NOT_FOUND))
		   {
			   SioSetupData->DevEnable = LdnDefault[i].Enable;
			   Status = pRS->SetVariable(SioLdName, &SioSetupGuid, Attributes, SioVariableSize, SioSetupData);
         
			   // Update Hii data
			   gBrowserCallbackEnabled = TRUE;
			   Status = HiiLibGetBrowserData(&SioVariableSize, SioSetupData, &SioSetupGuid, SioLdName);
			   SioSetupData->DevEnable = LdnDefault[i].Enable;
			   Status = HiiLibSetBrowserData(SioVariableSize, SioSetupData, &SioSetupGuid, SioLdName);
			   gBrowserCallbackEnabled = tmpBrowserCallbackEnabled;
		   }
		   i++;
	    }
    }
    pBS->FreePool(SioSetupData);
}
#endif

