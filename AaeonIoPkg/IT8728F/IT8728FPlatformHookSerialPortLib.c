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
// Name:  <IT8728FPlatformHookSerialPortLib.c>
//
// Description: The file initialize the serial port for PlatformHookLib.
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiPeiLib.h>
#include <Library/PlatformHookLib.h>
#include <IT8728FPlatformHookSerialPortLib.h>

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: PlatformHookSerialPortInitialize
//
// Description:
//  Performs platform specific initialization required for the CPU to access
//  the hardware associated with a SerialPortLib instance.  This function does
//  not intiailzie the serial port hardware itself.  Instead, it initializes
//  hardware devices that are required for the CPU to access the serial port
//  hardware.  This function may be called more than once.
//
// Input:  None
//
// Output: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (VOID)
{
    //1. Decode
    UINT8 index;

    for(index=0; index<sizeof(IT8728FSerialPortDebugDecodeTable)/sizeof(IO_DECODE_DATA); index++)
        AmiSioLibSetLpcDeviceDecoding(NULL, \
                                      IT8728FSerialPortDebugDecodeTable[index].BaseAdd, \
                                      IT8728FSerialPortDebugDecodeTable[index].UID, \
                                      IT8728FSerialPortDebugDecodeTable[index].Type);
    //2. Enable IO
    //3. Set Serial port address
    ProgramRtRegisterTable(0x00, IT8728FSerialPortDebugInitTable, sizeof(IT8728FSerialPortDebugInitTable)/sizeof(SIO_DEVICE_INIT_DATA));

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
