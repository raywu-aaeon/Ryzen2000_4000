
#include "Token.h"
#include <Library/IoLib.h>
#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
#include <AaeonIoPkg/IT8518/EcApiProtocol.c>
#endif

#ifndef API_WDT_Dev
#define API_WDT_Dev     0xA8
#endif
#ifndef API_WDT_Type
#define API_WDT_Type    0x00
#endif

#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
// IT8518GetGpio, IT8518SetGpio to be implemented.

VOID IT8518EnableWdt(UINT8 TimeUnit,UINT8 Time)
{
    UINT8 WDT_count;
    UINT8 WDT_Conf;  
    EcWriteByte(EcReg_Dev,API_WDT_Dev); //Setting Device
    EcWriteByte(EcReg_Type,API_WDT_Type); //Setting Type
    EcWriteByte(EcReg_Conf,CMD_Read); //Read Command
    API_Check();
    WDT_count = Time; // 5 units
    WDT_Conf = TimeUnit; // bit0, 0: Second.
                     // bit0, 1: Minute.
    EcWriteByte(EcReg_Dev,API_WDT_Dev); // Setting Device
    EcWriteByte(EcReg_Type,API_WDT_Type); // Setting Type
    EcWriteByte(EcReg_Dat0, 0); // Disable WDT
    // Set to zero will stop watchdog function.
    EcWriteByte(EcReg_Conf,CMD_Write); // Write start
    API_Check();

    EcWriteByte(EcReg_Dev,API_WDT_Dev); // Setting Device
    EcWriteByte(EcReg_Type,API_WDT_Type); // Setting Type
    EcWriteByte(EcReg_Dat0, WDT_count); // Setting watchdog timer
    // Set to zero will stop watchdog function.
    EcWriteByte(EcReg_Dat1, WDT_Conf); // Setting watchdog unit
    EcWriteByte(EcReg_Conf,CMD_Write); // Write start
    API_Check();
}

VOID IT8518DisableWdt()
{
    EcWriteByte(EcReg_Dev,API_WDT_Dev); // Setting Device
    EcWriteByte(EcReg_Type,API_WDT_Type); // Setting Type
    EcWriteByte(EcReg_Dat0, 0); // Disable WDT
    // Set to zero will stop watchdog function.
    EcWriteByte(EcReg_Conf,CMD_Write); // Write start
    API_Check();
}

UINT8 IT8518GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset)
{
    UINT8  Value=0;
    
    IoWrite8(IT8518_CONFIG_INDEX,IT8518_LDN_SEL_REGISTER);
    IoWrite8(IT8518_CONFIG_DATA,IOLDN);
    
    IoWrite8(IT8518_CONFIG_INDEX,RegisterOffset);
    Value = IoRead8(IT8518_CONFIG_DATA);
    
    return Value;
}
#endif
