/* $NoKeywords:$ */
/**
 * @file
 *
 * FCH DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   Legacy Interrupt DXE Driver
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
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

#include "LegacyInterrupt.h"
#define FILECODE UEFI_DXE_LEGACYINTERRUPT_LEGACYINTERRUPT_FILECODE


// Get the number of PIRQs supported.
EFI_STATUS
AmdGetNumberPirqs (
  IN       EFI_LEGACY_INTERRUPT_PROTOCOL *This,
     OUT   UINT8                         *NumberPirqs
  )
{
  if (NULL == NumberPirqs) {
    return EFI_INVALID_PARAMETER;
  }

  *NumberPirqs = MAX_NUMBER_PIRQS;
  return EFI_SUCCESS;
}


// Get the PCI bus#, device# and function# that associated with this protocol.
EFI_STATUS
AmdGetLocation (
  IN       EFI_LEGACY_INTERRUPT_PROTOCOL *This,
     OUT   UINT8                         *Bus,
     OUT   UINT8                         *Device,
     OUT   UINT8                         *Function
  )
{
  if ((NULL == Bus) || (NULL == Device) || (NULL == Function)) {
    return EFI_INVALID_PARAMETER;
  }

  *Bus      = FCH_PCI_BUS;
  *Device   = FCH_PCI_DEV;
  *Function = FCH_PCI_FUNC;

  return EFI_SUCCESS;
}


// Read the given PIRQ register and return the IRQ value that is assigned to it.
EFI_STATUS
AmdReadPirq (
  IN       EFI_LEGACY_INTERRUPT_PROTOCOL *This,
  IN       UINT8                         PirqNumber,
     OUT   UINT8                         *PirqData
  )
{
  if (NULL == PirqData) {
    return EFI_INVALID_PARAMETER;
  }
  LibFchIndirectIoRead (EfiPciWidthUint8, FCH_IOMAP_REGC00, PirqNumber, PirqData);

  return EFI_SUCCESS;
}


// Write an IRQ value to the specified PIRQ register.
EFI_STATUS
AmdWritePirq (
  IN       EFI_LEGACY_INTERRUPT_PROTOCOL *This,
  IN       UINT8                         PirqNumber,
  IN       UINT8                         PirqData
  )
{
  //if ((PirqNumber >= MAX_NUMBER_PIRQS) || (PirqData > 15)) {
  //  return EFI_INVALID_PARAMETER;
  //}
  LibFchIndirectIoWrite (EfiPciWidthUint8, FCH_IOMAP_REGC00, PirqNumber, &PirqData);

  return EFI_SUCCESS;
}


/*----------------------------------------------------------------------------------------*/
/**
 * Name: AmdInstallLegacyInterrupt
 *
 * This DXE driver produces the legacy interrupt protocol as part of the EfiCompatibility
 * component in CSM. This protocol will manage the programming of PCI IRQ assignment.
 *
 * @param[in]    ImageHandle     Pointer to the image handle
 * @param[in]    SystemTable     Pointer to the EFI system table
 *
 * @retval       EFI_SUCCESS     Driver initialized successfully
 * @retval       EFI_ERROR       Driver initialization failed
 *
 */
/*----------------------------------------------------------------------------------------*/
EFI_STATUS
AmdInstallLegacyInterrupt (
  IN       EFI_HANDLE              ImageHandle,
  IN       EFI_SYSTEM_TABLE        *SystemTable
  )
{
  EFI_LEGACY_INTERRUPT_PROTOCOL    *LegacyInterrupt;
  VOID                             *Instance;
  UINT8                            i;
  UINT8                            bValue;
  EFI_STATUS                       Status;

  //
  // Initialize PCI IRQ routing registers for INTA#-INTH#
  //
  for (i = 0; i < 8; i++) {
    bValue = i | BIT7;                                 // Select IRQ routing to APIC
    LibFchIoWrite (EfiPciWidthUint8, FCH_IOMAP_REGC00, &bValue);
    bValue = i | BIT4;
    LibFchIoWrite (EfiPciWidthUint8, FCH_IOMAP_REGC01, &bValue);
  }

  //
  // Check and see if the protocol has been installed already
  //
  Status = gBS->LocateProtocol (
                  &gEfiLegacyInterruptProtocolGuid,
                  NULL,
                  &Instance
                  );
  ASSERT (EFI_ERROR (Status));

  //
  // Allocate memory and initialize the data structure
  //
  Status = gBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_LEGACY_INTERRUPT_PROTOCOL),
                  &LegacyInterrupt
                  );
  ASSERT_EFI_ERROR (Status);

  LegacyInterrupt->GetNumberPirqs = AmdGetNumberPirqs;
  LegacyInterrupt->GetLocation    = AmdGetLocation;
  LegacyInterrupt->ReadPirq       = AmdReadPirq;
  LegacyInterrupt->WritePirq      = AmdWritePirq;


  //
  // Finally install the protocol
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiLegacyInterruptProtocolGuid,
                  LegacyInterrupt,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return (Status);
}


