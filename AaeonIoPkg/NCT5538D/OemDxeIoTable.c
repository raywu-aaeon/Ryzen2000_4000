//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
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
DXE_DEVICE_INIT_DATA   NCT5538D_DXE_COM_Mode_Init_Table[] = {
    //-----------------------------
    //| Reg8 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program COM RS485/RS232 Mode Registers.
    {0xF2, 0x3F, 0x00}, //BIT7: Enable/disable COM1 RS485 mode\no effect when com1 disabled
                        //BIT6: Enable/disable COM1 RTS# invert for rs485 mode\no effect when COM1 RS485 disabled
    {0xF0, 0xFC, 0x00}, //Bits 2-1: Select the clock source for UART1. 00: 24MHz/13 01: 24MHz/12 10: 24MHz 11: 24MHz/1.625

};

///---------------------------------------------------------------------
///This table will be filled when GPIO isBeforeActivate.
///---------------------------------------------------------------------
//#if NCT5538D_GPIO_PORT_PRESENT
SIO_DEVICE_INIT_DATA   DXE_GPIO_Init_Table_Before_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    //Program Global Configuration Registers.
    //These registers ask enter LDN== first.
    {0x07, 0x00, 0x00},  //
    

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
    {0x07, 0x00, 0x00},  //
    
    #if NCT5538D_GPIO1_PORT_PRESENT
    {NCT5538D_LDN_SEL_REGISTER,0x00, NCT5538D_LDN_GPIO1}, 
    //OEM_TODO: Base on OEM board.
    #endif
    #if NCT5538D_GPIO2_PORT_PRESENT
    {NCT5538D_LDN_SEL_REGISTER,0x00, NCT5538D_LDN_GPIO2}, 
    //OEM_TODO: Base on OEM board.
    {0x60,0x00, (UINT8)(IO1B >> 8)},            //GPIO Base Address MSB Register
    {0x61,0x00, (UINT8)(IO1B & 0xFF)},          //GPIO Base Address LSB Register    
    #endif
    #if NCT5538D_GPIO3_PORT_PRESENT
    {NCT5538D_LDN_SEL_REGISTER,0x00, NCT5538D_LDN_GPIO3}, 
    //OEM_TODO: Base on OEM board.
    #endif
    #if NCT5538D_GPIO_SELECTION_PRESENT
    {NCT5538D_LDN_SEL_REGISTER,0x00, NCT5538D_LDN_GPIO_SELECT}, 
    //OEM_TODO: Base on OEM board.
    #endif
    #if NCT5538D_WDT_PRESENT
    {NCT5538D_LDN_SEL_REGISTER,0x00, NCT5538D_LDN_WDT}, 
    //OEM_TODO: Base on OEM board.
    #endif
    #if NCT5538D_DSLEEP_PRESENT
    {NCT5538D_LDN_SEL_REGISTER,0x00, NCT5538D_LDN_DSLEEP}, 
    //OEM_TODO: Base on OEM board.
    #endif
}; //DXE_GPIO_Init_Table_After_Active
///---------------------------------------------------------------------
///The GPIO after active init table count.
///---------------------------------------------------------------------
UINT8 DXE_GPIO_Init_Table_After_Active_Count = sizeof(DXE_GPIO_Init_Table_After_Active)/sizeof(SIO_DEVICE_INIT_DATA);


///---------------------------------------------------------------------
///This table will be filled when PME isBeforeActivate.
///---------------------------------------------------------------------
#if NCT5538D_PME_CONTROLLER_PRESENT
SIO_DEVICE_INIT_DATA   DXE_PME_Init_Table_Before_Active[] = {
    // -----------------------------
    //| Reg16 | AndData8  | OrData8  |
    // -----------------------------
    // OEM_TODO: Base on OEM board.
    {0x07, 0x00, 0x00},

};
///---------------------------------------------------------------------
///The PME before active init table count.
///---------------------------------------------------------------------
UINT8 DXE_PME_Init_Table_Before_Active_Count = sizeof(DXE_PME_Init_Table_Before_Active)/sizeof(SIO_DEVICE_INIT_DATA);
#endif

#if NCT5538D_HWM_PRESENT
///-------------------------------------------------------------------
///This table will be filled when HWM isAfterActivate.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA   DXE_HWM_Init_Table_After_Active[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
    // Configuration Setting
        
    //Hardware Monitor Startup!
    {0x4E, 0xF0, 0x00},  //Select Bank 0;
    {0x40, 0xFE, 0x01},  //BIT1: Enable startup of monitoring operations

}; // DXE_HWM_Init_Table_After_Active
///---------------------------------------------------------------------
///The HWM after active init table count.
///---------------------------------------------------------------------
UINT8 DXE_HWM_Init_Table_After_Active_Count = sizeof(DXE_HWM_Init_Table_After_Active)/sizeof(SIO_DEVICE_INIT_DATA);
#endif //NCT5538D_HWM_PRESENT

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************


