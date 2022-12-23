/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Fabric IDS hook implementation
 *
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
#include <FabricRegistersDf3.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include <Library/FabricRegisterAccLib.h>
#include <IdsHookId.h>
#include <IdsNvIdSSP.h>
#include <IdsNvDefSSP.h>
#include <Filecode.h>

#define FILECODE LIBRARY_FABRICIDSHOOKSSPLIB_PEI_FABRICIDSHOOKSSPLIBPEI_FILECODE


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

IDS_HOOK_STATUS
FabricSspPeiDfFreezeModuleQueuesOnError (
  HOOK_ID HookId,
  VOID    *Handle,
  VOID    *Data
  )
{
  UINT64                IdsNvValue;
  DF_GLBL_CTRL_REGISTER *PDfGlblCtrl;

  IDS_HDT_CONSOLE (CPU_TRACE, "FabricSspFreezeModuleQueuesOnError Option\n");

  // Freeze DF module queues on error
  // D18F0x3F8[3]
  PDfGlblCtrl = (DF_GLBL_CTRL_REGISTER *) Data;
  IDS_NV_READ_SKIP (IDSNVID_DF_CMN_FREEZE_QUEUE_ERROR, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_DISABLED:
      PDfGlblCtrl->Field.DisImmSyncFloodOnFatalErr = 1;
      break;
    case IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_ENABLED:
      break;
    case IDSOPT_DF_CMN_FREEZE_QUEUE_ERROR_AUTO:
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }
  return IDS_HOOK_SUCCESS;
}


// DRAM scrub time --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabricDramScrubTime

// Redirect scrubber control --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabricEccScrubRedirection

// Poison scrubber control --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabricEccScrubPoisoned

// Redirect scrubber limit --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabricEccScrubRedirectionLimit

// Disable DF sync flood propagation --- ABL
// APCB_TOKEN_UID_DF_SYNC_FLOOD_PROP

// GMI encryption control --- ABL
// APCB_TOKEN_UID_DF_GMI_ENCRYPT

// xGMI encryption control --- ABL
// APCB_TOKEN_UID_DF_XGMI_ENCRYPT

// CC6 memory region encryption --- ABL
// APCB_TOKEN_UID_DF_SAVE_RESTORE_MEM_ENCRYPT

// Location of private memory regions --- ABL
// APCB_TOKEN_UID_DF_SYS_STORAGE_AT_TOP_OF_MEM

// System probe filter --- ABL
// APCB_TOKEN_UID_DF_PROBE_FILTER

// Memory interleaving --- ABL
// APCB_TOKEN_UID_DF_MEM_INTERLEAVING

// Memory interleaving size --- ABL
// APCB_TOKEN_UID_DF_MEM_INTERLEAVING_SIZE

// Channel interleaving hash --- ABL
// APCB_TOKEN_UID_DF_CHAN_INTLV_HASH

// Memory Clear --- ABL
// APCB_TOKEN_UID_DF_MEM_CLEAR

// CAKE CRC perf bounds --- ABL
// APCB_TOKEN_UID_DF_CAKE_CRC_THRESH_PERF_BOUNDS

// GMI2 replay --- ABL
// APCB_TOKEN_UID_DF_GMI2_REPLAY

// ACPI SLIT Distance Control --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabricSlitDegree

// ACPI SLIT non-self distance --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabric2ndDegreeSlitDistance

// ACPI SLIT same socket distance --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabric3rdDegreeSlitLocalDistance

// ACPI SLIT remote socket distance --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdFabric3rdDegreeSlitRemoteDistance

// PSP error injection support --- AGESA
// gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdPspEinjSupport

#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define FABRIC_SSP_IDS_HOOKS_INT_PEI
#else
  #include "Internal/FabricIdsHookSspLibIntPei.h"
#endif

IDS_HOOK_ELEMENT FabricSspIdsHooksPei[] = {
  {
    IDS_HOOK_DF_RAS_INIT,
    &FabricSspPeiDfFreezeModuleQueuesOnError
  },
  FABRIC_SSP_IDS_HOOKS_INT_PEI
  IDS_HOOKS_END
};

IDS_HOOK_TABLE FabricSspIdsHookTablePei = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  FabricSspIdsHooksPei
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &FabricSspIdsHookTablePei;
  return AGESA_SUCCESS;
}

