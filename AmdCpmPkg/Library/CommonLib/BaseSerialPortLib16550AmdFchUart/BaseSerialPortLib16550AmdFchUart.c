/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 * 
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 * 
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 * 
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 * 
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 ******************************************************************************
 */
//This file includes code originally published under the following license.

/** @file
  16550 UART Serial Port library functions

  Copyright (c) 2006 - 2012, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>
#include <Library/SerialPortLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/PlatformHookLib.h>

//
// 16550 UART register offsets and bitfields
//
#define R_UART_RXBUF          0
#define R_UART_TXBUF          0
#define R_UART_BAUD_LOW       0
#define R_UART_BAUD_HIGH      1
#define R_UART_FCR            2
#define   B_UART_FCR_FIFOE    BIT0
#define   B_UART_FCR_FIFO64   BIT5
#define R_UART_LCR            3
#define   B_UART_LCR_DLAB     BIT7
#define R_UART_MCR            4
#define   B_UART_MCR_RTS      BIT1
#define R_UART_LSR            5
#define   B_UART_LSR_RXRDY    BIT0
#define   B_UART_LSR_TXRDY    BIT5
#define   B_UART_LSR_TEMT     BIT6
#define R_UART_MSR            6
#define   B_UART_MSR_CTS      BIT4
#define   B_UART_MSR_DSR      BIT5

/**
  Read an 8-bit 16550 register.  The parameter Offset is added to the base address of the
  16550 registers that is specified by PcdSerialRegisterBase.
  @param  Offset  The offset of the 16550 register to read.
  @return The value read from the 16550 register.
**/
UINT8
SerialPortReadRegister (
  UINTN  Offset
  )
{
  return MmioRead8 ((UINTN)PcdGet64 (PcdSerialRegisterBase) + Offset * 4);
}

/**
  Write an 8-bit 16550 register. The parameter Offset is added to the base address of the
  16550 registers that is specified by PcdSerialRegisterBase.
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
  return MmioWrite8 ((UINTN)PcdGet64 (PcdSerialRegisterBase) + Offset * 4, Value);
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
  if (PcdGetBool (PcdSerialUseHardwareFlowControl)) {
    if (PcdGetBool (PcdSerialDetectCable)) {
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
      return (BOOLEAN) ((SerialPortReadRegister (R_UART_MSR) & (B_UART_MSR_DSR | B_UART_MSR_CTS)) == (B_UART_MSR_DSR | B_UART_MSR_CTS));
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
      return (BOOLEAN) ((SerialPortReadRegister (R_UART_MSR) & (B_UART_MSR_DSR | B_UART_MSR_CTS)) != (B_UART_MSR_DSR));
    }
  }

  return TRUE;
}

BOOLEAN
CheckCableConnection (
  )
{
  UINT32   RetryCount;

  // Check Cable connection
  RetryCount = 200;
  if (PcdGetBool (PcdSerialDetectCable)) {
    do {
      RetryCount--;
    } while (((SerialPortReadRegister (R_UART_MSR) & (B_UART_MSR_DSR | B_UART_MSR_CTS)) != (B_UART_MSR_DSR | B_UART_MSR_CTS)) && (RetryCount > 0));
  }

  if (RetryCount == 0) {
    // Time expired
    return FALSE;
  }
  return TRUE;
}

BOOLEAN
CheckSerialPort (
  )
{
  UINTN          Divisor;
  UINT32         SerialClkDiv16;

  SerialClkDiv16 = PcdGet32 (PcdSerialClock) / 16;
  //
  // See if the serial port is already initialized
  //
  if ((SerialPortReadRegister (R_UART_FCR) & (B_UART_FCR_FIFOE | B_UART_FCR_FIFO64)) !=
      (PcdGet8 (PcdSerialFifoControl)      & (B_UART_FCR_FIFOE | B_UART_FCR_FIFO64))     ) {
    return FALSE;
  }
  if ((SerialPortReadRegister (R_UART_LCR) & 0x3F) != (PcdGet8 (PcdSerialLineControl) & 0x3F)) {
    return FALSE;
  }
  SerialPortWriteRegister (R_UART_LCR, (UINT8)(SerialPortReadRegister (R_UART_LCR) | B_UART_LCR_DLAB));
  Divisor =  SerialPortReadRegister (R_UART_BAUD_HIGH) << 8;
  Divisor |= SerialPortReadRegister (R_UART_BAUD_LOW);
  SerialPortWriteRegister (R_UART_LCR, (UINT8)(SerialPortReadRegister (R_UART_LCR) & ~B_UART_LCR_DLAB));
  if (Divisor != SerialClkDiv16 / PcdGet32 (PcdSerialBaudRate)) {
    return FALSE;
  }
  return TRUE;
}

VOID
InitSerialPort (
  )
{
  UINTN          Divisor;
  UINT32         SerialClkDiv16;

  SerialClkDiv16 = PcdGet32 (PcdSerialClock) / 16;
  //
  // Configure baud rate
  //
  Divisor = SerialClkDiv16 / PcdGet32 (PcdSerialBaudRate);
  SerialPortWriteRegister (R_UART_LCR, B_UART_LCR_DLAB);
  SerialPortWriteRegister (R_UART_BAUD_HIGH, (UINT8) (Divisor >> 8));
  SerialPortWriteRegister (R_UART_BAUD_LOW, (UINT8) (Divisor & 0xff));

  //
  // Clear DLAB and configure Data Bits, Parity, and Stop Bits.
  // Strip reserved bits from PcdSerialLineControl
  //
  SerialPortWriteRegister (R_UART_LCR, (UINT8)(PcdGet8 (PcdSerialLineControl) & 0x3F));

  //
  // Enable and reset FIFOs
  // Strip reserved bits from PcdSerialFifoControl
  //
  SerialPortWriteRegister (R_UART_FCR, (UINT8)(PcdGet8 (PcdSerialFifoControl) & 0x27));

  //
  // Put Modem Control Register(MCR) into its reset state of 0x00.
  //
  SerialPortWriteRegister (R_UART_MCR, 0x00);
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
  RETURN_STATUS  Status;

  Status = PlatformHookSerialPortInitialize ();
  if (RETURN_ERROR (Status)) {
    return Status;
  }

  if (!CheckCableConnection()) {
    return RETURN_DEVICE_ERROR;
  }

  if (!CheckSerialPort()) {
    InitSerialPort();
  }

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
  UINT32   RetryCount;

  if (Buffer == NULL) {
    return 0;
  }

  if (!CheckCableConnection()) {
    return 0;
  }

  if (NumberOfBytes == 0) {
    //
    // Flush the hardware
    //

    //
    // Wait for both the transmit FIFO and shift register empty.
    //
    RetryCount = 2000;
    do {
      RetryCount--;
    } while (((SerialPortReadRegister (R_UART_LSR) & B_UART_LSR_TEMT) == 0) && (RetryCount > 0));

    if (RetryCount == 0) {
      InitSerialPort();
    }

    //
    // Wait for the hardware flow control signal
    //
    while (!SerialPortWritable ());
    return 0;
  }

  //
  // Compute the maximum size of the Tx FIFO
  //
  FifoSize = 1;
  if ((PcdGet8 (PcdSerialFifoControl) & B_UART_FCR_FIFOE) != 0) {
    if ((PcdGet8 (PcdSerialFifoControl) & B_UART_FCR_FIFO64) == 0) {
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
    RetryCount = 2000;
    do {
      RetryCount--;
    } while (((SerialPortReadRegister (R_UART_LSR) & B_UART_LSR_TEMT) == 0) && (RetryCount > 0));

    if (RetryCount == 0) {
      InitSerialPort();
    }

    //
    // Fill then entire Tx FIFO
    //
    for (Index = 0; Index < FifoSize && NumberOfBytes != 0; Index++, NumberOfBytes--, Buffer++) {
      //
      // Wait for the hardware flow control signal
      //
      while (!SerialPortWritable ());

      //
      // Write byte to the transmit buffer.
      //
      SerialPortWriteRegister (R_UART_TXBUF, *Buffer);
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

  Mcr = (UINT8)(SerialPortReadRegister (R_UART_MCR) & ~B_UART_MCR_RTS);

  for (Result = 0; NumberOfBytes-- != 0; Result++, Buffer++) {
    //
    // Wait for the serial port to have some data.
    //
    while ((SerialPortReadRegister (R_UART_LSR) & B_UART_LSR_RXRDY) == 0) {
      if (PcdGetBool (PcdSerialUseHardwareFlowControl)) {
        //
        // Set RTS to let the peer send some data
        //
        SerialPortWriteRegister (R_UART_MCR, (UINT8)(Mcr | B_UART_MCR_RTS));
      }
    }

    if (PcdGetBool (PcdSerialUseHardwareFlowControl)) {
      //
      // Clear RTS to prevent peer from sending data
      //
      SerialPortWriteRegister (R_UART_MCR, Mcr);
    }

    //
    // Read byte from the receive buffer.
    //
    *Buffer = SerialPortReadRegister (R_UART_RXBUF);
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
  if ((SerialPortReadRegister (R_UART_LSR) & B_UART_LSR_RXRDY) != 0) {
    if (PcdGetBool (PcdSerialUseHardwareFlowControl)) {
      //
      // Clear RTS to prevent peer from sending data
      //
      SerialPortWriteRegister (R_UART_MCR, (UINT8)(SerialPortReadRegister (R_UART_MCR) & ~B_UART_MCR_RTS));
    }
    return TRUE;
  }

  if (PcdGetBool (PcdSerialUseHardwareFlowControl)) {
    //
    // Set RTS to let the peer send some data
    //
    SerialPortWriteRegister (R_UART_MCR, (UINT8)(SerialPortReadRegister (R_UART_MCR) | B_UART_MCR_RTS));
  }

  return FALSE;
}
