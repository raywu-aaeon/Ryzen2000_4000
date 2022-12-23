/* $NoKeywords:$ */
/**
 * @file
 *
 * Report used MMIO region to GCD service
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
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdHeapLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/FabricResourceManagerLib.h>

#define FILECODE LIBRARY_FABRICRESOURCEREPORTTOGCDLIB_FABRICRESOURCEREPORTTOGCDLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * FabricResourceReportToGcd
 *
 * Report MMIO regions to GCD
 *
 */
EFI_STATUS
FabricResourceReportToGcd (
  )
{
  UINT8                     i;
  UINT8                     j;
  UINT8                     TempSocket;
  UINT8                     TempRb;
  UINT64                    Base;
  UINT64                    Size;
  EFI_STATUS                Status;
  EFI_STATUS                CalledStatus;
  LOCATE_HEAP_PTR           LocateHeapParams;
  FABRIC_MMIO_MANAGER      *FabricMmioManager;

  Status = EFI_SUCCESS;
  FabricMmioManager = NULL;
  // Find MMIO manager in heap
  LocateHeapParams.BufferHandle = AMD_MMIO_MANAGER;

  IDS_HDT_CONSOLE (CPU_TRACE, "Report MMIO region to GCD\n");

  if (HeapLocateBuffer (&LocateHeapParams, NULL) == AGESA_SUCCESS) {
    FabricMmioManager = (FABRIC_MMIO_MANAGER *) LocateHeapParams.BufferPtr;
  }

  // report reserved region (for primary FCH)
  Base = PcdGet32 (PcdAmdBottomMmioReservedForPrimaryRb);
  Size = 0x100000000 - Base;
  CalledStatus = gDS->AddMemorySpace (EfiGcdMemoryTypeMemoryMappedIo,
                                      Base,
                                      Size,
                                      (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
  Status = (CalledStatus > Status) ? CalledStatus : Status;
  IDS_HDT_CONSOLE (CPU_TRACE, "  Add reserved MMIO region base 0x%lX size 0x%lX, Status: %x\n", Base, Size, Status);

  CalledStatus = gDS->AllocateMemorySpace (EfiGcdAllocateAddress,
                                           EfiGcdMemoryTypeMemoryMappedIo,
                                           0,
                                           Size,
                                           &Base,
                                           (EFI_HANDLE) FabricMmioManager->ImageHandle,
                                           NULL);
  Status = (CalledStatus > Status) ? CalledStatus : Status;
  gDS->SetMemorySpaceAttributes (Base, Size, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
  IDS_HDT_CONSOLE (CPU_TRACE, "  Allocate reserved MMIO region base 0x%lX size 0x%lX, Status: %x\n", Base, Size, CalledStatus);


  if (FabricMmioManager != NULL) {
    for (i = 0; i < MAX_SOCKETS_SUPPORTED; i++) {
      for (j = 0; j < MAX_RBS_PER_SOCKET; j++) {
        // report MMIO region below 4G

        // find out Base & Size for this root bridge
        Base = 0xFFFFFFFFFFFFFFFF;
        Size = 0;
        if ((FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci != 0) &&
            (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci < Base)) {
          Base = FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci;
        }
        Size += FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci;

        if ((FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch != 0) &&
            (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch < Base)) {
          Base = FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPrefetch;
        }
        Size += FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPrefetch;

        if ((FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch != 0) &&
            (FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch < Base)) {
          Base = FabricMmioManager->MmioRegionBelow4G[i][j].BasePrefetch;
        }
        Size += FabricMmioManager->MmioRegionBelow4G[i][j].SizePrefetch;

        // call GCD service AddMemorySpace
        CalledStatus = gDS->AddMemorySpace (EfiGcdMemoryTypeMemoryMappedIo,
                                            Base,
                                            Size,
                                            (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
        Status = (CalledStatus > Status) ? CalledStatus : Status;
        IDS_HDT_CONSOLE (CPU_TRACE, "  Add Socket %X RB %X MMIO region base 0x%lX size 0x%lX, Status: %x\n", i, j, Base, Size, Status);

        // call GCD service AllocateMemorySpace to allocate NonPci MMIO
        if (FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci != 0) {

          CalledStatus = gDS->AllocateMemorySpace (EfiGcdAllocateAddress,
                                                   EfiGcdMemoryTypeMemoryMappedIo,
                                                   0,
                                                   FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci,
                                                   &FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci,
                                                   (EFI_HANDLE) FabricMmioManager->ImageHandle,
                                                   NULL);
          Status = (CalledStatus > Status) ? CalledStatus : Status;
          gDS->SetMemorySpaceAttributes (FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci, FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
          IDS_HDT_CONSOLE (CPU_TRACE, "  Allocate Non-Pci MMIO region base 0x%lX size 0x%lX, Status: %x\n", FabricMmioManager->MmioRegionBelow4G[i][j].BaseNonPci, FabricMmioManager->MmioRegionBelow4G[i][j].SizeNonPci, CalledStatus);
        }

        // report Non-PCI MMIO region above 4G

        // find out Base & Size for this root bridge
        Base = 0xFFFFFFFFFFFFFFFF;
        Size = 0;
        if ((FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci != 0) &&
            (FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci < Base)) {
          Base = FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci;
        }
        Size += FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci;

        if ((FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch != 0) &&
            (FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch < Base)) {
          Base = FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPrefetch;
        }
        Size += FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPrefetch;

        if ((FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch != 0) &&
            (FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch < Base)) {
          Base = FabricMmioManager->MmioRegionAbove4G[i][j].BasePrefetch;
        }
        Size += FabricMmioManager->MmioRegionAbove4G[i][j].SizePrefetch;

        // call GCD service AddMemorySpace
        CalledStatus = gDS->AddMemorySpace (EfiGcdMemoryTypeMemoryMappedIo,
                                            Base,
                                            Size,
                                            (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
        Status = (CalledStatus > Status) ? CalledStatus : Status;
        IDS_HDT_CONSOLE (CPU_TRACE, "  Add Socket %X RB %X MMIO region base 0x%lX size 0x%lX, Status: %x\n", i, j, Base, Size, Status);

        // call GCD service AllocateMemorySpace to allocate NonPci MMIO
        if (FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci != 0) {
          CalledStatus = gDS->AllocateMemorySpace (EfiGcdAllocateAddress,
                                                   EfiGcdMemoryTypeMemoryMappedIo,
                                                   0,
                                                   FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci,
                                                   &FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci,
                                                   (EFI_HANDLE) FabricMmioManager->ImageHandle,
                                                   NULL);
          Status = (CalledStatus > Status) ? CalledStatus : Status;
          gDS->SetMemorySpaceAttributes (FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci, FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
          IDS_HDT_CONSOLE (CPU_TRACE, "  Allocate Non-Pci MMIO region base 0x%lX size 0x%lX, Status: %x\n", FabricMmioManager->MmioRegionAbove4G[i][j].BaseNonPci, FabricMmioManager->MmioRegionAbove4G[i][j].SizeNonPci, CalledStatus);
        }
      }
    }

    // Check primary Rb's 2nd MMIO
    if (FabricMmioManager->PrimaryRbHas2ndMmioBelow4G) {
      TempSocket = (FabricMmioManager->PrimaryRb2ndMmioPairBelow4G >> 4) & 0xF;
      TempRb = FabricMmioManager->PrimaryRb2ndMmioPairBelow4G & 0xF;

      // find out Base & Size for this root bridge
      Base = 0xFFFFFFFFFFFFFFFF;
      Size = 0;
      if ((FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPci != 0) &&
          (FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPci < Base)) {
        Base = FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPci;
      }
      Size += FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPci;

      if ((FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPrefetch != 0) &&
          (FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPrefetch < Base)) {
        Base = FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPrefetch;
      }
      Size += FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPrefetch;

      if ((FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizePrefetch != 0) &&
          (FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BasePrefetch < Base)) {
        Base = FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BasePrefetch;
      }
      Size += FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizePrefetch;

      // call GCD service AddMemorySpace
      CalledStatus = gDS->AddMemorySpace (EfiGcdMemoryTypeMemoryMappedIo,
                                          Base,
                                          Size,
                                          (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
      Status = (CalledStatus > Status) ? CalledStatus : Status;

      IDS_HDT_CONSOLE (CPU_TRACE, "  Add primary Rb's 2nd MMIO region base 0x%lX size 0x%lX, Status: %x\n", Base, Size, CalledStatus);

      // call GCD service AllocateMemorySpace to allocate NonPci MMIO
      if (FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPci != 0) {
        CalledStatus = gDS->AllocateMemorySpace (EfiGcdAllocateAddress,
                                                 EfiGcdMemoryTypeMemoryMappedIo,
                                                 0,
                                                 FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPci,
                                                 &FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPci,
                                                 (EFI_HANDLE) FabricMmioManager->ImageHandle,
                                                 NULL);
        Status = (CalledStatus > Status) ? CalledStatus : Status;
        gDS->SetMemorySpaceAttributes (FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPci, FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPci, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
        IDS_HDT_CONSOLE (CPU_TRACE, "  Allocate primary Rb's 2nd Non-Pci MMIO region base 0x%lX size 0x%lX, Status: %x\n", FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].BaseNonPci, FabricMmioManager->MmioRegionBelow4G[TempSocket][TempRb].SizeNonPci, CalledStatus);
      }
    }

    FabricMmioManager->ReportToGcd = TRUE;
  }

  return Status;
}


/*---------------------------------------------------------------------------------------*/
/**
 * ReportMmioToGcd
 *
 *
 */
EFI_STATUS
ReportMmioToGcd (
  IN       UINT64 *BaseAddress,
  IN       UINT64 Length,
  IN       FABRIC_MMIO_MANAGER *FabricMmioManager
  )
{
  EFI_STATUS Status;

  Status = gDS->AllocateMemorySpace (EfiGcdAllocateAddress,
                                     EfiGcdMemoryTypeMemoryMappedIo,
                                     0,
                                     Length,
                                     BaseAddress,
                                     (EFI_HANDLE) FabricMmioManager->ImageHandle,
                                     NULL);
  gDS->SetMemorySpaceAttributes (*BaseAddress, Length, (EFI_MEMORY_UC | EFI_MEMORY_RUNTIME));
  IDS_HDT_CONSOLE (CPU_TRACE, "  report to GCD, Status: %x\n", Status);

  return Status;
}

