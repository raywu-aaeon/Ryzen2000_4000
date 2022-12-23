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

EFI_GUID EXPRESS_CARD_ACPI_DEVICE_GUID = {
  0x5f26ca84, 0x837d, 0x4c3e, 0x9d, 0x76, 0xb6, 0xa7, 0x88, 0xb7, 0x50, 0x57
};

EFI_GUID WIRELESS_BUTTON_ACPI_DEVICE_GUID = {
  0x246653E0, 0x99EF, 0x4C1A, 0x9A, 0x68, 0xB3, 0x18, 0x4D, 0xB6, 0x2F, 0xD9
};

EFI_GUID OTHER_HOTPLUG_ACPI_DEVICE_GUID = {
  0xF00B910D, 0x67A7, 0x48F3, 0x82, 0x96, 0x92, 0x0C, 0x23, 0x32, 0x62, 0xD5
};

EFI_GUID LOW_POWER_ETHERNET_ACPI_DEVICE_GUID = {
  0x798E5415, 0xD6FE, 0x4663, 0x81, 0x7C, 0xCE, 0xFD, 0x59, 0xB7, 0xD7, 0xA5
};

EFI_GUID WIRELESS_LAN_RECOVERY_ACPI_DEVICE_GUID = {
  0xAAD0FDDE, 0x2E43, 0x4483, 0xBD, 0x8E, 0x2E, 0x39, 0x90, 0x59, 0xC6, 0xB2
};

VOID
EFIAPI
AmdCpmPcieInitLate (
  IN      EFI_EVENT           Event,
  IN      VOID                *Context
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM PCIE Init DXE driver
 *
 * This function loads, overrides and installs Express Card SSDT table.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmPcieInitDxeEntryPoint (
  IN      EFI_HANDLE                      ImageHandle,
  IN      EFI_SYSTEM_TABLE                *SystemTable
  )
{
  EFI_STATUS                              Status;
  EFI_EVENT                               ReadyToBootEvent;

  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  Status = gBS->CreateEventEx (
                              CPM_EVENT_NOTIFY_SIGNAL,
                              CPM_TPL_NOTIFY,
                              AmdCpmPcieInitLate,
                              NULL,
                              &gEfiEventReadyToBootGuid,
                              &ReadyToBootEvent
                              );

  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Express Card SSDT table
 *
 * This function is used to update GPE number and PCIE Bridge Name
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
AmdCpmExpressCardSsdtCallBack (
  IN      VOID                    *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;

  BufferPtr = (UINT32*)Context;

  switch ( *((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('M', '1', '2', '9')):     // CpmExpressCardEventMethod: M129
    if (*(BufferPtr)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '1', '3', '0')):     // CpmExpressCardBridge: M130
    if (*(BufferPtr + 1)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 1);
    }
    break;
  }
  return FALSE;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Wireless Button SSDT table
 *
 * This function is used to update GPE number and PCIE Bridge Name
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
AmdCpmWirelessButtonSsdtCallBack (
  IN      VOID                    *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;

  BufferPtr = (UINT32*)Context;

  switch ( *((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('M', '1', '2', '1')):     // CpmWirelessButtonEventMethod: M121
    if (*(BufferPtr)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '1', '2', '3')):     // CpmWirelessBridge0: M123
    if (*(BufferPtr + 1)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '1', '2', '4')):     // CpmWirelessBridge1: M124
    if (*(BufferPtr + 2)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 2);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '1', '2', '5')):     // CpmWirelessBridge2: M125
    if (*(BufferPtr + 3)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 3);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '1', '2', '6')):     // CpmWirelessBridge3: M126
    if (*(BufferPtr + 4)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 4);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '1', '2', '7')):     // CpmWirelessButtonCurrentStatus: M127
    if (*(BufferPtr + 5)) {
      *(((UINT8*) AmlObjPtr) + 4) = 1;
      *(BufferPtr + 5) = 0;
    }
    break;
  }
  return FALSE;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Other Hotplug SSDT table
 *
 * This function is used to update GPE number and PCIE Bridge Name
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
AmdCpmOtherHotplugSsdtCallBack (
  IN      VOID                    *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;

  BufferPtr = (UINT32*)Context;

  switch ( *((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('M', '2', '2', '2')):     // CpmOtherHotplugCard0EventMethod: M222
    if (*(BufferPtr)) {
      *(UINT16 *) AmlObjPtr = 'L_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 0);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '5', '7')):     // CpmOtherHotplugCard0ConnectMethod: M257
    if (*(BufferPtr + 1)) {
      *(UINT16 *) AmlObjPtr = 'Q_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '5', '8')):     // CpmOtherHotplugCard0DisconnectMethod: M258
    if (*(BufferPtr + 2)) {
      *(UINT16 *) AmlObjPtr = 'Q_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 2);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '2', '3')):     // CpmOtherHotplugCard0Bridge: M223
    if (*(BufferPtr + 3)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 3);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '2', '4')):     // CpmOtherHotplugCard1EventMethod: M224
    if (*(BufferPtr + 4)) {
      *(UINT16 *) AmlObjPtr = 'L_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 4);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '5', '9')):     // CpmOtherHotplugCard1ConnectMethod: M259
    if (*(BufferPtr + 5)) {
      *(UINT16 *) AmlObjPtr = 'Q_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 5);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '6', '0')):     // CpmOtherHotplugCard1DisconnectMethod: M260
    if (*(BufferPtr + 6)) {
      *(UINT16 *) AmlObjPtr = 'Q_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 6);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '2', '5')):     // CpmOtherHotplugCard1Bridge: M225
    if (*(BufferPtr + 7)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 7);
    }
    break;
  case (CPM_SIGNATURE_32 ('E', 'C', '0', '_')):
    if (*(BufferPtr + 8)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 8);
    }
    break;
  case (CPM_SIGNATURE_32 ('L', 'P', 'C', '0')):
    if (*(BufferPtr + 9)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 9);
    }
    break;
  }
  return FALSE;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Low Power Etherent SSDT table
 *
 * This function is used to update GPE number and PCIE Bridge Name
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
AmdCpmLowPowerEthernetSsdtCallBack (
  IN      VOID                    *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;

  BufferPtr = (UINT32*)Context;

  switch ( *((UINT32*)AmlObjPtr)) {
  case (CPM_SIGNATURE_32 ('M', '2', '8', '1')):     // CpmLowPowerEthernetCablePlugOutMethod: M281
    if (*(BufferPtr + 0)) {
      *(UINT16 *) AmlObjPtr = 'Q_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 0);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '8', '2')):     // CpmLowPowerEthernetCablePlugInMethod:  M282
    if (*(BufferPtr + 1)) {
      *(UINT16 *) AmlObjPtr = 'Q_';
      *(UINT16 *) ((UINT8*)AmlObjPtr + 2) = *(UINT16*)(BufferPtr + 1);
    }
    break;
  case (CPM_SIGNATURE_32 ('M', '2', '8', '3')):     // CpmLowPowerEthernetBridgeAslName:      M283
    if (*(BufferPtr + 2)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 2);
    }
    break;
  case (CPM_SIGNATURE_32 ('B', 'C', 'M', '5')):     // BCM5
    if (*(BufferPtr + 3)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 3);
    }
    break;
  case (CPM_SIGNATURE_32 ('E', 'C', '0', '_')):
    if (*(BufferPtr + 4)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 4);
    }
    break;
  case (CPM_SIGNATURE_32 ('L', 'P', 'C', '0')):
    if (*(BufferPtr + 5)) {
      *(UINT32*) AmlObjPtr = *(BufferPtr + 5);
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Wireless LAN Recovery SSDT table
 *
 * This function is used to update PCIE Bridge Name
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
AmdCpmWirelessLanRecoverySsdtCallBack (
  IN      VOID                    *This,
  IN      VOID                    *AmlObjPtr,
  IN      VOID                    *Context
  )
{
  UINT32  *BufferPtr;

  BufferPtr = (UINT32*)Context;
  switch ( *((UINT32*)AmlObjPtr)) {
    case (CPM_SIGNATURE_32 ('M', '2', '9', '1')):     // CpmWirelessLanBridgeAslName:      M291
      if (*(BufferPtr + 0)) {
        *(UINT32*) AmlObjPtr = *(BufferPtr + 0);
      }
      break;

    case (CPM_SIGNATURE_32 ('D', 'E', 'V', '0')):    // DEV0
      if (*(BufferPtr + 1)) {
        *(UINT32*) AmlObjPtr = *(BufferPtr + 1);
      }
      break;
  }
  return FALSE;
}


/*----------------------------------------------------------------------------------------*/
/**
 * The function to load, override and install AMD CPM Express Card SSDT table.
 *
 * This function gets called each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmPcieInitLate (
  IN      EFI_EVENT               Event,
  IN      VOID                    *Context
  )
{
  AMD_CPM_NV_DATA_PROTOCOL        *CpmNvDataProtocolPtr;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_SAVE_CONTEXT_TABLE      *SaveContextTablePtr;
  AMD_CPM_EXPRESS_CARD_TABLE      *ExpressCardTablePtr;
  AMD_CPM_OTHER_HOTPLUG_CARD_TABLE  *OtherHotplugTablePtr;
  AMD_CPM_LOW_POWER_ETHERNET_TABLE  *LowPowerEthernetTablePtr;
  AMD_CPM_PCIE_TOPOLOGY_TABLE     *PcieTopologyTablePtr;
  AMD_CPM_DXIO_TOPOLOGY_TABLE     *DxioTopologyTablePtr;
  AMD_CPM_WIRELESS_BUTTON_TABLE   *WirelessButtonTablePtr;
  AMD_CPM_CORE_TOPOLOGY_TABLE     *AmdCpmCoreTopologyPtr;
  AMD_CPM_WIRELESS_LAN_RECOVERY_TABLE *WirelessLanRecoveryTablePtr;
  STATIC BOOLEAN                  InitlateInvoked = FALSE;
  EFI_STATUS                      Status;
  UINT32                          Buffer[10];
  UINT8                           SciMap;
  UINT8                           Index;
  UINT32                          PCIeStatus;
  UINT32                          DeviceVendoreId;
  UINT32                          IsFchBridge;
  UINT8                           CpuRevisionId;
  UINT8                           BusNumber;
  UINT8                           CoreNumber;

  RECORD_TIME_DXE (BeginAmdCpmPcieInitDxeDriver);

  if (!InitlateInvoked) {

    Status = gBS->LocateProtocol (  &gAmdCpmTableProtocolGuid,
                                    NULL,
                                    (VOID**)&CpmTableProtocolPtr
                                    );
    if (EFI_ERROR (Status)) {
      return;
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpPcieInitDxeDriverBegin);

    Status = gBS->LocateProtocol (  &gAmdCpmNvDataProtocolGuid,
                                    NULL,
                                    (VOID**)&CpmNvDataProtocolPtr
                                    );
    if (EFI_ERROR (Status)) {
      return;
    }

    ExpressCardTablePtr       = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_EXPRESS_CARD);
    OtherHotplugTablePtr      = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD);
    LowPowerEthernetTablePtr  = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_LOW_POWER_ETHERNET);
    WirelessLanRecoveryTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_WIRELESS_LAN_RECOVERY);
    SaveContextTablePtr       = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_SAVE_CONTEXT);
    PcieTopologyTablePtr      = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_TOPOLOGY);
    DxioTopologyTablePtr      = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_DXIO_TOPOLOGY);
    WirelessButtonTablePtr    = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_WIRELESS_BUTTON);
    AmdCpmCoreTopologyPtr     = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_CORE_TOPOLOGY);
    CpuRevisionId             = CpmTableProtocolPtr->CommonFunction.GetCpuRevisionId (CpmTableProtocolPtr);

    if (SaveContextTablePtr && PcieTopologyTablePtr) {
      PCIeStatus = 0;
      for ( Index = 0; Index < AMD_PCIE_PORT_DESCRIPTOR_SIZE; Index ++ ) {
        if ((PcieTopologyTablePtr->Port[Index].EngineData.EngineType == PciePortEngine) && (PcieTopologyTablePtr->Port[Index].Port.PortPresent)) {
          DeviceVendoreId =  CpmTableProtocolPtr->CommonFunction.PciRead32 (
                                CpmTableProtocolPtr,
                                0x00,
                                PcieTopologyTablePtr->Port[Index].Port.DeviceNumber,
                                PcieTopologyTablePtr->Port[Index].Port.FunctionNumber,
                                0x00
                                );
          if (DeviceVendoreId != 0 && DeviceVendoreId != 0xFFFFFFFF) {
            PCIeStatus |= 1 << Index;
          }
        }
        if (PcieTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
          break;
        }
      }

      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x00, (UINT8) (PCIeStatus));
      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x01, (UINT8) (PCIeStatus >> 8));
      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x02, (UINT8) (PCIeStatus >> 16));
      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x03, (UINT8) (PCIeStatus >> 24));
    }

    if (SaveContextTablePtr && DxioTopologyTablePtr) {
      PCIeStatus = 0;
      for ( Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++ ) {
        if ((DxioTopologyTablePtr->Port[Index].EngineData.EngineType == DxioPcieEngine) && (DxioTopologyTablePtr->Port[Index].Port.PortPresent)) {
          if (AmdCpmCoreTopologyPtr) {
            if (CpuRevisionId >= CPM_CPU_REVISION_ID_RV) {
              BusNumber = 0;
            } else {
              CoreNumber = DxioTopologyTablePtr->Port[Index].EngineData.StartLane / 32;
              BusNumber = AmdCpmCoreTopologyPtr->CoreList[CoreNumber].Bus;
            }
          } else {
            BusNumber = 0;
          }
          DeviceVendoreId =  CpmTableProtocolPtr->CommonFunction.PciRead32 (
                                CpmTableProtocolPtr,
                                BusNumber,
                                DxioTopologyTablePtr->Port[Index].Port.DeviceNumber,
                                DxioTopologyTablePtr->Port[Index].Port.FunctionNumber,
                                0x00
                                );
          if (DeviceVendoreId != 0 && DeviceVendoreId != 0xFFFFFFFF) {
            PCIeStatus |= 1 << Index;
          }
        }
        if (DxioTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
          break;
        }
      }

      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x00, (UINT8) (PCIeStatus));
      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x01, (UINT8) (PCIeStatus >> 8));
      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x02, (UINT8) (PCIeStatus >> 16));
      CpmTableProtocolPtr->CommonFunction.SetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x03, (UINT8) (PCIeStatus >> 24));
    }

    if (ExpressCardTablePtr) {
      ZeroMem (Buffer, sizeof (Buffer));
      SciMap = CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, ExpressCardTablePtr->EventPin);

      Buffer[0] = 'L_';
      if ((SciMap & 0xF) < 0xA) {
        Buffer[0] |= (0x30 + ((SciMap) & 0xF)) << 24;
      } else {
        Buffer[0] |= (0x40 + (((SciMap) & 0xF) - 0x9)) << 24;
      }
      if (((SciMap >> 4) & 0xF) < 0xA) {
        Buffer[0] |= (0x30 + ((SciMap >> 4) & 0xF)) << 16;
      } else {
        Buffer[0] |= (0x40 + (((SciMap >> 4) & 0xF) - 0x9)) << 16;
      }
      IsFchBridge = CpmTableProtocolPtr->CommonFunction.IsFchDevice (
                                                          CpmTableProtocolPtr,
                                                          ExpressCardTablePtr->Device,
                                                          ExpressCardTablePtr->Function
                                                          );
      if (IsFchBridge) {
        Buffer[1] = CpmTableProtocolPtr->CommonFunction.GetFchPcieAslName (
                                                          CpmTableProtocolPtr,
                                                          ExpressCardTablePtr->Device,
                                                          ExpressCardTablePtr->Function
                                                          );
      } else {
        Buffer[1] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (
                                                          CpmTableProtocolPtr,
                                                          ExpressCardTablePtr->Device,
                                                          ExpressCardTablePtr->Function
                                                          );
      }

      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (
                                                          CpmTableProtocolPtr,
                                                          &EXPRESS_CARD_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmExpressCardSsdtCallBack,
                                                          &Buffer[0]
                                                          );
    }

    if (WirelessButtonTablePtr && CpmTableProtocolPtr->MainTablePtr->WirelessButtonEn) {
      ZeroMem (Buffer, sizeof (Buffer));
      SciMap = CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, WirelessButtonTablePtr->EventPin);
      Buffer[0] = 'L_';
      if ((SciMap & 0xF) < 0xA) {
        Buffer[0] |= (0x30 + ((SciMap) & 0xF)) << 24;
      } else {
        Buffer[0] |= (0x40 + (((SciMap) & 0xF) - 0x9)) << 24;
      }
      if (((SciMap >> 4) & 0xF) < 0xA) {
        Buffer[0] |= (0x30 + ((SciMap >> 4) & 0xF)) << 16;
      } else {
        Buffer[0] |= (0x40 + (((SciMap >> 4) & 0xF) - 0x9)) << 16;
      }
      for (Index = 0; Index < 4; Index++) {
        IsFchBridge = CpmTableProtocolPtr->CommonFunction.IsFchDevice (
                                                            CpmTableProtocolPtr,
                                                            WirelessButtonTablePtr->Bridge[Index].Device,
                                                            WirelessButtonTablePtr->Bridge[Index].Function
                                                            );
        if (IsFchBridge) {
          Buffer[1 + Index] = CpmTableProtocolPtr->CommonFunction.GetFchPcieAslName (
                                                            CpmTableProtocolPtr,
                                                            WirelessButtonTablePtr->Bridge[Index].Device,
                                                            WirelessButtonTablePtr->Bridge[Index].Function
                                                            );
        } else {
          Buffer[1 + Index] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (
                                                            CpmTableProtocolPtr,
                                                            WirelessButtonTablePtr->Bridge[Index].Device,
                                                            WirelessButtonTablePtr->Bridge[Index].Function
                                                            );
        }
      }
      if (SaveContextTablePtr) {
        if (CpmTableProtocolPtr->CommonFunction.GetSaveContext (CpmTableProtocolPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, WirelessButtonStatus)) == 0) {
          Buffer[5] = 1;
        } else {
          Buffer[5] = 0;
        }
      }

      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (
                                                          CpmTableProtocolPtr,
                                                          &WIRELESS_BUTTON_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmWirelessButtonSsdtCallBack,
                                                          &Buffer[0]
                                                          );
    }

    if (OtherHotplugTablePtr) {
      ZeroMem (Buffer, sizeof (Buffer));
      if (OtherHotplugTablePtr->Number > 0) {
        if (OtherHotplugTablePtr->EventSource0 == 0) {
          Buffer[0] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, OtherHotplugTablePtr->EventPin0));
        } else {
          Buffer[1] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (OtherHotplugTablePtr->QEventFalling0);
          Buffer[2] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (OtherHotplugTablePtr->QEventRising0);
        }
        IsFchBridge = CpmTableProtocolPtr->CommonFunction.IsFchDevice (
                                                            CpmTableProtocolPtr,
                                                            OtherHotplugTablePtr->Device0,
                                                            OtherHotplugTablePtr->Function0
                                                            );
        if (IsFchBridge) {
          Buffer[3] = CpmTableProtocolPtr->CommonFunction.GetFchPcieAslName (
                                                            CpmTableProtocolPtr,
                                                            OtherHotplugTablePtr->Device0,
                                                            OtherHotplugTablePtr->Function0
                                                            );
        } else {
          Buffer[3] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (
                                                            CpmTableProtocolPtr,
                                                            OtherHotplugTablePtr->Device0,
                                                            OtherHotplugTablePtr->Function0
                                                            );
        }
      }
      if (OtherHotplugTablePtr->Number > 1) {
        if (OtherHotplugTablePtr->EventSource1 == 0) {
          Buffer[4] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (CpmTableProtocolPtr->CommonFunction.GetSciMap (CpmTableProtocolPtr, OtherHotplugTablePtr->EventPin1));
        } else {
          Buffer[5] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (OtherHotplugTablePtr->QEventFalling1);
          Buffer[6] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (OtherHotplugTablePtr->QEventRising1);
        }
        IsFchBridge = CpmTableProtocolPtr->CommonFunction.IsFchDevice (
                                                            CpmTableProtocolPtr,
                                                            OtherHotplugTablePtr->Device1,
                                                            OtherHotplugTablePtr->Function1
                                                            );
        if (IsFchBridge) {
          Buffer[7] = CpmTableProtocolPtr->CommonFunction.GetFchPcieAslName (
                                                            CpmTableProtocolPtr,
                                                            OtherHotplugTablePtr->Device1,
                                                            OtherHotplugTablePtr->Function1
                                                            );
        } else {
          Buffer[7] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (
                                                            CpmTableProtocolPtr,
                                                            OtherHotplugTablePtr->Device1,
                                                            OtherHotplugTablePtr->Function1
                                                            );
        }
      }
      Buffer[8] = CFG_AMD_CPM_ASL_EC_NAME;      // PcdGet32 (EcAslName)
      Buffer[9] = CFG_AMD_CPM_ASL_LPC_NAME;     // PcdGet32 (LpcAslName)

      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (
                                                          CpmTableProtocolPtr,
                                                          &OTHER_HOTPLUG_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmOtherHotplugSsdtCallBack,
                                                          &Buffer[0]
                                                          );
    }

    if (LowPowerEthernetTablePtr) {
      ZeroMem (Buffer, sizeof (Buffer));
      Buffer[0] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (LowPowerEthernetTablePtr->QEventCablePlugOut);
      Buffer[1] = CpmTableProtocolPtr->CommonFunction.EventAslNameConverter (LowPowerEthernetTablePtr->QEventCablePlugIn);
      Buffer[2] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                        LowPowerEthernetTablePtr->Device,
                                                                        LowPowerEthernetTablePtr->Function );
      Buffer[3] = CFG_AMD_CPM_ASL_LAN_NAME;     // PcdGet32 (LanAslName)
      Buffer[4] = CFG_AMD_CPM_ASL_EC_NAME;      // PcdGet32 (EcAslName)
      Buffer[5] = CFG_AMD_CPM_ASL_LPC_NAME;     // PcdGet32 (LpcAslName)

      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (
                                                          CpmTableProtocolPtr,
                                                          &LOW_POWER_ETHERNET_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmLowPowerEthernetSsdtCallBack,
                                                          &Buffer[0]
                                                          );
    }

    if (WirelessLanRecoveryTablePtr) {
      ZeroMem (Buffer, sizeof (Buffer));
      Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                        WirelessLanRecoveryTablePtr->Device,
                                                                        WirelessLanRecoveryTablePtr->Function );
      Buffer[1] = CFG_AMD_CPM_ASL_WLAN_NAME;    // PcdGet32 (WLanAslName)
      CpmTableProtocolPtr->CommonFunction.AddSsdtTable (
                                                          CpmTableProtocolPtr,
                                                          &WIRELESS_LAN_RECOVERY_ACPI_DEVICE_GUID,
                                                          NULL,
                                                          AmdCpmWirelessLanRecoverySsdtCallBack,
                                                          &Buffer[0]
                                                          );
    }

    CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpPcieInitDxeDriverEnd);
  }

  InitlateInvoked = TRUE;

  RECORD_TIME_DXE (EndAmdCpmPcieInitDxeDriver);

  return;
}
