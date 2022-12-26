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
#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   F81866SetGpio
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
F81866SetGpio ( 
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
			SetupData->F81866Gpio0x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio0x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio1x:
			SetupData->F81866Gpio1x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio1x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio2x:
			SetupData->F81866Gpio2x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio2x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio3x:
			SetupData->F81866Gpio3x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio3x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio4x:
			SetupData->F81866Gpio4x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio4x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio5x:
			SetupData->F81866Gpio5x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio5x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio6x:
			SetupData->F81866Gpio6x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio6x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio7x:
			SetupData->F81866Gpio7x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio7x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio8x:
			SetupData->F81866Gpio8x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81866Gpio8x_Oe[GpioGroupNum] = GpioType;
			break;														

		default:
			break;

	}	
}
#endif //PEI_BUILD

VOID F81866LDNSelect(UINT8 Ldn)
{
	IoWrite8(F81866_CONFIG_INDEX, 0x07);
	IoWrite8(F81866_CONFIG_DATA, Ldn);
}

VOID F81866ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F81866_CONFIG_INDEX, Index);
	IoWrite8(F81866_CONFIG_DATA, Data);
}

UINT8 F81866ConfigRegisterRead(UINT8 Index)
{
	UINT8 RegTmp8;
	IoWrite8(F81866_CONFIG_INDEX, Index);
	RegTmp8 = IoRead8(F81866_CONFIG_DATA);
	return RegTmp8;
}

VOID F81866EnterConfigMode()
{
	UINT8 F81866ConfigModeEnterValue[2] = {0x87,0x87};
	UINT8 i;

	// Enter config mode
	for(i=0;i<=0x01;i++){
		IoWrite8(F81866_CONFIG_INDEX, F81866ConfigModeEnterValue[i]);
		IoWrite8(0xEB, 0xFF); // IO delay
	}
}

VOID F81866ExitConfigMode()
{
	UINT8 F81866ConfigModeExitRegister = 0xAA;
	
	// Exit config mode
	IoWrite8(F81866_CONFIG_INDEX, F81866ConfigModeExitRegister);
}
//----------------------------------------------------------------------------
//
// Procedure:   F81866GetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 F81866GetGpio(IN UINT8 GpioNum)
{
	UINT8	RegTmp8, Offset;
	
	F81866EnterConfigMode();	
	F81866LDNSelect(F81866_LDN_GPIO);	//GPIO Device Configuration Registers
	
	if( (GpioNum/10) <= 7 )
	{
		Offset = ( ~(GpioNum/10) );
		Offset = Offset << 4;
		Offset &= 0xF0;
	}
	else if ( (GpioNum/10) >= 8 )
	{
		Offset = 0x88;	
	}
	RegTmp8 = F81866ConfigRegisterRead(Offset + 2);	//Pin Status Register
	RegTmp8 = RegTmp8 >> ( GpioNum%10 );
	RegTmp8 &= BIT0;
	
	F81866ExitConfigMode();
	return RegTmp8;
}

VOID F81866EnableWdt(UINT8 TimeUnit,UINT8 Time)
{
	UINT8 temp=0;

	F81866EnterConfigMode();

	F81866ConfigRegisterWrite(F81866_LDN_SEL_REGISTER,0x07);
 
	temp = F81866ConfigRegisterRead(0xF5);
	temp &= ~(BIT5+BIT3);	// Disable counting (WD_EN), clear unit setting
	temp |= BIT6;	// Clear status
	temp |= (TimeUnit << 3);	//Set Time Unit
	F81866ConfigRegisterWrite(0xF5,temp);
	
	F81866ConfigRegisterWrite(0xF6,Time);
	F81866ConfigRegisterWrite(0xF5,F81866ConfigRegisterRead(0xF5) | BIT5);

	F81866ExitConfigMode();
}

VOID F81866DisableWdt()
{
	UINT8 Data8 = 0;

	F81866EnterConfigMode();

	F81866ConfigRegisterWrite(F81866_LDN_SEL_REGISTER,0x07);

	Data8 = F81866ConfigRegisterRead(0xF5);
	Data8 = Data8 & ~BIT5;	// Disable counting (WD_EN)
	Data8 |= BIT6;	// Clear status
	F81866ConfigRegisterWrite(0xF5,Data8);

	F81866ExitConfigMode();
}

UINT8 F81866GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset)
{
    UINT8  Value=0;
    F81866EnterConfigMode();
    
    IoWrite8(F81866_CONFIG_INDEX,F81866_LDN_SEL_REGISTER);
    IoWrite8(F81866_CONFIG_DATA,IOLDN);
    
    IoWrite8(F81866_CONFIG_INDEX,RegisterOffset);
    Value = IoRead8(F81866_CONFIG_DATA);
    
    F81866ExitConfigMode();
    
    return Value;
}
#endif //F81866_SUPPORT
