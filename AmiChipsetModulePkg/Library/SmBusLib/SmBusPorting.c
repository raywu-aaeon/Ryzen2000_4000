//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//*************************************************************************
// $Header: /Alaska/BIN/Chipset/AMD/SouthBridge/TrinityHudson/Chipset/SmBus/SmBusPorting.c 1     4/11/12 3:55a Richarddai $
//
// $Revision: 1 $
//
// $Date: 4/11/12 3:55a $
//*************************************************************************

#include "Library/SmBusCommon.h"
#include "AmiCspLib.h"
#include <AmiChipsetIoLib.h>

// Token REMOTE_CTRL_ADDRESS was define under MCTP2 module.
// Append default value if MCTP2 module is not exist
#ifndef REMOTE_CTRL_ADDRESS
#define REMOTE_CTRL_ADDRESS 0x70
#endif

//Porting required - put unique GUID for given SMBUS controller
#define SM_BUS_CONTROLLER_IDENTIFIER_GUID \
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

EFI_GUID SmBusIdentifierGuid = SM_BUS_CONTROLLER_IDENTIFIER_GUID;

UINT8 SmBusPlatformReservedAddress[] = {
//Porting required - put platform hardcoded smbus addresses here
    0x00
};



/**
    This function sends commands via SMBUS interface

    @param Context SMBUS device private data
    @param SlaveAddress slave address value
    @param Command command
    @param Operation operation
    @param PecCheck parity check flag
    @param Length pointer to size of data buffer
    @param Buffer pointer to data buffer

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  Porting required

**/
EFI_STATUS Execute (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_DEVICE_ADDRESS SlaveAddress,
    IN     EFI_SMBUS_DEVICE_COMMAND Command,
    IN     EFI_SMBUS_OPERATION      Operation,
    IN     BOOLEAN                  PecCheck,
    IN OUT UINTN                    *Length,
    IN OUT VOID                     *Buffer
    )
{
    EFI_STATUS          Status = EFI_SUCCESS;
#if SB900_EC_SUPPORT
    UINT8               Data;                   // (P20100311A++)
#endif

    //================  ===============================
    SBSMBUS_PRIVATE       Private;

//(EIP37803--)    if (*Length > 32 || *Length < 1) return EFI_INVALID_PARAMETER;

    MemSet((VOID*)&Private, sizeof(SBSMBUS_PRIVATE), 0);   //Clear data


    if (*Length > 72 || *Length < 1) return EFI_INVALID_PARAMETER;


    Private.SmbusIoBase = Context->SmBusBase;  //SMBUS_BASE_ADDRESS


    Private.Context = Context;

    Private.SmbusIoWrite = SmbusIoWrite;
    Private.SmbusIoRead = SmbusIoRead;

    //--
    Private.SlaveAddress = (SlaveAddress.SmbusDeviceAddress << 1) | BIT00; // set read first
    Private.Operation = SMB_CMD_BYTE_DATA; // set byte RW default
    Private.Command = Command;
    Private.Length = *Length;
    Private.PecCheck = PecCheck;

#if SB900_EC_SUPPORT
    for (;;){
        while ((IoRead8(SMBUS_BASE_ADDRESS + 0x08)) & BIT06) {
            if (!(IoRead8(SMBUS_BASE_ADDRESS + 0x08) & BIT04 )) continue;

            //EcSemaphore is set, so make sure HostSemaphore is cleared
            Data = IoRead8(SMBUS_BASE_ADDRESS + 0x08);
            Data |= BIT05;
            IoWrite8(SMBUS_BASE_ADDRESS + 0x08, Data);
            continue;
        }

        if (IoRead8(SMBUS_BASE_ADDRESS + 0x08) & BIT04) break;

        // Request ownership of SMBus
        Data = IoRead8(SMBUS_BASE_ADDRESS + 0x08);
        Data |= BIT04;
        IoWrite8(SMBUS_BASE_ADDRESS + 0x08, Data);
    }
#endif
// <(P20100311A)

    switch (Operation) {
        case EfiSmbusQuickRead:
        case EfiSmbusQuickWrite:
            break;

        case EfiSmbusSendByte:
            Private.SlaveAddress &= ~BIT00;
        case EfiSmbusReceiveByte:
            Private.Operation = SMB_CMD_BYTE;
            break;

        // SMB_BYTE_DATA_RW
        case EfiSmbusWriteByte:
            Private.SlaveAddress &= ~BIT00;
        case EfiSmbusReadByte:
            break;

        // SMB_WORD_DATA_RW
        case EfiSmbusWriteWord:
            Private.SlaveAddress &= ~BIT00;
        case EfiSmbusReadWord:
            Private.Operation = SMB_CMD_WORD_DATA;
            break;

        // SMB_BLOCK_RW
        case EfiSmbusWriteBlock:
            Private.SlaveAddress &= ~BIT00;
        case EfiSmbusReadBlock:
            Private.Operation = SMB_CMD_BLOCK;
            break;

        case EfiSmbusProcessCall:
            break;

        case EfiSmbusBWBRProcessCall:
            break;

        default:
            break;
    }
    //
    // start Smbus access
    //
    Status = SmbusAccess(&Private, Buffer);

    *Length = Private.Length;

//#####if SB800_EC_SUPPORT
//####    // balakr0807 added to implement SMBus semaphore between System BIOS & EC firmware
//####    RESET_PCI8_SB(0x40,BIT05); // Release ownership of SMBus
//#####endif
// (P20100311A)>
#if SB900_EC_SUPPORT
    // balakr0807 added to implement SMBus semaphore between System BIOS & EC firmware
    while ((IoRead8(SMBUS_BASE_ADDRESS + 0x08)) & BIT4){

        // Release ownership of SMBus
        Data = IoRead8(SMBUS_BASE_ADDRESS + 0x08);
        Data |= BIT05;
        IoWrite8(SMBUS_BASE_ADDRESS + 0x08, Data);
    }
#endif
// <(P20100311A)

    return Status;
}

/**
    This function checks if SMBUS host received any notifications

    @param Context SMBUS device private data
    @param SlaveAddress pointer to return address of notificaion device
    @param Data pointer to notification data

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  Porting required

**/
EFI_STATUS CheckNotify (
    IN  SMBUS_PRIVATE            *Context,
    OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress,
    OUT UINTN                    *Data
    )
{
//Porting required
    return EFI_UNSUPPORTED;
}

/**
    This function initializes SMBUS PCI device and fills device context

    @param Context pointer to SMBUS host private data

    @retval VOID

    @note  Porting required

**/
VOID SmBusPeiInitialize(
    IN SMBUS_PRIVATE *Context
    )
{
    //
    // Most setting has been done in SB CIMX
    //
    //  ......
    //--<AAV>--Context->SmBusBase = SMBUS_BASE_ADDRESS;

	//
	// initial all the base.
	//
	RW_IO8_PMIO(FCH_PMIOA_REG04, BIT1, 0);
	RW_IO8_PMIO(FCH_PMIOA_REG00 + 2, BIT0, 0);
	RW_IO8_PMIO(FCH_PMIOA_REG00, BIT4, 0);

//(EIP65788+)       >>>
#if ASF_SUPPORT
	if (Context->SmBusBase == SMBUS1_BASE_ADDRESS) {
		//
		// The setting for Remote Control
		//
		//####IoWrite8(SMBUS1_BASE_ADDRESS+0xF, 0x80); // SM address of Sensor.
		//####IoWrite8(SMBUS1_BASE_ADDRESS+0xE, REMOTE_CTRL_ADDRESS); // SM address of Remote Control device.
		//####// Enable Legacy Sensor
		//####IoWrite8(SMBUS1_BASE_ADDRESS+0xD, IoRead8(SMBUS1_BASE_ADDRESS+0xD)|0x80);
		IoWrite8(SMBUS1_BASE_ADDRESS+0xF, 0x80);
		// SM address of Remote Control device.
		IoWrite8(SMBUS1_BASE_ADDRESS+0xE, REMOTE_CTRL_ADDRESS);
		//PEC enable
		IoWrite8(SMBUS1_BASE_ADDRESS+0x2, IoRead8(SMBUS1_BASE_ADDRESS+0x2)|0x80);
		//####// Enable Legacy Sensor
		IoWrite8(SMBUS1_BASE_ADDRESS+0xD, IoRead8(SMBUS1_BASE_ADDRESS+0xD)|0x80);
	}
#endif
//(EIP65788+)       <<<
}


/**

        
    @param Private 
    @param Offset 

    @retval VOID

**/
UINT8
SmbusIoRead (
  IN      SBSMBUS_PRIVATE  *Private,
  IN      UINTN           Offset
  )
{
    return IoRead8((UINT16)(Private->SmbusIoBase + Offset));
}

/**

        
    @param Private 
    @param Offset 
    @param Data 

    @retval VOID

**/
VOID
SmbusIoWrite (
  IN      SBSMBUS_PRIVATE  *Private,
  IN      UINTN           Offset,
  IN      UINTN           Data
  )
{
    IoWrite8((UINT16)(Private->SmbusIoBase + Offset),(UINT8)Data);
    return;
}

/**

        
    @param Private 
    @param reg 
    @param Set 
    @param Clear 

    @retval VOID

**/
VOID
rwSmBusIo(
  IN SBSMBUS_PRIVATE  *Private,
  IN UINT8          reg,
  IN UINT8          Set,
  IN UINT8          Clear
  )
{
    UINT8   Buffer=Private->SmbusIoRead(Private, reg);
    Buffer&=~Clear;
    Buffer|=Set;
    Private->SmbusIoWrite(Private, reg, Buffer);
}

/**

        
    @param Private 
    @param StatusBits 

         
    @retval TRUE CurrentHostStatus is ON
    @retval FALSE CurrentHostStatus is OFF

**/
BOOLEAN
isHostStatusSet(
  IN SBSMBUS_PRIVATE  *Private,
  IN UINT8          StatusBits
  )
{
    Private->CurrentHostStatus = Private->SmbusIoRead(Private,SMB_IOREG_HST_STS);
    return ((Private->CurrentHostStatus & StatusBits) != 0) ? TRUE:FALSE;
}

/**

        
    @param Private 
    @param StatusBits 

         
    @retval TRUE CurrentHostStatus is ON
    @retval FALSE CurrentHostStatus is OFF

**/
BOOLEAN
isHostStatusClear(
  IN SBSMBUS_PRIVATE  *Private,
  IN UINT8          StatusBits
  )
{
    Private->CurrentHostStatus = Private->SmbusIoRead(Private,SMB_IOREG_HST_STS);
    return ((Private->CurrentHostStatus & StatusBits) == 0) ? TRUE:FALSE;
}

/**

        
    @param Private 
    @param WaitBits 
    @param Counter 

         
    @retval TRUE CurrentHostStatus is ON
    @retval FALSE CurrentHostStatus is OFF

**/
BOOLEAN
WaitHostStatusClear(
  IN SBSMBUS_PRIVATE  *Private,
  IN UINT8          WaitBits,
  IN UINTN          Counter
  )
{
    do {
        SMBUS_DELAY_MACRO
        if(isHostStatusClear(Private, WaitBits)) break;
        Counter--;
    }while(Counter != 0);
    return (Counter == 0) ? FALSE:TRUE;
}

/**

        
    @param Private 
    @param WaitBits 
    @param Counter 

         
    @retval TRUE Counter is 0
    @retval FALSE Counter is not0

**/
BOOLEAN
WaitHostStatusSet(
  IN SBSMBUS_PRIVATE  *Private,
  IN UINT8          WaitBits,
  IN UINTN          Counter
  )
{
    do {
        SMBUS_DELAY_MACRO
        if(isHostStatusSet(Private, WaitBits)) break;
        Counter--;
    }while(Counter != 0);
    return (Counter == 0) ? FALSE:TRUE;
}

/**

        
    @param Private 
    @param WaitBits 
    @param CheckBits 
    @param Counter 

         
    @retval TRUE CurrentHostStatus is ON
    @retval FALSE CurrentHostStatus is OFF

**/
BOOLEAN
WaitHostStatusSetAndCheck(
  IN SBSMBUS_PRIVATE  *Private,
  IN UINT8          WaitBits,
  IN UINT8          CheckBits,
  IN UINTN          Counter
  )
{
    UINT8   HostStatus;

    if (WaitHostStatusSet(Private, WaitBits, Counter))
        HostStatus=Private->CurrentHostStatus;
    else HostStatus=0;
    return ((HostStatus&CheckBits) && Counter != 0) ? TRUE:FALSE;
}

/**

        
    @param Private 
    @param CntReg 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
SetSMBusEnvironment (
  IN SBSMBUS_PRIVATE      *Private,
  OUT UINT8             *CntReg
  )
{
    EFI_STATUS  Status = EFI_SUCCESS;
    
    
    { //Sync the AgesaPI SMBUS.c
      UINT16                 LoopCount;
       UINT8                  retryCount;
      UINT8                  bValue;
      BOOLEAN                IsBusy;
        
    
      // Keep polling until host gets SMBUS control
      LoopCount = 100;
      do {
      
        bValue = Private->SmbusIoRead(Private, SMB_IOREG08);
        bValue |= BIT4;       // Set HostSemaphore
        Private->SmbusIoWrite(Private,SMB_IOREG08,bValue);

        IoRead8 (0xed); // 0xed IO Delay
        IoRead8 (0xed); // 0xed IO Delay

        bValue = Private->SmbusIoRead(Private, SMB_IOREG08);
        LoopCount--;
      } while ((bValue & BIT4) == 0);     // Loop until semaphore has established

      
          // Clear host status and wait until host is idle
      IsBusy = TRUE;
      retryCount = 3;
      while (retryCount--) {
        LoopCount = 100;
        do {
           Private->SmbusIoWrite(Private, SMB_IOREG_HST_STS,0x1f);// Clear all status bits
           IoRead8 (0xed); // 0xed IO Delay
           IoRead8 (0xed); // 0xed IO Delay
           bValue = Private->SmbusIoRead(Private, SMB_IOREG_HST_STS);
          if ( ! ( bValue & BIT0) ) {
            IsBusy = FALSE;         // Bit0 = 0, controller is idle
            break;
          }
        } while (LoopCount--);
        if (!IsBusy) {
          break;
        }
        Private->SmbusIoWrite(Private, SMB_IOREG_HST_CNT,HST_CNT_KILL);// Set [1] = Kill current host transaction
      }

      // Clear slave status and wait until slave is idle
      IsBusy = TRUE;
      retryCount = 3;
      while (retryCount--) {
        LoopCount = 100;
        do {
           Private->SmbusIoWrite(Private, SMB_IOREG01,0x3f);// Clear SMB_ALL_SLAVE_STATUS   
           IoRead8 (0xed); // 0xed IO Delay
           IoRead8 (0xed); // 0xed IO Delay
           bValue = Private->SmbusIoRead(Private, SMB_IOREG01);
          if ( ! ( bValue & BIT0) ) {
            IsBusy = FALSE;         // Bit0 = 0, slave is idle
            break;
          }
        } while (LoopCount--);
        if (!IsBusy) {
          break;
        }
        Private->SmbusIoWrite(Private, SMB_IOREG01,BIT1);// Set BIT1 = SlaveInit
      }
  }
      
      
     *CntReg=Private->SmbusIoRead(Private, SMB_IOREG_HST_CNT);

    // Try to obtain SMBUS ownership
    if (WaitHostStatusClear(Private, HST_STS_INUSE_STS, 0xFFFF)) {
        Status = EFI_SUCCESS;
    }else Status = EFI_DEVICE_ERROR;

    // DisableInterruptAndSetConfiguration
    //--InterruptState = CPULib_GetInterruptState();
    //--CPULib_DisableInterrupt();
    rwSmBusIo(Private,SMB_IOREG_HST_CNT,0,\
        (HST_CNT_START+HST_CNT_SMB_CMD+HST_CNT_KILL+HST_CNT_INTRENN));
    //--if (InterruptState) CPULib_EnableInterrupt();

    // Try to force SMBUS ownership
    // TryToForceSMBusOwnership
    //---if (!WaitHostStatusClear(Private, HST_STS_INUSE_STS, 0xFFFF))
    if (isHostStatusSet(Private, HST_STS_INUSE_STS)) {
        if (Private->CurrentHostStatus&HST_STS_HOST_BUSY) {

            rwSmBusIo(Private,SMB_IOREG_HST_CNT,HST_CNT_KILL,0);

            if (WaitHostStatusSet(Private, HST_STS_FAILED, 1000)) {
                // Current host transaction is killed, set for normal host controller functionality
                Status = EFI_SUCCESS;
                rwSmBusIo(Private,SMB_IOREG_HST_CNT,0,HST_CNT_KILL);
            }else {
                Status = EFI_DEVICE_ERROR;
                return Status;
            }
        }
        // Claim SMBUS ownership
        // ReleaseSMBUSOwnership
        rwSmBusIo(Private,SMB_IOREG_HST_STS,HST_STS_INUSE_STS,0);

        if (isHostStatusClear(Private, HST_STS_INUSE_STS)) {
            Status = EFI_SUCCESS;
        }else {
            Status = EFI_DEVICE_ERROR;
        }
    }

    return Status;
}

/**

    @param Private 

    @retval VOID

**/
VOID ClearHostStatus (
  IN SBSMBUS_PRIVATE       *Private
  )
{
    Private->SmbusIoWrite(Private, SMB_IOREG_HST_STS, HST_STS_ERROR+HST_STS_INTR);
}

/**

    @param Private 

    @retval VOID

**/
VOID WriteCommand (
  IN SBSMBUS_PRIVATE       *Private
  )
{
    if (Private->Operation == SMB_CMD_BYTE) return;
    Private->SmbusIoWrite(Private,SMB_IOREG_HST_CMD,Private->Command);
}

/**

        
    @param Private 

    @retval VOID

**/
VOID WriteSlAddr (
  IN SBSMBUS_PRIVATE       *Private
  )
{
    Private->SmbusIoWrite(Private,SMB_IOREG_XMIT_SLVA, Private->SlaveAddress);
}

/**

        
    @param Private 
    @param Buffer 

    @retval VOID

**/
VOID WriteSMBusData (
  IN SBSMBUS_PRIVATE       *Private,
  IN OUT VOID            *Buffer
  )
{
    UINTN   i,Length=Private->Length;
    UINT8   *Data=Buffer;

    for (i=0; i<Length; i++) {
        if (Private->Operation == SMB_CMD_BLOCK) {
            Private->SmbusIoWrite(Private, SMB_IOREG_HOST_BLOCK_DB, Data[i]);
        } else if (Private->Operation == SMB_CMD_BYTE) {
            Private->SmbusIoWrite(Private,SMB_IOREG_HST_CMD,Private->Command);
            break;
        } else {
            Private->SmbusIoWrite(Private, SMB_IOREG_HST_D0+i, Data[i]);
        }
    }
}

/**

        
    @param Private 
    @param Buffer 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS ReadSmBusData (
  IN SBSMBUS_PRIVATE       *Private,
  IN OUT VOID            *Buffer
  )
{
    UINTN       i,Length=Private->Length;
    UINT8       *Data=Buffer;
    EFI_STATUS  nRet = EFI_SUCCESS;

    do{
        if (Private->Operation == SMB_CMD_BLOCK){
            Length=Private->SmbusIoRead(Private, SMB_IOREG_HST_D0);
            if(Length > Private->Length){                                        
                nRet = EFI_DEVICE_ERROR;                                          
                break;
            }
        }

    for (i=0; i<Length; i++) {
        if (Private->Operation == SMB_CMD_BLOCK) {
            Data[i] = Private->SmbusIoRead(Private, SMB_IOREG_HOST_BLOCK_DB);
            Private->SmbusIoWrite(Private, SMB_IOREG_HST_STS, HST_STS_BDS);
        } else {
            Data[i] = Private->SmbusIoRead(Private, SMB_IOREG_HST_D0 + i);
        }
    }

    Private->Length=Length;

    }while(0);
                                                
    return nRet;
}

/**

    @param Private 

    @retval VOID

**/
VOID StartSmBusTransition (
  IN SBSMBUS_PRIVATE       *Private
  )
{
    if (Private->PecCheck) {
        Private->SmbusIoWrite(Private, SMB_IOREG_AUX_CTL, (PEC_EN|PEC_APPEND));
    }

	if (Private->Context->SmBusBase == SMBUS1_BASE_ADDRESS) {
		// Set control mechanism of ASF Slave as disabled
		RESET_MMIO32(SB_MMIO_BASE + SMI_BASE + 0xA8, (BIT26 | BIT27));
		
		RESET_IO8(SMBUS1_BASE_ADDRESS + SMB_IOREG09, BIT0);
		RESET_IO8(SMBUS1_BASE_ADDRESS + SMB_IOREG15, BIT1);
	}

	// Start I2C command
    // keep PEC_EN,PEC_APPEND and start cmd
    rwSmBusIo(Private, SMB_IOREG_HST_CNT, (UINT8)(Private->Operation+HST_CNT_START), ~(PEC_EN+PEC_APPEND));
}

/**

    @param Private 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS WaitForHostIdle (
  IN SBSMBUS_PRIVATE       *Private
  )
{

    EFI_STATUS  Status = EFI_SUCCESS;

    WaitHostStatusSet(Private, HST_STS_HOST_BUSY, 5);
    if (!WaitHostStatusClear(Private, HST_STS_HOST_BUSY, 0x6000)) Status=EFI_NOT_READY;

    if (Private->Context->SmBusBase == SMBUS1_BASE_ADDRESS) {
    	SET_IO8(SMBUS1_BASE_ADDRESS + SMB_IOREG15, BIT1);
        IoWrite8(SMBUS1_BASE_ADDRESS + SMB_IOREG09, REMOTE_CTRL_ADDRESS | BIT0);

        // Set AsfSlave
        RW_IO8_PMIO(FCH_PMIOA_REG00 + 2, 0, BIT0);  

        // Set control mechanism of ASF Master as SMI
        RESET_MMIO32(SB_MMIO_BASE + SMI_BASE + 0xA8, (BIT26 | BIT27));
        SET_MMIO32(SB_MMIO_BASE + SMI_BASE + 0xA8, BIT26);
    }

    return Status;
}

/**

    @param Private 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS WaitForOperationComplete (
  IN SBSMBUS_PRIVATE       *Private
  )
{
    EFI_STATUS  Status;
    UINT8       ErrorBits=HST_STS_ERROR, CheckBits=(HST_STS_ERROR|HST_STS_INTR);

    // For ASF function.....
    // We don't need to verify the PECError[BIT4] of HostStatus[ASF_IO: 00h].
    // Since the PECAppend[BIT5] of HostControl[ASF_IO: 02h] has been set.
    if (Private->PecCheck) ErrorBits=(HST_STS_BUS_ERR|HST_STS_DEV_ERR);
    // if block check byte down
    if (Private->Operation == SMB_CMD_BLOCK)
        CheckBits=(HST_STS_BDS|HST_STS_ERROR|HST_STS_INTR);

    Status = EFI_SUCCESS;
    if (WaitHostStatusSetAndCheck(Private, \
        CheckBits, \
        ErrorBits, 700)) \
    {
        Status = EFI_DEVICE_ERROR;
    }

    return Status;
}

/**

        
    @param Private 
    @param SaveCnt 

    @retval VOID

**/
VOID RestoreSMBusEnvironment (
  IN SBSMBUS_PRIVATE       *Private,
  IN UINT8               SaveCnt
  )
{
    // Keep original PEC_EN and INTREN setting
    SaveCnt&=(HST_CNT_PEC_EN+HST_CNT_INTRENN);
    Private->SmbusIoWrite(Private, SMB_IOREG_HST_CNT, SaveCnt); // Restore original configuration

    // ReleaseSMBusOwnership    ; Release SMBUS ownership
    rwSmBusIo(Private, SMB_IOREG_HST_STS, HST_STS_INUSE_STS, 0);
}

/**

        
    @param Private 
    @param Buffer 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
SmbusAccess(
  IN SBSMBUS_PRIVATE       *Private,
  IN OUT VOID            *Buffer
  )
{
    EFI_STATUS  Status;
    BOOLEAN     IsWriteOperation = (Private->SlaveAddress & BIT00)?FALSE:TRUE;
    UINT8       SaveCnt;

    Status = SetSMBusEnvironment(Private, &SaveCnt);

    if (!EFI_ERROR(Status)) {

        if (Private->Operation == SMB_CMD_BLOCK) Private->SmbusIoWrite(Private, 0, HST_STS_BDS);
        ClearHostStatus(Private);

        WriteSlAddr(Private);
        WriteCommand(Private);

        if (Private->Operation == SMB_CMD_BLOCK) {
            Private->SmbusIoWrite(Private, SMB_IOREG_HST_D0, (UINT8)Private->Length);
        }

        if (IsWriteOperation)
            WriteSMBusData(Private, Buffer);

        if (Private->Context->SmBusBase == SMBUS1_BASE_ADDRESS) 
            RW_IO8_PMIO(FCH_PMIOA_REG00 + 2, BIT0, 0);  //Set AsfMaster

        StartSmBusTransition(Private);
        // append a delay for some C0,B2 CPU hanging issue
        //SMBUS_DELAY_MACRO
        //SMBUS_DELAY_MACRO

        if (Private->Operation == SMB_CMD_BLOCK) WaitForHostIdle(Private);

        Status = WaitForOperationComplete(Private);

        if ((Status == EFI_SUCCESS) && (IsWriteOperation == FALSE)) {
            Status = ReadSmBusData(Private, Buffer);
        }

        if (Private->Operation == SMB_CMD_BLOCK) Private->SmbusIoWrite(Private, 0, HST_STS_BDS);

    }

    RestoreSMBusEnvironment(Private,SaveCnt);

    return Status;
}


//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
