/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to access MMIO registers.
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
#include  "Porting.h"
#include  "AMD.h"
#include  "Library/AmdBaseLib.h"
#include  "Library/GnbMemAccLib.h"
#include  <Library/AmdS3SaveLib.h>
#include  "Filecode.h"
#define FILECODE LIBRARY_GNBMEMACCLIB_GNBMEMACCLIB_FILECODE
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
 * Write Memory/MMIO registers
 *
 *
 *
 * @param[in] Address         Physical Address
 * @param[in] Width           Access width
 * @param[in] Value           Pointer to value
 * @param[in] StdHeader       Standard configuration header
 */

VOID
GnbLibMemWrite (
  IN      UINT64        Address,
  IN      ACCESS_WIDTH  Width,
  IN      VOID          *Value,
  IN      VOID          *StdHeader
  )
{
  if (Width >= AccessS3SaveWidth8) {
    if (Width == AccessS3SaveWidth64) {
      AmdS3SaveScriptMemWrite (AccessS3SaveWidth32 - 0x80, Address, Value);
      AmdS3SaveScriptMemWrite (AccessS3SaveWidth32 - 0x80, Address + 4, (VOID *) ((UINTN)Value + 4));
    } else {
      AmdS3SaveScriptMemWrite (Width - 0x80, Address, Value);
    }
  }
  if ((Width == AccessWidth64) || (Width == AccessS3SaveWidth64)) {
    LibAmdMemWrite (AccessWidth32, Address, Value, StdHeader);
    LibAmdMemWrite (AccessWidth32, Address + 4, (VOID *) ((UINTN)Value + 4), StdHeader);
  } else {
    LibAmdMemWrite (Width, Address, Value, StdHeader);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Read Memory/MMIO registers
 *
 *
 *
 * @param[in]   Address         Physical Address
 * @param[in]   Width           Access width
 * @param[out]  Value           Pointer to value
 * @param[in]   StdHeader       Standard configuration header
 */

VOID
GnbLibMemRead (
  IN       UINT64       Address,
  IN       ACCESS_WIDTH Width,
     OUT   VOID         *Value,
  IN       VOID         *StdHeader
  )
{
  if (Width == AccessWidth64) {
    LibAmdMemRead (AccessWidth32, Address, Value, StdHeader);
    LibAmdMemRead (AccessWidth32, Address + 4, (VOID *) ((UINTN)Value + 4), StdHeader);
  } else {
    LibAmdMemRead (Width, Address, Value, StdHeader);
  }
}

