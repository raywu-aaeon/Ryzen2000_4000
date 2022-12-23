/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Hudson-2 SMI Dispatcher Driver
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
#include "FchSmmDispatcher.h"
#define FILECODE UEFI_SMM_FCHSMMDISPATCHER_FCHSMMDISPATCHER_FILECODE

#include <Protocol/SmmBase2.h>
#include <Protocol/SmmConfiguration.h>
#include <Protocol/SmmCpuIo2.h>

extern FCH_SMM_DISPATCHER_TABLE FchSmmDispatcherTable[];
extern UINT8 NumOfDispatcherTableEntry;
extern SAVE_B2B_IO B2bIoList[];
extern UINT8 NumOfB2bIoListEntry;
extern SAVE_PCI SavePciList[];
extern UINT8 NumOfSavePciListEntry;

EFI_SMM_CPU_PROTOCOL         *mSmmCpuProtocol;

FCH_SMM_SW_NODE              *HeadFchSmmSwNodePtr;
FCH_SMM_SX_NODE              *HeadFchSmmSxNodePtr;
FCH_SMM_PWRBTN_NODE          *HeadFchSmmPwrBtnNodePtr;
FCH_SMM_PERIODICAL_NODE      *HeadFchSmmPeriodicalNodePtr;
FCH_SMM_GPI_NODE             *HeadFchSmmGpiNodePtr;
FCH_SMM_USB_NODE             *HeadFchSmmUsbNodePtr;
FCH_SMM_MISC_NODE            *HeadFchSmmMiscNodePtr;
FCH_SMM_COMMUNICATION_BUFFER *CommunicationBufferPtr;
FCH_SMM_SW_CONTEXT           *EfiSmmSwContext;

EFI_SMM_PERIODIC_TIMER_CONTEXT EfiSmmPeriodicTimerContext;

typedef struct {
  EFI_GUID  *Guid;
  VOID      *Interface;
} FCH_PROTOCOL_LIST;

FCH_PROTOCOL_LIST FchProtocolList[] = {
                    &gFchSmmSwDispatch2ProtocolGuid,            &gFchSmmSwDispatch2Protocol,
                    &gEfiSmmSwDispatch2ProtocolGuid,            &gEfiSmmSwDispatch2Protocol,
                    &gFchSmmSxDispatch2ProtocolGuid,            &gFchSmmSxDispatch2Protocol,
                    &gEfiSmmSxDispatch2ProtocolGuid,            &gEfiSmmSxDispatch2Protocol,
                    &gFchSmmPwrBtnDispatch2ProtocolGuid,        &gFchSmmPwrBtnDispatch2Protocol,
                    &gEfiSmmPowerButtonDispatch2ProtocolGuid,   &gEfiSmmPwrBtnDispatch2Protocol,
                    &gFchSmmPeriodicalDispatch2ProtocolGuid,    &gFchSmmPeriodicalDispatch2Protocol,
                    &gEfiSmmPeriodicTimerDispatch2ProtocolGuid, &gEfiSmmPeriodicalDispatch2Protocol,
                    &gFchSmmUsbDispatch2ProtocolGuid,           &gFchSmmUsbDispatch2Protocol,
                    &gEfiSmmUsbDispatch2ProtocolGuid,           &gEfiSmmUsbDispatch2Protocol,
                    &gFchSmmGpiDispatch2ProtocolGuid,           &gFchSmmGpiDispatch2Protocol,
                    &gEfiSmmGpiDispatch2ProtocolGuid,           &gEfiSmmGpiDispatch2Protocol,
                    &gFchSmmIoTrapDispatch2ProtocolGuid,        &gFchSmmIoTrapDispatch2Protocol,
                    &gEfiSmmIoTrapDispatch2ProtocolGuid,        &gEfiSmmIoTrapDispatch2Protocol,
                    &gFchSmmMiscDispatchProtocolGuid,           &gFchSmmMiscDispatchProtocol,
                    };

EFI_STATUS
EFIAPI
FchSmmDispatchHandler (
  IN       EFI_HANDLE                   SmmImageHandle,
  IN       CONST EFI_SMM_ENTRY_CONTEXT  *SmmEntryContext,
  IN OUT   VOID                         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN                        *SourceSize OPTIONAL
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
FchSmmDispatcherEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    DispatchHandle;
  EFI_HANDLE                    FchSmmDispatcherHandle;
  UINTN                         i;

  AGESA_TESTPOINT (TpFchSmmDispatcherEntry, NULL);

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmCpuProtocolGuid,
                    NULL,
                    &mSmmCpuProtocol
                    );
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_SW_NODE),
                    &HeadFchSmmSwNodePtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmSwNodePtr, sizeof (FCH_SMM_SW_NODE));

  Status = gSmst->SmmAllocatePool (
                          EfiRuntimeServicesData,
                          sizeof (FCH_SMM_SX_NODE),
                          &HeadFchSmmSxNodePtr
                          );

  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmSxNodePtr, sizeof (FCH_SMM_SX_NODE));

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_PWRBTN_NODE),
                    &HeadFchSmmPwrBtnNodePtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmPwrBtnNodePtr, sizeof (FCH_SMM_PWRBTN_NODE));

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_PERIODICAL_NODE),
                    &HeadFchSmmPeriodicalNodePtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmPeriodicalNodePtr, sizeof (FCH_SMM_PERIODICAL_NODE));

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_GPI_NODE),
                    &HeadFchSmmGpiNodePtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmGpiNodePtr, sizeof (FCH_SMM_GPI_NODE));
  HeadFchSmmGpiNodePtr->Context.GpiNum = 0xffff;

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_USB_NODE),
                    &HeadFchSmmUsbNodePtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmUsbNodePtr, sizeof (FCH_SMM_USB_NODE));
  HeadFchSmmUsbNodePtr->Context.Order = 0xFF;

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_MISC_NODE),
                    &HeadFchSmmMiscNodePtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (HeadFchSmmMiscNodePtr, sizeof (FCH_SMM_MISC_NODE));

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_SW_CONTEXT),
                    &EfiSmmSwContext
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ZeroMem (EfiSmmSwContext, sizeof (FCH_SMM_SW_CONTEXT));

  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    sizeof (FCH_SMM_COMMUNICATION_BUFFER),
                    &CommunicationBufferPtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  for (i = 0 ; i < sizeof (FchProtocolList) / sizeof (FCH_PROTOCOL_LIST); i++ ) {
    FchSmmDispatcherHandle =  NULL;
    Status = gSmst->SmmInstallProtocolInterface (
               &FchSmmDispatcherHandle,
               FchProtocolList[i].Guid,
               EFI_NATIVE_INTERFACE,
               FchProtocolList[i].Interface);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  Status = gSmst->SmiHandlerRegister (
                    FchSmmDispatchHandler,
                    NULL,
                    &DispatchHandle
                    );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  {
    UINT32  SmmDispatcherData32;
    UINT32  SmmDispatcherIndex;

  //
  // Clear all handled SMI status bit
  //
    for (SmmDispatcherIndex = 0; SmmDispatcherIndex < NumOfDispatcherTableEntry; SmmDispatcherIndex++ ) {
      SmmDispatcherData32 = ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FchSmmDispatcherTable[SmmDispatcherIndex].StatusReg);
      SmmDispatcherData32 &= FchSmmDispatcherTable[SmmDispatcherIndex].SmiStatusBit;
      ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FchSmmDispatcherTable[SmmDispatcherIndex].StatusReg) = SmmDispatcherData32;
    }
  //
  // Clear SmiEnB and Set EOS
  //
    SmmDispatcherData32 = ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98);
    SmmDispatcherData32 &= ~(BIT31);
    SmmDispatcherData32 |= BIT28;
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98) = SmmDispatcherData32;
  }

  AGESA_TESTPOINT (TpFchSmmDispatcherExit, NULL);
  return Status;
}

VOID
SaveB2BRegisters (
  VOID
  )
{
  EFI_SMM_CPU_IO2_PROTOCOL   *SmmCpuIo;
  UINT8                      i;
  UINT32                     PciAddress;

  SmmCpuIo = &gSmst->SmmIo;

  for (i = 0; i < NumOfB2bIoListEntry; i++) {
    SmmCpuIo->Io.Read (SmmCpuIo, B2bIoList[i].ioWidth, B2bIoList[i].ioPort, 1, &B2bIoList[i].ioValue);
  }
  for (i = 0; i < NumOfSavePciListEntry; i++) {
    PciAddress = 0x80000000;
    PciAddress |= ((SavePciList[i].Bus << 16) | (SavePciList[i].Dev << 11) | (SavePciList[i].Func << 8) | (SavePciList[i].Offset));
    SmmCpuIo->Io.Write (SmmCpuIo, SMM_IO_UINT32, CFG_ADDR_PORT, 1, &PciAddress);
    SmmCpuIo->Io.Read (SmmCpuIo, SavePciList[i].DataWidth, CFG_DATA_PORT, 1, &SavePciList[i].DataValue);
  }
}

VOID
RestoreB2BRegisters ( VOID )
{
  EFI_SMM_CPU_IO2_PROTOCOL   *SmmCpuIo;
  UINT8                      i;
  UINT32                     PciAddress;

  SmmCpuIo = &gSmst->SmmIo;

  for (i = 0; i < NumOfSavePciListEntry; i++) {
    PciAddress = 0x80000000;
    PciAddress |= ((SavePciList[i].Bus << 16) | (SavePciList[i].Dev << 11) | (SavePciList[i].Func << 8) | (SavePciList[i].Offset));
    SmmCpuIo->Io.Write (SmmCpuIo, SMM_IO_UINT32, CFG_ADDR_PORT, 1, &PciAddress);
    SmmCpuIo->Io.Write (SmmCpuIo, SavePciList[i].DataWidth, CFG_DATA_PORT, 1, &SavePciList[i].DataValue);
  }
  for (i = 0; i < NumOfB2bIoListEntry; i++) {
    SmmCpuIo->Io.Write (SmmCpuIo, B2bIoList[i].ioWidth, B2bIoList[i].ioPort, 1, &B2bIoList[i].ioValue);
  }
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
FchSmmDispatchHandler (
  IN       EFI_HANDLE                   SmmImageHandle,
  IN       CONST EFI_SMM_ENTRY_CONTEXT  *SmmEntryContext,
  IN OUT   VOID                         *CommunicationBuffer OPTIONAL,
  IN OUT   UINTN                        *SourceSize OPTIONAL
  )
{
  UINT8        SmmDispatcherIndex;
  UINT32       SmiStatusData;
  UINT32       SmiReg88StatusData;
  UINT32       UsbSmiEnableRegister;
  UINT32       UsbSmiEnableRegister1;
  UINT32       UsbSmiEnableStatus;
  UINT32       UsbSmiEnableStatus1;
  UINT32       EosStatus;
  EFI_STATUS   Status;

  Status = EFI_WARN_INTERRUPT_SOURCE_PENDING; //Updated to be compliant with UDK2010.SR1.UP1
  SaveB2BRegisters ();
  SmiReg88StatusData = ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG88) & SmiCmdPort;
  FchSmnRead (0, 0x16D80118, &UsbSmiEnableRegister, NULL);
  UsbSmiEnableStatus = UsbSmiEnableRegister & BIT8;
  FchSmnRead (0, 0x16F80118, &UsbSmiEnableRegister1, NULL);
  UsbSmiEnableStatus1 = UsbSmiEnableRegister1 & BIT8;
  do {
    if (UsbSmiEnableStatus) {
      FchSmnRW (0, 0x16D80118, 0xfffffeff, 0x000, NULL);
    }
    if (UsbSmiEnableStatus1) {
      FchSmnRW (0, 0x16F80118, 0xfffffeff, 0x000, NULL);
    }
    for (SmmDispatcherIndex = 0; SmmDispatcherIndex < NumOfDispatcherTableEntry; SmmDispatcherIndex++ ) {
      SmiStatusData = ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FchSmmDispatcherTable[SmmDispatcherIndex].StatusReg);
      if (( SmiStatusData &= FchSmmDispatcherTable[SmmDispatcherIndex].SmiStatusBit) != 0) {
        CommunicationBufferPtr->SmiStatusReg = FchSmmDispatcherTable[SmmDispatcherIndex].StatusReg;
        CommunicationBufferPtr->SmiStatusBit = SmiStatusData;
        CommunicationBuffer = (VOID *) CommunicationBufferPtr;
        Status = FchSmmDispatcherTable[SmmDispatcherIndex].SmiDispatcher (SmmImageHandle, CommunicationBuffer, SourceSize);
        if (Status != EFI_SUCCESS) {
          Status = EFI_WARN_INTERRUPT_SOURCE_PENDING;
        }
        SmmDispatcherIndex = 0;
      }
    }
    if (UsbSmiEnableStatus) {
      FchSmnRW (0, 0x16D80118, 0xfffffeff, 0x100, NULL);
    }
    if (UsbSmiEnableStatus1) {
      FchSmnRW (0, 0x16F80118, 0xfffffeff, 0x100, NULL);
    }
    ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98) |= Eos;
    EosStatus = ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98) & Eos;
  } while ((EosStatus != Eos) || (ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG84) & UsbSmi));
  RestoreB2BRegisters ();
  return  Status;
}

//temp fix..
CONST VOID* IdsDebugPrint[] =
{
  NULL
};

