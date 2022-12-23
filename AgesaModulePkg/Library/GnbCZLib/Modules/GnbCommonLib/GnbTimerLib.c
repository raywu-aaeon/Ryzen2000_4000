/* $NoKeywords:$ */
/**
 * @file
 *
 * Various Timer services.
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
#include  "Gnb.h"
#include  "GnbLib.h"
#include  "GnbTimerLib.h"
#include  "GnbFamServices.h"
#include  "GnbPcieConfig.h"
#include  "GnbCommonLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBCOMMONLIB_GNBTIMERLIB_FILECODE




/*----------------------------------------------------------------------------------------*/
/*
 * Stall and save to script table
 *
 *
 *
 * @param[in] Microsecond     Stall time
 * @param[in] StdHeader       Standard configuration header
 */

VOID
GnbLibStallS3Save (
  IN      UINT32              Microsecond,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
//  S3_SAVE_DISPATCH (StdHeader, GnbLibStallS3Script_ID, sizeof (Microsecond), &Microsecond);
  GnbLibStall (Microsecond, StdHeader);
}


/*----------------------------------------------------------------------------------------*/
/*
 * Stall
 *
 *
 *
 * @param[in] Microsecond     Stall time
 * @param[in] StdHeader       Standard configuration header
 */

VOID
GnbLibStall (
  IN      UINT32              Microsecond,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT32 TimeStampStart;
  UINT32 TimeStampDelta;
  UINT32 TimeStampCurrent;

  TimeStampStart = GnbFmTimeStamp (StdHeader);
  do {
    TimeStampCurrent = GnbFmTimeStamp (StdHeader);
    TimeStampDelta = ((TimeStampCurrent > TimeStampStart) ? (TimeStampCurrent - TimeStampStart) : (0xffffffffull - TimeStampStart + TimeStampCurrent));
  } while (TimeStampDelta < Microsecond);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Stall S3 script
 *
 *
 *
 * @param[in]  StdHeader      Standard configuration header
 * @param[in]  ContextLength  Context Length (not used)
 * @param[in]  Context        pointer to UINT32 number of us
 */
VOID
GnbLibStallS3Script (
  IN      AMD_CONFIG_PARAMS    *StdHeader,
  IN      UINT16               ContextLength,
  IN      VOID*                Context
  )
{
  GnbLibStall (* ((UINT32*) Context), StdHeader);
}

/*----------------------------------------------------------------------------------------*/
/**
 * Family specific time stamp function
 *
 *
 * @param[in]  StdHeader       Standard configuration header
 * @retval                     Count
 */
UINT32
GnbFmTimeStamp (
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  AGESA_STATUS               Status;
  GNB_FAM_TS_SERVICES       *GnbFamTsFunc;
  GNB_HANDLE                *GnbHandle;

  GnbHandle = GnbGetHandle (StdHeader);

  Status = GnbLibLocateService (GnbFamTsService, GnbGetSocketId (GnbHandle), &GnbFamTsFunc, StdHeader);
  ASSERT (Status == AGESA_SUCCESS);
  if (Status == AGESA_SUCCESS) {
    return GnbFamTsFunc->GnbFmTimeStamp (StdHeader);
  }
  return 0;
}



