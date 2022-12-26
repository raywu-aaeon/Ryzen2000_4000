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
#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   IT8625SetGpio
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
IT8625SetGpio ( 
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
			SetupData->IT8625Gpio1x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio1x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio2x:
			SetupData->IT8625Gpio2x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio2x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio3x:
			SetupData->IT8625Gpio3x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio3x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio4x:
			SetupData->IT8625Gpio4x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio4x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio5x:
			SetupData->IT8625Gpio5x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio5x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio6x:
			SetupData->IT8625Gpio6x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio6x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio7x:
			SetupData->IT8625Gpio7x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio7x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio8x:
			SetupData->IT8625Gpio8x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio8x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio9x:
			SetupData->IT8625Gpio9x_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625Gpio9x_Oe[GpioGroupNum] = GpioType;
			break;

		case GpioAx:
			SetupData->IT8625GpioAx_Val[GpioGroupNum] = GpioVal;
			SetupData->IT8625GpioAx_Oe[GpioGroupNum] = GpioType;
			break;

		default:
			break;

	}
}

//----------------------------------------------------------------------------
//
// Procedure:   IT8625SetGpioFnType
//
// Description: This function is setting the function as the Simple I/O function
//		or the Alternate function
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              GpioFnType - The function type of GPIO
//		  - 0 for Alternate function
//		  - 1 for Simple I/O function
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID
IT8625SetGpioFnType ( 
	IN UINT8 	GpioNum,
	IN UINT8 	GpioFnType,
	IN SETUP_DATA	*SetupData
)	
{
	UINT8	GpioGroup, GpioGroupNum;

	GpioGroup = GpioNum / 10;
	GpioGroupNum = GpioNum % 10;

	switch(GpioGroup)
	{
		case Gpio1x:
			SetupData->IT8625Gpio1x_Se[GpioGroupNum] = GpioFnType;
			break;	

		case Gpio2x:
			SetupData->IT8625Gpio2x_Se[GpioGroupNum] = GpioFnType;
			break;

		case Gpio3x:
			SetupData->IT8625Gpio3x_Se[GpioGroupNum] = GpioFnType;
			break;

		case Gpio4x:
			SetupData->IT8625Gpio4x_Se[GpioGroupNum] = GpioFnType;
			break;

		case Gpio5x:
			SetupData->IT8625Gpio5x_Se[GpioGroupNum] = GpioFnType;
			break;

		case Gpio9x:
			SetupData->IT8625Gpio9x_Se[GpioGroupNum] = GpioFnType;
			break;

		case GpioAx:
			SetupData->IT8625GpioAx_Se[GpioGroupNum] = GpioFnType;
			break;

		default:
			break;
	}
}
#endif //PEI_BUILD

VOID IT8625LDNSelect(UINT8 Ldn)
{
	IoWrite8(IT8625_CONFIG_INDEX, IT8625_LDN_SEL_REGISTER);
	IoWrite8(IT8625_CONFIG_DATA, Ldn);
}
VOID IT8625ConfigRegisterWrite(UINT8 Index, UINT8 Data)
{
	IoWrite8(IT8625_CONFIG_INDEX, Index);
	IoWrite8(IT8625_CONFIG_DATA, Data);
}
UINT8 IT8625ConfigRegisterRead(UINT8 Index)
{
	UINT8 Data8;
	IoWrite8(IT8625_CONFIG_INDEX, Index);
	Data8 = IoRead8(IT8625_CONFIG_DATA);
	return Data8;
}
VOID IT8625EnterConfigMode()
{
	UINT8 IT8625ConfigModeEnterValue[4] = {0x87, 0x01, 0x55, 0x55};
	UINT8 i;

	// Enter config mode
	for(i=0;i<=0x03;i++){
		IoWrite8(IT8625_CONFIG_INDEX, IT8625ConfigModeEnterValue[i]);
		IoWrite8(0xEB, 0xFF); // IO delay
	}
}
VOID IT8625ExitConfigMode()
{
	UINT8 IT8625ConfigModeExitRegister = 0x02;

	// Exit config mode
	IoWrite8(IT8625_CONFIG_INDEX, IT8625ConfigModeExitRegister);
	IoWrite8(0xEB, 0xFF); // IO delay
	IoWrite8(IT8625_CONFIG_DATA, BIT1);
}
//----------------------------------------------------------------------------
//
// Procedure:   IT8625GetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 IT8625GetGpio(IN UINT8 GpioNum)
{
	UINT8 RegTmp8;
	UINT16 Address;
	
	Address = IT8625_GPIO_BASE_ADDRESS + ((GpioNum / 10)-1);	// Get GPIO Group I/O Address
	RegTmp8 = IoRead8(Address);					// Read GPIO status register value
	RegTmp8 = RegTmp8 >> (GpioNum % 10);				// Shift the specific GPIO pin status to bit 0
	RegTmp8 &= BIT0;						// Only reserved the specific GPIO pin status

	return RegTmp8;
}

VOID IT8625EnableWdt(UINT8 TimeUnit,UINT8 Time)
{
    UINT8 temp = 0;

    IT8625EnterConfigMode();

    IT8625ConfigRegisterWrite(IT8625_LDN_SEL_REGISTER, IT8625_LDN_GPIO);
 
    temp = IT8625ConfigRegisterRead(0x72);
    temp &= ~(BIT6 + BIT5 + BIT4);	// Disable counting (BIT6 & BIT4) and Set WDT Time-out value extra (BIT5).
    temp |= (~TimeUnit << 7);		// Set Time Unit
    temp |= (BIT6 + BIT4);		// Enable WDT Output through PWRGD and KRST
    IT8625ConfigRegisterWrite(0x72, temp);    
    IT8625ConfigRegisterWrite(0x73, Time);

    IT8625ExitConfigMode();
}

VOID IT8625DisableWdt()
{
    UINT8 Data8 = 0;

    IT8625EnterConfigMode();

    IT8625ConfigRegisterWrite(IT8625_LDN_SEL_REGISTER, IT8625_LDN_GPIO);

    Data8 = IT8625ConfigRegisterRead(0x72);
    Data8 = Data8 & ~(BIT6 + BIT4);  // Disable WDT Output through PWRGD/KRST

    IT8625ConfigRegisterWrite(0x72, Data8);
    IT8625ConfigRegisterWrite(0x73, 0);

    IT8625ExitConfigMode();
}

UINT8 IT8625GetIoLdnValue(UINT8 IOLDN,UINT8 RegisterOffset)
{
    UINT8  Value=0;

    IT8625EnterConfigMode();
    
    IoWrite8(IT8625_CONFIG_INDEX, IT8625_LDN_SEL_REGISTER);
    IoWrite8(IT8625_CONFIG_DATA, IOLDN);
    
    IoWrite8(IT8625_CONFIG_INDEX, RegisterOffset);
    Value = IoRead8(IT8625_CONFIG_DATA);
    
    IT8625ExitConfigMode();
    
    return Value;
}
#endif //IT8625_SUPPORT