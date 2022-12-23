/* $NoKeywords:$ */
/**
 * @file
 *
 * CCX down core and SMT initialization
 *
 * This funtion reduces the number of threads in the system, if desired.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CCX
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ****************************************************************************
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

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "AMD.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/CcxDownCoreLib.h>
#include <Library/BaseCoreLogicalIdLib.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/FabricTopologyServices2Ppi.h>
#include <Ppi/AmdCoreTopologyServicesPpi.h>
#include <Ppi/Reset2.h>
#include "Filecode.h"
#include "CcxZenZpDownCoreInit.h"

#define FILECODE CCX_ZEN_CCXZENZPPEI_CCXZENZPDOWNCOREINIT_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
CcxZenZpDownCoreAfterSmuServicesCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
EFI_PEI_NOTIFY_DESCRIPTOR   mAfterSmuServicesPpiCallback = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdNbioSmuServicesPpiGuid,
  CcxZenZpDownCoreAfterSmuServicesCallback
};

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  FabricClockGatingInit
 *
 *  Description:
 *    This funtion initializes the DF clock gating feature.
 *
 */
VOID
CcxZenZpDownCoreInit (
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  (**PeiServices).NotifyPpi (PeiServices, &mAfterSmuServicesPpiCallback);
}

EFI_STATUS
EFIAPI
CcxZenZpDownCoreAfterSmuServicesCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
  UINT8                                 DownCoreMode;
  UINT8                                 SmtMode;
  UINT32                                CoreDisFuse;
  UINT32                                ThrdPerCoreFuse;
  UINTN                                 i;
  UINTN                                 j;
  UINTN                                 ComplexCount;
  UINTN                                 CoreCount;
  UINTN                                 ThreadCount;
  UINTN                                 DieCount;
  UINTN                                 SystemDieCount;
  UINTN                                 SocketCount;
  UINTN                                 DesiredCoreCount;
  UINTN                                 DesiredComplexCount;
  UINT32                                SystemDieLoop;
  UINT32                                CoreDisByFuseCount;
  UINT32                                CoreDisMask;
  UINT32                                SmuArg[6];
  BOOLEAN                               IssueReset;
  BOOLEAN                               Attainable;
  BOOLEAN                               Met;
  BOOLEAN                               AlreadyDownCored;
  SOC_LOGICAL_ID                        LogicalId;
  EFI_STATUS                            Status;
  EFI_STATUS                            CalledStatus;
  CCX_CORE_DIS_MASK                     DownCore;
  PEI_AMD_NBIO_SMU_SERVICES_PPI         *NbioSmuServices;
  AMD_CORE_TOPOLOGY_SERVICES_PPI        *CoreTopologyServices;
  AMD_PEI_FABRIC_TOPOLOGY_SERVICES2_PPI *FabricTopologyServices;
  EFI_PEI_RESET2_PPI                    *Reset2;

  AGESA_TESTPOINT (TpCcxPeiDownCoreCallbackEntry, NULL);

  Status = EFI_SUCCESS;
  IssueReset = FALSE;
  DownCoreMode = PcdGet8 (PcdAmdDownCoreMode);
  SmtMode = PcdGet8 (PcdAmdSmtMode);
  BaseGetLogicalIdOnExecutingCore (&LogicalId);
  LibAmdMemFill (SmuArg, 0x00, 24, NULL);
  ASSERT (DownCoreMode < CCX_DOWN_CORE_MAX);
  ASSERT (SmtMode <= 1);

  CalledStatus = (*PeiServices)->LocatePpi (PeiServices, &gAmdNbioSmuServicesPpiGuid, 0, NULL, &NbioSmuServices);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  CalledStatus = (*PeiServices)->LocatePpi (PeiServices, &gAmdFabricTopologyServices2PpiGuid, 0, NULL, &FabricTopologyServices);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  CalledStatus = (*PeiServices)->LocatePpi (PeiServices, &gAmdCoreTopologyServicesPpiGuid, 0, NULL, &CoreTopologyServices);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  FabricTopologyServices->GetSystemInfo (&SocketCount, &SystemDieCount, NULL, NULL, NULL);

  DesiredCoreCount = 0xFFFFFFFF;
  DesiredComplexCount = 0xFFFFFFFF;
  CoreDisMask = 0;
  if (DownCoreMode != 0) {
    switch (DownCoreMode) {
    case CCX_DOWN_CORE_1_0:
      // 1+0 mode is only supported by PR
      if ((LogicalId.Family == AMD_FAMILY_17_ZP) && ((LogicalId.Revision & AMD_REV_F17_PR_ALL) != 0)) {
        DesiredCoreCount = 1;
        DesiredComplexCount = 1;
        CoreDisMask = 0x000000FE;
      } else {
        IDS_HDT_CONSOLE (CPU_TRACE, "  Downcore mode (1+0) not supported.  No downcoring will take place.\n");
        // Make attainability an impossibility
        DesiredCoreCount = 0xFFFFFFFF;
        DesiredComplexCount = 0xFFFFFFFF;
      }
      break;
    case CCX_DOWN_CORE_2_0:
      DesiredCoreCount = 2;
      DesiredComplexCount = 1;
      CoreDisMask = 0x000000FC;
      break;
    case CCX_DOWN_CORE_3_0:
      DesiredCoreCount = 3;
      DesiredComplexCount = 1;
      CoreDisMask = 0x000000F8;
      break;
    case CCX_DOWN_CORE_4_0:
      DesiredCoreCount = 4;
      DesiredComplexCount = 1;
      CoreDisMask = 0x000000F0;
      break;
    case CCX_DOWN_CORE_1_1:
      DesiredCoreCount = 1;
      DesiredComplexCount = 2;
      CoreDisMask = 0x000000EE;
      break;
    case CCX_DOWN_CORE_2_2:
      DesiredCoreCount = 2;
      DesiredComplexCount = 2;
      CoreDisMask = 0x000000CC;
      break;
    case CCX_DOWN_CORE_3_3:
      DesiredCoreCount = 3;
      DesiredComplexCount = 2;
      CoreDisMask = 0x00000088;
      break;
    default:
      // Make attainability an impossibility
      DesiredCoreCount = 0xFFFFFFFF;
      DesiredComplexCount = 0xFFFFFFFF;
      break;
    }
  }

  Attainable = TRUE;
  Met = TRUE;
  AlreadyDownCored = FALSE;
  SystemDieLoop = 0;
  CoreDisByFuseCount = 0;
  ThrdPerCoreFuse = 2;
  ThreadCount = ThrdPerCoreFuse;

  for (i = 0; i < SocketCount; i++) {
    FabricTopologyServices->GetProcessorInfo (i, &DieCount, NULL);
    for (j = 0; j < DieCount; j++) {
      // Get CoreDis FUSE
      NbioSmuServices->SmuRegisterRead (NbioSmuServices, SystemDieLoop, 0x5D25C, &CoreDisFuse);
      ThrdPerCoreFuse = ((CoreDisFuse >> 8) & 1) + 1;
      CoreDisFuse &= 0xFF; // bits[7:0]
      while (CoreDisFuse != 0) {
        if ((CoreDisFuse & 1) == 1) {
          CoreDisByFuseCount++;
        }
        CoreDisFuse = CoreDisFuse >> 1;
      }

      // Get actually core count and complex count
      CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, i, j, &ComplexCount, &CoreCount, &ThreadCount);
      IDS_HDT_CONSOLE (CPU_TRACE, "  CoreDisByFuseCount %X\n", CoreDisByFuseCount);
      IDS_HDT_CONSOLE (CPU_TRACE, "  ComplexCount %X; CoreCount %X\n", ComplexCount, CoreCount);

      // Check if already down cored
      if (((CoreCount * ComplexCount) + CoreDisByFuseCount) < 8) {
        AlreadyDownCored = TRUE;
        IDS_HDT_CONSOLE (CPU_TRACE, "  Already down cored, skip down core function\n");
      }
      if (DownCoreMode != 0) {
        if ((DesiredCoreCount > CoreCount) || (DesiredComplexCount > ComplexCount)) {
          Attainable = FALSE;
        }
        if ((DesiredCoreCount != CoreCount) || (DesiredComplexCount != ComplexCount)) {
          Met = FALSE;
        }
        DownCore.CoreDisMask[SystemDieLoop] = CoreDisMask;
      }
      SystemDieLoop++;
    }
  }
  DownCore.SystemDieCount = (UINT8) SystemDieLoop;

  if (DownCoreMode != 0) {
    if (Attainable && !Met && !AlreadyDownCored) {
      IDS_HOOK (IDS_HOOK_CCX_CORE_DIS_MASK, NULL, (VOID *) &DownCore);

      SystemDieLoop = 0;
      for (i = 0; (i < SocketCount) && Attainable; i++) {
        FabricTopologyServices->GetProcessorInfo (i, &DieCount, NULL);
        for (j = 0; (j < DieCount) && Attainable; j++) {
          IDS_HDT_CONSOLE (CPU_TRACE, "  Set Die%x down core register 0x%x\n", SystemDieLoop, DownCore.CoreDisMask[SystemDieLoop]);
          NbioSmuServices->SmuRegisterWrite (NbioSmuServices, SystemDieLoop, 0x5A860, &(DownCore.CoreDisMask[SystemDieLoop]));

          SmuArg[0] = 0xAA55AA55;
          NbioSmuServices->SmuServiceRequest (NbioSmuServices, SystemDieLoop, 1, SmuArg, SmuArg);
          SystemDieLoop++;
          IssueReset = TRUE;
        }
      }
    }
  }

  if (SmtMode == 0) {
    if (ThreadCount > 1) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  Disabling SMT\n");
      NbioSmuServices->SmuDisableSmt (NbioSmuServices);
      IssueReset = TRUE;
    }
  }

  // if DownCoreMode = Auto and it's already downcored
  // or if DownCoreMode != Auto, and actual core/ccx count meet neither DownCoreMode nor Fuse
  // or SmtMode = Auto, and actual ThreadsPerCore doesn't meet fuse
  // issue code reset
  if (((DownCoreMode != 0) && !Met && AlreadyDownCored) ||
      ((DownCoreMode == 0) && AlreadyDownCored) ||
      ((SmtMode == 1) && (ThreadCount != ThrdPerCoreFuse))) {
    CalledStatus = (*PeiServices)->LocatePpi (PeiServices, &gEfiPeiReset2PpiGuid, 0, NULL, &Reset2);
    if (CalledStatus == EFI_SUCCESS) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  Issuing cold reset\n");
      Reset2->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  if (IssueReset) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  Issuing warm reset\n");
    (**PeiServices).ResetSystem (PeiServices);
  }

  AGESA_TESTPOINT (TpCcxPeiDownCoreCallbackExit, NULL);

  return Status;
}


