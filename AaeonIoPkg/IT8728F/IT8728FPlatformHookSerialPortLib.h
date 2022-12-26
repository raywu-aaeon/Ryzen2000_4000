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
// Name:  <IT8728FPlatformHookSerialPortLib.h>
//
// Description: SIO init table in PEI phase. Just initialize the serial port for debug mode.
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA IT8728FSerialPortDebugDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {IT8728F_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
#ifdef EFI_DEBUG
#if (IT8728F_SERIAL_PORT1_PRESENT)
    {IT8728F_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif
};

SIO_DEVICE_INIT_DATA IT8728FSerialPortDebugInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {IT8728F_CONFIG_INDEX, 0x00, 0x87},
    {IT8728F_CONFIG_INDEX, 0x00, 0x01},
    {IT8728F_CONFIG_INDEX, 0x00, 0x55},
#if (IT8728F_CONFIG_INDEX == 0x2E)
    {IT8728F_CONFIG_INDEX, 0x00, 0x55},
#else
    {IT8728F_CONFIG_INDEX, 0x00, 0xAA},
#endif
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    // Program clock setting in global registers
    // Bit0: 0/1 for CLKIN is 48Mhz/24MHz .
    {IT8728F_CONFIG_INDEX, 0x00, 0x23},
    {IT8728F_CONFIG_DATA,  0xFE, 0x00 | IT8728F_CLOCK},
    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
#ifdef EFI_DEBUG
#if (IT8728F_SERIAL_PORT1_PRESENT)
    // Select device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_LDN_SEL_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_LDN_UART1},
    // Program Base Addr
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_LO_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_BASE1_HI_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, (UINT8)(IT8728F_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {IT8728F_CONFIG_INDEX, 0x00, IT8728F_ACTIVATE_REGISTER},
    {IT8728F_CONFIG_DATA,  0x00, IT8728F_ACTIVATE_VALUE},
#endif // IT8728F_SERIAL_PORT1_PRESENT
#endif // #ifdef EFI_DEBUG
    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {IT8728F_CONFIG_INDEX, 0x00, 0x02},
    {IT8728F_CONFIG_DATA,  0x00, 0x02},
};

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
