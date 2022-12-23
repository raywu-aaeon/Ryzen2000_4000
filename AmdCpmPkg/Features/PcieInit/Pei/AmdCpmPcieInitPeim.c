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
#ifdef AGESA_V9
  #include <Ppi/NbioPcieComplexFm15Ppi.h>
  #include <Ppi/NbioPcieComplexPpi.h>
  #include <Library/PeiServicesLib.h>
  #include <Library/PeiServicesTablePointerLib.h>
#endif // #ifdef AGESA_V9

EFI_STATUS
EFIAPI
AmdCpmPcieInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  );

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mCpmPcieInitPeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCpmGpioInitFinishedPpiGuid,
  AmdCpmPcieInitPeim
};

#ifdef AGESA_V9
EFI_STATUS
AmdCpmPcieGetComplexFm15 (
  IN     PEI_AMD_NBIO_PCIE_COMPLEX_FM15_PPI *This,
     OUT PCIe_COMPLEX_DESCRIPTOR            **UserConfig
  )
{
  PCIe_COMPLEX_DESCRIPTOR             *PcieComplex;
  EFI_STATUS                          Status;
  EFI_PEI_SERVICES                    **PeiServices;
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();

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
  PcieComplex = CpmTablePpiPtr->PeimPublicFunction.PcieComplexDescriptorPtr;

  *UserConfig = PcieComplex;
  return EFI_SUCCESS;
}

STATIC PEI_AMD_NBIO_PCIE_COMPLEX_FM15_PPI mPcieComplexFm15Ppi = {
  AMD_NBIO_PCIE_COMPLEX_FM15_REVISION,  ///< revision
  AmdCpmPcieGetComplexFm15
};

EFI_STATUS
AmdCpmDxioGetComplex (
  IN     PEI_AMD_NBIO_PCIE_COMPLEX_PPI *This,
     OUT DXIO_COMPLEX_DESCRIPTOR       **UserConfig
  )
{
  DXIO_COMPLEX_DESCRIPTOR             *DxioComplex;
  EFI_STATUS                          Status;
  EFI_PEI_SERVICES                    **PeiServices;
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();

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
  DxioComplex = CpmTablePpiPtr->PeimPublicFunction.DxioComplexDescriptorPtr;

  *UserConfig = DxioComplex;
  return EFI_SUCCESS;
}

STATIC PEI_AMD_NBIO_PCIE_COMPLEX_PPI mDxioComplexPpi = {
  AMD_NBIO_PCIE_COMPLEX_REVISION,  ///< revision
  AmdCpmDxioGetComplex
};
#endif // #ifdef AGESA_V9

/*----------------------------------------------------------------------------------------*/
/**
 * The Function to reset PCIe device.
 *
 * @param[in]     This          Pointer to AMD CPM Table Ppi
 * @param[in]     ResetId       Pcie Device Id which is defined in Pcie Complex Descriptor table
 * @param[in]     ResetControl  Reset Control Flag. 0: Reset assert. 1: Reset deassert
 *
 * @retval        EFI_SUCCESS   Function initialized successfully
 * @retval        EFI_ERROR     Initialization failed (see error for more details)
 */

VOID
EFIAPI
CpmPcieReset (
  IN      VOID                        *This,
  IN      UINT8                       ResetId,
  IN      UINT8                       ResetControl
  )
{
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr;
  CpmTablePpiPtr = This;
  CpmTablePpiPtr->CommonFunction.ResetDevice (CpmTablePpiPtr, ResetId, ResetControl);

  return;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Generate Pcie Complex Descriptor table for AGESA and set the trigger level of
 * GEVENT pin for Express Card.
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
AmdCpmPcieInitPeim (
  IN       EFI_PEI_SERVICES             **PeiServices,
  IN       EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN       VOID                         *Ppi
  )
{
  AMD_CPM_TABLE_PPI                   *CpmTablePpiPtr;
  AMD_CPM_MAIN_TABLE                  *MainTablePtr;
  AMD_CPM_PCIE_TOPOLOGY_TABLE         *PcieTopologyTablePtr;
  AMD_CPM_PCIE_TOPOLOGY_OVERRIDE_TABLE    *PcieTopologyOverrideTablePtr;
  AMD_CPM_DXIO_TOPOLOGY_TABLE         *DxioTopologyTablePtr;
  AMD_CPM_EXPRESS_CARD_TABLE          *ExpressCardTablePtr;
  AMD_CPM_OTHER_HOTPLUG_CARD_TABLE    *OtherHotplugTablePtr;
  AMD_CPM_WIRELESS_BUTTON_TABLE       *WirelessButtonTablePtr;
  AMD_CPM_SAVE_CONTEXT_TABLE          *SaveContextTablePtr;
  AMD_CPM_PCIE_CLOCK_TABLE            *PcieClockTablePtr;
  PCIe_COMPLEX_DESCRIPTOR             *PcieComplexDescriptorPtr;
  DXIO_COMPLEX_DESCRIPTOR             *DxioComplexDescriptorPtr;
  PCIE_TOPOLOGY_TABLE_PPI             *PcieTopologyTablePpi;
  AMD_CPM_CORE_TOPOLOGY_TABLE         *AmdCpmCoreTopologyPtr;
  EFI_PEI_PPI_DESCRIPTOR              *PpiListPcieTopologyTablePtr;
#ifdef AGESA_V9
  EFI_PEI_PPI_DESCRIPTOR              *PpiListNbioPcieComplexPtr;
#endif // #ifdef AGESA_V9
  EFI_STATUS                          Status;
  UINT8                               Index;
  UINT8                               Offset;
  UINT32                              PCIeStatus;
  UINT8                               i;
  BOOLEAN                             ClockType;
  UINT8                               CpuRevisionId;
  UINT16                              MinLane;
  UINT16                              MaxLane;

  RECORD_TIME_PEI (BeginAmdCpmPcieInitPeimDriver);

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

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpPcieInitPeimDriverBegin);

  MainTablePtr                    = CpmTablePpiPtr->MainTablePtr;
  PcieTopologyTablePtr            = CpmTablePpiPtr->CommonFunction.GetTablePtr2 (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_TOPOLOGY);
  PcieTopologyOverrideTablePtr    = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_TOPOLOGY_OVERRIDE);
  DxioTopologyTablePtr            = CpmTablePpiPtr->CommonFunction.GetTablePtr2 (CpmTablePpiPtr, CPM_SIGNATURE_DXIO_TOPOLOGY);
  ExpressCardTablePtr             = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_EXPRESS_CARD);
  OtherHotplugTablePtr            = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_OTHER_HOTPLUG_CARD);
  WirelessButtonTablePtr          = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_WIRELESS_BUTTON);
  SaveContextTablePtr             = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_SAVE_CONTEXT);
  PcieClockTablePtr               = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_PCIE_CLOCK);
  AmdCpmCoreTopologyPtr           = CpmTablePpiPtr->CommonFunction.GetTablePtr (CpmTablePpiPtr, CPM_SIGNATURE_CORE_TOPOLOGY);
  CpuRevisionId                   = CpmTablePpiPtr->CommonFunction.GetCpuRevisionId (CpmTablePpiPtr);

  if (PcieTopologyTablePtr && PcieTopologyOverrideTablePtr) {
    for (Index = 0; Index < AMD_PCIE_TOPOLOGY_OVERRIDE_SIZE; Index ++) {
      if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Raw == 0xFF) {
        break;
      }
      if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.Valid) {
        Offset = PcieTopologyOverrideTablePtr->Item[Index].Offset;
        if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.IsDdi) {
          if (Offset < AMD_PCIE_DDI_DESCRIPTOR_SIZE) {
            if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.EnableOverride) {
              if (PcieTopologyOverrideTablePtr->Item[Index].Enable) {
                PcieTopologyTablePtr->Ddi[Offset].EngineData.EngineType = PcieDdiEngine;
              } else {
                PcieTopologyTablePtr->Ddi[Offset].EngineData.EngineType = 0;
              }
            }
            if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.DdiTypeOverride) {
              PcieTopologyTablePtr->Ddi[PcieTopologyOverrideTablePtr->Item[Index].Offset].Ddi.ConnectorType = PcieTopologyOverrideTablePtr->Item[Index].DdiType;
            }
            if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.LaneOverride) {
              PcieTopologyTablePtr->Ddi[Offset].EngineData.StartLane = PcieTopologyOverrideTablePtr->Item[Index].StartLane;
              PcieTopologyTablePtr->Ddi[Offset].EngineData.EndLane = PcieTopologyOverrideTablePtr->Item[Index].EndLane;
            }
          }
        } else {
          if (Offset < AMD_PCIE_PORT_DESCRIPTOR_SIZE) {
            if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.EnableOverride) {
              if (PcieTopologyOverrideTablePtr->Item[Index].Enable) {
                PcieTopologyTablePtr->Port[Offset].EngineData.EngineType = PciePortEngine;
              } else {
                PcieTopologyTablePtr->Port[Offset].EngineData.EngineType = 0;
              }
            }
            if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.PortPresentOverride) {
              PcieTopologyTablePtr->Port[Offset].Port.PortPresent = PcieTopologyOverrideTablePtr->Item[Index].PortPresent;
            }
            if (PcieTopologyOverrideTablePtr->Item[Index].Flag.Config.LaneOverride) {
              PcieTopologyTablePtr->Port[Offset].EngineData.StartLane = PcieTopologyOverrideTablePtr->Item[Index].StartLane;
              PcieTopologyTablePtr->Port[Offset].EngineData.EndLane = PcieTopologyOverrideTablePtr->Item[Index].EndLane;
            }
          }
        }
      }
    }
  }

  if (SaveContextTablePtr && PcieTopologyTablePtr && CpmTablePpiPtr->CommonFunction.GetBootMode () == CPM_BOOT_MODE_S3) {
    PCIeStatus = 0;
    PCIeStatus |= CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x00);
    PCIeStatus |= CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x01) << 8;
    PCIeStatus |= CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x02) << 16;
    PCIeStatus |= CpmTablePpiPtr->CommonFunction.GetSaveContext (CpmTablePpiPtr, 0x80 + OFFSET_OF (AMD_CPM_PREDEFINED_SAVE_CONTEXT, PcieDeviceStatus) + 0x03) << 24;
    for ( Index = 0; Index < AMD_PCIE_PORT_DESCRIPTOR_SIZE; Index ++ ) {
      if ((PcieTopologyTablePtr->Port[Index].EngineData.EngineType == PciePortEngine) && (PcieTopologyTablePtr->Port[Index].Port.PortPresent)) {
        if (!(PCIeStatus & (1 << Index))) {
          PcieTopologyTablePtr->Port[Index].Port.PortPresent = PortDisabled;
        }
      }
      if (PcieTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
        break;
      }
    }
  }

  if ((ExpressCardTablePtr || OtherHotplugTablePtr) && PcieTopologyTablePtr) {
    for ( Index = 0; Index < AMD_PCIE_PORT_DESCRIPTOR_SIZE; Index ++ ) {
      if ((PcieTopologyTablePtr->Port[Index].EngineData.EngineType == PciePortEngine) && (PcieTopologyTablePtr->Port[Index].Port.PortPresent)) {
        if (ExpressCardTablePtr && (PcieTopologyTablePtr->Port[Index].Port.DeviceNumber == ExpressCardTablePtr->Device)  &&
           (PcieTopologyTablePtr->Port[Index].Port.FunctionNumber == ExpressCardTablePtr->Function)) {
          PcieTopologyTablePtr->Port[Index].Port.LinkHotplug = HotplugBasic;
          if (CpmTablePpiPtr->CommonFunction.GetGevent (CpmTablePpiPtr, ExpressCardTablePtr->EventPin)) {
            PcieTopologyTablePtr->Port[Index].Port.EndpointStatus = EndpointNotPresent;
          }
        }
        if (OtherHotplugTablePtr) {
          if ((OtherHotplugTablePtr->Number > 0) && (PcieTopologyTablePtr->Port[Index].Port.DeviceNumber == OtherHotplugTablePtr->Device0)  &&
             (PcieTopologyTablePtr->Port[Index].Port.FunctionNumber == OtherHotplugTablePtr->Function0)) {
            PcieTopologyTablePtr->Port[Index].Port.LinkHotplug = HotplugBasic;
            if (CpmTablePpiPtr->CommonFunction.GetGevent (CpmTablePpiPtr, OtherHotplugTablePtr->EventPin0)) {
              PcieTopologyTablePtr->Port[Index].Port.EndpointStatus = EndpointNotPresent;
            }
          }
          if ((OtherHotplugTablePtr->Number > 1) && (PcieTopologyTablePtr->Port[Index].Port.DeviceNumber == OtherHotplugTablePtr->Device1)  &&
             (PcieTopologyTablePtr->Port[Index].Port.FunctionNumber == OtherHotplugTablePtr->Function1)) {
            PcieTopologyTablePtr->Port[Index].Port.LinkHotplug = HotplugBasic;
            if (CpmTablePpiPtr->CommonFunction.GetGevent (CpmTablePpiPtr, OtherHotplugTablePtr->EventPin1)) {
              PcieTopologyTablePtr->Port[Index].Port.EndpointStatus = EndpointNotPresent;
            }
          }
        }
      }
      if (PcieTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
        break;
      }
    }
  }

  if ((ExpressCardTablePtr || OtherHotplugTablePtr) && DxioTopologyTablePtr) {
    for ( Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++ ) {
      if ((DxioTopologyTablePtr->Port[Index].EngineData.EngineType == DxioPcieEngine) && (DxioTopologyTablePtr->Port[Index].Port.PortPresent)) {
        if (ExpressCardTablePtr && (DxioTopologyTablePtr->Port[Index].Port.DeviceNumber == ExpressCardTablePtr->Device)  &&
           (DxioTopologyTablePtr->Port[Index].Port.FunctionNumber == ExpressCardTablePtr->Function)) {
          DxioTopologyTablePtr->Port[Index].EngineData.HotPluggable = HotPluggableDisabled;
          DxioTopologyTablePtr->Port[Index].Port.LinkHotplug = DxioHotplugBasic;
          if (CpmTablePpiPtr->CommonFunction.GetGevent (CpmTablePpiPtr, ExpressCardTablePtr->EventPin)) {
            DxioTopologyTablePtr->Port[Index].Port.EndpointStatus = EndpointNotPresent;
          }
        }
        if (OtherHotplugTablePtr) {
          if ((OtherHotplugTablePtr->Number > 0) && (DxioTopologyTablePtr->Port[Index].Port.DeviceNumber == OtherHotplugTablePtr->Device0)  &&
             (DxioTopologyTablePtr->Port[Index].Port.FunctionNumber == OtherHotplugTablePtr->Function0)) {
            DxioTopologyTablePtr->Port[Index].EngineData.HotPluggable = HotPluggableDisabled;
            if (OtherHotplugTablePtr->HotPlugMode0 == 1) {
              DxioTopologyTablePtr->Port[Index].Port.LinkHotplug = DxioHotplugEnhanced;
            } else {
              DxioTopologyTablePtr->Port[Index].Port.LinkHotplug = DxioHotplugBasic;
            }
            if (CpmTablePpiPtr->CommonFunction.GetGevent (CpmTablePpiPtr, OtherHotplugTablePtr->EventPin0)) {
              DxioTopologyTablePtr->Port[Index].Port.EndpointStatus = DxioEndpointNotPresent;
            }
          }
          if ((OtherHotplugTablePtr->Number > 1) && (DxioTopologyTablePtr->Port[Index].Port.DeviceNumber == OtherHotplugTablePtr->Device1)  &&
             (DxioTopologyTablePtr->Port[Index].Port.FunctionNumber == OtherHotplugTablePtr->Function1)) {
            DxioTopologyTablePtr->Port[Index].EngineData.HotPluggable = HotPluggableDisabled;
            if (OtherHotplugTablePtr->HotPlugMode1 == 1) {
              DxioTopologyTablePtr->Port[Index].Port.LinkHotplug = DxioHotplugEnhanced;
            } else {
              DxioTopologyTablePtr->Port[Index].Port.LinkHotplug = DxioHotplugBasic;
            }
            if (CpmTablePpiPtr->CommonFunction.GetGevent (CpmTablePpiPtr, OtherHotplugTablePtr->EventPin1)) {
              DxioTopologyTablePtr->Port[Index].Port.EndpointStatus = DxioEndpointNotPresent;
            }
          }
        }
      }
      if (DxioTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
        break;
      }
    }
  }

  if (WirelessButtonTablePtr && PcieTopologyTablePtr) {
    if (CpmTablePpiPtr->MainTablePtr->WirelessButtonEn == 2) {
      for ( Index = 0; Index < AMD_PCIE_PORT_DESCRIPTOR_SIZE; Index ++ ) {
        if ((PcieTopologyTablePtr->Port[Index].EngineData.EngineType == PciePortEngine) && (PcieTopologyTablePtr->Port[Index].Port.PortPresent)) {
          for (i = 0; i < 4; i++) {
            if (WirelessButtonTablePtr->Bridge[i].Device || WirelessButtonTablePtr->Bridge[i].Function) {
              if ((PcieTopologyTablePtr->Port[Index].Port.DeviceNumber == WirelessButtonTablePtr->Bridge[i].Device)  &&
                  (PcieTopologyTablePtr->Port[Index].Port.FunctionNumber == WirelessButtonTablePtr->Bridge[i].Function)) {
                PcieTopologyTablePtr->Port[Index].Port.LinkHotplug = HotplugBasic;
              }
            }
          }
        }
        if (PcieTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
          break;
        }
      }
    }
  }

  if (WirelessButtonTablePtr && DxioTopologyTablePtr) {
    if (CpmTablePpiPtr->MainTablePtr->WirelessButtonEn == 2) {
      for ( Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++ ) {
        if ((DxioTopologyTablePtr->Port[Index].EngineData.EngineType == DxioPcieEngine) && (DxioTopologyTablePtr->Port[Index].Port.PortPresent)) {
          for (i = 0; i < 4; i++) {
            if (WirelessButtonTablePtr->Bridge[i].Device || WirelessButtonTablePtr->Bridge[i].Function) {
              if ((DxioTopologyTablePtr->Port[Index].Port.DeviceNumber == WirelessButtonTablePtr->Bridge[i].Device)  &&
                  (DxioTopologyTablePtr->Port[Index].Port.FunctionNumber == WirelessButtonTablePtr->Bridge[i].Function)) {
                DxioTopologyTablePtr->Port[Index].EngineData.HotPluggable = HotPluggableDisabled;
                DxioTopologyTablePtr->Port[Index].Port.LinkHotplug = DxioHotplugBasic;
              }
            }
          }
        }
        if (DxioTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
          break;
        }
      }
    }
  }

  if (PcieClockTablePtr && PcieTopologyTablePtr) {
    ClockType = (BOOLEAN) CpmTablePpiPtr->CommonFunction.GetStrap (CpmTablePpiPtr) & BIT1;
    for ( Index = 0; Index < AMD_PCIE_PORT_DESCRIPTOR_SIZE; Index ++ ) {
      if ((PcieTopologyTablePtr->Port[Index].EngineData.EngineType == PciePortEngine) && (PcieTopologyTablePtr->Port[Index].Port.PortPresent)) {
        for (i = 0; i < AMD_PCIE_CLOCK_SIZE; i++) {
          if ((PcieTopologyTablePtr->Port[Index].Port.DeviceNumber == PcieClockTablePtr->Item[i].Device)  &&
              (PcieTopologyTablePtr->Port[Index].Port.FunctionNumber == PcieClockTablePtr->Item[i].Function)) {
            if (ClockType) {
              if (PcieClockTablePtr->Item[i].ClkReq != 0x00 && PcieClockTablePtr->Item[i].ClkReq != 0xFF) {
                PcieTopologyTablePtr->Port[Index].Port.MiscControls.ClkPmSupport = ClkPmSupportEnabled;
              }
            } else {
              if (PcieClockTablePtr->Item[i].ClkReqExt != 0x00 && PcieClockTablePtr->Item[i].ClkReqExt != 0xFF) {
                PcieTopologyTablePtr->Port[Index].Port.MiscControls.ClkPmSupport = ClkPmSupportEnabled;
              }
            }
          }
        }
      }
      if (PcieTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
        break;
      }
    }
  }

  if (PcieClockTablePtr && DxioTopologyTablePtr) {
    ClockType = (BOOLEAN) CpmTablePpiPtr->CommonFunction.GetStrap (CpmTablePpiPtr) & BIT1;
    for ( Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++ ) {
      if ((DxioTopologyTablePtr->Port[Index].EngineData.EngineType == DxioPcieEngine) && (DxioTopologyTablePtr->Port[Index].Port.PortPresent)) {
        for (i = 0; i < AMD_PCIE_CLOCK_SIZE; i++) {
          MinLane = 0;
          if (AmdCpmCoreTopologyPtr) {
            MinLane = (UINT16) (((PcieClockTablePtr->Item[i].SpecialFunctionId >> 24) & 0xF) * ((AmdCpmCoreTopologyPtr->Header.Attribute >> 12) & 0xF) * ((AmdCpmCoreTopologyPtr->Header.Attribute >> 8) & 0xF) * 32);
            MinLane += (UINT16) (((PcieClockTablePtr->Item[i].SpecialFunctionId >> 20) & 0xF) * ((AmdCpmCoreTopologyPtr->Header.Attribute >> 8) & 0xF) * 32);
            MinLane += (UINT16) (((PcieClockTablePtr->Item[i].SpecialFunctionId >> 16) & 0xF) * 32);
          }
          if ((CpuRevisionId == CPM_CPU_REVISION_ID_RV) || (CpuRevisionId == CPM_CPU_REVISION_ID_RV2) || \
              (CpuRevisionId == CPM_CPU_REVISION_ID_RN)) {
            MaxLane = MinLane + 16;
          } else {
            MaxLane = MinLane + 32;
          }
          if ((DxioTopologyTablePtr->Port[Index].Port.DeviceNumber == PcieClockTablePtr->Item[i].Device)  &&
              (DxioTopologyTablePtr->Port[Index].Port.FunctionNumber == PcieClockTablePtr->Item[i].Function)  &&
              ((UINT16) DxioTopologyTablePtr->Port[Index].EngineData.StartLane >= MinLane)  &&
              ((UINT16) DxioTopologyTablePtr->Port[Index].EngineData.StartLane < MaxLane)) {
            if (ClockType) {
              if (PcieClockTablePtr->Item[i].ClkReq != 0x00 && PcieClockTablePtr->Item[i].ClkReq != 0xFF) {
                DxioTopologyTablePtr->Port[Index].Port.MiscControls.ClkPmSupport = DxioClkPmSupportEnabled;
              }
            } else {
              if (PcieClockTablePtr->Item[i].ClkReqExt != 0x00 && PcieClockTablePtr->Item[i].ClkReqExt != 0xFF) {
                DxioTopologyTablePtr->Port[Index].Port.MiscControls.ClkPmSupport = DxioClkPmSupportEnabled;
              }
            }
          }
        }
      }
      if (DxioTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
        break;
      }
    }
  }

  if ((DxioTopologyTablePtr) && (CpuRevisionId == CPM_CPU_REVISION_ID_RV2)) {
    for ( Index = 0; Index < AMD_DXIO_PORT_DESCRIPTOR_SIZE; Index ++ ) {
      if ( (DxioTopologyTablePtr->Port[Index].EngineData.EngineType == DxioPcieEngine) && \
           (DxioTopologyTablePtr->Port[Index].Port.PortPresent) && \
           ((DxioTopologyTablePtr->Port[Index].Port.ClkReq == 0x06) || (DxioTopologyTablePtr->Port[Index].Port.ClkReq == 0x07)) ) {
        // RV2 disable CLK_REQ5 & CLK_REQ6 L1.1 & L1.2 support
        DxioTopologyTablePtr->Port[Index].Port.LinkAspmL1_1 = DxioAspmL11Disabled;
        DxioTopologyTablePtr->Port[Index].Port.LinkAspmL1_2 = DxioAspmL12Disabled;
      }
      if (DxioTopologyTablePtr->Port[Index].Flags == DESCRIPTOR_TERMINATE_LIST) {
        break;
      }
    }
  }

  if (PcieTopologyTablePtr) {
    Status = (**PeiServices).AllocatePool (
                                            (CPM_PEI_SERVICES**)PeiServices,
                                            sizeof (PCIe_COMPLEX_DESCRIPTOR),
                                            (VOID**)&PcieComplexDescriptorPtr
                                            );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    (**PeiServices).SetMem (
                            PcieComplexDescriptorPtr,
                            sizeof (PCIe_COMPLEX_DESCRIPTOR),
                            0
                           );
    PcieComplexDescriptorPtr->Flags         = DESCRIPTOR_TERMINATE_LIST;
    PcieComplexDescriptorPtr->SocketId      = 0;
    PcieComplexDescriptorPtr->PciePortList  = &PcieTopologyTablePtr->Port[0];
    PcieComplexDescriptorPtr->DdiLinkList   = &PcieTopologyTablePtr->Ddi[0];
    CpmTablePpiPtr->PeimPublicFunction.PcieComplexDescriptorPtr  = PcieComplexDescriptorPtr;
  }

  CpmTablePpiPtr->PeimPublicFunction.PcieReset                = CpmPcieReset;

  if (DxioTopologyTablePtr) {
    Status = (**PeiServices).AllocatePool (
                                            (CPM_PEI_SERVICES**)PeiServices,
                                            sizeof (DXIO_COMPLEX_DESCRIPTOR),
                                            (VOID**)&DxioComplexDescriptorPtr
                                            );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    (**PeiServices).SetMem (
                            DxioComplexDescriptorPtr,
                            sizeof (DXIO_COMPLEX_DESCRIPTOR),
                            0
                           );
    DxioComplexDescriptorPtr->Flags         = DESCRIPTOR_TERMINATE_LIST;
    DxioComplexDescriptorPtr->SocketId      = 0;
    DxioComplexDescriptorPtr->PciePortList  = &DxioTopologyTablePtr->Port[0];
    DxioComplexDescriptorPtr->DdiLinkList   = &DxioTopologyTablePtr->Ddi[0];
    CpmTablePpiPtr->PeimPublicFunction.DxioComplexDescriptorPtr  = DxioComplexDescriptorPtr;
  }

  Status = (*PeiServices)->AllocatePool (
                              (CPM_PEI_SERVICES**)PeiServices,
                              sizeof (PCIE_TOPOLOGY_TABLE_PPI),
                              (VOID**)&PcieTopologyTablePpi
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = (*PeiServices)->AllocatePool (
                              (CPM_PEI_SERVICES**)PeiServices,
                              sizeof (EFI_PEI_PPI_DESCRIPTOR),
                              (VOID**)&PpiListPcieTopologyTablePtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  PpiListPcieTopologyTablePtr->Flags   = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  PpiListPcieTopologyTablePtr->Guid    = &gPcieTopologyTablePpiGuid;
  PpiListPcieTopologyTablePtr->Ppi     = PcieTopologyTablePpi;
  Status = (*PeiServices)->InstallPpi (
                              (CPM_PEI_SERVICES**)PeiServices,
                              PpiListPcieTopologyTablePtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

#ifdef AGESA_V9
  Status = (*PeiServices)->AllocatePool (
                              (CPM_PEI_SERVICES**)PeiServices,
                              sizeof (EFI_PEI_PPI_DESCRIPTOR),
                              (VOID**)&PpiListNbioPcieComplexPtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  PpiListNbioPcieComplexPtr->Flags   = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  if (CpuRevisionId < CPM_CPU_REVISION_ID_ZP) {
    PpiListNbioPcieComplexPtr->Guid    = &gAmdNbioPcieComplexFm15PpiGuid;
    PpiListNbioPcieComplexPtr->Ppi     = (void *) &mPcieComplexFm15Ppi;
  } else {
    PpiListNbioPcieComplexPtr->Guid    = &gAmdNbioPcieComplexPpiGuid;
    PpiListNbioPcieComplexPtr->Ppi     = (void *) &mDxioComplexPpi;
  }

  Status = (*PeiServices)->InstallPpi (
                              (CPM_PEI_SERVICES**)PeiServices,
                              PpiListNbioPcieComplexPtr
                              );
  if (EFI_ERROR (Status)) {
    return Status;
  }
#endif // #ifdef AGESA_V9

  CpmTablePpiPtr->CommonFunction.PostCode (CpmTpPcieInitPeimDriverEnd);

  RECORD_TIME_PEI (EndAmdCpmPcieInitPeimDriver);

  return Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM PCIE Init PEIM driver
 *
 * This function registers the function to update PCIe topology table according
 * to AMD CPM PCIE TOPOLOGY OVERRIDE table and set GEVENT trigger level for Express
 * Card if AMD CPM Express Card Table exists.
 *
 * @param[in]     FileHandle     Pointer to the firmware file system header
 * @param[in]     PeiServices    Pointer to Pei Services
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmPcieInitPeimEntryPoint (
  IN        CPM_PEI_FILE_HANDLE         FileHandle,
  IN        CPM_PEI_SERVICES            **PeiServices
  )
{
  EFI_STATUS                      Status;

  Status = (**PeiServices).NotifyPpi (PeiServices, &mCpmPcieInitPeimNotify);

  return EFI_SUCCESS;
}
