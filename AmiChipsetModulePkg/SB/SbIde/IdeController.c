//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file IdeController.c
    Initialize and provide a protocol for the Ide controller.


**/
//**********************************************************************

// Module specific Includes

#include "IdeController.h"

//
// Global Variables definitions
//
extern EFI_COMPONENT_NAME_PROTOCOL      gComponentNameProtocol;
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL         *gPciRootBridgeIo;

EFI_S3_SAVE_STATE_PROTOCOL               *gBootScriptSave = NULL;

//-------------------------------------------------------
// controller Driver GUID
//-------------------------------------------------------
EFI_GUID gControllerDriverGuid = CONTROLLER_DRIVER_GUID;

//-------------------------------------------------------
// CSP definition
//-------------------------------------------------------
SB_SETUP_DATA                   gSetupData;
BOOLEAN                         CspInit = FALSE;
EFI_EVENT                       gReadyToBootEvent;
EFI_EVENT                       gPciIoEvent;
VOID                            *gRegistration=NULL;

//-------------------------------------------------------
//  EFI_DRIVER_BINDING_PROTOCOL instance
//-------------------------------------------------------
EFI_DRIVER_BINDING_PROTOCOL gSbIdeControllerDriverBinding = {
  SbIdeControllerSupported,
  SbIdeControllerStart,
  SbIdeControllerStop,
  1,
  NULL,
  NULL
};

//**********************************************************************
/**
    Installs Ide controller DriverBinding protocol


    @param ImageHandle Image handle for this driver image
    @param SystemTable pointer to the EFIsystem table


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note
  Here is the control flow of this function:
  1. Initialize Ami Lib.
  2. Install Driver Binding Protocol
  3. Return EFI_SUCCESS.

**/
//**********************************************************************
EFI_STATUS
EFIAPI
SbIdeControllerEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
    EFI_STATUS  Status;

    InitAmiLib(ImageHandle, SystemTable);

    //
    // Driver Binding Protocol install
    //
    gSbIdeControllerDriverBinding.DriverBindingHandle=ImageHandle;
    gSbIdeControllerDriverBinding.ImageHandle=ImageHandle;
    Status = gBS->InstallMultipleProtocolInterfaces(
                &ImageHandle,
                &gEfiDriverBindingProtocolGuid,
                &gSbIdeControllerDriverBinding,
                &gEfiComponentNameProtocolGuid,
                &gComponentNameProtocol,
                NULL
                );
    ASSERT_EFI_ERROR(Status);

    //
    // Create event for boot script
    //
    Status = CreateReadyToBootEvent(
                TPL_NOTIFY, \
                MultiCallBack, \
                NULL, \
                &gReadyToBootEvent \
                );
    ASSERT_EFI_ERROR(Status);

    //
    // Create event for boot script
    //
    Status = gBS->CreateEvent(
                EFI_EVENT_NOTIFY_SIGNAL, \
                TPL_NOTIFY, \
                MultiCallBack, \
                NULL, \
                &gPciIoEvent \
                );
    ASSERT_EFI_ERROR(Status);

    Status = gBS->RegisterProtocolNotify(
                &gEfiPciIoProtocolGuid, gPciIoEvent, &gRegistration);
    ASSERT_EFI_ERROR(Status);

    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"IdeControllerEntryPoint Status = %r\n", Status));

    return Status;
}

//**********************************************************************
/**
    Checks whether the given controller is IDE  or not


    @param This pointer to EFI_DRIVER_BINDING_PROTOCOL structure
    @param Controller handle of controller
    @param RemainingDevicePath pointer to EFI_DEVICE_PATH_PROTOCOL structure


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note
  Here is the control flow of this function:
  1. Check whether PCI and Devicepath protocol has been installed on this controller
  2. Check if the controller is IDE controller
  3. If IDEController protocol already installed, return EFI_ALREADY_STARTED
  4. Return EFI_SUCCESS

**/
//**********************************************************************
EFI_STATUS
EFIAPI
SbIdeControllerSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL *This,
  IN EFI_HANDLE                  Controller,
  IN EFI_DEVICE_PATH_PROTOCOL    *RemainingDevicePath
  )
{
    EFI_STATUS                  Status;
    EFI_DEVICE_PATH_PROTOCOL    *ParentDevicePath;
    EFI_PCI_IO_PROTOCOL         *PciIo;

    //
    // Ide Controller is a device driver, and should ingore the
    // "RemainingDevicePath" according to EFI spec
    //
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiDevicePathProtocolGuid,
                    (VOID *) &ParentDevicePath,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
    if (EFI_ERROR (Status)) {
      //
      // EFI_ALREADY_STARTED is also an error
      //
      return Status;
    }

    //
    // Close the protocol because we don't use it here
    //
    gBS->CloseProtocol (
          Controller,
          &gEfiDevicePathProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );

    //
    // Now test the EfiPciIoProtocol
    //
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID **) &PciIo,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // Check for the desired IDE controller
    //
    Status = IdeControllerCheck(PciIo);
    //
    // close protocol to avoid to carry it on for multiple exit points.
    //
    gBS->CloseProtocol (
          Controller,
          &gEfiPciIoProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );

    if (EFI_ERROR (Status)) return  EFI_UNSUPPORTED;

    if (!CspInit) {

        GetSbSetupData(gRT, &gSetupData, FALSE);

        Status = gBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, \
                    &gPciRootBridgeIo);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) {
            DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "SB Ide Driver locate PciRootBridgeIoProtocol = %r\n",Status));
            return Status;
        }

        Status = gBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
                    &gBootScriptSave);
        ASSERT_EFI_ERROR(Status);
        if (EFI_ERROR(Status)) {
            DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "SB Ide Driver locate BootScriptSaveProtocol = %r\n",Status));
            return Status;
        }

        CspInit = TRUE;
    }

  return Status;
}


//**********************************************************************
/**
    Installs IdeControllerProtocol


    @param This pointer to EFI_DRIVER_BINDING_PROTOCOL structure
    @param Controller handle of controller
    @param RemainingDevicePath pointer to EFI_DEVICE_PATH_PROTOCOL structure


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note
  Here is the control flow of this function:
  1. Check whether PCI and Devicepath protocol has been installed on this controller
  2. Check if the controller is IDE controller
  3. If "No", return  EFI_UNSUPPORTED
  5.Install IDEControllerprotocol and return EFI_SUCCESS.

**/
//**********************************************************************
EFI_STATUS
EFIAPI
SbIdeControllerStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
    EFI_STATUS                          Status;
    EFI_PCI_IO_PROTOCOL                 *PciIo;
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData = NULL;

    //
    // Now test and open the EfiPciIoProtocol
    //
    Status = gBS->OpenProtocol (
                    Controller,
                    &gEfiPciIoProtocolGuid,
                    (VOID **) &PciIo,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_BY_DRIVER
                    );
    //
    // Status == 0 - A normal execution flow, SUCCESS and the program proceeds.
    // Status == ALREADY_STARTED - A non-zero Status code returned. It indicates
    //           that the protocol has been opened and should be treated as a
    //           normal condition and the program proceeds. The Protocol will not
    //           opened 'again' by this call.
    // Status != ALREADY_STARTED - Error status, terminate program execution
    //
    if (EFI_ERROR (Status)) {
        //
        // EFI_ALREADY_STARTED is also an error
        //
        return Status;
    }
    //
    // Allocate Ide controller private data structure
    //

    PrivateData = MallocZ(sizeof(EFI_SBIDE_CONTROLLER_PRIVATE_DATA));
    if (PrivateData == NULL) {
        DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET,
            "Ide Controller START ERROR: \
                Allocating pool for IdePrivateData failed!\n"));
        Status = EFI_OUT_OF_RESOURCES;
        goto Done;
    }

    //
    // Initialize Ide controller private data
    //
    PrivateData->Signature              = CONTROLLER_SIGNATURE;
    PrivateData->PciIo                  = PciIo;
    PrivateData->IdeInit.GetChannelInfo = IdeInitGetChannelInfo;
    PrivateData->IdeInit.NotifyPhase    = IdeInitNotifyPhase;
    PrivateData->IdeInit.SubmitData     = IdeInitSubmitData;
    PrivateData->IdeInit.DisqualifyMode = IdeInitDisqualifyMode;
    PrivateData->IdeInit.CalculateMode  = IdeInitCalculateMode;
    PrivateData->IdeInit.SetTiming      = IdeInitSetTiming;
    PrivateData->IdeInit.EnumAll        = IDE_ENUMER_ALL;
    PrivateData->IdeInit.ChannelCount   = GetMaxChannels();
    // post code
    PROGRESS_CODE(DXE_SB_DEVICES_INIT);
    //
    // Enable Ide controller working in appropriate mode
    //
    Status = InitIdeController(PciIo);

    if (EFI_ERROR (Status)) {
      Status = EFI_DEVICE_ERROR;
      goto Done;
    }

    //
    // Install IDE_CONTROLLER_INIT protocol & private data to this instance
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gControllerDriverGuid,
                  PrivateData,
                  &gEfiIdeControllerInitProtocolGuid,
                  &(PrivateData->IdeInit),
                  NULL
                  );

Done:

    if (EFI_ERROR (Status)) {

        gBS->CloseProtocol (
              Controller,
              &gEfiPciIoProtocolGuid,
              This->DriverBindingHandle,
              Controller
              );
        if (PrivateData != NULL) {
            gBS->FreePool (PrivateData);
        }
    }

    return Status;
}

//**********************************************************************
/**
    Installs IdeControllerProtocol


    @param This Protocol instance pointer.
    @param Controller Handle of device to stop driver on
    @param ChildHandleBuffer Number of Handles in ChildHandleBuffer. If number of
        children is zero stop the entire bus driver.
    @param ChildHandleBuffer List of Child Handles to Stop.


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note
  Here is the control flow of this function:
  1. Check whether PCI and Devicepath protocol has been installed on this controller
  2. Check if the controller is IDE controller
  3. If "No", return  EFI_UNSUPPORTED
  5.Install IDEControllerprotocol and return EFI_SUCCESS.

**/
//**********************************************************************
EFI_STATUS
EFIAPI
SbIdeControllerStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL     *This,
  IN  EFI_HANDLE                      Controller,
  IN  UINTN                           NumberOfChildren,
  IN  EFI_HANDLE                      *ChildHandleBuffer
  )
{
    EFI_STATUS                          Status;
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData;

    //
    // Get private data
    //
    Status = gBS->OpenProtocol (
                    Controller,
                    &gControllerDriverGuid,
                    (VOID **) &PrivateData,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );

    if (!EFI_ERROR (Status)) {
        gBS->UninstallMultipleProtocolInterfaces (
              Controller,
              &gControllerDriverGuid,
              PrivateData,
              &gEfiIdeControllerInitProtocolGuid,
              &(PrivateData->IdeInit),
              NULL
              );
    }

    //
    // Close protocols opened by Ide controller driver
    //
    gBS->CloseProtocol (
          Controller,
          &gEfiPciIoProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );

    if (PrivateData != NULL) {
        gBS->FreePool (PrivateData);
    }

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    This function can be used to obtain information about a specified channel.
    It's usually used by IDE Bus driver during enumeration process.


    @param This - the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
    @param Channel - Channel number (0 based, either 0 or 1)
    @param Enabled - TRUE if the channel is enabled. If the channel is disabled,
        then it will no be enumerated.
    @param MaxDevices - The Max number of IDE devices that the bus driver can expect
        on this channel. For ATA/ATAPI, this number is either 1 or 2.


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitGetChannelInfo (
  IN   EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN   UINT8                               Channel,
  OUT  BOOLEAN                             *Enabled,
  OUT  UINT8                               *MaxDevices
  )
{
    //
    // Channel number (0 based, either 0 or 1)
    //
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData;
    // unreadVariable warning happened under MARCO "ASSERT"(\MdePkg\Include\Library\DebugLib.h)
    // cppcheck-suppress unreadVariable
    PrivateData = SBIDE_CONTROLLER_PRIVATE_DATA_FROM_THIS (This);
    ASSERT (PrivateData);

    if (Channel < This->ChannelCount) {
        *Enabled    = TRUE;
        *MaxDevices = CONTROLLER_MAX_DEVICES;

        return EFI_SUCCESS;

    } else {
        *Enabled = FALSE;
        return EFI_INVALID_PARAMETER;
    }
}

//**********************************************************************
/**
    This function is called by IdeBus driver before executing certain actions.
    This allows IDE Controller Init to prepare for each action.


    @param This - the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
    @param Phase - phase indicator defined by IDE_CONTROLLER_INIT protocol
    @param Channel - Channel number (0 based, either 0 or 1)


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitNotifyPhase (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL  *This,
  IN  EFI_IDE_CONTROLLER_ENUM_PHASE     Phase,
  IN  UINT8                             Channel
  )
{
    if (Channel >= This->ChannelCount) {
        return EFI_INVALID_PARAMETER;
    }

    switch (Phase) {

    case EfiIdeBeforeChannelEnumeration:
    case EfiIdeAfterChannelEnumeration:
    case EfiIdeBeforeChannelReset:
    case EfiIdeAfterChannelReset:
    case EfiIdeBusBeforeDevicePresenceDetection:
    case EfiIdeBusAfterDevicePresenceDetection:
    case EfiIdeResetMode:
        //
        // Do nothing at present
        //
        break;

    default:
        return EFI_UNSUPPORTED;
        break;
    }

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    This function is called by IdeBus driver to submit EFI_IDENTIFY_DATA data structure
    obtained from IDE deivce. This structure is used to set IDE timing


    @param This - the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
    @param Channel - IDE channel number (0 based, either 0 or 1)
    @param Device - IDE device number
    @param IdentifyData - A pointer to EFI_IDENTIFY_DATA data structure


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitSubmitData (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN  UINT8                               Channel,
  IN  UINT8                               Device,
  IN  EFI_IDENTIFY_DATA                   *IdentifyData
  )
{
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData;
    PrivateData = SBIDE_CONTROLLER_PRIVATE_DATA_FROM_THIS (This);
    ASSERT (PrivateData);

    if ((Channel >= This->ChannelCount) || \
                            (Device >= CONTROLLER_MAX_DEVICES)) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Make a local copy of device's IdentifyData and mark the valid flag
    //
    if (IdentifyData != NULL) {
        gBS->CopyMem (
          &(PrivateData->IdentifyData[Channel][Device]),
          IdentifyData,
          sizeof (EFI_IDENTIFY_DATA)
          );

        PrivateData->IdentifyValid[Channel][Device] = TRUE;
    } else {
        PrivateData->IdentifyValid[Channel][Device] = FALSE;
    }

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    This function is called by IdeBus driver to disqualify unsupported operation
    mode on specfic IDE device


    @param This - the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
    @param Channel - IDE channel number (0 based, either 0 or 1)
    @param Device - IDE device number
    @param BadModes - Operation mode indicator


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitDisqualifyMode (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN  UINT8                               Channel,
  IN  UINT8                               Device,
  IN  EFI_ATA_COLLECTIVE_MODE             *BadModes
  )
{
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData;
    PrivateData = SBIDE_CONTROLLER_PRIVATE_DATA_FROM_THIS (This);
    ASSERT (PrivateData);

    if ((Channel >= This->ChannelCount) || \
        (BadModes == NULL) || (Device >= CONTROLLER_MAX_DEVICES)) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Record the disqualified modes per channel per device. From ATA/ATAPI spec,
    // if a mode is not supported, the modes higher than it is also not
    // supported
    //
    gBS->CopyMem (
      &(PrivateData->DisqulifiedModes[Channel][Device]),
      BadModes,
      sizeof (EFI_ATA_COLLECTIVE_MODE)
      );

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    This function is called by IdeBus driver to calculate the best operation mode
    supported by specific IDE device


    @param This - the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
    @param Channel - IDE channel number (0 based, either 0 or 1)
    @param Device - IDE device number
    @param SupportedModes - Modes collection supported by IDE device


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitCalculateMode (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL       *This,
  IN  UINT8                                  Channel,
  IN  UINT8                                  Device,
  IN OUT EFI_ATA_COLLECTIVE_MODE             **SupportedModes
  )
{
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData;
    EFI_IDENTIFY_DATA                   *IdentifyData;
    BOOLEAN                             IdentifyValid;
    EFI_ATA_COLLECTIVE_MODE             *DisqulifiedModes;
    UINT16                              SelectedMode;
    EFI_STATUS                          Status;

    PrivateData = SBIDE_CONTROLLER_PRIVATE_DATA_FROM_THIS (This);
    ASSERT (PrivateData);

    if ((Channel >= This->ChannelCount) || \
        (SupportedModes == NULL) || (Device >= CONTROLLER_MAX_DEVICES)) {
        return EFI_INVALID_PARAMETER;
    }

    *SupportedModes = MallocZ (sizeof (EFI_ATA_COLLECTIVE_MODE));

    IdentifyData      = &(PrivateData->IdentifyData[Channel][Device]);
    DisqulifiedModes  = &(PrivateData->DisqulifiedModes[Channel][Device]);
    IdentifyValid     = PrivateData->IdentifyValid[Channel][Device];

    //
    // Make sure we've got the valid identify data
    // of the device from SubmitData()
    //
    if (!IdentifyValid) {
        return EFI_NOT_READY;
    }

    Status = CalculateBestPioMode (
              IdentifyData,
              (DisqulifiedModes->PioMode.Valid ?\
                ((UINT16 *) &(DisqulifiedModes->PioMode.Mode)) : NULL),
              &SelectedMode
              );
    if (!EFI_ERROR (Status)) {
        (*SupportedModes)->PioMode.Valid  = TRUE;
        (*SupportedModes)->PioMode.Mode   = SelectedMode;

    } else {
        (*SupportedModes)->PioMode.Valid = FALSE;
    }

    Status = CalculateBestUdmaMode (
              IdentifyData,
              (DisqulifiedModes->UdmaMode.Valid ? \
                ((UINT16 *) &(DisqulifiedModes->UdmaMode.Mode)) : NULL),
              &SelectedMode
              );

    if (!EFI_ERROR (Status)) {
        (*SupportedModes)->UdmaMode.Valid = TRUE;
        (*SupportedModes)->UdmaMode.Mode  = SelectedMode;

    } else {
        (*SupportedModes)->UdmaMode.Valid = FALSE;
    }

    //
    // User select IDE mode
    //
    UserIdeMode(&gSetupData, Channel, Device, SupportedModes);

    //
    // The modes other than PIO and UDMA are not supported by Ide controller
    //
    return EFI_SUCCESS;
}


//**********************************************************************
/**
    This function is called by IdeBus driver to set appropriate timing on IDE
    controller according supported operation mode


    @param This - the EFI_IDE_CONTROLLER_INIT_PROTOCOL instance.
    @param Channel - IDE channel number (0 based, either 0 or 1)
    @param Device - IDE device number
    @param Modes


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
IdeInitSetTiming (
  IN  EFI_IDE_CONTROLLER_INIT_PROTOCOL    *This,
  IN  UINT8                               Channel,
  IN  UINT8                               Device,
  IN  EFI_ATA_COLLECTIVE_MODE             *Modes
  )
{
    EFI_SBIDE_CONTROLLER_PRIVATE_DATA   *PrivateData;
    PrivateData = SBIDE_CONTROLLER_PRIVATE_DATA_FROM_THIS (This);
    ASSERT (PrivateData);

    if ((Channel >= This->ChannelCount) || \
            (Modes == NULL) || (Device >= CONTROLLER_MAX_DEVICES)) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Make sure we've got the valid identify data of the device
    // from SubmitData()
    //
    if (!(PrivateData->IdentifyValid[Channel][Device]) ) {
        return EFI_NOT_READY;
    }

    //
    // Only PIO mode and UDMA mode are supported
    //

    //if UDMA is supported, Set UDMA Mode
//    if (Modes->UdmaMode.Valid) {
//        IdeInitSetUdmaTiming (Channel, Device, PrivateData->PciIo, Modes);
//    }

//;<JohnZhang Debug Begin ----->
//    //If PIO is supported, Set PIO Mode
//    if (Modes->PioMode.Valid) {
//        IdeInitSetPioTiming(Channel, Device, PrivateData->PciIo, &(PrivateData->IdentifyData[Channel][Device]), Modes);
//    }
//;<JohnZhang Debug End   <-----

//    //If Pio and UDMA are not supported, return EFI_UNSUPPORTED
//    if ((!Modes->PioMode.Valid) && (!Modes->UdmaMode.Valid)) {
//        return EFI_UNSUPPORTED;
//    }

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    This function is used to calculate the best PIO mode supported by
    specific IDE device


    @param IdentifyData The identify data of specific IDE device
    @param DisPioMode OPTIONAL   - Disqualified PIO modes collection
    @param SelectedMode Available PIO modes collection


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
CalculateBestPioMode (
  IN  EFI_IDENTIFY_DATA    * IdentifyData,
  IN  UINT16               *DisPioMode OPTIONAL,
  OUT UINT16               *SelectedMode
  )
{
    UINT16  PioMode;
    UINT16  AdvancedPioMode;
    UINT16  Temp;
    UINT16  Index;
    UINT16  MinimumPioCycleTime;

    Temp    = 0xff;

    //######  PioMode = (UINT8) (IdentifyData->AtaData.pio_cycle_timing >> 8);
    //###### no such item in MdePkg use following item instead.
    PioMode = (UINT8) (IdentifyData->AtaData.obsolete_51_52[0] >> 8);

    //
    // see whether Identify Data word 64 - 70 are valid
    //
    if ((IdentifyData->AtaData.field_validity & 0x02) == 0x02) {

        AdvancedPioMode = IdentifyData->AtaData.advanced_pio_modes;

        for (Index = 0; Index < 8; Index++) {
            if ((AdvancedPioMode & 0x01) != 0) {
                Temp = Index;
            }

            AdvancedPioMode >>= 1;
        }

        //
        // if Temp is modified, meant the advanced_pio_modes is not zero;
        // if Temp is not modified, meant the no advanced
        // PIO Mode is supported,
        // the best PIO Mode is the value in pio_cycle_timing.
        //
        if (Temp != 0xff) {
            AdvancedPioMode = (UINT16) (Temp + 3);
        } else {
            AdvancedPioMode = PioMode;
        }

        //
        // Limit the PIO mode to at most PIO4.
        //
        PioMode = (UINT16) (AdvancedPioMode < 4 ? AdvancedPioMode : 4);

        MinimumPioCycleTime = \
            IdentifyData->AtaData.min_pio_cycle_time_with_flow_control;

        if (MinimumPioCycleTime <= 120) {
            PioMode = (UINT16) (4 < PioMode ? 4 : PioMode);
        } else if (MinimumPioCycleTime <= 180) {
            PioMode = (UINT16) (3 < PioMode ? 3 : PioMode);
        } else if (MinimumPioCycleTime <= 240) {
            PioMode = (UINT16) (2 < PioMode ? 2 : PioMode);
        } else {
            PioMode = 0;
        }

        //
        // Degrade the PIO mode if the mode has been disqualified
        //
        if (DisPioMode != NULL) {

          if (*DisPioMode < 2) {
                return EFI_UNSUPPORTED; // no mode below ATA_PIO_MODE_BELOW_2
          }

          if (PioMode >= *DisPioMode) {
                PioMode = (UINT16)(*DisPioMode - 1);
          }
        }

        if (PioMode < 2) {
            *SelectedMode = 1;       // ATA_PIO_MODE_BELOW_2;

        } else {
            *SelectedMode = PioMode; // ATA_PIO_MODE_2 to ATA_PIO_MODE_4;
        }

    } else {
        //
        // Identify Data word 64 - 70 are not valid
        // Degrade the PIO mode if the mode has been disqualified
        //
        if (DisPioMode != NULL) {

          if (*DisPioMode < 2) {
                return EFI_UNSUPPORTED; // no mode below ATA_PIO_MODE_BELOW_2
          }

          if (PioMode == *DisPioMode) {
                PioMode--;
          }
        }

        if (PioMode < 2) {
            *SelectedMode = 1; // ATA_PIO_MODE_BELOW_2;
        } else {
            *SelectedMode = 2; // ATA_PIO_MODE_2;
        }

    }

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    This function is used to calculate the best UDMA mode supported by
    specific IDE device


    @param IdentifyData The identify data of specific IDE device
    @param DisUDmaMode OPTIONAL  - Disqualified UDMA modes collection
    @param SelectedMode Available UMDA modes collection


    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
//**********************************************************************
EFI_STATUS
CalculateBestUdmaMode (
  IN  EFI_IDENTIFY_DATA    * IdentifyData,
  IN  UINT16               *DisUDmaMode OPTIONAL,
  OUT UINT16               *SelectedMode
  )
{
    UINT16  TempMode;
    UINT16  DeviceUDmaMode;

    DeviceUDmaMode = 0; // flag for 'Udma mode is not supported'

    //
    // Check whether the WORD 88 (supported UltraDMA by drive) is valid
    //
    if ((IdentifyData->AtaData.field_validity & 0x04) == 0x00) {
        return EFI_UNSUPPORTED;
    }

    DeviceUDmaMode = IdentifyData->AtaData.ultra_dma_mode;
    DeviceUDmaMode &= 0x7f;
    TempMode        = 0; // initialize it to UDMA-0

    while ((DeviceUDmaMode >>= 1) != 0) {
        TempMode++;
    }

    //
    // Degrade the UDMA mode if the mode has been disqualified
    //
    if (DisUDmaMode != NULL) {
        if (*DisUDmaMode == 0) {
            *SelectedMode = 0;
            return EFI_UNSUPPORTED; // no mode below ATA_UDMA_MODE_0
        }

        if (TempMode >= *DisUDmaMode) {
            TempMode = (UINT16) (*DisUDmaMode - 1);
        }
    }

    //
    // Possible returned mode is between ATA_UDMA_MODE_0 and ATA_UDMA_MODE_5
    //
    *SelectedMode = TempMode;

    return EFI_SUCCESS;
}

//**********************************************************************
/**
    Saves the IDE registers in a boot script

    @param Event signalled event
    @param Context calling context


    @retval VOID
**/
//**********************************************************************
VOID MultiCallBack(IN EFI_EVENT Event, IN VOID *Context)
{
    EFI_STATUS                      Status;

    if (gPciRootBridgeIo == NULL) {
        Status = gBS->LocateProtocol(
                            &gEfiPciRootBridgeIoProtocolGuid,
                            NULL,
                            &gPciRootBridgeIo
                            );
        ASSERT_EFI_ERROR(Status);
    }

    if (gBootScriptSave == NULL) {
        Status = gBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
                    &gBootScriptSave);
        ASSERT_EFI_ERROR(Status);
    }


    if (Event == gPciIoEvent) {
        PciIoCallBackScriptSave();
    }

    if (Event == gReadyToBootEvent) {
        // save other register here when ready to boot
        ReadyToBootCallBackScriptSave();
    }

    gBS->CloseEvent(Event);
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
