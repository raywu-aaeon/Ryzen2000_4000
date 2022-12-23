/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to access various CPU registers.
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
#include  <Porting.h>
#include  <AMD.h>
#include  <Filecode.h>
#include  <Library/GnbPciAccLib.h>
#include  <Library/GnbCpuAccLib.h>

#define FILECODE LIBRARY_GNBCPUACCLIB_GNBCPUACCLIB_FILECODE
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
 * Read CPU (DCT) indirect registers
 *
 *
 *
 * @param[in]  Address         PCI address of DCT register
 * @param[in]  IndirectAddress Offset of DCT register
 * @param[out] Value           Pointer to value
 * @param[in]  Config          Pointer to standard header
 */
VOID
GnbLibCpuPciIndirectRead (
  IN       UINT32        Address,
  IN       UINT32        IndirectAddress,
     OUT   UINT32        *Value,
  IN       VOID          *Config
  )
{
  UINT32  OffsetRegisterValue;
  GnbLibPciWrite (Address, AccessWidth32, &IndirectAddress, Config);
  do {
    GnbLibPciRead (Address , AccessWidth32, &OffsetRegisterValue, Config);
  } while ((OffsetRegisterValue & BIT31) == 0);
  GnbLibPciRead (Address + 4, AccessWidth32, Value, Config);
}


/*----------------------------------------------------------------------------------------*/
/**
 * Write CPU (DCT) indirect registers
 *
 *
 *
 * @param[in] Address         PCI address of DCT register
 * @param[in] IndirectAddress Offset of DCT register
 * @param[in] Value           Pointer to value
 * @param[in] Config          Pointer to standard header
 */
VOID
GnbLibCpuPciIndirectWrite (
  IN      UINT32        Address,
  IN      UINT32        IndirectAddress,
  IN      UINT32        *Value,
  IN      VOID          *Config
  )
{
  UINT32  OffsetRegisterValue;
  OffsetRegisterValue = IndirectAddress | BIT30;
  GnbLibPciWrite (Address + 4, AccessWidth32, Value, Config);
  GnbLibPciWrite (Address, AccessWidth32, &IndirectAddress, Config);
  do {
    GnbLibPciRead (Address , AccessWidth32, &OffsetRegisterValue, Config);
  } while ((OffsetRegisterValue & BIT31) == 0);
}



