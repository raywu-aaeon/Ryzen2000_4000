//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//*************************************************************************
/** @file SbFchNcbUpdateLib.c

**/
//*************************************************************************
#include <AmiDxeLib.h>
#include <Token.h>
#include <Protocol/SmiFlash.h>
#include <Protocol/AMIPostMgr.h>
#include <Protocol/FlashProtocol.h>
#include <Library/SbFchNcbUpdateLib.h>
#include <Capsule.h>

#include <Library/DebugLib.h>

extern FLASH_PROTOCOL *Flash;
extern UINT8 *RecoveryBuffer;
extern VOID  *mHobList;

#define FCH_FLASH_ADDR_TRANSFER(addr)   (addr - (0xFFFFFFFF - FLASH_SIZE + 1))

FCH_UPDATE_BLOCK_TABLE_STRUCT gFchUpdateBlockTable[] =
{
		// { Start address, End address }
#if !defined(AmiPspPkg_SUPPORT) || (AmiPspPkg_SUPPORT == 0)
		{ ROMSIG_BASE, ROMSIG_BASE + ROMSIG_SIZE, ROMSIG_OFFSET},
#endif
#if defined(XHCI_FIRWARE_SIZE) && (XHCI_FIRWARE_SIZE != 0)
		{ XHCI_FIRMWARE_BASE, XHCI_FIRMWARE_BASE + XHCI_FIRWARE_SIZE, XHCI_FIRMWARE_OFFSET},
#endif
		{0, 0, 0}
};

VOID FchUpdateBlockTable()
{
    UINTN                       i, j;
    EFI_STATUS                  Status;
    VOID                        *DisplayHandle;
    AMI_POST_MGR_KEY            OutKey;
    AMI_POST_MANAGER_PROTOCOL   *AmiPostMgr = NULL;
    UINT32                      UpdateBlockAddr, k;
    UINT32                      StartBlock, EndBlock;
    UINT8                       FchUpdatBlockTblEntries;
    EFI_GUID                    ImageCapsuleGuid = W8_SCREEN_IMAGE_CAPSULE_GUID;
    EFI_HOB_UEFI_CAPSULE        *Hob;
    EFI_CAPSULE_HEADER          *Capsule;
    EFI_TPL                     OldTpl;
    UINT8                       *Source;

    FchUpdatBlockTblEntries =
            sizeof(gFchUpdateBlockTable) / sizeof(FCH_UPDATE_BLOCK_TABLE_STRUCT);

    // No NCB need to be updated.
    if (!FchUpdatBlockTblEntries)
        return;

    //Verify if we're on OS firmware update path
 	Hob = mHobList;
    
    if (Hob != NULL) {
        do {
            Status = FindNextHobByType(EFI_HOB_TYPE_UEFI_CAPSULE, &Hob);
            if (!EFI_ERROR(Status)) { 
                Capsule = (EFI_CAPSULE_HEADER *)(VOID *)(UINTN)Hob->BaseAddress;
                if (!guidcmp(&(Capsule->CapsuleGuid), &ImageCapsuleGuid))
                    break;
            }
          } while(!EFI_ERROR(Status));
  
       if (EFI_ERROR(Status)) {   //no image hob - we're not on OS FW update path
          Status = pBS->LocateProtocol(&gAmiPostManagerProtocolGuid, NULL, &AmiPostMgr);
          if (EFI_ERROR(Status))  AmiPostMgr = NULL;
       }
    }

    if (AmiPostMgr)
    {
        AmiPostMgr->DisplayProgress(AMI_PROGRESS_BOX_INIT,
                    L"FCH NCB Update Progress",
                    NULL,
                    NULL,
                    0,
                    &DisplayHandle,
                    &OutKey);
    }

    for (i = 0; i < FchUpdatBlockTblEntries; i++)
    {
        StartBlock = FCH_FLASH_ADDR_TRANSFER(gFchUpdateBlockTable[i].StartAddress) / FLASH_BLOCK_SIZE;
        EndBlock = FCH_FLASH_ADDR_TRANSFER(gFchUpdateBlockTable[i].EndAddress) / FLASH_BLOCK_SIZE;

        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"Table%d, StartBlock: %08X, EndBlock: %08X\n"
        		,i ,gFchUpdateBlockTable[i].StartAddress, gFchUpdateBlockTable[i].EndAddress));

        // Update NCBs
        for (j = StartBlock, k = 0; j < EndBlock; j++, k++)
        {
            UpdateBlockAddr = gFchUpdateBlockTable[i].StartAddress + (k * FLASH_BLOCK_SIZE);
            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"UpdateBlockAddr: %08X\n",UpdateBlockAddr));

            Source = RecoveryBuffer + gFchUpdateBlockTable[i].BlockOffset + (k * FLASH_BLOCK_SIZE);
            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"Source: %08X\n", Source));

            if (AmiPostMgr)
            {
                AmiPostMgr->DisplayProgress(AMI_PROGRESS_BOX_UPDATE,
                         L"FCH NCB Update Progress",
                         NULL,
                         NULL,
                         ((j-StartBlock)+1)*100/(EndBlock-StartBlock),
                         &DisplayHandle,
                         &OutKey);
            }

            OldTpl = pBS->RaiseTPL(TPL_HIGH_LEVEL);
            Status = Flash->Update((UINT8*)UpdateBlockAddr, FLASH_BLOCK_SIZE, Source);
            pBS->RestoreTPL(OldTpl);
            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"FCH Flash->Update Status: %08x\n",Status));
        }
    }
    if (AmiPostMgr)
    {
        AmiPostMgr->DisplayProgress(AMI_PROGRESS_BOX_CLOSE,
                     L"FCH NCB Update Progress",
                     NULL,
                     NULL,
                     0,
                     &DisplayHandle,
                     &OutKey);
    }

}

VOID FchRecoveryInsertOEMTableBeforeFlash (VOID)
{
    FchUpdateBlockTable();
}
