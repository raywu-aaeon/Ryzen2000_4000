#ifndef _F75113PeiIoTable_H_
#define _F75113PeiIoTable_H_

#ifdef __cplusplus
extern "C" {
#endif
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <Token.h>
#include <Library/AmiSioPeiLib.h>

///---------------------------------------------------------------------
///Init table for PEI phase.
///---------------------------------------------------------------------
SIO_DEVICE_INIT_DATA F75113PeiInitTable[]= {
    // -----------------------------
    //|  Addr | DataMask  | DataValue |
    // -----------------------------

    //------------------------------------------------------------------
    // Enter Configuration Mode.
    //------------------------------------------------------------------
    {F75113_CONFIG_INDEX, 0x00, F75113_CONFIG_MODE_ENTER_VALUE},
    {F75113_CONFIG_INDEX, 0x00, F75113_CONFIG_MODE_ENTER_VALUE},

    //------------------------------------------------------------------
    // Before init all logical devices, program Global register if needed.
    //------------------------------------------------------------------
    // Select device
    {F75113_CONFIG_INDEX, 0x00, F75113_LDN_SEL_REGISTER},
    {F75113_CONFIG_DATA,  0x00, F75113_LDN_GLOBLE},
    // Base Address Enable
    {F75113_CONFIG_INDEX, 0x00, F75113_ACTIVATE_REGISTER},
    {F75113_CONFIG_DATA,  0x00, F75113_ACTIVATE_VALUE},

    //------------------------------------------------------------------
    // Program and initialize some logical device if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices, program Global register if needed.
    //------------------------------------------------------------------

    //------------------------------------------------------------------
    // After init all logical devices,  Exit Configuration Mode.
    //------------------------------------------------------------------
    {F75113_CONFIG_INDEX, 0x00, F75113_CONFIG_MODE_EXIT_VALUE},
};

///---------------------------------------------------------------------
///The PEI init table count.
///---------------------------------------------------------------------
UINT8 F75113PeiInitTableCount = sizeof(F75113PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif //_F75113PeiIoTable_H_


