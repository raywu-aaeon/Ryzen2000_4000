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
 ******************************************************************************
 */

#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>


/**
 Set AMD PBS setup configuration data in Variable

 @param[out] AmdPbsConfiguration Pointer to the structure of AMD_PBS_SETUP_OPTION,
                                this pointer must be allocated with sizeof(AMD_PBS_SETUP_OPTION)
                                before being called

 @retval EFI_SUCCESS            The AMD PBS configuration is successfully retrieved
 @retval EFI_INVALID_PARAMETER  NULL pointer for input KernelConfig paramater
 @return others                 Failed to retrieve kernel configuration
**/
EFI_STATUS
EFIAPI
SetAmdPbsConfiguration (
  IN AMD_PBS_SETUP_OPTION        *AmdPbsConfiguration
  )
{
  EFI_STATUS Status;
  UINT8      *Buffer;
  UINTN      BufferSize;

  if (AmdPbsConfiguration == NULL) {
    ASSERT_EFI_ERROR (AmdPbsConfiguration != NULL);
    return EFI_INVALID_PARAMETER;
  }

  Buffer       = NULL;
  BufferSize   = 0;
  Status = gRT->GetVariable (
                  AMD_PBS_SETUP_VARIABLE_NAME,
                  &gAmdPbsSystemConfigurationGuid,
                  NULL,
                  &BufferSize,
                  Buffer
                  );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    Buffer = AllocatePool (BufferSize);
    if (Buffer == NULL) {
      ASSERT_EFI_ERROR (Buffer != NULL);
      return EFI_OUT_OF_RESOURCES;
    }
    Status = gRT->GetVariable (
                    AMD_PBS_SETUP_VARIABLE_NAME,
                    &gAmdPbsSystemConfigurationGuid,
                    NULL,
                    &BufferSize,
                    Buffer
                    );
    if (Status == EFI_SUCCESS) {
      CopyMem (Buffer, AmdPbsConfiguration, sizeof (AMD_PBS_SETUP_OPTION));
      Status = gRT->SetVariable (
                    AMD_PBS_SETUP_VARIABLE_NAME,
                    &gAmdPbsSystemConfigurationGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                    BufferSize,
                    Buffer
                    );
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (Buffer);
    return Status;
  }

  //
  // No Setup variable, power on at the first time after updating firmware
  // retrieve default Setup data from SetupUtility protocol
  //
  Buffer = AllocatePool (sizeof (AMD_PBS_SETUP_OPTION));
  if (Buffer == NULL) {
    ASSERT_EFI_ERROR (Buffer != NULL);
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (Buffer, AmdPbsConfiguration, sizeof (AMD_PBS_SETUP_OPTION));
  BufferSize = sizeof (AMD_PBS_SETUP_OPTION);
  Status = gRT->SetVariable (
                AMD_PBS_SETUP_VARIABLE_NAME,
                &gAmdPbsSystemConfigurationGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                BufferSize,
                Buffer
                );

    return Status;
}

/**
 Retrieve AMD PBS setup configuration data

 @param[out] AmdPbsConfiguration Pointer to the structure of AMD_PBS_SETUP_OPTION,
                                this pointer must be allocated with sizeof(AMD_PBS_SETUP_OPTION)
                                before being called

 @retval EFI_SUCCESS            The AMD PBS configuration is successfully retrieved
 @retval EFI_INVALID_PARAMETER  NULL pointer for input KernelConfig paramater
 @return others                 Failed to retrieve kernel configuration
**/
EFI_STATUS
EFIAPI
GetAmdPbsConfiguration (
  OUT AMD_PBS_SETUP_OPTION     *AmdPbsConfiguration
  )
{
  EFI_STATUS Status;
  UINT8      *Buffer;
  UINTN      BufferSize;

  if (AmdPbsConfiguration == NULL) {
    ASSERT_EFI_ERROR (AmdPbsConfiguration != NULL);
    return EFI_INVALID_PARAMETER;
  }

  // The first time set the BufferSize to 0 to get the actual BufferSize should be used, then allocate the Buffer and get the variable again
  Buffer       = NULL;
  BufferSize   = 0;
  Status = gRT->GetVariable (
                  AMD_PBS_SETUP_VARIABLE_NAME,
                  &gAmdPbsSystemConfigurationGuid,
                  NULL,
                  &BufferSize,
                  Buffer
                  );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    Buffer = AllocatePool (BufferSize);
    if (Buffer == NULL) {
      ASSERT_EFI_ERROR (Buffer != NULL);
      return EFI_OUT_OF_RESOURCES;
    }
    Status = gRT->GetVariable (
                    AMD_PBS_SETUP_VARIABLE_NAME,
                    &gAmdPbsSystemConfigurationGuid,
                    NULL,
                    &BufferSize,
                    Buffer
                    );
    if (Status == EFI_SUCCESS) {
      CopyMem (AmdPbsConfiguration, Buffer, sizeof (AMD_PBS_SETUP_OPTION));
    }
    ASSERT_EFI_ERROR (Status);
    FreePool (Buffer);
    return Status;
  }

  return Status;
}
