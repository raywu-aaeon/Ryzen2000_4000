/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Fabric Core Coherent Master initialization.
 *
 * This funtion initializes the CCM devices in the fabric.
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
#include <Library/IdsLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include <FabricRegistersRV.h>
#include <Library/FabricRegisterAccLib.h>
#include "Filecode.h"
#include "FabricCcmInit.h"

#define FILECODE FABRIC_RV_FABRICRVPEI_FABRICCCMINIT_FILECODE

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
CONST UINTN ROMDATA RvCcmInstanceIds[] = {
  RV_CCM0_INSTANCE_ID,
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
 *  FabricCcmInit
 *
 *  Description:
 *    This funtion initializes the CCM devices in the fabric.
 *
 */
VOID
FabricCcmInit (
  IN       CONST EFI_PEI_SERVICES       **PeiServices,
  IN       AMD_PEI_SOC_LOGICAL_ID_PPI   *SocLogicalIdPpi
  )
{
  UINTN                                 i;
  CCM_CFG_REGISTER                      CcmCfg;
  CCM_CFG1_REGISTER                     CcmCfg1;
  MASTER_REQ_PRI_REGISTER               MasterReqPri;
  MASTER_LL_LP_REQ_PRI_THRESH_REGISTER  MasterLlLpReqPriThresh;

  MasterReqPri.Value = 0;
  MasterReqPri.Field.LPRdReqPri = 2;
  MasterReqPri.Field.UseSdpReqPri = 1;
  for (i = 0; i < (sizeof (RvCcmInstanceIds) / sizeof (RvCcmInstanceIds[0])); i++) {
    FabricRegisterAccWrite (0, 0, MASTER_REQ_PRI_FUNC, MASTER_REQ_PRI_REG, RvCcmInstanceIds[i], MasterReqPri.Value, FALSE);
  }

  MasterLlLpReqPriThresh.Value = 0;
  MasterLlLpReqPriThresh.Field.LPCumElvPriReqThr = 0x10;
  MasterLlLpReqPriThresh.Field.LPElvPriReqThr = 2;
  FabricRegisterAccWrite (0, 0, MASTER_LL_LP_REQ_PRI_THRESH_FUNC, MASTER_LL_LP_REQ_PRI_THRESH_REG, FABRIC_REG_ACC_BC, MasterLlLpReqPriThresh.Value, FALSE);

  for (i = 0; i < (sizeof (RvCcmInstanceIds) / sizeof (RvCcmInstanceIds[0])); i++) {
    CcmCfg.Value = FabricRegisterAccRead (0, 0, CCM_CFG_FUNC, CCM_CFG_REG, RvCcmInstanceIds[i]);
    CcmCfg.Field.DisProtErrRsp = 1;
    FabricRegisterAccWrite (0, 0, CCM_CFG_FUNC, CCM_CFG_REG, RvCcmInstanceIds[i], CcmCfg.Value, FALSE);

    CcmCfg1.Value = FabricRegisterAccRead (0, 0, CCM_CFG1_FUNC, CCM_CFG1_REG, RvCcmInstanceIds[i]);
    CcmCfg1.Field.EnExtPciGt8BTgtAbt = 1;
    FabricRegisterAccWrite (0, 0, CCM_CFG1_FUNC, CCM_CFG1_REG, RvCcmInstanceIds[i], CcmCfg1.Value, FALSE);
  }
}

