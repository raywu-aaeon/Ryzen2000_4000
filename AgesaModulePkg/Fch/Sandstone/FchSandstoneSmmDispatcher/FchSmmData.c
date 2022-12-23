/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 SMI Dispatcher Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/******************************************************************************
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
**/
#include "FchSmmDispatcher.h"

FCH_SMM_DISPATCHER_TABLE   FchSmmDispatcherTable[] = {
  {
    FCH_SMI_REG84,
    UsbSmi,
    FchSmmUsbDispatchHandler
  },
  {
    FCH_SMI_REG88,
    BIT12,
    FchSmmUsbDispatchHandler2
  },
  {
    FCH_SMI_REG88,
    Slp_Type,
    FchSmmSxDispatchHandler
  },
  {
    FCH_SMI_REG88,
    SmiCmdPort,
    FchSmmSwDispatchHandler
  },
  {
    FCH_SMI_REG84,
    PwrBtn,
    FchSmmPwrBtnDispatchHandler
  },
  {
    FCH_SMI_REG90,
    IoTrapping0,
    FchSmmIoTrapDispatchHandler
  },
  {
    FCH_SMI_REG90,
    IoTrapping1,
    FchSmmIoTrapDispatchHandler
  },
  {
    FCH_SMI_REG90,
    IoTrapping2,
    FchSmmIoTrapDispatchHandler
  },
  {
    FCH_SMI_REG90,
    IoTrapping3,
    FchSmmIoTrapDispatchHandler
  },
  {
    FCH_SMI_REG90,
    ShortTimer | LongTimer,
    FchSmmPeriodicalDispatchHandler
  },
  {
    FCH_SMI_REG10,
    Gpe,
    FchSmmGpiDispatchHandler
  },
  {
    FCH_SMI_REG84,
    Smbus0 | BIT13 | BIT14,
    FchSmmMiscDispatchHandler
  },
  {
    FCH_SMI_REG80,
    AllGevents,
    FchSmmMiscDispatchHandler
  },
#ifdef FCH_TIMER_TICK_INTERVAL_WA
  {
    FCH_SMI_REG90,
    BIT24,
    FchSmmMiscDispatchHandler
  },
  {
    FCH_SMI_REG8C,
    BIT2,
    FchSmmMiscDispatchHandler
  },
#endif
  {
    FCH_SMI_REG88,
    FchGppSerr0 | FchGppSerr1 | FchGppSerr2 | FchGppSerr3,
    FchSmmMiscDispatchHandler
  },
  {
    FCH_SMI_REG84,
    FchFakeSts0,
    FchSmmMiscDispatchHandler
  },
};
UINT8 NumOfDispatcherTableEntry = sizeof (FchSmmDispatcherTable) / sizeof (FCH_SMM_DISPATCHER_TABLE);

SAVE_B2B_IO       B2bIoList[] = {
  {CFG_ADDR_PORT, SMM_IO_UINT32, 0},
  {0x70,  SMM_IO_UINT8, 0},
  {0x72,  SMM_IO_UINT8, 0},
  {FCH_IOMAP_REGC00, SMM_IO_UINT8, 0},
  {FCH_IOMAP_REGCD0, SMM_IO_UINT8, 0},
  {FCH_IOMAP_REGCD4, SMM_IO_UINT8, 0},
  {FCH_IOMAP_REGCD6, SMM_IO_UINT8, 0},
};
UINT8 NumOfB2bIoListEntry = sizeof (B2bIoList) / sizeof (SAVE_B2B_IO);

SAVE_PCI      SavePciList[] = {
  {0, 0, 0, 0x60, SMM_IO_UINT32, 0},
  {0, 0, 0, 0x94, SMM_IO_UINT32, 0},
  {0, 0, 0, 0xE8, SMM_IO_UINT32, 0},
  {0, 0, 0, 0xE0, SMM_IO_UINT32, 0},
  {0, 0, 0, 0xB8, SMM_IO_UINT32, 0},
};
UINT8 NumOfSavePciListEntry = sizeof (SavePciList) / sizeof (SAVE_PCI);

