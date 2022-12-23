/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP TPM ACPI related functions
 *
 * Contains PSP TPM interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision$   @e \$Date$
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
 **/

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspCommonLib.h>
#include <Library/AmdPspFtpmLib.h>
#include <Protocol/AmdPspFtpmProtocol.h>

#include <Protocol/AcpiSupport.h>
#include <Protocol/AcpiSystemDescriptionTable.h>

//fTPM ACPI Object (AML code binary)
#include "fTPMAmlData.h"
#include "fTPMAcpi.h"


STATIC TPM2_ACPI_TABLE  Tpm2AcpiTable = {
  {
    SIGNATURE_32 ('T','P','M','2'),
    sizeof (TPM2_ACPI_TABLE),
    0x03,                             // ACPI Revision.
    0x00,
    TPM2_ACPI_OEM_ID,                 // OEM ID (filled in below).
    TPM2_ACPI_TABLE_OEM_ID,           // OEM Table ID (filled in below).
    TPM2_ACPI_OEM_REVISION ,          // ACPI OEM Revision (filled in below).
    1,                                // OEM Creator ID (filled in below).
    1                                 // OEM Creator Revision (filled in below).
   },
   0,                                 // Flags
   0,                                 // ControlArea
   0x02                               // StartMethod
};

VOID
EFIAPI
fTPMAcpiPublish (
  VOID
  )
{
  EFI_STATUS                  Status;
  EFI_ACPI_SUPPORT_PROTOCOL   *AcpiSupport;
  UINTN                       TableHandle;
  TPM2_CONTROL_AREA           *Tpm2ControlArea;
  UINT8                       *Tpm2AcpiDataPtr;
  UINT32                      *Memory32Fixed;
  EFI_ACPI_TABLE_VERSION      Version;

//
// Locate ACPISupport table. Bail if absent
//
  Status = gBS->LocateProtocol (
                  &gEfiAcpiSupportProtocolGuid,
                  NULL,
                  &AcpiSupport);
  if (EFI_ERROR (Status)) {
    return;
  }

  if (GetFtpmControlArea (&Tpm2ControlArea)) {
    return;
  }

  // Update the TPM ACPI Table for ControlArea location
  Tpm2AcpiTable.ControlArea = (EFI_PHYSICAL_ADDRESS) Tpm2ControlArea + 0x10;

  //
  // Install the ACPI Table
  //
  IDS_HDT_CONSOLE_PSP_TRACE ("\tInstall ACPI TPM2 Table\n");
  TableHandle = 0;
  Version = (EFI_ACPI_TABLE_VERSION_1_0B | EFI_ACPI_TABLE_VERSION_2_0 | EFI_ACPI_TABLE_VERSION_3_0 |
             EFI_ACPI_TABLE_VERSION_4_0) ;
  Status = AcpiSupport->SetAcpiTable (
                  AcpiSupport,
                  &Tpm2AcpiTable,
                  TRUE,
                  Version,
                  &TableHandle
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("\tUpdate _CRS Object with actual value\n");

  //Update _CRS Object with actual value
  for (Tpm2AcpiDataPtr = ((UINT8 *)fTPMAmlData + sizeof (EFI_ACPI_DESCRIPTION_HEADER));
       Tpm2AcpiDataPtr <= ((UINT8 *)fTPMAmlData + ((EFI_ACPI_DESCRIPTION_HEADER *)fTPMAmlData)->Length);
       Tpm2AcpiDataPtr++
       ) {
    Memory32Fixed = (UINT32 *)Tpm2AcpiDataPtr;
    switch (*Memory32Fixed) {
    //TPM2.0 Command Buffer allocate by BIOS, should be updated during POST
    //Memory32Fixed (ReadWrite, 0xBBBBBBBB, 0x100000)
    case 0xBBBBBBBB:
      *Memory32Fixed = (UINT32) (Tpm2ControlArea->CommandAddress);
      IDS_HDT_CONSOLE_PSP_TRACE ("Tpm2ControlArea->CommandAddress %x\n", Tpm2ControlArea->CommandAddress);
      Tpm2AcpiDataPtr += (sizeof (UINT32) - 1);
      break;
    //TPM2.0 Response Buffer allocate by BIOS, should be updated during POST
    //Memory32Fixed (ReadWrite, 0xCCCCCCCC, 0x100000)
    case 0xCCCCCCCC:
      *Memory32Fixed = (UINT32) (Tpm2ControlArea->ResponseAddress);
      IDS_HDT_CONSOLE_PSP_TRACE ("Tpm2ControlArea->ResponseAddress %x\n", Tpm2ControlArea->ResponseAddress);
      Tpm2AcpiDataPtr += (sizeof (UINT32) - 1);
      break;
    default:
      break;
    }
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("\tInstall Tpm SSDT table\n");

  TableHandle = 0;
  AcpiSupport->SetAcpiTable (
                 AcpiSupport,
                 fTPMAmlData,
                 TRUE,
                 Version,
                 &TableHandle
                 );
  if (EFI_ERROR (Status)) {
    return;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("PublishTables ACPI table\n");

  Status = AcpiSupport->PublishTables (AcpiSupport, Version);
  if (EFI_ERROR (Status)) {
    return;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("fTPMAcpiEvent exit\n");

}

EFI_STATUS
fTpmAcpiEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )

{
  EFI_STATUS                  Status;

  //If PSP feature turn off, exit the driver
  Status = CheckPspDevicePresent ();
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.Drv.fTpmAcpiEntryPoint Enter\n");

  fTPMAcpiPublish ();

  IDS_HDT_CONSOLE_PSP_TRACE ("fTpmAcpiEntryPoint Exit\n");
  return Status;
}

