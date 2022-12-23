/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory API for CZ DDR4, and related functions.
 *
 * Contains code that initializes memory
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

  AmdMemS3Dxe.c
  Memory Context S3 Save interface

Abstract:
--*/
#include "Uefi.h"
#include "PiDxe.h"
#include "AGESA.h"
#include "Library/IdsLib.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "AmdMemSmbiosV2Dxe.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Filecode.h"

#define FILECODE        MEM_AMDMEMSMBIOSV2DXE_AMDMEMSMBIOSV2DXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
STATIC AMD_MEM_SMBIOS_SERVICES_PROTOCOL   mMemDmiServicesProtocol = {
  SMBIOS_3_1_1,      // Support SMBIOS 3.1.1
  GetMemDmiInfo
};

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/**
 *---------------------------------------------------------------------------------------
 *
 *  Entry for AmdMemSmbiosCzDxe
 *  Install the protocol of Memory DMI information
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
DxeAmdMemSmbiosV2Entry (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                     Status;

  IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdMemSmbiosV2Dxe Entry\n");

  // Install SMBIOS services protocol
  Status = gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdMemSmbiosServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mMemDmiServicesProtocol
                );

  IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdMemSmbiosV2Dxe Exit\n");
  return Status;
}


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/**
 * This service retrieves information about memory.
 *
 * @param[in]  This                                 A pointer to the
 *                                                  AMD_MEM_SMBIOS_SERVICES_PROTOCOL instance.
 * @param[in, out] MemDmiInfo                           Contains Memory DMI information
 *
 * @retval EFI_SUCCESS                              The Memory DMI information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    MemDmiInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
GetMemDmiInfo (
  IN       AMD_MEM_SMBIOS_SERVICES_PROTOCOL       *This,
  IN OUT   DMI_INFO                               *MemDmiInfo
  )
{
  AMD_CONFIG_PARAMS             StdHeader;
  LOCATE_HEAP_PTR               LocateHeapParams;
  AGESA_STATUS                  Status;

  LocateHeapParams.BufferHandle = AMD_DMI_INFO_BUFFER_HANDLE;
  Status = HeapLocateBuffer (&LocateHeapParams, NULL);
  if (Status == AGESA_SUCCESS) {
    // Retrieve the memory DMI info from heap data
    IDS_HDT_CONSOLE (MAIN_FLOW, "  Memory DMI information retrieved from heap data.\n");
    LibAmdMemCopy (MemDmiInfo, LocateHeapParams.BufferPtr, LocateHeapParams.BufferSize, &StdHeader);

    return EFI_SUCCESS;
  } else {
    return EFI_UNSUPPORTED;
  }
}

