/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 Misc Dispatcher Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
 *
 */
/******************************************************************************
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

#include "FchSmmMiscDispatcher.h"
#include "Filecode.h"
#define FILECODE UEFI_SMM_FCHSMMDISPATCHER_FCHSMMMISCDISPATCHER_FCHSMMMISCDISPATCHER_FILECODE

EFI_STATUS
EFIAPI
FchSmmMiscDispatchRegister (
  IN       CONST FCH_SMM_MISC_DISPATCH_PROTOCOL   *This,
  IN       FCH_SMM_MISC_HANDLER_ENTRY_POINT       CallBackFunction,
  IN OUT   FCH_SMM_MISC_REGISTER_CONTEXT          *MiscRegisterContext,
     OUT   EFI_HANDLE                             *DispatchHandle
  );

EFI_STATUS
EFIAPI
FchSmmMiscDispatchUnRegister (
  IN       CONST FCH_SMM_MISC_DISPATCH_PROTOCOL   *This,
  IN       EFI_HANDLE                             DispatchHandle
  );

EFI_STATUS
EFIAPI
FchSmmMiscSmiEnable (
  IN OUT   FCH_SMM_MISC_REGISTER_CONTEXT          *MiscRegisterContext
  );

FCH_SMM_MISC_DISPATCH_PROTOCOL gFchSmmMiscDispatchProtocol = {
  FchSmmMiscDispatchRegister,
  FchSmmMiscDispatchUnRegister
};

/*----------------------------------------------------------------------------------------*/
/**
 * FCH SMM Misc dispatcher handler
 *
 *
 * @param[in]       SmmImageHandle        Image Handle
 * @param[in, out]   OPTIONAL CommunicationBuffer   Communication Buffer (see PI 1.1 for more details)
 * @param[in, out]   OPTIONAL SourceSize            Buffer size (see PI 1.1 for more details)

 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmMiscDispatchHandler (
  IN       EFI_HANDLE   SmmImageHandle,
  IN OUT   VOID         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN        *SourceSize OPTIONAL
  )
{
  EFI_STATUS  Status;
  FCH_SMM_MISC_NODE                   *CurrentFchSmmMiscNodePtr;
  FCH_SMM_COMMUNICATION_BUFFER        *CommunicationBufferPtr;
  UINT16 MiscSmiDispatched;
  MiscSmiDispatched = 0;
  Status = EFI_NOT_FOUND;
  CommunicationBufferPtr = (FCH_SMM_COMMUNICATION_BUFFER *)CommunicationBuffer;

  if (HeadFchSmmMiscNodePtr->FchMiscNodePtr == NULL) {
    Status = EFI_NOT_FOUND;
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + CommunicationBufferPtr->SmiStatusReg) = CommunicationBufferPtr->SmiStatusBit;
  } else {
    CurrentFchSmmMiscNodePtr = HeadFchSmmMiscNodePtr;
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + CommunicationBufferPtr->SmiStatusReg) = CommunicationBufferPtr->SmiStatusBit;
    while (CurrentFchSmmMiscNodePtr->FchMiscNodePtr!= NULL) {
      if (CurrentFchSmmMiscNodePtr->Context.SmiStatusReg == CommunicationBufferPtr->SmiStatusReg &&
          CurrentFchSmmMiscNodePtr->Context.SmiStatusBit == CommunicationBufferPtr->SmiStatusBit) {
        Status = CurrentFchSmmMiscNodePtr->CallBackFunction (
                                            CurrentFchSmmMiscNodePtr->DispatchHandle,
                                            &CurrentFchSmmMiscNodePtr->Context
                                            );
        MiscSmiDispatched++;
      }
      CurrentFchSmmMiscNodePtr = CurrentFchSmmMiscNodePtr->FchMiscNodePtr;
    }
    if (MiscSmiDispatched <= 0) {
      Status = EFI_NOT_FOUND;
    } else {
      Status = EFI_SUCCESS;
    }
  }
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Register MISC child handler
 *
 *
 * @param[in]       This                  Pointer to protocol
 * @param[in]       CallBackFunction
 * @param[in, out]   MiscRegisterContext
 * @param[out]      DispatchHandle        Handle (see PI 1.1 for more details)
 *
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmMiscDispatchRegister (
  IN       CONST FCH_SMM_MISC_DISPATCH_PROTOCOL   *This,
  IN       FCH_SMM_MISC_HANDLER_ENTRY_POINT       CallBackFunction,
  IN OUT   FCH_SMM_MISC_REGISTER_CONTEXT          *MiscRegisterContext,
     OUT   EFI_HANDLE                             *DispatchHandle
  )
{
  EFI_STATUS            Status;
  FCH_SMM_MISC_NODE     *NewFchSmmMiscNodePtr;
  FCH_SMM_MISC_NODE     *CurrentFchSmmMiscNodePtr;
  FCH_SMM_MISC_NODE     *PreviousFchSmmMiscNodePtr;

  Status = EFI_OUT_OF_RESOURCES;
  if (CallBackFunction == NULL || MiscRegisterContext == NULL || DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = gSmst->SmmAllocatePool (
                       EfiRuntimeServicesData,
                       sizeof (FCH_SMM_MISC_NODE),
                       &NewFchSmmMiscNodePtr
                       );
  ASSERT_EFI_ERROR (Status);

  NewFchSmmMiscNodePtr->CallBackFunction = CallBackFunction;
  *DispatchHandle = &NewFchSmmMiscNodePtr->DispatchHandle;
  NewFchSmmMiscNodePtr->DispatchHandle   = *DispatchHandle;
  NewFchSmmMiscNodePtr->Context          = *MiscRegisterContext;
  NewFchSmmMiscNodePtr->FchMiscNodePtr = HeadFchSmmMiscNodePtr;

  Status = FchSmmMiscSmiEnable (MiscRegisterContext);

  if (HeadFchSmmMiscNodePtr->FchMiscNodePtr == NULL) {
    NewFchSmmMiscNodePtr->FchMiscNodePtr = HeadFchSmmMiscNodePtr;
    HeadFchSmmMiscNodePtr = NewFchSmmMiscNodePtr;
  } else {
    PreviousFchSmmMiscNodePtr = HeadFchSmmMiscNodePtr;
    CurrentFchSmmMiscNodePtr = HeadFchSmmMiscNodePtr;
    while (CurrentFchSmmMiscNodePtr->FchMiscNodePtr != NULL) {
      if (NewFchSmmMiscNodePtr->Context.Order <= CurrentFchSmmMiscNodePtr->Context.Order &&
          CurrentFchSmmMiscNodePtr->Context.SmiStatusReg == NewFchSmmMiscNodePtr->Context.SmiStatusReg &&
          CurrentFchSmmMiscNodePtr->Context.SmiStatusBit == NewFchSmmMiscNodePtr->Context.SmiStatusBit) {
        if (PreviousFchSmmMiscNodePtr == CurrentFchSmmMiscNodePtr) {
          NewFchSmmMiscNodePtr->FchMiscNodePtr = HeadFchSmmMiscNodePtr;
          HeadFchSmmMiscNodePtr = NewFchSmmMiscNodePtr;
          Status = EFI_SUCCESS;
          return  Status;
        }
        NewFchSmmMiscNodePtr->FchMiscNodePtr = PreviousFchSmmMiscNodePtr->FchMiscNodePtr;
        PreviousFchSmmMiscNodePtr->FchMiscNodePtr = NewFchSmmMiscNodePtr;

        Status = EFI_SUCCESS;
        return  Status;
      }
      PreviousFchSmmMiscNodePtr = CurrentFchSmmMiscNodePtr;
      CurrentFchSmmMiscNodePtr = CurrentFchSmmMiscNodePtr->FchMiscNodePtr;
    }
    PreviousFchSmmMiscNodePtr->FchMiscNodePtr = NewFchSmmMiscNodePtr;
    NewFchSmmMiscNodePtr->FchMiscNodePtr = CurrentFchSmmMiscNodePtr;
  }
  Status = EFI_SUCCESS;
  return  Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Unregister MISC child handler
 *
 *
 * @param[in]       This                  Pointer to protocol
 * @param[in]       DispatchHandle
 *
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmMiscDispatchUnRegister (
  IN       CONST FCH_SMM_MISC_DISPATCH_PROTOCOL   *This,
  IN       EFI_HANDLE                             DispatchHandle
  )
{
  EFI_STATUS        Status;
  FCH_SMM_MISC_NODE *CurrentFchSmmMiscNodePtr;
  FCH_SMM_MISC_NODE *PreviousFchSmmMiscNodePtr;

  if (DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (HeadFchSmmMiscNodePtr->FchMiscNodePtr == NULL) {
    Status = EFI_NOT_FOUND;
    return  Status;
  } else {
    PreviousFchSmmMiscNodePtr = HeadFchSmmMiscNodePtr;
    CurrentFchSmmMiscNodePtr = HeadFchSmmMiscNodePtr;
    if (CurrentFchSmmMiscNodePtr->DispatchHandle == DispatchHandle) {
      HeadFchSmmMiscNodePtr = CurrentFchSmmMiscNodePtr->FchMiscNodePtr;
    } else {
      while (CurrentFchSmmMiscNodePtr->DispatchHandle != DispatchHandle) {
        PreviousFchSmmMiscNodePtr = CurrentFchSmmMiscNodePtr;
        CurrentFchSmmMiscNodePtr = CurrentFchSmmMiscNodePtr->FchMiscNodePtr;
        if (CurrentFchSmmMiscNodePtr->DispatchHandle == NULL) {
          Status = EFI_NOT_FOUND;
          return  Status;
        }
      }
      PreviousFchSmmMiscNodePtr->FchMiscNodePtr = CurrentFchSmmMiscNodePtr->FchMiscNodePtr;
    }
    Status = gSmst->SmmFreePool (
                       CurrentFchSmmMiscNodePtr
                       );
    ASSERT_EFI_ERROR (Status);
  }
  Status = EFI_SUCCESS;
  return  Status;
}


EFI_STATUS
EFIAPI
FchSmmMiscSmiEnable (
  IN OUT   FCH_SMM_MISC_REGISTER_CONTEXT          *MiscRegisterContext
  )
{
  UINT32    SmiEvent;
  UINT32    SmiStatusBit;
  UINT32    SmiControlReg;
  UINT32    SmiControlBit;
  UINT32    OrMask;
  UINT32    AndMask;

  SmiEvent = 0;
  SmiStatusBit = MiscRegisterContext->SmiStatusBit;
  while ((SmiStatusBit & BIT0) == 0) {
    SmiEvent++;
    SmiStatusBit = SmiStatusBit >> 1;
  }
  SmiEvent += (MiscRegisterContext->SmiStatusReg - FCH_SMI_REG80) * 8;

  SmiControlReg = FCH_SMI_REGA0 + (SmiEvent * 2 / 32) * 4;
  SmiControlBit = 1 << ((SmiEvent *2 ) % 32);

  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + MiscRegisterContext->SmiStatusReg) =  MiscRegisterContext->SmiStatusBit;

  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + SmiControlReg) &= ~(UINT32) (SmiControlBit + SmiControlBit * 2);
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + SmiControlReg) |= SmiControlBit;
  // Save in BootScriptTable for S3
  OrMask = SmiControlBit;
  AndMask = 0xFFFFFFFFul;
  S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + SmiControlReg), &OrMask, &AndMask);
  return EFI_SUCCESS;
}

