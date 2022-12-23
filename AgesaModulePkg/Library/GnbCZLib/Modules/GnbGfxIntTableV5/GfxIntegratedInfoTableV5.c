/* $NoKeywords:$ */
/**
 * @file
 *
 * Integrated table info init
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 324267 $   @e \$Date: 2015-08-14 14:09:44 +0800 (Fri, 14 Aug 2015) $
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
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbFuseTable.h"
#include  "GnbPcie.h"
#include  "GnbGfx.h"
#include  "GnbSbLib.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbGfxFamServices.h"
#include  "GnbNbInitLib.h"
#include  "GfxConfigLib.h"
#include  "GfxIntegratedInfoTableV5.h"
#include  "GfxPwrPlayTableV5.h"
#include  "OptionGnb.h"
#include  "GfxLibV5.h"
#include  "GfxEnumConnectors.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBGFXINTTABLEV5_GFXINTEGRATEDINFOTABLEV5_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
extern GNB_BUILD_OPTIONS  GnbBuildOptions;

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
 * Init V5 Support for eDP to Lvds translators
 *
 *
 * @param[in]     Engine  Engine configuration info
 * @param[in,out] Buffer  Buffer pointer
 * @param[in]     Pcie    PCIe configuration info
 */
VOID
STATIC
GfxIntegrateducEDPToLVDSRxIdCallback (
  IN       PCIe_ENGINE_CONFIG    *Engine,
  IN OUT   VOID                  *Buffer,
  IN       PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  UINT8    *uceDPToLVDSRxId;
  uceDPToLVDSRxId = (UINT8*) Buffer;
  // APU output DP signal to a 3rd party DP translator chip (Analogix, Parade etc),
  // the chip is handled by the 3rd party DP Rx firmware and it does not require the AMD SW to have a special
  // initialize/enable/disable sequence to control this chip, the AMD SW just follows the eDP spec
  // to enable the LVDS panel through this chip.

  if (Engine->Type.Ddi.DdiData.ConnectorType == ConnectorTypeEDPToLvds) {
    *uceDPToLVDSRxId = eDP_TO_LVDS_COMMON_ID;
    IDS_HDT_CONSOLE (GNB_TRACE, "Found 3rd party common EDPToLvds Connector\n");
  }
  // APU output DP signal to a 3rd party DP translator chip which requires a AMD SW one time initialization
  // to the chip based on the LVDS panel parameters ( such as power sequence time and panel SS parameter etc ).
  // After that, the AMD SW does not need any specific enable/disable sequences to control this chip and just
  // follows the eDP spec. to control the panel.
  if (Engine->Type.Ddi.DdiData.ConnectorType == ConnectorTypeEDPToLvdsSwInit) {
    *uceDPToLVDSRxId = eDP_TO_LVDS_SWINIT_ID;
    IDS_HDT_CONSOLE (GNB_TRACE, "Found EDPToLvds Connector requiring SW init\n");
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Calculate V5 NCLK clock
 *
 *
 *
 * @param[in] NbFid         NbFid
 * @param[in] NbDid         NbDid
 * @retval                  Clock in 10KHz
 */

UINT32
STATIC
GfxLibGetNclkV5 (
  IN      UINT8                   NbFid,
  IN      UINT8                   NbDid
  )
{
  UINT32  Divider;
  //i.e. NBCOF[0] = (100 * ([NbFid] + 4h) / (2^[NbDid])) Mhz
  if (NbDid == 1) {
    Divider = 2;
  } else if (NbDid == 0) {
    Divider = 1;
  } else {
    Divider = 1;
  }
  ASSERT (NbDid == 0 || NbDid == 1);
  return ((10000 * (NbFid + 4)) / Divider);
}

/*----------------------------------------------------------------------------------------*/
/**
 *Init V5 Nb p-State MemclkFreq
 *
 *
 * @param[in] IntegratedInfoTable Integrated info table pointer
 * @param[in] PpFuseArray         PP_FUSE_ARRAY_V2 pointer
 * @param[in] Gfx                 Gfx configuration info
 */

VOID
STATIC
GfxFillNbPstateMemclkFreqV5 (
  IN OUT   ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *IntegratedInfoTable,
  IN       PP_FUSE_ARRAY_V2                 *PpFuseArray,
  IN       GFX_PLATFORM_CONFIG              *Gfx
  )
{
  UINT8                           i;
  UINT8                           Channel;
  ULONG                           memps0_freq;
  ULONG                           memps1_freq;

  Channel = 0;
  if ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_ON_DCT1) != 0) {
    Channel = 1;
  } else if ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_ON_DCT2) != 0) {
    Channel = 2;
  } else if ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_ON_DCT3) != 0) {
    Channel = 3;
  }


  memps0_freq = 100 * GfxLibExtractDramFrequencyV5 ((UINT8) PpFuseArray->MemClkFreq[Channel], GnbLibGetHeader (Gfx));
  memps1_freq = 100 * GfxLibExtractDramFrequencyV5 ((UINT8) PpFuseArray->M1MemClkFreq[Channel], GnbLibGetHeader (Gfx));

  for (i = 0; i < 2; i++) {
    if (PpFuseArray->NbPstateEn[i] == 1) {
      IntegratedInfoTable->ulNbpStateMemclkFreq[i] = (PpFuseArray->MemPstate[i] == 0) ? memps0_freq : memps1_freq;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 *Init V5 NbPstateVid
 *
 *
 * @param[in] PpFuseArray         Fuse array pointer
 * @param[in] IntegratedInfoTable Integrated info table pointer
 * @param[in] Gfx                 Gfx configuration info
 */

VOID
STATIC
GfxFillNbPStateVidV5 (
  IN       PP_FUSE_ARRAY_V2                 *PpFuseArray,
  IN OUT   ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *IntegratedInfoTable,
  IN       GFX_PLATFORM_CONFIG              *Gfx
  )
{
  UINT8                   i;

  for (i = 0; i < 4; i++) {
    IntegratedInfoTable->usNBPStateVoltage[i] = (USHORT) ((PpFuseArray->NbVid_7[i] << 7) | (PpFuseArray->NbVid_6_0[i]));
    IntegratedInfoTable->ulNbpStateNClkFreq[i] = GfxLibGetNclkV5 ((UINT8) (PpFuseArray->NbFid[i]), (UINT8) (PpFuseArray->NbDid[i]));
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Copy memory content to FB
 *
 *
 * @param[in] SystemInfoTableV5Ptr    Pointer to integrated info table
 * @param[in] Gfx                     Pointer to global GFX configuration
 *
 */
VOID
GfxIntInfoTablePostToFbV5 (
  IN       ATOM_FUSION_SYSTEM_INFO_V5     *SystemInfoTableV5Ptr,
  IN       GFX_PLATFORM_CONFIG            *Gfx
  )
{
  UINT32      Index;
  UINT32      TableOffset;
  UINT32      FbAddress;
  TableOffset = (UINT32) (Gfx->UmaInfo.UmaSize - sizeof (ATOM_FUSION_SYSTEM_INFO_V5)) | 0x80000000;
  for (Index = 0; Index < sizeof (ATOM_FUSION_SYSTEM_INFO_V5); Index = Index + 4 ) {
    FbAddress = TableOffset + Index;
    GnbLibMemWrite (Gfx->GmmBase + GMMx00_ADDRESS, AccessWidth32, &FbAddress, GnbLibGetHeader (Gfx));
    GnbLibMemWrite (Gfx->GmmBase + GMMx04_ADDRESS, AccessWidth32, (UINT8*) SystemInfoTableV5Ptr + Index, GnbLibGetHeader (Gfx));
  }
}


/*----------------------------------------------------------------------------------------*/
/**
 *Init Dispclk <-> VID table
 *
 *
 * @param[in] PpFuseArray         Fuse array pointer
 * @param[in] IntegratedInfoTable Integrated info table pointer
 * @param[in] Gfx                 Gfx configuration info
 */

VOID
STATIC
GfxIntInfoTableInitDispclkTableV5 (
  IN       PP_FUSE_ARRAY_V2                 *PpFuseArray,
  IN       ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *IntegratedInfoTable,
  IN       GFX_PLATFORM_CONFIG              *Gfx
  )
{
  UINTN   Index;
  for (Index = 0; Index < 4; Index++) {
    if (PpFuseArray->DispClkDid[Index] != 0) {
      IntegratedInfoTable->sDISPCLK_Voltage[Index].ulMaximumSupportedCLK = GfxFmCalculateClock (
                                                                             PpFuseArray->DispClkDid[Index],
                                                                             GnbLibGetHeader (Gfx)
                                                                             );
      IntegratedInfoTable->sDISPCLK_Voltage[Index].ulVoltageIndex = (ULONG) Index;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 *Init Dispclk <-> VID table
 *
 *
 * @param[in] PpFuseArray         Fuse array pointer
 * @param[in] IntegratedInfoTable Integrated info table pointer
 * @param[in] Gfx                 Gfx configuration info
 */

VOID
STATIC
GfxIntInfoTableInitDispclkV2TableV5 (
  IN       PP_FUSE_ARRAY_V2                 *PpFuseArray,
  IN       ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *IntegratedInfoTable,
  IN       GFX_PLATFORM_CONFIG              *Gfx
  )
{
  UINTN   Index;
  for (Index = 0; Index < 8; Index++) {
    if (PpFuseArray->DispClkDid[Index] != 0) {
      IntegratedInfoTable->sDispClkVoltageMapping[Index].ulMaximumSupportedCLK = GfxFmCalculateClock (
                                                                             PpFuseArray->DispClkDid[Index],
                                                                             GnbLibGetHeader (Gfx)
                                                                             );
      IntegratedInfoTable->sDispClkVoltageMapping[Index].usVoltageLevel = (USHORT) (GnbTranslateVidCodeToMillivolt (PpFuseArray->VddNbVid[Index], GnbLibGetHeader (Gfx)) / 100);
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 *Init Sclk <-> VID table
 *
 *
 * @param[in] PpFuseArray         Fuse array pointer
 * @param[in] IntegratedInfoTable Integrated info table pointer
 * @param[in] Gfx                 Gfx configuration info
 */

VOID
STATIC
GfxIntInfoTableInitSclkTableV5 (
  IN       PP_FUSE_ARRAY_V2                 *PpFuseArray,
  IN       ATOM_INTEGRATED_SYSTEM_INFO_V1_9 *IntegratedInfoTable,
  IN       GFX_PLATFORM_CONFIG              *Gfx
  )
{
  UINT8                       Index;
  UINTN                       AvailSclkIndex;
  ATOM_AVAILABLE_SCLK_LIST    *AvailSclkList;
  BOOLEAN                     Sorting;
  AvailSclkList = &IntegratedInfoTable->sAvail_SCLK[0];

  AvailSclkIndex = 0;
  for (Index = 0; Index < MAX_NUM_OF_FUSED_DPM_STATES; Index++) {
    if (PpFuseArray->SclkDid[Index] != 0) {
      AvailSclkList[AvailSclkIndex].ulSupportedSCLK = GfxFmCalculateClock (PpFuseArray->SclkDid[Index], GnbLibGetHeader (Gfx));
      AvailSclkList[AvailSclkIndex].usVoltageIndex = Index;
      AvailSclkList[AvailSclkIndex].usVoltageID = PpFuseArray->VddNbVid[Index];
      AvailSclkIndex++;
    }
  }
  //Sort by VoltageIndex & ulSupportedSCLK
  if (AvailSclkIndex > 1) {
    do {
      Sorting = FALSE;
      for (Index = 0; Index < (AvailSclkIndex - 1); Index++) {
        ATOM_AVAILABLE_SCLK_LIST  Temp;
        BOOLEAN                   Exchange;
        Exchange = FALSE;
        if (AvailSclkList[Index].usVoltageIndex > AvailSclkList[Index + 1].usVoltageIndex) {
          Exchange = TRUE;
        }
        if ((AvailSclkList[Index].usVoltageIndex == AvailSclkList[Index + 1].usVoltageIndex) &&
            (AvailSclkList[Index].ulSupportedSCLK > AvailSclkList[Index + 1].ulSupportedSCLK)) {
          Exchange = TRUE;
        }
        if (Exchange) {
          Sorting = TRUE;
          LibAmdMemCopy (&Temp, &AvailSclkList[Index], sizeof (ATOM_AVAILABLE_SCLK_LIST), GnbLibGetHeader (Gfx));
          LibAmdMemCopy (&AvailSclkList[Index], &AvailSclkList[Index + 1], sizeof (ATOM_AVAILABLE_SCLK_LIST), GnbLibGetHeader (Gfx));
          LibAmdMemCopy (&AvailSclkList[Index + 1], &Temp, sizeof (ATOM_AVAILABLE_SCLK_LIST), GnbLibGetHeader (Gfx));
        }
      }
    } while (Sorting);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build integrated info table
 *
 *
 *
 * @param[in] Gfx                 Gfx configuration info
 * @param[in] SystemInfoTableV5   ATOM_FUSION_SYSTEM_INFO_V5 pointer
 * @param[in] PpFuseArray         PP_FUSE_ARRAY pointer
 * @retval    AGESA_STATUS
 */
AGESA_STATUS
GfxIntInfoTableInitV5 (
  IN      GFX_PLATFORM_CONFIG         *Gfx,
  IN      ATOM_FUSION_SYSTEM_INFO_V5  *SystemInfoTableV5,
  IN      PP_FUSE_ARRAY_V2             *PpFuseArray
  )
{
  AGESA_STATUS                    Status;
  AGESA_STATUS                    AgesaStatus;
  PCIe_PLATFORM_CONFIG            *Pcie;
  UINT8                           Channel;
  UINT8                           Index;

  AgesaStatus = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxIntegratedInfoTableInitV5 Enter\n");

  if (PpFuseArray != NULL) {

    Channel = 0;
    if ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_ON_DCT1) != 0) {
      Channel = 1;
    } else if ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_ON_DCT2) != 0) {
      Channel = 2;
    } else if ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_ON_DCT3) != 0) {
      Channel = 3;
    }
    SystemInfoTableV5->sIntegratedSysInfo.sHeader.usStructureSize = sizeof (ATOM_INTEGRATED_SYSTEM_INFO_V1_9);
    ASSERT (SystemInfoTableV5->sIntegratedSysInfo.sHeader.usStructureSize == 512);
    SystemInfoTableV5->sIntegratedSysInfo.sHeader.ucTableFormatRevision = 1;
    SystemInfoTableV5->sIntegratedSysInfo.sHeader.ucTableContentRevision = 9;
    SystemInfoTableV5->sIntegratedSysInfo.ulBootUpEngineClock = 200 * 100;    //Set default engine clock to 200MhZ
    SystemInfoTableV5->sIntegratedSysInfo.ulDentistVCOFreq = (PpFuseArray->MainPllOpFreqIdStartup + 0x10) * 10000;
    SystemInfoTableV5->sIntegratedSysInfo.ulBootUpUMAClock = Gfx->UmaInfo.MemClock * 100;

    SystemInfoTableV5->sIntegratedSysInfo.ulBootUpReqDisplayVector = (UINT32) Gfx->BootUpDisplayDevice;
    SystemInfoTableV5->sIntegratedSysInfo.usRequestedPWMFreqInHz = Gfx->LcdBackLightControl;
//    SystemInfoTableV5->sIntegratedSysInfo.ucUMAChannelNumber = ((Gfx->UmaInfo.UmaAttributes & UMA_ATTRIBUTE_INTERLEAVE) == 0) ? 1 : 2;
//    SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType = Gfx->UmaInfo.MemType;
    // Dram technology type
    switch (Gfx->UmaInfo.MemType) {
    case DDR2_TECHNOLOGY:
      SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType = 2;  // DDR2
      break;
    case DDR3_TECHNOLOGY:
      SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType = 3;  // DDR3
      break;
    case GDDR5_TECHNOLOGY:
      SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType = 5;  // DDR5
      break;
    case DDR4_TECHNOLOGY:
      SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType = 4;  // DDR4
      break;
    case UNSUPPORTED_TECHNOLOGY:
      SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType = 0;
      break;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "IntegratedSysInfo.ucMemoryType : %d\n", SystemInfoTableV5->sIntegratedSysInfo.ucMemoryType);

    SystemInfoTableV5->sIntegratedSysInfo.usBootUpNBVoltage = GnbLocateHighestVidIndex (GnbLibGetHeader (Gfx));
    SystemInfoTableV5->sIntegratedSysInfo.usPanelRefreshRateRange = Gfx->DynamicRefreshRate;
    SystemInfoTableV5->sIntegratedSysInfo.usLvdsSSPercentage = Gfx->LvdsSpreadSpectrum;
    //Locate PCIe configuration data to get definitions of display connectors
    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.sHeader.usStructureSize = sizeof (ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO);
    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.sHeader.ucTableFormatRevision = 1;
    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.sHeader.ucTableContentRevision = 1;
    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.uc3DStereoPinId = Gfx->Gnb3dStereoPinIndex;
    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.ucRemoteDisplayConfig = Gfx->GnbRemoteDisplaySupport;
    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.ucFixDPVoltageSwing = (UINT8) Gfx->DpFixedVoltSwingType;
    SystemInfoTableV5->sIntegratedSysInfo.usExtDispConnInfoOffset = offsetof (ATOM_INTEGRATED_SYSTEM_INFO_V1_9, sExtDispConnInfo);

    SystemInfoTableV5->sIntegratedSysInfo.ucEDPv1_4VSMode = (UINT8) Gfx->EDPv1_4VSMode;
    SystemInfoTableV5->sIntegratedSysInfo.ucReDrvSlvAddr.ucExtHDMIReDrvSlvAddr = (UINT8) Gfx->ExtHDMIReDrvSlvAddr;
    SystemInfoTableV5->sIntegratedSysInfo.UcReDrvRegNum.ucExtHDMIReDrvRegNum = (UINT8) Gfx->ExtHDMIReDrvRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->ExtHDMIRegSetting != NULL) {
      IDS_HDT_CONSOLE (GNB_TRACE, "HDMI retimer/redriver\n address = %x\n", Gfx->ExtHDMIReDrvSlvAddr);
      IDS_HDT_CONSOLE (GNB_TRACE, " RegNumber = %d\n", Gfx->ExtHDMIReDrvRegNum);
      if (Gfx->ExtHDMIReDrvRegNum > 0) {
        for (Index = 0; Index < Gfx->ExtHDMIReDrvRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asReDrvRegSetting.asExtHDMIRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->ExtHDMIRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asReDrvRegSetting.asExtHDMIRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->ExtHDMIRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->ExtHDMIRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->ExtHDMIRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.ucDP0_ExtHdmiSlvAddr = (UINT8) Gfx->DP0ExtHDMIReDrvSlvAddr;
    SystemInfoTableV5->sIntegratedSysInfo.ucDP0_ExtHdmiRegNum = (UINT8) Gfx->DP0ExtHDMIReDrvRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMIRegSetting != NULL) {
      SystemInfoTableV5->sIntegratedSysInfo.ulGPUCapInfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
      IDS_HDT_CONSOLE (GNB_TRACE, "DP0 retimer/redriver\n address = %x\n", Gfx->DP0ExtHDMIReDrvSlvAddr);
      IDS_HDT_CONSOLE (GNB_TRACE, " RegNumber = %d\n", Gfx->DP0ExtHDMIReDrvRegNum);
      if (Gfx->DP0ExtHDMIReDrvRegNum > 0) {
        for (Index = 0; Index < Gfx->DP0ExtHDMIReDrvRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asDP0_ExtHdmiRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMIRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asDP0_ExtHdmiRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMIRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMIRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMIRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.ucDP1_ExtHdmiSlvAddr = (UINT8) Gfx->DP1ExtHDMIReDrvSlvAddr;
    SystemInfoTableV5->sIntegratedSysInfo.ucDP1_ExtHdmiRegNum = (UINT8) Gfx->DP1ExtHDMIReDrvRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMIRegSetting != NULL) {
      SystemInfoTableV5->sIntegratedSysInfo.ulGPUCapInfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
      IDS_HDT_CONSOLE (GNB_TRACE, "DP1 retimer/redriver\n address = %x\n", Gfx->DP1ExtHDMIReDrvSlvAddr);
      IDS_HDT_CONSOLE (GNB_TRACE, " RegNumber = %d\n", Gfx->DP1ExtHDMIReDrvRegNum);
      if (Gfx->DP1ExtHDMIReDrvRegNum > 0) {
        for (Index = 0; Index < Gfx->DP1ExtHDMIReDrvRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asDP1_ExtHdmiRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMIRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asDP1_ExtHdmiRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMIRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMIRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMIRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.ucReDrvSlvAddr.ucDP2_ExtHdmiSlvAddr = (UINT8) Gfx->DP2ExtHDMIReDrvSlvAddr;
    SystemInfoTableV5->sIntegratedSysInfo.UcReDrvRegNum.ucDP2_ExtHdmiRegNum = (UINT8) Gfx->DP2ExtHDMIReDrvRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMIRegSetting != NULL) {
      SystemInfoTableV5->sIntegratedSysInfo.ulGPUCapInfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
      IDS_HDT_CONSOLE (GNB_TRACE, "DP2 retimer/redriver\n address = %x\n", Gfx->DP2ExtHDMIReDrvSlvAddr);
      IDS_HDT_CONSOLE (GNB_TRACE, " RegNumber = %d\n", Gfx->DP2ExtHDMIReDrvRegNum);
      if (Gfx->DP2ExtHDMIReDrvRegNum > 0) {
        for (Index = 0; Index < Gfx->DP2ExtHDMIReDrvRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asReDrvRegSetting.asDP2_ExtHdmiRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMIRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asReDrvRegSetting.asDP2_ExtHdmiRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMIRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMIRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMIRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.ucDP0_ExtHDMI6GRegNum = (UINT8) Gfx->DP0ExtHDMI6GRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMI6GhzRegSetting != NULL) {
      IDS_HDT_CONSOLE (GNB_TRACE, "6GHz RegNumber = %d\n", Gfx->DP0ExtHDMI6GRegNum);
      if (Gfx->DP0ExtHDMI6GRegNum > 0) {
        for (Index = 0; Index < Gfx->DP0ExtHDMI6GRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asDP0_ExtHdmi6GhzRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMI6GhzRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asDP0_ExtHdmi6GhzRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMI6GhzRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMI6GhzRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP0ExtHDMI6GhzRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.ucDP1_ExtHDMI6GRegNum = (UINT8) Gfx->DP1ExtHDMI6GRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMI6GhzRegSetting != NULL) {
      IDS_HDT_CONSOLE (GNB_TRACE, "6GHz RegNumber = %d\n", Gfx->DP1ExtHDMI6GRegNum);
      if (Gfx->DP1ExtHDMI6GRegNum > 0) {
        for (Index = 0; Index < Gfx->DP1ExtHDMI6GRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asDP1_ExtHdmi6GhzRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMI6GhzRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asDP1_ExtHdmi6GhzRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMI6GhzRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMI6GhzRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP1ExtHDMI6GhzRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.ucDP2_ExtHDMI6GRegNum = (UINT8) Gfx->DP2ExtHDMI6GRegNum;
    if ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMI6GhzRegSetting != NULL) {
      IDS_HDT_CONSOLE (GNB_TRACE, "6GHz RegNumber = %d\n", Gfx->DP2ExtHDMI6GRegNum);
      if (Gfx->DP2ExtHDMI6GRegNum > 0) {
        for (Index = 0; Index < Gfx->DP2ExtHDMI6GRegNum; Index++) {
          SystemInfoTableV5->sIntegratedSysInfo.asDP2_ExtHdmi6GhzRegSetting[Index].ucI2cRegIndex = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMI6GhzRegSetting)[Index].RegIndex;
          SystemInfoTableV5->sIntegratedSysInfo.asDP2_ExtHdmi6GhzRegSetting[Index].ucI2cRegVal = (UINT8) ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMI6GhzRegSetting)[Index].RegVal;
          IDS_HDT_CONSOLE (GNB_TRACE, " ucI2cRegIndex = %x\n  ucI2cRegVal = %x\n", ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMI6GhzRegSetting)[Index].RegIndex, ((HDMI_RE_DRIVER_I2C_REG_INFO *)Gfx->DP2ExtHDMI6GhzRegSetting)[Index].RegVal);
        }
      }
    }

    SystemInfoTableV5->sIntegratedSysInfo.usPCIEClkSSPercentage = Gfx->PcieRefClkSpreadSpectrum;
    IDS_HDT_CONSOLE (GNB_TRACE, "PcieRefClkSpreadSpectrum : %d\n", Gfx->PcieRefClkSpreadSpectrum);
    SystemInfoTableV5->sIntegratedSysInfo.ucLvdsMisc = Gfx->LvdsMiscControl.Value;
    IDS_HDT_CONSOLE (GNB_TRACE, "Lvds Misc control : %x\n", Gfx->LvdsMiscControl.Value);
    if (Gfx->LvdsMiscControl.Field.LvdsVoltOverwriteEn) {
      SystemInfoTableV5->sIntegratedSysInfo.ucLVDSVoltAdjust = Gfx->LVDSVoltAdjust;
      IDS_HDT_CONSOLE (GNB_TRACE, "LVDSVoltAdjust : %x\n", Gfx->LVDSVoltAdjust);
    }

    SystemInfoTableV5->sIntegratedSysInfo.ulVBIOSMisc = Gfx->DisplayMiscControl.Value;
    IDS_HDT_CONSOLE (GNB_TRACE, "Display Misc control : %x\n", Gfx->DisplayMiscControl.Value);

    // LVDS
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSPwrOnSeqDIGONtoDE_in4Ms = Gfx->LvdsPowerOnSeqDigonToDe;
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSPwrOnSeqDEtoVARY_BL_in4Ms = Gfx->LvdsPowerOnSeqDeToVaryBl;
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSPwrOffSeqVARY_BLtoDE_in4Ms = Gfx->LvdsPowerOnSeqVaryBlToDe;
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSPwrOffSeqDEtoDIGON_in4Ms = Gfx->LvdsPowerOnSeqDeToDigon;
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSOffToOnDelay_in4Ms = Gfx->LvdsPowerOnSeqOnToOffDelay;
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms = Gfx->LvdsPowerOnSeqVaryBlToBlon;
    SystemInfoTableV5->sIntegratedSysInfo.ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms = Gfx->LvdsPowerOnSeqBlonToVaryBl;
    SystemInfoTableV5->sIntegratedSysInfo.ulLCDBitDepthControlVal = Gfx->LcdBitDepthControlValue;
    SystemInfoTableV5->sIntegratedSysInfo.usMaxLVDSPclkFreqInSingleLink = Gfx->LvdsMaxPixelClockFreq;
    SystemInfoTableV5->sIntegratedSysInfo.ucMinAllowedBL_Level = Gfx->MinAllowedBLLevel;
    Status = PcieLocateConfigurationData (GnbLibGetHeader (Gfx), &Pcie);
    ASSERT (Status == AGESA_SUCCESS);
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
    if (Status == AGESA_SUCCESS) {
      Status = GfxIntegratedEnumerateAllConnectors (
                 &SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.sPath[0],
                 Pcie,
                 Gfx
                 );
      AGESA_STATUS_UPDATE (Status, AgesaStatus);
    }

    SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.uceDPToLVDSRxId = eDP_TO_LVDS_RX_DISABLE;
    PcieConfigRunProcForAllEngines (
      DESCRIPTOR_ALLOCATED | DESCRIPTOR_VIRTUAL | DESCRIPTOR_DDI_ENGINE,
      GfxIntegrateducEDPToLVDSRxIdCallback,
      &SystemInfoTableV5->sIntegratedSysInfo.sExtDispConnInfo.uceDPToLVDSRxId,
      Pcie
      );

    // Build info from fuses
    // Build Display clock info
    GfxIntInfoTableInitDispclkV2TableV5 (PpFuseArray, &SystemInfoTableV5->sIntegratedSysInfo, Gfx);
    // Build Sclk info table - no longer used
    //GfxIntInfoTableInitSclkTableV5 (PpFuseArray, &SystemInfoTableV5->sIntegratedSysInfo, Gfx);
    // Fill in Nb P-state MemclkFreq Data
    GfxFillNbPstateMemclkFreqV5 (&SystemInfoTableV5->sIntegratedSysInfo, PpFuseArray, Gfx);
    // Fill in HTC Data
    if (PpFuseArray->HtcEn == 1) {
      SystemInfoTableV5->sIntegratedSysInfo.ucHtcTmpLmt = (UCHAR) (PpFuseArray->HtcTmpLmt / 2 + 52);
      SystemInfoTableV5->sIntegratedSysInfo.ucHtcHystLmt = (UCHAR) (PpFuseArray->HtcHystLmt / 2);
    } else {
      SystemInfoTableV5->sIntegratedSysInfo.ucHtcTmpLmt = 0;
      SystemInfoTableV5->sIntegratedSysInfo.ucHtcHystLmt = 0;
    }
    // Fill in NB P states VID & NCLK info
    GfxFillNbPStateVidV5 (PpFuseArray, &SystemInfoTableV5->sIntegratedSysInfo, Gfx);

    // Family specific data update - store default values to be updated by family specific code
    //GfxFmIntegratedInfoTableInit (&SystemInfoV1Table.sIntegratedSysInfo, Gfx);
    SystemInfoTableV5->sIntegratedSysInfo.ulDDR_DLL_PowerUpTime = 4940;
    SystemInfoTableV5->sIntegratedSysInfo.ulDDR_PLL_PowerUpTime = 2000;

    if (PpFuseArray->MemPhyPllPdMode[Channel] != 0) {
      SystemInfoTableV5->sIntegratedSysInfo.ulSystemConfig |= BIT2;
    }
    if (PpFuseArray->DisDllShutdownSR[Channel] == 0) {
      SystemInfoTableV5->sIntegratedSysInfo.ulSystemConfig |= BIT1;
    }
    if (GnbBuildOptions.CfgPciePowerGatingFlags != (PCIE_POWERGATING_SKIP_CORE | PCIE_POWERGATING_SKIP_PHY)) {
      SystemInfoTableV5->sIntegratedSysInfo.ulSystemConfig |= BIT0;
    }
    SystemInfoTableV5->sIntegratedSysInfo.ulGPUCapInfo = GPUCAPINFO_TMDS_HDMI_USE_CASCADE_PLL_MODE | GPUCAPINFO_DP_USE_SINGLE_PLL_MODE;

    IDS_HDT_CONSOLE (GNB_TRACE, "ulSystemConfig : %x\n", SystemInfoTableV5->sIntegratedSysInfo.ulSystemConfig);

  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "  ERROR! Cannot locate fuse table\n");
    Status = AGESA_ERROR;
    AGESA_STATUS_UPDATE (Status, AgesaStatus);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxIntegratedInfoTableInitV5 Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump gfx integrated info table
 *
 *
 * @param[in] SystemInfoTableV5Ptr    Pointer to integrated info table
 * @param[in] Gfx                     Pointer to global GFX configuration
 *
 */
VOID
GfxIntInfoTableDebugDumpV5 (
  IN       ATOM_FUSION_SYSTEM_INFO_V5     *SystemInfoTableV5Ptr,
  IN       GFX_PLATFORM_CONFIG            *Gfx
  )
{
  ATOM_PPLIB_POWERPLAYTABLE5      *PpTable;
  ATOM_PPLIB_EXTENDEDHEADER       *ExtendedHeader;

  IDS_HDT_CONSOLE (GFX_MISC, "GfxIntInfoTableDebugDumpV5 Enter\n");

  PpTable = (ATOM_PPLIB_POWERPLAYTABLE5*) &SystemInfoTableV5Ptr->ulPowerplayTable;
  ExtendedHeader = (ATOM_PPLIB_EXTENDEDHEADER *) ((UINT8 *) (PpTable) + PpTable->usExtendendedHeaderOffset);
  IDS_HDT_CONSOLE (GFX_MISC, "    ExtendedHeader  usSize %d\n", ExtendedHeader->usSize);
  IDS_HDT_CONSOLE (GFX_MISC, "                    SizeOf %d\n", sizeof(ATOM_PPLIB_EXTENDEDHEADER));

  IDS_HDT_CONSOLE (GFX_MISC, "    ucHtcTmpLmt  0x%X\n", SystemInfoTableV5Ptr->sIntegratedSysInfo.ucHtcTmpLmt);
  IDS_HDT_CONSOLE (GFX_MISC, "    ucHtcHystLmt 0x%X\n", SystemInfoTableV5Ptr->sIntegratedSysInfo.ucHtcHystLmt);
  IDS_HDT_CONSOLE (GFX_MISC, "GfxIntInfoTableDebugDumpV5 Exit\n");
}


