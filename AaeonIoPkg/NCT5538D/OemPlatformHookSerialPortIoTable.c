//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file OemPlatformHookSerialPortIoTable.c
  SIO init table in PEI phase. Just initialize the serial port for debug mode.
**/
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioPeiLib.h>

///---------------------------------------------------------------------
///Decode table for debug serial port.
///---------------------------------------------------------------------
IO_DECODE_DATA NCT5538DSerialPortDebugDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {NCT5538D_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
    {DEBUG_COM_PORT_ADDR, 0x01, dsUART},

};

///---------------------------------------------------------------------
///The serial port debug decode table count.
///---------------------------------------------------------------------
UINT8 NCT5538DSerialPortDebugDecodeTableCount = sizeof(NCT5538DSerialPortDebugDecodeTable)/sizeof(IO_DECODE_DATA);

///---------------------------------------------------------------------
///Init table for debug serial port.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA NCT5538DSerialPortDebugInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_CONFIG_MODE_ENTER_VALUE},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_CONFIG_MODE_ENTER_VALUE},

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------
    {NCT5538D_CONFIG_INDEX, 0x00, 0x2A},
    {NCT5538D_CONFIG_DATA,  0x7F, 0x00},

    //------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //------------------------------------------------------------------
    // Select device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, DEBUG_LDN_UART},
    // Program Base Addr
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_LO_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, (UINT8)(DEBUG_COM_PORT_ADDR & 0xFF)},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_HI_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, (UINT8)(DEBUG_COM_PORT_ADDR >> 8)},
    // Activate Device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_ACTIVATE_VALUE},

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_CONFIG_MODE_EXIT_VALUE},

};

///---------------------------------------------------------------------
///The serial port debug init table count.
///---------------------------------------------------------------------
UINT8 NCT5538DSerialPortDebugInitTableCount = sizeof(NCT5538DSerialPortDebugInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


