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
// $Header: /Alaska/SOURCE/Modules/TCG/TpmClearOnRollBack/TpmClearOnRollback.c 1     5/23/13 7:49p Fredericko $
//
// $Revision: 1 $
//
// $Date: 5/23/13 7:49p $
//**********************************************************************
// Revision History
// ----------------
// $Log: /Alaska/SOURCE/Modules/TCG/TpmClearOnRollBack/TpmClearOnRollback.c $
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
// Name: TpmClearOnRollback
//
//
//
//---------------------------------------------------------------------------
//<AMI_FHDR_END>
#include "TpmClearOnRollback.h"
#include <Protocol/AMIPostMgr.h>
#include <Ppi/FwVersion.h>
#include <Hob.h>
#include <Token.h>
#include <Guid/HobList.h>
#include <AmiHobs.h>
#include<Library/TimerLib.h>
#include <AmiDxeLib.h>


VOID DrawMessageBox(
    IN CHAR16 *Caption,
    IN CHAR16 *Message
);


VOID * TcgGetEfiConfigurationTable(
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN EFI_GUID         *Guid
    )
{
    EFI_CONFIGURATION_TABLE *Table = SystemTable->ConfigurationTable;
    UINTN i = SystemTable->NumberOfTableEntries;

    for (;i;--i,++Table)
    {
        if (MemCmp(&Table->VendorGuid,Guid, sizeof(EFI_GUID))==0) return Table->VendorTable;
    }
    return 0;
}


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
// Procedure: RecoveryClearTpmBeforeFlash
//
// Description:
//  Process TPM clear on Rollback policy
//
// Input:
// VOID
//
// Output:
//  VOID
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>
VOID RecoveryClearTpmBeforeFlash (VOID)
{
    UINT8                       ClearResults;
    AMI_POST_MANAGER_PROTOCOL   *TpmClearAmiPostMgr = NULL;
    FW_VERSION                  Fid;
    EFI_EVENT                   MyEvent;
    FW_VERSION                  RecoveryFid={0};
    EFI_HOB_HANDOFF_INFO_TABLE  *TpmpHit;
    EFI_GUID                    TpmRecoveryHobGuid = AMI_RECOVERY_IMAGE_HOB_GUID;
    UINT32                      ProjectVersion, NewProjectVersion,ProjectVersionfloat, NewProjectVersionfloat;
    BOOLEAN                     Rollback=FALSE;
    EFI_STATUS                  Status;

    TpmpHit = GetEfiConfigurationTable(pST, &gEfiHobListGuid);
    if(TpmpHit != NULL && !EFI_ERROR(FindNextHobByGuid(&TpmRecoveryHobGuid, (void **)&TpmpHit)))
    {

        TpmGetFidFromBuffer(&RecoveryFid, (VOID *)(UINTN)((RECOVERY_IMAGE_HOB*)TpmpHit)->Address);
    }

    TpmRecoveryGetFidFromFv(&Fid);

    ProjectVersion = (Fid.ProjectMajorVersion[0] - '0') * 10 + (Fid.ProjectMajorVersion[1] - '0');
    ProjectVersion <<= 16;
    ProjectVersionfloat = (Fid.ProjectMinorVersion[0] - '0') * 10 + (Fid.ProjectMinorVersion[1] - '0');

    NewProjectVersion = (RecoveryFid.ProjectMajorVersion[0] - '0') * 10 + (RecoveryFid.ProjectMajorVersion[1] - '0');
    NewProjectVersion <<= 16;
    NewProjectVersionfloat = (RecoveryFid.ProjectMinorVersion[0] - '0') * 10 + (RecoveryFid.ProjectMinorVersion[1] - '0');
    
    if(NewProjectVersion < ProjectVersion){
        Rollback= TRUE;
    }
    
    if(NewProjectVersion == ProjectVersion){
        if(NewProjectVersionfloat < ProjectVersionfloat){
            Rollback=TRUE;
        }
    }

    if(Rollback == TRUE)
    {
        ClearResults = ClearTpmBeforeFlash();
        if(ClearResults == TPM_CLEAR_RESET_REQUIRED)
        {
            Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, (void **)&TpmClearAmiPostMgr);
            if(EFI_ERROR(Status))return;

            if(TpmClearAmiPostMgr != NULL)
            {
                TpmClearAmiPostMgr->DisplayInfoBox(L"TPM CLEAR",\
                                                   L"Caution: A Reset is required to Clear the TPM for Flash Update. Enable Recovery after reset",20, &MyEvent);

                MicroSecondDelay(1000000); //10seconds delay
            }

            pRS->ResetSystem( EfiResetCold, 0, 0, NULL );
        }
    }
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
