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
#include "FchSSSataD3ColdSmm.h"

EFI_STATUS
EFIAPI
AmdSmiSataD3ColdEntryCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  UINT8               Debug;
  UINT32              SmuArg[6];
  UINT32              SmuRequestId;
  UINT32              SmuResponse;
  PCI_ADDR            NbioPciAddress;

  Debug = 0x78;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &Debug);

  // 1, set DEVSLP PAD value
  FchSataD3ColdOverrideDevSlpPad ();
  // 2, put sata into offline mode.
  FchSataD3ColdOfflineMode ();
  // 3, save registers.
  FchSataD3ColdSaveRegisters ();
  // 4, polling each port already enter into offline mode.
  FchSataD3ColdPollingOffline ();
  // 5, Block reset from PCS to PHY.
  FchSataD3ColdBlockReset ();
  // 6, call SMU for D3Cold Entry.
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = MAKE_SBDFO (0, 0, 0, 0, 0);
  SmuArg[0] = 0x1;
  SmuRequestId = SMC_MSG_PowerDownSata;

  SmuResponse = NbioSmuServiceRequestV10 (NbioPciAddress, SmuRequestId, SmuArg, 0);

  //FchSataD3ColdPowerDown ();

  Debug = 0x79;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &Debug);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdSmiSataD3ColdExitCallback (
  IN       EFI_HANDLE                        DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT                *SwContext,
  IN OUT   UINTN                             *SizeOfSwContext
  )
{
  UINT8               Debug;
  UINT32              SmuArg[6];
  UINT32              SmuRequestId;
  UINT32              SmuResponse;
  PCI_ADDR            NbioPciAddress;

  Debug = 0x89;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &Debug);

  //000 check if we're in D3Cold
  if (FchSataD3ColdClockOn ()) {
    return EFI_SUCCESS;
  }

  //1, Enable FCH_SATA_100M_CLK: SW programs ACPI MISC_REG 0x4C[16]=1
  FchSataD3ColdEnable100MClk ();
  //2, Remove DEVSLP PAD override value: SW program ACPI PMIO_0xDC[1:0] to 2'b00
  FchSataD3ColdRemoveOverrideDevSlpPad ();
  //3, Set D3 resume indication signal and block OOB: SW program LOCAL_RSMU_Reg: 04h[10] = 1
  FchSataD3ColdBlockOOB ();
  //4, call SMU for D3Cold Exit.
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = MAKE_SBDFO (0, 0, 0, 0, 0);
  SmuArg[0] = 0x1;
  SmuRequestId = SMC_MSG_PowerUpSata;

  SmuResponse = NbioSmuServiceRequestV10 (NbioPciAddress, SmuRequestId, SmuArg, 0);

  //FchSataD3ColdPowerUp ();

  //5, Restore Sata registers
  FchSataD3ColdRestoreRegisters ();
  //6, Unblock reset from PCS to PHY: SW programs LOCAL_RSMU_Reg: 04h[11] = 0
  FchSataD3ColdUnBlockReset ();
  //7, De-assert D3 resume indication signal and un-block OOB: SW program SATA LOCAL_RSMU_Reg: 04h[10] = 0
  FchSataD3ColdUnBlockOOB ();
  Debug = 0x8A;
  LibFchSmmIoWrite (&gSmst->SmmIo, SMM_IO_UINT8, 0x80, &Debug);

  return EFI_SUCCESS;
}

/*********************************************************************************
 * Name: FchSataD3ColdSmmEntryPoint
 *
 * Description
 *   Entry point of the SataD3Cold SMM driver
 *   copy FCH_INIT_PROTOCOL to SMM, and register Fch Smm callbacks
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
FchSataD3ColdSmmEntryPoint (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )

{
  EFI_STATUS                               Status;
  FCH_SMM_SW_DISPATCH2_PROTOCOL            *AmdSwDispatch;
  FCH_SMM_SW_REGISTER_CONTEXT              SwRegisterContext;
  EFI_HANDLE                               SwHandle;
  UINT32                                   RTD3ColdEnableMap;

  Status = EFI_SUCCESS;
  RTD3ColdEnableMap = PcdGet32 (FchRTD3ColdEnableMap);

  if ((RTD3ColdEnableMap & BIT15) == 0) {
    return Status;
  }

  //
  //  Locate SMM SW dispatch protocol
  //
  Status = gSmst->SmmLocateProtocol (
             &gFchSmmSwDispatch2ProtocolGuid,
             NULL,
             &AmdSwDispatch
             );
  ASSERT_EFI_ERROR (Status);

  SwRegisterContext.AmdSwValue  = PcdGet8 (PcdFchSataD3EntrySwSmi);
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiSataD3ColdEntryCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SwRegisterContext.AmdSwValue  = PcdGet8 (PcdFchSataD3ExitSwSmi);
  SwRegisterContext.Order       = 0x80;
  Status = AmdSwDispatch->Register (
                            AmdSwDispatch,
                            AmdSmiSataD3ColdExitCallback,
                            &SwRegisterContext,
                            &SwHandle
                            );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  return Status;
}


