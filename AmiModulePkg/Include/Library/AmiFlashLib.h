//**********************************************************************
//*                                                                    *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
//*                                                                    *
//*      All rights reserved. Subject to AMI licensing agreement.      *
//*                                                                    *
//**********************************************************************

/** @file
  Header file that defines the Flash Library interfaces.
**/

#ifndef __AMI_FLASH_LIB__H__
#define __AMI_FLASH_LIB__H__

/// @name Bit definitions for AmiPcdFlashPropertyMask
/// Define properties of the flash device.
///@{

/// The flash device is not memory mapped when flash writes are enabled
#define AMI_FLASH_PROPERTY_NON_MEMORY_MAPPED_ON_WRITE_ENABLE 1
/// The flash device is not memory map under all circumstances
#define AMI_FLASH_PROPERTY_NON_MEMORY_MAPPED 3
/// The flash device has a zero flash erase polarity
#define AMI_FLASH_PROPERTY_ZERO_ERASE_POLARITY 4
///@}

// Compatibility definitions. Use AMI_FLASH_PROPERTY_XXX macros instead.
#define FLASH_PROPERTY_NON_MEMORY_MAPPED_ON_WRITE_ENABLE AMI_FLASH_PROPERTY_NON_MEMORY_MAPPED_ON_WRITE_ENABLE
#define FLASH_PROPERTY_NON_MEMORY_MAPPED AMI_FLASH_PROPERTY_NON_MEMORY_MAPPED
#define FLASH_PROPERTY_ZERO_ERASE_POLARITY AMI_FLASH_PROPERTY_ZERO_ERASE_POLARITY


/**
  Function to enable writes to the flash part.
**/
VOID AmiFlashDeviceWriteEnable(VOID);

/**
  Function to disable writes to the flash part.
**/
VOID AmiFlashDeviceWriteDisable(VOID);

/**
  Write the data into the block pointed to by BlockAddress.

  The function performs required erase/program operations to update flash device block with the supplied data.

  @param BlockAddress Pointer to the flash part area to write the data into. Must be aligned on a block boundary.
  @param Data Pointer to the data buffer to write into provided the BlockAddress

  @return BOOLEAN
  @retval TRUE The flash region was updated
  @retval FALSE The flash region could not be updated
**/
BOOLEAN AmiFlashWriteBlock(VOID* BlockAddress, VOID *Data);

/**
  Erase the block pointed to by the passed BlockAddress.

  @param BlockAddress Pointer to an address contained in the block.

  @return BOOLEAN
  @retval TRUE Erase completed successfully
  @retval FALSE Erase did not complete successfully
**/
BOOLEAN AmiFlashEraseBlock(VOID* BlockAddress);

/**
  Enable writing to the block that contains the BlockAddress

  @param BlockAddress Pointer to an address contained in the block.
**/
VOID AmiFlashBlockWriteEnable(VOID* BlockAddress);

/**
  Disable writing to the block that contains the BlockAddress.

  @param BlockAddress Pointer to an address contained in the block.
**/
VOID AmiFlashBlockWriteDisable(VOID* BlockAddress);

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
BOOLEAN AmiFlashProgram(VOID* Address, VOID *Data, UINT32 Length);

/**
  Read Length bytes from the Address and put them into the Data buffer

  @param Address Pointer to an address to start reading
  @param Data Pointer to a buffer to place the data into
  @param Length The number of bytes to read and place into the buffer

  @return BOOLEAN
  @retval TRUE Read completed successfully
  @retval FALSE Read did not complete successfully
**/
BOOLEAN  AmiFlashRead(VOID* Address, VOID *Data, UINT32 Length);

/**
  Converts a physical address to the starting address of the block
**/
VOID *AmiFlashBlockStartAddress(VOID *Address);

/**
  Performs flash device detection and prepares the library to work with the detected flash device.

  __NOTE: There is no requirement of calling this function prior to using other library functions.
  This function can be used to force re-initialization of the library (and re-detection of the flash device).
  The re-initialization might be useful when system switches between multiple flash devices at runtime.

  @return BOOLEAN
  @retval TRUE Initialization completed successfully
  @retval FALSE Initialization did not complete successfully
**/
BOOLEAN AmiFlashInit();

/**
  Returns default flash block size used by block functions

  @return flash block size in bytes
**/
UINT32 AmiGetFlashBlockSize();

/**
  Returns array of supported flash erase sizes

  @param[out] Granularity Array of supported flash erase sizes
  @param[out] NumberOfEntries Number of elements in the Granularity array  

  @return BOOLEAN
  @retval TRUE Erase granularity has been returned
  @retval FALSE Function call has failed
**/
BOOLEAN AmiGetFlashEraseGranularity(UINT32 **Granularity, UINT32* NumberOfEntries);

/**
  Returns current flash device write protection status

  @param[out] WriteEnable Current flash device write protection status.
              TRUE - write-enabled
              FALSE - write-disabled

  @return BOOLEAN
  @retval TRUE Status is returned
  @retval FALSE Function call has failed
**/
BOOLEAN AmiGetFlashWriteStatus(BOOLEAN *WriteEnable);

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
BOOLEAN AmiFlashErase(VOID* Address, UINT32 Length, BOOLEAN AdressOffset);

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
BOOLEAN AmiFlashWrite(VOID* Address, VOID *Data, UINT32 Length, BOOLEAN AdressOffset);

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
BOOLEAN AmiFlashWriteEnable(VOID* Address, UINT32 Length, BOOLEAN AdressOffset);


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
BOOLEAN AmiFlashWriteDisable(VOID* Address, UINT32 Length, BOOLEAN AdressOffset);

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
BOOLEAN AmiFlashProgramEx(VOID* Address, VOID *Data, UINT32 Length, BOOLEAN AdressOffset);

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
BOOLEAN  AmiFlashReadEx(VOID* Address, VOID *Data, UINT32 Length, BOOLEAN AdressOffset);

#endif
