//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************

/** @file Acoustic.h
    Acoustic header file

**/

#ifndef  _HDD_ACOUSTIC_H
#define  _HDD_ACOUSTIC_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------

#include <Token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Protocol/AcousticProtocol.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskInfo.h>
#include <IndustryStandard/AmiAtaAtapi.h>
#include "AcousticSetupVar.h"

//---------------------------------------------------------------------------

#if defined(IdeBusSrc_SUPPORT) && (IdeBusSrc_SUPPORT != 0)
#include <Protocol/AmiIdeBus.h>
#endif

#if defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0)
#include <Protocol/AmiAhciBus.h>
#endif

//
// Constant Defines
//
#define AUTOMATIC_ACOUSTIC_FEATURE_SET_SUPPORTED 0x0200

//
// Function defines
//
EFI_STATUS
EFIAPI
AcousticEntryPoint (
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable 
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif 

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
