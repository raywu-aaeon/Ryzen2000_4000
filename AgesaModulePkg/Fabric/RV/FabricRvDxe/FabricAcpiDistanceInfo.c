/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Fabric ACPI distance information for SLIT/CDIT.
 *
 * This funtion collect distance information for SLIT/CDIT.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ****************************************************************************
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
#include "Porting.h"
#include "AMD.h"
#include <Library/AmdBaseLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include <FabricRegistersRV.h>
#include <Library/FabricRegisterAccLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/FabricNumaServicesProtocol.h>
#include <Filecode.h>


#define FILECODE FABRIC_RV_FABRICRVDXE_FABRICACPIDISTANCEINFO_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
#define DISTANCE_TO_SELF  10
#define XGMI_PENALTY      12
#define GMI_PENALTY        6

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

EFI_STATUS
EFIAPI
FabricGetDistanceInfo (
  IN OUT   UINT8                                  *Distance,
  IN       UINT32                                  DomainCount,
  IN       DOMAIN_INFO                            *DomainInfo
  )
{
  UINT32                 i;
  UINT32                 j;
  UINT32                 DieIntlvIndex;
  CAKE_SYS_CFG_REGISTER  CakeSysCfg;

  for (i = 0; i < DomainCount; i++) {
    ASSERT (DomainInfo[i].Type < MaxDomainType);
    for (j = 0; j < DomainCount; j++) {
      if (i == j) {
        // Case 1: distance to self
        *Distance = DISTANCE_TO_SELF;
      } else {
        ASSERT (DomainInfo[i].Type != SocketIntlv);
        ASSERT (DomainInfo[j].Type != SocketIntlv);
        ASSERT (DomainInfo[j].Type < MaxDomainType);
        if ((DomainInfo[i].Type == DieIntlv) && (DomainInfo[j].Type == DieIntlv)) {
          // Case 2: die interleaving is enabled on both sockets, the normalized penalty
          //         is 1 xGMI hop as local is slower due to 3/4 chance of local hop
          *Distance = DISTANCE_TO_SELF + XGMI_PENALTY;
        } else if ((DomainInfo[i].Type == DieIntlv) || (DomainInfo[j].Type == DieIntlv)) {
          // Case 3: die interleaving is enabled on one of the two sockets, 1 xGMI + 3/4 GMI
          DieIntlvIndex = (DomainInfo[i].Type == DieIntlv) ? i : j;
          *Distance = (UINT8) (((DomainInfo[DieIntlvIndex].Intlv.Die.DieCount - 1) * GMI_PENALTY) / DomainInfo[DieIntlvIndex].Intlv.Die.DieCount);
          if ((((DomainInfo[DieIntlvIndex].Intlv.Die.DieCount - 1) * GMI_PENALTY) % DomainInfo[DieIntlvIndex].Intlv.Die.DieCount) >= ((DomainInfo[DieIntlvIndex].Intlv.Die.DieCount + 1) >> 1)) {
            *Distance = *Distance + 1;
          }
          *Distance += (DISTANCE_TO_SELF + XGMI_PENALTY);
        } else {
          // Die interleaving is disabled on both domains
          ASSERT (DomainInfo[i].Type == NoIntlv);
          ASSERT (DomainInfo[j].Type == NoIntlv);
          if (DomainInfo[i].Intlv.None.Socket == DomainInfo[j].Intlv.None.Socket) {
            // Case 4: Domains are on the same socket, 1 GMI
            *Distance = DISTANCE_TO_SELF + GMI_PENALTY;
          } else {
            CakeSysCfg.Value = FabricRegisterAccRead (DomainInfo[i].Intlv.None.Socket, DomainInfo[i].Intlv.None.Die, CAKE_SYS_CFG_FUNC, CAKE_SYS_CFG_REG, FABRIC_REG_ACC_BC);
            if (DomainInfo[j].Intlv.None.Die == CakeSysCfg.Field.ConnLocalXgmiDieId) {
              // Case 5: distance to die on other socket connected by xGMI
              *Distance = DISTANCE_TO_SELF + XGMI_PENALTY;
            } else {
              // Case 6: distance to die on other socket not directly connected by xGMI
              *Distance = DISTANCE_TO_SELF + XGMI_PENALTY + GMI_PENALTY;
            }
          }
        }
      }
      Distance++;
    }
  }

  return EFI_SUCCESS;
}


