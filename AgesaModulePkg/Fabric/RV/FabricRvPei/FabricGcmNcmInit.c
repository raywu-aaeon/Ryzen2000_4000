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
UINTN
GetActiveDramChannel (
  VOID
  );

UINT32
GetDramAddrRngVal (
  IN       UINT32 CsInstance
  );
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
 *  FabricGcmNcmInit
 *
 *  Description:
 *    This funtion initializes the CCM devices in the fabric.
 *
 */
VOID
FabricGcmNcmInit (
  IN       CONST EFI_PEI_SERVICES       **PeiServices,
  IN       AMD_PEI_SOC_LOGICAL_ID_PPI   *SocLogicalIdPpi
  )
{
  GCM_NCM_CTRL_REGISTER     GcmNcmCtrl;
  MASTER_REQ_CTRL_REGISTER  MasterReqCtrl;
  UINT32                    MstDramActReqLmt;

  GcmNcmCtrl.Value = 0;
  GcmNcmCtrl.Field.MapSdpVc0ToFtiVc5 = 1;
  GcmNcmCtrl.Field.GcmSelfGenPrbRsp = 1;
  FabricRegisterAccWrite (0, 0, GCM_NCM_CTRL_FUNC, GCM_NCM_CTRL_REG, FABRIC_REG_ACC_BC, GcmNcmCtrl.Value, FALSE);

  if (GetActiveDramChannel () == 2) {
    MstDramActReqLmt = 72;
  } else {
    MstDramActReqLmt = 48;
  }
  MasterReqCtrl.Value = FabricRegisterAccRead (0, 0, MASTER_REQ_CTRL_FUNC, MASTER_REQ_CTRL_REG, RV_DCE0_INSTANCE_ID);
  MasterReqCtrl.Field.MstDramActReqLmt = MstDramActReqLmt;
  FabricRegisterAccWrite (0, 0, MASTER_REQ_CTRL_FUNC, MASTER_REQ_CTRL_REG, RV_DCE0_INSTANCE_ID, MasterReqCtrl.Value, TRUE);
}

UINTN
GetActiveDramChannel (
  VOID
  )
{
  UINT32      CsInst;
  UINTN       ActiveChannelNum;

  ActiveChannelNum = 0;
  for (CsInst = 0; CsInst < RV_NUM_CS_BLOCKS; CsInst++) {
    if (GetDramAddrRngVal (CsInst) != 0) {
      ActiveChannelNum++;
    }
  }

  return (ActiveChannelNum);
}


UINT32
GetDramAddrRngVal (
  IN       UINT32 CsInstance
  )
{
  DRAM_BASE_ADDRESS_REGISTER      DramBaseAddr;
  UINT32                          AddrMapPair;
  UINT32                          CsAddrRngVal;

  ASSERT (CsInstance < RV_NUM_CS_BLOCKS);

  CsAddrRngVal = 0;
  for (AddrMapPair = 0; AddrMapPair < NUMBER_OF_CS_DRAM_REGIONS; AddrMapPair++) {
    DramBaseAddr.Value = FabricRegisterAccRead (0, 0, DRAMBASEADDR0_FUNC, DRAMBASEADDR0_REG + (AddrMapPair << 3), RV_CS0_INSTANCE_ID + CsInstance);
    CsAddrRngVal |= (DramBaseAddr.Field.AddrRngVal << AddrMapPair);
  }

  return (CsAddrRngVal);
}

