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
#include "GnbDxio.h"
#include <Library/NbioSmuV10Lib.h>
#define FILECODE UEFI_SMM_FCHSMM_SXSMI_FILECODE

extern  UINT8                        *mFchPciIrqRoutingTable;
extern FCH_DATA_BLOCK                      gFchDataInSmm;

EFI_STATUS
FchSmmRegisterSxSmi (
  VOID
  )
{
  EFI_STATUS                               Status;
  FCH_SMM_SX_DISPATCH2_PROTOCOL            *AmdSxDispatch;
  FCH_SMM_SX_REGISTER_CONTEXT              SxRegisterContext;
  EFI_HANDLE                               SxHandle;

  //
  // Register AMD SX SMM
  //
  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmSxDispatch2ProtocolGuid,
                  NULL,
                  &AmdSxDispatch
                  );
  ASSERT_EFI_ERROR (Status);

  SxRegisterContext.Type  = SxS3;
  SxRegisterContext.Phase = SxEntry;
  SxRegisterContext.Order = 0xC0;

  Status = AmdSxDispatch->Register (
                             AmdSxDispatch,
                             AmdSmiS3SleepEntryCallback,
                             &SxRegisterContext,
                             &SxHandle
                             );

  SxRegisterContext.Type  = SxS4;
  SxRegisterContext.Phase = SxEntry;
  SxRegisterContext.Order = 0xC0;

  Status = AmdSxDispatch->Register (
                             AmdSxDispatch,
                             AmdSmiS4SleepEntryCallback,
                             &SxRegisterContext,
                             &SxHandle
                             );

  SxRegisterContext.Type  = SxS5;
  SxRegisterContext.Phase = SxEntry;
  SxRegisterContext.Order = 0xC0;

  Status = AmdSxDispatch->Register (
                             AmdSxDispatch,
                             AmdSmiS5SleepEntryCallback,
                             &SxRegisterContext,
                             &SxHandle
                             );

  return Status;
}

/**
 * FixPsp4Ehang
 *
 *
 * @retval  VOID
 *
 */
VOID
FixPsp4Ehang (
  OUT VOID
  )
{
  UINT8          Value8;
  UINT32          IoApicNumber;
  AMD_CONFIG_PARAMS      *StdHeader;
  FCH_DATA_BLOCK      *pFchPolicy;

  pFchPolicy = &gFchDataInSmm;
  StdHeader = pFchPolicy->StdHeader;

  ACPIMMIO32 (FCH_AOACx94S0I3_CONTROL) |= FCH_AOACx94S0I3_CONTROL_ARBITER_DIS + FCH_AOACx94S0I3_CONTROL_INTERRUPT_DIS;
  ACPIMMIO32 (0xFEC00000) = 0x3E;
  ACPIMMIO32 (0xFEC00010) = 0xFF;
  LibAmdIoRead (AccessWidth8, FCH_IOMAP_REGED, &Value8, StdHeader);
  ACPIMMIO32 (0xFEC00020) = 0x17;
  LibAmdIoRead (AccessWidth8, FCH_IOMAP_REGED, &Value8, StdHeader);
  IoApicNumber = ACPIMMIO32 (0xFEC00020);

  for (IoApicNumber = 0; IoApicNumber < 24; IoApicNumber++) {
    ACPIMMIO32 (0xFEC00000) = 0x10 + (IoApicNumber << 1);
    ACPIMMIO32 (0xFEC00010) = BIT16;
  }
  // put eMMC into D0 if it is D0 
    ACPIMMIO32 (0xFED81E78) |= BIT3;
    ACPIMMIO32 (0xFED81E78) &= ~ 0x3;
}

/*++

Routine Description:


Arguments:

  DispatchHandle  - The handle of this callback, obtained when registering
  DispatchContext - Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT

Returns:

  None.

--*/
EFI_STATUS
EFIAPI
AmdSmiS3SleepEntryCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SX_REGISTER_CONTEXT *DispatchContext,
  IN OUT   VOID                              *CommBuffer OPTIONAL,
  IN OUT   UINTN                             *CommBufferSize  OPTIONAL
  )
{
  UINT8          Index;
  UINT8          *pData;
  FCH_DATA_BLOCK      *pFchPolicy;
  pFchPolicy = &gFchDataInSmm;
  // Save entire FCH PCI IRQ routing space (C00/C01)
  pData = mFchPciIrqRoutingTable;
  Index = 0xFF;
  do {
    Index++;
    LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC00, &Index);
    LibFchSmmIoRead (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC01, pData++);
  } while (Index != 0xFF);

  BackUpCG2 ();
  FixPsp4Ehang ();
  FchRVUsb3InitS3EntryProgram (pFchPolicy);
  ProgramPMEDis (0, FALSE);
  RestoreAmbaEmmc2D0 ();
  if (pFchPolicy->FchRunTime.FchDeviceEnableMap & BIT28) {
    ProgramLpcEmmcPins (FALSE);
  }
  if (pFchPolicy->HwAcpi.FchSxEntryXhciPmeEn) {
    ProgramXhciPmeEn(pFchPolicy);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdSmiS4SleepEntryCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SX_REGISTER_CONTEXT *DispatchContext,
  IN OUT   VOID                              *CommBuffer OPTIONAL,
  IN OUT   UINTN                             *CommBufferSize  OPTIONAL
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  pFchPolicy = &gFchDataInSmm;

  BackUpCG2 ();
  FixPsp4Ehang ();
  FchRVUsb3InitS3EntryProgram (pFchPolicy);
  ProgramPMEDis (0, FALSE);
  RestoreAmbaEmmc2D0 ();
  if (pFchPolicy->FchRunTime.FchDeviceEnableMap & BIT28) {
    ProgramLpcEmmcPins (FALSE);
  }
  if (pFchPolicy->HwAcpi.FchSxEntryXhciPmeEn) {
    ProgramXhciPmeEn(pFchPolicy);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdSmiS5SleepEntryCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SX_REGISTER_CONTEXT *DispatchContext,
  IN OUT   VOID                              *CommBuffer OPTIONAL,
  IN OUT   UINTN                             *CommBufferSize  OPTIONAL
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  pFchPolicy = &gFchDataInSmm;
  BackUpCG2 ();
  //RwMem (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG04 + 2, AccessWidth8, ~BIT3, BIT3);
  FixPsp4Ehang ();
  FchRVUsb3InitS3EntryProgram (pFchPolicy);
  RestoreAmbaEmmc2D0 ();
  if (pFchPolicy->FchRunTime.FchDeviceEnableMap & BIT28) {
    ProgramLpcEmmcPins (FALSE);
  }
  return EFI_SUCCESS;
}

