//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
    Main file that implements the Flash Platform Library.
**/
#include <Uefi.h>
#include <Token.h>

/**
    Returns location of the system firmware flash region (a.k.a. BIOS) within flash device.

    Platform has to implement this function if non-standard firmware region mapping is employed.
    If this function returns EFI_UNSUPPORTED, flash module uses standard firmware region detection algorithm.

    @param[out] Address of the system firmware flash region
    @param[out] Size of the system firmware flash region
    @param[in] AdressOffset Defines format of the Address.
        TRUE - Address is a CPU address (can only be used for memory mapped regions)
        FALSE - Address is an offset within SPI image

    @retval EFI_SUCCESS Address and Size are updated with flash region information
    @retval EFI_UNSUPPORTED Functionality is not supported.
    @retval EFI_INVALID_PARAMETER Address or Size is NULL
    @retval EFI_DEVICE_ERROR Flash region information cannot be retrieved due to a hardware error
**/
EFI_STATUS
AmiGetSytemFirmwareRegion(
    UINTN   *Address,
    UINTN   *Size,
    BOOLEAN AdressOffset
)
{
    if( (Address == NULL) || (Size == NULL) )
        return EFI_INVALID_PARAMETER;

    if( AdressOffset == TRUE )
        *Address = (UINTN)((UINT32)0 - (UINT32)FLASH_SIZE);
    else
        *Address = 0;

    *Size = FLASH_SIZE;

    return EFI_SUCCESS;
}