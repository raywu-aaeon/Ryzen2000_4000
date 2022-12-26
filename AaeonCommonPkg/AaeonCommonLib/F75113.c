//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include "AaeonCommonLib.h"

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)
//---------------------------------------------------------------------------
//		function definition _begin
//---------------------------------------------------------------------------
#if defined(F75113_SUPPORT) && (F75113_SUPPORT == 1)
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   F75113SetGpio
//
// Description: This function is setting the GPIO high/low and input/output
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              GpioVal - The high/low of GPIO, 1 for high, 0 for low
//              GpioType - The input/output of GPIO, 1 for output, 0 for input
//              SETUP_DATA - The pointer of setup item
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID
F75113SetGpio ( 
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
)	
{
	UINT8	GpioGroup, GpioGroupNum;

	GpioGroup = GpioNum / 10;
	GpioGroupNum = GpioNum % 10;

	switch(GpioGroup)
	{
		case Gpio0x:
			SetupData->F75113_GP0x_Data[GpioGroupNum] = GpioVal;
			SetupData->F75113_GP0x_Type[GpioGroupNum] = GpioType;
			break;

		case Gpio1x:
			SetupData->F75113_GP1x_Data[GpioGroupNum] = GpioVal;
			SetupData->F75113_GP1x_Type[GpioGroupNum] = GpioType;
			break;	

		case Gpio2x:
			SetupData->F75113_GP2x_Data[GpioGroupNum] = GpioVal;
			SetupData->F75113_GP2x_Type[GpioGroupNum] = GpioType;
			break;

		case Gpio3x:
			SetupData->F75113_GP3x_Data[GpioGroupNum] = GpioVal;
			SetupData->F75113_GP3x_Type[GpioGroupNum] = GpioType;			
			break;

		case Gpio4x:
			SetupData->F75113_GP4x_Data[GpioGroupNum] = GpioVal;
			SetupData->F75113_GP4x_Type[GpioGroupNum] = GpioType;			
			break;																

		default:
			break;

	}	
}

VOID F75113LDNSelect(UINT8 Ldn)
{
	IoWrite8(F75113_CONFIG_INDEX, 0x07);
	IoWrite8(F75113_CONFIG_DATA, Ldn);
}

VOID F75113ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F75113_CONFIG_INDEX, Index);
	IoWrite8(F75113_CONFIG_DATA, Data);
}

UINT8 F75113ConfigRegisterRead(UINT8 Index)
{
	UINT8 RegTmp8;
	IoWrite8(F75113_CONFIG_INDEX, Index);
	RegTmp8 = IoRead8(F75113_CONFIG_DATA);
	return RegTmp8;
}

VOID F75113EnterConfigMode()
{
	UINT8 F75113ConfigModeEnterValue[2] = {0x50,0x50};
	UINT8 i;

	// Enter config mode
	for(i=0;i<=0x01;i++){
		IoWrite8(F75113_CONFIG_INDEX, F75113ConfigModeEnterValue[i]);
		IoWrite8(0xEB, 0xFF); // IO delay
	}
}

VOID F75113ExitConfigMode()
{
	UINT8 F75113ConfigModeExitRegister = 0xAA;
	
	// Exit config mode
	IoWrite8(F75113_CONFIG_INDEX, F75113ConfigModeExitRegister);
}
//----------------------------------------------------------------------------
//
// Procedure:   F75113GetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 F75113GetGpio(IN UINT8 GpioNum)
{
	UINT8	RegTmp8, GpioGroup;
    UINT8   StatusRegArray[5] = {0x12, 0x22, 0x32, 0x42, 0x72};
	
	F75113EnterConfigMode();	
	F75113LDNSelect(F75113_LDN_GPIO);	//GPIO Device Configuration Registers
	
	GpioGroup = GpioNum/10;

	RegTmp8 = F75113ConfigRegisterRead(StatusRegArray[GpioGroup]);	//Pin Status Register
	RegTmp8 = RegTmp8 >> ( GpioNum%10 );
	RegTmp8 &= BIT0;
	
	F75113ExitConfigMode();
	return RegTmp8;
}
#endif //PEI_BUILD
#endif //F75113_SUPPORT