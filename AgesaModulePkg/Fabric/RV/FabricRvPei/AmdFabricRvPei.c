/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Fabric - Zeppelin API, and related functions.
 *
 * Contains code that initializes the data fabric
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
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
/*++
Module Name:

  AmdFabricRvPei.c
  Init DF interface

Abstract:
--*/

#include <PiPei.h>
#include "AGESA.h"
#include <Filecode.h>
#include <AmdSoc.h>
#include "FabricPstateServicesPei.h"
#include <Library/PeiFabricTopologyServices2Lib.h>
#include <Library/PeiFabricResourceManagerServicesLib.h>
#include "FabricDfClkGatingInit.h"
#include "FabricCsInit.h"
#include "FabricCcmInit.h"
#include "FabricGcmNcmInit.h"
#include "FabricIomsInit.h"
#include "FabricPieRasInit.h"
#include <Library/AmdIdsHookLib.h>
#include "Library/IdsLib.h"
#include <Ppi/SocLogicalIdPpi.h>
#include "FabricScrubInit.h"

#define FILECODE FABRIC_RV_FABRICRVPEI_AMDFABRICRVPEI_FILECODE


/*++

Routine Description:

  Fabric - Zeppelin Driver Entry.  Initialize the core complex.

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdFabricRvPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                      Status;
  EFI_STATUS                      CalledStatus;
  AMD_PEI_SOC_LOGICAL_ID_PPI      *SocLogicalIdPpi;

  AGESA_TESTPOINT (TpDfPeiEntry, NULL);

  Status = EFI_SUCCESS;

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdFabricRvPeiInit Entry\n");

  CalledStatus = (*PeiServices)->LocatePpi (
                                 PeiServices,
                                 &gAmdSocLogicalIdPpiGuid,
                                 0,
                                 NULL,
                                 &SocLogicalIdPpi
                                 );

  ASSERT (CalledStatus == EFI_SUCCESS);

  // Publish PEI topology services
  CalledStatus = FabricTopologyService2PpiInstall (PeiServices);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  // Publish PEI P-state services
  CalledStatus = FabricPstateServicePpiInstall (PeiServices);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  // Publish PEI resource manager services
  CalledStatus = FabricResourceManagerServicePpiInstall (PeiServices);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  IDS_HDT_CONSOLE (CPU_TRACE, "    Clock Gating Init\n");
  FabricClockGatingInit (PeiServices, SocLogicalIdPpi);

  IDS_HDT_CONSOLE (CPU_TRACE, "    CS Init\n");
  FabricCsInit (PeiServices, SocLogicalIdPpi);

  IDS_HDT_CONSOLE (CPU_TRACE, "    CCM Init\n");
  FabricCcmInit (PeiServices, SocLogicalIdPpi);

  IDS_HDT_CONSOLE (CPU_TRACE, "    GCM/NCM Init\n");
  FabricGcmNcmInit (PeiServices, SocLogicalIdPpi);

  IDS_HDT_CONSOLE (CPU_TRACE, "    IOMS Init\n");
  FabricIomsInit (PeiServices, SocLogicalIdPpi);

  IDS_HDT_CONSOLE (CPU_TRACE, "    PIE RAS Init\n");
  FabricPieRasInit (PeiServices, SocLogicalIdPpi);

  IDS_HDT_CONSOLE (CPU_TRACE, "    Scrub Init\n");
  FabricScrubInit (PeiServices, SocLogicalIdPpi);

  IDS_HOOK (IDS_HOOK_FABRIC_PEI_INIT_END, NULL, NULL);

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdFabricRvPeiInit End\n");

  AGESA_TESTPOINT (TpDfPeiExit, NULL);

  return (Status);
}


