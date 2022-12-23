/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate Component Resource Affinity Table (CRAT)
 *
 * Contains code that generate Component Resource Affinity Table (CRAT)
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
#include "AGESA.h"
#include "Filecode.h"
#include "AmdAcpiDxe.h"
#include "AmdAcpiCrat.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/BaseLib.h"
#include "Protocol/AmdCoreTopologyProtocol.h"
#include "Protocol/AmdAcpiCratServicesProtocol.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_ACPI_AMDACPICRAT_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
MakeHSAProcUnitEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MakeMemoryEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MakeCacheEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MakeTLBEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MakeFPUEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

VOID
MakeIOEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  );

CRAT_HSA_PROCESSING_UNIT *
AddOneHsaEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd
  );

CRAT_HSA_PROCESSING_UNIT *
FindNextHsaEntry (
  IN       CRAT_HSA_PROCESSING_UNIT *StartSearch,
  IN OUT   UINT8                   **TableEnd
  );

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *  All of the DATA should be defined in _CODE segment.
 *  Use ROMDATA to specify that it belongs to _CODE.
 *----------------------------------------------------------------------------
 */
STATIC CRAT_HEADER  ROMDATA CratHeaderStruct =
{
  {'C','R','A','T'},
  0,
  1,
  0,
  {0},
  {0},
  1,
  {'A','M','D',' '},
  1,
  0,
  0,
  {0, 0, 0, 0, 0, 0}
};

/// All entries that CRAT needs
// It's better to add entries in the order of CRAT_ENTRY_TYPE
CONST S_MAKE_CRAT_ENTRY ROMDATA MakeCratEntryTable[] =
{
  MakeHSAProcUnitEntry,
  MakeMemoryEntry,
  MakeCacheEntry,
  MakeTLBEntry,
  MakeFPUEntry,
  MakeIOEntry,
  NULL
};

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 *---------------------------------------------------------------------------------------
 *
 *  Generate CRAT
 *
 *  Description:
 *    This function will generate a complete Component Resource Affinity Table
 *    i.e. CRAT into a memory buffer.
 *
 *  Parameters:
 *    @param[in]       AcpiTableProtocol          Pointer to gEfiAcpiTableProtocolGuid protocol
 *    @param[in]       StdHeader                  Header for library and services
 *
 *    @retval          AGESA_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
AGESA_STATUS
AmdAcpiCrat (
  IN       EFI_ACPI_TABLE_PROTOCOL  *AcpiTableProtocol,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8                i;
  UINT8               *TableEnd;
  UINTN                TableSize;
  UINTN                TableKey;
  CRAT_HEADER         *CratHeaderStructPtr;
  ALLOCATE_HEAP_PARAMS AllocParams;

  // Allocate a buffer
  AllocParams.RequestedBufferSize = ACPI_TABLE_MAX_LENGTH;
  AllocParams.BufferHandle = AMD_ACPI_TABLE_BUFFER_HANDLE;
  AllocParams.Persist = HEAP_SYSTEM_MEM;

  if (HeapAllocateBuffer (&AllocParams, StdHeader) != AGESA_SUCCESS) {
    return AGESA_ERROR;
  }

  CratHeaderStructPtr = (CRAT_HEADER *) AllocParams.BufferPtr;
  TableEnd = (UINT8 *) CratHeaderStructPtr + sizeof (CRAT_HEADER);

  // Copy CratHeaderStruct -> data buffer
  LibAmdMemCopy ((VOID *) CratHeaderStructPtr, (VOID *) &CratHeaderStruct, (UINTN) (sizeof (CRAT_HEADER)), StdHeader);
  // Update table OEM fields.
  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 100) <= 6);
  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiCratTableHeaderOemTableId), 100) <= 8);

  LibAmdMemCopy ((VOID *) &CratHeaderStructPtr->OemId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6),
                 StdHeader);
  LibAmdMemCopy ((VOID *) &CratHeaderStructPtr->OemTableId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiCratTableHeaderOemTableId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiCratTableHeaderOemTableId), 8),
                 StdHeader);

  // Add all CRAT entries.
  // It's better to add entries in the order of CRAT_ENTRY_TYPE
  for (i = 0; MakeCratEntryTable[i].MakeCratEntry != NULL; i++) {
    MakeCratEntryTable[i].MakeCratEntry (CratHeaderStructPtr, &TableEnd, StdHeader);
  }

  // Store size in table (current buffer offset - buffer start offset)
  CratHeaderStructPtr->Length = (UINT32) (TableEnd - (UINT8 *) CratHeaderStructPtr);

  // Boundary check
  ASSERT (CratHeaderStructPtr->Length <= ACPI_TABLE_MAX_LENGTH);
  if (CratHeaderStructPtr->Length > ACPI_TABLE_MAX_LENGTH) {
    IDS_HDT_CONSOLE (CPU_TRACE, "ERROR: ACPI table buffer is overflow\n");
    IDS_DEADLOOP ()
  }

  // Update CRAT header Checksum
  ChecksumAcpiTable ((ACPI_TABLE_HEADER *) CratHeaderStructPtr, StdHeader);

  // Publish CRAT
  TableSize = CratHeaderStructPtr->Length;
  TableKey = 0;
  AcpiTableProtocol->InstallAcpiTable (
                  AcpiTableProtocol,
                  CratHeaderStructPtr,
                  TableSize,
                  &TableKey
                  );

  // Deallocate heap
  HeapDeallocateBuffer (AMD_ACPI_TABLE_BUFFER_HANDLE, StdHeader);

  IDS_HDT_CONSOLE (MAIN_FLOW, "  CRAT is created\n");
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/*---------------------------------------------------------------------------------------*/
/**
 * This function will add HSA Processing Unit entry.
 *
 *    @param[in]      CratHeaderStructPtr  CRAT header pointer
 *    @param[in, out] TableEnd             The end of CRAT
 *    @param[in, out] StdHeader            Standard Head Pointer
 *
 */
VOID
MakeHSAProcUnitEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  EFI_STATUS           CalledStatus;
  CRAT_HSA_PROCESSING_UNIT *CratHsaEntry;
  AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL *CcxAcpiCrat;
  AMD_IGPU_ACPI_CRAT_SERVICES_PROTOCOL *IGpuAcpiCrat;

  // Locate gAmdCcxAcpiCratServicesProtocol
  CalledStatus = gBS->LocateProtocol (&gAmdCcxAcpiCratServicesProtocolGuid, NULL, (VOID **) &CcxAcpiCrat);
  ASSERT (!EFI_ERROR (CalledStatus));
  if (CalledStatus != EFI_SUCCESS) {
    return;
  }
  CcxAcpiCrat->GetCratHsaProcCcxEntry (CcxAcpiCrat, CratHeaderStructPtr, TableEnd);

  // Locate gAmdIGpuAcpiCratServicesProtocol
  CalledStatus = gBS->LocateProtocol (&gAmdIGpuAcpiCratServicesProtocolGuid, NULL, (VOID **) &IGpuAcpiCrat);
  if (CalledStatus == EFI_SUCCESS) {
    CratHsaEntry = (CRAT_HSA_PROCESSING_UNIT *) (CratHeaderStructPtr + 1);
    while (CratHsaEntry != NULL) {
      CratHsaEntry = FindNextHsaEntry (CratHsaEntry, TableEnd);
      if(CratHsaEntry != NULL) {
        IGpuAcpiCrat->GetCratHsaProcIGpuEntry (IGpuAcpiCrat, CratHsaEntry);
        CratHsaEntry++;
      }
    }
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * This function will add memory entry.
 *
 *    @param[in]      CratHeaderStructPtr  CRAT header pointer
 *    @param[in, out] TableEnd             The end of CRAT
 *    @param[in, out] StdHeader            Standard Head Pointer
 *
 */
VOID
MakeMemoryEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AMD_FABRIC_ACPI_CRAT_SERVICES_PROTOCOL *CratMemory;

  if (gBS->LocateProtocol (&gAmdFabricAcpiCratServicesProtocolGuid, NULL, (VOID **) &CratMemory) == EFI_SUCCESS) {
    CratMemory->CreateMemory (CratMemory, CratHeaderStructPtr, TableEnd);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * This function will add cache entry.
 *
 *    @param[in]      CratHeaderStructPtr  CRAT header pointer
 *    @param[in, out] TableEnd             The end of CRAT
 *    @param[in, out] StdHeader            Standard Head Pointer
 *
 */
VOID
MakeCacheEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  EFI_STATUS           CalledStatus;
  AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL *CcxAcpiCrat;

  // Locate gAmdCcxAcpiCratServicesProtocol
  CalledStatus = gBS->LocateProtocol (&gAmdCcxAcpiCratServicesProtocolGuid, NULL, (VOID **) &CcxAcpiCrat);
  ASSERT (!EFI_ERROR (CalledStatus));
  if (CalledStatus != EFI_SUCCESS) {
    return;
  }

  CcxAcpiCrat->GetCratCacheEntry (CcxAcpiCrat, CratHeaderStructPtr, TableEnd);
}

/*---------------------------------------------------------------------------------------*/
/**
 * This function will add TLB entry.
 *
 *    @param[in]      CratHeaderStructPtr  CRAT header pointer
 *    @param[in, out] TableEnd             The end of CRAT
 *    @param[in, out] StdHeader            Standard Head Pointer
 *
 */
VOID
MakeTLBEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  EFI_STATUS           CalledStatus;
  AMD_CCX_ACPI_CRAT_SERVICES_PROTOCOL *CcxAcpiCrat;

  // Locate gAmdCcxAcpiCratServicesProtocol
  CalledStatus = gBS->LocateProtocol (&gAmdCcxAcpiCratServicesProtocolGuid, NULL, (VOID **) &CcxAcpiCrat);
  ASSERT (!EFI_ERROR (CalledStatus));
  if (CalledStatus != EFI_SUCCESS) {
    return;
  }

  CcxAcpiCrat->GetCratTlbEntry (CcxAcpiCrat, CratHeaderStructPtr, TableEnd);
}

/*---------------------------------------------------------------------------------------*/
/**
 * This function will add FPU entry.
 *
 *    @param[in]      CratHeaderStructPtr  CRAT header pointer
 *    @param[in, out] TableEnd             The end of CRAT
 *    @param[in, out] StdHeader            Standard Head Pointer
 *
 */
VOID
MakeFPUEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
}

/*---------------------------------------------------------------------------------------*/
/**
 * This function will add IO entry.
 *
 *    @param[in]      CratHeaderStructPtr  CRAT header pointer
 *    @param[in, out] TableEnd             The end of CRAT
 *    @param[in, out] StdHeader            Standard Head Pointer
 *
 */
VOID
MakeIOEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
}

/*---------------------------------------------------------------------------------------*/
/**
* This function will add one HSA entry.
*
*    @param[in]      CratHeaderStructPtr  CRAT header pointer
*    @param[in, out] TableEnd             The end of CRAT
*
*/
CRAT_HSA_PROCESSING_UNIT *
AddOneHsaEntry (
  IN       CRAT_HEADER       *CratHeaderStructPtr,
  IN OUT   UINT8            **TableEnd
  )
{
  CRAT_HSA_PROCESSING_UNIT *CurrentEntry;

  CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) *TableEnd;
  // Update NumNodes & Total entries
  CratHeaderStructPtr->TotalEntries++;
  CratHeaderStructPtr->NumNodes++;
  // Update TableEnd
  *TableEnd += sizeof (CRAT_HSA_PROCESSING_UNIT);
  ASSERT ((*TableEnd - (UINT8 *) CratHeaderStructPtr) <= ACPI_TABLE_MAX_LENGTH);
  // Init Type and Length
  CurrentEntry->Type = CRAT_HSA_PROC_UNIT_TYPE;
  CurrentEntry->Length = sizeof (CRAT_HSA_PROCESSING_UNIT);

  return CurrentEntry;
}


/*---------------------------------------------------------------------------------------*/
/**
* This function will add one HSA entry.
*
*    @param[in]      StartSearch          Search HSA entry from this address
*    @param[in, out] TableEnd             The end of CRAT
*
*/
CRAT_HSA_PROCESSING_UNIT *
FindNextHsaEntry (
  IN       CRAT_HSA_PROCESSING_UNIT *StartSearch,
  IN OUT   UINT8                   **TableEnd
  )
{
  BOOLEAN                   Found;
  CRAT_HSA_PROCESSING_UNIT *CurrentEntry;

  CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) StartSearch;
  Found = FALSE;

  while ((((UINT64) CurrentEntry) < ((UINT64) (*TableEnd))) && (!Found)) {
    switch (CurrentEntry->Type) {
    case CRAT_HSA_PROC_UNIT_TYPE:
      Found = TRUE;
      break;
    case CRAT_MEMORY_TYPE:
      CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) (((UINT8 *) CurrentEntry) + sizeof (CRAT_MEMORY));
      break;
    case CRAT_CACHE_TYPE:
      CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) (((UINT8 *) CurrentEntry) + sizeof (CRAT_CACHE));
      break;
    case CRAT_TLB_TYPE:
      CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) (((UINT8 *) CurrentEntry) + sizeof (CRAT_TLB));
      break;
    case CRAT_FPU_TYPE:
      CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) (((UINT8 *) CurrentEntry) + sizeof (CRAT_FPU));
      break;
    case CRAT_IO_TYPE:
      CurrentEntry = (CRAT_HSA_PROCESSING_UNIT *) (((UINT8 *) CurrentEntry) + sizeof (CRAT_IO));
      break;
    default:
      ASSERT (FALSE);
    }
  }

  if (!Found) {
    CurrentEntry = NULL;
  }

  return CurrentEntry;
}


