//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SdioDriver.c
    SDIO controller detection and configuration.
**/
#define SDIO_WRITE_PROTECT_ERR          0x003   // Write protect error

//----------------------------------------------------------------------

#include <SdioDriver.h>
#include <SdioElink.h>
#include <SdMmcPassThruSupport.h>
#include <Protocol/EraseBlock.h>
#include <Protocol/SmmControl2.h>

EFI_GUID gEfiSdMmcPassThruProtocolGuid = EFI_SD_MMC_PASS_THRU_PROTOCOL_GUID;
EFI_GUID gEfiEraseBlockProtocolGuid = EFI_ERASE_BLOCK_PROTOCOL_GUID;

#if ( defined(BOOT_SECTOR_WRITE_PROTECT) && (BOOT_SECTOR_WRITE_PROTECT != 0) )
#include <Protocol/AmiBlockIoWriteProtection.h>
AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *AmiBlkWriteProtection = NULL;
#endif

EFI_PHYSICAL_ADDRESS    gSdioReadData;
UINT8                   *SDDevnameForPNMZero  = (UINT8 *)"SD Memory Card - Device ";
UINT8                   *MMCDevnameForPNMZero = (UINT8 *)"MMC Memory Card - Device ";
CHAR16                  *gSdioBusDriverName = L"AMI SDIO Driver";
SDIO_DEV_CONFIGURATION  gSdioConfiguration;
EFI_HANDLE              gSdioDataHandle = NULL;
EFI_GUID                SdioRuntimeDataGuid = SDIO_RUNTIME_DATA_GUID;

EFI_EVENT               gEvSdioEnumTimer = NULL;
INT32                   gCounterSdioEnumTimer = 0;


//Global Buffers used for SMM Communication 
UINT8                   *gSdioCommunicateBuffer = NULL;
UINTN                   gSdioCommunicateBufferSize;

// EFI Driver Binding Protocol Instance
EFI_DRIVER_BINDING_PROTOCOL gSdioDriverBinding = {
    SdioDriverSupported,
    SdioDriverStart,
    SdioDriverStop,
    0x10,
    NULL,
    NULL
};

EFI_COMPONENT_NAME2_PROTOCOL gSdioCtlDriverName = {
    SdioCtlDriverName,
    SdioCtlGetControllerName,
    LANGUAGE_CODE_ENGLISH
};

EFI_SMM_CONTROL2_PROTOCOL   *gSmmCtl = NULL;
SDIO_GLOBAL_DATA            *gSdioData = NULL;
EFI_GUID                    gAmiSdioCommunicationGuid = SDIO_PARAMETER_BASE_ADDRESS_GUID;
EFI_GUID                    gAmiSdEmmcControllerInitProtocolGuid = AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL_GUID;
EFI_GUID                    gAmiSdEmmcVendorDevicePathGuid = AMI_SD_EMMC_VENDOR_DEVICE_PATH_GUID;

/**@internal
 * 
    Timer call-back routine that is used to monitor changes in 
    Sdio Bus.It monitors the state of the PSTATE register for 
    the device presence
    
    When this routine finds a new device connected to controller it
    will install a device node for that device by calling
    DetectAndConfigureDevice
    
    When this routine finds a disconneced device it uninstalls the
    device node by calling SdMCheckDeviceRemoval
    
    @param  Event   - Event whose notification function is being invoked.
    @param  Context - Pointer to the notification function's context.
    
    @return VOID
   
   @endinternal
**/
VOID
EFIAPI
SdioHotPlugTimer(
    EFI_EVENT   Event,
    VOID        *Context
)
{
    
    UINT8                     SlotNo = 0;
    SDIO_DEVICE_INTERFACE     *SdioDevInterface = NULL;
    AMI_SDIO_BUS_PROTOCOL     *SdioBusInterface = NULL;
    EFI_STATUS                Status = 0;
    UINTN                     NumHandles;
    EFI_HANDLE                *HandleBuffer;
    UINTN                     Index;
    UINT32                    PresentState;
    BOOLEAN                   CardPresentState = FALSE;
    
    if (Event) {
            gBS->SetTimer(Event, TimerCancel, ONESECOND /10);
    }
    
    // Locating all the handles that supports the SdioBusinitProtocol
    Status = gBS->LocateHandleBuffer (
                               ByProtocol,
                               &gSdioBusInitProtocolGuid,
                               NULL,
                               &NumHandles,
                               &HandleBuffer);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        gBS->SetTimer (Event, TimerPeriodic, ONESECOND / 10);
        return;
    }    
    
    for (Index = 0; Index < NumHandles; ++Index) {
        
        gBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gSdioBusInitProtocolGuid,
                        (VOID**)&SdioBusInterface);
            
        if (SdioBusInterface) {
            // Configuring the device if the device is present in slot
            for (SlotNo = 0; SlotNo < SdioBusInterface->NumberOfSlotsImplemented; SlotNo++) {
                
                CardPresentState = FALSE;
                PresentState = SDIO_REG32 (SdioBusInterface->SdioBaseAddress[SlotNo], PSTATE);
                // Check for card presence
                if (PresentState & PSTATE_CARD_INSERT) {
                    CardPresentState = TRUE;
                }
               // Skip the card detection if the card state(card removed and plugged in again) is not changed.
               if ((SdioBusInterface->CardPresentState[SlotNo] ^ CardPresentState) == 0) {
                   continue;
               }
                Status = DetectAndConfigureDevice (&gSdioDriverBinding, SdioBusInterface->ControllerHandle, NULL, SdioBusInterface, SlotNo);
                if (!EFI_ERROR(Status)) {
                    
                    SdioDevInterface = GetSdioDevInterface (SdioBusInterface, SlotNo);
                    if (SdioDevInterface != NULL) {
                        // Checking the device removal only for RemovableMedia
                        if (SdioDevInterface->SdioBlkIo->BlkIo.Media->RemovableMedia == TRUE) {
                            // Uninstalling the BlockIO and removing the device from the list if SdCard is removed
                            Status = SdCheckDeviceRemoval (SdioBusInterface, SlotNo);
                            ASSERT_EFI_ERROR (Status);
                        }
                    }	
                }
            }
        }
    }
    
    gBS->FreePool (HandleBuffer);
    
    if (Event) {
            gBS->SetTimer (Event, TimerPeriodic, ONESECOND / 10);
    }
    
}


/**
    This function notifies Legacy Boot event is signaled or not
    for restricting INT13 SMM calls before legacy boot event and
    to pass signature in smm region to unregister the Sw Smi handler.
     
    @param  Event   - Event whose notification function is being invoked.
    @param  Context - Pointer to the notification function's context.
    
    @retval    VOID
  
**/
VOID
EFIAPI
LegacyBootNotify (  
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    
    EFI_STATUS                       Status;
    UINTN                            SdioCommunicateBufferSize;
    EFI_SMM_COMMUNICATION_PROTOCOL   *SmmCommunication;
    EFI_SMM_COMMUNICATE_HEADER       *CommHeader;
    UINT64                           SdioSwSmiSignature = SIGNATURE_64 ('S', 'D', 'E', 'F', 'I', 'N', 'F', 'Y');   
    UINT64                           LegacyBootNotifySignature = SIGNATURE_64 ('S', 'D', 'L', 'E', 'G', 'N', 'F', 'Y');    
   
    SdioCommunicateBufferSize  = sizeof(EFI_GUID) + sizeof(UINTN) + sizeof(SdioSwSmiSignature);        
    gBS->SetMem(gSdioCommunicateBuffer, SdioCommunicateBufferSize, 0);    
    // Get the SmmCommunication Protocol 
    Status = gBS->LocateProtocol (
                         &gEfiSmmCommunicationProtocolGuid,
                         NULL,
                         (VOID **)&SmmCommunication);
                      
    if (EFI_ERROR(Status)) {
       return;
    }
   
    CommHeader = (EFI_SMM_COMMUNICATE_HEADER *)gSdioCommunicateBuffer;    
    gBS->CopyMem (&CommHeader->HeaderGuid, &gAmiSdioCommunicationGuid, sizeof(gAmiSdioCommunicationGuid));
    
    if (Context != NULL && Context == &gEfiEventExitBootServicesGuid ) {
        // Copy the Signature to Identify to differentiate between different handlers 
        CommHeader->MessageLength = sizeof(SdioSwSmiSignature);    
        gBS->CopyMem (&(CommHeader->Data[0]), &SdioSwSmiSignature, sizeof(SdioSwSmiSignature));
    } else {
        // Copy the Signature to Identify to differentiate between different handlers 
        CommHeader->MessageLength = sizeof(LegacyBootNotifySignature);    
        gBS->CopyMem (&(CommHeader->Data[0]), &LegacyBootNotifySignature, sizeof(LegacyBootNotifySignature));
    }
       
    Status = SmmCommunication->Communicate (
                                   SmmCommunication,
                                   gSdioCommunicateBuffer,
                                   &SdioCommunicateBufferSize);
   
    ASSERT_EFI_ERROR(Status);
    
    gBS->CloseEvent (Event);
    
    return; 
}

/**
    Installs gSdioDriverBinding protocol

        
    @param ImageHandle - Image handle of this driver
    @param SystemTable -  Pointer to the EFI System Table

    @retval EFI_STATUS

    @note  
      Here is the control flow of this function:
      1. Initialize Ami Lib.
      2. Install Driver Binding Protocol
      3. Return EFI_SUCCESS.

**/

EFI_STATUS
EFIAPI
SdioDriverEntryPoint (
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
)

{
    EFI_STATUS  Status;
    EFI_EVENT   LegacyBootEvent;
    EFI_EVENT   ExitBootServicesEvent;
    VOID        *ExitBootServicesRegistration = &gEfiEventExitBootServicesGuid;
    
    gSdioDriverBinding.DriverBindingHandle = ImageHandle;
    gSdioDriverBinding.ImageHandle = ImageHandle;
        
    // Buffers Allocated for SMM Communication As new core doesn't allow Buffers which are allocated after EndofDXE.
    // Maximum Size of Buffer allocated for reuse
        gSdioCommunicateBufferSize  = sizeof(EFI_GUID) + sizeof(UINTN) + sizeof(SDIO_GLOBAL_DATA);
    //
    // Allocate Memory for Communication buffer.   
    //
    Status = gBS->AllocatePool ( 
                           EfiRuntimeServicesData,
                           gSdioCommunicateBufferSize,
                           (VOID**)&gSdioCommunicateBuffer );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = gBS->InstallMultipleProtocolInterfaces(
                                             &gSdioDriverBinding.DriverBindingHandle,
                                             &gEfiDriverBindingProtocolGuid,
                                             &gSdioDriverBinding,
                                             &gEfiComponentName2ProtocolGuid,
                                             &gSdioCtlDriverName,
                                             NULL);
                        
    ASSERT_EFI_ERROR(Status);
  
    // Register a legcay boot event for restricting
    // INT13 SMM calls before legacy boot event
    Status = gBS->CreateEventEx (
                           EVT_NOTIFY_SIGNAL,
                           TPL_CALLBACK,
                           LegacyBootNotify,
                           NULL,
                           &gEfiEventLegacyBootGuid,
                           &LegacyBootEvent);
    ASSERT_EFI_ERROR(Status);
    
    
    // Create EXIT_BOOT_SERIVES Event Callback function to pass signature in smm region 
    //to unregister the Sw Smi handler for Legacy
    Status = gBS->CreateEventEx (
                          EVT_NOTIFY_SIGNAL,
                          TPL_CALLBACK,
                          LegacyBootNotify,
                          ExitBootServicesRegistration,
                          &gEfiEventExitBootServicesGuid,
                          &ExitBootServicesEvent);
                      
    
    ASSERT_EFI_ERROR(Status);
    
    return Status;
}

/**@internal
 * 
    It returns the Driver name of this SDIO Driver(AMI SDIO Driver)
        
    @param  This       - Pointer to EFI_COMPONENT_NAME_PROTOCOL structure
    @param  Language   - A pointer to a three character ISO 639-2 language
                         identifier
    @param  DriverName - Pointer to Unicode string which is the controller name

         
    @retval EFI_SUCCESS returns driver name address
    @retval EFI_INVALID_PARAMETER If input parameter is not valid.
    @retval EFI_UNSUPPORTED If Language requested is not English.
   
   @endinternal
**/
EFI_STATUS
EFIAPI
SdioCtlDriverName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL    *This,
    IN  CHAR8                           *Language,
    OUT CHAR16                          **DriverName
)
{
    if (!Language || !DriverName) {
        return EFI_INVALID_PARAMETER;
    }
    //
    //Supports only English
    //
    if (AsciiStriCmp (Language, LANGUAGE_CODE_ENGLISH)) {
        return EFI_UNSUPPORTED;
    }

    *DriverName = gSdioBusDriverName;
    return EFI_SUCCESS;
}

/**@internal
 * 
    It returns the Device name of the SD/MMC card.
       
    @param  This                 - Pointer to EFI_COMPONENT_NAME_PROTOCOL structure
    @param  Controller           - Controller handle
    @param  ChildHandle OPTIONAL - Handle of child controller
    @param  Language             - A pointer to a three character ISO 639-2 language
                                   identifier
    @param  ControllerName       - Pointer to Unicode string which is the controller name

         
    @retval EFI_SUCCESS returns Device name address
    @retval EFI_INVALID_PARAMETER If input parameter is not valid.
    @retval EFI_UNSUPPORTED If Language requested is not English.

   @endinternal
**/
EFI_STATUS
EFIAPI
SdioCtlGetControllerName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL    *This,
    IN  EFI_HANDLE                      Controller,
    IN  EFI_HANDLE                      ChildHandle        OPTIONAL,
    IN  CHAR8                           *Language,
    OUT CHAR16                          **ControllerName
)
{

    EFI_STATUS              Status;
    AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface = NULL;
    SDIO_DEVICE_INTERFACE   *SdioDevInterface = NULL;
    LIST_ENTRY              *DLink = NULL;
    
    // Check if gSdioBusInitProtocolGuid is installed on the Controller Device.
    Status =  gBS->OpenProtocol ( 
                            Controller,
                            &gSdioBusInitProtocolGuid,
                            (VOID**)&SdioBusInterface,
                            gSdioDriverBinding.DriverBindingHandle,
                            Controller,
                            EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                                
    if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) {
        return EFI_UNSUPPORTED;
    }
    //
    //Supports only "eng"
    //
    if (!Language || !ControllerName) {
        return EFI_INVALID_PARAMETER;
    }

    if (AsciiStriCmp (Language, LANGUAGE_CODE_ENGLISH)) {
        return EFI_UNSUPPORTED;
    }

    if (ChildHandle == NULL) {
        *ControllerName = gSdioBusDriverName;
    } else {
        for (DLink = SdioBusInterface->SdioDeviceList.ForwardLink ; 
                      DLink != &SdioBusInterface->SdioDeviceList ; 
                      DLink = DLink->ForwardLink) {
           
            SdioDevInterface = BASE_CR (DLink, SDIO_DEVICE_INTERFACE, SdioDeviceLink);
            
            if (SdioDevInterface->SdioDeviceHandle == ChildHandle)
                break; 
             SdioDevInterface = NULL;
        }

         if (SdioDevInterface && (SdioDevInterface->DeviceState == DEVICE_CONFIGURED_SUCCESSFULLY)) {
             *ControllerName = SdioDevInterface->UnicodePNMString;
              return EFI_SUCCESS;
         }
    }
    return EFI_UNSUPPORTED;
}
/** @internal
    Checks whether the given Device path is having AMI_SD_EMMC_VENDOR_DEVICE_PATH
    node or not.

    @param DevicePath  - Input device path pointer.
    
    @retval  EFI_SUCCESS - If the device path contains AMI_EMMC_VENDOR_DEVICE_PATH node.
             EFI_NOT_FOUND - If AMI_EMMC_VENDOR_DEVICE_PATH node not present.

   @endinternal
**/
EFI_STATUS 
EFIAPI 
CheckForSdEmmcVendorDp(
  IN EFI_DEVICE_PATH_PROTOCOL           *DevicePath
)
{
    AMI_SD_EMMC_VENDOR_DEVICE_PATH     *AmiSdEmmcVendorDpNode = NULL;
    EFI_DEVICE_PATH_PROTOCOL           *TruncatedDevicePath = NULL;
    // Traverse to last node and check for AMI_SD_EMMC_VENDOR_DEVICE_PATH node.
    
    for ( ; !IsDevicePathEnd (DevicePath); DevicePath = NextDevicePathNode (DevicePath))
        TruncatedDevicePath = DevicePath;

    AmiSdEmmcVendorDpNode = (AMI_SD_EMMC_VENDOR_DEVICE_PATH *)TruncatedDevicePath;
    if ((AmiSdEmmcVendorDpNode != NULL) && (AmiSdEmmcVendorDpNode->VendorDevicePath.Header.SubType == HW_VENDOR_DP)) {
        if (CompareGuid (&(AmiSdEmmcVendorDpNode->VendorDevicePath.Guid), &gAmiSdEmmcVendorDevicePathGuid)) {
            return EFI_SUCCESS;
        }
    }
    return EFI_NOT_FOUND;
}

/**
    Checks whether the given controller is Block I/O or not

        
    @param This                - Pointer to Binding protocol instance
    @param Controller          - Controller handle
    @param RemainingDevicePath - Pointer to EFI_DEVICE_PATH_PROTOCOL structure

    @note  
  Here is the control flow of this function:
  1. Check whether PCI and Device path protocol has been installed on this controller
  2. Check if the controller is Block I/O controller
  3. If Block I/O Controller protocol already installed, return EFI_ALREADY_STARTED
  4. Return EFI_SUCCESS

**/

EFI_STATUS
EFIAPI
SdioDriverSupported (
    IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_HANDLE                   Controller,
    IN  EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
)
{
    EFI_STATUS                                Status;
    EFI_DEVICE_PATH_PROTOCOL                  *ParentDevicePath;
    EFI_PCI_IO_PROTOCOL                       *PciIo;
    AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *AmiSdEmmcControllerInitProtcol;
    PCI_TYPE00                                PciConfig;

    //
    // Check whether DevicePath Protocol has been installed on this 
    // controller
    //    
    Status = gBS->OpenProtocol (
                           Controller,
                           &gEfiDevicePathProtocolGuid,
                           (VOID **)&ParentDevicePath,
                           This->DriverBindingHandle,
                           Controller,
                           EFI_OPEN_PROTOCOL_BY_DRIVER);

    if (EFI_ERROR (Status)) {
        return Status;
    }

    gBS->CloseProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    This->DriverBindingHandle,
                    Controller);
    //
    // Check whether AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL has been installed on this 
    // controller
    //    
    Status = gBS->OpenProtocol (
                           Controller,
                           &gAmiSdEmmcControllerInitProtocolGuid,
                           (VOID **)&AmiSdEmmcControllerInitProtcol,
                           This->DriverBindingHandle,
                           Controller,
                           EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (!EFI_ERROR(Status)) {
        gBS->CloseProtocol (
                       Controller,
                       &gAmiSdEmmcControllerInitProtocolGuid,
                       This->DriverBindingHandle,
                       Controller);
        // Also check for SD EMMC Vendor Device path node
        if (!EFI_ERROR(CheckForSdEmmcVendorDp(ParentDevicePath))) {
            return EFI_SUCCESS;
        } else {
            return EFI_UNSUPPORTED;
        }
    }
    //
    //Check whether PCI Protocol has been installed on this controller
    //
    Status = gBS->OpenProtocol (
                         Controller,
                         &gEfiPciIoProtocolGuid,
                         (VOID **)&PciIo,
                         This->DriverBindingHandle,
                         Controller,
                         EFI_OPEN_PROTOCOL_BY_DRIVER);
    
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    gBS->CloseProtocol ( 
                  Controller,
                  &gEfiPciIoProtocolGuid,
                  This->DriverBindingHandle,
                  Controller);
    
    //
    // See if this is a PCI Mass Storage Controller by looking at the Class 
    // Code Register
    //
    Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint8,
                          0,
                          sizeof(PCI_TYPE00),
                          &PciConfig);
    
    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    if (IS_CLASS2 (&PciConfig, 
            PCI_CL_SYSTEM_PERIPHERALS,
            PCI_CL_SYSTEM_PERIPHERALS_SCL_SD)) {
        return EFI_SUCCESS;
    }

    return EFI_UNSUPPORTED;
}

/**
    Installs BlockIoProtocol

    @param  This                - Pointer to EFI_COMPONENT_NAME_PROTOCOL structure
    @param  Controller          - Controller handle
    @param  RemainingDevicePath - Pointer to the EFI_DEVICE_PATH_PROTOCOL structure

    @note  
      Here is the control flow of this function:
      1. Open PCI and Device path protocol
      2. Enable the device
      3. Post the option rom
      4. If first time, allocate buffer for real mode thunk code
      5. For each disk...
         a. Allocate and initialize a private structure
         b. Install block I/O protocol on a new child device
         c. Open the child device
      6. Increment user counter

**/

EFI_STATUS
EFIAPI
SdioDriverStart (
    IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN  EFI_HANDLE                   Controller,
    IN  EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
)

{
    EFI_STATUS                                Status;
    EFI_PCI_IO_PROTOCOL                       *PciIo = NULL;
    EFI_DEVICE_PATH_PROTOCOL                  *ParentDevPath = NULL;
    UINTN                                     Pages = 0;
    EFI_PHYSICAL_ADDRESS                      AdmaDescriptorAdd = 0;
    AMI_SDIO_BUS_PROTOCOL                     *SdioBusInterface;
    UINT64                                    Attributes; 
    UINTN                                     Seg;
    UINTN                                     Bus;
    UINTN                                     Dev;
    UINTN                                     Func;
    UINTN                                     Index;
    AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL      *AmiSdEmmcControllerInitProtocol = NULL;
    SD_MMC_PASS_THRU_PROTOCOL                 *SdMmcPassthruInstance = NULL;
    EFI_SD_MMC_PASS_THRU_PROTOCOL             *EfiSdMmcPassThru = NULL;    
    UINT64                                    MappedBaseAddr = 0;
    void                                      *UnMappedAddress = NULL;
    UINTN                                     TempMemSize;
    
    //  Open Device Path Protocol
    Status = gBS->OpenProtocol (
                           Controller,
                           &gEfiDevicePathProtocolGuid,
                           (VOID **)&ParentDevPath,
                           This->DriverBindingHandle,
                           Controller,
                           EFI_OPEN_PROTOCOL_BY_DRIVER);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //Open PCI I/O Protocol BY_DRIVER
    Status = gBS->OpenProtocol ( 
                          Controller,
                          &gEfiPciIoProtocolGuid,
                          (VOID **)&PciIo,
                          This->DriverBindingHandle,
                          Controller,
                          EFI_OPEN_PROTOCOL_BY_DRIVER);
    // Open protocol returns EFI_UNSUPPORTED if PCI I/O Protocol not present
    // on Controller handle.So try to open AMI_SD_EMMC_CONTROLLER_INIT_PROTCOL BY_DRIVER.
    if (Status == EFI_UNSUPPORTED) {
        Status = gBS->OpenProtocol (
                               Controller,
                               &gAmiSdEmmcControllerInitProtocolGuid,
                               (VOID **)&AmiSdEmmcControllerInitProtocol,
                               This->DriverBindingHandle,
                               Controller,
                               EFI_OPEN_PROTOCOL_BY_DRIVER);
    }
    if (EFI_ERROR(Status)) {
        gBS->CloseProtocol (
                       Controller,
                       &gEfiDevicePathProtocolGuid,
                       This->DriverBindingHandle,
                       Controller);
        return Status;
    }

    Status = gBS->OpenProtocol (
                          Controller,
                          &gSdioBusInitProtocolGuid,
                          (VOID **)&SdioBusInterface,
                          This->DriverBindingHandle,
                          Controller,
                          EFI_OPEN_PROTOCOL_BY_DRIVER);


    if (!(Status == EFI_SUCCESS || Status == EFI_ALREADY_STARTED)) {

        Status = gBS->AllocatePool (
                              EfiBootServicesData,
                              sizeof(AMI_SDIO_BUS_PROTOCOL),
                              (VOID**)&SdioBusInterface);
        if (EFI_ERROR(Status)) { 
            return EFI_OUT_OF_RESOURCES;
        }
        Status = InstallSdioBusProtocol (
                                   Controller, 
                                   SdioBusInterface,
                                   (PciIo != NULL) ? (VOID*)PciIo :(VOID*)AmiSdEmmcControllerInitProtocol,
                                   (PciIo != NULL) ? PciIoType : NonPciIoType);
        
        if (EFI_ERROR(Status)) {
            
            gBS->CloseProtocol (
                           Controller,
                           &gEfiPciIoProtocolGuid,
                           This->DriverBindingHandle,
                           Controller);
            gBS->FreePool (SdioBusInterface);
            
            return Status;
        }
    }
    //
    // For Allocating Page (4KB of Memory) for ADMA descriptor
    //
    Pages = EFI_SIZE_TO_PAGES(SDIO_SIZE);
    if (SdioBusInterface->ControllerType == PciIoType ) {
        // Enable the Device
        Status = PciIo->Attributes ( 
                               PciIo,
                               EfiPciIoAttributeOperationSupported,
                               0,
                               &Attributes);
        if (EFI_ERROR(Status)) {
            goto ErrorPath;
        }
    
        Status = PciIo->Attributes ( 
                                PciIo,
                                EfiPciIoAttributeOperationEnable,
                                Attributes & EFI_PCI_DEVICE_ENABLE,
                                NULL);
        if (EFI_ERROR(Status)) {
            goto ErrorPath;
        }
    
        Status = PciIo->GetLocation (
                                 PciIo,
                                 &Seg,
                                 &Bus,
                                 &Dev,
                                 &Func);
        if (EFI_ERROR(Status)) {
            goto ErrorPath;
        } 
   
#if SDMMC_VERBOSE_PRINT    
        DEBUG((EFI_D_VERBOSE,"SdMmc: Controller Bus = %x Dev = %x Func = %x\n", Bus, Dev, Func));
#endif   
    
        //
        // Allocating Page (4KB of Memory) for ADMA descriptor
        //
        Status = PciIo->AllocateBuffer (
                                     PciIo,
                                     AllocateMaxAddress,
                                     EfiRuntimeServicesData,
                                     Pages,
                                     (VOID*)&AdmaDescriptorAdd,
                                     EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE);
        ASSERT_EFI_ERROR (Status);
        if (EFI_ERROR(Status)) {
            goto ErrorPath;
        }
        
        TempMemSize = EFI_PAGES_TO_SIZE(Pages);
        Status = PciIo->Map (
                         PciIo, 
                         EfiPciIoOperationBusMasterCommonBuffer,
                         (VOID *)AdmaDescriptorAdd,
                         &TempMemSize,
                         (EFI_PHYSICAL_ADDRESS *)&MappedBaseAddr,
                         &UnMappedAddress);
                              
        
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            goto ErrorPath;
        }                  
        else {
            AdmaDescriptorAdd = MappedBaseAddr;
        }
        
        SdioBusInterface->AdmaDescriptorAddressUnMap = UnMappedAddress;
        
    } else {
        
        //
        // Allocating Page (4KB of Memory) for ADMA descriptor
        //
        Status = gBS->AllocatePages (
                                AllocateAnyPages,
                                EfiRuntimeServicesData,
                                Pages,
                                (EFI_PHYSICAL_ADDRESS*)&(AdmaDescriptorAdd));
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) {
            goto ErrorPath;
        }
    }    
    SdioBusInterface->AdmaDescriptorAddress = (UINT64)AdmaDescriptorAdd;
    
    if (gSdioData == NULL ) {
        Status = gBS->AllocatePool (
                              EfiBootServicesData,
                              sizeof(SDIO_GLOBAL_DATA),
                              (VOID**)&gSdioData);
        if (EFI_ERROR(Status)) {
            goto ErrorPath;
        }
        //
        //  Clear the Buffer
        //
        gBS->SetMem ((VOID*)gSdioData, sizeof(SDIO_GLOBAL_DATA), 0);
        gBS->InstallProtocolInterface (
                                  &gSdioDataHandle,
                                  &SdioRuntimeDataGuid,
                                  EFI_NATIVE_INTERFACE,
                                  gSdioData);
                                  
        
        //
        // Get the SDIO access mode from Setup.
        //
        InitilizeSdioSetupConfiguration ( );
    }
    
    gCounterSdioEnumTimer++;

    // Detecting device before initializing timer
    SdioHotPlugTimer (NULL, NULL);
    
    // Tranfer the SDIO data to SMM driver for Legacy operation
    TransferSdioDataToSmram ( );
        
    // Installing EfiSdMmcPassThru protocol
    Status = gBS->OpenProtocol (
                          Controller,
                          &gEfiSdMmcPassThruProtocolGuid,
                          (VOID **)&EfiSdMmcPassThru,
                          This->DriverBindingHandle,
                          Controller,
                          EFI_OPEN_PROTOCOL_GET_PROTOCOL);
 
    if (EFI_ERROR(Status)) {
        // Allocate memory for SD_MMC_PASS_THRU_INSTANCE structure
        Status = gBS->AllocatePool (
                           EfiBootServicesData,
                           sizeof(SD_MMC_PASS_THRU_PROTOCOL),
                           (VOID**)&SdMmcPassthruInstance);
        
        if (!EFI_ERROR(Status)) {
            EfiSdMmcPassThru = (EFI_SD_MMC_PASS_THRU_PROTOCOL*)&(SdMmcPassthruInstance->EfiSdMmcPassThruProtocol);

            EfiSdMmcPassThru->IoAlign = 0;     // By default considering PIO mode
            EfiSdMmcPassThru->PassThru = PassThru;
            EfiSdMmcPassThru->GetNextSlot = GetNextSlot;
            EfiSdMmcPassThru->BuildDevicePath = BuildDevicePath;
            EfiSdMmcPassThru->GetSlotNumber = GetSlotNumber;
            EfiSdMmcPassThru->ResetDevice = ResetDevice;
            SdMmcPassthruInstance->PreviousSlot = 0xFF;
            SdMmcPassthruInstance->SdioBusInterface = SdioBusInterface;

            Status = gBS->InstallProtocolInterface (
                                             &Controller,
                                             &gEfiSdMmcPassThruProtocolGuid,
                                             EFI_NATIVE_INTERFACE,
                                             &(SdMmcPassthruInstance->EfiSdMmcPassThruProtocol)); 
            if (EFI_ERROR(Status)) {
                gBS->FreePool (SdMmcPassthruInstance);
                goto ErrorPath;
            }
        }
    }
   
#if (defined(BOOT_SECTOR_WRITE_PROTECT) && (BOOT_SECTOR_WRITE_PROTECT != 0))
    if (!EFI_ERROR(Status) && AmiBlkWriteProtection == NULL) {
        Status = gBS->LocateProtocol (
                               &gAmiBlockIoWriteProtectionProtocolGuid, 
                               NULL, 
                               &AmiBlkWriteProtection); 
        if (EFI_ERROR(Status)) {
            AmiBlkWriteProtection = NULL;
        }
    }
#endif    
    
    if (gEvSdioEnumTimer == NULL) {
    
        for (Index = 0; Index < SdioBusInterface->NumberOfSlotsImplemented; Index++ ){            
            // Initializing the timer event only for removable card slot 
            if (!(*(volatile UINT32 *)(SdioBusInterface->SdioBaseAddress[Index] + 0x40) & (BIT30 |BIT31))) {
                // Creating global timer for monitoring the device status
                Status = gBS->CreateEvent (
                                     EVT_TIMER | EVT_NOTIFY_SIGNAL,
                                     TPL_CALLBACK,
                                     SdioHotPlugTimer,
                                     0,
                                     &gEvSdioEnumTimer);
                ASSERT_EFI_ERROR(Status);
              
                break;
            }
        }
    }
   
    if (gEvSdioEnumTimer != NULL) {  
        Status = gBS->SetTimer (gEvSdioEnumTimer, TimerPeriodic, ONESECOND / 10);
        ASSERT_EFI_ERROR(Status);
    }   
    
    return EFI_SUCCESS;
    
ErrorPath:
    if (AdmaDescriptorAdd) {
        if (PciIo != NULL) {
            PciIo->FreeBuffer (
                          PciIo,
                          Pages,
                          (VOID *)AdmaDescriptorAdd);
            
            PciIo->Unmap (PciIo, (VOID *)SdioBusInterface->AdmaDescriptorAddressUnMap);
            SdioBusInterface->AdmaDescriptorAddressUnMap = NULL;
            
        } else {
            gBS->FreePages (
                       AdmaDescriptorAdd,
                       EFI_SIZE_TO_PAGES (SDIO_SIZE));
        }
    }
    gBS->CloseProtocol (
                   Controller,
                   (PciIo != NULL) ? &gEfiPciIoProtocolGuid : &gAmiSdEmmcControllerInitProtocolGuid,
                   This->DriverBindingHandle,
                   Controller);
    
    gBS->CloseProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  This->DriverBindingHandle,
                  Controller);
    
    if (gEvSdioEnumTimer != NULL) {  
        gBS->SetTimer (gEvSdioEnumTimer, TimerPeriodic, ONESECOND / 10);
    }  
    
    return Status;
}

/**
    Disconnect the Controller

    @param  This              - Pointer to EFI_COMPONENT_NAME_PROTOCOL structure
    @param  Controller        - Controller handle
    @param  NumberOfChildren  - Number of child devices
    @param  ChildHandleBuffer - Buffer holding child devices

    @note  
  Here is the control flow of this function:
  1. Decrement user counter
  2. Free global buffer
  3. Release PCI I/O protocol and Block I/O protocol for each child handle.
  4. Shut down the hardware for each child handle.

**/
EFI_STATUS
EFIAPI
SdioDriverStop (
    IN  EFI_DRIVER_BINDING_PROTOCOL *This,
    IN  EFI_HANDLE                  Controller,
    IN  UINTN                       NumberOfChildren,
    IN  EFI_HANDLE                  *ChildHandleBuffer
)

{
    AMI_SDIO_BUS_PROTOCOL          *SdioBusInterface;
    SDIO_DEVICE_INTERFACE          *SdioDeviceInterface;
    EFI_STATUS                     Status;
    UINT8                          Index;
    UINT8                          Slot = 0;
    EFI_PCI_IO_PROTOCOL            *PciIo = NULL;
    EFI_DEVICE_PATH_PROTOCOL       *DevPath;
    UINT64                         Attributes = 0;
 
    EFI_SD_MMC_PASS_THRU_PROTOCOL  *EfiSdMmcPassThru;
    SD_MMC_PASS_THRU_PROTOCOL      *SdMmcPassthruInstance = NULL;


    // Check if SDIO_BUS_PROTOCOL is installed on the Controller.
    Status = gBS->OpenProtocol ( 
                           Controller,
                           &gSdioBusInitProtocolGuid,
                           (VOID **)&SdioBusInterface,
                           This->DriverBindingHandle,
                           Controller,
                           EFI_OPEN_PROTOCOL_GET_PROTOCOL);

    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
   
    //
    // Check if ChildHandleBuffer is valid
    //
    if (NumberOfChildren) {
        for (Index = 0; Index < NumberOfChildren; Index++) {
            Status = gBS->CloseProtocol (
                                   Controller,
                                   (SdioBusInterface->ControllerType == PciIoType) ? &gEfiPciIoProtocolGuid : &gAmiSdEmmcControllerInitProtocolGuid,
                                   This->DriverBindingHandle,
                                   ChildHandleBuffer[Index]);
            if (EFI_ERROR(Status)) {
                ASSERT_EFI_ERROR(Status);
                continue;
            }
            Status = gBS->OpenProtocol (
                                   ChildHandleBuffer[Index],
                                   &gEfiDevicePathProtocolGuid,
                                   (VOID **)&DevPath,
                                   This->DriverBindingHandle,     
                                   Controller,
                                   EFI_OPEN_PROTOCOL_GET_PROTOCOL);
            ASSERT_EFI_ERROR(Status);
           
            //
            // Retrieve the Slot number from the device path.
            //
            while (!IsDevicePathEnd ((VOID *)DevPath)) {
               if (DevPath->Type == MESSAGING_DEVICE_PATH) {
                                                      
                   if (DevPath->SubType == MSG_SDIO_DP) {
                       Slot = ((SDIO_DEVICE_PATH *)DevPath)->SlotNumber;
                       break;                          
                   } else if (DevPath->SubType == MSG_EMMC_DP) {
                       Slot = ((EMMC_DEVICE_PATH *)DevPath)->SlotNumber;
                       break;                         
                   }
               } 
               DevPath = NextDevicePathNode (DevPath);
            }
            
            if (IsDevicePathEnd ((VOID *)DevPath)) {

                // Unable to find the Messaging device path node.
                ASSERT(FALSE);  
                return EFI_DEVICE_ERROR;
            }
        
            SdioDeviceInterface = GetSdioDevInterface (SdioBusInterface, Slot);
            if (!SdioDeviceInterface) {
                return EFI_DEVICE_ERROR;
            }
        
            //
            // Before uninstalling BLOCKIO check whether it is installed or not
            //
            Status = gBS->OpenProtocol (
                                   ChildHandleBuffer[Index],
                                   &gEfiBlockIoProtocolGuid,
                                   NULL,
                                   This->DriverBindingHandle,
                                   ChildHandleBuffer[Index],
                                   EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
            
            if (!EFI_ERROR(Status)) {
                
                Status = gBS->UninstallProtocolInterface (
                                                  ChildHandleBuffer[Index],
                                                  &gEfiBlockIoProtocolGuid, 
                                                  (EFI_BLOCK_IO_PROTOCOL *)(SdioDeviceInterface->SdioBlkIo));
                            
                ASSERT_EFI_ERROR(Status);
                gBS->FreePool (SdioDeviceInterface->SdioBlkIo->BlkIo.Media);
                gBS->FreePool (SdioDeviceInterface->SdioBlkIo);
            
            }              
            Status = gBS->OpenProtocol (
                                  ChildHandleBuffer[Index],
                                  &gEfiEraseBlockProtocolGuid,
                                  NULL,
                                  This->DriverBindingHandle,
                                  ChildHandleBuffer[Index],
                                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
            
            if (!EFI_ERROR(Status)) {
                
                Status = gBS->UninstallProtocolInterface (
                                                   ChildHandleBuffer[Index],
                                                   &gEfiEraseBlockProtocolGuid, 
                                                   (EFI_BLOCK_IO_PROTOCOL *)(SdioDeviceInterface->SdioBlkErase));
                            
                ASSERT_EFI_ERROR(Status);
                gBS->FreePool (SdioDeviceInterface->SdioBlkErase);
            
            }
       
            Status = gBS->UninstallProtocolInterface (
                                                ChildHandleBuffer[Index],
                                                &gEfiDevicePathProtocolGuid,
                                                SdioDeviceInterface->DevicePathProtocol);
            ASSERT_EFI_ERROR(Status);
            gBS->FreePool (SdioDeviceInterface->DevicePathProtocol);
            RemoveEntryList (&SdioDeviceInterface->SdioDeviceLink);
            gBS->FreePool (SdioDeviceInterface);
        
        } // for loop    
    } else {
        if (SdioBusInterface->ControllerType == PciIoType) {
            PciIo = (EFI_PCI_IO_PROTOCOL*)SdioBusInterface->ControllerInterface;
            //
            //Close all the protocols opened in Start Function
            //
            Status = PciIo->Attributes (
                                    PciIo,
                                    EfiPciIoAttributeOperationSupported,
                                    0,
                                    &Attributes);
            ASSERT_EFI_ERROR(Status);
        
            Status = PciIo->Attributes (
                                     PciIo,
                                     EfiPciIoAttributeOperationDisable,
                                     Attributes & EFI_PCI_DEVICE_ENABLE,
                                     NULL);
            ASSERT_EFI_ERROR(Status);
            Status = gBS->CloseProtocol (
                                    Controller,
                                    &gEfiPciIoProtocolGuid,
                                    This->DriverBindingHandle,
                                    Controller);
            ASSERT_EFI_ERROR(Status);
            
        } else if (SdioBusInterface->ControllerType == NonPciIoType) {
            Status = gBS->CloseProtocol ( 
                                     Controller,
                                     &gAmiSdEmmcControllerInitProtocolGuid,
                                     This->DriverBindingHandle,
                                     Controller);
            ASSERT_EFI_ERROR(Status);
        }
        
        Status = gBS->CloseProtocol (
                                Controller,
                                &gSdioBusInitProtocolGuid,
                                This->DriverBindingHandle,
                                Controller);
        ASSERT_EFI_ERROR(Status);							
        Status = gBS->CloseProtocol (
                               Controller,
                               &gEfiDevicePathProtocolGuid,
                               This->DriverBindingHandle,
                               Controller);
        ASSERT_EFI_ERROR(Status);
              
        Status = gBS->OpenProtocol ( 
                           Controller,
                           &gEfiSdMmcPassThruProtocolGuid,
                           (VOID **)&EfiSdMmcPassThru,
                           This->DriverBindingHandle,
                           Controller,   
                           EFI_OPEN_PROTOCOL_GET_PROTOCOL
                           );
        if (!EFI_ERROR(Status)) {
            //  Uninstall SdMmcPassThru Protocol for the controller.
            Status = gBS->UninstallMultipleProtocolInterfaces (
                                                        Controller,
                                                        &gEfiSdMmcPassThruProtocolGuid,
                                                        &(SdMmcPassthruInstance->EfiSdMmcPassThruProtocol),
                                                        NULL);
                             
    
            if (Status == EFI_SUCCESS) {
                gBS->FreePool (SdMmcPassthruInstance);
            }
        }
        // Free the Pages allocated for AdmaDescriptorAddress 
        if (SdioBusInterface->AdmaDescriptorAddress && (SdioBusInterface->AdmaDescriptorAddressUnMap != NULL)) {
            if (PciIo!= NULL) {
                PciIo->FreeBuffer (
                                PciIo,
                                EFI_SIZE_TO_PAGES (SDIO_SIZE),
                               (VOID *)SdioBusInterface->AdmaDescriptorAddress);
                
                PciIo->Unmap (PciIo, (VOID *)SdioBusInterface->AdmaDescriptorAddressUnMap);
                
            } else {
                gBS->FreePages (
                           SdioBusInterface->AdmaDescriptorAddress,
                           EFI_SIZE_TO_PAGES (SDIO_SIZE));
            }
        }
         
        if (--gCounterSdioEnumTimer == 0) {
          
            if (gEvSdioEnumTimer != NULL) {
                Status = gBS->SetTimer (gEvSdioEnumTimer, TimerCancel, ONESECOND / 10);
                ASSERT_EFI_ERROR(Status);
                // Kill the Event
                Status = gBS->CloseEvent (gEvSdioEnumTimer);
                ASSERT_EFI_ERROR(Status);
                gEvSdioEnumTimer = NULL;
            }	
            
            gCounterSdioEnumTimer = 0;
            
            if (gSdioData!= NULL) {
            
                Status = gBS->UninstallProtocolInterface ( 
                                                 gSdioDataHandle,
                                                 &SdioRuntimeDataGuid,
                                                 gSdioData);
                ASSERT_EFI_ERROR(Status);
                 gSdioDataHandle = NULL;
                 
                gBS->FreePool (gSdioData);
                gSdioData = NULL;
            }
        }
        
        Status = gBS->UninstallProtocolInterface ( 
                                             Controller,
                                             &gSdioBusInitProtocolGuid,
                                             SdioBusInterface);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        gBS->FreePool (SdioBusInterface);
    }
    return EFI_SUCCESS;
}

/**@internal
 * 
    Installs BUS Init Protocol on the IDE controller Handle
        
    @param  Controller          - Controller handle
    @param  SdioBusInterface    - Pointer to the AMI_SDIO_BUS_PROTOCOL structure
    @param  ControllerInterface - Controller interface
    @param  ControllerType      - Controller type

    @retval EFI_STATUS

    @note  
       1. Call SdioInitController
       2. Install gSdioBusInitProtocolGuid protocol

    @endinternal
**/

EFI_STATUS
InstallSdioBusProtocol (
    IN  EFI_HANDLE                  Controller,
    IN  OUT AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface,
    IN  VOID                        *ControllerInterface,
    IN  AMI_SD_EMMC_CONTROLLER_TYPE ControllerType
)
{
    EFI_STATUS  Status;

    // Initialize the default Values
    ZeroMemory (SdioBusInterface, sizeof(AMI_SDIO_BUS_PROTOCOL));

    SdioBusInterface->ControllerHandle = Controller;
    SdioBusInterface->ControllerInterface = ControllerInterface;
    SdioBusInterface->ControllerType = ControllerType;
    InitializeListHead (&SdioBusInterface->SdioDeviceList);

    // Init Sdio Controller
    Status = SdioInitController (SdioBusInterface);
    if (EFI_ERROR(Status)) { 
        return Status;
    }
    
    // As SdioHotPlugTimer() event function locates gSdioBusInitProtocolGuid handles.
    // So,Cancel the gEvSdioEnumTimer(Hot plug) event triggered by previous Host Controller
    // before installing gSdioBusInitProtocolGuid. 
    if (gEvSdioEnumTimer != NULL) {
        Status = gBS->SetTimer (gEvSdioEnumTimer, TimerCancel, ONESECOND / 10);
        ASSERT_EFI_ERROR(Status);
    }

    Status = gBS->InstallProtocolInterface (
                                    &Controller,
                                    &gSdioBusInitProtocolGuid,
                                    EFI_NATIVE_INTERFACE,
                                    SdioBusInterface);

    return Status;

}

/**@internal
 * 
    Initializes Sdio Controller

    @param  SdioBusInterface - Pointer to AMI_SDIO_BUS_PROTOCOL structure

    @retval EFI_STATUS

    @note  
      1. Update internal Data area about the Sdio controller Capabilities.
      2. Allocate memory for FIS and CommandList
      3. Enable Sdio mode
      3. Disable all the ports

   @endinternal
**/

EFI_STATUS
SdioInitController (
    IN  OUT AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface
)
{
    EFI_STATUS                               Status;
    UINT8                                    PciConfig[41];
    UINT8                                    BarOffset;
    UINT8                                    BarType;
    UINT8                                    BarSize = 4;
    UINT64                                   BarAnd;
    UINT8                                    SlotNo;
    EFI_PCI_IO_PROTOCOL                      *PciIo = NULL;
    AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL     *AmiSdEmmcControllerInitProtocol = NULL;
    
    if (SdioBusInterface->ControllerType == PciIoType) {
        PciIo = (EFI_PCI_IO_PROTOCOL*)SdioBusInterface->ControllerInterface;
        // Make sure SDIO Base address is programmed Properly
        Status = PciIo->Pci.Read (
                              PciIo,
                              EfiPciIoWidthUint8,
                              0,
                              sizeof (PciConfig),
                              PciConfig);

        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        //
        // Calculate the Base address for the first port asper Section C.3.3 
        // Slot Information Register (Offset 40h). The PCI BAR may not always 
        // start at 10h First Base Address Register Number bits will provide 
        // the BAR for firt slot.
        //
        BarOffset = PCI_BASE_ADDRESSREG_OFFSET + (PciConfig[40] & 0x07) *4;
        //
        // Slot Information Register's Bit 6-4 will provide the number of slots 
        // present in the controller. 
        //
        SdioBusInterface->NumberOfSlotsImplemented = ((PciConfig[40] & 0x70) >> 4)+1;
        BarType = (*(UINT8 *)(PciConfig + BarOffset))& (BAR_64_32_SUPPORT_BIT);
        
        //
        // The lower nible of the Bar address is cleared. If the Bar support 
        // 64 Bit then the Bar address is 8 bytes else 4 bytes
        //
        if (BarType == BAR_64_BIT) {
            BarAnd = 0xFFFFFFFFFFFFFFF0;
            BarSize = 8;
        } else {
            BarAnd = 0xFFFFFFF0;
            BarSize = 4;
        }

        for (SlotNo = 0; SlotNo < (SdioBusInterface->NumberOfSlotsImplemented); SlotNo++ ) {
            SdioBusInterface->SdioBaseAddress[SlotNo] = ((*(UINT64 *)(PciConfig + BarOffset + (SlotNo*BarSize))) & BarAnd);
            if (!SdioBusInterface->SdioBaseAddress[SlotNo]) { 
                ASSERT_EFI_ERROR(Status);
                return EFI_DEVICE_ERROR;
            }
        }
    }
    
    if (SdioBusInterface->ControllerType == NonPciIoType) {
        AmiSdEmmcControllerInitProtocol = (AMI_SD_EMMC_CONTROLLER_INIT_PROTOCOL*)SdioBusInterface->ControllerInterface;
        Status = AmiSdEmmcControllerInitProtocol->GetNumberOfSlots (AmiSdEmmcControllerInitProtocol, &SdioBusInterface->NumberOfSlotsImplemented);
        if (EFI_ERROR(Status) || !SdioBusInterface->NumberOfSlotsImplemented) {
            return EFI_DEVICE_ERROR;
        }
        for (SlotNo = 0; SlotNo < (SdioBusInterface->NumberOfSlotsImplemented); SlotNo++ ) {
            Status = AmiSdEmmcControllerInitProtocol->GetSlotBaseAddress (
                                                                  AmiSdEmmcControllerInitProtocol,\
                                                                  SlotNo,\
                                                                  &SdioBusInterface->SdioBaseAddress[SlotNo]);
            if (EFI_ERROR(Status)|| !SdioBusInterface->SdioBaseAddress[SlotNo]) { 
                ASSERT_EFI_ERROR(Status);
                return EFI_DEVICE_ERROR;
            }
        }
    }
    return EFI_SUCCESS;
}

/**@internal
       
    @param  SdioBusInterface - Pointer to AMI_SDIO_BUS_PROTOCOL structure
    @param  Port 	         - Sdio port number
 
    @retval Sdio_DEVICE_INTERFACE*

    @note  
      1. Return the Pointer to the Sdio_DEVICE_INTERFACE for the given Port and PM Port

   @endinternal
**/
SDIO_DEVICE_INTERFACE *
GetSdioDevInterface (
    IN  AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface,
    IN  UINT8                   Slot
)
{

    LIST_ENTRY              *DLink;
    SDIO_DEVICE_INTERFACE   *SdioDevInterface = NULL;
    
    for(DLink = SdioBusInterface->SdioDeviceList.ForwardLink;
           DLink != &SdioBusInterface->SdioDeviceList;
           DLink = DLink->ForwardLink ) {
        
        SdioDevInterface = BASE_CR(DLink,SDIO_DEVICE_INTERFACE,SdioDeviceLink);
      
        if (SdioDevInterface->SlotNumber == Slot)
            break;
        SdioDevInterface = NULL;
    }
    return SdioDevInterface;
}

/**@internal
 * 
    Detects and Configures Sdio Device

    @param  This                - Pointer to EFI_COMPONENT_NAME_PROTOCOL structure            
    @param  Controller          - Controller handle
    @param  RemainingDevicePath - Pointer to EFI_DEVICE_PATH_PROTOCOL structure
    @param  SdioBusInterface    - Pointer to AMI_SDIO_BUS_PROTOCOL structure
    @param  Slot                - Sdio slot number

    @retval EFI_STATUS

    @note  
 1. Detect whether device is connected to the port. If no device exit.
 2. Install SdioDevInterface. 
 3. Configure the Sdio device and the controller.
 4. Install DevicePath, BlockIO and DiskInfo protocol.

   @endinternal
**/
EFI_STATUS
DetectAndConfigureDevice (
    IN  EFI_DRIVER_BINDING_PROTOCOL *This,
    IN  EFI_HANDLE                  Controller,
    IN  EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath,
    IN  AMI_SDIO_BUS_PROTOCOL       *SdioBusInterface,
    IN  UINT8                       Slot
)
{

    EFI_STATUS              Status;
    SDIO_DEVICE_INTERFACE   *SdioDevInterface = NULL;
    UINT8                   Index;
    VOID                    *ControllerInterface=NULL;
    
    // Check the Slot already detected 
    SdioDevInterface = GetSdioDevInterface (SdioBusInterface, Slot);
    if (SdioDevInterface && ((SdioDevInterface->DeviceState == DEVICE_DETECTION_FAILED)||
        (SdioDevInterface->DeviceState == DEVICE_CONFIGURED_SUCCESSFULLY))){
        return EFI_SUCCESS;
    }

    Status = SdioDetectDeviceAndConfigure (SdioBusInterface, Slot);
    SdioDevInterface = GetSdioDevInterface (SdioBusInterface, Slot);
    if (EFI_ERROR(Status) || (!SdioDevInterface)) {
        if (SdioDevInterface) { 
            SdioDevInterface->DeviceState = DEVICE_DETECTION_FAILED;
        }
        return EFI_DEVICE_ERROR;
    }
    SdioDevInterface->DeviceState = DEVICE_CONFIGURED_SUCCESSFULLY;
    
    // Create the Device path
    Status = CreateSdioDevicePath (This, Controller, SdioDevInterface, RemainingDevicePath);
    if (EFI_ERROR(Status)) { 
        ASSERT_EFI_ERROR(Status);
        return EFI_DEVICE_ERROR;
    }

    // Install Device path on the new handle
    Status = gBS->InstallMultipleProtocolInterfaces (
                                        &(SdioDevInterface->SdioDeviceHandle),
                                        &gEfiDevicePathProtocolGuid,
                                        SdioDevInterface->DevicePathProtocol,
                                        NULL);
    if (EFI_ERROR(Status)) {
        SdioDevInterface->DeviceState = DEVICE_DETECTION_FAILED;
        return EFI_DEVICE_ERROR;
    }
    
    //
    // Open the Pci EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER attribute.
    //
    Status = gBS->OpenProtocol (
                          Controller,
                          (SdioBusInterface->ControllerType == PciIoType) ? &gEfiPciIoProtocolGuid : &gAmiSdEmmcControllerInitProtocolGuid,
                          (VOID**)&ControllerInterface,
                           This->DriverBindingHandle,
                           SdioDevInterface->SdioDeviceHandle,
                           EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    if (!SdioDevInterface->MassStorageDevice) {
        //
        // The detected Device is not a Mass Storage device.
        //
        return EFI_SUCCESS;
    }

    //
    // Convert the PNM string into Unicode String and store it. 
    //
    for (Index = 0; Index < 27; Index++) {
       SdioDevInterface->UnicodePNMString[Index] = (CHAR16)SdioDevInterface->SdioDevInfo->PNM[Index];
    }
    
    //
    // The detected device is Mass storage device. So initialize the Block IO and Legacy Int13
    // Functions for the SDIO device.
    //
    Status = InitSdioBlockIO (SdioDevInterface);
    if (EFI_ERROR(Status)) { 
        return EFI_DEVICE_ERROR; 
    }    
    Status = InitSdioBlockErase (SdioDevInterface);
    if (EFI_ERROR(Status)) { 
        return EFI_DEVICE_ERROR; 
    }
    Status = gBS->InstallMultipleProtocolInterfaces (
                                            &(SdioDevInterface->SdioDeviceHandle),
                                            &gEfiBlockIoProtocolGuid,
                                            (EFI_BLOCK_IO_PROTOCOL *)(SdioDevInterface->SdioBlkIo), 
                                            &gEfiEraseBlockProtocolGuid,
                                            (EFI_ERASE_BLOCK_PROTOCOL *)(SdioDevInterface->SdioBlkErase),
                                            NULL);
    if (EFI_ERROR(Status)) { 
        return EFI_DEVICE_ERROR; 
    }
    
    // Only for Removable media calling Connect Controller,
    // to support Hot-Plug feature.
    if (SdioDevInterface->SdioBlkIo->BlkIo.Media->RemovableMedia) {
        
    // Connect controller to start device drivers
    gBS->ConnectController (
                    SdioDevInterface->SdioDeviceHandle,
                    NULL,
                    NULL,
                    TRUE);
    }
    
    return EFI_SUCCESS;
}

/**@internal
 * 
    Detects a Sdio device connected to given Port and PMPort

    @param  SdioBusInterface - Pointer to AMI_SDIO_BUS_PROTOCOL structure
    @param  Port             - Sdio port number

    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
SdioDetectDeviceAndConfigure (
    IN  AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface,
    IN  UINT8                   Slot
)
{

    EFI_STATUS              Status;
    SDIO_DEVICE_INTERFACE   *SdioDevInterface = NULL;
    UINT64                  MappedBaseAddr = 0;
    void                    *UnMappedAddress = NULL;
    UINTN                   TempMemSize;
    EFI_PHYSICAL_ADDRESS    BufferAddress;
    EFI_PCI_IO_PROTOCOL     *PciIo = NULL;
    
    SdioDevInterface = GetSdioDevInterface (SdioBusInterface, Slot);

    if (!SdioDevInterface) {
        //
        // Entry not Present, Create New entry for the Slot 
        //
        Status = gBS->AllocatePool (
                             EfiBootServicesData,
                             sizeof(SDIO_DEVICE_INTERFACE),
                             (VOID**)&SdioDevInterface);
                    
        if (EFI_ERROR(Status))
            return Status;

        ZeroMemory (SdioDevInterface, sizeof(SDIO_DEVICE_INTERFACE));

        SdioDevInterface->SlotNumber = Slot;
        SdioDevInterface->SdioBusInterface = SdioBusInterface;
        SdioDevInterface->DeviceState = DEVICE_IN_RESET_STATE;

        //
        // Add to the SdioBusInterface
        //
        InsertTailList (&(SdioBusInterface->SdioDeviceList), &(SdioDevInterface->SdioDeviceLink));

    }

    //
    // Check the device Presence in the slot
    //
    Status = SdMmcCheckDevicePresence (SdioDevInterface, Slot);

    if (EFI_ERROR(Status)) {
        SdioBusInterface->CardPresentState[Slot] = FALSE;
        RemoveEntryList (&SdioDevInterface->SdioDeviceLink);
        gBS->FreePool (SdioDevInterface);
        return EFI_DEVICE_ERROR;
    }

    SdioBusInterface->CardPresentState[Slot] = TRUE;
    //
    // Check whether the device in SD slot is I/O device. 
    //
    Status = CheckAndConfigureSdioDevice (SdioDevInterface->SdioDevInfo, Slot);
    if (!EFI_ERROR(Status)) {
        if (SdioDevInterface->SdioDevInfo->IODevice == TRUE) {
            SdioDevInterface->MassStorageDevice = FALSE;
            return EFI_SUCCESS;
        }
    }
    //
    // Configure the SD and MMC device
    //
    Status = ConfigureSdMmcMemoryDevice (SdioDevInterface->SdioDevInfo, Slot);
    if (EFI_ERROR(Status)) {
        RemoveEntryList (&SdioDevInterface->SdioDeviceLink);
        gBS->FreePool (SdioDevInterface);
        return EFI_DEVICE_ERROR;
    } 
    SdioDevInterface->MassStorageDevice = TRUE;

    //
    //Get the SD/MMC card device name
    //
    Status = SDMmcMassGetPNMWithDeviceClass (SdioDevInterface->SdioDevInfo, Slot);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Based on the device and controller select the device access mode
    //
    Status = SDMMCCardSelectAccessMode (SdioDevInterface->SdioDevInfo, Slot);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Identify the device type ( HDD, Floppy ) based on the setup option
    //
    if (gSdioReadData == 0) {
        
        Status = gBS->AllocatePages (
                                AllocateAnyPages,
                                EfiBootServicesData,
                                1,
                                (EFI_PHYSICAL_ADDRESS*)&BufferAddress);
                
        ASSERT_EFI_ERROR(Status);        
        
        gSdioReadData = BufferAddress;
        if (SdioBusInterface->ControllerType == PciIoType) {
            
            TempMemSize = 0x1000;
        
            PciIo = (EFI_PCI_IO_PROTOCOL*)SdioBusInterface->ControllerInterface;
        
            Status = PciIo->Map (
                             PciIo, 
                             EfiPciIoOperationBusMasterCommonBuffer,
                             (VOID *)BufferAddress,
                             &TempMemSize,
                             (EFI_PHYSICAL_ADDRESS *)&MappedBaseAddr,
                             &UnMappedAddress);
           
            if (EFI_ERROR (Status)) {
                ASSERT_EFI_ERROR(Status);
                return Status;
            }
            gSdioReadData = MappedBaseAddr;
        }        
    }

    SdMmcGetEmulationType (SdioDevInterface->SdioDevInfo, Slot);
        
    if (gSdioReadData) { 
        Status = gBS->FreePages (gSdioReadData, 1);
        if (SdioBusInterface->ControllerType == PciIoType) {
            PciIo->Unmap (PciIo, (VOID *)UnMappedAddress);          
        }    
        gSdioReadData = 0;

    }
    
    return Status;
}


//**********************************************************************
/**@internal
 * 
    Creates SD and eMmc device path and adds it to SdioDevInterface

    @param  This                - Pointer to EFI_COMPONENT_NAME_PROTOCOL structure
    @param  Controller          - Controller handle
    @param  SdioDevInterface    - Pointer to SDIO_DEVICE_INTERFACE structure
    @param  RemainingDevicePath - Pointer to EFI_DEVICE_PATH_PROTOCOL structure

    @retval EFI_STATUS

    @note  
  Here is the control flow of this function:
  1.  Get the controller device path and append the SD\MMC device path
  2.  But currently we are using SATA device path SDIO device path is not 
      mentioned in the UEFI specification.

   @endinternal
**/
EFI_STATUS
CreateSdioDevicePath (
    IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
    IN  EFI_HANDLE                      Controller,
    IN  SDIO_DEVICE_INTERFACE           *SdioDevInterface,
    IN  OUT EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
 )
{
    EFI_STATUS                  Status;
    SDIO_DEVICE_PATH            SdDevicePath;
    EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;     
    EMMC_DEVICE_PATH            EmmcDevicePath;   
    
    // Append the Device Path
    Status = gBS->OpenProtocol (
                        Controller,
                        &gEfiDevicePathProtocolGuid,
                        (VOID **)&TempDevicePath,
                        This->DriverBindingHandle,
                        Controller,
                        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    
    if (EFI_ERROR(Status)) { 
        return Status;
    }
 
    if (SdioDevInterface->SdioDevInfo->bMode == SD_STAND_CAP || SdioDevInterface->SdioDevInfo->bMode == SD_HIGH_CAP) {      
        // Refer UEFI2.5spec. 9.3.5.25 SD Device Path section
        SdDevicePath.Header.Type = MESSAGING_DEVICE_PATH;
        SdDevicePath.Header.SubType = MSG_SDIO_DP;
        SetDevicePathNodeLength (&SdDevicePath.Header, sizeof(SDIO_DEVICE_PATH));
        SdDevicePath.SlotNumber = SdioDevInterface->SlotNumber;
        
        SdioDevInterface->DevicePathProtocol = AppendDevicePathNode (TempDevicePath, &SdDevicePath.Header);        
    } else {
        // Refer UEFI2.6spec. 9.3.5.28 eMMc Device Path section
        EmmcDevicePath.Header.Type = MESSAGING_DEVICE_PATH;
        EmmcDevicePath.Header.SubType = MSG_EMMC_DP;
        SetDevicePathNodeLength (&EmmcDevicePath.Header, sizeof(EMMC_DEVICE_PATH));
        EmmcDevicePath.SlotNumber = SdioDevInterface->SlotNumber;
        
        SdioDevInterface->DevicePathProtocol = AppendDevicePathNode (TempDevicePath, &EmmcDevicePath.Header);
    }
   
    return EFI_SUCCESS;
}



/**@internal
 * 
    Get the SDIO Access mode from Setup and Set the SDIO_Access_Mode 
    Global variable

    @param 

    @retval VOID

   @endinternal
**/
VOID
InitilizeSdioSetupConfiguration (
 )
{

    EFI_STATUS             Status;
    EFI_GUID               gSetupGuid = SETUP_GUID;
    UINTN                  VariableSize = sizeof(SDIO_DEV_CONFIGURATION);


    Status = gRT->GetVariable (
                          L"SdioDevConfiguration",
                          &gSetupGuid,
                          NULL,
                          &VariableSize,
                          &gSdioConfiguration);

    if (EFI_ERROR(Status)) {
        //
        // Error in Getting variable. Set the mode to Auto
        //
        gSdioData->SDIO_Access_Mode = 0;
    } else {
        //
        // Initialize the Sdio Access mode and emulation type from Setup.
        //
        gSdioData->SDIO_Access_Mode = gSdioConfiguration.SdioMode;
    }
    return;
}

/**@internal
 * 
    Check the device presence and return the status
        
    @param  SataDevInterface - Pointer to SDIO_DEVICE_INTERFACE pointer
    @param  Port             - Sdio port number

    @retval EFI_STATUS
   
   @endinternal
**/
EFI_STATUS
SdMmcCheckDevicePresence (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Slot
)
{
    EFI_STATUS              Status;
    UINT8                   DevIndex;
    UINT8                   Index;
    AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface = SdioDevInterface->SdioBusInterface;

    DevIndex=GetFreeDevEntry();
    if(DevIndex == 0xFF) {
        return EFI_DEVICE_ERROR;
    }
    
    gSdioData->SdioDev[DevIndex].SdioBaseAddress = SdioBusInterface->SdioBaseAddress[Slot];
    gSdioData->SdioDev[DevIndex].AdmaDescriptorAddress = SdioBusInterface->AdmaDescriptorAddress;
    SdioDevInterface->SdioDevInfo = &gSdioData->SdioDev[DevIndex];
    
    Index = GetDevEntry(gSdioData->SdioDev[DevIndex].SdioBaseAddress);
    if (Index != 0xff) {
        SdioDevInterface->SdioDevInfo->wEmulationOption = gSdioConfiguration.SdioEmu[Index].SdEmul;
    }

    //
    // Check the Device Presence
    //
    Status = CheckDevicePresenceInController (SdioDevInterface->SdioDevInfo, Slot);

    if (EFI_ERROR(Status)) {
        return EFI_NOT_FOUND;
    }

    
    //
    // Device is present in the SD Port
    //
    SdioDevInterface->SdioDevInfo->DevEntryUsed = TRUE;
    SdioDevInterface->SdioDevInfo->DeviceAddress = DevIndex+1;
    SdioDevInterface->SdioDevInfo->SlotNumber = SdioDevInterface->SlotNumber;

    return EFI_SUCCESS;
}

/**@internal
 * 
    This function Checks if SdCard is removed from the slot
    and Uninstalls the related protocols installed for the 
    device
        
    @param  SdioBusInterface - Pointer to the AMI_SDIO_BUS_PROTOCOL
    @param  Port             - Sdio port number

    @retval  EFI_SUCEESS       SD card is removed properly.
    @return  Other             Return error status.

   @endinternal
**/

EFI_STATUS
SdCheckDeviceRemoval (
    IN  AMI_SDIO_BUS_PROTOCOL       *SdioBusInterface,
    IN  UINT8                       Port
)
{
    UINT32                PresentState;
    UINT64                SdioBaseAddr;
    EFI_STATUS            Status = EFI_SUCCESS;
    SDIO_DEVICE_INTERFACE *SdioDevInterface = NULL;

    SdioDevInterface = GetSdioDevInterface (SdioBusInterface, Port);
                                        
    if (SdioDevInterface != NULL) {
        
        if (SdioDevInterface->DeviceState == DEVICE_CONFIGURED_SUCCESSFULLY) {
            
            SdioBaseAddr = SdioDevInterface->SdioDevInfo->SdioBaseAddress;
            
            // Bit 16 of present state register denote card present or not
            PresentState = SDIO_REG32 (SdioBaseAddr, PSTATE);
            // 
            if ((PresentState &PSTATE_CARD_INSERT)== 0) {
                
                // Before uninstalling BLOCKIO check whether it is installed or not
                Status = gBS->OpenProtocol (
                                     SdioDevInterface->SdioDeviceHandle,
                                     &gEfiBlockIoProtocolGuid,
                                     NULL,
                                     gSdioDriverBinding.DriverBindingHandle,
                                     SdioDevInterface->SdioDeviceHandle,
                                     EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
                          
                if (!EFI_ERROR(Status)) {
                    Status = gBS->UninstallProtocolInterface (
                                                     SdioDevInterface->SdioDeviceHandle,
                                                     &gEfiBlockIoProtocolGuid, 
                                                     (EFI_BLOCK_IO_PROTOCOL *)(SdioDevInterface->SdioBlkIo));
                                            
                    ASSERT_EFI_ERROR(Status);
                    gBS->FreePool (SdioDevInterface->SdioBlkIo->BlkIo.Media);
                    gBS->FreePool (SdioDevInterface->SdioBlkIo);
                }
                      
                Status = gBS->CloseProtocol ( 
                                    SdioBusInterface->ControllerHandle,
                                    &gEfiPciIoProtocolGuid,
                                    gSdioDriverBinding.DriverBindingHandle,
                                    SdioDevInterface->SdioDeviceHandle);
                                    
                ASSERT_EFI_ERROR(Status);    
                              
 
                // Before uninstalling Block Erase check whether it is installed or not
                Status = gBS->OpenProtocol (
                                    SdioDevInterface->SdioDeviceHandle,
                                    &gEfiEraseBlockProtocolGuid,
                                    NULL,
                                    gSdioDriverBinding.DriverBindingHandle,
                                    SdioDevInterface->SdioDeviceHandle,
                                    EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
            
                if (!EFI_ERROR(Status)) {
                    
                    Status = gBS->UninstallProtocolInterface (
                                                      SdioDevInterface->SdioDeviceHandle,
                                                      &gEfiEraseBlockProtocolGuid, 
                                                      (EFI_BLOCK_IO_PROTOCOL *)(SdioDevInterface->SdioBlkErase));
                    ASSERT_EFI_ERROR(Status);
                    gBS->FreePool (SdioDevInterface->SdioBlkErase);
                }       
                
                Status = gBS->UninstallProtocolInterface (
                                                  SdioDevInterface->SdioDeviceHandle,
                                                  &gEfiDevicePathProtocolGuid,
                                                  SdioDevInterface->DevicePathProtocol);   
                ASSERT_EFI_ERROR(Status);
                
                gBS->FreePool (SdioDevInterface->DevicePathProtocol);
                RemoveEntryList (&SdioDevInterface->SdioDeviceLink);
                gBS->FreePool (SdioDevInterface);
            }
        }
    }
      
    return Status;
}

/**@internal
 * 
    Transfer the Nvme Controller information to SMRAM area that would be used
    by the SDIO SMM driver 

    @param  

    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
TransferSdioDataToSmram ( )
{

    EFI_STATUS                      SmmStatus;
    EFI_SMM_COMMUNICATION_PROTOCOL  *SmmCommunication;
    EFI_SMM_COMMUNICATE_HEADER      *CommHeader;
    
    gSdioCommunicateBufferSize = sizeof(EFI_GUID) + sizeof(UINTN) + sizeof(SDIO_GLOBAL_DATA);
    gBS->SetMem(gSdioCommunicateBuffer, gSdioCommunicateBufferSize, 0);
    
    // Get needed resource
    SmmStatus = gBS->LocateProtocol (
                             &gEfiSmmCommunicationProtocolGuid,
                             NULL,
                             (VOID **)&SmmCommunication);
    if (EFI_ERROR (SmmStatus)) {
        return SmmStatus;
    }

    CommHeader = (EFI_SMM_COMMUNICATE_HEADER *)gSdioCommunicateBuffer;
    gBS->CopyMem (&CommHeader->HeaderGuid, &gAmiSdioCommunicationGuid, sizeof(gAmiSdioCommunicationGuid));
    CommHeader->MessageLength = sizeof(SDIO_GLOBAL_DATA);
    gBS->CopyMem (&(CommHeader->Data[0]), gSdioData, sizeof(SDIO_GLOBAL_DATA));
   
    SmmStatus = SmmCommunication->Communicate (
                                      SmmCommunication,
                                      gSdioCommunicateBuffer,
                                      &gSdioCommunicateBufferSize);
    return SmmStatus;
}

/**@internal
 * 
    Get the Free Entry Index from SDIO Device Buffer

    @param 

    @retval Entry No

   @endinternal
**/
UINT8
GetFreeDevEntry (
)
{
    UINT8  Index;

    for (Index = 0; Index < MAX_SDIO_DEVICES; Index++) {
        if (gSdioData->SdioDev[Index].DevEntryUsed == FALSE) {
            return Index;
        }
    }

    return 0xFF;

}

/**@internal
 * 
    This function identifies the device type and fill the 
    geometry parameter into SDIO_DEVICE_INFO

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio Port number

    @retval VOID

   @endinternal
**/

VOID
SdMmcGetEmulationType (
    IN  SDIO_DEVICE_INFO *SdioDevInfo,
    IN  UINT8            Port
)
{
    UINT16          EmulationType;
    UINT16          ForceEmulationType = 0;
    static UINT16   SdioMassEmulationTypeTable[4] = {
                                        0,                                                  // Auto
                                        (SDIO_EMU_FLOPPY_ONLY << 8) + SDIO_MASS_DEV_ARMD,   // Floppy
                                        (SDIO_EMU_FORCED_FDD << 8) + SDIO_MASS_DEV_ARMD,    // Forced floppy
                                        (SDIO_EMU_HDD_ONLY << 8) + SDIO_MASS_DEV_HDD };     // HDD
    
    if (SdioDevInfo->wEmulationOption) {                        // non Auto
        ForceEmulationType = SdioMassEmulationTypeTable[SdioDevInfo->wEmulationOption];
    }

    //
    // Assume floppy
    //
    EmulationType = (UINT16)(SDIO_EMU_FLOPPY_ONLY << 8) + SDIO_MASS_DEV_ARMD;

    if (SDIOGetFormatType( \
           SdioDevInfo, Port, (UINT8 *)gSdioReadData, &EmulationType) == SDIO_ERROR) {
        //
        // Find the device type by size
        //
        if ((SdioDevInfo->dMaxLBA >> 11) > MAXIMUM_SIZE_FOR_FLOPPY_EMULATION ) {
            //
            // Assume HDD
            //
            EmulationType = (UINT16)(SDIO_EMU_HDD_ONLY << 8) + SDIO_MASS_DEV_HDD;
        }
    }

    if (ForceEmulationType)
        EmulationType = ForceEmulationType;
    SdioDevInfo->bStorageType = (UINT8)EmulationType;
    SdioDevInfo->bEmuType = (UINT8)(EmulationType >> 8);

    return;

}

/**@internal
 * 
    This function reads the first sector from the mass storage
    device and identifies the formatted type, Sets the Emulation
    type accordingly.

    @param  SdioDevInfo  - Pointer to SDIO_DEVICE_INFO structure
    @param  Port         - Sdio Port number
    @param  SdioReadData - Pointer to Buffer
    @param  EmuType      - Pointer to location that contains Emulation type of the device

    @retval SDIO_ERROR   If could not identify the format type
    @retval SDIO_SUCCESS If formatted type is identified and EmuType is updated

   @endinternal
**/

UINT8
SDIOGetFormatType (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT8               *SdioReadData,
    OUT UINT16              *EmuType
)
{
    EFI_STATUS  Status;
    UINT16      Emu_Type;
    UINT8       *ActPartAddr;
    UINT32      dHS;

    //
    // Read the first sector of the device
    //
    Status = SdMmcRead (SdioDevInfo, Port, 0, 1, SdioReadData);

    if (EFI_ERROR(Status)) {
            return SDIO_ERROR;
    }

    SdioDevInfo->bHiddenSectors = 0;

    //
    // Check for validity of Boot Record
    //
    if (*(UINT16*)(SdioReadData + 0x1FE) != 0xAA55) {
        SDIOSetDefaultGeometry (SdioDevInfo, Port);
        return SDIO_ERROR;
    }

    //
    // Check for validity of the partition table
    //
    if (SDIOValidatePartitionTable( \
            SdioReadData, SdioDevInfo->dMaxLBA, &ActPartAddr) == SDIO_SUCCESS) {
        //
        // Only one partition present, check the device size, if the device size
        // is less than 530 MB assume FDD or else assume the emulation as HDD
        //
        if (SdioDevInfo->dMaxLBA < MAX_LBA_FOR_FLOPPY_EMULATION) {
            Emu_Type = (UINT16)(SDIO_EMU_FORCED_FDD << 8) + SDIO_MASS_DEV_ARMD;
        } else {
            Emu_Type = (UINT16)(SDIO_EMU_HDD_ONLY << 8) + SDIO_MASS_DEV_HDD;
        }

        //
        // Read boot sector, set the LBA number to boot record LBA number
        //
        dHS = *((UINT32*)(ActPartAddr + 8));
        SdioDevInfo->bHiddenSectors = (UINT8)dHS; // Save hidden sector value

        Status = SdMmcRead (SdioDevInfo, Port, dHS, 1, SdioReadData);

        if (EFI_ERROR(Status))
            return SDIO_ERROR;

        if (SDIOUpdateCHSFromBootRecord( \
                SdioDevInfo, Port, SdioReadData) == SDIO_SUCCESS) {

            *EmuType = Emu_Type;
             return SDIO_SUCCESS;
        } else {

            SDIOSetDefaultGeometry(SdioDevInfo, Port);
            *EmuType = (UINT16)(SDIO_EMU_HDD_ONLY << 8) + SDIO_MASS_DEV_HDD;
            SdioDevInfo->bHiddenSectors = 0;      // Reset hidden sector value
            return SDIO_SUCCESS;
        }
    }

    if (SDIOUpdateCHSFromBootRecord(
            SdioDevInfo, Port, SdioReadData) == SDIO_SUCCESS) {

        // Assume the emulation as floppy
        // If boot record is a valid FAT/NTFS file system
        *EmuType = (UINT16)(SDIO_EMU_FLOPPY_ONLY << 8) + SDIO_MASS_DEV_ARMD;
        return SDIO_SUCCESS;
    }
    
    SDIOSetDefaultGeometry (SdioDevInfo, Port);  
    Emu_Type = (UINT16)(SDIO_EMU_FLOPPY_ONLY << 8) + SDIO_MASS_DEV_ARMD;

    if (SdioDevInfo->dMaxLBA >= MAX_LBA_FOR_FLOPPY_EMULATION) {

        // Assume the emulation as HDD
        // If the device size greater than 530MB
        SdioDevInfo->bHiddenSectors = 0;
        Emu_Type = (UINT16)(SDIO_EMU_HDD_ONLY << 8) + SDIO_MASS_DEV_HDD;
    }

    *EmuType = Emu_Type;
    return SDIO_SUCCESS;

}

/**@internal
 * 
    This procedure updates cylinder parameter for device geometry.
    head and sector parameters are required before invoking this
    function.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio Port number

    @retval VOID

   @endinternal
**/

VOID
SdioMassUpdateCylinderInfo (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port 
)
{
    UINT32 Data = SdioDevInfo->dMaxLBA / (SdioDevInfo->NumSectors * SdioDevInfo->NumHeads);

    if (Data <= 1) 
        Data++;
    if (Data > 0xFFFF)
        Data = 0xFFFF;   // DOS workaround

    SdioDevInfo->NumCylinders = (UINT16)Data;
    SdioDevInfo->LBANumCyls = (UINT16)Data;
    return;
}

/**@internal
 * 
    This procedure sets the  default geometry for mass 
    storage devices.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio Port number

    @retval SDIO_SUCCESS

   @endinternal
**/

UINT8 
SDIOSetDefaultGeometry ( 
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    SdioDevInfo->NumHeads = 0xFF;
    SdioDevInfo->LBANumHeads = 0xFF;
    SdioDevInfo->NumSectors = 0x3F;
    SdioDevInfo->LBANumSectors = 0x3F;

    SdioMassUpdateCylinderInfo (SdioDevInfo, Port);
    return SDIO_SUCCESS;
}

/**@internal
 * 
    This procedure checks whether the partition table is valid.

    @param  Buffer      - Pointer to the Boot Record of the device
    @param  dMaxLBA     - Max LBA of the device
    @param  ActPartAddr - Pointer to a pointer that contains Active Partition offset

    @retval SDIO_SUCCESS partition table is valid:
    @retval ValidEntryCount Possible valid entry count ( 1-based )
    @retval ActPartAddr Active entry offset ( Absolute offset )
    @retval SDIO_ERROR Invalid partition table

   @endinternal
**/

UINT8
SDIOValidatePartitionTable (
    IN  UINT8   *Buffer,
    IN  UINT32  dMaxLBA,
    OUT UINT8   **ActPartAddr
)
{

    UINT8  *PartPtr;
    UINT8  PartNo = 0;
    UINT8  *ActPart = NULL;
    UINT8  ValidEntryCount = 0;

    //
    // Drive has a partition table, start from 1st bootable partition
    //
    PartPtr = Buffer + 0x1BE;

    for ( ; PartNo < 4; PartNo++, PartPtr += 0x10) {

        if (*PartPtr & 0x7F) 
            return SDIO_ERROR; //BootFlag should be 0x0 or 0x80
        //
        // Check whether beginning LBA is reasonable
        //
        if (*(UINT32*)(PartPtr + 8) > dMaxLBA) 
            return SDIO_ERROR;
        
        ValidEntryCount++;                      // Update valid entry count
        //
        // Update active entry offset
        //
        if (!(*PartPtr & 0x80))
            continue;
        if (ActPart)
            continue;
        ActPart = PartPtr;
    }

    if (ValidEntryCount < 1)
        return SDIO_ERROR; // Atleast one valid partition is found
    //
    // If no active partition table entry found use first entry
    //
    if (ActPart == NULL) 
        ActPart = Buffer + 0x1BE;

    *ActPartAddr = ActPart;

    return SDIO_SUCCESS;
}

/**@internal
 * 
    This function parses the boot record and extract the CHS
    information of the formatted media from the boot record.
    This routine checks for DOS & NTFS formats only

    @param  SdioDevInfo  - Pointer to SDIO_DEVICE_INFO structure
    @param  Port         - Sdio Port number
    @param  SdBootRecord - Pointer to Boot record of the device

    @retval SDIO_ERROR If the boot record is un-recognizable and CHS info is not extracted
    @retval SDIO_SUCCESS If the boot record is recognizable and CHS info is extracted. CHS information is updated in the SDIO_DEVICE_INFO structure

   @endinternal
**/

UINT8
SDIOUpdateCHSFromBootRecord (
    IN  SDIO_DEVICE_INFO*   SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT8*              SdBootRecord
)
{
    UINT32  OemName;
    UINT8   Heads;
    UINT8   SecPerTrack;
    UINT16  SecTimesHeads;
    UINT16  TotalSect;

    if (*((UINT16*)(SdBootRecord + 0x1FE)) != 0xAA55)
        return SDIO_ERROR;

    //
    // Read succeeded so the drive is formatted
    // Check for valid MSDOS/MSWIN/NTFS boot record
    //
    OemName = *(UINT32*)(SdBootRecord + 3);
    
    if ((OemName != 0x4F44534D) &&   // 'ODSM' for MSDO
        (OemName != 0x4957534D) &&   // 'IWSM' for MSWI
        (OemName != 0x5346544E)) {   // 'SFTN' for NTFS
        //
        // Check for valid FAT,FAT16,FAT32 boot records
        //
        *(SdBootRecord + 0x36 + 3) = 0x20;              // Ignore the 4th byte and fill it with space
        if ((*(UINT32*)(SdBootRecord + 0x36) != 0x20544146) &&      // " TAF" for FATx
            (*(UINT32*)(SdBootRecord + 0x52) != 0x33544146)) {      // "3TAF" for FAT3
            //
            // Boot Record is invalid. Return with error
            //
            return SDIO_ERROR;
        }
    }

    Heads = *(SdBootRecord + 0x1A);         // Number of heads
    SecPerTrack = *(SdBootRecord + 0x18);   // Sectors/track
    SecTimesHeads = Heads * SecPerTrack;

    // Zero check added to prevent invalid sector/head information in BPB
    if (SecTimesHeads == 0) {
        return SDIO_ERROR;
    }

    TotalSect = *(UINT16*)(SdBootRecord + 0x13);
    if (TotalSect) {
        SdioDevInfo->dMaxLBA = TotalSect;
    }

    SdioDevInfo->NumHeads = Heads;
    SdioDevInfo->LBANumHeads = Heads;
    SdioDevInfo->NumSectors = SecPerTrack;
    SdioDevInfo->LBANumSectors = SecPerTrack;

    SdioMassUpdateCylinderInfo (SdioDevInfo, Port);

    return  SDIO_SUCCESS;
}

/**@internal
 * 
    This function will select the Access mode for the data transfer.

    @param  SdioDevInfo  - Pointer to SDIO_DEVICE_INFO structure
    @param  Port         - Sdio Port number

    @retval EFI_SUCCESS

   @endinternal
**/
EFI_STATUS
SDMMCCardSelectAccessMode (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT32  Capability = 0;

    Capability = SDIO_REG32 (SdioDevInfo->SdioBaseAddress, CAP);

    
    if (gSdioData->SDIO_Access_Mode == 0 ) {

        //
        // If the SDIO access mode is Auto, based on capabilities select PIO,SDMA 
        // or ADMA
        //
        if ((Capability & ADMA2_SUPPORT) && (SdioDevInfo->bHostControllerVersion >= 1)) {
            SdioDevInfo->SDIO_Access = ADMA;
        } else if (Capability & SDMA_SUPPORT) {
            SdioDevInfo->SDIO_Access = SDMA;
        }else {
            SdioDevInfo->SDIO_Access = PIO;
        }
    } else if (gSdioData->SDIO_Access_Mode == 1) {

        //
        // If the SDIO access mode is ADMA and controller support it then ADMA 
        // is select else SDMA or PIO
        //
        if ((Capability & ADMA2_SUPPORT) && (SdioDevInfo->bHostControllerVersion >= 1)) {
            SdioDevInfo->SDIO_Access = ADMA;
        }else if (Capability & SDMA_SUPPORT) {
            SdioDevInfo->SDIO_Access = SDMA;
        }else {
            SdioDevInfo->SDIO_Access = PIO;
        }
    } else if (gSdioData->SDIO_Access_Mode == 2) {
        //
        // If the SDIO access mode is SDMA and controller support it then SDMA 
        // is select else ADMA or PIO
        //
        if (Capability & SDMA_SUPPORT) {
            SdioDevInfo->SDIO_Access = SDMA;
        } else if ((Capability & ADMA2_SUPPORT) && (SdioDevInfo->bHostControllerVersion >= 1)) {
            SdioDevInfo->SDIO_Access = ADMA;
        } else {
            SdioDevInfo->SDIO_Access = PIO;
        }
    } else if (gSdioData->SDIO_Access_Mode == 3) {
        //
        // If the SDIO access mode is PIO and then PIO is selected
        //
        SdioDevInfo->SDIO_Access = PIO;
    }

    return EFI_SUCCESS;
}
/**@internal
 * 
    Get the Sd/MMC card Device Name and concatenate it with the
    string formed based on the size of SD card if PNM is not Zero.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS

    @note
    If PNM is zero then SD Memory Card - Device (Index) is displayed for SD.
    MMC Memory Card - Device (Index) is displayed for MMC device. Index is
    varied for the no. of devices detected without PNM.

   @endinternal
**/
EFI_STATUS
SDMmcMassGetPNMWithDeviceClass (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT8   *TempUint8;
    UINT8   Index1;
    UINT8   Index2;
    UINT64  CardSize;
    BOOLEAN IsPNMZero = FALSE;
    static  UINT8 SDDevIndex = '0';
    static  UINT8 MMCDevIndex = '0';
    BOOLEAN SDCardWithOutPNMDetected = FALSE;

    TempUint8 = (UINT8*)&SdioDevInfo->d4CID[3];

    //
    // Check if PNM is Zero.
    //
    for (Index2 = 0; Index2 < 5; Index2++, TempUint8--) {
        if (*TempUint8 != '0') {
            break;
        }
    }

    if (Index2 == 5) {
       IsPNMZero = TRUE;
    }

    if ((SdioDevInfo->bMode == MMC_STAND_CAP) || \
            (SdioDevInfo->bMode == MMC_HIGH_CAP)) {
        //
        // If PNM is Zero display String MMCDevnameForPNMZero
        //
        if (IsPNMZero) {
            TempUint8 = (UINT8*)MMCDevnameForPNMZero;
        } else {
            TempUint8 = (UINT8*)"eMMC ";
        }
    } else {
        //
        // If PNM is Zero display String SDDevnameForPNMZero
        //
        if (IsPNMZero) {
            TempUint8 = SDDevnameForPNMZero;
            SDCardWithOutPNMDetected = TRUE;
        } else {
            //
            //Calculate the SD Card Size.
            //
            CardSize = ((UINT64)(SdioDevInfo->dMaxLBA) * 512);
            //
            //Assign name to display in setup based on the Size.
            //
            if (CardSize <= TWO_GB) {
                TempUint8 = (UINT8*)"SDSC - ";
            } else if (CardSize <= THIRTY_TWO_GB) {
                TempUint8 = (UINT8*)"SDHC - ";
            } else {
                TempUint8 = (UINT8*)"SDXC - ";
            }
        }
    }

    if (!IsPNMZero) {

        for (Index1 = 0; *TempUint8 != 0; Index1++, TempUint8++) {
            SdioDevInfo->PNM[Index1] = *TempUint8;
        }

        TempUint8 = (UINT8*)&SdioDevInfo->d4CID[3];
        //
        // Concatenate product name with above assigned name.
        //
        for (Index2 = 0; Index2 < 5; Index2++, TempUint8--) {
            // if there is non printable character, fill with space
            if (*TempUint8 > 0x1F) {
                SdioDevInfo->PNM[Index1 + Index2] = *TempUint8;
            } else {
                SdioDevInfo->PNM[Index1 + Index2] = ' ';
            }
        }

        if ((SdioDevInfo->bMode == MMC_STAND_CAP) || \
            (SdioDevInfo->bMode == MMC_HIGH_CAP)) {
            if (*TempUint8 > 0x1F) {
                SdioDevInfo->PNM[Index1 + Index2] = *TempUint8;
            } else {
                SdioDevInfo->PNM[Index1 + Index2] = ' ';
            }
            Index2++;
        }
        SdioDevInfo->PNM[Index1 + Index2] = 0;

    } else {

        for (Index1=0; *TempUint8 != 0; Index1++, TempUint8++) {
            SdioDevInfo->PNM[Index1] = *TempUint8;
        }

        //
        // Append the Index to the string to differentiate between two
        // Cards with PNM equal to Zero.
        //
        if (SDCardWithOutPNMDetected) {
            SdioDevInfo->PNM[Index1++] = SDDevIndex++;
        } else {
            if (SdioDevInfo->MmcBusWidth == MMC_1_BIT_BUS_WIDTH) {
                SdioDevInfo->PNM[Index1++] = MMCDevIndex - 1;
            } else {
                SdioDevInfo->PNM[Index1++] = MMCDevIndex++;
            }
        }

        SdioDevInfo->PNM[Index1] = 0;
    }

    return EFI_SUCCESS;
}
/**@internal
 * 
    Get the SDIO device information. It return if memory is present and 
    how many IO functions are present in the device.

    @param  SdioDevInfo   - Pointer to SDIO_DEVICE_INFO structure
    @param  Port          - Sdio port number
    @param  MemoryPresent - To check if memory is present or not

    @retval EFI_STATUS
    Note: This function is following section 3.2 The IO_SEND_OP_COND Command
    (CMD5) and 3.3 The IO_SEND_OP_COND Response (R4) of Spec SDIO Simplified 
    Specification Version 3.00

   @endinternal
**/
EFI_STATUS
SDCard_CheckIO (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT8               *MemoryPresent
)
{

    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT32      ResponceData = 0;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;

    //
    //Issue CMD5
    //
    CommandIndex = (IO_SEND_OP_COND_CMD5 << 8) | (RESP4_TYPE);
    CommandArgument = 0x000000;
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port, 
                     CommandIndex, 
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // According to section 3.3 The IO_SEND_OP_COND Response (R4) of SDIO 
    // Simplified  Specification Version 3.00. Bit27 is Memory Present Bit
    // and Bit28-Bit30 is Number of IO bits
    //
    ResponceData = SDIO_REG32 (SdioBaseAddr, RESP0);
    SdioDevInfo->IoFunctionCount = ((ResponceData >> 28) & 07);
    SdioDevInfo->dOCR = (ResponceData & 0xFFFFFF);
    *MemoryPresent = ((ResponceData >> 27) & 01);
    
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"\n SdMmc: NumberOfIo: %x,MemoryPresent:%x,IoOcr:%x ", SdioDevInfo->IoFunctionCount, *MemoryPresent, SdioDevInfo->dOCR));
#endif
    return EFI_SUCCESS;
}

/**@internal
 * 
    Configure the IO functionalities of the device

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
SdIoSetVoltage (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    EFI_STATUS      Status;
    UINT64          SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16          CommandIndex;
    UINT32          CommandArgument;
    UINT8           Index;
    UINT8           OcrMsb = 0;
    
    // Get the Most Significant bit of Ocr value
    for (Index = 23; Index > 0; Index--) {
        if ((SdioDevInfo->dOCR >> Index) & 0x1 ) {
            OcrMsb = Index;
            break;
        }
    }
    
    //
    //Set the Voltage Level.
    //
    CommandIndex = (IO_SEND_OP_COND_CMD5 << 8) | (RESP4_TYPE);
    CommandArgument = 1 << OcrMsb;
    Status = SdMmcCommand (
                      SdioDevInfo,
                      Port,
                      CommandIndex,
                      CommandArgument,
                      SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Issue CMD3 to publish a new relative address.
    //
    CommandIndex = ((SEND_RELATIVE_ADDR_CMD3 << 8) | RESP6_TYPE);
    CommandArgument = 0;
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port,
                     CommandIndex,
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    SdioDevInfo->wRCA = (UINT16)(SDIO_REG32 (SdioBaseAddr, RESP0) >> 16);
    SdioDevInfo->bState = CARDSTATUS_STBY;
    return EFI_SUCCESS;
}
/**@internal
 * 
    Configure the IO functionalities of device

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure 
    @param  Port        - Sdio port number
    
    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
EnableIoFunctions(
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Slot
    )
{
    EFI_STATUS    Status;
    UINT32        CommandArgument;
    UINT32        DataBuffer;
    UINT8         IOEx;
    UINT8         Index;
    UINT8         TimeOut = IO_ENABLE_TIMEOUT;

    
    for (Index = 1; Index <= SdioDevInfo->IoFunctionCount; Index++) {
        
        //Read the I/O Enable register
        CommandArgument = MAKE_SDIO_OFFSET(IO_ENABLE);    
        Status = SdIoReadWriteCmd (
                               SdioDevInfo,
                               Slot,
                               IO_RW_DIRECT,
                               CommandArgument,
                               &DataBuffer,
                               RESP5_TYPE,
                               1,
                               (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        IOEx  = (UINT8) DataBuffer | (1 << Index);	
        
        //Enable IOEx bit of corresponding function in  I/O Enable register
        CommandArgument = MAKE_SDIO_RW(1) | MAKE_SDIO_OFFSET(IO_ENABLE) | IOEx;       
        Status = SdIoReadWriteCmd (
                              SdioDevInfo,
                              Slot,
                              IO_RW_DIRECT,
                              CommandArgument,
                              &DataBuffer,
                              RESP5_TYPE,
                              0,
                              (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );

        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        while (1) {
            
            //Check whether the Corresponding IO function is enabled or not from I/O Ready register
            CommandArgument = MAKE_SDIO_OFFSET(IO_READY);      
            Status = SdIoReadWriteCmd (
                                   SdioDevInfo,
                                   Slot,
                                   IO_RW_DIRECT,
                                   CommandArgument,
                                   &DataBuffer,
                                   RESP5_TYPE,
                                   1,
                                   (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
            
            if (EFI_ERROR(Status)) {
                return Status;
            }
            
            // If IO_READY bit is enabled for corresponding function then quit the loop
            if ((UINT8)DataBuffer & (1 << Index))
                break;
            //1Ms delay
            MicroSecondDelay (1000);
            TimeOut--;
            if (!TimeOut) {
                return EFI_TIMEOUT;
            }		
        }
    }
    
    //enable the interrupt enable master bit
    CommandArgument = MAKE_SDIO_RW(1) |  MAKE_SDIO_OFFSET(INT_ENABLE) | BIT0;       	  
    Status = SdIoReadWriteCmd (
                          SdioDevInfo,
                          Slot,
                          IO_RW_DIRECT,
                          CommandArgument,
                          &DataBuffer,
                          RESP5_TYPE,
                          0,
                          (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );

    if (EFI_ERROR(Status)) {
        return Status;
    }
    return EFI_SUCCESS;
}

/**@internal
 * 
    Set the Block size for IO cards in Functional Block Size register.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number
    
    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
SetBlockSize (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Slot
) {
    UINT16        FnBlockSizeReg;
    UINT8         FuncNo;
    UINT32        CommandArgument;
    UINT32        DataBuffer;
 
   //Check the MultiBlock support on card
    if (SdioDevInfo->IoCapabilityRegister & SMB) {
        //Set 512 as default block size for all functions.
        for (FuncNo = 0; FuncNo <= SdioDevInfo->IoFunctionCount; FuncNo++) {		
            FnBlockSizeReg = FN_BLOCK_SIZE_OFFSET | (FuncNo * 0x100);
            CommandArgument = MAKE_SDIO_RW(1) | MAKE_SDIO_OFFSET (FnBlockSizeReg) | (BLOCK_SIZE & 0xFF);    
              
            SdIoReadWriteCmd (
                         SdioDevInfo,
                         Slot,
                         IO_RW_DIRECT,
                         CommandArgument,
                         &DataBuffer,
                         RESP5_TYPE,
                         0,
                         (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );  

            FnBlockSizeReg++;
            CommandArgument = MAKE_SDIO_RW(1) | MAKE_SDIO_OFFSET (FnBlockSizeReg) | ((BLOCK_SIZE >> 8) & 0xFF);    	   		   	   	  
            SdIoReadWriteCmd (
                        SdioDevInfo,
                        Slot,
                        IO_RW_DIRECT,
                        CommandArgument,
                        &DataBuffer,
                        RESP5_TYPE,
                        0,
                        (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );  
       
        }
    }
    return EFI_SUCCESS;	
}
/**@internal
 * 
    Get the Card Common Control Registers

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure 
    @param  Slot        - Sdio slot number
    
    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
SdIoGetCCCR (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Slot
) {
    EFI_STATUS       Status;
    UINT32           CommandArgument;
    UINT32           DataBuffer;
    UINT8            TupleCode;
    UINT8            TupleSize = 0;
    UINT8            Index;
    UINT32           CisPointerIndex;    
    
    //Get the Capability Register
    CommandArgument = MAKE_SDIO_OFFSET (CARD_CAPABILITY_REGISTER); 
                                                      
    Status = SdIoReadWriteCmd (
                          SdioDevInfo,
                          Slot,
                          IO_RW_DIRECT,
                          CommandArgument,
                          &DataBuffer,
                          RESP5_TYPE,
                          1,
                          (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
        
    if (EFI_ERROR(Status)) {
        return Status;
    }
    SdioDevInfo->IoCapabilityRegister = (UINT8)DataBuffer;
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE,"SdMmc: IoCapabilityRegister = %x \n", DataBuffer));
#endif   
    //Get the CommonCISPointer
    for (Index = 0; Index < 3; Index++) {
        CommandArgument = MAKE_SDIO_OFFSET(COMMON_CIS_POINTER + Index); 
                                                   
        Status = SdIoReadWriteCmd (
                              SdioDevInfo,
                              Slot,
                              IO_RW_DIRECT,
                              CommandArgument,
                              &DataBuffer,
                              RESP5_TYPE,
                              1,
                              (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
        
        if (EFI_ERROR(Status)) {
            return Status;
        }
        SdioDevInfo->CommonCISPointer = SdioDevInfo->CommonCISPointer  | (DataBuffer << (Index*8));    
    }
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE,"SdMmc: CommonCISPointer = %x \n", SdioDevInfo->CommonCISPointer));
#endif  
    CisPointerIndex = SdioDevInfo->CommonCISPointer;
    do {       
        //Get the CommonCISPointer
         CommandArgument = MAKE_SDIO_OFFSET(CisPointerIndex);  

        // Get the Tuple Code        
        Status=SdIoReadWriteCmd (
                             SdioDevInfo,
                             Slot,
                             IO_RW_DIRECT,
                             CommandArgument,
                             &DataBuffer,
                             RESP5_TYPE,
                             TRUE,
                             (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );

        if (EFI_ERROR(Status)) {
            return Status;
        }
        TupleCode = (UINT8)DataBuffer;

        // If it's Manufacture Tuple or End of Tuple , then exit the loop
        if (TupleCode == CISTPL_MANFID || TupleCode == CISTPL_END) {
            break;
        }
    
        // Read the Next Tuple Link (i.e size of current Tuple)
        CisPointerIndex++;
        CommandArgument = MAKE_SDIO_OFFSET (CisPointerIndex);            
        Status = SdIoReadWriteCmd (
                              SdioDevInfo,
                              Slot,
                              IO_RW_DIRECT,
                              CommandArgument,
                              &DataBuffer,
                              RESP5_TYPE,
                              TRUE,
                              (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );

        if (EFI_ERROR(Status)) {
            return Status;
        }

        // Try to get the Next Tuple Code.
        // Skip the  current Tuple (TupleLink + TupleLink Size)
        CisPointerIndex += DataBuffer+1;

    } while (CisPointerIndex <= CIS_AREA_END);
    
    // if Manufacture Tuple found, Read the Manufacture ID
    if (TupleCode == CISTPL_MANFID) {          
        // Get the Manufacture tuple size from next Tuple
        CisPointerIndex++;
        CommandArgument = MAKE_SDIO_OFFSET (CisPointerIndex); 
        Status=SdIoReadWriteCmd (
                             SdioDevInfo,
                             Slot,
                             IO_RW_DIRECT,
                             CommandArgument,
                             &DataBuffer,
                             RESP5_TYPE,
                             TRUE,
                             (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );

        if (EFI_ERROR(Status)) {
            return Status;
        }

        TupleSize = (UINT8)DataBuffer;
        CisPointerIndex++;
        for (Index = 0; Index < TupleSize; Index++  ) {
                            
          // Read the Manufacture tuple 
          CommandArgument = MAKE_SDIO_OFFSET (CisPointerIndex + Index); 
          Status=SdIoReadWriteCmd (
                             SdioDevInfo,
                             Slot,
                             IO_RW_DIRECT,
                             CommandArgument,
                             &DataBuffer,
                             RESP5_TYPE,
                             TRUE,
                             (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
          if (EFI_ERROR(Status)) {
              return Status;
          }
          SdioDevInfo->SdIOManufactureId[Index] = (UINT8)DataBuffer;     
        }        
    } 	   	   	
    return EFI_SUCCESS;      
}
/**@internal
 * 
    Check the Connected SD device is I/O device or not 

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure 
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note: This function is implemented as per sec 3.1.2 
    Initialization by I/O Aware Host of SDIO Simplified 
    Specification Version 3.00
    If the connected device is IO then return success 
    else return EFI_NOT_FOUND.
    
   @endinternal
**/
EFI_STATUS
CheckAndConfigureSdioDevice (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{

    EFI_STATUS  Status;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    UINT8       MemoryPresent;

    Status = ControllerInitEnvironment (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Issue CMD0
    //
    CommandIndex = GO_IDLE_STATE_CMD0;
    CommandArgument = 0;
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port,
                     CommandIndex,
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }    
    
    //
    // Check whether SD device has IO function.
    //
    Status = SDCard_CheckIO (SdioDevInfo, Port, &MemoryPresent);
    if ((EFI_ERROR(Status)) || MemoryPresent != 0 || SdioDevInfo->IoFunctionCount == 0) {
        return EFI_NOT_FOUND;
    } 
    
    //
    // It's an SD I/O Device.
    //      
    SdioDevInfo->IODevice = TRUE;
    
    Status = SdIoSetVoltage (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    Status = SdMmcCardSelect (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = EnableIoFunctions (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = SdIoGetCCCR (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = SetBlockSize (SdioDevInfo, Port);
    if (EFI_ERROR(Status)){
        return Status;
    }
   
    // Vendor specific initialization, if required
    Status = IoCardEnableHook (SdioDevInfo, Port);
    if (EFI_ERROR(Status)){
        return Status;
    }
    
    return EFI_SUCCESS;
}

/**@internal
 * 
    Get the Index no for the SdioBaseAddress

    @param  SdioBaseAddress - Sdio base address

    @retval DeviceIndex     - Index number for SdioBaseAddress

   @endinternal
**/
UINT8
GetDevEntry (
    IN  UINT64   SdioBaseAddress
)
{
    UINT8   Index;

    for (Index = 0; Index < MAX_SDIO_DEVICES; Index++) {
        if (gSdioConfiguration.SdioEmu[Index].SdMmcAddress == SdioBaseAddress) {
            return Index;
        }
    }

    return 0xFF;

}

