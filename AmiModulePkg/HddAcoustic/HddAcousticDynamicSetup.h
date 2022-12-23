//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file HddAcousticDynamicSetup.h
    Has Structure definition that is stored in NVRAM.
     
**/


#ifndef _ACOUSTIC_DYNAMIC_SETUP_VAR_H
#define _ACOUSTIC_DYNAMIC_SETUP_VAR_H
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------

#include <Token.h>

//---------------------------------------------------------------------------

#define HDD_ACOUSTIC_DYNAMIC_VARIABLE_ID 0xDDDE

#define ACOUSTIC_FORM_SET_CLASS          0xD0
#define ACOUSTIC_FORM_SET_GUID\
       { 0xC48AA1AC, 0xF870, 0x418D, { 0xA6, 0xEF, 0xC1, 0xDD, 0x89, 0xC1, 0xCE, 0x19 } }

#define ACOUSTIC_MAIN_FORM_ID            0x1
#define ACOUSTIC_SUB_FORM_ID             0x2

#define ACOUSTIC_MAIN_FORM_LABEL_START   0x1000
#define ACOUSTIC_MAIN_FORM_LABEL_END     0x1001
#define ACOUSTIC_SUB_FORM_LABEL_START    0x2000
#define ACOUSTIC_SUB_FORM_LABEL_END      0x2001

#define ACOUSTIC_CHECK_BOX_GLOBAL_KEY    0x10
#define ACOUSTIC_COMMON_ONEOF_GLOBAL_KEY 0x11

#define ACOUSTIC_CONTROLLER_BASE_KEY     0x200
#define ACOUSTIC_DEVICE_BASE_KEY         0x300

#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2015, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
