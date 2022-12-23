//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************

/** @file RsdpPlus.c
    Entry point for RsdpPlus initialization.

**/
//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Protocol/ManageShadowProtocol.h>

#ifndef CSM_SUPPORT
#define CSM_SUPPORT 0
#endif

#if CSM_SUPPORT
#include <Setup.h>
#include <ImageAuthentication.h>
#endif
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
DATA_BUFF_STRUC gDataInfo = {0,0};

// External Declaration(s)
extern ENABLE_RUNTIME_SHADOW_WRITE_HOOK ENABLE_RUNTIME_SHADOW_WRITE_HOOK_LIST EndOfEnableRuntimeShadowWriteHookLists;

// Function Definition(s)
ENABLE_RUNTIME_SHADOW_WRITE_HOOK* gEnableRuntimeShadowWriteHookList[] = {ENABLE_RUNTIME_SHADOW_WRITE_HOOK_LIST NULL};

//---------------------------------------------------------------------------

/**
    Hook for Enable/Disable runtime shadow ram write.
    @param  Enable      Enable/Disable runtime shadow ram write.

**/
VOID
EFIAPI
EnableRuntimeShadowWriteHook(
    IN BOOLEAN Enable
)
{
    UINTN Index;
    
    for (Index = 0; gEnableRuntimeShadowWriteHookList[Index] != NULL; Index++) 
        gEnableRuntimeShadowWriteHookList[Index](Enable);
}

#if CSM_SUPPORT
/**
    Elink function, Delete RSDP structure data before legacy boot.

**/
VOID
EFIAPI
EraseRsdpInFseg(VOID)
{
    EFI_STATUS  Status;
    EFI_GUID    SetupGuid   = SETUP_GUID;
    UINTN       VariableSize;
    UINT8       CurrentCsmState = 0;
    SETUP_DATA  SetupData;
    UINTN       *Buff = (UINTN*)gDataInfo.BuffAddress;

    //DEBUG((DEBUG_INFO,"RsdpPlusLib: (EraseRsdpInFseg) : EraseRsdpInFseg \n"));
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: (EraseRsdpInFseg) : Buff address is 0x%x \n",Buff));
    if(Buff == NULL)
        return;

    VariableSize = sizeof(UINT8);
    Status = gRT->GetVariable(EFI_SECURE_BOOT_NAME, &gEfiGlobalVariableGuid, NULL, &VariableSize, &CurrentCsmState);
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: (EraseRsdpInFseg) : Get Secure boot Global variable %r, CurrentCsmState [%d] \n",Status, CurrentCsmState));
    
    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);  
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: (EraseRsdpInFseg) : Get Setup Variable %r, CsmLaunchPolicy = %d.\n",Status, SetupData.CsmSupport));
    
    if(!EFI_ERROR(Status) && (SetupData.CsmSupport == 1 && !CurrentCsmState)){
        EnableRuntimeShadowWriteHook(TRUE);
        gBS->SetMem((VOID*)Buff, gDataInfo.UsedLength, 0x0);
        EnableRuntimeShadowWriteHook(FALSE);
        return;
    }
    
    return;
}
#endif
/**
    Elink function for creating RSDP in Shadow Ram when UEFI boot.
    
    @param  ImageHandle     The firmware allocated handle for the EFI image.
    @param  SystemTable     A pointer to the EFI System Table.
    
    @retval EFI_SUCCESS     The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
CreateRsdpInFseg(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    BOOLEAN     ExitToSetupFlag;
    MANAGE_SHADOW_RAM_PROTOCOL  *ManageShadowRamProtocol;
    EFI_GUID    ManageShadowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;
    EFI_GUID    Acpi20TableGuid = ACPI_20_TABLE_GUID;
    EFI_GUID    Acpi11TAbleGuid = ACPI_10_TABLE_GUID;
    RSDT_PTR_20 *RSDP = NULL;
    UINTN       DataSize;
    
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: (CreateRsdpInFseg) : CreateRsdpInFseg \n"));
    Status = EfiGetSystemConfigurationTable(&Acpi20TableGuid, (VOID **) &RSDP);
    
    if (EFI_ERROR(Status))
    {
        Status = EfiGetSystemConfigurationTable(&Acpi11TAbleGuid, (VOID **) &RSDP);
    }
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND; 
    
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: Rsdp Ptr [0x%x] \n",RSDP));
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: Rsdp Sig [%lx] \n",RSDP->Signature));
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: Rsdp XSDT addr [0x%x] \n",RSDP->XsdtAddr));
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: Rsdp RSDT addr [0x%x] \n",RSDP->RsdtAddr));
    
    Status = gBS->LocateProtocol(&ManageShadowRamProtocolGuid, NULL, (VOID**) &ManageShadowRamProtocol);
    ASSERT_EFI_ERROR(Status);
    
    DataSize = sizeof(ExitToSetupFlag);
    Status = gRT->GetVariable(
                 L"Exitflag",
                 &ManageShadowRamProtocolGuid,
                 NULL,
                 &DataSize,
                 &ExitToSetupFlag);
    
    //DEBUG((DEBUG_INFO,"RsdpPlusLib: (CreateRsdpInFseg): Get Variable Exitflag %r.\n",Status));
    if(EFI_ERROR(Status)){
        Status = ManageShadowRamProtocol->HeapToF000((UINT8*)RSDP, 16, (UINTN)sizeof(RSDT_PTR_20), &gDataInfo);
        //DEBUG((DEBUG_INFO,"RsdpPlusLib: (CreateRsdpInFseg): HeapToF000 %r \n",Status));
        return Status; //Preserved F seg too small, if halt here, that's mean preserve space less then 0x90 bytes.
    }

    return EFI_SUCCESS;
}

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
