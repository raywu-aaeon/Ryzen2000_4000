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
#include "AmdPspKvm.h"

KEY_CODE_MAP ScanCodeMap[] = {
  { KVM_NULL, SCAN_NULL }, \
  { KVM_UP, SCAN_UP }, \
  { KVM_DOWN, SCAN_DOWN }, \
  { KVM_LEFT, SCAN_LEFT }, \
  { KVM_RIGHT, SCAN_RIGHT }, \
  { KVM_LSHIFT, SCAN_NULL}, \
  { KVM_RSHIFT, SCAN_NULL}, \
  { KVM_LCONTROL, SCAN_NULL}, \
  { KVM_RCONTROL, SCAN_NULL}, \
  { KVM_LMETA, SCAN_NULL}, \
  { KVM_RMETA, SCAN_NULL}, \
  { KVM_LALT, SCAN_NULL}, \
  { KVM_RALT, SCAN_NULL}, \
  { KVM_CAPS_LOCK, SCAN_NULL}, \
  { KVM_NPK_NUM_LOCK, SCAN_NULL}, \
  { KVM_PRINT_SCREEN, SCAN_NULL}, \
  { KVM_ALTGR, SCAN_NULL}, \
  { KVM_MENU, SCAN_NULL}, \
  { KVM_PAGE_UP, SCAN_PAGE_UP}, \
  { KVM_PAGE_DOWN, SCAN_PAGE_DOWN}, \
  { KVM_END, SCAN_END}, \
  { KVM_INSERT, SCAN_INSERT}, \
  { KVM_DELETE, SCAN_DELETE}, \
  { KVM_NPK_DELETE, SCAN_DELETE}, \
  { KVM_HOME, SCAN_HOME}, \
  { KVM_F1, SCAN_F1 }, \
  { KVM_F2, SCAN_F2 }, \
  { KVM_F3, SCAN_F3 }, \
  { KVM_F4, SCAN_F4 }, \
  { KVM_F5, SCAN_F5 }, \
  { KVM_F6, SCAN_F6 }, \
  { KVM_F7, SCAN_F7 }, \
  { KVM_F8, SCAN_F8 }, \
  { KVM_F9, SCAN_F9 }, \
  { KVM_F10, SCAN_F10 }, \
  { KVM_F11, SCAN_F11 }, \
  { KVM_F12, SCAN_F12 }, \
  { KVM_ESC, SCAN_ESC }
};

KEY_CODE_MAP UnicodeCharMap[] = {
  { KVM_BACKSPACE, CHAR_BACKSPACE }, \
  { KVM_ENTER, CHAR_CARRIAGE_RETURN }, \
  { KVM_NPK_Enter, CHAR_CARRIAGE_RETURN}, \
  { KVM_TAB, CHAR_TAB}, \
  { KVM_NPK_0, CHAR_0}, \
  { KVM_NPK_1, CHAR_1}, \
  { KVM_NPK_2, CHAR_2}, \
  { KVM_NPK_3, CHAR_3}, \
  { KVM_NPK_4, CHAR_4}, \
  { KVM_NPK_5, CHAR_5}, \
  { KVM_NPK_6, CHAR_6}, \
  { KVM_NPK_7, CHAR_7}, \
  { KVM_NPK_8, CHAR_8}, \
  { KVM_NPK_9, CHAR_9}, \
  { KVM_NPK_Decimal, CHAR_Decimal}, \
  { KVM_NPK_Add, CHAR_Add}, \
  { KVM_NPK_Subtract, CHAR_Subtract}, \
  { KVM_NPK_Multiply, CHAR_Multiply}, \
  { KVM_NPK_Divide, CHAR_Divide}
};

MAGIC_KEY_MAP MagicKeyMap[] = {
  { KVM_MAGIC_KEY_STOP, KvmStoppedMessageCallback }
};

EFI_KEY_STATE KvmKeyState = {EFI_SHIFT_STATE_VALID, EFI_TOGGLE_STATE_VALID};

VOID
KvmMagicKey(
  IN  UINT16                          KeySym,
  IN  KVM_KEYBOARD_CONSOLE_IN_DEV     *ConsoleInDev
  )
{
  UINT16 i;

  for (i = 0; i < sizeof(MagicKeyMap) / sizeof(MAGIC_KEY_MAP); ++i){
    if (MagicKeyMap[i].KvmScanCode == KeySym){
      (MagicKeyMap[i].CallBack)((VOID*)ConsoleInDev);
    }
  }
}

VOID
KvmSyncKeyboardState(
  IN  UINT16                KeySym,
  OUT EFI_KEY_STATE         *KeyState
  )
{
  switch (KeySym)
  {
  case KVM_LSHIFT:
    KvmKeyState.KeyShiftState ^= EFI_LEFT_SHIFT_PRESSED;
    break;
  case KVM_RSHIFT:
    KvmKeyState.KeyShiftState ^= EFI_RIGHT_SHIFT_PRESSED;
    break;
  case KVM_LCONTROL:
    KvmKeyState.KeyShiftState ^= EFI_LEFT_CONTROL_PRESSED;
    break;
  case KVM_RCONTROL:
    KvmKeyState.KeyShiftState ^= EFI_RIGHT_CONTROL_PRESSED;
    break;
  case KVM_LALT:
    KvmKeyState.KeyShiftState ^= EFI_LEFT_ALT_PRESSED;
    break;
  case KVM_RALT:
    KvmKeyState.KeyShiftState ^= EFI_RIGHT_ALT_PRESSED;
    break;
  case KVM_CAPS_LOCK:
    KvmKeyState.KeyToggleState ^= EFI_CAPS_LOCK_ACTIVE;
    break;
  case KVM_NPK_NUM_LOCK:
    KvmKeyState.KeyToggleState ^= EFI_NUM_LOCK_ACTIVE;
    break;
  }
  CopyMem (KeyState, &KvmKeyState, sizeof (EFI_KEY_STATE));
}

VOID
KvmScanCodeTransfer(
  IN  UINT16                KeySym,
  OUT EFI_INPUT_KEY         *Key
  )
{
  UINT16 i;

  for (i = 0; i < sizeof(ScanCodeMap) / sizeof(KEY_CODE_MAP); ++i){
    if (ScanCodeMap[i].KvmScanCode == KeySym) {
      Key->ScanCode = ScanCodeMap[i].EfiScanCode;
      Key->UnicodeChar = CHAR_NULL;
      return;
    }
  }

  for (i = 0; i < sizeof(UnicodeCharMap) / sizeof(KEY_CODE_MAP); ++i){
    if (UnicodeCharMap[i].KvmScanCode == KeySym){
      Key->UnicodeChar = UnicodeCharMap[i].EfiScanCode;
      Key->ScanCode = SCAN_NULL;
      return;
    }
  }
  Key->UnicodeChar = (KeySym > 0x7F) ? CHAR_NULL : KeySym;
  Key->ScanCode = SCAN_NULL;
}

BOOLEAN
IsKvmkeyBufEmpty (
  IN  KVM_KEY_QUEUE         *Queue
  )
{
  return (BOOLEAN) (Queue->KbBuffer->WritePointer == Queue->KbBuffer->ReadPointer);
}

EFI_STATUS
PopKvmkeyBufHead (
  IN  KVM_KEY_QUEUE                 *Queue,
  IN  KVM_KEYBOARD_CONSOLE_IN_DEV   *ConsoleInDev,
  OUT EFI_KEY_DATA                  *KeyData OPTIONAL
  )
{
  if (IsKvmkeyBufEmpty (Queue)) {
    return EFI_NOT_READY;
  }

  if (KeyData != NULL) {
    KvmSyncKeyboardState((Queue->KbBuffer->Data[Queue->KbBuffer->ReadPointer].KeySym & 0xFFFF), &(KeyData->KeyState));
    KvmScanCodeTransfer((UINT16)(Queue->KbBuffer->Data[Queue->KbBuffer->ReadPointer].KeySym & 0xFFFF), &(KeyData->Key));
    KvmMagicKey((UINT16)(Queue->KbBuffer->Data[Queue->KbBuffer->ReadPointer].KeySym & 0xFFFF), ConsoleInDev);
  }
  Queue->KbBuffer->ReadPointer = (Queue->KbBuffer->ReadPointer + 1 == KVM_KEYBOARD_KEY_MAX_COUNT) ? 0 : Queue->KbBuffer->ReadPointer + 1;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmKeyboardEfiReset (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  IN  BOOLEAN                         ExtendedVerification
  )
{
  // TODO
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardEfiReset\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmKeyboardReadKeyStroke (
  IN  EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *This,
  OUT EFI_INPUT_KEY                   *Key
  )
{
  EFI_STATUS                  Status;
  KVM_KEYBOARD_CONSOLE_IN_DEV *ConsoleIn;
  EFI_KEY_DATA                KeyData;

  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardReadKeyStroke\n");


  ConsoleIn = KVM_KEYBOARD_CONSOLE_IN_DEV_FROM_THIS (This);
  while (1) {
    Status = KvmKeyboardReadKeyStrokeWorker (ConsoleIn, &KeyData);
    if (EFI_ERROR (Status)) {
      return Status;
    }
    if (KeyData.Key.ScanCode == SCAN_NULL && KeyData.Key.UnicodeChar == CHAR_NULL) {
      continue;
    }
    CopyMem (Key, &KeyData.Key, sizeof (EFI_INPUT_KEY));
    return EFI_SUCCESS;
  }
}

EFI_STATUS
KvmKeyboardReadKeyStrokeWorker (
  IN  KVM_KEYBOARD_CONSOLE_IN_DEV       *ConsoleInDev,
  OUT EFI_KEY_DATA                      *KeyData
  )

{
  EFI_STATUS                            Status;
  EFI_TPL                               OldTpl;

  if (KeyData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Enter critical section
  //
  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  if (ConsoleInDev->KeyboardErr) {
    Status = EFI_DEVICE_ERROR;
  } else {
    Status = PopKvmkeyBufHead (&ConsoleInDev->KvmKeyQueue, ConsoleInDev, KeyData);
    IDS_HDT_CONSOLE_PSP_TRACE ("KeyData  [%x] [%x]\n", KeyData->Key.ScanCode, KeyData->Key.UnicodeChar);
    IDS_HDT_CONSOLE_PSP_TRACE ("KeyState [%x] [%x]\n", KeyData->KeyState.KeyShiftState, KeyData->KeyState.KeyToggleState);
  }

  gBS->RestoreTPL (OldTpl);
  return Status;
}

EFI_STATUS
EFIAPI
KvmKeyboardEfiResetEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  IN  BOOLEAN                           ExtendedVerification
  )
{
  // KVM_KEYBOARD_CONSOLE_IN_DEV               *ConsoleInDev;

  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardEfiResetEx\n");
  // { volatile UINTN __i; __i = 1; while (__i); }

//   ConsoleInDev = KVM_TEXT_INPUT_EX_KEYBOARD_CONSOLE_IN_DEV_FROM_THIS (This);

//   return ConsoleInDev->ConIn.Reset (
//                                &ConsoleInDev->ConIn,
//                                ExtendedVerification
//                                );
//
  return EFI_SUCCESS;
 }

EFI_STATUS
EFIAPI
KvmKeyboardReadKeyStrokeEx (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
  OUT EFI_KEY_DATA                      *KeyData
  )
{
  KVM_KEYBOARD_CONSOLE_IN_DEV               *ConsoleInDev;

  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardReadKeyStrokeEx\n");

  if (KeyData == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ConsoleInDev = KVM_TEXT_INPUT_EX_KEYBOARD_CONSOLE_IN_DEV_FROM_THIS (This);
  return KvmKeyboardReadKeyStrokeWorker (ConsoleInDev, KeyData);
}

EFI_STATUS
EFIAPI
KvmKeyboardSetState (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_TOGGLE_STATE               *KeyToggleState
  )
{
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardSetState\n");
 
 // TODO
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmKeyboardRegisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_KEY_DATA                       *KeyData,
  IN EFI_KEY_NOTIFY_FUNCTION            KeyNotificationFunction,
  OUT EFI_HANDLE                        *NotifyHandle
  )
{
  //TODO
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardRegisterKeyNotify\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmKeyboardUnregisterKeyNotify (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *This,
  IN EFI_HANDLE                         NotificationHandle
  )
{
  //TODO
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardUnregisterKeyNotify\n");

  return EFI_SUCCESS;
}

VOID
EFIAPI
KvmKeyboardWaitForKey (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  EFI_TPL                         OldTpl;
  KVM_KEYBOARD_CONSOLE_IN_DEV     *ConsoleIn;
  UINT16                          ScanCode;
  KB_RING_BUFFER                  *KbBuffer;
  EFI_KEY_DATA                    KeyData;

  ConsoleIn = (KVM_KEYBOARD_CONSOLE_IN_DEV *) Context;
  KbBuffer = ConsoleIn->KvmKeyQueue.KbBuffer;
  //
  // Enter critical section
  //
  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  if (!ConsoleIn->KeyboardErr) {
    while (!IsKvmkeyBufEmpty (&ConsoleIn->KvmKeyQueue)) {
      ScanCode = (UINT16)(KbBuffer->Data[KbBuffer->ReadPointer].KeySym & 0xFFFF);
      if (ScanCode == KVM_NULL) {
        PopKvmkeyBufHead (&ConsoleIn->KvmKeyQueue, ConsoleIn, &KeyData);
        continue;
      }
      gBS->SignalEvent (Event);
      break;
    }
  }
  //
  // Leave critical section and return
  //
  gBS->RestoreTPL (OldTpl);
}

VOID
EFIAPI
KvmKeyboardWaitForKeyEx (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  // IDS_HDT_CONSOLE_PSP_TRACE ("KvmKeyboardWaitForKeyEx\n");

  KvmKeyboardWaitForKey (Event, Context);
}

EFI_STATUS
EFIAPI
KvmStoppedMessageCallback(
  IN  VOID                    *Context
  )
{
  AmdPspKvmSetSessionProgress(0);
  gRT->ResetSystem(EfiResetWarm, EFI_SUCCESS, 0, NULL);
  return EFI_SUCCESS;
}

