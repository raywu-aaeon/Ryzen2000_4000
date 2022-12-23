//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file EfiUsbCcid.c
    USB CCID EFI driver implementation

**/

#include <AmiUsbRtCcid.h>
#include "AmiUsbSmartCardReader.h"


USB_GLOBAL_DATA        gUsbCcidData;
USB_GLOBAL_DATA        *gUsbData = &gUsbCcidData;
USB_DATA_LIST          gUsbCcidDataList;
USB_DATA_LIST          *gUsbDataList = &gUsbCcidDataList;
URP_STRUC              gUsbUrp;
URP_STRUC              *gParameters = &gUsbUrp;

// Below gEfiSmartCardReaderProtocolGuid definiion will be removed once
// it is added into MdePkg
EFI_GUID gEfiSmartCardReaderProtocolGuid = EFI_SMART_CARD_READER_PROTOCOL_GUID;

EFI_STATUS
EFIAPI
SupportedUsbCcid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

EFI_STATUS
EFIAPI
StartUsbCcid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

EFI_STATUS
EFIAPI
StopUsbCcid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
);

EFI_STATUS
GetReturnValue(
    UINT8    RetValue
);

EFI_STATUS
EFIAPI
UsbCcidApiSmartClassDescriptor(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *ResponseBuffer
);

EFI_STATUS
EFIAPI
UsbCcidApiGetAtr(
    IN AMI_CCID_IO_PROTOCOL *This,
    UINT8 Slot,
    UINT8 *ATRData
);

EFI_STATUS
EFIAPI
UsbCcidApiPowerupSlot(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error,
    OUT UINT8                           *ATRData
);

EFI_STATUS
EFIAPI
UsbCcidApiPowerDownSlot(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error
);

EFI_STATUS
EFIAPI
UsbCcidApiGetSlotStatus(
    IN AMI_CCID_IO_PROTOCOL              *This,
    OUT UINT8                            *Status,
    OUT UINT8                            *Error,
    OUT UINT8                            *ClockStatus

);

EFI_STATUS
EFIAPI
UsbCcidApiXfrBlock(
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINTN                            CmdLength,
    IN UINT8                            *CmdBuffer,
    IN UINT8                            ISBlock,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
);

EFI_STATUS
EFIAPI
UsbCcidApiGetParameters(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
);

EFI_GUID gAmiCcidIoProtocolGuid = AMI_CCID_IO_PROTOCOL_GUID;
EFI_GUID gAmiCcidPresenceGuid = AMI_CCID_PRESENCE_GUID;

EFI_EVENT       gEvICCEnumTimer = 0;
UINTN           gCounterCcidEnumTimer = 0;
BOOLEAN         gICCLock = FALSE;

#define    USBCCID_DRIVER_VERSION        1

EFI_DRIVER_BINDING_PROTOCOL gCcidBindingProtocol = {
        SupportedUsbCcid,
        StartUsbCcid,
        StopUsbCcid,
        USBCCID_DRIVER_VERSION,
        NULL,
        NULL 
};

/**
    retrieves data stored at the tail of the queue and
    removes the tail item

    @param    Queue  Pointer to QUEUE_T structure

    @retval   Data   Pointer to QUEUE_T data

**/

VOID*
QueueGet (
    QUEUE_T  *Queue
)
{
    VOID* Data;
    if( Queue->Tail == Queue->Head ) return NULL;
    Data = Queue->Data[Queue->Tail++];
    if( Queue->Tail == Queue->Maxsize ) Queue->Tail -= Queue->Maxsize;
    return Data;
}

/**
    Function installs EFI_SMART_CARD_READER_PROTOCOL_GUID for Smart card reader's slot

    @param CcidHandle   Ccid handle
    @param CcidDevice   Ptr to Ccid device info
    @param ICCDevice    Ptr to Ccid device 

    @retval EFI_SUCCESS             Success to install Usb card reader protocol
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
InstallUSBSCardReaderProtocolOnSlot(
    EFI_HANDLE      CcidHandle,
    DEV_INFO        *CcidDevice,
    ICC_DEVICE      *ICCDevice
)
{

    EFI_STATUS             Status = EFI_INVALID_PARAMETER;
    EFI_USB_IO_PROTOCOL    *UsbIo = NULL;
    USB_SCARD_DEV          *SCardDev;
    CCID_DEV_INFO          *CcidDevData;
    
    if (!CcidDevice) return EFI_INVALID_PARAMETER;

    CcidDevData = &CcidDevice->CcidDevData;

    // Install Protocol for the SCard Reader Slot
    if(!CcidDevData || !((SMARTCLASS_DESC*)(CcidDevData->CcidDescriptor)) ) {
        return EFI_INVALID_PARAMETER;
    }

    //gBS->AllocatePool(EfiBootServicesData, sizeof(USB_SCARD_DEV), (VOID**)&SCardDev);
    SCardDev = AllocatePool(sizeof(USB_SCARD_DEV));
    if (SCardDev==NULL) return EFI_OUT_OF_RESOURCES;

    SCardDev->ChildHandle      = 0;
    SCardDev->ControllerHandle = CcidHandle;
    SCardDev->Slot             = ICCDevice->Slot;
    SCardDev->DevInfo          = CcidDevice;

    SCardDev->EfiSmartCardReaderProtocol.SCardConnect    = UsbSCardReaderApiConnect;
    SCardDev->EfiSmartCardReaderProtocol.SCardStatus     = UsbSCardReaderApiStatus;
    SCardDev->EfiSmartCardReaderProtocol.SCardDisconnect = UsbSCardReaderApiDisconnect;
    SCardDev->EfiSmartCardReaderProtocol.SCardTransmit   = UsbSCardReaderApiTransmit;
    SCardDev->EfiSmartCardReaderProtocol.SCardControl    = UsbSCardReaderApiControl;
    SCardDev->EfiSmartCardReaderProtocol.SCardGetAttrib  = UsbSCardReaderApiGetAttrib;

    Status = gBS->InstallProtocolInterface(
                    &SCardDev->ChildHandle,
                    &gEfiSmartCardReaderProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &SCardDev->EfiSmartCardReaderProtocol
                    );
    ASSERT_EFI_ERROR(Status);

    ICCDevice->SCardChildHandle = SCardDev->ChildHandle;

    Status = gBS->OpenProtocol (
                    CcidHandle,
                    &gEfiUsbIoProtocolGuid,
                    (VOID**)&UsbIo,
                    gCcidBindingProtocol.DriverBindingHandle,
                    SCardDev->ChildHandle,
                    EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 
                    );

    ASSERT_EFI_ERROR(Status);

    DEBUG((DEBUG_INFO, "Install SCard on %lx status = %x SCardDev->ChildHandle %x \n", CcidHandle, Status, SCardDev->ChildHandle));

    return Status;
}

/**
    Function installs AMI_CCID_IO_PROTOCOL_GUID for the ICC card

    
    @param CcidHandle    Ccid handle
    @param CcidDevice    Ptr to Ccid device info
    @param ICCDevice     Ptr to Ccid device

    @retval EFI_SUCCESS             Success to install Usb ccid device
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
InstallUsbCcid(
    EFI_HANDLE      CcidHandle,
    DEV_INFO        *CcidDevice, 
    ICC_DEVICE      *ICCDevice
)
{

    EFI_STATUS                  Status = EFI_INVALID_PARAMETER;
    USB_ICC_DEV                 *ICCDev;
    EFI_USB_IO_PROTOCOL         *UsbIo;

    //
    // Install Protocol irrespective of device found or not. 
    // By checking ChildHandle here, avoid repeated protocol installation.
    //

    if (ICCDevice && !ICCDevice->ChildHandle) {
    
        DEBUG((DEBUG_INFO, "InstallUsbCcid ....\n" ));

        //gBS->AllocatePool(EfiBootServicesData, sizeof(USB_ICC_DEV), (VOID**)&ICCDev);
        ICCDev = AllocatePool(sizeof(USB_ICC_DEV));
        if (ICCDev==NULL) return EFI_OUT_OF_RESOURCES;

        ICCDev->ChildHandle = 0;
        ICCDev->ControllerHandle = 0;
        ICCDev->DevInfo    = CcidDevice;
        ICCDev->Slot       = ICCDevice->Slot;


        ICCDev->CcidIoProtocol.UsbCcidApiSmartClassDescriptor = UsbCcidApiSmartClassDescriptor;
        ICCDev->CcidIoProtocol.UsbCcidApiGetAtr               = UsbCcidApiGetAtr;
        ICCDev->CcidIoProtocol.UsbCcidApiPowerupSlot          = UsbCcidApiPowerupSlot;
        ICCDev->CcidIoProtocol.UsbCcidApiPowerDownSlot        = UsbCcidApiPowerDownSlot;
        ICCDev->CcidIoProtocol.UsbCcidApiGetSlotStatus        = UsbCcidApiGetSlotStatus;
        ICCDev->CcidIoProtocol.UsbCcidApiXfrBlock             = UsbCcidApiXfrBlock;
        ICCDev->CcidIoProtocol.UsbCcidApiGetParameters        = UsbCcidApiGetParameters;
    
        Status = gBS->InstallProtocolInterface(
                        &ICCDev->ChildHandle,
                        &gAmiCcidIoProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        &ICCDev->CcidIoProtocol
                        );

        ASSERT_EFI_ERROR(Status);

        ICCDevice->ChildHandle = ICCDev->ChildHandle;

        DEBUG((DEBUG_INFO, "ICCDev->ChildHandle = %x\n", ICCDev->ChildHandle));

        Status = gBS->OpenProtocol (
                        CcidHandle,
                        &gEfiUsbIoProtocolGuid,
                        (VOID**)&UsbIo,
                        gCcidBindingProtocol.DriverBindingHandle,
                        ICCDev->ChildHandle,
                        EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER );
    
        DEBUG((DEBUG_INFO, "Install Ccid on %x status = %r\n", CcidHandle, Status));
        ASSERT_EFI_ERROR(Status);

    }

    return Status;

}

/**
    Uninstall EFI_SMART_CARD_READER_PROTOCOL for Smart card reader's slot

    @param Controller            Controller handle 
    @param ScardHandle           Scard handle
    @param DriverBindingHandle   Driver binding handle

    @retval EFI_SUCCESS             Success to uninstall Usb card reader protocol
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
UnInstallScardProtocol (
    EFI_HANDLE    Controller,
    EFI_HANDLE    ScardHandle,
    EFI_HANDLE    DriverBindingHandle
)
{

    EFI_STATUS                       Status;
    EFI_SMART_CARD_READER_PROTOCOL   *SmartCardReaderProtocol;

    DEBUG((DEBUG_INFO, "UnInstallSCardProtocol ....ChildHandle : %lx", ScardHandle));

    Status = gBS->OpenProtocol ( 
                    ScardHandle,
                    &gEfiSmartCardReaderProtocolGuid,
                    (VOID**)&SmartCardReaderProtocol,
                    DriverBindingHandle,
                    ScardHandle,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );
    
    if(!EFI_ERROR(Status)) {

        Status = gBS->CloseProtocol (
                        Controller, 
                        &gEfiUsbIoProtocolGuid, 
                        DriverBindingHandle, 
                        ScardHandle
                        );
        
        ASSERT_EFI_ERROR(Status);

        Status = gBS->UninstallProtocolInterface ( 
                        ScardHandle, 
                        &gEfiSmartCardReaderProtocolGuid, 
                        SmartCardReaderProtocol
                        );

        ASSERT_EFI_ERROR(Status);

        Status = gBS->FreePool(SmartCardReaderProtocol);
        ASSERT_EFI_ERROR(Status);
    }

    DEBUG((DEBUG_INFO, " Status : %r\n", Status));
    return Status;
}

/**
    Uninstall AMI_CCID_IO_PROTOCOL_GUID for each slot

    @param  CcidHandle    SmartCard Reader Handle
    @param  ChildHandle   Smart Card Handle

    @retval EFI_STATUS    Status of the operation
**/

EFI_STATUS
UnInstallUsbCcid (
    EFI_HANDLE    CcidHandle,
    EFI_HANDLE    ChildHandle
)
{

    EFI_STATUS                Status;
    AMI_CCID_IO_PROTOCOL      *CcidIoProtocol;

    DEBUG((DEBUG_INFO, "UnInstallUsbCcid ....ChildHandle : %lx", ChildHandle ));

    Status = gBS->OpenProtocol ( 
                    ChildHandle, 
                    &gAmiCcidIoProtocolGuid, 
                    (VOID**)&CcidIoProtocol, 
                    gCcidBindingProtocol.DriverBindingHandle, 
                    ChildHandle, 
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL
                    );

    //
    // Ccid protocol not found on ChildHandle. return with error.
    //
    if(!EFI_ERROR(Status)) {
        // If Ccid protocol Found, close the protocol and uninstall the protocol interface.

        Status = gBS->CloseProtocol (
                        CcidHandle, 
                        &gEfiUsbIoProtocolGuid, 
                        gCcidBindingProtocol.DriverBindingHandle, 
                        ChildHandle
                        );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        Status = gBS->UninstallProtocolInterface (
                        ChildHandle, 
                        &gAmiCcidIoProtocolGuid, 
                        CcidIoProtocol
                        );
    
        if(!EFI_ERROR(Status)){
            gBS->FreePool(CcidIoProtocol);
        }
    }

    DEBUG((DEBUG_INFO, " Status : %r\n", Status));
    return Status;
}

/**
    Generates a SW SMI to get the SMART Class Descriptor for the Ccid device

        
    @param This            Ptr for AMI_CCID_IO_PROTOCOL
    @param ResponseBuffer  Ptr for response buffer.

    @retval EFI_STATUS     Status returns SMART Class Descriptor in ResponseBuffer

**/

EFI_STATUS
EFIAPI
UsbCcidApiSmartClassDescriptor(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *ResponseBuffer
)
{

    EFI_STATUS  Status;
//    URP_STRUC   Parameters = {0};

    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc    = USB_CCID_SMARTCLASSDESCRIPTOR;

    gParameters->ApiData.CcidSmartClassDescriptor.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidSmartClassDescriptor.Slot = ((USB_ICC_DEV *)This)->Slot;
    gParameters->ApiData.CcidSmartClassDescriptor.ResponseBuffer = (UINTN)ResponseBuffer;
     
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    Generates a SW SMI to get the ATR data

        
    @param This      Ptr for AMI_CCID_IO_PROTOCOL
    @param Slot      Ccid slot
    @param ATRData   Ptr to atrdata

    @retval EFI_SUCCESS    Status returns if available

    @note  
      ATRData buffer length should be 32 bytes long. Caller should allocate 
      memory for *ATRData. 

**/

EFI_STATUS
EFIAPI
UsbCcidApiGetAtr(
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINT8                            Slot,
    OUT UINT8                           *ATRData
)
{

    EFI_STATUS  Status;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_CCID_ATR;

    gParameters->ApiData.CcidAtr.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidAtr.Slot = ((USB_ICC_DEV *)This)->Slot;
    gParameters->ApiData.CcidAtr.ATRData = (UINTN)ATRData;
    
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    Generates a SW SMI to power up the slot in CCID

        
    @param This      Ptr to AMI_CCID_IO_PROTOCOL
    @param Status   Ptr to Ccid status
    @param Error    Ptr to Ccid Error code
    @param ATRData   Ptr to Atrdata

    @retval EFI_SUCCESS    Status returns if Card powered up successfully.

    @note  
        ATRData buffer length should be 32 bytes long. Caller should allocate memory for *ATRData. 
        Presence/Absence of card can be determined from *Status and *bError.

**/

EFI_STATUS
EFIAPI
UsbCcidApiPowerupSlot(
    IN AMI_CCID_IO_PROTOCOL                 *This,
    OUT UINT8                               *PowerupSlotStatus,
    OUT UINT8                               *PowerupSlotError,
    OUT UINT8                               *ATRData
)
{

    EFI_STATUS              Status;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_CCID_POWERUP_SLOT;

    gParameters->ApiData.CcidPowerupSlot.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidPowerupSlot.Slot = ((USB_ICC_DEV *)This)->Slot;
    gParameters->ApiData.CcidPowerupSlot.ATRData = (UINTN)ATRData;
    
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);
    
    *PowerupSlotStatus = gParameters->ApiData.CcidPowerupSlot.Status; 
    *PowerupSlotError = gParameters->ApiData.CcidPowerupSlot.Error;

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    Generates a SW SMI to power down the slot in CCID.

        
    @param This      Ptr to AMI_CCID_IO_PROTOCOL
    @param bStatus   Ptr to Ccid status
    @param bError    Ptr to Ccid Error code

    @retval EFI_SUCCESS    Status returns if Card powered down successfully.

**/

EFI_STATUS
EFIAPI
UsbCcidApiPowerDownSlot(
    IN AMI_CCID_IO_PROTOCOL                 *This,
    OUT UINT8                               *PowerdownSlotStatus,
    OUT UINT8                               *PowerdownSlotError
)
{

    EFI_STATUS              Status;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_CCID_POWERDOWN_SLOT;

    gParameters->ApiData.CcidPowerdownSlot.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidPowerdownSlot.Slot = ((USB_ICC_DEV *)This)->Slot;

    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    *PowerdownSlotStatus = gParameters->ApiData.CcidPowerdownSlot.Status; 
    *PowerdownSlotError = gParameters->ApiData.CcidPowerdownSlot.Error;

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    This API returns data from RDR_to_PC_SlotStatus

        
    @param This          Ptr to AMI_CCID_IO_PROTOCOL
    @param bStatus       Ptr to Ccid status
    @param bError        Ptr to Ccid Error code
    @param bClockStatus  Ptr to Ccid clock status.

    @retval EFI_SUCCESS    Status returns if get slot status successfully.

**/

EFI_STATUS
EFIAPI
UsbCcidApiGetSlotStatus(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *GetSlotStatus,
    OUT UINT8                           *GetSlotError,
    OUT UINT8                           *ClockStatus

)
{

    EFI_STATUS              Status;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_CCID_GET_SLOT_STATUS;

    gParameters->ApiData.CcidGetSlotStatus.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidGetSlotStatus.Slot = ((USB_ICC_DEV *)This)->Slot;

    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    *GetSlotStatus = gParameters->ApiData.CcidGetSlotStatus.Status; 
    *GetSlotError = gParameters->ApiData.CcidGetSlotStatus.Error;
    *ClockStatus = gParameters->ApiData.CcidGetSlotStatus.ClockStatus;

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    This API generates a SWSMI to execute the USB_CCID_XFRBLOCK API.

        
    @param This           Ptr to AMI_CCID_IO_PROTOCOL
    @param CmdLength      Length of CmdBuffer
    @param CmdBuffer      Buffer prepared to be sent to ICC through PC_TO_RDR_XFRBLOCK cmd
    @param ISBlock        Valid only in T1 TDPU        
    @param bStatus        Ptr to Ccid status
    @param bError         Ptr to Ccid Error code 
    @param ResponseLength Lenght of the Responsebuffer
    @param ResponseBuffer Response buffer.
 
    @retval EFI_SUCCESS   Status returns if xfr block successfully.

    @note  
       ISBlock is valid only for T1. For updating IFS use S_IFS_REQUEST(0xC1).
       For WTX request use S_WTX_REQUEST (0xC3). For all others use I_BLOCK(0x0)
**/

EFI_STATUS
EFIAPI
UsbCcidApiXfrBlock(
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINTN                            CmdLength,
    IN UINT8                            *CmdBuffer,
    IN UINT8                            ISBlock,
    OUT UINT8                           *XfrBlockStatus,
    OUT UINT8                           *XfrBlockError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
)
{

    EFI_STATUS              Status;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_CCID_XFRBLOCK;
    gParameters->ApiData.CcidXfrBlock.CmdLength = CmdLength;
    gParameters->ApiData.CcidXfrBlock.CmdBuffer = (UINT32)(UINTN)CmdBuffer;
    gParameters->ApiData.CcidXfrBlock.ISBlock = I_BLOCK;
    gParameters->ApiData.CcidXfrBlock.ResponseLength = *ResponseLength;
    gParameters->ApiData.CcidXfrBlock.ResponseBuffer = (UINTN)ResponseBuffer;

    gParameters->ApiData.CcidXfrBlock.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidXfrBlock.Slot = ((USB_ICC_DEV *)This)->Slot;
    
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    *XfrBlockStatus = gParameters->ApiData.CcidXfrBlock.Status ;
    *XfrBlockError = gParameters->ApiData.CcidXfrBlock.Error;
    *ResponseLength = gParameters->ApiData.CcidXfrBlock.ResponseLength;

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    Returns data from PC_TO_RDR_GETPARAMETERS/RDR_to_PCParameters cmd

        
    @param This             Ptr to AMI_CCID_IO_PROTOCOL
    @param Status           Ptr to Ccid status
    @param Error            Ptr to Ccid Error code 
    @param ResponseLength   Lenght of the Responsebuffer
    @param ResponseBuffer   Response buffer. 

    @retval EFI_SUCCESS   Status returns if get parameter successfully.

**/

EFI_STATUS
EFIAPI
UsbCcidApiGetParameters(
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *GetParametersStatus,
    OUT UINT8                           *GetParametersError,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
)
{

    EFI_STATUS              Status;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_CCID_GET_PARAMETERS;
    gParameters->ApiData.CcidGetParameters.ResponseLength = *ResponseLength;
    gParameters->ApiData.CcidGetParameters.ResponseBuffer = (UINT32)(UINTN)ResponseBuffer;

    gParameters->ApiData.CcidGetParameters.DevInfo = (UINTN)((USB_ICC_DEV *)This)->DevInfo;
    gParameters->ApiData.CcidGetParameters.Slot = ((USB_ICC_DEV *)This)->Slot;
    
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    *GetParametersStatus = gParameters->ApiData.CcidGetParameters.Status ;
    *GetParametersError = gParameters->ApiData.CcidGetParameters.Error;
    *ResponseLength = gParameters->ApiData.CcidGetParameters.ResponseLength;

    Status = GetReturnValue(gParameters->RetValue);

    return Status;

}

/**
    Function to connect the Smard Card reader/ICC card in order to access the Smart
         reader/ICC card

    @param This                Ptr to EFI_SMART_CARD_READER_PROTOCOL
    @param AccessMode          Access Mode
    @param CardAction          Card Action
    @param PreferredProtocols  Preferred Protocols
    @param ActiveProtocol      Ptr to Active Protocol

    @retval EFI_SUCCESS        Status returns if card reader connect successfully.


**/

EFI_STATUS
EFIAPI
UsbSCardReaderApiConnect(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT32                         AccessMode,
    IN UINT32                         CardAction,
    IN UINT32                         PreferredProtocols,
    OUT UINT32                        *ActiveProtocol
)
{
    
    DEBUG((DEBUG_INFO, "UsbSCardReaderApiConnect AccessMode : %x CardAction : %x  PreferredProtocols : %x \n",\
        AccessMode, CardAction, PreferredProtocols));

    // Return error if AccessMode or CardAction input parameter is Invalid
    if( !((AccessMode==SCARD_AM_READER)||(AccessMode==SCARD_AM_CARD)) || 
            !(CardAction <= SCARD_CA_EJECT) ) {
        return EFI_INVALID_PARAMETER;
    }

    // Invalid Input parameter for ScardReader connect call
    if(AccessMode == SCARD_AM_READER) {
        // if AccessMode is set to SCARD_AM_READER,PreferredProtocol must be set to 
        // SCARD_PROTOCOL_UNDEFINED,CardAction to SCARD_CA_NORESET else error
        if( CardAction!=SCARD_CA_NORESET || PreferredProtocols!=SCARD_PROTOCOL_UNDEFINED ) {
            return EFI_INVALID_PARAMETER;
        }
    }

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_SMART_CARD_READER_CONNECT;
    
    gParameters->ApiData.SmartCardReaderConnect.DevInfo = (UINTN)((USB_SCARD_DEV *)This)->DevInfo;
    gParameters->ApiData.SmartCardReaderConnect.Slot = (UINTN)((USB_SCARD_DEV *)This)->Slot;
    gParameters->ApiData.SmartCardReaderConnect.AccessMode = AccessMode;
    gParameters->ApiData.SmartCardReaderConnect.CardAction = CardAction;
    gParameters->ApiData.SmartCardReaderConnect.PreferredProtocols = PreferredProtocols;
    gParameters->ApiData.SmartCardReaderConnect.ActiveProtocol = (UINTN)ActiveProtocol;
    
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    DEBUG((DEBUG_INFO, "UsbSCardReaderApiConnect Status : %r ActiveProtocol : %x\n", \
             gParameters->ApiData.SmartCardReaderConnect.EfiStatus, *ActiveProtocol));
    return gParameters->ApiData.SmartCardReaderConnect.EfiStatus;
}

/**
    Function disconnects Scard Reader/ICC card

    @param This        Ptr to EFI_SMART_CARD_READER_PROTOCOL
    @param CardAction  Card Action 

    @retval EFI_SUCCESS    Status returns if card reader disconnect successfully.

**/

EFI_STATUS
EFIAPI
UsbSCardReaderApiDisconnect(
    IN EFI_SMART_CARD_READER_PROTOCOL  *This,
    IN UINT32                          CardAction
)
{
    DEBUG((DEBUG_INFO, "UsbSCardReaderApiDisconnect CardAction : %x \n", CardAction));

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_SMART_CARD_READER_DISCONNECT;

    gParameters->ApiData.SmartCardReaderDisconnect.DevInfo = (UINTN)((USB_SCARD_DEV *)This)->DevInfo;
    gParameters->ApiData.SmartCardReaderDisconnect.Slot = (UINTN)((USB_SCARD_DEV *)This)->Slot;
    gParameters->ApiData.SmartCardReaderDisconnect.CardAction = CardAction;
    gParameters->ApiData.SmartCardReaderDisconnect.EfiStatus = 0;

    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    DEBUG((DEBUG_INFO, "UsbSCardReaderApiDisconnect Status : %r \n", gParameters->ApiData.SmartCardReaderDisconnect.EfiStatus ));

    return gParameters->ApiData.SmartCardReaderDisconnect.EfiStatus;
}

/**
    Function to get the status of the ICC card connected in Smart card reader

    @param This              Ptr to EFI_SMART_CARD_READER_PROTOCOL
    @param ReaderName        Ptr to Reader Name
    @param ReaderNameLength  Ptr to Reader Name Length
    @param State             Ptr to state
    @param CardProtocol      Ptr to card protocl
    @param Atr               Ptr to atr
    @param AtrLength         Ptr to atr length

    @retval EFI_SUCCESS      Status returns if get card reader status successfully.

**/

EFI_STATUS
EFIAPI
UsbSCardReaderApiStatus(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    OUT CHAR16                        *ReaderName,
    IN OUT UINTN                      *ReaderNameLength,
    OUT UINT32                        *State,
    OUT UINT32                        *CardProtocol,
    OUT UINT8                         *Atr,
    IN OUT UINTN                      *AtrLength
)
{
    if( EFI_ERROR(GetSmartCardReaderName( 
    	            This,
                    ReaderName, 
                    ReaderNameLength 
                    ))) {
        return EFI_BUFFER_TOO_SMALL;
    }

    DEBUG((DEBUG_INFO, "UsbSCardReaderApiStatus ReaderName : %lx ReaderNameLength : %lx Atr : %lx AtrLength : %lx \n",\
        ReaderName, *ReaderNameLength, Atr, *AtrLength));
    
    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_SMART_CARD_READER_STATUS;
    
    gParameters->ApiData.SmartCardReaderStatus.DevInfo = (UINTN)((USB_SCARD_DEV *)This)->DevInfo;
    gParameters->ApiData.SmartCardReaderStatus.Slot = (UINTN)((USB_SCARD_DEV *)This)->Slot;
    gParameters->ApiData.SmartCardReaderStatus.ReaderName = (UINTN)ReaderName;
    gParameters->ApiData.SmartCardReaderStatus.ReaderNameLength = (UINTN)ReaderNameLength;
    gParameters->ApiData.SmartCardReaderStatus.State = (UINTN)State;
    gParameters->ApiData.SmartCardReaderStatus.CardProtocol = (UINTN)CardProtocol;
    gParameters->ApiData.SmartCardReaderStatus.Atr = (UINTN)Atr;
    gParameters->ApiData.SmartCardReaderStatus.AtrLength = (UINTN)AtrLength;
      
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    DEBUG((DEBUG_INFO, "UsbSCardReaderApiStatus ReaderNameLength : %lx AtrLength : %lx  Status : %r\n",\
         *ReaderNameLength, *AtrLength, gParameters->ApiData.SmartCardReaderStatus.EfiStatus));
    
    return gParameters->ApiData.SmartCardReaderStatus.EfiStatus;
}

/**
    This function sends a command to the card or reader and returns its response.

    @param This           Ptr to EFI_SMART_CARD_READER_PROTOCOL
    @param CAPDU          Ptr to CAPDU
    @param CAPDULength    CAPDU length
    @param RAPDU          Ptr to RAPDU
    @param RAPDULength    Ptr to RAPDU length

    @retval EFI_SUCCESS   Status returns if card reader transmit successfully.


**/

EFI_STATUS
EFIAPI
UsbSCardReaderApiTransmit(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT8                          *CAPDU,
    IN UINTN                          CAPDULength,
    OUT UINT8                         *RAPDU,
    IN OUT UINTN                      *RAPDULength
)
{
 
    DEBUG((DEBUG_INFO, "UsbSCardReaderApiTransmit CAPDU : %lx CAPDULength : %lx RAPDU : %lx RAPDULength : %lx \n",\
          CAPDU, CAPDULength, RAPDU, *RAPDULength));

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->FuncNumber = USB_API_CCID_DEVICE_REQUEST;
    gParameters->SubFunc = USB_SMART_CARD_READER_TRANSMIT;
    
    gParameters->ApiData.SmartCardReaderTransmit.DevInfo = (UINTN)((USB_SCARD_DEV *)This)->DevInfo;
    gParameters->ApiData.SmartCardReaderTransmit.Slot = (UINTN)((USB_SCARD_DEV *)This)->Slot;
    gParameters->ApiData.SmartCardReaderTransmit.CAPDU = (UINTN)CAPDU;
    gParameters->ApiData.SmartCardReaderTransmit.CAPDULength = CAPDULength;
    gParameters->ApiData.SmartCardReaderTransmit.RAPDU = (UINTN)RAPDU;
    gParameters->ApiData.SmartCardReaderTransmit.RAPDULength = (UINTN)RAPDULength;
     
    //InvokeUsbApi(gParameters);
    UsbApiCcidRequest(gParameters);

    DEBUG((DEBUG_INFO, "UsbSCardReaderApiTransmit RAPDULength : %lx Status : %r\n",\
            *RAPDULength, gParameters->ApiData.SmartCardReaderTransmit.EfiStatus));

    return gParameters->ApiData.SmartCardReaderTransmit.EfiStatus;
}

/**
    This function is the API function of SMART CARD READER PROTOCOL

    @param This             Ptr to EFI_SMART_CARD_READER_PROTOCOL
    @param ControlCode      Control code
    @param InBuffer         Ptr to in buffer
    @param InBufferLength   In buffer length
    @param OutBuffer        Ptr to Out buffer 
    @param OutBufferLength  Ptr to out buffer length

    @retval EFI_UNSUPPORTED This protocol is not support.

**/

EFI_STATUS
EFIAPI
UsbSCardReaderApiControl(
  IN     EFI_SMART_CARD_READER_PROTOCOL    *This,
  IN     UINT32                            ControlCode,
  IN     UINT8                             *InBuffer OPTIONAL,
  IN     UINTN                             InBufferLength OPTIONAL,
     OUT UINT8                             *OutBuffer OPTIONAL,
  IN OUT UINTN                             *OutBufferLength OPTIONAL
)
{
    return EFI_UNSUPPORTED;
}

/**
    This function is the API function of SMART CARD READER PROTOCOL

    @param This             Ptr to EFI_SMART_CARD_READER_PROTOCOL
    @param Attrib           attrib
    @param OutBuffer        Ptr to out buffer
    @param OutBufferLength  Ptr to out buffer length

    @retval EFI_UNSUPPORTED This protocol is not support.

**/

EFI_STATUS
EFIAPI
UsbSCardReaderApiGetAttrib(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT32                         Attrib,
    OUT UINT8                         *OutBuffer,
    IN OUT UINTN                      *OutBufferLength
)
{
    return EFI_UNSUPPORTED;
}


/**
    This function to get SMART CARD reader name

    @param ControllerHandle  Controller handle
    @param ReaderName        Ptr to reader name
    @param ReaderNameLength  Ptr to reader name length

    @retval EFI_SUCCESS Status returns if get card reader name successfully.

**/
EFI_STATUS
GetSmartCardReaderName (
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    CHAR16        *ReaderName,
    UINTN         *ReaderNameLength
)
{
    EFI_STATUS                 Status;
    DEV_INFO                   *DevInfo = (DEV_INFO*)((USB_SCARD_DEV *)This)->DevInfo;
    EFI_USB_IO_PROTOCOL        *UsbIo = DevInfo->UsbIo;
    CHAR16                     *String = NULL;
    UINTN                      Length;

    Status = UsbIo->UsbGetStringDescriptor(
                      UsbIo,
                      0x0409,
                      DevInfo->StrProduct,
                      &String
                      );
    if(EFI_ERROR(Status)) {
        return Status;
    }

    if (String==NULL) return EFI_UNSUPPORTED;
    Length = StrnLenS (String, *ReaderNameLength);
    CopyMem(ReaderName, String, Length-2 );
    ReaderName[((Length-2)>>1)] = L'\0';
    *ReaderNameLength = Length;
    if (String!=NULL) FreePool(String);
    return Status;
}

/**
    Search the linked list to find the CCID Device for the given ICC

    @param ICCDevice     ICC device

    @retval Pointer        Ptr to DEV_INFO

**/
DEV_INFO*
GetCcidDevice(
    ICC_DEVICE        *ICCDevice
)
{
    return ICCDevice->DevInfo;
}

/**
    Convert CCID return Value to EFI_STATUS

    @param RetValue     Return value

    @retval EFI_STATUS   Return the EFI Status

**/

EFI_STATUS
GetReturnValue(
    UINT8    RetValue
)
{
    EFI_STATUS    Status;

    switch (RetValue) {

            case USB_SUCCESS:
                Status = EFI_SUCCESS;
                break;

            default:
                Status = EFI_DEVICE_ERROR;
    }

    return Status;
}

/**
    Timer call-back routine that is used to monitor insertion/removal 
    of ICC(Smart card) in the smart card reader.

     
    @param EFI_EVENT   Event,
    @param VOID        *Context

**/

VOID
EFIAPI
IccOnTimer(
    EFI_EVENT   Event,
    VOID        *Context
)
{
    ICC_DEVICE        *IccDevice = NULL;
    DEV_INFO          *CcidDevice = NULL; 
    BOOLEAN           Lock;
    EFI_HANDLE        CcidHandle;

    ATOMIC({Lock = gICCLock; gICCLock=1;});
 
    if( Lock ){
        DEBUG((DEBUG_INFO, "ICCOnTimer::  is locked; return\n" ));
        return;
    }

    do {

        ATOMIC({IccDevice = (ICC_DEVICE *)QueueGet(&gUsbDataList->ICCQueueCnnctDisc);});

        if (IccDevice == NULL) { 
            break;
        }

        CcidDevice = GetCcidDevice(IccDevice);

        if (!CcidDevice) {
            continue;
        }

        CcidHandle = CcidDevice->Handle;

        DEBUG((DEBUG_INFO, "Controller %lx\n", CcidHandle));
        DEBUG((DEBUG_INFO, "Insert/Removal: DevInfo %lx IccDevice %lx IccDevice->ChildHandle %lx IccDevice->ConfiguredStatus %x\n", \
                CcidDevice, IccDevice, IccDevice->ChildHandle, IccDevice->ConfiguredStatus ));

      if ((gUsbData->UsbFeature & USB_CCID_USE_INT_INS_REMOVAL) == USB_CCID_USE_INT_INS_REMOVAL){
        if (!IccDevice->ChildHandle && (IccDevice->ConfiguredStatus & ICCPRESENT)) {
            //DEBUG((DEBUG_INFO, "InstallUSBCCID ....\n" ));
            //
            // Install EFI interface to communicate with Smart Card/CCID
            //
            InstallUsbCcid(CcidHandle, CcidDevice, IccDevice);
        }

        if (IccDevice->ConfiguredStatus & CARDREMOVED) {
            //DEBUG((DEBUG_INFO, "UnInstallUSBCCID ....\n" ));
            //
            // Device Removed. Uninstall the existing Device
            //
             UnInstallUsbCcid (CcidHandle, IccDevice->ChildHandle);
             // Indication to the SMI handler that the CARD has been uninstalled.
             // This Handle will be checked before device is inserted into the queue.
             IccDevice->ChildHandle = NULL;
             
        }
      }else{

        InstallUsbCcid(CcidHandle, CcidDevice, IccDevice);     
      }


        // When card is removed, ScardChildHandle will still be valid so it will not do anything.
        // If the handle is valid, it means the protocol is already installed
        if (!IccDevice->SCardChildHandle) {
            InstallUSBSCardReaderProtocolOnSlot(CcidHandle, CcidDevice, IccDevice);
        }
    } while ( 1 );

    gICCLock = FALSE;

    return;
}

/**
    Verifies if usb CCID support can be installed on a device

        
    @param This                 pointer to driver binding protocol
    @param ControllerHandle     controller handle to install driver on
    @param RemainingDevicePath  pointer to device path

         
    @retval EFI_SUCCESS driver supports given controller
    @retval EFI_UNSUPPORTED driver doesn't support given controller

**/

EFI_STATUS
EFIAPI
SupportedUsbCcid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    EFI_USB_INTERFACE_DESCRIPTOR    Desc;
    EFI_STATUS                      Status;
    EFI_USB_IO_PROTOCOL             *UsbIo;

    Status = gBS->OpenProtocol (
                    Controller, 
                    &gEfiUsbIoProtocolGuid,
                    (VOID**)&UsbIo, 
                    This->DriverBindingHandle,
                    Controller, 
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL 
                    );

    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = UsbIo->UsbGetInterfaceDescriptor(UsbIo, &Desc);

    if(EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    if ( Desc.InterfaceClass == BASE_CLASS_CCID_STORAGE &&
         Desc.InterfaceSubClass == SUB_CLASS_CCID &&
         Desc.InterfaceProtocol == PROTOCOL_CCID) {
        return EFI_SUCCESS;
    } else {
        return EFI_UNSUPPORTED;
    }

}

/**
    Installs CCID protocol on a given handle

           
    @param This                pointer to driver binding protocol
    @param ControllerHandle    controller handle to install driver on
    @param RemainingDevicePath pointer to device path

         
    @retval EFI_SUCCESS       driver started successfully
    @retval EFI_UNSUPPORTED   driver didn't start

**/

EFI_STATUS
EFIAPI
StartUsbCcid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath
)
{
    EFI_STATUS                 Status;
    EFI_USB_IO_PROTOCOL        *UsbIo;
    USB_DEVICE_DESCRIPTOR      DeviceDes;
    EFI_USB_CONFIG_DESCRIPTOR  ConfigDes;
    USB_INTERFACE_DESCRIPTOR   InterfaceDes;
    UINT32                     TransferResult;

    //
    // Open Protocols
    //
    Status = gBS->OpenProtocol (
                    Controller,  
                    &gEfiUsbIoProtocolGuid,
                    (VOID**)&UsbIo, 
                    This->DriverBindingHandle,
                    Controller, 
                    EFI_OPEN_PROTOCOL_BY_DRIVER 
                    );
    if( EFI_ERROR(Status)) {
        return Status;
    }

    DEBUG((DEBUG_INFO,
        "USB: installUSBCCID: starting...Controller : %lx\n", Controller));

    {
        DEV_INFO  *DevInfo;
        DEV_INFO  *DevInfoTemp;
        USB_INTERFACE_DESCRIPTOR   *Intrf;
        UINT16                     Offset;
        UINT8                      ConfiDesBuf[MAX_CCID_CONTROL_DATA_SIZE];

        Status = UsbIo->UsbGetDeviceDescriptor(
                          UsbIo,
                          &DeviceDes
                          );
        if( EFI_ERROR(Status)) {
             gBS->CloseProtocol (
                   Controller, 
                   &gEfiUsbIoProtocolGuid, 
                   This->DriverBindingHandle, 
                   Controller
                   );
            return EFI_DEVICE_ERROR;
        }
        
        DevInfo = AllocatePool(sizeof(DEV_INFO));
        if (DevInfo == NULL) {
            gBS->CloseProtocol (
                   Controller, 
                   &gEfiUsbIoProtocolGuid, 
                   This->DriverBindingHandle, 
                   Controller
                   );
            return EFI_OUT_OF_RESOURCES;
        	
        }
        DevInfo->UsbIo = UsbIo;
        DevInfo->Handle = Controller;
        DevInfo->CcidDevData.CcidDescriptor    = (VOID*)&DevInfo->CcidDesc;
        DevInfo->CcidDevData.DataRates         = &DevInfo->CcidDataRates[0];
        DevInfo->CcidDevData.ClockFrequencies  = &DevInfo->ClockFrequencies[0];
        DevInfo->StrProduct                    = DeviceDes.StrProduct;
         
        Status = UsbIo->UsbGetConfigDescriptor(
                          UsbIo,
                          &ConfigDes
                          );

        if( EFI_ERROR(Status)) {
             gBS->CloseProtocol (
                   Controller, 
                   &gEfiUsbIoProtocolGuid, 
                   This->DriverBindingHandle, 
                   Controller
                   );
            FreePool(DevInfo);
            return EFI_DEVICE_ERROR;
        }

        Status = UsbGetDescriptor (
                   UsbIo,
                   (UINT16)((USB_DESC_TYPE_CONFIG << 8) | (ConfigDes.ConfigurationValue - 1)),
                   0,
                   ConfigDes.TotalLength,
                   (VOID*)(&ConfiDesBuf[0]),
                   &TransferResult
                   );

        if( EFI_ERROR(Status)) {
             gBS->CloseProtocol (
                   Controller, 
                   &gEfiUsbIoProtocolGuid, 
                   This->DriverBindingHandle, 
                   Controller
                   );
            FreePool(DevInfo);
            return EFI_DEVICE_ERROR;
        }        

        Status = UsbIo->UsbGetInterfaceDescriptor(
                          UsbIo,
                          &InterfaceDes
                          );

        if( EFI_ERROR(Status)) {
             gBS->CloseProtocol (
                   Controller, 
                   &gEfiUsbIoProtocolGuid, 
                   This->DriverBindingHandle, 
                   Controller
                   );
            FreePool(DevInfo);
            return EFI_DEVICE_ERROR;
        }
      
        for (Offset = (UINT16)ConfigDes.Length; Offset <ConfigDes.TotalLength; Offset = Offset + (UINT16)Intrf->Length) {
            Intrf = (USB_INTERFACE_DESCRIPTOR*)((UINT8*)ConfiDesBuf + Offset);
            if (Intrf->Length == 0) {
                break;
            }
            if (Intrf->DescriptorType == DESC_TYPE_INTERFACE &&
                InterfaceDes.InterfaceNumber == Intrf->InterfaceNumber &&
                InterfaceDes.AlternateSetting == Intrf->AlternateSetting ) {
                break;
            }
        }    
        DevInfoTemp = UsbCcidConfigureDevice(
                        DevInfo,
                        ConfiDesBuf,
                        (UINT16)(UINTN)((UINT8*)Intrf - (UINT8*)ConfiDesBuf),
                        ConfigDes.TotalLength
                        );
        if(!DevInfoTemp) {
             gBS->CloseProtocol (
                   Controller, 
                   &gEfiUsbIoProtocolGuid, 
                   This->DriverBindingHandle, 
                   Controller
                   );
            FreePool(DevInfo);
            return EFI_DEVICE_ERROR;
        }

        //
        // Install AMI CCID Presence protocol to identify SMART Card reader is detected
        //
        Status = gBS->InstallProtocolInterface(
                        &Controller,
                        &gAmiCcidPresenceGuid,
                        EFI_NATIVE_INTERFACE,
                        DevInfo
                        );

        ASSERT_EFI_ERROR(Status);

        //
        // Setting up Timer to to detect ICC card insertion removal 
        //
        gCounterCcidEnumTimer++;
        if (gEvICCEnumTimer == 0) {
            DEBUG((DEBUG_INFO, "USBBUS: Start: setup timer callback %x\n", &IccOnTimer ));
            
            gBS->CreateEvent(
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK, 
                   IccOnTimer,
                   0,
                   &gEvICCEnumTimer
                   );
            gBS->SetTimer(gEvICCEnumTimer, TimerPeriodic, MILLISECOND);
        }

    }

    DEBUG((DEBUG_INFO,
        "USB: installCcid: done (%x).\n", Status));


    return Status;
}


/**
    Uninstalls Ccid protocol on a given handle

           
    @param This               pointer to driver binding protocol
    @param ControllerHandle   controller handle to install driver on
    @param NumberOfChildren   number of childs on this handle
    @param ChildHandleBuffer  pointer to child handles array

         
    @retval EFI_SUCCESS             driver stopped successfully
    @retval EFI_INVALID_PARAMETER   invalid values passed for NumberOfChildren or
                                    ChildHandleBuffer
**/

EFI_STATUS
EFIAPI
StopUsbCcid(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
)
{

    EFI_STATUS Status;
    DEV_INFO  *DevInfo = NULL;

    if (!NumberOfChildren) {

        // Closer the timer event when all Ccid devices have been stopped
        if(--gCounterCcidEnumTimer==0){

            gBS->SetTimer(gEvICCEnumTimer, TimerCancel, ONESECOND);
            gBS->CloseEvent(gEvICCEnumTimer);
            gEvICCEnumTimer=0;

            DEBUG((DEBUG_INFO, "USB: Timer Stopped\n"));
        }

        Status = gBS->OpenProtocol (
                    Controller,  
                    &gAmiCcidPresenceGuid,
                    (VOID**)&DevInfo, 
                    This->DriverBindingHandle,
                    Controller, 
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL 
                    );
        if( EFI_ERROR(Status)) {
            return Status;
        }
 
        if (DevInfo==NULL) return EFI_INVALID_PARAMETER;

        // Stop polling the endpoint 
        DevInfo->UsbIo->UsbAsyncInterruptTransfer (
                   DevInfo->UsbIo,
                   DevInfo->IntInEndpoint,
                   FALSE,
                   DevInfo->PollInterval,
                   0,
                   NULL,
                   NULL
                   );

        //
        // uninstall gAmiCcidPresenceGuid 
        //
        Status = gBS->UninstallProtocolInterface ( 
                        Controller, 
                        &gAmiCcidPresenceGuid, 
                        DevInfo
                        );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        if (DevInfo!=NULL) FreePool(DevInfo);
        
        Status = gBS->CloseProtocol (
                        Controller, 
                        &gEfiUsbIoProtocolGuid, 
                        This->DriverBindingHandle, 
                        Controller
                        );
        ASSERT_EFI_ERROR(Status);
        
        DEBUG((DEBUG_INFO, "USB: StopUsbCcid: done : %r gCounterCcidEnumTimer : %x\n", \
                 Status,  gCounterCcidEnumTimer));
    }

    while (NumberOfChildren){

        //
        // Uninstall AMI_Ccid_IO_PROTOCOL for each slot
        //
        Status = UnInstallUsbCcid (Controller, Children[NumberOfChildren -  1]);

        if( EFI_ERROR(Status) ) {
            Status = UnInstallScardProtocol (Controller, Children[NumberOfChildren -  1], This->DriverBindingHandle);
        }
        ASSERT_EFI_ERROR(Status);

        NumberOfChildren--;

    }

    return Status;

}

/**
    Ccid driver entry point

    @param  ImageHandle    The firmware allocated handle for the EFI image.  
    @param  SystemTable    A pointer to the EFI System Table.

         
    @retval EFI_STATUS     Efi Status.

**/

EFI_STATUS
EFIAPI
UsbCcidInit(
  IN  EFI_HANDLE        ImageHandle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
)
{
    EFI_STATUS    Status;
 
    gUsbData->MaxDevCount = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid, AmiPcdMaxCcidDevCount);
    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdCcidUseIntInsRemoval)){
        gUsbData->UsbFeature |= USB_CCID_USE_INT_INS_REMOVAL;
    }

    if (PcdGetExBool (&gAmiUsbPkgTokenSpaceGuid, AmiPcdUsbCcidDevice)){
        gUsbData->UsbDevSupport |= USB_CCID_DEV_SUPPORT;
    }  
    
    gUsbData->UseT0T1Protocol = PcdGetEx8(&gAmiUsbPkgTokenSpaceGuid,AmiPcdUseT0T1Protocol);
    
    gUsbDataList->ICCQueueCnnctDisc.Data = (VOID*)gUsbDataList->ICCQueueData;
    gUsbDataList->ICCQueueCnnctDisc.Maxsize = COUNTOF(gUsbDataList->ICCQueueData);
    gUsbDataList->ICCQueueCnnctDisc.Head = 0;
    gUsbDataList->ICCQueueCnnctDisc.Tail = 0;

    DEBUG((DEBUG_INFO, "USB Ccid binding:\n\t"));
    DEBUG((DEBUG_INFO, "SupportedUsbCcid:%x\n", &SupportedUsbCcid ));
    DEBUG((DEBUG_INFO, "\tInstallUsbCcid:%x\n", &StartUsbCcid));
    DEBUG((DEBUG_INFO, "\tUninstallUsbCcid:%x\n", &StopUsbCcid ));


    // Install driver binding protocol here
    Status = EfiLibInstallDriverBindingComponentName2 (
               ImageHandle,
               SystemTable,
               &gCcidBindingProtocol,
               NULL,
               &gUsbCcidComponentName,
               &gUsbCcidComponentName2
               );

    return Status;

}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
