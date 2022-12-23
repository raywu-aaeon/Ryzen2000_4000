//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Ps2KbdPei.c
    PS/2 keyboard support routines in PEI

**/

#include "Token.h"
#include "Pei.h"
#include "Ppi/AmiKeyCodePpi.h"
#include "Ps2KbdPei.h"
#include "KbcCommon.h"
#include <Ppi/Stall.h>

EFI_GUID        gPeiAmikeycodeInputPpiGuid = EFI_PEI_AMI_KEYCODE_PPI_GUID;
PEI_KEYBOARD    gPeiKbd;

static EFI_PEI_STALL_PPI    *gStallPpi = NULL;
CONST EFI_PEI_SERVICES     **gPeiServices = NULL;

static EFI_PEI_PPI_DESCRIPTOR Ps2KeyboardInputPpiList = {
        (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
        &gPeiAmikeycodeInputPpiGuid,
        NULL
};

/**
 (E0EnhancedKeys, E1Seq, KeyPad_Table, KeyPadEfiCode_Table, ScancodeToEfi_table, Code_Table, code_table, ScanCode_Table)
  Above mentioned arrays are also defined in Ps2Kbd.c file. Kindly do update in this file also, if any of the arrays getting 
  removed or had any modification in future. 
  
**/
UINT8 E0EnhancedKeys [] = {0x20,0x30,0x2E};  // only mute, volume-up, down
UINT8 E1Seq[5]   = {0x1D, 0x45, 0xE1, 0x9D, 0xC5};
UINT8 KeyPad_Table[] = {
    '7','8','9','-','4','5','6','+','1','2','3','0','.'
};
UINT8 KeyPadEfiCode_Table[] = {
    EfiKeySeven, EfiKeyEight, EfiKeyNine, EfiKeyMinus,
    EfiKeyFour, EfiKeyFive, EfiKeySix, EfiKeyPlus,
    EfiKeyOne, EfiKeyTwo, EfiKeyThree,
    EfiKeyZero, EfiKeyPeriod
};
// EFI keys (UEFI Spec 2.1, Ch.28.4, Pg.1325)
UINT8 ScancodeToEfi_table[59] = { 
0, EfiKeyEsc, EfiKeyE1, EfiKeyE2, EfiKeyE3,EfiKeyE4, EfiKeyE5, EfiKeyE6,
EfiKeyE7, EfiKeyE8, EfiKeyE9, EfiKeyE10, EfiKeyE11, EfiKeyE12, EfiKeyBackSpace,
EfiKeyTab, EfiKeyD1, EfiKeyD2, EfiKeyD3, EfiKeyD4, EfiKeyD5, EfiKeyD6, EfiKeyD7,
EfiKeyD8, EfiKeyD9, EfiKeyD10, EfiKeyD11, EfiKeyD12, EfiKeyEnter,
EfiKeyCapsLock, EfiKeyC1, EfiKeyC2, EfiKeyC3, EfiKeyC4, EfiKeyC5, EfiKeyC6, EfiKeyC7,
EfiKeyC8, EfiKeyC9, EfiKeyC10, EfiKeyC11, EfiKeyE0,
EfiKeyLShift, EfiKeyD13, EfiKeyB1, EfiKeyB2, EfiKeyB3, EfiKeyB4, EfiKeyB5, EfiKeyB6,
EfiKeyB7, EfiKeyB8, EfiKeyB9, EfiKeyB10, EfiKeyRshift,
EfiKeyAsterisk, 0, EfiKeySpaceBar, 0
};
// Upper case keys
UINT8 Code_Table[59] = { 
0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 8,
9, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 13,
0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
'*', 0, ' ',0
};
// Lower case keys
UINT8 code_table[59] = { 
0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 8,
9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 13,
0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'','`',
0,'\\','z','x','c','v','b','n','m',',','.','/',0,
'*', 0, ' ', 0
};
EFI_EXTKEY ScanCode_Table[] = {
    {0x3B, EFI_SCAN_F1, EfiKeyF1},
    {0x3C, EFI_SCAN_F2, EfiKeyF2},
    {0x3D, EFI_SCAN_F3, EfiKeyF3},
    {0x3E, EFI_SCAN_F4, EfiKeyF4},
    {0x3F, EFI_SCAN_F5, EfiKeyF5},
    {0x40, EFI_SCAN_F6, EfiKeyF6},
    {0x41, EFI_SCAN_F7, EfiKeyF7},
    {0x42, EFI_SCAN_F8, EfiKeyF8},
    {0x43, EFI_SCAN_F9, EfiKeyF9},
    {0x44, EFI_SCAN_F10, EfiKeyF10},
    {0x57, EFI_SCAN_F11, EfiKeyF11},
    {0x58, EFI_SCAN_F12, EfiKeyF12},
    {0x47, EFI_SCAN_HOME, EfiKeyHome},
    {0x48, EFI_SCAN_UP, EfiKeyUpArrow},
    {0x49, EFI_SCAN_PGUP, EfiKeyPgUp},
    {0x4B, EFI_SCAN_LEFT, EfiKeyLeftArrow},
    {0x4D, EFI_SCAN_RIGHT, EfiKeyRightArrow},
    {0x4F, EFI_SCAN_END, EfiKeyEnd},
    {0x50, EFI_SCAN_DN, EfiKeyDownArrow},
    {0x51, EFI_SCAN_PGDN, EfiKeyPgDn},
    {0x52, EFI_SCAN_INS, EfiKeyIns},
    {0x53, EFI_SCAN_DEL, EfiKeyDel},
    {0xFF, 0xFF, 0xFF}  // End of table
};

/**
    Entry point for the PEI PS2 driver. Initializes and
    provides PEI AMIKeycode PPI for use. 
    
    @param    IN      EFI_FFS_FILE_HEADER       *FfsHeader
              IN      EFI_PEI_SERVICES          **PeiServices,

    @retval    EFI_STATUS

**/
EFI_STATUS
EFIAPI
Ps2KbdPeiEntryPoint (
    IN  EFI_PEI_FILE_HANDLE     FileHandle,
    IN  CONST EFI_PEI_SERVICES  **PeiServices
)
{   
    EFI_STATUS      Status;
    EFI_BOOT_MODE   BootMode;

    //
    // Check for PS2 KBD. If not present dont install KeycodePPI
    // 
    if (IoRead8(KBC_CMDSTS_PORT) == 0xFF){
        return EFI_NOT_FOUND;
    }

    Status = (**PeiServices).LocatePpi (PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, (VOID**)&gStallPpi);

    if (EFI_ERROR (Status)) { 
        return EFI_UNSUPPORTED;
    }

	gPeiServices = PeiServices;

    Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
    ASSERT_EFI_ERROR (Status);
    
    if (BootMode == BOOT_ON_S3_RESUME) {
        DEBUG (( DEBUG_INFO, " Ps2 Initilization on S3 resume \n"));
        // Send the KBC Self Test command
        Pei_Kbc_WriteCommandByte (0xAA);
        return EFI_SUCCESS;
    }
	
    //
    // Enable the Keyboard in Keyboard Controller
    //
    Pei_Kbc_WriteKeyboardControllerData(0x60,0x65);

    //
    // Clear the Existing Junk Data
    //
    Pei_Kbc_ClearOutputBuffer();


    Ps2KeyboardInputPpiList.Ppi = &gPeiKbd.AmiKeyCodePpi;
    gPeiKbd.AmiKeyCodePpi.ReadKey=Ps2PeiReadKey;
    gPeiKbd.AmiKeyCodePpi.SetLedState=Ps2PeiSetLedState;

    gPeiKbd.Ps2KeyData.KeyState.KeyToggleState = TOGGLE_STATE_VALID;
    gPeiKbd.Ps2KeyData.KeyState.KeyShiftState = SHIFT_STATE_VALID;


    //
    // Install the PPI for Ps2 Keyboard
    //
    Status = (**PeiServices).InstallPpi(PeiServices, &Ps2KeyboardInputPpiList);

    return Status;
}

/**
     Gets the keyboard data from KBC if available.
     
     @Param     IN EFI_PEI_SERVICES             **PeiServices,
                IN EFI_PEI_AMIKEYCODE_PPI       *This,
                OUT EFI_PEI_AMIKEYCODE_DATA     *KeyData

     @retval      
                EFI_NOT_READY - There was no keystroke data available.
								Current KeyData.KeyState values are updated.
                EFI_SUCCESS - KeyData is filled with the most up-to-date keypress
**/

EFI_STATUS
EFIAPI
Ps2PeiReadKey (
    IN EFI_PEI_SERVICES             **PeiServices,
    IN EFI_PEI_AMIKEYCODE_PPI       *This,
    OUT EFI_PEI_AMIKEYCODE_DATA     *KeyData
)
{
    EFI_STATUS Status;
    EFI_KEY_TOGGLE_STATE KeyToggleState=gPeiKbd.Ps2KeyData.KeyState.KeyToggleState;    
    
    Status = Processkey(&gPeiKbd.Ps2KeyData);

    if(!EFI_ERROR(Status)) {
        
        if (gPeiKbd.Ps2KeyData.Key.ScanCode == 0 && gPeiKbd.Ps2KeyData.Key.UnicodeChar == 0 && gPeiKbd.AmiKeyCodePpi.ReadKey == KBST_READY ){
            // If the Key ShiftState has valid key but KEY_STATE_EXPOSED bit not enabled, avoid copying data.
            if((gPeiKbd.Ps2KeyData.KeyState.KeyShiftState & ~SHIFT_STATE_VALID)!= 0){
                if(!(gPeiKbd.Ps2KeyData.KeyState.KeyToggleState & KEY_STATE_EXPOSED)){
                    return Status;
                }
            }
        }
        
        (*PeiServices)->CopyMem (KeyData, &gPeiKbd.Ps2KeyData, sizeof(EFI_PEI_AMIKEYCODE_DATA));
        //
        // Check the ToggleState. if changed Send Led On/Off command
        //
        if(KeyToggleState != gPeiKbd.Ps2KeyData.KeyState.KeyToggleState) {
            PeiLEDsOnOff();
        }
    }
    return Status;    
}

/**

    This routine Sets the toggle State to the Keyboard Device

    @Param       
                  IN    EFI_PEI_SERVICES          **PeiServices,
                  IN    EFI_PEI_AMIKEYCODE_PPI    *This,
                  IN    EFI_KEY_TOGGLE_STATE      KeyToggleState
                  
    @RetVal       Status

**/
EFI_STATUS 
EFIAPI
Ps2PeiSetLedState (
  IN    EFI_PEI_SERVICES        **PeiServices,
  IN    EFI_PEI_AMIKEYCODE_PPI  *This,
  IN    EFI_KEY_TOGGLE_STATE    KeyToggleState
)
{

    BOOLEAN ChgSL;
    BOOLEAN ChgCL;
    BOOLEAN ChgNL;
    
	// Check for KEY_STATE_EXPOSED bit enabled.
    if(KeyToggleState & KEY_STATE_EXPOSED){
        gPeiKbd.Ps2KeyData.KeyState.KeyToggleState |= KEY_STATE_EXPOSED;
    } else {
        gPeiKbd.Ps2KeyData.KeyState.KeyToggleState &= ~KEY_STATE_EXPOSED;
    }

    ChgSL = ((KeyToggleState & SCROLL_LOCK_ACTIVE)!=0) ^ ((gPeiKbd.Ps2KeyData.KeyState.KeyToggleState & SCROLL_LOCK_ACTIVE)!=0);
    ChgNL = ((KeyToggleState & NUM_LOCK_ACTIVE)!=0) ^ ((gPeiKbd.Ps2KeyData.KeyState.KeyToggleState & NUM_LOCK_ACTIVE)!=0);
    ChgCL = ((KeyToggleState & CAPS_LOCK_ACTIVE)!=0) ^ ((gPeiKbd.Ps2KeyData.KeyState.KeyToggleState & CAPS_LOCK_ACTIVE)!=0);

    if (ChgSL || ChgCL || ChgNL) {
        gPeiKbd.Ps2KeyData.KeyState.KeyToggleState &= ~(SCROLL_LOCK_ACTIVE | NUM_LOCK_ACTIVE | CAPS_LOCK_ACTIVE);

        if (KeyToggleState & SCROLL_LOCK_ACTIVE) gPeiKbd.Ps2KeyData.KeyState.KeyToggleState |= SCROLL_LOCK_ACTIVE;
        if (KeyToggleState & NUM_LOCK_ACTIVE) gPeiKbd.Ps2KeyData.KeyState.KeyToggleState |= NUM_LOCK_ACTIVE;
        if (KeyToggleState & CAPS_LOCK_ACTIVE) gPeiKbd.Ps2KeyData.KeyState.KeyToggleState |= CAPS_LOCK_ACTIVE;

        //
        //State Changes. Call Led on/off
        //
        PeiLEDsOnOff();
    }

    return EFI_SUCCESS;
}

/** @internal
    Send LED command and Data in the PEI phase

    @Param  VOID      

    @retval VOID
    @endinternal
**/

VOID
PeiLEDsOnOff(
)
{

    Pei_Kbc_ClearOutputBuffer();
    Pei_Kbc_WaitForInputBufferToBeFree();
    //
    // Send LED command
    //
    IoWrite8(KBC_DATA_PORT, 0xED);
    Pei_Kbc_WaitForInputBufferToBeFree();
    Pei_Kbc_ClearOutputBuffer();

    //
    // Send the Data
    //
    IoWrite8(KBC_DATA_PORT, (gPeiKbd.Ps2KeyData.KeyState.KeyToggleState & 7));

    Pei_Kbc_WaitForInputBufferToBeFree();

    return ;
}

/** @internal
    This routine clears the output buffer

    @param  VOID      

    @retval VOID
    @endinternal
**/

VOID 
Pei_Kbc_ClearOutputBuffer(
)
{
    UINT32  Count  = 50000;
    
    while(IoRead8(KBC_CMDSTS_PORT) & BIT0) {
        
        if(Count == 0) {
            //
            // 5Sec timeout
            //
            break;
        }

        //
        //Delay for 100 MicroSeconds
        //
        gStallPpi->Stall (gPeiServices, gStallPpi, 100);   
        
        IoRead8(KBC_DATA_PORT);
        --Count;
    }
   
}

/** @internal
    This routine checks the input buffer free bit and waits till
    it is set by the keyboard controller
    
    @param  VOID      

    @retval VOID
    @endinternal
**/

VOID 
Pei_Kbc_WaitForInputBufferToBeFree(
)
{
    UINT8   bStatus;
    UINT32  wCount  = 50000;

    bStatus     = (UINT8)(IoRead8(KBC_CMDSTS_PORT) & BIT1);
    while(bStatus) {

        if(wCount == 0) {
            //
            // 5Sec timeout
            //
            break;
        }

        //
        //Delay for 100 MicroSeconds
        //
        gStallPpi->Stall (gPeiServices, gStallPpi, 100);   

        bStatus = (UINT8)(IoRead8(KBC_CMDSTS_PORT) & BIT1);
        --wCount;
    }

    return;
}

/** @internal
    This routine sends the command byte to the keyboard controller
    
    @param  Command Byte      

    @retval VOID
    @endinternal
**/
VOID 
Pei_Kbc_WriteCommandByte (
    UINT8 bCmd
)
{
    Pei_Kbc_WaitForInputBufferToBeFree();
    IoWrite8(KBC_CMDSTS_PORT, bCmd);
    Pei_Kbc_WaitForInputBufferToBeFree();
    return;
}


/** @internal
    This routine writes a data byte to the keyboard controller
    by first sending a command byte first
  
    @param  VOID

    @retval VOID
    @endinternal
**/

VOID 
Pei_Kbc_WriteKeyboardControllerData (
  IN    UINT8                   bCmd, 
  IN    UINT8                   bData
)
{
    Pei_Kbc_WaitForInputBufferToBeFree();   // Wait for input buffer to be free
    Pei_Kbc_WriteCommandByte(bCmd);         // Send the command
    IoWrite8(KBC_DATA_PORT, bData);      // Write the data
    Pei_Kbc_WaitForInputBufferToBeFree();   // Wait for input buffer to be free
}


/** @internal
    Returns TRUE if the given make code belongs to the
    alphabetical symbol, otherwise returns FALSE.

    @param      data - The character to test

    @retval     True if character is letter
    @endinternal
**/

BOOLEAN
IsLetter (
    UINT8   data 
)
{
    if ((data >= 0x10 && data <= 0x19) ||   // Q...P
        (data >= 0x1E && data <= 0x26) ||   // A...L
        (data >= 0x2C && data <= 0x32)) {   // Z...M
        return TRUE;
    }
    return FALSE;
}

/** @internal
    Checks for enhanced keys mute, volume and returns the status.

    @param      KeyCode

    @retval     True if enhanced key false otherwise
    @endinternal
**/

BOOLEAN 
IsEnhancedKey( 
    UINT8 data
)
{
    UINTN    i;

    data &= 0x7F;    // reset MSB
    for ( i = 0; i < sizeof(E0EnhancedKeys); i++) {
        if ( data == E0EnhancedKeys[i]) {
            return    TRUE;
        }
    }
    return    FALSE;
}

/** @internal
    Reset State machine

    @param      VOID 

    @retval     VOID
    @endinternal

**/

VOID
ResetStateMachine(
)
{
    gPeiKbd.ScannerState = KBST_READY;
    gPeiKbd.ScannerCount = 0;    
    return;
}

/** @internal
    PS2 keyboard keys processor. It gets the key from KBC output buffer and calls
    Handles the Keyboard Data

    @param    *KeyData - KeyData Output Pointer 

    @retval    Status 
    @endinternal
**/

EFI_STATUS
Processkey(
    EFI_PEI_AMIKEYCODE_DATA *KeyData
)
{

    EFI_STATUS Status;
    UINT8 Data;
    
    if(IoRead8(KBC_CMDSTS_PORT) & 0x01) {
         Data = IoRead8(KBC_DATA_PORT);
    } else  {
        // No keystroke data available, updating the Current KeyData.KeyState values.
        KeyData->KeyState.KeyShiftState |= SHIFT_STATE_VALID;
        KeyData->KeyState.KeyToggleState |= TOGGLE_STATE_VALID;
        return EFI_NOT_READY;
    }

    //
    // PS2 keyboard could send one, two, four or six bytes in a row.
    // ScannerState is ST_READY if it is the first byte
    //
    if (gPeiKbd.ScannerState == KBST_READY) {
        switch (Data) {
            case 0xE0:
                gPeiKbd.ScannerState = KBST_E0;
                break;
            case 0xE1:
                gPeiKbd.ScannerState = KBST_E1;
                break;
            default:
               return ProcessByte(KeyData, Data, FALSE);
        }
    } else {
        // Multi-byte sequence is being processed
        if (gPeiKbd.ScannerState == KBST_E1)   // Processing E1 state
        {
            if (Data != E1Seq[gPeiKbd.ScannerCount]) {    // Wrong byte in a sequence
                gPeiKbd.ScannerState = KBST_READY;
                return EFI_NOT_READY;
            }

            //
            // E1 sequence data is correct, proceed
            //
            //PAUSE Key

            if  (gPeiKbd.ScannerCount == 2) { // The ONLY 2-key sequence starting with E1 is Pause
                KeyData->EfiKey = EfiKeyPause;
                KeyData->PS2ScanCode = Data;
                ResetStateMachine();
                return EFI_SUCCESS;
            }

            if  (gPeiKbd.ScannerCount == 4) { // E1 sequence has finished
                Status = ProcessByte(KeyData, Data, FALSE);
                ResetStateMachine();
                return Status;
            }

            //
            // E1 sequence is not complete, update the counter and return
            //
            gPeiKbd.ScannerCount++;
            return EFI_NOT_READY;
        } else {   // ScannerState == ST_E0 - processing E0 state

            //
            // For E0 state the Count values will be:
            //   0 for 1st and 2nd byte
            //   2 for 3rd byte (if available)
            //   1 for 4th byte (if available)
            // No validity checking will be done for 2nd,3rd and 4th bytes
            //

            if (gPeiKbd.ScannerState == KBST_E0) {
                if ( IsEnhancedKey( Data)) {
                    ResetStateMachine();
                    return EFI_NOT_READY;
                }
            
                // Processing E0 state, if data is 2A or AA or MSB bit is 
                // set (break key) ignore it. 
                if  ((Data == 0x2A) || (Data == 0xAA) || ((Data & 0x80) && \
                                   (Data != 0xb8)&& (Data != 0x9d))) {
                    // except in special case of alt or ctrl key
                    ResetStateMachine();
                    return EFI_NOT_READY;
                }
            }
         
            Status = ProcessByte(KeyData, Data, FALSE);
            ResetStateMachine();
            return Status;
        }   
    }

    return EFI_NOT_READY;
}

/** @internal
    Checks for valid key, updates key modifiers, and return the modified 
    Key Data 

    @param    *KeyData      - A pointer to the KEYBOARD device.
              data          - byte to process
              long_sequence - the indication of whether it is a
                              4 byte sequence or not; used to differentiate Shift keys

    @retval    Status
    @endinternal
**/

EFI_STATUS
ProcessByte(
    EFI_PEI_AMIKEYCODE_DATA *KeyData,
    UINT8 Data, 
    BOOLEAN long_sequence
)
{
    EFI_EXTKEY *extkey;       
    BOOLEAN bUpperCase, bShifted = 0;
    static BOOLEAN Make_Capslock = FALSE, Make_SCRLOCK = FALSE, Make_NUMLOCK = FALSE;      

    KeyData->Key.ScanCode = 0;
    KeyData->Key.UnicodeChar = 0;
    KeyData->PS2ScanCode = Data;

    //
    // Process ESC key
    //
    if (Data == 1) {
        KeyData->Key.ScanCode = EFI_SCAN_ESC;
        KeyData->EfiKey = EfiKeyEsc;
        return EFI_SUCCESS;
    }
    //
    // Process key modifiers: xyzLock (update LEDs) and Ctrl/Alt/Shift
    //

    switch (Data) {

        case 0x38:
            if (gPeiKbd.ScannerState == KBST_E0) {
               KeyData->KeyState.KeyShiftState |= RIGHT_ALT_PRESSED;
            } else {
               KeyData->KeyState.KeyShiftState |= LEFT_ALT_PRESSED;
            }
            return EFI_SUCCESS;
     
        case 0xB8:
            if (gPeiKbd.ScannerState == KBST_E0) {
               KeyData->KeyState.KeyShiftState &= ~RIGHT_ALT_PRESSED;
            } else {
               KeyData->KeyState.KeyShiftState &= ~LEFT_ALT_PRESSED;
            }
            return EFI_SUCCESS;

        case 0x1D:
            if (gPeiKbd.ScannerState == KBST_E0) {
                KeyData->KeyState.KeyShiftState  |= RIGHT_CONTROL_PRESSED;
            } else {
                KeyData->KeyState.KeyShiftState  |= LEFT_CONTROL_PRESSED;
            }
            return EFI_SUCCESS;

        case 0x9D:
            if (gPeiKbd.ScannerState == KBST_E0) {
                KeyData->KeyState.KeyShiftState &= ~RIGHT_CONTROL_PRESSED;
            } else {
                KeyData->KeyState.KeyShiftState &= ~LEFT_CONTROL_PRESSED;
            }
            return EFI_SUCCESS;

        case 0x2A: 
            KeyData->KeyState.KeyShiftState |= LEFT_SHIFT_PRESSED;
            return EFI_SUCCESS;

        case 0xAA: // could be a part of a long break code
            if (!long_sequence){
                KeyData->KeyState.KeyShiftState &= ~LEFT_SHIFT_PRESSED; 
                return EFI_SUCCESS;
            }
        break;
        case 0x36: 
            KeyData->KeyState.KeyShiftState |= RIGHT_SHIFT_PRESSED;
            return EFI_SUCCESS;

        case 0xB6: 
            KeyData->KeyState.KeyShiftState &= ~RIGHT_SHIFT_PRESSED;         
            return EFI_SUCCESS;

        case 0x3A:
            if (!Make_Capslock) {
                KeyData->KeyState.KeyToggleState ^= CAPS_LOCK_ACTIVE;
                Make_Capslock = TRUE;   
            }
            KeyData->EfiKey = EfiKeyCapsLock;
            return EFI_SUCCESS;

        case 0xBA:
            Make_Capslock = FALSE;
        break;

        case 0x46: 
            if (!Make_SCRLOCK) {
                KeyData->KeyState.KeyToggleState ^= SCROLL_LOCK_ACTIVE; 
                Make_SCRLOCK = TRUE;
            }
            KeyData->EfiKey = EfiKeySLck;
            return EFI_SUCCESS;
     
        case 0xC6:
            Make_SCRLOCK = FALSE;
            break;    

        case 0x45: 
            if (!Make_NUMLOCK) {
                KeyData->KeyState.KeyToggleState ^= NUM_LOCK_ACTIVE; 
                Make_NUMLOCK = TRUE;
            }
            KeyData->EfiKey = EfiKeyNLck;
            return EFI_SUCCESS;

        case 0xC5:
            Make_NUMLOCK = FALSE; 
            break;    
    }

    //
    // Process main block of keys
    //

    if ((Data !=0) && (Data < 0x3A) && !(Data == 0x37)) {// Exceptional case is Printscreen/sys req

        bShifted = KeyData->KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED);

        if (IsLetter(Data)) {   // for not-a-letter Caps-Lock must not work
            bUpperCase = (KeyData->KeyState.KeyToggleState & CAPS_LOCK_ACTIVE)? !bShifted: bShifted;
        }
        else {
            bUpperCase = bShifted;
        }
        if (bUpperCase) {
            KeyData->Key.UnicodeChar = Code_Table[Data];    // UPPER CASE TABLE
        }
        else {
            KeyData->Key.UnicodeChar = code_table[Data];    // lower case table
        }
        KeyData->EfiKey = ScancodeToEfi_table[Data];
        return EFI_SUCCESS;
    }


    //
    // Process keypad keys.  Exceptional cases:  -, + on keypad
    // Keypad numbers when NUMLOCK only is ON OR Shift only is pressed.
    if (gPeiKbd.ScannerState != KBST_E0) {
        if ((Data > 0x46) && (Data < 0x54) && !long_sequence) {
            if (((KeyData->KeyState.KeyToggleState & NUM_LOCK_ACTIVE)   // Only NUMLOCK in ON
                    && ((KeyData->KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)) == 0))
                || (((KeyData->KeyState.KeyToggleState & NUM_LOCK_ACTIVE) == 0)   // Only shift key is pressed
                    && (KeyData->KeyState.KeyShiftState & (RIGHT_SHIFT_PRESSED | LEFT_SHIFT_PRESSED)))
                || Data == 0x4a || Data ==0x4e) // check for -,  + keys in keypad
            {
                KeyData->Key.UnicodeChar = KeyPad_Table[Data-0x47];
                KeyData->EfiKey = KeyPadEfiCode_Table[Data-0x47];
                return EFI_SUCCESS;
            }
        }
    }

    //
    // Process F-keys
    //
    for (extkey = ScanCode_Table; extkey->makecode != 0xFF; extkey++) {
        if (Data == extkey->makecode) {
            KeyData->Key.ScanCode = extkey->efi_scancode;
            KeyData->EfiKey = extkey->efi_key;
            return EFI_SUCCESS;
        }
    }

   return EFI_NOT_READY;
}
