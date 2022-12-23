/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB env post initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 327174 $   @e \$Date: 2015-09-16 15:19:01 +0800 (Wed, 16 Sep 2015) $
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
#include  "GnbCommonLib.h"
#include  "GnbTable.h"
#include  "GnbPcieConfig.h"
#include  "GnbNbInitLib.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GnbFuseTableCZ.h"
#include  "PcieComplexDataCZ.h"
#include  "PcieLibCZ.h"
#include  "OptionGnb.h"
#include  "Library/AmdHeapLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GNBENVINITCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
//extern GNB_BUILD_OPTIONS_CZ   GnbBuildOptionsCZ;
extern GNB_TABLE ROMDATA      GnbEnvInitTableCZ [];
extern GNB_TABLE ROMDATA      GnbIommuEnvInitTableCZ [];
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

AGESA_STATUS
GnbEnvInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Registers need to be set if no GFX PCIe ports are used
 *
 *
 *
 * @param[in]  Pcie                Pointer to PCIe_PLATFORM_CONFIG
 * @retval     BOOLEAN
 */

BOOLEAN
STATIC
GnbIommuEnvInitCheckGfxPciePorts (
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  PCIe_WRAPPER_CONFIG   *WrapperList;
  BOOLEAN               GfxPciePortUsed;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitCheckGfxPciePorts Enter\n");
  GfxPciePortUsed = FALSE;

  WrapperList = PcieConfigGetChildWrapper (Pcie);
  ASSERT (WrapperList != NULL);
  if (WrapperList->WrapId == GFX_WRAP_ID) {
    PCIe_ENGINE_CONFIG   *EngineList;
    EngineList = PcieConfigGetChildEngine (WrapperList);
    while (EngineList != NULL) {
      if (PcieConfigIsPcieEngine (EngineList)) {
        IDS_HDT_CONSOLE (GNB_TRACE, "Checking Gfx ports device number %x\n", EngineList->Type.Port.NativeDevNumber);
        if (PcieConfigCheckPortStatus (EngineList, INIT_STATUS_PCIE_TRAINING_SUCCESS) ||
           ((EngineList->Type.Port.PortData.LinkHotplug != HotplugDisabled) && (EngineList->Type.Port.PortData.LinkHotplug != HotplugInboard))) {
          // GFX PCIe ports are being used
          GfxPciePortUsed = TRUE;
          IDS_HDT_CONSOLE (GNB_TRACE, "GFX PCIe ports are being used\n");
          break;
        }
      }
      EngineList = PcieLibGetNextDescriptor (EngineList);
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuMidInitCheckGfxPciePorts Exit\n");
  return GfxPciePortUsed;
}

/*----------------------------------------------------------------------------------------*/
/**
 * IOMMU Memory power gating
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
STATIC
GnbIommuEnvMemoryPowerGating (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS              Status;
  GNB_HANDLE                *GnbHandle;
  GNB_BUILD_OPTIONS_CZ      *GnbBuildOptionData;
  D0F2xFC_x3A_L1_STRUCT     D0F2xFC_x3A_L1;
  D0F2xFC_x3B_L1_STRUCT     D0F2xFC_x3B_L1;
  D0F2xFC_x3C_L1_STRUCT     D0F2xFC_x3C_L1;
  D0F2xFC_x39_L1_STRUCT     D0F2xFC_x39_L1;
  UINT8                     i;
  D0F2xF4_x3B_STRUCT        D0F2xF4_x3B;
  D0F2xF4_x3C_STRUCT        D0F2xF4_x3C;
  D0F2xF4_x3D_STRUCT        D0F2xF4_x3D;
  D0F2xF4_x35_STRUCT        D0F2xF4_x35;
  D0F2xF4_x36_STRUCT        D0F2xF4_x36;
  D0F2xF4_x37_STRUCT        D0F2xF4_x37;
  D0F2xF4_x95_STRUCT        D0F2xF4_x95;
  D0F2xF4_x96_STRUCT        D0F2xF4_x96;
  D0F2xF4_x97_STRUCT        D0F2xF4_x97;


  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuEnvMemoryPowerGating Enter\n");
  Status = AGESA_SUCCESS;

  GnbHandle = GnbGetHandle (StdHeader);

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  if (GnbBuildOptionData->CfgIommuL2MemPowerGating) {
    //Disable PGFSM Memory Power Gating in IOMMU L2
    D0F2xF4_x3B.Value = 0x100020FF;
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x3B_TYPE, D0F2xF4_x3B_ADDRESS, &D0F2xF4_x3B.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);

    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x3D_TYPE, D0F2xF4_x3D_ADDRESS, &D0F2xF4_x3D.Value, 0, StdHeader);
    D0F2xF4_x3C.Value = (D0F2xF4_x3D.Field.ReadValue | 0x00080000);
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x3C_TYPE, D0F2xF4_x3C_ADDRESS, &D0F2xF4_x3C.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);

    D0F2xF4_x3B.Value = 0x100010FF;
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x3B_TYPE, D0F2xF4_x3B_ADDRESS, &D0F2xF4_x3B.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);

    //Enabling PGMEM Memory Power Gating in IOMMU L2
    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x36_TYPE, D0F2xF4_x36_ADDRESS, &D0F2xF4_x36.Value, 0, StdHeader);
    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x37_TYPE, D0F2xF4_x37_ADDRESS, &D0F2xF4_x37.Value, 0, StdHeader);
    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x96_TYPE, D0F2xF4_x96_ADDRESS, &D0F2xF4_x96.Value, 0, StdHeader);
    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x97_TYPE, D0F2xF4_x97_ADDRESS, &D0F2xF4_x97.Value, 0, StdHeader);
    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x35_TYPE, D0F2xF4_x35_ADDRESS, &D0F2xF4_x35.Value, 0, StdHeader);
    GnbRegisterReadCZ (GnbHandle, D0F2xF4_x95_TYPE, D0F2xF4_x95_ADDRESS, &D0F2xF4_x95.Value, 0, StdHeader);

    D0F2xF4_x36.Field.L2aregLSThres = 0xC8;
    D0F2xF4_x37.Field.L2aregDSThres = 0xC8;
    D0F2xF4_x96.Field.L2bregLSThres = 0xC8;
    D0F2xF4_x97.Field.L2bregDSThres = 0xC8;
    D0F2xF4_x35.Field.L2aregLSEn = 1;
    D0F2xF4_x35.Field.L2aregDSEn = 1;
    D0F2xF4_x35.Field.L2aregSDEn = 1;
    D0F2xF4_x95.Field.L2bregLSEn = 1;
    D0F2xF4_x95.Field.L2bregDSEn = 1;
    D0F2xF4_x95.Field.L2bregSDEn = 1;

    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x36_TYPE, D0F2xF4_x36_ADDRESS, &D0F2xF4_x36.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x37_TYPE, D0F2xF4_x37_ADDRESS, &D0F2xF4_x37.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x96_TYPE, D0F2xF4_x96_ADDRESS, &D0F2xF4_x96.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x97_TYPE, D0F2xF4_x97_ADDRESS, &D0F2xF4_x97.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x35_TYPE, D0F2xF4_x35_ADDRESS, &D0F2xF4_x35.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    GnbRegisterWriteCZ (GnbHandle, D0F2xF4_x95_TYPE, D0F2xF4_x95_ADDRESS, &D0F2xF4_x95.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  }



  if (GnbBuildOptionData->CfgIommuL1MemPowerGating) {
    for (i = 0; i < 4; i++) {
      GnbRegisterReadCZ (GnbHandle, D0F2xFC_x3A_L1_TYPE, D0F2xFC_x3A_L1_ADDRESS (i), &D0F2xFC_x3A_L1.Value, 0, StdHeader);
      GnbRegisterReadCZ (GnbHandle, D0F2xFC_x3B_L1_TYPE, D0F2xFC_x3B_L1_ADDRESS (i), &D0F2xFC_x3B_L1.Value, 0, StdHeader);
      GnbRegisterReadCZ (GnbHandle, D0F2xFC_x3C_L1_TYPE, D0F2xFC_x3C_L1_ADDRESS (i), &D0F2xFC_x3C_L1.Value, 0, StdHeader);
      GnbRegisterReadCZ (GnbHandle, D0F2xFC_x39_L1_TYPE, D0F2xFC_x39_L1_ADDRESS (i), &D0F2xFC_x39_L1.Value, 0, StdHeader);

      D0F2xFC_x3A_L1.Field.LSThres = 0xC8;
      D0F2xFC_x3B_L1.Field.DSThres = 0xC8;
      D0F2xFC_x3C_L1.Field.SDThres = 0x44C;
      D0F2xFC_x39_L1.Field.LSEn = 1;
      D0F2xFC_x39_L1.Field.DSEn = 1;
      D0F2xFC_x39_L1.Field.SDEn = 1;

      GnbRegisterWriteCZ (GnbHandle, D0F2xFC_x3A_L1_TYPE, D0F2xFC_x3A_L1_ADDRESS (i), &D0F2xFC_x3A_L1.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
      GnbRegisterWriteCZ (GnbHandle, D0F2xFC_x3B_L1_TYPE, D0F2xFC_x3B_L1_ADDRESS (i), &D0F2xFC_x3B_L1.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
      GnbRegisterWriteCZ (GnbHandle, D0F2xFC_x3C_L1_TYPE, D0F2xFC_x3C_L1_ADDRESS (i), &D0F2xFC_x3C_L1.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
      GnbRegisterWriteCZ (GnbHandle, D0F2xFC_x39_L1_TYPE, D0F2xFC_x39_L1_ADDRESS (i), &D0F2xFC_x39_L1.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    }
  }



  IDS_HDT_CONSOLE (GNB_TRACE, "GnbIommuEnvMemoryPowerGating Exit [0x%x]\n", Status);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GNB init at env
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
GnbEnvInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS          Status;
  AGESA_STATUS          AgesaStatus;
  AMD_ENV_PARAMS        *EnvParamsPtr;
  UINT32                Property;
  GNB_HANDLE            *GnbHandle;
  PCI_ADDR              GnbPciAddress;
//  D18F5x170_STRUCT      D18F5x170;
  D0F0x7C_STRUCT        D0F0x7C;
  PCIe_PLATFORM_CONFIG  *Pcie;
  GNB_BUILD_OPTIONS_CZ  *GnbBuildOptionData;

  AGESA_TESTPOINT (TpGnbEnvInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEnvInterfaceCZ Enter\n");
  Property = TABLE_PROPERTY_DEFAULT;
  AgesaStatus = AGESA_SUCCESS;
  EnvParamsPtr = (AMD_ENV_PARAMS *) StdHeader;

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  GnbLoadFuseTableCZ (StdHeader);

  if (EnvParamsPtr->GnbEnvConfiguration.GpuFrequencyLimit != 0) {
    GnbOverrideGpuFreqeuencyCZ (StdHeader);
  }

  Property |= GnbBuildOptionData->GnbCommonOptions.CfgIommuL1ClockGatingEnable ? TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING : 0;
  Property |= GnbBuildOptionData->GnbCommonOptions.CfgIommuL2ClockGatingEnable ? TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING : 0;
  Property |= GnbBuildOptionData->CfgSstunlClkGating ? TABLE_PROPERTY_IOMMU_L1_SST_CLOCK_GATING : 0;
  if (!EnvParamsPtr->GnbEnvConfiguration.IommuSupport) {
    Property |= TABLE_PROPERTY_IOMMU_DISABLED;
  }

  GnbLibPciRead (MAKE_SBDFO (0, 0, 0, 0, D0F0x7C_ADDRESS), AccessWidth32, &D0F0x7C.Value, StdHeader);
  Property |= (D0F0x7C.Field.ForceIntGfxDisable != 0) ? TABLE_PROPERTY_IGFX_DISABLED : 0;

  Status = PcieLocateConfigurationData (StdHeader, &Pcie);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    Property |= GnbIommuEnvInitCheckGfxPciePorts (Pcie) ? 0 : TABLE_PROPERTY_DGFX_DISABLED;
  }
  GnbHandle = GnbGetHandle (StdHeader);
  GnbPciAddress = GnbGetHostPciAddress (GnbHandle);
  Status = GnbSetTom (GnbPciAddress, StdHeader);
  GnbOrbDynamicWake (GnbPciAddress, StdHeader);
  if (GnbIsGnbConnectedToSb (GnbHandle)) {
    GnbLpcDmaDeadlockPrevention (GnbHandle, StdHeader);
  }

  Status = GnbIommuEnvMemoryPowerGating (StdHeader);

  Status = GnbProcessTable (
             GnbHandle,
             GnbEnvInitTableCZ,
             Property,
             GNB_TABLE_FLAGS_FORCE_S3_SAVE,
             StdHeader
             );
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  Status = GnbProcessTable (
             GnbHandle,
             GnbIommuEnvInitTableCZ,
             Property,
             GNB_TABLE_FLAGS_FORCE_S3_SAVE,
             StdHeader
             );
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEnvInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpGnbEnvInterfaceCZExit, NULL);
  return  AgesaStatus;
}

