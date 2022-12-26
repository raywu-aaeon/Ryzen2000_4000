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
// Name:  <W83627DHGPlatformHookSerialPortLib.h>
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>


IO_DECODE_DATA W83627DHGSerialPortDebugDecodeTable[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    //Below decode is for DEBUG Mode
    {W83627DHG_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
    #ifdef EFI_DEBUG
    #if (W83627DHG_SERIAL_PORT1_PRESENT)
    {W83627DHG_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART}, // COMA decode
    #endif
    #endif
};

SIO_DEVICE_INIT_DATA W83627DHGSerialPortDebugInitTable[]={
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    //AMI_TODO:
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_CONFIG_MODE_ENTER_VALUE},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
     //Clock Selection,Default clock rate 48MHz
    {W83627DHG_CONFIG_INDEX, 0x00, 0x24},
    {W83627DHG_CONFIG_DATA,  0xBF, W83627DHG_CLOCK<<6},

    //---------------------------------------------------------------------
    // Before init all logical devices, program GPIO Multi-Pin if needed.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
    #if defined(EFI_DEBUG)
    #if (W83627DHG_SERIAL_PORT1_PRESENT)
    // Select device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_UART1},
    // Program Base Addr
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_LO_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, (UINT8)(W83627DHG_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_HI_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, (UINT8)(W83627DHG_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Program IRQ
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_IRQ1_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x04},
    // Activate Device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_ACTIVATE_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_ACTIVATE_VALUE},
    #endif // W83627DHG_SERIAL_PORT1_PRESENT
    #endif // #ifdef EFI_DEBUG

    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    //AMI_TODO:
    //Exit Configuration Mode.
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_CONFIG_MODE_EXIT_VALUE},
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
