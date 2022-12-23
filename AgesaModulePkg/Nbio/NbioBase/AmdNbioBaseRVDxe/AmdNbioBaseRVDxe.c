/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioPcieRVDxe Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioPcieRVDxe
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <PiDxe.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdNbioBaseServicesProtocol.h>
#include <Protocol/AmdAcpiCratServicesProtocol.h>
#include <Guid/GnbNbioBaseZPInfoHob.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Guid/HobList.h>

#define FILECODE NBIO_NBIOBASE_AMDNBIOBASERVDXE_AMDNBIOBASERVDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

EFI_STATUS
EFIAPI
IGpuGetCratHsaProcEntry (
  IN       AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL   *This,
  IN OUT   CRAT_HSA_PROCESSING_UNIT               *CratHsaEntry
  );

#define GPU__GC__NUM_SE 1
#define GPU__GC__NUM_SH_PER_SE 1
#define GPU__GC__NUM_CU_PER_SH 11

STATIC AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL   mIGpuCratServicesProtocol = {
  0,
  IGpuGetCratHsaProcEntry
};

/**
 * This service retrieves CRAT information about the HSA.
 *
 * @param[in]      This                             A pointer to the
 *                                                  AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL instance.
 * @param[in, out] CratHsaEntry                     Contains HSA processor information
 *
 * @retval EFI_SUCCESS                              The HSA processor information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    CratHsaProcInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
IGpuGetCratHsaProcEntry (
  IN       AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL   *This,
  IN OUT   CRAT_HSA_PROCESSING_UNIT               *CratHsaEntry
  )
{

  if (PcdGetBool (PcdCfgIommuSupport) == TRUE) {
    CratHsaEntry->Flags.HSAmmuPresent = 1;
  }

  CratHsaEntry->Flags.Enabled = 1;
  CratHsaEntry->Flags.GpuPresent = 1;
  CratHsaEntry->NumSIMDPerCU = 4;
  CratHsaEntry->NumSIMDCores = GPU__GC__NUM_SE * GPU__GC__NUM_SH_PER_SE * GPU__GC__NUM_CU_PER_SH * (CratHsaEntry->NumSIMDPerCU);
  CratHsaEntry->MaxWavesSIMD = 40;
  CratHsaEntry->LDSSizeInKB = 64;
  CratHsaEntry->WaveFrontSize = 64;
  CratHsaEntry->NumShaderBanks = GPU__GC__NUM_SE;
  CratHsaEntry->NumArrays = GPU__GC__NUM_SH_PER_SE;
  CratHsaEntry->NumCUPerArray = GPU__GC__NUM_SH_PER_SE * GPU__GC__NUM_CU_PER_SH;
  CratHsaEntry->MaxSlotsScratchCU = 32;

  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->Length: %x\n", CratHsaEntry->Length);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->Flags.Enabled: %x\n", CratHsaEntry->Flags.Enabled);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->Flags.GpuPresent: %x\n", CratHsaEntry->Flags.GpuPresent);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->Flags.CpuPresent: %x\n", CratHsaEntry->Flags.CpuPresent);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->Flags.HSAmmuPresent: %x\n", CratHsaEntry->Flags.HSAmmuPresent);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->ProcessorIdLow: %x\n", CratHsaEntry->ProcessorIdLow);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->NumSIMDPerCU: %x\n", CratHsaEntry->NumSIMDPerCU);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->NumSIMDCores: %x\n", CratHsaEntry->NumSIMDCores);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->MaxWavesSIMD: %x\n", CratHsaEntry->MaxWavesSIMD);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->LDSSizeInKB: %x\n", CratHsaEntry->LDSSizeInKB);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->WaveFrontSize: %x\n", CratHsaEntry->WaveFrontSize);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->NumShaderBanks: %x\n", CratHsaEntry->NumShaderBanks);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->NumArrays: %x\n", CratHsaEntry->NumArrays);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->NumCUPerArray: %x\n", CratHsaEntry->NumCUPerArray);
  IDS_HDT_CONSOLE (MAIN_FLOW, "CratHsaEntry->MaxSlotsScratchCU: %x\n", CratHsaEntry->MaxSlotsScratchCU);

  return EFI_SUCCESS;
}

EFI_STATUS
AmdDebugGetConfig (
  IN       DXE_AMD_NBIO_DEBUG_SERVICES_PROTOCOL     *This,
     OUT   UINT32                                   **DebugOptions
  )
{
  EFI_STATUS                           Status;
  GNB_BUILD_OPTIONS_ZP_DATA_HOB        *GnbBuildOptionsRVDataHob;

  //
  // Get information data from HOB.
  //
  Status = EfiGetSystemConfigurationTable (&gEfiHobListGuid, &GnbBuildOptionsRVDataHob);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  GnbBuildOptionsRVDataHob = GetNextGuidHob (&gGnbNbioBaseZPHobInfoGuid, GnbBuildOptionsRVDataHob);
  if (GnbBuildOptionsRVDataHob == NULL) {
    return EFI_NOT_FOUND;
  }

  *DebugOptions = (UINT32*) GnbBuildOptionsRVDataHob;
  return Status;
}

DXE_AMD_NBIO_DEBUG_SERVICES_PROTOCOL mDxeAmdNbioBaseServicesProtocol = {
  AMD_NBIO_DEBUG_OPTION_SERVICES_DXE_REVISION,
  AmdDebugGetConfig
};

EFI_STATUS
EFIAPI
AmdNbioBaseRVDxeEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;

  AGESA_TESTPOINT (TpNbioBaseDxeEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioBaseRVDxeEntry\n");
  Handle = NULL;

  if (PcdGet8 (PcdCfgIgpuContorl) != 0) {
    Status = gBS->InstallProtocolInterface (
                    &ImageHandle,
                    &gAmdIGpuAcpiCratServicesProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mIGpuCratServicesProtocol
                    );
  }

  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdNbioDebugServicesProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mDxeAmdNbioBaseServicesProtocol
                  );

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioBaseRVDxeExit\n");
  AGESA_TESTPOINT (TpNbioBaseDxeExit, NULL);
  return EFI_SUCCESS;
}

