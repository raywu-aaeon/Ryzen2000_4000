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

  AmdSocFp5RvPei.c
  Init Soc interface

Abstract:
--*/

#include <Filecode.h>
#include "AGESA.h"
#include <Library/CcxSetMmioCfgBaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/PeiSocLogicalIdServicesLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/FabricResourceInitLib.h>
#include <Library/PeiSocBistLoggingLib.h>
#include <Ppi/AmdSocPpi.h>
#include <Ppi/AmdSocPcdInitPpi.h>
#include <Ppi/AmdCcxPpi.h>
#include "AmdSocFp5RvPei.h"

#define FILECODE SOC_AMDSOCFP5RVPEI_AMDSOCFP5RVPEI_FILECODE

EFI_STATUS
EFIAPI
SocAfterPeiInitCompleteCallback (
  IN  CONST EFI_PEI_SERVICES                **PeiServices,
  IN        EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN        VOID                            *InvokePpi
  );

STATIC PEI_AMD_SOC_PPI mAmdSocInstallPpiTemplate = {
  AMD_SOC_PPI_REVISION,
};

STATIC PEI_AMD_PCD_INIT_READY_PPI mAmdPcdInitReadyPpi = {
  PEI_AMD_PCD_INIT_READY_PPI_REVISION,
};

STATIC EFI_PEI_PPI_DESCRIPTOR mAmdPcdInitReady = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdPcdInitReadyPpiGuid,
  &mAmdPcdInitReadyPpi
};

EFI_PEI_NOTIFY_DESCRIPTOR   mAfterCcxPeiInitCompletePpiCallback = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCcxPeiInitCompletePpiGuid,
  SocAfterPeiInitCompleteCallback
};

EFI_STATUS
SocPublishSiliconPpi (
  IN CONST EFI_PEI_SERVICES    **PeiServices,
  IN CONST EFI_GUID            *SiliconDriverId
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  EFI_PEI_PPI_DESCRIPTOR    *SocPpiDescriptorTemplate;

  // Allocate memory for the PPI descriptor
  Status = (*PeiServices)->AllocatePool (
                             PeiServices,
                             sizeof (EFI_PEI_PPI_DESCRIPTOR),
                             (VOID **)&SocPpiDescriptorTemplate
                             );
  ASSERT_EFI_ERROR ( Status);

  SocPpiDescriptorTemplate->Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
  SocPpiDescriptorTemplate->Guid  = (EFI_GUID*)SiliconDriverId;
  SocPpiDescriptorTemplate->Ppi   = &mAmdSocInstallPpiTemplate;

  Status = (*PeiServices)->InstallPpi (
                             PeiServices,
                             SocPpiDescriptorTemplate
                             );
  return (Status);
}

/*++

Routine Description:

  SOC Driver Entry. Initialize SOC device and publish silicon driver installation PPI

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdSocFp5RvPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  UINT8               i;
  SOC_ID_STRUCT       SocId;
  SOC_ID_STRUCT       SocId2;
  SOC_ID_STRUCT       SocId3;
  EFI_STATUS          Status = EFI_SUCCESS;
  PEI_AMD_AGESA_PARAMETER_GROUP_ID_PPI *PeiAmdAgesaParameterGroupIdPpi;
  AMD_PCD_PLATFORM_GROUP_LIST *AmdPcdPlatformGroupList;
  EFI_GUID *PlatformGroupGuid = NULL;

  DEBUG ((EFI_D_ERROR, "*****************************PEI SOC FP5 RV Driver Entry*********************\n"));

  // Check Hardware Identification
  SocId.SocFamilyID = F17_RV_RAW_ID;
  SocId.PackageType = RV_FP5;

  SocId2.SocFamilyID = F17_RV2_RAW_ID;
  SocId2.PackageType = RV_FP5;

  SocId3.SocFamilyID = F17_PIC_RAW_ID;
  SocId3.PackageType = RV_FP5;

  if (SocHardwareIdentificationCheck (&SocId) || SocHardwareIdentificationCheck (&SocId2) || SocHardwareIdentificationCheck (&SocId3)) {

    // Init PCIE Configuration Space
    CcxSetMmioCfgBaseLib ();
    // Init DF resource
    FabricResourceInit ();

    //
    // Parameter initailization
    //
    Status = (*PeiServices)->LocatePpi (
                PeiServices,
                &gAmdSocAgesaGroupIdentificationPpiGuid,
                0,
                NULL,
                (VOID**)&PeiAmdAgesaParameterGroupIdPpi
                );

    if (EFI_SUCCESS == Status) {
      AmdPcdPlatformGroupList = PeiAmdAgesaParameterGroupIdPpi->AmdConfigurationPcdGroupList;

      //Pass SOC ID to platform BIOS before PCD init.
      Status = PeiAmdAgesaParameterGroupIdPpi->AmdSocCallBackPei (PeiServices, &SocId, &PlatformGroupGuid);
      if (NULL == PlatformGroupGuid) {
        PlatformGroupGuid = AmdPcdPlatformGroupList->PlatformGroupGuid;
      }

      //find Group Agesa configuration list
      for (i = 0; i < AmdPcdPlatformGroupList->NumberOfGroupsList; i++) {
        if (CompareGuid (PlatformGroupGuid, (EFI_GUID *)AmdPcdPlatformGroupList->GroupList[i].PlatformGroupGuid)) {
          // Update PCD
          AmdPcdInit (AmdPcdPlatformGroupList->GroupList[i].NumberOfPcdEntries, (AMD_PCD_LIST *)AmdPcdPlatformGroupList->GroupList[i].ListEntry);
        }
      }
    }

    //
    // Publish the logical ID protocol
    //
    Status = SocLogicalIdServicePpiInstall (PeiServices);

    //
    //Publish Silicon Driver Installation PPI
    //
    Status = (*PeiServices)->InstallPpi (
                             PeiServices,
                             &mAmdPcdInitReady
                             );
    ASSERT_EFI_ERROR (Status);

    IDS_HOOK (IDS_HOOK_BEGINNING_OF_AGESA, NULL, NULL);

    //
    //Publish Silicon Driver Installation PPI
    //
    for (i = 0 ; i < SiliconDriverPpiListNumber; i++) {
      SocPublishSiliconPpi (PeiServices, SiliconDriverPpiList[i]);
    }

    (**PeiServices).NotifyPpi (PeiServices, &mAfterCcxPeiInitCompletePpiCallback);
  }

  DEBUG ((EFI_D_ERROR, "*****************************PEI SOC FP5 RV Driver Exit*********************\n"));
  return (Status);
}

/*++

Routine Description:

  Callback routine once gAmdCcxPeiInitCompletePpiGuid has been installed to ensure the following services have been published
  - Core Topology Services
  - Fabric Topology Services
  - Nbio SMU Services

Arguments:
  **PeiServices
  *NotifyDesc
  *InvokePpi

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
SocAfterPeiInitCompleteCallback (
  IN  CONST EFI_PEI_SERVICES                **PeiServices,
  IN        EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
  IN        VOID                            *InvokePpi
  )
{

  LogBistStatus (PeiServices);

  return EFI_SUCCESS;
}

