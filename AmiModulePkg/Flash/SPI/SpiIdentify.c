//***********************************************************************
//*                                                                     *
//*                      Copyright (c) 1985-2021, AMI.                  *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Flash update routines file.
**/

//----------------------------------------------------------------------------
// Includes
#include <Uefi.h>
#include <Token.h>
#include <Library/BaseMemoryLib.h>
#include <FlashPart.h>
#include "SpiFlash.h"
//----------------------------------------------------------------------------
// Local defines for transaction types
#ifndef SPI_OPCODE_TYPE_READ_NO_ADDRESS
#define SPI_OPCODE_TYPE_READ_NO_ADDRESS     0x0
#define SPI_OPCODE_TYPE_WRITE_NO_ADDRESS    0x1
#define SPI_OPCODE_TYPE_READ_WITH_ADDRESS   0x2
#define SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS  0x3
#endif
//----------------------------------------------------------------------------
// Module level global data
extern  UINT16          gFlashId;
extern  UINT32          gDeviceCapacity;
extern  FLASH_PART      gCommonSpiFlash;
extern  EX_FLASH_PART   gExFlashPart;
extern  UINT8           gFlashDeviceNumber[FLASH_PART_STRING_LENGTH];
//----------------------------------------------------------------------------
// Extern Function Prototypes
extern
BOOLEAN
CommonSpiReadId(
    FLASH_INFO  *FlashInfo,
    UINT32      *FlashId
);

extern
VOID
ReinitializeSpiEnvironment(
    FLASH_INFO  *FlashInfo
);
//----------------------------------------------------------------------------
// Flash Part Data Structures
FLASH_INFO Sst_25VF =
    {
        // Write Byte
        {SPI_SST25LF_COMMAND_WRITE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
         // Read Data
        {SPI_SST25VF_COMMAND_READ,          SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k
        {SPI_SST25LF_COMMAND_ERASE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Erase 64k
        {SPI_SST25LF_COMMAND_ERASE_64K,     SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_SST25LF_COMMAND_READ_STATUS,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_SST25VF_COMMAND_READ_ID,       SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Write Status Register
        {SPI_SST25LF_COMMAND_WRITE_S,       SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable
        {SPI_SST25LF_COMMAND_WRITE_S_EN,    SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Enable
        {SPI_SST25LF_COMMAND_WRITE_ENABLE,  SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        1,                                  // Page Size
        SECTOR_SIZE_4KB
    };

FLASH_INFO Sst_25LF =
    {
        // Write Byte
        {SPI_SST25LF_COMMAND_WRITE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Data
        {SPI_SST25LF_COMMAND_READ,          SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k
        {SPI_SST25LF_COMMAND_ERASE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Erase 64k
        {SPI_SST25LF_COMMAND_ERASE_64K,     SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_SST25LF_COMMAND_READ_STATUS,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_SST25LF_COMMAND_READ_ID,       SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Write Status Register
        {SPI_SST25LF_COMMAND_WRITE_S,       SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable
        {SPI_SST25LF_COMMAND_WRITE_S_EN,    SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Enable
        {SPI_SST25LF_COMMAND_WRITE_ENABLE,  SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        1,                                  // Page Size
        SECTOR_SIZE_4KB
    };

FLASH_INFO Stm_25PE =
    {
        // Write Byte
        {SPI_M25PExx_COMMAND_WRITE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Data
        {SPI_M25PExx_COMMAND_READ,          SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k
        {SPI_M25PExx_COMMAND_ERASE_4K,      SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Erase 64k
        {SPI_M25PExx_COMMAND_ERASE,         SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_M25PExx_COMMAND_READ_STATUS,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_M25PExx_COMMAND_READ_ID,       SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Status Register
        {SPI_M25PExx_COMMAND_WRITE_S,       SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable - Not available on this part
        {0,                                 SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Enable
        {SPI_M25PExx_COMMAND_WRITE_ENABLE,  SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        256,
        SECTOR_SIZE_64KB
    };

FLASH_INFO Atmel_26DF =
    {
        // Write Byte
        {SPI_AT26DF_COMMAND_WRITE,          SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Data
        {SPI_AT26DF_COMMAND_READ,           SPI_OPCODE_TYPE_READ_WITH_ADDRESS},
        // Erase 4k
        {SPI_AT26DF_COMMAND_ERASE,          SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Erase 64k
        {SPI_AT26DF_COMMAND_ERASE_64K,      SPI_OPCODE_TYPE_WRITE_WITH_ADDRESS},
        // Read Device Status Reg
        {SPI_AT26DF_COMMAND_READ_STATUS,    SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Read device ID
        {SPI_AT26DF_COMMAND_READ_ID,        SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Status Register
        {SPI_AT26DF_COMMAND_WRITE_S,        SPI_OPCODE_TYPE_WRITE_NO_ADDRESS},
        // Write Status Enable
        {SPI_AT26DF_COMMAND_UNPROTECT,      SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        // Write Enable
        {SPI_AT26DF_COMMAND_WRITE_ENABLE,   SPI_OPCODE_TYPE_READ_NO_ADDRESS},
        256,
        SECTOR_SIZE_4KB
    };
//----------------------------------------------------------------------------
// Functions Definitions

//----------------------------------------------------------------------------
// Identify Functions
/**
 * This function identifies the supported flash parts and returns appropriate
 * flash device API pointer. If flash part is not supported by this module it
 * will return FALSE.
 *
 * @param BlockAddress Block address of the flash part. Can be used to
 *                      send ID command
 * @param FlashStruct Pointer to hold the returned flash API
 *
 * @retval TRUE If flash part is supported, FlashApi contains routines to
 *              handle the flash requests
 * @retval FALSE Flash part is not supported
 */
BOOLEAN
IdentifySst_25LF(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
)
{
    UINT32  MfgDevId;

    if( !CommonSpiReadId( &Sst_25LF, &MfgDevId ) )
        return FALSE;

    switch( (UINT16)MfgDevId )
    {
        // Is SST 4M SPI flash part ?
        case SST_25LF040A :
            gExFlashPart.FlashCapacity = 0x80000;
            CopyMem( gFlashDeviceNumber, "SST 25LF040", 11 );
            break;
        // Is SST 8M SPI flash part ?
        case SST_25LF080A :
            gExFlashPart.FlashCapacity = 0x100000;
            CopyMem( gFlashDeviceNumber, "SST 25LF080", 11 );
            break;
        default :
            return FALSE;
    }

    *FlashStruct = &gCommonSpiFlash;
    CopyMem( &gExFlashPart.FlashCommandMenu, &Sst_25LF, sizeof(FLASH_INFO) );
    gExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = (UINT16)MfgDevId;
    gDeviceCapacity = gExFlashPart.FlashCapacity;
    (*FlashStruct)->FlashProgramSize = Sst_25LF.PageSize;
    (*FlashStruct)->FlashSectorSize = Sst_25LF.SectorSize;
    (*FlashStruct)->FlashPartNumber = gFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    // ReinitializeSpiEnvironment ( &gExFlashPart.FlashCommandMenu );
    return  TRUE;
}

/**
 * This function identifies the supported flash parts and returns appropriate
 * flash device API pointer. If flash part is not supported by this module it
 * will return FALSE.
 *
 * @param BlockAddress Block address of the flash part. Can be used to
 *                      send ID command
 * @param FlashStruct Pointer to hold the returned flash API
 *
 * @retval TRUE If flash part is supported, FlashApi contains routines to
 *              handle the flash requests
 * @retval FALSE Flash part is not supported
 */
BOOLEAN
IdentifyAtmel_26DF(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
)
{
    UINT32  MfgDevId;

    if( !CommonSpiReadId( &Atmel_26DF, &MfgDevId ) )
        return FALSE;

    switch( (UINT16)MfgDevId )
    {
        // Is Atmel 4M SPI flash part ?
        case ATMEL_26DF041 :
            gExFlashPart.FlashCapacity = 0x80000;
            Atmel_26DF.Erase64K.Opcode = SPI_INVALID_COMMAND;
            CopyMem( gFlashDeviceNumber, "ATMEL 26DF041/25DF041", 21 );
            break;
        // Is Atmel 8M SPI flash part ?
        case ATMEL_26DF081 :
            gExFlashPart.FlashCapacity = 0x100000;
            CopyMem( gFlashDeviceNumber, "ATMEL 26DF081/25DF081", 21 );
            break;
        // Is Atmel 16M SPI flash part ?
        case ATMEL_26DF161 :
        case ATMEL_25DQ161 :
            gExFlashPart.FlashCapacity = 0x200000;
            CopyMem( gFlashDeviceNumber, "ATMEL 26DF161/25DQ161", 21 );
            break;
        // Is Atmel 32M SPI flash part ?
        case ATMEL_26DF321 :
            gExFlashPart.FlashCapacity = 0x400000;
            CopyMem( gFlashDeviceNumber, "ATMEL 26DF321/25DF321", 21 );
            break;
        // Is Atmel 64M SPI flash part ?
        case ATMEL_25DF641 :
            gExFlashPart.FlashCapacity = 0x800000;
            CopyMem( gFlashDeviceNumber, "ATMEL 26DF641/25DF641", 21 );
            break;
        case ADESTO_AT25SF641 :
            gExFlashPart.FlashCapacity = 0x800000;
            Atmel_26DF.WriteStatusEnable.Opcode = SPI_AT26DF_COMMAND_WRITE_S_EN;
            Atmel_26DF.SectorSize = SECTOR_SIZE_4KB;
            CopyMem( gFlashDeviceNumber, "ADESTO AT25SF641", 16 );
            break;
        case ADESTO_AT25SL641 :
            gExFlashPart.FlashCapacity = 0x800000;
            Atmel_26DF.WriteStatusEnable.Opcode = SPI_AT26DF_COMMAND_WRITE_S_EN;
            Atmel_26DF.SectorSize = SECTOR_SIZE_4KB;
            CopyMem( gFlashDeviceNumber, "ADESTO AT25SL641", 16 );
            break;
        case ADESTO_AT25SL128A :
            gExFlashPart.FlashCapacity = 0x1000000;
            Atmel_26DF.WriteStatusEnable.Opcode = SPI_AT26DF_COMMAND_WRITE_S_EN;
            Atmel_26DF.SectorSize = SECTOR_SIZE_4KB;
            CopyMem( gFlashDeviceNumber, "ADESTO AT25SL128A", 17 );
            break;
        default :
            return FALSE;
    }
    *FlashStruct = &gCommonSpiFlash;
    CopyMem( &gExFlashPart.FlashCommandMenu, &Atmel_26DF, sizeof(FLASH_INFO) );
    gExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = (UINT16)MfgDevId;
    (*FlashStruct)->FlashProgramSize = Atmel_26DF.PageSize;
    (*FlashStruct)->FlashSectorSize = Atmel_26DF.SectorSize;
    (*FlashStruct)->FlashPartNumber = gFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    ReinitializeSpiEnvironment( &gExFlashPart.FlashCommandMenu );
    gDeviceCapacity = gExFlashPart.FlashCapacity;
    return  TRUE;
}

/**
 * This function identifies the flash capacity of supported flash parts by
 * its capacity ID.
 *
 * @param VenDevId Manufacturer/Device ID of flash part.
 *
 * @retval flash capacity
 */
UINT32
StmCheckMemoryCapacity(
    IN  UINT32  VenDevId
)
{
    switch( (VenDevId & 0x00FF0000) >> 16 )
    {
        case 0x10 : return ( 0x10000 );
        case 0x11 : return ( 0x20000 );
        case 0x12 : return ( 0x40000 );
        case 0x13 : return ( 0x80000 );
        case 0x14 : return ( 0x100000 );
        case 0x15 : return ( 0x200000 );
        case 0x36 : // MX25U32xx
        case 0x16 : return ( 0x400000 );
        case 0x37 : // MX25U64xx
        case 0x17 : return ( 0x800000 );
        case 0x38 : // MX25U128xx
        case 0x18 : return ( 0x1000000 );
        case 0x39 : // MX25U256xx
        case 0x19 : return ( 0x2000000 );
        case 0x1A : // MX25L51245G
        case 0x20 : return ( 0x4000000 );
        case 0x1B : // MX66L1G45G
        case 0x21 : return ( 0x8000000 );
    }
    return (FLASH_SIZE);
}

/**
 * This function identifies the flash capacity of supported flash parts by
 * its capacity ID.
 *
 * @param VenDevId Manufacturer/Device ID of flash part.
 *
 * @retval flash capacity
 */
UINT32
SpansionCheckMemoryCapacity(
    IN  UINT32  VenDevId
)
{
    switch( (VenDevId & 0x00FF0000) >> 16 )
    {
        case 0x12 : return ( 0x80000 );
        case 0x13 : return ( 0x100000 );
        case 0x14 : return ( 0x200000 );
        case 0x46 :                         // PMC 25LQ032
        case 0x15 : return ( 0x400000 );
        case 0x16 : return ( 0x800000 );
        case 0x17 : return ( 0x1000000 );
        case 0x20 : return ( 0x4000000 );
    }
    return (FLASH_SIZE);
}

/**
 * This function identifies the flash capacity of supported flash parts by
 * its capacity ID.
 *
 * @param VenDevId Manufacturer/Device ID of flash part.
 *
 * @retval flash capacity
 */
UINT32
IntelCheckMemoryCapacity(
    IN  UINT32  VenDevId
)
{
    switch( (VenDevId & 0x00FF0000) >> 16 )
    {
        case 0x11 :
        case 0x15 : return ( 0x200000 );
        case 0x12 :
        case 0x16 : return ( 0x400000 );
        case 0x13 :
        case 0x17 : return ( 0x800000 );
    }
    return (FLASH_SIZE);
}

/**
 * This function identifies the flash capacity of supported flash parts by
 * its capacity ID.
 *
 * @param VenDevId Manufacturer/Device ID of flash part.
 *
 * @retval flash capacity
 */
UINT32
SstCheckMemoryCapacity(
    IN  UINT32  VenDevId
)
{
    switch( (VenDevId & 0x00FF0000) >> 16 )
    {
        case 0x8C : return ( 0x40000 );
        case 0x8D : return ( 0x80000 );
        case 0x8E : return ( 0x100000 );
        case 0x01 : // SST 26VF016
        case 0x41 : return ( 0x200000 );
        case 0x02 : // SST 26VF032
        case 0x4A : return ( 0x400000 );
        case 0x43 : // SST 26VF064
        case 0x4B : return ( 0x800000 );
    }
    return (FLASH_SIZE);
}

/**
 * This function identifies the supported flash parts and returns appropriate
 * flash device API pointer. If flash part is not supported by this module it
 * will return FALSE.
 *
 * @param BlockAddress Block address of the flash part. Can be used to
 *                      send ID command
 * @param FlashStruct Pointer to hold the returned flash API
 *
 * @retval TRUE If flash part is supported, FlashApi contains routines to
 *              handle the flash requests
 * @retval FALSE Flash part is not supported
 */
BOOLEAN
IdentifyStm_25PExx(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
)
{
    UINT32  MfgDevId;

    if( !CommonSpiReadId( &Stm_25PE, &MfgDevId ) )
        return FALSE;

    switch( (UINT16)MfgDevId )
    {
        // erase page size = 256 bytes.
        case STM_25PExx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_256B;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_PAGE_ERASE;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "STM/Numonyx 25PE Series", 23 );
            break;
        // erase sector size = 4K bytes.
        case SST_26VFxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.GlobalBlockUnlock = TRUE;
            gExFlashPart.FlashCapacity = SstCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "SST 26VF Series", 15 );
            break;
        case PMC_25LVxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            Stm_25PE.Erase.Opcode = SPI_PMC25LV_COMMAND_ERASE;
            gExFlashPart.FlashCapacity = \
                                SpansionCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "PMC 25LV/LQ Series", 18 );
            break;
        case AMIC_25Lxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = \
                                SpansionCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "AMIC 25L Series", 15 );
            break;
        case AMIC_25Lxxx_ID :
        case AMIC_25LQxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "AMIC 25L/LQ Series", 18 );
            break;
        case EON_25Fxx_ID :
        case EON_25Qxx_ID :
        case EON_25Sxx_ID :
        case EON_25QHxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "EON 25F/Q/S/QH Series", 21 );
            break;
        case STM_25PXxx_ID :
        case STM_25PFxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "STM/Micron/Numonyx 25PF/PX Series", 33 );
            break;
        case XMC_25QUxx_ID :
        case XMC_25QUxxB_ID :
        case XMC_25QUxxC_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "XMC 25QU Series", 15 );
            break;
        case XMC_25QHxx_ID :
        case XMC_25QHxxB_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "XMC 25QH Series", 15 );
            break;
        case XMC_25RHxxC_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "XMC 25RH Series", 15 );
            break;
        case XMC_25RUxxC_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "XMC 25RU Series", 15 );
            break;
        case MXIC_25Lxxxx_ID :
        case MXIC_25Lxx35_ID :
        case MXIC_25Lxx36_ID :
        case MXIC_25Uxx35_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "MXIC 25L/U Series", 17 );
            break;
        case MXIC_25Rxx35_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "MXIC 25R Series", 15 );
            break;
        case MXIC_77Lxx50F_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "MXIC 77L Series", 15 );
            break;
        case WINBOND_25Xxx_ID :
        case WINBOND_25Qxx_ID :
        case WINBOND_25QxxF_ID :
        case WINBOND_25QxxW_ID :
        case WINBOND_25QxxJ_DTR_ID :
        case WINBOND_25MxxJ_ID :
        case WINBOND_25QxxJ_IM_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Winbond 25X/Q Series", 20 );
            break;
        case GD_25Qxx_ID :
        case GD_25LQxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "GigaDevice 25Q Series", 21 );
            break;
        case GD_25LBxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "GigaDevice 25LB Series", 22 );
            break;
        case GD_25Bxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "GigaDevice 25B Series", 21 );
            break;
        // erase block size = 64K bytes.
        case EON_25Pxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "EON 25P Series", 14 );
            break;
        case STM_25Pxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            if( gExFlashPart.FlashCapacity == 0x1000000 )
            {
                Stm_25PE.SectorSize = SECTOR_SIZE_256KB;
            }
            CopyMem( gFlashDeviceNumber, "STM/Micron/Numonyx 25P Series", 29 );
            break;
        case Numonyx_25Qxx_ID :
#if NUMONYX_USE_BLOCK_ERASE
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Micron/Numonyx 25Q Series", 25 );
            break;
#endif
        case Numonyx_25QxxA_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Micron/Numonyx 25Q Series", 25 );
            break;
        case SPANSION_25FLxxx_ID :
            gExFlashPart.FlashCapacity = \
                                    SpansionCheckMemoryCapacity( MfgDevId );
            if( gExFlashPart.FlashCapacity == 0x4000000 )
            {
                //Cypress S25FS512S
                Stm_25PE.SectorSize = SECTOR_SIZE_256KB;
                Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
                Stm_25PE.Erase64K.Opcode = SPI_INVALID_COMMAND;
                CopyMem( gFlashDeviceNumber, "Cypress 25FS-S Series", 21 );
            }
            else
            {
                Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
                Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
                CopyMem( gFlashDeviceNumber, "Spansion 25FL Series", 19 );
            }
            break;
        case SPANSION_25FLxxxP_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            gExFlashPart.FlashCapacity = \
                                    StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Spansion 25FL(P) Series", 23 );
            break;
        case SPANSION_25FL1xxK_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = \
                                    StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Spansion 25FL(K) Series", 23 );
            break;
        case SPANSION_25FLxxL_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = \
                                    StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Spansion 25FL(L) Series", 23 );
            break;
        case INTEL_25Fxxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_64KB;
            Stm_25PE.Erase.Opcode = SPI_M25PExx_COMMAND_ERASE;
            gExFlashPart.FlashCapacity = IntelCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Intel/Numonyx 25F160/320", 24 );
            break;
        case FM_25Qxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "FIDELIX 25Q Series", 18 );
            break;
        case FM_25Mxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "FIDELIX 25M Series", 18 );
            break;
        case SHFM_25Qxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Fudan FM25Q Series", 18 );
            break;
        case SHFM_25Wxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "Fudan FM25W Series", 18 );
            break;
        case ISSI_25LPxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "ISSI 25LP Series", 16 );
            break;
        case ISSI_25WPxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "ISSI 25WP Series", 16 );
            break;
        case ESMT_25Lxx_ID :
        case ESMT_25LxxQ_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "ESMT 25L QA/PA Series", 21 );
            break;
        case XT_25Fxx_ID :
            Stm_25PE.SectorSize = SECTOR_SIZE_4KB;
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "XTX 25F Series", 14 );
            break;
        default :
            return FALSE;
    }
    *FlashStruct = &gCommonSpiFlash;
    CopyMem( &gExFlashPart.FlashCommandMenu, &Stm_25PE, sizeof(FLASH_INFO) );
    gExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = (UINT16)MfgDevId;
    (*FlashStruct)->FlashProgramSize = Stm_25PE.PageSize;
    (*FlashStruct)->FlashSectorSize = Stm_25PE.SectorSize;
    (*FlashStruct)->FlashPartNumber = gFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    ReinitializeSpiEnvironment( &gExFlashPart.FlashCommandMenu );
    gDeviceCapacity = gExFlashPart.FlashCapacity;
    return TRUE;
}

/**
 * This function identifies the supported flash parts and returns appropriate
 * flash device API pointer. If flash part is not supported by this module it
 * will return FALSE.
 *
 * @param BlockAddress Block address of the flash part. Can be used to
 *                      send ID command
 * @param FlashStruct Pointer to hold the returned flash API
 *
 * @retval TRUE If flash part is supported, FlashApi contains routines to
 *              handle the flash requests
 * @retval FALSE Flash part is not supported
 */
BOOLEAN
IdentifySst_25VF(
    IN  volatile UINT8  *BlockAddress,
    OUT FLASH_PART      **FlashStruct
)
{
    UINT32  MfgDevId;

    if( !CommonSpiReadId( &Sst_25VF, &MfgDevId ) )
        return FALSE;

    switch( (UINT16)MfgDevId )
    {
        case SST_25VFxxx_ID :
            gExFlashPart.FlashCapacity = SstCheckMemoryCapacity( MfgDevId );
            if( gExFlashPart.FlashCapacity >= 0x800000 ) Sst_25VF.PageSize = 256;
#if defined(AAI_WORD_PROGRAM) && (AAI_WORD_PROGRAM == 1)
            else gExFlashPart.AAIWordProgram = TRUE;
#endif
            CopyMem( gFlashDeviceNumber, "SST 25VF Series", 15 );
            break;
        case ESMT_25LxxxT_ID :
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            CopyMem( gFlashDeviceNumber, "ESMT 25L T Series", 17 );
            break;
        case ESMT_25LxxxB_ID :
            gExFlashPart.FlashCapacity = StmCheckMemoryCapacity( MfgDevId );
            Sst_25VF.WriteStatusEnable.Opcode = 0;
            CopyMem( gFlashDeviceNumber, "ESMT 25L B Series", 17 );
            break;
        default :
            return FALSE;
    }
    *FlashStruct = &gCommonSpiFlash;
    CopyMem( &gExFlashPart.FlashCommandMenu, &Sst_25VF, sizeof(FLASH_INFO) );
    gExFlashPart.FlashVenDevId = MfgDevId;
    gFlashId = (UINT16)MfgDevId;
    (*FlashStruct)->FlashProgramSize = Sst_25VF.PageSize;
    (*FlashStruct)->FlashSectorSize = Sst_25VF.SectorSize;
    (*FlashStruct)->FlashPartNumber = gFlashDeviceNumber;
    // Update the OpCode to OpMenu immediately if need.
    ReinitializeSpiEnvironment( &gExFlashPart.FlashCommandMenu );
    gDeviceCapacity = gExFlashPart.FlashCapacity;
    return TRUE;
}