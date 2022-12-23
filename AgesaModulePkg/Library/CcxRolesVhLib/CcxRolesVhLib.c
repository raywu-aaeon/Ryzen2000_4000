/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Roles Library - VH
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
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
#include "AMD.h"
#include "Filecode.h"
#include <Library/CcxBaseX86Lib.h>

#define FILECODE LIBRARY_CCXROLESVHLIB_CCXROLESVHLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

 /*----------------------------------------------------------------------------------------
  *                          E X P O R T E D    F U N C T I O N S
  *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 *  Is this the BSP core?
 *
 *  @param[in,out]   StdHeader        Header for library and services
 *
 *  @retval          TRUE             Is BSP core
 *  @retval          FALSE            Is not BSP Core
 *
 */
BOOLEAN
CcxIsBsp (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT64   ApicBar;

  ApicBar = AsmReadMsr64 (0x0000001B);
  return (BOOLEAN) ((ApicBar & BIT8) != 0);
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Is the current core a primary core of it's compute unit?
 *
 *  @param[in]  StdHeader   Config handle for library and services.
 *
 *  @retval        TRUE  Is Primary Core
 *  @retval        FALSE Is not Primary Core
 *
 */
BOOLEAN
CcxIsComputeUnitPrimary (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  ThreadsPerCore;

  ThreadsPerCore = (UINT32) CcxGetThreadsPerCore ();
  if (ThreadsPerCore == 0) {
    ThreadsPerCore = 1;
  }
  return (BOOLEAN) ((CcxGetInitialApicID (StdHeader) % ThreadsPerCore) == 0);
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Is the current core a primary core of its complex?
 *
 *  @param[in]  StdHeader   Config handle for library and services.
 *
 *  @retval        TRUE  Is Primary Core
 *  @retval        FALSE Is not Primary Core
 *
 */
BOOLEAN
CcxIsComplexPrimary (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  ComplexMask;

  ComplexMask = (CcxGetThreadsPerCore () == 1) ? 0x00000003 : 0x00000007;
  return (BOOLEAN) ((CcxGetInitialApicID (StdHeader) & ComplexMask) == 0);
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Is the current core a primary core of it's node?
 *
 *  @param[in]  StdHeader   Config handle for library and services.
 *
 *  @retval        TRUE  Is Primary Core
 *  @retval        FALSE Is not Primary Core
 *
 */
BOOLEAN
CcxIsDiePrimary (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  DieMask;

  DieMask = (CcxGetThreadsPerCore () == 1) ? 0x00000007 : 0x0000000F;
  return (BOOLEAN) ((CcxGetInitialApicID (StdHeader) & DieMask) == 0);
}

/*---------------------------------------------------------------------------------------*/
/**
 *  Is the current core a primary core of it's node?
 *
 *  @param[in]  StdHeader   Config handle for library and services.
 *
 *  @retval        TRUE  Is Primary Core
 *  @retval        FALSE Is not Primary Core
 *
 */
BOOLEAN
CcxIsSocketPrimary (
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  SocketMask;

  SocketMask = (CcxGetThreadsPerCore () == 1) ? 0x0000003F : 0x0000007F;
  return (BOOLEAN) ((CcxGetInitialApicID (StdHeader) & SocketMask) == 0);
}

