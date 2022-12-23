/* $NoKeywords:$ */
/**
 * @file
 *
 * MemRestoreLib.c
 *
 * Memory Context Save/Restore Support
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
 * @e \$Revision: 329870 $ @e \$Date: 2015-10-29 13:13:29 +0800 (Thu, 29 Oct 2015) $
 *
 **/
/*****************************************************************************
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

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */

#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/MemRestore.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEMRESTORELIB_MEMRESTORELIB_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/**
 *  Set the flag of memory context save/restore to PASS
 *
 *
 **/
VOID
AmdMemRestoreSignOff (
  VOID
  )
{
  UINT8   Value8;
  UINT8   CmosData;

  IDS_HDT_CONSOLE (MAIN_FLOW, "\t[AMD MemRestore] Sign off Mem restore boot\n");

  //Update the CMOS[0xD] bit 0 with flag 0 to indicate S3 completion by memory context restore
  Value8 = CMOS_MEM_RESTORE_OFFSET;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_72, &Value8, NULL);
  Value8 = 0;
  LibAmdIoRead (AccessWidth8, CMOS_PORT_73, &Value8, NULL);
  CmosData = Value8;

  Value8 = CMOS_MEM_RESTORE_OFFSET;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_72, &Value8, NULL);
  Value8 = (CmosData & ~CMOS_BITMAP_MEM_RESTORE_BOOT_FAIL) | CMOS_BITMAP_APOB_SAVED;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_73, &Value8, NULL);
}

/**
 *  Check if memory context save/restore has been performed
 *
 *
 *  @retval CMOS Flag to indicate the failure
 *
 **/
BOOLEAN
AmdMemRestoreGetFailure (
  VOID
  )
{
  UINT8   Value8;

  Value8 = CMOS_MEM_RESTORE_OFFSET;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_72, &Value8, NULL);
  Value8 = 0x0;
  LibAmdIoRead (AccessWidth8, CMOS_PORT_73, &Value8, NULL);

  IDS_HDT_CONSOLE (MAIN_FLOW, "\t[AMD MemRestore] Get Mem Restore Failure = %d\n", Value8 & CMOS_BITMAP_MEM_RESTORE_BOOT_FAIL);

  if ((Value8 & CMOS_BITMAP_MEM_RESTORE_BOOT_FAIL) != 0) {
    return TRUE;
  }

  return FALSE;
}

/**
 *  Discard the current memory context saved in SPI ROM
 *
 *
 **/
VOID
AmdMemRestoreDiscardCurrentMemContext (
  VOID
  )
{
  UINT8   Value8;
  UINT8   CmosData;

  IDS_HDT_CONSOLE (MAIN_FLOW, "\t[AMD MemRestore] Discard current memory context\n");

  Value8 = CMOS_MEM_RESTORE_OFFSET;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_72, &Value8, NULL);
  Value8 = 0;
  LibAmdIoRead (AccessWidth8, CMOS_PORT_73, &Value8, NULL);
  CmosData = Value8;

  Value8 = CMOS_MEM_RESTORE_OFFSET;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_72, &Value8, NULL);
  Value8 = CmosData | CMOS_BITMAP_DISCARD_MEM_CONTEXT;
  LibAmdIoWrite (AccessWidth8, CMOS_PORT_73, &Value8, NULL);
}

