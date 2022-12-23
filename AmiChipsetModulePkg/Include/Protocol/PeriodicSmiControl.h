//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file PeriodicSmiControl.h
    The header file for Periodic Smi Control Protocol in SMM.

*/

#ifndef __SMM_PERIODICE_SMI_CONTROL_H__
#define __SMM_PERIODICE_SMI_CONTROL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Uefi.h>


#define AMI_PERIODICE_SMI_CONTROL_PROTOCOL_GUID \
  { \
  0x801e9def, 0xddbb, 0x4ca3, { 0x96, 0x98, 0xc9, 0x15, 0x8e, 0xb8, 0x6a, 0xea } \
  }

extern EFI_GUID gAmiPeriodicSmiControlProtocolGuid;

typedef struct _AMI_PERIODICE_SMI_CONTROL_PROTOCOL \
                                            AMI_PERIODICE_SMI_CONTROL_PROTOCOL;

//******************************************************
// AMI_PERIODICE_SMI_CONTROL
//******************************************************
typedef EFI_STATUS (EFIAPI *AMI_PERIODICE_SMI_CONTROL) (
    IN BOOLEAN                              Enable,
    IN EFI_HANDLE                           DispatchHandle
);


struct _AMI_PERIODICE_SMI_CONTROL_PROTOCOL {
    AMI_PERIODICE_SMI_CONTROL               Control;
};


/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
