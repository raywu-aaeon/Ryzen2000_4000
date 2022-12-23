/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#include <AmdCpmPei.h>


EFI_STATUS
EFIAPI
AmdCpmEcInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mCpmEcInitPeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCpmGpioInitFinishedPpiGuid,
  AmdCpmEcInitPeim
};

EFI_STATUS
EFIAPI
AmdCpmEcInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  EFI_STATUS              Status;
  AMD_CPM_EC_INIT_TABLE   *EcInitTablePtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  AMD_CPM_TABLE_PPI       *CpmTablePpiPtr;
  UINT8                   Data;

  Status = (*PeiServices)->LocatePpi (
                                      (CPM_PEI_SERVICES**)PeiServices,
                                      &gAmdCpmTablePpiGuid,
                                      0,
                                      NULL,
                                      (VOID**)&CpmTablePpiPtr
                                      );
  if (EFI_ERROR (Status)) {
    return  Status;
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpEcInitPeimDriverBegin);

  MainTablePtr    = CpmTablePpiPtr->MainTablePtr;
  EcInitTablePtr  = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_EC_INIT);

  if (EcInitTablePtr) {

    Data = (UINT8) MainTablePtr->Ec.Config.AcDcSwitchEn << 7;
    Status = CpmTablePpiPtr->CommonFunction.KbcWrite (0x60, 0xEA, &Data);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    if (MainTablePtr->Ec.Config.AcDcSwitchEn) {
      Data = EcInitTablePtr->AcTimer;
      Status = CpmTablePpiPtr->CommonFunction.KbcWrite (0x60, 0xEB, &Data);
      if (EFI_ERROR (Status)) {
        return Status;
      }

      Data = EcInitTablePtr->DcTimer;
      Status = CpmTablePpiPtr->CommonFunction.KbcWrite (0x60, 0xEC, &Data);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }

    if (MainTablePtr->Ec.Config.ColdBootCyclingEn) {
      Data = EcInitTablePtr->OnTimer;
      Status = CpmTablePpiPtr->CommonFunction.KbcWrite (0x60, 0xEF, &Data);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
    Data = (UINT8)MainTablePtr->Ec.Config.ColdBootCyclingEn;
    Status = CpmTablePpiPtr->CommonFunction.KbcWrite (0x60, 0xED, &Data);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (MainTablePtr->Ec.Config.S5PlusEn) {
    if (CpmTablePpiPtr->CommonFunction.GetStrap (CpmTablePpiPtr) & BIT2) {
      Status = CpmTablePpiPtr->CommonFunction.KbcWrite (0x60, 0xA2, NULL);
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpEcInitPeimDriverEnd);

  return Status;
}

EFI_STATUS
EFIAPI
AmdCpmEcInitPeimEntryPoint (
  IN        CPM_PEI_FILE_HANDLE         FileHandle,
  IN        CPM_PEI_SERVICES            **PeiServices
  )
{
  EFI_STATUS                      Status;

  Status = (**PeiServices).NotifyPpi (PeiServices, &mCpmEcInitPeimNotify);

  return EFI_SUCCESS;
}
