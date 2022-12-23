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

/** @file AmiSmbiosLib.h
  This file contains South Bridge(LPC) chipset porting library SMBIOS 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_SMBIOS_LIB_H__
#define __AMI_SMBIOS_LIB_H__

#include <Uefi.h>
#include "Token.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum _SB_WAKEUP_TYPE {
	SbWakeupTypeOther = 1,
	SbWakeupTypeUnknown = 2,
	SbWakeupTypeApmTimer = 3,
	SbWakeupTypeModemRing = 4,
	SbWakeupTypeLanRemote = 5,
	SbWakeupTypePowerSwitch = 6,
	SbWakeupTypePciPme = 7,
	SbWakeupTypeAcPowerRestored = 8,
	SbWakeupTypeSmBiosMax,
	SbWakeupTypeMax
} SB_WAKEUP_TYPE;

UINT8 getWakeupTypeForSmbios (
    VOID
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
