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
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81966HwmSetup.c>
//
// Description: This is related to individual HWM devices.
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <SioSetup.h>
#include "AaeonIoSetup.h"
//----------------------------------------------------------------------
// Constants, Macros and Type Definitions
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//Variable, Prototype, and External Declarations
//----------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////
////////////OEM PORTING REQUIRED/////////////OEM PORTING REQUIRED///////
////////////////////////////////////////////////////////////////////////
//<AMI_PHDR_START>
//----------------------------------------------------------------------
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
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetValueWithIO (
    IN UINT8 BankNo,
    IN UINT8 Register,
    OUT UINTN *Value
)
{

    // Enter Bank NO!

    //Read the data from register
    IoWrite8(F81966_HWM_INDEX_PORT, Register);
    *Value = IoRead8(F81966_HWM_DATA_PORT);
    return;
}

//RayWu, ADD 2014/12/03 >>
#if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
void AaeonCpuCoreTemperatureDetection(IN OUT HWM_DATA * Data)
{
	UINTN	T1;
	
	Data->Token = STRING_TOKEN(STR_HWM1_SYSTEM_TEMP1_VALUE);
	Data->Type = TEMPERATURE;
	Data->OddPos = 0x00;

	#if defined(INTEL_DTS_SUPPORT) && (INTEL_DTS_SUPPORT)
	{
		// F81966_IntelDTS_Miles, remove depency for baytrail code >>>>>
		//#include "Vlv2DeviceRefCodePkg/ValleyView2Soc/CPU/Include/CpuRegs.h"
		#ifndef EFI_MSR_CPU_THERM_TEMPERATURE
		#define EFI_MSR_CPU_THERM_TEMPERATURE 0x1A2
        #endif
		#ifndef EFI_MSR_IA32_CR_THERM_STATUS
		#define EFI_MSR_IA32_CR_THERM_STATUS 0x19C
		#endif
		// F81966_IntelDTS_Miles <<<<<
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
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature1
//
// Description:
//  Get Temperature1 value in HWM space register and update to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x72,&T1); // Bank0 Register 0x72.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature2
//
// Description:
//  Get the second System temperature value in HWM space register and update
//  to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x74,&T1); // Bank0 Register 0x74.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature3
//
// Description:
//  Get the second System temperature value in HWM space register and update
//  to Hii.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x7E,&T1); // Bank0 Register 0x7E.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature4
//
// Description:
//  Get the second System temperature value in HWM space register and update
//  to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x7A,&T1); // Bank0 Register 0x7A.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature5
//
// Description:
//  Get the second System temperature value in HWM space register and update
//  to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None

//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x7B,&T1); // Bank0 Register 0x7B.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateTemperature6
//
// Description:
//  Get the second System temperature value in HWM space register and update
//  to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x7C,&T1); // Bank0 Register 0x7C.
    if(T1 ==  0x80)
        Data->Value = 0x00;
    else
        Data->Value = (UINT16)T1;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:     GetAndUpdateFan1Speed
//
// Description:
//  Get the First FAN Speed value in HWM space register and update it to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:     GetAndUpdateFan2Speed
//
// Description:
//  Get FAN2 Speed value in HWM space register and update it to HII.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0xB0,&Speed); //  Register 0xA0
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x00,0xB1,&Speed); //  Register 0xA1
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)1500000/Divisor;
    }

    Data->Value = (UINT16)Speed;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:     GetAndUpdateFan3Speed
//
// Description:
//  Get FAN2 Speed value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0xC0,&Speed); //  Register 0xA0
    Divisor = (UINT8)Speed << 8;
    GetValueWithIO(0x00,0xC1,&Speed); //  Register 0xA1
    Divisor |= (UINT8) Speed;

    if( (Divisor == 0xFFFF) || (Divisor == 0x0FFF) || (Divisor  == 0 )) {
        Speed = 0;
    } else {
        Speed = (UINTN)1500000/Divisor;
    }
    Data->Value = (UINT16)Speed;

    return;
}
//RayWu, ADD 2014/12/03 >>
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN1Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN1Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN1;
	UINTN	Ra = VIN1_RA;
	UINTN	Rb = VIN1_RB;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x21,&VIN1) ; // Register 0x21
    VIN1 = VIN1*8*(Ra+Rb)/Rb;

    Data->Value = (UINT16)VIN1;

    return;

}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN2Voltage
//
// Description: Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN2Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN2;
	UINTN	Ra = VIN2_RA;
	UINTN	Rb = VIN2_RB;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x22,&VIN2) ; // Register 0x22
    VIN2 = VIN2*8*(Ra+Rb)/Rb;
    Data->Value = (UINT16)VIN2;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN3Voltage
//
// Description:
//  Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN3Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN3;
	UINTN	Ra = VIN3_RA;
	UINTN	Rb = VIN3_RB;	

    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x23,&VIN3) ; // Register 0x23
    VIN3 = VIN3*8*(Ra+Rb)/Rb;
    Data->Value = (UINT16)VIN3;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVIN4Voltage
//
// Description:
//  Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVIN4Voltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VIN4;
	UINTN	Ra = VIN4_RA;
	UINTN	Rb = VIN4_RB;

    Data->Token = STRING_TOKEN(STR_HWM1_VIN4_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x24,&VIN4) ; // Register 0x24
    VIN4 = VIN4*8*(Ra+Rb)/Rb;
    Data->Value = (UINT16)VIN4;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVSB5VVoltage
//
// Description:
//  Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None
//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
void
GetAndUpdateVSB5VVoltage (
    IN OUT HWM_DATA * Data
)
{
    UINTN       VSB5V;

    Data->Token = STRING_TOKEN(STR_HWM1_VSB5V_VALUE);
    Data->Type = VOLTAGE;
    Data->OddPos = 0x03;

    //OEM_TODO:Get value with HWM IO interface
    GetValueWithIO(0x00,0x27,&VSB5V) ; // Register 0x27
    VSB5V = VSB5V*8*3;
    Data->Value = (UINT16)VSB5V;

    return;
}
//RayWu, ADD 2014/12/03 <<
//RayWu, REMOVE 2014/12/03 >>
////<AMI_PHDR_START>
////----------------------------------------------------------------------
//// Procedure:   GetAndUpdateVIN1Voltage
////
//// Description: Get the Voltage value in HWM space register.
////
//// Input:
////  UINTN    IN OUT HWM_DATA * Data
////
//// Output:
////  None
////
////----------------------------------------------------------------------
////<AMI_PHDR_END>
//void
//GetAndUpdateVIN1Voltage (
//    IN OUT HWM_DATA * Data
//)
//{
//    UINTN       VIN1;
//
//    Data->Token = STRING_TOKEN(STR_HWM1_VIN1_VALUE);
//    Data->Type = VOLTAGE;
//    Data->OddPos = 0x03;
//
//    //OEM_TODO:Get value with HWM IO interface
//    GetValueWithIO(0x00,0x21,&VIN1) ; // Register 0x21
//    VIN1 = VIN1*8;
//
//    Data->Value = (UINT16)VIN1;
//
//    return;
//
//}
//
////<AMI_PHDR_START>
////----------------------------------------------------------------------
//// Procedure:   GetAndUpdateVIN2Voltage
////
//// Description: Get the Voltage value in HWM space register.
////
//// Input:
////  UINTN    IN OUT HWM_DATA * Data
////
//// Output:
////  None
////
////----------------------------------------------------------------------
////<AMI_PHDR_END>
//void
//GetAndUpdateVIN2Voltage (
//    IN OUT HWM_DATA * Data
//)
//{
//    UINTN       VIN2;
//
//    Data->Token = STRING_TOKEN(STR_HWM1_VIN2_VALUE);
//    Data->Type = VOLTAGE;
//    Data->OddPos = 0x03;
//
//    //OEM_TODO:Get value with HWM IO interface
//    GetValueWithIO(0x00,0x22,&VIN2) ; // Register 0x22
//    VIN2 = VIN2*8*(20+47)/47;
//    Data->Value = (UINT16)VIN2;
//
//    return;
//}
//
////<AMI_PHDR_START>
////----------------------------------------------------------------------
//// Procedure:   GetAndUpdateVIN3Voltage
////
//// Description:
////  Get the Voltage value in HWM space register.
////
//// Input:
////  UINTN    IN OUT HWM_DATA * Data
////
//// Output:
////  None
////
////----------------------------------------------------------------------
////<AMI_PHDR_END>
//void
//GetAndUpdateVIN3Voltage (
//    IN OUT HWM_DATA * Data
//)
//{
//    UINTN       VIN3;
//
//    Data->Token = STRING_TOKEN(STR_HWM1_VIN3_VALUE);
//    Data->Type = VOLTAGE;
//    Data->OddPos = 0x03;
//
//    //OEM_TODO:Get value with HWM IO interface
//    GetValueWithIO(0x00,0x23,&VIN3) ; // Register 0x23
//    VIN3 = VIN3*8;
//    Data->Value = (UINT16)VIN3;
//
//    return;
//}
//
////<AMI_PHDR_START>
////----------------------------------------------------------------------
//// Procedure:   GetAndUpdateVIN4Voltage
////
//// Description:
////  Get the Voltage value in HWM space register.
////
//// Input:
////  UINTN    IN OUT HWM_DATA * Data
////
//// Output:
////  None
////
////----------------------------------------------------------------------
////<AMI_PHDR_END>
//void
//GetAndUpdateVIN4Voltage (
//    IN OUT HWM_DATA * Data
//)
//{
//    UINTN       VIN4;
//
//    Data->Token = STRING_TOKEN(STR_HWM1_VIN4_VALUE);
//    Data->Type = VOLTAGE;
//    Data->OddPos = 0x03;
//
//    //OEM_TODO:Get value with HWM IO interface
//    GetValueWithIO(0x00,0x24,&VIN4) ; // Register 0x24
//    VIN4 = VIN4*8*(100+100)/100;
//    Data->Value = (UINT16)VIN4;
//
//    return;
//}
//
////<AMI_PHDR_START>
////----------------------------------------------------------------------
//// Procedure:   GetAndUpdateVSB5VVoltage
////
//// Description:
////  Get the Voltage value in HWM space register.
////
//// Input:
////  UINTN    IN OUT HWM_DATA * Data
////
//// Output:
////  None
////
////----------------------------------------------------------------------
////<AMI_PHDR_END>
//void
//GetAndUpdateVSB5VVoltage (
//    IN OUT HWM_DATA * Data
//)
//{
//    UINTN       VSB5V;
//
//    Data->Token = STRING_TOKEN(STR_HWM1_VSB5V_VALUE);
//    Data->Type = VOLTAGE;
//    Data->OddPos = 0x03;
//
//    //OEM_TODO:Get value with HWM IO interface
//    GetValueWithIO(0x00,0x27,&VSB5V) ; // Register 0x27
//    VSB5V = VSB5V*8*2;
//    Data->Value = (UINT16)VSB5V;
//
//    return;
//}
//RayWu, REMOVE 2014/12/03 <<
//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVCC3VVoltage
//
// Description:
//  Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None

//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x20,&VCC3V) ;  // Register 0x20
    VCC3V = VCC3V * 8 * 2;

    Data->Value = (UINT16)VCC3V;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVSB3VVoltage
//
// Description:
//  Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None

//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x25,&VSB3V) ; // Register 0x25
    VSB3V = VSB3V * 8 * 2 ;

    Data->Value = (UINT16)VSB3V;

    return;
}

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:   GetAndUpdateVBATVoltage
//
// Description:
//  Get the Voltage value in HWM space register.
//
// Input:
//  UINTN    IN OUT HWM_DATA * Data
//
// Output:
//  None

//
//----------------------------------------------------------------------
//<AMI_PHDR_END>
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
    GetValueWithIO(0x00,0x26,&VBAT) ; // Register 0x26
    VBAT = VBAT*8*2;
    Data->Value = (UINT16)VBAT;

    return;
}

SIO_EXTERNAL_FUN *F81966ExternalFunList[] = {
    //RayWu, ADD 2014/12/03 >>
    #if defined(AAEON_CPU_CORE_TEMP_DETECTION) && (AAEON_CPU_CORE_TEMP_DETECTION)
	AaeonCpuCoreTemperatureDetection,
	GetAndUpdateTemperature2,
	GetAndUpdateTemperature3,
	GetAndUpdateTemperature4,
	GetAndUpdateTemperature5,
	GetAndUpdateTemperature6,
    #else
	GetAndUpdateTemperature1,
	GetAndUpdateTemperature2,
	GetAndUpdateTemperature3,
	GetAndUpdateTemperature4,
	GetAndUpdateTemperature5,
	GetAndUpdateTemperature6,
    #endif //AAEON_CPU_CORE_TEMP_DETECTION
    //RayWu, ADD 2014/12/03 <<
    //RayWu, REMOVE 2014/12/03 >>
    //GetAndUpdateTemperature1,
    //GetAndUpdateTemperature2,
    //GetAndUpdateTemperature3,
    //GetAndUpdateTemperature4,
    //GetAndUpdateTemperature5,
    //GetAndUpdateTemperature6,
    //RayWu, REMOVE 2014/12/03 <<
    GetAndUpdateFan1Speed,
    GetAndUpdateFan2Speed,
    GetAndUpdateFan3Speed,
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

//<AMI_PHDR_START>
//----------------------------------------------------------------------
// Procedure:    F81966_HWM_CallBack
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
//----------------------------------------------------------------------
//<AMI_PHDR_END>
VOID F81966_HWM_CallBack(
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

    for(index=0; F81966ExternalFunList[index]; index++) {
        F81966ExternalFunList[index](&Data);
        AaeonHHMCommon(Data.Value, Data.Type, Data.Token, Data.OddPos, HiiHandle);
    }

    return;
}

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
