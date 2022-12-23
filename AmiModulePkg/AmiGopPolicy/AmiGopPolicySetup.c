//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiGopPolicySetup.c
    AmiGopPolicy Setup Routines.

*/

//----------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Pci.h>
#include <Setup.h>
#include <Token.h>
#include "AmiGopPolicy.h"
#include <AmiGopPolicyLinks.h>

#include <Protocol/ComponentName.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/EdidDiscovered.h>
#include <Protocol/PciIo.h>
#include <Library/PrintLib.h>

//----------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

typedef EFI_STATUS (OEM_GOP_DEVICE_CHECK) (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo
);

typedef EFI_STATUS (OEM_GOP_SWITCH_HOOK) (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  SETUP_DATA                  *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath
);

// Function Prototype(s)

BOOLEAN GetDriverName (
    IN  EFI_HANDLE  DriverBindingHandle,
    OUT CHAR16      **String
);

BOOLEAN GetDeviceName (
    IN  EFI_HANDLE  DriverBindingHandle,
    IN  EFI_HANDLE  ControllerHandle,
    IN  EFI_HANDLE  ChildControllerHandle,
    OUT CHAR16      **String
);

EFI_STATUS GetDriverBindingHandle (
    IN  EFI_HANDLE  ControllerHandle,
    OUT EFI_HANDLE  *DriverBindingHandle
);

EFI_STATUS GetDriverHandleBuffer (
    IN  EFI_HANDLE  Controller,
    OUT UINTN       *DriverHandleCount,
    OUT EFI_HANDLE  **DriverHandleBuffer
);

EFI_STATUS GetDeviceHandlesManagedByDriver (
    IN  EFI_HANDLE  DriverBindingHandle,
    OUT UINTN       *ControllerHandleCount,
    OUT EFI_HANDLE  **ControllerHandleBuffer
);

EFI_STATUS GetChildDeviceHandlesManagedByDriver (
    IN  EFI_HANDLE  DriverBindingHandle,
    IN  EFI_HANDLE  ControllerHandle,
    OUT UINTN       *ChildControllerHandleCount,
    OUT EFI_HANDLE  **ChildControllerHandleBuffer
);

EFI_STATUS GetOutputDeviceHandlesManagedByDriver (
    IN  EFI_HANDLE  DriverBindingHandle,
    IN  EFI_HANDLE  ControllerHandle,
    OUT UINTN       *OutputHandleCount,
    OUT EFI_HANDLE  **OutputHandleBuffer
);

EFI_STATUS ConnectGopDevicePath (
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  EFI_DEVICE_PATH_PROTOCOL  *pPath );

EFI_STATUS AmiGopDeviceCheck (
    IN  EFI_HANDLE                ControllerHandle,
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL       *PciIo
);

EFI_STATUS AmiDefaultGopDeviceCheck (
    IN  EFI_HANDLE                ControllerHandle,
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL       *PciIo );

EFI_STATUS AmiGopSwitchHook (
    IN  EFI_HANDLE                ControllerHandle, 
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  SETUP_DATA                *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL  *DevicePath
);

EFI_STATUS AmiDefaultGopSwitchFunction (
    IN  EFI_HANDLE                ControllerHandle,
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  SETUP_DATA                *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL  *DevicePath );

//----------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------
// Variable Declaration(s)

T_ITEM_LIST OutputHndList = { 0, 0, NULL };

UINT16  sDeviceName[] = { 
        STRING_TOKEN(STR_GOP_DEVICE_NAME_0),
        STRING_TOKEN(STR_GOP_DEVICE_NAME_1),
        STRING_TOKEN(STR_GOP_DEVICE_NAME_2),
        STRING_TOKEN(STR_GOP_DEVICE_NAME_3),
        };

UINT16  sDriverName[] = { 
        STRING_TOKEN(STR_GOP_DRIVER_NAME_0),
        STRING_TOKEN(STR_GOP_DRIVER_NAME_1),
        STRING_TOKEN(STR_GOP_DRIVER_NAME_2),
        STRING_TOKEN(STR_GOP_DRIVER_NAME_3),
        };

UINT16  sOutputName[] = {
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_0),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_1),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_2),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_3),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_4),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_5),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_6),
        STRING_TOKEN(STR_GOP_OUTPUT_NAME_7)
        };

UINTN   gSelectIndex = 0;
// GUID Definition(s)

static EFI_GUID gAmiGopPolicyVariableGuid = AMI_GOP_POLICY_VARIABLE_GUID;    
static EFI_GUID gSetupGuid = SETUP_GUID;

static EFI_GUID gAmiCsmThunkDriverGuid = { 0x2362ea9c, 0x84e5, 0x4dff, { 0x83, 0xbc, 0xb5, 0xac, 0xec, 0xb5, 0x7c, 0xbb } };

// Protocol Definition(s)

// External Declaration(s)

extern OEM_GOP_DEVICE_CHECK OEM_GOP_DEVICE_CHECK_LIST EndOfOemGopDeviceCheckList;
extern OEM_GOP_SWITCH_HOOK  OEM_GOP_SWITCH_HOOK_LIST  EndOfOemGopSwitchHookList;

// Function Definition(s)

OEM_GOP_DEVICE_CHECK*   OemGopDeviceCheckList[] = {OEM_GOP_DEVICE_CHECK_LIST NULL};
OEM_GOP_SWITCH_HOOK*    OemGopSwitchHookList[] = {OEM_GOP_SWITCH_HOOK_LIST NULL};


/**
    Initializes AmiGopPolicy Setup String

    @param HiiHandle - Handle to HII database
    @param Class - Indicates the setup class

    @retval VOID

    @note  None.

**/

VOID
InitAmiGopPolicyStrings (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{
    EFI_STATUS                  Status = EFI_SUCCESS;
    UINTN                       VariableSize = 0;
    AMI_GOP_POLICY_SETUP_DATA   AmiGopPolicySetupData;
    UINTN                       ControllerHandleCount = 0;
    EFI_HANDLE                  *ControllerHandleBuffer = NULL;
    EFI_HANDLE                  ControllerHandle;
    UINTN                       ControllerHandleIndex;
    EFI_HANDLE                  DriverBindingHandle;
    EFI_PCI_IO_PROTOCOL         *PciIo;
    UINTN                       ChildHandleCount = 0;
    EFI_HANDLE                  *ChildHandleBuffer = NULL;
    EFI_HANDLE                  ChildHandle;
    UINTN                       ChildHandleIndex = 0;
    EFI_DEVICE_PATH_PROTOCOL    *ChildHandleDp;
    CHAR16                      ChildHandleDpVar[0x40];
    EFI_DEVICE_PATH_PROTOCOL    *AmiGopOutputDp = NULL;
    CHAR16                      *String = NULL;
    UINTN                       Index = 0;

    if (Class != ADVANCED_FORM_SET_CLASS) return;

    // Save default AmiGopPolicySetupData on memory.
    AmiGopPolicySetupData.GopDeviceCount = 0;
    AmiGopPolicySetupData.GopOutputCount = 0;
    VariableSize = sizeof(AMI_GOP_POLICY_SETUP_DATA);
    Status = pRS->SetVariable (
                  L"AmiGopPolicySetupData",
                  &gAmiGopPolicyVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &AmiGopPolicySetupData );
    if (EFI_ERROR(Status)) return;
    //
    // Get all drivers handles which has PCI IO Protocol
    //
    Status = pBS->LocateHandleBuffer(
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &ControllerHandleCount,
                  &ControllerHandleBuffer);
    if (EFI_ERROR(Status)) return;

    for (ControllerHandleIndex = 0; ControllerHandleIndex < ControllerHandleCount; ControllerHandleIndex++) {
        ControllerHandle = ControllerHandleBuffer[ControllerHandleIndex];
        Status = pBS->HandleProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, (VOID**)&PciIo);
        if (EFI_ERROR(Status)) continue;

        Status = GetDriverBindingHandle (ControllerHandle, &DriverBindingHandle);
        if (EFI_ERROR(Status)) continue;

        Status = AmiGopDeviceCheck (ControllerHandle, DriverBindingHandle, PciIo);
        if (EFI_ERROR(Status)) continue;

        if (GetDeviceName(DriverBindingHandle, ControllerHandle, NULL, &String)) {
            InitString(HiiHandle, sDeviceName[Index], L"%s", String);
            if(String)
                pBS->FreePool(String);
        }

        if (GetDriverName(DriverBindingHandle, &String)) {
            InitString(HiiHandle, sDriverName[Index], L"%s", String);
            if(String)
                pBS->FreePool(String);
        }
        Index ++;
        Status = GetOutputDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &ChildHandleCount, &ChildHandleBuffer);
        if (!EFI_ERROR(Status)) {
            VariableSize = 0;
            Status = GetEfiVariable (
                     L"AmiGopOutputDp",
                     &gAmiGopPolicyVariableGuid,
                     NULL,
                     &VariableSize,
                     (VOID**)&AmiGopOutputDp);
            for (ChildHandleIndex = 0; ChildHandleIndex < ChildHandleCount; ChildHandleIndex++) {
                ChildHandle = ChildHandleBuffer[ChildHandleIndex];
                if (GetDeviceName(DriverBindingHandle, ControllerHandle, ChildHandle, &String)) {
                    Status = pBS->OpenProtocol (
                            ChildHandle,
                            &gEfiDevicePathProtocolGuid,
                            (VOID**)&ChildHandleDp,
                            NULL,
                            NULL,
                            EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
                    if (!EFI_ERROR(Status)) {
                        UnicodeSPrint(ChildHandleDpVar, 0x40, L"ChildHandleDpVar%01x", ChildHandleIndex);
                        pRS->SetVariable (
                                ChildHandleDpVar,
                                &gAmiGopPolicyVariableGuid,
                                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                                DPLength (ChildHandleDp),
                                ChildHandleDp );
                        if (AmiGopOutputDp != NULL) {
                            if (MemCmp (AmiGopOutputDp, ChildHandleDp, DPLength(ChildHandleDp)) == 0) {
                                gSelectIndex = ChildHandleIndex;
                            }
                        }
                    }
                    InitString(HiiHandle, sOutputName[ChildHandleIndex], L"%s", String);
                    if(String)
                        pBS->FreePool(String);
                }
            }
            break;
        }

        
    }

    // Update Gop Output Device Count
    // Save AmiGopPolicySetupData on memory.
    AmiGopPolicySetupData.GopDeviceCount = (UINT8)Index;
    AmiGopPolicySetupData.GopOutputCount = (UINT8)ChildHandleIndex;
    VariableSize = sizeof(AMI_GOP_POLICY_SETUP_DATA);
    pRS->SetVariable (
         L"AmiGopPolicySetupData",
         &gAmiGopPolicyVariableGuid,
         EFI_VARIABLE_BOOTSERVICE_ACCESS,
         VariableSize,
         &AmiGopPolicySetupData );

    if (ControllerHandleBuffer != NULL) pBS->FreePool(ControllerHandleBuffer);
    if (ChildHandleBuffer != NULL) pBS->FreePool(ChildHandleBuffer);
    if (AmiGopOutputDp != NULL) pBS->FreePool(AmiGopOutputDp);
}

/**
    AmiGopSwitchFunction Callback

    @param HiiHandle - Handle to HII database
    @param Class - Indicates the setup class
    @param SubClass - Indicates the setup sub class
    @param Key - unique value that defines the type of data to expect in the callback function.

    @retval EFI_SUCCESS - AmiGopSwitchFunction Callback function complete in SETUP

    @note  None.

**/

EFI_STATUS
AmiGopSwitchCallback (
    IN EFI_HII_HANDLE           HiiHandle, 
    IN UINT16                   Class, 
    IN UINT16                   SubClass, 
    IN UINT16                   Key )
{
    EFI_STATUS                  Status;
    SETUP_DATA                  *SetupData = NULL;
    UINTN                       SetupSize = sizeof(SETUP_DATA);
    CALLBACK_PARAMETERS         *CallbackParameters = NULL;

    UINTN                       ControllerHandleCount = 0;
    EFI_HANDLE                  *ControllerHandleBuffer = NULL;
    EFI_HANDLE                  ControllerHandle;
    UINTN                       ControllerHandleIndex;

    EFI_PCI_IO_PROTOCOL         *PciIo;

    EFI_HANDLE                  DriverBindingHandle;
    EFI_DRIVER_BINDING_PROTOCOL *DriverBinding = NULL;

    UINTN                       ChildHandleCount = 0;
    EFI_HANDLE                  *ChildHandleBuffer = NULL;
    UINTN                       ChildHandleIndex;
    CHAR16                      ChildHandleDpVar[0x40];

    EFI_DEVICE_PATH_PROTOCOL    *GopDevicePath = NULL;
    UINTN                       GopDevicePathLength = 0;

    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop = NULL;
    UINTN                       HorizontalResolution = 0;
    UINTN                       VerticalResolution = 0;
    UINTN                       GopHandleCount = 0;
    EFI_HANDLE                  *GopHandleBuffer = NULL;
    UINTN                       GopHandleIndex;
    UINTN                       SizeOfInfo = 0;
    UINT32                      Mode;
    UINT32                      MaxMode = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info = NULL;
    static BOOLEAN Changed = FALSE;
    //
    // Get Setup Buffer
    //
    CallbackParameters = GetCallbackParameters();
    if(CallbackParameters->Action == EFI_BROWSER_ACTION_RETRIEVE && !Changed) {
        CallbackParameters->Value->u8 = (UINT8)gSelectIndex;
        CallbackParameters->ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;
        Changed = TRUE;
    }
    if (CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGED) return EFI_UNSUPPORTED;

    Status = pBS->AllocatePool (EfiBootServicesData, SetupSize, (VOID**)&SetupData);
    if(EFI_ERROR(Status)) return Status;

    Status = HiiLibGetBrowserData (&SetupSize, SetupData, &gSetupGuid, L"Setup");
    if(EFI_ERROR(Status)) return Status;

    //
    // Get all drivers handles which has PCI IO Protocol
    //
    Status = pBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &ControllerHandleCount,
                  &ControllerHandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (ControllerHandleIndex = 0; ControllerHandleIndex < ControllerHandleCount; ControllerHandleIndex++) {
        ControllerHandle = ControllerHandleBuffer[ControllerHandleIndex];
        Status = pBS->HandleProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, (VOID**)&PciIo);
        if (EFI_ERROR(Status)) continue;

        //
        // Get Driver Binding Protocol for this VGA
        //
        Status = GetDriverBindingHandle (ControllerHandle, &DriverBindingHandle);
        if (EFI_ERROR(Status)) continue;

        Status = AmiGopDeviceCheck (ControllerHandle, DriverBindingHandle, PciIo);
        if (EFI_ERROR(Status)) continue;

        Status = pBS->OpenProtocol(
                      DriverBindingHandle,
                      &gEfiDriverBindingProtocolGuid,
                      (VOID**)&DriverBinding,
                      NULL,
                      NULL,
                      EFI_OPEN_PROTOCOL_GET_PROTOCOL);
        if (EFI_ERROR(Status)) continue;

        //
        // Find out Current GOP Output Mode
        //
        if (!EFI_ERROR(GetOutputDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &ChildHandleCount, &ChildHandleBuffer))) {
            for (ChildHandleIndex = 0; ChildHandleIndex < ChildHandleCount; ChildHandleIndex++) {
                Status = pBS->OpenProtocol (
                              ChildHandleBuffer[ChildHandleIndex],
                              &gEfiGraphicsOutputProtocolGuid,
                              (VOID**)&Gop,
                              NULL,
                              NULL,
                              EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                if (!EFI_ERROR(Status)) {
                    HorizontalResolution = Gop->Mode->Info->HorizontalResolution;
                    VerticalResolution = Gop->Mode->Info->VerticalResolution;
                    break;
                }
            }
        }

        //
        // Get User Selected Gop Output Handle.
        //
        UnicodeSPrint(ChildHandleDpVar, 0x40, L"ChildHandleDpVar%01x", SetupData->GopOutputSelect);
        GopDevicePathLength = 0;
        Status = GetEfiVariable (
                 ChildHandleDpVar,
                 &gAmiGopPolicyVariableGuid,
                 NULL,
                 &GopDevicePathLength,
                 (VOID**)&GopDevicePath);
        if (EFI_ERROR(Status)) continue;
        //
        // Save AmiGop Outut Device path for next boot
        //
        Status = pRS->SetVariable (
                      L"AmiGopOutputDp",
                      &gAmiGopPolicyVariableGuid,
                      EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                      DPLength(GopDevicePath),
                      GopDevicePath);
        
        Status = AmiGopSwitchHook (ControllerHandle, DriverBindingHandle, SetupData, GopDevicePath);
        if (!EFI_ERROR(Status)) {
            //
            // Set GOP Output Mode
            //
            Status = GetOutputDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &GopHandleCount, &GopHandleBuffer);
            if (!EFI_ERROR(Status)) {
                for (GopHandleIndex = 0; GopHandleIndex < GopHandleCount; GopHandleIndex++) {
                    Status = pBS->OpenProtocol (
                                  GopHandleBuffer[GopHandleIndex],
                                  &gEfiGraphicsOutputProtocolGuid,
                                  (VOID**)&Gop,
                                  NULL,
                                  NULL,
                                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
                    if (!EFI_ERROR(Status)) {
                        if ((HorizontalResolution == Gop->Mode->Info->HorizontalResolution) &&
                            (VerticalResolution == Gop->Mode->Info->VerticalResolution))
                            break;
                        MaxMode = Gop->Mode->MaxMode;
                        for (Mode = 0; Mode <= MaxMode; Mode++) {
                            if (!EFI_ERROR (Gop->QueryMode (Gop, Mode, &SizeOfInfo, &Info))) {
                                if ((HorizontalResolution == Info->HorizontalResolution) &&
                                    (VerticalResolution == Info->VerticalResolution)) {
                                    Status = Gop->SetMode (Gop, Mode);
                                    if (!EFI_ERROR(Status)) break;
                                }
                            }
                        }
                    }
                }
            }
        }
        else {
            //
            // delete AmiGop Outut Device path for next boot
            //
            Status = pRS->SetVariable (
                          L"AmiGopOutputDp",
                          &gAmiGopPolicyVariableGuid,
                          0,
                          0,
                          NULL);
        }
    }

    if (SetupData != NULL) pBS->FreePool(SetupData);
    if (ControllerHandleBuffer != NULL) pBS->FreePool(ControllerHandleBuffer);
    if (ChildHandleBuffer != NULL) pBS->FreePool(ChildHandleBuffer);
    if (GopDevicePath != NULL) pBS->FreePool(GopDevicePath);
    if (GopHandleBuffer != NULL) pBS->FreePool(GopHandleBuffer);

    return Status;
}

/**
    Invoke AmiGopDeviceCheck eLink

    @param ControllerHandle - the device controller handle be opened by its child device.
    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param *PciIo - the PciIo protocol which was installed on ControllerHandle.

    @retval EFI_SUCCESS - This VGA supports Display Switching function.

    @note  Display Switching function may failed because the GOP
           Driver is not supporting. Please contact VGA vendor to
           check for this function supporting.

**/

EFI_STATUS
AmiGopDeviceCheck (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       i;

    for (i = 0; OemGopDeviceCheckList[i] != NULL; i++) {
        Status = OemGopDeviceCheckList[i] (ControllerHandle, DriverBindingHandle, PciIo);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}

/**
    Sample code for check if this VGA supports Display Switching function.

    @param ControllerHandle - the device controller handle be opened by its child device.
    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param *PciIo - the PciIo protocol which was installed on ControllerHandle.

    @retval EFI_SUCCESS - This VGA supports Display Switching function.

    @note  Display Switching function may failed because the GOP
           Driver is not supporting. Please contact VGA vendor to
           check for this function supporting.

**/

EFI_STATUS
AmiDefaultGopDeviceCheck (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  EFI_PCI_IO_PROTOCOL         *PciIo )
{
    EFI_STATUS  Status;
    UINT8       PciClassCode;

    if (!PciIo) return EFI_INVALID_PARAMETER;

    // Check if this is ThunkDriver
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gAmiCsmThunkDriverGuid,
                  NULL,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
    if (!EFI_ERROR(Status)) return EFI_UNSUPPORTED;

    // Check if this is VGA controller
    Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint8, PCI_BCC, 1, &PciClassCode);
    if (EFI_ERROR(Status) || (PciClassCode != PCI_CL_DISPLAY)) return EFI_UNSUPPORTED;

    return EFI_SUCCESS;
}

/**
    Invoke AmiGopSwitchHook eLink

    @param ControllerHandle - the device controller handle be opened by its child device.
    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param *SetupData - the pointer to a setup data buffer for reference.
    @param *DevicePath - the pointer to a output device path node to initialize.

    @retval EFI_SUCCESS - VGA Display Switching function Success.

    @note  None.

**/

EFI_STATUS
AmiGopSwitchHook (
    IN  EFI_HANDLE                  ControllerHandle,
    IN  EFI_HANDLE                  DriverBindingHandle,
    IN  SETUP_DATA                  *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL    *DevicePath )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       i;

    for (i = 0; OemGopSwitchHookList[i] != NULL; i++) {
        Status = OemGopSwitchHookList[i] (ControllerHandle, DriverBindingHandle, SetupData, DevicePath);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}

/**
    Sample code for VGA Display Switching process.

    @param ControllerHandle - the device controller handle be opened by its child device.
    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param *SetupData - the pointer to a setup data buffer for reference.
    @param *DevicePath - the pointer to a output device path node to initialize.

    @retval EFI_SUCCESS - VGA Display Switching function Success.

    @note  None.

**/

EFI_STATUS
AmiDefaultGopSwitchFunction (
    IN  EFI_HANDLE                ControllerHandle,
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  SETUP_DATA                *SetupData,
    IN  EFI_DEVICE_PATH_PROTOCOL  *DevicePath )
{
    EFI_STATUS  Status;

    pBS->DisconnectController (ControllerHandle, NULL, NULL);
    Status = ConnectGopDevicePath(DriverBindingHandle, DevicePath);

    return Status;
}

/**
    Connect specific output device by input device path.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param *pPath - the pointer to a output device path node to initialize.

    @retval EFI_SUCCESS - Connect device Success.

    @note  None.

**/

EFI_STATUS
ConnectGopDevicePath (
    IN  EFI_HANDLE                DriverBindingHandle,
    IN  EFI_DEVICE_PATH_PROTOCOL  *pPath )
{
    EFI_HANDLE Handle;
    EFI_STATUS Status;
    EFI_STATUS ConnectStatus = EFI_UNSUPPORTED;
    UINTN      DpLength = 0;

    if (pPath == NULL) return EFI_INVALID_PARAMETER;
    while (DpLength < DPLength(pPath)) {
        EFI_DEVICE_PATH_PROTOCOL *pLastPath=NULL, *pFirstNode = pPath;
        if (isEndNode(pPath)) {
            if (pPath->SubType == END_ENTIRE_SUBTYPE) break;
            pPath++;
            continue;
        }
        while(TRUE){
            EFI_DEVICE_PATH_PROTOCOL *Dp;
            UINT8 SubType;

            pPath = pFirstNode;

            //LocateDevicePath can not work with multi-instance device paths.
            //Prepare single instance device path and call LocateDevicePath
            Dp = DPGetEndNode(pPath);
            if(Dp == NULL)
                break;
            SubType = Dp->SubType;
            Dp->SubType=END_ENTIRE_SUBTYPE;
            Status = pBS->LocateDevicePath(&gEfiDevicePathProtocolGuid, &pPath, &Handle);
            Dp->SubType=SubType;
            if (EFI_ERROR(Status)) break;

            if (pPath==pLastPath) break;
            pLastPath = pPath;
            ConnectStatus = pBS->ConnectController(Handle, &DriverBindingHandle, pPath, TRUE);
            if (EFI_ERROR(ConnectStatus)) break;
            else return ConnectStatus;
        }
        while (!isEndNode(pPath)) {
            DpLength += NODE_LENGTH(pPath);
            pPath = NEXT_NODE(pPath);
        }
        DpLength += sizeof(EFI_DEVICE_PATH_PROTOCOL);
    }

    return ConnectStatus;
}

/**
    Get driver name by input driver handle.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param Length - Length of name to be copied to String including null.
    @param *String - Output string of driver name.

    @retval TRUE - Get driver name Success.
    @retval FALSE - Get driver name fail.

    @note  None.

**/

BOOLEAN
GetDriverName (
    IN  EFI_HANDLE  DriverBindingHandle,
    OUT CHAR16      **String )
{
    EFI_STATUS                      Status;
    CHAR16                          *DriverName;
    EFI_COMPONENT_NAME_PROTOCOL     *ComponentName;
    CHAR8                           *Lang = NULL;
    UINTN                           Length;

    //
    // Get driver name from UEFI 2.0 Component Name 2 protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetDriverName(ComponentName, LANGUAGE_CODE_ENGLISH, &DriverName);
        if (EFI_ERROR(Status)) {
            //
            // Driver does not support "en-us", try to get SupportedLanguages
            //
            Length = AsciiStrLen(ComponentName->SupportedLanguages) + 1;
            pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)&Lang);
            if (Lang != NULL) {
                CHAR8 *TempChar = NULL;
                AsciiStrCpyS(Lang, Length, ComponentName->SupportedLanguages);
                TempChar = AsciiStrStr(Lang, ";");
                if (TempChar != NULL) *TempChar = 0x0000;
                Status = ComponentName->GetDriverName(ComponentName, Lang, &DriverName);
                pBS->FreePool(Lang);
                Lang = NULL;
            }
        }
        if (!EFI_ERROR(Status)) {
            Length = StrnSizeS(DriverName, 50);
            pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)String);
            UnicodeSPrint(*String, Length, L"%S", DriverName);
            return TRUE;
        }
    }

    //
    // If it fails to get the driver name from Component Name protocol interface, we should fall back on
    // EFI 1.1 Component Name protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetDriverName(ComponentName, "eng", &DriverName);
        if (!EFI_ERROR(Status)) {
            Length = StrnSizeS(DriverName, 50);
            pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)String);
            UnicodeSPrint(*String, Length, L"%S", DriverName);
            return TRUE;
        }
    }

    return FALSE;
}

/**
    Get device name by input device handle.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param ControllerHandle - the device controller handle be opened by its child device.
    @param ChildControllerHandle - the handle of child controller.
    @param *String - Output string of device name.

    @retval TRUE - Get device name Success.
    @retval FALSE - Get device name fail.

    @note  None.

**/

BOOLEAN
GetDeviceName (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  IN  EFI_HANDLE  ChildControllerHandle,
  OUT CHAR16      **String )
{
    EFI_STATUS                      Status;
    CHAR16                          *DeviceName;
    EFI_COMPONENT_NAME_PROTOCOL     *ComponentName;
    CHAR8                           *Lang = NULL;
    UINTN                           Length;
    //
    // Get driver name from UEFI 2.0 Component Name 2 protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentName2ProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetControllerName(ComponentName, ControllerHandle, ChildControllerHandle, LANGUAGE_CODE_ENGLISH, &DeviceName);
        if (EFI_ERROR(Status)) {
            //
            // Driver does not support "en-us", try to get SupportedLanguages
            //
            Length = AsciiStrLen(ComponentName->SupportedLanguages) + 1;
            pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)&Lang);
            if (Lang != NULL) {
                CHAR8 *TempChar = NULL;
                AsciiStrCpyS(Lang, Length, ComponentName->SupportedLanguages);
                TempChar = AsciiStrStr(Lang, ";");
                if (TempChar != NULL) *TempChar = 0x0000;
                Status = ComponentName->GetControllerName(ComponentName, ControllerHandle, ChildControllerHandle, Lang, &DeviceName);
                pBS->FreePool(Lang);
                Lang = NULL;
            }
        }
        if (!EFI_ERROR(Status)) {
            Length = StrnSizeS(DeviceName, 50);
            pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)String);
            UnicodeSPrint(*String, Length, L"%S", DeviceName);
            return TRUE;
        }
    }

    //
    // If it fails to get the driver name from Component Name protocol interface, we should fall back on
    // EFI 1.1 Component Name protocol interface.
    //
    Status = pBS->OpenProtocol(
                  DriverBindingHandle,
                  &gEfiComponentNameProtocolGuid,
                  (VOID**)&ComponentName,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (!EFI_ERROR(Status)) {
        Status = ComponentName->GetControllerName(ComponentName, ControllerHandle, ChildControllerHandle, "eng", &DeviceName);
        if (!EFI_ERROR(Status)) {
            Length = StrnSizeS(DeviceName, 50);
            pBS->AllocatePool(EfiBootServicesData, Length, (VOID**)String);
            UnicodeSPrint(*String, Length, L"%S", DeviceName);
            return TRUE;
        }
    }

    return FALSE;
}

/**
    Get DriverBinding Handle by input device handle.

    @param ControllerHandle - the device controller handle be opened by its child device.
    @param *DriverBindingHandle - the handle of a driver which contains the binding protocol.

    @retval EFI_SUCCESS - DriverBinding handle found.

    @note  None.

**/

EFI_STATUS
GetDriverBindingHandle (
    IN  EFI_HANDLE  ControllerHandle,
    OUT EFI_HANDLE  *DriverBindingHandle )
{
    EFI_STATUS                          Status;
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;
    UINTN                               Index;

    Status = pBS->LocateHandleBuffer(
                  AllHandles,   
                  NULL,
                  NULL,
                  &HandleCount, 
                  &HandleBuffer);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        ProtocolGuidArray = NULL;
        Status = pBS->ProtocolsPerHandle(
                      HandleBuffer[HandleIndex], 
                      &ProtocolGuidArray, 
                      &ArrayCount);
        if (EFI_ERROR(Status)) continue;

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            Status = pBS->OpenProtocolInformation(
                          HandleBuffer[HandleIndex], 
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (EFI_ERROR(Status)) continue;

            for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                if (OpenInfo[OpenInfoIndex].ControllerHandle == ControllerHandle) {
                    if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                        for(Index = 0; Index < HandleCount; Index++) {
                            if(HandleBuffer[Index] == OpenInfo[OpenInfoIndex].AgentHandle) {
                                *DriverBindingHandle=HandleBuffer[Index];
                                pBS->FreePool(OpenInfo);
                                pBS->FreePool(ProtocolGuidArray);
                                pBS->FreePool(HandleBuffer);
                                return EFI_SUCCESS;
                            }
                        }
                    }
                }
            }
            if (OpenInfo != NULL) pBS->FreePool(OpenInfo);
        }
         if (ProtocolGuidArray != NULL) pBS->FreePool(ProtocolGuidArray);
    }
    if (HandleBuffer != NULL) pBS->FreePool(HandleBuffer);
    return EFI_NOT_FOUND;
}

/**
    Get all DriverBinding Handles were installed by a specific device handle.

    @param Controller - the device controller handle be opened by its child device.
    @param *DriverHandleCount - the number of available driver handles returned in DriverHandleBuffer
    @param **DriverHandleBuffer - a pointer to the buffer to return the array of driver handles.

    @retval EFI_STATUS

    @note  If returned status is not succeful or find no available driver, the **DriverHandleBuffer will be NULL.

**/

EFI_STATUS
GetDriverHandleBuffer (
    IN  EFI_HANDLE                      Controller,
    OUT UINTN                           *DriverHandleCount,
    OUT EFI_HANDLE                      **DriverHandleBuffer )
{
    EFI_STATUS                          Status;
    UINTN                               HandleCount;
    BOOLEAN                             *HandleBufferMap;
    EFI_HANDLE                          *HandleBuffer;
    UINTN                               HandleIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;
    UINTN                               Index;
    UINTN                               AvailableIndex = 0;

    Status = pBS->LocateHandleBuffer(
                  AllHandles,   
                  NULL,
                  NULL,
                  &HandleCount, 
                  &HandleBuffer);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    HandleBufferMap = MallocZ (sizeof (BOOLEAN) * HandleCount);
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        HandleBufferMap[HandleIndex] = FALSE;
    }

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        ProtocolGuidArray = NULL;
        Status = pBS->ProtocolsPerHandle(
                      HandleBuffer[HandleIndex], 
                      &ProtocolGuidArray, 
                      &ArrayCount);
        if (EFI_ERROR(Status)) continue;

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            Status = pBS->OpenProtocolInformation(
                          HandleBuffer[HandleIndex], 
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (EFI_ERROR(Status)) continue;

            for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                if (OpenInfo[OpenInfoIndex].ControllerHandle == Controller) {
                    if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                        for (Index = 0; Index < HandleCount; Index++) {
                            if (HandleBuffer[Index] == OpenInfo[OpenInfoIndex].AgentHandle) {
                                HandleBufferMap[Index] = TRUE;
                                (*DriverHandleCount)++; 
                            }
                        }
                    }
                }
            }
            pBS->FreePool(OpenInfo);
        }
        pBS->FreePool(ProtocolGuidArray);
    }

    if (*DriverHandleCount > 0) {
        //
        // Copy the found device handle to returned buffer
        //
        *DriverHandleBuffer = MallocZ (sizeof (EFI_HANDLE) * (*DriverHandleCount));
        for (HandleIndex = 0, AvailableIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
            if (HandleBufferMap[HandleIndex]) {
                (*DriverHandleBuffer)[AvailableIndex] = HandleBuffer[HandleIndex];
                AvailableIndex++;
            }
        }
    }

    pBS->FreePool(HandleBuffer);

    if (*DriverHandleCount > 0)
        return EFI_SUCCESS;
    else
        return EFI_NOT_FOUND;
}

/**
    Get all device handles which are being opened by a specific driver.
    The rountine will allocate pool buffer for the found device handles,
    and it is the caller's responsibility to safe free the buffer.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param *ControllerHandleCount - the number of available device handles returned in ControllerHandleBuffer.
    @param **ControllerHandleBuffer - a pointer to the buffer to return the array of device handles.

    @retval EFI_STATUS.

    @note  If returned status is not succeful or find no available device, the *ControllerHandleBuffer will be NULL.

**/

EFI_STATUS
GetDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  OUT UINTN       *ControllerHandleCount,
  OUT EFI_HANDLE  **ControllerHandleBuffer )
{
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    BOOLEAN                             *HandleBufferMap;
    EFI_STATUS                          Status;
    UINTN                               HandleIndex;
    UINTN                               AvailableIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;

    *ControllerHandleCount  = 0;
    *ControllerHandleBuffer = NULL;
    HandleCount = 0;
    HandleBuffer = NULL;

    if (DriverBindingHandle == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Error;
    }

    //
    // Retrieve the list of all handles from the handle database
    //
    Status = pBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
    if (EFI_ERROR (Status)) goto Error;

    //
    //Create a map for HandleBuffer. If a handle in HandleBuffer is the wanted device handle, its map item is true.
    //
    HandleBufferMap = MallocZ (sizeof (BOOLEAN) * HandleCount);
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        HandleBufferMap[HandleIndex] = FALSE;
    }

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        //
        // Check if it is a device handle
        //
        Status = pBS->OpenProtocol (
                      HandleBuffer[HandleIndex],
                      &gEfiDevicePathProtocolGuid,
                      NULL,
                      NULL,
                      NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
        if (EFI_ERROR(Status)) continue;

        //
        // Retrieve the list of all the protocols on each handle
        //
        Status = pBS->ProtocolsPerHandle (
                      HandleBuffer[HandleIndex],
                      &ProtocolGuidArray,
                      &ArrayCount);

        if (!EFI_ERROR (Status)) {
            for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
                //
                // Retrieve the list of agents that have opened each protocol
                //
                Status = pBS->OpenProtocolInformation (
                              HandleBuffer[HandleIndex],
                              ProtocolGuidArray[ProtocolIndex],
                              &OpenInfo,
                              &OpenInfoCount);
                if (!EFI_ERROR (Status)) {
                    for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                        if (OpenInfo[OpenInfoIndex].AgentHandle == DriverBindingHandle) {
                            if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                                //
                                // HandleBufferMap[HandleIndex] is the wanted device handle, find it in the handlebuffer
                                // A bus driver maybe open a Controller with BY_DRIVER attribute for different protocol  many times,
                                //
                                HandleBufferMap[HandleIndex] = TRUE;
                            }
                        }
                    }
                    pBS->FreePool (OpenInfo);
                }
            }
        pBS->FreePool (ProtocolGuidArray);
        }
    }

    //
    // count how many device handles are found
    //
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        if (HandleBufferMap[HandleIndex]) {
            (*ControllerHandleCount)++;
        }
    }

    if (*ControllerHandleCount > 0) {
        //
        // Copy the found device handle to returned buffer
        //
        *ControllerHandleBuffer = MallocZ (sizeof (EFI_HANDLE) * (*ControllerHandleCount));
        for (HandleIndex = 0, AvailableIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
            if (HandleBufferMap[HandleIndex]) {
                (*ControllerHandleBuffer)[AvailableIndex] = HandleBuffer[HandleIndex];
                AvailableIndex++;
            }
        }
    }

    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return EFI_SUCCESS;

Error:

    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return Status;
}

/**
    Get all child device handles which are being opened by a specific driver.
    The rountine will allocate pool buffer for the found child device handles,
    and it is the caller's responsibility to safe free the buffer.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param ControllerHandle - the device controller handle be opened by its child device.
    @param *ChildControllerHandleCount - the number of available device handles returned in ControllerHandleBuffer.
    @param **ChildControllerHandleBuffer - a pointer to the buffer to return the array of child device handles.

    @retval EFI_STATUS.

    @note  If returned status is not succeful or find no available device, the *ChildControllerHandleBuffer will be NULL.

**/

EFI_STATUS
GetChildDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  OUT UINTN       *ChildControllerHandleCount,
  OUT EFI_HANDLE  **ChildControllerHandleBuffer )
{
    UINTN                               HandleCount;
    EFI_HANDLE                          *HandleBuffer;
    BOOLEAN                             *HandleBufferMap;
    EFI_STATUS                          Status;
    UINTN                               HandleIndex;
    UINTN                               AvailableIndex;
    EFI_GUID                            **ProtocolGuidArray;
    UINTN                               ArrayCount;
    UINTN                               ProtocolIndex;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY *OpenInfo;
    UINTN                               OpenInfoCount;
    UINTN                               OpenInfoIndex;

    *ChildControllerHandleCount  = 0;
    *ChildControllerHandleBuffer = NULL;
    HandleCount = 0;
    HandleBuffer = NULL;

    if ((DriverBindingHandle == NULL) || (ControllerHandle == NULL)) {
        Status = EFI_INVALID_PARAMETER;
        goto Error;
    }

    //
    // Retrieve the list of all handles from the handle database
    //
    Status = pBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer);
    if (EFI_ERROR(Status)) goto Error;

    //
    // Create a map for HandleBuffer. If a handle in HandleBuffer is the wanted device handle, its map item is true.
    //
    HandleBufferMap = MallocZ (sizeof (BOOLEAN) * HandleCount);
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        HandleBufferMap[HandleIndex] = FALSE;
    }

    //
    // Retrieve the list of all the protocols on each handle
    //
    Status = pBS->ProtocolsPerHandle (
                  ControllerHandle,
                  &ProtocolGuidArray,
                  &ArrayCount);
    if (!EFI_ERROR (Status)) {
        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            //
            // Retrieve the list of agents that have opened each protocol
            //
            Status = pBS->OpenProtocolInformation (
                          ControllerHandle,
                          ProtocolGuidArray[ProtocolIndex],
                          &OpenInfo,
                          &OpenInfoCount);
            if (!EFI_ERROR (Status)) {
                for (OpenInfoIndex = 0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
                    if (OpenInfo[OpenInfoIndex].AgentHandle == DriverBindingHandle) {
                        if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                            //
                            // OpenInfo[OpenInfoIndex].ControllerHandle is the wanted child device handle, find it in the handlebuffer
                            // A bus driver maybe open a Controller with BY_CHILD_CONTROLLER attribute for different protocol many times,
                            //
                            for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
                                if (OpenInfo[OpenInfoIndex].ControllerHandle == HandleBuffer[HandleIndex]) {
                                    HandleBufferMap[HandleIndex] = TRUE;
                                }
                            }
                        }
                    }
                }
            pBS->FreePool (OpenInfo);
            }
        }
        pBS->FreePool (ProtocolGuidArray);
    }

    //
    // count how many device handles are found
    //
    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        if (HandleBufferMap[HandleIndex]) {
            (*ChildControllerHandleCount)++;
        }
    }

    if (*ChildControllerHandleCount > 0) {
        //
        // Copy the found device handle to returned buffer
        //
        *ChildControllerHandleBuffer = MallocZ (sizeof (EFI_HANDLE) * (*ChildControllerHandleCount));
        for (HandleIndex = 0, AvailableIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
            if (HandleBufferMap[HandleIndex]) {
                (*ChildControllerHandleBuffer)[AvailableIndex] = HandleBuffer[HandleIndex];
                AvailableIndex++;
            }
        }
    }

    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return EFI_SUCCESS;

Error:
    if (HandleBuffer != NULL) pBS->FreePool (HandleBuffer);
    return Status;
}

/**
    Get all child device handles which have specific Protocol and produce by a specific driver.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol.
    @param ControllerHandle - the device controller handle be opened by its child device.

    @retval EFI_STATUS.

    @note  If returned status is not succeful or find no available device, the *OutputHndList will be NULL.

**/

EFI_STATUS
GetProtocolHandlesManagedByDriver (
  IN  EFI_HANDLE  DriverBindingHandle,
  IN  EFI_HANDLE  ControllerHandle,
  IN  EFI_GUID    Protocol )
{
    EFI_STATUS      Status;
    UINTN           ChildHandleCount = 0;
    EFI_HANDLE      *ChildHandleBuffer = NULL;
    UINTN           ChildHandleIndex = 0;
    UINT8           Index;
    BOOLEAN         Flag = FALSE;
    
    Status = GetChildDeviceHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, &ChildHandleCount, &ChildHandleBuffer);
    if (EFI_ERROR(Status)) return Status;

    for (ChildHandleIndex = 0; ChildHandleIndex < ChildHandleCount; ChildHandleIndex++) {
        Status = pBS->OpenProtocol(
                      ChildHandleBuffer[ChildHandleIndex],
                      &Protocol,
                      NULL, NULL, NULL,
                      EFI_OPEN_PROTOCOL_TEST_PROTOCOL);
        if (EFI_ERROR(Status))
            Status = GetProtocolHandlesManagedByDriver (DriverBindingHandle, ChildHandleBuffer[ChildHandleIndex], Protocol);
        else {
            for(Index = 0;Index < OutputHndList.ItemCount;Index ++) {
                if(*(EFI_HANDLE*)OutputHndList.Items[Index] == ChildHandleBuffer[ChildHandleIndex])
                    Flag = TRUE;
            }
            if(!Flag)
                AppendItemLst(&OutputHndList, &ChildHandleBuffer[ChildHandleIndex]);
        }
            
    }

    return EFI_SUCCESS;
}

/**
    Get all output device handles which are produced by a specific driver.
    The rountine will allocate pool buffer for the found output device handles,
    and it is the caller's responsibility to safe free the buffer.

    @param DriverBindingHandle - the handle of a driver which contains the binding protocol
    @param ControllerHandle - the device controller handle be opened by its child device 
    @param *OutputHandleCount - the number of available device handles returned in OutputHandleBuffer.
    @param **OutputHandleBuffer - a pointer to the buffer to return the array of Output device handles.

    @retval EFI_STATUS.

    @note  If returned status is not succeful or find no available device, the *OutputHandleBuffer will be NULL.

**/

EFI_STATUS
GetOutputDeviceHandlesManagedByDriver (
  IN  EFI_HANDLE    DriverBindingHandle,
  IN  EFI_HANDLE    ControllerHandle,
  OUT UINTN         *OutputHandleCount,
  OUT EFI_HANDLE    **OutputHandleBuffer )
{
    EFI_STATUS      Status;
    UINTN           HandleIndex = 0;

    *OutputHandleCount  = 0;
    *OutputHandleBuffer = NULL;

    Status = GetProtocolHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, gEfiEdidDiscoveredProtocolGuid);
    Status = GetProtocolHandlesManagedByDriver (DriverBindingHandle, ControllerHandle, gEfiGraphicsOutputProtocolGuid);

    if (OutputHndList.ItemCount) {
        *OutputHandleCount = OutputHndList.ItemCount;
        *OutputHandleBuffer = MallocZ(sizeof(EFI_HANDLE) * (*OutputHandleCount));
        for (HandleIndex = 0; HandleIndex < *OutputHandleCount; HandleIndex++) {
            (*OutputHandleBuffer)[HandleIndex] = *(EFI_HANDLE*)(OutputHndList.Items[HandleIndex]);
        }
    }

    return Status;
}
