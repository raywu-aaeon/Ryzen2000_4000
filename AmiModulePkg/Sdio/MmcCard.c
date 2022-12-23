//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Mmc.c
    Functions to handle Mmc related function

**/
//----------------------------------------------------------------------
#include <SdioController.h>
//----------------------------------------------------------------------

/**
    To program the power and get the OCR

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number
    @param  Argument    - Input argument for the command
    @param  Response    - Response type for the command 

    @retval EFI_STATUS
    Note: Following step 4 to 9 Jedec Electrical standard 4.51 and 5.01
    
**/
EFI_STATUS
MmcGetOcr (
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
    

    //
    // Older version i.e Jedec Electrical standard 4.51 suggest to issue cmd0
    // (as per step 4 from A.6.1 Bus initialization). The second time when 
    // MmcGetOcr funtion is called i.e while programming for  1.8 V switching  
    // the card will be in ready state 
    //
    CommandIndex = GO_IDLE_STATE_CMD0;
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


    //
    // Issue CMD1 to get OCR (as per step 4 from Sec A.6.1 Bus initialization)
    // mentioned Jedec Electrical standard 5.01
    //
    CommandIndex = (SEND_OP_COND_CMD1 << 8) | (RESP3_TYPE);
    
    //
    // Issue cmd1 for atleast 1 sec as per (10.1.2 eMMC power-up guidelines)
    // from Jedec Electrical standard 5.01  
    //
    for (Index=0; Index <= MMC_POWERUP_TIMEOUT; Index++) {
        Status = SdMmcCommand (
                         SdioDevInfo,
                         Port, 
                         CommandIndex,
                         Argument, 
                         SD_MMC_COMMAND_TIMEOUT);
        if (EFI_ERROR(Status)) {
            return EFI_DEVICE_ERROR;
        }
        
        //
        // Check if busy bit is set.
        //
        *Response = SDIO_REG32 (SdioBaseAddr, RESP0);
        if (*Response & CARD_POWERUP_STATUS_BIT) {
            return EFI_SUCCESS;
        }
        
        //
        // Delay for 10 Msec
        // 
        MicroSecondDelay (10000);
    }

    return EFI_TIMEOUT;
}

/**
    Set the Clock value for the MMC device

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note : This function follows :
    1. Jedec eMMC Electrical Standard 5.01
    2. SD Host Controller Simplified Specification Version 3.00 
**/
EFI_STATUS
MmcCard_SetClock (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT32      MaxCardClk = 0;
    BOOLEAN     HighSpeedSupport = FALSE;
    UINT32      MaxHstClk;
    EFI_STATUS  Status;
    UINT32      UpperCapValue;
    UINT32      LowerCapValue;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    
    // 
    // This function will check HighSpeedSupport support for host and will 
    // calculate the maximum host controller frequecy and maximum card 
    // frequecy
    //
    CalculateMaxCardAndHostFreq (
                            SdioDevInfo, 
                            Port, 
                            &HighSpeedSupport, 
                            &MaxCardClk,
                            &MaxHstClk);

    //
    // If host support Highspeed and card support High-Speed eMMC @ 52MHz then set to 52 Mhz
    // else if host support Highspeed and card support High-Speed eMMC @ 26MHz set to 26 Mhz
    // else set to normal mode
    //
    UpperCapValue = SDIO_REG32(SdioBaseAddr, CAP+4);
    LowerCapValue = SDIO_REG32(SdioBaseAddr, CAP);
    
    // Set to DDR50 mode if supported
    if ((UpperCapValue & DDR50_SUPPORT_CAP) && (LowerCapValue & VOLTAGE_SUPPORT_18) && (HighSpeedSupport) && \
          (SdioDevInfo->bMmcCardType & MMC_HS_DDR_52_18V30V )) {        
        if (!SdioDevInfo->VoltageSwitch) {
            SDIO_REG8_AND(SdioBaseAddr, PWRCTL, ~PWRCTL_POWER_ENABLE);
            SDIO_WRITE_REG8(SdioBaseAddr, PWRCTL, PWRCTL_18V);
            SDIO_REG8_OR(SdioBaseAddr, PWRCTL, PWRCTL_POWER_ENABLE);
            MicroSecondDelay (1000);
            SDIO_REG8_AND(SdioBaseAddr, CLKCTL, ~CLKCTL_CLOCK_ENABLE);
            SDIO_REG8_OR(SdioBaseAddr, HOSTCTL2, SIGNALING_ENABLE_1_8V);
            MicroSecondDelay (5000);
            SdioDevInfo->VoltageSwitch = TRUE;
        }
        SDIO_REG16_AND_OR(SdioBaseAddr, HOSTCTL2, ~UHS_MODE_SELECT,DDR50_UHS_SELECT);
        MicroSecondDelay (1000);
#if SDMMC_VERBOSE_PRINT
        DEBUG((EFI_D_VERBOSE ,"Set DDR50 mode...\n"));
#endif
        
        Status = ControllerSetClock (SdioDevInfo, Port, 52000000);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else if ((HighSpeedSupport) && (SdioDevInfo->bMmcCardType & MMC_HS_SDR_52)) {
        Status = ControllerSetClock (SdioDevInfo, Port, 52000000);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else if ((HighSpeedSupport) && (SdioDevInfo->bMmcCardType & MMC_HS_SDR_26)) {
        Status = ControllerSetClock (SdioDevInfo, Port, 26000000);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else {
        //
        // In Normal mode we try to set the clock to 25Mhz or less 
        //
        if ((MaxHstClk <= MaxCardClk ) && (MaxHstClk < 25000000)) {
            Status = ControllerSetClock (SdioDevInfo, Port, MaxHstClk);
            if (EFI_ERROR(Status)) {
                return Status;
            }
        } else if ((MaxCardClk < MaxHstClk ) && (MaxCardClk < 25000000)) {
            Status = ControllerSetClock (SdioDevInfo, Port, MaxCardClk);
            if (EFI_ERROR(Status)) {
                return Status;
            }
        } else {
            Status = ControllerSetClock (SdioDevInfo, Port, 25000000);
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
    }
    return EFI_SUCCESS;
}

/**
    Get Extended CSD from MMC device if version is 4.0 and higher

        
    @param  SdioDevInfo - Pointer to the SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note : This function follows This function follows step 23of Sec  A.6.1 
          Bus initialization from Jedec Electrical standard 5.01  
          specification

**/
EFI_STATUS
MmcCardGetExtCSD (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    EFI_STATUS  Status;
    UINT8       TransferAddress[512];
    UINT32      *Temp;

    Status = SdMmcReadWriteData (
                        SdioDevInfo,
                        Port, 
                        SEND_EXT_CSD_CMD8,
                        0,
                        (UINT32*)&TransferAddress[0],
                        0,
                        512, 
                        RESP1_TYPE,
                        FALSE, 
                        TRUE,
                        (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    //
    // Get the card type and Sector count from EXT_CSD register
    //
    SdioDevInfo->bMmcCardType = TransferAddress[196] & 0xff;  // CARD_TYPE [196]
    Temp = (UINT32*)&TransferAddress[212];
    SdioDevInfo->bMmcSecCount = *Temp;        // SEC_COUNT [215:212]
    InternalMemCopyMem (&SdioDevInfo->Ext_Csd, &TransferAddress[0], sizeof(EXT_CSD));
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"SdMmc: EXT_CSD Device type = 0x%x \n", SdioDevInfo->bMmcCardType));
    DEBUG((EFI_D_VERBOSE ,"SdMmc: EXT_CSD Max Sector Count = 0x%x \n", SdioDevInfo->bMmcSecCount));
#endif
    if (SdioDevInfo->bCsdStruct == 3) {
        SdioDevInfo->bCsdStruct = TransferAddress[194]; // CSD_STRUCTURE [194]
    }

    return Status;

}

/**
    Set the RCA value from the MMC card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure 
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Noate: This function follows step 17 of Sec A.6.1 Bus initialization
           from Jedec Electrical standard 5.01  specification.
           1. Issue CMD3 with new RCA.
           2. Receive R1, and put card to stand by stae.
**/
EFI_STATUS
MmcCardSetRCA (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{

    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;

    if ((SdioDevInfo->bState != CARDSTATUS_IDENT) &&
        (SdioDevInfo->bState != CARDSTATUS_STBY)) {
        return EFI_DEVICE_ERROR;
    }

    //
    // Issue CMD3 for all MMC devices
    //
    CommandIndex = ((SEND_RELATIVE_ADDR_CMD3 << 8) | RESP1_TYPE);
    CommandArgument = (Port + 2) << 16;
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port,
                     CommandIndex,
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    SdioDevInfo->wRCA = (UINT16)(Port+2);
    SdioDevInfo->bState = CARDSTATUS_STBY;

    return EFI_SUCCESS;
}

/**
    This function checks whether  1- bit mode is supported
     by the MMC card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS

**/
EFI_STATUS
TestMmc1BitSupport (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
) 
{

    EFI_STATUS  Status;
    UINT8       TransferBuffer[8] = {0};
    UINT8       Temp;

    //
    // Send command 19 to test the 1 bit bus with
    //
    TransferBuffer[0] = 0x40;
    Status = SdMmcReadWriteData (
                           SdioDevInfo,
                           Port,
                           BUSTEST_WRITE_CMD19,
                           0,
                           (UINT32*)&TransferBuffer[0],
                           1,
                           8,
                           RESP1_TYPE,
                           FALSE,
                           FALSE,
                           (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    
    //
    // Verify with command 14 whether the bit has been toggled
    //
    Temp = SdioDevInfo->MmcBusWidth;
    SdioDevInfo->MmcBusWidth = BUSTEST_READ_CMD14;
    Status = SdMmcReadWriteData (
                             SdioDevInfo,
                             Port,
                             BUSTEST_READ_CMD14,
                             0,
                             (UINT32*)&TransferBuffer[0],
                             1,
                             8,
                             RESP1_TYPE,
                             FALSE,
                             TRUE,
                             (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    SdioDevInfo->MmcBusWidth = Temp;    
    if ((EFI_ERROR(Status))&& (TransferBuffer[0]& 0xc0)!=0x80 ) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

/**
    This function checks whether 4-bit bus mode is supported by the
    MMC card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS

**/
EFI_STATUS
TestMmc4BitSupport (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    EFI_STATUS  Status;
    UINT8       TransferBuffer[8] = {0};
    UINT8       Temp;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    
    
    
    //
    // Send command 19 to test the 4 bit bus with
    //
    TransferBuffer[0] = 0x5a;
    Status = SdMmcReadWriteData (
                          SdioDevInfo,
                          Port,
                          BUSTEST_WRITE_CMD19,
                          0,
                          (UINT32*)&TransferBuffer[0],
                          1,
                          8,
                          RESP1_TYPE,
                          FALSE,
                          FALSE,
                          (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    if (EFI_ERROR(Status)) {
        SDIO_REG8_AND (SdioBaseAddr, HOSTCTL, ~(DATA_TRANSFER_4BITMODE));
        SdioDevInfo->MmcBusWidth = MMC_1_BIT_BUS_WIDTH;
        return TestMmc1BitSupport (SdioDevInfo, Port);
    }

    //
    // Verify with command 14 if the bit has been toggled
    //
    Temp = SdioDevInfo->MmcBusWidth;
    SdioDevInfo->MmcBusWidth = BUSTEST_READ_CMD14;
    Status = SdMmcReadWriteData (
                           SdioDevInfo,
                           Port,
                           BUSTEST_READ_CMD14,
                           0,
                           (UINT32*)&TransferBuffer[0],
                           1,
                           8,
                           RESP1_TYPE,
                           FALSE,
                           TRUE,
                           (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
    SdioDevInfo->MmcBusWidth = Temp;
    if ((EFI_ERROR(Status))|| TransferBuffer[0]!=0xa5 ) {
        SDIO_REG8_AND (SdioBaseAddr, HOSTCTL, ~(DATA_TRANSFER_4BITMODE));
        SdioDevInfo->MmcBusWidth = MMC_1_BIT_BUS_WIDTH;
        return TestMmc1BitSupport (SdioDevInfo, Port);
    }
    return EFI_SUCCESS;
}

/**
    This function checks whether 8-bit or 4-bit or 1- bit mode 
    is supported by the MMC card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS

**/
EFI_STATUS
MmcBusWidthTest (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    EFI_STATUS  Status;
    UINT8       TransferBuffer[8] = {0};
    UINT8       Temp;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    
    if (SdioDevInfo->MmcBusWidth == MMC_8_BIT_BUS_WIDTH ) {
        
        TransferBuffer[0] = 0x55;
        TransferBuffer[1] = 0xaa;
        
        //
        // Send command 19 to test the 8 bit bus with
        //
        Status =SdMmcReadWriteData (
                               SdioDevInfo,
                               Port,
                               BUSTEST_WRITE_CMD19,
                               0,
                               (UINT32*)&TransferBuffer[0],
                               1,
                               8,
                               RESP1_TYPE,
                               FALSE,
                               FALSE,
                               (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
        if (EFI_ERROR(Status)) {
            SDIO_REG8_AND_OR(SdioBaseAddr, HOSTCTL, ~(DATA_TRANSFER_8BITMODE), DATA_TRANSFER_4BITMODE);
            SdioDevInfo->MmcBusWidth = MMC_4_BIT_BUS_WIDTH;
            return TestMmc4BitSupport (SdioDevInfo, Port);
        }

        //
        // Verify with command 14 if the bit has been toggled
        //
        Temp = SdioDevInfo->MmcBusWidth;
        SdioDevInfo->MmcBusWidth = BUSTEST_READ_CMD14;
        Status  = SdMmcReadWriteData (
                                SdioDevInfo,
                                Port,
                                BUSTEST_READ_CMD14,
                                0,
                                (UINT32*)&TransferBuffer[0],
                                1,
                                8,
                                RESP1_TYPE,
                                FALSE,
                                TRUE,
                                (SD_MMC_COMMAND_TIMEOUT + READ_WRITE_TIMEOUT) );
        SdioDevInfo->MmcBusWidth = Temp;
        if ((EFI_ERROR(Status))|| TransferBuffer[0] != 0xaa || TransferBuffer[1] != 0x55) {
            SDIO_REG8_AND_OR(SdioBaseAddr, HOSTCTL, ~(DATA_TRANSFER_8BITMODE), DATA_TRANSFER_4BITMODE);
            SdioDevInfo->MmcBusWidth = MMC_4_BIT_BUS_WIDTH;
            return TestMmc4BitSupport(SdioDevInfo, Port);
        }
        return EFI_SUCCESS;
        
    }else if (SdioDevInfo->MmcBusWidth == MMC_4_BIT_BUS_WIDTH) {
        return TestMmc4BitSupport (SdioDevInfo, Port);
    }else {
        return TestMmc1BitSupport (SdioDevInfo, Port);
    }
    
}

/**
    Set the Bus width for the card

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number
    @param  BusTest     - Variable indicating to do bus width test or not

    @retval EFI_STATUS
    Note: This function follows the Section A.6.2 Switching to high-speed 
        mode of Jedec Electrical standard 5.01  
**/
EFI_STATUS
MmcCardBuswidth (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN BOOLEAN              BusTest
)
{
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;
    UINT32      CapValue = 0;
    BOOLEAN     DdrMode = FALSE;
    
    //
    // Currently only 4-bit bus width is set for the MMC/eMMC device.
    //
    if (SdioDevInfo->bSpecVers < 4) {
        //
        // Old MMC Card's does not support Bus Width command.
        //
        SdioDevInfo->MmcBusWidth = MMC_1_BIT_BUS_WIDTH;
        return EFI_SUCCESS;
    }
    
    if (((SDIO_REG16(SdioBaseAddr,HOSTCTL2) & UHS_MODE_SELECT)  == DDR50_UHS_SELECT) ||
            ( (SDIO_REG16(SdioBaseAddr,HOSTCTL2) & UHS_MODE_SELECT)  == DDR200_UHS_SELECT)) {
        DdrMode = TRUE;
    }

    //
    // Clear the Bus with Bits
    //
    SDIO_REG8_AND(SdioBaseAddr, HOSTCTL, ~(DATA_TRANSFER_8BITMODE+DATA_TRANSFER_4BITMODE));
    
    CapValue = SDIO_REG32(SdioBaseAddr,CAP);
    if ((SdioDevInfo->bHostControllerVersion >= HOST_CONTROLLER_VER3) && ((CapValue & BIT18) && ((CapValue>>30)==1))) {
        //
        // Select the 8 bit mode in host controller
        //
        SDIO_REG8_OR(SdioBaseAddr, HOSTCTL, DATA_TRANSFER_8BITMODE);
        if (DdrMode) {
            SdioDevInfo->MmcBusWidth = MMC_8_BIT_DDR_BUS_WIDTH;
        } else {
            SdioDevInfo->MmcBusWidth = MMC_8_BIT_BUS_WIDTH;
        }
    } else {
        //
        // Select the 4 bit mode in host controller
        //
        SDIO_REG8_OR(SdioBaseAddr, HOSTCTL, DATA_TRANSFER_4BITMODE);
        if (DdrMode) {
            SdioDevInfo->MmcBusWidth = MMC_4_BIT_DDR_BUS_WIDTH;        
        } else {
            SdioDevInfo->MmcBusWidth = MMC_4_BIT_BUS_WIDTH;
        }
    }
    
#if BUS_TEST_SUPPORT == 1
    //
    // This function send cmd 19 and cmd14 to test bus with
    // as per step 26 to 29 of A.6.2 Switching to high-speed 
    //
    if (BusTest) {
        Status = MmcBusWidthTest(SdioDevInfo,Port);
        if (EFI_ERROR(Status)) {
            SdioDevInfo->MmcBusWidth = MMC_1_BIT_BUS_WIDTH;
            return EFI_SUCCESS;
        }
    }
#endif
    
    // Set Bus-Width
    CommandIndex = ((SWITCH_FUNC_CMD6<< 8) | RESP1B_TYPE);
    CommandArgument = 0 | (SdioDevInfo->MmcBusWidth << 8) | (183 << 16) | (3 << 24); // bus width
    Status = SdMmcCommand (
                  SdioDevInfo,
                  Port,
                  CommandIndex,
                  CommandArgument,
                  SD_MMC_COMMAND_TIMEOUT );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Check if SWITCH_ERROR occured
    //
    Status = SdMmcCardGetStatus(SdioDevInfo, Port);
    if (EFI_ERROR(Status) && (SdioDevInfo->CurrentState != SWITCH_ERROR)) {
        return EFI_DEVICE_ERROR;
    }
    return EFI_SUCCESS;
}

/**
    Set the Sd device Bus width

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note: This function follows Section 6.6.4 "HS200" timing mode selection
    from Jedec Electrical standard 5.01  specification. Please note we are 
    not programming driver strength. It is kept to default
    

**/
EFI_STATUS
MmcCardHS200 (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;
    UINT32      MaxHstClk = 0;
    UINT32      CapValue = 0;

#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"Trying to Set HS200 mode ...\n"));
#endif
    
    
    //
    // AMI SDIO driver follows SD Host Controller Simplified Specification
    // Version 3.00. So 1.8V IO volatage only supported for HS200 emmc.
    //
    CapValue = SDIO_REG32(SdioBaseAddr, CAP);
    
    if (!((CapValue & BIT26) && (CapValue & BIT21))) {
        return EFI_UNSUPPORTED;
    }
    
    MaxHstClk = CapValue;
    if (SdioDevInfo->bHostControllerVersion == HOST_CONTROLLER_VER3) {
        MaxHstClk &= BASE_CLOCK_VER3;
    } else {
        MaxHstClk &= BASE_CLOCK;
    }

    MaxHstClk = (MaxHstClk >> 8);
    if (MaxHstClk <= 52) {
        return EFI_UNSUPPORTED;
    }
    
    //
    // Check CARD_TYPE to confirm if it supports HS200 at 1.8V and Bus width
    // is not set to one as per step 2 of 6.6.4 "HS200" timing mode selection
    //
    if (!(SdioDevInfo->bMmcCardType & MMC_HS200_SDR_18V)) {   
        return EFI_UNSUPPORTED;
    }
    
    //
    // Check if 1.8V switching in controller was successful
    //
    if (SdioDevInfo->VoltageSwitch == FALSE) {
        return EFI_UNSUPPORTED;
    }
    
    Status = MmcCardBuswidth (
                    SdioDevInfo, 
                    Port,
                    TRUE);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    if (SdioDevInfo->MmcBusWidth == MMC_1_BIT_BUS_WIDTH ) { 
        return EFI_UNSUPPORTED;
    }
    
    //
    // Set HS200 in HS_TIMING to the eMMC device. As per step 4 of 
    // 6.6.4 "HS200" timing mode selection
    //
    CommandIndex = ((SWITCH_FUNC_CMD6<< 8) | RESP1B_TYPE);
    CommandArgument = 0 | (2 << 8) | (185 << 16) | (3 << 24);
    Status = SdMmcCommand (
                  SdioDevInfo,
                  Port,
                  CommandIndex,
                  CommandArgument,
                  SD_MMC_COMMAND_TIMEOUT );
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // As per 4 of 6.6.4 "HS200" timing mode selection send command 13
    //
    Status = SdMmcCardGetStatus (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }
    
    //
    // As per step 4 of 6.6.4 "HS200" timing mode selection the state of the
    // card should be tran state
    //
    if (SdioDevInfo->bState != CARDSTATUS_TRAN) {
        return EFI_DEVICE_ERROR;
    }
    
    //
    // For the tuning for HS200 the SDR104 should 
    // be enabled or the tuning will fail at 200mhz
    //
    SDIO_REG8_OR(SdioBaseAddr, HOSTCTL2, SDR104_UHS_SELECT);
    
    //
    // As per ste 5 nd 6 of "6.6.4 "HS200" timing mode selection" set the
    // clock frequency to 200 Mhz and do tuning.
    //
    Status = HS200ClockTunning (SdioDevInfo, Port, MaxHstClk);
    if (EFI_ERROR(Status)) { 
        return Status;
    }
    
    // Chipset Specific Tuning for HS200
    // Code added to do tuning for HS200 or HS400 non-enhanced strobe mode.
    Status = SdMmcTunning (SdioDevInfo, Port, Hs200Tuning);
    if (EFI_ERROR(Status)) {
#if SDMMC_VERBOSE_PRINT
        DEBUG((EFI_D_VERBOSE ,"HS200 Tuning Failed...\n"));
#endif
        return Status;
    }
    
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"Set HS200 mode is successful...\n"));
#endif
    
    return EFI_SUCCESS;

}

/**
    Program HS400 mode. If strobe support is not present set card to HS200 first
    and set HS400 if it is successfull.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note: we are not programming driver strength. It is kept to default
    

**/
EFI_STATUS
MmcCardHS400 (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    EFI_STATUS  Status;
    UINT32      CapValue;
    BOOLEAN     EnhancedStrobe = FALSE;

#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"Trying to set HS400 mode ...\n"));
#endif

    // If enhanced strobe support is available, then HS400 mode selection has separate sequence.
    // Refer "Figure 30 - HS400 (Enhanced Strobe) Selection flow diagram" in eMMC JESD84-B51 spec.
    // Enhanced strobe is optional feature for the eMMC card.
#if CHECK_ENHANCED_STROBE_SUPPORT
    if (SdioDevInfo->Ext_Csd.Ext_Csd_Rev >= 8) {
        if (SdioDevInfo->Ext_Csd.Strobe_Support == 1) {
#if SDMMC_VERBOSE_PRINT
            DEBUG((EFI_D_VERBOSE ,"Strobe Support is present\n"));
#endif
            EnhancedStrobe = TRUE;
        }
    }
#endif
    
    CapValue = SDIO_REG32(SdioBaseAddr, CAP);
    
    if (!((CapValue & VOLTAGE_SUPPORT_18) && (CapValue & HIGH_SPEED_SUPPORT))) {
        DEBUG((EFI_D_ERROR, "High Speed and 18V Not Supported\n"));
        return EFI_UNSUPPORTED;
    }

    // Check CARD_TYPE to confirm if it supports HS400 at 1.8V and Bus width
    // is not set to one as per step 2 of 6.6.4 "HS400" timing mode selection
    if (!(SdioDevInfo->bMmcCardType & MMC_HS400_DDR_18V) || (SdioDevInfo->VoltageSwitch == FALSE)) {    
        DEBUG((EFI_D_ERROR, "HS400 Not Supported\n"));
        return EFI_UNSUPPORTED;
    }
       
    if (EnhancedStrobe == FALSE) {
        
#if SDMMC_VERBOSE_PRINT
            DEBUG((EFI_D_VERBOSE ,"Setting HS200 mode first\n"));
#endif
        // These steps are for non-enhanced strobe method. HS200 mode must be selected first.
        Status = MmcCardHS200 (SdioDevInfo, Port);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    // These next steps follow Embedded Multi-Media Card (eMMC)
    // Electrical Standard (5.1), section 6.6.2.3.
    // The optional "driver strength" steps are not done.
    // HS200 mode must already be on

    // Switch to High Speed mode
    CommandIndex = ((SWITCH_FUNC_CMD6 << 8) | RESP1B_TYPE);
    CommandArgument = 0 | (1 << 8) | (185 << 16) | (3 << 24);
    Status = SdMmcCommand (
                   SdioDevInfo,
                   Port, 
                   CommandIndex, 
                   CommandArgument, 
                   SD_MMC_COMMAND_TIMEOUT );
    if (EFI_ERROR(Status)) {           
        return Status;
    }

    // Set clock speed to max of 52 MHz
    if (SdioDevInfo->bMmcCardType & MMC_HS_SDR_52 ) {
        Status = ControllerSetClock (SdioDevInfo, Port, 52000000);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    } else if (SdioDevInfo->bMmcCardType & MMC_HS_SDR_26) {
        Status = ControllerSetClock (SdioDevInfo, Port, 26000000);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }

    // Enhanced strobe method
    // Write 0x86 to BUS_WIDTH(183) to set x8 bus mode and enable Enhanced Strobe
    if (!EnhancedStrobe) {
        CommandArgument = 0 | (MMC_8_BIT_DDR_BUS_WIDTH << 8) | (183 << 16) | (3 << 24);
    } else {
        CommandArgument = 0 | ( (0x80 | MMC_8_BIT_DDR_BUS_WIDTH) << 8) | (183 << 16) | (3 << 24);
        // Set HOSTCTL here as Bus Width is not set through MmcCardBuswidth().
        SDIO_REG8_OR(SdioBaseAddr, HOSTCTL, DATA_TRANSFER_8BITMODE);
    }
    CommandIndex = ((SWITCH_FUNC_CMD6<< 8) | RESP1B_TYPE);
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port, 
                     CommandIndex,
                     CommandArgument,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    SdioDevInfo->MmcBusWidth = MMC_8_BIT_DDR_BUS_WIDTH;

    // Switch to HS400 mode (write 3 to HS_TIMING(185))
    CommandIndex = ((SWITCH_FUNC_CMD6<< 8) | RESP1B_TYPE);
    CommandArgument = 0 | (3 << 8) | (185 << 16) | (3 << 24);
    Status = SdMmcCommand (
                     SdioDevInfo, 
                     Port, 
                     CommandIndex,
                     CommandArgument, 
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    SDIO_REG8_AND(SdioBaseAddr, HOSTCTL2, ~UHS_MODE_SELECT);
    SDIO_REG8_OR(SdioBaseAddr, HOSTCTL2, DDR200_UHS_SELECT);

    // Set speed to 200 MHz
    Status = ControllerSetClock (SdioDevInfo, Port, 200000000);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"HS400 mode is set successfully \n"));
#endif

    return EFI_SUCCESS;
}


/**
    This function issues tuning command to MMC card

    @param  SdioDevInfo  - Pointer to SDIO_DEVICE_INFO structure
    @param  Port          - Sdio port number
    @param  BufferAddress - Buffer address
    @param  Size          - Transfer block size
    
    @retval EFI_STATUS

**/
EFI_STATUS
MmcSendTuningCommand (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  VOID                *BufferAddress,
    IN  UINT16              Size
)   
{
    EFI_STATUS              Status;
    UINT16                  CommandIndex;
    UINT64                  SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    
    //
    // Configure the transfer mode register, Bloack size register and block
    // count register for the transfer
    //
    SDIO_WRITE_REG16(SdioBaseAddr, BLKSZ, Size);
    SDIO_WRITE_REG16(SdioBaseAddr, BLKCNT, 1);

    SDIO_WRITE_REG16(SdioBaseAddr, XFRMODE, DATA_TRANSFER_CARD2HOST);
    //
    // Send the Command argument and command
    //
    CommandIndex = (SEND_TUNING_MMC_CMD21<< 8) | (RESP1_TYPE+DATA_PRESENT_SELECT);
    Status = SdMmcCommand (
                     SdioDevInfo,
                     Port,
                     CommandIndex,
                     0,
                     SD_MMC_COMMAND_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return EFI_DEVICE_ERROR;
    }   
    //
    // Wait for the transfer to complete
    //
    Status = SdMmcWaitXferComplete (
                             SdioDevInfo,
                             Port,
                             (VOID**)&BufferAddress, 
                             Size,
                             1,
                             READ_WRITE_TIMEOUT);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    return Status;
}
/**
    Clock tunning for HS200

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note: This function follows setion 6.6.8.1 Sampling Tuning Sequence for HS200
**/
EFI_STATUS
HS200ClockTunning (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port,
    IN  UINT32              MaxHstClk
)
{
    UINT16      TuningBlockSize = 0;
    UINT8       Buffer[128];
    EFI_STATUS  Status;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT16      Temp16;
    UINT8       Index;
    
    //
    // Set the new clock to 200Mhz   
    //
    // If bus width set to 4bit the data pattern is in Tuning_block_4bit
    // else If bus width set to 8bit the data pattern is in Tuning_block_8bit
    //
    if (SdioDevInfo->MmcBusWidth == MMC_4_BIT_BUS_WIDTH) {
        TuningBlockSize = 64;
    } else if (SdioDevInfo->MmcBusWidth == MMC_8_BIT_BUS_WIDTH){
        TuningBlockSize = 128;
    }     
    //
    //disable clock first.Set the new clock to 200Mhz
    //
    ControllerSetClock (SdioDevInfo, Port, 200000000);
    SDIO_REG16_AND(SdioBaseAddr, HOSTCTL2, ~SAMPLING_CLOCK_SELECT);
    MicroSecondDelay (1000);
    SDIO_REG16_OR(SdioBaseAddr, HOSTCTL2, EXECUTE_TUNING);
    
    for (Index = 0; Index < 80; Index++){
        
        // Send tuning Command 
        Status  = MmcSendTuningCommand (
                                     SdioDevInfo,
                                     Port,
                                     (UINT32*)&Buffer[0],
                                     TuningBlockSize);
                                     
        if (EFI_ERROR(Status)) {
            //
            // HS200 failed clear the error status for  data and cmd.
            //
            SDIO_REG16_OR(SdioBaseAddr, ERINTSTS, 0x0FFF);
            SDIO_WRITE_REG16(SdioBaseAddr, NINTSTS, 0xFFFF);
            continue;
        }        
        Temp16 = SDIO_REG16(SdioBaseAddr, HOSTCTL2);
        if (!(Temp16&EXECUTE_TUNING)) {
            break;
        }
        MicroSecondDelay (3000);
    }
    
    Temp16 = SDIO_REG16(SdioBaseAddr,HOSTCTL2);    
    if (Temp16&SAMPLING_CLOCK_SELECT) {
#if SDMMC_VERBOSE_PRINT
        DEBUG((EFI_D_VERBOSE ,"SdMmc: tuning successful Index = %x\n", Index));
#endif
        return EFI_SUCCESS;
    } else {
#if SDMMC_VERBOSE_PRINT
        DEBUG((EFI_D_VERBOSE ,"SdMmc: tuning Failed reverting to previous mode \n"));
#endif        
        //
        // If tunning failed then revert back to High speed
        //        
        SDIO_REG8_AND(SdioBaseAddr, HOSTCTL2, ~SDR104_UHS_SELECT);
        return EFI_DEVICE_ERROR;
    }
}

/**
    Switching to High speed

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS
    Note: This function follows step 21-24 of Sec A.6.1 Bus initialization
           from Jedec Electrical standard 5.01  specification
**/
EFI_STATUS
MmcSetHighSpeed (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
) {
    UINT32      CapValue;
    EFI_STATUS  Status;
    UINT16      CommandIndex;
    UINT32      CommandArgument;
    
    //
    // Get extended CSD register if MMC 4.0 or higher as per step 22 and 23
    // of A.6.1 Bus initialization
    //
    if (SdioDevInfo->bSpecVers >= 4) {

        //
        // Set to High speed interface by enabling HS_TIMING in extended CSD reg.
        // if host controller supports High Speed. As per step 23 of A.6.1 Bus 
        // initialization
        //
        CapValue = SDIO_REG32(SdioDevInfo->SdioBaseAddress, CAP);
        if (CapValue & HIGH_SPEED_SUPPORT) {                                 
            CommandIndex = ((SWITCH_FUNC_CMD6<< 8) | RESP1B_TYPE);
            CommandArgument = 0 | (1 << 8) | (185 << 16) | (3 << 24);
            Status = SdMmcCommand (
                             SdioDevInfo,
                             Port,
                             CommandIndex,
                             CommandArgument,
                             SD_MMC_COMMAND_TIMEOUT);
            if (EFI_ERROR(Status)) {
                return Status;
            }
        }
    }
    
    //
    // Set the clock as per step 24 of A.6.1 Bus initialization
    //
    Status = MmcCard_SetClock (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    
    //
    // As per 6.6.2 High-speed modes selection send command 13
    //
    Status =  SdMmcCardGetStatus (SdioDevInfo, Port);
    if (EFI_ERROR(Status) && (Status != EFI_CRC_ERROR)) {
        return EFI_DEVICE_ERROR;
    }
    
    return EFI_SUCCESS;

}
/**
    Initialize the eMMC card.

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number 

    @retval EFI_STATUS
    Note: This function is as per Jedec eMMC Electrical Standard 5.01
          (Sec A.6.1 Bus initialization step 4 to 36). The step 1 to
          3 is already taken care in ControllerInitEnvironment function
**/
EFI_STATUS
MmcCardInit (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{

    EFI_STATUS  Status;
    UINT32      CommandArgument;
    UINT32      Response;
    UINT64      SdioBaseAddr = SdioDevInfo->SdioBaseAddress;
    UINT32      CapValue;
    UINT32      PresentState;
    UINT32      Temp32;
    SdioDevInfo->VoltageSwitch = FALSE;

#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE,"SdMmc: Mmc Card Found.. Initializing Mmc Card\n"));
#endif
    //
    // This function is to get OCR.
    // As per step 4-8 from sec Sec A.6.1 Bus initialization
    //
    CommandArgument = (CARD_POWERUP_STATUS_BIT| CARD_CAPACITY_STATUS | CARD_LOW_VOLTAGE_OUTPUT_WINDOW);
    Status = MmcGetOcr (SdioDevInfo, Port, CommandArgument, &Response);
    if (EFI_ERROR(Status)) {
        return EFI_NOT_FOUND;
    }
    SdioDevInfo->dOCR = Response;
    
    CapValue=SDIO_REG32(SdioBaseAddr, CAP);
    
    // If Host supports only 1.8V, check if Card is able to support 1.8V
    if (!SdioDevInfo->SdVoltageWindow) {
        if (!(SdioDevInfo->dOCR & CARD_LOW_VOLTAGE_WINDOW)) {
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE,"Host controller only supports 1.8V but Mmc Card does not support 1.8V\n"));
#endif
            return EFI_DEVICE_ERROR;
        }
    }
    
    //
    // Set 1.8V Programming in card as per  step 10-14 of Sec A.6.1 Bus 
    // initialization of Jedec Electrical standard 5.01
    //
    if ((CapValue & VOLTAGE_SUPPORT_18)&&((SdioDevInfo->dOCR)&CARD_LOW_VOLTAGE_WINDOW)) {

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
        SDIO_REG8_AND(SdioBaseAddr, CLKCTL,~CLKCTL_CLOCK_ENABLE);
        
        //
        // As mentioned in step 6 of sec Signal Voltage Switch Procedure
        // of Sd host controller 3.00
        //
        SDIO_REG8_OR(SdioBaseAddr, HOSTCTL2,SIGNALING_ENABLE_1_8V);
        
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
            ControllerSetClock (SdioDevInfo, Port, 400000);
            
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
            if (PresentState == 0xf) {
                
                //
                // Send CMD1 with argument 0x00000080 and receive R3 
                // as per step12 of A.6.1 Bus initialization
                //
                CommandArgument = (CARD_POWERUP_STATUS_BIT| CARD_CAPACITY_STATUS | CARD_LOW_VOLTAGE_WINDOW);
                Status = MmcGetOcr (SdioDevInfo, Port, CommandArgument, &Response);
                if ((!EFI_ERROR(Status)) && ((Response&(~CARD_CAPACITY_STATUS)) == (CARD_POWERUP_STATUS_BIT| CARD_LOW_VOLTAGE_OUTPUT_WINDOW))) {
                    SdioDevInfo->dOCR = Response;
                    SdioDevInfo->VoltageSwitch = TRUE;
                }
            } 
        }
        
        //
        // If switching to 1.8V failed then revert back to the Host supported 
        // higher voltage
        //
        if (SdioDevInfo->VoltageSwitch== FALSE) {
            
#if SDMMC_VERBOSE_PRINT
            DEBUG((EFI_D_VERBOSE,"1.8V Switching Failed, SdVoltageWindow - %d\n", SdioDevInfo->SdVoltageWindow));
#endif
            
            // If Host supports only 1.8V and Device does not support voltage switch return error.
            if (!SdioDevInfo->SdVoltageWindow) {
                return EFI_DEVICE_ERROR;
            }
            
            
            //
            // As per Step8 of A.6.1 Bus initialization "if Device is not 
            // compliant (since it should have put itself into inactive
            // state, due to voltage incompatibility, and not respond); in
            // such a case the host must power down the bus and start its 
            // error recovery procedure. As the Host's Error Recovery method
            // uses Abort command (which is executed in tran state) and 
            // Powering down necessitate Voltage and clock reprogramming. So 
            // better to call ControllerInitEnvironment.
            //
            SDIO_REG8_AND(SdioBaseAddr, PWRCTL, ~PWRCTL_POWER_ENABLE);
            Status = ControllerInitEnvironment (SdioDevInfo, Port);
            if (EFI_ERROR(Status)) {
                return Status;
            }
            
            CommandArgument = (CARD_POWERUP_STATUS_BIT| CARD_CAPACITY_STATUS | CARD_VOLTAGE_WINDOW);
            Status = MmcGetOcr (SdioDevInfo, Port, CommandArgument, &Response);
            SdioDevInfo->dOCR = Response;
            if (EFI_ERROR(Status)) {
               return Status;
            }
        }
    } 
    
    if ((SdioDevInfo->dOCR & MMC_CARD_CAPACITY_BIT )) { 
        SdioDevInfo->bMode = MMC_HIGH_CAP;
    } else {
        SdioDevInfo->bMode = MMC_STAND_CAP;
    }
    SdioDevInfo->bState = CARDSTATUS_READY;
    
    //
    // Get CID from card as per  step 15-16 of Sec A.6.1 Bus initialization
    // of Jedec Electrical standard 5.01
    //
    Status = SdMmcCardGetCID (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Set RCA for card as per  step 17 of Sec A.6.1 Bus initialization
    // of Jedec Electrical standard 5.01
    //
    Status = MmcCardSetRCA (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    //
    // Get CID from card as per  step 18-20 of Sec A.6.1 Bus initialization
    // of Jedec Electrical standard 5.01
    //
    Status = SdMmcCardGetCSD (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Send CMD7 with the Device's RCA to place the Device in tran state
    // as per step 21 of A.6.1 Bus initialization
    //
    Status = SdMmcCardSelect (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    if (SdioDevInfo->bSpecVers >= 4) {
        Status = MmcCardGetExtCSD (SdioDevInfo, Port);
        if (EFI_ERROR(Status)) {
            return Status;
        }
    }
    
    //
    //Get the device capacity
    //
    Status = MmcMassGetCapacity (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    //
    // Set HS400 if the controller and card support it. If error device will work in normal mode
    //
    Status = MmcCardHS400 (SdioDevInfo, Port);
    if (!EFI_ERROR(Status))  {
        // Chipset specific tuning after setting to HS400 mode
        Status = SdMmcTunning (SdioDevInfo, Port, Hs400Tuning);      
        if (!EFI_ERROR(Status)) {
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"HS400 tuning Passed \n"));
#endif
            return Status;
        }
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"HS400 tuning Failed \n"));
#endif
    }
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"Setting HS400 mode failed \n"));
#endif

    //
    // Set HS200 if the controller and card support it. If error device will work in normal mode
    //
    Status = MmcCardHS200 (SdioDevInfo, Port);
#if SDMMC_VERBOSE_PRINT
    DEBUG((EFI_D_VERBOSE ,"Setting HS200 mode Status : %r\n",Status));
#endif
    if (!EFI_ERROR(Status))  {
        return Status;
    }

    //
    // Set high Speed from card as per  A.6.2 Switching to high-speed modeof 
    // Jedec Electrical standard 5.01
    //
    Status = MmcSetHighSpeed (SdioDevInfo, Port);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    
    //
    // Set the bus width as per Section A.6.3 Changing the data bus width
    //
    Status = MmcCardBuswidth (SdioDevInfo, Port, FALSE);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    return Status;
}

/**
    Get the MMC device capacity

    @param  SdioDevInfo - Pointer to SDIO_DEVICE_INFO structure
    @param  Port        - Sdio port number

    @retval EFI_STATUS

**/
EFI_STATUS
MmcMassGetCapacity (
    IN  SDIO_DEVICE_INFO    *SdioDevInfo,
    IN  UINT8               Port
)
{
    UINT32      CSize;
    UINT8       BlockLength;
    UINT16      CommandIndex;
    UINT32      Mult;
    EFI_STATUS  Status;
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
    if (CSize == 0xfff) {
        SdioDevInfo->dMaxLBA = SdioDevInfo->bMmcSecCount;
    } else {
        //
        // Bit47-49 is Device size multipier
        // MULT = 2^(C_SIZE_MULT+2) (C_SIZE_MULT < 8)
        // 
        //
        Mult = (SdioDevInfo->d4CSD[1] & (DEVICE_SZIE_MUL_1)) >> 15;
        Mult = (1 << (Mult + 2));
        
        //
        // BLOCKNR(number of block) = (C_SIZE+1) * MULT
        //
        SdioDevInfo->dMaxLBA = (CSize + 1) * Mult;
        // If the BlockSize exceeds 512 bytes for MMC card, , then Set the Blocklength to 
        // default blocksize (512) using CMD16 (SET_BLOCK_LEN). 
        if (SdioDevInfo->wBlockSize > BLOCK_SIZE) {            
            CommandIndex = (SET_BLOCKLEN << 8) | (RESP1_TYPE);
            Status = SdMmcCommand (
                          SdioDevInfo, 
                          Port, 
                          CommandIndex, 
                          BLOCK_SIZE, 
                          SD_MMC_COMMAND_TIMEOUT );
            if (EFI_ERROR(Status)) {
                return EFI_DEVICE_ERROR;
            }
            // Modify the MaxLBA as per new BLOCK_SIZE (512)
            SdioDevInfo->dMaxLBA *= (SdioDevInfo->wBlockSize / BLOCK_SIZE);
            SdioDevInfo->wBlockSize = BLOCK_SIZE;
        }                
    }
    //
    // LBA address starts from 0 so the maximum accessible address should
    // be one less than the max.
    //
    SdioDevInfo->dMaxLBA -= 1;
    return EFI_SUCCESS;
}
