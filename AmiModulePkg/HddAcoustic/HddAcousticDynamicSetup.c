//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file HddAcousticDynamicSetup.c
    Contains HDD Acoustic Setup Routines which dynamically 
    updates HddAcoustic Setup VFR data
**/

#include <Token.h>

//Library used
#include <AmiDxeLib.h>
#include <Library/HiiLib.h>
#include <Library/AmiHiiUpdateLib.h>
#include <Guid/MdeModuleHii.h>
#include <Protocol/HiiString.h>
#include "HddAcousticDynamicSetup.h"
#include "Acoustic.h"
#include <Library/PrintLib.h>

//-------------------------------------------------------------------------
// Global Variable Definitions
//-------------------------------------------------------------------------

HDD_ACOUSTIC_DEVICE_DATA       *AcousticDeviceData = NULL;
EFI_HII_STRING_PROTOCOL        *HiiString = NULL;
CHAR8                          *SupportedLanguages = NULL;

EFI_HII_HANDLE gAcousticHiiHandle = NULL;

EFI_GUID gAcousticDeviceGuid  = HDD_ACOUSTIC_DEVICE_GUID;
EFI_GUID gAcousticFormSetGuid = ACOUSTIC_FORM_SET_GUID;

EFI_VARSTORE_ID gVarstoreId = HDD_ACOUSTIC_DYNAMIC_VARIABLE_ID;

UINTN gAcousticDeviceBaseKey        = ACOUSTIC_DEVICE_BASE_KEY;
UINTN gAcousticControllerBaseKey    = ACOUSTIC_CONTROLLER_BASE_KEY;
UINTN gAcousticCheckBoxKey          = ACOUSTIC_CHECK_BOX_GLOBAL_KEY;
UINTN gAcousticCommonLevelKey       = ACOUSTIC_COMMON_ONEOF_GLOBAL_KEY;

EFI_STRING_ID gHddAcouPortNumberStrIds[ACOUSTIC_MAXIMUM_PORT_SUPPORTED] = {0};
EFI_STRING_ID gHddAcouIdeDeviceStrIds[ACOUSTIC_MAXIMUM_PORT_SUPPORTED] = {0};
EFI_STRING_ID gHddAcouHddNameStrIds[ACOUSTIC_DEVICE_COUNT] = {0};
EFI_STRING_ID gHddAcouControllerNameStrIds[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED] = {0};
EFI_STRING_ID gHddAcouNotAvailableStrId = 0;
EFI_STRING_ID gHddAcouNotSupportedStrId = 0;
EFI_STRING_ID gHddNotFound = 0;
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
EFI_STRING_ID gHddAcouSupportedStrId = 0;
#endif

EFI_STATUS 
HddAcousticBrowserCallback(
    CONST EFI_HII_CONFIG_ACCESS_PROTOCOL*, 
    EFI_BROWSER_ACTION, 
    EFI_QUESTION_ID, 
    UINT8,
    EFI_IFR_TYPE_VALUE*, 
    EFI_BROWSER_ACTION_REQUEST*
    );

EFI_HII_CONFIG_ACCESS_PROTOCOL CallBack = { NULL, NULL, HddAcousticBrowserCallback };

CALLBACK_INFO SetupCallBack[] = {
    // Last field in every structure will be filled by the Setup
    { &gAcousticFormSetGuid, &CallBack, ACOUSTIC_FORM_SET_CLASS, 0, 0},
};

/**
    Add/Set the String to HII Database using HiiString Protocol

    @param HiiHandle
    @param String
    @param StringId

    @retval VOID

**/
EFI_STRING_ID
HddAcousticHiiAddStringInternal (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  CHAR16 *        String,
    IN  EFI_STRING_ID   StringId
)
{
    EFI_STATUS      Status;
    CHAR8*          Languages = NULL;
    UINTN           LangSize = 0;
    CHAR8*          CurrentLanguage;
    BOOLEAN         LastLanguage = FALSE;

    if(HiiString == NULL) {
        Status = pBS->LocateProtocol(&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
        if(EFI_ERROR(Status)) {
            return 0;
        }
    }

    if(SupportedLanguages == NULL) {
        Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
        if(Status == EFI_BUFFER_TOO_SMALL) {
            Status = pBS->AllocatePool(EfiBootServicesData, LangSize, (VOID**)&Languages);
            if(EFI_ERROR(Status)) {
                //
                //not enough resources to allocate string
                //
                return 0;
            }
            Status = HiiString->GetLanguages(HiiString, HiiHandle, Languages, &LangSize);
            if(EFI_ERROR(Status)) {
                return 0;
            }
        }
        SupportedLanguages=Languages;
    } else {
        Languages=SupportedLanguages;
    }

    while(!LastLanguage) {
        //
        //point CurrentLanguage to start of new language
        //
        CurrentLanguage = Languages;
        while(*Languages != ';' && *Languages != 0)
            Languages++;

        //
        //Last language in language list
        //
        if(*Languages == 0) {
            LastLanguage = TRUE;
            if(StringId == 0) {
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            } else {
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            }
            if(EFI_ERROR(Status)) {
                return 0;
            }
        } else {
            //
            //put null-terminator
            //
            *Languages = 0;
            if(StringId == 0) {
                Status = HiiString->NewString(HiiString, HiiHandle, &StringId, CurrentLanguage, NULL, String, NULL);
            } else {
                Status = HiiString->SetString(HiiString, HiiHandle, StringId, CurrentLanguage, String, NULL);
            }
            *Languages = ';';       //restore original character
            Languages++;
            if(EFI_ERROR(Status)) {
                return 0;
            }
        }
    }
    return StringId;
}

/**
    Add the String to HII Database using HiiString Protocol

    @param HiiHandle
    @param String

    @retval VOID

**/
EFI_STRING_ID
HddAcousticHiiAddString (
    IN  EFI_HII_HANDLE  HiiHandle,
    IN  CHAR16 *        String
)
{
    return HddAcousticHiiAddStringInternal(HiiHandle, String, 0);
}

/**
    This function is swaps the (2) bytes in the array of words.
    Basically changes the endian format.
    
    @param  IN CHAR8    *Data
    @param  IN UINT16   Size

    @retval VOID

**/

VOID
Swap_Entries (
    IN  CHAR8   *Data,
    IN  UINT16  Size
)
{
    UINT16  Index;
    CHAR8   Temp8;

    for (Index = 0; (Index+1) < Size; Index+=2) {
        Temp8           = Data[Index];
        Data[Index]     = Data[Index + 1];
        Data[Index + 1] = Temp8;
    }
}

/**
    This function displays PCI Configuration Address for each
    SataControllers Configured in SETUP.

    @param UINT8 ControllerNum

    @retval EFI_STRING_ID

**/
EFI_STRING_ID
DisplayControllerAddressInfo (
    UINT8                       ControllerNum
)
{
    CHAR16                          *NewString;
    EFI_STATUS                      Status;
    EFI_STRING_ID                   StringId;
    UINTN                           StringSize = 100;
    
    Status = pBS->AllocatePool(EfiBootServicesData, StringSize,(VOID **) &NewString);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return 0;
    }
    
    UnicodeSPrint(NewString, \
             StringSize, \
             L"SATA Controller %d - PCI Bus %02X Dev %02X Fun %02X", \
             ControllerNum, \
             AcousticDeviceData->BusNum[ControllerNum],\
             AcousticDeviceData->DevNum[ControllerNum],\
             AcousticDeviceData->FunNum[ControllerNum]);

    StringId = HddAcousticHiiAddString(gAcousticHiiHandle, NewString);
    
    if(NewString) {
        pBS->FreePool(NewString);
    }
    
    return StringId;
}

/**
    This function gives the HDD connected port number.

    @param IN  EFI_HANDLE              *DeviceHandle
    @param OUT UINT32                  *PortNum
    @param IN  UINT8                   Num
    @param EFI_DISK_INFO_PROTOCOL      *DiskInfo 

    @retval EFI_STATUS

**/
EFI_STATUS
GetPortNumber (
    IN  EFI_HANDLE              *DeviceHandle,
    OUT UINT32                  *PortNum,
    IN  UINT8                   Num,
    EFI_DISK_INFO_PROTOCOL      *DiskInfo
)
{
    EFI_STATUS                      Status;
    UINT32                          IdeDevice;
    UINT32                          IdeChannel;
    
    Status = pBS->HandleProtocol (
                              DeviceHandle,
                              &gEfiDiskInfoProtocolGuid,
                              (VOID**)&DiskInfo
                              );
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    Status = DiskInfo->WhichIde (
                        DiskInfo,
                        &IdeChannel,
                        &IdeDevice
                        );
    
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    if(AcousticDeviceData->AcousticModeFlag[Num] == AmiStorageInterfaceAhci) {  // AHCI Mode
        *PortNum = IdeChannel;
    } else if(AcousticDeviceData->AcousticModeFlag[Num] == AmiStorageInterfaceIde) { // IDE Mode
        IdeDevice = IdeChannel + (IdeDevice * 2);
        *PortNum = IdeDevice;
    }
    return EFI_SUCCESS;
}

/**
    This function gets the controller handle.

    @param EFI_HANDLE            *DeviceHandle
    @param EFI_HANDLE            *ControllerHandle

    @retval EFI_STATUS

**/
EFI_STATUS
GetControllerHandle (
    IN EFI_HANDLE            *DeviceHandle,
    OUT EFI_HANDLE           *ControllerHandle
)
{
    EFI_STATUS                      Status;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePath;
    EFI_DEVICE_PATH_PROTOCOL        *DevicePathNode;
    PCI_DEVICE_PATH                 *PciDevicePath = NULL;
    
    Status = pBS->HandleProtocol (
                                  DeviceHandle,
                                  &gEfiDevicePathProtocolGuid,
                                  (VOID *) &DevicePath
                                  );
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    DevicePathNode = DevicePath;
    while (!isEndNode (DevicePathNode)) {
        if ((DevicePathNode->Type == HARDWARE_DEVICE_PATH) &&
                (DevicePathNode->SubType == HW_PCI_DP)) {
                    PciDevicePath = (PCI_DEVICE_PATH *) DevicePathNode;
                    break;
        }

        DevicePathNode = NEXT_NODE (DevicePathNode);
    }
    
    if (PciDevicePath == NULL) {
        return EFI_NOT_FOUND;
    }
    
    // Getting controller handle
    Status = pBS->LocateDevicePath( &gEfiPciIoProtocolGuid, 
                                    &DevicePath, 
                                    ControllerHandle);
    
    ASSERT_EFI_ERROR(Status);
        
    return Status;
}

/**
    This function reads IDENTIFY_DATA and gets HDD model number. Finally this 
    function adds HDD Model number as a string to HII Database

    @param UINT8           DeviceNum 

    @retval VOID

**/
EFI_STRING_ID 
GetHddModelNumber (
    UINT8                      DeviceNum
)
{
    EFI_STATUS                      Status;
    UINT32                          PortNumber;
    CHAR16                          *NewString;
    UINT8                           Index;
    UINT8                           Num;
    UINTN                           HandleCount;
    EFI_HANDLE                      *HandleBuffer;
    EFI_HANDLE                      ControllerHandle;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo = NULL;
    EFI_PCI_IO_PROTOCOL             *PciIO;
    IDENTIFY_DATA                   *IdentifyDriveInfo = NULL;
    UINT32                          BufferSize = 0;
    CHAR8                           ModelNumber[43];
    UINTN                           SegNum;
    UINTN                           BusNum;
    UINTN                           DevNum;
    UINTN                           FuncNum;
    UINT32                          IdeDevice;
    UINT32                          IdeChannel;
    EFI_STRING_ID                   StringId;
    UINTN                           StringSize = 100;
    
    Status = pBS->LocateHandleBuffer (
                                      ByProtocol,
                                      &gEfiDiskInfoProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer
                                      );
    if (EFI_ERROR(Status)) {
        HandleCount = 0;
    }
    
    for (Index = 0; Index < HandleCount; Index++) {
        // Gets Controller Handle
        Status = GetControllerHandle(HandleBuffer[Index], &ControllerHandle);
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            pBS->FreePool (HandleBuffer);
            return 0;
        }
        
        // Get the PCI IO Protocol instance
        Status = pBS->OpenProtocol(
                          ControllerHandle,
                          &gEfiPciIoProtocolGuid,
                          (VOID **) &PciIO,
                          NULL,
                          ControllerHandle,
                          EFI_OPEN_PROTOCOL_GET_PROTOCOL);
          
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            pBS->FreePool (HandleBuffer);
            return 0;
        }
        
        // Retrieves PCI controller's PCI bus, device and function number.
        Status = PciIO->GetLocation(PciIO, 
                                    &SegNum, 
                                    &BusNum, 
                                    &DevNum, 
                                    &FuncNum);
        
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            pBS->FreePool (HandleBuffer);
            return 0;
        }
        
        for(Num=0; Num < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Num++) {
            if(AcousticDeviceData->ControllerPresent[Num] == 0) {
                continue;
            }
            
            // Checking for correct controller
            if((BusNum == AcousticDeviceData->BusNum[Num]) && \
               (DevNum == AcousticDeviceData->DevNum[Num]) && \
               (FuncNum == AcousticDeviceData->FunNum[Num])) {
                Status = pBS->HandleProtocol (
                                          HandleBuffer[Index],
                                          &gEfiDiskInfoProtocolGuid,
                                          (VOID**)&DiskInfo
                                          );
                if(EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    pBS->FreePool (HandleBuffer);
                    return 0;
                }

                Status = DiskInfo->WhichIde (
                                    DiskInfo,
                                    &IdeChannel,
                                    &IdeDevice
                                    );
                
                if(EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    pBS->FreePool (HandleBuffer);
                    return 0;
                }
                
                if(AcousticDeviceData->AcousticModeFlag[Num] == AmiStorageInterfaceAhci) {  // AHCI Mode
                    PortNumber = IdeChannel;
                } else if(AcousticDeviceData->AcousticModeFlag[Num] == AmiStorageInterfaceIde) { // IDE Mode
                    IdeDevice = IdeChannel + (IdeDevice * 2);
                    PortNumber = IdeDevice;
                }

                // Checking for correct HDD
                if(DeviceNum != ((Num * ACOUSTIC_MAXIMUM_PORT_SUPPORTED) + PortNumber)) {
                    continue;
                }

                Status = pBS->AllocatePool(EfiBootServicesData, 
                                           sizeof (IDENTIFY_DATA), 
                                           (VOID**)&IdentifyDriveInfo);
                if(EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    pBS->FreePool (HandleBuffer);
                    return 0;
                }

                pBS->SetMem(IdentifyDriveInfo, sizeof (IDENTIFY_DATA), 0);

                BufferSize = sizeof (IDENTIFY_DATA);
                Status = DiskInfo->Identify (
                                        DiskInfo,
                                        IdentifyDriveInfo,
                                        &BufferSize
                                        );
                if(EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    pBS->FreePool (IdentifyDriveInfo);
                    pBS->FreePool (HandleBuffer);
                    return 0;
                }
                
                // Copying HDD Model Number
                if(IdentifyDriveInfo != NULL) {
                    pBS->SetMem(ModelNumber, 42, 0x20);
                    pBS->CopyMem (ModelNumber+2, IdentifyDriveInfo->Model_Number_27, 40);
                    Swap_Entries (ModelNumber+2, 40);
                    ModelNumber[42] = '\0';

                    Status = pBS->AllocatePool(EfiBootServicesData, 
                                               StringSize, 
                                               (VOID**)&NewString);
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR(Status);
                        pBS->FreePool (IdentifyDriveInfo);
                        pBS->FreePool (HandleBuffer);
                        return 0;
                    }
                
                    UnicodeSPrint(NewString, StringSize, L"%a", ModelNumber);

                    // Adding the String to HII Database
                    StringId = HddAcousticHiiAddString(gAcousticHiiHandle, NewString);

                    if (IdentifyDriveInfo) {
                        pBS->FreePool (IdentifyDriveInfo);
                        IdentifyDriveInfo = NULL;
                    }
                    pBS->FreePool (NewString);
                }
            }
        }
    }
    pBS->FreePool (HandleBuffer);
    return StringId;
}

/**
    This function issues the SetFeature command

    @param  EFI_HANDLE                     ControllerHandle
    @param  EFI_HANDLE                     DeviceHandle
    @param  AMI_STORAGE_BUS_INTERFACE      BusInterfaceType
    @param  UINT8                          SubCommand
    @param  UINT8                          Mode

    @retval Status

**/
EFI_STATUS
IssueSetFeatureCmd (
    IN EFI_HANDLE                     ControllerHandle,
    IN EFI_HANDLE                     DeviceHandle,
    IN AMI_STORAGE_BUS_INTERFACE      BusInterfaceType,
    UINT8                             SubCommand,
    UINT8                             Mode
)
{
    EFI_STATUS                  Status;
    EFI_BLOCK_IO_PROTOCOL       *BlockIO;

#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) 
    AMI_IDE_BUS_PROTOCOL *IdeBusInterface;
#endif
    
#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
    SATA_DEVICE_INTERFACE   *SataDevInterface;
    AMI_AHCI_BUS_PROTOCOL   *AhciBusInterface;
    COMMAND_STRUCTURE       CommandStructure = {0};
#endif
    
    // Get the BlockIo Protocol instance
    Status = pBS->HandleProtocol(DeviceHandle, 
                                 &gEfiBlockIoProtocolGuid, 
                                 (VOID**)&BlockIO);

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    if ( BusInterfaceType == AmiStorageInterfaceAhci ) {
#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
        // It is in AHCI mode
        Status = pBS->OpenProtocol( ControllerHandle,
                                    &gAmiAhciBusProtocolGuid,
                                    (VOID**)&AhciBusInterface,
                                    NULL,
                                    ControllerHandle,
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL );
        if(!EFI_ERROR(Status)) {
            SataDevInterface = ((SATA_BLOCK_IO *)BlockIO)->SataDevInterface;
            CommandStructure.Command     = SET_FEATURE_COMMAND;
            CommandStructure.Features    = SubCommand;
            CommandStructure.SectorCount = Mode;
            Status = SataDevInterface->AhciBusInterface->ExecuteNonDataCommand \
                                                        ( SataDevInterface,\
                                                          CommandStructure );
        }
#endif
    } else if ( BusInterfaceType == AmiStorageInterfaceIde ) {
#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) 
        // It is in IDE mode
        Status = pBS->OpenProtocol( ControllerHandle,
                                    &gAmiIdeBusInitProtocolGuid,
                                    (VOID**)&IdeBusInterface,
                                    NULL,
                                    ControllerHandle,
                                    EFI_OPEN_PROTOCOL_GET_PROTOCOL );
        if(!EFI_ERROR(Status)) {
            IdeBusInterface = ((IDE_BLOCK_IO *)BlockIO)->IdeBusInterface;
            Status = IdeBusInterface->IdeNonDataCommand \
                                     ( IdeBusInterface, \
                                     SubCommand, Mode, 0, 0, 0, 0, 0, \
                                     0, 0, \
                                     IdeBusInterface->IdeDevice.Device << 4, \
                                     SET_FEATURE_COMMAND );
        }
#endif
    }
    return Status;
}

/**
    This function calls IssueSetFeatureCmd() according to Enable or
    Disable Automatic Acoustic Management

    @param  EFI_HANDLE                  *HandleBuffer
    @param  UINTN                       HandleCount
    @param  UINT8                       AcousticLevel
    @param  BOOLEAN                     DisableAcoustic

    @retval Status

**/
EFI_STATUS
AcousticManagementSupport (
    EFI_HANDLE                  *HandleBuffer,
    UINTN                       HandleCount,
    UINT8                       AcousticLevel,
    BOOLEAN                     DisableAcoustic
)
{
    EFI_STATUS                      Status;
    UINT8                           DeviceNum;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo = NULL;
    UINT8                           Index;
    UINT8                           Num;
    UINT8                           AcousticSupport;
    EFI_HANDLE                      ControllerHandle;
    EFI_PCI_IO_PROTOCOL             *PciIO = NULL;
    UINT32                          PortNum;
    UINTN                           SegNum;
    UINTN                           BusNum;
    UINTN                           DevNum;
    UINTN                           FuncNum;
    HDD_ACOUSTIC_DEVICE_DATA        *DeviceData = NULL;
    
    Status = pBS->AllocatePool( EfiBootServicesData, \
                                sizeof(HDD_ACOUSTIC_DEVICE_DATA), \
                                (VOID**)&DeviceData );
    ASSERT_EFI_ERROR( Status );
    if (EFI_ERROR(Status)) { 
        return Status;
    }
    
    // Retrieve uncommitted data from Browser
    HiiGetBrowserData(&gAcousticDeviceGuid, 
                      ACOUSTIC_VAR_NAME, 
                      sizeof(HDD_ACOUSTIC_DEVICE_DATA), 
                      (UINT8 *)DeviceData);
    
    for (Index = 0; Index < HandleCount; Index++) {
        // Gets Controller Handle
        Status = GetControllerHandle(HandleBuffer[Index], &ControllerHandle);
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            continue;
        }
        // Get the PCI IO Protocol instance
        Status = pBS->OpenProtocol(
                          ControllerHandle,
                          &gEfiPciIoProtocolGuid,
                          (VOID **) &PciIO,
                          NULL,
                          ControllerHandle,
                          EFI_OPEN_PROTOCOL_GET_PROTOCOL);
          
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            continue;
        }
        // Retrieves PCI controller's PCI bus, device and function number.
        Status = PciIO->GetLocation(PciIO, &SegNum, &BusNum, &DevNum, &FuncNum);
                    
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            continue;
        }
        
        for(Num=0; Num < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Num++) {
            if(AcousticDeviceData->ControllerPresent[Num] == 0) {
                continue;
            }
            
            // Checking for correct controller
            if((BusNum == AcousticDeviceData->BusNum[Num]) && \
               (DevNum == AcousticDeviceData->DevNum[Num]) && \
               (FuncNum == AcousticDeviceData->FunNum[Num])) {
                // Gets HDD connected port number
                Status = GetPortNumber(HandleBuffer[Index], 
                                       &PortNum, 
                                       Num, 
                                       DiskInfo);
                if(EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    break;
                }
                
                DeviceNum = (Num * ACOUSTIC_MAXIMUM_PORT_SUPPORTED) + (UINT8)PortNum;
                // If HDD not support Acoustic, don't send Acoustic Level to HDD
                if(AcousticDeviceData->AcousticSupported[DeviceNum] == 0) {
                    continue;
                }
                
                if(DisableAcoustic == FALSE) {
                    AcousticLevel = AcousticDeviceData->VendorAcousticValue[DeviceNum];
                    DeviceData->AcousticLevelIndv[DeviceNum] = ACOUSTIC_LEVEL_BYPASS;
                    AcousticSupport = ACOUSTIC_MANAGEMENT_ENABLE;
                } else {
                    AcousticSupport = ACOUSTIC_MANAGEMENT_DISABLE;
                }
                
                Status = IssueSetFeatureCmd(ControllerHandle,
                                            HandleBuffer[Index],
                                            AcousticDeviceData->AcousticModeFlag[Num],
                                            AcousticSupport,
                                            AcousticLevel);
                if (EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    break;
                }
            }
        }
    }
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
    if (DeviceData != NULL) {
        DeviceData->AcousticLevel = ACOUSTIC_LEVEL_BYPASS;
    }
#endif
    
    // Updates uncommitted data in the Form Browser
    HiiSetBrowserData(&gAcousticDeviceGuid, 
                      ACOUSTIC_VAR_NAME, 
                      sizeof(HDD_ACOUSTIC_DEVICE_DATA), 
                      (UINT8 *)DeviceData,
                      NULL);
    
    if (DeviceData) {
        pBS->FreePool (DeviceData);
    }
    
    return Status;
}

/**
    This function finds correct HDD and sends respective acoustic level
    to that HDD.

    @param  EFI_HANDLE                  *HandleBuffer
    @param  UINTN                       HandleCount
    @param  UINT8                       AcousticLevel
    @param  BOOLEAN                     DisableAcoustic

    @retval Status

**/
EFI_STATUS
SetAcousticLevel (
    EFI_HANDLE  *HandleBuffer,
    UINTN       HandleCount,
    UINT8       AcousticLevel,
    UINT8       DeviceNum)
{
    EFI_STATUS                      Status;
    UINT8                           Index;
    UINT8                           Num = 0;
    UINT8                           CommonAcousticMode;
    UINT32                          PortNum;
    UINTN                           SegNum;
    UINTN                           BusNum;
    UINTN                           DevNum;
    UINTN                           FuncNum;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo = NULL;
    EFI_PCI_IO_PROTOCOL             *PciIO = NULL;
    EFI_HANDLE                      ControllerHandle;
    
    CommonAcousticMode = AcousticLevel;

    for (Index = 0; Index < HandleCount; Index++) {
            // Gets Controller Handle
            Status = GetControllerHandle(HandleBuffer[Index], &ControllerHandle);
            if(EFI_ERROR(Status)) {
                ASSERT_EFI_ERROR(Status);
                continue;
            }
            // Get the PCI IO Protocol instance
            Status = pBS->OpenProtocol(
                              ControllerHandle,
                              &gEfiPciIoProtocolGuid,
                              (VOID **) &PciIO,
                              NULL,
                              ControllerHandle,
                              EFI_OPEN_PROTOCOL_GET_PROTOCOL);
              
            if(EFI_ERROR(Status)) {
                ASSERT_EFI_ERROR(Status);
                continue;
            }
            Status = PciIO->GetLocation(PciIO, 
                                        &SegNum, 
                                        &BusNum, 
                                        &DevNum, 
                                        &FuncNum);
                        
            if(EFI_ERROR(Status)) {
                ASSERT_EFI_ERROR(Status);
                continue;
            }
            
#if INDIVIDUAL_ACOUSTIC_SUPPORT
            Num = DeviceNum/ACOUSTIC_MAXIMUM_PORT_SUPPORTED;
#else
            Num = 0;
#endif
            for(;Num < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Num++) {
                if(AcousticDeviceData->ControllerPresent[Num] == 0) {
                    continue;
                }
                
                if((BusNum == AcousticDeviceData->BusNum[Num]) && \
                   (DevNum == AcousticDeviceData->DevNum[Num]) && \
                   (FuncNum == AcousticDeviceData->FunNum[Num])) {
                    // Gets HDD connected port number
                    Status = GetPortNumber(HandleBuffer[Index], 
                                           &PortNum, 
                                           Num, 
                                           DiskInfo);
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR(Status);
                        break;
                    }
                    
#if INDIVIDUAL_ACOUSTIC_SUPPORT
                    // Checking for correct HDD
                    if(DeviceNum != ((Num * ACOUSTIC_MAXIMUM_PORT_SUPPORTED) + PortNum)) {
                        break;
                    }
#else
                    DeviceNum = Num * ACOUSTIC_MAXIMUM_PORT_SUPPORTED + PortNum;
#endif
                    // If HDD not support Acoustic, don't send Acoustic Level to HDD
                    if(AcousticDeviceData->AcousticSupported[DeviceNum] == 0) {
                        break;
                    }
                    
                    // If Bypass Acoustic Mode, get vendor acoustic level
                    if(CommonAcousticMode == ACOUSTIC_LEVEL_BYPASS) { 
                        AcousticLevel = AcousticDeviceData->VendorAcousticValue[DeviceNum];
                    }
                    
                    Status = IssueSetFeatureCmd(ControllerHandle,
                                                HandleBuffer[Index],
                                                AcousticDeviceData->AcousticModeFlag[Num],
                                                ACOUSTIC_MANAGEMENT_ENABLE,
                                                AcousticLevel);
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR(Status);
                        break;
                    }
#if INDIVIDUAL_ACOUSTIC_SUPPORT
                    return Status;
#endif
                }
            }
        }
    return EFI_SUCCESS;
}

/**
    This function will dynamically add VFR contents to HDD Acoustic BIOS setup page
    using HII library functions.

    @param UINT8 ControllerNum

    @retval VOID

**/
VOID
HddAcousticInitDynamicSubFormContents(
    UINT8 ControllerNum
)
{
    VOID                        *StartOpCodeHandle;
    VOID                        *EndOpCodeHandle;
    EFI_IFR_GUID_LABEL          *StartLabel;
    EFI_IFR_GUID_LABEL          *EndLabel;
    VOID                        *OneOfOptionOpCodeHandle;
    UINT8                       Index;
    UINT8                       DeviceNum;
    CHAR16                      *String = NULL;
    UINTN                       StringSize = 70;
    EFI_STATUS                  Status;
    HDD_ACOUSTIC_DEVICE_DATA    *DeviceData = NULL;
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
    EFI_STRING_ID               StringId;
#endif
    
    Status = pBS->AllocatePool( EfiBootServicesData, \
                                sizeof(HDD_ACOUSTIC_DEVICE_DATA), \
                                (VOID**)&DeviceData );
    ASSERT_EFI_ERROR( Status );
    if (EFI_ERROR(Status)) { 
        return;
    }
    
    // Retrieve uncommitted data from Browser
    HiiGetBrowserData(&gAcousticDeviceGuid, 
                      ACOUSTIC_VAR_NAME, 
                      sizeof(HDD_ACOUSTIC_DEVICE_DATA), 
                      (UINT8 *)DeviceData);

    StartOpCodeHandle = HiiAllocateOpCodeHandle ();
    EndOpCodeHandle = HiiAllocateOpCodeHandle ();
    OneOfOptionOpCodeHandle = HiiAllocateOpCodeHandle ();

    // Create Hii Extended Label OpCode as the start and end opcode
    StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));

    EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    
    if(StartLabel == NULL || EndLabel == NULL) {
        return;
    }
    
    StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
    EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;

    StartLabel->Number = ACOUSTIC_SUB_FORM_LABEL_START;
    EndLabel->Number = ACOUSTIC_SUB_FORM_LABEL_END;
    
#if INDIVIDUAL_ACOUSTIC_SUPPORT
    // Create Oneof Option Opcode
    HiiCreateOneOfOptionOpCode (
            OneOfOptionOpCodeHandle,
            STRING_TOKEN(STR_BYPASS_STRING),
            (EFI_IFR_OPTION_DEFAULT | EFI_IFR_FLAG_CALLBACK),
            EFI_IFR_NUMERIC_SIZE_1,
            ACOUSTIC_LEVEL_BYPASS );

    HiiCreateOneOfOptionOpCode (
            OneOfOptionOpCodeHandle,
            STRING_TOKEN(STR_QUIET_STRING),
            EFI_IFR_FLAG_CALLBACK,
            EFI_IFR_NUMERIC_SIZE_1,
            ACOUSTIC_LEVEL_QUIET );
    
    HiiCreateOneOfOptionOpCode (
            OneOfOptionOpCodeHandle,
            STRING_TOKEN(STR_MAXIMUM_PERFORMANCE_STRING),
            EFI_IFR_FLAG_CALLBACK,
            EFI_IFR_NUMERIC_SIZE_1,
            ACOUSTIC_LEVEL_MAXIMUM_PERFORMANCE );
#endif
    
    Status = pBS->AllocatePool( EfiBootServicesData,
                       StringSize,
                       (VOID**)&String );
    
    if(!EFI_ERROR(Status)) {
        for(Index = 0; Index < ACOUSTIC_MAXIMUM_PORT_SUPPORTED; Index++) {
            // Calculating Device Number
            DeviceNum = ControllerNum * ACOUSTIC_MAXIMUM_PORT_SUPPORTED + Index;
            
            if(AcousticDeviceData->AcousticDevicePresent[DeviceNum]) {

                // Gets HDD model number and adds the model number as
                // string to HII Database
                if(gHddAcouHddNameStrIds[DeviceNum] == 0) {
                    gHddAcouHddNameStrIds[DeviceNum] = GetHddModelNumber(DeviceNum);;
                }
                
                if(AcousticDeviceData->AcousticModeFlag[ControllerNum] == AmiStorageInterfaceIde) { // IDE Mode
                    // Checks whether Port Number string already present or not
                    if(gHddAcouIdeDeviceStrIds[Index] == 0) {
                        if(Index == 0){
                            UnicodeSPrint(String, StringSize, L"Primary Master");
                        } else if(Index == 1){
                            UnicodeSPrint(String, StringSize, L"Secondary Master");
                        } else if(Index == 2){
                            UnicodeSPrint(String, StringSize, L"Primary Slave");
                        } else if(Index == 3){
                            UnicodeSPrint(String, StringSize, L"Secondary Slave");
                        }
                        gHddAcouIdeDeviceStrIds[Index] = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                    } 
                    // Updating IDE device dynamically
                    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            gHddAcouIdeDeviceStrIds[Index],
                            STRING_TOKEN(STR_EMPTY),
                            0,0);
                } else if(AcousticDeviceData->AcousticModeFlag[ControllerNum] == AmiStorageInterfaceAhci) { // AHCI Mode
                    if(gHddAcouPortNumberStrIds[Index] == 0) {
                        UnicodeSPrint(String, StringSize, L"Port %d", Index);
                        gHddAcouPortNumberStrIds[Index] = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                    }
                    // Updating Port number dynamically
                    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            gHddAcouPortNumberStrIds[Index],
                            STRING_TOKEN(STR_EMPTY),
                            0,0);
                }
                
                // Checks whether HDD Model Number string already present or not
                if(gHddAcouHddNameStrIds[DeviceNum] == 0) {
                    UnicodeSPrint(String, StringSize, L"  Port is empty");
                    gHddAcouHddNameStrIds[DeviceNum] = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                }
                
                // Updating HDD model number dynamically
                HiiCreateSubTitleOpCode(StartOpCodeHandle,
                        gHddAcouHddNameStrIds[DeviceNum],
                        STRING_TOKEN(STR_EMPTY),
                        0,0);
                
#if INDIVIDUAL_ACOUSTIC_SUPPORT
                // Checking Acoustic enabled or disabled in Setup
                if(DeviceData->AcousticPwrMgmt == 0) { // If Disabled,
                    if(gHddAcouNotAvailableStrId == 0) {
                        UnicodeSPrint(String, StringSize, L"  Acoustic Mode Not Available");
                        gHddAcouNotAvailableStrId = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                    }
                    
                    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            STRING_TOKEN(gHddAcouNotAvailableStrId),
                            STRING_TOKEN(gHddAcouNotAvailableStrId),
                            0,0);
                } else { // If Enabled,
                    if(AcousticDeviceData->AcousticSupported[DeviceNum] == 1) {
                        // Acoustic Level selection
                        // Now create OneOf OpCode...
                        HiiCreateOneOfOpCode (
                            StartOpCodeHandle,
                            (EFI_QUESTION_ID)(gAcousticDeviceBaseKey + DeviceNum),
                            gVarstoreId,
                            (UINT16)EFI_FIELD_OFFSET(HDD_ACOUSTIC_DEVICE_DATA, AcousticLevelIndv[DeviceNum]),
                            STRING_TOKEN(STR_AUTO_ACOUSTIC_MODE),
                            STRING_TOKEN(STR_AUTO_ACOUSTIC_MODE_HELP),
                            EFI_IFR_FLAG_CALLBACK,
                            EFI_IFR_NUMERIC_SIZE_1,
                            OneOfOptionOpCodeHandle,
                            NULL
                            );
                    } else {
                        if(gHddAcouNotSupportedStrId == 0) {
                            UnicodeSPrint(String, StringSize, L"  Acoustic Not Supported");
                            gHddAcouNotSupportedStrId = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                        }
                        
                        HiiCreateSubTitleOpCode(StartOpCodeHandle,
                                STRING_TOKEN(gHddAcouNotSupportedStrId),
                                STRING_TOKEN(gHddAcouNotSupportedStrId),
                                0,0);
                    }
                }
#else
                // Checking Acoustic enabled or disabled in Setup
                if(DeviceData->AcousticPwrMgmt == 0) {
                    if(gHddAcouNotAvailableStrId == 0) {
                        UnicodeSPrint(String, StringSize, L"  Acoustic Mode Not Available");
                        gHddAcouNotAvailableStrId = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                    }
                    
                    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            STRING_TOKEN(gHddAcouNotAvailableStrId),
                            STRING_TOKEN(gHddAcouNotAvailableStrId),
                            0,0);
                } else {
                    if(AcousticDeviceData->AcousticSupported[DeviceNum] == 1) {
                        if(gHddAcouSupportedStrId == 0) {
                            UnicodeSPrint(String, StringSize, L"  Acoustic Supported");
                            gHddAcouSupportedStrId = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                        }
                        StringId = gHddAcouSupportedStrId;
                    } else {
                        if(gHddAcouNotSupportedStrId == 0) {
                            UnicodeSPrint(String, StringSize, L"  Acoustic  Not Supported");
                            gHddAcouNotSupportedStrId = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                        }
                        StringId = gHddAcouNotSupportedStrId;
                    }
                    
                    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            STRING_TOKEN(StringId),
                            STRING_TOKEN(StringId),
                            0,0);
                }
#endif
                    
                HiiCreateSubTitleOpCode(StartOpCodeHandle,
                        STRING_TOKEN(STR_EMPTY),
                        STRING_TOKEN(STR_EMPTY),
                        0,0);
            }
        }
        pBS->FreePool(String);
    }

    // We are done!!
    HiiUpdateForm (
      gAcousticHiiHandle,
      &gAcousticFormSetGuid,
      ACOUSTIC_SUB_FORM_ID,
      StartOpCodeHandle,
      EndOpCodeHandle
    );

    if (StartOpCodeHandle != NULL) {
        HiiFreeOpCodeHandle (StartOpCodeHandle);
        HiiFreeOpCodeHandle (EndOpCodeHandle);
        HiiFreeOpCodeHandle (OneOfOptionOpCodeHandle);
    }
    
    if (DeviceData) {
        pBS->FreePool (DeviceData);
    }

}

/**
    This function will dynamically add VFR contents to HDD Acoustic BIOS setup page
    using HII library functions.

    @param VOID

    @retval VOID

**/
VOID
HddAcousticInitDynamicMainFormContents(
    VOID
)
{
    VOID                        *StartOpCodeHandle;
    VOID                        *EndOpCodeHandle;
    EFI_IFR_GUID_LABEL          *StartLabel;
    EFI_IFR_GUID_LABEL          *EndLabel;
    VOID                        *EnDisOneOfOptionOpCodeHandle;
    UINT8                       Index;
    CHAR16                      *String = NULL;
    UINTN                       StringSize = 50;
    EFI_STATUS                  Status;
    BOOLEAN                     HddFound = FALSE;
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
    VOID                        *CommonOneOfOptionOpCodeHandle;
#endif
    
    StartOpCodeHandle = HiiAllocateOpCodeHandle ();
    EndOpCodeHandle = HiiAllocateOpCodeHandle ();
    EnDisOneOfOptionOpCodeHandle = HiiAllocateOpCodeHandle ();
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
    CommonOneOfOptionOpCodeHandle = HiiAllocateOpCodeHandle ();
#endif
    
    // Create Hii Extended Label OpCode as the start and end opcode
    StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));

    EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (
            EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
    
    if(StartLabel == NULL || EndLabel == NULL) {
        return;
    }

    StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
    EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
    
    StartLabel->Number = ACOUSTIC_MAIN_FORM_LABEL_START;
    EndLabel->Number = ACOUSTIC_MAIN_FORM_LABEL_END;
    
    // Checking HDD present or not
    for(Index=0; Index < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Index++) {
        if(AcousticDeviceData->ControllerPresent[Index]) {
            HddFound = TRUE;
            break;
        }
    }
    
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            STRING_TOKEN(STR_ACOUSTIC_SUBTITLE),
                            STRING_TOKEN(STR_EMPTY),
                            0,0);
    
    HiiCreateSubTitleOpCode(StartOpCodeHandle,
                            gHddNotFound,
                            STRING_TOKEN(STR_EMPTY),
                            0,0);
    
    if(HddFound) {
        
        HiiCreateOneOfOptionOpCode (
                EnDisOneOfOptionOpCodeHandle,
                STRING_TOKEN(STR_DISABLED_STRING),
                (EFI_IFR_OPTION_DEFAULT | EFI_IFR_OPTION_DEFAULT_MFG),
                EFI_IFR_NUMERIC_SIZE_1,
                0 );
    
        HiiCreateOneOfOptionOpCode (
                EnDisOneOfOptionOpCodeHandle,
                STRING_TOKEN(STR_ENABLED_STRING),
                0,
                EFI_IFR_NUMERIC_SIZE_1,
                1 );
        
        // Now create OneOf OpCode...
        HiiCreateOneOfOpCode (
            StartOpCodeHandle,
            (EFI_QUESTION_ID)gAcousticCheckBoxKey,
            gVarstoreId,
            (UINT16)EFI_FIELD_OFFSET(HDD_ACOUSTIC_DEVICE_DATA, AcousticPwrMgmt),
            STRING_TOKEN(STR_ACOUSTIC_SUBTITLE),
            STRING_TOKEN(STR_AUTO_ACOUSTIC_HELP),
            (EFI_IFR_FLAG_CALLBACK | EFI_IFR_FLAG_RESET_REQUIRED),
            EFI_IFR_NUMERIC_SIZE_1,
            EnDisOneOfOptionOpCodeHandle,
            NULL
        );
        
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
        // Create Common Oneof Option Opcode
        HiiCreateOneOfOptionOpCode (
                CommonOneOfOptionOpCodeHandle,
                STRING_TOKEN(STR_BYPASS_STRING),
                (EFI_IFR_OPTION_DEFAULT | EFI_IFR_OPTION_DEFAULT_MFG | EFI_IFR_FLAG_CALLBACK),
                EFI_IFR_NUMERIC_SIZE_1,
                ACOUSTIC_LEVEL_BYPASS );
    
        HiiCreateOneOfOptionOpCode (
                CommonOneOfOptionOpCodeHandle,
                STRING_TOKEN(STR_QUIET_STRING),
                EFI_IFR_FLAG_CALLBACK,
                EFI_IFR_NUMERIC_SIZE_1,
                ACOUSTIC_LEVEL_QUIET );
        
        HiiCreateOneOfOptionOpCode (
                CommonOneOfOptionOpCodeHandle,
                STRING_TOKEN(STR_MAXIMUM_PERFORMANCE_STRING),
                EFI_IFR_FLAG_CALLBACK,
                EFI_IFR_NUMERIC_SIZE_1,
                ACOUSTIC_LEVEL_MAXIMUM_PERFORMANCE );
        
        // Acoustic Level selection
        // Now create OneOf OpCode...
        HiiCreateOneOfOpCode (
            StartOpCodeHandle,
            (EFI_QUESTION_ID) gAcousticCommonLevelKey,
            gVarstoreId,
            (UINT16)EFI_FIELD_OFFSET(HDD_ACOUSTIC_DEVICE_DATA, AcousticLevel),
            STRING_TOKEN(STR_AUTO_ACOUSTIC),
            STRING_TOKEN(STR_AUTO_ACOUSTIC_MODE_HELP),
            EFI_IFR_FLAG_CALLBACK,
            EFI_IFR_NUMERIC_SIZE_1,
            CommonOneOfOptionOpCodeHandle,
            NULL
            );
#endif
        
        Status = pBS->AllocatePool( EfiBootServicesData,
                           StringSize,
                           (VOID**)&String );
        
        if(!EFI_ERROR(Status)) {
            for(Index=0; Index < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Index++) {
                if(AcousticDeviceData->ControllerPresent[Index]) {
                    // Create string with PCI controller's Bus, Dev, Func number
                    if(gHddAcouControllerNameStrIds[Index] == 0) {
                        gHddAcouControllerNameStrIds[Index] = DisplayControllerAddressInfo(Index);
                    }
                    
                    if(gHddAcouControllerNameStrIds[Index] == 0) {
                        UnicodeSPrint(String, StringSize, L"SATA Controller %d", Index);
                        gHddAcouControllerNameStrIds[Index] = HddAcousticHiiAddString(gAcousticHiiHandle, String);
                    }
                
                    // Add goto control
                    HiiCreateGotoOpCode (
                            StartOpCodeHandle,
                            ACOUSTIC_SUB_FORM_ID,
                            gHddAcouControllerNameStrIds[Index],
                            gHddAcouControllerNameStrIds[Index],
                            EFI_IFR_FLAG_CALLBACK,
                            (EFI_QUESTION_ID)(gAcousticControllerBaseKey + Index)
                    );
                }
            }
            pBS->FreePool(String);
        }
    } else {
        Status = pBS->AllocatePool( EfiBootServicesData,
                            StringSize,
                           (VOID**)&String );
        ASSERT_EFI_ERROR(Status);
        
        UnicodeSPrint(String, StringSize, L"HDD not found");
        
        gHddNotFound = HddAcousticHiiAddString(gAcousticHiiHandle, String);
        
        HiiCreateSubTitleOpCode(StartOpCodeHandle,
                                gHddNotFound,
                                STRING_TOKEN(STR_EMPTY),
                                0,0);
        if (String!= NULL) {
            pBS->FreePool(String);
        }
    }
    
    // We are done!!
    HiiUpdateForm (
      gAcousticHiiHandle,
      &gAcousticFormSetGuid,
      ACOUSTIC_MAIN_FORM_ID,
      StartOpCodeHandle,
      EndOpCodeHandle
    );
    
    if (StartOpCodeHandle != NULL) {
        HiiFreeOpCodeHandle (StartOpCodeHandle);
        HiiFreeOpCodeHandle (EndOpCodeHandle);
        HiiFreeOpCodeHandle (EnDisOneOfOptionOpCodeHandle);
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
        HiiFreeOpCodeHandle (CommonOneOfOptionOpCodeHandle);
#endif
    }
    
}

/**
    This function initializes the HDD Acoustic IFR contents.

    @param EFI_EVENT Event - Event to signal
    @param VOID* Context - Event specific context

    @retval VOID

**/

VOID
EFIAPI
InitHddAcousticDynamicIfrContents (
        IN EFI_EVENT Event,
        IN VOID *Context
)
{
    EFI_STATUS                  Status;
    UINTN                       VariableSize = 0;
    
    Status = pRS->GetVariable(
                ACOUSTIC_VAR_NAME,
                &gAcousticDeviceGuid,
                NULL,
                &VariableSize,
                AcousticDeviceData 
                );
    
    if(Status == EFI_BUFFER_TOO_SMALL) {

        Status  = pBS->AllocatePool( 
                                     EfiBootServicesData,
                                     VariableSize,
                                     (VOID**)&AcousticDeviceData );
        
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return;
        }
        
        Status = pRS->GetVariable(
                    ACOUSTIC_VAR_NAME,
                    &gAcousticDeviceGuid,
                    NULL,
                    &VariableSize,
                    AcousticDeviceData 
                    );   
        
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            return;
        }
    }
    
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return;
    }

    HddAcousticInitDynamicMainFormContents();
}

/**
    This function is called by Setup browser to perform callback

    @param  EFI_HII_CONFIG_ACCESS_PROTOCOL  *This
    @param  EFI_BROWSER_ACTION              Action
    @param  EFI_QUESTION_ID                 KeyValue
    @param  EFI_IFR_TYPE_VALUE              *Value
    @param  EFI_BROWSER_ACTION_REQUEST      *ActionRequest

    @retval Status

**/
EFI_STATUS 
HddAcousticBrowserCallback(
    IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
    IN EFI_BROWSER_ACTION Action,
    IN EFI_QUESTION_ID KeyValue,
    IN UINT8 Type,
    IN EFI_IFR_TYPE_VALUE *Value,
    OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
)
{
    EFI_STATUS                      Status;
    UINT8                           ControllerNum;
    UINT8                           DeviceNum;
    BOOLEAN                         DisableAcoustic;
    UINT8                           AcousticLevel;
    UINTN                           HandleCount;
    EFI_HANDLE                      *HandleBuffer = NULL;
    HDD_ACOUSTIC_DEVICE_DATA        *DeviceData = NULL;
    
    if((Action != EFI_BROWSER_ACTION_CHANGING) && \
       (Action != EFI_BROWSER_ACTION_DEFAULT_STANDARD)) {
        return EFI_UNSUPPORTED;
    }
        
    if((Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) && \
       (KeyValue != gAcousticCheckBoxKey)) {
        return EFI_UNSUPPORTED;
    }
    

    Status = pBS->LocateHandleBuffer (
                                      ByProtocol,
                                      &gEfiDiskInfoProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer
                                      );
    if (EFI_ERROR(Status)) {
        HandleCount = 0;
    }
    
    if((KeyValue >= 0x200) && (KeyValue < 0x300)) { // Sub Form
        
        ControllerNum = (UINT8)(KeyValue - gAcousticControllerBaseKey);
        HddAcousticInitDynamicSubFormContents(ControllerNum);
        
    } else if((KeyValue >= 0x300) && (KeyValue < 0x400)) { // Device Acoustic Level Oneof
        
        AcousticLevel = Value->u8;
        DeviceNum = (UINT8)(KeyValue - gAcousticDeviceBaseKey);
        Status = SetAcousticLevel(HandleBuffer, HandleCount, AcousticLevel, DeviceNum);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            pBS->FreePool (HandleBuffer);
            return Status;
        }
        
    } else if(KeyValue == 0x10) { // Enable or Disable Acoustic
        
        if(Value->u8) {
            DisableAcoustic = FALSE;
            AcousticLevel = 1;
        } else {
            DisableAcoustic = TRUE;
            AcousticLevel = 0;
        }
        
        // If Load defaults selected, set DisableAcoustic flag
        if(Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
            AcousticLevel = 0;
            DisableAcoustic = TRUE;
        }
        
        Status = AcousticManagementSupport(HandleBuffer, 
                                           HandleCount, 
                                           AcousticLevel, 
                                           DisableAcoustic);
        
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            pBS->FreePool (HandleBuffer);
            return Status;
        }
        
        if(Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
            pBS->FreePool (HandleBuffer);
            return EFI_UNSUPPORTED;
        }
        
    } else if(KeyValue == gAcousticCommonLevelKey){ // Common Acoustic Level
        
        Status = pBS->AllocatePool( EfiBootServicesData, \
                                    sizeof(HDD_ACOUSTIC_DEVICE_DATA), \
                                    (VOID**)&DeviceData );
        ASSERT_EFI_ERROR( Status );
        if (EFI_ERROR(Status)) { 
            return Status;
        }
        
        // Retrieve uncommitted data from Browser
        HiiGetBrowserData(&gAcousticDeviceGuid, 
                          ACOUSTIC_VAR_NAME, 
                          sizeof(HDD_ACOUSTIC_DEVICE_DATA), 
                          (UINT8 *)DeviceData);
        
        // Checking Acoustic enabled or disabled in Setup
        if(DeviceData->AcousticPwrMgmt == 1) {
            AcousticLevel = Value->u8;
            DeviceNum = 0;
            Status = SetAcousticLevel(HandleBuffer, HandleCount, AcousticLevel, DeviceNum);
            if (EFI_ERROR(Status)) {
                ASSERT_EFI_ERROR(Status);
                pBS->FreePool (HandleBuffer);
                pBS->FreePool(DeviceData);
                return Status;
            }
        }
        pBS->FreePool(DeviceData);
        
    } else {
        pBS->FreePool (HandleBuffer);
        return EFI_UNSUPPORTED;
    }
    
    pBS->FreePool (HandleBuffer);
    return EFI_SUCCESS;
}

/**
    This function is the entry point. Registers callback on TSE event to update IFR data.

    @param  EFI_HANDLE          ImageHandle
    @param  EFI_SYSTEM_TABLE    *SystemTable

    @retval Status

**/
EFI_STATUS 
HddAcousticDynamicSetupEntryPoint (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    EFI_STATUS      Status;
    VOID            *SetupRegistration;
    EFI_GUID        SetupEnterGuid = AMITSE_SETUP_ENTER_GUID;
    EFI_EVENT       SetupEnterEvent;
    
    InitAmiLib(ImageHandle, SystemTable);
    
    // Load setup page and update strings
    Status = LoadResources(ImageHandle, sizeof(SetupCallBack) / sizeof(CALLBACK_INFO), SetupCallBack, NULL);
    if (!EFI_ERROR(Status)) {
        // Register callback on TSE event to update IFR data
        RegisterProtocolCallback(
            &SetupEnterGuid, InitHddAcousticDynamicIfrContents,
            NULL, &SetupEnterEvent, &SetupRegistration
        );
        gAcousticHiiHandle = SetupCallBack[0].HiiHandle;
    }

    return Status;
}
