//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SysNoKbc.c
    AMI USB keyboard driver data conversion and presentation
    routines, KBC is not present

**/


#include "AmiUsb.h"
#include "UsbKbd.h"
#include <Library/AmiUsbHcdLib.h>


#if KEYMONFILTER_SUPPORT
#include <Protocol/KeyMonPlatform.h>
#define     KEYMON_MAP              0x108
#define     KEYMON_DATA_ADDRESS     0x10C    
#endif

VOID UpdateKeyMon(UINT8 KeyCode);  

extern LEGACY_USB_KEYBOARD mLegacyKeyboard;
extern USB_GLOBAL_DATA *gUsbData;
extern UINT8 aTypematicRateDelayTable[];
extern USB_DATA_LIST   *gUsbDataList;

VOID UpdateLEDs();

//
// USB scan codes and the corresponding data that will be used during key translation
//
/*
0,  //0 00 Reserved (no event indicated)
0,  //1 01 Keyboard ErrorRollOver
0,  //2 02 Keyboard POSTFail
0,  //3 03 Keyboard ErrorUndefined
*/
UINT8 aLetters[] = {
    0x1e,   //4 04 Keyboard a and A
    0x30,   //5 05 Keyboard b and B
    0x2e,   //6 06 Keyboard c and C
    0x20,   //7 07 Keyboard d and D
    0x12,   //8 08 Keyboard e and E
    0x21,   //9 09 Keyboard f and F
    0x22,   //10 0A Keyboard g and G
    0x23,   //11 0B Keyboard h and H
    0x17,   //12 0C Keyboard i and I
    0x24,   //13 0D Keyboard j and J
    0x25,   //14 0E Keyboard k and K
    0x26,   //15 0F Keyboard l and L
    0x32,   //16 10 Keyboard m and M
    0x31,   //17 11 Keyboard n and N
    0x18,   //18 12 Keyboard o and O
    0x19,   //19 13 Keyboard p and P
    0x10,   //20 14 Keyboard q and Q
    0x13,   //21 15 Keyboard r and R
    0x1f,   //22 16 Keyboard s and S
    0x14,   //23 17 Keyboard t and T
    0x16,   //24 18 Keyboard u and U
    0x2f,   //25 19 Keyboard v and V
    0x11,   //26 1A Keyboard w and W
    0x2d,   //27 1B Keyboard x and X
    0x15,   //28 1C Keyboard y and Y
    0x2c,   //29 1D Keyboard z and Z
};

struct TNumbers {
    UINT8   NormalNumber;
    UINT8   ShiftedNumber;
} aNumbers[] = {
    {0x31, 0x21}, //30 1E Keyboard 1 and !
    {0x32, 0x40}, //31 1F Keyboard 2 and @
    {0x33, 0x23}, //32 20 Keyboard 3 and #
    {0x34, 0x24}, //33 21 Keyboard 4 and $
    {0x35, 0x25}, //34 22 Keyboard 5 and %
    {0x36, 0x5e}, //35 23 Keyboard 6 and ^
    {0x37, 0x26}, //36 24 Keyboard 7 and &
    {0x38, 0x2a}, //37 25 Keyboard 8 and *
    {0x39, 0x28}, //38 26 Keyboard 9 and (
    {0x30, 0x29}, //39 27 Keyboard 0 and )
};

struct TBasicKeys {
    UINT8 BasicKeyScancode;
    UINT8 BasicKeyAsciiNormal;
    UINT8 BasicKeyAsciiShifted;
    UINT16 BasicKeyCodeCtrl;
    UINT8 BasicKeyAsciiAlt;
} aBasicKey[] = {
    {0x1c, 0x0d, 0x0d, 0x1c0a, 0xa6}, //40 28 Keyboard Return (ENTER)
    {0x01, 0x1b, 0x1b, 0x011b, 0x01}, //41 29 Keyboard ESCAPE
    {0x0e, 0x08, 0x08, 0x0e7f, 0x0e}, //42 2A Keyboard DELETE (Backspace)
    {0x0f, 0x09, 0x00, 0x9400, 0xa5}, //43 2B Keyboard Tab
    {0x00, 0x00, 0x00, 0x0000, 0x00}, //44 2C Keyboard Spacebar, processed separately
    {0x0c, 0x2d, 0x5f, 0x0c1f, 0x82}, //45 2D Keyboard - and (underscore
    {0x0d, 0x3d, 0x2b, 0x0000, 0x83}, //46 2E Keyboard = and +
    {0x1a, 0x5b, 0x7b, 0x1a1b, 0x1a}, //47 2F Keyboard [ and {
    {0x1b, 0x5d, 0x7d, 0x1b1d, 0x1b}, //48 30 Keyboard ] and }
    {0x2b, 0x5c, 0x7c, 0x2b1c, 0x26}, //49 31 Keyboard \ and |
    {0x2b, 0x5c, 0x7c, 0x2b1c, 0x26}, //50 32 Keyboard Non-US # and ~
    {0x27, 0x3b, 0x3a, 0x0000, 0x27}, //51 33 Keyboard ; and :
    {0x28, 0x27, 0x22, 0x0000, 0x00}, //52 34 Keyboard ` and "
    {0x29, 0x60, 0x7e, 0x0000, 0x00}, //53 35 Keyboard Grave Accent and Tilde
    {0x33, 0x2c, 0x3c, 0x0000, 0x00}, //54 36 Keyboard, and <
    {0x34, 0x2e, 0x3e, 0x0000, 0x00}, //55 37 Keyboard . and >
    {0x35, 0x2f, 0x3f, 0x0000, 0x00}, //56 38 Keyboard / and ?
};
/*
//0x0000,   //57 39 Keyboard Caps Lock
*/
UINT8 aF1_10Key[] = {
    0x3b,   //58 3A Keyboard F1
    0x3c,   //59 3B Keyboard F2
    0x3d,   //60 3C Keyboard F3
    0x3e,   //61 3D Keyboard F4
    0x3f,   //62 3E Keyboard F5
    0x40,   //63 3F Keyboard F6
    0x41,   //64 40 Keyboard F7
    0x42,   //65 41 Keyboard F8
    0x43,   //66 42 Keyboard F9
    0x44,   //67 43 Keyboard F10
};
/*
0x85,   //68 44 Keyboard F11
0x86,   //69 45 Keyboard F12


0x00,   //70 46 Keyboard PrintScreen
0x00,   //71 47 Keyboard Scroll Lock
0x00,   //72 48 Keyboard Pause
*/
/* apparently the PS/2's int9 implementation returns the same
scan/ascii for extended keys, keeping the table below for
reference only.
struct TExtKeys {
    UINT8   NormalShiftedScanCode;
    UINT8   ShiftedAsciiCode;
    UINT8   wCtrlScanCode;
    UINT8   wAltScanCode;
} aExtKeys[] = {
    0x52, 0x30, 0x92, 0xA2, //73 49 Keyboard Insert
    0x47, 0x37, 0x77, 0x97, //74 4A Keyboard Home
    0x49, 0x39, 0x84, 0x99, //75 4B Keyboard PageUp
    0x53, 0x2e, 0x93, 0xA3, //76 4C Keyboard Delete Forward
    0x4f, 0x31, 0x75, 0x9F, //77 4D Keyboard End
    0x51, 0x33, 0x76, 0xA1, //78 4E Keyboard PageDown
    0x4d, 0x36, 0x74, 0x9D, //79 4F Keyboard RightArrow
    0x4b, 0x34, 0x73, 0x9B, //80 50 Keyboard LeftArrow
    0x50, 0x32, 0x91, 0xA0, //81 51 Keyboard DownArrow
    0x48, 0x38, 0x8D, 0x98, //82 52 Keyboard UpArrow
};
*/
UINT8 aExtKeys[] = {0x52,0x47,0x49,0x53,0x4f,0x51,0x4d,0x4b,0x50,0x48,};
/*
0x, //83 53 Keypad Num Lock and Clear
*/

UINT16 aKeypad1[] = {
    0x352f, //84 54 Keypad /
    0x372a, //85 55 Keypad *
    0x4a2d, //86 56 Keypad -
    0x4e2b, //87 57 Keypad +
    0x1c0d, //88 58 Keypad ENTER
};

struct TKeypadNumbers {
    UINT8 NormalScanCode;   // ascii code is 0
    UINT8 ShiftedAsciiCode; // altered by both NumLock and Shift
    UINT8 CtrlScanCode;     // ascii code is 0
    UINT8 AltScanCode;      // ascii code is 0
} aKeypad2[] = {
    {0x4f, 0x31, 0x75, 0x9f}, //89 59 Keypad 1 and End
    {0x50, 0x32, 0x91, 0xa0}, //90 5A Keypad 2 and Down Arrow
    {0x51, 0x33, 0x76, 0xa1}, //91 5B Keypad 3 and PageDn
    {0x4b, 0x34, 0x73, 0x9b}, //92 5C Keypad 4 and Left Arrow
    {0x4c, 0x35, 0x8f, 0x00}, //93 5D Keypad 5 (special, no code if lowercase)
    {0x4d, 0x36, 0x74, 0x9d}, //94 5E Keypad 6 and Right Arrow
    {0x47, 0x37, 0x77, 0x97}, //95 5F Keypad 7 and Home
    {0x48, 0x38, 0x8d, 0x98}, //96 60 Keypad 8 and Up Arrow
    {0x49, 0x39, 0x84, 0x99}, //97 61 Keypad 9 and PageUp
    {0x52, 0x30, 0x92, 0xa2}, //98 62 Keypad 0 and Insert
    {0x53, 0x2e, 0x93, 0xa3}, //99 63 Keypad . and Delete
};
/*
0x, //100 64 Keyboard Non-US \ and |
0x, //101 65 Keyboard Application
*/

typedef UINT16 (*GETCODE_FUNC) (UINT8 usbcode);


/**
    Returns the scan/ascii code for letter charachters, USB
    code from 4 to 1D.
    Keys from 'A' to 'Z' are interpreted using the following logic:
    1) first_keycode is 04
    2) last_keycode is 1D
    3) scan_code = letters[key-first_keycode].scancode
    4) ascii_code (normal) = 0x61+(key-first_keycode)
    5) ascii_code (shifted) = 0x41+(key-first_keycode)
    6) ascii_code (w/Ctrl) = key-first_keycode+1

    @param UsbCode                Key index (key code - 4)

    @retval ScanCodeAsciiCode     scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_Letter(UINT8 UsbCode)
{
    UINT8 ScanCode = aLetters[UsbCode];
    UINT8 AsciiCode = 0x61 + UsbCode;
    BOOLEAN ChangeCase = mLegacyKeyboard.KeyModifierState.CapsLock
        || mLegacyKeyboard.KeyModifierState.Shift;

    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(ScanCode);

    if (mLegacyKeyboard.KeyModifierState.CapsLock
        && mLegacyKeyboard.KeyModifierState.Shift) ChangeCase = FALSE;
    if (ChangeCase) AsciiCode -= 0x20;
    if (mLegacyKeyboard.KeyModifierState.Ctrl) AsciiCode = UsbCode+1;
    return (UINT16)(ScanCode << 8) + AsciiCode;
}


/**
    Returns the scan/ascii code for numbers, USB code from 1E to 27.
    Keys from '1' to '0' are interpreted using the following logic:
    1) first_keycode is 1E
    2) last_keycode is 27
    3) scan_code = key-first_keycode + 2
    4) ascii_code (normal) = aNumbers[key-first_keycode].NormalNumber
    5) ascii_code (shifted) = aNumbers[key-first_keycode].ShiftedNumber
    6) scan_code (w/Alt) = key-first_keycode + 0x78

    @param UsbCode Key         index (key code - 1E)

    @retval ScanCodeAsciiCode  scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_Number(UINT8 UsbCode)
{
    UINT8 ScanCode = UsbCode+2;
    UINT8 AsciiCode = aNumbers[UsbCode].NormalNumber;
    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(ScanCode);
    if (mLegacyKeyboard.KeyModifierState.Shift) {
        AsciiCode = aNumbers[UsbCode].ShiftedNumber;
    }
    if (mLegacyKeyboard.KeyModifierState.Ctrl) {
        AsciiCode = 0; ScanCode = 0;
        if (UsbCode == 1) { // "2"
            ScanCode = 3;
        }
        if (UsbCode == 5) { // "6"
            ScanCode = 7;
            AsciiCode = 0x1E;
        }
    }
    if (mLegacyKeyboard.KeyModifierState.Alt) {
        ScanCode = UsbCode + 0x78;
    }

    return (UINT16)(ScanCode << 8) + AsciiCode;
}


/**
    Returns the scan/ascii code for "basic keys" - not letters, not
    numbers (Enter, Escape, '[', '/', etc.); USB code from 28 to 38.

    @param UsbCode              Key index (key code - 28)

    @retval ScanCodeAsciiCode   scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_BasicKey(UINT8 UsbCode)
{
    UINT8 ScanCode  = aBasicKey[UsbCode].BasicKeyScancode;
    UINT8 AsciiCode  = (mLegacyKeyboard.KeyModifierState.Shift)?
            aBasicKey[UsbCode].BasicKeyAsciiShifted : aBasicKey[UsbCode].BasicKeyAsciiNormal;
    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(ScanCode );
    if (mLegacyKeyboard.KeyModifierState.Ctrl) return aBasicKey[UsbCode].BasicKeyCodeCtrl;
    if (mLegacyKeyboard.KeyModifierState.Alt) {
        AsciiCode = aBasicKey[UsbCode].BasicKeyAsciiAlt;
        if (AsciiCode == 0) ScanCode  = 0;
    }

    return (UINT16)(ScanCode  << 8) + AsciiCode ;
}


/**
    Returns the scan/ascii code for functional keys F1..F10;
    USB code from 3A to 43.

    @param UsbCode             Key index (key code - 3A)

    @retval ScanCodeAsciiCode  scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_F1_10Key(UINT8 UsbCode)
{
    UINT8 Code = aF1_10Key[UsbCode];
    //
    // ASCII codes are 0s
    // Scan codes:
    //   shifted = normal+0x19
    //   w/Ctrl  = normal+0x23
    //   w/Alt   = normal+0x2d
    //

    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(Code);

    if (mLegacyKeyboard.KeyModifierState.Shift) return (UINT16)(Code+0x19) << 8;
    if (mLegacyKeyboard.KeyModifierState.Ctrl) return (UINT16)(Code+0x23) << 8;
    if (mLegacyKeyboard.KeyModifierState.Alt) return (UINT16)(Code+0x2d) << 8;

    return (UINT16)Code << 8;
}


/**
    Returns the scan/ascii code for functional keys F11 and F12;
    USB code 44 and 45.

    @param UsbCode             Key index (key code - 44)

    @retval ScanCodeAsciiCode  scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_F11F12Key(UINT8 UsbCode)
{
    UINT16 aF11_F12[2] = {0x8500, 0x8600};
    //
    // ASCII codes are 0s
    // Scan codes: Normal Shifted w/Ctrl w/Alt
    //        F11   0x85   0x87    0x89   0x8B
    //        F12   0x86   0x88    0x8A   0x8C
    //

    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon((UINT8)(aF11_F12[UsbCode] >> 8));

    if (mLegacyKeyboard.KeyModifierState.Shift) return aF11_F12[UsbCode]+0x200;
    if (mLegacyKeyboard.KeyModifierState.Ctrl) return aF11_F12[UsbCode]+0x400;
    if (mLegacyKeyboard.KeyModifierState.Alt) return aF11_F12[UsbCode]+0x600;

    return aF11_F12[UsbCode];
}


/**
    Returns the scan/ascii code for extended keys such as Home,
    End, arrows, PgUp/Dn; USB code from 49 to 52.

    @param UsbCode  Key index (key code - 49)

    @retval scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_ExtKey(UINT8 UsbCode )
{
/*    UINT8 ScanCode = aExtKeys[UsbCode].NormalShiftedScanCode;
    UINT8 AsciiCode  = 0;

    if (mLegacyKeyboard.KeyModifierState.Shift) {
        AsciiCode = aExtKeys[UsbCode].ShiftedAsciiCode;
    } else {
        if (mLegacyKeyboard.KeyModifierState.Ctrl) {
            ScanCode = aExtKeys[UsbCode].wCtrlScanCode;
        } else {
            if (mLegacyKeyboard.KeyModifierState.Alt) {
                ScanCode = aExtKeys[UsbCode].wAltScanCode;
            }
        }
    }
    return ((UINT16)ScanCode << 8) + AsciiCode;*/
    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(aExtKeys[UsbCode]);

    return (UINT16)aExtKeys[UsbCode]<<8;
}


/**
    Returns the scan/ascii code for non-numeric part of the keypad,
    such as '/', '*', etc.; USB code from 54 to 58.

    @param UsbCode            Key index (key code - 54)

    @retval ScanCodeAsciiCode scan code in upper byte, ascii code in lower byte

**/

UINT16 GetCode_Keypad1(UINT8 UsbCode)
{
    if (mLegacyKeyboard.KeyModifierState.Ctrl || mLegacyKeyboard.KeyModifierState.Alt) {
        return 0;
    }

    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon((UINT8)(aKeypad1[UsbCode] >> 8));

    return aKeypad1[UsbCode];
}


/**
    Returns the scan/ascii code for numeric part of the keypad;
    USB code from 59 to 63.

    @param UsbCode             Key index (key code - 59)

    @retval ScanCodeAsciiCode  UsbCode scan code in upper byte, ascii code in lower byte

    @note  The ascii_code is altered depending on the combination of
              Shift and NumLock.

**/

UINT16 GetCode_Keypad2(UINT8 UsbCode)
{
    UINT8 ScanCode  = aKeypad2[UsbCode].NormalScanCode;
    UINT8 AsciiCode  = 0;
    BOOLEAN ChangeCase = mLegacyKeyboard.KeyModifierState.NumLock
        || mLegacyKeyboard.KeyModifierState.Shift;

    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(ScanCode);

    if (mLegacyKeyboard.KeyModifierState.NumLock
        && mLegacyKeyboard.KeyModifierState.Shift) ChangeCase = FALSE;

    if (ChangeCase) AsciiCode  = aKeypad2[UsbCode].ShiftedAsciiCode;
    if (mLegacyKeyboard.KeyModifierState.Ctrl) {
        return (UINT16)aKeypad2[UsbCode].CtrlScanCode << 8;
    }
    if (mLegacyKeyboard.KeyModifierState.Alt) {
        return (UINT16)aKeypad2[UsbCode].AltScanCode << 8;
    }
    return ((UINT16)ScanCode << 8) + AsciiCode ;
}


/**
    Returns the scan/ascii code for USB Key 0x64, a.k.a. Europe2
    Europe2 is typically in AT-101 Key Position 45, between Left
    Shift and Z keys.
    @param    UsbCode       Key index 
    @retval   0x567C
    @retval   0x565C
**/

UINT16 GetCode_64(UINT8 usbcode)
{
    //
    // Check for Hot Key from the KeyMon driver
    //
    UpdateKeyMon(0x56);

    if (mLegacyKeyboard.KeyModifierState.Shift) return 0x567C;
    return 0x565C;
}

/**
    This structure describes the range of the USB keys and the
    function that is called if the USB key is found within this
    range.

 Fields:  Name           Type         Description
          first_keycode  UINT8        first key code in the range
          last_keycode   UINT8        last key code in the range
          GetCode        GETCODE_FUNC function to call if the code is in the range

**/
typedef struct _TKEYGROUP  TKEYGROUP;  
struct _TKEYGROUP {
    UINT8   first_keycode;
    UINT8   last_keycode;
    GETCODE_FUNC    GetCode;
};

TKEYGROUP aGetKey[] = {
    {0x04, 0x1d, GetCode_Letter},
    {0x1e, 0x27, GetCode_Number},
    {0x28, 0x38, GetCode_BasicKey},
    {0x3A, 0x43, GetCode_F1_10Key},
    {0x44, 0x45, GetCode_F11F12Key},
    {0x49, 0x52, GetCode_ExtKey},
    {0x54, 0x58, GetCode_Keypad1},
    {0x59, 0x63, GetCode_Keypad2},
    {0x64, 0x64, GetCode_64},
    {0, 0, 0}
};


/**
    This function performs the key autorepeat
    @param  None

    @retval None
**/

VOID SysNoKbcAutoRepeat()
{
    UINT8 Index;
    UINT8 BdaKbdLedFlags;
    UINT8 Ledstate;


    EFI_STATUS  Status;
    VOID        *AddrCheck = ((VOID*)(UINTN)0x417); 
    Status = AmiUsbValidateMemoryBuffer (AddrCheck, sizeof(UINT8));
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return;


    BdaKbdLedFlags = *(UINT8*)(UINTN)0x417;
    gUsbData->RepeatCounter++;
    if (gUsbData->RepeatCounter >= gUsbData->RepeatRate) {

        //
        // Repeat rate is reached.
        // Reload repeat delay counter with keyrepeat delay value; original
        // type delay value will be restored in ProcessKeyboardData
        //
        if (gUsbData->RepeatIntervalMode){
            gUsbData->RepeatRate = aTypematicRateDelayTable[
                    (gUsbData->UsbKbcStatusFlag & KBC_TYPE_RATE_BIT_MASK_16MS) >>
                     KBC_TYPE_RATE_BIT_SHIFT_16MS];
        } else {
            gUsbData->RepeatRate = aTypematicRateDelayTable[
                    (gUsbData->UsbKbcStatusFlag & KBC_TYPE_RATE_BIT_MASK_8MS) >>
                     KBC_TYPE_RATE_BIT_SHIFT_8MS];            
        }
        
        gUsbData->RepeatCounter   = 0;

        for (Index=6; Index>0; Index--) if (mLegacyKeyboard.KeyCodeStorage[Index-1] != 0) break;

        if (Index != 0) {    // Some keys to repeat
            if (mLegacyKeyboard.KeyCodeStorage[Index-1]==mLegacyKeyboard.KeyToRepeat) {
                ProcessKeyCode(mLegacyKeyboard.KeyToRepeat);
            } else {
                mLegacyKeyboard.KeyToRepeat = mLegacyKeyboard.KeyCodeStorage[Index-1];
            }
            USBKeyRepeat(NULL, 2);  // Enable Key repeat
        }
    }

    //
    // See if current NumLock/ScrlLock/CapsLock matches the 40:17 values; update
    // the local data and LEDs accordingly.
    //
    Ledstate = *(UINT8*)&mLegacyKeyboard.KeyModifierState & 7;
    if (((BdaKbdLedFlags>>4) & 7) != Ledstate) {  // 7 is a mask for Scrl/Num/Caps locks
        *(UINT8*)&mLegacyKeyboard.KeyModifierState &= 0xF8;
        *(UINT8*)&mLegacyKeyboard.KeyModifierState |= ((BdaKbdLedFlags>>4) & 7);
        UpdateLEDs();   // Turn on/off Ctrl, Alt, NumLock LEDs
    }
}


/**
    Calls the service routine for the given keycode. Returns the
    scan/ascii code.

    @param keyCode             Key code

    @retval Code               scan code in upper byte, ascii code in lower byte

**/

UINT16
GetAsciiScan(UINT8 keyCode)
{
    TKEYGROUP *KeyGroup;
    UINT16 Code;

    if (keyCode == 0x2C) return 0x3920; // Space Bar
    for (KeyGroup = aGetKey; KeyGroup->GetCode != 0; KeyGroup++) {
        if (keyCode >= KeyGroup->first_keycode && keyCode <= KeyGroup->last_keycode) {
            Code = KeyGroup->GetCode(keyCode-KeyGroup->first_keycode);
            if (mLegacyKeyboard.KeyModifierState.Alt) Code &= 0xFF00;
            return Code;
        }
    }
    return 0;
}

/**
    This function takes the keyboard scan code and checks if it is present
    in the Key Monitor table. If found, it updates the corresponding bit in
    the Key Monitor map.
    Key monitor data structure pointer is at 9FC0:10C
    Key monitor map (32 bit) updated by this routine is at 9FC0:108
    Map element is {BYTE, DWORD}; BYTE - scan code, DWORD - attribute    

    @param KeyCode Key code
    @retval None 

**/
VOID
UpdateKeyMon(UINT8 KeyCode) 
{

#if KEYMONFILTER_SUPPORT
    KEY_ELEMENT     *KeyMonData;
    UINT32          *KeyMonMap;
    UINT16          EbdaSeg;
    UINTN           Index;
    UINTN           KeyMonSize;
    

    EFI_STATUS  Status;
    VOID        *AddrCheck = ((VOID*)0x40E); 
    Status = AmiUsbValidateMemoryBuffer(AddrCheck, sizeof(UINT32));
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return ;

 
    EbdaSeg = *(UINT16*)0x40e;
    KeyMonMap=(UINT32 *)((EbdaSeg << 4)+ KEYMON_MAP);


    Status = AmiUsbValidateMemoryBuffer((VOID*)KeyMonMap, sizeof(UINT32));
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return;


    //
    //KeyMon data Seg is located in EBDA:10E and Offset is EBDA:0x10C
    //    
    KeyMonData=(KEY_ELEMENT*)((*(UINT16 *)((EbdaSeg << 4) + KEYMON_DATA_ADDRESS + 2) << 4) + \
                             *(UINT16 *)((EbdaSeg << 4)  + KEYMON_DATA_ADDRESS));


    Status = AmiUsbValidateMemoryBuffer((VOID*)KeyMonData, sizeof(KEY_ELEMENT));
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return;



    if(KeyMonData == 0) {
        //
        //Nobody registerd the Hot key with KeyMon driver.
        //
        return;
    }
    
    KeyMonSize=*(UINT32 *)KeyMonData;
    (UINT8 *)KeyMonData+=4;

    for(Index=0;Index<=KeyMonSize;Index++) {
        if(KeyMonData[Index].ScanCode == KeyCode && 
            KeyMonData[Index].Keyattribute.ShiftKey == mLegacyKeyboard.KeyModifierState.Shift && 
            KeyMonData[Index].Keyattribute.CtrlKey == mLegacyKeyboard.KeyModifierState.Ctrl &&
            KeyMonData[Index].Keyattribute.AltKey == mLegacyKeyboard.KeyModifierState.Alt ) {
            //
            //Update the Keymon Map in the EBDA:0x108 area.
            //
            *KeyMonMap= (*KeyMonMap) | (1<< Index);
        }

    }
    return;
#else
    return;
#endif

}

/**
    Insert the given scan/ascii code in the BDA keyboard queue.
    Updates the necessary BDA pointers, head and tail.

    @param KeyCode    Key code, scan code in upper byte, ascii code in lower byte
    @retval None 
**/

VOID
InsertChar(UINT16 KeyCode)
{
    UINT16 BufHead;
    UINT16 BufTail;
    UINT16 BufStart;
    UINT16 BufEnd;


    EFI_STATUS  Status;
    VOID        *AddrCheck = ((VOID*)(UINTN)0x400); 
    Status = AmiUsbValidateMemoryBuffer (AddrCheck, 0x100);
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return;


    BufHead = *(UINT16*)(UINTN)0x41a;
    BufTail = *(UINT16*)(UINTN)0x41c;
    BufStart = *(UINT16*)(UINTN)0x480;
    BufEnd = *(UINT16*)(UINTN)0x482;

    *(UINT16*)(UINTN)(0x400+BufTail) = KeyCode;
    BufTail+=2;
    if (BufTail >= BufEnd) {
        BufTail = BufStart;
    }

    if (BufTail == BufHead) {
        //
        // Buffer overflow should be indicated here
        //
        return;
    }
    *(UINT16*)(UINTN)0x41c = BufTail;

    return;
}



/**
    Updates USB keyboard(s) LEDs according to the value of
    mLegacyKeyboard.KeyModifierState.
    
    @param None 
    @retval None 
**/

VOID
UpdateLEDs(
)
{
    UINT8       Index;
    DEV_INFO    *KbdDev;
    UINT8       Rb;


    EFI_STATUS  Status;
    VOID        *AddrCheck = ((VOID*)(UINTN)0x497); 
    Status = AmiUsbValidateMemoryBuffer (AddrCheck, sizeof(UINT8));
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return;

    //
    // Update LED status in every USB keyboard on the system
    //
    // BIT0 ScrlLock, BIT1 NumLock, BIT2 CapsLock
    Rb = (mLegacyKeyboard.KeyModifierState.NumLock)? 1 : 0;
    Rb = (mLegacyKeyboard.KeyModifierState.CapsLock)? Rb|2 : Rb;
    Rb = (mLegacyKeyboard.KeyModifierState.ScrlLock)? Rb|4 : Rb;
    //
    // Update the LED status in BDA.
    //
    *(UINT8*)(UINTN)0x497 = ((*(UINT8*)(UINTN)0x497) & 0xF8 ) | ((mLegacyKeyboard.KeyModifierState.NumLock)? 2 : 0)
                               | ((mLegacyKeyboard.KeyModifierState.CapsLock)? 4:0) | ((mLegacyKeyboard.KeyModifierState.ScrlLock)? 1 : 0) ;

    for (Index = 0; Index < gUsbData->MaxHidCount; Index++) {
        KbdDev  = gUsbDataList->UsbKbDeviceTable[Index];
        if (KbdDev) {
        UsbKbdSetLed(KbdDev, Rb);
        }
    }
}


/**
    Updates mLegacyKeyboard.KeyModifierState according to the value
    of the 1st byte of the USB keyboard data.
    
    @param  UsbKeys     Usb Key buffer
    @retval None
**/

VOID
ProcessCtrlAltShift(
    UINT8 *UsbKeys
)
{
    UINT8   Index;


    mLegacyKeyboard.KeyModifierState.Ctrl  = (UsbKeys[0] & 0x11)? 1 : 0;
    mLegacyKeyboard.KeyModifierState.Shift = (UsbKeys[0] & 0x22)? 1 : 0;
    mLegacyKeyboard.KeyModifierState.Alt   = (UsbKeys[0] & 0x44)? 1 : 0;

    //
    // Process Ctrl-Alt-Del combination
    //
    if (mLegacyKeyboard.KeyModifierState.Ctrl
        && mLegacyKeyboard.KeyModifierState.Alt) {
        for (Index = 2; Index < 6; Index++) {
            if (UsbKeys[Index] == 0x4C || UsbKeys[Index] == 0x63) {
                if (!(gUsbData->UsbStateFlag & USB_FLAG_RUNNING_UNDER_EFI)) {

                      AmiUsbResetSystem();
                      ByteWriteIO(0xcf9, 6);
                      // We should never get this far
                      while(1);
//                    }
                }
            }
        }
    }
}


/**
    Process the keys that alter NumLock/ScrollLock/CapsLock; updates
    mLegacyKeyboard.KeyModifierState and 0:417 accordingly.

    @param  UsbKeys     Usb Key buffer
    @retval None

**/

VOID
ProcessLockKeys(
    UINT8 *UsbKeys
)
{
    UINT8 Index;

    for (Index = 2; Index < 8; Index++) {
        switch (UsbKeys[Index]) {
            case 0x53:  // NumLock
                *(UINT8*)(UINTN)0x417 ^= 0x20; // Toggle BIT5
                // *(UINT8*)0x497 ^= 0x02; // Toggle BIT1
                mLegacyKeyboard.KeyModifierState.NumLock ^= 1;  // Toggle numlock state
                break;
            case 0x39:  // CapsLock
                *(UINT8*)(UINTN)0x417 ^= 0x40; // Toggle BIT6
                // *(UINT8*)0x497 ^= 0x04; // Toggle BIT2
                mLegacyKeyboard.KeyModifierState.CapsLock ^= 1;  // Toggle capslock state
                break;
            case 0x47:  // ScrlLock
                *(UINT8*)(UINTN)0x417 ^= 0x10; // Toggle BIT4
                // *(UINT8*)0x497 ^= 0x01; // Toggle BIT0
                mLegacyKeyboard.KeyModifierState.ScrlLock ^= 1;  // Toggle scrollock state
                break;
        }
    }
}


/**
    There is often the new key is pressed on a USB keyboard while
    the previous one is not quite released. In this case usbKeys
    buffer contains the old keys and the new ones. User, on the
    other hand, expects only the new ones to be processed.
    This requires the buffer data modification so that the "old"
    keys are removed.
    The only time we do not do this analysis is when the buffer
    is clear that indicates that all keys are released.
    
    @param  UsbKeys     Usb Key buffer
    @retval None

**/

VOID
AdjustKeyBuffer(
    UINT8 *UsbKeys
)
{
    UINT8 aData[6];
    UINT8 Index1, Index2;

    // Save the buffer
    for (Index1 = 0; Index1 < 6; Index1++) aData[Index1]=UsbKeys[Index1];

    // Patch the buffer
    for (Index2 =0; Index2 < 6; Index2++) {
        if (mLegacyKeyboard.KeyCodeStorage[Index2]==0) continue;
        for (Index1 = 0; Index1 < 6; Index1++) {
            if (UsbKeys[Index1] == 0) continue;
            if (UsbKeys[Index1] == mLegacyKeyboard.KeyCodeStorage[Index2]) {
                UsbKeys[Index1] = 0;
            }
        }
    }
    // Store the original buffer
    for (Index1 = 0; Index1 < 6; Index1++) mLegacyKeyboard.KeyCodeStorage[Index1] = aData[Index1];
}


/**
    This routine converts USB code into UINT16 with ASCII code in the
    lower byte and PS/2 scan code in the upper byte and inserts this
    UINT16 in the legacy keyboard queue in BDA.

    @param Code    USB key code
    @retval None
**/

VOID
ProcessKeyCode(UINT8 Code)
{
    UINT16 AsciiScan;
    AsciiScan = GetAsciiScan(Code);
    if (AsciiScan != 0) {
        InsertChar(AsciiScan);
    }
}


/**
    This routine is called from when the new data from USB keyboard
    is transmitted and available for processing. The functionality is
    similar to legacy INT9 handler - data is converted into PS/2
    ASCII/Scan codes and placed in BDA.

    @param UsbKeys Buffer with USB keys
    @retval None
**/

VOID
USBKB_Int9(
    UINT8 *UsbKeys
)
{
    UINT8 *KeyCode;
    UINT8 Index;
    UINT8 Ledstate;
    UINT8 BdaKbdLedFlags;


    EFI_STATUS          Status;
    VOID                *AddrCheck = ((VOID*)(UINTN)0x417); 
    Status = AmiUsbValidateMemoryBuffer (AddrCheck, sizeof(UINT8));
    if ((EFI_ERROR(Status))&&(Status != EFI_ABORTED)) return;


    BdaKbdLedFlags = (*(UINT8*)(UINTN)0x417) >> 4;
    AdjustKeyBuffer(&UsbKeys[2]);

    //
    // See if current NumLock/ScrlLock/CapsLock matches the 40:17 values.
    // ; update the local data and LEDs accordingly.
    //
    Ledstate = *(UINT8*)&mLegacyKeyboard.KeyModifierState & 7;
    if ((BdaKbdLedFlags & 7) != Ledstate) {  // 7 is a mask for Scrl/Num/Caps locks
        *(UINT8*)&mLegacyKeyboard.KeyModifierState &= 0xF8;
        *(UINT8*)&mLegacyKeyboard.KeyModifierState |= (BdaKbdLedFlags & 7);
        UpdateLEDs();   // Turn on/off Ctrl, Alt, NumLock LEDs
        //
        // Update to current Ctrl, Alt, NumLock LEDs state.
        //
        Ledstate = *(UINT8*)&mLegacyKeyboard.KeyModifierState & 7;
    }

    ProcessLockKeys(UsbKeys);
    ProcessCtrlAltShift(UsbKeys);

    for (KeyCode=UsbKeys+2, Index=0; Index<6; Index++, KeyCode++) {
        if (*KeyCode==0) continue;
        ProcessKeyCode(*KeyCode);
    }

    if (Ledstate != (*(UINT8*)&mLegacyKeyboard.KeyModifierState & 7)) {
        UpdateLEDs();   // Turn on/off Ctrl, Alt, NumLock LEDs
    }

    //
    // Reload the typematic rate value
    //
    if (gUsbData->RepeatIntervalMode){
        gUsbData->RepeatRate = aTypematicRateDelayTable[
            (gUsbData->UsbKbcStatusFlag & KBC_TYPE_DELAY_BIT_MASK_16MS) >>
                        KBC_TYPE_DELAY_BIT_SHIFT_16MS];
    } else {
        gUsbData->RepeatRate = aTypematicRateDelayTable[
        (gUsbData->UsbKbcStatusFlag & KBC_TYPE_DELAY_BIT_MASK_8MS) >>
                        KBC_TYPE_DELAY_BIT_SHIFT_8MS];
    }
    gUsbData->RepeatCounter   = 0;

    //
    // Buffer might be modified, original buffer is stored
    // in mLegacyKeyboard.KeyCodeStorage
    //
    if (mLegacyKeyboard.KeyCodeStorage[0] == 0) {
        USBKeyRepeat(NULL, 1);  // Disable Key repeat
    } else {
        USBKeyRepeat(NULL, 2);  // Enable Key repeat
    }
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
