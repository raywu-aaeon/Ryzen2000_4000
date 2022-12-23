//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file EfiUsbKb.c
    USB Keyboard Efi driver implementation

**/

#include "EfiUsbKb.h"
#include <Library/AmiUsbHcdLib.h>
#include <Library/PrintLib.h>

extern USB_GLOBAL_DATA *gUsbData;
extern URP_STRUC       *gParameters;
extern USB_DATA_LIST   *gUsbDataList;

AMI_MULTI_LANG_SUPPORT_PROTOCOL     *gMultiLangSupportProtocol;


// USB Key Code to Efi key mapping table
EFI_KEY_MAP gKeyMapTable[] = {
//  <USB key code>, <EFI scan code>, <unicode w/o shift>, <unicode w/ shift>, <EFI key>, <PS2 Scan code>, <shift state>, <toggle state>
//  {0x00,        SCAN_NULL,          0x00,   0x00,     0,                  0x00,    0,                        0},                        // 0x00     Reserved
    {0x01,        SCAN_NULL,          0x00,   0x00,     0,                  0xFF,    0,                        0},                        // 0x01     ErrorRollOver
    {0x02,        SCAN_NULL,          0x00,   0x00,     0,                  0xFC,    0,                        0},                        // 0x02     POSTFail
//  {0x03,        SCAN_NULL,          0x00,   0x00,     0,                  0x00,    0,                        0},                        // 0x03     ErrorUndefined
    {0x04,        SCAN_NULL,          'a',    'A',      EfiKeyC1,           0x1E,    0,                        0},                        // 0x04     a and A        
    {0x05,        SCAN_NULL,          'b',    'B',      EfiKeyB5,           0x30,    0,                        0},                        // 0x05     b and B        
    {0x06,        SCAN_NULL,          'c',    'C',      EfiKeyB3,           0x2E,    0,                        0},                        // 0x06     c and C        
    {0x07,        SCAN_NULL,          'd',    'D',      EfiKeyC3,           0x20,    0,                        0},                        // 0x07     d and D        
    {0x08,        SCAN_NULL,          'e',    'E',      EfiKeyD3,           0x12,    0,                        0},                        // 0x08     e and E        
    {0x09,        SCAN_NULL,          'f',    'F',      EfiKeyC4,           0x21,    0,                        0},                        // 0x09     f and F        
    {0x0A,        SCAN_NULL,          'g',    'G',      EfiKeyC5,           0x22,    0,                        0},                        // 0x0A     g and G        
    {0x0B,        SCAN_NULL,          'h',    'H',      EfiKeyC6,           0x23,    0,                        0},                        // 0x0B     h and H        
    {0x0C,        SCAN_NULL,          'i',    'I',      EfiKeyD8,           0x17,    0,                        0},                        // 0x0C     i and I        
    {0x0D,        SCAN_NULL,          'j',    'J',      EfiKeyC7,           0x24,    0,                        0},                        // 0x0D     j and J        
    {0x0E,        SCAN_NULL,          'k',    'K',      EfiKeyC8,           0x25,    0,                        0},                        // 0x0E     k and K        
    {0x0F,        SCAN_NULL,          'l',    'L',      EfiKeyC9,           0x26,    0,                        0},                        // 0x0F     l and L        
    {0x10,        SCAN_NULL,          'm',    'M',      EfiKeyB7,           0x32,    0,                        0},                        // 0x10     m and M        
    {0x11,        SCAN_NULL,          'n',    'N',      EfiKeyB6,           0x31,    0,                        0},                        // 0x11     n and M        
    {0x12,        SCAN_NULL,          'o',    'O',      EfiKeyD9,           0x18,    0,                        0},                        // 0x12     o and O        
    {0x13,        SCAN_NULL,          'p',    'P',      EfiKeyD10,          0x19,    0,                        0},                        // 0x13     p and P        
    {0x14,        SCAN_NULL,          'q',    'Q',      EfiKeyD1,           0x10,    0,                        0},                        // 0x14     q and Q        
    {0x15,        SCAN_NULL,          'r',    'R',      EfiKeyD4,           0x13,    0,                        0},                        // 0x15     r and R        
    {0x16,        SCAN_NULL,          's',    'S',      EfiKeyC2,           0x1F,    0,                        0},                        // 0x16     s and S        
    {0x17,        SCAN_NULL,          't',    'T',      EfiKeyD5,           0x14,    0,                        0},                        // 0x17     t and T        
    {0x18,        SCAN_NULL,          'u',    'U',      EfiKeyD7,           0x16,    0,                        0},                        // 0x18     u and U        
    {0x19,        SCAN_NULL,          'v',    'V',      EfiKeyB4,           0x2F,    0,                        0},                        // 0x19     v and V        
    {0x1A,        SCAN_NULL,          'w',    'W',      EfiKeyD2,           0x11,    0,                        0},                        // 0x1A     w and W        
    {0x1B,        SCAN_NULL,          'x',    'X',      EfiKeyB2,           0x2D,    0,                        0},                        // 0x1B     x and X        
    {0x1C,        SCAN_NULL,          'y',    'Y',      EfiKeyD6,           0x15,    0,                        0},                        // 0x1C     y and Y        
    {0x1D,        SCAN_NULL,          'z',    'Z',      EfiKeyB1,           0x2C,    0,                        0},                        // 0x1D     z and Z        
    {0x1E,        SCAN_NULL,          '1',    '!',      EfiKeyE1,           0x02,    0,                        0},                        // 0x1E     1 and !        
    {0x1F,        SCAN_NULL,          '2',    '@',      EfiKeyE2,           0x03,    0,                        0},                        // 0x1F     2 and @        
    {0x20,        SCAN_NULL,          '3',    '#',      EfiKeyE3,           0x04,    0,                        0},                        // 0x20     3 and #        
    {0x21,        SCAN_NULL,          '4',    '$',      EfiKeyE4,           0x05,    0,                        0},                        // 0x21     4 and $        
    {0x22,        SCAN_NULL,          '5',    '%',      EfiKeyE5,           0x06,    0,                        0},                        // 0x22     5 and %        
    {0x23,        SCAN_NULL,          '6',    '^',      EfiKeyE6,           0x07,    0,                        0},                        // 0x23     6 and ^        
    {0x24,        SCAN_NULL,          '7',    '&',      EfiKeyE7,           0x08,    0,                        0},                        // 0x24     7 and &        
    {0x25,        SCAN_NULL,          '8',    '*',      EfiKeyE8,           0x09,    0,                        0},                        // 0x25     8 and *        
    {0x26,        SCAN_NULL,          '9',    '(',      EfiKeyE9,           0x0A,    0,                        0},                        // 0x26     9 and (        
    {0x27,        SCAN_NULL,          '0',    ')',      EfiKeyE10,          0x0B,    0,                        0},                        // 0x27     0 and )        
    {0x28,        SCAN_NULL,          0x0D,   0x0D,     EfiKeyEnter,        0x1C,    0,                        0},                        // 0x28     Return(Enter)
    {0x29,        SCAN_ESC,           0x00,   0x00,     EfiKeyEsc,          0x01,    0,                        0},                        // 0x29     Escape         
    {0x2A,        SCAN_NULL,          0x08,   0x08,     EfiKeyBackSpace,    0x0E,    0,                        0},                        // 0x2A     Backspace   
    {0x2B,        SCAN_NULL,          0x09,   0x09,     EfiKeyTab,          0x0F,    0,                        0},                        // 0x2B     Tab            
    {0x2C,        SCAN_NULL,          ' ',    ' ',      EfiKeySpaceBar,     0x39,    0,                        0},                        // 0x2C     Space          
    {0x2D,        SCAN_NULL,          '-',    '_',      EfiKeyE11,          0x0C,    0,                        0},                        // 0x2D     - and _        
    {0x2E,        SCAN_NULL,          '=',    '+',      EfiKeyE12,          0x0D,    0,                        0},                        // 0x2E     = and +        
    {0x2F,        SCAN_NULL,          '[',    '{',      EfiKeyD11,          0x1A,    0,                        0},                        // 0x2F     [ and {        
    {0x30,        SCAN_NULL,          ']',    '}',      EfiKeyD12,          0x1B,    0,                        0},                        // 0x30     ] and }        
    {0x31,        SCAN_NULL,          '\\',   '|',      EfiKeyD13,          0x2B,    0,                        0},                        // 0x31     \ and |        
    {0x32,        SCAN_NULL,          '\\',   '|',      EfiKeyC12,          0x2B,    0,                        0},                        // 0x32     None-US # and ~
    {0x33,        SCAN_NULL,          ';',    ':',      EfiKeyC10,          0x27,    0,                        0},                        // 0x33     ; and :        
    {0x34,        SCAN_NULL,          '\'',   '"',      EfiKeyC11,          0x28,    0,                        0},                        // 0x34     ' and "        
    {0x35,        SCAN_NULL,          '`',    '~',      EfiKeyE0,           0x29,    0,                        0},                        // 0x35     ` and ~        
    {0x36,        SCAN_NULL,          ',',    '<',      EfiKeyB8,           0x33,    0,                        0},                        // 0x36     , and <        
    {0x37,        SCAN_NULL,          '.',    '>',      EfiKeyB9,           0x34,    0,                        0},                        // 0x37     . and >        
    {0x38,        SCAN_NULL,          '/',    '?',      EfiKeyB10,          0x35,    0,                        0},                        // 0x38     / and ?        
    {0x39,        SCAN_NULL,          0x00,   0x00,     EfiKeyCapsLock,     0x3A,    0,                        EFI_CAPS_LOCK_ACTIVE},     // 0x39     Caps Lock
    {0x3A,        SCAN_F1,            0x00,   0x00,     EfiKeyF1,           0x3B,    0,                        0},                        // 0x3A     F1          
    {0x3B,        SCAN_F2,            0x00,   0x00,     EfiKeyF2,           0x3C,    0,                        0},                        // 0x3B     F2          
    {0x3C,        SCAN_F3,            0x00,   0x00,     EfiKeyF3,           0x3D,    0,                        0},                        // 0x3C     F3          
    {0x3D,        SCAN_F4,            0x00,   0x00,     EfiKeyF4,           0x3E,    0,                        0},                        // 0x3D     F4          
    {0x3E,        SCAN_F5,            0x00,   0x00,     EfiKeyF5,           0x3F,    0,                        0},                        // 0x3E     F5          
    {0x3F,        SCAN_F6,            0x00,   0x00,     EfiKeyF6,           0x40,    0,                        0},                        // 0x3F     F6          
    {0x40,        SCAN_F7,            0x00,   0x00,     EfiKeyF7,           0x41,    0,                        0},                        // 0x40     F7          
    {0x41,        SCAN_F8,            0x00,   0x00,     EfiKeyF8,           0x42,    0,                        0},                        // 0x41     F8          
    {0x42,        SCAN_F9,            0x00,   0x00,     EfiKeyF9,           0x43,    0,                        0},                        // 0x42     F9          
    {0x43,        SCAN_F10,           0x00,   0x00,     EfiKeyF10,          0x44,    0,                        0},                        // 0x43     F10         
    {0x44,        SCAN_F11,           0x00,   0x00,     EfiKeyF11,          0x57,    0,                        0},                        // 0x44     F11         
    {0x45,        SCAN_F12,           0x00,   0x00,     EfiKeyF12,          0x58,    0,                        0},                        // 0x45     F12         
    {0x46,        SCAN_NULL,          0x00,   0x00,     EfiKeyPrint,        0x00,    EFI_SYS_REQ_PRESSED,      0},                        // 0x46     Print Screen
    {0x47,        SCAN_NULL,          0x00,   0x00,     EfiKeySLck,         0x46,    0,                        EFI_SCROLL_LOCK_ACTIVE},   // 0x47     Scroll Lock
    {0x48,        SCAN_PAUSE,         0x00,   0x00,     EfiKeyPause,        0x00,    0,                        0},                        // 0x48     Pause      
    {0x49,        SCAN_INSERT,        0x00,   0x00,     EfiKeyIns,          0x52,    0,                        0},                        // 0x49     Insert     
    {0x4A,        SCAN_HOME,          0x00,   0x00,     EfiKeyHome,         0x47,    0,                        0},                        // 0x4A     Home       
    {0x4B,        SCAN_PAGE_UP,       0x00,   0x00,     EfiKeyPgUp,         0x49,    0,                        0},                        // 0x4B     Page Up    
    {0x4C,        SCAN_DELETE,        0x00,   0x00,     EfiKeyDel,          0x53,    0,                        0},                        // 0x4C     Delete     
    {0x4D,        SCAN_END,           0x00,   0x00,     EfiKeyEnd,          0x4F,    0,                        0},                        // 0x4D     End        
    {0x4E,        SCAN_PAGE_DOWN,     0x00,   0x00,     EfiKeyPgDn,         0x51,    0,                        0},                        // 0x4E     Page Down  
    {0x4F,        SCAN_RIGHT,         0x00,   0x00,     EfiKeyRightArrow,   0x4D,    0,                        0},                        // 0x4F     Right Arrow
    {0x50,        SCAN_LEFT,          0x00,   0x00,     EfiKeyLeftArrow,    0x4B,    0,                        0},                        // 0x50     Left Arrow 
    {0x51,        SCAN_DOWN,          0x00,   0x00,     EfiKeyDownArrow,    0x50,    0,                        0},                        // 0x51     Down Arrow 
    {0x52,        SCAN_UP,            0x00,   0x00,     EfiKeyUpArrow,      0x48,    0,                        0},                        // 0x52     Up Arrow   
    {0x53,        SCAN_NULL,          0x00,   0x00,     EfiKeyNLck,         0x45,    0,                        EFI_NUM_LOCK_ACTIVE},      // 0x53     Keypad Num Lock
    {0x54,        SCAN_NULL,          '/',    '/',      EfiKeySlash,        0x35,    0,                        0},                        // 0x54     Keypad /                
    {0x55,        SCAN_NULL,          '*',    '*',      EfiKeyAsterisk,     0x37,    0,                        0},                        // 0x55     Keypad *                
    {0x56,        SCAN_NULL,          '-',    '-',      EfiKeyMinus,        0x4A,    0,                        0},                        // 0x56     Keypad -                
    {0x57,        SCAN_NULL,          '+',    '+',      EfiKeyPlus,         0x4E,    0,                        0},                        // 0x57     Keypad +                
    {0x58,        SCAN_NULL,          0x0D,   0x0D,     EfiKeyEnter,        0x1C,    0,                        0},                        // 0x58     Keypad Enter            
    {0x59,        SCAN_END,           '1',    0x00,     EfiKeyOne,          0x4F,    0,                        0},                        // 0x59     Keypad 1 and End        
    {0x5A,        SCAN_DOWN,          '2',    0x00,     EfiKeyTwo,          0x50,    0,                        0},                        // 0x5A     Keypad 2 and Down Arrow 
    {0x5B,        SCAN_PAGE_DOWN,     '3',    0x00,     EfiKeyThree,        0x51,    0,                        0},                        // 0x5B     Keypad 3 and PageDn     
    {0x5C,        SCAN_LEFT,          '4',    0x00,     EfiKeyFour,         0x4B,    0,                        0},                        // 0x5C     Keypad 4 and Left Arrow 
    {0x5D,        SCAN_NULL,          '5',    0x00,     EfiKeyFive,         0x4C,    0,                        0},                        // 0x5D     Keypad 5                
    {0x5E,        SCAN_RIGHT,         '6',    0x00,     EfiKeySix,          0x4D,    0,                        0},                        // 0x5E     Keypad 6 and Right Arrow
    {0x5F,        SCAN_HOME,          '7',    0x00,     EfiKeySeven,        0x47,    0,                        0},                        // 0x5F     Keypad 7 and Home       
    {0x60,        SCAN_UP,            '8',    0x00,     EfiKeyEight,        0x48,    0,                        0},                        // 0x60     Keypad 8 and Up Arrow   
    {0x61,        SCAN_PAGE_UP,       '9',    0x00,     EfiKeyNine,         0x49,    0,                        0},                        // 0x61     Keypad 9 and PageUp     
    {0x62,        SCAN_INSERT,        '0',    0x00,     EfiKeyZero,         0x52,    0,                        0},                        // 0x62     Keypad 0 and Insert     
    {0x63,        SCAN_DELETE,        '.',    0x00,     EfiKeyPeriod,       0x53,    0,                        0},                        // 0x63     Keypad . and Delete     
    {0x64,        SCAN_NULL,          '\\',   '|',      EfiKeyB0,           0x56,    0,                        0},                        // 0x64     Non-US \ and |
    {0x65,        SCAN_NULL,          0x00,   0x00,     EfiKeyA4,           0x00,    EFI_MENU_KEY_PRESSED,     0},                        // 0x65     Application
    {0x66,        SCAN_NULL,          0x00,   0x00,     0,                  0x00,    0,                        0},                        // 0x66     Power
    {0x67,        SCAN_NULL,          '=' ,   '=',      0,                  0x59,    0,                        0},                        // 0x67     Keypad =
    {0x68,        SCAN_F13,           0x00,   0x00,     0,                  0x64,    0,                        0},                        // 0x68     F13
    {0x69,        SCAN_F14,           0x00,    0x00,    0,                  0x65,    0,                        0},                        // 0x69     F14
    {0x6A,        SCAN_F15,           0x00,    0x00,    0,                  0x66,    0,                        0},                        // 0x6A     F15
    {0x6B,        SCAN_F16,           0x00,    0x00,    0,                  0x67,    0,                        0},                        // 0x6B     F16
    {0x6C,        SCAN_F17,           0x00,    0x00,    0,                  0x68,    0,                        0},                        // 0x6C     F17
    {0x6D,        SCAN_F18,           0x00,    0x00,    0,                  0x69,    0,                        0},                        // 0x6D     F18
    {0x6E,        SCAN_F19,           0x00,    0x00,    0,                  0x6A,    0,                        0},                        // 0x6E     F19
    {0x6F,        SCAN_F20,           0x00,    0x00,    0,                  0x6B,    0,                        0},                        // 0x6F     F20
    {0x70,        SCAN_F21,           0x00,    0x00,    0,                  0x6C,    0,                        0},                        // 0x70     F21
    {0x71,        SCAN_F22,           0x00,    0x00,    0,                  0x6D,    0,                        0},                        // 0x71     F22
    {0x72,        SCAN_F23,           0x00,    0x00,    0,                  0x6E,    0,                        0},                        // 0x72     F23
    {0x73,        SCAN_F24,           0x00,    0x00,    0,                  0x76,    0,                        0},                        // 0x72     F24
                                    
    {0x7F,        SCAN_MUTE,          0x00,    0x00,    0,                  0x00,    0,                        0},                        // 0x7F     Keyboard Mute
    {0x80,        SCAN_VOLUME_UP,     0x00,    0x00,    0,                  0x00,    0,                        0},                        // 0x80     Keyboard Volume Up
    {0x81,        SCAN_VOLUME_DOWN,   0x00,    0x00,    0,                  0x00,    0,                        0},                        // 0x81     Keyboard Volume Dn
    {0x87,        SCAN_NULL,          '\\',    '_',     EfiKeyB0,           0x73,    0,                        0},                        // 0x87     Keyboard Int'l 1 (Ro)
    {0x89,        SCAN_NULL,          0xA5,    '|',     EfiKeyD13,          0x7D,    0,                        0},                        // 0x89     Keyboard Int'l 2 (Yen)
                        
    {0xE0,        SCAN_NULL,          0x00,    0x00,    EfiKeyLCtrl,        0x00,    EFI_LEFT_CONTROL_PRESSED, 0},                        // 0xE0     LeftControl
    {0xE1,        SCAN_NULL,          0x00,    0x00,    EfiKeyLShift,       0x00,    EFI_LEFT_SHIFT_PRESSED,   0},                        // 0xE1     LeftShift
    {0xE2,        SCAN_NULL,          0x00,    0x00,    EfiKeyLAlt,         0x00,    EFI_LEFT_ALT_PRESSED,     0},                        // 0xE2     LeftAlt
    {0xE3,        SCAN_NULL,          0x00,    0x00,    EfiKeyA0,           0x00,    EFI_LEFT_LOGO_PRESSED,    0},                        // 0xE3     Left GUI
    {0xE4,        SCAN_NULL,          0x00,    0x00,    EfiKeyRCtrl,        0x00,    EFI_RIGHT_CONTROL_PRESSED,0},                        // 0xE4     RightControl
    {0xE5,        SCAN_NULL,          0x00,    0x00,    EfiKeyRShift,       0x00,    EFI_RIGHT_SHIFT_PRESSED,  0},                        // 0xE5     RightShift
    {0xE6,        SCAN_NULL,          0x00,    0x00,    EfiKeyA2,           0x00,    EFI_RIGHT_ALT_PRESSED,    0},                        // 0xE6     RightAlt
    {0xE7,        SCAN_NULL,          0x00,    0x00,    EfiKeyA3,           0x00,    EFI_RIGHT_LOGO_PRESSED,   0}                         // 0xE7     Right GUI
};


/**
    USB EFI keyboard driver driver protocol function that
    returns the keyboard controller name.

    @param Controller       The handle of a controller that the driver specified by
                            This is managing.  This handle specifies the controller
                            whose name is to be returned.
    @param Child            The handle of the child controller to retrieve the name
                            of.  This is an optional parameter that may be NULL.  It
                            will be NULL for device drivers.  It will also be NULL
                            for a bus drivers that wish to retrieve the name of the
                            bus controller.  It will not be NULL for a bus driver
                            that wishes to retrieve the name of a child controller.
                            Language         - A pointer to a three character ISO 639-2 language
                            identifier.  This is the language of the controller name
                            that that the caller is requesting, and it must match one
                            of the languages specified in SupportedLanguages.  The
                            number of languages supported by a driver is up to the
                            driver writer.
    @retval NULL            No controller name
**/

CHAR16*
UsbKbdGetControllerName(
    EFI_HANDLE Controller,
    EFI_HANDLE Child
)
{
    return NULL;
}

/**
    Initialize the key buffer

    @param KeyBuffer   Pointer to the key buffer structure

**/
VOID
InitKeyBuffer (
    KEY_BUFFER    *KeyBuffer
)
{
    UINT32  Index;
    UINT8   *Buffer;

    if ((KeyBuffer == NULL) || (KeyBuffer->Buffer == NULL)) {
        return;
    }

    Buffer = (UINT8*)KeyBuffer->Buffer;

    SetMem(Buffer, (KeyBuffer->MaxKey * sizeof(VOID*)) + 
        (KeyBuffer->MaxKey * KeyBuffer->KeySize), 0);

    Buffer += KeyBuffer->MaxKey * sizeof(VOID*);    
   
    for (Index = 0; 
        Index < KeyBuffer->MaxKey;
        Index++, Buffer += KeyBuffer->KeySize) {
        KeyBuffer->Buffer[Index] = Buffer;
    }
   
    KeyBuffer->Head = 0;
    KeyBuffer->Tail = 0;
}

/**
    Create a key buffer

    @param KeyBuffer    Pointer to the key buffer structure
    @param MaxKey       Maximum key of the buffer
    @param KeySize      Size of one key

    @retval EFI_SUCCESS             Succeeded to create a key buffer.
    @retval EFI_INVALID_PARAMETER   Input is not valid.

**/

EFI_STATUS
CreateKeyBuffer (
    KEY_BUFFER    *KeyBuffer,
    UINT8         MaxKey,
    UINT32        KeySize
)
{
    EFI_STATUS    Status;
    UINT8         *Buffer = NULL;

    if (KeyBuffer == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    Status = gBS->AllocatePool(
                    EfiBootServicesData, 
                    (MaxKey * sizeof(VOID*)) + (MaxKey * KeySize), 
                    (VOID**)&Buffer
                    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    KeyBuffer->Buffer = (VOID**)Buffer;
    KeyBuffer->MaxKey = MaxKey;
    KeyBuffer->KeySize = KeySize;

    InitKeyBuffer(KeyBuffer);

    return EFI_SUCCESS;
}

/**
    Destroy the key buffer

    @param KeyBuffer    Pointer to the key buffer structure

    @retval EFI_SUCCESS  Succeeded to Destroy a key buffer.

**/

EFI_STATUS
DestroyKeyBuffer (
    KEY_BUFFER    *KeyBuffer
)
{
    if ((KeyBuffer == NULL) || (KeyBuffer->Buffer == NULL)) {
        return EFI_SUCCESS;
    }
    
    gBS->FreePool(KeyBuffer->Buffer);
    SetMem(KeyBuffer, sizeof(KEY_BUFFER), 0);

    return EFI_SUCCESS;
}

/**
    Check whether the key buffer is empty

    @param KeyBuffer   Pointer to the key buffer structure

    @retval TRUE       Buffer is empty
    @retval FALSE      Buffer is not empty

**/

BOOLEAN
IsKeyBufferEmpty (
    KEY_BUFFER    *KeyBuffer
)
{
    return (KeyBuffer->Tail == KeyBuffer->Head);
}

/**
    Insert a key to key buffer.

    @param KeyBuffer    Pointer to the key buffer structure
    @param Key          The key to be inserted

**/

VOID
InsertKey (
    KEY_BUFFER    *KeyBuffer,
    VOID          *Key
)
{
    if ((KeyBuffer == NULL) || (KeyBuffer->Buffer == NULL)) {
        return;
    }
    CopyMem(KeyBuffer->Buffer[KeyBuffer->Head], Key, KeyBuffer->KeySize);

    KeyBuffer->Head = ((KeyBuffer->Head + 1) % KeyBuffer->MaxKey);

    if (KeyBuffer->Head == KeyBuffer->Tail){
        //Drop data from buffer
        KeyBuffer->Tail = ((KeyBuffer->Tail + 1) % KeyBuffer->MaxKey);
    }
}


/**
    Get a key from the buffer and remove it.

    @param KeyBuffer    Pointer to the key buffer structure
    @param Key          The key to be inserted

**/

VOID
GetKey (
    KEY_BUFFER    *KeyBuffer,
    VOID          *Key
)
{
    if ((KeyBuffer == NULL) || (KeyBuffer->Buffer == NULL)) {
        return;
    }
    if (KeyBuffer->Tail == KeyBuffer->Head) {
        return;
    }

    CopyMem(Key, KeyBuffer->Buffer[KeyBuffer->Tail], KeyBuffer->KeySize);
    KeyBuffer->Tail = ((KeyBuffer->Tail + 1) % KeyBuffer->MaxKey);
}


/**
    Set USB Keyboard LED state

    @param UsbKbd        Pointer to USB_KB_DEV instance

    @retval EFI_SUCCESS  Success to set keyboard LED

**/

EFI_STATUS
SetLed (
    USB_KB_DEV    *UsbKbd
)
{
    LED_MAP         Led;

    SetMem(&Led, sizeof(LED_MAP), 0);
    //
    // Set each field in Led map.
    //
    Led.NumLock = (UsbKbd->ToggleState & EFI_NUM_LOCK_ACTIVE) ? 1 : 0;
    Led.CapsLock = (UsbKbd->ToggleState & EFI_CAPS_LOCK_ACTIVE) ? 1 : 0;
    Led.ScrLock = (UsbKbd->ToggleState & EFI_SCROLL_LOCK_ACTIVE) ? 1 : 0;

    gBS->SetMem(gParameters, sizeof(URP_STRUC), 0);
    gParameters->ApiData.EfiKbLedsData.LedMapPtr = (UINTN)&Led;
    gParameters->ApiData.EfiKbLedsData.DevInfoPtr = (UINTN)UsbKbd->DevInfo;

    //
    // Lighten up LEDs.
    //
    
    gParameters->FuncNumber         = USB_API_LIGHTEN_KEYBOARD_LEDS;
    gParameters->SubFunc            = 0;

    InvokeUsbApi(gParameters);

    return EFI_SUCCESS;
}

/**
    It maps the current key to a Unicode character from
    the keyboard layout

    @param KeyData   Pointer to the AMI_EFI_KEY_DATA .

    @retval EFI_SUCCESS  Success to set language

**/

EFI_STATUS 
ProcessMultiLanguage (
    IN OUT  AMI_EFI_KEY_DATA                *KeyData
)
{
    EFI_STATUS Status;

    if (gMultiLangSupportProtocol == NULL) {
        Status= gBS->LocateProtocol(
                       &gAmiMultiLangSupportProtocolGuid,
                       NULL,
                       (VOID**)&gMultiLangSupportProtocol
                       );
        if (EFI_ERROR(Status)) {
            return EFI_NOT_FOUND;
        }
    }    

    return gMultiLangSupportProtocol->KeyboardLayoutMap(gMultiLangSupportProtocol, KeyData);
}

/**
    Converts USB key code to EFI Scan Code

    @param UsbKbd    Pointer to USB_KB_DEV instance
    @param UsbKey    Indicates the USB key that will be interpreted.
    @param EfiKey    A pointer to a buffer that is filled in with
                     the keystroke information for the key that
                     was pressed.

    @retval EFI_SUCCESS    Success convert USB key to EFI scan code.
    @retval EFI_NOT_READY  Key map is null

**/

EFI_STATUS
UsbKeyToEfiKey (
    USB_KB_DEV            *UsbKbd,
    USB_KEY               *UsbKey,
    AMI_EFI_KEY_DATA      *EfiKey

)
{
    UINT8                    Index = 0;
    EFI_KEY_MAP                *KeyMap = NULL;
    EFI_KEY_TOGGLE_STATE    ToggleState = 0;
    AMI_EFI_KEY_DATA        NewEfiKey;
    EFI_STATUS              MultiLanguageStatus;

    SetMem(&NewEfiKey, sizeof(AMI_EFI_KEY_DATA), 0);
    
    for (Index = 0; Index < sizeof(gKeyMapTable) / sizeof(gKeyMapTable[0]); Index++) {
        if (gKeyMapTable[Index].UsbKeyCode == UsbKey->KeyCode) {
            KeyMap = &gKeyMapTable[Index];
            break;
        }
    }

    if (KeyMap == NULL) {
        return EFI_NOT_READY;
    }

    ToggleState = UsbKbd->LastToggleState & KeyMap->ToggleState;

    if (UsbKey->Press) {
        UsbKbd->ShiftState |= KeyMap->ShiftState;
        UsbKbd->LastToggleState |= KeyMap->ToggleState;
    } else {
        UsbKbd->ShiftState &= ~KeyMap->ShiftState;
        UsbKbd->LastToggleState &= ~KeyMap->ToggleState;
        return EFI_NOT_READY;
    }

    ToggleState ^= KeyMap->ToggleState;

    if (ToggleState != 0) {
        // Toggle state changed, update the toggle state and set LED
        UsbKbd->ToggleState ^= ToggleState;
        SetLed(UsbKbd);
    }

    NewEfiKey.Key.ScanCode = KeyMap->ScanCode;
    NewEfiKey.Key.UnicodeChar = KeyMap->Unicode;
    NewEfiKey.EfiKey = KeyMap->EfiKey;
    NewEfiKey.PS2ScanCode = KeyMap->PS2ScanCode;
    NewEfiKey.KeyState.KeyShiftState = UsbKbd->ShiftState | EFI_SHIFT_STATE_VALID;
    NewEfiKey.KeyState.KeyToggleState = UsbKbd->ToggleState | EFI_TOGGLE_STATE_VALID;

    if (UsbKbd->ShiftState & (EFI_RIGHT_SHIFT_PRESSED | EFI_LEFT_SHIFT_PRESSED)) {
        NewEfiKey.Key.UnicodeChar = KeyMap->ShiftedUnicode;
    }

    if (UsbKbd->ToggleState & EFI_CAPS_LOCK_ACTIVE) {
        if (NewEfiKey.Key.UnicodeChar >= 'a' && NewEfiKey.Key.UnicodeChar <= 'z') {
            NewEfiKey.Key.UnicodeChar = KeyMap->ShiftedUnicode;
        } else if (NewEfiKey.Key.UnicodeChar >= 'A' && NewEfiKey.Key.UnicodeChar <= 'Z') {
            NewEfiKey.Key.UnicodeChar = KeyMap->Unicode;
        }
    }

    if (UsbKbd->ShiftState & (EFI_RIGHT_CONTROL_PRESSED | EFI_LEFT_CONTROL_PRESSED) &&
        UsbKbd->ShiftState & (EFI_RIGHT_ALT_PRESSED | EFI_LEFT_ALT_PRESSED) &&
        NewEfiKey.Key.ScanCode == SCAN_DELETE) {
        NewEfiKey.Key.UnicodeChar = 0;
    }

    if (NewEfiKey.Key.ScanCode != SCAN_NULL && NewEfiKey.Key.UnicodeChar != 0) {
        if (UsbKbd->ToggleState & EFI_NUM_LOCK_ACTIVE) {
            NewEfiKey.Key.ScanCode = SCAN_NULL;
        } else {
            NewEfiKey.Key.UnicodeChar = 0;
        }
    }

    MultiLanguageStatus = ProcessMultiLanguage(&NewEfiKey);
    
    if (!(UsbKbd->ToggleState & EFI_NUM_LOCK_ACTIVE) && NewEfiKey.EfiKey == EfiKeyFive) {
        NewEfiKey.Key.UnicodeChar = 0;
    }

    if (UsbKbd->ShiftState & (EFI_RIGHT_SHIFT_PRESSED | EFI_LEFT_SHIFT_PRESSED)) {
        // If a class of printable characters that are normally 
        // adjusted by shift modifiers (e.g. Shift Key + "f" key) 
        // would be presented solely as a KeyData.Key.UnicodeChar 
        // without the associated shift state.
        if (KeyMap->ShiftedUnicode != KeyMap->Unicode) {
            if (KeyMap->ScanCode == SCAN_NULL || 
                UsbKbd->ToggleState & EFI_NUM_LOCK_ACTIVE) {
                NewEfiKey.KeyState.KeyShiftState &= 
                    ~(EFI_LEFT_SHIFT_PRESSED | EFI_RIGHT_SHIFT_PRESSED);
            }
        }
    }

    if (NewEfiKey.Key.ScanCode == SCAN_NULL && NewEfiKey.Key.UnicodeChar == 0 &&
        KeyMap->ToggleState == 0) {
        if (NewEfiKey.KeyState.KeyShiftState & ~EFI_SHIFT_STATE_VALID) {
            // If the Key ShiftState has valid key but KEY_STATE_EXPOSED bit not enabled,
            // don't insert key into buffer
            if (!(NewEfiKey.KeyState.KeyToggleState & EFI_KEY_STATE_EXPOSED)) {
                UsbKbd->LastUsbKeyCode = 0;
                return EFI_UNSUPPORTED;
            }
        }
    }

    CopyMem(EfiKey, &NewEfiKey, sizeof(NewEfiKey));

    if (MultiLanguageStatus == EFI_WARN_STALE_DATA) {
        return MultiLanguageStatus;
    }

    return EFI_SUCCESS;

}


/**
    Check whether the pressed key matches a registered key or not.

    @param RegisteredKey  A pointer to keystroke data for the key that was registered.
    @param InputKey       A pointer to keystroke data for the key that was pressed.

    @retval TRUE          The key is registered or any incomplete key is registered.
    @retval FALSE         The key is not registered.

**/

BOOLEAN
IsKeyRegistered(
    EFI_KEY_DATA    *RegisteredKey,
    EFI_KEY_DATA    *InputKey
)
{
    if ((RegisteredKey == NULL) || (InputKey == NULL)) {
        return FALSE;
    }

    // If KeyData.Key, KeyData.KeyState.KeyToggleState and KeyData.KeyState.KeyShiftState are 0, 
    // then any incomplete keystroke will trigger a notification of the KeyNotificationFunction.
    if (RegisteredKey->Key.ScanCode == 0 && RegisteredKey->Key.UnicodeChar == 0
            && RegisteredKey->KeyState.KeyShiftState == 0 && RegisteredKey->KeyState.KeyToggleState == 0){
        return TRUE;
    }

    if ((RegisteredKey->Key.ScanCode != InputKey->Key.ScanCode) ||
        (RegisteredKey->Key.UnicodeChar != InputKey->Key.UnicodeChar)) {
        return FALSE;
    }

    if ((RegisteredKey->KeyState.KeyShiftState & EFI_SHIFT_STATE_VALID) &&
        (RegisteredKey->KeyState.KeyShiftState != InputKey->KeyState.KeyShiftState)) {
        return FALSE;
    }

    if ((RegisteredKey->KeyState.KeyToggleState & EFI_TOGGLE_STATE_VALID) &&
        ((RegisteredKey->KeyState.KeyToggleState ^ 
        InputKey->KeyState.KeyToggleState) & (EFI_TOGGLE_STATE_VALID | 
        EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE))) {
        return FALSE;
    }

    return TRUE;
}


/**
    Process the keystroke data before it is inserted to EFI 
    key buffer

    @param UsbKbd     Pointer to USB_KB_DEV instance
    @param EfiKey     A pointer to keystroke data for the key hat 
                      was pressed.

    @retval EFI_SUCCESS     Suceess to proecess the EFI key.

**/

EFI_STATUS
ProcessEfiKey (
    USB_KB_DEV          *UsbKbd,
    AMI_EFI_KEY_DATA    *EfiKey
)
{
    LIST_ENTRY         *Link = NULL;
    KEY_NOTIFY_LINK    *NotifyLink = NULL;

    for (Link = UsbKbd->KeyNotifyList.ForwardLink;
        Link != &UsbKbd->KeyNotifyList; 
        Link = Link->ForwardLink ) {
        NotifyLink = BASE_CR(Link, KEY_NOTIFY_LINK, Link);

        if (IsKeyRegistered(&NotifyLink->KeyData, (EFI_KEY_DATA*)EfiKey)) {
            CopyMem(&NotifyLink->KeyPressed, EfiKey, 
                    sizeof(NotifyLink->KeyPressed));
            gBS->SignalEvent(NotifyLink->NotifyEvent);
        }    

    }

    return EFI_SUCCESS;
}


/**
    Process the pending USB key and insert it to EFI key buffer

    @param UsbKbd     Pointer to USB_KB_DEV instance

    @retval EFI_SUCCESS     Suceess to process the Usb key.

**/

EFI_STATUS
ProcessUsbKey(
    USB_KB_DEV        *UsbKbd
)
{
    EFI_STATUS          Status = EFI_NOT_READY;
    static BOOLEAN      InProgress = FALSE;
    USB_KEY             UsbKey;
    AMI_EFI_KEY_DATA    EfiKey;
    BOOLEAN             NewKey = FALSE;                 

    if (InProgress) {
        return Status;
    }
    
    SetMem(&UsbKey, sizeof(USB_KEY), 0);
    SetMem(&EfiKey, sizeof(AMI_EFI_KEY_DATA), 0);
    
    InProgress = TRUE;

    while (!IsKeyBufferEmpty(&UsbKbd->DevInfo->UsbKeyBuffer)) {

        GetKey(&UsbKbd->DevInfo->UsbKeyBuffer, &UsbKey);

        NewKey = TRUE;

        if (UsbKey.Press == FALSE && UsbKbd->LastUsbKeyCode == UsbKey.KeyCode) {
            UsbKbd->LastUsbKeyCode = 0;
        }

        Status = UsbKeyToEfiKey(UsbKbd, &UsbKey, &EfiKey);
        
        if ((EFI_ERROR(Status)) && (Status != EFI_WARN_STALE_DATA)){
            continue;
        }

        ProcessEfiKey(UsbKbd, &EfiKey);
        InsertKey(&UsbKbd->EfiKeyBuffer, &EfiKey);
        UsbKbd->LastUsbKeyCode = UsbKey.KeyCode;
        
        // KeyboardLayoutMap returns EFI_WARN_STALE_DATA and returns 
        // the deadkey as a character to print, we have to handle the following Key again.
        if (Status == EFI_WARN_STALE_DATA) {
            Status = UsbKeyToEfiKey(UsbKbd, &UsbKey, &EfiKey);
            if (EFI_ERROR(Status)) {
                continue;
            }
            ProcessEfiKey(UsbKbd, &EfiKey);
            InsertKey(&UsbKbd->EfiKeyBuffer, &EfiKey);
            UsbKbd->LastUsbKeyCode = UsbKey.KeyCode;
        }
    }

    if ((NewKey == TRUE) && (UsbKbd->LastUsbKeyCode != 0)) {
        
        // The event might be is in the signaled state and it's NotifyFunction 
        // is queued, we close this event to remove it from the queue.
        gBS->CloseEvent(UsbKbd->KeyRepeatEvent);
        
        gBS->CreateEvent(
            EVT_TIMER | EVT_NOTIFY_SIGNAL,
            TPL_NOTIFY,
            KeyRepeatCallback,
            UsbKbd,
            &UsbKbd->KeyRepeatEvent);
        
        gBS->SetTimer(UsbKbd->KeyRepeatEvent, TimerRelative, USB_KBD_REPEAT_DELAY);
    }
    
    InProgress = FALSE;
    return Status;
}


/**
    This routine is called every time the key repeat is requested

    @param Event      Event that caused this function to be called
    @param Context    Context of the event

**/

VOID
EFIAPI
KeyRepeatCallback(
    EFI_EVENT   Event, 
    VOID        *Context
)
{
    USB_KB_DEV            *UsbKbd = (USB_KB_DEV*)Context;
    EFI_STATUS            Status = EFI_NOT_READY;
    USB_KEY               UsbKey;
    AMI_EFI_KEY_DATA      EfiKey;

    if (!(UsbKbd->DevInfo->Flag & DEV_INFO_DEV_PRESENT)) {
        return;
    }

    //
    // Do nothing when there is no repeat key.
    //
    if (UsbKbd->LastUsbKeyCode == 0) {
        return;
    }

    SetMem(&UsbKey, sizeof(USB_KEY), 0);
    SetMem(&EfiKey, sizeof(AMI_EFI_KEY_DATA), 0);
    
    UsbKey.KeyCode = UsbKbd->LastUsbKeyCode;
    UsbKey.Press = TRUE;
    Status = UsbKeyToEfiKey(UsbKbd, &UsbKey, &EfiKey);
    if ((EFI_ERROR(Status)) && (Status != EFI_WARN_STALE_DATA)) {
        return;
    }

    ProcessEfiKey(UsbKbd, &EfiKey);

    //
    // Inserts one Repeat key into keyboard buffer,
    //
    if (IsKeyBufferEmpty(&UsbKbd->EfiKeyBuffer)) {
        InsertKey(&UsbKbd->EfiKeyBuffer, &EfiKey);
    }

    // KeyboardLayoutMap returns EFI_WARN_STALE_DATA and returns 
    // the deadkey as a character to print, we have to handle the following Key again.
    if (Status == EFI_WARN_STALE_DATA) {
        Status = UsbKeyToEfiKey(UsbKbd, &UsbKey, &EfiKey);
        if (EFI_ERROR(Status)) {
            return;
        }
    }

    gBS->SetTimer(Event, TimerRelative, USB_KBD_REPEAT_RATE);
}


/**
    Timer callback to process USB key that was pressed.

    @param Event     Event that caused this function to be called
    @param Context   Context of the event


**/

VOID
EFIAPI
UsbKbdTimerCallback (
    EFI_EVENT    Event, 
    VOID        *Context
)
{
    ProcessUsbKey((USB_KB_DEV*)Context);
}

/**
    This function is called when registered key is pressed.

    @param Event      Event that caused this function to be called
    @param Context    Context of the event

**/

VOID
EFIAPI
UsbKeyNotifyCallback (
    EFI_EVENT    Event, 
    VOID        *Context
)
{
    KEY_NOTIFY_LINK    *NotifyLink = (KEY_NOTIFY_LINK*)Context;

    NotifyLink->NotifyFunction(&NotifyLink->KeyPressed);
}

/**
    Initialize all private key buffers

    @param UsbKbd    Pointer to USB_KB_DEV instance

**/

VOID
InitKeyboardBuffer (
    USB_KB_DEV        *UsbKbd
)
{
    gBS->SetTimer(UsbKbd->TimerEvent, TimerCancel, 0);
    gBS->SetTimer(UsbKbd->KeyRepeatEvent, TimerCancel, 0);
    
    UsbKbd->LastUsbKeyCode = 0;
    UsbKbd->ShiftState = 0;
    UsbKbd->LastToggleState = 0;

    InitKeyBuffer(&UsbKbd->DevInfo->KeyCodeBuffer);
    InitKeyBuffer(&UsbKbd->DevInfo->UsbKeyBuffer);
    InitKeyBuffer(&UsbKbd->EfiKeyBuffer);
    
    gBS->SetTimer(UsbKbd->TimerEvent, TimerPeriodic, USB_KBD_TIMER_INTERVAL);
}

/**
    This function clears USB keyboard buffers

    @param Event    Event that caused this function to be called
    @param Context  Context of the event


**/

VOID
EFIAPI
ClearUsbKbBuffer(
    IN EFI_EVENT    Event, 
    IN VOID         *Context
)
{
    InitKeyboardBuffer((USB_KB_DEV*)Context);

    SetMem(gUsbData->KbcCharacterBufferStart, 
           sizeof(gUsbData->KbcCharacterBufferStart), 0);

    gUsbDataList->KbcCharacterBufferHead = gUsbData->KbcCharacterBufferStart;
    gUsbDataList->KbcCharacterBufferTail = gUsbData->KbcCharacterBufferStart;

    SetMem(gUsbData->KbcScanCodeBufferStart, 
           sizeof(gUsbData->KbcScanCodeBufferStart), 0);

    gUsbDataList->KbcScanCodeBufferPtr = gUsbData->KbcScanCodeBufferStart;

    gBS->CloseEvent(Event);
}

/**
    Initialize USB Keyboard device and all private data structures.

    @param UsbKbd        Pointer to USB_KB_DEV instance

    @retval EFI_SUCCESS   Success to init usb keyboard

**/

EFI_STATUS
InitUsbKeyboard(
    USB_KB_DEV    *UsbKbd
)
{
    REPORT_STATUS_CODE(EFI_PROGRESS_CODE, (EFI_PERIPHERAL_KEYBOARD | EFI_P_KEYBOARD_PC_SELF_TEST));
    gBS->SetTimer(UsbKbd->TimerEvent, TimerCancel, 0);
    gBS->SetTimer(UsbKbd->KeyRepeatEvent, TimerCancel, 0);

    UsbKbd->LastUsbKeyCode = 0;

    UsbKbd->ShiftState = 0;
    UsbKbd->LastToggleState = 0;
    UsbKbd->ToggleState = 0;
    SetLed(UsbKbd);

    InitKeyBuffer(&UsbKbd->DevInfo->KeyCodeBuffer);
    InitKeyBuffer(&UsbKbd->DevInfo->UsbKeyBuffer);
    InitKeyBuffer(&UsbKbd->EfiKeyBuffer);

    gBS->SetTimer(UsbKbd->TimerEvent, TimerPeriodic, USB_KBD_TIMER_INTERVAL);
    
    return EFI_SUCCESS;
}

/**
    Installs SimpleTxtIn protocol on a given handle

    @param This                 Protocol instance pointer.
    @param Controller           Handle of device to test
    @param DevicePath           Optional parameter use to pick a specific child
                                device to start.
    @param DevInfo              Ptr to DEV_INFO
    @param UsbIo                Ptr to EFI_USB_IO_PROTOCOL
    
    @retval EFI_SUCCESS         Success to install USB keyboard


**/

EFI_STATUS
InstallUsbKeyboard (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath,
    DEV_INFO                    *DevInfo,            
    EFI_USB_IO_PROTOCOL         *UsbIo 
)
{
    EFI_STATUS    Status;
    USB_KB_DEV    *UsbKbd;
    CHAR8         UsbKbToken[USB_TOKEN_NAME_SIZE];

    USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HID, "USB: InstallUSBKeyboard: starting...\n");

    REPORT_STATUS_CODE(EFI_PROGRESS_CODE, (EFI_PERIPHERAL_KEYBOARD | EFI_P_PC_INIT));

    Status = gBS->AllocatePool(
                    EfiBootServicesData, 
                    sizeof(USB_KB_DEV), 
                    (VOID**)&UsbKbd
                    );
    if (EFI_ERROR(Status)) {
        REPORT_STATUS_CODE((EFI_ERROR_CODE | EFI_ERROR_MINOR), (EFI_PERIPHERAL_KEYBOARD | EFI_P_EC_CONTROLLER_ERROR));
        return Status;
    }

    SetMem(UsbKbd, sizeof(USB_KB_DEV), 0);

    //
    // Initialize UsbKbd
    //
    UsbKbd->Signature = USB_KB_DEV_SIGNATURE;
    UsbKbd->UsbIo = UsbIo;
    UsbKbd->DevInfo = DevInfo;

    CreateKeyBuffer(&UsbKbd->EfiKeyBuffer, MAX_KEY_ALLOWED, sizeof(AMI_EFI_KEY_DATA));

    Status = gBS->CreateEvent(
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    UsbKbdTimerCallback,
                    UsbKbd,
                    &UsbKbd->TimerEvent);
    ASSERT_EFI_ERROR (Status);

    Status = gBS->CreateEvent(
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    KeyRepeatCallback,
                    UsbKbd,
                    &UsbKbd->KeyRepeatEvent);
    ASSERT_EFI_ERROR (Status);

    SetLed(UsbKbd);
    gBS->SetTimer(UsbKbd->TimerEvent, TimerPeriodic, USB_KBD_TIMER_INTERVAL);

    UsbKbd->SimpleInput.Reset = UsbKbdSimpleInReset;
    UsbKbd->SimpleInput.ReadKeyStroke = UsbKbdSimpleInReadKeyStroke;

    // Setup the WaitForKey event
    //
    Status = gBS->CreateEvent(
                    EVT_NOTIFY_WAIT,
                    TPL_NOTIFY,
                    UsbKbdWaitForKey,
                    UsbKbd,
                    &UsbKbd->SimpleInput.WaitForKey);
    ASSERT_EFI_ERROR(Status);

    UsbKbd->SimpleInputEx.Reset = UsbKbdSimpleInExReset;
    UsbKbd->SimpleInputEx.ReadKeyStrokeEx = UsbKbdSimpleInExReadKeyStrokeEx;
    UsbKbd->SimpleInputEx.SetState = UsbKbdSimpleInExSetState;
    UsbKbd->SimpleInputEx.RegisterKeyNotify = UsbKbdSimpleInExRegisterKeyNotify;
    UsbKbd->SimpleInputEx.UnregisterKeyNotify = UsbKbdSimpleInExUnregisterKeyNotify;

    UsbKbd->KeycodeInput.Reset = UsbKbdKeycodeInReset;
    UsbKbd->KeycodeInput.ReadEfikey = UsbKbdKeycodeInReadEfiKey;
    UsbKbd->KeycodeInput.SetState = UsbKbdKeycodeInSetState;
    UsbKbd->KeycodeInput.RegisterKeyNotify = UsbKbdKeycodeInRegisterKeyNotify;
    UsbKbd->KeycodeInput.UnregisterKeyNotify = UsbKbdKeycodeInUnregisterKeyNotify;

    InitializeListHead(&UsbKbd->KeyNotifyList); 

    Status = gBS->CreateEvent(
                    EVT_NOTIFY_WAIT,
                    TPL_NOTIFY,
                    UsbKbdWaitForKey,
                    UsbKbd,
                    &UsbKbd->SimpleInputEx.WaitForKeyEx);
    ASSERT_EFI_ERROR(Status);

    Status = gBS->CreateEvent(
                    EVT_NOTIFY_WAIT,
                    TPL_NOTIFY,
                    UsbKbdWaitForKey,
                    UsbKbd,
                    &UsbKbd->KeycodeInput.WaitForKeyEx);
    ASSERT_EFI_ERROR(Status);

    if ((gUsbData->UsbFeature & USB_CLEAR_USB_KB_BUFFER_AT_READYTOBOOT) == USB_CLEAR_USB_KB_BUFFER_AT_READYTOBOOT) {
        // Create event on ready to boot to clear KB buffer
        Status = EfiCreateEventReadyToBootEx(
                    TPL_NOTIFY, ClearUsbKbBuffer, 
                    UsbKbd, &UsbKbd->ReadyToBootEvent);
        
        if (EFI_ERROR(Status)) {
            USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HID, "ClearUsbKbBuffer Event %r \n", Status);
        }
    }

    //
    // Install protocol interfaces for the USB keyboard device:
    //
    // Install simple txt in protocol interface
    // for the usb keyboard device.
    // Usb keyboard is a hot plug device, and expected to work immediately
    // when plugging into system, so a HotPlugDeviceGuid is installed onto
    // the usb keyboard device handle, to distinguish it from other conventional
    // console devices.
    //
    Status = gBS->InstallMultipleProtocolInterfaces(&Controller,
                    &gEfiSimpleTextInProtocolGuid, &UsbKbd->SimpleInput,
                    &gEfiSimpleTextInputExProtocolGuid, &UsbKbd->SimpleInputEx,
                    &gAmiEfiKeycodeProtocolGuid, &UsbKbd->KeycodeInput,
                    NULL
                    );

    ASSERT_EFI_ERROR (Status);

    USB_DEBUG(DEBUG_DEV_INIT|DEBUG_HID, "USB: InstallUSBKeyboard: done (%x).\n", Status);

    // Init Detect Usb Keyboard token
    AsciiSPrintUnicodeFormat(UsbKbToken, USB_TOKEN_NAME_SIZE, L"DetectUsbKb:0x%X/0x%X", DevInfo->VendorId, DevInfo->DeviceId);

    // PERF_START
    AmiUsbPerfStart(NULL, UsbKbToken, "AmiUsb", DevInfo->DetectStartTime);

    // PERF_END
    AmiUsbPerfEnd(NULL, UsbKbToken, "AmiUsb", DevInfo->DetectEndTime);

    // Init Config Usb Keyboard token
    AsciiSPrintUnicodeFormat(UsbKbToken, USB_TOKEN_NAME_SIZE, L"ConfigUsbKb:0x%X/0x%X", DevInfo->VendorId, DevInfo->DeviceId);

    // PERF_START
    AmiUsbPerfStart(NULL, UsbKbToken, "AmiUsb", DevInfo->ConfigStartTime);

    // PERF_END
    AmiUsbPerfEnd(NULL, UsbKbToken, "AmiUsb", 0);

  
    if (Status != EFI_SUCCESS) {
      REPORT_STATUS_CODE((EFI_ERROR_CODE | EFI_ERROR_MINOR), (EFI_PERIPHERAL_KEYBOARD | EFI_P_EC_CONTROLLER_ERROR));  
    }
    return Status;
}
                                        //<(EIP38434+)

/**
    Uninstalls SimpleTxtIn protocol on a given handle

    @param This                Pointer to driver binding protocol
    @param Controller          Controller handle.
    @param NumberOfChildren    Number of children in driver binding
    @param Children            Pointer to children handle
            
    @retval EFI_SUCCESS        Success to uninstall USB keyboard

**/

EFI_STATUS
UninstallUsbKeyboard (
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE                  Controller,
    UINTN                       NumberOfChildren,
    EFI_HANDLE                  *Children
)
{
    EFI_STATUS            Status;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL      *SimpleIn = NULL;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   *SimpleInEx = NULL;
    USB_KB_DEV            *UsbKbd = NULL;
    LIST_ENTRY            *Link = NULL;
    KEY_NOTIFY_LINK       *NotifyLink = NULL;

    Status = gBS->OpenProtocol(Controller,
                    &gEfiSimpleTextInProtocolGuid,
                    (VOID**)&SimpleIn,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = gBS->OpenProtocol(Controller,
                    &gEfiSimpleTextInputExProtocolGuid,
                    (VOID**)&SimpleInEx,
                    This->DriverBindingHandle,
                    Controller,
                    EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    REPORT_STATUS_CODE(EFI_PROGRESS_CODE, (EFI_PERIPHERAL_KEYBOARD | EFI_P_PC_DISABLE));
    
    UsbKbd = USB_KB_DEV_FROM_THIS(SimpleInEx, SimpleInputEx);

    gBS->SetTimer(UsbKbd->TimerEvent, TimerCancel, 0);
    gBS->SetTimer(UsbKbd->KeyRepeatEvent, TimerCancel, 0);

    //
    // Uninstall protocol interfaces for the USB keyboard device
    //
    Status = gBS->UninstallMultipleProtocolInterfaces ( 
                    Controller,
                    &gEfiSimpleTextInProtocolGuid, &UsbKbd->SimpleInput,
                    &gEfiSimpleTextInputExProtocolGuid,&UsbKbd->SimpleInputEx,
                    &gAmiEfiKeycodeProtocolGuid,&UsbKbd->KeycodeInput,
                    NULL
                    );
    
    if (EFI_ERROR(Status)) {
        return Status;
    }

    
    //
    // Close all the event that created in Start()
    //
    gBS->CloseEvent (UsbKbd->TimerEvent);
    gBS->CloseEvent (UsbKbd->KeyRepeatEvent);
    gBS->CloseEvent (UsbKbd->SimpleInput.WaitForKey);
    gBS->CloseEvent (UsbKbd->SimpleInputEx.WaitForKeyEx);
    gBS->CloseEvent (UsbKbd->KeycodeInput.WaitForKeyEx);


    for (Link = UsbKbd->KeyNotifyList.ForwardLink; Link != &UsbKbd->KeyNotifyList; ) {       	
       NotifyLink = BASE_CR(Link, KEY_NOTIFY_LINK, Link);
       Link = RemoveEntryList(&NotifyLink->Link);
       gBS->CloseEvent(NotifyLink->NotifyEvent);
       gBS->FreePool(NotifyLink);
    }
    
    if ((gUsbData->UsbFeature & USB_CLEAR_USB_KB_BUFFER_AT_READYTOBOOT) == 
    	USB_CLEAR_USB_KB_BUFFER_AT_READYTOBOOT) {
        gBS->CloseEvent(UsbKbd->ReadyToBootEvent);
    }

    DestroyKeyBuffer(&UsbKbd->EfiKeyBuffer);

    gBS->FreePool(UsbKbd);

    return Status;
}

/**
    This function reads EFI key data from key buffer

    @param UsbKbd    Pointer to USB_KB_DEV
    @param Key       Pointer to key
    @param KeySize   Size of the structure.

    @retval EFI_SUCCESS        Success to read efi key

**/

EFI_STATUS 
ReadEfiKey (
    USB_KB_DEV    *UsbKbd,
    VOID          *Key,
    UINT8         KeySize
)
{
    EFI_STATUS              Status = EFI_NOT_READY;
    static BOOLEAN          InProgress = FALSE;
    AMI_EFI_KEY_DATA        EfiKey;


    if (InProgress) return EFI_NOT_READY;
    InProgress = TRUE;

    if (!(UsbKbd->DevInfo->Flag & DEV_INFO_DEV_PRESENT)) {
        InProgress = FALSE;
        return EFI_DEVICE_ERROR;
    }
    
    SetMem(&EfiKey, sizeof(AMI_EFI_KEY_DATA), 0);
    
    if (IsKeyBufferEmpty(&UsbKbd->EfiKeyBuffer) && 
        EFI_ERROR(ProcessUsbKey(UsbKbd))) {
        if (UsbKbd->ShiftState != 0) {
            if(IsKeyBufferEmpty(&UsbKbd->EfiKeyBuffer) && (EfiKey.Key.UnicodeChar == 0) && (EfiKey.Key.ScanCode == SCAN_NULL)) {
                InProgress = FALSE;
                return EFI_NOT_READY;
            }
            EfiKey.KeyState.KeyShiftState = 
                UsbKbd->ShiftState | EFI_SHIFT_STATE_VALID;
            EfiKey.KeyState.KeyToggleState = 
                UsbKbd->ToggleState | EFI_TOGGLE_STATE_VALID;
            Status = EFI_SUCCESS;
        }
    } else {
        GetKey(&UsbKbd->EfiKeyBuffer, &EfiKey);
        EfiKey.EfiKeyIsValid = 1;
        EfiKey.PS2ScanCodeIsValid = 1;
        EfiKey.KeyState.KeyToggleState = 
                UsbKbd->ToggleState | EFI_TOGGLE_STATE_VALID;
        Status = EFI_SUCCESS;
    }

    if (!EFI_ERROR(Status)) {
        if ((EfiKey.Key.UnicodeChar == 0) && (EfiKey.Key.ScanCode == SCAN_NULL) &&
            (EfiKey.KeyState.KeyShiftState & ~EFI_SHIFT_STATE_VALID)) {
            // If the Key ShiftState has valid key but KEY_STATE_EXPOSED bit not enabled,
            // don't insert key into buffer
            if (!(EfiKey.KeyState.KeyToggleState & EFI_KEY_STATE_EXPOSED)) {
                InProgress = FALSE;
                return EFI_UNSUPPORTED;
            }
        }
        CopyMem(Key, &EfiKey, KeySize);
    }

    InProgress = FALSE;
    return Status; 
}


/***********************************************************************/
/*                                                                     */
/*            SimpleTextIn Protocol implementation routines            */
/*                                                                     */
/***********************************************************************/

/**
    Reset USB keyboard

    @param This                  Pointer to EFI_SIMPLE_TEXT_INPUT_PROTOCOL
    @param ExtendedVerification  Extended verification
    
    @retval EFI_SUCCESS          Success to reset Usb keyboard

**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInReset(
    IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
    IN  BOOLEAN                         ExtendedVerification
)
{
    EFI_STATUS	Status;
    USB_KB_DEV	*UsbKbd;
    EFI_TPL     OldTpl;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInput);

    if (!(UsbKbd->DevInfo->Flag & DEV_INFO_DEV_PRESENT)) {
        gBS->RestoreTPL(OldTpl);
        return EFI_DEVICE_ERROR;
    }
    
    //
    // Non Exhaustive reset: only reset private data structures.
    //
    if (!ExtendedVerification) {
        InitKeyboardBuffer(UsbKbd);
        gBS->RestoreTPL(OldTpl);
        return EFI_SUCCESS;
    }

    //
    // Exhaustive reset
    //
    Status = InitUsbKeyboard(UsbKbd);

    gBS->RestoreTPL(OldTpl);

    return Status;
}


/**
    Retrieves the key stroke from the keyboard buffer.

    @param This                  Pointer to EFI_SIMPLE_TEXT_INPUT_PROTOCOL
    @param Key                   Pointer to EFI_INPUT_KEY
    
    @retval EFI_SUCCESS          Success to read key stroke

**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInReadKeyStroke(
    IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
    OUT EFI_INPUT_KEY                   *Key
)
{
    EFI_STATUS	        Status;
    USB_KB_DEV	        *UsbKbd;
    EFI_TPL             OldTpl;
    AMI_EFI_KEY_DATA    EfiKey;

    SetMem(&EfiKey, sizeof(AMI_EFI_KEY_DATA), 0);
    
    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInput);

    Status = ReadEfiKey(UsbKbd, &EfiKey, sizeof(EfiKey));
    
    if ((EfiKey.Key.UnicodeChar == 0) && (EfiKey.Key.ScanCode == SCAN_NULL) &&
        (EfiKey.KeyState.KeyToggleState & EFI_KEY_STATE_EXPOSED)) {
        gBS->RestoreTPL(OldTpl);
        return EFI_NOT_READY;
    }

    if (!EFI_ERROR(Status)) {
        CopyMem(Key, &EfiKey, sizeof(EFI_INPUT_KEY));
    }

    gBS->RestoreTPL(OldTpl);

    return Status;
}


/**
    Reset USB keyboard

    @param This                  Pointer to EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
    @param ExtendedVerification  Extended verification
    
    @retval EFI_SUCCESS          Success to reset Usb keyboard

**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInExReset(
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
  IN  BOOLEAN                             ExtendedVerification
)
{
    USB_KB_DEV    *UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInputEx);
    return UsbKbdSimpleInReset(&UsbKbd->SimpleInput, ExtendedVerification);
}


/**
    Retrieves the key stroke from the keyboard buffer.


    @param This                  Pointer to EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
    @param KeyData               Pointer to EFI_KEY_DATA
    
    @retval EFI_SUCCESS          Success to read key stroke

**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInExReadKeyStrokeEx(
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
  OUT EFI_KEY_DATA                         *KeyData
)
{
    USB_KB_DEV	    *UsbKbd;
    EFI_STATUS      Status;
    EFI_TPL         OldTpl;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInputEx);

    if (KeyData == NULL) {
        gBS->RestoreTPL(OldTpl);
        return EFI_INVALID_PARAMETER;
    }
    
    Status = ReadEfiKey(UsbKbd, KeyData, sizeof(EFI_KEY_DATA));

    
    if (EFI_ERROR(Status)){
        if (Status == EFI_DEVICE_ERROR) {
            gBS->RestoreTPL(OldTpl);
            return Status;
        }
        Status = EFI_NOT_READY;
        SetMem(KeyData, sizeof(EFI_KEY_DATA), 0);
        KeyData->KeyState.KeyShiftState  = UsbKbd->ShiftState | EFI_SHIFT_STATE_VALID;
        KeyData->KeyState.KeyToggleState = UsbKbd->ToggleState | EFI_TOGGLE_STATE_VALID;
    }

    gBS->RestoreTPL(OldTpl);

    return Status;    
}

/**
    Set certain state for the input device.

    @param This             A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
                            instance.
    @param KeyToggleState   Pointer to the EFI_KEY_TOGGLE_STATE to
                            set the state for the input device.

    @retval EFI_SUCCESS          Success to set state
**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInExSetState(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_TOGGLE_STATE                    *KeyToggleState
)
{
    USB_KB_DEV           *UsbKbd;
    EFI_KEY_TOGGLE_STATE ToggleState = 0;
    EFI_TPL              OldTpl;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInputEx);

    if ((KeyToggleState == NULL)) {
        gBS->RestoreTPL(OldTpl);
        return EFI_INVALID_PARAMETER;
    }

    if (!(*KeyToggleState & EFI_TOGGLE_STATE_VALID)) {
        gBS->RestoreTPL(OldTpl);
        return EFI_UNSUPPORTED;
    }

    ToggleState = *KeyToggleState & (EFI_SCROLL_LOCK_ACTIVE | EFI_NUM_LOCK_ACTIVE | EFI_CAPS_LOCK_ACTIVE);

    if (*KeyToggleState & EFI_KEY_STATE_EXPOSED) {
        ToggleState |= EFI_KEY_STATE_EXPOSED;
    } else {
        ToggleState &= ~EFI_KEY_STATE_EXPOSED;
    }

    if (UsbKbd->ToggleState == ToggleState) {
        gBS->RestoreTPL(OldTpl);
        return EFI_SUCCESS;
    }

    //
    // Set the new modifier's state only if the requested state is different from the
    // current one.
    //
    UsbKbd->ToggleState = ToggleState;
    SetLed(UsbKbd);

    gBS->RestoreTPL(OldTpl);
 
    return EFI_SUCCESS;

}


/**
    Installs a callback notification function on a key

    @param This      A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX instance.
    @param KeyData   A pointer to a buffer that is filled in with the keystroke information 
                     for the key that was pressed. 
                     If KeyData.Key, KeyData.KeyState.KeyToggleState and KeyData.KeyState.
                     KeyShiftState are 0, then any incomplete keystroke will trigger a 
                     notification of the KeyNotificationFunction. 
    @param KeyNotificationFunction  Pointer to the Notification Function
    @param NotificationHandle       Handle to be unregisterd

    @retval EFI_SUCCESS    Key notify was registered successfully.
    @retval EFI_ERROR      Key notify was registered unsuccessfully.

**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInExRegisterKeyNotify(
    IN    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN    EFI_KEY_DATA                         *KeyData,
    IN    EFI_KEY_NOTIFY_FUNCTION              KeyNotificationFunction,
    OUT    EFI_HANDLE                          *NotifyHandle
)
{
    EFI_STATUS		Status = EFI_INVALID_PARAMETER;
    USB_KB_DEV		*UsbKbd;
    LIST_ENTRY          *Link = NULL;
    KEY_NOTIFY_LINK	*NotifyLink = NULL;
    EFI_TPL             OldTpl;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInputEx);
    
    if (KeyData == NULL || KeyNotificationFunction == NULL || NotifyHandle == NULL ) {
        gBS->RestoreTPL(OldTpl);
        return EFI_INVALID_PARAMETER;
    }

    // Check if the key has been reistered
    for (Link = UsbKbd->KeyNotifyList.ForwardLink;
        Link != &UsbKbd->KeyNotifyList; 
        Link = Link->ForwardLink ) {
        NotifyLink = BASE_CR(Link, KEY_NOTIFY_LINK, Link);
        if (CompareMem(&NotifyLink->KeyData, KeyData, sizeof(EFI_KEY_DATA)) == 0 &&
            NotifyLink->NotifyFunction == KeyNotificationFunction) {
            *NotifyHandle = (EFI_HANDLE)(&NotifyLink->Link);
            gBS->RestoreTPL(OldTpl);
            return EFI_SUCCESS;
        }        
    }
    
    //
    // Create database record and add to database
    //
    Status = gBS->AllocatePool(EfiBootServicesData, 
                    sizeof (KEY_NOTIFY_LINK), (VOID**)&NotifyLink);
    if (EFI_ERROR(Status)) {
        gBS->RestoreTPL(OldTpl);
        return Status;
    }

    SetMem(NotifyLink, sizeof (KEY_NOTIFY_LINK), 0);

    //
    // Gather information about the registration request
    //
    CopyMem(&NotifyLink->KeyData, KeyData, sizeof(NotifyLink->KeyData));
    NotifyLink->NotifyFunction = KeyNotificationFunction;

    Status = gBS->CreateEvent(
                    EVT_NOTIFY_SIGNAL, 
                    TPL_CALLBACK,
                    UsbKeyNotifyCallback, 
                    NotifyLink, 
                    &NotifyLink->NotifyEvent
                    );
    ASSERT_EFI_ERROR(Status);
    if (EFI_ERROR(Status)) {
        gBS->FreePool(NotifyLink);
        gBS->RestoreTPL(OldTpl);
        return Status;
    }

    InsertTailList(&UsbKbd->KeyNotifyList, &(NotifyLink->Link));

    //
    // Child's handle will be the address linked list link in the record
    //
    *NotifyHandle = (EFI_HANDLE)(&NotifyLink->Link);

    gBS->RestoreTPL(OldTpl);

    return EFI_SUCCESS;
}


/**
    Remove the notification which was previously registered.

    @param This                 A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX 
                                instance.
    @param NotificationHandle   Handle to be unregisterd

    @retval EFI_SUCCESS   Key notify was registered successfully.
    @retval EFI_ERROR     Key notify was registered unsuccessfully.

**/

EFI_STATUS
EFIAPI
UsbKbdSimpleInExUnregisterKeyNotify (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_HANDLE                            NotificationHandle
)
{
    USB_KB_DEV		*UsbKbd;
    LIST_ENTRY          *Link = NULL;
    KEY_NOTIFY_LINK     *NotifyLink = NULL;
    EFI_TPL             OldTpl;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, SimpleInputEx);

    if (NotificationHandle == NULL) {
        gBS->RestoreTPL(OldTpl);
        return EFI_INVALID_PARAMETER;
    }

    for (Link = UsbKbd->KeyNotifyList.ForwardLink;
        Link != &UsbKbd->KeyNotifyList; 
        Link = Link->ForwardLink ) {
        NotifyLink = BASE_CR(Link, KEY_NOTIFY_LINK, Link);
        if ((&NotifyLink->Link) == NotificationHandle) {
            RemoveEntryList(&NotifyLink->Link);
            gBS->CloseEvent(NotifyLink->NotifyEvent);
            gBS->FreePool(NotifyLink);
            gBS->RestoreTPL(OldTpl);
            return EFI_SUCCESS;
        }
    }
    gBS->RestoreTPL(OldTpl);

    return EFI_INVALID_PARAMETER;
}


/**
    Retrieves the key stroke from the keyboard buffer.

    @param This              Pointer to EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
    @param KeyData           Pointer to EFI_KEY_DATA

    @retval EFI_SUCCESS      Success to read key stroke form buffer

**/

EFI_STATUS
EFIAPI
UsbKbdKeycodeInReadEfiKey(
    IN    AMI_EFIKEYCODE_PROTOCOL       *This,
    OUT   AMI_EFI_KEY_DATA              *KeyData
)
{
    USB_KB_DEV      *UsbKbd;
    EFI_TPL         OldTpl;
    EFI_STATUS      Status;

    OldTpl = gBS->RaiseTPL(TPL_NOTIFY);

    UsbKbd = USB_KB_DEV_FROM_THIS(This, KeycodeInput);

    if (KeyData == NULL) {
        gBS->RestoreTPL(OldTpl);
        return EFI_INVALID_PARAMETER;
    }

    Status = ReadEfiKey(UsbKbd, KeyData, sizeof(AMI_EFI_KEY_DATA));

    if (EFI_ERROR(Status)){
        if (Status == EFI_DEVICE_ERROR) {
            gBS->RestoreTPL(OldTpl);
            return Status;
        }
        Status = EFI_NOT_READY;
        SetMem(KeyData, sizeof(EFI_KEY_DATA), 0);
        KeyData->KeyState.KeyShiftState  = UsbKbd->ShiftState | EFI_SHIFT_STATE_VALID;
        KeyData->KeyState.KeyToggleState = UsbKbd->ToggleState | EFI_TOGGLE_STATE_VALID;
    }

    gBS->RestoreTPL(OldTpl);
    
    return Status;
}

/**
    Reset USB keyboard
    
    @param This                  Pointer to EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL
    @param ExtendedVerification  Extended verification
    
    @retval EFI_SUCCESS          Success to reset USB keyboard.

**/
EFI_STATUS
EFIAPI
UsbKbdKeycodeInReset(
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN  BOOLEAN     			ExtendedVerification
)
{
    AMI_EFIKEYCODE_PROTOCOL    *AmiKeyCode = (AMI_EFIKEYCODE_PROTOCOL*)This;
    USB_KB_DEV    *UsbKbd = USB_KB_DEV_FROM_THIS(AmiKeyCode, KeycodeInput);
    return UsbKbdSimpleInReset(&UsbKbd->SimpleInput, ExtendedVerification);
}

/**
    Set certain state for the input device.

    @param This            A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
                           instance.
    @param KeyToggleState  Pointer to the EFI_KEY_TOGGLE_STATE to
                           set the state for the input device.

    @retval EFI_SUCCESS    Success to set state

**/

EFI_STATUS
EFIAPI
UsbKbdKeycodeInSetState(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN EFI_KEY_TOGGLE_STATE 	*KeyToggleState
)
{
    AMI_EFIKEYCODE_PROTOCOL *AmiKeyCode;
    USB_KB_DEV              *UsbKbd = NULL;

    if (This == NULL) return EFI_INVALID_PARAMETER;

    AmiKeyCode = (AMI_EFIKEYCODE_PROTOCOL*)This;
    UsbKbd = USB_KB_DEV_FROM_THIS(AmiKeyCode, KeycodeInput);

    return UsbKbdSimpleInExSetState(&UsbKbd->SimpleInputEx, KeyToggleState);
}

/**
    Installs a callback notification function on a key

    @param This    A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
                   instance.
    @param KeyData Key value
    @param KeyNotificationFunction  Pointer to the Notification Function
    @param NotificationHandle       Handle to be unregisterd

    @retval EFI_SUCCESS    Success to register key notify.

**/

EFI_STATUS
EFIAPI
UsbKbdKeycodeInRegisterKeyNotify(
    IN    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
    IN    EFI_KEY_DATA                      *KeyData,
    IN    EFI_KEY_NOTIFY_FUNCTION           KeyNotificationFunction,
    OUT   EFI_HANDLE                        *NotifyHandle
)
{
    AMI_EFIKEYCODE_PROTOCOL *AmiKeyCode = (AMI_EFIKEYCODE_PROTOCOL*)This;
    USB_KB_DEV    *UsbKbd = USB_KB_DEV_FROM_THIS (AmiKeyCode, KeycodeInput);
    
    return UsbKbdSimpleInExRegisterKeyNotify(
             &UsbKbd->SimpleInputEx, 
             KeyData, 
             KeyNotificationFunction, 
             NotifyHandle
             );
}

/**
    Uninstalls a callback notification function on a key

    @param This   A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL_EX
                  instance.
    @param NotificationHandle  Handle to be unregisterd

    @retval EFI_SUCCESS    Success to unregister key notify.

**/

EFI_STATUS
EFIAPI
UsbKbdKeycodeInUnregisterKeyNotify(
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_HANDLE                           NotificationHandle
)
{
    AMI_EFIKEYCODE_PROTOCOL *AmiKeyCode = (AMI_EFIKEYCODE_PROTOCOL*)This;
    USB_KB_DEV    *UsbKbd = USB_KB_DEV_FROM_THIS (AmiKeyCode, KeycodeInput);
    return UsbKbdSimpleInExUnregisterKeyNotify(
             &UsbKbd->SimpleInputEx, NotificationHandle);
}


/**
    Checks if a key is pending, if so - signals the event.

    @param  Event       Efi event occurred upon Usb key event
    @param  Context     Ptr to USB_KB_DEV

**/

VOID
EFIAPI
UsbKbdWaitForKey (
    IN  EFI_EVENT   Event,
    IN  VOID        *Context
    )
{
    USB_KB_DEV   *UsbKbd;
    EFI_TPL      OldTpl;
    AMI_EFI_KEY_DATA    EfiKey;
    KEY_BUFFER          *KeyBuffer;

    SetMem(&EfiKey, sizeof(AMI_EFI_KEY_DATA), 0);
    
    OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

    UsbKbd = (USB_KB_DEV*)Context;

    if (!(UsbKbd->DevInfo->Flag & DEV_INFO_DEV_PRESENT)) {
        gBS->RestoreTPL(OldTpl);
        return;
    }

    if (IsKeyBufferEmpty(&UsbKbd->EfiKeyBuffer) && 
        EFI_ERROR(ProcessUsbKey(UsbKbd))) {
        gBS->RestoreTPL(OldTpl);
        return;
    }
    
    // An Event will only be triggered if EfiKey.Key has information contained 
    // within it for EFI_SIMPLE_TEXT_INPUT_PROTOCOL WaitforKey.
    if (Event == UsbKbd->SimpleInput.WaitForKey) {
        
        KeyBuffer = &UsbKbd->EfiKeyBuffer;

        if ((KeyBuffer == NULL) || (KeyBuffer->Buffer == NULL)) {
            gBS->RestoreTPL(OldTpl);
            return;
        }
        
        if (KeyBuffer->Tail == KeyBuffer->Head) {
            gBS->RestoreTPL(OldTpl);
            return;
        }
        
        CopyMem(&EfiKey, KeyBuffer->Buffer[KeyBuffer->Tail], KeyBuffer->KeySize);
        
        //There maybe a partial keystroke in the queue, the event shouldn't be signaled 
        // when partial key stroke is detected and dequeue this partial keystroke.
        if ((EfiKey.Key.UnicodeChar == 0) && (EfiKey.Key.ScanCode == SCAN_NULL)
            && (EfiKey.KeyState.KeyToggleState & EFI_KEY_STATE_EXPOSED)) {
            KeyBuffer->Tail = ((KeyBuffer->Tail + 1) % KeyBuffer->MaxKey);
            gBS->RestoreTPL(OldTpl);
            return;
        }
    }

    //
    // If has key pending, signal the event.
    //
    gBS->SignalEvent(Event);

    gBS->RestoreTPL(OldTpl);
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
