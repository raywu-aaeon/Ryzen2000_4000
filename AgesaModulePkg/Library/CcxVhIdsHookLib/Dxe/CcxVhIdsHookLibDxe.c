/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Valhalla API, and related functions.
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
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include "CcxVhIdsSyncMsr.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CcxRolesLib.h>
#include <Protocol/MpService.h>
#include <Protocol/SmmControl2.h>
#include <Guid/EventGroup.h>
#include <IdsHookId.h>
#include <IdsNvIdSSP.h>
#include <IdsNvDefSSP.h>
#include "CcxVhIdsCustomPstates.h"
#include <Filecode.h>

#define FILECODE LIBRARY_CCXVHIDSHOOKLIB_DXE_CCXVHIDSHOOKLIBDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
EFI_EVENT                             CcxIdsVhDxeMpServiceEvent;

VOID                                  *CcxIdsVhForMpServiceEvent;

#define IDS_MAX_NUM_OF_SYNC_MSR 20
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
EFIAPI
CcxIdsVhDxeMpServiceCallBack (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  );

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

IDS_HOOK_STATUS
CcxVhDxeAfterApLaunch (
  HOOK_ID   HookId,
  VOID      *Handle,
  VOID      *Data
  )
{
  EFI_STATUS        Status;
  EFI_STATUS        CalledStatus;
  AMD_CONFIG_PARAMS StdHeader;

  Status = EFI_SUCCESS;

  if (CcxIsBsp (&StdHeader)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "CcxVhDxeAfterApLaunch External Options\n");

    // L1 Stream HW Prefetcher --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdL1StreamPrefetcher

    // L2 Stream HW Prefetcher --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdL2StreamPrefetcher

    // Platform First Error Handling --- AGESA
    // gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdAmdCcxCfgPFEHEnable

    // Core Performance Boost --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdCpbMode

    // Global C-state Control --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdCStateMode

    // Power Supply Idle Control --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdPowerSupplyIdleControl

    // SEV ASID Count --- ABL
    // APCB_TOKEN_UID_CCX_SEV_ASID_COUNT

    // SEV-ES ASID Space Limit --- ABL
    // APCB_TOKEN_UID_CCX_MIN_SEV_ASID

    // XTRIG7 Workaround --- ABL
    // APCB_TOKEN_UID_XTRIG7_WORKAROUND

    // ACPI _CST C1 Declaration --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdAcpiCstC1

    // Core Watchdog Timer Enable --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdCpuWdtEn

    // Core Watchdog Timer Interval --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdAmdCpuWdtTimeout

    // Core Watchdog Timer Severity --- AGESA
    // gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdAmdCpuWdtSeverity

    // MCA error thresh enable --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdMcaErrThreshEn

    // MCA error thresh count --- AGESA
    // gEfiAmdAgesaPkgTokenSpaceGuid.PcdMcaErrThreshCount

    // RedirectForReturnDis --- AGESA
    // gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdAmdRedirectForReturnDis

    // Opcache Control --- AGESA
    // gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdAmdOpcacheCtrl

    // Streaming Stores Control --- AGESA
    // gEfiAmdAgesaModulePkgTokenSpaceGuid.PcdAmdStreamingStoresCtrl
  }

  //
  // Set up call back after gEfiMpServiceProtocolGuid.
  //
  CalledStatus = gBS->CreateEventEx (
                           EVT_NOTIFY_SIGNAL,
                           TPL_NOTIFY,
                           CcxIdsVhDxeMpServiceCallBack,
                           NULL,
                           NULL,
                           &CcxIdsVhDxeMpServiceEvent
                           );
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  CalledStatus = gBS->RegisterProtocolNotify (
                          &gEfiMpServiceProtocolGuid,
                          CcxIdsVhDxeMpServiceEvent,
                          &(CcxIdsVhForMpServiceEvent)
                          );
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  if (Status == EFI_SUCCESS) {
    return IDS_HOOK_SUCCESS;
  } else {
    return IDS_HOOK_ERROR;
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * CcxIdsVhDxeMpServiceCallBack
 *
 *
 *  Parameters:
 *    @param[in]     Event
 *    @param[in]     *Context
 *
 *    @retval        VOID
 */
VOID
EFIAPI
CcxIdsVhDxeMpServiceCallBack (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  UINT16              i;
  IDS_BSC_AP_MSR_SYNC ApMsrSync[IDS_MAX_NUM_OF_SYNC_MSR];
  AMD_CONFIG_PARAMS   StdHeader;

  ZeroMem (ApMsrSync, sizeof (ApMsrSync));

  i = 0;

  // End of sync-up list

  ASSERT (i < IDS_MAX_NUM_OF_SYNC_MSR);
  if (i >= IDS_MAX_NUM_OF_SYNC_MSR) {
    IDS_HDT_CONSOLE (CPU_TRACE, "ERROR: IDS ApMsrSync overflow\n");
    IDS_DEADLOOP ()
  }
  CcxIdsVhDxeSyncMsr (ApMsrSync, &StdHeader);
}


#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define CCX_IDS_HOOKS_INT
#else
  #include <Internal/CcxVhIdsHookLibIntDxe.h>
#endif

IDS_HOOK_ELEMENT CcxVhIdsHooks[] = {
//  {
//    IDS_HOOK_CCX_AFTER_AP_LAUNCH,
//    &CcxVhDxeAfterApLaunch
//  },
  {
    IDS_HOOK_CCX_CUSTOM_PSTATES,
    &CcxVhIdsDxeCustomPstates
  },
  CCX_IDS_HOOKS_INT
  IDS_HOOKS_END
};

IDS_HOOK_TABLE CcxVhIdsHookTable = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  CcxVhIdsHooks
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &CcxVhIdsHookTable;
  return AGESA_SUCCESS;
}

