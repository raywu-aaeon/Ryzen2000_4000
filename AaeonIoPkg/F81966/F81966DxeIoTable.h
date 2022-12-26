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
// Name:    F81966DxeIoTable.h
//
// Description:
//  SIO init table in DXE phase. Any customers have to review below tables
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _F81966DxeIoTable_H_
#define _F81966DxeIoTable_H_

#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioDxeLib.h>

//<AMI_THDR_START>
//----------------------------------------------------------------------
//
// Name:        DXE_XXX_Init_Table
//
// Description:
//  Table filled with SIO GPIO,PME,HWM, etc. logical devices' setting
//  For example:
//  1. GPIO will define the GPIO pin useage
//  2. PME will power management control
//  3. HWM will set temperature, fan, voltage and start control.
//
// Notes:
//
//----------------------------------------------------------------------
//<AMI_THDR_END>
DXE_DEVICE_INIT_DATA   F81966_DXE_COM_Mode_Init_Table[] = {
    //-----------------------------
    //| Reg8 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program COM RS485/RS232 Mode Registers.
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM1 RS485 mode\no effect when com1 disabled
                        //BIT5: Enable/disable COM1 RTS# invert for rs485 mode\no effect when COM1 RS485 disabled
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM2 RS485 mode\no effect when com2 disabled
                        //BIT5: Enable/disable COM2 RTS# invert forrs485 mode\no effect when COM2 RS485 disabled
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM3 RS485 mode\no effect when com3 disabled
                        //BIT5: Enable/disable COM3 RTS# invert for rs485 mode\no effect when COM3 RS485 disabled
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM4 RS485 mode\no effect when com4 disabled
                        //BIT5: Enable/disable COM4 RTS# invert for rs485 mode\no effect when COM4 RS485 disabled
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM5 RS485 mode\no effect when com5 disabled
                        //BIT5: Enable/disable COM5 RTS# invert for rs485 mode\no effect when COM5 RS485 disabled
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM6 RS485 mode\no effect when com6 disabled
                        //BIT5: Enable/disable COM6 RTS# invert for rs485 mode\no effect when COM6 RS485 disabled
    //Program COM Clock Source Registers.
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART1. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART2. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART3. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART4. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART5. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART6. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    /*
    //Program COM RS485/RS232 Mode And Clock Source Registers.
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM1 RS485 mode\no effect when COM1 disabled
                        //BIT6: Enable/disable COM1 RTS# invert for rs485 mode\no effect when COM1 RS485 disabled
                        //Bits 2-1: Select the clock source for UART1. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM2 RS485 mode\no effect when COM2 disabled
                        //BIT6: Enable/disable COM2 RTS# invert for rs485 mode\no effect when COM2 RS485 disabled
                        //Bits 2-1: Select the clock source for UART2. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM3 RS485 mode\no effect when COM3 disabled
                        //BIT6: Enable/disable COM3 RTS# invert for rs485 mode\no effect when COM3 RS485 disabled
                        //Bits 2-1: Select the clock source for UART3. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM4 RS485 mode\no effect when COM4 disabled
                        //BIT6: Enable/disable COM4 RTS# invert for rs485 mode\no effect when COM4 RS485 disabled
                        //Bits 2-1: Select the clock source for UART4. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM5 RS485 mode\no effect when COM5 disabled
                        //BIT6: Enable/disable COM5 RTS# invert for rs485 mode\no effect when COM5 RS485 disabled
                        //Bits 2-1: Select the clock source for UART5. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM6 RS485 mode\no effect when COM6 disabled
                        //BIT6: Enable/disable COM6 RTS# invert for rs485 mode\no effect when COM6 RS485 disabled
                        //Bits 2-1: Select the clock source for UART6. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    */
};

//----------------------------------------------------------------------
//GPIO registers need init BeforeActivate, !!! BeforeActivate
//----------------------------------------------------------------------
//#if F81966_GPIO_PORT_PRESENT
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_Before_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program Global Configuration Registers.
    //These registers ask enter LDN== first.
    {0x07, 0x00, 0x00},

}; //DXE_GPIO_Init_Table_Before_Active
//#endif
//-------------------------------------------------------------------------
// PME registers need init BeforeActivate, !!! BeforeActivate
//-------------------------------------------------------------------------
#if F81966_PME_CONTROLLER_PRESENT
SIO_DEVICE_INIT_DATA   DXE_PME_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  |
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    {0x07, 0x00, 0x00},

};
#endif
//----------------------------------------------------------------------
// HWM registers need init AfterActivate. !!!AfterActivate
//----------------------------------------------------------------------
#if F81966_HWM_PRESENT
SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
//RayWu, ADD 2014/12/03 >>
	{0x6B, 0xF9, (F81966_T2_MODE << 2) | (F81966_T1_MODE << 1) },
//RayWu, ADD 2014/12/03 <<
//RayWu, REMOVE 2014/12/03 >>
//    // Configuration Setting
//    {0x6B, 0xF9, 0x00 }, //BIT2: 0: TEMP2 is connected to a thermistor.\1: TEMP2 is connected to a BJT. (default)
//                         //BIT1: 0: TEMP1 is connected to a thermistor.\1: TEMP2 is connected to a BJT. (default)
//RayWu, REMOVE 2014/12/03 <<
#if F81966_HWM_PECI_SUPPORT
	// PECI Setting
	{0x0A, 0xDE, 0x21 }, //Enable PECI
    {0x0C, 0x00, F81966_HWM_PECI_TCC },
#endif
    //Hardware Monitor Startup!
    {0x01, 0xF8, 0x03},  //BIT1: Enable startup of fan monitoring operations
                         //BIT0: Enable startup of temperature and voltage monitoring operations

    //F81966_SMF_Miles++ >>>>>
	//Fan type Setting
    #if F81966_SMF_SUPPORT
    {0x94, 0xC0, (FAN3_TYPE<<4)|(FAN2_TYPE<<2)|FAN1_TYPE },
    #endif
	//F81966_SMF_Miles++ <<<<<

}; // DXE_HWM_Init_Table_After_Active
#endif //F81966_HWM_PRESENT

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_F81966DxeIoTable_H_
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
