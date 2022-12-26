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
// Name:  <NCT6791DHwmSetup.c>
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
void
GetValueWithIO (
    IN UINT8    BankNo,
    IN UINT8    Register,
    OUT UINTN   *Value
);

UINTN TEMP_DECIMAL_TO_INTEGER (
    IN UINTN Int_Data,
    IN UINTN Dec_Data,
    IN UINTN Dec_Point
);
UINTN VOL_DIVISOR_CALCULATE (
    IN UINTN Vol_Value,
    IN UINTN Vol_Unit,
    IN UINTN R_B,
    IN UINTN R_S
);
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature1
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
GetAndUpdateTemperature1( 
    IN OUT HWM_DATA * Data
)
{
    UINTN      T1;
    
    Data->Token = STRING_TOKEN(STR_NCT6791D_SYSTEM_TEMP1_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x90,&T1); //Bank4, index90: SYSTIN temperature reading

    if (T1 == 0x80) 
        Data->Value = 0;
    else
        Data->Value = (UINT16)T1;
    
    return;
}


//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature2
//
// Description: 
//  Get the second System temperature value in HWM space register and update
//  to HII.
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
GetAndUpdateTemperature2 (
    IN OUT HWM_DATA * Data
  )
{
    UINTN      T1;
    Data->Token = STRING_TOKEN(STR_NCT6791D_SYSTEM_TEMP2_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    #if CPUTIN_TYPE
      GetValueWithIO(0x07, 0x20, &T1); //Bank7, index20: PECI Temperature reading
    #else // CPUTIN_TYPE
      GetValueWithIO(0x04, 0x91, &T1); //Bank4, index91: CPUTIN temperature reading
    #endif // CPUTIN_TYPE

    if (T1 == 0x80) 
        Data->Value = 0;
    else
        Data->Value = (UINT16)T1;

    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature3
//
// Description: 
//  Get the second System temperature value in HWM space register and update
//  to HII.
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
GetAndUpdateTemperature3 (
    IN OUT HWM_DATA * Data
  )
{
    UINTN      T1;
    Data->Token = STRING_TOKEN(STR_NCT6791D_SYSTEM_TEMP3_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x92,&T1); //Bank4, index92: AUXTIN0 temperature reading

    if (T1 == 0x80) 
        Data->Value = 0;
    else
        Data->Value = (UINT16)T1;

    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature4
//
// Description: 
//  Get the second System temperature value in HWM space register and update
//  to HII.
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
GetAndUpdateTemperature4 (
    IN OUT HWM_DATA * Data
  )
{
    UINTN      T1;
    Data->Token = STRING_TOKEN(STR_NCT6791D_SYSTEM_TEMP4_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x93,&T1); //Bank4, index93: AUXTIN1 temperature reading

    if (T1 == 0x80) 
        Data->Value = 0;
    else
        Data->Value = (UINT16)T1;

    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature5
//
// Description: 
//  Get the second System temperature value in HWM space register and update
//  to HII.
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
GetAndUpdateTemperature5 (
    IN OUT HWM_DATA * Data
  )
{
    UINTN      T1;
    Data->Token = STRING_TOKEN(STR_NCT6791D_SYSTEM_TEMP5_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x94,&T1); //Bank4, index94: AUXTIN2 temperature reading

    if (T1 == 0x80) 
        Data->Value = 0;
    else
        Data->Value = (UINT16)T1;

    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature6
//
// Description: 
//  Get the second System temperature value in HWM space register and update
//  to HII.
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
GetAndUpdateTemperature6 (
    IN OUT HWM_DATA * Data
  )
{
    UINTN      T1;
    Data->Token = STRING_TOKEN(STR_NCT6791D_SYSTEM_TEMP6_VALUE);
    Data->Type = TEMPERATURE;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x95,&T1); //Bank4, index95: AUXTIN3 temperature reading

    if (T1 == 0x80) 
        Data->Value = 0;
    else
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
    UINTN       Speed1, Speed2;
    
    Data->Token = STRING_TOKEN(STR_NCT6791D_FAN1_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;

    //OEM_TODO:Get value with HWM IO interface
    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC0,&Speed1);  //Bank4, indexC0: FAN RPM READING BIT[15:8]
    GetValueWithIO(0x04,0xC1,&Speed2);  //Bank4, indexC1: FAN RPM READING BIT[ 7:0]
    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)Speed1;

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
    Data->Token = STRING_TOKEN(STR_NCT6791D_FAN2_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;
    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC2,&Speed1);  //Bank4, indexC2: FAN RPM READING BIT[15:8]
    GetValueWithIO(0x04,0xC3,&Speed2);  //Bank4, indexC3: FAN RPM READING BIT[ 7:0]
    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)Speed1;

    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan3Speed
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
GetAndUpdateFan3Speed (
    IN OUT HWM_DATA * Data
  )
{
    UINTN       Speed1, Speed2;
    Data->Token = STRING_TOKEN(STR_NCT6791D_FAN3_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;
    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC4,&Speed1);  //Bank4, indexC4: FAN RPM READING BIT[15:8]
    GetValueWithIO(0x04,0xC5,&Speed2);  //Bank4, indexC5: FAN RPM READING BIT[ 7:0]
    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)Speed1;

    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan4Speed
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
GetAndUpdateFan4Speed (
    IN OUT HWM_DATA * Data
  )
{
    UINTN       Speed1, Speed2;
    Data->Token = STRING_TOKEN(STR_NCT6791D_FAN4_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;
    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC6,&Speed1);  //Bank4, indexC6: FAN RPM READING BIT[15:8]
    GetValueWithIO(0x04,0xC7,&Speed2);  //Bank4, indexC7: FAN RPM READING BIT[ 7:0]
    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)Speed1;

    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:     GetAndUpdateFan5Speed
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
GetAndUpdateFan5Speed (
    IN OUT HWM_DATA * Data
  )
{
    UINTN       Speed1, Speed2;
    Data->Token = STRING_TOKEN(STR_NCT6791D_FAN5_SPEED_VALUE);
    Data->Type = FAN_SPEED;
    Data->OddPos = 0x00;
    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0xC8,&Speed1);  //Bank4, indexC8: FAN RPM READING BIT[15:8]
    GetValueWithIO(0x04,0xC9,&Speed2);  //Bank4, indexC9: FAN RPM READING BIT[ 7:0]
    Speed1 = (Speed1 << 8) | Speed2;
    if((Speed1 == 0xFFFF) || (Speed1 == 0)) 
        Data->Value=0;
    else
        Data->Value = (UINT16)Speed1;

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
GetAndUpdateCPUVCOREVoltage (
    IN OUT HWM_DATA * Data
  )
{
    UINTN   CPUVCORE;
    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_CPUVCORE_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x80,&CPUVCORE) ; // Bank4, Register 0x80
    CPUVCORE = CPUVCORE * 8 * (CPUVCORE_R1 + CPUVCORE_R2) / CPUVCORE_R2; //Power input
    Data->Value = (UINT16)CPUVCORE;
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
    UINTN   VIN0;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN0_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x84,&VIN0) ; // Bank4, Register 0x84
//    VIN0 = VIN0 * 8; //positive voltage <2.048V format
//    VIN0 = VIN0 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN0 = VIN0 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN0 = VIN0 * 8 * (VIN0_R1 + VIN0_R2) / VIN0_R2;
    Data->Value = (UINT16)VIN0;
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
    UINTN   VIN1;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x81,&VIN1) ; // Bank4, Register 0x81
//    VIN1 = VIN1 * 8; //positive voltage <2.048V format
//    VIN1 = VIN1 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN1 = VIN1 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN1 = VIN1 * 8 * (VIN1_R1 + VIN1_R2) / VIN1_R2;
    Data->Value = (UINT16)VIN1;
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

    UINTN   VIN2;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8C,&VIN2) ; // Bank4, Register 0x8C
//    VIN2 = VIN2 * 8; //positive voltage <2.048V format
//    VIN2 = VIN2 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN2 = VIN2 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN2 = VIN2 * 8 * (VIN2_R1 + VIN2_R2) / VIN2_R2;
    Data->Value = (UINT16)VIN2;
    return;
   
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN3Voltage
//
// Description: Get the VIN3 Voltage value in HWM space register.
//
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

    UINTN   VIN3;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8D,&VIN3) ; // Bank4, Register 0x8D
//    VIN3 = VIN3 * 8; //positive voltage <2.048V format
//    VIN3 = VIN3 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN3 = VIN3 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN3 = VIN3 * 8 * (VIN3_R1 + VIN3_R2) / VIN3_R2;
    Data->Value = (UINT16)VIN3;
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

    UINTN   VIN4;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN4_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x86,&VIN4) ; // Bank4, Register 0x86
//    VIN4 = VIN4 * 8; //positive voltage <2.048V format
//    VIN4 = VIN4 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN4 = VIN4 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN4 = VIN4 * 8 * (VIN4_R1 + VIN4_R2) / VIN4_R2;
    Data->Value = (UINT16)VIN4;
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

    UINTN   VIN5;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN5_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8A,&VIN5) ; // Bank4, Register 0x8A
//    VIN5 = VIN5 * 8; //positive voltage <2.048V format
//    VIN5 = VIN5 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN5 = VIN5 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN5 = VIN5 * 8 * (VIN5_R1 + VIN5_R2) / VIN5_R2;
    Data->Value = (UINT16)VIN5;
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

    UINTN   VIN6;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN6_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8B,&VIN6) ; // Bank4, Register 0x8B
//    VIN6 = VIN6 * 8; //positive voltage <2.048V format
//    VIN6 = VIN6 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN6 = VIN6 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN6 = VIN6 * 8 * (VIN6_R1 + VIN6_R2) / VIN6_R2;
    Data->Value = (UINT16)VIN6;
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

    UINTN   VIN7;
//OEM_TODO: Base on OEM board to fill R1,R2
    UINTN   R1=10;
    UINTN   R2=100;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VIN7_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x8E,&VIN7) ; // Bank4, Register 0x8E
//    VIN7 = VIN7 * 8; //positive voltage <2.048V format
//    VIN7 = VIN7 * 8 * (R1+R2)/R2 ;//positive voltage >2.048V format
//    VIN7 = VIN7 * (1 + R3 / R4) - (R3 / R4) * VREF;//negative voltage format
    VIN7 = VIN7 * 8 * (VIN7_R1 + VIN7_R2) / VIN7_R2;
    Data->Value = (UINT16)VIN7;
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
    UINTN   AVCC;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_AVCC_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x82,&AVCC) ; // Bank4, Register 0x82
    AVCC = AVCC * 8 * 2; //Power input
    Data->Value = (UINT16)AVCC;
    return;
}
//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVCC3VVoltage
//
// Description: 
//  Get the VCC3V Voltage value in HWM space register.
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
GetAndUpdateVCC3VVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN   VCC3V;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VCC3V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x83,&VCC3V) ; // Bank4, Register 0x83
    VCC3V = VCC3V * 8 * 2; //Power input
    Data->Value = (UINT16)VCC3V;
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
    UINTN   VSB3;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VSB3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x87,&VSB3) ; // Bank4, Register 0x87
    VSB3 = VSB3 * 8 * 2; //Power input
    Data->Value = (UINT16)VSB3;
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
    UINTN   VBAT;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VBAT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x88,&VBAT) ; // Bank4, Register 0x88
    VBAT = VBAT * 8 * 2; //Power input
    Data->Value = (UINT16)VBAT;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVTTVoltage
//
// Description: 
//  Get the VTT Voltage value in HWM space register.
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
GetAndUpdateVTTVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN   VTT;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VTT_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x89,&VTT) ; // Bank4, Register 0x89
    VTT = VTT * 8; //Power input
    Data->Value = (UINT16)VTT;
    return;
}

//<AMI_PHDR_START>
//-------------------------------------------------------------------------
// Procedure:   GetAndUpdateVCOREREFINVoltage
//
// Description: 
//  Get the VCOREREFIN Voltage value in HWM space register.
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
GetAndUpdateVCOREREFINVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN   VCOREREFIN;

    Data->Token = STRING_TOKEN(STR_NCT6791D_HMM_VCOREREFIN_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x04,0x85,&VCOREREFIN) ; // Bank4, Register 0x85
    VCOREREFIN = VCOREREFIN * 8 * (VCOREREF_R1 + VCOREREF_R2) / VCOREREF_R2; //Power input
    Data->Value = (UINT16)VCOREREFIN;
    return;
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
    IoWrite8(NCT6791D_HWM_BASE_ADDRESS+0x05, 0x4E); 
    temp = IoRead8(NCT6791D_HWM_BASE_ADDRESS+0x06);
    temp &= 0xF8 ;
    IoWrite8(NCT6791D_HWM_BASE_ADDRESS+0x06, (temp | BankNo));

    //Read the data from register
    IoWrite8(NCT6791D_HWM_BASE_ADDRESS+0x05, Register); 
    *Value = IoRead8(NCT6791D_HWM_BASE_ADDRESS+0x06);
    return;
}

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


SIO_EXTERNAL_FUN *NCT6791DExternalFunList[] = {
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
    GetAndUpdateCPUVCOREVoltage,
    GetAndUpdateVIN0Voltage,
    GetAndUpdateVIN1Voltage,
    GetAndUpdateVIN2Voltage,
    GetAndUpdateVIN3Voltage,
    GetAndUpdateVIN4Voltage,
    GetAndUpdateVIN5Voltage,
    GetAndUpdateVIN6Voltage,
    GetAndUpdateVIN7Voltage,
    GetAndUpdateAVCCVoltage,
    GetAndUpdateVSB3Voltage,
    GetAndUpdateVCC3VVoltage,
    GetAndUpdateVBATVoltage,
    GetAndUpdateVTTVoltage,
    GetAndUpdateVCOREREFINVoltage,
    NULL
};

VOID NCT6791D_HWM_CallBack(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key)
{
    UINTN    index;
    HWM_DATA Data;
    CALLBACK_PARAMETERS *Callback = NULL;

    Callback = GetCallbackParameters();
    if(!Callback || Callback->Action != EFI_BROWSER_ACTION_CHANGING)
        return;

    for(index=0; NCT6791DExternalFunList[index]; index++)
    {
        NCT6791DExternalFunList[index](&Data);
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




