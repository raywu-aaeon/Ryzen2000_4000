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
/** @file IT8625HwmSetup.c
  This is related to individual HWM devices.
**/

//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SioSetup.h>
#include <AaeonIoSetup.h>

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
    UINT8       temp;

    // Enter Bank NO!
    IoWrite8(IT8625_HWM_INDEX_PORT, 0x06);
    temp = IoRead8(IT8625_HWM_DATA_PORT);
    temp &= 0x9F ;// BIT6-5: BANK_SEL
    IoWrite8(IT8625_HWM_DATA_PORT, (temp | BankNo << 5));

    //Read the data from register
    IoWrite8(IT8625_HWM_INDEX_PORT, Register);
    *Value = IoRead8(IT8625_HWM_DATA_PORT);
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

#if defined(AAEON_CPU_DTS_READING) && (AAEON_CPU_DTS_READING)
//-------------------------------------------------------------------------
// Procedure:   AaeonCpuDtsReading
//
// Description:
//  Get the CPU DTS temperature value in CPU MSR register and update to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
#ifndef EFI_MSR_CPU_THERM_TEMPERATURE
  #define EFI_MSR_CPU_THERM_TEMPERATURE 0x1A2
#endif // EFI_MSR_CPU_THERM_TEMPERATURE
#ifndef EFI_MSR_IA32_CR_THERM_STATUS
  #define EFI_MSR_IA32_CR_THERM_STATUS 0x19C
#endif // EFI_MSR_IA32_CR_THERM_STATUS
extern UINT64 ReadMsr(UINT32 Msr);

void AaeonCpuDtsReading(IN OUT HWM_DATA * Data)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 RegTmp8, TjMax;
    UINT64 RegTmp64;
    UINTN   T1;
    
    Data->Token = STRING_TOKEN(STR_HWM_CPU_DTS_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;
   
    TjMax = (UINT8)(ReadMsr(EFI_MSR_CPU_THERM_TEMPERATURE) >> 16);
    RegTmp64 = ReadMsr(EFI_MSR_IA32_CR_THERM_STATUS);
    RegTmp8 = (UINT8)TjMax - (UINT8)((RegTmp64 >> 16) & 0x7F);

    T1 = (UINTN)RegTmp8;

    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}
#endif //AAEON_CPU_DTS_READING

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
    GetValueWithIO(0x00,0x29,&T1); // Bank0 Register 0x29.
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
    GetValueWithIO(0x00,0x2A,&T1); // Bank0 Register 0x2A.
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
    GetValueWithIO(0x00,0x2B,&T1); // Bank0 Register 0x2B.
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
    GetValueWithIO(0x00,0x2C,&T1); // Bank0 Register 0x2C.
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
    GetValueWithIO(0x00,0x2D,&T1); // Bank0 Register 0x2D.
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
    GetValueWithIO(0x00,0x2E,&T1); // Bank0 Register 0x2E.
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
    UINTN       Speed1, Speed2;
    UINTN       Divisor = 0x02;
    Data->Token = STRING_TOKEN(STR_HWM1_FAN1_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x18,&Speed1);  //  Register 0x18
    GetValueWithIO(0x00,0x0D,&Speed2);  //  Register 0x0D
    
    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

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
    UINTN       Speed1, Speed2;
    UINTN       Divisor = 0x02;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN2_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x19,&Speed1);  //  Register 0x19
    GetValueWithIO(0x00,0x0E,&Speed2);  //  Register 0x0E

    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

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
    UINTN       Speed1, Speed2;
    UINTN       Divisor = 0x02;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN3_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x1A,&Speed1);  //  Register 0x1A
    GetValueWithIO(0x00,0x0F,&Speed2);  //  Register 0x0F

    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

    return;
}


/**
  Get the fourth FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateFan4Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed1, Speed2;
    UINTN       Divisor = 0x02;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN4_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x81,&Speed1);  //  Register 0x81
    GetValueWithIO(0x00,0x80,&Speed2);  //  Register 0x80

    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

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
    UINTN       Speed1, Speed2;
    UINTN       Divisor = 0x02;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN5_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x83,&Speed1);  //  Register 0x83
    GetValueWithIO(0x00,0x82,&Speed2);  //  Register 0x82

    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

    return;
}


/**
  Get the sixth FAN speed value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateFan6Speed (
    IN OUT HWM_DATA * Data
)
{
    UINTN       Speed1, Speed2;
    UINTN       Divisor = 0x02;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN6_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x94,&Speed1);  //  Register 0x94
    GetValueWithIO(0x00,0x93,&Speed2);  //  Register 0x93

    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

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
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_IT8625_HMM_VIN0_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x20,&VData) ; // Register 0x20
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN0_RA;
    R_Small = VIN0_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
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
    UINTN       VData;
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x21,&VData) ; // Register 0x21
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN1_RA;
    R_Small = VIN1_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
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
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x22,&VData) ; // Register 0x22
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN2_RA;
    R_Small = VIN2_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
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
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x23,&VData) ; // Register 0x23

    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN3_RA;
    R_Small = VIN3_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
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
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN4_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x24,&VData) ; // Register 0x24
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN4_RA;
    R_Small = VIN4_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
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
    UINTN       VData;
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN5_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x25,&VData) ; // Register 0x25
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN5_RA;
    R_Small = VIN5_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}

/**
  Get the VIN6 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVIN6Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN6_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x26,&VData) ; // Register 0x26
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    // >> AAEON_OVERRIDE
    R_Big = VIN6_RA;
    R_Small = VIN6_RB;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    // << AAEON_OVERRIDE
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}

/**
  Get the VSB3 voltage value in HWM space register and update to HII.

  @param  Data         data for HWM HII.
**/
void
GetAndUpdateVSB3VVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VSB3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x27,&VData) ; //bank0 Register 0x27
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
    // >> AAEON_OVERRIDE (The multiplier is already in divisor resistor)
    //Data->Value = (UINT16)VData*2;
    Data->Value = (UINT16)VData;
    // << AAEON_OVERRIDE

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
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VBAT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x28,&VData) ; //bank0 Register 0x28
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
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
    UINTN       Lsb_Unit=11;//AMI_TODO:LSB unit is 10.9mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VCC3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x2F,&VData) ; //bank0 Register 0x2F
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    Lsb_Unit = 109; // 10.9mv * 10 (For excluding the float-point)
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    VData /= 10;    // Revert for float point of the unit
    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}

///---------------------------------------------------------------------
///All Callback Functions List.
///---------------------------------------------------------------------
SIO_EXTERNAL_FUN *IT8625ExternalFunList[] = {
    #if defined(AAEON_CPU_DTS_READING) && (AAEON_CPU_DTS_READING)
    AaeonCpuDtsReading,
    #endif //AAEON_CPU_DTS_READING
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
    GetAndUpdateFan6Speed,
    GetAndUpdateVIN0Voltage,
    GetAndUpdateVIN1Voltage,
    GetAndUpdateVIN2Voltage,
    GetAndUpdateVIN3Voltage,
    GetAndUpdateVIN4Voltage,
    GetAndUpdateVIN5Voltage,
    GetAndUpdateVIN6Voltage,
    GetAndUpdateVSB3VVoltage,
    GetAndUpdateVBATVoltage,
    GetAndUpdateVCC3VVoltage,
    NULL
};

/**
  Form Callback Function. Will be called every 100m Polling for data Updates.

  @param  HiiHandle              A handle that was previously registered in the HII Database.
  @param  Class                  Indicates the setup class.
  @param  SubClass               Indicates the setup subclass
  @param  Key                    Id of setup control.
**/
VOID IT8625_HWM_CallBack(
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

    for(index=0; IT8625ExternalFunList[index]; index++) {
        IT8625ExternalFunList[index](&Data);
    // >> AAEON_OVERRIDE
    //    HHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
        AaeonHHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
    // << AAEON_OVERRIDE
    }

    return;
}

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
