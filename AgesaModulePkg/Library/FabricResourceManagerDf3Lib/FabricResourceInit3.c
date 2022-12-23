/* $NoKeywords:$ */
/**
 * @file
 *
 * Base Fabric MMIO map manager Lib implementation for DF3
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
#include <Library/AmdS3SaveLib.h>
#include <Library/AmdHeapLib.h>
#include <Protocol/FabricResourceManagerServicesProtocol.h>
#include <Library/FabricResourceSizeForEachRbLib.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include "FabricResourceManager3.h"

#define FILECODE LIBRARY_FABRICRESOURCEMANAGERDF3LIB_FABRICRESOURCEINIT3_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
FabricCheckResourceValid (
  IN       FABRIC_RESOURCE_FOR_EACH_RB  *ResourceSizeForEachRb
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * FabricResourceInit
 *
 * Initialize DF resource registers for each RootBridge.
 *
 */
EFI_STATUS
FabricResourceInit (
  )
{
  UINT8                         SocketNumber;
  UINT8                         RbsPerSocket;
  UINT8                        *ResourceDefaultMap;
  BOOLEAN                       SetResourceBaseOnNv;
  EFI_STATUS                    Status;
  EFI_STATUS                    CalledStatus;
  FABRIC_RESOURCE_FOR_EACH_RB   ResourceSizeForEachRb;
  FABRIC_MMIO_MANAGER          *FabricMmioManager;
  FABRIC_IO_MANAGER            *FabricIoManager;
  ALLOCATE_HEAP_PARAMS          AllocateHeapParams;

  Status = EFI_SUCCESS;
  CalledStatus = EFI_SUCCESS;
  FabricMmioManager = NULL;
  FabricIoManager = NULL;

  SocketNumber = (UINT8) FabricTopologyGetNumberOfProcessorsPresent ();
  RbsPerSocket = (UINT8) FabricTopologyGetNumberOfRootBridgesOnSocket (0);

  SetResourceBaseOnNv = FALSE;

  ResourceDefaultMap = (UINT8 *) (UINTN) (PcdGet64 (PcdAmdFabricResourceDefaultSizePtr));

  if (!PcdGetBool (PcdAmdFabricResourceDefaultMap)) {
    // If user doesn't force to use default map, try to get resource map from NV first
    if (FabricGetResourceSizeForEachRb (&ResourceSizeForEachRb) == EFI_SUCCESS) {
      SetResourceBaseOnNv = TRUE;
    } else {
    // Secondary, check PCD
      if (ResourceDefaultMap != NULL) {
        SetResourceBaseOnNv = TRUE;
        LibAmdMemCopy (&ResourceSizeForEachRb, ResourceDefaultMap, sizeof (FABRIC_RESOURCE_FOR_EACH_RB), NULL);
      }
    }
  } else {
    // If user force to use default map, check PCD first, if user doesn't have a default resource map, init MMIO/IO equally
    if (ResourceDefaultMap != NULL) {
      SetResourceBaseOnNv = TRUE;
      LibAmdMemCopy (&ResourceSizeForEachRb, ResourceDefaultMap, sizeof (FABRIC_RESOURCE_FOR_EACH_RB), NULL);
    }
  }

  // Check ResourceSizeForEachRb
  if (SetResourceBaseOnNv) {
    FabricCheckResourceValid (&ResourceSizeForEachRb);
  }

  AllocateHeapParams.RequestedBufferSize = sizeof (FABRIC_MMIO_MANAGER);
  AllocateHeapParams.BufferHandle        = AMD_MMIO_MANAGER;
  AllocateHeapParams.Persist             = HEAP_SYSTEM_MEM;
  if (HeapAllocateBuffer (&AllocateHeapParams, NULL) == AGESA_SUCCESS) {
    FabricMmioManager = (FABRIC_MMIO_MANAGER *) AllocateHeapParams.BufferPtr;
  }

  AllocateHeapParams.RequestedBufferSize = sizeof (FABRIC_IO_MANAGER);
  AllocateHeapParams.BufferHandle        = AMD_IO_MANAGER;
  AllocateHeapParams.Persist             = HEAP_SYSTEM_MEM;
  if (HeapAllocateBuffer (&AllocateHeapParams, NULL) == AGESA_SUCCESS) {
    FabricIoManager = (FABRIC_IO_MANAGER *) AllocateHeapParams.BufferPtr;
  }

  if  (FabricMmioManager != NULL) {
    if (SetResourceBaseOnNv) {
      // Get NvVariable successfully, try to init MMIO base on it
      IDS_HDT_CONSOLE (CPU_TRACE, "  Init MMIO based on NV variable\n");
      CalledStatus = FabricInitMmioBasedOnNvVariable3 (FabricMmioManager, &ResourceSizeForEachRb, NULL, SocketNumber, RbsPerSocket, TRUE);
    }
    if ((CalledStatus != EFI_SUCCESS) || (!SetResourceBaseOnNv)) {
      // Can't get NvVariable or init MMIO based on NVVariable failed
      IDS_HDT_CONSOLE (CPU_TRACE, "  Init MMIO equally\n");
      CalledStatus = FabricInitMmioEqually3 (FabricMmioManager, SocketNumber, RbsPerSocket);
      Status = (CalledStatus > Status) ? CalledStatus : Status;
    }
  } else {
    Status = EFI_ABORTED;
  }

  if  (FabricIoManager != NULL) {
    if (SetResourceBaseOnNv) {
      // Get NvVariable successfully, try to init IO base on it
      IDS_HDT_CONSOLE (CPU_TRACE, "  Init IO based on NV variable\n");
      CalledStatus = FabricInitIoBasedOnNvVariable3 (FabricIoManager, &ResourceSizeForEachRb, NULL, SocketNumber, RbsPerSocket, TRUE);
    }
    if ((CalledStatus != EFI_SUCCESS) || (!SetResourceBaseOnNv)) {
      // Can't get NvVariable or init IO based on NVVariable failed
      IDS_HDT_CONSOLE (CPU_TRACE, "  Init IO equally\n");
      CalledStatus = FabricInitIoEqually3 (FabricIoManager, SocketNumber, RbsPerSocket);
      Status = (CalledStatus > Status) ? CalledStatus : Status;
    }
  } else {
    Status = EFI_ABORTED;
  }

  if (SetResourceBaseOnNv) {
    CalledStatus = FabricInitPciBusBasedOnNvVariable3 (&ResourceSizeForEachRb, SocketNumber, RbsPerSocket);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  }

  return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitMmioEqually3
 *
 * Initialize MMIO registers for each RootBridge evenly.
 *
 * @param[in, out]    FabricMmioManager        Point to FABRIC_MMIO_MANAGER
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbsPerSocket             RootBridge number per socket
 *
 */
EFI_STATUS
FabricInitMmioEqually3 (
  IN       FABRIC_MMIO_MANAGER *FabricMmioManager,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbsPerSocket
  )
{
  UINT8  i;
  UINT8  j;
  UINT8  SystemRbNumber;
  UINT8  RbNumberAbovePcieCfg;
  UINT8  RbNumberAbovePcieCfgCopy;
  UINT8  RbNumberMmioHasInitialized;
  UINT64 TotalAvailableSize;
  UINT64 SizeAbovePcieCfg;
  UINT64 SizeBelowPcieCfg;
  UINT64 MmioBaseAddr;
  UINT64 MmioSize;
  UINT64 MmioSize16MAligned;
  UINT64 MmioSizeRemained;
  UINT64 MmioLimitAbove4G;
  UINT64 TOM;
  UINT64 TOM2;
  UINT64 PciCfgSpace;
  UINT64 BottomOfCompat;
  UINT64 MmioSizeBelowHole;
  UINT64 MmioSizeAboveHole;
  UINTN  PrimarySocket;
  UINTN  PrimaryRootBridge;
  BOOLEAN AbovePcieCfgIsTooSmall;
  BOOLEAN BelowPcieCfgIsTooSmall;
  BOOLEAN ReservedRegionAlreadySet;

  FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

  SystemRbNumber = RbsPerSocket * SocketNumber;
  BottomOfCompat = BOTTOM_OF_COMPAT;
  /// @todo For ZP B2 and later, 0xFED0_0000 ~ 0xFED0_FFFF should be POSTED
  /// @todo BottomOfCompat = ADDITIONAL_POSTED_REGION_UNDER_PRIMARY_RB_END + 1;
  ReservedRegionAlreadySet = FALSE;  // Indicate if PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat is set

  // System information
  PciCfgSpace = (AsmReadMsr64 (0xC0010058) >> 2) & 0xF;                   // Get bus range from MSR_C001_0058[5:2][BusRange]
  PciCfgSpace = MultU64x64 (((UINT64) 1 << PciCfgSpace), (1024 * 1024));  // The size of configuration space is 1MB times the number of buses
  TOM = AsmReadMsr64 (0xC001001A);
  TOM2 = AsmReadMsr64 (0xC001001D);
  IDS_HDT_CONSOLE (CPU_TRACE, "  TOM: 0x%lX, TOM2: 0x%lX, Pcie configuration space: 0x%lX ~ 0x%lX\n", TOM, TOM2, PcdGet64 (PcdPciExpressBaseAddress), (PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace));

  // Below 4G
  //    +---------------------------------+ +--+ 4G
  //    |  BIOS FW                        |
  //    |  Local APIC and etc.            |          Leave as undescribed, so it's a COMPAT region
  //    |       Undescribed               |
  //    +---------------------------------+ +--+ 0xFEC0_0000 (BottomOfCompat), from TOM to BottomOfCompat is MMIO space
  //    |  Reserved for Primary RootBridge|          Reserved this region for some devices which need a fixed MMIO space
  //    +---------------------------------+ +--+ 0xFE00_0000 (PcdAmdBottomMmioReservedForPrimaryRb), from TOM to PcdAmdBottomMmioReservedForPrimaryRb is the region that AllocateMmio function could use
  //    |  MMIO Above PCIe Cfg            |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+ +--+ PcdPciExpressBaseAddress + Size (defined by MSR_C001_0058[5:2][BusRange])
  //    |  PCIe Configuration Space       |
  //    |                                 |
  //    +---------------------------------+ +--+ PcdPciExpressBaseAddress (recommend to set PcdPciExpressBaseAddress equal to TOM)
  //    |                                 |
  //    |  MMIO Below PCIe Cfg            |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+ +--+ TOM
  //    |                                 |
  //    |  DRAM                           |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+ +--+ 0x0000_0000

  // Above 4G
  //    +---------------------------------+ +--+ 0xFFFD_0000_0000 (2^48 - 12G) or 0x7FD_0000_0000 (8T - 12G)
  //    |                                 |
  //    |   MMIO FOR RootBridge 7         |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+
  //    |                                 |
  //    |   ......                        |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+
  //    |                                 |
  //    |   MMIO FOR RootBridge 2         |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+
  //    |                                 |
  //    |   MMIO FOR RootBridge 1         |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+
  //    |                                 |
  //    |   MMIO FOR RootBridge 0         |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    |                                 |
  //    +---------------------------------+ +--+ TOM2 or 0x100_0000_0000

  AbovePcieCfgIsTooSmall = FALSE;
  BelowPcieCfgIsTooSmall = FALSE;

  ASSERT (PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb) >= (PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace));
  ASSERT (PcdGet64 (PcdPciExpressBaseAddress) >= TOM);
  ASSERT (BottomOfCompat >= PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb));

  SizeAbovePcieCfg = PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb) - PcdGet64 (PcdPciExpressBaseAddress) - PciCfgSpace;
  SizeBelowPcieCfg = PcdGet64 (PcdPciExpressBaseAddress) - TOM;
  TotalAvailableSize = SizeAbovePcieCfg + SizeBelowPcieCfg;

  if (SystemRbNumber > 1) {
    // For single RootBridge system, we don't want to check MMIO size above/below PcieCfg

    MmioSize = DivU64x32 (SizeBelowPcieCfg, SystemRbNumber);
    if (SizeAbovePcieCfg < DivU64x32 (MultU64x64 (MmioSize, 8), 10)) {
      // If SizeAbovePcieCfg < 80% of (SizeBelowPcieCfg / SystemRbNumber), ignore this region
      AbovePcieCfgIsTooSmall = TRUE;
      TotalAvailableSize -= SizeAbovePcieCfg;
      IDS_HDT_CONSOLE (CPU_TRACE, "  AbovePcieCfgIsTooSmall\n");
    }

    MmioSize = DivU64x32 (SizeAbovePcieCfg, SystemRbNumber);
    if (SizeBelowPcieCfg < DivU64x32 (MultU64x64 (MmioSize, 8), 10)) {
      // If SizeBelowPcieCfg < 80% of (SizeAbovePcieCfg / SystemRbNumber), ignore this region
      BelowPcieCfgIsTooSmall = TRUE;
      TotalAvailableSize -= SizeBelowPcieCfg;
      IDS_HDT_CONSOLE (CPU_TRACE, "  BelowPcieCfgIsTooSmall\n");
    }
    ASSERT (TotalAvailableSize != 0);
  }
  MmioSize = DivU64x32 (TotalAvailableSize, SystemRbNumber);
  MmioSize16MAligned = MmioSize & SIZE_16M_ALIGN;
  ASSERT ((!AbovePcieCfgIsTooSmall) || (!BelowPcieCfgIsTooSmall));

  // Setup MMIO below 4G
  MmioBaseAddr = 0;
  if (!AbovePcieCfgIsTooSmall) {
    //   1. find out how many RootBridges would have MMIO above PCIe Configuration Space
    RbNumberAbovePcieCfg = (UINT8) DivU64x32 (SizeAbovePcieCfg, (UINT32) MmioSize);
    if ((SizeAbovePcieCfg - MultU64x64 (MmioSize, RbNumberAbovePcieCfg)) > DivU64x32 (MmioSize, 2)) {
      RbNumberAbovePcieCfg++;
    }
    if (RbNumberAbovePcieCfg == 0) {
      // it could make sure single RootBridge system would always set the space above PcieCfg as MMIO in step 3
      RbNumberAbovePcieCfg++;
    }
    MmioSize = DivU64x32 (SizeAbovePcieCfg, RbNumberAbovePcieCfg);
    MmioSize16MAligned = MmioSize & SIZE_16M_ALIGN;
    MmioSizeRemained = SizeAbovePcieCfg - MultU64x64 (MmioSize16MAligned, (RbNumberAbovePcieCfg - 1));
    MmioBaseAddr = PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb);
  } else {
    //   2. if there's no MMIO above PCIe Configuration Space,
    RbNumberAbovePcieCfg = 0;
    MmioSizeRemained = SizeBelowPcieCfg - MultU64x64 (MmioSize16MAligned, (SystemRbNumber - 1));
    MmioBaseAddr = PcdGet64 (PcdPciExpressBaseAddress);
  }

  RbNumberAbovePcieCfgCopy = RbNumberAbovePcieCfg;
  //   3. allocate MMIO for primary RootBridge first, make sure it's always on top
  i = (UINT8) PrimarySocket;
  j = (UINT8) PrimaryRootBridge;
  FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] = TRUE;

  if (RbNumberAbovePcieCfg != 0) {
    // above PCIe Configuration Space
    MmioBaseAddr = MmioBaseAddr - MmioSizeRemained;
    RbNumberAbovePcieCfg--;
  } else if (!BelowPcieCfgIsTooSmall) {
    // below PCIe Configuration Space
    MmioBaseAddr = MmioBaseAddr - MmioSizeRemained;
  } else {
    ASSERT (FALSE);
  }

  if (!AbovePcieCfgIsTooSmall) {
    // if primary RootBridge's MMIO is above PCIe Configuration Space, include PcdAmdBottomMmioReservedForPrimaryRb ~ BottomOfCompat as well
    FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), i, j, MmioBaseAddr, (MmioSizeRemained + BottomOfCompat - PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb)));
    ReservedRegionAlreadySet = TRUE;
  } else {
    FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), i, j, MmioBaseAddr, MmioSizeRemained);
  }
  // Prefetchable -> Non Prefetchable -> Non Pci
  // Prefetchable/Non Prefetchable 80/20 Ratio
  FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci = PcdGet32 (PcdAmdMmioSizePerRbForNonPciDevice);
  FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch = (DivU64x32 (MultU64x64 ((MmioSizeRemained - FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci), 4), 5)) & SIZE_16M_ALIGN;
  FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch = MmioBaseAddr;
  FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch = FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch;
  FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci = (MmioBaseAddr + MmioSizeRemained - FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci) & (~VH_NON_PCI_MMIO_ALIGN_MASK);
  FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch = FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci - FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch;
  FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPci = 0;
  FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizePrefetch = 0;
  FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPrefetch = 0;
  FabricMmioManager->MmioRegionBelow4G[i][j].AlignNonPrefetch = 0;
  FabricMmioManager->MmioRegionBelow4G[i][j].AlignPrefetch = 0;
  IDS_HDT_CONSOLE (CPU_TRACE, "    Prefetch    0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch, (FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch), FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch);
  IDS_HDT_CONSOLE (CPU_TRACE, "    NonPrefetch 0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch, (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch), FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch);
  IDS_HDT_CONSOLE (CPU_TRACE, "    NonPci      0x%lX ~ 0x%lX, Size 0x%lX\n\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci, (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci + FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci), FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci);

  //   4. allocate MMIO for other RootBridges
  RbNumberMmioHasInitialized = 1;
  for (i = 0; i < SocketNumber; i++) {
    for (j = 0; j < RbsPerSocket; j++) {
      if ((i == PrimarySocket) && (j == PrimaryRootBridge)) {
        continue;
      }

      FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] = TRUE;
      if (RbNumberAbovePcieCfg != 0) {
        // above PCIe Configuration Space
        if (RbNumberMmioHasInitialized == 1) {
          MmioSizeRemained = MmioSize16MAligned;
        }
        MmioBaseAddr = MmioBaseAddr - MmioSizeRemained;
        RbNumberAbovePcieCfg--;
      } else if (!BelowPcieCfgIsTooSmall) {
        // below PCIe Configuration Space
        if (RbNumberAbovePcieCfgCopy == RbNumberMmioHasInitialized) {
          MmioSize = DivU64x32 (SizeBelowPcieCfg, (SystemRbNumber - RbNumberMmioHasInitialized));
          MmioSize16MAligned = MmioSize & SIZE_16M_ALIGN;
          MmioSizeRemained = SizeBelowPcieCfg - MultU64x64 (MmioSize16MAligned, (SystemRbNumber - RbNumberMmioHasInitialized - 1));
          MmioBaseAddr = PcdGet64 (PcdPciExpressBaseAddress);
        }
        if (RbNumberMmioHasInitialized == (RbNumberAbovePcieCfgCopy + 1)) {
          MmioSizeRemained = MmioSize16MAligned;
        }
        MmioBaseAddr = MmioBaseAddr - MmioSizeRemained;
      } else {
        ASSERT (FALSE);
      }

      FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), i, j, MmioBaseAddr, MmioSizeRemained);
      // Prefetchable -> Non Prefetchable -> Non Pci
      // Prefetchable/Non Prefetchable 80/20 Ratio
      FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci = PcdGet32 (PcdAmdMmioSizePerRbForNonPciDevice);
      FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch = (DivU64x32 (MultU64x64 ((MmioSizeRemained - FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci), 4), 5)) & SIZE_16M_ALIGN;
      FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch = MmioBaseAddr;
      FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch = FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch;
      FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci = (MmioBaseAddr + MmioSizeRemained - FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci) & (~VH_NON_PCI_MMIO_ALIGN_MASK);
      FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch = FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci - FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch;
      FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPci = 0;
      FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizePrefetch = 0;
      FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPrefetch = 0;
      FabricMmioManager->MmioRegionBelow4G[i][j].AlignNonPrefetch = 0;
      FabricMmioManager->MmioRegionBelow4G[i][j].AlignPrefetch = 0;
      IDS_HDT_CONSOLE (CPU_TRACE, "    Prefetch    0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch, (FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch), FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch);
      IDS_HDT_CONSOLE (CPU_TRACE, "    NonPrefetch 0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch, (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch + FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch), FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch);
      IDS_HDT_CONSOLE (CPU_TRACE, "    NonPci      0x%lX ~ 0x%lX, Size 0x%lX\n\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci, (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci + FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci), FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci);

      RbNumberMmioHasInitialized++;
    }
  }

  //   4. if there's a spare MMIO register pair, try to set undescribed space (above or below PCIe Configuration) as primary RootBridge's 2nd MMIO
  if (SystemRbNumber < (VH_MAX_RB_PER_SOCKET * VH_MAX_SOCKET)) {
    if ((AbovePcieCfgIsTooSmall && (SizeAbovePcieCfg != 0)) || ((SizeBelowPcieCfg != 0) && (BelowPcieCfgIsTooSmall || (SystemRbNumber == 1)))) {
      for (i = 0; i < VH_MAX_SOCKET; i++) {
        for (j = 0; j < VH_MAX_RB_PER_SOCKET; j++) {
          if (FabricMmioManager->AllocateMmioBelow4GOnThisRb[i][j] == FALSE) {
            IDS_HDT_CONSOLE (CPU_TRACE, "  socket 0 last root bridge has 2nd MMIO below 4G\n");
            FabricMmioManager->PrimaryRb2ndMmioPairBelow4G = (UINT8) ((i << 4) | j);
            if (AbovePcieCfgIsTooSmall) {
              MmioBaseAddr = PcdGet64 (PcdPciExpressBaseAddress) + PciCfgSpace;
              MmioSize = SizeAbovePcieCfg;
              FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), PrimarySocket, PrimaryRootBridge, MmioBaseAddr, (MmioSize + BottomOfCompat - PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb)));
              ReservedRegionAlreadySet = TRUE;
            } else {
              // for single RootBridge system, primary RootBridge always set the space above PcieCfg as MMIO in step 3
              MmioBaseAddr = TOM;
              MmioSize = SizeBelowPcieCfg;
              FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2), PrimarySocket, PrimaryRootBridge, MmioBaseAddr, MmioSize);
            }

            FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch = MmioSize;
            FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch = MmioBaseAddr;
            FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPci = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizePrefetch = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].UsedSizeNonPrefetch = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].AlignNonPrefetch = 0;
            FabricMmioManager->MmioRegionBelow4G[i][j].AlignPrefetch = 0;

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

  //   5. Distribute MMIO above 4G evenly
  MmioBaseAddr = (TOM2 > 0x100000000) ? TOM2 : 0x100000000; // Check if TOM2 > 4G
  MmioLimitAbove4G = 0x7FD00000000; // SMEE wold be enabled as default, so set limit to 0x7FD00000000

  if (PcdGet64 (PcdAmdMmioAbove4GLimit) < MmioLimitAbove4G) {
    MmioLimitAbove4G = (PcdGet64 (PcdAmdMmioAbove4GLimit) + 1) & 0xFFFFFFFFFFFF0000;
  }

  // there's a hole at 0xFD_0000_0000 ~ 0x100_0000_0000
  MmioSizeBelowHole = 0;
  MmioSizeAboveHole = 0;

  // calculate Mmio size below/above this hole
  if (MmioBaseAddr < 0xFD00000000) {
    MmioSizeBelowHole = (MmioLimitAbove4G < 0xFD00000000)? MmioLimitAbove4G : 0xFD00000000;
    MmioSizeBelowHole = MmioSizeBelowHole - MmioBaseAddr;
  }

  if (MmioLimitAbove4G > 0x10000000000) {
    MmioSizeAboveHole = (MmioBaseAddr > 0x10000000000)? MmioBaseAddr : 0x10000000000;
    MmioSizeAboveHole = MmioLimitAbove4G - MmioSizeAboveHole;
  }

  if ((MmioSizeBelowHole == 0) && (MmioSizeAboveHole == 0)) {
    MmioLimitAbove4G = 0; // set limit to 0, so there's no MMIO space above 4G
    IDS_HDT_CONSOLE (CPU_TRACE, "    WARNING: There's no MMIO space above 4G\n");
  } else {
    if (MmioSizeAboveHole > MmioSizeBelowHole) {
      MmioBaseAddr = (TOM2 > 0x10000000000) ? TOM2 : 0x10000000000; // Check if TOM2 > 1T
    } else {
      MmioLimitAbove4G = (MmioLimitAbove4G < 0xFD00000000) ? MmioLimitAbove4G : 0xFD00000000;
    }
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "    Above 4G MMIO base is 0x%lX, limit is 0x%lX\n", MmioBaseAddr, MmioLimitAbove4G);

  if (MmioLimitAbove4G > MmioBaseAddr) {
    MmioSize = MmioLimitAbove4G - MmioBaseAddr;
    MmioSize16MAligned = DivU64x32 (MmioSize, SystemRbNumber) & SIZE_16M_ALIGN;
    MmioSizeRemained = MmioSize - MultU64x64 (MmioSize16MAligned, (SystemRbNumber - 1));

    for (i = 0; i < SocketNumber; i++) {
      for (j = 0; j < RbsPerSocket; j++) {
        FabricMmioManager->AllocateMmioAbove4GOnThisRb[i][j] = TRUE;
        if ((i == (SocketNumber - 1)) && (j == (RbsPerSocket - 1))) {
          MmioSize16MAligned = MmioSizeRemained;
        }
        if (MmioSize16MAligned < MMIO_MIN_NON_PCI_SIZE_ABOVE4G) {
          continue;
        }
        if ((i == (SocketNumber - 1)) && (j == (RbsPerSocket - 1))) {
          // workaround to set last RootBridge's MMIO limit to 0xFFFF_FFFF_FFFF
          FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2 + 1), i, j, MmioBaseAddr, (0x1000000000000 - MmioBaseAddr));
        } else {
          FabricSetMmioReg3 (SocketNumber, ((i * RbsPerSocket + j) * 2 + 1), i, j, MmioBaseAddr, MmioSize16MAligned);
        }
        // Non Pci -> Prefetchable -> Non Prefetchable
        // Prefetchable/Non Prefetchable 80/20 Ratio
        FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci = (MmioBaseAddr + VH_NON_PCI_MMIO_ALIGN_MASK_ABOVE4G) & (~VH_NON_PCI_MMIO_ALIGN_MASK_ABOVE4G);
        FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci = (PcdGet32 (PcdAmdAbove4GMmioSizePerRbForNonPciDevice) > MMIO_MIN_NON_PCI_SIZE_ABOVE4G) ? PcdGet32 (PcdAmdAbove4GMmioSizePerRbForNonPciDevice) : MMIO_MIN_NON_PCI_SIZE_ABOVE4G;
        FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch = FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci + FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci;
        FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch = (DivU64x32 (MultU64x64 ((MmioBaseAddr + MmioSize16MAligned - FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci - FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci), 4), 5)) & SIZE_16M_ALIGN;
        FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch = FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch;
        FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch = MmioBaseAddr + MmioSize16MAligned - FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch;
        FabricMmioManager->MmioRegionAbove4G[i][j].UsedSizeNonPci = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].UsedSizePrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].UsedSizeNonPrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].AlignNonPrefetch = 0;
        FabricMmioManager->MmioRegionAbove4G[i][j].AlignPrefetch = 0;

        IDS_HDT_CONSOLE (CPU_TRACE, "    NonPci      0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci, (FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci + FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci), FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci);
        IDS_HDT_CONSOLE (CPU_TRACE, "    Prefetch    0x%lX ~ 0x%lX, Size 0x%lX\n", FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch, (FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch + FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch), FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch);
        IDS_HDT_CONSOLE (CPU_TRACE, "    NonPrefetch 0x%lX ~ 0x%lX, Size 0x%lX\n\n", FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch, (FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch + FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch), FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch);

        MmioBaseAddr += MmioSize16MAligned;
      }
    }
  }

  //   6. if there's a spare MMIO register pair, set 0xFED0_0000 ~ 0xFED0_FFFF as posted
  FabricAdditionalMmioSetting3 (FabricMmioManager, SocketNumber, RbsPerSocket, BottomOfCompat, ReservedRegionAlreadySet);
  return EFI_SUCCESS;
}

/*---------------------------------------------------------------------------------------*/
/**
 * FabricInitIoEqually3
 *
 * Initialize IO registers for each RootBridge evenly.
 *
 * @param[in, out]    FabricIoManager          Point to FABRIC_IO_MANAGER
 * @param[in]         SocketNumber             System socket count
 * @param[in]         RbsPerSocket             RootBridge number per socket
 *
 */
EFI_STATUS
FabricInitIoEqually3 (
  IN       FABRIC_IO_MANAGER   *FabricIoManager,
  IN       UINT8                SocketNumber,
  IN       UINT8                RbsPerSocket
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
  UINT32            IoSizeForThisRb;
  UINT32            IoBaseForPrimaryRb;
  UINT32            IoSizeForPrimaryRb;
  UINT32            IoBaseForOthers;
  UINT32            LegacyIoSize;
  UINTN             PrimarySocket;
  UINTN             PrimaryRootBridge;

  RegIndex = 0;
  LegacyIoSize = X86_LEGACY_IO_SIZE;
  IDS_HDT_CONSOLE (CPU_TRACE, "    reserve 0x%X IO size for legacy devices\n", LegacyIoSize);

  // most IO registers have a 16bit limit
  // reserve LegacyIoSize for primary RootBridge
  IoSize = ((0x10000 - LegacyIoSize) / (SocketNumber * RbsPerSocket)) & 0xFFFFF000; // 12 bit alignment

  // Get base & size for primary RootBridge
  FabricGetPrimayRb (&PrimarySocket, &PrimaryRootBridge);

  IoBaseForPrimaryRb = 0;
  IoSizeForPrimaryRb = DF_IO_LIMIT - IoBaseForPrimaryRb;
  IoBaseForOthers = 0;
  if ((SocketNumber != 1) || (RbsPerSocket != 1)) {
    // If we have more than one RootBridge
    // find out primary RootBridge and reserve an IO region start from 0 for it
    for (PhySktLoop = 0; PhySktLoop < SocketNumber; PhySktLoop++) {
      for (PhyRbLoop = 0; PhyRbLoop < RbsPerSocket; PhyRbLoop++) {
        if ((PhySktLoop == PrimarySocket) && (PhyRbLoop == PrimaryRootBridge)) {
          IoSizeForPrimaryRb = IoSize + LegacyIoSize;
          IoBaseForOthers = IoBaseForPrimaryRb + IoSizeForPrimaryRb;
        }
      }
    }
  }

  AlreadyInitNonPrimaryRbNum = 0;
  for (LogSktLoop = 0; LogSktLoop < SocketNumber; LogSktLoop++) {
    for (LogRbLoop = 0; LogRbLoop < RbsPerSocket; LogRbLoop++) {
      FabricGetPhySktRbNum (LogSktLoop, LogRbLoop, &PhySktLoop, &PhyRbLoop);

      if ((PhySktLoop == PrimarySocket) && (PhyRbLoop == PrimaryRootBridge)) {
        IoBase = IoBaseForPrimaryRb;
        IoSizeForThisRb = IoSizeForPrimaryRb;
      } else if (AlreadyInitNonPrimaryRbNum == (SocketNumber * RbsPerSocket - 2)) {
        // check if it's the last RB. DF's IO space is up to 25 bits, so set limit to 0x1FFFFFF for last RB
        IoBase = IoBaseForOthers;
        IoSizeForThisRb = DF_IO_LIMIT - IoBase;
      } else {
        IoBase = IoBaseForOthers;
        IoSizeForThisRb = IoSize;
        IoBaseForOthers += IoSizeForThisRb;
      }

      FabricSetIoReg3 (SocketNumber, RegIndex, PhySktLoop, PhyRbLoop, IoBase, IoSizeForThisRb);

      if ((PhySktLoop == PrimarySocket) && (PhyRbLoop == PrimaryRootBridge)) {
        // This root bridge has an additional IO region for legacy devices, size is LegacyIoSize
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase = IoBase + LegacyIoSize;
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize = IoSizeForThisRb - LegacyIoSize;
      } else if (AlreadyInitNonPrimaryRbNum == (SocketNumber * RbsPerSocket - 2)) {
        // When report to X86, IO region should be IoBase ~ X86IO_LIMIT since X86 only support 16 bits IO space
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase = IoBase;
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize = X86IO_LIMIT - FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase;
      } else {
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase = IoBase;
        FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize = IoSizeForThisRb;
        AlreadyInitNonPrimaryRbNum++;
      }
      FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoUsed = 0;

      IDS_HDT_CONSOLE (CPU_TRACE, "  Socket%x RootBridge%x has IO base 0x%X size 0x%X\n\n", PhySktLoop, PhyRbLoop, FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoBase, FabricIoManager->IoRegion[PhySktLoop][PhyRbLoop].IoSize);

      RegIndex++;
    }
  }

  FabricIoManager->GlobalCtrl = TRUE;

  return EFI_SUCCESS;
}


/*---------------------------------------------------------------------------------------*/
/**
 * FabricCheckResourceValid
 *
 * Check ResourceSizeForEachRb is valid or not
 * if Size is 0, set Alignment to 0
 *
 * @param[in]         MmioSizeForEachRb        How much MMIO size is required for each Root Bridge
 *
 */
VOID
FabricCheckResourceValid (
  IN       FABRIC_RESOURCE_FOR_EACH_RB  *ResourceSizeForEachRb
  )
{
  UINT8  i;
  UINT8  j;

  for (i = 0; i < MAX_SOCKETS_SUPPORTED; i++) {
    for (j = 0; j < MAX_RBS_PER_SOCKET; j++) {
      // Check NonPrefetchableMmioSizeAbove4G
      if (ResourceSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Size == 0) {
        ResourceSizeForEachRb->NonPrefetchableMmioSizeAbove4G[i][j].Alignment = 0;
      }

      // Check PrefetchableMmioSizeAbove4G
      if (ResourceSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Size == 0) {
        ResourceSizeForEachRb->PrefetchableMmioSizeAbove4G[i][j].Alignment = 0;
      }

      // Check NonPrefetchableMmioSizeBelow4G
      if (ResourceSizeForEachRb->NonPrefetchableMmioSizeBelow4G[i][j].Size == 0) {
        ResourceSizeForEachRb->NonPrefetchableMmioSizeBelow4G[i][j].Alignment = 0;
      }

      // Check PrefetchableMmioSizeAbove4G
      if (ResourceSizeForEachRb->PrefetchableMmioSizeBelow4G[i][j].Size == 0) {
        ResourceSizeForEachRb->PrefetchableMmioSizeBelow4G[i][j].Alignment = 0;
      }

      // Check PrimaryRbSecondNonPrefetchableMmioSizeBelow4G
      if (ResourceSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Size == 0) {
        ResourceSizeForEachRb->PrimaryRbSecondNonPrefetchableMmioSizeBelow4G.Alignment = 0;
      }

      // Check PrimaryRbSecondPrefetchableMmioSizeBelow4G
      if (ResourceSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Size == 0) {
        ResourceSizeForEachRb->PrimaryRbSecondPrefetchableMmioSizeBelow4G.Alignment = 0;
      }

    }
  }
}

