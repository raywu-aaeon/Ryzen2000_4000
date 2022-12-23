/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory API, and related functions.
 *
 * Contains code that initializes channel translation table
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
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
/*++
Module Name:

  MemChanXLatZpPei.c
  Init Memory channel translation table

Abstract:
--*/

#include "PiPei.h"
#include <Ppi/AmdMemPpi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/MemChanXLat.h>
#include <Ppi/FabricTopologyServices2Ppi.h>
#include "Filecode.h"

#define FILECODE MEM_AMDMEMCHANXLATZPPEI_MEMCHANXLATZPPEI_FILECODE

extern EFI_GUID gAmdMemChanXLatPpiGuid;

//
// Create a Channel Mapping Transaltion Table per CPU Package
//
HOST_TO_APCB_CHANNEL_XLAT DummyChannelXlatTable[] = {
  // Requested   Translated
  { 0xFF,       0xFF},
};

HOST_TO_APCB_CHANNEL_XLAT Am4ChannelXlatTable[] = {
  // Channel A = 0, Channel B = 1
  // Requested   Translated
  { 0,          1 },
  { 1,          0 },
  { 0xFF,       0xFF},
};

HOST_TO_APCB_CHANNEL_XLAT Sp4ChannelXlatTable[] = {
  // Channel A = 0, Channel B = 1, Channel C = 2, Channel D = 3
  // Requested   Translated
  { 0,          0 },
  { 1,          1 },
  { 2,          2 },
  { 3,          3 },
  { 0xFF,       0xFF},
};

HOST_TO_APCB_CHANNEL_XLAT Sp3ChannelXlatTable[] = {
  // Channel A = 0, Channel B = 1, Channel C = 2, Channel D = 3
  // Channel E = 4, Channel F = 5, Channel G = 6, Channel H = 7
  // Requested   Translated
  { 0,          3 },
  { 1,          2 },
  { 2,          0 },
  { 3,          1 },
  { 4,          7 },
  { 5,          6 },
  { 6,          4 },
  { 7,          5 },
  { 0xFF,       0xFF},
};

HOST_TO_APCB_CHANNEL_XLAT Sp3r2Cf4ChannelXlatTable[] = {
  // Channel A = 0, Channel B = 1, Channel C = 2, Channel D = 3
  // Channel E = 4, Channel F = 5, Channel G = 6, Channel H = 7
  // Requested   Translated
  { 0,          0 },
  { 1,          1 },
  { 2,          0xFF},
  { 3,          0xFF},
  { 4,          2 },
  { 5,          3 },
  { 6,          0xFF},
  { 7,          0xFF},
  { 0xFF,       0xFF},
};

/*++

Routine Description:

  Initialize the memory channel translation table.

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdMemChanXLatZpPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                            Status;
  SOC_ID_STRUCT                         SocId;
  AMD_MEMORY_CHANNEL_XLAT_PPI           *mMemChanXLatPpi;
  EFI_PEI_PPI_DESCRIPTOR                *mMemChanXLatPpiList;
  AMD_PEI_FABRIC_TOPOLOGY_SERVICES2_PPI *FabricTopologyServices;
  UINTN                                 NumOfDies;

  //----------------------------------------------------------------
  //
  //            Allocate space for PPI data structure
  //
  //----------------------------------------------------------------
  Status = (*PeiServices)->AllocatePool (
                           PeiServices,
                           sizeof (AMD_MEMORY_CHANNEL_XLAT_PPI),
                           &mMemChanXLatPpi
                           );
  if (EFI_SUCCESS != Status) {
    return Status;
  }

  Status = (*PeiServices)->AllocatePool (
                           PeiServices,
                           sizeof (EFI_PEI_PPI_DESCRIPTOR),
                           &mMemChanXLatPpiList
                           );
  if (EFI_SUCCESS != Status) {
    return Status;
  }

  mMemChanXLatPpi->XLatTab = (VOID *)&DummyChannelXlatTable[0];

  // Check Hardware Identification
  SocId.SocFamilyID = F17_ZP_RAW_ID;
  SocId.PackageType = ZP_AM4;

  if (SocHardwareIdentificationCheck (&SocId)) {
    mMemChanXLatPpi->XLatTab = (VOID *)&Am4ChannelXlatTable[0];
  }

  SocId.SocFamilyID = F17_ZP_RAW_ID;
  SocId.PackageType = ZP_SP4;

  if (SocHardwareIdentificationCheck (&SocId)) {
    mMemChanXLatPpi->XLatTab = (VOID *)&Sp4ChannelXlatTable[0];
  }

  SocId.SocFamilyID = F17_ZP_RAW_ID;
  SocId.PackageType = ZP_SP3;

  if (SocHardwareIdentificationCheck (&SocId)) {
    mMemChanXLatPpi->XLatTab = (VOID *)&Sp3ChannelXlatTable[0];
  }

  SocId.SocFamilyID = F17_ZP_RAW_ID;
  SocId.PackageType = TR_SP3r2;

  if (SocHardwareIdentificationCheck (&SocId)) {
    Status = (*PeiServices)->LocatePpi (
                                PeiServices,
                                &gAmdFabricTopologyServices2PpiGuid,
                                0,
                                NULL,
                                &FabricTopologyServices
                               );
    if (EFI_SUCCESS != Status) {
      return Status;
    }
    FabricTopologyServices->GetProcessorInfo (0, &NumOfDies, NULL);

    if (NumOfDies == 4) {
      mMemChanXLatPpi->XLatTab = (VOID *)&Sp3r2Cf4ChannelXlatTable[0];
    }
  }

  mMemChanXLatPpi->Revision = AMD_MEMORY_CHANNEL_XLAT_REVISION;
  mMemChanXLatPpiList->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  mMemChanXLatPpiList->Guid  = &gAmdMemChanXLatPpiGuid;
  mMemChanXLatPpiList->Ppi   = mMemChanXLatPpi;

  Status = (**PeiServices).InstallPpi (PeiServices, mMemChanXLatPpiList);

  return (Status);
}

