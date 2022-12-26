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
// Name:  <F81966PeiIoTable.h>
//
// Description:
//  SIO init table in PEI phase. Any customers have to review below tables
//  for themselves platform and make sure each initialization is necessary.
//
// Notes:
//  In all tables, only fill with necessary setting. Don't fill with default
//
//<AMI_FHDR_END>
//**********************************************************************
#ifndef _F81966PeiIoTable_H_
#define _F81966PeiIoTable_H_

#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include "token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA F81966PeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {F81966_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if (F81966_SERIAL_PORT1_PRESENT)
    {F81966_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (F81966_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
#if (F81966_FLOPPY_PORT_PRESENT)
    {0x3F0, 0, dsFDC},                                  // FDC decode
#endif
#endif
    //Below decode is for SIO generic IO decode
#if defined(F81966_TOTAL_BASE_ADDRESS) && (F81966_TOTAL_BASE_ADDRESS != 0)
    {F81966_TOTAL_BASE_ADDRESS, F81966_TOTAL_LENGTH, 0xFF},
#endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    {0x3E0, 0x10, 0xFF}, // 0x3E0~0x3F0 , open a IODecode section for UART3 4
    {0x2E0, 0x20, 0xFF}, // 0x2E0~0x2FF , open a IODecode section for UART5 6
    // Add more OEM IO decode below.

};

SIO_DEVICE_INIT_DATA F81966PeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {F81966_CONFIG_INDEX, 0x00, F81966_CONFIG_MODE_ENTER_VALUE},
    {F81966_CONFIG_INDEX, 0x00, F81966_CONFIG_MODE_ENTER_VALUE},

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------
    {F81966_CONFIG_INDEX, 0x00, 0x26},
    {F81966_CONFIG_DATA,  0x3F, F81966_CLOCK << 6},
    
    {F81966_CONFIG_INDEX, 0x00, 0x27},
    {F81966_CONFIG_DATA,  0xDD, (GPIO_DEC_RANGE << 5) | (DPORT_EN << 1)},
    // CLK_TUNE_PROG_EN -> 0 >>
    	{F81966_CONFIG_INDEX, 0x00, 0x27},
    	{F81966_CONFIG_DATA,  0xFE, 0x00},      
    	#if (F81966_SERIAL_PORT4_PRESENT)
    		{F81966_CONFIG_INDEX, 0x00, 0x29},
    		{F81966_CONFIG_DATA,  0x3F, 0xC0},  //UR4_GP_EN -> Full UART
    	#else
    		{F81966_CONFIG_INDEX, 0x00, 0x29},
    		{F81966_CONFIG_DATA,  0x3F, 0x00},    	
    	#endif          	
    	#if (F81966_SERIAL_PORT3_PRESENT)
    		{F81966_CONFIG_INDEX, 0x00, 0x29},
    		{F81966_CONFIG_DATA,  0xCF, 0x30},  //UR3_GP_EN -> Full UART
    	#else
    		{F81966_CONFIG_INDEX, 0x00, 0x29},
    		{F81966_CONFIG_DATA,  0xCF, 0x00},    	
    	#endif
    	// BANK_PROG_SEL -> 0 >>
    		{F81966_CONFIG_INDEX, 0x00, 0x27},
    		{F81966_CONFIG_DATA,  0xF3, 0x00},       
    		{F81966_CONFIG_INDEX, 0x00, 0x28},
    		{F81966_CONFIG_DATA,  0x2F, (PECI_PIN_EN << 7) | (LPT_PD_EN << 6) | (IR_PIN_EN << 4)},
    		#if (F81966_SERIAL_PORT5_PRESENT)
    			{F81966_CONFIG_INDEX, 0x00, 0x28},
    			{F81966_CONFIG_DATA,  0xF3, 0x0C},  // UR5_GP_EN -> Full UART
    		#else
    			{F81966_CONFIG_INDEX, 0x00, 0x28},
    			{F81966_CONFIG_DATA,  0xF3, 0x00},    		
    		#endif
    		#if (F81966_SERIAL_PORT6_PRESENT)
    			{F81966_CONFIG_INDEX, 0x00, 0x28},
    			{F81966_CONFIG_DATA,  0xFC, 0x03},  // UR6_GP_EN -> Full UART
    		#else
    			{F81966_CONFIG_INDEX, 0x00, 0x28},
    			{F81966_CONFIG_DATA,  0xFC, 0x00},    		
    		#endif
    		#if (F81966_PARALLEL_PORT_PRESENT)
    			{F81966_CONFIG_INDEX, 0x00, 0x28},
    			{F81966_CONFIG_DATA,  0xDF, 0x00},  // LPT_GP_EN -> LPT pins
    		#else
    			{F81966_CONFIG_INDEX, 0x00, 0x28},
    			{F81966_CONFIG_DATA,  0xDF, 0x20},    		
    		#endif
    		{F81966_CONFIG_INDEX, 0x00, 0x2A},
    		{F81966_CONFIG_DATA,  0x88, (GPIO11_FUNC_SEL << 4) | GPIO10_FUNC_SEL}, 
            {F81966_CONFIG_INDEX, 0x00, 0x2B},
            {F81966_CONFIG_DATA,  0x1C, (GPIO67_EN << 7) | (GPIO66_EN << 6) | (GPIO65_EN << 5) | (FANIN3_EN << 1) | FANCTRL3_EN},
    		{F81966_CONFIG_INDEX, 0x00, 0x2C},
    		{F81966_CONFIG_DATA,  0xE0, (GPIO04_EN << 4) | (GPIO03_EN << 3) | (GPIO02_EN << 2) | (GPIO01_EN << 1) | GPIO00_EN},        		
    	// BANK_PROG_SEL -> 0 << 
    	// BANK_PROG_SEL -> 1 >>
    		{F81966_CONFIG_INDEX, 0x00, 0x27},
    		{F81966_CONFIG_DATA,  0xF3, 0x04},      
    		{F81966_CONFIG_INDEX, 0x00, 0x28},
    		{F81966_CONFIG_DATA,  0xB3, (DPORT_PIN_SEL << 6) | (DPORT_MODE << 3) | (SIRQ_PWR_SEL << 2)},
    		{F81966_CONFIG_INDEX, 0x00, 0x2A},
    		{F81966_CONFIG_DATA,  0x88, (GPIO13_FUNC_SEL << 4) | GPIO12_FUNC_SEL},		{F81966_CONFIG_INDEX, 0x00, 0x2C},
    		{F81966_CONFIG_DATA,  0x08, (SMBUS_EN << 7) | (SDA3_PIN_EN << 6) | (SDA2_PIN_EN << 5) | (SDA0_PIN_EN << 4) | (SCL3_PIN_EN << 2) | (SCL2_PIN_EN << 1) | SCL0_PIN_EN},        		        		
    	// BANK_PROG_SEL -> 1 <<
    	// BANK_PROG_SEL -> 2 >>
    		{F81966_CONFIG_INDEX, 0x00, 0x27},
    		{F81966_CONFIG_DATA,  0xF3, 0x08},      
    		{F81966_CONFIG_INDEX, 0x00, 0x2A},
    		{F81966_CONFIG_DATA,  0x88, (GPIO15_FUNC_SEL << 4) | GPIO14_FUNC_SEL}, 
    		{F81966_CONFIG_INDEX, 0x00, 0x2C},
    		{F81966_CONFIG_DATA,  0x00, (GPIO27_EN << 7) | (GPIO26_EN << 6) | (GPIO25_EN << 5) | (GPIO24_EN << 4) | (GPIO23_EN << 3) | (GPIO22_EN << 2) | (GPIO21_EN << 1) | GPIO20_EN},        		
    	// BANK_PROG_SEL -> 2 <<      
    	// BANK_PROG_SEL -> 3 >>
    		{F81966_CONFIG_INDEX, 0x00, 0x27},
    		{F81966_CONFIG_DATA,  0xF3, 0x0C},      
    		{F81966_CONFIG_INDEX, 0x00, 0x2A},
    		{F81966_CONFIG_DATA,  0x88, (GPIO17_FUNC_SEL << 4) | GPIO16_FUNC_SEL},		
    		{F81966_CONFIG_INDEX, 0x00, 0x2C},
    		{F81966_CONFIG_DATA,  0x00, (GPIO97_EN << 7) | (GPIO96_EN << 6) | (GPIO95_EN << 5) | (GPIO94_EN << 4) | (GPIO93_EN << 3) | (GPIO92_EN << 2) | (GPIO91_EN << 1) | GPIO90_EN},        		
    	// BANK_PROG_SEL -> 3 <<     
    // CLK_TUNE_PROG_EN -> 0 
    // CLK_TUNE_PROG_EN -> 1 >>
    	{F81966_CONFIG_INDEX, 0x00, 0x27},
    	{F81966_CONFIG_DATA,  0xFE, BIT0},
 // CLK_TUNE_PROG_EN -> 1
    // WAKEUP_EN -> 0
    {F81966_CONFIG_INDEX, 0x00, 0x2D},
    {F81966_CONFIG_DATA,  0x77, (CLK_Source_SEL << 7)},

    //------------------------------------------------------------------
    // Initialize the Serial Port for debug usage. Default is COMA
    //------------------------------------------------------------------
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if (F81966_SERIAL_PORT1_PRESENT)
    // Select device
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART1},
    // Program Base Addr
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_LO_REGISTER},
    {F81966_CONFIG_DATA,  0x00, (UINT8)(F81966_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_HI_REGISTER},
    {F81966_CONFIG_DATA,  0x00, (UINT8)(F81966_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {F81966_CONFIG_INDEX, 0x00, F81966_ACTIVATE_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_ACTIVATE_VALUE},
#endif
#endif

    //------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //------------------------------------------------------------------
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (F81966_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_PS2K},
    // Program Base Addr
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_HI_REGISTER},
    {F81966_CONFIG_DATA,  0x00, 0x00},
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_LO_REGISTER},
    {F81966_CONFIG_DATA,  0x00, 0x60},
    // Program Interrupt
    {F81966_CONFIG_INDEX, 0x00, F81966_IRQ1_REGISTER},
    {F81966_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {F81966_CONFIG_INDEX, 0x00, F81966_ACTIVATE_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_PS2K},
    {F81966_CONFIG_INDEX, 0x00, F81966_ACTIVATE_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_DEACTIVATE_VALUE},
#endif //F81966_KEYBOARD_PRESENT
#if (F81966_FLOPPY_PORT_PRESENT)
    // Seclect device FLOPPY
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_FDC},
    // Program Base Addr
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_HI_REGISTER},
    {F81966_CONFIG_DATA,  0x00, 0x03},
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_LO_REGISTER},
    {F81966_CONFIG_DATA,  0x00, 0xF0},
    // Program Interrupt
    {F81966_CONFIG_INDEX, 0x00, F81966_IRQ1_REGISTER},
    {F81966_CONFIG_DATA,  0x00, 0x06},
    // Activate Device
    {F81966_CONFIG_INDEX, 0x00, F81966_ACTIVATE_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_ACTIVATE_VALUE},
#endif //F81966_FLOPPY_PORT_PRESENT
#endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)

    //------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //------------------------------------------------------------------
     
    //------------------------------------------------------------------
    // Initialize GPIO logical device
    //------------------------------------------------------------------   
#if (F81966_GPIO_PORT_PRESENT) 
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_GPIO},
    // Program Base Address
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_LO_REGISTER},
    {F81966_CONFIG_DATA,  0x00, (UINT8)(IO1B & 0xFF)},
    {F81966_CONFIG_INDEX, 0x00, F81966_BASE1_HI_REGISTER},
    {F81966_CONFIG_DATA,  0x00, (UINT8)(IO1B >> 8)},
    // Activate Device
    {F81966_CONFIG_INDEX, 0x00, F81966_ACTIVATE_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_ACTIVATE_VALUE},
#endif //F81966_GPIO_PORT_PRESENT
    //------------------------------------------------------------------
    // Initialize UART 1 logical device
    //------------------------------------------------------------------   
#if (F81966_SERIAL_PORT1_PRESENT) 
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART1},
    {F81966_CONFIG_INDEX, 0x00, 0xF6},
    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
#endif //F81966_SERIAL_PORT1_PRESENT 

    //------------------------------------------------------------------
    // Initialize UART 2 logical device
    //------------------------------------------------------------------ 
#if (F81966_SERIAL_PORT2_PRESENT)    
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART2},
    {F81966_CONFIG_INDEX, 0x00, 0xF6},
    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
#endif //F81966_SERIAL_PORT2_PRESENT     

    //------------------------------------------------------------------
    // Initialize UART 3 logical device
    //------------------------------------------------------------------ 
#if (F81966_SERIAL_PORT3_PRESENT)     
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART3},              
    {F81966_CONFIG_INDEX, 0x00, 0xF6},
    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
	#if (F81966_SERIAL_PORT3_EDGE_SHARE)
		//Set IRQ sharing to Edge High mode      
	    {F81966_CONFIG_INDEX, 0x00, 0xF0},
	    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  	// IRQ_MODE0->1, IRQ_SHARE->1 
	    {F81966_CONFIG_INDEX, 0x00, 0xF6},
	    {F81966_CONFIG_DATA,  0xF7, 0x00},  			// IRQ_MODE1->0     
	#endif //F81966_SERIAL_PORT3_EDGE_SHARE       
#endif //F81966_SERIAL_PORT3_PRESENT     

    //------------------------------------------------------------------
    // Initialize UART 4 logical device
    //------------------------------------------------------------------ 
#if (F81966_SERIAL_PORT4_PRESENT)     
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART4},         
    {F81966_CONFIG_INDEX, 0x00, 0xF6},
    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
	#if (F81966_SERIAL_PORT4_EDGE_SHARE)
		//Set IRQ sharing to Edge High mode      
	    {F81966_CONFIG_INDEX, 0x00, 0xF0},
	    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  	// IRQ_MODE0->1, IRQ_SHARE->1 
	    {F81966_CONFIG_INDEX, 0x00, 0xF6},
	    {F81966_CONFIG_DATA,  0xF7, 0x00},  			// IRQ_MODE1->0     
	#endif //F81966_SERIAL_PORT4_EDGE_SHARE       
#endif //F81966_SERIAL_PORT4_PRESENT     

    //------------------------------------------------------------------
    // Initialize UART 5 logical device
    //------------------------------------------------------------------ 
#if (F81966_SERIAL_PORT5_PRESENT)     
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART5},           
    {F81966_CONFIG_INDEX, 0x00, 0xF6},
    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
	#if (F81966_SERIAL_PORT5_EDGE_SHARE)
		//Set IRQ sharing to Edge High mode      
	    {F81966_CONFIG_INDEX, 0x00, 0xF0},
	    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  	// IRQ_MODE0->1, IRQ_SHARE->1 
	    {F81966_CONFIG_INDEX, 0x00, 0xF6},
	    {F81966_CONFIG_DATA,  0xF7, 0x00},  			// IRQ_MODE1->0     
	#endif //F81966_SERIAL_PORT5_EDGE_SHARE       
#endif //F81966_SERIAL_PORT5_PRESENT     

    //------------------------------------------------------------------
    // Initialize UART 6 logical device
    //------------------------------------------------------------------ 
#if (F81966_SERIAL_PORT6_PRESENT)     
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_UART6},   
    {F81966_CONFIG_INDEX, 0x00, 0xF6},
    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  		// FIFO_MODE->128-byte FIFO
	#if (F81966_SERIAL_PORT6_EDGE_SHARE)
		//Set IRQ sharing to Edge High mode      
	    {F81966_CONFIG_INDEX, 0x00, 0xF0},
	    {F81966_CONFIG_DATA,  0xFC, (BIT0 + BIT1)},  	// IRQ_MODE0->1, IRQ_SHARE->1 
	    {F81966_CONFIG_INDEX, 0x00, 0xF6},
	    {F81966_CONFIG_DATA,  0xF7, 0x00},  			// IRQ_MODE1->0     
	#endif //F81966_SERIAL_PORT6_EDGE_SHARE      
#endif //F81966_SERIAL_PORT6_PRESENT

    //------------------------------------------------------------------
    // Initialize PS2 logical device
    //------------------------------------------------------------------ 
    //F81966_PS2SWAP_Workaround++ >>>>>
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_PS2K},
    {F81966_CONFIG_INDEX, 0x00, 0xFE},
    {F81966_CONFIG_DATA,  0x00, 0x03},
    //F81966_PS2SWAP_Workaround++ <<<<<
    //
    //------------------------------------------------------------------
    // Initialize WDT logical device
    //------------------------------------------------------------------ 
#if (F81966_WDT_PRESENT)
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_WDT},
    {F81966_CONFIG_INDEX, 0x00, 0xF5},
    {F81966_CONFIG_DATA,  0xEC, 0x11},  // WD_PULSE -> pulse, WD_CLK_SEL -> 25 ms 
    {F81966_CONFIG_INDEX, 0x00, 0xFA},
    {F81966_CONFIG_DATA,  0xEE, 0x11},  // WDT_CLK_SEL - > 1, WDOUT_EN -> 1    
#endif //F81966_WDT_PRESENT
    
    //------------------------------------------------------------------
    // Initialize PME logical device
    //------------------------------------------------------------------
#if (F81966_PME_CONTROLLER_PRESENT) 
    {F81966_CONFIG_INDEX, 0x00, F81966_LDN_SEL_REGISTER},
    {F81966_CONFIG_DATA,  0x00, F81966_LDN_PME},
    {F81966_CONFIG_INDEX, 0x00, 0xE8},
    {F81966_CONFIG_DATA,  0x5F, 0xA0},  // RI2_WAKEUP_EN -> 1, RI1_WAKEUP_EN -> 1
    {F81966_CONFIG_INDEX, 0x00, 0xF4},
    {F81966_CONFIG_DATA,  0xBF, (LAST_ST_MODE << 6)},  
    {F81966_CONFIG_INDEX, 0x00, 0xFD},
    {F81966_CONFIG_DATA,  0x3F, (BOOT_FAIL_PD_DIS << 7) | (PWSIN_4S_PD_EN << 6)},
#endif //F81966_PME_CONTROLLER_PRESENT        

    //------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {F81966_CONFIG_INDEX, 0x00, F81966_CONFIG_MODE_EXIT_VALUE},

};

#if F81966_HWM_PRESENT
SIO_DEVICE_INIT_DATA   HWM_Init_Table[] = {
    //-----------------------------
    //| Reg16 | AndData8  | OrData8  |
    //-----------------------------
    //OEM_TODO: Base on OEM board.
	{0x6B, 0xF9, (F81966_T2_MODE << 2) | (F81966_T1_MODE << 1) },

#if F81966_HWM_PECI_SUPPORT
	// PECI Setting
	{0x0A, 0xDE, 0x21 }, //Enable PECI
    {0x0C, 0x00, F81966_HWM_PECI_TCC },
#endif
    //Hardware Monitor Startup!
    {0x01, 0xF8, 0x03},  //BIT1: Enable startup of fan monitoring operations
                         //BIT0: Enable startup of temperature and voltage monitoring operations

	//Fan type Setting
    #if F81966_SMF_SUPPORT
    {0x94, 0xC0, (FAN3_TYPE<<4)|(FAN2_TYPE<<2)|FAN1_TYPE },
    #endif

}; // HWM_Init_Table
#endif //F81966_HWM_PRESENT

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_F81966PeiIoTable_H_
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
