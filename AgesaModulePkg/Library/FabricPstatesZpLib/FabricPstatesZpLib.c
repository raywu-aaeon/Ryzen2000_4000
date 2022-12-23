/* $NoKeywords:$ */
/**
 * @file
 *
 * Base Fabric Pstates Lib implementation for DF1.0
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
#include <Library/FabricPstatesLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_FABRICPSTATESZPLIB_FABRICPSTATESZPLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

BOOLEAN
FabricPstatesAreAllSocketsInAUnifiedDomain (
  VOID
  )
{
  return TRUE;
}

BOOLEAN
FabricPstatesAreAllDieOnSocketInAUnifiedDomain (
  IN       UINTN  Socket
  )
{
  return TRUE;
}

BOOLEAN
FabricPstatesIsSwitchingEnabledOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  // Read F5x174[NbPstateDis]
  return TRUE;
}

UINTN
FabricPstatesGetNumberOfPstatesOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  // Read F5
  return 4;
}

VOID
FabricPstatesGetPstateInfo (
  IN       UINTN               Socket,
  IN       UINTN               Die,
  IN       UINTN               Pstate,
     OUT   FABRIC_PSTATE_INFO  *Info
  )
{
  Info->Frequency = Pstate * 800;
  Info->Voltage = 1550 - (Pstate * 200);
  Info->Power = 400 * Pstate;
  Info->AssociatedMstate = Pstate != 3 ? 0 : 1;
}

BOOLEAN
FabricPstatesForcePstateOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die,
  IN       UINTN  Pstate
  )
{
  // Check for previous force and save pstatectrl if none?

  // Check SmuCfgLock and return FALSE if appropriate

  // Force
  return TRUE;
}

VOID
FabricPstatesReleaseForceOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  // Restore pstatectrl
}

UINTN
FabricPstatesGetCurrentPstateOnDie (
  IN       UINTN  Socket,
  IN       UINTN  Die
  )
{
  // Check F5
  return 0;
}

