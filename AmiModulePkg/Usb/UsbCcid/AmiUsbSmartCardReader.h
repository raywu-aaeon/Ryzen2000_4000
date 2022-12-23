//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiUsbSmartCardReader.h
    Header file contains Smart Card reader Protocol API function declaration

**/

#ifndef _AMI_USB_SMART_CARD_READER_H_
#define _AMI_USB_SMART_CARD_READER_H_

#include <Protocol/SmartCardReader.h>

typedef struct {
    EFI_SMART_CARD_READER_PROTOCOL   EfiSmartCardReaderProtocol;
    VOID                             *DevInfo;
    UINT8                            Slot;
    UINT8                            AccessMode;
    EFI_HANDLE                       ControllerHandle;
    EFI_HANDLE                       ChildHandle;
} USB_SCARD_DEV;

EFI_STATUS
EFIAPI
UsbSCardReaderApiConnect(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT32                         AccessMode,
    IN UINT32                         CardAction,
    IN UINT32                         PreferredProtocol,
    OUT UINT32                        *ActiveProtocol
);

EFI_STATUS
EFIAPI
UsbSCardReaderApiDisconnect(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT32                         CardAction
);

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
);

EFI_STATUS
EFIAPI
UsbSCardReaderApiTransmit(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT8                          *CAPDU,
    IN UINTN                          CAPDULength,
    OUT UINT8                         *RAPDU,
    IN OUT UINTN                      *RAPDULength
);

EFI_STATUS
EFIAPI
UsbSCardReaderApiControl(
  IN     EFI_SMART_CARD_READER_PROTOCOL    *This,
  IN     UINT32                            ControlCode,
  IN     UINT8                             *InBuffer OPTIONAL,
  IN     UINTN                             InBufferLength OPTIONAL,
     OUT UINT8                             *OutBuffer OPTIONAL,
  IN OUT UINTN                             *OutBufferLength OPTIONAL
);

EFI_STATUS
EFIAPI
UsbSCardReaderApiGetAttrib(
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    IN UINT32                         Attrib,
    OUT UINT8                         *OutBuffer,
    IN OUT UINTN                      *OutBufferLength
);

EFI_STATUS
GetSmartCardReaderName (
    IN EFI_SMART_CARD_READER_PROTOCOL *This,
    CHAR16        *ReaderName,
    UINTN         *ReaderNameLength
);

#endif // _AMI_USB_SMART_CARD_READER_H_

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
