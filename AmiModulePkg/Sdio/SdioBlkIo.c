//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file SdioBlkIo.c
    BlockIo function implemented

**/

//----------------------------------------------------------------------

#include "SdioDriver.h"

//----------------------------------------------------------------------

#if ( defined(BOOT_SECTOR_WRITE_PROTECT) && (BOOT_SECTOR_WRITE_PROTECT != 0) )
#include <Protocol/AmiBlockIoWriteProtection.h>
extern AMI_BLOCKIO_WRITE_PROTECTION_PROTOCOL *AmiBlkWriteProtection;
#endif

/**
    Initializes Sdio Block IO interface

    @param  SdioDevInterface

    @retval EFI_STATUS

    @note  
  Here is the control flow of this function:
  1. Initialize EFI_BLOCK_IO_PROTOCOL Protocol.
  2. In case of Removable devices, detect Media presence.

**/

EFI_STATUS
InitSdioBlockIO (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface
 )
{
    EFI_STATUS              Status;
    EFI_BLOCK_IO_PROTOCOL   *BlkIo;
    SDIO_BLOCK_IO           *SdioBlkIo;
    EFI_BLOCK_IO_MEDIA      *BlkMedia;
    AMI_SDIO_BUS_PROTOCOL   *SdioBusInterface;
    SDIO_DEVICE_INFO        *SdioDevInfo = SdioDevInterface->SdioDevInfo;

    Status = gBS->AllocatePool (EfiBootServicesData,
                sizeof(SDIO_BLOCK_IO),
                (VOID**)&SdioBlkIo);

    if (EFI_ERROR(Status)) return Status;
    
    Status = gBS->AllocatePool (EfiBootServicesData,
                    sizeof(EFI_BLOCK_IO_MEDIA),
                    (VOID**)&BlkMedia);
    
    if (EFI_ERROR(Status)) {
        gBS->FreePool (SdioBlkIo);
        return Status;
    }
    gBS->SetMem( BlkMedia, sizeof(EFI_BLOCK_IO_MEDIA), 0 );
    SdioDevInterface->SdioBlkIo = SdioBlkIo;

    // Initialize the fields in IdeBlkIo (Sdio_BLOCK_IO)
    SdioBlkIo->SdioDevInterface = SdioDevInterface;

    BlkIo = &(SdioBlkIo->BlkIo);
    BlkIo->Media = BlkMedia;
    BlkIo->Reset = SdioReset;
    BlkIo->ReadBlocks = SdioBlkRead;
    BlkIo->WriteBlocks = SdioBlkWrite;
    BlkIo->FlushBlocks = SdioBlkFlush;

    BlkMedia->MediaId = 0;
    SdioBusInterface = SdioDevInterface->SdioBusInterface;
    
    //
    // check if controller has embedded slot(eMMC) in capabilities reg. If yes, report as non removable media
    //
    if ( (*(volatile UINT32 *)(SdioBusInterface->SdioBaseAddress[SdioDevInterface->SlotNumber] + 0x40 ) & (BIT30 |BIT31)) == BIT30) {
        BlkMedia->RemovableMedia = FALSE;
    } else {    
        BlkMedia->RemovableMedia = TRUE;
    }

    BlkMedia->MediaPresent = TRUE;
    BlkMedia->LogicalPartition = FALSE;
    BlkMedia->ReadOnly = FALSE;
    BlkMedia->WriteCaching = FALSE;
    BlkMedia->BlockSize = 512;

    if(SdioDevInfo->SDIO_Access==ADMA) {
        //
        // Buffer starting address must be evenly divisible by 4 with no 
        // remainder or else Read/Write function will return EFI_INVALID_PARAMETER.
        //
        BlkMedia->IoAlign = 4;  
    } else if(SdioDevInfo->SDIO_Access==SDMA){
        
        BlkMedia->IoAlign = 4096; 
    }


    //
    // Default value set to 1 logical blocks per PhysicalBlock
    //
    BlkMedia->LogicalBlocksPerPhysicalBlock=1;
    
    //
    // Default value set to 0 for Lowest Aligned LBA
    //
    BlkMedia->LowestAlignedLba=0;
    BlkMedia->OptimalTransferLengthGranularity=BlkMedia->BlockSize;
    
    BlkIo->Revision = EFI_BLOCK_IO_PROTOCOL_REVISION3;


    BlkMedia->LastBlock = SdioDevInterface->SdioDevInfo->dMaxLBA;

    return EFI_SUCCESS;
}


/**
    Read from the Sdio ATA Device

    @param  This 
    @param  MediaId 
    @param  LBA,
    @param  BufferSize 
    @param  Buffer 

    @retval EFI_STATUS

**/
EFI_STATUS
EFIAPI
SdioBlkRead (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  UINT32                  MediaId,
    IN  EFI_LBA                 Lba,
    IN  UINTN                   BufferSize,
    OUT VOID                    *Buffer
 )
{
    EFI_STATUS  Status;

    Status =  SdioBlkReadWrite(This, MediaId, Lba, BufferSize, Buffer, 0);
    return Status;
}

/**
    Write to Sdio ATA Device

    @param  This 
    @param  MediaId 
    @param  LBA,
    @param  BufferSize 
    @param  Buffer 

    @retval EFI_STATUS

**/
EFI_STATUS
EFIAPI
SdioBlkWrite (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  UINT32                  MediaId,
    IN  EFI_LBA                 Lba,
    IN  UINTN                   BufferSize,
    OUT VOID                    *Buffer
 )
{

    EFI_STATUS  Status;

#if ( defined(BOOT_SECTOR_WRITE_PROTECT) && (BOOT_SECTOR_WRITE_PROTECT != 0) )
    if(AmiBlkWriteProtection != NULL) {
        // Get user input
        Status = AmiBlkWriteProtection->BlockIoWriteProtectionCheck ( 
                                                    AmiBlkWriteProtection,
                                                    This,
                                                    Lba,
                                                    BufferSize
                                                    );
        // Abort operation if denied
        if(Status == EFI_ACCESS_DENIED) {
            return Status;
        }
    }
#endif
    
    Status =  SdioBlkReadWrite(This, MediaId, Lba, BufferSize, Buffer, 1);

    return Status;

}


/**
    Reset ATA device

        
    @param  This 
    @param  ExtendedVerification 

    @retval EFI_STATUS

**/
EFI_STATUS
EFIAPI
SdioReset (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  BOOLEAN                 ExtendedVerification
 )
{
    return EFI_SUCCESS;
}

/**
    Flush the cache
        
    @param  This 

    @retval EFI_STATUS

**/

EFI_STATUS
EFIAPI
SdioBlkFlush (
    IN  EFI_BLOCK_IO_PROTOCOL        *This
)
{
    return EFI_SUCCESS;
}

/**
    Read/Write to/from SD Device

        
    @param  This 
    @param  MediaId 
    @param  Lba,
    @param  BufferSize 
    @param  Buffer 
    @param  READWRITE

    @retval EFI_STATUS

    @note  
  1. Check for validity of the input
  2. Issue DMA or PIO Read/Write call.

**/
EFI_STATUS
SdioBlkReadWrite (
    IN  EFI_BLOCK_IO_PROTOCOL   *This,
    IN  UINT32                  MediaId,
    IN  EFI_LBA                 Lba,
    IN  UINTN                   BufferSize,
    OUT VOID                    *Buffer,
    BOOLEAN                     READWRITE
)
{
    UINTN                   NumberOfBlocks;
    SDIO_DEVICE_INTERFACE   *SdioDevInterface = ((SDIO_BLOCK_IO *)This)->SdioDevInterface;
    EFI_BLOCK_IO_MEDIA      *BlkMedia = This->Media;
    EFI_STATUS              Status=EFI_DEVICE_ERROR;
    UINT8                   Port=SdioDevInterface->SlotNumber;
    UINTN                   BufferAddress;

    //
    // Check if Media ID matches
    //
    if (BlkMedia->MediaId != MediaId) return EFI_MEDIA_CHANGED;

    if (BufferSize == 0) return EFI_SUCCESS;

    //
    // If IoAlign values is 0 or 1, means that the buffer can be placed 
    // anywhere in memory or else IoAlign value should be power of 2. To be
    // properly aligned the buffer address should be divisible by IoAlign  
    // with no remainder. 
    // 
    BufferAddress = (UINTN)Buffer;
    if((BlkMedia->IoAlign > 1 ) && (BufferAddress % BlkMedia->IoAlign)) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Check whether the block size is multiple of BlkMedia->BlockSize
    NumberOfBlocks = BufferSize % BlkMedia->BlockSize;
    if (NumberOfBlocks) {
        return EFI_BAD_BUFFER_SIZE;
    }

   // Check for Valid start Lba #
    if (Lba > BlkMedia->LastBlock) {
        return EFI_INVALID_PARAMETER;
    }

    NumberOfBlocks = BufferSize / BlkMedia->BlockSize;

    if (Lba + NumberOfBlocks > BlkMedia->LastBlock + 1) {
        return EFI_INVALID_PARAMETER;
    }

    if(!READWRITE) {
        Status=SdioReadDevice(SdioDevInterface,Port,Lba, (UINT32)NumberOfBlocks, Buffer);
    } else {
        Status=SdioWriteDevice(SdioDevInterface,Port,Lba, (UINT32)NumberOfBlocks, Buffer);
    }

    return Status;
}

/**
    Read the Data from Sd card

    @param  SdioDevInterface 
    @param  Port 

    @retval EFI_STATUS

**/
EFI_STATUS
SdioReadDevice (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Port,
    IN  EFI_LBA                 Lba,
    IN  UINT32                  NumBlks,
    IN  VOID                    *BufferAddress
)
{
    SDIO_DEVICE_INFO        *SdioDevInfo=SdioDevInterface->SdioDevInfo;
    UINT32                  TempNumBlks = MAX_NUMBLOCK_16BIT;
    VOID                    *DmaBuffer = 0;
    EFI_PHYSICAL_ADDRESS    DmaAddr;
    UINTN                   TotalBytes;
    EFI_STATUS              Status;
    EFI_STATUS              ReadStatus;
    VOID                    *TempBufferAdd=NULL;
    EFI_PCI_IO_PROTOCOL     *PciIo = NULL;

    TotalBytes = NumBlks * (SdioDevInterface->SdioDevInfo->wBlockSize);

    //
    // Map the BufferAddress for ADMA transfer
    //    
    if(((SdioDevInterface->SdioDevInfo->SDIO_Access== ADMA)||(SdioDevInterface->SdioDevInfo->SDIO_Access==SDMA)) \
            && (SdioDevInterface->SdioBusInterface->ControllerType == PciIoType)) {
        PciIo = (EFI_PCI_IO_PROTOCOL *)SdioDevInterface->SdioBusInterface->ControllerInterface;
        Status = PciIo->Map (PciIo,
                            EfiPciIoOperationBusMasterWrite,
                            BufferAddress,
                            &TotalBytes,
                            &DmaAddr,
                            &DmaBuffer
                            );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        TempBufferAdd =(UINT32*)DmaAddr;
    } else {
        TempBufferAdd =(UINT32*)BufferAddress;
    }

    //
    // If number of block are greater than 65535(16-bit) then divide the read into multiple read.
    //
    while(NumBlks > TempNumBlks) {
        SdMmcRead(SdioDevInfo,Port,(EFI_LBA)Lba, TempNumBlks,(VOID*)TempBufferAdd);
        NumBlks = NumBlks - TempNumBlks;
        Lba += TempNumBlks;
        TempBufferAdd = (UINT8*)TempBufferAdd + ((SdioDevInfo->wBlockSize) * TempNumBlks);
    }

    ReadStatus = SdMmcRead(SdioDevInfo,Port,(EFI_LBA)Lba, NumBlks,(VOID*)TempBufferAdd);
    
    //
    // Unmap the corresponding DMA memory
    //
    if(((SdioDevInterface->SdioDevInfo->SDIO_Access== ADMA)||(SdioDevInterface->SdioDevInfo->SDIO_Access==SDMA)) && \
            (SdioDevInterface->SdioBusInterface->ControllerType == PciIoType)) {
        Status = PciIo->Unmap ( PciIo,
                                DmaBuffer
                                );
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    return ReadStatus;
}

/**
    Read the Data from Sd card

    @param  SdioDevInterface 
    @param  Port 

    @retval EFI_STATUS

**/
EFI_STATUS
SdioWriteDevice (
    IN  SDIO_DEVICE_INTERFACE   *SdioDevInterface,
    IN  UINT8                   Port,
    IN  EFI_LBA                 Lba,
    IN  UINT32                  NumBlks,
    IN  VOID                    *BufferAddress
)
{
    SDIO_DEVICE_INFO        *SdioDevInfo=SdioDevInterface->SdioDevInfo;
    UINT32                  TempNumBlks = MAX_NUMBLOCK_16BIT;
    VOID                    *DmaBuffer = 0;
    EFI_PHYSICAL_ADDRESS    DmaAddr;
    UINTN                   TotalBytes;
    EFI_STATUS              Status;
    EFI_STATUS              WriteStatus;
    VOID                    *TempBufferAdd=NULL;
    EFI_PCI_IO_PROTOCOL     *PciIo = NULL;
    
#if SDIO_WriteProtect
    UINT32            Temp32;
    Temp32=SDIO_REG32(SdioDevInfo->SdioBaseAddress,PSTATE);
    if(!(Temp32 & PSTATE_WP)) {
        return EFI_WRITE_PROTECTED;
    }
#endif
    
    TotalBytes = NumBlks * (SdioDevInterface->SdioDevInfo->wBlockSize);
    
    //
    // Map the BufferAddress for ADMA transfer
    //
    if(((SdioDevInterface->SdioDevInfo->SDIO_Access== ADMA)||(SdioDevInterface->SdioDevInfo->SDIO_Access==SDMA)) \
                && (SdioDevInterface->SdioBusInterface->ControllerType == PciIoType)) {
        PciIo = (EFI_PCI_IO_PROTOCOL *)SdioDevInterface->SdioBusInterface->ControllerInterface;
        Status = PciIo->Map (PciIo,
                            EfiPciIoOperationBusMasterRead,
                            BufferAddress,
                            &TotalBytes,
                            &DmaAddr,
                            &DmaBuffer
                            );
        if (EFI_ERROR(Status)) {
            return Status;
        }
        TempBufferAdd =(UINT32*)DmaAddr;
    } else {
        TempBufferAdd =(UINT32*)BufferAddress;
    }

    //
    // If number of block are greater than 65535(16-bit) then divide the write into multiple write.
    //
    while(NumBlks > TempNumBlks) {
        SdMmcWrite(SdioDevInfo,Port,(EFI_LBA)Lba, (UINT32)TempNumBlks,(VOID*)TempBufferAdd);
        NumBlks = NumBlks - TempNumBlks;
        Lba += TempNumBlks;
        TempBufferAdd = (UINT8*)TempBufferAdd + ((SdioDevInfo->wBlockSize) * TempNumBlks);
    }
    WriteStatus = SdMmcWrite(SdioDevInfo,Port,(EFI_LBA)Lba, (UINT32)NumBlks,(VOID*)TempBufferAdd);
    

    //
    // Unmap the corresponding DMA memory
    //
    if(((SdioDevInterface->SdioDevInfo->SDIO_Access== ADMA)||(SdioDevInterface->SdioDevInfo->SDIO_Access==SDMA)) && \
        (SdioDevInterface->SdioBusInterface->ControllerType == PciIoType)) {
        Status = PciIo->Unmap (PciIo,
                                DmaBuffer
                                );
        if (EFI_ERROR(Status)) {
            return Status;
        }

    }
    return WriteStatus;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
