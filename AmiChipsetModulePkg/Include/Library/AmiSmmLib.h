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

/** @file AmiCmosLib.h
  This file contains South Bridge(LPC) chipset porting library SMM 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_SMM_LIB_H__
#define __AMI_SMM_LIB_H__

#include <PiDxe.h>
#include <PiSmm.h>
#include "Token.h"


#ifdef __cplusplus
extern "C" {
#endif

#if SMM_SUPPORT
EFI_STATUS SbSmmSaveRestoreStates (
    IN BOOLEAN                      Save
);
#endif

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
