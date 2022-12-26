#ifndef __AAEON_UART_MODE__H__
#define __AAEON_UART_MODE__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <token.h>
#include <Protocol/AmiSio.h>
#include <AmiGenericSio.h>
#include <Library\AmiSioDxeLib.h>
//****************************************************************************/
//		TYPE DECLARATIONS
//****************************************************************************/
//**********************************************************************
//<AMI_THDR_START>
//
// Name: DBE_DATABASE_STRUCT
//
// Fields:	
// ColNum	Type		Description
//	1		UINTN		Initial elements Count of index array to be created
//	2		UINTN		Current RecordCount stored in Database
//	3		UINTN		Number of Indexes in Database
//	4		DBE_INDEX*	Pointerto the indexes information of this Database;
//	5		VOID		*IndexArray;
//
// Description:	Initial structure to hold Database information
//
// Notes:	
//
//<AMI_THDR_END>
//**********************************************************************


//****************************************************************************/
//		MACROS DECLARATIONS
//****************************************************************************/
#define  RS232  0
#define  RS422  1
#define  RS485  2 

#define  F81438 0
#define  HW_DESIGN 1

#define Enabled 1
#define Disabled 0	
//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/

//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/

EFI_STATUS
EFIAPI
HwDesignSetMode ( 
	IN UINT8 	UartMode,
	IN UINT8 	UartModeSource,
	IN UINT8	*UartModeGpioTable,
	IN SETUP_DATA	*SetupData
);

EFI_STATUS
EFIAPI
F81438SetMode (
	IN UINT8 	UartMode,
	IN UINT8 	UartModeSource,
	IN UINT8	*UartModeGpioTable,
	IN SETUP_DATA	*SetupData
);

VOID
SioSetFlowControl ( 
	IN UINT8 	UartIndex,
	IN UINT8 	UartMode,
	IN UINT8	UartModeSource,
	IN SETUP_DATA	*SetupData
);

EFI_STATUS
EFIAPI
UartModeInit ( 
	IN UINT8 	UartNum,
	IN UINT8 	UartLdn,
	IN UINT8 	UartModeIndex,
	IN EFI_STRING	SioNvDataName,
	IN SETUP_DATA	*SetupData
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
