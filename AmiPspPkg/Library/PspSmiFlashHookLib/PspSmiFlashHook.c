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

/** @file PspSmiFlashHook.c
    SW SMI hook. 

**/


#include <AmiDxeLib.h>
#include <Protocol/SmiFlash.h>
#include <Library/DebugLib.h>
//----------------------------------------------------------------------------


/**
    This function is SW SMI hook that sets Flash Block Description
    type for AMI AFU utility.

        
    @param SwSmiNum SW SMI value number
    @param Buffer Flash descriptor address

    @retval VOID

**/

#define FLASH_DEVICE_BASE_ADDRESS           (0xFFFFFFFF - FLASH_SIZE + 1)
// ADDRESS is the OFFSET
#define ROMSIG_BASE                         (0xFFFFFFFF - FLASH_SIZE + FCH_FIRMWARE_OFFSET + 1)
#define AMD_ROMSIG_BLOCK_ADDRESS            (ROMSIG_BASE - FLASH_DEVICE_BASE_ADDRESS)
#define AMD_ROMSIG_BLOCK_END                (AMD_ROMSIG_BLOCK_ADDRESS + ROMSIG_SIZE)
#define AMD_PSP_NVRAM_BLOCK_ADDRESS         (PSP_BLOCK_START_ADDRESS - FLASH_DEVICE_BASE_ADDRESS)
#define AMD_PSP_NVRAM_BLOCK_END             (AMD_PSP_NVRAM_BLOCK_ADDRESS + TOTAL_PSP_NVRAM_SIZE)
#define AMD_PSP_FIXED_BLOCK_ADDRESS         (PSP_COMBO_DIRECTORY_ADDRESS - FLASH_DEVICE_BASE_ADDRESS)
#define AMD_PSP_FIXED_BLOCK_END             (AMD_PSP_FIXED_BLOCK_ADDRESS + PSP_COMBO_DIRECTORY_SIZE + PSP_FIRST_UPDATABLE_BLOCK_OFFSET - BLOCK_0_OFFSET)

#if PSP_USE_HW_AUTH == 1
#if PROTECT_PSP_FIXED_AREA_FROM_BEING_ERASED == 1
    #error  "PSP Crisis recovery is not supported in PSB mode. Please turn off token PROTECT_PSP_FIXED_AREA_FROM_BEING_ERASED."
#endif
#endif

VOID
PspUpdateBlockTypeId (
  IN    UINT8   SwSmiNum,
  IN    UINT64  Buffer
)
{
    BLOCK_DESC  *BlockDesc;
    UINTN       i;

    // Return if SW SMI value is not "Get Flash Info"
    if (SwSmiNum != SMIFLASH_GET_FLASH_INFO) 
        return;
    
    BlockDesc = (BLOCK_DESC*)&((INFO_BLOCK*)Buffer)->Blocks;

    // Lock PSP NVRAM area
    for (i = 0; i < ((INFO_BLOCK*)Buffer)->TotalBlocks; i++)
    {
        DEBUG((DEBUG_INFO, "PspUpdateBlockTypeId(PSP NVRAM): %08X(%08X), Block %08X\n",
                AMD_PSP_NVRAM_BLOCK_ADDRESS, AMD_PSP_NVRAM_BLOCK_END, BlockDesc[i].StartAddress));
        if (BlockDesc[i].StartAddress < AMD_PSP_NVRAM_BLOCK_ADDRESS) 
            continue;

        if (BlockDesc[i].StartAddress >= AMD_PSP_NVRAM_BLOCK_END)        	
            continue;

        DEBUG((DEBUG_INFO, "PspUpdateBlockTypeId: Found Blocks %08X\n",BlockDesc[i].StartAddress));

        BlockDesc[i].Type = PSP_FLASH_BLOCK_DESC_TYPE;
    }

#if (PROTECT_PSP_FIXED_AREA_FROM_BEING_ERASED == 1)
    // Lock ROM Sig area
    for (i = 0; i < ((INFO_BLOCK*)Buffer)->TotalBlocks; i++) {

        DEBUG((DEBUG_INFO,"PspUpdateBlockTypeId(ROMSIG): %08X(%08X), Block %08X\n",AMD_ROMSIG_BLOCK_ADDRESS,AMD_ROMSIG_BLOCK_END,BlockDesc[i].StartAddress));

        if (BlockDesc[i].StartAddress < AMD_ROMSIG_BLOCK_ADDRESS)
            continue;

        if (BlockDesc[i].StartAddress >= AMD_ROMSIG_BLOCK_END)
            continue;

        DEBUG((DEBUG_INFO,"PspUpdateBlockTypeId: Found Blocks %08X\n",BlockDesc[i].StartAddress));

        BlockDesc[i].Type = PSP_FLASH_BLOCK_DESC_TYPE;
    }

    // Lock PSP fixed area
    for (i = 0; i < ((INFO_BLOCK*)Buffer)->TotalBlocks; i++)
    {
        DEBUG((DEBUG_INFO, "PspUpdateBlockTypeId(PSP FIXED AREA): %08X(%08X), Block %08X\n",
                AMD_PSP_FIXED_BLOCK_ADDRESS, AMD_PSP_FIXED_BLOCK_END, BlockDesc[i].StartAddress));
        if (BlockDesc[i].StartAddress < AMD_PSP_FIXED_BLOCK_ADDRESS)
            continue;

        if (BlockDesc[i].StartAddress >= AMD_PSP_FIXED_BLOCK_END)
            continue;

        DEBUG((DEBUG_INFO, "PspUpdateBlockTypeId: Found Blocks %08X\n",BlockDesc[i].StartAddress));

        BlockDesc[i].Type = PSP_FLASH_BLOCK_DESC_TYPE;
    }
#endif
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
