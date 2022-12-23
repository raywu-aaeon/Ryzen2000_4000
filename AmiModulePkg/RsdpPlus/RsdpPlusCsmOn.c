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

/** @file RsdpPlusCsmOn.c 
    Support Legacy BIOS protocol to locate shadow ram when CSM on.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Protocol/ManageShadowProtocol.h>
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
EFI_STATUS EFIAPI CsmOnHeapToE000(UINT8 *Data, UINT32 Align, UINTN Length, DATA_BUFF_STRUC *Data2 OPTIONAL);
EFI_STATUS EFIAPI CsmOnHeapToF000(UINT8 *Data, UINT32 Align, UINTN Length, DATA_BUFF_STRUC *Data2 OPTIONAL);

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
EFI_LEGACY_BIOS_PROTOCOL    *gLegacyBiosProtocol = NULL;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)
extern VOID *gLegacyRegionAddress;
extern EFI_HANDLE   gManageShadowRamHandle;
extern VOID EFIAPI OemUpdateE000ShadowRamHook(UINT32*   ShadowRam, UINTN   UsageLength);
extern VOID EFIAPI OemUpdateF000ShadowRamHook(UINT32*   ShadowRam, UINTN   UsageLength);   
extern UPDATE_E000_SHADOW_RAM_HOOK* gUpdateE000ShadowRamHookList[];
extern UPDATE_F000_SHADOW_RAM_HOOK* gUpdateF000ShadowRamHookList[];
extern MANAGE_SHADOW_RAM_PROTOCOL gManageShadowRamProtocol;

// Function Definition(s)

//--------------------------------------------------------------------------- 

/**
    This is protocol function.
    According to input data and copy data to E-seg via legacy BIOS protocol.

    @param[in]  *Data      Pointer to context to save
    @param[in]  Align       Base alignment.
    @param[in]  Length      the length of the restored confidential information
    @param      *Data2     Pointer to stored data
    
    @retval EFI_SUCCESS             Copy Data successfully.
    
**/
EFI_STATUS
EFIAPI
CsmOnHeapToE000(
    IN UINT8 *Data,
    IN UINT32 Align,
    IN UINTN Length,
    IN OUT DATA_BUFF_STRUC *Data2 OPTIONAL)
{
    EFI_STATUS  Status;

    DEBUG((DEBUG_INFO,"RsdpPlus: (CsmOn): HeapToE000.\n"));

    Status = gLegacyBiosProtocol->GetLegacyRegion(gLegacyBiosProtocol,
                                        Length,
                                        E0000_BIT,
                                        (UINTN)Align,
                                        &gLegacyRegionAddress);
    if(EFI_ERROR(Status))
        return Status;

    Status = gLegacyBiosProtocol->CopyLegacyRegion(gLegacyBiosProtocol,
                                        Length,
                                        gLegacyRegionAddress,
                                        (VOID *)Data);
   if(EFI_ERROR(Status))
        return Status;

    if(Data2 != NULL){
        Data2->BuffAddress = (UINTN)gLegacyRegionAddress;
        Data2->UsedLength = Length;
        DEBUG((DEBUG_INFO,"RsdpPlus: Locate Fseg addr [0x%lx], Data Length 0x%x\n", Data2->BuffAddress, Data2->UsedLength));
    }   

    return Status;      
}
        
/**
    This is protocol function.
    According to input data and copy data to F-seg via legacy BIOS protocol.

    @param[in]  *Data      Pointer to context to save
    @param[in]  Align       Base alignment.
    @param[in]  Length      the length of the restored confidential information
    @param      *Data2     Pointer to stored data
    
    @retval EFI_SUCCESS             Copy Data successfully.
    
**/
EFI_STATUS
EFIAPI
CsmOnHeapToF000(
    IN UINT8 *Data,
    IN UINT32 Align,
    IN UINTN Length,
    IN OUT DATA_BUFF_STRUC *Data2 OPTIONAL)
{
    EFI_STATUS  Status;

    DEBUG((DEBUG_INFO,"RsdpPlus: (CsmOn): HeapToF000.\n"));

    Status = gLegacyBiosProtocol->GetLegacyRegion(gLegacyBiosProtocol,
                                        Length,
                                        F0000_BIT,
                                        (UINTN)Align,
                                        &gLegacyRegionAddress);
    if(EFI_ERROR(Status))
        return Status;

    Status = gLegacyBiosProtocol->CopyLegacyRegion(gLegacyBiosProtocol,
                                        Length,
                                        gLegacyRegionAddress,
                                        (VOID *)Data);
   if(EFI_ERROR(Status))
        return Status;

    if(Data2 != NULL){
        Data2->BuffAddress = (UINTN)gLegacyRegionAddress;
        Data2->UsedLength = Length;
        DEBUG((DEBUG_INFO,"RsdpPlus: Locate Fseg addr [0x%lx], Data Length 0x%x\n", Data2->BuffAddress, Data2->UsedLength));
    }

    return Status;
}

/**
    Locate Legacy Bios Protocol and Install Shadow Ram Protocol.
    
    @param[in]  *Event      signal event
    @param[in]  Context     pointer to event context
    
**/
VOID
EFIAPI
LocateLegacyBiosProCallBack(
    IN EFI_EVENT Event,
    IN VOID *Context
    )
{
    EFI_STATUS  Status;
    EFI_GUID    ManageShadowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;
    
    gBS->CloseEvent(Event);
    Status = gBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid,
                                 NULL,
                                 (VOID**) &gLegacyBiosProtocol);
    DEBUG((DEBUG_INFO,"RsdpPlus: (CallBack) Locate LegacyBios Protocol %r.\n", Status));
    if(EFI_ERROR(Status))
        return;

    gManageShadowRamProtocol.HeapToE000 = CsmOnHeapToE000;
    gManageShadowRamProtocol.HeapToF000 = CsmOnHeapToF000;
    Status = gBS->InstallProtocolInterface(
                    &gManageShadowRamHandle,
                    &ManageShadowRamProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gManageShadowRamProtocol
                    );
    DEBUG((DEBUG_INFO,"RsdpPlus: (CallBack) Install Manage ShadowRam Protocol %r.\n", Status));       
    return;
}

/**
    Elink function for RsdpPlus CSM On initialization.
    Install Manage Shadow Ram protocol that support LegacyBios protocol.
    
    @retval EFI_SUCCESS     Install protocol successfully
    
**/
EFI_STATUS
EFIAPI
RsdpPlusCsmOnEntryPoint(VOID)
{

    EFI_STATUS  Status;
    EFI_EVENT   Event;  
    VOID        *Registration;
    EFI_GUID    ManageShadowRamProtocolGuid = MANAGE_SHADOW_RAM_PROTOCOL_GUID;

    DEBUG((DEBUG_INFO,"RsdpPlus: RsdpPlusCsmOnEntryPoint.\n"));

    Status = gBS->LocateProtocol(&gEfiLegacyBiosProtocolGuid,
                                 NULL,
                                 (VOID**) &gLegacyBiosProtocol);
    DEBUG((DEBUG_INFO,"RsdpPlus: Locate LegacyBios Protocol %r.\n", Status));

    if(EFI_ERROR(Status)){
        Status = gBS->CreateEvent(
                EVT_NOTIFY_SIGNAL,
                TPL_NOTIFY,
                LocateLegacyBiosProCallBack,
                NULL,
                &Event
                );
        if (EFI_ERROR(Status))
            return Status;
        
        Status = gBS->RegisterProtocolNotify(
                &gEfiLegacyBiosProtocolGuid,
                Event,
                (VOID**) &Registration
                );
        if (EFI_ERROR(Status))
            return Status;
                        
    }
    
    gManageShadowRamProtocol.HeapToE000 = CsmOnHeapToE000;
    gManageShadowRamProtocol.HeapToF000 = CsmOnHeapToF000;
    Status = gBS->InstallProtocolInterface(
                    &gManageShadowRamHandle,
                    &ManageShadowRamProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &gManageShadowRamProtocol
                    );
    DEBUG((DEBUG_INFO,"RsdpPlus: Install Manage ShadowRam Protocol %r.\n", Status));
    return Status;
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
