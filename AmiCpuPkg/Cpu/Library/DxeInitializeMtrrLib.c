//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file DxeInitializeMtrrLib.c
    This file is a NULL library

**/
#include <PiDxe.h>
#include <Register/Msr.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>

/**
    This is a NULL library in Dxe.

        
    @retval NULL

**/
VOID
EFIAPI
InitializeMtrr(
  VOID
  )
{
    return;
}
