//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file 
 * SioStaticSetup.c
 * Sub Module Strings override routines to dynamically change Setup.
**/ 
//**********************************************************************
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include <AmiGenericSio.h>
#include <AaeonIoSetup.h>
#include <Library/PrintLib.h>


/**
    This function will return the power raised to the base number.

    @param Base     Base number.
    @param Power    Power value.
     
    @retval Data    the power raised to the base number

**/ 
// The Pow() is referred to the SioStaticSetup.c of GenericSio_15
UINTN
Pow (UINT8 Base, UINT8 Power)
{
    UINT8   Index;
    UINTN   Data = 1;
    for(Index = 0;Index < Power;Index ++) {
        Data *= Base;
    }
    return Data;
}

/**
    Update option with the data read from register

        
    @param RegData data from SIO registers
    @param Func Fan Speed,Voltage and Temperature
    @param StrToken String token
    @param OddPos Odd position
    @param hiiHandle HII Handle

    @retval 
        Return string in Buffer

**/
// The AaeonHHMCommon() is referred to the SioStaticSetup.c of GenericSio_15
// The content in the AAEON_OVERRIDE tag is added by AAEON
VOID EFIAPI AaeonHHMCommon(
    IN      UINT64     RegData,
    IN      UINT8     Func,
    IN      UINT16    StrToken,
    IN      UINT8     OddPos,
    IN      EFI_HII_HANDLE    hiiHandle
) {
    INT64           NData;
    CHAR16          StrUpdated[100];
    UINTN           StrSize = 100;
    CHAR16          Leading[2];
    CHAR16          Tail[4];
    UINT64          IntData;
    UINT64          FloatData;

    NData = (INT64)(RegData);
    StrCpy(Leading, L"+");
    // >> AAEON_OVERRIDE
    if((Func == TEMPERATURE) && ((INT8)NData < 0)) // If the data is temperature and the sign bit is "1", define minus data
    {
        NData = -(INT8)NData;     //Convert minus data
        StrCpy(Leading, L"-");
    }    
    // << AAEON_OVERRIDE
    //add negative value handle
    if(NData<0) {
        NData = -NData;
        StrCpy(Leading, L"-");
    }

    switch(Func) {
    case    VOLTAGE:                       //Indicate it's voltage
        StrCpy(Tail, L"V");
        break;
    case    TEMPERATURE:                   //Indicate it's Temperature
        StrCpy(Tail, L"\x2103");
        break;
    case    FAN_SPEED:                     //Indicate it's fan
        StrCpy(Tail, L"RPM");
        StrCpy(Leading, L"");
        break;
    default :                              
        break;
    }
    //When device not present, update to 'N/A'
    if(NData == 0x00) {
        StrCpy(StrUpdated, L": N/A     ");
    }
    else {
        if(OddPos) {
            FloatData = NData % Pow(10, OddPos);
            IntData = NData / Pow(10, OddPos);
            UnicodeSPrint(StrUpdated, StrSize, L": %s%d.%0*d %s", Leading, IntData, OddPos, FloatData, Tail);
        }
        else {
            IntData = NData;
            UnicodeSPrint(StrUpdated, StrSize, L": %s%d %s", Leading, IntData, Tail);
        }
    }
    
    InitString(hiiHandle, StrToken, StrUpdated);

    return;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2014, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**        5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093         **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
