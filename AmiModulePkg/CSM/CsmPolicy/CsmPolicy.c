//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file CsmPolicy.c
    Implementation of CSM policy functions

**/


#include <Token.h>
#include <AmiDxeLib.h>
#include <BootOptions.h>
#include <Protocol/PciIo.h>
#include <Protocol/LegacyBiosExt.h>
#include <Setup.h>
#include <CsmElinkFunctions.h>
#include <Protocol/AmiCsmOpromPolicy.h>

#define DEFAULT_HANDLE_BUFFER_SIZE 0x40
typedef struct {
    UINTN TotalSize;
    UINTN CurrentSize;
    EFI_HANDLE *Array;
} HANDLE_BUFFER;

HANDLE_BUFFER ThunkHandles;
HANDLE_BUFFER NonThunkHandles;
static EFI_HANDLE SharedGopHandle = 0;
static BOOLEAN UefiGopDisconnected = FALSE;
static BOOLEAN ProceedToBoot = FALSE;

EFI_EVENT gLocateHandlesPolicyEvent = NULL;
EFI_EVENT gProceedToBootPolicyEvent = NULL;
EFI_EVENT gPolicyEvent = NULL;

//----------------------------------------------------------------------------
static EFI_GUID gSetupGuid = SETUP_GUID;
extern EFI_GUID gBdsAllDriversConnectedProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gAmiOpromPolicyProtocolGuid;
extern EFI_GUID gAmiCsmThunkDriverGuid;

typedef EFI_STATUS (OEM_CHECK_UEFI_OPROM_POLICY) (EFI_HANDLE PciHandle);
extern OEM_CHECK_UEFI_OPROM_POLICY CSM_CHECK_UEFI_OPROM_POLICY EndOfCheckUefiOpromPolicyFunctions;
OEM_CHECK_UEFI_OPROM_POLICY* OemCheckUefiOpromPolicyList[] = { CSM_CHECK_UEFI_OPROM_POLICY NULL };

UINT8 CurrentCsmState;
VOID *DriverBindingRegistration;
SETUP_DATA SetupData;

typedef struct CSM_POLICY_SETUP_DATA {
    UINT8  BootOptionFilter;
    UINT8  PxeOpRom;
    UINT8  MassStorageOpRom;
    UINT8  VideoOpRom;
/*
    We added the following field to preserve functionality existed in previous
    PciBus versions. For PCI devices other than Network,Mass Storage or Video
    value of following field will determine OpROM behavior as before.
*/
    UINT8  OldOpRom;
} CSM_POLICY_SETUP_DATA;

CSM_POLICY_SETUP_DATA CsmPolicySetupData = {
    DEFAULT_BOOT_OPTION_FILTERING_POLICY,
    DEFAULT_PXE_OPROM_POLICY,
    DEFAULT_MASS_STORAGE_OPROM_POLICY,
    DEFAULT_VIDEO_OPROM_POLICY,
    1
};

EFI_STATUS EFIAPI CheckUefiOpRomPolicy(
    IN	AMI_OPROM_POLICY_PROTOCOL *This,
    IN	UINT8                     PciClass
);

VOID EFIAPI ProcessOpRom(
    IN OPTIONAL CSM_PLATFORM_POLICY_DATA *OpRomStartEndProtocol
);

AMI_OPROM_POLICY_PROTOCOL AmiOpRomPolicyProtocol = {
    CheckUefiOpRomPolicy,
    ProcessOpRom
};

EFI_STATUS EFIAPI CheckUefiOpRomPolicyByPciHandle(
    IN  AMI_CSM_OPROM_POLICY_PROTOCOL *This,
    IN  EFI_HANDLE                PciHandle
);

AMI_CSM_OPROM_POLICY_PROTOCOL AmiOpRomPolicyByPciHandleProtocol = {
    CheckUefiOpRomPolicyByPciHandle,
    (AMI_CSM_OPROM_POLICY_PROCESS)ProcessOpRom
};

EFI_STATUS AddHandle(
    IN OUT HANDLE_BUFFER *Target,
    EFI_HANDLE Handle
);

/**
    This function filters available boot options based on Setup
    control value
               
         
    @param Device Pointer to boot device

          
    @retval TRUE boot option will be removed from boot list
    @retval FALSE boot option won't be removed from boot list

**/
BOOLEAN CsmPolicyFilter( 
    IN BOOT_DEVICE *Device 
)
{
    BOOLEAN Result = FALSE;

    if(CurrentCsmState == 0)    //CSM is disabled on current boot - no need to filter boot options
        return Result;

    switch (CsmPolicySetupData.BootOptionFilter) {
        case 0: // Enable all boot options
            break;

        case 1: // Disable UEFI boot options
            Result = (Device->BbsEntry == NULL);
            break;

        case 2: // Disable Legacy boot options
            Result = (Device->BbsEntry != NULL);
            break;

        default:
            break;
    }
    return Result;
}

/**
    This function returns OpROM policy for given PCI class of the device

    @param 
        UINT8 PciClass - class of PCI device to check

         
    @retval UINT8 policy (0-disable all, 1-disable Legacy, 2-disable UEFI)

**/
UINT8 GetOpRomPolicy(
    IN UINT8 PciClass
)
{
    UINT8 Policy = 0xff;

    switch(PciClass) {
        case PCI_CL_NETWORK:
            Policy = CsmPolicySetupData.PxeOpRom;
            break;

        case PCI_CL_MASS_STOR:
            Policy = CsmPolicySetupData.MassStorageOpRom;
            break;

        case PCI_CL_DISPLAY:
            Policy = CsmPolicySetupData.VideoOpRom;
            break;

        default:
/*
    For PCI devices with PCI class different from Network, Mass Storage or Video
    behavior will be as in previous versions of PciBus driver - UEFI OpROM will
    be executed first or not executed at all
*/
            Policy = CsmPolicySetupData.OldOpRom;
            break;
    }
    return Policy;
}

/**
    This function determines should OpROM be executed

    @param PciClass - class of PCI device to check
    @param UefiOprom - TRUE if verifying UEFI OpROM, FALSE for Legacy OpROM

         
    @retval EFI_SUCCESS OpROM should be executed
    @retval EFI_UNSUPPORTED OpROM should not be executed

**/
EFI_STATUS CheckOpRomExecution(
    IN UINT8 PciClass,
    IN BOOLEAN UefiOprom
)
{
    UINT8 Policy;
    BOOLEAN Result = TRUE;

    Policy = GetOpRomPolicy(PciClass);

    switch(Policy) {
        case 0:     //all OpROMs are disabled
            Result = FALSE;
            break;

        case 1:     //only UEFI OpROMs are enabled
            Result = (UefiOprom) ? TRUE : FALSE;
            break;

        case 2:     //only Legacy OpROMs are enabled
            Result = (UefiOprom) ? FALSE : TRUE;
            break;

        default:    //all OpROMs are enabled
            break;
    }
    return (Result) ? EFI_SUCCESS : EFI_UNSUPPORTED;       
}

/**
    This function disconnects native UEFI GOP driver before
    executing legacy video BIOS

          
    @param PciIo instance of PciIo protocol on handle,
        that have to be disconnected

         
    @retval EFI_SUCCESS driver was disconnected
    @retval EFI_UNSUPPORTED driver can't be disconnected

**/
EFI_STATUS DisconnectUefiGop(
    IN EFI_PCI_IO_PROTOCOL *PciIo
)
{
    EFI_STATUS Status;
    EFI_HANDLE *Handles;
    EFI_HANDLE TmpHandle = NULL;
    UINTN Count;
    UINTN i;
    VOID *Interface;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *Entries;
    UINT64 Capabilities;
    
/* first find corresponding handle */
    Status = pBS->LocateHandleBuffer(ByProtocol, &gEfiPciIoProtocolGuid, NULL, &Count, &Handles);
    if(EFI_ERROR(Status))
        return Status;

    for(i = 0; i < Count; i++) {
        Status = pBS->HandleProtocol(Handles[i], &gEfiPciIoProtocolGuid, &Interface);
        if(EFI_ERROR(Status))
            continue;

        if((VOID *)PciIo == Interface) {
            SharedGopHandle = Handles[i];
            break;
        }
    }
    pBS->FreePool(Handles);

    if(i == Count)              //no matches
        return EFI_NOT_FOUND;

/* now find child handle where Gop is installed */
    Status = pBS->OpenProtocolInformation(SharedGopHandle, &gEfiPciIoProtocolGuid, &Entries, &Count);
    if(EFI_ERROR(Status))
        return Status;

    for(i = 0; i < Count; i++) {
        if(!(Entries[i].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER))
            continue;

        Status = pBS->HandleProtocol(Entries[i].ControllerHandle, &gEfiGraphicsOutputProtocolGuid, &Interface);
        if(!EFI_ERROR(Status)) {
            TmpHandle = Entries[i].AgentHandle;
            break;
        }
    }
    pBS->FreePool(Entries);

    if(i == Count)              //no matches
        return EFI_NOT_FOUND;

/* now check if AgentHandle is our CSM thunk */
    Status = pBS->HandleProtocol(TmpHandle, &gAmiCsmThunkDriverGuid, &Interface);
    if(!EFI_ERROR(Status))
        return EFI_SUCCESS;

    pBS->DisconnectController(SharedGopHandle, NULL, NULL);
/* we have to restore PCI attributes so video BIOS can be executed */
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationSupported, 
                0, &Capabilities); 
    if (EFI_ERROR(Status))
        return Status;
    
    Status = PciIo->Attributes (PciIo, EfiPciIoAttributeOperationEnable,
                Capabilities & EFI_PCI_DEVICE_ENABLE, NULL);        
    return Status;
}

/**
    This function will be called before and after installing legacy OpROM

          
    @note  
  PolicyData is valid when this call is made before Option ROM execution, it
  is NULL when this function is called after Option ROM execution.

**/
VOID EFIAPI ProcessOpRom(
    IN OPTIONAL CSM_PLATFORM_POLICY_DATA *OpRomStartEndProtocol
)
{
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8 PciClassCode;

    if(OpRomStartEndProtocol == NULL) { //post-process OpROM callback
        if(UefiGopDisconnected && !ProceedToBoot)
/* if this is last OpROM, and Gop was disconnected and we're not on legacy boot path */
            pBS->ConnectController(SharedGopHandle, NULL, NULL, TRUE);
        return;
    }

//check if someone already disabled execution of this OpROM
    if(OpRomStartEndProtocol->PciIo == NULL || OpRomStartEndProtocol->ExecuteThisRom == FALSE)
        return;

    PciIo = OpRomStartEndProtocol->PciIo;
    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClassCode);
    if (EFI_ERROR(Status)) 
        return;

    Status = CheckOpRomExecution(PciClassCode, FALSE);
    if(EFI_ERROR(Status)) {
        OpRomStartEndProtocol->ExecuteThisRom = FALSE;
        return;
    }

/* OK, we're decided to execute OpROM */
    OpRomStartEndProtocol->ExecuteThisRom = TRUE;

    if(PciClassCode == PCI_CL_DISPLAY) {
        Status = DisconnectUefiGop(PciIo);
    /* 
        we are executing video OpROM even if we can't disconnect
        native UEFI driver - possible bug
    */
        if(!EFI_ERROR(Status))
            UefiGopDisconnected = TRUE;
    }
    return;
}

/**
    This callback executed every time DriverBinding is installed

          
    @param Event Callback event
    @param Context pointer to calling context

**/
VOID EFIAPI LocateHandlesCallback(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS Status;
    EFI_STATUS Status1;
    UINTN Count = sizeof(EFI_HANDLE);
    EFI_HANDLE Handle;
    VOID *DummyInterface;

    do {
        Status = pBS->LocateHandle(ByRegisterNotify, 
                    NULL, 
                    DriverBindingRegistration, 
                    &Count, 
                    &Handle);
        if(!EFI_ERROR(Status)) {
            Status1 = pBS->HandleProtocol(Handle, 
                        &gAmiCsmThunkDriverGuid, 
                        &DummyInterface);
            if(EFI_ERROR(Status1)) { 
                Status = AddHandle(&NonThunkHandles, Handle);
            } else {
                Status = AddHandle(&ThunkHandles, Handle);
            }
        }
    } while (!EFI_ERROR(Status));
            
    return;
}

/**
    This function allocates buffer to store DriverBinding handles

          
    @param Target pointer to buffer to be initialized

**/
EFI_STATUS InitHandleBuffer(
    IN OUT HANDLE_BUFFER *Target
)
{
    EFI_STATUS Status;

    Status = pBS->AllocatePool(EfiBootServicesData, 
                    sizeof(EFI_HANDLE) * DEFAULT_HANDLE_BUFFER_SIZE, 
                    (VOID **)&(Target->Array));
    if(!EFI_ERROR(Status)) {
        Target->TotalSize = DEFAULT_HANDLE_BUFFER_SIZE;
        Target->CurrentSize = 0;
    }
    return Status;
}

/**
    This function increases and reallocates buffer to store 
    DriverBinding handles

          
    @param Target pointer to buffer to be increased

**/
EFI_STATUS IncreaseHandleBuffer(
    IN OUT HANDLE_BUFFER *Target
)
{
    EFI_STATUS Status;
    VOID *NewArray;

    Status = pBS->AllocatePool(EfiBootServicesData, 
                    sizeof(EFI_HANDLE) * (Target->TotalSize + DEFAULT_HANDLE_BUFFER_SIZE), 
                    &NewArray);
    if(!EFI_ERROR(Status)) {
        MemCpy(NewArray, Target->Array, sizeof(EFI_HANDLE) * Target->CurrentSize);
        Target->TotalSize += DEFAULT_HANDLE_BUFFER_SIZE;

        pBS->FreePool(Target->Array);
        Target->Array = (EFI_HANDLE *)NewArray;
    }
    return Status;
}

/**
    This function stores handles in allocated buffer

          
    @param Target pointer to buffer to store handle in
    @param Handle handle to be stored

    @retval 
        EFI_STATUS

**/
EFI_STATUS AddHandle(
    IN OUT HANDLE_BUFFER *Target,
    EFI_HANDLE Handle
)
{
    EFI_STATUS Status;

    if(Target->CurrentSize >= Target->TotalSize) {
        Status = IncreaseHandleBuffer(Target);
        if(EFI_ERROR(Status))
            return Status;
    }

    Target->Array[Target->CurrentSize] = Handle;
    Target->CurrentSize++;
    return EFI_SUCCESS;
}

/**
    This callback executed when all drivers are connected and system
    proceeds to boot

          
    @param Event Callback event
    @param Context pointer to calling context

**/
VOID EFIAPI ProceedToBootCallback(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    ProceedToBoot = TRUE;
}


/**
    Initialization of CsmPolicy data; this is a callback notification on
    gLegacyBiosProtocol installation

               
    @param Event Callback event
    @param Context pointer to calling context

**/
VOID EFIAPI CsmPolicyInit(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS Status;
    VOID *Registration;
    EFI_HANDLE Handle;
    UINTN Size = sizeof(EFI_HANDLE);

    CurrentCsmState = 1;

    Status = pBS->LocateHandle(ByProtocol, &gEfiLegacyBiosProtocolGuid, NULL, &Size, &Handle);

    if(EFI_ERROR(Status)) {
      return;
    }
	
    CsmPolicySetupData.BootOptionFilter = SetupData.BootOptionFilter;
    CsmPolicySetupData.VideoOpRom = SetupData.VideoOpRom;

    Status = RegisterProtocolCallback(&gBdsAllDriversConnectedProtocolGuid, 
                     ProceedToBootCallback, 
                     NULL, 
                     &gProceedToBootPolicyEvent, 
                     &Registration);
    ASSERT_EFI_ERROR(Status);

    /* Init platform driver override protocol */
    Status = InitHandleBuffer(&ThunkHandles);
    ASSERT_EFI_ERROR(Status);

    Status = InitHandleBuffer(&NonThunkHandles);
    ASSERT_EFI_ERROR(Status);

    Status = RegisterProtocolCallback(&gEfiDriverBindingProtocolGuid, 
                    LocateHandlesCallback, 
                    NULL, 
                    &gLocateHandlesPolicyEvent, 
                    &DriverBindingRegistration);
    ASSERT_EFI_ERROR(Status);

    /*call callback manually to get already registered handles */
    LocateHandlesCallback(gLocateHandlesPolicyEvent, NULL);
    
    Status = pBS->InstallMultipleProtocolInterfaces(&Handle,
                    &gAmiOpromPolicyProtocolGuid, 
                    &AmiOpRomPolicyProtocol,
                    &gAmiCsmOpromPolicyProtocolGuid, 
                    &AmiOpRomPolicyByPciHandleProtocol,
                    NULL);
    ASSERT_EFI_ERROR(Status);

}


/**
    This function is CsmPolicy driver entry point 

         
    @param ImageHandle Image handle
    @param SystemTable pointer to system table

          
    @retval EFI_SUCCESS Function executed successfully
    @retval EFI_ERROR Some error occurred during execution

**/
EFI_STATUS
EFIAPI
CsmPolicyEntry(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle;
    UINTN Size = sizeof(SETUP_DATA);
    VOID *Registration;

    InitAmiLib(ImageHandle, SystemTable);
    
    Status = pRS->GetVariable(L"Setup", &gSetupGuid, NULL, &Size, &SetupData);

    if (!EFI_ERROR(Status)) {
        CsmPolicySetupData.BootOptionFilter = SetupData.BootOptionFilter;
        CsmPolicySetupData.PxeOpRom = SetupData.PxeOpRom;
        CsmPolicySetupData.MassStorageOpRom = SetupData.MassStorageOpRom;
        CsmPolicySetupData.VideoOpRom = SetupData.VideoOpRom;
        CsmPolicySetupData.OldOpRom = SetupData.OldOpRom;
    } else {
        CsmPolicySetupData.BootOptionFilter = DEFAULT_BOOT_OPTION_FILTERING_POLICY;
        CsmPolicySetupData.PxeOpRom = DEFAULT_PXE_OPROM_POLICY;
        CsmPolicySetupData.MassStorageOpRom = DEFAULT_MASS_STORAGE_OPROM_POLICY;
        CsmPolicySetupData.VideoOpRom = DEFAULT_VIDEO_OPROM_POLICY;
        CsmPolicySetupData.OldOpRom = DEFAULT_OLD_OPROM_POLICY;
    }
    
    CurrentCsmState = 0;
    
// Determine current CSM state based on whether gEfiLegacyBiosProtocolGuid protocol is installed
    Size = sizeof(EFI_HANDLE);
    Status = pBS->LocateHandle(ByProtocol, &gEfiLegacyBiosProtocolGuid, NULL, &Size, &Handle);

    if(!EFI_ERROR(Status)) {
        CsmPolicyInit(NULL, NULL);
    } else {
        RegisterProtocolCallback(&gEfiLegacyBiosProtocolGuid, 
                    CsmPolicyInit, 
                    NULL, 
                    &gPolicyEvent, 
                    &Registration);
//Reset Boot option filter to avoid situation, when no boot options are available
        CsmPolicySetupData.BootOptionFilter = 0;
//Set video policy to UEFI only
        CsmPolicySetupData.VideoOpRom = 1;
    }

    return EFI_SUCCESS;
}


/**
  Library destructor.
  Free resources, remove the callbacks registered in constructor.
**/

EFI_STATUS
EFIAPI
CsmPolicyDestructor(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    if (gLocateHandlesPolicyEvent != NULL)
    {
        pBS->CloseEvent(gLocateHandlesPolicyEvent);
        gLocateHandlesPolicyEvent = NULL;
    }
    if (gProceedToBootPolicyEvent != NULL)
    {
        pBS->CloseEvent(gProceedToBootPolicyEvent);
        gProceedToBootPolicyEvent = NULL;
    }

    if (gPolicyEvent != NULL)
    {
        pBS->CloseEvent(gPolicyEvent);
        gPolicyEvent = NULL;
    }
    
    return EFI_SUCCESS;
}

/**
    This function is a part of AmiOpRomPolicyProtocol

         
    @param This -pointer to AMI_OPROM_POLICY_PROTOCOL
    @param PciClass -PCI device class

          
    @retval EFI_SUCCESS OpROM should be executed
    @retval EFI_UNSUPPORTED OpROM should not be executed

**/
EFI_STATUS EFIAPI CheckUefiOpRomPolicy(
    IN	AMI_OPROM_POLICY_PROTOCOL *This,
    IN	UINT8                     PciClass
)
{
    return CheckOpRomExecution(PciClass, TRUE);
}

/**
    This function is a part of AmiOpRomPolicyByPciHandleProtocol

         
    @param This -pointer to pointer to AMI_OPROM_POLICY_BY_PCIHANDLE_PROTOCOL
    @param PciHandle -PCI device handle

          
    @retval EFI_SUCCESS OpROM should be executed
    @retval EFI_UNSUPPORTED OpROM should not be executed

**/
EFI_STATUS EFIAPI CheckUefiOpRomPolicyByPciHandle(
    IN  AMI_CSM_OPROM_POLICY_PROTOCOL *This,
    IN  EFI_HANDLE                PciHandle
)
{
    UINT32 i;
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8 PciClass;

    for(i = 0; OemCheckUefiOpromPolicyList[i] != NULL; i++) {
        Status = OemCheckUefiOpromPolicyList[i](PciHandle);
        if(Status == EFI_SUCCESS || Status == EFI_UNSUPPORTED)
            return Status;
    }

    Status = pBS->HandleProtocol(PciHandle, &gEfiPciIoProtocolGuid, (VOID**)&PciIo);
    if(EFI_ERROR(Status))
        return Status;

    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint8, 0xB, 1, &PciClass);

    return (EFI_ERROR(Status))? Status : CheckOpRomExecution(PciClass, TRUE);
}

