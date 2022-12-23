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

/** @file AmiTimerIntLib.h
  This file contains chipset porting library timer interrupt functions 
  and data structure definitions.
  
*/

#ifndef __AMI_TIMER_INT_LIB_H__
#define __AMI_TIMER_INT_LIB_H__

#include <Uefi.h>
#include "Token.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef VOID (SAVE_RESTORE_CALLBACK)( BOOLEAN Save );


VOID SaveRestoreRegisters(
    IN BOOLEAN Save
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
