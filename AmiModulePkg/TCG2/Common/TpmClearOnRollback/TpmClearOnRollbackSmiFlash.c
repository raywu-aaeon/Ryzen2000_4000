//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2011, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
//**********************************************************************
// $Header: /Alaska/SOURCE/Modules/TCG/TpmClearOnRollBack/TpmClearOnRollbackSmiFlash.c 1     5/23/13 7:49p Fredericko $
//
// $Revision: 1 $
//
// $Date: 5/23/13 7:49p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG/TpmClearOnRollBack/TpmClearOnRollbackSmiFlash.c $
//
// 1     5/23/13 7:49p Fredericko
// [TAG]        EIP121823
// [Category]   New Feature
// [Description]    Clear TPM on BIOS rollback
// [Files]          TpmClearOnRollback.cif
// TpmClearOnRollback.c
// TpmClearOnRollback.h
// TpmClearOnRollback.sdl
// TpmClearOnRollback.mak
// TpmClearOnRollback.dxs
// TpmClearOnRollbackSmiFlash.c
// TpmClearOnRollbackWrapperLib.c
// TpmClearOnRollbackWrapperLib.h
//**********************************************************************
//<AMI_FHDR_START>
//---------------------------------------------------------------------------
// Name:
//
//
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include <AmiDxeLib.h>
#include "TpmClearOnRollback.h"
#include <Protocol/AMIPostMgr.h>
#include <Protocol/SmmVariable.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>


CLEAR_TPM_ROLLBACK_PROTOCOL *PrivateProtocol;
EFI_SMM_SYSTEM_TABLE2               *mSmst;
static FW_VERSION                          Fid;

extern EFI_GUID gAmiTpmRollbackSmmProtocolGuid;

UINT8 SmiFlashClearTpmBeforeFlash (void)
{
    return(ClearTpmBeforeFlash());
}


//****************************************************** ****************
//<AMI_PHDR_START>
//
// Procedure:    TpmClearRollBackSmmInit
//
// Description: Entry point for subcomponent
//
// Input:       IN    EFI_HANDLE ImageHandle,
//              IN    EFI_SYSTEM_TABLE *SystemTable
//
// Output: EFI_STATUS
//
// Modified:
//
// Referrals:
//
// Notes:
//
//<AMI_PHDR_END>
//**********************************************************************
EFI_STATUS
EFIAPI
TpmClearRollBackSmmInit(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable )
{
    EFI_HANDLE                    Handle=NULL;
    EFI_STATUS                    Status;
    UINT8 (*ClearTpmBeforeFlashFuncPtr)(void);
       
    InitAmiLib(ImageHandle, SystemTable);
    
    ClearTpmBeforeFlashFuncPtr = &SmiFlashClearTpmBeforeFlash;

    Status = gSmst->SmmAllocatePool (
                 EfiRuntimeServicesData,
                 sizeof (CLEAR_TPM_ON_ROLLBACK),
                 (void **)&PrivateProtocol
             );
   
    if((EFI_ERROR(Status)) || (PrivateProtocol == NULL))
    {
        return Status;
    }

    TpmRecoveryGetFidFromFv(&Fid);

    PrivateProtocol->ClearTpmOnRollBack = ClearTpmBeforeFlashFuncPtr; 

    Status = gSmst->SmmInstallProtocolInterface( &Handle, \
             &gAmiTpmRollbackSmmProtocolGuid, \
             EFI_NATIVE_INTERFACE, \
             PrivateProtocol );

    return Status;
}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2010, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
