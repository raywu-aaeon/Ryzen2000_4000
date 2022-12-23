#include <Uefi.h>

#include <../SpiFlash.h>

#define MAX_SPI_ROM_OFFSET  (0x8000000) // 128MB

extern EX_FLASH_PART    gExFlashPart;
extern BOOLEAN          gIsSpiMmioAddressMappedBottom16M;

/**
    This function is to check whether the value is valid.

    @retval TRUE It is a valid value of SPI ROM offset
    @retval FALSE It isn't a valid value of SPI ROM offset
**/
BOOLEAN
IsValidSpiRomOffset(
    IN  UINTN   Address
)
{
    if( Address < MAX_SPI_ROM_OFFSET )
    {
        return TRUE;
    }

    return FALSE;
}

/**
    This function is to check whether the value is a valid MMIO address.

    @retval TRUE operation is successful or it(argument of Address) is already a 
                valid MMIO address and SpiRomMmioAddress is updated with converted address.
    @retval FALSE operation fails and no update for SpiRomMmioAddress.
**/
BOOLEAN
CommonConvertToSpiRomMmioAddress(
    IN      UINTN   Address,
    IN  OUT VOID    **SpiRomMmioAddress
)
{
    //
    // Here is an assumption of only 16MB of Top of 4GB MMIO space mapped to SPI ROM.
    //
    UINTN MmioSignificantBits;

    if( gExFlashPart.FlashVenDevId != 0 )
    {
        MmioSignificantBits = 0xFF000000 | (UINTN)(~(UINT32)(gExFlashPart.FlashCapacity - 1));
    }
    else
    {
        MmioSignificantBits = 0xFF000000; // 16MB of top of 4GB MMIO, default
    }

    if( IsValidSpiRomOffset( Address ) == TRUE )
    {
        // It is a valid offset of SPI rom, then convert it to MMIO address
        // if it(offset) is mapped to MMIO.
        UINTN SpiRomOffsetBaseMappedToMmio = (gIsSpiMmioAddressMappedBottom16M) ? 0 : (SIZE_16MB);

        if( (Address >= SpiRomOffsetBaseMappedToMmio) && 
            (Address < (SpiRomOffsetBaseMappedToMmio + SIZE_16MB)) )
        {
            *SpiRomMmioAddress = (VOID*)(MmioSignificantBits | Address);
            return TRUE;
        }
        // It(Address) can't be convert to MMIO address.
        return FALSE;
    }

    if( (Address < SIZE_4GB) &&
        ((MmioSignificantBits & Address) == MmioSignificantBits) )
    {
        // it is already MMIO address mapped top of 4GB.
        *SpiRomMmioAddress = (VOID*)Address;
        return TRUE;
    }

    // unexpected error
    return FALSE;
}