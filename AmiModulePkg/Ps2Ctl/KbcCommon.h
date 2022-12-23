//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file KbcCommon.h
    Keyboard Controller Common definition 

**/

#ifndef __PS2_KBC_COMMON_H__
#define __PS2_KBC_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// KBC command/status/data IO ports
//
#define KBC_CMDSTS_PORT 0x64
#define KBC_DATA_PORT   0x60

// IO Delay Port
#define IO_DELAY_PORT   0xED

//
// KBC status bits definition
//
#define KBC_OBF         0x01
#define KBC_IBF         0x02 
#define KBC_SYSFLAG     0x04 
#define KBC_CMD_DATA    0x08
#define KBC_INHIBIT_SW  0x10
#define KBC_AUX_OBF     0x20
#define KBC_TIMEOUT_ERR 0x40
#define KBC_PARITY_ERR  0x80

//
//    COMMANDS from KEYBOARD to SYSTEM
//
#define KB_ACK_COM          0xFA    // ACKNOWLEDGE command
#define KB_RSND_COM         0xFE    // RESEND command
#define KB_OVRN_COM         0xFF    // OVERRUN command
#define KB_DIAG_FAIL_COM    0xFD    // DIAGNOSTIC FAILURE command

#define KBD_ENABLE_SCANNING     0xF4    
#define KBD_DISABLE_SCANNING    0xF5   
#define KBD_RESET               0xFF    

#define rKeyboardID         0xF2
#define rMouseID            0xF2

//
// Keyboard scanner states
//
#define KBST_READY      0
#define KBST_E0         1
#define KBST_E1         2

#define BUFFER_SIZE         32
#define SYSTEM_KEYBOARD_IRQ 0x01
#define SYSTEM_MOUSE_IRQ    0x0C
#define SLAVE_IRQ           0X02

// LED inter command state
#define ED_COMMAND_ISSUED       0x01
#define ED_DATA_ISSUED          0x02

typedef struct {
    UINT8 makecode;
    UINT8 efi_scancode;
    UINT8 efi_key;
} EFI_EXTKEY;


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif  
