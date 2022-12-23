/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Zen - Zeppelin API, and related functions.
 *
 * Contains code that initializes the core complex
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CCX
 * @e \$Revision$   @e \$Date$
 *
 */
/*****************************************************************************
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

#include <PiDxe.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Guid/HobList.h>
#include <Guid/EventGroup.h>
#include <Filecode.h>
#include <Library/DxeFabricTopologyServices2Lib.h>
#include <Library/DxeFabricResourceManagerServicesLib.h>
#include <Library/FabricResourceReportToGcdLib.h>
#include <Protocol/FabricNumaServicesProtocol.h>
#include "FabricPiePwrMgmt.h"
#include "FabricAcpiTable.h"
#include "FabricReadyToBoot.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdHeapLib.h>

#define FILECODE FABRIC_RV_FABRICRVDXE_AMDFABRICRVDXE_FILECODE
/*++
Module Name:

  AmdFabricRvDxe.c
  Init Data Fabric interface

Abstract:
--*/

VOID
EFIAPI
FabricNbioSmuServicesCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  );

/*++

Routine Description:

  Zen - Zeppelin Driver Entry.  Initialize the core complex.

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdFabricRvDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  UINT32                         NumaDomainCount;
  EFI_STATUS                     Status;
  EFI_STATUS                     CalledStatus;
  EFI_EVENT                      ReadyToBootEvent;
  FABRIC_NUMA_SERVICES_PROTOCOL  *FabricNuma;

  AGESA_TESTPOINT (TpDfDxeEntry, NULL);

  Status = EFI_SUCCESS;

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdFabricRvDxeInit Entry\n");

  // Publish DXE topology services
  CalledStatus = FabricTopologyService2ProtocolInstall (ImageHandle, SystemTable);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  // Publish DF Resource Manager services
  CalledStatus = FabricResourceManagerServiceProtocolInstall (ImageHandle, SystemTable);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  // Report MMIO Region to GCD
  // NOTE: this must be after FabricResourceManagerServiceProtocolInstall
  FabricResourceReportToGcd ();

  // Publish NUMA services protocol
  CalledStatus = FabricRvNumaServicesProtocolInstall (ImageHandle, SystemTable);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  if (gBS->LocateProtocol (&gAmdFabricNumaServicesProtocolGuid, NULL, (VOID **) &FabricNuma) == EFI_SUCCESS) {
    if (FabricNuma->GetDomainInfo (FabricNuma, &NumaDomainCount, NULL) == EFI_SUCCESS) {
      if (NumaDomainCount > 1) {
        // Publish ACPI Fabric SRAT services protocol
        CalledStatus = FabricRvAcpiSratProtocolInstall (ImageHandle, SystemTable);
        Status = (CalledStatus > Status) ? CalledStatus : Status;

        // Publish ACPI SLIT services protocol
        CalledStatus = FabricRvAcpiSlitProtocolInstall (ImageHandle, SystemTable);
        Status = (CalledStatus > Status) ? CalledStatus : Status;
      }
    }

    // Publish ACPI Fabric CRAT services protocol
    CalledStatus = FabricRvAcpiCratProtocolInstall (ImageHandle, SystemTable);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Publish ACPI CDIT services
    CalledStatus = FabricRvAcpiCditProtocolInstall (ImageHandle, SystemTable);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "    PIE power management\n");
  FabricPiePwrMgmtInit ();

  CalledStatus = gBS->CreateEventEx (
                      EVT_NOTIFY_SIGNAL,
                      TPL_NOTIFY,
                      FabricReadyToBoot,
                      NULL,
                      &gEfiEventReadyToBootGuid,
                      &ReadyToBootEvent
                      );
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdFabricRvDxeInit End\n");

  AGESA_TESTPOINT (TpDfDxeExit, NULL);

  return (Status);
}


