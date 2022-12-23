/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric MMIO initialization based on NV variable for DF1
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 *******************************************************************************
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "AMD.h"
#include "Filecode.h"
#include <FabricRegistersZP.h>
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Protocol/FabricResourceManagerServicesProtocol.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include <Library/FabricResourceSizeForEachRbLib.h>
#include "FabricResourceManager1.h"

#define FILECODE LIBRARY_FABRICRESOURCEMANAGERDF1LIB_FABRICRESOURCEINITBASEDONNV1_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
UINT32 mOverSizeBelowPcieMin = 0xFFFFFFFF;
UINT32 mAlignmentMask = 0;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
BOOLEAN
ArrangeMmioBelow4G (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN       UINT64                         MmioBaseAddrAbovePcieCfg,
  IN       UINT64                         MmioLimitAbovePcieCfg,
  IN       UINT64                         MmioBaseAddrBelowPcieCfg,
  IN       UINT64                         MmioLimitBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbNumberPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  );

BOOLEAN
GetNextCombination (
  IN       UINT8                          NumberOfRbBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbNumberPerSocket
  );

BOOLEAN
TryThisCombination (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN       UINT64                         MmioBaseAddrAbovePcieCfg,
  IN       UINT64                         MmioLimitAbovePcieCfg,
  IN       UINT64                         MmioBaseAddrBelowPcieCfg,
  IN       UINT64                         MmioLimitBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbNumberPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitPciBusBasedOnNvVariable1
 *
 * Initialize PCI bus base/limit for each Root Bridge based on NV variable.
 *
 * @param[in]         PciBusRangeForEachRb     How much PCI bus is required for each Root Bridge
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbsPerSocket             Root Bridge number per socket
 *
 */
EFI_STATUS
FabricInitPciBusBasedOnNvVariable1 (
  IN       FABRIC_RESOURCE_FOR_EACH_RB  *PciBusRangeForEachRb,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbsPerSocket
  )
{
  UINTN             SktLoop;
  UINTN             DieLoop;
  UINTN             RbLoop;
  UINTN             DiePerSkt;
  UINT8             RegIndex;
  UINT16            PciBusBase;
  UINT16            PciBusLimit;
  UINTN             PrimarySocket;
  UINTN             PrimaryRootBridge;
  UINTN             PciBase;
  UINTN             PciLimit;
  BOOLEAN           NeedReallocate;
  CFG_ADDRESS_CTRL_REGISTER         CfgAddrCtrl;

  // Check if we need to re-allocate PCI bus base/limit
  NeedReallocate = FALSE;
  for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
    for (RbLoop = 0; RbLoop < RbsPerSocket; RbLoop++) {
      PciBase = FabricTopologyGetHostBridgeBusBase (SktLoop, RbLoop, 0);
      PciLimit = FabricTopologyGetHostBridgeBusLimit (SktLoop, RbLoop, 0);
      if (PciLimit == 0xFF) {
        // skip checking PCI bus number for the last root bridge in system
        continue;
      }

      if ((PciLimit - PciBase + 1) != PciBusRangeForEachRb->PciBusNumber[SktLoop][RbLoop]) {
        NeedReallocate = TRUE;
        break;
      }
    }
  }

  if (NeedReallocate) {

    // Clear all Configuration Address Map registers (up to 8)
    IDS_HDT_CONSOLE (CPU_TRACE, "  Init PCI bus base/limit based on NV variable\n");
    for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
      DiePerSkt = FabricTopologyGetNumberOfDiesOnSocket (SktLoop);
      for (DieLoop = 0; DieLoop < DiePerSkt; DieLoop++) {
        for (RegIndex = 0; RegIndex < 8; RegIndex++) {
          FabricRegisterAccWrite (SktLoop, DieLoop, 0x0, (CFG_ADDR_MAP_REG0  + RegIndex * 4), FABRIC_REG_ACC_BC, 0, TRUE);
        }
        FabricRegisterAccWrite (SktLoop, DieLoop, 0x0, CFGADDRESSCTRL_REG, FABRIC_REG_ACC_BC, 0, TRUE);
      }
    }

    // Set Configuration Address Map registers
    PrimarySocket = 0;
    PrimaryRootBridge = 0;

    RegIndex = 0;
    PciBusBase = 0;
    PciBusLimit = (UINT16) (PciBusBase + PciBusRangeForEachRb->PciBusNumber[PrimarySocket][PrimaryRootBridge] - 1);
    FabricSetCfgAddrMapReg1 (SocketNumber, RbsPerSocket, RegIndex, PrimarySocket, PrimaryRootBridge, PciBusBase, PciBusLimit);
    CfgAddrCtrl.Value = 0;
    CfgAddrCtrl.Field.SecBusNum = PciBusBase;
    FabricRegisterAccWrite (PrimarySocket, PrimaryRootBridge, 0, CFGADDRESSCTRL_REG, FABRIC_REG_ACC_BC, CfgAddrCtrl.Value, TRUE);

    for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
      for (RbLoop = 0; RbLoop < RbsPerSocket; RbLoop++) {
        if ((SktLoop == PrimarySocket) && (RbLoop == PrimaryRootBridge)) {
          continue;
        }
        RegIndex++;
        PciBusBase = PciBusLimit + 1;
        if ((SktLoop == (UINTN) (SocketNumber - 1)) && (RbLoop == (UINTN) (RbsPerSocket - 1))) {
          PciBusLimit = 0xFF;
        } else {
          PciBusLimit = (UINT16) (PciBusBase + PciBusRangeForEachRb->PciBusNumber[SktLoop][RbLoop] - 1);
        }
        FabricSetCfgAddrMapReg1 (SocketNumber, RbsPerSocket, RegIndex, SktLoop, RbLoop, PciBusBase, PciBusLimit);
        CfgAddrCtrl.Value = 0;
        CfgAddrCtrl.Field.SecBusNum = PciBusBase;
        FabricRegisterAccWrite (SktLoop, RbLoop, 0, CFGADDRESSCTRL_REG, FABRIC_REG_ACC_BC, CfgAddrCtrl.Value, TRUE);
      }
    }
  }

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitIoBasedOnNvVariable1
 *
 * Initialize IO registers for each RB based on NV variable.
 *
 * @param[in, out]    FabricIoManager          Point to FABRIC_IO_MANAGER
 * @param[in]         IoSizeForEachRb          How much IO size is required for each RB
 * @param[in, out]    SpaceStaus               Current status
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbNumberPerSocket        Rb number per socket
 * @param[in]         SetDfRegisters           TRUE  - Set DF MMIO registers
 *                                             FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 */
EFI_STATUS
FabricInitIoBasedOnNvVariable1 (
  IN       FABRIC_IO_MANAGER   *FabricIoManager,
  IN       FABRIC_RESOURCE_FOR_EACH_RB *IoSizeForEachRb,
  IN       FABRIC_ADDR_SPACE_SIZE       *SpaceStatus,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbNumberPerSocket,
  IN       BOOLEAN              SetDfRegisters
  )
{
  UINT8             i;
  UINT8             j;
  UINT8             RegIndex;
  UINT8             DstFabricIDSysOffset;
  UINT32            IoBase;
  UINT32            IoSize;
  UINT32            LegacyIoSize;

  IoBase = 0;
  RegIndex = 0;
  LegacyIoSize = X86_LEGACY_IO_SIZE;
  IDS_HDT_CONSOLE (CPU_TRACE, "    reserve 0x%X IO size for legacy devices\n", LegacyIoSize);

  for (i = 0; i < SocketNumber; i++) {
    for (j = 0; j < RbNumberPerSocket; j++) {
      if (SpaceStatus != NULL) {
        SpaceStatus->IoSize += (UINT32) IoSizeForEachRb->IO[i][j].Size;
      }

      DstFabricIDSysOffset = (UINT8) FabricTopologyGetDieSystemOffset (i, j);
      if ((i == (SocketNumber - 1)) && (j == (RbNumberPerSocket - 1))) {
        // 1. first, check if it's the last RB. DF's IO space is up to 25 bits, so set limit to 0x1FFFFFF for last RB
        IoSize = DF_IO_LIMIT - IoBase;
      } else if ((i == 0) && (j == 0)) {
        // 2. second, if it's primary RB and it's not the last RB, plus size with LegacyIoSize
        IoSize = (UINT32) IoSizeForEachRb->IO[i][j].Size + LegacyIoSize;
      } else {
        IoSize = (UINT32) IoSizeForEachRb->IO[i][j].Size;
      }

      if (IoSize == 0) {
        continue;
      }

      if ((FabricIoManager != NULL) && SetDfRegisters) {
        FabricSetIoReg1 (SocketNumber, RbNumberPerSocket, RegIndex, DstFabricIDSysOffset, IoBase, IoSize);

        if ((i == 0) && (j == 0)) {
          FabricIoManager->IoRegion[i][j].IoBase = IoBase + LegacyIoSize;
          FabricIoManager->IoRegion[i][j].IoSize = IoSize - LegacyIoSize;
        } else {
          FabricIoManager->IoRegion[i][j].IoBase = IoBase;
          FabricIoManager->IoRegion[i][j].IoSize = IoSize;
        }

        FabricIoManager->IoRegion[i][j].IoUsed = 0;

        // When report to X86, IO region should be IoBase ~ X86IO_LIMIT since X86 only support 16 bits IO space
        if ((i == (SocketNumber - 1)) && (j == (RbNumberPerSocket - 1))) {
          FabricIoManager->IoRegion[i][j].IoSize = X86IO_LIMIT - FabricIoManager->IoRegion[i][j].IoBase;
        }

        IDS_HDT_CONSOLE (CPU_TRACE, "  Socket%x RB%x has IO base 0x%X size 0x%X\n", i, j, FabricIoManager->IoRegion[i][j].IoBase, FabricIoManager->IoRegion[i][j].IoSize);
      }

      ASSERT (IoBase <= X86IO_LIMIT);

      IoBase += IoSize;
      RegIndex++;
    }
  }

  if (SpaceStatus != NULL) {
    if (SpaceStatus->IoSize > X86IO_LIMIT) {
      SpaceStatus->IoSizeReqInc = SpaceStatus->IoSize - X86IO_LIMIT;
    } else {
      SpaceStatus->IoSizeReqInc = 0;
    }
    IDS_HDT_CONSOLE (CPU_TRACE, "  Space Status: IoSize %X, IoSizeReqInc %X\n", SpaceStatus->IoSize, SpaceStatus->IoSizeReqInc);
  }

  if (FabricIoManager != NULL) {
    FabricIoManager->GlobalCtrl = TRUE;
  }

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitMmioBasedOnNvVariable1
 *
 * Initialize MMIO registers for each RB based on NV variable.
 *
 * @param[in, out]    FabricMmioManager        Point to FABRIC_MMIO_MANAGER
 * @param[in]         MmioSizeForEachRb        How much MMIO size is required for each RB
 * @param[in, out]    SpaceStaus               Current status
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbNumberPerSocket        RB number per socket
 * @param[in]         SetDfRegisters           TRUE  - Set DF MMIO registers
 *                                             FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 */
EFI_STATUS
FabricInitMmioBasedOnNvVariable1 (
  IN       FABRIC_MMIO_MANAGER *FabricMmioManager,
  IN       FABRIC_RESOURCE_FOR_EACH_RB *MmioSizeForEachRb,
  IN       FABRIC_ADDR_SPACE_SIZE       *SpaceStatus,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbNumberPerSocket,
  IN       BOOLEAN              SetDfRegisters
  )
{
  UINT8  i;
  UINT8  j;
  UINT8  DstFabricIDSysOffset;
  UINT64 MmioLimitAbove4G;
  UINT64 MmioBaseAddr;
  UINT64 MmioBaseAddrNextRb;
  UINT64 MmioBaseAddrPrefetchable;
  UINT64 MmioBaseAddrNonPrefetchable;
  UINT64 SizePrefetchable;
  UINT64 SizeNonPrefetchable;
  UINT64 MmioBaseAddrAbovePcieCfg;
  UINT64 MmioBaseAddrBelowPcieCfg;
  UINT64 MmioLimitAbovePcieCfg;
  UINT64 MmioLimitBelowPcieCfg;
  UINT64 TOM;
  UINT64 TOM2;
  UINT64 PciCfgSpace;
  UINT64 AlignMask;
  UINT64 AlignMaskP;
  UINT64 MmioSizeBelowHole;
  UINT64 MmioSizeAboveHole;
  EFI_STATUS Status;
  BOOLEAN MmioIsAbovePcieCfg[MAX_SOCKETS_SUPPORTED * MAX_DIES_PER_SOCKET];
  BOOLEAN EnoughSpaceAbove4G;
  BOOLEAN LargeAlignFirst;
  BOOLEAN LastCombinationWork;

  Status = EFI_SUCCESS;

  // If MmioSizeForEachRb is not NULL, we should record current space status
  // Init global variable
  if (SpaceStatus != NULL) {
    mOverSizeBelowPcieMin = 0xFFFFFFFF;
    mAlignmentMask = 0;
  }

  // System information
  PciCfgSpace = (AsmReadMsr64 (0xC0010058) >> 2) & 0xF;                   // Get bus range from MSR_C001_0058[5:2][BusRange]
  PciCfgSpace = MultU64x64 (((UINT64) 1 << PciCfgSpace), (1024 * 1024));  // The size of configuration space is 1MB times the number of buses
  TOM = AsmReadMsr64 (0xC001001A);
  TOM2 = AsmReadMsr64 (0xC001001D);
  IDS_HDT_CONSOLE (CPU_TRACE, "  TOM: %lX, TOM2: %lX, Pcie configuration space: %lX ~ %lX\n", TOM, TOM2, PcdGet64 (PcdPciExpressBaseAddress), (PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace));

  ASSERT (PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb) >= (PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace));
  ASSERT (PcdGet64 (PcdPciExpressBaseAddress) >= TOM);

  // Calculate size of above 4G
  MmioBaseAddrNextRb = (TOM2 > 0x100000000)? TOM2 : 0x100000000; // Check if TOM2 > 4G
  MmioLimitAbove4G = 0x7FD00000000; // SMEE wold be enabled as default, so set limit to 0x7FD00000000

  if (PcdGet64 (PcdAmdMmioAbove4GLimit)  < MmioLimitAbove4G) {
    MmioLimitAbove4G = (PcdGet64 (PcdAmdMmioAbove4GLimit) + 1) & 0xFFFFFFFFFFFF0000;
    if (MmioLimitAbove4G <= MmioBaseAddrNextRb) {
      MmioLimitAbove4G = MmioBaseAddrNextRb;
    }
  }

  // there's a hole at 0xFD_0000_0000 ~ 0x100_0000_0000
  MmioSizeBelowHole = 0;
  MmioSizeAboveHole = 0;

  // calculate Mmio size below/above this hole
  if (MmioBaseAddrNextRb < 0xFD00000000) {
    MmioSizeBelowHole = (MmioLimitAbove4G < 0xFD00000000) ? MmioLimitAbove4G : 0xFD00000000;
    MmioSizeBelowHole = MmioSizeBelowHole - MmioBaseAddrNextRb;
  }

  if (MmioLimitAbove4G > 0x10000000000) {
    MmioSizeAboveHole = (MmioBaseAddrNextRb > 0x10000000000)? MmioBaseAddrNextRb : 0x10000000000;
    MmioSizeAboveHole = MmioLimitAbove4G - MmioSizeAboveHole;
  }

  if ((MmioSizeBelowHole == 0) && (MmioSizeAboveHole == 0)) {
    MmioLimitAbove4G = 0; // set limit to 0, so there's no MMIO space above 4G
    IDS_HDT_CONSOLE (CPU_TRACE, "    WARNING: There's no MMIO space above 4G\n");
  } else {
    if (MmioSizeAboveHole > MmioSizeBelowHole) {
      MmioBaseAddrNextRb = (TOM2 > 0x10000000000) ? TOM2 : 0x10000000000; // Check if TOM2 > 1T
    } else {
      MmioLimitAbove4G = (MmioLimitAbove4G < 0xFD00000000) ? MmioLimitAbove4G : 0xFD00000000;
    }
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "    Above 4G MMIO base is %lX, limit is %lX\n", MmioBaseAddrNextRb, MmioLimitAbove4G);

  LargeAlignFirst = TRUE;
  EnoughSpaceAbove4G = TRUE;
  for (i = 0; i < SocketNumber; i++) {
    for (j = 0; j < RbNumberPerSocket; j++) {
      // Calculate reqiured size, it's for output parameter 'SpaceStatus'
      if (SpaceStatus != NULL) {
        SpaceStatus->MmioSizeAbove4G += MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size;
        SpaceStatus->MmioSizeBelow4G += (UINT32) (MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[i][j].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[i][j].Size);
      }

      // If there's no MMIO request for above 4G, try next one
      if ((MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size + MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size) == 0) {
        continue;
      }

      AlignMask  = MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Alignment;
      AlignMaskP = MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Alignment;
      MmioBaseAddr = MmioBaseAddrNextRb;
      if ((LargeAlignFirst && (MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Alignment >= MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Alignment)) ||
          ((!LargeAlignFirst) && (MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Alignment <= MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Alignment))) {
        // Prefetchable -> Non Prefetchable
        MmioBaseAddrPrefetchable = (MmioBaseAddr + AlignMaskP) & (~AlignMaskP);
        MmioBaseAddrNonPrefetchable = (MmioBaseAddrPrefetchable + MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size + AlignMask) & (~AlignMask);
        SizePrefetchable = MmioBaseAddrNonPrefetchable - MmioBaseAddrPrefetchable;
        SizeNonPrefetchable = MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size;
        MmioBaseAddrNextRb = MmioBaseAddrNonPrefetchable + SizeNonPrefetchable;
      } else {
        // Non Prefetchable -> Prefetchable
        MmioBaseAddrNonPrefetchable = (MmioBaseAddr + AlignMask) & (~AlignMask);
        MmioBaseAddrPrefetchable = (MmioBaseAddrNonPrefetchable + MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size + AlignMaskP) & (~AlignMaskP);
        SizeNonPrefetchable = MmioBaseAddrPrefetchable - MmioBaseAddrNonPrefetchable;
        SizePrefetchable = MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size;
        MmioBaseAddrNextRb = MmioBaseAddrPrefetchable + SizePrefetchable;
      }
      LargeAlignFirst = !LargeAlignFirst;

      if (SizeNonPrefetchable == 0) {

        MmioBaseAddrNonPrefetchable = 0;
      }
      if (SizePrefetchable == 0) {

        MmioBaseAddrPrefetchable = 0;
      }

      // Check if space is enough
      if (MmioBaseAddrNextRb > MmioLimitAbove4G) {
        EnoughSpaceAbove4G = FALSE;
        IDS_HDT_CONSOLE (CPU_TRACE, "  No enough size above 4G\n");
        Status = EFI_OUT_OF_RESOURCES;
      }

      if (SetDfRegisters && EnoughSpaceAbove4G && (FabricMmioManager != NULL)) {
        //   Set MMIO above 4G
        if ((MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size == 0) &&
            (MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size == 0)) {
          continue;
        }

        IDS_HDT_CONSOLE (CPU_TRACE, "  User Request above 4G: Socket%x RB%x Prefetch MMIO Size %lX, AlignBit %X\n", i, j, MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size, MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Alignment);
        IDS_HDT_CONSOLE (CPU_TRACE, "                           Non Prefetch MMIO Size %lX, AlignBit %X\n", MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size, MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Alignment);
        DstFabricIDSysOffset = (UINT8) FabricTopologyGetDieSystemOffset (i, j);
        if ((i == (SocketNumber - 1)) && (j == (RbNumberPerSocket - 1))) {
          // workaround to set last RB's MMIO limit to 0xFFFF_FFFF_FFFF
          FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((i * RbNumberPerSocket + j) * 2 + 1), DstFabricIDSysOffset, MmioBaseAddr, (0x1000000000000 - MmioBaseAddr));
        } else {
          FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((i * RbNumberPerSocket + j) * 2 + 1), DstFabricIDSysOffset, MmioBaseAddr, (MmioBaseAddrNextRb - MmioBaseAddr));
        }
        FabricMmioManager->AllocateMmioAbove4GOnThisRb[i][j] = TRUE;
        FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci = 0;  // don't have Non Pci MMIO for above 4G
        FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch = MmioBaseAddrPrefetchable;
        FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch = MmioBaseAddrNonPrefetchable;
        FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch = SizePrefetchable;
        FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch = SizeNonPrefetchable;
        FabricMmioManager->MmioRegionAbove4G[i][j].UsedSizeNonPci = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].UsedSizePrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].UsedSizeNonPrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].AlignNonPrefetch = MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Alignment;
        FabricMmioManager->MmioRegionAbove4G[i][j].AlignPrefetch = MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Alignment;

        IDS_HDT_CONSOLE (CPU_TRACE, "    BasePrefetch    0x%lX, SizePrefetch    0x%lX\n", FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch, FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch);
        IDS_HDT_CONSOLE (CPU_TRACE, "    BaseNonPrefetch 0x%lX, SizeNonPrefetch 0x%lX\n", FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch, FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch);
      }
    }
  }

  // Calculate size of below 4G
  MmioBaseAddrAbovePcieCfg = PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace;
  MmioBaseAddrBelowPcieCfg = TOM;
  MmioLimitAbovePcieCfg    = PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb);
  MmioLimitBelowPcieCfg    = PcdGet64 (PcdPciExpressBaseAddress);

  LastCombinationWork = FALSE;
  if (FabricGetResourceDistribution (&MmioIsAbovePcieCfg[0]) == EFI_SUCCESS) {
    // Get distribution information from NV, try it first
    if (TryThisCombination (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbNumberPerSocket, FabricMmioManager, SetDfRegisters)) {
      // It works! No need to find out a new combination that which RB is above Pcie Cfg
      IDS_HDT_CONSOLE (CPU_TRACE, "  Use combination in NV\n");
      LastCombinationWork = TRUE;
    }
  }

  if (!LastCombinationWork) {
    if (ArrangeMmioBelow4G (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbNumberPerSocket, FabricMmioManager, SetDfRegisters)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  Save combination to NV\n");
      FabricSetResourceDistribution (&MmioIsAbovePcieCfg[0]);
    } else {
      IDS_HDT_CONSOLE (CPU_TRACE, "  No enough size below 4G\n");
      Status = EFI_OUT_OF_RESOURCES;
    }
  }

  if (SpaceStatus != NULL) {
    ASSERT (mOverSizeBelowPcieMin != 0xFFFFFFFF);
    SpaceStatus->MmioSizeAbove4GReqInc = (MmioBaseAddrNextRb > MmioLimitAbove4G) ? (MmioBaseAddrNextRb - MmioLimitAbove4G) : 0;
    SpaceStatus->MmioSizeBelow4GReqInc = mOverSizeBelowPcieMin;
    if (SpaceStatus->MmioSizeBelow4GReqInc != 0) {
      SpaceStatus->MmioSizeBelow4GReqInc = (SpaceStatus->MmioSizeBelow4GReqInc + mAlignmentMask) & (~mAlignmentMask);
    }
    IDS_HDT_CONSOLE (CPU_TRACE, "  Space Status: MmioSizeAbove4G %lX, MmioSizeAbove4GReqInc %lX\n", SpaceStatus->MmioSizeAbove4G, SpaceStatus->MmioSizeAbove4GReqInc);
    IDS_HDT_CONSOLE (CPU_TRACE, "  Space Status: MmioSizeBelow4G %lX, MmioSizeBelow4GReqInc %lX\n", SpaceStatus->MmioSizeBelow4G, SpaceStatus->MmioSizeBelow4GReqInc);
  }

  return Status;
}


/*---------------------------------------------------------------------------------------*/
/**
 * Try to arrange MMIO below 4G
 *
 *
 * @param[in]         MmioSizeForEachRb           Required MMIO size for each RB
 * @param[in]         MmioBaseAddrAbovePcieCfg    MmioBaseAddrAbovePcieCfg
 * @param[in]         MmioLimitAbovePcieCfg       MmioLimitAbovePcieCfg
 * @param[in]         MmioBaseAddrBelowPcieCfg    MmioBaseAddrBelowPcieCfg
 * @param[in]         MmioLimitBelowPcieCfg       MmioLimitBelowPcieCfg
 * @param[in, out]    MmioIsAbovePcieCfg          An BOOLEAN array, indicate which RB's MMIO is above Pcie Cfg
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbNumberPerSocket           RB number per socket
 * @param[in]         FabricMmioManager           Point to FABRIC_MMIO_MANAGER
 * @param[in]         SetDfRegisters              TRUE  - Set DF MMIO registers
 *                                                FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 * @retval            TRUE
 *                    FALSE
 */
BOOLEAN
ArrangeMmioBelow4G (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN       UINT64                         MmioBaseAddrAbovePcieCfg,
  IN       UINT64                         MmioLimitAbovePcieCfg,
  IN       UINT64                         MmioBaseAddrBelowPcieCfg,
  IN       UINT64                         MmioLimitBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbNumberPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  )
{
  UINT8   NumberOfRbBelowPcieCfg;
  BOOLEAN GetAnCombination;
  BOOLEAN NextCombination;

  GetAnCombination = FALSE;

  // Try to put 0 RB, 1 RB, 2 RBs... ZEN_MAX_SYSTEM_DIE_COUNT RBs below Pcie Cfg
  for (NumberOfRbBelowPcieCfg = 0; NumberOfRbBelowPcieCfg <= (SocketNumber * RbNumberPerSocket); NumberOfRbBelowPcieCfg++) {
    // 1. Default, all RBs are above Pcie Cfg
    LibAmdMemFill (MmioIsAbovePcieCfg, TRUE, (sizeof (BOOLEAN) * (MAX_SOCKETS_SUPPORTED * MAX_DIES_PER_SOCKET)), NULL);
    NextCombination = TRUE;

    // 2. First, try to put RB 7 to RB (ZEN_MAX_SYSTEM_DIE_COUNT - NumberOfRbBelowPcieCfg) below Pcie Cfg
    if (NumberOfRbBelowPcieCfg > 0 ) {
      LibAmdMemFill ((MmioIsAbovePcieCfg + (SocketNumber * RbNumberPerSocket) - NumberOfRbBelowPcieCfg), FALSE, (sizeof (BOOLEAN) * NumberOfRbBelowPcieCfg), NULL);
    }

    while (NextCombination) {
      // 3. Try this combination
      GetAnCombination = TryThisCombination (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbNumberPerSocket, FabricMmioManager, FALSE);
      if (GetAnCombination) {
        break;
      }
      // 4. If we can't make it, try to another combination
      NextCombination = GetNextCombination (NumberOfRbBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbNumberPerSocket);
    }
    if ((GetAnCombination) || (MmioLimitBelowPcieCfg == MmioBaseAddrBelowPcieCfg)) {
      // If we already got an combination or there's no space above Pcie Cfg, then break
      break;
    }

  }

  if (GetAnCombination) {
    TryThisCombination (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbNumberPerSocket, FabricMmioManager, SetDfRegisters);
  }

  return GetAnCombination;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get a different combination
 *
 *
 * @param[in]         NumberOfRbBelowPcieCfg     How many RBs MMIO should be put below Pcie Cfg
 * @param[in, out]    MmioIsAbovePcieCfg          An BOOLEAN array, indicate which RB's MMIO is above Pcie Cfg
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbNumberPerSocket          RB number per socket
 *
 * @retval            TRUE                        Get a combination
 *                    FALSE                       All combinations have been tried
 */
BOOLEAN
GetNextCombination (
  IN       UINT8                          NumberOfRbBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbNumberPerSocket
  )
{
  UINT8  MoveThisOne;
  UINT8  ResetTheseRb;

  // From RB 0, there're total number of 'ResetTheseRb' sequential RB, whose MMIO is below Pcie Cfg
  for (ResetTheseRb = 0; ResetTheseRb < NumberOfRbBelowPcieCfg; ResetTheseRb++) {
    if (*(MmioIsAbovePcieCfg + ResetTheseRb) == TRUE) {
      break;
    }
  }

  // if ResetTheseRb == NumberOfRbBelowPcieCfg
  // All combinations have been tried.
  if (ResetTheseRb == NumberOfRbBelowPcieCfg) {
    return FALSE;
  }

  // After number of ResetTheseRb RBs, find out the first RB whose MMIO is below Pcie Cfg.
  for (MoveThisOne = ResetTheseRb + 1; MoveThisOne < (SocketNumber * RbNumberPerSocket); MoveThisOne++) {
    if (*(MmioIsAbovePcieCfg + MoveThisOne) == FALSE) {
      break;
    }
  }
  ASSERT (MoveThisOne < (SocketNumber * RbNumberPerSocket));
  *(MmioIsAbovePcieCfg + MoveThisOne) = TRUE;
  *(MmioIsAbovePcieCfg + MoveThisOne - 1) = FALSE;
  LibAmdMemFill (MmioIsAbovePcieCfg, TRUE, (sizeof (BOOLEAN) * ResetTheseRb), NULL);
  LibAmdMemFill ((MmioIsAbovePcieCfg + MoveThisOne - 1 - ResetTheseRb), FALSE, (sizeof (BOOLEAN) * ResetTheseRb), NULL);

  return TRUE;
}

/*---------------------------------------------------------------------------------------*/
/**
 * If there's enough space for current combination
 *
 *
 * @param[in]         MmioSizeForEachRb           Required MMIO size for each RB
 * @param[in]         MmioBaseAddrAbovePcieCfg    MmioBaseAddrAbovePcieCfg
 * @param[in]         MmioLimitAbovePcieCfg       MmioLimitAbovePcieCfg
 * @param[in]         MmioBaseAddrBelowPcieCfg    MmioBaseAddrBelowPcieCfg
 * @param[in]         MmioLimitBelowPcieCfg       MmioLimitBelowPcieCfg
 * @param[in, out]    MmioIsAbovePcieCfg          An BOOLEAN array, indicate which RB's MMIO is above Pcie Cfg
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbNumberPerSocket           RB number per socket
 * @param[in]         FabricMmioManager           Point to FABRIC_MMIO_MANAGER
 * @param[in]         SetDfRegisters              TRUE  - Set DF MMIO registers
 *                                                FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 * @retval            TRUE
 *                    FALSE
 */
BOOLEAN
TryThisCombination (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN       UINT64                         MmioBaseAddrAbovePcieCfg,
  IN       UINT64                         MmioLimitAbovePcieCfg,
  IN       UINT64                         MmioBaseAddrBelowPcieCfg,
  IN       UINT64                         MmioLimitBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbNumberPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  )
{
  UINT8  i;
  UINT8  j;
  UINT8  SocketLoop;
  UINT8  RbLoop;
  UINT8  DstFabricIDSysOffset;
  UINT64 MmioBaseAddr; // To calculate oversize, we must use UINT64 here for all address, size
  UINT64 MmioCeiling;
  UINT64 MmioBaseAddrPrefetchable;
  UINT64 MmioBaseAddrNonPrefetchable;
  UINT64 MmioBaseAddrNonPci;
  UINT64 PrimaryRbSecondMmioSize;
  UINT64 SizePrefetchable;
  UINT64 SizeNonPrefetchable;
  UINT64 SizeNonPci;
  UINT64 AlignMask;
  UINT64 AlignMaskP;
  UINT64 AlignMaskNonPci;
  UINT64 BottomOfCompat;
  UINT64 OverSizeAbovePcieCfg;
  UINT64 OverSizeBelowPcieCfg;
  UINT64 AlignForFirstMmioRegionAbovePcieCfg;
  UINT64 AlignForFirstMmioRegionBelowPcieCfg;
  UINT64 DeltaSize; // this variable keeps the data how much size would be reduced if there's no NON-PCI MMIO
  BOOLEAN AlreadyGotAlignForFirstMmioRegionAbovePcieCfg;
  BOOLEAN AlreadyGotAlignForFirstMmioRegionBelowPcieCfg;
  BOOLEAN BigAlignFirstAbovePcieCfg;
  BOOLEAN BigAlignFirstBelowPcieCfg;
  BOOLEAN BigAlignFirst;
  BOOLEAN ReservedRegionAlreadySet;
  BOOLEAN OverSizeFlag;
  BOOLEAN PrimaryRbNonPciMmioAt2ndRegion;

  BigAlignFirstAbovePcieCfg = TRUE;
  BigAlignFirstBelowPcieCfg = TRUE;
  OverSizeFlag = FALSE;
  DeltaSize = 0;
  PrimaryRbNonPciMmioAt2ndRegion = FALSE;
  AlreadyGotAlignForFirstMmioRegionAbovePcieCfg = FALSE;
  AlreadyGotAlignForFirstMmioRegionBelowPcieCfg = FALSE;
  SizeNonPci = (PcdGet32 (PcdAmdMmioSizePerRbForNonPciDevice) > MMIO_MIN_NON_PCI_SIZE) ? PcdGet32 (PcdAmdMmioSizePerRbForNonPciDevice): MMIO_MIN_NON_PCI_SIZE;
  AlignMaskNonPci = ZEN_NON_PCI_MMIO_ALIGN_MASK;
  AlignForFirstMmioRegionAbovePcieCfg = 0;
  AlignForFirstMmioRegionBelowPcieCfg = 0;

  BottomOfCompat = BOTTOM_OF_COMPAT;
  /// @todo For ZP B2 and later, 0xFED0_0000 ~ 0xFED0_FFFF should be POSTED
  /// @todo BottomOfCompat = ADDITIONAL_POSTED_REGION_UNDER_DIE0_END + 1;
  ReservedRegionAlreadySet = FALSE;  // Indicate if PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat is set

  for (i = SocketNumber; i > 0; i--) {
    for (j = RbNumberPerSocket; j > 0; j--) {
      SocketLoop = i - 1;
      RbLoop = j - 1;

      if ((MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + SizeNonPci) == 0) {
        continue;
      }

      AlignMask  = MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment;
      AlignMaskP = MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment;

      if (*(MmioIsAbovePcieCfg + SocketLoop * ZEN_MAX_DIE_PER_SOCKET + RbLoop)) {
        // Mmio is above PcieCfg
        BigAlignFirst = BigAlignFirstAbovePcieCfg;
        MmioBaseAddr = MmioBaseAddrAbovePcieCfg;
        BigAlignFirstAbovePcieCfg = !BigAlignFirstAbovePcieCfg;

        if (!AlreadyGotAlignForFirstMmioRegionAbovePcieCfg) {
          // Save alignment for the first MMIO region, it will be used for calculate oversize
          AlignForFirstMmioRegionAbovePcieCfg = (AlignMask > AlignMaskP) ? AlignMask : AlignMaskP;
          AlreadyGotAlignForFirstMmioRegionAbovePcieCfg = TRUE;
        }
      } else {
        // Mmio is below PcieCfg
        BigAlignFirst = BigAlignFirstBelowPcieCfg;
        MmioBaseAddr = MmioBaseAddrBelowPcieCfg;
        BigAlignFirstBelowPcieCfg = !BigAlignFirstBelowPcieCfg;

        if (!AlreadyGotAlignForFirstMmioRegionBelowPcieCfg) {
          // Save alignment for the first MMIO region, it will be used for calculate oversize
          AlignForFirstMmioRegionBelowPcieCfg = (AlignMask > AlignMaskP) ? AlignMask: AlignMaskP;
          AlreadyGotAlignForFirstMmioRegionBelowPcieCfg = TRUE;
        }
      }

      if (BigAlignFirst) {
        if (MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment >= MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment) {
          // Prefetchable -> Non Prefetchable -> Non Pci
          MmioBaseAddrPrefetchable = (MmioBaseAddr + AlignMaskP) & (~AlignMaskP);
          MmioBaseAddrNonPrefetchable = (MmioBaseAddrPrefetchable + MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + AlignMask) & (~AlignMask);
          MmioBaseAddrNonPci = (MmioBaseAddrNonPrefetchable + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + AlignMaskNonPci) & (~AlignMaskNonPci);
          SizePrefetchable = MmioBaseAddrNonPrefetchable - MmioBaseAddrPrefetchable;
          SizeNonPrefetchable = MmioBaseAddrNonPci - MmioBaseAddrNonPrefetchable;
          MmioCeiling = MmioBaseAddrNonPci + SizeNonPci;
          DeltaSize = MmioBaseAddrNonPci - MmioBaseAddrNonPrefetchable - MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + SizeNonPci;
        } else {
          // Non Prefetchable -> Prefetchable -> Non Pci
          MmioBaseAddrNonPrefetchable = (MmioBaseAddr + AlignMask) & (~AlignMask);
          MmioBaseAddrPrefetchable = (MmioBaseAddrNonPrefetchable + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + AlignMaskP) & (~AlignMaskP);
          MmioBaseAddrNonPci = (MmioBaseAddrPrefetchable + MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + AlignMaskNonPci) & (~AlignMaskNonPci);
          SizeNonPrefetchable = MmioBaseAddrPrefetchable - MmioBaseAddrNonPrefetchable;
          SizePrefetchable = MmioBaseAddrNonPci - MmioBaseAddrPrefetchable;
          MmioCeiling = MmioBaseAddrNonPci + SizeNonPci;
          DeltaSize = MmioBaseAddrNonPci - MmioBaseAddrPrefetchable - MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + SizeNonPci;
        }
      } else {
        if (MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment <= MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment) {
          // Non Pci -> Prefetchable -> Non Prefetchable
          MmioBaseAddrNonPci = (MmioBaseAddr + AlignMaskNonPci) & (~AlignMaskNonPci);
          MmioBaseAddrPrefetchable = (MmioBaseAddrNonPci + SizeNonPci + AlignMaskP) & (~AlignMaskP);
          MmioBaseAddrNonPrefetchable = (MmioBaseAddrPrefetchable + MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + AlignMask) & (~AlignMask);
          SizePrefetchable = MmioBaseAddrNonPrefetchable - MmioBaseAddrPrefetchable;
          SizeNonPrefetchable = MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size;
          MmioCeiling = MmioBaseAddrNonPrefetchable + SizeNonPrefetchable;
          DeltaSize = MmioBaseAddrPrefetchable - ((MmioBaseAddr + AlignMaskP) & (~AlignMaskP));
        } else {
          // Non Pci -> Non Prefetchable -> Prefetchable
          MmioBaseAddrNonPci = (MmioBaseAddr + AlignMaskNonPci) & (~AlignMaskNonPci);
          MmioBaseAddrNonPrefetchable = (MmioBaseAddrNonPci + SizeNonPci + AlignMask) & (~AlignMask);
          MmioBaseAddrPrefetchable = (MmioBaseAddrNonPrefetchable + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + AlignMaskP) & (~AlignMaskP);
          SizeNonPrefetchable = MmioBaseAddrPrefetchable - MmioBaseAddrNonPrefetchable;
          SizePrefetchable = MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size;
          MmioCeiling = MmioBaseAddrPrefetchable + SizePrefetchable;
          DeltaSize = MmioBaseAddrNonPrefetchable - ((MmioBaseAddr + AlignMask) & (~AlignMask));
        }
      }

      if (SizeNonPrefetchable == 0) {

        MmioBaseAddrNonPrefetchable = 0;
      }
      if (SizePrefetchable == 0) {

        MmioBaseAddrPrefetchable = 0;
      }

      // Check if space is enough
      if (*(MmioIsAbovePcieCfg + SocketLoop * ZEN_MAX_DIE_PER_SOCKET + RbLoop)) {
        // Mmio is above PcieCfg
        MmioBaseAddrAbovePcieCfg = MmioCeiling;
        if (MmioBaseAddrAbovePcieCfg > MmioLimitAbovePcieCfg) {
          OverSizeFlag = TRUE;
        }
      } else {
        // Mmio is below PcieCfg
        MmioBaseAddrBelowPcieCfg = MmioCeiling;
        if (MmioBaseAddrBelowPcieCfg > MmioLimitBelowPcieCfg) {
          OverSizeFlag = TRUE;
        }
      }

      // (OverSize) && (Primary RB has 2nd MMIO), try to see if moving primary RB's Non-Pci MMIO from 1st region to 2nd region could work
      // Always put Non-Pci at top of 2nd MMIO
      if ((OverSizeFlag) && (SocketLoop == 0) && (RbLoop == 0) && ((SocketNumber * RbNumberPerSocket) < (ZEN_MAX_DIE_PER_SOCKET * ZEN_MAX_SOCKET))) {
        if (*(MmioIsAbovePcieCfg)) {
          if (((MmioBaseAddrAbovePcieCfg - DeltaSize) <= MmioLimitAbovePcieCfg) &&
              (MmioBaseAddrBelowPcieCfg <= ((MmioLimitBelowPcieCfg - SizeNonPci) & (~AlignMaskNonPci)))) {
            OverSizeFlag = FALSE;
            PrimaryRbNonPciMmioAt2ndRegion = TRUE;
            MmioBaseAddrAbovePcieCfg -= DeltaSize;
            MmioCeiling -= DeltaSize;
          }
        } else {
          if (((MmioBaseAddrBelowPcieCfg - DeltaSize) <= MmioLimitBelowPcieCfg) &&
              (MmioBaseAddrAbovePcieCfg <= ((MmioLimitAbovePcieCfg - SizeNonPci) & (~AlignMaskNonPci)))) {
            OverSizeFlag = FALSE;
            PrimaryRbNonPciMmioAt2ndRegion = TRUE;
            MmioBaseAddrBelowPcieCfg -= DeltaSize;
            MmioCeiling -= DeltaSize;
          }
        }

        // Adjust MmioBaseAddrNonPrefetchable & MmioBaseAddrPrefetchable if we move primary RB's NON-PCI from 1st region to 2nd region and NON-PCI is at lower address
        if (PrimaryRbNonPciMmioAt2ndRegion && (!BigAlignFirst)) {
          MmioBaseAddrNonPrefetchable -= DeltaSize;
          MmioBaseAddrPrefetchable -= DeltaSize;
        }
      }

      // Set DF MMIO registers
      if ((!OverSizeFlag) && SetDfRegisters && (FabricMmioManager != NULL)) {
        IDS_HDT_CONSOLE (CPU_TRACE, "  User Request below 4G: Socket%x RB%x Prefetch MMIO Size %lX, AlignBit %X\n", SocketLoop, RbLoop, MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size, MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment);
        IDS_HDT_CONSOLE (CPU_TRACE, "                           Non Prefetch MMIO Size %lX, AlignBit %X\n", MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size, MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment);
        ASSERT (BottomOfCompat >= PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb));

        DstFabricIDSysOffset = (UINT8) FabricTopologyGetDieSystemOffset (SocketLoop, RbLoop);
        if ((SocketLoop == 0) && (RbLoop == 0)) {
          if (*(MmioIsAbovePcieCfg + SocketLoop * ZEN_MAX_DIE_PER_SOCKET + RbLoop)) {
            FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((SocketLoop * RbNumberPerSocket + RbLoop) * 2), DstFabricIDSysOffset, MmioBaseAddr, (BottomOfCompat - MmioBaseAddr));
            MmioBaseAddrAbovePcieCfg = BottomOfCompat;
            ReservedRegionAlreadySet = TRUE;
          } else {
            FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((SocketLoop * RbNumberPerSocket + RbLoop) * 2), DstFabricIDSysOffset, MmioBaseAddr, (MmioLimitBelowPcieCfg - MmioBaseAddr));
            MmioBaseAddrBelowPcieCfg = MmioLimitBelowPcieCfg;
          }
        } else {
          FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((SocketLoop * RbNumberPerSocket + RbLoop) * 2), DstFabricIDSysOffset, MmioBaseAddr, (MmioCeiling - MmioBaseAddr));
        }

        FabricMmioManager->AllocateMmioBelow4GOnThisRb[SocketLoop][RbLoop] = TRUE;
        if ((SocketLoop == 0) && (RbLoop == 0) && PrimaryRbNonPciMmioAt2ndRegion) {
          IDS_HDT_CONSOLE (CPU_TRACE, "    NON-PCI MMIO of primary RB has been moved to its 2nd region\n");
          FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPci = 0;
          FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPci = 0;
        } else {
          FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPci = MmioBaseAddrNonPci;
          FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPci = SizeNonPci;
        }
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BasePrefetch = MmioBaseAddrPrefetchable;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPrefetch = MmioBaseAddrNonPrefetchable;

        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizePrefetch = SizePrefetchable;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPrefetch = SizeNonPrefetchable;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].UsedSizeNonPci = 0;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].UsedSizePrefetch = 0;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].UsedSizeNonPrefetch = 0;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].AlignNonPrefetch = MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment;
        FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].AlignPrefetch = MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment;

        IDS_HDT_CONSOLE (CPU_TRACE, "    BasePrefetch    0x%lX, SizePrefetch    0x%lX\n", FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BasePrefetch, FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizePrefetch);
        IDS_HDT_CONSOLE (CPU_TRACE, "    BaseNonPrefetch 0x%lX, SizeNonPrefetch 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPrefetch, FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPrefetch);
        IDS_HDT_CONSOLE (CPU_TRACE, "    BaseNonPci      0x%lX, SizeNonPci      0x%lX\n", FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPci, FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPci);
      }
    }
  }

  // If SetDfRegisters if FALSE, this function is called by FabricReallocateResourceForEachRb
  // And we should record which combination has the minimum gap
  if (!SetDfRegisters) {
    if (OverSizeFlag) {
      if (MmioBaseAddrAbovePcieCfg > MmioLimitAbovePcieCfg) {
        OverSizeAbovePcieCfg = MmioBaseAddrAbovePcieCfg - MmioLimitAbovePcieCfg;
      } else {
        OverSizeAbovePcieCfg = 0;
      }
      if (MmioBaseAddrBelowPcieCfg > MmioLimitBelowPcieCfg) {
        OverSizeBelowPcieCfg = MmioBaseAddrBelowPcieCfg - MmioLimitBelowPcieCfg;
      } else {
        OverSizeBelowPcieCfg = 0;
      }
      if (OverSizeAbovePcieCfg == 0) {
        // Since user would not change PcieCfg space location, they would only change TOM, so we should make sure there's no oversize above PcieCfg
        if (OverSizeBelowPcieCfg < mOverSizeBelowPcieMin) {
          mOverSizeBelowPcieMin = (UINT32) OverSizeBelowPcieCfg;
          mAlignmentMask = (UINT32) AlignForFirstMmioRegionBelowPcieCfg;
        }
      }
    } else {
      mOverSizeBelowPcieMin = 0;
    }
  }

  // Primary RB's 2nd MMIO
  if ((!OverSizeFlag) && SetDfRegisters && (FabricMmioManager != NULL)) {
    if (((MmioBaseAddrAbovePcieCfg + ZEN_MMIO_MIN_SIZE) <= MmioLimitAbovePcieCfg) || ((MmioBaseAddrBelowPcieCfg + ZEN_MMIO_MIN_SIZE) <= MmioLimitBelowPcieCfg)) {
      if ((MmioSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size != 0) || (MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size != 0) || PrimaryRbNonPciMmioAt2ndRegion) {
        if ((SocketNumber * RbNumberPerSocket) < (ZEN_MAX_DIE_PER_SOCKET * ZEN_MAX_SOCKET)) {
          for (i = 0; i < ZEN_MAX_SOCKET; i++) {
            for (j = 0; j < ZEN_MAX_DIE_PER_SOCKET; j++) {
              if (FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] == FALSE) {
                IDS_HDT_CONSOLE (CPU_TRACE, "  Primary RB has 2nd MMIO below 4G\n");
                FabricMmioManager->PrimaryRb2ndMmioPairBelow4G = (UINT8) ((i << 4) | j);
                if (MmioBaseAddrAbovePcieCfg < MmioLimitAbovePcieCfg) {
                  FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((i * RbNumberPerSocket + j) * 2), 0, MmioBaseAddrAbovePcieCfg, (BottomOfCompat - MmioBaseAddrAbovePcieCfg));
                  MmioBaseAddr = MmioBaseAddrAbovePcieCfg;
                  PrimaryRbSecondMmioSize = MmioLimitAbovePcieCfg - MmioBaseAddrAbovePcieCfg;
                  ReservedRegionAlreadySet = TRUE;
                } else {
                  FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((i * RbNumberPerSocket + j) * 2), 0, MmioBaseAddrBelowPcieCfg, (MmioLimitBelowPcieCfg - MmioBaseAddrBelowPcieCfg));
                  MmioBaseAddr = MmioBaseAddrBelowPcieCfg;
                  PrimaryRbSecondMmioSize = MmioLimitBelowPcieCfg - MmioBaseAddrBelowPcieCfg;
                }
                if (PrimaryRbNonPciMmioAt2ndRegion) {
                  // Always put Non-Pci at top of 2nd MMIO
                  FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci = (MmioBaseAddr + PrimaryRbSecondMmioSize - SizeNonPci) & (~AlignMaskNonPci);
                  FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci = SizeNonPci;
                  PrimaryRbSecondMmioSize = FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci - MmioBaseAddr;
                } else {
                  FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci = 0;
                  FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci = 0;
                }
                // Distribute primary RB's 2nd MMIO base on user request
                AlignMask  = MmioSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Alignment;
                AlignMaskP = MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Alignment;
                if (MmioSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size == 0) {
                  SizePrefetchable = PrimaryRbSecondMmioSize;
                  SizeNonPrefetchable = 0;
                } else if (MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size == 0) {
                  SizePrefetchable = 0;
                  SizeNonPrefetchable = PrimaryRbSecondMmioSize;
                } else {
                  SizePrefetchable = MultU64x64 (DivU64x32 (PrimaryRbSecondMmioSize, ((UINT32) (MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size + MmioSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size))), MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size);
                  SizeNonPrefetchable = PrimaryRbSecondMmioSize - SizePrefetchable;
                }

                if (SizePrefetchable != 0) {
                  MmioBaseAddrPrefetchable = (MmioBaseAddr + AlignMaskP) & (~AlignMaskP);
                  SizePrefetchable = SizePrefetchable;
                } else {
                  MmioBaseAddrPrefetchable = MmioBaseAddr;
                  SizePrefetchable = 0;
                }

                if (SizeNonPrefetchable != 0) {
                  MmioBaseAddrNonPrefetchable = (MmioBaseAddrPrefetchable + SizePrefetchable + AlignMask) & (~AlignMask);
                  SizeNonPrefetchable = MmioBaseAddr + PrimaryRbSecondMmioSize - MmioBaseAddrNonPrefetchable;
                } else {
                  MmioBaseAddrNonPrefetchable = MmioBaseAddrPrefetchable + SizePrefetchable;
                  SizeNonPrefetchable = 0;
                }

                if (SizeNonPrefetchable == 0) {

                  MmioBaseAddrNonPrefetchable = 0;
                }
                if (SizePrefetchable == 0) {

                  MmioBaseAddrPrefetchable = 0;
                }

                FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch = MmioBaseAddrPrefetchable;
                FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch = MmioBaseAddrNonPrefetchable;
                FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch = SizePrefetchable;
                FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch = SizeNonPrefetchable;
                FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizePrefetch = 0;
                FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPrefetch = 0;
                FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPci = 0;
                FabricMmioManager->MmioRegionBelow4G[i][j].AlignNonPrefetch = MmioSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Alignment;
                FabricMmioManager->MmioRegionBelow4G[i][j].AlignPrefetch = MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Alignment;

                IDS_HDT_CONSOLE (CPU_TRACE, "    BasePrefetch    0x%lX, SizePrefetch    0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch, FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch);
                IDS_HDT_CONSOLE (CPU_TRACE, "    BaseNonPrefetch 0x%lX, SizeNonPrefetch 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch, FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch);
                IDS_HDT_CONSOLE (CPU_TRACE, "    BaseNonPci      0x%lX, SizeNonPci      0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci, FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci);

                FabricMmioManager->PrimaryRbHas2ndMmioBelow4G = TRUE;
                break;
              }
            }
            if (FabricMmioManager->PrimaryRbHas2ndMmioBelow4G) {
              break;
            }
          }
        }
      }
    }

    // If there's a spare MMIO register pair, set 0xFED0_0000 ~ 0xFED0_FFFF as posted
    FabricAdditionalMmioSetting1 (FabricMmioManager, SocketNumber, RbNumberPerSocket, BottomOfCompat, ReservedRegionAlreadySet);
  }


  return (!OverSizeFlag);
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricAdditionalMmioSetting1
 *
 * If reserved region for primayr RB (PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat) has not been set,
 * or that region doesn't include ADDITIONAL_POSTED_REGION_UNDER_DIE0_START ~ ADDITIONAL_POSTED_REGION_UNDER_DIE0_END,
 * set ADDITIONAL_POSTED_REGION_UNDER_DIE0_START ~ ADDITIONAL_POSTED_REGION_UNDER_DIE0_END as POSTED
 *
 * @param[in, out]    FabricMmioManager           Point to FABRIC_MMIO_MANAGER
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbNumberPerSocket           RB number per socket
 * @param[in]         BottomOfCompat              From BottomOfCompat to 4G is COMPAT region
 * @param[in]         ReservedRegionAlreadySet    PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat has been set or not
 *
 */
VOID
FabricAdditionalMmioSetting1 (
  IN       FABRIC_MMIO_MANAGER *FabricMmioManager,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbNumberPerSocket,
  IN       UINT64               BottomOfCompat,
  IN       BOOLEAN              ReservedRegionAlreadySet
  )
{
  UINT8   i;
  UINT8   j;
  UINT64  Base;
  UINT64  Size;
  BOOLEAN AlreadySet;

  AlreadySet = FALSE;
  Base = ADDITIONAL_POSTED_REGION_UNDER_DIE0_START;
  Size = ADDITIONAL_POSTED_REGION_UNDER_DIE0_END - ADDITIONAL_POSTED_REGION_UNDER_DIE0_START + 1;

  // If reserved region for primary RB (PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat) has not been set
  // or that region doesn't include ADDITIONAL_POSTED_REGION_UNDER_DIE0_START ~ ADDITIONAL_POSTED_REGION_UNDER_DIE0_END
  if ((!ReservedRegionAlreadySet) ||
      ((ReservedRegionAlreadySet) && (BottomOfCompat <= ADDITIONAL_POSTED_REGION_UNDER_DIE0_END))) {
    if (Size >= ZEN_MMIO_MIN_SIZE) {
      for (i = 0; i < ZEN_MAX_SOCKET; i++) {
        for (j = 0; j < ZEN_MAX_DIE_PER_SOCKET; j++) {
          // Find out a spare MMIO register pair
          if (FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] == FALSE) {
            if ((FabricMmioManager->PrimaryRbHas2ndMmioBelow4G) &&
                (((FabricMmioManager->PrimaryRb2ndMmioPairBelow4G >> 4) & 0xF) == i) &&
                ((FabricMmioManager->PrimaryRb2ndMmioPairBelow4G & 0xF) == j)) {
              continue;
            }
            FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((i * RbNumberPerSocket + j) * 2), 0, Base, Size);
            AlreadySet = TRUE;
            break;
          }

          if (FabricMmioManager->AllocateMmioAbove4GOnThisRb[i][j] == FALSE) {
            FabricSetMmioReg1 (SocketNumber, RbNumberPerSocket, ((i * RbNumberPerSocket + j) * 2 + 1), 0, Base, Size);
            AlreadySet = TRUE;
            break;
          }
        }
        if (AlreadySet) {
          break;
        }
      }
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetMmioReg1
 *
 * Set MMIO register pairs according to input parameters
 *
 * @param[in]         TotalSocket                 System socket count
 * @param[in]         RbPerSocket                 RB number per socket
 * @param[in]         MmioPairIndex               Which MMIO register pair should be set
 * @param[in]         DstFabricIDSysOffset        Fabric ID system offset
 * @param[in]         BaseAddress                 Base address of MMIO region
 * @param[in]         Length                      Length of MMIO region
 *
 */
VOID
FabricSetMmioReg1 (
  IN       UINT8  TotalSocket,
  IN       UINT8  RbPerSocket,
  IN       UINT8  MmioPairIndex,
  IN       UINT8  DstFabricIDSysOffset,
  IN       UINT64 BaseAddress,
  IN       UINT64 Length
  )
{
  UINTN  i;
  UINTN  j;
  MMIO_ADDR_CTRL MmioAddrCtrlReg;

  ASSERT (Length >= ZEN_MMIO_MIN_SIZE);
  BaseAddress = (BaseAddress + 0xFFFF) & 0xFFFFFFFFFFFF0000;
  MmioAddrCtrlReg.Value = FabricRegisterAccRead (0, 0, 0x0, (MMIO_ADDRESS_CONTROL_REG_0 + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC);
  for (i = 0; i < TotalSocket; i++) {
    for (j = 0; j < RbPerSocket; j++) {
      FabricRegisterAccWrite (i, j, 0x0, (MMIO_BASE_ADDRESS_REG_0  + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC, (UINT32) (BaseAddress >> 16), TRUE);
      FabricRegisterAccWrite (i, j, 0x0, (MMIO_LIMIT_ADDRESS_REG_0 + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC, (UINT32) ((BaseAddress + Length - 1) >> 16), TRUE);
      MmioAddrCtrlReg.Field.RE = 1;
      MmioAddrCtrlReg.Field.WE = 1;
      MmioAddrCtrlReg.Field.DstFabricID &= 0x1F;
      MmioAddrCtrlReg.Field.DstFabricID |= DstFabricIDSysOffset;
      FabricRegisterAccWrite (i, j, 0x0, (MMIO_ADDRESS_CONTROL_REG_0 + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC, MmioAddrCtrlReg.Value, TRUE);
    }
  }
  IDS_HDT_CONSOLE (CPU_TRACE, "  AGESA set MMIO pair #%X, 0x%X0000 ~ 0x%XFFFF DstFabricID: 0x%X\n", MmioPairIndex, (UINT32) (BaseAddress >> 16), (UINT32) ((BaseAddress + Length - 1) >> 16), MmioAddrCtrlReg.Field.DstFabricID);
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetIoReg1
 *
 * Set IO register pairs according to input parameters
 *
 * @param[in]         TotalSocket                 System socket count
 * @param[in]         RbPerSocket                RB number per socket
 * @param[in]         RegIndex                    Which IO register should be set
 * @param[in]         DstFabricIDSysOffset        Fabric ID system offset
 * @param[in]         IoBase                      Base address of IO region
 * @param[in]         IoSize                      Length of IO region
 *
 */
VOID
FabricSetIoReg1 (
  IN       UINT8  TotalSocket,
  IN       UINT8  RbPerSocket,
  IN       UINT8  RegIndex,
  IN       UINT8  DstFabricIDSysOffset,
  IN       UINT32 IoBase,
  IN       UINT32 IoSize
  )
{
  UINTN  i;
  UINTN  j;
  X86IO_BASE_ADDR  IoBaseReg;
  X86IO_LIMIT_ADDR IoLimitReg;

  IoBaseReg.Value  = 0;
  IoLimitReg.Value = FabricRegisterAccRead (0, 0, 0x0, (X86IO_LIMIT_ADDRESS_REG0 + RegIndex * 8), FABRIC_REG_ACC_BC);

  for (i = 0; i < TotalSocket; i++) {
    for (j = 0; j < RbPerSocket; j++) {
      IoBaseReg.Field.RE = 1;
      IoBaseReg.Field.WE = 1;
      IoBaseReg.Field.IOBase = (IoBase & 0xFFFFF000) >> 12;
      FabricRegisterAccWrite (i, j, 0x0, (X86IO_BASE_ADDRESS_REG0 + RegIndex * 8), FABRIC_REG_ACC_BC, IoBaseReg.Value, TRUE);

      IoLimitReg.Field.DstFabricID &= 0x1F;
      IoLimitReg.Field.DstFabricID |= DstFabricIDSysOffset;
      IoLimitReg.Field.IOLimit = ((IoBase + IoSize - 1) & 0xFFFFF000) >> 12;
      FabricRegisterAccWrite (i, j, 0x0, (X86IO_LIMIT_ADDRESS_REG0 + RegIndex * 8), FABRIC_REG_ACC_BC, IoLimitReg.Value, TRUE);
    }
  }
  IDS_HDT_CONSOLE (CPU_TRACE, "  AGESA set IO pair #%X, 0x%X000 ~ 0x%XFFF DstFabricID: 0x%X\n", RegIndex, (UINT32) (IoBase >> 12), (UINT32) ((IoBase + IoSize - 1) >> 12), IoLimitReg.Field.DstFabricID);

}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetCfgAddrMapReg1
 *
 * Set MMIO register pairs according to input parameters
 *
 * @param[in]         TotalSocket                 System socket count
 * @param[in]         RbPerSocket                 RB number per socket
 * @param[in]         RegIndex                    Which CFG Addr Map register should be set
 * @param[in]         SktNum                      Socket number
 * @param[in]         RbNum                       Root bridge number
 * @param[in]         Base                        PCI bus base
 * @param[in]         Limit                       PCI bus Limit
 *
 */
VOID
FabricSetCfgAddrMapReg1 (
  IN       UINT8  TotalSocket,
  IN       UINT8  RbPerSocket,
  IN       UINT8  RegIndex,
  IN       UINTN  SktNum,
  IN       UINTN  RbNum,
  IN       UINT16 Base,
  IN       UINT16 Limit
  )
{
  UINTN  i;
  UINTN  j;
  CFG_ADDR_MAP CfgAddrMapReg;

  ASSERT (Base < 0x100);
  ASSERT (Limit < 0x100);

  CfgAddrMapReg.Value = 0;
  CfgAddrMapReg.Field.RE = 1;
  CfgAddrMapReg.Field.WE = 1;
  CfgAddrMapReg.Field.DstFabricID = (UINT32) FabricTopologyGetHostBridgeSystemFabricID (SktNum, RbNum, 0);
  CfgAddrMapReg.Field.BusNumBase = Base;
  CfgAddrMapReg.Field.BusNumLimit = Limit;

  for (i = 0; i < TotalSocket; i++) {
    for (j = 0; j < RbPerSocket; j++) {
      FabricRegisterAccWrite (i, j, 0x0, (CFG_ADDR_MAP_REG0  + RegIndex * 4), FABRIC_REG_ACC_BC, CfgAddrMapReg.Value, TRUE);
    }
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  AGESA set CfgAddrMap #%X, 0x%2X ~ 0x%2X DstFabricID: 0x%X\n", RegIndex, CfgAddrMapReg.Field.BusNumBase, CfgAddrMapReg.Field.BusNumLimit, CfgAddrMapReg.Field.DstFabricID);
}

