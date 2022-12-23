/**

Copyright (c) 2012, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Base.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/RngLib.h>

UINTN __security_cookie = 0xAB;

//
// Below data structure is from vcruntime.h and gs_report.c (Microsoft Visual Studio)
//

__declspec(noreturn) void __cdecl __report_gsfailure(void)
{
  DEBUG ((DEBUG_ERROR, "STACK FAULT: Buffer Overflow in function %p.\n", _ReturnAddress()));
  CpuDeadLoop ();
}

__declspec(noreturn) void __cdecl __report_rangecheckfailure(void)
{
  DEBUG ((DEBUG_ERROR, "STACK FAULT: Buffer Overflow in function %p.\n", _ReturnAddress()));
  CpuDeadLoop ();
}

__declspec(noreturn) void __GSHandlerCheck(void)
{
  CpuDeadLoop ();
}

RETURN_STATUS EFIAPI StackCheckLibConstructor(
        VOID
        )
{
    UINT64 tmp;
    GetRandomNumber64(&tmp);
    __security_cookie = (UINTN)tmp;
    return RETURN_SUCCESS;
}

