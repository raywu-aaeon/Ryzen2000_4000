/* $NoKeywords:$ */
/**
 * @file
 *
 * Implement Custom Core Pstates
 *
 * Contains code that Custom Core Pstates
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Library
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

#include "AMD.h"
#include "PiDxe.h"
#include <Library/BaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CcxPstatesLib.h>
#include <Porting.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CcxMpServicesLib.h>
#include <Library/CcxIdsCustomPstatesLib.h>
#include <Library/ApobCommonServiceLib.h>
#include <Protocol/AmdCoreTopologyProtocol.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/AmdNbioSmuServicesProtocol.h>
#include "Filecode.h"

#define FILECODE LIBRARY_CCXIDSCUSTOMPSTATESZENLIB_CCXIDSCUSTOMPSTATESZENLIB_FILECODE


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
SwitchPstateOnAllCores (
  IN       CCX_SWITCH_PSTATE *SwitchPstate
  );

VOID
UpdateMsrOnAllCores (
  IN       CCX_UPDATE_MSR *Msr
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 * CcxZenZpIdsSetPstateMsrs - routine to update Pstate MSRs to specified values
 *
 *
 * @param[in]  *CustomPstates  Pointer to data for Custom Pstates
 *
 *
 */
VOID
CcxIdsCustomPstateSetMsrLib (
  IN       IDS_CUSTOM_CORE_PSTATE  *CustomPstates
  )
{
  UINT8                   i;
  UINT8                   CurPstate;
  UINT8                   PreVid;
  UINT8                   CurrentVid;
  UINT32                  MaxPstate;
  UINT32                  ApobInstanceId;
  UINT32                  PreFreq;
  UINT32                  CurrentFreq;
  UINTN                   SocketLoop;
  UINTN                   DieLoop;
  UINTN                   ComplexLoop;
  UINTN                   CoreLoop;
  UINTN                   NumberOfSockets;
  UINTN                   NumberOfSystemDies;
  UINTN                   NumberOfDies;
  UINTN                   NumberOfComplexes;
  UINTN                   NumberOfCores;
  UINTN                   SystemDieCount;
  BOOLEAN                 Modified;
  BOOLEAN                 LastOne;
  IDS_PSTATE_MSR          PstateMsr;
  IDS_PSTATE_CURLIM_MSR   PstateCurLim;
  CCX_SWITCH_PSTATE       SwitchPstate;
  CCX_UPDATE_MSR          UpdateMsr;
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL            *NbioSmuServices;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL           *CoreTopologyServices;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL        *FabricTopologyServices;
  UINT8                   PhysComplexNumber;
  UINT8                   PhysCoreNumber;

  SwitchPstate.WaitForCompletion = TRUE;

  // Check custom core Pstate settings
  PreFreq = 0xFFFFFFFF;
  PreVid = 0;
  for (i = 0; i <= (PS_MAX_REG - PS_MIN_REG); i++) {
    if (CustomPstates[i].Custom == CCX_IDS_CORE_PSTATES_DISABLED) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  P%X - Disable\n", i);
      break;
    } else if (CustomPstates[i].Custom == CCX_IDS_CORE_PSTATES_CUSTOM) {
      ASSERT (CustomPstates[i].CoreDid != 0);
      CurrentFreq = (UINT32) (DivU64x32 (MultU64x64 (200, CustomPstates[i].CoreFid), CustomPstates[i].CoreDid));
      CurrentVid = CustomPstates[i].CoreVid;
      IDS_HDT_CONSOLE (CPU_TRACE, "  P%X - Custom, Frequency: %dMHz  FID-0x%X DID-0x%X VID-0x%X\n", i, CurrentFreq, CustomPstates[i].CoreFid, CustomPstates[i].CoreDid, CustomPstates[i].CoreVid);
    } else {
      PstateMsr.Value = AsmReadMsr64 (MSR_PSTATE_0 + i);
      if (PstateMsr.Field.PstateEn == 0) {
        break;
      }
      CurrentFreq = (UINT32) (DivU64x32 (MultU64x64 (200, PstateMsr.Field.CpuFid_7_0), (UINT32) PstateMsr.Field.CpuDfsId));
      CurrentVid = (UINT8) PstateMsr.Field.CpuVid;
      IDS_HDT_CONSOLE (CPU_TRACE, "  P%X - Auto,   Frequency: %dMHz  FID-0x%X DID-0x%X VID-0x%X\n", i, CurrentFreq, PstateMsr.Field.CpuFid_7_0, PstateMsr.Field.CpuDfsId, PstateMsr.Field.CpuVid);
    }

    if (PreFreq < CurrentFreq) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  ERROR: P%X frequency > P%X frequency\n", i, (i - 1));
      ASSERT (FALSE);
      return;
    }
    if (PreVid > CurrentVid) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  ERROR: P%X VID < P%X VID\n", i, (i - 1));
      ASSERT (FALSE);
      return;
    }
    PreFreq = CurrentFreq;
    PreVid = CurrentVid;
  }

  gBS->LocateProtocol (&gAmdNbioSmuServicesProtocolGuid, NULL, &NbioSmuServices);
  gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, &FabricTopologyServices);
  gBS->LocateProtocol (&gAmdCoreTopologyServicesProtocolGuid, NULL, &CoreTopologyServices);

  MaxPstate = 0;
  Modified = FALSE;

  if (FabricTopologyServices->GetSystemInfo (FabricTopologyServices, &NumberOfSockets, &NumberOfSystemDies, NULL, NULL, NULL) != EFI_SUCCESS) {
    return;
  }

  // Get Current Pstate limit
  PstateCurLim.Value = AsmReadMsr64 (MSR_PSTATE_CURRENT_LIMIT);

  // NOTE: setting Pstate registers in this order: first P1 ~ P7 then P0
  LastOne = FALSE;
  for (i = 1; ((i <= (PS_MAX_REG - PS_MIN_REG + 1)) && (!LastOne)); i++) {
    // If it's (PS_MAX_REG - PS_MIN_REG + 1), we already set P1~P7, change it to P0
    if (i == (PS_MAX_REG - PS_MIN_REG + 1)) {
      i = 0;
      LastOne = TRUE;
    }

    if (CustomPstates[i].Custom == CCX_IDS_CORE_PSTATES_DISABLED) {
      //
      // Disable
      //

      // We can't disable P0
      ASSERT (i > 0);

      // if Pstate[i] is enabled, then disable it and all lower Pstates
      PstateMsr.Value = AsmReadMsr64 (MSR_PSTATE_0 + i);
      if (PstateMsr.Field.PstateEn == 1) {
        Modified = TRUE;
        CurPstate = CcxGetCurrentPstate ();
        if (CurPstate >= i) {
          SwitchPstate.Pstate = i - 1;
          SwitchPstateOnAllCores (&SwitchPstate);
        }
        // disable all lower Psates
        while (i <= (PS_MAX_REG - PS_MIN_REG)) {
          UpdateMsr.MsrAddr = MSR_PSTATE_0 + i;
          UpdateMsr.MsrData = AsmReadMsr64 (MSR_PSTATE_0 + i);
          UpdateMsr.MsrData &= 0x7FFFFFFFFFFFFFFF;
          CcxRunFunctionOnAps (ALL_THREADS, UpdateMsrOnAllCores, &UpdateMsr, NON_BLOCKING_MODE);
          UpdateMsrOnAllCores (&UpdateMsr);

          i++;
        }
        // Now, i = (PS_MAX_REG - PS_MIN_REG + 1), we need decrease it by 1 and continue this for loop for P0
        i--;
      }
      continue;
    } else if (CustomPstates[i].Custom == CCX_IDS_CORE_PSTATES_CUSTOM) {
      //
      // Custom
      //

      // Vid >= 0xF8 is an invalid setting, skip it
      if (CustomPstates[i].CoreVid >= 0xF8) {
        continue;
      }
      Modified = TRUE;
      CurPstate = CcxGetCurrentPstate ();
      if ((CurPstate == i) && (CurPstate > 0)) {
        // Current Pstate == i and it's not P0, switch to above Pstate
        // For P0, we don't need to switch to another Pstate first, there're 2 reasons
        // 1. SMU team confirmed it's not necessory
        // 2. All other Pstates could be disabled by User
        SwitchPstate.Pstate = i - 1;
        SwitchPstateOnAllCores (&SwitchPstate);
      }
      // Customize this Pstate
      UpdateMsr.MsrAddr = MSR_PSTATE_0 + i;
      UpdateMsr.MsrData = AsmReadMsr64 (MSR_PSTATE_0 + i);
      UpdateMsr.MsrData &= 0x7FFFFFFFFFC00000;
      UpdateMsr.MsrData |= CustomPstates[i].CoreFid |
                           (CustomPstates[i].CoreDid << 8) |
                           (CustomPstates[i].CoreVid << 14 |
                           0x8000000000000000);
      CcxRunFunctionOnAps (ALL_THREADS, UpdateMsrOnAllCores, &UpdateMsr, NON_BLOCKING_MODE);
      UpdateMsrOnAllCores (&UpdateMsr);

      // Switch back
      if ((CurPstate == i) && (CurPstate > 0)) {
        SwitchPstate.Pstate = CurPstate;
        SwitchPstateOnAllCores (&SwitchPstate);
      }

      MaxPstate++;
    } else if (CustomPstates[i].Custom == CCX_IDS_CORE_PSTATES_AUTO) {
      //
      // Auto
      //

      // If this Pstate is disabled, and user didn't customize it, set i = PS_MAX_REG - PS_MIN_REG
      PstateMsr.Value = AsmReadMsr64 (MSR_PSTATE_0 + i);
      if (PstateMsr.Field.PstateEn == 0) {
        // Skip checking Pi ~ Pmin, check P0 for next time
        i = PS_MAX_REG - PS_MIN_REG;
        continue;
      } else {
        MaxPstate++;
      }
    }
  }

  // If no registers were modified then return
  if (!Modified) {
    return;
  }

  // MaxPstate is 0 based
  MaxPstate--;
  ASSERT (MaxPstate < 8);

  //
  // Update PstateMaxVal and CurPstateLimit
  //

  SystemDieCount = 0;
  for (SocketLoop = 0; SocketLoop < NumberOfSockets; SocketLoop++) {
    if (FabricTopologyServices->GetProcessorInfo (FabricTopologyServices, SocketLoop, &NumberOfDies, NULL) != EFI_SUCCESS) {
      return;
    }
    for (DieLoop = 0; DieLoop < NumberOfDies; DieLoop++) {
      SystemDieCount++;
      if (CoreTopologyServices->GetCoreTopologyOnDie (CoreTopologyServices, SocketLoop, DieLoop, &NumberOfComplexes, &NumberOfCores, NULL) != EFI_SUCCESS) {
        return;
      }

      ApobInstanceId = ((UINT32) SocketLoop << 8) | (UINT32) DieLoop;
      for (ComplexLoop = 0; ComplexLoop < NumberOfComplexes; ComplexLoop++) {
        ApobGetPhysComplexNumber (ApobInstanceId, CCD_INDEX_NOT_USED, (UINT32) ComplexLoop, &PhysComplexNumber);
        if (PhysComplexNumber == CCX_NOT_PRESENT) {
          return;
        }
        for (CoreLoop = 0; CoreLoop < NumberOfCores; CoreLoop++) {
          ApobGetPhysCoreNumber (ApobInstanceId, CCD_INDEX_NOT_USED, (UINT32) ComplexLoop, (UINT32) CoreLoop, &PhysCoreNumber);
          if (PhysCoreNumber == CCX_NOT_PRESENT) {
            return;
          }
          NbioSmuServices->AmdSmuRegisterRMW (NbioSmuServices, (UINT32) (SystemDieCount - 1), 0x180010BC | (((UINT32) PhysComplexNumber) << 22) | (((UINT32) PhysCoreNumber) << 17), 0xFFFFFF8F, (MaxPstate << 4));
        }
      }
    }
  }

  return;
}


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 * SwitchPstateOnAllCores - routine to switch Pstates on all cores.
 *
 *
 * @param[in]  *SwitchPstate  Pointer to struct with data for Pstate transition
 *
 *
 */
VOID
SwitchPstateOnAllCores (
  IN       CCX_SWITCH_PSTATE *SwitchPstate
  )
{
  SwitchPstate->WaitForCompletion = FALSE;
  CcxRunFunctionOnAps (ALL_THREADS, CcxSwitchPstate, SwitchPstate, NON_BLOCKING_MODE);
  SwitchPstate->WaitForCompletion = TRUE;
  CcxSwitchPstate (SwitchPstate);
}

VOID
UpdateMsrOnAllCores (
  IN       CCX_UPDATE_MSR *Msr
  )
{
  AsmWriteMsr64 (Msr->MsrAddr, Msr->MsrData);
}

