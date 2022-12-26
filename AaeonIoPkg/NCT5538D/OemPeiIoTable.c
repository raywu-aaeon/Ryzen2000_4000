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
IO_DECODE_DATA NCT5538DPeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {NCT5538D_CONFIG_INDEX, 2, 0xFF},
    //Decode for KBC
#if (NCT5538D_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
    //Below decode is for recovery mode
#if (NCT5538D_RECOVERY_SUPPORT)
    {RECOVERY_COM_PORT_ADDR, 0x02, dsUART},
#endif
    //Below decode is for SIO generic IO decode
#if defined(NCT5538D_TOTAL_BASE_ADDRESS) && (NCT5538D_TOTAL_BASE_ADDRESS != 0)
    {NCT5538D_TOTAL_BASE_ADDRESS, NCT5538D_TOTAL_LENGTH, 0xFF},
#endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // Add more OEM IO decode below.
};

///---------------------------------------------------------------------
///The PEI decode table count.
///---------------------------------------------------------------------
UINT8 NCT5538DPeiDecodeTableCount = sizeof(NCT5538DPeiDecodeTable)/sizeof(IO_DECODE_DATA);

///---------------------------------------------------------------------
///Init table for PEI phase.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA NCT5538DPeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_CONFIG_MODE_ENTER_VALUE},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_CONFIG_MODE_ENTER_VALUE},

//    //------------------------------------------------------------------
//    // Before init all logical devices, program Global register if needed.
//    //------------------------------------------------------------------
//    {NCT5538D_CONFIG_INDEX, 0x00, 0x27},
//    {NCT5538D_CONFIG_DATA,  0x7F, 0x00},//Set muti-function pin for UARTA

    // Global Register CR1Ah
    {NCT5538D_CONFIG_INDEX, 0x00, 0x1A},
    {NCT5538D_CONFIG_DATA, ~(BIT7 + BIT6), (NCT5538D_PIN40_SELECTION << 6) | BIT1},

    // Global Register CR1Bh
    {NCT5538D_CONFIG_INDEX, 0x00, 0x1B},
    {NCT5538D_CONFIG_DATA, ~BIT7, (NCT5538D_PIN23_SELECTION << 7)},

    // Global Register CR1Ch
    {NCT5538D_CONFIG_INDEX, 0x00, 0x1C},
    {NCT5538D_CONFIG_DATA, ~(BIT6 + BIT5 + BIT0), (NCT5538D_PIN2_SELECTION << 6) | (NCT5538D_PIN1_SELECTION << 5) | NCT5538D_PIN59_SELECTION},

    // Global Register CR1Dh
    {NCT5538D_CONFIG_INDEX, 0x00, 0x1D},
    {NCT5538D_CONFIG_DATA, ~(BIT3 + BIT2 + BIT1), (NCT5538D_PIN42_SELECTION << 1)},

    // Global Register CR24h
    {NCT5538D_CONFIG_INDEX, 0x00, 0x24},
    {NCT5538D_CONFIG_DATA, ~(BIT5 + BIT4 + BIT3), (NCT5538D_AUXFANOUT0_OUTPUT_TYPE << 5) | (NCT5538D_SYSFANOUT_OUTPUT_TYPE << 4) | (NCT5538D_CPUFANOUT_OUTPUT_TYPE << 3)},

    // Global Register CR2Ah
    {NCT5538D_CONFIG_INDEX, 0x00, 0x2A},
    {NCT5538D_CONFIG_DATA, ~(BIT7 + BIT1 + BIT0), (NCT5538D_SERIAL_PORT1_PRESENT ? 0 << 7 : 1 << 7) | (NCT5538D_MOUSE_PRESENT ? 0 << 1 : 1 << 1) | (NCT5538D_KEYBOARD_PRESENT ? 0 : 1)},

    // Global Register CR2Bh
    {NCT5538D_CONFIG_INDEX, 0x00, 0x2B},
    {NCT5538D_CONFIG_DATA, ~(BIT7 + BIT6), (NCT5538D_PIN37_SELECTION << 7) | (NCT5538D_PIN38_SELECTION << 6)},

    // Global Register CR2Ch
    {NCT5538D_CONFIG_INDEX, 0x00, 0x2C},
    {NCT5538D_CONFIG_DATA, ~(BIT6 + BIT5 + BIT4 + BIT3 + BIT0), (NCT5538D_PIN35_SELECTION << 5) | (NCT5538D_PIN44_SELECTION << 3) | NCT5538D_PIN58_SELECTION},

    // Logical Device 7 GPIO7 / GPIO8
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, NCT5538D_LDN_GPIO1},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA, ~(BIT2 + BIT1), (NCT5538D_GPIO8_ACTIVE << 2) | (NCT5538D_GPIO7_ACTIVE << 1)},
    // CRE0h should be controlled by BIOS Setup
    // CRE1h should be controlled by BIOS Setup
    // CRE4h should be controlled by BIOS Setup
    // CRE5h should be controlled by BIOS Setup

    // Logical Device 8 WDT1 / GPIO0
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, NCT5538D_LDN_GPIO2},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA, ~(BIT3 + BIT1), (IO1B ? 1 << 3 : 0 << 3) | (NCT5538D_GPIO0_ACTIVE << 1)},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_HI_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, (UINT8)(IO1B >> 8)},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_LO_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, (UINT8)(IO1B)},
    // CRE0h should be controlled by BIOS Setup
    // CRE1h should be controlled by BIOS Setup

    // Logical Device 9 GPIO2 / GPIO3 / GPIO4 / GPIO5
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, NCT5538D_LDN_GPIO3},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA, ~(BIT3 + BIT2 + BIT1 + BIT0), (NCT5538D_GPIO5_ACTIVE << 3) | (NCT5538D_GPIO4_ACTIVE << 2) | (NCT5538D_GPIO3_ACTIVE << 1) | NCT5538D_GPIO2_ACTIVE},
    // CRE0h should be controlled by BIOS Setup
    // CRE1h should be controlled by BIOS Setup
    // CRE3h should be controlled by BIOS Setup
    // CRE5h should be controlled by BIOS Setup
    // CRF0h should be controlled by BIOS Setup
    // CRF1h should be controlled by BIOS Setup
    // CRF4h should be controlled by BIOS Setup
    // CRF5h should be controlled by BIOS Setup

    // Logical Device A ACPI
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, NCT5538D_LDN_PME},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xE3},
    {NCT5538D_CONFIG_DATA, 0xFF, 0x00}, // Clear Event Status Register
    {NCT5538D_CONFIG_INDEX, 0x00, 0xE4},
    {NCT5538D_CONFIG_DATA, ~(BIT4), (NCT5538D_3VSBSW_EN << 4)},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xE5},
    {NCT5538D_CONFIG_DATA, ~(BIT2 + BIT1 + BIT0), (NCT5538D_RESETCONO_TO_PWROK << 2) | (NCT5538D_PWROK_SOURCE_SELECTION << 1) | (NCT5538D_ATXPGD_ROUTE_TO_PWROK)},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xE6},
    {NCT5538D_CONFIG_DATA, ~(BIT3 + BIT2 + BIT1), (NCT5538D_PWROK_DEL << 1)},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xE7},
    {NCT5538D_CONFIG_DATA, ~(BIT0), NCT5538D_HWM_RESET_SOURCE_SELECTION},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xF0},
    {NCT5538D_CONFIG_DATA, ~(BIT7 + BIT6 + BIT5), (NCT5538D_PIN34_SELECTION << 5)},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xF2},
    {NCT5538D_CONFIG_DATA, ~(BIT4 + BIT3), (NCT5538D_PIN37_SELECTION ? 0 << 4 : 1 << 4) | (NCT5538D_PIN38_SELECTION ? 0 << 3 : 1 << 3)},

    // Logical Device B HWM
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, NCT5538D_LDN_HWM},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_HI_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, (UINT8)(IO2B >> 8)},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_LO_REGISTER},
    {NCT5538D_CONFIG_DATA, 0x00, (UINT8)(IO2B)},
    {NCT5538D_CONFIG_INDEX, 0x00, 0xFA},
    {NCT5538D_CONFIG_DATA, ~(BIT3 + BIT2), (NCT5538D_RESETCONO_PWROK_PULSE_WIDTH << 2)},
    // >> 2016/07/19 AAEON_OVERRIDE
    // Activate Device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_ACTIVATE_VALUE},
    // << 2016/07/19 AAEON_OVERRIDE
    //------------------------------------------------------------------
    // Initialize KBC if exist
    //------------------------------------------------------------------
#if (NCT5538D_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_LDN_PS2K},
    // Program Base Addr
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_HI_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, 0x00},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_LO_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, 0x60},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE2_HI_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, 0x00},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE2_LO_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_IRQ1_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_LDN_PS2K},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_DEACTIVATE_VALUE},
#endif //NCT5538D_KEYBOARD_PRESENT

    //------------------------------------------------------------------
    // Initialize Serial Port and Floppy Controller for Recovery
    //------------------------------------------------------------------
#if (NCT5538D_RECOVERY_SUPPORT)
    // Select device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_LDN_SEL_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, RECOVERY_LDN_UART},
    // Program Base Addr
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_LO_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, (UINT8)(RECOVERY_COM_PORT_ADDR & 0xFF)},
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_BASE1_HI_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, (UINT8)(RECOVERY_COM_PORT_ADDR >> 8)},
    // Activate Device
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_ACTIVATE_REGISTER},
    {NCT5538D_CONFIG_DATA,  0x00, NCT5538D_ACTIVATE_VALUE},
#endif //NCT5538D_RECOVERY_SUPPORT

    //------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {NCT5538D_CONFIG_INDEX, 0x00, NCT5538D_CONFIG_MODE_EXIT_VALUE},

    // >> 2016/07/19 AAEON_OVERRIDE
    //---------------------------------------------------------------------
    // PEI Init Hardware Monitor.
    //---------------------------------------------------------------------
    #if NCT5538D_HWM_PRESENT
    //Bank Select,bank 0
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x4E},
    {NCT5538D_HWM_DATA_PORT, 0xF0, 0x00},
    //SYSFANOUT Output Mode Selection,DC output(Default)
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x04},
    {NCT5538D_HWM_DATA_PORT, 0xFE, 0x01},
    //SYSFANOUT PWM Output Frequency Configuration Register
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x00},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x04},
    //CPUFANOUT PWM Output Frequency Configuration Register 
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x02},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x04},
    //AUXFANOUT0 PWM Output Frequency Configuration Register 
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x10},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x04},
    //AUXFANOUT1 PWM Output Frequency Configuration Register 
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x12},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x04},
    //AUXFANOUT2 PWM Output Frequency Configuration Register 
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x14},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x04},
    //SMI mask
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x43},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0xFF},
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x44},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0xFF},
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x46},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x1E},

    //SMI/OVT setting >>
    //OVT# Configuration,Enable/Disable SMIOVT1#,mode select
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x18},
    {NCT5538D_HWM_DATA_PORT, 0xAE, 0x40},
    //SMI/OVT Control,Enable/Disable SMIOVT2,3, SMIOVT2~6 mode select
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x4C},
    {NCT5538D_HWM_DATA_PORT, 0x93, 0x08},

    //voltage limit setting >>
    //CPUVCORE High Limit
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x2b},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //CPUVCORE Low Limit
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x2c},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN0 High Limit 
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x2d},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN0 Low Limit 
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x2e},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //AVCC High Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x2f},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //AVCC Low Limit
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x30},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //3VCC High Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x31},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //3VCC Low Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x32},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN1 High Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x33},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN1 Low Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x34},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN8 High Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x35},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN8 Low Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x36},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN4 High Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x37},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN4 Low Limit  
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x38},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},
    //SMIOVT1 temperature sensor High Limit    
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x39},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x7F},
    //SMIOVT1 temperature sensor Hysteresis Limit    
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x3A},
    //{NCT5538D_HWM_DATA_PORT, 0x00, 0x00},

    //FAN IN/OUT Control
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x4D},
    {NCT5538D_HWM_DATA_PORT, 0x00, 0x55},
    //FAN IN/OUT Control    
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x50},
    {NCT5538D_HWM_DATA_PORT, 0xFC, 0x01},
    //VBAT Monitor Control,and AUXTIN/CPUTIN Sensor type selection
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x5D},
    {NCT5538D_HWM_DATA_PORT, 0x80, 0x00 |(AUXTIN3_SENSOR<<6)|(AUXTIN2_SENSOR<<5)|(AUXTIN1_SENSOR<<4)\
                |(AUXTIN0_SENSOR<<3)|(CPUTIN_SENSOR<<2)|(SYSTIN_SENSOR<<1)|EN_VBAT_MNT},

    //Enable AUXTIN/CPUTIN Current Mode
    //{NCT5538D_HWM_INDEX_PORT, 0x00, 0x5E},
    //{NCT5538D_HWM_DATA_PORT, 0x81, 0x7E},

    //PECI Temperature Reading Enable for SMIOVT and SMART FAN Control 
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0xAE},
    {NCT5538D_HWM_DATA_PORT, 0xFC, 0x03},

    //Bank Select,bank 7
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x4E},
    {NCT5538D_HWM_DATA_PORT, 0xF0, 0x07},

    //PECI Enable Function
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x01},
    {NCT5538D_HWM_DATA_PORT, 0x78, (PECI_EN<<7)|(IS_PECI30<<2)|(MANUAL_EN<<1)|ROUTINE_EN},
    //Set PECI Agent Config
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x03},
    {NCT5538D_HWM_DATA_PORT, 0xFF, PECI_AGENT_CFG},
    //Tbase for PECI
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x09},
    {NCT5538D_HWM_DATA_PORT, 0x00, TBASE0},
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x0A},
    {NCT5538D_HWM_DATA_PORT, 0x00, TBASE1},

    //index4Eh bit[3-0] select bank number.
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x4E},
    {NCT5538D_HWM_DATA_PORT, 0xF0, 0x00},
    // Configuration Register,Enable SMI# and Start
    {NCT5538D_HWM_INDEX_PORT, 0x00, 0x40},
    {NCT5538D_HWM_DATA_PORT, 0x44, 0x01},
    #endif //NCT5538D_HWM_PRESENT
    // << 2016/07/19 AAEON_OVERRIDE
};

///---------------------------------------------------------------------
///The PEI init table count.
///---------------------------------------------------------------------
UINT8 NCT5538DPeiInitTableCount = sizeof(NCT5538DPeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

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


