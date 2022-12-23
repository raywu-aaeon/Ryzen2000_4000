//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiCspSmmServicesLib.h
  This file contains chipset porting SMM services library 
  functions and data structure definitions for SMM stage.
  
*/

#ifndef __AMI_CSP_SMM_SERVICES_LIB_H__
#define __AMI_CSP_SMM_SERVICES_LIB_H__

#include <PiDxe.h>
#include <PiSmm.h>
#include "Token.h"
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>


#ifdef __cplusplus
extern "C" {
#endif

EFI_STATUS CspInitSmmHandler(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN EFI_STATUS       (*InSmmFunction)(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
);

#ifdef __cplusplus
}
#endif
#endif


//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
