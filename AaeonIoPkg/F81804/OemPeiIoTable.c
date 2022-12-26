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
/** @file OemPeiIoTable.c
  SIO init table in PEI phase. Any customers have to review below tables
  for themselves platform and make sure each initialization is necessary.

  @note In all tables, only fill with necessary setting. Don't fill with default
**/
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioPeiLib.h>

///---------------------------------------------------------------------
///Decode table for PEI phase.
///---------------------------------------------------------------------
IO_DECODE_DATA F81804PeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {F81804_CONFIG_INDEX, 2, 0xFF},
    //Decode for KBC
#if (F81804_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
    //Below decode is for recovery mode
#if (F81804_RECOVERY_SUPPORT)
    {RECOVERY_COM_PORT_ADDR, 0x02, dsUART},
#endif
    //Below decode is for SIO generic IO decode
#if defined(F81804_TOTAL_BASE_ADDRESS) && (F81804_TOTAL_BASE_ADDRESS != 0)
    {F81804_TOTAL_BASE_ADDRESS, F81804_TOTAL_LENGTH, 0xFF},
#endif
    
};

///---------------------------------------------------------------------
///The PEI decode table count.
///---------------------------------------------------------------------
UINT8 F81804PeiDecodeTableCount = sizeof(F81804PeiDecodeTable)/sizeof(IO_DECODE_DATA);

///---------------------------------------------------------------------
///Init table for PEI phase.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA F81804PeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {F81804_CONFIG_INDEX, 0x00, F81804_CONFIG_MODE_ENTER_VALUE},
    {F81804_CONFIG_INDEX, 0x00, F81804_CONFIG_MODE_ENTER_VALUE},

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------
    {F81804_CONFIG_INDEX, 0x00, 0x26},
    {F81804_CONFIG_DATA,  0x3F, F81804_CLOCK << 6},

    {F81804_CONFIG_INDEX, 0x00, 0x27},
    {F81804_CONFIG_DATA,  0xDD, (GPIO_DEC_RANGE << 5) | (DPORT_EN << 1)},
    // CLK_TUNE_PROG_EN -> 0 >>
    	{F81804_CONFIG_INDEX, 0x00, 0x27},
    	{F81804_CONFIG_DATA,  0xFE, 0x00},      
    	// BANK_PROG_SEL -> 0 >>
    		{F81804_CONFIG_INDEX, 0x00, 0x27},
    		{F81804_CONFIG_DATA,  0xF3, 0x00}, 
			#if (F81804_SERIAL_PORT2_PRESENT) 
			    {F81804_CONFIG_INDEX, 0x00, 0x28},
			    {F81804_CONFIG_DATA,  0xFC, 0x03},  //UR2_GP_EN -> Full UART
    		#else
    			{F81804_CONFIG_INDEX, 0x00, 0x28},
    			{F81804_CONFIG_DATA,  0xF3, 0x00}, 		    
			#endif    		      
    		{F81804_CONFIG_INDEX, 0x00, 0x28},
    		{F81804_CONFIG_DATA,  0x2F, (PECI_PIN_EN << 7)},
    		{F81804_CONFIG_INDEX, 0x00, 0x2B},
    		{F81804_CONFIG_DATA,  0x1C, (GPIO67_EN << 7) | (GPIO66_EN << 6) | (FANIN3_EN << 1) | FANCTRL3_EN}, 
    		{F81804_CONFIG_INDEX, 0x00, 0x2C},
    		{F81804_CONFIG_DATA,  0xE0, (GPIO04_EN << 4) | GPIO00_EN},        		
    	// BANK_PROG_SEL -> 0 << 
    	// BANK_PROG_SEL -> 1 >>
    		{F81804_CONFIG_INDEX, 0x00, 0x27},
    		{F81804_CONFIG_DATA,  0xF3, 0x04},      
    		{F81804_CONFIG_INDEX, 0x00, 0x28},
    		{F81804_CONFIG_DATA,  0xB3, (DPORT_MODE << 3) | (SIRQ_PWR_SEL << 2)},	
    		{F81804_CONFIG_INDEX, 0x00, 0x2C},
    		{F81804_CONFIG_DATA,  0x08, (SMBUS_EN << 7) | (SDA2_PIN_EN << 5) | SCL0_PIN_EN},        		        		
    	// BANK_PROG_SEL -> 1 <<
    	// BANK_PROG_SEL -> 2 >>
    		{F81804_CONFIG_INDEX, 0x00, 0x27},
    		{F81804_CONFIG_DATA,  0xF3, 0x08},      
    		{F81804_CONFIG_INDEX, 0x00, 0x2A},
    		{F81804_CONFIG_DATA,  0x88, (GPIO15_FUNC_SEL << 4) | GPIO14_FUNC_SEL}, 
    		{F81804_CONFIG_INDEX, 0x00, 0x2C},
    		{F81804_CONFIG_DATA,  0x00, (GPIO27_EN << 7) | (GPIO26_EN << 6) | (GPIO25_EN << 5) | (GPIO24_EN << 4) | (GPIO23_EN << 3) | (GPIO22_EN << 2)},        		
    	// BANK_PROG_SEL -> 2 <<      
    	// BANK_PROG_SEL -> 3 >>
    		{F81804_CONFIG_INDEX, 0x00, 0x27},
    		{F81804_CONFIG_DATA,  0xF3, 0x0C},      
    		{F81804_CONFIG_INDEX, 0x00, 0x2A},
    		{F81804_CONFIG_DATA,  0x88, (GPIO17_FUNC_SEL << 4) | GPIO16_FUNC_SEL},		
    		{F81804_CONFIG_INDEX, 0x00, 0x2C},
    		{F81804_CONFIG_DATA,  0x00, (GPIO97_EN << 7) | (GPIO95_EN << 5) | (GPIO94_EN << 4) | (GPIO93_EN << 3) | (GPIO92_EN << 2) | (GPIO91_EN << 1)},        		
    	// BANK_PROG_SEL -> 3 <<            	      	  	         	
    // CLK_TUNE_PROG_EN -> 0 
    // CLK_TUNE_PROG_EN -> 1 >>
    	{F81804_CONFIG_INDEX, 0x00, 0x27},
    	{F81804_CONFIG_DATA,  0xFE, BIT0},
 // CLK_TUNE_PROG_EN -> 1
    // WAKEUP_EN -> 0
    {F81804_CONFIG_INDEX, 0x00, 0x2D},
    {F81804_CONFIG_DATA,  0x77, (CLK_Source_SEL << 7)},

    //------------------------------------------------------------------
    // Initialize Serial Port and Floppy Controller for Recovery
    //------------------------------------------------------------------
#if (F81804_RECOVERY_SUPPORT)
    // Select device
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, RECOVERY_LDN_UART},
    // Program Base Addr
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_LO_REGISTER},
    {F81804_CONFIG_DATA,  0x00, (UINT8)(RECOVERY_COM_PORT_ADDR & 0xFF)},
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_HI_REGISTER},
    {F81804_CONFIG_DATA,  0x00, (UINT8)(RECOVERY_COM_PORT_ADDR >> 8)},
    // Activate Device
    {F81804_CONFIG_INDEX, 0x00, F81804_ACTIVATE_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_ACTIVATE_VALUE},
#endif //F81804_RECOVERY_SUPPORT

    //------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // Initialize GPIO logical device
    //------------------------------------------------------------------ 
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_GPIO},

    // Program Base Address
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_LO_REGISTER},
    {F81804_CONFIG_DATA,  0x00, (UINT8)(IO1B & 0xFF)},
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_HI_REGISTER},
    {F81804_CONFIG_DATA,  0x00, (UINT8)(IO1B >> 8)},
    // Activate Device
    {F81804_CONFIG_INDEX, 0x00, F81804_ACTIVATE_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_ACTIVATE_VALUE},

    //------------------------------------------------------------------
    // Initialize UART 1 logical device
    //------------------------------------------------------------------   
#if (F81804_SERIAL_PORT1_PRESENT) 
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_UART1},
    {F81804_CONFIG_INDEX, 0x00, 0xF6},
    {F81804_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
#endif //F81804_SERIAL_PORT1_PRESENT 

    //------------------------------------------------------------------
    // Initialize UART 2 logical device
    //------------------------------------------------------------------ 
#if (F81804_SERIAL_PORT2_PRESENT)    
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_UART2},
    {F81804_CONFIG_INDEX, 0x00, 0xF6},
    {F81804_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
#endif //F81804_SERIAL_PORT2_PRESENT  
#    
    //------------------------------------------------------------------
    // Initialize KBC if exist
    //------------------------------------------------------------------
#if (F81804_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_PS2K},
    // Program Base Addr
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_HI_REGISTER},
    {F81804_CONFIG_DATA,  0x00, 0x00},
    {F81804_CONFIG_INDEX, 0x00, F81804_BASE1_LO_REGISTER},
    {F81804_CONFIG_DATA,  0x00, 0x60},
    // Program Interrupt
    {F81804_CONFIG_INDEX, 0x00, F81804_IRQ1_REGISTER},
    {F81804_CONFIG_DATA,  0x00, 0x01},
    {F81804_CONFIG_INDEX, 0x00, F81804_IRQ2_REGISTER},
    {F81804_CONFIG_DATA,  0x00, 0x0C},
    // Activate Device
    {F81804_CONFIG_INDEX, 0x00, F81804_ACTIVATE_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_PS2K},
    {F81804_CONFIG_INDEX, 0x00, F81804_ACTIVATE_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_DEACTIVATE_VALUE},
#endif //F81804_KEYBOARD_PRESENT

    //F81804_PS2SWAP_Workaround++ >>>>>
    // Seclect device KEYBOARD
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_PS2K},
    {F81804_CONFIG_INDEX, 0x00, 0xFE},
    {F81804_CONFIG_DATA,  0x77, 0x00},
    //F81804_PS2SWAP_Workaround++ <<<<<

#if (F81804_WDT_PRESENT)
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_WDT},
    {F81804_CONFIG_INDEX, 0x00, 0xFA},
    {F81804_CONFIG_DATA,  0xF7, 0x01},  // WDOUT_EN -> 1    
    {F81804_CONFIG_INDEX, 0x00, 0xF5},
    {F81804_CONFIG_DATA,  0xEC, 0x11},  // WD_PULSE -> pulse, WD_CLK_SEL -> 25 ms 
#endif //F81804_WDT_PRESENT

    //------------------------------------------------------------------
    // Initialize PME logical device
    //------------------------------------------------------------------
#if (F81804_PME_CONTROLLER_PRESENT) 
    {F81804_CONFIG_INDEX, 0x00, F81804_LDN_SEL_REGISTER},
    {F81804_CONFIG_DATA,  0x00, F81804_LDN_PME},
    {F81804_CONFIG_INDEX, 0x00, 0xE8},
    {F81804_CONFIG_DATA,  0x5F, 0xA0},  // RI2_WAKEUP_EN -> 1, RI1_WAKEUP_EN -> 1
    {F81804_CONFIG_INDEX, 0x00, 0xF4},
    {F81804_CONFIG_DATA,  0xBF, (LAST_ST_MODE << 6)},  
    {F81804_CONFIG_INDEX, 0x00, 0xFD},
    {F81804_CONFIG_DATA,  0x3F, (BOOT_FAIL_PD_DIS << 7) | (PWSIN_4S_PD_EN << 6)},
#endif //F81804_PME_CONTROLLER_PRESENT   

    //------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {F81804_CONFIG_INDEX, 0x00, F81804_CONFIG_MODE_EXIT_VALUE},

};

///---------------------------------------------------------------------
///The PEI init table count.
///---------------------------------------------------------------------
UINT8 F81804PeiInitTableCount = sizeof(F81804PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

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

