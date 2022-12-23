//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


#include "I2cHcOperationDxe.h"

EFI_STATUS
I2cDisable(
    IN UINTN MmioBase
    )
{
    UINT32 NumTries = 10000;  /* 0.1 seconds */

    MmioWrite32(MmioBase + R_IC_ENABLE, 0);
    while(0 != (MmioRead32(MmioBase + R_IC_ENABLE_STATUS) & 1)) {
        MicroSecondDelay(10);
        NumTries --;
        if(0 == NumTries)
            return EFI_NOT_READY;
    }

    return EFI_SUCCESS;
}



EFI_STATUS
I2cEnable(
    IN UINTN MmioBase
    )
{
    UINT32 NumTries = 10000;  /* 0.1 seconds */

    MmioWrite32(MmioBase + R_IC_ENABLE, 1);
    while(0 == (MmioRead32 (MmioBase + R_IC_ENABLE_STATUS) & 1)) {
        MicroSecondDelay(10);
        NumTries --;
        if(0 == NumTries) 
            return EFI_NOT_READY;
    }

    return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
I2cBusFrequencySet(
    IN  UINTN MmioBase,
    IN  UINTN BusClockHertz,
    IN OUT UINT16 *I2cMode
    )
{
    *I2cMode = B_IC_MASTER_MODE | B_IC_SLAVE_DISABLE | B_IC_RESTART_EN;

    DEBUG((EFI_D_INFO,"InputFreq BusClockHertz: %d\r\n",BusClockHertz));

    //
    //  Set the 100 KHz clock divider according to SV result and I2C spec
    //
    MmioWrite32(MmioBase + R_IC_SS_SCL_HCNT, (UINT16)PcdGet16(AmiPcdI2cSsSCLHcnt));
    MmioWrite32(MmioBase + R_IC_SS_SCL_LCNT, (UINT16)PcdGet16(AmiPcdI2cSsSCLLcnt));
    //
    //  Set the 400 KHz clock divider according to SV result and I2C spec
    //
    MmioWrite32(MmioBase + R_IC_FS_SCL_HCNT, (UINT16)PcdGet16(AmiPcdI2cFsSCLHcnt));
    MmioWrite32(MmioBase + R_IC_FS_SCL_LCNT, (UINT16)PcdGet16(AmiPcdI2cFsSCLLcnt));
    //
    //  Set the 3.4 MHz clock divider according to SV result and I2C spec
    //
    MmioWrite32(MmioBase + R_IC_HS_SCL_HCNT, (UINT16)PcdGet16(AmiPcdI2cHsSCLHcnt));
    MmioWrite32(MmioBase + R_IC_HS_SCL_LCNT, (UINT16)PcdGet16(AmiPcdI2cHsSCLLcnt));


    switch (BusClockHertz) {
        case 100 * 1000:
            MmioWrite32 (MmioBase + R_IC_SDA_HOLD, (UINT32)PcdGet32(AmiPcdI2cSsSDAHold));//100K
            *I2cMode |= V_IC_SPEED_STANDARD;
            break;
        case 400 * 1000:
            MmioWrite32 (MmioBase + R_IC_SDA_HOLD, (UINT32)PcdGet32(AmiPcdI2cFsSDAHold));//400K
            *I2cMode |= V_IC_SPEED_FAST;
            break;
        default:
            MmioWrite32 (MmioBase + R_IC_SDA_HOLD, (UINT32)PcdGet32(AmiPcdI2cHsSDAHold));//3.4M
            *I2cMode |= V_IC_SPEED_HIGH;
            break;
    }

    //
    //  Select the frequency counter
    //  Enable restart condition,
    //  Enable master FSM, disable slave FSM
    //
    //I2cMode |= B_MASTER_MODE;

    return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
I2CInit(
    IN UINTN  MmioBase,
    IN UINT16 SlaveAddress
    )
{
    EFI_STATUS Status   = EFI_SUCCESS;
    UINT16     I2cMode = 0;

    Status = I2cDisable(MmioBase);
    DEBUG((EFI_D_INFO, "I2cDisable Status = %r\r\n", Status));
	
	I2cBusFrequencySet(MmioBase, 400 * 1000, &I2cMode);//Set I2cMode
    //MmioWrite32( mI2CBaseAddress + R_IC_CLK_GATE, 0x01);//No use for A0
    MmioWrite32(MmioBase + R_IC_INTR_MASK, 0x0);
    //if ( 0x7f < SlaveAddress ) 
    //  SlaveAddress = ( SlaveAddress & 0x3ff ) | IC_TAR_10BITADDR_MASTER;
    MmioWrite32(MmioBase + R_IC_TAR, (UINT16)SlaveAddress);
    MmioWrite32(MmioBase + R_IC_RX_TL, 0);
    MmioWrite32(MmioBase + R_IC_TX_TL, 0);
    MmioWrite32(MmioBase + R_IC_CON, I2cMode);

    Status = I2cEnable(MmioBase);
    DEBUG((EFI_D_INFO, "I2cEnable Status = %r\r\n", Status));

    MmioRead32 (MmioBase + R_IC_CLR_TX_ABRT);
    MmioWrite32(MmioBase + R_IC_CLK_PARAMS, 1);
    return EFI_SUCCESS;
}



EFI_STATUS
ByteReadI2C_Basic(
    IN  UINTN MmioBase,
    IN  UINT8 SlaveAddress,
    IN  UINTN ReadBytes,
    OUT UINT8 *ReadBuffer,
    IN  UINT8 Start,
    IN  UINT8 End
    )
{

    EFI_STATUS Status = EFI_SUCCESS;
    UINT32     I2cStatus;
    UINT16     ReceiveData;
    UINT8      *ReceiveDataEnd;
    UINT8      *ReceiveRequest;
    UINT16     raw_intr_stat;
    UINT32     Count = 0;


    ReceiveDataEnd = &ReadBuffer[ReadBytes];
    if(ReadBytes) {

        ReceiveRequest = ReadBuffer;
        //DEBUG((EFI_D_INFO,"Read: ---------------%d bytes to RX\r\n",ReceiveDataEnd - ReceiveRequest));

        while((ReceiveDataEnd > ReceiveRequest) || (ReceiveDataEnd > ReadBuffer)) {
            //Check for NACK
            raw_intr_stat = (UINT16)MmioRead32(MmioBase + R_IC_RAW_INTR_STAT);
            if(0 != (raw_intr_stat & I2C_INTR_TX_ABRT)) {
                MmioRead32(MmioBase + R_IC_CLR_TX_ABRT);
                Status = EFI_DEVICE_ERROR;
                DEBUG((EFI_D_INFO,"TX ABRT ,%d bytes hasn't been transferred\r\n", ReceiveDataEnd - ReceiveRequest));
                break;
            }

            //  Determine if another byte was received
            I2cStatus = (UINT16)MmioRead32(MmioBase + R_IC_STATUS);
            if(0 != (I2cStatus & STAT_RFNE)) {
                ReceiveData = (UINT16)MmioRead32(MmioBase + R_IC_DATA_CMD);
                *ReadBuffer++ = (UINT8)ReceiveData;
                // DEBUG((EFI_D_INFO, "MmioRead32 ,1 byte 0x:%x is received\r\n", ReceiveData));
            }

            if(ReceiveDataEnd==ReceiveRequest) {
                MicroSecondDelay(FIFO_WRITE_DELAY);
                // DEBUG((EFI_D_INFO, "ReceiveDataEnd==ReceiveRequest------------%x\r\n", I2cStatus & STAT_RFNE));
                Count++;
                if(Count < 1024)   //to avoid sys hung  without ul-pmc device  on RVP
                    continue;      //Waiting the last request to get data and make (ReceiveDataEnd > ReadBuffer) =TRUE.
                else
                    break;
            }

            //  Wait until a read request will fit
            if(0 == (I2cStatus & STAT_TFNF)) {
                DEBUG((EFI_D_INFO,"Wait until a read request will fit\r\n"));
                MicroSecondDelay(10);
                continue;
            }
            //  Issue the next read request
            if(End && Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, B_READ_CMD | B_CMD_RESTART | B_CMD_STOP);
            else if(!End && Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, B_READ_CMD | B_CMD_RESTART);
            else if(End && !Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, B_READ_CMD | B_CMD_STOP);
            else if(!End && !Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, B_READ_CMD);
            MicroSecondDelay(FIFO_WRITE_DELAY);//wait after send cmd

            ReceiveRequest += 1;
        }
        //local_irq_restore(eflags);
    }
    return Status;

}



EFI_STATUS
ByteWriteI2C_Basic(
    IN UINTN MmioBase,
    IN UINT8 SlaveAddress,
    IN UINTN WriteBytes,
    IN UINT8 *WriteBuffer,
    IN UINT8 Start,
    IN UINT8 End
    )
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32     I2cStatus;
    UINT8      *TransmitEnd;
    UINT16     raw_intr_stat;
    UINT32     Count = 0;


    TransmitEnd = &WriteBuffer[WriteBytes];
    if(WriteBytes) {
        //DEBUG((EFI_D_INFO,"Write: --------------%d bytes to TX\r\n",TransmitEnd - WriteBuffer));
        while(TransmitEnd > WriteBuffer) {
            I2cStatus = MmioRead32(MmioBase + R_IC_STATUS);
            raw_intr_stat = (UINT16)MmioRead32(MmioBase + R_IC_RAW_INTR_STAT);

            if(0 != (raw_intr_stat & I2C_INTR_TX_ABRT)) {
                MmioRead32(MmioBase + R_IC_CLR_TX_ABRT);
                Status = EFI_DEVICE_ERROR;
                DEBUG((EFI_D_ERROR, "TX ABRT TransmitEnd:0x%x WriteBuffer:0x%x\r\n", TransmitEnd, WriteBuffer));
                break;
            }

            if(0 == (I2cStatus & STAT_TFNF)) {   //if tx not full , will  send cmd  or continue to wait
                MicroSecondDelay(FIFO_WRITE_DELAY);
                continue;
            }

            if(End && Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, (*WriteBuffer++) | B_CMD_RESTART| B_CMD_STOP);
            else if(!End && Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, (*WriteBuffer++) | B_CMD_RESTART);
            else if(End && !Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, (*WriteBuffer++) | B_CMD_STOP);
            else if(!End && !Start)
                MmioWrite32(MmioBase + R_IC_DATA_CMD, (*WriteBuffer++));
            // Add a small delay to work around some odd behavior being seen.  Without this delay bytes get dropped.
            MicroSecondDelay(FIFO_WRITE_DELAY);   //wait after send cmd

            //time out
            while(1) {
                raw_intr_stat = MmioRead16(MmioBase + R_IC_RAW_INTR_STAT);
                if(0 != ( raw_intr_stat & I2C_INTR_TX_ABRT)) {
                    MmioRead16(MmioBase + R_IC_CLR_TX_ABRT);
                    Status = EFI_DEVICE_ERROR;
                    DEBUG((EFI_D_ERROR, "TX ABRT TransmitEnd:0x%x WriteBuffer:0x%x\r\n", TransmitEnd, WriteBuffer));
                }
                if(0 == MmioRead16(MmioBase + R_IC_TXFLR))
                    break;

                MicroSecondDelay(FIFO_WRITE_DELAY);
                Count++;

                if(Count < 1024)   //to avoid sys hung without ul-pmc device on RVP
                    continue;      //Waiting the last request to get data and make (ReceiveDataEnd > ReadBuffer) =TRUE.
                else
                    break;
            }
        }
    }

    if(EFI_ERROR(Status)) {
        DEBUG((EFI_D_INFO,"ByteWriteI2C_Basic Exit with Status %r\r\n",Status));
    }

    return Status;
}



EFI_STATUS
EFIAPI
I2cWriteRead(
    UINTN  MmioBase,
    UINT8  SlaveAddress,
    UINTN  WLength,
    UINT8  *Write_Buffer,
    UINTN  RLength,
    UINT8  *Read_Buffer
    )
{
    EFI_STATUS Status = EFI_UNSUPPORTED;
    UINTN        Index;

    I2CInit(MmioBase, SlaveAddress);

    if((WLength == 0) &&(RLength != 0)) {
        Status = ByteReadI2C_Basic(MmioBase, SlaveAddress, 1, Read_Buffer, TRUE, FALSE);
        Read_Buffer++;
        Status = ByteReadI2C_Basic(MmioBase, SlaveAddress, RLength - 2, Read_Buffer, FALSE, FALSE);
        for(Index = 0; Index < (RLength-2); Index++)
            Read_Buffer++;
        Status = ByteReadI2C_Basic(MmioBase, SlaveAddress, 1, Read_Buffer, FALSE, TRUE);

    } else if((WLength != 0) &&(RLength == 0)) {
        Status = ByteWriteI2C_Basic(MmioBase, SlaveAddress, 1, Write_Buffer, TRUE, FALSE);
        Write_Buffer++;
        Status = ByteWriteI2C_Basic(MmioBase, SlaveAddress, WLength - 2, Write_Buffer, FALSE, FALSE);
        for(Index = 0; Index < (WLength - 2); Index++)
            Write_Buffer++;
        Status = ByteWriteI2C_Basic(MmioBase, SlaveAddress, 1, Write_Buffer, FALSE, TRUE);

    } else if((WLength != 0) &&(RLength != 0)) {
        Status = ByteWriteI2C_Basic(MmioBase, SlaveAddress, 1, Write_Buffer, TRUE, FALSE);
        Write_Buffer++;
        Status = ByteWriteI2C_Basic(MmioBase, SlaveAddress, WLength - 2, Write_Buffer, FALSE, FALSE);
        for(Index = 0; Index < (WLength - 2); Index++)
            Write_Buffer++;
        Status = ByteWriteI2C_Basic(MmioBase, SlaveAddress, 1, Write_Buffer, FALSE, FALSE);
        Status = ByteReadI2C_Basic(MmioBase, SlaveAddress, 1, Read_Buffer, TRUE, FALSE);
        Read_Buffer++;
        Status = ByteReadI2C_Basic(MmioBase, SlaveAddress, RLength - 2, Read_Buffer, FALSE, FALSE);
        for(Index = 0; Index < (RLength - 2); Index++)
            Read_Buffer++;
        Status = ByteReadI2C_Basic(MmioBase, SlaveAddress, 1, Read_Buffer, FALSE, TRUE);

    }

    return Status;
}


