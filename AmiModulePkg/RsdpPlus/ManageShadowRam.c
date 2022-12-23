//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************

/** @file ManageShadowRam.c 
    Installing protocol functions for other module used.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Protocol/ManageShadowProtocol.h>
#include "ShadowRamProtocol.h"

#ifndef CSM_SUPPORT
#define CSM_SUPPORT 0
#endif

#if CSM_SUPPORT
#include <Setup.h>
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
EFI_STATUS EFIAPI HeapToE000(IN UINT8 *Data, UINT32 Align, IN UINTN Length, IN OUT DATA_BUFF_STRUC *Data2 OPTIONAL);
EFI_STATUS EFIAPI HeapToF000(IN UINT8 *Data, UINT32 Align, IN UINTN Length, IN OUT DATA_BUFF_STRUC *Data2 OPTIONAL);
VOID EFIAPI UpdateShadowBeforEfiBoot(VOID);
VOID EFIAPI EraseShadowAfterEfiBoot(VOID);
//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
EFI_HANDLE  gManageShadowRamHandle = NULL;
UINT8   *gE000HeapPtr = NULL;
UINT8   *gF000HeapPtr = NULL;
UINT8   *gESegStore = NULL;
UINT8   *gFSegStore = NULL;
UINT8   gEsegUserCount = 0;
UINT8   gFsegUserCount = 0;
UINT32  gE000BuffLength = 0;
UINT32  gF000BuffLength = 0;

#if CSM_SUPPORT
SETUP_DATA  gSetupData;
VOID        *gLegacyRegionAddress = NULL;
#endif

// Protocol Definition(s)
SHADOW_RAM_PROTOCOL gShadowRamProtocol = 
{
    UpdateShadowBeforEfiBoot,
    EraseShadowAfterEfiBoot
};

MANAGE_SHADOW_RAM_PROTOCOL gManageShadowRamProtocol =
{
    HeapToE000,
    HeapToF000
};

// External Declaration(s)
extern UPDATE_E000_SHADOW_RAM_HOOK UPDATE_E000_SHADOW_RAM_HOOK_LIST EndOfUpdateE000ShadowRamHookList;
extern UPDATE_F000_SHADOW_RAM_HOOK UPDATE_F000_SHADOW_RAM_HOOK_LIST EndOfUpdateF000ShadowRamHookList;
extern CSM_ON_LINK_HOOK CSM_ON_LINK_HOOK_LIST EndOfCsmOnLinkHookList;
extern ENABLE_RUNTIME_SHADOW_WRITE_HOOK ENABLE_RUNTIME_SHADOW_WRITE_HOOK_LIST gEndOfEnableRuntimeShadowWriteHookList;

// Function Definition(s)
UPDATE_E000_SHADOW_RAM_HOOK* gUpdateE000ShadowRamHookList[] = {UPDATE_E000_SHADOW_RAM_HOOK_LIST NULL};
UPDATE_F000_SHADOW_RAM_HOOK* gUpdateF000ShadowRamHookList[] = {UPDATE_F000_SHADOW_RAM_HOOK_LIST NULL};
CSM_ON_LINK_HOOK* gCsmOnLinkHookList[] = {CSM_ON_LINK_HOOK_LIST NULL};
ENABLE_RUNTIME_SHADOW_WRITE_HOOK* gEnableRuntimeShadowWriteHookList[] = {ENABLE_RUNTIME_SHADOW_WRITE_HOOK_LIST NULL};

//---------------------------------------------------------------------------    

/**
    Hook for update Eseg.
    @param  ShadowRam      A pointer to shadow ram area.
    @param  UsageLength     Used data size.

**/
VOID
EFIAPI
OemUpdateE000ShadowRamHook(
    IN UINT32*  ShadowRam,
    IN UINTN    UsageLength
)
{
    UINTN Index;
    
    for (Index = 0; gUpdateE000ShadowRamHookList[Index] != NULL; Index++) 
        gUpdateE000ShadowRamHookList[Index](ShadowRam, UsageLength);
}

/**
    Hook for update Fseg.
	@param  ShadowRam		A pointer to shadow ram area.
	@param  UsageLength		Used data size.

**/
VOID
EFIAPI
OemUpdateF000ShadowRamHook(
    IN UINT32*	ShadowRam,
	IN UINTN	UsageLength
)
{
    UINTN Index;
    
    for (Index = 0; gUpdateF000ShadowRamHookList[Index] != NULL; Index++) 
        gUpdateF000ShadowRamHookList[Index](ShadowRam, UsageLength);
}

/**
    Hook for external CSM On feature.
	@retval Status	Depending on the link function. 

**/
EFI_STATUS
ExecuteCsmOnLinkHook(VOID)
{
    EFI_STATUS	Status;
    UINTN Index;
    
    for (Index = 0; gCsmOnLinkHookList[Index] != NULL; Index++) 
        Status = gCsmOnLinkHookList[Index]();

    return Status;
}

/**
    Hook for Enable/Disable runtime shadow ram write.
    @param  Enable      Enable/Disable runtime shadow ram write.

**/
VOID
EnableRuntimeShadowWriteHook(
    IN BOOLEAN Enable
)
{
    UINTN Index;
    
    for (Index = 0; gEnableRuntimeShadowWriteHookList[Index] != NULL; Index++) 
        gEnableRuntimeShadowWriteHookList[Index](Enable);
}

/**
    This is "BeforeEfiBootLaunchHook" elink function.
	It will store original data of Shadow ram and then copy shadow buff's data to shadow ram. 

**/
VOID
EFIAPI
UpdateShadowBeforEfiBoot(VOID)
{
    EFI_STATUS	Status;
    UINT32      E000Offset = 0xE0000;
    UINT32      F000Offset = 0xF0000;

    DEBUG((DEBUG_INFO,"RsdpPlus: Entry Update Shadow Ram!!!\n"));	
    DEBUG((DEBUG_INFO,"RsdpPlus: (UpdateShadowBeforEfiBoot): gE000BuffLength [0x%x] \n", gE000BuffLength));
    DEBUG((DEBUG_INFO,"RsdpPlus: (UpdateShadowBeforEfiBoot): gF000BuffLength [0x%x] \n", gF000BuffLength));

    if(gE000BuffLength == 0 && gF000BuffLength == 0) return;

    //unlock shadow ram
    EnableRuntimeShadowWriteHook(TRUE);

    if(gE000BuffLength != 0){
        Status = gBS->AllocatePool(
                    EfiBootServicesData,
                    gE000BuffLength,
                    (VOID**) &gESegStore
                    );
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))
            return;

        gBS->CopyMem(gESegStore, (UINT32*)E000Offset, (UINTN)gE000BuffLength);
        gBS->SetMem((VOID*)E000Offset, gE000BuffLength, 0);
        gBS->CopyMem((UINT32*)E000Offset, gE000HeapPtr, (UINTN)gE000BuffLength);
        DEBUG((DEBUG_INFO,"RsdpPlus: E000 Info : Data length %d bytes, There are %d data in Shadow Ram!!!\n", gE000BuffLength, gEsegUserCount));
        OemUpdateE000ShadowRamHook((UINT32*)E000Offset, (UINTN)gE000BuffLength);
    }

    if(gF000BuffLength != 0){
        Status = gBS->AllocatePool(
                    EfiBootServicesData,
                    gF000BuffLength,
                    (VOID**) &gFSegStore
                    );
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))
            return;

        gBS->CopyMem(gFSegStore, (UINT32*)F000Offset, (UINTN)gF000BuffLength);
        gBS->SetMem((VOID*)F000Offset, gF000BuffLength, 0);
        gBS->CopyMem((UINT32*)F000Offset, gF000HeapPtr, (UINTN)gF000BuffLength);
        DEBUG((DEBUG_INFO,"RsdpPlus: F000 Info : Data length %d bytes, There are %d data in Shadow Ram!!!\n", gF000BuffLength, gFsegUserCount));
        OemUpdateF000ShadowRamHook((UINT32*)F000Offset, (UINTN)gF000BuffLength);
    }

    //Clear Warm Reset Flash in 0FFFF0H (BYTE)
    gBS->SetMem((VOID*)0xFFFF0, 0x1, 0);	

    //Lock shadow ram
    EnableRuntimeShadowWriteHook(FALSE);

    return;
}

/**
    This is "AfterEfiBootLaunchHook" elink function.
    It will restore original data to Shadow ram.

**/
VOID
EFIAPI
EraseShadowAfterEfiBoot(VOID)
{
    UINT32      E000Offset = 0xE0000;
    UINT32      F000Offset = 0xF0000;
    BOOLEAN     ExitToSetup = TRUE;	
    EFI_STATUS  Status;
    EFI_GUID    ManageShadowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;

    DEBUG((DEBUG_INFO,"RsdpPlus: Entry Update Shadow Ram!!!\n"));

#if CSM_SUPPORT
    if(gSetupData.CsmSupport == 1){

        if(gLegacyRegionAddress == NULL) return;

        Status = gRT->SetVariable(
                        L"Exitflag",
                        &ManageShadowRamProtocolGuid,
                        EFI_VARIABLE_BOOTSERVICE_ACCESS \
                        |EFI_VARIABLE_RUNTIME_ACCESS,
                        sizeof(ExitToSetup),
                        &ExitToSetup);
        DEBUG((DEBUG_INFO,"RsdpPlus: (CsmOn): Set ExitFlag variable %r \n", Status));
        ASSERT_EFI_ERROR (Status);

        return;
    }
#endif

    DEBUG((DEBUG_INFO,"RsdpPlus: (UpdateShadowBeforEfiBoot): gE000BuffLength [0x%x] \n", gE000BuffLength));
    DEBUG((DEBUG_INFO,"RsdpPlus: (UpdateShadowBeforEfiBoot): gF000BuffLength [0x%x] \n", gF000BuffLength));

    if(gE000BuffLength == 0 && gF000BuffLength == 0) return;
    
    DEBUG((DEBUG_INFO,"RsdpPlus: Store Shadow Ram to default!!!\n"));	
    
    EnableRuntimeShadowWriteHook(TRUE);

    if(gE000BuffLength != 0){
        gBS->CopyMem((UINT32*)E000Offset, gESegStore, gE000BuffLength);
        gBS->FreePool(gESegStore);
    }

    if(gF000BuffLength != 0){
        gBS->CopyMem((UINT32*)F000Offset, gFSegStore, gF000BuffLength);
        Status = gBS->FreePool(gFSegStore);
        ASSERT_EFI_ERROR (Status);
    }

    EnableRuntimeShadowWriteHook(FALSE);

    Status = gRT->SetVariable(
                    L"Exitflag",
                    &ManageShadowRamProtocolGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS \
                    |EFI_VARIABLE_RUNTIME_ACCESS,
                    sizeof(ExitToSetup),
                    &ExitToSetup);
    DEBUG((DEBUG_INFO,"RsdpPlus: Set ExitFlag variable %r \n", Status));
    ASSERT_EFI_ERROR (Status);

    return;
}

/**
    This is protocol function.
    According to input data and copy data to E-seg temporary buffer.
    
    @param[in]  *Data      Pointer to context to save
    @param[in]  Align       Base alignment.
    @param[in]  Length      the length of the restored confidential information
    @param      *Data2     Pointer to stored data
    
    @retval EFI_INVALID_PARAMETER   error for input data is NULL and length is 0
    @retval EFI_BUFFER_TOO_SMALL    error for Input data length is greater than gEsegBufferSize.
    @retval EFI_SUCCESS             Copy Data successfully.

**/
EFI_STATUS
EFIAPI
HeapToE000(
    IN UINT8 *Data,
    IN UINT32 Align,
    IN UINTN Length,
    IN OUT DATA_BUFF_STRUC *Data2 OPTIONAL)
{

    UINT8   *DataPtr = NULL;
    UINT8	*EndOfDataPtr = NULL;
    UINT32  EsegBufferSize = 0x10000;
    
    if(Data == NULL || Length == 0)
        return EFI_INVALID_PARAMETER;
    
    if(((UINTN)gE000BuffLength + Length) > EsegBufferSize)
        return EFI_BUFFER_TOO_SMALL;
    
    if(Align != 0){
        DataPtr = (UINT8*)(( (UINTN)(gE000HeapPtr + gE000BuffLength)& ~((UINTN)Align - 1)) + (UINTN)Align);
    }else{
        DataPtr = gE000HeapPtr + gE000BuffLength;
    }
    
    if(Data2 != NULL){
        Data2->BuffAddress = (UINTN)gE000HeapPtr;
        Data2->UsedLength = (UINTN)(DataPtr - gE000HeapPtr);
    
    }

    EndOfDataPtr = (UINT8*)(DataPtr + Length);
    DEBUG((DEBUG_INFO,"RsdpPlus: Align [0x%x],DataPtr [0x%lx],EndOfDataPtr [0x%lx] \n", Align, DataPtr, EndOfDataPtr));
    
    if(EndOfDataPtr > (gE000HeapPtr + EsegBufferSize))
        return EFI_BUFFER_TOO_SMALL;
    
    gBS->CopyMem(DataPtr, Data, Length);
   
    gE000BuffLength = (UINT32)(EndOfDataPtr - gE000HeapPtr);
    DEBUG((DEBUG_INFO,"RsdpPlus: (HeapToE000): gE000BuffLength [0x%x] \n", gE000BuffLength));
    
    gEsegUserCount++;
    
    return EFI_SUCCESS;
}

/**
    This is protocol function.
    According to input data and copy data to F-seg temporary buffer.
    
    @param[in]  *Data      Pointer to context to save
    @param[in]  Align       Base alignment.
    @param[in]  Length      the length of the restored confidential information
    @param      *Data2     Pointer to stored data
    
    @retval EFI_INVALID_PARAMETER   error for input data is NULL and length is 0
    @retval EFI_BUFFER_TOO_SMALL    error for Input data length is greater than EsegBufferSize
    @retval EFI_SUCCESS             Copy Data successfully

**/
EFI_STATUS
EFIAPI
HeapToF000(
    IN UINT8 *Data,
    IN UINT32 Align,
    IN UINTN Length,
    IN OUT DATA_BUFF_STRUC *Data2 OPTIONAL)
{
    UINT8   *DataPtr = NULL;
    UINT8   *EndOfDataPtr = NULL;
    UINT32  FsegBufferSize = 0xE000; // Preserve 0x2000 byte for Legacy VGA OpRom
    
    
    if(Data == NULL || Length == 0)
        return EFI_INVALID_PARAMETER;
    
    if(((UINTN)gF000BuffLength + Length) > FsegBufferSize)
        return EFI_BUFFER_TOO_SMALL;
    
    if(Align != 0){
        DataPtr = (UINT8*)(( (UINTN)(gF000HeapPtr + gF000BuffLength)& ~((UINTN)Align - 1)) + (UINTN)Align);
    }else{
        DataPtr = gF000HeapPtr + gF000BuffLength;
    }
    
    if(Data2 != NULL){
        Data2->BuffAddress = (UINTN)gF000HeapPtr;
        Data2->UsedLength = (UINTN)(DataPtr - gF000HeapPtr);
    }
    
    EndOfDataPtr = (UINT8*)(DataPtr + Length);
    DEBUG((DEBUG_INFO,"RsdpPlus: Align [0x%x],DataPtr [0x%lx],EndOfDataPtr [0x%lx] \n", Align, DataPtr, EndOfDataPtr));
    
    if(EndOfDataPtr > (gF000HeapPtr + FsegBufferSize))
        return EFI_BUFFER_TOO_SMALL;

    gBS->CopyMem(DataPtr, Data, Length);

    gF000BuffLength = (UINT32)(EndOfDataPtr - gF000HeapPtr);
    DEBUG((DEBUG_INFO,"RsdpPlus: (HeapToF000): gF000BuffLength [0x%x] \n", gF000BuffLength));

    gFsegUserCount++;

    return EFI_SUCCESS;
}

/**
    Install Shadow Ram Protocol.

    @param[in]  *Event      signal event
    @param[in]  Context     pointer to event context
    
    @retval EFI_SUCCESS     Install ShadowRam Protocol successfully

**/
EFI_STATUS
EFIAPI
ShadowRamCallBack(
    IN EFI_EVENT Event,
    IN VOID *Context
    )
{
    EFI_STATUS	Status;
    EFI_HANDLE  ShadowRameHandle = NULL;
    EFI_GUID    ShadowRamProtocolGuid = SHADOW_RAM_PROTOCOL_GUID;

    gBS->CloseEvent(Event);
    Status = gBS->InstallProtocolInterface(
                                &ShadowRameHandle,
                                &ShadowRamProtocolGuid,
                                EFI_NATIVE_INTERFACE,
                                &gShadowRamProtocol
                                );
    return Status;
}

/**
    Callback for RsdpPlus initialization.
    Register a All Driver Connect protocol callback function.
    And allocate two buff for Manage Shadow Ram protocol used.
    Install Manage Shadow Ram protocol.

    @param[in]  *Event      signal event
    @param[in]  Context     pointer to event context

**/
VOID
EFIAPI
ManageShadowRamProtocolInitCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
    )
{
    EFI_EVENT   SecondEvent;
    EFI_STATUS  Status;
    VOID        *Registration;
    static  EFI_PHYSICAL_ADDRESS    E000PagePtr;
    static  EFI_PHYSICAL_ADDRESS    F000PagePtr;
    EFI_GUID    AllDriverConnectGuid = gBdsAllDriversConnectedProtocolGuid;   
    EFI_GUID    ManageShadowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;
    EFI_GUID    GlobalVariableGuid = EFI_GLOBAL_VARIABLE;
    
#if CSM_SUPPORT
    EFI_GUID    SetupGuid   = SETUP_GUID;
    UINTN       VariableSize;
    UINT8       CurrentCsmState = 0;

    Status = gBS->CreateEvent(
            EVT_NOTIFY_SIGNAL,
            TPL_NOTIFY,
            ShadowRamCallBack,
            NULL,
            &SecondEvent
            );
    if (EFI_ERROR(Status)) 
        return;
        
    Status = gBS->RegisterProtocolNotify(
                &AllDriverConnectGuid,
                SecondEvent,
                (VOID**) &Registration
                );
    
    if (EFI_ERROR(Status))
        return;

    VariableSize = sizeof(UINT8);
    Status = gRT->GetVariable(EFI_SECURE_BOOT_NAME, &GlobalVariableGuid, NULL, &VariableSize, &CurrentCsmState);
    DEBUG((DEBUG_INFO,"RsdpPlus: Get Secure boot Global variable %r, CurrentCsmState [%d] \n", Status, CurrentCsmState));
    
    VariableSize = sizeof (SETUP_DATA);
    Status = gRT->GetVariable (L"Setup", &SetupGuid, NULL, &VariableSize, &gSetupData);
    DEBUG((DEBUG_INFO,"RsdpPlus: Get Setup Variable %r, CsmLaunchPolicy = %d.\n", Status, gSetupData.CsmSupport));
    
    if(!EFI_ERROR(Status) && (gSetupData.CsmSupport == 1 && !CurrentCsmState)){
        Status = ExecuteCsmOnLinkHook();
        DEBUG((DEBUG_INFO,"RsdpPlus: ExecuteCsmOnLinkHook %r.\n", Status));
        return;
    }
#endif
    DEBUG((DEBUG_INFO,"RsdpPlus: Non-CSM.\n"));

    Status = gBS->CreateEvent(
                EVT_NOTIFY_SIGNAL,
                TPL_NOTIFY,
                ShadowRamCallBack,
                NULL,
                &SecondEvent
                );

    if (EFI_ERROR(Status)) 
        return;

    Status = gBS->RegisterProtocolNotify(
                &AllDriverConnectGuid,
                SecondEvent,
                (VOID**) &Registration
                );
    
    if (EFI_ERROR(Status))
        return;

    Status = gBS->AllocatePages(
                 AllocateAnyPages, 
                 EfiBootServicesData, 
                 16,
                 &E000PagePtr);
    ASSERT_EFI_ERROR(Status);
    
    gE000HeapPtr = (UINT8*)E000PagePtr;
    DEBUG((DEBUG_INFO,"RsdpPlus: gE000HeapPtr [0x%lx] \n", gE000HeapPtr));

    Status = gBS->AllocatePages(
                AllocateAnyPages,
                EfiBootServicesData,
                16,
                &F000PagePtr);
    ASSERT_EFI_ERROR(Status);
    
    gF000HeapPtr = (UINT8*)F000PagePtr;
    DEBUG((DEBUG_INFO,"RsdpPlus: gF000HeapPtr [0x%lx] \n", gF000HeapPtr));

    Status = gBS->InstallProtocolInterface(
                    &gManageShadowRamHandle,
                    &ManageShadowRamProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gManageShadowRamProtocol
                    );
    DEBUG((DEBUG_INFO,"RsdpPlus: Install Manage ShadowRam Protocol %r.\n", Status));
    return;
}

/**
    Entry point for RsdpPlus initialization.
    
    @param  ImageHandle     The firmware allocated handle for the EFI image.
    @param  SystemTable     A pointer to the EFI System Table.
    
    @retval EFI_SUCCESS     The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
ManageShadowRamEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_EVENT   Event;
    VOID        *Registration;
    VOID        *Protocol;

    Status = gBS->LocateProtocol(&gEfiAcpiSupportProtocolGuid, NULL, (VOID**) &Protocol);
    DEBUG((DEBUG_INFO,"RsdpPlus: Locate ACPI Support Protocol %r \n", Status));
    if(!EFI_ERROR(Status)){
        ManageShadowRamProtocolInitCallback(NULL,NULL);
    }else{

        Status = gBS->CreateEvent(
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    ManageShadowRamProtocolInitCallback,
                    NULL,
                    &Event
                    );

        if (EFI_ERROR(Status)) 
            return Status;

        Status = gBS->RegisterProtocolNotify(
                    &gEfiAcpiSupportProtocolGuid,
                    Event,
                    (VOID**) &Registration
                    );
        
        if (EFI_ERROR(Status))
            return Status;        
    }
    
    return EFI_SUCCESS;
}

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
