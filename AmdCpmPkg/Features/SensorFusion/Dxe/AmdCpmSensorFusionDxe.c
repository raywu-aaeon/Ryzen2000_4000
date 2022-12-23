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

#include <AmdCpmDxe.h>

EFI_GUID SENSORFUSION_ACPI_DEVICE_GUID = {
  0xA7D18461, 0x72A5, 0x4BC7, 0x9E, 0xFC, 0x31, 0xE4, 0xD3, 0x5B, 0x82, 0x14
};

VOID
EFIAPI
AmdCpmSensorFusionInitLate (
  IN      EFI_EVENT       Event,
  IN      VOID            *Context
  );

BOOLEAN
EFIAPI
AmdCpmSensorFusionCallBack (
  IN      AMD_CPM_TABLE_PROTOCOL  *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM SensorFusion DXE driver
 *
 * This function stores the setting of SensorFusion in NV Data and loads, updates
 * and installs SensorFusion SSDT Table.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmSensorFusionDxeEntryPoint (
  IN      EFI_HANDLE              ImageHandle,
  IN      EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       ReadyToBootEvent;

  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  Status = gBS->CreateEventEx (
                  CPM_EVENT_NOTIFY_SIGNAL,
                  CPM_TPL_CALLBACK,
                  AmdCpmSensorFusionInitLate,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &ReadyToBootEvent
                  );

  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * The function to load AMD CPM Zero Power Odd SSDT table.
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */
VOID
EFIAPI
AmdCpmSensorFusionInitLate (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  )
{
  STATIC BOOLEAN                  InitlateInvoked = FALSE;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_MAIN_TABLE              *CpmMainTablePtr;
  EFI_STATUS                      Status;
  UINT32                          Buffer[1];

  if (!InitlateInvoked) {

    Status = gBS->LocateProtocol (&gAmdCpmTableProtocolGuid, NULL, (VOID**)&CpmTableProtocolPtr);
    if (EFI_ERROR (Status)) {
      return;
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpSensorFusionDxeDriverBegin);

    CpmMainTablePtr = CpmTableProtocolPtr->MainTablePtr;
    if (CpmMainTablePtr->SensorFusionEn) {
      Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                        8,
                                                                        1 );
      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                          &SENSORFUSION_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmSensorFusionCallBack,
                                                          &Buffer[0] );
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpSensorFusionDxeDriverEnd);
  }

  InitlateInvoked = TRUE;

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to override Zero Power Odd SSDT Table
 *
 * This function is used to update GPE numbers and SATA port number.
 *
 * @param[in]     This           Pointer to Protocol
 * @param[in]     AmlObjPtr      The AML Object Buffer
 * @param[in]     Context        The Parameter Buffer
 *
 * @retval        TRUE           SSDT Table has been updated completely
 * @retval        FALSE          SSDT Table has not been updated completely
 */
BOOLEAN
EFIAPI
AmdCpmSensorFusionCallBack (
  IN      AMD_CPM_TABLE_PROTOCOL  *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;
  BufferPtr = (UINT32*)Context;

  switch (*((UINT32*)AmlObjPtr)) {
  case CPM_SIGNATURE_32 ('P', 'B', 'C', '_'):     // ASL code: \_SB.PCI0.PBC
    if (*(BufferPtr + 0)) {
      *((UINT32*)AmlObjPtr) = *(BufferPtr + 0);
    }
    break;
  }

  return FALSE;
}

