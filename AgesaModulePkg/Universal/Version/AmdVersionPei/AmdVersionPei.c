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
/*++
Module Name:

  AmdVersionPei.c
  Init AGESA version string interface

Abstract:
--*/

#include <Filecode.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Ppi/AmdVerPpi.h>
#include "AmdVersionPei.h"


#define FILECODE UNIVERSAL_VERISION_AMDVERSIONPEI_AMDVERSIONPEI_FILECODE

/*++

Routine Description:

  Version Driver Entry. Initialize and publish AGESA version string PPI

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdVersionPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;
  PEI_AMD_VER_PPI    *mAmdVersionStringPpi;
  EFI_PEI_PPI_DESCRIPTOR    *mAmdVersionString;

  UINTN SignatureSize;

  //Init VER_PEI_PPI
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (PEI_AMD_VER_PPI),
                             &mAmdVersionStringPpi
                             );
  ASSERT_EFI_ERROR ( Status);

  mAmdVersionStringPpi->Signature = PcdGetPtr (PcdAmdPackageString);
  SignatureSize = AsciiStrSize (mAmdVersionStringPpi->Signature);
  mAmdVersionStringPpi->VersionString = mAmdVersionStringPpi->Signature + SignatureSize;

  // Allocate memory for the PPI descriptor
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (EFI_PEI_PPI_DESCRIPTOR),
                             (VOID **)&mAmdVersionString
                             );
  ASSERT_EFI_ERROR ( Status);

  mAmdVersionString->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  mAmdVersionString->Guid  = &gAmdVersionStringPpiGuid;
  mAmdVersionString->Ppi   = mAmdVersionStringPpi;

  Status = (*PeiServices)->InstallPpi (
                             PeiServices,
                             mAmdVersionString
                             );
  return (Status);
}


