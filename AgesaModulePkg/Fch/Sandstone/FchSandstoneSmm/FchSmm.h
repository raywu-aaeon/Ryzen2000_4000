/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH SMM Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   FCH SMM Driver
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
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
 */

#ifndef _FCH_SMM_DRIVER_H_
#define _FCH_SMM_DRIVER_H_

#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciIo.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmReadyToBoot.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/debugLib.h>

#include <Protocol/FchSmmSwDispatch2.h>
#include <Protocol/FchSmmSxDispatch2.h>
#include <Protocol/FchSmmPwrBtnDispatch2.h>
#include <Protocol/FchSmmPeriodicalDispatch2.h>
#include <Protocol/FchSmmGpiDispatch2.h>
#include <Protocol/FchSmmMiscDispatch.h>
#include <Protocol/FchSmmIoTrapDispatch2.h>
#include <Protocol/FchSmmUsbDispatch2.h>
#include <Protocol/FchInitProtocol.h>

#include <Library/FchSmmLib.h>
#include "FchPlatform.h"

EFI_STATUS
EFIAPI
AmdSmiAcpiOnCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN CONST FCH_SMM_SW_REGISTER_CONTEXT       *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  );

EFI_STATUS
EFIAPI
AmdSmiAcpiOnCallback2 (
  IN  EFI_HANDLE                       DispatchHandle,
  IN  FCH_SMM_SW_REGISTER_CONTEXT      *DispatchContext,
  IN  FCH_SMM_SW_CONTEXT               *EfiSmmSwContext,
  IN  UINTN                            *SizeOfEfiSmmSwContext
  );

EFI_STATUS
EFIAPI
AmdSmiAcpiOffCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN CONST FCH_SMM_SW_REGISTER_CONTEXT       *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  );

#ifdef FCH_SPI_PROTECT_SMI
  EFI_STATUS
  EFIAPI
  AmdSmiSpiUnlockCallback (
    IN       EFI_HANDLE                        DispatchHandle,
    IN CONST FCH_SMM_SW_REGISTER_CONTEXT       *DispatchContext,
    IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
    IN OUT   UINTN                             *SizeOfSwContext
  );

  EFI_STATUS
  EFIAPI
  AmdSmiSpiLockCallback (
    IN       EFI_HANDLE                        DispatchHandle,
    IN CONST FCH_SMM_SW_REGISTER_CONTEXT       *DispatchContext,
    IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
    IN OUT   UINTN                             *SizeOfSwContext
  );
#endif

VOID
FchSmmAcpiOn (
  IN      FCH_DATA_BLOCK   *FchDataPtr
  );

VOID
FchInitS3EarlyRestore (
  IN      FCH_DATA_BLOCK     *FchDataPtr
  );

VOID
FchInitS3LateRestore (
  IN      FCH_DATA_BLOCK     *FchDataPtr
  );

EFI_STATUS
EFIAPI
AmdSmiBeforePciS3RestoreCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN CONST FCH_SMM_SW_REGISTER_CONTEXT       *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
);

EFI_STATUS
EFIAPI
AmdSmiAfterPciS3RestoreCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN CONST FCH_SMM_SW_REGISTER_CONTEXT       *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
);

EFI_STATUS
EFIAPI
AmdSmiPowerButtonCallback (
  IN       EFI_HANDLE                       DispatchHandle,
  IN CONST FCH_SMM_PWRBTN_REGISTER_CONTEXT  *DispatchContext,
  IN OUT   VOID                             *CommBuffer OPTIONAL,
  IN OUT   UINTN                            *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
AmdSmiPowerButtonCallbackTest (
  IN       EFI_HANDLE                       DispatchHandle,
  IN CONST FCH_SMM_PWRBTN_REGISTER_CONTEXT  *DispatchContext,
  IN OUT   VOID                             *CommBuffer OPTIONAL,
  IN OUT   UINTN                            *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
AmdSmiS3SleepEntryCallback (
  IN       EFI_HANDLE                       DispatchHandle,
  IN CONST FCH_SMM_SX_REGISTER_CONTEXT      *DispatchContext,
  IN OUT   VOID                             *CommBuffer OPTIONAL,
  IN OUT   UINTN                            *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
AmdSmiS4SleepEntryCallback (
  IN       EFI_HANDLE                       DispatchHandle,
  IN CONST FCH_SMM_SX_REGISTER_CONTEXT      *DispatchContext,
  IN OUT   VOID                             *CommBuffer OPTIONAL,
  IN OUT   UINTN                            *CommBufferSize  OPTIONAL
  );

EFI_STATUS
EFIAPI
AmdSmiS4SleepEntryCallback2 (
  IN  EFI_HANDLE                       DispatchHandle,
  IN  FCH_SMM_SX_REGISTER_CONTEXT      *DispatchContext,
  IN OUT   VOID                        *CommBuffer,
  IN OUT   UINTN                       *CommBufferSize
  );

EFI_STATUS
EFIAPI
AmdSmiS5SleepEntryCallback (
  IN       EFI_HANDLE                       DispatchHandle,
  IN CONST FCH_SMM_SX_REGISTER_CONTEXT      *DispatchContext,
  IN OUT   VOID                             *CommBuffer OPTIONAL,
  IN OUT   UINTN                            *CommBufferSize  OPTIONAL
  );


EFI_STATUS
EFIAPI
AmdMiscFchGppHpSmiCallback (
  IN  EFI_HANDLE                        DispatchHandle,
  IN  FCH_SMM_MISC_REGISTER_CONTEXT     *DispatchContext
  );

#ifdef FCH_TIMER_TICK_INTERVAL_WA
  EFI_STATUS
  EFIAPI
  AmdMiscFchHpetIntervalCallback (
    IN  EFI_HANDLE                        DispatchHandle,
    IN  FCH_SMM_MISC_REGISTER_CONTEXT     *DispatchContext
  );

  EFI_STATUS
  EFIAPI
  AmdMiscFchIrq2TrapCallback (
    IN  EFI_HANDLE                        DispatchHandle,
    IN  FCH_SMM_MISC_REGISTER_CONTEXT     *DispatchContext
  );
#endif


EFI_STATUS
EFIAPI
FchUsbBeforeOCcallback (
  IN  EFI_HANDLE                        DispatchHandle,
  IN  FCH_SMM_USB_REGISTER_CONTEXT      *DispatchContext
  );

EFI_STATUS
FchSmmRegisterSwSmi (
  VOID
  );

EFI_STATUS
FchSmmRegisterPeriodicTimerSmi (
  VOID
  );

EFI_STATUS
FchSmmRegisterGpiSmi (
  VOID
  );

EFI_STATUS
FchSmmRegisterPowerButtonSmi (
  VOID
  );

EFI_STATUS
FchSmmRegisterSxSmi (
  VOID
  );

VOID
FchEnableSleepTransition (
  VOID
  );

EFI_STATUS
FchSmmRegisterMiscSmi (
  VOID
  );

EFI_STATUS
FchSmmRegisterIoTrapSmi (
  VOID
  );

EFI_STATUS
RegisterUsbPatchSmi (
  VOID
  );

EFI_STATUS
FchSmmRegisterEhciDebugport (
  VOID
  );

EFI_STATUS
EFIAPI
FchSmmRTBCallBack (
  IN CONST EFI_GUID                       *Protocol,
  IN VOID                                 *Interface,
  IN EFI_HANDLE                           Handle
);

EFI_STATUS
FchSmmCopyOemTable (
  VOID
);
#endif

