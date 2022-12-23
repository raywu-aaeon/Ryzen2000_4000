/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD FCH SMM Diag sDispatcher Driver
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
#define FILECODE UEFIUDK_FCH_FCHKERNMODULEPKG_FCHSMMDISPATCHER_FCHSMMDIAGDISPATCHER_FILECODE
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmConfiguration.h>
#include <Protocol/SmmCpuIo2.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/SmmCpu.h>

#include "FchPlatform.h"
extern EFI_GUID gFchSmmDiagDispatchProtocolGuid;
#define DIAG_ENABLE 0x1
#define DIAG_DISABLE 0x2

UINT8 DiagEnable;

typedef struct {
  EFI_GUID  *Guid;
  VOID      *Interface;
} FCH_PROTOCOL_LIST;

FCH_PROTOCOL_LIST FchProtocolDiagList[] = {
                    &gFchSmmDiagDispatchProtocolGuid,            NULL,
                    };

EFI_STATUS
EFIAPI
FchSmmDiagDispatchHandler (
  IN       EFI_HANDLE                   SmmImageHandle,
  IN       CONST EFI_SMM_ENTRY_CONTEXT  *SmmEntryContext,
  IN OUT   VOID                         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN                        *SourceSize OPTIONAL
  );

VOID
FchSmmDiagIoRead (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT16                      Address,
     OUT   VOID                        *Value
  );
VOID
FchSmmDiagIoWrite (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT64                      Address,
  IN       VOID                        *Value
  );
/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD FCH SMM dispatcher driver
 * Example of dispatcher driver that handled IO TRAP requests only
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
FchSmmDiagDispatcherEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    DispatchHandle;
  EFI_HANDLE                    FchSmmDiagDispatcherHandle;
  UINTN                         i;

  Status = gSmst->SmiHandlerRegister (
                    FchSmmDiagDispatchHandler,
                    NULL,
                    &DispatchHandle
                    );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (i = 0 ; i < sizeof (FchProtocolDiagList) / sizeof (FCH_PROTOCOL_LIST); i++ ) {
    FchSmmDiagDispatcherHandle =  NULL;
    Status = gSmst->SmmInstallProtocolInterface (
               &FchSmmDiagDispatcherHandle,
               FchProtocolDiagList[i].Guid,
               EFI_NATIVE_INTERFACE,
               FchProtocolDiagList[i].Interface);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return Status;
}

VOID
FchSmmDiagIoRead (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT16                      Address,
     OUT   VOID                        *Value
  )
{
  SmmIo->Io.Read (
                   SmmIo,
                   AccessWidth,
                   Address,
                   1,
                   Value
                   );
}
VOID
FchSmmDiagIoWrite (
  IN       EFI_SMM_CPU_IO2_PROTOCOL    *SmmIo,
  IN       EFI_SMM_IO_WIDTH            AccessWidth,
  IN       UINT64                      Address,
  IN       VOID                        *Value
  )
{
  SmmIo->Io.Write (
              SmmIo,
              AccessWidth,
              Address,
              1,
              Value
              );
}

/*----------------------------------------------------------------------------------------*/
/**
 * FCH SMM dispatcher handler
 *
 *
 * @param[in]       SmmImageHandle        Image Handle
 * @param[in]       SmmEntryContext         (see PI 1.2 for more details)
 * @param[in, out]   OPTIONAL CommunicationBuffer   Communication Buffer (see PI 1.1 for more details)
 * @param[in, out]   OPTIONAL SourceSize            Buffer size (see PI 1.1 for more details)

 * @retval          EFI_SUCCESS           SMI handled by dispatcher
 * @retval          EFI_UNSUPPORTED       SMI not supported by dispcther
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
EFIAPI
FchSmmDiagDispatchHandler (
  IN       EFI_HANDLE                   SmmImageHandle,
  IN       CONST EFI_SMM_ENTRY_CONTEXT  *SmmEntryContext,
  IN OUT   VOID                         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN                        *SourceSize OPTIONAL
  )
{
  EFI_STATUS   Status;
  UINT8        SwSmiCmdAddress;
  UINT8        SwSmiValue;
  UINT8        Index;

  SwSmiCmdAddress = ACPIMMIO8 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A);
  FchSmmDiagIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, 0x80, &SwSmiCmdAddress);
  FchSmmDiagIoRead (&gSmst->SmmIo, SMM_IO_UINT8, SwSmiCmdAddress, &SwSmiValue);
  if (SwSmiValue == DIAG_ENABLE) {
    DiagEnable = 1;
    ACPIMMIO8 (0xfed80304) |= 0x01;
    FchSmmDiagIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, 0x80, &DiagEnable );
  } else if (SwSmiValue == DIAG_DISABLE ) {
    DiagEnable = 0;
    FchSmmDiagIoWrite (&gSmst->SmmIo, SMM_IO_UINT16, 0x80, &DiagEnable );
  }


  if (DiagEnable == 1) {
    for ( Index = 0; Index < 20; Index++ ) {
      ACPIMMIO8 (0xfed10020 + Index) = ACPIMMIO8 (0xfed80280 + Index);
    }
    ACPIMMIO8 (0xfed10040) = SwSmiValue;

    for ( Index = 0; Index < 20; Index++ ) {
      ACPIMMIO8 (0xfed80280 + Index) |= 0;
    }
    }
  Status = EFI_SUCCESS;
  return  Status;
}






