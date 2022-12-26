//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
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
DXE_DEVICE_INIT_DATA   F81804_DXE_COM_Mode_Init_Table[] = {
    //-----------------------------
    //| Reg8 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program COM RS485/RS232 Mode Registers.
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM1 RS485 mode\no effect when com1 disabled
                        //BIT5: Enable/disable COM1 RTS# invert for rs485 mode\no effect when COM1 RS485 disabled
    {0xF0, 0xCF, 0x00}, //BIT4: Enable/disable COM2 RS485 mode\no effect when com2 disabled
                        //BIT5: Enable/disable COM2 RTS# invert forrs485 mode\no effect when COM2 RS485 disabled
    //Program COM Clock Source Registers.
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART1. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625
    {0xF2, 0xFC, 0x00}, //Bits 1-0: Select the clock source for UART2. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625

};

///---------------------------------------------------------------------
///This table will be filled when GPIO isBeforeActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_Before_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program Global Configuration Registers.
    //These registers ask enter LDN== first.
    {0x07, 0x00, 0x06},  //

}; //DXE_GPIO_Init_Table_Before_Active
///---------------------------------------------------------------------
///The GPIO before active init table count.
///---------------------------------------------------------------------
UINT8 DXE_GPIO_Init_Table_Before_Active_Count = sizeof(DXE_GPIO_Init_Table_Before_Active)/sizeof(SIO_DEVICE_INIT_DATA);

///---------------------------------------------------------------------
///This table will be filled when GPIO isAfterActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_After_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program Global Configuration Registers.
    //These registers ask enter LDN== first.
    {0x07, 0x00, 0x06},  //
    
}; //DXE_GPIO_Init_Table_After_Active
///---------------------------------------------------------------------
///The GPIO after active init table count.
///---------------------------------------------------------------------
UINT8 DXE_GPIO_Init_Table_After_Active_Count = sizeof(DXE_GPIO_Init_Table_After_Active)/sizeof(SIO_DEVICE_INIT_DATA);

///---------------------------------------------------------------------
///This table will be filled when PME isBeforeActivate.
///---------------------------------------------------------------------
#if F81804_PME_CONTROLLER_PRESENT
SIO_DEVICE_INIT_DATA   DXE_PME_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  |
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    {0x07, 0x00, 0x0A},

};
///---------------------------------------------------------------------
///The PME before active init table count.
///---------------------------------------------------------------------
UINT8 DXE_PME_Init_Table_Before_Active_Count = sizeof(DXE_PME_Init_Table_Before_Active)/sizeof(SIO_DEVICE_INIT_DATA);
#endif

#if F81804_HWM_PRESENT
///---------------------------------------------------------------------
///This table will be filled when HWM isAfterActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    // Configuration Setting
    //{0x6B, 0xF9, 0x00 }, //BIT2: 0: TEMP2 is connected to a thermistor.\1: TEMP2 is connected to a BJT. (default)
    //                     //BIT1: 0: TEMP1 is connected to a thermistor.\1: TEMP1 is connected to a BJT. (default)
    {0x6B, 0xF9, (F81804_T2_MODE << 2) | (F81804_T1_MODE << 1) },   
#if F81804_HWM_PECI_SUPPORT
	// PECI Setting
	{0x0A, 0xFE, 0x01 }, // PECI_EN -> 1
    {0x0C, 0x00, F81804_HWM_PECI_TCC },
#endif                      
    //Hardware Monitor Startup!
    {0x01, 0xF8, 0x03},  //BIT1: Enable startup of fan monitoring operations
                         //BIT0: Enable startup of temperature and voltage monitoring operations

}; // DXE_HWM_Init_Table_After_Active
///---------------------------------------------------------------------
///The HWM after active init table count.
///---------------------------------------------------------------------
UINT8 DXE_HWM_Init_Table_After_Active_Count = sizeof(DXE_HWM_Init_Table_After_Active)/sizeof(SIO_DEVICE_INIT_DATA);
#endif //F81804_HWM_PRESENT

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

