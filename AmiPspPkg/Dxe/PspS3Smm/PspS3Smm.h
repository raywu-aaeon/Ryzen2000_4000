//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************

/** @file PspS3Smm.h
    This file contains the Includes, Definitions, typedefs,
    Variable and External Declarations, Structure and
    function prototypes needed for the PspS3Smm driver

**/

#ifndef _PSP_S3_SMM_H_
#define _PSP_S3_SMM_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/FlashProtocol.h>


EFI_STATUS
InSmmFunction (
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
