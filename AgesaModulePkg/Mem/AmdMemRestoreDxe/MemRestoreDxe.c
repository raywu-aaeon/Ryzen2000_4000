/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Memory Context Save/Restore driver
 *
 * Contains code that performs memory context save/restore
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  MEM
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
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
#include "Uefi.h"
#include "PiDxe.h"
#include "Library/UefiBootServicesTableLib.h"

#include "AGESA.h"
#include "Library/IdsLib.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdHeapLib.h"
#include "Library/MemRestore.h"
#include "MemRestoreDxe.h"
#include "Filecode.h"

#include <IndustryStandard/SmBios.h>
#include <Protocol/Smbios.h>

#define FILECODE        MEM_AMDMEMRESTOREDXE_MEMRESTOREDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * Mark the boot completion by memory context restore
 *
 * This function marks the boot completion by memory context restore
 *
 *  Parameters:
 *    @param[in]     Event
 *    @param[in]     *Context
 *
 *    @retval        VOID
 *
 */
VOID
EFIAPI
MemRestoreBootCompleteCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS                  Status;
  EFI_SMBIOS_TABLE_HEADER     *Record;
  EFI_SMBIOS_HANDLE           SmbiosHandle;
  EFI_SMBIOS_PROTOCOL         *Smbios;
  SMBIOS_TABLE_TYPE16         *Type16Record;
  BOOLEAN                     EccCapable;

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  //Ecc WA
  EccCapable = FALSE;
  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  Status = gBS->LocateProtocol (
                  &gEfiSmbiosProtocolGuid,
                  NULL,
                  (VOID **) &Smbios
                  );

  if (!EFI_ERROR(Status)) {
    do {
      Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Record, NULL);
      if (EFI_ERROR(Status)) {
        break;
      }

      if (Record->Type == EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY) {
        Type16Record = (SMBIOS_TABLE_TYPE16 *) Record;

        if (Type16Record->MemoryErrorCorrection == 0x06) {
          EccCapable = TRUE;
          break;
        }
      }
    } while(Status == EFI_SUCCESS);

    if (EccCapable == TRUE) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "\t[AMD MemRestore] Feature disabled due to EccCapable\n");
      AmdMemRestoreDiscardCurrentMemContext ();
      return;
    }
  } else {
    ASSERT (FALSE);
  }

  AmdMemRestoreSignOff ();
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  Entry for DxeAmdMemRestoreEntry
 *
 *    @retval          EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
DxeAmdMemRestoreEntry (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_EVENT                      ReadyToBootEvent;

  IDS_HDT_CONSOLE (MAIN_FLOW, "\tDxeAmdMemRestoreEntry Entry\n");

  IDS_HDT_CONSOLE (MAIN_FLOW, "\t[AMD MemRestore] Install callback to mark boot completion by memory context restore\n");

  Status = gBS->CreateEventEx (
               EVT_NOTIFY_SIGNAL,
               TPL_NOTIFY,
               MemRestoreBootCompleteCallback,
               NULL,
               &gEfiEventReadyToBootGuid,
               &ReadyToBootEvent
             );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("\tError Installing callback\n");
    return Status;
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "\tDxeAmdMemRestoreEntry Exit\n");
  return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

