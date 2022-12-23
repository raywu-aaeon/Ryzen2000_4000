//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SpiFlashParts.h
    This file contains the structure and function prototypes needed
    for the Flash driver

**/
#ifndef __SPI_FLASH_PARTS_H_
#define __SPI_FLASH_PARTS_H_
#ifdef __cplusplus
extern "C" {
#endif

BOOLEAN
IdentifySst_25VF(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
);

BOOLEAN
IdentifyStm_25PExx(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
);

BOOLEAN
IdentifyAtmel_26DF(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
);

BOOLEAN
IdentifySst_25LF(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif