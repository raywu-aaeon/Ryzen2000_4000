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

/** @file AmiPspFtpm.h
    Ami Psp Ftpm definition

**/

#ifndef _AMI_PSP_FTPM_H_
#define _AMI_PSP_FTPM_H_

#ifdef __cplusplus
extern "C" {
#endif

//Definition for Ami Ftpm Flag
#define PSP_FTPM_FLAG_CLEAR 0x01ul

typedef struct {
	EFI_HOB_GUID_TYPE		EfiHobGuidType;
	UINT8					ClearPspNvram;
} AMI_PSP_FTPM_HOB;

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
