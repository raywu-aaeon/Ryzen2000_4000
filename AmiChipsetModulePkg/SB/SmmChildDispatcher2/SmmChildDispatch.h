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
/** @file SmmChildDispatch.h
    SMM Child dispatcher functions and data structures definition

**/
//**********************************************************************
#ifndef __SMM_CHILD_DISPATCH__H__
#define __SMM_CHILD_DISPATCH__H__
#ifdef __cplusplus
extern "C" {
#endif

#include <AmiDxeLib.h>
#include <Protocol/SmmSwDispatch.h>
#include <Protocol/SmmSxDispatch.h>
#include <Protocol/SmmPeriodicTimerDispatch.h>
#include <Protocol/SmmUsbDispatch.h>
#include <Protocol/SmmGpiDispatch.h>
#include <Protocol/SmmStandbyButtonDispatch.h>
#include <Protocol/SmmPowerButtonDispatch.h>


#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmUsbDispatch2.h>
#include <Protocol/SmmGpiDispatch2.h>
#include <Protocol/SmmStandbyButtonDispatch2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Protocol/SmmIoTrapDispatch2.h>

#define SMM_COMMON_ORDER      0x80

typedef VOID ( *SMI_GENERIC_CALLBACK ) (
  IN EFI_HANDLE  DispatchHandle,
  IN CONST VOID  *Context         OPTIONAL,
  IN OUT VOID    *CommBuffer      OPTIONAL,
  IN OUT UINTN   *CommBufferSize  OPTIONAL
);

typedef struct {
    DLINK                   Link;
    UINT32                  Signature;
    SMI_GENERIC_CALLBACK    Callback;
    UINT8                   Context[1];
} HANDLER_LINK;

typedef struct {
    DLINK                               Link;
    EFI_SMM_HANDLER_ENTRY_POINT2        OrgCallback;
    UINTN                               SwSmiInputValue;
} SW_CALLBACKS_LINK;

#define _CR(Record, TYPE, Field)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))

#define SB_CR(record, TYPE, field, signature) _CR(record, TYPE, field)

#define GET_FCH_SMM_SW_NODE_FROM_HANDLE(_record) SB_CR(_record, FCH_SMM_SW_NODE, DispatchHandle,signature)

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
