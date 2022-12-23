/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 4 7 16 17 18 19 20
 *
 * Contains code that generate SMBIOS type 4 7 16 17 18 19 20
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
#include "AMD.h"
#include "Filecode.h"
#include "Library/AmdBaseLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/IdsLib.h"
#include "Protocol/Smbios.h"
#include <MemDmi.h>
#include "Protocol/AmdSmbiosCompleteProtocol.h"
#include "Protocol/AmdSmbiosServicesProtocol.h"
#include "Protocol/FabricTopologyServices2.h"
#include "AmdSmbiosDxe.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_SMBIOS_AMDSMBIOSDXE_FILECODE

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
 *  Entry for AmdSmbiosDxe
 *  Generate SMBIOS type 4 7 16 17 18 19 20
 *
 *  Description:
 *    This function will populate SMBIOS with
 *      type  4: Processor Information
 *      type  7: Cache Information
 *      type 16: Physical Memory Array
 *      type 17: Memory Device
 *      type 18: Memory Error Information
 *      type 19: Memory Array Mapped Address
 *      type 20: Memory Device Mapped Address
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
AmdGenerateSmbios (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  UINT16                     CacheHandle[CpuLmaxCache];
  UINT8                      Socket;
  UINT8                      Channel;
  UINT8                      Dimm;
  UINTN                      NumberOfInstalledProcessors;
  UINTN                      NumberOfDie;
  EFI_SMBIOS_HANDLE          ArrayHandle;
  EFI_SMBIOS_HANDLE          ArrayMappedHandle;
  EFI_SMBIOS_HANDLE          ArrayErrorHandle;
  EFI_SMBIOS_HANDLE          DeviceHandle;
  EFI_STATUS                 Status;
  EFI_STATUS                 CalledStatus;
  EFI_SMBIOS_PROTOCOL       *Smbios;
  DMI_INFO                   MemDmiInfo;
  EFI_HANDLE                 Handle;
  AMD_CONFIG_PARAMS          StdHeader;
  DXE_AMD_SMBIOS_INIT_COMPLETE_PROTOCOL AmdSmbiosInitCompleteProtocol;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  AMD_MEM_SMBIOS_SERVICES_PROTOCOL *AmdMemSmbiosServices;
  UINT8                      RegionIndex;

  AGESA_TESTPOINT (TpUniversalSmbiosEntry, NULL);

  IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdGenerateSmbios Entry\n");

  // Check PCD
  if (PcdGetBool (PcdAmdRemoveSmbios)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "  Smbios is disabled by user, exit\n");
    AGESA_TESTPOINT (TpUniversalSmbiosAbort, NULL);
    return EFI_UNSUPPORTED;
  }

  // Avoid re-entry by locating gAmdSmbiosDxeInitCompleteProtocolGuid.
  CalledStatus = gBS->LocateProtocol (&gAmdSmbiosDxeInitCompleteProtocolGuid, NULL, (VOID **)&AmdSmbiosInitCompleteProtocol);
  if (CalledStatus == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "    re-entry, just return EFI_ALREADY_STARTED\n");
    AGESA_TESTPOINT (TpUniversalSmbiosAbort, NULL);
    return EFI_ALREADY_STARTED;
  }
  Status = EFI_SUCCESS;

  // Locate Smbios protocol
  gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &Smbios);
  IDS_HDT_CONSOLE (MAIN_FLOW, "  SMBIOS Version: %x.%x\n", Smbios->MajorVersion, Smbios->MinorVersion);

  CalledStatus = gBS->LocateProtocol (&gAmdMemSmbiosServicesProtocolGuid, NULL, (VOID **)&AmdMemSmbiosServices);
  if (EFI_ERROR (CalledStatus)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdMemSmbiosServices not found.\n");
    AGESA_TESTPOINT (TpUniversalSmbiosAbort, NULL);
    return EFI_PROTOCOL_ERROR;
  }
  CalledStatus = AmdMemSmbiosServices->GetMemDmiInfo (AmdMemSmbiosServices, &MemDmiInfo);
  if (EFI_ERROR (CalledStatus)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "  Error invoking AmdMemSmbiosServices.\n");
    AGESA_TESTPOINT (TpUniversalSmbiosAbort, NULL);
    return EFI_PROTOCOL_ERROR;
  }

  // Locate FabricTopologyServicesProtocol
  gBS->LocateProtocol (&gAmdFabricTopologyServices2ProtocolGuid, NULL, (VOID **) &FabricTopology);
  FabricTopology->GetSystemInfo (FabricTopology, &NumberOfInstalledProcessors, &NumberOfDie, NULL, NULL, NULL);

  // Add Memory Types
  CalledStatus = AmdAddSmbiosType18 (Smbios, &ArrayErrorHandle, &StdHeader);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  CalledStatus = AmdAddSmbiosType16 (Smbios, &MemDmiInfo, ArrayErrorHandle, &ArrayHandle, &StdHeader);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  ArrayMappedHandle = 0;
  for (RegionIndex = 0; RegionIndex < MAX_T19_REGION_SUPPORTED; RegionIndex++) {
    CalledStatus = AmdAddSmbiosType19 (Smbios, &MemDmiInfo, ArrayHandle, &ArrayMappedHandle, &StdHeader, RegionIndex);
  }
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  for (Socket = 0; Socket < NumberOfInstalledProcessors; Socket++) {
    // Initialize CacheHandle with 0xFFFF
    LibAmdMemFill (CacheHandle, 0xFF, sizeof (UINT16) * CpuLmaxCache, &StdHeader);

    // Add type 7 first, to get handle
    CalledStatus = AmdAddSmbiosType7 (Socket, &CacheHandle, Smbios, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Add type 4
    CalledStatus = AmdAddSmbiosType4 (Socket, CacheHandle, Smbios, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    for (Channel = 0; Channel < MAX_CHANNELS_PER_SOCKET; Channel++) {
      for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm++) {
        CalledStatus = AmdAddSmbiosType17 (Smbios, &MemDmiInfo, Socket, Channel, Dimm, ArrayHandle, 0xFFFF, &DeviceHandle, &StdHeader);
        Status = (CalledStatus > Status) ? CalledStatus : Status;

        CalledStatus = AmdAddSmbiosType20 (Smbios, &MemDmiInfo, Socket, Channel, Dimm, DeviceHandle, ArrayMappedHandle, &StdHeader);
        Status = (CalledStatus > Status) ? CalledStatus : Status;
      }
    }
  }

  if (NumberOfInstalledProcessors < PcdGet8 (PcdAmdNumberOfPhysicalSocket)) {
    for (Socket = (UINT8) NumberOfInstalledProcessors; Socket < PcdGet8 (PcdAmdNumberOfPhysicalSocket); Socket++) {
      AmdAddSmbiosType4ForNoProcInstalled (Socket, CacheHandle, Smbios, &StdHeader);
    }
  }

  // Install Protocol gAmdSmbiosDxeInitCompleteProtocolGuid to avoid re-entry
  IDS_HDT_CONSOLE (MAIN_FLOW, "  Install Protocol gAmdSmbiosDxeInitCompleteProtocolGuid to avoid re-entry\n");
  AmdSmbiosInitCompleteProtocol.Revision = 311;
  Handle = NULL;
  gBS->InstallProtocolInterface (
                          &Handle,
                          &gAmdSmbiosDxeInitCompleteProtocolGuid,
                          EFI_NATIVE_INTERFACE,
                          &AmdSmbiosInitCompleteProtocol
                          );

  IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdGenerateSmbios Exit\n");

  AGESA_TESTPOINT (TpUniversalSmbiosExit, NULL);

  return Status;
}


/**
 *---------------------------------------------------------------------------------------
 *
 *  Check if kernel code support SMBIOS version x.x
 *
 *  Parameters:
 *    @param[in]       Smbios                       Pointer to EfiSmbiosProtocol
 *    @param[in]       MajorVersion                 Major version
 *    @param[in]       MinorVersion                 Minor version

 *    @retval          TRUE  - version x.x is supported
 *                     FALSE - version x.x is not supported
 *
 *---------------------------------------------------------------------------------------
 */
BOOLEAN
AmdSmbiosVersionCheck (
  IN       EFI_SMBIOS_PROTOCOL *Smbios,
  IN       UINT8                MajorVersion,
  IN       UINT8                MinorVersion
  )
{
  if ((Smbios->MajorVersion > MajorVersion) ||
      ((Smbios->MajorVersion == MajorVersion) && (Smbios->MinorVersion >= MinorVersion))) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


