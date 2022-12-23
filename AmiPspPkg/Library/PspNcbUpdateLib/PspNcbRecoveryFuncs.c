//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

//*************************************************************************
/** @file PspNcbRecoveryFuncs.c

**/
//*************************************************************************
#include <AmiDxeLib.h>
//#include <Token.h>
#include <Protocol/SmiFlash.h>
#include <Protocol/AmiPostMgr.h>
#include <Protocol/FlashProtocol.h>
#include <Library/PspNcbUpdate.h>
#include <Capsule.h>
#include <AmiHobs.h>
#include <Library/DebugLib.h>

extern FLASH_PROTOCOL *Flash;
extern UINT8 *RecoveryBuffer;

#define PSP_FLASH_ADDR_TRANSFER(addr)   (addr - (0xFFFFFFFF - FLASH_SIZE + 1))

#define ROMSIG_BASE                     (0xFFFFFFFF - FLASH_SIZE + FCH_FIRMWARE_OFFSET + 1)

PSP_UPDATE_BLOCK_TABLE_STRUCT PspUpdateBlockTable[] =
{
		// { Start address, End address , Block offset}
#if (PROTECT_PSP_FIXED_AREA_FROM_BEING_ERASED == 1)
        { PSP_FIRST_UPDATABLE_BLOCK_ADDRESS , PSP_BLOCK_START_ADDRESS + TOTAL_PSP_DATA_SIZE  , PSP_FIRST_UPDATABLE_BLOCK_OFFSET }
#else
		{ ROMSIG_BASE, ROMSIG_BASE + ROMSIG_SIZE, FCH_FIRMWARE_OFFSET},
		{ PSP_BLOCK_START_ADDRESS + TOTAL_PSP_NVRAM_SIZE, PSP_BLOCK_START_ADDRESS + TOTAL_PSP_DATA_SIZE, PSP_BLOCK_START_OFFSET+TOTAL_PSP_NVRAM_SIZE }
#endif
};

/**
    This elink is to provide a call for updating Psp block table.

    @param VOID

    @retval VOID

**/

VOID
UpdateBlockTableForPsp(
    VOID
)
{
    UINTN                       i, j;
    EFI_STATUS                  Status;
    VOID                        *DisplayHandle;
    AMI_POST_MGR_KEY            OutKey;
    AMI_POST_MANAGER_PROTOCOL   *AmiPostMgr = NULL;
    UINT32                      UpdateBlockAddr = 0, k = 0;
    UINT32                      StartBlock, EndBlock;
    UINT8                       PspUpdatBlockTblEntries;
    EFI_GUID                    ImageCapsuleGuid = W8_SCREEN_IMAGE_CAPSULE_GUID;
    EFI_GUID                    GuidHob = HOB_LIST_GUID;
    EFI_HOB_UEFI_CAPSULE        *Hob;
    EFI_CAPSULE_HEADER          *Capsule;
    EFI_TPL                     OldTpl;
    UINT8                       *Source;

    PspUpdatBlockTblEntries = sizeof (PspUpdateBlockTable) /
     sizeof (PSP_UPDATE_BLOCK_TABLE_STRUCT);

    // No NCB need to be updated.
    if (!PspUpdatBlockTblEntries)
        return;

    // Verify if we're on OS firmware update path
    Hob = GetEfiConfigurationTable (pST, &GuidHob);
    
    if (Hob != NULL)
    {
        do
        {
            Status = FindNextHobByType (EFI_HOB_TYPE_UEFI_CAPSULE, &Hob);
            if (!EFI_ERROR (Status))
            { 
                Capsule = (EFI_CAPSULE_HEADER *)(VOID *)(UINTN)Hob->BaseAddress;
                if (!guidcmp (&(Capsule->CapsuleGuid), &ImageCapsuleGuid))
                    break;
            }
        } while(!EFI_ERROR (Status));
  
       if (EFI_ERROR(Status))
       {    // no image hob - we're not on OS FW update path
            Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, &AmiPostMgr);
            if (EFI_ERROR (Status))
                AmiPostMgr = NULL;
       }
    }

    if (AmiPostMgr)
        AmiPostMgr->DisplayProgress (AMI_PROGRESS_BOX_INIT, L"PSP NCB Update Progress",
                     NULL, NULL, 0, &DisplayHandle, &OutKey);

    for (i = 0; i < PspUpdatBlockTblEntries; i++)
    {
        StartBlock = PSP_FLASH_ADDR_TRANSFER (PspUpdateBlockTable[i].StartAddress) /
                      FLASH_BLOCK_SIZE;
        EndBlock = PSP_FLASH_ADDR_TRANSFER (PspUpdateBlockTable[i].EndAddress) /
                      FLASH_BLOCK_SIZE;

        DEBUG((DEBUG_INFO, "Table%d, StartBlock: %08X, EndBlock: %08X\n",
         i , PspUpdateBlockTable[i].StartAddress, PspUpdateBlockTable[i].EndAddress));

        // Update NCBs
        for (j = StartBlock, k = 0; j < EndBlock; j++, k++)
        {
            UpdateBlockAddr = PspUpdateBlockTable[i].StartAddress + (k * FLASH_BLOCK_SIZE);
            DEBUG((DEBUG_INFO, "UpdateBlockAddr: %08X\n", UpdateBlockAddr));

            Source = RecoveryBuffer + PspUpdateBlockTable[i].BlockOffset + (k * FLASH_BLOCK_SIZE);
            DEBUG((DEBUG_INFO, "Source: %08X\n", Source));

            if (AmiPostMgr)
            {
                AmiPostMgr->DisplayProgress (AMI_PROGRESS_BOX_UPDATE, L"PSP NCB Update Progress",
                             NULL, NULL, ((j-StartBlock)+1)*100/(EndBlock-StartBlock),
                             &DisplayHandle, &OutKey);
            }

            OldTpl = pBS->RaiseTPL (TPL_HIGH_LEVEL);
            Status = Flash->Update ((UINT8*)UpdateBlockAddr, FLASH_BLOCK_SIZE, Source);
            pBS->RestoreTPL (OldTpl);
            DEBUG((DEBUG_INFO, "PSP Flash->Update Status: %08x\n", Status));
        }
    }
    if (AmiPostMgr)
        AmiPostMgr->DisplayProgress (AMI_PROGRESS_BOX_CLOSE, L"PSP NCB Update Progress",
                     NULL, NULL, 0, &DisplayHandle, &OutKey);
}

#include <AmiModulePkg/Recovery/ReFlash/ReFlash.h>

/**
    This elink is to provide a call for updating Psp block table.

    @param VOID

    @retval VOID

**/

VOID
PspRecoveryInsertOemTableBeforeFlash (
    VOID
)
{
	UINT32 i;
	//
    // Fix BitLocker issue for new Recovery module.
	//
    for (i = 0; BlocksToUpdate[i].Type != FvTypeMax; i++) {
        if ((UINTN)(BlocksToUpdate[i].BlockAddress) == PSP_BLOCK_START_ADDRESS){
            BlocksToUpdate[i].Update = FALSE;   // This will keep whole PSP area from being updated by kernel
        }
    }

    // Update PSP area by AmiPspPkg
    UpdateBlockTableForPsp();
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
