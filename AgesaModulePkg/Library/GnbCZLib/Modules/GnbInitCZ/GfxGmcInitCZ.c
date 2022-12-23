/* $NoKeywords:$ */
/**
 * @file
 *
 * GFX Memory Controller initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-26 11:00:43 +0800 (Thu, 26 Feb 2015) $
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
#include  "GnbGfx.h"
#include  "GnbCommonLib.h"
#include  "GnbTable.h"
#include  "GnbPcieConfig.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GfxLibCZ.h"
#include  "GfxGmcInitCZ.h"
#include  "Library/AmdHeapLib.h"
#include  "OptionGnb.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GFXGMCINITCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern GNB_TABLE ROMDATA GfxGmcInitTableCZ [];
extern GNB_TABLE ROMDATA GfxGmcClockGatingEnableCZ [];


#define GNB_GFX_DRAM_CH_0_PRESENT 1
#define GNB_GFX_DRAM_CH_1_PRESENT 2

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
 * Initialize Fb location
 *
 *
 *
 * @param[in]   GnbHandle         Pointer to GNB_HANDLE
 * @param[in]   Gfx               Pointer to global GFX configuration
 *
 */
VOID
GfxGmcInitializeFbLocationCZ (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  GMMx2024_STRUCT   GMMx2024;
  GMMx2068_STRUCT   GMMx2068;
  GMMx2C04_STRUCT   GMMx2C04;
  GMMx5428_STRUCT   GMMx5428;
  UINT64            FBBase;
  UINT64            FBTop;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGmcInitializeFbLocationCZ Enter\n");

  FBBase = 0x0F400000000;
  FBTop = FBBase + Gfx->UmaInfo.UmaSize - 1;
  GMMx2024.Value = 0;
  GMMx2C04.Value = 0;
  GMMx2024.Field.FB_BASE = (UINT16) (FBBase >> 24);
  GMMx2024.Field.FB_TOP = (UINT16) (FBTop >> 24);
  GMMx2068.Field.FB_OFFSET = (UINT32) (Gfx->UmaInfo.UmaBase >> 22);
  GMMx2C04.Field.NONSURF_BASE = (UINT32) (FBBase >> 8);
  GMMx5428.Field.CONFIG_MEMSIZE = Gfx->UmaInfo.UmaSize >> 20;
  GnbRegisterWriteCZ (GnbHandle, GMMx2024_TYPE, GMMx2024_ADDRESS, &GMMx2024.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  GnbRegisterWriteCZ (GnbHandle, GMMx2068_TYPE, GMMx2068_ADDRESS, &GMMx2068.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  GnbRegisterWriteCZ (GnbHandle, GMMx2C04_TYPE, GMMx2C04_ADDRESS, &GMMx2C04.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  GnbRegisterWriteCZ (GnbHandle, GMMx5428_TYPE, GMMx5428_ADDRESS, &GMMx5428.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
}

/*----------------------------------------------------------------------------------------*/
/**
 * Secure Garlic Access
 *
 *
 *
 * @param[in]   GnbHandle         Pointer to GNB_HANDLE
 * @param[in]   Gfx               Pointer to global GFX configuration
 *
 */
VOID
GfxGmcSecureGarlicAccessCZ (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  UINT32   GMMx2868;
  UINT32   GMMx286C;
  UINT32   GMMx2878;

  GMMx2868 = (UINT32) (Gfx->UmaInfo.UmaBase >> 20);
  GnbRegisterWriteCZ (GnbHandle, GMMx2868_TYPE, GMMx2868_ADDRESS, &GMMx2868, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  GMMx286C = (UINT32) (((Gfx->UmaInfo.UmaBase + Gfx->UmaInfo.UmaSize) >> 20) - 1);
  GnbRegisterWriteCZ (GnbHandle, GMMx286C_TYPE, GMMx286C_ADDRESS, &GMMx286C, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  // Area FB - 32K reserved by VBIOS for SBIOS to use
  GMMx2878 = (UINT32) ((Gfx->UmaInfo.UmaBase + Gfx->UmaInfo.UmaSize - 32 * 1024) >> 12);
  GnbRegisterWriteCZ (GnbHandle, GMMx2878_TYPE, GMMx2878_ADDRESS, &GMMx2878, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
}

/*----------------------------------------------------------------------------------------*/
/**
 * Performance Programming for DDR4
 *
 *
 *
 * @param[in]   GnbHandle         Pointer to GNB_HANDLE
 * @param[in]   Gfx               Pointer to global GFX configuration
 *
 */
VOID
GfxGmcPerformanceProgrammingDDR4CZ (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  D18F2x94_dct0_STRUCT           D18F2x94_dct0;
  D18F2x94_dct0_STRUCT           D18F2x94_dct1;
  D18F2x78_dct0_STRUCT           D18F2x78_dct0;
  D18F2x78_dct0_STRUCT           D18F2x78_dct1;
  UINT32                         GMMx2764;
  UINT32                         GMMx27C0;
  UINT32                         GMMx27C4;
  UINT32                         GMMx27d4;
  UINT32                         GMMx276c;
  UINT32                         GMMx2774;
  UINT32                         GMMx27f0;
  UINT32                         GMMx2778;
  UINT32                         GMMx27fc;
  UINT32                         GMMx2808;

  GnbRegisterReadCZ (GnbHandle, D18F2x94_dct0_TYPE, D18F2x94_dct0_ADDRESS, &D18F2x94_dct0.Value, 0, GnbLibGetHeader (Gfx));
  GnbRegisterReadCZ (GnbHandle, D18F2x94_dct1_TYPE, D18F2x94_dct1_ADDRESS, &D18F2x94_dct1.Value, 0, GnbLibGetHeader (Gfx));
  GnbRegisterReadCZ (GnbHandle, D18F2x78_dct0_TYPE, D18F2x78_dct0_ADDRESS, &D18F2x78_dct0.Value, 0, GnbLibGetHeader (Gfx));
  GnbRegisterReadCZ (GnbHandle, D18F2x78_dct1_TYPE, D18F2x78_dct1_ADDRESS, &D18F2x78_dct1.Value, 0, GnbLibGetHeader (Gfx));

  if ((D18F2x94_dct0.Field.DisDramInterface != 1) || (D18F2x94_dct1.Field.DisDramInterface != 1)) {
    if ((D18F2x78_dct0.Field.DramType == 2) || (D18F2x78_dct1.Field.DramType == 2)) {
      // Set MC_ARB_POP register
      GMMx2764 = 0x45911;
      GnbRegisterWriteCZ (GnbHandle, GMMx2764_TYPE, GMMx2764_ADDRESS, &GMMx2764, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Set MC_ARB_LM_RD and MC_ARB_LM_WR
      GMMx27C0 = 0x8f2008;
      GnbRegisterWriteCZ (GnbHandle, GMMx27C0_TYPE, GMMx27C0_ADDRESS, &GMMx27C0, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      GMMx27C4 = 0x48f2006;
      GnbRegisterWriteCZ (GnbHandle, GMMx27C4_TYPE, GMMx27C4_ADDRESS, &GMMx27C4, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Program MC_ARB_RET_CREDITS_WR
      GMMx27d4 = 0x0302706f;
      GnbRegisterWriteCZ (GnbHandle, GMMx27D4_TYPE, GMMx27D4_ADDRESS, &GMMx27d4, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Program MC_ARB_SQM_CNTL
      GMMx276c = 0x118;
      GnbRegisterWriteCZ (GnbHandle, GMMx276C_TYPE, GMMx276C_ADDRESS, &GMMx276c, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Program MC_ARB_DRAM_TIMING
      GMMx2774 = 0x0;
      GnbRegisterWriteCZ (GnbHandle, GMMx2774_TYPE, GMMx2774_ADDRESS, &GMMx2774, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Program MC_ARB_DRAM_TIMING_1
      GMMx27f0 = 0x0;
      GnbRegisterWriteCZ (GnbHandle, GMMx27F0_TYPE, GMMx27F0_ADDRESS, &GMMx27f0, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Program MC_ARB_DRAM_TIMING2 and MC_ARB_DRAM_TIMING2_1
      GMMx2778 = 0x0;
      GnbRegisterWriteCZ (GnbHandle, GMMx2778_TYPE, GMMx2778_ADDRESS, &GMMx2778, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      GMMx27fc = 0x0;
      GnbRegisterWriteCZ (GnbHandle, GMMx27FC_TYPE, GMMx27FC_ADDRESS, &GMMx27fc, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
      // Program  MC_ARB_BURST_TIME
      GMMx2808 = 0x0;
      GnbRegisterWriteCZ (GnbHandle, GMMx2808_TYPE, GMMx2808_ADDRESS, &GMMx2808, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Enable Stutter Mode with/without power-gating
 *
 *
 *
 * @param[in]   GnbHandle         Pointer to GNB_HANDLE
 * @param[in]   Gfx               Pointer to global GFX configuration
 *
 */
VOID
GfxGmcEnableStutterModePowerGatingCZ (
  IN      GNB_HANDLE            *GnbHandle,
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  GMMx3508_STRUCT   GMMx3508;
  GMMx350C_STRUCT   GMMx350C;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGmcEnableStutterModePowerGatingCZ Enter\n");

  GnbRegisterReadCZ (GnbHandle, GMMx3508_TYPE, GMMx3508_ADDRESS, &GMMx3508.Value, 0, GnbLibGetHeader (Gfx));
  GnbRegisterReadCZ (GnbHandle, GMMx350C_TYPE, GMMx350C_ADDRESS, &GMMx350C.Value, 0, GnbLibGetHeader (Gfx));
  if (Gfx->GmcPowerGating != GmcPowerGatingDisabled) {
    // Enabling power gating
    if (Gfx->GmcPowerGating == GmcPowerGatingWithStutter) {
      GMMx3508.Field.RENG_EXECUTE_ON_PWR_UP = 1;
      GMMx350C.Field.RENG_EXECUTE_ON_REG_UPDATE = 1;
      GMMx350C.Field.STCTRL_STUTTER_EN = 0;
    } else {
      GMMx3508.Field.RENG_EXECUTE_ON_PWR_UP = 0;
      GMMx350C.Field.RENG_EXECUTE_ON_REG_UPDATE = 0;
      GMMx350C.Field.STCTRL_STUTTER_EN = 1;
    }
  } else {
    // Disabling power gating
    GMMx3508.Field.RENG_EXECUTE_ON_PWR_UP = 0;
    GMMx350C.Field.RENG_EXECUTE_ON_REG_UPDATE = 0;
    GMMx350C.Field.STCTRL_STUTTER_EN = 0;
  }
  GnbRegisterWriteCZ (GnbHandle, GMMx3508_TYPE, GMMx3508_ADDRESS, &GMMx3508.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  GnbRegisterWriteCZ (GnbHandle, GMMx350C_TYPE, GMMx350C_ADDRESS, &GMMx350C.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGmcEnableStutterModePowerGatingCZ Exit\n");
}


/*----------------------------------------------------------------------------------------*/
/**
 * Initialize GMC
 *
 *
 *
 * @param[in]   Gfx               Pointer to global GFX configuration
 *
 */

AGESA_STATUS
GfxGmcInitCZ (
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  GMMx2878_STRUCT   GMMx2878;
  GMMx5228_STRUCT   GMMx5228;
  UINT32            GMMx206C;
  GMMxD008_STRUCT   GMMxD008;
  GMMxD808_STRUCT   GMMxD808;

  GNB_HANDLE        *GnbHandle;
  GNB_BUILD_OPTIONS_CZ      *GnbBuildOptionData;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGmcInitCZ Enter\n");
  GnbHandle = GnbGetHandle (GnbLibGetHeader (Gfx));
  ASSERT (GnbHandle != NULL);

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, GnbLibGetHeader (Gfx));
  ASSERT (GnbBuildOptionData != NULL);

  //2.5 Frame buffer location
  GfxGmcInitializeFbLocationCZ (GnbHandle, Gfx);

  //2.6.1 Frame-buffer aperture
  GfxGmcSecureGarlicAccessCZ (GnbHandle, Gfx);

  GnbProcessTable (
    GnbHandle,
    GfxGmcInitTableCZ,
    0,
    GNB_TABLE_FLAGS_FORCE_S3_SAVE,
    GnbLibGetHeader (Gfx)
    );

  //2.5.1 Additional Performance Programming for DDR4
  GfxGmcPerformanceProgrammingDDR4CZ (GnbHandle, Gfx);

  //4. Power management
  //4.1 Enabling clock-gating
  if (Gfx->GmcClockGating) {
    GnbProcessTable (
      GnbHandle,
      GfxGmcClockGatingEnableCZ,
      0,
      GNB_TABLE_FLAGS_FORCE_S3_SAVE,
      GnbLibGetHeader (Gfx)
      );
  }

  //5. Steering all requests to ONION
  switch (Gfx->UmaSteering) {
  case DefaultGarlic:
    // APU
    GMMx206C = 0;
    break;
  case SystemTrafficOnion:
    // dGPU
    GMMx206C = 1;
    break;
  case Onion:
    // debug, everything to BIF
    GMMx206C = 2;
    break;
  case Garlic:
    // debug, only fb and non-snoop system to onion3
    GMMx206C = 3;
    break;
  default:
    GMMx206C = 0;
    ASSERT (FALSE);
    break;
  }
  GnbRegisterWriteCZ (GnbHandle, GMMx206C_TYPE, GMMx206C_ADDRESS, &GMMx206C, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));

  if (GnbBuildOptionData->CfgBifMemPowerGatingEnable) {
    GnbRegisterReadCZ (GnbHandle, GMMx5228_TYPE, GMMx5228_ADDRESS, &GMMx5228, 0, GnbLibGetHeader (Gfx));
    GMMx5228.Field.BIF_MEM_SD_EN = 1;
    GnbRegisterWriteCZ (GnbHandle, GMMx5228_TYPE, GMMx5228_ADDRESS, &GMMx5228, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  }

  // SDMA Memory Power Gating
  if (GnbBuildOptionData->CfgSDMAMemPowerGatingEnable) {
    GnbRegisterReadCZ (GnbHandle, GMMxD008_TYPE, GMMxD008_ADDRESS, &GMMxD008.Value, 0, GnbLibGetHeader (Gfx));
    GnbRegisterReadCZ (GnbHandle, GMMxD808_TYPE, GMMxD808_ADDRESS, &GMMxD808.Value, 0, GnbLibGetHeader (Gfx));

    GMMxD008.Field.MEM_POWER_OVERRIDE = 1;
    GMMxD808.Field.MEM_POWER_OVERRIDE = 1;
    GMMxD008.Field.MEM_POWER_SD_EN = 1;
    GMMxD808.Field.MEM_POWER_SD_EN = 1;

    GnbRegisterWriteCZ (GnbHandle, GMMxD008_TYPE, GMMxD008_ADDRESS, &GMMxD008.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
    GnbRegisterWriteCZ (GnbHandle, GMMxD808_TYPE, GMMxD808_ADDRESS, &GMMxD808.Value, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  }

  IDS_OPTION_CALLOUT (IDS_CALLOUT_GNB_GMM_REGISTER_OVERRIDE, Gfx, GnbLibGetHeader (Gfx));
  // 2.6.1 Locking critical register
  if (Gfx->GmcLockRegisters) {
    GnbRegisterReadCZ (GnbHandle, GMMx2878_TYPE, GMMx2878_ADDRESS, &GMMx2878, 0, GnbLibGetHeader (Gfx));
    GMMx2878.Field.LOCK_MC_FUS_DRAM_REGS = 1;
    GnbRegisterWriteCZ (GnbHandle, GMMx2878_TYPE, GMMx2878_ADDRESS, &GMMx2878, GNB_REG_ACC_FLAG_S3SAVE, GnbLibGetHeader (Gfx));
  }
  //4.2 Enabling stutter mode with or without power-gating
  GfxGmcEnableStutterModePowerGatingCZ (GnbHandle, Gfx);

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxGmcInitCZ Exit\n");
  return AGESA_SUCCESS;
}

