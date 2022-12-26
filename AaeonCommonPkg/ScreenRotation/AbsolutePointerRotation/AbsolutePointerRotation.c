//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AbsolutePointerRotation.c

    This module rotates the coordinates reported by absolute pointer.
*/

//============================================================================
// Includes
//============================================================================
#include <AmiDxeLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/AbsolutePointer.h>
#include <../ScreenRotation.h>

typedef struct {
    DLINK                                    Link;
    EFI_HANDLE                               Handle;
    EFI_ABSOLUTE_POINTER_PROTOCOL            *AbsolutePointer;
    EFI_ABSOLUTE_POINTER_GET_STATE           OrgGetState;
    EFI_ABSOLUTE_POINTER_MODE                OrgMode;
} ABSOLUTE_POINTER_INFO;

//============================================================================
// Define
//============================================================================

//============================================================================
// External Global Variable Declaration
//============================================================================

//============================================================================
// Global Variable Declaration
//============================================================================
static VOID *Registration = NULL;
static SCREEN_ROTATION_POLICY Policy;
static ABSOLUTE_POINTER_INFO *gAbsolutePointerInfo = NULL;

//============================================================================
// Function Definitions
//============================================================================
/** 
    Rotation hook for absolute pointer.

    Absolute pointer should point to the original coordinates before rotated to let ESA/TSE work. 

    @param This   A pointer to the EFI_ABSOLUTE_POINTER_PROTOCOL
                  instance.

    @param State  A pointer to the state information on the
                  pointer device.

    @retval  EFI_UNSUPPORTED    No original GetState call
    @retval  Status             From original GetState call
    @retval  EFI_SUCCESS        Succeed to rotate the state or 
                                    from original GetState call
    @retval  EFI_PROTOCOL_ERROR Mode field from protocol is invalid
**/
EFI_STATUS
EFIAPI
AbsolutePointerRotationGetState (
  EFI_ABSOLUTE_POINTER_PROTOCOL  *This,
  EFI_ABSOLUTE_POINTER_STATE     *State
)
{
    EFI_STATUS Status;

    if (!gAbsolutePointerInfo) return EFI_UNSUPPORTED;

    if((Policy.Direction == RIGHT_ROTATION ) || (Policy.Direction == LEFT_ROTATION)) {
        pBS->CopyMem(This->Mode, &gAbsolutePointerInfo->OrgMode, sizeof(EFI_ABSOLUTE_POINTER_MODE) );
    }
    Status = gAbsolutePointerInfo->OrgGetState(This, State);
    if (EFI_ERROR(Status)) return Status;

    if (!This->Mode) return EFI_PROTOCOL_ERROR;

    if ((This->Mode->AbsoluteMaxY > This->Mode->AbsoluteMinY)
            && (This->Mode->AbsoluteMaxX > This->Mode->AbsoluteMinX))
    {
        UINT64 NewX;
        UINT64 NewY;

        if (Policy.Direction == RIGHT_ROTATION)
        {
            NewX = State->CurrentY;
            NewY = This->Mode->AbsoluteMaxX - State->CurrentX;
        }
        else if (Policy.Direction == LEFT_ROTATION)
        {
            NewY = State->CurrentX;
            NewX = This->Mode->AbsoluteMaxY - State->CurrentY;
        }
        else { // REVERSION
            NewX = This->Mode->AbsoluteMaxX - State->CurrentX;
            NewY = This->Mode->AbsoluteMaxY - State->CurrentY;
        }

        // Update AbsMaxX and AbsMaxY for MouseDriver calculation
        if((Policy.Direction == RIGHT_ROTATION ) || (Policy.Direction == LEFT_ROTATION)) {
            This->Mode->AbsoluteMaxX = gAbsolutePointerInfo->OrgMode.AbsoluteMaxY;
            This->Mode->AbsoluteMinX = gAbsolutePointerInfo->OrgMode.AbsoluteMinY;
            This->Mode->AbsoluteMaxY = gAbsolutePointerInfo->OrgMode.AbsoluteMaxX;
            This->Mode->AbsoluteMinY = gAbsolutePointerInfo->OrgMode.AbsoluteMinX;
        }
        State->CurrentX = NewX;
        State->CurrentY = NewY;
    }

    return EFI_SUCCESS;
}

/**
    AbsolutePointer notification callback.

    @param  Event
    @param  Context

    @retval  EFI_STATUS
**/
VOID
AbsolutePointerNotification (
    IN  EFI_EVENT   Event,
    IN  VOID        *Context)
{
    EFI_ABSOLUTE_POINTER_PROTOCOL *AbsolutePointer;
    EFI_STATUS      Status;
    EFI_HANDLE      AbsolutePointerHandle;
    EFI_HANDLE      *Handles;
    UINTN           HandleCount;

    // Locate the handle based on the registration
    Status = pBS->LocateHandleBuffer(
                     ByRegisterNotify,
                     NULL,
                     Registration,
                     &HandleCount,
                     &Handles);
    if (EFI_ERROR(Status)) return;

    if (Handles[0] != pST->ConsoleInHandle) return;
     
    AbsolutePointerHandle = Handles[0];
    pBS->FreePool(Handles);

    Status = pBS->HandleProtocol( AbsolutePointerHandle, &gEfiAbsolutePointerProtocolGuid, (VOID**)&AbsolutePointer);
    if (EFI_ERROR(Status)) return;
    
    if (gAbsolutePointerInfo)
        FreePool((VOID*)gAbsolutePointerInfo);

    gAbsolutePointerInfo = AllocateZeroPool(sizeof(ABSOLUTE_POINTER_INFO));
    if (!gAbsolutePointerInfo)
    {
        DEBUG((EFI_D_ERROR, "[AbsolutePointerRotation]: Out of resources for AbsolutePointerInfo\n"));
        gAbsolutePointerInfo = NULL;
        return;
    }

    gAbsolutePointerInfo->AbsolutePointer = AbsolutePointer;
    gAbsolutePointerInfo->Handle = AbsolutePointerHandle;
    gAbsolutePointerInfo->OrgGetState = AbsolutePointer->GetState;
    // gAbsolutePointerInfo->OrgMode that used and initialized by AbsolutePointerRotationGetState call.

    if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION)
    {
        pBS->CopyMem(&gAbsolutePointerInfo->OrgMode, AbsolutePointer->Mode, sizeof(EFI_ABSOLUTE_POINTER_MODE));
    }

    AbsolutePointer->GetState = AbsolutePointerRotationGetState;
}

/**
    Function to swap back to original absolute pointer for OS.

    @param  Event
    @param  Context

    @retval VOID

**/
VOID
SwapBackAbsolutePointer(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_ABSOLUTE_POINTER_PROTOCOL *AbsolutePointer;

    if (!gAbsolutePointerInfo) return;

    AbsolutePointer = gAbsolutePointerInfo->AbsolutePointer;
    if (!AbsolutePointer) return;

    AbsolutePointer->GetState = gAbsolutePointerInfo->OrgGetState;

    if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION)
    {
        //
        //  Mode did not change
        //
        if (AbsolutePointer->Mode->AbsoluteMaxX == gAbsolutePointerInfo->OrgMode.AbsoluteMaxY
                && AbsolutePointer->Mode->AbsoluteMaxY == gAbsolutePointerInfo->OrgMode.AbsoluteMaxX)
        {
            pBS->CopyMem(AbsolutePointer->Mode, &gAbsolutePointerInfo->OrgMode, sizeof(EFI_ABSOLUTE_POINTER_MODE));
        }
    }
}

/**
    Function to swap the absolute pointer for SHELL.

    @param  Event
    @param  Context

    @retval VOID

**/
VOID
SwapAbsolutePointer(
    IN EFI_EVENT    Event,
    IN VOID         *Context
)
{
    EFI_ABSOLUTE_POINTER_PROTOCOL *AbsolutePointer;

    if (!gAbsolutePointerInfo) return;

    AbsolutePointer = gAbsolutePointerInfo->AbsolutePointer;
    if (!AbsolutePointer) return;

    AbsolutePointer->GetState = AbsolutePointerRotationGetState;
    if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION)
    {
        pBS->CopyMem(&gAbsolutePointerInfo->OrgMode, AbsolutePointer->Mode, sizeof(EFI_ABSOLUTE_POINTER_MODE));
    }
}

#define AMITSE_EVENT_AFTER_BOOT_GUID \
  {0x8c12a959, 0x70bc, 0x4362, 0xb4, 0x37, 0xb8, 0x05, 0x14, 0xa1, 0x91, 0x6e}
/**
    Absolute pointer rotation entry point

    @param  ImageHandle
    @param  SystemTable

    @retval  EFI_STATUS
**/
EFI_STATUS
AbsolutePointerRotationEntryPoint(
    EFI_HANDLE ImageHandle,
    EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS  Status = EFI_SUCCESS;
    EFI_EVENT   Event;
    EFI_EVENT   ProtocolCallbackEvent;
    VOID        *ProtocolNotifyRegistration;
    EFI_GUID    EfiShellInterfaceGuid = EFI_SHELL_PROTOCOL_GUID;
    EFI_GUID    EfiShell20InterfaceGuid = EFI_SHELL2_0_FILE_GUID;
    static      BOOLEAN Guard = FALSE;
    EFI_GUID    AfterBootGuid = AMITSE_EVENT_AFTER_BOOT_GUID; 

    InitAmiLib(ImageHandle, SystemTable);
    DEBUG((EFI_D_INFO, "[AbsolutePointerRotation] Entry Point.\n"));
    if (!Guard) 
    {
        EFI_GUID AbsolutePointerRotationGuid = SCREEN_ROTATION_GUID;
        UINTN Size = sizeof(SCREEN_ROTATION_POLICY);

        Status = pRS->GetVariable(L"ScreenRotationPolicy",
                                  &AbsolutePointerRotationGuid,
                                  NULL,
                                  &Size,
                                  &Policy);
        if (!EFI_ERROR(Status)) Guard = TRUE;
    }
    if (Policy.Direction != NORMAL) 
    {
        // Create event
        Status = pBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                  TPL_CALLBACK,
                                  AbsolutePointerNotification,
                                  NULL,
                                  &Event );
        if (EFI_ERROR(Status)) return Status;
        // Register a notification when the AbsolutePointer is installed
        Status = pBS->RegisterProtocolNotify(&gEfiAbsolutePointerProtocolGuid,
                                             Event,
                                             &Registration);
        if (EFI_ERROR(Status)) 
        {
            DEBUG((EFI_D_ERROR, "[AbsolutePointerRotation] RegisterProtocolNotify status = %r.\n", Status));
            return Status;
        }
        // Create event
        Status = pBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                  TPL_CALLBACK,
                                  SwapAbsolutePointer,
                                  NULL,
                                  &ProtocolCallbackEvent );

        if (!EFI_ERROR(Status))
        {
            Status = pBS->RegisterProtocolNotify(&AfterBootGuid,
                                                ProtocolCallbackEvent,
                                                &ProtocolNotifyRegistration);
        }
        
        if (Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION) 
        {
            // Register a callback function before boot.
            Status = RegisterProtocolCallback(&gAmiTseEventBeforeBootGuid,
                                              SwapBackAbsolutePointer,
                                              NULL,
                                              &ProtocolCallbackEvent,
                                              &ProtocolNotifyRegistration);
            if (EFI_ERROR(Status)) 
            {
                DEBUG((EFI_D_ERROR, "[AbsolutePointerRotation] RegisterProtocolCallback before boot status = %r.\n", Status));
                return Status;
            }
            // Register a callback function when entering SHELL 1.0.
            Status = RegisterProtocolCallback(&EfiShellInterfaceGuid,
                                              SwapAbsolutePointer,
                                              NULL,
                                              &ProtocolCallbackEvent,
                                              &ProtocolNotifyRegistration);
            if (EFI_ERROR(Status)) 
            {
                DEBUG((EFI_D_ERROR, "[AbsolutePointerRotation] RegisterProtocolCallback for SHELL 1.0 status = %r.\n", Status));
                return Status;
            }

            // Register a callback function when entering SHELL 2.0.
            Status = RegisterProtocolCallback(&EfiShell20InterfaceGuid,
                                              SwapAbsolutePointer,
                                              NULL,
                                              &ProtocolCallbackEvent,
                                              &ProtocolNotifyRegistration);
            if (EFI_ERROR(Status)) 
            {
                DEBUG((EFI_D_ERROR, "[AbsolutePointerRotation] RegisterProtocolCallback for SHELL 2.0 status = %r.\n", Status));
                return Status;
            }
        } // Policy.Direction == RIGHT_ROTATION || Policy.Direction == LEFT_ROTATION
    } // Policy.Direction != NORMAL

    return Status;
}
