/* $NoKeywords:$ */
/**
 * @file
 *
 * Generate SMBIOS type 4 7 16 17 19 20
 *
 * Contains code that generate SMBIOS type 4 7 16 17 19 20
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
#include "AmdAcpiCpuSsdt.h"
#include "AmdAcpiSrat.h"
#include "AmdAcpiSlit.h"
#include "AmdAcpiCrat.h"
#include "AmdAcpiCdit.h"
#include "AmdAcpiMsct.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "Library/UefiBootServicesTableLib.h"
#include "Protocol/AcpiTable.h"
#include "Protocol/AmdAcpiCompleteProtocol.h"
#include "PiDxe.h"

#define FILECODE UNIVERSAL_ACPI_AMDACPIDXE_FILECODE

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

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 *---------------------------------------------------------------------------------------
 *
 *  Entry for AmdAcpiDxe
 *  Generate ACPI tables
 *
 *  Description:
 *    This function will populate ACPI tables with
 *      SLIT:
 *      SRAT:
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
AmdGenerateAcpiTables (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                 Status;
  EFI_STATUS                 CalledStatus;
  EFI_HANDLE                 Handle;
  AMD_CONFIG_PARAMS          StdHeader;
  EFI_ACPI_TABLE_PROTOCOL   *AcpiTableProtocol;
  DXE_AMD_ACPI_INIT_COMPLETE_PROTOCOL AmdAcpiInitCompleteProtocol;

  AGESA_TESTPOINT (TpUniversalAcpiEntry, NULL);

  IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdGenerateAcpiTables Entry\n");

  // Avoid re-entry by locating gAmdAcpiDxeInitCompleteProtocolGuid.
  CalledStatus = gBS->LocateProtocol (&gAmdAcpiDxeInitCompleteProtocolGuid, NULL, (VOID **)&AmdAcpiInitCompleteProtocol);
  if (CalledStatus == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "    re-entry, just return EFI_ALREADY_STARTED\n");
    AGESA_TESTPOINT (TpUniversalAcpiAbort, NULL);
    return EFI_ALREADY_STARTED;
  }

  Status = EFI_SUCCESS;

  // Locate ACPISupport table.
  CalledStatus = gBS->LocateProtocol (
                       &gEfiAcpiTableProtocolGuid,
                       NULL,
                       &AcpiTableProtocol
                       );
  if (EFI_ERROR (CalledStatus)) {
    AGESA_TESTPOINT (TpUniversalAcpiAbort, NULL);
    return CalledStatus;
  }

  // Processor SSDT
  if (PcdGetBool (PcdAmdAcpiCpuSsdt)) {
    CalledStatus = AmdAcpiCpuSSdt (AcpiTableProtocol, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  }

  // System Resource Affinity Table (SRAT)
  if (PcdGetBool (PcdAmdAcpiSrat)) {
    CalledStatus = AmdAcpiSrat (AcpiTableProtocol, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Maximum System Characteristics Table (MSCT), provided only when SRAT exists
    if ((PcdGetBool (PcdAmdAcpiMsct)) && (CalledStatus == AGESA_SUCCESS)) {
      CalledStatus = AmdAcpiMsct (AcpiTableProtocol, &StdHeader);
      Status = (CalledStatus > Status) ? CalledStatus : Status;
    }
  }

  // System Locality Distance Information Table (SLIT)
  if (PcdGetBool (PcdAmdAcpiSlit)) {
    CalledStatus = AmdAcpiSlit (AcpiTableProtocol, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  }

  // Component Resource Affinity Table (CRAT)
  if (PcdGetBool (PcdAmdAcpiCrat)) {
    CalledStatus = AmdAcpiCrat (AcpiTableProtocol, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  }

  // Component Locality Distance Information Table (CDIT)
  if (PcdGetBool (PcdAmdAcpiCdit)) {
    CalledStatus = AmdAcpiCdit (AcpiTableProtocol, &StdHeader);
    Status = (CalledStatus > Status) ? CalledStatus : Status;
  }

  // End
  IDS_HDT_CONSOLE (MAIN_FLOW, "  Install Protocol gAmdAcpiDxeInitCompleteProtocolGuid to avoid re-entry\n");
  AmdAcpiInitCompleteProtocol.Revision = 0;
  Handle = NULL;
  gBS->InstallProtocolInterface (
                          &Handle,
                          &gAmdAcpiDxeInitCompleteProtocolGuid,
                          EFI_NATIVE_INTERFACE,
                          &AmdAcpiInitCompleteProtocol
                          );

  IDS_HDT_CONSOLE (MAIN_FLOW, "  AmdGenerateAcpiTables Exit\n");

  AGESA_TESTPOINT (TpUniversalAcpiExit, NULL);

  return Status;

}


