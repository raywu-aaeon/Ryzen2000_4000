/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 SMI Dispatcher Driver Example
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


#include "FchSmmIoTrapDispatcher.h"
#include "Filecode.h"
#define FILECODE UEFI_SMM_FCHSMMDISPATCHER_FCHSMMIOTRAPDISPATCHER_FCHSMMIOTRAPDISPATCHER_FILECODE

EFI_STATUS
EFIAPI
FchSmmIoTrapDispatch2Register (
  IN       CONST FCH_SMM_IO_TRAP_DISPATCH2_PROTOCOL  *This,
  IN       FCH_SMM_IO_TRAP_HANDLER_ENTRY_POINT2      DispatchFunction,
  IN OUT   FCH_SMM_IO_TRAP_REGISTER_CONTEXT          *RegisterContext,
     OUT   EFI_HANDLE                                *DispatchHandle
  );

EFI_STATUS
EFIAPI
FchSmmIoTrapDispatch2UnRegister (
  IN       CONST FCH_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                               DispatchHandle
  );

FCH_SMM_IO_TRAP_DISPATCH2_PROTOCOL gFchSmmIoTrapDispatch2Protocol = {
  FchSmmIoTrapDispatch2Register,
  FchSmmIoTrapDispatch2UnRegister
};

FCH_IO_TRAP_ENTRY  mFchIoTrapList[] = {
  { BIT20, 0,  0xC0, 0xF0, 0, 0, 0},
  { BIT21, 1,  0xC2, 0xF0, 0, 0, 0},
  { BIT22, 2,  0xC4, 0xF0, 0, 0, 0},
  { BIT23, 3,  0xC8, 0xF0, 0, 0, 0},
};

UINTN mFchIoTrapIndex = 0;

/*----------------------------------------------------------------------------------------*/
/**
 * FCH SMM IO TRAP dispatcher handler
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
FchSmmIoTrapDispatchHandler (
  IN       EFI_HANDLE   SmmImageHandle,
  IN OUT   VOID         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN        *SourceSize OPTIONAL
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINT32      SmiIoTrapStatusBitmap;
  Status = EFI_UNSUPPORTED;

  SmiIoTrapStatusBitmap = ACPIMMIO32 (ACPI_MMIO_BASE + 0x290);
  SmiIoTrapStatusBitmap &= BIT20 + BIT21 + BIT22 + BIT23;
  if (SmiIoTrapStatusBitmap != 0) {
    for (Index = 0; Index < (sizeof (mFchIoTrapList) / sizeof (FCH_IO_TRAP_ENTRY)); Index++) {
      if ((mFchIoTrapList[Index].StatusMask & SmiIoTrapStatusBitmap) != 0) {
        ACPIMMIO32 (ACPI_MMIO_BASE + 0x290) = mFchIoTrapList[Index].StatusMask;
        if (mFchIoTrapList[Index].DispatchFunction) {
          Status = mFchIoTrapList[Index].DispatchFunction (
                     mFchIoTrapList[Index].DispatchHandle,
                     &mFchIoTrapList[Index].Context,
                     NULL,
                     NULL
                     );
          DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] IoTrap SMM handler dispatched: Address = 0x%04lx, return - %r\n", \
                 mFchIoTrapList[Index].Context.Address, Status));
        }
        break;
      }
    }
  }
  return  Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Register IO TRAP child handler
 *
 *
 * @param[in]       This                  Pointer to protocol
 * @param[in]       DispatchFunction      Child dispcther function
 * @param[in, out]   RegisterContext            Register contecxt (see PI 1.1 for more details)
 * @param[out]      DispatchHandle        Handle (see PI 1.1 for more details)
 *
 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmIoTrapDispatch2Register (
  IN       CONST FCH_SMM_IO_TRAP_DISPATCH2_PROTOCOL  *This,
  IN       FCH_SMM_IO_TRAP_HANDLER_ENTRY_POINT2      DispatchFunction,
  IN OUT   FCH_SMM_IO_TRAP_REGISTER_CONTEXT          *RegisterContext,
     OUT   EFI_HANDLE                                *DispatchHandle
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINT32      OrMask;
  UINT32      AndMask;
  Status = EFI_OUT_OF_RESOURCES;

  ASSERT ((DispatchFunction != NULL) && (DispatchHandle != NULL));

  if (mFchIoTrapIndex == ((sizeof (mFchIoTrapList) / sizeof (FCH_IO_TRAP_ENTRY)))) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (DispatchFunction == NULL || RegisterContext == NULL || DispatchHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  for (Index = 0; Index < (sizeof (mFchIoTrapList) / sizeof (FCH_IO_TRAP_ENTRY)); Index++) {
    if ((mFchIoTrapList[Index].DispatchFunction == NULL) && (Index == mFchIoTrapIndex))  {
      CopyMem (
        &mFchIoTrapList[Index].Context,
        RegisterContext,
        sizeof (FCH_SMM_IO_TRAP_REGISTER_CONTEXT)
        );
      mFchIoTrapList[Index].DispatchFunction = DispatchFunction;
      *DispatchHandle = &mFchIoTrapList[Index];
      mFchIoTrapIndex ++; 
      //Clear Status
      ACPIMMIO32 (ACPI_MMIO_BASE + 0x290) = mFchIoTrapList[Index].StatusMask;
      //Set base address
      ACPIMMIO16 (ACPI_MMIO_BASE + 0xEC0 + Index * 2) = RegisterContext->Address;
      //Set Read Write Attribute
      ACPIMMIO32 (ACPI_MMIO_BASE + 0xECC ) &= ~ (1 << Index );
      if (RegisterContext->Type == WriteTrap) {
        ACPIMMIO32 (ACPI_MMIO_BASE + 0xECC ) |= (1 << Index );
      }
      // Enable SMI
      ACPIMMIO32 (ACPI_MMIO_BASE + 0x2C4) |= 1 << ((Index * 2) + 8);
      // Save in BootScriptTable for S3
      OrMask = 1 << ((Index * 2) + 8);
      AndMask = ~ (UINT32) (3 << ((Index * 2) + 8));
      S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGC4), &OrMask, &AndMask);

      DEBUG ((DEBUG_INFO, "[FchSmmDispatcher] Registering IoTrap SMM handler: Address = 0x%04lx, Type = 0x%x\n", \
             RegisterContext->Address, RegisterContext->Type));
      Status = EFI_SUCCESS;
      break;
    }
  }
  return  Status;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Unregister IO TRAP child handler
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
FchSmmIoTrapDispatch2UnRegister (
  IN       CONST FCH_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                               DispatchHandle
  )
{
  EFI_STATUS  Status;
  UINTN       Index;
  UINT32      OrMask;
  UINT32      AndMask;
  Status = EFI_NOT_FOUND;
  for (Index = 0; Index < (sizeof (mFchIoTrapList) / sizeof (FCH_IO_TRAP_ENTRY)); Index++) {
    if ( &mFchIoTrapList[Index] == DispatchHandle) {
      mFchIoTrapList[Index].DispatchFunction = NULL;
      //Clear Status ACTION. Is it safe? wll EOS be taken care?
      ACPIMMIO32 (ACPI_MMIO_BASE + 0x290) = mFchIoTrapList[Index].StatusMask;
      // Disable SMI
      ACPIMMIO32 (ACPI_MMIO_BASE + 0x2C4) &= (~(3 << ((1 << Index) + 8)));
      // Save in BootScriptTable for S3
      OrMask = 0;
      AndMask = ~ (UINT32) (3 << ((Index * 2) + 8));
      S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGC4), &OrMask, &AndMask);
      Status = EFI_SUCCESS;
    }
  }
  return  Status;
}


EFI_STATUS
EFIAPI
EfiSmmIoTrapDispatch2Register (
  IN       CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
  IN       EFI_SMM_HANDLER_ENTRY_POINT2             DispatchFunction,
  IN OUT   EFI_SMM_IO_TRAP_REGISTER_CONTEXT         *RegisterContext,
     OUT   EFI_HANDLE                               *DispatchHandle
  )
{
  FCH_SMM_IO_TRAP_REGISTER_CONTEXT  FchRegisterContext;

  FchRegisterContext.Address = RegisterContext->Address;
  FchRegisterContext.Length  = RegisterContext->Length;
  FchRegisterContext.Type    = RegisterContext->Type;
  return FchSmmIoTrapDispatch2Register (
           &gFchSmmIoTrapDispatch2Protocol,
           DispatchFunction,
           &FchRegisterContext,
           DispatchHandle
           );
}

EFI_STATUS
EFIAPI
EfiSmmIoTrapDispatch2UnRegister (
  IN       CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
  IN       EFI_HANDLE                               DispatchHandle
  )
{
  return FchSmmIoTrapDispatch2UnRegister (
           &gFchSmmIoTrapDispatch2Protocol,
           DispatchHandle
           );
}

EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL gEfiSmmIoTrapDispatch2Protocol = {
  EfiSmmIoTrapDispatch2Register,
  EfiSmmIoTrapDispatch2UnRegister
};


