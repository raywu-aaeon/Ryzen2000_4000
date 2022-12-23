/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB-SB link procedure
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
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "GnbPcieInitLib.h"
#include  "GnbSbLib.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBSBLIB_GNBSBPCIE_FILECODE
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
 * Enable/Disable ASPM on GNB-SB link
 *
 *
 *
 * @param[in]  Engine          Pointer to engine config descriptor
 * @param[in]  Pcie            Pointer to global PCIe configuration
 *
 */

AGESA_STATUS
SbPcieLinkAspmControl (
  IN      PCIe_ENGINE_CONFIG    *Engine,
  IN      PCIe_PLATFORM_CONFIG  *Pcie
  )
{
  AGESA_STATUS    Status;
  PCIE_ASPM_TYPE  Aspm;

  Aspm = Engine->Type.Port.PortData.LinkAspm;

  Status = SbPcieInitAspm (Aspm, GnbLibGetHeader (Pcie));
  if (Status != AGESA_SUCCESS) {
    return AGESA_UNSUPPORTED;
  }

  PcieAspmEnableOnFunction (Engine->Type.Port.Address, Aspm, GnbLibGetHeader (Pcie));
  return  AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Init SB ASPM.
 * Enable ASPM states on SB
 *
 *
 * @param[in] Aspm       ASPM bitmap.
 * @param[in] StdHeader  Standard configuration header
 */
/*----------------------------------------------------------------------------------------*/

AGESA_STATUS
SbPcieInitAspm (
  IN      PCIE_ASPM_TYPE       Aspm,
  IN      AMD_CONFIG_PARAMS   *StdHeader
  )
{
  UINT16        AlinkPort;

  AlinkPort = SbGetAlinkIoAddress (StdHeader);
  ASSERT (AlinkPort != 0);
  if (AlinkPort == 0) {
    return AGESA_UNSUPPORTED;
  }
  GnbLibIoRMW (AlinkPort, AccessS3SaveWidth32, 0x0, 0x40000038, StdHeader);
  GnbLibIoRMW (AlinkPort + 4, AccessS3SaveWidth32, 0x0, 0xA0, StdHeader);
  GnbLibIoRMW (AlinkPort, AccessS3SaveWidth32, 0x0, 0x4000003c, StdHeader);
  GnbLibIoRMW (AlinkPort + 4, AccessS3SaveWidth32, 0xffff00ff, 0x6900, StdHeader);
  GnbLibIoRMW (AlinkPort, AccessS3SaveWidth32, 0x0, 0x80000068, StdHeader);
  GnbLibIoRMW (AlinkPort + 4, AccessS3SaveWidth32, 0xfffffffc, Aspm, StdHeader);
  return AGESA_SUCCESS;
}



