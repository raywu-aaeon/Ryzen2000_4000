//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file FastBootSmi.c
 *  Implementation of fast boot smi functionality.
 */

#include <Library/DebugLib.h>
#include <AmiDxeLib.h>
#include <Token.h>
#include <Setup.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>




extern EFI_GUID gEfiSmmSwDispatch2ProtocolGuid;
EFI_SMM_BASE2_PROTOCOL          *gSmmBase2;
EFI_SMM_SYSTEM_TABLE2           *gSmst2;


/**
 * SwSmiHandler.
 *    
 * @param[in]   DispatchHandle         Handle of this dispatch function. 
 * @param[in]   Context                Points to an optional handler context which was specified when the handler was registered.
 * @param[in]   CommBuffer             A pointer to a collection of data in memory that 
 *                                     will be conveyed from a non-SMM environment into an SMM environment.
 * @param[in]   CommBufferSize         The size of the CommBuffer.
 *
 * @retval      EFI_SUCCESS            Set variable success.
 * @retval      Other                  Get or Set variable failed.
 */

EFI_STATUS 
EFIAPI 
SwSmiHandler (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context OPTIONAL,
  IN OUT VOID    *CommBuffer OPTIONAL,
  IN OUT UINTN   *CommBufferSize OPTIONAL )
{

    EFI_STATUS  Status;
    EFI_GUID    SetupGuid = SETUP_GUID;
    UINTN       SetupDataSize = sizeof(SETUP_DATA);    
    SETUP_DATA  SetupData;
    UINT32      Attributes;
    
    Status = gRT->GetVariable(
                    L"Setup", 
                    &SetupGuid, 
                    &Attributes, 
                    &SetupDataSize, 
                    &SetupData);
    if (EFI_ERROR(Status)) return Status;
    
    SetupData.FastBoot = 0;      

    Status = gRT->SetVariable(
                    L"Setup", 
                    &SetupGuid,
                    Attributes,
                    SetupDataSize, 
                    &SetupData);
    return Status;
}

/**
 * Set PM under AMITSE_EVENT_BEFORE_BOOT_GUID.
 *    
 * @param[in]   ImageHandle         The firmware allocated handle for the EFI image. 
 * @param[in]   SystemTable         A pointer to the EFI System Table.
 *
 * @retval      EFI_SUCCESS         The entry point is executed successfully.
 */

EFI_STATUS 
EFIAPI 
FastBootSmiEntryPoint(
    IN EFI_HANDLE           ImageHandle,
    IN EFI_SYSTEM_TABLE     *SystemTable
)
{ 
    EFI_STATUS                      Status;
    EFI_HANDLE                      SwSmiHandle = NULL;
    EFI_SMM_SW_DISPATCH2_PROTOCOL   *SwSmiDispatch = NULL;
    EFI_SMM_SW_REGISTER_CONTEXT     SwSmiContext;

    InitAmiSmmLib( ImageHandle, SystemTable );
    
    Status = gBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, (VOID **) &gSmmBase2);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = gSmmBase2->GetSmstLocation (gSmmBase2, &gSmst2);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    Status = gSmst2->SmmLocateProtocol(&gEfiSmmSwDispatch2ProtocolGuid,
                                       NULL,
                                       (VOID **)&SwSmiDispatch);
    if (EFI_ERROR(Status)) return EFI_SUCCESS;

    SwSmiContext.SwSmiInputValue = FAST_BOOT_DISABLE_SWSMI;
    Status = SwSmiDispatch->Register(SwSmiDispatch,
                                     SwSmiHandler,
                                     &SwSmiContext,
                                     &SwSmiHandle);
    if (EFI_ERROR (Status)) return Status;
    
    return EFI_SUCCESS;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


