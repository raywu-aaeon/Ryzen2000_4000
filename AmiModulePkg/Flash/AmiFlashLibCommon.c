//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
    Common AmiFlashlibrary functions used by both the DXE and Runtime drivers
**/
#include "AmiFlashLibCommon.h"

/// Global variable used to store the address of the start of the BIOS region in the flash part
UINTN       gAmiFlashDeviceBase = (0xFFFFFFFF - FLASH_SIZE + 1);
UINT32      gFlashBlockSize = FLASH_BLOCK_SIZE;
UINTN       gFlashEmpty = (UINTN)(-FLASH_ERASE_POLARITY);
UINT16      gFlashId = 0;
UINT32      gDeviceCapacity = FLASH_SIZE;
FLASH_PART  *gFlashApi = NULL;
UINT8       gFlashDeviceNumber[FLASH_PART_STRING_LENGTH];

IDENTIFY*           gFlashList[] = {FLASH_LIST NULL};
OEM_FLASH_WRITE*    gOemFlashWriteEnable[] = {OEM_FLASH_WRITE_ENABLE_LIST NULL};
OEM_FLASH_WRITE*    gOemFlashWriteDisable[] = {OEM_FLASH_WRITE_DISABLE_LIST NULL};
OEM_FLASH_STATUS*   gOemGetFlashWriteStatus[] = {OEM_GET_FLASH_WRITE_STATUS_LIST NULL};
UINT16              gOemValidFlashTable[] = {OEM_FLASH_VALID_TABLE_LIST 0xFFFF};

/**
    This function goes through the elinked list of oem flash write enable
    functions giving control.
**/
VOID
OemFlashDeviceWriteEnable(
    VOID
)
{
    UINT8   Index;

    for( Index = 0; gOemFlashWriteEnable[Index] != NULL; Index++ )
        gOemFlashWriteEnable[Index]();
}

/**
    This function goes through the elinked list of oem flash write disable
    functions giving control.
**/
VOID
OemFlashDeviceWriteDisable(
    VOID
)
{
    UINT8   Index;

    for( Index = 0; gOemFlashWriteDisable[Index] != NULL; Index++ )
        gOemFlashWriteDisable[Index]();
}

/**
    This function goes through the elinked list of oem get flash write status.

    @param WriteEnabled return flash device's write status

    @return BOOLEAN
    @retval TRUE all functions are executed successfully and all functions' write status is TURE
    @retval FALSE there is function which is executed failed, return WriteEnabled value should be ignored
**/
BOOLEAN
OemGetFlashDeviceWriteStatus(
    OUT BOOLEAN *WriteEnabled
)
{
    UINT8   Index;

    //If there is no function in elink list, status cannot be determined, returns FALSE
    if( gOemGetFlashWriteStatus[0] == NULL )
    {
        return FALSE;
    }

    //Check all functions in elink list
    for( Index = 0; gOemGetFlashWriteStatus[Index] != NULL; Index++ )
    {
        BOOLEAN Result;

        Result = gOemGetFlashWriteStatus[Index]( WriteEnabled );
        //Retrun fail since function execution is failed
        if( Result == FALSE )
            return FALSE;
        //Break
        if( *WriteEnabled == FALSE )
            return TRUE;
    }

    //Get here only when all linked functions return write enabled
    return TRUE;
}

/**
    This function identifies the supported flash parts and returns TRUE.
    If flash part is not supported by this module it will return FALSE.

    @param dFlashId Present Flash Part ID

    @retval TRUE Flash part is Valid.
    @retval FALSE Flash part is not Valid.
**/
BOOLEAN
OemIsFlashValid(
    VOID
)
{
    UINTN   Index;

    if( gOemValidFlashTable[0] == 0xFFFF )
        return TRUE;

    for( Index = 0; gOemValidFlashTable[Index] != 0xFFFF; Index++ )
    {
        if( gFlashId == gOemValidFlashTable[Index] )
            return TRUE;
    }

    return FALSE;
}

/**
    Fixup global data for for a virtual address space. This routine must be
    called by the library consumer in the EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE
    event handler

    @param Rs pointer to the Runtime Services Table
**/
VOID
FlashVirtualFixup(
    IN  EFI_RUNTIME_SERVICES    *Rs
)
{
    static BOOLEAN  FlashVirtual = FALSE;
    UINT8           Index;

    //if gFlashApi is NULL, nothing to fix up
    //Notes: Current implementation of Identify routines
    //will not work in virtual mode since absolute addresses are used
    //That's Ok for now since current flash library consumers
    //call flash routines at boot time, so we should have gFlashApi
    //initialized at this point
    if( gFlashApi == NULL )
        return;

    // This function gets called from Nvramdxe.c and flash.c, do anything when
    // the function is called second time.
    if( FlashVirtual == TRUE )
        return;
    else
        FlashVirtual = TRUE;

    //Do device specific fixups
    gFlashApi->FlashVirtualFixup( Rs );

    //Fixup gFlashApi member functions
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashReadCommand) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashEraseCommand) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashEraseCommandEx) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashProgramCommand) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashBlockWriteEnable) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashBlockWriteDisable) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashDeviceWriteEnable) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashDeviceWriteDisable) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashGetEraseGranularity) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashVirtualFixup) );
    Rs->ConvertPointer( 0, (VOID**)&(gFlashApi->FlashPartNumber) );

    //Fixup gFlashApi pointer
    Rs->ConvertPointer( 0, (VOID**)&gFlashApi );

    //convert gAmiFlashDeviceBase address
    Rs->ConvertPointer( 0, (VOID**)&gAmiFlashDeviceBase );

    //Fixup gOemFlashWriteEnable list
    for( Index = 0; gOemFlashWriteEnable[Index] != NULL; Index++ )
        Rs->ConvertPointer( 0, (VOID**)&gOemFlashWriteEnable[Index] );

    //Fixup gOemFlashWriteDisable list
    for( Index = 0; gOemFlashWriteDisable[Index] != NULL; Index++ )
        Rs->ConvertPointer( 0, (VOID**)&gOemFlashWriteDisable[Index] );

    //Fixup gOemGetFlashWriteStatus list
    for( Index = 0; gOemGetFlashWriteStatus[Index] != NULL; Index++ )
        Rs->ConvertPointer( 0, (VOID**)&gOemGetFlashWriteStatus[Index] );
}

/**
    Verifies if the device has been erased properly or if the current byte
    is the same as the byte to be written at this location.

    @param Dest starting address of where the data will be written
    @param Source starting address of the data that is supposed to be written
    @param Size length of the data set to check
    @param IsClean return value to indicate that the data area that will be written
                    to has already been erased
    @param IsEqual return value to indicate that the data to be written is the same
                    as the data that is already there
**/
VOID
IsCleanOrEqual(
    IN  UINT8       *Dest,
    IN  const UINT8 *Source,
    IN  UINTN       Size,
    IN  BOOLEAN     AdressOffset,
    OUT BOOLEAN     *IsClean,
    OUT BOOLEAN     *IsEqual
)
{
    BOOLEAN NoMmio;

#if defined(NO_MMIO_FLASH_ACCESS_DURING_UPDATE) && (NO_MMIO_FLASH_ACCESS_DURING_UPDATE == 1)
    NoMmio = TRUE;
#else
    NoMmio = FALSE;
#endif
    *IsClean = TRUE;
    *IsEqual = TRUE;

    //If input dest is memory address and token NO_MMIO_FLASH_ACCESS_DURING_UPDATE is set or
    //input dest is flash offest
    if( ((AdressOffset == TRUE) && (NoMmio == TRUE)) || (AdressOffset == FALSE) )
    {
        UINT8   Buffer[WRITE_BLOCK_BUFFER_SIZE];
        UINTN   RestSize;
        UINTN   ReadSize;
        UINT32  Index;

        for( RestSize = Size, ReadSize = sizeof(Buffer);
             RestSize > 0; RestSize -= ReadSize )
        {
            if( RestSize > ReadSize )
                ReadSize = sizeof(Buffer);
            else
                ReadSize = RestSize;
            AmiFlashReadEx(
                (VOID*)((UINTN)Dest + (Size - RestSize)),
                (VOID*)Buffer,
                (UINT32)ReadSize,
                AdressOffset );
            for( Index = 0; Index < ReadSize; Index++ )
            {
                if( Buffer[Index] != (UINT8)gFlashEmpty ) *IsClean = FALSE;
                if( Buffer[Index] != Source[Size - RestSize + Index] ) *IsEqual = FALSE;
                if( !(*IsEqual || *IsClean) ) return;
            }
        }
    }
    else
    {
        // loops through the destination looking to see if the data is the same
        //  as the source, or if the Destination has already bee erased
        // If Dest and Source are both INT_SIZE aligned, comparing them with INTN pointer
        if( !(((UINTN)Dest & (INT_SIZE - 1)) || ((UINTN)Source & (INT_SIZE - 1))) )
        {
            UINTN   *DestN = (UINTN*)Dest;
            UINTN   *SourceN = (UINTN*)Source;

            for( ; Size >= INT_SIZE; Size -= INT_SIZE )
            {
                if( *DestN != gFlashEmpty )
                    *IsClean = FALSE;
                if( *DestN++ != *SourceN++ )
                    *IsEqual = FALSE;
                if( !(*IsEqual || *IsClean) )
                    return;
            }
        }

        // since the address may not be INT_SIZE aligned, this checks
        //  the rest of the data
        for( ; Size > 0; Size-- )
        {
            if( *Dest != (UINT8)gFlashEmpty )
                *IsClean = FALSE;
            if( *Dest++ != *Source++ )
                *IsEqual = FALSE;
            if( !(*IsEqual || *IsClean) )
                return;
        }
    }
}

/**
    Check input address and length are aligned with granularity

    @param Address Address to be checked
    @param Length Length to be checked
**/
BOOLEAN
CheckAlignmentWithGranularity(
    IN  VOID    *Address,
    IN  UINT32  Length
)
{
    UINT32  *Granularities;
    UINT32  Entries;
    UINT32  Alignment;

    if( AmiGetFlashEraseGranularity( &Granularities, &Entries ) == TRUE )
    {
        UINT32  Index;
        for( Index = 0, Alignment = Granularities[0]; Index < Entries; Index++ )
        {
            //Choose smaller granularity for alignment
            if( Alignment > Granularities[Index] )
            {
                Alignment = Granularities[Index];
            }
        }
    }
    else
    {
        //default check with block size
        Alignment = gFlashBlockSize;
    }

    if( ((UINTN)Address % Alignment != 0) || (Length % Alignment != 0) )
        return FALSE;
    else
        return TRUE;
}

/**
    This function goes through the elinked list of identify functions giving
    control until one part is identified properly

    @param BlockAddress Address to access the flash part

    @retval EFI_SUCCESS
**/
EFI_STATUS
FlashInit(
    IN  volatile UINT8  *BlockAddress
)
{
    UINTN   Index;
    BOOLEAN Found = FALSE;

    for( Index = 0; (Found == FALSE) && gFlashList[Index]; Index++ )
    {
        Found = gFlashList[Index]( BlockAddress, &gFlashApi );
    }

    if( Found && (OemIsFlashValid() == FALSE) )
        gFlashApi = NULL;

    return EFI_SUCCESS;
}

/**
    This function chooses the correct flash part to call and then fill its model name.

    @param BlockAddress Address to access flash part
    @param Buffer Buffer to fill the flash model name.
**/
VOID
GetFlashPartInfomation(
    IN  UINT8   *BlockAddress,
    IN  UINT8   *Buffer
)
{
    if( gFlashApi == NULL )
    {
        SetMem( &gFlashDeviceNumber, FLASH_PART_STRING_LENGTH, 0 );
        FlashInit( BlockAddress );
    }

    if( (gFlashApi != NULL) && (gFlashApi->FlashPartNumber != NULL) )
    {
        UINT8   FlashStringSign[4] = {'$','F','P','S'};

        CopyMem( (VOID*)Buffer, (VOID*)FlashStringSign, 4 );
        Buffer += sizeof(UINT32);
        WriteUnaligned32( (UINT32*)Buffer, FLASH_PART_STRING_LENGTH );
        Buffer += sizeof(UINT32);
        CopyMem( (VOID*)Buffer, (VOID*)(gFlashApi->FlashPartNumber), FLASH_PART_STRING_LENGTH );
    }
}

/**
    Function to get flash part name string
**/
CHAR8*
AmiGetFlashPartName(
    VOID
)
{
    return (CHAR8*)gFlashDeviceNumber;
}

/**
    Function to enable writes to the flash part.
**/
VOID
AmiFlashDeviceWriteEnable(
    VOID
)
{
    OemFlashDeviceWriteEnable ();

    if ( gFlashApi == NULL )
        FlashInit( (UINT8*)gAmiFlashDeviceBase );

    if ( gFlashApi == NULL )
        return;

    gFlashApi->FlashDeviceWriteEnable();
}

/**
    Function to disable writes to the flash part.
**/
VOID
AmiFlashDeviceWriteDisable(
    VOID
)
{
    if( gFlashApi == NULL )
        FlashInit( (UINT8*)gAmiFlashDeviceBase );

    if( gFlashApi == NULL )
        return;

    gFlashApi->FlashDeviceWriteDisable();

    OemFlashDeviceWriteDisable();
}

/**
    Write the data into the block pointed to by BlockAddress.

    The function performs required erase/program operations to update flash device block with the supplied data.

    @param BlockAddress Pointer to the flash part area to write the data into. Must be aligned on a block boundary.
    @param Data Pointer to the data buffer to write into provided the BlockAddress

    @return BOOLEAN
    @retval TRUE The flash region was updated
    @retval FALSE The flash region could not be updated
**/
BOOLEAN
AmiFlashWriteBlock(
    VOID    *BlockAddress,
    VOID    *Data
)
{
    BOOLEAN AdressOffset;

    if( (UINTN)BlockAddress < gDeviceCapacity )
        AdressOffset = FALSE;
    else
        AdressOffset = TRUE;

    return AmiFlashWrite( BlockAddress, Data, gFlashBlockSize, AdressOffset );
}

/**
    Erase the block pointed to by the passed BlockAddress.

    @param BlockAddress Pointer to an address contained in the block.

    @return BOOLEAN
    @retval TRUE Erase completed successfully
    @retval FALSE Erase did not complete successfully
**/
BOOLEAN
AmiFlashEraseBlock(
    VOID    *BlockAddress
)
{
    BOOLEAN AdressOffset;

    if( (UINTN)BlockAddress < gDeviceCapacity )
        AdressOffset = FALSE;
    else
        AdressOffset = TRUE;

    return AmiFlashErase( BlockAddress, gFlashBlockSize, AdressOffset );
}

/**
    Enable writing to the block that contains the BlockAddress

    @param BlockAddress Pointer to an address contained in the block.
**/
VOID
AmiFlashBlockWriteEnable(
    VOID    *BlockAddress
)
{
    BOOLEAN AdressOffset;

    if( (UINTN)BlockAddress < gDeviceCapacity )
        AdressOffset = FALSE;
    else
        AdressOffset = TRUE;

    AmiFlashWriteEnable( BlockAddress, gFlashBlockSize, AdressOffset );
}

/**
    Disable writing to the block that contains the BlockAddress.

    @param BlockAddress Pointer to an address contained in the block.
**/
VOID
AmiFlashBlockWriteDisable(
    VOID    *BlockAddress
)
{
    BOOLEAN AdressOffset;

    if( (UINTN)BlockAddress < gDeviceCapacity )
        AdressOffset = FALSE;
    else
        AdressOffset = TRUE;

    AmiFlashWriteDisable( BlockAddress, gFlashBlockSize, AdressOffset );
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
AmiFlashProgram(
    VOID    *Address,
    VOID    *Data,
    UINT32  Length
)
{
    BOOLEAN AdressOffset;

    if( (UINTN)Address < gDeviceCapacity )
        AdressOffset = FALSE;
    else
        AdressOffset = TRUE;

    return AmiFlashProgramEx( Address, Data, Length, AdressOffset );
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
AmiFlashRead(
    VOID    *Address,
    VOID    *Data,
    UINT32  Length
)
{
    BOOLEAN AdressOffset;

    if( (UINTN)Address < gDeviceCapacity )
        AdressOffset = FALSE;
    else
        AdressOffset = TRUE;

    return AmiFlashReadEx( Address, Data, Length, AdressOffset );
}

/**
    Converts a physical address to the starting address of the block
**/
VOID*
AmiFlashBlockStartAddress(
    VOID    *Address
)
{
    return (VOID*)((UINTN)Address - (((UINTN)Address - gAmiFlashDeviceBase) % gFlashBlockSize));
}

/**
    Performs flash device detection and prepares the library to work with the detected flash device.

    __NOTE: There is no requirement of calling this function prior to using other library functions.
    This function can be used to force re-initialization of the library (and re-detection of the flash device).
    The re-initialization might be useful when system switches between multiple flash devices at runtime.

    @return BOOLEAN
    @retval TRUE Initialization completed successfully
    @retval FALSE Initialization did not complete successfully
**/
BOOLEAN
AmiFlashInit()
{
    return !EFI_ERROR(FlashInit( (UINT8*)gAmiFlashDeviceBase ));
}

/**
    Returns default flash block size used by block functions

    @return flash block size in bytes
**/
UINT32
AmiGetFlashBlockSize()
{
    return gFlashBlockSize;
}

/**
    Returns array of supported flash erase sizes

    @param[out] Granularity Array of supported flash erase sizes
    @param[out] NumberOfEntries Number of elements in the Granularity array

    @return BOOLEAN
    @retval TRUE Erase granularity has been returned
    @retval FALSE Function call has failed
**/
BOOLEAN
AmiGetFlashEraseGranularity(
    UINT32  **Granularity,
    UINT32  *NumberOfEntries
)
{
    if( gFlashApi == NULL )
        FlashInit( (UINT8*)gAmiFlashDeviceBase );

    if( gFlashApi == NULL )
        return FALSE;

    return gFlashApi->FlashGetEraseGranularity( Granularity, NumberOfEntries );
}

/**
    Returns current flash device write protection status

    @param[out] WriteEnable Current flash device write protection status.
              TRUE - write-enabled
              FALSE - write-disabled

    @return BOOLEAN
    @retval TRUE Status is returned
    @retval FALSE Function call has failed
**/
BOOLEAN
AmiGetFlashWriteStatus(
    BOOLEAN *WriteEnable
)
{
    return OemGetFlashDeviceWriteStatus( WriteEnable );
}

/**
    Erases portion of the flash device

    @param Address Address to erase. Must be aligned to flash erase granularity.
            Can be address or offset depending on the AdressOffset value (see below).
    @param Length The number of bytes to erase. Must be aligned to flash erase granularity.
    @param AdressOffset Defines format of the Address.
            TRUE - Address is a CPU address (can only be used for memory mapped regions)
            FALSE - Address is an offset within SPI image

    @return BOOLEAN
    @retval TRUE Erase completed successfully
    @retval FALSE Erase did not complete successfully or input parameters are not properly aligned.
**/
BOOLEAN
AmiFlashErase(
    VOID    *Address,
    UINT32  Length,
    BOOLEAN AdressOffset
)
{
    EFI_STATUS  Status;

    if( gFlashApi == NULL )
        FlashInit( (UINT8*)Address );

    if( gFlashApi == NULL )
        return FALSE;

    Status = gFlashApi->FlashEraseCommandEx( (UINT8*)Address, Length, AdressOffset );
    if( !EFI_ERROR(Status) )
        return TRUE;
    else
        return FALSE;
}

/**
    Write the data into a portion of the flash device.

    The function performs required erase/program operations to update a portion of flash device with the supplied data.

    @param Address Address to write. Must be aligned to flash erase granularity.
                    Can be address or offset depending on the AdressOffset value (see below).
    @param Data Pointer to a buffer of size Length containing data to write into provided flash address.
    @param Length The number of bytes to write. Must be aligned to flash erase granularity.
    @param AdressOffset Defines format of the Address.
            TRUE - Address is a CPU address (can only be used for memory mapped regions)
            FALSE - Address is an offset within SPI image

    @return BOOLEAN
    @retval TRUE The flash region was updated
    @retval FALSE The flash region could not be updated or input parameters are not properly aligned.
**/
BOOLEAN
AmiFlashWrite(
    VOID    *Address,
    VOID    *Data,
    UINT32  Length,
    BOOLEAN AdressOffset
)
{
    BOOLEAN IsClean;
    BOOLEAN IsEqual;
    BOOLEAN Result;

    //This checks to see if the data in the flash part has already been
    //erased or if it is already the same as what will be programmed there
    IsCleanOrEqual( (UINT8*)Address, (UINT8*)Data, (UINTN)Length, AdressOffset, &IsClean, &IsEqual );

    //If it is already the same then exit
    if( IsEqual == TRUE )
        return TRUE;

    //If not the same enable the block for writing
    AmiFlashWriteEnable( Address, Length, AdressOffset );

    //This loop checks IsClean to see if the block area that is to be written to
    //has already been erased.  If it hasn't then, the FlashEraseBlock() is called
    //to erase the block.
    //If it is either clean or is erased, then it calls the program function
    if( IsClean || AmiFlashErase( Address, Length, AdressOffset ) )
        Result = AmiFlashProgramEx( Address, Data, Length, AdressOffset );
    // If it is not clean and the erase block function does not finish properly
    // then set result to return false
    else
        Result = FALSE;

    // disable the ability to write to the block
    AmiFlashWriteDisable( Address, Length, AdressOffset );

    return Result;
}

/**
    Enables update of a portion of the flash device

    @param Address Starting address of the area to be updated. Must be aligned to flash erase granularity.
            Can be address or offset depending on the AdressOffset value (see below).
    @param Length Length of the flash area. Must be aligned to flash erase granularity.
    @param AdressOffset Defines format of the Address.
            TRUE - Address is a CPU address (can only be used for memory mapped regions)
            FALSE - Address is an offset within SPI image

    @return BOOLEAN
    @retval TRUE Flash writes have been enabled
    @retval FALSE Operation failed or input parameters are not properly aligned.
**/
BOOLEAN
AmiFlashWriteEnable(
    VOID    *Address,
    UINT32  Length,
    BOOLEAN AdressOffset
)
{
    if( gFlashApi == NULL )
        FlashInit( (UINT8*)Address );

    if( gFlashApi == NULL )
        return FALSE;

    if( CheckAlignmentWithGranularity( Address, Length ) == FALSE )
        return FALSE;

    gFlashApi->FlashBlockWriteEnable( (volatile UINT8*)Address, Length, AdressOffset );

    return TRUE;
}

/**
    Disables update of a portion of the flash device

    @param Address Starting address of the area to be updated. Must be aligned to flash erase granularity.
            Can be address or offset depending on the AdressOffset value (see below).
    @param Length Length of the flash area. Must be aligned to flash erase granularity.
    @param AdressOffset Defines format of the Address.
            TRUE - Address is a CPU address (can only be used for memory mapped regions)
            FALSE - Address is an offset within SPI image

    @return BOOLEAN
    @retval TRUE Flash writes have been enabled
    @retval FALSE Operation failed or input parameters are not properly aligned.
**/
BOOLEAN
AmiFlashWriteDisable(
    VOID    *Address,
    UINT32  Length,
    BOOLEAN AdressOffset
)
{
    if( gFlashApi == NULL )
        FlashInit( (UINT8*)Address );

    if( gFlashApi == NULL )
        return FALSE;

    if( CheckAlignmentWithGranularity( Address, Length ) == FALSE )
        return FALSE;

    gFlashApi->FlashBlockWriteDisable( (volatile UINT8*)Address, Length, AdressOffset );

    return TRUE;
}

/**
    Program Length bytes of data from Data into the Address.
    __NOTE: No erase operation are performed.

    @param Address Pointer to the address to write the data
    @param Data The data to write into the address
    @param Length The number of bytes that need to be written
    @param AdressOffset Defines format of the Address.
            TRUE - Address is a CPU address (can only be used for memory mapped regions)
            FALSE - Address is an offset within SPI image

    @return BOOLEAN
    @retval TRUE Programming the data was successful
    @retval FALSE Programming the data was not successful
**/
BOOLEAN
AmiFlashProgramEx(
    VOID    *Address,
    VOID    *Data,
    UINT32  Length,
    BOOLEAN AdressOffset
)
{
    volatile UINT8  *TempAddress;
    UINT32          TempLength;
    UINT8           *DataPtr;

    if( gFlashApi == NULL )
        FlashInit( (UINT8*)Address );

    if( gFlashApi == NULL )
        return FALSE;

    TempAddress = (volatile UINT8*)Address;
    TempLength = Length;
    DataPtr = (UINT8*)Data;

    do
    {
        BOOLEAN Result;

        Result = gFlashApi->FlashProgramCommand( TempAddress, DataPtr, &TempLength, AdressOffset );
        if( Result == FALSE )
            return FALSE;
        TempAddress += (Length - TempLength);
        DataPtr += (Length - TempLength);
        Length = TempLength;
    }while( TempLength != 0 );

    return TRUE;
}

/**
    Read Length bytes from the Address and put them into the Data buffer

    @param Address Pointer to an address to start reading
    @param Data Pointer to a buffer to place the data into
    @param Length The number of bytes to read and place into the buffer
    @param AdressOffset Defines format of the Address.
        TRUE - Address is a CPU address (can only be used for memory mapped regions)
        FALSE - Address is an offset within SPI image

    @return BOOLEAN
    @retval TRUE Read completed successfully
    @retval FALSE Read did not complete successfully
**/
BOOLEAN
AmiFlashReadEx(
    VOID    *Address,
    VOID    *Data,
    UINT32  Length,
    BOOLEAN AdressOffset
)
{
    volatile UINT8  *TempAddress;
    UINT32          TempLength;
    UINT8           *DataPtr;

    if( gFlashApi == NULL )
        FlashInit( (UINT8*)Address );

    if( gFlashApi == NULL )
        return FALSE;

    TempAddress = (volatile UINT8*)Address;
    TempLength = Length;
    DataPtr = (UINT8*)Data;

    do
    {
        gFlashApi->FlashReadCommand( TempAddress, DataPtr, &TempLength, AdressOffset );
        TempAddress += (Length - TempLength);
        DataPtr += (Length - TempLength);
        Length = TempLength;
    }while( TempLength != 0 );

    return TRUE;
}

/**
    Library constructor for the DXE AmiFlashLib instance.

    @param ImageHandle The ImageHandle of the driver consuming the AmiFlashLib
    @param SystemTable Pointer to the EFI System Table

    @return EFI_SUCCESS The library constructor completed execution
**/
EFI_STATUS
EFIAPI
DxeAmiFlashLibConstructor(
    IN  EFI_HANDLE          ImageHandle,
    IN  EFI_SYSTEM_TABLE    *SystemTable
)
{
    return FlashInit( (UINT8*)gAmiFlashDeviceBase );
}

/**
    Library constructor for the PEI AmiFlashLib instance.

    @param  FileHandle   The handle of FFS header the loaded driver.
    @param  PeiServices  The pointer to the PEI services.

    @retval EFI_SUCCESS  The constructor always returns EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
PeiAmiFlashLibConstructor(
    IN  EFI_PEI_FILE_HANDLE     FileHandle,
    IN  CONST EFI_PEI_SERVICES  **PeiServices
)
{
    return FlashInit( (UINT8*)gAmiFlashDeviceBase );
}
