//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiUsbCcid.h
    AMI USB CCID Protocol definition

**/

#ifndef _AMI_USB_CCID_H
#define _AMI_USB_CCID_H


#ifndef GUID_VARIABLE_DEFINITION

// CCID definitions/Structures
typedef struct _AMI_CCID_IO_PROTOCOL AMI_CCID_IO_PROTOCOL;

#define AMI_CCID_IO_PROTOCOL_GUID \
  { 0xB167C2F5, 0xE26A, 0x4DFF, {0x8E, 0x1C, 0x08, 0x07, 0xC7, 0xF0, 0x2A, 0x88}}

#define AMI_CCID_PRESENCE_GUID \
  { 0x5FDEE00D, 0xDA40, 0x405A, {0xB9, 0x2E, 0xCF, 0x4A, 0x80, 0xEA, 0x8F, 0x76}}

typedef enum {
  I_BLOCK,
  S_IFS_REQUEST = 0xC1,
  S_ABORT_REQUEST,
  S_WTX_REQUEST    
} ISBlock;

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_SMARTCLASSDESCRIPTOR) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *ResponseBuffer
);

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_GET_ATR) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINT8                            Slot,
    OUT UINT8                           *ATRData
);

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_POWERUP_SLOT) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error,
    OUT UINT8                           *ATRData
);

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_POWERDOWN_SLOT) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error
);

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_GET_SLOT_STATUS) (
    IN AMI_CCID_IO_PROTOCOL              *This,
    OUT UINT8                            *Status,
    OUT UINT8                            *Error,
    OUT UINT8                            *ClockStatus
);

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_XFR_BLOCK) (
    IN AMI_CCID_IO_PROTOCOL             *This,
    IN UINTN                            CmdLength,
    IN UINT8                            *CmdBuffer,
    IN UINT8                            ISBlock,
    OUT UINT8                           *Status,
    OUT UINT8                           *Error,
    IN OUT UINTN                        *ResponseLength,
    OUT UINT8                           *ResponseBuffer
);

typedef
EFI_STATUS
(EFIAPI *AMI_CCID_GET_PARAMETERS) (
    IN AMI_CCID_IO_PROTOCOL              *This,
    OUT UINT8                            *Status,
    OUT UINT8                            *Error,
    OUT UINTN                            *ResponseLength,
    OUT UINT8                            *ResponseBuffer
);

struct _AMI_CCID_IO_PROTOCOL {
    AMI_CCID_SMARTCLASSDESCRIPTOR       UsbCcidApiSmartClassDescriptor;
    AMI_CCID_GET_ATR                    UsbCcidApiGetAtr;
    AMI_CCID_POWERUP_SLOT               UsbCcidApiPowerupSlot;    
    AMI_CCID_POWERDOWN_SLOT             UsbCcidApiPowerDownSlot;    
    AMI_CCID_GET_SLOT_STATUS            UsbCcidApiGetSlotStatus;
    AMI_CCID_XFR_BLOCK                  UsbCcidApiXfrBlock;
    AMI_CCID_GET_PARAMETERS             UsbCcidApiGetParameters;    
        
};

typedef struct {
    AMI_CCID_IO_PROTOCOL        CcidIoProtocol;
    VOID                        *DevInfo;
    UINT8                       Slot;
    EFI_HANDLE                  ControllerHandle;
    EFI_HANDLE                  ChildHandle;

} USB_ICC_DEV;

#endif
#endif // _AMI_USB_CCID_H

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
