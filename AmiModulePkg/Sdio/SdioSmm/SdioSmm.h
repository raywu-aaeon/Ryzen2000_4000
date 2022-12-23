//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file SdioSmm.h
    Header file for the SdioSmm

**/

#ifndef _EFI_SDIO_SMM_DRIVER_H_
#define _EFI_SDIO_SMM_DRIVER_H_

//----------------------------------------------------------------------


#include <Token.h>
#include <Protocol/LegacyBios.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include "SdioDef.h"

#define RETURN(status) {return status;}

//----------------------------------------------------------------------

//-----------------------------------------------
//      ERROR CODE REPORTED TO CALLER
//-----------------------------------------------
#define SDIO_WRITE_PROTECT_ERR          0x003   // Write protect error
#define SDIO_TIME_OUT_ERR               0x080   // Command timed out error
#define SDIO_DRIVE_NOT_READY_ERR        0x0AA   // Drive not ready error
#define SDIO_DATA_CORRECTED_ERR         0x011   // Data corrected error
#define SDIO_PARAMETER_FAILED           0x007   // Bad parameter error
#define SDIO_MARK_NOT_FOUND_ERR         0x002   // Address mark not found error
#define SDIO_NO_MEDIA_ERR               0x031   // No media in drive
#define SDIO_READ_ERR                   0x004   // Read error
#define SDIO_UNCORRECTABLE_ERR          0x010   // Uncorrectable data error
#define SDIO_BAD_SECTOR_ERR             0x00A   // Bad sector error
#define SDIO_GENERAL_FAILURE            0x020   // Controller general failure

#define MAX_NUMBLOCK_16BIT              0xFFFF


EFI_STATUS
EFIAPI
SdioSwSmiHandler (
    EFI_HANDLE      DispatchHandle,
    IN  CONST VOID  *DispatchContext OPTIONAL,
    IN  OUT VOID    *CommBuffer      OPTIONAL,
    IN  OUT UINTN   *CommBufferSize  OPTIONAL
);

EFI_STATUS
EFIAPI
InstallSwSmiHandlerForLegacy (
    IN CONST EFI_GUID  *Protocol,
    IN VOID            *Interface,
    IN EFI_HANDLE      Handle
);

VOID
SdMmcAPIRead (
    SDIO_STRUC  *SdioURP
);

VOID
SdMmcAPIWrite (
    SDIO_STRUC  *SdioURP
);

UINT8
GetDevEntry (
    IN  UINT8  DeviceAddress
);

VOID
SdMmcApiReset (
    SDIO_STRUC  *SdioURP
);

VOID
SdMmcApiDeviceGeometry (
    SDIO_STRUC  *SdioURP
);

VOID
SdMmcNotSupported (
    SDIO_STRUC  *SdioURP
);

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093     **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
