//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiCmosManagerLib.h
    Contains the routines that constitute the CMOS access
    implementation.  This file contains source code that is used
    for both PEI and DXE phases.

**/


#ifndef _AMI_CMOS_MANAGER_LIB_H_
#define _AMI_CMOS_MANAGER_LIB_H_

#include <Efi.h>
#include <AmiLib.h>
#include <CmosAccess.h>
#include <SspTokens.h>

EFI_STATUS ReadWriteStandardRange (
    IN      EFI_PEI_SERVICES      **PeiServices,  // NULL in DXE phase
    IN      CMOS_ACCESS_TYPE      AccessType,
    IN      UINT16                CmosRegister,
    IN OUT  UINT8                 *CmosParameterValue );


//================================================================
//   Southbridge should implement functions to support access
//   to additional CMOS banks (add the following to SBCspLib.h)
//================================================================
/*
EFI_STATUS ReadWriteSecondBankTranslated (
    IN      EFI_PEI_SERVICES      **PeiServices,  // NULL in DXE phase
    IN      CMOS_ACCESS_TYPE      AccessType,
    IN      UINT16                CmosRegister,
    IN OUT  UINT8                 *CmosParameterValue );
*/

BOOLEAN CmosMgrBatteryIsGood (
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosMgrIsFirstBoot (
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosMgrIsBsp(
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosMgrIsColdBoot(
    IN  EFI_PEI_SERVICES        **PeiServices );

BOOLEAN CmosIsUsable(
    IN  EFI_PEI_SERVICES        **PeiServices );

#endif
