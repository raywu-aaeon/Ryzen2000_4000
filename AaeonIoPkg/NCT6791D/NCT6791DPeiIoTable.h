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
// Name:  <NCT6791DPeiIoTable.h>
//
// Description:
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "token.h"
#include <Library/AmiSioPeiLib.h>
IO_DECODE_DATA NCT6791DPeiDecodeTable[]={
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {NCT6791D_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
    #if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
    #if (NCT6791D_SERIAL_PORT1_PRESENT)
    {NCT6791D_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
    #endif
    #endif
    #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    #if (NCT6791D_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
    #endif
    #endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    //Below decode is for SIO generic IO decode
    #if defined(NCT6791D_TOTAL_BASE_ADDRESS) && (NCT6791D_TOTAL_BASE_ADDRESS != 0)
    {NCT6791D_TOTAL_BASE_ADDRESS, NCT6791D_TOTAL_LENGTH, 0xFF},
    #endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    #if (NCT6791D_CIR_PORT_PRESENT)
    {0x3E0, 0x10, 0xFF},//for CIR
    #endif
    // Add more OEM IO decode below.
};

SIO_DEVICE_INIT_DATA NCT6791DPeiInitTable[]={
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_CONFIG_MODE_ENTER_VALUE},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // IRQ Type and Polarity setting.
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    {NCT6791D_CONFIG_INDEX, 0x00, 0x1A},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR1A_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x1B},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR1B_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x1C},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR1C_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x1D},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR1D_VAL},    
    {NCT6791D_CONFIG_INDEX, 0x00, 0x24},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR24_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x27},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR27_VAL}, 
    {NCT6791D_CONFIG_INDEX, 0x00, 0x2A},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR2A_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x2B},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR2B_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x2C},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR2C_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0x2D},      
    {NCT6791D_CONFIG_DATA,  0xFC, NCT6791D_CR2D_VAL},
    #if (STRAP_FUN_RESULT_OVERRIDE)
    {NCT6791D_CONFIG_INDEX, 0x00, 0x2F},      
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_CR2F_VAL},
    #endif // STRAP_FUN_RESULT_OVERRIDE
    //---------------------------------------------------------------------
    // Initialize the Serial Port for Recovery. Default is COMA
    //---------------------------------------------------------------------
    #if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
    #if (NCT6791D_SERIAL_PORT1_PRESENT)
    // Select device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_UART1},
    // Program Base Addr
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_ACTIVATE_VALUE},
    #endif
    #endif
    //---------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //---------------------------------------------------------------------
// 2015/08/25 Eric -     #if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
    #if (NCT6791D_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_PS2K},
    // Program Base Addr
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, 0x00},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, 0x60},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE2_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, 0x00},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE2_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_IRQ1_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, 0x01},
	// >> 2015/08/25 Eric
    // Program Interrupt
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_IRQ2_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, 0x0C},
	// << 2015/08/25 Eric
    // Activate Device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_ACTIVATE_VALUE},
    #else
    // Deactivate Device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_PS2K},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_DEACTIVATE_VALUE},
    #endif //NCT6791D_KEYBOARD_PRESENT
// 2015/08/25 Eric -     #endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)
    //---------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //---------------------------------------------------------------------
    // Seclect device KEYBOARD
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_PS2K},
    // config
    {NCT6791D_CONFIG_INDEX, 0xFF, 0xF0},
    {NCT6791D_CONFIG_DATA,  0xF7, 0x80 | (NCT6791D_PORT92_EN << 2) | (NCT6791D_GA20_SFTCTL<<1) | NCT6791D_KBRST_SFTCTL},

    // LDN 7 GPIO6, GPIO7, GPIO8 Configuration Settings
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_GPIO1},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN7_ACTIVE_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xEC},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO7_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xED},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO8_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF8},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO6_MULTI_VAL},

    // LDN 8 WDT1, WDT_MEM, GPIO0, GPIO1 Configuration Settings
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_GPIO2},
    // Program GPIO Base Addr
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_GPIO_BASE_ADDRESS & 0xFF)},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_GPIO_BASE_ADDRESS >> 8)},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN8_ACTIVE_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE4},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO0_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF4},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO1_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF5},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_WDT1_KBC_MODE},

    // LDN 9 GPIO2, GPIO3, GPIO4, GPIO5 Configuration Settings
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_GPIO3},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN9_ACTIVE_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE9},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO2_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xEA},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO3_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xEB},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO5_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xEE}, //RayWu, ADD 2015/09/04
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GPIO4_MULTI_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xFE},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_INPUT_DET_TYPE},

    // LDN A ACPI Configuration Settings
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_ACPI},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE0},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRE0_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE4},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRE4_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE5},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRE5_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE6},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRE6_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE7},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRE7_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE9},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRE9_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xEC},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CREC_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xED},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRED_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xEE},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CREE_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF0},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRF0_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF1},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRF1_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF2},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRF2_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF6},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRF6_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF7},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRF7_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xFC},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRFC_VAL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xFE},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDNA_CRFE_VAL},

    // LDN B Hardware Monitor Configuration Settings
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_HWM},
    // Program HM Base Addr
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_HWM_BASE_ADDRESS & 0xFF)},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE1_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_HWM_BASE_ADDRESS >> 8)},
    // Program SB-TSI Base Addr
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE2_LO_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_TSI_BASE_ADDRESS & 0xFF)},
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_BASE2_HI_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, (UINT8)(NCT6791D_TSI_BASE_ADDRESS >> 8)},
    // Activate Device
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_ACTIVATE_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_ACTIVATE_VALUE},

    // LDN F GPIO Push-pull or Open-drain selection Settings
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_LDN_SEL_REGISTER},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_LDN_GPIO4},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE0},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP1_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE1},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP2_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE2},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP3_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE3},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP4_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE4},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP5_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE5},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP6_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE6},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP7_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE7},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP8_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xE9},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_GP0_PP_OD_SEL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF1},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_I2C_P80_CTRL},
    {NCT6791D_CONFIG_INDEX, 0x00, 0xF2},
    {NCT6791D_CONFIG_DATA,  0x00, NCT6791D_I2C_P80_DATA},
    //---------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {NCT6791D_CONFIG_INDEX, 0x00, NCT6791D_CONFIG_MODE_EXIT_VALUE},

    //---------------------------------------------------------------------
    // PEI Init Hardware Monitor.
    //---------------------------------------------------------------------
    #if NCT6791D_HWM_PRESENT
    //Bank Select,bank 0
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x4E},
    {NCT6791D_HWM_DATA_PORT, 0xF0, 0x00},
    //SYSFANOUT Output Mode Selection,DC output(Default)
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x04},
    {NCT6791D_HWM_DATA_PORT, 0xFE, 0x01},
    //SYSFANOUT PWM Output Frequency Configuration Register
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x00},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x04},
    //CPUFANOUT PWM Output Frequency Configuration Register 
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x02},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x04},
    //AUXFANOUT0 PWM Output Frequency Configuration Register 
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x10},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x04},
    //AUXFANOUT1 PWM Output Frequency Configuration Register 
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x12},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x04},
    //AUXFANOUT2 PWM Output Frequency Configuration Register 
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x14},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x04},
    //SMI mask
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x43},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0xFF},
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x44},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0xFF},
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x46},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x1E},
    
    //SMI/OVT setting >>
    //OVT# Configuration,Enable/Disable SMIOVT1#,mode select
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x18},
    {NCT6791D_HWM_DATA_PORT, 0xAE, 0x40},
    //SMI/OVT Control,Enable/Disable SMIOVT2,3, SMIOVT2~6 mode select
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x4C},
    {NCT6791D_HWM_DATA_PORT, 0x93, 0x00},

    //voltage limit setting >>
    //CPUVCORE High Limit
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x2b},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //CPUVCORE Low Limit
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x2c},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN0 High Limit 
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x2d},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN0 Low Limit 
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x2e},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //AVCC High Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x2f},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //AVCC Low Limit
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x30},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //3VCC High Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x31},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //3VCC Low Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x32},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN1 High Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x33},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN1 Low Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x34},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN8 High Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x35},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN8 Low Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x36},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //VIN4 High Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x37},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //VIN4 Low Limit  
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x38},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},
    //SMIOVT1 temperature sensor High Limit    
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x39},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x7F},
    //SMIOVT1 temperature sensor Hysteresis Limit    
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x3A},
    //{NCT6791D_HWM_DATA_PORT, 0x00, 0x00},

    //FAN IN/OUT Control
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x4D},
    {NCT6791D_HWM_DATA_PORT, 0x00, 0x55},
    //FAN IN/OUT Control    
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x50},
    {NCT6791D_HWM_DATA_PORT, 0xFC, 0x05},
    //VBAT Monitor Control,and AUXTIN/CPUTIN Sensor type selection
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x5D},
    {NCT6791D_HWM_DATA_PORT, 0xfC, 0x01 |(AUXTIN3_SENSOR<<6)|(AUXTIN2_SENSOR<<5)|(AUXTIN1_SENSOR<<4)\
                |(AUXTIN0_SENSOR<<3)|(CPUTIN_SENSOR<<2)|(SYSTIN_SENSOR<<1)|EN_VBAT_MNT},
    
    //Enable AUXTIN/CPUTIN Current Mode
    //{NCT6791D_HWM_INDEX_PORT, 0x00, 0x5E},
    //{NCT6791D_HWM_DATA_PORT, 0x81, 0x7E},

    //PECI Temperature Reading Enable for SMIOVT and SMART FAN Control 
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0xAE},
    {NCT6791D_HWM_DATA_PORT, 0xFC, 0x03},
    
    //Bank Select,bank 7
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x4E},
    {NCT6791D_HWM_DATA_PORT, 0xF0, 0x07},

    //PECI Enable Function
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x01},
    {NCT6791D_HWM_DATA_PORT, 0x78, (PECI_EN<<7)|(IS_PECI30<<2)|(MANUAL_EN<<1)|ROUTINE_EN},
    //Set PECI Agent Config
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x03},
    {NCT6791D_HWM_DATA_PORT, 0xFF, PECI_AGENT_CFG},
    //Tbase for PECI
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x09},
    {NCT6791D_HWM_DATA_PORT, 0x00, TBASE0},
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x0A},
    {NCT6791D_HWM_DATA_PORT, 0x00, TBASE1},
    
    //index4Eh bit[3-0] select bank number.
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x4E},
    {NCT6791D_HWM_DATA_PORT, 0xF0, 0x00},
    // Configuration Register,Enable SMI# and Start
    {NCT6791D_HWM_INDEX_PORT, 0x00, 0x40},
    {NCT6791D_HWM_DATA_PORT, 0x44, 0x03},
    #endif  // NCT6791D_HWM_PRESENT
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



