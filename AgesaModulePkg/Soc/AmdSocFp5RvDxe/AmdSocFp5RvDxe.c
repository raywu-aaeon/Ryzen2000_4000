/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#include <Filecode.h>
#include "AGESA.h"
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/DxeSocLogicalIdServicesLib.h>
#include <Protocol/AmdSocProtocol.h>
#include "AmdSocFp5RvDxe.h"

#define FILECODE SOC_AMDSOCFP5RVDXE_AMDSOCFP5RVDXE_FILECODE

extern  EFI_BOOT_SERVICES       *gBS;

//
// Driver Global Data
//

/*********************************************************************************
 * Name: AmdSocFp5DxeInit
 *
 * Description
 *   Entry point of the AMD SOC Raven FP5 DXE driver
 *   Perform the configuration init, resource reservation, early post init
 *   and install all the supported protocol
 *
 * Input
 *   ImageHandle : EFI Image Handle for the DXE driver
 *   SystemTable : pointer to the EFI system table
 *
 * Output
 *   EFI_SUCCESS : Module initialized successfully
 *   EFI_ERROR   : Initialization failed (see error for more details)
 *
 *********************************************************************************/
EFI_STATUS
EFIAPI
AmdSocFp5RvDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  EFI_HANDLE          Handle;
  SOC_ID_STRUCT       SocId;
  SOC_ID_STRUCT       SocId2;
  SOC_ID_STRUCT       SocId3;
  UINT8 i;

  DEBUG ((EFI_D_ERROR, "*****************************DXE SOC FP5 RV Driver Entry*********************\n"));

  SocId.SocFamilyID = F17_RV_RAW_ID;
  SocId.PackageType = RV_FP5;

  SocId2.SocFamilyID = F17_RV2_RAW_ID;
  SocId2.PackageType = RV_FP5;

  SocId3.SocFamilyID = F17_PIC_RAW_ID;
  SocId3.PackageType = RV_FP5;

  // Check Hardware Identification
  if (SocHardwareIdentificationCheck (&SocId) || SocHardwareIdentificationCheck (&SocId2) || SocHardwareIdentificationCheck (&SocId3)) {
    //
    // Publish the logical ID protocol
    //
    Status = SocLogicalIdServiceProtocolInstall (ImageHandle, SystemTable);

    IDS_HOOK (IDS_HOOK_BEGINNING_OF_AGESA, NULL, NULL);

    //
    // Publish the Silicon installation protocol
    //

    Handle = ImageHandle;
    for (i = 0 ; i < SiliconDriverProtocolListNumber; i++) {
      Status = gBS->InstallProtocolInterface (
                    &Handle,
                    SiliconDriverProtocolList[i],
                    EFI_NATIVE_INTERFACE,
                    NULL
                    );
    }
  }
  DEBUG ((EFI_D_ERROR, "*****************************DXE SOC FP5 RV Driver Exit*********************\n"));
  return (Status);
}


