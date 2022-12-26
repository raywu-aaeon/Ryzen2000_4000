//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
//<AMI_FHDR_START>
//
// Name:  <NCT6791DPlatformHookSerialPortLib.c>
//
// Description:	
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Library/PlatformHookLib.h>
#include <NCT6791DPlatformHookSerialPortLib.h>

/**
  Performs platform specific initialization required for the CPU to access
  the hardware associated with a SerialPortLib instance.  This function does
  not intiailzie the serial port hardware itself.  Instead, it initializes
  hardware devices that are required for the CPU to access the serial port
  hardware.  This function may be called more than once.

  @retval RETURN_SUCCESS       The platform specific initialization succeeded.
  @retval RETURN_DEVICE_ERROR  The platform specific initialization could not be completed.

**/
RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (
  VOID
  )
{
	//1. Decode
	UINT8 index;

	for(index=0; index<sizeof(NCT6791DSerialPortDebugDecodeTable)/sizeof(IO_DECODE_DATA); index++)
		AmiSioLibSetLpcDeviceDecoding(NULL, \
				NCT6791DSerialPortDebugDecodeTable[index].BaseAdd, \
				NCT6791DSerialPortDebugDecodeTable[index].UID, \
				NCT6791DSerialPortDebugDecodeTable[index].Type);
	//2. Enable IO
	//3. Set Serial port address
	ProgramRtRegisterTable(0x00, NCT6791DSerialPortDebugInitTable, sizeof(NCT6791DSerialPortDebugInitTable)/sizeof(SIO_DEVICE_INIT_DATA));

	return  RETURN_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************



