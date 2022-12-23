//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmiCmosLibNull.c
    Contains routines that are board-specific.

**/

#include <AmiCmosLib.h>

EFI_STATUS ReadWriteCmosBank2 (
    IN EFI_PEI_SERVICES         **PeiServices,  // NULL in DXE phase
    IN CMOS_ACCESS_TYPE         AccessType,
    IN UINT16                   CmosRegister,
    IN OUT UINT8                *CmosParameterValue )
{
    return EFI_SUCCESS;
}


BOOLEAN SbGetRtcPowerStatus (
    IN EFI_PEI_SERVICES     **PeiServices )
{
    return TRUE;
} 
