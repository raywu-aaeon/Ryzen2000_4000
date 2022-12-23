/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD common SOC IDS functions
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
#include "Uefi.h"
#include "PiPei.h"
#include "cpuRegisters.h"
#include "Library/AmdBaseLib.h"
#include <Library/BaseLib.h>
#include "Library/IdsLib.h"
#include "Library/AmdIdsHookLib.h"
#include <Library/CcxBaseX86Lib.h>
#include <Library/CcxDownCoreLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Ppi/AmdSocPcdInitPpi.h>
#include "IdsHookId.h"
#include "Filecode.h"

#define FILECODE LIBRARY_SOCCMNIDSHOOKRVLIB_PEI_SOCCMNIDSHOOKRVLIBPEI_FILECODE


#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define SOC_IDS_HOOKS_INT
#else
  #include "Internal/SocCmnIdsHookRvLibIntPei.h"
#endif

EFI_STATUS
EFIAPI
SocRvIdsDownCoreCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  );


EFI_PEI_NOTIFY_DESCRIPTOR   mSocIdsAgesaPcdInitReadyCallback = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPcdInitReadyPpiGuid,
  SocRvIdsDownCoreCallback
};

IDS_HOOK_STATUS
SocRvIdsBeginningCmn (
  HOOK_ID   HookId,
  VOID      *Handle,
  VOID      *Data
  )
{
  EFI_PEI_SERVICES              **PeiServices;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();

  (**PeiServices).NotifyPpi (PeiServices, &mSocIdsAgesaPcdInitReadyCallback);

  return IDS_HOOK_SUCCESS;
}

EFI_STATUS
EFIAPI
SocRvIdsDownCoreCallback (
  IN  EFI_PEI_SERVICES                **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN  VOID                            *InvokePpi
  )
{
  UINT8                                 DownCoreMode;
  UINT8                                 SmtMode;
  UINTN                                 EnabledThreadCount;
  UINTN                                 EnabledCoreCount;
  UINTN                                 DesiredCoreCount;
  CPUID_DATA                            CpuId;

  IDS_HDT_CONSOLE (CPU_TRACE, "SocRvIdsDownCoreCallback External Options\n");

  DownCoreMode = PcdGet8 (PcdAmdDownCoreMode);
  SmtMode = PcdGet8 (PcdAmdSmtMode);

  if ((DownCoreMode != CCX_DOWN_CORE_AUTO) || (SmtMode != 1)) {
    switch (DownCoreMode) {
    case CCX_DOWN_CORE_1_0:
      DesiredCoreCount = 1;
      break;
    case CCX_DOWN_CORE_2_0:
      DesiredCoreCount = 2;
      break;
    case CCX_DOWN_CORE_3_0:
      DesiredCoreCount = 3;
      break;
    default:
      DesiredCoreCount = 4;
      break;
    }

    AsmCpuid (
        AMD_CPUID_ASIZE_PCCOUNT,
        &(CpuId.EAX_Reg),
        &(CpuId.EBX_Reg),
        &(CpuId.ECX_Reg),
        &(CpuId.EDX_Reg)
        );

    EnabledThreadCount = (CpuId.ECX_Reg & 0xFF) + 1; // bit 7:0
    EnabledCoreCount = EnabledThreadCount / CcxGetThreadsPerCore ();

    if (((SmtMode == 0) && (CcxGetThreadsPerCore () > 1)) ||
        (DesiredCoreCount < EnabledCoreCount)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "set PcdToggleAllPwrGoodOnCf9 to FALSE\n");
      PcdSetBool (PcdToggleAllPwrGoodOnCf9, FALSE);
    }
  }

  return EFI_SUCCESS;
}


IDS_HOOK_ELEMENT SocIdsCmnHooks[] = {
  {
    IDS_HOOK_BEGINNING_OF_AGESA,
    &SocRvIdsBeginningCmn
  },
  SOC_IDS_HOOKS_INT
  IDS_HOOKS_END
};

IDS_HOOK_TABLE SocIdsCmnHookTable = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  SocIdsCmnHooks
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &SocIdsCmnHookTable;
  return AGESA_SUCCESS;
}

