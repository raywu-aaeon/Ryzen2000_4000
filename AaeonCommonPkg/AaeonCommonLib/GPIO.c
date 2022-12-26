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
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   AaeonSetGpio
//
// Description: This function is setting the GPIO high/low and input/output
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              GpioVal - The high/low of GPIO, 1 for high, 0 for low
//              GpioType - The input/output of GPIO, 1 for output, 0 for input
//              ChipType - The TOKEN value of GPIO source chip, refer to Readme.md
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID
AaeonSetGpio ( 
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN UINT8	ChipType,
	IN SETUP_DATA	*SetupData
)	
{
	switch(ChipType)
	{
		case F81866_CHIP_TYPE:
			#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
				F81866SetGpio(GpioNum, GpioVal, GpioType, SetupData);	
			#endif
			break;

		case F81966_CHIP_TYPE:
			#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
				F81966SetGpio(GpioNum, GpioVal, GpioType, SetupData);	
			#endif
			break;			

		case F81801_CHIP_TYPE:

			break;	

		case F81216SEC_CHIP_TYPE:

			break;

		case IT8728F_CHIP_TYPE:
			#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
				IT8728FSetGpio(GpioNum, GpioVal, GpioType, SetupData);
			#endif	
			break;

		case IT8625_CHIP_TYPE:
			#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
				IT8625SetGpio(GpioNum, GpioVal, GpioType, SetupData);
			#endif	
			break;

		case W83627DHG_CHIP_TYPE:
		
			break;					
		case F75111_CHIP_TYPE:
			#if defined(F75111PeiPkg_SUPPORT) && (F75111PeiPkg_SUPPORT == 1)	
				F75111SetGpio(GpioNum, GpioVal, GpioType, SetupData);
			#endif
			break;	

		case F81804_CHIP_TYPE:
			#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
				F81804SetGpio(GpioNum, GpioVal, GpioType, SetupData);	
			#endif
			break;

		case F75113_CHIP_TYPE:
			#if defined(F75113_SUPPORT) && (F75113_SUPPORT == 1)
				F75113SetGpio(GpioNum, GpioVal, GpioType, SetupData);
			#endif  
			break;  

		case SOC_CHIP_TYPE:
		
			break;				

		default:
			break;

	}	
}	
#endif //PEI_BUILD

//----------------------------------------------------------------------------
//
// Procedure:   AaeonGetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       ChipType - The number of GPIO source chip, refer to Readme.md
//              GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 AaeonGetGpio(IN UINT8 ChipType, IN UINT8 GpioNum)
{
	UINT8	RegTmp8 = 0;
	
	switch(ChipType)
	{
		case F81866_CHIP_TYPE:
			#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
				RegTmp8 = F81866GetGpio(GpioNum);	
			#endif
			break;

		case F81966_CHIP_TYPE:
			#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
				RegTmp8 = F81966GetGpio(GpioNum);	
			#endif
			break;			

		case F81801_CHIP_TYPE:
		
			break;	

		case F81216SEC_CHIP_TYPE:
		
			break;

		case IT8728F_CHIP_TYPE:
			#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
				RegTmp8 = IT8728FGetGpio(GpioNum);	
			#endif			
			break;

		case IT8625_CHIP_TYPE:
			#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
				RegTmp8 = IT8625GetGpio(GpioNum);	
			#endif			
			break;

		case W83627DHG_CHIP_TYPE:
		
			break;

		case F75111_CHIP_TYPE:
			#if defined(F75111PeiPkg_SUPPORT) && (F75111PeiPkg_SUPPORT == 1)	
				RegTmp8 = F75111GetGpio(GpioNum);	
			#endif
			break;

		case F81804_CHIP_TYPE:
			#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
				RegTmp8 = F81804GetGpio(GpioNum);	
			#endif
			break;	

		case F75113_CHIP_TYPE:
			#if defined(F75113_SUPPORT) && (F75113_SUPPORT == 1)
				RegTmp8 = F75113GetGpio(GpioNum);  
			#endif  
			break;  

		case SOC_CHIP_TYPE:
		
			break;							

		default:
			return 0;
	}
	return RegTmp8;
}