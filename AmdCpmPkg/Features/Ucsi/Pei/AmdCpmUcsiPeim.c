/*****************************************************************************
 *
 * Copyright 2018 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
AmdCpmUcsiPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mCpmUcsiPeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCpmGpioInitFinishedPpiGuid,
  AmdCpmUcsiPeim
};

/*----------------------------------------------------------------------------------------*/
/**
 *
 * @param[in]     PeiServices       Pointer to Pei Services
 * @param[in]     NotifyDescriptor  The descriptor for the notification event
 * @param[in]     Ppi               Pointer to the PPI in question.
 *
 * @retval        EFI_SUCCESS       Module initialized successfully
 * @retval        EFI_ERROR         Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmUcsiPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  EFI_STATUS                            Status;
  AMD_CPM_TABLE_PPI                     *CpmTablePpiPtr;
  AMD_CPM_MAIN_TABLE                    *MainTablePtr;
  AMD_CPM_UCSI_TABLE                    *CpmUcsiTablePtr;
  UINT8                                 Value8;
  UINT8                                 Offset;

  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeim-Start\n"));
  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeim-From-"));
  DEBUG((DEBUG_INFO, "AmdCpmUcsiPeimEntryPoint-NotifyPpi-gAmdCpmGpioInitFinishedPpiGuid\n"));
  Value8 = 0;
  Offset = 0;

  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeim-LocatePpi-gAmdCpmTablePpiGuid\n"));
  Status = (*PeiServices)->LocatePpi (  (CPM_PEI_SERVICES**)PeiServices,
                                        &gAmdCpmTablePpiGuid,
                                        0,
                                        NULL,
                                        (VOID**)&CpmTablePpiPtr );
  if (EFI_ERROR (Status)) {
    DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeim-End-1-Status = %r\n", Status));
    return Status;
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpUcsiPeimDriverBegin);
  MainTablePtr    = CpmTablePpiPtr->MainTablePtr;
  CpmUcsiTablePtr = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_UCSI);

  if (CpmUcsiTablePtr && (MainTablePtr->UcsiEn == 1)) {
    if (CpmUcsiTablePtr->EcUcsiLocation == 0) {
      Offset = CpmUcsiTablePtr->EcVersionLocation;
      CpmTablePpiPtr->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8); // CFG_CPM_ECRAM_BASE_ADDR = PcdGet16 (EcRamBaseAddr)
      CpmUcsiTablePtr->Reserved[0] = Value8;
      Offset = CpmUcsiTablePtr->EcVersionLocation + 1;
      CpmTablePpiPtr->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &Offset, &Value8); // CFG_CPM_ECRAM_BASE_ADDR = PcdGet16 (EcRamBaseAddr)
      CpmUcsiTablePtr->Reserved[1] = Value8;
    } else {
      CpmUcsiTablePtr->Reserved[0] = CpmTablePpiPtr->CommonFunction.MmioRead8 (CpmUcsiTablePtr->EcUcsiLocation + (UINT32)(CpmUcsiTablePtr->EcVersionLocation));
      CpmUcsiTablePtr->Reserved[1] = CpmTablePpiPtr->CommonFunction.MmioRead8 (CpmUcsiTablePtr->EcUcsiLocation + (UINT32)(CpmUcsiTablePtr->EcVersionLocation + 1));
    }
  }

  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeim-End-2-Status = %r\n", Status));
  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpUcsiPeimDriverEnd);
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM UCSI PEIM driver
 *
 * @param[in]     FileHandle     Pointer to the firmware file system header
 * @param[in]     PeiServices    Pointer to Pei Services
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmUcsiPeimEntryPoint (
  IN        CPM_PEI_FILE_HANDLE         FileHandle,
  IN        CPM_PEI_SERVICES            **PeiServices
  )
{
  EFI_STATUS                            Status;
  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeimEntryPoint-Start\n"));

  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeimEntryPoint-NotifyPpi-gAmdCpmGpioInitFinishedPpiGuid\n"));
  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeimEntryPoint-For-AmdCpmUcsiPeim\n"));
  Status = (**PeiServices).NotifyPpi (PeiServices, &mCpmUcsiPeimNotify);

  DEBUG((DEBUG_INFO, "FEA-PEI-AmdCpmUcsiPeimEntryPoint-End\n"));
  return Status;
}
