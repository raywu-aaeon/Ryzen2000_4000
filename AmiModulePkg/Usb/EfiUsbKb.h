//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file EfiUsbKb.h
    AMI USB keyboard driver header file

**/

#ifndef _EFI_USB_KB_H
#define _EFI_USB_KB_H

#include "Uhcd.h"
#include <Protocol/AmiKeycode.h>
#include <UsbKbd.h>

#define USBKB_DRIVER_VERSION 2

EFI_STATUS
InstallUsbKeyboard (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    DEV_INFO                    *DevInfo,            
    EFI_USB_IO_PROTOCOL         *UsbIo 
);

EFI_STATUS
UninstallUsbKeyboard (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
);

                                                                                //(EIP38434+)>
EFI_STATUS      InstallUSBAbsMouse(EFI_HANDLE Controller,DEV_INFO   *pDevInfo); 
EFI_STATUS UninstallUSBAbsMouse(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, UINTN NumberOfChildren, EFI_HANDLE *Children);
 
EFI_STATUS InstallUSBMouse(EFI_HANDLE Controller,EFI_USB_IO_PROTOCOL *UsbIo,DEV_INFO *DevInfo);
EFI_STATUS UninstallUSBMouse(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, UINTN numberOfChildren, EFI_HANDLE *children  );
      
EFI_STATUS  EFIAPI SupportedUSBHid(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, EFI_DEVICE_PATH_PROTOCOL *dp);
EFI_STATUS  EFIAPI InstallUSBHid(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, EFI_DEVICE_PATH_PROTOCOL *dp);
EFI_STATUS  EFIAPI UninstallUSBHid(EFI_DRIVER_BINDING_PROTOCOL  *This,
    EFI_HANDLE, UINTN numberOfChildren, EFI_HANDLE *children  );
EFI_STATUS CreateKeyBuffer(KEY_BUFFER *KeyBuffer, UINT8 MaxKey, UINT32 KeySize);
EFI_STATUS DestroyKeyBuffer(KEY_BUFFER *KeyBuffer);
                                                                                //<(EIP38434+)

#define USB_KB_DEV_SIGNATURE  EFI_SIGNATURE_32('u','k','b','d')

typedef struct {
    UINTN                               Signature;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL      SimpleInput;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   SimpleInputEx;
    AMI_EFIKEYCODE_PROTOCOL             KeycodeInput;
    LIST_ENTRY                          KeyNotifyList;
 
    EFI_USB_IO_PROTOCOL                 *UsbIo;
    DEV_INFO                            *DevInfo;
    EFI_EVENT                           TimerEvent;
    EFI_EVENT                           KeyRepeatEvent;
    EFI_EVENT                           ReadyToBootEvent;

    KEY_BUFFER                          EfiKeyBuffer;

    UINT32                              ShiftState;
    EFI_KEY_TOGGLE_STATE                ToggleState;
    EFI_KEY_TOGGLE_STATE                LastToggleState;

    UINT8                               LastUsbKeyCode;
} USB_KB_DEV;

typedef struct {
    UINT8                               UsbKeyCode;
    UINT16                              ScanCode;
    CHAR16                              Unicode;
    CHAR16                              ShiftedUnicode;
    EFI_KEY                             EfiKey;
    UINT8                               PS2ScanCode;
    UINT32                              ShiftState;
    EFI_KEY_TOGGLE_STATE                ToggleState;
} EFI_KEY_MAP;

typedef struct {
    LIST_ENTRY                          Link;   //MUST BE THE FIRST FIELD
    EFI_KEY_DATA                        KeyData;
    EFI_KEY_NOTIFY_FUNCTION             NotifyFunction;
    EFI_HANDLE                          NotifyEvent;
    EFI_KEY_DATA                        KeyPressed;
} KEY_NOTIFY_LINK;

#define TIMER_MSEC              10000
#define USB_KBD_TIMER_INTERVAL  10 * TIMER_MSEC
#define USB_KBD_REPEAT_DELAY    500 * TIMER_MSEC
#define USB_KBD_REPEAT_RATE     33 * TIMER_MSEC

//
// Global Variables
//

#define USB_KB_DEV_FROM_THIS(a,b) \
    CR(a, USB_KB_DEV, b, USB_KB_DEV_SIGNATURE)


EFI_STATUS InitUSBMouse();

EFI_STATUS
EFIAPI
UsbKbdSimpleInReset (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  IN  BOOLEAN                 ExtendedVerification
  );

EFI_STATUS
EFIAPI
UsbKbdSimpleInReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  OUT EFI_INPUT_KEY           *Key
  );

EFI_STATUS
EFIAPI
UsbKbdSimpleInExReset (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  BOOLEAN                 ExtendedVerification
  );

EFI_STATUS
EFIAPI
UsbKbdSimpleInExReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  OUT EFI_KEY_DATA *KeyData
  );

EFI_STATUS
EFIAPI
UsbKbdSimpleInExSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
);

EFI_STATUS
EFIAPI
UsbKbdSimpleInExRegisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
);

EFI_STATUS
EFIAPI
UsbKbdSimpleInExUnregisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
  );

EFI_STATUS
EFIAPI
UsbKbdKeycodeInReset(
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  BOOLEAN     			ExtendedVerification
);

EFI_STATUS
EFIAPI
UsbKbdKeycodeInReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
);

EFI_STATUS
EFIAPI
UsbKbdKeycodeInSetState(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE 	*KeyToggleState
);

EFI_STATUS
EFIAPI
UsbKbdKeycodeInRegisterKeyNotify(
    IN    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN    EFI_KEY_DATA                      *KeyData,
    IN    EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
    OUT   EFI_HANDLE                        *NotifyHandle
);

EFI_STATUS
EFIAPI
UsbKbdKeycodeInUnregisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_HANDLE                           NotificationHandle
);

VOID
EFIAPI
UsbKbdWaitForKey(
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  );

VOID
EFIAPI
KeyRepeatCallback(
    EFI_EVENT   Event, 
    VOID        *Context
);

#endif

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
