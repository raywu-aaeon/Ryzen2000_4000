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
#define FILECODE UEFI_SMM_FCHSMM_SWSMI_FILECODE

extern FCH_DATA_BLOCK                  gFchDataInSmm;
extern UINT8                           *mFchPciIrqRoutingTable;


UINT16
FchGetPmBase (
  VOID
  )
{
  UINT8       Lsb;
  UINT8       Msb;

  LibFchSmmPmioRead8 (&gSmst->SmmIo, FCH_PMIOA_REG60, &Lsb);
  LibFchSmmPmioRead8 (&gSmst->SmmIo, FCH_PMIOA_REG60 + 1, &Msb);
  return (UINT16) ((Msb << 8) + Lsb);
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
AmdSmiBeforePciS3RestoreCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  EFI_STATUS          Status;
  UINT8               Index;
  UINT8               *pData;

  Status = EFI_SUCCESS;

  // Restore entire FCH PCI IRQ routing space (C00/C01)
  pData = mFchPciIrqRoutingTable;
  Index = 0xFF;
  do {
    Index++;
    LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC00, &Index);
    LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC01, pData++);
  } while (Index != 0xFF);

  pFchPolicy = &gFchDataInSmm;
  FchInitS3EarlyRestore (pFchPolicy);
  return Status;
}

EFI_STATUS
EFIAPI
AmdSmiAfterPciS3RestoreCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  EFI_STATUS          Status;

  Status = EFI_SUCCESS;
  pFchPolicy = &gFchDataInSmm;
  FchInitS3LateRestore (pFchPolicy);
  return Status;
}


EFI_STATUS
EFIAPI
AmdSmiAcpiOnCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  UINT16              AcpiPmbase;
  UINT8               dbIndex;
  UINT8               dbIrq;
  UINT32              ddValue;

  AcpiPmbase = FchGetPmBase ();

  pFchPolicy = &gFchDataInSmm;
  FchSmmAcpiOn (pFchPolicy);

  // Disable all GPE events and clear all GPE status
  ddValue = 0;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT32, AcpiPmbase + R_FCH_ACPI_EVENT_ENABLE, &ddValue);
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT32, AcpiPmbase + R_FCH_ACPI_EVENT_STATUS, &ddValue);

  // Set ACPI IRQ to IRQ9 for non-APIC OSes
  dbIndex = 0x10;                                          // PIC - SCI
  dbIrq = 9;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC00, &dbIndex);
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC01, &dbIrq);

  dbIndex |= BIT7;                                         // IOAPIC - SCI
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC00, &dbIndex);
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, FCH_IOMAP_REGC01, &dbIrq);

  // Finally enable SCI
  LibFchSmmIoRead (&gSmst->SmmIo, SMM_IO_UINT32, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &ddValue);
  ddValue |= BIT0;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT32, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &ddValue);

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
AmdSmiAcpiOffCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  UINT16      AcpiPmbase;
  UINT32      ddValue;

  AcpiPmbase = FchGetPmBase ();

  // Turn off SCI
  LibFchSmmIoRead (&gSmst->SmmIo, SMM_IO_UINT32, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &ddValue);
  ddValue &= ~BIT0;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT32, AcpiPmbase + R_FCH_ACPI_PM_CONTROL, &ddValue);

  return EFI_SUCCESS;
}

#ifdef FCH_SPI_PROTECT_SMI
EFI_STATUS
EFIAPI
AmdSmiSpiUnlockCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  EFI_STATUS          Status;

  Status = EFI_SUCCESS;
  pFchPolicy = &gFchDataInSmm;
  FchSpiUnlock (pFchPolicy);
  return Status;
}

EFI_STATUS
EFIAPI
AmdSmiSpiLockCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  FCH_DATA_BLOCK      *pFchPolicy;
  EFI_STATUS          Status;

  Status = EFI_SUCCESS;
  pFchPolicy = &gFchDataInSmm;
  FchSpiLock (pFchPolicy);
  return Status;
}
#endif

STATIC UINT8          SavePort80 = 0x00;

EFI_STATUS
EFIAPI
AmdStartTimerSmiCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  SavePort80 = ACPIMMIO8 (ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG44);

  ACPIMMIO16 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG96) |= SMI_TIMER_ENABLE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdStopTimerSmiCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  ACPIMMIO16 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG96) &= ~SMI_TIMER_ENABLE;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &SavePort80);
  return EFI_SUCCESS;
}




EFI_STATUS
FchSmmRegisterSwSmi (
  VOID
  )
{
  EFI_STATUS                               Status;
  FCH_SMM_SW_DISPATCH2_PROTOCOL            *AmdSwDispatch;
  FCH_SMM_SW_REGISTER_CONTEXT              SwRegisterContext;
  EFI_HANDLE                               SwHandle;
  FCH_MISC                                 *FchMisc;

  FchMisc = &gFchDataInSmm.Misc;

  //
  //  Locate SMM SW dispatch protocol
  //
  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmSwDispatch2ProtocolGuid,
                  NULL,
                  &AmdSwDispatch
                  );
  ASSERT_EFI_ERROR (Status);

  SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemBeforePciRestoreSwSmi); // use of PCD in place of FCHOEM_BEFORE_PCI_RESTORE_SWSMI    0xD3
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiBeforePciS3RestoreCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemAfterPciRestoreSwSmi); // use of PCD in place of FCHOEM_AFTER_PCI_RESTORE_SWSMI    0xD4
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiAfterPciS3RestoreCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemEnableAcpiSwSmi); // use of PCD in place of FCHOEM_ENABLE_ACPI_SWSMI           0xA0
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiAcpiOnCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemDisableAcpiSwSmi); // use of PCD in place of FCHOEM_DISABLE_ACPI_SWSMI          0xA1
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiAcpiOffCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }

#ifdef FCH_SPI_PROTECT_SMI
  SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemSpiUnlockSwSmi); // use of PCD in place of FCHOEM_SPI_UNLOCK_SWSMI            0xAA
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiSpiUnlockCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemSpiLockSwSmi); // use of PCD in place of FCHOEM_SPI_LOCK_SWSMI              0xAB
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiSpiLockCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }
#endif

  if (FchMisc->LongTimer.Enable || FchMisc->ShortTimer.Enable) {
    SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemStartTimerSmi); // use of PCD in place of FCHOEM_START_TIMER_SMI             0xBC
    SwRegisterContext.Order       = 0x80;
    Status = AmdSwDispatch->Register (
                              AmdSwDispatch,
                              AmdStartTimerSmiCallback,
                              &SwRegisterContext,
                              &SwHandle
                              );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    SwRegisterContext.AmdSwValue  = PcdGet8(PcdFchOemStopTimerSmi); // use of PCD in place of FCHOEM_STOP_TIMER_SMI              0xBD
    SwRegisterContext.Order       = 0x80;
    Status = AmdSwDispatch->Register (
                              AmdSwDispatch,
                              AmdStopTimerSmiCallback,
                              &SwRegisterContext,
                              &SwHandle
                              );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}


