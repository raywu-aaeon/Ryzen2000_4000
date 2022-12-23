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

  AmdSocAm4Pei.c
  Init Soc interface

Abstract:
--*/

#include <Library/DebugLib.h>
#include <AmdSoc.h>
#include <Ppi/AmdSocPcdInitPpi.h>
#include "AmdAgesaParameterGroupPei.h"


STATIC AMD_PCD_PTR mPcdAmdAgesaConfigParameter6 = {sizeof (EFI_GUID), &gAmdSocAgesaGroupIdentificationPpiGuid};

// the PCDs list here are simple for the reference. platform BIOS need to replace with the cofiguration PCD provide by IP driver.
AMD_PCD_LIST AmdConfigurationParameterListA[] = {
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001A, (UINT64)TRUE, PCD_BOOL},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001B, (UINT64)0xAA, PCD_UINT8},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001C, (UINT64)0x4321, PCD_UINT16},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001D, (UINT64)0x12345678, PCD_UINT32},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001E, (UINT64)0xDEADBEEFDEADBEEF, PCD_UINT64}
};

AMD_PCD_LIST AmdConfigurationParameterListB[] = {
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001A, (UINT64)FALSE, PCD_BOOL},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001B, (UINT64)0xBB, PCD_UINT8},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001C, (UINT64)0x7654, PCD_UINT16},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001D, (UINT64)0x45678123, PCD_UINT32},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001E, (UINT64)0xABCDEF0123456789, PCD_UINT64},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001F, (UINT64)(UINTN)&mPcdAmdAgesaConfigParameter6, PCD_PTR}
};

AMD_PCD_LIST AmdConfigurationParameterListC[] = {
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001B, (UINT64)0xCC, PCD_UINT8},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001C, (UINT64)0xAA55, PCD_UINT16},
  {&gEfiAmdAgesaPkgTokenSpaceGuid, 0x0003001D, (UINT64)0xDEADBEEF, PCD_UINT32}
};

//the number of the list depends on platform design. the number can be vary.
AMD_GROUP_LIST_HEADER AmdConfigurationParameterGroupList[] = {
{&gAmdConfigurationParameterListAGuid, (sizeof (AmdConfigurationParameterListA) / sizeof (AmdConfigurationParameterListA[0])), &AmdConfigurationParameterListA[0]},
{&gAmdConfigurationParameterListBGuid, (sizeof (AmdConfigurationParameterListB) / sizeof (AmdConfigurationParameterListB[0])), &AmdConfigurationParameterListB[0]},
{&gAmdConfigurationParameterListCGuid, (sizeof (AmdConfigurationParameterListC) / sizeof (AmdConfigurationParameterListC[0])), &AmdConfigurationParameterListC[0]}
};

STATIC AMD_PCD_PLATFORM_GROUP_LIST mAmdPcdPlatformGroupList = {
  0,
  (sizeof (AmdConfigurationParameterGroupList) / sizeof (AmdConfigurationParameterGroupList[0])),
  &AmdConfigurationParameterGroupList[0],
  &gAmdConfigurationParameterListAGuid
};

STATIC PEI_AMD_AGESA_PARAMETER_GROUP_ID_PPI mAmdAgesaParameterGroupIdPpi = {
  AMD_AGESA_PARAMETER_GROUP_ID_PPI_REVISION,
  &mAmdPcdPlatformGroupList,
  AmdSocCallBackPei,
};

STATIC EFI_PEI_PPI_DESCRIPTOR mPpiAgesaParameterGroupIdService = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdSocAgesaGroupIdentificationPpiGuid,
  &mAmdAgesaParameterGroupIdPpi
};

/*++

Routine Description:

  SOC Driver Entry. Initialize SOC device and publish silicon driver installation PPI

Arguments:

Returns:

  EFI_STATUS

--*/
EFI_STATUS
EFIAPI
AmdAgesaParameterGroupPeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS          Status = EFI_SUCCESS;

  DEBUG ((EFI_D_ERROR, "***************PEI AGESA Parameter Group Identification Driver Entry***************\n"));

  // Publish Agesa Parameter Group Identification Ppi
  // this ppi need to be installed before SOC driver
  Status = (*PeiServices)->InstallPpi (
                               PeiServices,
                               &mPpiAgesaParameterGroupIdService
                               );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((EFI_D_ERROR, "***************PEI AGESA Parameter Group Identification Driver Exit***************\n"));
  return (Status);
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 * This function use for change AGESA configuration parameter PCD for multiplatform support.
 *
 * It will prepare AGESA configuration group list and return to SOC driver.
 * then the SOC driver will update the PCD value based on the list provide by this function.
 *
 * @param[in]   PeiServices
 * @param[in]   SocId
 * @param[out]  PlalformGroupGuid
 *
 */
EFI_STATUS
EFIAPI
AmdSocCallBackPei (
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN       SOC_ID_STRUCT *SocId,
  OUT      EFI_GUID **PlalformGroupGuid
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;

  *PlalformGroupGuid = &gAmdConfigurationParameterListBGuid;

  if (SocId->SocFamilyID == F17_ZP_RAW_ID && SocId->PackageType == ZP_PKG_AM4) {
    *PlalformGroupGuid = &gAmdConfigurationParameterListBGuid;
  }

  if (SocId->SocFamilyID == F17_ZP_RAW_ID && SocId->PackageType == ZP_SP3) {
    *PlalformGroupGuid = &gAmdConfigurationParameterListCGuid;
  }

  if (SocId->SocFamilyID == F17_ZP_RAW_ID && SocId->PackageType == ZP_SP4) {
    *PlalformGroupGuid = &gAmdConfigurationParameterListAGuid;
  }

  return Status;
}
