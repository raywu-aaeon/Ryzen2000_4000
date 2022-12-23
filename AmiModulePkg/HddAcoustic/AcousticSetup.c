//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file AcousticSetup.c
    This file contains functions used by the Acoustic module

**/

//---------------------------------------------------------------------------

#include "Acoustic.h"
#include <Library/HiiLib.h>

//---------------------------------------------------------------------------

#if LOCAL_ACOUSTIC_SETUP
EFI_GUID gAcousticDeviceGuid = HDD_ACOUSTIC_DEVICE_GUID;
HDD_ACOUSTIC_DEVICE_DATA  gAcousticDeviceData;

//
// Add more elements if there are more than 3 controllers
//
STRING_REF DevStrings[ACOUSTIC_DEVICE_COUNT] = {
    STRING_TOKEN(STR_ACOUSTIC_SATA0_PORT0_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA0_PORT1_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA0_PORT2_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA0_PORT3_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA0_PORT4_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA0_PORT5_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_PORT0_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_PORT1_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_PORT2_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_PORT3_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_PORT4_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_PORT5_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_PORT0_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_PORT1_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_PORT2_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_PORT3_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_PORT4_DEVICE_NAME),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_PORT5_DEVICE_NAME)
};

STRING_REF ControllerAddrInfo[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED] = {
    STRING_TOKEN(STR_ACOUSTIC_SATA0_SETTINGS),
    STRING_TOKEN(STR_ACOUSTIC_SATA1_SETTINGS),
    STRING_TOKEN(STR_ACOUSTIC_SATA2_SETTINGS)
};

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

    @param EFI_HII_HANDLE 

    @retval EFI_STATUS

**/
EFI_STATUS
DisplayControllerAddressInfo (
    IN  EFI_HII_HANDLE  HiiHandle
)
{
    UINT8                           Num;
    STRING_REF                      StrRef;
    CHAR8                           *NewString;
    EFI_STATUS                      Status;
    UINTN                           StringSize = 50;
    
    Status = pBS->AllocatePool(EfiBootServicesData, StringSize,(VOID **) &NewString);
    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    for(Num = 0; Num < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Num++) {
        if(gAcousticDeviceData.ControllerPresent[Num] == 1){
            StrRef = ControllerAddrInfo[Num];
            AsciiSPrint(
                    NewString, \
                    StringSize, \
                    "SATA Controller %d - PCI Bus %02X Dev %02X Fun %02X", \
                    Num, \
                    gAcousticDeviceData.BusNum[Num],\
                    gAcousticDeviceData.DevNum[Num],\
                    gAcousticDeviceData.FunNum[Num]);

            InitString(\
                      HiiHandle,\
                      StrRef,\
                      L"%a", \
                      NewString\
                     );
        }            
    }
    
    if(NewString) {
        pBS->FreePool(NewString);
    }
    
    return Status;
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
    
    if(gAcousticDeviceData.AcousticModeFlag[Num] == AmiStorageInterfaceAhci) {  // AHCI Mode
        *PortNum = IdeChannel;
    } else if(gAcousticDeviceData.AcousticModeFlag[Num] == AmiStorageInterfaceIde) { // IDE Mode
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
    if (EFI_ERROR(Status)) {
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
    
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    return Status;
}

/**
    Initialize Acoustic misc configuration strings.

    @param HiiHandle 
    @param Class 

    @retval VOID

**/

VOID 
InitAcousticStrings (
    EFI_HII_HANDLE  HiiHandle, 
    UINT16          Class
)
{
    EFI_STATUS                      Status;
    UINTN                           VariableSize;
    UINT32                          PortNum;
    CHAR8                           *NewString;
    UINT8                           Index;
    UINT8                           Num;
    UINT8                           DeviceNum;
    UINTN                           HandleCount;
    EFI_HANDLE                      *HandleBuffer;
    EFI_HANDLE                      ControllerHandle;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo = NULL;
    EFI_PCI_IO_PROTOCOL             *PciIO;
    IDENTIFY_DATA                   *IdentifyDriveInfo = NULL;
    UINT32                          BufferSize = 0;
    STRING_REF                      Token;
    CHAR8                           ModelNumber[43];
    UINTN                           SegNum;
    UINTN                           BusNum;
    UINTN                           DevNum;
    UINTN                           FuncNum;
    UINT32                          IdeDevice;
    UINT32                          IdeChannel;

    if (Class == ADVANCED_FORM_SET_CLASS) {
        
        VariableSize = sizeof(HDD_ACOUSTIC_DEVICE_DATA);
        
        Status = pRS->GetVariable(ACOUSTIC_VAR_NAME,\
                                 &gAcousticDeviceGuid,\
                                 NULL,\
                                 &VariableSize,\
                                 &gAcousticDeviceData);
        if (EFI_ERROR(Status)) { 
            ASSERT_EFI_ERROR( Status );
            return;
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
        
        // Displays PCI Configuration Address for each SataControllers Configured in SETUP.
        Status = DisplayControllerAddressInfo(HiiHandle);
        if (EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            pBS->FreePool(HandleBuffer);
            return;
        }
        
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
            
            for(Num=0; Num < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Num++) {
                if(gAcousticDeviceData.ControllerPresent[Num] == 0) {
                    continue;
                }
                
                // Checking for correct controller
                if((BusNum == gAcousticDeviceData.BusNum[Num]) && \
                   (DevNum == gAcousticDeviceData.DevNum[Num]) && \
                   (FuncNum == gAcousticDeviceData.FunNum[Num])) {
                    Status = pBS->HandleProtocol (
                                              HandleBuffer[Index],
                                              &gEfiDiskInfoProtocolGuid,
                                              (VOID**)&DiskInfo
                                              );
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR(Status);
                        continue;
                    }

                    Status = DiskInfo->WhichIde (
                                        DiskInfo,
                                        &IdeChannel,
                                        &IdeDevice
                                        );
                    
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR(Status);
                        continue;
                    }
                    
                    // Getting Port Number
                    if(gAcousticDeviceData.AcousticModeFlag[Num] == AmiStorageInterfaceAhci) {  // AHCI Mode
                        PortNum = IdeChannel;
                    } else if(gAcousticDeviceData.AcousticModeFlag[Num] == AmiStorageInterfaceIde) { // IDE Mode
                        IdeDevice = IdeChannel + (IdeDevice * 2);
                        PortNum = IdeDevice;
                    }

                    // Calculating Device Number
                    DeviceNum = (Num * ACOUSTIC_MAXIMUM_PORT_SUPPORTED) + PortNum;
                    Token = DevStrings[DeviceNum];

                    Status = pBS->AllocatePool(EfiBootServicesData, 
                                               sizeof (IDENTIFY_DATA), 
                                               (VOID**)&IdentifyDriveInfo);
                    if(EFI_ERROR(Status)) {
                        ASSERT_EFI_ERROR(Status);
                        continue;
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
                        continue;
                    }
                    
                    // Reading HDD Model Number
                    if(IdentifyDriveInfo != NULL) {
                        UINTN    StringSize = 43;
                        pBS->SetMem(ModelNumber, 42, 0x20);
                        pBS->CopyMem (ModelNumber+2, IdentifyDriveInfo->Model_Number_27, 40);
                        Swap_Entries (ModelNumber+2, 40);
                        ModelNumber[42] = '\0';

                        Status = pBS->AllocatePool(EfiBootServicesData, StringSize, (VOID**)&NewString);
                        if(EFI_ERROR(Status)) {
                            ASSERT_EFI_ERROR(Status);
                            continue;
                        }
                    
                        AsciiSPrint(NewString, StringSize, "%a", ModelNumber);

                        InitString(
                                HiiHandle,
                                Token,
                                L"%a",
                                NewString
                               );

                        pBS->FreePool (IdentifyDriveInfo);
                        IdentifyDriveInfo = NULL;
                        pBS->FreePool (NewString);
                    }
                }
            }
        }
        if (HandleBuffer) {
            pBS->FreePool (HandleBuffer);
        }
    }
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
    
    Status = pBS->HandleProtocol(DeviceHandle, 
                                 &gEfiBlockIoProtocolGuid, 
                                 (VOID**)&BlockIO);

    if (EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return  Status;
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
    if (EFI_ERROR(Status)) { 
        ASSERT_EFI_ERROR( Status );
        return Status;
    }
    
    //
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
        //Get the PCI IO Protocol instance
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
        Status = PciIO->GetLocation(PciIO, &SegNum, &BusNum, &DevNum, &FuncNum);
                    
        if(EFI_ERROR(Status)) {
            ASSERT_EFI_ERROR(Status);
            continue;
        }
        
        for(Num=0; Num < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Num++) {
            if(gAcousticDeviceData.ControllerPresent[Num] == 0) {
                continue;
            }
            
            if((BusNum == gAcousticDeviceData.BusNum[Num]) && \
               (DevNum == gAcousticDeviceData.DevNum[Num]) && \
               (FuncNum == gAcousticDeviceData.FunNum[Num])) {
                // Gets HDD connected port number
                Status = GetPortNumber(HandleBuffer[Index], 
                                       &PortNum, 
                                       Num, 
                                       DiskInfo);
                if(EFI_ERROR(Status)) {
                    ASSERT_EFI_ERROR(Status);
                    break;
                }
                
                DeviceNum = Num * ACOUSTIC_MAXIMUM_PORT_SUPPORTED + PortNum;
                // If HDD not support Acoustic, don't send Acoustic Level to HDD
                if(gAcousticDeviceData.AcousticSupported[DeviceNum] == 0) {
                    break;
                }
                
                if(DisableAcoustic == FALSE) {
                    AcousticLevel = gAcousticDeviceData.VendorAcousticValue[DeviceNum];
                    DeviceData->AcousticLevelIndv[DeviceNum] = ACOUSTIC_LEVEL_BYPASS;
                    AcousticSupport = ACOUSTIC_MANAGEMENT_ENABLE;
                } else {
                    AcousticSupport = ACOUSTIC_MANAGEMENT_DISABLE;
                }
                
                Status = IssueSetFeatureCmd(ControllerHandle,
                                            HandleBuffer[Index],
                                            gAcousticDeviceData.AcousticModeFlag[Num],
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
    This is setup callback function. This function updates Acoustic level 
    of HDD in Setup page.
    
    @param  EFI_HII_HANDLE HiiHandle
    @param  UINT16         Class
    @param  UINT16         SubClass
    @param  UINT16         Key

    @retval EFI_STATUS

**/
EFI_STATUS 
AcousticLevelCallback(
    IN EFI_HII_HANDLE HiiHandle, 
    IN UINT16 Class, 
    IN UINT16 SubClass, 
    IN UINT16 Key
)
{
    EFI_STATUS                      Status = EFI_UNSUPPORTED;
    UINT8                           DeviceNum;
    UINTN                           VariableSize;
    HDD_ACOUSTIC_DEVICE_DATA        AcousticDeviceData;
    EFI_DISK_INFO_PROTOCOL          *DiskInfo = NULL;
    UINT8                           Index;
    UINT8                           Num = 0;
    UINTN                           HandleCount;
    EFI_HANDLE                      *HandleBuffer;
    EFI_HANDLE                      ControllerHandle;
    EFI_PCI_IO_PROTOCOL             *PciIO = NULL;
    UINT32                          PortNum;
    UINTN                           SegNum;
    UINTN                           BusNum;
    UINTN                           DevNum;
    UINTN                           FuncNum;
    CALLBACK_PARAMETERS             *CallbackParameters;
    UINT8                           AcousticLevel;
    BOOLEAN                         DisableAcoustic = FALSE;

    CallbackParameters = GetCallbackParameters();
    if(!CallbackParameters ) {
        return EFI_UNSUPPORTED;
    }
    
    switch(Key) {
    case ACOUSTIC_LEVEL_KEY_00:
        DeviceNum = 0;
        break;
    case ACOUSTIC_LEVEL_KEY_01:
        DeviceNum = 1;
        break;
    case ACOUSTIC_LEVEL_KEY_02:
        DeviceNum = 2;
        break;
    case ACOUSTIC_LEVEL_KEY_03:
        DeviceNum = 3;
        break;
    case ACOUSTIC_LEVEL_KEY_04:
        DeviceNum = 4;
        break;
    case ACOUSTIC_LEVEL_KEY_05:
        DeviceNum = 5;
        break;
    case ACOUSTIC_LEVEL_KEY_06:
        DeviceNum = 6;
        break;
    case ACOUSTIC_LEVEL_KEY_07:
        DeviceNum = 7;
        break;
    case ACOUSTIC_LEVEL_KEY_08:
        DeviceNum = 8;
        break;
    case ACOUSTIC_LEVEL_KEY_09:
        DeviceNum = 9;
        break;
    case ACOUSTIC_LEVEL_KEY_10:
        DeviceNum = 10;
        break;
    case ACOUSTIC_LEVEL_KEY_11:
        DeviceNum = 11;
        break;
    case ACOUSTIC_LEVEL_KEY_12:
        DeviceNum = 12;
        break;
    case ACOUSTIC_LEVEL_KEY_13:
        DeviceNum = 13;
        break;
    case ACOUSTIC_LEVEL_KEY_14:
        DeviceNum = 14;
        break;
    case ACOUSTIC_LEVEL_KEY_15:
        DeviceNum = 15;
        break;
    case ACOUSTIC_LEVEL_KEY_16:
        DeviceNum = 16;
        break;
    case ACOUSTIC_LEVEL_KEY_17:
        DeviceNum = 17;
        break;
    case COMMON_ACOUSTIC_LEVEL_KEY:
        break;
    case DISABLE_ACOUSTIC_KEY:
        if(CallbackParameters->Value->u8 == 0) {
            DisableAcoustic = TRUE;
        } else {
            DisableAcoustic = FALSE;
        }
        break;
    default:
        return Status;
    }
    
    // Checking for Load Defaults
    if(CallbackParameters->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
        AcousticLevel = 0;
    } else if(CallbackParameters->Action != EFI_BROWSER_ACTION_CHANGING ) {
        return EFI_UNSUPPORTED;
    }
    
    VariableSize = sizeof(HDD_ACOUSTIC_DEVICE_DATA);
    Status = pRS->GetVariable(ACOUSTIC_VAR_NAME,\
                             &gAcousticDeviceGuid,\
                             NULL,\
                             &VariableSize,\
                             &AcousticDeviceData);
    if (EFI_ERROR(Status)) { 
        ASSERT_EFI_ERROR( Status );
        return Status;
    }
    
    AcousticLevel = CallbackParameters->Value->u8;
#if INDIVIDUAL_ACOUSTIC_SUPPORT
    if(AcousticLevel == ACOUSTIC_LEVEL_BYPASS) { // If Bypass Acoustic Mode
        AcousticLevel = AcousticDeviceData.VendorAcousticValue[DeviceNum];
    }
#endif
    
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
    
    // If Load defaults selected, set DisableAcoustic flag
    if(CallbackParameters->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
        AcousticLevel = 0;
        DisableAcoustic = TRUE;
    }
    
    if(DisableAcoustic && (AcousticLevel == 0)) { 
        // Disables Acoustic in HDD
        Status = AcousticManagementSupport(HandleBuffer, 
                                           HandleCount, 
                                           AcousticLevel, 
                                           DisableAcoustic);
        if(CallbackParameters->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
            return EFI_UNSUPPORTED;
        } else {
            return Status;
        }
    } else if(!DisableAcoustic && (AcousticLevel == 1)) {
        // Enables Acoustic in HDD
        Status = AcousticManagementSupport(HandleBuffer, 
                                           HandleCount,  
                                           AcousticLevel, 
                                           DisableAcoustic);
        if(CallbackParameters->Action == EFI_BROWSER_ACTION_DEFAULT_STANDARD) {
            return EFI_UNSUPPORTED;
        } else {
            return Status;
        }
    }
    
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
            if(AcousticDeviceData.ControllerPresent[Num] == 0) {
                continue;
            }
            
            if((BusNum == AcousticDeviceData.BusNum[Num]) && \
               (DevNum == AcousticDeviceData.DevNum[Num]) && \
               (FuncNum == AcousticDeviceData.FunNum[Num])) {
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
                if(AcousticDeviceData.AcousticSupported[DeviceNum] == 0) {
                    break;
                }
                
                Status = IssueSetFeatureCmd(ControllerHandle,
                                            HandleBuffer[Index],
                                            AcousticDeviceData.AcousticModeFlag[Num],
                                            ACOUSTIC_MANAGEMENT_ENABLE,
                                            AcousticLevel);
            }
        }
    }
    
    if (HandleBuffer) {
        pBS->FreePool (HandleBuffer);
    }
    return EFI_SUCCESS;
}
#endif
