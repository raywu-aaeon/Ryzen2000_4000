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
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/PcdLib.h>
#include <IdsHookId.h>
#include <IdsNvIdSSP.h>
#include <IdsNvDefSSP.h>

#include "smu11_bios_if.h"

#define FILECODE LIBRARY_NBIOIDSHOOKSSPLIB_DXE_NBIOIDSHOOKSSPLIBDXE_FILECODE

/**
 *
 * IDS HOOK for NBIO After CCX
 *
 *
 *
 * @param[in] HookId          IDS HOOK ID
 * @param[in] Handle          Handle
 * @param[in] Data            Data
 * @retval    AGESA_STATUS
 *
 **/
IDS_HOOK_STATUS
CmnHookFuncNbioAfterCcx (
  HOOK_ID HookId,
  VOID *Handle,
  VOID *Data
  )
{
  return IDS_HOOK_SUCCESS;
}
/**
 *
 * IDS HOOK for NBIO PCIe AER initialization
 *
 *
 *
 * @param[in] HookId          IDS HOOK ID
 * @param[in] Handle          Handle
 * @param[in] Data            Data
 * @retval    AGESA_STATUS
 *
 **/
IDS_HOOK_STATUS
CmnHookFuncNbioPcieAerInit (
  HOOK_ID HookId,
  VOID *Handle,
  VOID *Data
  )
{
  return IDS_HOOK_SUCCESS;
}

/**
 *
 * IDS HOOK for SMU initialization
 *
 *
 *
 * @param[in] HookId          IDS HOOK ID
 * @param[in] Handle          Handle
 * @param[in] Data            Data
 * @retval    AGESA_STATUS
 *
 **/
IDS_HOOK_STATUS
CmnHookFuncNbioSMUInit (
  HOOK_ID   HookId,
  VOID      *Handle,
  VOID      *Data
  )
{
  UINT64     IdsNvValue;
  UINT32     Value;
  PPTable_t  *PPTable;

  PPTable = (PPTable_t*)Data;

  ASSERT (Handle != NULL);

  // Common/External SMU Feature Flags
  Value = PcdGet32 (PcdSmuFeatureControlDefines);
  //DF Cstates
  IDS_NV_READ_SKIP (IDSNVID_CMN_GNB_SMU_DF_CSTATES, &IdsNvValue) {
    if (IdsNvValue != 0xf) {
      Value &= (UINT32) (~BIT19);
      if (IdsNvValue == 1) {
        Value |= BIT19;
      }
    }
  }
  PcdSet32 (PcdSmuFeatureControlDefines, Value);
  IDS_HDT_CONSOLE (GNB_TRACE, "PcdSmuFeatureControlDefines(0x%08x)\n", Value);

  //Determinism Slider: If Auto set to enable (agesa PCD is 0 by default)
  IDS_NV_READ_SKIP (IDSNVID_CMN_DETERMINISM_SLIDER, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_CMN_DETERMINISM_SLIDER_POWER:
      PPTable->DeterminismPercentage = 0; // Power
      break;
    case IDSOPT_CMN_DETERMINISM_SLIDER_AUTO:
    case IDSOPT_CMN_DETERMINISM_SLIDER_PERFORMANCE:
      PPTable->DeterminismPercentage = 100; // Performance
      break;
    }
  }

  return IDS_HOOK_SUCCESS;
}

#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define NBIO_SSP_IDS_HOOKS_DXE_INT
#else
  #include <Internal/NbioIdsHookSspLibDxeInt.h>
#endif

IDS_HOOK_ELEMENT NbioSspIdsHookFuncs[] = {
  {
    IDS_HOOK_NBIO_AFTER_CCX,
    &CmnHookFuncNbioAfterCcx
  },
  {
    IDS_HOOK_NBIO_PCIE_AER_INIT,
    &CmnHookFuncNbioPcieAerInit
  },
  {
    IDS_HOOK_NBIO_SMU_INIT,
    &CmnHookFuncNbioSMUInit
  },
  NBIO_SSP_IDS_HOOKS_DXE_INT
  IDS_HOOKS_END
};

IDS_HOOK_TABLE NbioSspIdsHookTable = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  NbioSspIdsHookFuncs
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &NbioSspIdsHookTable;
  return AGESA_SUCCESS;
}

