
#include "Token.h"
#include <Library/IoLib.h>
#include "AaeonCommonLib.h"

#if defined(AAEON_BFPI_SUPPORT) && (AAEON_BFPI_SUPPORT == 1)
UINT8 WdtSourceTypeSio1[] = {
		#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
			F81866_CHIP_TYPE,	
		#endif
		#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
			F81966_CHIP_TYPE,	
		#endif
		#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
			F81804_CHIP_TYPE,	
		#endif
		#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
			IT8728F_CHIP_TYPE,
		#endif
		#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
			IT8625_CHIP_TYPE,
		#endif
		// Others to be implemented
		// End of table
		0xFF
};

UINT8 WdtSourceTypeEc1[] = {
		#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
			IT851X_CHIP_TYPE,	
		#endif
		// Others to be implemented
		// End of table
		0xFF
};

// Other source type to be implemented
#endif

//----------------------------------------------------------------------------
//
// Procedure:   AaeonDisableWatchDog
//
// Description: This function is a general dispatcher to disable WDT.
//
// Input:       ChipType : Select WDT chip to operate
//
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID AaeonDisableWatchDog(
	IN UINT8 ChipType
)
{
	switch(ChipType)
	{
		case F81866_CHIP_TYPE:
			#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
				F81866DisableWdt();	
			#endif
			break;

		case F81966_CHIP_TYPE:
			#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
				F81966DisableWdt();	
			#endif
			break;			

		case F81801_CHIP_TYPE:
			// To be implemented
			break;	

		case F81804_CHIP_TYPE:
			#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
				F81804DisableWdt();	
			#endif
			break;	

		case F81216SEC_CHIP_TYPE:
			// To be implemented
			break;

		case IT8728F_CHIP_TYPE:
			#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
				IT8728FDisableWdt();
			#endif	
			break;

		case IT8625_CHIP_TYPE:
			#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
				IT8625DisableWdt();
			#endif	
			break;

		case W83627DHG_CHIP_TYPE:
			// To be implemented
			break;			

		case IT851X_CHIP_TYPE:
			#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
				IT8518DisableWdt();
			#endif	
			break;			

		case SOC_CHIP_TYPE:
			// To be implemented
			break;				

#if defined(AAEON_BFPI_SUPPORT) && (AAEON_BFPI_SUPPORT == 1)
		case SOURCE_TYPE_SIO1:
			if (sizeof(WdtSourceTypeSio1) > 1)
			{
				AaeonDisableWatchDog(WdtSourceTypeSio1[0]);	// Basically enable 1 WDT is sufficient. This algorithm can be improved in future.
			}
			break;
		case SOURCE_TYPE_EC1:
			if (sizeof(WdtSourceTypeEc1) > 1)
			{
				AaeonDisableWatchDog(WdtSourceTypeEc1[0]);	// Basically enable 1 WDT is sufficient. This algorithm can be improved in future.
			}
			break;
			// Other source type to be implemented
#endif

		default:
			break;

	}	
    
}

//----------------------------------------------------------------------------
//
// Procedure:   AaeonEnableWatchDog
//
// Description: This function is a general dispatcher to enable WDT.
//
// Input:       ChipType : Select WDT chip to operate
//              TimeUnit   - Unit of Timer value : 0 - Second; 1 - Minut
//              Timer - Timer value to set to WDT
//
// Output:      
//
// Notes:       
//----------------------------------------------------------------------------
VOID AaeonEnableWatchDog(
	IN UINT8 ChipType,
    IN UINT8 TimeUnit,
    IN UINT8 Timer
)
{
	switch(ChipType)
	{
		case F81866_CHIP_TYPE:
			#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
				F81866EnableWdt(TimeUnit,Timer);	
			#endif
			break;

		case F81966_CHIP_TYPE:
			#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
				F81966EnableWdt(TimeUnit,Timer);	
			#endif
			break;			

		case F81801_CHIP_TYPE:
			// To be implemented
			break;	

		case F81804_CHIP_TYPE:
			#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
				F81804EnableWdt(TimeUnit,Timer);	
			#endif
			break;	

		case F81216SEC_CHIP_TYPE:
			// To be implemented
			break;

		case IT8728F_CHIP_TYPE:
			#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
				IT8728FEnableWdt(TimeUnit,Timer);
			#endif	
			break;

		case IT8625_CHIP_TYPE:
			#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
				IT8625EnableWdt(TimeUnit,Timer);
			#endif	
			break;

		case W83627DHG_CHIP_TYPE:
			// To be implemented
			break;			

		case IT851X_CHIP_TYPE:
			#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
				IT8518EnableWdt(TimeUnit,Timer);
			#endif	
			break;			

		case SOC_CHIP_TYPE:
			// To be implemented
			break;				

#if defined(AAEON_BFPI_SUPPORT) && (AAEON_BFPI_SUPPORT == 1)
		case SOURCE_TYPE_SIO1:
			if (sizeof(WdtSourceTypeSio1) > 1)
			{
				AaeonEnableWatchDog(WdtSourceTypeSio1[0],TimeUnit,Timer);	// Basically enable 1 WDT is sufficient. This algorithm can be improved in future.
			}
			break;
		case SOURCE_TYPE_EC1:
			if (sizeof(WdtSourceTypeEc1) > 1)
			{
				AaeonEnableWatchDog(WdtSourceTypeEc1[0],TimeUnit,Timer);	// Basically enable 1 WDT is sufficient. This algorithm can be improved in future.
			}
			break;
			// Other source type to be implemented
#endif

		default:
			break;

	}	
    
}
