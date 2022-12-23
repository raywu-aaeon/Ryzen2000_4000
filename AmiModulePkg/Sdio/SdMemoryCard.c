//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file Sd.c
    Functions to handle Sd related function

**/
//----------------------------------------------------------------------
#include <SdioController.h>
//----------------------------------------------------------------------

/**
    To program the power and get the OCR

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure 
    @param  Port        - SDIO port number
    @param  Argument
    @param  Response

    @retval EFI_STATUS
    Note: This function is referred from 4.2.3 Card Initialization and 
    Identification Process from Physical Layer Simplified Specification
     Version 4.10
    
**/
EFI_STATUS
SDGetOcr (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT32              Argument,
    OUT UINT32              *Response
) 
{
    EFI_STATUS  Status;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    UINT16      Index;
    
    for (Index = 0; Index <= SD_POWERUP_TIMEOUT; Index++) {
        //
        // Issue CMD 55. CMD55 will fail for MMC card until the card
        // is in standby state(i.e after CMD3(SEND_RELATIVE_ADDR) is sent).
        // Please check the MMCA 4.1(JESD84-A441) Specification.
        //
        CommandIndex = (APP_CMD_CMD55 << 8) | (RESP1_TYPE);
        CommandArgument = 0;
        Status = SdMmcCommand (
                         SdioDevInfo,
                         Port,
                         CommandIndex,
                         CommandArgument,
                         SD_MMC_COMMAND_TIMEOUT);
        if (EFI_ERROR(Status)) {
            return EFI_DEVICE_ERROR;
        }
        
        CommandIndex = (SD_SEND_OP_COND_ACMD41 << 8) | (RESP3_TYPE);
        Status = SdMmcCommand (
                SdioDevInfo, 
                Port, 
                CommandIndex,
                Argument,
                SD_MMC_COMMAND_TIMEOUT);
        if (EFI_ERROR(Status)) {
            return EFI_DEVICE_ERROR;
        }
    
        *Response = SDIO_REG32(SdioBaseAddr, RESP0);
        if (*Response & CARD_POWERUP_STATUS_BIT) {
            return EFI_SUCCESS;
        }
        
        //
        // Delay for 10 Msec
        // 
        MicroSecondDelay (10000);
    } 
    return EFI_NOT_FOUND;;
}

/**
    Set the Clock value for the Sd device

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - SDIO port number

    @retval EFI_STATUS
    Note : This function follows :
    1. Jedec eMMC Electrical Standard 5.01
    2. SD Host Controller Simplified Specification Version 3.00 
**/
EFI_STATUS
SdCardSetClock (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT32      MaxCardClk = 0;
    UINT32      MaxHstClk = 0;
    BOOLEAN     HighSpeedSupport = FALSE;
    EFI_STATUS  Status;
    UINT8       SdCardModeSupport;
    UINT32      MaxAllowedClock = 25000000;

    // 
    // This function will check HighSpeedSupport support for host and will 
    // calculate the maximum host controller frequency and maximum card 
    // frequency
    //
    CalculateMaxCardAndHostFreq (
                            SdioDevInfo, 
                            Port, 
                            &HighSpeedSupport, 
                            &MaxCardClk,
                            &MaxHstClk);
    

    //
    // If Card supports SPEC 3 or if card belong to Class10 set high speed 
    // mode
    //
    if (HighSpeedSupport) {
        if ((((SdioDevInfo->d2SCR[7] & 0x0F) == 2) &&       // SD_SPEC ==2
                (SdioDevInfo->d2SCR[5] & BIT7)) ||         // SD_SPEC3 == 1
                (SdioDevInfo->d4CSD[2] & BIT30)) {          // class 10 of CCC field is set
            Status = SdQueryMode(SdioDevInfo, Port, &SdCardModeSupport, 0);
            if ((Status == EFI_SUCCESS) && (SdCardModeSupport &SD_HIGH_SPEED)) {
                Status = SdSetMode (SdioDevInfo, Port, SD_HIGH_SPEED, 0);
                if (!EFI_ERROR(Status)) {
                    MaxAllowedClock = 50000000;
                }
            }
        }
        
    }
    //
    // In Normal mode we try to set the clock to 25Mhz or less 
    //
    if ((MaxHstClk <= MaxCardClk ) && (MaxHstClk < MaxAllowedClock)) {
        Status = ControllerSetClock (SdioDevInfo, Port, MaxHstClk);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else if ((MaxCardClk < MaxHstClk ) && (MaxCardClk < MaxAllowedClock)) {
        Status = ControllerSetClock (SdioDevInfo, Port, MaxCardClk);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else {
        Status = ControllerSetClock (SdioDevInfo, Port, MaxAllowedClock);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    return EFI_SUCCESS;
}

/**
    Get the RCA value from the SD card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - SDIO port number

    @retval EFI_STATUS
    Noate: This function follows 4.2.3 Card Initialization and 
           Identification Process from Physical Layer Simplified 
           Specification Version 4.10
           1. Issue CMD3
           2. Receive R6, and get the Device's RCA.
**/
EFI_STATUS
SDCardGetRCA (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{

    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;

    if ((SdioDevInfo->bState != CARDSTATUS_IDENT) &&
        (SdioDevInfo->bState != CARDSTATUS_STBY)) {
        return EFI_DEVICE_ERROR;
    }

    //
    // Issue CMD3 for SD device.
    //
    CommandIndex = ((SEND_RELATIVE_ADDR_CMD3 << 8) | RESP6_TYPE);
    CommandArgument = 0;
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port,
                     CommandIndex,
                     CommandArgument, 
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    SdioDevInfo->wRCA = (UINT16)(SDIO_REG32(SdioBaseAddr, RESP0) >> 16);
    SdioDevInfo->bState = CARDSTATUS_STBY;

    return EFI_SUCCESS;
}

/**
    Get Sd card SCR value

    @param  SdioDevInfo 
    @param  Port 

    @retval EFI_STATUS
    Note: This function is following Physical Layer Simplified 
        Specification Version 4.10
        1. Issue ACMD41
    

**/
EFI_STATUS
SDCardGetSCR (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    EFI_STATUS  Status;
    UINT8       TransferAddress[8];
    UINT8       Index;

    Status = SdMmcReadWriteData (
                           SdioDevInfo,
                           Port, 
                           SEND_SCR_ACMD51,
                           0,
                           (UINT32*)&TransferAddress[0], 
                           0, 
                           8,
                           RESP1_TYPE,
                           TRUE, 
                           TRUE,
                           (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // The output data format: MSB comes first for the ACMD51. So reverse the 
    // Data to get the proper SCR fields.
    //
    for (Index = 0; Index < 8; Index++) {
        SdioDevInfo->d2SCR[Index] = TransferAddress[7-Index];
    }
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"SdMmc: SCR Bus width supported by card = 0x%x \n", SdioDevInfo->d2SCR[6]&0xf));
    switch(SdioDevInfo->d2SCR[7]) {
        case 0: DEBUG((EFI_D_VERBOSE ,"SdMmc: Sd card Spec version 1.0 and 1.01 \n"));
                break;
        case 1: DEBUG((EFI_D_VERBOSE ,"SdMmc: Sd card Spec version 1.10 \n"));
        break;
        case 2: if(SdioDevInfo->d2SCR[5] >> 7 == 1) {
                    if( (SdioDevInfo->d2SCR[5] >> 2) & 1){
                        DEBUG((EFI_D_VERBOSE ,"SdMmc: Sd card Spec version 4.XX\n"));
                        break;
                    } else {
                        DEBUG((EFI_D_VERBOSE ,"SdMmc: Sd card Spec version 3.0X\n"));
                        break;
                    }
                }
        default: DEBUG((EFI_D_VERBOSE ,"SdMmc: Sd card Spec version 2.00\n"));
                break;
    }
#endif
    return Status;
}

/**
    Set the Bus width for the card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - SDIO port number 

    @retval EFI_STATUS
    Note: This function follows the Section A.6.2 Switching to high-speed 
        mode of Jedec Electrical standard 5.01
        1. Get SCR and check [51:48] bit for supported bus with
           according to 5.6 SCR register from Physical Layer Simplified 
           Specification Version 4.10
        2. If supported Issue CMD55+ACMD6
**/
EFI_STATUS
SdCardBuswidth (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;
    
    Status = SDCardGetSCR(SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
#if SDMMC_VERBOSE_PRINT
        SdioDevInfo->MmcBusWidth = 1;
#endif
    //
    // Check the Bus width. Bit 48-51 gives the bus width in SCR field.
    //
    if (SdioDevInfo->d2SCR[6] & BIT2) {

        //
        //Issue CMD55
        //

        CommandIndex = ((APP_CMD_CMD55 << 8) | RESP1_TYPE);
        CommandArgument = (UINT32)SdioDevInfo->wRCA;
        CommandArgument = CommandArgument << 16;
        Status = SdMmcCommand (
                         SdioDevInfo,
                         Port,
                         CommandIndex,
                         CommandArgument,
                         SD_MMC_COMMAND_TIMEOUT);

        if (EFI_ERROR(Status)) {
            return Status;
        }

        //
        //Issue ACMD6
        //
        CommandIndex = ((SET_BUS_WIDTH_ACMD6 << 8) | RESP1_TYPE);
        CommandArgument = 2;
        Status = SdMmcCommand (
                         SdioDevInfo,
                         Port, 
                         CommandIndex,
                         CommandArgument, 
                         SD_MMC_COMMAND_TIMEOUT);

        if (EFI_ERROR(Status)) {
            return Status;
        }
#if SDMMC_VERBOSE_PRINT
        SdioDevInfo->MmcBusWidth = 4;
#endif
        SDIO_REG8_OR(SdioBaseAddr, HOSTCTL, DATA_TRANSFER_4BITMODE);

    }

    return EFI_SUCCESS;
}

/**
    Initialize the SD card.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - SDIO port number

    @retval EFI_STATUS
    Note: This function is as per Jedec eMMC Electrical Standard 5.01
          (Sec A.6.1 Bus initialization step 4 to 36).
**/
EFI_STATUS
SdCardInit (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{

    EFI_STATUS  Status;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
#if UHS_SD_SUPPORT
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT32      PresentState;
    UINT32      Temp32;
    UINT32      CapValue;
#endif
    SdioDevInfo->VoltageSwitch = FALSE;
    
    //
    // As per Section 4.2.2 Operating Condition Validation Issueing CMD0
    //
    CommandIndex = GO_IDLE_STATE_CMD0;
    CommandArgument = 0;
    Status=SdMmcCommand (
                   SdioDevInfo,
                   Port,
                   CommandIndex, 
                   CommandArgument, 
                   SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // As per Section 4.2.2 Operating Condition Validation Get Ocr
    //
    Status = SdSetVoltage (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
#if UHS_SD_SUPPORT
    //
    // Check if 1.8V switch is Accepted
    //
    CapValue = SDIO_REG32(SdioBaseAddr, CAP);
    if ((SdioDevInfo->bHostControllerVersion >= HOST_CONTROLLER_VER3) && (CapValue & VOLTAGE_SUPPORT_18) && \
          (SdioDevInfo->dOCR & SWITCHING_18V_ACCEPTED)) {
                
        SDIO_REG8_AND(SdioBaseAddr, PWRCTL, ~PWRCTL_POWER_ENABLE);
        SDIO_WRITE_REG8(SdioBaseAddr, PWRCTL, PWRCTL_18V);
        SDIO_REG8_OR(SdioBaseAddr, PWRCTL, PWRCTL_POWER_ENABLE);
        
        //
        // Delay mentioned in step 11 of A.6.1 Bus initialization of JEDEC 
        // Ver5.01
        //
        MicroSecondDelay (1000);
        
        //
        // Stop providing SD clock to the card.As mentioned in step 4 of sec 
        // Signal Voltage Switch Procedure of Sd host controller 3.00
        // 
        SDIO_REG8_AND(SdioBaseAddr, CLKCTL, ~CLKCTL_CLOCK_ENABLE);
        ControllerSetClock (SdioDevInfo, Port, 400000);
        
        
        //
        // Issue switch command according to 4.2.4 Bus Signal Voltage Switch
        // Sequence
        //
        CommandIndex = ((SWITCH_COMMAND_CMD11 << 8) | RESP1_TYPE);
        CommandArgument = 0;
        Status = SdMmcCommand (SdioDevInfo, Port, CommandIndex, CommandArgument);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        
        //
        // As mentioned in step 6 of sec Signal Voltage Switch Procedure
        // of Sd host controller 3.00
        //
        SDIO_REG8_OR(SdioBaseAddr, HOSTCTL2, SIGNALING_ENABLE_1_8V);
        
        //
        // Delay is mentioned in 3.6.1 Signal Voltage Switch Procedure of step 7.
        //
        MicroSecondDelay (5000);
        Temp32 = SDIO_REG32(SdioBaseAddr, HOSTCTL2);
        
        //
        // Check 1.8V set as per step 8 of sec 3.6.1 Signal Voltage Switch 
        // Procedure of Sd host controller 3.00
        //
        if (Temp32 & SIGNALING_ENABLE_1_8V) {
            //
            // Set the clock to 400KHZ
            //
            //Status = ControllerSetClock(SdioDevInfo,Port,25000000);
            
            //
            // Delay is mentioned in 3.6.1 Signal Voltage Switch Procedure 
            // of step 10.
            // 
            MicroSecondDelay (1000);
            
            //
            // Check DAT[3:0] is 1111b as per step 11 of sec 3.6.1 Signal 
            // Voltage Switch Procedure of Sd host controller 3.00
            //
            PresentState = SDIO_REG32(SdioBaseAddr, PSTATE);
        
            PresentState = PresentState >> 20;
            PresentState &= 0xf;
            
            //
            // DAT[3:0] should 1111b
            //
            if (PresentState != 0xf) {
                return EFI_DEVICE_ERROR;
            }
            SdioDevInfo->VoltageSwitch = TRUE;
            
        }
    }
#endif
        
    //
    // Get CID from card as per  4.2.3 Card Initialization and Identification
    //  Process of Physical Layer Simplified Specification Version 4.10
    //
    Status = SdMmcCardGetCID (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Get RCA from card as per  4.2.3 Card Initialization and Identification
    //  Process of Physical Layer Simplified Specification Version 4.10
    //
    Status = SDCardGetRCA (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Get CSD as per Section 4.3 Data Transfer Mode of Physical Layer
    // Simplified Specification Version 4.10
    //
    Status = SdMmcCardGetCSD (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // CMD7 is used to select one card and put it into the Transfer State
    // 4.3 Data Transfer Mode of Physical Layer Simplified Specification 
    // Version 4.10
    //
    Status = SdMmcCardSelect (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    if (SdioDevInfo->VoltageSwitch == FALSE) {
        //
        // In Data Transfer Mode the host switch the card frequency
        // from F(OD) to F(PP) frequency range
        //
        Status = SdCardSetClock (SdioDevInfo, Port);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    //
    // Asper 4.3.1 Wide Bus Selection/Deselection The bus width must be
    // selected in Tran state. 
    // 
    Status = SdCardBuswidth (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    if (SdioDevInfo->VoltageSwitch == TRUE) {
        //
        // Set the UHS mode according to the card and controller
        //
        Status = SdCardSetUhsMode (SdioDevInfo, Port);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    //
    //Get the device capacity
    //
    Status = SdMassGetCapacity (SdioDevInfo, Port);
    return Status;

}

/**
    Get the SD device capacity

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - SDIO port number 

    @retval EFI_STATUS

**/
EFI_STATUS
SdMassGetCapacity (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT32      CSize;
    UINT8       BlockLength;
    UINT16      CommandIndex;
    UINT32      Mult;
    EFI_STATUS  Status;

    if ((SdioDevInfo->bCsdStruct > 0) && (SdioDevInfo->bMode == SD_HIGH_CAP)) { 
        //
        //CSD20. Device size is from bit 48-69.
        //
        CSize = ((SdioDevInfo->d4CSD[1]) >> 16) & 0xffff;
        CSize = CSize | ((SdioDevInfo->d4CSD[2] << 16) & 0x3f0000);
        
        //
        // memory capacity = (C_SIZE+1) * 512KByte
        // So number of blocks= (CSize+1) << 10 and BlockSize is 512
        // 
        SdioDevInfo->dMaxLBA = (CSize+1) << 10;
        SdioDevInfo->wBlockSize = BLOCK_SIZE;
    } else {
        //
        // Bit80-83 is Max. read data block length for the MMC.
        // BLOCK_LEN = 2^(READ_BL_LEN), (READ_BL_LEN < 12)
        //
        BlockLength = (UINT8)((SdioDevInfo->d4CSD[2] & MAX_READ_BLOCK_LENGTH) >> 16);
        SdioDevInfo->wBlockSize = (1 << BlockLength);
        
        //
        // MMC(following spec > 4.0) should have C_SIZE as 0xFFF and
        // dMaxLBA is calculated from SEC_COUNT register.
        //
        CSize = ((SdioDevInfo->d4CSD[1] & DEVICE_SIZE_1L) >> 30) | \
                    ((SdioDevInfo->d4CSD[2] & DEVICE_SIZE_1H) << 2);
        
        
        
        //
        // Bit47-49 is Device size multipier
        // MULT = 2^(C_SIZE_MULT+2) (C_SIZE_MULT < 8)
        // 
        //
        Mult = (SdioDevInfo->d4CSD[1] & (DEVICE_SZIE_MUL_1)) >> 15;
        Mult = (1<<(Mult+2));
        
        //
        // BLOCKNR (number of block)= (C_SIZE+1) * MULT
        //
        SdioDevInfo->dMaxLBA = (CSize+1) * Mult;
        
        // If the BlockSize exceeds 512 bytes for SDSC card, , then Set the Blocklength to 
        // default blocksize (512) using CMD16 (SET_BLOCK_LEN). 
        if (SdioDevInfo->wBlockSize > BLOCK_SIZE) {            
            CommandIndex = (SET_BLOCKLEN << 8) | (RESP1_TYPE);
            Status = SdMmcCommand (
                             SdioDevInfo, 
                             Port, 
                             CommandIndex,
                             BLOCK_SIZE,
                             SD_MMC_COMMAND_TIMEOUT);
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
            // Modify the MaxLBA as per new BLOCK_SIZE (512)
            SdioDevInfo->dMaxLBA *= (SdioDevInfo->wBlockSize / BLOCK_SIZE);
            SdioDevInfo->wBlockSize = BLOCK_SIZE;
        }   
    }

    // LBA address starts from 0 so the maximum accessible 
    // address should be one less than the max.

    SdioDevInfo->dMaxLBA -= 1;
    return EFI_SUCCESS;
}

/**
    To program the power and get the OCR

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - SDIO port numbers 

    @retval EFI_STATUS
    Note: According to Section 4.2.2 Operating Condition Validation
    
**/
EFI_STATUS
SdSetVoltage (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;
    UINT32      Response;
#if UHS_SD_SUPPORT
    UINT32      CapValue;
#endif
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;

#if UHS_SD_SUPPORT
    CapValue = SDIO_REG32(SdioBaseAddr, CAP);
#endif    
    //
    // According to Section 4.2.2 Operating Condition Validation CMD8
    // should be issued prior to AMCD41 for the SDXC and SDHC to initialize
    //
    CommandIndex = (SEND_IF_COND_CMD8 << 8) | (RESP7_TYPE);
        
    // 
    // The CMD8's lower 8 bit is check patern and BIT8-BIT is VHS
    // (Voltage Suplied). VHS=0001 is 2.7-3.6V.
    //
    CommandArgument = 0x1aa;
    Status = SdMmcCommand (
                     SdioDevInfo, 
                     Port,
                     CommandIndex,
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    Response = SDIO_REG32(SdioBaseAddr, RESP0);
    if ((!EFI_ERROR(Status)) && Response == 0x1aa) {
        
#if UHS_SD_SUPPORT
        //
        // Check if 1.8V is supported by Host controller. To query the 1.8V request for card.
        //
        if ((SdioDevInfo->bHostControllerVersion >= HOST_CONTROLLER_VER3) && (CapValue & VOLTAGE_SUPPORT_18)) {
            SdioDevInfo->SdVoltageWindow |= CARD_REQUEST_18V;
        }
#endif
        //
        // It is a high capacity card(SDXC or SDHC)
        //
        SdioDevInfo->SdVoltageWindow |= CARD_CAPACITY_STATUS;
    }
    
    //
    // As per 4.2.2 Operating Condition Validation and 4.2.3 Card 
    // Initialization and Identification Process
    //
    Status = SDGetOcr (
                  SdioDevInfo, 
                  Port, 
                  SdioDevInfo->SdVoltageWindow, 
                  &Response);
    if (EFI_ERROR(Status)) {
        return EFI_NOT_FOUND;
    }
    SdioDevInfo->dOCR = Response;
    
    if (Response & CARD_CAPACITY_STATUS) {
        SdioDevInfo->bMode = SD_HIGH_CAP;
    } else {
        SdioDevInfo->bMode = SD_STAND_CAP;
    }
    
    SdioDevInfo->bState = CARDSTATUS_READY;
    
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"SdMmc: Sd Card Found.. Initializing Sd Memory Card\n"));
#endif
    return EFI_SUCCESS;
}

/**
    This function will set the speed mode for host and card. 

    @param  SdioDevInfo      - Pointer to SDIO_DEVICE_INFO structure
    @param  Port             - SDIO port number   
    @param  SdCardMode       - SD card speed mode
    @param  SdControllerMode - To check id UHS is supported bu host

    @retval EFI_STATUS
    Note : This function follows :
    1. 4.3.10 Switch Function Command of Physical Layer Simplified 
       Specification Version 4.10
**/
EFI_STATUS
SdSetMode (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT16              SdCardMode,
    IN  UINT8               SdControllerMode
)
{
    EFI_STATUS  Status;
    UINT16      CommandIndex;
    UINT32      CommandArgument = 0;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    
    //
    // Send the Switch command for the selected speed mode
    //
    CommandIndex = ((SWITCH_FUNC_CMD6 << 8) | RESP1B_TYPE);
    CommandArgument = (0x80000000)|SdCardMode;
    Status = SdMmcCommand (
                     SdioDevInfo, 
                     Port,
                     CommandIndex,
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // If UHS is supported, set the UHS mode in Host 
    //
    if (SdControllerMode) {
        SDIO_REG16_AND_OR(SdioBaseAddr, HOSTCTL2, ~UHS_MODE_SELECT, SdControllerMode);
    }

#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE," Sd  Speed Mode set to %x", SdCardMode));
#endif
    
    return EFI_SUCCESS;
}

/**
    This function will issue CMD6(switch command) to check the 
    supported mode for SD cards

    @param  SdioDevInfo      - Pointer to SDIO_DEVICE_INFO structure
    @param  Port             - Sdio port number
    @param  SdSpeedMode      - SD card speed mode
    @param  SdPowerLimitMode - SD card Power limit mode

    @retval UINT8
    Note : This function follows :
    1. 4.3.10 Switch Function Command of Physical Layer Simplified 
       Specification Version 4.10
**/
EFI_STATUS
SdQueryMode (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    OUT UINT8               *SdSpeedMode,
    OUT UINT8               *SdPowerLimitMode
)
{
    EFI_STATUS  Status;
    UINT8       CMD6Status[64];
    
    *SdSpeedMode = 0;
    if (SdPowerLimitMode) {
        *SdPowerLimitMode = 0;
    }
    
    Status = SdMmcReadWriteData (
                            SdioDevInfo,\
                            Port,\
                            SWITCH_FUNC_CMD6,\
                            0,\
                            (UINT32*)&CMD6Status[0],\
                            1,\
                            CMD6_STATUS_BLOCKSIZE,\
                            RESP1_TYPE,\
                            FALSE,\
                            TRUE,
                            (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    if (EFI_ERROR(Status)) {
      return Status;
    }
    
    *SdSpeedMode = (CMD6Status[CMD6_STATUS_BLOCKSIZE - 1 - 50]) & 0x1F;
    if (SdPowerLimitMode) {
        *SdPowerLimitMode = (CMD6Status[CMD6_STATUS_BLOCKSIZE - 1 - 56]) & 0x1F;
    }
    
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE," Sd supported Mode  %x \n",SdSpeedMode));
#endif 
    
    return EFI_SUCCESS;
}

/**
    This function is called to set the UHS mode in SD card and 
    controller

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval UINT8
    Note : This function follows :
    1. 4.3.10 Switch Function Command of Physical Layer Simplified 
       Specification Version 4.10
**/
EFI_STATUS
SdCardSetUhsMode
(
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    EFI_STATUS  Status;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT8       SdCardModeSupport;
    UINT8       SdPowerLimit;
    UINT16      SdPowerMode = 0;
    UINT32      UpperCapValue;
    
    //
    // Check the supported UHS Modes in SD card. According to 4.3.10 
    // Switch Function Command
    //
    Status = SdQueryMode (
                    SdioDevInfo,
                    Port,
                    &SdCardModeSupport,
                    &SdPowerLimit);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Check the support Power limit according to Table 4-11 : Available
    // Functions of CMD6
    //
    if (SdPowerLimit & SD_PW1_8W_SUPPORT) {
        SdPowerMode = SD_PW1_8W;
    } else if (SdPowerLimit & SD_PW1_44W_SUPPORT) {
        SdPowerMode = SD_PW1_44W;
    }
    
    
    UpperCapValue = SDIO_REG32(SdioBaseAddr, CAP + 4);
    
    //
    // Select the supported modes in card and controller
    //
    if ((UpperCapValue & DDR50_SUPPORT_CAP) && (SdCardModeSupport & SD_DDR50)) {
        
        //
        // Select DDR50 in card and controller
        //
        Status = SdSetMode (
                      SdioDevInfo,
                      Port,
                      (DDR50_UHS_SELECT | SdPowerMode),
                      DDR50_UHS_SELECT);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        ControllerSetClock (SdioDevInfo, Port, 50000000);
    } else if ((UpperCapValue & SDR50_SUPPORT_CAP) && (SdCardModeSupport & SD_SDR50) && (!(UpperCapValue & TUNE_SDR50))) {
        
        //
        // Select SDR50 in card and controller. 
        //
        Status = SdSetMode (
                      SdioDevInfo,
                      Port, 
                      (SDR50_UHS_SELECT | SdPowerMode), 
                      SDR50_UHS_SELECT);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        ControllerSetClock (SdioDevInfo, Port, 100000000);
    } else if (SdCardModeSupport & SD_SDR25) {
        //
        // Select SDR25 in card and controller
        //
        Status = SdSetMode (
                      SdioDevInfo, 
                      Port, 
                      (SDR25_UHS_SELECT | SdPowerMode),
                      SDR25_UHS_SELECT);
        if (EFI_ERROR(Status)) {
            return Status;
        }
        ControllerSetClock (SdioDevInfo, Port, 50000000);
    } 
    MicroSecondDelay (10000);
    
    return EFI_SUCCESS;
}

