/*****************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */

#ifndef _AMD_PSP_KVM_KEYBOARD_H_
#define _AMD_PSP_KVM_KEYBOARD_H_

#define KVM_KEYBOARD_CONSOLE_IN_DEV_SIGNATURE       SIGNATURE_32 ('k', 'k', 'v', 'm')
#define KVM_KEYBOARD_CONSOLE_IN_EX_NOTIFY_SIGNATURE SIGNATURE_32 ('k', 'k', 'c', 'i')

typedef EFI_STATUS (EFIAPI *KVM_KBD_MAGIC_KEY_CALLBACK)(
  IN  VOID                    *Context
  );

typedef struct {
  UINT32                            KeySym;
} KbRingData;

#define KVM_KEYBOARD_BUFFER_SIZE       (32 * 1024) // 32KB Keyboard Buffer
#define KVM_KEYBOARD_DATA_BUFFER_SIZE  (KVM_KEYBOARD_BUFFER_SIZE - 2 * sizeof(UINT32))
#define KVM_KEYBOARD_KEY_MAX_COUNT     KVM_KEYBOARD_DATA_BUFFER_SIZE / sizeof(KbRingData)

typedef struct {
  UINT32                              WritePointer;
  UINT32                              ReadPointer;
  UINT32                              TerminateKVMSession;
  KbRingData                          Data[KVM_KEYBOARD_KEY_MAX_COUNT];
} KB_RING_BUFFER;

typedef struct {
  KB_RING_BUFFER*                       KbBuffer;
} KVM_KEY_QUEUE;

typedef struct _KVM_KEYBOARD_CONSOLE_IN_EX_NOTIFY {
  UINTN                               Signature;
  EFI_HANDLE                          NotifyHandle;
  EFI_KEY_DATA                        KeyData;
  EFI_KEY_NOTIFY_FUNCTION             KeyNotificationFn;
  LIST_ENTRY                          NotifyEntry;
} KVM_KEYBOARD_CONSOLE_IN_EX_NOTIFY;


typedef struct {
  UINTN                               Signature;

  EFI_HANDLE                          Handle;
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL      ConIn;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL   ConInEx;

  EFI_EVENT                           TimerEvent;

  KVM_KEY_QUEUE                       KvmKeyQueue;
  EFI_KEY_STATE                       KvmKeyState;

  //
  // Error state
  //
  BOOLEAN                             KeyboardErr;
  LIST_ENTRY                          NotifyList;
  EFI_UNICODE_STRING_TABLE            *ControllerNameTable;
} KVM_KEYBOARD_CONSOLE_IN_DEV;

#define KVM_KEYBOARD_CONSOLE_IN_DEV_FROM_THIS(a)  CR (a, KVM_KEYBOARD_CONSOLE_IN_DEV, ConIn, KVM_KEYBOARD_CONSOLE_IN_DEV_SIGNATURE)
#define KVM_TEXT_INPUT_EX_KEYBOARD_CONSOLE_IN_DEV_FROM_THIS(a) \
  CR (a, \
      KVM_KEYBOARD_CONSOLE_IN_DEV, \
      ConInEx, \
      KVM_KEYBOARD_CONSOLE_IN_DEV_SIGNATURE \
      )

#define KVM_KEYBOARD_MAX_TRY                256     // 256
#define KVM_KEYBOARD_TIMEOUT                65536   // 0.07s
#define KVM_KEYBOARD_WAITFORVALUE_TIMEOUT   1000000 // 1s
#define KVM_KEYBOARD_BAT_TIMEOUT            4000000 // 4s
#define KVM_KEYBOARD_TIMER_INTERVAL         100000  // 0.01s

#define KVM_NULL                            0x0000
#define KVM_BACKSPACE                       0xFF08
#define KVM_TAB                             0xFF09
#define KVM_ENTER                           0xFF0D
#define KVM_BREAK                           0xFF13
#define KVM_SCROLL_LOCK                     0xFF14
#define KVM_ESC                             0xFF1B
#define KVM_HOME                            0xFF50
#define KVM_LEFT                            0xFF51
#define KVM_UP                              0xFF52
#define KVM_RIGHT                           0xFF53
#define KVM_DOWN                            0xFF54
#define KVM_PAGE_UP                         0xFF55
#define KVM_PAGE_DOWN                       0xFF56
#define KVM_END                             0xFF57
#define KVM_PRINT_SCREEN                    0xFF61
#define KVM_INSERT                          0xFF63
#define KVM_NUMLOCK                         0xFF7F
#define KVM_F1                              0xFFBE
#define KVM_F2                              0xFFBF
#define KVM_F3                              0xFFC0
#define KVM_F4                              0xFFC1
#define KVM_F5                              0xFFC2
#define KVM_F6                              0xFFC3
#define KVM_F7                              0xFFC4
#define KVM_F8                              0xFFC5
#define KVM_F9                              0xFFC6
#define KVM_F10                             0xFFC7
#define KVM_F11                             0xFFC8
#define KVM_F12                             0xFFC9
#define KVM_LSHIFT                          0xFFE1
#define KVM_RSHIFT                          0xFFE2
#define KVM_LCONTROL                        0xFFE3
#define KVM_RCONTROL                        0xFFE4
#define KVM_CAPS_LOCK                       0xFFE5
#define KVM_LMETA                           0xFFE7
#define KVM_RMETA                           0xFFE8
#define KVM_LALT                            0xFFE9
#define KVM_RALT                            0xFFEA
#define KVM_ALTGR                           0xFF7E
#define KVM_WINDOWS                         0xFFEC
#define KVM_MENU                            0xFF67
#define KVM_DELETE                          0xFFFF

/* NUM Pad keys */
#define KVM_NPK_0                            0xFFB0
#define KVM_NPK_1                            0xFFB1
#define KVM_NPK_2                            0xFFB2
#define KVM_NPK_3                            0xFFB3
#define KVM_NPK_4                            0xFFB4
#define KVM_NPK_5                            0xFFB5
#define KVM_NPK_6                            0xFFB6
#define KVM_NPK_7                            0xFFB7
#define KVM_NPK_8                            0xFFB8
#define KVM_NPK_9                            0xFFB9
#define KVM_NPK_Enter                        0xFF8D 
#define KVM_NPK_Delete                       0xFF9F
#define KVM_NPK_Decimal                      0xFFAE
#define KVM_NPK_Add                          0xFFAB
#define KVM_NPK_Subtract                     0xFFAD
#define KVM_NPK_Multiply                     0xFFAA
#define KVM_NPK_Divide                       0xFFAF
#define KVM_NPK_DELETE                       0xFF9F
#define KVM_NPK_NUM_LOCK                     0xFF7F


#define KVM_MAGIC_KEY_STOP                  0xEE01 // KVM Stopped Message

#define CHAR_0                              '0'
#define CHAR_1                              '1'
#define CHAR_2                              '2'
#define CHAR_3                              '3'
#define CHAR_4                              '4'
#define CHAR_5                              '5'
#define CHAR_6                              '6'
#define CHAR_7                              '7'
#define CHAR_8                              '8'
#define CHAR_9                              '9'
#define CHAR_Decimal                        '.'
#define CHAR_Add                            '+'
#define CHAR_Subtract                       '-'
#define CHAR_Multiply                       '*'
#define CHAR_Divide                         '/'

typedef struct {
  UINT16                              KvmScanCode;
  UINT16                              EfiScanCode;
} KEY_CODE_MAP;

typedef struct {
  UINT16                              KvmScanCode;
  KVM_KBD_MAGIC_KEY_CALLBACK          CallBack;
} MAGIC_KEY_MAP;

EFI_STATUS
EFIAPI
KvmKeyboardEfiReset (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  IN  BOOLEAN                         ExtendedVerification
  );

EFI_STATUS
EFIAPI
KvmKeyboardReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  OUT EFI_INPUT_KEY                   *Key
  );

EFI_STATUS
KvmKeyboardReadKeyStrokeWorker (
  IN  KVM_KEYBOARD_CONSOLE_IN_DEV       *ConsoleInDev,
  OUT EFI_KEY_DATA                      *KeyData
  );

EFI_STATUS
EFIAPI
KvmKeyboardEfiResetEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  IN  BOOLEAN                           ExtendedVerification
  );

EFI_STATUS
EFIAPI
KvmKeyboardReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  OUT EFI_KEY_DATA                      *KeyData
  );

EFI_STATUS
EFIAPI
KvmKeyboardSetState (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_TOGGLE_STATE               *KeyToggleState
  );

EFI_STATUS
EFIAPI
KvmKeyboardRegisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_DATA                       *KeyData,
  IN EFI_KEY_NOTIFY_FUNCTION            KeyNotificationFunction,
  OUT EFI_HANDLE                        *NotifyHandle
  );

EFI_STATUS
EFIAPI
KvmKeyboardUnregisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_HANDLE                         NotificationHandle
  );

VOID
EFIAPI
KvmKeyboardWaitForKey (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  );

VOID
EFIAPI
KvmKeyboardWaitForKeyEx (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  );

EFI_STATUS
EFIAPI
KvmKbdControllerDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
KvmKbdControllerDriverStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  );

EFI_STATUS
EFIAPI
KvmStoppedMessageCallback(
  IN  VOID                    *Context
  );

#endif

