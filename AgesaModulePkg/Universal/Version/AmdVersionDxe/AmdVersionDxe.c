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
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Protocol/AmdVerProtocol.h>
#include "AmdVersionDxe.h"

#define FILECODE UNIVERSAL_VERISION_AMDVERSIONDXE_AMDVERSIONDXE_FILECODE

extern  EFI_BOOT_SERVICES       *gBS;

//
// Driver Global Data
//

/*********************************************************************************
 * Name: AmdVersionDxeInit
 *
 * Description
 *   Entry point of the AMD Version DXE driver
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
AmdVersionDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  EFI_HANDLE          Handle;
  UINTN               SigStringSize;
  UINTN               PcdFullSize;
  CONST CHAR8* AmdVersionStringSig;
  UINT8* AmdVersionString;
  AMD_VER_PROTOCOL *AmdVerProtocol;


  //
  // Publish AGESA version string
  //

  //Get Signature and version string size.
  AmdVersionStringSig = PcdGetPtr (PcdAmdPackageString);
  SigStringSize = AsciiStrSize (AmdVersionStringSig);
  PcdFullSize = SigStringSize + AsciiStrSize (AmdVersionStringSig + SigStringSize);

  // Allocate memory for version string
  Status = gBS->AllocatePool (
                  EfiRuntimeServicesData,
                  PcdFullSize,
                  &AmdVersionString
                  );
  ASSERT_EFI_ERROR (Status);

  gBS->CopyMem (
        AmdVersionString,
        (VOID *)PcdGetPtr (PcdAmdPackageString),
        PcdFullSize
        );

  // Allocate memory for AGESA Version String Protocol
  Status = gBS->AllocatePool (
                  EfiRuntimeServicesData,
                  sizeof (AMD_VER_PROTOCOL),
                  &AmdVerProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  AmdVerProtocol->Signature = AmdVersionString;
  AmdVerProtocol->VersionString = AmdVersionString + SigStringSize;
  //
  // Publish AGESA version string protocol
  //
  Handle = ImageHandle;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdVersionStringProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &AmdVerProtocol
                  );

  return (Status);
}


