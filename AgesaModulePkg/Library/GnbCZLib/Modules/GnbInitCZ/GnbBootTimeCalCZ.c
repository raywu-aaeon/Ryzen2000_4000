/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB boot time calibration.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 324268 $   @e \$Date: 2015-08-14 14:18:33 +0800 (Fri, 14 Aug 2015) $
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
#include  "GnbFuseTable.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbCommonLib.h"
#include  "GnbRegisterAccCZ.h"
#include  "GnbRegistersCZ.h"
#include  "GnbFamServices.h"
#include  "OptionGnb.h"
#include  "GnbSmuInitLibV8.h"
#include  "OptionGnb.h"
#include  "Library/AmdHeapLib.h"
#include  <Library/BaseLib.h>
#include  <Library/CcxBtcLib.h>

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBINITCZ_GNBBOOTTIMECALCZ_FILECODE

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
// todo:_BTC extern CPU_FAMILY_SUPPORT_TABLE           BtcFamilyServiceTable;

extern F15CZ_VID_WA_PSTATE_ADJ  F15CzVidWorkaroundPstateAdjustmentTable[];

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define   BTC_START                1       ///< Start message
#define   FIRST_CAL_PGM            2       ///< First test
#define   NUMBER_OF_CAL_PGMS       3       ///< Number of tests

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
 * Read back and set SMU parameters for GBV
 *
 *
 *
 * @param[in]  GnbHandle  GNB_HANDLE
 * @param[in]  AccessFlags         Flag for S3
 * @param[in]  StdHeader  Standard configuration header
 */

VOID
STATIC
BtcGetSetGbvCZ (
  IN      GNB_HANDLE          *GnbHandle,
  IN      UINT32              AccessFlags,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  DEV_OBJECT             DevObject;
  UINT32                 SmuArg[6];

  GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);

  //BTC voltage guard-band for P-State 4 to P-State 7
  GnbSmuServiceRequestV8 (
     &DevObject,
     SMC_MSG_GetBtcGbvHi,
     SmuArg,
     0
     );
  if ((AccessFlags & GNB_REG_ACC_FLAG_S3SAVE) != 0) {
    SmuArg[4] = 0;
    SmuArg[5] = 0;
    GnbSmuServiceRequestV8 (
       &DevObject,
       SMC_MSG_SetBtcGbvHi,
       SmuArg,
       GNB_REG_ACC_FLAG_S3SAVE
       );
  }
  //BTC voltage guard-band for P-State 0 to P-State 3
  GnbSmuServiceRequestV8 (
     &DevObject,
     SMC_MSG_GetBtcGbvLo,
     SmuArg,
     0
     );
  if ((AccessFlags & GNB_REG_ACC_FLAG_S3SAVE) != 0) {
    SmuArg[4] = 0;
    SmuArg[5] = 0;
    GnbSmuServiceRequestV8 (
       &DevObject,
       SMC_MSG_SetBtcGbvLo,
       SmuArg,
       GNB_REG_ACC_FLAG_S3SAVE
       );
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * PCIe Boot Time Cal Interface
 *
 *
 *
 * @param[in]  StdHeader  Standard configuration header
 * @retval     AGESA_STATUS
 */

AGESA_STATUS
GnbBootTimeCalInterfaceCZ (
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  AGESA_STATUS           AgesaStatus;
  GNB_HANDLE             *GnbHandle;
  DEV_OBJECT             DevObject;
  UINT8                  CalPgmIndex;
  UINT8                  NumberOfCalPgms;
  UINT32                 SmuArg[6];
  UINT32                 D0F0xBC_xC0016078;
  GNB_BUILD_OPTIONS_CZ  *GnbBuildOptionData;
  UINT64                MsrData;
  UINT32                i;

  AgesaStatus = AGESA_SUCCESS;
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbBootTimeCalInterfaceCZ Enter\n");

  GnbBuildOptionData = GnbLocateHeapBuffer (AMD_GNB_BUILD_OPTIONS_HANDLE, StdHeader);
  ASSERT (GnbBuildOptionData != NULL);


  GnbHandle = GnbGetHandle (StdHeader);

  if (IsF15CzVidAdjustmentRequired (StdHeader)) {

    for (i = 0; F15CzVidWorkaroundPstateAdjustmentTable[i].Pstate != 0xFF; i++) {
      GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);
      MsrData = AsmReadMsr64 (0xC0010064 + F15CzVidWorkaroundPstateAdjustmentTable[i].Pstate);
      SmuArg[0] = (UINT32) (((MsrData >> 9) & 0xFF) | (F15CzVidWorkaroundPstateAdjustmentTable[i].Pstate << 16));
      GnbSmuServiceRequestV8 (
         &DevObject,
         SMC_MSG_SetCpuVid,
         SmuArg,
         GNB_REG_ACC_FLAG_S3SAVE
         );
    }
  }

  GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);
  if (!GnbBuildOptionData->GnbCommonOptions.CfgSmuMessageEnable) {
    IDS_HDT_CONSOLE (GNB_TRACE, "BIOS FORCE SKIP SMU SERVICE!!\n");
    return AgesaStatus;
  }

  GnbHandle = GnbGetHandle (StdHeader);
  GnbSmuServiceCommonInitArgumentsV8 (GnbHandle, StdHeader, &DevObject, SmuArg);

  NumberOfCalPgms = NUMBER_OF_CAL_PGMS;

  // Read fuse to see if this processor supports boot time calibration
  GnbRegisterReadCZ (GnbGetHandle (StdHeader), TYPE_D0F0xBC, 0xC0016078,
                     &D0F0xBC_xC0016078, 0, StdHeader);

  if ((GnbBuildOptionData->CfgBTCEnable == TRUE) && (((D0F0xBC_xC0016078 & BIT29) == BIT29) || ((D0F0xBC_xC0016078 & BIT28) == BIT28))) {

    // Step 1. Set the Pstate on all cores to Pmin(P7)
    AgesaStatus = CcxBtcBefore (StdHeader);
    if (AgesaStatus == AGESA_SUCCESS) {
      // Step 2. Send BTC_START. This initializes code and hardware (SPMI, PSMs, etc).
      // Step 3. Wait for SMU completion, SMU sets the register which is polled.
      SmuArg[0] = BTC_START;
      GnbSmuServiceRequestV8 (
         &DevObject,
         SMC_MSG_BC,
         SmuArg,
         0
         );

      // Step 4. Execute all the tests.
      for (CalPgmIndex = 0; CalPgmIndex < NumberOfCalPgms; CalPgmIndex++) {
        // Step 4.1 Execute calibration pgm.X
        // Don't run workload for now
        //BtcFamilyServices->RunBtc (BtcFamilyServices, CalPgmIndex, StdHeader);

        // Step 4.2 Send test number to SMU.
        // Step 4.3. Wait for SMU completion
        IDS_HDT_CONSOLE (GNB_TRACE, "Starting test number %d\n", FIRST_CAL_PGM + CalPgmIndex);
        SmuArg[0] = FIRST_CAL_PGM + CalPgmIndex;
        GnbSmuServiceRequestV8 (
           &DevObject,
           SMC_MSG_BC,
           SmuArg,
           0
           );
      }

      // Step 5. Restore Pstate on all cores.
      CcxBtcAfter (StdHeader);

    }
  }

  // Both save and restore needs to happen even if BTC fuses are disabled
  // Step 6. Get GBV and set back for S3.
  // need to record the BTCGBV vector after the shadowPstates
  // This is because shadowPstates modifies the BTCGBV data structure.
  BtcGetSetGbvCZ (GnbHandle, GNB_REG_ACC_FLAG_S3SAVE, StdHeader);

  // Step 7. Update Shadow VID tables
  // Call SMU service instead of CPU routine
  if (GnbBuildOptionData->CfgShadowPstates == TRUE) {
    SmuArg[0] = 0;
    GnbSmuServiceRequestV8 (
       &DevObject,
       SMC_MSG_ApplyShadowPstates,
       SmuArg,
       GNB_REG_ACC_FLAG_S3SAVE
       );
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbBootTimeCalInterfaceCZ Exit [0x%x]\n", AgesaStatus);
  return  AgesaStatus;
}

