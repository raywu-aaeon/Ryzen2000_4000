/* $NoKeywords:$ */
/**
 * @file
 *
 * GNB VGA decode control
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project   GNB DXE Driver
 * @e \$Revision$   @e \$Date$
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
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiLib.h>

#include <Protocol\PciRootBridgeIo.h>
#include <Protocol\PciIo.h>
#include <Library\S3BootScriptLib.h>

#define FILECODE UEFI_DXE_AMDIGPUVGACONTROLDXE_AMDIGPUVGACONTROLDXE_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define VGA_ATTRIBUTES (EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO | EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO)


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */

EFI_EVENT                             PciIoEvent;
VOID                                  *mRegistrationForPciIo;
EFI_PCI_IO_PROTOCOL_ATTRIBUTES        mGenericAttributes;
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *mPciRootBridgeIo = NULL;


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
EFIAPI
HookiGpuPciIo (
  IN      EFI_EVENT         Event,
  IN      VOID              *Context
  );

VOID
WritePci32 (
  IN      UINT64            Address,
  IN      UINT32            Value,
  IN      BOOLEAN           Save
  );

UINT32
ReadPci32 (
  IN      UINT64            Address
  );

VOID
SetVgaDecode (
  IN      BOOLEAN           VgaDecode
  );



/**
 *---------------------------------------------------------------------------------------
 *
 *  AmdiGpuVgaControlDxeInit
 *
 *  Description:
 *     Monitor attribute enablement request
 *
 *  Parameters:
 *    @param[in]     ImageHandle
 *    @param[in]     SystemTable
 *
 *    @retval         EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/

EFI_STATUS
EFIAPI
AmdiGpuVgaControlDxeInit (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                      Status;
  //
  // Initialize Global Variable
  //

  //
  // Locate Root Bridge IO
  //
  Status = gBS->LocateProtocol (
                  &gEfiPciRootBridgeIoProtocolGuid,
                  NULL,
                  &mPciRootBridgeIo
                  );
  ASSERT_EFI_ERROR (Status);
  //
  // Register the event handling function for PCIO install protocol
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HookiGpuPciIo,
                  NULL,
                  NULL,
                  &PciIoEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->RegisterProtocolNotify (
                  &gEfiPciIoProtocolGuid,
                  PciIoEvent,
                  &mRegistrationForPciIo
                  );
  ASSERT_EFI_ERROR (Status);
  //
  // Disable VGA decoding by default (enablement would have to be requested through PciIo protocol)
  //
  SetVgaDecode (FALSE);
  return Status;
}


/**
 *---------------------------------------------------------------------------------------
 *
 *  AmdiGpuAttributes
 *
 *  Description:
 *     Monitor attribute enablement request
 *
 *  Parameters:
 *    @param[in]     This
 *    @param[in]     Operation
 *    @param[in]     Attributes
 *    @param[out]    OPTIONAL Result
 *
 *    @retval        EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/

EFI_STATUS
AmdiGpuAttributes (
  IN       EFI_PCI_IO_PROTOCOL                       *This,
  IN       EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION  Operation,
  IN       UINT64                                   Attributes,
     OUT   UINT64                                   *Result OPTIONAL
  )
{
  if (Operation == EfiPciIoAttributeOperationSet || Operation == EfiPciIoAttributeOperationEnable) {
    if ((Attributes & VGA_ATTRIBUTES) != 0) {
      SetVgaDecode (TRUE);
    }
  } else if (Operation == EfiPciIoAttributeOperationDisable) {
    if ((Attributes & VGA_ATTRIBUTES) != 0) {
      SetVgaDecode (FALSE);
    }
  }
  return mGenericAttributes (This, Operation, Attributes, Result);
}


/**
 *---------------------------------------------------------------------------------------
 *
 *  HookiGpuPciIo
 *
 *  Description:
 *     Calls hook to PCIIO protocol for iGPU
 *
 *  Parameters:
 *    @param[in]     Event
 *    @param[in]     *Context
 *
 *    @retval         VOID
 *
 *---------------------------------------------------------------------------------------
 **/

VOID
EFIAPI
HookiGpuPciIo (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS           Status;
  EFI_HANDLE           Handle;
  UINTN                Size;
  EFI_PCI_IO_PROTOCOL  *PciIo;
  UINTN                Segment;
  UINTN                Bus;
  UINTN                Device;
  UINTN                Function;

  Size = sizeof (EFI_HANDLE);
  Status = gBS->LocateHandle (
                  ByRegisterNotify,
                  NULL,
                  mRegistrationForPciIo,
                  &Size,
                  &Handle
                  );
  ASSERT_EFI_ERROR (Status);
  //
  // Locate PCIIO protocol associated with registration
  //
  Status = gBS->HandleProtocol (Handle, &gEfiPciIoProtocolGuid, &PciIo);
  ASSERT_EFI_ERROR (Status);
  //
  // Determine device managed by protocol
  //
  Status = PciIo->GetLocation (PciIo, &Segment, &Bus, &Device, &Function);
  if ((Bus == 0) && (Device == 1) && (Function == 0)) {
    //
    // Hook to function that set attributed
    //
    mGenericAttributes = PciIo->Attributes;
    PciIo->Attributes = AmdiGpuAttributes;
    gBS->CloseEvent (Event);
  }
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  SetVgaDecode
 *
 *  Description:
 *     Control VGA decode
 *
 *  Parameters:
 *    @param[in]     VgaDecode
 *
 *
 *---------------------------------------------------------------------------------------
 **/

VOID
SetVgaDecode (
  IN    BOOLEAN   VgaDecode
  )
{
  UINT32 Value;

  WritePci32 (EFI_PCI_ADDRESS (0, 0, 0, 0x60), 0x9D, TRUE);
  Value = ReadPci32 (EFI_PCI_ADDRESS (0, 0, 0, 0x64));
  Value &= ~(0x2);
  if (VgaDecode) {
    Value |= 0x2;
  }
  WritePci32 (EFI_PCI_ADDRESS (0, 0, 0, 0x64), Value, TRUE);
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  WritePci32
 *
 *  Description:
 *    Write PCI DWORD
 *
 *  Parameters:
 *    @param[in]     Address
 *    @param[in]     Value
 *    @param[in]     Save
 *
 *    @retval         Content of PCI register
 *---------------------------------------------------------------------------------------
 **/
VOID
WritePci32 (
  IN      UINT64   Address,
  IN      UINT32   Value,
  IN      BOOLEAN  Save
  )
{

  mPciRootBridgeIo->Pci.Write (mPciRootBridgeIo, EfiPciIoWidthUint32, Address, 1, &Value);

  if (Save) {
    S3BootScriptSavePciCfgWrite (
                  EfiPciIoWidthUint32,
                  Address,
                  1,
                  &Value);
  }
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  ReadPci32
 *
 *  Description:
 *    Read PCI DWORD
 *
 *  Parameters:
 *    @param[in]     Address
 *
 *---------------------------------------------------------------------------------------
 **/
UINT32
ReadPci32 (
  IN      UINT64   Address
  )
{
  UINT32  Value;

  mPciRootBridgeIo->Pci.Read (mPciRootBridgeIo, EfiPciIoWidthUint32, Address, 1, &Value);

  return Value;
}

