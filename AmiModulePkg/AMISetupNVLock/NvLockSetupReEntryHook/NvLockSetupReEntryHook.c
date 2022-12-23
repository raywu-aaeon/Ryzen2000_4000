//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2021, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file NVLockSetupReentryHook.c
    Implements the password validation and Unlocking the NVRAM When system 
    exiting from boot option to setup
    
**/

#include <PwdLib.h>
#include <AMISetupNVLock/AMISetupNVLock.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/EsaTseInterfaces.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

extern UINTN       gSetupNVLockPwdSize;
extern CHAR16*     gSetupNVLockPwd;
extern EFI_STATUS  InitEsaTseInterfaces (void);

/**
    This function will unlock protected NVRAM variable through password 
    when exiting from boot option to setup.
    
    This function gets called while re-entering the setup from boot option.
    It will prompt the password window, if system password ADMIN/USER installed. 
    If valid password entered, system will boot to setup and protected 
    NVRAM variable will be unlocked. If invalid password provided 3 times, 
    system will become stable, need to restart the system. If ADMIN password only 
    installed, In setup re-entry it will accept empty password also, system 
    will boot to setup in USER mode and protected NVRAM variable will be 
    unlocked. 
    
    @param  VOID
    
    @retval VOID
**/
VOID NvLockSetupReEntry()
{
    EFI_STATUS Status;
    EFI_GUID SetupPwdGuid = SETUPPASSWD_GUID;
    SETUP_DATA NvLockSetupVariable = {0};
    UINTN VarSize = sizeof(NvLockSetupVariable);
    UINT8    NvLockSetupControl = 0;
    UINT32 PasswordInstalled = 0;

    // Checks the AmiSetupNvlock Protection support
    Status =  pRS->GetVariable(L"Setup", 
                         &gAmiSetupVariableGuid, 
                         NULL, 
                         &VarSize, 
                         &NvLockSetupVariable );
    if(!EFI_ERROR(Status)){
        NvLockSetupControl = NvLockSetupVariable.NvLockSetupControl;
    }
    if(NvLockSetupControl == 0)//If Runtime protection disabled, Return from here.
        return;
    PasswordInstalled = PasswordCheckInstalled();//Checks the Password installed or not
    DEBUG_SETUPNVLOCK((DEBUG_INFO, "\nAmiSetupNvLock: PasswordInstalled : %d\n",PasswordInstalled));
    if(PasswordInstalled == AMI_PASSWORD_NONE)//If Password not installed, Unlocking the NVRAM
        return;
    else {
        UINT32  PasswordType = 0;
        UINTN NoOfRetries = 3;
        AMI_POST_MANAGER_PROTOCOL *AmiPostMgr;
        TSE_POST_STATUS PostStatus;
        
        gSetupNVLockPwdSize = TSE_PASSWORD_LENGTH;
        gSetupNVLockPwd = AllocateZeroPool((gSetupNVLockPwdSize + 1)*sizeof(CHAR16));
        
        Status = InitEsaTseInterfaces ();
        DEBUG_SETUPNVLOCK((DEBUG_INFO, "\nAmiSetupNvLock: InitEsaTseInterfaces Status: %r\n",Status));
        if (!EFI_ERROR (Status)){
            Status = gBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, (VOID**)&AmiPostMgr);
            if (EFI_ERROR(Status)) 
                return;
            PostStatus = AmiPostMgr->GetPostStatus();
            if (PostStatus >= TSE_POST_STATUS_PROCEED_TO_BOOT){
               PasswordType = CheckSystemPassword( AMI_PASSWORD_USER, &NoOfRetries, NULL); //To draw the password window
               gEsaInterfaceForTSE->EsaTseSetGetVariables (EsaPasswordType, 1, 0, (UINTN *)&PasswordType);
            }
            else
                PasswordType = gEsaInterfaceForTSE->CheckSystemPassword (AMI_PASSWORD_USER, &NoOfRetries, NULL);
            
        }
        else{
            PasswordType = CheckSystemPassword( AMI_PASSWORD_USER, &NoOfRetries, NULL);
        }
        if(AMI_PASSWORD_NONE == PasswordType){ // Invalid password 
            UINTN Index = 0;
            EFI_INPUT_KEY Key;
            while(1){
                //Ctl-Alt-Del is not recognized by core unless a
                //ReadKeyStroke is issued
                gBS->WaitForEvent( 1, pST->ConIn->WaitForKey, &Index );
                gST->ConIn->ReadKeyStroke( pST->ConIn, &Key );
            }
        }
        else if((AMI_PASSWORD_USER == PasswordType) && (*(gSetupNVLockPwd) == L'\0')){ // Empty password Check
            EFI_GUID TseSetupGuid = AMITSESETUP_GUID;
            AMITSESETUP *mSysConf = NULL;
            UINT16 OutBuffer[sizeof(AMITSESETUP)];
            UINT32 SetupDataAttributes = 0;
            UINTN SetupDataSize = sizeof(AMITSESETUP);
            Status = gRT->GetVariable(TSE_SETUP_VAR_NAME, 
                                        &TseSetupGuid, 
                                        &SetupDataAttributes, 
                                        &SetupDataSize, 
                                        &OutBuffer );
            if(!EFI_ERROR(Status)){
                mSysConf = (AMITSESETUP *)OutBuffer;
                Status = gRT->SetVariable(SETUPPASS_VAR_NAME_ANY, 
                                           &SetupPwdGuid,
                                           EFI_VARIABLE_BOOTSERVICE_ACCESS , 
                                           sizeof(mSysConf->AdminPassword), 
                                           mSysConf->AdminPassword);
        		DEBUG_SETUPNVLOCK((DEBUG_INFO, "\nAmiSetupNvLock: SETUPPASS_VAR_NAME_ANY SetVariable Status: %r",Status));
            }
        }
        else {
            Status = gRT->SetVariable(SETUPPASS_VAR_NAME_ANY, 
                                                    &SetupPwdGuid,
                                                    EFI_VARIABLE_BOOTSERVICE_ACCESS , 
                                                    sizeof(gSetupNVLockPwd), 
                                                    gSetupNVLockPwd );
         DEBUG_SETUPNVLOCK((DEBUG_INFO, "\nAmiSetupNvLock: SETUPPASS_VAR_NAME_ANY SetVariable Status: %r",Status));
        }
        if(gSetupNVLockPwd){
            MemSet(gSetupNVLockPwd,TSE_PASSWORD_LENGTH,0);
            FreePool(gSetupNVLockPwd);
        }
            
    }
    return;
    
}
