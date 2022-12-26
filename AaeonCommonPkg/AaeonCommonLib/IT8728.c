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
#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   IT8728FSetGpio
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
IT8728FSetGpio ( 
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
		case Gpio1x:
			SetupData->IT8728FGpio1x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio1x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio2x:
			SetupData->IT8728FGpio2x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio2x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio3x:
			SetupData->IT8728FGpio3x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio3x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio4x:
			SetupData->IT8728FGpio4x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio4x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio5x:
			SetupData->IT8728FGpio5x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio5x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio6x:
			SetupData->IT8728FGpio6x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio6x_Oe[GpioGroupNum] = GpioType;			
			break;

		case Gpio7x:
			SetupData->IT8728FGpio7x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio7x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio8x:
			SetupData->IT8728FGpio8x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8728FGpio8x_Oe[GpioGroupNum] = GpioType;
			break;														

		default:
			break;

	}	
}
#endif //PEI_BUILD
VOID IT8728FLDNSelect(UINT8 Ldn)
{
	IoWrite8(IT8728F_CONFIG_INDEX, 0x07);
	IoWrite8(IT8728F_CONFIG_DATA, Ldn);
}
VOID IT8728FConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(IT8728F_CONFIG_INDEX, Index);
	IoWrite8(IT8728F_CONFIG_DATA, Data);
}
UINT8 IT8728FConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(IT8728F_CONFIG_INDEX, Index);
	Data8 = IoRead8(IT8728F_CONFIG_DATA);
	return Data8;
}
VOID IT8728FEnterConfigMode()
{
	UINT8 IT8728FConfigModeEnterValue[4] = {0x87,0x01,0x55,0x55};
	UINT8 i;

	// Enter config mode
	for(i=0;i<=0x03;i++){
		IoWrite8(IT8728F_CONFIG_INDEX, IT8728FConfigModeEnterValue[i]);
		IoWrite8(0xEB, 0xFF); // IO delay
	}
}
VOID IT8728FExitConfigMode()
{
	UINT8 IT8728FConfigModeExitRegister = 0x02;

	// Exit config mode
	IoWrite8(IT8728F_CONFIG_INDEX, IT8728FConfigModeExitRegister);
	IoWrite8(0xEB, 0xFF); // IO delay
	IoWrite8(IT8728F_CONFIG_DATA, BIT1);
}
//----------------------------------------------------------------------------
//
// Procedure:   IT8728FGetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 IT8728FGetGpio(IN UINT8 GpioNum)
{
	UINT8 RegTmp8;
	UINT16 Address;
	
	Address = IT8728F_GPIO_BASE_ADDRESS + ((GpioNum/10)-1);
	RegTmp8 = IoRead8(Address);
	RegTmp8 = RegTmp8 >> (GpioNum % 10);	// Shift the specific GPIO pin status to bit 0
	RegTmp8 &= BIT0;			// Only reserved the specific GPIO pin status

	return RegTmp8;
}

VOID IT8728FEnableWdt(UINT8 TimeUnit,UINT8 Time)
{
    UINT8 temp=0;

    IT8728FEnterConfigMode();

    IT8728FConfigRegisterWrite(IT8728F_LDN_SEL_REGISTER,0x07);
 
    temp = IT8728FConfigRegisterRead(0x72);
    temp &= ~(BIT6+BIT5+BIT4);   // Disable counting (BIT6+BIT4) and Set WDT Time-out value extra(BIT5).
    temp |= (~TimeUnit << 7);    //Set Time Unit 
    temp |= (BIT6+BIT4);	// Enable WDT Output through PWRGD and KRST
    IT8728FConfigRegisterWrite(0x72,temp);    
    IT8728FConfigRegisterWrite(0x73,Time);

    IT8728FExitConfigMode();
}

VOID IT8728FDisableWdt()
{
    UINT8 Data8 = 0;

    IT8728FEnterConfigMode();

    IT8728FConfigRegisterWrite(IT8728F_LDN_SEL_REGISTER,0x07);

    Data8 = IT8728FConfigRegisterRead(0x72);
    Data8 = Data8 & ~(BIT6+BIT4);  // Disable WDT Output through PWRGD/KRST

    IT8728FConfigRegisterWrite(0x72,Data8);
    IT8728FConfigRegisterWrite(0x73,0);

    IT8728FExitConfigMode();
}

UINT8 IT8728FGetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset)
{
    UINT8  Value=0;
    IT8728FEnterConfigMode();
    
    IoWrite8(IT8728F_CONFIG_INDEX,IT8728F_LDN_SEL_REGISTER);
    IoWrite8(IT8728F_CONFIG_DATA,IOLDN);
    
    IoWrite8(IT8728F_CONFIG_INDEX,RegisterOffset);
    Value = IoRead8(IT8728F_CONFIG_DATA);
    
    IT8728FExitConfigMode();
    
    return Value;
}
#endif //IT8728F_SUPPORT