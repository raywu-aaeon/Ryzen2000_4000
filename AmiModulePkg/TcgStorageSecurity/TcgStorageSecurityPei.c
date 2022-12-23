//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file HddSecurityPei.c

**/

#include <PiPei.h>
#include <Ppi/IoMmu.h>
#include <Ppi/SmmCommunication.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/LockBoxLib.h>
#include "TcgStorageSec.h"

UINT8            *gTcgStorageSecLockBoxMapData = NULL;
UINTN            gLockBoxMapDataSize = 0;
EFI_GUID         gTcgStorageSecLockBoxMapDataGuid = TCG_STORAGE_SEC_LOCKBOX_MAP_DATA_GUID;
EDKII_IOMMU_PPI  *gIoMmuPpi = NULL;

/**
    Sends Mapped Address to SMM
    
    @param None
    
    @return EFI_STATUS
 
**/
EFI_STATUS
SendMappedAddressToSmm()
{
    EFI_STATUS                         Status;
    EFI_PEI_SMM_COMMUNICATION_PPI      *SmmCommunicationPpi;
    EFI_SMM_COMMUNICATE_HEADER         *CommHeader;
    UINT8                              *CommBuffer;
    UINTN                              CommSize;
    VOID                               *MapInfo;
    
    Status = PeiServicesLocatePpi (
                            &gEfiPeiSmmCommunicationPpiGuid,
                            0,
                            NULL,
                            (VOID **)&SmmCommunicationPpi );
    if (EFI_ERROR (Status)) {
        return Status;
    }
    
    CommBuffer = AllocateZeroPool(sizeof(EFI_GUID) + sizeof(UINT64) + gLockBoxMapDataSize);
    if (CommBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    CommHeader = (EFI_SMM_COMMUNICATE_HEADER *)CommBuffer;
    CommSize   = sizeof(EFI_GUID) + sizeof(UINT64) + gLockBoxMapDataSize;

    CommHeader->MessageLength = gLockBoxMapDataSize;
    CopyMem (&CommHeader->HeaderGuid, &gTcgStorageSecLockBoxMapDataGuid, sizeof(EFI_GUID));
    
    MapInfo = (VOID*)&CommBuffer[sizeof(EFI_GUID) + sizeof(UINT64)];
    CopyMem (MapInfo, gTcgStorageSecLockBoxMapData, gLockBoxMapDataSize);
    
    Status = SmmCommunicationPpi->Communicate (
                                        SmmCommunicationPpi,
                                        CommBuffer,
                                        &CommSize );
    DEBUG((DEBUG_INFO, "TcgStorageSecurityPei: Communicate Status - %r\n", Status));
    
    return EFI_SUCCESS;
}

/**
    Once BootScript restoration done, gets remapped device BAR using OpalDeviceInfoPpi
    and send it to SMM
    
    @param PeiServices
    @param NotifyDesc
    @param InvokePpi
    
    @return EFI_STATUS
 
**/
EFI_STATUS
EFIAPI
PeiSmmCommunicationPpiCallback(
    IN  EFI_PEI_SERVICES               **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR      *NotifyDesc,
    IN  VOID                           *InvokePpi
)
{
    EFI_STATUS              Status;
    UINT8                   Count;
    IOMMU_MAP_INFORMATION   *MapInfo;
    UINT8                   Index;
    EFI_PHYSICAL_ADDRESS    DeviceAddress;
    UINTN                   NumberOfBytes;
    VOID                    *Mapping;
    
    if(gIoMmuPpi == NULL) {
        return EFI_SUCCESS;
    }
    
    DEBUG((DEBUG_INFO, "TcgStorageSecurityPei: PeiSmmCommunicationPpiCallback\n"));
    
    // In Intel and AMD platform, when IOMMU is enabled, control will come here.
    // But, LockBox data will be there only in AMD platform as SMM IOMMU protocol is not available.
    // So, below check will fail in Intel platform.
    
    // First get LockBox data size
    gLockBoxMapDataSize = sizeof(gTcgStorageSecLockBoxMapData);
    Status = RestoreLockBox (
                        &gTcgStorageSecLockBoxMapDataGuid, 
                        &gTcgStorageSecLockBoxMapData, 
                        &gLockBoxMapDataSize );

    if (Status != EFI_BUFFER_TOO_SMALL) {
        return Status;
    }

    // Restore LockBox data
    gTcgStorageSecLockBoxMapData = AllocateZeroPool(gLockBoxMapDataSize);
    if (gTcgStorageSecLockBoxMapData == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    Status = RestoreLockBox (
                        &gTcgStorageSecLockBoxMapDataGuid, 
                        gTcgStorageSecLockBoxMapData, 
                        &gLockBoxMapDataSize );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Count   = gTcgStorageSecLockBoxMapData[0];
    MapInfo = (IOMMU_MAP_INFORMATION*)&gTcgStorageSecLockBoxMapData[1];
    
    for(Index = 0; Index < Count; Index++, MapInfo++) {

        if(MapInfo->Address1 != 0) {
            NumberOfBytes = MapInfo->Length1;
            
            Status = gIoMmuPpi->Map (
                                gIoMmuPpi, 
                                MapInfo->Operation1,
                                (VOID*)(UINTN)MapInfo->Address1,
                                &NumberOfBytes,
                                &DeviceAddress,
                                &Mapping );
            if(EFI_ERROR(Status) || (NumberOfBytes != MapInfo->Length1)) {
                MapInfo->Address1 = 0;
                continue;
            }

            Status = gIoMmuPpi->SetAttribute (
                                  gIoMmuPpi,
                                  Mapping,
                                  EDKII_IOMMU_ACCESS_READ | EDKII_IOMMU_ACCESS_WRITE);
            if (EFI_ERROR (Status)) {
                MapInfo->Address1 = 0;
                continue;
            }
            
            MapInfo->Address1 = DeviceAddress;
        }
        
        if(MapInfo->Address2 != 0) {
            NumberOfBytes = MapInfo->Length2;
            Status = gIoMmuPpi->Map (
                                gIoMmuPpi, 
                                MapInfo->Operation2,
                                (VOID*)(UINTN)MapInfo->Address2,
                                &NumberOfBytes,
                                &DeviceAddress,
                                &Mapping );
            if(EFI_ERROR(Status) || (NumberOfBytes != MapInfo->Length2)) {
                MapInfo->Address2 = 0;
                continue;
            }

            Status = gIoMmuPpi->SetAttribute (
                                      gIoMmuPpi,
                                      Mapping,
                                      EDKII_IOMMU_ACCESS_READ | EDKII_IOMMU_ACCESS_WRITE);
            if (EFI_ERROR (Status)) {
                MapInfo->Address2 = 0;
                continue;
            }
            
            MapInfo->Address2 = DeviceAddress;
        }
    }
    
    Status = SendMappedAddressToSmm();
    return Status;
}

EFI_PEI_NOTIFY_DESCRIPTOR gPeiSmmCommunicationPpiNotifyDesc = {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiSmmCommunicationPpiGuid,
    PeiSmmCommunicationPpiCallback
};

/**
    Entry Point for HddSecurityPei driver

    @param  FileHandle
    @param  PeiServices

    @retval EFI_STATUS
**/
EFI_STATUS
EFIAPI
TcgStorageSecurityPeiEntry (
  IN EFI_PEI_FILE_HANDLE       FileHandle,
  IN CONST EFI_PEI_SERVICES    **PeiServices
)
{
    EFI_STATUS       Status;
    EFI_BOOT_MODE    BootMode;
    
    Status = PeiServicesGetBootMode (&BootMode);
    if (EFI_ERROR(Status) || (BootMode != BOOT_ON_S3_RESUME)) {
        return Status;
    }
    
    Status = PeiServicesLocatePpi (
                            &gEdkiiIoMmuPpiGuid, 
                            0, 
                            NULL, 
                            (VOID **)&gIoMmuPpi );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    Status = PeiServicesNotifyPpi (&gPeiSmmCommunicationPpiNotifyDesc);
    return Status;
}
