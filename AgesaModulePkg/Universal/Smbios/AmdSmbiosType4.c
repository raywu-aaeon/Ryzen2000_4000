/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 4
 *
 * Contains code that generate SMBIOS type 4
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
#include "Porting.h"
#include "Filecode.h"
#include "Library/IdsLib.h"
#include "Library/BaseLib.h"
#include "Library/AmdBaseLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/MemoryAllocationLib.h"
#include "Protocol/Smbios.h"
#include "Protocol/AmdSmbiosServicesProtocol.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_SMBIOS_AMDSMBIOSTYPE4_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
CHAR8 ROMDATA str_ProcManufacturer[] = "Unknown";
CHAR8 ROMDATA str_ProcVersion[] = "Not Installed";

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
 *  Generate SMBIOS type 4
 *
 *  Parameters:
 *    @param[in]       Socket             Socket number
 *    @param[in]       CacheHandle        Handle of L1 L2 & L3 cache
 *    @param[in]       Smbios             Pointer to EfiSmbiosProtocol
 *    @param[in]       StdHeader          Handle to config for library and services
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
AmdAddSmbiosType4 (
  IN       UINTN                 Socket,
  IN       UINT16                CacheHandle[CpuLmaxCache],
  IN       EFI_SMBIOS_PROTOCOL  *Smbios,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINTN                             StructureSize;
  UINTN                             StringSize;
  UINTN                             TotalSize;
  EFI_STATUS                        Status;
  EFI_STATUS                        CalledStatus;
  AMD_SMBIOS_TABLE_TYPE4           *SmbiosTableType4;
  EFI_SMBIOS_STRING                *StrPtr;
  AMD_CCX_CORE_DMI_INFO             AmdCoreDmiInfo;
  AMD_CCX_SMBIOS_SERVICES_PROTOCOL *AmdSmbiosServices;

  Status = EFI_SUCCESS;

  // Calculate size of DMI type 4
  StructureSize = sizeof (AMD_SMBIOS_TABLE_TYPE4);
  TotalSize = StructureSize;
  switch (Socket) {
  case 0:
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket0));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSerialNumberSocket0));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosAssetTagSocket0));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosPartNumberSocket0));
    break;
  case 1:
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket1));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSerialNumberSocket1));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosAssetTagSocket1));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosPartNumberSocket1));
    break;
  default:
    // Only support up to 2 sockets
    ASSERT (FALSE);
  }
  TotalSize += sizeof (AmdCoreDmiInfo.ProcessorVersion);
  TotalSize += sizeof (AmdCoreDmiInfo.ProcessorManufacturer);
  ++TotalSize; // Additional null (00h), End of strings

  // Allocate zero pool
  SmbiosTableType4 = NULL;
  SmbiosTableType4 = AllocateZeroPool (TotalSize);
  if (SmbiosTableType4 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Generate DMI type 4 --- Start
  CalledStatus = gBS->LocateProtocol (&gAmdCcxSmbiosServicesProtocolGuid, NULL, (VOID **)&AmdSmbiosServices);
  if (EFI_ERROR (CalledStatus)) {
    return EFI_PROTOCOL_ERROR;
  }
  AmdSmbiosServices->GetCoreDmiInfo (AmdSmbiosServices, Socket, &AmdCoreDmiInfo);

  SmbiosTableType4->Hdr.Type             = AMD_EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION;
  SmbiosTableType4->Hdr.Length           = (UINT8) StructureSize;
  SmbiosTableType4->Hdr.Handle           = AMD_SMBIOS_HANDLE_PI_RESERVED;

  SmbiosTableType4->Socket               = 1;
  SmbiosTableType4->ProcessorManufacture = 2;
  SmbiosTableType4->ProcessorVersion     = 3;
  SmbiosTableType4->SerialNumber         = 4;
  SmbiosTableType4->AssetTag             = 5;
  SmbiosTableType4->PartNumber           = 6;

  SmbiosTableType4->ProcessorType        = AmdCoreDmiInfo.ProcessorType;
  if (AmdCoreDmiInfo.ProcessorFamily < 0xFE) {
    SmbiosTableType4->ProcessorFamily    = (UINT8) AmdCoreDmiInfo.ProcessorFamily;
    SmbiosTableType4->ProcessorFamily2   = SmbiosTableType4->ProcessorFamily;
  } else {
    SmbiosTableType4->ProcessorFamily    = 0xFE;
    SmbiosTableType4->ProcessorFamily2   = AmdCoreDmiInfo.ProcessorFamily;
  }
  *((UINT32 *) &SmbiosTableType4->ProcessorId.Signature)    = AmdCoreDmiInfo.ProcessorID.EaxFamilyId;
  *((UINT32 *) &SmbiosTableType4->ProcessorId.FeatureFlags) = AmdCoreDmiInfo.ProcessorID.EdxFeatureId;
  *((UINT8  *) &SmbiosTableType4->Voltage)                  = AmdCoreDmiInfo.Voltage;
  SmbiosTableType4->ExternalClock        = AmdCoreDmiInfo.ExternalClock;
  SmbiosTableType4->MaxSpeed             = AmdCoreDmiInfo.MaxSpeed;
  SmbiosTableType4->CurrentSpeed         = AmdCoreDmiInfo.CurrentSpeed;
  SmbiosTableType4->Status               = AmdCoreDmiInfo.Status;
  SmbiosTableType4->ProcessorUpgrade     = AmdCoreDmiInfo.ProcessorUpgrade;
  SmbiosTableType4->L1CacheHandle        = CacheHandle[CpuL1Cache];
  SmbiosTableType4->L2CacheHandle        = CacheHandle[CpuL2Cache];
  SmbiosTableType4->L3CacheHandle        = CacheHandle[CpuL3Cache];
  if (AmdCoreDmiInfo.CoreCount >= 0xFF) {
    SmbiosTableType4->CoreCount          = 0xFF;
    SmbiosTableType4->CoreCount2         = AmdCoreDmiInfo.CoreCount;
  } else {
    SmbiosTableType4->CoreCount          = (UINT8) AmdCoreDmiInfo.CoreCount;
    SmbiosTableType4->CoreCount2         = AmdCoreDmiInfo.CoreCount;
  }
  if (AmdCoreDmiInfo.CoreEnabled >= 0xFF) {
    SmbiosTableType4->EnabledCoreCount   = 0xFF;
    SmbiosTableType4->EnabledCoreCount2  = AmdCoreDmiInfo.CoreEnabled;
  } else {
    SmbiosTableType4->EnabledCoreCount   = (UINT8) AmdCoreDmiInfo.CoreEnabled;
    SmbiosTableType4->EnabledCoreCount2  = AmdCoreDmiInfo.CoreEnabled;
  }
  if (AmdCoreDmiInfo.ThreadCount >= 0xFF) {
    SmbiosTableType4->ThreadCount        = 0xFF;
    SmbiosTableType4->ThreadCount2       = AmdCoreDmiInfo.ThreadCount;
  } else {
    SmbiosTableType4->ThreadCount        = (UINT8) AmdCoreDmiInfo.ThreadCount;
    SmbiosTableType4->ThreadCount2       = AmdCoreDmiInfo.ThreadCount;
  }
  SmbiosTableType4->ProcessorCharacteristics = AmdCoreDmiInfo.ProcessorCharacteristics;
  // Generate DMI type 4 --- End


  // Append all strings
  StrPtr = (EFI_SMBIOS_STRING*) (((UINT8 *) SmbiosTableType4) + StructureSize);
  StringSize = TotalSize - StructureSize;
  switch (Socket) {
  case 0:
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket0)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        AmdCoreDmiInfo.ProcessorManufacturer
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        AmdCoreDmiInfo.ProcessorVersion
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSerialNumberSocket0)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosAssetTagSocket0)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosPartNumberSocket0)
        );
    break;
  case 1:
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket1)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        AmdCoreDmiInfo.ProcessorManufacturer
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        AmdCoreDmiInfo.ProcessorVersion
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSerialNumberSocket1)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosAssetTagSocket1)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosPartNumberSocket1)
        );
    break;
  default:
    // Only support up to 2 sockets
    ASSERT (FALSE);
  }
  // Add DMI type 4
  CalledStatus = Smbios->Add (Smbios, NULL, &SmbiosTableType4->Hdr.Handle, (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType4);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  // Free pool
  FreePool (SmbiosTableType4);

  return Status;
}


EFI_STATUS
EFIAPI
AmdAddSmbiosType4ForNoProcInstalled (
  IN       UINTN                 Socket,
  IN       UINT16                CacheHandle[CpuLmaxCache],
  IN       EFI_SMBIOS_PROTOCOL  *Smbios,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINTN                             StructureSize;
  UINTN                             StringSize;
  UINTN                             TotalSize;
  EFI_STATUS                        Status;
  EFI_STATUS                        CalledStatus;
  AMD_SMBIOS_TABLE_TYPE4           *SmbiosTableType4;
  EFI_SMBIOS_STRING                *StrPtr;

  Status = EFI_SUCCESS;

  // Calculate size of DMI type 4
  StructureSize = sizeof (AMD_SMBIOS_TABLE_TYPE4);
  TotalSize = StructureSize;
  switch (Socket) {
  case 0:
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket0));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSerialNumberSocket0));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosAssetTagSocket0));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosPartNumberSocket0));
    break;
  case 1:
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket1));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosSerialNumberSocket1));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosAssetTagSocket1));
    TotalSize += AsciiStrSize (PcdGetPtr (PcdAmdSmbiosPartNumberSocket1));
    break;
  default:
    // Only support up to 2 sockets
    ASSERT (FALSE);
  }
  TotalSize += sizeof (str_ProcVersion);
  TotalSize += sizeof (str_ProcManufacturer);
  ++TotalSize; // Additional null (00h), End of strings

  // Allocate zero pool
  SmbiosTableType4 = NULL;
  SmbiosTableType4 = AllocateZeroPool (TotalSize);
  if (SmbiosTableType4 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Generate DMI type 4 --- Start

  SmbiosTableType4->Hdr.Type             = AMD_EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION;
  SmbiosTableType4->Hdr.Length           = (UINT8) StructureSize;
  SmbiosTableType4->Hdr.Handle           = AMD_SMBIOS_HANDLE_PI_RESERVED;

  SmbiosTableType4->Socket               = 1;
  SmbiosTableType4->ProcessorManufacture = 2;
  SmbiosTableType4->ProcessorVersion     = 3;
  SmbiosTableType4->SerialNumber         = 4;
  SmbiosTableType4->AssetTag             = 5;
  SmbiosTableType4->PartNumber           = 6;

  SmbiosTableType4->ProcessorType        = 0x2;
  SmbiosTableType4->ProcessorFamily      = 0x2;
  SmbiosTableType4->ProcessorFamily2     = 0x2;
  SmbiosTableType4->ProcessorUpgrade     = 0x2;
  SmbiosTableType4->L1CacheHandle        = 0xFFFF;
  SmbiosTableType4->L2CacheHandle        = 0xFFFF;
  SmbiosTableType4->L3CacheHandle        = 0xFFFF;
  SmbiosTableType4->ProcessorCharacteristics = 0x2;
  // Generate DMI type 4 --- End


  // Append all strings
  StrPtr = (EFI_SMBIOS_STRING*) (((UINT8 *) SmbiosTableType4) + StructureSize);
  StringSize = TotalSize - StructureSize;
  switch (Socket) {
  case 0:
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket0)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        str_ProcManufacturer
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        str_ProcVersion
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSerialNumberSocket0)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosAssetTagSocket0)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosPartNumberSocket0)
        );
    break;
  case 1:
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSocketDesignationSocket1)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        str_ProcManufacturer
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        str_ProcVersion
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosSerialNumberSocket1)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosAssetTagSocket1)
        );
    Status = LibAmdInsertSmbiosString (
        &StrPtr,
        &StringSize,
        PcdGetPtr (PcdAmdSmbiosPartNumberSocket1)
        );
    break;
  default:
    // Only support up to 2 sockets
    ASSERT (FALSE);
  }
  // Add DMI type 4
  CalledStatus = Smbios->Add (Smbios, NULL, &SmbiosTableType4->Hdr.Handle, (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType4);
  Status = (CalledStatus > Status) ? CalledStatus : Status;

  // Free pool
  FreePool (SmbiosTableType4);

  return Status;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


