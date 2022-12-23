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
#include "FabricRegistersZP.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Library/AmdIdsHookLib.h"
#include "Library/BaseFabricTopologyLib.h"
#include "Library/FabricRegisterAccLib.h"
#include "IdsHookId.h"
#include "IdsNvIdZP.h"
#include "IdsNvDefZP.h"
#include "Filecode.h"

#define FILECODE LIBRARY_FABRICIDSHOOKZPLIB_PEI_FABRICIDSHOOKZPLIBPEI_FILECODE


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

IDS_HOOK_STATUS
FabricZpPeiDfFreezeModuleQueuesOnError (
  HOOK_ID HookId,
  VOID    *Handle,
  VOID    *Data
  )
{
  UINT64                IdsNvValue;
  DF_GLBL_CTRL_REGISTER *PDfGlblCtrl;

  IDS_HDT_CONSOLE (CPU_TRACE, "FabricZpFreezeModuleQueuesOnError Option\n");

  //Disable DF sync flood propagation
  // D18F03F8[3]
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


IDS_HOOK_STATUS
FabricZpPeiDfRedirectScrubCtrl (
  HOOK_ID HookId,
  VOID    *Handle,
  VOID    *Data
  )
{
  UINT64                IdsNvValue;
  BOOLEAN               *PDfRedirScrubCtrl;

  IDS_HDT_CONSOLE (CPU_TRACE, "FabricZpPeiRedirectScrubCtrl Option\n");

  //Redirect scrubber control
  // D18F6x58[0]
  PDfRedirScrubCtrl = (BOOLEAN *) Data;
  IDS_NV_READ_SKIP (IDSNVID_DF_CMN_REDIR_SCRUB_CTRL, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_DISABLED:
      *PDfRedirScrubCtrl = 0;
      break;
    case IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_ENABLED:
      *PDfRedirScrubCtrl = 1;
      break;
    case IDSOPT_DF_CMN_REDIR_SCRUB_CTRL_AUTO:
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }
  return IDS_HOOK_SUCCESS;
}


IDS_HOOK_STATUS
FabricZpPeiDfDramScrubTime (
  HOOK_ID HookId,
  VOID    *Handle,
  VOID    *Data
  )
{
  UINT64                IdsNvValue;
  UINT8                 *PDfDramScrubTime;

  IDS_HDT_CONSOLE (CPU_TRACE, "FabricZpPeiDramScrubTime Option\n");

  //DRAM scrub time
  PDfDramScrubTime = (UINT8 *) Data;
  IDS_NV_READ_SKIP (IDSNVID_DF_CMN_DRAM_SCRUB_TIME, &IdsNvValue) {
    switch (IdsNvValue) {
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_DISABLED:
      *PDfDramScrubTime = 0;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_1HOUR:
      *PDfDramScrubTime = 1;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_4HOURS:
      *PDfDramScrubTime = 4;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_8HOURS:
      *PDfDramScrubTime = 8;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_16HOURS:
      *PDfDramScrubTime = 16;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_24HOURS:
      *PDfDramScrubTime = 24;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_48HOURS:
      *PDfDramScrubTime = 48;
      break;
    case IDSOPT_DF_CMN_DRAM_SCRUB_TIME_AUTO:
      break;
    default:
      ASSERT (FALSE);
      break;
    }
  }
  return IDS_HOOK_SUCCESS;
}


#ifndef IDS_HOOK_INTERNAL_SUPPORT
  #define FABRIC_ZP_IDS_HOOKS_INT_PEI
#else
  #include "Internal/FabricIdsHookZpLibIntPei.h"
#endif

IDS_HOOK_ELEMENT FabricZpIdsHooksPei[] = {
  {
    IDS_HOOK_DF_RAS_INIT,
    &FabricZpPeiDfFreezeModuleQueuesOnError
  },
  {
    IDS_HOOK_PIE_REDIRECT_SCRUB_CTRL_INIT,
    &FabricZpPeiDfRedirectScrubCtrl
  },
  {
    IDS_HOOK_PIE_DRAM_SCRUB_TIME_INIT,
    &FabricZpPeiDfDramScrubTime
  },
  FABRIC_ZP_IDS_HOOKS_INT_PEI
  IDS_HOOKS_END
};

IDS_HOOK_TABLE FabricZpIdsHookTablePei = {
  IDS_HOOK_TABLE_HEADER_REV1_DATA,
  FabricZpIdsHooksPei
};


AGESA_STATUS
GetIdsHookTable (
  IDS_HOOK_TABLE **IdsHookTable
  )
{
  *IdsHookTable = &FabricZpIdsHookTablePei;
  return AGESA_SUCCESS;
}
