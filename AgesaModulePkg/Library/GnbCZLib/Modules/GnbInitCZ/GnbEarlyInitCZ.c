/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB early post initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 329717 $   @e \$Date: 2015-10-27 06:36:16 +0800 (Tue, 27 Oct 2015) $
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
#include  "OptionGnb.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbTable.h"
#include  "GnbSmuInitLibV8.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
// todo:_remove #include  "cpuF15PowerMgmt.h"
// todo:_remove #include  "cpuFeatures.h"
#include  "GnbPspCZ.h"
#include  "Library/AmdHeapLib.h"
// todo:_remove #include  "PspBaseLib.h"
#include  "GnbAzalialib.h"
#include <Library/FchBaseLib.h>
#include  <AmdSoc.h>

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GNBEARLYINITCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern GNB_TABLE ROMDATA    GnbEarlierInitTableBeforeSmuCZ [];
extern GNB_TABLE ROMDATA    GnbEarlyInitTableCZ [];
extern GNB_TABLE ROMDATA    GnbIommuEarlyInitTableCZ [];
extern GNB_BUILD_OPTIONS_CZ GnbBuildOptionsCZ;
extern BUILD_OPT_CFG        UserOptions;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID *
GnbGetBuildOptionsCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbEarlyInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbEarlierInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * GnbGetBuildOptionsCZ - Get GNB Build options
 *
 *
 * @param[in]       StdHeader           Standard configuration header
 */
VOID *
GnbGetBuildOptionsCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  GNB_BUILD_OPTIONS_CZ  *GnbBuildOptionData;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbGetBuildOptionsCZ Enter\n");

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  if (GnbBuildOptionData == NULL) {
    GnbBuildOptionData = &GnbBuildOptionsCZ;
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbGetBuildOptionsCZ Enter\n");
  return (VOID *)GnbBuildOptionData;
}

/**
 * GnbAzaliaEarlyInitCZ - Config Azalia controller
 *
 *
 * @param[in]       StdHeader           Standard configuration header
 *
 */
VOID
GnbAzaliaEarlyInitCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  UINT32                Value32;
  UINT32                Data32;
  GNB_HANDLE            *GnbHandle;
  AMD_EARLY_PARAMS      *EarlyParamsPtr;
  UINT32                AcpSelect;
  UINT32                AcpPinConfig;
  GMMx1474C_STRUCT      GMMx1474C;
  GMMx14750_STRUCT      GMMx14750;
  D0F0x64_x50_STRUCT    D0F0x64_x50;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbAzaliaEarlyInitCZ Enter\n");
  EarlyParamsPtr = (AMD_EARLY_PARAMS *) StdHeader;
  GnbHandle = GnbGetHandle (StdHeader);

  IDS_HDT_CONSOLE (GNB_TRACE, "AcpPowerGating = %x\n", EarlyParamsPtr->PlatformConfig.AcpPowerGating);
  if ( EarlyParamsPtr->PlatformConfig.AcpPowerGating == FALSE) {
    GnbSmuAcpPowerGatingV8 (GnbHandle, SMC_MSG_PowerUpAcp, StdHeader);
  }

  if (GnbLibPciIsDevicePresent (MAKE_SBDFO (0, 0, 9, 2, 0), StdHeader)) {
    Value32 = 0xFE9F00;
    GnbLibPciWrite (MAKE_SBDFO (0, 0, 0x18, 1, 0xB4), AccessWidth32, &Value32, StdHeader);
    Value32 = 0xFE9003;
    GnbLibPciWrite (MAKE_SBDFO (0, 0, 0x18, 1, 0xB0), AccessWidth32, &Value32, StdHeader);

    AcpSelect = EarlyParamsPtr->PlatformConfig.GnbAzI2sBusSelect;
    AcpPinConfig = EarlyParamsPtr->PlatformConfig.GnbAzI2sBusPinConfig;
    if (GnbLibPciIsDevicePresent (MAKE_SBDFO (0, 0, 1, 0, 0), StdHeader)) {
      Value32 = 0xFE900000;
      GnbLibPciWrite (MAKE_SBDFO (0, 0, 1, 0, 0x24), AccessWidth32, &Value32, StdHeader);
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 1, 0, 0x4), AccessWidth32, 0xFFFFFFF9, BIT1 | BIT2, StdHeader);
      GnbHandle->GmmBase = Value32;

      GnbRegisterReadCZ (GnbHandle, GMMx14750_TYPE, GMMx14750_ADDRESS, &GMMx14750.Value, 0, StdHeader);
      GMMx14750.Field.AZ_I2S_SELECT = AcpSelect;
      GnbRegisterWriteCZ (GnbHandle, GMMx14750_TYPE, GMMx14750_ADDRESS, &GMMx14750.Value, AccessWidth32, StdHeader);

      GnbRegisterReadCZ (GnbHandle, GMMx1474C_TYPE, GMMx1474C_ADDRESS, &GMMx1474C.Value, 0, StdHeader);
      GMMx1474C.Field.ACP_I2S_PIN_CONFIG = AcpPinConfig;
      if (AcpSelect == GnbAcpAzalia) {
        GMMx1474C.Field.ACP_I2S_PIN_CONFIG = 0;
      }
      GnbRegisterWriteCZ (GnbHandle, GMMx1474C_TYPE, GMMx1474C_ADDRESS, &GMMx1474C.Value, AccessWidth32, StdHeader);

      Value32 = 0;
      GnbHandle->GmmBase = Value32;
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 1, 0, 0x4), AccessWidth32, 0xFFFFFFF9, 0, StdHeader);
      GnbLibPciWrite (MAKE_SBDFO (0, 0, 1, 0, 0x24), AccessWidth32, &Value32, StdHeader);
    }

    Value32 = 0xFE900000;
    if (AcpSelect == GnbAcpAzalia) {
      GnbLibPciWrite (MAKE_SBDFO (0, 0, 9, 2, 0x10), AccessWidth32, &Value32, StdHeader);
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x48), AccessWidth32, 0xFFFFFFFE, BIT0, StdHeader);
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x4), AccessWidth32, 0xFFFFFFF9, BIT1 | BIT2, StdHeader);

      ConfigureVerbTable (Value32, EarlyParamsPtr->PlatformConfig.AzaliaCodecVerbTable, StdHeader);

      Value32 = 0;
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x4), AccessWidth32, 0xFFFFFFF9, 0, StdHeader);
      GnbLibPciWrite (MAKE_SBDFO (0, 0, 9, 2, 0x10), AccessWidth32, &Value32, StdHeader);
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x48), AccessWidth32, 0xFFFFFFFE, 0, StdHeader);

      Value32 = EarlyParamsPtr->PlatformConfig.AzaliaSsid;
      if (Value32 != 0) {
        GnbRegisterWriteCZ (GnbHandle, TYPE_D9F2, 0x4C, &Value32, AccessWidth32, StdHeader);
        IDS_HDT_CONSOLE (GNB_TRACE, "Gnb Azalia SSID=%x\n", Value32);
      }
    } else {
      GnbLibPciWrite (MAKE_SBDFO (0, 0, 9, 2, 0x14), AccessWidth32, &Value32, StdHeader);

      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x48), AccessWidth32, 0xFFFFFFFD, BIT1, StdHeader);
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x4), AccessWidth32, 0xFFFFFFF9, BIT1 | BIT2, StdHeader);

      GnbLibMemRead (Value32 + 0x08, AccessWidth32, &Data32, StdHeader);
      Data32 |= BIT0;
      GnbLibMemWrite (Value32 + 0x08, AccessWidth32, &Data32, StdHeader);

      Value32 = 0;
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x4), AccessWidth32, 0xFFFFFFF9, 0, StdHeader);
      GnbLibPciWrite (MAKE_SBDFO (0, 0, 9, 2, 0x14), AccessWidth32, &Value32, StdHeader);
      GnbLibPciRMW (MAKE_SBDFO (0, 0, 9, 2, 0x48), AccessWidth32, 0xFFFFFDFD, BIT9, StdHeader);

      GnbRegisterReadCZ (GnbHandle, D0F0x64_x50_TYPE, D0F0x64_x50_ADDRESS, &D0F0x64_x50.Value, 0, StdHeader);
      D0F0x64_x50.Field.ACGPortB_BusMasterDis = 1;
      D0F0x64_x50.Field.ACGPortB_P2pDis = 1;
      D0F0x64_x50.Field.ACGPortB_CfgDis = 1;
      D0F0x64_x50.Field.ACGPortB_Dis = 1;
      GnbRegisterWriteCZ (GnbHandle, D0F0x64_x50_TYPE, D0F0x64_x50_ADDRESS, &D0F0x64_x50.Value, 0, StdHeader);
    }

    Value32 = 0;
    GnbLibPciWrite (MAKE_SBDFO (0, 0, 0x18, 1, 0xB0), AccessWidth32, &Value32, StdHeader);
    GnbLibPciWrite (MAKE_SBDFO (0, 0, 0x18, 1, 0xB4), AccessWidth32, &Value32, StdHeader);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbAzaliaEarlyInitCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Request VDDB Pmin
 *
 *
 *
 * @param[in]  GnbHandle  GNB_HANDLE
 * @param[in]  StdHeader  Standard configuration header
 */

VOID
STATIC
GnbRequestVddNbPminCZ (
  IN      GNB_HANDLE                      *GnbHandle,
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{

}

/*----------------------------------------------------------------------------------------*/
/**
 * Initialize GFX straps.
 *
 *
 * @param[in] StdHeader  Standard configuration header
 */

VOID
STATIC
GfxStrapsEarlyInitCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  D0F0xD4_x013014AC_STRUCT    D0F0xD4_x13014AC;
  D0F0xD4_x013014B6_STRUCT    D0F0xD4_x13014B6;
  D0F0xD4_x013014BE_STRUCT    D0F0xD4_x13014BE;
  D0F0xD4_x013014B8_STRUCT    D0F0xD4_x13014B8;
  GNB_HANDLE                 *GnbHandle;
  AMD_EARLY_PARAMS           *EarlyParams;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxStrapsEarlyInitCZ Enter\n");

  GnbHandle = GnbGetHandle (StdHeader);
  EarlyParams = (AMD_EARLY_PARAMS *) StdHeader;

  GnbRegisterReadCZ (GnbHandle, D0F0xD4_x013014AC_TYPE, D0F0xD4_x013014AC_ADDRESS, &D0F0xD4_x13014AC.Value, 0, StdHeader);
  GnbRegisterReadCZ (GnbHandle, D0F0xD4_x013014B6_TYPE, D0F0xD4_x013014B6_ADDRESS, &D0F0xD4_x13014B6.Value, 0, StdHeader);
  GnbRegisterReadCZ (GnbHandle, D0F0xD4_x013014BE_TYPE, D0F0xD4_x013014BE_ADDRESS, &D0F0xD4_x13014BE.Value, 0, StdHeader);
  GnbRegisterReadCZ (GnbHandle, D0F0xD4_x013014B8_TYPE, D0F0xD4_x013014B8_ADDRESS, &D0F0xD4_x13014B8.Value, 0, StdHeader);

  D0F0xD4_x13014B8.Field.StrapBifE2ePrefixEnA = 1;
  D0F0xD4_x13014B8.Field.StrapBifExtendedFmtSupportedA = 1;

  D0F0xD4_x13014B6.Field.StrapBifAzLegacyDeviceTypeDis = 0x0;
  D0F0xD4_x13014B6.Field.StrapBifF0LegacyDeviceTypeDis = 0x0;

  D0F0xD4_x13014AC.Field.StrapBifAudioEnPin = EarlyParams->PlatformConfig.GnbHdAudio;
  D0F0xD4_x13014B6.Field.StrapBifAudioEn = EarlyParams->PlatformConfig.GnbHdAudio;

  // Enable PCI Vendor Specific Capabilities
  D0F0xD4_x13014BE.Field.StrapBifSymalignHwDebug = 1;

  GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x013014AC_TYPE, D0F0xD4_x013014AC_ADDRESS, &D0F0xD4_x13014AC.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x013014B6_TYPE, D0F0xD4_x013014B6_ADDRESS, &D0F0xD4_x13014B6.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x013014BE_TYPE, D0F0xD4_x013014BE_ADDRESS, &D0F0xD4_x13014BE.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x013014B8_TYPE, D0F0xD4_x013014B8_ADDRESS, &D0F0xD4_x13014B8.Value, 0, StdHeader);


  IDS_HDT_CONSOLE (GNB_TRACE, "GfxStrapsEarlyInitCZ Exit\n");
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enable Gfx gBIF
 *
 *
 * @param[in] StdHeader  Standard configuration header
 * @retval    AGESA_STATUS
 */

AGESA_STATUS
STATIC
GfxGBifEnableCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  D0F0xD4_x01301486_STRUCT    D0F0xD4_x1301486;
  D0F0xD4_x01091518_STRUCT    D0F0xD4_x1091518;
  D0F0xBC_xC0014000_STRUCT    D0F0xBC_xC0014000;
  GNB_HANDLE                  *GnbHandle;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGBifEnableCZ Enter\n");
  GnbHandle = GnbGetHandle (StdHeader);

  GnbRegisterReadCZ (GnbHandle, D0F0xBC_xC0014000_TYPE, D0F0xBC_xC0014000_ADDRESS, &D0F0xBC_xC0014000.Value, 0, StdHeader);
  if (D0F0xBC_xC0014000.Field.GPU_DIS != 1) {
    GfxStrapsEarlyInitCZ (StdHeader);
  } else {
    GnbSmuRequestGpuPowerV8 (GnbHandle, SMC_MSG_PowerDownGpu, StdHeader);
  }

  GnbRegisterReadCZ (GnbHandle, D0F0xD4_x01301486_TYPE, D0F0xD4_x01301486_ADDRESS, &D0F0xD4_x1301486.Value, 0, StdHeader);
  GnbRegisterReadCZ (GnbHandle, D0F0xD4_x01091518_TYPE, D0F0xD4_x01091518_ADDRESS, &D0F0xD4_x1091518.Value, 0, StdHeader);
  D0F0xD4_x1301486.Field.LinkTrainEn = 0x1;
  D0F0xD4_x1091518.Field.LinkTrainEn = 0x1;
  GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x01091518_TYPE, D0F0xD4_x01091518_ADDRESS, &D0F0xD4_x1091518.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x01301486_TYPE, D0F0xD4_x01301486_ADDRESS, &D0F0xD4_x1301486.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGBifEnableCZ Exit\n");

  return  AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GNB load build options data
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
STATIC
GnbLoadBuildOptionDataCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  GNB_BUILD_OPTIONS_CZ    *GnbBuildOptionData;
// todo:_Workaround  CPU_LOGICAL_ID          LogicalId;
  CPUID_DATA              CpuId;

  GnbBuildOptionData = (GNB_BUILD_OPTIONS_CZ *) GnbAllocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, sizeof (GNB_BUILD_OPTIONS_CZ), StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  GnbBuildOptionData->GnbCommonOptions.CfgScsSupport = GnbBuildOptionsCZ.GnbCommonOptions.CfgScsSupport;
  GnbBuildOptionData->GnbCommonOptions.CfgUmaSteering = GnbBuildOptionsCZ.GnbCommonOptions.CfgUmaSteering;
  GnbBuildOptionData->GnbCommonOptions.GmcPowerGating = GnbBuildOptionsCZ.GnbCommonOptions.GmcPowerGating;
  GnbBuildOptionData->GnbCommonOptions.CfgGmcClockGating = GnbBuildOptionsCZ.GnbCommonOptions.CfgGmcClockGating;
  GnbBuildOptionData->GnbCommonOptions.CfgOrbDynWakeEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgOrbDynWakeEnable;
  GnbBuildOptionData->GnbCommonOptions.CfgOrbClockGatingEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgOrbClockGatingEnable;
  GnbBuildOptionData->GnbCommonOptions.CfgIommuL1ClockGatingEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgIommuL1ClockGatingEnable;
  GnbBuildOptionData->GnbCommonOptions.CfgIommuL2ClockGatingEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgIommuL2ClockGatingEnable;
//  GnbBuildOptionData->GnbCommonOptions.LclkDeepSleepEn = GnbBuildOptionsCZ.GnbCommonOptions.LclkDeepSleepEn;
//  GnbBuildOptionData->GnbCommonOptions.LclkDpmEn = GnbBuildOptionsCZ.GnbCommonOptions.LclkDpmEn;
  GnbBuildOptionData->GnbCommonOptions.CfgIocLclkClockGatingEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgIocLclkClockGatingEnable;
  GnbBuildOptionData->GnbCommonOptions.CfgBapmSupport = GnbBuildOptionsCZ.GnbCommonOptions.CfgBapmSupport;
  GnbBuildOptionData->GnbCommonOptions.CfgDcTdpEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgDcTdpEnable;

  GnbBuildOptionData->GnbCommonOptions.CfgSmuMessageEnable = GnbBuildOptionsCZ.GnbCommonOptions.CfgSmuMessageEnable;

// todo:_PSP Lib
//  if (CheckPspRecoveryFlagV1 ()) {
//    GnbBuildOptionData->GnbCommonOptions.CfgSmuMessageEnable = FALSE;
//  }

  GnbBuildOptionData->CfgChubClockGating = GnbBuildOptionsCZ.CfgChubClockGating;
  GnbBuildOptionData->CfgAcpClockGating = GnbBuildOptionsCZ.CfgAcpClockGating;
  GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Value = GnbBuildOptionsCZ.CfgSMUServiceEnablementBitMap.Value;

// todo:_Workaround
//  GetLogicalIdOfCurrentCore (&LogicalId, StdHeader);
//  if ((LogicalId.Revision & AMD_F15_BR_A1) != 0) {
  GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.AVFS = 1;
//  }

  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
//  if (((CpuId.EBX_Reg >> 28) & 0xF) == BR_PKG_FP4) {
  GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.BBB = 0;
  GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.IBS = 0;
  GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.STAPM = 0;
    // GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.SCLK_STRETCHER = 1;
//  }

  GnbBuildOptionData->CfgAxgDisable = GnbBuildOptionsCZ.CfgAxgDisable;
  GnbBuildOptionData->CfgPcieHwInitPwerGating = GnbBuildOptionsCZ.CfgPcieHwInitPwerGating;
  GnbBuildOptionData->CfgAriSupport = GnbBuildOptionsCZ.CfgAriSupport;
  GnbBuildOptionData->CfgSpgClockGatingEnable = GnbBuildOptionsCZ.CfgSpgClockGatingEnable;
  GnbBuildOptionData->CfgAcgAzClockGatingEnable = GnbBuildOptionsCZ.CfgAcgAzClockGatingEnable;
  GnbBuildOptionData->CfgIommuL1MemPowerGating = GnbBuildOptionsCZ.CfgIommuL1MemPowerGating;
  GnbBuildOptionData->CfgIommuL2MemPowerGating = GnbBuildOptionsCZ.CfgIommuL2MemPowerGating;
  GnbBuildOptionData->CfgOrbTxMemPowerGating = GnbBuildOptionsCZ.CfgOrbTxMemPowerGating;
  GnbBuildOptionData->CfgOrbRxMemPowerGating = GnbBuildOptionsCZ.CfgOrbRxMemPowerGating;
  GnbBuildOptionData->CfgSstunlClkGating = GnbBuildOptionsCZ.CfgSstunlClkGating;
  GnbBuildOptionData->CfgParityErrorConfiguration = GnbBuildOptionsCZ.CfgParityErrorConfiguration;
  GnbBuildOptionData->CfgSpgMemPowerGatingEnable = GnbBuildOptionsCZ.CfgSpgMemPowerGatingEnable;
  GnbBuildOptionData->CfgAcgAzMemPowerGatingEnable = GnbBuildOptionsCZ.CfgAcgAzMemPowerGatingEnable;
  GnbBuildOptionData->CfgBifMemPowerGatingEnable = GnbBuildOptionsCZ.CfgBifMemPowerGatingEnable;
  GnbBuildOptionData->CfgSDMAMemPowerGatingEnable = GnbBuildOptionsCZ.CfgSDMAMemPowerGatingEnable;
  GnbBuildOptionData->CfgPcieTxpwrInOff = GnbBuildOptionsCZ.CfgPcieTxpwrInOff;
  GnbBuildOptionData->CfgPcieRxpwrInOff = GnbBuildOptionsCZ.CfgPcieRxpwrInOff;
  GnbBuildOptionData->CfgBTCEnable = GnbBuildOptionsCZ.CfgBTCEnable;
  GnbBuildOptionData->CfgPSIEnable = GnbBuildOptionsCZ.CfgPSIEnable;
  GnbBuildOptionData->CfgACSEnable = GnbBuildOptionsCZ.CfgACSEnable;
  GnbBuildOptionData->CfgShadowPstates = GnbBuildOptionsCZ.CfgShadowPstates;
  if (GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.AVFS == 0) {
    GnbBuildOptionData->CfgShadowPstates = 0;
  }

  IDS_OPTION_CALLOUT (IDS_CALLOUT_GNB_BUILDOPTIONS_OVERRIDE, GnbBuildOptionData, StdHeader);
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GNB init at early post
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
GnbEarlyInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS     Status;
  AGESA_STATUS     AgesaStatus;
  GNB_HANDLE       *GnbHandle;
  UINT32           Property;
  GNB_BUILD_OPTIONS_CZ  *GnbBuildOptionData;
  D18F5x174_STRUCT      D18F5x174;
  AMD_EARLY_PARAMS      *EarlyParamsPtr;
  D0F2xFC_x32_L1_STRUCT D0F2xFC_x32_L1;

  AgesaStatus = AGESA_SUCCESS;
  AGESA_TESTPOINT (TpGnbEarlyInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEarlyInterfaceCZ Enter\n");
  GnbHandle = GnbGetHandle (StdHeader);

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);

  // Check if NbPstate disable
  GnbRegisterReadCZ (GnbHandle, TYPE_D18F5, D18F5x174_ADDRESS, &D18F5x174.Value, 0, StdHeader);
  if (D18F5x174.Field.NbPstateDis == 1) {
    // If NbPstate disabled, then disable NBDPM for SMU
    GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.NB_DPM = 0;
  }

  EarlyParamsPtr = (AMD_EARLY_PARAMS *) StdHeader;
  GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.CONN_STDBY = 0;

  Property = TABLE_PROPERTY_DEFAULT;
  Property |= UserOptions.CfgGnbSyncFloodPinAsNmi ? TABLE_PROPERTY_NMI_SYNCFLOOD : 0;
  Property |= GnbBuildOptionData->GnbCommonOptions.CfgBapmSupport ? TABLE_PROPERTY_BAPM : 0;
  Status = GnbProcessTable (
             GnbHandle,
             GnbEarlyInitTableCZ,
             Property,
             0,
             StdHeader
             );
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  Status = GnbProcessTable (
             GnbHandle,
             GnbIommuEarlyInitTableCZ,
             Property,
             0,
             StdHeader
             );
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (FchReadSleepType() != 0x03) {
    GnbRegisterReadCZ (GnbHandle, D0F2xFC_x32_L1_TYPE, D0F2xFC_x32_L1_ADDRESS (L1_SEL_IOAGR), &D0F2xFC_x32_L1.Value, 0, StdHeader);
    D0F2xFC_x32_L1.Field.AtsMultipleRespEn = 0x1;
    D0F2xFC_x32_L1.Field.AtsMultipleL1toL2En = 0x1;
    D0F2xFC_x32_L1.Field.TimeoutPulseExtEn = 0x1;
    D0F2xFC_x32_L1.Field.DmaBufCredits = 0x20;
    D0F2xFC_x32_L1.Field.DmaBufMaxNpCred = 0x20;
    D0F2xFC_x32_L1.Field.DmaNpHaltDis = 0x1;
    GnbRegisterWriteCZ (GnbHandle, D0F2xFC_x32_L1_TYPE, D0F2xFC_x32_L1_ADDRESS (L1_SEL_IOAGR), &D0F2xFC_x32_L1.Value, 0, StdHeader);
  }
//  GnbRequestVddNbPminCZ (GnbHandle, StdHeader);
  Status = GfxGBifEnableCZ (StdHeader);
  ASSERT (Status == AGESA_SUCCESS);

  GnbAzaliaEarlyInitCZ (StdHeader);

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEarlyInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpGnbEarlyInterfaceCZExit, NULL);
  return  AgesaStatus;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GNB init at earlier post
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
GnbEarlierInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS      Status;
  AGESA_STATUS      AgesaStatus;
  GNB_HANDLE        *GnbHandle;
  AgesaStatus = AGESA_SUCCESS;
  Status = AGESA_SUCCESS;
  AGESA_TESTPOINT (TpGnbEarlierInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEarlierInterfaceCZ Enter\n");
  GnbHandle = GnbGetHandle (StdHeader);

  Status = GnbProcessTable (
             GnbHandle,
             GnbEarlierInitTableBeforeSmuCZ,
             0,
             0,
             StdHeader
             );
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  Status = GnbLoadBuildOptionDataCZ (StdHeader);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);

  GnbSmuFirmwareTestV8 (GnbHandle, SMC_MSG_TEST, StdHeader);

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbEarlierInterfaceCZ Exit [0x%x]\n", Status);
  AGESA_TESTPOINT (TpGnbEarlierInterfaceCZExit, NULL);
  return  AgesaStatus;
}

