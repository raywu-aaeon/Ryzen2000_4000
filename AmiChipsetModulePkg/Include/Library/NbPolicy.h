//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file NbPolicy.h
    North Bridge setup data header file, define all the North
    Bridge setup items and a structures in this file. 


**/

#ifndef _AMI_NB_SETUP_POLICY_H // To Avoid this header get compiled twice
#define _AMI_NB_SETUP_POLICY_H

#include <Setup.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

typedef struct _NB_SETUP_DATA  NB_SETUP_DATA;

typedef struct _NB_SETUP_DATA {
    // NB Setup header
    UINT32  NbPolicyVersion;

    UINT8   MemClk;
    UINT8   EnableBankIntlv;
    UINT8   EnableChannelIntlv;
    UINT8   MemClr;
    UINT8   MemClrFlag;

} NB_SETUP_DATA;

#pragma pack(pop)

typedef VOID (NB_OEM_SETUP_CALLBACK) (
    IN VOID                 *Services,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
);


VOID GetNbSetupData (
    IN VOID                 *Service,
    IN OUT NB_SETUP_DATA    *NbSetupData,
    IN BOOLEAN              Pei
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
