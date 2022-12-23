/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific GFX library
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309572 $   @e \$Date: 2014-12-17 16:39:45 +0800 (Wed, 17 Dec 2014) $
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
#include  "GnbPcieConfig.h"
#include  "GnbGfx.h"
#include  "GfxLibCZ.h"
#include  "GnbCommonLib.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "Library/AmdHeapLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GFXLIBCZ_FILECODE
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
 * Disable GFX controller
 *
 *
 *
 * @param[in] StdHeader  Standard configuration header
 */

VOID
GfxDisableControllerCZ (
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  GnbLibPciRMW (
    MAKE_SBDFO (0, 0, 0, 0,D0F0x7C_ADDRESS),
    AccessS3SaveWidth32,
    0xffffffff,
    1 << D0F0x7C_ForceIntGfxDisable_OFFSET,
    StdHeader
    );
}

/*----------------------------------------------------------------------------------------*/
/**
 * Get system PLL COF
 *
 *
 *
 * @param[in] StdHeader  Standard configuration header
 * @retval    System PLL COF
 */
UINT32
GfxLibGetSystemPllCofCZ (
  IN       AMD_CONFIG_PARAMS      *StdHeader
  )
{
  D0F0xBC_xC001400C_STRUCT  D0F0xBC_xC001400C;
  GnbRegisterReadCZ (GnbGetHandle (StdHeader), D0F0xBC_xC001400C_TYPE,  D0F0xBC_xC001400C_ADDRESS, &D0F0xBC_xC001400C.Value, 0, StdHeader);
  return 100 * (D0F0xBC_xC001400C.Field.MainPllOpFreqIdStartup + 0x10);

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
GfxCalculateClockCZ (
  IN       UINT8                       Did,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  UINT32  Divider;
  UINT32  SystemPllCof;
  SystemPllCof = GfxLibGetSystemPllCofCZ (StdHeader) * 100;
  if (Did >= 8 && Did <= 0x3F) {
    Divider = Did * 25;
  } else if (Did > 0x3F && Did <= 0x5F) {
    Divider = (Did - 64) * 50 + 1600;
  } else if (Did > 0x5F && Did <= 0x7E) {
    Divider = (Did - 96) * 100 + 3200;
  } else if (Did == 0x7f) {
    Divider = 128 * 100;
  } else {
///@todo    ASSERT (FALSE);
    return 200 * 100;
  }
  ASSERT (Divider != 0);
  return (((SystemPllCof * 100) + (Divider - 1)) / Divider);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Check if Video BIOS has posted or not
 *
 *
 * @param[in] Gfx             Pointer to global GFX configuration
 */

BOOLEAN
GfxIsVbiosPostedCZ (
  IN      GFX_PLATFORM_CONFIG   *Gfx
  )
{
  GMMx1740_STRUCT GMMx1740;
  GnbRegisterReadCZ (GnbGetHandle (GnbLibGetHeader (Gfx)), GMMx1740_TYPE, GMMx1740_ADDRESS, &GMMx1740.Value, 0, GnbLibGetHeader (Gfx));

  return ((GMMx1740.Value & ATOM_S7_ASIC_INIT_COMPLETEb1) != 0) ? TRUE : FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 * This function will add HSA Processing Unit entry for Gnb.
 *
 *    @param[in, out] StdHeader            Standard Head Pointer
 *    @retval         AGESA_ERROR          Crat table entry is not created successfully
 *    @retval         AGESA_SUCCESS        Crat table entry is created successfully
 */
AGESA_STATUS
GfxMakeHSAProcUnitEntryCZ (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  CRAT_HSA_PROCESSING_UNIT   *HsaProcUnit;

  IDS_HDT_CONSOLE (GNB_TRACE, "Make HSA Proc entry\n");

  HsaProcUnit = (CRAT_HSA_PROCESSING_UNIT *) GnbAllocateHeapBuffer (AMD_GNB_CRAT_HSA_TABLE_HANDLE, sizeof (CRAT_HSA_PROCESSING_UNIT), StdHeader);
  if (HsaProcUnit == NULL) {
    return AGESA_ERROR;
  }
  HsaProcUnit->Length = 40;
  HsaProcUnit->Flags.Enabled = 1;
  HsaProcUnit->Flags.GpuPresent = 1;
  HsaProcUnit->Flags.CpuPresent = 0;
  HsaProcUnit->Flags.IommuPresent = 1;
  HsaProcUnit->ProcessorIdLow = 0x80000000;
  HsaProcUnit->NumSIMDPerCU = 4;
  HsaProcUnit->NumSIMDCores = GPU__GC__NUM_SE * GPU__GC__NUM_SH_PER_SE * GPU__GC__NUM_CU_PER_SH * (HsaProcUnit->NumSIMDPerCU);
  HsaProcUnit->MaxWavesSIMD = 40;
  HsaProcUnit->LDSSizeInKB = 64;
  HsaProcUnit->WaveFrontSize = 64;
  HsaProcUnit->NumBanks = GPU__GC__NUM_SE;
  HsaProcUnit->NumArrays = GPU__GC__NUM_SH_PER_SE;
  HsaProcUnit->NumCUPerArray = GPU__GC__NUM_SH_PER_SE * GPU__GC__NUM_CU_PER_SH;
  HsaProcUnit->MaxSlotsScratchCU = 32;

  IDS_HDT_CONSOLE (GNB_TRACE, "Make HSA Proc exit\n");
  return AGESA_SUCCESS;
}

