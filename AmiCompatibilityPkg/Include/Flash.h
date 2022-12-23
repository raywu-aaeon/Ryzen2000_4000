//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/**
  @file Flash.h
 */

#ifndef __FLASH__H__
#define __FLASH__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <Efi.h>


#define AMI_EVENT_FLASH_WRITE_LOCK \
    { 0x49D34AE7, 0x9454, 0x4551, {0x8F, 0x71, 0x46, 0x7D, 0x8C, 0x0E, 0x4E, 0xF5 }}

VOID FlashDeviceWriteEnable();
VOID FlashDeviceWriteDisable();
BOOLEAN FlashWriteBlock(UINT8* BlockAddress, UINT8 *Data);
EFI_STATUS FlashInit(volatile UINT8* pBlockAddress);

VOID FlashVirtualFixup(EFI_RUNTIME_SERVICES *pRS);

BOOLEAN FlashEraseBlock(volatile UINT8* BlockAddress);
VOID FlashBlockWriteEnable(UINT8* BlockAddress);
VOID FlashBlockWriteDisable(UINT8* BlockAddress);
BOOLEAN FlashProgram(volatile UINT8* Address, UINT8 *Data, UINT32 Length);
BOOLEAN  FlashRead(volatile UINT8* Address, UINT8 *Data, UINT32 Length);

#define BLOCK(adr) ( (UINTN)(adr) -  (((UINTN)(adr) - FlashDeviceBase)%FlashBlockSize) )

extern const UINT32 FlashBlockSize;
extern const UINTN FlashDeviceBase;
/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
