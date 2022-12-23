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

/** @file AmiCspFlashLib.h
  This file contains South Bridge(LPC) chipset porting library FLASH 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_CSP_FLASH_LIB_H__
#define __AMI_CSP_FLASH_LIB_H__

#include <Uefi.h>

#ifdef __cplusplus
extern "C" {
#endif

#if BIOS_LOCK_ENABLE
VOID BiosLockEnableSmiFlashHook (
    IN UINT8                        SwSmiNum,
    IN OUT UINT64                   Buffer
);
#endif

EFI_STATUS SbFlashProtectedRange (
    VOID
);

BOOLEAN IsTopSwapOn(
    VOID
);

VOID  SetTopSwap(
    IN BOOLEAN                      On
);

EFI_STATUS ReadSpiDescriptor (
    IN UINT8                SectionSelect,
    IN UINT8                SectionIndex,
    OUT UINT32              *SectionData
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
