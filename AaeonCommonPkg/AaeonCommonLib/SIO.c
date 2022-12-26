//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include "AaeonCommonLib.h"
#include "Token.h"
#include <Library/IoLib.h>

#if defined(AAEON_BFPI_SUPPORT) && (AAEON_BFPI_SUPPORT == 1)
UINT8 SioSourceTypeSio1[] = {
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

UINT8 SioSourceTypeEc1[] = {
		#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
			IT851X_CHIP_TYPE,	
		#endif
		// Others to be implemented
		// End of table
		0xFF
};

// Other source type to be implemented
#endif
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   AaeonGetIoLdnValue
//
// Description: This function is getting the SIO Logic Device Register.
//
// Input:       
//              ChipType      : Select WDT chip to operate
//              IOLDN         : LDN number
//              RegisterOffset: 
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
UINT8
AaeonGetIoLdnValue (
    IN UINT8 ChipType, 
	IN UINT8 IOLDN,
	IN UINT8 RegisterOffset
)	
{
    UINT8 Data = 0;
	switch(ChipType)
	{
		case F81866_CHIP_TYPE:
			#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
		        Data = F8186GetIoLdnValue(IOLDN,RegisterOffset);	
			#endif
			break;

		case F81966_CHIP_TYPE:
			#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
		        Data = F81966GetIoLdnValue(IOLDN,RegisterOffset);	
			#endif
			break;			

		case F81801_CHIP_TYPE:
			// To be implemented
			break;	

		case F81804_CHIP_TYPE:
			#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
		        Data = F81804GetIoLdnValue(IOLDN,RegisterOffset);	
			#endif
			break;	

		case F81216SEC_CHIP_TYPE:
			// To be implemented
			break;

		case IT8728F_CHIP_TYPE:
			#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
		        Data = IT8728FGetIoLdnValue(IOLDN,RegisterOffset);
			#endif	
			break;

		case IT8625_CHIP_TYPE:
			#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
		        Data = IT8625GetIoLdnValue(IOLDN,RegisterOffset);
			#endif	
			break;

		case W83627DHG_CHIP_TYPE:
			// To be implemented
			break;			

		case IT851X_CHIP_TYPE:
			#if defined(IT8518_SUPPORT) && (IT8518_SUPPORT == 1)
		        Data = IT8518GetIoLdnValue(IOLDN,RegisterOffset);
			#endif	
			break;			

		case SOC_CHIP_TYPE:
			// To be implemented
			break;				

#if defined(AAEON_BFPI_SUPPORT) && (AAEON_BFPI_SUPPORT == 1)
		case SOURCE_TYPE_SIO1:
			if (sizeof(SioSourceTypeSio1) > 1)
			{
			    Data = AaeonGetIoLdnValue(SioSourceTypeSio1[0],IOLDN,RegisterOffset);
			}
			break;
		case SOURCE_TYPE_EC1:
			if (sizeof(SioSourceTypeEc1) > 1)
			{
			    Data = AaeonGetIoLdnValue(SioSourceTypeEc1[0],IOLDN,RegisterOffset);
			}
			break;
			// Other source type to be implemented
#endif

		default:
			break;

	}	
  	
	return Data;
}	
#endif //PEI_BUILD
