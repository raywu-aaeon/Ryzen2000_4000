#ifndef __AAEON_DIO__H__
#define __AAEON_DIO__H__
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

//****************************************************************************/
//		VARIABLE DECLARATIONS
//****************************************************************************/

//****************************************************************************/
//		FUNCTION DECLARATIONS
//****************************************************************************/

EFI_STATUS
EFIAPI
DioInit ( 
	IN SETUP_DATA	*SetupData
);

#pragma pack (push,1)
typedef struct {
	// Layout must be same as "WDCB" defined in AaeonDio3.asl
	UINT32 DioBufferAddress;		//Offset 0		// DIO Capability Buffer Address
	// Config:
	// [0] - Interrupt Enabled:
	//    0 - No DIO pin enabled for interrupt.
	//    1 - At least one DIO pin enabled.
	// Other bits - Reserved.
	UINT8  Config0;			//Offset 4
	UINT8  Config1;			//Offset 5
	UINT8  Config2;			//Offset 6
	UINT8  Config3;			//Offset 7
	// Pin capabilities
	UINT32 DioInCap[4];		//Offset 8		// DIO Input Capability for pin 1~128
	UINT32 DioOutCap[4];	//Offset 24		// DIO Input Capability for pin 1~128
	UINT32 DioDrvCap[4];	//Offset 40		// DIO Input Capability for pin 1~128
	UINT32 DioIntCap[4];	//Offset 56		// DIO Input Capability for pin 1~128
	UINT32 DioSource;		//Offset 72		// 1st DIO Source IC
	UINT8 DioGpioNum[128];  //Offset 76		// 1st DIO GPIO mapping
	UINT32 Dio2Source;		//Offset 204	// 2nd DIO Source IC
	UINT8 Dio2GpioNum[128];	//Offset 208	// 2nd DIO GPIO mapping
    // TODO: Porting may be required if 3rd DIO controller is supported.
    #if defined(THIRD_DIO_NUMBER) && (THIRD_DIO_NUMBER > 0)
	UINT32 Dio3Source;		//Offset 336	// 3rd DIO Source IC
	UINT8 Dio3GpioNum[128];	//Offset 340	// 3rd DIO GPIO mapping
	#endif
} AAEON_DIO_GLOBAL_NVS_AREA;
#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
