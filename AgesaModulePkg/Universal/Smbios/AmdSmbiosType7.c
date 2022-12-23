/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 7
 *
 * Contains code that generate SMBIOS type 7
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
#include "AmdSmbios.h"
#include "AMD.h"
#include "Filecode.h"
#include "Library/IdsLib.h"
#include "Library/BaseLib.h"
#include "Library/PrintLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/MemoryAllocationLib.h"
#include "Protocol/Smbios.h"
#include "Protocol/AmdSmbiosServicesProtocol.h"
#include "AmdSmbiosDxe.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_SMBIOS_AMDSMBIOSTYPE7_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define CACHE_LEVEL_STR_LENGTH 11
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
 *  Generate SMBIOS type 7
 *
 *    @param[in]       Socket             Socket number
 *    @param[out]      CacheHandle        Handle of L1 L2 & L3 cache
 *    @param[in]       Smbios             Pointer to EfiSmbiosProtocol
 *    @param[in]       StdHeader          Handle to config for library and services
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
AmdAddSmbiosType7 (
  IN       UINTN                 Socket,
     OUT   UINT16              (*CacheHandle)[CpuLmaxCache],
  IN       EFI_SMBIOS_PROTOCOL  *Smbios,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8                             CacheLevel;
  UINTN                             StructureSize;
  UINTN                             TotalSize;
  EFI_STATUS                        Status;
  EFI_STATUS                        CalledStatus;
  EFI_SMBIOS_STRING                 CacheLevelStr[CACHE_LEVEL_STR_LENGTH];
  EFI_SMBIOS_STRING                *StrPtr;
  AMD_SMBIOS_TABLE_TYPE7           *SmbiosTableType7;
  AMD_CACHE_DMI_INFO                AmdCacheDmiInfo;
  AMD_CCX_SMBIOS_SERVICES_PROTOCOL *AmdSmbiosServices;

  Status = EFI_SUCCESS;

  CalledStatus = gBS->LocateProtocol (&gAmdCcxSmbiosServicesProtocolGuid, NULL, (VOID **)&AmdSmbiosServices);
  if (EFI_ERROR (CalledStatus)) {
    return EFI_PROTOCOL_ERROR;
  }
  AmdSmbiosServices->GetCacheDmiInfo (AmdSmbiosServices, Socket, &AmdCacheDmiInfo);

  StructureSize = sizeof (AMD_SMBIOS_TABLE_TYPE7);
  // Version Check
  if (!AmdSmbiosVersionCheck (Smbios, 3, 1)) {
    StructureSize -= sizeof (SmbiosTableType7->MaximumCacheSize2);
    StructureSize -= sizeof (SmbiosTableType7->InstalledSize2);
  }
  TotalSize = StructureSize + CACHE_LEVEL_STR_LENGTH + 1; // +1 is for additional null (00h), End of strings


  for (CacheLevel = CpuL1Cache; CacheLevel < CpuLmaxCache; CacheLevel++) {
    if (AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].InstallSize == 0) {
      // break if cache size is 0
      break;
    }
    SmbiosTableType7 = NULL;
    SmbiosTableType7 = AllocateZeroPool (TotalSize);
    if (SmbiosTableType7 == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    // Generate DMI type 7 --- Start
    SmbiosTableType7->Hdr.Type             = AMD_EFI_SMBIOS_TYPE_CACHE_INFORMATION;
    SmbiosTableType7->Hdr.Length           = (UINT8) StructureSize;
    SmbiosTableType7->Hdr.Handle           = AMD_SMBIOS_HANDLE_PI_RESERVED;

    SmbiosTableType7->SocketDesignation    = 1;
    SmbiosTableType7->CacheConfiguration   = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].CacheCfg;
    SmbiosTableType7->MaximumCacheSize     = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].MaxCacheSize;
    SmbiosTableType7->InstalledSize        = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].InstallSize;
    *((UINT16 *) &SmbiosTableType7->SupportedSRAMType)  = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].SupportedSramType;
    *((UINT16 *) &SmbiosTableType7->CurrentSRAMType)    = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].CurrentSramType;
    SmbiosTableType7->CacheSpeed           = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].CacheSpeed;
    SmbiosTableType7->ErrorCorrectionType  = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].ErrorCorrectionType;
    SmbiosTableType7->SystemCacheType      = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].SystemCacheType;
    SmbiosTableType7->Associativity        = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].Associativity;
    if (AmdSmbiosVersionCheck (Smbios, 3, 1)) {
      SmbiosTableType7->MaximumCacheSize2  = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].MaxCacheSize2;
      SmbiosTableType7->InstalledSize2     = AmdCacheDmiInfo.CacheEachLevelInfo[CacheLevel].InstallSize2;
    }
    // Generate DMI type 7 --- End

    // Append all strings
    AsciiSPrint (CacheLevelStr, CACHE_LEVEL_STR_LENGTH, "L%d - Cache", (CacheLevel + 1));
    StrPtr = (EFI_SMBIOS_STRING*) (((UINT8 *) SmbiosTableType7) + StructureSize);
    Status = AsciiStrCatS (StrPtr, CACHE_LEVEL_STR_LENGTH, CacheLevelStr);

    // Add DMI type 7
    CalledStatus = Smbios->Add (Smbios, NULL, &SmbiosTableType7->Hdr.Handle, (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType7);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
    if (!EFI_ERROR (CalledStatus)) {
      (*CacheHandle)[CacheLevel] = SmbiosTableType7->Hdr.Handle;
    }

    // Free pool
    FreePool (SmbiosTableType7);
  }

  return Status;
}


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


