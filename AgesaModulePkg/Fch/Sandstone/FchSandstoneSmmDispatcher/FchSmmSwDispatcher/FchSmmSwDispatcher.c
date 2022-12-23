/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 Child SMI Dispatcher Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 311751 $   @e \$Date: 2015-01-26 13:34:23 -0800 (Mon, 26 Jan 2015) $
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

#include "FchSmmSwDispatcher.h"
#include "Filecode.h"
#define FILECODE UEFI_SMM_FCHSMMDISPATCHER_FCHSMMSWDISPATCHER_FCHSMMSWDISPATCHER_FILECODE


EFI_STATUS
EFIAPI
FchSmmSwDispatch2Register (
  IN       CONST FCH_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN       FCH_SMM_SW_HANDLER_ENTRY_POINT2      DispatchFunction,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT    *RegisterContext,
     OUT   EFI_HANDLE                           *DispatchHandle
  );

EFI_STATUS
EFIAPI
FchSmmSwDispatch2UnRegister (
  IN       CONST FCH_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                           DispatchHandle
  );

FCH_SMM_SW_DISPATCH2_PROTOCOL gFchSmmSwDispatch2Protocol = {
  FchSmmSwDispatch2Register,
  FchSmmSwDispatch2UnRegister,
  (UINTN) MAX_SW_SMI_VALUE
};

BOOLEAN
STATIC
IsSwSmiValueUsed (
  IN UINTN Value
  );

/*----------------------------------------------------------------------------------------*/
/**
 * FCH SMM SW dispatcher handler
 *
 *
 * @param[in]       SmmImageHandle        Image Handle
 * @param[in, out]   OPTIONAL CommunicationBuffer   Communication Buffer (see PI 1.2 for more details)
 * @param[in, out]   OPTIONAL SourceSize            Buffer size (see PI 1.2 for more details)

 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmSwDispatchHandler (
  IN       EFI_HANDLE   SmmImageHandle,
  IN OUT   VOID         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN        *SourceSize OPTIONAL
  )
{
  EFI_STATUS                  Status;
  FCH_SMM_SW_NODE             *CurrentFchSmmSwNodePtr;
  UINT16                      SwSmiValue;
  UINT8                       SwSmiCmdAddress;
  UINT16                      SwSmiDispatched;
  UINTN                       SizeOfFchSmmSwContext;
  UINT8                       i;
  EFI_SMM_SAVE_STATE_IO_INFO  IoInfo;

  Status = EFI_NOT_FOUND;
  SwSmiDispatched = 0;

  SwSmiCmdAddress = ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A);
  LibFchSmmIoRead (&gSmst->SmmIo, SMM_IO_UINT16, SwSmiCmdAddress, &SwSmiValue);

  ASSERT (mSmmCpuProtocol != NULL);
  i = (UINT8) gSmst->NumberOfCpus;
  do {
    EfiSmmSwContext->SwSmiCpuIndex = i - 1;
    Status = mSmmCpuProtocol->ReadSaveState (
                                mSmmCpuProtocol,
                                sizeof (EFI_SMM_SAVE_STATE_IO_INFO),
                                EFI_SMM_SAVE_STATE_REGISTER_IO,
                                EfiSmmSwContext->SwSmiCpuIndex,
                                &IoInfo
                                );
    if ((Status == EFI_SUCCESS) && (IoInfo.IoPort == SwSmiCmdAddress) && ((UINT8) IoInfo.IoData == (UINT8) SwSmiValue)) {
      break;
    }
  } while (--i);
  EfiSmmSwContext->CommandPort = (UINT8) SwSmiValue;
  EfiSmmSwContext->DataPort = (UINT8) (SwSmiValue >> 8);

  if (HeadFchSmmSwNodePtr->FchSwNodePtr == NULL) {
    Status = EFI_NOT_FOUND;
  } else {
    CurrentFchSmmSwNodePtr = HeadFchSmmSwNodePtr;
    while (CurrentFchSmmSwNodePtr->FchSwNodePtr!= NULL) {
      if ((UINT8) CurrentFchSmmSwNodePtr->Context.AmdSwValue == (UINT8) SwSmiValue) {
        if (CurrentFchSmmSwNodePtr->CallBack2Function != NULL) {
          SizeOfFchSmmSwContext = (UINTN) sizeof (FCH_SMM_SW_CONTEXT);
          Status = CurrentFchSmmSwNodePtr->CallBack2Function (
                                          CurrentFchSmmSwNodePtr->DispatchHandle,
                                          &CurrentFchSmmSwNodePtr->Context,
                                          EfiSmmSwContext,
                                          &SizeOfFchSmmSwContext
                                          );
          DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] SW SMM handler dispatched: SwValue = 0x%x, Order = 0x%x, return - %r\n", \
                 CurrentFchSmmSwNodePtr->Context.AmdSwValue, CurrentFchSmmSwNodePtr->Context.Order, Status));
        }

        SwSmiDispatched++;
      }
      CurrentFchSmmSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
    }
    if (SwSmiDispatched <= 0) {
      Status = EFI_NOT_FOUND;
    } else {
      ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG88) = SmiCmdPort;
      Status = EFI_SUCCESS;
    }
  }
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG88) = SmiCmdPort;
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Register SW child handler
 *
 *
 * @param[in]       This                  Pointer to protocol
 * @param[in]       DispatchFunction      Callback Function
 * @param[in, out]  RegisterContext       Register contecxt (see PI 1.1 for more details)
 * @param[out]      DispatchHandle        Handle (see PI 1.1 for more details)
 *
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmSwDispatch2Register (
  IN       CONST FCH_SMM_SW_DISPATCH2_PROTOCOL *This,
  IN       FCH_SMM_SW_HANDLER_ENTRY_POINT2     DispatchFunction,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT   *RegisterContext,
     OUT   EFI_HANDLE                          *DispatchHandle
  )
{
  EFI_STATUS      Status;
  FCH_SMM_SW_NODE *NewFchSmmSwNodePtr;
  FCH_SMM_SW_NODE *CurrentFchSmmSwNodePtr;
  FCH_SMM_SW_NODE *PreviousFchSmmSwNodePtr;
  UINT32          OrMask;
  UINT32          AndMask;

  Status = EFI_OUT_OF_RESOURCES;

  if (DispatchFunction == NULL || RegisterContext == NULL || DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGB0) |= BIT22;
  // Save in BootScriptTable for S3
  OrMask = BIT22;
  AndMask = 0xFFFFFFFFul;
  S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGB0), &OrMask, &AndMask);

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_SW_NODE),
                    &NewFchSmmSwNodePtr
                    );
  ASSERT_EFI_ERROR (Status);

  NewFchSmmSwNodePtr->CallBack2Function = DispatchFunction;
  NewFchSmmSwNodePtr->Context = *RegisterContext;
  *DispatchHandle = &NewFchSmmSwNodePtr->DispatchHandle;
  NewFchSmmSwNodePtr->DispatchHandle = *DispatchHandle;

  DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] Registering SW SMM handler: SwValue = 0x%x, Order = 0x%x\n", RegisterContext->AmdSwValue, RegisterContext->Order));
  if (HeadFchSmmSwNodePtr->FchSwNodePtr == NULL) {
    NewFchSmmSwNodePtr->FchSwNodePtr = HeadFchSmmSwNodePtr;
    HeadFchSmmSwNodePtr = NewFchSmmSwNodePtr;
  } else {
    PreviousFchSmmSwNodePtr = HeadFchSmmSwNodePtr;
    CurrentFchSmmSwNodePtr = HeadFchSmmSwNodePtr;
    while (CurrentFchSmmSwNodePtr->FchSwNodePtr != NULL) {
      if (NewFchSmmSwNodePtr->Context.Order <= CurrentFchSmmSwNodePtr->Context.Order &&
          CurrentFchSmmSwNodePtr->Context.AmdSwValue == NewFchSmmSwNodePtr->Context.AmdSwValue) {

        if (PreviousFchSmmSwNodePtr == CurrentFchSmmSwNodePtr) {
          NewFchSmmSwNodePtr->FchSwNodePtr = HeadFchSmmSwNodePtr;
          HeadFchSmmSwNodePtr = NewFchSmmSwNodePtr;
          Status = EFI_SUCCESS;
          return Status;
        }
        NewFchSmmSwNodePtr->FchSwNodePtr = PreviousFchSmmSwNodePtr->FchSwNodePtr;
        PreviousFchSmmSwNodePtr->FchSwNodePtr = NewFchSmmSwNodePtr;

        Status = EFI_SUCCESS;
        return  Status;
      }
      PreviousFchSmmSwNodePtr = CurrentFchSmmSwNodePtr;
      CurrentFchSmmSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
    }
    PreviousFchSmmSwNodePtr->FchSwNodePtr = NewFchSmmSwNodePtr;
    NewFchSmmSwNodePtr->FchSwNodePtr = CurrentFchSmmSwNodePtr;
  }
  Status = EFI_SUCCESS;
  return  Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Unregister SW child handler
 *
 *
 * @param[in]       This                  Pointer to protocol
 * @param[in]       DispatchHandle        Dispatch Handle
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmSwDispatch2UnRegister (
  IN       CONST FCH_SMM_SW_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                          DispatchHandle
  )
{
  EFI_STATUS      Status;
  FCH_SMM_SW_NODE *CurrentFchSmmSwNodePtr;
  FCH_SMM_SW_NODE *PreviousFchSmmSwNodePtr;

  if (DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  if (HeadFchSmmSwNodePtr->FchSwNodePtr == NULL) {
    Status = EFI_NOT_FOUND;
    return  Status;
  } else {
    PreviousFchSmmSwNodePtr = HeadFchSmmSwNodePtr;
    CurrentFchSmmSwNodePtr = HeadFchSmmSwNodePtr;
    if (CurrentFchSmmSwNodePtr->DispatchHandle == DispatchHandle) {
      HeadFchSmmSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
    } else {
      while (CurrentFchSmmSwNodePtr->DispatchHandle != DispatchHandle) {
        PreviousFchSmmSwNodePtr = CurrentFchSmmSwNodePtr;
        CurrentFchSmmSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
        if (CurrentFchSmmSwNodePtr->DispatchHandle == NULL) {
          Status = EFI_NOT_FOUND;
          return  Status;
        }
      }
      PreviousFchSmmSwNodePtr->FchSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
    }

    Status = gSmst->SmmFreePool (
                      CurrentFchSmmSwNodePtr
                      );
    ASSERT_EFI_ERROR (Status);
  }
  Status = EFI_SUCCESS;
  return  Status;
}

BOOLEAN
STATIC
IsSwSmiValueUsed (
  IN UINTN Value
  )
{
  BOOLEAN           Result;
  FCH_SMM_SW_NODE   *CurrentFchSmmSwNodePtr;

  Result = FALSE;
  CurrentFchSmmSwNodePtr = HeadFchSmmSwNodePtr;
  while ((CurrentFchSmmSwNodePtr->FchSwNodePtr != NULL) && !Result) {
    Result = (CurrentFchSmmSwNodePtr->Context.AmdSwValue == Value);
    CurrentFchSmmSwNodePtr = CurrentFchSmmSwNodePtr->FchSwNodePtr;
  }
  return Result;
}

EFI_STATUS
EFIAPI
EfiSmmSwDispatch2Register (
  IN       CONST EFI_SMM_SW_DISPATCH2_PROTOCOL   *This,
  IN       EFI_SMM_HANDLER_ENTRY_POINT2          DispatchFunction,
  IN OUT   EFI_SMM_SW_REGISTER_CONTEXT           *RegisterContext,
     OUT   EFI_HANDLE                            *DispatchHandle
  )
{
  FCH_SMM_SW_REGISTER_CONTEXT    FchRegisterContext;
  UINTN                          Index;

  FchRegisterContext.Order = 0x80;               // SMM_DEFAULT_ORDER
  if (RegisterContext->SwSmiInputValue == (UINTN) -1) {
    for (Index = 1u; Index < MAX_SW_SMI_VALUE; Index++) {
      if (!IsSwSmiValueUsed (Index)) {
        FchRegisterContext.AmdSwValue = Index;
        RegisterContext->SwSmiInputValue = Index;
        break;
      }
    }
    if (Index == MAX_SW_SMI_VALUE) {
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    FchRegisterContext.AmdSwValue = RegisterContext->SwSmiInputValue;
  }
  return FchSmmSwDispatch2Register (
           &gFchSmmSwDispatch2Protocol,
           DispatchFunction,
           &FchRegisterContext,
           DispatchHandle
           );
}


EFI_STATUS
EFIAPI
EfiSmmSwDispatch2UnRegister (
  IN       CONST EFI_SMM_SW_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                          DispatchHandle
  )
{
  return FchSmmSwDispatch2UnRegister (
           &gFchSmmSwDispatch2Protocol,
           DispatchHandle
           );
}

EFI_SMM_SW_DISPATCH2_PROTOCOL gEfiSmmSwDispatch2Protocol = {
  EfiSmmSwDispatch2Register,
  EfiSmmSwDispatch2UnRegister,
  (UINTN) MAX_SW_SMI_VALUE
};


