/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate Maximum System Characteristic Tables (MSCT)
 *
 * Contains code that generate Maximum System Characteristic Table (MSCT)
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
#include "AmdAcpiMsct.h"
#include "AmdAcpiDxe.h"
#include <Library/BaseLib.h>
#include <Library/CcxBaseX86Lib.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdHeapLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/CcxBaseServicesProtocol.h>
#include <Protocol/AmdAcpiMsctServicesProtocol.h>

#define FILECODE UNIVERSAL_ACPI_AMDACPIMSCT_FILECODE

STATIC MSCT_HEADER ROMDATA MsctHeaderStruct =
{
  {'M', 'S', 'C', 'T'},       // Signature
  0,                          // Length
  1,                          // Revision
  0,                          // Checksum
  {0},                        // OemId
  {0},                        // OemTableId
  0,                          // OemRevision
  {'A', 'M', 'D', ' '},       // CreatorId
  1,                          // CreatorRev
  0,                          // OffsetProxDomInfo
  0,                          // MaxProxDom
  0,                          // MaxClkDom
  0                           // MaxPhysAddr
};


VOID
STATIC
CreateMsctEntry (
  IN       UINT32 ProxDomainLo,
  IN       UINT32 ProxDomainHi,
  IN       UINT32 MaxProcCap,
  IN       UINT64 MaxMemCap,
  IN OUT   UINT8  **EndOfTable
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/**
 *---------------------------------------------------------------------------------------
 *
 *  Generate MSCT
 *
 *  Description:
 *    This function will generate a complete Maximum System Characteristic Table
 *    i.e. MSCT into a memory buffer.
 *
 *  Parameters:
 *    @param[in]       AcpiTableProtocol          Pointer to gEfiAcpiTableProtocolGuid protocol
 *    @param[in]       StdHeader                  Header for library and services
 *
 *    @retval          AGESA_ERROR                Heap allocation failed, or NUMA services protocol not
 *                                                available
 *                     AGESA_SUCCESS              MSCT successfully generated
 *
 *---------------------------------------------------------------------------------------
 */
AGESA_STATUS
AmdAcpiMsct (
  IN       EFI_ACPI_TABLE_PROTOCOL  *AcpiTableProtocol,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8                                   *EndOfTable;
  UINTN                                   TableSize;
  UINTN                                   TableKey;
  UINT32                                  i;
  UINT32                                  NumPopProxDomains;
  UINT32                                  MaxNumProxDomains;
  UINT32                                  PrevDomain;
  UINT32                                  ProxDomainLo;
  UINT32                                  PrevDomainMaxProcCap;
  UINT64                                  PrevDomainMaxMemCap;
  EFI_STATUS                              CalledStatus;
  AGESA_STATUS                            Status;
  MSCT_HEADER                             *MsctHeaderStructPtr;
  ALLOCATE_HEAP_PARAMS                    AllocParams;
  AMD_FABRIC_ACPI_MSCT_SERVICES_PROTOCOL  *FabricMsctServices;
  CCX_BASE_SERVICES_PROTOCOL              *CcxBaseServices;
  MSCT_PROX_DOMAIN_INFO                   *MsctInfo;

  // Locate Fabric MSCT services protocol
  if (gBS->LocateProtocol (&gAmdFabricAcpiMsctServicesProtocolGuid, NULL, (VOID **) &FabricMsctServices) != EFI_SUCCESS) {
    return AGESA_ERROR;
  }

  // Locate CCX Base services protocol
  if (gBS->LocateProtocol (&gAmdCcxBaseServicesProtocolGuid, NULL, (VOID **) &CcxBaseServices) != EFI_SUCCESS) {
    return AGESA_ERROR;
  }

  // Allocate space for the table
  AllocParams.RequestedBufferSize = ACPI_TABLE_MAX_LENGTH;
  AllocParams.BufferHandle        = AMD_ACPI_TABLE_BUFFER_HANDLE;
  AllocParams.Persist             = HEAP_SYSTEM_MEM;

  if (HeapAllocateBuffer (&AllocParams, StdHeader) != AGESA_SUCCESS) {
    return AGESA_ERROR;
  }

  MsctHeaderStructPtr = (MSCT_HEADER *) AllocParams.BufferPtr;
  EndOfTable = (UINT8 *) MsctHeaderStructPtr + sizeof (MSCT_HEADER);

  LibAmdMemCopy ((VOID *) MsctHeaderStructPtr, (VOID *) &MsctHeaderStruct, (UINTN) (sizeof (MSCT_HEADER)), StdHeader);

  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiMsctTableHeaderOemTableId), 100) <= 8);

  LibAmdMemCopy ((VOID *) &MsctHeaderStructPtr->OemId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6),
                 StdHeader);
  LibAmdMemCopy ((VOID *) &MsctHeaderStructPtr->OemTableId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiMsctTableHeaderOemTableId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiMsctTableHeaderOemTableId), 8),
                 StdHeader);

  CalledStatus = FabricMsctServices->GetMsctInfo (FabricMsctServices, &NumPopProxDomains, &MaxNumProxDomains, &MsctInfo);

  ASSERT (CalledStatus == EFI_SUCCESS);

  MsctHeaderStructPtr->OffsetProxDomInfo = (UINT32) (EndOfTable - (UINT8 *) MsctHeaderStructPtr);
  MsctHeaderStructPtr->MaxProxDom = MaxNumProxDomains - 1;
  MsctHeaderStructPtr->MaxClkDom = 0;
  MsctHeaderStructPtr->MaxPhysAddr =  ((UINT64) 1 << CcxBaseServices->CcxGetMaxPhysAddr (CcxBaseServices)) - 1;

  PrevDomain = 0;
  ProxDomainLo = 0;
  PrevDomainMaxProcCap = MsctInfo[0].MaxProcCap;
  PrevDomainMaxMemCap = MsctInfo[0].MaxMemCap;

  // If contiguous domains in the MSCT contain the same amount of processors and memory,
  // we can report the domains as a range with a single structure.
  for (i = 0; i < NumPopProxDomains; i++) {
    PrevDomain = i - 1;
    // If MaxProcCap and MaxMemCap of current domain do not match previous domain, we add an entry to the MSCT table
    if ((PrevDomainMaxProcCap != MsctInfo[i].MaxProcCap) || (PrevDomainMaxMemCap != MsctInfo[i].MaxMemCap)) {
      CreateMsctEntry (ProxDomainLo, PrevDomain, MsctInfo[PrevDomain].MaxProcCap, MsctInfo[PrevDomain].MaxMemCap, &EndOfTable);
      ProxDomainLo = i;
      PrevDomainMaxProcCap = MsctInfo[i].MaxProcCap;
      PrevDomainMaxMemCap = MsctInfo[i].MaxMemCap;
    }
  }

  CreateMsctEntry (ProxDomainLo, NumPopProxDomains - 1, MsctInfo[NumPopProxDomains - 1].MaxProcCap, MsctInfo[NumPopProxDomains - 1].MaxMemCap, &EndOfTable);

  // Add range for any remaining unused domains.
  if (NumPopProxDomains < MaxNumProxDomains) {
    CreateMsctEntry (NumPopProxDomains, MaxNumProxDomains - 1, 0, 0, &EndOfTable);
  }

  MsctHeaderStructPtr->Length = (UINT32) (EndOfTable - (UINT8 *) MsctHeaderStructPtr);

  // Boundary check
  ASSERT (MsctHeaderStructPtr->Length <= ACPI_TABLE_MAX_LENGTH);
  if (MsctHeaderStructPtr->Length > ACPI_TABLE_MAX_LENGTH) {
    IDS_HDT_CONSOLE (CPU_TRACE, "ERROR: ACPI table buffer overflowed\n");
    IDS_DEADLOOP ();
  }

  // Update checksum
  ChecksumAcpiTable ((ACPI_TABLE_HEADER *) MsctHeaderStructPtr, StdHeader);

  // Publish MSCT
  TableSize = MsctHeaderStructPtr->Length;
  TableKey = 0;
  CalledStatus = AcpiTableProtocol->InstallAcpiTable (
                             AcpiTableProtocol,
                             MsctHeaderStructPtr,
                             TableSize,
                             &TableKey
                             );
  if (CalledStatus == EFI_SUCCESS) {
    Status = AGESA_SUCCESS;
    IDS_HDT_CONSOLE (MAIN_FLOW, "  MSCT is created\n");
  } else {
    Status = AGESA_ERROR;
    IDS_HDT_CONSOLE (MAIN_FLOW, "  MSCT was not created\n");
  }

  // Deallocate heap
  HeapDeallocateBuffer (AMD_ACPI_TABLE_BUFFER_HANDLE, StdHeader);

  return Status;
}


/**
 *---------------------------------------------------------------------------------------
 *
 *  CreateMsctEntry
 *
 *  Description:
 *    Create the maximum proximity domain structure
 *
 *  Parameters:
 *    @param[in]      ProxDomainLo               The lowest proximity domain number in the range
 *    @param[in]      ProxDomainHi               The highest proximity domain number in the range
 *    @param[in]      MaxProcCap                 Maximum (actual) processor capacity for each proximity domain
 *    @param[in]      MaxMemCap                  Maximum (actual) memory capacity for each proximity domain
 *    @param[in,out]  EndOfTable                 Pointer to the end of the MSCT table
 *
 *
 *---------------------------------------------------------------------------------------
 */
VOID
STATIC
CreateMsctEntry (
  IN       UINT32 ProxDomainLo,
  IN       UINT32 ProxDomainHi,
  IN       UINT32 MaxProcCap,
  IN       UINT64 MaxMemCap,
  IN OUT   UINT8  **EndOfTable
  )
{

  MSCT_PROX_DOMAIN_INFO_STRUCT  *MaxProxDomStruct;

  MaxProxDomStruct = (MSCT_PROX_DOMAIN_INFO_STRUCT *) *EndOfTable;
  MaxProxDomStruct->Revision = 1;
  MaxProxDomStruct->Length = 22;
  MaxProxDomStruct->MaxProcCap = MaxProcCap;
  MaxProxDomStruct->MaxMemCap = MaxMemCap;
  MaxProxDomStruct->ProximityLow = ProxDomainLo;
  MaxProxDomStruct->ProximityHigh = ProxDomainHi;
  *EndOfTable += sizeof (MSCT_PROX_DOMAIN_INFO_STRUCT);
}
