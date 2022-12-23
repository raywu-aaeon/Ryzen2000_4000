/* $NoKeywords:$ */
/**
 * @file
 *
 *Fabric watchdog timer library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
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
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "AMD.h"
#include <FabricRegistersZP.h>
#include "Library/IdsLib.h"
#include <Library/FabricWdtLib.h>
#include <Library/FabricRegisterAccLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_FABRICWDTZPLIB_FABRICWDTZPLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
UINT32 DfZpWdtCntSelDecode [] =
{
  31,
  127,
  255,
  511,
  1023,
  2047,
  4095,
  16383
};
#define NumberOfDfWdtCntSel (sizeof (DfZpWdtCntSelDecode) / sizeof (DfZpWdtCntSelDecode[0]))

UINT64 DfZpWdtBaseSelDecode [] =
{
  1310000,
  1280,
  10,
  0
};
#define NumberOfDfWdtBaseSel (sizeof (DfZpWdtBaseSelDecode) / sizeof (DfZpWdtBaseSelDecode[0]))

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  FabricGetCcmWdtInfo
 *
 *  @param[in, out] DfCcmTimeout        DF CCM WDT time in ns
 *
 *  @retval TRUE  WDT is enabled
 *  @retval FALSE WDT is disabled
 *
 */
BOOLEAN
FabricGetCcmWdtInfo (
  IN       UINT64 *DfCcmTimeout
  )
{
  BOOLEAN                DfWdtEn;
  DF_GLBL_CTRL_REGISTER  DfGlblCtrl;

  DfGlblCtrl.Value = FabricRegisterAccRead (0, 0, DF_GLBL_CTRL_FUNC, DF_GLBL_CTRL_REG, FABRIC_REG_ACC_BC);
  ASSERT (DfGlblCtrl.Field.WDTBaseSel < NumberOfDfWdtBaseSel);
  ASSERT (DfGlblCtrl.Field.CCMWDTCntSel < NumberOfDfWdtCntSel);
  if (DfGlblCtrl.Field.WDTBaseSel < 3) {
    DfWdtEn = TRUE;
    *DfCcmTimeout = (UINT64) (DfZpWdtBaseSelDecode[DfGlblCtrl.Field.WDTBaseSel] * DfZpWdtCntSelDecode[DfGlblCtrl.Field.CCMWDTCntSel]);
  } else {
    DfWdtEn = FALSE;
    *DfCcmTimeout = 0;
  }
  return DfWdtEn;
}

