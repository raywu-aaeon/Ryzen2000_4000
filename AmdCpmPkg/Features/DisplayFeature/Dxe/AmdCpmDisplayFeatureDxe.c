/*****************************************************************************
 *
 * Copyright 2012 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#include <AmdCpmDxe.h>

VOID
EFIAPI
AmdCpmDisplayFeatureInitMid (
  IN        EFI_EVENT       Event,
  IN        VOID            *Context
  );

VOID
EFIAPI
AmdCpmDisplayFeatureInitLateEntry (
  IN        EFI_EVENT       Event,
  IN        VOID            *Context
  );

VOID
EFIAPI
AmdCpmDisplayFeatureVbiosShadow (
  IN        EFI_EVENT       Event,
  IN        VOID            *Context
  );

/*----------------------------------------------------------------------------------------*/
/**
 * Entry point of the AMD CPM Display Feature DXE driver
 *
 * This function installs AMD CPM DISPLAY FEATURE PROTOCOL and initialize display features.
 *
 * @param[in]     ImageHandle    Pointer to the firmware file system header
 * @param[in]     SystemTable    Pointer to System table
 *
 * @retval        EFI_SUCCESS    Module initialized successfully
 * @retval        EFI_ERROR      Initialization failed (see error for more details)
 */

EFI_STATUS
EFIAPI
AmdCpmDisplayFeatureDxeEntryPoint (
  IN        EFI_HANDLE                      ImageHandle,
  IN        EFI_SYSTEM_TABLE                *SystemTable
  )
{
  EFI_STATUS                                Status;
  EFI_EVENT                                 ReadyToBootEvent;
  EFI_EVENT                                 PciIoEvent;
  EFI_HANDLE                                Handle;
  AMD_CPM_DISPLAY_FEATURE_PROTOCOL          *CpmDisplayFeatureProtocolPtr;
  AMD_CPM_TABLE_PROTOCOL                    *CpmTableProtocolPtr;
  EFI_PCI_IO_PROTOCOL                       *PciIo;
  AMD_CPM_ALL_PCI_IO_PROTOCOLS_INSTALLED_PROTOCOL *Tmp;
  VOID                                      *RegistrationForPciIoPtr;

  //
  // Initialize Global Variable
  //
  CpmInitializeDriverLib (ImageHandle, SystemTable);

  RECORD_TIME_DXE (BeginAmdCpmDisplayFeatureDxeDriver);

  Status = gBS->LocateProtocol (  &gAmdCpmTableProtocolGuid,
                                  NULL,
                                  (VOID**)&CpmTableProtocolPtr
                                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDxeDriverBegin);

  Status = gBS->AllocatePool (
                    EfiACPIMemoryNVS,
                    sizeof (AMD_CPM_DISPLAY_FEATURE_PROTOCOL),
                    (VOID**)&CpmDisplayFeatureProtocolPtr
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  CpmDisplayFeatureProtocolPtr = ZeroMem (CpmDisplayFeatureProtocolPtr, sizeof (AMD_CPM_DISPLAY_FEATURE_PROTOCOL));

  CpmDisplayFeatureProtocolPtr->Revision                                      = AMD_CPM_DISPLAY_FEATURE_PROTOCOL_REV;
  CpmDisplayFeatureProtocolPtr->TableProtocolPtr                              = CpmTableProtocolPtr;
  CpmDisplayFeatureProtocolPtr->DisplayFeatureData.DisplayFeatureTablePtr     = (VOID *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_DISPLAY_FEATURE);
  CpmDisplayFeatureProtocolPtr->DisplayFeatureData.DevicePathTablePtr         = (VOID *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_DEVICE_PATH);
  CpmDisplayFeatureProtocolPtr->DisplayFeatureData.SpecificSsidTablePtr       = (VOID *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_SPECIFIC_SSID);
  CpmDisplayFeatureProtocolPtr->DisplayFeatureData.RebrandDualGraphicsSsidTablePtr  = (VOID *)CpmTableProtocolPtr->CommonFunction.GetTablePtr (CpmTableProtocolPtr, CPM_SIGNATURE_REBRAND_DUAL_GRAPHICS_SSID);

  Handle = ImageHandle;
  Status = gBS->InstallProtocolInterface (
                    &Handle,
                    &gAmdCpmDisplayFeatureProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    CpmDisplayFeatureProtocolPtr
                    );
  if (EFI_ERROR (Status)) {
    return (Status);
  }

  Status = gBS->LocateProtocol (
                    &gEfiPciIoProtocolGuid,
                    NULL,
                    (VOID**)&PciIo
                    );

  if (EFI_ERROR (Status)) {
    Status = gBS->LocateProtocol (
                    &gAmdCpmAllPciIoProtocolsInstalledProtocolGuid,
                    NULL,
                    (VOID**)&Tmp
                    );
    if (EFI_ERROR (Status)) {
      AmdCpmDisplayFeatureInitMid (NULL, CpmDisplayFeatureProtocolPtr);
    } else {
      AmdCpmDisplayFeatureVbiosShadow (NULL, CpmDisplayFeatureProtocolPtr);
    }
  } else {
    Status = gBS->CreateEvent (
                    CPM_EVENT_NOTIFY_SIGNAL,
                    CPM_TPL_NOTIFY,
                    AmdCpmDisplayFeatureInitMid,
                    CpmDisplayFeatureProtocolPtr,
                    (VOID**)&PciIoEvent
                    );

    Status = gBS->RegisterProtocolNotify (
                    &gEfiPciIoProtocolGuid,
                    PciIoEvent,
                    (VOID**)&RegistrationForPciIoPtr
                    );
  }
  Status = gBS->CreateEventEx (
                    CPM_EVENT_NOTIFY_SIGNAL,
                    CPM_TPL_NOTIFY,
                    AmdCpmDisplayFeatureInitLateEntry,
                    CpmDisplayFeatureProtocolPtr,
                    &gEfiEventReadyToBootGuid,
                    (VOID**)&ReadyToBootEvent
                    );

  CpmTableProtocolPtr->CommonFunction.PostCode (CpmTpDisplayFeatureDxeDriverEnd);

  RECORD_TIME_DXE (EndAmdCpmDisplayFeatureDxeDriver);

  return EFI_SUCCESS;
}
