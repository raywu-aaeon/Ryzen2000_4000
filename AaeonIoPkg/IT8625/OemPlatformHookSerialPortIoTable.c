//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
IO_DECODE_DATA IT8625SerialPortDebugDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {IT8625_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
    {DEBUG_COM_PORT_ADDR, 0x01, dsUART},

};

///---------------------------------------------------------------------
///The serial port debug decode table count.
///---------------------------------------------------------------------
UINT8 IT8625SerialPortDebugDecodeTableCount = sizeof(IT8625SerialPortDebugDecodeTable)/sizeof(IO_DECODE_DATA);

///---------------------------------------------------------------------
///Init table for debug serial port.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA IT8625SerialPortDebugInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {IT8625_CONFIG_INDEX, 0x00, 0x87},
    {IT8625_CONFIG_INDEX, 0x00, 0x01},
    {IT8625_CONFIG_INDEX, 0x00, 0x55},
    #if (IT8625_CONFIG_INDEX == 0x2E)
        {IT8625_CONFIG_INDEX, 0x00, 0x55},
    #else
        {IT8625_CONFIG_INDEX, 0x00, 0xAA},
    #endif

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------
    //Clock Setting 
    {IT8625_CONFIG_INDEX, 0x00, 0x23},
    {IT8625_CONFIG_DATA,  0xF6, (IT8625_CLK_SELECT << 3) | IT8625_CLOCK},   //Bit0: CLKIN Frequence; Bit3: CLK select
    {IT8625_CONFIG_INDEX, 0x00, 0x07},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_GPIO},                           //LDN 07
    {IT8625_CONFIG_INDEX, 0x00, 0x2D},
    // >> AAEON_OVERRIDE
    //{IT8625_CONFIG_DATA,  0xF9, (IT8625_PCICLK << 2) | (IT8625_DPLL_RESET << 1)}, //Bit1: DPLL Reset Enable; Bit2: PCICLK select
    {IT8625_CONFIG_DATA,  0x05, (PIN_115_FUN_SEL << 7) | (PIN_116_FUN_SEL << 6) | (PIN_117_FUN_SEL << 5) | (PIN_2_FUN_SEL << 4) | (PIN_3_FUN_SEL << 3) | ((!FAN_TAC5) << 1)},
    // << AAEON_OVERRIDE
    {IT8625_CONFIG_INDEX, 0x00, 0x71},
    {IT8625_CONFIG_DATA,  0xF7, IT8625_CLK_IN_SELECT << 3},                 //Bit3: External CLK_IN Select.

    //------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //------------------------------------------------------------------
    // Select device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, DEBUG_LDN_UART},
    // Program Base Addr
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_LO_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(DEBUG_COM_PORT_ADDR & 0xFF)},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_HI_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(DEBUG_COM_PORT_ADDR >> 8)},
    // Activate Device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_ACTIVATE_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_ACTIVATE_VALUE},

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {IT8625_CONFIG_INDEX, 0x00, 0x02},
    {IT8625_CONFIG_DATA,  0x00, 0x02},

};

///---------------------------------------------------------------------
///The serial port debug init table count.
///---------------------------------------------------------------------
UINT8 IT8625SerialPortDebugInitTableCount = sizeof(IT8625SerialPortDebugInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
