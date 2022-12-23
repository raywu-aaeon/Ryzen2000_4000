/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Ccx Down Core Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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
#include "AGESA.h"
#include "cpuRegisters.h"
#include "Filecode.h"
#include "PiPei.h"
#include "Library/AmdBaseLib.h"
#include "Library/CcxDownCoreLib.h"
#include "Library/PeiServicesTablePointerLib.h"
#include <Library/PciLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_CCXDOWNCOREXVLIB_CCXDOWNCOREXVLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
#define CCX_XV_DOWN_CORE_REG_MASK 0xF

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *  Set down core register
 *
 *
 *  @param[in] CcxDownCoreMode - Down core mode
 *  @param[in] StdHeader      - Config handle for library and services.
 *
 */
VOID
CcxDownCore (
  IN       CCX_DOWN_CORE_MODE CcxDownCoreMode,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT32    DownCoreReg;
  UINT32    LocalPciRegister;
  UINTN     PciAddress;
  EFI_PEI_SERVICES **PeiServices;

  IDS_HDT_CONSOLE (CPU_TRACE, "  Down Core Mode %d\n", CcxDownCoreMode);
  DownCoreReg = 0;
  switch (CcxDownCoreMode) {
  case CCX_DOWN_CORE_AUTO:
    return;
    break;
  case CCX_DOWN_CORE_1_0:
    DownCoreReg = 0xE;
    break;
  case CCX_DOWN_CORE_1_1:
    DownCoreReg = 0xA;
    break;
  case CCX_DOWN_CORE_2_0:
    DownCoreReg = 0xC;
    break;
  default:
    return;
    break;
  }

  PciAddress = MAKE_SBDFO (0, 0, 0x18, FUNC_3, DOWNCORE_CTRL);
  LocalPciRegister = PciRead32 (PciAddress);

  if ((LocalPciRegister & CCX_XV_DOWN_CORE_REG_MASK) == DownCoreReg) {
    return;
  } else {
    PciWrite32 (PciAddress, DownCoreReg);
    IDS_HDT_CONSOLE (CPU_TRACE, "  Set down core register %x, and issue warm reset\n", DownCoreReg);
    PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
    ASSERT (PeiServices != NULL);
    (**PeiServices).ResetSystem (PeiServices);
  }
}

/*---------------------------------------------------------------------------------------
 *                           L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */


