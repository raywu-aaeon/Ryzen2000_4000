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

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif