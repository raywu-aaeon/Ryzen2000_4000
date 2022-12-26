//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//*************************************************************************
//<AMI_FHDR_START>
//
// Name:  <IT8728FSetup.c>
//
// Description: This is related to individual HWM devices.
//
//<AMI_FHDR_END>
//*************************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SioSetup.h>
#include "AaeonIoSetup.h"
//-------------------------------------------------------------------------
// Constants, Macros and Type Definitions
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
////////////OEM PORTING REQUIRED/////////////OEM PORTING REQUIRED/////////////
//////////////////////////////////////////////////////////////////////////////
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     TEMP_DECIMAL_TO_INTEGER
//
// Description:
//  Get the register value form HWM space register.
//
// Input:
//    IN UINTN Int_Data---integer part data
//    IN UINTN Dec_Data---decimal part data
//    IN UINTN Dec_Point---the count of decimal unit point
// Output:
//  UINTN   Data---output the translation data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN TEMP_DECIMAL_TO_INTEGER (
    IN UINTN Int_Data,
    IN UINTN Dec_Data,
    IN UINTN Dec_Point//when 0.5,it is 1,when 0.25 it is 2,when 0.125,it is 3
)
{
    UINTN       OutBuffer=0;
    INTN        InData=0;
    UINTN       Dec_Unit=1;

    InData = (INTN)(Int_Data);

    if(InData < 0) {
        Dec_Unit=-1;
    }
    while(Dec_Point) {
        Int_Data=Int_Data*10;
        Dec_Unit=Dec_Unit*5;
        Dec_Point--;
    }
    OutBuffer=Int_Data+Dec_Data*Dec_Unit;

    return OutBuffer;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     VOL_DIVISOR_CALCULATE
//
// Description:
//  Get the register value form HWM voltage space register.
//
// Input:
//    IN UINTN Vol_Value---voltage parameter
//    IN UINTN Vol_Unit---voltage lsb unit
//    IN UINTN R_B---divisor bigger resitor
//    IN UINTN R_S---divisor smaller resitor
// Output:
//  UINTN   Data---output the voltage value
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
UINTN VOL_DIVISOR_CALCULATE (
    IN UINTN Vol_Value,
    IN UINTN Vol_Unit,
    IN UINTN R_B,
    IN UINTN R_S
)
{
    UINTN  OutBuffer=0;
    if((R_B != 0) && (R_S != 0)) { //it use resistor divisor
        OutBuffer = Vol_Value * Vol_Unit * (R_B + R_S)/R_S;
    } else {//it don't use resistor divisor
        OutBuffer = Vol_Value * Vol_Unit;
    }

    return OutBuffer;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetValueWithIO
//
// Description:
//  Get the register value form HWM space register.
//
// Input:
//  UINT8   BankNo,
//  UINT8   Register -> Register who content the wanted value
//  UINTN   *Value   -> Register value
//
// Output:
//  UINTN   *Value
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetValueWithIO (
    IN UINT8 BankNo,
    IN UINT8 Register,
    OUT UINTN *Value
)
{
    UINT8       temp;

    // Enter Bank NO!
    IoWrite8(IT8728F_HWM_INDEX_PORT, 0x4E);
    temp = IoRead8(IT8728F_HWM_DATA_PORT);
    temp &= 0xF8 ;
    IoWrite8(IT8728F_HWM_DATA_PORT, (temp | BankNo));

    //Read the data from register
    IoWrite8(IT8728F_HWM_INDEX_PORT, Register);
    *Value = IoRead8(IT8728F_HWM_DATA_PORT);

    return;
}
//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------
// >> 2017/03/22 Eric
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   AaeonCpuCoreTemperatureDetection
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
#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
void AaeonCpuCoreTemperatureDetection(IN OUT HWM_DATA * Data)
{
    UINTN   T1;
    
    Data->Token = STRING_TOKEN(STR_HWM_CPU_DTS_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    #if defined(INTEL_DTS_SUPPORT) && (INTEL_DTS_SUPPORT)
    {
        //#include "Vlv2DeviceRefCodePkg/ValleyView2Soc/CPU/Include/CpuRegs.h"
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
// << 2017/03/22 Eric
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetSystemTemp1
//
// Description:
//  Get the first System temperature value in HWM space register and update to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetSystemTemp1(
    IN OUT HWM_DATA * Data
)
{
    UINTN       T1;
    UINTN       IntData=0;
    UINTN       DecData=0;
    UINT8       Unit_Point_Count=0;//AMI_TODO integer:0,0.5->1,0.25->2,0.125->3

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP1_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = Unit_Point_Count;

    //Get Integer Data,AMI_TODO:
    GetValueWithIO(0x00,0x29,&IntData); // Bank0 Register 0x29.
    if((IntData == 0x80) || (IntData == 0x7F)) {//No device on the sensor
        Data->Value = 0;
        return;
    }
    //Get Demical Data,AMI_TODO:

    //Get the Sign Bit,Positive or Negative,AMI_TODO:
    IntData=(UINTN)(INTN)(INT8)IntData;//8bit Data
    //Change Data display
    T1= TEMP_DECIMAL_TO_INTEGER (IntData,//integer
                                 DecData,//decimal
                                 Unit_Point_Count);//point

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)(INTN)T1;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetSystemTemp2
//
// Description:
//  Get the first System temperature value in HWM space register and update to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetSystemTemp2(
    IN OUT HWM_DATA * Data
)
{
    UINTN       T1;
    UINTN       IntData=0;
    UINTN       DecData=0;
    UINT8       Unit_Point_Count=0;//AMI_TODO integer:0,0.5->1,0.25->2,0.125->3

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP2_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = Unit_Point_Count;

    //Get Integer Data,AMI_TODO:
    GetValueWithIO(0x00,0x2A,&IntData); // Bank0 Register 0x2A.

    if((IntData == 0x80) || (IntData == 0x7F)) {//No device on the sensor
        Data->Value = 0;
        return;
    }
    //Get Demical Data,AMI_TODO:

    //Get the Sign Bit,Positive or Negative,AMI_TODO:
    IntData=(UINTN)(INTN)(INT8)IntData;//8bit Data
    //Change Data display
    T1= TEMP_DECIMAL_TO_INTEGER (IntData,//integer
                                 DecData,//decimal
                                 Unit_Point_Count);//point

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)(INTN)T1;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetSystemTemp3
//
// Description:
//  Get the first System temperature value in HWM space register and update to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetSystemTemp3(
    IN OUT HWM_DATA * Data
)
{
    UINTN       T1;
    UINTN       IntData=0;
    UINTN       DecData=0;
    UINT8       Unit_Point_Count=0;//AMI_TODO integer:0,0.5->1,0.25->2,0.125->3

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP3_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = Unit_Point_Count;

    //Get Integer Data,AMI_TODO:
    GetValueWithIO(0x00,0x2B,&IntData); // Bank0 Register 0x2B.

    if((IntData == 0x80) || (IntData == 0x7F)) {//No device on the sensor
        Data->Value = 0;
        return;
    }
    //Get Demical Data,AMI_TODO:

    //Get the Sign Bit,Positive or Negative,AMI_TODO:
    IntData=(UINTN)(INTN)(INT8)IntData;//8bit Data
    //Change Data display
    T1= TEMP_DECIMAL_TO_INTEGER (IntData,//integer
                                 DecData,//decimal
                                 Unit_Point_Count);//point

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)(INTN)T1;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan1Speed
//
// Description:
//  Get the First FAN Speed value in HWM space register and update it to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
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

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan2Speed
//
// Description:
//  Get the second FAN Speed value in HWM space register and update it to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
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

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan3Speed
//
// Description:
//  Get the third FAN Speed value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
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

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan4Speed
//
// Description:
//  Get the fourth FAN Speed value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
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
    // >> 2017/03/22 Eric
    //GetValueWithIO(0x00,0x80,&Speed1);  //  Register 0x80
    //GetValueWithIO(0x00,0x81,&Speed2);  //  Register 0x81
    GetValueWithIO(0x00,0x81,&Speed1);  //  Register 0x81
    GetValueWithIO(0x00,0x80,&Speed2);  //  Register 0x80
    // << 2017/03/22 Eric

    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0) || (Divisor == 0))
        Data->Value=0;
    else
        Data->Value = (UINT16)(1350000/(Divisor * Speed1));

    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan5Speed
//
// Description:
//  Get the fifth FAN Speed value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
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

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN0Voltage
//
// Description:
//  Get the VIN0 Voltage value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN0Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=150;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_IT8728F_HMM_VIN0_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x20,&VData) ; // Register 0x20
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN0_RA;
    R_Small = VIN0_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN1Voltage
//
// Description: Get the VIN1 Voltage value in HWM space register.
//
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN1Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x21,&VData) ; // Register 0x21
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN1_RA;
    R_Small = VIN1_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;

}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN2Voltage
//
// Description: Get the VIN2 Voltage value in HWM space register.
//
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN2Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x22,&VData) ; // Register 0x22
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN2_RA;
    R_Small = VIN2_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN3Voltage
//
// Description:
//  Get the VIN0 Voltage value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN3Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x23,&VData) ; // Register 0x23
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN3_RA;
    R_Small = VIN3_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN4Voltage
//
// Description: Get the VIN4 Voltage value in HWM space register.
//
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN4Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN4_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x24,&VData) ; // Register 0x24
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN4_RA;
    R_Small = VIN4_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN5Voltage
//
// Description: Get the VIN5 Voltage value in HWM space register.
//
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN5Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN5_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x25,&VData) ; // Register 0x24
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN5_RA;
    R_Small = VIN5_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN6Voltage
//
// Description: Get the VIN6 Voltage value in HWM space register.
//
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN6Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN6_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x26,&VData) ; // Register 0x24
    //RayWu, ADD 2014/07/28 >>
    R_Big = VIN6_RA;
    R_Small = VIN6_RB;
    Lsb_Unit = 12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN7Voltage
//
// Description: Get the VIN7 Voltage value in HWM space register.
//
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN7Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=10;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=10; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN7_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x27,&VData) ; // Register 0x27
    R_Big = 0;
    R_Small = 1;
    Lsb_Unit = 2*12;
    
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVBATVoltage
//
// Description:
//  Get the VBAT Voltage value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVBATVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VBAT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x28,&VData) ; //bank0 Register 0x28
    //RayWu, ADD 2014/07/28 >>
    R_Big = 0;
    R_Small = 1;
    Lsb_Unit = 2*12;
    //RayWu, ADD 2014/07/28 <<
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT16 data
    Data->Value = (UINT16)VData;
    return;
}

SIO_EXTERNAL_FUN *IT8728FExternalFunList[] = {
    // >> 2017/03/22 Eric
    #if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
    AaeonCpuCoreTemperatureDetection,
    #endif //AAEON_CPU_CORE_TEMP_DETECTION
    // << 2017/03/22 Eric
    GetSystemTemp1,
    GetSystemTemp2,
    GetSystemTemp3,
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
    GetAndUpdateVBATVoltage,
    NULL
};

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:    IT8728F_HWM_CallBack
//
// Description:
//  Form Callback Function.Will be called every 100m Polling for data Updates.
//
// Input:
//  IN EFI_HII_HANDLE HiiHandle
//  IN UINT16 Class
//  IN UINT16 SubClass
//  IN UINT16 Key
//
// Output:    VOID
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID IT8728F_HWM_CallBack(
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

    for(index=0; IT8728FExternalFunList[index]; index++) {
        IT8728FExternalFunList[index](&Data);
        AaeonHHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
    }


    return;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
