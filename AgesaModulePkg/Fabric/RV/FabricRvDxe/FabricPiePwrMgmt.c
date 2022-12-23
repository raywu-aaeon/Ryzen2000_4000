/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Fabric PIE power management initialization.
 *
 * This funtion initializes fabric power management features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "AMD.h"
#include <Library/BaseFabricTopologyLib.h>
#include <FabricRegistersRV.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/AmdIdsHookLib.h>
#include "Filecode.h"
#include "cpuRegisters.h"
#include "FabricPiePwrMgmt.h"
#include <Library/BaseCoreLogicalIdLib.h>
#include "SocLogicalId.h"

#define FILECODE FABRIC_RV_FABRICRVDXE_FABRICPIEPWRMGMT_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

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
 *  FabricPiePwrMgmtInit
 *
 *  Description:
 *    This funtion initializes fabric power management features.
 *
 */
VOID
FabricPiePwrMgmtInit (
  VOID
  )
{
  CSTATE_CTRL_REGISTER          CstateCtrl;
  PWR_MGMT_CFG1_REGISTER        PwrMgmtCfg1;
  PWR_MGMT_TMR_CTRL0_REGISTER   PwrMgmtTmrCtrl0;
  PWR_MGMT_TMR_CTRL1_REGISTER   PwrMgmtTmrCtrl1;
  DF_PC6_SERVICE_CTRL_REGISTER  DfPc6ServiceCtrl;
  PWR_MGMT_CFG0_REGISTER        PwrMgmtCfg0;
  PWR_MGMT_HYST_CTRL_REGISTER   PwrMgtHystCtl;
  SOC_LOGICAL_ID                LogicalId;

  BaseGetLogicalIdOnExecutingCore (&LogicalId);

  CstateCtrl.Value = FabricRegisterAccRead (0, 0, CSTATE_CTRL_FUNC, CSTATE_CTRL_REG, FABRIC_REG_ACC_BC);
  CstateCtrl.Field.DfCstateDisable =   (PcdGet8 (PcdAmdCStateMode) == 1) ? 0 : 1;
  CstateCtrl.Field.DfCstateClkPwrDnEn = 1;
  CstateCtrl.Field.DfCstateSelfRefrEn = 1;
  CstateCtrl.Field.DfCstateMmStutterOptEn = 1;
  CstateCtrl.Field.DfCstateMmPwrGateOptEn = 1;
  CstateCtrl.Field.DfCstatePwrGateEn = 1;
  IDS_HOOK (IDS_HOOK_PIE_PWR_MGMT_INIT, NULL, (VOID *) &CstateCtrl);
  if ((LogicalId.Family == AMD_FAMILY_17_RV) && ((LogicalId.Revision & AMD_REV_F17_RV_A0) != 0)) {
    CstateCtrl.Field.DfCstatePwrGateEn = 0;
  }
  FabricRegisterAccWrite (0, 0, CSTATE_CTRL_FUNC, CSTATE_CTRL_REG, FABRIC_REG_ACC_BC, CstateCtrl.Value, TRUE);

  DfPc6ServiceCtrl.Value = FabricRegisterAccRead (0, 0, DF_PC6_SERVICE_CTRL_FUNC, DF_PC6_SERVICE_CTRL_REG, FABRIC_REG_ACC_BC);
  DfPc6ServiceCtrl.Field.Pc6RampOnFchHint = 1;
  FabricRegisterAccWrite (0, 0, DF_PC6_SERVICE_CTRL_FUNC, DF_PC6_SERVICE_CTRL_REG, FABRIC_REG_ACC_BC, DfPc6ServiceCtrl.Value, TRUE);

  PwrMgmtCfg1.Value = FabricRegisterAccRead (0, 0, PWR_MGMT_CFG1_FUNC, PWR_MGMT_CFG1_REG, FABRIC_REG_ACC_BC);
  PwrMgmtCfg1.Field.VdciBusyPstateChkDis = 1;
  FabricRegisterAccWrite (0, 0, PWR_MGMT_CFG1_FUNC, PWR_MGMT_CFG1_REG, FABRIC_REG_ACC_BC, PwrMgmtCfg1.Value, TRUE);

  PwrMgmtTmrCtrl0.Value = FabricRegisterAccRead (0, 0, PWR_MGMT_TMR_CTRL0_FUNC, PWR_MGMT_TMR_CTRL0_REG, FABRIC_REG_ACC_BC);
  PwrMgmtTmrCtrl0.Field.ClkGaterPropDly = 16;
  PwrMgmtTmrCtrl0.Field.CreditReleaseToDrainDly = 23;
  PwrMgmtTmrCtrl0.Field.ComponentDrainedSampleDly = 23;
  PwrMgmtTmrCtrl0.Field.ProbesDrainedSampleDly = 20;
  FabricRegisterAccWrite (0, 0, PWR_MGMT_TMR_CTRL0_FUNC, PWR_MGMT_TMR_CTRL0_REG, FABRIC_REG_ACC_BC, PwrMgmtTmrCtrl0.Value, TRUE);

  PwrMgmtTmrCtrl1.Value = FabricRegisterAccRead (0, 0, PWR_MGMT_TMR_CTRL1_FUNC, PWR_MGMT_TMR_CTRL1_REG, FABRIC_REG_ACC_BC);
  PwrMgmtTmrCtrl1.Field.AllDrainedTimeoutDly = 25;
  PwrMgmtTmrCtrl1.Field.AllDrainedTimeoutScale = 2;
  FabricRegisterAccWrite (0, 0, PWR_MGMT_TMR_CTRL1_FUNC, PWR_MGMT_TMR_CTRL1_REG, FABRIC_REG_ACC_BC, PwrMgmtTmrCtrl1.Value, TRUE);

  PwrMgmtCfg0.Value = FabricRegisterAccRead (0, 0, PWR_MGMT_CFG0_FUNC, PWR_MGMT_CFG0_REG, FABRIC_REG_ACC_BC);
  PwrMgmtCfg0.Field.DowngradeCstateCommonClkGate = 0;
  FabricRegisterAccWrite (0, 0, PWR_MGMT_CFG0_FUNC, PWR_MGMT_CFG0_REG, FABRIC_REG_ACC_BC, PwrMgmtCfg0.Value, TRUE);

  PwrMgmtCfg0.Value = FabricRegisterAccRead (0, 0, PWR_MGMT_CFG0_FUNC, PWR_MGMT_CFG0_REG, FABRIC_REG_ACC_BC);
  PwrMgmtCfg0.Field.DowngradeCstateCommonClkGate = 0;
  if ((LogicalId.Family == AMD_FAMILY_17_RV) && ((LogicalId.Revision & AMD_REV_F17_RV_A0) != 0)) {
    PwrMgmtCfg0.Field.MmhubEarlyDisconDis = 1;
  }
  FabricRegisterAccWrite (0, 0, PWR_MGMT_CFG0_FUNC, PWR_MGMT_CFG0_REG, FABRIC_REG_ACC_BC, PwrMgmtCfg0.Value, TRUE);

  if ((LogicalId.Family == AMD_FAMILY_17_RV) && ((LogicalId.Revision & AMD_REV_F17_RV_A0) != 0)) {
    PwrMgtHystCtl.Value = FabricRegisterAccRead (0, 0, PWR_MGMT_HYST_CTRL_FUNC, PWR_MGMT_HYST_CTRL_REG, FABRIC_REG_ACC_BC);
    PwrMgtHystCtl.Field.DfCstateHyst = 14;
    FabricRegisterAccWrite (0, 0, PWR_MGMT_HYST_CTRL_FUNC, PWR_MGMT_HYST_CTRL_REG, FABRIC_REG_ACC_BC, PwrMgtHystCtl.Value, TRUE);
  }
}


