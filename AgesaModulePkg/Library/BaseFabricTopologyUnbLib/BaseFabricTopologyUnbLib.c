/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Topology Base Lib implementation for UNB programs
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
#include <Library/BaseLib.h>
#include <Library/BaseFabricTopologyLib.h>
#include "Filecode.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE  LIBRARY_BASEFABRICTOPOLOGYUNBLIB_BASEFABRICTOPOLOGYUNBLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

UINTN
FabricTopologyGetNumberOfProcessorsPresent (
  VOID
  )
{
  return 1;
}

UINTN
FabricTopologyGetNumberOfSystemDies (
  VOID
  )
{
  return 1;
}

UINTN
FabricTopologyGetNumberOfSystemRootBridges (
  VOID
  )
{
  return 1;
}

UINTN
FabricTopologyGetNumberOfDiesOnSocket (
  IN       UINTN Socket
  )
{
  return 1;
}

UINTN
FabricTopologyGetNumberOfRootBridgesOnSocket (
  IN       UINTN Socket
  )
{
  return 1;
}


UINTN
FabricTopologyGetNumberOfRootBridgesOnDie (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  return 1;
}

UINTN
FabricTopologyGetDieSystemOffset (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  return 0;
}

CONST
AMD_FABRIC_TOPOLOGY_DIE_DEVICE_MAP *
FabricTopologyGetDeviceMapOnDie (
  IN       UINTN Socket,
  IN       UINTN Die
  )
{
  return NULL;
}

UINTN
FabricTopologyGetHostBridgeSystemFabricID (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  return 0;
}

UINTN
FabricTopologyGetHostBridgeBusBase (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  return 0;
}

UINTN
FabricTopologyGetHostBridgeBusLimit (
  IN       UINTN Socket,
  IN       UINTN Die,
  IN       UINTN Index
  )
{
  return 0xFF;
}


