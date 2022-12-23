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

//**********************************************************************
/** @file SbSerialPortLib.c
   Sb serial port debug

**/
//**********************************************************************
#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>
#ifdef SB_SERIALPORT_RUNTIME
#include <Library/UefiRuntimeServicesTableLib.h>
#endif //SB_SERIALPORT_RUNTIME
#include <Token.h>
#include <Sb.h>


#define FCH_UART_RXBUF          0
#define FCH_UART_TXBUF          0
#define FCH_UART_BAUD_LOW       0
#define FCH_UART_BAUD_HIGH      1
#define FCH_UART_FCR            2
#define   FCH_UART_FCR_FIFOE    BIT0
#define   FCH_UART_FCR_FIFO64   BIT5
#define FCH_UART_LCR            3
#define   FCH_UART_LCR_DLAB     BIT7
#define FCH_UART_MCR            4
#define   FCH_UART_MCR_RTS      BIT1
#define FCH_UART_LSR            5
#define   FCH_UART_LSR_RXRDY    BIT0
#define   FCH_UART_LSR_TXRDY    BIT5
#define   FCH_UART_LSR_TEMT     BIT6
#define FCH_UART_MSR            6
#define   FCH_UART_MSR_CTS      BIT4
#define   FCH_UART_MSR_DSR      BIT5

#define FCH_SRR_OFFSET              0x88

/**
  ## Line Control Register (LCR) for the 16550 serial port.  This encodes data bits, parity, and stop bits.  
  #    BIT1..BIT0 - Data bits.  00b = 5 bits, 01b = 6 bits, 10b = 7 bits, 11b = 8 bits
  #    BIT2       - Stop Bits.  0 = 1 stop bit.  1 = 1.5 stop bits if 5 data bits selected, otherwise 2 stop bits.
  #    BIT5..BIT2 - Parity.  xx0b = No Parity, 001b = Odd Parity, 011b = Even Parity, 101b = Mark Parity, 111b=Stick Parity
  #    BIT7..BIT6 - Reserved.  Must be 0.
  #
  # Default is No Parity, 8 Data Bits, 1 Stop Bit.
  **/

#define FchSerialLineControl               0x3 
/**
   FIFO Control Register (FCR) for the 16550 serial port.   
  #    BIT0       - FIFO Enable.  0 = Disable FIFOs.  1 = Enable FIFOs.
  #    BIT1       - Clear receive FIFO.  1 = Clear FIFO.
  #    BIT2       - Clear transmit FIFO.  1 = Clear FIFO.
  #    BIT4..BIT3 - Reserved.  Must be 0.
  #    BIT5       - Enable 64-byte FIFO.  0 = Disable 64-byte FIFO.  1 = Enable 64-byte FIFO
  #    BIT7..BIT6 - Reserved.  Must be 0.
  #
  # Default is to enable and clear all FIFOs.
**/

#define FchSerialFifoControl               0x7 

/**
  ## If TRUE, then the 16550 serial port hardware flow control is enabled.
  #  If FALSE, then the 16550 serial port hardware flow control is disabled.  Default value.
**/
#define FchSerialUseHardwareFlowControl       FALSE 

/**
  ## If TRUE, then 16550 serial Tx operations will block if DSR is not asserted (no cable).
  #  If FALSE, then the 16550 serial Tx operations will not be blocked if DSR is not asserted. Default value.
  #  This define is ignored if FchSerialUseHardwareFlowControl is FALSE.
**/

#define FchSerialDetectCable       FALSE 


GLOBAL_REMOVE_IF_UNREFERENCED UINTN  gSbUartBASE = 0xFEDC6000;//default Uart0 address
/**
   Update the FCH Uart base address as chip
        
    @param VOID 

    @retval VOID

**/

UpdateUartMmioAsChip (){

	// Sandstone uart mmio address
	switch (FCH_UART_DEBUG_SELECT) {
		case 4 :
			gSbUartBASE = 0xFEDCF000;
			break;
		case 3 :
			gSbUartBASE = 0xFEDCE000;
			break;
		case 2 :
			gSbUartBASE = 0xFEDCA000;
			break;
		case 1 :
			gSbUartBASE = 0xFEDC9000;
			break;
	}

} 

/**
   Get the FCH Uart base address
        
    @param VOID 

    @retval VOID

**/

UINTN
GetSbUartBase (VOID)
{
  return gSbUartBASE;
}


#ifdef SB_SERIALPORT_RUNTIME

VOID EFIAPI InitAmiRuntimeLib(
    IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable,
    IN EFI_EVENT_NOTIFY ExitBsCallback OPTIONAL,
    IN EFI_EVENT_NOTIFY GoVirtualCallback OPTIONAL
);

/**

        
    @param Event 
    @param Context 

    @retval VOID

**/
VOID SbUartBaseVirtualAddressChange (
    IN EFI_EVENT Event, IN VOID *Context
)
{
  UpdateUartMmioAsChip();
  gRT->ConvertPointer(0, (VOID**)&gSbUartBASE);
}

/**

    @param ImageHandle 
    @param SystemTable 

         
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
EFIAPI
SBSerialPortRuntimeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  InitAmiRuntimeLib(ImageHandle, SystemTable, NULL, SbUartBaseVirtualAddressChange);
  return EFI_SUCCESS;
}

#endif  //SB_SERIALPORT_RUNTIME

/**
  Read an 8-bit 16550 register.  If PcdSerialUseMmio is TRUE, then the value is read from 
  MMIO space.  If PcdSerialUseMmio is FALSE, then the value is read from I/O space.  The
  parameter Offset is added to the base address of the 16550 registers that is specified 
  by PcdSerialRegisterBase. 
  
  @param  Offset  The offset of the 16550 register to read.

  @return The value read from the 16550 register.

**/
UINT8
SerialPortReadRegister (
  UINTN  Offset
  )
{
  return MmioRead8 (GetSbUartBase()+ Offset*4);
}


/**
  Write an 8-bit 16550 register.  If PcdSerialUseMmio is TRUE, then the value is written to
  MMIO space.  If PcdSerialUseMmio is FALSE, then the value is written to I/O space.  The
  parameter Offset is added to the base address of the 16550 registers that is specified 
  by PcdSerialRegisterBase. 
  
  @param  Offset  The offset of the 16550 register to write.
  @param  Value   The value to write to the 16550 register specified by Offset.

  @return The value written to the 16550 register.

**/

UINT8
SerialPortWriteRegister (
  UINTN  Offset,
  UINT8  Value
  )
{
  return MmioWrite8 (GetSbUartBase()+ Offset*4, Value);
}

/**
  Delay time 

  @param  Usec           delay time with unit us 
  @retval 

**/
VOID SbUartStall (UINTN Usec)
{
  UINTN   Counter = (Usec * 7)/2; // 3.58 count per microsec
  UINTN   i;
  UINT32  Data32;
  UINT32  PrevData;

  MmioWrite16(ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG64,PM_TMR_BLK_ADDRESS); //decode timer base address
  PrevData = IoRead32(PM_TMR_BLK_ADDRESS);
  for (i=0; i < Counter; ) {
     Data32 = IoRead32(PM_TMR_BLK_ADDRESS);
      if (Data32 < PrevData) {        // Reset if there is a overlap
          PrevData=Data32;
          continue;
      }
      i += (Data32 - PrevData);
	PrevData=Data32; // FIX need to find out the real diff betweek different count.
  }
}

/**
  Power on  Fch Uart device 
  
  @retval NONE
**/

VOID
SbUartPowerOn (
  )
{

}


/**
  Return whether the hardware flow control signal allows writing.

  @retval TRUE  The serial port is writable.
  @retval FALSE The serial port is not writable.
**/
BOOLEAN
SerialPortWritable (
  VOID
  )
{
  if (FchSerialUseHardwareFlowControl) {
    if (FchSerialDetectCable) {
      //
      // Wait for both DSR and CTS to be set
      //   DSR is set if a cable is connected.
      //   CTS is set if it is ok to transmit data
      //
      //   DSR  CTS  Description                               Action
      //   ===  ===  ========================================  ========
      //    0    0   No cable connected.                       Wait
      //    0    1   No cable connected.                       Wait
      //    1    0   Cable connected, but not clear to send.   Wait
      //    1    1   Cable connected, and clear to send.       Transmit
      //
      return (BOOLEAN) ((SerialPortReadRegister (FCH_UART_MSR) & (FCH_UART_MSR_DSR | FCH_UART_MSR_CTS)) == (FCH_UART_MSR_DSR | FCH_UART_MSR_CTS));
    } else {
      //
      // Wait for both DSR and CTS to be set OR for DSR to be clear.  
      //   DSR is set if a cable is connected.
      //   CTS is set if it is ok to transmit data
      //
      //   DSR  CTS  Description                               Action
      //   ===  ===  ========================================  ========
      //    0    0   No cable connected.                       Transmit
      //    0    1   No cable connected.                       Transmit
      //    1    0   Cable connected, but not clear to send.   Wait
      //    1    1   Cable connected, and clar to send.        Transmit
      //
      return (BOOLEAN) ((SerialPortReadRegister (FCH_UART_MSR) & (FCH_UART_MSR_DSR | FCH_UART_MSR_CTS)) != (FCH_UART_MSR_DSR));
    }
  }

  return TRUE;
}

/**
  Initialize the serial device hardware.
  
  If no initialization is required, then return RETURN_SUCCESS.
  If the serial device was successfully initialized, then return RETURN_SUCCESS.
  If the serial device could not be initialized, then return RETURN_DEVICE_ERROR.
  
  @retval RETURN_SUCCESS        The serial device was initialized.
  @retval RETURN_DEVICE_ERROR   The serial device could not be initialized.

**/
RETURN_STATUS
EFIAPI
SerialPortInitialize (
  VOID
  )
{
 //Update the uart base address as the different chip    
  UpdateUartMmioAsChip();
  
  //Open the UART
  SbUartPowerOn();
  
  //default use BAUD rate 115200
  MmioWrite8 (GetSbUartBase()+FCH_SRR_OFFSET, 0x01); //reset UART0
  
  SerialPortWriteRegister (FCH_UART_LCR, FCH_UART_LCR_DLAB);
  SerialPortWriteRegister (FCH_UART_BAUD_HIGH, 00);
  SerialPortWriteRegister (FCH_UART_BAUD_LOW, 0x1a); //set 115200

  //
  // Clear DLAB and configure Data Bits, Parity, and Stop Bits.
  // Strip reserved bits from PcdSerialLineControl
  //
  SerialPortWriteRegister (FCH_UART_LCR, (UINT8)(FchSerialLineControl & 0x3F));

  //
  // Enable and reset FIFOs
  // Strip reserved bits from PcdSerialFifoControl
  //
  SerialPortWriteRegister (FCH_UART_FCR, (UINT8)(FchSerialFifoControl & 0x27));

  //
  // Put Modem Control Register(MCR) into its reset state of 0x00.
  //  
  SerialPortWriteRegister (FCH_UART_MCR, 0x00);


  //Configure UART pin
#if (defined(FCH_UART_DEBUG_SELECT) && (FCH_UART_DEBUG_SELECT == 1))     
  MmioWrite8 (FCH_IOMUXx89_UART0_RTS_L_EGPIO137, 0x00);
  MmioWrite8 (FCH_IOMUXx8A_UART0_TXD_EGPIO138, 0x00);
#endif //#if (defined(FCH_UART_DEBUG_SELECT) && (FCH_UART_DEBUG_SELECT == 1)) 
   
#if (defined(FCH_UART_DEBUG_SELECT) && (FCH_UART_DEBUG_SELECT == 2)) 
  MmioWrite8 (FCH_IOMUXx8E_UART1_RTS_L_EGPIO142, 0x00);
  MmioWrite8 (FCH_IOMUXx8F_UART1_TXD_EGPIO143, 0x00);
#endif //#if (defined(FCH_UART_DEBUG_SELECT) && (FCH_UART_DEBUG_SELECT == 2)) 
   
  return RETURN_SUCCESS;
}

/**
  Write data from buffer to serial device. 
 
  Writes NumberOfBytes data bytes from Buffer to the serial device.  
  The number of bytes actually written to the serial device is returned.
  If the return value is less than NumberOfBytes, then the write operation failed.

  If Buffer is NULL, then ASSERT(). 

  If NumberOfBytes is zero, then return 0.

  @param  Buffer           Pointer to the data buffer to be written.
  @param  NumberOfBytes    Number of bytes to written to the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes written to the serial device.  
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
SerialPortWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
)
{

  UINTN    Result;
  UINTN    Index;
  UINTN    FifoSize;
  
  if (NULL == Buffer) {
    return 0;
  }

  //Check  is the Serial port init ok
  if ((SerialPortReadRegister (FCH_UART_LCR) & 0x3F) !=FchSerialLineControl) {
  //re initial  
  SerialPortInitialize();
  }
  
  if (NumberOfBytes == 0) {
    //
    // Flush the hardware
    //

    //
    // Wait for both the transmit FIFO and shift register empty.
    //
    while ((SerialPortReadRegister (FCH_UART_LSR) & FCH_UART_LSR_TEMT) == 0);

    while (!SerialPortWritable ());
    return 0;
  }
  
   
     //
  // Compute the maximum size of the Tx FIFO
  //
  FifoSize = 1;
  if ((FchSerialFifoControl & FCH_UART_FCR_FIFOE) != 0) {
    if ((FchSerialFifoControl & FCH_UART_FCR_FIFO64) == 0) {
      FifoSize = 16;
    } else {
      FifoSize = 64;
    }
  }
    
   Result = NumberOfBytes;
  while (NumberOfBytes != 0) {
    //
    // Wait for the serial port to be ready, to make sure both the transmit FIFO
    // and shift register empty.
    //
    while ((SerialPortReadRegister (FCH_UART_LSR) & FCH_UART_LSR_TEMT) == 0);

    //
    // Fill then entire Tx FIFO
    //
    for (Index = 0; Index < FifoSize && NumberOfBytes != 0; Index++, NumberOfBytes--, Buffer++) {
      //
      // Wait for the hardware flow control signal
      //
     // while (!SerialPortWritable ());
       while (!SerialPortWritable ());
       
      //
      // Write byte to the transmit buffer.
      //
      SerialPortWriteRegister (FCH_UART_TXBUF, *Buffer);
    }
  }

  return Result;
  
}

/**
  Reads data from a serial device into a buffer.

  @param  Buffer           Pointer to the data buffer to store the data read from the serial device.
  @param  NumberOfBytes    Number of bytes to read from the serial device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes read from the serial device.  
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
SerialPortRead (
  OUT UINT8     *Buffer,
  IN  UINTN     NumberOfBytes
)
{
  UINTN  Result;
  UINT8  Mcr;
 
  if (NULL == Buffer) {
      return 0;
  }

  Mcr = (UINT8)(SerialPortReadRegister (FCH_UART_MCR) & ~FCH_UART_MCR_RTS);


  for (Result = 0; NumberOfBytes-- != 0; Result++, Buffer++) {
      //
      // Wait for the serial port to have some data.
      //
      while ((SerialPortReadRegister (FCH_UART_LSR) & FCH_UART_LSR_RXRDY) == 0) {
      
          if (FchSerialUseHardwareFlowControl) {
          //
          // Set RTS to let the peer send some data
          //
          SerialPortWriteRegister (FCH_UART_MCR, (UINT8)(Mcr | FCH_UART_MCR_RTS));
         }
      }
      
      if (FchSerialUseHardwareFlowControl) {
        //
        // Clear RTS to prevent peer from sending data
        //
        SerialPortWriteRegister (FCH_UART_MCR, Mcr);
      }
      
      //
      // Read byte from the receive buffer.
      //
      *Buffer = SerialPortReadRegister (FCH_UART_RXBUF);
  }

  return Result;
}


/**
  Polls a serial device to see if there is any data waiting to be read.

  Polls aserial device to see if there is any data waiting to be read.
  If there is data waiting to be read from the serial device, then TRUE is returned.
  If there is no data waiting to be read from the serial device, then FALSE is returned.

  @retval TRUE             Data is waiting to be read from the serial device.
  @retval FALSE            There is no data waiting to be read from the serial device.

**/
BOOLEAN
EFIAPI
SerialPortPoll (
  VOID
  )
{
  //
  // Read the serial port status
  //
  if ((SerialPortReadRegister (FCH_UART_LSR) & FCH_UART_LSR_RXRDY) != 0) {
      if (FchSerialUseHardwareFlowControl) {
      //
      // Clear RTS to prevent peer from sending data
      //
      SerialPortWriteRegister (FCH_UART_MCR, (UINT8)(SerialPortReadRegister (FCH_UART_MCR) & ~FCH_UART_MCR_RTS));
    }
    return TRUE;
  }    
  
    if (FchSerialUseHardwareFlowControl) {
    //
    // Set RTS to let the peer send some data
    //
    SerialPortWriteRegister (FCH_UART_MCR, (UINT8)(SerialPortReadRegister (FCH_UART_MCR) | FCH_UART_MCR_RTS));
  }
  
  return FALSE;
}

/**
  Init serial port

**/


RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (
  VOID
  )

{    
	SerialPortInitialize();
	
	return RETURN_SUCCESS;
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
