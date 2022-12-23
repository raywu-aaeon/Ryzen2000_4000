/* $NoKeywords:$ */
/**
 * @file
 *
 * Interface to initialize Graphics Controller at mid POST
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309352 $   @e \$Date: 2014-12-15 09:11:26 +0800 (Mon, 15 Dec 2014) $
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
#include  "GfxConfigLib.h"
#include  "GnbCommonLib.h"
#include  "GnbGfxFamServices.h"
#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBSVIEW_GNBSVIEW_FILECODE
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
AGESA_STATUS
GfxInitSview (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );


/*----------------------------------------------------------------------------------------*/
/**
 * Copy memory content to FB
 *
 *
 * @param[in] Source       Pointer to source
 * @param[in] FbOffset     FB offset
 * @param[in] Length       The length to copy
 * @param[in] Gfx          Pointer to global GFX configuration
 *
 */
VOID
GfxLibCopyMemToFb (
  IN     VOID                   *Source,
  IN     UINT32                  FbOffset,
  IN     UINT32                  Length,
  IN     GFX_PLATFORM_CONFIG    *Gfx
  )
{
  UINT32 GMMx00;
  UINT32 GMMx04;
  UINT32        Index;
  for (Index = 0; Index < Length; Index = Index + 4 ) {
    GMMx00 = 0x80000000 | (FbOffset + Index);
    GMMx04 = *(UINT32*) ((UINT8*)Source + Index);
    GnbLibMemWrite (Gfx->GmmBase, AccessWidth32, &GMMx00, GnbLibGetHeader (Gfx));
    GnbLibMemWrite (Gfx->GmmBase + 4, AccessWidth32, &GMMx04, GnbLibGetHeader (Gfx));
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init SVIEW configuration
 *
 *
 *
 * @param[in] StdHeader       Standard configuration header
 * @retval    AGESA_STATUS
 */

AGESA_STATUS
GfxInitSview (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  )
{
  AGESA_STATUS          Status;
  AGESA_STATUS          AgesaStatus;
  GFX_PLATFORM_CONFIG   *Gfx;
  UINT32                Value32;
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxInitSview Enter\n");
  AgesaStatus = AGESA_SUCCESS;
  Status =  GfxLocateConfigData (StdHeader, &Gfx);
  AGESA_STATUS_UPDATE (Status, AgesaStatus);
  if (Status == AGESA_SUCCESS) {
    if (GnbLibPciIsDevicePresent (MAKE_SBDFO (0, 0, 1, 0, 0), StdHeader)) {
      if (!GfxFmIsVbiosPosted (Gfx)) {
        GFX_VBIOS_IMAGE_INFO  VbiosImageInfo;
        LibAmdMemCopy (&VbiosImageInfo.StdHeader, StdHeader, sizeof (AMD_CONFIG_PARAMS), StdHeader);
        VbiosImageInfo.ImagePtr = NULL;
        VbiosImageInfo.GfxPciAddress = Gfx->GfxPciAddress;
        VbiosImageInfo.Flags = GFX_VBIOS_IMAGE_FLAG_SPECIAL_POST;
        GnbLibPciRead (Gfx->GfxPciAddress.AddressValue | 0x4, AccessWidth32, &Value32, StdHeader);
        GnbLibPciRMW (Gfx->GfxPciAddress.AddressValue | 0x4, AccessWidth8, 0xff, BIT1 | BIT2 | BIT0, StdHeader);
        Status = AgesaGetVbiosImage (0, &VbiosImageInfo);
        if (Status == AGESA_SUCCESS && VbiosImageInfo.ImagePtr != NULL) {
          GfxLibCopyMemToFb (VbiosImageInfo.ImagePtr, 0, (*((UINT8*) VbiosImageInfo.ImagePtr + 2)) << 9, Gfx);
        }
        GnbLibPciWrite (Gfx->GfxPciAddress.AddressValue | 0x4, AccessWidth32, &Value32, StdHeader);
      }
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GfxInitSview Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}

