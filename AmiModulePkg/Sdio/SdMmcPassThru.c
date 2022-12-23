//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SdMmcPassThru.c
    Contains SdMmc PassThru protocol APIs definition

**/

//---------------------------------------------------------------------------
#include  "SdMmcPassThruSupport.h"
//---------------------------------------------------------------------------
// SD card command list
UINT8 SdCommandClass0[13] = { // Class0 commands
0, 2, 3, 4, 7, 8, 9, 10, 11, 12, 13, 15, 0xFF};

UINT8 SdCommandClass1[1] = { // Class1 commands
0xFF }; 

UINT8 SdCommandClass2[7] = { // Class2 commands
16, 17, 18, 19, 20, 23, 0xFF};

UINT8 SdCommandClass3[1] = { // Class3 Commands
 0xFF }; 

UINT8 SdCommandClass4[7] = { // Class4 commands
16, 20, 23, 24, 25, 27, 0xFF};

UINT8 SdCommandClass5[4] = { // Class5 commands
32, 33, 38, 0xFF};

UINT8 SdCommandClass6[4] = { // Class6 commands
28, 29, 30, 0xFF};

UINT8 SdCommandClass7[3] = { // Class7 commands
40, 42, 0xFF};

UINT8 SdCommandClass8[3] = { // Class8 commands
55, 56, 0xFF};

UINT8 SdCommandClass9[4] = { // Class9 commands
52, 53, 54, 0xFF};

UINT8 SdCommandClass10[2] = { // Class10 commands
6, 0xFF};

UINT8 SdCommandClass11[5] = { // Class11 commands   
48, 49, 58, 59, 0xFF};

// MMC command list
UINT8 MmcCommandClass0[17] = { // Class0 commands
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 19, 0xFF};

UINT8 MmcCommandClass1[1] = { // Class1 commands
0xFF }; 

UINT8 MmcCommandClass2[5] = { // Class2 commands
16, 17, 18, 21, 0xFF};

UINT8 MmcCommandClass3[1] = { // Class3 Commands
 0xFF }; 

UINT8 MmcCommandClass4[7] = { // Class4 commands
23, 24, 25, 26, 27, 49, 0xFF};

UINT8 MmcCommandClass5[4] = { // Class5 commands
35, 36, 38, 0xFF};

UINT8 MmcCommandClass6[5] = { // Class6 commands
28, 29, 30, 31, 0xFF};

UINT8 MmcCommandClass7[2] = { // Class7 commands
42, 0xFF};

UINT8 MmcCommandClass8[3] = { // Class8 commands
55, 56, 0xFF};

UINT8 MmcCommandClass9[3] = { // Class9 commands
39, 40, 0xFF};

UINT8 MmcCommandClass10[3] = { // Class10 commands
53, 54, 0xFF};

UINT8 MmcCommandClass11[6] = { // Class11 commands   
44, 45, 46, 47, 48, 0xFF};

UINT8 SdIoCommandList[4] = {
7, 52, 53, 0xFF
};
/**
    Sends an SDMmc command to an SD device that is attached 
    to the SD controller

    @param  This           - A pointer to the EFI_SD_MMC_PASS_THRU_PROTOCOL instance.
    @param  Slot           - Sdio slot number
    @param  Packet         - A pinter to the command to be send to sdio device
    @param  Event OPTIONAL - If non-blocking I/O is not supported then Event is ignored, and blocking
                             I/O is performed. If Event is NULL, then blocking I/O is performed. If
                             Event is not NULL and non blocking I/O is supported, then non-blocking
                             I/O is performed, and Event will be signaled when the Sdio command completes

    @retval EFI_STATUS

    @note   A pointer to the SDMmc command to send to the SD device specified by the Slot number.
**/
EFI_STATUS
PassThru (
    IN EFI_SD_MMC_PASS_THRU_PROTOCOL                *This,
    IN UINT8                                        Slot,
    IN OUT EFI_SD_MMC_PASS_THRU_COMMAND_PACKET      *Packet,
    IN EFI_EVENT                                    Event
)
{
    EFI_STATUS                    Status = EFI_SUCCESS;
    SDIO_DEVICE_INTERFACE         *SdioDevInterface = NULL;
    SD_MMC_PASS_THRU_PROTOCOL     *SdMmcPassThruInstance = \
                                  (SD_MMC_PASS_THRU_PROTOCOL *)This;
    BOOLEAN                       Read;
    UINT64                        MaxBytes;
    UINT32                        NumBlks;
    UINT16                        CommandClass;
    VOID                          *TransferBuffer;
    UINT16                        ClassIndex;
    UINT16                        Index;
    BOOLEAN                       CommandSupported = FALSE;
    UINT8                         IdentificationCommandList [5] = { 1, 2, 3, 8, 11};
    UINT8                         *SdCommandClassList[] = { SdCommandClass0, SdCommandClass1, SdCommandClass2,\
                                  SdCommandClass3, SdCommandClass4, SdCommandClass5, SdCommandClass6, \
                                  SdCommandClass7, SdCommandClass8, SdCommandClass9, SdCommandClass10, SdCommandClass11 };
    UINT8                         *MmcCommandClassList[] = { MmcCommandClass0, MmcCommandClass1, MmcCommandClass2,\
                                      MmcCommandClass3, MmcCommandClass4, MmcCommandClass5, MmcCommandClass6, \
                                      MmcCommandClass7, MmcCommandClass8, MmcCommandClass9, MmcCommandClass10, MmcCommandClass11 };
    UINT8                         *SupportedClass;
    UINT64                        CommandTimeout;
    UINT32                        Remainder;
    
    if (Packet == NULL || Slot == 0xFF || Packet->SdMmcCmdBlk == NULL || Packet->SdMmcStatusBlk == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    // Finding the SdioDeviceInterface pointer
    SdioDevInterface = GetSdioDevInterface (
                                 SdMmcPassThruInstance->SdioBusInterface, 
                                 Slot);
    
    // If SdioDevInterface is NULL,then no device is connected to the Slot
    if (SdioDevInterface == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    if(SdioDevInterface->MassStorageDevice) {
        // Commands listed in IdentificationCommandList is supported only during Card initialization, Hence 
        // return EFI_UNSUPPORTED for these commands
        
        for (Index = 0; Index < sizeof (IdentificationCommandList); Index++ ) {
            
            // Refer Spec. Embedded Multi-Media Card Electrical Standard (5.1), Section 6.6
            // After the Device is assigned an RCA it will not respond to 
            // identification commands: CMD1, CMD2, or CMD3 
            if ( (Index > 2) && ((SdioDevInterface->SdioDevInfo->bMode == MMC_HIGH_CAP ) || 
                 (SdioDevInterface->SdioDevInfo->bMode == MMC_STAND_CAP )) ) {
                break;
            }
            
            if (IdentificationCommandList [Index] == Packet->SdMmcCmdBlk->CommandIndex) {
                return EFI_UNSUPPORTED;
            }	
        }
        
        //From the CSD register ( Bit 84: 95), get the Supported CommandClass for the card 
        CommandClass = (SdioDevInterface->SdioDevInfo->d4CSD[2] & 0xFFF00000) >> 20; 
        
        // Check whether the input packet command is supported or not.
        for (ClassIndex = 0; ClassIndex <= 11; ClassIndex++) {
            if(CommandClass & (1 << ClassIndex)) {
                if ((SdioDevInterface->SdioDevInfo->bMode == MMC_HIGH_CAP ) || 
                    (SdioDevInterface->SdioDevInfo->bMode == MMC_STAND_CAP )) {
                    // Get the supported command list for Sd card
                    SupportedClass = MmcCommandClassList [ClassIndex];
                } else {
                    // Get the supported command list for MMC card
                    SupportedClass = SdCommandClassList [ClassIndex];
                }
                for (Index = 0; SupportedClass [Index] != 0xFF; Index++ ) {
                    if (SupportedClass [Index] == Packet->SdMmcCmdBlk->CommandIndex) {
                        CommandSupported = TRUE;
                        break;
                    }
                }
            }
            if (CommandSupported) {
                break;
            }
        }
        //check for Sdio command lists
    } else if (SdioDevInterface->SdioDevInfo->IODevice) {
        for (Index = 0; SdIoCommandList[Index] != 0xFF; Index++ ) {
            if (SdIoCommandList[Index] == Packet->SdMmcCmdBlk->CommandIndex) {
                CommandSupported = TRUE;
                break;
            }
        }
      
    }
    
    // The command described by the SD Command Packet is not supported.
    if (!CommandSupported) {
        return EFI_UNSUPPORTED;
    }
    
    switch (Packet->SdMmcCmdBlk->ResponseType) {
        case SdMmcResponseTypeR1:
            Packet->SdMmcCmdBlk->ResponseType =  RESP1_TYPE;
            break;
        case SdMmcResponseTypeR1b:
            Packet->SdMmcCmdBlk->ResponseType = RESP1B_TYPE;
            break;
        case SdMmcResponseTypeR2:
            Packet->SdMmcCmdBlk->ResponseType =  RESP2_TYPE;
            break;
        case SdMmcResponseTypeR3:
            Packet->SdMmcCmdBlk->ResponseType =  RESP3_TYPE;
            break;
        case SdMmcResponseTypeR4: 
            Packet->SdMmcCmdBlk->ResponseType = RESP4_TYPE;
            break;
        case SdMmcResponseTypeR5: 
            Packet->SdMmcCmdBlk->ResponseType =  RESP5_TYPE;
            break;
        case SdMmcResponseTypeR5b:
            Packet->SdMmcCmdBlk->ResponseType =  RESP5B_TYPE;
            break;
        case SdMmcResponseTypeR6: 
            Packet->SdMmcCmdBlk->ResponseType =  RESP6_TYPE;
            break;
        case SdMmcResponseTypeR7: 
            Packet->SdMmcCmdBlk->ResponseType =  RESP7_TYPE;
            break;
    }
    CommandTimeout = Packet->Timeout;

    // Converting 100 nanoseconds unit to 1 microsecond unit
    if ((CommandTimeout != 0)) {
        CommandTimeout = MultU64x32 (Packet->Timeout,100);
        // Considering 1 millisecond as the default timeout value if the CommandTimeout
        // is less than 1 millisecond.
        if (CommandTimeout < 1000000) {
            CommandTimeout = 1;
        } else {
            CommandTimeout = DivU64x32Remainder (CommandTimeout,1000000, &Remainder);
            
            // After converting nanoseconds to millisecond, if there is any Remainder 
            // adding 1 millisecond to CommandTimeout
            if (Remainder != 0) {
                CommandTimeout = CommandTimeout + 1;
            }
        }
    } 
    
    if (Packet->SdMmcCmdBlk->CommandType != SdMmcCommandTypeAdtc) { // Process Non data commands
        
        Status = SdMmcCommand (
                        SdioDevInterface->SdioDevInfo,
                        Slot, 
                        (Packet->SdMmcCmdBlk->CommandIndex << 8) | (UINT16)(Packet->SdMmcCmdBlk->ResponseType), 
                        Packet->SdMmcCmdBlk->CommandArgument,
                        CommandTimeout);
        
        
    } else { // Process Data Commands
        
        //Packet defines a data command but both InDataBuffer
        //and OutDataBuffer are NULL.
        if ((Packet->InDataBuffer == NULL) && (Packet->OutDataBuffer == NULL)) {
            return EFI_INVALID_PARAMETER;
        }
        
        // Check for Read/Write Commands
        Read = (Packet->InDataBuffer) ? 1 : 0;
        
        TransferBuffer = (UINTN)(Read) ? Packet->InDataBuffer : Packet->OutDataBuffer;
        
        if (SdioDevInterface->MassStorageDevice) {
            
            // Calculate the maximum byte transfer supported by the host
            MaxBytes = MultU64x64 (((UINT64)SdioDevInterface->SdioDevInfo->dMaxLBA),
                         ((UINT64)SdioDevInterface->SdioDevInfo->wBlockSize));
        
            // The InTransferLength or OutTransferLength or exceeds the limit supported by SD card
            if (((UINTN)(Read) ? Packet->InTransferLength : Packet->OutTransferLength) > MaxBytes) {
                return EFI_BAD_BUFFER_SIZE;
            }
        
            //Calculate the block count for transfer
            NumBlks = ((UINTN)(Read) ? Packet->InTransferLength : Packet->OutTransferLength) \
                                            / SdioDevInterface->SdioDevInfo->wBlockSize;
        
            //Send Read/Write command
            Status = SdMmcReadWriteData (
                                   SdioDevInterface->SdioDevInfo,
                                   Slot,
                                   (UINT8)Packet->SdMmcCmdBlk->CommandIndex,
                                    Packet->SdMmcCmdBlk->CommandArgument,
                                    TransferBuffer,
                                    NumBlks,
                                    SdioDevInterface->SdioDevInfo->wBlockSize,
                                    (UINT16)Packet->SdMmcCmdBlk->ResponseType,
                                    FALSE,
                                    Read,
                                    CommandTimeout);
        } else if (SdioDevInterface->SdioDevInfo->IODevice) {
            
            Status = SdIoReadWriteCmd (
                                SdioDevInterface->SdioDevInfo,
                                Slot,
                                Packet->SdMmcCmdBlk->CommandIndex,
                                Packet->SdMmcCmdBlk->CommandArgument,
                                TransferBuffer,
                                (UINT16)Packet->SdMmcCmdBlk->ResponseType,
                                Read,
                                CommandTimeout);      
        }
 }
        
#if SDMMC_VERBOSE_PRINT
        DEBUG((EFI_D_VERBOSE,"SdMmc: PassThru Status = %r \n", Status));
#endif

    // Update the Status once transaction is completed.
    Packet->TransactionStatus = Status;
    
    if (!EFI_ERROR(Status)) {
        
        // Filling the Command Specific Response Data.
        Packet->SdMmcStatusBlk->Resp0 = SDIO_REG32(SdioDevInterface->SdioDevInfo->SdioBaseAddress,RESP0);
        Packet->SdMmcStatusBlk->Resp1 = SDIO_REG32(SdioDevInterface->SdioDevInfo->SdioBaseAddress,RESP1);
        Packet->SdMmcStatusBlk->Resp2 = SDIO_REG32(SdioDevInterface->SdioDevInfo->SdioBaseAddress,RESP2);
        Packet->SdMmcStatusBlk->Resp3 = SDIO_REG32(SdioDevInterface->SdioDevInfo->SdioBaseAddress,RESP3);
        return EFI_SUCCESS;
    }
    
    return EFI_DEVICE_ERROR;
}

/**
    Retrieves the next slot number for SdMmc devices on the
    SD controller.

    @param  This - A pointer to the EFI_SD_MMC_PASS_THRU_PROTOCOL instance.
    @param  Slot - Sdio slot number

    @retval EFI_SUCCESS or EFI_NOT_FOUND

**/

EFI_STATUS 
GetNextSlot (
    IN  EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
    IN  OUT UINT8                     *Slot
)
{
    SDIO_DEVICE_INTERFACE           *SdioDevInterface = NULL;
    LIST_ENTRY                      *DLink = NULL;
    SD_MMC_PASS_THRU_PROTOCOL       *SdMmcPassThruInstance = \
                                      (SD_MMC_PASS_THRU_PROTOCOL *)This;
    UINT8                           PreviousSlot;

    PreviousSlot = SdMmcPassThruInstance->PreviousSlot;
    
    // If Slot is NULL (or) If Slot is not 0xFF and Slot was not returned 
    // on a previous call to GetNextSlot()
    if (Slot == NULL || ((0xFF != *Slot ) && (PreviousSlot != *Slot))) {
        return EFI_INVALID_PARAMETER;
    }

    // If on input Slot is 0xFFFF, then the slot number of the first slot on the
    // SD controller is returned.
    if (0xFF == *Slot) {
        DLink = SdMmcPassThruInstance->SdioBusInterface->SdioDeviceList.ForwardLink;
        if (DLink == &SdMmcPassThruInstance->SdioBusInterface->SdioDeviceList) {
            return EFI_NOT_FOUND;
        }
        SdioDevInterface = BASE_CR(DLink, SDIO_DEVICE_INTERFACE, SdioDeviceLink);
        *Slot = SdioDevInterface->SlotNumber;
        SdMmcPassThruInstance->PreviousSlot = *Slot;
        return EFI_SUCCESS;
    }

    // If Slot is a slot number that was returned on a previous call to GetNextSlot(), 
    // then the slot number of the next slot on the SD controller is returned.
    if (PreviousSlot == *Slot) {
        
        for (DLink = SdMmcPassThruInstance->SdioBusInterface->SdioDeviceList.ForwardLink;
                DLink != &SdMmcPassThruInstance->SdioBusInterface->SdioDeviceList;
                DLink = DLink->ForwardLink) {
            // Find the SdioDeviceInterface pointer
            SdioDevInterface = BASE_CR (DLink, SDIO_DEVICE_INTERFACE, SdioDeviceLink);
            // If SdioDevInterface->SlotNumber exceeds the Previous Slot value, 
            // then initialize the Slot value accordingly
            if (SdioDevInterface->SlotNumber > *Slot) { 
                *Slot = SdioDevInterface->SlotNumber;
                SdMmcPassThruInstance->PreviousSlot = *Slot;
                return EFI_SUCCESS;
            }
            SdioDevInterface = NULL;
        }
    }
    return EFI_NOT_FOUND;
}


/**
    This function allocates and builds a device path node for 
    SD or eMMc card on the controller.

    @param  This       - Pointer to EFI_SD_MMC_PASS_THRU_PROTOCOL instance   
    @param  Slot       - Sdio slot numbeer
    @param  DevicePath - Pointer to EDI_DEVICE_PATH_PROTOCOL structure

    @retval EFI_SUCCESS or EFI_NOT_FOUND

**/
EFI_STATUS
BuildDevicePath (
    IN EFI_SD_MMC_PASS_THRU_PROTOCOL     *This,
    IN UINT8                             Slot,
     OUT EFI_DEVICE_PATH_PROTOCOL      **DevicePath
)
{
    EFI_STATUS                    Status;
    EFI_DEVICE_PATH_PROTOCOL      *TempDevicePath;
    SDIO_DEVICE_INTERFACE         *SdioDevInterface = NULL;
    SD_MMC_PASS_THRU_PROTOCOL     *SdMmcPassThruInstance = \
                                          (SD_MMC_PASS_THRU_PROTOCOL *)This;
  
    // If DevicePath is null, return EFI_INVALID_PARAMETER
    if(NULL == DevicePath) {
        return  EFI_INVALID_PARAMETER;
    }

    // Allocate memory for the DevicepathNode
    Status = gBS->AllocatePool (
                          EfiBootServicesData,
                          sizeof(SD_DEVICE_PATH),
                          (VOID**)DevicePath);
    if (EFI_ERROR(Status)) {           
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Finding the SdioDeviceInterface pointer
    SdioDevInterface = GetSdioDevInterface (
                                   SdMmcPassThruInstance->SdioBusInterface, 
                                   Slot);
    // The SD card specified by Slot does not exist on the SD controller
    if (SdioDevInterface == NULL) {
        gBS->FreePool (*DevicePath);      
        *DevicePath = NULL;
        return EFI_NOT_FOUND;
    }
    
    TempDevicePath = SdioDevInterface->DevicePathProtocol;
    
    // Get the SD or Mmc Device Path Node
    while (!IsDevicePathEnd (TempDevicePath)) {
        if ((TempDevicePath->Type == MESSAGING_DEVICE_PATH) \
               && (TempDevicePath->SubType == MSG_SD_DP || TempDevicePath->SubType == MSG_EMMC_DP)) {
            
            gBS->CopyMem (*DevicePath, TempDevicePath, sizeof(SD_DEVICE_PATH));
            return EFI_SUCCESS;
        }
        TempDevicePath = NextDevicePathNode (TempDevicePath);
    }
    
    // Returning NULL if devicePath doesn't match
    gBS->FreePool (*DevicePath);      
    *DevicePath = NULL;    
     
    return EFI_NOT_FOUND;
}

/**
    Retrieves an SD card slot number based on the input device path.
    
    @param This       - Pointer to EFI_SD_MMC_PASS_THRU_PROTOCOL instance
    @param DevicePath - Pointer to EFI_DEVICE_PATH_PROTOCOL structure
    @param Slot       - Sdio slot number

    @retval EFI_STATUS

**/
EFI_STATUS 
GetSlotNumber (
    IN EFI_SD_MMC_PASS_THRU_PROTOCOL    *This,
    IN EFI_DEVICE_PATH_PROTOCOL         *DevicePath,
    OUT UINT8                           *Slot
) 
{
    UINT16        DevicePathLength = 0;

    if (!DevicePath || !This || !Slot) {
        return EFI_INVALID_PARAMETER;
    }
    
    //Calculate DevicepathLength
    DevicePathLength = (DevicePath)->Length[0] | (DevicePath)->Length[1] << 8;
    
    // Retrieves the slot number form the device path
    if ((DevicePath->Type == MESSAGING_DEVICE_PATH) && (DevicePath->SubType == MSG_SD_DP || \
           DevicePath->SubType == MSG_EMMC_DP ) && (DevicePathLength == sizeof(SD_DEVICE_PATH) || \
                                           DevicePathLength == sizeof(EMMC_DEVICE_PATH))) {
                       
        *Slot = DevicePath->SubType == MSG_SD_DP ? \
                    ((SD_DEVICE_PATH *)DevicePath)->SlotNumber : ((EMMC_DEVICE_PATH *)DevicePath)->SlotNumber;
        
        return EFI_SUCCESS;
    }
    
    return EFI_UNSUPPORTED;	
}

/**
    Resets an SD card that is connected to the SD controller.
    
    @param  This - Pointer to EFI_SD_MMC_PASS_THRU_PROTOCOL instance
    @param  Slot - Sdio slot number

    @retval EFI_SUCCESS or EFI_NOT_FOUND

**/

EFI_STATUS
ResetDevice (
    IN  EFI_SD_MMC_PASS_THRU_PROTOCOL  *This,
    IN  UINT8                          Slot
)
{
    UINT16                        CommandIndex;
    UINT32                        CommandArgument;
    SDIO_DEVICE_INTERFACE         *SdioDevInterface = NULL;
    SD_MMC_PASS_THRU_PROTOCOL     *SdMmcPassThruInstance = \
                                      (SD_MMC_PASS_THRU_PROTOCOL *)This;
    EFI_STATUS                    Status;
    
    // Slot number is invalid.
    if (Slot == 0xFF) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Finding the SdioDeviceInterface pointer
    SdioDevInterface = GetSdioDevInterface (
                                 SdMmcPassThruInstance->SdioBusInterface, 
                                 Slot);
    
    // SD Device not present in the Slot.
    if (SdioDevInterface == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    if (SdioDevInterface->SdioDevInfo->IODevice ) {
        CommandIndex = (IO_RW_DIRECT << 8) | (RESP5_TYPE);
        
        //Enable RES (bit-3) of IO_ABORT register
        CommandArgument = (MAKE_SDIO_RW(1)| MAKE_SDIO_OFFSET (IO_ABORT_REGISTER) | RESET);
  
        
        Status = SdMmcCommand (
                          SdioDevInterface->SdioDevInfo,
                          Slot,
                          CommandIndex,
                          CommandArgument,
                          SD_MMC_COMMAND_TIMEOUT);	    
        
    } else {
        // Issue CMD0 with argument of 0x00000000 to reset the device.
        CommandIndex = GO_IDLE_STATE_CMD0;
        CommandArgument = 0;
        Status = SdMmcCommand (
                         SdioDevInterface->SdioDevInfo,
                         Slot,
                         CommandIndex,
                         CommandArgument,
                         SD_MMC_COMMAND_TIMEOUT);
    }
    
#if SDMMC_VERBOSE_PRINT
        DEBUG((EFI_D_VERBOSE,"SdMmc: Reset Status = %r\n", Status));
#endif  
        
    if(EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    
    return EFI_SUCCESS;
}

