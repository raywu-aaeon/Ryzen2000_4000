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

#include <AmdCpmDxe.h>


EFI_GUID ADAPTIVE_S4_ACPI_DEVICE_GUID = {
  0xa8080674, 0xe53c, 0x4ddf, 0x9f, 0xf8, 0xba, 0x21, 0xf7, 0xa6, 0x99, 0x92
};

VOID
EFIAPI
AmdCpmAdaptiveS4InitMid (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  );

VOID
EFIAPI
AmdCpmAdaptiveS4InitLate (
  IN      EFI_EVENT       Event,
  IN      VOID            *Context
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Adaptive S4 DXE driver
 *
 * This function stores the setting of Adaptive S4 in NV Data and installs Adaptive
 * S4 SSDT Table.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmAdaptiveS4DxeEntryPoint (
  IN      EFI_HANDLE              ImageHandle,
  IN      EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       ReadyToBootEvent;
  EFI_EVENT                       AdaptiveS4DisplayOff;
  VOID                            *mAdaptiveS4DisplayOff;

  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  Status = gBS->CreateEvent (
                  CPM_EVENT_NOTIFY_SIGNAL,
                  CPM_TPL_NOTIFY,
                  AmdCpmAdaptiveS4InitMid,
                  NULL,
                  &AdaptiveS4DisplayOff
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->RegisterProtocolNotify (
                  &gAmdCpmAllPciIoProtocolsInstalledProtocolGuid,
                  AdaptiveS4DisplayOff,
                  &mAdaptiveS4DisplayOff
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->CreateEventEx (
                  CPM_EVENT_NOTIFY_SIGNAL,
                  CPM_TPL_NOTIFY,
                  AmdCpmAdaptiveS4InitLate,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &ReadyToBootEvent
                  );

  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * The function to turn off display in Adaptive S4.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmAdaptiveS4InitMid (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  )
{
  STATIC BOOLEAN                  InitlateInvoked = FALSE;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_ADAPTIVE_S4_TABLE       *CpmAdaptiveS4TablePtr;
  AMD_CPM_MAIN_TABLE              *CpmMainTablePtr;
  AMD_CPM_DEVICE_PATH_TABLE       *DevicePathTablePtr;
  AMD_CPM_SAVE_CONTEXT_TABLE      *SaveContextTablePtr;
  EFI_STATUS                      Status;
  UINT32                          Offset;
  UINT8                           BufferSignature0;
  UINT8                           BufferSignature1;
  UINT8                           BufferSignature2;
  UINT8                           BufferSignature3;
  UINT8                           AdativeS4Flag;
  UINT8                           Data;
  UINT8                           EcOffset;
  UINT16                          GfxVid;
  UINT8                           i;
  UINT8                           bus;
  UINT16                          BaseAddr;
  UINT8                           BootMode;

  AdativeS4Flag = 0;

  if (!InitlateInvoked) {

    Status = gBS->LocateProtocol (&gAmdCpmTableProtocolGuid, NULL, (VOID**)&CpmTableProtocolPtr);
    if (EFI_ERROR (Status)) {
      return;
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpAdaptiveS4DxeDisplayTurnOffBegin);

    CpmMainTablePtr         = CpmTableProtocolPtr->MainTablePtr;
    CpmAdaptiveS4TablePtr   = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_ADAPTIVE_S4);
    DevicePathTablePtr      = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_DEVICE_PATH);
    SaveContextTablePtr     = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_SAVE_CONTEXT);
    if (SaveContextTablePtr && CpmAdaptiveS4TablePtr && CpmMainTablePtr->AdaptiveS4En) {
      BootMode = CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, BootMode));
      if (BootMode == CPM_BOOT_MODE_S4) {
        if (CpmMainTablePtr->AdaptiveS4En == 2) {
          Offset = CpmMainTablePtr->AcpiMemIoBaseAddr + 0x100 * CpmAdaptiveS4TablePtr->BufferType + CpmAdaptiveS4TablePtr->BufferOffset;
          BufferSignature0 = CpmTableProtocolPtr->CommonFunction.MmioRead8 (Offset + 0x00);
          BufferSignature1 = CpmTableProtocolPtr->CommonFunction.MmioRead8 (Offset + 0x01);
          BufferSignature2 = CpmTableProtocolPtr->CommonFunction.MmioRead8 (Offset + 0x02);
          BufferSignature3 = CpmTableProtocolPtr->CommonFunction.MmioRead8 (Offset + 0x03);
          if (BufferSignature3 == 'A' && BufferSignature2 == 'S' && BufferSignature1 == '3' && BufferSignature0 == 'P') {
            AdativeS4Flag = 1;
          }
        } else if (CpmMainTablePtr->AdaptiveS4En == 1) {
          EcOffset = CpmAdaptiveS4TablePtr->EcRamOffset + 0x04;
          Status = CpmTableProtocolPtr->CommonFunction.KbcRead (CFG_CPM_ECRAM_BASE_ADDR, 0x80, &EcOffset, &Data);   // CFG_CPM_ECRAM_BASE_ADDR = PcdGet16 (EcRamBaseAddr)
          if (EFI_ERROR (Status)) {
            return;
          }
          AdativeS4Flag = Data & BIT0;
        }
        if (AdativeS4Flag) {
          for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
            if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
              break;
            }
            if (DevicePathTablePtr->Path[i].Bridge.Device == 0) {
              bus = 0;
              GfxVid = CpmTableProtocolPtr->CommonFunction.PciRead16 (
                                  CpmTableProtocolPtr,
                                  bus,
                                  DevicePathTablePtr->Path[i].Device.Device,
                                  DevicePathTablePtr->Path[i].Device.Function,
                                  0x00    // PCI_VENDOR_ID_OFFSET
                                  );
            } else {
              bus = CpmTableProtocolPtr->CommonFunction.PciRead8 (
                                  CpmTableProtocolPtr,
                                  0,
                                  DevicePathTablePtr->Path[i].Bridge.Device,
                                  DevicePathTablePtr->Path[i].Bridge.Function,
                                  0x19    // PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET
                                  );
              GfxVid = CpmTableProtocolPtr->CommonFunction.PciRead16 (
                                  CpmTableProtocolPtr,
                                  bus,
                                  DevicePathTablePtr->Path[i].Device.Device,
                                  DevicePathTablePtr->Path[i].Device.Function,
                                  0x00    // PCI_VENDOR_ID_OFFSET
                                  );
            }
            if (GfxVid != 0xFFFF && GfxVid != 0x0000) {
              if (CpmTableProtocolPtr->CommonFunction.PciRead8 (
                                  CpmTableProtocolPtr,
                                  bus,
                                  DevicePathTablePtr->Path[i].Device.Device,
                                  DevicePathTablePtr->Path[i].Device.Function,
                                  0x0B    // R_BASE_CODE
                                  ) == 3) {
                BaseAddr = CpmTableProtocolPtr->CommonFunction.PciRead16 (
                                  CpmTableProtocolPtr,
                                  bus,
                                  DevicePathTablePtr->Path[i].Device.Device,
                                  DevicePathTablePtr->Path[i].Device.Function,
                                  0x20    // R_BASE_CODE
                                  ) & 0xFFF0;
                CpmTableProtocolPtr->CommonFunction.IoWrite32 (BaseAddr, 0x172C);
                CpmTableProtocolPtr->CommonFunction.IoWrite32 (BaseAddr + 4, BIT16 | CpmTableProtocolPtr->CommonFunction.IoRead32 (BaseAddr + 4));
              }
            }
          }
        }
      }
    }
    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpAdaptiveS4DxeDisplayTurnOffEnd);
  }

  InitlateInvoked = TRUE;

  return;
}

BOOLEAN
EFIAPI
AmdCpmAdaptiveS4SsdtCallBack (
  IN      VOID                    *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;

  BufferPtr = (UINT32*)Context;

  switch ( *((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('E', 'C', '0', '_')):
    if (*BufferPtr) {
      *(UINT32*) AmlObjPtr = *(UINT32*)BufferPtr;
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '0', '4', '2')):     // CpmKbcMutex: M042
    if (*(BufferPtr + 1)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('L', 'P', 'C', '0')):
    if (*(BufferPtr + 2)) {
      *(UINT32*) AmlObjPtr = *(UINT32*)(BufferPtr + 2);
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to load AMD CPM Adaptive S4 SSDT table.
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmAdaptiveS4InitLate (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  )
{
  STATIC BOOLEAN                  InitlateInvoked = FALSE;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_ADAPTIVE_S4_TABLE       *CpmAdaptiveS4TablePtr;
  AMD_CPM_MAIN_TABLE              *CpmMainTablePtr;
  EFI_STATUS                      Status;
  UINT32                          Buffer[3];

  RECORD_TIME_DXE (BeginAmdCpmAdaptiveS4DxeDriver);

  if (!InitlateInvoked) {
    Status = gBS->LocateProtocol (&gAmdCpmTableProtocolGuid, NULL, (VOID**)&CpmTableProtocolPtr);
    if (EFI_ERROR (Status)) {
      return;
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpAdaptiveS4DxeDriverBegin);

    CpmMainTablePtr = CpmTableProtocolPtr->MainTablePtr;
    CpmAdaptiveS4TablePtr = (AMD_CPM_ADAPTIVE_S4_TABLE *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_ADAPTIVE_S4);

    if (CpmAdaptiveS4TablePtr && CpmMainTablePtr->AdaptiveS4En) {
      Buffer[0] = CFG_AMD_CPM_ASL_EC_NAME;      // PcdGet32 (EcAslName)
      Buffer[1] = CFG_AMD_CPM_ASL_EC_MUTEX;     // PcdGet32 (EcMutexAslName)
      Buffer[2] = CFG_AMD_CPM_ASL_LPC_NAME;     // PcdGet32 (LpcAslName)

      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                          &ADAPTIVE_S4_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmAdaptiveS4SsdtCallBack,
                                                          &Buffer[0]
                                                       );
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpAdaptiveS4DxeDriverEnd);
  }

  InitlateInvoked = TRUE;

  RECORD_TIME_DXE (EndAmdCpmAdaptiveS4DxeDriver);

  return;
}
