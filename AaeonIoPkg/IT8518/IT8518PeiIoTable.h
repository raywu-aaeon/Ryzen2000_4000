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
// Name:  <IT8518PeiIoTable.h>
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
#ifndef _IT8518PeiIoTable_H_
#define _IT8518PeiIoTable_H_

#ifdef __cplusplus
extern "C" {
#endif
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA IT8518PeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {IT8518_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode
#if (defined(Recovery_SUPPORT) && (SerialRecovery_SUPPORT))
#if (IT8518_SERIAL_PORT1_PRESENT)
    {IT8518_SERIAL_PORT1_BASE_ADDRESS, 0x01, dsUART},
#endif
#endif
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (IT8518_KEYBOARD_PRESENT)
    {0x60, 0, dsPS2K},                                  // KBC decode
#endif
#endif
    //Below decode is for SIO generic IO decode
#if defined(IT8518_TOTAL_BASE_ADDRESS) && (IT8518_TOTAL_BASE_ADDRESS != 0)
    {IT8518_TOTAL_BASE_ADDRESS, IT8518_TOTAL_LENGTH, 0xFF},
#endif
    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    // Add more OEM IO decode below.
#if (IT8518_CIR_PORT_PRESENT)
    {0x3E0, 0x10, 0xFF},//for CIR
#endif
};

SIO_DEVICE_INIT_DATA IT8518PeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------
    {IT8518_CONFIG_INDEX, 0x00, 0x23},//Super IO all device software reset or enable/disable
    {IT8518_CONFIG_DATA,  0xFE, 0x00 | SIOEN},

    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------



    //---------------------------------------------------------------------
    // Initialize the KeyBoard and floppy controller for Recovery
    //---------------------------------------------------------------------
#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT)
#if (IT8518_KEYBOARD_PRESENT)
    // Seclect device KEYBOARD
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PS2K},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x60},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x64},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x01},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_ACTIVATE_VALUE},
#else
    // Deactivate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PS2K},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_KEYBOARD_PRESENT
#endif //#if defined(Recovery_SUPPORT) && (Recovery_SUPPORT == 1)
    //---------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //---------------------------------------------------------------------
#if (IT8518_SWUC_PRESENT)
    // Seclect device SWUC
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_SWUC},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_TOTAL_BASE_ADDRESS & 0x00FF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_TOTAL_BASE_ADDRESS >> 8)},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_SWUC_PRESENT
#if (IT8518_SMFI_PRESENT)
    // Seclect device SMFI
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_SWUC},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x10) & 0x00FF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x10) >> 8)},
    // Program H2RAM-HLPC BASE ADDRESS
    {IT8518_CONFIG_INDEX, 0x00, 0XF5},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, 0xF6},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_SMFI_PRESENT
#if (IT8518_BRAM_PRESENT)
    // Seclect device BRAM
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_BRAM},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x20) & 0x00FF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x20) >> 8)},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_BRAM_PRESENT
#if (IT8518_PMC1_PRESENT)
    // Seclect device PMC1
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PMC1},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_PMC1_PRESENT
#if (IT8518_PMC2_PRESENT)
    // Seclect device PMC2
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PMC2},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},//IO Port base address high byte for descriptor0
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},//IO Port base address low byte for descriptor0
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},//IO Port base address high byte for descriptor1
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},//IO Port base address low byte for descriptor1
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, 0X64},//IO Port base address high byte for descriptor2
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, 0X65},//IO Port base address low byte for descriptor2
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_PMC2_PRESENT
#if (IT8518_PMC3_PRESENT)
    // Seclect device PMC3
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PMC3},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},//IO Port base address high byte for descriptor0
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},//IO Port base address low byte for descriptor0
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},//IO Port base address high byte for descriptor1
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},//IO Port base address low byte for descriptor1
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_PMC3_PRESENT
#if (IT8518_PMC4_PRESENT)
    // Seclect device PMC4
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PMC4},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},//IO Port base address high byte for descriptor0
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},//IO Port base address low byte for descriptor0
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},//IO Port base address high byte for descriptor1
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},//IO Port base address low byte for descriptor1
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_PMC4_PRESENT
#if (IT8518_SSPI_PRESENT)
    // Seclect device SSPI
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_SSPI},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x30) & 0x00FF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x30) >> 8)},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_SSPI_PRESENT
#if (IT8518_PECI_PRESENT)
    // Seclect device PECI
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_PECI},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x40) & 0x00FF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)((IT8518_TOTAL_BASE_ADDRESS+0x40) >> 8)},
    // Program Interrupt
    {IT8518_CONFIG_INDEX, 0x00, IT8518_IRQ1_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_DEACTIVATE_VALUE},
#endif //IT8518_PECI_PRESENT    
    //---------------------------------------------------------------------
    //Disable Non-Used Device in Pei Phase,if its default value is actived.
    //---------------------------------------------------------------------
    // Seclect device CIR
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_CIR},
    // Clear Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, 0x00},
    //---------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------

//    #if (IT8518_SERIAL_PORT1_PRESENT)|(IT8518_DBG_SUPPORT)
    // Select device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_UART1},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_SERIAL_PORT1_BASE_ADDRESS & 0xFF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE1_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_SERIAL_PORT1_BASE_ADDRESS >> 8)},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_ACTIVATE_VALUE},
//    #endif

    
//    #if (IT8518_SERIAL_PORT2_PRESENT)
    // Select device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_LDN_SEL_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_LDN_UART2},
    // Program Base Addr
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_LO_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_SERIAL_PORT2_BASE_ADDRESS & 0xFF)},
    {IT8518_CONFIG_INDEX, 0x00, IT8518_BASE2_HI_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, (UINT8)(IT8518_SERIAL_PORT2_BASE_ADDRESS >> 8)},
    // Activate Device
    {IT8518_CONFIG_INDEX, 0x00, IT8518_ACTIVATE_REGISTER},
    {IT8518_CONFIG_DATA,  0x00, IT8518_ACTIVATE_VALUE},
//    #endif    

    
    
    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
};
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_IT8518PeiIoTable_H_
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
