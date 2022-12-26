//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file OemDxeIoTable.c
  SIO init table in DXE phase. Any customers have to review below tables
  for themselves platform and make sure each initialization is necessary.

  @note  In all tables, only fill with necessary setting. Don't fill with default
**/
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioDxeLib.h>

///---------------------------------------------------------------------
///This table will be filled when COMs isBeforeActivate.
///---------------------------------------------------------------------
DXE_DEVICE_INIT_DATA   IT8625_DXE_COM_Mode_Init_Table[] = {
    //-----------------------------
    //| Reg8 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program COM RS485/RS232 Mode And Clock Source Registers.
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM1 RS485 mode\no effect when COM1 disabled
                        //BIT6: Enable/disable COM1 RTS# invert for rs485 mode\no effect when COM1 RS485 disabled
                        //Bits 2-1: Select the clock source for UART1. 00: 24MHz/13 01: 24MHz/12 10: Reserved 11: Reserved
    {0xF0, 0x39, 0x00}, //BIT7: Enable/disable COM2 RS485 mode\no effect when COM2 disabled
                        //BIT6: Enable/disable COM2 RTS# invert for rs485 mode\no effect when COM2 RS485 disabled
                        //Bits 2-1: Select the clock source for UART2. 00: 24MHz/13 01: 24MHz/12 10: Reserved 11: Reserved
};

///---------------------------------------------------------------------
///This table will be filled when GPIO isBeforeActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program Global Configuration Registers.
    //These registers ask enter LDN== first.
    //{0x60,0x00, (UINT8)((IO1B+0x10) >> 8)},     //SMI# Normal Run Access Base Address MSB Register
    //{0x61,0x00, (UINT8)((IO1B+0x10) & 0xFF)},   //SMI# Normal Run Access Base Address LSB Register
    {0x62,0x00, (UINT8)(IO1B >> 8)},            //Simple I/O Base Address MSB Register
    {0x63,0x00, (UINT8)(IO1B & 0xFF)},          //Simple I/O Base Address LSB Register
    //...
}; //DXE_GPIO_Init_Table_After_Active
///---------------------------------------------------------------------
///The GPIO after active init table count.
///---------------------------------------------------------------------
UINT8 DXE_GPIO_Init_Table_After_Active_Count = sizeof(DXE_GPIO_Init_Table_After_Active)/sizeof(SIO_DEVICE_INIT_DATA);

///---------------------------------------------------------------------
///This table will be filled when ENV isBeforeActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_ENV_Init_Table_Before_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    {0xF0,0x00, 0x00},  //CRF0=0x00
}; //DXE_ENV_Init_Table_Before_Active
///---------------------------------------------------------------------
///The HWM before active init table count.
///---------------------------------------------------------------------
UINT8 DXE_ENV_Init_Table_Before_Active_Count = sizeof(DXE_ENV_Init_Table_Before_Active)/sizeof(SIO_DEVICE_INIT_DATA);

///---------------------------------------------------------------------
///This table will be filled when HWM isAfterActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    // Program Global Configuration Registers.
// >> AAEON_OVERRIDE Porting from DXE to PEI
//#if (IT8625_PECI)
//    //Programming PECI
//    {0x0A, 0xCF, 0x20},// 0Ah[5-4]=10
//    {0x8E, 0x00, 0x00},// 8Eh=00
//    {0x88, 0x00, 0xFF},// 88h=FF   
//    //TMPIN Source Selection.
//    {0x06, 0x9F, 0x40},// Bank2
//    {0x1D, 0xF0, 0x00},// 1Dh[3-0](TMPIN1)
//    {0x1D, 0x0F, 0x00},// 1Dh[7-4](TMPIN2)
//    {0x1E, 0xF0, 0x00},// 1Eh[3-0](TMPIN3)
//    {0x1E, 0x0F, 0x00},// 1Eh[7-4](TMPIN4)
//    {0x1F, 0xF0, 0x00},// 1Fh[3-0](TMPIN5)
//    {0x1F, 0x0F, 0x00},// 1Fh[7-4](TMPIN6)
//    //Thermal Diode Zero Degree Adjust.
//    {0x06, 0x9F, 0x00},// Bank1
//    {0x5C, 0x7F, 0x80},// 5Ch[7]=1 for enable access thermal diode zero degree adjust.
//    {0x56, 0x00, 0x00},// 56h(TMPIN1)
//    {0x57, 0x00, 0x00},// 57h(TMPIN2)
//    {0x59, 0x00, 0x00},// 59h(TMPIN3)
//    {0x5A, 0x00, 0x00},// 5Ah(TMPIN4)
//    {0x90, 0x00, 0x00},// 90h(TMPIN5)
//    {0x91, 0x00, 0x00},// 91h(TMPIN6)
//    {0x5C, 0x7F, 0x00},// 5Ch[7]=0 for disable access thermal diode zero degree adjust.
//#endif        
// << AAEON_OVERRIDE Porting from DXE to PEI
    //------------------------------------------------------------------
    // >>ITE Workaround for early I/O initialization sequence start
    // Base on IT8625E_09_13_15_16_17_18_56_51_69BIOS_APNoteV19.pdf, Doc No.: ITEU3-AN-13019
    //------------------------------------------------------------------
    #if (IT8625_PECI)
    {0x0A,  0xC3,  0x24}, //Index[0A]=Bit[2]=1b;Bit[3]=0b; Bit[5:4]=1;0b
    {0x89,  0x00,  0x30}, //Index[89]=30h
    {0x8A,  0x00,  0x01}, //Index[8A]=01h 
    {0x8B,  0x00,  0x02}, //Index[8B]=02h
    {0x8C,  0x00,  0x01}, //Index[8C]=01h
    {0x8E,  0x00,  0xE0}, //Index[8E]=E0h --> auto start
    #endif  // IT8625_PECI
    //------------------------------------------------------------------
    //<<ITE Workaround for early I/O initialization sequence end
    //------------------------------------------------------------------
    
// >> AAEON_OVERRIDE Porting from DXE to PEI
//    {0x0B,  0xF7,  0x00 | FAN_TAC6 << 3}, //BIT3: FAN_TAC6 Enable 
//    {0x0C,  0xCF,  0x00 | FAN_TAC5 << 5 | FAN_TAC4 << 4}, //BIT5~4: FAN_TAC5-4 Enable 
//    {0x13,  0x8F,  0x00 | FAN_TAC3 << 6 | FAN_TAC2 << 5 | FAN_TAC1 << 4}, //BIT6~4: FAN_TAC3-1 Enable 
//    {0x50,  0x00,  0xFF}, //Enable Vin0 - 7
//    {0x51,  0x00,  0x00 | (IT8625_TEMP_RESISTOR_MODE_3_ENABLE << 5) //TMP 1-3 Set to Thermal Resistor
//                        | (IT8625_TEMP_RESISTOR_MODE_2_ENABLE << 4) //Thermal Diode
//                        | (IT8625_TEMP_RESISTOR_MODE_1_ENABLE << 3)
//                        | (IT8625_TEMP_DIODE_MODE_3_ENABLE << 2)
//                        | (IT8625_TEMP_DIODE_MODE_2_ENABLE << 1)
//                        | IT8625_TEMP_DIODE_MODE_1_ENABLE},
//    //Hardware Monitor Startup!
//    {0x00, 0xBE, 0x41},  //BIT6: Update VBAT Voltage Reading
//                         //BIT0: Enable the startup of monitoring operations
// << AAEON_OVERRIDE Porting from DXE to PEI
    {0x00,  0xFF,  0x40}, //Index[00] Update VBAT Voltage Reading (Just for avoid compile error when above IT8625_PECI token disabled)

}; // DXE_HWM_Init_Table_After_Active
///---------------------------------------------------------------------
///The HWM after active init table count.
///---------------------------------------------------------------------
UINT8 DXE_HWM_Init_Table_After_Active_Count = sizeof(DXE_HWM_Init_Table_After_Active)/sizeof(SIO_DEVICE_INIT_DATA);

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
