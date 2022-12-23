//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file Acoustic.c
    Initialize and provide a protocol for the Acoustic support.

**/

//---------------------------------------------------------------------------

#include "Acoustic.h"

//---------------------------------------------------------------------------

EFI_GUID gHddAcousticInitProtocolGuid = AMI_HDD_ACOUSTIC_INIT_PROTOCOL_GUID;
EFI_GUID gAcousticDeviceGuid = HDD_ACOUSTIC_DEVICE_GUID;
AMI_HDD_ACOUSTIC_INIT_PROTOCOL *gHddAcousticInitProtocol;

/**
    Gets controller's bus, device and function number.

    @param BusInterface 
    @param BusInterfaceType
    @param ControllerNum 
    @param PortNum 
    @param DeviceData 

    @retval EFI_STATUS
**/
EFI_STATUS
GetControllerInfo (
    IN  VOID                          *BusInterface,
    AMI_STORAGE_BUS_INTERFACE         BusInterfaceType,
    OUT UINT8                         *ControllerNum,
    OUT UINT8                         *PortNum,
    IN OUT HDD_ACOUSTIC_DEVICE_DATA   *DeviceData
)
{
    EFI_STATUS            Status;
    UINTN                 SegNum;
    UINTN                 BusNum;
    UINTN                 DevNum;
    UINTN                 FuncNum;
    UINT8                 Index;
    EFI_PCI_IO_PROTOCOL   *PciIo = NULL;
    
#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) 
    AMI_IDE_BUS_PROTOCOL  *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
#endif
    
#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
    SATA_DEVICE_INTERFACE *SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;
#endif

    if ( BusInterfaceType == AmiStorageInterfaceIde ) { // IDE Mode
#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) 
        PciIo      = IdeBusInterface->PciIO;
        *PortNum   = IdeBusInterface->IdeDevice.Channel + \
                            (IdeBusInterface->IdeDevice.Device*2);
#endif
    } else if ( BusInterfaceType == AmiStorageInterfaceAhci ) { // AHCI Mode
#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
        PciIo       = SataDevInterface->AhciBusInterface->PciIO;
        *PortNum    = SataDevInterface->PortNumber;
#endif
    }

    // Retrieves PCI controller's PCI bus, device and function number.
    Status = PciIo->GetLocation( PciIo, &SegNum, &BusNum, &DevNum, &FuncNum );

    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    // Checking for controller presence
    for(Index=0; Index < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Index++) {
        if ((DeviceData->BusNum[Index] == (UINT8)BusNum) && \
            (DeviceData->DevNum[Index] == (UINT8)DevNum) && \
            (DeviceData->FunNum[Index] == (UINT8)FuncNum)&& \
            (DeviceData->ControllerPresent[Index] == 1)) {
            break;
        }
    }
    
    // If controller not present, store bus, device and function number
    if( Index == ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED ) {
        for(Index=0; Index < ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED; Index++) {
            if ((DeviceData->BusNum[Index] == 0) && \
                (DeviceData->DevNum[Index] == 0) && \
                (DeviceData->FunNum[Index] == 0) && \
                (DeviceData->ControllerPresent[Index] == 0)) {
                DeviceData->BusNum[Index] = (UINT8)BusNum;
                DeviceData->DevNum[Index] = (UINT8)DevNum;
                DeviceData->FunNum[Index] = (UINT8)FuncNum;
                DeviceData->ControllerPresent[Index] = 1;
                break;
            }
        }
    }
    
    // Setting SATA Controller's Mode flag
    DeviceData->AcousticModeFlag[Index] = BusInterfaceType ? AmiStorageInterfaceAhci : AmiStorageInterfaceIde;
    *ControllerNum = Index;

    return EFI_SUCCESS;
}


/**
    This function gets control from Bus drivers through 
    AMI_HDD_ACOUSTIC_INIT_PROTOCOL. It checks whether HDD supports 
    acoustic or not. If supports, it stores Vendor Specified Acoustic 
    Level and Current Acoustic Level present in HDD.

    @param  VOID                         *BusInterface
    @param  AMI_STORAGE_BUS_INTERFACE    BusInterfaceType

    @retval Status

**/
EFI_STATUS
EFIAPI
InitHddAcoustic (
    IN VOID                         *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE    BusInterfaceType
)
{
    EFI_STATUS                 Status = 0;
    IDENTIFY_DATA              *IdentifyDriveInfo = NULL;
    UINT8                      ControllerNum = 0;
    UINT8                      PortNum = 0;
    UINT8                      CurrentLevel;
    UINT8                      DeviceNum = 0;
    UINT32                     Attribute = 0;
    UINTN                      DeviceDataSize = 0;
    HDD_ACOUSTIC_DEVICE_DATA   *DeviceData = NULL;

#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) 
    AMI_IDE_BUS_PROTOCOL *IdeBusInterface = (AMI_IDE_BUS_PROTOCOL*)BusInterface;
#endif
    
#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
    SATA_DEVICE_INTERFACE *SataDevInterface = (SATA_DEVICE_INTERFACE*)BusInterface;
#endif
  
    if ( BusInterfaceType == AmiStorageInterfaceAhci ) { // AHCI Mode
#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
        IdentifyDriveInfo = &(SataDevInterface->IdentifyData);
#endif
    } else if ( BusInterfaceType == AmiStorageInterfaceIde ) { // IDE Mode
#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0) 
        IdentifyDriveInfo = &(IdeBusInterface->IdeDevice.IdentifyData);
#endif
    }
    
    Status = pBS->AllocatePool(EfiBootServicesData,
                               sizeof (HDD_ACOUSTIC_DEVICE_DATA),
                               (VOID**)&DeviceData );
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    pBS->SetMem( DeviceData, sizeof(HDD_ACOUSTIC_DEVICE_DATA), 0 );
    
    Status = GetEfiVariable(
                    ACOUSTIC_VAR_NAME,
                    &gAcousticDeviceGuid,
                    &Attribute,
                    &DeviceDataSize,
                    (VOID**)&DeviceData
                    );
    
    if ( EFI_ERROR( Status ) && Attribute == 0) {
        Attribute = (UINT32)(EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
    }
    
    // Gets controller number and stores Controller's details
    Status = GetControllerInfo( BusInterface, 
                                BusInterfaceType, 
                                &ControllerNum, 
                                &PortNum, 
                                DeviceData );
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    // Calculating Device Number
    DeviceNum = (ControllerNum * ACOUSTIC_MAXIMUM_PORT_SUPPORTED) + PortNum;
        
    // Set device present flag
    DeviceData->AcousticDevicePresent[DeviceNum] = 1;

    // Does it support Acoustics?
    if (!(IdentifyDriveInfo->Command_Set_Supported_83 & \
                          AUTOMATIC_ACOUSTIC_FEATURE_SET_SUPPORTED)) { 
        DeviceData->AcousticSupported[DeviceNum] = 0;
    } else {
        // Get the drive's current acoustic value
        CurrentLevel = IdentifyDriveInfo->Acoustic_Level_94 & 0xFF;
        
        // Store vendor specific acoustic level
        DeviceData->VendorAcousticValue[DeviceNum] = \
                            IdentifyDriveInfo->Acoustic_Level_94 >> 8;
        
        // Acoustic is supported by the drive
        DeviceData->AcousticSupported[DeviceNum] = 1;
        
        if(DeviceData->AcousticPwrMgmt != 0) { // If Automatic Acoustic Management enabled
            if(CurrentLevel == ACOUSTIC_LEVEL_QUIET || \
                    CurrentLevel == ACOUSTIC_LEVEL_MAXIMUM_PERFORMANCE) {
                // Store current acoustic level
                DeviceData->AcousticLevelIndv[DeviceNum] = CurrentLevel;
            } else { 
                DeviceData->AcousticLevelIndv[DeviceNum] = \
                                (UINT8)(IdentifyDriveInfo->Acoustic_Level_94 >> 8);
            }
        }
    }
    
    Status = pRS->SetVariable(
            ACOUSTIC_VAR_NAME,
            &gAcousticDeviceGuid,
            Attribute,
            sizeof(HDD_ACOUSTIC_DEVICE_DATA),
            DeviceData
            );
    
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    if (DeviceData) {
        pBS->FreePool(DeviceData);
    }
    return Status;
}

/**
    This routine is the entry point for the Acoustic driver. It
    installs AMI_HDD_ACOUSTIC_INIT_PROTOCOL.

    @param ImageHandle     Handle to this driver image
    @param SystemTable     Pointer to the system table

    @retval EFI_STATUS
**/

EFI_STATUS
EFIAPI
AcousticEntryPoint (
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
)
{
    EFI_STATUS                Status;
    EFI_HANDLE                Handle = NULL;
    HDD_ACOUSTIC_DEVICE_DATA  *DeviceData = NULL;
    UINTN                     DeviceDataSize = 0;
    UINT32                    Attribute = 0;
    UINT8                     EnDisAcoustic = 0;
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
    UINT8                     CommonAcoustic = 0;
#endif

    InitAmiLib( ImageHandle, SystemTable );

    Status = pBS->AllocatePool( EfiBootServicesData,
                                sizeof(AMI_HDD_ACOUSTIC_INIT_PROTOCOL),
                                (VOID**)&gHddAcousticInitProtocol );

    if ( EFI_ERROR( Status )) {
        return Status;
    }

    gHddAcousticInitProtocol->InitHddAcoustic = InitHddAcoustic;
    
    Status = pBS->InstallProtocolInterface(
                        &Handle,
                        &gHddAcousticInitProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        gHddAcousticInitProtocol
                        );
    
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    Status = GetEfiVariable(
                    ACOUSTIC_VAR_NAME,
                    &gAcousticDeviceGuid,
                    &Attribute,
                    &DeviceDataSize,
                    (VOID**)&DeviceData
                    );
    
    if ( !EFI_ERROR( Status )) {
        EnDisAcoustic = DeviceData->AcousticPwrMgmt;
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
        CommonAcoustic = DeviceData->AcousticLevel;
#endif
    } else if ( EFI_ERROR( Status ) && Attribute == 0) {
        Attribute = (UINT32) (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS);
    }
    
    // Clearing HDD_ACOUSTIC_DEVICE_DATA variable
    Status = pBS->AllocatePool(EfiBootServicesData, \
                               sizeof(HDD_ACOUSTIC_DEVICE_DATA),\
                               (VOID**)&DeviceData \
                              );
    
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    pBS->SetMem(DeviceData, sizeof(HDD_ACOUSTIC_DEVICE_DATA),0);
    DeviceData->AcousticPwrMgmt = EnDisAcoustic;
#if !INDIVIDUAL_ACOUSTIC_SUPPORT
    DeviceData->AcousticLevel = CommonAcoustic;
#endif

    Status = pRS->SetVariable(ACOUSTIC_VAR_NAME, 
                              &gAcousticDeviceGuid, \
                              Attribute,\
                              sizeof (HDD_ACOUSTIC_DEVICE_DATA),\
                              DeviceData);
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    if (DeviceData) {
        pBS->FreePool (DeviceData);
    }

    return EFI_SUCCESS;
}
