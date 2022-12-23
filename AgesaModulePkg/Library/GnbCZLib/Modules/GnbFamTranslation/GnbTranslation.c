/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific function translation
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312448 $   @e \$Date: 2015-02-06 10:57:34 +0800 (Fri, 06 Feb 2015) $
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
#include  "GnbPcieConfig.h"
#include  "GnbFamServices.h"
#include  "GnbGfxFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbGfx.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBFAMTRANSLATION_GNBTRANSLATION_FILECODE
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
 * Check if IOMMU unit present and enabled
 *
 *
 *
 *
 * @param[in]  GnbHandle       Gnb handle
 * @param[in]  StdHeader       Standard configuration header
 *
 */
BOOLEAN
GnbFmCheckIommuPresent (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  AGESA_STATUS              Status;
  GNB_FAM_IOMMU_SERVICES    *GnbIommuConfigService;
  Status = GnbLibLocateService (GnbIommuService, GnbGetSocketId (GnbHandle), &GnbIommuConfigService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return GnbIommuConfigService->GnbFmCheckIommuPresent (GnbHandle, StdHeader);
  }
  return FALSE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Create IVRS entry
 *
 *
 * @param[in]  GnbHandle       Gnb handle
 * @param[in]  Type            Entry type
 * @param[in]  Ivrs            IVRS table pointer
 * @param[in]  StdHeader       Standard configuration header
 *
 */

AGESA_STATUS
GnbFmCreateIvrsEntry (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       IVRS_BLOCK_TYPE            Type,
  IN       VOID                       *Ivrs,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  AGESA_STATUS              Status;
  GNB_FAM_IOMMU_SERVICES    *GnbIommuConfigService;
  Status = GnbLibLocateService (GnbIommuService, GnbGetSocketId (GnbHandle), &GnbIommuConfigService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return GnbIommuConfigService->GnbFmCreateIvrsEntry (GnbHandle, Type, Ivrs, StdHeader);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Map graphics engine to display path
 *
 *
 *
 *
 * @param[in]   Engine            Engine configuration info
 * @param[out]  DisplayPathList   Display path list
 * @param[in]   Gfx               Pointer to global GFX configuration
 *
 */
AGESA_STATUS
GfxFmMapEngineToDisplayPath (
  IN       PCIe_ENGINE_CONFIG          *Engine,
     OUT   EXT_DISPLAY_PATH            *DisplayPathList,
  IN       GFX_PLATFORM_CONFIG         *Gfx
  )
{
  AGESA_STATUS              Status;
  GFX_FAM_SERVICES          *GfxFamilyService;
  GNB_HANDLE                *GnbHandle;
  GnbHandle = GnbGetHandle (GnbLibGetHeader (Gfx));
  Status = GnbLibLocateService (GfxFamService, GnbGetSocketId (GnbHandle), &GfxFamilyService, GnbLibGetHeader (Gfx));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return GfxFamilyService->GfxMapEngineToDisplayPath (Engine, DisplayPathList, Gfx);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Calculate COF for DFS out of Main PLL
 *
 *
 *
 * @param[in] Did         Did
 * @param[in] StdHeader   Standard Configuration Header
 * @retval                COF in 10khz
 */

UINT32
GfxFmCalculateClock (
  IN       UINT8                      Did,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  AGESA_STATUS              Status;
  GFX_FAM_SERVICES          *GfxFamilyService;
  GNB_HANDLE                *GnbHandle;
  GnbHandle = GnbGetHandle (StdHeader);
  Status = GnbLibLocateService (GfxFamService, GnbGetSocketId (GnbHandle), &GfxFamilyService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return GfxFamilyService->GfxCalculateClock (Did, StdHeader);
  }
  return 200*100;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Disable GFX controller
 *
 *
 *
 * @param[in] StdHeader  Standard configuration header
 */

VOID
GfxFmDisableController (
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  AGESA_STATUS              Status;
  GFX_FAM_SERVICES          *GfxFamilyService;
  GNB_HANDLE                *GnbHandle;
  GnbHandle = GnbGetHandle (StdHeader);
  Status = GnbLibLocateService (GfxFamService, GnbGetSocketId (GnbHandle), &GfxFamilyService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    GfxFamilyService->GfxDisableController (StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Set idle voltage mode for GFX
 *
 *
 * @param[in] Gfx             Pointer to global GFX configuration
 */

BOOLEAN
GfxFmIsVbiosPosted (
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  AGESA_STATUS              Status;
  GFX_FAM_SERVICES          *GfxFamilyService;
  GNB_HANDLE                *GnbHandle;
  GnbHandle = GnbGetHandle (GnbLibGetHeader (Gfx));
  Status = GnbLibLocateService (GfxFamService, GnbGetSocketId (GnbHandle), &GfxFamilyService, GnbLibGetHeader (Gfx));
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return GfxFamilyService->GfxIsVbiosPosted (Gfx);
  }
  return TRUE;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get base SSDT table
 *
 *
 *
 * @param[in]     StdHeader       Standard Configuration Header
 * @retval        pointer to SSTD table
 */
VOID *
GnbFmAlibGetBaseTable (
  IN       AMD_CONFIG_PARAMS             *StdHeader
  )
{
  AGESA_STATUS              Status;
  GNB_FAM_ALIB_SERVICES     *GnbFamilyAlibService;
  GNB_HANDLE                *GnbHandle;
  VOID                      *AlibSsdtTable;

  AlibSsdtTable = NULL;
  GnbHandle = GnbGetHandle (StdHeader);
  Status = GnbLibLocateService (GnbFamAlibService, GnbGetSocketId (GnbHandle), &GnbFamilyAlibService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    AlibSsdtTable = GnbFamilyAlibService->GnbFmAlibGetBaseTable (StdHeader);
  }

  return AlibSsdtTable;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get GnbBuildOptionsCommon Structure
 *
 *
 *
 * @param[in]     StdHeader       Standard Configuration Header
 * @retval        pointer to SSTD table
 */
VOID *
GnbFmGnbBuildOptions (
  IN       AMD_CONFIG_PARAMS             *StdHeader
  )
{
  AGESA_STATUS                    Status;
  GNB_FAM_BUILDOPTIONS_POINTERS   *GnbFamilyBuildOptionsService;
  GNB_HANDLE                      *GnbHandle;
  VOID                            *GnbBuildOptionsPtr;

  GnbBuildOptionsPtr = NULL;
  GnbHandle = GnbGetHandle (StdHeader);
  Status = GnbLibLocateService (GnbFamBuildOptionPointer, GnbGetSocketId (GnbHandle), &GnbFamilyBuildOptionsService, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    GnbBuildOptionsPtr = GnbFamilyBuildOptionsService->GnbFmGetBuildOptions (StdHeader);
  }

  return GnbBuildOptionsPtr;
}



