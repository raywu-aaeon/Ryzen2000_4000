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
/** @file NCT5538DHwmSetup.c
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
    UINT8   temp;
    //Enter Bank NO!
    IoWrite8(NCT5538D_HWM_INDEX_PORT, 0x4E);
    temp = IoRead8(NCT5538D_HWM_DATA_PORT);
    temp &= 0xF0 ;
    IoWrite8(NCT5538D_HWM_DATA_PORT, (temp | BankNo));
    //Read the data from register
    IoWrite8(NCT5538D_HWM_INDEX_PORT, Register);
    *Value = IoRead8(NCT5538D_HWM_DATA_PORT);
    return;
}

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
// >> 2016/07/19 AAEON_OVERRIDE
void
GetAndUpdateTemperature0(
    IN OUT HWM_DATA * Data
)
{
    UINTN      T1;

    Data->Token = STRING_TOKEN(STR_HWM_CPU_DTS_TEMP_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x07, 0x20, &T1); //Bank7, index20: PECI Temperature reading
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}
// << 2016/07/19 AAEON_OVERRIDE

/**
  Get the first system temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature1(
    IN OUT HWM_DATA * Data
)
{
    UINTN      T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP1_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x90,&T1); // Bank4 Register 0x90.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

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
    UINTN       T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP2_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x91,&T1); // Bank4 Register 0x91.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

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
    UINTN       T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP3_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x92,&T1); // Bank4 Register 0x92.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

/**
  Get the first fourth temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature4 (
    IN OUT HWM_DATA * Data
)
{
    UINTN       T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP4_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x93,&T1); // Bank4 Register 0x93.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

/**
  Get the fifth system temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature5 (
    IN OUT HWM_DATA * Data
)
{
    UINTN       T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP5_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x94,&T1); // Bank4 Register 0x94.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

/**
  Get the sixth system temperature value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateTemperature6 (
    IN OUT HWM_DATA * Data
)
{
    UINTN       T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP6_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x95,&T1); // Bank4 Register 0x95.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

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
    GetValueWithIO(0x04,0xC0,&Speed); //  Register 0xC0
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x04,0xC1,&Speed); //  Register 0xC1
    Divisor |= (UINT8) Speed;
    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}

/**
  Get the second FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
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
    GetValueWithIO(0x04,0xC2,&Speed); //  Register 0xC2
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x04,0xC3,&Speed); //  Register 0xC3
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)Divisor;
    }

    Data->Value = (UINT16)Speed;

    return;
}

/**
  Get the third FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateFan3Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed;
    UINTN       Divisor;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN3_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC4,&Speed); //  Register 0xC4
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x04,0xC5,&Speed); //  Register 0xC5
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}

/**
  Get the forth FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateFan4Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed;
    UINTN       Divisor;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN4_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC6,&Speed); //  Register 0xC6
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x04,0xC7,&Speed); //  Register 0xC7
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}

/**
  Get the fifth FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateFan5Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed;
    UINTN       Divisor;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN5_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xB8,&Speed); //  Register 0xB8
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x04,0xB9,&Speed); //  Register 0xB9
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)1350000/Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}

/**
  Get the VIN0 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN0Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
// >> 2016/07/19 AAEON_OVERRIDE
//    UINTN       R_Big=34;   //AMI_TODO:Connect bigger divisor resistor
//    UINTN       R_Small=34; //AMI_TODO:Connect smaller divisor resistor
// << 2016/07/19 AAEON_OVERRIDE

    Data->Token = STRING_TOKEN(STR_NCT5538D_HMM_VIN0_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x84,&VData) ; // Register 0x84
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=10;
    //R_Small=10;
    //calculate voltage value
// >> 2016/07/19 AAEON_OVERRIDE
//    VData = VOL_DIVISOR_CALCULATE (VData,
//                                   Lsb_Unit,
//                                   R_Big,
//                                   R_Small);
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   VIN0_R1,
                                   VIN0_R2);
// << 2016/07/19 AAEON_OVERRIDE

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
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
    UINTN       VIN1;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x81,&VIN1) ; // Register 0x81
// >> 2016/07/19 AAEON_OVERRIDE
//    VIN1 = VIN1*8;
    VIN1 = VIN1 * 8 * (VIN1_R1 + VIN1_R2) / VIN1_R2;
// << 2016/07/19 AAEON_OVERRIDE

    Data->Value = (UINT16)VIN1;

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
    UINTN       VIN2;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8C,&VIN2) ; // Register 0x8C
    VIN2 = VIN2*8*(20+47)/47;
    Data->Value = (UINT16)VIN2;

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
    UINTN       VIN3;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8D,&VIN3) ; // Register 0x8D
    VIN3 = VIN3*8;
    Data->Value = (UINT16)VIN3;

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
    UINTN       VIN4;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN4_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x86,&VIN4) ; // Register 0x86
    VIN4 = VIN4*8*(100+100)/100;
    Data->Value = (UINT16)VIN4;

    return;
}

/**
  Get the VIN5 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN5Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN4;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN5_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8A,&VIN4) ; // Register 0x8A
    VIN4 = VIN4*8*(100+100)/100;
    Data->Value = (UINT16)VIN4;

    return;
}

/**
  Get the VIN5 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN6Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN4;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN6_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8B,&VIN4) ; // Register 0x8B
    VIN4 = VIN4*8*(100+100)/100;
    Data->Value = (UINT16)VIN4;

    return;
}

/**
  Get the VIN5 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN7Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN4;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN7_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8E,&VIN4) ; // Register 0x8E
    VIN4 = VIN4*8*(100+100)/100;
    Data->Value = (UINT16)VIN4;

    return;
}

/**
  Get the AVCC voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateAVCCVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       AVCC;

    Data->Token = STRING_TOKEN(STR_NCT5538D_HWM_AVCC_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x82,&AVCC) ; // Register 0x82
    AVCC = AVCC*8*2;
    Data->Value = (UINT16)AVCC;

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
    UINTN       VCC3V;

    Data->Token = STRING_TOKEN(STR_HWM1_VCC3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x83,&VCC3V) ;  // Register 0x83
    VCC3V = VCC3V * 8 * 2;

    Data->Value = (UINT16)VCC3V;

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
    UINTN       VSB3V;

    Data->Token = STRING_TOKEN(STR_HWM1_VSB3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x87,&VSB3V) ; // Register 0x87
    VSB3V = VSB3V * 8 * 2 ;

    Data->Value = (UINT16)VSB3V;

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
    UINTN       VBAT;

    Data->Token = STRING_TOKEN(STR_HWM1_VBAT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x88,&VBAT) ; // Register 0x88
    VBAT = VBAT*8*2;
    Data->Value = (UINT16)VBAT;

    return;
}

/**
  Get the VTT voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVTTVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VTT;

    Data->Token = STRING_TOKEN(STR_NCT5538D_HWM_VTT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x89,&VTT) ; // Register 0x89
    VTT = VTT*8*2;
    Data->Value = (UINT16)VTT;

    return;
}

/**
  Get the CPUVCORE voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateCPUVCOREVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       CPUVCORE;

    Data->Token = STRING_TOKEN(STR_NCT5538D_HWM_CPUVCORE_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x80,&CPUVCORE) ; // Register 0x80
    CPUVCORE = CPUVCORE*8*2;
    Data->Value = (UINT16)CPUVCORE;

    return;
}

/**
  Get the VCOREREFIN voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVCOREREFINVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VCOREREFIN;

    Data->Token = STRING_TOKEN(STR_NCT5538D_HWM_VCOREREFIN_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x85,&VCOREREFIN) ; // Register 0x85
    VCOREREFIN = VCOREREFIN*8*2;
    Data->Value = (UINT16)VCOREREFIN;

    return;
}

///---------------------------------------------------------------------
///All Callback Functions List.
///---------------------------------------------------------------------
SIO_EXTERNAL_FUN *NCT5538DExternalFunList[] = {
    GetAndUpdateTemperature0,   // AAEON_OVERRIDE +
    GetAndUpdateTemperature1,
    GetAndUpdateTemperature2,
    GetAndUpdateTemperature3,
    GetAndUpdateTemperature4,
    GetAndUpdateTemperature5,
    GetAndUpdateTemperature6,
    GetAndUpdateFan1Speed,
    GetAndUpdateFan2Speed,
    GetAndUpdateFan3Speed,
    GetAndUpdateFan4Speed,
    GetAndUpdateFan5Speed,
    GetAndUpdateVIN0Voltage,
    GetAndUpdateVIN1Voltage,
    GetAndUpdateVIN2Voltage,
    GetAndUpdateVIN3Voltage,
    GetAndUpdateVIN4Voltage,
    GetAndUpdateVIN5Voltage,
    GetAndUpdateVIN6Voltage,
    GetAndUpdateVIN7Voltage,
    GetAndUpdateAVCCVoltage,
    GetAndUpdateVCC3VVoltage,
    GetAndUpdateVSB3VVoltage,
    GetAndUpdateVBATVoltage,
    GetAndUpdateVTTVoltage,
    GetAndUpdateCPUVCOREVoltage,
    GetAndUpdateVCOREREFINVoltage,
    NULL
};

/**
  Form Callback Function. Will be called every 100m Polling for data Updates.

  @param  HiiHandle              A handle that was previously registered in the HII Database.
  @param  Class                  Indicates the setup class.
  @param  SubClass               Indicates the setup subclass
  @param  Key                    Id of setup control.
**/
VOID NCT5538D_HWM_CallBack(
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

    for(index=0; NCT5538DExternalFunList[index]; index++) {
        NCT5538DExternalFunList[index](&Data);
        AaeonHHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
    }

    return;
}

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


