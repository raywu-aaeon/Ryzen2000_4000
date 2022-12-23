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
 * @param[in] Offset - The offset of ROM
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
  return FALSE;
}

/**
 * FchSpiRomReadEx - Extended fucntion to read the SPI ROM
 *
 *
 * @param[in] Location - Offset of host SPI ROM2/ROM3 address window
 *                     - Host address in ROM2/ROM3 window to SPI ROM
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
  return FALSE;
}