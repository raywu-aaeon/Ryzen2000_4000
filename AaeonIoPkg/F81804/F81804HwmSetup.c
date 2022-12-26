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
/** @file F81804HwmSetup.c
  This is related to individual HWM devices.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SioSetup.h>
#include "AaeonIoSetup.h"
////////////////////////////////////////////////////////////////////////
////////////OEM PORTING REQUIRED/////////////OEM PORTING REQUIRED///////
////////////////////////////////////////////////////////////////////////
/**
  Get the register value form HWM space register.

  @param  BankNo            Bank Select
  @param  Register          Register who content the wanted value
  @param  Value         Pointer to register value
**/
void
GetValueWithIO (
    IN UINT8 BankNo,
    IN UINT8 Register,
    OUT UINTN *Value
)
{

    // Enter Bank NO!

    //Read the data from register
    IoWrite8(F81804_HWM_INDEX_PORT, Register);
    *Value = IoRead8(F81804_HWM_DATA_PORT);
    return;
}
#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
void AaeonCpuCoreTemperatureDetection(IN OUT HWM_DATA * Data)
{
    UINTN   T1;
    
    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP1_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    #if defined(INTEL_DTS_SUPPORT) && (INTEL_DTS_SUPPORT)
    {
        #ifndef EFI_MSR_CPU_THERM_TEMPERATURE
        #define EFI_MSR_CPU_THERM_TEMPERATURE 0x1A2
        #endif
        #ifndef EFI_MSR_IA32_CR_THERM_STATUS
        #define EFI_MSR_IA32_CR_THERM_STATUS 0x19C
        #endif

        extern UINT64 ReadMsr(UINT32 Msr);
        
        EFI_STATUS Status = EFI_SUCCESS;
        UINT8 RegTmp8, TjMax;
        UINT64 RegTmp64;
        
        TjMax = (UINT8)(ReadMsr(EFI_MSR_CPU_THERM_TEMPERATURE) >> 16);
        RegTmp64 = ReadMsr(EFI_MSR_IA32_CR_THERM_STATUS);
        RegTmp8 = (UINT8)TjMax - (UINT8)((RegTmp64 >> 16) & 0x7F);
        
        T1 = (UINTN)RegTmp8;
    }
    #endif //INTEL_DTS_SUPPORT


    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}
#endif //AAEON_CPU_CORE_TEMP_DETECTION
/**
  Get the register value form HWM voltage space register.

  @param  Vol_Value         voltage parameter.
  @param  Vol_Unit          voltage lsb unit.
  @param  R_B               divisor bigger resitor.
  @param  R_S               divisor smaller resitor.

  @return the voltage value.
**/
UINTN VOL_DIVISOR_CALCULATE (
    IN UINTN Vol_Value,
    IN UINTN Vol_Unit,
    IN UINTN R_B,
    IN UINTN R_S
)
{
    UINTN       OutBuffer=0;
    if((R_B != 0) && (R_S != 0)) { //it use resistor divisor
        OutBuffer = Vol_Value * Vol_Unit * (R_B + R_S)/R_S;
    } else { //it don't use resistor divisor
        OutBuffer = Vol_Value * Vol_Unit;
    }

    return OutBuffer;
}

/**
  Get the first system temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature1(
    IN OUT HWM_DATA * Data
)
{
    UINTN      TData;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP1_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x70,&TData); // Bank0 Register 0x70.
    if(TData ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)TData;

    return;
}

/**
  Get the second system temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature2 (
    IN OUT HWM_DATA * Data
)
{
    UINTN       TData;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP2_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x72,&TData); // Bank0 Register 0x72.
    if(TData ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)TData;

    return;
}

/**
  Get the third system temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature3 (
    IN OUT HWM_DATA * Data
)
{
    UINTN       TData;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP3_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x74,&TData); // Bank0 Register 0x74.
    if(TData ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)TData;

    return;
}

/**
  Get the first FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateFan1Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed;
    UINTN       Divisor;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN1_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0xA0,&Speed); //  Register 0xA0
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x00,0xA1,&Speed); //  Register 0xA1
    Divisor |= (UINT8) Speed;
    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)1500000/Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}
void
GetAndUpdateFan2Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed;
    UINTN       Divisor;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN2_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0xC0,&Speed); //  Register 0xC0
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x00,0xC1,&Speed); //  Register 0xC1
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)1500000/Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}

/**
  Get the VIN1 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN1Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN   Ra = VIN1_RA;
    UINTN   Rb = VIN1_RB;
    
    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x21,&VData) ; // Register 0x21
    VData = VData*8*(Ra+Rb)/Rb;
    
    Data->Value = (UINT16)VData;

    return;

}

/**
  Get the VIN2 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN2Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN   Ra = VIN2_RA;
    UINTN   Rb = VIN2_RB;
    
    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x22,&VData) ; // Register 0x22
    Data->Value = VData*8*(Ra+Rb)/Rb;
    return;
}
/**
  Get the VIN3 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN3Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x23,&VData) ; // Register 0x23
    VData = VData*8;
    Data->Value = (UINT16)VData;

    return;
}

/**
  Get the VIN4 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN4Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN4_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x24,&VData) ; // Register 0x24
    VData = VData*8*(100+100)/100;
    Data->Value = (UINT16)VData;

    return;
}

/**
  Get the VSB5 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVSB5VVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;

    Data->Token = STRING_TOKEN(STR_HWM1_VSB5V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x27,&VData) ; // Register 0x27
    VData = VData*8*3;
    Data->Value = (UINT16)VData;

    return;
}

/**
  Get the VCC3V voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVCC3VVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;

    Data->Token = STRING_TOKEN(STR_HWM1_VCC3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x20,&VData) ;  // Register 0x20
    VData = VData * 8 * 2;

    Data->Value = (UINT16)VData;

    return;
}

/**
  Get the VSB3V voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVSB3VVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;

    Data->Token = STRING_TOKEN(STR_HWM1_VSB3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x25,&VData) ; // Register 0x25
    VData = VData * 8 * 2 ;

    Data->Value = (UINT16)VData;

    return;
}

/**
  Get the VBAT voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVBATVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;

    Data->Token = STRING_TOKEN(STR_HWM1_VBAT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x26,&VData) ; // Register 0x26
    VData = VData*8*2;
    Data->Value = (UINT16)VData;

    return;
}

///---------------------------------------------------------------------
///All Callback Functions List.
///---------------------------------------------------------------------
SIO_EXTERNAL_FUN *F81804ExternalFunList[] = {
#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
AaeonCpuCoreTemperatureDetection,
GetAndUpdateTemperature2,
#else
    GetAndUpdateTemperature1,
    GetAndUpdateTemperature2,
#endif //AAEON_CPU_CORE_TEMP_DETECTION
    GetAndUpdateTemperature3,
    GetAndUpdateFan1Speed,
    GetAndUpdateFan2Speed,
    GetAndUpdateVIN1Voltage,
    GetAndUpdateVIN2Voltage,
    GetAndUpdateVIN3Voltage,
    GetAndUpdateVIN4Voltage,
    GetAndUpdateVSB5VVoltage,
    GetAndUpdateVCC3VVoltage,
    GetAndUpdateVSB3VVoltage,
    GetAndUpdateVBATVoltage,
    NULL
};

/**
  Form Callback Function. Will be called every 100m Polling for data Updates.

  @param  HiiHandle              A handle that was previously registered in the HII Database.
  @param  Class                  Indicates the setup class.
  @param  SubClass               Indicates the setup subclass
  @param  Key                    Id of setup control.
**/
VOID F81804_HWM_CallBack(
    IN EFI_HII_HANDLE               HiiHandle,
    IN UINT16                       Class,
    IN UINT16                       SubClass,
    IN UINT16                       Key
)
{
    UINTN    index;
    HWM_DATA Data;
    CALLBACK_PARAMETERS *Callback = NULL;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return;

    for(index=0; F81804ExternalFunList[index]; index++) {
        F81804ExternalFunList[index](&Data);
        AaeonHHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
    }

    return;
}

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

