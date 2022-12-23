//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AhciRecovery.c
    Implements EFI_PEI_RECOVERY_BLOCK_IO_PPI for Ahci devices.

**/

#include "AhciRecovery.h"

// PEI Recovery Block I/O PPI
EFI_PEI_PPI_DESCRIPTOR   AhciPpiDescriptor = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiVirtualBlockIoPpiGuid,
    NULL
};

// PEI Recovery Block I/O PPI2
EFI_PEI_PPI_DESCRIPTOR   AhciPpiDescriptor2 = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiVirtualBlockIo2PpiGuid,
    NULL
};

static  EFI_PEI_NOTIFY_DESCRIPTOR gNotifyList = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,    
    &gEfiEndOfPeiSignalPpiGuid,
    NotifyOnAhciRecoveryCapsuleLoaded
};

static EFI_DEVICE_PATH EndOfDevicePathNode = {
    END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
    {sizeof(EFI_DEVICE_PATH),0}
};

//Defining function declaration part for the functions added through ELINK PcieSataControllerInitFuncList
extern PCIE_CONTROLLER_INIT_FUNCTION PCIE_SATA_CONTROLLER_INIT_FUNC_LIST EndOfPcieControllerInitFunctions;

PCIE_CONTROLLER_INIT_FUNCTION *gPcieControllerInitFunction[] = {
        PCIE_SATA_CONTROLLER_INIT_FUNC_LIST NULL
};

EDKII_IOMMU_PPI      *gEdk2IoMmuPpi = NULL;

/**
    Returns the Device Info from List
       
    @param  AhciBlkIoDev 
    @param  DeviceIndex    

    @retval AHCI_RECOVERY_DEVICE_INFO*
    
**/
AHCI_RECOVERY_DEVICE_INFO *
GetDeviceInfoFromList (
     IN AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev,
     IN UINTN                       DeviceIndex
)
{
    LIST_ENTRY                 *LinkData;
    AHCI_RECOVERY_DEVICE_INFO  *DeviceInfo;
    UINT16                      Index = 1;
    
    for(LinkData = AhciBlkIoDev->DeviceList.ForwardLink;
        LinkData != &AhciBlkIoDev->DeviceList;
        LinkData = LinkData->ForwardLink) {
        
        DeviceInfo = BASE_CR(LinkData, AHCI_RECOVERY_DEVICE_INFO, Link);
        if (Index == DeviceIndex) {
            return DeviceInfo;
        }
        Index++;
    }
    return NULL;
}

/**
    GetNumberOfBlockDevices function of EFI_PEI_RECOVERY_BLOCK_IO2_PPI.
    This Returns the number of Block Devices present in the System.

    @param PeiServices 
    @param This 

    @retval NumberBlockDevices

**/
EFI_STATUS
EFIAPI
AhciGetNumberOfBlockDevices2 (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI  *This,
    OUT UINTN                           *NumberBlockDevices
)
{
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev = NULL;
    EFI_STATUS                  Status;

    if (This == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    AhciBlkIoDev = BASE_CR(This ,AHCI_RECOVERY_BLK_IO_DEV, RecoveryBlkIo2);

    Status = AhciGetNumberOfBlockDevices( PeiServices, 
                                          &AhciBlkIoDev->RecoveryBlkIo, 
                                          NumberBlockDevices );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    DEBUG ((DEBUG_BLKIO, "\n AhciGetNumberOfBlockDevices2 - Number of Ahci Devices found :%x\n",AhciBlkIoDev->DeviceCount ));
    *NumberBlockDevices = AhciBlkIoDev->DeviceCount;

    return EFI_SUCCESS;
}

/**
    GetNumberOfBlockDevices function of EFI_PEI_RECOVERY_BLOCK_IO_PPI.
    This Returns the number of Block Devices present in the System.

    @param PeiServices 
    @param This 

    @retval NumberBlockDevices

**/
EFI_STATUS
EFIAPI
AhciGetNumberOfBlockDevices (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI   *This,
    OUT UINTN                           *NumberBlockDevices
)
{
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev = NULL;
    EFI_STATUS                  Status;
    
    if (This == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    AhciBlkIoDev = (AHCI_RECOVERY_BLK_IO_DEV*)This;

    if (!AhciBlkIoDev->HaveEnumeratedDevices) {
        Status =  AhciEnumerateDevices( PeiServices, AhciBlkIoDev);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        AhciBlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    DEBUG ((DEBUG_BLKIO, "\n AhciGetNumberOfBlockDevices - Number of Ahci Devices found :%x\n",AhciBlkIoDev->DeviceCount ));
    *NumberBlockDevices = AhciBlkIoDev->DeviceCount;

    return EFI_SUCCESS;
}

/** 
    GetBlockDeviceMediaInfo function of EFI_PEI_RECOVERY_BLOCK_IO2_PPI.
    This returns the Block IO Media Information.

    @param PeiServices 
    @param This 
    @param DeviceIndex 

    @retval MediaInfo

**/
EFI_STATUS
EFIAPI
AhciGetBlockDeviceMediaInfo2 (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI  *This,
    IN  UINTN                           DeviceIndex,
    OUT EFI_PEI_BLOCK_IO2_MEDIA         *MediaInfo
)
{
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev     = NULL;
    AHCI_RECOVERY_DEVICE_INFO   *AhciRecDeviceInfo = NULL;
    EFI_STATUS                  Status;
    
    // As per PI spec, DeviceIndex is a number from one to Number of BlockDevices
    if ((This == NULL) || !DeviceIndex || (MediaInfo == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    AhciBlkIoDev = BASE_CR(This ,AHCI_RECOVERY_BLK_IO_DEV, RecoveryBlkIo2);
    
    AhciRecDeviceInfo = GetDeviceInfoFromList(AhciBlkIoDev,DeviceIndex);
    if (AhciRecDeviceInfo == NULL) {
        return EFI_NOT_FOUND;
    }
    
    if ( !AhciBlkIoDev->HaveEnumeratedDevices ) {
        Status = AhciGetBlockDeviceMediaInfo(PeiServices, 
                                              &AhciBlkIoDev->RecoveryBlkIo,
                                              DeviceIndex, 
                                              &AhciRecDeviceInfo->MediaInfo);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    CopyMem(MediaInfo, &AhciRecDeviceInfo->MediaInfo2, sizeof(EFI_PEI_BLOCK_IO2_MEDIA));
    return EFI_SUCCESS;
}

/**
    GetBlockDeviceMediaInfo function of EFI_PEI_RECOVERY_BLOCK_IO_PPI.
    This returns the Block IO Media Information.

    @param PeiServices 
    @param This 
    @param DeviceIndex 

    @retval MediaInfo

**/
EFI_STATUS
EFIAPI
AhciGetBlockDeviceMediaInfo (
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI   *This,
    IN  UINTN                           DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA          *MediaInfo
)
{
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev = NULL;
    AHCI_RECOVERY_DEVICE_INFO   *AhciRecDeviceInfo;
    EFI_STATUS                  Status;

    if (!DeviceIndex || (This == NULL) || (MediaInfo == NULL)) {
        return EFI_INVALID_PARAMETER;
    }

    AhciBlkIoDev = (AHCI_RECOVERY_BLK_IO_DEV*)This;
    
    if ( !AhciBlkIoDev->HaveEnumeratedDevices ) {
        Status = AhciEnumerateDevices( PeiServices, AhciBlkIoDev);
        if ( EFI_ERROR( Status )) {
            return Status;                 
        }
        AhciBlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    // As per PI spec, DeviceIndex is a number from one to Number of BlockDevices
    if (DeviceIndex > (AhciBlkIoDev->DeviceCount)) {
        return EFI_INVALID_PARAMETER;
    }
	
    AhciRecDeviceInfo = GetDeviceInfoFromList(AhciBlkIoDev,DeviceIndex);
    if (AhciRecDeviceInfo == NULL) {
        return EFI_NOT_FOUND;
    }
    
    if ( !AhciRecDeviceInfo->LookedForMedia ) {
        if (AhciRecDeviceInfo->RecoveryDeviceType  == ATAPI) {
            DetectAtapiMedia(AhciRecDeviceInfo);
        }
        AhciRecDeviceInfo->LookedForMedia = TRUE;
    }

    CopyMem(MediaInfo, &AhciRecDeviceInfo->MediaInfo, sizeof(EFI_PEI_BLOCK_IO_MEDIA));
    return EFI_SUCCESS;
}

/**
    ReadBlocks function of EFI_PEI_RECOVERY_BLOCK_IO2_PPI.

    @param  PeiServices
    @param  This
    @param  DeviceIndex
    @param  StartLba
    @param  BufferSize

    @retval Buffer

**/
EFI_STATUS
EFIAPI
AhciReadBlocks2 (
    IN  EFI_PEI_SERVICES                 **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI   *This,
    IN  UINTN                            DeviceIndex,
    IN  EFI_PEI_LBA                      StartLba,
    IN  UINTN                            BufferSize,
    OUT VOID                             *Buffer
)
{
    EFI_STATUS                  Status;
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev = NULL;

    // As per PI spec, DeviceIndex is a number from one to Number of BlockDevices
    if (This == NULL || !DeviceIndex) {
        return EFI_INVALID_PARAMETER;
    }
   
    AhciBlkIoDev = BASE_CR(This ,AHCI_RECOVERY_BLK_IO_DEV, RecoveryBlkIo2);
    
    Status = AhciReadBlocks( PeiServices, 
                             &AhciBlkIoDev->RecoveryBlkIo, 
                             DeviceIndex,
                             StartLba, 
                             BufferSize, 
                             Buffer);

    DEBUG (( DEBUG_BLKIO, "Ahci_ReadBlocks2 Status :%x", Status ));
    return Status;
}

/**   
    ReadBlocks function of EFI_PEI_RECOVERY_BLOCK_IO_PPI.

    @param  PeiServices
    @param  This
    @param  DeviceIndex
    @param  StartLba
    @param  BufferSize

    @retval Buffer

**/
EFI_STATUS
EFIAPI
AhciReadBlocks (
    IN  EFI_PEI_SERVICES                 **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI    *This,
    IN  UINTN                            DeviceIndex,
    IN  EFI_PEI_LBA                      StartLba,
    IN  UINTN                            BufferSize,
    OUT VOID                             *Buffer
)
{
    EFI_PEI_BLOCK_IO_MEDIA      MediaInfo;
    UINTN                       NumberOfBlocks;
    EFI_PHYSICAL_ADDRESS        DeviceAddress;
    EFI_STATUS                  Status             = EFI_SUCCESS;
    UINTN                       BlockSize          = 0;
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev     = NULL;
    AHCI_RECOVERY_DEVICE_INFO   *AhciRecDeviceInfo = NULL;
    VOID                        *Mapping           = NULL;
    
    // As per PI spec, DeviceIndex is a number from one to Number of BlockDevices
    if ( This == NULL || !DeviceIndex || Buffer == NULL ) {
        return EFI_INVALID_PARAMETER;
    }

    AhciBlkIoDev = (AHCI_RECOVERY_BLK_IO_DEV*)This;

    if (BufferSize == 0) {
        return EFI_SUCCESS;
    }

    if ( !AhciBlkIoDev->HaveEnumeratedDevices ) {
        Status = AhciEnumerateDevices( PeiServices, AhciBlkIoDev);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        AhciBlkIoDev->HaveEnumeratedDevices = TRUE;
    }
    
    ZeroMem(&MediaInfo,sizeof(EFI_PEI_BLOCK_IO_MEDIA));
    
    AhciRecDeviceInfo = GetDeviceInfoFromList(AhciBlkIoDev,DeviceIndex);
    if (AhciRecDeviceInfo == NULL) {
       return EFI_NOT_FOUND;
    }

    if ( !AhciRecDeviceInfo->LookedForMedia ) {
        Status = AhciGetBlockDeviceMediaInfo(
                                    PeiServices,
                                    This,
                                    DeviceIndex,
                                    &MediaInfo
                                    );

        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else{
        CopyMem (&MediaInfo, &(AhciRecDeviceInfo->MediaInfo), sizeof(EFI_PEI_BLOCK_IO_MEDIA));
    }

    BlockSize = MediaInfo.BlockSize;
    if(BlockSize == 0){
        return EFI_NO_MEDIA;
    }
    if ( BufferSize % BlockSize != 0 ) {
        return EFI_INVALID_PARAMETER;
    }

    if ( !MediaInfo.MediaPresent ) {
        return EFI_NO_MEDIA;
    }
    
    if (gEdk2IoMmuPpi) {
        Status = gEdk2IoMmuPpi->Map(gEdk2IoMmuPpi,
                                   EdkiiIoMmuOperationBusMasterWrite,
                                   Buffer,
                                   &BufferSize,
                                   &DeviceAddress,
                                   &Mapping
                                  );

        if (EFI_ERROR(Status)){
            return Status;
        }

        Buffer = (VOID*)(UINTN)DeviceAddress;
    }

    // Pass the Parameters
    if(  AhciRecDeviceInfo->RecoveryDeviceType == ATA ) {
        NumberOfBlocks = BufferSize / BlockSize;
        if ((StartLba > MediaInfo.LastBlock) || ((StartLba + NumberOfBlocks) > (MediaInfo.LastBlock + 1))) {
            if (Mapping){
                gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, Mapping);    
            }
            return EFI_INVALID_PARAMETER;
        }
        // Read the Data from Ata devices.     
        Status = AhciAtaReadSectors(
                                AhciRecDeviceInfo,
                                Buffer,
                                BufferSize,
                                StartLba,
                                BlockSize);
    } else {
        Status = AhciAtapiReadSectors(
                                AhciRecDeviceInfo,
                                Buffer,
                                BufferSize,
                                StartLba,
                                BlockSize);
    }
    
    if (Mapping){
        gEdk2IoMmuPpi->Unmap(gEdk2IoMmuPpi, Mapping);    
    }

    DEBUG (( DEBUG_BLKIO, "Ahci_ReadBlocks Status :%x", Status ));
    return Status;
}

/** 
    Description : Enumerates Ata or Atapi devices.
    
    @param  PeiServices
    @param  AhciBlkIoDev

    @retval EFI_STATUS
    
**/

EFI_STATUS
AhciEnumerateDevices (
    IN  EFI_PEI_SERVICES            **PeiServices,
    IN  AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev
)
{
    AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo;
    AMI_PEI_PCI_ENUMERATION_PPI     *PeiPciEnumerationPpi;
    AMI_PEI_PCI_CLASSCODE           PciClassCode;
    AMI_PEI_PCI_DEVICE_LOCATION     PeiPciDevLocation;
    UINT8                           DeviceInstance = 0;
    UINTN                           PciAddr;
    UINT32                          BaseAddr;
    UINT32                          Index;
    EFI_STATUS                      Status;
    UINT16                          VendorId;
    
    // Initializing the list to store the Ahci device details
    InitializeListHead (&AhciBlkIoDev->DeviceList);
    
    Status = PeiServicesLocatePpi(
                        &gEdkiiIoMmuPpiGuid, 
                        0, 
                        NULL, 
                        (VOID**)&gEdk2IoMmuPpi);
    DEBUG((DEBUG_INFO, "Locate gEdkiiIoMmuPpiGuid Status - %r\n", Status));
    
    Status = PeiServicesLocatePpi( 
                        &gAmiPeiPciEnumerationPpiGuid, 
                        0, 
                        NULL, 
                        (VOID**)&PeiPciEnumerationPpi);
    DEBUG((DEBUG_INFO, "Locate PeiPciEnumerationPpi Status - %r\n", Status));
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    
    Status = PeiPciEnumerationPpi->InitDevices(PeiPciEnumerationPpi);
    if ( EFI_ERROR( Status )) {
        return Status;
    }
        
    PciClassCode.BaseClassCode = AHCI_CLASS_CODE;
    PciClassCode.SubClassCode =  AHCI_SUBCLASS_CODE;
    PciClassCode.ProgrammingInterface = AHCI_HBA_PI;  
    
    do {
        Status = PeiPciEnumerationPpi->GetNextDeviceByClassCode(
                                                    PeiPciEnumerationPpi, 
                                                    PciClassCode,
                                                    DeviceInstance,
                                                    &PeiPciDevLocation );
            
        if ( EFI_ERROR( Status )) {
            break;
        } 
        
        PciAddr = PCI_LIB_ADDRESS(PeiPciDevLocation.BusNumber,
                                  PeiPciDevLocation.DeviceNumber,
                                  PeiPciDevLocation.FunctionNumber,
                                  0);

        BaseAddr = PciRead32(PciAddr + ABAR_OFFSET);
        VendorId = PciRead16(PciAddr + PCI_VENDOR_ID_OFFSET);

        AhciControllerInfo = AllocateZeroPool ( sizeof(AHCI_RECOVERY_CONTROLLER_INFO));
        if (AhciControllerInfo == NULL) {
            return EFI_OUT_OF_RESOURCES;
        }

        AhciControllerInfo->AhciBaseAddress = (UINT64)BaseAddr;
        // Mask don't care bits for Mmio base address 
        AhciControllerInfo->AhciBaseAddress &= ~0x0F;
        AhciControllerInfo->BusNumber = PeiPciDevLocation.BusNumber;
        AhciControllerInfo->Device = PeiPciDevLocation.DeviceNumber;
        AhciControllerInfo->Function = PeiPciDevLocation.FunctionNumber;
        DEBUG((DEBUG_VERBOSE,"SATA controller Found @B[0x%x]:D[0x%x]:F[0x%x], BaseAddress:%x \n",
                            AhciControllerInfo->BusNumber,
                            AhciControllerInfo->Device,
                            AhciControllerInfo->Function,
                            AhciControllerInfo->AhciBaseAddress));
        
        AhciControllerInfo->DevPath = PeiDPCopy(PeiPciDevLocation.DevicePath);

        DeviceInstance++;
        
        for(Index = 0; gPcieControllerInitFunction[Index] != NULL; Index++) {                            
            gPcieControllerInitFunction[Index] (PciAddr,VendorId);               
       }  
           
       ConfigureDevices(AhciControllerInfo, AhciBlkIoDev);
       
    } while(!EFI_ERROR(Status));
    
    // Register a Notification function that free Up the resources allocated for Controller at the End of PEI phase
    Status = PeiServicesNotifyPpi (&gNotifyList);
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR (Status);
        return Status;
    }

    return EFI_SUCCESS;
}

/**
    Creates a SATA device device path and adds it to AhciRecDeviceInfo
        
    @param AhciRecDeviceInfo 
    @param AhciControllerInfo 

    @retval EFI_STATUS
    
**/
EFI_STATUS
CreateSataDevicePath (
    IN   AHCI_RECOVERY_DEVICE_INFO       *AhciRecDeviceInfo,
    IN   AHCI_RECOVERY_CONTROLLER_INFO   *AhciControllerInfo
)
{
    SATA_DEVICE_PATH    SataDevicePath;
    
    SataDevicePath.Header.Type = MESSAGING_DEVICE_PATH;
    SataDevicePath.Header.SubType = MSG_SATA_DP;
    SataDevicePath.Header.Length[0] = (UINT8)sizeof(SATA_DEVICE_PATH);
    SataDevicePath.Header.Length[1] = (UINT8)(sizeof(SATA_DEVICE_PATH) >> 8);
    SataDevicePath.HBAPortNumber = AhciRecDeviceInfo->PortNo;
    SataDevicePath.PortMultiplierPortNumber = AhciRecDeviceInfo->PMPortNo == 0xFF ? 0xFFFF : AhciRecDeviceInfo->PMPortNo;
    SataDevicePath.Lun = 0;

    AhciRecDeviceInfo->DevicePath = PeiDPAddNode (AhciControllerInfo->DevPath,&(SataDevicePath.Header));
    return EFI_SUCCESS;

}

/**
    This function configures and initializes the device.

    @param  AhciRecDeviceInfo 
    @param  AhciBlkIoDev

    @retval Status

**/
EFI_STATUS
ConfigureDevices (
    IN   AHCI_RECOVERY_CONTROLLER_INFO *AhciControllerInfo,
    IN   AHCI_RECOVERY_BLK_IO_DEV      *AhciBlkIoDev
)
{
    UINT32                          PortEnumeration;     // Bit Map
    UINT8                           CurrentPort = 0, CurrentPMPort = 0xFF;
    EFI_STATUS                      Status;
    
    // Initialize the SATA Controller
    Status = AhciInitController(AhciControllerInfo);
    
    AhciControllerInfo->HBAPortImplemented = HBA_REG32(AhciControllerInfo->AhciBaseAddress, HBA_PI);
    if (!AhciControllerInfo->HBAPortImplemented) {
        return EFI_NOT_FOUND;
    }
    
    PortEnumeration = AhciControllerInfo->HBAPortImplemented;
   //--------------------------------------------------------------------------
   //  Detection and Configuration starts
   //--------------------------------------------------------------------------
   for ( CurrentPort = 0 ; PortEnumeration != 0 ; PortEnumeration >>= 1, CurrentPort++, CurrentPMPort = 0xFF) {

       if(!(PortEnumeration & 1)) {
            continue;
       }

       // Check if the current port is implemented or not?
       Status = CheckPortImplemented(AhciControllerInfo, CurrentPort);
       if (EFI_ERROR(Status)) {
           continue;
       }

       // Detect and Configure the ATA and ATAPI devices
       Status = DetectAndConfigureDevice(AhciBlkIoDev, AhciControllerInfo, CurrentPort, CurrentPMPort);
       DEBUG ((DEBUG_INFO, "\nDetectAndConfigureDevice Status at Port:%x and PMPort:%x is %r\n", CurrentPort,CurrentPMPort, Status)); 
    }
   
    return EFI_SUCCESS;
}
/**   
    This routine resets the Ahci Controller on end of Pei when
    Ahci Recovery Capsule Loaded.

    @param PeiServices 
    @param NotifyDesc 
    @param InvokePpi 

    @retval EFI_SUCCESS
    
**/
EFI_STATUS
EFIAPI
NotifyOnAhciRecoveryCapsuleLoaded (
    IN  EFI_PEI_SERVICES            **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDesc,
    IN  VOID                        *InvokePpi
)
{
    EFI_STATUS                       Status;
    AMI_PEI_PCI_ENUMERATION_PPI      *PeiPciEnumerationPpi = NULL;
    
    Status = PeiServicesLocatePpi(&gAmiPeiPciEnumerationPpiGuid, 
                                  0, 
                                  NULL, 
                                  (VOID**)&PeiPciEnumerationPpi);
    if ( EFI_ERROR( Status )) {
        DEBUG((DEBUG_INFO, "AhciRecovery %a(): gAmiPeiPciEnumerationPpiGuid Not Found\n", __FUNCTION__));
        return Status;
    }
        
    Status = PeiPciEnumerationPpi->ResetDeviceResources(PeiPciEnumerationPpi);
    DEBUG((DEBUG_INFO, "AhciRecovery %a(): ResetDeviceResources: %r.\n", __FUNCTION__, Status));
    
    return Status;
}
/**
    PeiDPCopy copies the user provided device path into a new buffer and
    returns its address.
    
    @param  DevicePath
    
    @retval Address of the new copy of DevicePath
    
**/
VOID* 
PeiDPCopy (
    EFI_DEVICE_PATH *DevicePath
)
{
    UINTN Length;
    UINT8 *NewDp = NULL;
    
    if (!DevicePath) {
        return NULL;
    }
    
    Length = PeiDPLength(DevicePath);
    if(!Length) {
        return NULL;
    }
    
    NewDp = AllocateZeroPool(Length);            
    CopyMem(NewDp, DevicePath, Length);
    
    return NewDp;
}

/**  
    PeiDPLength Finds length of the provided device path, 
    
    @param  DevicePath
     
    @retval Size of the device path, including EndOfDevicePath.

 **/
UINTN 
PeiDPLength (
    IN EFI_DEVICE_PATH *DevicePath
)
{
    UINTN Size = 0;
    UINTN Length;

    if (DevicePath == NULL) {
        return 0;
    }
    
    for( ; !(isEndNode(DevicePath) && DevicePath->SubType==END_ENTIRE_SUBTYPE) ; 
            DevicePath = NEXT_NODE(DevicePath)) {
        
        Length = NODE_LENGTH(DevicePath);
        
        // Protection from the junk data.
        // Zero type and zero length are illegal.
        // If we encountered them, return
        if (!DevicePath->Type || !Length) {
            return Size;
        } 
        Size += Length;
    }
    
    return Size + sizeof(EFI_DEVICE_PATH); // add size of END_DEVICE_PATH node
}

/**   
    PeiDpAddNode adds the very first element of pDp2 to pDp1 just 
    before its device path terminator. 

    @param  pDp1
    @param  pDp2
    
    @retval Address of the newly allocated modified device path
    
    @note
    1.pDp1 is the device path to be appended to pDp2
    2.Device Path read from pDp2, and its very first element will be 
      appended to pDp1.
      
**/
VOID* 
PeiDPAddNode (
    IN EFI_DEVICE_PATH *pDp1, 
    IN EFI_DEVICE_PATH *pDp2
)
{
    UINTN               DpLength;
    UINT8               *NewDp, *TempDp;
        
    if (!pDp2) {
        return (pDp1) ? PeiDPCopy(pDp1) : PeiDPCopy(&EndOfDevicePathNode);
    }
    
    DpLength = pDp1 ? PeiDPLength(pDp1) - sizeof(EFI_DEVICE_PATH) : 0;
    
    NewDp = AllocateZeroPool((DpLength + NODE_LENGTH(pDp2) + sizeof(EFI_DEVICE_PATH)));
    TempDp = NewDp;

    if (DpLength) { 
        CopyMem ( TempDp, pDp1, DpLength); 
        TempDp += DpLength; 
    }
    
    CopyMem ( TempDp, pDp2, NODE_LENGTH(pDp2)); 
    TempDp += NODE_LENGTH(pDp2);
    
    CopyMem(TempDp, &EndOfDevicePathNode, sizeof(EndOfDevicePathNode));
    
    return NewDp;
}

/**
    Installs EFI_PEI_RECOVERY_BLOCK_IO_PPI for ATA devices. 
   
    @retval EFI_OUT_OF_RESOURCES   Memory allocation failed due to a lack of resources.
    @retval EFI_SUCCESS            EFI_PEI_RECOVERY_BLOCK_IO_PPI installed successfully.
    @retval EFI_INVALID_PARAMETER  The PpiList pointer is NULL, or any of the PEI PPI descriptors in the 
                                   list do not have the EFI_PEI_PPI_DESCRIPTOR_PPI bit set in the Flags field.
**/
EFI_STATUS
EFIAPI
InstallPeiRecoveryBlkIoPpi ()
{
    AHCI_RECOVERY_BLK_IO_DEV    *AhciBlkIoDev  = NULL;
    static   BOOLEAN            RecoveryBlockIoPpiInstalled = FALSE;
    EFI_STATUS                  Status;

    if(RecoveryBlockIoPpiInstalled) {
        return EFI_SUCCESS;
    }
    
    AhciBlkIoDev = AllocateZeroPool(sizeof(AHCI_RECOVERY_BLK_IO_DEV));
    if ( AhciBlkIoDev == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    AhciBlkIoDev->HaveEnumeratedDevices = FALSE;
    AhciBlkIoDev->DeviceCount           = 0;
    AhciBlkIoDev->AmiExtSig             = AMI_EXTENSION_SIGNATURE;
     
    AhciBlkIoDev->RecoveryBlkIo.GetNumberOfBlockDevices = AhciGetNumberOfBlockDevices;
    AhciBlkIoDev->RecoveryBlkIo.GetBlockDeviceMediaInfo = AhciGetBlockDeviceMediaInfo;
    AhciBlkIoDev->RecoveryBlkIo.ReadBlocks              = AhciReadBlocks;
    AhciPpiDescriptor.Ppi = &AhciBlkIoDev->RecoveryBlkIo;
    
    Status = PeiServicesInstallPpi( &AhciPpiDescriptor );
    ASSERT_EFI_ERROR (Status );

    // Install Virtual Block Io PPI for Ahci Recovery
    AhciBlkIoDev->RecoveryBlkIo2.GetNumberOfBlockDevices = AhciGetNumberOfBlockDevices2;
    AhciBlkIoDev->RecoveryBlkIo2.GetBlockDeviceMediaInfo = AhciGetBlockDeviceMediaInfo2;
    AhciBlkIoDev->RecoveryBlkIo2.ReadBlocks              = AhciReadBlocks2;
    AhciPpiDescriptor2.Ppi = &AhciBlkIoDev->RecoveryBlkIo2;

    Status = PeiServicesInstallPpi( &AhciPpiDescriptor2 );  
    ASSERT_EFI_ERROR (Status );
    RecoveryBlockIoPpiInstalled = TRUE;
    
    return Status;
}
/**
    Entry Point for AhciRecovery,Installs EFI_PEI_RECOVERY_BLOCK_IO_PPI for AHCI devices.

    @param  FileHandle
    @param  PeiServices

    @retval EFI_STATUS

**/
EFI_STATUS 
EFIAPI
AhciRecoveryPeimEntry (
    IN  EFI_PEI_FILE_HANDLE     FileHandle,
    IN  CONST EFI_PEI_SERVICES  **PeiServices
)
{
  
    EFI_STATUS      Status;
    
    // Install Virtual Block Io PPI for Ahci Recovery
    Status = InstallPeiRecoveryBlkIoPpi();
 
    return Status;
}
