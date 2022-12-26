//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
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
IO_DECODE_DATA F81804SerialPortDebugDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {F81804_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
#if (DEBUG_COM_PORT_ADDR == 0x2F0 || DEBUG_COM_PORT_ADDR == 0x2E0)
    {0x2E0, 0x20, 0xFF}, // 0x2E0~0x2FF , open a IODecode section for UART5 6
#else
    {DEBUG_COM_PORT_ADDR, 0x01, dsUART},
#endif
};

///---------------------------------------------------------------------
///The serial port debug decode table count.
///---------------------------------------------------------------------
UINT8 F81804SerialPortDebugDecodeTableCount = sizeof(F81804SerialPortDebugDecodeTable)/sizeof(IO_DECODE_DATA);

///---------------------------------------------------------------------
///Init table for debug serial port.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA F81804SerialPortDebugInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {F81804_CONFIG_INDEX, 0x00, F81804_CONFIG_MODE_ENTER_VALUE},
    {F81804_CONFIG_INDEX, 0x00, F81804_CONFIG_MODE_ENTER_VALUE},

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------
    {F81804_CONFIG_INDEX, 0x00, 0x26},
    {F81804_CONFIG_DATA,  0x3F, F81804_CLOCK << 6},

    //------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //------------------------------------------------------------------
    // Select device
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, DEBUG_LDN_UART},
    // Program Base Addr
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_LO_REGISTER},
    {F81804_CONFIG_DATA,  0x00, (UINT8)(DEBUG_COM_PORT_ADDR & 0xFF)},
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_HI_REGISTER},
    {F81804_CONFIG_DATA,  0x00, (UINT8)(DEBUG_COM_PORT_ADDR >> 8)},
    // Activate Device
    {F81804_CONFIG_INDEX, 0x00, F81804_ACTIVATE_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_ACTIVATE_VALUE},

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {F81804_CONFIG_INDEX, 0x00, F81804_CONFIG_MODE_EXIT_VALUE},
};

///---------------------------------------------------------------------
///The serial port debug init table count.
///---------------------------------------------------------------------
UINT8 F81804SerialPortDebugInitTableCount = sizeof(F81804SerialPortDebugInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

