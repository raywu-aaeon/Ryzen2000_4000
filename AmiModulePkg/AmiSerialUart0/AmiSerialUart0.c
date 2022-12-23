/**
//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
*/


#include <Library/DebugLib.h>
#include <AmiDxeLib.h>
#include <Protocol/TerminalAmiSerial.h>
#include <Protocol/DevicePath.h>
#include <Library/PcdLib.h>
#include <Token.h>

typedef struct {
  VENDOR_DEVICE_PATH        Guid;
  ACPI_HID_DEVICE_PATH	AcpiDp;
  UART_DEVICE_PATH          Uart;
  EFI_DEVICE_PATH_PROTOCOL  End;
} SIMPLE_TEXT_OUT_DEVICE_PATH;

SIMPLE_TEXT_OUT_DEVICE_PATH mDevicePathUart0 = {
  {
    { HARDWARE_DEVICE_PATH, HW_VENDOR_DP, sizeof (VENDOR_DEVICE_PATH), 0},
    EFI_CALLER_ID_GUID // Use the drivers GUID
  },
  { { ACPI_DEVICE_PATH, ACPI_DP, sizeof(ACPI_HID_DEVICE_PATH)}, EISA_PNP_ID(0x501), 0 },
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

#if FchUart0LegacyEnableToken == 0
BOOLEAN gUart0LegacyIo   = FALSE;
#else
BOOLEAN gUart0LegacyIo   = TRUE;
#endif

#if FchUart0LegacyEnableToken == 0
	#define FCH_UART0_BASE_ADDRESS_IO 0x0
#elif FchUart0LegacyEnableToken == 1
	#define FCH_UART0_BASE_ADDRESS_IO 0x2E8
#elif FchUart0LegacyEnableToken == 2
	#define FCH_UART0_BASE_ADDRESS_IO 0x2F8
#elif FchUart0LegacyEnableToken == 3
	#define FCH_UART0_BASE_ADDRESS_IO 0x3E8
#elif FchUart0LegacyEnableToken == 4
	#define FCH_UART0_BASE_ADDRESS_IO 0x3F8
#endif
	
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

    if(!gUart0LegacyIo){
        *Clock=PCI_UART_INPUT_CLOCK;
    } else {
        *Clock = LEGACY_UART_INPUT_CLOCK;
    }
    return;
}


// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: GetBaseAddress
//
// Description:
//  Gets the base address for the Serial Port.
// 
// Input:
//  IN  AMI_SERIAL_PROTOCOL *This - Pointer to AmiSerialProtocol
//  OUT UINT64              *BaseAddress - Pointer to return Base Address  
//
// Output:
//  VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID GetBaseAddress (
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINT64              *BaseAddress
) 
{
    if ((FchRTDeviceEnableMapToken & BIT11) != 0) {
	    if(!gUart0LegacyIo){
		    *BaseAddress = FCH_UART_BASE_ADDRESS;
	    } else {
		    *BaseAddress = FCH_UART0_BASE_ADDRESS_IO;
	    }
    } else {
	    *BaseAddress = 0;
    }
    return;
}

// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: CheckPciMmio
//
// Description:
//  Gives information whether it is a pci serial device, if yes,
//  tells whether it is a MMIO device.
// 
// Input:
//  IN  AMI_SERIAL_PROTOCOL *This - Pointer to AmiSerialProtocol
//  OUT BOOLEAN             *Pci  -  BOOLEAN to fill whether it is PCI device 
//  OUT BOOLEAN             *Mmio - BOOLEAN to fill whether it is MMIO access
//
// Output:
//  VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID CheckPciMmio(
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT BOOLEAN             *Pci,
    OUT BOOLEAN             *Mmio,
    OUT UINT8               *MmioWidth
)
{
    *Pci = TRUE;
    if(!gUart0LegacyIo){
        *Mmio = TRUE;
        *MmioWidth = PCI_SERIAL_MMIO_WIDTH;
    } else {
        *Mmio = FALSE;
        *MmioWidth = 0;
    }
    return;
}

// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: GetPciLocation
//
// Description:
//  This Function will give the Bus/Dev/func if it is a PCI Serial Device.
// 
// Input:
//  IN  AMI_SERIAL_PROTOCOL *This - Pointer to AmiSerialProtocol
//  OUT UINTN               *Bus - Pointer to return Bus No.
//  OUT UINTN               *Dev - Pointer to return Device No.
//  OUT UINTN               *Func- Pointer to return Function No.
//  OUT UINT8               *Port- Pointer to return Port No.
//
// Output:
//  VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID GetPciLocation(
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINTN               *Bus,
    OUT UINTN               *Dev,
    OUT UINTN               *Func,
    OUT UINT8               *Port
)
{

    *Bus = 0x0;
    *Dev = 0x0;
    *Func = 0x0;
    *Port = 0x0;

    return;
}

// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: GetSerialIRQ
//
// Description:
//  Gets the IRQ number for the Serial Port.
// 
// Input:
//  IN  AMI_SERIAL_PROTOCOL *This - Pointer to AmiSerialProtocol
//  OUT UINT8               *SerialIRQ - Pointer to return IRQ number.
//
// Output:
//  VOID
//
// Modified:
//
// Referrals:
//
// Notes:
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>

VOID GetSerialIRQ(
    IN  AMI_SERIAL_PROTOCOL *This,
	OUT UINT8             *SerialIRQ
)
{
  *SerialIRQ = 0x04; 

    return;
}


VOID GetUid (
    IN  AMI_SERIAL_PROTOCOL *This,
    OUT UINT8               *Uid
) 
{
    *Uid = 0;
    return;
}


EFI_HANDLE	 gHandle=NULL;

AMI_SERIAL_PROTOCOL gAmiSerialProtocolUart0 = {
  GetBaseAddress,
  CheckPciMmio,
  GetPciLocation,
  GetSerialIRQ,
  GetUid,
  GetUartClock
};

// <AMI_PHDR_START>
//---------------------------------------------------------------------------
//
// Name: AmiSerialEntryPoint
//
// Description:
//  Entry point for AMI Serial Driver.It installs AMI Serial DriverBinding
//  Protocol.
//
// Input:
//  IN EFI_HANDLE ImageHandle - The image handle.
//  IN EFI_SYSTEM_TABLE *SystemTable - A pointer to the EFI system table.
//
// Output:
//  EFI_STATUS   
//
// Modified:
//
// Referrals:
//  
//
// Notes:
//
//--------------------------------------------------------------------------- 
// <AMI_PHDR_END>

EFI_STATUS EFIAPI
AmiSerialEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{

    EFI_STATUS              Status;
    //
    // Install AmiSerial protocol interfaces for the serial device.
    //
    Status = SystemTable->BootServices->InstallMultipleProtocolInterfaces (
                  &gHandle, 
                  &gAmiSerialProtocolGuid,   &gAmiSerialProtocolUart0,
                  &gEfiDevicePathProtocolGuid, &mDevicePathUart0, 
                  NULL
                  );

	ASSERT_EFI_ERROR (Status);
	return Status;
}

/**
//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2016, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
*/
