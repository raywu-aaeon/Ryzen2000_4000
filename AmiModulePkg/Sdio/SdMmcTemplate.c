//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SdMmcTemplate.c
 
    It is an template file for chipset specific programming.

**/

#include "SdioDriver.h"
#include "SdioController.h"

/**
    This function issues tuning command to card.
    This function is chipset specific porting, Care must be taken
    by porting engineer as this function is called twice from MmcCard.c
	for both HS200 and HS400 tuning. 

    @param  SdioDevInterface 
    @param  Port

    @retval EFI_STATUS

**/
EFI_STATUS 
SdMmcTunning (
    IN  SDIO_DEVICE_INFO        *SdioDevInfo,
    IN  UINT8                   Slot,
    IN  EMMC_TUNING_MODE        TuningMode
)
{
    return EFI_SUCCESS;
}


/**
    This function programs the hardware specific initialization for IO card.
    @param  SdioDevInterface 
    @param  Port

    @retval EFI_STATUS

**/
EFI_STATUS 
IoCardEnableHook (
    IN  SDIO_DEVICE_INFO *SdioDevInfo,
    IN  UINT8                   Slot
){
    return EFI_SUCCESS;
}

