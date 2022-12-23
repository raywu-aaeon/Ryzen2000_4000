/* $NoKeywords:$ */
/**
 * @file
 *
 * IOMMU IVRS Table Creation
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 316101 $   @e \$Date: 2015-04-03 09:33:53 +0800 (Fri, 03 Apr 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "Gnb.h"
#include  "Library/AmdHeapLib.h"
#include  "GnbPcieConfig.h"
#include  "GnbFamServices.h"
#include  "GnbCommonLib.h"
#include  "GnbIvrsLib.h"
#include  "GnbRegistersCommonV2.h"
#include  "OptionGnb.h"
#include  "GnbIommuIvrs.h"

#define FILECODE LIBRARY_GNBCZLIB_MODULES_GNBIOMMUIVRS_GNBIOMMUIVRS_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
extern GNB_BUILD_OPTIONS ROMDATA GnbBuildOptions;
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

#define IVRS_TABLE_LENGTH 8 * 1024

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

AGESA_STATUS
GnbBuildIvmdList (
  IN       IVRS_BLOCK_TYPE            Type,
  IN       VOID                       *Ivrs,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

VOID
GnbIommuIvrsTableDump (
  IN       VOID                 *Ivrs,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  );


IOMMU_IVRS_HEADER IvrsHeader = {
  {'I', 'V', 'R', 'S'},
  sizeof (IOMMU_IVRS_HEADER),
  2,
  0,
  {'A', 'M', 'D', ' ', ' ', 0},
  {'A', 'M', 'D', 'I', 'O', 'M', 'M', 'U'},
  1,
  {'A','M','D',' '},
  0,
  0,
  0
};

/*----------------------------------------------------------------------------------------*/
/**
 * Create gnb ioapic IVHD entry
 *
 *
 * @param[in]  GnbHandle       Gnb handle
 * @param[in]  Ivhd            IVHD header pointer
 * @param[in]  StdHeader       Standard configuration header
 *
 */
VOID
GnbIvhdAddApicEntry (
  IN       GNB_HANDLE                 *GnbHandle,
     OUT   IVRS_IVHD_ENTRY            *Ivhd,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  UINT32              AddressLow;
  UINT32              AddressHigh;
  UINT64              IoapicAddress;
  D0F0xFC_x00_STRUCT  D0F0xFC_x00;
  PCI_ADDR            GnbPciAddress;
  PCI_ADDR            GnbIoapicPciId;
  AMD_LATE_PARAMS     *LateParamsPtr;

  LateParamsPtr = (AMD_LATE_PARAMS *) StdHeader;

  // Get the PCI address of the GNB
  GnbPciAddress = GnbGetHostPciAddress (GnbHandle);

  // Get gnb ioapic address
  GnbLibPciIndirectRead (
    GnbPciAddress.AddressValue | D0F0xF8_ADDRESS,
    D0F0xFC_x01_ADDRESS,
    AccessS3SaveWidth32,
    &AddressLow,
    StdHeader
    );
  GnbLibPciIndirectRead (
    GnbPciAddress.AddressValue | D0F0xF8_ADDRESS,
    D0F0xFC_x02_ADDRESS,
    AccessS3SaveWidth32,
    &AddressHigh,
    StdHeader
    );
  IoapicAddress = ((UINT64) AddressHigh) << 32;
  IoapicAddress |= ((UINT64) AddressLow) & 0xffffff00;

  // Get gnb ioapic enable state
  GnbLibPciIndirectRead (
    GnbPciAddress.AddressValue | D0F0xF8_ADDRESS,
    D0F0xFC_x00_ADDRESS,
    AccessS3SaveWidth32,
    &D0F0xFC_x00.Value,
    StdHeader
    );

  if ((IoapicAddress != 0) && (D0F0xFC_x00.Field.IoapicEnable == 1) && (LateParamsPtr->GnbLateConfiguration.GnbIoapicId != 0xff)) {
    GnbIoapicPciId.AddressValue = GnbPciAddress.AddressValue;
    GnbIoapicPciId.Address.Function = 1;
    GnbIvhdAddSpecialDeviceEntry (
      IvhdSpecialDeviceIoapic,
      GnbIoapicPciId,
      LateParamsPtr->GnbLateConfiguration.GnbIoapicId,
      0,
      Ivhd,
      StdHeader
      );
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Calculate an ACPI style checksum
 *
 * Computes the checksum and stores the value to the checksum
 * field of the passed in ACPI table's header.
 *
 * @param[in]  Table             ACPI table to checksum
 * @param[in]  StdHeader         Config handle for library and services
 *
 */
VOID
ChecksumAcpiTable (
  IN OUT   ACPI_TABLE_HEADER *Table,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8  *BuffTempPtr;
  UINT8  Checksum;
  UINT32 BufferOffset;

  Table->Checksum = 0;
  Checksum = 0;
  BuffTempPtr = (UINT8 *) Table;
  for (BufferOffset = 0; BufferOffset < Table->TableLength; BufferOffset++) {
    Checksum = Checksum - *(BuffTempPtr + BufferOffset);
  }

  Table->Checksum = Checksum;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build IVRS table
 *
 *
 *
 * @param[in]     StdHeader       Standard Configuration Header
 * @retval        AGESA_SUCCESS
 * @retval        AGESA_ERROR
 */

AGESA_STATUS
GnbIommuIvrsTable (
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  AGESA_STATUS            Status;
  AMD_LATE_PARAMS         *LateParamsPtr;
  VOID                    *Ivrs;
  BOOLEAN                 IvrsSupport;
  GNB_HANDLE              *GnbHandle;

  Status = AGESA_SUCCESS;
  LateParamsPtr = (AMD_LATE_PARAMS*) StdHeader;
  IvrsSupport = FALSE;
  Ivrs = LateParamsPtr->AcpiIvrs;
  if (Ivrs == NULL) {
    Ivrs = GnbAllocateHeapBuffer (
             AMD_ACPI_IVRS_BUFFER_HANDLE,
             IVRS_TABLE_LENGTH,
             StdHeader
             );
    ASSERT (Ivrs != NULL);
    if (Ivrs == NULL) {
      return  AGESA_ERROR;
    }
    LateParamsPtr->AcpiIvrs = Ivrs;
  }
  LibAmdMemFill (Ivrs, 0x0, IVRS_TABLE_LENGTH, StdHeader);
  LibAmdMemCopy (Ivrs, &IvrsHeader, sizeof (IvrsHeader), StdHeader);
  // Update table OEM fields.
  LibAmdMemCopy (
    (VOID *) &((ACPI_TABLE_HEADER*) Ivrs)->OemId,
    (VOID *) &GnbBuildOptions.OemIdString,
    sizeof (GnbBuildOptions.OemIdString),
    StdHeader);
  LibAmdMemCopy (
    (VOID *) &((ACPI_TABLE_HEADER*) Ivrs)->OemTableId,
    (VOID *) &GnbBuildOptions.OemTableIdString,
    sizeof (GnbBuildOptions.OemTableIdString),
    StdHeader);

  GnbHandle = GnbGetHandle (StdHeader);
  while (GnbHandle != NULL) {
    if (GnbFmCheckIommuPresent (GnbHandle, StdHeader)) {
      IDS_HDT_CONSOLE (GNB_TRACE, "Build IVRS for Socket %d Silicon %d\n", GnbGetSocketId (GnbHandle) , GnbGetSiliconId (GnbHandle));
      IvrsSupport = TRUE;
      GnbFmCreateIvrsEntry (GnbHandle, IvrsIvhdBlock10h, Ivrs, StdHeader);
      GnbFmCreateIvrsEntry (GnbHandle, IvrsIvhdBlock11h, Ivrs, StdHeader);
      GnbBuildIvmdList (IvrsIvmdBlock, Ivrs, StdHeader);
      if (GnbBuildOptions.IvrsRelativeAddrNamesSupport) {
        GnbFmCreateIvrsEntry (GnbHandle, IvrsIvhdrBlock40h, Ivrs, StdHeader);
        GnbFmCreateIvrsEntry (GnbHandle, IvrsIvhdrBlock41h, Ivrs, StdHeader);
        GnbBuildIvmdList (IvrsIvmdrBlock, Ivrs, StdHeader);
      }
    }
    GnbHandle = GnbGetNextHandle (GnbHandle);
  }
  if (IvrsSupport == TRUE) {
    ChecksumAcpiTable ((ACPI_TABLE_HEADER*) Ivrs, StdHeader);
    GNB_DEBUG_CODE (GnbIommuIvrsTableDump (Ivrs, StdHeader));
  } else {
    IDS_HDT_CONSOLE (GNB_TRACE, "  IVRS table not generated\n");
    LateParamsPtr->AcpiIvrs = NULL;
  }
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build IVMD list
 *
 *
 * @param[in]  Type            Entry type
 * @param[in]  Ivrs            IVRS table pointer
 * @param[in]  StdHeader       Standard configuration header
 *
 */

AGESA_STATUS
GnbBuildIvmdList (
  IN       IVRS_BLOCK_TYPE            Type,
  IN       VOID                       *Ivrs,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  )
{
  IOMMU_EXCLUSION_RANGE_DESCRIPTOR  *IvrsExclusionRangeList;
  IVRS_IVMD_ENTRY                   *Ivmd;
  UINT16                            StartId;
  UINT16                            EndId;

  IDS_HDT_CONSOLE (GNB_TRACE, "GnbBuildIvmdList Entry\n");
  IvrsExclusionRangeList = ((AMD_LATE_PARAMS*)StdHeader)->IvrsExclusionRangeList;
  if (IvrsExclusionRangeList != NULL) {
    // Process the entire IvrsExclusionRangeList here and create an IVMD for eache entry
    IDS_HDT_CONSOLE (GNB_TRACE, "Process Exclusion Range List\n");
    while ((IvrsExclusionRangeList->Flags & DESCRIPTOR_TERMINATE_LIST) == 0) {
      if ((IvrsExclusionRangeList->Flags & DESCRIPTOR_IGNORE) == 0) {
        // Address of IVMD entry
        Ivmd = (IVRS_IVMD_ENTRY*) ((UINT8 *)Ivrs + ((IOMMU_IVRS_HEADER *) Ivrs)->TableLength);
        StartId =
          (IvrsExclusionRangeList->RequestorIdStart.Bus << 8) +
          (IvrsExclusionRangeList->RequestorIdStart.Device << 3) +
          (IvrsExclusionRangeList->RequestorIdStart.Function);
        EndId =
          (IvrsExclusionRangeList->RequestorIdEnd.Bus << 8) +
          (IvrsExclusionRangeList->RequestorIdEnd.Device << 3) +
          (IvrsExclusionRangeList->RequestorIdEnd.Function);
        GnbIvmdAddEntry (
          Type,
          StartId,
          EndId,
          IvrsExclusionRangeList->RangeBaseAddress,
          IvrsExclusionRangeList->RangeLength,
          Ivmd,
          StdHeader);
        // Add entry size to existing table length
        ((IOMMU_IVRS_HEADER *)Ivrs)->TableLength += sizeof (IVRS_IVMD_ENTRY);
      }
      // Point to next entry in IvrsExclusionRangeList
      IvrsExclusionRangeList++;
    }
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "GnbBuildIvmdList Exit\n");
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump IVRS table
 *
 *
 * @param[in]     Ivrs            Pointer to IVRS table
 * @param[in]     StdHeader       Standard Configuration Header
 */

VOID
GnbIommuIvrsTableDump (
  IN       VOID                 *Ivrs,
  IN       AMD_CONFIG_PARAMS    *StdHeader
  )
{
  UINT8   *Block;
  UINT8   *Entry;
  Block = (UINT8 *) Ivrs + sizeof (IOMMU_IVRS_HEADER);
  IDS_HDT_CONSOLE (GNB_TRACE, "<----------  IVRS Table Start -----------> \n");
  IDS_HDT_CONSOLE (GNB_TRACE, "  IVInfo           = 0x%08x\n", ((IOMMU_IVRS_HEADER *) Ivrs)-> IvInfo);
  while (Block < ((UINT8 *) Ivrs + ((IOMMU_IVRS_HEADER *) Ivrs)->TableLength)) {
    if (*Block == IvrsIvhdBlock10h || *Block == IvrsIvhdBlock11h) {
      IDS_HDT_CONSOLE (GNB_TRACE, "  <-------------IVHD Block Start -------->\n");
      IDS_HDT_CONSOLE (GNB_TRACE, "  Flags            = 0x%02x\n", ((IVRS_IVHD_ENTRY *) Block)->Flags);
      IDS_HDT_CONSOLE (GNB_TRACE, "  Type             = 0x%02x\n", ((IVRS_IVHD_ENTRY *) Block)->Type);
      IDS_HDT_CONSOLE (GNB_TRACE, "  DeviceId         = 0x%04x\n", ((IVRS_IVHD_ENTRY *) Block)->DeviceId);
      IDS_HDT_CONSOLE (GNB_TRACE, "  CapabilityOffset = 0x%02x\n", ((IVRS_IVHD_ENTRY *) Block)->CapabilityOffset);
      IDS_HDT_CONSOLE (GNB_TRACE, "  BaseAddress      = 0x%08x%08x\n", (UINT32) (((IVRS_IVHD_ENTRY *) Block)->BaseAddress >> 32), (UINT32) ((IVRS_IVHD_ENTRY *) Block)->BaseAddress);
      IDS_HDT_CONSOLE (GNB_TRACE, "  PCI Segment      = 0x%04x\n", ((IVRS_IVHD_ENTRY *) Block)->PciSegment);
      IDS_HDT_CONSOLE (GNB_TRACE, "  IommuInfo        = 0x%04x\n", ((IVRS_IVHD_ENTRY *) Block)->IommuInfo);
      if (*Block == IvrsIvhdBlock11h) {
        IDS_HDT_CONSOLE (GNB_TRACE, "  IommuAttributes  = 0x%08x\n", ((IVRS_IVHD_ENTRY_11H *) Block)->IommuAttributes);
        IDS_HDT_CONSOLE (GNB_TRACE, "  IommuEfr         = 0x%08x\n", ((IVRS_IVHD_ENTRY_11H *) Block)->IommuEfr);
        Entry = Block + sizeof (IVRS_IVHD_ENTRY_11H);
      } else {
        IDS_HDT_CONSOLE (GNB_TRACE, "  IommuEfr         = 0x%08x\n", ((IVRS_IVHD_ENTRY_10H *) Block)->IommuEfr);
        Entry = Block + sizeof (IVRS_IVHD_ENTRY_10H);
      }
      IDS_HDT_CONSOLE (GNB_TRACE, "  <-------------IVHD Block Device Entries Start -------->\n");
      while (Entry < (Block + ((IVRS_IVHD_ENTRY *) Block)->Length)) {
        IDS_HDT_CONSOLE (GNB_TRACE, "  ");
        switch (*Entry) {
        case IvhdEntrySelect:
        case IvhdEntryEndRange:
          GnbLibDebugDumpBuffer (Entry, 4, 1, 4);
          Entry = Entry + 4;
          break;
        case IvhdEntryStartRange:
          GnbLibDebugDumpBuffer (Entry, 8, 1, 8);
          Entry = Entry + 8;
          break;
        case IvhdEntryAliasStartRange:
          GnbLibDebugDumpBuffer (Entry, 12, 1, 12);
          Entry = Entry + 12;
          break;
        case IvhdEntryAliasSelect:
        case IvhdEntryExtendedSelect:
        case IvhdEntrySpecialDevice:
          GnbLibDebugDumpBuffer (Entry, 8, 1, 8);
          Entry = Entry + 8;
          break;
        case IvhdEntryPadding:
          Entry = Entry + 4;
          break;
        default:
          IDS_HDT_CONSOLE (GNB_TRACE, "  Unsupported entry type [%d]\n");
          ASSERT (FALSE);
        }
      }
      IDS_HDT_CONSOLE (GNB_TRACE, "  <-------------IVHD Block Device Entries End -------->\n");
      IDS_HDT_CONSOLE (GNB_TRACE, "  <-------------IVHD Block End ---------->\n");
    } else if (
        (*Block == IvrsIvmdBlock) ||
        (*Block == IvrsIvmdBlockRange) ||
        (*Block == IvrsIvmdBlockSingle) ||
        (*Block == IvrsIvmdrBlock) ||
        (*Block == IvrsIvmdrBlockSingle)) {
      IDS_HDT_CONSOLE (GNB_TRACE, "  <-------------IVMD Block Start -------->\n");
      IDS_HDT_CONSOLE (GNB_TRACE, "  Flags            = 0x%02x\n", ((IVRS_IVMD_ENTRY *) Block)->Flags);
      IDS_HDT_CONSOLE (GNB_TRACE, "  DeviceId         = 0x%04x\n", ((IVRS_IVMD_ENTRY *) Block)->DeviceId);
      switch (*Block) {
      case IvrsIvmdBlock:
      case IvrsIvmdrBlock:
        IDS_HDT_CONSOLE (GNB_TRACE, "  Applies to all devices\n");
        break;
      case IvrsIvmdBlockSingle:
      case IvrsIvmdrBlockSingle:
        IDS_HDT_CONSOLE (GNB_TRACE, "  Applies to a single device\n");
        break;
      default:
        IDS_HDT_CONSOLE (GNB_TRACE, "  DeviceId End   = 0x%04x\n", ((IVRS_IVMD_ENTRY *) Block)->AuxiliaryData);
      }
      IDS_HDT_CONSOLE (GNB_TRACE, "  StartAddress     = 0x%08x%08x\n", (UINT32) (((IVRS_IVMD_ENTRY *) Block)->BlockStart >> 32), (UINT32) ((IVRS_IVMD_ENTRY *) Block)->BlockStart);
      IDS_HDT_CONSOLE (GNB_TRACE, "  BockLength       = 0x%08x%08x\n", (UINT32) (((IVRS_IVMD_ENTRY *) Block)->BlockLength >> 32), (UINT32) ((IVRS_IVMD_ENTRY *) Block)->BlockLength);
      IDS_HDT_CONSOLE (GNB_TRACE, "  <-------------IVMD Block End ---------->\n");
    }
    Block = Block + ((IVRS_IVHD_ENTRY *) Block)->Length;
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "<----------  IVRS Table Raw Data --------> \n");
  GnbLibDebugDumpBuffer (Ivrs, ((IOMMU_IVRS_HEADER *) Ivrs)->TableLength, 1, 16);
  IDS_HDT_CONSOLE (GNB_TRACE, "\n");
  IDS_HDT_CONSOLE (GNB_TRACE, "<----------  IVRS Table End -------------> \n");
}


