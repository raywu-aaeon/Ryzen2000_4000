/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate Component Locality Distance Information Table (CDIT)
 *
 * Contains code that generate Component Locality Distance Information Table (CDIT)
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
#include "AmdAcpiCdit.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Library/BaseLib.h"
#include <Protocol/AmdAcpiCditServicesProtocol.h>
#include "PiDxe.h"

#define FILECODE UNIVERSAL_ACPI_AMDACPICDIT_FILECODE

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *  All of the DATA should be defined in _CODE segment.
 *  Use ROMDATA to specify that it belongs to _CODE.
 *----------------------------------------------------------------------------
 */
STATIC CDIT_HEADER  ROMDATA CditHeaderStruct =
{
  {'C','D','I','T'},
  0,
  1,
  0,
  {0},
  {0},
  1,
  {'A','M','D',' '},
  1,
  1
};


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 *---------------------------------------------------------------------------------------
 *
 *  Generate CDIT
 *
 *  Description:
 *    This function will generate a complete Component Locality Distance Information Table
 *    i.e. CDIT into a memory buffer.
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
AmdAcpiCdit (
  IN       EFI_ACPI_TABLE_PROTOCOL  *AcpiTableProtocol,
  IN       AMD_CONFIG_PARAMS        *StdHeader
  )
{
  UINT8               *Distance;
  UINT8                NumberOfDomains;
  UINTN                TableSize;
  UINTN                TableKey;
  CDIT_HEADER         *CditHeaderStructPtr;
  ALLOCATE_HEAP_PARAMS AllocParams;
  AMD_FABRIC_ACPI_CDIT_SERVICES_PROTOCOL *FabricCditServices;

  // Locate protocol
  if (gBS->LocateProtocol (&gAmdFabricAcpiCditServicesProtocolGuid, NULL, (VOID **) &FabricCditServices) != EFI_SUCCESS) {
    return AGESA_ERROR;
  }

  // Allocate a buffer
  AllocParams.RequestedBufferSize = ACPI_TABLE_MAX_LENGTH;
  AllocParams.BufferHandle = AMD_ACPI_TABLE_BUFFER_HANDLE;
  AllocParams.Persist = HEAP_SYSTEM_MEM;


  if (HeapAllocateBuffer (&AllocParams, StdHeader) != AGESA_SUCCESS) {
    return AGESA_ERROR;
  }

  CditHeaderStructPtr = (CDIT_HEADER *) AllocParams.BufferPtr;
  Distance = (UINT8 *) CditHeaderStructPtr + sizeof (CDIT_HEADER);

  // Copy CditHeaderStruct -> data buffer
  LibAmdMemCopy ((VOID *) CditHeaderStructPtr, (VOID *) &CditHeaderStruct, (UINTN) (sizeof (CDIT_HEADER)), StdHeader);
  // Update table OEM fields.
  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 100) <= 6);
  ASSERT (AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiCditTableHeaderOemTableId), 100) <= 8);

  LibAmdMemCopy ((VOID *) &CditHeaderStructPtr->OemId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiTableHeaderOemId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiTableHeaderOemId), 6),
                 StdHeader);
  LibAmdMemCopy ((VOID *) &CditHeaderStructPtr->OemTableId,
                 (VOID *) PcdGetPtr (PcdAmdAcpiCditTableHeaderOemTableId),
                 AsciiStrnLenS (PcdGetPtr (PcdAmdAcpiCditTableHeaderOemTableId), 8),
                 StdHeader);

  // Get CDID from gAmdFabricAcpiCditServicesProtocolGuid
  FabricCditServices->GetCditDistanceInfo (FabricCditServices, &NumberOfDomains, Distance);

  // Update number of system localities
  CditHeaderStructPtr->NumDomains = (UINT64) NumberOfDomains;

  // Store size in table (current buffer offset - buffer start offset)
  CditHeaderStructPtr->Length = sizeof (CDIT_HEADER) + (UINT32) (NumberOfDomains * NumberOfDomains);


  // Boundary check
  ASSERT (CditHeaderStructPtr->Length <= ACPI_TABLE_MAX_LENGTH);
  if (CditHeaderStructPtr->Length > ACPI_TABLE_MAX_LENGTH) {
    IDS_HDT_CONSOLE (CPU_TRACE, "ERROR: ACPI table buffer is overflow\n");
    IDS_DEADLOOP ()
  }

  // Update SSDT header Checksum
  ChecksumAcpiTable ((ACPI_TABLE_HEADER *) CditHeaderStructPtr, StdHeader);

  // Publish SSDT
  TableSize = CditHeaderStructPtr->Length;
  TableKey = 0;
  AcpiTableProtocol->InstallAcpiTable (
                  AcpiTableProtocol,
                  CditHeaderStructPtr,
                  TableSize,
                  &TableKey
                  );

  // Deallocate heap
  HeapDeallocateBuffer (AMD_ACPI_TABLE_BUFFER_HANDLE, StdHeader);

  IDS_HDT_CONSOLE (MAIN_FLOW, "  CDIT is created\n");
  return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


