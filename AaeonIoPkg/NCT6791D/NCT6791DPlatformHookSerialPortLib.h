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
// Name:  <NCT6791DPlatformHookSerialPortLib.h>
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
IO_DECODE_DATA NCT6791DSerialPortDebugDecodeTable[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {NCT6791D_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for DEBUG Mode
    #ifdef EFI_DEBUG
    #if (NCT6791D_SERIAL_PORT1_PRESENT)
    {NCT6791D_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
    #endif
    #endif
};

SIO_DEVICE_INIT_DATA NCT6791DSerialPortDebugInitTable[]={
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_CONFIG_MODE_ENTER_VALUE},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
    #ifdef EFI_DEBUG
    #if (NCT6791D_SERIAL_PORT1_PRESENT)
    // Select device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_UART1},
    // Program Base Addr
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_ACTIVATE_VALUE},
    #endif // NCT6791D_SERIAL_PORT1_PRESENT
    #endif // #ifdef EFI_DEBUG
    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_CONFIG_MODE_EXIT_VALUE},
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



