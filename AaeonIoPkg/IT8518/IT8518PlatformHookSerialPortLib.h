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
// Name:  <IT8518PlatformHookSerialPortLib.h>
//
// Description: SIO init table in PEI phase. Just initialize the serial port for debug mode.
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _IT8518PlatformHookSerialPortLib_H_
#define _IT8518PlatformHookSerialPortLib_H_

#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA IT8518SerialPortDebugDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {IT8518_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
#ifdef EFI_DEBUG
#if (IT8518_SERIAL_PORT1_PRESENT)
    {IT8518_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif
};

SIO_DEVICE_INIT_DATA IT8518SerialPortDebugInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    {IT8518_CONFIG_INDEX, 0x00, 0x23},//Super IO all device software reset or enable/disable
    {IT8518_CONFIG_DATA,  0xFE, 0x00 | SIOEN},
    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
#ifdef EFI_DEBUG
#if (IT8518_SERIAL_PORT1_PRESENT)
    // Select device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_UART1},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_ACTIVATE_VALUE},
#endif // IT8518_SERIAL_PORT1_PRESENT
#endif // #ifdef EFI_DEBUG
    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_IT8518PlatformHookSerialPortLib_H_
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
