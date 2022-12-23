//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file CsmSimpleIn.c
    Implements the SimpleTextIn protocol for the Csm.

**/

#include <Efi.h>
#include <AmiDxeLib.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/AmiKeycode.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/ConsoleControl.h>
#include <Protocol/LegacyBios.h>
#include <Library/DxeServicesTableLib.h>

#ifndef ACCESS_PAGE0_CODE
#define ACCESS_PAGE0_CODE(statements)                           \
    {                                                           \
      statements;                                               \
    }
#endif

typedef struct _CSMSIMPLEIN_DEV {
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL      SimpleTextInput;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL	SimpleTextInputEx;
    AMI_EFIKEYCODE_PROTOCOL             EfiKeycodeInput;
} CSMSIMPLEIN_DEV;

typedef struct _KEY_WAITING_RECORD{
  DLINK                                         Link;
  EFI_KEY_DATA                                  Context;
  EFI_KEY_NOTIFY_FUNCTION                       Callback;
} KEY_WAITING_RECORD;

DLIST                               mCsmKeyboardData;

// Simple Input protocol function prototypes

EFI_STATUS EFIAPI CsmSimpleInInputReset(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    IN BOOLEAN                          ExtendedVerification
);

EFI_STATUS EFIAPI CsmSimpleInInputReadKey(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    OUT EFI_INPUT_KEY                   *Key
);

//Simple Input Ex protocol function prototypes

EFI_STATUS EFIAPI CsmSimpleInInputResetEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN BOOLEAN                              ExtendedVerification
);

EFI_STATUS EFIAPI CsmSimpleInInputReadKeyEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    OUT EFI_KEY_DATA                        *KeyData
);

EFI_STATUS EFIAPI CsmSimpleInInputSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_TOGGLE_STATE                 *KeyToggleState
);

EFI_STATUS EFIAPI CsmSimpleInInputRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_DATA                         *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION              KeyNotificationFunction,
    OUT EFI_HANDLE                          *NotifyHandle
);

EFI_STATUS EFIAPI CsmSimpleInInputUnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_HANDLE                           NotificationHandle
);

// AMI KeyCode protocol function prototypes

EFI_STATUS EFIAPI
CsmSimpleInInputReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL              *This,
    OUT AMI_EFI_KEY_DATA                    *KeyData
);

VOID EFIAPI ConnectCsmSimpleIn(
    IN EFI_EVENT Event, 
    IN VOID *Context
);

EFI_HANDLE          gCsmSimpleInHandle = NULL;

/**
    CSM SimpleIn driver entry point

    @param Standard EFI Image entry - EFI_IMAGE_ENTRY_POINT

    @retval The status of CSM board initialization

**/

EFI_STATUS
InitCsmSimpleIn (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{

    EFI_STATUS          Status;
    CSMSIMPLEIN_DEV     *CsmSimpleInDev = NULL;
	static EFI_GUID     GuidConInStarted = CONSOLE_IN_DEVICES_STARTED_PROTOCOL_GUID;
	EFI_EVENT 	        Event;
	VOID                *pRegistration;


    Status = pBS->AllocatePool(
                    EfiBootServicesData,
                    sizeof(CSMSIMPLEIN_DEV),
                    (VOID**)&CsmSimpleInDev);

    if (EFI_ERROR(Status)) {
        return Status;
    }

    pBS->SetMem(CsmSimpleInDev, sizeof(CSMSIMPLEIN_DEV), 0);

    CsmSimpleInDev->SimpleTextInput.Reset = CsmSimpleInInputReset;
    CsmSimpleInDev->SimpleTextInput.ReadKeyStroke = CsmSimpleInInputReadKey;
    CsmSimpleInDev->SimpleTextInput.WaitForKey = NULL;

    CsmSimpleInDev->SimpleTextInputEx.Reset = CsmSimpleInInputResetEx;
    CsmSimpleInDev->SimpleTextInputEx.ReadKeyStrokeEx = CsmSimpleInInputReadKeyEx;
    CsmSimpleInDev->SimpleTextInputEx.SetState = CsmSimpleInInputSetState;
    CsmSimpleInDev->SimpleTextInputEx.RegisterKeyNotify = CsmSimpleInInputRegisterKeyNotify;
    CsmSimpleInDev->SimpleTextInputEx.UnregisterKeyNotify = CsmSimpleInInputUnRegisterKeyNotify;
    CsmSimpleInDev->SimpleTextInputEx.WaitForKeyEx = NULL;

    CsmSimpleInDev->EfiKeycodeInput.Reset = CsmSimpleInInputResetEx;
    CsmSimpleInDev->EfiKeycodeInput.ReadEfikey = CsmSimpleInInputReadEfiKey;
    CsmSimpleInDev->EfiKeycodeInput.SetState = CsmSimpleInInputSetState;
    CsmSimpleInDev->EfiKeycodeInput.RegisterKeyNotify = CsmSimpleInInputRegisterKeyNotify;
    CsmSimpleInDev->EfiKeycodeInput.UnregisterKeyNotify = CsmSimpleInInputUnRegisterKeyNotify;
    CsmSimpleInDev->EfiKeycodeInput.WaitForKeyEx = NULL;

    Status = pBS->InstallMultipleProtocolInterfaces(
            &gCsmSimpleInHandle,
            &gEfiSimpleTextInProtocolGuid, &CsmSimpleInDev->SimpleTextInput,
            &gEfiSimpleTextInputExProtocolGuid, &CsmSimpleInDev->SimpleTextInputEx,
            &gAmiEfiKeycodeProtocolGuid, &CsmSimpleInDev->EfiKeycodeInput,
            NULL
            );
    ASSERT_EFI_ERROR(Status);
    
	RegisterProtocolCallback(
            &GuidConInStarted, ConnectCsmSimpleIn,
            NULL, &Event,&pRegistration
	        );


    return EFI_SUCCESS;
}

/**
    This function Connect the CsmSimpleIn handle 

           
    @param Event signaled event
    @param Context pointer to event context

**/

VOID EFIAPI ConnectCsmSimpleIn(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    // Connect the CsmSimpleIn, So that ConSplitter gets notified 
    pBS->ConnectController(gCsmSimpleInHandle, NULL, NULL, TRUE);
    // Kill the Event
    pBS->CloseEvent(Event); 

    return;        
}


/**
    In CsmSimpleIn implementation, this function does nothing.
**/

EFI_STATUS EFIAPI CsmSimpleInInputReset(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    IN BOOLEAN                          ExtendedVerification
)
{
    return EFI_SUCCESS;
}


/**
    In CsmSimpleIn implementation, this function does nothing.
**/

EFI_STATUS EFIAPI CsmSimpleInInputResetEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN BOOLEAN                              ExtendedVerification
)
{
    return EFI_SUCCESS;
}


/**
    Returns a EFI_INPUT_KEY Key if possible.
    In CsmSimpleIn implementation there is no key returned.
    
    @retval EFI_NOT_READY
**/

EFI_STATUS EFIAPI CsmSimpleInInputReadKey(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    OUT EFI_INPUT_KEY                   *Key
)
{
    return EFI_NOT_READY;
}


/*
 
  40:17
        |7|6|5|4|3|2|1|0| keyboard flag byte 0
         | | | | | | | `--- right shift key depressed
         | | | | | | `---- left shift key depressed
         | | | | | `----- CTRL key depressed
         | | | | `------ ALT key depressed
         | | | `------- scroll-lock is active
         | | `-------- num-lock is active
         | `--------- caps-lock is active
         `---------- insert is active
  40:18
        |7|6|5|4|3|2|1|0| keyboard flag byte
         | | | | | | | `--- left CTRL key depressed
         | | | | | | `---- left ALT key depressed
         | | | | | `----- system key depressed and held
         | | | | `------ suspend key has been toggled
         | | | `------- scroll lock key is depressed
         | | `-------- num-lock key is depressed
         | `--------- caps-lock key is depressed
         `---------- insert key is depressed
*/


/**
    Get the Key Toggle state from BDA

    @param  KeyToggleState - Pointer to the EFI_KEY_TOGGLE_STATE to
            set the state for the input device.

**/

EFI_STATUS CsmSimpleInToggleState(
    OUT EFI_KEY_TOGGLE_STATE *KeyToggleState
)
{
    UINT8   KeyState;

    ACCESS_PAGE0_CODE(
        KeyState = *(UINT8*)(UINTN)0x417;
    );

    *KeyToggleState = EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED;
    
    if (KeyState & 0x10) {
        *KeyToggleState |= EFI_SCROLL_LOCK_ACTIVE;
    }
    if (KeyState & 0x20) {
        *KeyToggleState |= EFI_NUM_LOCK_ACTIVE;
    }
    if (KeyState & 0x40) {
        *KeyToggleState |= EFI_CAPS_LOCK_ACTIVE;
    }

    return EFI_SUCCESS;
}


/**
    Get the Shift/Alt/Crtl state from BDA

    @param  KeyModifierState - Pointer to the Shift/Ctrl/Alt/SysRq state UINT32 data.

**/

EFI_STATUS CsmSimpleInModifierState(
    OUT UINT32 *KeyModifierState
)
{
    UINT16  BdaKeyState;

    ACCESS_PAGE0_CODE(
        BdaKeyState = *(UINT16*)(UINTN)0x417;
    );
    
    *KeyModifierState = EFI_SHIFT_STATE_VALID;
    
    if (BdaKeyState & 0x1) {
        *KeyModifierState |= EFI_RIGHT_SHIFT_PRESSED;
    }
    if (BdaKeyState & 0x2) {
        *KeyModifierState |= EFI_LEFT_SHIFT_PRESSED;
    }
    if (BdaKeyState & 0x4) {
        if (BdaKeyState & 0x100) {
            *KeyModifierState |= EFI_LEFT_CONTROL_PRESSED;
        } else {
            *KeyModifierState |= EFI_RIGHT_CONTROL_PRESSED;
        }
    }
    if (BdaKeyState & 0x8) {
        if (BdaKeyState & 0x200) {
            *KeyModifierState |= EFI_LEFT_ALT_PRESSED;
        } else {
            *KeyModifierState |= EFI_RIGHT_ALT_PRESSED;
        }
    }
    if (BdaKeyState & 0x400) {
        *KeyModifierState |= EFI_SYS_REQ_PRESSED;
    }

    return EFI_SUCCESS;
}


/**
    Reads the next keystroke from the input device and returns data in the form of EFI_KEY_DATA structure.
    This routine is a part of SimpleTextInEx protocol implementation.
    
    @retval EFI_NOT_READY - no keystroke is ever available from CsmSimpleIn

**/

EFI_STATUS
EFIAPI
CsmSimpleInInputReadKeyEx(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    OUT EFI_KEY_DATA *KeyData
)
{
    if(KeyData == NULL)
        return EFI_INVALID_PARAMETER;

    pBS->SetMem (KeyData, sizeof(EFI_KEY_DATA) , 0);
    CsmSimpleInToggleState(&(KeyData->KeyState.KeyToggleState));
    CsmSimpleInModifierState(&(KeyData->KeyState.KeyShiftState));
    
    return EFI_NOT_READY;
}


/**
    Set certain state for the input device.

    @param This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
                          instance.
    @param KeyToggleState - Pointer to the EFI_KEY_TOGGLE_STATE to
                          set the state for the input device.
**/

EFI_STATUS
EFIAPI
CsmSimpleInInputSetState (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE *KeyToggleState
)
{
    UINT8   CurrentKeyState;
    
    if(KeyToggleState == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    if (!(*KeyToggleState & EFI_TOGGLE_STATE_VALID) ||
        ((*KeyToggleState & (~(EFI_TOGGLE_STATE_VALID | EFI_KEY_STATE_EXPOSED | EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE)))) ) {
        return EFI_UNSUPPORTED;
    }
    ACCESS_PAGE0_CODE(
        CurrentKeyState = *(UINT8*)(UINTN)0x417;
    
        // Clear NumLock, CapsLock, Scroll Lock status
        CurrentKeyState &= 0x8F;
    
        if (*KeyToggleState & EFI_SCROLL_LOCK_ACTIVE) {
            CurrentKeyState |= 0x10;
        }
    
        if (*KeyToggleState & EFI_NUM_LOCK_ACTIVE) {
            CurrentKeyState |= 0x20;
        }
    
        if (*KeyToggleState & EFI_CAPS_LOCK_ACTIVE) {
            CurrentKeyState |= 0x40;
        }
    
        *(UINT8*)(UINTN)0x417 = CurrentKeyState;
        *(UINT8*)(UINTN)0x497 = (CurrentKeyState >> 4);     // Update LED's status flag
    );
    return EFI_SUCCESS;
}

/**
    Register a notification function for a particular
    keystroke for the input device.

    @param This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
        instance.
    @param KeyData - Key value
    @param KeyNotificationFunction- Pointer to the Notification Function
    @param NotificationHandle - Handle to be unregisterd

**/

EFI_STATUS
EFIAPI
CsmSimpleInInputRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_DATA *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    OUT EFI_HANDLE *NotifyHandle
)
{

    EFI_STATUS          Status;
    KEY_WAITING_RECORD  *CsmKeyIn;

    if(KeyData == NULL || KeyNotificationFunction == NULL || NotifyHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }


    //
    // Create database record and add to database
    //
    Status = pBS->AllocatePool (
                      EfiRuntimeServicesData,
                      sizeof (KEY_WAITING_RECORD),
                      (VOID**)&CsmKeyIn
                      );

    if(EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Gather information about the registration request
    //

    CsmKeyIn->Context   = *KeyData;
    CsmKeyIn->Callback  = KeyNotificationFunction;

    DListAdd (&mCsmKeyboardData, &(CsmKeyIn->Link));

    //
    // Child's handle will be the address linked list link in the record
    //
    *NotifyHandle = (EFI_HANDLE) (&CsmKeyIn->Link);

    return EFI_SUCCESS;
}


/**
    Removes the notification which was previously
    registered by CsmSimpleInInputRegisterKeyNotify.

    @param This - A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
        instance.
    @param NotificationHandle - Handle to be unregistered

**/

EFI_STATUS
EFIAPI
CsmSimpleInInputUnRegisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_HANDLE NotificationHandle
)
{
    DLINK               *ListPtr;
    KEY_WAITING_RECORD  *CsmKeyIn;

    if(NotificationHandle == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    ListPtr = mCsmKeyboardData.pHead;
    while ( ListPtr != NULL)
    {
        CsmKeyIn = OUTTER(ListPtr, Link, KEY_WAITING_RECORD);
        if ( (&CsmKeyIn->Link) == NotificationHandle)
        {
            DListDelete(&mCsmKeyboardData, ListPtr);
            pBS->FreePool(CsmKeyIn);
            return EFI_SUCCESS;
        }

        ListPtr = ListPtr->pNext;
    }

    return EFI_INVALID_PARAMETER;
}


/**
    Reads the next keystroke from the input device and returns data in the form of AMI_EFI_KEY_DATA structure.
    This routine is a part of AmiEfiKeycode protocol implementation.
    
    @retval EFI_NOT_READY - no keystroke is ever available from CsmSimpleIn
**/

EFI_STATUS
EFIAPI
CsmSimpleInInputReadEfiKey(
    IN AMI_EFIKEYCODE_PROTOCOL *This,
    OUT AMI_EFI_KEY_DATA *KeyData
)
{
    pBS->SetMem (KeyData, sizeof(AMI_EFI_KEY_DATA) , 0);
    CsmSimpleInToggleState(&(KeyData->KeyState.KeyToggleState));
    CsmSimpleInModifierState(&(KeyData->KeyState.KeyShiftState));
    
    return EFI_NOT_READY;
}

