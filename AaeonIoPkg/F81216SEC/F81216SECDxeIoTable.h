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
// Name:    F81216SECDxeIoTable.h
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

//DXE_DEVICE_INIT_DATA   F81216SEC_DXE_COM_Mode_Init_Table[] = {
//    // -----------------------------
//    //| Reg8 | AndData8  | OrData8  |
//    // -----------------------------
//    // OEM_TODO: Base on OEM board.
//    // Program COM RS485/RS232 Mode Registers
//    // Program COM RS485/RS232 Mode And Clock Source Registers.
//    {0xF0, 0x6C, (F81216SEC_COM1_RS485_Mode<<7) | (F81216SEC_COM1_RS485_RTS_INV<<4) | (F81216SEC_SERIAL_PORT1_Clock_Value)},	//make no effect when com1 disabled
//    {0xF0, 0x6C, (F81216SEC_COM2_RS485_Mode<<7) | (F81216SEC_COM2_RS485_RTS_INV<<4) | (F81216SEC_SERIAL_PORT2_Clock_Value)},	//make no effect when com2 disabled
//    {0xF0, 0x6C, (F81216SEC_COM3_RS485_Mode<<7) | (F81216SEC_COM3_RS485_RTS_INV<<4) | (F81216SEC_SERIAL_PORT3_Clock_Value)},	//make no effect when com3 disabled
//    {0xF0, 0x6C, (F81216SEC_COM4_RS485_Mode<<7) | (F81216SEC_COM4_RS485_RTS_INV<<4) | (F81216SEC_SERIAL_PORT4_Clock_Value)},	//make no effect when com4 disabled
//};


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


