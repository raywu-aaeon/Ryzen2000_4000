/* $NoKeywords:$ */
/**
 * @file
 *
 * GFX mid post initialization.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 311542 $   @e \$Date: 2015-01-23 10:30:39 +0800 (Fri, 23 Jan 2015) $
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
#include  <Library/PcdLib.h>
#include  "Gnb.h"
#include  "GnbGfx.h"
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "GfxConfigLib.h"
#include  "GnbNbInitLib.h"
#include  "GnbGfxFamServices.h"
#include  "GfxGmcInitCZ.h"
#include  "GfxLibCZ.h"
#include  "GfxLibV5.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "PcieConfigData.h"
#include  "PcieConfigLib.h"
#include  "GnbHandleLib.h"
#include  "OptionGnb.h"
#include  "GnbSmuInitLibV8.h"
#include  "PcieLibCZ.h"
#include  "Library/AmdHeapLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GFXMIDINITCZ_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

extern GNB_BUILD_OPTIONS_CZ GnbBuildOptionsCZ;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
AGESA_STATUS
STATIC
GfxSetBootUpVoltageCZ (
  IN      GFX_PLATFORM_CONFIG   *Gfx
  );

AGESA_STATUS
GfxMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Set boot up voltage
 *
 *
 * @param[in] Gfx             Pointer to global GFX configuration
 * @retval    AGESA_STATUS
 */

AGESA_STATUS
STATIC
GfxSetBootUpVoltageCZ (
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init Gfx SSID Registers
 *
 *
 *
 * @param[in] Gfx           Pointer to global GFX configuration
 * @retval    AGESA_STATUS  Always succeeds
 */

AGESA_STATUS
GfxInitSsidCZ (
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  AGESA_STATUS    Status;
  UINT32          TempData;
  UINT32          SSIDData;
  PCI_ADDR        IgpuAddress;
  PCI_ADDR        HdaudioAddress;
  SMU_TDP_INFO      *TdpInfo;
  UINT32            SocketTDP;

  Status = AGESA_SUCCESS;
  TempData = 0;
  SSIDData = 0;

  IgpuAddress = Gfx->GfxPciAddress;
  HdaudioAddress = Gfx->GfxPciAddress;
  HdaudioAddress.Address.Function = 1;

  // Set SSID for internal GPU
  if (PcdGet32 (PcdAmdCfgGnbIGPUSSID) != 0) {
    GnbLibPciRMW ((IgpuAddress.AddressValue | 0x4C), AccessS3SaveWidth32, 0, PcdGet32 (PcdAmdCfgGnbIGPUSSID), GnbLibGetHeader (Gfx));
  } else {
    // The SSID definitions
    // The most significant digit is hard-coded to 1 to represent Carrizo
    // The next 2 digits are the CZ RID
    // The least significant digit represents TDP.  0 and 1 represent 15W and 35W respectively
    // Example of 5-part ID CZ 35W B10: VID=1002, DID=9874, SVID=OEM specific value, SSID=1C41, RID=C4(08/RevisonID)
    TdpInfo = (SMU_TDP_INFO *) GnbLocateHeapBuffer (AMD_GNB_TDP_HANDLE, GnbLibGetHeader (Gfx));
    GnbLibPciRead (IgpuAddress.AddressValue, AccessS3SaveWidth32, &TempData, GnbLibGetHeader (Gfx));
    if (TdpInfo != NULL) {
      GnbLibPciRead (IgpuAddress.AddressValue | 0x08, AccessWidth32, &SSIDData, GnbLibGetHeader (Gfx));
      SSIDData = (SSIDData & 0xFF) << 4;
      SSIDData |= 0x1000;
      // TDP value in milli watts
      SocketTDP = TdpInfo->SmuTdp;
      if (SocketTDP == 35000) {
        // 1 represent 35W
        SSIDData |= 1;
      }
      TempData &= 0xFFFF;
      TempData |= (SSIDData & 0xFFFF) << 16;
      IDS_HDT_CONSOLE (GNB_TRACE, " fGPU branding: TDP = %d, SSID=%x\n", SocketTDP, TempData);
    }
    GnbLibPciRMW ((IgpuAddress.AddressValue | 0x4C), AccessS3SaveWidth32, 0, TempData, GnbLibGetHeader (Gfx));
  }

  // Set SSID for internal HD Audio
  if (PcdGet32 (PcdAmdCfgGnbHDAudioSSID) != 0) {
    GnbLibPciRMW ((HdaudioAddress.AddressValue | 0x4C), AccessS3SaveWidth32, 0, PcdGet32 (PcdAmdCfgGnbHDAudioSSID), GnbLibGetHeader (Gfx));
  } else {
    GnbLibPciRead (HdaudioAddress.AddressValue, AccessS3SaveWidth32, &TempData, GnbLibGetHeader (Gfx));
    GnbLibPciRMW ((HdaudioAddress.AddressValue | 0x4C), AccessS3SaveWidth32, 0, TempData, GnbLibGetHeader (Gfx));
  }

  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init GFX at Mid Post.
 *
 *
 *
 * @param[in] StdHeader       Standard configuration header
 * @retval    AGESA_STATUS
 */

AGESA_STATUS
GfxMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS                Status;
  AGESA_STATUS                AgesaStatus;
  GFX_PLATFORM_CONFIG         *Gfx;
  UINT8                       AudioEPCount;
  AMD_MID_PARAMS              *MidParamsPtr;
  UINT8                       MaxAudioEndpoints;
  GMMx60D0_STRUCT             GMMx60D0;
  GNB_HANDLE                  *GnbHandle;

  AGESA_TESTPOINT (TpGfxMidInterfaceCZEntry, NULL);
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxMidInterfaceCZ Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  GnbHandle = GnbGetHandle (StdHeader);

  Status =  GfxLocateConfigData (StdHeader, &Gfx);

  ASSERT (Status == AGESA_SUCCESS);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_FATAL) {
    GfxFmDisableController (StdHeader);
  } else {
    if (Gfx->UmaInfo.UmaMode != UMA_NONE) {
      Status = GfxEnableGmmAccessV5 (Gfx);
      ASSERT (Status == AGESA_SUCCESS);
      AGESA_STATUS_UPDATE (Status, AgesaStatus);

      // Power off eDP if no eDP present
      Status = PcieEdpPortPowerCheckCZ (StdHeader);
      ASSERT (Status == AGESA_SUCCESS);
      AGESA_STATUS_UPDATE (Status, AgesaStatus);

      if (Status != AGESA_SUCCESS) {
        // Can not initialize GMM registers going to disable GFX controller
        IDS_HDT_CONSOLE (GNB_TRACE, "  Fail to establish GMM access\n");
        Gfx->UmaInfo.UmaMode = UMA_NONE;
        GfxFmDisableController (StdHeader);
      } else {
        MidParamsPtr = (AMD_MID_PARAMS *) StdHeader;
        MaxAudioEndpoints = MidParamsPtr->GnbMidConfiguration.MaxNumAudioEndpoints;

        Status = GfxGmcInitCZ (Gfx);
        AGESA_STATUS_UPDATE (Status, AgesaStatus);

        Status = GfxSetBootUpVoltageCZ (Gfx);
        AGESA_STATUS_UPDATE (Status, AgesaStatus);

        Status = GfxInitSsidCZ (Gfx);
        AGESA_STATUS_UPDATE (Status, AgesaStatus);

        AudioEPCount = 0;
        Status = GfxIntAudioEPEnumV5 (Gfx, &AudioEPCount);
        AGESA_STATUS_UPDATE (Status, AgesaStatus);

        Status = GfxMakeHSAProcUnitEntryCZ (StdHeader);
        AGESA_STATUS_UPDATE (Status, AgesaStatus);

        if (AudioEPCount > MaxAudioEndpoints) {
          AudioEPCount = MaxAudioEndpoints;
        }

        if ((AudioEPCount > GnbBuildOptionsCZ.GnbCommonOptions.CfgGnbNumDisplayStreamPipes) ||
            (AudioEPCount == 0)) {
          AudioEPCount = GnbBuildOptionsCZ.GnbCommonOptions.CfgGnbNumDisplayStreamPipes;
        }

        AudioEPCount = 7 - AudioEPCount;
        GnbRegisterReadCZ (GnbGetHandle (StdHeader), GMMx60D0_TYPE, GMMx60D0_ADDRESS, &GMMx60D0.Value, 0, StdHeader);
        GMMx60D0.Field.PORT_CONNECTIVITY = AudioEPCount;
        GMMx60D0.Field.PORT_CONNECTIVITY_OVERRIDE_ENABLE = 1;
        GnbRegisterWriteCZ (GnbGetHandle (StdHeader), GMMx60D0_TYPE, GMMx60D0_ADDRESS, &GMMx60D0.Value, 0, StdHeader);
      }
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxMidInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  AGESA_TESTPOINT (TpGfxMidInterfaceCZExit, NULL);
  return  AgesaStatus;
}


