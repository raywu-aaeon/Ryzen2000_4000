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
// Name:  <W83627DHGHwmSetup.c>
//
// Description: This is related to individual HHM devices.
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
    UINTN       OutBuffer=0;
    if((R_B!=0) && (R_S!=0)){//it use resistor divisor
      OutBuffer = Vol_Value * Vol_Unit * (R_B + R_S)/R_S;
    }else {//it don't use resistor divisor
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
    IoWrite8(W83627DHG_HWM_INDEX_PORT, 0x4E);
    temp = IoRead8(W83627DHG_HWM_DATA_PORT);
    temp &= 0xF8 ;
    IoWrite8(W83627DHG_HWM_DATA_PORT, (temp | BankNo));

    //Read the data from register
    IoWrite8(W83627DHG_HWM_INDEX_PORT, Register);
    *Value = IoRead8(W83627DHG_HWM_DATA_PORT);
}
//-------------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// Procedure:   AaeonCpuCoreTemperatureDetection
//
// Description:
//  Get the CPU temperature value from CPU MSR and update to HII.
//
// Input:
//  HWM_DATA    *Data
//
// Output:
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
#if W83627DHG_CPU_DTS_SUPPORT
  // For removing depency for platform code
  #ifndef EFI_MSR_CPU_THERM_TEMPERATURE
  #define EFI_MSR_CPU_THERM_TEMPERATURE 0x1A2
  #endif
  #ifndef EFI_MSR_IA32_CR_THERM_STATUS
  #define EFI_MSR_IA32_CR_THERM_STATUS 0x19C
  #endif
extern UINT64 ReadMsr(UINT32 Msr);

void AaeonCpuCoreTemperatureDetection(IN OUT HWM_DATA * Data)
{
	UINTN	T1;
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 RegTmp8, TjMax;
    UINT64 RegTmp64;
	
	Data->Token = STRING_TOKEN(STR_W83627DHG_HWM1_CPU_DTS_TEMP_VALUE);
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
#endif //W83627DHG_CPU_DTS_SUPPORT

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
    UINTN      T1;

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP1_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //Get Integer Data,AMI_TODO:
    GetValueWithIO(0x00,0x27,&T1); // Bank0 Register 0x27.
    //Get Demical Data,AMI_TODO:
    //pass to setup data which is UINT64 data
        Data->Value = (UINT16)T1;
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

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP2_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //Get Integer Data,AMI_TODO:
    GetValueWithIO(0x01,0x50,&T1);     				// Bank1 Register 0x50. LSB:units of 0.5??C.
//  GetValueWithIO(0x01,0x51,&IntData1);           // Bank1 Register 0x51.
    Data->Value = (UINT16)T1;

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

    Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP3_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //Get Integer Data,AMI_TODO:
    GetValueWithIO(0x02,0x50,&T1);     // Bank2 Register 0x50. LSB:units of 0.5??C.
//  GetValueWithIO(0x02,0x51,&IntData1);           // Bank2 Register 0x51.
    Data->Value = (UINT16)T1;
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
    UINTN   Divisor, Divisor1, Divisor2;
    UINTN   temp, Speed;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN1_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    GetValueWithIO(0x00,0x28,&temp); //  Register 0x28--SYSFANIN

    GetValueWithIO(0x00,0x47,&Divisor1); //  Register 0x47[5-4]: Divisor bit1,bit0 .
    GetValueWithIO(0x00,0x5D,&Divisor2); //  Register 0x5D[5]: Divisor bit2 .
    Divisor = ((Divisor1 & 0x30) >> 4) | ((Divisor2 & 0x20) >> 3) ;
    Divisor = (UINTN)(BIT0 << (UINT8)Divisor);

    if(temp == 0xFF || temp == 0 || Divisor == 0)Speed=0;
    else
    Speed = (UINTN)1350000/(Divisor*temp);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)Speed;

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
    UINTN   Divisor, Divisor1, Divisor2;
    UINTN   temp, Speed;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN2_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    GetValueWithIO(0x00,0x29,&temp); //  Register 0x29--CPUFANIN0

    GetValueWithIO(0x00,0x47,&Divisor1); //  Register 0x47[7-6]: Divisor bit1,bit0 .
    GetValueWithIO(0x00,0x5D,&Divisor2); //  Register 0x5D[6]: Divisor bit2 .
    Divisor = ((Divisor1 & 0xC0) >> 6) | ((Divisor2 & 0x40) >> 4) ;
    Divisor = (UINTN)(BIT0 << (UINT8)Divisor);

    if(temp == 0xFF || temp == 0 || Divisor == 0)Speed=0;
    else
    Speed = (UINTN)1350000/(Divisor*temp);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)Speed;
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
    UINTN   Divisor, Divisor1, Divisor2;
    UINTN   temp, Speed;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN3_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    GetValueWithIO(0x00,0x2A,&temp); //  Register 0x2A--AUXFANIN0

    GetValueWithIO(0x00,0x4B,&Divisor1); //  Register 0x4B[7-6]: Divisor bit1,bit0 .
    GetValueWithIO(0x00,0x5D,&Divisor2); //  Register 0x5D[7]: Divisor bit2 .
    Divisor = ((Divisor1 & 0xC0) >> 6) | ((Divisor2 & 0x80) >> 5) ;
    Divisor = (UINTN)(BIT0 << (UINT8)Divisor);

    if(temp == 0xFF || temp == 0 || Divisor == 0)Speed=0;
    else
    Speed = (UINTN)1350000/(Divisor*temp);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)Speed;

    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan4Speed
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
GetAndUpdateFan4Speed (
    IN OUT HWM_DATA * Data
  )
{
    UINTN   Divisor, Divisor1, Divisor2;
    UINTN   temp, Speed;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN4_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    GetValueWithIO(0x00,0x3F,&temp); //  Register 0x3F--CPUFANIN1

    GetValueWithIO(0x00,0x59,&Divisor1); //  Register 0x59[1-0]: Divisor bit1,bit0 .
    GetValueWithIO(0x00,0x4C,&Divisor2); //  Register 0x4C[7]: Divisor bit2 .
    Divisor = ((Divisor1 & 0x03) >> 0) | ((Divisor2 & 0x80) >> 5) ;
    Divisor = (UINTN)(BIT0 << (UINT8)Divisor);

    if(temp == 0xFF || temp == 0 || Divisor == 0)Speed=0;
    else
    Speed = (UINTN)1350000/(Divisor*temp);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)Speed;

    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan5Speed
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
GetAndUpdateFan5Speed (
    IN OUT HWM_DATA * Data
  )
{
    UINTN   Divisor, Divisor1, Divisor2;
    UINTN   temp, Speed;

    Data->Token = STRING_TOKEN(STR_HWM1_FAN5_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    GetValueWithIO(0x05,0x53,&temp); //  Register 0x53--AUXFANIN1

    GetValueWithIO(0x00,0x59,&Divisor1); //  Register 0x59[3-2]: Divisor bit1,bit0 .
    GetValueWithIO(0x00,0x59,&Divisor2); //  Register 0x59[7]: Divisor bit2 .
    Divisor = ((Divisor1 & 0x0C) >> 2) | ((Divisor2 & 0x80) >> 5) ;
    Divisor = (UINTN)(BIT0 << (UINT8)Divisor);

    if(temp == 0xFF || temp == 0 || Divisor == 0)Speed=0;
    else
    Speed = (UINTN)1350000/(Divisor*temp);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)Speed;

    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVCOREVoltage
//
// Description:
//  Get the VCORE Voltage value in HWM space register.
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
GetAndUpdateVCOREVoltage (
    IN OUT HWM_DATA * Data
  )
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=1;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=0; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_W83627DHG_HWM1_VCORE_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x20,&VData) ;  // Register 0x20
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???
    //R_Small=???
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
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
    UINTN       R_Big=W83627DHG_VIN0_RA;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=W83627DHG_VIN0_RB; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_W83627DHG_HWM1_VIN0_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x21,&VData) ; // Register 0x22
    //OEM_TODO:change R_Big & R_Small Value according to your board
    R_Big=10;
    R_Small=10;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
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
    UINTN       R_Big=W83627DHG_VIN1_RA;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=W83627DHG_VIN1_RB; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x24,&VData) ; // Register 0x24
    //OEM_TODO:change R_Big & R_Small Value according to your board
    R_Big=20;
    R_Small=10;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
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
    UINTN       R_Big=W83627DHG_VIN2_RA;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=W83627DHG_VIN2_RB; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x25,&VData) ; // Register 0x25
    //OEM_TODO:change R_Big & R_Small Value according to your board
    R_Big=150;
    R_Small=10;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
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
    UINTN       R_Big=W83627DHG_VIN3_RA;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=W83627DHG_VIN3_RB; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x04;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x26,&VData) ; // Register 0x26

    //OEM_TODO:change R_Big & R_Small Value according to your board
    R_Big=10;
    R_Small=10;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateAVCCVoltage
//
// Description:
//  Get the AVCC Voltage value in HWM space register.
//
// Input:
//  HWM_DATA    *Data
//
//  HWM_DATA    *Data
//
//-------------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateAVCCVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_W83627DHG_HWM1_VACC_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x22,&VData) ; // Register 0x22
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVCC3Voltage
//
// Description:
//  Get the VSB3V Voltage value in HWM space register.
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
GetAndUpdateVCC3Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VCC3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x00,0x23,&VData) ; //bank0 Register 0x23
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVSB3Voltage
//
// Description:
//  Get the VSB3V Voltage value in HWM space register.
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
GetAndUpdateVSB3Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VData;
    UINTN       Lsb_Unit=8;//AMI_TODO:LSB unit is 8mv
    UINTN       R_Big=20;   //AMI_TODO:Connect bigger divisor resistor
    UINTN       R_Small=20; //AMI_TODO:Connect smaller divisor resistor

    Data->Token = STRING_TOKEN(STR_HWM1_VSB3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //AMI_TODO:Get value of Hwm Space raw data
    GetValueWithIO(0x05,0x50,&VData) ; //bank5 Register 0x50
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);
    //pass to setup data which is UINT64 data
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
    GetValueWithIO(0x05,0x51,&VData) ; //bank5 Register 0x51
    //OEM_TODO:change R_Big & R_Small Value according to your board
    //R_Big=???;
    //R_Small=???;
    //calculate voltage value
    VData = VOL_DIVISOR_CALCULATE (VData,
                                   Lsb_Unit,
                                   R_Big,
                                   R_Small);

    //pass to setup data which is UINT64 data
    Data->Value = (UINT16)VData;
    return;
}

SIO_EXTERNAL_FUN *W83627DHGExternalFunList[] = {
    AaeonCpuCoreTemperatureDetection,
	GetSystemTemp1,
	GetSystemTemp2,
	GetSystemTemp3,
	GetAndUpdateFan1Speed,
	GetAndUpdateFan2Speed,
	GetAndUpdateFan3Speed,
	GetAndUpdateFan4Speed,
	GetAndUpdateFan5Speed,
	GetAndUpdateVCOREVoltage,
	GetAndUpdateVIN0Voltage,
	GetAndUpdateVIN1Voltage,
	GetAndUpdateVIN2Voltage,
	GetAndUpdateVIN3Voltage,
	GetAndUpdateVCC3Voltage,
	GetAndUpdateAVCCVoltage,
	GetAndUpdateVSB3Voltage,
	GetAndUpdateVBATVoltage,
	NULL
};

VOID W83627DHG_HWM_CallBack(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    UINTN    index;
    HWM_DATA Data;
    CALLBACK_PARAMETERS *Callback = NULL;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return;

    for(index=0; W83627DHGExternalFunList[index]; index++)
    {
    	W83627DHGExternalFunList[index](&Data);
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
