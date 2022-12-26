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
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:    NCT6791DDxeIoTable.h
//
// Description: 
//  SIO init table in DXE phase. Any customers have to review below tables 
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//*************************************************************************
#ifndef _DXEIoTable_H
#define _DXEIoTable_H
#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioDxeLib.h>
//<AMI_THDR_START>
//-------------------------------------------------------------------------
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
//-------------------------------------------------------------------------
//<AMI_THDR_END>

// >> 2015/03/27 Eric Remove
//DXE_DEVICE_INIT_DATA   NCT6791D_DXE_COM_Mode_Init_Table[] = {
//    // -----------------------------
//    //| Reg8 | AndData8  | OrData8  |
//    // -----------------------------
//    // OEM_TODO: Base on OEM board.
//    // Program COM RS485/RS232 Mode Registers.
//    {0xF2, 0x3F, (NCT6791D_COM1_RS485_Mode<<7) | (NCT6791D_COM1_RS485_RTS_INV << 6)},	//make no effect when com1 disabled
//    {0xF2, 0x3F, (NCT6791D_COM2_RS485_Mode<<7) | (NCT6791D_COM2_RS485_RTS_INV << 6)},	//make no effect when com2 disabled
//    // Program COM Clock Source Registers.
//    {0xF0, 0xFC, NCT6791D_SERIAL_PORT1_Clock_Value},	//make no effect when com1 disabled
//    {0xF0, 0xFC, NCT6791D_SERIAL_PORT2_Clock_Value},	//make no effect when com2 disabled
//
//};
// << 2015/03/27 Eric Remove
//-------------------------------------------------------------------------
// GPIO registers init table.
//-------------------------------------------------------------------------
// Define a table for init LDN8 after active.
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
    //OEM_TODO: Base on OEM board.
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_GPIO2}, //Select GPIO, WDT1(LDN8)
    {0x60,0x00, (UINT8)(IO1B >> 8)},    //GPIO  Interface  I/O  base address MSB register
    {0x61,0x00, (UINT8)(IO1B & 0xFF)},  //GPIO  Interface  I/O  base address LSB register
    //-------------------------------------------------------------------------
    // GPIO registers init table.
    //-------------------------------------------------------------------------
    /*
    #if NCT6791D_GPIO1_PORT_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_GPIO1}, //Select GPIO(LDN7)
    //...
    //..
    //.
    #endif //NCT6791D_GPIO1_PORT_PRESENT
    #if NCT6791D_GPIO2_PORT_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_GPIO2}, //Select GPIO, WDT1(LDN8)
    //...
    //..
    //.
    #endif //NCT6791D_GPIO2_PORT_PRESENT
    #if NCT6791D_GPIO3_PORT_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_GPIO3}, //Select GPIO(LDN9)
    //...
    //..
    //.
    #endif //NCT6791D_GPIO3_PORT_PRESENT
    #if NCT6791D_GPIO4_PORT_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_GPIO4}, //Select GPIO(LDNF)
    //...
    //..
    //.
    #endif //NCT6791D_GPIO4_PORT_PRESENT
    //-------------------------------------------------------------------------
    // ACPI registers init table.
    //-------------------------------------------------------------------------
    #if NCT6791D_ACPI_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_ACPI}, //Select ACPI
    //...
    //..
    //.
    #endif 
    //-------------------------------------------------------------------------
    // WDT2 registers init table.
    //-------------------------------------------------------------------------
    #if NCT6791D_WDT2_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_WDT2}, //Select WDT2
    //...
    //..
    //.
    #endif 
    //-------------------------------------------------------------------------
    // PORT80, IR registers init table.
    //-------------------------------------------------------------------------
    #if NCT6791D_P80_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_P80}, //Select PORT80, IR
    //...
    //..
    //.
    #endif 
    //-------------------------------------------------------------------------
    // DEEP SLEEP registers init table.
    //-------------------------------------------------------------------------
    #if NCT6791D_DSLP_PRESENT
    {NCT6791D_LDN_SEL_REGISTER,0x00, NCT6791D_LDN_DSLP}, //Select DEEP SLEEP
    //...
    //..
    //.
    #endif 
    */
};//DXE_GPIO_Init_Table_After_Active
#if NCT6791D_HWM_PRESENT
//----------------------------------------------------------------------------------------------
// ENV registers need init BeforeActivate, !!! BeforeActivate
//----------------------------------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_ENV_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  | 
    // -----------------------------
    {0xF0,0x00, 0x00},  //CRF0=0x00
}; //DXE_ENV_Init_Table_Before_Active
//-------------------------------------------------------------------------
// HWM registers need init AfterActivate. !!!AfterActivate
//-------------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
    // ----------------
    //|  Reg8 | Data8  |
    // ----------------
    //OEM_TODO: Base on OEM board.
    //Bank Select,bank 0
    {0x4E,0xF0, 0x00},
    {0x04,0xFE, 0x01},//SYSFANOUT Output Mode Selection,DC output(Default)
    {0x00,0x00, 0x04},//SYSFANOUT PWM Output Frequency Configuration Register 
    {0x02,0x00, 0x04},//CPUFANOUT PWM Output Frequency Configuration Register 
    {0x10,0x00, 0x04},//AUXFANOUT0 PWM Output Frequency Configuration Register 
    {0x12,0x00, 0x04},//AUXFANOUT1 PWM Output Frequency Configuration Register 
    {0x14,0x00, 0x04},//AUXFANOUT2 PWM Output Frequency Configuration Register 
    //SMI mask
    {0x43,0x00, 0xFF},
    {0x44,0x00, 0xFF},
    {0x46,0x00, 0x1E},
    //SMI/OVT setting
    {0x18,0xAE, 0x40},//OVT# Configuration,Enable/Disable SMIOVT1#,mode select
    {0x4C,0x93, 0x00},//SMI/OVT Control,Enable/Disable SMIOVT2,3, SMIOVT2~6 mode select
    //SMI/OVT setting
    {0x18,0xAE, 0x40},//OVT# Configuration,Enable/Disable SMIOVT1#,mode select
    {0x4C,0x93, 0x00},//SMI/OVT Control,Enable/Disable SMIOVT2,3, SMIOVT2~6 mode select
    //voltage limit setting
    //    {0x2b,0x00, 0x7F},//CPUVCORE High Limit 
    //    {0x2c,0x00, 0x00},//CPUVCORE Low Limit
    //    {0x2d,0x00, 0x7F},//VIN0 High Limit 
    //    {0x2e,0x00, 0x00},//VIN0 Low Limit 
    //    {0x2f,0x00, 0x7F},//AVCC High Limit  
    //    {0x30,0x00, 0x00},//AVCC Low Limit
    //    {0x31,0x00, 0x7F},//3VCC High Limit  
    //    {0x32,0x00, 0x00},//3VCC Low Limit  
    //    {0x33,0x00, 0x7F},//VIN1 High Limit  
    //    {0x34,0x00, 0x00},//VIN1 Low Limit  
    //    {0x35,0x00, 0x7F},//VIN8 High Limit  
    //    {0x36,0x00, 0x00},//VIN8 Low Limit  
    //    {0x37,0x00, 0x7F},//VIN4 High Limit  
    //    {0x38,0x00, 0x00},//VIN4 Low Limit  
    //    {0x39,0x00, 0x7F},//SMIOVT1 temperature sensor High Limit    
    //    {0x3A,0x00, 0x00},//SMIOVT1 temperature sensor Hysteresis Limit    
    {0x4D,0x00, 0x55},//FAN IN/OUT Control
    {0x50,0xFC, 0x05},//FAN IN/OUT Control    
    //VBAT Monitor Control,and AUXTIN/CPUTIN Sensor type selection
    {0x5D,0xfC, 0x01 |(AUXTIN3_SENSOR<<6)|(AUXTIN2_SENSOR<<5)|(AUXTIN1_SENSOR<<4)\
                |(AUXTIN0_SENSOR<<3)|(CPUTIN_SENSOR<<2)|(SYSTIN_SENSOR<<1)|EN_VBAT_MNT},    
    
    //    {0x5E,0x81, 0x7E},//Enable AUXTIN/CPUTIN Current Mode
    {0xAE,0xFC, 0x03},//PECI Temperature Reading Enable for SMIOVT and SMART FAN Control 
    
    //Bank Select,bank 7
    {0x4E,0xF0, 0x07},
    {0x01,0x78, (PECI_EN<<7)|(IS_PECI30<<2)|(MANUAL_EN<<1)|ROUTINE_EN},//PECI Enable Function
    //Set PECI Agent Config
    {0x03, 0xFF, PECI_AGENT_CFG},
    //Tbase for PECI
    {0x09,0x00, TBASE0},
    {0x0A,0x00, TBASE1},
    
    {0x4E,0xF0, 0x00}, //index4Eh bit[3-0] select bank number.
    {0x40,0x44, 0x03},// Configuration Register,Enable SMI# and Start
};
#endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif //_DXEIoTable_H
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************




