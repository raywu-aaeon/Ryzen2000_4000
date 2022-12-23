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

  AmdCcxZenZpPei.c
  Init CCX interface

Abstract:
--*/

#include "PiPei.h"
#include <AGESA.h>
#include "CcxZenZpCacheInit.h"
#include "CcxZenZpDownCoreInit.h"
#include "CcxZenZpBrandString.h"
#include <Library/CcxBaseX86Lib.h>
#include <Library/CcxRolesLib.h>
#include <Library/CcxDownCoreLib.h>
#include <Library/CcxResetTablesLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/IdsLib.h>
#include <Library/FchBaseLib.h>
#include <Library/AmdCapsuleLib.h>
#include <Library/BaseCoreLogicalIdLib.h>
#include <Library/ApobCommonServiceLib.h>
#include <Library/BaseMemoryLib.h>
#include <Ppi/AmdCcxPpi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Ppi/FabricTopologyServices2Ppi.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <CcxRegistersZp.h>
#include <Ppi/ReadOnlyVariable2.h>
#include "Filecode.h"

#define FILECODE CCX_ZEN_CCXZENZPPEI_AMDCCXZENZPPEI_FILECODE

VOID
CcxPerfBump (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *NbioSmuServices
  );

STATIC PEI_AMD_CCX_INIT_COMPLETE_PPI mCcxPeiInitCompletePpi = {
  AMD_CCX_PPI_REVISION
};

STATIC EFI_PEI_PPI_DESCRIPTOR mCcxPeiInitCompletePpiList =
{
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCcxPeiInitCompletePpiGuid,
  &mCcxPeiInitCompletePpi
};

extern EFI_GUID gApSyncFlagNvVariableGuid;

#define ZEN_COMPLEX_MASK  0x0F
#define ZEN_COMPLEX_SIZE  4
#define ZP_COMPLEX_COUNT  2
UINT8  EnabledCoreCountOnComplex[16] =
{
  0x00,  //  0
  0x01,  //  1
  0x01,  //  2
  0x02,  //  3
  0x01,  //  4
  0x02,  //  5
  0x02,  //  6
  0x03,  //  7
  0x01,  //  8
  0x02,  //  9
  0x02,  // 10
  0x03,  // 11
  0x02,  // 12
  0x03,  // 13
  0x03,  // 14
  0x04,  // 15
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
AmdCcxZenZpPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  UINT8                                 OpnComplexCoreCount[ZP_COMPLEX_COUNT];
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
  UINTN                                 OpnThreadCount;
  UINTN                                 OpnComplexCount;
  UINT8                                 EnabledComplex;
  UINTN                                 VariableSize;
  VOLATILE UINT32                       *ApSyncFlag;
  UINT32                                ApNumBfLaunch;
  UINT32                                SystemDieLoop;
  UINT32                                OpnFuse;
  UINT32                                PackageType;
  UINT32                                ApobInstanceId;
  BOOLEAN                               IsS3;
  BOOLEAN                               S3Support;
  EFI_STATUS                            Status;
  EFI_STATUS                            CalledStatus;
  AMD_CONFIG_PARAMS                     StdHeader;
  PEI_AMD_NBIO_SMU_SERVICES_PPI         *NbioSmuServices;
  AMD_CORE_TOPOLOGY_SERVICES_PPI        *CoreTopologyServices;
  AMD_PEI_FABRIC_TOPOLOGY_SERVICES2_PPI *FabricTopologyServices;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI       *Variable;
  SOC_LOGICAL_ID                        LogicalId;

  AGESA_TESTPOINT (TpCcxPeiEntry, NULL);

  Status = EFI_SUCCESS;

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenZpPeiInit Entry\n");

  if (CcxIsBsp (&StdHeader)) {
    if ((FchReadSleepType () == 0x3) ||  (AmdCapsuleGetStatus ()) ) {
      IsS3 = TRUE;
    } else {
      IsS3 = FALSE;
    }

    // Disable PFEH for B1

    // Get LogicalId and Package
    BaseGetLogicalIdOnExecutingCore (&LogicalId);
    if ((LogicalId.Family == AMD_FAMILY_17_ZP) && ((LogicalId.Revision & AMD_REV_F17_ZP_B1) != 0)) {
      PcdSetBool (PcdAmdCcxCfgPFEHEnable, FALSE);
    }

    if (!IsS3) {
      CcxZenZpCacheInit (&StdHeader);
      IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenZpCacheInit Done\n");
    }

    CalledStatus = (**PeiServices).LocatePpi (
                    PeiServices,
                    &gAmdNbioSmuServicesPpiGuid,
                    0,
                    NULL,
                    &NbioSmuServices
                    );
    ASSERT (CalledStatus == EFI_SUCCESS);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
    CcxPerfBump (NbioSmuServices);

    CcxZenZpDownCoreInit (PeiServices);

    CcxProgramTablesAtReset ((IsS3 ? 3 : 0), &StdHeader);
    IDS_HDT_CONSOLE (CPU_TRACE, "  CcxProgramTablesAtReset Done\n");

    if (!IsS3) {
      CcxZenZpSetBrandString (&StdHeader);
      IDS_HDT_CONSOLE (CPU_TRACE, "  CcxZenZpSetBrandString Done\n");
    }

    CalledStatus = (*PeiServices)->LocatePpi (
                                   PeiServices,
                                   &gAmdCoreTopologyServicesPpiGuid,
                                   0,
                                   NULL,
                                   &CoreTopologyServices
                                   );
    ASSERT (CalledStatus == EFI_SUCCESS);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    CalledStatus = (*PeiServices)->LocatePpi (
                                   PeiServices,
                                   &gAmdFabricTopologyServices2PpiGuid,
                                   0,
                                   NULL,
                                   &FabricTopologyServices
                                   );
    ASSERT (CalledStatus == EFI_SUCCESS);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    FabricTopologyServices->GetSystemInfo (&NumberOfSockets, NULL, NULL, NULL, NULL);

    if (IsS3) {
      AGESA_TESTPOINT (TpCcxPeiStartLaunchApsForS3, NULL);
      IDS_HDT_CONSOLE (CPU_TRACE, "    Launching APs in PEI for S3\n");

      ApNumBfLaunch = 0;
      ApSyncFlag = NULL;
      CalledStatus = (**PeiServices).LocatePpi (PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &Variable);
      ASSERT (CalledStatus == EFI_SUCCESS);

      VariableSize = sizeof (UINT32);
      CalledStatus = Variable->GetVariable (
                      Variable,
                      L"ApSyncFlagNv",
                      &gApSyncFlagNvVariableGuid,
                      NULL,
                      &VariableSize,
                      (VOID *) &ApSyncFlag
                      );
      ASSERT (CalledStatus == EFI_SUCCESS);
      ASSERT (ApSyncFlag != NULL);
      IDS_HDT_CONSOLE (CPU_TRACE, " ApSyncFlagAddr %x\n", ApSyncFlag);

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
                  ApNumBfLaunch = *ApSyncFlag;
                  CoreTopologyServices->LaunchThread (CoreTopologyServices, i, j, k, LogicalThread);
                  // Wait until the core launch
                  while (*ApSyncFlag != (ApNumBfLaunch + 1)) {
                    ;
                  }
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
    } else {
      // Determine if S3 should be disabled
      S3Support = TRUE;

      PackageType = CcxGetProcessorPackageType (&StdHeader);
      if (PackageType == (1 << ZP_SOCKET_SP4)) {
        NbioSmuServices->SmuRegisterRead (NbioSmuServices, 0, 0x5D258, &OpnFuse);
        if ((OpnFuse & BIT30) != 0) {
          PackageType = (1 << ZP_SOCKET_SP3r2);
        }
      }

      if ((PackageType == (1 << ZP_SOCKET_SP3)) ||
          (PackageType == (1 << ZP_SOCKET_SP4)) ||
          ((PackageType == (1 << ZP_SOCKET_SP4r2)) && ((LogicalId.Revision & AMD_REV_F17_PR_ALL) == 0)))  {
        IDS_HDT_CONSOLE (CPU_TRACE, "    The package type does not support S3\n");
        S3Support = FALSE;

        if (PcdGetBool (PcdAmdScnLockNEnable) && (PackageType == (1 << ZP_SOCKET_SP3))) {
          AsmMsrOr64 (0xC0011020, BIT8);
        }

      } else {
        SystemDieLoop = 0;
        for (i = 0; i < NumberOfSockets; i++) {
          FabricTopologyServices->GetProcessorInfo (i, &NumberOfDies, NULL);
          for (j = 0; j < NumberOfDies; j++) {
            CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, i, j, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads);
            NbioSmuServices->SmuRegisterRead (NbioSmuServices, SystemDieLoop, 0x5D25C, &OpnFuse);
            OpnThreadCount = (UINTN) (((OpnFuse >> 8) & 1) + 1);
            OpnFuse = (~OpnFuse) & 0xFF;
            OpnComplexCount = 0;

            ApobInstanceId = ((UINT32) i << 8) | (UINT32) j;

            ApobGetPhysComplexNumber (ApobInstanceId, j, 0, &EnabledComplex);

            for (k = 0; k < ZP_COMPLEX_COUNT; k++) {
              OpnComplexCoreCount[k] = EnabledCoreCountOnComplex[((OpnFuse >> (ZEN_COMPLEX_SIZE * k)) & ZEN_COMPLEX_MASK)];
              if (OpnComplexCoreCount[k] != 0) {
                OpnComplexCount++;
              }
            }

            ASSERT ((OpnComplexCount > 0) && (OpnComplexCount <= ZP_COMPLEX_COUNT));
            if (OpnComplexCount > 1) {
              ASSERT (OpnComplexCoreCount[0] == OpnComplexCoreCount[1]);
            }

            if ((OpnComplexCount != NumberOfComplexes) ||
                ((UINTN) OpnComplexCoreCount[EnabledComplex] != NumberOfCores) ||
                (OpnThreadCount != NumberOfThreads)) {
              IDS_HDT_CONSOLE (CPU_TRACE, "    Threads have been removed by software.  Disable S3\n");
              S3Support = FALSE;
            }
            SystemDieLoop++;
          }
        }
      }
      if (!S3Support) {
        IDS_HDT_CONSOLE (CPU_TRACE, "    Setting PcdAmdAcpiS3Support to FALSE\n");
        PcdSetBool (PcdAmdAcpiS3Support, S3Support);
      }
    }

    CalledStatus = (**PeiServices).InstallPpi (PeiServices, &mCcxPeiInitCompletePpiList);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  } else {
    Status = EFI_DEVICE_ERROR;
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenZpPeiInit End\n");

  AGESA_TESTPOINT (TpCcxPeiExit, NULL);

  return (Status);
}

VOID
CcxPerfBump (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *NbioSmuServices
  )
{
  UINT32 Fuse;
  SOC_LOGICAL_ID LogicalId;

  BaseGetLogicalIdOnExecutingCore (&LogicalId);

  NbioSmuServices->SmuRegisterRead (NbioSmuServices, 0, 0x5D450, &Fuse);
  if (LogicalId.Family == AMD_FAMILY_17_ZP) {
    if (((LogicalId.Revision & AMD_REV_F17_ZP_LT_B1) != 0) ||
        (((LogicalId.Revision & AMD_REV_F17_ZP_B1) != 0) && ((Fuse & BIT27) == 0))) {
      AsmMsrOr64 (0xC0011020, BIT4);
    }
  }
}


