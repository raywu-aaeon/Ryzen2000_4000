//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SdioBlkErase.c
    BlockErase function implemented

**/

//----------------------------------------------------------------------
#include <SdioDriver.h>
//----------------------------------------------------------------------

/**
    To erase a specified number of device blocks.
    
    For SD cards below three commands are used to erase specified number of blocks.
        1. CMD32 (ERASE_WR_BLK_START) - to specify the StartLBA from where blocks needs to be erased
        2. CMD33 (ERASE_WR_BLK_END) - to specify the EndLBA until which blocks needs to be erased
        3. CMD38 (Arg- 0) - Erase the blocks specified within the Start and EndLBA.
    
    For MMC, below three commands are used to erase specified number of blocks.
        1. CMD35 (ERASE_GROUP_START) - to specify the StartLBA from where blocks needs to be erased
        2. CMD36 (ERASE_GROUP_END) - to specify the EndLBA until which blocks needs to be erased
        3. CMD38 (Arg- 1) - Erase the blocks specified within the Start and EndLBA.
    
    @param  This    - Pointer to EFI_ERASE_BLOCK_PROTOCOL structure
    @param  MediaId - The media ID that the erase request is for
    @param  LBA     - The starting logical block address
    @param  Token   - A pointer to the token associated with the
                      transaction.
    @param  Size    - The size in bytes to be erased

    @retval EFI_STATUS
**/
EFI_STATUS
SdioBlockErase (
    IN  EFI_ERASE_BLOCK_PROTOCOL   *This,
    IN  UINT32                     MediaId,
    IN  EFI_LBA                    LBA,
    IN OUT EFI_ERASE_BLOCK_TOKEN   *Token,
    IN UINTN                       Size
) {
    EFI_STATUS  Status;
    UINT32      CardStatus;
    UINT32      EraseCommandArgument;
    UINT8       EraseStartCommand, EraseEndCommand;
    UINT64      EndLBA;
    UINT8       EraseTimeOutCount = 0;
   
    SDIO_DEVICE_INTERFACE   *SdioDevInterface = ((SDIO_BLOCK_ERASE *)This)->SdioDevInterface;
       
    //Parameter Set Commands (Erase group selection) are not allowed, while the
    //device is in Programming State.
    Status= SdMmcCardGetStatus(
                          SdioDevInterface->SdioDevInfo,
                          SdioDevInterface->SlotNumber);
    if(EFI_ERROR(Status) && 
      (SdioDevInterface->SdioDevInfo->CurrentState == CARDSTATUS_PRG )) {
        return EFI_DEVICE_ERROR;
    }
    
    // Calculate the EndLBA, based on bytes to be erased and StartLBA
    EndLBA = LBA + ((Size / SdioDevInterface->SdioDevInfo->wBlockSize) - 1);
    
    // Validate whether the input size is EraseLengthGranularity aligned.
    if (((Size / SdioDevInterface->SdioDevInfo->wBlockSize) % This->EraseLengthGranularity) ||
         (EndLBA > SdioDevInterface->SdioDevInfo->dMaxLBA)){
        return EFI_INVALID_PARAMETER;
    }
    
    // Find out whether the device is MMC or SD card.
    // For MMC card, EraseCommand sequence is ERASE_GROUP_START, ERASE_GROUP_END, ERASE 
    // For SD card, EraseCommand sequence is ERASE_WR_BLK_START, ERASE_WR_BLK_END, ERASE 

    if ((SdioDevInterface->SdioDevInfo->bMode == MMC_HIGH_CAP ) || 
        (SdioDevInterface->SdioDevInfo->bMode == MMC_STAND_CAP )) {
                
        EraseStartCommand = ERASE_GROUP_START;
        EraseEndCommand   = ERASE_GROUP_END;
        //For CMD38, When Bit 0 = 1 and Bit 1=0, will perform a TRIM on the sector(s). 
        EraseCommandArgument = 1;
        
        // Data address for media =<2 GB is a 32 bit byte address 
        // Data address for media > 2 GB is a 32 bit sector (512B) address.        
        if(SdioDevInterface->SdioDevInfo->bMode == MMC_STAND_CAP ) {
            LBA = MultU64x32(LBA , SdioDevInterface->SdioDevInfo->wBlockSize);
            EndLBA = MultU64x32(EndLBA , SdioDevInterface->SdioDevInfo->wBlockSize) ;
        } 
    } else {
        EraseStartCommand = ERASE_WR_BLK_START;
        EraseEndCommand   = ERASE_WR_BLK_END;     
        //For CMD38, When all argument bits are zero, will perform an erase on erase group(s).
        EraseCommandArgument = 0;
        
        //SDSC Cards use byte unit address,
        //SDHC and SDXC Cards use block unit address (512 bytes)
        if(SdioDevInterface->SdioDevInfo->bMode == SD_STAND_CAP ) {
            LBA = MultU64x32(LBA , SdioDevInterface->SdioDevInfo->wBlockSize);
            EndLBA = MultU64x32(EndLBA , SdioDevInterface->SdioDevInfo->wBlockSize) ;
        } 
    }        
    // Specify the Start address 
    Status = SdMmcCommand(
                     SdioDevInterface->SdioDevInfo,
                     SdioDevInterface->SlotNumber,
                     (EraseStartCommand << 8) | RESP1_TYPE,
                     (UINT32)LBA,
                     SD_MMC_COMMAND_TIMEOUT);
    if(EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }        
    // Specify the End address
    Status = SdMmcCommand (
                     SdioDevInterface->SdioDevInfo,
                     SdioDevInterface->SlotNumber,
                     (EraseEndCommand << 8) | RESP1_TYPE,
                     (UINT32)EndLBA,
                     SD_MMC_COMMAND_TIMEOUT);
    if(EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    // Erase the specified blocks.          
    Status = SdMmcCommand (
                     SdioDevInterface->SdioDevInfo,
                     SdioDevInterface->SlotNumber,
                     (ERASE << 8) | RESP1B_TYPE,
                     EraseCommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if(Status == EFI_TIMEOUT || Status == EFI_SUCCESS) {
        CardStatus = SDIO_REG32(SdioDevInterface->SdioDevInfo->SdioBaseAddress,RESP0);
        if (CardStatus & WP_ERASE_SKIP) {
            // Erase range includes write protected sectors
            return EFI_WRITE_PROTECTED;  
        } 
        EraseTimeOutCount = 10;  // 10 * 250ms = 2.5 Sec
        do {
            MicroSecondDelay (250000); // Check the card state for every 250ms
            Status = SdMmcCardGetStatus (
                                 SdioDevInterface->SdioDevInfo,
                                 SdioDevInterface->SlotNumber);
            if(EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
            if(SdioDevInterface->SdioDevInfo->bState == CARDSTATUS_TRAN) {
                break;
            }
            EraseTimeOutCount--;
        } while(EraseTimeOutCount);
            
        if(!EraseTimeOutCount){
            return EFI_DEVICE_ERROR;
        }
    } else {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

/**
    Initializes Sdio Erase BLock interface and defines the EraseLength granularity for the devices.
    
    For SDSC card,EraseLengthGranularity is one or multiple units of SECTOR_SIZE, 
    when ERASE_BLK_EN is disabled. Else it will be one or multiple units of 512 bytes, 
    when ERASE_BLK_EN is enabled.
    
    For MMC card, TRIM command will be used for Erase operation. TRIM command does not 
    depend on Erase Group size,hence host will be able to erase one or multiple units of 
    512 bytes. So EraseLengthGranularity is fixed to 1.

    @param  SdioDevInterface - Pointer to SDIO_DEVICE_INTERFACE structure

    @retval EFI_STATUS

    @note  
  Here is the control flow of this function:
  1. Initialize EFI_ERASE_BLOCK_PROTOCOL Protocol.
  2. Defines EraseLengthGranularity - Minimum number of consecutive blocks, which 
     can be erased during ERASE operation.

**/
EFI_STATUS
InitSdioBlockErase (
    IN  SDIO_DEVICE_INTERFACE            *SdioDevInterface
)
{
    EFI_STATUS                 Status;
    EFI_ERASE_BLOCK_PROTOCOL   *BlkErase;
    SDIO_BLOCK_ERASE           *SdioBlkErase;
    UINT32                     Temp32 = 0;
   
    Status = gBS->AllocatePool (EfiBootServicesData,
               sizeof(SDIO_BLOCK_ERASE),
               (VOID**)&SdioBlkErase);

    if (EFI_ERROR(Status)) {
        return Status;
    }
   
    SdioDevInterface->SdioBlkErase = SdioBlkErase;
    SdioBlkErase->SdioDevInterface = SdioDevInterface;

    BlkErase = &(SdioBlkErase->BlkErase);
    BlkErase->EraseBlocks = SdioBlockErase;
   
    BlkErase->Revision = EFI_ERASE_BLOCK_PROTOCOL_REVISION; 
    // Check for eMMC  
    if ((SdioDevInterface->SdioDevInfo->bMode == MMC_HIGH_CAP ) || 
       (SdioDevInterface->SdioDevInfo->bMode == MMC_STAND_CAP )) {
        //Setting granularity as 1, to allow the host to erase one or multiple units of 512 bytes.
        BlkErase->EraseLengthGranularity = 1;
    } else {
        //
        // For SDSC card,Erase unit is one or multiple units of SECTOR_SIZE, when ERASE_BLK_EN is disabled
        // Else it will be one or multiple units of 512 bytes, when ERASE_BLK_EN is enabled.
        //
        if ((SdioDevInterface->SdioDevInfo->bMode == SD_STAND_CAP) &&
            !(SdioDevInterface->SdioDevInfo->d4CSD[1] & ERASE_BLK_EN)) {
            
            Temp32 = SdioDevInterface->SdioDevInfo->d4CSD[1] & SECTOR_SIZE;
            BlkErase->EraseLengthGranularity = (Temp32 >> 7) + 1;              
        } else {
            //
            //For, SDHC and SDXC Cards, ERASE_BLK_EN is fixed to 1
            //hence the host can erase one or multiple units of 512 bytes
            //
            BlkErase->EraseLengthGranularity = 1;   
        }
   }
   return EFI_SUCCESS;
}

