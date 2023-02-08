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
// Name:  <F81866PlatformHookSerialPortLib.h>
//
// Description: SIO init table in PEI phase. Just initialize the serial port for debug mode.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _F81866PlatformHookSerialPortLib_H_
#define _F81866PlatformHookSerialPortLib_H_

#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA F81866SerialPortDebugDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {F81866_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
#ifdef EFI_DEBUG
#if (F81866_SERIAL_PORT1_PRESENT)
    {F81866_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif
};

SIO_DEVICE_INIT_DATA F81866SerialPortDebugInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0x00, F81866_CONFIG_MODE_ENTER_VALUE},
    {F81866_CONFIG_INDEX, 0x00, F81866_CONFIG_MODE_ENTER_VALUE},

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0x00, 0x26},
    {F81866_CONFIG_DATA,  0x3F, F81866_CLOCK << 6},
    {F81866_CONFIG_INDEX, 0x00, 0x27},
    {F81866_CONFIG_DATA,  0xFE, 0x00},

    //------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //------------------------------------------------------------------
#ifdef EFI_DEBUG
#if (F81866_SERIAL_PORT1_PRESENT)
    // Select device
    {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART1},
    // Program Base Addr
    {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_LO_REGISTER},
    {F81866_CONFIG_DATA,  0x00, (UINT8)(F81866_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_HI_REGISTER},
    {F81866_CONFIG_DATA,  0x00, (UINT8)(F81866_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {F81866_CONFIG_INDEX, 0x00, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_ACTIVATE_VALUE},
#endif // F81866_SERIAL_PORT1_PRESENT
#endif // #ifdef EFI_DEBUG

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0x00, F81866_CONFIG_MODE_EXIT_VALUE},

};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_F81866PlatformHookSerialPortLib_H_
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
