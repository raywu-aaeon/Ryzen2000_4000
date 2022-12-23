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

EFI_GUID DISPLAY_FEATURE_I_ACPI_DEVICE_GUID = {
  0x9d695853, 0xa840, 0x4670, 0x9d, 0xae, 0x95, 0x11, 0x16, 0xe8, 0x11, 0x51
};

EFI_GUID DISPLAY_FEATURE_I2_ACPI_DEVICE_GUID = {
  0xE751E272, 0x9D7A, 0x4E8F, 0x8B, 0xB4, 0x52, 0x21, 0x52, 0xE8, 0xEB, 0x49
};

EFI_GUID DISPLAY_FEATURE_NoI_ACPI_DEVICE_GUID = {
  0xC7E9B6A4, 0x7149, 0x4135, 0xBD, 0xFC, 0xB8, 0x32, 0x7B, 0xBC, 0x93, 0x25
};

EFI_GUID DISPLAY_FEATURE_D_ACPI_DEVICE_GUID = {
  0x78db63b7, 0xe9f4, 0x4244, 0x90, 0xc6, 0xf5, 0x84, 0x59, 0x12, 0xeb, 0x3b
};

EFI_GUID DISPLAY_FEATURE_D2_ACPI_DEVICE_GUID = {
  0x245031A5, 0x33E6, 0x4962, 0x9B, 0x66, 0x95, 0xCF, 0x63, 0x26, 0x36, 0x66
};

EFI_GUID DISPLAY_FEATURE_MXM_OVERT_ACPI_DEVICE_GUID = {
  0xe0ec8f82, 0xfd17, 0x4f8d, 0x8d, 0xff, 0xa4, 0xcf, 0xfb, 0xe7, 0x4c, 0x4d
};

EFI_GUID DISPLAY_FEATURE_DISPLAY_CONNECT_EVENT_ACPI_DEVICE_GUID = {
  0x6476864d, 0xf8a0, 0x460e, 0x94, 0x7b, 0x5f, 0x7b, 0x88, 0xa5, 0x21, 0x16
};

EFI_GUID DISPLAY_FEATURE_DGPU_D3_COLD_ACPI_DEVICE_GUID = {
  0x3c673ccc, 0x25e0, 0x454b, 0xa4, 0xb9, 0x10, 0x8f, 0xb8, 0xca, 0xac, 0x1a
};

EFI_GUID DISPLAY_FEATURE_ATPX_DGPU_ACPI_DEVICE_GUID = {
  0x96A507FB, 0x20F6, 0x44F3, 0x9B, 0x91, 0x75, 0xAB, 0xD0, 0xE0, 0x49, 0x3B
};

EFI_GUID DISPLAY_FEATURE_ATPX_DGPU2_ACPI_DEVICE_GUID = {
  0x5D263214, 0x3BB4, 0x43CC, 0xB2, 0x03, 0x87, 0xD4, 0xB1, 0xF9, 0xE6, 0xF2
};

EFI_GUID DISPLAY_FEATURE_ATPX_IGPU_ACPI_DEVICE_GUID = {
  0x652EF761, 0x119A, 0x4FD2, 0xB2, 0x1E, 0xEF, 0xD8, 0x34, 0x93, 0xBA, 0x5A
};

EFI_GUID DISPLAY_FEATURE_ATPX_IGPU2_ACPI_DEVICE_GUID = {
  0x1CC2006D, 0xFABC, 0x4936, 0xA5, 0x52, 0xDC, 0x1E, 0xC2, 0xA4, 0x44, 0xD0
};

VOID
AmdCpmDisplayFeatureInitLate (
  IN        AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr
  );

BOOLEAN
EFIAPI
AmdCpmIGpuSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  );

BOOLEAN
EFIAPI
AmdCpmDGpuSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  );

BOOLEAN
EFIAPI
AmdCpmDGpuD3ColdCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  );

BOOLEAN
EFIAPI
AmdCpmMxmOverTSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  );

BOOLEAN
EFIAPI
AmdCpmDisplayConnectEventSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  );

/*----------------------------------------------------------------------------------------*/
/**
 * AmdCpmDisplayFeatureInitLateEntry
 *
 * This function is called as part of CPM DXE Driver Initialization. It gets called
 * each time the EFI_EVENT_SIGNAL_READY_TO_BOOT gets signaled.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmDisplayFeatureInitLateEntry (
  IN EFI_EVENT          Event,
  IN VOID               *Context
  )
{
  STATIC BOOLEAN  AmdCpmDisplayFeatureInitLateEntryInvoked = FALSE;

  RECORD_TIME_DXE (BeginAmdCpmDisplayFeatureLateInit);

  if (!AmdCpmDisplayFeatureInitLateEntryInvoked) {
    AmdCpmDisplayFeatureInitLate (Context);
  }

  AmdCpmDisplayFeatureInitLateEntryInvoked = TRUE;

  RECORD_TIME_DXE (EndAmdCpmDisplayFeatureLateInit);
}


/*----------------------------------------------------------------------------------------*/
/**
 *
 * The function to set Sub-System Id on iGPU and dGPU, update NV Data for
 * Display Feature and install Display Feature SSDT tables for iGPU and dGPU.
 *
 * @param[in]     CpmDisplayFeatureProtocolPtr  Pointer to AMD CPM Display Feature Protocol
 *
 */

VOID
AmdCpmDisplayFeatureInitLate (
  IN        AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr
  )
{
  AMD_CPM_MAIN_TABLE              *MainTablePtr;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_NV_DATA_PROTOCOL        *pAmdCpmNvDataProtocol;
  AMD_CPM_DISPLAY_FEATURE_TABLE   *DisplayFeatureTablePtr;
  AMD_CPM_DEVICE_PATH_TABLE       *DevicePathTablePtr;
  AMD_CPM_SPECIFIC_SSID_TABLE     *SpecificSsidTablePtr;
  AMD_CPM_REBRAND_DUAL_GRAPHICS_SSID_TABLE  *RebrandDualGraphicsSsidTablePtr;
  AMD_CPM_REBRAND_DUAL_GRAPHICS_SSID_TABLE2 *RebrandDualGraphicsSsidTable2Ptr;
  AMD_CPM_PCIE_TOPOLOGY_TABLE     *PcieTopologyTablePtr;
  AMD_CPM_DXIO_TOPOLOGY_TABLE     *DxioTopologyTablePtr;
  PCIe_PORT_DESCRIPTOR            *PciePortDescriptorPtr;
  DXIO_PORT_DESCRIPTOR            *DxioPortDescriptorPtr;
  AMD_CPM_GFX_DETECT              GfxDetect;
  EFI_STATUS                      Status;
  UINT8                           Bus;
  UINT8                           Dev;
  UINT8                           Func;
  UINT16                          VendorId;
  UINT16                          VendorId2;
  UINT16                          DeviceId;
  UINT16                          DeviceId2;
  UINT32                          Index;
  AMD_CPM_NV_DATA_STRUCT          *eNvStore;
  UINT32                          VbiosAddr;
  UINT32                          VbiosSize;
  UINT32                          Ssid;
  UINT32                          NewSsid;
  UINT32                          DgpuSsid;
  UINT32                          DgpuAudioSsid;
  UINT16                          j;
  UINT8                           i;
  UINT8                           iGpuIndex;
  UINT8                           dGpuIndex;
  UINT32                          Buffer[35];
  CPM_DISPLAY_FEATURE_PRIVATE     *DisplayFeatureDataPtr;
  UINT8                           SciMap;
  UINT8                           RevId;
  UINT16                          iSsid;
  UINT32                          PowerXpressFixedMode;
  UINT32                          PowerXpressDynamicMode;
  UINT32                          HyperCrossFire;
  UINT32                          IsDgpuPrimary;
  UINT32                          IsBrightnessByDriver;
  UINT32                          DisableDgpuAudioInPX;
  UINT32                          DualGraphicsNotSupported;
  UINT32                          PulseGeneratorSupport;
  UINT32                          RebrandDualGraphics;
  UINT32                          FullPciEmulationSupport;
  UINT32                          DetachableGraphicsSupport;
  UINT32                          D3ColdSupport;
  UINT32                          HybridGraphicsSupport;
  UINT32                          CurrentPowerXpress;
  UINT32                          CurrentHyperCrossFire;
  UINT32                          CurrentHybridGraphics;

  Status        = EFI_SUCCESS;
  Bus           = 0;
  Dev           = 0;
  Func          = 0;
  VendorId      = 0;
  DeviceId      = 0;
  eNvStore      = 0;
  DgpuSsid      = PcdGet32 (PcdCpmDgpuSsid);
  DgpuAudioSsid = PcdGet32 (PcdCpmDgpuAudioSsid);

  CpmTableProtocolPtr = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;
  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDxeInitLateBegin);

  Status = gBS->LocateProtocol (  &gAmdCpmNvDataProtocolGuid,
                                  NULL,
                                  (VOID**)&pAmdCpmNvDataProtocol );
  if (EFI_ERROR (Status)) {
    return;
  }

  eNvStore                  = pAmdCpmNvDataProtocol->NvDataPtr;
  PcieTopologyTablePtr      = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_PCIE_TOPOLOGY);
  DxioTopologyTablePtr      = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_DXIO_TOPOLOGY);

  DisplayFeatureDataPtr     = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
  MainTablePtr              = CpmTableProtocolPtr->MainTablePtr;
  PowerXpressFixedMode      = MainTablePtr->DisplayFeature.Config.PowerXpressFixedMode;
  PowerXpressDynamicMode    = MainTablePtr->DisplayFeature.Config.PowerXpressDynamicMode;
  HyperCrossFire            = MainTablePtr->DisplayFeature.Config.HyperCrossFire;
  IsBrightnessByDriver      = MainTablePtr->DisplayFeature.Config.IsBrightnessByDriver;
  DisableDgpuAudioInPX      = MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX;
  DualGraphicsNotSupported  = MainTablePtr->DisplayFeature.Config.DualGraphicsNotSupported;
  PulseGeneratorSupport     = MainTablePtr->DisplayFeature.Config.PulseGeneratorSupport;
  RebrandDualGraphics       = MainTablePtr->DisplayFeature.Config.RebrandDualGraphics;
  FullPciEmulationSupport   = MainTablePtr->DisplayFeature.Config.FullPciEmulationSupport;
  DetachableGraphicsSupport = MainTablePtr->DisplayFeature.Config.DetachableGraphicsSupport;
  D3ColdSupport             = MainTablePtr->DisplayFeature.Config.D3ColdSupport;
  HybridGraphicsSupport     = MainTablePtr->DisplayFeature.Config.HybridGraphicsSupport;
  DisplayFeatureTablePtr    = DisplayFeatureDataPtr->DisplayFeatureTablePtr;
  DevicePathTablePtr        = DisplayFeatureDataPtr->DevicePathTablePtr;
  SpecificSsidTablePtr      = DisplayFeatureDataPtr->SpecificSsidTablePtr;
  RebrandDualGraphicsSsidTablePtr   = DisplayFeatureDataPtr->RebrandDualGraphicsSsidTablePtr;
  RebrandDualGraphicsSsidTable2Ptr  = DisplayFeatureDataPtr->RebrandDualGraphicsSsidTablePtr;
  CurrentPowerXpress        = DisplayFeatureDataPtr->CurrentFeature.Mask.PowerXpress;
  CurrentHyperCrossFire     = DisplayFeatureDataPtr->CurrentFeature.Mask.HyperCrossFire;
  CurrentHybridGraphics     = DisplayFeatureDataPtr->CurrentFeature.Mask.HybridGraphics;

  if (DisplayFeatureTablePtr) {
    if (RebrandDualGraphics && RebrandDualGraphicsSsidTablePtr) {
      if (RebrandDualGraphicsSsidTablePtr->Header.FormatRevision != 0) {
        DisplayFeatureTablePtr->FunctionDisableMask |= BIT0;
      }
    }

    VbiosAddr = DisplayFeatureDataPtr->VBiosImage;
    if (VbiosAddr != 0xFFFFFFFF && VbiosAddr != 0) {
      VbiosSize = (*((UINT8*) (EFI_PHYSICAL_ADDRESS) VbiosAddr + 2)) << 9;
      eNvStore->CpmAtrmRomSize = (UINT32)VbiosSize;
      if (VbiosSize != 0 && VbiosSize <= 0x10000) {
        CpmTableProtocolPtr->CommonFunction.CopyMem ( &eNvStore->CpmAtrmRomImage[0],
                                                      (VOID *) (EFI_PHYSICAL_ADDRESS)VbiosAddr,
                                                      (UINTN)VbiosSize );
      }
    }

    eNvStore->CpmDisplayFeatureConfig = MainTablePtr->DisplayFeature.Raw;

    // ATCS
    eNvStore->CpmAtcsSupportedFunctionMask = 0x0F;                                                    // AtcsSupportedFunctionMask;

    // AtpxSupportedFunctionMask
        if (DisplayFeatureTablePtr->MuxFlag) {
          eNvStore->CpmAtpxSupportedFunctionMask |= 0x0000018F;
        } else {
          if (CurrentPowerXpress) {
            eNvStore->CpmAtpxSupportedFunctionMask |= 0x00000003;
          } else if (CurrentHybridGraphics) {
            eNvStore->CpmAtpxSupportedFunctionMask |= 0x00000001;
          }
          if (DisplayFeatureTablePtr->MacoGpio != 0) {
            eNvStore->CpmAtpxSupportedFunctionMask |= 0x00000200;
          }
          if (FullPciEmulationSupport) {
            eNvStore->CpmAtpxSupportedFunctionMask |= 0x00000400;
          }
        }

    // AtpxFlags
    if (DisplayFeatureTablePtr->MuxFlag) {
      eNvStore->CpmAtpxFlags |= DisplayFeatureTablePtr->MuxFlag;
    } else {
      if (PowerXpressDynamicMode == 1) {
        eNvStore->CpmAtpxFlags |= 0x00000480;                                                         // PX Dynamic Mode Support Full dGPU Powerdown
      } else if (PowerXpressDynamicMode == 2) {
        eNvStore->CpmAtpxFlags |= 0x00000080;
      } else if (HybridGraphicsSupport) {
        eNvStore->CpmAtpxFlags |= 0x00004000;
      }
      if (DualGraphicsNotSupported) {
        eNvStore->CpmAtpxFlags |= 0x00000100;
      }
      if (!PulseGeneratorSupport) {
        eNvStore->CpmAtpxFlags |= 0x00000800;
      }
      if (FullPciEmulationSupport) {
        eNvStore->CpmAtpxFlags |= 0x00008000;
      }
      if (DetachableGraphicsSupport) {
        eNvStore->CpmAtpxFlags |= 0x00010000;
      }
    }

    // ATIF
    eNvStore->CpmAtifSupportedNotificationMask |= DisplayFeatureTablePtr->AtifSupportedNotificationMask;// AtifSupportedNotificationMask
    if (CurrentPowerXpress || CurrentHybridGraphics) {
      eNvStore->CpmAtifSupportedNotificationMask |= 0x40;
    } else {
      eNvStore->CpmAtifSupportedNotificationMask &= 0xFFFFFFDF;
    }
    if (IsBrightnessByDriver) {
      eNvStore->CpmAtifSupportedNotificationMask |= 0x80;
    } else {
      eNvStore->CpmAtifSupportedNotificationMask &= 0xFFFFFF7F;
    }
    if (DisplayFeatureTablePtr->MxmOverTempEvent == 0xFF) {
      eNvStore->CpmAtifSupportedNotificationMask &= 0xFFFFFFF7;
    }
    eNvStore->CpmAtifSupportedNotificationMask |= 0x100;
    eNvStore->CpmAtifFunctionBitVector = 0xC00F;                                                        // AtifFunctionBitVector
    eNvStore->CpmAtifFlags = 0x00000001;                                                                // AtifFlags

    GfxDetect.NumDevice         = 0;
    GfxDetect.DeviceStructSize  = 8;
    for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
      if (DevicePathTablePtr->Path[i].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid == 0) {
        break;
      }
      if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid && DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist) {
        if (CurrentPowerXpress || CurrentHybridGraphics) {
          GfxDetect.Device[GfxDetect.NumDevice].Flags = DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga << 2;
        } else {
          GfxDetect.Device[GfxDetect.NumDevice].Flags = DevicePathTablePtr->Path[i].FeatureMask.Mask.Removable | (DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga << 2);
        }
        GfxDetect.Device[GfxDetect.NumDevice].Bus     = (UINT16)DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus;
        GfxDetect.Device[GfxDetect.NumDevice].Device  = DevicePathTablePtr->Path[i].Device.Device;
        GfxDetect.NumDevice++;
      }
    }

    CpmTableProtocolPtr->CommonFunction.CopyMem ( &eNvStore->CpmAtifDeviceListBuffer[0],
                                                  &GfxDetect,
                                                  sizeof(AMD_CPM_GFX_DETECT) );                         // AtifDeviceListBuffer

    eNvStore->CpmiGpuP2pBridgePfa = DisplayFeatureDataPtr->GfxBridgePfa[0].Raw;                         // iGpuP2pBridgePfa
    eNvStore->CpmiGpuP2pDevicePfa = DisplayFeatureDataPtr->GfxDevicePfa[0].Raw;                         // iGpuP2pDevicePfa
    eNvStore->CpmdGpuP2pBridgePfa = DisplayFeatureDataPtr->GfxBridgePfa[1].Raw;                         // dGpuP2pBridgePfa
    eNvStore->CpmdGpuP2pDevicePfa = DisplayFeatureDataPtr->GfxDevicePfa[1].Raw;                         // dGpuP2pDevicePfa

    eNvStore->CpmdGpuAspmLxEnable = 0;                                                                  // dGpuAspmLxEnable
    if (PcieTopologyTablePtr && eNvStore->CpmdGpuP2pBridgePfa) {
      PciePortDescriptorPtr   = &PcieTopologyTablePtr->Port[0];
      while (TRUE) {
        if (PciePortDescriptorPtr->Port.DeviceNumber == DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Device) {
          if (PciePortDescriptorPtr->Port.FunctionNumber == DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Function) {
            eNvStore->CpmdGpuAspmLxEnable = CpmTableProtocolPtr->CommonFunction.PciRead8 (  CpmTableProtocolPtr,
                                                                                            DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Bus,
                                                                                            DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Device,
                                                                                            DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Function,
                                                                                            0x68 );
            break;
          }
        }
        if (PciePortDescriptorPtr->Flags & DESCRIPTOR_TERMINATE_LIST) {
          break;
        }
        PciePortDescriptorPtr ++;
      }
    }

    if (DxioTopologyTablePtr && eNvStore->CpmdGpuP2pBridgePfa) {
      DxioPortDescriptorPtr   = &DxioTopologyTablePtr->Port[0];
      while (TRUE) {
        if (DxioPortDescriptorPtr->Port.DeviceNumber == DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Device) {
          if (DxioPortDescriptorPtr->Port.FunctionNumber == DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Function) {
            eNvStore->CpmdGpuAspmLxEnable = CpmTableProtocolPtr->CommonFunction.PciRead8 (  CpmTableProtocolPtr,
                                                                                            DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Bus,
                                                                                            DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Device,
                                                                                            DisplayFeatureDataPtr->GfxBridgePfa[1].Pfa.Function,
                                                                                            0x68 );
            break;
          }
        }
        if (DxioPortDescriptorPtr->Flags & DESCRIPTOR_TERMINATE_LIST) {
          break;
        }
        DxioPortDescriptorPtr ++;
      }
    }

    iGpuIndex = 0xFF;
    dGpuIndex = 0xFF;
    i = 0;
    while (i < AMD_DISPLAY_DEVICE_PATH_SIZE) {
      if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
        break;
      }
      if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[i].IsDgpu) {
        iGpuIndex = i;
      }
      if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[i].IsDgpu && DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga) {
        dGpuIndex = i;
      }
      i++;
    }
    if (iGpuIndex == 0xFF) {
      MainTablePtr->DisplayFeature.Config.IsDgpuPrimary = 1;
    }
    if (dGpuIndex == 0xFF) {
      i = 0;
      while (i < AMD_DISPLAY_DEVICE_PATH_SIZE) {
        if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
          break;
        }
        if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[i].IsDgpu) {
          dGpuIndex = i;
          break;
        }
        i++;
      }
    }
    if (dGpuIndex == 0xFF) {
      MainTablePtr->DisplayFeature.Config.IsDgpuPrimary = 0;
      i = 0;
      while (i < AMD_DISPLAY_DEVICE_PATH_SIZE) {
        if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
          break;
        }
        if (DevicePathTablePtr->Path[i].IsDgpu) {
          dGpuIndex = i;
          break;
        }
        i++;
      }
    }

    IsDgpuPrimary = MainTablePtr->DisplayFeature.Config.IsDgpuPrimary;

    eNvStore->CpmdGpuAudioDisable = 0;
    if (DisableDgpuAudioInPX) {
      eNvStore->CpmdGpuAudioDisable = CFG_CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI;
    }

    eNvStore->CpmDisplayFeatureConfig = MainTablePtr->DisplayFeature.Raw;

    for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
      if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
        break;
      }
      if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu && DevicePathTablePtr->Path[Index].IsDgpu) {
        Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
        Dev       = DevicePathTablePtr->Path[Index].Device.Device;
        Func      = DevicePathTablePtr->Path[Index].Device.Function;
        DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x02);
        DeviceId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func + 1, 0x02);
        if ((DgpuSsid != 0) && (DeviceId != 0xFFFF)) {
          CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func, 0x4C, DgpuSsid);
        }
        if ((DgpuAudioSsid != 0) && (DeviceId2 != 0xFFFF)) {
          CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func + 1, 0x4C, DgpuAudioSsid);
        }
      } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu && DevicePathTablePtr->Path[Index].IsDgpu)
    } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)

    if (!(DisplayFeatureTablePtr->FunctionDisableMask & BIT0)) {
      if (PowerXpressFixedMode || PowerXpressDynamicMode || HybridGraphicsSupport) {
        Ssid = 0x01240000;
      } else if (HyperCrossFire) {
        if (IsDgpuPrimary) {
          Ssid = 0x01250000;
        } else {
          Ssid = 0x01260000;
        }
      } else {
        Ssid = 0x01230000;
      }

      DisplayFeatureDataPtr->Ssid = Ssid;

      for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
        if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
          break;
        }
        if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu) {
          Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
          Dev       = DevicePathTablePtr->Path[Index].Device.Device;
          Func      = DevicePathTablePtr->Path[Index].Device.Function;
          VendorId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                      Bus,
                                                                      Dev,
                                                                      Func,
                                                                      0x00 );
          DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                      Bus,
                                                                      Dev,
                                                                      Func,
                                                                      0x02 );
          DeviceId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                      Bus,
                                                                      Dev,
                                                                      Func + 1,
                                                                      0x02 );
          NewSsid   = Ssid | (UINT32)VendorId;
          if (SpecificSsidTablePtr) {
            for (j = 0; j < AMD_SPECIFIC_SSID_DEVICE_SIZE; j++) {
              if (SpecificSsidTablePtr->Item[j].VendorId == 0xFFFF) {
                break;
              } else {
                if ((SpecificSsidTablePtr->Item[j].VendorId == VendorId) && (SpecificSsidTablePtr->Item[j].DeviceId == DeviceId)) {
                  CpmTableProtocolPtr->CommonFunction.PciWrite32 (  CpmTableProtocolPtr,
                                                                    Bus,
                                                                    Dev,
                                                                    Func,
                                                                    0x4C,
                                                                    NewSsid );
                }
                if ((DeviceId2 != 0xFFFF) && (SpecificSsidTablePtr->Item[j].VendorId == VendorId) && (SpecificSsidTablePtr->Item[j].DeviceId == DeviceId2)) {
                  CpmTableProtocolPtr->CommonFunction.PciWrite32 (  CpmTableProtocolPtr,
                                                                    Bus,
                                                                    Dev,
                                                                    Func + 1,
                                                                    0x4C,
                                                                    NewSsid );
                }
              }
            }
          } else if (DgpuSsid == 0) {
            CpmTableProtocolPtr->CommonFunction.PciWrite32 (  CpmTableProtocolPtr,
                                                              Bus,
                                                              Dev,
                                                              Func,
                                                              0x4C,
                                                              NewSsid );
          }
        } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu)
      } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)
    } // End of if (!(DisplayFeatureTablePtr->FunctionDisableMask & BIT0))

    if (RebrandDualGraphics && RebrandDualGraphicsSsidTablePtr) {
      switch (RebrandDualGraphicsSsidTablePtr->Header.FormatRevision) {
      case 0:
        Ssid = 0xFFFF0000;
        for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
          if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
            break;
          }
          if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].IsDgpu) {
            Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
            Dev       = DevicePathTablePtr->Path[Index].Device.Device;
            Func      = DevicePathTablePtr->Path[Index].Device.Function;
            VendorId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                        Bus,
                                                                        Dev,
                                                                        Func,
                                                                        0x00 );
            DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                        Bus,
                                                                        Dev,
                                                                        Func,
                                                                        0x02 );

            for (j = 0; j < AMD_REBRAND_DUAL_GRAPHICS_SSID_DEVICE_SIZE; j++) {
              if (RebrandDualGraphicsSsidTablePtr->Item[j].VendorId == 0xFFFF) {
                break;
              } else {
                if ((RebrandDualGraphicsSsidTablePtr->Item[j].VendorId == VendorId) &&
                    (RebrandDualGraphicsSsidTablePtr->Item[j].DeviceId == DeviceId) &&
                    (RebrandDualGraphicsSsidTablePtr->Item[j].IsDgpu == 0)) {
                    Ssid = ((UINT32) DeviceId) << 16;
                  break;
                }
              }
            }
          } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].IsDgpu)
        } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)
        DisplayFeatureDataPtr->Ssid2 = Ssid;
        if (Ssid != 0xFFFF0000) {
          for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
            if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
              break;
            }
            if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[Index].IsDgpu) {
              Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
              Dev       = DevicePathTablePtr->Path[Index].Device.Device;
              Func      = DevicePathTablePtr->Path[Index].Device.Function;
              VendorId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                          Bus,
                                                                          Dev,
                                                                          Func,
                                                                          0x00 );
              VendorId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                          Bus,
                                                                          Dev,
                                                                          Func,
                                                                          0x2C );
              DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                          Bus,
                                                                          Dev,
                                                                          Func,
                                                                          0x02 );
              NewSsid   = Ssid | (UINT32)VendorId2;

              for (j = 0; j < AMD_REBRAND_DUAL_GRAPHICS_SSID_DEVICE_SIZE; j++) {
                if (RebrandDualGraphicsSsidTablePtr->Item[j].VendorId == 0xFFFF) {
                  break;
                } else {
                  if ((RebrandDualGraphicsSsidTablePtr->Item[j].VendorId == VendorId) &&
                      (RebrandDualGraphicsSsidTablePtr->Item[j].DeviceId == DeviceId) &&
                      (RebrandDualGraphicsSsidTablePtr->Item[j].IsDgpu == 1)) {
                    CpmTableProtocolPtr->CommonFunction.PciWrite32 (  CpmTableProtocolPtr,
                                                                      Bus,
                                                                      Dev,
                                                                      Func,
                                                                      0x4C,
                                                                      NewSsid );
                    break;
                  }
                }
              }
            } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[Index].IsDgpu)
          } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)
        } // End of if (Ssid != 0xFFFF0000)
      case 1:
        Ssid = 0xFFFF0000;
        for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
          if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
            break;
          }
          if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].IsDgpu) {
            Bus   = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
            Dev   = DevicePathTablePtr->Path[Index].Device.Device;
            Func  = DevicePathTablePtr->Path[Index].Device.Function;
            iSsid = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                    Bus,
                                                                    Dev,
                                                                    Func,
                                                                    0x2E );
            Ssid  = ((UINT32)iSsid) << 16;
          } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].IsDgpu)
        } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)
        DisplayFeatureDataPtr->Ssid2 = Ssid;
        if (Ssid != 0xFFFF0000) {
          iSsid = (UINT16) (Ssid >> 16);
          for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
            if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
              break;
            }
            if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[Index].IsDgpu) {
              Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
              Dev       = DevicePathTablePtr->Path[Index].Device.Device;
              Func      = DevicePathTablePtr->Path[Index].Device.Function;
              DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                          Bus,
                                                                          Dev,
                                                                          Func,
                                                                          0x02 );
              VendorId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                                                          Bus,
                                                                          Dev,
                                                                          Func,
                                                                          0x2C );
              RevId     = CpmTableProtocolPtr->CommonFunction.PciRead8 (  CpmTableProtocolPtr,
                                                                          Bus,
                                                                          Dev,
                                                                          Func,
                                                                          0x08 );
              if (RebrandDualGraphicsSsidTable2Ptr->Svid == 0 || RebrandDualGraphicsSsidTable2Ptr->Svid == 0xFFFF) {
                NewSsid   = Ssid | (UINT32)VendorId2;
              } else {
                NewSsid   = Ssid | (UINT32)RebrandDualGraphicsSsidTable2Ptr->Svid;
              }

              for (j = 0; j < AMD_REBRAND_DUAL_GRAPHICS_SSID_DEVICE_SIZE; j++) {
                if (RebrandDualGraphicsSsidTable2Ptr->Item[j].dDeviceId == 0xFFFF) {
                  break;
                } else {
                  if ((RebrandDualGraphicsSsidTable2Ptr->Item[j].dRevId == RevId) &&
                      (RebrandDualGraphicsSsidTable2Ptr->Item[j].iSsid == iSsid) &&
                      (RebrandDualGraphicsSsidTable2Ptr->Item[j].dDeviceId == DeviceId)) {
                    CpmTableProtocolPtr->CommonFunction.PciWrite32 (  CpmTableProtocolPtr,
                                                                      Bus,
                                                                      Dev,
                                                                      Func,
                                                                      0x4C,
                                                                      NewSsid );
                    break;
                  }
                }
              } // End of for (j = 0; j < AMD_REBRAND_DUAL_GRAPHICS_SSID_DEVICE_SIZE; j++)
            } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[Index].IsDgpu)
          } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)
        } // End of if (Ssid != 0xFFFF0000)
      } // End of switch (RebrandDualGraphicsSsidTablePtr->Header.FormatRevision)
    } // End of if (RebrandDualGraphics && RebrandDualGraphicsSsidTablePtr)

    // Patch PX ASL SSDT Table
    if (!(DisplayFeatureTablePtr->FunctionDisableMask & BIT1)) {
      for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
        if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid && DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist) {
          ZeroMem (Buffer, sizeof (Buffer));
          if (DevicePathTablePtr->Path[i].IsDgpu) {
            if (DevicePathTablePtr->Path[i].FeatureMask.Mask.MultiBridge == 0) {
              Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[i].Bridge.Device,
                                                                                DevicePathTablePtr->Path[i].Bridge.Function );
              if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.NonAmdGpu) {
                CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                    &DISPLAY_FEATURE_D_ACPI_DEVICE_GUID,
                                                                    NULL,
                                                                    AmdCpmDGpuSsdtCallBack,
                                                                    &Buffer[0] );
              }
            } else {
              Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[i].Bridge.Device,
                                                                                DevicePathTablePtr->Path[i].Bridge.Function );
              if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.NonAmdGpu) {
                CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                    &DISPLAY_FEATURE_D2_ACPI_DEVICE_GUID,
                                                                    NULL,
                                                                    AmdCpmDGpuSsdtCallBack,
                                                                    &Buffer[0] );
              }
            }
            if (DevicePathTablePtr->Path[i].FeatureMask.Mask.D3Cold && D3ColdSupport) {
              Buffer[1] = (UINT32) DevicePathTablePtr->Path[i].DeviceIdVcc;
              Buffer[2] = (UINT32) DevicePathTablePtr->Path[i].Bridge.Device;
              Buffer[3] = (UINT32) DevicePathTablePtr->Path[i].Bridge.Function;
              Buffer[4] = (UINT32) DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus;
              if (DevicePathTablePtr->Path[i].FeatureMask.Mask.NonAmdGpu) {
                Buffer[5] = 0;
                Buffer[6] = 0;
              } else {
                Buffer[5] = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                                                                            (UINT8)DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus,
                                                                            0,
                                                                            0,
                                                                            0x2C );
                Buffer[6] = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                                                                            (UINT8)DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus,
                                                                            0,
                                                                            1,
                                                                            0x2C );
              }
              Buffer[7] = 1;

              Buffer[8] = DisplayFeatureDataPtr->GfxBridgePMem[1].BridgeCommand;
              Buffer[9] = DisplayFeatureDataPtr->GfxBridgePMem[1].BusNumberReg;
              Buffer[10] = DisplayFeatureDataPtr->GfxBridgePMem[1].BridgeNonPrefetchable;
              Buffer[11] = DisplayFeatureDataPtr->GfxBridgePMem[1].LimitBaseLowReg;
              Buffer[12] = DisplayFeatureDataPtr->GfxBridgePMem[1].BaseHighReg;
              Buffer[13] = DisplayFeatureDataPtr->GfxBridgePMem[1].LimitHighReg;
              Buffer[14] = 1;

              Buffer[15] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BridgeCommand;
              Buffer[16] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BusNumberReg;
              Buffer[17] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BridgeNonPrefetchable;
              Buffer[18] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].LimitBaseLowReg;
              Buffer[19] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BaseHighReg;
              Buffer[20] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].LimitHighReg;
              Buffer[21] = 1;

              Buffer[22] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BridgeCommand;
              Buffer[23] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BusNumberReg;
              Buffer[24] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BridgeNonPrefetchable;
              Buffer[25] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].LimitBaseLowReg;
              Buffer[26] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BaseHighReg;
              Buffer[27] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].LimitHighReg;
              Buffer[28] = 1;

              Buffer[29] = DisplayFeatureDataPtr->GfxDevicePMem[1].DeviceCommand;
              Buffer[30] = DisplayFeatureDataPtr->GfxDevicePMem[1].DoorbellLowReg;
              Buffer[31] = DisplayFeatureDataPtr->GfxDevicePMem[1].DoorbellHighReg;
              Buffer[32] = DisplayFeatureDataPtr->GfxDevicePMem[1].DeviceNonPrefetchable;
              Buffer[33] = DisplayFeatureDataPtr->GfxDevicePMem[1].DeviceIdReg;
              Buffer[34] = 1;

              CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                  &DISPLAY_FEATURE_DGPU_D3_COLD_ACPI_DEVICE_GUID,
                                                                  NULL,
                                                                  AmdCpmDGpuD3ColdCallBack,
                                                                  &Buffer[0] );
            }
          } else {
            Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                              DevicePathTablePtr->Path[dGpuIndex].Bridge.Device,
                                                                              DevicePathTablePtr->Path[dGpuIndex].Bridge.Function );
            if (DisplayFeatureDataPtr->VBiosFlag && (CurrentPowerXpress || CurrentHyperCrossFire || CurrentHybridGraphics) && !IsDgpuPrimary) {
              Buffer[1] = 1;
            } else {
              Buffer[1] = 0;
            }
            Buffer[2] = 0;
            if (DevicePathTablePtr->Path[i].Bridge.Device == 0) {
              CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                  &DISPLAY_FEATURE_I_ACPI_DEVICE_GUID,
                                                                  NULL,
                                                                  AmdCpmIGpuSsdtCallBack,
                                                                  &Buffer[0] );
            } else {
              Buffer[2] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[i].Bridge.Device,
                                                                                DevicePathTablePtr->Path[i].Bridge.Function );
              CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                  &DISPLAY_FEATURE_I2_ACPI_DEVICE_GUID,
                                                                  NULL,
                                                                  AmdCpmIGpuSsdtCallBack,
                                                                  &Buffer[0] );
            }
            iGpuIndex = 0;
          }
          ZeroMem (Buffer, sizeof (Buffer));
          if ((IsDgpuPrimary) && (DevicePathTablePtr->Path[i].IsDgpu)) {
            if (DevicePathTablePtr->Path[i].FeatureMask.Mask.MultiBridge == 0) {
              if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.NonAmdGpu) {
                Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                  DevicePathTablePtr->Path[i].Bridge.Device,
                                                                                  DevicePathTablePtr->Path[i].Bridge.Function );
                CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                    &DISPLAY_FEATURE_ATPX_DGPU_ACPI_DEVICE_GUID,
                                                                    NULL,
                                                                    AmdCpmDGpuSsdtCallBack,
                                                                    &Buffer[0] );
              }
            } else {
              Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[i].Bridge.Device,
                                                                                DevicePathTablePtr->Path[i].Bridge.Function );
              CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                  &DISPLAY_FEATURE_ATPX_DGPU2_ACPI_DEVICE_GUID,
                                                                  NULL,
                                                                  AmdCpmDGpuSsdtCallBack,
                                                                  &Buffer[0] );
            }
          } else if ((!IsDgpuPrimary) && (!DevicePathTablePtr->Path[i].IsDgpu)) {
            if (DevicePathTablePtr->Path[i].Bridge.Device == 0) {
              Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[dGpuIndex].Bridge.Device,
                                                                                DevicePathTablePtr->Path[dGpuIndex].Bridge.Function );
              Buffer[1] = 0;
              Buffer[2] = 0;
              CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                  &DISPLAY_FEATURE_ATPX_IGPU_ACPI_DEVICE_GUID,
                                                                  NULL,
                                                                  AmdCpmIGpuSsdtCallBack,
                                                                  &Buffer[0] );
            } else {
              Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[dGpuIndex].Bridge.Device,
                                                                                DevicePathTablePtr->Path[dGpuIndex].Bridge.Function );
              Buffer[1] = 0;
              Buffer[2] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                                DevicePathTablePtr->Path[i].Bridge.Device,
                                                                                DevicePathTablePtr->Path[i].Bridge.Function );
              CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                                  &DISPLAY_FEATURE_ATPX_IGPU2_ACPI_DEVICE_GUID,
                                                                  NULL,
                                                                  AmdCpmIGpuSsdtCallBack,
                                                                  &Buffer[0] );
            }
          }
        } else {
          if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid == 0) {
            break;
          }
        }
      } // End of for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++)

      if (iGpuIndex == 0xFF && dGpuIndex != 0xFF) {
        if (!DevicePathTablePtr->Path[dGpuIndex].FeatureMask.Mask.NonAmdGpu) {
          ZeroMem (Buffer, sizeof (Buffer));
          Buffer[0] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                            DevicePathTablePtr->Path[dGpuIndex].Bridge.Device,
                                                                            DevicePathTablePtr->Path[dGpuIndex].Bridge.Function );
          Buffer[1] = 0;
          Buffer[2] = 0;
          CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                              &DISPLAY_FEATURE_NoI_ACPI_DEVICE_GUID,
                                                              NULL,
                                                              AmdCpmIGpuSsdtCallBack,
                                                              &Buffer[0] );
        }
      } // End of if (iGpuIndex == 0xFF && dGpuIndex != 0xFF)

      if (DisplayFeatureTablePtr->MxmOverTempEvent != 0xFF) {
        if (!DevicePathTablePtr->Path[dGpuIndex].FeatureMask.Mask.NonAmdGpu) {
          ZeroMem (Buffer, sizeof (Buffer));
          SciMap = CpmTableProtocolPtr->CommonFunction.GetSciMap (  CpmTableProtocolPtr,
                                                                    DisplayFeatureTablePtr->MxmOverTempEvent );
          if ((SciMap & 0xF) < 0xA) {
            Buffer[0] = 0x3000 + (((SciMap) & 0xF) << 8);
          } else {
            Buffer[0] = 0x4000 + ((((SciMap) & 0xF) - 0x9) << 8);
          }
          if (((SciMap >> 4) & 0xF) < 0xA) {
            Buffer[0] |= 0x30 + ((SciMap >> 4) & 0xF);
          } else {
            Buffer[0] |= 0x40 + (((SciMap >> 4) & 0xF) - 0x9);
          }
          Buffer[0] = (Buffer[0] << 16) + (((UINT32)'L') << 8) + (UINT32)'_';
          CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                              &DISPLAY_FEATURE_MXM_OVERT_ACPI_DEVICE_GUID,
                                                              NULL,
                                                              AmdCpmMxmOverTSsdtCallBack,
                                                              &Buffer[0] );
        }
      } // End of if (DisplayFeatureTablePtr->MxmOverTempEvent != 0xFF)

      if (DisplayFeatureTablePtr->DisplayConnectEvent != 0xFF && (CurrentPowerXpress || CurrentHybridGraphics)) {
        if (!DevicePathTablePtr->Path[dGpuIndex].FeatureMask.Mask.NonAmdGpu) {
          ZeroMem (Buffer, sizeof (Buffer));
          SciMap = CpmTableProtocolPtr->CommonFunction.GetSciMap (  CpmTableProtocolPtr,
                                                                    DisplayFeatureTablePtr->DisplayConnectEvent );
          if ((SciMap & 0xF) < 0xA) {
            Buffer[0] = 0x3000 + (((SciMap) & 0xF) << 8);
          } else {
            Buffer[0] = 0x4000 + ((((SciMap) & 0xF) - 0x9) << 8);
          }
          if (((SciMap >> 4) & 0xF) < 0xA) {
            Buffer[0] |= 0x30 + ((SciMap >> 4) & 0xF);
          } else {
            Buffer[0] |= 0x40 + (((SciMap >> 4) & 0xF) - 0x9);
          }
          Buffer[0] = (Buffer[0] << 16) + (((UINT32)'L') << 8) + (UINT32)'_';
          Buffer[1] = CpmTableProtocolPtr->CommonFunction.GetPcieAslName (  CpmTableProtocolPtr,
                                                                            DevicePathTablePtr->Path[dGpuIndex].Bridge.Device,
                                                                            DevicePathTablePtr->Path[dGpuIndex].Bridge.Function );
          CpmTableProtocolPtr->CommonFunction.AddSsdtTable (  (VOID*)CpmTableProtocolPtr,
                                                              &DISPLAY_FEATURE_DISPLAY_CONNECT_EVENT_ACPI_DEVICE_GUID,
                                                              NULL,
                                                              AmdCpmDisplayConnectEventSsdtCallBack,
                                                              &Buffer[0] );
        }
      } // End of if (DisplayFeatureTablePtr->DisplayConnectEvent != 0xFF && (CurrentPowerXpress || CurrentHybridGraphics))
    } // End of if (!(DisplayFeatureTablePtr->FunctionDisableMask & BIT1))
  } // End of if (DisplayFeatureTablePtr)

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDxeInitLateEnd);

  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Display Feature SSDT table for iGPU
 *
 * This function is used to update the name of PCIe bridge for dGPU in ASL
 * and renames XTRM to ATRM if PowerXpress is enabled.
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
AmdCpmIGpuSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  )
{
  UINT32    *BufferPtr;

  BufferPtr = (UINT32*)Context;

  switch ( *((UINT32*)AmlObjPtr)) {
  case CPM_SIGNATURE_32 ('X', 'T', 'R', 'M'):     // ASL code: Method(XTRM,2,Serialized)
    if (*(BufferPtr + 1)) {
      *((UINT32*)AmlObjPtr) = CPM_SIGNATURE_32 ('A', 'T', 'R', 'M');
    }
    break;
  case CPM_SIGNATURE_32 ('P', 'B', '2', '_'):     // ASL code: \_SB.PCI0.PB2
    if (*BufferPtr) {
      *((UINT32*)AmlObjPtr) = *BufferPtr;
    }
    break;
  case CPM_SIGNATURE_32 ('P', 'B', 'C', '_'):     // ASL code: \_SB.PCI0.PBC
    if (*(BufferPtr + 2)) {
      *((UINT32*)AmlObjPtr) = *(BufferPtr + 2);
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Display Feature SSDT table for dGPU
 *
 * This function is used to update the name of PCIe bridge for dGPU in ASL
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
AmdCpmDGpuSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  )
{
  UINT32    *BufferPtr;
  BufferPtr = (UINT32*)Context;
  switch ( *((UINT32*)AmlObjPtr)) {
  case CPM_SIGNATURE_32 ('P', 'B', '2', '_'):     // ASL code: \_SB.PCI0.PB2
    if (*BufferPtr) {
      *((UINT32*)AmlObjPtr) = *BufferPtr;
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Display Feature SSDT table for MXM_OVERT
 *
 * This function is used to update the name of GPE method in ASL
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
AmdCpmMxmOverTSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  )
{
  UINT32    *BufferPtr;
  BufferPtr = (UINT32*)Context;
  switch ( *((UINT32*)AmlObjPtr)) {
  case CPM_SIGNATURE_32 ('M', '2', '1', '7'):     // ASL code: CpmMxmOverTempEventMethod: M217
    if (*BufferPtr) {
      *((UINT32*)AmlObjPtr) = *BufferPtr;
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Display Feature SSDT table for Discrete GPU
 * connect/disconnect event
 *
 * This function is used to update the name of GPE method in ASL
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
AmdCpmDisplayConnectEventSsdtCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  )
{
  UINT32    *BufferPtr;
  BufferPtr = (UINT32*)Context;
  switch ( *((UINT32*)AmlObjPtr)) {
  case CPM_SIGNATURE_32 ('M', '2', '1', '8'):     // ASL code: CpmDisplayConnectEventMethod: M218
    if (*BufferPtr) {
      *((UINT32*)AmlObjPtr) = *BufferPtr;
    }
    break;
  case CPM_SIGNATURE_32 ('P', 'B', '2', '_'):     // ASL code: \_SB.PCI0.PB2
    if (*(BufferPtr + 1)) {
      *((UINT32*)AmlObjPtr) = *(BufferPtr + 1);
    }
    break;
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback function to update Display Feature SSDT table for dGPU D3Cold
 *
 * This function is used to update the name of PCIe bridge for dGPU in ASL
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
AmdCpmDGpuD3ColdCallBack (
  IN        VOID                    *This,
  IN        VOID                    *AmlObjPtr,
  IN        VOID                    *Context
  )
{
  UINT32    *BufferPtr;
  UINT8     *DataPtr;
  BufferPtr = (UINT32*)Context;
  DataPtr = (UINT8*)AmlObjPtr;
  switch ( *((UINT32*)AmlObjPtr)) {
  case CPM_SIGNATURE_32 ('P', 'B', '2', '_'):     // ASL code: \_SB.PCI0.PB2
    if (*BufferPtr) {
      *((UINT32*)AmlObjPtr) = *BufferPtr;
    }
    break;
  case CPM_SIGNATURE_32 ('M', '2', '3', '6'):     // ASL code: CpmDgpuPowerResourceBuffer: M236
    if (*(BufferPtr + 1)) {
      if (*(BufferPtr + 7)) {
// In DGpuD3Cold.asl
//            CreateByteField(CpmDgpuPowerResourceBuffer, 0, CpmDgpuPowerResourceDeviceId)
//            CreateByteField(CpmDgpuPowerResourceBuffer, 1, CpmBridgeDevice)
//            CreateByteField(CpmDgpuPowerResourceBuffer, 2, CpmBridgeFunction)
//            CreateByteField(CpmDgpuPowerResourceBuffer, 3, CpmDgpuBus)
//            CreateDwordField(CpmDgpuPowerResourceBuffer, 4, CpmDgpuSsidVid0)
//            CreateDwordField(CpmDgpuPowerResourceBuffer, 8, CpmDgpuSsidVid1)
// In AmdCpmDisplayFeatureInitLate.c
//                Buffer[1] = (UINT32) DevicePathTablePtr->Path[i].DeviceIdVcc;
//                Buffer[2] = (UINT32) DevicePathTablePtr->Path[i].Bridge.Device;
//                Buffer[3] = (UINT32) DevicePathTablePtr->Path[i].Bridge.Function;
//                Buffer[4] = (UINT32) DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus;
//                Buffer[5] = CpmTableProtocolPtr->CommonFunction.PciRead32 (CpmTableProtocolPtr, (UINT8)DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus, 0, 0, 0x2C);
//                Buffer[6] = CpmTableProtocolPtr->CommonFunction.PciRead32 (CpmTableProtocolPtr, (UINT8)DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus, 0, 1, 0x2C);
//                Buffer[7] = 1;
        *((UINT8*)AmlObjPtr + 8) = *(UINT8*)(BufferPtr + 1);
        *((UINT8*)AmlObjPtr + 9) = *(UINT8*)(BufferPtr + 2);
        *((UINT8*)AmlObjPtr + 10) = *(UINT8*)(BufferPtr + 3);
        *((UINT8*)AmlObjPtr + 11) = *(UINT8*)(BufferPtr + 4);
        *((UINT32*)AmlObjPtr + 3) = *(BufferPtr + 5);
        *((UINT32*)AmlObjPtr + 4) = *(BufferPtr + 6);
        *(BufferPtr + 7) = 0;
      }
    }
    break;
  case CPM_SIGNATURE_32 ('M', '3', '5', '0'):     // ASL code: CpmdGpuBridgePMemPostBuffer: M350
    if (*(BufferPtr + 1)) {
      if (*(BufferPtr + 14)) {
// In DGpuD3Cold.asl
//            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 0,  CpmBridgePMemPostCommand)
//            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 4,  CpmBridgePMemPostBusNumberReg)
//            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 8,  CpmBridgePMemPostNonPrefetchable)
//            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 12, CpmBridgePMemPostLimitBaseLowReg)
//            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 16, CpmBridgePMemPostBaseHighReg)
//            CreateDwordField (CpmdGpuBridgePMemPostBuffer, 20, CpmBridgePMemPostLimitHighReg)
// In AmdCpmDisplayFeatureInitLate.c
//              Buffer[8] = DisplayFeatureDataPtr->GfxBridgePMem[1].BridgeCommand;
//              Buffer[9] = DisplayFeatureDataPtr->GfxBridgePMem[1].BusNumberReg;
//              Buffer[10] = DisplayFeatureDataPtr->GfxBridgePMem[1].BridgeNonPrefetchable;
//              Buffer[11] = DisplayFeatureDataPtr->GfxBridgePMem[1].LimitBaseLowReg;
//              Buffer[12] = DisplayFeatureDataPtr->GfxBridgePMem[1].BaseHighReg;
//              Buffer[13] = DisplayFeatureDataPtr->GfxBridgePMem[1].LimitHighReg;
//              Buffer[14] = 1;
        *((UINT32*)AmlObjPtr + 2) = *(BufferPtr + 8);
        *((UINT32*)AmlObjPtr + 3) = *(BufferPtr + 9);
        *((UINT32*)AmlObjPtr + 4) = *(BufferPtr + 10);
        *((UINT32*)AmlObjPtr + 5) = *(BufferPtr + 11);
        *((UINT32*)AmlObjPtr + 6) = *(BufferPtr + 12);
        *((UINT32*)AmlObjPtr + 7) = *(BufferPtr + 13);
        *(BufferPtr + 14) = 0;
      }
    }
    break;
  case CPM_SIGNATURE_32 ('M', '3', '5', '1'):     // ASL code: CpmdGpuBridgeUpStPostBuffer: M351
    if (*(BufferPtr + 1)) {
      if (*(BufferPtr + 21)) {
// In DGpuD3Cold.asl
//            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 0,  CpmBridgeUpStPostCommand)
//            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 4,  CpmBridgeUpStPostBusNumberReg)
//            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 8,  CpmBridgeUpStPostNonPrefetchable)
//            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 12, CpmBridgeUpStPostLimitBaseLowReg)
//            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 16, CpmBridgeUpStPostBaseHighReg)
//            CreateDwordField (CpmdGpuBridgeUpStPostBuffer, 20, CpmBridgeUpStPostLimitHighReg)
// In AmdCpmDisplayFeatureInitLate.c
//              Buffer[15] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BridgeCommand;
//              Buffer[16] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BusNumberReg;
//              Buffer[17] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BridgeNonPrefetchable;
//              Buffer[18] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].LimitBaseLowReg;
//              Buffer[19] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].BaseHighReg;
//              Buffer[20] = DisplayFeatureDataPtr->GfxBridgeUpSt[1].LimitHighReg;
//              Buffer[21] = 1;
        *((UINT32*)AmlObjPtr + 2) = *(BufferPtr + 15);
        *((UINT32*)AmlObjPtr + 3) = *(BufferPtr + 16);
        *((UINT32*)AmlObjPtr + 4) = *(BufferPtr + 17);
        *((UINT32*)AmlObjPtr + 5) = *(BufferPtr + 18);
        *((UINT32*)AmlObjPtr + 6) = *(BufferPtr + 19);
        *((UINT32*)AmlObjPtr + 7) = *(BufferPtr + 20);
        *(BufferPtr + 21) = 0;
      }
    }
    break;
  case CPM_SIGNATURE_32 ('M', '3', '5', '2'):     // ASL code: CpmdGpuBridgeDnStPostBuffer: M352
    if (*(BufferPtr + 1)) {
      if (*(BufferPtr + 28)) {
// In DGpuD3Cold.asl
//            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 0,  CpmBridgeDnStPostCommand)
//            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 4,  CpmBridgeDnStPostBusNumberReg)
//            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 8,  CpmBridgeDnStPostNonPrefetchable)
//            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 12, CpmBridgeDnStPostLimitBaseLowReg)
//            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 16, CpmBridgeDnStPostBaseHighReg)
//            CreateDwordField (CpmdGpuBridgeDnStPostBuffer, 20, CpmBridgeDnStPostLimitHighReg)
// In AmdCpmDisplayFeatureInitLate.c
//              Buffer[22] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BridgeCommand;
//              Buffer[23] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BusNumberReg;
//              Buffer[24] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BridgeNonPrefetchable;
//              Buffer[25] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].LimitBaseLowReg;
//              Buffer[26] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].BaseHighReg;
//              Buffer[27] = DisplayFeatureDataPtr->GfxBridgeDnSt[1].LimitHighReg;
//              Buffer[28] = 1;
        *((UINT32*)AmlObjPtr + 2) = *(BufferPtr + 22);
        *((UINT32*)AmlObjPtr + 3) = *(BufferPtr + 23);
        *((UINT32*)AmlObjPtr + 4) = *(BufferPtr + 24);
        *((UINT32*)AmlObjPtr + 5) = *(BufferPtr + 25);
        *((UINT32*)AmlObjPtr + 6) = *(BufferPtr + 26);
        *((UINT32*)AmlObjPtr + 7) = *(BufferPtr + 27);
        *(BufferPtr + 28) = 0;
      }
    }
    break;
  case CPM_SIGNATURE_32 ('M', '3', '5', '3'):     // ASL code: CpmdGpuDevicePMemPostBuffer: M353
    if (*(BufferPtr + 1)) {
      if (*(BufferPtr + 34)) {
// In DGpuD3Cold.asl
//            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 0,  CpmDevicePMemPostCommand)
//            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 4,  CpmDevicePMemPostDoorbellLowReg)
//            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 8,  CpmDevicePMemPostDoorbellHighReg)
//            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 12, CpmDevicePMemPostNonPrefetchable)
//            CreateDwordField (CpmdGpuDevicePMemPostBuffer, 16, CpmDevicePMemPostDeviceId)
// In AmdCpmDisplayFeatureInitLate.c
//              Buffer[29] = DisplayFeatureDataPtr->GfxDevicePMem[1].DeviceCommand;
//              Buffer[30] = DisplayFeatureDataPtr->GfxDevicePMem[1].DoorbellLowReg;
//              Buffer[31] = DisplayFeatureDataPtr->GfxDevicePMem[1].DoorbellHighReg;
//              Buffer[32] = DisplayFeatureDataPtr->GfxDevicePMem[1].DeviceNonPrefetchable;
//              Buffer[33] = DisplayFeatureDataPtr->GfxDevicePMem[1].DeviceIdReg;
//              Buffer[34] = 1;
        *((UINT32*)AmlObjPtr + 2) = *(BufferPtr + 29);
        *((UINT32*)AmlObjPtr + 3) = *(BufferPtr + 30);
        *((UINT32*)AmlObjPtr + 4) = *(BufferPtr + 31);
        *((UINT32*)AmlObjPtr + 5) = *(BufferPtr + 32);
        *((UINT32*)AmlObjPtr + 6) = *(BufferPtr + 33);
        *(BufferPtr + 34) = 0;
      }
    }
    break;
  case CPM_SIGNATURE_32 ('X', 'P', 'R', '0'):     // ASL code: Name(XPR0, Package() {CpmDgpuPowerResourceVcc}) // Power resources required for D0
    if (*(BufferPtr + 1)) {
      *((UINT32*)AmlObjPtr) = CPM_SIGNATURE_32 ('_', 'P', 'R', '0');
    }
    break;
  case CPM_SIGNATURE_32 ('X', 'P', 'R', '2'):     // ASL code: Name(XPR2, Package() {CpmDgpuPowerResourceVcc}) // Power resources required for D2
    if (*(BufferPtr + 1)) {
      *((UINT32*)AmlObjPtr) = CPM_SIGNATURE_32 ('_', 'P', 'R', '2');
    }
    break;
  case CPM_SIGNATURE_32 ('X', 'P', 'R', '3'):     // ASL code: Name(XPR3, Package() {CpmDgpuPowerResourceVcc}) // Power resources required for D3
    if (*(BufferPtr + 1)) {
      *((UINT32*)AmlObjPtr) = CPM_SIGNATURE_32 ('_', 'P', 'R', '3');
    }
    break;
  case CPM_SIGNATURE_32 ('X', 'S', '0', 'W'):     // ASL code: Name(XS0W, 4)
    if (*(BufferPtr + 1)) {
      *((UINT32*)AmlObjPtr) = CPM_SIGNATURE_32 ('_', 'S', '0', 'W');
    }
    break;
  }
  return FALSE;
}

