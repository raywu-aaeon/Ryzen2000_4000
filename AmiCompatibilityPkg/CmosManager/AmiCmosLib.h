//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiCmosLib.h
    Contains the routines that constitute the CMOS access
    implementation.  This file contains source code that is used
    for both PEI and DXE phases.

**/


#ifndef _AMI_CMOS_LIB_H_
#define _AMI_CMOS_LIB_H_

#include <Uefi.h>
#include "CmosAccess.h"

EFI_STATUS ReadWriteCmosBank2 (
    IN EFI_PEI_SERVICES         **PeiServices,  // NULL in DXE phase
    IN CMOS_ACCESS_TYPE         AccessType,
    IN UINT16                   CmosRegister,
    IN OUT UINT8                *CmosParameterValue );

BOOLEAN SbGetRtcPowerStatus (
    IN EFI_PEI_SERVICES     **PeiServices );

#endif
