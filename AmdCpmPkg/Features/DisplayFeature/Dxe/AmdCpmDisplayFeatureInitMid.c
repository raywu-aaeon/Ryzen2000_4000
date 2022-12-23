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


VOID
AmdCpmSaveGfxResourceInitMid (
  IN        AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr,
  IN        UINT8                           MultiBridge,
  IN        UINT8                           bus,
  IN        AMD_CPM_DEVICE_PATH_ITEM        *GpuDevice,
     OUT    AMD_CPM_PCI_PFA                 *GfxBridgePfa,
     OUT    AMD_CPM_PCI_PFA                 *GfxDevicePfa,
     OUT    AMD_CPM_PCI_BPMEM               *RootBridgeData,
     OUT    AMD_CPM_PCI_BPMEM               *UpStBridgeData,
     OUT    AMD_CPM_PCI_BPMEM               *DnStBridgeData,
     OUT    AMD_CPM_PCI_DPMEM               *DevicePciData
  )
{
  GfxBridgePfa->Pfa.Bus = 0;
  GfxBridgePfa->Pfa.Device = GpuDevice->Bridge.Device;
  GfxBridgePfa->Pfa.Function = GpuDevice->Bridge.Function;
  GfxDevicePfa->Pfa.Bus = bus;
  GfxDevicePfa->Pfa.Device = GpuDevice->Device.Device;
  GfxDevicePfa->Pfa.Function = GpuDevice->Device.Function;

  RootBridgeData->BridgeCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxBridgePfa->Pfa.Bus,
                    GfxBridgePfa->Pfa.Device,
                    GfxBridgePfa->Pfa.Function,
                    0x04 );

  RootBridgeData->BusNumberReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxBridgePfa->Pfa.Bus,
                    GfxBridgePfa->Pfa.Device,
                    GfxBridgePfa->Pfa.Function,
                    0x18 );

  RootBridgeData->BridgeNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxBridgePfa->Pfa.Bus,
                    GfxBridgePfa->Pfa.Device,
                    GfxBridgePfa->Pfa.Function,
                    0x20 );

  RootBridgeData->LimitBaseLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxBridgePfa->Pfa.Bus,
                    GfxBridgePfa->Pfa.Device,
                    GfxBridgePfa->Pfa.Function,
                    0x24 );

  RootBridgeData->BaseHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxBridgePfa->Pfa.Bus,
                    GfxBridgePfa->Pfa.Device,
                    GfxBridgePfa->Pfa.Function,
                    0x28 );

  RootBridgeData->LimitHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxBridgePfa->Pfa.Bus,
                    GfxBridgePfa->Pfa.Device,
                    GfxBridgePfa->Pfa.Function,
                    0x2C );

  if ((MultiBridge & 1) == 1) {
    UpStBridgeData->BridgeCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((RootBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04 );

    UpStBridgeData->BusNumberReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((RootBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18 );

    UpStBridgeData->BridgeNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((RootBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20 );

    UpStBridgeData->LimitBaseLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((RootBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24 );

    UpStBridgeData->BaseHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((RootBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28 );

    UpStBridgeData->LimitHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((RootBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C );
  }

  if ((MultiBridge & 2) == 2) {
    DnStBridgeData->BridgeCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((UpStBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04 );

    DnStBridgeData->BusNumberReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((UpStBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18 );

    DnStBridgeData->BridgeNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((UpStBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20 );

    DnStBridgeData->LimitBaseLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((UpStBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24 );

    DnStBridgeData->BaseHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((UpStBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28 );

    DnStBridgeData->LimitHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((UpStBridgeData->BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C );
  }

  DevicePciData->DeviceIdReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxDevicePfa->Pfa.Bus,
                    GfxDevicePfa->Pfa.Device,
                    GfxDevicePfa->Pfa.Function,
                    0x00 );

  DevicePciData->DeviceCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxDevicePfa->Pfa.Bus,
                    GfxDevicePfa->Pfa.Device,
                    GfxDevicePfa->Pfa.Function,
                    0x04 );

  DevicePciData->DoorbellLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxDevicePfa->Pfa.Bus,
                    GfxDevicePfa->Pfa.Device,
                    GfxDevicePfa->Pfa.Function,
                    0x18 );

  DevicePciData->DoorbellHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxDevicePfa->Pfa.Bus,
                    GfxDevicePfa->Pfa.Device,
                    GfxDevicePfa->Pfa.Function,
                    0x1C );

  DevicePciData->DeviceNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    GfxDevicePfa->Pfa.Bus,
                    GfxDevicePfa->Pfa.Device,
                    GfxDevicePfa->Pfa.Function,
                    0x24 );
}

VOID
AmdCpmSetApcAndiGFX (
  IN        AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr
  )
{
  AMD_CPM_COMMON_FUNCTION         *CommonFunctionPtr;
  CPM_DISPLAY_FEATURE_PRIVATE     *DisplayFeatureDataPtr;

  CommonFunctionPtr       = &CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction;
  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;

  if (DisplayFeatureDataPtr->GfxBridgePfa[0].Raw) {
    //APC: Set ISA_EN and VGA_EN bit in the APC bridge
    CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.PciOr8 (
                CpmDisplayFeatureProtocolPtr->TableProtocolPtr,
                DisplayFeatureDataPtr->GfxBridgePfa[0].Pfa.Bus,
                DisplayFeatureDataPtr->GfxBridgePfa[0].Pfa.Device,
                DisplayFeatureDataPtr->GfxBridgePfa[0].Pfa.Function,
                0x3E,
                BIT2 + BIT3
                );

    //APC: Enable Bus Master, memory and IO decoding
    CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.PciOr8 (
                CpmDisplayFeatureProtocolPtr->TableProtocolPtr,
                DisplayFeatureDataPtr->GfxBridgePfa[0].Pfa.Bus,
                DisplayFeatureDataPtr->GfxBridgePfa[0].Pfa.Device,
                DisplayFeatureDataPtr->GfxBridgePfa[0].Pfa.Function,
                PCI_COMMAND_OFFSET,
                BIT0 + BIT1 + BIT2
                );
  }

  if (DisplayFeatureDataPtr->GfxDevicePfa[0].Raw) {
    //Internal GFX: Enable memory and IO decoding
    CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.PciOr8 (
                CpmDisplayFeatureProtocolPtr->TableProtocolPtr,
                DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Bus,
                DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Device,
                DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Function,
                PCI_COMMAND_OFFSET,
                BIT0 + BIT1
                );
  }
  return;
}

VOID
AmdCpmDgpuSpecialPostForHcfiGpu (
  IN        AMD_CPM_DISPLAY_FEATURE_PROTOCOL  *CpmDisplayFeatureProtocolPtr,
  IN        VOID                              *VBiosImage,
  IN        UINTN                             VBiosImageSize
  )
{
#ifndef AMD_CPM_EDKII
  EFI_STATUS                                  Status;
  EFI_LEGACY_BIOS_PROTOCOL                    *LegacyBios;
  EFI_IA32_REGISTER_SET                       Regs;
  UINT32                                      TempDBuf;
  UINT8                                       *DSegBuffer;
  UINT16                                      Patch;
  CPM_DISPLAY_FEATURE_PRIVATE                 *DisplayFeatureDataPtr;
  UINT8                                       *SaveBufferPtr;
  EFI_LEGACY_REGION_PROTOCOL                  *LegacyRegion;

  DisplayFeatureDataPtr = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;

  //Step 00. Allocate memory to save original data
  Status = gBS->AllocatePool (
                  EfiRuntimeServicesData,
                  0x10000,
                  (VOID**)&SaveBufferPtr
                  );
  if (!EFI_ERROR (Status)) {

    //Locate legacy region protocol
    Status = gBS->LocateProtocol (&gEfiLegacyRegionProtocolGuid, NULL, (VOID**)&LegacyRegion);
    if (!EFI_ERROR (Status)) {

      //Step 01. dGPUVBiosSpecialPost
      Status          = gBS->LocateProtocol (&gEfiLegacyBiosProtocolGuid, NULL, (VOID**)&LegacyBios);
      if (!EFI_ERROR (Status)) {

        LegacyRegion->UnLock (LegacyRegion, 0xD0000, 0x10000, NULL);

        TempDBuf        = 0x000D0000;
        DSegBuffer      = (UINT8 *) (UINTN)TempDBuf;

        CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.CopyMem (SaveBufferPtr, DSegBuffer, 0x10000);
        CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.CopyMem (DSegBuffer, VBiosImage, VBiosImageSize);

        Patch           = *((UINT16 *) (UINTN) (TempDBuf + 0x40));
        EfiZeroMem (&Regs, sizeof (EFI_IA32_REGISTER_SET));

        Regs.X.AX       = DisplayFeatureDataPtr->GfxDevicePfa[0].Raw;
        Status          = LegacyBios->FarCall86 (
                                        LegacyBios,
                                        0xD000,
                                        Patch,
                                        &Regs,
                                        NULL,
                                        0
                                        );
        ASSERT_EFI_ERROR (Status);

        //Step 02. CopyVBiosFromD000
        CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.CopyMem (VBiosImage, DSegBuffer, VBiosImageSize);
        CpmDisplayFeatureProtocolPtr->TableProtocolPtr->CommonFunction.CopyMem (DSegBuffer, SaveBufferPtr, 0x10000);

         // lock the D000:0000 after we restore it
        LegacyRegion->Lock (LegacyRegion, 0xD0000, 0x10000, NULL);
      }
    }
  }
  Status = gBS->FreePool (SaveBufferPtr);
#endif

  return;
}

VOID
AmdCpmDisableDgpuAudioInPX (
  IN        AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr
  )
{
  CPM_DISPLAY_FEATURE_PRIVATE *DisplayFeatureDataPtr;
  AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr;
  UINT64                      Mmiobase;
  UINT32                      RomStrapOffset;
  UINT8                       DgpuCase;
  UINT32                      DeviceIdReg;
  UINT8                       DeviceCommand;

  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
  CpmTableProtocolPtr     = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;

  if (DisplayFeatureDataPtr->GfxDevicePfa[1].Raw) {
    DeviceIdReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                      DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                      DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                      0x00 );

    if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x67C0) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x67DF)) {
      DgpuCase = 0x10;      // Ellesmere
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x67E0) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x67FF)) {
      DgpuCase = 0x11;      // Baffin
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x6900) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x695F)) {
      DgpuCase = 0x12;      // Iceland(Weston), Tonga, Polaris22
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x6980) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x699F)) {
      DgpuCase = 0x13;      // Lexa
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x6860) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x687F)) {
      DgpuCase = 0x20;      // Greenland
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x69A0) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x69BF)) {
      DgpuCase = 0x21;      // Vega12
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x7310) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x731F)) {
      DgpuCase = 0x22;      // Navi10
    } else if (((DeviceIdReg >> 16) & 0xFFFF) == 0x7330) {
      DgpuCase = 0x22;      // Navi10
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x7340) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x734F)) {
      DgpuCase = 0x23;      // Navi14
    } else {
      DgpuCase = 0x0;       // Old GPU
    }

    if (DgpuCase >= 0x10) {
      // BAR5
      Mmiobase = (UINT64) CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x24 );
    } else {
      // BAR2
      Mmiobase = (UINT64) CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x1C );

      Mmiobase <<= 32;

      Mmiobase |= (UINT64) CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x18 );
    }

    if ((Mmiobase != 0xFFFFFFFFFFFFFFFF) && (Mmiobase != 0)) {
      DeviceCommand = CpmTableProtocolPtr->CommonFunction.PciRead8 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x04 );

      CpmTableProtocolPtr->CommonFunction.PciWrite8 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x04,
                        0x07 );

      if (DgpuCase >= 0x20) {
        // Bit28 for STRAP_FUNC_EN_DEV0_F1
        RomStrapOffset = 0x34E0;
        CpmTableProtocolPtr->CommonFunction.MmioAnd32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xEFFFFFFF );
      } else if (DgpuCase >= 0x10) {
        // Bit1 for STRAP_BIF_AUDIO_EN
        RomStrapOffset = 0x5418;
        CpmTableProtocolPtr->CommonFunction.MmioAnd32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xFFFFFFFD );
      } else {
        // Bit12 for STRAP_BIF_AUDIO_EN
        RomStrapOffset = 0x540C;
        CpmTableProtocolPtr->CommonFunction.MmioAnd32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xFFFFEFFF );
      }

      CpmTableProtocolPtr->CommonFunction.PciWrite8 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x04,
                        DeviceCommand );
    }
  }
  return;
}

VOID
AmdCpmEnableDgpuSmbusInPX (
  IN        AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr
  )
{
  CPM_DISPLAY_FEATURE_PRIVATE *DisplayFeatureDataPtr;
  AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr;
  UINT64                      Mmiobase;
  UINT32                      RomStrapOffset;
  UINT8                       DgpuCase;
  UINT32                      DeviceIdReg;
  UINT8                       DeviceCommand;

  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
  CpmTableProtocolPtr     = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;

  if (DisplayFeatureDataPtr->GfxDevicePfa[1].Raw) {
    DeviceIdReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                      DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                      DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                      0x00 );

    if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x67C0) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x67DF)) {
      DgpuCase = 0x10;      // Ellesmere
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x67E0) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x67FF)) {
      DgpuCase = 0x11;      // Baffin
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x6900) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x695F)) {
      DgpuCase = 0x12;      // Iceland(Weston), Tonga, Polaris22
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x6980) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x699F)) {
      DgpuCase = 0x13;      // Lexa
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x6860) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x687F)) {
      DgpuCase = 0x20;      // Greenland
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x69A0) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x69BF)) {
      DgpuCase = 0x21;      // Vega12
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x7310) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x731F)) {
      DgpuCase = 0x22;      // Navi10
    } else if (((DeviceIdReg >> 16) & 0xFFFF) == 0x7330) {
      DgpuCase = 0x22;      // Navi10
    } else if ((((DeviceIdReg >> 16) & 0xFFFF) >= 0x7340) && (((DeviceIdReg >> 16) & 0xFFFF) <= 0x734F)) {
      DgpuCase = 0x23;      // Navi14
    } else {
      DgpuCase = 0x0;       // Old GPU
    }

    if (DgpuCase >= 0x10) {
      // BAR5
      Mmiobase = (UINT64) CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x24 );
    } else {
      // BAR2
      Mmiobase = (UINT64) CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x1C );

      Mmiobase <<= 32;

      Mmiobase |= (UINT64) CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x18 );
    }

    if ((Mmiobase != 0xFFFFFFFFFFFFFFFF) && (Mmiobase != 0)) {
      DeviceCommand = CpmTableProtocolPtr->CommonFunction.PciRead8 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x04 );

      CpmTableProtocolPtr->CommonFunction.PciWrite8 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x04,
                        0x07 );

      if (DgpuCase >= 0x20) {
        // Bit8 for SMBUS_ADDR
//        RomStrapOffset = 0x5A208;
//        CpmTableProtocolPtr->CommonFunction.MmioAnd32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xFFFFFEFF );
      } else if (DgpuCase >= 0x10) {
        // Bit1 for STRAP_BIF_SMBUS_DIS
        RomStrapOffset = 0x5780;
        CpmTableProtocolPtr->CommonFunction.MmioAnd32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xFFFFFFFD );
      } else {
        // Bit0 for STRAP_BIF_SMB_EN
        // Bit[7:1] for STRAP_BIF_SMB_SLV_ADR
        RomStrapOffset = 0x53F4;
        CpmTableProtocolPtr->CommonFunction.MmioAndThenOr32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xFFFFFF00, 0x00000083 );
      }

      CpmTableProtocolPtr->CommonFunction.PciWrite8 ( CpmTableProtocolPtr,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Bus,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Device,
                        DisplayFeatureDataPtr->GfxDevicePfa[1].Pfa.Function,
                        0x04,
                        DeviceCommand );
    }
  }
  return;
}

VOID
AmdCpmDisableIoDecodeOfPossiblePcieGfx (
  IN        EFI_EVENT   Event,
  IN        VOID        *Context
  )
{
  AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr;
  AMD_CPM_TABLE_PROTOCOL              *CpmTableProtocolPtr;
  CPM_DISPLAY_FEATURE_PRIVATE         *DisplayFeatureDataPtr;
  AMD_CPM_DEVICE_PATH_TABLE           *DevicePathTablePtr;
  UINT8                               Data8;
  UINT8                               i;

  CpmDisplayFeatureProtocolPtr = Context;
  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
  CpmTableProtocolPtr     = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;
  DevicePathTablePtr      = DisplayFeatureDataPtr->DevicePathTablePtr;

  Data8 = 0;
  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDisableIoDecodeBegin);

  for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
    if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
      if (DevicePathTablePtr->Path[i].IsDgpu && DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga) {
        Data8 = CpmTableProtocolPtr->CommonFunction.PciRead8 (
                                CpmTableProtocolPtr,
                                0,
                                DevicePathTablePtr->Path[i].Bridge.Device,
                                DevicePathTablePtr->Path[i].Bridge.Function,
                                0x3E                                  // R_IRQ_BRIDGE_CNTL
                                );
        if (!(Data8 & BIT3)) {
          // Clear IO decoding if VGA
          CpmTableProtocolPtr->CommonFunction.PciAnd8 (
                                CpmTableProtocolPtr,
                                (UINT8)DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus,
                                DevicePathTablePtr->Path[i].Device.Device,
                                DevicePathTablePtr->Path[i].Device.Function,
                                0x04,                                 // PCI_COMMAND_OFFSET,
                                0xFE
                                );
        }
      }
    } else {
      break;
    }
  }
  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDisableIoDecodeEnd);
  return;
}

VOID
AmdCpmDisableIoDecodeOfPossibleApcGfx (
  IN        EFI_EVENT   Event,
  IN        VOID        *Context
  )
{
  AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr;
  AMD_CPM_TABLE_PROTOCOL              *CpmTableProtocolPtr;
  CPM_DISPLAY_FEATURE_PRIVATE         *DisplayFeatureDataPtr;
  AMD_CPM_DEVICE_PATH_TABLE           *DevicePathTablePtr;
  UINT8                               SecondaryBus;
  UINT8                               Data8;
  UINT8                               i;

  CpmDisplayFeatureProtocolPtr = Context;
  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
  CpmTableProtocolPtr     = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;
  DevicePathTablePtr      = DisplayFeatureDataPtr->DevicePathTablePtr;

  SecondaryBus = 0;
  Data8 = 0;
  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDisableIoDecodeBegin);

  for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
    if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
      if (!DevicePathTablePtr->Path[i].IsDgpu && DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist) {
        if (!DevicePathTablePtr->Path[i].Bridge.Device) {
          SecondaryBus = CpmTableProtocolPtr->CommonFunction.PciRead8 (
                                CpmTableProtocolPtr,
                                0,
                                DevicePathTablePtr->Path[i].Bridge.Device,
                                DevicePathTablePtr->Path[i].Bridge.Function,
                                0x19                                            // PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET
                                );
        }
        Data8 = CpmTableProtocolPtr->CommonFunction.PciRead8 (
                                CpmTableProtocolPtr,
                                SecondaryBus,
                                DevicePathTablePtr->Path[i].Device.Device,
                                DevicePathTablePtr->Path[i].Device.Function,
                                0x0B                                            // R_BASE_CODE
                                );
        if (Data8 == 0x3) {
          // Clear IO decoding if VGA
          CpmTableProtocolPtr->CommonFunction.PciAnd8 (
                                CpmTableProtocolPtr,
                                SecondaryBus,
                                DevicePathTablePtr->Path[i].Device.Device,
                                DevicePathTablePtr->Path[i].Device.Function,
                                0x04,                                           // PCI_COMMAND_OFFSET,
                                0xFE
                                );
          break;
        }
      }
    } else {
      break;
    }
  }
  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDisableIoDecodeEnd);
  return;
}

VOID
AmdCpmClearPossiblePcieGFX (
  IN        VOID        *Context
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   LegacyBootEvent;

  LegacyBootEvent = NULL;
  Status = CpmCreateEventReadyToBoot (
              CPM_TPL_CALLBACK,
              AmdCpmDisableIoDecodeOfPossiblePcieGfx,
              Context,
              &LegacyBootEvent
              );
  ASSERT_EFI_ERROR (Status);
  return;
}

VOID
AmdCpmClearPossibleApcGFX (
  IN        VOID        *Context
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   LegacyBootEvent;

  LegacyBootEvent = NULL;
  Status = CpmCreateEventReadyToBoot (
              CPM_TPL_CALLBACK,
              AmdCpmDisableIoDecodeOfPossibleApcGfx,
              Context,
              &LegacyBootEvent
              );
  ASSERT_EFI_ERROR (Status);
  return;
}

VOID
AmdCpmGetGpuVbiosImage (
  IN       AMD_CPM_DISPLAY_FEATURE_PROTOCOL   *CpmDisplayFeatureProtocolPtr,
  IN       UINT8                              GpuType,
     OUT   VOID                               **VBiosImage,
     OUT   UINTN                              *VBiosImageSize
  )
{
  EFI_STATUS                                  Status;
  UINTN                                       HandleCount;
  EFI_HANDLE                                  *HandleBuffer;
  UINTN                                       Index;
  EFI_PCI_IO_PROTOCOL                         *PciIo;
  BOOLEAN                                     Found;
  AMD_CPM_ALL_PCI_IO_PROTOCOLS_INSTALLED_PROTOCOL   *Tmp;
  UINT32                                      *VbiosInfo;
  UINTN                                       Seg;
  UINTN                                       Bus;
  UINTN                                       Dev;
  UINTN                                       Fnc;
  UINT8                                       GpuBus;
  EFI_HANDLE                                  VgaHandle;
  UINT16                                      dGpVid;
  CPM_DISPLAY_FEATURE_PRIVATE                 *DisplayFeatureDataPtr;
  UINT16                                      *TmpPtr;
  PCI_DATA_STRUCTURE                          *TmpPciDataStruct;

  dGpVid = 0;
  Found = FALSE;
  PciIo = NULL;
  GpuBus = 0x00;
  Seg = 0x00;
  Bus = 0x00;
  Dev = 0x00;
  Fnc = 0x00;
  VgaHandle = NULL;
  DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;

  //
  // A. Search Int or Ext GFX bridge and then get the SubBus information from this bridge
  //

  //  Step 01.
  //  Search handles that support the gEfiPciIoProtocolGuid protocol
  //  gBS->LocateHandleBuffer returns an array of handles.

  Status = gBS->LocateHandleBuffer (
                      ByProtocol,
                      &gEfiPciIoProtocolGuid,
                      NULL,
                      &HandleCount,
                      &HandleBuffer
                      );

  ASSERT_EFI_ERROR (Status);

  //
  //B. Search iGPU / dGPU device under bridge
  //

  *VBiosImage     = NULL;
  *VBiosImageSize = 0;

  for (Index = 0; (Index < HandleCount) && (Found == FALSE); Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiPciIoProtocolGuid,
                    (VOID**)&PciIo
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Step 01.
    // See if this is a PCI Graphics Controller by looking at Class Code Register
    //
    PciIo->GetLocation (
             PciIo,
             &Seg,
             &Bus,
             &Dev,
             &Fnc
             );

    if (((UINTN)Bus == DisplayFeatureDataPtr->GfxDevicePfa[GpuType].Pfa.Bus) &&
        ((UINTN)Dev == DisplayFeatureDataPtr->GfxDevicePfa[GpuType].Pfa.Device) &&
        ((UINTN)Fnc == DisplayFeatureDataPtr->GfxDevicePfa[GpuType].Pfa.Function)) {

      Status = PciIo->Pci.Read (
                          PciIo,
                          EfiPciIoWidthUint16,
                          PCI_VENDOR_ID_OFFSET,       //Start offset: 0x00
                          1,                          //Length of bytes
                          &dGpVid
                          );

      if (dGpVid != 0xFFFF) {
        VgaHandle       = HandleBuffer[Index];
        *VBiosImage     = PciIo->RomImage;
        *VBiosImageSize = (UINTN) PciIo->RomSize;
      } else {
        *VBiosImage     = NULL;
        *VBiosImageSize = 0;
      }
      Found = TRUE;
    }
  }

  //
  // Check VBIOS ROM SIZE. if it is harger 64K bytes, it must be adjusted.
  //
  if (*VBiosImageSize > 0x10000) {
    //
    // Get a Pointer to PCI Data Structure from offset 0x18,0x19
    //
    TmpPtr = (UINT16 *) ((UINT8 *) (*VBiosImage) + 0x18);

    //
    // Get actual VBios image size
    //
    TmpPciDataStruct = (PCI_DATA_STRUCTURE *) ((UINT8 *) (*VBiosImage) + (*TmpPtr));
    *VBiosImageSize = (UINT16) (TmpPciDataStruct->ImageLength) * 512;
  }

  if (GpuType == 1) {
    //
    //Step03. Save OpRom info. to an Array of AmdCpmAllPciIoProtocolsInstalledProtocolGuid
    //
    Status = gBS->AllocatePool (
                    EfiBootServicesData,
                    12,                      //(UINT32 = 4 bytes, 4 byte * 3 = 12 bytes)
                    (VOID**)&VbiosInfo
                    );

    Status = gBS->LocateProtocol (&gAmdCpmAllPciIoProtocolsInstalledProtocolGuid, NULL, (VOID**)&Tmp);
    VbiosInfo[0] = (UINT32) (UINTN)*VBiosImage;
    VbiosInfo[1] = (UINT32) *VBiosImageSize;
    VbiosInfo[2] = (UINT32) (UINTN)VgaHandle;

    DisplayFeatureDataPtr->VBiosImage       = (UINT32) (UINTN) *VBiosImage;
    DisplayFeatureDataPtr->VBiosImageSize   = (UINT32) *VBiosImageSize;

    if (DisplayFeatureDataPtr->VBiosImage && DisplayFeatureDataPtr->VBiosImageSize) {
      DisplayFeatureDataPtr->VBiosFlag      = TRUE;
    } else {
      DisplayFeatureDataPtr->VBiosFlag      = FALSE;
    }

    Tmp->Buffer = (VOID *)VbiosInfo;
  }

  return;
}

AGESA_STATUS
AmdCpmGetPostedVbiosImage (
  IN      GFX_VBIOS_IMAGE_INFO         *VbiosImageInfo
  )
{
  AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr;
  CPM_DISPLAY_FEATURE_PRIVATE         *DisplayFeatureDataPtr;
  EFI_STATUS                          Status;
  AGESA_STATUS                        CpmStatus;
  VOID                                *VBiosImage = NULL;
  UINTN                               VBiosImageSize = 0;
  UINT32                              IsDgpuPrimary;
  UINT32                              SpecialPostIgpu;
  UINT32                              CurrentPowerXpress;
  UINT32                              CurrentSurroundView;
  UINT32                              CurrentHyperCrossFire;
  UINT32                              CurrentHybridGraphics;
  AMD_CPM_TABLE_PROTOCOL              *CpmTableProtocolPtr;

  CpmStatus = AGESA_UNSUPPORTED;
  Status = gBS->LocateProtocol (
                  &gAmdCpmDisplayFeatureProtocolGuid,
                  NULL,
                  (VOID**)&CpmDisplayFeatureProtocolPtr
                  );
  if (!EFI_ERROR (Status)) {
    DisplayFeatureDataPtr = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
    CpmTableProtocolPtr   = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;
    IsDgpuPrimary         = CpmTableProtocolPtr->MainTablePtr->DisplayFeature.Config.IsDgpuPrimary;
    SpecialPostIgpu       = CpmTableProtocolPtr->MainTablePtr->DisplayFeature.Config.SpecialPostIgpu;
    CurrentPowerXpress    = DisplayFeatureDataPtr->CurrentFeature.Mask.PowerXpress;
    CurrentSurroundView   = DisplayFeatureDataPtr->CurrentFeature.Mask.SurroundView;
    CurrentHyperCrossFire = DisplayFeatureDataPtr->CurrentFeature.Mask.HyperCrossFire;
    CurrentHybridGraphics = DisplayFeatureDataPtr->CurrentFeature.Mask.HybridGraphics;

    if ((CurrentPowerXpress || CurrentSurroundView || CurrentHyperCrossFire || SpecialPostIgpu || CurrentHybridGraphics) && IsDgpuPrimary) {
      if (DisplayFeatureDataPtr->GfxDevicePfa[0].Raw == 0) {
        DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Bus = 0;
        DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Device = 1;
        DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Function = 0;
      }
      if ((DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Bus == VbiosImageInfo->GfxPciAddress.Address.Bus) &&
          (DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Device == VbiosImageInfo->GfxPciAddress.Address.Device) &&
          (DisplayFeatureDataPtr->GfxDevicePfa[0].Pfa.Function == VbiosImageInfo->GfxPciAddress.Address.Function)) {
        if ((VbiosImageInfo->Flags & GFX_VBIOS_IMAGE_FLAG_SPECIAL_POST) != 0) {
          // HCF-dGPU or SurroundView
          AmdCpmGetGpuVbiosImage (CpmDisplayFeatureProtocolPtr, 0, (VOID *)&VBiosImage, &VBiosImageSize);
          if (VBiosImage && VBiosImageSize) {
            AmdCpmSetApcAndiGFX (CpmDisplayFeatureProtocolPtr);
            AmdCpmDgpuSpecialPostForHcfiGpu (CpmDisplayFeatureProtocolPtr, VBiosImage, VBiosImageSize);
            VbiosImageInfo->ImagePtr = VBiosImage;
            CpmStatus = AGESA_SUCCESS;
          }
        }
      }
    }
  }
  return CpmStatus;
}

VOID
EFIAPI
AmdCpmDisplayFeatureVbiosShadow (
  IN        EFI_EVENT                   Event,
  IN        VOID                        *Context
  )
{
  AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *CpmDisplayFeatureProtocolPtr;
  CPM_DISPLAY_FEATURE_PRIVATE         *DisplayFeatureDataPtr;
  AMD_CPM_MAIN_TABLE                  *MainTablePtr;
  AMD_CPM_DEVICE_PATH_TABLE           *DevicePathTablePtr;
  AMD_CPM_DEVICE_PATH_ITEM            *iGpuDevice;
  AMD_CPM_DEVICE_PATH_ITEM            *dGpuDevice;
  AMD_CPM_GPIO_DEVICE_POWER_TABLE     *GpioDevicePowerTablePtr;
  AMD_CPM_TABLE_PROTOCOL              *CpmTableProtocolPtr;

  STATIC BOOLEAN                      IsInvoked = FALSE;
  UINT8                               i;
  UINT8                               bus;
  UINT8                               MultiBridge;
  UINT8                               DisplayStatus;
  UINT16                              GfxVid;
  UINT16                              ClassCode;
  UINT8                               GpioDeviceId;
  UINT8                               DeviceId;
  UINT8                               Mode;
  UINT8                               Index;
  VOID                                *VBiosImage = NULL;
  UINTN                               VBiosImageSize = 0;
  UINT32                              IsDgpuPrimary;
  UINT32                              CfgDisableDgpuAudioInPX;
  UINT32                              CfgEnableDgpuSmbusInPX;
  UINT32                              CurrentPowerXpress;
  UINT32                              CurrentHyperCrossFire;
  UINT32                              CurrentNonAmdGpu;
  UINT32                              CurrentHybridGraphics;
  UINT32                              CurrentD3Cold;

  RECORD_TIME_DXE (BeginAmdCpmDisplayFeatureMidInit);

  CpmDisplayFeatureProtocolPtr = Context;
  CpmTableProtocolPtr = CpmDisplayFeatureProtocolPtr->TableProtocolPtr;
  DisplayStatus = 0;
  iGpuDevice = NULL;
  dGpuDevice = NULL;
  ClassCode = 0;
  CurrentNonAmdGpu = 0;

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureVbiosShadowBegin);

  if (!IsInvoked) {
    MainTablePtr            = CpmTableProtocolPtr->MainTablePtr;
    IsDgpuPrimary           = MainTablePtr->DisplayFeature.Config.IsDgpuPrimary;
    CfgDisableDgpuAudioInPX = MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX;
    CfgEnableDgpuSmbusInPX  = MainTablePtr->DisplayFeature.Config.EnableDgpuSmbusInPX;
    DisplayFeatureDataPtr   = &CpmDisplayFeatureProtocolPtr->DisplayFeatureData;
    DevicePathTablePtr      = DisplayFeatureDataPtr->DevicePathTablePtr;
    GpioDevicePowerTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_GPIO_DEVICE_POWER);

    CpmTableProtocolPtr->DxePublicFunction.GetPostedVbiosImage = AmdCpmGetPostedVbiosImage;

    if (MainTablePtr->DisplayFeature.Config.PowerXpressFixedMode || MainTablePtr->DisplayFeature.Config.PowerXpressDynamicMode) {
      DisplayFeatureDataPtr->CurrentFeature.Mask.PowerXpress = 1;
    }
    if (MainTablePtr->DisplayFeature.Config.HybridGraphicsSupport) {
      DisplayFeatureDataPtr->CurrentFeature.Mask.HybridGraphics = 1;
    }
    if (MainTablePtr->DisplayFeature.Config.HyperCrossFire) {
      DisplayFeatureDataPtr->CurrentFeature.Mask.HyperCrossFire = 1;
    }
    if (MainTablePtr->DisplayFeature.Config.SurroundView) {
      DisplayFeatureDataPtr->CurrentFeature.Mask.SurroundView = 1;
    }
    if (MainTablePtr->DisplayFeature.Config.D3ColdSupport) {
      DisplayFeatureDataPtr->CurrentFeature.Mask.D3Cold = 1;
    }
    CurrentPowerXpress      = DisplayFeatureDataPtr->CurrentFeature.Mask.PowerXpress;
    CurrentHyperCrossFire   = DisplayFeatureDataPtr->CurrentFeature.Mask.HyperCrossFire;
    CurrentHybridGraphics   = DisplayFeatureDataPtr->CurrentFeature.Mask.HybridGraphics;
    CurrentD3Cold           = DisplayFeatureDataPtr->CurrentFeature.Mask.D3Cold;

    for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
      DevicePathTablePtr->Path[i].FeatureMask.Raw &= 0x8000FFFF;
      if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
        MultiBridge = 0;
        bus = 0;
        if (DevicePathTablePtr->Path[i].Bridge.Device == 0) {
          GfxVid = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                              bus,
                              DevicePathTablePtr->Path[i].Device.Device,
                              DevicePathTablePtr->Path[i].Device.Function,
                              PCI_VENDOR_ID_OFFSET );
          ClassCode = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                              bus,
                              DevicePathTablePtr->Path[i].Device.Device,
                              DevicePathTablePtr->Path[i].Device.Function,
                              PCI_CLASSCODE_OFFSET + 1 );
        } else {
          GfxVid = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                              0,
                              DevicePathTablePtr->Path[i].Bridge.Device,
                              DevicePathTablePtr->Path[i].Bridge.Function,
                              PCI_VENDOR_ID_OFFSET );
          if (GfxVid != 0xFFFF && GfxVid != 0x0000 && (GfxVid & 0xFFDF) == 0x1002) {
            bus = CpmTableProtocolPtr->CommonFunction.PciRead8 ( CpmTableProtocolPtr,
                              0,
                              DevicePathTablePtr->Path[i].Bridge.Device,
                              DevicePathTablePtr->Path[i].Bridge.Function,
                              PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET );
            ClassCode = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                              bus,
                              0,
                              0,
                              PCI_CLASSCODE_OFFSET + 1 );
            if (ClassCode == 0x0604) {
              MultiBridge = 1;
              bus = CpmTableProtocolPtr->CommonFunction.PciRead8 ( CpmTableProtocolPtr,
                                bus,
                                0,
                                0,
                                PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET );
              ClassCode = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                                bus,
                                0,
                                0,
                                PCI_CLASSCODE_OFFSET + 1 );
              if (ClassCode == 0x0604) {
                MultiBridge = 3;
                bus = CpmTableProtocolPtr->CommonFunction.PciRead8 ( CpmTableProtocolPtr,
                                  bus,
                                  0,
                                  0,
                                  PCI_BRIDGE_SECONDARY_BUS_REGISTER_OFFSET );
              }
            }
            ClassCode = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                              bus,
                              DevicePathTablePtr->Path[i].Device.Device,
                              DevicePathTablePtr->Path[i].Device.Function,
                              PCI_CLASSCODE_OFFSET + 1 );
            GfxVid = CpmTableProtocolPtr->CommonFunction.PciRead16 ( CpmTableProtocolPtr,
                              bus,
                              DevicePathTablePtr->Path[i].Device.Device,
                              DevicePathTablePtr->Path[i].Device.Function,
                              PCI_VENDOR_ID_OFFSET );
          }
        }
        if (GfxVid != 0xFFFF && GfxVid != 0x0000 && (ClassCode & 0xFF00) == 0x0300) {
          if ((GfxVid & 0xFFDF) != 0x1002) {
            DevicePathTablePtr->Path[i].FeatureMask.Mask.NonAmdGpu = 1;
            MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX = 0;
            CfgDisableDgpuAudioInPX = 0;
            CurrentNonAmdGpu = 1;
          }
          DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist = 1;
          DevicePathTablePtr->Path[i].FeatureMask.Mask.MultiBridge = MultiBridge;
          if (DevicePathTablePtr->Path[i].FeatureMask.Raw) {
            if (DevicePathTablePtr->Path[i].IsDgpu) {
              if (!dGpuDevice) {
                dGpuDevice = &(DevicePathTablePtr->Path[i]);
                AmdCpmSaveGfxResourceInitMid ( CpmTableProtocolPtr, MultiBridge, bus,
                                                &(DevicePathTablePtr->Path[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgePfa[i]),
                                                &(DisplayFeatureDataPtr->GfxDevicePfa[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgePMem[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgeUpSt[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgeDnSt[i]),
                                                &(DisplayFeatureDataPtr->GfxDevicePMem[i]) );
                if (IsDgpuPrimary) {
                  DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga = 1;
                }
              }
            } else {
              if (!iGpuDevice) {
                iGpuDevice = &(DevicePathTablePtr->Path[i]);
                AmdCpmSaveGfxResourceInitMid ( CpmTableProtocolPtr, MultiBridge, bus,
                                                &(DevicePathTablePtr->Path[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgePfa[i]),
                                                &(DisplayFeatureDataPtr->GfxDevicePfa[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgePMem[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgeUpSt[i]),
                                                &(DisplayFeatureDataPtr->GfxBridgeDnSt[i]),
                                                &(DisplayFeatureDataPtr->GfxDevicePMem[i]) );
                if (!IsDgpuPrimary) {
                  DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga = 1;
                  if (CurrentPowerXpress || CurrentHybridGraphics) {
                    DevicePathTablePtr->Path[i].FeatureMask.Mask.Removable = 1;
                  }
                }
              }
            }
          }
          if (!DisplayFeatureDataPtr->CurrentFeature.Raw) {
            DevicePathTablePtr->Path[i].FeatureMask.Raw &= 0xFFFFFFE0;
          }
          if (DevicePathTablePtr->Path[i].IsDgpu) {
            DisplayStatus |= BIT0;
          } else {
            DisplayStatus |= BIT1;
          }
          DevicePathTablePtr->Path[i].FeatureMask.Mask.Bus = bus;
        } else {
          DevicePathTablePtr->Path[i].FeatureMask.Raw &= 0xFFFFFFE0;
        }
      } else {
        break;
      }
    }

    if (!(iGpuDevice && dGpuDevice)) {
      if (iGpuDevice) {
        MainTablePtr->DisplayFeature.Config.IsDgpuPrimary = 0;
      } else if (dGpuDevice) {
        MainTablePtr->DisplayFeature.Config.IsDgpuPrimary = 1;
      } else {
        for (Index = 0; Index < 2; Index ++) {
          for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
            if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
              break;
            }
            if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist == 1) {
              if (DevicePathTablePtr->Path[i].IsDgpu == IsDgpuPrimary) {
                DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga = 1;
                break;
              }
            }
          }
          if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Vga == 1) {
            break;
          }
          MainTablePtr->DisplayFeature.Config.IsDgpuPrimary = 1;
        }
      }
      DisplayFeatureDataPtr->CurrentFeature.Raw &= 0xFFFFFFE8;
      MainTablePtr->DisplayFeature.Raw &= 0xFFFFFF00;
      if (DisplayStatus == (BIT0 | BIT1)) {
        if (!IsDgpuPrimary) {
          AmdCpmClearPossiblePcieGFX (Context);
        } else {
          AmdCpmClearPossibleApcGFX (Context);
          AmdCpmClearPossiblePcieGFX (Context);
        }
      } else if (DisplayStatus == BIT0) {
        AmdCpmClearPossiblePcieGFX (Context);
      }

      for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
        if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
          break;
        }
        if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist == 1) {
          if (DevicePathTablePtr->Path[i].IsDgpu == IsDgpuPrimary) {
            if (GpioDevicePowerTablePtr) {
              DeviceId  = DevicePathTablePtr->Path[i].DeviceId;
              Mode      = DevicePathTablePtr->Path[i].Mode;
              if (DeviceId != 0xFF && DeviceId != 0x00) {
                for (Index = 0; Index < AMD_GPIO_DEVICE_POWER_SIZE; Index++) {
                  GpioDeviceId = GpioDevicePowerTablePtr->DevicePowerList[Index].DeviceId;
                  if (GpioDeviceId == 0xFF || GpioDeviceId == 0x00) {
                    break;
                  }
                  if (GpioDeviceId == DeviceId &&
                      GpioDevicePowerTablePtr->DevicePowerList[Index].Mode == Mode &&
                      GpioDevicePowerTablePtr->DevicePowerList[Index].Type == 0) {
                    CpmTableProtocolPtr->CommonFunction.SetGpio (
                                                                  CpmTableProtocolPtr,
                                                                  GpioDevicePowerTablePtr->DevicePowerList[Index].Config.SetGpio.Pin,
                                                                  GpioDevicePowerTablePtr->DevicePowerList[Index].Config.SetGpio.Value
                                                                  );
                  }
                }
              }
            }
            break;
          }
        }
      }
      if (CfgDisableDgpuAudioInPX) {
        AmdCpmDisableDgpuAudioInPX (CpmDisplayFeatureProtocolPtr);
      }
      if (CfgEnableDgpuSmbusInPX && !IsDgpuPrimary) {
        AmdCpmEnableDgpuSmbusInPX (CpmDisplayFeatureProtocolPtr);
      }
    } else {
      if (!CurrentNonAmdGpu) {
        if ((CurrentPowerXpress || CurrentHyperCrossFire || CurrentHybridGraphics) && !IsDgpuPrimary) {
          // PowerXpress or HybridGraphics
          AmdCpmGetGpuVbiosImage (CpmDisplayFeatureProtocolPtr, 1, (VOID *)&VBiosImage, &VBiosImageSize);
        }
        if (CfgDisableDgpuAudioInPX) {
          AmdCpmDisableDgpuAudioInPX (CpmDisplayFeatureProtocolPtr);
        }
        if (CfgEnableDgpuSmbusInPX && !IsDgpuPrimary) {
          AmdCpmEnableDgpuSmbusInPX (CpmDisplayFeatureProtocolPtr);
        }
        if (IsDgpuPrimary) {
          AmdCpmClearPossibleApcGFX (Context);
          AmdCpmClearPossiblePcieGFX (Context);
        } else {
          AmdCpmClearPossiblePcieGFX (Context);
        }
      } // End of if (!CurrentNonAmdGpu)
    } // End of if (!(iGpuDevice & dGpuDevice))
  } // End of if (!IsInvoked)

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureVbiosShadowEnd);

  IsInvoked = TRUE;

  RECORD_TIME_DXE (EndAmdCpmDisplayFeatureMidInit);
}

/*----------------------------------------------------------------------------------------*/
/**
 * AmdCpmDisplayFeatureInitMid
 *
 * This function is called as part of CPM DXE Driver Initialization. It gets called
 * each time the AMD CPM ALL PCI IO PROTOCOLS INSTALLED PROTOCOL is installed.
 *
 * @param[in]     Event          EFI_EVENT
 * @param[in]     Context        The Parameter Buffer
 *
 */

VOID
EFIAPI
AmdCpmDisplayFeatureInitMid (
  IN        EFI_EVENT                       Event,
  IN        VOID                            *Context
  )
{
  EFI_STATUS      Status = 0;
  STATIC BOOLEAN  AmdCpmDisplayFeatureInitMidInvoked = FALSE;
  EFI_EVENT       DisplayFeatureVbiosShadow;
  VOID            *mRegisterationForVbiosShadow;

  if (!AmdCpmDisplayFeatureInitMidInvoked) {

    //
    // Register the event handling function for AmdCpmDisplayFeatureInitMid to be launched after
    // PciIo protocol
    //
    Status = gBS->CreateEvent (
                    CPM_EVENT_NOTIFY_SIGNAL,
                    CPM_TPL_NOTIFY,
                    AmdCpmDisplayFeatureVbiosShadow,
                    Context,
                    &DisplayFeatureVbiosShadow
                    );

    if (EFI_ERROR (Status)) {
      return;
    }

    Status = gBS->RegisterProtocolNotify (
                    &gAmdCpmAllPciIoProtocolsInstalledProtocolGuid,
                    DisplayFeatureVbiosShadow,
                    &mRegisterationForVbiosShadow
                    );

    if (EFI_ERROR (Status)) {
      return;
    }
  }

  AmdCpmDisplayFeatureInitMidInvoked = TRUE;
}
