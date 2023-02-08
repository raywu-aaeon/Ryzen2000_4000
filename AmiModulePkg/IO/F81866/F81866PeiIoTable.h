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
// Name:  <F81866PeiIoTable.h>
//
// Description:
//  SIO init table in PEI phase. Any customers have to review below tables
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _F81866PeiIoTable_H_
#define _F81866PeiIoTable_H_

#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA F81866PeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {F81866_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if (F81866_SERIAL_PORT1_PRESENT)
    {F81866_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (F81866_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
#if (F81866_FLOPPY_PORT_PRESENT)
    {0x3F0, 0, dsFDC},                                  // FDC decode
#endif
#endif
    //Below decode is for SIO generic IO decode
#if defined(F81866_TOTAL_BASE_ADDRESS) && (F81866_TOTAL_BASE_ADDRESS != 0)
    {F81866_TOTAL_BASE_ADDRESS, F81866_TOTAL_LENGTH, 0xFF},
#endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    {0x3E0, 0x10, 0xFF}, // 0x3E0~0x3F0 , open a IODecode section for UART3 4
    {0x2E0, 0x20, 0xFF}, // 0x2E0~0x2FF , open a IODecode section for UART5 6
    // Add more OEM IO decode below.

};

SIO_DEVICE_INIT_DATA F81866PeiInitTable[]= {
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
#if (F81866_SERIAL_PORT3_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, 0x29},
    {F81866_CONFIG_DATA,  0xCF, 0x30},
#endif
#if (F81866_SERIAL_PORT4_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, 0x29},
    {F81866_CONFIG_DATA,  0x3F, 0xC0},
#endif
#if (F81866_SERIAL_PORT5_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, 0x28},
    {F81866_CONFIG_DATA,  0xB3, 0x4C},
#endif
#if (F81866_SERIAL_PORT6_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, 0x28},
    {F81866_CONFIG_DATA,  0xBC, 0x43},
#endif
#if (F81866_PARALLEL_PORT_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, 0x28},
    {F81866_CONFIG_DATA,  0xDF, 0x00},
#endif
    // Enable PS/2 KB/MS Wake-up Function
#if (F81866_KEYBOARD_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, 0x2D},
    {F81866_CONFIG_DATA,  0xF7, 0x0F},
#endif

    //------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //------------------------------------------------------------------
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
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
#endif
#endif

    //------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //------------------------------------------------------------------
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (F81866_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_LDN_PS2K},
    // Program Base Addr
    {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_HI_REGISTER},
    {F81866_CONFIG_DATA,  0x00, 0x00},
    {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_LO_REGISTER},
    {F81866_CONFIG_DATA,  0x00, 0x60},
    /*
        [Fintek Notes:it have no 0x62,0x63 registers]
        {F81866_CONFIG_INDEX, 0x00, F81866_BASE2_HI_REGISTER},
        {F81866_CONFIG_DATA,  0x00, 0x00},
        {F81866_CONFIG_INDEX, 0x00, F81866_BASE2_LO_REGISTER},
        {F81866_CONFIG_DATA,  0x00, 0x64},
    */
    // Program Interrupt
    {F81866_CONFIG_INDEX, 0x00, F81866_IRQ1_REGISTER},
    {F81866_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {F81866_CONFIG_INDEX, 0x00, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_LDN_PS2K},
    {F81866_CONFIG_INDEX, 0x00, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_DEACTIVATE_VALUE},
#endif //F81866_KEYBOARD_PRESENT
#if (F81866_FLOPPY_PORT_PRESENT)
    // Seclect device FLOPPY
    {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_LDN_FDC},
    // Program Base Addr
    {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_HI_REGISTER},
    {F81866_CONFIG_DATA,  0x00, 0x03},
    {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_LO_REGISTER},
    {F81866_CONFIG_DATA,  0x00, 0xF0},
    // Program Interrupt
    {F81866_CONFIG_INDEX, 0x00, F81866_IRQ1_REGISTER},
    {F81866_CONFIG_DATA,  0x00, 0x06},
    // Activate Device
    {F81866_CONFIG_INDEX, 0x00, F81866_ACTIVATE_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_ACTIVATE_VALUE},
#endif //F81866_FLOPPY_PORT_PRESENT
#endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)

    //------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {F81866_CONFIG_INDEX, 0x00, F81866_CONFIG_MODE_EXIT_VALUE},

};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_F81866PeiIoTable_H_
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
