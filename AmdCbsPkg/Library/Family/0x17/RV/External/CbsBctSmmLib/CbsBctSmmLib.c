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


#include <Base.h>
#include <Uefi.h>

#include <Protocol/HiiConfigRouting.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>

#include <Guid/MdeModuleHii.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HiiLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiLib.h>

#include <Library/AmdCbsSetupLib.h>
#include <Protocol/AmdCbsHookProtocol.h>
#include "AmdCbsVariable.h"
#include "AmdCbsFormID.h"
#include "AmdSoc.h"

#include "Porting.h"
#include "Addendum/Apcb/Inc/RV/APCB.h"
#include "ApcbCommon.h"
#include "Protocol/AmdApcbProtocol.h"
#include "Library/AmdPspBaseLibV2.h"
#include "Library/CbsBctSmmLib.h"

extern  EFI_GUID gAmdApcbSmmServiceProtocolGuid;

VOID
PrepareCmnTypeAttrib (
  UINT32 *Size,
  APCB_PARAM_ATTRIBUTE *ApcbParaAttrib,
  VOID *CbsVariable
  );

VOID
PrepareCmnTypeValue (
  UINT32 *Size,
  UINT8 *ApcbParaValue,
  VOID *CbsVariable
  );

EFI_STATUS
EFIAPI
CbsBctSetVariable (
  IN CBS_BCT_SMM_PROTOCOL    *This,
  IN UINT8                   *IfrData
)
{
  EFI_STATUS                      Status;
  BOOLEAN                         ApcbEntryExist;
  TYPE_ATTRIB                     TypeAttrib;
  UINT64                          OldApcbPtr;
  UINT32                          EntrySize;
  UINT64                          EntryDest;
  UINT32                          AttributeSize;
  UINT32                          ValueSize;
  UINT32                          TotalSizeExt;
  UINT8                           *DataStream;
  UINT8                           *ValueStream;
  UINT8                           *NewApcbPtr;
  AMD_APCB_SERVICE_PROTOCOL       *mApcbSmmServiceProtocol;

  NewApcbPtr = NULL;
  Status = EFI_SUCCESS;
  // Check the existence and size of APCB  entry 0x60
  ApcbEntryExist = BIOSEntryInfo (BIOS_APCB_INFO, INSTANCE_IGNORED, &TypeAttrib, &OldApcbPtr, &EntrySize, &EntryDest);
  if (ApcbEntryExist == FALSE) {
    DEBUG ((EFI_D_ERROR, "BCT Error: APCB Entry doesn't exist\n"));
    return EFI_UNSUPPORTED;
  }

  // Calculate the buffer needed to store the external byte stream
  AttributeSize = 0;
  ValueSize = 0;
  DataStream = NULL;
  PrepareCmnTypeAttrib (&AttributeSize, (APCB_PARAM_ATTRIBUTE *)DataStream, (CBS_CONFIG *)IfrData);
  PrepareCmnTypeValue (&ValueSize, DataStream, (CBS_CONFIG *)IfrData);
  TotalSizeExt = AttributeSize + ValueSize;
  TotalSizeExt += ((ALIGN_SIZE_OF_TYPE - (TotalSizeExt % ALIGN_SIZE_OF_TYPE)) & (ALIGN_SIZE_OF_TYPE - 1));

  if (0 != TotalSizeExt) {
    DEBUG ((EFI_D_ERROR, "Replace CBS Common Options\n"));
    // Allocate buffer for new Type data stream
    DataStream = NULL;
    DataStream = AllocateZeroPool (TotalSizeExt);
    if (DataStream == NULL) {
      DEBUG ((EFI_D_ERROR, "BCT Error: fail to allocate buffer for new type data stream\n"));
      return EFI_UNSUPPORTED;
    }

    // Create new Type data stream
    PrepareCmnTypeAttrib (&AttributeSize, (APCB_PARAM_ATTRIBUTE *)DataStream, (CBS_CONFIG *)IfrData);
    ValueStream = &DataStream[AttributeSize];
    PrepareCmnTypeValue (&ValueSize, ValueStream, (CBS_CONFIG *)IfrData);

    Status = gSmst->SmmLocateProtocol (
                &gAmdApcbSmmServiceProtocolGuid,
                NULL,
                &mApcbSmmServiceProtocol
                );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = mApcbSmmServiceProtocol->ApcbUpdateCbsData (mApcbSmmServiceProtocol, DataStream, TotalSizeExt, FALSE);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    // Free temporary buffer
    Status = gSmst->SmmFreePool (DataStream);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }
  return Status;
}

EFI_STATUS
EFIAPI
CbsBctWriteFlash (
)
{
  EFI_STATUS                      Status;
  AMD_APCB_SERVICE_PROTOCOL       *mApcbSmmServiceProtocol;

  Status = gSmst->SmmLocateProtocol (
              &gAmdApcbSmmServiceProtocolGuid,
              NULL,
              &mApcbSmmServiceProtocol
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = mApcbSmmServiceProtocol->ApcbFlushData (mApcbSmmServiceProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
