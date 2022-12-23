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

#include <AmdCpmBase.h>
#include <OptionCpuInstall.h>
#include CPM_PPI_DEFINITION (AmdCpmTablePpi)

#define PT_XHCI_ID_A 0x43B91022
#define PT_XHCI_ID_B 0x43BA1022
#define PT_XHCI_ID_C 0x43BB1022
#define PT_XHCI_ID_D 0x43BC1022

CPU_REVISION_ITEM *CpuRevisionTable[] = {
  OPTION_CPM_CPU_REVISION_ID_ON
  OPTION_CPM_CPU_REVISION_ID_TN
  OPTION_CPM_CPU_REVISION_ID_KV
  OPTION_CPM_CPU_REVISION_ID_KB
  OPTION_CPM_CPU_REVISION_ID_ML
  OPTION_CPM_CPU_REVISION_ID_CZ
  OPTION_CPM_CPU_REVISION_ID_NL
  OPTION_CPM_CPU_REVISION_ID_AM
  OPTION_CPM_CPU_REVISION_ID_ST
  OPTION_CPM_CPU_REVISION_ID_BR
  OPTION_CPM_CPU_REVISION_ID_ZP
  OPTION_CPM_CPU_REVISION_ID_RV
  OPTION_CPM_CPU_REVISION_ID_RV2
  OPTION_CPM_CPU_REVISION_ID_SSP
  OPTION_CPM_CPU_REVISION_ID_MTS
  NULL
};

PCIE_BRIDGE_NAME *PcieBridgeName[] = {
  OPTION_CPM_PCIE_BRIDGE_NAME_ON
  OPTION_CPM_PCIE_BRIDGE_NAME_TN
  OPTION_CPM_PCIE_BRIDGE_NAME_KV
  OPTION_CPM_PCIE_BRIDGE_NAME_KB
  OPTION_CPM_PCIE_BRIDGE_NAME_ML
  OPTION_CPM_PCIE_BRIDGE_NAME_CZ
  OPTION_CPM_PCIE_BRIDGE_NAME_NL
  OPTION_CPM_PCIE_BRIDGE_NAME_AM
  OPTION_CPM_PCIE_BRIDGE_NAME_ST
  OPTION_CPM_PCIE_BRIDGE_NAME_BR
  OPTION_CPM_PCIE_BRIDGE_NAME_ZP
  OPTION_CPM_PCIE_BRIDGE_NAME_RV
  OPTION_CPM_PCIE_BRIDGE_NAME_RV2
  OPTION_CPM_PCIE_BRIDGE_NAME_SSP
  OPTION_CPM_PCIE_BRIDGE_NAME_MTS
  NULL
};

UINT8 AmdCpmSsdtSupport = AMD_CPM_SSDT_SUPPORT;


/*---------------------------------------------------------------------------------------*/
/**
 * Check RV OPN number
 *
 * @retval    TRUE    This is RV B4 part
 *            FALSE   This is not RV B4 part
 *
 */
BOOLEAN
CpmCheckRvOpnB4 (
  IN       VOID                        *This
  )
{
  UINT32              TempData32;

  TempData32 =  (PcdGet32 (PcdGetRVFamilyOPN) >> 30) & 0x3;

  if (TempData32 == 2) {
    return TRUE;
  } else if (TempData32 == 3) {
    return TRUE;
  }
  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get SBI (Sideband Interface) Address in PCI MMIO Base
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    SBI Address
 *
 */
UINT32
CpmGetSbTsiAddr (
  IN       VOID                        *This
  )
{
  AMD_CPM_MAIN_TABLE  *MainTablePtr;
  MainTablePtr = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  return (MainTablePtr->PcieMemIoBaseAddr + 0x000C31E8);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check whether thermal function is enabled in current CPU or APU
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    TRUE    Both of ThermtpEn and HtcCapable are enabled
 *            FALSE   Either of ThermtpEn or HtcCapable is not enabled
 *
 */
BOOLEAN
CpmIsThermalSupport (
  IN       VOID                        *This
  )
{
  AMD_CPM_TABLE_PPI   *CpmTablePpiPtr = This;
  UINT32              ThermtpEn;
  UINT32              HtcCapable;

  ThermtpEn   = CpmTablePpiPtr->CommonFunction.PciRead32 (CpmTablePpiPtr, 0, 0x18, 3, 0xE4) & BIT5;      // D18F3xE4 Thermtrip Status [5]: ThermtpEn
  HtcCapable  = CpmTablePpiPtr->CommonFunction.PciRead32 (CpmTablePpiPtr, 0, 0x18, 3, 0xE8) & BIT10;     // D18F3xE8 Northbridge Capabilities [10]: HtcCapable

  return (BOOLEAN) ((ThermtpEn != 0) && (HtcCapable != 0));
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check whether thermal function is enabled in current CPU or APU
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    The CPU Revision Item for current platform
 *
 */
CPU_REVISION_ITEM*
CpmGetCpuRevisionItem (
  IN       VOID           *This
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  CPU_REVISION_ITEM       **CpuRevisionPtr;
  CPU_REVISION_ITEM       *CpuRevisionItemPtr;
  CPU_REVISION_ITEM       *Item;
  UINT32                  Value;
  UINT32                  ApuSupportMask;

  ApuSupportMask = PcdGet32 (ApuSupportMask);
  CommonFunctionPtr = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;

  CpuRevisionPtr = &CpuRevisionTable[0];
  CommonFunctionPtr->CpuidRead(This, &Value, NULL);             // AMD_CPUID_FMF
  if ((Value & 0x0FFF0F00) == 0x00810F00) {                     // CPM_CPU_REVISION_ID_RV
    if (CpmCheckRvOpnB4(This)) {
      Value = 0x00820F00;                                       // Treat it as RV2
    }
  }
  Item = 0;
  while (*CpuRevisionPtr && !Item) {
    CpuRevisionItemPtr = *CpuRevisionPtr;
    while (CpuRevisionItemPtr->Mask) {
      if (!(ApuSupportMask & (1 << CpuRevisionItemPtr->CpuRevision))) {
        break;
      }
      if ((CpuRevisionItemPtr->Mask & Value) == CpuRevisionItemPtr->Value) {
        Item = CpuRevisionItemPtr;
        break;
      }
      CpuRevisionItemPtr ++;
    }
    CpuRevisionPtr ++;
  }
  return Item;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get Current PCIe Bridge Name Table
 *
 *
 * @param[in] This    The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    The PCIe Bridge Name Table
 *
 */
PCIE_BRIDGE_NAME*
CpmGetPcieBridgeNameTable (
  IN       VOID           *This
  )
{
  PCIE_BRIDGE_NAME **PcieNameTablePtr;
  PCIE_BRIDGE_NAME *PcieNameItemPtr;
  CPU_REVISION_ITEM *ItemPtr;
  UINT8 PcieBridgeType;
  PcieBridgeType = 0;
  ItemPtr = CpmGetCpuRevisionItem (This);
  if (ItemPtr) {
    PcieBridgeType = ItemPtr->PcieRevision;
  }

  PcieNameTablePtr = &PcieBridgeName[0];
  PcieNameItemPtr = 0;
  while (*PcieNameTablePtr) {
    if ((*PcieNameTablePtr)->PcieRevision == PcieBridgeType) {
      PcieNameItemPtr = *PcieNameTablePtr;
      break;
    }
    PcieNameTablePtr ++;
  }
  return PcieNameItemPtr;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get Promontory Pcie Bridge Device/Function Address
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval              The Promontory Pcie Bridge Device/Function Address
 * @retval    0x0       The is no Promontory
 *
 */
UINT32
CpmGetPtBrDevAddr (
  IN       VOID                       *This
  )
{
  AMD_CPM_TABLE_PPI   *CpmTablePpiPtr = This;
  PCIE_BRIDGE_NAME    *BridgeNamePtr;
  UINT32              DeviceID;
  UINT32              BridgeAddress;

  DeviceID = 0;
  BridgeAddress = 0;
  BridgeNamePtr = CpmGetPcieBridgeNameTable (This);
  while (BridgeNamePtr->Device != 0) {
    DeviceID = CpmTablePpiPtr->CommonFunction.GetPcieEndPointDeviceID (CpmTablePpiPtr, BridgeNamePtr->Device, BridgeNamePtr->Function);
    if (DeviceID == PT_XHCI_ID_A || DeviceID == PT_XHCI_ID_B || DeviceID == PT_XHCI_ID_C || DeviceID == PT_XHCI_ID_D) {
      BridgeAddress = CpmTablePpiPtr->MainTablePtr->PcieMemIoBaseAddr + (BridgeNamePtr->Device << 15) + (BridgeNamePtr->Function << 12);
      return BridgeAddress;
    }
    BridgeNamePtr ++;
  }
  return BridgeAddress;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get PCIe Bridge Name in ASL code
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 * @param[in] Device    The PCI Device Number of PCIe Bridge
 * @param[in] Function  The PCI Function Number of PCIe Bridge
 *
 * @retval    The PCIe Bridge Name in ASL code
 *
 */
UINT32
CpmGetPcieAslName (
  IN       VOID                       *This,
  IN       UINT8                      Device,
  IN       UINT8                      Function
  )
{
  PCIE_BRIDGE_NAME  *BridgeNamePtr;
  UINT32  Name;

  Name = 0;
  BridgeNamePtr = CpmGetPcieBridgeNameTable (This);
  while (BridgeNamePtr->Device != 0) {
    if (BridgeNamePtr->Device == Device && BridgeNamePtr->Function == Function) {
      switch (BridgeNamePtr->NameId) {
      case 0x10:
        Name = PcdGet32 (PcieGfx0AslName);
        break;
      case 0x11:
        Name = PcdGet32 (PcieGfx1AslName);
        break;
      case 0x12:
        Name = PcdGet32 (PcieGfx2AslName);
        break;
      case 0x13:
        Name = PcdGet32 (PcieGfx3AslName);
        break;
      case 0x14:
        Name = PcdGet32 (PcieGfx4AslName);
        break;
      case 0x20:
        Name = PcdGet32 (PcieGpp0AslName);
        break;
      case 0x21:
        Name = PcdGet32 (PcieGpp1AslName);
        break;
      case 0x22:
        Name = PcdGet32 (PcieGpp2AslName);
        break;
      case 0x23:
        Name = PcdGet32 (PcieGpp3AslName);
        break;
      case 0x24:
        Name = PcdGet32 (PcieGpp4AslName);
        break;
      case 0x25:
        Name = PcdGet32 (PcieGpp5AslName);
        break;
      case 0x26:
        Name = PcdGet32 (PcieGpp6AslName);
        break;
      case 0x27:
        Name = PcdGet32 (PcieGpp7AslName);
        break;
      case 0x28:
        Name = PcdGet32 (PcieGpp8AslName);
        break;
      case 0x29:
        Name = PcdGet32 (PcieGpp9AslName);
        break;
      case 0x2A:
        Name = PcdGet32 (PcieGppAAslName);
        break;
      case 0x2B:
        Name = PcdGet32 (PcieGppBAslName);
        break;
      case 0x2C:
        Name = PcdGet32 (PcieGppCAslName);
        break;
      case 0x2D:
        Name = PcdGet32 (PcieGppDAslName);
        break;
      case 0x2E:
        Name = PcdGet32 (PcieGppEAslName);
        break;
      case 0x2F:
        Name = PcdGet32 (PcieGppFAslName);
        break;
      case 0x30:
        Name = PcdGet32 (PcieGp17AslName);
        break;
      case 0x31:
        Name = PcdGet32 (PcieGp18AslName);
        break;
      case 0x32:
        Name = PcdGet32 (PcieGp28AslName);
        break;
      case 0x33:
        Name = PcdGet32 (PcieGp38AslName);
        break;
      case 0x40:
        Name = PcdGet32 (PcieGppGAslName);
        break;
      case 0x41:
        Name = PcdGet32 (PcieGppHAslName);
        break;
      }
      if (!Name) {
        Name = BridgeNamePtr->Name;
      }
      break;
    }
    BridgeNamePtr ++;
  }
  return Name;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get CPU Revision Id
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 *
 * @retval    The CPU Revision Id
 *
 */
UINT8
CpmGetCpuRevisionId (
  IN       VOID                       *This
  )
{
  CPU_REVISION_ITEM *ItemPtr;
  UINT8             Revision;

  Revision = 0xFF;
  ItemPtr = CpmGetCpuRevisionItem (This);
  if (ItemPtr) {
    Revision = ItemPtr->CpuRevision;
  }

  return Revision;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Register CPM Common CPU Function
 *
 *
 * @param[in] This      The pointer of AMD CPM Table Ppi or Protocol
 *
 */
VOID
EFIAPI
CpmRegisterCpu (
  IN       VOID                        *This
  )
{
  AMD_CPM_COMMON_FUNCTION *CommonFunctionPtr;
  AMD_CPM_MAIN_TABLE      *MainTablePtr;
  UINT64                  Value;
  MainTablePtr = ((AMD_CPM_TABLE_PPI*)This)->MainTablePtr;
  CommonFunctionPtr = &((AMD_CPM_TABLE_PPI*)This)->CommonFunction;
  if (!MainTablePtr->PcieMemIoBaseAddr) {
    Value = CommonFunctionPtr->MsrRead (0xC0010058);
    MainTablePtr->PcieMemIoBaseAddr = (UINT32) (Value & 0xFFF00000);
  }
  CommonFunctionPtr->GetCpuRevisionId = CpmGetCpuRevisionId;
  if (!MainTablePtr->CpmCpuRevisionId) {
    MainTablePtr->CpmCpuRevisionId = CommonFunctionPtr->GetCpuRevisionId (This);
    DEBUG((DEBUG_INFO, "  LIB-CPU-%a-CpmCpuRevisionId = 0x%02X\n", __FUNCTION__, MainTablePtr->CpmCpuRevisionId));
  }
  CommonFunctionPtr->GetSbTsiAddr     = CpmGetSbTsiAddr;
  CommonFunctionPtr->IsThermalSupport = CpmIsThermalSupport;
  CommonFunctionPtr->GetPcieAslName   = CpmGetPcieAslName;
  CommonFunctionPtr->GetPtBrDevAddr   = CpmGetPtBrDevAddr;
  return;
}
