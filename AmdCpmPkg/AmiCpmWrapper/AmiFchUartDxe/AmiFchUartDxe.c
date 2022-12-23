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

/** @file AmiFchUartDxe.c
    This file contains code to install AMI_SERIAL_PROTOCOL for FCH-UART.
    And initial serial port.

**/

#include <PiDxe.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/SerialPortLib.h>
#include <Library/PcdLib.h>
#include <Library/DevicePathLib.h>

#include <Protocol/SerialIo.h>
#include <Protocol/TerminalAmiSerial.h>

struct {
	VENDOR_DEVICE_PATH 			Guid;
	ACPI_HID_DEVICE_PATH		AcpiDp;
	UART_DEVICE_PATH			Uart;
	EFI_DEVICE_PATH_PROTOCOL	End;
} CONST STATIC mDevicePath = {
  {
    { HARDWARE_DEVICE_PATH, HW_VENDOR_DP, sizeof (VENDOR_DEVICE_PATH), 0},
    EFI_CALLER_ID_GUID // Use the drivers GUID
  },
  { { ACPI_DEVICE_PATH, ACPI_DP, sizeof(ACPI_HID_DEVICE_PATH)}, EISA_PNP_ID(0x501), FixedPcdGet8(PcdFchUartPort) },
  {
    { MESSAGING_DEVICE_PATH, MSG_UART_DP, sizeof (UART_DEVICE_PATH), 0},
    0,        // Reserved
    FixedPcdGet64 (PcdUartDefaultBaudRate),   // BaudRate
    FixedPcdGet8 (PcdUartDefaultDataBits),    // DataBits
    FixedPcdGet8 (PcdUartDefaultParity),      // Parity (N)
    FixedPcdGet8 (PcdUartDefaultStopBits)     // StopBits
  },
  { END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, sizeof (EFI_DEVICE_PATH_PROTOCOL), 0}
};

/**
    Gets base address for the Serial Port.

    @param This Pointer to AmiSerialProtocol
    @param return the base address.

    @retval VOID

    @note This API added for non-generic serial ports other than PCI serial
    ports.

**/

VOID GetBaseAddress (
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINT64              *BaseAddress
)
{

    *BaseAddress = PcdGet64 (PcdSerialRegisterBase);

    return;
}

/**
    Gives information whether it is a pci serial device, if yes,
    tells whether it is a MMIO device.

    @param This Pointer to AmiSerialProtocol
    @param BOOLEAN to fill whether it is PCI device
    @param BOOLEAN to fill whether it is MMIO access
    @param return MMIO width

    @retval VOID

    @note This API added for non-generic serial ports other than PCI serial
    ports.

**/

VOID CheckPciMmio(
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT BOOLEAN             *Pci,
    OUT BOOLEAN             *Mmio,
    OUT UINT8               *MmioWidth
)
{
    *Pci = TRUE;
    *Mmio = TRUE;
    *MmioWidth = 4;

    return;
}

/**
    This Function will give the Bus/Dev/func if it is a PCI Serial Device.

    @param This Pointer to AmiSerialProtocol
    @param Pointer to return Bus No.
    @param Pointer to return Device No.
    @param Pointer to return Function No.
    @param Pointer to return Port No.

    @retval VOID

    @note This API added for non-generic serial ports other than PCI serial
    ports.

**/

VOID GetPciLocation(
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINTN               *Bus,
    OUT UINTN               *Dev,
    OUT UINTN               *Func,
    OUT UINT8               *Port
)
{

    *Bus = 0;
    *Dev = 0;
    *Func = 0;
    *Port = mDevicePath.AcpiDp.UID;

    return;
}

/**
    Gets the IRQ number for the Serial Port.

    @param This Pointer to AmiSerialProtocol
    @param Pointer to return IRQ number.

    @retval VOID

    @note This API added for non-generic serial ports other than PCI serial
    ports.

**/

VOID GetSerialIRQ(
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINT8             *SerialIRQ
)
{

    *SerialIRQ = 0x00; // 74h/75h of C00/C01

    return;
}

/**
    Gets the Uid.

    @param This Pointer to AmiSerialProtocol
    @param Pointer to return UID.

    @retval VOID

    @note This API added for non-generic serial ports other than PCI serial
    ports.

**/

VOID GetUid (
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINT8               *Uid
)
{
    *Uid = mDevicePath.AcpiDp.UID;

    return;
}

/**
    Gets the UART Clock .

    @param This Pointer to AmiSerialProtocol
    @param Clock Pointer to return UART Clock.

    @retval VOID

    @note This API added for non-generic serial ports other than PCI serial
    ports.

**/

VOID
GetUartClock (
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINTN              *Clock
)
{

    *Clock = PcdGet32 (PcdSerialClockRate);

    return;
}

AMI_SERIAL_PROTOCOL gAmiSerialProtocolUart = {
  GetBaseAddress,
  CheckPciMmio,
  GetPciLocation,
  GetSerialIRQ,
  GetUid,
  GetUartClock
};

/**
  Initialize the state information for the Serial Io Protocol

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
SerialDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
	EFI_STATUS      Status;
	EFI_HANDLE		Handle = NULL;

	Status = SerialPortInitialize ();
	if (EFI_ERROR(Status)) {
		return Status;
	}

	// Make a new handle with Serial IO protocol and its device path on it.
	Status = gBS->InstallMultipleProtocolInterfaces (
				  &Handle,
				  &gAmiSerialProtocolGuid,  &gAmiSerialProtocolUart,
				  &gEfiDevicePathProtocolGuid,  &mDevicePath,
				  NULL
				  );
	ASSERT_EFI_ERROR (Status);

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
