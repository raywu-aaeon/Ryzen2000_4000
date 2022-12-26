#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <setupdata.h>
#include "Token.h"
#include "AMITSEElinks.h"
#include <AutoId.h> 
#include "..\..\AaeonSetup.h"

extern PAGE_LIST           *gPages;
extern UINT8         *gApplicationData;
extern PAGE_ID_LIST  *gPageIdList;

typedef struct _HII_FORM_ADDRESS
{
    EFI_GUID formsetGuid; // Required
    UINT16      formId; // Required
    VOID *      Handle; // Optional
}HII_FORM_ADDRESS;

#define NULL_GUID \
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }


//extern HII_FORM_ADDRESS *RootPageList;
HII_FORM_ADDRESS tRootPageList[] = { AMITSE_SUBPAGE_AS_ROOT_PAGE_LIST { NULL_GUID, 0, NULL}, };


extern BOOLEAN EfiCompareGuid ( IN EFI_GUID *Guid1,  IN EFI_GUID *Guid2  );

BOOLEAN IsAaeonRootPage(UINT16 formId){
    if ( formId == AAEON_MAIN_MAIN || 
          formId == AAEON_ADVANCED_MAIN || 
          formId == AAEON_CHIPSET_MAIN ||
          formId == AAEON_SECURITY_MAIN ||
          formId == AAEON_BOOT_MAIN || 
          formId == AAEON_EXIT_MAIN )
        return TRUE;
    else
        return FALSE;
}

VOID AaeonSetupLibHook()
{
    UINTN RootPageListCount = sizeof(tRootPageList) / sizeof (HII_FORM_ADDRESS);
    UINTN i,j;
    PAGE_INFO *info;
    PAGE_ID_INFO *pageIdInfo;
    
    EFI_STATUS   Status = EFI_SUCCESS;
    EFI_GUID     AaeonSetupGuid = AAEON_VAR_GUID;
    UINTN        VariableSize = sizeof(AAEON_SETUP_DATA);
    UINT32       Attributes;
    AAEON_SETUP_DATA   dAaeonSetup;
    
    Status = gRT->GetVariable( L"AaeonSetup", &AaeonSetupGuid, &Attributes,              
                               &VariableSize, &dAaeonSetup );
   
    // Support to Handle some child pages as root pages.
    for(j=0; j<RootPageListCount;j++)
    {
        if ( !IsAaeonRootPage( tRootPageList[j].formId) )
            continue;
        for ( i = 0; i < (UINTN)gPages->PageCount; i++ ) // EIP110194
        {
            info = (PAGE_INFO*)((UINTN)gApplicationData + gPages->PageList[i]);

            // To Make Page as root
            if( info->PageFormID == tRootPageList[j].formId)
            {
                // If Handle is not null compare. If it null Ignore
                if(tRootPageList[j].Handle != NULL)
                {
                    if(info->PageHandle != tRootPageList[j].Handle)
                        continue;
                }
                pageIdInfo = (PAGE_ID_INFO *)(((UINT8 *) gPageIdList) + gPageIdList->PageIdList[info->PageIdIndex]);

                if( EfiCompareGuid(&pageIdInfo->PageGuid,&tRootPageList[j].formsetGuid) )//Compare Guid
                    info->PageParentID =0;
            }
        }
    }
}

