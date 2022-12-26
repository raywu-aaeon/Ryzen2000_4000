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
// Name:  <W83627DHGPeiIoTable.h>
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "Token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA W83627DHGPeiDecodeTable[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {W83627DHG_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
    #if defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT)
    #if (W83627DHG_SERIAL_PORT1_PRESENT)
    {W83627DHG_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART}, // COMA decode
    #endif
	#endif
    #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    #if (W83627DHG_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
    #endif
    #if (W83627DHG_FLOPPY_PORT_PRESENT)
    {0x3F0, 0, dsFDC},                                  // FDC decode
    #endif
    #endif
    //Below decode is for SIO generic IO decode
    #if defined(W83627DHG_TOTAL_BASE_ADDRESS) && (W83627DHG_TOTAL_BASE_ADDRESS != 0)
    {W83627DHG_TOTAL_BASE_ADDRESS, W83627DHG_TOTAL_LENGTH, 0xFF}, // open a IODecode section for GPIO+PME+...
    #endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    // Add more OEM IO decode below.
};

SIO_DEVICE_INIT_DATA W83627DHGPeiInitTable[]={
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    //AMI_TODO:
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_CONFIG_MODE_ENTER_VALUE},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    //Clock Selection,Default clock rate 48MHz
    {W83627DHG_CONFIG_INDEX, 0x00, 0x24},
    {W83627DHG_CONFIG_DATA,  0xBF, W83627DHG_CLOCK<<6 },
    //---------------------------------------------------------------------
    // Before init all logical devices, program GPIO Multi-Pin if needed.
    //---------------------------------------------------------------------
    #if W83627DHG_SERIAL_PORT1_PRESENT
    {W83627DHG_CONFIG_INDEX, 0x00, 0x29},
    {W83627DHG_CONFIG_DATA,  0xF7, 0x00},
    #endif
    #if W83627DHG_KEYBOARD_PRESENT
    {W83627DHG_CONFIG_INDEX, 0x00, 0x2A},
    {W83627DHG_CONFIG_DATA,  0xFE, 0x00},
    #endif
    #if W83627DHG_WDT_PORT_PRESENT
    {W83627DHG_CONFIG_INDEX, 0x00, 0x2D},
    {W83627DHG_CONFIG_DATA,  0xFE, 0x00},
    #endif

    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
    #if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
    #if (W83627DHG_SERIAL_PORT1_PRESENT)
    // Select device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_UART1},
    // Program Base Addr
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_LO_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, (UINT8)(W83627DHG_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_HI_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, (UINT8)(W83627DHG_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Program IRQ
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_IRQ1_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x04},
    // Activate Device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_ACTIVATE_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_ACTIVATE_VALUE},
    #endif // W83627DHG_SERIAL_PORT1_PRESENT
    #endif // #ifdef EFI_DEBUG
    //---------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //---------------------------------------------------------------------
    #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    #if (W83627DHG_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_PS2K},
    // Program Base Addr
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_HI_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x00},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_LO_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x60},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE2_HI_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x00},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE2_LO_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt 1
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_IRQ1_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x01},
    // Program Interrupt 2
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_IRQ2_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x0C},
    // Activate Device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_ACTIVATE_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_PS2K},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_ACTIVATE_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_DEACTIVATE_VALUE},
    #endif
    #if (W83627DHG_FLOPPY_PORT_PRESENT)
    // Seclect device FLOPPY
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_FDC},
    // Program Base Addr
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_HI_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x03},
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_BASE1_LO_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0xF0},
    // Program Interrupt
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_IRQ1_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, 0x06},
    // Activate Device
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_ACTIVATE_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_ACTIVATE_VALUE},
    #endif
    #endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)
    //---------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //---------------------------------------------------------------------
    // Seclect device KEYBOARD
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_PS2K},
    // config
    {W83627DHG_CONFIG_INDEX, 0x00, 0xF0},
    {W83627DHG_CONFIG_DATA,  0x00, 0x00 | (W83627DHG_KBC_CLOCK << 6)\
                    | (W83627DHG_KBC_PORT92 << 2)\
                    | (W83627DHG_KBC_GATE20 << 1)\
                    | W83627DHG_KBC_KBRST},
    //---------------------------------------------------------------------
    // Programm ACPI if needed.
    //---------------------------------------------------------------------
    #if W83627DHG_PS2_SWAP
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_LDN_SEL_REGISTER},
    {W83627DHG_CONFIG_DATA,  0x00, W83627DHG_LDN_ACPI},
    {W83627DHG_CONFIG_INDEX, 0x00, 0xE0},
    {W83627DHG_CONFIG_DATA,  0xFB, 0x04},
    #endif
    //---------------------------------------------------------------------
    // Programm Watch Dog Time and PLED & SUSLED if needed.
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    //AMI_TODO:
    //Exit Configuration Mode.
    {W83627DHG_CONFIG_INDEX, 0x00, W83627DHG_CONFIG_MODE_EXIT_VALUE},
};

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
