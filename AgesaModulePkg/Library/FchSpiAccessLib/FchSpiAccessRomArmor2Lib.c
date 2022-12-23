/*
*****************************************************************************
*
* Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
*
*******************************************************************************
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Filecode.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/FchSpiAccessLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdPspFlashAccLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_FCHSPIACCESSROMARMOR2LIB_FILECODE

#define IS_SPI_ROM2_OFFSET(a) (((a) < 0x1000000) ? TRUE : FALSE)
#define IS_IN_SPI_ROM2_WINDOW(a) ((((a) & ~(0xFFFFFF)) == 0xFF000000) ? TRUE : FALSE)
#define IS_SPI_ROM3_OFFSET(a) (((a) < 0x4000000) ? TRUE : FALSE)
#define IS_IN_SPI_ROM3_WINDOW(a) ((((a) & ~(0x3FFFFFF)) == 0xFD00000000) ? TRUE : FALSE)
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
 * IsRom2Decoded - check Offset
 *
 *
 * @param[in] Offset - The offset of ROM
 *
 * @retval BOOLEAN Is in SPI ROM2 decode window or not
 */
BOOLEAN
IsRom2Decoded (
  IN       UINT64        Offset
  )
{
  return FALSE;
}

/**
 * FchSpiRomRead - Read the SPI ROM
 *
 *
 * @param[in] Offset - The offset of ROM or ROM2 address
 * @param[out]*Data - Buffer address to save the data
 * @param[in] Length - The number of byte to read
 *
 * @retval BOOLEAN success read or not
 */
BOOLEAN
FchSpiRomRead (
    IN      UINT32            Offset,
    OUT     UINT8             *Data,
    IN      UINT32            Length
  )
{
  return FchSpiRomReadEx(Offset, Data, Length);
}

/**
 * FchSpiRomReadEx - Extended function to read the SPI ROM
 *
 *
 * @param[in] Location - Host address in ROM2/ROM3 window to SPI ROM
 *                     - Offset of host SPI ROM3 address window when ROM Armor 2 disabled
 *                     - Offset of physical ROM when ROM Armor 2 enabled
 * @param[out]*Data - Buffer address to save the data
 * @param[in] Length - The number of byte to read
 *
 * @retval BOOLEAN success read or not
 */
BOOLEAN
FchSpiRomReadEx (
    IN      UINTN             Location,
    OUT     UINT8             *Data,
    IN      UINT32            Length
  )
{
  EFI_STATUS        Status;
  UINTN             NumByte;
  UINTN             FlasAddress;

  if (sizeof(UINTN) != sizeof(UINT64)){ //not in 64 bit mode
    return FALSE;
  }

  if ((Data == NULL) || (Length == 0)){
   return FALSE;
  }

  if( IS_SPI_ROM3_OFFSET (Location)) {  // Offset of ROM
    if((Location >= FCH_ROM_SIZE_64M) || (Length > FCH_ROM_SIZE_64M) || ((Location + Length) > FCH_ROM_SIZE_64M)){
    return FALSE;
    }
    FlasAddress = FCH_ROM_START_ADDRESS_3 + Location;
  } else if(IS_IN_SPI_ROM2_WINDOW(Location) || IS_IN_SPI_ROM3_WINDOW(Location)){ // ROM2/ROM3 address
    FlasAddress = Location;
  } else{
    return FALSE;
  }

  NumByte = Length;
  Status = PspReadFlash (Location, &NumByte, Data);
  if (Status == EFI_NOT_FOUND) {
    CopyMem (Data, (VOID *)FlasAddress, NumByte);
  }

  return TRUE;
}