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
 ******************************************************************************
 */

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

#include "Library/BaseLib.h"
#include "Library/BaseMemoryLib.h"
#include "Library/DebugLib.h"
#include "IndustryStandard/Acpi.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/UefiRuntimeServicesTableLib.h"
#include "Library/AmdBaseLib.h"
#include "Protocol/AcpiTable.h"
#include "Protocol/FirmwareVolume2.h"
#include "Protocol/AmdNbioSmuServicesProtocol.h"
#include "Library/NbioHandleLib.h"
#include "Library/NbioSmuV9Lib.h"
#include "Library/ApobCommonServiceLib.h"

#include "../Aod.h"
#include <AmdSoc.h>



EFI_BOOT_SERVICES                 *gBS;

// 8E1C914F-82F6-4AD6-BAE2-C1A33B19B9B1
EFI_GUID AOD_SSDT_GUID = {
  0x8E1C914F, 0x82F6, 0x4AD6, 0xBA, 0xE2, 0xC1, 0xA3, 0x3B, 0x19, 0xB9, 0xB1
};

extern EFI_GUID gAodNvAreaUpdatedProtocolGuid;


EFI_STATUS
UpdateAodSsdt (
  IN OUT EFI_ACPI_DESCRIPTION_HEADER      *TableHeader
);

BOOLEAN
IsOpRegionObj (
  IN UINT8               *SsdtPointer
  )
{
  UINT16                 *Operation = NULL;

  Operation = (UINT16*)(SsdtPointer - 2);
  if (*Operation == 0x805B ) {
    return TRUE;
  }

  return FALSE;
};

BOOLEAN
IsPackageObj (
  IN UINT8               *SsdtPointer
  )
{
  if (* (UINT8 *) (SsdtPointer + 4) == 0x12 ) {
    return TRUE;
  }

  return FALSE;
};


EFI_STATUS
UpdateOpRegion (
  IN UINT8               *SsdtPointer,
  IN VOID*               RegionStartAddress,
  IN UINT32              RegionSize
  )
{
  UINT8                         AddressPrefix;
  UINT32                        *Address;
  UINT32                        *DwordSize;
  UINT8                         SizePrefix;
  UINT16                        *WordSize;
  UINT8                         *ByteSize;

  AddressPrefix = *(SsdtPointer + 5);
  ASSERT (AddressPrefix == 0x0C);
  Address = (UINT32*) (SsdtPointer + 6);
  ASSERT ((((UINTN)RegionStartAddress) & 0xFFFFFFFF) == (UINTN)RegionStartAddress);
  *Address = (UINT32)(UINTN)RegionStartAddress;
  SizePrefix = *(SsdtPointer + 10);
  if (SizePrefix == 0x0C) {
    DwordSize = (UINT32*) (SsdtPointer + 11);
    *DwordSize = RegionSize;
  } else if (SizePrefix == 0x0B) {
    ASSERT (RegionSize < 0x10000);
    RegionSize &= 0xFFFF;
    WordSize = (UINT16*) (SsdtPointer + 11);
    *WordSize = (UINT16) RegionSize;
  } else if (SizePrefix == 0x0A) {
    ASSERT (RegionSize < 0x100);
    RegionSize &= 0xFF;
    ByteSize = (UINT8*) (SsdtPointer + 11);
    *ByteSize = (UINT8) RegionSize;
  } else {
    ASSERT (FALSE);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
UpdateOpValue (
  IN  UINT8               *SsdtPointer,
  IN  UINT32              Value,
  OUT UINT8               *Size
  )
{
  UINT8                         SizePrefix;

  SizePrefix = *SsdtPointer;
  if (SizePrefix == 0x0C) {
    if (Value) {
      * (UINT32 *) (SsdtPointer + 1) = Value;
    }
    *Size = 4;
  } else if (SizePrefix == 0x0B) {
    if (Value) {
      * (UINT16 *) (SsdtPointer + 1) = (UINT16) Value;
    }
    *Size = 2;
  } else if (SizePrefix == 0x0A) {
    if (Value) {
      * (UINT8 *) (SsdtPointer + 1) = (UINT8) Value;
    }
    *Size = 1;
  } else {
    // no prefix
    if (Value) {
      * (UINT8 *) (SsdtPointer + 1) = (UINT8) Value;
    }
    *Size = 1;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetOpValue (
  IN  UINT8               *SsdtPointer,
  IN  UINT32              *Value,
  OUT UINT8               *Size
  )
{
  UINT8                         SizePrefix;

  SizePrefix = *SsdtPointer;
  if (SizePrefix == 0x0C) {
    *Value = * (UINT32 *) (SsdtPointer + 1);
    *Size = 4;
  } else if (SizePrefix == 0x0B) {
    *Value = * (UINT16 *) (SsdtPointer + 1);
    *Size = 2;
  } else if (SizePrefix == 0x0A) {
    *Value = * (UINT8 *) (SsdtPointer + 1);
    *Size = 1;
  } else {
    // no prefix
    *Value = * (UINT8 *) (SsdtPointer + 1);
    *Size = 1;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
UpdateObit (
  IN UINT8               *SsdtPointer,
  IN UINT8               *EndAddress
  )
{
  UINT16 SetVddioMin;
  UINT16 SetVddioMax;
  UINT16 SetVddioStepping;
  UINT32 PackageSize;
  UINT32 Index;
  UINT8  Size;

  SetVddioMin = PcdGet16 (PcdMemVddioMin);
  SetVddioMax = PcdGet16 (PcdMemVddioMax);
  SetVddioStepping = PcdGet16 (PcdMemVddioStepping);

  if ((SetVddioMin == 0) && (SetVddioMax == 0) && (SetVddioStepping == 0)) {
    // Use build time values
    return EFI_SUCCESS;
  }

  DEBUG ((EFI_D_ERROR, "    PackageLengthBytes = %x %x %x\n", * (UINT8 *) (SsdtPointer + 5), * (UINT8 *) (SsdtPointer + 6), * (UINT8 *) (SsdtPointer + 7)));

  PackageSize = 0;
  if ((* (UINT8 *) (SsdtPointer + 5) & 0xC0) == 0) {
    // PkgLeadByte [7:6] = 00b, then package length is encoded with bit [5:0]
    PackageSize = * (UINT8 *) (SsdtPointer + 5) & 0x3F;
  } else if ((* (UINT8 *) (SsdtPointer + 5) & 0xF0) == 0x40) {
    // PkgLeadByte [7:6] = 01b, then bit[5:4] must be 0, package length is encoded with (next byte << 4) + bit [3:0]
    PackageSize = (* (UINT8 *) (SsdtPointer + 5) & 0xF) + (((UINT32) (* (UINT8 *) (SsdtPointer + 6))) << 4);
  } else if ((* (UINT8 *) (SsdtPointer + 5) & 0xF0) == 0xC0) {
    // PkgLeadByte [7:6] = 11b, then bit[5:4] must be 0, package length is encoded with (next next byte << 12) + (next byte << 4) + bit [3:0]
    PackageSize = (* (UINT8 *) (SsdtPointer + 5) & 0xF) + (((UINT32) (* (UINT8 *) (SsdtPointer + 6))) << 4) + (((UINT32)(* (UINT8 *) (SsdtPointer + 7))) << 12);
  }
  DEBUG ((EFI_D_ERROR, "    PackageSize = %x\n", PackageSize));

  Index = 0;
  while ((SsdtPointer < EndAddress) && (Index < PackageSize)) {
    if (* (UINT32 *) SsdtPointer == 0x00030001) {  // Set VDDIO Command ID
      DEBUG ((EFI_D_ERROR, "    Found VDDIO Command ID: Addr=%x, Min=%x, Max=%x, Step=%x\n", (UINT32) SsdtPointer, SetVddioMin, SetVddioMax, SetVddioStepping));
      SsdtPointer += 4;

      // Override Min
      UpdateOpValue (SsdtPointer, SetVddioMin, &Size);
      SsdtPointer = SsdtPointer + Size + 1;

      // Override Max
      UpdateOpValue (SsdtPointer, SetVddioMax, &Size);
      SsdtPointer = SsdtPointer + Size + 1;

      // Override Stepping
      UpdateOpValue (SsdtPointer, SetVddioStepping, &Size);
      SsdtPointer = SsdtPointer + Size + 1;

      return EFI_SUCCESS;  // Break out after found the command ID
    }
    SsdtPointer ++;
    Index ++;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
UpdateObd2 (
  IN UINT8               *SsdtPointer,
  IN UINT8               *EndAddress
  )
{
  UINT16 SetVddioMin;
  UINT16 SetVddioMax;
  UINT16 SetVddioStepping;
  UINT32 PackageSize;
  UINT32 Index, Loop;
  UINT8  Size;
  UINT32 ItemNum;

  ItemNum = 0;
  SetVddioMin = PcdGet16 (PcdMemVddioMin);
  SetVddioMax = PcdGet16 (PcdMemVddioMax);
  SetVddioStepping = PcdGet16 (PcdMemVddioStepping);

  if ((SetVddioMin == 0) && (SetVddioMax == 0) && (SetVddioStepping == 0)) {
    // Use build time values
    return EFI_SUCCESS;
  }

  DEBUG ((EFI_D_ERROR, "    PackageLengthBytes = %x %x %x\n", * (UINT8 *) (SsdtPointer + 5), * (UINT8 *) (SsdtPointer + 6), * (UINT8 *) (SsdtPointer + 7)));

  PackageSize = 0;
  if ((* (UINT8 *) (SsdtPointer + 5) & 0xC0) == 0) {
    // PkgLeadByte [7:6] = 00b, then package length is encoded with bit [5:0]
    PackageSize = * (UINT8 *) (SsdtPointer + 5) & 0x3F;
  } else if ((* (UINT8 *) (SsdtPointer + 5) & 0xF0) == 0x40) {
    // PkgLeadByte [7:6] = 01b, then bit[5:4] must be 0, package length is encoded with (next byte << 4) + bit [3:0]
    PackageSize = (* (UINT8 *) (SsdtPointer + 5) & 0xF) + (((UINT32) (* (UINT8 *) (SsdtPointer + 6))) << 4);
  } else if ((* (UINT8 *) (SsdtPointer + 5) & 0xF0) == 0xC0) {
    // PkgLeadByte [7:6] = 11b, then bit[5:4] must be 0, package length is encoded with (next next byte << 12) + (next byte << 4) + bit [3:0]
    PackageSize = (* (UINT8 *) (SsdtPointer + 5) & 0xF) + (((UINT32) (* (UINT8 *) (SsdtPointer + 6))) << 4) + (((UINT32)(* (UINT8 *) (SsdtPointer + 7))) << 12);
  }
  DEBUG ((EFI_D_ERROR, "    PackageSize = %x\n", PackageSize));

  Index = 0;
  while ((SsdtPointer < EndAddress) && (Index < PackageSize)) {
    if (* (UINT32 *) SsdtPointer == 0x00030001) {  // Set VDDIO Command ID
      DEBUG ((EFI_D_ERROR, "    Found VDDIO Command ID: Addr=%x, Min=%x, Max=%x, Step=%x\n", (UINT32) SsdtPointer, SetVddioMin, SetVddioMax, SetVddioStepping));
      SsdtPointer += 4;

      GetOpValue (SsdtPointer, &ItemNum, &Size);
      SsdtPointer = SsdtPointer + Size + 1;
      DEBUG ((EFI_D_ERROR, "    Item Num = %x\n", ItemNum));

      if (ItemNum != (UINT32) ((SetVddioMax - SetVddioMin) / SetVddioStepping) + 1) {
        // Fix me
        return EFI_SUCCESS;
      }

      for (Loop = 0; Loop < ItemNum; Loop ++) {
        UpdateOpValue (SsdtPointer, SetVddioMin + SetVddioStepping * Loop, &Size);
        SsdtPointer = SsdtPointer + Size + 1;
      }

      return EFI_SUCCESS;  // Break out after found the command ID
    }
    SsdtPointer ++;
    Index ++;
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
InstallAodSsdtTable (
  IN       VOID                                *EfiGuid,
  IN       UINT64                              *OemTableId
  )
{
  EFI_ACPI_TABLE_PROTOCOL             *AcpiSupport;
  UINTN                               TableList;
  EFI_STATUS                          Status;
  EFI_GUID                            *EfiGuidPtr;
  EFI_HANDLE                          *HandleBuffer;
  UINTN                               NumberOfHandles;
  UINTN                               Index;
  EFI_FIRMWARE_VOLUME2_PROTOCOL       *FwVol;
  UINTN                               Size;
  UINT32                              FvStatus;
  EFI_FV_FILETYPE                     FileType;
  EFI_FV_FILE_ATTRIBUTES              Attributes;
  INTN                                Instance;
  EFI_ACPI_COMMON_HEADER              *CurrentTable;
  UINT64                              TableId;

  CurrentTable  = NULL;
  TableList     = 0;
  EfiGuidPtr    = (EFI_GUID*) EfiGuid;
  FwVol         = NULL;
  Size          = 0;

  //
  // Locate protocol.
  // There is little chance we can't find an FV protocol
  //
  Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gEfiFirmwareVolume2ProtocolGuid,
                    NULL,
                    &NumberOfHandles,
                    &HandleBuffer
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Looking for FV with ACPI storage file
  //
  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiFirmwareVolume2ProtocolGuid,
                    (VOID**)&FwVol
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    //
    // See if it has the ACPI storage file
    //
    Size     = 0;
    FvStatus = 0;
    Status = FwVol->ReadFile (
                    FwVol,
                    EfiGuidPtr,
                    NULL,
                    &Size,
                    &FileType,
                    &Attributes,
                    &FvStatus
                    );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //
  // Free any allocated buffers
  //
  gBS->FreePool (HandleBuffer);

  //
  // Sanity check that we found our data file
  //
  ASSERT (FwVol);
  ASSERT (Status == EFI_SUCCESS);

  //
  // Read tables from the storage file.
  //

  Instance     = 0;
  CurrentTable = NULL;

  while (Status == EFI_SUCCESS) {
    Status = FwVol->ReadSection (
                    FwVol,
                    EfiGuidPtr,
                    EFI_SECTION_RAW,
                    Instance,
                    (VOID**)&CurrentTable,
                    &Size,
                    &FvStatus
                    );

    if (!EFI_ERROR (Status)) {
      TableId = ((EFI_ACPI_DESCRIPTION_HEADER*) CurrentTable)->OemTableId;
      if (*((UINT32 *) CurrentTable) == 'TDSS' && (OemTableId ? TableId == *OemTableId: TRUE)) {
        DEBUG ((EFI_D_ERROR, "    Found SSDT\n"));
        break;
      }

      //
      // Increment the instance
      //
      Instance++;
      CurrentTable = NULL;
    }
  }

  Status = gBS->LocateProtocol (
                    &gEfiAcpiTableProtocolGuid,
                    NULL,
                    (VOID**)&AcpiSupport
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  TableList = 0;


  UpdateAodSsdt ((EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable);


  //CpmSetAcpiTable (AcpiSupport, CurrentTable, TRUE, AMD_CPM_ACPI_VERSION_SUPPORT, Size, TableList, Status);
  Status = AcpiSupport->InstallAcpiTable (
            AcpiSupport,
            CurrentTable,
            Size,
            &TableList);

  if (CurrentTable) {
    Status = gBS->FreePool (CurrentTable);
  }

  return  Status;
}

BOOLEAN
AodFamilyIdentifyZp (
  )
{
  UINT32     EAX_Reg;
  UINT32     EBX_Reg;
  UINT32     ECX_Reg;
  UINT32     EDX_Reg;
  UINT64     SocFamilyID;

  AsmCpuid (
      0x80000001,
      &EAX_Reg,
      &EBX_Reg,
      &ECX_Reg,
      &EDX_Reg
      );
  SocFamilyID = EAX_Reg & RAW_FAMILY_ID_MASK;
  if (SocFamilyID == F17_ZP_RAW_ID) {
    return TRUE;
  }
  return FALSE;

}


EFI_STATUS
UpdateAodSsdt (
  IN OUT EFI_ACPI_DESCRIPTION_HEADER      *TableHeader
)
{
  UINT8                               *SsdtPointer;
  UINT32                              *Signature;
  EFI_STATUS                           Status;
  UINTN                                BufferSize;
  AodNvAreaStruct                     *AodNvAreaBufferPtr;
  AodCpuBiosStruct                    *AodCpuBiosStructPtr;
  AOD_NV_AREA_UPDATED_PROTOCOL        *AodNvAreaUpdatedProtocolPtr;
  EFI_HANDLE                           Handle = NULL;
  UINT32                               RegEbx;
  UINT32                               RegEcx;
  UINT8                                Index;
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *NbioSmuServiceProtocolPtr;
  UINT32                               SmuArg[6];
  UINT16                               ElementSizeInByte;
  UINT64                               ElementValue;
  UINT32                               NumberOfValidThresholds;
  EDC_THROTTLE_THRESHOLD               *Thresholds;
  UINT8                                DieNum;

  DEBUG ((EFI_D_ERROR, "  UpdateAodSsdt:\n"));

  // Update OemId and OemTableId
  LibAmdMemCopy (
    (VOID *) &TableHeader->OemId,
    (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
    AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6),
    (AMD_CONFIG_PARAMS *)NULL
    );

  LibAmdMemCopy (
    (VOID *) &TableHeader->OemTableId,
    (VOID *) PcdGetPtr (PcdAmdAodHeaderOemTableId),
    AsciiStrnLenS (PcdGetPtr (PcdAmdAodHeaderOemTableId), 8),
    NULL
    );

  // Init AodMemBuffer
  BufferSize = sizeof (AodNvAreaStruct);
  Status = gBS->AllocatePool (
                  EfiACPIMemoryNVS,
                  BufferSize,
                  &AodNvAreaBufferPtr
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  DEBUG ((EFI_D_INFO, "  Allocate AodNvAreaStruct at: 0x%x\n", AodNvAreaBufferPtr));
  ZeroMem (AodNvAreaBufferPtr, BufferSize);
  AodNvAreaBufferPtr->AodMemBuffer.Version = 0x4;

  for (SsdtPointer = (UINT8 *)((UINTN)TableHeader + sizeof (EFI_ACPI_DESCRIPTION_HEADER)); SsdtPointer <= (UINT8 *)((UINTN)TableHeader + (UINTN)(TableHeader->Length)); SsdtPointer++) {
    Signature = (UINT32*) SsdtPointer;

    switch (*Signature) {
      case (SIGNATURE_32 ('A', 'O', 'D', 'T')):
        if (IsOpRegionObj (SsdtPointer)) {
          DEBUG ((EFI_D_ERROR, "  Update AODT Base = 0x%x, Size = 0x%x\n", (UINT32) (UINTN) AodNvAreaBufferPtr, sizeof (AodMemoryBufferStruct)));
          UpdateOpRegion (SsdtPointer, AodNvAreaBufferPtr, sizeof (AodNvAreaStruct));
        }
        break;

      case (SIGNATURE_32 ('O', 'B', 'I', 'T')):
        if (IsPackageObj (SsdtPointer)) {
          DEBUG ((EFI_D_ERROR, "  Find OBIT Package\n"));
          UpdateObit (SsdtPointer, (UINT8 *)((UINTN)TableHeader + (UINTN)(TableHeader->Length)));
        }
        break;

      case (SIGNATURE_32 ('O', 'B', 'D', '2')):
        if (IsPackageObj (SsdtPointer)) {
          DEBUG ((EFI_D_ERROR, "  Find OBD2 Package\n"));
          UpdateObd2 (SsdtPointer, (UINT8 *)((UINTN)TableHeader + (UINTN)(TableHeader->Length)));
        }
        break;


      default:
        break;
    }
  }

  // Init AodCpuBiosStruct
  BufferSize = sizeof (AodCpuBiosStruct);
  Status = gBS->AllocatePool (
                  EfiACPIMemoryNVS,
                  BufferSize,
                  &AodCpuBiosStructPtr
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  DEBUG ((EFI_D_INFO, "  Allocate AodCpuBiosStruct at: 0x%x\n", AodCpuBiosStructPtr));
  ZeroMem (AodCpuBiosStructPtr, BufferSize);
  AodCpuBiosStructPtr->Version = 0x4;
  AodCpuBiosStructPtr->OcDisable = PcdGetBool (PcdOcDisable);
  AodCpuBiosStructPtr->OcVoltageMax = PcdGet16 (PcdOcVoltageMax);
  AodCpuBiosStructPtr->OcFrequencyMax = PcdGet16 (PcdOcFrequencyMax);
  AodCpuBiosStructPtr->PptPlatformPCD = PcdGet32 (PcdAmdcTDP);
  AodCpuBiosStructPtr->TdcPlatformPCD = PcdGet32 (PcdCfgTDC);
  AodCpuBiosStructPtr->EdcPlatformPCD = PcdGet32 (PcdCfgEDC);
  AodCpuBiosStructPtr->MemVddioStepping = PcdGet16 (PcdMemVddioStepping);

  // Get SMT enable/disable info from CPUIDx8000001E_EBX[15:8]: 0 SMT off, 1 SMT on
  AsmCpuid (0x8000001E, NULL, &RegEbx, &RegEcx, NULL);
  AodCpuBiosStructPtr->SmtEnabled = ((RegEbx >> 8) & 0xFF) ? 1 : 0;
  // CPUIDx8000001E_ECX[10:8]: NodesPerProcessor - 1
  DieNum = ((RegEcx >> 8) & 0x7) + 1;

  // Get Core count from CPUIDx80000008_ECX[7:0]: number of threads - 1
  AsmCpuid (0x80000008, NULL, NULL, &RegEcx, NULL);
  RegEcx &= 0xFF;
  RegEcx += 1;
  AodCpuBiosStructPtr->ActiveCoreNum = (AodCpuBiosStructPtr->SmtEnabled ? (UINT16) (RegEcx / 2) : (UINT16) RegEcx) / DieNum;

  //Check if APOB type exist
  Status = ApobGetMemGenInfoElement (0, MemCtrllerProcOdtDddr4Current, &ElementSizeInByte, &ElementValue);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "  APOB_MEM_GENERAL_CONFIGURATION_INFO_TYPE is not found\n"));
  } else {
    ApobGetMemGenInfoElement(0, MemCtrllerProcOdtDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->procODT = (UINT16) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerRttNomDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->RttNom = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerRttWrDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->RttWR = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerRttParkDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->RttPark = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerAddrCmdSetupDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->AddrCmdSetup = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerCsOdtSetupDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->CsOdtSetup = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerCkeSetupDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->CkeSetup = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerCadBusAddrCmdDrvStrenDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->CadBusAddrDrvStren = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerCadBusClkDrvStrenDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->CadBusClkDrvStren = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerCsOdtCmdDrvStrenDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->CadBusCsOdtCmdDrvStren = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, MemCtrllerCkeDrvStrenDddr4Current, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->CadBusCkeDrvStren = (UINT8) ElementValue;

    ApobGetMemGenInfoElement(0, InterLeaveCapability, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->MemInterleavingCap = (UINT32) ElementValue;

    ApobGetMemGenInfoElement(0, InterLeaveCurrentMode, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->MemInterleavingMode = (UINT32) ElementValue;

    ApobGetMemGenInfoElement(0, InterLeaveSize, &ElementSizeInByte, &ElementValue);
    AodCpuBiosStructPtr->InterleavingSize = (UINT32) ElementValue;


    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->procODT: 0x%x\n", AodCpuBiosStructPtr->procODT));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->RttNom: 0x%x\n", AodCpuBiosStructPtr->RttNom));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->RttWR: 0x%x\n", AodCpuBiosStructPtr->RttWR));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->RttPark: 0x%x\n", AodCpuBiosStructPtr->RttPark));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->AddrCmdSetup: 0x%x\n", AodCpuBiosStructPtr->AddrCmdSetup));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->CsOdtSetup: 0x%x\n", AodCpuBiosStructPtr->CsOdtSetup));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->CkeSetup: 0x%x\n", AodCpuBiosStructPtr->CkeSetup));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->CadBusAddrDrvStren: 0x%x\n", AodCpuBiosStructPtr->CadBusAddrDrvStren));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->CadBusClkDrvStren: 0x%x\n", AodCpuBiosStructPtr->CadBusClkDrvStren));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->CadBusCsOdtCmdDrvStren: 0x%x\n", AodCpuBiosStructPtr->CadBusCsOdtCmdDrvStren));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->CadBusCkeDrvStren: 0x%x\n", AodCpuBiosStructPtr->CadBusCkeDrvStren));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->MemInterleavingCap: 0x%x\n", AodCpuBiosStructPtr->MemInterleavingCap));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->MemInterleavingMode: 0x%x\n", AodCpuBiosStructPtr->MemInterleavingMode));
    DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->InterleavingSize: 0x%x\n", AodCpuBiosStructPtr->InterleavingSize));
  }

  Status = ApobGetNumberOfValidThresholds (0, &NumberOfValidThresholds);
  if (Status != EFI_SUCCESS) {
    DEBUG ((EFI_D_ERROR, "  APOB_CCX_EDC_THROTTLE_THRESH_TYPE is not found\n"));
  } else {
    DEBUG ((EFI_D_INFO, "  ApobEdcThrottleThresholdInfoStructPtr->NumberOfValidThresholds: 0x%x\n", NumberOfValidThresholds));
    for (Index = 0; Index < NumberOfValidThresholds; Index++) {
      ApobGetThresholds (0, Index, &Thresholds);
      DEBUG ((EFI_D_INFO, "    ApobEdcThrottleThresholdInfoStructPtr->Thresholds[%d].Type: 0x%x\n", Index, Thresholds->Type));
      DEBUG ((EFI_D_INFO, "    ApobEdcThrottleThresholdInfoStructPtr->Thresholds[%d].OpnValue: 0x%x\n", Index, Thresholds->OpnValue));
      DEBUG ((EFI_D_INFO, "    ApobEdcThrottleThresholdInfoStructPtr->Thresholds[%d].AblProgrammedValue: 0x%x\n", Index, Thresholds->AblProgrammedValue));
      if (Thresholds->Type == EDC_THROTTLE_TYPE_CORE) {
        AodCpuBiosStructPtr->EdcThrottlerCtrl = (UINT8) Thresholds->AblProgrammedValue;
        AodCpuBiosStructPtr->EdcThrottlerCtrlOpnValue = (UINT8) Thresholds->OpnValue;
      }
    }
  }

  if (AodFamilyIdentifyZp()) {
    // Read Tctl from SMU message
    Status = gBS->LocateProtocol (
                 &gAmdNbioSmuServicesProtocolGuid,
                 NULL,
                 (VOID **)&NbioSmuServiceProtocolPtr
                 );

    if (Status == EFI_SUCCESS) {
        SmuArg[0] = 0;
        SmuArg[1] = 0;
        SmuArg[2] = 0;
        SmuArg[3] = 0;
        SmuArg[4] = 0;
        SmuArg[5] = 0;
        NbioSmuServiceProtocolPtr->AmdSmuServiceRequest (NbioSmuServiceProtocolPtr, 0, SMC_MSG_TCTL_OFFSET, SmuArg, SmuArg);
        AodCpuBiosStructPtr->TempOffset = (INT32) SmuArg[0];
        DEBUG ((EFI_D_INFO, "  AodCpuBiosStructPtr->TempOffset: %d\n", AodCpuBiosStructPtr->TempOffset));
    }
  } else {
    AodCpuBiosStructPtr->TempOffset = 0;
    DEBUG ((EFI_D_INFO, "  Non-ZP Family: AodCpuBiosStructPtr->TempOffset: %d\n", AodCpuBiosStructPtr->TempOffset));
  }

  // Install gPlatformSsdtInstalledProtocolGuid Protocol
  BufferSize = sizeof (AOD_NV_AREA_UPDATED_PROTOCOL);
  Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  BufferSize,
                  &AodNvAreaUpdatedProtocolPtr
                  );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  AodNvAreaUpdatedProtocolPtr->Version = 1;
  AodNvAreaUpdatedProtocolPtr->AodNvAreaPtr = AodNvAreaBufferPtr;
  AodNvAreaUpdatedProtocolPtr->AodCpuBiosStuctPtr = AodCpuBiosStructPtr;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gAodNvAreaUpdatedProtocolGuid, AodNvAreaUpdatedProtocolPtr,
                  NULL
                  );

  return Status;
}

EFI_STATUS
EFIAPI
InstallAodSsdtEntryPoint (
  IN       EFI_HANDLE              ImageHandle,
  IN       EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_STATUS                      Status;

  Status = EFI_SUCCESS;

  DEBUG ((EFI_D_ERROR, "  InstallAodSsdtEntryPoint:\n"));
  Status = InstallAodSsdtTable (&AOD_SSDT_GUID, NULL);
  return Status;
}

