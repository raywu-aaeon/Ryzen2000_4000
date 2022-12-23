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

/** @file SmmBiosWriteDispatch.h
    SMM BIOS Write Dispatch Protocol header.

*/

#ifndef __SMM_BIOS_WRITE_DISPATCH_PROTOCOL_H__
#define __SMM_BIOS_WRITE_DISPATCH_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Uefi.h>

// {E512DFE4-BF44-480d-9B7A-777B0BE32775}
#define EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL_GUID \
  {0xe512dfe4, 0xbf44, 0x480d, 0x9b, 0x7a, 0x77, 0x7b, 0xb, 0xe3, 0x27, 0x75}


typedef struct _EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL \
                                        EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL;

//******************************************************
// EFI_SMM_BIOS_WRITE_DISPATCH
//******************************************************
typedef VOID (EFIAPI *EFI_SMM_BIOS_WRITE_DISPATCH) (
  IN EFI_HANDLE                           DispatchHandle,
	IN VOID                                 *DispatchContext
);


typedef EFI_STATUS (EFIAPI *EFI_SMM_BIOS_WRITE_REGISTER) (
  IN EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL *This,
  IN EFI_SMM_BIOS_WRITE_DISPATCH          DispatchFunction,
  OUT EFI_HANDLE                          *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_BIOS_WRITE_UNREGISTER) (
  IN EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL *This,
  IN EFI_HANDLE                           DispatchHandle
);


struct _EFI_SMM_BIOS_WRITE_DISPATCH_PROTOCOL {
    EFI_SMM_BIOS_WRITE_REGISTER             Register;
    EFI_SMM_BIOS_WRITE_UNREGISTER           UnRegister;
};

extern EFI_GUID gEfiSmmBiosWriteDispatchProtocolGuid;

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
