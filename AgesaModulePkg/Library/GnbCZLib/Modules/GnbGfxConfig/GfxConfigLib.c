/* $NoKeywords:$ */
/**
 * @file
 *
 * Initialize GFX configuration data structure.
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
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbGfx.h"
#include  "GfxConfigLib.h"
#include  "GnbCommonLib.h"
#include  "OptionGnb.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBGFXCONFIG_GFXCONFIGLIB_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


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
 * Get UMA info
 *
 * UMA info stored on heap by memory module
 *
 * @param[out] UmaInfo      Pointer to UMA info structure
 * @param[in]  StdHeader    Standard configuration header
 */

VOID
GfxGetUmaInfo (
     OUT   UMA_INFO          *UmaInfo,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UMA_INFO *MemUmaInfo;

  MemUmaInfo = GnbLocateHeapBuffer (AMD_UMA_INFO_HANDLE, StdHeader);
  if (MemUmaInfo == NULL) {
    LibAmdMemFill (UmaInfo, 0x00, sizeof (UMA_INFO), StdHeader);
    UmaInfo->UmaMode = UMA_NONE;
  } else {
    LibAmdMemCopy (UmaInfo, MemUmaInfo, sizeof (UMA_INFO), StdHeader);
    if ((UmaInfo->UmaBase == 0) || (UmaInfo->UmaSize == 0)) {
      UmaInfo->UmaMode = UMA_NONE;
    }
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Locate UMA configuration data
 *
 *
 *
 * @param[in]     StdHeader     Standard configuration header
 * @param[in,out] Gfx           Pointer to GFX configuration
 * @retval        AGESA_STATUS  Data located
 * @retval        AGESA_FATA    Data not found
 */

AGESA_STATUS
GfxLocateConfigData (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
     OUT   GFX_PLATFORM_CONFIG   **Gfx
  )
{
  *Gfx = GnbLocateHeapBuffer (AMD_GFX_PLATFORM_CONFIG_HANDLE, StdHeader);
  if (*Gfx == NULL) {
    IDS_ERROR_TRAP;
    return  AGESA_FATAL;
  }
  (*Gfx)->StdHeader = (PVOID) StdHeader;
  return AGESA_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Debug dump
 *
 *
 *
 * @param[in]     Gfx           Pointer to GFX configuration
 */

VOID
GfxConfigDebugDump (
  IN       GFX_PLATFORM_CONFIG      *Gfx
  )
{
  IDS_HDT_CONSOLE (GFX_MISC, "<-------------- GFX Config Start ------------->\n");
  IDS_HDT_CONSOLE (GFX_MISC, "  HD Audio - %s\n", (Gfx->GnbHdAudio == 0) ? "Disabled" : "Enabled");
  IDS_HDT_CONSOLE (GFX_MISC, "  DynamicRefreshRate - 0x%x\n", Gfx->DynamicRefreshRate);
  IDS_HDT_CONSOLE (GFX_MISC, "  LcdBackLightControl - 0x%x\n", Gfx->LcdBackLightControl);
  IDS_HDT_CONSOLE (GFX_MISC, "  AbmSupport - %s\n", (Gfx->AbmSupport == 0) ? "Disabled" : "Enabled");
  IDS_HDT_CONSOLE (GFX_MISC, "  GmcClockGating - %s\n", (Gfx->GmcClockGating == 0) ? "Disabled" : "Enabled");
  IDS_HDT_CONSOLE (GFX_MISC, "  GmcPowerGating - %s\n",
    (Gfx->GmcPowerGating == GmcPowerGatingDisabled) ? "Disabled" : (
    (Gfx->GmcPowerGating == GmcPowerGatingStutterOnly) ? "GmcPowerGatingStutterOnly" : (
    (Gfx->GmcPowerGating == GmcPowerGatingWithStutter) ? "GmcPowerGatingWithStutter" : "Unknown"))
  );
  IDS_HDT_CONSOLE (GFX_MISC, "  UmaSteering - %s\n",
    (Gfx->UmaSteering == DefaultGarlic) ? "DefaultGarlic" : (
    (Gfx->UmaSteering == SystemTrafficOnion) ? "SystemTrafficOnion" : (
    (Gfx->UmaSteering == Onion) ? "Onion" : (
    (Gfx->UmaSteering == Garlic) ? "Garlic" : "Unknown")))
    );
  IDS_HDT_CONSOLE (GFX_MISC, "  iGpuVgaMode - %s\n",
    (Gfx->iGpuVgaMode == iGpuVgaAdapter) ? "VGA" : (
    (Gfx->iGpuVgaMode == iGpuVgaNonAdapter) ? "Non VGA" : "Unknown")
    );
  IDS_HDT_CONSOLE (GFX_MISC, "  UmaMode - %s\n", (Gfx->UmaInfo.UmaMode == UMA_NONE) ? "No UMA" : "UMA");
  if (Gfx->UmaInfo.UmaMode != UMA_NONE) {
    IDS_HDT_CONSOLE (GFX_MISC, "  UmaBase - 0x%x\n", Gfx->UmaInfo.UmaBase);
    IDS_HDT_CONSOLE (GFX_MISC, "  UmaSize - 0x%x\n", Gfx->UmaInfo.UmaSize);
    IDS_HDT_CONSOLE (GFX_MISC, "  UmaAttributes - 0x%x\n", Gfx->UmaInfo.UmaAttributes);
  }
  IDS_HDT_CONSOLE (GFX_MISC, "  BootUpDisplayDevice - 0x%x\n", Gfx->BootUpDisplayDevice);
  IDS_HDT_CONSOLE (GFX_MISC, "<-------------- GFX Config End --------------->\n");

}

