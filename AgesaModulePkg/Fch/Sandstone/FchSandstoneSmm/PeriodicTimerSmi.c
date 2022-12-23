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
#include "FchSmm.h"
#define FILECODE UEFI_SMM_FCHSMM_PERIODICTIMERSMI_FILECODE

extern FCH_DATA_BLOCK                      gFchDataInSmm;

UINT32 mShortTimerCounter;
UINT32 mLongTimerCounter;

/*++

Routine Description:
  Handler for LongTimer SMI

Arguments:

  DispatchHandle  - The handle of this callback, obtained when registering
  RegisterContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

Returns:

  None.

--*/
EFI_STATUS
EFIAPI
AmdSmiLongTimerCallback (
  IN       EFI_HANDLE                                DispatchHandle,
  IN       CONST FCH_SMM_PERIODICAL_REGISTER_CONTEXT *RegisterContext,
  IN OUT   EFI_SMM_PERIODIC_TIMER_CONTEXT            *PeriodicTimerContext,
  IN OUT   UINTN                                     *SizeOfContext
  )
{
  //LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, 0x80, &mLongTimerCounter);
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &mLongTimerCounter);
  mLongTimerCounter++;
  return EFI_SUCCESS;
}


/*++

Routine Description:
  Handler for ShortTimer SMI

Arguments:

  DispatchHandle  - The handle of this callback, obtained when registering
  RegisterContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

Returns:

  None.

--*/
EFI_STATUS
EFIAPI
AmdSmiShortTimerCallback (
  IN       EFI_HANDLE                                DispatchHandle,
  IN       CONST FCH_SMM_PERIODICAL_REGISTER_CONTEXT *RegisterContext,
  IN OUT   EFI_SMM_PERIODIC_TIMER_CONTEXT            *PeriodicTimerContext,
  IN OUT   UINTN                                     *SizeOfContext
  )
{
  //LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, 0x80, &mShortTimerCounter);
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &mShortTimerCounter);
  mShortTimerCounter++;
  return EFI_SUCCESS;
}


EFI_STATUS
FchSmmRegisterPeriodicTimerSmi (
  VOID
  )
{
  EFI_STATUS                              Status;
  FCH_SMM_PERIODICAL_DISPATCH2_PROTOCOL   *AmdPeriodicalDispatch;
  FCH_SMM_PERIODICAL_REGISTER_CONTEXT     PeriodicalRegisterContext;
  EFI_HANDLE                              PtHandle;
  FCH_MISC                                *FchMisc;

  FchMisc = &gFchDataInSmm.Misc;

  //
  // Periodic Timer SMI Registration
  //
  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmPeriodicalDispatch2ProtocolGuid,
                  NULL,
                  &AmdPeriodicalDispatch
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Due to the post code limitation, we choose to turn on LongTimer and ShortTimer SMIs exclusively.
  // If both are set to enable in setup, we only register the LongTimer SMI.
  //
  if (FchMisc->LongTimer.Enable) {
    PeriodicalRegisterContext.SmiTickInterval  = LONG_TIMER_SMI_INTERVAL;
    PeriodicalRegisterContext.Period           = FchMisc->LongTimer.CycleDuration * LONG_TIMER_SMI_INTERVAL;
    PeriodicalRegisterContext.StartNow         = FchMisc->LongTimer.StartNow;
    mLongTimerCounter = 0;
    Status = AmdPeriodicalDispatch->Register (
                                      AmdPeriodicalDispatch,
                                      AmdSmiLongTimerCallback,
                                      &PeriodicalRegisterContext,
                                      &PtHandle
                                      );
  } else if (FchMisc->ShortTimer.Enable) {
    PeriodicalRegisterContext.SmiTickInterval  = SHORT_TIMER_SMI_INTERVAL;
    PeriodicalRegisterContext.Period           = (FchMisc->ShortTimer.CycleDuration >> 1) * SHORT_TIMER_SMI_INTERVAL;
    PeriodicalRegisterContext.StartNow         = FchMisc->ShortTimer.StartNow;
    mShortTimerCounter = 0;
    Status = AmdPeriodicalDispatch->Register (
                                      AmdPeriodicalDispatch,
                                      AmdSmiShortTimerCallback,
                                      &PeriodicalRegisterContext,
                                      &PtHandle
                                      );
  }
  return Status;
}



