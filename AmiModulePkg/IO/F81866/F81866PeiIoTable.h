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
#include "token.h"
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
//RayWu, ADD 2014/09/03 >>
        {F81866_CONFIG_INDEX, 0x00, 0x26},
        {F81866_CONFIG_DATA,  0x3F, F81866_CLOCK << 6},
        {F81866_CONFIG_INDEX, 0x00, 0x27},
        //{F81866_CONFIG_DATA,  0xFE, 0x00},
        {F81866_CONFIG_DATA,  0xDE, 0 | (GPIO_DEC_RANGE << 5)},
        //F81866_UART_DEFAULT++ >>>>>
        {F81866_CONFIG_INDEX, 0x00, 0x29},
        {F81866_CONFIG_DATA,  0x0F, 0x00},
        //F81866_UART_DEFAULT++ <<<<<
        #if (F81866_SERIAL_PORT3_PRESENT)
        {F81866_CONFIG_INDEX, 0x00, 0x29},
        {F81866_CONFIG_DATA,  0xCF, (F81866_UART3_FUNC_SEL << 4)},
        #endif
        #if (F81866_SERIAL_PORT4_PRESENT)
        {F81866_CONFIG_INDEX, 0x00, 0x29},
        {F81866_CONFIG_DATA,  0x3F, (F81866_UART4_FUNC_SEL << 6)},
        #endif
        {F81866_CONFIG_INDEX, 0x00, 0x27},
        {F81866_CONFIG_DATA,  0xF3, 0x00}, //GPIO_PROG_SEL[0] = 0
        //F81866_UART_DEFAULT++ >>>>>
        {F81866_CONFIG_INDEX, 0x00, 0x28},
        {F81866_CONFIG_DATA,  0x00, 0x60}, //Set to 0x60
        //F81866_UART_DEFAULT++ <<<<<
        #if (F81866_SERIAL_PORT5_PRESENT)
        {F81866_CONFIG_INDEX, 0x00, 0x28},
        {F81866_CONFIG_DATA,  0xB3, BIT6 | (F81866_UART5_FUNC_SEL << 2)},
        #endif
        #if (F81866_SERIAL_PORT6_PRESENT)
        {F81866_CONFIG_INDEX, 0x00, 0x28},
        {F81866_CONFIG_DATA,  0xBC, BIT6 | F81866_UART6_FUNC_SEL},
        #endif
        #if (F81866_PARALLEL_PORT_PRESENT)
        {F81866_CONFIG_INDEX, 0x00, 0x28},
        {F81866_CONFIG_DATA,  0xDF, 0x00},
        //FIX_LPT_MULITIFUNCION_PIN++ >>>>>
        {F81866_CONFIG_INDEX, 0x00, 0x2B},
        {F81866_CONFIG_DATA,  0xFC, 0x00},
        //FIX_LPT_MULITIFUNCION_PIN++ <<<<<
        #endif
        {F81866_CONFIG_INDEX, 0x00, 0x27},
        {F81866_CONFIG_DATA,  0xF3, 0x04}, //GPIO_PROG_SEL[0] = 1
        {F81866_CONFIG_INDEX, 0x00, 0x28},
        {F81866_CONFIG_DATA,  0xFC, (PIN76_EN << 1) | PIN71_EN},

        {F81866_CONFIG_INDEX, 0x00, 0x29},
        {F81866_CONFIG_DATA,  0xF0, (SCL_PIN76_EN << 3) | (SDA_PIN71_EN << 2) | (SDA_PIN68_EN << 1) | SCL_PIN67_EN},
        {F81866_CONFIG_INDEX, 0x00, 0x2B},
        {F81866_CONFIG_DATA,  0x1C, (GPIO67_EN << 7) | (GPIO66_EN << 6) | (GPIO65_EN << 5) | (FANIN3_EN << 1) | FANCTRL3_EN},

        {F81866_CONFIG_INDEX, 0x00, 0x27},
        {F81866_CONFIG_DATA,  0xF3, 0x00}, //GPIO_PROG_SEL[0] = 0
        {F81866_CONFIG_INDEX, 0x00, 0x2C},
        {F81866_CONFIG_DATA,  0xE0, (GPIO04_EN << 4) | (GPIO03_EN << 3) | (GPIO02_EN << 2) | (GPIO01_EN << 1) | GPIO00_EN},

        {F81866_CONFIG_INDEX, 0x00, 0x27},
        {F81866_CONFIG_DATA,  0xF3, 0x04}, //GPIO_PROG_SEL[0] = 1
        {F81866_CONFIG_INDEX, 0x00, 0x2C},
        {F81866_CONFIG_DATA,  0x10, (GPIO17_EN << 7) | (GPIO16_EN << 6) | (GPIO15_EN << 5) | (GPIO14_EN << 4) | (GPIO13_EN << 3) | (GPIO12_EN << 2) | (GPIO11_EN << 1) | GPIO10_EN},

        {F81866_CONFIG_INDEX, 0x00, 0x27},
        {F81866_CONFIG_DATA,  0xF3, 0x08}, //GPIO_PROG_SEL[0] = 2
        {F81866_CONFIG_INDEX, 0x00, 0x2C},
        {F81866_CONFIG_DATA,  0x00, (GPIO27_EN << 7) | (GPIO26_EN << 6) | (GPIO25_EN << 5) | (GPIO24_EN << 4) | (GPIO23_EN << 3) | (GPIO22_EN << 2) | (GPIO21_EN << 1) | GPIO20_EN},

        {F81866_CONFIG_INDEX, 0x00, 0x2D},
        {F81866_CONFIG_DATA,  0xF7, 0x00}, //Disable KB/MS wakeup function
//RayWu, ADD 2014/09/03 <<
//RayWu, ADD 2014/09/13 >>
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_GPIO},
        // Program Base Addr
        {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_LO_REGISTER},
        {F81866_CONFIG_DATA,  0x00, (UINT8)(IO1B & 0xFF)},
        {F81866_CONFIG_INDEX, 0x00, F81866_BASE1_HI_REGISTER},
        {F81866_CONFIG_DATA,  0x00, (UINT8)(IO1B >> 8)},
        // Activate Device
        {F81866_CONFIG_INDEX, 0x00, F81866_ACTIVATE_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_ACTIVATE_VALUE},

//        {F81866_CONFIG_INDEX, 0x00, 0xF1},
//        {F81866_CONFIG_DATA,  0x00, GPIO0_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0xF3},
//        {F81866_CONFIG_DATA,  0x00, GPIO0_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0xF0},
//        {F81866_CONFIG_DATA,  0x00, GPIO0_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0xE1},
//        {F81866_CONFIG_DATA,  0x00, GPIO1_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0xE3},
//        {F81866_CONFIG_DATA,  0x00, GPIO1_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0xE0},
//        {F81866_CONFIG_DATA,  0x00, GPIO1_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0xD1},
//        {F81866_CONFIG_DATA,  0x00, GPIO2_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0xD3},
//        {F81866_CONFIG_DATA,  0x00, GPIO2_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0xD0},
//        {F81866_CONFIG_DATA,  0x00, GPIO2_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0xC1},
//        {F81866_CONFIG_DATA,  0x00, GPIO3_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0xC3},
//        {F81866_CONFIG_DATA,  0x00, GPIO3_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0xC0},
//        {F81866_CONFIG_DATA,  0x00, GPIO3_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0xB1},
//        {F81866_CONFIG_DATA,  0x00, GPIO4_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0xB3},
//        {F81866_CONFIG_DATA,  0x00, GPIO4_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0xB0},
//        {F81866_CONFIG_DATA,  0x00, GPIO4_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0xA1},
//        {F81866_CONFIG_DATA,  0x00, GPIO5_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0xA3},
//        {F81866_CONFIG_DATA,  0x00, GPIO5_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0xA0},
//        {F81866_CONFIG_DATA,  0x00, GPIO5_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0x91},
//        {F81866_CONFIG_DATA,  0x00, GPIO6_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0x93},
//        {F81866_CONFIG_DATA,  0x00, GPIO6_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0x90},
//        {F81866_CONFIG_DATA,  0x00, GPIO6_OE},

//        {F81866_CONFIG_INDEX, 0x00, 0x81},
//        {F81866_CONFIG_DATA,  0x00, GPIO7_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0x83},
//        {F81866_CONFIG_DATA,  0x00, GPIO7_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0x80},
//        {F81866_CONFIG_DATA,  0x00, GPIO7_OE},
//
//        {F81866_CONFIG_INDEX, 0x00, 0x89},
//        {F81866_CONFIG_DATA,  0x00, GPIO8_VAL},
//        {F81866_CONFIG_INDEX, 0x00, 0x8B},
//        {F81866_CONFIG_DATA,  0x00, GPIO8_DRV_EN},
//        {F81866_CONFIG_INDEX, 0x00, 0x88},
//        {F81866_CONFIG_DATA,  0x00, GPIO8_OE},
//RayWu, ADD 2014/09/13 <<
//RayWu, ADD 2015/04/14 >>
        // All UART default as 128 byte FIFO
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART1},
        {F81866_CONFIG_INDEX, 0x00, 0xF6},
        {F81866_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART2},
        {F81866_CONFIG_INDEX, 0x00, 0xF6},
        {F81866_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART3},
        {F81866_CONFIG_INDEX, 0x00, 0xF0},
        {F81866_CONFIG_DATA,  0xFC, ((0x01 & F81866_UART3_LEVEL_EDGE_SHARE_MODE) << 1) | F81866_UART3_IRQ_SHARE},
        {F81866_CONFIG_INDEX, 0x00, 0xF6},
        {F81866_CONFIG_DATA,  0xF4, ((0x02 & F81866_UART3_LEVEL_EDGE_SHARE_MODE) << 2) | (BIT0 + BIT1)},
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART4},
        {F81866_CONFIG_INDEX, 0x00, 0xF0},
        {F81866_CONFIG_DATA,  0xFC, ((0x01 & F81866_UART4_LEVEL_EDGE_SHARE_MODE) << 1) | F81866_UART4_IRQ_SHARE},
        {F81866_CONFIG_INDEX, 0x00, 0xF6},
        {F81866_CONFIG_DATA,  0xF4, ((0x02 & F81866_UART4_LEVEL_EDGE_SHARE_MODE) << 2) | (BIT0 + BIT1)},
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART5},
        {F81866_CONFIG_INDEX, 0x00, 0xF0},
        {F81866_CONFIG_DATA,  0xFC, ((0x01 & F81866_UART5_LEVEL_EDGE_SHARE_MODE)  << 1) | F81866_UART5_IRQ_SHARE},
        {F81866_CONFIG_INDEX, 0x00, 0xF6},
        {F81866_CONFIG_DATA,  0xF4, ((0x02 & F81866_UART5_LEVEL_EDGE_SHARE_MODE) << 2) | (BIT0 + BIT1)},
        {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
        {F81866_CONFIG_DATA,  0x00, F81866_LDN_UART6},
        {F81866_CONFIG_INDEX, 0x00, 0xF0},
        {F81866_CONFIG_DATA,  0xFC, ((0x01 & F81866_UART6_LEVEL_EDGE_SHARE_MODE)  << 1) | F81866_UART6_IRQ_SHARE},
        {F81866_CONFIG_INDEX, 0x00, 0xF6},
        {F81866_CONFIG_DATA,  0xF4, ((0x02 & F81866_UART6_LEVEL_EDGE_SHARE_MODE) << 2) | (BIT0 + BIT1)},
//RayWu, ADD 2015/04/14 <<

//RayWu, REMOVE 2014/09/03 >>
//    {F81866_CONFIG_INDEX, 0x00, 0x26},
//    {F81866_CONFIG_DATA,  0x3F, F81866_CLOCK << 6},
//    {F81866_CONFIG_INDEX, 0x00, 0x27},
//    {F81866_CONFIG_DATA,  0xFE, 0x00},
//#if (F81866_SERIAL_PORT3_PRESENT)
//    {F81866_CONFIG_INDEX, 0x00, 0x29},
//    {F81866_CONFIG_DATA,  0xCF, 0x30},
//#endif
//#if (F81866_SERIAL_PORT4_PRESENT)
//    {F81866_CONFIG_INDEX, 0x00, 0x29},
//    {F81866_CONFIG_DATA,  0x3F, 0xC0},
//#endif
//#if (F81866_SERIAL_PORT5_PRESENT)
//    {F81866_CONFIG_INDEX, 0x00, 0x28},
//    {F81866_CONFIG_DATA,  0xB3, 0x4C},
//#endif
//#if (F81866_SERIAL_PORT6_PRESENT)
//    {F81866_CONFIG_INDEX, 0x00, 0x28},
//    {F81866_CONFIG_DATA,  0xBC, 0x43},
//#endif
//#if (F81866_PARALLEL_PORT_PRESENT)
//    {F81866_CONFIG_INDEX, 0x00, 0x28},
//    {F81866_CONFIG_DATA,  0xDF, 0x00},
//#endif
//    // Enable PS/2 KB/MS Wake-up Function
//#if (F81866_KEYBOARD_PRESENT)
//    {F81866_CONFIG_INDEX, 0x00, 0x2D},
//    {F81866_CONFIG_DATA,  0xF7, 0x0F},
//#endif
//RayWu, REMOVE 2014/09/03 <<
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
    //F81866_PS2SWAP_Workaround++ >>>>>
    // Seclect device KEYBOARD
    {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_LDN_PS2K},
    {F81866_CONFIG_INDEX, 0x00, 0xFE},
    {F81866_CONFIG_DATA,  0x00, 0x03},
    //F81866_PS2SWAP_Workaround++ <<<<<

    //F81866_WDTINIT_Miles++ >>>>>
#if (F81866_WDT_PRESENT)
    {F81866_CONFIG_INDEX, 0x00, F81866_LDN_SEL_REGISTER},
    {F81866_CONFIG_DATA,  0x00, F81866_LDN_WDT},
    {F81866_CONFIG_INDEX, 0x00, 0xF5},
    {F81866_CONFIG_DATA,  0xEF, 0x11},		// 25ms pulse, sec mode 
    {F81866_CONFIG_INDEX, 0x00, 0xFA},
    {F81866_CONFIG_DATA,  0xEF, 0x01},		// WDT_CLK_SEL, 0: internal 1:external
#endif //F81866_WDT_PRESENT
    //F81866_WDTINIT_Miles++ <<<<<
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
