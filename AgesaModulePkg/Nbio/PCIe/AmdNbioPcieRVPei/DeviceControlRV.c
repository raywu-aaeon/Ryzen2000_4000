/* $NoKeywords:$ */
/**
 * @file
 *
 * NBIF Device Control Functions
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 276746 $   @e \$Date: 2014-10-28 12:22:52 -0600 (Mon, 28 Oct 2013) $
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
#include <AMD.h>
#include <Gnb.h>
#include <PiPei.h>
#include <Filecode.h>
#include <GnbRegistersRV.h>
#include <AmdPcieComplex.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVPEI_DEVICECONTROLRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------*/
/**
 * NBIF Device Enable
 *
 *
 *
 * @param[in]  PeiServices   Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  GnbHandle     GNB_HANDLE
 */

VOID
NbioEnableNbifDevice (
  IN        GNB_HANDLE         *GnbHandle,
  IN        UINT8              DeviceType,
  IN        UINT8              StartLane
  )
{
  IDS_HDT_CONSOLE(GNB_TRACE, "NbioEnableNbifDevice (DeviceType=%x)\n", DeviceType);

  switch (DeviceType) {
  case DxioSATAEngine:

    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF1_SATA_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                     NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                     (UINT32) ~(1 << 8),
                     (1 << 8),
                     0
                     );
    break;

  case DxioEthernetEngine:
    switch (StartLane) {
    case 0:
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       NBIF1_XGBE0_STRAP0_ADDRESS,
                       (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                       (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                       NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                       (UINT32) ~(1 << 9),
                       (1 << 9),
                       0
                       );
      break;
    case 1:
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       NBIF1_XGBE1_STRAP0_ADDRESS,
                       (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                       (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                       NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                       (UINT32) ~(1 << 10),
                       (1 << 10),
                       0
                       );
      break;
    default:
      // XGBE is only supported on lanes 1:0, any other is invalid
      ASSERT (FALSE);
    }
    break;

  case DxioHDaudioEngine:
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_HDAUDIO_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                     NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                     (UINT32) ~(1 << 6),
                     (1 << 6),
                     0
                     );
    break;
  case DxioACPEngine:
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_ACP_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    break;
  case DxioMP2Engine:
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_MP2_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    break;
  }
  return;
}

/*----------------------------------------------------------------------------------------*/
/**
 * NBIF Device Disable
 *
 *
 *
 * @param[in]  PeiServices   Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  GnbHandle     GNB_HANDLE
 */

VOID
NbioDisableNbifDevice (
  IN        GNB_HANDLE         *GnbHandle,
  IN        UINT8              DeviceType,
  IN        UINT8              StartLane
  )
{
  IDS_HDT_CONSOLE(GNB_TRACE, "NbioDisableNbifDevice (DeviceType=%x)\n", DeviceType);

  switch (DeviceType) {
  case DxioSATAEngine:

    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF1_SATA_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                     NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                     (UINT32) ~(1 << 8),
                     (0 << 8),
                     0
                     );
    break;

  case DxioEthernetEngine:
    switch (StartLane) {
    case 4:
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       NBIF1_XGBE0_STRAP0_ADDRESS,
                       (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                       (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                       NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                       (UINT32) ~(1 << 9),
                       (0 << 9),
                       0
                       );
      break;
    case 5:
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       NBIF1_XGBE1_STRAP0_ADDRESS,
                       (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                       (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                       0
                       );
      NbioRegisterRMW (GnbHandle,
                       NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                       NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                       (UINT32) ~(1 << 10),
                       (0 << 10),
                       0
                       );
      break;
    default:
      // XGBE is only supported on lanes 7:4, any other is invalid
      ASSERT (FALSE);
    }
    break;

  case DxioHDaudioEngine:
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_HDAUDIO_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     NBIFMISC0_INTR_LINE_ENABLE_TYPE,
                     NBIFMISC0_INTR_LINE_ENABLE_ADDRESS,
                     (UINT32) ~(1 << 6),
                     (0 << 6),
                     0
                     );
    break;
  case DxioACPEngine:
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_ACP_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    break;
  case DxioMP2Engine:
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_MP2_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    break;
  }
  return;
}


