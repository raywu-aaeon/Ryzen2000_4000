//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
    Old FlashLib functions wrapper
**/
#include "FlashLibWrapper.h"

/**
    This function chooses the correct flash part to call and then enables
    write operation for a flash device
**/
VOID
FlashDeviceWriteEnable(
    VOID
)
{
    AmiFlashDeviceWriteEnable();
}

/**
    This function chooses the correct flash part to call and then disables
    write operation for a flash device
**/
VOID
FlashDeviceWriteDisable(
    VOID
)
{
    AmiFlashDeviceWriteDisable();
}

BOOLEAN
FlashWriteBlock(
    IN  UINT8   *BlockAddress,
    IN  UINT8   *Data
)
{
    return AmiFlashWriteBlock( (VOID*)BlockAddress, (VOID*)Data );
}

/**
    FlashInit() is in AmiFlashLib, it should be linked already.
**/

/**
    FlashVirtualFixup() is in AmiFlashLib, it should be linked already.
**/

/**
    Erase the block pointed to by the passed BlockAddress.

    @param BlockAddress Pointer to an address contained in the block.

    @return BOOLEAN
    @retval TRUE Erase completed successfully
    @retval FALSE Erase did not complete successfully
**/
BOOLEAN
FlashEraseBlock(
    IN  volatile UINT8  *BlockAddress
)
{
    return AmiFlashEraseBlock( (VOID*)BlockAddress );
}

/**
    Enable writing to the block that contains the BlockAddress

    @param BlockAddress Pointer to an address contained in the block.
**/
VOID
FlashBlockWriteEnable(
    IN  UINT8   *BlockAddress
)
{
    AmiFlashBlockWriteEnable( (VOID*)BlockAddress );
}

/**
    Disable writing to the block that contains the BlockAddress.

    @param BlockAddress Pointer to an address contained in the block.
**/
VOID
FlashBlockWriteDisable(
    IN  UINT8   *BlockAddress
)
{
    AmiFlashBlockWriteDisable( (VOID*)BlockAddress );
}

/**
    Program Length bytes of data from Data into the Address.
    __NOTE: No erase operation are performed.

    @param Address Pointer to the address to write the data
    @param Data The data to write into the address
    @param Length The number of bytes that need to be written

    @return BOOLEAN
    @retval TRUE Programming the data was successful
    @retval FALSE Programming the data was not successful
**/
BOOLEAN
FlashProgram(
    IN  volatile UINT8  *Address,
    IN  UINT8           *Data,
    IN  UINT32          Length
)
{
    return AmiFlashProgram( (VOID*)Address, (VOID*)Data, Length );
}

/**
    Read Length bytes from the Address and put them into the Data buffer

    @param Address Pointer to an address to start reading
    @param Data Pointer to a buffer to place the data into
    @param Length The number of bytes to read and place into the buffer

    @return BOOLEAN
    @retval TRUE Read completed successfully
    @retval FALSE Read did not complete successfully
**/
BOOLEAN
FlashRead(
    IN  volatile UINT8  *Address,
    IN  UINT8           *Data,
    IN  UINT32          Length
)
{
    return AmiFlashRead( (VOID*)Address, (VOID*)Data, Length );
}