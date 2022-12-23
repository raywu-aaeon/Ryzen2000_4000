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
#define FILECODE UEFI_SMM_FCHSMM_POWERBUTTONSMI_FILECODE

EFI_STATUS
FchSmmRegisterPowerButtonSmi (
  VOID
  )
{
  EFI_STATUS                              Status;
  FCH_SMM_PWRBTN_DISPATCH2_PROTOCOL       *AmdPwrBtnDispatch;
  FCH_SMM_PWRBTN_REGISTER_CONTEXT         AmdPowerButtonContext;
  EFI_HANDLE                              PowerButtonHandle;

  //
  // Register power button SMM event
  //
  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmPwrBtnDispatch2ProtocolGuid,
                  NULL,
                  &AmdPwrBtnDispatch
                  );
  ASSERT_EFI_ERROR (Status);

  AmdPowerButtonContext.Phase = EfiPowerButtonExit;
  AmdPowerButtonContext.Order = 0xFF;
  Status = AmdPwrBtnDispatch->Register (
                                AmdPwrBtnDispatch,
                                AmdSmiPowerButtonCallback,
                                &AmdPowerButtonContext,
                                &PowerButtonHandle
                                );

  AmdPowerButtonContext.Phase = EfiPowerButtonEntry;
  AmdPowerButtonContext.Order = 0x89;
  Status = AmdPwrBtnDispatch->Register (
                                AmdPwrBtnDispatch,
                                AmdSmiPowerButtonCallbackTest,
                                &AmdPowerButtonContext,
                                &PowerButtonHandle
                                );
  return Status;
}


//
// Enable sleep state transition
//
VOID
FchEnableSleepTransition ( VOID )
{
  // Set SLP_TYPEn to enable SLP_TYP to do S1/S3/S5
  RwPmio (FCH_PMIOA_REGBE, AccessWidth8, 0xFF, BIT5, NULL);

  // Enable S state transition
  RwPmio (FCH_PMIOA_REG08 + 3, AccessWidth8, (UINT32)~(BIT1 + BIT0), (UINT32) BIT0, NULL);
}


/*++

Routine Description:
  SMI handler to restore ACPI mode

Arguments:

  DispatchHandle  - The handle of this callback, obtained when registering
  DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

Returns:

  None.

--*/
EFI_STATUS
EFIAPI
AmdSmiPowerButtonCallbackTest (
  IN       EFI_HANDLE                            DispatchHandle,
  IN       CONST FCH_SMM_PWRBTN_REGISTER_CONTEXT *DispatchContext,
  IN OUT   VOID                                  *CommBuffer OPTIONAL,
  IN OUT   UINTN                                 *CommBufferSize  OPTIONAL
  )
{
  EFI_STATUS     Status;
  Status = EFI_SUCCESS;
  return Status;
}


EFI_STATUS
EFIAPI
AmdSmiPowerButtonCallback (
  IN       EFI_HANDLE                            DispatchHandle,
  IN       CONST FCH_SMM_PWRBTN_REGISTER_CONTEXT *DispatchContext,
  IN OUT   VOID                                  *CommBuffer OPTIONAL,
  IN OUT   UINTN                                 *CommBufferSize  OPTIONAL
  )
{
  EFI_STATUS     Status;
  UINT32         AcpiMmioBase;
  UINT16         AcpiPmbase;
  UINT16         Value16;

  Status = EFI_SUCCESS;

  FchEnableSleepTransition ();
//  GetFchAcpiMmioBase (&AcpiMmioBase, NULL);
  AcpiMmioBase = 0xFED80000;
  GetFchAcpiPmBase (&AcpiPmbase, NULL);
  BackUpCG2 ();
  RestoreAmbaEmmc2D0 ();

  // Turn off SLP_TYP SMI
  RwMem (AcpiMmioBase + SMI_BASE + FCH_SMI_REGB0, AccessWidth32, (UINT32)~(BIT3 + BIT2), 0);

  // Clear power button status
  Value16 = BIT8;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, AcpiPmbase + R_FCH_ACPI_PM1_STATUS, &Value16);

  // power the system off now
  LibFchSmmIoRead (&gSmst->SmmIo, SMM_IO_UINT16, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &Value16);
  Value16 &= (UINT32)~(BIT12 + BIT11 + BIT10);
  Value16 |= 5 << 10;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &Value16);
  Value16 |= BIT13;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &Value16);

  return Status;
}


