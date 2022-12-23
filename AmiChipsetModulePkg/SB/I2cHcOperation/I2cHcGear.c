//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************


/** @file I2cHcGear.c
    This file contains code for I2c Hc Operation Protocol Library.
*/
#include "I2cHcOperationDxe.h"

/**

  Get where the current host controller

  @param[in]   This                  I2C Host Controller
  @param[out]  Info                  Get the host info

  @retval EFI_SUCCESS
  @retval EFI_INVALID_PARAMETER      Info was NULL  

 **/
EFI_STATUS
I2cHcGetInfo(
    IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL     *This,
    OUT       AMI_I2C_LOCATION_INFO             *Info
    )
{
    I2C_BUS_INSTANCE    *I2cPort;

    if (Info == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    I2cPort = I2C_PRIVATE_DATA_FROM_THIS (This);
    CopyMem (Info, &I2cPort->Location, sizeof (AMI_I2C_LOCATION_INFO));

    return EFI_SUCCESS;
}

/**

  Access the I2C bus

  @param[in]      This                  I2C Host Controller
  @param[in]      SlaveAddress          Device slave address
  @param[in]      RequestPacket         read/write packages
  @param[in]      Event                 triggered Event after executed RequestPacket

  @retval EFI_SUCCESS
  @retval EFI_DEVICE_ERROR      I2C bus not exist
  @retval EFI_TIMEOUT           Device is no acknowledge

 **/
EFI_STATUS
I2cHcStartRequest(
    IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL     *This,
    IN        UINTN                             SlaveAddress,
    IN        EFI_I2C_REQUEST_PACKET            *RequestPacket,
    IN        EFI_EVENT                         Event      OPTIONAL,
    OUT       EFI_STATUS                        *I2cStatus OPTIONAL
    )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    I2C_BUS_INSTANCE    *I2cPort;
    UINTN               MmioBase;
    UINTN               BufferLen[2];
    UINT8               *Buffer[2];

    I2cPort   = I2C_PRIVATE_DATA_FROM_THIS (This);
    MmioBase  = I2cPort->I2cBase;
    //MmioBase = FindSerialIoBar (PchSerialIoIndexI2C0,0);

    Buffer[0]    = RequestPacket->Operation[0].Buffer;
    BufferLen[0] = RequestPacket->Operation[0].LengthInBytes;
    Buffer[1]    = RequestPacket->OperationCount == 2 ? RequestPacket->Operation[1].Buffer : NULL;
    BufferLen[1] = RequestPacket->OperationCount == 2 ? RequestPacket->Operation[1].LengthInBytes : 0;

    switch (RequestPacket->Operation[0].Flags) {
        //
        // I2C Master request for write. Bit0 = 0
        //
        case 0:
            Status = I2cWriteRead (MmioBase, (UINT8)SlaveAddress, BufferLen[0], Buffer[0], BufferLen[1], Buffer[1]);
            break;

        //
        // I2C Master request for read. Bit0 = 1
        //
        case I2C_FLAG_READ:
            Status = I2cWriteRead (MmioBase, (UINT8)SlaveAddress, BufferLen[1], Buffer[1], BufferLen[0], Buffer[0]);
            break;
    }
    return Status;
}

/**

    Get the I2C Bus Configuration of Frequency
  
    @param[in]   This                  I2C Host Controller
    @param[out]  Freq                  Current I2C bus Freq
    
    @retval EFI_SUCCESS                The I2C bus frequency was returned
                                       successfully.
    @retval EFI_INVALID_PARAMETER      Freq was NULL

**/
EFI_STATUS
I2cHcGetConfiguration (
    IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL   *This,
    OUT       UINTN                           *Freq
    )
{
    I2C_BUS_INSTANCE    *I2cPort;
    UINTN               MmioBase;
    UINT8               Reg8;

    if (Freq == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    I2cPort = I2C_PRIVATE_DATA_FROM_THIS (This);
    MmioBase = I2cPort->I2cBase;
    // MmioBase = FindSerialIoBar (PchSerialIoIndexI2C0, 0);

    Reg8 = MmioRead8 (MmioBase + R_IC_CON);
    switch (Reg8 & (BIT2|BIT3)) {
        case V_IC_SPEED_STANDARD:
            *Freq = I2C_HC_100KHZ;
            break;
        case V_IC_SPEED_FAST:
            *Freq = I2C_HC_400KHZ;
            break;
        case V_IC_SPEED_HIGH:
            *Freq = I2C_HC_3_4MHZ;
            break;
    }

    DEBUG ((EFI_D_INFO, "0x%016Lx: I2C bus frequency get, %d HZ\r\n", (UINT64)(UINTN)I2cPort, *Freq));

    return EFI_SUCCESS;

    //  I2C_BUS_INSTANCE    *I2cPort;
    //  UINTN               I2CBaseAddress;
    //  UINTN               PciMmBase;
    //  UINT8               Reg8;

    //  I2cPort = I2C_PORT_CONTEXT_FROM_MASTER_PROTOCOL ( This );
    //
    //  PciMmBase = MmPciAddress (
    //                0,
    //                I2cPort->Location.Pci.Bus,
    //                I2cPort->Location.Pci.Dev,
    //                I2cPort->Location.Pci.Func,
    //                0
    //                );
    //
    //  I2CBaseAddress = MmioRead32 (PciMmBase + R_LPSS_IO_BAR) & B_LPSS_IO_BAR_BA;
    //
    //  *Freq = 0;
    //  Reg8 = MmioRead8 ( I2CBaseAddress + R_IC_CON);
    //  
    //  switch (Reg8&(BIT2|BIT3)) {
    //  case V_SPEED_STANDARD:
    //    *Freq =  I2C_HC_100KHZ;
    //    break;
    //  case V_SPEED_FAST:
    //    *Freq = I2C_HC_400KHZ;
    //    break;
    //  case V_SPEED_HIGH:
    //    *Freq = I2C_HC_3_4MHZ;
    //    break;
    //  }
    //
    //  DEBUG (( DEBUG_I2C_OPERATION, "0x%016Lx: I2C bus frequency get, %d HZ\r\n", (UINT64)(UINTN)I2cPort, *Freq));

    //return EFI_SUCCESS;
}
/**

  Set the I2C Bus Configuration of Frequency, default value is 100KHz

  @param[in]   This                  I2C Host Controller
  @param[in]   Freq                  I2C bus Freq

  @retval EFI_SUCCESS
  @retval EFI_NO_MAPPING             wrong frequence

 **/
EFI_STATUS
I2cHcSetConfiguration (
    IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL     *This,
    IN        UINTN                             BusClockHertz
    )
{
    //UINT32             Speed;
    I2C_BUS_INSTANCE   *I2cPort;
    UINTN              MmioBase;
    UINT16             I2cMode = 0;
    // UINTN              hCnt = 0;
    // UINTN              lCnt = 0;

    I2cPort  = I2C_PRIVATE_DATA_FROM_THIS (This);
    MmioBase = I2cPort->I2cBase;

    // if (BusClockHertz < 100*1000) {
    //     //can't run that slowly
    //     return EFI_UNSUPPORTED;
    // } else if (BusClockHertz < 400*1000) {
    //     //for any request in range [100kHz, 400kHz), set 100kHz
    //     BusClockHertz = 100000;
    //     Speed = V_IC_SPEED_STANDARD;
    //     MmioWrite32(MmioBase + R_IC_SDA_HOLD, 0x001C001C);
    //     MmioWrite32(MmioBase + R_IC_SS_SCL_HCNT, 528);
    //     MmioWrite32(MmioBase + R_IC_SS_SCL_LCNT, 640);
    // } else if (BusClockHertz < 1000*1000) {
    //     //for any request in range [400kHz, 1MHz), set 400kHz
    //     BusClockHertz = 400000;
    //     Speed = V_IC_SPEED_FAST;
    //     MmioWrite32(MmioBase + R_IC_SDA_HOLD, 0x001C001C);
    //     MmioWrite32(MmioBase + R_IC_FS_SCL_HCNT, 128);
    //     MmioWrite32(MmioBase + R_IC_FS_SCL_LCNT, 160);
    // } else {
    //     //for any request in range [1MHz, +inf), set 1MHz. This silicon doesn't support 3.4MHz mode.
    //     BusClockHertz = 1000000;
    //     Speed = V_IC_SPEED_FAST;
    //     MmioWrite32(MmioBase + R_IC_SDA_HOLD, 0x00280028);
    //     MmioWrite32(MmioBase + R_IC_FS_SCL_HCNT, 30);
    //     MmioWrite32(MmioBase + R_IC_FS_SCL_LCNT, 80);
    // }

    I2cBusFrequencySet(MmioBase, BusClockHertz, &I2cMode);
    MmioWrite32(MmioBase + R_IC_CON, I2cMode);
    // MmioWrite32(MmioBase + R_IC_CON, Speed | B_IC_RESTART_EN | B_IC_SLAVE_DISABLE | B_IC_MASTER_MODE);

    return EFI_SUCCESS;

}

/**

  Reset I2C Host

  @param[in]  This                  I2C Host Controller
  @param[in]  Slave                 I2C Slave Addr

  @retval EFI_SUCCESS

 **/
EFI_STATUS
I2cHcReset (
    IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL     *This,
    IN  UINTN                                   Slave
    )
{
    // I2C_BUS_INSTANCE    *I2cPort;
    // UINTN               MmioAddress;
    // EFI_STATUS          Status = EFI_SUCCESS;
    //
    //
    // I2cPort   = I2C_PRIVATE_DATA_FROM_THIS (This);
    // MmioAddress  = I2cPort->I2cBase;

    return EFI_SUCCESS;
}
/**

  Switch I2C host controller to Slave/Master mode

  @param[in]  This                  I2C Host Controller
  @param[out] Mode                  Switch the I2C to Slave/Master mode

  @retval EFI_SUCCESS
  @retval EFI_UNSUPPORTED           Doesn't support this function

 **/
EFI_STATUS
I2cHcSwitchMode(
    IN  CONST AMI_I2C_HC_OPERATION_PROTOCOL     *This,
    IN  OUT I2C_ACTIVE_MODE                     Mode
    )
{
    I2C_BUS_INSTANCE    *I2cPort;
    UINTN               MmioBase;

    DEBUG ((EFI_D_INFO, "I2cHcSwitchMode ..\n" ));

    I2cPort   = I2C_PRIVATE_DATA_FROM_THIS (This);
    MmioBase = I2cPort->I2cBase;
    //MmioBase = FindSerialIoBar (PchSerialIoIndexI2C0,0);

    switch (Mode) {
        case MasterMode:
            MmioAnd32 ( MmioBase + R_IC_CON, (B_IC_MASTER_MODE | B_IC_RESTART_EN | B_IC_SLAVE_DISABLE));
            break;

        case SlaveMode:
            MmioAnd32 (MmioBase + R_IC_CON, ~(B_IC_MASTER_MODE | B_IC_SLAVE_DISABLE));
            break;
    }

    //
    //  //
    //  //  Locate the configuration
    //  //
    //  I2cPort = I2C_PORT_CONTEXT_FROM_MASTER_PROTOCOL ( This );
    //
    //  if (!(I2cPort->Location.Header.Capabilities & I2C_HC_CAP_SWITCH_MODE)) {
    //    return EFI_UNSUPPORTED;
    //  }

    return EFI_SUCCESS;  
}

/**
  Init the I2C Protocl

  This routine allocates the necessary resources for the driver.


  @param [in] I2cOperation       Address of an AMI_I2C_HC_OPERATION_PROTOCOL structure

  @retval EFI_SUCCESS         Driver API properly initialized

 **/
EFI_STATUS
I2cHcOperationProtocolInit (
    IN AMI_I2C_HC_OPERATION_PROTOCOL     *I2cHcOperation
    )
{
    DEBUG ((EFI_D_INFO, "I2cHcOperationProtocolInit ..\n" ));

    //
    //  Initialize the I2C Hc Operation Protocol
    //
    I2cHcOperation->Version             = AMI_I2C_HC_VERSION_1;
    I2cHcOperation->GetInfo             = I2cHcGetInfo;
    I2cHcOperation->GetConfiguration    = I2cHcGetConfiguration;
    I2cHcOperation->SetConfiguration    = I2cHcSetConfiguration;
    I2cHcOperation->StartRequest        = I2cHcStartRequest;
    I2cHcOperation->Reset               = I2cHcReset;
    I2cHcOperation->Switch              = I2cHcSwitchMode;

    //
    //  The port is successfully configured
    //
    DEBUG (( DEBUG_LOAD, "I2cOperationProtocolInit exiting, Status: %r\r\n", EFI_SUCCESS ));

    //
    //  Return the startup status
    //
    return EFI_SUCCESS;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
