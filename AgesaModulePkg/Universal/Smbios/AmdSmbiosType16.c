/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 16
 *
 * Contains code that generate SMBIOS type 16
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

#define FILECODE UNIVERSAL_SMBIOS_AMDSMBIOSTYPE16_FILECODE

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
 *  Generate SMBIOS type 16
 *
 *  Parameters:
 *    @param[in]       Smbios                       Pointer to EfiSmbiosProtocol
 *    @param[in]       MemDmiInfo                   Pointer to Memory DMI information
 *    @param[in]       MemoryErrorInfoHandle        Handle of the array where error is detected
 *    @param[out]      MemoryArrayHandle            Handle of the current physical array
 *    @param[in]       StdHeader                    Handle to config for library and services
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
AmdAddSmbiosType16 (
  IN       EFI_SMBIOS_PROTOCOL  *Smbios,
  IN       DMI_INFO             *MemDmiInfo,
  IN       EFI_SMBIOS_HANDLE     MemoryErrorInfoHandle,
  IN       EFI_SMBIOS_HANDLE    *MemoryArrayHandle,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINTN                             StructureSize;
  UINTN                             TotalSize;
  EFI_STATUS                        Status;
  EFI_STATUS                        CalledStatus;
  AMD_SMBIOS_TABLE_TYPE16          *SmbiosTableType16;

  Status = EFI_SUCCESS;
  // Calculate size of DMI type 16
  StructureSize = sizeof (AMD_SMBIOS_TABLE_TYPE16);
  TotalSize = StructureSize + 2; // Additional null (00h), End of strings

  // Allocate zero pool
  SmbiosTableType16 = NULL;
  SmbiosTableType16 = AllocateZeroPool (TotalSize);
  if (SmbiosTableType16 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Generate DMI type 4 --- Start

  SmbiosTableType16->Hdr.Type                     = AMD_EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY;
  SmbiosTableType16->Hdr.Length                   = (UINT8) StructureSize;
  SmbiosTableType16->Hdr.Handle                   = AMD_SMBIOS_HANDLE_PI_RESERVED;

  SmbiosTableType16->Location                     = MemDmiInfo->T16.Location;
  SmbiosTableType16->Use                          = MemDmiInfo->T16.Use;
  SmbiosTableType16->MemoryErrorCorrection        = MemDmiInfo->T16.MemoryErrorCorrection;
  SmbiosTableType16->MemoryErrorInformationHandle = MemoryErrorInfoHandle;
  SmbiosTableType16->NumberOfMemoryDevices        = MemDmiInfo->T16.NumberOfMemoryDevices;

  SmbiosTableType16->MaximumCapacity              = PcdGet32 (PcdAmdSmbiosT16MaximumCapacity);
  if (SmbiosTableType16->MaximumCapacity == 0x80000000) {
    SmbiosTableType16->ExtendedMaximumCapacity      = PcdGet64 (PcdAmdSmbiosT16ExtMaximumCapacity);
  } else {
    SmbiosTableType16->ExtendedMaximumCapacity      = 0;
  }

  // Add DMI type 16
  CalledStatus = Smbios->Add (Smbios, NULL, &SmbiosTableType16->Hdr.Handle, (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType16);
  Status = (CalledStatus > Status) ? CalledStatus : Status;
  *MemoryArrayHandle = SmbiosTableType16->Hdr.Handle;

  // Free pool
  FreePool (SmbiosTableType16);

  return Status;
}



/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


