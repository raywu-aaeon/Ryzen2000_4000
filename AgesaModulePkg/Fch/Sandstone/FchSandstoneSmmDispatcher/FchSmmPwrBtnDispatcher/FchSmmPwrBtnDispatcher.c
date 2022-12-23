/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 POWER BUTTON Dispatcher Driver
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

#include "FchSmmPwrBtnDispatcher.h"
#include "Filecode.h"
#define FILECODE UEFI_SMM_FCHSMMDISPATCHER_FCHSMMPWRBTNDISPATCHER_FCHSMMPWRBTNDISPATCHER_FILECODE

EFI_STATUS
EFIAPI
FchSmmPwrBtnDispatch2Register (
  IN       CONST FCH_SMM_PWRBTN_DISPATCH2_PROTOCOL  *This,
  IN       FCH_SMM_PWRBTN_HANDLER_ENTRY_POINT2      CallBackFunction,
  IN       FCH_SMM_PWRBTN_REGISTER_CONTEXT          *RegisterContext,
     OUT   EFI_HANDLE                               *DispatchHandle
  );

EFI_STATUS
EFIAPI
FchSmmPwrBtnDispatch2UnRegister (
  IN       CONST FCH_SMM_PWRBTN_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                               DispatchHandle
  );

FCH_SMM_PWRBTN_DISPATCH2_PROTOCOL gFchSmmPwrBtnDispatch2Protocol = {
  FchSmmPwrBtnDispatch2Register,
  FchSmmPwrBtnDispatch2UnRegister
};

/*----------------------------------------------------------------------------------------*/
/**
 * FCH SMM POWER BUTTON dispatcher handler
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
FchSmmPwrBtnDispatchHandler (
  IN       EFI_HANDLE   SmmImageHandle,
  IN OUT   VOID         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN        *SourceSize OPTIONAL
  )
{
  EFI_STATUS  Status;
  FCH_SMM_PWRBTN_NODE *CurrentFchSmmPwrBtnNodePtr;
  Status = EFI_NOT_FOUND;

  if (HeadFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr == NULL) {
    Status = EFI_NOT_FOUND;
  } else {
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG84) = PwrBtn;
    CurrentFchSmmPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    while (CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr!= NULL) {
      if (CurrentFchSmmPwrBtnNodePtr->Context.Phase == EfiPowerButtonEntry) {
        if (CurrentFchSmmPwrBtnNodePtr->CallBack2Function != NULL) {
          Status = CurrentFchSmmPwrBtnNodePtr->CallBack2Function (
                                                 CurrentFchSmmPwrBtnNodePtr->DispatchHandle,
                                                 &CurrentFchSmmPwrBtnNodePtr->Context,
                                                 NULL,
                                                 NULL
                                                 );
          DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] PwrBtn SMM handler dispatched (Phase = Entry) Order = 0x%x, \
                  return - %r\n", CurrentFchSmmPwrBtnNodePtr->Context.Order, Status));
        }
        Status = EFI_SUCCESS;
      }
      CurrentFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
    }

    CurrentFchSmmPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    while (CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr!= NULL) {
      if (CurrentFchSmmPwrBtnNodePtr->Context.Phase == EfiPowerButtonExit) {
        if (CurrentFchSmmPwrBtnNodePtr->CallBack2Function != NULL) {
          Status = CurrentFchSmmPwrBtnNodePtr->CallBack2Function (
                                                 CurrentFchSmmPwrBtnNodePtr->DispatchHandle,
                                                 &CurrentFchSmmPwrBtnNodePtr->Context,
                                                 NULL,
                                                 NULL
                                                 );
          DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] PwrBtn SMM handler dispatched (Phase = Exit) Order = 0x%x, \
                  return - %r\n", CurrentFchSmmPwrBtnNodePtr->Context.Order, Status));
        }
        Status = EFI_SUCCESS;
      }
      CurrentFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
    }
  }
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Register POWER BOTTON child handler
 *
 *
 * @param[in]       This                  Pointer to protocol
 * @param[in]       CallBackFunction
 * @param[in, out]   RegisterContext
 * @param[out]      DispatchHandle        Handle (see PI 1.1 for more details)
 *
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmPwrBtnDispatch2Register (
  IN       CONST FCH_SMM_PWRBTN_DISPATCH2_PROTOCOL  *This,
  IN       FCH_SMM_PWRBTN_HANDLER_ENTRY_POINT2      CallBackFunction,
  IN       FCH_SMM_PWRBTN_REGISTER_CONTEXT          *RegisterContext,
     OUT   EFI_HANDLE                               *DispatchHandle
  )
{
  EFI_STATUS  Status;
  FCH_SMM_PWRBTN_NODE *NewFchSmmPwrBtnNodePtr;
  FCH_SMM_PWRBTN_NODE *CurrentFchSmmPwrBtnNodePtr;
  FCH_SMM_PWRBTN_NODE *PreviousFchSmmPwrBtnNodePtr;
  Status = EFI_OUT_OF_RESOURCES;

  if (CallBackFunction == NULL || RegisterContext == NULL || DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGAC) |= BIT6;
  Status = gSmst->SmmAllocatePool (
                       EfiRuntimeServicesData,
                       sizeof (FCH_SMM_PWRBTN_NODE),
                       &NewFchSmmPwrBtnNodePtr
                       );
  ASSERT_EFI_ERROR (Status);
  NewFchSmmPwrBtnNodePtr->CallBack2Function = CallBackFunction;
  *DispatchHandle = &NewFchSmmPwrBtnNodePtr->DispatchHandle;
  NewFchSmmPwrBtnNodePtr->DispatchHandle = *DispatchHandle;
  NewFchSmmPwrBtnNodePtr->Context = *RegisterContext;

  DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] Registering PwrBtn SMM handler: Phase = 0x%x, Order = 0x%x\n", \
         RegisterContext->Phase, RegisterContext->Order));
  if (HeadFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr == NULL) {
    NewFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    HeadFchSmmPwrBtnNodePtr = NewFchSmmPwrBtnNodePtr;
  } else {
    PreviousFchSmmPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    CurrentFchSmmPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    while (CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr != NULL) {
      if (NewFchSmmPwrBtnNodePtr->Context.Order <= CurrentFchSmmPwrBtnNodePtr->Context.Order) {
        if (PreviousFchSmmPwrBtnNodePtr == CurrentFchSmmPwrBtnNodePtr) {
          NewFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
          HeadFchSmmPwrBtnNodePtr = NewFchSmmPwrBtnNodePtr;
          Status = EFI_SUCCESS;
          return Status;
        }
        NewFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = PreviousFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
        PreviousFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = NewFchSmmPwrBtnNodePtr;

        Status = EFI_SUCCESS;
        return Status;
      }
      PreviousFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr;
      CurrentFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
    }
    PreviousFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = NewFchSmmPwrBtnNodePtr;
    NewFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr;
  }
  Status = EFI_SUCCESS;



  return  Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Unregister POWER BUTTON child handler
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
FchSmmPwrBtnDispatch2UnRegister (
  IN       CONST FCH_SMM_PWRBTN_DISPATCH2_PROTOCOL  *This,
  IN       EFI_HANDLE                               DispatchHandle
  )
{
  EFI_STATUS  Status;
  FCH_SMM_PWRBTN_NODE *CurrentFchSmmPwrBtnNodePtr;
  FCH_SMM_PWRBTN_NODE *PreviousFchSmmPwrBtnNodePtr;

  if (DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (HeadFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr == NULL) {
    Status = EFI_NOT_FOUND;
    return  Status;
  } else {
    PreviousFchSmmPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    CurrentFchSmmPwrBtnNodePtr = HeadFchSmmPwrBtnNodePtr;
    if (CurrentFchSmmPwrBtnNodePtr->DispatchHandle == DispatchHandle) {
      HeadFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
    } else {
      while (CurrentFchSmmPwrBtnNodePtr->DispatchHandle != DispatchHandle) {
        PreviousFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr;
        CurrentFchSmmPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
        if (CurrentFchSmmPwrBtnNodePtr->DispatchHandle == NULL) {
          Status = EFI_NOT_FOUND;
          return  Status;
        }
      }
      PreviousFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr = CurrentFchSmmPwrBtnNodePtr->FchPwrBtnNodePtr;
    }

    Status = gSmst->SmmFreePool (
                         CurrentFchSmmPwrBtnNodePtr
                         );
    ASSERT_EFI_ERROR (Status);
  }
  Status = EFI_SUCCESS;
  return  Status;
}


EFI_STATUS
EFIAPI
EfiSmmPwrBtnDispatch2Register (
  IN       CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *This,
  IN       EFI_SMM_HANDLER_ENTRY_POINT2                  DispatchFunction,
  IN       EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT         *RegisterContext,
     OUT   EFI_HANDLE                                    *DispatchHandle
  )
{
  FCH_SMM_PWRBTN_REGISTER_CONTEXT  FchRegisterContext;

  FchRegisterContext.Phase = RegisterContext->Phase;
  FchRegisterContext.Order = 0x80;      // SMM_DEFAULT_ORDER
  return FchSmmPwrBtnDispatch2Register (
           &gFchSmmPwrBtnDispatch2Protocol,
           DispatchFunction,
           &FchRegisterContext,
           DispatchHandle
           );
}

EFI_STATUS
EFIAPI
EfiSmmPwrBtnDispatch2UnRegister (
  IN       CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                                    DispatchHandle
  )
{
  return FchSmmPwrBtnDispatch2UnRegister (
           &gFchSmmPwrBtnDispatch2Protocol,
           DispatchHandle
           );
}

EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL gEfiSmmPwrBtnDispatch2Protocol = {
  EfiSmmPwrBtnDispatch2Register,
  EfiSmmPwrBtnDispatch2UnRegister
};


