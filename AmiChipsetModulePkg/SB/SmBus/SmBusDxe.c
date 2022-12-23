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

//*************************************************************************
/** @file SmBusDxe.c
    SMBUS DXE functions implementation

**/
//*************************************************************************

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include "Token.h"
#include <Guid/AmiCspHobs.h>
#include "SmBusDxe.h"
#include <Protocol/PciRootBridgeIo.h>               // (EIP54380+)
#include <Protocol/DriverBinding.h>                 // gEfiDriverBindingProtocolGuid
#include <AmiChipsetIoLib.h>
#include <Sb.h>
#include <Library/SbCspLib.h>
#include <Library/SmBusCommon.h>

#include <Library/DebugLib.h>

#include <Library/UefiBootServicesTableLib.h>

#define MICROSECOND     10
#define MILLISECOND     (1000 * MICROSECOND)
#define ONESECOND       (1000 * MILLISECOND)

extern EFI_GUID SmBusIdentifierGuid;

EFI_HANDLE 						gControllerHandle;  // (EIP54380+)
SMBUS_DXE_PRIVATE               *gPrivate;          // (EIP54380+)

#if (ASF_INSTANCE != 0)
SMBUS_DXE_PRIVATE               *gPrivateDash = NULL;
#define ASF_SIGNATURE_GUID {0xc79f083d, 0x66e0, 0x4c5f, 0xa7, 0x2a, 0x6e, 0xa2, 0x84, 0xb5, 0x6f, 0x4a}
static EFI_GUID    gAsfSignatureGuid = ASF_SIGNATURE_GUID;
#endif

EFI_DRIVER_BINDING_PROTOCOL SmBusDriverBindingProtocol = {
    DriverBindingSupported,
    DriverBindingStart,
    DriverBindingStop,
    0x10,
    NULL,
    NULL
    };

// (EIP54380)>
/**
    This function configures and installs SMBUS protocol before
    SMBus EFI 1.1 drvier is installed.

    @param VOID

               
    @retval EFI_SUCCESS SMBUS protocol has been installed.
**/

EFI_STATUS SmBusEarlyDxeDriver ( VOID )
{
    EFI_STATUS                      Status;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *PciRootBridgeIo = NULL;
    UINT16                          Cmd16;

    Status = gBS->AllocatePool( EfiBootServicesData, \
                                sizeof(SMBUS_DXE_PRIVATE), \
                                &gPrivate );
    if (EFI_ERROR(Status)) return Status;

    Status = gBS->AllocatePool( \
                        EfiBootServicesData, \
                        sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_DXE_ARP_DEVICES, \
                        &(gPrivate->SmBusContext.ArpDeviceList) );
    if (EFI_ERROR(Status)) {
        gBS->FreePool( gPrivate );
        return Status;
    }

#if (ASF_INSTANCE != 0)
    Status = gBS->AllocatePool( EfiBootServicesData, \
                                sizeof(SMBUS_DXE_PRIVATE), \
                                &gPrivateDash );

    if (EFI_ERROR(Status)) return Status;



    Status = gBS->AllocatePool( \
                        EfiBootServicesData, \
                        sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_DXE_ARP_DEVICES, \
                        &(gPrivateDash->SmBusContext.ArpDeviceList) );

    if (EFI_ERROR(Status)) {
        gBS->FreePool( gPrivateDash );
        return Status;
    }
#endif

    gPrivate->SmBusProtocol.Execute   = SmBusDxeExecute;
    gPrivate->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    gPrivate->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    gPrivate->SmBusProtocol.Notify    = SmBusDxeNotify;

    gPrivate->NotifyEvent = NULL;
    gPrivate->Identifier = SmBusIdentifierGuid;

    gPrivate->SmBusContext.SmBusWait = SmBusDxeWait;
    gPrivate->SmBusContext.MaxDevices = MAX_DXE_ARP_DEVICES;
    RetrieveHobData( gPrivate );

#if (ASF_INSTANCE != 0)
    gPrivateDash->SmBusProtocol.Execute   = SmBusDxeExecute;
    gPrivateDash->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    gPrivateDash->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    gPrivateDash->SmBusProtocol.Notify    = SmBusDxeNotify;

    gPrivateDash->NotifyEvent = NULL;
    gPrivateDash->Identifier = SmBusIdentifierGuid;

    gPrivateDash->SmBusContext.SmBusWait = SmBusDxeWait;
    gPrivateDash->SmBusContext.MaxDevices = MAX_DXE_ARP_DEVICES;
    RetrieveHobData( gPrivateDash );
    gPrivateDash->SmBusContext.SmBusBase = SMBUS1_BASE_ADDRESS ; //SMBUS_BASE_ADDRESS + 0x20
#endif

    Status = gBS->LocateProtocol( &gEfiPciRootBridgeIoProtocolGuid, \
                                  NULL, \
                                  &PciRootBridgeIo );

    ASSERT_EFI_ERROR(Status);

    gPrivate->SmBusContext.SmBusBase = SMBUS_BASE_ADDRESS;

    // Enable SMBus controller I/O decode.
    PciRootBridgeIo->Pci.Read( PciRootBridgeIo, \
                               EfiPciWidthUint16, \
                               SMBUS_REG(SMBUS_REG_PCICMD), \
                               1, \
                               &Cmd16 );
    Cmd16 |= 1;
    PciRootBridgeIo->Pci.Write( PciRootBridgeIo, \
                                EfiPciWidthUint16, \
                                SMBUS_REG(SMBUS_REG_PCICMD), \
                                1, \
                                &Cmd16 );

    Status = gBS->InstallProtocolInterface( &gControllerHandle, \
                                            &gEfiSmbusHcProtocolGuid, \
                                            EFI_NATIVE_INTERFACE,
                                            &gPrivate->SmBusProtocol );
    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "SBSmbusDxe: Install Protocol Interface Failed.\n"));
    }

#if (ASF_INSTANCE != 0)
    Status = gBS->InstallProtocolInterface( &gControllerHandle, \
                                            &gAsfSignatureGuid, \
                                            EFI_NATIVE_INTERFACE,
                                            &gPrivateDash->SmBusProtocol );

    if (EFI_ERROR(Status)) {
        DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET, "AsfSignature: Install Protocol Interface Failed.\n"));
    }
#endif

    return Status;
}
// <(EIP54380)

/**
    This Protocol Function can be used to execute SMBus command
    on a particular SMBus controller in SMM.

    @param This Pointer to the SMBus Protocol structure
    @param SlaveAddress Address of the SMBus device
    @param Command Command to be sent to the device
    @param Operation SMBus operation to be performed
    @param PecCheck Flag indicating the usage of PEC
    @param Length Length of the data in the Buffer (IN or OUT)
    @param Buffer Pointer to the buffer with the data (IN or OUT)

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  PORTING REQUIRED
**/

EFI_STATUS SmBusSmmExecute (
    IN EFI_SMBUS_HC_PROTOCOL            *This,
    IN EFI_SMBUS_DEVICE_ADDRESS         SlaveAddress,
    IN EFI_SMBUS_DEVICE_COMMAND         Command,
    IN EFI_SMBUS_OPERATION              Operation,
    IN BOOLEAN                          PecCheck,
    IN OUT UINTN                        *Length,
    IN OUT VOID                         *Buffer )
{
    UINT16      PciCmd,PciCmdTemp;

    EFI_STATUS  Status = EFI_SUCCESS;

    // Get current SMBUS Base address.
#if (ASF_INSTANCE != 0)
    gPrivateDash->SmBusContext.SmBusBase = SMBUS1_BASE_ADDRESS ;
#else
    gPrivate->SmBusContext.SmBusBase = SMBUS_BASE_ADDRESS;
#endif

    // Save SMBUS PCI Command Register (Offset 04) - Enable SMBUS IO Space.
    PciCmd = READ_PCI16_SMBUS(SMBUS_REG_PCICMD);
    PciCmdTemp = PciCmd | BIT00;
    WRITE_PCI16_SMBUS(SMBUS_REG_PCICMD,PciCmdTemp );

    Status = Execute( &(((SMBUS_DXE_PRIVATE *)This)->SmBusContext), \
                    SlaveAddress, \
                    Command, \
                    Operation, \
                    PecCheck, \
                    Length, \
                    Buffer );

    // Restore the SMBUS PCI Command Register.
    WRITE_PCI16_SMBUS(SMBUS_REG_PCICMD, PciCmd);

    return EFI_SUCCESS;
}

#ifdef _AUTOGENH_BA28936B_4051_48cf_A5CD_B63D7BFCA84A // SmBusDxe
#else // if not SmBusDxe
#include <Library/AmiCspSmmServicesLib.h>
/**
    This function installs SMBus SMM protocol for the SMBus
    controller present in the SB.

    @param ImageHandle Image handle for the SB component
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  GENERALLY NO PORTING REQUIRED
**/
EFI_STATUS
EFIAPI
SmBusInSmmInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_HANDLE                  Handle = NULL;
    EFI_GUID                    SmmSmbusProtocolGuid = \
                                                AMI_SMBUS_SMM_PROTOCOL_GUID;

#if (ASF_INSTANCE != 0)
    static SMBUS_DXE_PRIVATE    SmbusSmmPrivateDash;
    gPrivateDash = &SmbusSmmPrivateDash;
    // Porting Required
    gPrivateDash->SmBusProtocol.Execute   = SmBusSmmExecute;
    gPrivateDash->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    gPrivateDash->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    gPrivateDash->SmBusProtocol.Notify    = SmBusDxeNotify;
    gPrivateDash->SmBusContext.SmBusWait  = SmBusDxeSmmWait;

    return gSmst->SmmInstallProtocolInterface( &Handle,
                                          &SmmSmbusProtocolGuid,
                                          EFI_NATIVE_INTERFACE,
                                          &gPrivateDash->SmBusProtocol );
#else
    static SMBUS_DXE_PRIVATE    SmbusSmmPrivate;
    gPrivate = &SmbusSmmPrivate;
    // Porting Required
    gPrivate->SmBusProtocol.Execute   = SmBusSmmExecute;
    gPrivate->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    gPrivate->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    gPrivate->SmBusProtocol.Notify    = SmBusDxeNotify;
    gPrivate->SmBusContext.SmBusWait  = SmBusDxeSmmWait;

    return gSmst->SmmInstallProtocolInterface( &Handle,
                                          &SmmSmbusProtocolGuid,
                                          EFI_NATIVE_INTERFACE,
                                          &gPrivate->SmBusProtocol );
#endif

}
#endif // #else _AUTOGENH_BA28936B_4051_48cf_A5CD_B63D7BFCA84A // SmBusDxe

/**
    This function installs SMBus DXE protocol for the SMBus
    controller present in the SB.

    @param ImageHandle Image handle for the SB component
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  GENERALLY NO PORTING REQUIRED
**/

EFI_STATUS
EFIAPI
SmBusNotInSmmInit (
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
    EFI_STATUS Status;


    Status = SmBusEarlyDxeDriver();                 // (EIP54380+)

#if SMBUS_BLINDING_PROTOCOL_SUPPORT                 // (EIP54380+)
    SmBusDriverBindingProtocol.ImageHandle = ImageHandle;
    SmBusDriverBindingProtocol.DriverBindingHandle = ImageHandle;
    Status = gBS->InstallMultipleProtocolInterfaces( \
                                             &ImageHandle, \
                                             &gEfiDriverBindingProtocolGuid, \
                                             &SmBusDriverBindingProtocol, \
                                             NULL );
#endif
    return Status;
}

/**
    This function installs SMBus DXE/SMM protocols for the SMBus
    controller present in the SB.

    @param ImageHandle Image handle for the SB component
    @param SystemTable Pointer to the system table

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SmBusDxeEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable )
{
#ifdef _AUTOGENH_BA28936B_4051_48cf_A5CD_B63D7BFCA84A // SmBusDxe
	return SmBusNotInSmmInit(ImageHandle, SystemTable);
#else // SmBusSmm
    return CspInitSmmHandler ( ImageHandle, \
                               SystemTable, \
                               SmBusInSmmInit);
#endif
}

/**
    SMBUS DXE Driver binding protocol Supported function

    @param This pointer to EFI_DRIVER_BINDING_PROTOCOL structure
    @param ControllerHandle handle of controller to serve
    @param RemainingDevicePath pointer to EFI_DEVICE_PATH_PROTOCOL structure

    @retval EFI_SUCCESS driver supports given controller
    @retval EFI_UNSUPPORTED given controller not supported

**/
EFI_STATUS
EFIAPI 
DriverBindingSupported ( 
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
    EFI_STATUS          Status;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINT8               PciData[4];

    Status = gBS->OpenProtocol (
                            ControllerHandle,
                            &gEfiPciIoProtocolGuid,
                            (VOID **) &PciIo,
                            This->DriverBindingHandle,
                            ControllerHandle,
                            EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR (Status))
        return EFI_UNSUPPORTED;

  //
  // See if this is a PCI Smbus Controller by looking at the Class Code Register
  //
    Status = PciIo->Pci.Read (
                            PciIo,
                            EfiPciIoWidthUint32,
                            0x8,
                            1,
                            (VOID *)PciData );
    if (EFI_ERROR (Status))
        return EFI_UNSUPPORTED;

    gBS->CloseProtocol (
         ControllerHandle,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         ControllerHandle );

    return (PciData[3] == 0x0c && PciData[2] == 0x05) ? EFI_SUCCESS : EFI_UNSUPPORTED;
}

/**
    SMBUS DXE Driver binding protocol Start function

    @param This pointer to EFI_DRIVER_BINDING_PROTOCOL structure
    @param ControllerHandle handle of controller to serve
    @param RemainingDevicePath pointer to EFI_DEVICE_PATH_PROTOCOL structure

    @retval EFI_SUCCESS driver supports given controller
    @retval EFI_UNSUPPORTED given controller not supported

**/
EFI_STATUS
EFIAPI 
DriverBindingStart ( 
    IN EFI_DRIVER_BINDING_PROTOCOL    *This,
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
)
{
    EFI_STATUS Status;
    SMBUS_DXE_PRIVATE *Private;

    // (EIP54380)>
    static BOOLEAN          EarlyDxeProtocol = TRUE;

    if (EarlyDxeProtocol) {
        Status = gBS->UninstallProtocolInterface( gControllerHandle, \
                                                  &gEfiSmbusHcProtocolGuid, \
                                                  &gPrivate->SmBusProtocol );
        if (Status == EFI_SUCCESS) {
            gBS->FreePool( gPrivate->SmBusContext.ArpDeviceList );
            gBS->FreePool( gPrivate );
        }
        EarlyDxeProtocol = FALSE;
    }
    // <(EIP54380)

    Status = gBS->AllocatePool(EfiBootServicesData,
                               sizeof(SMBUS_DXE_PRIVATE),
                               &Private);
    if(EFI_ERROR(Status))
        return Status;

    Status = gBS->AllocatePool(EfiBootServicesData,
                               sizeof(EFI_SMBUS_DEVICE_MAP) * MAX_DXE_ARP_DEVICES,
                               &(Private->SmBusContext.ArpDeviceList));
    if(EFI_ERROR(Status))
        return Status;

    Status = gBS->OpenProtocol (
                            ControllerHandle,
                            &gEfiPciIoProtocolGuid,
                            (VOID **) &(Private->PciIo),
                            This->DriverBindingHandle,
                            ControllerHandle,
                            EFI_OPEN_PROTOCOL_BY_DRIVER );
    if (EFI_ERROR (Status))
    {
        gBS->FreePool(Private->SmBusContext.ArpDeviceList);
        gBS->FreePool(Private);
        return Status;
    }

    Private->SmBusProtocol.Execute   = SmBusDxeExecute;
    Private->SmBusProtocol.ArpDevice = SmBusDxeArpDevice;
    Private->SmBusProtocol.GetArpMap = SmBusDxeGetArpMap;
    Private->SmBusProtocol.Notify    = SmBusDxeNotify;

    Private->NotifyEvent = NULL;
    Private->Identifier = SmBusIdentifierGuid;

    Private->SmBusContext.SmBusWait = SmBusDxeWait;
    Private->SmBusContext.MaxDevices = MAX_DXE_ARP_DEVICES;
    RetrieveHobData(Private);


    Private->SmBusContext.SmBusBase = SMBUS_BASE_ADDRESS;//SMBUS_BASE_ADDRESS;

    DListInit(&(Private->NotifyList));

    Status = gBS->InstallMultipleProtocolInterfaces(
                    &ControllerHandle,
                    &gEfiSmbusHcProtocolGuid, &Private->SmBusProtocol,
                    NULL);
    if (EFI_ERROR (Status))
    {
        gBS->CloseProtocol(
                        ControllerHandle,
                        &gEfiPciIoProtocolGuid,
                        This->DriverBindingHandle,
                        ControllerHandle );
        gBS->FreePool(Private->SmBusContext.ArpDeviceList);
        gBS->FreePool(Private);
    }
    return Status;
}

/**
    SMBUS DXE Driver binding protocol Stop function

    @param This pointer to EFI_DRIVER_BINDING_PROTOCOL structure
    @param ControllerHandle handle of controller to serve
    @param NumberOfChildren number of child devices of controller
    @param ChildHandleBuffer pointer to child devices handles array

    @retval EFI_SUCCESS driver was successfully uninstalled from controller

**/
EFI_STATUS
EFIAPI 
DriverBindingStop ( 
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN  UINTN                       NumberOfChildren,
    IN  EFI_HANDLE                  *ChildHandleBuffer
)
{
    EFI_STATUS              Status;
    SMBUS_DXE_PRIVATE       *Private;
    EFI_SMBUS_HC_PROTOCOL   *SmBusProtocol;

    Status = gBS->OpenProtocol (
                        ControllerHandle,
                        &gEfiSmbusHcProtocolGuid,
                        &SmBusProtocol,
                        This->DriverBindingHandle,
                        ControllerHandle,
                        EFI_OPEN_PROTOCOL_GET_PROTOCOL );
    if (EFI_ERROR (Status))
        return EFI_NOT_STARTED;

    gBS->CloseProtocol (
                    ControllerHandle,
                    &gEfiSmbusHcProtocolGuid,
                    This->DriverBindingHandle,
                    ControllerHandle );

    Private = (SMBUS_DXE_PRIVATE *) SmBusProtocol;

    // uninstall the protocol
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    ControllerHandle,
                    &gEfiSmbusHcProtocolGuid, &Private->SmBusProtocol,
                    NULL );
    if (EFI_ERROR (Status))
        return Status;

    if(Private->NotifyEvent != 0)
    {
        SMBUS_NOTIFY_LINK *NotifyLink = (SMBUS_NOTIFY_LINK *)(Private->NotifyList.pHead);
        SMBUS_NOTIFY_LINK *DeleteLink;

        gBS->CloseEvent(Private->NotifyEvent);
        while(NotifyLink != 0)
        {
            DeleteLink = NotifyLink;
            NotifyLink = (SMBUS_NOTIFY_LINK *)NotifyLink->Link.pNext;
            gBS->FreePool(DeleteLink);
        }
    }

    gBS->CloseProtocol (
                    ControllerHandle,
                    &gEfiPciIoProtocolGuid,
                    This->DriverBindingHandle,
                    ControllerHandle );
    gBS->FreePool(Private->SmBusContext.ArpDeviceList);
    gBS->FreePool(Private);

    return EFI_SUCCESS;
}

/**
    EFI_SMBUS_HC_PROTOCOL Execute function

    @param This pointer to EFI_SMBUS_HC_PROTOCOL structure
    @param SlaveAddress slave address
    @param Command command
    @param Operation operation
    @param PecCheck parity check flag
    @param Length pointer to size of data buffer
    @param Buffer pointer to data buffer

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SmBusDxeExecute (
    IN CONST  EFI_SMBUS_HC_PROTOCOL         *This,
    IN        EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
    IN        EFI_SMBUS_DEVICE_COMMAND      Command,
    IN        EFI_SMBUS_OPERATION           Operation,
    IN        BOOLEAN                       PecCheck,
    IN OUT    UINTN                         *Length,
    IN OUT    VOID                          *Buffer
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;

    return Execute(
                &(Private->SmBusContext),
                SlaveAddress,
                Command,
                Operation,
                PecCheck,
                Length,
                Buffer);
}

/**
    EFI_SMBUS_HC_PROTOCOL ArpDevice function

    @param This pointer to EFI_SMBUS_HC_PROTOCOL structure
    @param ArpAll Enumerate all devices flag
    @param SmbusUdid OPTIONAL- pointer to device ID to assign new address
    @param SlaveAddress OPTIONAL - pointer to return assigned address

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SmBusDxeArpDevice (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN      BOOLEAN                       ArpAll,
    IN      EFI_SMBUS_UDID                *SmbusUdid, OPTIONAL
    IN OUT  EFI_SMBUS_DEVICE_ADDRESS      *SlaveAddress OPTIONAL
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;

    return ArpDevice(
                &(Private->SmBusContext),
                ArpAll,
                SmbusUdid,
                SlaveAddress);
}

/**
    EFI_SMBUS_HC_PROTOCOL GetArpMap function

    @param This pointer to EFI_SMBUS_HC_PROTOCOL structure
    @param Length pointer to store size of address map
    @param SmbusDeviceMap pointer to store pointer to address map

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SmBusDxeGetArpMap (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN OUT  UINTN                         *Length,
    IN OUT  EFI_SMBUS_DEVICE_MAP          **SmbusDeviceMap
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;

    return GetArpMap(
                &(Private->SmBusContext),
                Length,
                SmbusDeviceMap);
}

/**
    EFI_SMBUS_HC_PROTOCOL Notify function

    @param This pointer to EFI_SMBUS_HC_PROTOCOL structure
    @param SlaveAddress address of notification device
    @param Data notification data
    @param NotifyFunction pointer to callback function

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS SmBusDxeNotify (
    IN      EFI_SMBUS_HC_PROTOCOL         *This,
    IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
    IN      UINTN                         Data,
    IN      EFI_SMBUS_NOTIFY_FUNCTION     NotifyFunction
)
{
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)This;
    SMBUS_NOTIFY_LINK *NewLink;
    EFI_STATUS        Status;

    if(NotifyFunction == NULL)
        return EFI_INVALID_PARAMETER;

    Status = gBS->AllocatePool(EfiBootServicesData, sizeof(SMBUS_NOTIFY_LINK), &NewLink);
    if(EFI_ERROR(Status))
        return Status;

    NewLink->SlaveAddress   = SlaveAddress;
    NewLink->Data           = Data;
    NewLink->NotifyFunction = NotifyFunction;

    DListAdd(&(Private->NotifyList), (DLINK *)NewLink);
    if(Private->NotifyList.Size == 1)
        Status = InitializeNotifyPolling(Private);

    return Status;
}

/**
    Function initializes host notify polling periodic event

    @param Context pointer to SMBUS device private data

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS InitializeNotifyPolling (
    IN SMBUS_DXE_PRIVATE *Context
)
{
    EFI_STATUS Status;

    Status = gBS->CreateEvent (
                  (EFI_EVENT_TIMER | EFI_EVENT_NOTIFY_SIGNAL),
                  TPL_CALLBACK,
                  PollSmbusNotify,
                  Context,
                  &Context->NotifyEvent );
    if (EFI_ERROR(Status))
        return Status;

    Status = gBS->SetTimer (
                  Context->NotifyEvent,
                  TimerPeriodic,
                  ONESECOND );
    if (EFI_ERROR(Status))
        return Status;

    return EFI_SUCCESS;
}

/**
    Function performs periodic check of host notifications

    @param Event periodic check event
    @param Context event calling context

    @retval VOID

**/
VOID PollSmbusNotify (
    IN  EFI_EVENT Event,
    IN  VOID      *Context
)
{
    EFI_STATUS Status;
    EFI_SMBUS_DEVICE_ADDRESS Address;
    UINTN Data;
    SMBUS_DXE_PRIVATE *Private = (SMBUS_DXE_PRIVATE *)Context;
    SMBUS_NOTIFY_LINK *NotifyLink = (SMBUS_NOTIFY_LINK *)(Private->NotifyList.pHead);

    Status = CheckNotify(&(Private->SmBusContext), &Address, &Data);
    if (EFI_ERROR(Status))
        return;

    while(NotifyLink != NULL)
    {
        if(Address.SmbusDeviceAddress == NotifyLink->SlaveAddress.SmbusDeviceAddress && \
           Data == NotifyLink->Data)
            NotifyLink->NotifyFunction(Address, Data);

        NotifyLink = (SMBUS_NOTIFY_LINK *)NotifyLink->Link.pNext;
    }
}

//-------------------------------------------------------------------
// Struct EFI_SMBUS_DEVICE_MAP has one member, that declared as UINTN
// Due to this declaration this struct may have different size if
// compiled in x64 mode - 4 bytes in PEI and 8 bytes in DXE
// So we need mediator structure, to convert from PEI to DXE map, that
// was saved in Hob in PEI phase
//-------------------------------------------------------------------

#pragma pack(1)
typedef struct {
    UINT32  Address;
    EFI_SMBUS_UDID Udid;
} PEI_EFI_SMBUS_DEVICE_MAP;
#pragma pack()

/**
    Function reads device map created in PEI phase

    @param Private pointer to device private data

    @retval VOID

**/
VOID RetrieveHobData (
    IN OUT SMBUS_DXE_PRIVATE *Private
)
{
    AMI_CSP_SMBUS_HOB *Hob;
    EFI_GUID      HobListGuid = HOB_LIST_GUID;
    EFI_STATUS    Status;
    SMBUS_PRIVATE *Context = &(Private->SmBusContext);

    PEI_EFI_SMBUS_DEVICE_MAP *PeiMap;
    UINT32 i;

    Context->BoardReservedAddressCount = 0;
    Context->BoardReservedAddressList = 0;
    Context->ArpDeviceCount = 0;

    Hob = (AMI_CSP_SMBUS_HOB *)GetEfiConfigurationTable(gST, &HobListGuid);

    if(Hob == NULL)
        return;

    Status = FindNextHobByGuid(&(Private->Identifier), &Hob);
    if(EFI_ERROR(Status))
        return;

    Context->BoardReservedAddressCount = Hob->BoardReservedAddressCount;
                                                        // (P20101202A)>
//####    Context->BoardReservedAddressList = Hob->BoardReservedAddressList;
    Context->BoardReservedAddressList = (UINT8*)Hob->BoardReservedAddressList;
                                                        // <(P20101202A)
    Context->ArpDeviceCount = Hob->ArpDeviceCount;

    PeiMap = (PEI_EFI_SMBUS_DEVICE_MAP *)Hob->ArpDeviceList;
    for(i = 0; i < Hob->ArpDeviceCount; i++)
    {
        Context->ArpDeviceList[i].SmbusDeviceAddress.SmbusDeviceAddress = PeiMap[i].Address;
        Context->ArpDeviceList[i].SmbusDeviceUdid = PeiMap[i].Udid;
    }
/*
    MemCpy(Context->ArpDeviceList,
           Hob->ArpDeviceList,
           Context->ArpDeviceCount * sizeof(EFI_SMBUS_DEVICE_MAP));
*/
}

//**********************************************************************
//                  Porting functions
//**********************************************************************

/**
    This function waits given number of microseconds

    @param This 
    @param Microseconds number of microseconds to wait

    @retval VOID

    @note  Porting required

**/
VOID SmBusDxeSmmWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds   //count in 15microsec
    )
{
    UINT8   Reference = IoRead8(0x61) & 0x10;
    UINT8   Current;

    while(Microseconds)
    {
        Current = IoRead8(0x61) & 0x10;
        if (Reference != Current)
        {
            Reference = Current;
            Microseconds--;
        }
    }

}

/**
    This function waits given number of microseconds

    @param This 
    @param Microseconds number of microseconds to wait

    @retval VOID

    @note  Porting required

**/
VOID SmBusDxeWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds
    )
{
    gBS->Stall(Microseconds);
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
