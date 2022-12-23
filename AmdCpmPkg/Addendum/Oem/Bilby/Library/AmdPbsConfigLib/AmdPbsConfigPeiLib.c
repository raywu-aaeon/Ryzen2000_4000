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

#include <AmdCpmPei.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>

EFI_STATUS
EFIAPI
LoadAmdPbsDefault (
  OUT AMD_PBS_SETUP_OPTION        *AmdPbsConfiguration
  );

/**
 Retrieve AMD PBS setup configuration data

 @param[out] AmdPbsConfig       Pointer to the structure of AMD_PBS_SETUP_OPTION,
                                this pointer must be allocated with sizeof(AMD_PBS_SETUP_OPTION)
                                before being called

 @retval EFI_SUCCESS            The AMD PBS configuration is successfully retrieved
 @retval EFI_INVALID_PARAMETER  NULL pointer for input AmdPbsConfig paramater
 @return others                 Failed to retrieve AMD PBS configuration
**/
EFI_STATUS
EFIAPI
GetAmdPbsConfiguration (
  OUT AMD_PBS_SETUP_OPTION        *AmdPbsConfiguration
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariablePpi;
  AMD_PBS_SETUP_OPTION            LocalAmdPbsConfiguration;
  AMD_PBS_SETUP_OPTION            AmdPbsTempConfiguration;
  UINTN                           Size;
  UINT8                           Index;
  UINT8                           DefaultUsedPbsSize;
  AMD_CPM_OEM_TABLE_PPI           *AmdCpmOemTablePpi;
  BOOLEAN                         OemTableReady;

  Index = 0;
  DefaultUsedPbsSize = 46;        // It's RV PI 1001 DefaultUsedPbsSize.
  OemTableReady = TRUE;

  if (AmdPbsConfiguration == NULL) {
    ASSERT_EFI_ERROR (AmdPbsConfiguration != NULL);
    return EFI_INVALID_PARAMETER;
  }

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariablePpi
             );
  if (EFI_ERROR(Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  Status = PeiServicesLocatePpi (
             &gAmdCpmOemTablePpiGuid,
             0,
             NULL,
             (VOID **) &AmdCpmOemTablePpi
             );
  if (EFI_ERROR(Status)) {
    OemTableReady = FALSE;
  }

  Size = sizeof (AMD_PBS_SETUP_OPTION);
  Status = VariablePpi->GetVariable (
                          VariablePpi,
                          AMD_PBS_SETUP_VARIABLE_NAME,
                          &gAmdPbsSystemConfigurationGuid,
                          NULL,
                          &Size,
                          &LocalAmdPbsConfiguration
                          );
  if (Status == EFI_SUCCESS) {
    if (LocalAmdPbsConfiguration.AmdCpmUsedPbsSize > 0) {
      DefaultUsedPbsSize = LocalAmdPbsConfiguration.AmdCpmUsedPbsSize;
    }
    if (OemTableReady) {
      if (LocalAmdPbsConfiguration.PlatformId != ((PcdGet16 (OriginalPlatformId) & BIT2) >> 2)) {
        DefaultUsedPbsSize = 0;     // Force to load all of PBS default value.
      }
      if (LocalAmdPbsConfiguration.CurrentId != ((PcdGet16 (CurrentPlatformId) < 0x0008) ? 0 : 1)) {
        DefaultUsedPbsSize = 0;     // Force to load all of PBS default value.
      }
    }
    if (DefaultUsedPbsSize < AMD_CPM_USED_PBS_SIZE) {
      Status = LoadAmdPbsDefault (&AmdPbsTempConfiguration);
      CopyMem (((UINT8 *) &LocalAmdPbsConfiguration) + DefaultUsedPbsSize, ((UINT8 *) &AmdPbsTempConfiguration) + DefaultUsedPbsSize, AMD_CPM_USED_PBS_SIZE - DefaultUsedPbsSize);
      for (Index = DefaultUsedPbsSize; Index < AMD_CPM_USED_PBS_SIZE; Index ++) {
        DEBUG((DEBUG_INFO, "OEM-PEI-GetAmdPbsConfiguration-Update PBS Index[0x%X] = 0x%X to 0x%X\n", Index, ((UINT8 *) &LocalAmdPbsConfiguration)[Index], ((UINT8 *) &LocalAmdPbsConfiguration)[Index]));
      }
      if (LocalAmdPbsConfiguration.AmdCpmUsedPbsSize != AMD_CPM_USED_PBS_SIZE) {
        LocalAmdPbsConfiguration.AmdCpmUsedPbsSize = AMD_CPM_USED_PBS_SIZE;
        DEBUG((DEBUG_INFO, "OEM-PEI-GetAmdPbsConfiguration-Update AmdCpmUsedPbsSize to 0x%X\n", LocalAmdPbsConfiguration.AmdCpmUsedPbsSize));
      }
      if (LocalAmdPbsConfiguration.PlatformId != ((PcdGet16 (OriginalPlatformId) & BIT2) >> 2)) {
        LocalAmdPbsConfiguration.PlatformId = ((PcdGet16 (OriginalPlatformId) & BIT2) >> 2);
        DEBUG((DEBUG_INFO, "OEM-PEI-GetAmdPbsConfiguration-Update PlatformId to 0x%X\n", LocalAmdPbsConfiguration.PlatformId));
      }
      if (LocalAmdPbsConfiguration.CurrentId != ((PcdGet16 (CurrentPlatformId) < 0x0008) ? 0 : 1)) {
        LocalAmdPbsConfiguration.CurrentId = ((PcdGet16 (CurrentPlatformId) < 0x0008) ? 0 : 1);
        DEBUG((DEBUG_INFO, "OEM-PEI-GetAmdPbsConfiguration-Update CurrentId to 0x%X\n", LocalAmdPbsConfiguration.CurrentId));
      }
    }
    CopyMem (AmdPbsConfiguration, &LocalAmdPbsConfiguration, Size);
  } else {
    Status = LoadAmdPbsDefault (AmdPbsConfiguration);
  }

  return Status;
}
