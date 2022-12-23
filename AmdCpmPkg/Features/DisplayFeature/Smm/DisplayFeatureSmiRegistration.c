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
#include <Protocol/AmdApcbProtocol.h>
#include <ApcbCommon.h>

CPM_EXTERN_gBS;

UINT32                          mDgpuSsid;
UINT32                          mDgpuAudioSsid;

extern  AMD_CPM_DISPLAY_FEATURE_PROTOCOL    *gCpmDisplayFeatureSmmProtocol;

VOID
AmdCpmSaveGfxResource (
  IN        CPM_DISPLAY_FEATURE_PRIVATE     *DisplayFeatureDataPtr,
  IN        AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr,
  IN        UINT8                           i,
     OUT    AMD_CPM_PCI_BPMEM               *RootBridgeData,
     OUT    AMD_CPM_PCI_BPMEM               *UpStBridgeData,
     OUT    AMD_CPM_PCI_BPMEM               *DnStBridgeData,
     OUT    AMD_CPM_PCI_DPMEM               *DevicePciData
  )
{
  RootBridgeData->BridgeCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x04 );

  RootBridgeData->BusNumberReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x18 );

  RootBridgeData->BridgeNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x20 );

  RootBridgeData->LimitBaseLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x24 );

  RootBridgeData->BaseHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x28 );

  RootBridgeData->LimitHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x2C );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x18,
                    DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg );

  if (DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg != 0) {
    UpStBridgeData->BridgeCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04 );

    UpStBridgeData->BusNumberReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18 );

    UpStBridgeData->BridgeNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20 );

    UpStBridgeData->LimitBaseLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24 );

    UpStBridgeData->BaseHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28 );

    UpStBridgeData->LimitHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18,
                      DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg );
  }

  if ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg != 0) && (DisplayFeatureDataPtr->GfxBridgeDnSt[i].BusNumberReg != 0)){
    DnStBridgeData->BridgeCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04 );

    DnStBridgeData->BusNumberReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18 );

    DnStBridgeData->BridgeNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20 );

    DnStBridgeData->LimitBaseLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24 );

    DnStBridgeData->BaseHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28 );

    DnStBridgeData->LimitHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18,
                      DisplayFeatureDataPtr->GfxBridgeDnSt[i].BusNumberReg );
  }

  DevicePciData->DeviceIdReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x00 );

  DevicePciData->DeviceCommand = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x04 );

  DevicePciData->DoorbellLowReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x18 );

  DevicePciData->DoorbellHighReg = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x1C );

  DevicePciData->DeviceNonPrefetchable = CpmTableProtocolPtr->CommonFunction.PciRead32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x24 );
}

VOID
AmdCpmProgramGfxResource (
  IN        CPM_DISPLAY_FEATURE_PRIVATE     *DisplayFeatureDataPtr,
  IN        AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr,
  IN        UINT8                           i
  )
{
  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x18,
                    DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x20,
                    DisplayFeatureDataPtr->GfxBridgePMem[i].BridgeNonPrefetchable );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x24,
                    DisplayFeatureDataPtr->GfxBridgePMem[i].LimitBaseLowReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x28,
                    DisplayFeatureDataPtr->GfxBridgePMem[i].BaseHighReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x2C,
                    DisplayFeatureDataPtr->GfxBridgePMem[i].LimitHighReg );

  CpmTableProtocolPtr->CommonFunction.PciOr8 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x04,
                    0x02 );

  if (DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg != 0) {
    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18,
                      DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20,
                      DisplayFeatureDataPtr->GfxBridgeUpSt[i].BridgeNonPrefetchable );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24,
                      DisplayFeatureDataPtr->GfxBridgeUpSt[i].LimitBaseLowReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28,
                      DisplayFeatureDataPtr->GfxBridgeUpSt[i].BaseHighReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C,
                      DisplayFeatureDataPtr->GfxBridgeUpSt[i].LimitHighReg );

    CpmTableProtocolPtr->CommonFunction.PciOr8 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04,
                      0x02 );
  }

  if ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg != 0) && (DisplayFeatureDataPtr->GfxBridgeDnSt[i].BusNumberReg != 0)){
    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18,
                      DisplayFeatureDataPtr->GfxBridgeDnSt[i].BusNumberReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20,
                      DisplayFeatureDataPtr->GfxBridgeDnSt[i].BridgeNonPrefetchable );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24,
                      DisplayFeatureDataPtr->GfxBridgeDnSt[i].LimitBaseLowReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28,
                      DisplayFeatureDataPtr->GfxBridgeDnSt[i].BaseHighReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C,
                      DisplayFeatureDataPtr->GfxBridgeDnSt[i].LimitHighReg );

    CpmTableProtocolPtr->CommonFunction.PciOr8 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04,
                      0x02 );
  }

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x18,
                    DisplayFeatureDataPtr->GfxDevicePMem[i].DoorbellLowReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x1C,
                    DisplayFeatureDataPtr->GfxDevicePMem[i].DoorbellHighReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x24,
                    DisplayFeatureDataPtr->GfxDevicePMem[i].DeviceNonPrefetchable );

  CpmTableProtocolPtr->CommonFunction.PciOr8 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x04,
                    0x02 );
}

VOID
AmdCpmRestoreGfxResource (
  IN        CPM_DISPLAY_FEATURE_PRIVATE     *DisplayFeatureDataPtr,
  IN        AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr,
  IN        UINT8                           i,
     OUT    AMD_CPM_PCI_BPMEM               *RootBridgeData,
     OUT    AMD_CPM_PCI_BPMEM               *UpStBridgeData,
     OUT    AMD_CPM_PCI_BPMEM               *DnStBridgeData,
     OUT    AMD_CPM_PCI_DPMEM               *DevicePciData
  )
{
  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x04,
                    DevicePciData->DeviceCommand );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x18,
                    DevicePciData->DoorbellLowReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x1C,
                    DevicePciData->DoorbellHighReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxDevicePfa[i].Pfa.Function,
                    0x24,
                    DevicePciData->DeviceNonPrefetchable );

  if ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg != 0) && (DisplayFeatureDataPtr->GfxBridgeDnSt[i].BusNumberReg != 0)){
    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04,
                      DnStBridgeData->BridgeCommand );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18,
                      DnStBridgeData->BusNumberReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20,
                      DnStBridgeData->BridgeNonPrefetchable );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24,
                      DnStBridgeData->LimitBaseLowReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28,
                      DnStBridgeData->BaseHighReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C,
                      DnStBridgeData->LimitHighReg );
  }

  if (DisplayFeatureDataPtr->GfxBridgeUpSt[i].BusNumberReg != 0) {
    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x04,
                      UpStBridgeData->BridgeCommand );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x18,
                      UpStBridgeData->BusNumberReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x20,
                      UpStBridgeData->BridgeNonPrefetchable );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x24,
                      UpStBridgeData->LimitBaseLowReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x28,
                      UpStBridgeData->BaseHighReg );

    CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                      (UINT8) ((DisplayFeatureDataPtr->GfxBridgePMem[i].BusNumberReg >> 8) & 0xFF),
                      0,
                      0,
                      0x2C,
                      UpStBridgeData->LimitHighReg );
  }

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x04,
                    RootBridgeData->BridgeCommand );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x18,
                    RootBridgeData->BusNumberReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x20,
                    RootBridgeData->BridgeNonPrefetchable );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x24,
                    RootBridgeData->LimitBaseLowReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x28,
                    RootBridgeData->BaseHighReg );

  CpmTableProtocolPtr->CommonFunction.PciWrite32 ( CpmTableProtocolPtr,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Bus,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Device,
                    DisplayFeatureDataPtr->GfxBridgePfa[i].Pfa.Function,
                    0x2C,
                    RootBridgeData->LimitHighReg );
}

/*----------------------------------------------------------------------------------------*/
/**
 *
 * The function to disable audio in dGPU when PowerXpress is enabled and sets SSID
 *
 * @param[in]     DispatchHandle  The handle of this callback, obtained when registering
 * @param[in]     DispatchContext Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
 *
 * @retval        EFI_SUCCESS     Callback function successfully
 * @retval        EFI_ERROR       Callback function failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmDisableDgpuAudioInPXSmm (
  IN        EFI_HANDLE                      DispatchHandle,
  IN        CPM_SMM_SW_DISPATCH_CONTEXT     *DispatchContext
  )
{
  CPM_DISPLAY_FEATURE_PRIVATE *DisplayFeatureDataPtr;
  AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr;
  AMD_CPM_MAIN_TABLE          *MainTablePtr;
  UINT64                      Mmiobase;
  UINT32                      RomStrapOffset;
  UINT8                       DgpuCase;
  UINT32                      CurrentPowerXpress;
  UINT32                      DisableDgpuAudioInPX;
  UINT32                      IsDgpuPrimary;

  AMD_CPM_PCI_BPMEM           RootBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_BPMEM           UpStBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_BPMEM           DnStBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_DPMEM           DevicePciData  = {0, 0, 0, 0, 0};

  DisplayFeatureDataPtr   = &gCpmDisplayFeatureSmmProtocol->DisplayFeatureData;
  CpmTableProtocolPtr     = gCpmDisplayFeatureSmmProtocol->TableProtocolSmmPtr;
  MainTablePtr            = CpmTableProtocolPtr->MainTablePtr;
  CurrentPowerXpress      = DisplayFeatureDataPtr->CurrentFeature.Mask.PowerXpress;
  DisableDgpuAudioInPX    = MainTablePtr->DisplayFeature.Config.DisableDgpuAudioInPX;
  IsDgpuPrimary           = MainTablePtr->DisplayFeature.Config.IsDgpuPrimary;

  if (DisableDgpuAudioInPX) {
    if (DisplayFeatureDataPtr->GfxDevicePfa[1].Raw) {
      AmdCpmSaveGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, 1, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
      AmdCpmProgramGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, 1);

      if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x67C0) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x67DF)) {
        DgpuCase = 0x10;      // Ellesmere
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x67E0) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x67FF)) {
        DgpuCase = 0x11;      // Baffin
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x6900) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x695F)) {
        DgpuCase = 0x12;      // Iceland(Weston), Tonga, Polaris22
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x6980) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x699F)) {
        DgpuCase = 0x13;      // Lexa
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x6860) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x687F)) {
        DgpuCase = 0x20;      // Greenland
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x69A0) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x69BF)) {
        DgpuCase = 0x21;      // Vega12
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x7310) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x731F)) {
        DgpuCase = 0x22;      // Navi10
      } else if (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) == 0x7330) {
        DgpuCase = 0x22;      // Navi10
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x7340) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x734F)) {
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
      }

      AmdCpmRestoreGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, 1, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
    }
  }
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 *
 * The function to set auto uma mode in smm
 *
 * @param[in]     DispatchHandle  The handle of this callback, obtained when registering
 * @param[in]     DispatchContext Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
 *
 * @retval        EFI_SUCCESS     Callback function successfully
 * @retval        EFI_ERROR       Callback function failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmDisplayFeatureSetAutoUmaModeSmm (
  IN        EFI_HANDLE                      DispatchHandle,
  IN        CPM_SMM_SW_DISPATCH_CONTEXT     *DispatchContext
  )
{
  EFI_STATUS                                Status;
  AMD_CPM_TABLE_PROTOCOL                    *CpmTableProtocolPtr;
  AMD_APCB_SERVICE_PROTOCOL                 *mApcbSmmServiceProtocol;
  UINT16                                    TokenId;
  UINT32                                    SizeInByte;
  UINT64                                    Value;
  UINT8                                     CpuRevisionId;
  AMD_CPM_MAIN_TABLE                        *MainTablePtr;

  CpmTableProtocolPtr = gCpmDisplayFeatureSmmProtocol->TableProtocolSmmPtr;
  MainTablePtr        = CpmTableProtocolPtr->MainTablePtr;
  CpuRevisionId       = MainTablePtr->CpmCpuRevisionId;

  Status = EFI_SUCCESS;
  TokenId = 0;
  SizeInByte = 0;
  Value = 0;

  if (CpuRevisionId > CPM_CPU_REVISION_ID_ZP) {
    Status = CpmSmmLocateProtocol ( &gAmdApcbSmmServiceProtocolGuid,
                                    NULL,
                                    &mApcbSmmServiceProtocol );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    TokenId = APCB_ID_CBS_CMN_GNB_GFX_UMA_MODE;
    SizeInByte = 1;             // UINT8 Size
    Value = 2;                  // UMA_AUTO = 2
    Status = mApcbSmmServiceProtocol->ApcbSetCbsParameter ( mApcbSmmServiceProtocol,
                                                            TokenId,
                                                            &SizeInByte,
                                                            &Value );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    TokenId = APCB_ID_CBS_CMN_GNB_GFX_UMA_VERSION;
    SizeInByte = 1;             // UINT8 Size
    Value = 0;                  // UMA_LEGACY = 0
    Status = mApcbSmmServiceProtocol->ApcbSetCbsParameter ( mApcbSmmServiceProtocol,
                                                            TokenId,
                                                            &SizeInByte,
                                                            &Value );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = mApcbSmmServiceProtocol->ApcbFlushData ( mApcbSmmServiceProtocol );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } // End of if (CpuRevisionId > CPM_CPU_REVISION_ID_ZP)

  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 *
 * The function to enable dGPU Smbus slave device when PowerXpress is enabled
 *
 * @param[in]     DispatchHandle  The handle of this callback, obtained when registering
 * @param[in]     DispatchContext Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
 *
 * @retval        EFI_SUCCESS     Callback function successfully
 * @retval        EFI_ERROR       Callback function failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmEnableDgpuSmbusInPXSmm (
  IN        EFI_HANDLE                      DispatchHandle,
  IN        CPM_SMM_SW_DISPATCH_CONTEXT     *DispatchContext
  )
{
  CPM_DISPLAY_FEATURE_PRIVATE *DisplayFeatureDataPtr;
  AMD_CPM_TABLE_PROTOCOL      *CpmTableProtocolPtr;
  AMD_CPM_MAIN_TABLE          *MainTablePtr;
  UINT64                      Mmiobase;
  UINT32                      RomStrapOffset;
  UINT8                       DgpuCase;
  UINT32                      CurrentPowerXpress;
  UINT32                      CfgEnableDgpuSmbusInPX;
  UINT32                      IsDgpuPrimary;

  AMD_CPM_PCI_BPMEM           RootBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_BPMEM           UpStBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_BPMEM           DnStBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_DPMEM           DevicePciData  = {0, 0, 0, 0, 0};

  DisplayFeatureDataPtr   = &gCpmDisplayFeatureSmmProtocol->DisplayFeatureData;
  CpmTableProtocolPtr     = gCpmDisplayFeatureSmmProtocol->TableProtocolSmmPtr;
  MainTablePtr            = CpmTableProtocolPtr->MainTablePtr;
  CurrentPowerXpress      = DisplayFeatureDataPtr->CurrentFeature.Mask.PowerXpress;
  CfgEnableDgpuSmbusInPX  = MainTablePtr->DisplayFeature.Config.EnableDgpuSmbusInPX;
  IsDgpuPrimary           = MainTablePtr->DisplayFeature.Config.IsDgpuPrimary;

  if (CfgEnableDgpuSmbusInPX && !IsDgpuPrimary) {
    if (DisplayFeatureDataPtr->GfxDevicePfa[1].Raw) {
      AmdCpmSaveGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, 1, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
      AmdCpmProgramGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, 1);

      if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x67C0) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x67DF)) {
        DgpuCase = 0x10;      // Ellesmere
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x67E0) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x67FF)) {
        DgpuCase = 0x11;      // Baffin
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x6900) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x695F)) {
        DgpuCase = 0x12;      // Iceland(Weston), Tonga, Polaris22
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x6980) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x699F)) {
        DgpuCase = 0x13;      // Lexa
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x6860) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x687F)) {
        DgpuCase = 0x20;      // Greenland
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x69A0) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x69BF)) {
        DgpuCase = 0x21;      // Vega12
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x7310) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x731F)) {
        DgpuCase = 0x22;      // Navi10
      } else if (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) == 0x7330) {
        DgpuCase = 0x22;      // Navi10
      } else if ((((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) >= 0x7340) && (((DevicePciData.DeviceIdReg >> 16) & 0xFFFF) <= 0x734F)) {
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
        if (DgpuCase >= 0x20) {
          // Bit8 for SMBUS_ADDR
//          RomStrapOffset = 0x5A208;
//          CpmTableProtocolPtr->CommonFunction.MmioAnd32 ( (Mmiobase & 0xFFFFFFFFFFFFFFF0) + RomStrapOffset, 0xFFFFFEFF );
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
      }

      AmdCpmRestoreGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, 1, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
    }
  }
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to set Sub-System ID
 *
 * @param[in]     DispatchHandle  The handle of this callback, obtained when registering
 * @param[in]     DispatchContext Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
 *
 * @retval        EFI_SUCCESS     Callback function successfully
 * @retval        EFI_ERROR       Callback function failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmSetGpuSsidSmm (
  IN        EFI_HANDLE                      DispatchHandle,
  IN        CPM_SMM_SW_DISPATCH_CONTEXT     *DispatchContext
  )
{
  AMD_CPM_MAIN_TABLE              *MainTablePtr;
  AMD_CPM_TABLE_PROTOCOL          *CpmTableProtocolPtr;
  AMD_CPM_DISPLAY_FEATURE_TABLE   *DisplayFeatureTablePtr;
  AMD_CPM_DEVICE_PATH_TABLE       *DevicePathTablePtr;
  AMD_CPM_SPECIFIC_SSID_TABLE     *SpecificSsidTablePtr;
  AMD_CPM_REBRAND_DUAL_GRAPHICS_SSID_TABLE  *RebrandDualGraphicsSsidTablePtr;
  AMD_CPM_REBRAND_DUAL_GRAPHICS_SSID_TABLE2 *RebrandDualGraphicsSsidTable2Ptr;
  UINT8                           Bus;
  UINT8                           Dev;
  UINT8                           Func;
  UINT16                          VendorId;
  UINT16                          VendorId2;
  UINT16                          DeviceId;
  UINT16                          DeviceId2;
  UINT8                           Index;
  UINT32                          Ssid;
  UINT32                          NewSsid;
  UINT16                          i;
  CPM_DISPLAY_FEATURE_PRIVATE     *DisplayFeatureDataPtr;
  UINT8                           RevId;
  UINT16                          iSsid;
  UINT32                          RebrandDualGraphics;

  AMD_CPM_PCI_BPMEM           RootBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_BPMEM           UpStBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_BPMEM           DnStBridgeData = {0, 0, 0, 0, 0, 0};
  AMD_CPM_PCI_DPMEM           DevicePciData  = {0, 0, 0, 0, 0};

  DisplayFeatureDataPtr   = &gCpmDisplayFeatureSmmProtocol->DisplayFeatureData;
  CpmTableProtocolPtr     = gCpmDisplayFeatureSmmProtocol->TableProtocolSmmPtr;
  MainTablePtr              = CpmTableProtocolPtr->MainTablePtr;
  RebrandDualGraphics       = MainTablePtr->DisplayFeature.Config.RebrandDualGraphics;
  DisplayFeatureTablePtr    = DisplayFeatureDataPtr->DisplayFeatureTablePtr;
  DevicePathTablePtr        = DisplayFeatureDataPtr->DevicePathTablePtr;
  SpecificSsidTablePtr      = DisplayFeatureDataPtr->SpecificSsidTablePtr;
  RebrandDualGraphicsSsidTablePtr   = DisplayFeatureDataPtr->RebrandDualGraphicsSsidTablePtr;
  RebrandDualGraphicsSsidTable2Ptr  = DisplayFeatureDataPtr->RebrandDualGraphicsSsidTablePtr;

  if (DisplayFeatureTablePtr) {

    if (RebrandDualGraphics && RebrandDualGraphicsSsidTablePtr) {
      if (RebrandDualGraphicsSsidTablePtr->Header.FormatRevision != 0) {
        DisplayFeatureTablePtr->FunctionDisableMask |= BIT0;
      }
    }

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
        if ((mDgpuSsid != 0) && (DeviceId != 0xFFFF)) {
          CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func, 0x4C, mDgpuSsid);
        }
        if ((mDgpuAudioSsid != 0) && (DeviceId2 != 0xFFFF)) {
          CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func + 1, 0x4C, mDgpuAudioSsid);
        }
      } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu && DevicePathTablePtr->Path[Index].IsDgpu)
    } // End of for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++)

    if (!(DisplayFeatureTablePtr->FunctionDisableMask & BIT0)) {

      Ssid = DisplayFeatureDataPtr->Ssid;

      for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
        if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
          break;
        }
        if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu) {
          AmdCpmSaveGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
          AmdCpmProgramGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index);
          Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
          Dev       = DevicePathTablePtr->Path[Index].Device.Device;
          Func      = DevicePathTablePtr->Path[Index].Device.Function;
          VendorId  = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x00);
          DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x02);
          DeviceId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func + 1, 0x02);
          NewSsid   = Ssid | (UINT32)VendorId;
          if (SpecificSsidTablePtr) {
            for (i = 0; i < AMD_SPECIFIC_SSID_DEVICE_SIZE; i++) {
              if (SpecificSsidTablePtr->Item[i].VendorId == 0xFFFF) {
                break;
              } else {
                if ((SpecificSsidTablePtr->Item[i].VendorId == VendorId) && (SpecificSsidTablePtr->Item[i].DeviceId == DeviceId)) {
                  CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func, 0x4C, NewSsid);
                }
                if ((DeviceId2 != 0xFFFF) && (SpecificSsidTablePtr->Item[i].VendorId == VendorId) && (SpecificSsidTablePtr->Item[i].DeviceId == DeviceId2)) {
                  CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func + 1, 0x4C, NewSsid);
                }
              }
            }
          } else if (mDgpuSsid == 0) {
            CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func, 0x4C, NewSsid);
          }
          AmdCpmRestoreGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
        } // End of if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && !DevicePathTablePtr->Path[Index].FeatureMask.Mask.NonAmdGpu)
      }
    }

    if (RebrandDualGraphics && RebrandDualGraphicsSsidTablePtr) {
      Ssid = DisplayFeatureDataPtr->Ssid2;
      switch (RebrandDualGraphicsSsidTablePtr->Header.FormatRevision) {
      case 0:
        if (Ssid != 0xFFFF0000) {
          for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
            if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
              break;
            }
            if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[Index].IsDgpu) {
              AmdCpmSaveGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
              AmdCpmProgramGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index);
              Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
              Dev       = DevicePathTablePtr->Path[Index].Device.Device;
              Func      = DevicePathTablePtr->Path[Index].Device.Function;
              VendorId  = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x00);
              VendorId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x2C);
              DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x02);
              NewSsid   = Ssid | (UINT32)VendorId2;

              for (i = 0; i < AMD_REBRAND_DUAL_GRAPHICS_SSID_DEVICE_SIZE; i++) {
                if (RebrandDualGraphicsSsidTablePtr->Item[i].VendorId == 0xFFFF) {
                  break;
                } else {
                  if ((RebrandDualGraphicsSsidTablePtr->Item[i].VendorId == VendorId) &&
                      (RebrandDualGraphicsSsidTablePtr->Item[i].DeviceId == DeviceId) &&
                      (RebrandDualGraphicsSsidTablePtr->Item[i].IsDgpu == 1)) {
                    CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func, 0x4C, NewSsid);
                    break;
                  }
                }
              }
              AmdCpmRestoreGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
            }
          }
        }
      case 1:
        if (Ssid != 0xFFFF0000) {
          iSsid = (UINT16) (Ssid >> 16);
          for (Index = 0; Index < AMD_DISPLAY_DEVICE_PATH_SIZE; Index++) {
            if (DevicePathTablePtr->Path[Index].FeatureMask.Raw == 0xFFFFFFFF || DevicePathTablePtr->Path[Index].FeatureMask.Mask.Valid == 0) {
              break;
            }
            if (DevicePathTablePtr->Path[Index].FeatureMask.Mask.Exist && DevicePathTablePtr->Path[Index].IsDgpu) {
              AmdCpmSaveGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
              AmdCpmProgramGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index);
              Bus       = (UINT8) DevicePathTablePtr->Path[Index].FeatureMask.Mask.Bus;
              Dev       = DevicePathTablePtr->Path[Index].Device.Device;
              Func      = DevicePathTablePtr->Path[Index].Device.Function;
              DeviceId  = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x02);
              VendorId2 = CpmTableProtocolPtr->CommonFunction.PciRead16 (CpmTableProtocolPtr, Bus, Dev, Func, 0x2C);
              RevId     = CpmTableProtocolPtr->CommonFunction.PciRead8 (CpmTableProtocolPtr, Bus, Dev, Func, 0x08);
              if (RebrandDualGraphicsSsidTable2Ptr->Svid == 0 || RebrandDualGraphicsSsidTable2Ptr->Svid == 0xFFFF) {
                NewSsid   = Ssid | (UINT32)VendorId2;
              } else {
                NewSsid   = Ssid | (UINT32)RebrandDualGraphicsSsidTable2Ptr->Svid;
              }

              for (i = 0; i < AMD_REBRAND_DUAL_GRAPHICS_SSID_DEVICE_SIZE; i++) {
                if (RebrandDualGraphicsSsidTable2Ptr->Item[i].dDeviceId == 0xFFFF) {
                  break;
                } else {
                  if ((RebrandDualGraphicsSsidTable2Ptr->Item[i].dRevId == RevId) &&
                      (RebrandDualGraphicsSsidTable2Ptr->Item[i].iSsid == iSsid) &&
                      (RebrandDualGraphicsSsidTable2Ptr->Item[i].dDeviceId == DeviceId)) {
                    CpmTableProtocolPtr->CommonFunction.PciWrite32 (CpmTableProtocolPtr, Bus, Dev, Func, 0x4C, NewSsid);
                    break;
                  }
                }
              }
              AmdCpmRestoreGfxResource (DisplayFeatureDataPtr, CpmTableProtocolPtr, Index, &RootBridgeData, &UpStBridgeData, &DnStBridgeData, &DevicePciData);
            }
          }
        }
      }
    }
  }
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * The function to set GPIO for display output
 *
 * @param[in]     DispatchHandle  The handle of this callback, obtained when registering
 * @param[in]     DispatchContext Pointer to the EFI_SMM_SW_DISPATCH_CONTEXT
 *
 * @retval        EFI_SUCCESS     Callback function successfully
 * @retval        EFI_ERROR       Callback function failed (see error for more details)
 */
EFI_STATUS
EFIAPI
AmdCpmSetGpuDisplayOutputSmm (
  IN        EFI_HANDLE                      DispatchHandle,
  IN        CPM_SMM_SW_DISPATCH_CONTEXT     *DispatchContext
  )
{
  CPM_DISPLAY_FEATURE_PRIVATE   *DisplayFeatureDataPtr;
  AMD_CPM_MAIN_TABLE            *MainTablePtr;
  AMD_CPM_DEVICE_PATH_TABLE     *DevicePathTablePtr;
  AMD_CPM_GPIO_DEVICE_POWER_TABLE *GpioDevicePowerTablePtr;
  AMD_CPM_TABLE_PROTOCOL        *CpmTableProtocolPtr;
  UINT8                         i;
  UINT8                         GpioDeviceId;
  UINT8                         DeviceId;
  UINT8                         Mode;
  UINT8                         Index;
  UINT32                        IsDgpuPrimary;

  DisplayFeatureDataPtr   = &gCpmDisplayFeatureSmmProtocol->DisplayFeatureData;
  CpmTableProtocolPtr     = gCpmDisplayFeatureSmmProtocol->TableProtocolSmmPtr;
  MainTablePtr            = CpmTableProtocolPtr->MainTablePtr;
  IsDgpuPrimary           = MainTablePtr->DisplayFeature.Config.IsDgpuPrimary;
  DevicePathTablePtr      = DisplayFeatureDataPtr->DevicePathTablePtr;
  GpioDevicePowerTablePtr = CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_GPIO_DEVICE_POWER);

  if (GpioDevicePowerTablePtr && DevicePathTablePtr) {
    for (i = 0; i < AMD_DISPLAY_DEVICE_PATH_SIZE; i++) {
      if (!DevicePathTablePtr->Path[i].FeatureMask.Mask.Valid) {
        break;
      }
      if (DevicePathTablePtr->Path[i].FeatureMask.Mask.Exist == 1) {
        if (DevicePathTablePtr->Path[i].IsDgpu == IsDgpuPrimary) {
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
                CpmTableProtocolPtr->CommonFunction.SetGpio ( CpmTableProtocolPtr,
                                                              GpioDevicePowerTablePtr->DevicePowerList[Index].Config.SetGpio.Pin,
                                                              GpioDevicePowerTablePtr->DevicePowerList[Index].Config.SetGpio.Value );
              }
            }
          }
          break;
        }
      }
    }
  }
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * SMI Handler to restore display feature
 *
 * This function disables audio in dGPU when PowerXpress is enabled and sets SSID
 * when resume from S3.
 *
 */

EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmDisplayFeatureRestoreSmm,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SW_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  )
{
  AmdCpmDisableDgpuAudioInPXSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  AmdCpmEnableDgpuSmbusInPXSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  AmdCpmSetGpuSsidSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  AmdCpmSetGpuDisplayOutputSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * SMI Handler to Disable Dgpu Audio
 *
 * This function disables audio in dGPU when PX/HG is enabled
 *
 */

EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmDisableDgpuAudioSwSmiSmm,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SW_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  )
{
  AmdCpmDisableDgpuAudioInPXSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  AmdCpmSetGpuSsidSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * SMI Handler to Set Auto Uma Mode
 *
 * This function Set Auto Uma Mode when ATCS Function 7 is issued by driver
 *
 */

EFI_STATUS
EFIAPI
CPM_DEFINE_CALLBACK (
  IN      CPM_CALLBACK_NAME     AmdCpmDisplayFeatureSetAutoUmaModeCallBackSmm,
  IN      CPM_CALLBACK_VAR_TYPE EFI_HANDLE,
  IN      CPM_CALLBACK_VAR_NAME DispatchHandle,
  IN      CPM_CALLBACK_VAR_TYPE CPM_SMM_SW_DISPATCH_CONTEXT,
  IN      CPM_CALLBACK_VAR_NAME *DispatchContext
  )
{
  AmdCpmDisplayFeatureSetAutoUmaModeSmm (DispatchHandle, (CPM_SMM_SW_DISPATCH_CONTEXT*)DispatchContext);
  return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * AMD CPM Display Feature SMM Register Center
 *
 * This function registers the SMI handler to disable audio in dGPU when PowerXpress is enabled
 * and set SSID when resume from S3.
 *
 * @retval        EFI_SUCCESS    Function initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */


EFI_STATUS
AmdCpmDisplayFeatureSmmRegistrationCenter (
  VOID
  )
{
  EFI_STATUS                          Status;
  CPM_SMM_SW_DISPATCH_PROTOCOL        *SwDispatch;
  CPM_SMM_SW_DISPATCH_CONTEXT         SwContext;
  EFI_HANDLE                          SwHandle;
  AMD_CPM_TABLE_PROTOCOL              *CpmTableProtocolPtr;
  AMD_CPM_MAIN_TABLE                  *MainTablePtr;
  UINT8                               CpuRevisionId;

  CpmTableProtocolPtr = gCpmDisplayFeatureSmmProtocol->TableProtocolSmmPtr;
  MainTablePtr        = CpmTableProtocolPtr->MainTablePtr;
  CpuRevisionId       = MainTablePtr->CpmCpuRevisionId;

  mDgpuSsid      = PcdGet32 (PcdCpmDgpuSsid);
  mDgpuAudioSsid = PcdGet32 (PcdCpmDgpuAudioSsid);

  //
  //  Locate SMM SW dispatch protocol
  //
  Status = CpmSmmLocateProtocol ( &gCpmSmmSwDispatchProtocolGuid,
                                  NULL,
                                  (VOID**)&SwDispatch );
  ASSERT_EFI_ERROR (Status);

  SwContext.SwSmiInputValue = CFG_CPM_ACPI_RESTORE_SW_SMI;
  Status = SwDispatch->Register ( SwDispatch,
                                  AmdCpmDisplayFeatureRestoreSmm,
                                  &SwContext,
                                  &SwHandle );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SwContext.SwSmiInputValue = CFG_CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI;
  Status = SwDispatch->Register ( SwDispatch,
                                  AmdCpmDisableDgpuAudioSwSmiSmm,
                                  &SwContext,
                                  &SwHandle );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (CpuRevisionId > CPM_CPU_REVISION_ID_ZP) {
    SwContext.SwSmiInputValue = CFG_CPM_SWSMICMD_SETAUTOUMAMODE;
    Status = SwDispatch->Register ( SwDispatch,
                                    AmdCpmDisplayFeatureSetAutoUmaModeCallBackSmm,
                                    &SwContext,
                                    &SwHandle );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } // End of if (CpuRevisionId > CPM_CPU_REVISION_ID_ZP)

  return EFI_SUCCESS;
}
