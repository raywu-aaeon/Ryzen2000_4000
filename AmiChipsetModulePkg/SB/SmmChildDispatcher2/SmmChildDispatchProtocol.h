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
/** @file SmmChildDispatchProtocol.h
    SMM Child dispatcher protocols functions definition

**/
//**********************************************************************
#ifndef __SMM_CHILD_DISPATCH_PROTOCOL__H__
#define __SMM_CHILD_DISPATCH_PROTOCOL__H__
#ifdef __cplusplus
extern "C" {
#endif

#if BACKWARD_COMPATIBLE_MODE

#include <Protocol/SmmSwDispatch.h>
#include <Protocol/SmmSxDispatch.h>
#include <Protocol/SmmPeriodicTimerDispatch.h>
#include <Protocol/SmmUsbDispatch.h>
#include <Protocol/SmmGpiDispatch.h>
#include <Protocol/SmmStandbyButtonDispatch.h>
#include <Protocol/SmmPowerButtonDispatch.h>
#include <Protocol/SmmUsbDispatch.h>
#endif


#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmUsbDispatch2.h>
#include <Protocol/SmmGpiDispatch2.h>
#include <Protocol/SmmStandbyButtonDispatch2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>

#include <Protocol/SmmIoTrapDispatch2.h>

#include <Protocol/FchSmmSwDispatch2.h>
#include <Protocol/FchSmmIoTrapDispatch2.h>
#include <Protocol/FchSmmUsbDispatch2.h>
#include <Protocol/FchSmmSxDispatch2.h>
#include <Protocol/FchSmmGpiDispatch2.h>
#include <Protocol/FchSmmPwrBtnDispatch2.h>
#include <Protocol/FchSmmPeriodicalDispatch2.h>

///#include "FchInterfaceProtocol.h"

//******************** Sw SMI protocol functions *********************************

#if BACKWARD_COMPATIBLE_MODE
EFI_STATUS EfiSmmSwRegister (
    IN EFI_SMM_SW_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_SW_DISPATCH          Function,
    IN EFI_SMM_SW_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                  *Handle
    );

EFI_STATUS EfiSmmSwUnregister(
    IN EFI_SMM_SW_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                   Handle
    );

//******************** Sx SMI protocol functions *********************************

EFI_STATUS EfiSmmSxRegister(
    IN EFI_SMM_SX_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_SX_DISPATCH          Function,
    IN EFI_SMM_SX_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                  *Handle
    );

EFI_STATUS EfiSmmSxUnregister(
    IN EFI_SMM_SX_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                   Handle
    );

//******************** Periodic timer SMI protocol functions *********************

EFI_STATUS EfiSmmTimerRegister(
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH          Function,
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                              *Handle
    );

EFI_STATUS EfiSmmTimerUnregister(
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle
    );

EFI_STATUS EfiSmmTimerGetNextShorterInterval(
    IN EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL *This,
    IN OUT UINT64                               **SmiTickInterval
);

//******************** Usb SMI protocol functions ********************************

EFI_STATUS EfiSmmUsbRegister(
    IN EFI_SMM_USB_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_USB_DISPATCH             Function,
    IN EFI_SMM_USB_DISPATCH_CONTEXT     *Context,
    OUT EFI_HANDLE                      *Handle
);

EFI_STATUS EfiSmmUsbUnregister(
    IN EFI_SMM_USB_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                       Handle
);

//******************** Gpi SMI protocol functions ********************************

#define SUPPORTED_GPIS  0xffff

EFI_STATUS EfiSmmGpiRegister (
    IN EFI_SMM_GPI_DISPATCH_PROTOCOL    *This,
    IN EFI_SMM_GPI_DISPATCH             Function,
    IN EFI_SMM_GPI_DISPATCH_CONTEXT     *Context,
    OUT EFI_HANDLE                      *Handle
);

EFI_STATUS EfiSmmGpiUnregister(
    IN EFI_SMM_GPI_DISPATCH_PROTOCOL    *This,
    IN EFI_HANDLE                       Handle
);

//******************** Standby button SMI protocol functions *********************

EFI_STATUS EfiSmmSButtonRegister (
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL *This,
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH          Function,
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_CONTEXT  *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmSButtonUnregister (
    IN EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL *This,
    IN EFI_HANDLE                               Handle
);

//******************** Power button SMI protocol functions *********************

EFI_STATUS EfiSmmPButtonRegister(
    IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   *This,
    IN EFI_SMM_POWER_BUTTON_DISPATCH            Function,
    IN EFI_SMM_POWER_BUTTON_DISPATCH_CONTEXT    *Context,
    OUT EFI_HANDLE                              *Handle
);

EFI_STATUS EfiSmmPButtonUnregister(
    IN EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL   *This,
    IN EFI_HANDLE                               Handle
);
#endif
/******************** SB IO trap SMI protocol functions *********************/
EFI_STATUS EfiSmmIoTrapRegister2 (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2       Function,
    IN OUT   EFI_SMM_IO_TRAP_REGISTER_CONTEXT   *Context,
    OUT      EFI_HANDLE                         Handle
  );

EFI_STATUS EfiSmmIoTrapUnregister2 (
    IN CONST EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL *This,
    IN       EFI_HANDLE                         Handle
  );


EFI_STATUS
EfiSmmSwRegister2 (
    IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL  *This,
  IN        EFI_SMM_HANDLER_ENTRY_POINT2   DispatchFunction,
  IN  OUT   EFI_SMM_SW_REGISTER_CONTEXT    *RegisterContext,
  OUT       EFI_HANDLE                     *DispatchHandle
  );

EFI_STATUS
EfiSmmSwUnregister2 (
    IN CONST EFI_SMM_SW_DISPATCH2_PROTOCOL       *This,
  IN       EFI_HANDLE                     DispatchHandle
  );

EFI_STATUS EfiSmmSxRegister2 (
    IN CONST EFI_SMM_SX_DISPATCH2_PROTOCOL  *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2   Function,
    IN CONST EFI_SMM_SX_REGISTER_CONTEXT    *Context,
    OUT      EFI_HANDLE                     *Handle
  );

EFI_STATUS EfiSmmSxUnregister2 (
    IN CONST EFI_SMM_SX_DISPATCH2_PROTOCOL    *This,
    IN       EFI_HANDLE                       Handle
  );

EFI_STATUS EfiSmmTimerRegister2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL    *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2                 Function,
    IN CONST EFI_SMM_PERIODIC_TIMER_REGISTER_CONTEXT      *Context,
    OUT      EFI_HANDLE                                   *Handle
  );

EFI_STATUS EfiSmmTimerUnregister2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                                 Handle
  );

EFI_STATUS EfiSmmTimerGetNextShorterInterval2 (
    IN CONST EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL *This,
    IN OUT   UINT64                                    **SmiTickInterval
  );

EFI_STATUS EfiSmmUsbRegister2 (
    IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL   *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2     Function,
    IN CONST EFI_SMM_USB_REGISTER_CONTEXT     *Context,
    OUT      EFI_HANDLE                       *Handle
  );

EFI_STATUS EfiSmmUsbUnregister2(
    IN CONST EFI_SMM_USB_DISPATCH2_PROTOCOL   *This,
    IN       EFI_HANDLE                       Handle
  );

EFI_STATUS EfiSmmGpiRegister2 (
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL   *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2     Function,
    IN CONST EFI_SMM_GPI_REGISTER_CONTEXT     *Context,
    OUT      EFI_HANDLE                       *Handle
  );

EFI_STATUS EfiSmmGpiUnregister2 (
    IN CONST EFI_SMM_GPI_DISPATCH2_PROTOCOL   *This,
    IN       EFI_HANDLE                       Handle
  );

EFI_STATUS EfiSmmSButtonRegister2 (
    IN CONST EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL    *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2                 Function,
    IN CONST EFI_SMM_STANDBY_BUTTON_REGISTER_CONTEXT      *Context,
    OUT      EFI_HANDLE                                   *Handle
  );

EFI_STATUS EfiSmmSButtonUnregister2 (
    IN CONST EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL    *This,
    IN       EFI_HANDLE                                   Handle
  );

EFI_STATUS EfiSmmPButtonRegister2 (
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL  *This,
    IN       EFI_SMM_HANDLER_ENTRY_POINT2             Function,
    IN CONST EFI_SMM_POWER_BUTTON_REGISTER_CONTEXT    *Context,
    OUT      EFI_HANDLE                               *Handle
  );

EFI_STATUS EfiSmmPButtonUnregister2 (
    IN CONST EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL  *This,
    IN       EFI_HANDLE                               Handle
  );



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
