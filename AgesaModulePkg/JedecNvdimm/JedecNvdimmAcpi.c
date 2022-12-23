/* $NoKeywords:$ */
/**
 * @file
 *
 * JedecNvdimmAcpi.c
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  JedecNvdimm
 * @e \$Revision$   @e \$Date$
 *
 */
/*
 ******************************************************************************
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

/** @file JedecNvdimmAcpi.c
    JedecNvdimmAcpi Driver Implementation

**/

#include "AMD.h"
#include "Filecode.h"
#include "JedecNvdimm.h"
#include "JedecNvdimmAcpi.h"
#include "JedecNvdimmDsm.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "Library/BaseLib.h"
#include "Library/IdsLib.h"
#include "Protocol/Smbios.h"
#include <MemDmi.h>
#include <Addendum/Apcb/Inc/SSP/APOB.h>
#include <Library/HobLib.h>
#include "Protocol/AcpiTable.h"
#include "Protocol/AmdAcpiSratServicesProtocol.h"
#include "IndustryStandard/SmBios.h"
#include "IndustryStandard/Acpi.h"
#include "Protocol/AcpiSystemDescriptionTable.h"

#define FILECODE UNIVERSAL_SMBIOS_AMDSMBIOSDXE_FILECODE
#define ACPI_TABLE_MAX_LENGTH           0x100000ul    // Reserve 1M for ACPI table

#define EFI_ACPI_TABLE_VERSION_1_0B (1 << 1)
#define EFI_ACPI_TABLE_VERSION_2_0  (1 << 2)
#define EFI_ACPI_TABLE_VERSION_3_0  (1 << 3)
#define EFI_ACPI_TABLE_VERSION_4_0  (1 << 4)
#define EFI_ACPI_TABLE_VERSION_5_0  (1 << 5)

#define EFI_ACPI_TABLE_VERSION_X    (EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0 | EFI_ACPI_TABLE_VERSION_4_0)

#define EFI_SIGNATURE_16(A, B)        ((A) | (B << 8))
#define EFI_SIGNATURE_32(A, B, C, D)  (EFI_SIGNATURE_16 (A, B) | (EFI_SIGNATURE_16 (C, D) << 16))

EFI_GUID EFI_BYTE_ADDRESSABLE_PERSISTENT_MEMORY_REGION = {0x66F0D379, 0xB4F3, 0x4074, 0xAC, 0x43, 0x0D, 0x33, 0x18, 0xB7, 0x8C, 0xDB};

extern EFI_GUID gAmdNvdimmInfoHobGuid;
extern EFI_GUID gAmdNvdimmSpdInfoHobGuid;
extern UINT32 gNvdimmBitMap;
extern EFI_STATUS ReadNvdimm (UINT8 Socket, UINT8 Channel, UINT8 Dimm, UINT8 Page, UINT8 Register, UINT8 *Data, BOOLEAN IsSpd);
extern EFI_STATUS WriteNvdimm (UINT8 Socket, UINT8 Channel, UINT8 Dimm, UINT8 Page, UINT8 Register, UINT8 *Data, BOOLEAN IsSpd);

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define PRINT_TABLES 1

UINT8   gTotalSmbiosHandles = 0;
UINT16  gSmbiosHandles[ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_CHANNELS_PER_SOCKET * ABL_APOB_MAX_DIMMS_PER_CHANNEL - 1];

// NvdimmAddrSize[0]: a NVDIMM module starting address, [1]: its size
typedef struct {
    UINT32      NvdimmAddrSize[ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_CHANNELS_PER_SOCKET * ABL_APOB_MAX_DIMMS_PER_CHANNEL - 1][2];
} NVDIMM_INFO;

STATIC NFIT_HEADER  ROMDATA NfitHdrStruct =
{
  {'N','F','I','T'},
  0,
  1,
  0,
  {0},
  {0},
  1,
  {'A','M','D',' '},
  1,
  0
};

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

STATIC
VOID
ChecksumAcpiTable (
    IN OUT   NFIT_HEADER        *Table
    );

STATIC
UINT32
GetProximityDomain (
    IN OUT   UINT64             DimmBase,
    IN       AMD_CONFIG_PARAMS  *StdHeader
    );

STATIC
UINT16
GetSmbiosType17Handle (
    IN       UINT16                   NvdimmCtrlRegionStructIndex,
    IN       CONTROL_REGION_STRUCT    *StartOfCtrlRegionStruct,
    IN       CONTROL_REGION_STRUCT    *EndOfCtrlRegionStruct
    );

STATIC
UINT32
ConvertSerialNumberString (
    IN       EFI_SMBIOS_TABLE_HEADER  *Record,
    IN       UINT16                   SerialNumberStringIndex
    );

STATIC
UINT32
RotateRight (
    UINT32    Number,
    UINT32    Bits
    );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
    Generate the NFIT ACPI tables

    @param    TotalNvdimm

    @retval   EFI_SUCCESS or EFI_DEVICE_ERROR

**/

EFI_STATUS
GenerateJedecNvdimmAcpi (
    OUT UINT16  *TotalNvdimm
    )
{
    EFI_STATUS                Status;
    VOID                      *HobAddr;
    NVDIMM_INFO               *NvdimmInfo;
    UINT16                    NvdimmInfoLength;
    UINT16                    i;
    UINT8                     j;
    EFI_ACPI_TABLE_PROTOCOL   *AcpiTableProtocol;
    NFIT_HEADER               *NfitHeaderPtr;
    SPA_RANGE_STRUCT          *SpaRangeStructPtr;
    REGION_MAPPING_STRUCT     *RegionMappingStructPtr;
    CONTROL_REGION_STRUCT     *CtrlRegionStructPtr;
    CONTROL_REGION_STRUCT     *StartOfCtrlRegionStruct;
    CONTROL_REGION_STRUCT     *EndOfCtrlRegionStruct;
    SMBIOS_MGMT_INFO_STRUCT   *SmbiosMgmtInfoStructPtr;
    UINT16                    *SmbiosMgmtInfoStructHandlePtr;
    UINT8                     *NfitTypePtr;
    ALLOCATE_HEAP_PARAMS      AllocHeapParams;
    AMD_CONFIG_PARAMS         StdHeader;
    UINTN                     TableSize;
    UINTN                     TableKey;
    NVDIMM_SPD_INFO           *NvdimmSpdInfo;
    UINT32                    NvdimmIndex;
    UINT8                     Data;
    UINT16                    FunctionInterfaceDescriptor;

    DEBUG ((EFI_D_ERROR, "AmdGenerateNvdimmAcpi Entry\n"));

    Status = EFI_SUCCESS;
    HobAddr = GetFirstGuidHob (&gAmdNvdimmInfoHobGuid);
    if (HobAddr == NULL) {
        DEBUG ((EFI_D_ERROR, "gAmdNvdimmInfoHobGuid hob not found!\n"));
        return EFI_UNSUPPORTED;
    }
    NvdimmInfo = (NVDIMM_INFO *) GET_GUID_HOB_DATA (HobAddr);
    NvdimmInfoLength = ABL_APOB_MAX_SOCKETS_SUPPORTED * ABL_APOB_MAX_CHANNELS_PER_SOCKET * ABL_APOB_MAX_DIMMS_PER_CHANNEL - 1;
    *TotalNvdimm = 0;
    for (i = 0; i < NvdimmInfoLength; i++) {
        if (NvdimmInfo->NvdimmAddrSize[i][1] != 0) {    // [i][1] = NVDIMM size, size != 0 means a NVDIMM present
            (*TotalNvdimm)++;
        } else {
            break;
        }
    }

    DEBUG ((EFI_D_ERROR, "Total NVDIMMs found = %d\n", *TotalNvdimm));

    if (0 == *TotalNvdimm) {   // No NVDIMM in system, return
        return EFI_SUCCESS;
    }

    // Create NVDIMM ACPI table while any NVDIMM present in system
    Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, &AcpiTableProtocol);
    if (EFI_ERROR (Status)) {
        return EFI_DEVICE_ERROR;
    }

    AllocHeapParams.RequestedBufferSize = ACPI_TABLE_MAX_LENGTH;
    AllocHeapParams.BufferHandle = AMD_ACPI_TABLE_BUFFER_HANDLE;
    AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
    if (HeapAllocateBuffer (&AllocHeapParams, &StdHeader) != AGESA_SUCCESS) {
        return AGESA_ERROR;
    }

    NfitHeaderPtr = (NFIT_HEADER *) AllocHeapParams.BufferPtr;

    // Fill NFIT header basic contents
    LibAmdMemCopy (NfitHeaderPtr, (VOID *) &NfitHdrStruct, (UINTN) (sizeof (NFIT_HEADER)), &StdHeader);

    // Update table OEM fields to NFIT table
    ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 100) <= 6);
    ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemTableId), 100) <= 8);

    LibAmdMemCopy ((VOID *) NfitHeaderPtr->OemId,
                   (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
                   AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6),
                   &StdHeader);
    LibAmdMemCopy ((VOID *) NfitHeaderPtr->OemTableId,
                   (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemTableId),
                   AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemTableId), 8),
                   &StdHeader);

    HobAddr = GetFirstGuidHob (&gAmdNvdimmSpdInfoHobGuid);
    if (HobAddr == NULL) {
        DEBUG ((EFI_D_ERROR, "gAmdNvdimmSpdInfoHobGuid hob not found!\n"));
        return EFI_UNSUPPORTED;
    }
    NvdimmSpdInfo = (NVDIMM_SPD_INFO *) GET_GUID_HOB_DATA (HobAddr);

    // Configure NVDIMM bitmap
    for (i = 0; i < *TotalNvdimm; i++) {
        DEBUG ((EFI_D_ERROR, "NVDIMM Socket %d, Channel %d, Dimm %d\n", NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm));
        gNvdimmBitMap |= (((1 << NvdimmSpdInfo[i].Dimm) << NvdimmSpdInfo[i].Channel*2) << NvdimmSpdInfo[i].Socket*16);
    }
    DEBUG ((EFI_D_ERROR, "gNvdimmBitMap  = %X\n", gNvdimmBitMap));

    // -----------------------------------------------------------------------------------------------
    // Insert System Physical Address (SPA) Range Structure
    //
    NfitTypePtr = (UINT8 *) NfitHeaderPtr + (sizeof (NFIT_HEADER));
    for (i = 0; i < *TotalNvdimm; i++) {
        SpaRangeStructPtr = (SPA_RANGE_STRUCT *) NfitTypePtr;
        SpaRangeStructPtr->Type = 0;
        SpaRangeStructPtr->Length = (sizeof (SPA_RANGE_STRUCT));
        SpaRangeStructPtr->SpaRangeStructIndex = i + 1;     // Value 0 is reserved, assing to 1 ~ TotalNvdimm
        SpaRangeStructPtr->Flags = BIT1;                    // Indicate that data in Proximity Domain field is valid

        // ProximityDomain must match with corresponding entry in the SRAT table, FabricCreateSratMemoryInfo assign socket number as Domain
        SpaRangeStructPtr->ProximityDomain = GetProximityDomain (LShiftU64 ((UINT64) NvdimmInfo->NvdimmAddrSize[i][0], 8), &StdHeader);
        SpaRangeStructPtr->AddrRangeTypeGUID = EFI_BYTE_ADDRESSABLE_PERSISTENT_MEMORY_REGION;
        SpaRangeStructPtr->SpaRangeBase = LShiftU64 ((UINT64) NvdimmInfo->NvdimmAddrSize[i][0], 8);     // Convert address to byte
        SpaRangeStructPtr->SpaRangeLength = LShiftU64 ((UINT64) NvdimmInfo->NvdimmAddrSize[i][1], 8);   // Convert size to byte
        SpaRangeStructPtr->AddrRangeMemMappingAttr = EFI_MEMORY_UC;

        NfitTypePtr += (sizeof (SPA_RANGE_STRUCT));

#if PRINT_TABLES
        DEBUG ((EFI_D_ERROR, "System Physical Address (SPA) Range Structure\n"));
        DEBUG ((EFI_D_ERROR, "Type                                    %02X\n", SpaRangeStructPtr->Type));
        DEBUG ((EFI_D_ERROR, "Length                                  %02X\n", SpaRangeStructPtr->Length));
        DEBUG ((EFI_D_ERROR, "SPA Range Structure Index               %02X\n", SpaRangeStructPtr->SpaRangeStructIndex));
        DEBUG ((EFI_D_ERROR, "Flags                                   %02X\n", SpaRangeStructPtr->Flags));
        DEBUG ((EFI_D_ERROR, "Proximity Domain                        %04X\n", SpaRangeStructPtr->ProximityDomain));
        DEBUG ((EFI_D_ERROR, "System Physical Address Range Base      %08lX\n", SpaRangeStructPtr->SpaRangeBase));
        DEBUG ((EFI_D_ERROR, "System Physical Address Range Length    %08lX\n", SpaRangeStructPtr->SpaRangeLength));
        DEBUG ((EFI_D_ERROR, "Address Range Memory Mapping Attribute  %08lX\n", SpaRangeStructPtr->AddrRangeMemMappingAttr));
#endif
    }

    // -----------------------------------------------------------------------------------------------
    // Insert Control Region Structure
    //
    StartOfCtrlRegionStruct = (CONTROL_REGION_STRUCT *) NfitTypePtr;

    // NvdimmIndex holds the data that which DIMM slot in system with NVDIMM. Bit 0 for slot 0, bit 1 for slot 1, etc.
    // A 1 marks that slot with a NVDIMM.
    NvdimmIndex = 0;

    for (i = 0; i < *TotalNvdimm; i++) {
        CtrlRegionStructPtr = (CONTROL_REGION_STRUCT *) NfitTypePtr;
        CtrlRegionStructPtr->Type = 4;
        CtrlRegionStructPtr->Length = sizeof (CONTROL_REGION_STRUCT);
        CtrlRegionStructPtr->ControlRegionStructIndex = i + 1;
        CtrlRegionStructPtr->VendorId = NvdimmSpdInfo[i].Spd320;
        CtrlRegionStructPtr->DeviceId = NvdimmSpdInfo[i].Spd192;
        CtrlRegionStructPtr->RevisionId = NvdimmSpdInfo[i].Spd349;
        CtrlRegionStructPtr->SubSysVendorId = NvdimmSpdInfo[i].Spd194;
        CtrlRegionStructPtr->SubSysDeviceId = NvdimmSpdInfo[i].Spd196;
        CtrlRegionStructPtr->SubSysRevisionId = NvdimmSpdInfo[i].Spd198;
        CtrlRegionStructPtr->ValidField = 1;
        CtrlRegionStructPtr->ManufacturingLocation = (UINT8) NvdimmSpdInfo[i].Spd322;
        CtrlRegionStructPtr->ManufacturingDate = NvdimmSpdInfo[i].Spd323;
        CtrlRegionStructPtr->SerialNumber[0] = NvdimmSpdInfo[i].SerialNumber[0];
        CtrlRegionStructPtr->SerialNumber[1] = NvdimmSpdInfo[i].SerialNumber[1];
        CtrlRegionStructPtr->SerialNumber[2] = NvdimmSpdInfo[i].SerialNumber[2];
        CtrlRegionStructPtr->SerialNumber[3] = NvdimmSpdInfo[i].SerialNumber[3];

        for (j = 204; j <= 218; j += 2) {
            Status = ReadNvdimm (NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, j, &Data, TRUE);
            FunctionInterfaceDescriptor = Data;
            Status = ReadNvdimm (NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, j+1, &Data, TRUE);
            FunctionInterfaceDescriptor |= (Data << 8);
            if (FunctionInterfaceDescriptor & BIT15) {                      // Implemented
                // Bits[4:0] Function Interface
                if ((FunctionInterfaceDescriptor & 0x1F) == 1) {            // Byte Addressable Energy Backed Interface 1
                    // Bits[9:5] Function Class
                    if (((FunctionInterfaceDescriptor >> 5) & 0x1F) == 1) { // Byte addressable Energy Backed
                        CtrlRegionStructPtr->RegionFormatInterfaceCode = ((((FunctionInterfaceDescriptor >> 5) & 0x1F) << 8) |
                                                                            (FunctionInterfaceDescriptor & 0x1F));
                        break;
                    }
                }
            }
        }

        CtrlRegionStructPtr->NumOfBlockCtrlWindow = 0;
        CtrlRegionStructPtr->SizeOfBlockCtrlWindow = 0;
        CtrlRegionStructPtr->CmdRegOffsetInBlockCtrlWindow = 0;
        CtrlRegionStructPtr->SizeOfCmdRegInBlockCtrlWindow = 0;
        CtrlRegionStructPtr->StatusRegOffsetInBlockCtrlWindow = 0;
        CtrlRegionStructPtr->SizeOfStatusRegInBlockCtrlWindow = 0;
        CtrlRegionStructPtr->CtrlRegionFlag = 0;

        NvdimmIndex |= (UINT32) 1 << NvdimmSpdInfo[i].NvdimmIndex;

//      NvdimmSpdInfo++;    // Point to next NVDIMM SPD data
        NfitTypePtr += (sizeof (CONTROL_REGION_STRUCT));

#if PRINT_TABLES
        DEBUG ((EFI_D_ERROR, "NVDIMM Control Region Structure\n"));
        DEBUG ((EFI_D_ERROR, "Type                                   %02X\n", CtrlRegionStructPtr->Type));
        DEBUG ((EFI_D_ERROR, "Length                                 %02X\n", CtrlRegionStructPtr->Length));
        DEBUG ((EFI_D_ERROR, "NVDIMM Control Region Structure Index  %02X\n", CtrlRegionStructPtr->ControlRegionStructIndex));
        DEBUG ((EFI_D_ERROR, "Vendor ID                              %02X\n", CtrlRegionStructPtr->VendorId));
        DEBUG ((EFI_D_ERROR, "Device ID                              %02X\n", CtrlRegionStructPtr->DeviceId));
        DEBUG ((EFI_D_ERROR, "Revision ID                            %02X\n", CtrlRegionStructPtr->RevisionId));
        DEBUG ((EFI_D_ERROR, "Subsystem Vendor ID                    %02X\n", CtrlRegionStructPtr->SubSysVendorId));
        DEBUG ((EFI_D_ERROR, "Subsystem Device ID                    %02X\n", CtrlRegionStructPtr->SubSysDeviceId));
        DEBUG ((EFI_D_ERROR, "Subsystem Revision ID                  %02X\n", CtrlRegionStructPtr->SubSysRevisionId));
        DEBUG ((EFI_D_ERROR, "Valid Fields                           %02X\n", CtrlRegionStructPtr->ValidField));
        DEBUG ((EFI_D_ERROR, "Manufacturing Location                 %02X\n", CtrlRegionStructPtr->ManufacturingLocation));
        DEBUG ((EFI_D_ERROR, "Manufacturing Date                     %02X\n", CtrlRegionStructPtr->ManufacturingDate));
        DEBUG ((EFI_D_ERROR, "Serial Number                          %04X\n", (CtrlRegionStructPtr->SerialNumber[3] << 24) |
                                                                     (CtrlRegionStructPtr->SerialNumber[2] << 16) |
                                                                     (CtrlRegionStructPtr->SerialNumber[1] << 8) |
                                                                     (CtrlRegionStructPtr->SerialNumber[0])));
        DEBUG ((EFI_D_ERROR, "Region Format Interface Code           %02X\n", CtrlRegionStructPtr->RegionFormatInterfaceCode));
#endif
    }

    EndOfCtrlRegionStruct = (CONTROL_REGION_STRUCT *) NfitTypePtr;

    // -----------------------------------------------------------------------------------------------
    // Insert Region Mapping Structure
    // Put Region Mapping Structure after Control Region Structure because Region Mapping Structure->
    // Nvdimm Physical ID is "Handle for the SMBIOS Type 17 describing the NVDIMM containing the NVDIMM
    // region". Need to compare the Type 17 Serial Number to the one at the corresponding Control Region
    // Structure.
    //
    for (i = 0; i < *TotalNvdimm; i++) {
        RegionMappingStructPtr = (REGION_MAPPING_STRUCT *) NfitTypePtr;
        RegionMappingStructPtr->Type = 1;
        RegionMappingStructPtr->Length = sizeof (REGION_MAPPING_STRUCT);
        RegionMappingStructPtr->NfitDeviceHandle = (UINT32) ((NvdimmSpdInfo[i].Socket << 12) | (NvdimmSpdInfo[i].Channel << 4) | (NvdimmSpdInfo[i].Dimm));
        RegionMappingStructPtr->NvdimmRegionId = i + 1;     // Take the same as SpaRangeStructPtr->SpaRangeStructIndex
        RegionMappingStructPtr->SpaRangeStructIndex = i + 1;
        RegionMappingStructPtr->NvdimmCtrlRegionStructIndex = i + 1;
        RegionMappingStructPtr->NvdimmPhysicalId = GetSmbiosType17Handle (RegionMappingStructPtr->NvdimmCtrlRegionStructIndex,
                                                                          StartOfCtrlRegionStruct, EndOfCtrlRegionStruct);  // Smbios TYPE 17 handle
        RegionMappingStructPtr->NvdimmRegionSize = LShiftU64 ((UINT64) NvdimmInfo->NvdimmAddrSize[i][1], 8);                // Convert size to byte
        RegionMappingStructPtr->RegionOffset = 0;           // Zero because no interleaving
        RegionMappingStructPtr->NvdimmPhysicalAddrRegionBase = 0;
        RegionMappingStructPtr->InterleaveStructIndex = 0;  // Zero because no block region
        RegionMappingStructPtr->InterleaveWay = 1;          // No interleaving so only 1 NVDIMM
        RegionMappingStructPtr->NvdimmStateFlags = BIT5;

        Status = ReadNvdimm (NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_SAVE_STATUS0, &Data, FALSE);
        if (Data & BIT1) RegionMappingStructPtr->NvdimmStateFlags |= BIT0;
        Status = ReadNvdimm (NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_RESTORE_STATUS0, &Data, FALSE);
        if (Data & BIT1) RegionMappingStructPtr->NvdimmStateFlags |= BIT1;
        Status = ReadNvdimm (NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_ERASE_STATUS0, &Data, FALSE);
        if (Data & BIT1) RegionMappingStructPtr->NvdimmStateFlags |= BIT3;
        Status = ReadNvdimm (NvdimmSpdInfo[i].Socket, NvdimmSpdInfo[i].Channel, NvdimmSpdInfo[i].Dimm, 0, PAGE0_ARM_STATUS0, &Data, FALSE);
        if (Data & BIT1) RegionMappingStructPtr->NvdimmStateFlags |= BIT3;

        NfitTypePtr += (sizeof (REGION_MAPPING_STRUCT));

#if PRINT_TABLES
        DEBUG ((EFI_D_ERROR, "NVDIMM Region Mapping Structure\n"));
        DEBUG ((EFI_D_ERROR, "Type                                   %02X\n", RegionMappingStructPtr->Type));
        DEBUG ((EFI_D_ERROR, "Length                                 %02X\n", RegionMappingStructPtr->Length));
        DEBUG ((EFI_D_ERROR, "NFIT Device Handle                     %04X\n", RegionMappingStructPtr->NfitDeviceHandle));
        DEBUG ((EFI_D_ERROR, "NVDIMM Physical ID                     %02X\n", RegionMappingStructPtr->NvdimmPhysicalId));
        DEBUG ((EFI_D_ERROR, "NVDIMM Region ID                       %02X\n", RegionMappingStructPtr->NvdimmRegionId));
        DEBUG ((EFI_D_ERROR, "SPA Range Structure Index              %02X\n", RegionMappingStructPtr->SpaRangeStructIndex));
        DEBUG ((EFI_D_ERROR, "NVDIMM Control Region Structure Index  %02X\n", RegionMappingStructPtr->NvdimmCtrlRegionStructIndex));
        DEBUG ((EFI_D_ERROR, "NVDIMM Region Size                     %08lX\n", RegionMappingStructPtr->NvdimmRegionSize));
        DEBUG ((EFI_D_ERROR, "Region Offset                          %08lX\n", RegionMappingStructPtr->RegionOffset));
        DEBUG ((EFI_D_ERROR, "NVDIMM Physical Address Region Base    %08lX\n", RegionMappingStructPtr->NvdimmPhysicalAddrRegionBase));
        DEBUG ((EFI_D_ERROR, "Interleave Structure Index             %02X\n", RegionMappingStructPtr->InterleaveStructIndex));
        DEBUG ((EFI_D_ERROR, "Interleave Ways                        %02X\n", RegionMappingStructPtr->InterleaveWay));
        DEBUG ((EFI_D_ERROR, "NVDIMM State Flags                     %02X\n", RegionMappingStructPtr->NvdimmStateFlags));
#endif
    }

    // -----------------------------------------------------------------------------------------------
    // SMBIOS Management Information Structure
    //
    SmbiosMgmtInfoStructPtr = (SMBIOS_MGMT_INFO_STRUCT *) NfitTypePtr;
    SmbiosMgmtInfoStructPtr->Type = 3;
    SmbiosMgmtInfoStructPtr->Length = sizeof (SMBIOS_MGMT_INFO_STRUCT) + (gTotalSmbiosHandles * sizeof(UINT16));
    SmbiosMgmtInfoStructHandlePtr = (UINT16 *)(NfitTypePtr + 8);
#if PRINT_TABLES
    DEBUG ((EFI_D_ERROR, "SMBIOS Management Information Structure\n"));
    DEBUG ((EFI_D_ERROR, "Type      %02X\n", SmbiosMgmtInfoStructPtr->Type));
#endif
    for (i = 0; i < gTotalSmbiosHandles; i++) {
        SmbiosMgmtInfoStructHandlePtr[i] = gSmbiosHandles[i];
        DEBUG ((EFI_D_ERROR, "Data[%d]   %02X\n", i, SmbiosMgmtInfoStructHandlePtr[i]));
    }

    NfitTypePtr += (SmbiosMgmtInfoStructPtr->Length);

    // Fill whole NFIT length
    NfitHeaderPtr->Length = (sizeof (NFIT_HEADER)) + ((*TotalNvdimm) * ((sizeof (SPA_RANGE_STRUCT)) + (sizeof (REGION_MAPPING_STRUCT)) + (sizeof (CONTROL_REGION_STRUCT)))) + SmbiosMgmtInfoStructPtr->Length;
    //NfitHeaderPtr->Length = (UINT32) (NfitTypePtr - (UINT8 *) NfitHeaderPtr);

    // Update NFIT header checksum
    ChecksumAcpiTable (NfitHeaderPtr);

    // Publish NFIT
    TableSize = NfitHeaderPtr->Length;
    TableKey = 0;
    AcpiTableProtocol->InstallAcpiTable (AcpiTableProtocol, NfitHeaderPtr, TableSize, &TableKey);

    // Deallocate heap
    HeapDeallocateBuffer (AMD_ACPI_TABLE_BUFFER_HANDLE, &StdHeader);

    DEBUG ((EFI_D_ERROR, "AmdGenerateNvdimmAcpi Exit\n"));
    return Status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Calculate an ACPI style checksum
 *
 * Computes the checksum and stores the value to the checksum
 * field of the passed in ACPI table's header.
 *
 * @param[in]  Table             ACPI table to checksum
 *
 */
STATIC
VOID
ChecksumAcpiTable (
    IN OUT   NFIT_HEADER        *Table
   )
{
    UINT8  *BuffTempPtr;
    UINT8  Checksum;
    UINT32 BufferOffset;

    Table->Checksum = 0;
    Checksum = 0;
    BuffTempPtr = (UINT8 *) Table;
    for (BufferOffset = 0; BufferOffset < Table->Length; BufferOffset++) {
        Checksum = Checksum - *(BuffTempPtr + BufferOffset);
    }

    Table->Checksum = Checksum;
}

/**
 * Based on the DIMM base address to retrieve the Domain from
 * SRAT table
 *
 * @param[in]  DimmBase - Memory range base address
 *
 */
STATIC
UINT32
GetProximityDomain (
    IN OUT   UINT64             DimmBase,
    IN       AMD_CONFIG_PARAMS  *StdHeader
    )
{
    UINT8                                   *TableEnd;
    SRAT_HEADER                             *SratHeaderStructPtr;
    ALLOCATE_HEAP_PARAMS                    AllocParams;
    AMD_FABRIC_ACPI_SRAT_SERVICES_PROTOCOL  *SratMemory;
    SRAT_MEMORY                             *SratMemoryEntryPtr;
    UINT64                                  MemoryBase;
    UINT64                                  MemorySize;
    UINT64                                  MemoryHoleSize;
    UINT32                                  ProximityDomain;

    // Allocate a buffer
    AllocParams.RequestedBufferSize = 4 * 1024;    // 4 KB is enough for SRAT
    AllocParams.BufferHandle = AMD_MEM_MISC_HANDLES_END;
    AllocParams.Persist = HEAP_SYSTEM_MEM;

    if (HeapAllocateBuffer (&AllocParams, StdHeader) != AGESA_SUCCESS) {
      //return AGESA_ERROR;
      DEBUG ((EFI_D_ERROR, "Fail to allocate heap for AMD_MEM_MISC_HANDLES_END handle\n"));
      ASSERT_EFI_ERROR (EFI_OUT_OF_RESOURCES);
      return 0;
    }

    SratHeaderStructPtr = (SRAT_HEADER *) AllocParams.BufferPtr;
    TableEnd = (UINT8 *) SratHeaderStructPtr + sizeof (SRAT_HEADER);

    // Just need SRAT Type 1 Memory Affinity Structure
    // SratMemory->CreateMemory --> FabricCreateSratMemoryInfo, read ZP DF base/limit register to create SRAT entry
    if (gBS->LocateProtocol (&gAmdFabricAcpiSratServicesProtocolGuid, NULL, (VOID **) &SratMemory) == EFI_SUCCESS) {
        SratMemory->CreateMemory (SratMemory, SratHeaderStructPtr, &TableEnd);
    } else {
      DEBUG ((EFI_D_ERROR, "SRAT services not installed at GetProximityDomain\n"));
      // Deallocate heap
      HeapDeallocateBuffer (AMD_MEM_MISC_HANDLES_END, StdHeader);
      return 0;
    }

    // - The first entry: base=0, length=0x000a_0000
    // - The 2nd entry: base=0x0010_0000, length=4GB - MMIO hole size - 0x0010_0000
    // - The 3rd entry: base=0x1_0000_0000, length=?
    // - Search the SRAT entry with base address = 0x1_0000_0000 (4GB)
    // - MMIO hole size = 4GB - end address of 2nd entry
    SratMemoryEntryPtr = (SRAT_MEMORY *) ((UINT8 *) SratHeaderStructPtr + sizeof (SRAT_HEADER));
    //SratMemoryEntryPtr += 2;   // Point to the 3rd entry
    //while (TRUE) {
    //  MemoryBase = LShiftU64 (SratMemoryEntryPtr->BaseAddressHigh, 32);
    //  MemoryBase += SratMemoryEntryPtr->BaseAddressLow;
    //  if (0x100000000 == MemoryBase) {
    //    break;
    //  }
    //  SratMemoryEntryPtr++;
    //}

    // SratMemoryEntryPtr point to the entry its memory base = 4GB
    //SratMemoryEntryPtr--;   // Point to the 2nd entry

    SratMemoryEntryPtr++;   // Point to the 2nd entry
    MemoryBase = LShiftU64 (SratMemoryEntryPtr->BaseAddressHigh, 32);
    MemoryBase += SratMemoryEntryPtr->BaseAddressLow;
    MemorySize = LShiftU64 (SratMemoryEntryPtr->LengthHigh, 32);
    MemorySize += SratMemoryEntryPtr->LengthLow;
    MemoryHoleSize = 0x100000000 - MemoryBase - MemorySize;

    SratMemoryEntryPtr++;   // Point to the 3rd entry
    //SratMemoryEntryPtr++;   // Skip the entry of 4GB, this one is not NVDIMM
    // Search the entry its base/size cover the input DimmBase
    while (TRUE) {
        MemoryBase = LShiftU64 (SratMemoryEntryPtr->BaseAddressHigh, 32);
        MemoryBase += SratMemoryEntryPtr->BaseAddressLow;
        MemorySize = LShiftU64 (SratMemoryEntryPtr->LengthHigh, 32);
        MemorySize += SratMemoryEntryPtr->LengthLow;
        if (MemoryBase == 0) {    // No more memory entry, should not hit this condition
            DEBUG ((EFI_D_ERROR, "Error at GetProximityDomain\n"));
            break;
        }
        if ((DimmBase >= (MemoryBase - MemoryHoleSize)) && (DimmBase < (MemoryBase - MemoryHoleSize + MemorySize))) {
            break;    // The input DimmBase covered by this entry
        }
        SratMemoryEntryPtr++;
    }
    ProximityDomain = SratMemoryEntryPtr->ProximityDomain;

    // Deallocate heap
    HeapDeallocateBuffer (AMD_MEM_MISC_HANDLES_END, StdHeader);

    DEBUG ((EFI_D_ERROR, "ProximityDomain = %d\n", ProximityDomain));
    return ProximityDomain;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Gets the SMBIOS type 17 handle
 *
 * @param[in]  NvdimmCtrlRegionStructIndex
 *
 */
STATIC
UINT16
GetSmbiosType17Handle (
    IN       UINT16                 NvdimmCtrlRegionStructIndex,
    IN       CONTROL_REGION_STRUCT  *StartOfCtrlRegionStruct,
    IN       CONTROL_REGION_STRUCT  *EndOfCtrlRegionStruct
    )
{
    CONTROL_REGION_STRUCT   *EntryPtr;
    EFI_SMBIOS_PROTOCOL     *Smbios;
    EFI_STATUS              Status;
    EFI_SMBIOS_HANDLE       SmbiosHandle;
    EFI_SMBIOS_TYPE         Type;
    EFI_SMBIOS_TABLE_HEADER *Record;
    SMBIOS_TABLE_TYPE17     *T17;
    UINT16                  SerialNumberStringIndex;
    UINT32                  SerialNumber;
    UINT16                  Type17Handle;
    BOOLEAN                 HandleFound;
    UINT32                  SpdSerialNumber;

    Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, &Smbios);

    EntryPtr = StartOfCtrlRegionStruct;
    Type17Handle = 0;
    HandleFound = FALSE;

    while (EntryPtr < EndOfCtrlRegionStruct) {
        if (EntryPtr->ControlRegionStructIndex == NvdimmCtrlRegionStructIndex) {
            // Found the target NVDIMM Control Region Structure
            SmbiosHandle = 0xfffe;
            Type = 17;
            while (TRUE) {
                if (Smbios->GetNext(Smbios, &SmbiosHandle, &Type, &Record, NULL) == EFI_SUCCESS) {
                    DEBUG ((EFI_D_ERROR, "Type 17 handle = %x, Record = %x\n", SmbiosHandle, Record));
                    T17 = (SMBIOS_TABLE_TYPE17 *) Record;
                    if (T17->MemoryType == Ddr4MemType) {   // Ignore the empty entry
                        // Get this Type 17 entry serial number, convert it to a uint32 number
                        SerialNumberStringIndex = (UINT16) T17->SerialNumber;
                        SerialNumber = ConvertSerialNumberString (Record, SerialNumberStringIndex);

                        // Compare the serial number to the one read from SPD, if match then this is the correct entry,
                        // return its handle
                        SpdSerialNumber = ((UINT32) EntryPtr->SerialNumber[3] << 24) | ((UINT32) EntryPtr->SerialNumber[2] << 16) |
                                          ((UINT32) EntryPtr->SerialNumber[1] << 8) | (UINT32) EntryPtr->SerialNumber[0];
                        if (SerialNumber == SpdSerialNumber) {
                            Type17Handle = T17->Hdr.Handle;
                            HandleFound = TRUE;
                            break;
                        }
                    }
                }   // if (Smbios->GetNext
            }   // while (TRUE)
        }   // if (EntryPtr->ControlRegionStructIndex
        if (HandleFound) {
            gSmbiosHandles[gTotalSmbiosHandles] = Type17Handle;
            gTotalSmbiosHandles++;
            break;
        }
        EntryPtr++;
    }

    return Type17Handle;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Function to convert serial number string from ascii to number
 *
 * @param[in]  Record - starting address of string area
 * @param[in]  SerialNumberStringIndex - index of the serial number string
 *
 */
STATIC
UINT32
ConvertSerialNumberString (
    IN       EFI_SMBIOS_TABLE_HEADER    *Record,
    IN       UINT16                     SerialNumberStringIndex
    )
{
    UINT8     *Type17Ptr;
    UINT32    SerialNumber;
    UINT16    i;

    Type17Ptr = (UINT8 *) Record;
    Type17Ptr += sizeof (SMBIOS_TABLE_TYPE17);    // Move pointer to the first string
    SerialNumberStringIndex--;
    while (0 != SerialNumberStringIndex) {
        while (0 != *Type17Ptr) {
            Type17Ptr++;
        }
        SerialNumberStringIndex--;
        Type17Ptr++;
    }

    // Type17Ptr point to the string of serial number
    // Convert ascii to number, maximum 8 ascii digit
    SerialNumber = 0;
    for (i = 0; i < 4; i++) {
        if (0 != *Type17Ptr) {
            SerialNumber = RotateRight (SerialNumber, 8);
            if (*Type17Ptr > 0x39) {    // a ~ f
                SerialNumber |= ((*Type17Ptr - 0x40 + 9) & 0xf) << 4;
            } else {
                SerialNumber |= ((*Type17Ptr - 0x30) & 0xf) << 4;
            }
            Type17Ptr++;
            if (*Type17Ptr > 0x39) {    // a ~ f
                SerialNumber |= (*Type17Ptr - 0x40 + 9) & 0xf;
            } else {
                SerialNumber |= (*Type17Ptr - 0x30) & 0xf;
            }
            Type17Ptr++;
        } else {
            break;
        }
    }
    SerialNumber = RotateRight (SerialNumber, 8);

    return SerialNumber;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Function to rotate a 32 bits number right x bits
 *
 * @param[in]  Number -
 * @param[in]  Bits -
 *
 */
STATIC
UINT32
RotateRight (
    UINT32    Number,
    UINT32    Bits
    )
{
    return ((Number >> Bits) | (Number << (32 - Bits)));
}


