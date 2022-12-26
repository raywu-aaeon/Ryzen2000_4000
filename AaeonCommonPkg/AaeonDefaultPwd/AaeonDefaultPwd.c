//;******************************************************************************
//;* Copyright (c) 2018, Aaeon Corporation. All Rights Reserved.
//;*
//;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
//;* transmit, broadcast, present, recite, release, license or otherwise exploit
//;* any part of this publication in any form, by any means, without the prior
//;* written permission of Aaeon Corporation.
//;*
//;******************************************************************************
//; ModuleName:
//;
//;   AaeonDefaultPwd.c
//;
//;------------------------------------------------------------------------------
//;
//; Abstract:
//;
//;   This module overrides Admin/User password at first boot only.
//;
//;   STR_AAEON_DEFAULT_ADMIN_PWD_VALUE in Build/AutoGenAaeonDefaultPwd.uni :
//;       "" - Don't set Admin password
//;       "123" - Set Admin password as 123
//;   STR_AAEON_DEFAULT_USER_PWD_VALUE in Build/AutoGenAaeonDefaultPwd.uni :
//;       "" - Don't set User password
//;       "123" - Set User password as 123
//;

#include "token.h"
#include <AmiLib.h>
#include <EFI.h>
#include <AMIVfr.h>
#include "commonoem.h"
#include "variable.h"
#include "Setup.h"
#include <Library/MemoryAllocationLib.h>
#include <AmiDxeLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/HiiLib.h>
#include <Library/DebugLib.h>
#include <AMITSEElinks.h>
#include <SetupStrDefs.h>


extern EFI_RUNTIME_SERVICES *gRT;

/*VOID RayDebug80(UINT8 Time, UINT8 Code){
 UINTN i;
 
 i = 0x0FFFF | (Time << 16);
 while(i != 0){
  IoWrite8(0x80, Code);
  i--;
 }
}*/


VOID SetAaeonDefaultPWD(
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class
)
{
    EFI_STATUS   Status;
    CHAR16       *EncPass = NULL;  
    EFI_GUID     AmiTseSetupGuid = AMITSESETUP_GUID;
    AMITSESETUP  AmiTseSetup;
    UINTN        Size = 0;
    UINT16       Buffer = 0;
    UINTN        PasswordLength = SETUP_PASSWORD_LENGTH;
    CHAR16       *PasswordEntered = NULL;
    UINT32       Attributes;
    UINT32       SetupAttributes;
    UINTN        SetupDataSize = sizeof(SETUP_DATA);
    UINT8        i = 0;
    SETUP_DATA   SetupData;
    EFI_GUID     SetupGuid = SETUP_GUID;
    
    TRACE((-1,"AAEON DEFAULT PASSWORD START \n"));
    
    if (Class != SECURITY_FORM_SET_CLASS) 
        return;
    
    Status = gRT->GetVariable(L"Setup", &SetupGuid, &SetupAttributes, &SetupDataSize, &SetupData);    
    if((SetupData.AaeonSetDefaultAdminPwd == 0 && SetupData.AaeonSetDefaultUserPwd == 0) 
        || (SetupData.AaeonSetDefaultPWDFirstBoot == 1))
        return;
    
    Size = sizeof(AMITSESETUP);
    Status = gRT->GetVariable(L"AMITSESetup", &AmiTseSetupGuid, &Attributes, &Size, &AmiTseSetup);
    
    if (EFI_ERROR(Status))
    {
        MemSet(&AmiTseSetup, Size, 0);
        AmiTseSetup.AMISilentBoot = DEFAULT_QUIET_BOOT;
    }
    
    EncPass = AllocatePool((PasswordLength + 1)*sizeof(CHAR16));
    PasswordEntered = AllocatePool((PasswordLength + 1)*sizeof(CHAR16));
    
    //
    // Set admin password if STR_AAEON_DEFAULT_ADMIN_PWD_VALUE is not empty ("")
    //
    // Clear EncPass buffer
    MemSet(EncPass, (PasswordLength + 1)*sizeof(CHAR16), 0);
    // Clear PasswordEntered buffer
    MemSet( PasswordEntered, (PasswordLength + 1)*sizeof(CHAR16), 0 );
    if(SetupData.AaeonSetDefaultAdminPwd == 1)
    {
        //Get String
        PasswordEntered = HiiGetString (
                            HiiHandle,
                            STRING_TOKEN(STR_AAEON_DEFAULT_ADMIN_PWD_VALUE),
                            NULL
                          );
        
        TRACE((-1,"AAEON DEFAULT PASSWORD (STRING INIT): %S \n",PasswordEntered));

        if (StrLen(PasswordEntered) != 0) {
            i = 0;
            while(PasswordEntered[i]!=0)
            {
                EncPass[i]=PasswordEntered[i];
                i++;
            }    
            PasswordEncode( EncPass, (PasswordLength)*sizeof(CHAR16));
            TRACE((-1,"AAEON DEFAULT PASSWORD Encode (STRING INIT): %X \n",EncPass));
            // Set Admin password
            MemCpy(&AmiTseSetup.AdminPassword, EncPass,(PasswordLength)*sizeof(CHAR16));
        }
    }

    //
    // Set user password if STR_AAEON_DEFAULT_USER_PWD_VALUE is not empty ("")
    //
    // Clear EncPass buffer
    MemSet(EncPass, (PasswordLength + 1)*sizeof(CHAR16), 0);
    // Clear PasswordEntered buffer
    MemSet( PasswordEntered, (PasswordLength + 1)*sizeof(CHAR16), 0 );
    if(SetupData.AaeonSetDefaultUserPwd == 1)
    {
        PasswordEntered = HiiGetString (
                            HiiHandle,
                            STRING_TOKEN(STR_AAEON_DEFAULT_USER_PWD_VALUE),
                            NULL
                          );
        if (StrLen(PasswordEntered) != 0) {
            i = 0;
            while(PasswordEntered[i]!=0)
            {
                EncPass[i]=PasswordEntered[i];
                i++;
            }
            // Set user password
            PasswordEncode( EncPass, PasswordLength*sizeof(CHAR16));
            MemCpy(&AmiTseSetup.UserPassword, EncPass, PasswordLength*sizeof(CHAR16));
        }
    }

    SetupData.AaeonSetDefaultPWDFirstBoot = 1;

    Status = gRT->SetVariable(L"Setup", 
            &SetupGuid, 
            SetupAttributes,    
            SetupDataSize, 
            &SetupData);    

    Status = gRT->SetVariable(L"AMITSESetup", 
            &AmiTseSetupGuid, 
            Attributes,    
            Size, 
            &AmiTseSetup);
}
