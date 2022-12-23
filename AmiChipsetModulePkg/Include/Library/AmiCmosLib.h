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
  This file contains South Bridge(LPC) chipset porting library CMOS 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_CMOS_LIB_H__
#define __AMI_CMOS_LIB_H__

#include <PiPei.h>
#include <Uefi.h>
#include "Token.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef BOOLEAN (SB_RTC_PWR_VALID_CALLBACK) (
    VOID
);

UINT8 ReadCmos(
    IN UINT8 Index
);

VOID WriteCmos(
    IN UINT8 Index, 
    IN UINT8 Value
);

//---------------------------------------------------------------------------
//  CMOS Manager Support
//
//  South bridge should implement functions to support access to additional 
//  CMOS banks that exist beyond the first 128 bytes.
//---------------------------------------------------------------------------

#if CMOS_MANAGER_SUPPORT
#include <CmosAccess.h>

EFI_STATUS ReadWriteCmosBank2 (
    IN EFI_PEI_SERVICES             **PeiServices,  // NULL in DXE phase
    IN CMOS_ACCESS_TYPE             AccessType,
    IN UINT16                       CmosRegister,
    IN OUT UINT8                    *CmosParameterValue
);

BOOLEAN SbGetRtcPowerStatus (
    IN EFI_PEI_SERVICES             **PeiServices  // NULL in DXE phase
);

#endif  // #if CMOS_MANAGER_SUPPORT


BOOLEAN SbCheckNmiStatus (
    VOID
);

BOOLEAN SbEnableDisableNmi (
    IN BOOLEAN      Enable
);

VOID SbSaveRestoreNmi (
    IN BOOLEAN      Save
);

BOOLEAN SbIsRtcPwrValid (
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
