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

/** @file AmiSmbiosLib.c
    South Bridge SMBIOS Library implementation

*/

#include <Library/AmiSmbiosLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>

#if SMBIOS_SUPPORT && SB_WAKEUP_TYPE_FN
/**
    Detect and return SMBIOS wake-up type

    @param VOID

    @retval 0x01 = Other
            0x02 = Unknown
            0x03 = APM Timer
            0x04 = Modem Ring
            0x05 = LAN Remote
            0x06 = Power Switch
            0x07 = PCI PME#
            0x08 = AC Power Restored

    @note  Porting required 
**/
UINT8 getWakeupTypeForSmbios (
    VOID
)
{
    UINT8   WakeupTypeForSmbios = PcdGet8(AmiPcdSbWakeType);

    if (WakeupTypeForSmbios >= SbWakeupTypeSmBiosMax) {
      WakeupTypeForSmbios = DEFAULT_SYSTEM_WAKEUP_TYPE;
    }
    
    return WakeupTypeForSmbios;
}
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
