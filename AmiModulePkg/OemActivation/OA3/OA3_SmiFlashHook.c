//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file OA3_SmiFlashHook.c

**/

#include "OA3.h"
#include <Protocol/AmiSmiFlash.h>
#include <Library/DebugLib.h>


/**
    This function is SW SMI hook that sets Flash Block Description
    type for AMI AFU utility. 

    @param 
        SwSmiNum    - SW SMI value number
        Buffer      - Flash descriptor address

    @retval VOID

**/

VOID OemActivationUpdateBlockTypeId (
    IN UINT8  SwSmiNum,
    IN UINT64 Buffer )
{
    AMI_SMI_FLASH_BLOCK_DESC *BlockDesc;
    UINTN  i;

    // return if SW SMI value is not "Get Flash Info"
    if (SwSmiNum != AMI_SMI_FLASH_GET_FLASH_INFO_SMI)
        return;

    BlockDesc = (AMI_SMI_FLASH_BLOCK_DESC*)&((AMI_SMI_FLASH_INFO_BLOCK*)Buffer)->Blocks;

    for (i = 0; i < ((AMI_SMI_FLASH_INFO_BLOCK*)Buffer)->TotalBlocks; i++) {

//        DEBUG ((DEBUG_INFO, "OemActivationUpdateBlockTypeId: %08X(%08X), Block %08X\n",OEM_ACTIVATION_BLOCK_ADDRESS,OEM_ACTIVATION_BLOCK_END,BlockDesc[i].StartAddress));

        if (BlockDesc[i].StartAddress < OEM_ACTIVATION_BLOCK_ADDRESS)
            continue;

        if (BlockDesc[i].StartAddress >= OEM_ACTIVATION_BLOCK_END)
            continue;

//        DEBUG ((DEBUG_INFO, "OemActivationUpdateBlockTypeId: Found Blocks %08X\n",BlockDesc[i].StartAddress));

        BlockDesc[i].Type = AMI_SMI_FLASH_OA3_FLASH_BLOCK_DESC_TYPE;
    }
}
