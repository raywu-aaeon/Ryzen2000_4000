//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file
  Implementation of EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL

**/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/PlatformToDriverConfiguration.h>
#include <Protocol/AmiPlatformToDriverAgent.h>

EFI_HANDLE CurrentControllerHandle = NULL;                  //!< Handle of currently processed controller
AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL *CurrentAgent = NULL; //!< Currently used agent instance

/**
  Sets up a current agent.

  This function finds appropriate AMI_PLATFORM_TO_DRIVER_AGENT_PROTOCOL
  instance, based on passed parameters
  
  @param  ControllerHandle  Handle of the controller for which to find the agent
  @param  ChildHandle       Handle of the child of the controller for which to find the agent

  @retval EFI_SUCCESS       Current agent is found
  @retval EFI_NOT_FOUND     No appropriate agent for this controller

**/
EFI_STATUS GetAgent (
        IN EFI_HANDLE ControllerHandle,
        IN EFI_HANDLE ChildHandle
        )
{
    EFI_STATUS Status;
    EFI_HANDLE *Handles;
    UINTN      NoOfHandles;
    UINTN      i;
    
    Status = gBS->LocateHandleBuffer (ByProtocol, 
                                     &gAmiPlatformToDriverAgentProtocolGuid,
                                     NULL,
                                     &NoOfHandles,
                                     &Handles);
    if (EFI_ERROR (Status)) {
        return Status;
    }

    for (i = 0; i < NoOfHandles; i++) {
        Status = gBS->HandleProtocol (Handles[i], &gAmiPlatformToDriverAgentProtocolGuid, &CurrentAgent);
        if (EFI_ERROR (Status))
            continue;
        Status = CurrentAgent->Supported (CurrentAgent, ControllerHandle, ChildHandle);
        if (!EFI_ERROR (Status))
            return Status;
    }
    CurrentAgent = NULL;
    return EFI_NOT_FOUND;
}

/**
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL Query member function implementation

  This function allow the UEFI driver to query the platform for configuration needed
  to complete driver's Start() operation
  
  @param This                 A pointer to the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL instance.
  
  @param ControllerHandle     The handle the platform will return
                              configuration information about.
  
  @param ChildHandle          The handle of the child controller to
                              return information on. This is an optional
                              parameter that may be NULL. It will be
                              NULL for device drivers and for bus
                              drivers that attempt to get options for
                              the bus controller. It will not be NULL
                              for a bus driver that attempts to get
                              options for one of its child controllers.
  
  
  @param Instance             Pointer to the Instance value. Zero means
                              return the first query data. The caller should
                              increment this value by one each time to retrieve
                              successive data.

  @param ParameterTypeGuid    An EFI_GUID that defines the contents
                              of ParameterBlock. UEFI drivers must
                              use the ParameterTypeGuid to determine
                              how to parse the ParameterBlock. The caller
                              should not attempt to free ParameterTypeGuid.

  @param ParameterBlock       The platform returns a pointer to the
                              ParameterBlock structure which
                              contains details about the
                              configuration parameters specific to
                              the ParameterTypeGuid. This structure
                              is defined based on the protocol and
                              may be different for different
                              protocols. UEFI driver decodes this
                              structure and its contents based on
                              ParameterTypeGuid. ParameterBlock is
                              allocated by the platform and the
                              platform is responsible for freeing
                              the ParameterBlock after Result is
                              called.

  @param ParameterBlockSize   The platform returns the size of
                              the ParameterBlock in bytes.


  @retval EFI_SUCCESS           The platform return parameter
                                information for ControllerHandle.

  @retval EFI_NOT_FOUND         No more unread Instance exists.

  @retval EFI_INVALID_PARAMETER ControllerHandle is NULL.

  @retval EFI_INVALID_PARAMETER Instance is NULL.

  @retval EFI_DEVICE_ERROR      A device error occurred while
                                attempting to return parameter block
                                information for the controller
                                specified by ControllerHandle and
                                ChildHandle.

  @retval EFI_OUT_RESOURCES     There are not enough resources
                                available to set the configuration
                                options for the controller specified
                                by ControllerHandle and ChildHandle.

**/
EFI_STATUS PlatformToDriverConfigurationQuery (
        IN  CONST EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
        IN  CONST EFI_HANDLE                              ControllerHandle,
        IN  CONST EFI_HANDLE                              ChildHandle,
        IN  CONST UINTN                                   *Instance,
        OUT EFI_GUID                                      **ParameterTypeGuid,
        OUT VOID                                          **ParameterBlock,
        OUT UINTN                                         *ParameterBlockSize
        )
{
    EFI_STATUS Status;

    if (ControllerHandle == NULL || Instance == NULL)
        return EFI_INVALID_PARAMETER;

    if (ControllerHandle != CurrentControllerHandle) {
        Status = GetAgent ((EFI_HANDLE) ControllerHandle, (EFI_HANDLE) ChildHandle);
        if (EFI_ERROR (Status)) {
            CurrentControllerHandle = NULL;
            return EFI_NOT_FOUND;
        }

        CurrentControllerHandle = ControllerHandle;
    }

    return CurrentAgent->Query (CurrentAgent,
                              (EFI_HANDLE) ControllerHandle,
                              (EFI_HANDLE) ChildHandle,
                              (UINTN *) Instance,
                               ParameterTypeGuid,
                               ParameterBlock,
                               ParameterBlockSize);
}

/**
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL Response member function implementation

  This function tell the platform what actions where taken by the driver after processing
  the data returned from Query
  
  @param This                A pointer to the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL instance.

  @param ControllerHandle    The handle the driver is returning
                             configuration information about.

  @param ChildHandle         The handle of the child controller to
                             return information on. This is an optional
                             parameter that may be NULL. It will be
                             NULL for device drivers, and for bus
                             drivers that attempt to get options for
                             the bus controller. It will not be NULL
                             for a bus driver that attempts to get
                             options for one of its child controllers.
                             Instance Instance data returned from
                             Query().

  @param Instance            Instance data passed to Query().

  @param ParameterTypeGuid   ParameterTypeGuid returned from Query.

  @param ParameterBlock      ParameterBlock returned from Query.

  @param ParameterBlockSize  The ParameterBlock size returned from Query.

  @param ConfigurationAction The driver tells the platform what
                             action is required for ParameterBlock to
                             take effect.
  
  
  @retval EFI_SUCCESS           The platform return parameter information
                                for ControllerHandle.
  
  @retval EFI_NOT_FOUND         Instance was not found.
  
  @retval EFI_INVALID_PARAMETER ControllerHandle is NULL.
 
  @retval EFI_INVALID_PARAMETER Instance is zero.
  
**/
EFI_STATUS PlatformToDriverConfigurationResponse (
        IN CONST EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
        IN CONST EFI_HANDLE                                    ControllerHandle,
        IN CONST EFI_HANDLE                                    ChildHandle,
        IN CONST UINTN                                         *Instance,
        IN CONST EFI_GUID                                      *ParameterTypeGuid,
        IN CONST VOID                                          *ParameterBlock,
        IN CONST UINTN                                         ParameterBlockSize,
        IN CONST EFI_PLATFORM_CONFIGURATION_ACTION             ConfigurationAction
        )
{
    if (ControllerHandle == NULL || Instance == NULL)
        return EFI_INVALID_PARAMETER;

    if (ControllerHandle != CurrentControllerHandle || CurrentAgent == NULL)
        return EFI_NOT_FOUND;

    return CurrentAgent->Response (CurrentAgent,
            (EFI_HANDLE)                        ControllerHandle,
            (EFI_HANDLE)                        ChildHandle,
            (UINTN *)                           Instance,
            (EFI_GUID *)                        ParameterTypeGuid,
            (VOID *)                            ParameterBlock,
            (UINTN)                             ParameterBlockSize,
            (EFI_PLATFORM_CONFIGURATION_ACTION) ConfigurationAction);
}

/**
  Instance of EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL that will be installed
  
**/

EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL EfiPlatformToDriverConfigurationProtocol = {
    PlatformToDriverConfigurationQuery,
    PlatformToDriverConfigurationResponse
};

/**
  The user Entry Point for module PlatformToDriver. The user code starts with this function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS EFIAPI PlatformToDriverEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS Status;
    EFI_HANDLE Handle = NULL;

    Status = gBS->InstallMultipleProtocolInterfaces (
                                &Handle,
                                &gEfiPlatformToDriverConfigurationProtocolGuid, 
                                &EfiPlatformToDriverConfigurationProtocol,
                                NULL);

    return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
