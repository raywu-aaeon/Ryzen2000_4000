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

#include <AmdCpmSmm.h>

CPM_DEFINE_gBS;
CPM_DEFINE_gSmst;

AMD_CPM_TABLE_PROTOCOL *gCpmTableSmmProtocol;


EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmAdaptiveS4SmmCallback,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SX_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Adaptive S4 SMM driver
 *
 * This function registers the callback function before go to S4.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
AmdCpmAdaptiveS4SmmEntryPoint (
  IN      EFI_HANDLE                  ImageHandle,
  IN      EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                          Status;
  CPM_SMM_SX_DISPATCH_PROTOCOL        *SxDispatch;
  CPM_SMM_SX_DISPATCH_CONTEXT         SxContext;
  EFI_HANDLE                          SxHandle;

  If_CpmInSmm (ImageHandle, SystemTable, gBS, gSmst, Status) {

    //
    // Initialize global variables
    //
    Status = gBS->LocateProtocol (
                    &gAmdCpmTableSmmProtocolGuid,
                    NULL,
                    (VOID**)&gCpmTableSmmProtocol
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    gCpmTableSmmProtocol->CommonFunction.PostCode (CpmTpAdaptiveS4SmmDriverBegin);

    //
    //  Locate SMM Sx dispatch protocol
    //
    Status = CpmSmmLocateProtocol (
                    &gCpmSmmSxDispatchProtocolGuid,
                    NULL,
                    (VOID**)&SxDispatch
                    );
    ASSERT_EFI_ERROR (Status);

    SxContext.Type  = SxS4;
    SxContext.Phase = SxEntry;
    Status = SxDispatch->Register (
                    SxDispatch,
                    AmdCpmAdaptiveS4SmmCallback,
                    &SxContext,
                    &SxHandle
                    );

    gCpmTableSmmProtocol->CommonFunction.PostCode (CpmTpAdaptiveS4SmmDriverEnd);

  }

  RECORD_TIME_DXE (EndAmdCpmAdaptiveS4SmmDriver);

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * S4 SMI Handler for Adaptive S4
 *
 * This function programs RTC alarm registers if the OS will go to Adaptive S4 RTC mode
 * and RTC alarm register is not set by OS.
 *
 */
EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmAdaptiveS4SmmCallback,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SX_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  )
{
  AMD_CPM_ADAPTIVE_S4_TABLE *CpmAdaptiveS4TablePtr;
  UINT32                    Offset;
  UINT8                     Flag;
  UINT8                     BufferSignature0;
  UINT8                     BufferSignature1;
  UINT8                     BufferSignature2;
  UINT8                     BufferSignature3;
  UINT8                     RtcValue[8];
  UINT8                     TimeOut;

  gCpmTableSmmProtocol->CommonFunction.PostCode (CpmTpAdaptiveS4SmmRtcAlarmProgramBegin);

  CpmAdaptiveS4TablePtr = gCpmTableSmmProtocol->CommonFunction.GetTablePtr (gCpmTableSmmProtocol, CPM_SIGNATURE_ADAPTIVE_S4);

  if (CpmAdaptiveS4TablePtr && gCpmTableSmmProtocol->MainTablePtr->AdaptiveS4En == 2) {
    Offset = gCpmTableSmmProtocol->MainTablePtr->AcpiMemIoBaseAddr + 0x100 * CpmAdaptiveS4TablePtr->BufferType + CpmAdaptiveS4TablePtr->BufferOffset;
    Flag   = gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x08);
    BufferSignature0 = gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x00);
    BufferSignature1 = gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x01);
    BufferSignature2 = gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x02);
    BufferSignature3 = gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x03);

    if (BufferSignature3 == 'A' && BufferSignature2 == 'S' && BufferSignature1 == '3' && BufferSignature0 == '4' && (Flag & BIT0)) {
      RtcValue[0] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x00);
      RtcValue[1] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x01);
      RtcValue[2] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x02);
      RtcValue[3] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x03);
      RtcValue[4] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x04);
      RtcValue[5] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x05);
      RtcValue[6] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x07);
      RtcValue[7] = gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x0D) & 0x3F;
      Flag = ((gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x0B) & 0x20) == 0x00);
      if (((RtcValue[7] != 0) && (RtcValue[7] < RtcValue[6])) || ((RtcValue[5] & 0xC0) == 0x80) || ((RtcValue[3] & 0xC0) == 0x80) || ((RtcValue[1] & 0xC0) == 0x80)) {
        Flag = 1;
      } else if (((RtcValue[5] & 0xC0) != 0xC0) && RtcValue[5] > 23) {
        Flag = 1;
      } else if (((RtcValue[3] & 0xC0) != 0xC0) && RtcValue[3] > 59) {
        Flag = 1;
      } else if (((RtcValue[1] & 0xC0) != 0xC0) && RtcValue[1] > 59) {
        Flag = 1;
      } else {
        TimeOut = 1;
        if (((RtcValue[5] & 0xC0) == 0xC0) || (RtcValue[5] > RtcValue[4])) {
          TimeOut = 0;
        }
        if (TimeOut && (((RtcValue[3] & 0xC0) == 0xC0) || (RtcValue[3] > RtcValue[2]))) {
          TimeOut = 0;
        }
        if (TimeOut && (((RtcValue[1] & 0xC0) == 0xC0) || (RtcValue[1] > RtcValue[0]))) {
          TimeOut = 0;
        }
        Flag = Flag | TimeOut;
      }

      if (Flag) {
        gCpmTableSmmProtocol->CommonFunction.MmioAnd8 (
                                                    Offset + 0x08,
                                                    0xFD);  // Clean Flag
        gCpmTableSmmProtocol->CommonFunction.SetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x0B,
                                                    gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x0B) & 0xDF
                                                    );      // Disable alarm
        gCpmTableSmmProtocol->CommonFunction.SetAcpi (
                                                    gCpmTableSmmProtocol,
                                                    0x03,
                                                    gCpmTableSmmProtocol->CommonFunction.GetAcpi (gCpmTableSmmProtocol, 0x03) & 0xFB
                                                    );     // Disable alarm
        gCpmTableSmmProtocol->CommonFunction.SetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x01,
                                                    gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x00)
                                                    );    // Set second alarm
        gCpmTableSmmProtocol->CommonFunction.SetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x03,
                                                    gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x09)
                                                    );    // Set minute alarm
        gCpmTableSmmProtocol->CommonFunction.SetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x05,
                                                    gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x0A)
                                                    );    // Set hour alarm
        gCpmTableSmmProtocol->CommonFunction.SetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x0D,
                                                    (gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x0D) & 0xC0) | gCpmTableSmmProtocol->CommonFunction.MmioRead8 (Offset + 0x0B)
                                                    );    // Set day alarm

        gCpmTableSmmProtocol->CommonFunction.GetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x0C
                                                    );    // Clear alarm
        gCpmTableSmmProtocol->CommonFunction.SetAcpi (
                                                    gCpmTableSmmProtocol,
                                                    0x01,
                                                    0x04
                                                    );    // Clear alarm
        gCpmTableSmmProtocol->CommonFunction.SetRtc (
                                                    gCpmTableSmmProtocol,
                                                    0x0B,
                                                    gCpmTableSmmProtocol->CommonFunction.GetRtc (gCpmTableSmmProtocol, 0x0B) | 0x20
                                                    );    // Enable alarm
        gCpmTableSmmProtocol->CommonFunction.SetAcpi (
                                                    gCpmTableSmmProtocol,
                                                    0x03,
                                                    gCpmTableSmmProtocol->CommonFunction.GetAcpi (gCpmTableSmmProtocol, 0x03) | 0x04
                                                    );    // Enable alarm

        gCpmTableSmmProtocol->CommonFunction.MmioWrite8 (Offset + 0x00, 'Y');
      }
    } else {
      gCpmTableSmmProtocol->CommonFunction.MmioWrite8 (Offset + 0x00, 0x00);
      gCpmTableSmmProtocol->CommonFunction.MmioWrite8 (Offset + 0x01, 0x00);
      gCpmTableSmmProtocol->CommonFunction.MmioWrite8 (Offset + 0x02, 0x00);
      gCpmTableSmmProtocol->CommonFunction.MmioWrite8 (Offset + 0x03, 0x00);
    }
  }
  gCpmTableSmmProtocol->CommonFunction.PostCode (CpmTpAdaptiveS4SmmRtcAlarmProgramEnd);

  return EFI_SUCCESS;
}
