//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file UsbCcid.c
    AMI USB CCID Device class support driver

**/

#include "AmiUsbRtCcid.h"
#include "Protocol/AmiUsbCcid.h"

extern  USB_GLOBAL_DATA *gUsbData;
extern  USB_DATA_LIST   *gUsbDataList;


//                      Fi   Max  Di
UINT16 gFiFmaxDi[] = {   372,   4, 0, 
                        372,   5, 1, 
                        558,   6, 2,
                        744,   8, 4,
                        1116, 12, 8,
                        1488, 16, 16,
                        1860, 20, 32,
                        0,     0, 64, 
                        0,     0, 12,
                        512,   5, 20,
                        768,   7,  0,
                        1024, 10,  0,
                        1536, 15,  0,
                        2048, 20,  0,
                        0,     0,  0,
                        0,     0,  0
                        };

/**
 Type:        Function Dispatch Table

    This is the table of functions used by USB CCID API

**/

API_FUNC gUsbCcidApiTable[] = {

    UsbCcidSmartClassDescriptor,  // USB Mass API Sub-Func 00h
    UsbCcidAtr,                   // USB Mass API Sub-Func 01h
    UsbCcidPowerupSlot,           // USB Mass API Sub-Func 02h
    UsbCcidPowerDownSlot,         // USB Mass API Sub-Func 03h
    UsbCcidGetSlotStatus,         // USB Mass API Sub-Func 04h
    UsbCcidXfrBlock,              // USB Mass API Sub-Func 05h
    UsbCcidGetParameters,         // USB Mass API Sub-Func 06h

    UsbSCardReaderConnect,        // USB Mass API Sub-Func 07h
    UsbSCardReaderDisConnect,     // USB Mass API Sub-Func 08h
    UsbSCardReaderStatus,         // USB Mass API Sub-Func 09h
    UsbSCardReaderTransmit,       // USB Mass API Sub-Func 0Ah
    UsbSCardReaderControl,        // USB Mass API Sub-Func 0Bh
    UsbSCardReaderGetAttrib,      // USB Mass API Sub-Func 0Ch
};

/**
    This routine delays for specified number of micro seconds

    @param Usec      Amount of delay (count in 1 microsec)


**/

VOID
EFIAPI
FixedDelay(
    UINTN           Usec
)
{
    gBS->Stall(Usec);
    return;
}

/**
    This function is part of the USB BIOS CCID API 
    This API returns 36h bytes of SMART Class Descriptor to the caller. 
    Input Buffer of 36h bytes long is provided by the caller.
    
    @param Urp    Pointer to the URP structure
                  Urp->RetValue USB_SUCESS if data is returned
    @retval None

**/
VOID
UsbCcidSmartClassDescriptor(
    IN OUT URP_STRUC *Urp
)
{
   
    DEV_INFO    *DevInfo;
    CCID_DEV_INFO   *CcidDevData;


    DevInfo = (DEV_INFO *) (Urp->ApiData.CcidSmartClassDescriptor.DevInfo);

    // Check whether it is a valid CCID Device
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }
       
    CopyMem((UINT8 *)(Urp->ApiData.CcidSmartClassDescriptor.ResponseBuffer),
            (UINT8 *)CcidDevData->CcidDescriptor, (UINT32)sizeof(SMARTCLASS_DESC));

    Urp->RetValue = USB_SUCCESS;

    return;

}

/**
    This function is part of the USB CCID API .
    This API returns ATR data if present

    @param Urp    Pointer to the URP structure
                  Urp->RetValue : USB_SUCESS if data is returned
    @retval None 

**/
VOID
UsbCcidAtr(
    IN OUT URP_STRUC *Urp

)
{

    DEV_INFO            *DevInfo;
    ICC_DEVICE          *IccDevice;
    CCID_DEV_INFO       *CcidDevData;


    DevInfo = (DEV_INFO *)(Urp->ApiData.CcidAtr.DevInfo);
    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }

    Urp->RetValue = USB_ERROR;

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidAtr.Slot);

    if (IccDevice) {
        if (IccDevice->ConfiguredStatus & ATRDATAPRESENT) {
            CopyMem((UINT8 *)(Urp->ApiData.CcidAtr.ATRData),
                    (UINT8 *)IccDevice->RawATRData, MAX_ATR_LENGTH);
            Urp->RetValue = USB_SUCCESS;
        }
    }

    return;

}

/**
    This function is part of the USB BIOS CCID API 
    This API powers up the particular slot in CCID and returns ATR data if successful
    @param Urp    Pointer to the URP structure
                  Urp->RetValue : USB_SUCESS if data is returned
    @retval None 



**/
VOID
UsbCcidPowerupSlot (
    IN OUT URP_STRUC *Urp

)
{

    EFI_STATUS  Status;    
    DEV_INFO    *DevInfo;
    ICC_DEVICE  *IccDevice;
    CCID_DEV_INFO       *CcidDevData;

    DevInfo = (DEV_INFO *) (Urp->ApiData.CcidPowerupSlot.DevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }
   
    //
    // Locate the ICCDevice 
    //
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidPowerupSlot.Slot);

    if (IccDevice) {
        //
        // The slot has been already discovered. Check the status.
        //
        if (IccDevice->ConfiguredStatus & VOLTAGEAPPLIED) {
            //
            // Power down the device
            //
            PCtoRDRIccPowerOff (DevInfo, IccDevice);
            RDRToPCSlotStatus(DevInfo, IccDevice);
        }
    }

    Status = ICCInsertEvent(DevInfo, Urp->ApiData.CcidPowerupSlot.Slot);

    //
    // If the card has been successfully poweredup copy ATR data
    //
    if (!IccDevice) {
        IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidPowerupSlot.Slot);
        if (!IccDevice) {
            Urp->RetValue = USB_ERROR;
            return;
        }
    }
    Urp->ApiData.CcidPowerupSlot.Status = IccDevice->Status;
    Urp->ApiData.CcidPowerupSlot.Error = IccDevice->Error;

    if (IccDevice->ConfiguredStatus & ATRDATAPRESENT) {
        CopyMem((UINT8 *)(Urp->ApiData.CcidPowerupSlot.ATRData),
                (UINT8 *)IccDevice->RawATRData, MAX_ATR_LENGTH);      
    }

    Urp->RetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR){
        Urp->RetValue = USB_ERROR;
    }

    return;

}


/**
    This function is part of the USB BIOS CCID API 
    This API powers down the particular slot.
    
    @param Urp    Pointer to the URP structure\
                  Urp->RetValue : USB_SUCESS if data is returned
    @retval None 

**/
VOID
UsbCcidPowerDownSlot(
    IN OUT URP_STRUC *Urp
)
{
    
    EFI_STATUS  Status = EFI_SUCCESS;
    DEV_INFO    *DevInfo;
    ICC_DEVICE  *IccDevice;
    CCID_DEV_INFO       *CcidDevData;

    DevInfo = (DEV_INFO *)(Urp->ApiData.CcidPowerdownSlot.DevInfo);

    Urp->RetValue = USB_ERROR;

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidPowerdownSlot.Slot);

    if (IccDevice) {
        //
        // The slot has been already discovered. Check the status.
        //
        if (IccDevice->ConfiguredStatus & ICCPRESENT) {
            //
            // Power down the device
            //
            Status = PCtoRDRIccPowerOff (DevInfo, IccDevice);
            RDRToPCSlotStatus(DevInfo, IccDevice);

            IccDevice->ConfiguredStatus &= (~VOLTAGEAPPLIED);

            Urp->ApiData.CcidPowerdownSlot.Status = IccDevice->Status;
            Urp->ApiData.CcidPowerdownSlot.Error = IccDevice->Error;

        }
    }

    Urp->RetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->RetValue = USB_ERROR;
    }

    return;

}

/**
    This function is part of the USB BIOS MASS API 
    This API returns information from RDR_to_PC_SlotStatus. 

    @param Urp    Pointer to the URP structure.
                  Urp->RetValue : USB_SUCESS if data is returned
    @retval None 

**/
VOID
UsbCcidGetSlotStatus (
    IN OUT URP_STRUC *Urp
)
{
    
    EFI_STATUS  Status;
    DEV_INFO    *DevInfo;
    ICC_DEVICE  *IccDevice;
    CCID_DEV_INFO       *CcidDevData;

    DevInfo = (DEV_INFO *) (Urp->ApiData.CcidGetSlotStatus.DevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidGetSlotStatus.Slot);
    if (!IccDevice || !(IccDevice->ConfiguredStatus & ICCPRESENT)) {
        Urp->ApiData.CcidGetSlotStatus.Status = 0x42; 
        Urp->ApiData.CcidGetSlotStatus.Error = 0xFE;
        Urp->RetValue = USB_ERROR;
        return;
    }
    
    //
    // Issue the cmd
    //
    Status = PCToRDRGetSlotStatus(DevInfo, IccDevice);
    
    if (EFI_ERROR(Status)) {
        Urp->RetValue = USB_ERROR;
        return;        
    }

    //
    // Get the response
    //
    Status = RDRToPCSlotStatus(DevInfo, IccDevice);

    Urp->ApiData.CcidGetSlotStatus.Status = IccDevice->Status;
    Urp->ApiData.CcidGetSlotStatus.Error = IccDevice->Error;
    Urp->ApiData.CcidGetSlotStatus.ClockStatus = IccDevice->ClockStatus;

    Urp->RetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->RetValue = USB_ERROR;
    }

    return;

}


/**
    This function is part of the USB BIOS MASS API.
    This API excutes PC_to_RDR_XfrBlock cmd and returns the response from 
    RDR_to_PC_DataBlock to the caller.
           
    @param Urp    Pointer to the URP structure.
                  Urp->RetValue : USB_SUCESS if data is returned
    @retval None 



**/

VOID
UsbCcidXfrBlock (
    IN OUT URP_STRUC *Urp
)
{

    EFI_STATUS  Status = EFI_SUCCESS;
    DEV_INFO    *DevInfo;
    ICC_DEVICE  *IccDevice;
    UINT32      CmdLength = (UINT32)Urp->ApiData.CcidXfrBlock.CmdLength;
    UINT8       *CmdBuffer = (UINT8 *)Urp->ApiData.CcidXfrBlock.CmdBuffer;
    UINT8       IsBlock = (BOOLEAN)Urp->ApiData.CcidXfrBlock.ISBlock;
    UINT32      *ResponseLength = (UINT32 *)&(Urp->ApiData.CcidXfrBlock.ResponseLength);
    UINT8       *ResponseBuffer = (UINT8 *)(Urp->ApiData.CcidXfrBlock.ResponseBuffer);
    CCID_DEV_INFO       *CcidDevData;

    DevInfo = (DEV_INFO *)(Urp->ApiData.CcidXfrBlock.DevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidXfrBlock.Slot);

    if (!IccDevice || !(IccDevice->ConfiguredStatus & ICCPRESENT)) {
        Urp->ApiData.CcidXfrBlock.Status = 0x42; 
        Urp->ApiData.CcidXfrBlock.Error = 0xFE;
        Urp->RetValue = USB_ERROR;
        return;
    }


    //
    // Only T0/T1 are recognized
    //
    if (IccDevice->ProtocolNum > 1) {
        Urp->RetValue = USB_ERROR;        
        return;
    } 

    //
    // Check for T0/T1
    //
    if (IccDevice->ProtocolNum) {    
        switch (((SMARTCLASS_DESC*)CcidDevData->CcidDescriptor)->Features & 0x70000) {

            case TDPU_LEVEL_EXCHANGE:

                Status = TxRxT1TDPUChar (DevInfo, IccDevice, CmdLength, CmdBuffer, IsBlock, ResponseLength, ResponseBuffer);
                break;

            case CHARACTER_LEVEL_EXCHANGE:

                Status = TxRxT1TDPUChar (DevInfo, IccDevice, CmdLength, CmdBuffer, IsBlock, ResponseLength, ResponseBuffer);
                break;

            case SHORT_ADPU_LEVEL_EXCHANGE:
            case EXT_ADPU_LEVEL_EXCHANGE:
        
                Status = TxRxT1Adpu(DevInfo, IccDevice, CmdLength, CmdBuffer, ResponseLength, ResponseBuffer);
                break;
        }
    } else {
        // T0 not supported yet
        Urp->RetValue = USB_ERROR;        
        return;
    }

    Urp->ApiData.CcidXfrBlock.Status = IccDevice->Status;
    Urp->ApiData.CcidXfrBlock.Error = IccDevice->Error;

    Urp->RetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->RetValue = USB_ERROR;
    }

    return;

}

/**
    This function is part of the USB BIOS CCID API.
    This API returns the response to RDR_to_PCParameters cmd
    
    @param Urp    Pointer to the URP structure.
                  Urp->RetValue : USB_SUCESS if data is returned
    @retval None 

**/
VOID
UsbCcidGetParameters (
    IN OUT URP_STRUC *Urp

)
{
    
    EFI_STATUS  Status;
    DEV_INFO    *DevInfo;
    ICC_DEVICE  *IccDevice;
    CCID_DEV_INFO       *CcidDevData;

    DevInfo = (DEV_INFO *)(Urp->ApiData.CcidGetParameters.DevInfo);

    //
    // Check whether it is a valid CCID Device
    //
    if (!DevInfo) {
        Urp->RetValue = USB_ERROR;
        return;
    }
    CcidDevData = &DevInfo->CcidDevData;

    if (!CcidDevData) {
        Urp->RetValue = USB_ERROR;
        return;
    }    
    if (!CcidDevData->CcidDescriptor) {
        Urp->RetValue = USB_ERROR;
        return;
    }

    //
    // Locate the ICCDevice 
    //
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.CcidGetParameters.Slot);
    if (!IccDevice || !(IccDevice->ConfiguredStatus & ICCPRESENT)) {
        Urp->ApiData.CcidGetParameters.Status = 0x42; 
        Urp->ApiData.CcidGetParameters.Error = 0xFE;
        Urp->RetValue = USB_ERROR;
        return;
    }

    // Should we check for device presence in data area. The call will find that out anyways.

    //    
    // Issue the cmd
    //
    Status = PCToRDRGetParameters(DevInfo, IccDevice);
    
    if (EFI_ERROR(Status)) {
        Urp->RetValue = USB_ERROR;
        return;        
    }

    //
    // Get the response
    //
    Status = RDRToPCParameters(DevInfo, IccDevice);
    if (!EFI_ERROR(Status)) {
        Urp->ApiData.CcidGetParameters.ResponseLength = 6;
        if (IccDevice->ProtocolNum) {
            Urp->ApiData.CcidGetParameters.ResponseLength = 8;
        }
        //
        // Update the Data
        //
        CopyMem((UINT8 *)(Urp->ApiData.CcidGetParameters.ResponseBuffer),
                (UINT8 *)&(IccDevice->ProtocolNum),
                (UINT32)(Urp->ApiData.CcidGetParameters.ResponseLength));
    }

    Urp->ApiData.CcidGetParameters.Status = IccDevice->Status;
    Urp->ApiData.CcidGetParameters.Error = IccDevice->Error;

    Urp->RetValue = USB_SUCCESS;

    if (Status == EFI_DEVICE_ERROR) {
        Urp->RetValue = USB_ERROR;
    }

    return;

}

/**
    This function is part of the USB BIOS CCID API. It refers to 
    SCardConnect API of EFI SMART CARD READER PROTOCOL.

    @param Urp    Pointer to the URP structure.
    @retval None 

**/

VOID
UsbSCardReaderConnect(
    IN OUT URP_STRUC *Urp
) 
{
    EFI_STATUS      Status;
    DEV_INFO        *DevInfo;
    ICC_DEVICE      *IccDevice;
    UINT8           Slot;
    UINT32          AccessMode;
    UINT32          CardAction;
    UINT32          PreferredProtocols;
    CCID_DEV_INFO   *CcidDevData;
    UINT8          IccPreferredProtocols;

    // Get the Input Parameter passed to the EFI Smart Card reader Protocol API
    Slot = Urp->ApiData.SmartCardReaderConnect.Slot;
    DevInfo = (DEV_INFO *)(Urp->ApiData.SmartCardReaderConnect.DevInfo);
    AccessMode = Urp->ApiData.SmartCardReaderConnect.AccessMode;
    CardAction = Urp->ApiData.SmartCardReaderConnect.CardAction;
    PreferredProtocols = Urp->ApiData.SmartCardReaderConnect.PreferredProtocols;

    // Get the respective ICC_DEVICE structure for the SCardReader Slot
    IccDevice = GetIccDevice(DevInfo, Slot);
    CcidDevData = &DevInfo->CcidDevData;
 
    if (!IccDevice || !CcidDevData || !CcidDevData->CcidDescriptor) {
        //*ReturnStatus = EFI_NOT_FOUND;
        Urp->ApiData.SmartCardReaderConnect.EfiStatus = EFI_NOT_FOUND;
        return;
    }


    // Already card is connected
    if (IccDevice->SlotConnectStatus) {
        //*ReturnStatus = EFI_ACCESS_DENIED;
        Urp->ApiData.SmartCardReaderConnect.EfiStatus = EFI_ACCESS_DENIED;
        return;
    }

    if (AccessMode == SCARD_AM_READER) {

        if (!((IccDevice->ConfiguredStatus & (ICCPRESENT | VOLTAGEAPPLIED | ATRDATAPRESENT))
                == (ICCPRESENT | VOLTAGEAPPLIED | ATRDATAPRESENT))) {
            // Call to configure the SMART CARD READER if the slot is not active
            Status = ConfigureCcid(DevInfo, IccDevice);
            // Voltage applied but ICC ATR is not retrieved As ICC card is not available
            // it is not an error for SCARD_AM_READER connect
            if (Status == EFI_NOT_FOUND) {
                return;
            }
        }
        //*ReturnStatus = EFI_SUCCESS;
        Urp->ApiData.SmartCardReaderConnect.EfiStatus = EFI_SUCCESS;
        IccDevice->SlotConnectStatus = SCARD_AM_READER;
        return;
    } else {

        Status = EFI_DEVICE_ERROR;

        switch (CardAction) {
            case SCARD_CA_NORESET:
                // Check if SMART card reader slot is already configured, If configured already return Active Protocol
                if (((IccDevice->ConfiguredStatus & (ICCPRESENT | VOLTAGEAPPLIED | ATRDATAPRESENT))
                        == (ICCPRESENT | VOLTAGEAPPLIED | ATRDATAPRESENT))) {
                    // Check Preferred Protocol mask contain an Active Protocol, return success if supported
                    IccPreferredProtocols = (UINT8)PreferredProtocols;
                    if (((1 << IccDevice->ProtocolNum) & IccPreferredProtocols) == (1 << IccDevice->ProtocolNum)) {

                         Status = EFI_SUCCESS;
                     } else {
                         Status = EFI_INVALID_PARAMETER;
                     }
                } else {
                    // Power up and Configure Slot 
                    Status = ConfigureCcid(DevInfo, IccDevice);
                }
                break;

            case SCARD_CA_COLDRESET:
                // Power Off the ICC device if it is already Power on and Active
                // Cold Reset starts with Power Off, Power On Device at below (SCARD_CA_WARMRESET)
                PCtoRDRIccPowerOff (DevInfo, IccDevice);

                Status = RDRToPCSlotStatus(DevInfo, IccDevice);
                if (EFI_ERROR(Status)) {
                   break;
                }
            case SCARD_CA_WARMRESET:
                // Power on and configure the ICC device
                Status = ConfigureCcid(DevInfo, IccDevice);
                break;

            case SCARD_CA_UNPOWER:
                // Send Power Off command to the ICC device
                PCtoRDRIccPowerOff (DevInfo, IccDevice);
                Status = RDRToPCSlotStatus(DevInfo, IccDevice);
                break;
            case SCARD_CA_EJECT:
                Status = EFI_UNSUPPORTED;
                break;
            default:
                Status = EFI_SUCCESS;
                break;
        }

        *(UINT32*)Urp->ApiData.SmartCardReaderConnect.ActiveProtocol = (1 << IccDevice->ProtocolNum);

        //*ReturnStatus = Status;
        Urp->ApiData.SmartCardReaderConnect.EfiStatus = Status;

        if (!EFI_ERROR(Status)) {
            IccDevice->SlotConnectStatus = SCARD_AM_CARD;
        } 
    }
    return;
}

/**
    This function is part of the USB BIOS MASS API. It refers to 
    SCardDisConnect API of EFI SMART CARD READER PROTOCOL.

    @param Urp    Pointer to the URP structure.
    @retval None 

**/
VOID
UsbSCardReaderDisConnect(
    IN OUT URP_STRUC *Urp
)
{
    DEV_INFO        *DevInfo;
    ICC_DEVICE      *IccDevice;
    UINT32          CardAction;
    EFI_STATUS      Status = EFI_UNSUPPORTED;
    CCID_DEV_INFO   *CcidDevData;

    DevInfo = (DEV_INFO *)(Urp->ApiData.SmartCardReaderDisconnect.DevInfo);
    CardAction = Urp->ApiData.SmartCardReaderDisconnect.CardAction;
        
    // Get the respective ICC_DEVICE structure for the CCID Slot
    IccDevice = GetIccDevice(DevInfo, 
                             Urp->ApiData.SmartCardReaderDisconnect.Slot);

    CcidDevData = &DevInfo->CcidDevData;

    if (!IccDevice || !CcidDevData || !CcidDevData->CcidDescriptor) {
        Urp->ApiData.SmartCardReaderDisconnect.EfiStatus = EFI_INVALID_PARAMETER;
        return;
    }

    switch (CardAction) {
        case SCARD_CA_EJECT:
            if (IccDevice->SlotConnectStatus == SCARD_AM_READER) {
                // Reader SCardConnect call is made, return Unsupported
                Urp->ApiData.SmartCardReaderDisconnect.EfiStatus = EFI_UNSUPPORTED;
                return;
            }
            break;
        case SCARD_CA_COLDRESET:
        case SCARD_CA_WARMRESET:
        case SCARD_CA_UNPOWER:
            PCtoRDRIccPowerOff (DevInfo, IccDevice);
            Status = RDRToPCSlotStatus(DevInfo, IccDevice);
            break;
        case SCARD_CA_NORESET:
            Status = EFI_SUCCESS;
            break;
    }

    IccDevice->SlotConnectStatus = 0;
    
    Urp->ApiData.SmartCardReaderDisconnect.EfiStatus = Status;
    return;
}

/**
    This function updates the input parameter(State) with Smart card status

    @param CcidCmdStatus      Ccid command status
    @param State              Smart card state

    @retval  None

**/

void
UpdateICCState(
    UINT8  CcidCmdStatus,
    UINT32 *State
)
{
    switch (CcidCmdStatus & 0x07)
    {
    case 0: *State = SCARD_ACTIVE;
            break;
    case 1: *State = SCARD_INACTIVE;
            break;
    case 2: *State = SCARD_ABSENT;
            break;
    default:
        *State = SCARD_UNKNOWN;
    }
    return;
}

/**
    This function updates Smart card Atr information

    @param IccDevice         Pointer to Icc(Integrated Circuit(s) Card)device data structure
    @param Atr               Atr data
    @param AtrLength         Length of Atr data

    @retval  EFI_SUCCESS      On success
    @retval  Others           error

**/
EFI_STATUS
UpdateSCardReaderAtrData(
    ICC_DEVICE    *IccDevice,
    UINT8         *Atr,
    UINTN         *AtrLength
)
{
    // Return error if input is not valid
    if (!Atr || !AtrLength) {
        return EFI_INVALID_PARAMETER;
    }

    if (*AtrLength < sizeof(ATR_DATA) ) {
        *AtrLength = sizeof(ATR_DATA);
        return EFI_BUFFER_TOO_SMALL;
    }

    if (IccDevice) {
       if (IccDevice->ConfiguredStatus & ATRDATAPRESENT) {
           CopyMem(Atr, (UINT8 *)IccDevice->RawATRData, MAX_ATR_LENGTH);
       } else {
           return EFI_DEVICE_ERROR;
       }
    }

    return EFI_SUCCESS;
}

/**
    This function is part of the USB BIOS CCID API. It refers to 
    SCardStatus API of EFI SMART CARD READER PROTOCOL

    @param Urp    Pointer to the URP structure.
    @retval None 

**/

VOID
UsbSCardReaderStatus(
   IN OUT URP_STRUC *Urp
)
{
    EFI_STATUS   Status;
    DEV_INFO     *DevInfo;
    ICC_DEVICE   *IccDevice;
    UINT32       *State;
    UINT32       *CardProtocol;
    UINT8        *Atr;
    UINTN        *AtrLength;
    CCID_DEV_INFO   *CcidDevData;

    DevInfo = (DEV_INFO *)(Urp->ApiData.SmartCardReaderStatus.DevInfo);
    State = (UINT32*)Urp->ApiData.SmartCardReaderStatus.State;
    CardProtocol = (UINT32*)Urp->ApiData.SmartCardReaderStatus.CardProtocol;
    Atr = (UINT8*)Urp->ApiData.SmartCardReaderStatus.Atr;
    AtrLength = (UINTN*)Urp->ApiData.SmartCardReaderStatus.AtrLength;

    // Get ICC device Interface
    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.SmartCardReaderStatus.Slot);

    CcidDevData = &DevInfo->CcidDevData;

    if (!IccDevice || !CcidDevData || !CcidDevData->CcidDescriptor) {
        Urp->ApiData.SmartCardReaderStatus.EfiStatus = EFI_DEVICE_ERROR;
        return;
    }

    if (IccDevice->SlotConnectStatus == 0) {
       Urp->ApiData.SmartCardReaderStatus.EfiStatus = EFI_INVALID_PARAMETER;
       return;
    }

    if (State != NULL) {
         // Send command to get status of the Scard Reader slot
         PCToRDRGetSlotStatus(DevInfo, IccDevice);
         Status = RDRToPCSlotStatus(DevInfo, IccDevice);
         if (EFI_ERROR(Status)) {
             //*ReturnStatus = Status;
             Urp->ApiData.SmartCardReaderStatus.EfiStatus = Status;
             return;
         }   
         UpdateICCState(IccDevice->Status, State);
    }

    if (CardProtocol) {
        *CardProtocol = (1 << IccDevice->ProtocolNum);
    }

    Status = UpdateSCardReaderAtrData(IccDevice, Atr, AtrLength);

    //*ReturnStatus = Status;
    Urp->ApiData.SmartCardReaderStatus.EfiStatus = Status;
    return;
}

/**
    This function is part of the USB BIOS CCID API. Used to transfer command to smard card.

    @param Urp    Pointer to the URP structure.
    @retval None 

**/

VOID
UsbSCardReaderTransmit(
    IN OUT URP_STRUC *Urp
)
{
    ICC_DEVICE   *IccDevice;
    URP_STRUC    XfrBlockUrp;
    DEV_INFO     *DevInfo;
    CCID_DEV_INFO   *CcidDevData;

    DevInfo = (DEV_INFO*)Urp->ApiData.SmartCardReaderTransmit.DevInfo;

    IccDevice = GetIccDevice(DevInfo, Urp->ApiData.SmartCardReaderTransmit.Slot);

    CcidDevData = &DevInfo->CcidDevData;

    if (!IccDevice || !CcidDevData ||!CcidDevData->CcidDescriptor) {
        Urp->ApiData.SmartCardReaderTransmit.EfiStatus = EFI_DEVICE_ERROR;
        return;
    }

    if (IccDevice->SlotConnectStatus == 0) {
        Urp->ApiData.SmartCardReaderTransmit.EfiStatus = EFI_INVALID_PARAMETER;
        return;
    }

    ZeroMem(&XfrBlockUrp, sizeof (URP_STRUC));

    XfrBlockUrp.ApiData.CcidXfrBlock.CmdLength = Urp->ApiData.SmartCardReaderTransmit.CAPDULength;
    XfrBlockUrp.ApiData.CcidXfrBlock.CmdBuffer = (UINTN)Urp->ApiData.SmartCardReaderTransmit.CAPDU;
    XfrBlockUrp.ApiData.CcidXfrBlock.ISBlock = I_BLOCK;
    XfrBlockUrp.ApiData.CcidXfrBlock.ResponseLength = *(UINTN *)(Urp->ApiData.SmartCardReaderTransmit.RAPDULength);
    XfrBlockUrp.ApiData.CcidXfrBlock.ResponseBuffer = (UINTN)Urp->ApiData.SmartCardReaderTransmit.RAPDU;

    XfrBlockUrp.ApiData.CcidXfrBlock.DevInfo = (UINTN)DevInfo;
    XfrBlockUrp.ApiData.CcidXfrBlock.Slot = Urp->ApiData.SmartCardReaderTransmit.Slot;

    UsbCcidXfrBlock(&XfrBlockUrp);

    *(UINTN *)(Urp->ApiData.SmartCardReaderTransmit.RAPDULength) = XfrBlockUrp.ApiData.CcidXfrBlock.ResponseLength;

    if (Urp->RetValue) {
        Urp->ApiData.SmartCardReaderTransmit.EfiStatus = EFI_DEVICE_ERROR;
    } else {
        Urp->ApiData.SmartCardReaderTransmit.EfiStatus = EFI_SUCCESS;
    }
    return;
}

/**
    This function is part of the USB BIOS CCID API.

    @param Urp    Pointer to the URP structure.
    @retval None 

**/
VOID
UsbSCardReaderControl (
    IN OUT URP_STRUC *Urp
)
{
    return;
}

/**
    This function is part of the USB BIOS CCID API.
    The function gets the card reader attrubute
    
    @param Urp    Pointer to the URP structure.
    @retval None 

**/
VOID
UsbSCardReaderGetAttrib (
    IN OUT URP_STRUC *Urp
)
{
    return;
}

/**
    PC_TO_RDR_XFRBLOCK cmd is issued to the device
    This function sends PC_TO_RDR_XFRBLOCK to the device. 
    See section 6.1.4 of CCID spec 1.1 for the details.

    Input  
    @param DevInfo            Pointer to devInfo structure
    @param ICCDevice          Pointer to ICC_DEVICE structure
    @param CmdLength          Command length
    @param CmdBuffer          Command data buffer
    @param BlockWaitingTime   Block waiting time
    @param LevelParameter     Level parameter
    
    @retval EFI_SUCCESS       Success
    @retval Others            Error
          
**/
EFI_STATUS
PCToRDRXfrBlock (
    IN DEV_INFO             *DevInfo,
    IN ICC_DEVICE           *ICCDevice,
    IN UINT32               CmdLength,
    IN UINT8                *CmdBuffer,
    IN UINT8                BlockWaitingTime,
    IN UINT16               LevelParameter    

)
{

    EFI_STATUS                      Status = EFI_SUCCESS;
    PC_TO_RDR_XFRBLOCK_STRUC        *CcidCmdBuffer;
    UINT32                          Data;
    UINT32                          Index;  

    DEBUG((DEBUG_INFO, "PCToRDRXfrBlock ...."));
  
    CcidCmdBuffer = AllocatePool(sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength);
    if (!CcidCmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    ZeroMem((UINT8 *)CcidCmdBuffer, sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength);

    //
    // Prepare  the cmd buffer
    //
    CcidCmdBuffer->MessageType = PC_TO_RDR_XFRBLOCK;
    CcidCmdBuffer->Length = CmdLength;
    CcidCmdBuffer->Slot = ICCDevice->Slot;
    CcidCmdBuffer->Seq = gUsbData->CcidSequence;
    CcidCmdBuffer->BWI = BlockWaitingTime;
    CcidCmdBuffer->LevelParameter = LevelParameter;

    //
    // Copy the cmd
    //
    if (CmdLength) {
        CopyMem((UINT8 *)CcidCmdBuffer + sizeof(PC_TO_RDR_XFRBLOCK_STRUC),
                CmdBuffer, CmdLength);
    }


    DEBUG((DEBUG_INFO, "\n"));
    for (Index = 0; Index < sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength; Index++) {
        DEBUG((DEBUG_INFO, "%02X ", ((UINT8 *)CcidCmdBuffer)[Index]));
    }
    DEBUG((DEBUG_INFO, "\n"));

    Data = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CcidCmdBuffer, 
                                    sizeof(PC_TO_RDR_XFRBLOCK_STRUC) + CmdLength
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!Data) {
        Status = EFI_DEVICE_ERROR;
    }

    FreePool(CcidCmdBuffer);
    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;
    
}

/**
    PC_TO_RDR_ICCPOWERON cmd is issued to the CCID
    See section 6.1.1 of CCID spec Rev 1.1 for more details
        
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure
    @param PowerLevel         00:Automatic  Voltage selection, 01:5.0v, 02:3.0v, 03:1.8v

    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
PCtoRDRIccPowerOn(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN UINT8            PowerLevel
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_ICCPOWERON_STRUC    PcToRdrCmd;
    PC_TO_RDR_ICCPOWERON_STRUC     *CmdBuffer = &PcToRdrCmd;
    UINT32                        Data;

    DEBUG ((DEBUG_INFO, "PCtoRDRIccPowerOn .... PowerLevel : %x...", PowerLevel));

    ZeroMem((UINT8 *)CmdBuffer, sizeof(PC_TO_RDR_ICCPOWERON_STRUC));

    //
    // Prepare  the cmd buffer
    //
    CmdBuffer->MessageType = PC_TO_RDR_ICCPOWERON;
    CmdBuffer->Length = 0;
    CmdBuffer->Slot = ICCDevice->Slot;
    CmdBuffer->Seq = gUsbData->CcidSequence;
    CmdBuffer->PowerSlot = PowerLevel;
    CmdBuffer->RFU = 0;

    Data = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CmdBuffer, 
                                    sizeof(PC_TO_RDR_ICCPOWERON_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!Data) {
        Status = EFI_DEVICE_ERROR;
    }

    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;

}


/**
    PC_TO_RDR_ICCPOWEROFF cmd is issued to the CCID
    See section 6.1.2 of CCID spec Rev 1.1 for more details
    
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure


    @retval EFI_SUCCESS       Success
    @retval Others            Error


**/
EFI_STATUS
PCtoRDRIccPowerOff(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice
)
{

    EFI_STATUS                  Status = EFI_SUCCESS;
    PC_TO_RDR_ICCPOWEROFF_STRUC PcToRdrCmd;
    PC_TO_RDR_ICCPOWEROFF_STRUC *CmdBuffer = &PcToRdrCmd;
    UINT32                      Data;

    DEBUG((DEBUG_INFO, "PCtoRDRIccPowerOff ...."));

    ZeroMem((UINT8 *)CmdBuffer, sizeof(PC_TO_RDR_ICCPOWEROFF_STRUC));

    //
    // Prepare the buffer
    //
    CmdBuffer->MessageType = PC_TO_RDR_ICCPOWEROFF;
    CmdBuffer->Length = 0;
    CmdBuffer->Slot = ICCDevice->Slot;
    CmdBuffer->Seq = gUsbData->CcidSequence;

    Data = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CmdBuffer, 
                                    sizeof(PC_TO_RDR_ICCPOWEROFF_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!Data) {
        Status = EFI_DEVICE_ERROR;
    }
    else {
        ICCDevice->ConfiguredStatus = 0;
    }

    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;

}

/**
    PC_TO_RDR_GETSLOTSTATUS cmd is issued to CCID
    See section 6.1.3 of CCID spec Rev 1.1 for more details
    
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure


    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
PCToRDRGetSlotStatus(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_GETSLOT_STATUS_STRUC PcToRdrCmd;
    PC_TO_RDR_GETSLOT_STATUS_STRUC *CmdBuffer = &PcToRdrCmd;
    UINT32                        Data;

    DEBUG((DEBUG_INFO, "PCToRDRGetSlotStatus ...."));

    ZeroMem((UINT8 *)CmdBuffer, sizeof(PC_TO_RDR_GETPARAMETERS_STRUC));
    
    //
    // Prepare cmd buffer
    //
    CmdBuffer->MessageType = PC_TO_RDR_GETSLOTSTATUS;
    CmdBuffer->Slot = ICCDevice->Slot;
    CmdBuffer->Seq = gUsbData->CcidSequence;

    Data = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CmdBuffer, 
                                    sizeof(PC_TO_RDR_GETSLOT_STATUS_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!Data) {
        Status = EFI_DEVICE_ERROR;
    }


    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;

}


/**
    PC_TO_RDR_GETPARAMETERS cmd is issued to CCID
    See section 6.1.5 of CCID spec Rev 1.1 for more details
    
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure


    @retval EFI_SUCCESS       Success
    @retval Others            Error
            
**/
EFI_STATUS
PCToRDRGetParameters(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_GETPARAMETERS_STRUC PcToRdrCmd;
    PC_TO_RDR_GETPARAMETERS_STRUC *CmdBuffer = &PcToRdrCmd;
    UINT32                        Data;

    DEBUG((DEBUG_INFO, "PCToRDRGetParameters ...."));

    ZeroMem((UINT8 *)CmdBuffer, sizeof(PC_TO_RDR_GETPARAMETERS_STRUC));

    //
    // Prepare cmd buffer
    //
    CmdBuffer->MessageType = PC_TO_RDR_GETPARAMETERS;
    CmdBuffer->Slot = ICCDevice->Slot;
    CmdBuffer->Seq = gUsbData->CcidSequence;

    Data = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CmdBuffer, 
                                    sizeof(PC_TO_RDR_GETPARAMETERS_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!Data) {
        Status = EFI_DEVICE_ERROR;
    }


    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;

}

/**
    PC_TO_RDR_SETPARAMETERS cmd is issued to CCID
    See section 6.1.7 of CCID spec Rev 1.1 for more details
    
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure
    @param ProtocolNum        0 : T=0, 1 : T=1
    @param Data               Points to data from abProtocolDataStructure
    
    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
PCToRDRSetParameters(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN UINT8            ProtocolNum,
    IN VOID             *Data
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_SETPARAMETERS_T0_STRUC *CmdBuffer;
    UINT32                        DwData;
    UINT8                        Length = ProtocolNum == 0 ? sizeof(PROTOCOL_DATA_T0) : sizeof(PROTOCOL_DATA_T1);

    DEBUG ((DEBUG_INFO, "PCToRDRSetParameters .... ProtocolNum : %x ", ProtocolNum));

    CmdBuffer = AllocatePool(Length + sizeof(RDR_HEADER));
    if (!CmdBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    ZeroMem((UINT8 *)CmdBuffer, Length + sizeof(RDR_HEADER));

    //
    // Prepare 
    //
    CmdBuffer->MessageType = PC_TO_RDR_SETPARAMETERS;
    CmdBuffer->Length = Length;
    CmdBuffer->Slot = ICCDevice->Slot;
    CmdBuffer->Seq = gUsbData->CcidSequence;
    CmdBuffer->ProtocolNum = ProtocolNum;

    CopyMem((UINT8 *)CmdBuffer + sizeof(RDR_HEADER), (UINT8 *)Data, Length);

    DwData = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CmdBuffer, 
                                    Length + sizeof(RDR_HEADER)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!DwData) {
        Status = EFI_DEVICE_ERROR;
    }

    FreePool(CmdBuffer);

    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;

}

/**
    PC_TO_RDR_SETDATARATEANDCLOCK cmd is issued. 
    Response for this cmd is from RDR_TO_PC_DATARATEANDCLOCK
    See section 6.1.14 of CCID spec Rev 1.1 for more detail
         
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 
    @param ClockFrequency     ICC Clock Frequency in KHz
    @param DataRate           ICC data rate in bpd

    @retval EFI_SUCCESS       Success
    @retval Others            Error
    
**/
EFI_STATUS
PCToRDRSetDataRateAndClockFrequency(
    IN DEV_INFO          *DevInfo,
    IN ICC_DEVICE        *ICCDevice,
    IN UINT32            ClockFrequency, 
    IN UINT32            DataRate
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC PcToRdrCmd;
    PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC *CmdBuffer = &PcToRdrCmd;
    UINT32                        Data;

    DEBUG ((DEBUG_INFO, "PCToRDRSetDataRateAndClockFrequency ...."));

    ZeroMem((UINT8 *)CmdBuffer, sizeof(PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC));

    //
    // Prepare cmd buffer
    //
    CmdBuffer->MessageType = PC_TO_RDR_SETDATARATEANDCLOCK;
    CmdBuffer->Length = 8;
    CmdBuffer->Slot = ICCDevice->Slot;
    CmdBuffer->Seq = gUsbData->CcidSequence;
    CmdBuffer->CloclFrequency = ClockFrequency;
    CmdBuffer->DataRate = DataRate;

    Data = UsbCcidIssueBulkTransfer(DevInfo, 0, 
                                    (UINT8 *)CmdBuffer, 
                                    sizeof(PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY_STRUC)
                                    );

    //
    // Handle Error if any. This error is due to blk transfer
    //
    if (!Data) {
        Status = EFI_DEVICE_ERROR;
    }

    DEBUG((DEBUG_INFO, "%r ....", Status));

    return Status;

}

/**
    RDR_TO_PC_DATABLOCK cmd is issued to the CCID. 
    This is on response to PCI_to_RDR_XfrBlock
    See section 6.2.1 of CCID spec Rev 1.1 for more details  
         
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 
    @param Length             Length of bytes in Buffer
    @param Buffer             Points to abData in RDR_TO_PC_DATABLOCK

    @retval EFI_SUCCESS       Success
    @retval Others            Error
     
**/
EFI_STATUS
RDRToPCDataBlock(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN OUT UINT32       *Length,
    OUT UINT8           *Buffer

)
{    

    EFI_STATUS      Status = EFI_SUCCESS;
    RDR_TO_PC_DATABLOCK_STRUC*  ReceiveBuffer;
    UINT32          Data;
    UINT8           Iterations = 3;
    UINT32          Index;   

    //
    // Allocate memory for receiving data
    //
    ReceiveBuffer = AllocatePool(sizeof(RDR_TO_PC_DATABLOCK_STRUC) + *Length);
    if (!ReceiveBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    ZeroMem((UINT8 *)ReceiveBuffer, sizeof(RDR_TO_PC_DATABLOCK_STRUC) + *Length);

    do {
        //
        // Get the response 
        //
        ReceiveBuffer->MessageType = RDR_TO_PC_DATABLOCK;
        ReceiveBuffer->Length = *Length;
        ReceiveBuffer->Slot = ICCDevice->Slot;
        ReceiveBuffer->Seq = gUsbData->CcidSequence;
        ReceiveBuffer->Status = 0;
        ReceiveBuffer->Error = 0;
        ReceiveBuffer->ChainParameter = 0;

        Data = UsbCcidIssueBulkTransfer(DevInfo, BIT7, 
                                        (UINT8 *)ReceiveBuffer, 
                                        sizeof(RDR_TO_PC_DATABLOCK_STRUC) + *Length
                                        );

        DEBUG((DEBUG_INFO, "\n"));

        for (Index =0; Index < sizeof(RDR_TO_PC_DATABLOCK_STRUC) + ReceiveBuffer->Length; Index++) {
            DEBUG((DEBUG_INFO, "%02X ", ((UINT8 *)ReceiveBuffer)[Index]));
        }

        DEBUG((DEBUG_INFO, "\n"));

        //    
        // Handle Error if any. This error is due to blk transfer
        //
        if (!Data) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCDataBlock;
        }    

        //
        // Check for time extension 
        //
        if ((ReceiveBuffer->Status & 0xC0) == 0x80) {
            FixedDelay(ReceiveBuffer->Error * ICCDevice->WaitTime * 1000);  
        } else {
            break;
        }

        Iterations--;
    } while (Iterations);    

    // Should the cmd be aborted if the response isn't received???

    //
    // Processed without error if Zero
    //
    if (ReceiveBuffer->Status & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((ReceiveBuffer->Status & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }
    }

    if (Iterations && !EFI_ERROR(Status)) {
    
        ICCDevice->ChainParameter = ReceiveBuffer->ChainParameter;

        //
        // If response is successful get the data
        //
        if (ReceiveBuffer->Length && ReceiveBuffer->Length <= *Length) {
    
            // Copy data 
            CopyMem(Buffer,
                    (UINT8 *)ReceiveBuffer + sizeof(RDR_TO_PC_DATABLOCK_STRUC),
                    ReceiveBuffer->Length);

        }

        if  (ReceiveBuffer->Length > *Length) {
            Status = EFI_BUFFER_TOO_SMALL;
        }

        //
        // Update the o/p buffer length
        //
        *Length = ReceiveBuffer->Length;

    } else {

        Status = EFI_DEVICE_ERROR;
        *Length = 0;
    }

    //
    // Save the last cmd status 
    //
    ICCDevice->Status = ReceiveBuffer->Status;
    ICCDevice->Error = ReceiveBuffer->Error;


    //    
    // if success exit
    //
    if (!EFI_ERROR(Status) && !ICCDevice->Status) {
        Status =  EFI_SUCCESS;
        goto exit_RDRToPCDataBlock;
    }

    // Card not present?
    Status = EFI_NOT_FOUND;
    if ((ReceiveBuffer->Status & 7) == 2) goto exit_RDRToPCDataBlock;

    //
    // Other errors
    //
    Status = EFI_DEVICE_ERROR;

exit_RDRToPCDataBlock:

    gUsbData->CcidSequence++;

    FreePool(ReceiveBuffer);
    DEBUG((DEBUG_INFO, " Status : %r bStatus : %02X bError : %02X\n", Status, ICCDevice->Status, ICCDevice->Error));
    
    return Status;

}

/**
    RDR_TO_PC_SLOTSTATUS cmd is issued to CCID.
    See section 6.2.2 of CCID spec Rev 1.1 for more details.
        
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 

    @retval EFI_SUCCESS       Success
    @retval Others            Error

    
**/
EFI_STATUS
RDRToPCSlotStatus(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice
)
{

    EFI_STATUS                  Status = EFI_SUCCESS;
    RDR_TO_PC_SLOTSTATUS_STRUC  RdrToPcCmd;
    RDR_TO_PC_SLOTSTATUS_STRUC  *ReceiveBuffer = &RdrToPcCmd;
    UINT32                      Data;
    UINT8                       Iterations = 3;    

    ZeroMem((UINT8 *)ReceiveBuffer, sizeof(RDR_TO_PC_SLOTSTATUS_STRUC));
    do {
        //
        // Read the PCSlot Status
        //
        ReceiveBuffer->MessageType = RDR_TO_PC_SLOTSTATUS;
        ReceiveBuffer->Length = 0;
        ReceiveBuffer->Slot = ICCDevice->Slot;
        ReceiveBuffer->Seq = gUsbData->CcidSequence;

        Data = UsbCcidIssueBulkTransfer(DevInfo, BIT7, 
                                        (UINT8 *)ReceiveBuffer, 
                                        sizeof(RDR_TO_PC_SLOTSTATUS_STRUC)
                                        );

        //
        // Handle Error if any. This error is due to blk transfer
        //
        if (!Data) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCSlotStatus;
        }

        //
        // Check for time extension 
        //
        if ((ReceiveBuffer->Status & 0xC0) == 0x80) {
            FixedDelay(ReceiveBuffer->Error * ICCDevice->WaitTime * 1000);  
        } else {
            break;
        }

        Iterations--;
    } while (Iterations);


    //
    // Save the last cmd status 
    //
    ICCDevice->Status = ReceiveBuffer->Status;
    ICCDevice->Error = ReceiveBuffer->Error;

    // Processed without error if Zero
    if (ReceiveBuffer->Status & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((ReceiveBuffer->Status & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }

    }

    if (Iterations && !EFI_ERROR(Status)) {
        //
        // Update the last ClockStatus
        //
        ICCDevice->ClockStatus = ReceiveBuffer->ClockStatus; 
    } else {
        Status = EFI_DEVICE_ERROR;
    }

exit_RDRToPCSlotStatus:

    gUsbData->CcidSequence++;

    DEBUG((DEBUG_INFO, " Status :  %r Status : %02X Error : %02X\n", Status, ICCDevice->Status, ICCDevice->Error));

    return Status;
}

/**
    RDR_TO_PC_SLOTSTATUS cmd is issued
    See section 6.2.3 of CCID spec Rev 1.1 for more details
         
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 

    @retval EFI_SUCCESS       Success
    @retval Others            Error
       
**/
EFI_STATUS
RDRToPCParameters(
    IN DEV_INFO           *DevInfo,
    IN ICC_DEVICE        *ICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    RDR_TO_PC_PARAMETERS_T1_STRUC RdrToPcCmd;
    RDR_TO_PC_PARAMETERS_T1_STRUC *ReceiveBuffer = &RdrToPcCmd;
    UINT32                        Data;
    UINT8                         Iterations = 3;

    ZeroMem((UINT8 *)ReceiveBuffer, sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC));

    do {

        //
        // Read the PCSlot Status
        //
        ReceiveBuffer->Header.MessageType = RDR_TO_PC_PARAMETERS;
        ReceiveBuffer->Header.Length = 0;
        ReceiveBuffer->Header.Slot = ICCDevice->Slot;
        ReceiveBuffer->Header.Seq = gUsbData->CcidSequence;

        Data = UsbCcidIssueBulkTransfer(DevInfo, BIT7, 
                                        (UINT8 *)ReceiveBuffer, 
                                        sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC)
                                        );

        //
        // Handle Error if any. This error is due to blk transfer
        //
        if (!Data) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCParameters;
        }

        //
        // Check for time extension 
        //
        if ((ReceiveBuffer->Header.Status & 0xC0) == 0x80) {
           FixedDelay(ReceiveBuffer->Header.Error * ICCDevice->WaitTime * ICCDevice->ETU);  
        } else {
           break;
        }

        Iterations--;

    } while (Iterations);

    //
    // Save the last cmd status 
    //
    ICCDevice->Status = ReceiveBuffer->Header.Status;
    ICCDevice->Error = ReceiveBuffer->Header.Error;

    //
    // Processed without error if Zero
    //
    if (ReceiveBuffer->Header.Status & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((ReceiveBuffer->Header.Status & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }

    }

    if (Iterations && !EFI_ERROR(Status)) {

        //
        // Update the Data
        //
        CopyMem((UINT8 *)&(ICCDevice->ProtocolNum),
                (UINT8 *)&(ReceiveBuffer->Header.Data),
                sizeof(RDR_TO_PC_PARAMETERS_T1_STRUC) - 9);

    } else {
        Status = EFI_DEVICE_ERROR;
    }

exit_RDRToPCParameters:

    gUsbData->CcidSequence++;

    DEBUG((DEBUG_INFO, " Status :  %r Status : %02X Error : %02X\n", Status, ICCDevice->Status, ICCDevice->Error));

    PrintPCParameters((UINT8 *)&(ICCDevice->ProtocolNum));

    return Status;

}


/**
    RDR_TO_PC_DATARATEANDCLOCK cmd is issued. 
    Returns dwClockFrequency and dwDataRate.See section 6.2.5 of CCID spec Rev 1.1 for more details.
         
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 

    @retval EFI_SUCCESS       Success
    @retval Others            Error
         
**/
EFI_STATUS
RDRToPCDataRateAndClockFrequency(
    IN DEV_INFO          *DevInfo,
    IN ICC_DEVICE        *ICCDevice
)
{

    EFI_STATUS                    Status = EFI_SUCCESS;
    RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC  RdrToPcCmd;
    RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC  *ReceiveBuffer = &RdrToPcCmd;
    UINT32                        Data;
    UINT8                        Iterations = 3;    

    ZeroMem((UINT8 *)ReceiveBuffer, sizeof(RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC));

    do {

        //
        // Read the PCSlot Status
        //
        ReceiveBuffer->MessageType = RDR_TO_PC_DATARATEANDCLOCK;
        ReceiveBuffer->Length = 8;
        ReceiveBuffer->Slot = ICCDevice->Slot;
        ReceiveBuffer->Seq = gUsbData->CcidSequence;

        Data = UsbCcidIssueBulkTransfer(DevInfo, BIT7, 
                                        (UINT8 *)ReceiveBuffer, 
                                        sizeof(RDR_TO_PC_DATARATEANDCLOCKFREQUENCY_STRUC));

        //
        // Handle Error if any. This error is due to blk transfer
        //
        if (!Data) {
            Status = EFI_DEVICE_ERROR;
            goto exit_RDRToPCDataRateAndClockFrequency;
        }

        //
        // Check for time extension 
        //
        if ((ReceiveBuffer->Status & 0xC0) == 0x80) {
            FixedDelay(ReceiveBuffer->Error * ICCDevice->WaitTime * 1000);  
        } else {
            break;
        }

        Iterations--;

    } while (Iterations);


    //
    // Processed without error if Zero
    //
    if (ReceiveBuffer->Status & 0xC0) {
        Status = EFI_DEVICE_ERROR;

        if ((ReceiveBuffer->Status & 0x3) == 0x2) {        
            Status = EFI_NOT_FOUND;
        }
    }

    if (Iterations && !EFI_ERROR(Status)) {

         ICCDevice->ClockFrequency = ReceiveBuffer->ClockFrequency; 
         ICCDevice->DataRate = ReceiveBuffer->DataRate;

    } else {

        Status = EFI_DEVICE_ERROR;

    }

    //
    // Save the last cmd status 
    //
    ICCDevice->Status = ReceiveBuffer->Status;
    ICCDevice->Error = ReceiveBuffer->Error;

exit_RDRToPCDataRateAndClockFrequency:

    gUsbData->CcidSequence++;

    DEBUG((DEBUG_INFO, " Status :  %r bStatus : %02X bError : %02X\n", 
                Status, ICCDevice->Status, ICCDevice->Error));

    DEBUG((DEBUG_INFO, " dwClockFrequency :  %4x dwDataRate : %4x\n", 
                ICCDevice->ClockFrequency, ICCDevice->DataRate));

    return Status;

}

/**
    Transmit/Receive T1 ADPU
          
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 
    @param CmdLength          Command length
    @param CmdBuffer          Command buffer
    @param ResponseLength     Response length
    @param ResponseLength     Response length

    @retval EFI_SUCCESS       Success
    @retval Others            Error


**/
EFI_STATUS
TxRxT1Adpu (
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN UINT32           CmdLength,
    IN UINT8            *CmdBuffer,
    OUT UINT32          *ResponseLength,
    OUT UINT8           *ResponseBuffer
)
{

    EFI_STATUS  Status;

    //
    // Issue the cmd
    //
    Status = PCToRDRXfrBlock(DevInfo, ICCDevice, CmdLength, CmdBuffer, 0, 0);
    
    if (EFI_ERROR(Status)){
        return Status;        
    }

    //
    // Get the response
    //
    Status = RDRToPCDataBlock(DevInfo, ICCDevice, ResponseLength, ResponseBuffer);

    return Status;
}

/**
    Transmit/Receive T1 TDPU/Character         
           
    @param DevInfo          Pointer to devInfo structure
    @param ICCDevice        Pointer to ICC_DEVICE structure 
    @param CmdLength          Command length
    @param CmdBuffer          Command buffer
    @param ResponseLength     Response length
    @param ResponseLength     Response length

    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
TxRxT1TDPUChar (
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN UINT32           CmdLength,
    IN UINT8            *CmdBuffer,
    IN UINT8            ISBlock,
    IN OUT UINT32       *ResponseLength,
    OUT UINT8           *ResponseBuffer
)
{

    EFI_STATUS  Status;
    UINT8       Pcb = ISBlock;


    UINT32      IBlockFrameLength = 0;      // Used for I-Block
    UINT8       *IBlockFrame = NULL;

    UINT32      SendBlockFrameLength = 0;   // Place holder for the block currently sent
    UINT8       *SendBlockFrame = NULL;

    UINT32      RBlockFrameLength = 0;      // Used for R-Block
    UINT8       *RBlockFrame = NULL;

    UINT32      SBlockFrameLength = 0;      // Used for S-Block
    UINT8       *SBlockFrame = NULL;

    UINT32      lResponseLength = 0;        // Response buffer for all the blocks I/S/R
    UINT32      OrglResponseLength = 0;     
    UINT8       *lResponseBuffer;

    UINT8       wLevelParameter = 0;

    UINT8       bBWIByte = 0;    

    UINT32      UserBufferLength = *ResponseLength;
    UINT32      lResponseBufferAddDataPtr = 0;
    CCID_DEV_INFO   *CcidDevData;



    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return EFI_DEVICE_ERROR;
   
    
    // Initialize Chaining is off
    ICCDevice->Chaining = FALSE;
    *ResponseLength  = 0;

    // Update Pcb with Nas only for IBlocks
    if (!ISBlock) {
        Pcb = ((ICCDevice->NaSInterface & 1) << 6);
    }

    Status = ConstructBlockFrame(DevInfo, ICCDevice, 
                                ICCDevice->NAD, Pcb, 
                                CmdLength, CmdBuffer, 
                                &wLevelParameter, &IBlockFrameLength, 
                                &IBlockFrame
                                );        


    if (EFI_ERROR(Status)) { 
        return Status;
    }

    SendBlockFrameLength = IBlockFrameLength;
    SendBlockFrame = IBlockFrame;

    if (UserBufferLength < 2)  lResponseLength = 2;

    lResponseLength += (UserBufferLength + 3 + (ICCDevice->EpilogueFields == 0 ? 1 :  2));

    lResponseBuffer = AllocatePool(lResponseLength);
    ASSERT(lResponseBuffer);
    if (!lResponseBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    ZeroMem(lResponseBuffer, lResponseLength);

    OrglResponseLength = lResponseLength;

    ICCDevice->T1CharCmdDataPhase = TRUE; // Always Cmd Phase first

    do {
        UINT8       ReceiveStatus;
        Status = PCToRDRXfrBlock(DevInfo, ICCDevice, 
                                SendBlockFrameLength, SendBlockFrame, 
                                bBWIByte, wLevelParameter
                                );

        if (EFI_ERROR(Status)){
            break;        
        }

        //
        // Get the response
        //
        lResponseLength = OrglResponseLength - lResponseBufferAddDataPtr;
        Status = RDRToPCDataBlock(DevInfo, ICCDevice, &lResponseLength, lResponseBuffer + lResponseBufferAddDataPtr);

        if (EFI_ERROR(Status)){
            break;        
        }

        // Check for errors
        ReceiveStatus = HandleReceivedBlock(DevInfo, ICCDevice, 
                                            IBlockFrameLength, IBlockFrame, 
                                            SendBlockFrameLength, SendBlockFrame, 
                                            lResponseBuffer
                                            );        

        bBWIByte = 0;

        switch (ReceiveStatus) {

            case BLOCK_TRANSMISION_SUCCESS:
                break;
    
            case RESEND_BLOCK:
                break;

            case SEND_R_BLOCK_1:
            case SEND_R_BLOCK_0:

                // Check if Chaining is in progress
                if (ICCDevice->Chaining) {

                    // Copy the data from lResponseBuffer to the user buffer
                    //
                    // If success copy the data to Response buffer
                    //
                    //if (lResponseBuffer[2] && ((UserBufferLength - *ResponseLength) < lResponseBuffer[2])) {
                        //Status = EFI_BUFFER_TOO_SMALL;        
                    //}
                    CopyMem(ResponseBuffer + *ResponseLength, lResponseBuffer + 3, lResponseBuffer[2]);
                    *ResponseLength +=  lResponseBuffer[2];
                    lResponseBufferAddDataPtr = 0;          // Reset to use the lResponseBuffer from the beginning
                    
                    // Clear out the PCB/length feild so that by mistake the buffer is interpreted as valid data
                    lResponseBuffer[1] = 0;
                    lResponseBuffer[2] = 0;
                    lResponseLength = OrglResponseLength;
                    
                }
                Status = ConstructBlockFrame(DevInfo, ICCDevice,    
                                            ICCDevice->NAD, ReceiveStatus == SEND_R_BLOCK_1 ? 0x80 | 0x10 : 0x80, 
                                            0, NULL, &wLevelParameter, 
                                            &RBlockFrameLength, &RBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }
                SendBlockFrameLength = RBlockFrameLength;
                SendBlockFrame = RBlockFrame;
                ICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case I_BLOCK_RESEND:

                Status = ConstructBlockFrame(DevInfo, ICCDevice, 
                                            ICCDevice->NAD, Pcb, CmdLength, 
                                            CmdBuffer, &wLevelParameter, 
                                            &IBlockFrameLength, &IBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }
                SendBlockFrameLength = IBlockFrameLength;
                SendBlockFrame = IBlockFrame;
                ICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case WTX_RESPONSE:

                bBWIByte = lResponseBuffer[3];

                Status = ConstructBlockFrame(DevInfo, ICCDevice, 
                                            ICCDevice->NAD, WTX_RESPONSE, 
                                            lResponseBuffer[2], lResponseBuffer + 3, 
                                            &wLevelParameter, &SBlockFrameLength, 
                                            &SBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }

                SendBlockFrameLength = SBlockFrameLength;
                SendBlockFrame = SBlockFrame;
                ICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case GET_DATA_T1_CHAR:
                
                //
                // Issue a PCToRDRXfrBlock with dwLength to zero. 
                // Check Page 68 of CCID spec Rev 1.1, Apr 22, 2005
                //

                SendBlockFrameLength = 0;
                // Assumption : only LRC is supported
                wLevelParameter = lResponseBuffer[2] + 1; 

                //
                // Since the prologue is received in the first three bytes increment 
                // the address so that data is recived after that  
                //
                lResponseBufferAddDataPtr += 3;   

                //
                // Indicate it is data phase now                  
                //
                ICCDevice->T1CharCmdDataPhase = FALSE;  
                break;

            case IFS_RESPONSE:
                Status = ConstructBlockFrame(DevInfo, ICCDevice, 
                                            ICCDevice->NAD, IFS_RESPONSE, 
                                            lResponseBuffer[2], lResponseBuffer + 3, 
                                            &wLevelParameter, &SBlockFrameLength, 
                                            &SBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }

                SendBlockFrameLength = SBlockFrameLength;
                SendBlockFrame = SBlockFrame;
                ICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            case ABORT_RESPONSE:
                 Status = ConstructBlockFrame(DevInfo, ICCDevice, 
                                            ICCDevice->NAD, ABORT_RESPONSE, 
                                            lResponseBuffer[2], lResponseBuffer + 3, 
                                            &wLevelParameter, &SBlockFrameLength, 
                                            &SBlockFrame
                                            );        

                if (EFI_ERROR(Status)) {
                    ReceiveStatus = BLOCK_TRANSMISSION_TERMINATE;
                }

                SendBlockFrameLength = SBlockFrameLength;
                SendBlockFrame = SBlockFrame;
                ICCDevice->T1CharCmdDataPhase = TRUE;
                break;

            default:
                break;
                        
        }

        if (ReceiveStatus == BLOCK_TRANSMISION_SUCCESS) {
            break;
        }       
    }while (1);

    //
    // If success copy the data to Response buffer for the last I-Block that was received.
    //
    if (lResponseBuffer[2] && ((UserBufferLength - *ResponseLength) < lResponseBuffer[2])) {
        Status = EFI_BUFFER_TOO_SMALL;        
    }

    if (lResponseBuffer[2] && ((UserBufferLength - *ResponseLength) >= lResponseBuffer[2])) {
        CopyMem(ResponseBuffer + *ResponseLength, lResponseBuffer + 3, lResponseBuffer[2]);
        *ResponseLength +=  lResponseBuffer[2];
    }

    //
    // Free up memory I-Block allocated here
    //
    if (IBlockFrame && IBlockFrameLength) {
        FreePool(IBlockFrame);
    }

    //
    // Free up S-Block memory allocated here
    //
    if (SBlockFrame && SBlockFrameLength) {
        FreePool(SBlockFrame);
    }

    if (lResponseBuffer && OrglResponseLength) {
        FreePool(lResponseBuffer);
    }



    return Status;
}


/**
    Construct the Block Frame for the CCID
        
    @param DevInfo         
    @param ICCDevice        
    @param Nad          
    @param PCB          
    @param InfLength     
    @param InfBuffer    
    @param LevelParameter          
    @param BlockFrameLength     
    @param BlockFrame
    
    
    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
ConstructBlockFrame(
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN UINT8            Nad,
    IN UINT8            PCB,
    IN UINT32           InfLength,
    IN UINT8            *InfBuffer,
    OUT UINT8           *LevelParameter,
    OUT UINT32          *BlockFrameLength,
    OUT UINT8           **BlockFrame
)
{

    UINT32  BufLengthRequired = InfLength + 3 + (ICCDevice->EpilogueFields == 0 ? 1 :  2);
    CCID_DEV_INFO   *CcidDevData;


    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return EFI_DEVICE_ERROR;

    //
    // Check if the input buffer if already allocated is enough for the current case. 
    // If not free it up and allocate again.
    //
    
    if (BufLengthRequired > *BlockFrameLength) {
        if (*BlockFrame) {
            FreePool(*BlockFrame);
            *BlockFrame = NULL;

        }
    }

    *BlockFrameLength = InfLength + 3 + (ICCDevice->EpilogueFields == 0 ? 1 :  2);

    //
    // if BlockFrame is NULL only then allocate memory. Assumption is if Memory 
    // has been allocated before then it is sufficent enough for the length needed.
    //
    if (!*BlockFrame) {
        //
        // Allocate length needed to contruct the Block Frame
        //
         *BlockFrame = AllocatePool(*BlockFrameLength);
        if (!*BlockFrame) {
            return EFI_OUT_OF_RESOURCES;
        }
    }

    ZeroMem(*BlockFrame, *BlockFrameLength);

    (*BlockFrame)[0] = Nad;
    (*BlockFrame)[1] = PCB;
    (*BlockFrame)[2] = (UINT8)InfLength;

    if (InfLength) {
        CopyMem((UINT8 *)(*BlockFrame + 3), (UINT8 *)InfBuffer, InfLength);
    }

    //
    // Update Checksum
    //
    (*BlockFrame)[*BlockFrameLength - 1] = 0;

    if (ICCDevice->EpilogueFields == 0) {
        CalculateLRCChecksum(*BlockFrame, *BlockFrameLength);
    } else {
        return EFI_UNSUPPORTED;
    }

    //
    // For Character transfer update wLevelParameter also
    //
    if (!(((SMARTCLASS_DESC*)CcidDevData->CcidDescriptor)->Features & 0x70000)) {
        *LevelParameter = 3;
    }

    return EFI_SUCCESS;    

}

/**
    Process the Recevied data from CCID device

        
    @param DevInfo 
    @param ICCDevice 
    @param OriginalBlockFrameLength 
    @param OriginalBlockFrame 
    @param SentBlockFrameLength 
    @param SentBlockFrame 
    @param ReceivedBlockFrame 

    @retval EFI_SUCCESS       Success
    @retval Others            Error


    @note  
      For Character exchange control will come twice for S(Response), I-Block with M bit set. So while counting
      number of exchnages this needs to be taken care of.
      Refer to ISO/IEC 7816-1 First edition 1998-10-15 for different scenarios mentioned in this function.

**/
UINT8   
HandleReceivedBlock (
    IN DEV_INFO         *DevInfo,
    IN ICC_DEVICE       *ICCDevice,
    IN UINT32           OriginalBlockFrameLength,
    IN UINT8            *OriginalBlockFrame,
    IN UINT32           SentBlockFrameLength,
    IN UINT8            *SentBlockFrame,
    IN UINT8            *ReceivedBlockFrame
)
{

    UINT8        ReturnParameter = BLOCK_TRANSMISION_SUCCESS;
    BOOLEAN      T1Char;
    CCID_DEV_INFO   *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return BLOCK_TRANSMISSION_TERMINATE;

    T1Char = (((SMARTCLASS_DESC*)CcidDevData->CcidDescriptor)->Features & 0x70000) ? FALSE : TRUE;

    // It is easy to support T1 TDPU & CHAR as they are almost same except that 
    // prologue and data are received separatly in T1 Char.
    // The trick here will be that when data is received we can combine the 
    // previously received prologue and the INF/Epilogue received 
    // later so that it will be similar to T1 TDPU. Then all the processing will be same.

    if (!ReceivedBlockFrame) {    // if no response
        if (ICCDevice->RBlockCounter == 2) {
            return BLOCK_TRANSMISSION_TERMINATE;
        }
        
        // If I-Block sent before and no response, send R-Block with the expected I Block(N(R). Rule 7.1/Rule 7.6
        if (!(SentBlockFrame[1] & 0x80)) { 
            
            ICCDevice->RBlockCounter++;

            if (ICCDevice->NaSCard) {
             return SEND_R_BLOCK_0;
            } else {
                return SEND_R_BLOCK_1;
            }
        }

        return BLOCK_TRANSMISSION_TERMINATE;
    }

    // Reset the RBlock Counter if the response we received isn't a R-Block.
    if ((ReceivedBlockFrame[1] & 0xC0) !=  RBLOCK) {
            ICCDevice->RBlockCounter = 0;
    }

    //
    // Is the block received an I-Block?
    //
    if (!(ReceivedBlockFrame[1] & 0x80)) {

        //
        // It is T1 Char and also if in cmd phase handle it.
        //
        if (T1Char && ICCDevice->T1CharCmdDataPhase)  { 

            // Save the N(s) from the card for later use.
            ICCDevice->NaSCard = (ReceivedBlockFrame[1] & NSBIT) >> 6;

            // If data needs to be received
            if (ReceivedBlockFrame[2]){
                return GET_DATA_T1_CHAR;
            }  else {
                return BLOCK_TRANSMISION_SUCCESS;
            }            

        }

        // It is T1TDPU or it is T1 Char but in data phase

       
        // Is Mbit set, then nothing more to do
        if (!(ReceivedBlockFrame[1] & 0x20)) {
            //
            // Toggle N(S) bit only after a successful I Block Transmission
            //
            ICCDevice->Chaining = FALSE;
            ICCDevice->NaSInterface = !(ICCDevice->NaSInterface);

            return BLOCK_TRANSMISION_SUCCESS;
        }
        else {
            // Since Mbit is set, Send R-Block with the next N(s) expected from card. Section 5, Rules 2.2 and 5
            
            ICCDevice->Chaining = TRUE;

            if (ICCDevice->NaSCard) {
                return SEND_R_BLOCK_0;
            }
            else {
                return SEND_R_BLOCK_1;
            }
        }
    }

    // No difference between T1 Char and T1 Tdpu in R-phase

    //
    // Is the Block received is a R block?
    //
    if (ReceivedBlockFrame){ 
        if((ReceivedBlockFrame[1] & 0xC0) ==  RBLOCK) {
        // Is there an error?
            if (ReceivedBlockFrame[1] & 0x03) {
                //Re-transmit it
                if ((SentBlockFrame[1] & 0xc0) == 0x00) {
                    return  I_BLOCK_RESEND;
                }
                else {
                    return RESEND_BLOCK;
                }
            }

            if (T1Char && ICCDevice->T1CharCmdDataPhase) {
                return  GET_DATA_T1_CHAR;
            }

            if (ICCDevice->RBlockCounter == 3) {
                ICCDevice->RBlockCounter = 0;
                return BLOCK_TRANSMISSION_TERMINATE;
            }
            ICCDevice->RBlockCounter++;

            if (ICCDevice->Chaining == FALSE) {
                //
                // if the received  R-Block is same as the last sent I-Block AND Chaining is not in progress, resend I-Block. Scenario 8
                //
                if ((ReceivedBlockFrame[1] & 0x10) >> 4 == (ICCDevice->NaSInterface & 1) << 6) {
                    return I_BLOCK_RESEND;
                } 
                else {
                    //
                    // Scenario 11/12
                    //
                    if (ICCDevice->NaSInterface & 1) {
                        return SEND_R_BLOCK_1;
                    } else {
                        return SEND_R_BLOCK_0;
                    }
                }
            }
            else { 
                //
                // Chaining is in progress...
                //
                //   
                // Scenario 5
                //
                if ((ReceivedBlockFrame[1] & 0x10) >> 4 != (ICCDevice->NaSInterface & 1) << 6) {
                    // return I_BLOCK;
                }
                //
                // Scenario 23
                //
                if (ReceivedBlockFrame[1]  == SentBlockFrame[1]) {
                    if (ReceivedBlockFrame[1] & 0x10) {
                        return SEND_R_BLOCK_1;
                    } else {
                        return SEND_R_BLOCK_0;
                    }
                }
            }
            // We can try giving S-Synch also if it doesn't respond to R-Block. 
            // S-Synch can be done only for 2nd Iblock on-wards.
        }
    }
    //
    // Is the Block Received is a S block? 
    //
    if ((ReceivedBlockFrame[1] & 0xC0) == 0xC0) {

        switch (ReceivedBlockFrame[1]) {

            case IFS_REQUEST:

               if (T1Char && ICCDevice->T1CharCmdDataPhase) {
                    ReturnParameter = GET_DATA_T1_CHAR;
                    break;
                }
                // Save the new IFSD data
                ICCDevice->IFSD = ReceivedBlockFrame[3];
                ReturnParameter = IFS_RESPONSE;
                break;

            case IFS_RESPONSE:
                //
                // It is T1 Char and also if in cmd phase handle it.
                //
                if (T1Char && ICCDevice->T1CharCmdDataPhase)  { 

                    // If data needs to be received
                    if (ReceivedBlockFrame[2]){
                        return GET_DATA_T1_CHAR;
                    }  else {
                        return BLOCK_TRANSMISION_SUCCESS;
                    }            
                }  
                break;

            case ABORT_REQUEST:
                    ICCDevice->Chaining = FALSE;
                    ReturnParameter = ABORT_RESPONSE;
                    break;

            case ABORT_RESPONSE:
                break;

            case WTX_REQUEST:

                if (T1Char && ICCDevice->T1CharCmdDataPhase) {
                    ReturnParameter = GET_DATA_T1_CHAR;
                    break;
                }

                ReturnParameter = WTX_RESPONSE;
                break;                

            case RESYNCH_RESPONSE:
                break;

            case WTX_RESPONSE:              // Won't be received from card. Card will only generate WTX request.
                break;        
            case RESYNCH_REQUEST:           // Card won't issue ReSynch
                break;
            default:
                break;

        }  
  
    }                

   return ReturnParameter;

}

/**
    Calculates LRC checksum

    @param BlockFrame
    @param BlockFrameLength

    @retval None
**/
VOID
CalculateLRCChecksum (
    UINT8       *BlockFrame, 
    UINT32      BlockFrameLength
)
{
    UINT32  Index = 0;

    for (; Index < BlockFrameLength - 1; Index++ ){
        BlockFrame[BlockFrameLength-1] ^= BlockFrame[Index];
    }
    
    return;
}

/**
    Search the linked list to find the ICC_DEVICE for the given slot number.

    @param DevInfo      Pointer to the DevInfo structure
    @param Slot           Slot number

    @retval ICCDevice   Pointer to the Icc device structure
    @retval NULL          Can not find any ICC_DEVICE

**/
ICC_DEVICE*
GetIccDevice(
    DEV_INFO        *DevInfo, 
    UINT8            Slot
)
{
    
    LIST_ENTRY    *Link;
    CCID_DEV_INFO *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;
    if(!CcidDevData) return NULL;

    for (Link = CcidDevData->IccDeviceList.ForwardLink;
        Link != &CcidDevData->IccDeviceList; Link = Link->ForwardLink ) {
        ICC_DEVICE    *ICCDevice;
        ICCDevice = BASE_CR(Link, ICC_DEVICE, Link);

        //
        // Slot # matches
        //
        if ((ICCDevice->Signature == ICC_DEVICE_SIG) && (ICCDevice->Slot == Slot)) {
            return ICCDevice;
        }      

    }

    return NULL;
}

/**
    The routine update the Transmision protocol supported and other 
    timing related data
 
    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure

          
    @retval None

    @note  This function looks into ATR data and updates CLASS A/B/C information, 
              calculates ETU, WaitTime etc
        
**/
VOID
UpdateATRDataInfo(
    DEV_INFO            *DevInfo,
    ICC_DEVICE          *ICCDevice
)
{
    UINT8    Data;
    UINT8    Index =1;

    //
    // T0 is mandatory
    //
    ICCDevice->AtrData.T0 = ICCDevice->RawATRData[Index];
    ICCDevice->AtrData.NumberofHystoricalBytes = ICCDevice->RawATRData[Index] & 0xF;
    Index++;

    //
    // Update TA1
    //
    if (ICCDevice->AtrData.T0 & 0x10) {
        ICCDevice->AtrData.TA1 = ICCDevice->RawATRData[Index];
        ICCDevice->AtrData.TA1Present = TRUE;
        Index++;
    } else {
        //
        // Default value if TA1 is not present
        //
        ICCDevice->AtrData.TA1 = 0x11;
    }

    Data = ICCDevice->AtrData.TA1;
    ICCDevice->GlobalFi = gFiFmaxDi[(Data >> 4) * 3];
    ICCDevice->GlobalFmax = (UINT8)gFiFmaxDi[(Data >> 4) * 3 + 1];
    ICCDevice->GlobalDi = (UINT8)gFiFmaxDi[(Data& 0xF) * 3 + 2];


    //
    // Update TB1
    //
    if (ICCDevice->AtrData.T0 & 0x20) {
        ICCDevice->AtrData.TB1 = ICCDevice->RawATRData[Index];
        ICCDevice->AtrData.TB1Present = TRUE;
        Index++;
    }

    //
    // Update TC1
    //
    if (ICCDevice->AtrData.T0 & 0x40) {
        ICCDevice->AtrData.TC1 = ICCDevice->RawATRData[Index];
        ICCDevice->AtrData.TC1Present = TRUE;
        Index++;
    }

    //
    // Update TD1
    //
    if (ICCDevice->AtrData.T0 & 0x80) {
        ICCDevice->AtrData.TD1 = ICCDevice->RawATRData[Index];
        ICCDevice->AtrData.TD1Present = TRUE;
        Index++;
    }

    if (ICCDevice->AtrData.TD1) {

        //
        // Update TA2
        //
        if (ICCDevice->AtrData.TD1 & 0x10) {
            ICCDevice->AtrData.TA2 = ICCDevice->RawATRData[Index];
            ICCDevice->AtrData.TA2Present = TRUE;
            ICCDevice->SpecificMode = (ICCDevice->AtrData.TA2 & BIT7) ? TRUE : FALSE;
            Index++;
        }

        //
        // Update TB2
        //
        if (ICCDevice->AtrData.TD1 & 0x20) {
            ICCDevice->AtrData.TB2 = ICCDevice->RawATRData[Index];
            ICCDevice->AtrData.TB2Present = TRUE;
            Index++;
        }

        //
        // Update TC2
        //
        if (ICCDevice->AtrData.TD1 & 0x40) {
            ICCDevice->AtrData.TC2 = ICCDevice->RawATRData[Index];
            ICCDevice->AtrData.TC2Present = TRUE;
            Index++;
        }

        //
        // Update TD2
        //
        if (ICCDevice->AtrData.TD1 & 0x80) {
            ICCDevice->AtrData.TD2 = ICCDevice->RawATRData[Index];
            ICCDevice->AtrData.TD2Present = TRUE;
            //Index++;
        }
    }

    //
    // Check if T15 is present else only CLASS A is supported. 
    // By default CLASS A is supported
    //
    ICCDevice->ClassABC = 1;            

    for (Data = 1;  Data < MAX_ATR_LENGTH ;){

        //
        // Is it T15?
        //
        if ((ICCDevice->RawATRData[Data] & 0xF) == 0xF){
            if ((Data + 1) < MAX_ATR_LENGTH) { 
                ICCDevice->ClassABC = ICCDevice->RawATRData[Data + 1] & 0x3F;
                ICCDevice->StopClockSupport = ICCDevice->RawATRData[Data + 1] >> 5;
                ICCDevice->AtrData.TD15 = ICCDevice->RawATRData[Data];
                ICCDevice->AtrData.TD15Present = TRUE;
                ICCDevice->AtrData.TA15 = ICCDevice->RawATRData[Data + 1];
                ICCDevice->AtrData.TA15Present = TRUE;
                break;
            }
        } else {
            // We need info on how many Transmission Protocols are supported by the 
            // card and what are those. Use these loop to do that.
            if (Data > 1) {    // Skip T0
                Index = ICCDevice->TransmissionProtocolSupported;
                ICCDevice->TransmissionProtocolSupported |=  ( 1 << (ICCDevice->RawATRData[Data] & 0x0F));
                if (Index != ICCDevice->TransmissionProtocolSupported) { 
                    ICCDevice->NumofTransmissionProtocolSupported++;
                }
            }

            // No more valid TDx?
            if (!(ICCDevice->RawATRData[Data] & 0x80)) break;
            Data += FindNumberOfTs(ICCDevice->RawATRData[Data]);
        }
    }

    return;
}

/**
    Find the First offerred Transmission protocol.
    Section 8.2.3 ISO 7816-3 2006-11-01: TD1 encodes first offered protocol. 
    If TD1 not present assume T0.

    @param ICCDevice    Pointer to the Icc device structure

    @retval TRANSMISSION_PROTOCOL        

**/
TRANSMISSION_PROTOCOL GetDefaultProtocol (
    ICC_DEVICE        *ICCDevice
)
{

    if (ICCDevice->AtrData.TD1Present) {
        return ICCDevice->AtrData.TD1 & 0xf;
    }

    return T0_PROTOCOL;

}

/**
    CCID which doesn't perform "Automatic parameter config. based on ATR

    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure

    @retval TA1           Best TA1 value

    @note  
  1. Calculate the Baud rate using TA1 value

  2. If in CCID bNumDataRatesSupported = 0 then any value between dwDatRate 
     and dwMaxDataRate is supported

  3. Check if ICC baud rate is less tha dwMaxDataRate. If yes use that.

  4. If  bNumDataRatesSupported is not zero get all possible values and try to 
     match it and use that value.

**/
UINT8 
FindBestTA1Value (
    DEV_INFO        *DevInfo,
    ICC_DEVICE      *ICCDevice
)
{

    UINT32              ICCBaudrate;
    UINT8               Di = ICCDevice->GlobalDi;
    SMARTCLASS_DESC     *CcidDescriptor;
    CCID_DEV_INFO       *CcidDevData;


    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return 0;
   
    CcidDescriptor = (SMARTCLASS_DESC*)CcidDevData->CcidDescriptor;
    //
    // If Automatic parameter conf. based on ATR data is 
    //
    if (CcidDescriptor->Features & AUTO_PARAMETER_CONFIG) {
        return ICCDevice->AtrData.TA1;
    }

    ICCBaudrate =   (ICCDevice->GlobalFmax * 1000 * ICCDevice->GlobalDi)/ICCDevice->GlobalFi;      

    if (CcidDevData->DataRates && CcidDevData->ClockFrequencies) {
    } else {
        if (ICCBaudrate <= CcidDescriptor->MaxDataRate) {
            return ICCDevice->AtrData.TA1;
        } else {
            //
            // Can we decrement the Di value and try to match it
            //
            for ( ; Di ; --Di){
                ICCBaudrate =   (ICCDevice->GlobalFmax * 1000 * Di)/ICCDevice->GlobalFi;                
                if (ICCBaudrate <= CcidDescriptor->MaxDataRate) {
                    return ((ICCDevice->AtrData.TA1 & 0xF0) | Di);
                }
            }
        }
    }

    //
    // Worst case return the default value. 
    // Actuall we should fail saying this CCID/ICC combination isn't supported.
    //
    return ICCDevice->AtrData.TA1;        

}


/**
    Based on the agreed upon TA1 value and Transmission protocol 
    calculate the timing values

    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure
      
    @retval None

**/
VOID
CalculateTimingValues (
    DEV_INFO          *DevInfo,
    ICC_DEVICE        *ICCDevice
)
{

    UINT8   NValue;
    UINT8   Data;
    UINT8    TDCount = 0;

    ICCDevice->FindIndex = ICCDevice->AtrData.TA1;

    //
    // NValue defaults to zero if TC1 not present
    //
    NValue = ICCDevice->AtrData.TC1Present == TRUE ? ICCDevice->AtrData.TC1 : 0;

    //
    // Calculate 1 etu in micro sec
    //
    ICCDevice->ETU = ICCDevice->GlobalFi / (ICCDevice->GlobalDi * ICCDevice->GlobalFmax); 

    //
    // Extra Gaurd Time GT in etu units (section 8.3)
    //
    if (ICCDevice->AtrData.TA15Present) {
        ICCDevice->ExtraGuardTime = (UINT8)(12 +  (NValue / ICCDevice->GlobalFmax  * ICCDevice->GlobalFi/ ICCDevice->GlobalDi));
    } else {
        ICCDevice->ExtraGuardTime = 12 + (NValue / ICCDevice->GlobalFmax) ;          
    }

    // Update Wait Time  (see section 10.2)
    // WT = WI * 960 * Fi /f where WI is TC2
    // Default if TC2 is not present
    /*
    Data = 10;         

    if (FpICCDevice->AtrData.TC2Present) {
        Data = FpICCDevice->AtrData.TC2;
    }    
    */
    //
    // Calculate WT (wait time between two characters) in ETU units
    //
    ICCDevice->WTwaittime = 960 * ICCDevice->GlobalFi/(ICCDevice->GlobalFmax);


    // update Block Width time and Epilogue bit
    // BWT = 11etu + 2 ^ BWI * 960 * Fd /f  (Section 11.4.3)
    // Default BWI is 4. Bit 7:4 in first TB for T1 encodes BWI
    // Fd = 372 (sec section 8.1)

    // Default values (11.4.3)
    ICCDevice->BWI  = 4;
    ICCDevice->CWI =  13;
    ICCDevice->IFSC = 32;
    ICCDevice->IFSD = 32;
    ICCDevice->NAD = 0;

    for (Data = 1;  Data < MAX_ATR_LENGTH; ){

        // Look for the First TD for T= 1. It should from TD2
        if (TDCount < 2) {
            if (ICCDevice->RawATRData[Data] & 0x80) {
                TDCount++;
                Data += FindNumberOfTs(ICCDevice->RawATRData[Data]);
                continue;
            } else {
                break;
            }
        }

        // Is it T1?
        if ((ICCDevice->RawATRData[Data] & 0xF) == 0x1){

            if (ICCDevice->RawATRData[Data] & 0x10) {
                if ((Data + 1) < MAX_ATR_LENGTH) { 
                    ICCDevice->IFSC = ICCDevice->RawATRData[Data + 1];
                }
            }

            if (ICCDevice->RawATRData[Data] & 0x20) {
                if ((Data + 2) < MAX_ATR_LENGTH) { 
                    ICCDevice->BWI = (ICCDevice->RawATRData[Data + 2] & 0xF0) >> 4;
                    ICCDevice->CWI = ICCDevice->RawATRData[Data + 2] & 0xF;
                }
                
            }

            // Section 11.4.4
            if (ICCDevice->RawATRData[Data] & 0x40) {
                if ((Data + 3) < MAX_ATR_LENGTH) { 
                    ICCDevice->EpilogueFields = (ICCDevice->RawATRData[Data + 3] & 0x1);
                }
            }

            break;
        }

        //
        // No more valid TDx?
        //
        if (!(ICCDevice->RawATRData[Data] & 0x80)) break;

        Data += FindNumberOfTs(ICCDevice->RawATRData[Data]);

    }    

    //
    // Block Widthtime in ETU units
    //
    ICCDevice->BWT = (UINT8)((1 << (ICCDevice->BWI - 1)) * 960 * 372 /(ICCDevice->GlobalFmax)) + 11;

    PrintTimingInfo(ICCDevice);

    return;
}

/**
    Issue PPS cmd to select T0/T1
    
    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure
    @param Data           Points to the buffer which is sent to CCID. 
    @param DataLength     Data length

    @retval EFI_SUCCESS       Success
    @retval Others            Error

    @note  
              This command is issued to CCID which doesn't support AUTO_PARAMETER_CONFIG 
              or when default values or not acceptable

**/
EFI_STATUS
IssuePPSCmd(
    DEV_INFO            *DevInfo,
    ICC_DEVICE          *ICCDevice,
    UINT8               *Data,
    UINT8               DataLength
)
{

    EFI_STATUS    Status = EFI_SUCCESS;
    UINT8        *ResponseBuffer;
    UINT32        ResponseLength;
    SMARTCLASS_DESC *CcidDescriptor;
    CCID_DEV_INFO   *CcidDevData;


    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return EFI_DEVICE_ERROR;

    CcidDescriptor = (SMARTCLASS_DESC*)CcidDevData->CcidDescriptor;

    //
    // Allocate memory for receiving data
    //
    ResponseBuffer = AllocatePool(DataLength);
    ASSERT(ResponseBuffer);
    if (!ResponseBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }
    ZeroMem((UINT8 *)ResponseBuffer, DataLength);


    //
    //Check what level of Transmission Protocol is supported
    //
    ResponseLength = 0;
    if (!(CcidDescriptor->Features & 0x70000)) {
        ResponseLength = 2;                                 // For Character exchange only 2 bytes expected.
    }  


    PCToRDRXfrBlock(DevInfo, ICCDevice, DataLength, Data, 0, (UINT16)ResponseLength);
    if (CcidDescriptor->Features & 0x70000) {
        ResponseLength = 4;                                 // For TDPU expected data is 4
    }
    Status = RDRToPCDataBlock(DevInfo, ICCDevice, &ResponseLength, ResponseBuffer);

    // If length is not same and only Character level Transmission is supported, 
    // issue another XfrBlock cmd to get the rest of the data
    if ((ResponseLength != DataLength) && !(CcidDescriptor->Features & 0x70000)) {

        DataLength = (UINT8)ResponseLength;
        ResponseLength = 2;
        PCToRDRXfrBlock(DevInfo, ICCDevice, 0, Data, 0, (UINT16)ResponseLength);
        Status = RDRToPCDataBlock(DevInfo, ICCDevice, &ResponseLength, ResponseBuffer + DataLength);
    
    }

    //
    // I/P and O/P should be identical for success
    //

    FreePool(ResponseBuffer);
    return Status;
}


/**
    Based on the dwFeatures register setting, power up CCID/ICC

    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure

    @retval EFI_SUCCESS       Success
    @retval Others            Error 

    @note  Based on dwFeatures value from SMART Class Descriptor either 
              do an automatic Power-on or go through a manual
              power up sequence and then callect the ATR data.
    
    
**/
EFI_STATUS
VoltageSelection(
    DEV_INFO          *DevInfo,
    ICC_DEVICE        *ICCDevice
)
{

    EFI_STATUS   Status;
    EFI_STATUS   ATRStatus = EFI_DEVICE_ERROR;
    SMARTCLASS_DESC *CcidDescriptor;
    //
    // Get all voltage level supported by CCID
    //
    UINT8        VoltageLevelCcid;        
    //
    // Select the lowest voltage
    //
    UINT8        VoltageMask = VOLT_18;                                                
    //
    // Successful poweron will result in ATR data
    //
    UINT32       BufferLength;                                        

    CCID_DEV_INFO   *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return EFI_DEVICE_ERROR;
   
    CcidDescriptor = (SMARTCLASS_DESC*)CcidDevData->CcidDescriptor;
    VoltageLevelCcid = CcidDescriptor->VoltageSupport; 
    //
    // Make sure the first selection is valid
    //
    do {

        if (VoltageLevelCcid & VoltageMask) {
            break;
        }

        VoltageMask = VoltageMask >> 1;

    }while (VoltageMask);

    //
    // If Automatic Voltage selection is supported go for it. 
    // Discard the initialization done above
    if (CcidDescriptor->Features & AUTO_ACTIVATION_VOLT_SELECTION){
        //
        // Automatic Voltage selection is supported            
        //
        VoltageLevelCcid = AUTO_VOLT;
        VoltageMask = 0;
    }

    do {

        //
        // Issue the cmd to Power it up
        //
        Status = PCtoRDRIccPowerOn (DevInfo, 
                                    ICCDevice, 
                                    ((VoltageLevelCcid & VoltageMask) == 4) ?  3 : VoltageMask);


        if(EFI_ERROR(Status)) { 
            break;
        }

        //
        // Get the response to IccPoweron
        //
        BufferLength = MAX_ATR_LENGTH;
        Status = RDRToPCDataBlock ( DevInfo, 
                                    ICCDevice, 
                                    &BufferLength, 
                                    ICCDevice->RawATRData
                                    );

        //
        // if successfully powered up, ATR data should be available
        //
        if (!EFI_ERROR(Status) && BufferLength) {

            ICCDevice->ConfiguredStatus = (ICCPRESENT | VOLTAGEAPPLIED | ATRDATAPRESENT);

            PrintATRData(ICCDevice->RawATRData);
        
            // From the ATR data, get the required information
            UpdateATRDataInfo(DevInfo, ICCDevice);

            // ATR data got successfully and configured successfully. 
            ATRStatus = EFI_SUCCESS;
            break;

        }

        //
        // if Card not present    
        //
        if ((ICCDevice->Status & 7) == 2) {
            Status = EFI_NOT_FOUND;
            break;
        }

        //
        // ICC is present but some error
        //
        ICCDevice->ConfiguredStatus = ICCPRESENT;

        //
        // Card present but voltage selection is not OK. Power it off and select next voltage
        //
        Status =  PCtoRDRIccPowerOff (DevInfo,  ICCDevice);
        if (EFI_ERROR(Status)) break;

        Status = RDRToPCSlotStatus(DevInfo, ICCDevice);
        if (EFI_ERROR(Status)) break;

        VoltageMask = VoltageMask >> 1;

        //
        // 10 msec delay before applying the next power class Spec 6.2.3
        //
        FixedDelay (10 * 1000);

    } while (VoltageMask);

    // Return the status of the ATR data read and configuration
    return ATRStatus;

}

/**
    Based on the ATR data and the dwFeature register contend 
    do the Rate and Protocol programming


    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure
    @param Data           Points to the buffer which is sent to CCID. 
    @param DataLength     Data length

    @retval EFI_SUCCESS       Success
    @retval Others            Error

    @note  Based on data received from Power-on sequence (ATR data) and dwFetaures value, 
              Speed of communicatin is established.

**/
EFI_STATUS
RateAndProtocolManagement(
    DEV_INFO          *DevInfo,
    ICC_DEVICE        *ICCDevice
)
{

    EFI_STATUS              Status = EFI_SUCCESS;
    PROTOCOL_DATA_T1        Data;
    
    SMARTCLASS_DESC         *CcidDescriptor;
    TRANSMISSION_PROTOCOL   FirstOfferredProtocol;
    UINT32                  ResponseLength;
    UINT8                   ResponseBuffer[20];
    UINT32                  ExchangeLevel;
    BOOLEAN                 ForceSetParams = FALSE;
    CCID_DEV_INFO           *CcidDevData;

    ZeroMem(&Data, sizeof(PROTOCOL_DATA_T1));
    
    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return EFI_DEVICE_ERROR;

    CcidDescriptor = (SMARTCLASS_DESC*)CcidDevData->CcidDescriptor;
    ExchangeLevel = (CcidDescriptor->Features & 0x70000);
    
    FirstOfferredProtocol = GetDefaultProtocol(ICCDevice);

    ICCDevice->ProtocolNum = (UINT8)FirstOfferredProtocol;

    //
    // Check whether TA1 value is good enough for the reader. If not get the right value
    //
    ICCDevice->AtrData.TA1 = FindBestTA1Value(DevInfo, ICCDevice);


    //
    // Check if more than one transmission protocol is supported. 
    // If yes then there may be a need for PPSCmd (ISO 7816-3:2006(E) Sec: 6.3.1)
    // Check if Automatic PPS negotiation done by CCID or not. If not issue one.
    // If TA2 is present Card is in Specific mode. So no need for PPS (7816-3:2006 see sec 6.3 fig 4)
    //

    // When PPS exchange must be made? (Page 19 CCID Rev 1.1) 
    // 1. If both AUTO_PPS_NEGOTIATION_CCID AND AUTO_PPS_NEGOTIATION_ACTIVE are not set PPS must be given in case of TDPU or Character
    //                          OR
    // 2. if AUTO_PPS_NEGOTIATION_ACTIVE is present AND TA2 not present AND the preferred protocol isn't USE_T0_T1_PROTOCOL

    if (((CcidDescriptor->Features & (AUTO_PPS_NEGOTIATION_CCID | AUTO_PPS_NEGOTIATION_ACTIVE)) == 0 &&
        (ExchangeLevel <= 0x10000 ) && !ICCDevice->AtrData.TA2Present) ||
        ((CcidDescriptor->Features & AUTO_PPS_NEGOTIATION_ACTIVE) && !ICCDevice->AtrData.TA2Present && 
         ICCDevice->NumofTransmissionProtocolSupported > 1 && FirstOfferredProtocol != gUsbData->UseT0T1Protocol)) {
        UINT8                   Counter;
        UINT8                   PPSData[] = {0xFF, 0x10, 0x11, 0x00};
        DEBUG((DEBUG_INFO, "IssuePPSCmd ..."));

        //
        // Update PPS data if in case PPSCmd needs to be issued
        //
        PPSData[1] |= FirstOfferredProtocol;

        //
        // Update PPS2
        //
        PPSData[2] = ICCDevice->AtrData.TA1;
    
        //
        // Update checksum
        //
        for (Counter = 0; Counter < sizeof (PPSData) - 1; Counter++) {
            PPSData[sizeof (PPSData) - 1] ^= PPSData[Counter];
        }
    
        Status = IssuePPSCmd(DevInfo, ICCDevice, PPSData, sizeof (PPSData));

        DEBUG((DEBUG_INFO, "%r\n", Status));

        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    DEBUG((DEBUG_INFO, "CcidDescriptor.... Features: %x \n",CcidDescriptor->Features));

    if (CcidDescriptor->Features & AUTO_PARAMETER_CONFIG) {   

        //
        // Issue GetParameters to get the Transmission Protocol and other parameters
        //
        Status = PCToRDRGetParameters(DevInfo, ICCDevice);
        if (EFI_ERROR(Status)) return Status;
    
        Status = RDRToPCParameters(DevInfo, ICCDevice);
        if (EFI_ERROR(Status)) return Status;        

        //if returned parameters is all zero, use the default values.
        // Workaround for Broadcom CCID. GetParametrs always return zero.
        if (!ICCDevice->ProtocolNum && !ICCDevice->FindIndex && !ICCDevice->TCCKST && !ICCDevice->GuardTime \
            && !ICCDevice->WaitingInteger && !ICCDevice->IFSC1 && !ICCDevice->ClockStop && !ICCDevice->NadValue){
            DEBUG((DEBUG_INFO, "Get Parameters is all zero..\n"));
            CalculateTimingValues (DevInfo, ICCDevice);
            ForceSetParams = TRUE;
            ICCDevice->ProtocolNum = FirstOfferredProtocol;
        }
        else {
            ICCDevice->ExtraGuardTime = ICCDevice->GuardTime;
            ICCDevice->WTwaittime = ICCDevice->WaitingInteger;
            ICCDevice->IFSC =  ICCDevice->IFSC1;
            ICCDevice->NAD = ICCDevice->NadValue;
        }

    } else {

        //
        // Now that the TA1 value and the protocol has been finalized, 
        // It is time to calculate the different timing parameters.
        //
        CalculateTimingValues (DevInfo, ICCDevice);
    }

    // Issue SET Params if below two conditions are satisfied
    // Condition 1: If CCID get parameters are all Zero (i.e. Workaround for Broadcom devices) OR
    // Condition 2: Not in specific mode (TA2 is zero) AND
    //              BIT1 not set OR (BIT1 Set but Getparams return non prefered protocol AND
    //              if BIT7 is set OR if BIT 6 and 7 are both not set
    if (
        ForceSetParams == TRUE || \
        (!ICCDevice->AtrData.TA2Present && \
            (!(CcidDescriptor->Features & AUTO_PARAMETER_CONFIG) ||
                // BIT1 set and Protocol we received in Getparams doesn't match the first offered protocol
                ((CcidDescriptor->Features & AUTO_PARAMETER_CONFIG) && ICCDevice->ProtocolNum != FirstOfferredProtocol)) && \
            // If BIT7 is set and not in Specific mode (TA2 non-zero)
            ((CcidDescriptor->Features & AUTO_PPS_NEGOTIATION_ACTIVE ) || \
            // if BIT 6 & 7 are both zero, also not in Specific mode
            (!(CcidDescriptor->Features & (AUTO_PPS_NEGOTIATION_ACTIVE | AUTO_PPS_NEGOTIATION_CCID) ) ) ) \
        )){ 

        DEBUG((DEBUG_INFO, "Set Parameters required..%x\n", ICCDevice->ProtocolNum));

        //
        // Use the superset of the T0/T1 structure (ie T1 structure) even if it is T0. It should work.
        //
        Data.FindDindex = ICCDevice->FindIndex;
        Data.TCCKST1 = ICCDevice->ProtocolNum == 0  ? 0 : (ICCDevice->EpilogueFields | 0x10);
        Data.GuardTimeT1 = ICCDevice->ExtraGuardTime;

        Data.WaitingIntergersT1 = ICCDevice->ProtocolNum == 0  ? 
                                (UINT8)ICCDevice->WTwaittime : (ICCDevice->BWI << 4 | ICCDevice->CWI);

        Data.ClockStop = ICCDevice->ClockStop;
        Data.IFSC = ICCDevice->IFSC;
        Data.NadValue = ICCDevice->NAD;
            
        Status = PCToRDRSetParameters(DevInfo, ICCDevice, ICCDevice->ProtocolNum, (VOID *)&Data);

        if (!EFI_ERROR(Status)){
            Status = RDRToPCParameters(DevInfo, ICCDevice);
        } else {
            return Status; 
        }

        // Work around for Broadcom CCID
        if (ICCDevice->ProtocolNum != FirstOfferredProtocol) {
            DEBUG((DEBUG_INFO, "ProtocolNum %x doesn't match with  FirstOfferredProtocol%x\n", ICCDevice->ProtocolNum, FirstOfferredProtocol));
            ICCDevice->ProtocolNum =  FirstOfferredProtocol;
        }
    }

    //
    // Based on T0 or T1 update Waittime. For T0 use WTWaittime, for T1 use BWT. 
    //
    if (ICCDevice->ProtocolNum) {
        ICCDevice->WaitTime = ICCDevice->BWT;
    } else {
        ICCDevice->WaitTime = ICCDevice->WTwaittime;            
    }

    //
    // If Automatic ICC Clock Freq AND Automatic Buad Rate selection 
    // isn't supported issue SetDataRateAndClock cmd
    //
    if (!(CcidDescriptor->Features & (AUTO_BAUD_RATE_SELECTION |AUTO_ICC_CLOCK_FREQ))){

    }

    //
    // Check if IFSC/IFSD needs to be increased. Default value is 0x20. T1 and TDPU/Char needs this cmd.
    //
    if (ICCDevice->ProtocolNum){ 
    	UINT8    SetIFS[] = {0xFC};   
        switch(CcidDescriptor->Features & 0x70000) { 
            case CHARACTER_LEVEL_EXCHANGE:
                // Both SUZCR90 and O2Micro oz77c6l1 didn't respond to SBlock call below without this delay
                FixedDelay(10 * 1000);      // 10msec delay. No break. Let the flow continue below.
            case TDPU_LEVEL_EXCHANGE:
              ResponseLength = 1;
                SetIFS[0] = (UINT8)CcidDescriptor->MaxIFSD;

                DEBUG((DEBUG_INFO, "SetIFS[0] %x\n", SetIFS[0]));

                Status = TxRxT1TDPUChar (DevInfo, ICCDevice, sizeof (SetIFS), SetIFS, IFS_REQUEST, &ResponseLength, ResponseBuffer);
                // Update the received IFSD
                if (!EFI_ERROR(Status) && ResponseLength == 1){
                    ICCDevice->IFSD = ResponseBuffer[0];
                }
                break;
            default:
                break;
        }
    } 
    return Status;

}

/**
    This function powers up, sets the clock/rate etc 
    (configure CCID based on device capability)

    @param DevInfo      Pointer to the DevInfo structure
    @param ICCDevice    Pointer to the Icc device structure
    @param Data           Points to the buffer which is sent to CCID. 
    @param DataLength     Data length

    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
ConfigureCcid(
    DEV_INFO          *DevInfo,
    ICC_DEVICE        *ICCDevice
)
{
    EFI_STATUS  Status;
    UINT8       RetryCount = 3;

    //
    // Power up the device
    //
    do {
        Status = VoltageSelection(DevInfo, ICCDevice);
        RetryCount--;

        //    
        // check for errors and do try to recover
        //
        if(EFI_ERROR(Status) || ICCDevice->Status) {
            //
            // If card present but not powered up retry it. 
            // If card not present the exit immediatly
            //
            if (ICCDevice->Status ==  2) {
                break;
            }            
        } else {
            break;
        }

    }while (RetryCount);

    //    
    //Configure the data Rate and select the Protocol
    //
    if (!EFI_ERROR(Status)){
        Status = RateAndProtocolManagement (DevInfo, ICCDevice);
    }
    
    if (EFI_ERROR(Status)) {
        ICCDevice->ConfiguredStatus = CONFIGFAILED;
    }

    return Status;
}

/**
    This function executes a bulk transaction on the USB. The
    transfer may be either DATA_IN or DATA_OUT packets containing
    data sent from the host to the device or vice-versa. This
    function wil not return until the request either completes
    successfully or completes with error (due to time out, etc.)
    Size of data can be upto 64K

    @param DeviceInfo    Pointer to the DevInfo structure (if available else 0)
    @param XferDir       Transfer direction
                         Bit 7   : Data direction
                                    0 Host sending data to device
                                    1 Device sending data to host
                         Bit 6-0 : Reserved
    @param CmdBuffer     Buffer containing data to be sent to the device or
                         buffer to be used to receive data. Value in
    @param Size         Length request parameter, number of bytes of data
                         to be transferred in or out of the host controller

    @retval data         Amount of data transferred

**/

UINT32
UsbCcidIssueBulkTransfer (
    DEV_INFO*   DevInfo, 
    UINT8       XferDir,
    UINT8*      CmdBuffer, 
    UINT32      Size
)
{
    UINT32                          TransStatus;
    EFI_USB_IO_PROTOCOL             *UsbIo = DevInfo->UsbIo;
    EFI_STATUS                      Status;
    UINTN                           PacketLength = (UINTN)Size;

    if (XferDir == 0){
        Status = UsbIo->UsbBulkTransfer(
                          UsbIo,
                          DevInfo->BulkOutEndpoint,
                          CmdBuffer,
                          &PacketLength,
                          USB_CCID_BULK_TIMEOUT,
                          &TransStatus
                          );  
    
    } else {
        Status = UsbIo->UsbBulkTransfer(
                          UsbIo,
                          DevInfo->BulkInEndpoint + XferDir,
                          CmdBuffer,
                          &PacketLength,
                          USB_CCID_BULK_TIMEOUT,
                          &TransStatus
                          );
    }

    if (!EFI_ERROR(Status)) {
        return Size;
    } else{
        return 0;
    }

}

/**
    Issues Control Pipe request to default pipe

    @param DevInfo   DeviceInfo structure (if available else 0)
   @param  Request     Request type (low byte)
                       Bit 7   : Data direction
                                 0 = Host sending data to device
                                 1 = Device sending data to host
                       Bit 6-5 : Type
                                 00 = Standard USB request
                                 01 = Class specific
                                 10 = Vendor specific
                                 11 = Reserved
                       Bit 4-0 : Recipient
                                 00000 = Device
                                 00001 = Interface
                                 00010 = Endpoint
                                 00100 - 11111 = Reserved
                      Request code, a one byte code describing
                     the actual device request to be executed
                     (ex: 1 : ABORT, 2 : GET_CLOCK_FREQUENCIES, 3: GET_DATA_RATES)
   @param Index      wIndex request parameter (meaning varies)
   @param Value      wValue request parameter (meaning varies)
   @param Buffer    Buffer containing data to be sent to the
                      device or buffer to be used to receive data
   @param Length     wLength request parameter, number of bytes
                      of data to be transferred in or out
                      of the host controller

   @retval Data       Number of bytes actually transferred

**/

UINT32
UsbCcidIssueControlTransfer(
    DEV_INFO*   DevInfo,     
    UINT16      Request,
    UINT16      Index,
    UINT16      Value,
    UINT8       *Buffer,
    UINT16      Length
)
{

    EFI_STATUS                      Status;
    EFI_USB_DEVICE_REQUEST          UsbReq;
    UINT32                          TransStatus;
    EFI_USB_IO_PROTOCOL             *UsbIo = DevInfo->UsbIo;
    
    UsbReq.RequestType = (UINT8)Request;
    UsbReq.Request     = (UINT8)(Request>>8);
    UsbReq.Value       = Value;
    UsbReq.Index       = Index;
    UsbReq.Length      = Length;
    

    
    if (UsbReq.RequestType >= 0x80){
        Status = UsbIo->UsbControlTransfer(
                          UsbIo,
                          &UsbReq,
                          EfiUsbDataIn,
                          USB_CCID_TRANSFER_TIMEOUT,
                          Buffer,
                          UsbReq.Length,
                          &TransStatus
                          );
    } else {
        Status = UsbIo->UsbControlTransfer(
                          UsbIo,
                          &UsbReq,
                          EfiUsbDataOut,
                          USB_CCID_TRANSFER_TIMEOUT,
                          Buffer,
                          UsbReq.Length,
                          &TransStatus
                          );    	
    }

    if (!EFI_ERROR(Status)) {
        return UsbReq.Length;
    } else {
        return 0;
    }
}

/**
    Returns the # of Ts present in TDx

    @param Data      
    @retval Count  Returns number of TDx present in ATR data

**/
UINT8
FindNumberOfTs(
    UINT8    Data
)
{
    UINT8    Count = 0;
    UINT8    Mask = 0x10;

    for ( ;Mask; Mask = Mask << 1){
        if (Data & Mask) { 
            Count++;
        }
    }

    return Count;    
}

/**
    This function prints the information gathered from GetPCParameters

    @param Data       
    @retval VOID

**/
VOID 
PrintPCParameters(
    UINT8 * Data
)
{

    DEBUG((DEBUG_INFO, "ProtocolNum     : %02X\n", Data[0])); 
    DEBUG((DEBUG_INFO, "mFindexDIndex   : %02X\n", Data[1])); 
    DEBUG((DEBUG_INFO, "mTCCKST0        : %02X\n", Data[2])); 
    DEBUG((DEBUG_INFO, "GaurdTime       : %02X\n", Data[3])); 
    DEBUG((DEBUG_INFO, "WaitingInterger : %02X\n", Data[4])); 
    DEBUG((DEBUG_INFO, "ClockStop       : %02X\n", Data[5])); 
    DEBUG((DEBUG_INFO, "IFSC1           : %02X\n", Data[6])); // Valid only for T1    
    DEBUG((DEBUG_INFO, "NadValue        : %02X\n", Data[7])); // Valid only for T1

    return;
} 


/**
    This function prints the information gathered from ATR data

    @param DevInfo      Pointer to the DevInfo structure       
    @retval None

**/
VOID
PrintTimingInfo(
    ICC_DEVICE    *ICCDevice
)
{

    DEBUG((DEBUG_INFO, "ETU              : %02X  \n", ICCDevice->ETU)); 
    DEBUG((DEBUG_INFO, "GlobalFi         : %04x  \n", ICCDevice->GlobalFi)); 
    DEBUG((DEBUG_INFO, "GlobalFmax       : %02X  \n", ICCDevice->GlobalFmax)); 
    DEBUG((DEBUG_INFO, "GlobalDi         : %02X  \n", ICCDevice->GlobalDi)); 

    DEBUG((DEBUG_INFO, "SpecificMode     : %02X  \n", ICCDevice->SpecificMode)); 

    DEBUG((DEBUG_INFO, "ClassABC         : %02X  \n", ICCDevice->ClassABC)); 
    DEBUG((DEBUG_INFO, "StopClockSupport : %02X  \n", ICCDevice->StopClockSupport)); 

    DEBUG((DEBUG_INFO, "ExtraGuardTime   : %02X  \n", ICCDevice->ExtraGuardTime)); 
    DEBUG((DEBUG_INFO, "WTwaittime       : %08x  \n", ICCDevice->WTwaittime)); 

    DEBUG((DEBUG_INFO, "BWI              : %02X  \n", ICCDevice->BWI)); 
    DEBUG((DEBUG_INFO, "CWI              : %02X  \n", ICCDevice->CWI)); 
    DEBUG((DEBUG_INFO, "IFSC             : %02X  \n", ICCDevice->IFSC)); 
    DEBUG((DEBUG_INFO, "NAD              : %02X  \n", ICCDevice->NAD)); 
    DEBUG((DEBUG_INFO, "EpilogueFields   : %02X  \n", ICCDevice->EpilogueFields)); 
    DEBUG((DEBUG_INFO, "BWT              : %02X  \n", ICCDevice->BWT)); 

    return;
}

/**
    This function Prints the RAW ATR Data

    @param ATRData   the RAW ATR Data  
    @retval None

**/
VOID
PrintATRData(
    UINT8            *ATRData
)
{

    UINT8        TDx = 2;
    UINT8        Index;


    DEBUG((DEBUG_INFO, "    ATR Data \n"));

    for (Index=0; Index < 32; Index++) {
        DEBUG((DEBUG_INFO, "%02X ", ATRData[Index]));
    }

    Index = 0;

    DEBUG((DEBUG_INFO, "\nTS  : %02X  \n", ATRData[Index++])); 

    TDx = ATRData[Index];
    DEBUG((DEBUG_INFO, "T0  : %02X  \n", ATRData[Index++])); 
    DEBUG((DEBUG_INFO, "TA1 : %02X  \n", (TDx & 0x10) ? ATRData[Index++] : 0)); 
    DEBUG((DEBUG_INFO, "TB1 : %02X  \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC1 : %02X  \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD1 : %02X  \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    if (!(TDx & 0x80)) return;
    TDx = ATRData[Index-1];

 
    DEBUG((DEBUG_INFO, "TA2 : %02X \n", (TDx & 0x10) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TB2 : %02X \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC2 : %02X \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD2 : %02X \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    if (!(TDx & 0x80)) return;
    TDx = ATRData[Index-1];

    DEBUG((DEBUG_INFO, "TA3 : %02X \n", (TDx & 0x10) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TB3 : %02X \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC3 : %02X \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD3 : %02X \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    if (!(TDx & 0x80)) return;
    TDx = ATRData[Index-1];

    DEBUG((DEBUG_INFO, "TA4 : %02X \n", (TDx & 0x10) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TB4 : %02X \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC4 : %02X \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD4 : %02X \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    if (!(TDx & 0x80)) return;
    TDx = ATRData[Index-1];

    DEBUG((DEBUG_INFO, "TA5 : %02X \n", (TDx & 0x10) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TB5 : %02X \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC5 : %02X \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD5 : %02X \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    if (!(TDx & 0x80)) return;
    TDx = ATRData[Index-1];

    DEBUG((DEBUG_INFO, "TA6 : %02X \n", (TDx & 0x10) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TB6 : %02X \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC6 : %02X \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD6 : %02X \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    if (!(TDx & 0x80)) return;
    TDx = ATRData[Index-1];

    DEBUG((DEBUG_INFO, "TA7 : %02X \n", (TDx & 0x10) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TB7 : %02X \n", (TDx & 0x20) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TC7 : %02X \n", (TDx & 0x40) ? ATRData[Index++] : 0));
    DEBUG((DEBUG_INFO, "TD7 : %02X \n", (TDx & 0x80) ? ATRData[Index++] : 0));

    return;
}

/**
    Prints SMART class Descriptor data

    @param CCIDDesc  SMART class Descriptor data        
    @retval VOID

**/
VOID
PrintDescriptorInformation (
    SMARTCLASS_DESC *CcidDesc
)
{
#if DEBUG_MODE
    CHAR8    *Strings[] = {"CHARACTER", "TDPU", "Short ADPU", "Extended ADPU"};
    UINT8    Exchange;


    Exchange = (UINT8)((CcidDesc->Features & 0x70000) >> 16);

    DEBUG((DEBUG_INFO, "Sizeof SMART Class Descriptor :  %X\n", sizeof (SMARTCLASS_DESC)));
    DEBUG((DEBUG_INFO, "DescLength            :  %04X\n", CcidDesc->DescLength));
    DEBUG((DEBUG_INFO, "DescType              :  %04X\n", CcidDesc->DescType));
    DEBUG((DEBUG_INFO, "bcdCcid               :  %04X\n", CcidDesc->BcdCCID));
    DEBUG((DEBUG_INFO, "MaxSlotIndex          :  %04X\n", CcidDesc->MaxSlotIndex));
    DEBUG((DEBUG_INFO, "VoltageSupport        :  %04X\n", CcidDesc->VoltageSupport));
    DEBUG((DEBUG_INFO, "Protocols             :  %04X\n", CcidDesc->Protocols));
    DEBUG((DEBUG_INFO, "DefaultClock          :  %04X\n", CcidDesc->DefaultClock));
    DEBUG((DEBUG_INFO, "MaximumClock          :  %04X\n", CcidDesc->MaximumClock));
    DEBUG((DEBUG_INFO, "NumClockSupported     :  %04X\n", CcidDesc->NumClockSupported));
    DEBUG((DEBUG_INFO, "DataRate              :  %04X\n", CcidDesc->DataRate));
    DEBUG((DEBUG_INFO, "MaxDataRate           :  %04X\n", CcidDesc->MaxDataRate));
    DEBUG((DEBUG_INFO, "NumDataRatesSupported :  %04X\n", CcidDesc->NumDataRatesSupported));
    DEBUG((DEBUG_INFO, "MaxIFSD               :  %04X\n", CcidDesc->MaxIFSD));
    DEBUG((DEBUG_INFO, "SynchProtocols        :  %04X\n", CcidDesc->SynchProtocols));
    DEBUG((DEBUG_INFO, "Mechanical            :  %04X\n", CcidDesc->Mechanical));
    DEBUG((DEBUG_INFO, "Features              :  %04X\n", CcidDesc->Features));
    DEBUG((DEBUG_INFO, "ClassGetResponse      :  %04X\n", CcidDesc->MaxCCIDMessageLength));
    DEBUG((DEBUG_INFO, "ClassGetResponse      :  %04X\n", CcidDesc->ClassGetResponse));
    DEBUG((DEBUG_INFO, "ClassEnvelope         :  %04X\n", CcidDesc->ClassEnvelope));
    DEBUG((DEBUG_INFO, "LcdLayout             :  %04X\n", CcidDesc->LcdLayout));
    DEBUG((DEBUG_INFO, "PINSupport            :  %04X\n", CcidDesc->PINSupport));
    DEBUG((DEBUG_INFO, "MaxCcidBusySlots      :  %04X\n", CcidDesc->MaxCCIDBusySlots));

    DEBUG((DEBUG_INFO, "*************************************\n")); 
    DEBUG((DEBUG_INFO, " Device is in:")); 
    DEBUG((DEBUG_INFO, "%a Exchange mode\n", Strings[Exchange])); 
    DEBUG((DEBUG_INFO, "*************************************\n")); 
#endif
}

/**
    This routine is called when InterruptIN messages is generated
      
    @param pHCStruc      Pointer to HCStruc
    @param DevInfo       Pointer to device information structure
    @param Td            Pointer to the polling TD
    @param Buffer        Pointer to the data buffer
    @param DataLength    Data length
    
    @retval USB_SUCCESS       Success
    @retval UEB_ERROR         Error

    @note  When an ICC card is inserted or removed Interrupt message is generated.   

**/

UINT8
EFIAPI
UsbCcidProcessInterruptData (
    DEV_INFO    *DevInfo,
    UINT8       *Buffer,
    UINT16      DataLength
)
{

    EFI_STATUS      Status;
    
    UINT8           Slot;
    UINT32          SlotICCStatus = *(UINT32 *)(Buffer + 1);
    SMARTCLASS_DESC *CcidDescriptor;
    CCID_DEV_INFO   *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return USB_ERROR;


    DEBUG((DEBUG_INFO, "UsbCcidProcessInterruptData.... %X %X %X %X\n", 
                *Buffer, *(Buffer +1), *(Buffer + 2), *(Buffer + 3)));
    
    CcidDescriptor = (SMARTCLASS_DESC*)(UINTN*)CcidDevData->CcidDescriptor;
    if(CcidDescriptor->DescType  != DESC_TYPE_SMART_CARD){   //CCID Smart Card Class DescriptorType
        return USB_ERROR;
    }
    switch (*Buffer) {
        
        //
        // ICC Card either inserted or Removed
        //
        case RDR_TO_PC_NOTIFYSLOTCHANGE:        

            //
            // Find the # of bytes in this notification
            //
            /*
            Slot = CCIDDescriptor->bMaxSlotIndex + 1; // Make it 1 based
            
            bmSlotICCByte = (CCIDDescriptor->bMaxSlotIndex + 1) >> 2;

            if (Slot & 0x3) { 
                bmSlotICCByte++;
            }
            */

            Slot = 0;
            do {
            	UINT8           Data;
                Data = (SlotICCStatus >> Slot) & 0x3;
                //
                // Is there a change in status
                //
                if ((Data & 0x3) == 3) {                
                    Status = ICCInsertEvent (DevInfo, Slot);
                    if (EFI_ERROR(Status)){
                        DEBUG((DEBUG_INFO, "ICCInsertEvent %r \n",Status ));
                    }
                }
                if ((Data & 0x3) == 2) {                
                    Status = ICCRemovalEvent (DevInfo, Slot);
                    if (EFI_ERROR(Status)){
                        DEBUG((DEBUG_INFO, "ICCRemovalEvent %r \n",Status ));
                    }
                }
                  Slot++;
            } while (Slot < (CcidDescriptor->MaxSlotIndex + 1));                        

            break;

        case RDR_TO_PC_HARDWAREERROR:        

            DEBUG((DEBUG_INFO, "RDR To PC Hardware Error Slot %X Sequence %X Error Code %X \n", 
                            *Buffer, *(Buffer +1), *(Buffer + 2)));
            break;

        default:
            break;
    }

    return USB_SUCCESS;
}

/**
    In response to Device removal, Interrupt-in message is received. 
    Icc Device is removed from the linked list.

    @param DevInfo      Pointer to the DevInfo structure
    @param Slot           Slot number
    
    @retval EFI_SUCCESS       Success
    @retval Others            Error    

**/
EFI_STATUS
ICCRemovalEvent(
        DEV_INFO    *DevInfo,
        UINT8        Slot
)
{

    ICC_DEVICE        *ICCDevice;
    
    ICCDevice = GetIccDevice(DevInfo, Slot);
   
    if (ICCDevice) {

        // Don't free up the memory. EFI driver (EfiUsbCCID) makes use of this data area to 
        // find whether ICC has been removed or added.
        // Before freeing up, clear the bytes
        ZeroMem((UINT8 *)(ICCDevice->RawATRData), sizeof(ICCDevice->RawATRData));
        ZeroMem((UINT8 *)&(ICCDevice->AtrData), sizeof(ATR_DATA));

        //
        //Free up the memory and remove it from linked list
        //

        if (ICCDevice->ConfiguredStatus & ICCPRESENT) {
            ICCDevice->ConfiguredStatus = CARDREMOVED;
        } else {
            //
            // Handle if IccRemovalEven is called multiple times
            //
            return EFI_SUCCESS;
        }

        DEBUG((DEBUG_INFO, "ICC device removed - Slot : %X\n", Slot));

        IccQueuePut((void *)ICCDevice);

    }

    DEBUG((DEBUG_INFO, "Removal: DevInfo %X ICCDevice %X\n", DevInfo, ICCDevice));

    return EFI_SUCCESS;
}


/**
    In response to Device Insertion, Interrupt-in message is received. 
    Icc Device is added to the linked list and configured.

    @param DevInfo      Pointer to the DevInfo structure
    @param Slot           Slot number
    
    @retval EFI_SUCCESS       Success
    @retval Others            Error   

**/
EFI_STATUS
ICCInsertEvent(
    DEV_INFO    *DevInfo,
    UINT8       Slot
)
{

    EFI_STATUS        Status;
    ICC_DEVICE        *ICCDevice;
    BOOLEAN         NewDeviceAdded = FALSE;
    CCID_DEV_INFO   *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;
    if (!CcidDevData) return EFI_DEVICE_ERROR;

    DEBUG((DEBUG_INFO, "ICCInsertEvent Slot %X \n", Slot));
    //
    // Check if the device already exist. if so use it.
    //
    ICCDevice = GetIccDevice(DevInfo, Slot);

    if (!ICCDevice) {
        //
        // Alocate memory for ICC_DEVICE and attach it to the linked list
        //

        ICCDevice = &DevInfo->IccDevice[Slot];
   
        ZeroMem((UINT8 *)ICCDevice, sizeof(ICC_DEVICE));
        ICCDevice->DevInfo = DevInfo;

        //
        // Add to the slot list
        //

        if (&(CcidDevData->IccDeviceList) != NULL) {
            InsertTailList(&(CcidDevData->IccDeviceList), &(ICCDevice->Link));
            NewDeviceAdded = TRUE;
        }
    }


    if ((gUsbData->UsbFeature & USB_CCID_USE_INT_INS_REMOVAL) == USB_CCID_USE_INT_INS_REMOVAL){
    // Handle Multiple ICCInsertEvent calls. Some cards generate 
    // Interrupt in Interrupt-IN endpoint and some don't.
    // For card which don't generate the intterupt, CCID API should be used to power up the device.
    DEBUG((DEBUG_INFO, "ICCDevice->ConfiguredStatus %X \n", ICCDevice->ConfiguredStatus));
    if ((ICCDevice->ConfiguredStatus != CARDREMOVED) && (ICCDevice->ConfiguredStatus)) {

        if (ICCDevice->ConfiguredStatus == CONFIGFAILED) {
            return EFI_DEVICE_ERROR;
        }
        return EFI_SUCCESS;

    }
    }

    
    ICCDevice->Signature = ICC_DEVICE_SIG;
    ICCDevice->Slot = Slot;
    ICCDevice->WaitTime = INITWAITTIME;
    ICCDevice->ConfiguredStatus = 0;

    Status = ConfigureCcid(DevInfo, ICCDevice);


    if ((gUsbData->UsbFeature & USB_CCID_USE_INT_INS_REMOVAL) == USB_CCID_USE_INT_INS_REMOVAL){
    if(EFI_ERROR(Status)){

        //
        //Free up the memory and remove it from linked list
        //

        RemoveEntryList(&ICCDevice->Link);

    } else {
        DEBUG((DEBUG_INFO, "ICC device added - Slot : %X\n", Slot));
    
        if (ICCDevice->ChildHandle == NULL) {
            IccQueuePut((void *)ICCDevice);
        }
    }

    } else {
    //
    // Even if configuration failed install the protocol in polling mode.         
    //
    DEBUG((DEBUG_INFO, "ICC device added - Slot : %X\n", Slot));
    
    if (NewDeviceAdded && (ICCDevice->ChildHandle == NULL)) {
        IccQueuePut((void *)ICCDevice);
    }
    }

    DEBUG((DEBUG_INFO, "Insert : DevInfo %X ICCDevice %X\n", DevInfo, ICCDevice));

    return Status;
}

/**
    Puts the pointer  into the queue for processing.
    updates queue head and tail. This data is read from EfiUSBCCID.C 
    which installs AMI_CCID_IO_PROTOCOL

    @param  d         (void *)ICCDevice        
    @retval None

**/

VOID
IccQueuePut(
    VOID * IccDev
)
{
    QUEUE_T* Queue = &gUsbDataList->ICCQueueCnnctDisc;

    while (Queue->Head >= Queue->Maxsize) {
        Queue->Head -= Queue->Maxsize;
    }

    Queue->Data[Queue->Head++] = IccDev;
    if (Queue->Head == Queue->Maxsize) {
        Queue->Head -= Queue->Maxsize;
    }
    if (Queue->Head == Queue->Tail) {
        //Drop data from queue
        Queue->Tail++;
        while (Queue->Tail >= Queue->Maxsize) {
            Queue->Tail -= Queue->Maxsize;
        }
    }
    return;
}

/**
    Do some USB device info data initialization 

    @param DevInfo          Pointer to devInfo structure
    @param Desc             Pointer to the descriptor structure
    @param StartOffset        Start offset of the device descriptor
    @param  EndOffset         End offset of the device descriptor

    @retval EFI_SUCCESS       Success
    @retval Others            Error

**/
EFI_STATUS
DoDevInfoInitialization (
    DEV_INFO    *DevInfo,
    UINT8       *Desc,
    UINT16      StartOffset,
    UINT16      EndOffset
)
{

    UINT8           Temp;
    USB_ENDPOINT_DESCRIPTOR       *EndpDesc;
    USB_INTERFACE_DESCRIPTOR      *IntrfDesc;
    SMARTCLASS_DESC *CcidDesc = NULL;
    CCID_DEV_INFO   *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;

    //
    // Initialize the Initlist to hold data for each Slot 
    //

    InitializeListHead(&CcidDevData->IccDeviceList); 
    IntrfDesc = (USB_INTERFACE_DESCRIPTOR*)(Desc + StartOffset);

    //
    // Calculate the end of descriptor block
    //
    Desc+=((USB_CONFIG_DESCRIPTOR*)Desc)->TotalLength; 
    EndpDesc = (USB_ENDPOINT_DESCRIPTOR*)((char*)IntrfDesc + IntrfDesc->Length);

    do {
        if (IntrfDesc->DescriptorType == DESC_TYPE_SMART_CARD) {
            CcidDesc = (SMARTCLASS_DESC *)IntrfDesc;
            break;
        }
        IntrfDesc = (USB_INTERFACE_DESCRIPTOR*) ((UINT8 *)IntrfDesc + IntrfDesc->Length);
    } while ((UINT8 *)IntrfDesc < Desc);

    if (!CcidDesc) { 
        return EFI_DEVICE_ERROR;
    }
 
    CopyMem((UINT8 *)(CcidDevData->CcidDescriptor), (UINT8 *)CcidDesc, sizeof(SMARTCLASS_DESC));
    CcidDesc = (SMARTCLASS_DESC*)CcidDevData->CcidDescriptor;

    if (CcidDesc->NumDataRatesSupported) {    
        //
        // Issue GET_DATA_RATES cmd. Should interface number be zero?
        //
        UsbCcidIssueControlTransfer(DevInfo, 
                                    CCID_CLASS_SPECIFIC_GET_DATA_RATES, 
                                    0x0, 0, (UINT8 *)CcidDevData->DataRates, 
                                    CcidDesc->NumDataRatesSupported * sizeof(UINT32)
                                    );
        
    } else {
        CcidDevData->DataRates = 0;
    }

    if (CcidDesc->NumClockSupported) {
        //            
        // Issue GET_CLOCK_FREQUENCIES. Should interface number be zero?
        //
        UsbCcidIssueControlTransfer(DevInfo,  
                                    CCID_CLASS_SPECIFIC_GET_CLOCK_FREQUENCIES, 
                                    0x0, 0, (UINT8 *)CcidDevData->ClockFrequencies,
                                    CcidDesc->NumClockSupported * sizeof(UINT32));
    } else {
        CcidDevData->ClockFrequencies = 0;
    }

    PrintDescriptorInformation(CcidDevData->CcidDescriptor);

    Temp = 0x03;       // bit 1 = Bulk In, bit 0 = Bulk Out

    for( ;(EndpDesc->DescriptorType != DESC_TYPE_INTERFACE) && ((UINT8*)EndpDesc < Desc);
        EndpDesc = (USB_ENDPOINT_DESCRIPTOR*)((UINT8 *)EndpDesc + EndpDesc->Length)){

    if(!(EndpDesc->Length)) {  
        // Br if 0 length desc (should never happen, but...)
        break;  
    }

        if( EndpDesc->DescriptorType != DESC_TYPE_ENDPOINT ) {
            continue;
        }

        if ((EndpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) ==
                EP_DESC_FLAG_TYPE_BULK) {   // Bit 1-0: 10 = Endpoint does bulk transfers
            if(!(EndpDesc->EndpointAddress & EP_DESC_ADDR_DIR_BIT)) {
                //
                // Bit 7: Dir. of the endpoint: 1/0 = In/Out
                // If Bulk-Out endpoint already found then skip subsequent ones
                // on the interface.
                //
                if (Temp & 1) {
                    DevInfo->BulkOutEndpoint = (UINT8)(EndpDesc->EndpointAddress
                                                        & EP_DESC_ADDR_EP_NUM);
                    DevInfo->BulkOutMaxPkt = EndpDesc->MaxPacketSize;
                    Temp &= 0xFE;
                }
            } else {
                //
                // If Bulk-In endpoint already found then skip subsequent ones
                // on the interface
                //
                if (Temp & 2) {
                    DevInfo->BulkInEndpoint  = (UINT8)(EndpDesc->EndpointAddress
                                                        & EP_DESC_ADDR_EP_NUM);
                    DevInfo->BulkInMaxPkt    = EndpDesc->MaxPacketSize;
                    Temp   &= 0xFD;
                }
            }
        }

        //
        // Check for and configure Interrupt endpoint if present
        //
        if ((EndpDesc->Attributes & EP_DESC_FLAG_TYPE_BITS) !=
                EP_DESC_FLAG_TYPE_INT) {    // Bit 1-0: 10 = Endpoint does interrupt transfers
          continue;
        }

    if (EndpDesc->EndpointAddress & EP_DESC_ADDR_DIR_BIT) {
      DevInfo->IntInEndpoint = EndpDesc->EndpointAddress;
      DevInfo->IntInMaxPkt = EndpDesc->MaxPacketSize;
      DevInfo->PollInterval = EndpDesc->Interval;  
    }
    }

    return EFI_SUCCESS;
}


/**
    This routine initializes each slot of Smartcard reader

    @param DevInfo    Pointer to device information structure

    @retval EFI_SUCCESS       Success
    @retval Others            Error
**/
EFI_STATUS
UpdateSCardSlotInfo (
    DEV_INFO    *DevInfo
)
{
    UINT8          Index = 0;
    ICC_DEVICE     *ICCDevice = NULL; 
    CCID_DEV_INFO   *CcidDevData = NULL;
    SMARTCLASS_DESC *SmartClassDescriptor = NULL;
    
    
    if(DevInfo == NULL) return EFI_INVALID_PARAMETER;
    
    CcidDevData = &DevInfo->CcidDevData;
    if(CcidDevData == NULL) return EFI_INVALID_PARAMETER;
      
    SmartClassDescriptor = (SMARTCLASS_DESC*)(UINTN)(CcidDevData->CcidDescriptor);
    if(SmartClassDescriptor == NULL) return EFI_INVALID_PARAMETER;

    if(SmartClassDescriptor->DescType  != DESC_TYPE_SMART_CARD){   //CCID Smart Card Class DescriptorType
        return EFI_INVALID_PARAMETER;
    }
    DEBUG((DEBUG_INFO, "SmartClassDescriptor DescType %x MaxSlotIndex%X \n", SmartClassDescriptor->DescType, SmartClassDescriptor->MaxSlotIndex ));
    for( Index=0; Index <= SmartClassDescriptor->MaxSlotIndex ; Index++ ) {

        // Code to initialize Each slot of the CCID irrespective of ICC card 
        // is present in the Slot or not
        ICCDevice = GetIccDevice(DevInfo, Index);

        if (ICCDevice) {
            ICCDevice->ChildHandle = 0;
            ICCDevice->SCardChildHandle = 0;
            ICCDevice->WaitTime = INITWAITTIME;
            ICCDevice->SlotConnectStatus = 0;
            ICCDevice->ConfiguredStatus = 0;
            continue;
        }

        ICCDevice = &DevInfo->IccDevice[Index];

        ZeroMem((UINT8 *)ICCDevice, sizeof(ICC_DEVICE));

        ICCDevice->Signature = ICC_DEVICE_SIG;
        ICCDevice->ChildHandle = 0;
        ICCDevice->SCardChildHandle = 0;

        // Slot Number
        ICCDevice->Slot = Index;
        ICCDevice->WaitTime = INITWAITTIME;
        ICCDevice->SlotConnectStatus = 0;
        ICCDevice->ConfiguredStatus = 0;
        ICCDevice->DevInfo = DevInfo;

        // Add to the slot list
        if(&(CcidDevData->IccDeviceList) != NULL){
            InsertTailList(&(CcidDevData->IccDeviceList), &(ICCDevice->Link));
        }

        IccQueuePut((void *)ICCDevice);
    }

    return EFI_SUCCESS;
}

/**
  Handler function for USB CCID Device asynchronous interrupt transfer.

  @param  Data             A pointer to a buffer that is filled with Hid data which is
                           retrieved via asynchronous interrupt transfer.
  @param  DataLength       Indicates the size of the data buffer.
  @param  Context          Pointing to AMI_USB_HID_IO instance.
  @param  TransferResult   Indicates the result of the asynchronous interrupt transfer.

  @retval EFI_SUCCESS      Asynchronous interrupt transfer is handled successfully.
  @retval EFI_DEVICE_ERROR Hardware error occurs.

**/
EFI_STATUS
EFIAPI
CcidInterruptComplete (
  IN    VOID        *Data,
  IN    UINTN       DataLength,
  IN    VOID        *Context,
  IN    UINT32      TransferResult
  )
{
    DEV_INFO            *DevInfo = (DEV_INFO*)Context;
    EFI_USB_IO_PROTOCOL *UsbIo = DevInfo->UsbIo;
    UINT32              UsbResult;
    
    if (TransferResult != EFI_USB_NOERROR) {
        if ((TransferResult & EFI_USB_ERR_STALL) == EFI_USB_ERR_STALL) {
            UsbClearEndpointHalt (
              UsbIo,
              DevInfo->IntInEndpoint,
              &UsbResult
              );
        }
        UsbIo->UsbAsyncInterruptTransfer (
                 UsbIo,
                 DevInfo->IntInEndpoint,
                 FALSE,
                 0,
                 0,
                 NULL,
                 NULL
                 );
        return EFI_DEVICE_ERROR;
    }
    
    UsbCcidProcessInterruptData(
      DevInfo,
      (UINT8*)Data,
      (UINT16)DataLength
      );
 
    return EFI_SUCCESS;
}

/**
    This function checks an interface descriptor of a device
    to see if it describes a USB CCID device.  If the device
    is a CCID device,  then it is configured
    and initialized.

    @param  HCStruc          Pointer to Host controller structure
    @param  DevInfo          Pointer to devInfo structure
    @param  Desc             Pointer to the descriptor structure
    @param  StartOffset      Start offset of the device descriptor
    @param  EndOffset        End offset of the device descriptor

    @retval EFI_SUCCESS       Success
    @retval Others            Error

    @retval  DevInfo         New device info structure
    @retval  NULL              On error

**/
DEV_INFO*
EFIAPI
UsbCcidConfigureDevice (
    DEV_INFO        *DevInfo,
    UINT8           *Desc,
    UINT16          StartOffset,
    UINT16          EndOffset
)
{

    EFI_STATUS        Status;
    USB_INTERFACE_DESCRIPTOR      *IntrfDesc = (USB_INTERFACE_DESCRIPTOR*)(Desc + StartOffset);

    DEBUG((DEBUG_INFO, "UsbCcidConfigureDevice ....\n"));

    //
    // Do some house keeping related DEV_INFO structure. No H/W access
    //
    Status = DoDevInfoInitialization(DevInfo, Desc, StartOffset, EndOffset);

    if (EFI_ERROR(Status)) {
        return NULL;
    }

    // Add number if ICC_DEVICE structure(based in the Slot present in the Descriptor) in DEV_INFO structure
    UpdateSCardSlotInfo(DevInfo);


    if ((gUsbData->UsbFeature & USB_CCID_USE_INT_INS_REMOVAL) == USB_CCID_USE_INT_INS_REMOVAL){
        //
        // if Interrupt EndPoint is supported
        //
        if (IntrfDesc->NumEndpoints == 3) {
            DevInfo->PollingLength = DevInfo->IntInMaxPkt;
            DevInfo->UsbIo->UsbAsyncInterruptTransfer (
                       DevInfo->UsbIo,
                       DevInfo->IntInEndpoint,
                       TRUE,
                       DevInfo->PollInterval,
                       DevInfo->IntInMaxPkt,
                       CcidInterruptComplete,
                       DevInfo
                       );
        }

    }else{
        Status = ICCInsertEvent(DevInfo, 0);
        if (EFI_ERROR(Status)) {
            DEBUG((DEBUG_INFO,"ICCInsertEvent Status = %r\n", Status));
        }
    }

    //
    // Should we support CCID which doesn't support interrupt-IN Message.
    // Maybe not for now.
    //
    return  DevInfo;

}


/**
    This function disconnects the CCID device.

    @param  DevInfo          Pointer to devInfo structure   
         
    @retval USB_SUCCESS        Success
    @retval Others             Error

    @note  Free up all memory allocated to the device. 
              Remove ICC device from the device list.

**/

UINT8
EFIAPI
UsbCcidDisconnectDevice (
    DEV_INFO    *DevInfo
)
{

    ICC_DEVICE *ICCDevice;
    LIST_ENTRY *Link;
    CCID_DEV_INFO   *CcidDevData;

    CcidDevData = &DevInfo->CcidDevData;
    if(!CcidDevData) return USB_ERROR;


    if ((gUsbData->UsbFeature & USB_CCID_USE_INT_INS_REMOVAL) == USB_CCID_USE_INT_INS_REMOVAL){
        // Stop polling the endpoint 
        DevInfo->UsbIo->UsbAsyncInterruptTransfer (
                   DevInfo->UsbIo,
                   DevInfo->IntInEndpoint,
                   FALSE,
                   0,
                   0,
                   NULL,
                   NULL
                   );
 
 
        DevInfo->IntInEndpoint = 0;
    }
    //
    // Free up all the memory allocated for each ICC device
    //
    for (Link = CcidDevData->IccDeviceList.ForwardLink;
        Link != &CcidDevData->IccDeviceList; 
        Link = Link->ForwardLink ) {
        ICCDevice = BASE_CR(Link, ICC_DEVICE, Link);

        RemoveEntryList(&ICCDevice->Link);
   
    }

    return USB_SUCCESS;
}



/**
    This routine services the USB API function number 30h.  It
    handles all the CCID related calls from the higher
    layer. Different sub-functions are invoked depending on
    the sub-function number

    @param UsbUrp     Pointer to the URP structure
                      URP structure is updated with the relevant information

    @retval None
**/

VOID
EFIAPI
UsbApiCcidRequest(
    URP_STRUC *UsbUrp
)
{

    
    UINT8 CcidFuncIndex = UsbUrp->SubFunc;
    UINT8 NumberOfCcidFunctions = sizeof(gUsbCcidApiTable) / sizeof(API_FUNC *);

    if ((gUsbData->UsbDevSupport & USB_CCID_DEV_SUPPORT) == USB_CCID_DEV_SUPPORT){
    //
    // Make sure function number is valid
    //
    if (CcidFuncIndex >= NumberOfCcidFunctions) {
        DEBUG((DEBUG_INFO, "UsbApi CcidRequest Invalid function#%x\n", CcidFuncIndex));
        return;
    }
    //
    // Function number is valid - call it
    //
    gUsbCcidApiTable[CcidFuncIndex](UsbUrp);
    }


}
//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
