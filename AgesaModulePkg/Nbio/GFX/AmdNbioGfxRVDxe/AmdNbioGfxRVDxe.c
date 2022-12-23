/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioGfxRVDxe Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioGfxRVDxe
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
 */
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
 */
#include <PiDxe.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdNbioPcieServicesProtocol.h>
#include <Guid/GnbPcieInfoHob.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Guid/HobList.h>
#include <Guid/GnbIntegratedSysInfoHob.h>

#define FILECODE NBIO_GFX_AMDNBIOGFXRVDXE_AMDNBIOGFXRVDXE_FILECODE
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


/*----------------------------------------------------------------------------------------
 *           T A B L E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


EFI_STATUS
EFIAPI
AmdNbioGfxRVDxeEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;
  NBIO_Frame_Buffer_DATA_HOB           *FrambufferHob;
  UINT64                               DestinationAddress;
  AGESA_TESTPOINT (TpNbioGfxDxeEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioGfxRVDxeEntry\n");

  Status = EFI_SUCCESS;
  Handle = NULL;

  //
  // Get information data from HOB.
  //
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &FrambufferHob);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  FrambufferHob = GetNextGuidHob (&gGnbIntegratedSysInfoHobGuid, FrambufferHob);
  if (FrambufferHob == NULL) {
    return EFI_NOT_FOUND;
  }

  DestinationAddress = (UINT64)((FrambufferHob->UMAInfo.Base + FrambufferHob->UMAInfo.Size) - sizeof(ATOM_FUSION_SYSTEM_INFO_V9));
  IDS_HDT_CONSOLE (MAIN_FLOW, "DXE FrambufferHob->UMAInfo.Base: %lx\n", FrambufferHob->UMAInfo.Base);
  IDS_HDT_CONSOLE (MAIN_FLOW, "DXE FrambufferHob->UMAInfo.Size: %lx\n", FrambufferHob->UMAInfo.Size);

  CopyMem ((VOID*)DestinationAddress,
    &(FrambufferHob->AtomFusionSystemInfoV9),
    sizeof(ATOM_FUSION_SYSTEM_INFO_V9));

  IDS_HDT_CONSOLE (MAIN_FLOW, "Real Integrated Table: %lx\n", (UINT64)((FrambufferHob->UMAInfo.Base + FrambufferHob->UMAInfo.Size) - sizeof(ATOM_FUSION_SYSTEM_INFO_V9)));

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioGfxRVDxeExit\n");
  AGESA_TESTPOINT (TpNbioGfxDxeExit, NULL);
  return Status;
}

