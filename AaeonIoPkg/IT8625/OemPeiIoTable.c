//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
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
IO_DECODE_DATA IT8625PeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {IT8625_CONFIG_INDEX, 2, 0xFF},
    //Decode for KBC
#if (IT8625_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
    //Below decode is for recovery mode
#if (IT8625_RECOVERY_SUPPORT)
    {RECOVERY_COM_PORT_ADDR, 0x02, dsUART},
#endif
    //Below decode is for SIO generic IO decode
#if defined(IT8625_TOTAL_BASE_ADDRESS) && (IT8625_TOTAL_BASE_ADDRESS != 0)
    {IT8625_TOTAL_BASE_ADDRESS, IT8625_TOTAL_LENGTH, 0xFF},
#endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    // Add more OEM IO decode below.
#if (IT8625_CIR_PORT_PRESENT)
    {0x3E0, 0x10, 0xFF},//for CIR
#endif
};

///---------------------------------------------------------------------
///The PEI decode table count.
///---------------------------------------------------------------------
UINT8 IT8625PeiDecodeTableCount = sizeof(IT8625PeiDecodeTable)/sizeof(IO_DECODE_DATA);

///---------------------------------------------------------------------
///Init table for PEI phase.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA IT8625PeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------
    //------------------------------------------------------------------
    // >>ITE Workaround for early I/O initialization sequence start
    // Base on IT8625E_09_13_15_16_17_18_56_51_69-BIOS_APNoteV19.pdf, Doc No.: ITEU3-AN-13019
    //------------------------------------------------------------------
    {IT8625_CONFIG_INDEX, 0x00, 0x87},
    {IT8625_CONFIG_INDEX, 0x00, 0x01},
    {IT8625_CONFIG_INDEX, 0x00, 0x55},
    #if (IT8625_CONFIG_INDEX == 0x2E)
        {IT8625_CONFIG_INDEX, 0x00, 0x55},
    #else
        {IT8625_CONFIG_INDEX, 0x00, 0xAA},
    #endif
        
    //Clock Setting 
    {IT8625_CONFIG_INDEX, 0x00, 0x23},
    {IT8625_CONFIG_DATA,  0xE6, (IT8625_WDT_LED_CLOCK_SRC << 4) | (IT8625_CLK_SELECT << 3) | IT8625_CLOCK},   //Bit0: CLKIN Frequence; Bit3: CLK select; Bit4: Clock Source Select of Watch Dog Timer and LED Blinking
    {IT8625_CONFIG_INDEX, 0x00, 0x07},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_GPIO},   //LDN 07
    // >> AAEON_OVERRIDE
    // GPIO Set 1 Multi-Function Pin Selection Register (Index=25h, Default=00h)
    {IT8625_CONFIG_INDEX, 0x00, 0x25},
    {IT8625_CONFIG_DATA,  0x00, (PIN_25_FUN_SEL << 7) | (PIN_127_FUN_SEL << 6) | (PIN_128_FUN_SEL << 5) | (PIN_28_FUN_SEL << 4) | (PIN_13_FUN_SEL << 3) | (PIN_30_FUN_SEL << 2) | (PIN_31_FUN_SEL << 1) | PIN_81_FUN_SEL},
    // GPIO Set 2 Multi-Function Pin Selection Register (Index=26h, Default=F3h)
    {IT8625_CONFIG_INDEX, 0x00, 0x26},
    {IT8625_CONFIG_DATA,  0x00, (PIN_17_FUN_SEL << 7) | (PIN_18_FUN_SEL << 6) | (PIN_19_FUN_SEL << 5) | (PIN_20_FUN_SEL << 4) | (PIN_21_FUN_SEL << 3) | (PIN_22_FUN_SEL << 2) | (PIN_23_FUN_SEL << 1) | PIN_24_FUN_SEL},
    // GPIO Set 3 Multi-Function Pin Selection Register (Index=27h, Default=00h)
    {IT8625_CONFIG_INDEX, 0x00, 0x27},
    {IT8625_CONFIG_DATA,  0x00, (PIN_8_FUN_SEL << 7) | (PIN_9_FUN_SEL << 6) | (PIN_10_FUN_SEL << 5) | (PIN_11_FUN_SEL << 4) | (PIN_124_FUN_SEL << 3) | (PIN_125_FUN_SEL << 2) | (PIN_126_FUN_SEL << 1) | PIN_16_FUN_SEL},
    // GPIO Set 4 Multi-Function Pin Selection Register (Index=28h, Default=00h)
    {IT8625_CONFIG_INDEX, 0x00, 0x28},
    {IT8625_CONFIG_DATA,  0x40, (PIN_67_FUN_SEL << 7) | (PIN_120_FUN_SEL << 5) | (PIN_53_FUN_SEL << 4) | (PIN_51_FUN_SEL << 3) | (PIN_118_FUN_SEL << 2) | (PIN_122_FUN_SEL << 1) | PIN_76_FUN_SEL},
    // GPIO Set 5 Multi-Function Pin Selection Register (Index=29h, Default=01h)
    {IT8625_CONFIG_INDEX, 0x00, 0x29},
    {IT8625_CONFIG_DATA,  0x00, (PIN_80_79_FUN_SEL << 7) | (PIN_78_77_42_FUN_SEL << 6) | (PIN_82_FUN_SEL << 5) | (PIN_70_FUN_SEL << 4) | (PIN_74_FUN_SEL << 3) | (PIN_6_FUN_SEL << 2) | (PIN_7_FUN_SEL << 1) | PIN_45_FUN_SEL},
    // << AAEON_OVERRIDE
    {IT8625_CONFIG_INDEX, 0x00, 0x2D},
    // >> AAEON_OVERRIDE
    //{IT8625_CONFIG_DATA,  0xF9, (IT8625_PCICLK << 2) | (IT8625_DPLL_RESET << 1)}, //Bit1: DPLL Reset Enable; Bit2: PCICLK select
    {IT8625_CONFIG_DATA,  0x05, (PIN_115_FUN_SEL << 7) | (PIN_116_FUN_SEL << 6) | (PIN_117_FUN_SEL << 5) | (PIN_2_FUN_SEL << 4) | (PIN_3_FUN_SEL << 3) | (!FAN_TAC5 << 1)},
    // << AAEON_OVERRIDE
    // >> AAEON_OVERRIDE
    // Initial GPIO I/O Base Address
    {IT8625_CONFIG_INDEX, 0x00, 0x62},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(IO1B >> 8)},
    {IT8625_CONFIG_INDEX, 0x00, 0x63},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(IO1B & 0xFF)},
    // << AAEON_OVERRIDE
    {IT8625_CONFIG_INDEX, 0x00, 0x71},
    {IT8625_CONFIG_DATA,  0xF7, IT8625_CLK_IN_SELECT << 3},                 //Bit3: External CLK_IN Select.
    
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_ENV},	//LDN 04
    {IT8625_CONFIG_INDEX, 0x00, 0xF0},
    {IT8625_CONFIG_DATA,  0x00, 0x00},	//0xF0= 00h
    {IT8625_CONFIG_INDEX, 0x00, 0xF1},
    {IT8625_CONFIG_DATA,  0x00, 0xBF},	//0xF1= BFh
    {IT8625_CONFIG_INDEX, 0x00, 0xF2},
    {IT8625_CONFIG_DATA,  0x00, 0x00},	//0xF2= 00
    {IT8625_CONFIG_INDEX, 0x00, 0xF3},
    {IT8625_CONFIG_DATA,  0x00, 0x00},	//0xF3= 00
    {IT8625_CONFIG_INDEX, 0x00, 0xF4},
    {IT8625_CONFIG_DATA,  0x00, 0x00},	//0xF4= 00
    {IT8625_CONFIG_INDEX, 0x00, 0xF5},
    {IT8625_CONFIG_DATA,  0x3F, 0x00},	//0xF5<7,6>= 0,0b
    {IT8625_CONFIG_INDEX, 0x00, 0xF9},	
    {IT8625_CONFIG_DATA,  0x7F, 0x00},	//0xF9<7>=0b (default)
    {IT8625_CONFIG_INDEX, 0x00, 0xFA},
    {IT8625_CONFIG_DATA,  0x00, 0x00},	//0xFA= 00h
    {IT8625_CONFIG_INDEX, 0x00, 0xFB},
    {IT8625_CONFIG_DATA,  0xF3, 0x0C},  //0xFB<3,2> (write "1" clear status)
        
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_GPIO},  //LDN 07
    {IT8625_CONFIG_INDEX, 0x00, 0x28},
    {IT8625_CONFIG_DATA,  0xBF, 0x00},	//Index28 Bit6=0 (keep default)
    {IT8625_CONFIG_INDEX, 0x00, 0x2A},
    {IT8625_CONFIG_DATA,  0x5F, 0x00},	//0x2A<5>= 0(disable RSTCONIN); don't enable LDN07 2A bit7
    {IT8625_CONFIG_INDEX, 0x00, 0x72},
    {IT8625_CONFIG_DATA,  0xEF, 0x00},	//0x72<4>=0(disable WDT if no use)
    {IT8625_CONFIG_INDEX, 0x00, 0x23},
    {IT8625_CONFIG_DATA,  0xBF, 0x40},  //0x23<6>=1
//    #if (JP4==1)
    {IT8625_CONFIG_INDEX, 0x00, 0x2C},
    {IT8625_CONFIG_DATA,  0xB7, (PWRGD_SRC_BY_VIN3 << 3) | 0x40},    //Index2C Bit6=1
//    #endif  
    
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_ENV}, 
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_HI_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(IT8625_HWM_BASE_ADDRESS >> 8)},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_LO_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(IT8625_HWM_BASE_ADDRESS & 0xFF)}, 
    // Activate Device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_ACTIVATE_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_ACTIVATE_VALUE},
    {IT8625_CONFIG_INDEX, 0x00, 0x02},
    {IT8625_CONFIG_DATA,  0x00, 0x02},  
    
    {IT8625_HWM_INDEX_PORT, 0x00, 0x0A},
    {IT8625_HWM_DATA_PORT,  0xBF, 0x40}, 	//Index 0Ah:Bit[6]=1b
    {IT8625_HWM_INDEX_PORT, 0x00, 0x00},
    {IT8625_HWM_DATA_PORT,  0xBE, 0x41},	//Index 00 bit0 set"1" Start monitor; Index00 Bit6=1
    //If Intel PECI
    {IT8625_HWM_INDEX_PORT, 0x00, 0x8E},
    {IT8625_HWM_DATA_PORT,  0x3D, 0xC2}, 	//Index 8Eh Bit[7,6] =1,1b; Index[8E}=02
    {IT8625_HWM_INDEX_PORT, 0x00, 0x0A},
    {IT8625_HWM_DATA_PORT,  0xC3, 0x24}, 	//Index 0Ah: Bit[2]=1b;Bit[3]=0b;Bit[5:4]=10b
    //If AMD TSI
    //{IT8625_HWM_INDEX_PORT, 0x00, 0x98},
    //{IT8625_HWM_DATA_PORT,  0x00, 0x40}, 	//Index 0x98=40
    //------------------------------------------------------------------
    //<<ITE Workaround for early I/O initialization sequence end
    //------------------------------------------------------------------
    
    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {IT8625_CONFIG_INDEX, 0x00, 0x87},
    {IT8625_CONFIG_INDEX, 0x00, 0x01},
    {IT8625_CONFIG_INDEX, 0x00, 0x55},
    #if (IT8625_CONFIG_INDEX == 0x2E)
        {IT8625_CONFIG_INDEX, 0x00, 0x55},
    #else
        {IT8625_CONFIG_INDEX, 0x00, 0xAA},
    #endif

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    // Select GPIO device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_GPIO},
#if (IT8625_SERIAL_PORT2_PRESENT)
    {IT8625_CONFIG_INDEX, 0x00, 0x26}, // clear index 26h bit7~4 bit1~0
    {IT8625_CONFIG_DATA,  0x0C, 0x00},
#endif // IT8625_SERIAL_PORT2_PRESENT

    //------------------------------------------------------------------
    // Initialize KBC if exist
    //------------------------------------------------------------------
#if (IT8625_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_PS2K},
    // Program Base Addr
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_HI_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, 0x00},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_LO_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, 0x60},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE2_HI_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, 0x00},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE2_LO_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt
    {IT8625_CONFIG_INDEX, 0x00, IT8625_IRQ1_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_ACTIVATE_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_PS2K},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_ACTIVATE_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_DEACTIVATE_VALUE},
#endif //IT8625_KEYBOARD_PRESENT

    //------------------------------------------------------------------
    // Initialize Serial Port and Floppy Controller for Recovery
    //------------------------------------------------------------------
#if (IT8625_RECOVERY_SUPPORT)
    // Select device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, RECOVERY_LDN_UART},
    // Program Base Addr
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_LO_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(RECOVERY_COM_PORT_ADDR & 0xFF)},
    {IT8625_CONFIG_INDEX, 0x00, IT8625_BASE1_HI_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, (UINT8)(RECOVERY_COM_PORT_ADDR >> 8)},
    // Activate Device
    {IT8625_CONFIG_INDEX, 0x00, IT8625_ACTIVATE_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_ACTIVATE_VALUE},

#endif //IT8625_RECOVERY_SUPPORT

    //------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //------------------------------------------------------------------
    // Seclect device KEYBOARD
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_PS2K},
    // config
    {IT8625_CONFIG_INDEX, 0x00, 0xF0},
    {IT8625_CONFIG_DATA,  0xF7, 0x00 | (IT8625_KBC_CLOCK << 3)},
    // Seclect Environment Controller
    {IT8625_CONFIG_INDEX, 0x00, IT8625_LDN_SEL_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, IT8625_LDN_ENV},
    // Clear Interrupt
    {IT8625_CONFIG_INDEX, 0x00, IT8625_IRQ1_REGISTER},
    {IT8625_CONFIG_DATA,  0x00, 0x00},
    // config
    {IT8625_CONFIG_INDEX, 0x00, 0xF4}, //Auto-swap of KCLK/KDAT and MCLK/MDAT
    {IT8625_CONFIG_DATA,  0x7F, IT8625_PS2_SWAP << 7},

    //------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {IT8625_CONFIG_INDEX, 0x00, 0x02},
    {IT8625_CONFIG_DATA,  0x00, 0x02},

	// >> AAEON_OVERRIDE Porting from DXE to PEI
	//---------------------------------------------------------------------
	// PEI Init Hardware Monitor.
	//---------------------------------------------------------------------
  #if IT8625_HWM_PRESENT
    #if (IT8625_PECI)
    //Programming PECI
    {IT8625_HWM_INDEX_PORT, 0x00, 0x0A},    // Interface Selection Register
    {IT8625_HWM_DATA_PORT,  0xCF, 0x20},    // 0Ah[5-4]=10
    {IT8625_HWM_INDEX_PORT, 0x00, 0x8E},    // External Temperature Sensor Host Control Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 8Eh=00
    {IT8625_HWM_INDEX_PORT, 0x00, 0x88},    // External Temperature Sensor Host Status Register
    {IT8625_HWM_DATA_PORT,  0x00, 0xFF},    // 88h=FF to clear status
    //TMPIN Source Selection.
    {IT8625_HWM_INDEX_PORT, 0x00, 0x06},    // SMI# Mask Register 3
    {IT8625_HWM_DATA_PORT,  0x9F, 0x40},    // Bank2
    {IT8625_HWM_INDEX_PORT, 0x00, 0x1D},    // TMPIN Source Selection – 1 (TSS1) for TMPIN1 & TMPIN2
    {IT8625_HWM_DATA_PORT,  0x00, 0x00 | (TMPIN2_SRC_SEL << 4)  // TMPIN2 Source Selection
                                       | TMPIN1_SRC_SEL},       // TMPIN1 Source Selection
    {IT8625_HWM_INDEX_PORT, 0x00, 0x1E},    // TMPIN Source Selection – 1 (TSS1) for TMPIN3 & TMPIN4
    {IT8625_HWM_DATA_PORT,  0x00, 0x00 | (TMPIN4_SRC_SEL << 4)  // TMPIN4 Source Selection
                                       | TMPIN3_SRC_SEL},       // TMPIN3 Source Selection
    {IT8625_HWM_INDEX_PORT, 0x00, 0x1F},    // TMPIN Source Selection – 1 (TSS1) for TMPIN5 & TMPIN6
    {IT8625_HWM_DATA_PORT,  0x00, 0x00 | (TMPIN6_SRC_SEL << 4)  // TMPIN6 Source Selection
                                       | TMPIN5_SRC_SEL},       // TMPIN5 Source Selection
    //Thermal Diode Zero Degree Adjust.
    {IT8625_HWM_INDEX_PORT, 0x00, 0x06},    // SMI# Mask Register 3
    {IT8625_HWM_DATA_PORT,  0x9F, 0x00},    // Bank0
    {IT8625_HWM_INDEX_PORT, 0x00, 0x5C},    // Beep Event Enable Register
    {IT8625_HWM_DATA_PORT,  0x7F, 0x80},    // 5Ch[7]=1 for enable access thermal diode zero degree adjust.
    {IT8625_HWM_INDEX_PORT, 0x00, 0x56},    // TMPIN1 Zero Degree Adjust Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 56h(TMPIN1)
    {IT8625_HWM_INDEX_PORT, 0x00, 0x57},    // TMPIN2 Zero Degree Adjust Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 57h(TMPIN2)
    {IT8625_HWM_INDEX_PORT, 0x00, 0x59},    // TMPIN3 Zero Degree Adjust Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 59h(TMPIN3)
    {IT8625_HWM_INDEX_PORT, 0x00, 0x5A},    // TMPIN4 Zero Degree Adjust Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 5Ah(TMPIN4)
    {IT8625_HWM_INDEX_PORT, 0x00, 0x90},    // TMPIN5 Zero Degree Adjust Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 90h(TMPIN5)
    {IT8625_HWM_INDEX_PORT, 0x00, 0x91},    // TMPIN6 Zero Degree Adjust Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00},    // 91h(TMPIN6)
    {IT8625_HWM_INDEX_PORT, 0x00, 0x5C},    // Beep Event Enable Register
    {IT8625_HWM_DATA_PORT,  0x7F, 0x00},    // 5Ch[7]=0 for disable access thermal diode zero degree adjust.
    #endif  // IT8625_PECI
    {IT8625_HWM_INDEX_PORT, 0x00, 0x0B},                    // General Control Register 1
    {IT8625_HWM_DATA_PORT,  0xF7, 0x00 | (FAN_TAC6 << 3)},  //BIT3: FAN_TAC6 Enable 
    {IT8625_HWM_INDEX_PORT, 0x00, 0x0C},                                    // General Control Register 2
    {IT8625_HWM_DATA_PORT,  0xCF, 0x00 | (FAN_TAC5 << 5) | (FAN_TAC4 << 4)},    //BIT5~4: FAN_TAC5-4 Enable
    {IT8625_HWM_INDEX_PORT, 0x00, 0x13},                    // Fan Controller Main Control Register
    {IT8625_HWM_DATA_PORT,  0x8F, 0x00 | (FAN_TAC3 << 6)    // BIT6: FAN_TAC3 Enable
                                       | (FAN_TAC2 << 5)    // BIT5: FAN_TAC2 Enable
                                       | (FAN_TAC1 << 4)},  // BIT4: FAN_TAC1 Enable
    {IT8625_HWM_INDEX_PORT, 0x00, 0x50},  // ADC Voltage Channel Enable Register
    {IT8625_HWM_DATA_PORT,  0x00, 0xFF},  //Enable Vin0 - 7
    {IT8625_HWM_INDEX_PORT, 0x00, 0x51},  // ADC Temperature Channel Enable Register
    {IT8625_HWM_DATA_PORT,  0x00, 0x00 | (IT8625_TEMP_RESISTOR_MODE_3_ENABLE << 5) //TMPIN 3-1 Thermal Resistor mode
                                       | (IT8625_TEMP_RESISTOR_MODE_2_ENABLE << 4)
                                       | (IT8625_TEMP_RESISTOR_MODE_1_ENABLE << 3)
                                       | (IT8625_TEMP_DIODE_MODE_3_ENABLE << 2) //TMPIN 3-1 Thermal Diode mode
                                       | (IT8625_TEMP_DIODE_MODE_2_ENABLE << 1)
                                       | IT8625_TEMP_DIODE_MODE_1_ENABLE},
    // >> IT8625 Serial Port 1 DCD#1 pin workaround
    #if (IT8625_SERIAL_PORT1_PRESENT)
    {IT8625_HWM_INDEX_PORT, 0x00, 0xA3},  // FAN_CTL6 SmartGuardian Automatic Mode Start PWM Register
    {IT8625_HWM_DATA_PORT,  0x00, 0xFF},  // Set 0xFF to prevent DCD#1 pin output 23.xx kHz garbage signal
    #endif // IT8625_SERIAL_PORT1_PRESENT
    // << IT8625 Serial Port 1 DCD#1 pin workaround
    //Hardware Monitor Startup!
    {IT8625_HWM_INDEX_PORT, 0x00, 0x00},    // Configuration Register 
    {IT8625_HWM_DATA_PORT,  0xBE, 0x41},    //BIT6: Update VBAT Voltage Reading
                                            //BIT0: Enable the startup of monitoring operations
  #endif  // IT8625_HWM_PRESENT
// << AAEON_OVERRIDE Porting from DXE to PEI

};

///---------------------------------------------------------------------
///The PEI init table count.
///---------------------------------------------------------------------
UINT8 IT8625PeiInitTableCount = sizeof(IT8625PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
