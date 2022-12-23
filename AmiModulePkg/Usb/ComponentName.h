//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file ComponentName.h
    AMI USB driver component name header file

**/

#ifndef _AMIUSB_COMPONENT_NAME_H__
#define _AMIUSB_COMPONENT_NAME_H__

#include <Protocol/ComponentName2.h>
#include <Library/BaseLib.h>

#ifndef LANGUAGE_CODE_ENGLISH_2
#define LANGUAGE_CODE_ENGLISH_2 "en"
#endif

extern EFI_COMPONENT_NAME2_PROTOCOL gComponentNameUsb;
extern EFI_COMPONENT_NAME2_PROTOCOL gComponentNameUsbBus;
extern EFI_COMPONENT_NAME2_PROTOCOL gComponentNameUsbMass;
extern EFI_COMPONENT_NAME2_PROTOCOL gComponentNameUsbHid;
//
// EFI Component Name Functions
//
EFI_STATUS
EFIAPI
AmiUsbComponentNameGetDriverName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  CHAR8                         *Language,
    OUT CHAR16                        **DriverName
);

EFI_STATUS
EFIAPI
AmiUsbComponentNameGetControllerName (
    IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
    IN  EFI_HANDLE                    ControllerHandle,
    IN  EFI_HANDLE                    ChildHandle        OPTIONAL,
    IN  CHAR8                         *Language,
    OUT CHAR16                        **ControllerName
  );
                                        //<(EIP59272)
#endif //_AMIUSB_COMPONENT_NAME_H__

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
