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
// Name:  <F81216SECPeiIoTable.h>
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
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include "token.h"
#include <Library/AmiSioPeiLib.h>

IO_DECODE_DATA F81216SECPeiDecodeTable[]= {
    // -----------------------------
    //|  BaseAdd | UID  | Type |
    // -----------------------------
    {F81216SEC_CONFIG_INDEX, 2, 0xFF},
    //Below decode is for recovery mode

    // !!!!Attention!!!!This is necessary
    //OEM_TODO//OEM_TODO//OEM_TODO//OEM_TODO
    // If your com port number > 2 , you'd add more table for more com ports.
    {0x240, 0x40, 0xFF}, // 0x240~0x27f     // Add more OEM IO decode below.
};

SIO_DEVICE_INIT_DATA F81216SECPeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //---------------------------------------------------------------------
    // Enter Configuration Mode.
    //---------------------------------------------------------------------
    {F81216SEC_CONFIG_INDEX, 0x00, F81216SEC_CONFIG_MODE_ENTER_VALUE},
    {F81216SEC_CONFIG_INDEX, 0x00, F81216SEC_CONFIG_MODE_ENTER_VALUE},
    //---------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------

    {F81216SEC_CONFIG_INDEX, 0x00, 0x25},
    {F81216SEC_CONFIG_DATA,  0xFE, F81216SEC_CLOCK},
    //---------------------------------------------------------------------
    // Initialize the Serial Port for debug useage. Default is COMA
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //---------------------------------------------------------------------
    //---------------------------------------------------------------------
    //Disable Non-Used Device in Pei Phase,if its default value is actived.
    //---------------------------------------------------------------------
    // Seclect device WDT
    {F81216SEC_CONFIG_INDEX, 0x00, F81216SEC_LDN_SEL_REGISTER},
    {F81216SEC_CONFIG_DATA,  0x00, F81216SEC_LDN_WDT},
    // Clear Interrupt
    {F81216SEC_CONFIG_INDEX, 0x00, F81216SEC_IRQ1_REGISTER},
    {F81216SEC_CONFIG_DATA,  0x00, 0x00},
    // Deactivate Device
    {F81216SEC_CONFIG_INDEX, 0x00, F81216SEC_ACTIVATE_REGISTER},
    {F81216SEC_CONFIG_DATA,  0x00, F81216SEC_DEACTIVATE_VALUE},

    //---------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //---------------------------------------------------------------------
    {F81216SEC_CONFIG_INDEX, 0x00, F81216SEC_CONFIG_MODE_EXIT_VALUE},
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


