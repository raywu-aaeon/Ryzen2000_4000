//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file AmiGopPolicy.c
    AmiGopPolicy output initialization in the DXE stage.

*/

//----------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------

#include <Efi.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Token.h>
#include <Protocol/DevicePath.h>
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
#include <Protocol/EdidOverride.h>
#endif
#include <AmiGopPolicy.h>
#include <AmiGopPolicyLinks.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/PciIo.h>
#include <Pci.h>
#include <Protocol/DriverBinding.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
typedef struct {
    LIST_ENTRY                  Link;
    EFI_DRIVER_BINDING_PROTOCOL *EfiDriverBindingProtocol;
    EFI_DRIVER_BINDING_START    OriginalStartFunction;
} GOP_POLICY_DRIVERBINDING_LIST;

LIST_ENTRY  gGopDriverBindingList;

UINT8       gEdidActiveDataBlock[128] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x5A, 0x63, 0x18, 0xF3, 0x01, 0x01, 0x01, 0x01, 0x07, 0x0E, 0x01, 0x03, 0x08, 0x1E, 0x17, 0x78, 0x2A, 0x8C, 0x3E, 0xA4, 0x58, 0x4D, 0x91, 0x24, 0x15, 0x4F, 0x51, 0xBF, 0xEE, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x64, 0x19, 0x00, 0x40, 0x41, 0x00, 0x26, 0x30, 0x18, 0x88, 0x36, 0x00, 0x30, 0xE4, 0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x39, 0x32, 0x32, 0x30, 0x34, 0x30, 0x37, 0x30, 0x30, 0x32, 0x37, 0x35, 0x0A, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x32, 0x4B, 0x1E, 0x3E, 0x09, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x56, 0x41, 0x35, 0x32, 0x31, 0x2D, 0x31, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x57};
//----------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
typedef EFI_STATUS (OEM_GOP_EDID_OVERRIDE_GET_EDID) (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid
);
#endif

// Function Prototype(s)

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
EFI_STATUS 
EFIAPI
AmiGopEdidOverrideGetEdid (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid
);
#endif

//----------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

static EFI_GUID gAmiGopPolicyVariableGuid = AMI_GOP_POLICY_VARIABLE_GUID;    

// Protocol Definition(s)

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
EFI_EDID_OVERRIDE_PROTOCOL EfiEdidOverrideProtocol = {
  AmiGopEdidOverrideGetEdid
};
#endif

// External Declaration(s)

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
extern OEM_GOP_EDID_OVERRIDE_GET_EDID   OEM_GOP_EDID_OVERRIDE_GET_EDID_LIST EndOfOemGopEdidOverrideGetEdidList;
#endif

// Function Definition(s)

VOID ConnectDevicePath(IN EFI_DEVICE_PATH_PROTOCOL *pPath);
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
OEM_GOP_EDID_OVERRIDE_GET_EDID* OemGopEdidOverrideGetEdidList[] = {OEM_GOP_EDID_OVERRIDE_GET_EDID_LIST NULL};
#endif


/**
    Connect AmiGopPolicyConOut Device Path

    @param VOID

    @retval VOID

    @note  None.

**/

VOID
ConnectAmiGopPolicyConOut (VOID)
{
    EFI_STATUS                  Status;
    EFI_DEVICE_PATH_PROTOCOL    *GopDevicePath = NULL;
    UINTN                       VariableSize = 0;
    UINTN                       DeviceHandleCount = 0;
    EFI_HANDLE                  *DeviceHandleBuffer = NULL;
    EFI_HANDLE                  DeviceHandle;
    UINTN                       DeviceHandleIndex;
    EFI_DEVICE_PATH_PROTOCOL    *DevicePath = NULL;
    UINTN                       DevicePathSize;
    BOOLEAN                     Matched = FALSE;


    Status = GetEfiVariable (
             L"AmiGopOutputDp",
             &gAmiGopPolicyVariableGuid,
             NULL,
             &VariableSize,
             (VOID**)&GopDevicePath);
    if ((EFI_ERROR(Status)) || (GopDevicePath == NULL)) return ;
    DevicePathSize = GetDevicePathSize (GopDevicePath);

    ConnectDevicePath(GopDevicePath);
    Status = gBS->LocateHandleBuffer (
            ByProtocol,
            &gEfiGraphicsOutputProtocolGuid,
            NULL,
            &DeviceHandleCount,
            &DeviceHandleBuffer);
    if(!EFI_ERROR(Status)) {
        for (DeviceHandleIndex = 0; DeviceHandleIndex < DeviceHandleCount; DeviceHandleIndex++) {
            DeviceHandle = DeviceHandleBuffer[DeviceHandleIndex];
            Status = gBS->HandleProtocol(DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID**)&DevicePath);
            if(!EFI_ERROR(Status)) {
                if (DevicePathSize == GetDevicePathSize (DevicePath)) {
                    if(CompareMem (GopDevicePath, DevicePath, DevicePathSize) == 0) {
                        Matched = TRUE;
                        break;
                    }
                }
            }
        }
        if(DeviceHandleBuffer)
            gBS->FreePool(DeviceHandleBuffer);
    }

    if(!Matched) {
        //
        // delete AmiGop Outut Device path
        //
        Status = gRT->SetVariable (
                      L"AmiGopOutputDp",
                      &gAmiGopPolicyVariableGuid,
                      0,
                      0,
                      NULL);
    }
    
    
    
    gBS->FreePool(GopDevicePath);
    return;
}

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

    Status = gBS->LocateHandleBuffer(
                  AllHandles,   
                  NULL,
                  NULL,
                  &HandleCount, 
                  &HandleBuffer);
    if (EFI_ERROR(Status)) return EFI_NOT_FOUND;

    for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
        ProtocolGuidArray = NULL;
        Status = gBS->ProtocolsPerHandle(
                      HandleBuffer[HandleIndex], 
                      &ProtocolGuidArray, 
                      &ArrayCount);
        if (EFI_ERROR(Status)) continue;

        for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {
            Status = gBS->OpenProtocolInformation(
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
                                gBS->FreePool(OpenInfo);
                                gBS->FreePool(ProtocolGuidArray);
                                gBS->FreePool(HandleBuffer);
                                return EFI_SUCCESS;
                            }
                        }
                    }
                }
            }
            if (OpenInfo != NULL) gBS->FreePool(OpenInfo);
        }
         if (ProtocolGuidArray != NULL) gBS->FreePool(ProtocolGuidArray);
    }
    if (HandleBuffer != NULL) gBS->FreePool(HandleBuffer);
    return EFI_NOT_FOUND;
}

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
    Status = gBS->OpenProtocol(
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

EFI_STATUS
DriverBindingStartWrapper (
    IN EFI_DRIVER_BINDING_PROTOCOL  *This,
    IN EFI_HANDLE                   ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_DEVICE_PATH_PROTOCOL        *GopDevicePath = NULL;
    UINTN                           VariableSize = 0;
    GOP_POLICY_DRIVERBINDING_LIST   *DriverBinding = NULL;
    LIST_ENTRY                      *Entry;
    BOOLEAN                         EntryFound = FALSE;
    EFI_DEVICE_PATH_PROTOCOL        *GopAcpiAdrDPNode = NULL;
    UINTN                           DeviceHandleCount = 0;
    EFI_HANDLE                      *DeviceHandleBuffer = NULL;
    EFI_HANDLE                      DeviceHandle;
    UINTN                           DeviceHandleIndex;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath = NULL;
    UINTN                           DevicePathSize;    
    
    for (Entry = GetFirstNode(&gGopDriverBindingList); !IsNull(&gGopDriverBindingList, Entry); Entry = GetNextNode(&gGopDriverBindingList, Entry)) {
        DriverBinding = (GOP_POLICY_DRIVERBINDING_LIST *)Entry;

        if (CompareMem(This, DriverBinding->EfiDriverBindingProtocol, sizeof(UINTN)) == 0) {
            EntryFound = TRUE;
            break;
        }
    }
    
    if (!EntryFound) {
        return EFI_NOT_FOUND;
    }
    
    if (DriverBinding->OriginalStartFunction == NULL) {
        return EFI_NOT_FOUND;
    }
            
    Status = GetEfiVariable (
        L"AmiGopOutputDp",
        &gAmiGopPolicyVariableGuid,
        NULL,
        &VariableSize,
        (VOID**)&GopDevicePath
    );

    if (GopDevicePath != NULL) {
        DevicePathSize = GetDevicePathSize (GopDevicePath);
        GopAcpiAdrDPNode = DPGetLastNode(GopDevicePath);
        Status = gBS->LocateHandleBuffer (
                ByProtocol,
                &gEfiGraphicsOutputProtocolGuid,
                NULL,
                &DeviceHandleCount,
                &DeviceHandleBuffer);
        if(!EFI_ERROR(Status)) {
            for (DeviceHandleIndex = 0; DeviceHandleIndex < DeviceHandleCount; DeviceHandleIndex++) {
                DeviceHandle = DeviceHandleBuffer[DeviceHandleIndex];
                Status = gBS->HandleProtocol(DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID**)&DevicePath);
                if(!EFI_ERROR(Status)) {
                    if (DevicePathSize == GetDevicePathSize (DevicePath)) {
                        if(CompareMem (GopDevicePath, DevicePath, DevicePathSize) == 0) {
                            if(DeviceHandleBuffer)
                                gBS->FreePool(DeviceHandleBuffer);
                            return EFI_ALREADY_STARTED; 
                        }       
                    }
                }
            }
            if(DeviceHandleBuffer)
                gBS->FreePool(DeviceHandleBuffer);
        }
        
        Status = DriverBinding->OriginalStartFunction(This, ControllerHandle, GopAcpiAdrDPNode);
        if (Status == EFI_SUCCESS) {
            return Status;
        }
        
    }
    Status = DriverBinding->OriginalStartFunction(This, ControllerHandle, RemainingDevicePath);
    return Status;
}

VOID
HookGopDriverBinding (VOID)
{
    EFI_STATUS                      Status;
    UINTN                           VariableSize = 0;
    UINTN                           ControllerHandleCount = 0;
    EFI_HANDLE                      *ControllerHandleBuffer = NULL;
    EFI_HANDLE                      ControllerHandle;
    UINTN                           ControllerHandleIndex;
    EFI_PCI_IO_PROTOCOL             *PciIo;
    EFI_HANDLE                      DriverBindingHandle;
    EFI_DEVICE_PATH_PROTOCOL        *GopDevicePath = NULL;
    GOP_POLICY_DRIVERBINDING_LIST   *DriverBinding = NULL;
    static BOOLEAN                  DriverBindingHooked = FALSE;    
    
    if (DriverBindingHooked) {
        return;
    }
    
    DriverBindingHooked = TRUE;
    
    InitializeListHead(&gGopDriverBindingList);
    
    Status = GetEfiVariable (
             L"AmiGopOutputDp",
             &gAmiGopPolicyVariableGuid,
             NULL,
             &VariableSize,
             (VOID**)&GopDevicePath);
    
    if ((EFI_ERROR(Status)) || (GopDevicePath == NULL)) return ;
    
    //
    // Get all drivers handles which has PCI IO Protocol
    //
    Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &ControllerHandleCount,
                  &ControllerHandleBuffer);
    if (EFI_ERROR(Status)) return;
    
    for (ControllerHandleIndex = 0; ControllerHandleIndex < ControllerHandleCount; ControllerHandleIndex++) {
        
        //DEBUG ((EFI_D_INFO, "HookGopDriverBinding: ControllerHandle = 0x%lX\n", ControllerHandle));
        
        ControllerHandle = ControllerHandleBuffer[ControllerHandleIndex];
        Status = gBS->HandleProtocol (
            ControllerHandle, 
            &gEfiPciIoProtocolGuid, 
            (VOID**)&PciIo
        );
        if (EFI_ERROR(Status)) 
            continue;

        //
        // Get Driver Binding Protocol for this VGA
        //
        Status = GetDriverBindingHandle (ControllerHandle, &DriverBindingHandle);
        if (EFI_ERROR(Status)) 
            continue;

        Status = AmiDefaultGopDeviceCheck (ControllerHandle, DriverBindingHandle, PciIo);
        if (EFI_ERROR(Status)) 
            continue;

        Status = gBS->AllocatePool(EfiBootServicesData, sizeof(GOP_POLICY_DRIVERBINDING_LIST), (VOID**)&DriverBinding);
        if (EFI_ERROR(Status)) 
            continue;
        
        Status = gBS->OpenProtocol (
            DriverBindingHandle,
            &gEfiDriverBindingProtocolGuid,
            (VOID**)&(DriverBinding->EfiDriverBindingProtocol),
            NULL,
            NULL,
            EFI_OPEN_PROTOCOL_GET_PROTOCOL
        );
        if (EFI_ERROR(Status)) 
            continue;
                
        DriverBinding->OriginalStartFunction = DriverBinding->EfiDriverBindingProtocol->Start;
        DriverBinding->EfiDriverBindingProtocol->Start = DriverBindingStartWrapper;
        InsertTailList(&gGopDriverBindingList, &DriverBinding->Link);
    }

    if (ControllerHandleBuffer != NULL) gBS->FreePool(ControllerHandleBuffer);
    if (GopDevicePath != NULL) gBS->FreePool(GopDevicePath);
}

/**
    Invoke AmiGopEdidOverrideGetEdid eLink

    @param *This
    @param *ChildHandle
    @param *Attributes
    @param *EdidSize
    @param ***Edid

    @retval EFI_SUCCESS - Get Oem Override Edid Success.

    @note  None.

**/

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
EFI_STATUS
EFIAPI
AmiGopEdidOverrideGetEdid (
  IN      EFI_EDID_OVERRIDE_PROTOCOL  *This,
  IN      EFI_HANDLE                  *ChildHandle,
  OUT     UINT32                      *Attributes,
  IN OUT  UINTN                       *EdidSize,
  IN OUT  UINT8                       **Edid )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    UINTN       i;

    for (i = 0; OemGopEdidOverrideGetEdidList[i] != NULL; i++) {
        Status = OemGopEdidOverrideGetEdidList[i] (This, ChildHandle, Attributes, EdidSize, Edid);
        if(!EFI_ERROR(Status)) break;
    }

    return Status;
}
#endif

/**
    Sample code for AmiGopEdidOverrideGetEdid eLink function

    @param *This
    @param *ChildHandle
    @param *Attributes
    @param *EdidSize
    @param ***Edid

    @retval EFI_UNSUPPORTED - This Function Always Returns UNSUPPORTED.

    @note  None.

**/

#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
EFI_STATUS
AmiDefaultGopEdidOverrideGetEdid (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid )
{
    /**Attributes = 0;
    *EdidSize = 128;
    pBS->CopyMem (
           *Edid,
           &gEdidActiveDataBlock,
           128
           );
    return EFI_SUCCESS;*/
        return EFI_UNSUPPORTED;
}
#endif

/**
    Installs AmiGopPolicy related protocols

    @param VOID

    @retval VOID

    @note  None.

**/

VOID
AmiGopPolicyProtocolInsatll ( VOID )
{
#if OEM_EDID_OVERRIDE_PROTOCOL_SUPPORT
    EFI_HANDLE  Handle = NULL;

    gBS->InstallMultipleProtocolInterfaces(
         &Handle,
         &gEfiEdidOverrideProtocolGuid,
         &EfiEdidOverrideProtocol,
         NULL );
#endif
    return;
}

