/* $NoKeywords:$ */
/**
 * @file
 *
 * GFX POST initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 328050 $   @e \$Date: 2015-09-29 06:53:15 +0800 (Tue, 29 Sep 2015) $
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
#include  "GnbPcie.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbGfx.h"
#include  "GfxConfigLib.h"
#include  "GnbFuseTable.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GnbSmuInitLibV8.h"
#include  "OptionGnb.h"
#include  "GnbLibHeap.h"
#include  "GnbFamServices.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GFXPOSTINITCZ_FILECODE
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
AGESA_STATUS
GfxPostInterfaceCZ (
  IN       AMD_CONFIG_PARAMS               *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Allocate UMA configuration data
 *
 *
 *
 * @param[in]     StdHeader     Standard configuration header
 * @retval        AGESA_STATUS  Always succeeds
 */

AGESA_STATUS
GfxConfigPostInterfaceCZ (
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  GFX_PLATFORM_CONFIG       *Gfx;
  AMD_POST_PARAMS           *PostParamsPtr;
  AGESA_STATUS              Status;
  GNB_BUILD_OPTIONS_COMMON  *GnbCommonOptions;
  PostParamsPtr = (AMD_POST_PARAMS *)StdHeader;
  Status = AGESA_SUCCESS;
  AGESA_TESTPOINT (TpGfxConfigPostInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxConfigPostInterfaceCZ Enter\n");
  Gfx = GnbAllocateHeapBuffer (AMD_GFX_PLATFORM_CONFIG_HANDLE, sizeof (GFX_PLATFORM_CONFIG), StdHeader);
  ASSERT (Gfx != NULL);
  if (Gfx != NULL) {
    LibAmdMemFill (Gfx, 0x00, sizeof (GFX_PLATFORM_CONFIG), StdHeader);
    GnbCommonOptions = (GNB_BUILD_OPTIONS_COMMON*) GnbFmGnbBuildOptions (StdHeader);
    if (GnbBuildOptions.IgfxModeAsPcieEp) {
      Gfx->GfxControllerMode = GfxControllerPcieEndpointMode;
      Gfx->GfxPciAddress.AddressValue = MAKE_SBDFO (0, 0, 1, 0, 0);
    } else {
      Gfx->GfxControllerMode = GfxControllerLegacyBridgeMode;
      Gfx->GfxPciAddress.AddressValue = MAKE_SBDFO (0, 1, 5, 0, 0);
    }
    Gfx->StdHeader = (PVOID) StdHeader;
    Gfx->GnbHdAudio = TRUE;//CFG_GNB_HD_AUDIO;                    //form UserOptions PostParamsPtr->PlatformConfig.GnbHdAudio;
    Gfx->AbmSupport = FALSE;//CFG_ABM_SUPPORT;                     //form UserOptions PostParamsPtr->PlatformConfig.AbmSupport;
    Gfx->DynamicRefreshRate = 0;//CFG_DYNAMIC_REFRESH_RATE;    //form UserOptions PostParamsPtr->PlatformConfig.DynamicRefreshRate;
    Gfx->LcdBackLightControl = 200;//CFG_LCD_BACK_LIGHT_CONTROL; //form UserOptions PostParamsPtr->PlatformConfig.LcdBackLightControl;
    Gfx->AmdPlatformType = 0;//CFG_AMD_PLATFORM_TYPE;          //form UserOptions UserOptions.CfgAmdPlatformType;
    Gfx->GmcClockGating = GnbCommonOptions->CfgGmcClockGating;
    Gfx->GmcPowerGating = GnbCommonOptions->GmcPowerGating;
    Gfx->UmaSteering = GnbCommonOptions->CfgUmaSteering;
    GNB_DEBUG_CODE (
      GfxConfigDebugDump (Gfx);
      );
  } else {
    Status = AGESA_ERROR;
  }
  IDS_OPTION_HOOK (IDS_GNB_PLATFORMCFG_OVERRIDE, Gfx, StdHeader);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxConfigPostInterfaceCZ Exit [0x%x]\n", Status);
  AGESA_TESTPOINT (TpGfxConfigPostInterfaceCZExit, NULL);
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init GFX at Post.
 *
 *
 *
 * @param[in]     StdHeader     Standard configuration header
 * @retval        AGESA_STATUS
 */


AGESA_STATUS
GfxPostInterfaceCZ (
  IN       AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AMD_POST_PARAMS           *PostParamsPtr;
  AGESA_STATUS              Status;
  GFX_PLATFORM_CONFIG       *Gfx;
  D0F0xBC_xC0014000_STRUCT  D0F0xBC_xC0014000;
  D0F0xD4_x013014AC_STRUCT  D0F0xD4_x13014AC;
  D0F0xD4_x013014B6_STRUCT  D0F0xD4_x13014B6;
  GNB_HANDLE                *GnbHandle;

  PostParamsPtr = (AMD_POST_PARAMS *)StdHeader;
  Status = AGESA_SUCCESS;
  AGESA_TESTPOINT (TpGfxPostInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxPostInterfaceCZ Enter\n");
  GnbHandle = GnbGetHandle (StdHeader);
  ASSERT (GnbHandle != NULL);
  GnbRegisterReadCZ (GnbHandle, D0F0xBC_xC0014000_TYPE,
      D0F0xBC_xC0014000_ADDRESS, &D0F0xBC_xC0014000.Value, 0, StdHeader);
  Status = GfxLocateConfigData (StdHeader, &Gfx);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    if (D0F0xBC_xC0014000.Field.GPU_DIS == 1) {
      PostParamsPtr->MemConfig.UmaMode = UMA_NONE;
      Gfx->GfxFusedOff = TRUE;
    }
  } else {
    PostParamsPtr->MemConfig.UmaMode = UMA_NONE;
  }
  if (PostParamsPtr->MemConfig.UmaMode == UMA_NONE) {
    GnbRegisterReadCZ (GnbHandle, D0F0xD4_x013014AC_TYPE, D0F0xD4_x013014AC_ADDRESS, &D0F0xD4_x13014AC.Value, 0, StdHeader);
    GnbRegisterReadCZ (GnbHandle, D0F0xD4_x013014B6_TYPE, D0F0xD4_x013014B6_ADDRESS, &D0F0xD4_x13014B6.Value, 0, StdHeader);
    D0F0xD4_x13014AC.Field.StrapBifAudioEnPin = FALSE;
    D0F0xD4_x13014B6.Field.StrapBifAudioEn = FALSE;
    GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x013014AC_TYPE, D0F0xD4_x013014AC_ADDRESS, &D0F0xD4_x13014AC.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
    GnbRegisterWriteCZ (GnbHandle, D0F0xD4_x013014B6_TYPE, D0F0xD4_x013014B6_ADDRESS, &D0F0xD4_x13014B6.Value, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxPostInterfaceCZ Exit [0x%x]\n", Status);
  AGESA_TESTPOINT (TpGfxPostInterfaceCZExit, NULL);
  return  Status;
}

