//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

#ifndef __SPI_FLASH_INC_H__
#define __SPI_FLASH_INC_H__

BOOLEAN
IsValidSpiRomOffset(
    IN  UINTN   Address
);

BOOLEAN
CommonConvertToSpiRomMmioAddress(
    IN      UINTN   Address,
    IN  OUT VOID    **SpiRomMmioAddress
);

VOID*
EFIAPI
SpiFlashAsmMfence(
    VOID
);
#endif