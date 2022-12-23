//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file AcousticSetupVar.h
    Has Structure definition that is stored in NVRAM.
     
**/


#ifndef _ACOUSTIC_SETUP_VAR_H
#define _ACOUSTIC_SETUP_VAR_H
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------

#include <Token.h>

//---------------------------------------------------------------------------

#define HDD_ACOUSTIC_DEVICE_GUID\
        { 0x4b63986c, 0x20b3, 0x49c6, { 0x91, 0xa8, 0x8a, 0x1b, 0x96, 0x8d, 0x5a, 0xb3 } }

#define ACOUSTIC_VAR_NAME L"AcousticVarName"

#ifndef TYPEDEF_HDD_ACOUSTIC_DEVICE_DATA
#define TYPEDEF_HDD_ACOUSTIC_DEVICE_DATA
typedef struct {
    UINT8  AcousticPwrMgmt;
    UINT8  AcousticLevel;
    UINT8  AcousticLevelIndv[ACOUSTIC_DEVICE_COUNT];
    UINT8  ControllerPresent[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED];
    UINT8  AcousticModeFlag[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED];
    UINT8  BusNum[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED];
    UINT8  DevNum[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED];
    UINT8  FunNum[ACOUSTIC_MAXIMUM_CONTROLLER_SUPPORTED];
    UINT8  AcousticSupported[ACOUSTIC_DEVICE_COUNT];
    UINT8  AcousticDevicePresent[ACOUSTIC_DEVICE_COUNT];
    UINT8  VendorAcousticValue[ACOUSTIC_DEVICE_COUNT];
}HDD_ACOUSTIC_DEVICE_DATA;
#endif

#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
