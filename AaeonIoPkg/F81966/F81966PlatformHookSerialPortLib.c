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
// Name:  <F81966PlatformHookSerialPortLib.c>
//
// Description: The file initialize the serial port for PlatformHookLib.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Library/AmiSioPeiLib.h>
#include "F81966PlatformHookSerialPortLib.h"

// <AMI_PHDR_START>
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
// <AMI_PHDR_END>
RETURN_STATUS
EFIAPI
PlatformHookSerialPortInitialize (VOID)
{
    //1. Decode
    UINT8 index;

    for(index=0; index<sizeof(F81966SerialPortDebugDecodeTable)/sizeof(IO_DECODE_DATA); index++)
        AmiSioLibSetLpcDeviceDecoding(NULL, \
                                      F81966SerialPortDebugDecodeTable[index].BaseAdd, \
                                      F81966SerialPortDebugDecodeTable[index].UID, \
                                      F81966SerialPortDebugDecodeTable[index].Type);
    //2. Enable IO
    //3. Set Serial port address
    ProgramRtRegisterTable(0x00, F81966SerialPortDebugInitTable, sizeof(F81966SerialPortDebugInitTable)/sizeof(SIO_DEVICE_INIT_DATA));

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
