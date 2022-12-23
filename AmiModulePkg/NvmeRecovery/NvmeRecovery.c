//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file NvmeRecovery.c
    This file contains the code to implement
    EFI_PEI_RECOVERY_BLOCK_IO_PPI for Nvme devices.

**/

#include "NvmeRecovery.h"

// PEI Recovery Block I/O PPI
EFI_PEI_PPI_DESCRIPTOR   NvmeBlockIoPpiDescriptor = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiVirtualBlockIoPpiGuid,
    NULL
};

static EFI_PEI_NOTIFY_DESCRIPTOR gNotifyList = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiEndOfPeiSignalPpiGuid,
    NotifyOnNvmeRecoveryCapsuleLoaded
};

NVME_NAMESPACE_DEVICE_PATH   gPeiNvmePath = { { MESSAGING_DEVICE_PATH,
                                                MSG_NVME_NAMESPACE_DP,
                                                {sizeof( NVME_NAMESPACE_DEVICE_PATH )}
                                              }, 0, 0 
                                            };

static EFI_DEVICE_PATH EndOfDevicePathNode = { END_DEVICE_PATH, END_ENTIRE_SUBTYPE,
                                               {sizeof(EFI_DEVICE_PATH),0}
                                             };

NVME_PCI_DEVICE_INFO  *gNvmePciDeviceInfo[MAX_NVME_RECOVERY_DEVICE];
EDKII_IOMMU_PPI       *gEdk2IoMmuPpi = NULL;

/**
   @internal

    Returns ActiveNameSpace interface based on DeviceIndex
    
    @param NvmeBlkIo
    @param DeviceIndex
    
    @return ACTIVE_NAMESPACE_DATA*

   @endinternal
**/
ACTIVE_NAMESPACE_DATA*
GetActiveNameSpaceDataByIndex (
    IN NVME_RECOVERY_BLK_IO_DEV *NvmeBlkIo,
    IN UINTN                    DeviceIndex
)
{
    UINT16                 Index;
    LIST_ENTRY             *LinkData;
    NVME_CONTROLLER_INFO   *NvmeControllerInfo;
    ACTIVE_NAMESPACE_DATA  *ActiveNameSpaceData;
    UINTN                  DeviceCount = 0;
    
    if(DeviceIndex > NvmeBlkIo->TotalDeviceCount) {
        return NULL;
    }
    
    for(Index = 0; Index < NvmeBlkIo->TotalControllerCount; Index++) {
        
        NvmeControllerInfo = NvmeBlkIo->NvmeControllerInfo[Index];
        
        // Check whether the requested device under this NVMe controller
        if((DeviceCount + NvmeControllerInfo->TotalActiveNameSpaceCount) < DeviceIndex) {
            DeviceCount += NvmeControllerInfo->TotalActiveNameSpaceCount;
            continue;
        }
        
        // If yes, find its index in ActiveNameSpace list
        for (LinkData = NvmeControllerInfo->ActiveNameSpaceList.ForwardLink; 
             LinkData != &NvmeControllerInfo->ActiveNameSpaceList; 
             LinkData = LinkData->ForwardLink) {
            
            ActiveNameSpaceData = BASE_CR(LinkData ,ACTIVE_NAMESPACE_DATA, Link);
            if(++DeviceCount == DeviceIndex) {
                return ActiveNameSpaceData;
            }
        }
    }

    return NULL;
}

/**
    Nvme_GetNumberOfBlockDevices is API function of EFI_PEI_RECOVERY_BLOCK_IO_PPI. 
    This Returns the number of Nvme Block Devices present in the System.
   
    @param  PeiServices 
    @param  This 
    @param  NumberBlockDevices 

    @retval EFI_STATUS

    @note  
        The enumeration will be done to find Nvmedevices if not enumerated already        
   @endinternal
**/
EFI_STATUS
EFIAPI
Nvme_GetNumberOfBlockDevices(
    IN  EFI_PEI_SERVICES              **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    OUT UINTN                         *NumberBlockDevices
)
{
    NVME_RECOVERY_BLK_IO_DEV  *NvmeBlkIoDev = NULL;
    EFI_STATUS                Status;

    if ( !This || !NumberBlockDevices) {
        return EFI_INVALID_PARAMETER;
    }

    NvmeBlkIoDev = (NVME_RECOVERY_BLK_IO_DEV*)This;

    if ( !NvmeBlkIoDev->HaveEnumeratedDevices ) {
        // Enumerate PCI root bridges for Nvme Devices
        Status = EnumerateNvmeDevices( NvmeBlkIoDev );
        if(EFI_ERROR(Status)) {
            return Status;
        }
        NvmeBlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    *NumberBlockDevices = NvmeBlkIoDev->TotalDeviceCount;
    DEBUG((DEBUG_INFO, "Number of block devices - %x\n", NvmeBlkIoDev->TotalDeviceCount));
    return EFI_SUCCESS;
}

/**
    Routine returns the Media information of the Nvme device respective to the 
    NvmeDevice index

    @param  PeiServices 
    @param  This 
    @param  DeviceIndex 
    @param  MediaInfo 

    @retval Status

    @note  
      The enumeration will be done to find Nvmedevices if not enumerated
      already.
**/
EFI_STATUS
EFIAPI
Nvme_GetBlockDeviceMediaInfo (
    IN  EFI_PEI_SERVICES              **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN  UINTN                         DeviceIndex,
    OUT EFI_PEI_BLOCK_IO_MEDIA        *MediaInfo
)
{
    NVME_RECOVERY_BLK_IO_DEV  *NvmeBlkIoDev = NULL;
    EFI_STATUS                Status;
    ACTIVE_NAMESPACE_DATA     *ActiveNameSpaceData;

    // Return error if input parameter is invalid
    if ( !This || !DeviceIndex || !MediaInfo ) {
        return EFI_INVALID_PARAMETER;
    }

    NvmeBlkIoDev = (NVME_RECOVERY_BLK_IO_DEV*)This;

    // Enumerate to find the Nvme Devices if not enumerated.
    if ( !NvmeBlkIoDev->HaveEnumeratedDevices ) {
        Status = EnumerateNvmeDevices( NvmeBlkIoDev );
        if ( EFI_ERROR( Status )) {
            return Status;
        }
        NvmeBlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    // Return error if input Nvme device index is invalid
    // As per PI spec, DeviceIndex is a number from one to Number of BlockDevices
    if( DeviceIndex > NvmeBlkIoDev->TotalDeviceCount ) {
        return EFI_INVALID_PARAMETER;
    }
    
    ActiveNameSpaceData = GetActiveNameSpaceDataByIndex(NvmeBlkIoDev, DeviceIndex);
    if(ActiveNameSpaceData == NULL) {
        return EFI_NOT_FOUND;
    }

    if ( !ActiveNameSpaceData->LookedForMedia ) {
        ActiveNameSpaceData->LookedForMedia = TRUE;
    }

    // Return the Media info of the requested NVME Device.
    CopyMem(MediaInfo, &ActiveNameSpaceData->MediaInfo, sizeof(EFI_PEI_BLOCK_IO_MEDIA));
    return EFI_SUCCESS;
}

/**
    Read Nvme device LBA given as input and stores the data in Buffer
    Total number of LBA to read is calculated from input BufferSize

    @param  PeiServices 
    @param  This 
    @param  DeviceIndex 
    @param  StartLba 
    @param  BufferSize 
    @param  Buffer 

    @retval Status
       Data filled in *Buffer

    @note  
      The enumeration will be done to find Nvme devices if not enumerated
      already.
**/
EFI_STATUS
EFIAPI
Nvme_ReadBlocks (
    IN  EFI_PEI_SERVICES              **PeiServices,
    IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI *This,
    IN  UINTN                         DeviceIndex,
    IN  EFI_PEI_LBA                   StartLba,
    IN  UINTN                         BufferSize,
    OUT VOID                          *Buffer
)
{
    EFI_PEI_BLOCK_IO_MEDIA    MediaInfo;
    EFI_STATUS                Status;
    NVME_RECOVERY_BLK_IO_DEV  *NvmeBlkIoDev = NULL;
    ACTIVE_NAMESPACE_DATA     *ActiveNameSpaceData;
    BOOLEAN                   MediaPresent;

    // Return error if input parameter is invalid
    if ( !This || !DeviceIndex || !Buffer ) {
        return EFI_INVALID_PARAMETER;
    }
    
    NvmeBlkIoDev = (NVME_RECOVERY_BLK_IO_DEV *)This;

    if ( BufferSize == 0 ) {
        return EFI_SUCCESS;
    }

    if ( !NvmeBlkIoDev->HaveEnumeratedDevices ) {
        Status = EnumerateNvmeDevices( NvmeBlkIoDev );
        if ( EFI_ERROR( Status )) {
            return Status;
        }
        NvmeBlkIoDev->HaveEnumeratedDevices = TRUE;
    }

    // Return error if input Nvme device index is invalid
    // As per PI spec, DeviceIndex is a number from one to Number of BlockDevices
    if( DeviceIndex > NvmeBlkIoDev->TotalDeviceCount ) {
        return EFI_INVALID_PARAMETER;
    }
    
    ActiveNameSpaceData = GetActiveNameSpaceDataByIndex(NvmeBlkIoDev, DeviceIndex);
    if(ActiveNameSpaceData == NULL) {
        return EFI_NOT_FOUND;
    }

    if ( !ActiveNameSpaceData->LookedForMedia ) {
        Status = Nvme_GetBlockDeviceMediaInfo( PeiServices,
                                               This,
                                               DeviceIndex,
                                               &MediaInfo );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        MediaPresent = MediaInfo.MediaPresent;
        
    } else {
        MediaPresent = ActiveNameSpaceData->MediaInfo.MediaPresent;
    }

    if ( !MediaPresent ) {
        // Return as No media found
        return EFI_NO_MEDIA;
    }

    Status = NvmeReadBlocks( ActiveNameSpaceData,
                             StartLba,
                             BufferSize,
                             Buffer,
                             NULL );

    return Status;
}

/**
   @internal
   
    Enumerate PCI root bridges for Nvme Controller/Drive

    @param  NvmeBlkIoDev 

    @retval EFI_STATUS

   @endinternal
**/
EFI_STATUS
EnumerateNvmeDevices(
    IN OUT NVME_RECOVERY_BLK_IO_DEV             *NvmeBlkIoDev
)
{
    EFI_STATUS                               Status;
    UINTN                                    Index;
    UINT8                                    DevIndex = 0;
    NVME_CONTROLLER_INFO                    *NvmeControllerInfo;
    UINTN                                    PciAddr;
    UINT8                                    DeviceInstance = 0;
    AMI_PEI_PCI_ENUMERATION_PPI              *PeiPciEnumerationPpi;
    AMI_PEI_PCI_DEVICE_LOCATION              *PeiPciDevLocation;
    AMI_PEI_PCI_CLASSCODE                    PciClassCode;
    UINT32                                   Lower32 = 0;
    UINT32                                   Upper32 = 0;
    EFI_DEVICE_PATH                          *DevPath;
    UINTN                                    DpLength;
    UINTN                                    MmioBase;
    EDKII_NVM_EXPRESS_HOST_CONTROLLER_PPI    *NvmeHostControllerPpi = NULL;
    
    PeiServicesLocatePpi(&gEdkiiIoMmuPpiGuid, 
                         0, 
                         NULL, 
                         (VOID**)&gEdk2IoMmuPpi);
    
    Status = PeiServicesLocatePpi( &gAmiPeiPciEnumerationPpiGuid, 
                                   0, 
                                   NULL, 
                                   (VOID**)&PeiPciEnumerationPpi );
    DEBUG((DEBUG_INFO, "Locate PeiPciEnumerationPpi Status - %r\n", Status));
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    
    Status = PeiPciEnumerationPpi->InitDevices(PeiPciEnumerationPpi);
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    
    PciClassCode.BaseClassCode = NVME_CLASS_CODE;
    PciClassCode.SubClassCode =  NVME_SUBCLASS_CODE;
    PciClassCode.ProgrammingInterface = NVME_INTERFACE_CODE;

    PeiPciDevLocation = AllocateZeroPool(sizeof(AMI_PEI_PCI_DEVICE_LOCATION));
    if ( PeiPciDevLocation == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    do {
        Status = PeiPciEnumerationPpi->GetNextDeviceByClassCode( PeiPciEnumerationPpi, 
                                                                  PciClassCode,
                                                                  DeviceInstance,
                                                                  PeiPciDevLocation);
        DEBUG((DEBUG_INFO, "\n GetNextDeviceByClassCode Status :%r ",Status));
        if ( EFI_ERROR( Status )) {
            break;
        }
        
        // Allocate memory for the Controller
        gNvmePciDeviceInfo[DeviceInstance] = AllocateZeroPool(sizeof(NVME_PCI_DEVICE_INFO));
        if ( gNvmePciDeviceInfo[DeviceInstance] == NULL) {
            return EFI_OUT_OF_RESOURCES;
        }
        
        gNvmePciDeviceInfo[DeviceInstance]->BusNumber = PeiPciDevLocation->BusNumber;
        gNvmePciDeviceInfo[DeviceInstance]->Device =  PeiPciDevLocation->DeviceNumber;
        gNvmePciDeviceInfo[DeviceInstance]->Function = PeiPciDevLocation->FunctionNumber;
        gNvmePciDeviceInfo[DeviceInstance]->DevPath = PeiPciDevLocation->DevicePath;
        
        PciAddr = PCI_LIB_ADDRESS(PeiPciDevLocation->BusNumber,
                                  PeiPciDevLocation->DeviceNumber,
                                  PeiPciDevLocation->FunctionNumber,
                                  0);
        
        Lower32 = PciRead32(PciAddr + PCI_BASE_ADDRESSREG_OFFSET);
        Upper32 = PciRead32(PciAddr + PCI_BASE_ADDRESSREG_OFFSET + 4);
        
        gNvmePciDeviceInfo[DeviceInstance]->BaseAddress = (UINTN)(LShiftU64(Upper32, 32) + Lower32);
        gNvmePciDeviceInfo[DeviceInstance]->BaseAddress &= ~0x0F; // Mask don't care bits for Mmio Base Address
        
        DEBUG((DEBUG_INFO, "\n Nvme Device Found with BaseAddress:%x ",gNvmePciDeviceInfo[DeviceInstance]->BaseAddress ));
        DeviceInstance++;
    } while(!EFI_ERROR(Status));
    
    Status = PeiServicesNotifyPpi (&gNotifyList);
    if(EFI_ERROR(Status)) {
        ASSERT_EFI_ERROR (Status);
        return Status;
    }

    // Search for the Nvme Controller and Configure the Nvme Controller
    for(Index=0; Index < MAX_NVME_RECOVERY_DEVICE; Index++) {
        
        if( gNvmePciDeviceInfo[Index] ) {

            // Allocate memory for Nvme Controller
            NvmeControllerInfo = AllocateZeroPool(sizeof(NVME_CONTROLLER_INFO));
            if(NvmeControllerInfo == NULL) {
                return EFI_OUT_OF_RESOURCES;
            }
            
            NvmeBlkIoDev->NvmeControllerInfo[Index] = NvmeControllerInfo;

            NvmeControllerInfo->BusNumber = gNvmePciDeviceInfo[Index]->BusNumber;
            NvmeControllerInfo->Device = gNvmePciDeviceInfo[Index]->Device;
            NvmeControllerInfo->Function = gNvmePciDeviceInfo[Index]->Function;
            NvmeControllerInfo->DevPath = gNvmePciDeviceInfo[Index]->DevPath;
            
            NvmeControllerInfo->BarAddress = gNvmePciDeviceInfo[Index]->BaseAddress;
            
        } else { // Check any remapped NVMe available
            if(NvmeHostControllerPpi == NULL) {
                Status = PeiServicesLocatePpi(&gEdkiiPeiNvmExpressHostControllerPpiGuid, 
                                              0, 
                                              NULL, 
                                              (VOID**)&NvmeHostControllerPpi);
                if(EFI_ERROR(Status)) {
                    continue;
                }
            }
            
            // Get MmioBase of remapped NVMe
            Status = NvmeHostControllerPpi->GetNvmeHcMmioBar(NvmeHostControllerPpi,
                                                             DevIndex,
                                                             &MmioBase);
            if(EFI_ERROR(Status)) {
                continue;
            }
            
            // Get DevicePath of remapped NVMe
            Status = NvmeHostControllerPpi->GetNvmeHcDevicePath(NvmeHostControllerPpi,
                                                                DevIndex++,
                                                                &DpLength,
                                                                &DevPath);
            if(EFI_ERROR(Status)) {
                continue;
            }
            
            gNvmePciDeviceInfo[Index] = AllocateZeroPool(sizeof(NVME_PCI_DEVICE_INFO));
            if(NvmeControllerInfo == NULL) {
                return EFI_OUT_OF_RESOURCES;
            }
            
            // Allocate memory for Nvme Controller
            NvmeControllerInfo = AllocateZeroPool(sizeof(NVME_CONTROLLER_INFO));
            if(NvmeControllerInfo == NULL) {
                return EFI_OUT_OF_RESOURCES;
            }
            
            NvmeBlkIoDev->NvmeControllerInfo[Index] = NvmeControllerInfo;
            
            NvmeControllerInfo->BarAddress = (UINT64)MmioBase;
            gNvmePciDeviceInfo[Index]->BaseAddress = (UINT64)MmioBase;
            
            NvmeControllerInfo->DevPath = DevPath;
            gNvmePciDeviceInfo[Index]->DevPath = DevPath;
            
        }
        
        if(gNvmePciDeviceInfo[Index] == NULL) {
            continue;
        }

        Status = InitAndConfigNvmeController(NvmeControllerInfo);
        DEBUG((DEBUG_INFO, "InitAndConfigNvmeController Status - %r\n", Status));
        if(!EFI_ERROR(Status)) {
            NvmeBlkIoDev->TotalDeviceCount += NvmeControllerInfo->TotalActiveNameSpaceCount;
            NvmeBlkIoDev->TotalControllerCount++;
        }
    }

    return EFI_SUCCESS;
}

/**
   @internal
   
    It is a notification function after capsule is loaded to reprogram the PCI enumeration.

    @param  PeiServices 
    @param  NotifyDesc 
    @param  InvokePpi 

    @retval Status
    
   @endinternal
**/
EFI_STATUS
EFIAPI
NotifyOnNvmeRecoveryCapsuleLoaded (
    IN  EFI_PEI_SERVICES          **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDesc,
    IN  VOID                      *InvokePpi
)
{
    EFI_STATUS                       Status;
    AMI_PEI_PCI_ENUMERATION_PPI      *PeiPciEnumerationPpi = NULL;
    
    Status = PeiServicesLocatePpi( &gAmiPeiPciEnumerationPpiGuid, 0, NULL, (VOID**)&PeiPciEnumerationPpi);
    if ( EFI_ERROR( Status )) {
        return Status;
    }
    
    Status = PeiPciEnumerationPpi->ResetDeviceResources(PeiPciEnumerationPpi);
    return Status;
}

/**
   @internal
   
    PeiDpCopy copies the user provided device path into a new buffer and
    returns its address.
    
    @param  PeiServices
    @param  pDp
    
    @retval Address of the new copy of pDp
    
   @endinternal
**/
VOID* 
PeiDpCopy (
    IN EFI_DEVICE_PATH *DevicePath
)
{
    UINTN Length;
    UINT8 *NewDp = NULL;
    
    if (!DevicePath) {
        return NULL;
    }
    
    Length = PeiDpLength(DevicePath);
    if(!Length) {
        return NULL;
    }
    
    NewDp = AllocateZeroPool(Length);
            
    CopyMem(NewDp, DevicePath, Length);
    
    return NewDp;
}

/**  
    @internal
    PeiDPLength Finds length of the provided device path, 
    (including the size of EndOfDevicePath).
    
     @param  DevicePath    DevicePath whose size is to be returned.
     
     @retval Size of the device path, pDp, including EndOfDevicePath.
     @endinternal
 **/
UINTN 
PeiDpLength (
    IN EFI_DEVICE_PATH *DevicePath
)
{
    UINTN Size = 0;
    UINTN Length;

    if (DevicePath == NULL) {
        return 0;
    }
    
    for(  ; !(isEndNode(DevicePath) && DevicePath->SubType==END_ENTIRE_SUBTYPE) ; 
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
   @internal
   
    PeiDpAddNode adds the very first element of pDp2 to pDp1 just 
    before its device path terminator. 

    @param  pDp1
    @param  pDp2
    
    @retval Address of the newly allocated modified device path
    
    @note
    1.pDp1 is the device path to be appended to pDp2
    2.Device Path read from pDp2, and its very first element will be 
      appended to pDp1.
      
   @endinternal
**/
VOID* 
PeiDpAddNode (
    IN EFI_DEVICE_PATH *pDp1, 
    IN EFI_DEVICE_PATH *pDp2
)
{
    UINTN DpLength;
    UINT8 *NewDp, *TempDp;
        
    if (!pDp2) {
        return (pDp1) ? PeiDpCopy(pDp1) : PeiDpCopy(&EndOfDevicePathNode);
    }
    
    DpLength = pDp1 ? PeiDpLength(pDp1) - sizeof(EFI_DEVICE_PATH) : 0;
    
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
    Installs EFI_PEI_RECOVERY_BLOCK_IO_PPI for Nvme devices. 
  
    @retval EFI_OUT_OF_RESOURCES   Memory allocation failed due to a lack of resources.
    @retval EFI_SUCCESS            EFI_PEI_RECOVERY_BLOCK_IO_PPI installed successfully.
    @retval EFI_INVALID_PARAMETER  The PpiList pointer is NULL, or any of the PEI PPI descriptors in the 
                                   list do not have the EFI_PEI_PPI_DESCRIPTOR_PPI bit set in the Flags field.
**/
EFI_STATUS
EFIAPI
InstallPeiRecoveryBlkIoPpi()
{
    static   BOOLEAN          RecoveryBlockIoPpiInstalled = FALSE;
    EFI_STATUS                Status;
    NVME_RECOVERY_BLK_IO_DEV  *NvmeBlkIoDev  = NULL;
    
    if(RecoveryBlockIoPpiInstalled) {
        return EFI_SUCCESS;
    }
    
    NvmeBlkIoDev = AllocateZeroPool(sizeof(NVME_RECOVERY_BLK_IO_DEV));
    if ( NvmeBlkIoDev == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    NvmeBlkIoDev->HaveEnumeratedDevices = FALSE;
    NvmeBlkIoDev->AmiExtSig             = AMI_EXTENSION_SIGNATURE;
    NvmeBlkIoDev->RecoveryBlkIo.GetNumberOfBlockDevices = Nvme_GetNumberOfBlockDevices;
    NvmeBlkIoDev->RecoveryBlkIo.GetBlockDeviceMediaInfo = Nvme_GetBlockDeviceMediaInfo;
    NvmeBlkIoDev->RecoveryBlkIo.ReadBlocks              = Nvme_ReadBlocks;
    NvmeBlockIoPpiDescriptor.Ppi = &NvmeBlkIoDev->RecoveryBlkIo;

    // Install EFI_PEI_RECOVERY_BLOCK_IO_PPI
    Status = PeiServicesInstallPpi( &NvmeBlockIoPpiDescriptor );
    if ( EFI_ERROR( Status )) {
        ASSERT_EFI_ERROR (Status);
        return Status;
    }
    
    RecoveryBlockIoPpiInstalled = TRUE;
    return Status;
}


/**
    Entry point for NvmeRecovery, installs EFI_PEI_RECOVERY_BLOCK_IO_PPI 
    for Nvme devices.

    @param  FileHandle    Handle of the file being invoked.
    @param  PeiServices   Describes the list of possible PEI Services.

    @retval EFI_SUCCESS            The PEIM executed normally.
    @retval EFI_INVALID_PARAMETER  Invalid input parameter.
    
**/
EFI_STATUS
EFIAPI
NvmeRecoveryPeimEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
    EFI_STATUS   Status;

    // Install Virtual Block Io PPI
    Status = InstallPeiRecoveryBlkIoPpi();
    return Status;   
}
