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

/** @file NbDxeBoard.c
    This file contains DXE stage board component code for
    Template NB

**/

// Module specific Includes
#include "Efi.h"
#include "Pei.h"
#include "Token.h"
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "NbDxeBoard.h"
#include "Nb.h"
#include <CpuSetupData.h>
#include <Protocol/AmiMemInfo.h>


/**
    This function initializes the board specific component in
    in the chipset north bridge

          
    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

           
    @retval EFI_SUCCESS init success.

**/

EFI_STATUS EFIAPI NBDXE_BoardInit (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{

	return EFI_SUCCESS;
}

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
