/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdPspKvmMouse.h
 *
 * Contains definition for AmdPspKvmMouse
 *
 */
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
 **/
#ifndef _AMD_PSP_KVM_MOUSE_H_
#define _AMD_PSP_KVM_MOUSE_H_

#include <Protocol/SimplePointer.h>
#include <Protocol/AbsolutePointer.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/PciLib.h>
#include <Library/DebugLib.h>


#include <AGESA.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspMboxLibV2.h>
#include <Protocol/AmdPspKvmServiceProtocol.h>

#define KVM_LEFT_CLICK_MASK           0x1;
#define KVM_MIDDLE_CLICK_MASK         0x2;
#define KVM_RIGHT_CLICK_MASK          0x4;
#define KVM_SCROLL_UP_MASK            0x8;
#define KVM_SCROLL_DOWN_MASK          0x10;

// #define KVM_POINTER_STATE           EFI_SIMPLE_POINTER_STATE
#define KVM_MOUSE_BUFFER_SIZE         (32 * 1024) // 32KB Keyboard Buffer
#define KVM_MOUSE_DATA_BUFFER_SIZE    (KVM_MOUSE_BUFFER_SIZE - 2 * sizeof(UINT32))
#define KVM_MOUSE_MAX_COUNT           KVM_MOUSE_DATA_BUFFER_SIZE / sizeof(KVM_POINTER_STATE)

typedef struct {
  UINT32                              ButtonMask; //1=Left click, 2=Middle/Scroll click, 4=Right click, 8=Scroll up, 16=Scroll down
  UINT32                              MovementX;
  UINT32                              MovementY;
} KVM_POINTER_STATE;


typedef struct {
  UINT32                              WritePointer;
  UINT32                              ReadPointer;
  KVM_POINTER_STATE                   Data[KVM_MOUSE_MAX_COUNT];
} KVM_MOUSE_BUFFER;

#define KVM_MOUSE_DEV_SIGNATURE     SIGNATURE_32 ('k', 'v', 'm', 'm')

typedef struct {
  UINTN                               Signature;

  EFI_HANDLE                          Handle;
  EFI_SIMPLE_POINTER_PROTOCOL         SimplePointerProtocol;
  EFI_SIMPLE_POINTER_STATE            SimpleState;
  EFI_SIMPLE_POINTER_MODE             SimpleMode;

  EFI_ABSOLUTE_POINTER_PROTOCOL       AbsolutePointerProtocol;
  EFI_ABSOLUTE_POINTER_STATE          AbsoluteState;
  EFI_ABSOLUTE_POINTER_MODE           AbsoluteMode;

  BOOLEAN                             StateChanged;

  UINT8                               DataPackageSize;
  KVM_MOUSE_BUFFER                    *MRingBuffer;

  EFI_EVENT                           TimerEvent;

  EFI_UNICODE_STRING_TABLE            *ControllerNameTable;
} KVM_MOUSE_DEV;


KVM_MOUSE_DEV           mKvmMouseDev;
KVM_MOUSE_BUFFER        *mMRingBuffer;

EFI_STATUS
EFIAPI
KvmAbsoluteMouseDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
KvmAbsoluteMouseDriverStop (
  IN EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN EFI_HANDLE                    Controller,
  IN UINTN                         NumberOfChildren,
  IN EFI_HANDLE                    *ChildHandleBuffer
  );

EFI_STATUS
EFIAPI
KvmSimpleMouseDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  );


EFI_STATUS
EFIAPI
KvmSimpleMouseDriverStop (
  IN EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN EFI_HANDLE                    Controller,
  IN UINTN                         NumberOfChildren,
  IN EFI_HANDLE                    *ChildHandleBuffer
  );

BOOLEAN
IsKvmMouseBufEmpty (
  IN  KVM_MOUSE_BUFFER        *MRingBuffer
  );

EFI_STATUS
EFIAPI
InitializeMsRingBuffer (
  IN OUT KVM_MOUSE_BUFFER           **MRingBuffer
  );

VOID
EFIAPI
KvmGetNextPointer(
  IN OUT UINT32          *Pointer
  );

#endif
