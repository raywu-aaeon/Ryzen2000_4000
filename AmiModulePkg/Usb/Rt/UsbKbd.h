//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file UsbKbd.h
    AMI USB keyboard support header

**/

// Avoid including multiple instance of this file
#ifndef     __USBKBD_H
#define     __USBKBD_H

#include    <Token.h>

// Make/break code equates

#define KBC_AUTO_REPEAT_BIT_MASK    (0x01 << 9)
#define KBC_PASSWORD_FLAG_BIT_MASK  (0x01 << 10)
#define KBC_SCANNER_STATUS_BIT_MASK (0x01 << 11)
#define KBC_PORT6064_TRAP_BIT_MASK  (0x01 << 12)
#define KBC_MK_BRK_CODE_BIT_MASK    (0x01 << 13)

#define USB_GEN_MAKE_CODE  0x020
#define USB_GEN_BREAK_CODE 0x030


// Equates used by keyboard controller scanner code
#define LEFT_ALT        0x011   // Left-ALT scan code (set 2)
#define LEFT_CTRL       0x014   // Left-CTRL scan code (set 2)
#define LEFT_SHIFT      0x012   // Left-SHIFT scan code (set 2)
#define RIGHT_SHIFT     0x059   // Right-SHIFT scan code (set 2)

// Extended status flag bit definitions
#define KBCEXT_LED_UPDATE_IN_PROGRESS_BIT   BIT0

// Scan code for base case only
#define RIGHT_ALT       0x011+0x80  // Local code id (scan-2)
#define RIGHT_CTRL      0x014+0x80  // Local code id (scan-2)
#define LEFT_MS_KEY     0x01F+0x80  // Microsoft left key
#define RIGHT_MS_KEY    0x027+0x80  // Microsoft right key
#define APP_MS_KEY      0x02F+0x80  // Microsoft application key
#define RIGHT_ENTER     0x05A+0x80  // Local code id (scan-2)

#define USB_CAPS_LOCK_KEY_CODE          0x39
#define USB_SCROLL_LOCK_KEY_CODE        0x47
#define USB_NUM_LOCK_KEY_CODE           0x53

// Equates for KB shift key status information
#define KB_FUNCTION_BIT         7   // Function key LED bit
#define KB_FUNCTION_BIT_MASK    (1 << KB_FUNCTION_BIT)
#define KB_SCROLL_LOCK_BIT      6   // Scroll key LED bit
#define KB_SCROLL_LOCK_BIT_MASK (1 << KB_SCROLL_LOCK_BIT)
#define KB_CAPS_LOCK_BIT        5   // CAPS lock key LED bit
#define KB_CAPS_LOCK_BIT_MASK   (1 << KB_CAPS_LOCK_BIT)
#define KB_NUM_LOCK_BIT         4   // NUM lock key LED bit
#define KB_NUM_LOCK_BIT_MASK    (1 << KB_NUM_LOCK_BIT   )
#define KB_ALT_KEY_BIT          3   // ALT key status bit
#define KB_ALT_KEY_BIT_MASK     (1 << KB_ALT_KEY_BIT    )
#define KB_CTRL_KEY_BIT         2   // CTRL key status bit
#define KB_CTRL_KEY_BIT_MASK    (1 << KB_CTRL_KEY_BIT   )
#define KB_LSHIFT_KEY_BIT       1   // LSHIFT key status bit
#define KB_LSHIFT_KEY_BIT_MASK  (1 << KB_LSHIFT_KEY_BIT)
#define KB_RSHIFT_KEY_BIT       0   // RSHIFT key status bit
#define KB_RSHIFT_KEY_BIT_MASK  (1 << KB_RSHIFT_KEY_BIT)

#define KBC_SCAN_CODE_SET_BIT_SHIFT 0
#define KBC_SET_SCAN_CODE_SET2      (0x02 << KBC_SCAN_CODE_SET_BIT_SHIFT)
#define KBC_SCAN_CODE_SET_BIT_MASK  (0x03 << KBC_SCAN_CODE_SET_BIT_SHIFT)


#define REPEAT_8MS                    0
#define REPEAT_16MS                   1

#define REPEAT_INTERVAL_16MS          16
#define KBC_TYPE_RATE_BIT_SHIFT_16MS  1
#define KBC_TYPE_RATE_BIT_MASK_16MS   (0x05 << KBC_TYPE_RATE_BIT_SHIFT_16MS)

#define KBC_TYPE_DELAY_BIT_SHIFT_16MS 4
#define KBC_TYPE_DELAY_BIT_MASK_16MS  (0x05 << KBC_TYPE_DELAY_BIT_SHIFT_16MS)


#define REPEAT_INTERVAL_8MS           8
#define KBC_TYPE_RATE_BIT_SHIFT_8MS   2
#define KBC_TYPE_RATE_BIT_MASK_8MS    (0x07 << KBC_TYPE_RATE_BIT_SHIFT_8MS)

#define KBC_TYPE_DELAY_BIT_SHIFT_8MS  6
#define KBC_TYPE_DELAY_BIT_MASK_8MS   (0x07 << KBC_TYPE_DELAY_BIT_SHIFT_8MS)


// Scan code common to all the cases (base, control, shift and alt cases)
#define PRINT_SCREEN        (0x07C + 0x80)    // Local code id (scan-2)

// Scan code common to base and control cases
#define PAUSE_KEY       (0x07E + 0x80)    // Local code id (scan-2)

// Scan code common to base and shift cases
#define SLASH_KEY       (0x4A + 0x80)     // Local code id (scan-2)

// Scan code common to base, shift and num lock cases
#define END_KEY         (0x069 + 0x80)    // Local code id (scan-2)
#define LEFT_KEY        (0x06B + 0x80)    // Local code id (scan-2)
#define HOME_KEY        (0x06C + 0x80)    // Local code id (scan-2)
#define INSERT_KEY      (0x070 + 0x80)    // Local code id (scan-2)
#define DEL_KEY         (0x071 + 0x80)    // Local code id (scan-2)
#define DOWN_KEY        (0x072 + 0x80)    // Local code id (scan-2)
#define RIGHT_KEY       (0x074 + 0x80)    // Local code id (scan-2)
#define UP_KEY          (0x075 + 0x80)    // Local code id (scan-2)
#define PAGE_DOWN_KEY   (0x07A + 0x80)    // Local code id (scan-2)
#define PAGE_UP_KEY     (0x07D + 0x80)    // Local code id (scan-2)

#define CCB_TRANSLATE_SCAN_CODE_BIT_MASK    BIT6
#define KBC_COMMAND_REG     0x64
#define KBC_SUBCOMMAND_REG  0x60
#define KBC_STATUS_REG      0x64
#define KBC_DATA_REG        0x60

#define MOUSE_ENABLED_BIT               7
#define MOUSE_ENABLED_BIT_MASK          (1 << MOUSE_ENABLED_BIT)
#define MOUSE_DATA_READY_BIT            6
#define MOUSE_DATA_READY_BIT_MASK       (1 << MOUSE_DATA_READY_BIT)
#define MOUSE_DATA_FROM_USB_BIT         5
#define MOUSE_DATA_FROM_USB_BIT_MASK    (1 << MOUSE_DATA_FROM_USB_BIT)
  // Mouse data size = 1:4byte data, 0:3byte data
#define MOUSE_4BYTE_DATA_BIT            4
#define MOUSE_4BYTE_DATA_BIT_MASK       (1 << MOUSE_4BYTE_DATA_BIT)

#define KBC_DATA_TX_ORDER_BIT_MASK  0x03 << 14
#define KBC_DATA_TX_ORDER_INC_VALUE 0x01 << 14
#define KBC_DATA_TX_ORDER_KB_FIRST  0x02 << 14

#define CCB_KEYBOARD_INTRPT                 BIT0
#define CCB_MOUSE_INTRPT                    BIT1    
#define CCB_KEYBOARD_DISABLED               BIT4
#define CCB_MOUSE_DISABLED                  BIT5
#define CCB_TRANSLATE_SCAN_CODE_BIT_MASK    BIT6

#ifndef USB_KBD_SET_LED_TIMEOUT_MS
#define USB_KBD_SET_LED_TIMEOUT_MS 100
#endif

UINT8       EFIAPI ByteReadIO(UINT16);
VOID        EFIAPI ByteWriteIO(UINT16, UINT8);

UINT8       USBMouse_GetFromMouseBuffer ();
VOID        EFIAPI USBKeyRepeat(HC_STRUC*, UINT8);
UINT8       USBKBC_GetFromCharacterBuffer();

UINT8   USBKB_ConvertSet2CodeToSet1Code(UINT8);
VOID    USBKBC_SendToCharacterBuffer(UINT8);
UINT8   USBTrap_GetCurrentScanCodeSetNumber();
UINT8   USBKB_ConvertScanCodeBetweenCodeSet(UINT8, UINT8*);
UINT8   KBC_WaitForInputBufferToBeFree( );
UINT8   KBC_WaitForOutputBufferToBeFilled( );
VOID    USBKB_GenerateType1MakeCode( );
VOID    USBKB_GenerateType1BreakCode( );
VOID    USBKB_GenerateType2MakeCode( );
VOID    USBKB_GenerateType2BreakCode( );
UINT8   USBTrap_GetOverrunCode( );
VOID    USBKB_DiscardCharacter(UINT8*);
UINT16  USBKB_CheckForExtendedKey(UINT8);
UINT16  USBKB_CheckForNumericKeyPadKey(UINT8);
UINT8   USBKBC_CheckCharacterBufferFull(UINT8);
VOID    USBKB_UpdateLEDState(UINT8);
UINT8   USBKB_ConvertUSBKeyCodeToScanCodeSet2 (UINT8);
UINT16  USBKB_CheckModifierKeyPress (UINT8);
UINT8   KBC_WriteCommandByte(UINT8);
UINT8   KBC_ReadDataByte(UINT8 *);
VOID    KBC_WriteSubCommandByte(UINT8);
EFI_STATUS    SYSKBC_SendKBCData();

extern  UINT8       EFIAPI USB_InstallCallBackFunction (CALLBACK_FUNC);

extern  DEV_INFO*   EFIAPI USB_GetDeviceInfoStruc(UINT8, DEV_INFO*,UINT8, HC_STRUC*);
extern  UINT8       USBLogError(UINT16);
extern  VOID        USBKeyRepeat(HC_STRUC*, UINT8);

extern  UINT8       USBMSSendMouseData();
extern  VOID        USBMSUpdateMouseInterface();


VOID        USBKBDInitialize (VOID);
UINT8       USBKBDDisconnectDevice (DEV_INFO*);

VOID    USBKBC_GetAndStoreCCB();
DEV_INFO*   USBKBDConfigureDevice (DEV_INFO*);  //(EIP84455)
UINT16  USBKBDFindUSBKBDeviceTableEntry(DEV_INFO*);
UINT8   USBKBDProcessKeyboardData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   UsbKbdSetLed(DEV_INFO*, UINT8);

VOID    USBKB_GenerateScanCode ( UINT8, UINT8, UINT16 );

VOID    UsbScanner(DEV_INFO*, UINT8*);
VOID    USBKB_Scanner (DEV_INFO*, UINT8*);
VOID    USBKB_Int9(UINT8*);

VOID    ProcessKeyCode(UINT8);

VOID    LegacyAutoRepeat(HC_STRUC*);
VOID    SysKbcAutoRepeat(HC_STRUC*);
VOID    SysNoKbcAutoRepeat();
VOID    EFIAPI USBKBDPeriodicInterruptHandler(HC_STRUC*);
UINT8   EFIAPI USBHIDProcessData( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);               
UINT8   USBMSProcessMouseData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);
UINT8   USBAbsProcessMouseData ( HC_STRUC*, DEV_INFO*, UINT8*, UINT8*, UINT16);

typedef struct _USB_KEY USB_KEY; 
struct _USB_KEY{
  UINT8    KeyCode;
  BOOLEAN  Press;
};

#define MAX_KEY_ALLOWED 32

typedef struct _LEGACY_USB_KEY_MODIFIERS  LEGACY_USB_KEY_MODIFIERS; 
struct _LEGACY_USB_KEY_MODIFIERS {
    UINT8   ScrlLock    : 1;
    UINT8   NumLock     : 1;
    UINT8   CapsLock    : 1;
    UINT8   Ctrl        : 1;
    UINT8   Alt         : 1;
    UINT8   Shift       : 1;
};


typedef struct _LEGACY_USB_KEYBOARD  LEGACY_USB_KEYBOARD; 
struct _LEGACY_USB_KEYBOARD {
    UINT8 KeyCodeStorage[6];
    LEGACY_USB_KEY_MODIFIERS    KeyModifierState;
    UINT8 KeyToRepeat;
};


typedef struct _USBKBD_DATA  USBKBD_DATA ;
struct _USBKBD_DATA {
    union {
      UINT8       Modifier;
      struct {
          UINT8       KB_RSHIFT      : 1;// RSHIFT key status bit
          UINT8       KB_LSHIFT      : 1;// LSHIFT key status bit
          UINT8       KB_CTRL        : 1;// CTRL key status bit
          UINT8       KB_ALT         : 1;// ALT key status bit
          UINT8       KB_NUM_LOCK    : 1;// NUM lock key LED bit
          UINT8       KB_CAPS_LOCK   : 1;// CAPS lock key LED bit
          UINT8       KB_SCROLL_LOCK : 1;// Scroll key LED bit
          UINT8       KB_FUNCTION    : 1;// Function key LED bit     
      } Modify;
    } StatusBits;
      UINT8  Reserved;
      UINT8  Keycode[6];
};

//              0   Bit     Description
//              -------------------------------------------
//                   0      If set, button 1 is pressed
//                   1      If set, button 2 is pressed
//                   2      If set, button 3 is pressed
//                   3-7        Reserved
//              -------------------------------------------
//              1   X displacement value
//              2   Y displacement value
typedef struct _USBMS_DATA  USBMS_DATA ;
struct _USBMS_DATA{
    union {
      UINT8       ButtonByte;
      struct {
        UINT8       BUTTON1     : 1;// RSHIFT key status bit
        UINT8       BUTTON2     : 1;// LSHIFT key status bit
        UINT8       BUTTON3     : 1;// CTRL key status bit
        UINT8       RESERVED    : 5;// ALT key status bit
      } BUTTON;
    } StatusBits;
        UINT8   X;
        UINT8   Y;
        UINT8   Z;
        UINT16  EfiX;
        UINT16  EfiY;
        UINT8   FillUsage;
};
typedef struct _USBABS_DATA  USBABS_DATA; 
struct _USBABS_DATA {
        UINT8  Button;
        UINT16  X;
        UINT16  Y;
        UINT16   Pressure;
}; 
#endif      // __USB_H

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
