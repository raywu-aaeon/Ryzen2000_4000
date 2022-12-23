//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Runtime specific portion of the AmiFlashLib. Contains the library constructor and
  performs the necessary initialization of the library and installs a callback to
  handle virtual address changes.
**/
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Library/AmiFlashLib.h>

#include <Token.h>

extern UINTN        gAmiFlashDeviceBase;
static EFI_EVENT    gRuntimeAmiFlashLibVirtualAddressChangeEvent = NULL;

VOID
FlashVirtualFixup(
    IN  EFI_RUNTIME_SERVICES *Rs
);

EFI_STATUS
EFIAPI
DxeAmiFlashLibConstructor(
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
);

/**
 * Notification callback function for the virtual event change. This function is called when
 * the system is notified of the change to a virtual addressing mode so that the pointers
 * used can be converted to their virtual addresses.
 *
 * @param Event The event handle
 * @param Context The context of the notification event
 */
VOID
EFIAPI
AmiFlashLibVirtualNotifyEvent(
    IN  EFI_EVENT   Event,
    IN  VOID        *Context
)
{
    FlashVirtualFixup( gRT );
    gRT->ConvertPointer( 0, (VOID**)&gAmiFlashDeviceBase );
}

/**
 * Library constructor for the Runtime AmiFlashLib instance.
 *
 * @param ImageHandle The ImageHandle of the driver consuming the AmiFlashLib
 * @param SystemTable Pointer to the EFI System Table
 *
 * @return EFI_SUCCESS The library constructor completed execution
 */
EFI_STATUS
EFIAPI
RuntimeAmiFlashLibConstructor(
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
)
{
    gBS->CreateEvent(
            EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE,
            TPL_CALLBACK,
            AmiFlashLibVirtualNotifyEvent,
            NULL,
            &gRuntimeAmiFlashLibVirtualAddressChangeEvent );

    return DxeAmiFlashLibConstructor( ImageHandle, SystemTable );
}

/**
 * Library destructor for the Runtime AmiFlashLib instance.
 *
 * @param ImageHandle The ImageHandle of the driver consuming the AmiFlashLib
 * @param SystemTable Pointer to the EFI System Table
 *
 * @return EFI_SUCCESS The library destructor completed successfully
 */
EFI_STATUS
EFIAPI
RuntimeAmiFlashLibDestructor(
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
){
    return gBS->CloseEvent( gRuntimeAmiFlashLibVirtualAddressChangeEvent );
}