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

#include "AmdPspKvmSimpleMouse.h"

STATIC BOOLEAN mSimpleFirstTimeReset = TRUE;

EFI_STATUS
EFIAPI
KvmToEfiSimplePointerState (
  IN KVM_POINTER_STATE              *KvmPointerState,
  OUT EFI_SIMPLE_POINTER_STATE      *EfiPointerState
)
{
  EfiPointerState->RelativeMovementX = KvmPointerState->MovementX;
  EfiPointerState->RelativeMovementY = KvmPointerState->MovementY;
  EfiPointerState->RelativeMovementZ = 0;
  EfiPointerState->LeftButton = (KvmPointerState->ButtonMask & 0x1) == 0x0 ? FALSE : TRUE;
  EfiPointerState->RightButton = (KvmPointerState->ButtonMask & 0x4) == 0x0 ? FALSE : TRUE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
InitializeMsRingBufferTestPattern (
  OUT KVM_MOUSE_BUFFER           *MRingBuffer
  )
{
  UINT32 i = 0;
  MRingBuffer->Data[i++].MovementX = 0x8000;
  MRingBuffer->Data[i++].MovementY = 0x8000;
  MRingBuffer->WritePointer = i;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmSimpleMouseDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                            Status;
  KVM_MOUSE_DEV                         *MouseDev;
  EFI_TPL                               OldTpl;

  Status = EFI_SUCCESS;
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmMouseDriverStart >>\n");

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
  MouseDev = &mKvmMouseDev;
  ZeroMem (MouseDev, sizeof (KVM_MOUSE_DEV));

  MouseDev->Signature       = KVM_MOUSE_DEV_SIGNATURE;
  MouseDev->Handle          = Controller;
  MouseDev->DataPackageSize = 3;

  MouseDev->SimpleMode.ResolutionX                = 4;
  MouseDev->SimpleMode.ResolutionY                = 4;
  MouseDev->SimpleMode.ResolutionZ                = 0;
  MouseDev->SimpleMode.LeftButton                 = TRUE;
  MouseDev->SimpleMode.RightButton                = TRUE;  
  
  MouseDev->SimplePointerProtocol.Reset     = KvmSimpleMouseReset;
  MouseDev->SimplePointerProtocol.GetState  = KvmSimpleMouseGetState;
  MouseDev->SimplePointerProtocol.Mode      = &(MouseDev->SimpleMode);

  InitializeMsRingBuffer(&MouseDev->MRingBuffer);
  mMRingBuffer = MouseDev->MRingBuffer;
  // InitializeMsRingBufferTestPattern (MouseDev->MRingBuffer);
  IDS_HDT_CONSOLE_PSP_TRACE ("Kvm Mouse Buffer: Max Count %x Ptr %x\n", KVM_MOUSE_MAX_COUNT, MouseDev->MRingBuffer);

  Status = gBS->CreateEvent (
                  EVT_NOTIFY_WAIT,
                  TPL_NOTIFY,
                  KvmSimpleMouseWaitForInput,
                  MouseDev,
                  &((MouseDev->SimplePointerProtocol).WaitForInput)
                  );
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmSimpleMouseWaitForInput Event Created\n");

  MouseDev->ControllerNameTable = NULL;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gEfiSimplePointerProtocolGuid,
                  &MouseDev->SimplePointerProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("EFI_SIMPLE_POINTER_PROTOCOL Installed\n");

  // PcdSet64 (PcdKvmConInHandle, (UINT64) (UINTN) Controller);
  // gST->ConsoleInHandle = Controller;
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmMouseDriverStart<<\n");
  gBS->RestoreTPL (OldTpl);

  return EFI_SUCCESS;

ErrorExit:
  IDS_HDT_CONSOLE_PSP_TRACE ("Kvm Mouse Driver Error<<\n");

  if ((MouseDev != NULL) && (MouseDev->SimplePointerProtocol.WaitForInput != NULL)) {
    gBS->CloseEvent (MouseDev->SimplePointerProtocol.WaitForInput);
  }

  if ((MouseDev != NULL) && (MouseDev->TimerEvent != NULL)) {
    gBS->CloseEvent (MouseDev->TimerEvent);
  }

  if ((MouseDev != NULL) && (MouseDev->ControllerNameTable != NULL)) {
    FreeUnicodeStringTable (MouseDev->ControllerNameTable);
  }

  if (MouseDev != NULL) {
    FreePool (MouseDev);
  }
  gBS->RestoreTPL (OldTpl);

  return Status;
}

EFI_STATUS
EFIAPI
KvmSimpleMouseDriverStop (
  IN EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN EFI_HANDLE                    Controller,
  IN UINTN                         NumberOfChildren,
  IN EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                  Status;
  EFI_SIMPLE_POINTER_PROTOCOL *SimplePointerProtocol;
  KVM_MOUSE_DEV               *MouseDev;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiSimplePointerProtocolGuid,
                  (VOID **) &SimplePointerProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  MouseDev = KVM_MOUSE_DEV_FROM_THIS (SimplePointerProtocol);

  Status = gBS->UninstallProtocolInterface (
                  Controller,
                  &gEfiSimplePointerProtocolGuid,
                  &MouseDev->SimplePointerProtocol
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gBS->CloseEvent (MouseDev->SimplePointerProtocol.WaitForInput);
  FreeUnicodeStringTable (MouseDev->ControllerNameTable);
  FreePool (MouseDev);

  gBS->CloseProtocol (
         Controller,
         &gEfiPciIoProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmSimpleMouseReset (
  IN EFI_SIMPLE_POINTER_PROTOCOL    *This,
  IN BOOLEAN                        ExtendedVerification
  )
{
  // TODO
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
KvmSimpleMouseGetState (
  IN EFI_SIMPLE_POINTER_PROTOCOL    *This,
  IN OUT EFI_SIMPLE_POINTER_STATE   *State
  )
{
  KVM_MOUSE_DEV                     *MouseDev;
  EFI_STATUS                        Status;
  EFI_TPL                           OldTpl;

  Status = EFI_SUCCESS;
  MouseDev = KVM_MOUSE_DEV_FROM_THIS(This);

  if (mSimpleFirstTimeReset) {
    IDS_HDT_CONSOLE_PSP_TRACE ("First time reset Mouse State\n");
    Status = MouseDev->SimplePointerProtocol.Reset (
                         &MouseDev->SimplePointerProtocol,
                         TRUE
                         );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    mSimpleFirstTimeReset = FALSE;
  }

  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);
  KvmSimpleReadMouseState(MouseDev);
  if (!MouseDev->StateChanged) {
    gBS->RestoreTPL (OldTpl);
    return EFI_NOT_READY;
  }
  CopyMem (State, &(MouseDev->SimpleState), sizeof (EFI_SIMPLE_POINTER_STATE));
  //
  // clear mouse state
  //
  MouseDev->SimpleState.RelativeMovementX = 0;
  MouseDev->SimpleState.RelativeMovementY = 0;
  MouseDev->SimpleState.RelativeMovementZ = 0;
  MouseDev->StateChanged            = FALSE;
  gBS->RestoreTPL (OldTpl);
  
  return EFI_SUCCESS;
}

VOID
EFIAPI
KvmSimpleMouseWaitForInput (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  EFI_TPL       OldTpl;
  KVM_MOUSE_DEV *MouseDev;

  MouseDev = (KVM_MOUSE_DEV *) Context;
  OldTpl = gBS->RaiseTPL (TPL_NOTIFY);

  if (!IsKvmMouseBufEmpty(MouseDev->MRingBuffer)) {
    gBS->SignalEvent (Event);
  }
  gBS->RestoreTPL (OldTpl);
}

VOID
EFIAPI
KvmSimpleReadMouseState (
  IN KVM_MOUSE_DEV       *MouseDev
  )
{
  if (IsKvmMouseBufEmpty(MouseDev->MRingBuffer) || MouseDev->StateChanged) {
    return;
  }
  KvmToEfiSimplePointerState(&(MouseDev->MRingBuffer->Data[MouseDev->MRingBuffer->ReadPointer]),&(MouseDev->SimpleState));
  KvmGetNextPointer (&(MouseDev->MRingBuffer->ReadPointer));
  MouseDev->StateChanged = TRUE;
}

