//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//**********************************************************************
/** @file SbSmmIoTrapDispatch2.h
    SMM IO Trap Dispatch2 Protocol Header.
    Before SMM-43 we use this header file to support IO Trap.
    For SMM-43 and later we use the original SMM IO Trap Dispatch2 Protocol
    in the SMM component.

**/
//**********************************************************************

#ifndef __SB_SMM_IO_TRAP_DISPATCH2_PROTOCOL_H__
#define __SB_SMM_IO_TRAP_DISPATCH2_PROTOCOL_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Efi.h>

// {58DC368D-7BFA-4E77-ABBC-0E29418DF930}
#define EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID \
  {0x58dc368d, 0x7bfa, 0x4e77, 0xab, 0xbc, 0x0e, 0x29, 0x41, 0x8d, 0xf9, 0x30}

GUID_VARIABLE_DECLARATION(gEfiSmmIoTrapDispatch2ProtocolGuid,EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL_GUID);

typedef struct _EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL  EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL;


//******************************************************
// EFI_SMM_IO_TRAP_DISPATCH2
//******************************************************
// I/O Trap valid types

typedef enum {
    WriteTrap = 0,
    ReadTrap,
    ReadWriteTrap,
    IoTrapTypeMaximum
} EFI_SMM_IOTRAP_DISPATCH_TYPE;

// I/O Trap context structure containing information about the I/O Trap
// event that should invoke the handler

typedef struct {
    UINT16                        Address;
    UINT16                        Length;
    EFI_SMM_IOTRAP_DISPATCH_TYPE  Type;
} EFI_SMM_IO_TRAP_REGISTER_CONTEXT;

// I/O Trap context structure containing information about the I/O Trap
// that occurred.

typedef struct {
    UINT32                        WriteData;
} EFI_SMM_IO_TRAP_CONTEXT;

typedef VOID (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2) (
    IN EFI_HANDLE                           DispatchHandle,
    IN EFI_SMM_IO_TRAP_CONTEXT              *Context
);

// For compatible Aptio SMM-43.
// Original SPEC (SMM CIS) version 0.9 doesn't have EFI_SMM_HANDLER_ENTRY_POINT2
//      and EFI_SMM_IO_TRAP_DISPATCH2_REGISTER.
// Whole DispatchFunction is two parameter function.
//
// After UEFI PI 1.0 (SMM CIS) version 1.2.
//      Whole DispatchFunction is four parameter function. (EFI_SMM_HANDLER_ENTRY_POINT2)
#ifndef EFI_SMM_HANDLER_ENTRY_POINT2
#define EFI_SMM_HANDLER_ENTRY_POINT2 EFI_SMM_IO_TRAP_DISPATCH2
#endif

typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2_REGISTER) (
    IN EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN EFI_SMM_IO_TRAP_DISPATCH2            DispatchFunction,
    IN OUT EFI_SMM_IO_TRAP_REGISTER_CONTEXT *DispatchContext,
    OUT EFI_HANDLE                          *DispatchHandle
);

typedef EFI_STATUS (EFIAPI *EFI_SMM_IO_TRAP_DISPATCH2_UNREGISTER) (
    IN EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL   *This,
    IN EFI_HANDLE                           DispatchHandle
);

struct _EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL {
    EFI_SMM_IO_TRAP_DISPATCH2_REGISTER      Register;
    EFI_SMM_IO_TRAP_DISPATCH2_UNREGISTER    UnRegister;
};

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
