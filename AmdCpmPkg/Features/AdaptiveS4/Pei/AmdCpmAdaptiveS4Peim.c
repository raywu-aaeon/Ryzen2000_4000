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
AmdCpmAdaptiveS4Peim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

#ifdef AGESA_V9
STATIC EFI_PEI_NOTIFY_DESCRIPTOR mCpmAdaptiveS4PeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCpmGpioInitFinishedPpiGuid,
  AmdCpmAdaptiveS4Peim
};
#endif

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Adaptive S4 PEIM driver
 *
 * This function will set the flag if the system wakes up from Adaptive S4 and
 * RTC method is used.
 *
 * @param[in]     FileHandle     Pointer to the firmware file system header
 * @param[in]     PeiServices    Pointer to Pei Services
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmAdaptiveS4Peim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr;
  AMD_CPM_MAIN_TABLE                  *MainTablePtr;
  AMD_CPM_ADAPTIVE_S4_TABLE           *AdaptiveS4TablePtr;
  EFI_STATUS                          Status;
  UINT32                              Offset;
  UINT8                               BufferSignature0;
  UINT8                               BufferSignature1;
  UINT8                               BufferSignature2;
  UINT8                               BufferSignature3;

  RECORD_TIME_PEI (BeginAmdCpmAdaptiveS4PeimDriver);

  Status = (*PeiServices)->LocatePpi (
                                      PeiServices,
                                      &gAmdCpmTablePpiGuid,
                                      0,
                                      NULL,
                                      (VOID**)&CpmTablePpiPtr
                                      );
  if (EFI_ERROR (Status)) {
    return  Status;
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpAdaptiveS4PeimDriverBegin);

  MainTablePtr                  = CpmTablePpiPtr->MainTablePtr;
  AdaptiveS4TablePtr            = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_ADAPTIVE_S4);

  if (AdaptiveS4TablePtr) {
    if (MainTablePtr->AdaptiveS4En == 2) {
      if (CpmTablePpiPtr->CommonFunction.GetBootMode () == CPM_BOOT_MODE_S4) {
        // RTC Method
        Offset = MainTablePtr->AcpiMemIoBaseAddr + 0x100 * AdaptiveS4TablePtr->BufferType + AdaptiveS4TablePtr->BufferOffset;
        BufferSignature0 = CpmTablePpiPtr->CommonFunction.MmioRead8 (Offset + 0x00);
        BufferSignature1 = CpmTablePpiPtr->CommonFunction.MmioRead8 (Offset + 0x01);
        BufferSignature2 = CpmTablePpiPtr->CommonFunction.MmioRead8 (Offset + 0x02);
        BufferSignature3 = CpmTablePpiPtr->CommonFunction.MmioRead8 (Offset + 0x03);
        if (CpmTablePpiPtr->CommonFunction.IsRtcWakeup (CpmTablePpiPtr) && BufferSignature3 == 'A' && BufferSignature2 == 'S' && BufferSignature1 == '3' && (BufferSignature0 == 'Y' || BufferSignature0 == 'P')) {
          CpmTablePpiPtr->CommonFunction.MmioOr8 (Offset + 0x08, BIT1);
          CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x00, 'P');
        } else {
          CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x00, 0x00);
          CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x01, 0x00);
          CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x02, 0x00);
          CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x03, 0x00);
          CpmTablePpiPtr->CommonFunction.MmioAnd8 (Offset + 0x08, 0xFD);
        }
      } else if (CpmTablePpiPtr->CommonFunction.GetBootMode () == CPM_BOOT_MODE_S3 && CpmTablePpiPtr->CommonFunction.IsRtcWakeup (CpmTablePpiPtr)) {
      } else {
        // RTC Method
        Offset = MainTablePtr->AcpiMemIoBaseAddr + 0x100 * AdaptiveS4TablePtr->BufferType + AdaptiveS4TablePtr->BufferOffset;
        CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x00, 0x00);
        CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x01, 0x00);
        CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x02, 0x00);
        CpmTablePpiPtr->CommonFunction.MmioWrite8 (Offset + 0x03, 0x00);
        CpmTablePpiPtr->CommonFunction.MmioAnd8 (Offset + 0x08, 0xFD);
      }
    }
  }

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpAdaptiveS4PeimDriverEnd);

  RECORD_TIME_PEI (EndAmdCpmAdaptiveS4PeimDriver);

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Adaptive S4 PEIM driver
 *
 * This function registers the functions to set HotPlug attribute in PCIe Topology Table
 * if Express Card supports.
 *
 * @param[in]     FileHandle     Pointer to the firmware file system header
 * @param[in]     PeiServices    Pointer to Pei Services
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmAdaptiveS4PeimEntryPoint (
  IN        CPM_PEI_FILE_HANDLE         FileHandle,
  IN        CPM_PEI_SERVICES            **PeiServices
  )
{
  EFI_STATUS                      Status;
#ifndef AGESA_V9
  EFI_PEI_NOTIFY_DESCRIPTOR       NotifyDescriptor;
  VOID                            *Ppi = NULL;
#endif

#ifdef AGESA_V9
  Status = (**PeiServices).NotifyPpi (PeiServices, &mCpmAdaptiveS4PeimNotify);
#else
  Status = AmdCpmAdaptiveS4Peim ((EFI_PEI_SERVICES**)PeiServices,
                               &NotifyDescriptor,
                               Ppi);
#endif
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return Status;
}
