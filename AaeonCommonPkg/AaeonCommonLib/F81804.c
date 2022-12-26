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
#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   F81804SetGpio
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
F81804SetGpio ( 
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
			SetupData->F81804Gpio0x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio0x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio1x:
			SetupData->F81804Gpio1x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio1x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio2x:
			SetupData->F81804Gpio2x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio2x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio5x:
			SetupData->F81804Gpio5x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio5x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio6x:
			SetupData->F81804Gpio6x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio6x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio7x:
			SetupData->F81804Gpio7x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio7x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio9x:
			SetupData->F81804Gpio9x_Val[GpioGroupNum] = GpioVal;
			SetupData->F81804Gpio9x_Oe[GpioGroupNum] = GpioType;
			break;																	

		default:
			break;

	}	
}
#endif //PEI_BUILD

VOID F81804LDNSelect(UINT8 Ldn)
{
	IoWrite8(F81804_CONFIG_INDEX, 0x07);
	IoWrite8(F81804_CONFIG_DATA, Ldn);
}

VOID F81804ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(F81804_CONFIG_INDEX, Index);
	IoWrite8(F81804_CONFIG_DATA, Data);
}

UINT8 F81804ConfigRegisterRead(UINT8 Index)
{
	UINT8 RegTmp8;
	IoWrite8(F81804_CONFIG_INDEX, Index);
	RegTmp8 = IoRead8(F81804_CONFIG_DATA);
	return RegTmp8;
}

VOID F81804EnterConfigMode()
{
	UINT8 F81804ConfigModeEnterValue[2] = {F81804_CONFIG_MODE_ENTER_VALUE,F81804_CONFIG_MODE_ENTER_VALUE};
	UINT8 i;

	// Enter config mode
	for(i=0;i<=0x01;i++){
		IoWrite8(F81804_CONFIG_INDEX, F81804ConfigModeEnterValue[i]);
		IoWrite8(0xEB, 0xFF); // IO delay
	}
}

VOID F81804ExitConfigMode()
{
	UINT8 F81804ConfigModeExitRegister = F81804_CONFIG_MODE_EXIT_VALUE;
	
	// Exit config mode
	IoWrite8(F81804_CONFIG_INDEX, F81804ConfigModeExitRegister);
}
//----------------------------------------------------------------------------
//
// Procedure:   F81804GetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 F81804GetGpio(IN UINT8 GpioNum)
{
	UINT8	RegTmp8, GpioGroup, GpioGroupNum, NoUse=0;
	
    //GPIO0x Pin Status Register Register 0xF2
    //GPIO1x Pin Status Register Register 0xE2
    //GPIO2x Pin Status Register Register 0xD2
    //GPIO5x Pin Status Register Register 0xA2
    //GPIO6x Pin Status Register Register 0x92
    //GPIO7x Pin Status Register Register 0x82
    //GPIO9x Pin Status Register Register 0x9A
    UINT8 	F81804_Status_Reg[10] = {0xF2, 0xE2, 0xD2, NoUse, NoUse, 0xA2, 0x92, 0x82, NoUse, 0x9A};
    	
   	GpioGroup = GpioNum / 10;
	GpioGroupNum = GpioNum % 10;

	F81804EnterConfigMode();	
	F81804LDNSelect(F81804_LDN_GPIO);	//GPIO Device Configuration Registers

	RegTmp8 = F81804ConfigRegisterRead(F81804_Status_Reg[GpioGroup]);	//Pin Status Register
	RegTmp8 = RegTmp8 >> GpioGroupNum;  //Move status bit to BIT0
	RegTmp8 &= BIT0;  //Clear no use bit
	
	F81804ExitConfigMode();
	return RegTmp8;
}

VOID F81804EnableWdt(UINT8 TimeUnit,UINT8 Time)
{
	UINT8 temp=0;

	F81804EnterConfigMode();

	F81804ConfigRegisterWrite(F81804_LDN_SEL_REGISTER,0x07);
 
	temp = F81804ConfigRegisterRead(0xF5);
	temp &= ~(BIT5+BIT3);	// Disable counting (WD_EN), clear unit setting
	temp |= BIT6;	// Clear status
	temp |= (TimeUnit << 3);	//Set Time Unit
	F81804ConfigRegisterWrite(0xF5,temp);
	
	F81804ConfigRegisterWrite(0xF6,Time);
	F81804ConfigRegisterWrite(0xF5,F81804ConfigRegisterRead(0xF5) | BIT5);

	F81804ExitConfigMode();
}

VOID F81804DisableWdt()
{
	UINT8 Data8 = 0;

	F81804EnterConfigMode();

	F81804ConfigRegisterWrite(F81804_LDN_SEL_REGISTER,0x07);

	Data8 = F81804ConfigRegisterRead(0xF5);
	Data8 = Data8 & ~BIT5;	// Disable counting (WD_EN)
	Data8 |= BIT6;	// Clear status
	F81804ConfigRegisterWrite(0xF5,Data8);

	F81804ExitConfigMode();
}

UINT8 F81804GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset)
{
    UINT8  Value=0;
    F81804EnterConfigMode();
    
    IoWrite8(F81804_CONFIG_INDEX,F81804_LDN_SEL_REGISTER);
    IoWrite8(F81804_CONFIG_DATA,IOLDN);
    
    IoWrite8(F81804_CONFIG_INDEX,RegisterOffset);
    Value = IoRead8(F81804_CONFIG_DATA);
    
    F81804ExitConfigMode();
    
    return Value;
}
#endif //F81804_SUPPORT
