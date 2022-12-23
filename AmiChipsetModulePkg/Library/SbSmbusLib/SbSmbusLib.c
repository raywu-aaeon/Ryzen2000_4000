/** @file
Implementation of SmBusLib class library for DXE phase.

Copyright (c) 2006 - 2010, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.


**/

#include <PiDxe.h>

#include <Protocol/SmbusHc.h>

#include <Library/SmbusLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

#include <IndustryStandard/SmBus.h>
#include "Library/SmBusCommon.h"
#include <Sb.h>
#include <Library/PcdLib.h>

/**
    This function waits given number of microseconds

    @param This
    @param Microseconds number of microseconds to wait

    @retval VOID

    @note  Porting required

**/
VOID SmBusDxeSmmWait(
    IN SMBUS_PRIVATE *This,
    IN UINTN Microseconds   //count in 15microsec
    )
{
    UINT8   Reference = IoRead8(0x61) & 0x10;
    UINT8   Current;

    while(Microseconds)
    {
        Current = IoRead8(0x61) & 0x10;
        if (Reference != Current)
        {
            Reference = Current;
            Microseconds--;
        }
    }

}

/**
  Executes an SMBus operation to an SMBus controller.

  This function provides a standard way to execute Smbus script
  as defined in the SmBus Specification. The data can either be of
  the Length byte, word, or a block of data.

  @param  SmbusOperation  Signifies which particular SMBus hardware protocol instance
                          that it will use to execute the SMBus transactions.
  @param  SmBusAddress    The address that encodes the SMBUS Slave Address,
                          SMBUS Command, SMBUS Data Length, and PEC.
  @param  Length          Signifies the number of bytes that this operation will do.
                          The maximum number of bytes can be revision specific
                          and operation specific.
  @param  Buffer          Contains the value of data to execute to the SMBus slave
                          device. Not all operations require this argument. The
                          length of this buffer is identified by Length.
  @param  Status          Return status for the executed command.
                          This is an optional parameter and may be NULL.

  @return The actual number of bytes that are executed for this operation.

**/
UINTN
InternalSmBusExec (
  IN     EFI_SMBUS_OPERATION        SmbusOperation,
  IN     UINTN                      SmBusAddress,
  IN     UINTN                      Length,
  IN OUT VOID                       *Buffer,
     OUT RETURN_STATUS              *Status        OPTIONAL
  )
{
  //Porting required
  EFI_SMBUS_DEVICE_ADDRESS  SmbusDeviceAddress;
  UINT16                    SmBusBase;
  UINT16                    SmBusCmd;
  RETURN_STATUS             ReturnStatus;
  UINT32 					CONST FchAcpiMmioBase = PcdGet32 (AmiPcdFchAcpiMmioBase);
  // A limitation on AMD. AMD has two SmBus controller (Smbus/Asf).
  //	We guess user use ASF controller.
  UINT16					CONST TokenOfSmBusBase = SMBUS1_BASE_ADDRESS; // Use ASF controller base for the moment.
  SMBUS_PRIVATE				Private = {TokenOfSmBusBase, SmBusDxeSmmWait, 0, 0, NULL, 0, NULL};

  SmbusDeviceAddress.SmbusDeviceAddress = SMBUS_LIB_SLAVE_ADDRESS (SmBusAddress);
  SmBusBase = MmioRead16 (FchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REG00);
  SmBusCmd = SmBusBase & BIT4;
  SmBusBase &= 0xFF00;
  SmBusBase |= 0x20;

  if (SmBusBase != TokenOfSmBusBase) { // Assign a new I/O if the original address is not SMBUS1_BASE_ADDRESS
      MmioAndThenOr16 (
          FchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REG00,
		  0xFF,
          (TokenOfSmBusBase & 0xFF00) + ((SmBusCmd == 0) ? BIT4 : 0)
          );
  }

  ReturnStatus = Execute (
                  &Private, //
                  SmbusDeviceAddress,
                  SMBUS_LIB_COMMAND (SmBusAddress),
                  SmbusOperation,
                  SMBUS_LIB_PEC (SmBusAddress),
                  &Length,
                  Buffer
                  );

  // Restore the SMBus PCI Command Register
  MmioAndThenOr16 (
      FchAcpiMmioBase + PMIO_BASE + FCH_PMIOA_REG00,
	  ~BIT4,
      SmBusCmd
      );

  if (Status != NULL) {
    *Status = ReturnStatus;
  }

  return Length;
  //Porting required
}

/**
  Executes an SMBUS quick read command.

  Executes an SMBUS quick read command on the SMBUS device specified by SmBusAddress.
  Only the SMBUS slave address field of SmBusAddress is required.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If PEC is set in SmBusAddress, then ASSERT().
  If Command in SmBusAddress is not zero, then ASSERT().
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS:  The SMBUS command was executed.
                        RETURN_TIMEOUT:  A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR: The request was not
                        completed because a failure reflected in the Host Status
                        Register bit.  Device errors are a result of a transaction
                        collision, illegal command field, unclaimed cycle (host
                        initiated), or bus errors (collisions).
                        RETURN_UNSUPPORTED: The SMBus operation is not supported.

**/
VOID
EFIAPI
SmBusQuickRead (
  IN  UINTN                     SmBusAddress,
  OUT RETURN_STATUS             *Status       OPTIONAL
  )
{
  ASSERT (!SMBUS_LIB_PEC (SmBusAddress));
  ASSERT (SMBUS_LIB_COMMAND (SmBusAddress)   == 0);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  InternalSmBusExec (EfiSmbusQuickRead, SmBusAddress, 0, NULL, Status);
}

/**
  Executes an SMBUS quick write command.

  Executes an SMBUS quick write command on the SMBUS device specified by SmBusAddress.
  Only the SMBUS slave address field of SmBusAddress is required.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If PEC is set in SmBusAddress, then ASSERT().
  If Command in SmBusAddress is not zero, then ASSERT().
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.
                        Device errors are a result of a transaction collision,
                        illegal command field, unclaimed cycle (host initiated),
                        or bus errors (collisions).
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

**/
VOID
EFIAPI
SmBusQuickWrite (
  IN  UINTN                     SmBusAddress,
  OUT RETURN_STATUS             *Status       OPTIONAL
  )
{
  ASSERT (!SMBUS_LIB_PEC (SmBusAddress));
  ASSERT (SMBUS_LIB_COMMAND (SmBusAddress)   == 0);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  InternalSmBusExec (EfiSmbusQuickWrite, SmBusAddress, 0, NULL, Status);
}

/**
  Executes an SMBUS receive byte command.

  Executes an SMBUS receive byte command on the SMBUS device specified by SmBusAddress.
  Only the SMBUS slave address field of SmBusAddress is required.
  The byte received from the SMBUS is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Command in SmBusAddress is not zero, then ASSERT().
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle(host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The byte received from the SMBUS.

**/
UINT8
EFIAPI
SmBusReceiveByte (
  IN  UINTN          SmBusAddress,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINT8   Byte;

  ASSERT (SMBUS_LIB_COMMAND (SmBusAddress) == 0);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)  == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  InternalSmBusExec (EfiSmbusReceiveByte, SmBusAddress, 1, &Byte, Status);

  return Byte;
}

/**
  Executes an SMBUS send byte command.

  Executes an SMBUS send byte command on the SMBUS device specified by SmBusAddress.
  The byte specified by Value is sent.
  Only the SMBUS slave address field of SmBusAddress is required.  Value is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Command in SmBusAddress is not zero, then ASSERT().
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Value         The 8-bit value to send.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle(host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct (PEC is incorrect)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The parameter of Value.

**/
UINT8
EFIAPI
SmBusSendByte (
  IN  UINTN          SmBusAddress,
  IN  UINT8          Value,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINT8   Byte;

  ASSERT (SMBUS_LIB_COMMAND (SmBusAddress)   == 0);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  Byte   = Value;
  InternalSmBusExec (EfiSmbusSendByte, SmBusAddress, 1, &Byte, Status);

  return Value;
}

/**
  Executes an SMBUS read data byte command.

  Executes an SMBUS read data byte command on the SMBUS device specified by SmBusAddress.
  Only the SMBUS slave address and SMBUS command fields of SmBusAddress are required.
  The 8-bit value read from the SMBUS is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failurereflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle (host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct (PEC is incorrect)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The byte read from the SMBUS.

**/
UINT8
EFIAPI
SmBusReadDataByte (
  IN  UINTN          SmBusAddress,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINT8   Byte;

  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  InternalSmBusExec (EfiSmbusReadByte, SmBusAddress, 1, &Byte, Status);

  return Byte;
}

/**
  Executes an SMBUS write data byte command.

  Executes an SMBUS write data byte command on the SMBUS device specified by SmBusAddress.
  The 8-bit value specified by Value is written.
  Only the SMBUS slave address and SMBUS command fields of SmBusAddress are required.
  Value is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Value         The 8-bit value to write.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The parameter of Value.

**/
UINT8
EFIAPI
SmBusWriteDataByte (
  IN  UINTN          SmBusAddress,
  IN  UINT8          Value,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINT8   Byte;

  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  Byte = Value;
  InternalSmBusExec (EfiSmbusWriteByte, SmBusAddress, 1, &Byte, Status);

  return Value;
}

/**
  Executes an SMBUS read data word command.

  Executes an SMBUS read data word command on the SMBUS device specified by SmBusAddress.
  Only the SMBUS slave address and SMBUS command fields of SmBusAddress are required.
  The 16-bit value read from the SMBUS is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.
                        Device errors are a result of a transaction collision,
                        illegal command field, unclaimed cycle (host initiated),
                        or bus errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is
                        incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The byte read from the SMBUS.

**/
UINT16
EFIAPI
SmBusReadDataWord (
  IN  UINTN          SmBusAddress,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINT16  Word;

  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  InternalSmBusExec (EfiSmbusReadWord, SmBusAddress, 2, &Word, Status);

  return Word;
}

/**
  Executes an SMBUS write data word command.

  Executes an SMBUS write data word command on the SMBUS device specified by SmBusAddress.
  The 16-bit value specified by Value is written.
  Only the SMBUS slave address and SMBUS command fields of SmBusAddress are required.
  Value is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Value         The 16-bit value to write.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the SMBUS
                        command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.
                        Device errors are a result of a transaction collision,
                        illegal command field, unclaimed cycle (host initiated),
                        or bus errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct.
                        (PEC is incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The parameter of Value.

**/
UINT16
EFIAPI
SmBusWriteDataWord (
  IN  UINTN          SmBusAddress,
  IN  UINT16         Value,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINT16  Word;

  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  Word = Value;
  InternalSmBusExec (EfiSmbusWriteWord, SmBusAddress, 2, &Word, Status);

  return Value;
}

/**
  Executes an SMBUS process call command.

  Executes an SMBUS process call command on the SMBUS device specified by SmBusAddress.
  The 16-bit value specified by Value is written.
  Only the SMBUS slave address and SMBUS command fields of SmBusAddress are required.
  The 16-bit value returned by the process call command is returned.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Length in SmBusAddress is not zero, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Value         The 16-bit value to write.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.
                        Device errors are a result of a transaction collision,
                        illegal command field, unclaimed cycle (host initiated),
                        or bus errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is
                        incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The 16-bit value returned by the process call command.

**/
UINT16
EFIAPI
SmBusProcessCall (
  IN  UINTN          SmBusAddress,
  IN  UINT16         Value,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  InternalSmBusExec (EfiSmbusProcessCall, SmBusAddress, 2, &Value, Status);

  return Value;
}

/**
  Executes an SMBUS read block command.

  Executes an SMBUS read block command on the SMBUS device specified by SmBusAddress.
  Only the SMBUS slave address and SMBUS command fields of SmBusAddress are required.
  Bytes are read from the SMBUS and stored in Buffer.
  The number of bytes read is returned, and will never return a value larger than 32-bytes.
  If Status is not NULL, then the status of the executed command is returned in Status.
  It is the caller's responsibility to make sure Buffer is large enough for the total number of bytes read.
  SMBUS supports a maximum transfer size of 32 bytes, so Buffer does not need to be any larger than 32 bytes.
  If Length in SmBusAddress is not zero, then ASSERT().
  If Buffer is NULL, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  Buffer        The pointer to the buffer to store the bytes read from
                        the SMBUS.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_SUCCESS: The SMBUS command was executed.
                        RETURN_TIMEOUT: A timeout occurred while executing the SMBUS
                        command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle (host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is
                        incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The number of bytes read.

**/
UINTN
EFIAPI
SmBusReadBlock (
  IN  UINTN          SmBusAddress,
  OUT VOID           *Buffer,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  ASSERT (Buffer != NULL);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress)    == 0);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  return InternalSmBusExec (EfiSmbusReadBlock, SmBusAddress, 0x20, Buffer, Status);
}

/**
  Executes an SMBUS write block command.

  Executes an SMBUS write block command on the SMBUS device specified by SmBusAddress.
  The SMBUS slave address, SMBUS command, and SMBUS length fields of SmBusAddress are required.
  Bytes are written to the SMBUS from Buffer.
  The number of bytes written is returned, and will never return a value larger than 32-bytes.
  If Status is not NULL, then the status of the executed command is returned in Status.
  If Length in SmBusAddress is zero or greater than 32, then ASSERT().
  If Buffer is NULL, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        MBUS Command, SMBUS Data Length, and PEC.
  @param  Buffer        The pointer to the buffer to store the bytes read from
                        the SMBUS.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR:  The request was not completed because
                        a failure reflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle (host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is
                        incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The number of bytes written.

**/
UINTN
EFIAPI
SmBusWriteBlock (
  IN  UINTN          SmBusAddress,
  OUT VOID           *Buffer,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINTN  Length;

  ASSERT (Buffer != NULL);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress) >= 1);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress) <= 32);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  Length = SMBUS_LIB_LENGTH (SmBusAddress);
  return InternalSmBusExec (EfiSmbusWriteBlock, SmBusAddress, Length, Buffer, Status);
}

/**
  Executes an SMBUS block process call command.

  Executes an SMBUS block process call command on the SMBUS device specified by SmBusAddress.
  The SMBUS slave address, SMBUS command, and SMBUS length fields of SmBusAddress are required.
  Bytes are written to the SMBUS from WriteBuffer.  Bytes are then read from the SMBUS into ReadBuffer.
  If Status is not NULL, then the status of the executed command is returned in Status.
  It is the caller's responsibility to make sure ReadBuffer is large enough for the total number of bytes read.
  SMBUS supports a maximum transfer size of 32 bytes, so Buffer does not need to be any larger than 32 bytes.
  If Length in SmBusAddress is zero or greater than 32, then ASSERT().
  If WriteBuffer is NULL, then ASSERT().
  If ReadBuffer is NULL, then ASSERT().
  If any reserved bits of SmBusAddress are set, then ASSERT().

  @param  SmBusAddress  The address that encodes the SMBUS Slave Address,
                        SMBUS Command, SMBUS Data Length, and PEC.
  @param  WriteBuffer   The pointer to the buffer of bytes to write to the SMBUS.
  @param  ReadBuffer    The pointer to the buffer of bytes to read from the SMBUS.
  @param  Status        Return status for the executed command.
                        This is an optional parameter and may be NULL.
                        RETURN_TIMEOUT: A timeout occurred while executing the
                        SMBUS command.
                        RETURN_DEVICE_ERROR: The request was not completed because
                        a failure reflected in the Host Status Register bit.  Device
                        errors are a result of a transaction collision, illegal
                        command field, unclaimed cycle (host initiated), or bus
                        errors (collisions).
                        RETURN_CRC_ERROR:  The checksum is not correct. (PEC is
                        incorrect.)
                        RETURN_UNSUPPORTED:  The SMBus operation is not supported.

  @return The number of bytes written.

**/
UINTN
EFIAPI
SmBusBlockProcessCall (
  IN  UINTN          SmBusAddress,
  IN  VOID           *WriteBuffer,
  OUT VOID           *ReadBuffer,
  OUT RETURN_STATUS  *Status        OPTIONAL
  )
{
  UINTN   Length;

  ASSERT (WriteBuffer != NULL);
  ASSERT (ReadBuffer  != NULL);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress) >= 1);
  ASSERT (SMBUS_LIB_LENGTH (SmBusAddress) <= 32);
  ASSERT (SMBUS_LIB_RESERVED (SmBusAddress) == 0);

  Length = SMBUS_LIB_LENGTH (SmBusAddress);
  //
  // Assuming that ReadBuffer is large enough to save another memory copy.
  //
  ReadBuffer = CopyMem (ReadBuffer, WriteBuffer, Length);
  return InternalSmBusExec (EfiSmbusBWBRProcessCall, SmBusAddress, Length, ReadBuffer, Status);
}
