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
// Name:    IT8728FDxeIoTable.h
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

DXE_DEVICE_INIT_DATA   IT8728F_DXE_COM_Mode_Init_Table[] = {
    // -----------------------------
    //| Reg8 | AndData8  | OrData8  |
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    // Program COM RS485/RS232 Mode And Clock Source Registers.
    {0xF0, 0xF9, (IT8728F_SERIAL_PORT1_Clock_Value<<1)},	//make no effect when com1 disabled
    {0xF0, 0xF9, (IT8728F_SERIAL_PORT2_Clock_Value<<1)},	//make no effect when com2 disabled
    {0xF0, 0xFE, 0x00}, //No IRQ sharing under DOS. //RayWu, ADD 2014/07/28
};

#if IT8728F_GPIO_PORT_PRESENT
//-------------------------------------------------------------------------
// GPIO registers need init AfterActivate, !!! AfterActivate
//-------------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  |
    // -----------------------------
//OEM_TODO: Base on OEM board.
    {0x60,0x00, (UINT8)((IO1B+0x10) >> 8)},     //SMI# Normal Run Access Base Address MSB Register
    {0x61,0x00, (UINT8)((IO1B+0x10) & 0xFF)},   //SMI# Normal Run Access Base Address LSB Register
    {0x62,0x00, (UINT8)(IO1B >> 8)},            //Simple I/O Base Address MSB Register
    {0x63,0x00, (UINT8)(IO1B & 0xFF)},          //Simple I/O Base Address LSB Register
    {0x64,0x00, (UINT8)((IO1B+0x20) >> 8)},     //Serial Flash I/F Base Address MSB Register
    {0x65,0x00, (UINT8)((IO1B+0x20) & 0xFF)},   //Serial Flash I/F Base Address LSB Register
// Move to PEI Phase -     {0x2C, 0xFE, ( (~VIN0_7_SUPPORT >> 3) & BIT0 )} //RayWu, ADD 2014/07/28
    /*
        {0x72,0xEF, 0x00},  //CR72[4]=0,disable wdt
        {0x73,0x00, 0x38},  //Watch Dog Timer Time-Out Value (LSB) Register (Index=73h, Default=C0h)
        {0x74,0x00, 0x00},  //Watch Dog Timer Time-Out Value (MSB) Register (Index=74h, Default=00h)
        //GPIO Pin Set 1, 2, 3, 4, 5 and 6 Polarity Registers
        //(Index=B0h, B1h, B2h, B3h, B4h and B5h, Default=00h)
        {0xB0,0x00, 0x00},
        {0xB1,0x00, 0x00},
        {0xB2,0x00, 0x00},
        {0xB3,0x00, 0x00},
        {0xB4,0x00, 0x00},
        //GPIO Pin Set 1, 2, 3, 4, 5 and 6 Pin Internal Pull-up Enable Registers
        //(Index=B8h, B9h, BAh, BBh, Bch and BDh, Default=00h)
        {0xB8,0x00, 0x00},
        {0xB9,0x00, 0x00},
        {0xBA,0x00, 0x00},
        {0xBB,0x00, 0x00},
        {0xBC,0x00, 0x00},
        {0xBD,0x00, 0x00},
        //Simple I/O Set 1, 2, 3, 4 and 5 Enable Registers
        //(Index=C0h, C1h, C2h, C3h and C4h, Default=01h, 00h, 00h, 40h, and 00h)
        {0xC0,0x00, 0x01},
        {0xC1,0x00, 0x00},
        {0xC2,0x00, 0x00},
        {0xC3,0x00, 0x40},
        {0xC4,0x00, 0x00},
        //Simple I/O Set 1, 2, 3, 4 and 5 Output Enable Registers
        //(Index=C8h, C9h, CAh, CBh and CCh, Default=01h, 00h, 00h, 40h, and 00h)
        {0xC8,0x00, 0x01},
        {0xC9,0x00, 0x00},
        {0xCA,0x00, 0x00},
        {0xCB,0x00, 0x40},
        {0xCC,0x00, 0x00},
        {0xCD,0x00, 0x00},
        //Panel Button De-bounce 0 Input Pin Mapping Registers (Index=E0h, Default=00h)
        {0xE0,0x00, 0x00},
        //Panel Button De-bounce 1 Input Pin Mapping Registers (Index=E1h, Default=00h)
        {0xE1,0x00, 0x00},  //
        //IRQ External Routing 1-0 Input Pin Mapping Registers (Index=E3h-E2h, Default=00h)
        {0xE2,0x00, 0x00},  //
        {0xE3,0x00, 0x00},  //
        //IRQ External Routing 1-0 Interrupt Level Selection Register (Index=E4h, Default=00h)
        {0xE4,0x00, 0x00},  //

        {0xF0,0x00, 0x00},  //SMI# Control Register 1 (Index=F0h, Default=00h)
        {0xF1,0x00, 0x00},  //SMI# Control Register 2 (Index=F1h, Default=00h)
        {0xF2,0x00, 0x00},  //SMI# Status Register 1 (Index=F2h, Default=00h)
        {0xF3,0x00, 0x00},  //SMI# Status Register 2 (Index=F3h, Default=00h)
        {0xF4,0x00, 0x00},  //SMI# Pin Mapping Register (Index=F4h, Default=00h)
        {0xF5,0x00, 0x00},  //Hardware Monitor Thermal Output Pin Mapping Register (Index=F5h, Default=00h)
        {0xF6,0x00, 0x00},  //Hardware Monitor Alert Beep Pin Mapping Register (Index=F6h, Default=00h)
        {0xF7,0x00, 0x00},  //Keyboard Lock Pin Mapping Register (Index=F7h, Default=00h)
        {0xF8,0x00, 0x00},  //GP LED Blinking 1 Pin Mapping Register (Index=F8h, Default=00h)
        {0xF9,0x00, 0x00},  //GP LED Blinking 1 Control Register (Index=F9h, Default=00h)
        {0xFA,0x00, 0x00},  //GP LED Blinking 2 Pin Mapping Register (Index=FAh, Default=00h)
        {0xFB,0x00, 0x00},  //GP LED Blinking 2 Control Register (Index=FBh, Default=00h)
    */
}; //DXE_GPIO_Init_Table_After_Active
#endif

#if IT8728F_HWM_PRESENT
//----------------------------------------------------------------------------------------------
// ENV registers need init BeforeActivate, !!! BeforeActivate
//----------------------------------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_ENV_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  |
    // -----------------------------
    {0xF0,0x00, 0x00},  //CRF0=0x00
    {0xF1,0x00, 0xBF},  //clear status, Bit6 don't clear
//    {0xF2,0x00, 0x00},  //CRF2=0x00 //RayWu, REMOVE 2014/10/27
// 2015/08/25 Eric -    {0xF3,0x00, 0x00},  //CRF3=0x00
//    {0xF4,0x10, 0x00},  //CRF4=0x00 //RayWu, REMOVE 2014/10/27
    {0xF5,0x3F, 0x00},  //CRF5[7:6]=00
    {0xFA,0x00, 0x00},  //CRFA[3:2]=00->CRFA=0x00
    {0xFB,0xF3, 0x0C},  //CRFB[3:2]=00,write 1 to clear status
// >> 2016/11/08 Eric, Remove for AC PWR CTRL by PEI phase
//    //RayWu, ADD 2014/10/27 >>
//    {0xF2,0x20, 0x00},  //CRF2=0x00
//    {0xF4,0x30, 0x00},  //CRF4=0x00
//    //RayWu, ADD 2014/10/27 <<
// << 2016/11/08 Eric, Remove for AC PWR CTRL by PEI phase
}; //DXE_ENV_Init_Table_Before_Active
//-------------------------------------------------------------------------
// HWM registers need init AfterActivate. !!!AfterActivate
//-------------------------------------------------------------------------
// >> Move to PEI Init Phase
//SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
//    // -----------------------------
//    //| Reg16 | AndData8  | OrData8  |
//    // -----------------------------
//    // Program Global Configuration Registers.
//    //{0x50,  0x00,  0xFF},   //Enable Vin0 - 7 //RayWu, REMOVE 2014/07/28
//	{0x50,  0x00,  VIN0_7_SUPPORT}, //RayWu, ADD 2014/07/28
//    {
//        0x51,  0x00,  0x00 | (IT8728F_TEMP_SST_PECI_HTRR << 6)
//        | (IT8728F_TEMP_RESISTOR_MODE_3_ENABLE << 5)//TMP 1-3 Set to Thermal Resistor
//        | (IT8728F_TEMP_RESISTOR_MODE_2_ENABLE << 4)//Thermal Diode
//        | (IT8728F_TEMP_RESISTOR_MODE_1_ENABLE << 3)
//        | (IT8728F_TEMP_DIODE_MODE_3_ENABLE << 2)
//        | (IT8728F_TEMP_DIODE_MODE_2_ENABLE << 1)
//        | IT8728F_TEMP_DIODE_MODE_1_ENABLE
//    },
////Workaround by Applicaton Note of Ite8783F for BIOS issue about Early I/O >>
//#if    IT8728F_Secondary_Floppy
//    {0x0a,  0xBF,  0x00}, //EC register Index 0Ah bit 6 must be 0 for secondary floppy
//#else
//#if    (IT8728F_ETSHS_MODE > 1) //PECI or SST Host must set Clock to 24MHz (AN1.3)
//    {0x0a,  0x8F,  0x48 | (IT8728F_ETSHS_MODE << 4)},    //External Thermal Sensor Host Selection
//#else
//    {0x0a,  0x8F,  0x40 | (IT8728F_ETSHS_MODE << 4)},    //External Thermal Sensor Host Selection
//#endif
//#endif    //IT8728F_Secondary_Floppy
//    //{0x0B,  0x00,  0xC9}, //RayWu, REMOVE 2014/07/28
//    {0x0B,  0x3F,  0xC0}, //RayWu, ADD 2014/07/28
////Workaround by Applicaton Note of Ite8783F for BIOS issue about Early I/O <<
//    {0x0C,  0xF8,  0x07},   //Set Fan 16-bit Counter Divisor Enable
////RayWu, REMOVE 2014/07/28 >>
////    {0x13,  0x07,  0x70},   //FAN_TAC3-1 Enable
////    {0x14,  0x7F,  0x80},   //FAN_CTL Polarity active high
////RayWu, REMOVE 2014/07/28 <<
////RayWu, ADD 2014/07/28 >>
//    {0x13,  0x8F, ( (FAN_TAC_3 << 6)|(FAN_TAC_2 << 5)|(FAN_TAC_1 << 4) )},
//    {0x14,  0x7F,  (FAN_CTL_POLARITY << 7)},
////RayWu, ADD 2014/07/28 <<
//    {0x5c,  0x7F,  0x80},   //Thermal Diode Zero Degree Adjust register write enable
//    {0x4A,  0x00,  0x9C},   //Ite8783 BIOS AN Ver 1.3
////RayWu, REMOVE 2014/07/28 >>
////#if IT8728F_TEMP_DIODE_MODE_1_ENABLE
////    {0x56,  0x00,  0x56},   //Thermal Diode 1(index 56)Zero Degree Adjust Register
////#endif
////#if IT8728F_TEMP_DIODE_MODE_2_ENABLE
////    {0x57,  0x00,  0x56},   //Thermal Diode 2(index 57)Zero Degree Adjust Register
////#endif
////#if IT8728F_TEMP_DIODE_MODE_3_ENABLE
////    {0x59,  0x00,  0x56},   //Thermal Diode 3(index 59Zero Degree Adjust Register
////#endif
////RayWu, REMOVE 2014/07/28 <<
////RayWu, ADD 2014/07/28 >>
////#if IT8728F_TEMP_DIODE_MODE_1_ENABLE
//#if TEMP_ADJUST_1
//    {0x56,  0x00,  TEMP_ADJUST_1},
//#endif  // TEMP_ADJUST_1
////#endif
////#if IT8728F_TEMP_DIODE_MODE_2_ENABLE
//#if TEMP_ADJUST_2
//    {0x57,  0x00,  TEMP_ADJUST_2},
//#endif  // TEMP_ADJUST_2
////#endif
////#if IT8728F_TEMP_DIODE_MODE_3_ENABLE
//#if TEMP_ADJUST_3
//    {0x59,  0x00,  TEMP_ADJUST_3},
//#endif // TEMP_ADJUST_3
////#endif
////RayWu, ADD 2014/07/28 <<
//    {0x5c,  0x7F,  0x00},   //Thermal Diode Zero Degree Adjust register write disable
////FAN_CTL3-1 SmartGuardian Automatic Mode Register
////Bit 7   : This bit selects the PWM linear changing decreasing mode
////          0:Slow decreasing mode
////          1:Direct decreasing mode
////Bit 4-0 : Temperature internal
//    {0x65,  0x60,  0x04},   //Set FAN_CTL1 as Slow decreasing mode and Temperature interval to 4
//    {0x6D,  0x60,  0x04},   //Set FAN_CTL2 as Slow decreasing mode and Temperature interval to 4
//    {0x75,  0x60,  0x04},   //Set FAN_CTL3 as Slow decreasing mode and Temperature interval to 4
//#if    (IT8728F_ETSHS_MODE == 6)
//    {0x89,  0x00,  Host_Target_Address},  //Host Target Address
//    {0x8a,  0x00,  Host_Write_Length},    //Host Write Length
//    {0x8b,  0x00,  Host_Read_Length},     //Host Read Length
//    {0x8c,  0x00,  Host_Command },        //Command
//    {0x8e,  0x00,  0x20},                 //Auto-Start
//    {0x55,  0x7f,  0x80},                 //Temp3 Reading Source Select
//#endif
//    {0x00, 0xBE, 0x41}, //Index 00 bit 6 set to 1(Update VBAT Voltage Reading again)
//}; // DXE_HWM_Init_Table_After_Active
// << Move to PEI Init Phase
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

