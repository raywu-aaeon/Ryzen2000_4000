//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Common include files and definitions used by AmiFlashLibCommon.c
**/
#include <Uefi.h>
#include <PiPei.h>
#include <Token.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/AmiFlashLib.h>

#include <FlashElink.h>
#include <FlashPart.h>

#define INT_SIZE sizeof(UINTN)

BOOLEAN
FlashErase(
    volatile UINT8  *BlockAddress,
    UINT32          Length
);

//Flash part list creation code must be in this order
typedef
BOOLEAN
(IDENTIFY)(
    volatile UINT8  *BlockAddress,
    FLASH_PART      **Struct
);

//Oem flash write enable/disable list creation code must be in this order
typedef
VOID
(OEM_FLASH_WRITE)(
    VOID
);

//Oem get flash status list creation code must be in this order
typedef
BOOLEAN
(OEM_FLASH_STATUS)(
    IN  BOOLEAN *WriteStatus
);

extern IDENTIFY FLASH_LIST EndOfInitList;
extern OEM_FLASH_WRITE OEM_FLASH_WRITE_ENABLE_LIST EndOfOemFlashList;
extern OEM_FLASH_WRITE OEM_FLASH_WRITE_DISABLE_LIST EndOfOemFlashList;
extern OEM_FLASH_STATUS OEM_GET_FLASH_WRITE_STATUS_LIST EndOfOemGetFlashStatusList;