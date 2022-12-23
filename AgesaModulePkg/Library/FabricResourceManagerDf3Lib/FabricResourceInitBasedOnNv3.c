/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric MMIO initialization based on NV variable for DF3
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
#include <FabricRegistersDf3.h>
#include <FabricInfoSsp.h>
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Protocol/FabricResourceManagerServicesProtocol.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include <Library/FabricResourceSizeForEachRbLib.h>
#include "FabricResourceManager3.h"

#define FILECODE LIBRARY_FABRICRESOURCEMANAGERDF3LIB_FABRICRESOURCEINITBASEDONNV3_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
UINT32 mOverSizeBelowPcieMin = 0xFFFFFFFF;
UINT32 mAlignmentMask = 0;

BOOLEAN mLogToPhyMapInit = FALSE;
BOOLEAN mEnoughAbovePcieSpaceForPrimaryRb = FALSE;
FABRIC_RB_LOG_TO_PHY_MAP mLogToPhyMap[SSP_MAX_SOCKETS * SSP_MAX_DIES_PER_SOCKET * SSP_MAX_HOST_BRIDGES_PER_DIE];


#define MMIO_QUEUE_SIZE 3

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
BOOLEAN
ArrangeMmioAbove4G (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN OUT   FABRIC_ADDR_SPACE_SIZE        *SpaceStatus,
  IN OUT   UINT64                        *MmioBaseAddrNextRb,
  IN       UINT64                         MmioLimitAbove4G,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbsPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  );

BOOLEAN
ArrangeMmioBelow4G (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN       UINT64                         MmioBaseAddrAbovePcieCfg,
  IN       UINT64                         MmioLimitAbovePcieCfg,
  IN       UINT64                         MmioBaseAddrBelowPcieCfg,
  IN       UINT64                         MmioLimitBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbsPerSocket,
  IN       UINT8                          PrimarySocket,
  IN       UINT8                          PrimaryRootBridge,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  );

BOOLEAN
GetNextCombination (
  IN       UINT8                          NumberOfRbBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbsPerSocket
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
  IN       UINT8                          RbsPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  );

CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FindIomsMap3 (
  IN       UINTN               Socket,
  IN       UINTN               Die
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitPciBusBasedOnNvVariable3
 *
 * Initialize PCI bus base/limit for each Root Bridge based on NV variable.
 *
 * @param[in]         PciBusRangeForEachRb     How much PCI bus is required for each Root Bridge
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbsPerSocket             Root Bridge number per socket
 *
 */
EFI_STATUS
FabricInitPciBusBasedOnNvVariable3 (
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
  UINTN             RbPerDie;
  BOOLEAN           NeedReallocate;
  CFG_ADDRESS_CTRL_REGISTER         CfgAddrCtrl;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *IomsEntry;

  // Check if we need to re-allocate PCI bus base/limit
  NeedReallocate = FALSE;

  RbPerDie = FabricTopologyGetNumberOfRootBridgesOnDie (0, 0);
  for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
    for (RbLoop = 0; RbLoop < RbsPerSocket; RbLoop++) {
      PciBase = FabricTopologyGetHostBridgeBusBase (SktLoop, (RbLoop / RbPerDie), (RbLoop % RbPerDie));
      PciLimit = FabricTopologyGetHostBridgeBusLimit (SktLoop, (RbLoop / RbPerDie), (RbLoop % RbPerDie));
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
    IomsEntry = FindIomsMap3 (0, 0);
    ASSERT (IomsEntry != NULL);

    // Clear all Configuration Address Map registers (up to 8)
    IDS_HDT_CONSOLE (CPU_TRACE, "  Init PCI bus base/limit based on NV variable\n");
    for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
      DiePerSkt = FabricTopologyGetNumberOfDiesOnSocket (SktLoop);
      for (DieLoop = 0; DieLoop < DiePerSkt; DieLoop++) {
        for (RegIndex = 0; RegIndex < 8; RegIndex++) {
          FabricRegisterAccWrite (SktLoop, DieLoop, 0x0, (CFG_ADDR_MAP_REG0  + RegIndex * 4), FABRIC_REG_ACC_BC, 0, TRUE);
        }
        for (RbLoop = 0; RbLoop < RbsPerSocket; RbLoop++) {
          FabricRegisterAccWrite (SktLoop, DieLoop, 0x0, CFGADDRESSCTRL_REG, IomsEntry->IDs[RbLoop].InstanceID, 0, TRUE);
        }
      }
    }

    // Set Configuration Address Map registers
    FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

    RegIndex = 0;
    PciBusBase = 0;
    PciBusLimit = (UINT16) (PciBusBase + PciBusRangeForEachRb->PciBusNumber[PrimarySocket][PrimaryRootBridge] - 1);
    FabricSetCfgAddrMapReg3 (SocketNumber, (UINT8) RbPerDie, RegIndex, PrimarySocket, PrimaryRootBridge, PciBusBase, PciBusLimit);
    CfgAddrCtrl.Value = 0;
    CfgAddrCtrl.Field.SecBusNum = PciBusBase;
    FabricRegisterAccWrite (PrimarySocket, 0, 0, CFGADDRESSCTRL_REG, IomsEntry->IDs[PrimaryRootBridge].InstanceID, CfgAddrCtrl.Value, TRUE);

    for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
      for (RbLoop = RbsPerSocket; RbLoop > 0; RbLoop--) {
        if ((SktLoop == PrimarySocket) && ((RbLoop - 1) == PrimaryRootBridge)) {
          continue;
        }
        RegIndex++;
        PciBusBase = PciBusLimit + 1;
        if ((SktLoop == (UINTN) (SocketNumber - 1)) && (RbLoop == 1)) {
          PciBusLimit = 0xFF;
        } else {
          PciBusLimit = (UINT16) (PciBusBase + PciBusRangeForEachRb->PciBusNumber[SktLoop][RbLoop - 1] - 1);
        }
        FabricSetCfgAddrMapReg3 (SocketNumber, (UINT8) RbPerDie, RegIndex, SktLoop, (RbLoop - 1), PciBusBase, PciBusLimit);
        CfgAddrCtrl.Value = 0;
        CfgAddrCtrl.Field.SecBusNum = PciBusBase;
        FabricRegisterAccWrite (SktLoop, 0, 0, CFGADDRESSCTRL_REG, IomsEntry->IDs[RbLoop - 1].InstanceID, CfgAddrCtrl.Value, TRUE);
      }
    }
  }

  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitIoBasedOnNvVariable3
 *
 * Initialize IO registers for each Root Bridge based on NV variable.
 *
 * @param[in, out]    FabricIoManager          Point to FABRIC_IO_MANAGER
 * @param[in]         IoSizeForEachRb          How much IO size is required for each Root Bridge
 * @param[in, out]    SpaceStaus               Current status
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbsPerSocket             Root Bridge number per socket
 * @param[in]         SetDfRegisters           TRUE  - Set DF MMIO registers
 *                                             FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 */
EFI_STATUS
FabricInitIoBasedOnNvVariable3 (
  IN       FABRIC_IO_MANAGER   *FabricIoManager,
  IN       FABRIC_RESOURCE_FOR_EACH_RB  *IoSizeForEachRb,
  IN       FABRIC_ADDR_SPACE_SIZE       *SpaceStatus,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbsPerSocket,
  IN       BOOLEAN              SetDfRegisters
  )
{
  UINTN             PhySktLoop;
  UINTN             PhyRbLoop;
  UINTN             LogSktLoop;
  UINTN             LogRbLoop;
  UINT8             RegIndex;
  UINT8             AlreadyInitNonPrimaryRbNum;
  UINT32            IoBase;
  UINT32            IoSize;
  UINT32            IoBaseForPrimaryRb;
  UINT32            IoSizeForPrimaryRb;
  UINT32            IoBaseForOthers;
  UINT32            LegacyIoSize;
  UINTN             PrimarySocket;
  UINTN             PrimaryRootBridge;

  RegIndex = 0;
  LegacyIoSize = X86_LEGACY_IO_SIZE;

  IoBaseForPrimaryRb = 0;
  IoSizeForPrimaryRb = DF_IO_LIMIT - IoBaseForPrimaryRb;
  IoBase = 0;
  IoBaseForOthers = 0;

  FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

  if ((SocketNumber != 1) || (RbsPerSocket != 1)) {
    // If we have more than one RootBridge
    // find out primary RootBridge and reserve an IO region start from 0 for it
    for (PhySktLoop = 0; PhySktLoop < SocketNumber; PhySktLoop++) {
      for (PhyRbLoop = 0; PhyRbLoop < RbsPerSocket; PhyRbLoop++) {
        if ((PhySktLoop == PrimarySocket) && (PhyRbLoop == PrimaryRootBridge)) {
          IoSizeForPrimaryRb = (UINT32) (IoSizeForEachRb->IO[PhySktLoop][PhyRbLoop].Size & VH_IO_SIZE_MASK) + LegacyIoSize;
          IoBaseForOthers = IoBaseForPrimaryRb + IoSizeForPrimaryRb;
        }
      }
    }
  }


  IDS_HDT_CONSOLE (CPU_TRACE, "    reserve 0x%X IO size for legacy devices\n", LegacyIoSize);

  AlreadyInitNonPrimaryRbNum = 0;
  for (LogSktLoop = 0; LogSktLoop < SocketNumber; LogSktLoop++) {
    for (LogRbLoop = 0; LogRbLoop < RbsPerSocket; LogRbLoop++) {
      FabricGetPhySktRbNum (LogSktLoop, LogRbLoop, &PhySktLoop, &PhyRbLoop);
      if (SpaceStatus != NULL) {
        SpaceStatus->IoSize += (UINT32) IoSizeForEachRb->IO[PhySktLoop][PhyRbLoop].Size & VH_IO_SIZE_MASK;
      }

      if ((PhySktLoop == PrimarySocket) && (PhyRbLoop == PrimaryRootBridge)) {
        IoBase = IoBaseForPrimaryRb;
        IoSize = IoSizeForPrimaryRb;
      } else if (AlreadyInitNonPrimaryRbNum == (SocketNumber * RbsPerSocket - 2)) {
        // check if it's the last RB. DF's IO space is up to 25 bits, so set limit to 0x1FFFFFF for last RB
        IoBase = IoBaseForOthers;
        IoSize = DF_IO_LIMIT - IoBase;
      } else {
        IoBase = IoBaseForOthers;
        IoSize = (UINT32) IoSizeForEachRb->IO[PhySktLoop][PhyRbLoop].Size & VH_IO_SIZE_MASK;
        IoBaseForOthers += IoSize;
      }

      ASSERT (IoBase <= X86IO_LIMIT);

      if (IoSize == 0) {
        continue;
      }

      if ((FabricIoManager != NULL) && SetDfRegisters) {
        FabricSetIoReg3 (SocketNumber, RegIndex, PhySktLoop, PhyRbLoop, IoBase, IoSize);

        if ((PhySktLoop == PrimarySocket) && (PhyRbLoop == PrimaryRootBridge)) {
          // This root bridge has an additional IO region for legacy devices, size is LegacyIoSize
          FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase = IoBase + LegacyIoSize;
          FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize = IoSize - LegacyIoSize;
        } else if (AlreadyInitNonPrimaryRbNum == (SocketNumber * RbsPerSocket - 2)) {
          // When report to X86, IO region should be IoBase ~ X86IO_LIMIT since X86 only support 16 bits IO space
          FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase = IoBase;
          FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize = X86IO_LIMIT - FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase;
        } else {
          FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase = IoBase;
          FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize = IoSize;
          AlreadyInitNonPrimaryRbNum++;
        }
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoUsed = 0;
        IDS_HDT_CONSOLE (CPU_TRACE, "  Socket%x RootBridge%x has IO base 0x%X size 0x%X\n\n", PhySktLoop, PhyRbLoop, FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase, FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize);
      }

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
 * FabricInitMmioBasedOnNvVariable3
 *
 * Initialize MMIO registers for each Root Bridge based on NV variable.
 *
 * @param[in, out]    FabricMmioManager        Point to FABRIC_MMIO_MANAGER
 * @param[in]         MmioSizeForEachRb        How much MMIO size is required for each Root Bridge
 * @param[in, out]    SpaceStaus               Current status
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbsPerSocket             Root Bridge number per socket
 * @param[in]         SetDfRegisters           TRUE  - Set DF MMIO registers
 *                                             FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 */
EFI_STATUS
FabricInitMmioBasedOnNvVariable3 (
  IN       FABRIC_MMIO_MANAGER *FabricMmioManager,
  IN       FABRIC_RESOURCE_FOR_EACH_RB  *MmioSizeForEachRb,
  IN       FABRIC_ADDR_SPACE_SIZE       *SpaceStatus,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbsPerSocket,
  IN       BOOLEAN              SetDfRegisters
  )
{
  UINT64 MmioLimitAbove4G;
  UINT64 MmioBaseAddrNextRb;
  UINT64 MmioBaseAddrAbovePcieCfg;
  UINT64 MmioBaseAddrBelowPcieCfg;
  UINT64 MmioLimitAbovePcieCfg;
  UINT64 MmioLimitBelowPcieCfg;
  UINT64 TOM;
  UINT64 TOM2;
  UINT64 PciCfgSpace;
  UINT64 MmioSizeBelowHole;
  UINT64 MmioSizeAboveHole;
  UINT64 SizeNonPci;
  UINTN  PrimarySocket;
  UINTN  PrimaryRootBridge;
  EFI_STATUS Status;
  BOOLEAN MmioIsAbovePcieCfg[SSP_MAX_SOCKETS * SSP_MAX_DIES_PER_SOCKET * SSP_MAX_HOST_BRIDGES_PER_DIE];
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
  IDS_HDT_CONSOLE (CPU_TRACE, "  TOM: 0x%lX, TOM2: 0x%lX, Pcie configuration space: 0x%lX ~ 0x%lX\n", TOM, TOM2, PcdGet64 (PcdPciExpressBaseAddress), (PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace));

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

  IDS_HDT_CONSOLE (CPU_TRACE, "    Above 4G MMIO base is 0x%lX, limit is 0x%lX\n", MmioBaseAddrNextRb, MmioLimitAbove4G);

  ArrangeMmioAbove4G (MmioSizeForEachRb, SpaceStatus, &MmioBaseAddrNextRb, MmioLimitAbove4G, SocketNumber, RbsPerSocket, FabricMmioManager, SetDfRegisters);

  // Calculate size of below 4G
  MmioBaseAddrAbovePcieCfg = PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace;
  MmioBaseAddrBelowPcieCfg = TOM;
  MmioLimitAbovePcieCfg    = PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb);
  MmioLimitBelowPcieCfg    = PcdGet64 (PcdPciExpressBaseAddress);

  FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

  SizeNonPci = PcdGet32 (PcdAmdMmioSizePerRbForNonPciDevice);
  if ((MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[PrimarySocket][PrimaryRootBridge].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[PrimarySocket][PrimaryRootBridge].Size + SizeNonPci) <= (MmioLimitAbovePcieCfg - MmioBaseAddrAbovePcieCfg)) {
    mEnoughAbovePcieSpaceForPrimaryRb = TRUE;
  }

  LastCombinationWork = FALSE;
  if (FabricGetResourceDistribution (&MmioIsAbovePcieCfg[0]) == EFI_SUCCESS) {
    // Get distribution information from NV, try it first
    if (TryThisCombination (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbsPerSocket, FabricMmioManager, SetDfRegisters)) {
      // It works! No need to find out a new combination that which RootBridge is above Pcie Cfg
      IDS_HDT_CONSOLE (CPU_TRACE, "  Use combination in NV\n");
      LastCombinationWork = TRUE;
    }
  }

  if (!LastCombinationWork) {
    if (ArrangeMmioBelow4G (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbsPerSocket, (UINT8) PrimarySocket, (UINT8) PrimaryRootBridge, FabricMmioManager, SetDfRegisters)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  Save combination to NV\n");
      FabricSetResourceDistribution (&MmioIsAbovePcieCfg[0]);
    } else {
      if (mEnoughAbovePcieSpaceForPrimaryRb) {
        mEnoughAbovePcieSpaceForPrimaryRb = FALSE;
        if (ArrangeMmioBelow4G (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbsPerSocket, (UINT8) PrimarySocket, (UINT8) PrimaryRootBridge, FabricMmioManager, SetDfRegisters)) {
          IDS_HDT_CONSOLE (CPU_TRACE, "  Save combination to NV\n");
          FabricSetResourceDistribution (&MmioIsAbovePcieCfg[0]);
        } else {
          IDS_HDT_CONSOLE (CPU_TRACE, "  No enough size below 4G\n");
          Status = EFI_OUT_OF_RESOURCES;
        }
      } else {
        IDS_HDT_CONSOLE (CPU_TRACE, "  No enough size below 4G\n");
        Status = EFI_OUT_OF_RESOURCES;
      }
    }
  }

  // Update SpaceStatus
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
 * Try to arrange MMIO above 4G
 *
 *
 * @param[in]         MmioSizeForEachRb           Required MMIO size for each RootBridge
 * @param[in, out]    SpaceStaus                  Current status
 * @param[in, out]    MmioBaseAddrNextRb          MmioBaseAddr for next RB, be used to check overflow
 * @param[in]         MmioLimitAbove4G            MmioLimitAbove4G
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbsPerSocket                RootBridge number per socket
 * @param[in]         FabricMmioManager           Point to FABRIC_MMIO_MANAGER
 * @param[in]         SetDfRegisters              TRUE  - Set DF MMIO registers
 *                                                FALSE - Not set DF MMIO registers, just calculate if user's requirment could be satisfied.
 *
 * @retval            TRUE
 *                    FALSE
 */
BOOLEAN
ArrangeMmioAbove4G (
  IN       FABRIC_RESOURCE_FOR_EACH_RB   *MmioSizeForEachRb,
  IN OUT   FABRIC_ADDR_SPACE_SIZE        *SpaceStatus,
  IN OUT   UINT64                        *MmioBaseAddrNextRb,
  IN       UINT64                         MmioLimitAbove4G,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbsPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  )
{
  UINT8  i;
  UINT8  j;
  UINT8  SktLoop;
  UINT8  RbLoop;
  UINT64 MmioBaseAddr;
  UINT64 MmioBaseAddrPrefetchable;
  UINT64 MmioBaseAddrNonPrefetchable;
  UINT64 MmioBaseAddrNonPci;
  UINT64 SizePrefetchable;
  UINT64 SizeNonPrefetchable;
  UINT64 SizeNonPciAbove4G;
  UINT64 AlignMask;
  UINT64 AlignMaskP;
  UINT64 AlignMaskNonPci;
  BOOLEAN EnoughSpaceAbove4G;
  BOOLEAN BigAlignFirst;
  FABRIC_MMIO_ABOVE_4G_QUEUE  MmioQueue[MMIO_QUEUE_SIZE];
  FABRIC_MMIO_ABOVE_4G_QUEUE  Temp;

  EnoughSpaceAbove4G = TRUE;
  BigAlignFirst = TRUE;
  AlignMaskNonPci = VH_NON_PCI_MMIO_ALIGN_MASK_ABOVE4G;
  MmioBaseAddrPrefetchable = 0;
  MmioBaseAddrNonPrefetchable = 0;
  MmioBaseAddrNonPci = 0;
  SizePrefetchable = 0;
  SizeNonPrefetchable = 0;
  SizeNonPciAbove4G = (PcdGet32 (PcdAmdAbove4GMmioSizePerRbForNonPciDevice) > MMIO_MIN_NON_PCI_SIZE_ABOVE4G) ? PcdGet32 (PcdAmdAbove4GMmioSizePerRbForNonPciDevice): MMIO_MIN_NON_PCI_SIZE_ABOVE4G;
  for (SktLoop = 0; SktLoop < SocketNumber; SktLoop++) {
    for (RbLoop = 0; RbLoop < RbsPerSocket; RbLoop++) {
      // Calculate reqiured size, it's for output parameter 'SpaceStatus'
      if (SpaceStatus != NULL) {
        SpaceStatus->MmioSizeAbove4G += MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size;
        SpaceStatus->MmioSizeBelow4G += (UINT32) (MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SktLoop][RbLoop].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SktLoop][RbLoop].Size);
      }

      // If there's no MMIO request for above 4G, try next one
      if ((MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size + MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size + SizeNonPciAbove4G) == 0) {
        continue;
      }

      AlignMask  = MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Alignment;
      AlignMaskP = MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Alignment;
      MmioBaseAddr = *MmioBaseAddrNextRb;

      // default sequence should be Non Pci -> Prefetchable -> Non Prefetchable
      // this would match the sequence used in FabricInitMmioEqually3 ()
      i = 0;
      MmioQueue[i].MmioType = NON_PCI_DEVICE_ABOVE_4G;
      MmioQueue[i++].AlignBit = AlignMaskNonPci;
      MmioQueue[i].MmioType = P_MMIO_ABOVE_4G;
      MmioQueue[i++].AlignBit = AlignMaskP;
      MmioQueue[i].MmioType = MMIO_ABOVE_4G;
      MmioQueue[i++].AlignBit = AlignMask;
      ASSERT (i <= MMIO_QUEUE_SIZE);

      if (BigAlignFirst) {
        // MmioQueue[0] has the biggest align bit
        for (i = 0; i < MMIO_QUEUE_SIZE; i++) {
          for (j = 0; j < (MMIO_QUEUE_SIZE - i - 1); j++) {
            if (MmioQueue[j].AlignBit < MmioQueue[j + 1].AlignBit) {
              Temp = MmioQueue[j + 1];
              MmioQueue[j + 1] = MmioQueue[j];
              MmioQueue[j] = Temp;
            }
          }
        }
      } else {
        // MmioQueue[0] has the smallest align bit (except align bit = 0)
        // always put MMIO region whose align bit is 0 on high address
        // this would match the algorithm used in FabricInitMmioEqually3 ()
        for (i = 0; i < MMIO_QUEUE_SIZE; i++) {
          for (j = 0; j < (MMIO_QUEUE_SIZE - i - 1); j++) {
            if (((MmioQueue[j].AlignBit > MmioQueue[j + 1].AlignBit) || (MmioQueue[j].AlignBit == 0)) &&
                (MmioQueue[j + 1].AlignBit != 0)) {
              Temp = MmioQueue[j + 1];
              MmioQueue[j + 1] = MmioQueue[j];
              MmioQueue[j] = Temp;
            }
          }
        }
      }
      BigAlignFirst = !BigAlignFirst;

      MmioBaseAddr = *MmioBaseAddrNextRb;
      for (i = 0; i < MMIO_QUEUE_SIZE; i++) {
        switch (MmioQueue[i].MmioType) {
        case MMIO_ABOVE_4G:
          MmioBaseAddrNonPrefetchable = (*MmioBaseAddrNextRb + AlignMask) & (~AlignMask);
          SizeNonPrefetchable = MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size;
          *MmioBaseAddrNextRb = MmioBaseAddrNonPrefetchable + SizeNonPrefetchable;
          break;
        case P_MMIO_ABOVE_4G:
          MmioBaseAddrPrefetchable = (*MmioBaseAddrNextRb + AlignMaskP) & (~AlignMaskP);
          SizePrefetchable = MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size;
          *MmioBaseAddrNextRb = MmioBaseAddrPrefetchable + SizePrefetchable;
          break;
        case NON_PCI_DEVICE_ABOVE_4G:
          MmioBaseAddrNonPci = (*MmioBaseAddrNextRb + AlignMaskNonPci) & (~AlignMaskNonPci);
          *MmioBaseAddrNextRb = MmioBaseAddrNonPci + SizeNonPciAbove4G;
          break;
        default:
          ASSERT (FALSE);
          break;
        };
      }

      if (SizeNonPrefetchable == 0) {
        MmioBaseAddrNonPrefetchable = 0;
      }
      if (SizePrefetchable == 0) {
        MmioBaseAddrPrefetchable = 0;
      }

      // Check if space is enough
      if (*MmioBaseAddrNextRb > MmioLimitAbove4G) {
        EnoughSpaceAbove4G = FALSE;
        IDS_HDT_CONSOLE (CPU_TRACE, "  No enough size above 4G\n");
      }

      if (SetDfRegisters && EnoughSpaceAbove4G && (FabricMmioManager != NULL)) {
        //   Set MMIO above 4G
        if ((MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size == 0) &&
            (MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size == 0) &&
            (SizeNonPciAbove4G == 0)) {
          continue;
        }

        IDS_HDT_CONSOLE (CPU_TRACE, "---Socket%x RootBridge%x---\n", SktLoop, RbLoop);
        IDS_HDT_CONSOLE (CPU_TRACE, "  Request above 4G\n        Prefetch Size 0x%lX, AlignBit 0x%X\n", MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size, MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Alignment);
        IDS_HDT_CONSOLE (CPU_TRACE, "    Non Prefetch Size 0x%lX, AlignBit 0x%X\n\n", MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Size, MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Alignment);
        if ((SktLoop == (SocketNumber - 1)) && (RbLoop == (RbsPerSocket - 1))) {
          // workaround to set last RootBridge's MMIO limit to 0xFFFF_FFFF_FFFF
          FabricSetMmioReg3 (SocketNumber, ((SktLoop * RbsPerSocket + RbLoop) * 2 + 1), SktLoop, RbLoop, MmioBaseAddr, (0x1000000000000 - MmioBaseAddr));
        } else {
          FabricSetMmioReg3 (SocketNumber, ((SktLoop * RbsPerSocket + RbLoop) * 2 + 1), SktLoop, RbLoop, MmioBaseAddr, (*MmioBaseAddrNextRb - MmioBaseAddr));
        }
        FabricMmioManager->AllocateMmioAbove4GOnThisRb[SktLoop][RbLoop] = TRUE;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BaseNonPci = MmioBaseAddrNonPci;  // don't have Non Pci MMIO for above 4G
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BasePrefetch = MmioBaseAddrPrefetchable;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BaseNonPrefetch = MmioBaseAddrNonPrefetchable;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizeNonPci = SizeNonPciAbove4G;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizePrefetch = SizePrefetchable;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizeNonPrefetch = SizeNonPrefetchable;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].UsedSizeNonPci = 0;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].UsedSizePrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].UsedSizeNonPrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].AlignNonPrefetch = MmioSizeForEachRb->NonPrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Alignment;
        FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].AlignPrefetch = MmioSizeForEachRb->PrefetchableMmioSizeAbove4G[SktLoop][RbLoop].Alignment;

        IDS_HDT_CONSOLE (CPU_TRACE, "    NonPci      0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BaseNonPci, (FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BaseNonPci + FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizeNonPci), FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizeNonPci);
        IDS_HDT_CONSOLE (CPU_TRACE, "    Prefetch    0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BasePrefetch, (FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BasePrefetch + FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizePrefetch), FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizePrefetch);
        IDS_HDT_CONSOLE (CPU_TRACE, "    NonPrefetch 0x%lX ~ 0x%lX, Size 0x%lX\n\n", FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BaseNonPrefetch, (FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].BaseNonPrefetch + FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizeNonPrefetch), FabricMmioManager->MmioRegionAbove4G[SktLoop][RbLoop].SizeNonPrefetch);
      }
    }
  }

  return EnoughSpaceAbove4G;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Try to arrange MMIO below 4G
 *
 *
 * @param[in]         MmioSizeForEachRb           Required MMIO size for each RootBridge
 * @param[in]         MmioBaseAddrAbovePcieCfg    MmioBaseAddrAbovePcieCfg
 * @param[in]         MmioLimitAbovePcieCfg       MmioLimitAbovePcieCfg
 * @param[in]         MmioBaseAddrBelowPcieCfg    MmioBaseAddrBelowPcieCfg
 * @param[in]         MmioLimitBelowPcieCfg       MmioLimitBelowPcieCfg
 * @param[in, out]    MmioIsAbovePcieCfg          An BOOLEAN array, indicate which RootBridge's MMIO is above Pcie Cfg
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbsPerSocket                RootBridge number per socket
 * @param[in]         PrimarySocket               Which socket has the primary root bridge
 * @param[in]         PrimaryRootBridge           Primary root bridge indxe
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
  IN       UINT8                          RbsPerSocket,
  IN       UINT8                          PrimarySocket,
  IN       UINT8                          PrimaryRootBridge,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  )
{
  UINT8   NumberOfRbBelowPcieCfg;
  BOOLEAN GetAnCombination;
  BOOLEAN NextCombination;

  GetAnCombination = FALSE;

  // Try to put 0 RootBridge, 1 RootBridge, 2 RootBridges... VH_MAX_SYSTEM_RB_COUNT RootBridges below Pcie Cfg
  for (NumberOfRbBelowPcieCfg = 0; NumberOfRbBelowPcieCfg <= (SocketNumber * RbsPerSocket); NumberOfRbBelowPcieCfg++) {
    // 1. Default, all RootBridges are above Pcie Cfg
    LibAmdMemFill (MmioIsAbovePcieCfg, TRUE, (sizeof (BOOLEAN) * (SSP_MAX_SOCKETS * SSP_MAX_DIES_PER_SOCKET * SSP_MAX_HOST_BRIDGES_PER_DIE)), NULL);
    NextCombination = TRUE;

    // 2. First, try to put RootBridge 7 to RootBridge (VH_MAX_SYSTEM_RB_COUNT - NumberOfRbBelowPcieCfg) below Pcie Cfg
    if (NumberOfRbBelowPcieCfg > 0 ) {
      LibAmdMemFill ((MmioIsAbovePcieCfg + (SocketNumber * RbsPerSocket) - NumberOfRbBelowPcieCfg), FALSE, (sizeof (BOOLEAN) * NumberOfRbBelowPcieCfg), NULL);
    }

    while (NextCombination) {
      if (((mEnoughAbovePcieSpaceForPrimaryRb) && (*(MmioIsAbovePcieCfg + PrimarySocket * VH_MAX_RB_PER_SOCKET + PrimaryRootBridge))) ||
          ((!mEnoughAbovePcieSpaceForPrimaryRb) && (!*(MmioIsAbovePcieCfg + PrimarySocket * VH_MAX_RB_PER_SOCKET + PrimaryRootBridge)))) {
        // 3. Try this combination
        GetAnCombination = TryThisCombination (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbsPerSocket, FabricMmioManager, FALSE);
        if (GetAnCombination) {
          break;
        }
      }
      // 4. If we can't make it, try to another combination
      NextCombination = GetNextCombination (NumberOfRbBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbsPerSocket);
    }
    if ((GetAnCombination) || (MmioLimitBelowPcieCfg == MmioBaseAddrBelowPcieCfg)) {
      // If we already got an combination or there's no space above Pcie Cfg, then break
      break;
    }

  }

  if (GetAnCombination) {
    TryThisCombination (MmioSizeForEachRb, MmioBaseAddrAbovePcieCfg, MmioLimitAbovePcieCfg, MmioBaseAddrBelowPcieCfg, MmioLimitBelowPcieCfg, MmioIsAbovePcieCfg, SocketNumber, RbsPerSocket, FabricMmioManager, SetDfRegisters);
  }

  return GetAnCombination;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Get a different combination
 *
 *
 * @param[in]         NumberOfRbBelowPcieCfg      How many RootBridges MMIO should be put below Pcie Cfg
 * @param[in, out]    MmioIsAbovePcieCfg          An BOOLEAN array, indicate which RootBridge's MMIO is above Pcie Cfg
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbsPerSocket                RootBridge number per socket
 *
 * @retval            TRUE                        Get a combination
 *                    FALSE                       All combinations have been tried
 */
BOOLEAN
GetNextCombination (
  IN       UINT8                          NumberOfRbBelowPcieCfg,
  IN OUT   BOOLEAN                       *MmioIsAbovePcieCfg,
  IN       UINT8                          SocketNumber,
  IN       UINT8                          RbsPerSocket
  )
{
  UINT8  MoveThisOne;
  UINT8  ResetTheseRbs;

  // From RootBridge 0, there're total number of 'ResetTheseRbs' sequential RootBridge, whose MMIO is below Pcie Cfg
  for (ResetTheseRbs = 0; ResetTheseRbs < NumberOfRbBelowPcieCfg; ResetTheseRbs++) {
    if (*(MmioIsAbovePcieCfg + ResetTheseRbs) == TRUE) {
      break;
    }
  }

  // if ResetTheseRbs == NumberOfRbBelowPcieCfg
  // All combinations have been tried.
  if (ResetTheseRbs == NumberOfRbBelowPcieCfg) {
    return FALSE;
  }

  // After number of ResetTheseRbs RootBridges, find out the first RootBridge whose MMIO is below Pcie Cfg.
  for (MoveThisOne = ResetTheseRbs + 1; MoveThisOne < (SocketNumber * RbsPerSocket); MoveThisOne++) {
    if (*(MmioIsAbovePcieCfg + MoveThisOne) == FALSE) {
      break;
    }
  }
  ASSERT (MoveThisOne < (SocketNumber * RbsPerSocket));
  *(MmioIsAbovePcieCfg + MoveThisOne) = TRUE;
  *(MmioIsAbovePcieCfg + MoveThisOne - 1) = FALSE;
  LibAmdMemFill (MmioIsAbovePcieCfg, TRUE, (sizeof (BOOLEAN) * ResetTheseRbs), NULL);
  LibAmdMemFill ((MmioIsAbovePcieCfg + MoveThisOne - 1 - ResetTheseRbs), FALSE, (sizeof (BOOLEAN) * ResetTheseRbs), NULL);

  return TRUE;
}

/*---------------------------------------------------------------------------------------*/
/**
 * If there's enough space for current combination
 *
 *
 * @param[in]         MmioSizeForEachRb           Required MMIO size for each RootBridge
 * @param[in]         MmioBaseAddrAbovePcieCfg    MmioBaseAddrAbovePcieCfg
 * @param[in]         MmioLimitAbovePcieCfg       MmioLimitAbovePcieCfg
 * @param[in]         MmioBaseAddrBelowPcieCfg    MmioBaseAddrBelowPcieCfg
 * @param[in]         MmioLimitBelowPcieCfg       MmioLimitBelowPcieCfg
 * @param[in, out]    MmioIsAbovePcieCfg          An BOOLEAN array, indicate which RootBridge's MMIO is above Pcie Cfg
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbsPerSocket                RootBridge number per socket
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
  IN       UINT8                          RbsPerSocket,
  IN       FABRIC_MMIO_MANAGER           *FabricMmioManager,
  IN       BOOLEAN                        SetDfRegisters
  )
{
  UINT8  i;
  UINT8  j;
  UINT8  SocketLoop;
  UINT8  RbLoop;
  UINTN  PrimarySocket;
  UINTN  PrimaryRootBridge;
  UINT64 MmioBaseAddr; // To caculate oversize, we must use UINT64 here for all address, size
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
  SizeNonPci = PcdGet32 (PcdAmdMmioSizePerRbForNonPciDevice);
  AlignMaskNonPci = VH_NON_PCI_MMIO_ALIGN_MASK;
  AlignForFirstMmioRegionAbovePcieCfg = 0;
  AlignForFirstMmioRegionBelowPcieCfg = 0;

  FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

  BottomOfCompat = BOTTOM_OF_COMPAT;
  /// @todo For ZP B2 and later, 0xFED0_0000 ~ 0xFED0_FFFF should be POSTED
  /// @todo BottomOfCompat = ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END + 1;
  ReservedRegionAlreadySet = FALSE;  // Indicate if PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat is set

  for (i = 0; i <= (SocketNumber * RbsPerSocket); i++) {
    SocketLoop = (SocketNumber * RbsPerSocket - i - 1) / RbsPerSocket;
    RbLoop = (SocketNumber * RbsPerSocket - i - 1) % RbsPerSocket;

    // Skip allocating MMIO for primary RootBridge, and will allocate later
    if ((SocketLoop == PrimarySocket) && (RbLoop == PrimaryRootBridge)) {
      continue;
    }

    // This is the last loop, now try to allocate MMIO for primary RootBridge
    if (i == (SocketNumber * RbsPerSocket)) {
      SocketLoop = (UINT8) PrimarySocket;
      RbLoop = (UINT8) PrimaryRootBridge;
    }

    if ((MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size + SizeNonPci) == 0) {
      continue;
    }

    AlignMask  = MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment;
    AlignMaskP = MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment;

    if (*(MmioIsAbovePcieCfg + SocketLoop * VH_MAX_RB_PER_SOCKET + RbLoop)) {
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
    if (*(MmioIsAbovePcieCfg + SocketLoop * VH_MAX_RB_PER_SOCKET + RbLoop)) {
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

    // (OverSize) && (Primary RootBridge has 2nd MMIO), try to see if moving primary RootBridge's Non-Pci MMIO from 1st region to 2nd region could work
    // Always put Non-Pci at top of 2nd MMIO
    if ((OverSizeFlag) && (SocketLoop == PrimarySocket) && (RbLoop == PrimaryRootBridge) && ((SocketNumber * RbsPerSocket) < (VH_MAX_RB_PER_SOCKET * VH_MAX_SOCKET))) {
      if (*(MmioIsAbovePcieCfg + SocketLoop * VH_MAX_RB_PER_SOCKET + RbLoop)) {
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

      // Adjust MmioBaseAddrNonPrefetchable & MmioBaseAddrPrefetchable if we move primary RootBridge's NON-PCI from 1st region to 2nd region and NON-PCI is at lower address
      if (PrimaryRbNonPciMmioAt2ndRegion && (!BigAlignFirst)) {
        MmioBaseAddrNonPrefetchable -= DeltaSize;
        MmioBaseAddrPrefetchable -= DeltaSize;
      }
    }

    // Set DF MMIO registers
    if ((!OverSizeFlag) && SetDfRegisters && (FabricMmioManager != NULL)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "---Socket%x RootBridge%x---\n", SocketLoop, RbLoop);
      IDS_HDT_CONSOLE (CPU_TRACE, "  Request below 4G\n        Prefetch Size 0x%lX, AlignBit 0x%X\n", MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size, MmioSizeForEachRb->PrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment);
      IDS_HDT_CONSOLE (CPU_TRACE, "    Non Prefetch Size 0x%lX, AlignBit 0x%X\n\n", MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Size, MmioSizeForEachRb->NonPrefetchableMmioSizeBelow4G[SocketLoop][RbLoop].Alignment);
      ASSERT (BottomOfCompat >= PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb));

      if ((SocketLoop == PrimarySocket) && (RbLoop == PrimaryRootBridge)) {
        if (*(MmioIsAbovePcieCfg + SocketLoop * VH_MAX_RB_PER_SOCKET + RbLoop)) {
          FabricSetMmioReg3 (SocketNumber, ((SocketLoop * RbsPerSocket + RbLoop) * 2), SocketLoop, RbLoop, MmioBaseAddr, (BottomOfCompat - MmioBaseAddr));
          MmioBaseAddrAbovePcieCfg = BottomOfCompat;
          ReservedRegionAlreadySet = TRUE;
        } else {
          FabricSetMmioReg3 (SocketNumber, ((SocketLoop * RbsPerSocket + RbLoop) * 2), SocketLoop, RbLoop, MmioBaseAddr, (MmioLimitBelowPcieCfg - MmioBaseAddr));
          MmioBaseAddrBelowPcieCfg = MmioLimitBelowPcieCfg;
        }
      } else {
        FabricSetMmioReg3 (SocketNumber, ((SocketLoop * RbsPerSocket + RbLoop) * 2), SocketLoop, RbLoop, MmioBaseAddr, (MmioCeiling - MmioBaseAddr));
      }

      FabricMmioManager->AllocateMmioBelow4GOnThisRb[SocketLoop][RbLoop] = TRUE;
      if ((SocketLoop == PrimarySocket) && (RbLoop == PrimaryRootBridge) && PrimaryRbNonPciMmioAt2ndRegion) {
        IDS_HDT_CONSOLE (CPU_TRACE, "    NON-PCI MMIO of Primary RootBridge has been moved to its 2nd region\n");
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

      IDS_HDT_CONSOLE (CPU_TRACE, "    Prefetch    0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BasePrefetch, (FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BasePrefetch + FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizePrefetch), FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizePrefetch);
      IDS_HDT_CONSOLE (CPU_TRACE, "    NonPrefetch 0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPrefetch, (FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPrefetch + FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPrefetch), FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPrefetch);
      IDS_HDT_CONSOLE (CPU_TRACE, "    NonPci      0x%lX ~ 0x%lX, Size 0x%lX\n\n", FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPci, (FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].BaseNonPci + FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPci), FabricMmioManager->MmioRegionBelow4G[SocketLoop][RbLoop].SizeNonPci);
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

  // Primary RootBridge's 2nd MMIO
  if ((!OverSizeFlag) && SetDfRegisters && (FabricMmioManager != NULL)) {
    if (((MmioBaseAddrAbovePcieCfg + VH_MMIO_MIN_SIZE) <= MmioLimitAbovePcieCfg) || ((MmioBaseAddrBelowPcieCfg + VH_MMIO_MIN_SIZE) <= MmioLimitBelowPcieCfg)) {
      if ((MmioSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size != 0) || (MmioSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size != 0) || PrimaryRbNonPciMmioAt2ndRegion) {
        if ((SocketNumber * RbsPerSocket) < (VH_MAX_RB_PER_SOCKET * VH_MAX_SOCKET)) {
          for (i = 0; i < VH_MAX_SOCKET; i++) {
            for (j = 0; j < VH_MAX_RB_PER_SOCKET; j++) {
              if (FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] == FALSE) {
                IDS_HDT_CONSOLE (CPU_TRACE, "  Primary RB has 2nd MMIO below 4G\n");
                FabricMmioManager->PrimaryRb2ndMmioPairBelow4G = (UINT8) ((i << 4) | j);
                if (MmioBaseAddrAbovePcieCfg < MmioLimitAbovePcieCfg) {
                  FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), PrimarySocket, PrimaryRootBridge, MmioBaseAddrAbovePcieCfg, (BottomOfCompat - MmioBaseAddrAbovePcieCfg));
                  MmioBaseAddr = MmioBaseAddrAbovePcieCfg;
                  PrimaryRbSecondMmioSize = MmioLimitAbovePcieCfg - MmioBaseAddrAbovePcieCfg;
                  ReservedRegionAlreadySet = TRUE;
                } else {
                  FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), PrimarySocket, PrimaryRootBridge, MmioBaseAddrBelowPcieCfg, (MmioLimitBelowPcieCfg - MmioBaseAddrBelowPcieCfg));
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
                // Distribute Primary RB's 2nd MMIO base on user request
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

                IDS_HDT_CONSOLE (CPU_TRACE, "    Prefetch    0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch, (FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch), FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch);
                IDS_HDT_CONSOLE (CPU_TRACE, "    NonPrefetch 0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch, (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch), FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch);
                IDS_HDT_CONSOLE (CPU_TRACE, "    NonPci      0x%lX ~ 0x%lX, Size 0x%lX\n\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci, (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci + FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci), FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci);

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
    FabricAdditionalMmioSetting3 (FabricMmioManager, SocketNumber, RbsPerSocket, BottomOfCompat, ReservedRegionAlreadySet);
  }

  return (!OverSizeFlag);
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricAdditionalMmioSetting3
 *
 * If reserved region for primary RB (PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat) has not been set,
 * or that region doesn't include ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_START ~ ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END,
 * set ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_START ~ ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END as POSTED
 *
 * @param[in, out]    FabricMmioManager           Point to FABRIC_MMIO_MANAGER
 * @param[in]         SocketNumber                System socket count
 * @param[in]         RbsPerSocket                RootBridge number per socket
 * @param[in]         BottomOfCompat              From BottomOfCompat to 4G is COMPAT region
 * @param[in]         ReservedRegionAlreadySet    PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat has been set or not
 *
 */
VOID
FabricAdditionalMmioSetting3 (
  IN       FABRIC_MMIO_MANAGER *FabricMmioManager,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbsPerSocket,
  IN       UINT64               BottomOfCompat,
  IN       BOOLEAN              ReservedRegionAlreadySet
  )
{
  UINT8   i;
  UINT8   j;
  UINT64  Base;
  UINT64  Size;
  UINTN   PrimarySocket;
  UINTN   PrimaryRootBridge;
  BOOLEAN AlreadySet;

  FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

  AlreadySet = FALSE;
  Base = ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_START;
  Size = ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END - ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_START + 1;

  // If reserved region for primary RB (PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat) has not been set
  // or that region doesn't include ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_START ~ ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END
  if ((!ReservedRegionAlreadySet) ||
      ((ReservedRegionAlreadySet) && (BottomOfCompat <= ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END))) {
    if (Size >= VH_MMIO_MIN_SIZE) {
      for (i = 0; i < VH_MAX_SOCKET; i++) {
        for (j = 0; j < VH_MAX_RB_PER_SOCKET; j++) {
          // Find out a spare MMIO register pair
          if (FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] == FALSE) {
            if ((FabricMmioManager->PrimaryRbHas2ndMmioBelow4G) &&
                (((FabricMmioManager->PrimaryRb2ndMmioPairBelow4G >> 4) & 0xF) == i) &&
                ((FabricMmioManager->PrimaryRb2ndMmioPairBelow4G & 0xF) == j)) {
              continue;
            }
            FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), PrimarySocket, PrimaryRootBridge, Base, Size);
            AlreadySet = TRUE;
            break;
          }

          if (FabricMmioManager->AllocateMmioAbove4GOnThisRb[i][j] == FALSE) {
            FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2 + 1), PrimarySocket, PrimaryRootBridge, Base, Size);
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
 * FabricSetMmioReg3
 *
 * Set MMIO register pairs according to input parameters
 *
 * @param[in]         TotalSocket                 System socket count
 * @param[in]         MmioPairIndex               Which MMIO register pair should be set
 * @param[in]         SktNum                      Socket number
 * @param[in]         RbNum                       Root bridge number
 * @param[in]         BaseAddress                 Base address of MMIO region
 * @param[in]         Length                      Length of MMIO region
 *
 */
VOID
FabricSetMmioReg3 (
  IN       UINT8  TotalSocket,
  IN       UINT8  MmioPairIndex,
  IN       UINTN  SktNum,
  IN       UINTN  RbNum,
  IN       UINT64 BaseAddress,
  IN       UINT64 Length
  )
{
  UINTN  i;
  UINTN  j;
  UINTN  DiePerSkt;
  MMIO_ADDR_CTRL MmioAddrCtrlReg;

  ASSERT (Length >= VH_MMIO_MIN_SIZE);
  BaseAddress = (BaseAddress + 0xFFFF) & 0xFFFFFFFFFFFF0000;

  MmioAddrCtrlReg.Value = 0;
  MmioAddrCtrlReg.Field.RE = 1;
  MmioAddrCtrlReg.Field.WE = 1;
  MmioAddrCtrlReg.Field.DstFabricID = (UINT32) FabricTopologyGetHostBridgeSystemFabricID (SktNum, 0, RbNum);

  for (i = 0; i < TotalSocket; i++) {
    DiePerSkt = FabricTopologyGetNumberOfDiesOnSocket (i);
    for (j = 0; j < DiePerSkt; j++) {
      FabricRegisterAccWrite (i, j, 0x0, (MMIO_BASE_ADDRESS_REG_0  + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC, (UINT32) (BaseAddress >> 16), TRUE);
      FabricRegisterAccWrite (i, j, 0x0, (MMIO_LIMIT_ADDRESS_REG_0 + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC, (UINT32) ((BaseAddress + Length - 1) >> 16), TRUE);
      FabricRegisterAccWrite (i, j, 0x0, (MMIO_ADDRESS_CONTROL_REG_0 + MmioPairIndex * 0x10), FABRIC_REG_ACC_BC, MmioAddrCtrlReg.Value, TRUE);
    }
  }
  IDS_HDT_CONSOLE (CPU_TRACE, "  AGESA set MMIO pair #%X, 0x%X0000 ~ 0x%XFFFF DstFabricID: 0x%X\n", MmioPairIndex, (UINT32) (BaseAddress >> 16), (UINT32) ((BaseAddress + Length - 1) >> 16), MmioAddrCtrlReg.Field.DstFabricID);
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetIoReg3
 *
 * Set IO register pairs according to input parameters
 *
 * @param[in]         TotalSocket                 System socket count
 * @param[in]         RegIndex                    Which IO register should be set
 * @param[in]         SktNum                      Socket number
 * @param[in]         RbNum                       Root bridge number
 * @param[in]         IoBase                      Base address of IO region
 * @param[in]         IoSize                      Length of IO region
 *
 */
VOID
FabricSetIoReg3 (
  IN       UINT8  TotalSocket,
  IN       UINT8  RegIndex,
  IN       UINTN   SktNum,
  IN       UINTN   RbNum,
  IN       UINT32 IoBase,
  IN       UINT32 IoSize
  )
{
  UINTN  i;
  UINTN  j;
  UINTN  DiePerSkt;
  X86IO_BASE_ADDR  IoBaseReg;
  X86IO_LIMIT_ADDR IoLimitReg;

  IoBaseReg.Value  = 0;
  IoLimitReg.Value = 0;
  IoLimitReg.Field.DstFabricID = (UINT32) FabricTopologyGetHostBridgeSystemFabricID (SktNum, 0, RbNum);

  for (i = 0; i < TotalSocket; i++) {
    DiePerSkt = FabricTopologyGetNumberOfDiesOnSocket (i);
    for (j = 0; j < DiePerSkt; j++) {
      IoBaseReg.Field.RE = 1;
      IoBaseReg.Field.WE = 1;
      IoBaseReg.Field.IOBase = (IoBase & 0xFFFFF000) >> 12;
      FabricRegisterAccWrite (i, j, 0x0, (X86IO_BASE_ADDRESS_REG0 + RegIndex * 8), FABRIC_REG_ACC_BC, IoBaseReg.Value, TRUE);

      IoLimitReg.Field.IOLimit = ((IoBase + IoSize - 1) & 0xFFFFF000) >> 12;
      FabricRegisterAccWrite (i, j, 0x0, (X86IO_LIMIT_ADDRESS_REG0 + RegIndex * 8), FABRIC_REG_ACC_BC, IoLimitReg.Value, TRUE);
    }
  }
  IDS_HDT_CONSOLE (CPU_TRACE, "  AGESA set IO pair #%X, 0x%X000 ~ 0x%XFFF DstFabricID: 0x%X\n", RegIndex, (UINT32) (IoBase >> 12), (UINT32) ((IoBase + IoSize - 1) >> 12), IoLimitReg.Field.DstFabricID);

}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricSetCfgAddrMapReg3
 *
 * Set MMIO register pairs according to input parameters
 *
 * @param[in]         TotalSocket                 System socket count
 * @param[in]         RbPerDie                    Rb count per Die
 * @param[in]         RegIndex                    Which CFG Addr Map register should be set
 * @param[in]         SktNum                      Socket number
 * @param[in]         RbNum                       Root bridge number
 * @param[in]         Base                        PCI bus base
 * @param[in]         Limit                       PCI bus Limit
 *
 */
VOID
FabricSetCfgAddrMapReg3 (
  IN       UINT8  TotalSocket,
  IN       UINT8  RbPerDie,
  IN       UINT8  RegIndex,
  IN       UINTN  SktNum,
  IN       UINTN  RbNum,
  IN       UINT16 Base,
  IN       UINT16 Limit
  )
{
  UINTN  i;
  UINTN  j;
  UINTN  DiePerSkt;
  CFG_ADDR_MAP CfgAddrMapReg;

  ASSERT (Base < 0x100);
  ASSERT (Limit < 0x100);

  CfgAddrMapReg.Value = 0;
  CfgAddrMapReg.Field.RE = 1;
  CfgAddrMapReg.Field.WE = 1;
  CfgAddrMapReg.Field.DstFabricID = (UINT32) FabricTopologyGetHostBridgeSystemFabricID (SktNum, (RbNum / RbPerDie), (RbNum % RbPerDie));
  CfgAddrMapReg.Field.BusNumBase = Base;
  CfgAddrMapReg.Field.BusNumLimit = Limit;

  for (i = 0; i < TotalSocket; i++) {
    DiePerSkt = FabricTopologyGetNumberOfDiesOnSocket (i);
    for (j = 0; j < DiePerSkt; j++) {
      FabricRegisterAccWrite (i, j, 0x0, (CFG_ADDR_MAP_REG0  + RegIndex * 4), FABRIC_REG_ACC_BC, CfgAddrMapReg.Value, TRUE);
    }
  }
  IDS_HDT_CONSOLE (CPU_TRACE, "  AGESA set CfgAddrMap #%X, 0x%2X ~ 0x%2X DstFabricID: 0x%X\n", RegIndex, CfgAddrMapReg.Field.BusNumBase, CfgAddrMapReg.Field.BusNumLimit, CfgAddrMapReg.Field.DstFabricID);
}

VOID
FabricGetPrimayRb (
  IN       UINTN *SocketNum,
  IN       UINTN *RootBridgeNum
  )
{
  ROOT_BRIDGE_LOCATION Location;

  if (FabricTopologyGetSystemComponentRootBridgeLocation (PrimaryFch, &Location)) {
    *SocketNum = Location.Socket;
    *RootBridgeNum = Location.Index;
  } else {
    *SocketNum = 0;
    *RootBridgeNum = 0;
  }
}

VOID
FabricGetPhySktRbNum (
  IN       UINTN LogSktNum,
  IN       UINTN LogRbNum,
  IN       UINTN *PhySktNum,
  IN       UINTN *PhyRbNum
  )
{
  UINTN i;
  UINTN j;
  UINTN k;
  UINTN SysRbCount;
  UINTN SocketCount;
  UINTN DieCount;
  UINTN RbCount;
  UINTN RbNumInSkt;
  FABRIC_RB_LOG_TO_PHY_MAP Temp;

  if (!mLogToPhyMapInit) {
    SysRbCount = 0;
    SocketCount = FabricTopologyGetNumberOfProcessorsPresent ();
    for (i = 0; i < SocketCount; i++) {
      RbNumInSkt = 0;
      DieCount = FabricTopologyGetNumberOfDiesOnSocket (i);
      for (j = 0; j < DieCount; j++) {
        RbCount = FabricTopologyGetNumberOfRootBridgesOnDie (i, j);
        for (k = 0; k < RbCount; k++) {
          mLogToPhyMap[SysRbCount].PhySktNum = i;
          mLogToPhyMap[SysRbCount].PhyRbNum = RbNumInSkt;
          mLogToPhyMap[SysRbCount].PciBusBase = FabricTopologyGetHostBridgeBusBase (i, j, k);
          mLogToPhyMap[SysRbCount].PciBusLimit = FabricTopologyGetHostBridgeBusLimit (i, j, k);
          if ((mLogToPhyMap[SysRbCount].PciBusLimit > 256) ||
              (mLogToPhyMap[SysRbCount].PciBusBase >  256) ||
              (mLogToPhyMap[SysRbCount].PciBusBase > mLogToPhyMap[SysRbCount].PciBusLimit)) {
            mLogToPhyMap[SysRbCount].PciBusBase = 0xFFFFFFFF;
            mLogToPhyMap[SysRbCount].PciBusLimit = 0;
          }

          RbNumInSkt++;
          SysRbCount++;
        }
      }
    }

    for (i = 0; i < SysRbCount; i++) {
      for (j = (SysRbCount - 1); j > i; j--) {
        if (mLogToPhyMap[j].PciBusBase < mLogToPhyMap[j - 1].PciBusBase) {
          Temp.PhySktNum = mLogToPhyMap[j].PhySktNum;
          Temp.PhyRbNum = mLogToPhyMap[j].PhyRbNum;
          Temp.PciBusBase = mLogToPhyMap[j].PciBusBase;
          Temp.PciBusLimit = mLogToPhyMap[j].PciBusLimit;

          mLogToPhyMap[j].PhySktNum = mLogToPhyMap[j - 1].PhySktNum;
          mLogToPhyMap[j].PhyRbNum = mLogToPhyMap[j - 1].PhyRbNum;
          mLogToPhyMap[j].PciBusBase = mLogToPhyMap[j - 1].PciBusBase;
          mLogToPhyMap[j].PciBusLimit = mLogToPhyMap[j - 1].PciBusLimit;

          mLogToPhyMap[j - 1].PhySktNum = Temp.PhySktNum;
          mLogToPhyMap[j - 1].PhyRbNum = Temp.PhyRbNum;
          mLogToPhyMap[j - 1].PciBusBase = Temp.PciBusBase;
          mLogToPhyMap[j - 1].PciBusLimit = Temp.PciBusLimit;
        }
      }
    }
    mLogToPhyMapInit = TRUE;
  }

  RbNumInSkt = FabricTopologyGetNumberOfRootBridgesOnSocket (0);
  *PhySktNum = mLogToPhyMap[LogSktNum * RbNumInSkt + LogRbNum].PhySktNum;
  *PhyRbNum = mLogToPhyMap[LogSktNum * RbNumInSkt + LogRbNum].PhyRbNum;
  IDS_HDT_CONSOLE (CPU_TRACE, "  Logical Socket %x, Rb %x is Physical Socket%x, Rb %x\n", LogSktNum, LogRbNum, *PhySktNum, *PhyRbNum);
}

CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FindIomsMap3 (
  IN       UINTN               Socket,
  IN       UINTN               Die
  )
{
  UINTN                                      i;
  CONST AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP  *DeviceMap;

  DeviceMap = FabricTopologyGetDeviceMapOnDie (Socket, Die);
  for (i = 0; DeviceMap[i].Type < FabricDeviceTypeMax; i++) {
    if (DeviceMap[i].Type == Ioms) {
      break;
    }
  }

  if (DeviceMap[i].Type == Ioms) {
    return &DeviceMap[i];
  } else {
    return NULL;
  }
}

