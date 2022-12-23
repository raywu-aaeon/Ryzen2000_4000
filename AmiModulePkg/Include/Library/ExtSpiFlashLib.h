//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file ExtSpiFlashLib.h
    This file contains the structure and function prototypes needed
    for extened spi flash library

**/

#ifndef _EXT_SPI_FLASH_LIB_H_
#define _EXT_SPI_FLASH_LIB_H_

/**
    Read current specified segment(128Mbit).

    @param SegmentIndex, points to a buffer for receiveing current segment index

    @retval EFI_SUCCESS           Swtich to the specific segment successfully
    @retval EFI_UNSUPPORTED       Current SPI flash device is not supported.
    @retval EFI_DEVICE_ERROR      Operation aborted because of device limitation

**/
EFI_STATUS EFIAPI GetCurrent128MbSegment(OUT UINT8 *SegmentIndex);
/**
    Switch to the specific segment(128Mbit).

    @param SegmentIndex, 0x0 is 1st(lowest) 128Mbit segment, 0x1 is 2nd 128Mbit(upper) segment.

    @retval EFI_SUCCESS           Swtich to the specific segment successfully
    @retval EFI_UNSUPPORTED       Current SPI flash device is not supported.
    @retval EFI_DEVICE_ERROR      Operation aborted because of device limitation

**/
EFI_STATUS EFIAPI Switch128MbSegment(IN UINT8 SegmentIndex);


UINT8 EFIAPI CheckEAR(VOID);
/**
    This routine switch Extend Address Register (EAR)
    Extended Address Register (EAR):
     configure the memory device into two 128Mb segments to select which one is active through the EAR<0>.
                |-----------------|
                |                 |
                |                 |
                |     Top 16M     |
                |                 |
                |                 |<--EAR<0>= 1
   0xFFFFFFFF   |-----------------|
                |                 |
                |                 |
                |    Bottom 16M   |
                |                 |
                |                 |<--EAR<0>= 0 (default)
                |-----------------|

    @param area - TRUE:TOP 16M 
                  FALSE:Bottom 16M 
                  
    @return EFI_STATUS             
**/
VOID EFIAPI SwitchFlashArea(IN BOOLEAN area);

#endif