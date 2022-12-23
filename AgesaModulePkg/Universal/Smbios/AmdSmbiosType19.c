/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 19
 *
 * Contains code that generate SMBIOS type 19
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Universal
 * @e \$Revision$   @e \$Date$
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
#include "AmdSmbios.h"
#include "AMD.h"
#include "Porting.h"
#include "Filecode.h"
#include "Library/IdsLib.h"
#include "Library/BaseLib.h"
#include <MemDmi.h>
#include "Library/UefiBootServicesTableLib.h"
#include "Library/MemoryAllocationLib.h"
#include "Protocol/Smbios.h"
#include "Protocol/AmdSmbiosServicesProtocol.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_SMBIOS_AMDSMBIOSTYPE19_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/**
 *---------------------------------------------------------------------------------------
 *
 *  Generate SMBIOS type 19
 *
 *  Parameters:
 *    @param[in]       Smbios                       Pointer to EfiSmbiosProtocol
 *    @param[in]       MemDmiInfo                   Pointer to Memory DMI information
 *    @param[in]       MemoryArrayHandle            Handle of the array that maps to the address range
 *    @param[in]       ArrayMappedHandle            Handle of the array mapped address that maps to the address range
 *    @param[in]       StdHeader                    Handle to config for library and services
 *
 *    @retval          EFI_SUCCESS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
AmdAddSmbiosType19 (
  IN       EFI_SMBIOS_PROTOCOL  *Smbios,
  IN       DMI_INFO             *MemDmiInfo,
  IN       EFI_SMBIOS_HANDLE     MemoryArrayHandle,
  IN       EFI_SMBIOS_HANDLE    *ArrayMappedHandle,
  IN       AMD_CONFIG_PARAMS    *StdHeader,
  IN       UINT8                RegionIndex
  )
{
  UINTN                             StructureSize;
  UINTN                             TotalSize;
  EFI_STATUS                        Status;
  EFI_STATUS                        CalledStatus;
  AMD_SMBIOS_TABLE_TYPE19          *SmbiosTableType19;

  Status = EFI_SUCCESS;

  if ((MemDmiInfo->T19[RegionIndex].StartingAddr == MemDmiInfo->T19[RegionIndex].EndingAddr) &&
      (MemDmiInfo->T19[RegionIndex].ExtStartingAddr == MemDmiInfo->T19[RegionIndex].ExtEndingAddr)) {
    return Status;
  }
  // Generate DMI type 19 --- Start

  SmbiosTableType19 = NULL;
  StructureSize = sizeof (AMD_SMBIOS_TABLE_TYPE19);
  TotalSize = StructureSize + 2; // Additional null (00h), End of strings

  // Allocate zero pool
  SmbiosTableType19 = NULL;
  SmbiosTableType19 = AllocateZeroPool (TotalSize);
  if (SmbiosTableType19 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SmbiosTableType19->Hdr.Handle                        = AMD_SMBIOS_HANDLE_PI_RESERVED;
  SmbiosTableType19->Hdr.Type                          = AMD_EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS;
  SmbiosTableType19->Hdr.Length                        = (UINT8) StructureSize;

  SmbiosTableType19->StartingAddress                   = MemDmiInfo->T19[RegionIndex].StartingAddr;
  SmbiosTableType19->EndingAddress                     = MemDmiInfo->T19[RegionIndex].EndingAddr;
  SmbiosTableType19->MemoryArrayHandle                 = MemoryArrayHandle;
  SmbiosTableType19->PartitionWidth                    = MemDmiInfo->T19[RegionIndex].PartitionWidth;
  SmbiosTableType19->ExtendedStartingAddress           = MemDmiInfo->T19[RegionIndex].ExtStartingAddr;
  SmbiosTableType19->ExtendedEndingAddress             = MemDmiInfo->T19[RegionIndex].ExtEndingAddr;

  // Add DMI type 19
  CalledStatus = Smbios->Add (Smbios, NULL, &SmbiosTableType19->Hdr.Handle, (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType19);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  *ArrayMappedHandle = SmbiosTableType19->Hdr.Handle;

  // Free pool
  FreePool (SmbiosTableType19);

  return Status;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

