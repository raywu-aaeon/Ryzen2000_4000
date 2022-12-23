/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioALibRVDxe Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioALibRVDxe
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <Filecode.h>
#include <PiDxe.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdNbioBaseServicesProtocol.h>
#include <Library/UefiLib.h>
#include <Protocol/AcpiTable.h>
#include <Library/NbioIommuIvrsLib.h>
#include <Protocol/AmdNbioAlibServicesProtocol.h>
#include <AlibSsdtRV.h>
#include "AmdNbioAlibCallback.h"

#define FILECODE NBIO_NBIOALIB_AMDNBIOALIBRVDXE_AMDNBIOALIBRVDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
AmdGetAlibAddress (
  IN       DXE_AMD_NBIO_ALIB_SERVICES_PROTOCOL      *This,
     OUT   VOID                                     **AlibAddressOutput
  )
{
  *AlibAddressOutput = &AlibSsdtRV;
}

DXE_AMD_NBIO_ALIB_SERVICES_PROTOCOL mDxeAmdNbioAlibServicesProtocol = {
  AMD_ALIB_SERVICES_DXE_REVISION,
  AmdGetAlibAddress
};

/**
 *---------------------------------------------------------------------------------------
 *  InstallALibAcpiTable
 *
 *  Description:
 *     notification event handler for install ALib Acpi Table
 *  Parameters:
 *    @param[in]     Event      Event whose notification function is being invoked.
 *    @param[in]     *Context   Pointer to the notification function's context.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
InstallALibAcpiTable (
  IN       EFI_EVENT  Event,
  IN       VOID       *Context
  )
{
  EFI_ACPI_TABLE_PROTOCOL *AcpiTable;
  EFI_STATUS              Status;
  VOID                    *AlibBuffer;

  IDS_HDT_CONSOLE (MAIN_FLOW, "InstallALibAcpiTable Start\n");
  AlibBuffer = NULL;

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **)&AcpiTable);
  if (EFI_ERROR (Status)) {
    return;
  }
  //
  // Create ACPI ALIB SSDT table
  //
  PcieAlibBuildAcpiTable ((VOID **)&AlibBuffer);


  //
  // Close event, so it will not be invoked again.
  //
  gBS->CloseEvent (Event);
  IDS_HDT_CONSOLE (MAIN_FLOW, "InstallALibAcpiTable End\n");
}


EFI_STATUS
EFIAPI
AmdNbioAlibRVDxeEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                           Status;
  EFI_HANDLE                           Handle;
  VOID *Registration;

  AGESA_TESTPOINT (TpNbioAlibDxeEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioAlibRVDxeEntry Enter\n");
  Handle = NULL;

  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdNbioALibServicesProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mDxeAmdNbioAlibServicesProtocol
                  );
  EfiCreateProtocolNotifyEvent (&gEfiAcpiTableProtocolGuid, TPL_CALLBACK, InstallALibAcpiTable, NULL, &Registration);

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioAlibRVDxeEntry Exit\n");
  AGESA_TESTPOINT (TpNbioAlibDxeExit, NULL);

  return Status;
}

