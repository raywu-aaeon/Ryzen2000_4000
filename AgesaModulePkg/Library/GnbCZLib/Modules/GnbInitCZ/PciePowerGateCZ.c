/* $NoKeywords:$ */
/**
 * @file
 *
 * PCIe power gate initialization
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
*****************************************************************************
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
*
*/
/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  <Library/BaseLib.h>
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "OptionGnb.h"
#include  "GnbPcieConfig.h"
#include  "GnbPcieFamServices.h"
#include  "GnbPcieInitLib.h"
#include  "GnbSmuInitLibV8.h"
#include  "GnbRegistersCZ.h"
#include  "GnbRegisterAccCZ.h"
#include  "PciePowerGateCZ.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_PCIEPOWERGATECZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern GNB_BUILD_OPTIONS      GnbBuildOptions;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------*/
/**
 * Power down unused lanes
 *
 *
 *
 *
 * @param[in]       Wrapper         Pointer to wrapper configuration
 * @param[in, out]  Buffer          Not used
 * @param[in]       Pcie            Pointer to global PCIe configuration
 * @retval          AGESA_SUCCESS
 *
 */

AGESA_STATUS
STATIC
PciePowerGatePowerDownUnusedLanesCallbackCZ (
  IN       PCIe_WRAPPER_CONFIG   *Wrapper,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8                   Index;
  UINTN                   State;
  UINT32                  LaneBitmap;
  UINT32                  LaneBitmapNative;
  UINT16                  StartLane;
  UINT16                  EndLane;
  DEV_OBJECT              DevObject;
  UINT32                  SmuArg[6];
  GNB_HANDLE              *GnbHandle;
  SMU_PCIE_PHY_LN_STRUCT  Phy_Data;
  UINT8                   PowerGatingFlags;


  IDS_HDT_CONSOLE (GNB_TRACE, "PciePowerGatePowerDownUnusedLanesCallbackCZ Enter\n");

  if (Wrapper->Features.PowerOffUnusedLanes != 0) {
    PowerGatingFlags = *(UINT8 *) Buffer;
    Phy_Data.Value = 0;
    GnbHandle = GnbGetHandle (GnbLibGetHeader (Pcie));
    GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, (AMD_CONFIG_PARAMS *)Pcie->StdHeader, &DevObject, SmuArg);

    LaneBitmapNative = PcieUtilGetWrapperLaneBitMap (
                        LANE_TYPE_PHY_NATIVE_ALL,
                        0,
                        Wrapper
                        );
    LaneBitmap = PcieUtilGetWrapperLaneBitMap (
                   LANE_TYPE_PHY_NATIVE_ALL,
                   LANE_TYPE_PCIE_PHY_NATIVE_ALLOC_ACTIVE | LANE_TYPE_DDI_PHY_NATIVE_ACTIVE | LANE_TYPE_PCIE_PHY_NATIVE_HOTPLUG,
                   Wrapper
                   );
    if (LaneBitmap == LaneBitmapNative) {
      State = 0;
      StartLane = 0;
      EndLane = 0;
      for (Index = 0; Index <= (HighBitSet32 (LaneBitmap) + 1); Index++) {
        if ((State == 0) && ((LaneBitmap & (1 << Index)) != 0)) {
          StartLane = Index;
          State = 1;
        } else if ((State == 1) && ((LaneBitmap & (1 << Index)) == 0)) {
          EndLane = Index - 1;
          State = 0;

          Phy_Data.Field.Tx = 1;
          Phy_Data.Field.Rx = 1;
          Phy_Data.Field.Core = 1;
          if ((PowerGatingFlags & PCIE_POWERGATING_SKIP_CORE) != 0) {
            Phy_Data.Field.SkipCore = 1;
          }
          if ((PowerGatingFlags & PCIE_POWERGATING_SKIP_PHY) != 0) {
            Phy_Data.Field.SkipPhy = 1;
          }
          Phy_Data.Field.LowerLaneID = StartLane + Wrapper->StartPhyLane;
          Phy_Data.Field.UpperLaneID = EndLane + Wrapper->StartPhyLane;
          IDS_HDT_CONSOLE (
            GNB_TRACE,
            "  LowerLaneID - %02d UpperLaneID - %02d Tx - %d  Rx - %d Core - %d Exit\n",
            Phy_Data.Field.LowerLaneID,
            Phy_Data.Field.UpperLaneID,
            Phy_Data.Field.Tx,
            Phy_Data.Field.Rx,
            Phy_Data.Field.Core
            );

          SmuArg[0] = Phy_Data.Value;
          GnbSmuServiceRequestV8 (
            &DevObject,
            SMC_MSG_PHY_LN_OFF,
            SmuArg,
            GNB_REG_ACC_FLAG_S3SAVE
            );
        }
      }
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PciePowerGatePowerDownUnusedLanesCallbackCZ Exit\n");
  return AGESA_SUCCESS;
}




/*----------------------------------------------------------------------------------------*/
/**
 * Pcie Power gate init
 *
 *   Late PCIe initialization
 *
 * @param[in]  Pcie                Pointer to global PCIe configuration
 * @retval     AGESA_SUCCESS       Topology successfully mapped
 */

AGESA_STATUS
PciePowerGateCZ (
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8                   PowerGatingFlags;
  GNB_HANDLE              *GnbHandle;

  IDS_HDT_CONSOLE (GNB_TRACE, "PciePowerGateCZ Enter\n");

  GnbHandle = GnbGetHandle (GnbLibGetHeader (Pcie));

  PowerGatingFlags = GnbBuildOptions.CfgPciePowerGatingFlags;

  IDS_HDT_CONSOLE (GNB_TRACE, "  PowerGatingFlags = %02x\n", PowerGatingFlags);

  IDS_OPTION_HOOK (IDS_GNB_PCIE_POWER_GATING, &PowerGatingFlags, GnbLibGetHeader (Pcie));
  IDS_HDT_CONSOLE (GNB_TRACE, "  PowerGatingFlags = %02x\n", PowerGatingFlags);

  // Power down unused lanes
  PcieConfigRunProcForAllWrappers (
    DESCRIPTOR_PCIE_WRAPPER | DESCRIPTOR_DDI_WRAPPER,
    PciePowerGatePowerDownUnusedLanesCallbackCZ,
    &PowerGatingFlags,
    Pcie
    );

  IDS_HDT_CONSOLE (GNB_TRACE, "PciePowerGateCZ Exit\n");
  return  AGESA_SUCCESS;
}

