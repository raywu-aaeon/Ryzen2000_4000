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
// Name:  <W83627DHGDxeIoTable.h>
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
//RayWu, REMOVE 2015/08/07 >>
//DXE_DEVICE_INIT_DATA   W83627DHG_DXE_COM_Mode_Init_Table[] = {
//    // -----------------------------
//    //| Reg8 | AndData8  | OrData8  |
//    // -----------------------------
//    // OEM_TODO: Base on OEM board.
//    // Program COM Clock Source Registers.
//    {0xF0, 0xFC, W83627DHG_SERIAL_PORT1_Clock_Value},	//make no effect when com1 disabled
//    {0xF0, 0xFC, W83627DHG_SERIAL_PORT2_Clock_Value},	//make no effect when com2 disabled
//    {0xF0, 0xFC, W83627DHG_SERIAL_PORT3_Clock_Value},	//make no effect when com1 disabled
//    {0xF0, 0xFC, W83627DHG_SERIAL_PORT4_Clock_Value},	//make no effect when com2 disabled
//    {0xF0, 0xFC, W83627DHG_SERIAL_PORT5_Clock_Value},	//make no effect when com1 disabled
//    {0xF0, 0xFC, W83627DHG_SERIAL_PORT6_Clock_Value},	//make no effect when com2 disabled
//};
//RayWu, REMOVE 2015/08/07 <<
//-------------------------------------------------------------------------
// GPIO registers need init BeforeActivate, !!! BeforeActivate
//-------------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  |
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    // Program Global Configuration Registers.
    // These registers ask enter LDN== first.
    {0x07, 0x00, 0x07},  //
    /*
    #if W83627DHG_GPIO6_PORT_PRESENT
    {W83627DHG_LDN_SEL_REGISTER,0x00, W83627DHG_LDN_GPIO6}, //Select GPIO6
    //...
    //..
    //..
    #endif 
    #if W83627DHG_WDT_PRESENT
    {W83627DHG_LDN_SEL_REGISTER,0x00, W83627DHG_LDN_WDT}, //Select WDTO# & PLED
    //...
    //..
    //..
    #endif 
    #if W83627DHG_GPIO2_PORT_PRESENT
    {W83627DHG_LDN_SEL_REGISTER,0x00, W83627DHG_LDN_GPIO2}, //Select GPIO2, GPIO3, GPIO4, GPIO5
    //...
    //..
    //..
    #endif 
    #if W83627DHG_ACPI_PRESENT
    {W83627DHG_LDN_SEL_REGISTER,0x00, W83627DHG_LDN_ACPI}, //Select ACPI
    //...
    //..
    //..
    #endif 
    #if W83627DHG_PECI_PRESENT
    {W83627DHG_LDN_SEL_REGISTER,0x00, W83627DHG_LDN_PECI}, //Select PECI, SST
    //...
    //..
    //..
    #endif 
    */
}; //DXE_GPIO_Init_Table_After_Active

#if W83627DHG_HWM_PRESENT
//-------------------------------------------------------------------------
// HWM registers need init AfterActivate. !!!AfterActivate
//-------------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
//--------------------------------------------------------------------
//Before the EC monitoring function can be implemented, the steps below should be followed:
//1.  Set the Limits.
//2.  Set the interrupt Mask
//3.  Set the Enable bits.
// -----------------------------
//| Reg16 | AndData8  | OrData8  |
// -----------------------------
// OEM_TODO: Base on OEM board.
    //Smbus slave address,which needed by using smbus access
    //{0x48,0x80, 0x2d},
    //1,Basic Setting(Fan PWM/DC,Sensor Type)
    //Bank Select,bank 0
    {0x4E,0xF8, 0x00},
    //SYSFANOUT/CPUFANOUT setting
    {0x00,0x00, 0x04},//SYSFANOUT PWM Output Frequency Configuration Register
    {0x02,0x00, 0x04},//CPUFANOUT PWM Output Frequency Configuration Register
    {0x04,0xFC, (CPUFANOUT_SEL <<1) | SYSFANOUT_SEL },//CPUFANOUT/SYSFANOUT Output Mode
    //temperature sensor type selection
    {0x5D,0xF1, (AUXTIN_SENSOR_TYPE << 3) | (CPUTIN_SENSOR_TYPE << 2) | (SYSTIN_SENSOR_TYPE << 1)},
    //2,Event Mask(SMI/Beep/OVT#) setting:
    /*
    //SMI/OVT setting
    {0x18,0xAF, 0x40},//OVT# Configuration,Enable/Disable SMIOVT1#,mode select
    //SMI mask setting
    {0x43,0x00, 0xFF},
    {0x44,0x3C, 0xFF},
    {0x46,0x7F, 0x00},
    //beep setting
    {0x56,0x00, 0xFF},//enable cpucore,vin0,avcc,5vcc,sys temp,cpu temp,sys fan,cpu fan beep
    {0x57,0x6C, 0x93},//enable vin1,vin2,caseopen beep
    //Bank Select,bank 4
    {0x4E,0xF8, 0x04},
    {0x51,0xfc, 0x03},//SMI# Mask for vbat,5vsb
    {0x53,0xfc, 0x03},//enable vbat,5vsb beep
    */
    //3,Limit Setting(Voltage/Temperature/FanSpeed)
    //voltage limit setting
    //Bank Select,bank 0
    //{0x4E,0xF8, 0x00},
    //{0x2b,0x00, 0x7F},//CPUVCORE High Limit
    //{0x2c,0x00, 0x00},//CPUVCORE Low Limit
    //{0x2d,0x00, 0x7F},//VIN0 High Limit
    //{0x2e,0x00, 0x00},//VIN0 Low Limit
    //{0x2f,0x00, 0x7F},//AVCC High Limit
    //{0x30,0x00, 0x00},//AVCC Low Limit
    //{0x31,0x00, 0x7F},//5VCC High Limit
    //{0x32,0x00, 0x00},//5VCC Low Limit
    //{0x33,0x00, 0x7F},//VIN1 High Limit
    //{0x34,0x00, 0x00},//VIN1 Low Limit
    //{0x35,0x00, 0x7F},//VIN2 High Limit
    //{0x36,0x00, 0x00},//VIN2 Low Limit
    //{0x39,0x00, 0x7F},//SMIOVT1 temperature sensor High Limit
    //{0x3A,0x00, 0x00},//SMIOVT1 temperature sensor Hysteresis Limit
    //{0x3B,0x00, 0x7F},//System fan count Limit
    //{0x3C,0x00, 0x00},//Cpu fan count Limit
    //Bank Select,bank 5
    //{0x4E,0xF8, 0x05},
    //{0x54,0x00, 0xFF},//5VSB High Limit
    //{0x55,0x00, 0x00},//5VSB Low Limit
    //{0x56,0x00, 0xFF},//VBAT High Limit
    //{0x57,0x00, 0x00},//VBAT Low Limit
    //4,Enable Bit Set:
    //Bank Select,bank 0
    {0x4E,0xF8, 0x00},
    //Enable Vbat Monitor
    {0x5D,0xFE, 0x01},
    //Enable Critical temperature protection
    //{0x5E,0x00, 0x04},
    //5,Other Setting,if you needed:
    //Bank Select,bank 1, if CPUTIN sensor exist
    {0x4E,0xF8, 0x01},
    //{0x52,0xFE, 0x00},//monitor CPUTIN
    //{0x53,0x00, 0x4b},//CPUTIN temperature sensor Hysteresis Limit
    //{0x54,0x7F, 0x00},//CPUTIN temperature sensor Hysteresis Limit
    //{0x55,0x00, 0x50},//CPUTIN Temperature Source Over-temperature (High Byte)
    //{0x56,0x7F, 0x00},//CPUTIN Temperature Source Over-temperature (Low Byte)
    //Bank Select,bank 4,if SYSTIN/CPUTIN sensor exist
    {0x4E,0xF8, 0x04},
    {0x54,0x00, SYSTIN_OFFSET},//SYSTIN Temperature Sensor Offset
    {0x55,0x00, CPUTIN_OFFSET},//CPUTIN Temperature Sensor Offset
    {0x56,0x00, AUXTIN_OFFSET},//AUXTIN Temperature Sensor Offset
    //6,Start:
    //start monitor
    {0x4E,0xF8, 0x00},
    {0x40,0xFC, 0x03},// Configuration Register,Enable SMI# and Start
}; // DXE_HWM_Init_Table_After_Active
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
