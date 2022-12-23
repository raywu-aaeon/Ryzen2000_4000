/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP V1 Base Library
 *
 * Contains interface to the PSP library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 317842 $   @e \$Date: 2015-04-29 15:06:52 +0800 (Wed, 29 Apr 2015) $
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


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdPspCommonServiceProtocol.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDPSPCOMMONLIBDXE_AMDPSPCOMMONLIBDXE_FILECODE

AMD_PSP_COMMON_SERVICE_PROTOCOL *mPspServicePtr = NULL;
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
GetPspServicePointer (
  )
{
  EFI_STATUS Status;
  if (mPspServicePtr == NULL) {
    Status = gBS->LocateProtocol (&gAmdPspCommonServiceProtocolGuid, NULL, &mPspServicePtr);
    if (EFI_ERROR (Status)) {
      ASSERT (FALSE);
      return Status;
    }
  }
  return EFI_SUCCESS;
}

BOOLEAN
GetFtpmControlArea (
  IN OUT   VOID **FtpmControlArea
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return FALSE;
  }

  return mPspServicePtr->GetFtpmControlArea (FtpmControlArea);
}

VOID
SwitchPspMmioDecode (
  IN       BOOLEAN SwitchFlag,
  IN OUT   UINT32 *RegisterCopy
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return;
  }
  mPspServicePtr->SwitchPspMmioDecode (SwitchFlag, RegisterCopy);
}

BOOLEAN
CheckPspDevicePresent (
  VOID
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return FALSE;
  }
  return mPspServicePtr->CheckPspDevicePresent ();
}

EFI_STATUS
CheckFtpmCaps (
  IN OUT   UINT32 *Caps
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  return mPspServicePtr->CheckFtpmCaps (Caps);
}

BOOLEAN
PSPEntryInfo (
  IN       UINT32                       EntryType,
  IN OUT   UINT64                      *EntryAddress,
  IN       UINT32                      *EntrySize
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return FALSE;
  }

  return mPspServicePtr->PSPEntryInfo (EntryType, EntryAddress, EntrySize);
}

BOOLEAN
PspLibTimeOut (
  IN       UINT64              uSec,
  IN       FP_CONDITIONER      Conditioner,
  IN       VOID                *Context
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return FALSE;
  }

  return mPspServicePtr->PspLibTimeOut (uSec, Conditioner, Context);

}

VOID
AcquirePspSmiRegMutex (
  VOID
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return;
  }

  mPspServicePtr->AcquirePspSmiRegMutex ();
}

VOID
ReleasePspSmiRegMutex (
  VOID
  )
{
  EFI_STATUS Status;

  Status = GetPspServicePointer ();

  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return;
  }

  mPspServicePtr->ReleasePspSmiRegMutex ();
}

