//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************

/** @file AcousticProtocol.h
    Header file that has protocol structure for Acoustic Module.

**/

#ifndef  _ACOUSITC_PROTOCOL_H   
#define  _ACOUSITC_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------

#include <AmiStorageFeatures.h>

//---------------------------------------------------------------------------

#define AMI_HDD_ACOUSTIC_INIT_PROTOCOL_GUID\
        { 0x10e9d800, 0x53b7, 0x4845, { 0x9d, 0xff, 0x30, 0xd1, 0x8a, 0x95, 0x6d, 0x53 } }

//  Equates used for Acoustic Flags
#define     ACOUSTIC_SUPPORT_DISABLE            0x00
#define     ACOUSTIC_SUPPORT_ENABLE             0x01
#define     ACOUSTIC_LEVEL_BYPASS               0xFF
#define     ACOUSTIC_LEVEL_MAXIMUM_PERFORMANCE  0xFE
#define     ACOUSTIC_LEVEL_QUIET                0x80

typedef 
EFI_STATUS 
(EFIAPI *AMI_HDD_ACOUSTIC_INIT_INSTALL) (
    IN VOID                       *BusInterface,
    IN AMI_STORAGE_BUS_INTERFACE  BusInterfaceType
);

typedef struct _AMI_HDD_ACOUSTIC_INIT_PROTOCOL {
    AMI_HDD_ACOUSTIC_INIT_INSTALL    InitHddAcoustic;
}AMI_HDD_ACOUSTIC_INIT_PROTOCOL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
