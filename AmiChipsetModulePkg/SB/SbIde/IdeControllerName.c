//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file IdeControllerName.c
    Initialize and provide a protocol for the Ide controller.


**/
//**********************************************************************

// Module specific Includes

#include "IdeController.h"

#include <Protocol/DriverBinding.h>
#include <Protocol/PIDEController.h>

EFI_DRIVER_BINDING_PROTOCOL  gIdeBusDriverBinding;
EFI_GUID                     gEfiIdeControllerProtocolGuid = IDE_CONTROLLER_PROTOCOL_GUID;

extern CHAR16  *gIdeDriverName;
extern CHAR16  *gIdeControllerName;

//
// EFI Component Name Protocol
// This portion declares a gloabl variable of EFI_COMPONENT_NAME2_PROTOCOL type.
//
EFI_COMPONENT_NAME2_PROTOCOL gComponentNameProtocol = {
  IdeControllerGetDriverName,
  IdeControllerGetControllerName,
  LANGUAGE_CODE_ENGLISH
};

/**
    Retrieves a Unicode string that is the user readable name of
    the EFI Driver.


        
    @param This A pointer to the EFI_COMPONENT_NAME2_PROTOCOL instance.
    @param Language A pointer to a three character ISO 639-2 language identifier.
        This is the language of the driver name that that the caller
        is requesting, and it must match one of the languages specified
        in SupportedLanguages.  The number of languages supported by a
        driver is up to the driver writer.
    @param DriverName A pointer to the Unicode string to return.  This Unicode string
        is the name of the driver specified by This in the language
        specified by Language.

         
    @retval EFI_SUCCES The Unicode string for the Driver specified by This
        and the language specified by Language was returned
        in DriverName.
    @retval EFI_INVALID_PARAMETER Language is NULL.
    @retval EFI_INVALID_PARAMETER DriverName is NULL.
    @retval EFI_UNSUPPORTED The driver specified by This does not support the
        language specified by Language.

**/
EFI_STATUS
IdeControllerGetDriverName (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
)
{
    if(!Language || !DriverName) return EFI_INVALID_PARAMETER;
    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH))
        return EFI_UNSUPPORTED;
    *DriverName = gIdeDriverName;
    return EFI_SUCCESS;
}

/**
    Retrieves a Unicode string that is the user readable name of
    the controller that is being managed by an EFI Driver.

        
    @param This A pointer to the EFI_COMPONENT_NAME2_PROTOCOL instance.
    @param ControllerHandle The handle of a controller that the driver specified by
        This is managing.  This handle specifies the controller
        whose name is to be returned.
    @param ChildHandle OPTIONAL      - The handle of the child controller to retrieve the name
        of.  This is an optional parameter that may be NULL.  It
        will be NULL for device drivers.  It will also be NULL
        for a bus drivers that wish to retrieve the name of the
        bus controller.  It will not be NULL for a bus driver
        that wishes to retrieve the name of a child controller.
    @param Language A pointer to a three character ISO 639-2 language
        identifier.  This is the language of the controller name
        that that the caller is requesting, and it must match one
        of the languages specified in SupportedLanguages.  The
        number of languages supported by a driver is up to the
        driver writer.
    @param ControllerName A pointer to the Unicode string to return.  This Unicode
        string is the name of the controller specified by
        ControllerHandle and ChildHandle in the language
        specified by Language from the point of view of the
        driver specified by This.

         
    @retval EFI_SUCCESS The Unicode string for the user readable name in the
        language specified by Language for the driver
        specified by This was returned in DriverName.
    @retval EFI_INVALID_PARAMETER ControllerHandle is not a valid EFI_HANDLE.
    @retval EFI_INVALID_PARAMETER ChildHandle is not NULL and it is not a valid
        EFI_HANDLE.
    @retval EFI_INVALID_PARAMETER Language is NULL.
    @retval EFI_INVALID_PARAMETER ControllerName is NULL.
    @retval EFI_UNSUPPORTED The driver specified by This is not currently
        managing the controller specified by
        ControllerHandle and ChildHandle.
    @retval EFI_UNSUPPORTED The driver specified by This does not support the
        language specified by Language.

**/
EFI_STATUS
IdeControllerGetControllerName (
  IN  EFI_COMPONENT_NAME2_PROTOCOL  *This,
  IN  EFI_HANDLE                   ControllerHandle,
  IN  EFI_HANDLE                   ChildHandle        OPTIONAL,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **ControllerName
  )
{
    EFI_STATUS                          Status;

    Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiIdeControllerProtocolGuid,
                  NULL,
                  gIdeBusDriverBinding.DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );

    if (Status != EFI_SUCCESS && Status != EFI_ALREADY_STARTED) 
        return EFI_UNSUPPORTED;

    if(!Language || !ControllerName) return EFI_INVALID_PARAMETER;

    if (!LanguageCodesEqual( Language, LANGUAGE_CODE_ENGLISH))
        return EFI_UNSUPPORTED;

     *ControllerName = gIdeControllerName;
     return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
