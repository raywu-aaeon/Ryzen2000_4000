/* $NoKeywords:$ */
/**
 * @file
 *
 * DXIO Ancillary Data handlers
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#include <Filecode.h>
#include <PiPei.h>
#include <AmdPcieComplex.h>
#include <GnbDxio.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Library/BaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/GnbLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/DxioLibV1.h>

#define FILECODE LIBRARY_DXIOLIBV1_DXIOANCDATAV1_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Function to calculate the ancillary data size for a PCIe/SATA engine
 *
 *
 * @param[in]  PortPointer   Pointer to port descriptor
 */
UINT32
DxioAncDataCalcSize (
  IN       DXIO_PORT_DESCRIPTOR    *PortPointer
  )
{
  DXIO_PHY_PARAM    *PhyParam;
  UINT32            DataSize;
  UINT32            LaneCount;

  PhyParam = &PortPointer->Phy.PhyParam[0];

  DataSize = 0;
  while (PhyParam->ParamType != 0) {
    switch (PhyParam->ParamType) {
      case   rx_vref_ctrl:
      case   SSC_OFF_FRUG1:
      case   SSC_OFF_PHUG1:
      case   GEN1_txX_iboost_lvl:
      case   GEN1_txX_vboost_en:
      case   GEN1_Unsupported1:
      case   GEN1_Unsupported2:
      case   GEN1_rxX_eq_att_lvl:
      case   GEN1_rxX_eq_vga1_gain:
      case   GEN1_rxX_eq_vga2_gain:
      case   GEN1_rxX_eq_dfe_tap1:
      case   GEN1_tx_vboost_lvl:
      case   GEN2_txX_iboost_lvl:
      case   GEN2_txX_vboost_en:
      case   GEN2_Unsupported1:
      case   GEN2_Unsupported2:
      case   GEN2_rxX_eq_att_lvl:
      case   GEN2_rxX_eq_vga1_gain:
      case   GEN2_rxX_eq_vga2_gain:
      case   GEN2_rxX_eq_dfe_tap1:
      case   GEN2_tx_vboost_lvl:
      case   GEN3_txX_iboost_lvl:
      case   GEN3_txX_vboost_en:
      case   GEN3_rxX_adapt_afe_en:
      case   GEN3_rxX_adapt_dfe_en:
      case   GEN3_rxX_eq_att_lvl:
      case   GEN3_rxX_eq_vga1_gain:
      case   GEN3_rxX_eq_vga2_gain:
      case   GEN3_rxX_eq_dfe_tap1:
      case   GEN3_tx_vboost_lvl:
        // For a single-entry parameter
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        break;

      case   rxX_los_threshold:
      case   GEN1_txX_eq_pre:
      case   GEN1_txX_eq_main:
      case   GEN1_txX_eq_post:
      case   GEN1_rxX_eq_ctle_pole:
      case   GEN1_rxX_eq_ctle_boost:
      case   GEN2_txX_eq_pre:
      case   GEN2_txX_eq_main:
      case   GEN2_txX_eq_post:
      case   GEN2_rxX_eq_ctle_pole:
      case   GEN2_rxX_eq_ctle_boost:
      case   GEN3_txX_eq_pre:
      case   GEN3_txX_eq_main:
      case   GEN3_txX_eq_post:
      case   GEN3_rxX_eq_ctle_pole:
      case   GEN3_rxX_eq_ctle_boost:
        // For a per-lane parameter
        if (PortPointer->EngineData.StartLane > PortPointer->EngineData.EndLane) {
          LaneCount = (PortPointer->EngineData.StartLane - PortPointer->EngineData.EndLane) + 1;
        } else {
          LaneCount = (PortPointer->EngineData.EndLane - PortPointer->EngineData.StartLane) + 1;
        }
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        break;

      default:
        ASSERT (FALSE);
        break;
    }
    PhyParam++;
  }
  if (DataSize != 0) {
    DataSize += sizeof (DXIO_ANCILLARYDATA_SUBHEAP);
  }
  return DataSize;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Function to populate the ancillary data for a PCIe/SATA engine
 *
 *
 * @param[in]  EnginePointer   Pointer to engine descriptor
 * @param[in]  PortPointer     Pointer to engine topology
 * @param[in]  AncData         Pointer to next available location in ancillary data
 */
UINT32
DxioAncDataPopulate (
  IN       DXIO_ENGINE_DESCRIPTOR  *EnginePointer,
  IN       DXIO_PORT_DESCRIPTOR    *PortPointer,
  IN       UINT8                   *AncData
  )
{
  DXIO_PHY_PARAM                *PhyParam;
  UINT32                        DataSize;
  UINT32                        Index;
  UINT32                        StartLane;
  UINT32                        EndLane;
  UINT32                        LaneCount;
  DXIO_OVRSSET_ENTRY            *AncDataEntry;
  DXIO_ANCILLARYDATA_SUBHEAP    *AncDataHeader;

  AncDataEntry = (DXIO_OVRSSET_ENTRY *) (AncData + sizeof (DXIO_ANCILLARYDATA_SUBHEAP));
  PhyParam = &PortPointer->Phy.PhyParam[0];

  DataSize = 0;
  StartLane = EnginePointer->StartLane;
  EndLane = EnginePointer->EndLane;
  if (StartLane > EndLane) {
    //Handle the port reversal case
    StartLane = EnginePointer->EndLane;
    EndLane = EnginePointer->StartLane;
  }
  LaneCount = (EndLane - StartLane) + 1;
  while (PhyParam->ParamType != 0) {
    switch (PhyParam->ParamType) {
      case   SSC_OFF_FRUG1:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_SSC_OFF_FRUG1;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   SSC_OFF_PHUG1:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_SSC_OFF_PHUG1;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   rx_vref_ctrl:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rx_vref_ctrl;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_txX_iboost_lvl:
      case   GEN2_txX_iboost_lvl:
      case   GEN3_txX_iboost_lvl:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_txX_iboost_lvl;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_txX_vboost_en:
      case   GEN2_txX_vboost_en:
      case   GEN3_txX_vboost_en:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_txX_vboost_en;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_rxX_eq_att_lvl:
      case   GEN2_rxX_eq_att_lvl:
      case   GEN3_rxX_eq_att_lvl:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_eq_att_lvl;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_rxX_eq_vga1_gain:
      case   GEN2_rxX_eq_vga1_gain:
      case   GEN3_rxX_eq_vga1_gain:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_eq_vga1_gain;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_rxX_eq_vga2_gain:
      case   GEN2_rxX_eq_vga2_gain:
      case   GEN3_rxX_eq_vga2_gain:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_eq_vga2_gain;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_rxX_eq_dfe_tap1:
      case   GEN2_rxX_eq_dfe_tap1:
      case   GEN3_rxX_eq_dfe_tap1:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_eq_dfe_tap1;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN1_tx_vboost_lvl:
      case   GEN2_tx_vboost_lvl:
      case   GEN3_tx_vboost_lvl:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_tx_vboost_lvl;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN3_rxX_adapt_afe_en:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_adapt_afe_en;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      case   GEN3_rxX_adapt_dfe_en:
        DataSize += sizeof (DXIO_OVRSSET_ENTRY);
        AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_adapt_dfe_en;
        AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
        AncDataEntry->laneNumber = StartLane;
        AncDataEntry->value = PhyParam->ParamValue;
        AncDataEntry++;
        break;

      // For a per-lane parameter
      case   rxX_los_threshold:
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        for (Index = StartLane; Index <= EndLane; Index++) {
          DataSize += sizeof (DXIO_OVRSSET_ENTRY);
          AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_los_threshold;
          AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
          AncDataEntry->laneNumber = Index;
          AncDataEntry->value = PhyParam->ParamValue;
          AncDataEntry++;
        }
        break;

      case   GEN1_txX_eq_pre:
      case   GEN2_txX_eq_pre:
      case   GEN3_txX_eq_pre:
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        for (Index = StartLane; Index <= EndLane; Index++) {
          AncDataEntry->overrideField = DXIO_OVRSSET_FLD_txX_eq_pre;
          AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
          AncDataEntry->laneNumber = Index;
          AncDataEntry->value = PhyParam->ParamValue;
          AncDataEntry++;
        }
        break;

      case   GEN1_txX_eq_main:
      case   GEN2_txX_eq_main:
      case   GEN3_txX_eq_main:
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        for (Index = StartLane; Index <= EndLane; Index++) {
          AncDataEntry->overrideField = DXIO_OVRSSET_FLD_txX_eq_main;
          AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
          AncDataEntry->laneNumber = Index;
          AncDataEntry->value = PhyParam->ParamValue;
          AncDataEntry++;
        }
        break;

      case   GEN1_txX_eq_post:
      case   GEN2_txX_eq_post:
      case   GEN3_txX_eq_post:
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        for (Index = StartLane; Index <= EndLane; Index++) {
          AncDataEntry->overrideField = DXIO_OVRSSET_FLD_txX_eq_post;
          AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
          AncDataEntry->laneNumber = Index;
          AncDataEntry->value = PhyParam->ParamValue;
          AncDataEntry++;
        }
        break;
      case   GEN1_rxX_eq_ctle_pole:
      case   GEN2_rxX_eq_ctle_pole:
      case   GEN3_rxX_eq_ctle_pole:
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        for (Index = StartLane; Index <= EndLane; Index++) {
          AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_eq_ctle_pole;
          AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
          AncDataEntry->laneNumber = Index;
          AncDataEntry->value = PhyParam->ParamValue;
          AncDataEntry++;
        }
        break;

      case   GEN1_rxX_eq_ctle_boost:
      case   GEN2_rxX_eq_ctle_boost:
      case   GEN3_rxX_eq_ctle_boost:
        DataSize += LaneCount * sizeof (DXIO_OVRSSET_ENTRY);
        for (Index = StartLane; Index <= EndLane; Index++) {
          AncDataEntry->overrideField = DXIO_OVRSSET_FLD_rxX_eq_ctle_boost;
          AncDataEntry->fieldGen = PhyParam->ParamType >> 6;
          AncDataEntry->laneNumber = Index;
          AncDataEntry->value = PhyParam->ParamValue;
          AncDataEntry++;
        }
        break;

      default:
        ASSERT (FALSE);
        break;
    }
    PhyParam++;
  }
  if (DataSize != 0) {
    DataSize += sizeof (DXIO_ANCILLARYDATA_SUBHEAP);
    AncDataHeader = (DXIO_ANCILLARYDATA_SUBHEAP *) AncData;
    AncDataHeader->descriptorType = DXIO_ANCDATA_SUBHEAPTYPE_OVRRSET;
    AncDataHeader->version = DXIO_ANCILLARYDATA_SUBHEAP_VERSION;
    AncDataHeader->numDWORDs = DataSize >> 2;
  }
  return DataSize;
}


