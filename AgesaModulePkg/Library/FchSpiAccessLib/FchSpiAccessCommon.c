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
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Library/FchSpiAccessLib.h>
#include "FchRegistersCommon.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/**
* DetectRom2Page - detect the ROM page decoded into ROM2 decode range
*
*
* @param VOID
*
* @retval UINT32 - the ROM page address (bit 24/25)
*/
UINT32
DetectRom2Page(
)
{
  UINT32    Value32;
  UINT8     SpiRomPageXor;
  UINT32    RomPage;

  RomPage = FCH_ROM_START_ADDRESS_2 >> 24;

  Value32 = MmioRead32 ((UINTN)(FCH_SPI_BASE_ADDRESS + FCH_SPI_MMIO_REG30));
  if (Value32 & FCH_SPI_R2MSK24){
    RomPage &= ~FCH_SPI_R2VAL24;
    RomPage |= Value32 & FCH_SPI_R2VAL24;
  }
  if (Value32 & FCH_SPI_R2MSK25){
    RomPage &= ~FCH_SPI_R2VAL25;
    RomPage |= Value32 & FCH_SPI_R2VAL25;
  }

  Value32 = MmioRead32 ((UINTN)(FCH_SPI_BASE_ADDRESS + FCH_SPI_MMIO_REG5C_Addr32_Ctrl3));

  SpiRomPageXor = (UINT8)(Value32 & FCH_SPI_SPIROM_PAGE_MASK);
  RomPage ^= SpiRomPageXor;

  return (RomPage << 24);
}

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
  UINT32                    Bank;

  Bank = DetectRom2Page();

  if ((Bank & BIT24) != (Offset & BIT24)){
    return FALSE;
  }else {
    return TRUE;
  }
}
