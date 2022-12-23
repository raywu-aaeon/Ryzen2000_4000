/*****************************************************************************
  *
  * Copyright 2016 - 2018 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
  *
  * AMD is granting you permission to use this software (the Materials)
  * pursuant to the terms and conditions of your Software License Agreement
  * with AMD.  This header does *NOT* give you permission to use the Materials
  * or any rights under AMD's intellectual property.  Your use of any portion
  * of these Materials shall constitute your acceptance of those terms and
  * conditions.  If you do not agree to the terms and conditions of the Software
  * License Agreement, please do not use any portion of these Materials.
  *
  * CONFIDENTIALITY:  The Materials and all other information, identified as
  * confidential and provided to you by AMD shall be kept confidential in
  * accordance with the terms and conditions of the Software License Agreement.
  *
  * LIMITATION OF LIABILITY: THE MATERIALS AND ANY OTHER RELATED INFORMATION
  * PROVIDED TO YOU BY AMD ARE PROVIDED "AS IS" WITHOUT ANY EXPRESS OR IMPLIED
  * WARRANTY OF ANY KIND, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
  * MERCHANTABILITY, NONINFRINGEMENT, TITLE, FITNESS FOR ANY PARTICULAR PURPOSE,
  * OR WARRANTIES ARISING FROM CONDUCT, COURSE OF DEALING, OR USAGE OF TRADE.
  * IN NO EVENT SHALL AMD OR ITS LICENSORS BE LIABLE FOR ANY DAMAGES WHATSOEVER
  * (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS, BUSINESS
  * INTERRUPTION, OR LOSS OF INFORMATION) ARISING OUT OF AMD'S NEGLIGENCE,
  * GROSS NEGLIGENCE, THE USE OF OR INABILITY TO USE THE MATERIALS OR ANY OTHER
  * RELATED INFORMATION PROVIDED TO YOU BY AMD, EVEN IF AMD HAS BEEN ADVISED OF
  * THE POSSIBILITY OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE
  * EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES,
  * THE ABOVE LIMITATION MAY NOT APPLY TO YOU.
  *
  * AMD does not assume any responsibility for any errors which may appear in
  * the Materials or any other related information provided to you by AMD, or
  * result from use of the Materials or any related information.
  *
  * You agree that you will not reverse engineer or decompile the Materials.
  *
  * NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
  * further information, software, technical information, know-how, or show-how
  * available to you.  Additionally, AMD retains the right to modify the
  * Materials at any time, without notice, and is not obligated to provide such
  * modified Materials to you.
  *
  * U.S. GOVERNMENT RESTRICTED RIGHTS: The Materials are provided with
  * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
  * subject to the restrictions as set forth in FAR 52.227-14 and
  * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
  * Government constitutes acknowledgement of AMD's proprietary rights in them.
  *
  * EXPORT ASSURANCE:  You agree and certify that neither the Materials, nor any
  * direct product thereof will be exported directly or indirectly, into any
  * country prohibited by the United States Export Administration Act and the
  * regulations thereunder, without the required authorization from the U.S.
  * government nor will be used for any purpose prohibited by the same.
  * ***************************************************************************
  *
 */

#include "SocLogicalId.h"
#include "Library/AmdBaseLib.h"
#include "Ids.h"
#include "Library/IdsLib.h"
#include "Library/AmdErrorLogLib.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"

#define FILECODE LIBRARY_HARDCODEDMEMCOMMONSERVICELIB_HARDCODEDMEMCOMMONSERVICELIB_FILECODE

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

// [Fam15 only]
UINT32
GetPlatformNumberOfSockets (
  VOID
  )
{
  return 1;
}

// [Fam15 only]
BOOLEAN
GetSocketModuleOfNode (
  IN       UINT32    Node,
     OUT   UINT32    *Socket,
     OUT   UINT32    *Module,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  *Socket = 0;
  *Module = 0;

  return TRUE;
}

// [Fam15 only]
VOID
PutEventLog (
  IN       AGESA_STATUS EventClass,
  IN       UINT32 EventInfo,
  IN       UINT32 DataParam1,
  IN       UINT32 DataParam2,
  IN       UINT32 DataParam3,
  IN       UINT32 DataParam4,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{

}

// [Fam15 only]
BOOLEAN
GetPciAddress (
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN       UINT32            Socket,
  IN       UINT32            Module,
     OUT   PCI_ADDR          *PciAddress,
     OUT   AGESA_STATUS      *AgesaStatus
  )
{
  BOOLEAN      Result;

  Result = TRUE;
  // Always Succeeds.
  *AgesaStatus = AGESA_SUCCESS;

  PciAddress->AddressValue = MAKE_SBDFO (0, 0, 24, 0, 0);

  return Result;
}

// [Fam15 only]
BOOLEAN
IsProcessorPresent (
  IN       UINT32             Socket,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  BOOLEAN Result;

  Result = FALSE;

  if (Socket == 0) {
    Result = TRUE;
  }
  return Result;
}

// [Fam15 only]
VOID
GetLogicalIdOfSocket (
  IN       UINT32 Socket,
     OUT   SOC_LOGICAL_ID *LogicalId,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  LogicalId->Family = AMD_FAMILY_CZ;
  LogicalId->Revision = AMD_REV_F15_BR_A1;
}

