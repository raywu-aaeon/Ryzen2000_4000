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
/*++
Module Name:

  AmdCcxZenRvPei.c
  Init CCX interface

Abstract:
--*/

#include "PiPei.h"
#include <AGESA.h>
#include "CcxZenRvCacheInit.h"
#include "CcxZenRvDownCoreInit.h"
#include "CcxZenRvBrandString.h"
#include <Library/CcxBaseX86Lib.h>
#include <Library/CcxBistLib.h>
#include <Library/CcxRolesLib.h>
#include <Library/CcxDownCoreLib.h>
#include <Library/CcxResetTablesLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/IdsLib.h>
#include <Library/FchBaseLib.h>
#include <Library/AmdCapsuleLib.h>
#include <Ppi/AmdCcxPpi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Ppi/FabricTopologyServices2Ppi.h>
#include "Filecode.h"

#define FILECODE CCX_ZEN_CCXZENRVPEI_AMDCCXZENRVPEI_FILECODE

STATIC PEI_AMD_CCX_INIT_COMPLETE_PPI mCcxPeiInitCompletePpi = {
  AMD_CCX_PPI_REVISION
};

STATIC EFI_PEI_PPI_DESCRIPTOR mCcxPeiInitCompletePpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCcxPeiInitCompletePpiGuid,
  &mCcxPeiInitCompletePpi
};

/*++

Routine Description:

  Zen - Zeppelin Driver Entry.  Initialize the core complex.

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdCcxZenRvPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  UINTN                                 i;
  UINTN                                 j;
  UINTN                                 k;
  UINTN                                 m;
  UINTN                                 n;
  UINTN                                 NumberOfSockets;
  UINTN                                 NumberOfDies;
  UINTN                                 NumberOfComplexes;
  UINTN                                 NumberOfCores;
  UINTN                                 NumberOfThreads;
  UINTN                                 LogicalThread;
  BOOLEAN                               IsS3;
  EFI_STATUS                            Status;
  EFI_STATUS                            CalledStatus;
  AMD_CONFIG_PARAMS                     StdHeader;
  AMD_CORE_TOPOLOGY_SERVICES_PPI        *CoreTopologyServices;
  AMD_PEI_FABRIC_TOPOLOGY_SERVICES2_PPI *FabricTopologyServices;

  AGESA_TESTPOINT (TpCcxPeiEntry, NULL);

  Status = EFI_SUCCESS;

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenRvPeiInit Entry\n");

  if (CcxIsBsp (&StdHeader)) {
    if ((FchReadSleepType () == 0x3) ||  (AmdCapsuleGetStatus ()) ) {
      IsS3 = TRUE;
    } else {
      IsS3 = FALSE;
    }

    if (!IsS3) {
      CcxZenRvCacheInit (&StdHeader);
      IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenRvCacheInit Done\n");
    }

    if (CheckBistStatus (&StdHeader) != AGESA_SUCCESS) {
      Status = EFI_DEVICE_ERROR;
    }

    CcxZenRvDownCoreInit (PeiServices);

    CcxProgramTablesAtReset (FchReadSleepType (), &StdHeader);
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxProgramTablesAtReset Done\n");

    if (!IsS3) {
      CcxZenRvSetBrandString (&StdHeader);
      IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenRvSetBrandString Done\n");
    }

    if (IsS3) {
      AGESA_TESTPOINT (TpCcxPeiStartLaunchApsForS3, NULL);
      IDS_HDT_CONSOLE (CPU_TRACE, "    Launching APs in PEI for S3\n");

      CalledStatus = (*PeiServices)->LocatePpi (
                                     PeiServices,
                                     &gAmdCoreTopologyServicesPpiGuid,
                                     0,
                                     NULL,
                                     &CoreTopologyServices
                                     );

      CalledStatus = (*PeiServices)->LocatePpi (
                                     PeiServices,
                                     &gAmdFabricTopologyServices2PpiGuid,
                                     0,
                                     NULL,
                                     &FabricTopologyServices
                                     );

      FabricTopologyServices->GetSystemInfo (&NumberOfSockets, NULL, NULL, NULL, NULL);

      for (i = 0; i < NumberOfSockets; i++) {
        FabricTopologyServices->GetProcessorInfo (i, &NumberOfDies, NULL);
        for (j = 0; j < NumberOfDies; j++) {
          CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, i, j, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
          for (k = 0; k < NumberOfComplexes; k++) {
            LogicalThread = 0;
            for (m = 0; m < NumberOfCores; m++) {
              for (n = 0; n < NumberOfThreads; n++) {
                if (!((i == 0) && (j == 0) && (k == 0) && (LogicalThread == 0))) {

                  IDS_HDT_CONSOLE (CPU_TRACE, "      Launch socket %X die %X complex %X core %X thread %X\n", i, j, k, m, n);

                  CoreTopologyServices->LaunchThread (CoreTopologyServices, i, j, k, LogicalThread);
                }
                LogicalThread++;
              }
            }
          }
        }
      }

      // MSRC001_1023[49, TwCfgCombineCr0Cd] = 1
      AsmMsrOr64 (0xC0011023, BIT49);

      AGESA_TESTPOINT (TpCcxPeiEndLaunchApsForS3, NULL);
    }

    CalledStatus = (**PeiServices).InstallPpi (PeiServices, &mCcxPeiInitCompletePpiList);
    if (CalledStatus > Status) {
      Status = CalledStatus;
    }
  } else {
    Status = EFI_DEVICE_ERROR;
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenRvPeiInit End\n");

  AGESA_TESTPOINT (TpCcxPeiExit, NULL);

  return (Status);
}

